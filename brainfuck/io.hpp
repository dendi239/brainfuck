#pragma once

#include <iostream>

#include "errors.hpp"

namespace brainfuck {

class IOError : public ConcreteRuntimeError {
public:
  IOError(string cause) : ConcreteRuntimeError(::std::move(cause)) {}
};

class IO {
public:
  virtual ~IO() = default;

  virtual unsigned char getchar() = 0;
  virtual void putchar(unsigned char c) = 0;
};

template <class InStream, class OutStream>
class StreamIO : public IO {
public:
  StreamIO(InStream in_stream, OutStream out_stream) 
  : in_stream_(in_stream), out_stream_(out_stream)
  {}

  virtual unsigned char getchar() override {
    char c;
    if (!in_stream_.read(&c, 1)) {
      throw IOError("failed to read symbol");
    }
    return static_cast<unsigned char>(c);    
  }

  virtual void putchar(unsigned char c) override {
    out_stream_ << static_cast<char>(c);
  }

private:
  InStream in_stream_;
  OutStream out_stream_;
};

inline StreamIO<::std::istream &, ::std::ostream &> default_io(){
  return StreamIO<::std::istream &, ::std::ostream &>(
    ::std::cin, ::std::cout);
}

}  // namespace brainfuck
