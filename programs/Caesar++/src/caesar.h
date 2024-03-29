// src/caesar.h
#include <cryptopp/filters.h>

namespace CaesarPP {

  /// \brief Interface for the data processing portion of a Caesar Cipher
  class CaesarStreamTransformation : public CryptoPP::StreamTransformation
  {
  public:
    /// \brief Encrypt or decrypt an array of bytes
    void ProcessData(
      CryptoPP::byte *outString,
      const CryptoPP::byte *inString,
      size_t length
    );

    /// \brief Determines whether the cipher supports random access
    bool IsRandomAccess() const { return false; }

    /// \brief Determines whether the cipher is self-inverting
    bool IsSelfInverting() const { return false; }

    /// \brief Determines if the cipher is being operated in its forward direction
    bool IsForwardTransformation() const { return true; }
  };

}