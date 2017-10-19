#include "number.h"
#include "variable.h"
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
    if(ps){
      return ps->match(*this);
    }
    return value() == term.value();
  }
