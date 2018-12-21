#if !defined(AFX_DLGCURRENTENCODEABILITY_H__BA6E2F62_ECBA_4A5A_BAB3_0BECC9904BEB__INCLUDED_)
#define AFX_DLGCURRENTENCODEABILITY_H__BA6E2F62_ECBA_4A5A_BAB3_0BECC9904BEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCurrentEncodeAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCurrentEncodeAbility dialog
#include "Markup.h"
#define MAXENCODETYPE				8 
#define MAXFRAMERATETYPE			20
#define MAX_RESOLUTION_ENTRY        16

typedef struct tagRESOLUTION_ENTRY
{
    BYTE    byResolutionIndex;    
    BYTE    byVideoFrameRate[MAXFRAMERATETYPE];
}RESOLUTION_ENTRY, *LPRESOLUTION_ENTRY;

typedef struct tagSUB_CHAN_LIST
{
    DWORD   dwResolutionEntryNum;
    RESOLUTION_ENTRY struResolutionEntry[MAX_RESOLUTION_ENTRY];
}SUB_CHAN_LIST, *LPSUB_CHAN_LIST;
typedef struct tagCURRENT_ENCODE_PARAM
{
    BYTE byVideoEncodeType;
    BYTE byResolution;
    BYTE byVideoFrameRate[MAXFRAMERATETYPE];
    BYTE  byChanNum;
    SUB_CHAN_LIST   struSubChanList[MAX_CHANNUM_V30];
}CURRENT_ENCODE_PARAM, *LPCURRENT_ENCODE_PARAM;

class CDlgCurrentEncodeAbility : public CDialog
{
// Construction
public:
	CDlgCurrentEncodeAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCurrentEncodeAbility)
	enum { IDD = IDD_DLG_CURRENT_ENCODE_ABILITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCurrentEncodeAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCurrentEncodeAbility)
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
    CURRENT_ENCODE_PARAM m_struCurrentEncode;
public:
    BOOL WirteBufToFile(char *pBuf, DWORD dwBufSize);
    BOOL FormatSendBufXml(char *pSendBuf);
    BOOL GetCurrentEncodeAbiliity(char *pSendBuf, DWORD dwBufSize);
    
    BOOL ParseCurrentEncodeAbility(char *pRecvBuf, DWORD dwBufSize);
    BOOL ParseCurrentEncodeAbilityXml(CMarkup &struMarkUp);
    BOOL ParseVideoEncodeTypeXml(CMarkup &struMarkUp);
    BOOL ParseVideoResolutionXml(CMarkup &struMarkUp);
    BOOL ParseVideoFrameRateXml(CMarkup &struMarkUp, BYTE *byVideoFramRate, DWORD dwSize);

    BOOL ParseSubChanlList(CMarkup &struMarkup);

    BOOL ParseResolutionEntry(CMarkup &struMarkup, int nChanIndex);

    void SetCurrentEncodeParamToWnd(CURRENT_ENCODE_PARAM &struEncodeParam);
    void SetSubChanListToWnd(SUB_CHAN_LIST &struSbuChanList);
    void SetResolutionEntry(RESOLUTION_ENTRY &struResolutionEntry);

    void ParseStrIndex(CString strIndex, byte* array, int iArrayLength);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCURRENTENCODEABILITY_H__BA6E2F62_ECBA_4A5A_BAB3_0BECC9904BEB__INCLUDED_)
