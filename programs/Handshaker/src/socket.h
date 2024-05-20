// src/socket.h
#ifndef __HANDSHAKER_SOCKET_H__
#define __HANDSHAKER_SOCKET_H__

#include <unistd.h> // ::close
#include <string> // std::string
#include <botan/tls.h> // TLS::Client

namespace Handshaker {

  typedef int socket_type;
  typedef size_t sendrecv_len_type;

  inline socket_type invalid_socket() { return -1; }
  inline void close_socket(socket_type s) { ::close(s); }

  /// \brief Establishes a connection to host using ::socket and ::connect
  socket_type connect_to_host(const std::string&, uint16_t);

  /// \brief Uses ::read from multiplex I/O with socket and/or stdin
  ssize_t multiplex_read(socket_type, Botan::TLS::Client&&);

}

#endif