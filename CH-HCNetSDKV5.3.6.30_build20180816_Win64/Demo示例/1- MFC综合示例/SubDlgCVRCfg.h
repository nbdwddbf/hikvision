#if !defined(AFX_SUBDLGCVRCFG_H__C0817596_07EC_4873_9D17_223C286CAAF8__INCLUDED_)
#define AFX_SUBDLGCVRCFG_H__C0817596_07EC_4873_9D17_223C286CAAF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgCVRCfg.h : header file
//
#include "DlgCVR.h"
/////////////////////////////////////////////////////////////////////////////
// CSubDlgCVRCfg dialog

class CSubDlgCVRCfg : public CDialog
{
// Construction
public:
	CSubDlgCVRCfg(CWnd* pParent = NULL);   // standard constructor

    enum
    {   
        SUB_WND_CVR_CFG = 0,
            SUB_WND_STREAM_SRC = 1,
            SUB_WND_STREAM_RECORDSTATUS = 2,
            SUB_WND_STREAM_INFO = 3,
            SUB_WND_STREAM_LOCK = 4            
    };
 

// Dialog Data
	//{{AFX_DATA(CSubDlgCVRCfg)
	enum { IDD = IDD_SUBDLG_PRODUCT_CVR };
	CTabCtrl	m_tabStreamID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgCVRCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgCVRCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnDevCfg();
	afx_msg void OnBtmStreamid();
	afx_msg void OnBtnRecordPassBack();
	afx_msg void OnBtnDevStorage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    void CurCfgUpdate();
public:
//     CDlgStreamSrcCfg				m_dlgStreamSrc;
//     CDlgStreamRecordStatus			m_dlgStreamRecordStatus;
//     CDlgStreamRecordInfo			m_dlgStreamRecordInfo;
//     CDlgStreamManualRecordAndLock	m_dlgStreamManualRecordAndLock;
//     CDlgCVR                         m_dlgCVRCfg;


    LONG m_lUserID;
    int  m_iDevIndex;
    LONG m_lChanNo;
    afx_msg void OnBnClickedButtonRecordPassbackBasicCfg();
    afx_msg void OnBnClickedBtnPreviewByStreamid();
    afx_msg void OnBnClickedBtnResourceIpCfg();
    afx_msg void OnBnClickedBtnDataConfig();
    afx_msg void OnBnClickedBtnRemoteBackupTaskCfg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGCVRCFG_H__C0817596_07EC_4873_9D17_223C286CAAF8__INCLUDED_)
