// CodecUtils.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestRc4.h"
#include "TestUtf8.h"
#include "BigLittleEndian.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//CTestRc4::Go();
	//CodecUtils::CTestUtf8::Test_IsUtf8();
	//printf("sizeof(short):%d\n", sizeof(short));
	printf("Current Compiler:%s\n", CBigLittleEndian::IsCurrentCompilerLittleEndian()?"Little Endian":"Big Endian");

	fprintf(stderr, "\n\n\n\nGAME OVER.\n");
	getchar();
	return 0;
}

