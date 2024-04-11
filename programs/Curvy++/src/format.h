// src/format.h
#ifndef __CURVYPP_FORMAT_H__
#define __CURVYPP_FORMAT_H__

#include <cryptopp/default.h> // Integer
#include <iomanip> // std::hex
#include <string> // std::string
#include <sstream> // std::stringstream

namespace CurvyPP {
namespace Format {

  /// \brief Returns the key in hexadecimal format as a string
  inline std::string key_to_hex(const CryptoPP::Integer& key_be)
  {
    std::stringstream stream;
    stream << std::hex << key_be;
    return stream.str();
  }

}
}

#endif