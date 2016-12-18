#include <cassert>
#include <vector>
#include "Node_T.h"
#include "Storage_T.h"
#include "FunctionTable_T.h"
#include "DebugNew.h"
#include "Excetion_T.h"

bool Node_T::isLeftValue() const
{
	return false;
}

void Node_T::assign(double number)
{
	assert(!"not a left value.");
}

double NumberNode_T::calc() const
{
	return i_number;
}

double MinusNode_T::calc() const
{
	return - i_pChild->calc();
}

double FunctionNode_T::calc() const
{
	return (*i_pFun)(i_pChild->calc());
}

double AssignNode_T::calc() const
{
	double x = 0.0;
	x = i_pRight->calc();
	i_pLeft->assign(x);

	return x;
}

MultipleNode_T::MultipleNode_T( std::auto_ptr<Node_T> pNode)
{
	add(pNode, true);
}

void MultipleNode_T::add(std::auto_ptr<Node_T> pCell, const bool posi)
{
	i_cells.push_back(pCell.release());
	i_posivites.push_back(posi);
}
MultipleNode_T::~MultipleNode_T()
{
	std::vector<Node_T*>::const_iterator it;
	for (it = i_cells.begin(); it != i_cells.end(); ++it)
	{
		delete *it;
	}
}

double SumNode_T::calc() const
{
	std::vector<Node_T*>::const_iterator itCell;
	std::vector<bool>::const_iterator itPosivite;
	double result = 0.0;

	for (itCell = i_cells.begin(), itPosivite = i_posivites.begin();
			itCell != i_cells.end(); ++itCell, ++itPosivite)
	{
		assert(itPosivite != i_posivites.end());	
		if (*itPosivite)
		{
			result += (*itCell)->calc();
		} 
		else
		{
			result -= (*itCell)->calc();
		}
	}

	return result;
}

double ProductNode_T::calc() const
{
	std::vector<Node_T*>::const_iterator itCell;
	std::vector<bool>::const_iterator itPositive;
	double result = 1.0;
	
	for (itCell = i_cells.begin(), itPositive = i_posivites.begin();
			itCell != i_cells.end(); ++itCell, ++itPositive)
	{
		if (*itPositive)
		{
			result *= (*itCell)->calc();
		}
		else
		{
			result /= (*itCell)->calc();
		}
	}

	return result;
}

bool VariableNode_T::isLeftValue() const
{
	return true;
}

double VariableNode_T::calc() const
{
	double x = 0.0;
	if ( isLeftValue() )
	{
		x = i_storage.get(i_id);
	}
	else
	{
		//Å×³öÒì³£
		SyntaxError_T syntax("SYNTAXERROR : it must be a left value!");
		throw(syntax);
	}
	return x;
}

void VariableNode_T::assign(double number)
{
	i_storage.set(number,i_id);
}