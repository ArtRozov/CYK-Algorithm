//We assume that:
//For data:
//1. The grammar has a Chomsky normal form
//2. "Symbol" for epsilon: EPS
//3. Every terminal is ONE ASCII SYMBOL that isn't a big English letter(small English letter and special symbols: (, ), ! and etc.)
//4. Every non_terminal is A BIG SYMBOL/ A BIG SYMBOL with ONE DIGIT(big English letter) Example: A or A0;
//For input:
//1. Number of lines of rules
//2. Each rule has the form:
// - A->BC|B0C|BC1|B1C0|...|a|EPS
// - A0->BC|B0C|BC1|B1C0|...|a|EPS

#include "include/CYK_Parser.h"

int main() {
  Grammar NF;
  NF.ReadGrammar();
  NF.PrintRules();
  std::string word;
  std::cout << "Enter the word\n";
  std::cin >> word;
  CYK parser;
  if (parser.Parse(NF, word)) {
    std::cout << "\nYes, this word belongs to grammar language\n\n";
  } else {
    std::cout << "\nNo, this word doesn't belongs to grammar language\n\n";
  }
  std::cout << "Press Ctrl+D to start checking test-coverage!\n";
  std::cin >> word;
  return 0;
}
