#include <iostream>
#include "benchmark.h"

int main()
{
  std::cout << std::endl 
    << "Welcome to FiboBenchmark!"
    << std::endl;

  double total_duration = benchmark::run_fibonacci();

  std::cout << "Elapsed time: "
            << total_duration << "s"
            << std::endl;

  return 0;
}