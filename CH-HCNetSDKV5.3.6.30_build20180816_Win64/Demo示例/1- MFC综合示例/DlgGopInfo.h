#if !defined(AFX_DLGGOPINFO_H__7A6AC0C1_877F_41BF_9C17_54E96BCA1A9D__INCLUDED_)
#define AFX_DLGGOPINFO_H__7A6AC0C1_877F_41BF_9C17_54E96BCA1A9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGopInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGopInfo dialog

class CDlgGopInfo : public CDialog
{
// Construction
public:
	CDlgGopInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGopInfo)
	enum { IDD = IDD_DLG_GOP_INFO };
	CListCtrl	m_listRetInfo;
	CComboBox	m_cmbChan;
	CTime	m_DataStart;
	CTime	m_DataStop;
	CTime	m_timeStart;
	CTime	m_timeStop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGopInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGopInfo)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int m_iDevIndex;
    LONG m_lUserID;
    NET_DVR_GOP_INFO m_struGopInfo;
    NET_DVR_GOP_INFO_RET m_struGopInfoRet;
    LONG m_lRemoteHandle;

    LRESULT OnShowGOPInfo(WPARAM wParam, LPARAM lParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGOPINFO_H__7A6AC0C1_877F_41BF_9C17_54E96BCA1A9D__INCLUDED_)
