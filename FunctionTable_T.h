#ifndef _FUNCTIONTALBE_H_
#define _FUNCTIONTALBE_H_

typedef double (*pFunc)(double);

class SymbolTable_T;
class FunctionTable_T
{
public:
	FunctionTable_T(SymbolTable_T& symbol);
	void init(SymbolTable_T& symbol);
	unsigned int size() const;
	pFunc get(unsigned int id) const;
	~FunctionTable_T()
	{
		delete i_pFun;
	}
private:
	pFunc* i_pFun;
	unsigned int i_size;
};

#endif	//_FUNCTIONTALBE_H_