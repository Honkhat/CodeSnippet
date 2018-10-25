#include "MainWnd.h"

CMainWnd::CMainWnd(void):m_pBtnHorzLay(nullptr),m_pBtnVertLay(nullptr),m_pLayHorz(nullptr),m_pLayVert(nullptr),m_pCboA1(nullptr)

{

}


CMainWnd::~CMainWnd(void)
{
}

const CDuiString& CMainWnd::GetResourcePath()
{
	return g_sResourcePath;
}

CDuiString CMainWnd::GetSkinFolder()
{
	return _T("MainWnd");
}

CDuiString CMainWnd::GetSkinFile() 
{
	return _T("MainWnd.xml");
}

LPCTSTR CMainWnd::GetWindowClassName() const 
{
	return _T("CMainWnd"); 
}

void CMainWnd::InitWindow()
{
	m_pBtnHorzLay = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnHorzLayout")));
	m_pBtnVertLay = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btnVertLayout")));
	m_pLayHorz = dynamic_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("layConHorz")));
	m_pLayVert = dynamic_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("layConVert")));
	
	m_pCboA1 = dynamic_cast<CComboUI*>(m_PaintManager.FindControl(_T("cboA1")));
}


void CMainWnd::Notify(TNotifyUI& msg)
{
	if(msg.sType == DUI_MSGTYPE_CLICK)
	{
		if(msg.pSender->GetName() == "closebtn")
			::PostQuitMessage(0);
		else if(m_pBtnHorzLay == msg.pSender)
			OnUI_BtnHorzLay();
		else if(m_pBtnVertLay == msg.pSender)
			OnUI_BtnVertLay();
	}
	
}

void CMainWnd::OnUI_BtnHorzLay()
{
	SwitchParentNode(m_pLayHorz, m_pLayVert);
	
	//Digging for CComboUI adding CListContainerElementUI as subitems problem.
// 	if(m_pCboA1)
// 	{
// 		CListLabelElementUI* pLbl = new CListLabelElementUI;
// 		pLbl->SetText(_T("东方莫琴"));
// 		m_pCboA1->Add(pLbl);
// 	}

}

void CMainWnd::OnUI_BtnVertLay()
{
	SwitchParentNode(m_pLayVert, m_pLayHorz);

	//Digging for CComboUI adding CListContainerElementUI as subitems problem.
// 	if(m_pCboA1)
// 	{
// 		CListContainerElementUI* pCon = new CListContainerElementUI;
// 		pCon->SetText(_T("东方莫琴-容器"));
// 		m_pCboA1->Add(pCon);
// 	}
}

void CMainWnd::SwitchParentNode(CContainerUI* pDestCon, CContainerUI* pSrcCon)
{
	if(!pDestCon || !pSrcCon)
		return;

	pSrcCon->SetVisible(false);
	pSrcCon->SetAutoDestroy(false);
	for(int i = 0; i < pSrcCon->GetCount(); ++i)
	{
		CControlUI* pItem = pSrcCon->GetItemAt(i);
		pDestCon->Add(pItem);
	}
	pSrcCon->RemoveAll();
	pDestCon->SetVisible(true);
	//pDestCon->SetPos(pDestCon->GetPos());
}