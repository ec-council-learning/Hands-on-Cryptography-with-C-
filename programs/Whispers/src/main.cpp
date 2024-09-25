// src/main.cpp
#include <iostream> // std::cout
#include <string> // std::string
#include "identity.h" // wiz::Identity
#include "contact.h" // wiz::Contact
#include "whisper.h" // wiz::Whisper

int print_usage() {
  std::cout
    << "Usage: wiz [-h] <command> <friend-pubkey> <whisper>\n"
    << "  e.g: wiz id\n"
    << "  e.g: wiz write path/recipient/pubkey \"Hey, this is my whisper!\"\n"
    << "  e.g: wiz read path/sender/pubkey \"...Jf5qIvDv/10Xdfwz8z9D...\"\n"
    << "\nFLAGS: \n"
    << "  -h: Prints this help message and usage examples.\n"
    << "\nCOMMANDS: \n"
    << "  write: Create an encrypted Whisper destined at a ECDH public key.\n"
    << "  read: Read an encrypted Whisper as received from ECDH public key.\n"
    << "  id: Create new Whisper ID to accept Whispers for ECDH public key.\n";
  return 1;
}

int main(int argc, char* argv[])
{
  // TODO: Permit overwrite of identity file path
  std::string id_file = "data/id_ecdh.wizid";
  wiz::Identity* user;

  // read the first argument to identify potential -h or id call
  auto flag = std::string(argv[1]);
  if (flag == "id") {
    // setup the identity or open it (ECDH private/public key)
    // Note: no need to store in memory.
    user = new wiz::Identity(id_file);
    std::cout << static_cast<std::string>(*user);

    // Job done.
    delete user;
    return 0;
  }

  // otherwise, 4 options are required.
  // also accepted are: `wiz -h` and `wiz help`
  auto missing_args = flag != "id" && argc < 4;
  if (missing_args || flag == "-h" || flag == "help")
    return print_usage();

  // parses command options for read and write commands
  std::string command = argv[1],
              contact = argv[2],
              whisper = argv[3];

  // first setup the current identity (ECDH private/public key)
  user = new wiz::Identity(id_file);

  // creates a ECDH ephemeral private key for communications
  // between `user` (the sender) and `chatee` (the recipient).
  wiz::Contact* chatee = new wiz::Contact(contact);
  wiz::Whisper*   chat = new wiz::Whisper(*user, *chatee);
  std::cout << "Session created successfully." << std::endl;

  // in the case of decryption, an exception is thrown if
  // the decrypting private key is not the recipient key.
  try {
    // handles the "wiz read" and "wiz write" commands
    std::string result = chat->Handle(command, whisper);

    // prints the ciphertext (write) or plaintext (read)
    std::cout << "Whisper: " << result << std::endl;
  }
  catch (Botan::Exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    std::cerr << "Decryption failed. Must be recipient to decrypt!" << std::endl;
  }

  delete chat;
  delete chatee;
  delete user;
  return 0;
}