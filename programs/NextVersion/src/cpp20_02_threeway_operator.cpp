#include "features.hpp"

namespace nextversion {
namespace cpp20 {

  // defines the run method
  int threeway_operator::run() const
  {
    int a = 1,
        b = 2,
        c = 3;

    auto is_smaller_fn = [] (int a, int b) -> bool {
      return (a <=> b) < 0;
    };

    auto is_greater_fn = [] (int a, int b) {
      return (a <=> b) > 0;
    };

    auto is_equal_fn = [] (int a, int b) {
      return (a <=> b) == 0;
    };

    return is_smaller_fn(a, b) && is_greater_fn(c, b)
      ? 0
      : 1;
  }

}
}