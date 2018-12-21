#if !defined(AFX_DLGGETWIFICLIENTLISTINFO_H__2ED82FB0_F6C7_4E6A_BC0A_80B6CEF18504__INCLUDED_)
#define AFX_DLGGETWIFICLIENTLISTINFO_H__2ED82FB0_F6C7_4E6A_BC0A_80B6CEF18504__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetWifiClientListInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGetWifiClientListInfo dialog

class CDlgGetWifiClientListInfo : public CDialog
{
// Construction
public:
	CDlgGetWifiClientListInfo(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;

	NET_DVR_WIFI_CLIENT_INFO m_struWifiClientInfo;
	long m_lHandle;
	BOOL m_bGetNext;
	HANDLE	m_hGetInfoThread;
	DWORD m_iRowCount;
	char m_sTemp[256];
	void AddInfoToDlg();
	static DWORD WINAPI GetConfigThread (LPVOID lpArg);

// Dialog Data
	//{{AFX_DATA(CDlgGetWifiClientListInfo)
	enum { IDD = IDD_DLG_GET_WIFI_CLIENT_LIST_INFO };
	CListCtrl	m_listClientInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGetWifiClientListInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGetWifiClientListInfo)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETWIFICLIENTLISTINFO_H__2ED82FB0_F6C7_4E6A_BC0A_80B6CEF18504__INCLUDED_)
