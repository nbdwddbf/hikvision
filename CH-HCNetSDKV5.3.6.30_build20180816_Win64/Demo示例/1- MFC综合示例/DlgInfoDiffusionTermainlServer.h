#if !defined(AFX_DLGINFODIFFUSIONTERMAINLSERVER_H__C71C72B3_EB76_42FB_81B9_CB63A1C2B903__INCLUDED_)
#define AFX_DLGINFODIFFUSIONTERMAINLSERVER_H__C71C72B3_EB76_42FB_81B9_CB63A1C2B903__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionTermainlServer.h : header file

#include "InfoDiffusionParamsConvert.h"
#define MAX_LEN_XML 10*1024*1024 //xml最大长度
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTermainlServer dialog

class CDlgInfoDiffusionTermainlServer : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionTermainlServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionTermainlServer)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_TERMINL_SERVER };
	CListCtrl	m_listTerminal;
	CListCtrl	m_listGroup;
	CComboBox	m_cmbOprType;
	CComboBox	m_cmbIPType;
	BOOL	m_byRegister;
	DWORD	m_dwGroupId;
	CString	m_szIP;
	DWORD	m_dwPort;
	DWORD	m_dwTerminalId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionTermainlServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionTermainlServer)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnGroupAdd();
	afx_msg void OnBtnGroupDel();
	afx_msg void OnBtnGroupMod();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnTerAdd();
	afx_msg void OnBtnTerDel();
	afx_msg void OnBtnTerMod();
	afx_msg void OnClickListGroup(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
    LONG m_lUserID;
    int m_iDeviceIndex;
    
    NET_DVR_PUBLISH_SERVER_ADDR m_struAddr;
    char* m_pOutputXmlBuffer;
    
    int m_nCurSelGroup;
    int m_nCurSelTerminal;
    
public:
    void InitList();
    void UpdatList();
    CString m_csUserName;
    CString m_csPwd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONTERMAINLSERVER_H__C71C72B3_EB76_42FB_81B9_CB63A1C2B903__INCLUDED_)
