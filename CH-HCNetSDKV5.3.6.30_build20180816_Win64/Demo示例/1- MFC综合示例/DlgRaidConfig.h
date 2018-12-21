#if !defined(AFX_DLGRAIDCONFIG_H__7AF031AF_4194_480E_A464_3BD82CAC5768__INCLUDED_)
#define AFX_DLGRAIDCONFIG_H__7AF031AF_4194_480E_A464_3BD82CAC5768__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRaidConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRaidConfig dialog
#include "SubDlgAdapterCfg.h"
#include "SubDlgArrayCfg.h"
#include "SubDlgPDCfg.h"
#include "SubDlgVDCfg.h"
#include "SubDlgBTS.h"


class CDlgRaidConfig : public CDialog
{
// Construction
public:
	CDlgRaidConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRaidConfig)
	enum { IDD = IDD_DLG_RAID_CONFIG };
	CTabCtrl	m_tabRaidCfg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRaidConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRaidConfig)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabRaidCfg(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public: // fun
    BOOL GetAdapterInfo();
    BOOL SetAdapterInfo();
    BOOL GetPDList();
    BOOL GetArrayList();
    BOOL GetVDList();
    BOOL SetSpareDisk();
    BOOL GetArraySpaceAlloc(DWORD dwArrayID);
    BOOL DelArray(DWORD dwArrayID);
    BOOL CreateArray();
    BOOL MigrateArray();
    BOOL RebuildArray();
    BOOL CreateVD();
    BOOL DelVD(DWORD dwID);
    BOOL RepairVD(DWORD dwID);

    void RaidConfigUpdate(int iConfigType);
    void ChangeCurConfigWnd(int iConfigType);
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
	LONG    m_lChannel;

    int     m_iRaidConfigType;
    CSubDlgPDCfg        m_subDlgPDCfg;
    CSubDlgArrayCfg     m_subDlgArrayCfg;
    CSubDlgVDCfg        m_subDlgVDCfg;
    CSubDlgAdapterCfg   m_subDlgAdapterCfg;
	CSubDlgBTS			m_subDlgBTSCfg;


#if 1
    NET_DVR_RAID_ADAPTER_INFO m_struAdapterInfo;
    NET_DVR_PHY_DISK_LIST  m_struPDList;
    NET_DVR_ARRAY_LIST m_struArrayList;
    NET_DVR_VD_LIST     m_struVDList;
    NET_DVR_SPARE_DISK_PARAM m_struSpareDisk;
    NET_DVR_ARRAY_SPACE_ALLOC_INFO m_struArraySpaceAlloc;
    NET_DVR_OPERATE_ARRAY_PARAM m_struOperateArray;
    NET_DVR_SPARE_DISK_PARAM m_struSpareDiskParam;
    NET_DVR_OPERATE_VD_PARAM m_struOpeateVD;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRAIDCONFIG_H__7AF031AF_4194_480E_A464_3BD82CAC5768__INCLUDED_)
