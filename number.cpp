#include "number.h"
#include "atom.h"
#include "variable.h"

Number :: Number ( int n ) : _symbol ( n ) {}

int Number :: value () { return _symbol; }

int Number :: symbol () { return _symbol; }

bool Number :: match ( Number number ){
	return _symbol == number.symbol();
}

bool Number :: match ( Atom atom ){
	return false;
}

bool Number :: match ( Variable &variable ){
	return variable.match ( *this );
} 

