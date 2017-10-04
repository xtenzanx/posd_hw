#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
using std::string;

class Atom;
class Number;

class Variable{
	public:
  		Variable ( string v );
		//string const _symbol;
		bool assignable ();
		string value ();
		void setAssignable ( bool d );
		void setValue ( string c );
		bool match ( Atom atom );
		bool match ( Number number );	
	private:
		string const _symbol;
		string _value; 
		bool _assignable = true; 
};

#endif
