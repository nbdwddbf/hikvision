#pragma once


// CDlgRemoteEmailAddReceiver dialog

class CDlgRemoteEmailAddReceiver : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteEmailAddReceiver)

public:
	CDlgRemoteEmailAddReceiver(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteEmailAddReceiver();

// Dialog Data



public:



	//{{AFX_DATA(CDlgRemoteEmailAddReceiver)
	enum { IDD = IDD_DLG_REMOTE_EMAIL_ADD_RECEIVER };
	CString m_csReceiverName;
	CString m_csReceiverAddr;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteEmailAddReceiver)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteEmailAddReceiver)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnEmailReceiverOk();
	afx_msg void OnBnClickedBtnEmailReceiverExit();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	
};
