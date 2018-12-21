#if !defined(AFX_DLGPTZTRACKPARAMCFG_H__B1A70F2B_5A45_4E9A_8D4E_A15498F6D7E6__INCLUDED_)
#define AFX_DLGPTZTRACKPARAMCFG_H__B1A70F2B_5A45_4E9A_8D4E_A15498F6D7E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPtzTrackParamCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzTrackParamCfg dialog

class CDlgPtzTrackParamCfg : public CDialog
{
	// Construction
public:
	CDlgPtzTrackParamCfg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CDlgPtzTrackParamCfg)
	enum { IDD = IDD_DLG_PTZ_TRACK_CFG };
	CComboBox	m_comboAutoTrackEnable;
	CComboBox	m_comboTrackMode;
	int		m_nTrackTime;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPtzTrackParamCfg)
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgPtzTrackParamCfg)
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void InitCtrlState();
	BOOL GetPtzTrackParam();
	BOOL SetPtzTrackParam();
	
	void SaveWndContent();
	void LoadWndContent();
public:
	LONG m_lServerID;
	LONG m_lChannel;
	int  m_iDevIndex;
	NET_DVR_PTZ_TRACK_PARAM m_struPtzTrackParam;
//	CString m_sTrackStatus;
	afx_msg void OnBnClickedBtnGettrackstatus();
	char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPTZTRACKPARAMCFG_H__B1A70F2B_5A45_4E9A_8D4E_A15498F6D7E6__INCLUDED_)
