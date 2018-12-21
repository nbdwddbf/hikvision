#if !defined(AFX_PTZBUTTON_H__B3E99438_BBCE_4862_845F_D3AB668824A6__INCLUDED_)
#define AFX_PTZBUTTON_H__B3E99438_BBCE_4862_845F_D3AB668824A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PTZButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPTZButton window

class CPTZButton : public CButton
{
// Construction
public:
	CPTZButton();
public:
	int m_iSubBtnIndex;
	LONG m_lPlayHandle;//²¥·Å¾ä±ú

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPTZButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	void PTZControlAll(LONG lRealHandle,DWORD dwPTZCommand,DWORD dwStop ,int Speed);
	virtual ~CPTZButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPTZButton)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTZBUTTON_H__B3E99438_BBCE_4862_845F_D3AB668824A6__INCLUDED_)
