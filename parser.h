#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include "utParser.h"
using namespace std ;
class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      Term* v = new Variable(symtable[_scanner.tokenValue()].first);
      v = termtable(v);
      return v;
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }
  void matchings() {
    Term* term = createTerm();
    Node *left, *right, *root;
    if(term !=nullptr){
      _terms.push_back(term);

      while ((_currentToken = _scanner.nextToken()) == ';' || _currentToken == '=' || _currentToken == ',') {
        if(_currentToken == ';')  //SEMICOLON
        {
          _termtable.clear();
          left = _Treenode;
          matchings();
          Node * root = new Node(SEMICOLON, nullptr, left, expressionTree());
          _Treenode = root;
        }
        else if(_currentToken == ',') //COMMA
        {
          left = _Treenode;
          matchings();
          root = new Node(COMMA, nullptr, left, expressionTree());
          _Treenode = root;

        }
        else  //EQUALITY _currentToken == '='
        {
          left = new Node(TERM, _terms.back(), nullptr, nullptr);
          _terms.push_back(createTerm());
          right = new Node(TERM, _terms.back(), nullptr, nullptr);
          root = new Node(EQUALITY, nullptr, left, right);
          _Treenode = root;
        }
      }
    }
  }

  Node* expressionTree() {
    return _Treenode;
  }
  Term* termtable(Term * term){
    for (int i = 0; i < _termtable.size(); i++) {
      if(term->symbol() ==_termtable[i]->symbol()){
        return _termtable[i];
      }
    }
    _termtable.push_back(term);
    return term;
  }
private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  vector<Term *> _termtable;
  Scanner _scanner;
  int _currentToken;
  Node* _Treenode;
};

#endif
