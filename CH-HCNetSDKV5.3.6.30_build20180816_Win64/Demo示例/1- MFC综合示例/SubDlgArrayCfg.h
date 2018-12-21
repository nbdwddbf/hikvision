#if !defined(AFX_SUBDLGARRAYCFG_H__448F463C_A14C_431F_B0F1_62E5FFD59756__INCLUDED_)
#define AFX_SUBDLGARRAYCFG_H__448F463C_A14C_431F_B0F1_62E5FFD59756__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgArrayCfg.h : header file
//
#include "SubDlgPDCfg.h"
#include "SubDlgAdapterCfg.h"
/////////////////////////////////////////////////////////////////////////////
// CSubDlgArrayCfg dialog

class CSubDlgArrayCfg : public CDialog
{
// Construction
public:
	CSubDlgArrayCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubDlgArrayCfg)
	enum { IDD = IDD_SUB_DLG_ARRAY_CFG };
	CListCtrl	m_listPDSlot;
	CComboBox	m_comboRaidMode;
	CListCtrl	m_ListArrrayInfo;
	CString	m_csArrayName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgArrayCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgArrayCfg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnDelArray();
	afx_msg void OnBtnCreateVd();
	afx_msg void OnBtnRebuildArray();
	afx_msg void OnBtnMigrateArray();
	afx_msg void OnItemchangedListArrayInfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    BOOL CheckInitParam();
    void CurCfgUpdate();
    BOOL GetArrayList();
    BOOL DelArray(DWORD dwArrayID);
    BOOL GetPDList();
    BOOL GetAdapterInfo();
    BOOL GetOperateArrayData();
    BOOL MigrateArray();
    BOOL RebuildArray();
    void ProcessBgaInfo(char *str, const NET_DVR_BGA_INFO &struBgaInfo);
public:
    int m_iSelectIndex;
    int m_iDevIndex;
    LONG m_lServerID;
    NET_DVR_ARRAY_LIST m_struArrayList;
	NET_DVR_PHY_DISK_INFO *m_pPhyDiskInfo;
    NET_DVR_PHY_DISK_LIST m_struPDList;
    NET_DVR_RAID_ADAPTER_INFO   m_struAdapterInfo;
    NET_DVR_OPERATE_ARRAY_PARAM m_struOperateArray;
    CSubDlgPDCfg m_struDlgPDCfg;

	DWORD m_dwPhyDiskInfoNum;
	int m_lGetPhyDiskHanle;
protected:
	LRESULT OnShowPhyDiskInfo(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGARRAYCFG_H__448F463C_A14C_431F_B0F1_62E5FFD59756__INCLUDED_)
