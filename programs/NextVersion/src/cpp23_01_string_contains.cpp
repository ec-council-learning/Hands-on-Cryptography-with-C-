#include <string>
#include "features.hpp"

namespace nextversion {
namespace cpp23 {

  // defines the run method
  int string_contains::run() const
  {
    bool it_contains = std::string("Hi!").contains("i");
    return 0;
  }

}
}