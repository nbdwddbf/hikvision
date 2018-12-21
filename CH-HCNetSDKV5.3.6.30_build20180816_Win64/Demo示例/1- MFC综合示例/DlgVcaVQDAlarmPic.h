#if !defined(AFX_DLGVCAVQDALARMPIC_H__C635C6DF_3653_4B61_A106_53699CD9E19E__INCLUDED_)
#define AFX_DLGVCAVQDALARMPIC_H__C635C6DF_3653_4B61_A106_53699CD9E19E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "VcaCommonOperations.h"
// DlgVcaVQDAlarmPic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaVQDAlarmPic dialog

class CDlgVcaVQDAlarmPic : public CDialog,public CVcaCommonOperations
{
// Construction
public:
	CDlgVcaVQDAlarmPic(CWnd* pParent = NULL);   // standard constructor

	enum DOWNLOAD_STATUS
	{
		DOWNLOAD_STATUS_FINISH = 1,
		DOWNLOAD_STATUS_PROCESSING = 2,
		DOWNLOAD_STATUS_FAILED = 3,
	    DOWNLOAD_STATUS_NETWORK_ERROR = 4
	};
// Dialog Data
	//{{AFX_DATA(CDlgVcaVQDAlarmPic)
	enum { IDD = IDD_DLG_VCA_VQD_ALARMPIC };
	CProgressCtrl	m_ctrlDownloadProgress;
	CComboBox	m_comboVQDEvent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaVQDAlarmPic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaVQDAlarmPic)
	afx_msg void OnBtnDownloadAlarmPic();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg LRESULT OnMsgDownloadAlarmPicFinish(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void InitCtrlState();
	void DownLoadVQDEventAlarmPic();
private:
	LONG m_lDownloadHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAVQDALARMPIC_H__C635C6DF_3653_4B61_A106_53699CD9E19E__INCLUDED_)
