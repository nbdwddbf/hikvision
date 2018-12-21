#if !defined(AFX_DLGMIXAUDIOOUTCFG_H__838474E1_08D2_40EB_8F1C_36EB0B88CEC8__INCLUDED_)
#define AFX_DLGMIXAUDIOOUTCFG_H__838474E1_08D2_40EB_8F1C_36EB0B88CEC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMixAudioOutCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMixAudioOutCfg dialog

class CDlgMixAudioOutCfg : public CDialog
{
// Construction
public:
	CDlgMixAudioOutCfg(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;

// Dialog Data
	//{{AFX_DATA(CDlgMixAudioOutCfg)
	enum { IDD = IDD_DLG_MIX_AUDIOOUT_CFG };
	CComboBox	m_cmbOutputGain;
	CComboBox	m_cmbTriggerTime;
	CComboBox	m_cmbRecoveryGain;
	CComboBox	m_cmbModulatorValue;
	CComboBox	m_cmbFreeTime;
	CComboBox	m_cmbCompressRate;
	CComboBox	m_cmbCompressThreshold;
	CComboBox	m_cmbCompressMode;
	BOOL	m_bEnableModulator;
	BOOL	m_bEnablePostFilter;
	BOOL	m_bEnableLimitPressure;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMixAudioOutCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMixAudioOutCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bOutputMute;
    BOOL m_bSoundQualityHanding;
    int m_iOutputGainEx;
    int m_iOutputIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMIXAUDIOOUTCFG_H__838474E1_08D2_40EB_8F1C_36EB0B88CEC8__INCLUDED_)
