#include "number.h"
#include "atom.h"
#include "variable.h"
#include <string>

using std::string;
Number :: Number(int v):_value(v),_symbol(std::to_string(v)){}
  int Number :: value(){return _value;}
  string Number :: symbol(){return _symbol;}
  bool Number :: match(Number num){return _value==num._value;}
  bool Number :: match(Atom at){return _symbol==at.symbol();}
  bool Number :: match(Variable var){
  	bool ret = var.getassignable();
  	if(ret || var.value()==std::to_string(_value)){
  		return true;
  	}
  	return false;
  }
