#if !defined(AFX_DLGRECORDHOSTAUDIOEFFECTIVECFG_H__BF3ABEAE_5593_432E_A51B_47BD696F8BA3__INCLUDED_)
#define AFX_DLGRECORDHOSTAUDIOEFFECTIVECFG_H__BF3ABEAE_5593_432E_A51B_47BD696F8BA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostAudioEffectiveCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostAudioEffectiveCfg dialog

class CDlgRecordHostAudioEffectiveCfg : public CDialog
{
// Construction
public:
	CDlgRecordHostAudioEffectiveCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordHostAudioEffectiveCfg)
	enum { IDD = IDD_DLG_RECORD_HOST_AUDIO_EFFECT_CFG };
		// NOTE: the ClassWizard will add data members here
    CComboBox	m_comAudioChan;

    LONG m_lAudioChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordHostAudioEffectiveCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(CDlgRecordHostAudioEffectiveCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	DWORD   	m_dwCheckDelay;
	BYTE		m_byThreshold;
	BYTE     	m_byVolumePercent;
	BYTE     	m_byPriority;

	NET_DVR_AUDIO_EFFECTIVE_CFG m_struAudioEffectiveCfg;

public:
	LONG m_lUserID;
    int m_iDeviceIndex;
	//LONG  m_lChannel;

    char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTAUDIOEFFECTIVECFG_H__BF3ABEAE_5593_432E_A51B_47BD696F8BA3__INCLUDED_)
