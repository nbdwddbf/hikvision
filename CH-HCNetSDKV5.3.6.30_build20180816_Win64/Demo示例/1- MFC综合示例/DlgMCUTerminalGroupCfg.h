#if !defined(AFX_DLGMCUTERMINALGROUPCFG_H__C874AAB9_6A00_4A2E_98FC_D488A45639B2__INCLUDED_)
#define AFX_DLGMCUTERMINALGROUPCFG_H__C874AAB9_6A00_4A2E_98FC_D488A45639B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUTerminalGroupCfg.h : header file
//

#include "XMLParamsConvert.h"

#include "MCUGeneralDef.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUTerminalGroupCfg dialog

class CDlgMCUTerminalGroupCfg : public CDialog
{
// Construction
public:
	CDlgMCUTerminalGroupCfg(CWnd* pParent = NULL);   // standard constructor

    ~CDlgMCUTerminalGroupCfg()
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
	//{{AFX_DATA(CDlgMCUTerminalGroupCfg)
	enum { IDD = IDD_DLG_MCU_TERM_GROUP_CFG };
		// NOTE: the ClassWizard will add data members here
	//CListCtrl* m_pListGroupInfo;
    CListCtrl* m_pListTermInfo;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUTerminalGroupCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUTerminalGroupCfg)
	afx_msg void OnBtnCfg();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();

	afx_msg void OnBtnAddTerm();
	afx_msg void OnBtnAddGroup();
	afx_msg void OnClickLstGroupInfo(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnRadGet();
	afx_msg void OnRadCfg();
	afx_msg void OnRadAdd();
	afx_msg void OnRadDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	//DWORD m_dwGroupNum;
	//TermGroupInfo m_TermGroupInfoList[MAX_GROUP_COUNT];

	TermGroupInfo m_struTermGroupInfo;


	//DWORD  m_TermNOListTmp[MAX_TERM_COUNT];
	


	//DWORD   m_dwTermNO;
    CString   m_csTermNO;
	CString   m_csGroupID;
	CString m_strGroupName;
	BOOL    m_bEnable;

	char    *m_szRequestURL;
char*   m_pXMLParamBuf;
DWORD   m_dwXMLParamBufLen;
char    *m_szXMLResultBuf;
DWORD   m_dwXMLResultBufLen;	
char    *m_szXMLStatus;
	
	CString ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf);
	
	//void InsertGroupInfo(const TermGroupInfo& struTermGroupInfo);	

    void InsertTermInfo(DWORD dwTermNumTmp, char* TermNo);

public:
	int   m_iDeviceIndex;
    LONG  m_lUserID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCUTERMINALGROUPCFG_H__C874AAB9_6A00_4A2E_98FC_D488A45639B2__INCLUDED_)
