#include <deque>
#include <fstream>
#include <iostream>

#include "brainfuck.hpp"

constexpr const int kIterationLimit = 1'000'000'000;

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    ::std::cerr << "Usage: BRAINFUCK SOURCE" << ::std::endl;
    return 1;
  }

  auto memory = brainfuck::StaticMemory<1'000'000>();
  auto program_stream = ::std::fstream(argv[1]);
  auto program =
      brainfuck::InstructionsStream<::std::fstream &>(program_stream);

  auto io = brainfuck::default_io();
  auto interpretator = brainfuck::tree::Interpretator(
    &memory, &io, &program);

  try {
    size_t step = 0;

    for (step = 0; step < kIterationLimit && interpretator.tick(); ++step)
      ;

    if (step >= kIterationLimit) {
      return 1;
    }

    ::std::cerr << "ticks: " << step << ::std::endl;
  } catch (brainfuck::Error &exception) {
    ::std::cerr << exception.what() << ::std::endl;
    return 1;
  }

  return 0;
}
