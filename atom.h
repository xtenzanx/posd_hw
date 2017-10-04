#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;

class Variable;
class Number;

class Atom {
public:
  Atom (string s):_symbol(s) {}
  bool operator ==(Atom a) {return _symbol == a._symbol;}
  string _symbol;

  bool match(Number n);
  bool match(Atom a);
  bool match(Variable &v);
};

#endif
