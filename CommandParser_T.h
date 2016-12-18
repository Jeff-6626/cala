#ifndef _COMMANDPARSER_H_T_
#define _COMMANDPARSER_H_T_

#include <string>
#include "Parser_T.h"
class Scanner_T;
class Calc_T;
class CommandParser_T
{
	enum ECommand
	{
		CMD_HELP,
		CMD_QUIT,
		CMD_VAR,
		CMD_FUN,
		CMD_LOAD,
		CMD_SAVE,
		CMD_ERROR
	};
public:
	CommandParser_T(Scanner_T& scanner, Calc_T& calc);
	Status execute();
private:
	Status help() const;
	Status listVar() const;
	Status listFunc() const;
	Status load(const std::string& fileName);
	Status save(const std::string& fileName);
	Scanner_T& i_scanner;
	Calc_T& i_calc;
	ECommand i_cmd;
	std::string i_cmdName;
};

#endif	//_COMMANDPARSER_H_T_