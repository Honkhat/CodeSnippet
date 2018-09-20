#include "UTF8.h"
#include <string>



namespace CodecUtils
{
CUTF8::CUTF8(void)
{
}


CUTF8::~CUTF8(void)
{
}

bool CUTF8::IsTextUtf8(const char* szText)
{
	if(!szText || strlen(szText) < 1)
		return false;

	//首字节最高位:
	//	0:
	//		ASCII字符, 可能为UTF-8编码, 也可能不是(所有的字符集应该都会兼容ASCII);
	//	1:
	//		可能为GB18030-2005字符, 可能为UTF-8字符;

	//兼顾速度和准确性, 如果连续5个非ASCII字符符合UTF-8的编码规则, 即认为是UTF-8编码;

	const int kJudgeNoneAsciiChrs = 5;
	const int iStrLen = strlen(szText);
	int iCheckedNoneAsciiChrs = 0;
	for(int i = 0; i < iStrLen; )
	{
		unsigned char chr = szText[i];
		if(0 != (chr & 0x80))//"1";
		{
			if(0x02 == (chr>>6))//UTF-8不会出现一个字符的首字节以"10"开头;
				return false;

			int iChrBytes = 0;
			if(chr >= 0xfc && chr < 0xfe)
				iChrBytes = 6;
			else if(chr >= 0xf8)
				iChrBytes = 5;
			else if(chr >= 0xf0)
				iChrBytes = 4;
			else if(chr >= 0xe0)
				iChrBytes = 3;
			else if(chr >= 0xc0)
				iChrBytes = 2;

			if(iChrBytes < 2 || iChrBytes > 6)//UTF-8一个字符占用的字节数:1-6;
				return false;

			while(--iChrBytes)
			{
				++i;
				if(i > iStrLen-1)//保证不越界访问数组元素;
					return false;

				if(0x02 != (((unsigned char)szText[i]) >> 6))//必须是"10"开头;
					return false;
			}
			++iCheckedNoneAsciiChrs;
			++i;
		}
		else//"0";
		{
			++i;
		}

		if(iCheckedNoneAsciiChrs >= kJudgeNoneAsciiChrs)
			break;
	}

	return true;
}

}