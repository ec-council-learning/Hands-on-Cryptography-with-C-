// src/getargs.h
#ifndef __SIGGIE_GETARGS_H__
#define __SIGGIE_GETARGS_H__

#include <iostream>
#include <fstream>
#include <map>

#if defined(WIN32) || defined(_WIN32)
  #include <windows.h> // GetStdHandle
#elif defined(__unix__) || defined(__APPLE__)
  #include <termios.h> // termios
  #include <unistd.h> // STDIN_FILENO
  #include <iosfwd> // fileno
#endif

namespace Siggie {

  typedef std::map<std::string, std::string> args_t;

  inline args_t parse_args(int argc, char* argv[]) {
    args_t args{};
    for (int i = 0; i < argc; i++) {
      if (i == 0) args.emplace("program", std::string(argv[i]));
      else if (argv[i][0] == '-') {
        // value options
        if (argc >= i+2) {
          args.emplace(std::string(argv[i]), std::string(argv[i+1]));
          i++; // force skip value
        }
        // flags
        else args.emplace(std::string(argv[i]), "1");
      }
      else if (args.end() == args.find("file")) {
        args.emplace("file", std::string(argv[i]));
      }
      else /* <sig_file> */ {
        args.emplace("sig_file", std::string(argv[i]));
      }
    }

    return args;
  }

#if defined(WIN32) || defined(_WIN32)
  inline const char* get_platform_stdin() {
    return "CONIN$";
  }

  inline DWORD supress_echo() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    return mode; // <- old mode
  }

  inline void cleanup_echo(DWORD mode) {
    SetConsoleMode(hStdin, mode);
  }
#elif defined(__unix__) || defined(__APPLE__)
  inline const char* get_platform_stdin() {
    return "/dev/tty";
  }

  inline termios supress_echo() {
    std::FILE* fp = std::fopen(get_platform_stdin(), "r");
    termios oldt;
    tcgetattr(fileno(fp), &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(fileno(fp), TCSANOW, &newt);
    std::fclose(fp);
    return oldt;
  }

  inline void cleanup_echo(termios mode) {
    std::FILE* fp = std::fopen(get_platform_stdin(), "r");
    tcsetattr(fileno(fp), TCSANOW, &mode);
    std::fclose(fp);
  }
#endif

  inline std::string consume_stdin() {
    std::string temp, out;
    while (std::getline(std::cin >> std::ws, temp))
      out += temp + "\n";
    std::cin.clear();
    return out;
  }

  inline std::string get_buffered_input() {
    std::ifstream term(get_platform_stdin());
    std::streambuf* old_buffer;
    std::string in;

    old_buffer = std::cin.rdbuf(term.rdbuf());
    std::getline(std::cin >> std::ws, in);
    if (old_buffer) std::cin.rdbuf(old_buffer);
    term.close();

    return in;
  }

  inline std::string get_password() {
    std::cout << "Enter your password: " << std::flush;

    auto old = supress_echo();
    std::string in = get_buffered_input();
    cleanup_echo(old);

    return in;
  }

  inline std::string get_option(const std::string& arg, args_t args) {
    auto find_it = args.find(arg);
    if (args.end() == find_it)
      return "";

    return (*find_it).second;
  }
}

#endif