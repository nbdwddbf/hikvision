#if !defined(AFX_DLGALARMHOSTDATAUPLOADMODE_H__67C30368_EC24_4516_BC50_E68ADA9BC4D4__INCLUDED_)
#define AFX_DLGALARMHOSTDATAUPLOADMODE_H__67C30368_EC24_4516_BC50_E68ADA9BC4D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmhostDataUploadMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostDataUploadMode dialog

class CDlgAlarmhostDataUploadMode : public CDialog
{
// Construction
public:
	CDlgAlarmhostDataUploadMode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmhostDataUploadMode)
	enum { IDD = IDD_DLG_ALARMHOST_DATA_UPLOAD };
	CComboBox	m_cmValueUploadMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmhostDataUploadMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmhostDataUploadMode)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_iDeviceIndex;
	long m_lUserID;
	NET_DVR_ALARMHOST_ALARM_MODE_CFG m_struAlarmMode;
	char m_szLan[128];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTDATAUPLOADMODE_H__67C30368_EC24_4516_BC50_E68ADA9BC4D4__INCLUDED_)
