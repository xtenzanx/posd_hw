#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
using std::string;

class Atom;
class Number;

class Variable : public Term{
public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string symbol() const;
  string value(){ return _value; }

  bool match(Atom a);
  bool match(Number n);
  bool match(Variable &v);

  void setValue(string value);
  bool getAssignable();
  
private:
  string _value;
  bool _assignable = true;
  std::vector<Variable*> matchVector = {};
};

#endif
