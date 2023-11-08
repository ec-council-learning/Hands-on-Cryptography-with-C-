// src/feature.cpp
#include "feature.hpp"

// defines the feature class constructor
nextversion::feature::feature(std::string n)
  : name(n)
{

}

// defines the feature class' run function
int nextversion::feature::run() const
{
  return 1;
}