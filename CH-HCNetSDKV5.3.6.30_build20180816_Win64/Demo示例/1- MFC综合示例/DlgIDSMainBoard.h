#if !defined(AFX_DLGIDSMAINBOARD_H__707B0CE6_5DCB_4E46_8219_FCABF4382557__INCLUDED_)
#define AFX_DLGIDSMAINBOARD_H__707B0CE6_5DCB_4E46_8219_FCABF4382557__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIDSMainBoard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIDSMainBoard dialog

class CDlgIDSMainBoard : public CDialog
{
// Construction
public:
	CDlgIDSMainBoard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIDSMainBoard)
	enum { IDD = IDD_DLG_IDS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIDSMainBoard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIDSMainBoard)
	afx_msg void OnBtnGerAllModule();
	afx_msg void OnBtnSubSystemAlarm();
	afx_msg void OnBtnWhiteListCfg();
	afx_msg void OnBtnWirelessBusinnessSearch();
	afx_msg void OnBtnGetAllRemoteController();
	afx_msg void OnBtnRemoteControllerCfg();
	afx_msg void OnBtnKeyboradCfg();
	afx_msg void OnBtnAlarmCaptrueCfg();
	afx_msg void OnBtnLinkageChan();
	afx_msg void OnBtnCenterSvrCfg();
	afx_msg void OnBnClickedBtnDelayPreviewCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIDSMAINBOARD_H__707B0CE6_5DCB_4E46_8219_FCABF4382557__INCLUDED_)
