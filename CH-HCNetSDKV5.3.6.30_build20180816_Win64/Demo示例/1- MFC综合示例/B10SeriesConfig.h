#if !defined(AFX_B10SERIESCONFIG_H__76A50EA7_94BD_4196_9DA7_0C91EC82D38A__INCLUDED_)
#define AFX_B10SERIESCONFIG_H__76A50EA7_94BD_4196_9DA7_0C91EC82D38A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// B10SeriesConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CB10SeriesConfig dialog

class CB10SeriesConfig : public CDialog
{
// Construction
public:
	CB10SeriesConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CB10SeriesConfig)
	enum { IDD = IDD_DLG_BX_CONFIG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CB10SeriesConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CB10SeriesConfig)
	afx_msg void OnButDisplaychanConfig();
	afx_msg void OnButB10xRingcfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_B10SERIESCONFIG_H__76A50EA7_94BD_4196_9DA7_0C91EC82D38A__INCLUDED_)
