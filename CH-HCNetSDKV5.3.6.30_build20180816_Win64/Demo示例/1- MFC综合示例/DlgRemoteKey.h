#pragma once


// CDlgRemoteKey dialog

class CDlgRemoteKey : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteKey)

public:
	CDlgRemoteKey(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteKey();

// Dialog Data


public:

	//{{AFX_DATA(CDlgRemoteKey)
	enum { IDD = IDD_DLG_REMOTE_KEY };
	int		m_iPanSel;
	int		m_iOutputSel;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteKey)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteKey)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRemoteKeyExit();
	afx_msg void OnBnClickedBtn0();
	afx_msg void OnBnClickedBtn2();
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn3();
	afx_msg void OnBnClickedBtn4();
	afx_msg void OnBnClickedBtn5();
	afx_msg void OnBnClickedBtn6();
	afx_msg void OnBnClickedBtn7();
	afx_msg void OnBnClickedBtn8();
	afx_msg void OnBnClickedBtn9();
	afx_msg void OnBnClickedBtnMainMenu();
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnRec();
	afx_msg void OnBnClickedBtnMulti();
	afx_msg void OnBnClickedBtnA();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnEsc();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnBnClickedBtnLeft();
	afx_msg void OnBnClickedBtnRight();
	afx_msg void OnBnClickedBtnSysInfo();
	afx_msg void OnBnClickedBtnVoip();
	afx_msg void OnBnClickedBtnPan();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBtn16();
	afx_msg void OnBtn15();
	afx_msg void OnBtn14();
	afx_msg void OnBtn13();
	afx_msg void OnBtn12();
	afx_msg void OnBtn11();
	afx_msg void OnBtnStartPanel();
	afx_msg void OnBtnStopPanel();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	LONG m_lServerID;
	
	
};
