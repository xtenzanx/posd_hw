#include "term.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include "list.h"

string Atom::symbol() const{
    return _symbol;
};

string Atom::value(){
    return _symbol;
};

bool Atom::match(Number n){
    return false;
}
bool Atom::match(Atom a){
    return false;
}
bool Atom::match(Variable &v){
    return v.match(*this);
}
bool Atom::match(List &l){
    return false;
}