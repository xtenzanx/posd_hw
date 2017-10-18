#include "term.h"
#include "number.h"
#include "atom.h"
#include "variable.h"

string Number::symbol() const{
    return _symbol;
}

string Number::value(){
    return _value;
}

bool Number::match(Number n){
    return (value() == n.value()) ? (true) : (false);
}
bool Number::match(Atom a){
    return false;
}
bool Number::match(Variable &v){
    return v.match(*this);
}