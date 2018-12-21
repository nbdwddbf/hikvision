#if !defined(AFX_DLGIOOUTCFG_H__523CA3D3_BE1B_401C_B5CA_C153833A6F52__INCLUDED_)
#define AFX_DLGIOOUTCFG_H__523CA3D3_BE1B_401C_B5CA_C153833A6F52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIOOutCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIOOutCfg dialog

class CDlgIOOutCfg : public CDialog
{
// Construction
public:
	void SaveData();
	void EnableTimeCtrl(BOOL bEnable);
	void EnableWindows(BOOL bEnable);
	void UpdateCtrlData();
	long m_iDeviceIndex;
	long m_lUserID;
	int m_pStatusGetList[3];
	int	m_pStatusSetList[3];
	
	CDlgIOOutCfg(CWnd* pParent = NULL);   // standard constructor

	NET_DVR_IOOUT_CFG m_struIOOutCfg;
	NET_DVR_IOOUT_COND m_struIOOutCfgCond;
	int m_iStatus;
// Dialog Data
	//{{AFX_DATA(CDlgIOOutCfg)
	enum { IDD = IDD_DLG_IOOUTCFG };
	CComboBox	m_cbDefaultState;
	CComboBox	m_cbWorkState;
	CComboBox	m_cbWorkMode;
	CComboBox	m_cbSyncOutputNo;
	BOOL	m_bChkFlashLightEnable;
	BYTE	m_byEndHour;
	BYTE	m_byDutyRatio;
	BYTE	m_byEndMin;
	BYTE	m_byFreqMulti;
	BYTE	m_byStartHour;
	BYTE	m_byStartMin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIOOutCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIOOutCfg)
	afx_msg void OnButtonGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckEnableFlashlight();
	afx_msg void OnSelchangeComboWorkmode();
	afx_msg void OnButtonSet();
	afx_msg void OnSelchangeComboSyncOutputno();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIOOUTCFG_H__523CA3D3_BE1B_401C_B5CA_C153833A6F52__INCLUDED_)
