#include "../include/IOcstring.h"

namespace sool::io
{
	void strcpy(const char* src,char* dst, const unsigned int len)
	{
		int i = 0;
		while((len && i < len) || src[i] != 0)
		{
			dst[i] = src[i];
			i++;
		}
		if(!len)
			dst[i] = 0;
	}

	void strendstrip(char* str, char toStrip)
	{
		int i = strlen(str)-1;
		while(i > 0 && str[i] == toStrip)
			str[i] = 0;
	}

}
