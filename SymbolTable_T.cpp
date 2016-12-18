#include <string>
#include <map>
#include <algorithm>
#include "SymbolTable_T.h"

unsigned int SymbolTable_T::add(const std::string& symbol)
{
	i_dictionary[symbol] = i_id;
	return i_id++;
}

unsigned int SymbolTable_T::find(const std::string& symbol) const
{
	std::map<std::string, unsigned int>::const_iterator it;
	it = i_dictionary.find(symbol);

	if (it != i_dictionary.end())
		return it->second;
	
	return IDNOTFOUND;
}

class Entry
{
public:
	Entry(int id) : i_id(id)	{}
	bool operator()(const std::pair<const std::string, unsigned int>& it)
	{
		return it.second == i_id;
	}
private:
	int i_id;
};

std::string SymbolTable_T::get(unsigned int id) const
{
	std::map<std::string, unsigned int>::const_iterator it;
	it = find_if(i_dictionary.begin(), i_dictionary.end(), Entry(id));

	if ( it != i_dictionary.end() )
	{
		return it->first;
	}
	else
	{
		throw("Unknow function");
	}
}

unsigned int SymbolTable_T::getId() const
{
	return i_id;
}

void SymbolTable_T::serialize(Serializer_T& out) const
{
	out << i_dictionary.size();
	std::map<std::string, unsigned int>::const_iterator it;
	for (it = i_dictionary.begin(); it != i_dictionary.end(); ++it)
		out << it->first << it->second;
	out << i_id;
}
void SymbolTable_T::deSerialize(DeSerializer_T& in)
{
	i_dictionary.clear();
	unsigned int size;
	in >> size;
	for (unsigned int i=0; i<size; i++)
	{	
		std::string str;
		unsigned int id;
		in >> str >> id;
		i_dictionary[str] = id;
	}
	in >> i_id;
}