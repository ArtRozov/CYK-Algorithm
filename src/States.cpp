#include "../include/States.h"

NonTerminal::NonTerminal() = default;

NonTerminal::NonTerminal(std::pair<char, char> pair) {
  number = pair.first - 'A' + 100 * (pair.second + 1 - '0');
}

bool operator<(const NonTerminal& first, const NonTerminal& second) {
  return first.number < second.number;
}

bool operator==(const NonTerminal& first, const NonTerminal& second) {
  return first.number == second.number;
}

Terminal::Terminal() { number = 10; };

Terminal::Terminal(char c) { number = int(c); }

[[nodiscard]] char Terminal::GetChar() const { return char(number); }

bool operator==(const Terminal& first, const Terminal& second) {
  return first.number == second.number;
}
