#pragma once


// CDlgJPEGSnatchConfig dialog

class CDlgJPEGSnatchConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgJPEGSnatchConfig)

public:
	CDlgJPEGSnatchConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgJPEGSnatchConfig();

// Dialog Data
public:
	//{{AFX_DATA(CDlgJPEGSnatchConfig)
	enum { IDD = IDD_DLG_JPEG_SNATCH_CONFIG };
	CComboBox m_comboJpegResolution;
	CComboBox m_comboJpegQuality;
	//}}AFX_DATA



	//{{AFX_VIRTUAL(CDlgJPEGSnatchConfig)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgJPEGSnatchConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnJpegConfigExit();
	afx_msg void OnBtnCapture();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	PCHANNEL_INFO m_pChanInfo;
	BOOL GetCompressCfgAbility(DWORD dwIPChanIndex);
	void GetResolutionAbility();
	NET_DVR_COMPRESSIONCFG_ABILITY *m_pCompresscfgAbility;
	int m_iDeviceIndex;
};
