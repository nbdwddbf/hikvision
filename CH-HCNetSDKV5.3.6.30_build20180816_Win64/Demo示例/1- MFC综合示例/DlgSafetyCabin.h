#if !defined(AFX_DLGSAFETYCABIN_H__BD739A74_F552_46FE_89CE_F783F26B6DA7__INCLUDED_)
#define AFX_DLGSAFETYCABIN_H__BD739A74_F552_46FE_89CE_F783F26B6DA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSafetyCabin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSafetyCabin dialog

class CDlgSafetyCabin : public CDialog
{
// Construction
public:
	CDlgSafetyCabin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSafetyCabin)
	enum { IDD = IDD_DLG_SAFETYCABIN };
	CComboBox	m_comboWorkMode;
	CComboBox	m_comboSensorType;
	CComboBox	m_comboFaintToUnlock;
	CComboBox	m_comboOverTimeToUnlock;
	short	m_wCurtainDelay;
	short	m_wCurtainResponse;
	BYTE	m_byDevUseTimeOut;
	BYTE	m_bySensitivity;
	short   m_wFaintToEmergencyTime;
	BYTE	m_byFollowDetectorSensitivity;
	BYTE	m_byManyPersonSensitivity;
	

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSafetyCabin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSafetyCabin)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnOutputScheduleCfg();
	afx_msg void OnBtnOneOutputScheduleCfg();
	afx_msg void OnBtnSafecabinState();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int  m_iDeviceIndex;
	NET_DVR_SAFETYCABIN_WORK_MODE m_struWorkMode;
	NET_DVR_SAFETYCABIN_PERSON_SIGNAL_CFG m_struPersonSignalCfg;
	NET_DVR_ALARMHOST_ABILITY m_struAblity;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSAFETYCABIN_H__BD739A74_F552_46FE_89CE_F783F26B6DA7__INCLUDED_)
