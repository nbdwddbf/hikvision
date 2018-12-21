#if !defined(AFX_DLGTRIALPIPCFG_H__1844BE9E_9C4D_4BA7_8DA0_A4E49E7A3525__INCLUDED_)
#define AFX_DLGTRIALPIPCFG_H__1844BE9E_9C4D_4BA7_8DA0_A4E49E7A3525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrialPIPCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialPIPCfg dialog

class CDlgTrialPIPCfg : public CDialog
{
// Construction
public:
	CDlgTrialPIPCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTrialPIPCfg)
	enum { IDD = IDD_DLG_TRIAL_PIP_CFG };
	CComboBox	m_cmbShowMode;
	CComboBox	m_cmbShowChan;
	CComboBox	m_cmbShowPosition;
	CComboBox	m_cmbPipChanNum;
	UINT	m_dwX;
	UINT	m_dwY;
	UINT	m_dwHeight;
	UINT	m_dwWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrialPIPCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrialPIPCfg)
	afx_msg void OnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCmbShowPos();
	afx_msg void OnSet();
	afx_msg void OnMode();
	afx_msg void OnSelchangeCmbPipChanNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    long m_lUserID;
    int m_iDevIndex;
    NET_DVR_TRIAL_SYSTEM_INFO m_struSystemInfo;

protected:
    NET_DVR_INQUEST_PIP_STATUS_V40 m_struInquestPIPStatus;
private:
    void AddChanItemInfo(CComboBox* cmbBox);
    void AddPIPShowModeInfo();
    void ShowCurPIPInfo();
    void SelectCmbBoxByData(CComboBox* cmbBox, DWORD dwFindData);
    DWORD m_dwLastShowChanIndex;
    void SaveLastSmallChanInfo(DWORD dwChaIndex);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRIALPIPCFG_H__1844BE9E_9C4D_4BA7_8DA0_A4E49E7A3525__INCLUDED_)
