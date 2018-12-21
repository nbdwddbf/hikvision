#if !defined(AFX_TIMESEGMENT_H__54CE4BF5_A591_4E31_9975_3C50854C1921__INCLUDED_)
#define AFX_TIMESEGMENT_H__54CE4BF5_A591_4E31_9975_3C50854C1921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeSegment.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeSegment dialog

class CTimeSegment : public CDialog
{
// Construction
public:
	CTimeSegment(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeSegment)
	enum { IDD = IDD_DLG_TIME_SEGMENT_SET };
	CComboBox	m_cmbVerify;
	CComboBox	m_cmbDoorStatus;
	CListCtrl	m_lstTimeSegment;
	BOOL	m_BEnable;
	COleDateTime	m_dtEndTime;
	COleDateTime	m_dtStartTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeSegment)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeSegment)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	afx_msg void OnClickLstTimesegment(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusLstTimesegment(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
    NET_DVR_SINGLE_PLAN_SEGMENT m_struTimeSegment[MAX_TIMESEGMENT_V30]; 
    int m_iCurSel;
    void UpdateList(); 
    BOOL CheckDate(const NET_DVR_SIMPLE_DAYTIME& struItem);

public:
    void SetTimeSegment(const NET_DVR_SINGLE_PLAN_SEGMENT*  lpItem); 
    void GetTimeSegment(NET_DVR_SINGLE_PLAN_SEGMENT* lpItem); 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMESEGMENT_H__54CE4BF5_A591_4E31_9975_3C50854C1921__INCLUDED_)
