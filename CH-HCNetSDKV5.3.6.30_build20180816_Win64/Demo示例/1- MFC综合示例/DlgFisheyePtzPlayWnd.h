#if !defined(AFX_DLGFISHEYEPTZPLAYWND_H__5703CB35_5261_4063_8635_AC0D58A69BBC__INCLUDED_)
#define AFX_DLGFISHEYEPTZPLAYWND_H__5703CB35_5261_4063_8635_AC0D58A69BBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Resource.h"
// DlgFisheyePtzPlayWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyePtzPlayWnd dialog

class CDlgFisheyePtzPlayWnd : public CDialog
{
// Construction
public:
	CDlgFisheyePtzPlayWnd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFisheyePtzPlayWnd)
	enum { IDD = IDD_DLG_FISHEYE_PTZ_PLAYWND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFisheyePtzPlayWnd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFisheyePtzPlayWnd)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL StartRealPlay();
	BOOL StopRealPlay();
public:
	void SwitchChannel(LONG lChannel);
	void DrawFun(HDC hdc);
public:
	LONG m_lServerID;
	LONG m_lChannel;
	int  m_iDevIndex;
	LONG m_lRealHandle;
	CRect m_rcPlayWnd;
private:
	CPen m_pen;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFISHEYEPTZPLAYWND_H__5703CB35_5261_4063_8635_AC0D58A69BBC__INCLUDED_)
