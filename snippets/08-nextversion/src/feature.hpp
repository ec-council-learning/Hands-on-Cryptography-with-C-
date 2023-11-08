// src/feature.hpp
#include <string>

namespace nextversion {

  // declares the feature class
  class feature
  {
    std::string name;

    public:
      feature(std::string);

      // declares the virtual run() function
      virtual int run() const;
  };

}