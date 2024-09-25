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



  delete chat;
  delete chatee;
  delete user;
  return 0;
}