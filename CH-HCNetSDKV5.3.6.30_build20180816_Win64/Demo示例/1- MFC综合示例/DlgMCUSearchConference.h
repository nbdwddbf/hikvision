#if !defined(AFX_DLGMCUSEARCHCONFERENCE_H__4BF6F2A6_9086_4EB4_A3A3_C5C2EE2B0B91__INCLUDED_)
#define AFX_DLGMCUSEARCHCONFERENCE_H__4BF6F2A6_9086_4EB4_A3A3_C5C2EE2B0B91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUSearchConference.h : header file
//

#include "MCUGeneralDef.h"

#include "XMLParamsConvert.h"

#define MAX_MATCH_COUNT       256
//#define ISAPI_STATUS_LEN      4096


struct TimeSpain
{
	char szStartTime[MAX_XML_ELEM_LEN];
	char szEndTime[MAX_XML_ELEM_LEN];
};

struct ConferenceMatchInfo
{
	//DWORD dwConfID;
    char  szConfID[MAX_XML_ELEM_LEN];
	char  szConfName[MAX_XML_ELEM_LEN];
	TimeSpain struTimeSpain;
	char  szConfType[MAX_XML_ELEM_LEN];
	char  szConfState[MAX_XML_ELEM_LEN];
	
};


struct ConferenceSearchDes
{
	char  szSearchID[MAX_XML_ELEM_LEN];
	TimeSpain struTimeSpain;
	char  szConfType[MAX_XML_ELEM_LEN];
	char  szConfState[MAX_XML_ELEM_LEN];
	DWORD dwMaxResults;
	DWORD dwSearchResultsPosition;

};

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUSearchConference dialog

class CDlgMCUSearchConference : public CDialog
{
// Construction
public:
	CDlgMCUSearchConference(CWnd* pParent = NULL);   // standard constructor

    ~CDlgMCUSearchConference()
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
	//{{AFX_DATA(CDlgMCUSearchConference)
	enum { IDD = IDD_DLG_MCU_CONF_SEARCH };
		// NOTE: the ClassWizard will add data members here
	CComboBox	m_comConfType;
	CComboBox	m_comConfStatus;

	CComboBox	m_comSearchRet;
	CComboBox	m_comSearchStatus;

	CComboBox	m_comConfTypeRet;
	CComboBox	m_comConfStatusRet;
	CListCtrl* m_pListConfInfoRet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUSearchConference)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUSearchConference)
	afx_msg void OnBtnSearch();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL OnInitDialog();

private:
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

	//Ret会议开始时间
    DWORD    m_dwStartYearRet;
    DWORD    m_dwStartMonthRet;
    DWORD    m_dwStartDayRet;
    DWORD    m_dwStartHourRet;
    DWORD    m_dwStartMinuteRet;
	
    //Ret会议结束时间
    DWORD    m_dwEndYearRet;
    DWORD    m_dwEndMonthRet;
    DWORD    m_dwEndDayRet;
    DWORD    m_dwEndHourRet;
    DWORD    m_dwEndMinuteRet;

	CString  m_strSearchID;

	DWORD    m_dwCountRet;

	CString  m_strSearchRet;
	CString  m_strSearchStatus;
    CString  m_strSearchStatusRet;

	CString  m_strConfType;
	CString  m_strConfStatus;

	DWORD    m_dwMaxCountRet;
	DWORD    m_dwCountStartRet;

	CString  m_strConfTypeRet;
	CString  m_strConfStatusRet;


	DWORD    m_dwMatchCount;
	
	ConferenceMatchInfo m_lstConfMatch[MAX_MATCH_COUNT];

	ConferenceSearchDes m_struConfSearchDes;


    char    *m_szRequestURL;
    char*   m_pXMLParamBuf;
    DWORD   m_dwXMLParamBufLen;
    char    *m_szXMLResultBuf;
    DWORD   m_dwXMLResultBufLen;	
    char    *m_szXMLStatus;

	
	CString ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf);


	void InsertMatchConf(const ConferenceMatchInfo& struConfInfo);

	BOOL StringToTime(char* szTime, int length, DWORD& year, DWORD& Month, DWORD& day, DWORD& hour, DWORD& minute);
	

public:
	int   m_iDeviceIndex;
    LONG  m_lUserID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCUSEARCHCONFERENCE_H__4BF6F2A6_9086_4EB4_A3A3_C5C2EE2B0B91__INCLUDED_)
