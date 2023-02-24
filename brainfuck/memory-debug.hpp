#pragma once

#include <deque>
#include <iomanip>
#include <iostream>

#include "memory.hpp"
#include "utils.hpp"

namespace debug {

struct Memory : public brainfuck::Memory {
  bool is_debug = false;

  ::std::deque<unsigned char> memory{0};
  int index = 0, shift = 0;

  virtual void shift_left() override {
    if (index) {
      --index;
    } else {
      memory.push_front(0);
      ++shift;
    }
    if (!is_debug) {
      ::std::cerr << "[memory] shift to " << Index() << ::std::endl;
    }
  }

  virtual void shift_right() override {
    ++index;
    if (index == memory.size()) {
      memory.push_back(0);
    }
    if (!is_debug) {
      ::std::cerr << "[memory] shift to " << Index() << ::std::endl;
    }
  }

  virtual unsigned char get() const override {
    if (!is_debug) {
      ::std::cerr << "[memory] read " << brainfuck::HexString(memory[index]) << " at "
                  << Index() << ::std::endl;
    }

    return memory[index];
  }

  virtual void inc() override { ++memory[index]; }
  virtual void dec() override { --memory[index]; }

  virtual void set(unsigned char c) override { memory[index] = c; }

  int Index() const { return index - shift; }

  void dump(int step = 5) {
    auto old_value = is_debug;
    is_debug = true;

    for (int i = 0; i < step; ++i) {
      shift_left();
    }

    for (int i = 0; i < 2 * step + 1; ++i, shift_right()) {
      ::std::cerr << " " << brainfuck::HexString(get());
    }
    ::std::cerr << "\n";

    for (int i = 0; i < 2 * step + 1; ++i)
      shift_left();

    for (int i = 0; i < 2 * step + 1; ++i, shift_right()) {
      if (i)
        ::std::cerr << " ";
      ::std::cerr << ::std::setw(4) << Index();
    }
    ::std::cerr << ::std::endl;

    for (int i = 0; i < step + 1; ++i)
      shift_left();
    is_debug = old_value;
  }
};

} // namespace debug
