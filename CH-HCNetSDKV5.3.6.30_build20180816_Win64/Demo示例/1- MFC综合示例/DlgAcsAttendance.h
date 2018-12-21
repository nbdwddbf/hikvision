#pragma once


// CDlgAcsAttendance 对话框

class CDlgAcsAttendance : public CDialog
{
	DECLARE_DYNAMIC(CDlgAcsAttendance)

public:
	CDlgAcsAttendance(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAcsAttendance();

// 对话框数据
	enum { IDD = IDD_DLG_ACS_ATTENDANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnScheduleInfo();
    int m_iDevIndex;
    long m_lServerID;
    afx_msg void OnBnClickedBtnAttendanceSummaryInfo();
    afx_msg void OnBnClickedBtnAttendanceRecordInfo();
    afx_msg void OnBnClickedBtnAbnormalInfo();
    afx_msg void OnBnClickedBtnDepartmentParam();
    afx_msg void OnBnClickedBtnSchedulePlan();
    afx_msg void OnBnClickedBtnAttendanceRule();
    afx_msg void OnBnClickedBtnOrdinaryClass();
    afx_msg void OnBnClickedBtnWorkingClass();
    afx_msg void OnBnClickedBtnAttendanceHolidayGroup();
    afx_msg void OnBnClickedBtnAttendanceHolidayPlan();
};
