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
		std::string sGb = "UTF-8��8-bit Unicode Transformation Format����һ�����Unicode�Ŀɱ䳤���ַ����루�����룩��Ҳ��һ��ǰ׺�롣������������ʾUnicode��׼�е��κ��ַ�����������еĵ�һ���ֽ�����ASCII���ݣ���ʹ��ԭ������ASCII�ַ�����������ֻ�����ٲ����޸ģ����ɼ���ʹ�á���ˣ����𽥳�Ϊ�����ʼ�����ҳ�������洢�������ֵ�Ӧ���У����Ȳ��õı��롣���������̹���С�飨IETF��Ҫ�����л�����Э�鶼����֧��UTF-8���롣";
		std::cout<<"�ַ���:"<<std::endl;
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
		std::cout<<"�ַ���:"<<std::endl;
		std::cout<<sGb<<std::endl;
		bool bIsUtf8 = CodecUtils::CUTF8::IsTextUtf8(sGb.c_str());
		if(bIsUtf8)
			std::cout<<"YES."<<std::endl;
		else
			std::cout<<"NO."<<std::endl;
	}
	std::cout<<std::endl<<std::endl;
	{
		std::string sGb = "UTF-8��8-bit Unicode Transformation Format����һ�����Unicode�Ŀɱ䳤���ַ����루�����룩��Ҳ��һ��ǰ׺�롣������������ʾUnicode��׼�е��κ��ַ�����������еĵ�һ���ֽ�����ASCII���ݣ���ʹ��ԭ������ASCII�ַ�����������ֻ�����ٲ����޸ģ����ɼ���ʹ�á���ˣ����𽥳�Ϊ�����ʼ�����ҳ�������洢�������ֵ�Ӧ���У����Ȳ��õı��롣���������̹���С�飨IETF��Ҫ�����л�����Э�鶼����֧��UTF-8���롣";
		std::string sUtf8;
		CodecUtils::CStringCodecConverter::GbToUtf8(sGb,sUtf8);
		std::cout<<"�ַ���:"<<std::endl;
		std::cout<<sUtf8<<std::endl;
		bool bIsUtf8 = CodecUtils::CUTF8::IsTextUtf8(sUtf8.c_str());
		if(bIsUtf8)
			std::cout<<"YES."<<std::endl;
		else
			std::cout<<"NO."<<std::endl;

		std::cout<<std::endl<<std::endl;

		CodecUtils::CStringCodecConverter::Utf8ToGb(sUtf8, sGb);
		std::cout<<"�ַ���:"<<std::endl;
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
