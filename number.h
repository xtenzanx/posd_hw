#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
#include <string>
using std::string;

class Number : public Term{
public:
  Number(double db):Term(db) {}
};

#endif