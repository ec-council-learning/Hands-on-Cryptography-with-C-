// src/channel.cpp
#include "channel.h"
#include <memory> // std::make_shared
#include <botan/tls.h> // TLS
#include <botan/auto_rng.h> // AutoSeeded_RNG
#include "listeners.h"
#include "session.h"
#include "socket.h"

using SessionManagerImpl = Botan::TLS::Session_Manager_In_Memory;

int Handshaker::HandshakeOnlyChannel::TryHandshakeWithServer() {
  // Connects a socket to host:port using the socket library
  // This only validates the host and availability pre-TLS
  m_sockfd = Handshaker::connect_to_host(m_host, m_port);

  // Opens the TLS communication channel
  auto shared_rng = std::make_shared<Botan::AutoSeeded_RNG>();
  Botan::TLS::Client client(
    /* callbacks = */std::make_shared<Handshaker::Listeners>(*this),
    /* manager = */std::make_shared<SessionManagerImpl>(shared_rng),
    /* creds   = */std::make_shared<Handshaker::UnsafeSession>(),
    /* policy  = */std::make_shared<Botan::TLS::Strict_Policy>(),
    /* rng     = */shared_rng,
    /* server  = */Botan::TLS::Server_Information(m_host, m_port),
    /* version = */Botan::TLS::Protocol_Version::TLS_V13
  );

  // m_completed is set when Handshake is done (Listeners#tls_session_activated)
  while (! client.is_closed() && !m_completed) {
    // Reads from socket and/or stdin
    ssize_t got = Handshaker::multiplex_read(
      m_sockfd,
      std::move(client)
    );

    // EOF or error ?
    if (got == 0) break; // EOF
    else if (got == -1) continue; // error
  }

  client.close();
  ::close(m_sockfd);
  return 0;
}