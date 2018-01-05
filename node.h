#ifndef NODE_H
#define NODE_H
#include "term.h"
#include "global.h"
enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};
class Node
{
public:
    Node(Operators op);
    Node(Operators op, Term *t, Node *l, Node *r);
    bool evaluate();
    Operators payload;
    Term *term;
    Node *left;
    Node *right;
};
#endif
