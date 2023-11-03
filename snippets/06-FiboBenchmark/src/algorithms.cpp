#include "algorithms.h"

unsigned long int my_algorithms::fibonacci(unsigned int number)
{
  if (number < 2) {
    return number;
  }

  return fibonacci(number - 1) + fibonacci(number - 2);
}