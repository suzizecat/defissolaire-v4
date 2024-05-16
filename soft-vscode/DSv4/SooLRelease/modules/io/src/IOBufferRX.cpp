/*
 * IOBufferRX.cpp
 *
 *  Created on: 7 juil. 2020
 *      Author: julien
 */

#include "../include/IOBufferRX.h"

namespace sool::io
{
	IOBufferRX::IOBufferRX(char* aBuffer, const unsigned int aSize) : _buffer(aBuffer),
			_buf_size(aSize),
			_validator(nullptr),
			_validator_prompt(nullptr),
			_on_full_handler(nullptr),
			_on_valid_input(nullptr),
			_transfer_handler(nullptr),
			_locked(false),
			_validated(false)
	{
		clear();
	}

	void IOBufferRX::clear()
	{
		for(unsigned int i = 0; i < _buf_size; i++)
			_buffer[i] = 0;
		_wr_position = 0;
		_empty = true;
		_full = false;
		_transfer_ongoing = false;
	}

	bool IOBufferRX::put(const char aChar)
	{
		_validated = false;
		if(_locked)
			return false;
		if(aChar == 127) //Backspace (DEL)
		{
			if(! _empty)
			{
				_wr_position --;
				_buffer[_wr_position] = 0;
				_full = (_wr_position == _buf_size);
				_empty = ! _wr_position;

			}
			return true;
		}

		if(_full)
			return false;

		_buffer[_wr_position] = aChar;
		_wr_position ++;
		_empty = false;

		_full = (_wr_position == _buf_size);

		int validator_output;
		if(_validator_prompt != nullptr)
		{
			validator_output = (_linked_prompt->*_validator_prompt)(*this,aChar);
			if(validator_output)
			{
				_validated = true;
				if(_on_valid_input != nullptr)
					_on_valid_input(*this,validator_output);
			}

		}
		else if(_validator != nullptr)
		{
			validator_output = _validator(*this,aChar);
			if(validator_output)
			{
				_validated = true;
				if(_on_valid_input != nullptr)
					_on_valid_input(*this,validator_output);
				else
					clear();
			}
		}

		if(_full && _on_full_handler != nullptr)
			_on_full_handler(*this,_buffer,_buf_size);

		return true;
	}

	bool IOBufferRX::set(const char* aContent)
	{
		clear();
		int i =0;
		while(aContent[i] != 0)
		{
			if(put(aContent[i++]))
			{
				if(_validated)
					return true;
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	bool IOBufferRX::match(const char* aPattern) const
	{
		int i = 0;
		while( aPattern[i] != 0 && i < _buf_size)
		{
			if(aPattern[i] != _buffer[i])
				return false;
			i ++;
		}
		return true;
	}

	void IOBufferRX::transfer(char* aNewBuffer)
	{
		_transfer_ongoing = true;
		if(_transfer_handler != nullptr)
		{
			_transfer_handler(_buffer,_wr_position,aNewBuffer);
		}
		else
		{
			for(int i = 0; i < _wr_position; i++)
			{
				aNewBuffer[i] = _buffer[i];
			}
			aNewBuffer[_wr_position] = 0;
			_transfer_ongoing = false;
		}
	}

	void IOBufferRX::wait_for_transfer_done() const
	{
		while(_transfer_ongoing)
			asm("nop");
	}

}


