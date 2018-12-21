#if !defined(AFX_DLGLOCALINPUTINFO_H__4C19F398_D61E_4672_9417_86C81C8F195E__INCLUDED_)
#define AFX_DLGLOCALINPUTINFO_H__4C19F398_D61E_4672_9417_86C81C8F195E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLocalInputInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLocalInputInfo dialog

class CDlgLocalInputInfo : public CDialog
{
// Construction
public:
	CDlgLocalInputInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLocalInputInfo)
	enum { IDD = IDD_DLG_LOCAL_INPUT_INFO };
	CComboBox	m_comboInputChan;
	CString	m_sChannel;
	//}}AFX_DATA
	void setParam(NET_DVR_TRIAL_SYSTEM_INFO struTrialSystemInfo);
	NET_DVR_TRIAL_SYSTEM_INFO m_struTrialSystemInfo;
	NET_DVR_LOCAL_INPUT_INFO m_struLocalInputInfo;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLocalInputInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLocalInputInfo)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOCALINPUTINFO_H__4C19F398_D61E_4672_9417_86C81C8F195E__INCLUDED_)
