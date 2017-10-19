#ifndef NUMBER_H
#define NUMBER_H
#include <sstream>
#include <string>
#include "term.h"
using std::string;
class Number:public Term {
public:
  Number(double v);
  string value();
  string symbol() const;
  bool match(Term &term);
private:
	double _value;
	const string _symbol;
};


#endif
