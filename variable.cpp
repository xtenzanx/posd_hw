#include "number.h"
#include "atom.h"
#include "variable.h"

bool Variable::match(Number n){
    return true;
}
bool Variable::match(Atom a){
    bool ret = _assignable;

    // if(_value == a._symbol){
    //     ret = true;
    // }
    // else{
    //     if(_assignable){
    //         _value = a._symbol;
    //         _assignable = false;
    //     }
    // }

    return ret;




    // bool ret = _assignable;
    // if(_assignable){
    //     _value = a._symbol ;
    //     _assignable = false;
    // }
    // return ret;
}