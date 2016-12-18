#ifndef _EXCETION_H_
#define _EXCETION_H_

#include <exception>
#include <string>

class Excetion_T : public std::exception
{
public:
	Excetion_T(const char* message)
		: i_message(message)	{}
	Excetion_T(std::string message)
		: i_message(message)	{}
	virtual const char* what() const;
private:
	std::string i_message;
};

class SyntaxError_T : public Excetion_T
{
public:
	explicit SyntaxError_T(const char* message)
		: Excetion_T(message)	{}
	explicit SyntaxError_T(std::string message)
		: Excetion_T(message)	{}
};

class FileStreamError_T : public Excetion_T
{
public:
	explicit FileStreamError_T(const char* message)
		: Excetion_T(message)	{}
	explicit FileStreamError_T(std::string message)
		: Excetion_T(message)	{}
};

class CheckNumberError : public Excetion_T
{
public:
	explicit CheckNumberError(const char* message)
		: Excetion_T(message)	{}
	explicit CheckNumberError(std::string message)
		: Excetion_T(message)	{}
};


#endif	//_EXCETION_H_