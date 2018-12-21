#if !defined(AFX_DLGALARMOPERATORUSER_H__B4337F57_002B_42FF_B041_EA3A8E57292D__INCLUDED_)
#define AFX_DLGALARMOPERATORUSER_H__B4337F57_002B_42FF_B041_EA3A8E57292D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmOperatorUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmOperatorUser dialog

class CDlgAlarmOperatorUser : public CDialog
{
// Construction
public:
	CDlgAlarmOperatorUser(CWnd* pParent = NULL);   // standard constructor
	void InitCombox();

// Dialog Data
	//{{AFX_DATA(CDlgAlarmOperatorUser)
	enum { IDD = IDD_DLG_ALARMHOST_OPERATOR_USER };
	CComboBox	m_cmSubsystem;
	CComboBox	m_comboUserIndex;
	CString	m_csPassword;
	CString	m_csUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmOperatorUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmOperatorUser)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetup();
	afx_msg void OnSelchangeComboUserIndex();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
    afx_msg void OnBtnKeyboradCfg();
    afx_msg void OnBtnKeyboardUser();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    DWORD   m_dwOperatorUserNum;
    LONG    m_lUserIndex;
    DWORD   m_dwAlarmInNum;
    int     m_iSubSystemNum;
    DWORD   m_dwKeyboardUserNum;

    NET_DVR_OPERATE_USER m_struOperatorUser;

    int     m_iPopMenuType; // 
public:
	void InitUserIndexCombo();
    
    BOOL GetOperateUser(NET_DVR_OPERATE_USER &struOperatorUser);
    BOOL SetOperateUser(NET_DVR_OPERATE_USER &struOperatorUser);

//     void GetOperateUserFromWnd(NET_DVR_OPERATE_USER &struOperatorUser);
//     void SetOperateUserToWnd(NET_DVR_OPERATE_USER &struOperatorUser);
//     void GetAlarmOnFromWnd(BYTE *byAlarmIn, DWORD dwSize);
//     void GetAlarmOffFromWnd(BYTE *byAlarmIn, DWORD dwSize);
//     void GetBypassFromWnd(BYTE *byAlarmIn, DWORD dwSize);
//     void SetAlarmOnToWnd(BYTE *byAlarmIn, DWORD dwSize);
//     void SetAlarmOffToWnd(BYTE *byAlarmIn, DWORD dwSize);
//     void SetBypassToWnd(BYTE *byAlarmIn, DWORD dwSize);
//     void SetSubSystemToWnd(BYTE *bySubSystem, DWORD dwSize);

	//     void InitWnd();
	//     void InitAlarmOnList();
	//     void InitAlarmOffList();
	//     void InitBypassList();
	//     void InitSubSystemList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMOPERATORUSER_H__B4337F57_002B_42FF_B041_EA3A8E57292D__INCLUDED_)

