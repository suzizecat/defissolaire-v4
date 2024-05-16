/*
 * IOBuffer.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: julien
 */

#include <IOBufferTX.h>
namespace sool::io
{

	IOBufferTX::IOBufferTX(char* aBuff, unsigned int aSize) : _buffer(aBuff),
			_buf_size(aSize),
			_rd_position(0),
			_wr_position(0),
			_empty(true),
			_full(false),
			_on_full_handler(nullptr),
			_on_send_all(nullptr),
			_on_send_byte(nullptr),
			_send_on_ovf(true)
	{
		clear();
	}

	void IOBufferTX::put(const char aChar)
	{
		if(_full)
			clear();
		if(_wr_position < _buf_size)
		{
			_buffer[_wr_position] = aChar;
			_wr_position ++;
			_empty = false;
		}

		_full = _wr_position == _buf_size;
		if(_full)
		{
			if(_on_full_handler != nullptr)
			{
				_on_full_handler(*this, &(_buffer[_rd_position]),_buf_size - _rd_position);
			}
			else if(_send_on_ovf)
			{
				send_all();
			}
		}


 	}

	void IOBufferTX::put(const char* aString, bool stop_on_full)
	{
		int i = 0;
		while(aString[i] != 0 && (! stop_on_full || ! _full))
		{
			put(aString[i]);
			i++;
		}
	}

	void IOBufferTX::print(const char aChar)
	{
		put(aChar);
		send();
	}

	void IOBufferTX::print(const char* aString)
	{
		put(aString);
		send_all();
	}

	char IOBufferTX::send()
	{
		char ret = 0;
		if(! _empty)
		{
			ret = _buffer[_rd_position];
			if(_on_send_byte != nullptr)
				_on_send_byte(ret);
			_rd_position ++;
			_empty = _rd_position == _wr_position;
		}

		if(_empty)
			clear(true);
		return ret;
	}
	void IOBufferTX::clear(bool partial)
	{
		for(int i = 0; i < (partial ? _wr_position : _buf_size); i++)
			_buffer[i] = 0;
		_wr_position = 0;
		_rd_position = 0;
		_empty = true;
		_full = false;

	}

	 void IOBufferTX::send_all()
	{
		 if(_on_send_all != nullptr)
		 {
			 _on_send_all(*this,&(_buffer[_rd_position]),_wr_position - _rd_position);
			 clear(true);
		 }
		 else
		 {
			 while(! _empty)
				 send();
		 }

	}


}


