// src/main.cpp
#include <iostream>
#include <string>
#include <memory>
#include "factory.h"

int main()
{
  CurvyPP::Factory factory;
  std::string curve, priv, pub, sig;
  std::cout << "Which curve would you like to use today? [ed25519|secp256|pkcs1]: ";
  std::getline(std::cin, curve);

  // generates a random keypair using factory
  if (std::string::npos != curve.find("secp256")) {
    auto keypair = factory.CreateSecp256();
    priv = keypair->GetPrivateKey();
    pub  = keypair->GetPublicKey();
    sig  = keypair->Sign("Hello, Curvy++!");
    delete keypair;
  }
  else if (std::string::npos != curve.find("pkcs1")) {
    auto keypair = factory.CreatePKCS1();
    priv = keypair->GetPrivateKey();
    pub  = keypair->GetPublicKey();
    sig  = keypair->Sign("Hello, Curvy++!");
    delete keypair;
  }
  else {
    auto keypair = factory.CreateEd25519();
    priv = keypair->GetPrivateKey();
    pub  = keypair->GetPublicKey();
    sig  = keypair->Sign("Hello, Curvy++!");
    delete keypair;
  }

  // displays information about the key and signature
  std::cout
    << "Private Key: " << priv << std::endl
    << "Public Key:  " << pub << std::endl
    << "Signature:   " << std::endl << sig
    << std::endl;
  return 0;
}