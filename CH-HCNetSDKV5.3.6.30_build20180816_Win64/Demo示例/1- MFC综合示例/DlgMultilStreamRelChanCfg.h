#if !defined(AFX_DLGMULTILSTREAMRELCHANCFG_H__A4BF1580_130D_4EE4_9B59_04F38E9937B8__INCLUDED_)
#define AFX_DLGMULTILSTREAMRELCHANCFG_H__A4BF1580_130D_4EE4_9B59_04F38E9937B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMultilStreamRelChanCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMultilStreamRelChanCfg dialog

class CDlgMultilStreamRelChanCfg : public CDialog
{
// Construction
public:
	CDlgMultilStreamRelChanCfg(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;

// Dialog Data
	//{{AFX_DATA(CDlgMultilStreamRelChanCfg)
	enum { IDD = IDD_DLG_MULTISTREAM_RELATION_CHAN_CFG };
	CComboBox	m_cmbRelChan;
	CComboBox	m_cmbMultiStreamNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMultilStreamRelChanCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMultilStreamRelChanCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMULTILSTREAMRELCHANCFG_H__A4BF1580_130D_4EE4_9B59_04F38E9937B8__INCLUDED_)
