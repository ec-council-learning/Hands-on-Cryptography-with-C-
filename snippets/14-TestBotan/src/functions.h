// src/functions.h
#ifndef __TESTBOTAN_FUNCTIONS_H__
#define __TESTBOTAN_FUNCTIONS_H__

#include <string> // std::string

std::string encrypt(std::string);
std::string pem_encoded_key();
std::string whirlpool_hash(std::string);

#endif