#include <map>
#include <atomic>
#include "feature.hpp"

namespace nextversion {
  // declares a feature registry type (by name)
  typedef std::map<std::string, feature> feature_registry_t;

  namespace cpp11 {

    // declares a feature class
    class variadic_templates: public feature
    {
      public:
        variadic_templates()
          : feature("Variadic Templates")
        {}

        // declares the run() function overload
        int run() const;
    };

    // declares a feature class
    class lambda_functions: public feature
    {
      public:
        lambda_functions()
          : feature("Lambda Functions")
        {}

        // declares the run() function overload
        int run() const;
    };

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
    class fold_expressions: public feature
    {
      public:
        fold_expressions()
          : feature("Fold Expressions")
        {}

        // declares the run() function overload
        int run() const;
    };

    // defines an inline variable
    inline std::atomic<int> counter(0);

    // declares a feature class
    class inline_variables: public feature
    {
      public:
        inline_variables()
          : feature("Inline Variables")
        {}

        // declares the run() function overload
        int run() const;
    };

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

  namespace cpp20 {

    // declares a feature class
    class feature_tests: public feature
    {
      public:
        feature_tests()
          : feature("Feature Tests")
        {}

        // declares the run() function overload
        int run() const;
    };

    // declares a feature class
    class threeway_operator: public feature
    {
      public:
        threeway_operator()
          : feature("Three-way comparison")
        {}

        // declares the run() function overload
        int run() const;
    };

    // declares a feature class
    class utf8_compat: public feature
    {
      public:
        utf8_compat()
          : feature("UTF-8 Characters")
        {}

        // declares the run() function overload
        int run() const;
    };

  }

  namespace cpp23 {

    // declares a feature class
    class string_contains: public feature
    {
      public:
        string_contains()
          : feature("UTF-8 Characters")
        {}

        // declares the run() function overload
        int run() const;
    };

    // declares a feature class
    class byte_swap: public feature
    {
      public:
        byte_swap()
          : feature("UTF-8 Characters")
        {}

        // declares the run() function overload
        int run() const;
    };

  }

}