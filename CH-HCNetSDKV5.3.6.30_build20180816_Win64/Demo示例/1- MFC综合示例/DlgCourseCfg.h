#if !defined(AFX_DLGCOURSECFG_H__D8E985D4_1A38_46EC_B3A7_BDFD1B9130EF__INCLUDED_)
#define AFX_DLGCOURSECFG_H__D8E985D4_1A38_46EC_B3A7_BDFD1B9130EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCourseCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCourseCfg dialog

class DlgCourseCfg : public CDialog
{
// Construction
public:
	DlgCourseCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgCourseCfg)
	enum { IDD = IDD_DLG_CURRICULUM_CFG };
	CComboBox	m_comLessionIndex;
	CComboBox	m_comDayIndex;
	CTime	m_ctData;
	UINT	m_nDayNum;
	UINT	m_nEndHour;
	UINT	m_nEndMin;
	UINT	m_nLessionIndex;
	UINT	m_nStartHour;
	UINT	m_nStartMin;
	UINT	m_nCourseIndex;
	//}}AFX_DATA

	UINT m_nOldDay;
	LONG m_lUserID;
	int  m_iDeviceIndex;
	int m_iMirrorNum;
	int m_iStartChannel;
	NET_DVR_CURRICULUM_CFG m_struCurriculum[64];
	NET_DVR_DATE m_struDate[64];
	int m_index;
	int m_nOldIndex;
	int m_nDayCount;
	int m_bDataOK;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCourseCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgCourseCfg)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnDayNumOk();
	afx_msg void OnBtnOk();
	afx_msg void OnBtnGet();
	afx_msg void OnSelchangeComDayIndex();
	afx_msg void OnSelchangeComLessionIndex();
	afx_msg void OnBtnDataOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOURSECFG_H__D8E985D4_1A38_46EC_B3A7_BDFD1B9130EF__INCLUDED_)
