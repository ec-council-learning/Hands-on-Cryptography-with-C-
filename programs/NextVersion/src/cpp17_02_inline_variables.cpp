#include "features.hpp"

namespace nextversion {
namespace cpp17 {

  // defines the run method
  int inline_variables::run() const
  {
    auto double_increment = [] () {
      nextversion::cpp17::counter++;
      nextversion::cpp17::counter++;
    };

    double_increment();
    return 2 == nextversion::cpp17::counter ? 0 : 1;
  }

}
}