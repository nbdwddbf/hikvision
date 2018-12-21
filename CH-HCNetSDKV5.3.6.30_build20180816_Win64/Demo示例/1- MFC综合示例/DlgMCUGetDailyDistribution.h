#if !defined(AFX_DLGMCUGETDAILYDISTRIBUTION_H__79A05E84_33A7_435A_B0AC_B394EEAD001E__INCLUDED_)
#define AFX_DLGMCUGETDAILYDISTRIBUTION_H__79A05E84_33A7_435A_B0AC_B394EEAD001E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUGetDailyDistribution.h : header file
//
#include "XMLParamsConvert.h"

#define MAX_DAILY_CONF_COUNT 32

struct ConfDaliyInfo
{
	DWORD dwID;
	DWORD dwDay;
	BOOL bConf;
};
/////////////////////////////////////////////////////////////////////////////
// CDlgMCUGetDailyDistribution dialog

class CDlgMCUGetDailyDistribution : public CDialog
{
// Construction
public:
	CDlgMCUGetDailyDistribution(CWnd* pParent = NULL);   // standard constructor

    ~CDlgMCUGetDailyDistribution()
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
	//{{AFX_DATA(CDlgMCUGetDailyDistribution)
	enum { IDD = IDD_DLG_MCU_GET_DAILY_DISTRBUTION };
		// NOTE: the ClassWizard will add data members here
	CListCtrl* m_pListDailyDistribute;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUGetDailyDistribution)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUGetDailyDistribution)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL OnInitDialog();

private:
	DWORD  m_dwCondYear;
	DWORD  m_dwCondMonth;

    char    *m_szRequestURL;
    char*   m_pXMLParamBuf;
    DWORD   m_dwXMLParamBufLen;
    char    *m_szXMLResultBuf;
    DWORD   m_dwXMLResultBufLen;	
    char    *m_szXMLStatus;

    int  m_nIndex;
	
	CString ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf);

	DWORD   m_dwConfCount;
	ConfDaliyInfo m_ConfDailyLst[MAX_DAILY_CONF_COUNT];

	void InsertConfDailyInfo(const ConfDaliyInfo& struConfDailyInfo);


public:
	int   m_iDeviceIndex;
    LONG  m_lUserID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCUGETDAILYDISTRIBUTION_H__79A05E84_33A7_435A_B0AC_B394EEAD001E__INCLUDED_)
