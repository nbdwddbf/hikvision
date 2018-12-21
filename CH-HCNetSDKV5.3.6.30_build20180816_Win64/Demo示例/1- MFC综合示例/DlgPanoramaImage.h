#include "afxwin.h"
#if !defined(AFX_DLGPANORAMAIMAGE_H__0948FF68_25A9_4FDC_9EC9_34AC4EF9CDB9__INCLUDED_)
#define AFX_DLGPANORAMAIMAGE_H__0948FF68_25A9_4FDC_9EC9_34AC4EF9CDB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPanoramaImage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPanoramaImage dialog

class CDlgPanoramaImage : public CDialog
{
// Construction
public:
	CDlgPanoramaImage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPanoramaImage)
	enum { IDD = IDD_DLG_PANORAMAIMAGE };
//	CComboBox	m_comFusionWay;
	CComboBox	m_comFusionMode;
    CComboBox	m_comSensorNo;
    CComboBox	m_comType;
    int m_iAdjustmentRange;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPanoramaImage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPanoramaImage)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
    afx_msg void OnBtnSensorAdjustment();
    afx_msg void OnBtnReset();
    afx_msg void OnBtnSensorInfo();
    
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    NET_DVR_PANORAMAIMAGE m_struPanoramaImage;

    LONG  m_lChannel;
    LONG m_lUserID;
    int m_iDeviceIndex;
    BYTE n_byR;
    BYTE m_byG;
    BYTE m_byB;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    CComboBox m_cmbRgbType;
    BYTE m_byBrightness;
    CComboBox m_cmbPreviewMode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPANORAMAIMAGE_H__0948FF68_25A9_4FDC_9EC9_34AC4EF9CDB9__INCLUDED_)
