// CodecUtils.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestRc4.h"
#include "TestUtf8.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CTestRc4::Go();
	//CodecUtils::CTestUtf8::Test_IsUtf8();


	fprintf(stderr, "\n\n\n\nGAME OVER.\n");
	getchar();
	return 0;
}

