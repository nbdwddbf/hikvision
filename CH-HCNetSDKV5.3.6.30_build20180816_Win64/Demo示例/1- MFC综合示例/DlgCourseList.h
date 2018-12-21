#if !defined(AFX_DLGCOURSELIST_H__E64A3B7C_7F59_48DC_9F46_015A923E1F18__INCLUDED_)
#define AFX_DLGCOURSELIST_H__E64A3B7C_7F59_48DC_9F46_015A923E1F18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCourseList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCourseList dialog

class DlgCourseList : public CDialog
{
// Construction
public:
	DlgCourseList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgCourseList)
	enum { IDD = IDD_DLG_COURSE_LIST };
	CListCtrl	m_listCourse;
	CComboBox	m_byCourseType;
	CString	m_byCourseName;
	CString	m_byInstructorName;
	COleDateTime	m_startTime;
	COleDateTime	m_endTime;
	COleDateTime	m_endDate;
	CTime	m_startDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCourseList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgCourseList)
    virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetCourseList();
    afx_msg LRESULT OnMsgGetCourseListFinish(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lChannel;
    LONG m_lUserID;
    int m_iDeviceIndex;
    
    LONG        m_lCourseListHandle;
    MSGCallBack fMessageCallBack;
    
    void StopCourselList();
    void ProcGetCourseList(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void AddCourseListItem(const NET_DVR_COURSE_CFG &Item);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOURSELIST_H__E64A3B7C_7F59_48DC_9F46_015A923E1F18__INCLUDED_)
