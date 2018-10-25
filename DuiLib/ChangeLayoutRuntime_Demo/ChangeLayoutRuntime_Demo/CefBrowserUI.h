#pragma once
/*
	@Date:    2017/07/26;
	@Author:  jian.he;
	@Company: AnyMacro.com;
*/
#include "CefHeaders.h"
#include "DuiLib/UIlib.h"
#include <functional>
#include "CefClientHandler.h"

namespace DuiLib
{


class CCefBrowserUI: public CControlUI
{
public:	
	CCefBrowserUI(HWND hParent);
	~CCefBrowserUI(void);

	virtual LPCTSTR GetClass() const;
	virtual LPVOID  GetInterface(LPCTSTR pstrName);
	virtual void    DoInit();
	virtual void    DoEvent(TEventUI& event);
	virtual void    SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	virtual void    SetPos(RECT rc);
	virtual void    SetVisible(bool bVisible = true);
	virtual void    SetInternVisible(bool bVisible = true) override;
	//self-defined callbacks..
	void AfterBrowserCreated();
	void OnGotFocus();

	void ReFresh();
	void ReLoad();
	void LoadURL(CefString& strURL);
	void ExecJavaScript(const CefString& js);
	void ViewSource();
	void GetSource(CefGetSourceCallBack pCallback);

	HWND GetCefHandle();
	CefRefPtr<CCefClientHandler>  m_pClientHandler;
	static const TCHAR* kCefBrowserUIClass;

	void SetOnWebLoadEnd(CB_WEBLOADEND cb);
	void SetOnPopup(CB_B4POPUP cb);
	void SetOnBrowserCreated(CB_AFTERBROWSERCREATED cb);
private:
	CCefBrowserUI(void);
	
	
	HWND m_hWnd;
	std::string m_sUrl;
	std::string m_sUrlPrefix;
};



}

