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
        bool ret = _varassignable;
        if(_varassignable ||pv->_varassignable){
          _varassignable = false;
          if(vec.size() > 0 ){
            for(int i=0;i<vec.size();i++){
              pv->vec.push_back(vec[i]);
              (*vec[i]).vec.push_back(pv);
            }
          }
          vec.push_back(pv); //x = y  y=z
          pv->vec.push_back(this);//y = x
          _value =pv->value();//(Y)value = X
          pv->match(*this);
        }
        return ret;
      }
      bool ret = _assignable;
      if(_assignable ||term.value() == _value){
        _value = term.value();
        _assignable = false;
          cout << "symbol:"<<symbol()<<endl;
          for(int i=0;i<vec.size();i++){
            (*vec[i])._value = term.value();
        }
        return ret;
      }


      return false;
}
