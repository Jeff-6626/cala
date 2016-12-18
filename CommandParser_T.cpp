#include <cassert>
#include <iostream>
#include "CommandParser_T.h"
#include "Scanner_T.h"
#include "Calc_T.h"
#include "Excetion_T.h"

CommandParser_T::CommandParser_T(Scanner_T& scanner, Calc_T& calc)
	: i_scanner(scanner), i_calc(calc)
{
	assert(i_scanner.isCommand());
	i_scanner.accept();
	i_cmdName = i_scanner.getSymbol();
	switch (i_cmdName[0])
	{
	case 'h':
		i_cmd = CMD_HELP;
		break;
	case 'q':
		i_cmd = CMD_QUIT;
		break;
	case 'v':
		i_cmd = CMD_VAR;
		break;
	case 'f':
		i_cmd = CMD_FUN;
		break;
	case 'l':
		i_cmd = CMD_LOAD;
		break;
	case 's':
		i_cmd = CMD_SAVE;
		break;
	default:
		i_cmd = CMD_ERROR;
		break;
	}
}

Status CommandParser_T::execute()
{
	i_scanner.acceptCommand();
	std::string fileName = i_scanner.getSymbol();
	Status status = STATUS_OK;
	switch (i_cmd)
	{
	case CMD_HELP:
		status = help();
		break;
	case CMD_QUIT:
		std::cout << "GOOD BYE!" << std::endl;
		status = STATUS_QUIT;
		break;
	case CMD_VAR:
		status = listVar();
		break;
	case CMD_FUN:
		status = listFunc();
		break;
	case CMD_LOAD:
		fileName = i_scanner.getSymbol();
		status = load(fileName);
		break;
	case CMD_SAVE:
		status = save(fileName);
		break;
	default:
		std::cout << "Unknow Command \"" << i_cmdName << "\"." << std::endl;
		status = STATUS_ERROR;
	}
	return status;
}

Status CommandParser_T::help() const
{
	std::cout << "Recognized commands: " << std::endl;
	std::cout << "!help" << std::endl;
	std::cout << "!quit" << std::endl;
	std::cout << "!v" << std::endl;
	std::cout << "!f" << std::endl;
	std::cout << "!load filename" << std::endl;
	std::cout << "!save filename" << std::endl;
	return STATUS_OK;
}

Status CommandParser_T::listVar() const
{
	std::cout << "variable list:" << std::endl;
	i_calc.listVar();
	return STATUS_OK;
}

Status CommandParser_T::listFunc() const
{
	std::cout << "function list:" << std::endl;
	i_calc.listFunc();
	return STATUS_OK;
}

const long f_version = 1;	//°æ±¾ºÅ

Status CommandParser_T::load(const std::string& fileName)
{
	std::cout << "load : \"" << fileName << "\"." << std::endl;
	Status status = STATUS_OK;
	try
	{
		DeSerializer_T in(fileName);
		long ver;
		in >> ver;
		if (ver != f_version)
			throw Excetion_T("Miss match version.");
		i_calc.deSerialize(in);
	}
	catch (FileStreamError_T& f)
	{
		std::cout << "Load Error:" << f.what() << std::endl;
		status = STATUS_ERROR;
	}
	catch (Excetion_T& e)
	{
		std::cout << "Load Error:" << e.what() << std::endl;
		status = STATUS_ERROR;
	}

	return status;
}

Status CommandParser_T::save(const std::string& fileName)
{
	std::cout << "save : \"" << fileName << "\"." << std::endl;
	Status status = STATUS_OK;
	try
	{
		Serializer_T out(fileName);
		out << f_version;
		i_calc.serialize(out);
	}
	catch (FileStreamError_T& f)
	{	
		status = STATUS_ERROR;
		std::cout << "Save Error:" << f.what() << std::endl;
	}
	catch (Excetion_T& e)
	{	
		status = STATUS_ERROR;
		std::cout << "Save Error:" << e.what() << std::endl;
	}

	return status;
}