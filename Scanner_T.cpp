#include <cctype>
#include <iostream>
#include "Scanner_T.h"
double Scanner_T::getNumber() const
{
	return i_number;
}

std::string Scanner_T::getSymbol() const
{
	return i_symbol;
}

EToken Scanner_T::getToken() const
{
	return i_token;
}

bool Scanner_T::isCommand() const
{
	return i_token == TOKEN_COMMAND;
}

void Scanner_T::readChar()
{
	i_look = i_in.get();
	while (i_look == ' ' || i_look == '\t')
		i_look = i_in.get();
}

void Scanner_T::acceptCommand()
{
	readChar();
	i_symbol.erase();
	while (!isspace(i_look))
	{
		i_symbol += i_look;
		i_look = i_in.get();
	}
}

void Scanner_T::accept()
{
	readChar();
	switch (i_look)
	{
	case '+':
		i_token = TOKEN_PLUS;
		break;
	case '-':
		i_token = TOKEN_MINUS;
		break;
	case '*':
		i_token = TOKEN_MULTIPLY;
		break;
	case '/':
		i_token = TOKEN_DIVIDE;
		break;
	case '=':
		i_token = TOKEN_ASSING;
		break;
	case '!':
		i_token = TOKEN_COMMAND;
		break;
	case '\n':	case '\0':	case 'EOF':
		i_token = TOKEN_END;
		break;
	case '1':	case '2':	case '3':	case '4':	case '5':
	case '6':	case '7':	case '8':	case '9':	case '0':
	case '.':
		i_token = TOKEN_NUMBER;
		i_in.putback(i_look);
		i_in>>i_number;
		break;
	case '(':
		i_token = TOKEN_LEFT_PARETHESIS;
		break;
	case ')':
		i_token = TOKEN_RIGHT_PARETHESIS;
		break;
	default:
		if (isalpha(i_look) || i_look == '_')
		{
			i_token = TOKEN_IDENTIFIER;
			i_symbol.erase();
			do 
			{
				i_symbol += i_look; 
				i_look = i_in.get();
			} while (isalpha(i_look) || i_look == '_');
			i_in.putback(i_look);
		}
		else
			i_token = TOKEN_ERROR;
	}
}