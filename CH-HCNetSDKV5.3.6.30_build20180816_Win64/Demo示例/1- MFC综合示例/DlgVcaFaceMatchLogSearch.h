#if !defined(AFX_DLGVCAFACEMATCHLOGSEARCH_H__5E13F2D3_77F5_4A83_B46B_F578CFBECD96__INCLUDED_)
#define AFX_DLGVCAFACEMATCHLOGSEARCH_H__5E13F2D3_77F5_4A83_B46B_F578CFBECD96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaFaceMatchLogSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceMatchLogSearch dialog

class CDlgVcaFaceMatchLogSearch : public CDialog
{
// Construction
public:
	CDlgVcaFaceMatchLogSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaFaceMatchLogSearch)
	enum { IDD = IDD_DLG_VCA_FACEMATCH_LOG_SEARCH };
	CListCtrl	m_listFindData;
	CTime	m_ctDateStart;
	CTime	m_ctDateEnd;
	CTime	m_ctTimeStart;
	CTime	m_ctTimeEnd;
	DWORD	m_dwBlackListFaceID;
	DWORD	m_dwBlackListID;
	DWORD	m_dwSnapFaceID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaFaceMatchLogSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaFaceMatchLogSearch)
	afx_msg void OnBtnFind();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnGetFacematchPic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	LONG    m_lFindHandle;
	HANDLE  m_hFindThread;
	LONG    m_lFaceMatchLogNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAFACEMATCHLOGSEARCH_H__5E13F2D3_77F5_4A83_B46B_F578CFBECD96__INCLUDED_)
