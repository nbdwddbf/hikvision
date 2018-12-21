#if !defined(AFX_DLGCLOUDUPLOADSTRATEGYCFG_H__9F1B95DD_6146_44BC_856D_8396EA383B4C__INCLUDED_)
#define AFX_DLGCLOUDUPLOADSTRATEGYCFG_H__9F1B95DD_6146_44BC_856D_8396EA383B4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCloudUploadstrategyCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudUploadstrategyCfg dialog

class CDlgCloudUploadstrategyCfg : public CDialog
{
// Construction
public:
	CDlgCloudUploadstrategyCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCloudUploadstrategyCfg)
	enum { IDD = IDD_DLG_CLOUD_UPLOADSTRATEGY_CFG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCloudUploadstrategyCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCloudUploadstrategyCfg)
	afx_msg void OnBtnGetCloudUploadstrategy();
	afx_msg void OnBtnSetCloudStrategy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CComboBox m_comboStrategyType;
    CComboBox m_comboRecordType;
    BOOL m_bAllEvent;
    BOOL m_bMotion;
    BOOL m_bAlarm;
    BOOL m_bVCA;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    NET_DVR_CLOUD_UPLOADSTRATEGY_COND m_struCloudUploadStrategyCond;
    NET_DVR_CLOUD_UPLOADSTRATEGY m_struCloudUploadStrategy;
    NET_DVR_STD_CONFIG m_struStdConfig;
public:
    int m_lUserID;
    int m_lChanNo;
    int m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLOUDUPLOADSTRATEGYCFG_H__9F1B95DD_6146_44BC_856D_8396EA383B4C__INCLUDED_)
