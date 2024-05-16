/*
 * IOPromptCmd.cpp
 *
 *  Created on: 7 juil. 2020
 *      Author: julien
 */




#include "../include/IOPromptCmd.h"
#include "../include/IOCstring.h"
#include <malloc.h>


namespace sool::io
{
	IOPromptCmd::IOPromptCmd(const char* aName,CmdHandler_t aHandler  ) : _handler(aHandler),_nextPtr(nullptr)
	{
		strcpy(aName,_name);
	}

	/*IOPromptCmd::IOPromptCmd(const IOPromptCmd& aCmd ) : _nextPtr(nullptr)
	{
		_name = aCmd._name;
		_handler = aCmd._handler;
	}*/

	int IOPromptCmd::call(int argn,  char argv[IOPROMPT_MAX_ARGN][IOPROMPT_MAX_ARGLEN]) const
	{
		if(_handler != nullptr)
			return _handler(argn,argv);
		else
			return -1;
	}
}
