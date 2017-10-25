#include "term.h"
#include "number.h"
#include "atom.h"
#include "variable.h"
#include "list.h"

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
bool Number::match(List &l){
    return false;
}
// bool Number::match(Term & term){
//     Number * pn = dynamic_cast<Number *>(&term);
//     if(pn){
//         // return match(*pn);
//         return true;
//     }
//     else{
//         return false;
//     }
// }


bool Number::match(Term & term){
    Atom * pa = dynamic_cast<Atom *>(&term);
    Number * pn = dynamic_cast<Number *>(&term);
    Variable * pv = dynamic_cast<Variable *>(&term);
    if(pa){
        return match(*pa);
    }
    else if(pn){
        return match(*pn);
    }
    else if(pv){
        return match(*pv);
    }
    else{
        return false;
    }

}