// src/benchmark.h
#ifndef __SYMMETRYRACE_BENCHMARK_H__
#define __SYMMETRYRACE_BENCHMARK_H__
#include <chrono>
#include <functional>
#include <iostream>
#include <string>

namespace SymmetryRace {
  // shortcuts
  typedef std::chrono::steady_clock         clock_t;
  typedef std::chrono::time_point<clock_t>  time_point_t;
  typedef std::chrono::duration<double>     duration_t;

  inline std::string benchmark(
    double& out_seconds,
    std::function<std::string()> fun
  ) {
    time_point_t start = clock_t::now();
    std::string result = fun();
    time_point_t end = clock_t::now();

    duration_t elapsed_time = end - start;
    out_seconds += elapsed_time.count();

    return result;
  };
}
#endif