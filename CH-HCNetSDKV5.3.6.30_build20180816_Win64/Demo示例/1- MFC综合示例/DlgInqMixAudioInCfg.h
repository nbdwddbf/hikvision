#if !defined(AFX_DLGINQMIXAUDIOINCFG_H__47BDA23B_8836_4321_B0AA_0553584DC8B2__INCLUDED_)
#define AFX_DLGINQMIXAUDIOINCFG_H__47BDA23B_8836_4321_B0AA_0553584DC8B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInqMixAudioInCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInqMixAudioInCfg dialog

class CDlgInqMixAudioInCfg : public CDialog
{
// Construction
public:
	CDlgInqMixAudioInCfg(CWnd* pParent = NULL);   // standard constructor

	LONG m_lUserID;
	int m_iDeviceIndex;
	NET_DVR_INQUEST_MIX_AUDIOIN_CFG m_struInqMixAudioInCfg;
	int m_iCurChanType;
	
	void InitMixChanNumCombo();
	void InitChanList();
	//void OnBtnGet();
	void GetChanInfoFromWnd();
	void SetChanInfoToDlg();

// Dialog Data
	//{{AFX_DATA(CDlgInqMixAudioInCfg)
	enum { IDD = IDD_DLG_INQ_MIX_AUDIOIN };
	CComboBox	m_cmbMixChanNum;
	CComboBox	m_cmbInqRoomNo;
	CListCtrl	m_listCtrlChan;
	CComboBox	m_cmbChanType;
	BOOL	m_bEnableMixAudioIn;
	UINT	m_nMixAudioDelay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInqMixAudioInCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInqMixAudioInCfg)
	afx_msg void OnSelchangeCmbChanType();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnRefreshChanNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINQMIXAUDIOINCFG_H__47BDA23B_8836_4321_B0AA_0553584DC8B2__INCLUDED_)
