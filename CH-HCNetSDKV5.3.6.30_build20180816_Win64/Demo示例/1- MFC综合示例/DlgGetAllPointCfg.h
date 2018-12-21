#if !defined(AFX_DLGGETALLPOINTCFG_H__A7B13BEC_397A_446F_AB07_C869DD08F5C8__INCLUDED_)
#define AFX_DLGGETALLPOINTCFG_H__A7B13BEC_397A_446F_AB07_C869DD08F5C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetAllPointCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllPointCfg dialog

class DlgGetAllPointCfg : public CDialog
{
// Construction
public:
	DlgGetAllPointCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgGetAllPointCfg)
	enum { IDD = IDD_DLG_GET_ALL_POINT_CFG };
	CListCtrl	m_listPointCfg;
	//}}AFX_DATA
	NET_DVR_ALARM_POINT_CFG m_struAlarmPointCfg;
	DWORD m_iDeviceIndex;
	LONG m_lUserID;
	long m_lHandle;
	BOOL m_bGetNext;
	HANDLE	m_hGetInfoThread;
	DWORD m_iRowCount;
	char m_sTemp[256];
	void AddInfoToDlg();
	static DWORD WINAPI GetConfigThread (LPVOID lpArg);
	BOOL OnInitDialog();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgGetAllPointCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgGetAllPointCfg)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETALLPOINTCFG_H__A7B13BEC_397A_446F_AB07_C869DD08F5C8__INCLUDED_)
