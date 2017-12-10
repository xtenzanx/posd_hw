#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include "term.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include "struct.h"
#include "list.h"
#include "global.h"
#include "scanner.h"
#include "utParser.h"
#include "node.h"

// using std::string;
using namespace std;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }



  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());


      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void matchings(){
    Term* term = createTerm();

    if(term!=nullptr){
      if(comma){
        Term* findTerm = find(term);
        if(findTerm != nullptr){
          term->match(*findTerm);
        }
      }
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',' ||  _currentToken=='='|| _currentToken == ';'){
        if(_currentToken == '='){
          comma = false;
          Node* left = new Node(TERM,_terms.back(),nullptr,nullptr);
          if(_terms.back()->value()== "s(s(X))"){
            std::cout << "104fk" << endl;
          }
          _terms.push_back(createTerm());
          Node* right = new Node(TERM,_terms.back(),nullptr,nullptr);
          if(_terms.back()->value()== "s(s(X))"){
          }
          Node* root = new Node(EQUALITY,nullptr,left,right);
          _expressionTree = root;
        }
        else if(_currentToken == ','){
          comma = true;
          Node * left = _expressionTree;
          matchings();
          Node * root = new Node(COMMA, nullptr, left, expressionTree());
          _expressionTree = root;
        }
        else{
          comma = false;
          Node * left = _expressionTree;
          matchings();
          Node * root = new Node(SEMICOLON, nullptr, left, expressionTree());
          _expressionTree = root;
        }
      }
    }
  }

  Node* expressionTree(){
    return _expressionTree;
  }

  Term * find(Term * term){
    for(int index = 0; index < _terms.size() ; index++){
      if(_terms[index]->symbol() == term->symbol()) {
        return _terms[index];
      }
      Struct * s = dynamic_cast<Struct*>(_terms[index]);
      if(s) {
        return findStruct(s,term);
      }
    }
    return nullptr;
  }

  Term * findStruct(Struct * s, Term * term){
    for(int i = 0; i < s->arity() ; i++){
      if(s->args(i)->symbol() == term->symbol()) {
        return s->args(i);
      }
      Struct * ss = dynamic_cast<Struct*>(s->args(i));
      if(ss) {
        return findStruct(ss,term);
      }
    }
  }
private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  Node* _expressionTree;
  bool comma = false;
  int _lastToken;
};
#endif
