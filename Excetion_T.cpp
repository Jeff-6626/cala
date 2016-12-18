#include "Excetion_T.h"

const char* Excetion_T::what() const
{
	return i_message.c_str();
}