// src/client.h
#ifndef __HTTPSAFE_CLIENT_H__
#define __HTTPSAFE_CLIENT_H__
#include <iostream>
#include <string>
#include <memory>
#include <span>
#include <botan/tls_session_manager_memory.h>
#include <botan/auto_rng.h>
#include <botan/asio_compat.h>
#include <boost/asio.hpp>
#include "backend.h"

namespace HTTPSafe {

  // Define a class for handling the HTTPS client
  class Client {
    boost::asio::io_context&        io_context_;
    boost::asio::ip::tcp::socket    socket_;
    boost::asio::ip::tcp::resolver  resolver_;
    Botan::System_Certificate_Store system_cert_store;

    std::string host_;
    std::shared_ptr<Botan::AutoSeeded_RNG>  rng_;
    std::unique_ptr<Botan::TLS::Client>     tls_client_;

    std::array<uint8_t, 4096> buffer_;

  public:
    bool handshake_completed = false;

    // Default constructor
    Client(boost::asio::io_context&,
      const std::string&,
      const std::string&);

    void async_send_data(std::span<const uint8_t>);
    void async_read_data();

    void send_http_request(const std::string&);
    void read_http_response();

    std::string get_host() const {
      return host_;
    }

  private:
    void do_handshake();
  };

  // Define a class for handling TLS callbacks
  class Handlers: public Botan::TLS::Callbacks {
    Client&  channel_;
  public:
    Handlers(Client& channel) : channel_(channel) {}

    // TLS callbacks implementation
    void tls_emit_data(std::span<const uint8_t> data) override;
    void tls_record_received(
      uint64_t seq_no,
      std::span<const uint8_t> data
    ) override;
    void tls_alert(Botan::TLS::Alert alert) override;
    void tls_session_established(const Botan::TLS::Session_Summary &session) override;
    void tls_session_activated() override;
  };
}
#endif