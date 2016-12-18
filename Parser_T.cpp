#include <sstream>
#include "Parser_T.h"
#include "Scanner_T.h"
#include "Node_T.h"
#include "Calc_T.h"
#include "DebugNew.h"
#include "Excetion_T.h"

void Parser_T::parser()
{
	i_tree = expre();
}

double Parser_T::clac() const
{
	return i_tree->calc();
}

std::auto_ptr<Node_T> Parser_T::expre()
{
	std::auto_ptr<Node_T> pNode = trem();
	EToken token = i_scanner.getToken();

	if (token == TOKEN_PLUS || token == TOKEN_MINUS)
	{
		std::auto_ptr<MultipleNode_T> pMultiple( new SumNode_T(pNode) );
		do 
		{
			i_scanner.accept();
			std::auto_ptr<Node_T> pNode = trem();
			pMultiple->add(pNode, token==TOKEN_PLUS);
			token = i_scanner.getToken();
		} while (token == TOKEN_PLUS || token == TOKEN_MINUS);

		pNode = pMultiple;
	}
	else if (token == TOKEN_ASSING)
	{
		i_scanner.accept();
		std::auto_ptr<Node_T> pRight = expre();
		if (pNode->isLeftValue())
		{
			pNode= std::auto_ptr<Node_T>( new AssignNode_T(pNode, pRight) );
		}
		else
		{
			//抛出异常
			SyntaxError_T syntax("SYNTAXERROR : it must be a left value!");
			throw(syntax);
		}
	}

	return pNode;
}

std::auto_ptr<Node_T> Parser_T::trem()
{
	std::auto_ptr<Node_T> pNode = faction();
	EToken token = i_scanner.getToken();

	if (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE)
	{
		std::auto_ptr<MultipleNode_T> pMultiple( new ProductNode_T(pNode) );
		do 
		{
			i_scanner.accept();
			std::auto_ptr<Node_T> pRight = faction();
			pMultiple->add(pRight, token == TOKEN_MULTIPLY);
			token = i_scanner.getToken();
		} while (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE);
		
		pNode = pMultiple;
	}

	return pNode;
}

std::auto_ptr<Node_T> Parser_T::faction()
{
	std::auto_ptr<Node_T> pNode;
	EToken token = i_scanner.getToken();
	if (token == TOKEN_NUMBER)
	{
		i_scanner.accept();
		pNode = std::auto_ptr<Node_T>( new NumberNode_T(i_scanner.getNumber()) );
	}
	else if (token == TOKEN_MINUS)
	{
		i_scanner.accept();
		pNode = std::auto_ptr<Node_T>(  new MinusNode_T(faction()) );
	}
	else if (token == TOKEN_LEFT_PARETHESIS)
	{
		i_scanner.accept();
		pNode = expre();
		if (i_scanner.getToken() == TOKEN_RIGHT_PARETHESIS)
		{
			i_scanner.accept();
		}
		else
		{
			//抛出异常
			SyntaxError_T syntax("SYNTAXERROR : it must have a right parethesis !");
			throw(syntax);
		}
	}
	else if (token == TOKEN_IDENTIFIER)
	{
		std::string symbol = i_scanner.getSymbol();
		int id = i_calc.getSymbol(symbol);
		i_scanner.accept();
		if (i_scanner.getToken() == TOKEN_LEFT_PARETHESIS)
		{
			i_scanner.accept();
			pNode = expre();
			if (i_scanner.getToken() == TOKEN_RIGHT_PARETHESIS)
			{
				i_scanner.accept();
				if (id != SymbolTable_T::IDNOTFOUND)
				{
					pNode = std::auto_ptr<Node_T>( new FunctionNode_T(pNode, i_calc.getFunc(id)) );
				}
				else
				{
					//抛出异常
					i_token = TOKEN_ERROR;
					char buf[256] = {0};
					std::ostringstream oss;
					oss << "EXCEPTIONERROR : Unknown function \"" << symbol << "\"!";
					Excetion_T excep(oss.str());
					throw(excep);
				}
			}
			else
			{
				//抛出异常
				SyntaxError_T syntax("SYNTAXERROR : it must be a left value!");
				throw(syntax);
			}
		}
		else
		{
			if (id == SymbolTable_T::IDNOTFOUND)
			{
				id = i_calc.addSymbol(symbol);
				i_calc.getStorage().set(0.0, id);
			}
			pNode = std::auto_ptr<Node_T>( new VariableNode_T(id, i_calc.getStorage()) );
		}
	}
	else
	{
		SyntaxError_T syntax("some other syntaxError !");
		throw(syntax);
		token = TOKEN_ERROR;
	}

	return pNode;
}