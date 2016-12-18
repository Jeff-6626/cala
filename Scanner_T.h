#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <string>

enum EToken{
	TOKEN_COMMAND,
	TOKEN_ERROR,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_ASSING,
	TOKEN_LEFT_PARETHESIS,
	TOKEN_RIGHT_PARETHESIS,
	TOKEN_IDENTIFIER,
	TOKEN_END
};

class Scanner_T
{
public:
	Scanner_T(std::istream& in) : i_in(in)	{}
	void accept();
	void acceptCommand();
	double getNumber() const;
	std::string getSymbol() const;
	EToken getToken() const;
	bool isCommand() const;
private:
	void readChar();
	double i_number;
	std::string i_symbol;
	std::istream& i_in;
	EToken i_token;
	int i_look;
};

#endif	//_SCANNER_H_
