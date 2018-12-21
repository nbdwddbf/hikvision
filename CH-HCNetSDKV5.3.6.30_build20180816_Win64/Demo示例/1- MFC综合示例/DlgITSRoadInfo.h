#if !defined(AFX_DLGITSROADINFO_H__AF31766F_85FA_4EE5_B2B9_D8B089E70BB3__INCLUDED_)
#define AFX_DLGITSROADINFO_H__AF31766F_85FA_4EE5_B2B9_D8B089E70BB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSRoadInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSRoadInfo dialog

class CDlgITSRoadInfo : public CDialog
{
// Construction
public:
	CDlgITSRoadInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgITSRoadInfo)
	enum { IDD = IDD_DLG_ITS_ROADINFO_GET };
	CComboBox	m_comboTriggerMode;
	CComboBox	m_comboDeviceType;
	CComboBox	m_comboDeviceNO;
	DWORD	m_dwChannel;
	CString	m_csDeviceName;
	DWORD	m_dwDeviceNum;
	DWORD	m_dwDeviceState;
	DWORD	m_dwDirectionNO;
	CString	m_csDeviceID;
	DWORD	m_dwLaneID;
	CString	m_csMonitorID;
	CString	m_csMonitorInfo;
    BYTE    m_byRelateChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSRoadInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSRoadInfo)
	afx_msg void OnBtnGet();
	afx_msg void OnSelchangeComboDeviceNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lChannel; 
    int  m_iDevIndex;
    LONG m_lServerID;
	NET_ITS_ROADINFO m_struRoadInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSROADINFO_H__AF31766F_85FA_4EE5_B2B9_D8B089E70BB3__INCLUDED_)
