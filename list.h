#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "string"
#include <vector>
using std::vector;

class List : public Term {
public:
  string symbol() const;
  bool match(Term & term);
public:
  List (): _elements() {};
  List (vector<Term *> const & elements):_elements(elements){};
  Term * getitem(int key){
    if(_elements.size() > key){
      return _elements[key];
    }
    else{
      return 0;
    }
  };
  int getsize(){return _elements.size();}
  Term * head() const;
  List * tail() const;

private:
  vector<Term *> _elements;
  string _symbol;
  Term *pt;
};

#endif
