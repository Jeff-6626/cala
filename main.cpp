#include <iostream>
#include <memory>
#include "Parser_T.h"
#include "Scanner_T.h"
#include "Calc_T.h"
#include "DebugNew.h"
#include "Excetion_T.h"
#include "CommandParser_T.h"

int main( void )
{
	Calc_T clac;
	Status status = STATUS_OK;
	while (status != STATUS_QUIT)
	{
		Scanner_T scanner(std::cin);
		scanner.accept();
		if (scanner.isCommand())
		{
			CommandParser_T parser(scanner, clac);
			status = parser.execute();
			
		}
		else
		{
			Parser_T parser(scanner, clac);
			try
			{
				parser.parser();
				std::cout << parser.clac() << std::endl;
			}
			catch(Excetion_T& e)
			{
				std::cout << e.what() << std::endl;
			}
			catch(SyntaxError_T& s)
			{
				std::cout << s.what() << std::endl;
			}
			catch(FileStreamError_T& f)
			{
				std::cout << f.what() << std::endl;
			}
			catch (CheckNumberError& c)
			{
				std::cout << c.what() << std::endl;
			}
			catch(...)
			{
				std::cout << "others error" << std::endl;
			}
		}
		
	}
	
	return 0;
}