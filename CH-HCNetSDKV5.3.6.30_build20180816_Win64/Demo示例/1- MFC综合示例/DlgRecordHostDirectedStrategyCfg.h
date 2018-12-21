#if !defined(AFX_DLGRECORDHOSTDIRECTEDSTRATEGYCFG_H__29E22E89_CC7E_4B11_9929_6997B9ABC295__INCLUDED_)
#define AFX_DLGRECORDHOSTDIRECTEDSTRATEGYCFG_H__29E22E89_CC7E_4B11_9929_6997B9ABC295__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostDirectedStrategyCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostDirectedStrategyCfg dialog

class CDlgRecordHostDirectedStrategyCfg : public CDialog
{
// Construction
public:
	CDlgRecordHostDirectedStrategyCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordHostDirectedStrategyCfg)
	enum { IDD = IDD_DLG_DIRECTED_STRATEGY_CFG };
		// NOTE: the ClassWizard will add data members here
    CComboBox	m_comStrategy;
    NET_DVR_DIRECTED_STRATEGY_CFG m_struDirectedStrategy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordHostDirectedStrategyCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

    BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(CDlgRecordHostDirectedStrategyCfg)
	afx_msg void OnBtnGet();
    afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lChannel;
    LONG m_lUserID;
    int m_iDeviceIndex;

    char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTDIRECTEDSTRATEGYCFG_H__29E22E89_CC7E_4B11_9929_6997B9ABC295__INCLUDED_)
