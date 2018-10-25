/******************************************************************* 
*  Copyright(c) 2017-2020 Anymacro 
*  All rights reserved. 
*   
*  创建日期: 2018-03-16
*  作者: David
*  邮箱: weirunping@anymacro.com
*  说明: 这个文件被使用在管理平台插件开发中
******************************************************************/

#include "CefClientHandler.h"


CCefClientHandler::CCefClientHandler() :hWnd_(NULL),m_cbBrowserCreated(NULL),m_cbWebLoadEnd(nullptr)
{
}

CCefClientHandler::~CCefClientHandler()
{

}

CefRefPtr<CefLifeSpanHandler> CCefClientHandler::GetLifeSpanHandler()
{
	return this;
}
CefRefPtr<CefLoadHandler> CCefClientHandler::GetLoadHandler()
{
	return this;
}

//一个ClientHandler可以对应多个Browser;
void CCefClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	m_pBrowser = browser;
	if(m_cbBrowserCreated)
		m_cbBrowserCreated();
}

void CCefClientHandler::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame)
{
	// 	CEF_REQUIRE_UI_THREAD();
	// 
	// 	CefString* strTmpURL = new CefString(browser->GetMainFrame()->GetURL());
	// 	int nID = browser->GetIdentifier();
	// 	::PostMessage(hWnd_, UI_CEF_WEBLOADSTART, nID, (LPARAM)strTmpURL);

	//return __super::OnLoadStart(browser, frame);
}
void CCefClientHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{
	CEF_REQUIRE_UI_THREAD();

	if(m_cbWebLoadEnd)
		m_cbWebLoadEnd();
}



void CCefClientHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
{
	CEF_REQUIRE_UI_THREAD();

	// Don't display an error for downloaded files.
	if (errorCode == ERR_ABORTED)
		return;

	// Display a load error message.
	std::stringstream ss;
	ss << "<html><body bgcolor=\"white\">"
		"<h2>Failed to load URL " << std::string(failedUrl) <<
		" with error " << std::string(errorText) << " (" << errorCode <<
		").</h2></body></html>";
	frame->LoadString(ss.str(), failedUrl);
}

bool CCefClientHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, CefLifeSpanHandler::WindowOpenDisposition target_disposition,
	bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, bool* no_javascript_access)
{
	if(m_cbB4Popup)
		m_cbB4Popup(target_url);

	return true;
}

void CCefClientHandler::OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model)
{
	model->Clear();
}

void CCefClientHandler::OnGotFocus(CefRefPtr<CefBrowser> browser)
{
	if(m_cbGotFocus)
		m_cbGotFocus();
}
