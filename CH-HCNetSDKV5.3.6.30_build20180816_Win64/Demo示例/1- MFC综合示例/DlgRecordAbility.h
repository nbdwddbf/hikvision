#if !defined(AFX_DLGRECORDABILITY_H__A42D79CA_F5C8_43CD_B16A_826D9216DE0C__INCLUDED_)
#define AFX_DLGRECORDABILITY_H__A42D79CA_F5C8_43CD_B16A_826D9216DE0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordAbility dialog

class CDlgRecordAbility : public CDialog
{
// Construction
public:
	CDlgRecordAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordAbility)
	enum { IDD = IDD_DLG_RECORD_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecordAbility)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetAbility();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	char*   m_pRecvBuf;
    LONG    m_lServerID;
    int     m_iDevIndex;
	
	BOOL WirteBufToFile(char *pBuf, DWORD dwBufSize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDABILITY_H__A42D79CA_F5C8_43CD_B16A_826D9216DE0C__INCLUDED_)
