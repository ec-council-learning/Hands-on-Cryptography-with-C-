#include <functional>

namespace benchmark {
  // defines a function predicate
  typedef std::function<void()> predicate_t;

  // declares the run_predicate() function
  double run_predicate(predicate_t);

}