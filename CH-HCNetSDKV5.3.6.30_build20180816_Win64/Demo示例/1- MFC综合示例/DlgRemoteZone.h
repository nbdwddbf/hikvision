#if !defined(AFX_DLGREMOTEZONE_H__EE8AB6AF_1A93_46DA_8696_127ADEE9D654__INCLUDED_)
#define AFX_DLGREMOTEZONE_H__EE8AB6AF_1A93_46DA_8696_127ADEE9D654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteZone.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteZone dialog

class CDlgRemoteZone : public CDialog
{
// Construction
public:
	CDlgRemoteZone(CWnd* pParent = NULL);   // standard constructor
	NET_DVR_ZONEANDDST m_struZoneAndDst;
	int m_iDeviceIndex;
// Dialog Data
	//{{AFX_DATA(CDlgRemoteZone)
	enum { IDD = IDD_DLG_REMOTE_ZONE };
	CComboBox	m_comboZone;
	CComboBox	m_comboWeekNo2;
	CComboBox	m_comboWeekNo;
	CComboBox	m_comboWeekDate2;
	CComboBox	m_comboWeekDate;
	CComboBox	m_comboMonth;
	CComboBox	m_comboMonth2;
	CComboBox	m_comboMinute2;
	CComboBox	m_comboMinute;
	CComboBox	m_comboHour2;
	CComboBox	m_comboHour;
	CComboBox	m_comboEnableDst;
	CComboBox	m_comboDstOffSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteZone)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteZone)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTEZONE_H__EE8AB6AF_1A93_46DA_8696_127ADEE9D654__INCLUDED_)
