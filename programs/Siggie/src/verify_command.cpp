// src/verify_command.cpp
#include "command.h"
#include <filesystem> // std::filesystem
#include <vector> // std::vector
#include <fstream> // std::ifstream
#include <sstream> // std::stringstream
#include <botan/pubkey.h> // PK_Verifier

/// \brief Factory function for the VerifyCommand instance with \a identity
std::unique_ptr<Siggie::VerifyCommand> Siggie::make_verify_command(
  const Identity& identity
) {
  return std::make_unique<VerifyCommand>("verify", [identity](
    std::string doc_file,
    std::string sig_file,
    std::string buffer
  ) {
    // make sure the signature document exists
    std::filesystem::directory_entry entry{sig_file};
    if (! entry.exists())
      throw std::runtime_error("Error: Provided file argument does not exist.");

    // reads the document content
    std::string data_buffer;
    if (! buffer.empty())
      data_buffer = buffer;
    else {
      std::ifstream doc_ptr(doc_file);
      std::stringstream doc_buffer;
      doc_buffer << doc_ptr.rdbuf();
      doc_ptr.close();
      data_buffer = doc_buffer.str();
    }

    // reads signature content
    std::ifstream  sig_ptr(sig_file);
    std::stringstream sig_buffer;
    sig_buffer << sig_ptr.rdbuf();
    sig_ptr.close();

    // re-construct public key and initialize verifier
    auto pub = identity.ExportPublicKey();
    Botan::PK_Verifier verifier(*pub, "SHA-256");
    verifier.update(data_buffer);

    std::string raw_signature = sig_buffer.str();
    std::vector<uint8_t> signature(raw_signature.begin(), raw_signature.end());
    return verifier.check_signature(signature);
  });
}