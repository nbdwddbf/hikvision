#if !defined(AFX_DLGPLAYLOCKFILE_H__ABD3E354_9CA8_410C_BC47_9039EE356A18__INCLUDED_)
#define AFX_DLGPLAYLOCKFILE_H__ABD3E354_9CA8_410C_BC47_9039EE356A18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPlayLockFile.h : header file
//
#include "afxcmn.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayLockFile dialog

class CDlgPlayLockFile : public CDialog
{
// Construction
public:
	CDlgPlayLockFile(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgPlayLockFile();
// Dialog Data
	//{{AFX_DATA(CDlgPlayLockFile)
	enum { IDD = IDD_DLG_PLAY_LOCK_FILE };
	CListCtrl	m_listChannelRecordStatus;
	CComboBox	m_comboGroupNO;
	CComboBox	m_comboRecordType;
	DWORD	m_dwDuration;
	CTime	m_ctLockBeginDate;
	CTime	m_ctLockBeginTime;
	CTime	m_ctLockEndDate;
	CTime	m_ctLockEndTime;
	int     m_iDeviceIndex;
	long    m_lLoginID;
	int     m_iChanCount;
	long    m_lStartChan;
	int     m_iChanIndex;
	DWORD	m_dwDiskNO;
	CTime	m_ctLockBeginDate2;
	CTime	m_ctLockBeginTime2;
	CTime	m_ctLockEndDate2;
	CTime	m_ctLockEndTime2;
	CTime	m_ctUnlockTimePointDate;
	CTime	m_ctUnlockTimePointTime;
	BOOL	m_bOfflineRecord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlayLockFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPlayLockFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnFileLock();
	afx_msg void OnBtnFileUnlock();
	afx_msg void OnBtnUpdateRecordInfo();
	afx_msg void OnSelchangeComboGroupno();
	afx_msg void OnClickListIpChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnModifyInfo();
	afx_msg void OnBtnSetRecordDisk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SetParentWnd(HWND *hhWnd, int iParentNum);	
	BOOL CheckDate(CTime tFrom, CTime tTo);
	BOOL CheckInitParam();

	HWND m_hPareTabWnd;
	HWND m_hPareDlgWnd;
	
	NET_DVR_TIME_LOCK m_struLockPara;
	NET_DVR_LOCK_RETURN m_struLockReturn;
	NET_DVR_CHAN_GROUP_RECORD_STATUS m_struGroupRecordStatus;

	int m_iCurSelectedRow;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAYLOCKFILE_H__ABD3E354_9CA8_410C_BC47_9039EE356A18__INCLUDED_)
