#pragma once

#include <algorithm>
#include <array>

namespace brainfuck {

class Memory {
public:
  virtual ~Memory() = default;

  virtual void inc() = 0;
  virtual void dec() = 0;

  virtual unsigned char get() const = 0;
  virtual void set(unsigned char c) = 0;

  virtual void shift_left() = 0;
  virtual void shift_right() = 0;

  virtual void add(int diff) {
    for (int i = 0; i < diff; ++i) {
      inc();
    }
    for (int i = 0; i < -diff; ++i) {
      dec();
    }
  }

  virtual void shift(int diff) {
    for (int i = 0; i < diff; ++i) {
      shift_right();
    }
    for (int i = 0; i < -diff; ++i) {
      shift_left();
    }
  }
};

template <size_t size> class StaticMemory : public Memory {
public:
  StaticMemory() { ::std::fill(memory_.begin(), memory_.end(), 0); }

  virtual void shift_left() override {
    memory_index_-- ? 0 : memory_index_ += size;
  }
  virtual void shift_right() override {
    ++memory_index_ == size ? memory_index_ -= size : 0;
  }

  virtual void inc() override { ++memory_[memory_index_]; }
  virtual void dec() override { --memory_[memory_index_]; }

  virtual unsigned char get() const override { return memory_[memory_index_]; }
  virtual void set(unsigned char c) override { memory_[memory_index_] = c; }


  virtual void add(int diff) override {
    memory_[memory_index_] += diff;
  }

  virtual void shift(int diff) override {
    int destination = static_cast<int>(memory_index_) + diff;
    destination %= size;
    if (destination < 0) {
      destination += size;
    }
    memory_index_ = static_cast<size_t>(destination);
  }

private:
  size_t memory_index_ = 0;
  ::std::array<unsigned char, size> memory_;
};

} // namespace brainfuck
