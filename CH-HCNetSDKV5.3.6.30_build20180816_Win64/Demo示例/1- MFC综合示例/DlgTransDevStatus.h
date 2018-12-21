#if !defined(AFX_DLGTRANSDEVSTATUS_H__69DE1A38_0AC5_4B93_84CE_553C48A46858__INCLUDED_)
#define AFX_DLGTRANSDEVSTATUS_H__69DE1A38_0AC5_4B93_84CE_553C48A46858__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTransDevStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTransDevStatus dialog
#define MAX_TRANS_CHAN_NUM  256
class CDlgTransDevStatus : public CDialog
{
// Construction
public:
	CDlgTransDevStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTransDevStatus)
	enum { IDD = IDD_DLG_TRANS_DEV_STATUS };
	CListCtrl	m_listTransChan;
	CListCtrl	m_listDstIp;
	CListCtrl	m_listDstEncInfo;
	DWORD	m_dwLeftResource;
	DWORD	m_dwTotalResource;
	BYTE	m_byCpuLoad;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTransDevStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTransDevStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnUpdate();
	afx_msg void OnBtnExit();
	afx_msg void OnClickListTransChan(NMHDR* pNMHDR, LRESULT* pResult);

#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int  m_iDeviceIndex;
	int  m_iCurSelItem;
	BOOL m_bGetAll;
	int  m_iCount;
	NET_DVR_TRANSDEVICE_STATUS m_struTransDevStatus; //转码设备状态
	char* m_pRecv; //转码设备状态
	NET_DVR_STREAM_INFO m_struStreamInfo[MAX_TRANS_CHAN_NUM];
	DWORD m_dwStatusList[MAX_TRANS_CHAN_NUM];	

	void InsertDataToList(DWORD dwList);//dwList = 0 转码通道表，dwList = 1目标IP表，dwList = 3目标编码格式表
	CString GetFormatType(BYTE byIndex);
	CString GetVideoEncType(BYTE byIndex);
	CString GetResolutionName(BYTE byIndex);
	//CString GetVideoBitrate(DWORD dwIndex);
	CString GetFrameRate(DWORD dwIndex);
	CString GetAudioEncType(BYTE dwIndex);
	void GetDeviceStatus();
	void SaveStreamInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRANSDEVSTATUS_H__69DE1A38_0AC5_4B93_84CE_553C48A46858__INCLUDED_)
