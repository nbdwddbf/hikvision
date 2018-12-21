#if !defined(AFX_DLGWDRCFG_H__7EB00F9D_86AB_4F8B_96ED_0830DB5CAB37__INCLUDED_)
#define AFX_DLGWDRCFG_H__7EB00F9D_86AB_4F8B_96ED_0830DB5CAB37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWDRCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWDRCfg dialog

class CDlgWDRCfg : public CDialog
{
// Construction
public:
	CDlgWDRCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWDRCfg)
	enum { IDD = IDD_DLG_WDR_CFG };
	CComboBox	m_cmbChannel;
	BOOL	m_bEnable;
    BYTE    m_byLevel1;
    BYTE    m_byLevel2;
    BYTE    m_byContrastLevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWDRCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
    public:
        LONG  m_lUserID;
        LONG  m_iDevIndex;
        NET_DVR_WDR_CFG  m_struWDRCfg;
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWDRCfg)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWDRCFG_H__7EB00F9D_86AB_4F8B_96ED_0830DB5CAB37__INCLUDED_)
