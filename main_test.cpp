#include "include/CYK_Parser.h"
#include <gtest/gtest.h>

TEST(Parse, Belongs) {
  Grammar grammar;
  grammar.AddRule("S->a|AB");
  grammar.AddRule("A->a");
  grammar.AddRule("B->BB|b");
  grammar.start = grammar.non_terminals[grammar.GetIndexOfNonTerminal(grammar.non_terminals[0])];
  CYK parser;
  ASSERT_EQ(true, parser.Parse(grammar, "abbb"));
}

TEST(Parse, Doesnot_belongs) {
  Grammar grammar;
  grammar.AddRule("S->EPS|a|A0B");
  grammar.AddRule("A0->B1B1");
  grammar.AddRule("B->b");
  grammar.SetStart(std::make_pair('S', '0' - 1));
  CYK parser;
  ASSERT_EQ(false, parser.Parse(grammar, "ab"));
}

TEST(Parse, Epsilon_belongs) {
  Grammar grammar;
  grammar.AddRule("S->EPS|BB|CD");
  grammar.AddRule("B->BB|CD");
  grammar.AddRule("C->(");
  grammar.AddRule("D->BE|)");
  grammar.AddRule("E->)");
  grammar.SetStart(std::make_pair('S', '0' - 1));
  CYK parser;
  ASSERT_EQ(true, parser.Parse(grammar, "EPS"));
}

TEST(GetIndexOfNonTerminal, Doesnot_exist) {
  Grammar grammar;
  grammar.SetStart(std::make_pair('S', '0' - 1));
  ASSERT_EQ(1, grammar.GetIndexOfNonTerminal(NonTerminal(std::make_pair('A', '0'))));
}

TEST(PrintRules, Right_print) {
  Grammar grammar;
  grammar.AddRule("S->EPS|a|A0B");
  grammar.AddRule("A0->B1B1|CB1");
  grammar.AddRule("B->b");
  grammar.AddRule("B1->CC");
  grammar.AddRule("C->c");
  ASSERT_NO_THROW(grammar.PrintRules());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
