/*
 * IORXCmd.h
 *
 *  Created on: 7 juil. 2020
 *      Author: julien
 */

#ifndef MODULES_IO_INCLUDE_IOBUFFERRX_H_
#define MODULES_IO_INCLUDE_IOBUFFERRX_H_

namespace sool::io
{
	class IOPrompt;
	class IOBufferRX
	{
	public:
		/**
		 * Create a receiver buffer handler pointing on the given buffer with the given size.
		 * @param aBuffer Pointer to the receiver buffer.
		 * @param aSize Size in char (bytes) of the given buffer.
		 */
		explicit IOBufferRX(char* aBuffer,const unsigned int aSize);

		/**
		 * Empty the buffer and reset all internal pointers
		 */
		void clear();

		/**
		 * Add the given character at the end of the buffer content.
		 * @param aChar Character to add
		 * @return True upon success.
		 */
		bool put(const char aChar);
		bool set(const char* aContent);

		bool match(const char* aPattern) const;
		void transfer(char* aNewBuffer);

		inline void notify_transfer_done();
		void wait_for_transfer_done() const;

		inline void lock();
		inline void unlock();

		inline void set_validator(int  (*aFunc)      (IOBufferRX& self, char aChar));
		inline void set_validator(int  (IOPrompt::*aFunc)      (IOBufferRX& self, char aChar),IOPrompt* aPrompt);

		inline void set_on_valid_input(void (*aFunc) (IOBufferRX& self, int validatorOutput));

		inline int get_buffer_size() const;
		inline void replace_last(const char aChar);

	protected :
		char * _buffer;
		unsigned int _buf_size;

		bool _empty;
		bool _full;
		bool _locked;

		bool _validated;

		//unsigned int _rd_position;
		unsigned int _wr_position;

		volatile bool _transfer_ongoing;

		IOPrompt* _linked_prompt;

		int  (*_validator)      (IOBufferRX& self, char aChar);
		int  (IOPrompt::*_validator_prompt)      (IOBufferRX& self, char aChar);
		void (*_on_valid_input) (IOBufferRX& self, int validatorOutput);
		void (*_on_full_handler)(IOBufferRX& self, char* aBuffer, unsigned int aSize);
		bool (*_transfer_handler)(const char* srcBuffer,const unsigned int aSize, char* aNewBuffer);


	};

	inline void IOBufferRX::notify_transfer_done()
	{
		_transfer_ongoing = false;
	}

	inline void IOBufferRX::set_validator(int  (*aFunc)      (IOBufferRX& self, char aChar))
	{
		_validator = aFunc;
	}
	inline void IOBufferRX::set_validator(int  (IOPrompt::*aFunc)      (IOBufferRX& self, char aChar), IOPrompt* aPrompt)
	{
		_validator_prompt = aFunc;
		_linked_prompt = aPrompt;
	}

	inline void IOBufferRX::set_on_valid_input(void (*aFunc) (IOBufferRX& self, int validatorOutput))
	{
		_on_valid_input = aFunc;
	}

	inline void IOBufferRX::lock()
	{
		_locked = true;
	}

	inline void IOBufferRX::unlock()
	{
		_locked = false;
	}

	inline int IOBufferRX::get_buffer_size() const
	{
		return _wr_position + 1;
	}

	inline void IOBufferRX::replace_last(const char aChar)
	{
		if(_wr_position > 0)
		{
			_buffer[_wr_position-1] = aChar;
		}
	}
}



#endif /* MODULES_IO_INCLUDE_IOBUFFERRX_H_ */
