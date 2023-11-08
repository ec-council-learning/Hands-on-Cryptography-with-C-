#include <iostream>
#include <memory>
#include "utils.hpp"
#include "features.hpp"

// defines shortcut types for the registry
typedef std::map<int, nextversion::feature*> registry_t;
typedef std::map<int, nextversion::feature*>::iterator registry_iter_t;

// defines shortcut types for feature test classes
typedef nextversion::cpp11::variadic_templates cpp11_feature_1_t;
typedef nextversion::cpp11::lambda_functions cpp11_feature_2_t;
typedef nextversion::cpp11::auto_keyword cpp11_feature_3_t;
typedef nextversion::cpp17::fold_expressions cpp17_feature_1_t;
typedef nextversion::cpp17::inline_variables cpp17_feature_2_t;
typedef nextversion::cpp17::if_initializer cpp17_feature_3_t;
typedef nextversion::cpp20::feature_tests cpp20_feature_1_t;
typedef nextversion::cpp20::threeway_operator cpp20_feature_2_t;
typedef nextversion::cpp20::utf8_compat cpp20_feature_3_t;
typedef nextversion::cpp23::string_contains cpp23_feature_1_t;
typedef nextversion::cpp23::byte_swap cpp23_feature_2_t;

// defines a feature registry (by number)
registry_t feature_ids = {
  { 1, new cpp11_feature_1_t() },
  { 2, new cpp11_feature_2_t() },
  { 3, new cpp11_feature_3_t() },
  { 4, new cpp17_feature_1_t() },
  { 5, new cpp17_feature_2_t() },
  { 6, new cpp17_feature_3_t() },
  { 7, new cpp20_feature_1_t() },
  { 8, new cpp20_feature_2_t() },
  { 9, new cpp20_feature_3_t() },
  { 10, new cpp23_feature_1_t() },
  { 11, new cpp23_feature_2_t() },
};

int main()
{
    int value;
    std::string input;

    do {
      // display a menu
      std::cout << "Choose one of the feature tests: " << std::endl
                << "[1] Variadic templates (c++11)" << std::endl
                << "[2] Lambda functions   (c++11)" << std::endl
                << "[3] The auto variable  (c++11)" << std::endl
                << "[4] Fold expressions   (c++17)" << std::endl
                << "[5] Inline variables   (c++17)" << std::endl
                << "[6] If initializers    (c++17)" << std::endl
                << "[7] Feature tests      (c++20)" << std::endl
                << "[8] Three-way Operator (c++20)" << std::endl
                << "[9] UTF-8 Characters   (c++20)" << std::endl
                << "[10] string.contains() (c++23)" << std::endl
                << "[11] Swapping bytes    (c++23)" << std::endl
                << "[0] Quit program" << std::endl
                << "Enter a number (0-11): ";
      value = nextversion::getnumber(std::cin, 0, 11);

      if (value == 0) {
        std::cout << std::endl << "See you soon." << std::endl;
        return 0;
      }

      // find the corresponding feature test implementation
      registry_iter_t it = feature_ids.find(value);
      if (it == feature_ids.end()) {
        std::cout << "Feature test not yet implemented." << std::endl;
        return 1;
      }

      // execute the feature test
      int result = (it->second)->run();
      std::cout << "Feature test result: "
                << (result == 0 ? "[OK]" : "Error")
                << std::endl
                << std::endl;

      // ask whether to continue or quit
      input = "";
      std::cout << "Do you want to continue? [y/N] ";
      std::ws(std::cin);
      std::getline(std::cin, input);
      std::cout << std::endl;
    }
    while (input[0] == 'y' || input[0] == 'Y');

    return 0;
}