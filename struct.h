#ifndef STRUCT_H
#define STRUCT_H
#include <string>
#include <vector>
#include "atom.h"
#include "term.h"
//#include "variable.h"
using std::string;
class Struct: public Term {
public:
  Struct(Atom const & name, std::vector<Term *> v);
  Term * args(int index);
  Atom const & name();
  string symbol() const;
  string value() const;
  int arity();
  bool match(Term & term);
private:
  Atom _name;
  std::vector<Term *> _args;
};


#endif
