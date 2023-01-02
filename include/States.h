#include <iostream>
#include <map>
#include <set>
#include <vector>

class NonTerminal {
 public:
  long long number;

  NonTerminal();

  explicit NonTerminal(std::pair<char, char>);
};

bool operator<(const NonTerminal&, const NonTerminal&);

bool operator==(const NonTerminal&, const NonTerminal&);

class Terminal {
 public:
  //If EPS - number is 10
  int number = 10;

  Terminal();

  explicit Terminal(char);

  [[nodiscard]] char GetChar() const;
};

bool operator==(const Terminal&, const Terminal&);
