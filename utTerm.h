#ifndef UTTERM_H
#define UTTERM_H
#include "number.h"
#include "atom.h"
#include "variable.h"
using namespace std;
//test Number.value()
TEST (Number,ctor) {
	Number num(25);
	ASSERT_EQ("25",num.value());
}
//test Number.symbol()
TEST (Number, symbol) {
	Number num(10);
	ASSERT_EQ("10",num.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
	Number num(25);
	Number num1(25);
	ASSERT_TRUE(num.match(num1));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
	Number num(25);
	Number num1(0);
	ASSERT_FALSE(num.match(num1));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
	Number num(25);
	Atom num1("tom");
	ASSERT_FALSE(num.match(num1));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
  Number num(25);
  Variable var("X");
  EXPECT_TRUE(num.match(var));

}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
	Number num(25);
	Atom num1("tom");
	ASSERT_FALSE(num1.match(num));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
	Atom tom("tom");
	Variable var("X");
	ASSERT_TRUE(tom.match(var));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
	Atom tom("tom");
	Variable var("X");
	ASSERT_TRUE(var.match(tom));
	ASSERT_TRUE(tom.match(var));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
	Atom tom("tom");
	Atom jerry("jerry");
	Variable var("X");
	ASSERT_TRUE(var.match(jerry));
	ASSERT_FALSE(tom.match(var));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
	Variable var("X");
	Number num(5);
	ASSERT_TRUE(var.match(num));
	EXPECT_EQ("5",var.value());
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
	Variable Var("X");
	Number num(25);
	Number num1(100);
	ASSERT_TRUE(Var.match(num));
	EXPECT_FALSE(Var.match(num1));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
	Variable Var("X");
	Atom tom("tom");
	Number num(25);
	ASSERT_TRUE(Var.match(tom));
	EXPECT_FALSE(Var.match(num));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
	Number num(25);
	Atom tom("tom");
	Variable var("X");
	ASSERT_TRUE(var.match(tom));
	ASSERT_FALSE(num.match(var));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
	Variable var("X");
	Atom tom("tom");
	ASSERT_TRUE(var.match(tom));
	ASSERT_TRUE(var.match(tom));
}
#endif
