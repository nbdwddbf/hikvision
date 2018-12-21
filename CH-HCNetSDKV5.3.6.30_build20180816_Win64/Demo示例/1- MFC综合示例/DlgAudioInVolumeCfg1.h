#include "afxwin.h"
#if !defined(AFX_DLGAUDIOINVOLUMECFG1_H__751BC0CA_E8AE_4A0E_B0C7_42E497C1C9B8__INCLUDED_)
#define AFX_DLGAUDIOINVOLUMECFG1_H__751BC0CA_E8AE_4A0E_B0C7_42E497C1C9B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAudioInVolumeCfg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioInVolumeCfg dialog

class CDlgAudioInVolumeCfg : public CDialog
{
// Construction
public:
	CDlgAudioInVolumeCfg(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;
    DWORD   m_dwLastIndex;

// Dialog Data
	//{{AFX_DATA(CDlgAudioInVolumeCfg)
	enum { IDD = IDD_DLG_AUDIOIN_VOLUME_CFG };
	BOOL	m_bChkPhantomPower;
	BOOL	m_bEnableFBC;
	BOOL	m_bEnableAEC;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAudioInVolumeCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAudioInVolumeCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    NET_DVR_VOLUME_CFG m_struVolumeCfg;
public:
    int m_iAudioInIndex;
    CComboBox m_comboAudioOutIndex;
    int m_iAudioVolume;
    afx_msg void OnCbnSelchangeComboAudioOutIndex();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUDIOINVOLUMECFG1_H__751BC0CA_E8AE_4A0E_B0C7_42E497C1C9B8__INCLUDED_)
