#ifndef _CALC_H_
#define _CALC_H_

#include "SymbolTable_T.h"
#include "Storage_T.h"
#include "FunctionTable_T.h"
#include "Serializer_T.h"

class Parser_T;
class Calc_T : public Serializable_T
{
	friend class Parser_T;
public:
	Calc_T() : i_func(i_symbol), i_storage(i_symbol)	{}
	void listFunc() const;
	void listVar() const;
	virtual void serialize(Serializer_T& out) const;
	virtual void deSerialize(DeSerializer_T& in);
private:
	unsigned int addSymbol(const std::string& symbol);
	pFunc getFunc(unsigned int id) const;
	unsigned int getSymbol(const std::string& symbol) const;
	Storage_T& getStorage();
	SymbolTable_T i_symbol;
	FunctionTable_T i_func;
	Storage_T i_storage;
};

#endif	//_CALC_H_