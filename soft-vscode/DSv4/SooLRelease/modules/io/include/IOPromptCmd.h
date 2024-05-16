/*
 * IOPromptCmd.h
 *
 *  Created on: 7 juil. 2020
 *      Author: julien
 */

#ifndef MODULES_IO_INCLUDE_IOPROMPTCMD_H_
#define MODULES_IO_INCLUDE_IOPROMPTCMD_H_

#include "IOsetup.h"

namespace sool::io
{
class IOPromptCmd
	{
	friend class IOPrompt;
	public:
		typedef int (*CmdHandler_t)(int argn, argv_t argv);

		explicit IOPromptCmd(const char* aName,CmdHandler_t aCmd  );

		//IOPromptCmd(const IOPromptCmd& aCmd);

		int call(int argn, argv_t argv) const;

	protected:
		IOPromptCmd* _nextPtr;
		char _name[IOPROMPT_MAX_ARGLEN];
		int (*_handler)(int argn, argv_t argv);
	};
}

#endif /* MODULES_IO_INCLUDE_IOPROMPTCMD_H_ */
