#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;

class Number;
class Variable;

class Atom : public Term{
public:
  Atom (string s):_symbol(s) {}
  string symbol() const;
  string value();

  bool match(Number n);
  bool match(Atom a);
  bool match(Variable &v);

  string _symbol;
};


#endif
