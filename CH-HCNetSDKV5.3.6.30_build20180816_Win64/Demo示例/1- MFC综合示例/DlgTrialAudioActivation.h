#if !defined(AFX_DLGTRIALAUDIOACTIVATION_H__386ED7EB_F681_4E33_B20A_F193675E7641__INCLUDED_)
#define AFX_DLGTRIALAUDIOACTIVATION_H__386ED7EB_F681_4E33_B20A_F193675E7641__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrialAudioActivation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialAudioActivation dialog

class CDlgTrialAudioActivation : public CDialog
{
// Construction
public:
	CDlgTrialAudioActivation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTrialAudioActivation)
	enum { IDD = IDD_DLG_TRIAL_AUDIO_ACTIVATION };
	CComboBox	m_cmbBaseNo;
	CComboBox	m_cmbPresetNO;
	CComboBox	m_cmbChan;
	CComboBox	m_cmbAudioActivation;
	BOOL	m_bEnable;
	UINT	m_wDelayTime;
	BYTE	m_bySensitivity;
	BYTE	m_byPriority;
	BOOL	m_bPreset;
	BOOL	m_bChkVGA1;
	BOOL	m_bChkVGA2;
	BOOL	m_bChkVGA3;
	BOOL	m_bChkVGA4;
	BOOL	m_bChkVGA5_10;
	BOOL	m_bChkHDMI1;
	BOOL	m_bChkHDMI2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrialAudioActivation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrialAudioActivation)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeCmbAudioInputNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int m_lUserID;
    int m_iDevIndex;
    NET_DVR_AUDIO_ACTIVATION_CFG m_struAudioActCfg;
    NET_DVR_TRIAL_SYSTEM_INFO m_struSystemInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRIALAUDIOACTIVATION_H__386ED7EB_F681_4E33_B20A_F193675E7641__INCLUDED_)
