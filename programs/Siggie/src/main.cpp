// src/main.cpp
#include <string>
#include <iostream>
#include "getargs.h"
#include "identity.h"
#include "command.h"

int main(int argc, char* argv[])
{
  Siggie::args_t args = Siggie::parse_args(argc, argv);
  std::string file    = Siggie::get_option("file", args), buffer;

  // accepts data on stdin (e.g. `cat data/document | Siggie`)
  if (file.empty()) buffer = Siggie::consume_stdin();

  // one of file or stdin input is required
  if (file.empty() && buffer.empty()) return Siggie::print_usage();

  // passphrase input with echo suppressed
  // note: use Ctrl+D to stop input on Unix, Ctrl+Z on Windows
  std::string pass = Siggie::get_option("-p", args);
  if (pass.empty() || pass == "-") pass = Siggie::get_password();

  std::string id_file = "data/id_ecdsa";
  try {
    std::unique_ptr<Siggie::Identity> identity;
    std::filesystem::directory_entry entry{id_file};

    if (entry.exists()) identity = Siggie::make_identity(id_file, pass);
    else {
      identity = Siggie::make_identity();
      identity->Export(id_file, pass);
    }

    auto message  = Siggie::run_command(*identity, args, buffer);
    std::cout << std::endl << message << std::endl;
  }
  catch (std::runtime_error& e) {
    std::cerr << "An error ocurred: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}