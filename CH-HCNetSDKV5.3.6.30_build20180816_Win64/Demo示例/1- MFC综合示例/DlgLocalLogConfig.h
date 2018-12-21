#pragma once


// CDlgLocalLogConfig dialog

class CDlgLocalLogConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgLocalLogConfig)

public:
	CDlgLocalLogConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLocalLogConfig();

// Dialog Data
	enum { IDD = IDD_DLG_LOCAL_LOG_CONFIG };


public:
	//{{AFX_DATA(CDlgLocalLogConfig)
	BOOL m_bChkAlarmInfo;
	BOOL m_bChkSuccInfo;
	BOOL m_bChkFailInfo;
	BOOL m_bChkAutoSaveLog;
	BOOL m_bChkOutputDebugString;
	//}}AFX_DATA



	//{{AFX_VIRTUAL(CTransparentTrans)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgLocalLogConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnLocalLogOk();
	afx_msg void OnBnClickedBtnLocalLogExit();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	CRITICAL_SECTION m_csLock;
	
};
