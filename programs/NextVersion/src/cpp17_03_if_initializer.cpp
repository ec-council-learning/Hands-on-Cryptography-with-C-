#include "features.hpp"

namespace nextversion {
namespace cpp17 {

  // defines the run method
  int if_initializer::run() const
  {
    if (int a_number = 1; a_number == 1) {
      return 0;
    }

    return 1;
  }

}
}