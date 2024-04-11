// src/main.cpp
#include <iostream> // std::cout, std::getline
#include <string> // std::string
#include "factory.h" // Factory

int main()
{
  std::string curve, priv, pub, sig;
  std::cout << "Which curve would you like to use today? [ed25519|secp256|pkcs1]: ";
  std::getline(std::cin, curve);

  CurvyPP::Factory factory;
  if (std::string::npos != curve.find("secp256")) {
    auto keypair = factory.CreateSecp256();
    priv = keypair->GetPrivateKey(); pub = keypair->GetPublicKey();
    sig  = keypair->Sign("Hello, Curvy++!");
    delete keypair;
  }
  else if (std::string::npos != curve.find("pkcs1")) {
    auto keypair = factory.CreatePKCS1();
    priv = keypair->GetPrivateKey(); pub = keypair->GetPublicKey();
    sig  = keypair->Sign("Hello, Curvy++!");
    delete keypair;
  }
  else {
    auto keypair = factory.CreateEd25519();
    priv = keypair->GetPrivateKey(); pub = keypair->GetPublicKey();
    sig  = keypair->Sign("Hello, Curvy++!");
    delete keypair;
  }

  std::cout << "Private Key: " << priv << std::endl
    << "Public Key:  " << pub << std::endl
    << "Signature:   " << std::endl << sig << std::endl;
  return 0;
}