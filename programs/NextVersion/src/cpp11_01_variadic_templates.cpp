#include "features.hpp"

namespace nextversion {
namespace cpp11 {

  template <typename... args_pack_t>
  class store_anything
  {};

  // declares the variadic template class
  template <typename tail_arg_t, typename... args_pack_t>
  class store_anything<tail_arg_t, args_pack_t...>
    : store_anything<args_pack_t...>
  {
    tail_arg_t tail;

    public:
      // defines the constructor with pack expansion
      store_anything(tail_arg_t arg, args_pack_t... args)
        : store_anything<args_pack_t...>(args...), tail(arg) // forward
      {}
  };

  // defines the run method
  int variadic_templates::run() const
  {
    store_anything<const char*, int, bool> obj1("A message coupled to a number and a boolean", 1, false);
    store_anything<const char*, int, int, int, int, bool, long, const char*, char> obj2("Another message", 1, 2, 3, 4, true, NULL, "END", '!');

    return 0;
  }

}
}