#if !defined(AFX_DLGCLEARACSPARAM_H__C1E96FEA_F331_4AAF_8057_3E26DE35D003__INCLUDED_)
#define AFX_DLGCLEARACSPARAM_H__C1E96FEA_F331_4AAF_8057_3E26DE35D003__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgClearAcsParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgClearAcsParam dialog

class CDlgClearAcsParam : public CDialog
{
// Construction
public:
	CDlgClearAcsParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgClearAcsParam)
	enum { IDD = IDD_DLG_CLEAR_ACS };
	BOOL	m_bCard;
	BOOL	m_bCardRightHolidayGroup;
	BOOL	m_bCardRightHoliDayPlan;
	BOOL	m_bCardRightPlanTemplate;
	BOOL	m_bCardRightWeekPlan;
	BOOL	m_bDoorStatusHolidayGroup;
	BOOL	m_bDoorStatusHolidayPlan;
	BOOL	m_bDoorStatusPlanTemplate;
	BOOL	m_bDoorStatusWeekPlan;
	BOOL	m_bGroup;
	BOOL	m_bVerifyHolidayGroup;
	BOOL	m_bVerifyHolidayPaln;
	BOOL	m_bVerifyPlanTemplate;
	BOOL	m_bVerifyWeekPaln;
    BOOL	m_bAntiSneakCfg;
    BOOL	m_bDoorEventCardLinkge;
	BOOL	m_bDoorCardPasswdCfg;
	BOOL	m_bPersonStatistical;
    BOOL    m_bExamInfo;
    BOOL    m_bExamineeInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgClearAcsParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgClearAcsParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnClearAcsParam();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	LONG m_lChannel;
	int m_iDevIndex;
    int m_iLocalControllerID;
    BOOL m_bBlackListPic;
    BOOL m_bBlackList;
    BOOL m_bFailedFace;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLEARACSPARAM_H__C1E96FEA_F331_4AAF_8057_3E26DE35D003__INCLUDED_)
