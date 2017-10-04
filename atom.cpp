#include "atom.h"
#include "number.h"
#include "variable.h"

Atom :: Atom ( string a ) : _symbol ( a ) {}

string Atom :: symbol () { return _symbol; }
/*
bool Atom :: operator == ( Atom a ) {
	return _symbol == a._symbol;
}
*/
bool Atom :: match ( Number number ) {
	return false;
}

bool Atom :: match ( Variable &variable ){
	if ( variable.assignable() || variable.value() == _symbol ){
		variable.setValue ( _symbol );
		variable.setAssignable (false);
		return true;
	}
	return false;
}

