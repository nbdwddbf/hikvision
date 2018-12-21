#if !defined(AFX_DLGRECORDHOSTFRAMECFG_H__12840AE5_FD6C_4D66_808C_09D8D4AE1C3C__INCLUDED_)
#define AFX_DLGRECORDHOSTFRAMECFG_H__12840AE5_FD6C_4D66_808C_09D8D4AE1C3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordHostFrameCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostFrameCfg dialog

class CDlgRecordHostFrameCfg : public CDialog
{
// Construction
public:
	CDlgRecordHostFrameCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecordHostFrameCfg)
	enum { IDD = IDD_DLG_RECORD_HOST_FRAME_CFG };
		// NOTE: the ClassWizard will add data members here
    CComboBox	m_comFrameEnable;
    CComboBox	m_comTopWidth;
    CComboBox	m_comBottomWidth;
    CComboBox	m_comLeftWidth;
    CComboBox	m_comRightWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecordHostFrameCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

    DWORD m_dwPicNo;

    BYTE m_byFrameEnable;

    BYTE m_byTopWidth;
    BYTE m_byTopR;
    BYTE m_byTopG;
    BYTE m_byTopB;

    BYTE m_byBottomWidth;
    BYTE m_byBottomR;
    BYTE m_byBottomG;
    BYTE m_byBottomB;

    BYTE m_byLeftWidth;
    BYTE m_byLeftR;
    BYTE m_byLeftG;
    BYTE m_byLeftB;

    BYTE m_byRightWidth;
    BYTE m_byRightR;
    BYTE m_byRightG;
    BYTE m_byRightB;

    NET_DVR_FRAME_CFG m_struFrameCfg;

	// Generated message map functions
	//{{AFX_MSG(CDlgRecordHostFrameCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;

    char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDHOSTFRAMECFG_H__12840AE5_FD6C_4D66_808C_09D8D4AE1C3C__INCLUDED_)
