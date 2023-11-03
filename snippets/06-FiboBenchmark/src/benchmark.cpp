#include <chrono>
#include "benchmark.h"
#include "algorithms.h"

namespace benchmark {

  // shortcuts
  using std::chrono::duration;
  using std::chrono::time_point;
  using std::chrono::steady_clock;

  double run_fibonacci() {
    // start a chronometer
    time_point<steady_clock> start = steady_clock::now();

    // execute the fibonacci backwards sum
    unsigned long int fb = my_algorithms::fibonacci(42);

    // stop the chronometer
    time_point<steady_clock> end = steady_clock::now();

    // compute elapsed time
    duration<double> elapsed_seconds = end - start;
    return elapsed_seconds.count();
  }
}