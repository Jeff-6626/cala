#include <cmath>
#include "Storage_T.h"
#include "SymbolTable_T.h"
#include "Excetion_T.h"

Storage_T::Storage_T(SymbolTable_T& symbol)
{
	add(symbol);
}

void Storage_T::add(SymbolTable_T& symbol)
{
	unsigned int i = symbol.add("pi");
	add(exp(0.0), i);

	i = symbol.add("e");
	add(2.0*acos(0.0), i);
}

void Storage_T::add(const double number, unsigned int id)
{
	i_cells.resize(id+1);
	i_posivites.resize(id+1);
	i_cells[id] = number;
	i_posivites[id] = true;
}

void Storage_T::set(const double number, unsigned int id)
{
	if (id < i_cells.size())
	{
		i_cells[id] = number;
		i_posivites[id] = true;
	}
	else if (id == i_cells.size())
	{
		add(number, id);
	}
	else
	{
		//Å×³öÒì³£
		Excetion_T excep("EXCEPTIONERROR : this is a error id !");
		throw(excep);
	}
}

double Storage_T::get(unsigned int id) const
{
	if (i_posivites[id])
	{
		return i_cells[id];
	}
	
	return 0.0;
}

void Storage_T::serialize(Serializer_T& out) const
{
	out << i_cells.size();
	for (unsigned int i=0; i<i_cells.size(); i++)
		out << i_cells[i] << i_posivites[i];
}
void Storage_T::deSerialize(DeSerializer_T& in)
{
	i_cells.clear();
	i_posivites.clear();
	unsigned int size;
	in >> size;
	i_cells.resize(size);
	i_posivites.resize(size);

	double d;
	bool b;
	for (unsigned int i=0; i<size; i++)
	{	
		in >> d >> b;
		i_cells[i] = d;
		i_posivites[i] = b;
	}
}