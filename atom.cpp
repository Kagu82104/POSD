#include "atom.h"
#include "variable.h"
#include "list.h"
Atom :: Atom (string s):_symbol(s) {};
  string Atom :: symbol() const {return _symbol;};
  bool Atom :: match(Term &term) {
    Variable * ps = dynamic_cast<Variable *>(&term);
    List * pl = dynamic_cast<List *>(&term);
    if(ps){
      return ps->match(*this);
    }
    if(pl){
      return false;
    }
    return _symbol == term.value();
  }
