#if !defined(AFX_DLGVIDEOINTERCOMNOTICEDATACFG_H__B498B713_9AB8_4DB2_B6CD_A5AA8790D14D__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMNOTICEDATACFG_H__B498B713_9AB8_4DB2_B6CD_A5AA8790D14D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomNoticeDataCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomNoticeDataCfg dialog

class CDlgVideoIntercomNoticeDataCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomNoticeDataCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomNoticeDataCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_NOTICE_DATA_CFG };
	CDateTimeCtrl	m_ctrlNoticeDataTime;
	CComboBox	m_comboNoticeLevel;
	CString	m_strNoticeDetail;
	CString	m_strNoticeNumber;
	CString	m_strNoticeTheme;
	COleDateTime	m_dtNoticeTime;
	CString	m_strPicPath[MAX_NOTICE_PIC_NUM];
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomNoticeDataCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomNoticeDataCfg)
	afx_msg void OnBtnSelPic1();
	afx_msg void OnBtnSelPic2();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSelPic3();
	afx_msg void OnBtnSelPic4();
	afx_msg void OnBtnSelPic5();
	afx_msg void OnBtnSelPic6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void GetParamFromWnd(NET_DVR_NOTICE_DATA* pNoticeData);
	BOOL SetNoticeData();
public:
	LONG m_lServerID;
	LONG m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMNOTICEDATACFG_H__B498B713_9AB8_4DB2_B6CD_A5AA8790D14D__INCLUDED_)
