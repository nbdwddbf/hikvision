#if !defined(AFX_DLGALARMKEYBOARDUSER_H__CD35D6BD_74F7_4DB2_AD60_78D1B5DC15BD__INCLUDED_)
#define AFX_DLGALARMKEYBOARDUSER_H__CD35D6BD_74F7_4DB2_AD60_78D1B5DC15BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmKeyboardUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmKeyboardUser dialog

class CDlgAlarmKeyboardUser : public CDialog
{
// Construction
public:
	CDlgAlarmKeyboardUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmKeyboardUser)
	enum { IDD = IDD_DLG_ALARMHOST_KEYBOARD_USER };
	CListCtrl	m_listAlarmIn;
	CComboBox	m_comboUserIndex;
	UINT	m_dwUserID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmKeyboardUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmKeyboardUser)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboUserIndex();
	afx_msg void OnBtnSetup();
	afx_msg void OnRclickListAlarmIn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuCancelAll();
	afx_msg void OnMenuSelectAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    DWORD   m_dwKeyboardUserNum;
    DWORD   m_dwAlarmInNum;
    
    LONG m_lUserIndex;
    NET_DVR_KEYBOARD_USER m_struKeyboardUser;
public:
    void InitWnd();
    void InitUserIndexCombo();
    void InitAlarmInList();

    BOOL GetKeyboardUser(NET_DVR_KEYBOARD_USER &struKeyboardUser);
    BOOL SetKeyboardUser(NET_DVR_KEYBOARD_USER &struKeyboardUser);

    void GetKeyboardUserFromWnd(NET_DVR_KEYBOARD_USER &struKeyboardUser);
    void SetKeyboardUserToWnd(NET_DVR_KEYBOARD_USER &struKeyboardUser);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMKEYBOARDUSER_H__CD35D6BD_74F7_4DB2_AD60_78D1B5DC15BD__INCLUDED_)
