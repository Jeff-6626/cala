#ifndef _SERIALIZER_H_
#define _SERIALIZER_H_

#include <fstream>
#include <string>
//serializer	序列化
//deserializer	反序列化
class Serializer_T
{
public:
	Serializer_T(const std::string& fileName);
	Serializer_T& put(int x);
	Serializer_T& put(unsigned int x);
	Serializer_T& put(long x);
	Serializer_T& put(unsigned long x);
	Serializer_T& put(const std::string& x);
	Serializer_T& put(bool x);
	Serializer_T& put(double x);

	Serializer_T& operator<<(int x);
	Serializer_T& operator<<(unsigned int x);
	Serializer_T& operator<<(long x);
	Serializer_T& operator<<(unsigned long x);
	Serializer_T& operator<<(const std::string& x);
	Serializer_T& operator<<(bool x);
	Serializer_T& operator<<(double x);
private:
	std::ofstream i_stream;
};


class DeSerializer_T
{
public:
	DeSerializer_T(const std::string& fileName);
	DeSerializer_T& get(int& x);
	DeSerializer_T& get(unsigned int& x);
	DeSerializer_T& get(long& x);
	DeSerializer_T& get(unsigned long& x);
	DeSerializer_T& get(std::string& x);
	DeSerializer_T& get(bool& x);
	DeSerializer_T& get(double& x);

	DeSerializer_T& operator>>(int& x);
	DeSerializer_T& operator>>(unsigned int& x);
	DeSerializer_T& operator>>(long& x);
	DeSerializer_T& operator>>(unsigned long& x);
	DeSerializer_T& operator>>(std::string& x);
	DeSerializer_T& operator>>(bool& x);
	DeSerializer_T& operator>>(double& x);
private:
	std::ifstream i_stream;
};

class Serializable_T
{
public:
	virtual void serialize(Serializer_T& out) const = 0;
	virtual void deSerialize(DeSerializer_T& in) = 0;
};

#endif	//_SERIALIZER_H_