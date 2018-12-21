#if !defined(AFX_PTZBUTTON1_H__0CCED6D3_E62A_4EA1_86E9_600A4BC1CC75__INCLUDED_)
#define AFX_PTZBUTTON1_H__0CCED6D3_E62A_4EA1_86E9_600A4BC1CC75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PTZButton1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPTZButton1 window

class CPTZButton1 : public CButton
{
// Construction
public:
	CPTZButton1();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPTZButton1)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPTZButton1();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPTZButton1)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
public:
	long	m_lPlayHandle;
	int		m_iChannel;
	int		m_iPTZType;
	int		m_iDevIndex;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTZBUTTON1_H__0CCED6D3_E62A_4EA1_86E9_600A4BC1CC75__INCLUDED_)
