#if !defined(AFX_DLGITSIMAGEMERGECFG_H__993B15E0_B694_42FB_A31D_53581453E6CB__INCLUDED_)
#define AFX_DLGITSIMAGEMERGECFG_H__993B15E0_B694_42FB_A31D_53581453E6CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSImageMergeCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSImageMergeCfg dialog

class CDlgITSImageMergeCfg : public CDialog
{
// Construction
public:
	CDlgITSImageMergeCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgITSImageMergeCfg)
	enum { IDD = IDD_DLG_ITS_IMG_MERGE };
	CComboBox	m_comboThreeMergeType;
	CComboBox	m_comboSingleMergeType;
	CComboBox	m_comboDoubleMergeType;
	BOOL	m_bChkMergeEn;
	DWORD	m_dwCloseupIndex;
	DWORD	m_dwJpegQuality;
	DWORD	m_dwMaxMergeSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSImageMergeCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSImageMergeCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lChannel; 
    int  m_iDevIndex;
    LONG m_lServerID;
	NET_ITS_IMGMERGE_CFG m_struImgMerge;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSIMAGEMERGECFG_H__993B15E0_B694_42FB_A31D_53581453E6CB__INCLUDED_)
