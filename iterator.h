#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>
#include <iostream>
#include <algorithm>
#include "struct.h"
#include "list.h"
#include <queue>

using namespace std;

template<class Item>
class Iterator
{
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual Item currentItem() const = 0;
    virtual bool isDone() const = 0;
};

template<class Item>
class NullIterator :public Iterator<Item>
{
public:
    friend class Term;
    void first(){}
    void next(){}
    Item currentItem() const
    {
        return nullptr;
    }
    bool isDone() const
    {
        return true;
    }
private:
    NullIterator(Item n){}
};

template<class Item>
class StructIterator :public Iterator<Item>
{
public:
    friend class Struct;
    void first() 
    {
        _index = 0;
    }

    Item currentItem() const 
    {
        return _s->args(_index);
    }

    bool isDone() const 
    {
        return _index >= (int)_s->arity();
    }

    void next() 
    {
        _index++;
    }
private:
    StructIterator(Struct *s): _index(0), _s(s) {}
    int _index;
    Struct* _s;
};

template<class Item>
class ListIterator :public Iterator<Item>
{
public:
    friend class List;
    void first() {
        _index = 0;
    }

    Item currentItem() const {
        return _list->args(_index);
    }

    bool isDone() const {
        return _index >= (int)_list->arity();
    }

    void next() {
        _index++;
    }
private:
    ListIterator(List *list): _index(0), _list(list) {}
    int _index;
    List* _list;
};

template<class Item>
class DFSIterator : public Iterator<Item>
{
public:
    friend class Term; 
    friend class Struct; 
    friend class List; 
    void first()
    {
        _index = 0;
        Item term;
        std::stack<Item> stk;
        std::vector<Item> rev;
        stk.push(_term);

        while(!stk.empty()){
            term = stk.top();
            stk.pop();
            if(_term!=term){
                _dfsTerms.push_back(term);
            }

            Iterator<Item> * it=term->createIterator();

            rev.clear();
            for(it->first();!it->isDone();it->next()){
                rev.push_back(it->currentItem());
            }
            std::reverse(rev.begin(),rev.end());
            for(size_t i=0;i<rev.size();i++){
                stk.push(rev[i]);
            }

        }
    }
    void next()
    {
        _index++;
    }
    Item currentItem() const
    {
        return _dfsTerms[_index];
    }
    bool isDone() const
    {
        return _index >= (int)_dfsTerms.size();
    }
private:
    DFSIterator(Item term):_term(term),_index(0)
    {

    }
    std::vector<Item> _dfsTerms;
    Item _term;
    int _index;
};

template<class Item>
class BFSIterator : public Iterator<Item>
{
public:
    friend class Term;  
    friend class Struct; 
    friend class List; 
    void first()
    {
        Item term;
        _index = 0;
        queue<Item> que;
        que.push(_term);
        while(!que.empty()) 
        {
            term = que.front();
            que.pop();

            if(_term!=term)
            {
                _bfsTerms.push_back(term);
            }
            Iterator<Item> * it=term->createIterator();
            for(it->first();!it->isDone();it->next())
            {
                que.push(it->currentItem());
            }
        }
    }
    void next()
    {
        _index++;
    }
    Item currentItem() const
    {
        return _bfsTerms[_index];
    }
    bool isDone() const{
        return _index >= (int)_bfsTerms.size();
    }

private:
    BFSIterator(Item term):_term(term),_index(0)
    {

    }
    std::vector<Item> _bfsTerms;
    Item _term;
    int _index;

};
#endif
