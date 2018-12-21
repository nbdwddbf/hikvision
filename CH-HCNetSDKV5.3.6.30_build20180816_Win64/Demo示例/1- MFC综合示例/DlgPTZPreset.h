#pragma once
#include "afxwin.h"


// CDlgPTZPreset dialog

class CDlgPTZPreset : public CDialog
{
	DECLARE_DYNAMIC(CDlgPTZPreset)

public:
	CDlgPTZPreset(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPTZPreset();
	BOOL m_bAuto;
// Dialog Data

public:
	//{{AFX_DATA(CDlgPTZPreset)
	enum { IDD = IDD_DLG_PTZ_PRESET };
	CComboBox	m_comboWiperMode;
	CComboBox m_comboPreset;
	BYTE	m_byWorkTimeInterval;
	DWORD	m_dwContinueWorkTime;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgPTZPreset)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPTZPreset)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPresetAdd();
	afx_msg void OnBnClickedBtnPresetDel();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnPtzTran();
	afx_msg void OnBtnDo();
	afx_msg void OnBtnPtzLight();
	afx_msg void OnBtnWiper();
	afx_msg void OnBtnGetWiper();
	afx_msg void OnBtnSetWiper();
	afx_msg void OnSelchangeComboWiperMode();
	afx_msg void OnBtnLinearScan();
	afx_msg void OnBtnCleAllSeq();
	afx_msg void OnBtnCleAllCruise();
	afx_msg void OnBtnAllClePrest();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int m_iDevIndex;
	LONG m_lLoginID;
	LONG m_lChanNum;
	NET_DVR_WIPERINFO_CFG m_struWiperInfo;
    void AddResolution();
    void SetResolutionCurSel(DWORD dwData);
    short m_wSensitivity;
};
