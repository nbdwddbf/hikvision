#if !defined(AFX_DLGWALLBASEMAPWIN_H__8D1390FC_41EC_4312_96C8_A3E848E4A282__INCLUDED_)
#define AFX_DLGWALLBASEMAPWIN_H__8D1390FC_41EC_4312_96C8_A3E848E4A282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWallBasemapWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWallBasemapWin dialog

class CDlgWallBasemapWin : public CDialog
{
// Construction
public:
	CDlgWallBasemapWin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWallBasemapWin)
	enum { IDD = IDD_DLG_WALL_BASEMAP_WIN };
	CComboBox	m_comboBasemapWinNo;
	CComboBox	m_comboBasemapType;
	BOOL	m_bEnable;
	BOOL	m_bShowEnable;
	DWORD	m_dwBasemapNo;
	DWORD	m_dwHeight;
	BYTE	m_byOut1;
	BYTE	m_byOut2;
	BYTE	m_byOut3;
	BYTE	m_byOut4;
	DWORD	m_dwWidth;
	DWORD	m_dwX;
	DWORD	m_dwY;
	BYTE	m_byWallNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWallBasemapWin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWallBasemapWin)
	virtual BOOL OnInitDialog();	
	afx_msg void OnBtnBasemapWinSet();
	afx_msg void OnBtnBasemapWinGet();
	afx_msg void OnBtnBasemapSet();
	afx_msg void OnBtnBasemapGet();
	afx_msg void OnSelchangeComboBasemapType();
	afx_msg void OnBtnCancle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int m_iDeviceIndex;
	DWORD m_dwBasemapWinNo;
	NET_DVR_BASEMAP_WINCFG m_struBasemapWinCfg;
	NET_DVR_BASEMAP_CONTROL_CFG m_struBasemapControlCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWALLBASEMAPWIN_H__8D1390FC_41EC_4312_96C8_A3E848E4A282__INCLUDED_)
