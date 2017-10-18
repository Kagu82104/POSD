#ifndef STRUCT_H
#define STRUCT_H
#include <string>
#include <vector>
#include "atom.h"
#include "term.h"
#include "variable.h"
using std::string;
class Struct: public Term {
public:
  Struct(Atom const & name, std::vector<Term *> v):_name(name), _args(v) {}
  Term * args(int index) { return _args[index]; }
  Atom const & name() { return _name; }
  string symbol() const {
    if(_args.size() > 0 ){
      string ret = _name.symbol() +"(";
      for (int i=0;i<_args.size()-1;i++){
          ret +=_args[i]->symbol() +", ";
      }
      ret +=_args[_args.size()-1]->symbol() +")";
      return ret;
    }
  };
  string value() const {
    string ret = _name.symbol() +"(";
    for (int i=0;i<_args.size()-1;i++){
        ret +=_args[i]->value() +", ";
    }
    ret +=_args[_args.size()-1]->value() +")";
    return ret;
  };
  bool match(Term & term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
     if (!_name.match(ps->_name)){return false;}//match1

     if (_args.size() != ps->_args.size()) {return false;}//match2

     for (int i = 0; i < _args.size(); i++) {//match3 match4
       if (_args[i]->symbol()!=ps->_args[i]->symbol()) {return false;}
     }
     return true;
   }
    return false;
  }
private:
  Atom _name;
  std::vector<Term *> _args;
};


#endif
