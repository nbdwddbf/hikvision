#include "afxwin.h"
#if !defined(AFX_DLGPRIVATEPROTOCOLCFG_H__408DE20E_4169_4331_B486_C1199BA95A52__INCLUDED_)
#define AFX_DLGPRIVATEPROTOCOLCFG_H__408DE20E_4169_4331_B486_C1199BA95A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPrivateProtocolCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPrivateProtocolCfg dialog

class CDlgPrivateProtocolCfg : public CDialog
{
// Construction
public:
	CDlgPrivateProtocolCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPrivateProtocolCfg)
	enum { IDD = IDD_DLG_PRIVATE_PROTOCL_CFG };
	CComboBox	m_comboServerType;
    CComboBox   m_comboEnable;
	CComboBox	m_comboAlgorithm;
	BOOL	m_bEcryptedSMSEnable;
	CString	m_csIndexCode;
	CString	m_csIP;
	int		m_iPort;
	CString	m_csSecretKey;
	DWORD	m_dwKeyLen;
	DWORD	m_dwInterVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrivateProtocolCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPrivateProtocolCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


    NET_DVR_PRIVATE_PROTOCOL_CFG m_struPrivateProtocol;
    
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChannel;
    CComboBox m_comboAcauisitionMode;
    DWORD m_dwDistanceLimit;
    CComboBox m_combPKmode;
    CComboBox m_combMACAddrReduction;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRIVATEPROTOCOLCFG_H__408DE20E_4169_4331_B486_C1199BA95A52__INCLUDED_)
