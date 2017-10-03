#ifndef NUMBER_H
#define NUMBER_H
#include "atom.h"
#include <string>

using std::string;
class Atom;
class Variable;
class Number {
public:
  Number(int v);
  int value();
  string symbol();
  bool match(Number num);
  bool match(Atom at);
  bool match(Variable var);
private:
	int _value;
	const string _symbol;
};


#endif
