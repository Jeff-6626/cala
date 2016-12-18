#ifndef _PARSER_H_
#define _PARSER_H_

#include <memory>
#include "Scanner_T.h"

class Calc_T;
class Node_T;

enum Status
{
	STATUS_OK,
	STATUS_ERROR,
	STATUS_QUIT
};

class Parser_T
{
public:
	Parser_T(Scanner_T& scanner, Calc_T& calc) 
		: i_scanner(scanner), i_calc(calc)	{}
	void parser();
	double clac() const;
private:
	std::auto_ptr<Node_T> expre();
	std::auto_ptr<Node_T> trem();
	std::auto_ptr<Node_T> faction();
	Scanner_T& i_scanner;
	std::auto_ptr<Node_T> i_tree;
	EToken i_token;
	Calc_T& i_calc;
	Status i_status;
};

#endif	//_PARSER_H_