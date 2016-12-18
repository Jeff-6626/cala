#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <vector>
#include "Serializer_T.h"

class SymbolTable_T;
class Storage_T : public Serializable_T
{
public:
	Storage_T(SymbolTable_T& symbol);
	void add(SymbolTable_T& symbol);
	void add(const double number, unsigned int id);
	void set(const double number, unsigned int id);
	double get(unsigned int id) const;
	virtual void serialize(Serializer_T& out) const;
	virtual void deSerialize(DeSerializer_T& in);
private:
	std::vector<double> i_cells;
	std::vector<bool> i_posivites;
};

#endif	//_STORAGE_H_