#include <random>

#include "brainfuck.hpp"

const char *kReadNumberTests = R"P(
+>> set first two bytes 10
>> reserve place for number of tests

,>+++++[<-->-]< read symbol minus line feed 
[
  >++++++[<------>-]<-- make it digit
  <<
   copy test number to three places to the right
     [->>>+>>+<<<<<]>>>>>[-<<<<<+>>>>>]<<<<<
    >[->>>+>>+<<<<<]>>>>>[-<<<<<+>>>>>]<<<<<<
    >>>[-<<<
      +>+<[>-<<]<[>]>  add one with overflow
      +>+<[>-<<]<[>]>  add two with overflow
      +>+<[>-<<]<[>]>  add three with overflow
      +>+<[>-<<]<[>]>  add four with overflow
      +>+<[>-<<]<[>]>  add five with overflow
      +>+<[>-<<]<[>]>  add six with overflow
      +>+<[>-<<]<[>]>  add seven with overflow
      +>+<[>-<<]<[>]>  add eight with overflow
      +>+<[>-<<]<[>]>  add nine with overflow
         >>>]<<<
    >>>>[-<<<+++++++++>>>]<<<<  add nine for top byte
  >>
  [-<<
    +>+<[>-<<]<[>]>  add one with overflow
    >>]
  ,>+++++[<-->-]< read symbol minus line feed
]
<<.>.
)P";

const char *kCountToZero = R"P(
+>> set first two bytes 10
>> reserve place for number of tests

,>+++++[<-->-]< read symbol minus line feed 
[
  >++++++[<------>-]<-- make it digit
  <<
   copy test number to three places to the right
     [->>>+>>+<<<<<]>>>>>[-<<<<<+>>>>>]<<<<<
    >[->>>+>>+<<<<<]>>>>>[-<<<<<+>>>>>]<<<<<<
    >>>[-<<<
      +>+<[>-<<]<[>]>  add one with overflow
      +>+<[>-<<]<[>]>  add two with overflow
      +>+<[>-<<]<[>]>  add three with overflow
      +>+<[>-<<]<[>]>  add four with overflow
      +>+<[>-<<]<[>]>  add five with overflow
      +>+<[>-<<]<[>]>  add six with overflow
      +>+<[>-<<]<[>]>  add seven with overflow
      +>+<[>-<<]<[>]>  add eight with overflow
      +>+<[>-<<]<[>]>  add nine with overflow
         >>>]<<<
    >>>>[-<<<+++++++++>>>]<<<<  add nine for top byte
  >>
  [-<<
    +>+<[>-<<]<[>]>  add one with overflow
    >>]
  ,>+++++[<-->-]< read symbol minus line feed
]

check if number of tests is not zero 
<<[>>+<<<]<[>]>>>
< [> +<<]<<[>]>>>
[
  [-]
  <<.>.>

  <<
   >-<[>+<<]<[>]>-  remove one with overflow
  >>

  [-]
  check if number of tests is not zero 
  <<[>>+<<<]<[>]>>>
  < [> +<<]<<[>]>>>
]
)P";

const char *kAbsolutelyInappropriateWords = R"P(
+>+>> set first three bytes 110
>> reserve place for number of tests

,>+++++[<-->-]< read symbol minus line feed 
[
  >++++++[<------>-]<-- make it digit
  <<
   copy test number to three places to the right
     [->>>+>>+<<<<<]>>>>>[-<<<<<+>>>>>]<<<<<
    >[->>>+>>+<<<<<]>>>>>[-<<<<<+>>>>>]<<<<<<
    >>>[-<<<
      +>+<[>-<<]<[>]>  add one with overflow
      +>+<[>-<<]<[>]>  add two with overflow
      +>+<[>-<<]<[>]>  add three with overflow
      +>+<[>-<<]<[>]>  add four with overflow
      +>+<[>-<<]<[>]>  add five with overflow
      +>+<[>-<<]<[>]>  add six with overflow
      +>+<[>-<<]<[>]>  add seven with overflow
      +>+<[>-<<]<[>]>  add eight with overflow
      +>+<[>-<<]<[>]>  add nine with overflow
         >>>]<<<
    >>>>[-<<<+++++++++>>>]<<<<  add nine for top byte
  >>
  [-<<
    +>+<[>-<<]<[>]>  add one with overflow
    >>]
  ,>+++++[<-->-]< read symbol minus line feed
]

check if number of tests is not zero 
<<[>>+<<<]<[>]>>> 
< [> +<<<]<<[>]>>>

[
  [-]
  <<
   >-<[>+<<]<[>]>-  remove one with overflow
  >>
  
  > reserve one bit for answer
  ,>+++++[<-->-]< read symbol minus line feed 
  [
    
    >+++++++++[-<-------->]<---- V becomes zero
    >>+<< make 01 after symbol
    
      <+>[<->>]>[<]< IF zero then flag is nonzero
      ---- if Z then now zero
      <+>[<->>]>[<]< IF zero then flag is nonzero

    [-]>>-<< clear
    ,>+++++[<-->-]< read symbol minus line feed 
  ]
  <
  
  >+<
  [[-]>[-]<
    PRINT YES
    >+++++++++[-<++++++++++>]<-.
    >++++[-<----->]<.
    >++[-<+++++++>]<.
    [-]>++[-<+++++>]<.
    [-]
  ]
  >[[-]>[-]<
    PRINT NO
    >++++++++[-<++++++++++>]<--.
    +.
    [-]>++[-<+++++>]<.
    [-]
  ]<
    
  [-]
  check if number of tests is not zero
  <<[>>+<<<]<[>]>>> 
  < [> +<<<]<<[>]>>>
]
)P";

using namespace std;

vector<bool> solve(const vector<string> &in) {
  vector<bool> ans;
  for (auto &s : in) {
    if (count(s.begin(), s.end(), 'V') || count(s.begin(), s.end(), 'Z')) {
      ans.push_back(true);
    } else {
      ans.push_back(false);
    }
  }
  return ans;
}

vector<bool> parse_yes_no(const string &s) {
  vector<bool> ans;

  stringstream ss(s);
  string c;

  while (ss >> c) {
    ans.push_back(c == "YES");
  }

  return ans;
}

string bit_str(const vector<bool> &v) {
  string ans(v.size(), '0');
  for (int i = 0; i < v.size(); ++i) {
    ans[i] += v[i];
  }
  return ans;
}

void run_test(const vector<string> &input) {
  auto in_stream = stringstream();
  in_stream << input.size() << "\n";
  for (auto s : input) {
    in_stream << s << "\n";
  }

  auto raw_out =
      brainfuck::eval(kAbsolutelyInappropriateWords, in_stream.str());

  auto expected = solve(input);
  auto actual = parse_yes_no(raw_out);

  if (expected != actual) {
    cerr << "Input: " << input.size();
    for (auto s : input) {
      cerr << " " << s;
    }
    cerr << "\n";
    cerr << "Expected: " << bit_str(expected) << "\n"
         << "  Actual: " << bit_str(actual) << "\n"
         << "     Raw: " << (int)static_cast<unsigned char>(raw_out[0]) 
         << " " << (int)static_cast<unsigned char>(raw_out[1])
         << " " << (int)static_cast<unsigned char>(raw_out[2]) << ""
         << " " << (int)static_cast<unsigned char>(raw_out[3]) << ""
         << " " << (int)static_cast<unsigned char>(raw_out[4]) << "\n"
         << (int)static_cast<unsigned char>(raw_out[5]) 
         << " " << (int)static_cast<unsigned char>(raw_out[6])
         << " " << (int)static_cast<unsigned char>(raw_out[7]) << ""
         << " " << (int)static_cast<unsigned char>(raw_out[8]) << ""
         << " " << (int)static_cast<unsigned char>(raw_out[9]) << "\n"
         << (int)static_cast<unsigned char>(raw_out[10]) 
         << " " << (int)static_cast<unsigned char>(raw_out[11])
         << " " << (int)static_cast<unsigned char>(raw_out[12]) << ""
         << " " << (int)static_cast<unsigned char>(raw_out[13]) << ""
         << " " << (int)static_cast<unsigned char>(raw_out[14]) << "\n"
        //  << " " << (int)static_cast<unsigned char>(raw_out[5]) << ""
        //  << " " << (int)static_cast<unsigned char>(raw_out[6]) << ""
        //  << " " << (int)static_cast<unsigned char>(raw_out[7]) << ""
        //  << " " << (int)static_cast<unsigned char>(raw_out[8]) << "\n"
         << raw_out << endl;
    exit(1);
  }
}

void test_read_number() {
  bool failed = false;
  for (int i = 1; i <= 10'000; ++i) {
    auto output = brainfuck::eval(kReadNumberTests, ::std::to_string(i) + "\n");

    const int low = static_cast<unsigned char>(output[0]);
    const int high =
        output.size() > 1 ? static_cast<unsigned char>(output[1]) : 0;
    if (low != (i & 255) || high != (i >> 8)) {
      std::cerr << "Failed read number\n";
      std::cerr << "    Expected: " << i << std::endl;
      std::cerr << "       Found: " << high << " >>8 | " << low << std::endl;
      failed = true;
    }
  }
  if (failed) {
    exit(1);
  }
}

void test_count_zero(int start) {
  auto output = brainfuck::eval(kCountToZero, ::std::to_string(start) + "\n");

  bool failed = false;
  for (int i = 0, target = start; i < output.size(); i += 2, --target) {
    if (static_cast<unsigned char>(output[i]) != (target & 255) ||
        static_cast<unsigned char>(output[i + 1]) != (target >> 8)) {
      failed = true;
    }
  }

  if (failed) {
    for (int i = 0, target = start; i < output.size(); i += 2, --target) {
      std::cerr << " " << target << ": "
                << (int)static_cast<unsigned char>(output[i]) << " "
                << (int)static_cast<unsigned char>(output[i + 1]) << "\n";
    }
    exit(1);
  }
}

void test_count_zero() {
  for (int i = 1; i <= 10'000; ++i) {
    test_count_zero(i);
  }
}

int main() {
  test_read_number();
  test_count_zero();

  for (auto &input : vector<vector<string>>{
           vector<string>{
               "peremoga",
               "mogiliZazia",
               "Vodka",
               "oZVerenie",
               "zvzv",
               "zVZv",
           },
       }) {
    run_test(input);
  }

  uniform_int_distribution<int> dist_len(3, 10);
  uniform_int_distribution<char> dist_ch('A', 'Z');

  for (int size = 257; size <= 10'000; ++size) {
    mt19937 rnd(size);
    vector<string> input(size);
    for (auto &s : input) {
      s.resize(dist_len(rnd));
      for (auto &c : s) {
        c = dist_ch(rnd);
      }
    }
    run_test(input);
  }
}