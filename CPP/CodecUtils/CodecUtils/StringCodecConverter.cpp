#include "StringCodecConverter.h"
#include <windows.h>

namespace CodecUtils
{
CStringCodecConverter::CStringCodecConverter(void)
{
}


CStringCodecConverter::~CStringCodecConverter(void)
{
}

void CStringCodecConverter::GbToUtf8(std::string& sGb, std::string& sUtf8)
{
	if(sGb.length() < 1)
		return;

	//prepare utf-16 buffer;
	int iUtf16Chrs = ::MultiByteToWideChar(CP_ACP, 0, sGb.c_str(), -1, NULL, 0);
	iUtf16Chrs += 1;//一定要加1，不然会出现尾巴;
	wchar_t *szUtf16 = new wchar_t[iUtf16Chrs];
	wmemset(szUtf16, 0, iUtf16Chrs);

	//GB --> UTF-16;
	::MultiByteToWideChar(CP_ACP, 0, sGb.c_str(), sGb.length(), szUtf16, iUtf16Chrs);

	//prepare utf-8 buffer;
	int iUtf8Chrs = ::WideCharToMultiByte(CP_UTF8, 0, szUtf16, -1, NULL, NULL, NULL, NULL);
	iUtf8Chrs += 1;
	char *szUtf8 = new char[iUtf8Chrs];
	memset(szUtf8, 0, iUtf8Chrs);

	//UTF-16 --> UTF-8;
	::WideCharToMultiByte(CP_UTF8, 0, szUtf16, iUtf16Chrs, szUtf8, iUtf8Chrs, NULL, NULL);

	sUtf8 = szUtf8;
	delete[] szUtf16;
	delete[] szUtf8;
}

void CStringCodecConverter::Utf8ToGb(std::string& sUtf8, std::string& sGb)
{
	if(sUtf8.size() < 1)
		return;

	//prepare UTF-16 buffer;
	int iUtf16Chrs = ::MultiByteToWideChar(CP_UTF8, 0, sUtf8.c_str(), -1, NULL, 0);
	iUtf16Chrs += 1;
	wchar_t *szUtf16 = new wchar_t[iUtf16Chrs];//一定要加1，不然会出现尾巴
	wmemset(szUtf16, 0, iUtf16Chrs);

	//UTF-8 --> UTF-16;
	MultiByteToWideChar(CP_UTF8, 0, sUtf8.c_str(), sUtf8.length(), szUtf16, iUtf16Chrs);

	//prepare GB buffer;
	int iGbChrs = WideCharToMultiByte(CP_ACP, 0, szUtf16, -1, NULL, NULL, NULL, NULL);
	iGbChrs += 1;
	char *szGb = new char[iGbChrs];
	memset(szGb, 0, iGbChrs);

	//UTF-16 --> GB;
	WideCharToMultiByte(CP_ACP, 0, szUtf16, iUtf16Chrs, szGb, iGbChrs, NULL, NULL);

	sGb = szGb;
	delete[] szUtf16;
	delete[] szGb;
}

void CStringCodecConverter::Utf16ToUtf8(std::string& sUtf16, std::string& sUtf8)
{

}

void CStringCodecConverter::Utf8ToUtf16(std::string& sUtf8, std::string& sUtf16)
{

}

}