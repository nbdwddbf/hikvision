#if !defined(AFX_DLGONLINEUSERLIST_H__BA2B313C_E5B5_4B85_85E7_4390F4817B72__INCLUDED_)
#define AFX_DLGONLINEUSERLIST_H__BA2B313C_E5B5_4B85_85E7_4390F4817B72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOnlineUserList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgOnlineUserList dialog

class DlgOnlineUserList : public CDialog
{
// Construction
public:
	DlgOnlineUserList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgOnlineUserList)
	enum { IDD = IDD_DLG_ONLINE_USER };
	CComboBox	m_dwChannel;
	CListCtrl	m_listOnlineUser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgOnlineUserList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgOnlineUserList)
	virtual BOOL OnInitDialog();
    afx_msg void OnButtonGet();
    afx_msg LRESULT OnMsgGetOnlineUserListFinish(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lChannel;
    LONG m_lUserID;
    int m_iDeviceIndex;
    
    LONG        m_lOnlineUserHandle;
    MSGCallBack fMessageCallBack;
    
    void StopOnlineUserlList();
    void ProcGetOnlineUserList(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void AddOnlineUserListItem(const NET_DVR_ONLINEUSER_CFG &Item);
    BOOL ValidIPv6(BYTE *ip);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGONLINEUSERLIST_H__BA2B313C_E5B5_4B85_85E7_4390F4817B72__INCLUDED_)
