#pragma once

#include <sstream>

#include "interpreter.hpp"
#include "io.hpp"
#include "memory.hpp"
#include "program-debug.hpp"
#include "program.hpp"
#include "tree.hpp"

namespace brainfuck {

inline string eval(string program, string input) {
  std::stringstream in_stream(input), out_stream;
  auto io = StreamIO<std::stringstream &, std::stringstream &>(in_stream, out_stream);
  auto program_ = debug::Program(program);
  auto memory = StaticMemory<1'000'000>();
  
  auto interpretator = tree::Interpretator(&memory, &io, &program_);
  while (interpretator.tick())
    ;

  return out_stream.str();
}

}  // namespace brainfuck
