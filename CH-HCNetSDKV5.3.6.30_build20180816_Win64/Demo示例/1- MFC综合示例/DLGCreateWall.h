#if !defined(AFX_DLGCREATEWALL_H__07DFA1DB_4292_41B9_8AD6_CCCFF9B6C27F__INCLUDED_)
#define AFX_DLGCREATEWALL_H__07DFA1DB_4292_41B9_8AD6_CCCFF9B6C27F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGCreateWall.h : header file
//
#include "./xml/XmlBase.h"
/////////////////////////////////////////////////////////////////////////////
// CDLGCreateWall dialog

class CDLGCreateWall : public CDialog
{
// Construction
public:
	CDLGCreateWall(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGCreateWall)
	enum { IDD = IDD_DLG_VIDEOWALL_CREATEWALL };
	BOOL	m_BEnable;
	CString	m_csName;
	BYTE	m_byWallNo;
	DWORD	m_dwWidth;
	DWORD	m_dwX;
	DWORD	m_dwY;
	DWORD	m_dwHeight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGCreateWall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGCreateWall)
	afx_msg void OnBtnWallRefresh();
	afx_msg void OnBtnWallSet();
	afx_msg void OnBtnOutputSet();
	afx_msg void OnBtnWinSet();
	afx_msg void OnBtnVirLEDSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
	LONG m_iDeviceIndex;

 
    
protected:
    void GetXMLAbility(); 

private:
    char * m_pXMLBuf;
    // Ù–‘
    BYTE m_byMaxWallNo; 
    BYTE m_byMinWallNo; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATEWALL_H__07DFA1DB_4292_41B9_8AD6_CCCFF9B6C27F__INCLUDED_)
