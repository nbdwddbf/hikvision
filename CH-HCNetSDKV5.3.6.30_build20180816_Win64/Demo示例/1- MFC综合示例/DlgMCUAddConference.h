#if !defined(AFX_DLGMCUADDCONFERENCE_H__C67E1054_0854_43E9_9258_C0100FD58659__INCLUDED_)
#define AFX_DLGMCUADDCONFERENCE_H__C67E1054_0854_43E9_9258_C0100FD58659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUAddConference.h : header file
//


#include "MCUGeneralDef.h"
#include "XMLParamsConvert.h"
#include "afxwin.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgMCUAddConference dialog

class CDlgMCUAddConference : public CDialog
{
// Construction
public:
	CDlgMCUAddConference(CWnd* pParent = NULL);   // standard constructor

    ~CDlgMCUAddConference()
    {
        if (NULL != m_szRequestURL)
        {
            delete[] m_szRequestURL;
            m_szRequestURL = NULL;
        }
        if (NULL != m_szXMLResultBuf)
        {
            delete[] m_szXMLResultBuf;
            m_szXMLResultBuf = NULL;
        } 
        if (NULL != m_szXMLResultBuf)
        {
            delete[] m_szXMLStatus;
            m_szXMLStatus = NULL;
        }
    }

// Dialog Data
	//{{AFX_DATA(CDlgMCUAddConference)
	enum { IDD = IDD_DLG_MCU_ADD_CONFERENCE };
		// NOTE: the ClassWizard will add data members here
    CComboBox	m_comAutoRemindTime;
    CComboBox	m_comSoundPSTTime;
    CComboBox	m_comRegularType;
    CComboBox	m_comWeekDate;
    CComboBox	m_comMonthDate;
    CComboBox	m_comWinMode;
    CComboBox	m_comViewMode;

    CButton     m_btnAddMember;
    CButton     m_btnAddTerm;
    CButton     m_btnAddWinTerm;
    CButton     m_btnMemberViewTerm;

    CButton     m_btnEnableLoopTerm;
    CButton     m_btnEnableSoundPro;

    CEdit       m_edtLoopTime;
    //CEdit       m_edtLoopTermID;
    CEdit       m_edtLoopTermNO;

    CEdit       m_edtSoundProWinNO;
    CEdit       m_edtTermWinNO;
    CEdit       m_edtWinTermTermNO;

	//CEdit       m_edtConfID;


    CListCtrl* m_pListMember;
    CListCtrl* m_pListLoopTerm;
    CListCtrl* m_pListWinTerm;
    CListCtrl* m_pListMemberView;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUAddConference)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
    BOOL OnInitDialog();
	//{{AFX_MSG(CDlgMCUAddConference)
	afx_msg void OnBtnAdd();
	afx_msg void OnRadDefinite();
	afx_msg void OnRadTemp();
	afx_msg void OnChkChairman();
	afx_msg void OnBtnAddMember();
	afx_msg void OnChkLoopEnable();
	afx_msg void OnBtnAddTerminal();
	afx_msg void OnChkSoundProEnable();
	afx_msg void OnChkFixed();
	afx_msg void OnBtnAddWinTerm();
	afx_msg void OnBtnAddMemberView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CString m_strConferTitle; //会议名称

    //会议开始时间
    DWORD    m_dwStartYear;
    DWORD    m_dwStartMonth;
    DWORD    m_dwStartDay;
    DWORD    m_dwStartHour;
    DWORD    m_dwStartMinute;

    //会议结束时间
    DWORD    m_dwEndYear;
    DWORD    m_dwEndMonth;
    DWORD    m_dwEndDay;
    DWORD    m_dwEndHour;
    DWORD    m_dwEndMinute;

    CString m_strConferContent;//会议内容
    
    BOOL    m_bConfTypeRegular;//是否是定时会议
    CString m_strNotification; //通知

	CString   m_csMembTermNO;
    BOOL    m_bIsChairMan;

    DWORD   m_dwRepeatTime;     //重复次数

    BOOL    m_bEnableLoopTerm; //使能LoopTerminal
    DWORD   m_dwLoopTime;      //轮询间隔时间

    BOOL    m_bEnableSoundPri;//使能语音激励
    DWORD   m_dwSoundProWinNO;


    DWORD   m_dwMemberCount;  //会议成员数目

    //WinTermList
    DWORD   m_dwWinTermWinNO;
	CString   m_csWinTermTermNO;
    BOOL    m_bFixed;

    //LoopTermList
	CString  m_csLoopTermNO;

    //MemberViewList
    DWORD  m_dwMemberViewCount;
    DWORD  m_dwMembViewMembNO;


    DWORD   m_dwLoopTermCount;
    DWORD   m_dwWinTermCount;
    CString   m_csMemberViewID;

    //Comb相关联的变量
    DWORD       m_dwAutoRemindTime;
    DWORD       m_dwSoundPSTTime;
    CString     m_strRegularType;
    CString     m_strWeekDate;
    DWORD       m_dwMonthDate;
    CString     m_strWinMode;
    CString     m_strViewMode;

	//DWORD		m_dwConfID;
    CString     m_csConfID;
	BOOL        m_bEnabled;

	Conference  m_struConf;

    char    *m_szRequestURL;
    char*   m_pXMLParamBuf;
    DWORD   m_dwXMLParamBufLen;
    char    *m_szXMLResultBuf;
    DWORD   m_dwXMLResultBufLen;	
    char    *m_szXMLStatus;

	CString ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf);


public:
	int   m_iDeviceIndex;
    LONG  m_lUserID;
		
    CComboBox m_cmbTimeType;
    int m_dwDuration;
    CString m_szTimeType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCUADDCONFERENCE_H__C67E1054_0854_43E9_9258_C0100FD58659__INCLUDED_)
