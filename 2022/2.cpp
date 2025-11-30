#include <array>
#include <fstream>
#include <iostream>
#include <scn/scan.h>
#include <stdexcept>
#include <string>

using namespace std;

enum Choice { ROCK = 1, PAPER = 2, SCISSORS = 3 };
enum Outcome { LOSE = 0, DRAW = 3, WIN = 6 };

Choice char_to_choice(char c) {
  switch (c) {
  case 'A':
  case 'X':
    return ROCK;
  case 'B':
  case 'Y':
    return PAPER;
  case 'C':
  case 'Z':
    return SCISSORS;
  default:
    throw invalid_argument("Invalid choice");
  }
}

Outcome determine_outcome(char c) {
  switch (c) {
  case 'X':
    return Outcome::LOSE;
  case 'Y':
    return Outcome::DRAW;
  case 'Z':
    return Outcome::WIN;
  default:
    throw invalid_argument("Invalid outcome");
  }
}

Choice determine_choice_from_outcome(Choice opponent, Outcome outcome) {
  switch (outcome) {
  case Outcome::WIN:
    return static_cast<Choice>((opponent + 1) % 3);
  case Outcome::DRAW:
    return opponent;
  case Outcome::LOSE:
    return static_cast<Choice>((opponent + 2) % 3);
  }
}

// Simplified winner determination using modular arithmetic
// Rock beats Scissors, Paper beats Rock, Scissors beats Paper
// WIN if (player - opponent + 3) % 3 == 1
int calculate_score(Choice opponent, Choice player) {
  Outcome outcome_score = Outcome::LOSE;

  if (opponent == player) {
    outcome_score = Outcome::DRAW;
  } else if ((player - opponent + 3) % 3 == 1) {
    outcome_score = Outcome::WIN;
  }

  return player + outcome_score;
}

long compute_part_1(char opponent_char, char player_char) {
  const Choice opponent = char_to_choice(opponent_char);
  const Choice player = char_to_choice(player_char);
  return calculate_score(opponent, player);
}

long compute_part_2(char opponent_char, char outcome_char) {
  const Choice opponent = char_to_choice(opponent_char);
  const Outcome outcome = determine_outcome(outcome_char);
  const Choice player = determine_choice_from_outcome(opponent, outcome);
  return player + 1 + outcome;
}

int main() {
  ifstream test_case("input_2.txt");
  if (!test_case.is_open()) {
    cerr << "Error: Cannot open input_2.txt" << endl;
    return 1;
  }

  string line;
  long part1 = 0;
  long part2 = 0;

  while (getline(test_case, line)) {
    if (auto result = scn::scan<char, char>(line, "{} {}")) {
      const auto [opponent_char, player_char] = result->values();
      part1 += compute_part_1(opponent_char, player_char);
      part2 += compute_part_2(opponent_char, player_char);
    }
  }

  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2 << endl;
  return 0;
}
