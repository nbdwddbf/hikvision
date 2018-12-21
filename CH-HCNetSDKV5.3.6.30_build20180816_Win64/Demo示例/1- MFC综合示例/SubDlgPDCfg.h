#if !defined(AFX_SUBDLGPDCFG_H__C53E869D_56C2_4A9F_A856_374189668890__INCLUDED_)
#define AFX_SUBDLGPDCFG_H__C53E869D_56C2_4A9F_A856_374189668890__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgPDCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubDlgPDCfg dialog

class CSubDlgPDCfg : public CDialog
{
// Construction
public:
	CSubDlgPDCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubDlgPDCfg)
	enum { IDD = IDD_SUB_DLG_PD_CFG };
	CComboBox	m_comboRaidInitMode;
	CComboBox	m_comboSpareType;
	CListCtrl	m_listPDSlot;
	CComboBox	m_comboRaidMode;
	CListCtrl	m_ListPDInfo;
	CString	m_csArrayName;
	int		m_iArrayID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgPDCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnCancel();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgPDCfg)
	afx_msg void OnBtnFastConfig();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnCreateArray();
	afx_msg void OnBtnSetSpareDisk();
	afx_msg void OnBtnDelSpareDisk();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnBtnCalcArraySize();
	afx_msg void OnCancelMode();
    afx_msg LRESULT OnMsgPhyDiskInfoFinish(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    NET_DVR_PHY_DISK_LIST m_struPDList;
    NET_DVR_PHY_DISK_INFO* m_pStruPhyDiskInfo;
    NET_DVR_RAID_ADAPTER_INFO   m_struAdapterInfo;
    NET_DVR_OPERATE_ARRAY_PARAM    m_struOperateArray;
    NET_DVR_SPARE_DISK_PARAM m_struSpareDisk;
    int  m_lFastConfigHandle;
    DWORD m_dwArraySize;  // Units of G   
    DWORD m_dwPhyDiskNum;
    int m_lGetPhyDiskHanle;
public:
    void CurCfgUpdate();
    BOOL CheckInitParam();
    BOOL GetPDList();
    BOOL GetAdapterInfo();
    BOOL CreateArray();
    BOOL CalcArraySize();
    BOOL SetSpareDisk();

    LRESULT OnShowPhyDiskInfo(WPARAM wParam, LPARAM lParam);
	static DWORD WINAPI GetPhyDiskInfoThread(LPVOID lpArg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGPDCFG_H__C53E869D_56C2_4A9F_A856_374189668890__INCLUDED_)
