#if !defined(AFX_DLGSNEAKANDLOCK_H__B57369E3_7267_4EA1_B0F7_900325FF59C6__INCLUDED_)
#define AFX_DLGSNEAKANDLOCK_H__B57369E3_7267_4EA1_B0F7_900325FF59C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSneakAndLock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSneakAndLock dialog

class CDlgSneakAndLock : public CDialog
{
// Construction
public:
	CDlgSneakAndLock(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSneakAndLock)
	enum { IDD = IDD_DLG_SNEAK_AND_LOCK };
	CListCtrl	m_lstDoorInterLock;
	CListCtrl	m_lstFollowCardRead;
	CComboBox	m_comCardReaderSeqIndex;
	CComboBox	m_comCardReaderIndex;
	CComboBox	m_comLockGroupIndex;
	CComboBox	m_comLockDoorIndex;
	BOOL	m_bLockEnable;
	BOOL	m_bSneakEnable;
	DWORD	m_dwMultiDoorGroup;
	DWORD	m_dwCardReaderSequence;
	DWORD	m_dwStartCardReaderNo;
	BOOL	m_bCardReader;
	DWORD	m_dwReaderCardNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSneakAndLock)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSneakAndLock)
	afx_msg void OnBtnSaveLock();
	afx_msg void OnBtnSetLock();
	afx_msg void OnBtnGetLock();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboLockGroupIndex();
	afx_msg void OnSelchangeComboLockDoorIndex();
	afx_msg void OnBtnSaveSneak();
	afx_msg void OnBtnSetSneak();
	afx_msg void OnBtnGetSneak();
	afx_msg void OnSelchangeComboCardReaderIndex();
	afx_msg void OnSelchangeComboCardReaderSeqIndex();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnGetSneakReadcard();
	afx_msg void OnBtnSetSneakReadcard();
	afx_msg void OnClickLstFollowupCardReader(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditSeqReaderNo();
	afx_msg void OnClickLstDoorInterlock(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusLockDoorNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lUserID;
	LONG m_lChannel;
	int m_iDevIndex;

	NET_DVR_ANTI_SNEAK_CFG m_struSneakCfg;
	NET_DVR_MULTI_DOOR_INTERLOCK_CFG m_struMultiDoorLockCfg;
    NET_DVR_CARD_READER_ANTI_SNEAK_CFG m_struCardReadAntiSneak[MAX_CARD_READER_NUM];
    NET_DVR_CARD_READER_ANTI_SNEAK_CFG m_struCardAntiSneak; 
    BYTE m_bySet[MAX_CARD_READER_NUM];

private:
    DWORD m_dwLastCardIndex; 
    DWORD m_dwLastDoorIndex; 

protected:
    void UpdateFollowUpList(); 
    void UpdateDoorInterlockList(); 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSNEAKANDLOCK_H__B57369E3_7267_4EA1_B0F7_900325FF59C6__INCLUDED_)
