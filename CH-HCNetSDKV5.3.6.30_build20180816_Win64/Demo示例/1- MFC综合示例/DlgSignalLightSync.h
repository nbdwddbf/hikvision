#if !defined(AFX_DLGSIGNALLIGHTSYNC_H__0904CEC1_2BC7_4EC5_9DC7_1FC963795251__INCLUDED_)
#define AFX_DLGSIGNALLIGHTSYNC_H__0904CEC1_2BC7_4EC5_9DC7_1FC963795251__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSignalLightSync.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSignalLightSync dialog

class CDlgSignalLightSync : public CDialog
{
// Construction
public:
	long m_iCurChanNO;
	long m_lUserID;
	CDlgSignalLightSync(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSignalLightSync)
	enum { IDD = IDD_DLG_SIGNALLIGHT_SYNC };
	CComboBox	m_cbLinkLock;
	int	m_wPhase;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSignalLightSync)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSignalLightSync)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSIGNALLIGHTSYNC_H__0904CEC1_2BC7_4EC5_9DC7_1FC963795251__INCLUDED_)
