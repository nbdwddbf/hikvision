#if !defined(AFX_DLGENCODEABILITY_H__50106965_3EAF_41C6_8F18_14E7DD14AE5C__INCLUDED_)
#define AFX_DLGENCODEABILITY_H__50106965_3EAF_41C6_8F18_14E7DD14AE5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEncodeAbility.h : header file
//
#include "Markup.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEncodeAbility dialog

#define MAXENCODETYPE				8 
#define MAXRESOLUTIONTYPE			50
#define MAXFRAMERATETYPE			20
#define MAXINTERVALBPFRAMETYPE      3
#define MAXVIDEOBITRATETYPE			28
#define MAXAUDIOENCODETYPE          100
typedef struct tagVIDEOCOMPRESSINFO
{
    LONG lMinVideoBitrate[MAXRESOLUTIONTYPE];
    LONG lMaxVideoBitrate[MAXRESOLUTIONTYPE];
    LONG lEFrame;
    BYTE byVideoEncodeType[MAXENCODETYPE];
    BYTE byVideoResolution[MAXRESOLUTIONTYPE];
    BYTE byVideoFrameRate[MAXFRAMERATETYPE];
    BYTE byIntervalBPFrame[MAXINTERVALBPFRAMETYPE];
}VIDEOCOMPRESSINFO, *LPVIDEOCOMPRESSINFO;

typedef struct tagVIDEOCOMPRESSCFG
{
    VIDEOCOMPRESSINFO struMainPara;
    VIDEOCOMPRESSINFO struSubPara;
}VIDEOCOMPRESSCFG, *LPVIDEOCOMPRESSCFG;

typedef struct tagAUDIOCOMPRESSINFO
{   
    BYTE byAudioEncodeType[MAXAUDIOENCODETYPE];
    BYTE byVoiceTalkEncodeType[MAXAUDIOENCODETYPE];
}AUDIOCOMPRESSINFO, *LPAUDIOCOMPRESSINFO;

typedef struct tagENCODE_ABILITY_PARAM
{
    AUDIOCOMPRESSINFO   struAudioCompress;
    DWORD               dwVideoChanNum;
    VIDEOCOMPRESSCFG    struVideoCompressCfg[MAX_CHANNUM_V30];
}ENCODE_ABILITY_PARAM, *LPENCODE_ABILITY_PARAM;

class CDlgEncodeAbility : public CDialog
{
// Construction
public:
	CDlgEncodeAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEncodeAbility)
	enum { IDD = IDD_DLG_ENCODE_ABILITY };
	CComboBox	m_comboResolution;
	CComboBox	m_comboEncodeType;
	CListBox	m_listVideoFrameRate;
	CListBox	m_listVideoResolution;
	CListBox	m_listVideoEncode;
	CListBox	m_listIntervalBPFrame;
	CComboBox	m_comboStreamType;
	CListBox	m_listAudioEncode;
	CComboBox	m_comboChannel;
	CListBox	m_listVoicetalkEncode;
	int		m_iMaxVideoBitrate;
	int		m_iMinVideoBitrate;
	int		m_iEFrame;
	CString	m_sVideoFrame;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEncodeAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEncodeAbility)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboStreamType();
	afx_msg void OnSelchangeComboChannel();
	afx_msg void OnBtnCurrenEncodeAbility();
	afx_msg void OnBtnDeviceAllAbility();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
	DWORD   m_dwVideoChan;
    char    *m_pRecvBuf;
	char *m_pRecvBuf10;
    char    *m_pSendBuf;
    ENCODE_ABILITY_PARAM m_struEncodeAbility;
	DWORD m_dwVideoChanNO;
	BOOL m_bEncode20;
	BOOL m_bEncode10;

private:

    CString m_csVideoResolution[MAXRESOLUTIONTYPE];
    CString m_csVideoEncodeType[MAXENCODETYPE];
	CString m_csVideoFrameRate[MAXRESOLUTIONTYPE];
	int m_lMaxVideoBitrate[MAXRESOLUTIONTYPE];
	int m_lMinVideoBitrate[MAXRESOLUTIONTYPE];

public:
    void InitWnd();
    BOOL GetEncodeAbility();    
    BOOL GetCurrentEncodeAbility();
    void InitString();
    
    void InitVideiEncodeTypeString();

    void InitReolutionCombo();
    void InitEncodeTypeCombo();

    void SetEncodeAbilityToWnd(ENCODE_ABILITY_PARAM &struEncodeAbility);
    void SetAudioCompressInfoToWnd(AUDIOCOMPRESSINFO &struAudioCompressInfo);
    void SetVideoCompressCfgToWnd(VIDEOCOMPRESSCFG &struVideoCompressCfg);
    void SetVideoCompressInfoToWnd(VIDEOCOMPRESSINFO &struVideoCompressInfo);
    
    
    BOOL ParseEncodeAbility(char *pBuf, DWORD dwBufSize);
    BOOL ParseAudioVideoXml(CMarkup &struMarkup);
    BOOL ParseAudioCompressXml(CMarkup &struMarkup);
    BOOL ParseAudioEncodeTypeXml(CMarkup &struMarkup);
    BOOL ParseVoiceTalkEncodeTypeXml(CMarkup &struMarkup);

    BOOL ParseVideoCompressXml(CMarkup &struMarkup);
    BOOL ParseMainChanXml(CMarkup &struMarkup, VIDEOCOMPRESSINFO& struMainPara);
    BOOL ParseSubChanXml(CMarkup &struMarkup, VIDEOCOMPRESSINFO& struSubPara);

    BOOL ParseMinMaxVideoRate(CMarkup &struMarkup, LONG *lMinVideoBitrate, LONG *lMaxVideoBitrate);
    BOOL ParseEFrame(CMarkup &struMarkup, LONG &lEFrame);
    BOOL ParseVideoEncodeType(CMarkup &struMarkup, BYTE *byVideoEncodeType, DWORD dwArraySize);
    BOOL ParseVideoResolution(CMarkup &struMarkup, BYTE *byVideoResolution, DWORD dwArraySize);
    BOOL ParseVideoFrameRate(CMarkup &struMarkup, BYTE *byVideoFrameRate, DWORD dwArraySize);
    BOOL ParseIntervalBPFrame(CMarkup &struMarkup, BYTE *byIntervalBPFrameRate, DWORD dwArraySize);

//     LONG lMinVideoBitrate;
//     LONG lMaxVideoBitrate;
//     LONG lEFrame;
//     BYTE byVideoEncodeType[MAXENCODETYPE];
//     BYTE byVideoResolution[MAXRESOLUTIONTYPE];
//     BYTE byVideoFrameRate[MAXFRAMERATETYPE];
//     BYTE byIntervalBPFrame[MAXINTERVALBPFRAMETYPE];
// 

    
    BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
    void    ParseStrIndex(CString strIndex, byte* array, int iArrayLength);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENCODEABILITY_H__50106965_3EAF_41C6_8F18_14E7DD14AE5C__INCLUDED_)
