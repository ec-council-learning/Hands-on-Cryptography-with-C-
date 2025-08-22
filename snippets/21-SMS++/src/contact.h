// src/contact.h
#ifndef __SMSPLUSPLUS_CONTACT_H__
#define __SMSPLUSPLUS_CONTACT_H__
#include <memory> // std::unique_ptr
#include <string> // std::string
#include <vector> // std::vector
#include "identity.h" // Identity, PublicKeyImpl

namespace SMSpp {
  class Message;

  /// \brief Class implementation that describes contacts ("friends").
  class Contact {
    friend class Message;
    std::vector<uint8_t>              m_raw_public_key;
    std::unique_ptr<SMSpp::PublicKeyImpl> m_public_key;

  public:
    Contact(const Identity&);
    Contact(const std::string&);
    Contact(const Contact&);
    Contact(const Contact&&);
    virtual ~Contact() {}

    std::string Fingerprint() const;
  };
}
#endif