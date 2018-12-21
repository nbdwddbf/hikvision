#if !defined(AFX_DLGVCAFINDSNAPDATA_H__34D0D7A4_DDBC_48AE_8412_1F6AE4763AEC__INCLUDED_)
#define AFX_DLGVCAFINDSNAPDATA_H__34D0D7A4_DDBC_48AE_8412_1F6AE4763AEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaFindSnapData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFindSnapData dialog

class CDlgVcaFindSnapData : public CDialog
{
// Construction
public:
	CDlgVcaFindSnapData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaFindSnapData)
	enum { IDD = IDD_DLG_VCA_FIND_SNAPPICTURE };
	CListCtrl	m_listFindData;
	CComboBox	m_comboFindType;
	CTime	m_ctDateEnd;
	CTime	m_ctDateStart;
	CTime	m_ctTimeEnd;
	CTime	m_ctTimeStart;
	BYTE	m_byThreshold;
	DWORD	m_dwFacePicID;
	BOOL	m_bChkSearch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaFindSnapData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaFindSnapData)
	afx_msg void OnBtnImportPic();
	afx_msg void OnBtnAdvFind();
	afx_msg void OnBtnFind();
	afx_msg void OnBtnExit();
	afx_msg void OnChkSearch();
	afx_msg void OnSelchangeComboFindType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	LONG    m_lFindHandle;
	HANDLE  m_hFindThread;
	LONG    m_lFacePicNum;
	
	NET_VCA_NORMAL_FIND m_struNormalFind;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAFINDSNAPDATA_H__34D0D7A4_DDBC_48AE_8412_1F6AE4763AEC__INCLUDED_)
