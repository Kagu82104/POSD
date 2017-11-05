#include "variable.h"
#include "list.h"
using namespace std;
#include <iostream>
Variable :: Variable(string s):_symbol(s),_value(s){}
  string Variable :: value() const{
    if(_termassignable){
      return pt->value();
    }
    if(_listassignable){
      return pt->value();
    }
    return _value;
  }
  string Variable :: symbol() const{return _symbol;}
  bool Variable :: match(Term & term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    Variable * pv = dynamic_cast<Variable *>(&term);
    //Variable * pv = term.getVariable();
    List * pl = dynamic_cast<List *>(&term);
      if(ps){
        if(!_termassignable) {
          pt = &term;
          _termassignable = true;
        }
        return _termassignable;
      }
      if(pv){
        if(_assignable ||pv->_assignable){
          _varassignable = false;
          if(vec.size() > 0 ){
            for (int i = 0; i < vec.size(); i++) {
              (*vec[i]).vec.push_back(pv);
              for (int j = 0; j < pv->vec.size(); j++) {
                (*vec[i]).vec.push_back(pv->vec[j]);
              }
            }
            for (int i = 0; i < pv->vec.size(); i++) {
              (*(pv->vec[i])).vec.push_back(this);
              for (int j = 0; j < vec.size(); j++) {
                (pv->vec[i])->vec.push_back(vec[j]);
              }
            }
            int vsize = pv->vec.size();
            for(int i=0;i<vec.size();i++){
              pv->vec.push_back(vec[i]);
            }
            for(int i=0;i<vsize;i++){
              vec.push_back(pv->vec[i]);
            }
            // for(int i=0;i<vec.size();i++){
            //   pv->vec.push_back(vec[i]);
            //   (*vec[i]).vec.push_back(pv);
            // }
            // for(int i=0;i<pv->vec.size();i++){
            //   vec.push_back(pv->vec[i]);
            //   pv->vec[i]->vec.push_back(vec[i]);
            // }
          }
          vec.push_back(pv); //x = y  y=z
          pv->vec.push_back(this);//y = x
          if(!_assignable){
            pv->_value = value();//(Y)value = X
            pv->_assignable = false;
          }
          else if(!(pv->_assignable)){
            _value =pv->value();//(Y)value = X
            _assignable = false;
          }
          else{
            _value = pv->value();
          }
          return true;
        }
        else if(value()==pv->value()){
          return true;
        }
        return false;
      }
      if(pl){
        if(!_listassignable || pt == &term) {
          pt = &term;
          _value = pl->value();
          _listassignable = true;
        }
        return _listassignable;
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
//Variable & Variable :: getVariable() { return *this; }
