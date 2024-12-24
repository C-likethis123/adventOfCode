#include "ud_matrix.h"
#include "user_defined.h"
#include <algorithm>
#include <bitset>
#include <climits>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <experimental/iterator>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
/**
Data structures:
- registers (an array of values?)


1. initialise program values
2. parse instructions as an int vector
3. calculate operand and opcode
4. each opcode corresponds to a function that would:
- read/modify register value
- output


 */



using namespace std;
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

template <typename T> using matrix = user_defined::matrix<T>;

enum Register {
  A,
  B,
  C
};

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
  if (test_case.is_open()) {
    vector<long> registers;
    std::smatch match;
    while (getline(test_case, line) && !line.empty()) {
      std::regex register_regex("Register .: (\\d+)");
      if (std::regex_search(line, match, register_regex)) {
        registers.emplace_back(stol(match[1]));
      }
    }
    getline(test_case, line);
    std::regex program_regex("Program: (.+)");
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
    vector<int> output;
    vector<function<void(int)>> functions({
      [&pc, &get_combo_operand, &registers](int operand) {
        long numerator = registers[A];
        double denominator = pow(2, get_combo_operand(operand));
        registers[A] = (long) (numerator / denominator);
        pc += 2;
      },
      [&pc, &registers](int operand) {
        registers[B] ^= operand;
        pc += 2;
      },
      [&pc, &registers, &get_combo_operand](int operand) {
        registers[B] = get_combo_operand(operand)% 8;
        pc += 2;
      },
      [&pc, &registers](int operand) {
        if (registers[A] != 0) {
          pc = operand;
        } else {
          pc += 2;
        }
      },
      [&pc, &registers](int operand) {
        registers[B] ^= registers[C];
        pc += 2;
      },
      [&output, &pc, &get_combo_operand, &registers](int operand) {
        output.emplace_back(get_combo_operand(operand) % 8);
        pc += 2;
      },
      [&pc, &get_combo_operand, &registers](int operand) {
        long numerator = registers[A];
        double denominator = pow(2, get_combo_operand(operand));
        registers[B] = (long) (numerator / denominator);
        pc += 2;
      },
      [&pc, &get_combo_operand, &registers](int operand) {
        long numerator = registers[A];
        double denominator = pow(2, get_combo_operand(operand));
        registers[C] = (long) (numerator / denominator);
        pc += 2;
      },
    });
    if (std::regex_search(line, match, program_regex)) {
      vector<long> instructions = split(match[1], ",");
      while (pc < instructions.size()) {
        int opcode = instructions[pc];
        int operand = instructions[pc+1];
        (functions[opcode])(operand);
      }
    }
    // from: https://stackoverflow.com/questions/3496982/how-can-i-print-a-list-of-elements-separated-by-commas/3497021#3497021
    std::copy(std::begin(output),
              std::end(output),
              std::experimental::make_ostream_joiner(std::cout, ","));
  }
  return 0;
}
