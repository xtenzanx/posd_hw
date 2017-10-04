#ifndef NUMBER_H
#define NUMBER_H

#include <string>
using std::string;

class Atom;
class Variable;

class Number {
	public :
		Number ( int n ); 
		int value ();
		int symbol ();
		bool match ( Number number );
		bool match ( Atom atom );
		bool match ( Variable &variable );
	private :
		const int _symbol;
};
#endif

