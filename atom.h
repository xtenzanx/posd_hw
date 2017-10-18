#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;


class Atom : public Term{
public:
  Atom (string s):_symbol(s) {}
  string symbol() const;
  string value();

  string _symbol;
};


#endif
