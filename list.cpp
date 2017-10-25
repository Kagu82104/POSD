#include "list.h"
#include <string>
#include "variable.h"

// public:
//   List (): _elements() {}
//   List (vector<Term *> const & elements):_elements(elements){}
//   Term * head() const;
//   List * tail() const;
//
// private:
//   vector<Term *> _elements;

string List :: symbol() const {
  string ret;
  ret +="[";
  if(_elements.size() > 0 ){
    for (int i=0;i<_elements.size()-1;i++){
        ret +=_elements[i]->value() +", ";
    }
    ret +=_elements[_elements.size()-1]->symbol();
  }
  ret +="]";
    return ret;
}

bool List :: match(Term & term){
  List * ps = dynamic_cast<List *>(&term);
  Variable * pv = dynamic_cast<Variable *>(&term);
  if(ps){
    if(ps->getsize()==getsize()){
      int samelist=0;
      for(int i=0;i<getsize();i++){
        if(ps->_elements[i]==_elements[i]){
          samelist+=1;
        }
        if(samelist==getsize()){
          return true;
        }
      }
      for (int i = 0; i < ps->getsize(); i++) {
        bool listmatchlist =_elements[i]->match(*(ps->_elements[i]));
        if(!listmatchlist){
          return false;
        }
      }
      return true;
    }
    return false;
  }
  if(pv){
      pv->match(*this);
      return true;
  }

  return symbol() == term.symbol();
}

Term * List :: head() const{
  if (_elements.empty()) {
      throw string("Accessing head in an empty list");
    }
    else {
      return _elements[0];
    }
}

List * List :: tail() const{
  if (_elements.empty()) {
      throw string("Accessing tail in an empty list");
    }
    else {
      std :: vector<Term *> args;
      for (int i = 1; i < _elements.size(); i++) {
        args.push_back(_elements[i]);
      }
      List *list1 = new List(args);
      return list1;
    }
 }
