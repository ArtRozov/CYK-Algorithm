#include "States.h"

class Grammar {
 public:
  std::vector<NonTerminal> non_terminals;
  std::vector<Terminal> terminals;
  std::map<NonTerminal, std::vector<std::pair<NonTerminal, NonTerminal>>> non_terminal_rules;
  std::map<NonTerminal, std::vector<Terminal>> terminal_rules;
  NonTerminal start{};

  [[nodiscard]] size_t GetIndexOfNonTerminal(const NonTerminal&) const;

  [[nodiscard]] bool TerminalExist(const Terminal&) const;

  [[nodiscard]] bool NonTerminalExist(const NonTerminal&) const;

  Terminal SetTerminal(char);

  NonTerminal SetNonTerminal(std::pair<char, char>);

  void SetStart(std::pair<char, char>);

  void AddRule(const std::string&);

  void ReadGrammar();

  void PrintRules() const;
};
