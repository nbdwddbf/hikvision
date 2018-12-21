#if !defined(AFX_DLGPICMODELCFG_H__B7280DBE_442F_4DE8_A211_6F4FA7D4837C__INCLUDED_)
#define AFX_DLGPICMODELCFG_H__B7280DBE_442F_4DE8_A211_6F4FA7D4837C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPicModelCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPicModelCfg dialog

class CDlgPicModelCfg : public CDialog
{
// Construction
public:
	CDlgPicModelCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPicModelCfg)
	enum { IDD = IDD_DLG_PIC_MODEL_CFG };
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPicModelCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPicModelCfg)
	afx_msg void OnBtnGet();
    afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUserID;
    LONG m_iDevIndex;
protected:
    NET_DVR_PIC_MODEL_CFG m_struPicModelCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPICMODELCFG_H__B7280DBE_442F_4DE8_A211_6F4FA7D4837C__INCLUDED_)

