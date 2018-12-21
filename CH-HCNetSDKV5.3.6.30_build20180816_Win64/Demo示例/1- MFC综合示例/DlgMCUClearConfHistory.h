#if !defined(AFX_DLGMCUCLEARCONFHISTORY_H__69AEC60E_AFCD_4C63_A701_C4046EAD555F__INCLUDED_)
#define AFX_DLGMCUCLEARCONFHISTORY_H__69AEC60E_AFCD_4C63_A701_C4046EAD555F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUClearConfHistory.h : header file
//

#include "XMLParamsConvert.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUClearConfHistory dialog

class CDlgMCUClearConfHistory : public CDialog
{
// Construction
public:
	CDlgMCUClearConfHistory(CWnd* pParent = NULL);   // standard constructor

    ~CDlgMCUClearConfHistory()
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
	//{{AFX_DATA(CDlgMCUClearConfHistory)
	enum { IDD = IDD_DLG_MCU_CLEAR_CONF_HISTORY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUClearConfHistory)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUClearConfHistory)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnBtnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    BOOL OnInitDialog();

private:

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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCUCLEARCONFHISTORY_H__69AEC60E_AFCD_4C63_A701_C4046EAD555F__INCLUDED_)
