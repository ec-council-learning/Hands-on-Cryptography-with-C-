// src/format.h
#ifndef __CRYPTOSTARS_FORMAT_H__
#define __CRYPTOSTARS_FORMAT_H__

#include <algorithm> // transform
#include <iterator> // back_inserter
#include <cctype> // tolower
#include <iomanip> // hex
#include <sstream> // stringstream
#include <string> // string
#include <cryptopp/cryptlib.h> // byte, Integer, SecByteBlock
#include <cryptopp/filters.h> // StringSink
#include <cryptopp/hex.h> // HexEncoder

namespace CryptoStars {
namespace Format {
  /// \brief Returns the lowercase formatted string
  inline std::string strtolower(const std::string& input)
  {
    std::string output;
    output.resize(input.size());

    std::transform(input.begin(), input.end(), output.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return output;
  }

  /// \brief Returns only the values of a given map, as a vector
  template <typename map_t, typename vector_t>
  inline void map_to_vector(const map_t& input, vector_t &output)
  {
    std::transform(
      input.begin(), input.end(),
      std::back_inserter(output),
      [](auto &kv) { return kv.second; }
    );
  }

  /// \brief Returns the key in hexadecimal format as a string
  inline std::string key_to_hex(const CryptoPP::Integer& key_be)
  {
    std::stringstream stream;
    stream << std::hex << key_be;
    return stream.str();
  }

  /// \brief Returns the SecByteBlock in hexadecimal format as a string
  inline std::string bytes_to_hex(const CryptoPP::SecByteBlock& block)
  {
    std::string out;
    CryptoPP::HexEncoder key_encoder(new CryptoPP::StringSink(out));
    key_encoder.Put((const CryptoPP::byte*) block.data(), block.size());
    key_encoder.MessageEnd();
    return out;
  }

  /// \brief Returns the string of bytes in hexadecimal format
  inline std::string bytes_to_hex(const std::string& block)
  {
    std::string out;
    CryptoPP::HexEncoder key_encoder(new CryptoPP::StringSink(out));
    key_encoder.Put((const CryptoPP::byte*) block.data(), block.size());
    key_encoder.MessageEnd();
    return out;
  }

  /// \brief Returns the bytes as parsed from hexadecimal format
  inline void hex_to_bytes(CryptoPP::byte* outString, const std::string& inString)
  {
    unsigned int byteLength = inString.length() / 2;
    std::stringstream stream;
    stream << std::hex;
    for (int i = 0; i < inString.length(); i += 2) {
      int byte;

      stream << inString.substr(i, 2);
      stream >> byte;
      stream.str(std::string());
      stream.clear();

      outString[i/2] = byte & 0xFF;
    }
  }
}
}

#endif