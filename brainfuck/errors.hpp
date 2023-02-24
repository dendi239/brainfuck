#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace brainfuck {

using ::std::string;

class Error {
public:
  virtual ~Error() = default;
  virtual string what() const = 0;
};

class RuntimeError : public Error {
public:
  virtual string cause() const = 0;

  virtual string what() const override { return "runtime error: " + cause(); }
};

class ConcreteRuntimeError : public RuntimeError {
public:
  ConcreteRuntimeError(string cause) : cause_(::std::move(cause)) {}
  ~ConcreteRuntimeError() = default;

  virtual string cause() const override { return cause_; }

private:
  string cause_;
};

class SyntaxError : public Error {
public:
  virtual string cause() const = 0;

  virtual string what() const override { return "syntax error: " + cause(); }
};

} // namespace brainfuck
