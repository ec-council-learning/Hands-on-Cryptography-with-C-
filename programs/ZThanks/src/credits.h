// src/credits.h
#ifndef __ZTHANKS_CREDITS_H__
#define __ZTHANKS_CREDITS_H__
#include <string> // std::string
#include <map> // std::map

namespace ztx {

  /// \brief Class implementation that describes encrypted credit messages.
  class ZCredits
  {
    std::string                        m_message;
    std::map<std::string, std::string> m_ciphers;

  public:
    /// \brief Creates a new credits instances with message \a msg.
    ZCredits(const std::string&);

    /// \brief Default class destructor.
    virtual ~ZCredits() {};

    /// \brief Returns the string representation of ZCredits instances.
    operator std::string() const;

  private:
    /// \brief Prepares a value \a val to be streamed over a string stream.
    std::string Stream_Value(const std::string&) const;
  };
}
#endif