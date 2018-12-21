#if !defined(AFX_DLGINFRARED_H__41FAFEEB_61D5_4A89_B70B_38CAE003736A__INCLUDED_)
#define AFX_DLGINFRARED_H__41FAFEEB_61D5_4A89_B70B_38CAE003736A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfrared.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInfrared dialog

class CDlgInfrared : public CDialog
{
// Construction
public:
	CDlgInfrared(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfrared)
	enum { IDD = IDD_DLG_INFRARED };
	CComboBox	m_cmbIRPortLearn;
	CComboBox	m_cmbCtrlLearn;
	CComboBox	m_cmbCMDCtrlName;
	CComboBox	m_cmbInfraredCtrl;
	CComboBox	m_cmbInfraredPort;
	CString	m_csCmd1Name;
	CString	m_csCmd10Name;
	CString	m_csCmd11Name;
	CString	m_csCmd12Name;
	CString	m_csCmd13Name;
	CString	m_csCmd14Name;
	CString	m_csCmd15Name;
	CString	m_csCmd16Name;
	CString	m_csCmd17Name;
	CString	m_csCmd18Name;
	CString	m_csCmd19Name;
	CString	m_csCmd2Name;
	CString	m_csCmd20Name;
	CString	m_csCmd21Name;
	CString	m_csCmd22Name;
	CString	m_csCmd23Name;
	CString	m_csCmd24Name;
	CString	m_csCmd25Name;
	CString	m_csCmd26Name;
	CString	m_csCmd27Name;
	CString	m_csCmd28Name;
	CString	m_csCmd29Name;
	CString	m_csCmd3Name;
	CString	m_csCmd30Name;
	CString	m_csCmd31Name;
	CString	m_csCmd32Name;
	CString	m_csCmd4Name;
	CString	m_csCmd5Name;
	CString	m_csCmd6Name;
	CString	m_csCmd7Name;
	CString	m_csCmd8Name;
	CString	m_csCmd9Name;
	CString	m_csInfraredPortName;
	CString	m_csInfraredCtrlName;
	BOOL	m_bSave;
	BOOL	m_bSaveLearnCmd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfrared)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfrared)
	afx_msg void OnBtnIrNameCfgSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnIrNameCfgGet();
	afx_msg void OnBtnSendCtrlCmd();
	afx_msg void OnSelchangeCmbInfraredPortCtrl();
	afx_msg void OnBtnLearn();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStopLearn();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    long m_lUserID;
    int m_iDevIndex;
    NET_DVR_INFRARED_CMD_NAME_CFG  m_struInfraredCmdNameCfg;
    NET_DVR_INFRARED_OUTPUT_CTRL_CFG m_struIROutPutCtrlCfg;

    LONG m_lInfraredHandle;
    NET_DVR_INFRARED_LEARN_INFO m_struInfraredLearnInfo;
    NET_DVR_INFRARED_LEARN_END  m_struInfraredEnd;
protected:
    void ShowChangeCMDNameInfo(); 
    void ShowCMDCtrlInfo();
    void OnGetInfraredPortName(DWORD dwIRPort);
    BOOL m_bStopLearn;
protected:
    LRESULT OnChangeInfraredLearnStatus(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFRARED_H__41FAFEEB_61D5_4A89_B70B_38CAE003736A__INCLUDED_)
