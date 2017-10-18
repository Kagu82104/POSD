#ifndef NUMBER_H
#define NUMBER_H
#include <sstream>
#include <string>
#include "term.h"
#include "variable.h"
#include "struct.h"
using std::string;
class Number:public Term {
public:
  Number(double v):_value(v){};
  string value(){
    std::stringstream ss;
    ss << _value;
    return ss.str();
  };
  string symbol() const {
    std::stringstream ss;
    ss << _value;
    return ss.str();
  };

private:
	double _value;
	const string _symbol;
};


#endif
