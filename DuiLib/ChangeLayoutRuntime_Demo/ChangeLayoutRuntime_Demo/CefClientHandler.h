/******************************************************************* 
*  Copyright(c) 2017-2020 Anymacro 
*  All rights reserved. 
*   
*  创建日期: 2018-03-16
*  作者: David
*  邮箱: weirunping@anymacro.com
*  说明: 这个文件被使用在管理平台插件开发中
******************************************************************/

#ifndef ANYMACRO_CEFCLIENTHANDLER_H
#define ANYMACRO_CEFCLIENTHANDLER_H

#include "CefHeaders.h"
#include <functional>

typedef std::function<void()> CB_AFTERBROWSERCREATED;
typedef std::function<void()> CB_WEBLOADEND;
typedef std::function<bool(const CefString& target_url)> CB_B4POPUP;
typedef std::function<void()> CB_GOTFOCUS;

class CCefClientHandler : public CefClient,public CefDisplayHandler,public CefLifeSpanHandler,public CefLoadHandler,public CefRequestHandler, public CefContextMenuHandler, public CefFocusHandler
{
public:
	CCefClientHandler();
	~CCefClientHandler();

	// CefClient methods:
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;
	virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override{return this;}
	virtual CefRefPtr<CefFocusHandler> GetFocusHandler(){return this;}

	//---------------- CefLifeSpanHandler methods:----------------------------
	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name,
		CefLifeSpanHandler::WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, bool* no_javascript_access) override;
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
	// ----------------CefLoadHandler methods:---------------------------
	virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) override;
	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,CefRefPtr<CefFrame> frame,int httpStatusCode) override;
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,CefRefPtr<CefFrame> frame,ErrorCode errorCode,const CefString& errorText,const CefString& failedUrl) override;
	//---------------------------CefFocusHandler methods------------------------	
	virtual void OnGotFocus(CefRefPtr<CefBrowser> browser);


	//菜单处理
	virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) override;

public:	
	CefRefPtr<CefBrowser> m_pBrowser;
	HWND hWnd_; //接收消息的句柄

	CB_AFTERBROWSERCREATED m_cbBrowserCreated;
	CB_WEBLOADEND m_cbWebLoadEnd;
	CB_B4POPUP m_cbB4Popup;
	CB_GOTFOCUS m_cbGotFocus;
private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(CCefClientHandler);
	//由于CEF采用多线程架构，有必要使用锁和闭包来保证在多不同线程安全的传递数据。IMPLEMENT_LOCKING定义提供了Lock()和Unlock()方法以及AutoLock对象来保证不同代码块同步访问
	IMPLEMENT_LOCKING(CCefClientHandler);
};

typedef std::function<void (std::string)> CefGetSourceCallBack;

class Visitor : public CefStringVisitor {
public:
   CefGetSourceCallBack pCallBack;
   Visitor(CefGetSourceCallBack callback) {pCallBack = callback;}
   virtual void Visit(const CefString& value) OVERRIDE {

	   if(pCallBack)
		  pCallBack(value);
		  
   }
   IMPLEMENT_REFCOUNTING(Visitor);
};

#endif