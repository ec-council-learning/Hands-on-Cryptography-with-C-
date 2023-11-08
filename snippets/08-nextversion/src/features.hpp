// src/features.hpp
#include <map>
#include "feature.hpp"

namespace nextversion {
  // declares a feature registry type (by name)
  typedef std::map<std::string, feature*> feature_registry_t;

  namespace cpp11 {

    // declares a feature class
    class auto_keyword: public feature
    {
      public:
        auto_keyword()
          : feature("Keyword auto")
        {}

        // declares the run() function overload
        int run() const;
    };

  }

  namespace cpp17 {

    // declares a feature class
    class if_initializer: public feature
    {
      public:
        if_initializer()
          : feature("If/Switch Initializer")
        {}

        // declares the run() function overload
        int run() const;
    };

  }
}