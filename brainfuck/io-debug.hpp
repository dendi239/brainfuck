#include <ostream>

#include "io.hpp"

namespace debug {

class IO : public brainfuck::IO {
public:
  IO() = default;
  explicit IO(::std::string input) : input_(::std::move(input)) {}

  void putchar(unsigned char c) override {
    input_.push_back(static_cast<char>(c));
  }

  unsigned char getchar() override {
    return static_cast<unsigned char>(input_[cursor_++]);
  }

  void set_input(::std::string input) {
    input_ = input;
    cursor_ = 0;
  }

  ::std::string get_output() const { return output_; }

  void dump() {
    const ::std::string input_pref = "Input: \"";
    const ::std::string output_pref = "Output: \"";
    ::std::cerr << input_pref << input_ << "\"\n"
                << ::std::string(input_pref.size() + cursor_, ' ') << "^\n"
                << output_pref << output_ << "\"\n";
  }

private:
  ::std::string input_;
  ::std::string output_;
  int cursor_ = 0;
};

} // namespace debug
