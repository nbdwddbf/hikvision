#if !defined(AFX_DLGMERGEDEVRESOURCE_H__129DF060_F45F_48B2_BDB7_CA026F2899D5__INCLUDED_)
#define AFX_DLGMERGEDEVRESOURCE_H__129DF060_F45F_48B2_BDB7_CA026F2899D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMergeDevResource.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDevResource dialog

class CDlgMergeDevResource : public CDialog
{
// Construction
public:
	CDlgMergeDevResource(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMergeDevResource)
	enum { IDD = IDD_DLG_MERGE_DEV_RESOURCE };
	CComboBox	m_comboOutputNo;
	CComboBox	m_comboCodeChan;
	BOOL	m_bAudio;
	DWORD	m_dwSubWinNo;
	DWORD	m_dwWinNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMergeDevResource)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMergeDevResource)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnExit();
	afx_msg void OnSelchangeComboCodeChan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    char m_szLan[64];

    NET_DVR_CHAN_RELATION_RESOURCE m_struChanResource[8];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMERGEDEVRESOURCE_H__129DF060_F45F_48B2_BDB7_CA026F2899D5__INCLUDED_)
