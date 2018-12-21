#if !defined(AFX_DLGMCUTERMINALCTRL_H__A3409C64_2C17_42A9_A087_2632B65D46E7__INCLUDED_)
#define AFX_DLGMCUTERMINALCTRL_H__A3409C64_2C17_42A9_A087_2632B65D46E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUTerminalCtrl.h : header file
//

#include "XMLParamsConvert.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUTerminalCtrl dialog

class CDlgMCUTerminalCtrl : public CDialog
{
// Construction
public:
	CDlgMCUTerminalCtrl(CWnd* pParent = NULL);   // standard constructor

    ~CDlgMCUTerminalCtrl()
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
	//{{AFX_DATA(CDlgMCUTerminalCtrl)
	enum { IDD = IDD_DLG_MCU_TERMINAL_CTRL };
	CButton    m_btnMute;
    CButton    m_btnAudioInput;
	CEdit      m_edtVolume;
    CEdit      m_edtAudioInputVol;
    CString    m_csURL;
    CComboBox  m_comOperType;
    CString    m_csOperType;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUTerminalCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUTerminalCtrl)
	afx_msg void OnBtnOk();
	afx_msg void OnChkMute();
    afx_msg void OnChkAudioInput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL OnInitDialog();

private:

	//DWORD     m_dwConfID;
	//DWORD     m_dwTermID;

    //CString  m_csConfID;
    //CString  m_csTermID;

	
	//BOOL    m_bDisconnect;
	BOOL    m_bMute;
	DWORD   m_dwVolume;
	BOOL    m_bAudioInputDisabled;
	DWORD   m_dwAudioInputVolume;

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

#endif // !defined(AFX_DLGMCUTERMINALCTRL_H__A3409C64_2C17_42A9_A087_2632B65D46E7__INCLUDED_)
