#ifndef UTTERM_H
#define UTTERM_H

#include "number.h"
#include "atom.h"
#include "variable.h"

//test Number.value()
TEST ( Number , ctor ) {
	Number number ( 15 );
	ASSERT_EQ ( 15 , number.value() );
}

//test Number.symbol()
TEST ( Number , symbol ) {
	Number number ( 15 ) ;
	ASSERT_EQ ( 15 , number.symbol() );
}

//?- 25=25.
//true.
TEST ( Number , matchSuccess ) {
	Number numberOne ( 25 );
        Number numberTwo ( 25 );
	ASSERT_TRUE ( numberOne.match ( numberTwo ) );
}

//?- 25=0.
//false.
TEST ( Number , matchFailureDiffValue ) {
	Number numberOne ( 25 );
        Number numberTwo ( 0 );
	ASSERT_FALSE ( numberOne.match ( numberTwo ) );
}

//?- 25=tom.
//false.
TEST ( Number , matchFailureDiffConstant ) {
	Number number ( 25 );
	Atom tom( "tom" );
	ASSERT_FALSE ( number.match ( tom ) );	
}

//?- 25=X.
//true.
TEST ( Number , matchSuccessToVar ) {
	Number number ( 25 );
	Variable X ( "X" );
	ASSERT_TRUE ( number.match ( X ) );
}

//?- tom=25.
//false.
TEST ( Atom , matchFailureDiffConstant ) {
	Atom tom ( "tom" );
	Number number ( 25 );
	ASSERT_FALSE ( tom.match ( number ) );
}

// ?- tom = X.
// X = tom.
TEST ( Atom , matchSuccessToVar ) {
	Atom tom ( "tom" );
	Variable X ( "X" );
	ASSERT_TRUE ( tom.match ( X ) );
}

// ?- X=tom, tom=X.
// X = tom.
TEST ( Atom , matchSuccessToVarInstantedToDiffConstant ) {
	Variable X ( "X" );
	Atom tom ( "tom" );
	X.match ( tom );
	ASSERT_TRUE ( tom.match ( X ) );
}

// ?- X=jerry, tom=X.
// false.
TEST ( Atom , matchFailureToVarInstantedToDiffConstant ) {
	Variable X ( "X" );
	Atom tom ( "tom" );
	Atom jerry ( "jerry" );
	X.match ( jerry );
	ASSERT_FALSE ( tom.match ( X ) );
}

// ?- X = 5.
// X = 5.
TEST ( Var , matchSuccessToNumber ) {
	Variable X ( "X" );
	Number number ( 5 );
	ASSERT_TRUE ( X.match ( number ) );
}

// ?- X=25, X= 100.
// false.
TEST ( Var , matchFailureToTwoDiffNumbers ) {
	Variable X ( "X" );
	Number numberOne ( 25 );
	Number numberTwo ( 100 );
	X.match ( numberOne );
	ASSERT_FALSE ( X.match ( numberTwo ) );
}

// ?- X=tom, X= 25.
// false.
TEST ( Var , matchSuccessToAtomThenFailureToNumber ) {
	Variable X ( "X" );
	Atom tom ( "tom" );
	Number number ( 25 );
	X.match ( tom );
	ASSERT_FALSE ( X.match ( number ) );
}

//?- tom=X, 25=X.
//false.
TEST ( Var , matchSuccessToAtomThenFailureToNumber2 ) {
	Atom tom ( "tom" );
	Variable X ( "X" );
	Number number ( 25 );
	tom.match ( X );
	ASSERT_FALSE ( number.match ( X ) );
}

//?- X=tom, X=tom.
//true.
TEST( Var , reAssignTheSameAtom ){
	Variable X ( "X" );
	Atom tom ( "tom" );
	X.match ( tom );
	ASSERT_TRUE ( X.match ( tom ) );
}

#endif
