#include <cmath>
#include "FunctionTable_T.h"
#include "SymbolTable_T.h"
#include "DebugNew.h"

struct FuncEntrys
{
	pFunc pfun;
	char* funName;
};

struct FuncEntrys Entry[] = 
{
	log,	"log",
	log10,	"log10",
	exp,	"exp",
	sqrt,	"sqrt",
	sin,	"sin",
	cos,	"cos",
	tan,	"tan",
	sinh,	"sinh",
	cosh,	"cosh",
	tanh,	"tanh",
	asin,	"asin",
	acos,	"acos",
	atan,	"atan"
};

FunctionTable_T::FunctionTable_T(SymbolTable_T& symbol)
	: i_size( sizeof(Entry) / sizeof(Entry[0]) )
{
	init(symbol);
}

void FunctionTable_T::init(SymbolTable_T& symbol)
{
	i_pFun = new pFunc[i_size];
	for (unsigned int i=0; i<size(); i++)
	{
		i_pFun[i] = Entry[i].pfun;
		symbol.add(Entry[i].funName);
	}
}

pFunc FunctionTable_T::get(unsigned int id) const
{
	return i_pFun[id];
}

unsigned int FunctionTable_T::size() const
{
	return i_size;
}