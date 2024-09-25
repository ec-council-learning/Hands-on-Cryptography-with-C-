// src/main.cpp
#include <iostream> // std::cout
#include <string> // std::string
#include "identity.h" // c2c::Identity
#include "contact.h" // c2c::Contact
#include "message.h" // c2c::Message

int print_usage() {
  std::cout
    << "Usage: c2c [-h] <command> <friend-pubkey> <message>\n"
    << "  e.g: c2c write path/to/pubkey \"Hey, this is my message!\"\n"
    << "  e.g: c2c read path/to/pubkey \"...Jf5qIvDv/10Xdfwz8z9D...\"\n"
    << "\nFLAGS: \n"
    << "  -h: Prints this help message and usage examples.\n"
    << "\nCOMMANDS: \n"
    << "  write: Create an encrypted message destined at a ECDH public key.\n"
    << "  read: Read an encrypted message as received from ECDH public key.\n";
  return 1;
}

int main(int argc, char* argv[])
{
  // 4 options required, e.g.: `c2c write path/to/friend_ecdh.pub "My Friend"`
  // also accepted are: `c2c -h` and `c2c help`
  auto flag = std::string(argv[1]);
  if (argc < 4 || flag == "-h" || flag == "help")
    return print_usage();

  // parses command options
  std::string command = argv[1],
              contact = argv[2],
              message = argv[3];

  // first setup the current identity (ECDH private/public key)
  std::string id_file = "data/id_ecdh.c2cid";
  c2c::Identity* user = new c2c::Identity(id_file);

  // creates a ECDH ephemeral private key for communications
  // between `user` (the sender) and `chatee` (the recipient).
  c2c::Contact* chatee = new c2c::Contact(contact);
  c2c::Message*   chat = new c2c::Message(*user, *chatee);
  std::cout << "Session created successfully." << std::endl;

  // in the case of decryption, an exception is thrown if
  // the decrypting private key is not the recipient key.
  try {
    // handles the "c2c read" and "c2c write" commands
    std::string result = chat->Handle(command, message);

    // prints the ciphertext (write) or plaintext (read)
    std::cout << "Result: " << result << std::endl;
  }
  catch (Botan::Exception& e) {
    std::cerr << "Decryption failed. Must be recipient to decrypt!" << std::endl;
  }

  delete chat;
  delete chatee;
  delete user;
  return 0;
}