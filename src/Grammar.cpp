#include "../include/Grammar.h"

[[nodiscard]] size_t Grammar::GetIndexOfNonTerminal(const NonTerminal& non_terminal) const {
  for (size_t i = 0; i < non_terminals.size(); ++i) {
    if (non_terminal == non_terminals[i]) { return i; }
  }
  return non_terminals.size();
}

[[nodiscard]] bool Grammar::TerminalExist(const Terminal& term) const {
  for (auto& terminal: terminals) {
    if (term == terminal) { return true; }
  }
  return false;
}

[[nodiscard]] bool Grammar::NonTerminalExist(const NonTerminal& term) const {
  for (auto& non_terminal: non_terminals) {
    if (term == non_terminal) { return true; }
  }
  return false;
}

Terminal Grammar::SetTerminal(char c) {
  Terminal term(c);
  if (!TerminalExist(term)) { terminals.push_back(term); }
  return term;
}

NonTerminal Grammar::SetNonTerminal(std::pair<char, char> pair) {
  NonTerminal non_term(pair);
  if (!NonTerminalExist(non_term)) { non_terminals.push_back(non_term); }
  return non_term;
}

void Grammar::SetStart(std::pair<char,char> pair) {
  start = SetNonTerminal(pair);
}

void Grammar::AddRule(const std::string& input_str) {
  std::string state;
  std::string str = input_str + '|';
  NonTerminal begin{};
  for (size_t i = 0; i < str.length(); ++i) {
    if (str[i] == '-') {
      if (state.length() == 1) { begin = SetNonTerminal(std::make_pair(state[0], '0' - 1)); }
      else { begin = SetNonTerminal(std::make_pair(state[0], state[1])); }
      i += 1;
      state.clear();
    } else if (str[i] == '|') {
      if (state.length() == 1) {
        Terminal term = SetTerminal(state[0]);
        terminal_rules[begin].push_back(term);
      } else if (state == "EPS") {
        Terminal term = SetTerminal(10);
        terminal_rules[begin].push_back(term);
      } else {
        NonTerminal first{};
        NonTerminal second{};
        if (state.length() == 2) {
          first = SetNonTerminal(std::make_pair(state[0], '0' - 1));
          second = SetNonTerminal(std::make_pair(state[1], '0' - 1));
        } else if (state.length() == 4) {
          first = SetNonTerminal(std::make_pair(state[0], state[1]));
          second = SetNonTerminal(std::make_pair(state[2], state[3]));
        } else {
          if ('A' <= state[1] && state[1] <= 'Z') {
            first = SetNonTerminal(std::make_pair(state[0], '0' - 1));
            second = SetNonTerminal(std::make_pair(state[1], state[2]));
          } else {
            first = SetNonTerminal(std::make_pair(state[0], state[1]));
            second = SetNonTerminal(std::make_pair(state[2], '0' - 1));
          }
        }
        non_terminal_rules[begin].push_back(std::make_pair(first, second));
      }
      state.clear();
    } else { state += str[i]; }
  }
}

void Grammar::ReadGrammar() {
  std::cout << "Set the start non_terminal.\nExamples: S, S0, S1, ..., S9\n";
  std::string begin;
  std::cin >> begin;
  while (begin.length() == 0 ||
          begin.length() >= 3 ||
            !('A'<=begin[0] && begin[0] <= 'Z') ||
            !(begin.length() == 1 || begin.length() == 2 && ('0' <= begin[1] && begin[1] <= '9'))) {
    std::cout << "Wrong input\nTry again: set the start non_terminal.\nExamples: S, S0, S1, ..., S9\n";
    std::cin >> begin;
  }
  if (begin.length() == 1) {
    std::cout << begin[0] << " - initial nonterminal.\n";
    begin += (char) ('0' - 1); 
  } else {
    std::cout << begin[0] << begin[1] << " - initial nonterminal.\n";
  }
  start = NonTerminal(std::make_pair(begin[0], begin[1]));
  size_t num_of_rules;
  std::cout << "Write number of rules to read.\n";
  std::cin >> num_of_rules;
  std::cout << "Write " << num_of_rules << " rules in each line\nExample of rule in line: A->B0A1|BC|...|EPS|a\n" <<
                                           "Remember: write rules without space symbols like in the example!\n";
  for (size_t i = 0; i < num_of_rules; ++i) {
    std::cout << "Rule number " << i + 1 << '\n';
    std::string rule;
    std::cin >> rule;
    AddRule(rule);
    std::cout << "Rule number " << i + 1 << " is written into the grammar.\n";
  }
  std::cout << "End of reading the grammar!\n";
}

void Grammar::PrintRules() const {
  for (auto val: non_terminals) {
    std::cout << (char) ('A' + (val.number % 100));
    if (val.number >= 100) { std::cout << (char) ('0' + (val.number / 100) - 1); }
    std::cout << ' ';
  }
  std::cout << '\n';
  for (auto val: terminals) {
    if (val.number == 10){ std::cout << "EPS ";}
    else { std::cout << (char) (val.number) << ' '; }
  }
  std::cout << '\n';
  for (const auto& pair: non_terminal_rules) {
    std::cout << (char) ('A' + (pair.first.number % 100));
    if (pair.first.number >= 100) { std::cout << (char) ('0' + (pair.first.number / 100) - 1); }
    std::cout << "->";
    for (auto val: pair.second) {
      std::cout << (char) ('A' + (val.first.number % 100));
      if (val.first.number >= 100) { std::cout << (char) ('0' + (val.first.number / 100) - 1); }
      std::cout << (char) ('A' + (val.second.number % 100));
      if (val.second.number >= 100) { std::cout << (char) ('0' + (val.second.number / 100) - 1); }
      std::cout << "|";
    }
    std::cout << '\n';
  }
  for (const auto& pair: terminal_rules) {
    std::cout << (char) ('A' + (pair.first.number % 100));
    if (pair.first.number >= 100) { std::cout << (char) ('0' + (pair.first.number / 100) - 1); }
    std::cout << "->";
    for (auto val: pair.second) {
      if (val.number == 10) {
        std::cout << "EPS";
      } else {
        std::cout << (char) (val.number);
      }
      std::cout << '|';
    }
    std::cout << '\n';
  }
}
