#pragma once

#include <iostream>
#include <optional>
#include <string>

#include "program.hpp"

namespace debug {

class Program : public brainfuck::RandomAccessProgram {
public:
  Program() = default;
  Program(::std::string program) : program(::std::move(program)) {}

  ::std::string program;
  size_t index = 0;

  virtual size_t now() const override { return index; }
  virtual void jump(size_t destination) override { index = destination; }

  void dump() const {
    ::std::cerr << program << "\n";
    ::std::cerr << ::std::string(index, ' ') << "^" << ::std::endl;
  }

  virtual ::std::optional<unsigned char> read_command() override {
    if (index == program.size()) {
      return ::std::nullopt;
    }
    return program[index++];
  }
};

} // namespace debug
