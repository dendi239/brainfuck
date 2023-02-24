#pragma once

#include <vector>

#include "errors.hpp"
#include "io.hpp"
#include "memory.hpp"
#include "program.hpp"

namespace brainfuck {

using ::std::nullopt;

class Interpretator {
public:
  Interpretator(Memory *memory, IO *io, RandomAccessProgram *program)
  : memory_(memory), io_(io), program_(program)
  {}

  bool eval(unsigned char command) {
    // ::std::cerr << "command: '" << command << "' at " << program_->now() << ::std::endl;
    switch (command) {
      case '[': {
        cycles_.push_back(program_->now());
        // ::std::cerr << "  test loop counter on: " 
        //             << static_cast<int>(memory_->get()) 
        //             << ::std::endl;
        if (memory_->get()) {
          return true;
        }
        // ::std::cerr << "  skip loop" << ::std::endl;

        for (size_t balance = 1; balance;) {
          if (auto cmd = program_->read_command(); cmd != nullopt) {
            if (*cmd == '[') {
              ++balance;
            } else if (*cmd == ']') {
              --balance;
            }
          } else {
            throw ConcreteRuntimeError("unmactched cycle start");
          }
        }

        // ::std::cerr << "  now at " << program_->now() << ::std::endl;

        cycles_.pop_back();
        break;
      }

      case ']': {
        program_->jump(cycles_.back());
        cycles_.pop_back();
        break;
      }

      case '+': {
        memory_->inc();
        break;
      }

      case '-': {
        memory_->dec();
        break;
      }

      case '>': {
        memory_->shift_right();
        break;
      }

      case '<': {
        memory_->shift_left();
        break;
      }

      case ',': {
        memory_->set(io_->getchar());
        break;
      }

      case '.': {
        io_->putchar(memory_->get());
        break;
      }
    }

    return true;
  }

  bool tick() {
    while (true) {
      auto cmd = program_->read_command();
      if (!cmd) {
        return false;
      }

      if (eval(*cmd)) {
        return true;
      }
    }

    return false;
  }

private:
  ::std::vector<size_t> cycles_;

  Memory *memory_;
  IO *io_;
  RandomAccessProgram *program_;
};

// template <class InStream, class OutStream, class Instructions, class Memory>
// class Interpretator {
// public:
//   Interpretator(InStream &&in, OutStream &&out, Instructions instructions,
//                 Memory memory)
//       : in_stream_(in), out_stream_(out), instructions_(instructions),
//         memory_(memory) {}

//   void eval(unsigned char cmd) {
//     if (is_debug) {
//       ::std::cerr << "eval '" << cmd << "'\n";
//     }

//     switch (cmd) {
//     case '[':
//       cycles_.push_back(instructions_.now());
//       if (memory_.get()) {
//         return;
//       }

//       for (size_t balance_ = 1; balance_;) {
//         auto cmd = instructions_.read_command();

//         if (cmd == nullopt) {
//           throw ConcreteRuntimeError("unmactched cycle start");
//         }

//         if (*cmd == '[') {
//           ++balance_;
//         }

//         if (*cmd == ']') {
//           --balance_;
//         }
//       }

//       cycles_.pop_back();
//       break;

//     case ']':
//       instructions_.jump(cycles_.back());
//       cycles_.pop_back();
//       break;

//     case '+':
//       memory_.inc();
//       break;

//     case '-':
//       memory_.dec();
//       break;

//     case '<':
//       memory_.shift_left();
//       break;

//     case '>':
//       memory_.shift_right();
//       break;

//     case '.':
//       out_stream_ << memory_.get();
//       break;

//     case ',': {
//       char c;
//       if (!in_stream_.read(&c, 1)) {
//         throw ConcreteRuntimeError("failed to read symbol");
//       }
//       memory_.set(static_cast<unsigned char>(c));
//       break;
//     }

//     default:
//       break;
//     }
//   }

//   bool tick() {
//     auto command = instructions_.read_command();
//     if (command == nullopt) {
//       if (is_debug) {
//         ::std::cerr << "[interpreter] failed to read another command"
//                     << ::std::endl;
//       }

//       return false;
//     }

//     eval(*command);
//     return true;
//   }

// private:
//   bool is_debug = false;

//   InStream in_stream_;
//   OutStream out_stream_;

//   ::std::vector<size_t> cycles_;

//   Instructions instructions_;
//   Memory memory_;
// };

} // namespace brainfuck
