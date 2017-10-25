#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
using std::string;

class Atom;
class Variable;
class List;

class Number : public Term{
public:
    // Number(string i):_symbol(i),_value(i){}

    Number(double d){
        // _value = std::to_string(d);
        // _symbol = std::to_string(d);
        std::ostringstream strs;
        strs << d;
        _symbol = strs.str();
        _value = strs.str();
        
    }
    
    string symbol() const;
    string value();

    bool match(Number n);
    bool match(Atom a);
    bool match(Variable &v);
    bool match(List &l);

private:
    string _symbol;
    string _value;
};

#endif
