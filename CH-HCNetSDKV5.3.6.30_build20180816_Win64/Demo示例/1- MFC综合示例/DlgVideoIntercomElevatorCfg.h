#if !defined(AFX_DLGVIDEOINTERCOMELEVATORCFG_H__EEA471D1_1A08_479A_9C9A_115596D4B452__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMELEVATORCFG_H__EEA471D1_1A08_479A_9C9A_115596D4B452__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomElevatorCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomElevatorCfg dialog

class CDlgVideoIntercomElevatorCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomElevatorCfg(CWnd* pParent = NULL);   // standard constructor
    inline BOOL ValidIPv6(BYTE *ip);
// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomElevatorCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_ELEVATOR };
	CComboBox	m_comboRS485Protocol;
	CComboBox	m_comboNetworkProtocol;
	CComboBox	m_comboInterfaceType;
	BOOL	m_bEnable;
    DWORD   m_dwNegativeFloor;
	CString	m_csServiceIP;
	short	m_wPort;
    CComboBox   m_cmbElevatorControlType;
    CString m_csUserName;
    CString m_csPassword;
    DWORD   m_dwElevatorNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomElevatorCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomElevatorCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lServerID;
	LONG m_iDevIndex;
	NET_DVR_ELEVATORCONTROL_CFG_V50 m_struElevatorCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMELEVATORCFG_H__EEA471D1_1A08_479A_9C9A_115596D4B452__INCLUDED_)
