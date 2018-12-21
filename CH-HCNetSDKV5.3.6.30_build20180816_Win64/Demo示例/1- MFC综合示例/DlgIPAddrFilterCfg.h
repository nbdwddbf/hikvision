#if !defined(AFX_DLGIPADDRFILTERCFG_H__9D38E3AA_9251_45FB_A686_848CA169D773__INCLUDED_)
#define AFX_DLGIPADDRFILTERCFG_H__9D38E3AA_9251_45FB_A686_848CA169D773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPAddrFilterCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAddrFilterCfg dialog

class CDlgIPAddrFilterCfg : public CDialog
{
// Construction
public:
	CDlgIPAddrFilterCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIPAddrFilterCfg)
	enum { IDD = IDD_DLG_IPADDR_FILTER };
	CComboBox	m_comboFilterType;
	BOOL	m_bChkIPAddrEn;
	CString	m_csIPAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPAddrFilterCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPAddrFilterCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lServerID;
	int     m_iDevIndex;
	LONG    m_lChannel;
	NET_DVR_IPADDR_FILTERCFG m_struIPAddrCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPADDRFILTERCFG_H__9D38E3AA_9251_45FB_A686_848CA169D773__INCLUDED_)
