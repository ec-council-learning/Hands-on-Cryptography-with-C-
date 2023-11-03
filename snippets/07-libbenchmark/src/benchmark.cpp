#include <chrono>
#include "benchmark.h"

namespace benchmark {

  // shortcuts
  using std::chrono::duration;
  using std::chrono::time_point;
  using std::chrono::steady_clock;

  // defines the run_predicate function
  double run_predicate(predicate_t fun) {
    // start a chronometer
    time_point<steady_clock> start = steady_clock::now();

    // execute the function predicate
    fun();

    // stop the chronometer
    time_point<steady_clock> end = steady_clock::now();

    // compute elapsed time
    duration<double> elapsed_seconds = end - start;
    return elapsed_seconds.count();
  }

}