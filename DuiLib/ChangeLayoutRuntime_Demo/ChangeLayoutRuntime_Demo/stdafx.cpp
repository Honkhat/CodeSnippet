// stdafx.cpp : 只包括标准包含文件的源文件
// ChangeLayoutRuntime_Demo.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

CDuiString& ResourcePath()
{
	TCHAR tszModule[MAX_PATH + 1] = { 0 };
	::GetModuleFileName(NULL, tszModule, MAX_PATH);
	::PathAppendA(tszModule, _T("..\\TEST-skin\\"));
	static CDuiString g_sResPath = tszModule;
	return g_sResPath;
}
const CDuiString g_sResourcePath = ResourcePath();//相对于.exe路径;