#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
using std::string;


class Number : public Term{
public:
    // Number(string i):_symbol(i),_value(i){}

    Number(double d){
        _value = std::to_string(d);

        // _symbol = std::to_string(d);
        std::ostringstream strs;
        strs << d;
        _symbol = strs.str();
        
    }
    
    string value(){ return _value; }
    string symbol() const;


private:
    string _symbol;
    string _value;
};

#endif
