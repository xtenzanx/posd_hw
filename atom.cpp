#include "number.h"
#include "atom.h"
#include "variable.h"

bool Atom::match(Number n){
    return false;
}
bool Atom::match(Atom a){
    return false;
}
// bool Atom::match(Variable &v){
//     // return v.match(*this);
//     return true;
// }