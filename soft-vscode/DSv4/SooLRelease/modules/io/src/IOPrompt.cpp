/*
 * IOPrompt.cpp
 *
 *  Created on: 7 juil. 2020
 *      Author: julien
 */



#include "../include/IOPrompt.h"
#include "../include/IOCstring.h"
#include "cstring"
namespace sool::io
{
	IOPrompt::IOPrompt(IOBufferRX& aRX, IOBufferTX& aTX) : _rx(aRX),
			_tx(aTX),
			_cmd_list(nullptr),
			_prompt{0},
			_validated(false),
			_argn(0),
			_errno(0)
	{
		set_prompt("> ");
		for(int i = 0; i < IOPROMPT_MAX_ARGN; i++)
			for(int j =0; j< IOPROMPT_MAX_ARGLEN;j++)
				_argv[i][j] = 0;

	}

	/*IOPrompt::~IOPrompt()
	{
		IOPromptCmd* curr = _cmd_list;
		IOPromptCmd* next;
		while(curr != nullptr)
		{
			next = curr->_nextPtr;
			delete curr;
			curr = next;
		}
	}*/

	void IOPrompt::init()
	{
		_rx.set_validator(&IOPrompt::_rx_validator,this);
	}

	void IOPrompt::prompt()
	{
		_tx << "\n" << _prompt;
		_tx.send_all();
	}
	void IOPrompt::register_cmd(IOPromptCmd* aCmd)
	{
		if(_cmd_list == nullptr)
			_cmd_list = aCmd;
		else
		{
			IOPromptCmd* cmd = _cmd_list;
			while(cmd->_nextPtr != nullptr)
			{
				cmd = cmd->_nextPtr;
			}
			cmd->_nextPtr = aCmd;
		}
	}

	/*void IOPrompt::register_cmd(const char* name, const IOPromptCmd::CmdHandler_t aHandler)
	{
		if(_cmd_list == nullptr)
			_cmd_list = new IOPromptCmd(name,aHandler);
		else
		{
			IOPromptCmd* cmd = _cmd_list;
			while(cmd->_nextPtr != nullptr)
			{
				cmd = cmd->_nextPtr;
			}
			cmd->_nextPtr = new IOPromptCmd(name,aHandler);
		}
	}*/

	void IOPrompt::set_prompt(const char* aPrompt)
	{
		bool eop = false;
		for(int i = 0; i < 10; i++)
		{
			if(! eop)
			{
				_prompt[i] = aPrompt[i];
				eop = aPrompt[i] == 0;
			}
			else
				_prompt[i] = 0;
		}
		_prompt[10] = 0;
	}
	void IOPrompt::clear()
	{
		for(int i = 0; i < _argn; i++)
		{
			for(int j = 0; j < IOPROMPT_MAX_ARGLEN; j++)
				_argv[i][j] = 0;
		}
		_argn = 0;
	}

	int IOPrompt::_rx_validator(IOBufferRX& aRX,char aChar)
	{
		if(aChar == '\r')
		{
			aRX.replace_last(' ');
			aRX.lock();
			_validated = true;
			return 1;
		}
		if(aRX.match("\e[A"))
		{
			recall();
			return 1;
		}

		return 0;
	}

	void IOPrompt::_process_args()
	{

		_rx.transfer(_cmdline);
		char last_c = ' ';
		char c;
		int i = 0;

		clear();
		//Counting words
		while(_cmdline[i] != 0)
		{
			c = _cmdline[i];
			i++;
			if(c != ' ' && last_c == ' ') //New word
			{
				_argn ++;
			}
			last_c = c;
		}
		if(_argn > 0)
		{
			//Splitting words
			i = 0;
			last_c = ' ';
			int word_i = 0;
			int word_start = 0;
			int word_length= 0;

			while(_cmdline[i] != 0)
			{
				c = _cmdline[i];

				if(c != ' ' && last_c == ' ') //Start of word
				{
					word_start = i;
					word_length = 1;
				}
				else if(c == ' ' && last_c != ' ') //End of word
				{
					strcpy(&(_cmdline[word_start]),_argv[word_i],word_length);
					_argv[word_i][word_length] = 0;

					word_i ++;
				}
				else if(c != ' ' && last_c != ' ')
				{
					word_length ++;
				}
				i++;
				last_c = c;
			}
		}
	}

	IOPromptCmd* IOPrompt::_select_cmd(const char* aCmd) const
	{
		IOPromptCmd* cmd = _cmd_list;
		while(cmd != nullptr)
		{
			if(streq(aCmd, cmd->_name))
				break;
			cmd = cmd->_nextPtr;
		}
		return cmd;

	}

	void IOPrompt::process()
	{
		if(! _validated)
			return;

		_process_args();

		if(_argn > 0)
		{
			_tx.put('\n');
			IOPromptCmd* cmd = _select_cmd(_argv[0]);
			if(cmd != nullptr)
				_errno = cmd->call(_argn, _argv);
			else
			{
				_tx << "Unknown command " << _argv[0];
				_tx.send_all();
				_errno = -1;
			}
		}

		_validated = false;
		_rx.clear();
		_rx.unlock();
		prompt();
	}

	void IOPrompt::recall()
	{
		strendstrip(_cmdline, ' ');
		_tx << "\r" << _prompt << _cmdline;
		_tx.send_all();
		_rx.set(_cmdline);
	}
}
