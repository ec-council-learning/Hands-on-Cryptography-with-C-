// src/client.cpp
#include <iostream>
#include <exception>
#include <botan/tls_session_manager_memory.h>
#include "client.h"

typedef boost::asio::io_context               iocontext_t;
typedef boost::asio::ip::tcp::resolver        resolver_t;
typedef Botan::TLS::Session_Manager_In_Memory session_mgr_t;
typedef HTTPSafe::CredentialsManager          creds_mgr_t;
typedef HTTPSafe::TLSPolicy                   tls_policy_t;

HTTPSafe::Client::Client(
  iocontext_t& io_context,
  const std::string& host,
  const std::string& port
) : host_(host), resolver_(io_context), socket_(io_context), io_context_(io_context)
{
  rng_ = std::make_shared<Botan::AutoSeeded_RNG>();
  auto session_manager = std::make_shared<session_mgr_t>(rng_);
  auto creds_manager = std::make_shared<creds_mgr_t>();
  auto tls_policy = std::make_shared<tls_policy_t>();

  // Resolve the hostname to an IP address
  resolver_t::results_type endpoints = resolver_.resolve(host, port);

  // Connect to the server
  boost::asio::connect(socket_, endpoints);

  // Set up Botan TLS client
  Botan::TLS::Server_Information server_info(host, port);
  tls_client_ = std::make_unique<Botan::TLS::Client>(
    /* callbacks = */std::make_shared<HTTPSafe::Handlers>(*this),
    /* manager = */session_manager,
    /* creds   = */creds_manager,
    /* policy  = */tls_policy,
    /* rng     = */rng_,
    /* server  = */server_info,
    /* version = */Botan::TLS::Protocol_Version::TLS_V12
  );

  // Handshake starts with a read from TLS peer
  async_read_data();
}

void HTTPSafe::Client::async_send_data(std::span<const uint8_t> data) {
  boost::asio::write(socket_, boost::asio::buffer(data, data.size()));
}

void HTTPSafe::Client::async_read_data() {
  socket_.async_read_some(boost::asio::buffer(buffer_),
    [this](boost::system::error_code ec, std::size_t length)
    {
      if (!ec) {
        // Feed the received data to Botan's TLS client
        tls_client_->received_data(buffer_.data(), length);

        // Continue reading for more data
        async_read_data();
      }
      else if (ec != boost::asio::error::eof) {
        throw boost::system::system_error(ec);
      }
    });

  // tells boost::asio to execute async tasks
  io_context_.run();
}

void HTTPSafe::Client::send_http_request(const std::string& request) {
  if (! handshake_completed)
    throw std::runtime_error(std::string("TLS handshake not completed. Cannot send request."));

  // Send HTTP request over TLS
  tls_client_->send(
    reinterpret_cast<const uint8_t*>(request.data()),
    request.size()
  );
}

void HTTPSafe::Client::read_http_response() {
  async_read_data();
}

void HTTPSafe::Handlers::tls_emit_data(std::span<const uint8_t> data) {
  channel_.async_send_data(data);
}

void HTTPSafe::Handlers::tls_record_received(
  uint64_t seq_no,
  std::span<const uint8_t> data
) {
  std::cout.write(reinterpret_cast<const char*>(data.data()), data.size());
}

void HTTPSafe::Handlers::tls_alert(Botan::TLS::Alert alert) {
  std::cerr << "TLS Alert: " << alert.type_string() << std::endl;
}

void HTTPSafe::Handlers::tls_session_established(const Botan::TLS::Session_Summary &session) {
  std::cout << "Session established with "
            << session.server_info().hostname() << std::endl;

  // Update completion flag
  channel_.handshake_completed = true;
}

void HTTPSafe::Handlers::tls_session_activated() {
  std::cout << "Session ready to be written to "
            << channel_.get_host() << std::endl;

  // Send an HTTP GET request over the established secure TLS channel
  std::string request = 
    "GET / HTTP/1.1\r\nHost: "
    + channel_.get_host() + "\r\n"
    + "Connection: close\r\n\r\n";

  channel_.send_http_request(request);
}