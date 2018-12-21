#if !defined(AFX_DLGCONNECTLIST_H__BAEC8C66_E4C9_4DAC_AB87_9EE73D0387A4__INCLUDED_)
#define AFX_DLGCONNECTLIST_H__BAEC8C66_E4C9_4DAC_AB87_9EE73D0387A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConnectList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgConnectList dialog

class DlgConnectList : public CDialog
{
// Construction
public:
	DlgConnectList(CWnd* pParent = NULL);   // standard constructor
	~DlgConnectList();

// Dialog Data
	//{{AFX_DATA(DlgConnectList)
	enum { IDD = IDD_DLG_CONNECT_LIST };
	CListCtrl	m_listGetConnectDev;
    CComboBox	m_comChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgConnectList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgConnectList)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetDevList();
    afx_msg LRESULT OnMsgGetDevListFinish(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lChannel;
    LONG m_lUserID;
    int m_iDeviceIndex;

    LONG        m_lDevListHandle;
    MSGCallBack fMessageCallBack;
    
    void StopDevlList();
    void ProcGetDevList(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void AddDevListItem(const NET_DVR_CONNECTDEV_CFG &Item);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONNECTLIST_H__BAEC8C66_E4C9_4DAC_AB87_9EE73D0387A4__INCLUDED_)
