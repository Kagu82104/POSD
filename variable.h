#ifndef VARIABLE_H
#define VARIABLE_H
#include <string>
#include "atom.h"
using std::string;
class Atom;
class Number;
class Variable{
public:
  Variable(string s);
  string value();
  bool match( Atom atom );
  bool match(Number num);
  string setvalue(string v);
  bool setassignable(bool b);
  bool getassignable();
private:
  string _value;
  string const _symbol;
  bool _varassignable = true;
};

#endif
