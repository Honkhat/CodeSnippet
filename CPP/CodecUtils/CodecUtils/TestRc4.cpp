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
	//CodecUtils::ANYMACRO_RC4 ���������в������, ����ʱ���ϵ, ���ﲻ������;
	//..


	CodecUtils::RC4 oRc4;
	const std::string kStrOri = "cryptlib��OpenSSL�ǻ���\"Eric Young\"�Ĵ��룬cryptoppԴ��\"Phil Karn\"��des.c��\
								��������ͬ������£�LibTomCrypt��KARN_portable������key schedule��ȫһ�¡�\
								��Щ�����Ŀ�����Ƿ���DES��׼�ģ�����ͬ��������õ���ͬ�������";
	const std::string kStrKey = "alex0221";
	unsigned char *szEnc = nullptr, *szDec = nullptr;

	std::cout<<"***************************************"<<std::endl;
	std::cout<<"�ַ����ӽ��ܲ���CASE 1: ���޸�ԭ�ַ���"<<std::endl;
	std::cout<<"***************************************"<<std::endl;

	std::cout<<"ԭ�ַ���:"<<std::endl<<kStrOri<<std::endl<<std::endl<<std::endl;

	oRc4.Crypt((unsigned char*)kStrOri.c_str(), szEnc, kStrOri.length(), kStrKey.c_str(), kStrKey.length());
	std::cout<<"���ܺ���ַ���:	"<<std::endl;
	for(int i = 0; i < kStrOri.length(); ++i)//ע��: ���ܺ���ַ������������ܰ���'\0',�������޷���ȷ��ֵ��һ��std::string��, ���Ե����ֽ����鴦�������ȷ�ķ�ʽ!
		std::cout<<(char)szEnc[i];
	std::cout<<std::endl<<std::endl<<std::endl;

	oRc4.Crypt((unsigned char*)szEnc, szDec, kStrOri.length(), kStrKey.c_str(), kStrKey.length());
	std::cout<<"���ܺ���ַ���:	"<<std::endl;
	for(int i = 0; i < kStrOri.length(); ++i)//ע��: ���ܺ���ַ������������ܰ���'\0',�������޷���ȷ��ֵ��һ��std::string��, ���Ե����ֽ����鴦�������ȷ�ķ�ʽ!
		std::cout<<(char)szDec[i];
	std::cout<<std::endl<<std::endl<<std::endl;

	{
		std::cout<<"***************************************"<<std::endl;
		std::cout<<"�ַ����ӽ��ܲ���CASE 2: ����ԭ�ַ���"<<std::endl;
		std::cout<<"***************************************"<<std::endl;

		const int iDataLen = kStrOri.length()+1;
		char* szCopy = new char[iDataLen];
		memset(szCopy, 0, iDataLen);
		memcpy(szCopy, kStrOri.c_str(), iDataLen);
		oRc4.Crypt((unsigned char*)szCopy, iDataLen, kStrKey.c_str(), kStrKey.length());
		std::cout<<"���ܺ���ַ���:	"<<std::endl;
		std::cout<<szCopy;
		std::cout<<std::endl<<std::endl<<std::endl;

		oRc4.Crypt((unsigned char*)szCopy, iDataLen, kStrKey.c_str(), kStrKey.length());
		std::cout<<"���ܺ���ַ���:	"<<std::endl;
		std::cout<<szCopy;
		std::cout<<std::endl<<std::endl<<std::endl;


		delete szCopy;
	}

	const int kPathMaxLen = 260;
	char szPath[kPathMaxLen] = {0};
	_getcwd(szPath, kPathMaxLen);//IDE�µĵ���״̬,���ڹ���Ŀ¼��; ����exe����״̬, ����exeĿ¼.
	//std::cout<<szPath<<std::endl;
	const std::string kFileKey = "anymacro";

	{
		std::cout<<"***************************************"<<std::endl;
		std::cout<<"�ļ��ӽ��ܲ���CASE 3: ���޸�ԭ�ļ�"<<std::endl;
		std::cout<<"***************************************"<<std::endl;

		std::string sSrcFile,sDstFile;
		sSrcFile = szPath;
		sSrcFile += "\\testdata\\1_ori.html";
		sDstFile = szPath;
		sDstFile += "\\testdata\\1_enc.html";

		std::cout<<"���ڼ����ļ�..\n";
		oRc4.Crypt(sSrcFile.c_str(), sDstFile.c_str(), kFileKey.c_str(), kFileKey.length());

		std::cout<<"���ڽ����ļ�..\n";
		sSrcFile = sDstFile;
		sDstFile = szPath;
		sDstFile += "\\testdata\\1_dec.html";
		oRc4.Crypt(sSrcFile.c_str(), sDstFile.c_str(), kFileKey.c_str(), kFileKey.length());

		std::cout<<"�������.\n\n";
	}


	{
		std::cout<<"***************************************"<<std::endl;
		std::cout<<"�ļ��ӽ��ܲ���CASE 4: �޸�ԭ�ļ�"<<std::endl;
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

		std::cout<<"���ڼ����ļ�..\n";
		oRc4.Crypt(sCopyFile.c_str(), kFileKey.c_str(), kFileKey.length());

		std::cout<<"���ڽ����ļ�..\n";
		oRc4.Crypt(sCopyFile.c_str(), kFileKey.c_str(), kFileKey.length());

		std::cout<<"�������.\n\n";
	}
	
}