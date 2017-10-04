#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;

class Number;
class Variable;

class Atom {
	public:
  		Atom ( string a );
		string symbol();
		//bool operator == ( Atom a );
		//string _symbol;
		bool match ( Number number );
		bool match ( Variable &variable );
  	private:
		const string _symbol;
};

#endif
