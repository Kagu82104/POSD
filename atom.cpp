#include "number.h"
#include "atom.h"
#include "variable.h"
#include <string>
using std::string;

Atom :: Atom (string s):_symbol(s) {}
	string Atom :: symbol(){return _symbol;}
	bool Atom :: match(Number num){return false;};
	bool Atom :: match(Variable &var){
  	bool ret = var.getassignable();
    if(ret || var.value()==""){
      var.setvalue(_symbol) ;
      var.setassignable(false);
			return true;
    }
		else if(_value==var.symbol()){
			return true;
		}
    return ret;
  }
