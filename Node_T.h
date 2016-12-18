#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include <cassert>
#include <memory>
#include "FunctionTable_T.h"


class NonCopyable_T
{
protected:
	NonCopyable_T()	{};
private:
	NonCopyable_T(const NonCopyable_T& non);
	NonCopyable_T& operator=(const NonCopyable_T& non);
};

class Node_T : private NonCopyable_T
{
public:
	virtual double calc() const = 0;
	virtual bool isLeftValue() const;
	virtual void assign(double number);
};

class NumberNode_T : public Node_T
{
public:
	NumberNode_T(double number) : i_number(number)	{}
	virtual double calc() const;
private:
	const double i_number;
};

class UnaryNode_T : public Node_T
{
public:
	UnaryNode_T(std::auto_ptr<Node_T> pChild) : i_pChild(pChild)	{}
	virtual double calc() const = 0;
protected:
	std::auto_ptr<Node_T> i_pChild;
};

class MinusNode_T : public UnaryNode_T
{
public:
	MinusNode_T(std::auto_ptr<Node_T> pChild) : UnaryNode_T(pChild)	{}
	double calc() const;
};

class FunctionNode_T : public UnaryNode_T
{
public:
	FunctionNode_T(std::auto_ptr<Node_T> pNode, pFunc pFun)
		: UnaryNode_T(pNode), i_pFun(pFun)	{}
	virtual double calc() const;
private:
	pFunc i_pFun;
};

class BinaryNode_T : public Node_T
{
public:
	BinaryNode_T(std::auto_ptr<Node_T> pLeft, std::auto_ptr<Node_T> pRight)
		: i_pLeft(pLeft), i_pRight(pRight)	{}
	virtual double calc() const = 0;
protected:
	std::auto_ptr<Node_T> i_pLeft;
	std::auto_ptr<Node_T> i_pRight;
};

class AssignNode_T : public BinaryNode_T
{
public:
	AssignNode_T(std::auto_ptr<Node_T> pLeft, std::auto_ptr<Node_T> pRight)
		: BinaryNode_T(pLeft, pRight)	
	{
		assert(i_pLeft->isLeftValue());
	}
	virtual double calc() const;
};

class MultipleNode_T : public Node_T
{
public:
	MultipleNode_T( std::auto_ptr<Node_T> pNode);
	void add(std::auto_ptr<Node_T> pCell, const bool posi);
	virtual double calc() const = 0;
	virtual ~MultipleNode_T();
protected:
	std::vector<Node_T*> i_cells;
	std::vector<bool> i_posivites;
};

class SumNode_T : public MultipleNode_T
{
public:
	SumNode_T(std::auto_ptr<Node_T> pNode) : MultipleNode_T(pNode)		{}
	virtual double calc() const;
};

class ProductNode_T : public MultipleNode_T
{
public:
	ProductNode_T(std::auto_ptr<Node_T> pNode) : MultipleNode_T(pNode)		{}
	virtual double calc() const;
};

class Storage_T;
class VariableNode_T : public Node_T
{
public:
	VariableNode_T(unsigned int id, Storage_T& storage)
		: i_id(id), i_storage(storage)	{}
	virtual bool isLeftValue() const;
	virtual double calc() const;
	virtual void assign(double number);
private:
	unsigned int i_id;
	Storage_T& i_storage;
};

#endif	//_NODE_H_
