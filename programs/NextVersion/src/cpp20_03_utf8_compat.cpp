#include <string>
#include "features.hpp"

namespace nextversion {
namespace cpp20 {

  // defines the run method
  int utf8_compat::run() const
  {
    std::u8string utf8_sz1 = u8"A",
                  utf8_sz2 = u8"👋";

    return 0;
  }

}
}