#ifndef NUＭBER_H
#define NUＭBER_H

#include <string>
using std::string;

class Atom;
class Variable;

class Number {
public:
    Number(string i):_symbol(i),_value(i){}

    Number(int i){
        _symbol = std::to_string(i);
        _value = std::to_string(i);
    }
    
    string value(){ return _value; }
	string symbol(){ return _symbol; }
    bool match(Number n);
    bool match(Atom a);
    bool match(Variable &v);

private:
    string _symbol;
    string _value;
};

#endif
