#if !defined(AFX_DLGXMLALARMABILITY_H__AC6A3FF9_4609_44F6_B4ED_CB236410A23F__INCLUDED_)
#define AFX_DLGXMLALARMABILITY_H__AC6A3FF9_4609_44F6_B4ED_CB236410A23F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlAlarmAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlAlarmAbility dialog

class CDlgXmlAlarmAbility : public CDialog
{
// Construction
public:
	CDlgXmlAlarmAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXmlAlarmAbility)
	enum { IDD = IDD_DLG_XML_ALARM_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlAlarmAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlAlarmAbility)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;
	
	BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
	BOOL GetAlarmAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLALARMABILITY_H__AC6A3FF9_4609_44F6_B4ED_CB236410A23F__INCLUDED_)
