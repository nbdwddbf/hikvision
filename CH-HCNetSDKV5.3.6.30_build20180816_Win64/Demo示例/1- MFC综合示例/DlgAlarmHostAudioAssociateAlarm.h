#if !defined(AFX_DLGALARMHOSTAUDIOASSOCIATEALARM_H__09CF673B_B5AF_4CAC_B0D2_EC5C0A3B0D67__INCLUDED_)
#define AFX_DLGALARMHOSTAUDIOASSOCIATEALARM_H__09CF673B_B5AF_4CAC_B0D2_EC5C0A3B0D67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostAudioAssociateAlarm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostAudioAssociateAlarm dialog

class CDlgAlarmHostAudioAssociateAlarm : public CDialog
{
// Construction
public:
	CDlgAlarmHostAudioAssociateAlarm(CWnd* pParent = NULL);   // standard constructor
	int		m_iDeviceIndex;
	long	m_lUserID;
	char	m_szLan[128];
	NET_DVR_ALARMHOST_ABILITY m_struAbility;
	NET_DVR_ALARMHOST_AUDIO_ASSOCIATE_ALARM m_struAudioAssoiateAlarm;
	int		m_iCurrentAudioIndex;
// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostAudioAssociateAlarm)
	enum { IDD = IDD_DLG_ALARMHOST_AUDIO_ASSIOCIATE_ALARM };
	CListCtrl	m_listExitDoor;
	CListCtrl	m_listEnterDoor;
	CListCtrl	m_listAlarmIn;
	CComboBox	m_cmAudioNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostAudioAssociateAlarm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostAudioAssociateAlarm)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSelectall();
	afx_msg void OnBtnCancelall();
	afx_msg void OnSelchangeComboAudioNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void GetDataFromDlg();
	void SetCurrentDataToDlg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTAUDIOASSOCIATEALARM_H__09CF673B_B5AF_4CAC_B0D2_EC5C0A3B0D67__INCLUDED_)
