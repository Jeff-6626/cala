#include "Excetion_T.h"
#include "Serializer_T.h"

using std::ios;

const int f_truePattern = 0xfab1fab2;
const int f_falsePattern = 0xbad1bad2;

//========================Serializer_T========================================//

Serializer_T::Serializer_T(const std::string& fileName)
	: i_stream(fileName.c_str(), ios::out | ios::binary)
{
	if (!i_stream)
 		throw FileStreamError_T("Couldn't open file!");
}

Serializer_T& Serializer_T::put(int x)
{
	i_stream.write(reinterpret_cast<char*>(&x), sizeof(int));
	if (i_stream.bad())
		throw FileStreamError_T("Write file failed!");

	return *this;
}

Serializer_T& Serializer_T::put(unsigned int x)
{
	i_stream.write(reinterpret_cast<char*>(&x), sizeof(unsigned int));
	if (i_stream.bad())
		throw FileStreamError_T("Write file failed!");

	return *this;
}

Serializer_T& Serializer_T::put(long x)
{
	i_stream.write(reinterpret_cast<char*>(&x), sizeof(long));
	if (i_stream.bad())
		throw FileStreamError_T("Write file failed!");

	return *this;
}

Serializer_T& Serializer_T::put(unsigned long x)
{
	i_stream.write(reinterpret_cast<char*>(&x),sizeof(unsigned long));
	if (i_stream.bad())
		throw FileStreamError_T("Write file failed!");

	return *this;
}

Serializer_T& Serializer_T::put(const std::string& x)
{
	int len = x.length();
	put(len);
	i_stream.write(x.data(), x.length());
	if (i_stream.bad())
		throw FileStreamError_T("Write file failed!");
	return *this;
}

Serializer_T& Serializer_T::put(bool x)
{
	int n = x ? f_truePattern : f_falsePattern;
	put(n);
	return *this;
}

Serializer_T& Serializer_T::put(double x)
{
	i_stream.write(reinterpret_cast<char*>(&x), sizeof(double));
	if (i_stream.bad())
		throw FileStreamError_T("Write file failed!");

	return *this;
}

Serializer_T& Serializer_T::operator<<(int x)
{
	return put(x);
}

Serializer_T& Serializer_T::operator<<(unsigned int x)
{
	return put(x);
}

Serializer_T& Serializer_T::operator<<(long x)
{
	return put(x);
}

Serializer_T& Serializer_T::operator<<(unsigned long x)
{
	return put(x);
}

Serializer_T& Serializer_T::operator<<(const std::string& x)
{
	return put(x);
}

Serializer_T& Serializer_T::operator<<(bool x)
{
	return put(x);
}

Serializer_T& Serializer_T::operator<<(double x)
{
	return put(x);
}

//=============================DeSerilalizer_T====================================================//

DeSerializer_T::DeSerializer_T(const std::string& fileName)
	:i_stream(fileName.c_str(), ios::in | ios::binary)
{
	if (!i_stream)
		throw FileStreamError_T("Couldn't open file.");
}

DeSerializer_T& DeSerializer_T::get(int& x)
{
	if (i_stream.eof())
		throw FileStreamError_T("Unexpected end of file");

	i_stream.read(reinterpret_cast<char*>(&x), sizeof(int));

	if (i_stream.bad())
		throw FileStreamError_T("Read file failed.");
	return *this;
}

DeSerializer_T& DeSerializer_T::get(unsigned int& x)
{
	if (i_stream.eof())
		throw FileStreamError_T("Unexpected end of file");

	i_stream.read(reinterpret_cast<char*>(&x), sizeof(unsigned int));

	if (i_stream.bad())
		throw FileStreamError_T("Read file failed.");
	return *this;
}

DeSerializer_T& DeSerializer_T::get(long& x)
{
	if (i_stream.eof())
		throw FileStreamError_T("Unexpected end of file");

	i_stream.read(reinterpret_cast<char*>(&x), sizeof(long));

	if (i_stream.bad())
		throw FileStreamError_T("Read file failed.");
	return *this;
}

DeSerializer_T& DeSerializer_T::get(unsigned long& x)
{
	if (i_stream.eof())
		throw FileStreamError_T("Unexpected end of file");

	i_stream.read(reinterpret_cast<char*>(&x), sizeof(unsigned long));

	if (i_stream.bad())
		throw FileStreamError_T("Read file failed.");
	return *this;
}

DeSerializer_T& DeSerializer_T::get(std::string& x)
{
	int len;
	get(len);

	if (i_stream.eof())
		throw FileStreamError_T("Unexpected end of file");
	x.resize(len);
	i_stream.read(&x[0], len);

	if (i_stream.bad())
		throw FileStreamError_T("Read file failed.");

	return *this;
}

DeSerializer_T& DeSerializer_T::get(bool& x)
{
	int n;
	get(n);
	if (n == f_truePattern)
		x = true;
	else if (n == f_falsePattern)
		x = false;
	else
		throw CheckNumberError("Data error");
	return *this;
}

DeSerializer_T& DeSerializer_T::get(double& x)
{
	if (i_stream.eof())
		throw FileStreamError_T("Unexpected end of file");

	i_stream.read(reinterpret_cast<char*>(&x), sizeof(double));

	if (i_stream.bad())
		throw FileStreamError_T("Read file failed.");
	return *this;
}

DeSerializer_T& DeSerializer_T::operator>>(int& x)
{
	return get(x);
}

DeSerializer_T& DeSerializer_T::operator>>(unsigned int& x)
{
	return get(x);
}

DeSerializer_T& DeSerializer_T::operator>>(long& x)
{
	return get(x);
}

DeSerializer_T& DeSerializer_T::operator>>(unsigned long& x)
{
	return get(x);
}

DeSerializer_T& DeSerializer_T::operator>>(std::string& x)
{
	return get(x);
}

DeSerializer_T& DeSerializer_T::operator>>(bool& x)
{
	return get(x);
}

DeSerializer_T& DeSerializer_T::operator>>(double& x)
{
	return get(x);
}