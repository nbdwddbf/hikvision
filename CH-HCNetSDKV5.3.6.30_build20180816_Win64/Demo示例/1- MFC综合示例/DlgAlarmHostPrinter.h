#if !defined(AFX_DLGALARMHOSTPRINTER_H__C27A0598_B085_45DB_8033_DC2A78952726__INCLUDED_)
#define AFX_DLGALARMHOSTPRINTER_H__C27A0598_B085_45DB_8033_DC2A78952726__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostPrinter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostPrinter dialog

class CDlgAlarmHostPrinter : public CDialog
{
// Construction
public:
	CDlgAlarmHostPrinter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostPrinter)
	enum { IDD = IDD_DLG_ALARMHOST_PRINTER };
	CListCtrl	m_listOperateInfo;
	CListCtrl	m_listDeviceInfo;
	CListCtrl	m_listAlarmInfo;
	BOOL	m_chEnable;
	BOOL	m_chPrintTime;
	BOOL	m_chFault;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostPrinter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostPrinter)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	int m_iDeviceIndex;
	long m_lUserID;
	char m_szLan[128];
	NET_DVR_ALARMHOST_PRINTER_CFG m_struPrinter;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTPRINTER_H__C27A0598_B085_45DB_8033_DC2A78952726__INCLUDED_)
