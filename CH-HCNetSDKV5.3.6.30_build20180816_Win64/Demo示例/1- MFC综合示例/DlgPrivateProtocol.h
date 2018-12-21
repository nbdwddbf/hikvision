#if !defined(AFX_DLGPRIVATEPROTOCOL_H__3050EB4B_396C_4347_8DA8_A1A3C036F123__INCLUDED_)
#define AFX_DLGPRIVATEPROTOCOL_H__3050EB4B_396C_4347_8DA8_A1A3C036F123__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPrivateProtocol.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPrivateProtocol dialog

class CDlgPrivateProtocol : public CDialog
{
// Construction
public:
	CDlgPrivateProtocol(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPrivateProtocol)
	enum { IDD = IDD_DLG_PRIVATE_PROTOCL };
	CComboBox	m_comboAlgorithm;
	CComboBox	m_comboServerType;
	BOOL	m_bEcryptedSMSEnable;
	int		m_interval;
	CString	m_csIP;
	int		m_iPort;
	int		m_iKeyLen;
	CString	m_csSecretKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrivateProtocol)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPrivateProtocol)
	afx_msg void OnButton1();
	afx_msg void OnButton5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    NET_DVR_PRIVATE_PROTOCOL_CFG m_struPrivateProtocol;

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRIVATEPROTOCOL_H__3050EB4B_396C_4347_8DA8_A1A3C036F123__INCLUDED_)
