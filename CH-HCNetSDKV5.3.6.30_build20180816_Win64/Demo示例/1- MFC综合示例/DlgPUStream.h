#if !defined(AFX_DLGPUSTREAM_H__E7EAA7D2_92B0_4C86_AA05_DDA0721A1B33__INCLUDED_)
#define AFX_DLGPUSTREAM_H__E7EAA7D2_92B0_4C86_AA05_DDA0721A1B33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPUStream.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPUStream dialog

class CDlgPUStream : public CDialog
{
// Construction
public:
	CDlgPUStream(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPUStream)
	enum { IDD = IDD_DLG_PU_STREAM };
	CIPAddressCtrl	m_ipStream;
	CIPAddressCtrl	m_ipDvr;
	CComboBox	m_comboStreamTransType;
	CComboBox	m_comboDvrTransMode;
	CComboBox	m_comboDvrTransProtocol;
	BOOL	m_bStreamValid;
	int		m_iDvrPort;
	CString	m_csPassword;
	int		m_iStreamPort;
	CString	m_csUserName;
	int		m_iDvrChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPUStream)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPUStream)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckStreamValid();
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL EnableStream(BOOL bEnable);
	BOOL GetPUStreamPara();
	BOOL SetVcaIvmsSched();
	NET_DVR_PU_STREAM_CFG m_struPUStream; //parameter of getting stream from front-end device
    int m_iDevIndex ;
    LONG m_lServerID;
    LONG m_lChannel;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPUSTREAM_H__E7EAA7D2_92B0_4C86_AA05_DDA0721A1B33__INCLUDED_)
