#pragma once

#include "stdafx.h"

class CMainWnd: public WindowImplBase
{
public:
	CMainWnd(void);
	~CMainWnd(void);

protected:
	virtual const CDuiString& GetResourcePath();
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR    GetWindowClassName() const;
	virtual void       InitWindow();
	virtual void       Notify(TNotifyUI& msg);


	void OnUI_BtnHorzLay();
	void OnUI_BtnVertLay();
	void SwitchParentNode(CContainerUI* pDestCon, CContainerUI* pSrcCon);
private:
	CButtonUI* m_pBtnHorzLay;
	CButtonUI* m_pBtnVertLay;
	CHorizontalLayoutUI* m_pLayHorz;
	CVerticalLayoutUI* m_pLayVert;

	CComboUI* m_pCboA1;

};
