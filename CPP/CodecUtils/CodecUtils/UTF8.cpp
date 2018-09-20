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

	//���ֽ����λ:
	//	0:
	//		ASCII�ַ�, ����ΪUTF-8����, Ҳ���ܲ���(���е��ַ���Ӧ�ö������ASCII);
	//	1:
	//		����ΪGB18030-2005�ַ�, ����ΪUTF-8�ַ�;

	//����ٶȺ�׼ȷ��, �������5����ASCII�ַ�����UTF-8�ı������, ����Ϊ��UTF-8����;

	const int kJudgeNoneAsciiChrs = 5;
	const int iStrLen = strlen(szText);
	int iCheckedNoneAsciiChrs = 0;
	for(int i = 0; i < iStrLen; )
	{
		unsigned char chr = szText[i];
		if(0 != (chr & 0x80))//"1";
		{
			if(0x02 == (chr>>6))//UTF-8�������һ���ַ������ֽ���"10"��ͷ;
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

			if(iChrBytes < 2 || iChrBytes > 6)//UTF-8һ���ַ�ռ�õ��ֽ���:1-6;
				return false;

			while(--iChrBytes)
			{
				++i;
				if(i > iStrLen-1)//��֤��Խ���������Ԫ��;
					return false;

				if(0x02 != (((unsigned char)szText[i]) >> 6))//������"10"��ͷ;
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