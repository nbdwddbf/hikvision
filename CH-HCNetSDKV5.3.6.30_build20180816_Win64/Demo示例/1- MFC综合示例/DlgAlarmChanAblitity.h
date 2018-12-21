#if !defined(AFX_DLGALARMCHANABLITITY_H__7ABF4476_29BF_4FE8_AFB2_6AF2D97E4AB5__INCLUDED_)
#define AFX_DLGALARMCHANABLITITY_H__7ABF4476_29BF_4FE8_AFB2_6AF2D97E4AB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmChanAblitity.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmChanAblitity dialog

class CDlgAlarmChanAblitity : public CDialog
{
// Construction
public:
	CDlgAlarmChanAblitity(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmChanAblitity)
	enum { IDD = IDD_DLG_ALARM_CHAN_ABLITITY };
	CListCtrl	m_listSensorChan;
	CListCtrl	m_listRs485Chan;
	CListCtrl	m_listAlarmOutChan;
	CListCtrl	m_listAlarmInChan;
	//}}AFX_DATA

	int m_iDeviceIndex;
	LONG m_lUserID;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmChanAblitity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmChanAblitity)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMCHANABLITITY_H__7ABF4476_29BF_4FE8_AFB2_6AF2D97E4AB5__INCLUDED_)
