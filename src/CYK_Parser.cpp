#include "../include/CYK_Parser.h"

bool CYK::Parse(const Grammar& grammar, const std::string& str) {
  if (str == "EPS") {
    return grammar.TerminalExist(Terminal());
  }
  std::vector<std::vector<std::vector<bool>>> dp(grammar.non_terminals.size(),
                                                 std::vector<std::vector<bool>>(str.length(),
                                                                                std::vector<bool>(str.length(), false)));
  //Base
  for (const auto& pair: grammar.terminal_rules) {
    for (auto val: pair.second) {
      char c = val.GetChar();
      for (size_t i = 0; i < str.length(); ++i) {
        if (c == str[i]) { dp[grammar.GetIndexOfNonTerminal(pair.first)][i][i] = true; }
      }
    }
  }
  //Transition
  for (size_t len = 1; len < str.length(); ++len) {
    for (size_t i = 0; i < str.length() - len; ++i) {
      for (const auto& pair: grammar.non_terminal_rules) {
        for (auto val: pair.second) {
          for (size_t j = i; j < i + len; ++j) {
            dp[grammar.GetIndexOfNonTerminal(pair.first)][i][i + len] =
              dp[grammar.GetIndexOfNonTerminal(pair.first)][i][i + len] ||
              (dp[grammar.GetIndexOfNonTerminal(val.first)][i][j] &&
               dp[grammar.GetIndexOfNonTerminal(val.second)][j + 1][i + len]);
          }
        }
      }
    }
  }
  return dp[grammar.GetIndexOfNonTerminal(grammar.start)][0][str.length() - 1];
}
