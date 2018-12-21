#if !defined(AFX_DLGMCUGETTERMGROUPLIST_H__43CCAF93_DEF4_4579_BCF9_44F97F7C8E64__INCLUDED_)
#define AFX_DLGMCUGETTERMGROUPLIST_H__43CCAF93_DEF4_4579_BCF9_44F97F7C8E64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUGetTermGroupList.h : header file
//


#include "XMLParamsConvert.h"
#include "MCUGeneralDef.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUGetTermGroupList dialog

class CDlgMCUGetTermGroupList : public CDialog
{
// Construction
public:
	CDlgMCUGetTermGroupList(CWnd* pParent = NULL);   // standard constructor

    ~CDlgMCUGetTermGroupList()
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
	//{{AFX_DATA(CDlgMCUGetTermGroupList)
	enum { IDD = IDD_DLG_MCU_GET_TERM_GROUP_LIST };
		// NOTE: the ClassWizard will add data members here
	CListCtrl* m_pListGroupInfo;
    CListCtrl* m_pListTermInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUGetTermGroupList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUGetTermGroupList)
	afx_msg void OnBtnGet();
	afx_msg void OnClickLstGroupInfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:

	DWORD m_dwGroupNum;
	TermGroupInfo m_TermGroupInfoList[MAX_GROUP_COUNT];

    char    *m_szRequestURL;
    char*   m_pXMLParamBuf;
    DWORD   m_dwXMLParamBufLen;
    char    *m_szXMLResultBuf;
    DWORD   m_dwXMLResultBufLen;	
char    *m_szXMLStatus;
	
	CString ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf);
	
	void InsertGroupInfo(const TermGroupInfo& struTermGroupInfo);

	void InsertTermInfo(char* pTermNO);

public:

	int   m_iDeviceIndex;
    LONG  m_lUserID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCUGETTERMGROUPLIST_H__43CCAF93_DEF4_4579_BCF9_44F97F7C8E64__INCLUDED_)
