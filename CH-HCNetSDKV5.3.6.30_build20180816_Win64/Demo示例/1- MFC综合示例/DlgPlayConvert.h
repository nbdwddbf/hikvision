#if !defined(AFX_DLGPLAYCONVERT_H__7DEA740B_CCC4_44F5_9259_6A768CD15839__INCLUDED_)
#define AFX_DLGPLAYCONVERT_H__7DEA740B_CCC4_44F5_9259_6A768CD15839__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DlgPlayConvert.h : header file
//
#define LPPLAYBACK_CONVERT_SIZE 128		// 结构体指针数组大小
#define NAME_SIZE 64		// 结构体中szName数组大小
#define FRAME_RATE_SIZE 64		// 结构体中dwFrameRate数组大小
#define BIT_RATE_SIZE 64	// 结构体中dwBitRate数组大小
#define FRAME_RATE_STRING_LENGTH 500	// 存储帧率字符串数组大小
#define BIT_RATE_STRING_LENGTH 500		// 存储码率字符串数组大小

typedef struct tagPLAYBACK_CONVERT 
{
	BYTE byIndex;
	char szName[NAME_SIZE];
	DWORD dwFrameRate[FRAME_RATE_SIZE];
	DWORD dwBitRate[BIT_RATE_SIZE];
}PLAYBACK_CONVERT, *LPPLAYBACK_CONVERT;


/////////////////////////////////////////////////////////////////////////////
// DlgPlayConvert dialog

class DlgPlayConvert : public CDialog
{
// Construction
public:
	DlgPlayConvert(CWnd* pParent = NULL);   // standard constructor
    ~DlgPlayConvert();

// Dialog Data
	//{{AFX_DATA(DlgPlayConvert)
	enum { IDD = IDD_DLG_PLAY_CONVERT };
	CComboBox	m_StreamType;
	CComboBox	m_comFormatType;
	CComboBox	m_comVideoEncComplexity;
	CComboBox	m_comVideoFrameRate;
	CComboBox	m_comVideoEnctype;
	CComboBox	m_comVideoBitrate;
	CComboBox	m_comResolution;
	CComboBox	m_comIntervalBPFrame;
	CComboBox	m_comBitrateType;
	CComboBox	m_comPicQuality;
	CComboBox	m_comAudioEnctype;
	short	m_IntervalFrameI;
	BOOL	m_bEnableSVC;
	BYTE	m_byENumber;
	//}}AFX_DATA

  	LONG m_lPlayHandle;
 	void Init(LONG &lplayhandle);
// 	LONG m_lLoginID;
// 	NET_DVR_VOD_PARA m_struVodPara;
// 	int m_iResult;
// 	HWND m_hPlayBackWnd;
// 	NET_DVR_PLAYCOND m_struPlayCon;
	void getComPressionInfoV30(NET_DVR_COMPRESSION_INFO_V30 *struCompressionInfoV30);
	NET_DVR_COMPRESSION_INFO_V30 m_struCompressionInfoV30;
	NET_DVR_COMPRESSIONCFG_ABILITY *m_pCompresscfgAbility;
	DWORD m_iDeviceIndex;
	BOOL OnInitDialog();
	BOOL GetRecordAbility();

    DWORD m_dwCurChanNo;
    char  *m_pRecvBuf;
	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgPlayConvert)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:

	
	// Generated message map functions
	//{{AFX_MSG(DlgPlayConvert)
	afx_msg void OnSet();
	afx_msg void OnEditchangeComResolution();
	afx_msg void OnEditchangeComVedioFrameRate();
	afx_msg void OnSelchangeComVedioFrameRate();
	afx_msg void OnCloseupComResolution();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    BOOL GetResolutionAbility();

	LPPLAYBACK_CONVERT m_pConvert[LPPLAYBACK_CONVERT_SIZE];		// 结构体指针数组
	int m_iResolutionNum;	// 设备支持的转码回放分辨率数目
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAYCONVERT_H__7DEA740B_CCC4_44F5_9259_6A768CD15839__INCLUDED_)
