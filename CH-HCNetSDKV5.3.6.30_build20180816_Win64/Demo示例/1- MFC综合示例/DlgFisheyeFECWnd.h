#if !defined(AFX_DLGFISHEYEFECWND_H__76E26584_5260_4C97_9905_A2C0B2203FB9__INCLUDED_)
#define AFX_DLGFISHEYEFECWND_H__76E26584_5260_4C97_9905_A2C0B2203FB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFisheyeFECWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyeFECWnd dialog

class CDlgFisheyeFECWnd : public CDialog
{
// Construction
public:
	CDlgFisheyeFECWnd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFisheyeFECWnd)
	enum { IDD = IDD_DLG_FISHEYE_FECWND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFisheyeFECWnd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFisheyeFECWnd)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	HWND GetPlayWnd();
	void DrawFun(HDC hdc,DWORD dwWidth,DWORD dwHeight);
	void SetRealHandle(LONG lRealHandle);
private:
	CRect m_rcPlayWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFISHEYEFECWND_H__76E26584_5260_4C97_9905_A2C0B2203FB9__INCLUDED_)
