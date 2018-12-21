#if !defined(AFX_DLGVOICETALK_H__156395F2_1A5C_4F20_A6C3_EDDC94E5B9CF__INCLUDED_)
#define AFX_DLGVOICETALK_H__156395F2_1A5C_4F20_A6C3_EDDC94E5B9CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVoiceTalk.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVoiceTalk dialog

class CDlgVoiceTalk : public CDialog
{
// Construction
public:
	CDlgVoiceTalk(CWnd* pParent = NULL);   // standard constructor
	DWORD m_dwDeviceIndex;
	DWORD m_dwSel;
	void EnableCtrl();
	NET_DVR_WORKSTATE_V30 m_struWorkState;
	NET_DVR_DIGITAL_CHANNEL_STATE m_struDigitalAudioState;
    BOOL m_bGetWorkStatusSucc;
    NET_DVR_DECODER_WORK_STATUS m_DecoderWorkStatus;
// Dialog Data
	//{{AFX_DATA(CDlgVoiceTalk)
	enum { IDD = IDD_DLG_VOICE_TALK };
	CComboBox	m_comboDataType;
	CComboBox	m_comboVoiceChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVoiceTalk)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVoiceTalk)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnStop();
	afx_msg void OnSelchangeComboVoiceChan();
	afx_msg void OnBtnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVOICETALK_H__156395F2_1A5C_4F20_A6C3_EDDC94E5B9CF__INCLUDED_)
