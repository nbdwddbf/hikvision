#if !defined(AFX_DLGWALLVIRLED_H__FF22C61E_B60C_4794_B43A_AA792019F494__INCLUDED_)
#define AFX_DLGWALLVIRLED_H__FF22C61E_B60C_4794_B43A_AA792019F494__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWallVirLED.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWallVirLED dialog

class CDlgWallVirLED : public CDialog
{
// Construction
public:
	CDlgWallVirLED(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWallVirLED)
	enum { IDD = IDD_DLG_VIDEOWALL_VIRTUAL_LED };
	CComboBox	m_cmbMoveSpeed;
	CComboBox	m_cmbMoveDirection;
	CComboBox	m_CombMoveMode;
	CComboBox	m_CombFontSize;
	CComboBox	m_CombDisplayMode;
	BYTE	m_byFontColU;
	BYTE	m_byFontColV;
	BYTE	m_byFontColY;
	DWORD	m_dwHeight;
	DWORD	m_dwLEDNo;
	DWORD	m_dwWallNo;
	DWORD	m_dwWidth;
	DWORD	m_dwX;
	DWORD	m_dwY;
	CString	m_csLEDContent;
	BYTE	m_byBackgroundU;
	BYTE	m_byBackgroundV;
	BYTE	m_byBackgroundY;
	BOOL	m_BEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWallVirLED)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWallVirLED)
	afx_msg void OnBtnVirRefresh();
	afx_msg void OnBtnVirLedset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
	LONG m_iDeviceIndex;
    BYTE m_byWallNo;                   //用于初始化墙号
protected:
    BOOL UpdateLedPapam(NET_DVR_VIRTUALLED_PARAM &Papam); 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWALLVIRLED_H__FF22C61E_B60C_4794_B43A_AA792019F494__INCLUDED_)
