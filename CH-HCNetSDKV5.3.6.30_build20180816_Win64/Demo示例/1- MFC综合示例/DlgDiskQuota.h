#if !defined(AFX_DLGDISKQUOTA_H__D0CB725F_1626_4BC6_BAD2_4DBED93F9592__INCLUDED_)
#define AFX_DLGDISKQUOTA_H__D0CB725F_1626_4BC6_BAD2_4DBED93F9592__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiskQuota.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDiskQuota dialog

class CDlgDiskQuota : public CDialog
{
// Construction
public:
	CDlgDiskQuota(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDiskQuota)
	enum { IDD = IDD_DLG_HARD_DISK_QUOTA };
	CComboBox	m_comboAddInfoType;
	CComboBox	m_comboRecordType;
	CComboBox	m_comboPicType;
	UINT	m_iPicCapacity;
	UINT	m_iRecordCapacity;
	UINT	m_iPicUsed;
	UINT	m_iRecordUsed;
	BYTE	m_byDrawPer;
	BYTE	m_byPicPer;
	BYTE	m_byRecordPer;
	BYTE	m_byRecordQuotaRatio;
	BYTE	m_byPicQuotaRatio;
	UINT	m_iAddInfoCapacity;
	BYTE	m_byAddInfoQuotaRatio;
	UINT	m_iAddInfoUsed;
	BOOL	m_bAllChann;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDiskQuota)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDiskQuota)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnQuotaCfg();
	afx_msg void OnBtnQuotaUpgrade();
	afx_msg void OnBtnQuotaExit();
	afx_msg void OnBtnDrawFrameQuotaCfg();
	afx_msg void OnButtonDrawFrameUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
    LONG    m_lChannelNum;
    NET_DVR_DISK_QUOTA_CFG m_struDiskQuotaCfg;
	NET_DVR_DRAWFRAME_DISK_QUOTA_CFG m_struDrawFrame;
public:
    void InitWnd();

    BOOL GetDiskQuotaCfg(LONG lChannel, NET_DVR_DISK_QUOTA_CFG &struDiskQuotaCfg);
    BOOL SetDiskQuotaCfg(LONG lChannel, NET_DVR_DISK_QUOTA_CFG &struDiskQuotaCfg);

    void GetDiskQuotaCfgFromWnd(NET_DVR_DISK_QUOTA_CFG &struDiskQuotaCfg);
    void GetPicQuotaFromWnd(NET_DVR_DISK_QUOTA &struPicQuota);
    void GetRecordQuotaFromWnd(NET_DVR_DISK_QUOTA &struRecordQuota);
    void GetAddInfoQuotaFromWnd(NET_DVR_DISK_QUOTA &struAddInfoQuota);
    
    void SetDiskQuotaCfgToWnd(NET_DVR_DISK_QUOTA_CFG &struDiskQuotaCfg);
    void SetPicQuotaToWnd(NET_DVR_DISK_QUOTA &struPicQuota);
    void SetRecordQuotaToWnd(NET_DVR_DISK_QUOTA &struRecordQuota);
    void SetAddInfoQuotaFromWnd(NET_DVR_DISK_QUOTA &struAddInfoQuota);
    DWORD m_dwPicPeriod;
    DWORD m_dwReocrdPeriod;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDISKQUOTA_H__D0CB725F_1626_4BC6_BAD2_4DBED93F9592__INCLUDED_)
