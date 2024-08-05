// src/main.cpp
#include <iostream>
#include <string>
#include "garden.h"

using BeeTransport::PrivateGarden;

int main(int argc, char* argv[])
{
  bool debug = argc >= 2 && std::string(argv[1]) == "debug";
  int flowers;
  std::cout << "How many flowers must be seeded? [1-256] ";
  if (! (std::cin >> flowers) || flowers < 1 || flowers > 256)
    flowers = 1;

  std::cout << "Now seeding a garden of " << flowers << " flowers..." << std::endl;
  auto garden = new PrivateGarden(flowers);
  garden->SetDebugMode(debug);
  garden->SeedNewFlowers();

  char choice;
  do {
    std::cout << std::endl << "Do you want to let the bees in? [Y/n] ";
    if (! (std::cin >> choice) || (choice != 'n' && choice != 'y')) choice = 'y';
    if (choice == 'n') break;

    std::cout << "Now preparing flower pollination..." << std::endl;
    garden->PrepareSafeBeeTransport();
    garden->ExecuteSafeBeeTransport();
  }
  while (choice == 'y');

  std::cout << std::endl << "Congratulations!" << std::endl
            << garden->CountFlowers() << " flowers have grown!"
            << std::endl;

  std::cout << std::endl << "Do you want to display your breeds? [Y/n] ";
  if (! (std::cin >> choice) || (choice != 'n' && choice != 'y')) choice = 'y';
  if (choice == 'y')
    std::cout << std::endl << static_cast<std::string>(*garden) << std::endl;

  std::cout << "Now destroying your private garden." << std::endl;
  delete garden;

  std::cout << "Job done." << std::endl;
  return 0;
}