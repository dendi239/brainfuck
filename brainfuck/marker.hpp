#pragma once

#include <map>

#include "memory.hpp"
#include "io.hpp"

namespace brainfuck::marker {

struct Memory : public brainfuck::Memory {
  virtual void inc() override { add(+1); }
  virtual void dec() override { add(-1); }

  virtual unsigned char get() const override { return 0; }
  virtual void set(unsigned char c) override {}

  virtual void shift_left() override { shift(-1); }
  virtual void shift_right() override { shift(+1); }

  virtual void add(int diff) override {
    diffs[index] += diff;
  }
  
  virtual void shift(int diff) override {
    index += diff;
  }

  ::std::map<int, int> diffs;
  int index = 0;
};

struct IO : public brainfuck::IO {
  virtual unsigned char getchar() {
    used = true;
    return 0;
  }

  virtual void putchar(unsigned char) {
    used = true;
  };

  bool used = false;
};

}  // namespace brainfuck::marker