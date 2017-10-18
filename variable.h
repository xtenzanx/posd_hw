#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "term.h"
using std::string;

class Term;
class Atom;
class Number;
class Struct;

class Variable : public Term{
public:
  Variable(string s):_symbol(s),_value(s){}
  string const _symbol;
  string symbol() const;
  string value();

  bool match(Atom a);
  bool match(Number n);
  bool match(Variable &v);
  bool match(Struct &s);

  void setValue(string value);
  bool getAssignable();
  
private:
  string _value;
  bool _assignable = true;
  std::vector<Variable*> matchVector = {};
  Struct * matchStruct = 0;
};

#endif
