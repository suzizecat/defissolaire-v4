#ifndef __SOOL_MODULE_IO_BUFFER
#define __SOOL_MODULE_IO_BUFFER


namespace sool::io
{
	class IOBufferTX
	{
	public:
		explicit IOBufferTX(char * aBuffer, const unsigned int aSize);
		void clear(const bool partial = false);

		void put(const char aChar);
		void put(const char* aString, bool stop_on_full= false);

		void print(const char aChar);
		void print(const char* aString);

		char send();
		void send_all();

		void set_on_full_handler(void (*aHandler)(IOBufferTX& caller, char* aBuff, unsigned int aSize));
		void set_on_send_all(    void (*aHandler)(IOBufferTX& caller, char* aBuff, unsigned int aSize));
		void set_on_send_byte(   void (*aHandler)(char aByte));

		void set_send_on_ovf(const bool aBool);



	protected:
		char* _buffer;
		const unsigned int _buf_size;

		unsigned int _rd_position;
		unsigned int _wr_position;

		bool _empty;
		bool _full;

		bool _send_on_ovf;

		void (*_on_full_handler)(IOBufferTX& caller, char* aBuff, unsigned int aSize);
		void (*_on_send_all)(IOBufferTX& caller, char* aBuff, unsigned int aSize);
		void (*_on_send_byte)(char aByte);
	};


	inline void IOBufferTX::set_on_full_handler(void (*aHandler)(IOBufferTX& caller, char* aBuff, unsigned int aSize))
	{
		_on_full_handler = aHandler;
	}

	inline void IOBufferTX::set_on_send_all(void (*aHandler)(IOBufferTX& caller, char* aBuff, unsigned int aSize))
	{
		_on_send_all = aHandler;
	}

	inline void IOBufferTX::set_on_send_byte(   void (*aHandler)(char aByte))
	{
		_on_send_byte = aHandler;
	}

	inline void IOBufferTX::set_send_on_ovf(const bool aBool)
	{
		_send_on_ovf = aBool;
	}

	template<typename T>
	IOBufferTX& operator<<(IOBufferTX& aTX, T aT)
	{
		aTX.put(aT);
		return aTX;
	}
}



#endif
