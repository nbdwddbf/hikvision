#if !defined(AFX_DLGPTZSCOPE_H__71488EEC_BD18_4663_9B0A_ECC438B73D14__INCLUDED_)
#define AFX_DLGPTZSCOPE_H__71488EEC_BD18_4663_9B0A_ECC438B73D14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPtzScope.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzScope dialog

class CDlgPtzScope : public CDialog
{
// Construction
public:
	CDlgPtzScope(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPtzScope)
	enum { IDD = IDD_DLG_PTZ_SCOPE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPtzScope)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPtzScope)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG   m_lServerID;
    int    m_iDevIndex;
    LONG    m_lChannel;
    NET_DVR_PTZSCOPE m_struPtzScope;    
    
public:
    void SetPtzScoprToWnd(NET_DVR_PTZSCOPE &struPtzScope);

    BOOL GetPtzScope(NET_DVR_PTZSCOPE &struPtzScope);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPTZSCOPE_H__71488EEC_BD18_4663_9B0A_ECC438B73D14__INCLUDED_)
