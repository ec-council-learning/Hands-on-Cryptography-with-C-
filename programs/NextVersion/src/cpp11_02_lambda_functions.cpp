#include "features.hpp"

namespace nextversion {
namespace cpp11 {

  // defines the run method
  int lambda_functions::run() const
  {
    auto sum_lambda = [](int a, int b) { return a+b; };
    sum_lambda(1, 1);

    return 0;
  }

}
}