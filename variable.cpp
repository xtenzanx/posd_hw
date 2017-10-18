#include "term.h"
#include "variable.h"
#include "atom.h"
#include "number.h"
#include "struct.h"

string Variable::symbol() const{
    return _symbol;
}

string Variable::value(){
    if(matchStruct!=0){
        return matchStruct->value();
    }
    else{
        return _value;
    }
    
}


void Variable::setValue(string value){
    _value = value;
};

bool Variable::getAssignable(){
    return _assignable;
};


bool Variable::match(Atom a){
    bool ret = _assignable;

    if(_value == a._symbol){
        ret = true;
    }
    else{
        if(_assignable){
            _value = a._symbol;

            //更新群體value
            for(int i = 0; i < matchVector.size(); i++){
                matchVector[i]->setValue(_value);
            }

            _assignable = false;
        }
    }

    return ret;
}


bool Variable::match(Number n){
    bool ret = _assignable;
    
    if(_value == n.symbol()){
        ret = true;
    }
    else{
        if(_assignable){
            _value = n.symbol();

            //更新群體value
            for(int i = 0; i < matchVector.size(); i++){
                matchVector[i]->setValue(_value);
            }

            _assignable = false;
        }
    }

    return ret;
}

bool Variable::match(Variable &v){

    //判斷是否為同個變數
    if(_symbol != v.symbol()){

        //己群加入他群成員
        std::vector<Variable*> otherVector = {};
        otherVector.push_back(&v);
        for(int i = 0; i < v.matchVector.size(); i++){
            otherVector.push_back(v.matchVector[i]);
        }
        int count_o = matchVector.size();
        for(int i = 0; i < count_o; i++){
            for(int j = 0; j < otherVector.size(); j++){
                matchVector[i]->matchVector.push_back(otherVector[j]);
            }
        }
        for(int i = 0; i < otherVector.size(); i++){
            matchVector.push_back(otherVector[i]);
        }


        //他群加入幾群成員
        std::vector<Variable*> selfVector = {};
        selfVector.push_back(this);
        for(int i = 0; i < matchVector.size(); i++){
            selfVector.push_back(matchVector[i]);
        }
        int count_s = v.matchVector.size();
        for(int i = 0; i < count_s; i++){
            for(int j = 0; j < selfVector.size(); j++){
                v.matchVector[i]->matchVector.push_back(selfVector[j]);
            }
        }
        for(int i = 0; i < selfVector.size(); i++){
            v.matchVector.push_back(selfVector[i]);
        }
        

        
        if(!_assignable){
            //自己有值分給他人
            for(int i = 0; i < matchVector.size(); i++){
                matchVector[i]->setValue(_value);
            }
        }
        else{
            for(int i = 0; i < matchVector.size(); i++){
                //別人有值自己加入
                if(!matchVector[i]->getAssignable()){
                    _value = matchVector[i]->value();
                    break;
                }
            }
        }
        
    }

    return true;
}




bool Variable::match(Struct &s){
    bool ret = _assignable;


    matchStruct = &s;
    
    // if(_value == n.symbol()){
    //     ret = true;
    // }
    // else{
    //     if(_assignable){
    //         _value = n.symbol();
            
    //         //更新群體value
    //         for(int i = 0; i < matchVector.size(); i++){
    //             matchVector[i]->setValue(_value);
    //         }

    //         _assignable = false;
    //     }
    // }

    return ret;
}