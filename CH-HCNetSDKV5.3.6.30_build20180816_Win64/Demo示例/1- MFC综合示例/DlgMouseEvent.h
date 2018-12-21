#if !defined(AFX_DLGMOUSEEVENT_H__B928329C_8A69_4B8C_BBD7_C5BD2F4D5DD8__INCLUDED_)
#define AFX_DLGMOUSEEVENT_H__B928329C_8A69_4B8C_BBD7_C5BD2F4D5DD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMouseEvent.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMouseEvent dialog

class CDlgMouseEvent : public CDialog
{
// Construction
public:
	CDlgMouseEvent(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMouseEvent)
	enum { IDD = IDD_DLG_MOUSE_EVENT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMouseEvent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMouseEvent)
	afx_msg void OnBtnStartLocalRecord();
	afx_msg void OnBtnStopLocalRecord();
	afx_msg void OnBtnStartRemoteTest();
	afx_msg void OnBtnStopRemoteTest();
	afx_msg void OnBtnSendData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
      
public:
    LONG m_lUserID;
    int m_iDevIndex;
    NET_DVR_MOUSE_EVENT_PARAM m_struMousePara;

    LONG m_lStartLocalRecordHanlde;
    LONG m_lStartRemoteTestHanlde;
    BOOL  m_bStop ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOUSEEVENT_H__B928329C_8A69_4B8C_BBD7_C5BD2F4D5DD8__INCLUDED_)
