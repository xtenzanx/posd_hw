#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;
#include <iostream>
using namespace std;
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "utParser.h"
#include "node.h"
#include "term.h"
#include "number.h"

class Parser{

public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      //std::cout << new Number(_scanner.tokenValue()) << endl;
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
    /*先讀入scanner*/
    Term* term = createTerm();

    /*createTerm回傳如果是空指標代表沒有輸入東西*/
    if(term!=nullptr){
      /*判斷目前是不是讀到,*/
      if(comma){
        /*去檢查有沒有相同的symbol*/
        Term* findTerm = find(term);
        /*如果不是空指標代表有相同的跟他做match*/
        if(findTerm != nullptr){
          term->match(*findTerm);
        }
      }
      _terms.push_back(term);
      /*產生樹*/
      while((_currentToken = _scanner.nextToken()) == ',' ||  _currentToken=='='|| _currentToken == ';'){
        if(_currentToken == '='){
          comma = false;
          /*左節點擺目前的數*/
          Node* left = new Node(TERM,_terms.back(),nullptr,nullptr);
          /*塞入下一個*/
          if(_terms.back()->value()== "s(s(X))"){
            std::cout << "104fk" << endl;
          }
          _terms.push_back(createTerm());
          /*右節點擺剛剛塞入的數*/
          Node* right = new Node(TERM,_terms.back(),nullptr,nullptr);
          if(_terms.back()->value()== "s(s(X))"){
            /*可能地方*/
          }
          /*擺入=並連到左節點與右節點*/
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
      }/*
      std::cout << "112" << endl;
      std::cout << _terms[0]->value() << endl;
      std::cout << _terms[1]->value() << endl;
      std::cout << _terms[2]->value() << endl;
      std::cout << _terms[3]->value() << endl;
      std::cout << _terms[4]->value() << endl;
      std::cout << _terms[5]->value() << endl;
      _terms[5]->match(*term);
      std::cout << _terms[5]->typeinfo() << endl;*/
    }
  }

  Node* expressionTree(){
    return _expressionTree;
  }

  /*去term中尋找是否有重複的*/
  Term * find(Term * term){
    for(int index = 0; index < _terms.size() ; index++){
      /*目前的term和傳進來的term有沒有symbol相同的*/
      if(_terms[index]->symbol() == term->symbol()) {
        return _terms[index];
      }
      /*動態轉型struct*/
      Struct * s = dynamic_cast<Struct*>(_terms[index]);
      /*s如果不是空指標就代表有struct去找struct裏頭有沒有symbol相同的*/
      if(s) {
        return findStruct(s,term);
      }
    }
    return nullptr;
  }

  Term * findStruct(Struct * s, Term * term){
    /*檢查struct裏頭有沒有和term的symbol一樣的*/
    for(int i = 0; i < s->arity() ; i++){
      if(s->args(i)->symbol() == term->symbol()) {
        return s->args(i);
      }
      Struct * ss = dynamic_cast<Struct*>(s->args(i));
      if(ss) {
        return findStruct(ss,term);
      }
    }
    //return nullptr;
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
