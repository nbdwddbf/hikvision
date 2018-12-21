#if !defined(AFX_DLGSNMPCFG_H__46ACE51C_0A37_4726_B081_6A33F64331D2__INCLUDED_)
#define AFX_DLGSNMPCFG_H__46ACE51C_0A37_4726_B081_6A33F64331D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSnmpCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSnmpCfg dialog

class CDlgSnmpCfg : public CDialog
{
// Construction
public:
	CDlgSnmpCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSnmpCfg)
	enum { IDD = IDD_DLG_SNMP_CFG };
	CString	m_csReadCommunity;
	int		m_iSnmpPort;
	CString	m_csTrapHostIP;
	CString	m_csWriteCommunity;
	int		m_iTrapHostPort;
	CString	m_strAuthPWRO;
	CString	m_strAuthPWRW;
	int		m_iAuthTypeRO;
	int		m_iAuthTypeRW;
	CString	m_strPrivPWRO;
	CString	m_strPrivPWRW;
	int		m_iSecLevelRO;
	int		m_iSecLevelRW;
	CString	m_strUserNameRO;
	CString	m_strUserNameRW;
	BOOL	m_bSnmpV1;
	BOOL	m_bSnmpV2;
	BOOL	m_bSnmpV3;
	int		m_iPrivateTypeRO;
	int		m_iPrivateTypeRW;
	CString	m_csTrapName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSnmpCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSnmpCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetSnmp();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    LONG    m_iDevIndex;
    NET_DVR_SNMPCFG_V30 m_struSnmpCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSNMPCFG_H__46ACE51C_0A37_4726_B081_6A33F64331D2__INCLUDED_)
