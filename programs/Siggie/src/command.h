// src/command.h
#ifndef __SIGGIE_COMMAND_H__
#define __SIGGIE_COMMAND_H__

#include <map> // std::map
#include <string> // std::string
#include <functional> // std::function
#include <memory> // std::unique_ptr
#include <iostream> // std::cout
#include "identity.h"
#include "getargs.h"

namespace Siggie {

  /// \brief Wrapper class to execute commands with Siggie
  template <typename ReturnType, typename... ArgsType>
  class Command {
  public:
    std::string name;
    std::function<ReturnType (ArgsType...)> handle_fn;

    Command(const std::string& n, std::function<ReturnType (ArgsType...)> f)
      : name(n), handle_fn(f) {}

    virtual ~Command() {}
  };

  /// \brief SignCommand return a std::string and accepts \a doc_file,
  ///        \a sig_file and an optional \a buffer.
  typedef Command<std::string, std::string, std::string, std::string> SignCommand;

  /// \brief VerifyCommand return a bool and accepts accepts \a doc_file,
  ///        \a sig_file and an optional \a buffer.
  typedef Command<bool, std::string, std::string, std::string> VerifyCommand;

  /// \brief Factory function for the SignCommand instance with \a identity
  std::unique_ptr<SignCommand> make_sign_command(const Identity&);

  /// \brief Factory function for the VerifyCommand instance with \a identity
  std::unique_ptr<VerifyCommand> make_verify_command(const Identity&);

  /// \brief Helper function to create and run one of the above commands using
  ///        the keypair \a identity, options \a args and an optional \a buffer.
  std::string run_command(const Identity&, Siggie::args_t, const std::string&);

  /// \brief Prints the usage information for the Siggie software
  int print_usage();
}

#endif