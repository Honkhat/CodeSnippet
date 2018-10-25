// ChangeLayoutRuntime_Demo.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "ChangeLayoutRuntime_Demo.h"
#include "MainWnd.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	char wsPath[MAX_PATH] = { 0 };
	::GetModuleFileNameA(NULL, wsPath, MAX_PATH);
	::PathAppendA(wsPath, "..\\skin");
	CPaintManagerUI::SetResourcePath((LPCTSTR)wsPath);

	if(FAILED(::CoInitialize(NULL)))
		return 0;

	CMainWnd* pMainFrame = new CMainWnd;
	pMainFrame->Create(NULL, _T("DuiLib Main Wnd"), UI_WNDSTYLE_FRAME, 0L, 800, 600);


	pMainFrame->CenterWindow();
	pMainFrame->ShowWindow();
	CPaintManagerUI::MessageLoop();

	delete pMainFrame;
	::CoUninitialize();

	return 0;
}