#if !defined(AFX_DLGMCUCONFERENCECTRL_H__84EC1B12_FFA9_48FD_B8D6_0195578A33A4__INCLUDED_)
#define AFX_DLGMCUCONFERENCECTRL_H__84EC1B12_FFA9_48FD_B8D6_0195578A33A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUConferenceCtrl.h : header file
//

#include "XMLParamsConvert.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUConferenceCtrl dialog

class CDlgMCUConferenceCtrl : public CDialog
{
// Construction
public:
	CDlgMCUConferenceCtrl(CWnd* pParent = NULL);   // standard constructor
    ~CDlgMCUConferenceCtrl()
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
	//{{AFX_DATA(CDlgMCUConferenceCtrl)
	enum { IDD = IDD_DLG_MCU_CONF_CTRL };
		// NOTE: the ClassWizard will add data members here

	CComboBox	m_comCtrlCMD;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUConferenceCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUConferenceCtrl)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnBtnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL OnInitDialog();

private:

	//DWORD   m_dwConfID;
    CString m_csConfID;

	CString m_strConfID;
	CString m_strCtrlCMD;
	CString m_strRemindContent;


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

#endif // !defined(AFX_DLGMCUCONFERENCECTRL_H__84EC1B12_FFA9_48FD_B8D6_0195578A33A4__INCLUDED_)
