#if !defined(AFX_DLGALARMHOSTTRANSPARENT_H__06A54AAD_77A1_4581_9555_41D26404C0A0__INCLUDED_)
#define AFX_DLGALARMHOSTTRANSPARENT_H__06A54AAD_77A1_4581_9555_41D26404C0A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostTransparent.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostTransparent dialog

class CDlgAlarmHostTransparent : public CDialog
{
// Construction
public:
	CDlgAlarmHostTransparent(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostTransparent)
	enum { IDD = IDD_DLG_ALARMHOST_TRANSPARENT };
	CListCtrl	m_listRecvData;
	CComboBox	m_comboChan;
	CComboBox	m_comboSerialType;
	CString	m_csData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostTransparent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostTransparent)
	afx_msg void OnCreatechannel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroychannel();
	afx_msg void OnSelchangeComboSerialType();
	afx_msg void OnBtnSendData();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    NET_DVR_ALARMHOST_ABILITY m_struDevAbility;
    int     m_iDevIndex;
    LONG    m_lSerialHandle;
    
public:
    void InitWnd();
    void InitSerialTypeCombo();
    void InitChannelCombo(int nChanNum);
    void InitRecvDataList();
    // NET_DVR_AlarmHostSerialStop(m_lSerialHandle)
    BOOL AlarmHostSerialSend();
    

//         NET_DVR_API HPR_BOOL CALLBACK SDKPREFIX(AlarmHostSerialSend)(HPR_INT32 lSerialHandle,HPR_INT32 lPort,char *pSendBuf,HPR_UINT32 dwBufSize);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTTRANSPARENT_H__06A54AAD_77A1_4581_9555_41D26404C0A0__INCLUDED_)
