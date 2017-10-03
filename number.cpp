#include "number.h"
#include "atom.h"
#include "variable.h"

bool Number::match(Number n){
    return (value() == n.value()) ? (true) : (false);
}
bool Number::match(Atom a){
    return false;
}
bool Number::match(Variable &v){
    return v.match(*this);
    // return true;
}



