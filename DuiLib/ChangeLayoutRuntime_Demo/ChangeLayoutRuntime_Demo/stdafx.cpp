// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// ChangeLayoutRuntime_Demo.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

CDuiString& ResourcePath()
{
	TCHAR tszModule[MAX_PATH + 1] = { 0 };
	::GetModuleFileName(NULL, tszModule, MAX_PATH);
	::PathAppendA(tszModule, _T("..\\TEST-skin\\"));
	static CDuiString g_sResPath = tszModule;
	return g_sResPath;
}
const CDuiString g_sResourcePath = ResourcePath();//�����.exe·��;