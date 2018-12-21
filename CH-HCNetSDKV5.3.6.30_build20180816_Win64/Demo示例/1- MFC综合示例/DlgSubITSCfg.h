#if !defined(AFX_DLGSUBITSCFG_H__135DAC87_925E_4A2C_9BCD_B59A0FE2E64E__INCLUDED_)
#define AFX_DLGSUBITSCFG_H__135DAC87_925E_4A2C_9BCD_B59A0FE2E64E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSubITSCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSubITSCfg dialog

class CSubDlgITSCfg : public CDialog
{
// Construction
public:
	CSubDlgITSCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSubITSCfg)
	enum { IDD = IDD_SUB_DLG_ITS_CFG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSubITSCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSubITSCfg)
	afx_msg void OnBtnTs();
	afx_msg void OnBtnItsIoinCfg();
	afx_msg void OnBtnItsConfig();
	afx_msg void OnBtnItsMonitor();
	afx_msg void OnBtnItsMiniPost();
	afx_msg void OnBtnWifiServerCfg();
	afx_msg void OnBtnMobileTriggerCfg();
	afx_msg void OnBtnFtpUpload();
    afx_msg void OnBtnPostRadarCfg();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void CurCfgUpdate();
public:
	LONG m_lUserID;
	LONG m_lChannel;
	LONG m_lDeviceIndex;
	LONG m_lChanCount;
    afx_msg void OnBnClickedButtonUhfRfidReader();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSUBITSCFG_H__135DAC87_925E_4A2C_9BCD_B59A0FE2E64E__INCLUDED_)
