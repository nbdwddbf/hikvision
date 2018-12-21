#pragma once
#include "afxwin.h"


// CDlgHardDiskCfg dialog

typedef enum tagBACKUP_MODE
{
	BACKUP_BYFILE = 1,
	BACKUP_BYTIME,
	BACKUP_PICTURE,
	RESUME_INQUEST,
	BACKUP_LOG
}BACKUP_MODE;

class CDlgHardDiskCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgHardDiskCfg)

public:
	CDlgHardDiskCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgHardDiskCfg();

// Dialog Data
public:	
	//{{AFX_DATA(CDlgHardDiskCfg)
	enum { IDD = IDD_DLG_HARD_DISK_CFG };
        CComboBox	m_cmbDiskList;
	CComboBox	m_cmbHDCFGGroup;
	CListCtrl	m_listDisk;
	CListCtrl	m_listChan;
	CComboBox	m_comboGroup;
	CComboBox	m_comboBelongGroup;
	CComboBox	m_comboDisk;
	CComboBox m_comboEsataFunc;
	BOOL m_bChkCyclicRecord;
	int m_iSpaceThreshold;
	BOOL	m_bChkAllChan;
	BOOL	m_bContinueBackup;
	BOOL	m_bDelAllInvalidDisk;
	BOOL	m_bHDSleep;
	BOOL	m_byAllLogBackup;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDlgHardDiskCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgHardDiskCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOneHdOk();
	afx_msg void OnBtnHdRefresh();
	afx_msg void OnRadioNone();
	afx_msg void OnRadioReadOnly();
	afx_msg void OnRadioRedund();
    afx_msg void OnRadioNotRW();
	afx_msg void OnClickListDisk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboGroup();
	afx_msg void OnSelchangeComboDisk();
	afx_msg void OnBtnSetGroup();
	afx_msg void OnChkAllChan();
	afx_msg void OnBtnHdSet();
	afx_msg void OnBtnExpand();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnBtnBackupLog();
	afx_msg void OnSelchangeComboDiskList();
	afx_msg void OnBtnDelHd();
	afx_msg void OnBtnUnmount();
	afx_msg void OnBtnMount();
	afx_msg void OnRadioBackup();
	afx_msg void OnButtonSet();
	afx_msg void OnBtnNFS();
	afx_msg void OnBtnEsataMinisasUsage();
	afx_msg void OnBtnRaid();
	afx_msg void OnBtnISCSI();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	LONG m_lLoginID;
	int m_iSelHDNum;
	int m_iSelGroup;
	DWORD m_dwDiskCount;
	DWORD m_dwChanCount;
	void CreateTree();
	DWORD m_dwDevIndex;
	BOOL m_bRecordChan[MAX_CHANNUM_V30];
	void CheckInitParam();
	void UpdataChanStatus();
	void ChangeReChanData(DWORD* pChanData, DWORD dwMaxChanNum, DWORD dwChangedData, DWORD dwChangeType);
    BOOL FindDataFromChanArray(DWORD* pChanData, DWORD dwMaxChanNum, DWORD dwFindData);
	int m_iGroupNum;
	void SetRadioChk(int iAttr);
	 void SaveLastStatusToHDCfgV40(DWORD dwCurHDGroupNo);
    NET_DVR_HDCFG_V50 m_struHDCfg;
	NET_DVR_HD_STATUS m_struHDStatus;
	int		m_iHDAttr;
	//NET_DVR_HDGROUP_CFG m_struHDGroupCfg;
	NET_DVR_HDGROUP_CFG_V40  m_struHDGroupCfg;
	int m_iSelHDIndex;
    LONG m_lExapandHandle;
	LONG    m_timerHandle;
	LONG m_lRemoteUnmountHandle;
	BOOL	m_bBackuping;
	 BOOL    *m_pbHDGroupCfgV40;
	HANDLE	m_hBackupThread;
	LONG    m_lBackupHandle;
	DWORD   m_dwCurChanNum;
	NET_DVR_DISKABILITY_LIST	m_struDiskList;
	NET_DVR_BACKUP_LOG_PARAM	m_struBackupLogParam;
    afx_msg void OnBnClickedBtnHardDiskVolumeInfo();
    afx_msg void OnBnClickedBtnemmc();
};
