#if !defined(AFX_DLGMCUDELCONFERENCE_H__3A5CC9F4_F74D_4708_A806_9C2D9F604E4B__INCLUDED_)
#define AFX_DLGMCUDELCONFERENCE_H__3A5CC9F4_F74D_4708_A806_9C2D9F604E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUDelConference.h : header file
//

#include "XMLParamsConvert.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUDelConference dialog

class CDlgMCUDelConference : public CDialog
{
// Construction
public:
	CDlgMCUDelConference(CWnd* pParent = NULL);   // standard constructor

    ~CDlgMCUDelConference()
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
	//{{AFX_DATA(CDlgMCUDelConference)
	enum { IDD = IDD_DLG_MCU_DEL_CONFERENCE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUDelConference)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUDelConference)
	afx_msg void OnBtnDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL OnInitDialog();

private:
	CString m_csConfID;

	//DWORD     m_dwConfID;

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

#endif // !defined(AFX_DLGMCUDELCONFERENCE_H__3A5CC9F4_F74D_4708_A806_9C2D9F604E4B__INCLUDED_)
