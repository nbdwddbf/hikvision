#if !defined(AFX_DLGWALLWIN_H__8F3BD38D_2336_418E_A8BB_0087F145475F__INCLUDED_)
#define AFX_DLGWALLWIN_H__8F3BD38D_2336_418E_A8BB_0087F145475F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWallWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWallWin dialog
#define MAX_WALL_WIN_COUNT     256
class CDlgWallWin : public CDialog
{
// Construction
public:
	CDlgWallWin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWallWin)
	enum { IDD = IDD_DLG_WALLWIN };
	CListCtrl	m_listWinCfg;
	BOOL	m_bEnable;
	DWORD	m_dwLayer;
	short	m_wH;
	short	m_wW;
	short	m_wX;
	short	m_wY;
	BYTE	m_byTransparency;
	BYTE	m_byWinMode;
	BOOL	m_bTransparency;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWallWin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWallWin)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListWincfg(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSave();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnSetPro();
	afx_msg void OnBtnGetPro();
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnSetWallCfg();
	afx_msg void OnBtnGetWallCfg();
	afx_msg void OnBtnWinTop();
	afx_msg void OnBtnWinBottom();
	afx_msg void OnBtnCloseAllWin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	LONG m_iDeviceIndex;
	DWORD m_dwSetCount;
	int m_iCurSel;
	DWORD m_dwWinCount;
	DWORD m_dwStatus[MAX_WALL_WIN_COUNT];
	DWORD m_dwWinNum[MAX_WALL_WIN_COUNT];
	NET_DVR_WALLWINCFG m_struList[MAX_WALL_WIN_COUNT];
	DWORD m_dwWinNumSet[MAX_WALL_WIN_COUNT];
	NET_DVR_WALLWINCFG m_struSet[MAX_WALL_WIN_COUNT];
	NET_DVR_WALLWINPARAM m_struWallWinParam;
	NET_DVR_WALL_CFG m_struWallCfg;
	void DrawList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWALLWIN_H__8F3BD38D_2336_418E_A8BB_0087F145475F__INCLUDED_)
