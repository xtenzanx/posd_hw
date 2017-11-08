#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>
using std::vector;

class List : public Term {
public:
  List() : _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}

  string symbol() const{
    if(_elements.empty()){
      return "[]";
    }else{
      string ret = "[";
      vector<Term *>::const_iterator it = _elements.begin();
      for ( ; it != _elements.end()-1; ++it)
        ret += (*it)->symbol()+", ";
      ret += (*it)->symbol()+"]";
      return ret;
    }
  }
  string value() const{
    if(_elements.empty()){
      return "[]";
    }else{
      string ret = "[";
      vector<Term *>::const_iterator it = _elements.begin();
      for ( ; it != _elements.end()-1; ++it)
        ret += (*it)->value()+", ";
      ret += (*it)->value()+"]";
      return ret;
    }
  }
  bool compareElementsifexit(string compare){
    vector<Term *>::const_iterator it = _elements.begin();    
    for ( ; it != _elements.end()-1; ++it){
      if(compare == (*it)->value()){
        return false;            
      }  
    }
    return true;      
  }
  Term & getClasstype (int i){
    return *_elements[i];
  }
  bool match(Term & term){
    List * li = dynamic_cast<List *>(&term);
    if(_elements.size() == li->_elements.size()){
      for (int i=0; i<_elements.size()-1; i++){
        _elements[i]->match(li->getClasstype(i));
      }        
		  return true;
    }
    return false;
  }

  Term * head() const{
    if(!_elements.size()){
        throw string("Accessing head in an empty list");
    }

    return _elements[0];   
  }

  List * tail() const{
    if(!_elements.size()){
        throw string("Accessing tail in an empty list");
    }
        
    std :: vector<Term *>v(_elements.begin() + 1, _elements.end());
    List *temp = new List(v);
    return temp;
  }
private:
  vector<Term *> _elements;

};

#endif