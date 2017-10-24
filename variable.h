#ifndef VARIABLE_H
#define VARIABLE_H
#include <vector>
#include <string>
#include "struct.h"
using std::string;
using namespace std;
class Struct;
class Variable:public Term{
public:
  Variable(string s);
  string value() const;
  string symbol() const;
  bool match(Term & term);
  //Variable * getVariable();
  string _symbol;
  string _value;
  Term *pt;
  bool _assignable = true;
  bool _varassignable = true;
  bool _termassignable = false;
  bool _listassignable = false;
  std::vector<Variable *> vec;

};

#endif
