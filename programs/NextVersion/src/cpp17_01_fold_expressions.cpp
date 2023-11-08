#include "features.hpp"

namespace nextversion {
namespace cpp17 {

  template<typename... Args>
  int sum(Args&&... args)
  {
    return (args + ...);
  }

  // defines the run method
  int fold_expressions::run() const
  {
    int sum_of = sum(1, 2, 3);

    return sum_of == 6 ? 0 : 1;
  }

}
}