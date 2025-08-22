// src/whisper.h
#ifndef __WHISPERS_WHISPER_H__
#define __WHISPERS_WHISPER_H__
#include <string> // std::string
#include "identity.h"
#include "contact.h"

namespace wiz {
  class Identity;

  /// \brief Class implementation that describes ECIES-encrypted whispers.
  class Whisper
  {
    const Identity&   m_id;
    const Contact& m_friend;

  public:
    Whisper(const Identity&, const Contact&);
    virtual ~Whisper() {};

    std::string Handle(const std::string&, const std::string&) const;

  private:
    std::string Read(const std::string&) const;
    std::string Write(const std::string&) const;
  };
}
#endif