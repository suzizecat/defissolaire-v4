/*
 * IOPrompt.h
 *
 *  Created on: 7 juil. 2020
 *      Author: julien
 */

#ifndef MODULES_IO_INCLUDE_IOPROMPT_H_
#define MODULES_IO_INCLUDE_IOPROMPT_H_

#include "IOsetup.h"
#include "./IOBufferRX.h"
#include "./IOBufferTX.h"
#include "./IOPromptCmd.h"
namespace sool::io
{
	class IOPrompt
	{

	public:
		/**
		 * The IOPrompt constructor. It takes in parameter an input and an output
		 * flow handlers, already set up with the hardware handlers.
		 * The Rx handler will get a dedicated validator, overriding any validator previously set up.
		 *
		 * @param aRX The ingoing flow handler.
		 * @param aTX The outgoing flow handler.
		 */
		explicit IOPrompt(IOBufferRX& aRX, IOBufferTX& aTX);
		//~IOPrompt();
		/**
		 * Perform some remaining tasks after constructor.
		 * MUST be called before process().
		 *
		 * In particular, this function set the Rx validator function.
		 */
		void init();

		/**
		 * Register an IOPromptCmd to be available in the prompt.
		 * @param aCmd Command wrapper to add to the prompt.
		 */
		void register_cmd(IOPromptCmd* aCmd);

		/**
		 * Set the message shown each time the user is prompted.
		 * @param aPrompt A new prompt
		 */
		void set_prompt(const char* aPrompt);

		/**
		 * Display the prompt message
		 */
		void prompt();

		/**
		 * Clear the screen and place the cursor at home position.
		 * Display prompt afterward.
		 */
		void clear();

		/**
		 * If content have been validated, will split the arguments and call the appropriate command.
		 */
		void process();

		void recall();
	protected:


		IOBufferRX& _rx;
		IOBufferTX& _tx;

		IOPromptCmd* _cmd_list;

		char _prompt[11];
		bool _validated;

		char _cmdline[IOPROMPT_MAX_CMDLEN];
		argv_t _argv;
		int _argn;
		int _errno;

		void _process_args();
		IOPromptCmd* _select_cmd(const char* cmd) const ;
		int _rx_validator(IOBufferRX& aRX,char aChar);

	};
}


#endif /* MODULES_IO_INCLUDE_IOPROMPT_H_ */
