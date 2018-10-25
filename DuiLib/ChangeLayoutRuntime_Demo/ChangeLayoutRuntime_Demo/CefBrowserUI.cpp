#include "CefHeaders.h"
#include "CefBrowserUI.h"
#include <include/wrapper/cef_helpers.h>
#include <include/base/cef_bind.h>
#include <windows.h>
#include <shlwapi.h>

namespace DuiLib
{
const TCHAR* CCefBrowserUI::kCefBrowserUIClass = _T("CCefBrowserUI");
std::string StringToUTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete []pwBuf;
	delete []pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

CCefBrowserUI::CCefBrowserUI(void)
{
}


CCefBrowserUI::~CCefBrowserUI(void)
{
	if(m_pClientHandler.get() && m_pClientHandler->m_pBrowser.get())
	{
	}
}

CCefBrowserUI::CCefBrowserUI(HWND hParent)
{
	m_hWnd = hParent; //m_hWnd = GetManager()->GetPaintWindow();	
	m_pClientHandler = new CCefClientHandler();
	m_pClientHandler->hWnd_ = m_hWnd;
	m_pClientHandler->m_cbBrowserCreated = std::bind(&CCefBrowserUI::AfterBrowserCreated, this);
	m_pClientHandler->m_cbGotFocus = std::bind(&CCefBrowserUI::OnGotFocus, this);
}

LPCTSTR CCefBrowserUI::GetClass() const
{
	return kCefBrowserUIClass;
}

LPVOID CCefBrowserUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcscmp(pstrName, DUI_CTR_CEFBROWSER) == 0)
		return this;
	else
		return CControlUI::GetInterface(pstrName);
}

void CCefBrowserUI::DoInit()
{
	if( m_sUrlPrefix.length() > 0 )
		m_sUrl = m_sUrlPrefix + m_sUrl;
	//替换'\\'为'/'
	int pos = 0;
	pos = m_sUrl.find('\\', pos);
	while( pos != string::npos )
	{  
		m_sUrl.replace(pos, 1, "/");
		pos = m_sUrl.find('\\', pos+1);
	}


	CefWindowInfo info;
	info.SetAsChild(m_hWnd, m_rcItem);
	CefBrowserSettings browserSettings;
	CefBrowserHost::CreateBrowser(info, m_pClientHandler, m_sUrl, browserSettings, NULL);
}

void CCefBrowserUI::DoEvent(TEventUI& event)
{
	//鼠标形状等需要过滤一下吗?!!! jian.he;

	__super::DoEvent(event);
}

void CCefBrowserUI::OnGotFocus()
{
	GetManager()->SetFocus(NULL);
}


void CCefBrowserUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("url")) == 0)
	{
		m_sUrl = pstrValue;	
		//自动转换相对路径到绝对路径..
		if( m_sUrl.length() > 0 && m_sUrl[0] == '.' )
		{
			char szPath[MAX_PATH] = {0};
			::GetModuleFileNameA(NULL, szPath, MAX_PATH);
			::PathAppendA(szPath, "..\\");
			::PathAppendA(szPath, m_sUrl.c_str());
			m_sUrl = szPath;

			m_sUrl = DuiLib::StringToUTF8(m_sUrl);
		}
	}
	else if(_tcscmp(pstrName, _T("urlprefix")) == 0)
	{
		m_sUrlPrefix = pstrValue;
	}
	else
	{
		CControlUI::SetAttribute(pstrName, pstrValue);
	}
}

void CCefBrowserUI::SetPos(RECT rc)
{
	__super::SetPos(rc);
	
	HWND hHost = GetCefHandle(); //有的时候调用这里的时候，m_pBrowser还没有获取有效值！所以需要AfterBrowserCreated()回调!jian.he;20170731;
	if(hHost){
		//SetWindowPos(hHost, HWND_TOP, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, SWP_NOZORDER);
		MoveWindow(hHost, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, true);
	}
}

void CCefBrowserUI::AfterBrowserCreated()
{
	HWND hHost = GetCefHandle();
	if(hHost)
	{
		//SetWindowPos(hHost, HWND_TOP, m_rcItem.left, m_rcItem.top, m_rcItem.right-m_rcItem.left, m_rcItem.bottom-m_rcItem.top, SWP_NOZORDER);
		MoveWindow(hHost, m_rcItem.left, m_rcItem.top, m_rcItem.right-m_rcItem.left, m_rcItem.bottom-m_rcItem.top, false);
		::ShowWindow(hHost, IsVisible()?SW_SHOW:SW_HIDE);

		//为了正确与duilib的RichEdit等其他控件切换焦点，这里手动设置DUILIB窗口无焦点.jian.he 20170801;
		GetManager()->SetFocus(NULL);
	}
}

HWND CCefBrowserUI::GetCefHandle()
{
	HWND hRet = NULL;
	if(m_pClientHandler.get() && m_pClientHandler->m_pBrowser.get())
	{
		CefRefPtr<CefBrowserHost> pHost = m_pClientHandler->m_pBrowser->GetHost();
		if(pHost)
			hRet = pHost->GetWindowHandle();
	}	
	
	return hRet;
}

void CCefBrowserUI::SetVisible(bool bVisible /*= true*/)
{
	__super::SetVisible(bVisible);

	HWND hwnd = GetCefHandle();
	if (hwnd)
		::ShowWindow(hwnd, bVisible ? SW_SHOW : SW_HIDE);
}

void CCefBrowserUI::SetInternVisible(bool bVisible)
{
	__super::SetInternVisible(bVisible);

	HWND hwnd = GetCefHandle();
	if(hwnd)
		::ShowWindow(hwnd, bVisible ? SW_SHOW : SW_HIDE);
}

void CCefBrowserUI::ReFresh()
{
	RECT rectnew = GetPos();
	SetPos(rectnew);
}


void CCefBrowserUI::ReLoad()
{
	if(m_pClientHandler.get() && m_pClientHandler->m_pBrowser.get())
		m_pClientHandler->m_pBrowser->Reload();
}

void CCefBrowserUI::LoadURL(CefString& strURL)
{
	m_sUrl = strURL;
	if(m_pClientHandler && m_pClientHandler->m_pBrowser)
		m_pClientHandler->m_pBrowser->GetMainFrame()->LoadURL(strURL);
}

void CCefBrowserUI::ExecJavaScript(const CefString& js)
{
	if (m_pClientHandler.get() && m_pClientHandler->m_pBrowser.get())
	{
		CefRefPtr<CefFrame> frame = m_pClientHandler->m_pBrowser->GetMainFrame();
		if (frame)
			frame->ExecuteJavaScript(js, L"", 0);
	}
}


void CCefBrowserUI::SetOnWebLoadEnd(CB_WEBLOADEND cb)
{
	m_pClientHandler->m_cbWebLoadEnd = cb;
}

void CCefBrowserUI::SetOnPopup(CB_B4POPUP cb)
{
	m_pClientHandler->m_cbB4Popup = cb;;
}
void CCefBrowserUI::SetOnBrowserCreated(CB_AFTERBROWSERCREATED cb)
{
	m_pClientHandler->m_cbBrowserCreated = cb;
}


void CCefBrowserUI::ViewSource()
{
	if (m_pClientHandler.get() && m_pClientHandler->m_pBrowser.get())
	{
		CefRefPtr<CefFrame> frame = m_pClientHandler->m_pBrowser->GetMainFrame();
		if (frame)
			frame->ViewSource();
	}
}

void CCefBrowserUI::GetSource(CefGetSourceCallBack pCallback)
{
	if (m_pClientHandler.get() && m_pClientHandler->m_pBrowser.get())
	{
		CefRefPtr<CefFrame> frame = m_pClientHandler->m_pBrowser->GetMainFrame();

		CefString  t_cefstring;
		Visitor *visitor = new Visitor(pCallback);
		
		if(visitor)
		{
			frame->GetSource(visitor);
			return;
		}
	}

	return;
}

}