#include "node.h"
#include "variable.h"

bool Node::evaluate(){
  /*判斷式是等於,做matching*/
  if(payload == EQUALITY){
    return left->term->match(*(right->term));
  }
  /*判斷式是逗號,代表裡面還有判斷式去檢查裡面*/
  else if(payload == COMMA){
    bool l = left->evaluate();
    bool r = right->evaluate();
    return (l&&r);
  }
  /*判斷式是分號,代表有效範圍*/
  else if(payload == SEMICOLON){
    bool l = left->evaluate();
    bool r = right->evaluate();
    return (l||r);
  }
}
