#if !defined(AFX_DLGVEDIOAUDIOINCFG_H__78547A3A_F6CE_4E6A_9000_42589844564D__INCLUDED_)
#define AFX_DLGVEDIOAUDIOINCFG_H__78547A3A_F6CE_4E6A_9000_42589844564D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVedioAudioInCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgVedioAudioInCfg dialog

class DlgVedioAudioInCfg : public CDialog
{
// Construction
public:
	DlgVedioAudioInCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgVedioAudioInCfg)
	enum { IDD = IDD_DLG_VEDIO_AUDIOIN_CFG };
	BOOL	m_AudioSource;
	UINT	m_AudioChannel;
	UINT	m_VedioChannel;
	//}}AFX_DATA
	NET_DVR_VIDEO_AUDIOIN_CFG m_struVedioAudioInCfg;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgVedioAudioInCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgVedioAudioInCfg)
	afx_msg void OnSet();
	afx_msg void OnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVEDIOAUDIOINCFG_H__78547A3A_F6CE_4E6A_9000_42589844564D__INCLUDED_)
