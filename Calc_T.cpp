#include <iostream>
#include "Calc_T.h"

unsigned int Calc_T::getSymbol(const std::string& symbol) const
{
	return i_symbol.find(symbol);
}

pFunc Calc_T::getFunc(unsigned int id) const
{
	return i_func.get(id);
}

Storage_T& Calc_T::getStorage()
{
	return i_storage;
}

unsigned int Calc_T::addSymbol(const std::string& symbol)
{
	return i_symbol.add(symbol);
}

void Calc_T::listFunc() const
{
	for (unsigned int i=0; i<i_func.size(); i++)
	{
		std::cout << i_symbol.get(i) << std::endl;
	}
}

void Calc_T::listVar() const
{
	for (unsigned int i = i_func.size(); i<i_symbol.getId(); i++)
	{
		std::cout << i_symbol.get(i) << " = " << i_storage.get(i) << std::endl;
	}
}

void Calc_T::serialize(Serializer_T& out) const
{
	i_symbol.serialize(out);
	i_storage.serialize(out);
}

void Calc_T::deSerialize(DeSerializer_T& in)
{
	i_symbol.deSerialize(in);
	i_storage.deSerialize(in);
}