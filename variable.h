#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
using std::string;

class Atom;
class Number;

class Variable{
public:
  Variable(string s):_symbol(s){}
  
  string const _symbol;

  string value(){ return _value; }

  bool match(Number n);
  // bool match(Atom a){
  //   bool ret = _assignable;
  //   if(_assignable){
  //     _value = a._symbol ;
  //     _assignable = false;
  //   }
  //   return ret;
  // }
  // bool match(Variable v){
  //     return false;
  // }

private:
  string _value;
  bool _assignable = true;
};

#endif
