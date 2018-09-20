#include "TestRc4.h"
#include "rc4.h"
#include <iostream>
#include <direct.h>
#include <fstream>

CTestRc4::CTestRc4(void)
{
}


CTestRc4::~CTestRc4(void)
{
}

void CTestRc4::Go()
{
	//CodecUtils::ANYMACRO_RC4 已在闪信中测试完成, 由于时间关系, 这里不做测试;
	//..


	CodecUtils::RC4 oRc4;
	const std::string kStrOri = "cryptlib和OpenSSL是基于\"Eric Young\"的代码，cryptopp源于\"Phil Karn\"的des.c。\
								在输入相同的情况下，LibTomCrypt与KARN_portable产生的key schedule完全一致。\
								这些公开的库必须是符合DES标准的，所以同样的输入得到相同的输出。";
	const std::string kStrKey = "alex0221";
	unsigned char *szEnc = nullptr, *szDec = nullptr;

	std::cout<<"***************************************"<<std::endl;
	std::cout<<"字符串加解密测试CASE 1: 不修改原字符串"<<std::endl;
	std::cout<<"***************************************"<<std::endl;

	std::cout<<"原字符串:"<<std::endl<<kStrOri<<std::endl<<std::endl<<std::endl;

	oRc4.Crypt((unsigned char*)kStrOri.c_str(), szEnc, kStrOri.length(), kStrKey.c_str(), kStrKey.length());
	std::cout<<"加密后的字符串:	"<<std::endl;
	for(int i = 0; i < kStrOri.length(); ++i)//注意: 加密后的字符串内容区可能包含'\0',这样就无法正确赋值给一个std::string了, 所以当成字节数组处理才是正确的方式!
		std::cout<<(char)szEnc[i];
	std::cout<<std::endl<<std::endl<<std::endl;

	oRc4.Crypt((unsigned char*)szEnc, szDec, kStrOri.length(), kStrKey.c_str(), kStrKey.length());
	std::cout<<"解密后的字符串:	"<<std::endl;
	for(int i = 0; i < kStrOri.length(); ++i)//注意: 加密后的字符串内容区可能包含'\0',这样就无法正确赋值给一个std::string了, 所以当成字节数组处理才是正确的方式!
		std::cout<<(char)szDec[i];
	std::cout<<std::endl<<std::endl<<std::endl;

	{
		std::cout<<"***************************************"<<std::endl;
		std::cout<<"字符串加解密测试CASE 2: 覆盖原字符串"<<std::endl;
		std::cout<<"***************************************"<<std::endl;

		const int iDataLen = kStrOri.length()+1;
		char* szCopy = new char[iDataLen];
		memset(szCopy, 0, iDataLen);
		memcpy(szCopy, kStrOri.c_str(), iDataLen);
		oRc4.Crypt((unsigned char*)szCopy, iDataLen, kStrKey.c_str(), kStrKey.length());
		std::cout<<"加密后的字符串:	"<<std::endl;
		std::cout<<szCopy;
		std::cout<<std::endl<<std::endl<<std::endl;

		oRc4.Crypt((unsigned char*)szCopy, iDataLen, kStrKey.c_str(), kStrKey.length());
		std::cout<<"解密后的字符串:	"<<std::endl;
		std::cout<<szCopy;
		std::cout<<std::endl<<std::endl<<std::endl;


		delete szCopy;
	}

	const int kPathMaxLen = 260;
	char szPath[kPathMaxLen] = {0};
	_getcwd(szPath, kPathMaxLen);//IDE下的调试状态,是在工程目录下; 单独exe运行状态, 是在exe目录.
	//std::cout<<szPath<<std::endl;
	const std::string kFileKey = "anymacro";

	{
		std::cout<<"***************************************"<<std::endl;
		std::cout<<"文件加解密测试CASE 3: 不修改原文件"<<std::endl;
		std::cout<<"***************************************"<<std::endl;

		std::string sSrcFile,sDstFile;
		sSrcFile = szPath;
		sSrcFile += "\\testdata\\1_ori.html";
		sDstFile = szPath;
		sDstFile += "\\testdata\\1_enc.html";

		std::cout<<"正在加密文件..\n";
		oRc4.Crypt(sSrcFile.c_str(), sDstFile.c_str(), kFileKey.c_str(), kFileKey.length());

		std::cout<<"正在解密文件..\n";
		sSrcFile = sDstFile;
		sDstFile = szPath;
		sDstFile += "\\testdata\\1_dec.html";
		oRc4.Crypt(sSrcFile.c_str(), sDstFile.c_str(), kFileKey.c_str(), kFileKey.length());

		std::cout<<"解密完毕.\n\n";
	}


	{
		std::cout<<"***************************************"<<std::endl;
		std::cout<<"文件加解密测试CASE 4: 修改原文件"<<std::endl;
		std::cout<<"***************************************"<<std::endl;

		std::string sSrcFile, sCopyFile;
		sSrcFile = szPath;
		sSrcFile += "\\testdata\\1_ori.html";
		sCopyFile = szPath;
		sCopyFile += "\\testdata\\1_copy.html";
		remove(sCopyFile.c_str());

		std::ifstream fOri(sSrcFile);
		std::ofstream fCopy(sCopyFile);
		fCopy<<fOri.rdbuf();
		fOri.close();
		fCopy.close();

		std::cout<<"正在加密文件..\n";
		oRc4.Crypt(sCopyFile.c_str(), kFileKey.c_str(), kFileKey.length());

		std::cout<<"正在解密文件..\n";
		oRc4.Crypt(sCopyFile.c_str(), kFileKey.c_str(), kFileKey.length());

		std::cout<<"解密完毕.\n\n";
	}
	
}