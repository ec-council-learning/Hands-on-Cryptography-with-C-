#include <iostream>
#include "benchmark.h"
#include "algorithms.h"

int main()
{
    std::cout
        << std::endl 
        << "Welcome to FiboWithLib!"
        << std::endl;

    double total_duration = benchmark::run_predicate([] () -> void {
        my_algorithms::fibonacci(42);
    });

    std::cout << "Elapsed time: "
              << total_duration << "s"
              << std::endl;

    return 0;
}