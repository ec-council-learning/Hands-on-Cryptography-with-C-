// src/listeners.h
#ifndef __HANDSHAKER_LISTENERS_H__
#define __HANDSHAKER_LISTENERS_H__
#include <span> // std::span
#include <botan/tls.h> // TLS::Callbacks
#include "channel.h"

namespace Handshaker {

  class HandshakeOnlyChannel;

  class Listeners : public Botan::TLS::Callbacks
  {
  private:
    HandshakeOnlyChannel& m_channel;

  public:
    Listeners(HandshakeOnlyChannel& channel) : m_channel(channel) {}

    void relay_message(std::span<const uint8_t> buffer);

    /// \brief Sends data to tls server
    void tls_emit_data(std::span<const uint8_t> data) override;

    /// \brief Processes full TLS record received by tls server
    void tls_record_received(
      uint64_t seq_no,
      std::span<const uint8_t> data
    ) override;

    /// \brief Handles a tls alert received from the tls server
    void tls_alert(Botan::TLS::Alert alert) override;

    /// \brief Handshake initiated and session ID created
    void tls_session_established(const Botan::TLS::Session_Summary &session) override;

    /// \brief Handshake complete and channel closed
    void tls_session_activated() override;
  };
}
#endif