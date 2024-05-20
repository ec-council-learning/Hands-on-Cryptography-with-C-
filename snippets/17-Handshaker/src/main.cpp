// src/main.cpp
#include <iostream>
#include <string>
#include "channel.h"

using Handshaker::HandshakeOnlyChannel;

int main(int argc, char* argv[])
{
  bool debug = argc >= 2 && std::string(argv[1]) == "debug";

  std::cout << "Now preparing a TLS v1.3 connection..." << std::endl;
  auto channel = new HandshakeOnlyChannel("evi.as", 443);
  channel->SetDebugMode(debug);

  std::cout << "Now creating a TLS connection handshake with evi.as:443..." << std::endl;
  channel->TryHandshakeWithServer();
                 
  delete channel;
  std::cout << "Connection closed with evi.as:443." << std::endl;
  std::cout << "Job done." << std::endl;
  return 0;
}