#include "number.h"
#include "atom.h"
#include "variable.h"
#include <string>
using std::string;

  Variable :: Variable(string s):_symbol(s){}
  string Variable :: value(){ return _value; }

  bool Variable :: match(Number num){
    bool ret = _varassignable;
    if(ret || _value==num.value()){
      _value = num.value();
      _varassignable = false;
      return true;
    }
    return ret;
  }

  void Variable :: setvalue(string v){ _value = v; }

  void Variable :: setassignable(bool b){ _varassignable = b; }
  bool Variable :: getassignable(){ return _varassignable; }

  bool Variable :: match( Atom atom ){
    bool ret = _varassignable;
    if(ret || _value==atom.symbol()){
      _value = atom.symbol();
      _varassignable = false;
      return true;
    }
    return ret;
  }
