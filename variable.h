#ifndef VARIABLE_H
#define VARIABLE_H
#include <vector>
#include <string>
#include "atom.h"
#include "number.h"
//#include "struct.h"
using std::string;
using namespace std;
class Struct;
class Variable:public Term{
public:
  Variable(string s):_symbol(s),_value(s){}
  string value() const{
    if(_termassignable)
      return pt->value();
    return _value;
  }
  string symbol() const{return _symbol;}
  bool match( Atom & atom ){
    bool ret = _assignable;
    if(_assignable||_value!=atom.value()){
      _value = atom.symbol();
      if(!_varassignable){
        for(int i=0;i<vec.size();i++){
            (*vec[i])._value = atom.value();
          }
      }
      _assignable = false;
    }
    return ret;
  }
  bool match(Variable & v){
    bool ret = _varassignable;
      if(vec.size() > 0 ){
        for(int i=0;i<vec.size();i++){
          v.vec.push_back(vec[i]);
          (*vec[i]).vec.push_back(&v);
        }
      }
      vec.push_back(&v); //x = y  y=z
      v.vec.push_back(this);//y = x
      _value =v.value();//(Y)value = X
      _varassignable = false;
    return ret;
  }
  bool match(Number & num){
      _value = num.value();
      for(int i=0;i<vec.size();i++){
          *vec[i] = num.value();
        }
    return true;
  }
  bool match(Term & term){
      if(!_termassignable) {
        pt = &term;
        _termassignable = true;
      }
      return _termassignable;
}
  string _symbol;
  string _value;
  Term *pt;
  bool _assignable = true;
  bool _varassignable = true;
  bool _termassignable = false;
  std::vector<Variable *> vec;
};

#endif
