#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>
#include <iostream>
#include <algorithm>
#include "struct.h"
#include "list.h"
#include <queue>
using namespace std;

template<class TermType>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual TermType currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template<class TermType>
class NullIterator :public Iterator<TermType>{
public:
  friend class Term;
  void first(){}
  void next(){}
  TermType currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }
private:
  NullIterator(TermType n){}
};

template<class TermType>
class StructIterator :public Iterator<TermType>{
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  TermType currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template<class TermType>
class ListIterator :public Iterator<TermType>{
public:
  friend class List;
  void first() {
    _index = 0;
  }

  TermType currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  ListIterator(List *list): _index(0), _list(list) {}
  int _index;
  List* _list;
};

template<class TermType>
class DFSIterator : public Iterator<TermType>{
public:
  friend class Term;
  friend class List;
  friend class Struct;

   void first(){
    _index = 0;
    TermType term;
    std::stack<TermType> stk;
    std::vector<TermType> rev;
    stk.push(_term);

    while(!stk.empty()){
      term = stk.top();
      stk.pop();
      if(_term!=term){
        _dfsTerms.push_back(term);
      }

      Iterator<TermType>* it=term->createIterator();

      rev.clear();
      for(it->first();!it->isDone();it->next()){
        rev.push_back(it->currentItem());
      }
      std::reverse(rev.begin(),rev.end());
      for(int i=0;i<rev.size();i++){
        stk.push(rev[i]);
      }

    }
   }
   void next(){
    _index++;
   }
   TermType currentItem() const{
    return _dfsTerms[_index];
   }
   bool isDone() const{
    return _index >= _dfsTerms.size();
   }
  private:
    DFSIterator(TermType term):_term(term),_index(0){}
    std::vector<TermType> _dfsTerms;
    TermType _term;
    int _index;
};
template<class TermType>
class BFSIterator : public Iterator<TermType>{
public:
  friend class Term;
  friend class List;
  friend class Struct;
   void first(){
     TermType term;
     _index = 0;
     queue<Term*> que;
     que.push(_term);
     while(!que.empty()) {
      term = que.front();
      que.pop();

      if(_term!=term){
        _bfsTerms.push_back(term);
      }
      Iterator<TermType>* it=term->createIterator();
      for(it->first();!it->isDone();it->next()){
        que.push(it->currentItem());
      }
     }
   }
   void next(){
    _index++;
   }
   TermType currentItem() const{
    return _bfsTerms[_index];
   }
   bool isDone() const{
     return _index >= _bfsTerms.size();
    }

  private:
    BFSIterator(TermType term):_term(term),_index(0){}
    std::vector<TermType> _bfsTerms;
    TermType _term;
    int _index;

};
#endif
