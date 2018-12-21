#pragma once

// CDlgVcaFaceSnapEx 对话框

class CDlgVcaFaceSnapEx : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVcaFaceSnapEx)

public:
	CDlgVcaFaceSnapEx(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVcaFaceSnapEx();

// 对话框数据
	enum { IDD = IDD_DLG_VCA_FACE_SNAP_EX };

    CComboBox	m_cmbChannel;
    CComboBox	m_comROI;
    CComboBox	m_comFaceEnable;
    CComboBox	m_comBackgroundPic;
    CComboBox	m_comboMatchType;
    CComboBox	m_comboSensitive;
    CComboBox	m_comboSnapTimes;
    CComboBox	m_comboRuleNum;
    CComboBox	m_comboPicQuality;
    CComboBox	m_comboPicResolution;
    CComboBox m_comboBox;
    CListCtrl   m_lstFaceSnapEx;
    BOOL	m_bChkFilterActive;
    BOOL	m_bDrawPolygon;
    BOOL	m_bChkEnable;
    BYTE	m_byRate;
    BOOL	m_bSetMiniFilter;
    BOOL	m_bSetMaxFilter;
    BYTE	m_bySnapInterval;
    BYTE	m_bySnapThreshold;
    BYTE	m_byReferBright;
    BYTE	m_byMatchThreshold;
    DWORD	m_dwFaceExposureMinDuration;
    DWORD	m_dwTerminalNo;
    DWORD	m_dwUploadInterval;
    DWORD	m_dwValidFaceMinDuration;
    DWORD   m_dwFaceFilteringTime;
    CRect   m_rcPlayWnd;
    NET_VCA_POLYGON m_struPolyGon;
    BOOL    m_bDrawEnd;
    int     m_nDrawPointNum;
    LONG    m_lPlayHandle;
    CEdit   m_editTextBox;

    void InitListCtrl();
    void DrawRgnFun(HDC hdc);
    BOOL Play(NET_DVR_CLIENTINFO* struClientInfo, LONG loginID, int index);
  
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
    void SaveParam();

	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUserID;
    LONG m_lChannel;
    LONG m_lDeviceIndex;
    CString strStatus;

    int m_iItem;
    int m_iSubItem;
    int m_iLastItem;
    int m_bSelectItem;
    int m_iRowCount;

    LPNET_VCA_FACESNAP_COND m_pStruFaceSnapCond;
    NET_VCA_FACESNAPCFG m_struFaceSnapCfg;
    LPNET_VCA_FACESNAPCFG m_pstruFaceSnapCfg;
    NET_VCA_FACESNAP_COND m_struCond;

    NET_VCA_FACESNAPCFG m_struBatchFaceSnapCfg[64];

    afx_msg void OnBnClickedBtnSetFacesnapEx();
    afx_msg void OnBnClickedBtnGetFacesnap();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnBnClickedCheckSetMiniFilterEx();
    afx_msg void OnBnClickedCheckSetMaxFilterEx();
    afx_msg void OnBnClickedCheckFilterActiveEx();

    
    afx_msg void OnNMClickListFacesnapEx(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMDblclkListFacesnapEx(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnKillfocusEditTextBox();
    afx_msg void OnCbnKillfocusComboBox();
};
