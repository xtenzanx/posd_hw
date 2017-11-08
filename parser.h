#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "term.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "list.h"
#include "global.h"
#include "scanner.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  Term* createTerm(){
    int token = _scanner.nextToken();
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
        // Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        // if(_scanner.currentChar() == '('){
        //   _scanner.nextToken();
        //   vector<Term*> terms = getArgs();
        //   if(_currentToken == ')')
        //     return new Struct(*atom, terms);
        // }
        // else{
        //   return atom;
        // }
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        if(_scanner.currentChar() == '(') {
          _scanner.nextToken() ;
          if (_scanner.currentChar() == ')'){
            
            _scanner.nextToken();
            vector<Term*> emptyTerms = {};
            return new Struct(*atom, emptyTerms);
            // throw string("unexpected token2");
          }
          vector<Term*> terms = getArgs();
          if(_currentToken == ')')
            return new Struct(*atom, terms);
        }
        else
          return atom;
    }else if(token == '['){
      _scanner.skipLeadingWhiteSpace();
      if (_scanner.currentChar() == ']'){
        _scanner.nextToken();
        return new List();
      }
      else{
        vector<Term*> terms = getArgs();
        if (_currentToken == ')'){
          throw string("unexpected token");
        }
        return new List(terms);  
      }
    }
    return nullptr;
  }

  vector<Term*> getArgs()
  {
    Term* term = createTerm();
    vector<Term*> args;
    if(term)
      args.push_back(term);
    while((_currentToken = _scanner.nextToken()) == ',') {
      args.push_back(createTerm());
    }
    return args;


  }



private:
  Scanner _scanner;
  int _currentToken;
};
#endif
