#pragma once
#include <string>
/*
	@Date:		2018/09/13 11:00;
	@Author:	jian.he;
	@Mail:		worksdata@163.com;
	@Purpose:	ASCII/UTF-8/UTF-16..etc. Mutual convert.
*/

namespace CodecUtils
{
class CStringCodecConverter
{
public:
	CStringCodecConverter(void);
	~CStringCodecConverter(void);

	//GB[2312/K/18030-2000/18030-2005] <--> UTF-8;
	static void GbToUtf8(std::string& sGb, std::string& sUtf8);
	static void Utf8ToGb(std::string& sUtf8, std::string& sGb);
};
}

