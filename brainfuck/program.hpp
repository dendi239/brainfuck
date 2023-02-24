#pragma once

#include <optional>
#include <vector>

namespace brainfuck {

using ::std::nullopt;
using ::std::optional;

class Program {
public:
  virtual ~Program() = default;
  virtual optional<unsigned char> read_command() = 0;
};

class RandomAccessProgram : public Program {
public:
  virtual void jump(size_t destination) = 0;
  virtual size_t now() const = 0;
};

template <class ProgramStream> class InstructionsStream : public RandomAccessProgram {
public:
  InstructionsStream(ProgramStream program_stream)
      : program_stream_(program_stream) {}

  virtual void jump(size_t destination) override { program_index_ = destination; }

  virtual size_t now() const override { return program_index_ - 1; }

  virtual optional<unsigned char> read_command() override {
    if (program_index_ < commands_.size()) {
      return commands_[program_index_++];
    }

    unsigned char c;
    if (!(program_stream_ >> c)) {
      return nullopt;
    }

    commands_.push_back(c);
    return commands_[program_index_++];
  }

private:
  ProgramStream program_stream_;

  size_t program_index_ = 0;
  ::std::vector<unsigned char> commands_;
};

} // namespace brainfuck
