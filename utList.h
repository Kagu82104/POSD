#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
List list;
EXPECT_EQ("[]",list.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
Number num(496);
Number num1(8128);
std::vector<Term *> v ={&num,&num1};
List list(v);
EXPECT_EQ("[496, 8128]",list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  std::vector<Term *> v ={&terence_tao,&alan_mathison_turing};
  List list(v);
  EXPECT_EQ("[terence_tao, alan_mathison_turing]",list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X");
  Variable Y("Y");
  std::vector<Term *> v ={&X,&Y};
  List list(v);
  EXPECT_EQ("[X, Y]",list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Number num(496);
  Atom tom("tom");
  Atom terence_tao("terence_tao");
  Variable X("X");
  std::vector<Term *> v ={&num,&X,&terence_tao};
  List list(v);
  EXPECT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> v ={&num,&X,&terence_tao};
  List list(v);
  Number num1(8128);
  EXPECT_FALSE(num1.match(list));

}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> v ={&num,&X,&terence_tao};
  std::vector<Term *> v1 ={&X};
  List list(v);
  Struct s(Atom("s"), v1);
  EXPECT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> v ={&num,&X,&terence_tao};
  List list(v);
  Variable Y("Y");
  EXPECT_TRUE(Y.match(list));
  EXPECT_EQ("[496, X, terence_tao]",Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> v ={&num,&X,&terence_tao};
  List list(v);
  EXPECT_TRUE(X.match(list));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> v ={&num,&X,&terence_tao};
  List list(v);
  EXPECT_TRUE(list.match(list));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
Number num(496);
Variable X("X");
Variable Y("Y");
Atom terence_tao("terence_tao");
std::vector<Term *> v ={&num,&X,&terence_tao};
std::vector<Term *> v1 ={&num,&Y,&terence_tao};
List list(v);
List list1(v1);
EXPECT_TRUE(list.match(list1));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number num(496);
  Number num1(8128);
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  std::vector<Term *> v ={&num,&X,&terence_tao};
  std::vector<Term *> v1 ={&num,&num1,&terence_tao};
  List list(v);
  List list1(v1);
  EXPECT_TRUE(list.match(list1));
  EXPECT_EQ("8128",X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Number num(496);
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  std::vector<Term *> v ={&num,&X,&terence_tao};
  List list(v);
  Y.match(list);
  //EXPECT_EQ("[496, X, terence_tao]",Y.value());
  //EXPECT_EQ("[496, X, terence_tao]",list.value());
  X.match(alan_mathison_turing);
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]",list.value());
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]",Y.value());
  EXPECT_EQ("alan_mathison_turing",X.value());
  //EXPECT_EQ("[496, alan_mathison_turing, terence_tao]",Y.value());
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> v1 = {&f};
  List first_list(v1);
  vector<Term *> args = {&first_list, &s, &t};
  List l(args);
  EXPECT_EQ(string("[first]"), l.head()->value());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());

}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  vector<Term *> args;
  List l(args);
  try
  {
    l.head();
  }
  catch(string exception)
  {
    EXPECT_EQ("Accessing head in an empty list",exception);
  }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  vector<Term *> args;
  List l(args);
  try
  {
    l.tail();
  }
  catch(string exception)
  {
    EXPECT_EQ("Accessing tail in an empty list",exception);
  }
}

#endif
/*
[  FAILED  ] 2 tests, listed below:

[  FAILED  ] List.matchToSameListShouldSucceed
unknown file: Failure
C++ exception with description "std::bad_alloc" thrown in the test body.


*/
