#if !defined(AFX_DLGMCUGETCONFSTATUS_H__49359EB7_7703_4866_8217_F9C1DD48A25A__INCLUDED_)
#define AFX_DLGMCUGETCONFSTATUS_H__49359EB7_7703_4866_8217_F9C1DD48A25A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMCUGetConfStatus.h : header file
//

#include "XMLParamsConvert.h"
#include "MCUGeneralDef.h"
#include "afxwin.h"

struct AVInfo
{
	char szAudioInType[MAX_XML_ELEM_LEN];
	char szAudioOutType[MAX_XML_ELEM_LEN];

	char szVideoInType[MAX_XML_ELEM_LEN];
	char szVideoOutType[MAX_XML_ELEM_LEN];

	DWORD dwAudioInPackets;
	DWORD dwAudioInPackLoss;
	
	DWORD dwAudioOutPackets;
	DWORD dwAudioOutPackLoss;
    DWORD dwAudioBitRate;

	DWORD dwVideoInPackets;
	DWORD dwVideoInPackLoss;
	
	DWORD dwVideoOutPackets;
	DWORD dwVideoOutPackLoss;

	DWORD dwAVBitRate;
	DWORD dwFrameRate;

    DWORD dwResWidth;
    DWORD dwResHeight;

};

struct TerminalStatus
{
	char szTermID[MAX_XML_ELEM_LEN];
	char szTermName[MAX_XML_ELEM_LEN];
	DWORD dwJoinedDur;

	AVInfo struAVInfo;

	char szConnState[MAX_XML_ELEM_LEN];
	char szMuteState[MAX_XML_ELEM_LEN];
	DWORD dwVolume;
	char szAudioInState[MAX_XML_ELEM_LEN];
	char szImageState[MAX_XML_ELEM_LEN];
	char szVideoInState[MAX_XML_ELEM_LEN];
};

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUGetConfStatus dialog

class CDlgMCUGetConfStatus : public CDialog
{
// Construction
public:
	CDlgMCUGetConfStatus(CWnd* pParent = NULL);   // standard constructor
    ~CDlgMCUGetConfStatus()
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
	//{{AFX_DATA(CDlgMCUGetConfStatus)
	enum { IDD = IDD_DLG_MCU_GET_CONF_STATUS };
		// NOTE: the ClassWizard will add data members here

	CComboBox	m_comConfStatus;
	CComboBox	m_comTermConnStatus;
    CComboBox	m_comAudioInType;
    CComboBox	m_comAudioOutType;
	CComboBox	m_comVideoInType;
    CComboBox	m_comVideoOutType;

	CListCtrl* m_pListTerm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMCUGetConfStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMCUGetConfStatus)
	afx_msg void OnBtnGet();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL OnInitDialog();

private:

    int m_nIndex;

	//DWORD   m_dwConfID;
    CString m_csConfID;
	CString m_strConfStatus;
	CString m_strCreatorName;
	DWORD   m_dwConfDuration;
	CString m_strConfContent;


	//CString m_strTermName;
	DWORD   m_dwJoinedDur;
	CString m_strConnState;
	CString m_strMuteState;
	DWORD   m_dwVolume;
	CString m_strAudioInState;
	CString m_strImageState;
	CString m_strVideoInState;

	CString m_strAudioInType;
	CString m_strVideoInType;
	DWORD   m_dwAudioInPackSize;
	DWORD   m_dwVideoInPackSize;
	DWORD   m_dwAudioInPackLoss;
	DWORD   m_dwVideoInPackLoss;

	CString m_strAudioOutType;
	CString m_strVideoOutType;
	DWORD   m_dwAudioOutPackSize;
	DWORD   m_dwVideoOutPackSize;
	DWORD   m_dwAudioOutPackLoss;
	DWORD   m_dwVideoOutPackLoss;

	DWORD   m_dwBitRate;
	DWORD   m_dwFrameRate;

	DWORD   m_dwTermCount;
	TerminalStatus m_TermStatusLst[MAX_TERM_COUNT];

    char    *m_szRequestURL;
    char*   m_pXMLParamBuf;
    DWORD   m_dwXMLParamBufLen;
    char    *m_szXMLResultBuf;
    DWORD   m_dwXMLResultBufLen;	
    char    *m_szXMLStatus;

	CString ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf);

	void InsertTermStateInfo(const TerminalStatus& struTermInfo);

public:
	int   m_iDeviceIndex;
    LONG  m_lUserID;

    CComboBox m_cVideoType;
    int m_dwVFrame;
    int m_iRWidth;
    int m_iRHeight;
    int m_iVFrame;
    CComboBox m_cmbCAType;
    int m_iSample;
    int m_iAFrame;
    DWORD m_dwAudioFrame;
    DWORD m_dwResWidth;
    DWORD m_dwResHeight;
    CString m_strCVideoType;
    CString m_strCAudioType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCUGETCONFSTATUS_H__49359EB7_7703_4866_8217_F9C1DD48A25A__INCLUDED_)
