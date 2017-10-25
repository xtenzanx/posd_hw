#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;

class Number;
class Variable;
class List;

class Atom : public Term{
public:
  Atom (string s):_symbol(s) {}
  string symbol() const;
  string value();

  bool match(Number n);
  bool match(Atom a);
  bool match(Variable &v);
  bool match(List &l);

  string _symbol;
};


#endif
