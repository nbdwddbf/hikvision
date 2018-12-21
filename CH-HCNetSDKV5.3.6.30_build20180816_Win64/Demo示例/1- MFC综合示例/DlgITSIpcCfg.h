#if !defined(AFX_DLGITSIPCCFG_H__FF42EEED_6850_4ED0_89B3_9A6DC736D7CE__INCLUDED_)
#define AFX_DLGITSIPCCFG_H__FF42EEED_6850_4ED0_89B3_9A6DC736D7CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSIpcCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSIpcCfg dialog

class CDlgITSIpcCfg : public CDialog
{
// Construction
public:
	CDlgITSIpcCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgITSIpcCfg)
	enum { IDD = IDD_DLG_ITS_IPC_CFG };
	CComboBox	m_comboIpcType;
	CComboBox	m_comboDirectionType;
	CString	m_csDeviceID;
	CString	m_csMointorInfo;
	CString	m_csMointorID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSIpcCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSIpcCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lChannel; 
    int  m_iDevIndex;
    LONG m_lServerID;
	NET_ITS_IPC_CHAN_CFG m_struIPCChan;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSIPCCFG_H__FF42EEED_6850_4ED0_89B3_9A6DC736D7CE__INCLUDED_)
