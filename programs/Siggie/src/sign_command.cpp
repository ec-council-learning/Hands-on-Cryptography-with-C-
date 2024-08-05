// src/sign_command.cpp
#include "command.h"
#include <filesystem> // std::filesystem
#include <vector> // std::vector
#include <fstream> // std::ifstream
#include <sstream> // std::stringstream
#include <botan/auto_rng.h> // AutoSeeded_RNG
#include <botan/pubkey.h> // PK_Signer
#include <botan/hex.h> // hex_encode

/// \brief Factory function for the SignCommand instance with \a identity
std::unique_ptr<Siggie::SignCommand> Siggie::make_sign_command(
  const Identity& identity
) {
  return std::make_unique<SignCommand>("sign", [identity](
    std::string doc_file,
    std::string sig_file,
    std::string buffer
  ) {
    Botan::AutoSeeded_RNG rng;
    std::string data_buffer;

    if (! buffer.empty())
      data_buffer = buffer;
    else {
      // make sure the document to-be-signed exists
      std::filesystem::directory_entry entry{doc_file};
      if (! entry.exists())
        throw std::runtime_error("Error: Provided document does not exist.");

      // reads the content from file
      std::ifstream file_ptr(doc_file);
      std::stringstream file_buf;
      file_buf << file_ptr.rdbuf();
      file_ptr.close();
      data_buffer = file_buf.str();
    }

    // re-construct private key and initialize signer
    auto priv = identity.ExportPrivateKey();
    Botan::PK_Signer signer(*priv, rng, "SHA-256");
    signer.update(data_buffer);
    std::vector<uint8_t> sig = signer.signature(rng);

    // saves the signature bytes into a .sig file
    std::ofstream sig_ptr(sig_file);
    sig_ptr << std::string(sig.begin(), sig.end());
    sig_ptr.close();

    // returns hexadecimal signature notation
    return Botan::hex_encode(sig);
  });
}