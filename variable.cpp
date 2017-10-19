#include "variable.h"
using namespace std;
#include <iostream>
Variable :: Variable(string s):_symbol(s),_value(s){}
  string Variable :: value() const{
    if(_termassignable)
      return pt->value();
    return _value;
  }
  string Variable :: symbol() const{return _symbol;}
  bool Variable :: match(Term & term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    Variable * pv = dynamic_cast<Variable *>(&term);
      if(ps){
        if(!_termassignable) {
          pt = &term;
          _termassignable = true;
        }
        return _termassignable;
      }
      if(pv){
        if(_assignable ||pv->_assignable){
          cout << symbol() <<_value<< pv->symbol() <<pv->value() <<endl;

          _varassignable = false;
          if(vec.size() > 0 ){
            for(int i=0;i<vec.size();i++){
              pv->vec.push_back(vec[i]);
              (*vec[i]).vec.push_back(pv);
            }
          }
          vec.push_back(pv); //x = y  y=z
          pv->vec.push_back(this);//y = x
          cout <<_assignable <<endl;
          if(!_assignable){
            pv->_value = value();//(Y)value = X
            pv->_assignable = false;
          }
          else if(!(pv->_assignable)){
            _value =pv->value();//(Y)value = X
            _assignable = false;
          }

          //pv->match(*this);
          return true;
        }
        return false;
      }
      bool ret = _assignable;
      if(_assignable ||term.value() == _value){
        _value = term.value();
        _assignable = false;
          for(int i=0;i<vec.size();i++){
            (*vec[i])._value = term.value();
        }
        ret = true;
      }


      return ret;
}
