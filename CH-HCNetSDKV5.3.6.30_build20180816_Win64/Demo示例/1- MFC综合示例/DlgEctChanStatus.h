#if !defined(AFX_DLGECTCHANSTATUS_H__E067255E_EB08_437B_B055_3995F3B3EEDA__INCLUDED_)
#define AFX_DLGECTCHANSTATUS_H__E067255E_EB08_437B_B055_3995F3B3EEDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEctChanStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEctChanStatus dialog

class CDlgEctChanStatus : public CDialog
{
// Construction
public:
	CDlgEctChanStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEctChanStatus)
	enum { IDD = IDD_DLG_ECT_CHANNEL_STATUS };
	CListCtrl	m_listEctChanStatus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEctChanStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEctChanStatus)
	afx_msg void OnBtnGetStatus();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lLoginID;
	INT  m_iDeviceIndex;
	LONG m_lChannel;
	long m_lFindHandle;
	BOOL m_bGetNext;
	HANDLE	m_hGetInfoThread;
	LONG m_iEctStatusCount;
	static DWORD WINAPI GetEctChanStatusThread(LPVOID lpArg);
	LPNET_ITS_ECT_CHANNELSTATE  lpITSEctChannelStatus;
	void AddEctChanStatusInfoToDlg(LPNET_ITS_ECT_CHANNELSTATE lpInter);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGECTCHANSTATUS_H__E067255E_EB08_437B_B055_3995F3B3EEDA__INCLUDED_)
