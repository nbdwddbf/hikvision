#if !defined(AFX_DLGCOURSEINFO_H__67222F18_2A4F_40F5_9A9D_04112FE43569__INCLUDED_)
#define AFX_DLGCOURSEINFO_H__67222F18_2A4F_40F5_9A9D_04112FE43569__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCourseInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCourseInfo dialog

class DlgCourseInfo : public CDialog
{
// Construction
public:
	DlgCourseInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgCourseInfo)
	enum { IDD = IDD_DLG_COURSE_INDEX_CFG };
	CString	m_sCourseDescription;
	CString	m_sCourseName;
	CString	m_sTeacherName;
	UINT	m_index;
	//}}AFX_DATA

	LONG m_lUserID;
	int  m_iDeviceIndex;
	int m_iMirrorNum;
	int m_iStartChannel;
	NET_DVR_COURSE_RECORDING_INFO m_struCourseRecordInfo;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCourseInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgCourseInfo)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOURSEINFO_H__67222F18_2A4F_40F5_9A9D_04112FE43569__INCLUDED_)
