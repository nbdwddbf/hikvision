#if !defined(AFX_DLGPOSTRADARCFG_H__E73F4E89_7EF5_4A6C_B4B9_24BD0DB58303__INCLUDED_)
#define AFX_DLGPOSTRADARCFG_H__E73F4E89_7EF5_4A6C_B4B9_24BD0DB58303__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPostRadarCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPostRadarCfg dialog

class CDlgPostRadarCfg : public CDialog
{
// Construction
public:
	CDlgPostRadarCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPostRadarCfg)
	enum { IDD = IDD_DLG_POSTRADAR_CFG };
	CComboBox	m_comDetectMode;
	CComboBox	m_comWorkMode;
	CComboBox	m_comSpeedType;
	CComboBox	m_comDirectionFilter;
	CComboBox	m_comLaneType;
	DWORD	m_dwBigCarSignSpeed;
	DWORD	m_dwBigCarSpeedLimit;
	DWORD	m_dwInterval;
	DWORD	m_dwSignSpeed;
	DWORD	m_dwSpeedLimit;
	DWORD	m_dwAngleCorrect;
	DWORD	m_dwSensitivity;
	DWORD	m_dwSpeedLowLimit;
	BYTE	m_byID;
	DWORD	m_dwTrigDistance;
	CString	m_csSoftwareVersion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPostRadarCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPostRadarCfg)
	afx_msg void OnBtnSetPostradar();
	afx_msg void OnBtnGetPostradar();
	afx_msg void OnBtnGetPostradarRecom();
	afx_msg void OnBtnSetPostradarparam();
	afx_msg void OnBtnGetPostradarparamRecom();
	afx_msg void OnBtnGetPostradarparam();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lLoginID;
    INT  m_iDeviceIndex;
    LONG m_lChannel;
    char m_szLan[2048];
    char m_szStatusBuf[ISAPI_STATUS_LEN];
	BOOL m_bCheckPost;
	BOOL m_bOverSpeed;
//	DWORD m_dwLowSpeedLimit;
//	CString m_dwBigCarLowSpeedLimit;
	DWORD m_dwLowSpeedLimit;
	DWORD m_dwBigCarLowSpeedLimit;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOSTRADARCFG_H__E73F4E89_7EF5_4A6C_B4B9_24BD0DB58303__INCLUDED_)
