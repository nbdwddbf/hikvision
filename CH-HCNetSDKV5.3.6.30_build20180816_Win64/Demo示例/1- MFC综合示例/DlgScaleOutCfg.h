#if !defined(AFX_DLGSCALEOUTCFG_H__FCE7BA27_E369_4EA9_9723_5FED771328B5__INCLUDED_)
#define AFX_DLGSCALEOUTCFG_H__FCE7BA27_E369_4EA9_9723_5FED771328B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgScaleOutCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgScaleOutCfg dialog

class CDlgScaleOutCfg : public CDialog
{
// Construction
public:
	CDlgScaleOutCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgScaleOutCfg)
	enum { IDD = IDD_DLG_OUT_SCALE_CFG };
	CComboBox	m_comboOutScale8;
	CComboBox	m_comboOutScale7;
	CComboBox	m_comboOutScale6;
	CComboBox	m_comboOutScale5;
	CComboBox	m_comboOutScale4;
	CComboBox	m_comboOutScale3;
	CComboBox	m_comboOutScale2;
	CComboBox	m_comboOutScale;
	//}}AFX_DATA

	int m_iDeviceIndex;
	LONG m_lUserID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgScaleOutCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgScaleOutCfg)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCALEOUTCFG_H__FCE7BA27_E369_4EA9_9723_5FED771328B5__INCLUDED_)
