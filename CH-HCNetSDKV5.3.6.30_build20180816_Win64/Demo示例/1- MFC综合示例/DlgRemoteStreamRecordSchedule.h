#pragma once
#include "afxwin.h"


// CDlgRemoteStreamRecordSchedule dialog

class CDlgRemoteStreamRecordSchedule : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteStreamRecordSchedule)

public:
	CDlgRemoteStreamRecordSchedule(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteStreamRecordSchedule();

// Dialog Data


public:

	//{{AFX_DATA(CDlgRemoteStreamRecordSchedule)
	enum { IDD = IDD_DLG_REMOTE_RECORD_SCHEDULE1 };
	CComboBox m_comboWeekday;
	BOOL m_bCheckAllDay;
	CComboBox m_comboAllDayType;
	int m_iHour11;
	int m_iMin11;
	int m_iHour12;
	int m_iMin12;
	int m_iHour21;
	int m_iMin21;
	int m_iHour22;
	int m_iMin22;
	int m_iHour31;
	int m_iMin31;
	int m_iHour32;
	int m_iMin32;
	int m_iHour41;
	int m_iMin41;
	int m_iHour42;
	int m_iMin42;
	int m_iHour51;
	int m_iMin51;
	int m_iHour52;
	int m_iMin52;
	int m_iHour61;
	int m_iMin61;
	int m_iHour62;
	int m_iMin62;
	int m_iHour71;
	int m_iMin71;
	int m_iHour72;
	int m_iMin72;
	int m_iHour81;
	int m_iMin81;
	int m_iHour82;
	int m_iMin82;
	CComboBox m_comboTimeRecType1;
	CComboBox m_comboTimeRecType2;
	CComboBox m_comboTimeRecType3;
	CComboBox m_comboTimeRecType4;
	CComboBox m_comboCopyWeekday;
	CComboBox m_comboTimeRecType5;
	CComboBox m_comboTimeRecType6;
	CComboBox m_comboTimeRecType7;
	CComboBox m_comboTimeRecType8;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteStreamRecordSchedule)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteStreamRecordSchedule)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRemoteRecOk();
	afx_msg void OnBnClickedBtnRemoteRecExit();	
	afx_msg void OnBnClickedBtnRemoteRecCopy();
	afx_msg void OnCbnSelchangeComboWeekDay();
	afx_msg void OnBnClickedChkAllDay();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int m_nDate;
	int m_nCopyDate;
	void EnableControl(BOOL bEnable);
	BOOL TimeTest();
	//LPNET_DVR_RECORD_V30 m_struRemoteRecSchedule;
	LPNET_DVR_STREAM_RECORD_INFO m_pstruStreamRecordInfo;
	
    LONG    m_lServerID;
    LONG    m_lChannel;     
    int     m_iDevIndex;
};
