#include "number.h"
#include "variable.h"
#include "list.h"
  Number :: Number(double v):_value(v),_symbol(std::to_string(v)){};
  string Number :: value(){
    std::stringstream ss;
    ss << _value;
    return ss.str();
  };
  string Number :: symbol() const {
    std::stringstream ss;
    ss << _value;
    return ss.str();
  };
  bool Number :: match(Term &term) {
    Variable * ps = dynamic_cast<Variable *>(&term);
    List * pl = dynamic_cast<List *>(&term);
    if(ps){
      return ps->match(*this);
    }
    if(pl){
      return false;
    }
    return value() == term.value();
  }
