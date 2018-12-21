#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgFormatHD dialog

class CDlgFormatHD : public CDialog
{
	DECLARE_DYNAMIC(CDlgFormatHD)

public:
	CDlgFormatHD(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgFormatHD();

// Dialog Data
	

public:
	//{{AFX_DATA(CDlgFormatHD)
	enum { IDD = IDD_DLG_FORMAT_HD };
	CComboBox m_comboHDDriver;
	CString m_csFormatStat;
	CProgressCtrl m_progressFormat;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CDlgFormatHD)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgFormatHD)
	virtual BOOL OnInitDialog();	
	afx_msg void OnBnClickedBtnDoFormat();
	afx_msg void OnBnClickedBtnFormatExit();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int		m_iDeviceIndex;
	LONG	m_lFormat[MAX_DISKNUM_V30];		
	LONG	m_lFormatAll;
	UINT	m_nTime;
	BOOL	m_bFormat[MAX_DISKNUM_V30];	
	DWORD   m_dwDiskNum;
	LONG	m_lDiskSel;
	BOOL	m_bFormatAll;
	int m_iDiskIndex;
    DWORD m_dwHddNo;
    CString m_csIp;
    BOOL m_bAll;
    BOOL m_bIpv6;
    afx_msg void OnBnClickedButtonFroamtV50();
};
