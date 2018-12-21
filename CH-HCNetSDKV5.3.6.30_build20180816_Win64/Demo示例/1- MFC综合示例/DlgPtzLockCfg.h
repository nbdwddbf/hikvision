#if !defined(AFX_DLGPTZLOCKCFG_H__544E593D_C344_42E4_8A26_69BD30FA3BC1__INCLUDED_)
#define AFX_DLGPTZLOCKCFG_H__544E593D_C344_42E4_8A26_69BD30FA3BC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPtzLockCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzLockCfg dialog

class CDlgPtzLockCfg : public CDialog
{
// Construction
public:
	CDlgPtzLockCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPtzLockCfg)
	enum { IDD = IDD_DLG_PTZ_LOCKCFG };
	CComboBox	m_cmbWorkMode;
	CComboBox	m_cmbChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPtzLockCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPtzLockCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUserID;
    int m_iDevIndex;
    LONG m_lChannel;
    NET_DVR_PTZ_LOCKCFG m_struPtzLockCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPTZLOCKCFG_H__544E593D_C344_42E4_8A26_69BD30FA3BC1__INCLUDED_)
