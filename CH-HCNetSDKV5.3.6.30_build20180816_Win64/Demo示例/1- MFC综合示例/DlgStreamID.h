#if !defined(AFX_DLGSTREAMID_H__5181F751_4C5E_4D5F_98AB_CD90AD4450F5__INCLUDED_)
#define AFX_DLGSTREAMID_H__5181F751_4C5E_4D5F_98AB_CD90AD4450F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStreamID.h : header file
//

#include "DlgStreamSrcCfg.h"
#include "DlgStreamRecordInfo.h"
#include "DlgStreamRecordStatus.h"
#include "DlgStreamManualRecordAndLock.h"
#include "DlgStreamRecCheck.h"
#include "DlgStreamMediaCfg.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamID dialog

class CDlgStreamID : public CDialog
{
// Construction
public:
	CDlgStreamID(CWnd* pParent = NULL);   // standard constructor

	void WindowUpdate();

// Dialog Data
	//{{AFX_DATA(CDlgStreamID)
	enum { IDD = IDD_DLG_STREAM_ID };
	CTabCtrl	m_tabStreamID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStreamID)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	CDlgStreamSrcCfg				m_dlgStreamSrc;
	CDlgStreamRecordStatus			m_dlgStreamRecordStatus;
	CDlgStreamRecordInfo			m_dlgStreamRecordInfo;
	CDlgStreamManualRecordAndLock	m_dlgStreamManualRecordAndLock;
	CDlgStreamRecCheck				m_dlgStreamRecordCheck;
    CDlgStreamMediaCfg			    m_dlgStreamMediaCfg;

private:
	int m_iTabIndex;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStreamID)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabStreamId(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTREAMID_H__5181F751_4C5E_4D5F_98AB_CD90AD4450F5__INCLUDED_)
