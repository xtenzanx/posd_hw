#ifndef UTTERM_H
#define UTTERM_H

#include "number.h"
#include "atom.h"
#include "variable.h"

//test Number.value()
TEST (Number,ctor) {
    Number n(598);
    ASSERT_EQ("598", n.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number n(598);
    ASSERT_EQ("598", n.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number n1(25);
    Number n2(25);
    ASSERT_TRUE(n1.match(n2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number n1(25);
    Number n2(0);
    ASSERT_FALSE(n1.match(n2));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number n(25);
    Atom a("tom");
    ASSERT_FALSE(n.match(a));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number n(25);
    Variable x("X");
    ASSERT_TRUE(n.match(x));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom a("tom");
    Number n(25);
    ASSERT_FALSE(a.match(n));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    // Atom a("tom");
    // Variable x("X");
    // ASSERT_TRUE(a.match(x));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    // Variable x("X");
    // Atom a("tom");
    // EXPECT_TRUE(x.match(a));
    // EXPECT_TRUE(a.match(x));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {

}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
 
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {

}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {

}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {

}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){

}
#endif
