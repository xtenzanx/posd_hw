#include "list.h"
#include "variable.h"
#include "atom.h"
#include "number.h"
#include "struct.h"

string List::symbol() const{
    string ret = "[";
    for(int i = 0; i < _elements.size() ; i++){
        if(i!=0) ret += ", ";
        ret += _elements[i]-> symbol();
    }
    ret += "]";
    return  ret;
}

string List::value(){
    string ret = "[";
    for(int i = 0; i < _elements.size() ; i++){
        if(i!=0) ret += ", ";
        ret += _elements[i]-> value();
    }
    ret += "]";
    return  ret;
}

// bool List::match(Term & term){
//     List * pl = dynamic_cast<List *>(&term);
//     if(pl){
//         for(int i = 0; i < _elements.size() ; i++){
//             if(_elements[i]->match( *(pl->_elements[i]) )){
//                 continue;
//             }
//             else{
//                 return false;
//                 // return true;
//             }
//         }
//         return true;
//     }
//     else{
//         return false;
//     }
// }

bool List::match(Atom &a){
    return false;
}
bool List::match(Number &n){
    return false;
}
bool List::match(Struct &s){
    return false;
}
bool List::match(Variable &v){
    return v.match(*this);
}

bool List::match(List &l){

    // Variable * pv = dynamic_cast<Variable *>(l._elements[1]);
    // Number * pn = dynamic_cast<Number *>(l._elements[1]);

    // if(pn){
    //     return _elements[1]->match( *pn );
    //     // return true;
    // }
    // else{
    //     return false;
    // }

    // return _elements[1]->match( *(l._elements[1]) );
    

    for(int i = 0; i < _elements.size() ; i++){
        if(_elements[i]->match( *(l._elements[i]) )){
            continue;
        }
        else{
            return false;
            // return true;
        }
    }
    return true;
}

vector<Term *> List::getElements(){
    return _elements;
}


Term * List::head() const {
    if(!_elements.size()){
        throw string("Accessing head in an empty list");
    }

    return _elements[0];
}

List * List::tail() const {
    if(!_elements.size()){
        throw string("Accessing tail in an empty list");
    }
        
    std :: vector<Term *>v(_elements.begin() + 1, _elements.end());
    List *temp = new List(v);
    return temp;
}