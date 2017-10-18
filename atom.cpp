#include "term.h"
#include "atom.h"

string Atom::symbol() const{
    return _symbol;
}

string Atom::value(){
    return _symbol;
};