#include "features.hpp"

namespace nextversion {
namespace cpp20 {

  // defines the run method
  int feature_tests::run() const
  {
    int counter = 0;

#ifdef __cpp_impl_three_way_comparison
      ++counter;
#endif

#ifdef __cpp_designated_initializers
      ++counter;
#endif

    return counter == 2 ? 0 : 1;
  }

}
}