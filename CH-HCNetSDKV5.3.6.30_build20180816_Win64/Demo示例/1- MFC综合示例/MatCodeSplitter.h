#if !defined(AFX_MATCODESPLITTER_H__DEBCA202_627A_4DBF_8853_EB0B4A19BC97__INCLUDED_)
#define AFX_MATCODESPLITTER_H__DEBCA202_627A_4DBF_8853_EB0B4A19BC97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatCodeSplitter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatCodeSplitter dialog

class CMatCodeSplitter : public CDialog
{
// Construction
public:
	CMatCodeSplitter(CWnd* pParent = NULL);   // standard constructor

    LONG m_lServerID;
    NET_DVR_CODESPLITTERINFO m_CodeSplitterInfo[4];
// Dialog Data
	//{{AFX_DATA(CMatCodeSplitter)
	enum { IDD = IDD_DLG_MATCODESPLITTER1 };
	CComboBox	m_FlowControlCtrl;
	CComboBox	m_StopBitCtrl;
	CComboBox	m_ParityCtrl;
	CComboBox	m_DataBitCtrl;
	CComboBox	m_BaudRateCtrl;
	CComboBox	m_DecoderTypeCtrl;
	CComboBox	m_DecoderChanCtrl;
	CComboBox	m_CodeNumCtrl;
	int		m_iDecoderAddress;
	CString	m_strCodeSplitterIp;
	CString	m_strCodeSplitterName;
	CString	m_strCodeSplitterPsw;
	DWORD	m_dwCodeSplitterPort;
	int		m_iDecoderAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatCodeSplitter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatCodeSplitter)
	afx_msg void OnExit();
	afx_msg void OnGetcodesplitter();
	afx_msg void OnSetcodesplitter();
	virtual BOOL OnInitDialog();
//	afx_msg void OnSelchangeCombobaudrate();
	afx_msg void OnButtonSure();
	afx_msg void OnSelchangeCombocodenum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATCODESPLITTER_H__DEBCA202_627A_4DBF_8853_EB0B4A19BC97__INCLUDED_)
