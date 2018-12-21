#if !defined(AFX_DLGRECORDPUBLISHCFG_H__CDC1E118_CEC6_4BD6_80B0_EF8DDC05F4DE__INCLUDED_)
#define AFX_DLGRECORDPUBLISHCFG_H__CDC1E118_CEC6_4BD6_80B0_EF8DDC05F4DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordPublishCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgRecordPublishCfg dialog

class DlgRecordPublishCfg : public CDialog
{
    // Construction
public:
    DlgRecordPublishCfg(CWnd* pParent = NULL);   // standard constructor
    
    // Dialog Data
    //{{AFX_DATA(DlgRecordPublishCfg)
    enum { IDD = IDD_DLG_PUBLISH_CFG };
    CComboBox	m_comRecordStreamType;
    CComboBox	m_comRecordChan;
    CComboBox	m_comPublishType;
    CComboBox	m_comProtocolType;
    CComboBox	m_comDirectStreamType;
    CComboBox	m_comAddressType;
    CComboBox	m_comDirLevel;
    CComboBox	m_comFirstDirMoe;
    CComboBox	m_comSecordDirMode;
    BOOL	m_bRecordPublish;
    CString	m_sPath;
    CString	m_sPassword;
    UINT	m_nPort;
    CString	m_sUrl;
    CString	m_sUserName;
    CString	m_sIP;
    CString	m_csSecordUserDir;
    CString	m_csFirstUserDir;
    BOOL	m_bRecordMainStream;
    BOOL	m_bRecordStreamThree;
    BOOL	m_bRecordSubStream;
    BYTE    m_byMin;
    BYTE    m_byHour;
    CComboBox    m_cmbTimerMode;
    BOOL    m_bUploadByTime;
    
    //}}AFX_DATA
    
    NET_DVR_PUBLISH_CFG m_struPublishCfg;
    LONG m_lUserID;
    int  m_iDeviceIndex;
    int m_iMirrorNum;
    int m_iStartChannel;
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(DlgRecordPublishCfg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
protected:
    BOOL OnInitDialog();
    // Generated message map functions
    //{{AFX_MSG(DlgRecordPublishCfg)
    afx_msg void OnBtnSet();
    afx_msg void OnBtnGet();
    afx_msg void OnBtnRecordOk();
    afx_msg void OnSelchangeComboRecordChan();
    afx_msg void OnBtnOk();
    afx_msg void OnBtnBrowse();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDPUBLISHCFG_H__CDC1E118_CEC6_4BD6_80B0_EF8DDC05F4DE__INCLUDED_)
