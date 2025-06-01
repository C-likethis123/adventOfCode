
#include "ud_matrix.h"
#include "user_defined.h"
#include <algorithm>
#include <bitset>
#include <climits>
#include <experimental/iterator>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
/**
modification:
- brute force?? start from 1 and iterate until I get an output which is the
same... this will probably take forever. was thinking of binary search but I
don't think it'll work.

brute force takes forever...

To output a copy, I need to have:
- out instruction
- jump instruction to keep jumping to the out instruction
- terminate when it's 0???

Eg: 117440

03 -> divides, adds result to A. (A / 2^3 = 229)
54 -> outputs register A modulo 8
30 -> jumps back to 0

14680, output: 0
1835, output: 3
229, output: 5
28, output: 4
3, output: 3
0, output: 0

A: 0

last output: 0
- 03: 0*8 = 0
- 54: 0+0

second last: 3
- 03: 0*8
- 54: 3

third: 4
- 03: 3*8
- 54: 24+4 = 28

forth: 5
- 03: 28*8
- 54: 224+5=229

229*8+3

1835*8=114??? * 8




Actual input:

24
13
75
15
03
42
55 <- one output instruction here
30 <- there is only one jump operation here


for instruction 2: registers[B] = 1 % 8 -> I can't reverse this to what the value is before.



 */

using namespace std;
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T> using matrix = user_defined::matrix<T>;

enum Register { A, B, C };

vector<long> split(string s, string delimiter) {
  vector<long> v;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    if (!token.empty()) {
      v.push_back(std::stol(token));
    }
    s.erase(0, pos + delimiter.length());
  }
  v.push_back(std::stol(s));
  return v;
}

int main(int argc, const char *argv[]) {
  long ans = 0;
  string line;
  if (argc < 2) {
    cerr << "supply a file name";
    return -1;
  }
  ifstream test_case(argv[1]);
  ofstream debug("output.txt");
  vector<long> registers;
  std::smatch match;
  if (test_case.is_open()) {
    while (getline(test_case, line) && !line.empty()) {
      std::regex register_regex("Register .: (\\d+)");
      if (std::regex_search(line, match, register_regex)) {
        registers.emplace_back(stol(match[1]));
      }
    }
  }
  getline(test_case, line);
  std::regex program_regex("Program: (.+)");
  vector<long> instructions;
  int instruction_counter;

  if (std::regex_search(line, match, program_regex)) {
    instructions = split(match[1], ",");
    instruction_counter = instructions.size() - 1;
  }
  auto get_combo_operand = [&registers](int operand) -> long {
    if (operand < 4) {
      return operand;
    }
    if (operand == 4) {
      return registers[A];
    }
    if (operand == 5) {
      return registers[B];
    }
    return registers[C];
  };
  long pc = 0;
  vector<long> output;
  vector<function<void(int)>> functions({
      [&pc, &get_combo_operand, &registers](int operand) { // change
        double denominator = pow(2, get_combo_operand(operand));
        registers[A] *= (long)(denominator);
        pc += 2;
      },
      [&pc, &registers](int operand) { // not changed, how to reverse this?
        registers[B] ^= operand;
        pc += 2;
      },
      [&pc, &registers, &get_combo_operand](int operand) { // changed
        registers[B] += get_combo_operand(operand);
        pc += 2;
      },
      [&pc, &instruction_counter, &registers](int operand) { // changed
        if (instruction_counter >= 0) {
          instruction_counter--;
          pc = operand;
          cout << "instruction counter: " << instruction_counter
               << ", registers: " << registers[A] << ", " << registers[B]
               << ", " << registers[C] << endl;
        } else {
          pc += 2;
        }
      },
      [&pc, &registers](int operand) { // not changed, how to revese bitwise or?
        registers[B] ^= registers[C];
        pc += 2;
      },
      [&instructions, &instruction_counter, &pc, // changed
       &registers](int operand) {
        // ignore if it's a literal operand since it does not modify anything
        if (operand > 3) {
          registers[operand % 4] += instructions[instruction_counter];
        }
        pc += 2;
      },
      [&pc, &get_combo_operand, &registers](int operand) { // changed
        long numerator = registers[A];
        double denominator = pow(2, get_combo_operand(operand));
        registers[B] = (long)(numerator * denominator);
        pc += 2;
      },
      [&pc, &get_combo_operand, &registers](int operand) { // changed
        long numerator = registers[A];
        double denominator = pow(2, get_combo_operand(operand));
        registers[C] = (long)(numerator * denominator);
        pc += 2;
      },
  });

  registers[A] = 0;

  pc = 0;
  while (pc < instructions.size()) {
    int opcode = instructions[pc];
    int operand = instructions[pc + 1];
    (functions[opcode])(operand);
  }

  return 0;
}
