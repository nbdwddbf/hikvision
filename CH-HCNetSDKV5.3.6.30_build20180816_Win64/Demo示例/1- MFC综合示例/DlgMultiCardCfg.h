#if !defined(AFX_DLGMULTICARDCFG_H__666FF054_9F66_45E4_B270_B4BAD279B595__INCLUDED_)
#define AFX_DLGMULTICARDCFG_H__666FF054_9F66_45E4_B270_B4BAD279B595__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMultiCardCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMultiCardCfg dialog

class CDlgMultiCardCfg : public CDialog
{
// Construction
public:
	CDlgMultiCardCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMultiCardCfg)
	enum { IDD = IDD_DLG_MULTI_CARD };
	CComboBox	m_comMultiCardIndex;
	CComboBox	m_comGroupIndex;
	BOOL	m_bCombinationEnable;
	BOOL	m_bEnable;
	BOOL	m_bMultiCardEnable;
	BOOL	m_bOffLineVerify;
	DWORD	m_dwGroupNo;
	BYTE	m_byMemberNum;
	BYTE	m_bySequenceNo;
	BYTE	m_bySwipeIntervalTimeout;
	DWORD	m_dwTemplateNo;
	DWORD	m_dwDoorNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMultiCardCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMultiCardCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetMultiCard();
	afx_msg void OnBtnSetMultiCard();
	afx_msg void OnSelchangeComboCombinationIndex();
	afx_msg void OnSelchangeComboGroupIndex();
	afx_msg void OnBtnSaveMultiCard();
	afx_msg void OnSelchangeComboMultiCardIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lUserID;
	LONG m_lChannel;
	int m_iDevIndex;

	NET_DVR_MULTI_CARD_CFG_V50 m_struMultiCardCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMULTICARDCFG_H__666FF054_9F66_45E4_B270_B4BAD279B595__INCLUDED_)
