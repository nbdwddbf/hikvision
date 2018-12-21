#if !defined(AFX_DLGVIDEOINTERCOMALARMCFG_H__B6A3941C_A573_406C_9078_2B7494198CCE__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMALARMCFG_H__B6A3941C_A573_406C_9078_2B7494198CCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomAlarmCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgVideoIntercomAlarmCfg dialog

class DlgVideoIntercomAlarmCfg : public CDialog
{
// Construction
public:
	DlgVideoIntercomAlarmCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgVideoIntercomAlarmCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_ALARM_CFG };
	BOOL	m_byDoorNotCloseAlarm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgVideoIntercomAlarmCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgVideoIntercomAlarmCfg)
	afx_msg void OnButtonGet();
	afx_msg void OnButtonSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMALARMCFG_H__B6A3941C_A573_406C_9078_2B7494198CCE__INCLUDED_)
