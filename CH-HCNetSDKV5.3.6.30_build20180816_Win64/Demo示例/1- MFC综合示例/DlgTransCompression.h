#if !defined(AFX_DLGTRANSCOMPRESSION_H__3961EF99_F1EB_4E5C_9D1C_E1F899D91EB9__INCLUDED_)
#define AFX_DLGTRANSCOMPRESSION_H__3961EF99_F1EB_4E5C_9D1C_E1F899D91EB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTransCompression.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTransCompression dialog

class CDlgTransCompression : public CDialog
{
// Construction
public:
	CDlgTransCompression(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTransCompression)
	enum { IDD = IDD_DLG_TRANS_COMPRESSION };
	CComboBox	m_comboStreamType;
	CListCtrl	m_listSubCmp;
	CListCtrl	m_listMainCmp;
	CComboBox	m_comboVideoBitrate;
	CComboBox	m_comboVEncType;
	CComboBox	m_comboResolution;
	CComboBox	m_comboPicQuality;
	CComboBox	m_comboFrameRate;
	CComboBox	m_comboFormatType;
	CComboBox	m_comboEncComplexity;
	CComboBox	m_comboCmpType;
	CComboBox	m_comboBPFrame;
	CComboBox	m_comboBitrateType;
	CComboBox	m_comboAEncType;
	DWORD	m_dwChannel;
	DWORD	m_dwIInterval;
	CString	m_csStreamId;
	DWORD	m_dwBitrate;
	BOOL	m_bChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTransCompression)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTransCompression)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnMod();
	afx_msg void OnBtnDelete();
	afx_msg void OnClickListMainCmp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListSubCmp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboCmpType();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnExit();
	afx_msg void OnChkChannel();
	afx_msg void OnBtnPreview();
	afx_msg void OnBtnCopyAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int  m_iDeviceIndex;
	int  m_iCurSelItem;
	NET_DVR_COMPRESSIONCFG_ABILITY m_struCompressionCfgAblity;
	void InsertMainResolution();
	void InsertSubResolution();
	void InsertFrame();
	void InsertBitrateType();
	void InsertBitrate();
	void InsertStreamType();
	void InsertPicQuality();
	void InsertBpFrame();
	void InsertVideoEnc();
	void InsertAudioEnc();
	void InsertVEncComplexity();
	void InsertFormatType();
	void AddDataToList(DWORD dwList, DWORD dwIndex);//dwList = 0添加到主码流表，dwList = 1添加到字码流表, dwList = 2都添加
	void ListToControl(BYTE byList);//byList = 0将主码流表中某行插入到控件，byList = 1将子码流表中某项插入到控件
	void AddStreamInfoToList(LPNET_DVR_STREAM_INFO lpStreamInfo, DWORD dwNum);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRANSCOMPRESSION_H__3961EF99_F1EB_4E5C_9D1C_E1F899D91EB9__INCLUDED_)
