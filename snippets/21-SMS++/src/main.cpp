// src/main.cpp
#include <iostream> // std::cout
#include <string> // std::string
#include "identity.h" // SMSpp::Identity
#include "contact.h" // SMSpp::Contact
#include "message.h" // SMSpp::Message

int main(int argc, char* argv[])
{
  // 4 options required, e.g.: `SMS write path/to/friend_ecdh.smsid.pub "My Friend"`
  auto flag = std::string(argv[1]);
  if (argc < 4 || flag == "-h" || flag == "help") {
    std::cout << "Usage: SMS [-h] <command> <friend-pubkey> <message>\n";
    return 1;
  }

  std::string command = argv[1], contact = argv[2], message = argv[3];

  // first setup the current identity (ECDH private/public key)
  std::string id_file = "data/id_ecdh.smsid";
  SMSpp::Identity* user = new SMSpp::Identity(id_file);

  // creates a ECDH ephemeral private key for communications
  // between `user` (the sender) and `chatee` (the recipient).
  SMSpp::Contact* chatee = new SMSpp::Contact(contact);
  SMSpp::Message*   chat = new SMSpp::Message(*user, *chatee);
  std::cout << "Session created successfully." << std::endl;

  try {
    // handles the "SMS read" and "SMS write" commands
    std::string result = chat->Handle(command, message);
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