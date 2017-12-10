#include "node.h"
#include "variable.h"

bool Node::evaluate(){
  if(payload == EQUALITY){
    return left->term->match(*(right->term));
  }
  else if(payload == COMMA){
    bool l = left->evaluate();
    bool r = right->evaluate();
    return (l&&r);
  }
  else if(payload == SEMICOLON){
    bool l = left->evaluate();
    bool r = right->evaluate();
    return (l||r);
  }
}
