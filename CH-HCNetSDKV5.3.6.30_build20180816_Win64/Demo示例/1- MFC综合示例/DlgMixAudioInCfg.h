#if !defined(AFX_DLGMIXAUDIOINCFG_H__BAEE9009_169D_419F_B609_03741A4B9A02__INCLUDED_)
#define AFX_DLGMIXAUDIOINCFG_H__BAEE9009_169D_419F_B609_03741A4B9A02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMixAudioInCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMixAudioInCfg dialog

class CDlgMixAudioInCfg : public CDialog
{
// Construction
public:
	CDlgMixAudioInCfg(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;

// Dialog Data
	//{{AFX_DATA(CDlgMixAudioInCfg)
	enum { IDD = IDD_DLG_MIX_AUDIOIN_CFG };
	CComboBox	m_cmbStaticFilterNum;
	CComboBox	m_cmbFilterQValue;
	CComboBox	m_cmbMode;
	DWORD	m_dwHighPassFilter;
	DWORD	m_dwNoiseMargin;
	BOOL	m_bEnableFBC;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMixAudioInCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMixAudioInCfg)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bDspFBC;
    int m_iInputVolume;
    int m_iVolumeIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMIXAUDIOINCFG_H__BAEE9009_169D_419F_B609_03741A4B9A02__INCLUDED_)
