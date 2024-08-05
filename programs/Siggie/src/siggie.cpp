// src/siggie.cpp
#include "command.h"
#include <stdexcept> // std::runtime_error
#include <iostream> // std::cout, std::endl

/// \brief Prints the usage information for the siggie software
int Siggie::print_usage() {
  std::cout << "Usage: Siggie <file> <sig_file> [-p passphrase] [--debug] [--check]" << std::endl
    << "  e.g: " << std::endl
    << "  Siggie data/document" << std::endl
    << "  echo 'Hello, World!' | Siggie" << std::endl
    << "  cat data/document | Siggie --check data/document.sig" << std::endl
    << std::endl << "OPTIONS: " << std::endl
    << "  file: Determines the document to sign/verify." << std::endl
    << "  sig_file: Determines the signature file being output/verified." << std::endl
    << "  -p passphrase: Uses given passphrase to unlock the identity file." << std::endl
    << "  --check: Enables the verification mode for digital signatures." << std::endl
    << "  --debug: Enables the debug mode (verbose) for the program." << std::endl
    << std::endl << "COMMANDS: " << std::endl
    << "  sign: Pass a document <file> to sign it using a DSA." << std::endl
    << "  verify: Pass a signature <file> (.sig) to verify a signature." << std::endl;
  return 1;
}

/// \brief Helper function to create and run one of the above commands using
///        the keypair \a identity,options \a args and an optional \a buffer.
std::string Siggie::run_command(
  const Identity& identity,
  Siggie::args_t args,
  const std::string& buffer
) {
  std::string signature_suffix = ".sig";
  std::string doc_file = Siggie::get_option("file", args),
              sig_file = Siggie::get_option("sig_file", args),
              message;

  // accepts a signature suffix in the filename, i.e. ".sig"
  if (doc_file.ends_with(signature_suffix)) {
    sig_file = sig_file.empty() ? doc_file : sig_file;
    doc_file = doc_file.substr(0, doc_file.find(signature_suffix));
  }
  // accepts original document to construct signature file
  else if (!doc_file.empty() && sig_file.empty()) {
    sig_file = doc_file + signature_suffix;
  }
  // accepts stdin (buffer) to construct signature file data/stdin.sig
  else
    sig_file = (doc_file = "data/stdin") + signature_suffix;

  // accepts an original document or stdin to SIGN
  if (Siggie::get_option("--check", args).empty()) {
    auto command = make_sign_command(identity);
    auto result  = command->handle_fn(doc_file, sig_file, buffer);
    message = "Signature: " + result;
  }
  // accepts a signature file to VERIFY (--check)
  else {
    auto command = make_verify_command(identity);
    auto result  = command->handle_fn(doc_file, sig_file, buffer);
    message = std::string("Verified: ").append(result ? "OK" : "NOT OK");
  }

  return message;
}