#include "atom.h"
#include "variable.h"
Atom :: Atom (string s):_symbol(s) {};
  string Atom :: symbol() const {return _symbol;};
  bool Atom :: match(Term &term) {
    Variable * ps = dynamic_cast<Variable *>(&term);
    if(ps){
      return ps->match(*this);
    }
    return _symbol == term.value();
  }
