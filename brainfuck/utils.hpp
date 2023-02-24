#pragma once

#include <string>

namespace brainfuck {

inline char HexDigit(int value) {
  if (value >= 10) {
    return 'A' + value - 10;
  } else {
    return '0' + value;
  }
}

inline ::std::string HexString(unsigned char c) {
  char s[] = "0x00";
  s[2] = HexDigit(c >> 4);
  s[3] = HexDigit(c & 15);
  return s;
}

}  // namespace brainfuck
