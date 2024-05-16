/*
 * IOcstring.h
 *
 *  Created on: 7 juil. 2020
 *      Author: julien
 */

#ifndef MODULES_IO_INCLUDE_IOCSTRING_H_
#define MODULES_IO_INCLUDE_IOCSTRING_H_

namespace sool::io
{
	void strcpy(const char* src,char* dst,const unsigned int len = 0);
	constexpr int strlen(const char* aString)
	{
		int len = 0;
		while(aString[len] != 0)
			len++;
		return len;
	};

	constexpr bool streq(const char* s1,const char* s2)
		{
			int i = 0;
			while(s1[i] != 0)
			{
				if(s1[i] != s2[i])
					return false;
				i++;
			}
			return s1[i] == s2[i];
		};

	constexpr int str2i(const char* s)
	{
		int out = 0;
		bool reverse = false;
		for(int i = 0; i < strlen(s); i++)
		{
			if(i == 0 && s[i] == '-')
				reverse = !reverse;
			else if(s[i] < '0' || s[i] > '9' )
				break;
			out *= 10;
			out += s[i] - '0';
		}
		return reverse ? -out : out;
	}

	void strendstrip(char* str, char toStrip);
}

#endif /* MODULES_IO_INCLUDE_IOCSTRING_H_ */
