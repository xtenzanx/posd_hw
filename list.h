#ifndef LIST_H
#define LIST_H

#include "term.h"

#include <vector>
using std::vector;

class Term;
class Atom;
class Number;
class Variable;
class Struct;

class List : public Term {
public:
  string symbol() const;
  string value();
  // bool match(Term & term);
  bool match(Atom &a);
  bool match(Number &n);
  bool match(Variable &v);
  bool match(Struct &s);
  bool match(List &l);
  vector<Term *> getElements();

public:
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const;
  List * tail() const;

private:
  vector<Term *> _elements;

};

#endif
