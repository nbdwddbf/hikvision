#if !defined(AFX_DLGONEKEYPUBLISH_H__817C740D_B47B_43AD_9B5E_F9A93E228FB4__INCLUDED_)
#define AFX_DLGONEKEYPUBLISH_H__817C740D_B47B_43AD_9B5E_F9A93E228FB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOneKeyPublish.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgOneKeyPublish dialog

class DlgOneKeyPublish : public CDialog
{
// Construction
public:
	DlgOneKeyPublish(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgOneKeyPublish)
	enum { IDD = IDD_DLG_ONE_KEY_PUBLISH };
	CComboBox	m_comRecordChan;
	BOOL	m_bDefine;
	BOOL	m_bRecordPublish;
	CTime	m_ctEndData;
	CTime	m_ctEndTime;
	CTime	m_ctStartData;
	CTime	m_ctStartTime;
	BOOL	m_bRecordMainStream;
	BOOL	m_bRecordSubStream;
	BOOL	m_bRecordStreamThree;
	//}}AFX_DATA


	LONG m_lUserID;
	int  m_iDeviceIndex;
	int m_iMirrorNum;
	int m_iStartChannel;
	LONG m_lTranHandle;
	BOOL	m_bGetNext;
	HANDLE	m_hGetInfoThread;
	NET_DVR_ONEKEY_PUBLISH_CFG m_struOnekeyPublish;
	static DWORD WINAPI GetPublishInfoThread(LPVOID lpArg);
	void SetText(CString cstemp);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgOneKeyPublish)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgOneKeyPublish)
	afx_msg void OnBtnPublish();
	afx_msg void OnBtnRecordOk();
	afx_msg void OnSelchangeComboRecordChan();
	afx_msg void OnChkDefine();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGONEKEYPUBLISH_H__817C740D_B47B_43AD_9B5E_F9A93E228FB4__INCLUDED_)
