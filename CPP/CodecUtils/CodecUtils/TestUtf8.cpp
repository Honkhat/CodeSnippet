#include "TestUtf8.h"
#include <string>
#include <iostream>
#include "UTF8.h"
#include "StringCodecConverter.h"

namespace CodecUtils
{
CTestUtf8::CTestUtf8(void)
{
}


CTestUtf8::~CTestUtf8(void)
{
}

void CTestUtf8::Test_IsUtf8()
{
	std::cout<<"******************************"<<std::endl;
	std::cout<<"Test_IsUtf8()"<<std::endl;
	std::cout<<"******************************"<<std::endl;

	{
		std::string sGb = "UTF-8（8-bit Unicode Transformation Format）是一种针对Unicode的可变长度字符编码（定长码），也是一种前缀码。它可以用来表示Unicode标准中的任何字符，且其编码中的第一个字节仍与ASCII兼容，这使得原来处理ASCII字符的软件无须或只须做少部份修改，即可继续使用。因此，它逐渐成为电子邮件、网页及其他存储或传送文字的应用中，优先采用的编码。互联网工程工作小组（IETF）要求所有互联网协议都必须支持UTF-8编码。";
		std::cout<<"字符串:"<<std::endl;
		std::cout<<sGb<<std::endl;
		bool bIsUtf8 = CodecUtils::CUTF8::IsTextUtf8(sGb.c_str());
		if(bIsUtf8)
			std::cout<<"YES."<<std::endl;
		else
			std::cout<<"NO."<<std::endl;
	}
	std::cout<<std::endl<<std::endl;
	{
		std::string sGb = "UTF-8:8-bit Unicode Transformation Format";
		std::cout<<"字符串:"<<std::endl;
		std::cout<<sGb<<std::endl;
		bool bIsUtf8 = CodecUtils::CUTF8::IsTextUtf8(sGb.c_str());
		if(bIsUtf8)
			std::cout<<"YES."<<std::endl;
		else
			std::cout<<"NO."<<std::endl;
	}
	std::cout<<std::endl<<std::endl;
	{
		std::string sGb = "UTF-8（8-bit Unicode Transformation Format）是一种针对Unicode的可变长度字符编码（定长码），也是一种前缀码。它可以用来表示Unicode标准中的任何字符，且其编码中的第一个字节仍与ASCII兼容，这使得原来处理ASCII字符的软件无须或只须做少部份修改，即可继续使用。因此，它逐渐成为电子邮件、网页及其他存储或传送文字的应用中，优先采用的编码。互联网工程工作小组（IETF）要求所有互联网协议都必须支持UTF-8编码。";
		std::string sUtf8;
		CodecUtils::CStringCodecConverter::GbToUtf8(sGb,sUtf8);
		std::cout<<"字符串:"<<std::endl;
		std::cout<<sUtf8<<std::endl;
		bool bIsUtf8 = CodecUtils::CUTF8::IsTextUtf8(sUtf8.c_str());
		if(bIsUtf8)
			std::cout<<"YES."<<std::endl;
		else
			std::cout<<"NO."<<std::endl;

		std::cout<<std::endl<<std::endl;

		CodecUtils::CStringCodecConverter::Utf8ToGb(sUtf8, sGb);
		std::cout<<"字符串:"<<std::endl;
		std::cout<<sGb<<std::endl;
		bIsUtf8 = CodecUtils::CUTF8::IsTextUtf8(sGb.c_str());
		if(bIsUtf8)
			std::cout<<"YES."<<std::endl;
		else
			std::cout<<"NO."<<std::endl;
	}
	std::cout<<std::endl<<std::endl;
}
}
