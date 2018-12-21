#include "afxwin.h"
#if !defined(AFX_DLGDEVSERVER_H__8A15A532_1501_47F6_8012_CE764B18E546__INCLUDED_)
#define AFX_DLGDEVSERVER_H__8A15A532_1501_47F6_8012_CE764B18E546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDevServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDevServer dialog

class CDlgDevServer : public CDialog
{
// Construction
public:
	CDlgDevServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDevServer)
	enum { IDD = IDD_DLG_DEVSERVER };
	CComboBox	m_comDeicing;
	CComboBox	m_comStreamEncryption;
	CComboBox	m_comMultDisco;
	CComboBox	m_comSupplementLight;
	CComboBox	m_comRtspAuthentication;
	CComboBox	m_comboTelnetServerNew;
	CComboBox	m_comWebAuthentication;
	CComboBox	m_comSSHServer;
	CComboBox	m_comAutoDefog;
	CComboBox	m_comboAbfServer;
	CComboBox	m_comboTelnetServer;
	CComboBox	m_comboIRLampServer;
	CComboBox	m_comboEnableLEDStatus;
	CComboBox   m_comboLoginLock;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDevServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDevServer)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnBtnSecSet();
	afx_msg void OnBtnSecGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG    m_lServerID;
	DWORD	m_dwDevIndex;
    DWORD	m_dwAlarmOutNum;
	DWORD	m_dwAlarmInNum;
    DWORD   m_nChannel;
    DWORD   m_lStartChan;
	NET_DVR_DEVSERVER_CFG m_struDevServerCfg;
	NET_DVR_SECURITY_CFG m_struSecurityCfg;
    CComboBox m_combAntiAttack;
    BOOL m_bEnableVisibleMovementPower;
    BOOL m_bEnableThermalMovementPower;
    BOOL EnablePtzPower;

    CComboBox m_cPowerSavingControl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVSERVER_H__8A15A532_1501_47F6_8012_CE764B18E546__INCLUDED_)
