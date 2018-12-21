#if !defined(AFX_PLAYLOCALFILE_H__D37ADA99_1F39_4487_8A4F_9FC259831BD6__INCLUDED_)
#define AFX_PLAYLOCALFILE_H__D37ADA99_1F39_4487_8A4F_9FC259831BD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayLocalFile.h : header file
//
#include "GeneralDef.h"
#include <vector>

using std::vector;
/////////////////////////////////////////////////////////////////////////////
// CPlayLocalFile dialog

class CPlayLocalFile : public CPropertyPage
{
	DECLARE_DYNCREATE(CPlayLocalFile)

// Construction
public:
	CPlayLocalFile();
	~CPlayLocalFile();

public:
      BOOL m_bIsPlaying;
	  BOOL m_bIsPause;
	  BOOL m_bChangeSpeed;
	  BOOL m_bStep;
	  LONG m_lPlayPort;

	  DWORD m_TotalTime;
	  DWORD m_TotalFrames;
public:
	void StopPlayBack();
	void PlayLoalFile();
	int SearchRecordFile(int iDevIndex, int iChanIndex, const CTime &StartTime, const CTime &StopTime);
	BOOL CheckDate(const CTime &StartTime,const CTime &StopTime,const CTime &DirName);
	void GetStartStopTime(CTime &tStartTime, CTime &tStopTime);
	int SearchLocalFile(int iDevIndex,int iChanIndex,const CTime &StartTime,const CTime &StopTime,int iFileType);
    vector<LOCAL_FILE_INFO> m_vLocalFile;  //查找得到的文件数组
	int m_iRecType;                         //文件类型
// Dialog Data
	//{{AFX_DATA(CPlayLocalFile)
	enum { IDD = IDD_PAGE_LOCAL };
	CListCtrl	m_ctrlFileList;
	CSliderCtrl	m_sliderPlay;
	CDateTimeCtrl	m_StartTime;
	CDateTimeCtrl	m_StopTime;
	CDateTimeCtrl	m_StartDate;
	CDateTimeCtrl	m_StopDate;
	CComboBox	m_coRecType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPlayLocalFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPlayLocalFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSearchLocal();
	afx_msg void OnSelchangeComboTypeLocal();
	afx_msg void OnDblclkFileList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnPlayLocal();
	afx_msg void OnBtnStopLocal();
	afx_msg void OnBtnFastLocal();
	afx_msg void OnBtnSlowLocal();
	afx_msg void OnReleasedcaptureSliderPlayLocal(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonDel();
	afx_msg void OnButtonDelAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYLOCALFILE_H__D37ADA99_1F39_4487_8A4F_9FC259831BD6__INCLUDED_)
