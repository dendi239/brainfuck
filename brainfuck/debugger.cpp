#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_set>

#include "brainfuck.hpp"
#include "io-debug.hpp"
#include "memory-debug.hpp"
#include "program-debug.hpp"

const char *kHelp = R"P(
Commands:
> h          prints this help message
> i STRING   sets input for the program
> o          prints output of program
> p PROGRAM  sets current program to PROGRAM
> j INDEX    jums execution to INDEX
> d          dumps current program state as well as memory state
> b [INDEX]  sets breakpoint at INDEX if specified, otherwise at current moment.
> n [steps]  makes one step, if steps specified, number of steps
> c          continues execution
> e          exits debugger
)P";

class Debugger {
public:
  Debugger()
      : program_(), memory_(), io_(),
        interpretator_(&memory_, &io_, &program_) {}

  void set_input(::std::string input) { io_.set_input(input); }

  ::std::string get_output() const { return io_.get_output(); }

  void set_program(::std::string program) {
    program_ = debug::Program{program};
    interpretator_ = brainfuck::Interpretator(&memory_, &io_, &program_);
  }

  void jump(size_t position) { program_.jump(position); }

  void toggle_breakpoint_now() { toggle_breakpoint(program_.now()); }

  bool tick() {
    if (!interpretator_.tick())
      return false;

    if (breakpoints_.count(program_.now()))
      return false;

    return true;
  }

  void toggle_breakpoint(size_t location) {
    if (breakpoints_.count(location)) {
      breakpoints_.erase(location);
    } else {
      breakpoints_.insert(location);
    }
  }

  void dump() {
    io_.dump();
    memory_.dump();
    program_.dump();
  }

private:
  debug::Program program_;
  debug::Memory memory_;
  debug::IO io_;

  ::std::unordered_set<size_t> breakpoints_;
  brainfuck::Interpretator interpretator_;
};

int main() {
  ::std::string command;
  ::std::stringstream output;

  Debugger debugger;

  while ((::std::cout << "> ") && ::std::getline(::std::cin, command)) {
    bool is_exit = false;

    switch (command[0]) {
    case 'i': {
      debugger.set_input(command.substr(2));
      break;
    }

    case 'o': {
      ::std::cout << debugger.get_output() << '\n';
      break;
    }

    case 'h': {
      ::std::cout << kHelp << ::std::endl;
      break;
    }

    case 'p': {
      if (command.size() <= 2) {
        ::std::cout << kHelp << ::std::endl;
        break;
      }

      // TODO: Filter program-only interface.
      debugger.set_program(command.substr(2));
      break;
    }

    case 'd': {
      debugger.dump();
      break;
    }

    case 'j': {
      size_t destination = ::std::stoi(command.data() + 2);
      debugger.jump(destination);
      break;
    }

    case 'n': {
      size_t steps = 1;
      if (command[1] == ' ') {
        steps = ::std::stoi(command.data() + 2);
      }

      while (steps-- && debugger.tick())
        ;
      break;
    }

    case 'c': {
      while (debugger.tick())
        ;
    }

    case 'e': {
      is_exit = true;
      break;
    }
    }

    if (is_exit) {
      break;
    }
  }

  return 0;
}