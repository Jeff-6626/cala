#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <string>
#include <map>
#include "Serializer_T.h"

class SymbolTable_T : public Serializable_T
{
public:
	enum{IDNOTFOUND = 0xffffffff};
public:
	SymbolTable_T() : i_id(0)	{};
	unsigned int add(const std::string& symbol);
	unsigned int find(const std::string& symbol) const;
	std::string get(unsigned int id) const;
	unsigned int getId() const;
	virtual void serialize(Serializer_T& out) const;
	virtual void deSerialize(DeSerializer_T& in);
private:
	std::map<std::string, unsigned int> i_dictionary;
	unsigned int i_id;
};

#endif	//_SYMBOLTABLE_H_