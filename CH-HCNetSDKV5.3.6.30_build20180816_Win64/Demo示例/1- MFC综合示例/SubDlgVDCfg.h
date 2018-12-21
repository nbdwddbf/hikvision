#if !defined(AFX_SUBDLGVDCFG_H__1508EA29_F43F_46D9_A8AE_BFAC9A582198__INCLUDED_)
#define AFX_SUBDLGVDCFG_H__1508EA29_F43F_46D9_A8AE_BFAC9A582198__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgVDCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubDlgVDCfg dialog

class CSubDlgVDCfg : public CDialog
{
// Construction
public:
	CSubDlgVDCfg(CWnd* pParent = NULL);   // standard constructor

	inline BOOL ValidIPv6(BYTE *ip);

// Dialog Data
	//{{AFX_DATA(CSubDlgVDCfg)
	enum { IDD = IDD_SUB_DLG_VD_CFG };
	CListCtrl	m_ListVDInfo;
	UINT	m_dwDstLunID;
	UINT	m_dwSrcLunID;
	CString	m_strLunNewName;
	CString	m_strArrayIDGroup;
	UINT	m_dwCapacity;
	CString	m_strNewWarrantIP;
	CString	m_strNewDVRName;
	CString	m_strOldDVRName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgVDCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgVDCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnRepair();
	afx_msg void OnButtonCloneLun();
	afx_msg void OnClickListVdInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonExpand();
	afx_msg void OnButtonModify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    BOOL CheckInitParam();
    void CurCfgUpdate();
    BOOL GetVDList();
    BOOL DelVD(DWORD dwID);
    BOOL RepairVD(DWORD dwID);
    void ProcessBgaInfo(char *str, const NET_DVR_BGA_INFO &struBgaInfo);

public:
    int                 m_iDevIndex;
    LONG                m_lServerID;
    NET_DVR_VD_LIST     m_struVDList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGVDCFG_H__1508EA29_F43F_46D9_A8AE_BFAC9A582198__INCLUDED_)
