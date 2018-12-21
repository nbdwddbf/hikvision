#if !defined(AFX_DLGAUDIODIACRITICALCFG_H__11D7D3E0_7BA9_44CF_B2C8_AA62EB991771__INCLUDED_)
#define AFX_DLGAUDIODIACRITICALCFG_H__11D7D3E0_7BA9_44CF_B2C8_AA62EB991771__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAudioDiacriticalCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioDiacriticalCfg dialog

class CDlgAudioDiacriticalCfg : public CDialog
{
// Construction
public:
	CDlgAudioDiacriticalCfg(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;

// Dialog Data
	//{{AFX_DATA(CDlgAudioDiacriticalCfg)
	enum { IDD = IDD_DLG_AUDIO_DIACRITICAL_CFG };
	CComboBox	m_cmbChan;
	CSliderCtrl	m_sliderBassValue;
	BOOL	m_bEnable;
	CString	m_csBassValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAudioDiacriticalCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAudioDiacriticalCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomdrawSliderBassValue(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUDIODIACRITICALCFG_H__11D7D3E0_7BA9_44CF_B2C8_AA62EB991771__INCLUDED_)
