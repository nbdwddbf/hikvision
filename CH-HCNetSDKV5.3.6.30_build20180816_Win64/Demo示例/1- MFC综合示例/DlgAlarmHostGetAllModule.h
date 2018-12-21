#if !defined(AFX_DLGALARMHOSTGETALLMODULE_H__2A2F8C1D_6CE7_4031_97FF_A925BF5A3D74__INCLUDED_)
#define AFX_DLGALARMHOSTGETALLMODULE_H__2A2F8C1D_6CE7_4031_97FF_A925BF5A3D74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostGetAllModule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAlarmHostGetAllModule dialog

class DlgAlarmHostGetAllModule : public CDialog
{
// Construction
public:
	DlgAlarmHostGetAllModule(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAlarmHostGetAllModule)
	enum { IDD = IDD_DLG_GET_ALL_MODULE };
	CListCtrl	m_listData;
	CComboBox	m_comModuleType;
	//}}AFX_DATA


	int m_iDevIndex;
	LONG m_lServerID;
	LONG m_lTranHandle;
	BOOL m_bGetNext;
	HANDLE	m_hGetInfoThread;
	NET_DVR_MODULE_INFO m_struModuleInfo;
	int m_iRowCount;

	static DWORD WINAPI GetConfigThread (LPVOID lpArg);
	void AddInfoToDlg();
	BOOL OnInitDialog();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAlarmHostGetAllModule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAlarmHostGetAllModule)
	afx_msg void OnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTGETALLMODULE_H__2A2F8C1D_6CE7_4031_97FF_A925BF5A3D74__INCLUDED_)
