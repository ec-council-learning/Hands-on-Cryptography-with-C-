// src/socket.cpp
#include "socket.h"
#include <stdexcept> // std::runtime_error
#include <sys/socket.h> // socket, connect
#include <sys/time.h> // timeval
#include <sys/types.h> // fd_set, FD_x family
#include <netdb.h> // addrinfo, getaddrinfo, freeaddrinfo
#include <botan/mem_ops.h> // clear_mem

/// \brief Establishes a connection to host using ::socket and ::connect
Handshaker::socket_type Handshaker::connect_to_host(
  const std::string& host,
  uint16_t port
) {
  addrinfo hints;
  Botan::clear_mem(&hints, 1);
  hints.ai_family = AF_UNSPEC; // any of IPv4 & IPv6
  hints.ai_socktype = SOCK_STREAM; // <- TCP ; UDP would be SOCK_DGRAM
  addrinfo *res, *rp = nullptr;

  // Returns one or more addrinfo structures in res (linked list)
  if(::getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res) != 0) {
    throw std::runtime_error("getaddrinfo failed for " + host);
  }

  // Iterates through the linked list of Internet addresses
  // And tries to open a socket, then connect to host using the socket 
  Handshaker::socket_type fd = 0;
  for(rp = res; rp != nullptr; rp = rp->ai_next) {
    fd = ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if(fd == Handshaker::invalid_socket()) continue;

    // Connects to current host using created socket
    if(::connect(fd, rp->ai_addr, static_cast<socklen_t>(rp->ai_addrlen)) != 0) {
      ::close(fd);
      continue;
    }

    break;
  }

  ::freeaddrinfo(res);
  if(rp == nullptr) throw std::runtime_error("connect failed");
  return fd;
}

/// \brief Uses ::read from multiplex I/O with socket and/or stdin
ssize_t Handshaker::multiplex_read(
  Handshaker::socket_type sockfd,
  Botan::TLS::Client&& client
) {
  ssize_t got;
  fd_set readfds;
  FD_ZERO(&readfds); // zero bits initialization
  FD_SET(sockfd, &readfds); // set file descriptor bit in fd set

  // Monitors multiple file descriptors (multiplex I/O)
  struct timeval timeout = {1, 0};
  ::select(static_cast<int>(sockfd + 1), &readfds, nullptr, nullptr, &timeout);

  // Actively reading from socket (network) (max. 4kB)
  if (FD_ISSET(sockfd, &readfds)) {
    uint8_t buf[4 * 1024] = {0};
    got = ::read(sockfd, buf, sizeof(buf));

    // EOF or error ?
    if (got == 0 || got == -1) return got;
    client.received_data(buf, got);
  }

  // Actively reading from stdin (local) (max. 1kB)
  if(FD_ISSET(STDIN_FILENO, &readfds)) {
    uint8_t buf[1024] = {0};
    got = read(STDIN_FILENO, buf, sizeof(buf));

    // EOF or error ?
    if (got == 0 || got == -1) return got;
    if (got != 2 || buf[1] != '\n') {
      client.send(buf, got);
    }
  }

  return got;
}