#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;
class Number;
class Variable;
class Atom {
public:
	Atom (string s);
	string symbol();
	bool match(Number num);
	bool match(Variable& var);

private:
	bool _assignable = true;
	const string _symbol;
};

#endif
