#if !defined(AFX_DLGINFODIFFUSIONXMLCFG_H__45B142E9_EB16_40ED_AA71_062E927DEDE2__INCLUDED_)
#define AFX_DLGINFODIFFUSIONXMLCFG_H__45B142E9_EB16_40ED_AA71_062E927DEDE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionXmlCfg.h : header file
//

#define MAX_LEN_XML 10*1024*1024 //XML最大长度

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionXmlCfg dialog

class CDlgInfoDiffusionXmlCfg : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionXmlCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionXmlCfg)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_XML_CFG };
	CComboBox	m_cmbOperateType;
	CString	m_szCommandStr;
	CString	m_szInputParam;
	CString	m_szOutputParam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionXmlCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionXmlCfg)
	afx_msg void OnBtnExit();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;

	char m_szCommandBuf[512];
	char* m_lpOutputXml;
public:
    BOOL m_binputFileData;
    CString m_strFilePath;
    afx_msg void OnBnClickedBtnSelectFile();
    HANDLE  m_hFile;
    LONG m_iFileSize;
    DWORD m_dwRecvTimeOut;
    BOOL m_bChanConvert;
    afx_msg void OnBnClickedButtonTestMime();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONSERVERXML_H__45B142E9_EB16_40ED_AA71_062E927DEDE2__INCLUDED_)
