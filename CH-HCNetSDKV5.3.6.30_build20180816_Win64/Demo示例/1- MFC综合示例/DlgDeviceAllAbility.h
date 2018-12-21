#if !defined(AFX_DLGDEVICEALLABILITY_H__F53B5F28_97F8_4265_85EB_FDDAFDFF33DF__INCLUDED_)
#define AFX_DLGDEVICEALLABILITY_H__F53B5F28_97F8_4265_85EB_FDDAFDFF33DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeviceAllAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceAllAbility dialog

class CDlgDeviceAllAbility : public CDialog
{
// Construction
public:
	CDlgDeviceAllAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDeviceAllAbility)
	enum { IDD = IDD_DLG_DEVICE_ALL_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeviceAllAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeviceAllAbility)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lResolution;
    LONG    m_lEncodeType;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;

    BOOL FormatSendBufXml(char *pSendBuf);
    BOOL GetDeviceAllAbility(char *pSendBuf, DWORD dwBufSize);
    BOOL WirteBufToFile(char *pBuf, DWORD dwBufSize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICEALLABILITY_H__F53B5F28_97F8_4265_85EB_FDDAFDFF33DF__INCLUDED_)
