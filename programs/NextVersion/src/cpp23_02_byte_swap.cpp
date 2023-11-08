#include <bit>
#include "features.hpp"

namespace nextversion {
namespace cpp23 {

  // defines the run method
  int byte_swap::run() const
  {
    constexpr auto bits = std::uint16_t(0xCAFE);
    unsigned short next = std::byteswap(bits);

    if (next != std::uint16_t(0xFECA)) {
      return 1;
    }

    return 0;
  }

}
}