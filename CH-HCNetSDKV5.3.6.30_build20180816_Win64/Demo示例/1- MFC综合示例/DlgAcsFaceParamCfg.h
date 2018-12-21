#pragma once


// CDlgAcsFaceParamCfg 对话框

class CDlgAcsFaceParamCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgAcsFaceParamCfg)

public:
	CDlgAcsFaceParamCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAcsFaceParamCfg();
    virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_ACS_FACE_PARAM_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    int m_iDevIndex;
    long m_lServerID;
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonStop();
    afx_msg void OnBnClickedButtonSet();
    afx_msg void OnBnClickedButtonGet();
    afx_msg LRESULT OnMsgSetFaceParamCfgFinish(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgGetFaceParamCfgFinish(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgAddFaceParamCfgToList(WPARAM wParam, LPARAM lParam);
    BOOL UpdateFaceParamCfg(NET_DVR_FACE_PARAM_CFG &struFaceParamCfg);
    void AddToFaceParamList(const NET_DVR_FACE_PARAM_CFG& struCardInfo);
    int GetExistItem(const NET_DVR_FACE_PARAM_CFG *lpCardCfg);
    void UpdateList(int iInsertIndex, const NET_DVR_FACE_PARAM_CFG& struFaceParamCfg);

    void AddToList(const NET_DVR_FAILED_FACE_INFO& struFailedFaceInfo);
    LPDWORD GetFaceParamCfgPoint();    //获取指向人脸参数配置的指针
    LPDWORD m_lpRecordCardCfg;  //指向人脸参数配置的指针
    LONG m_lSetFaceParamCfgHandle;
    LONG m_lGetFaceParamCfgHandle;
    DWORD m_dwSendIndex;       //下发序号
    BOOL SendFirstFace();
    BOOL SendNextFace();
    LPNET_DVR_FACE_PARAM_CFG m_lpNowSendFace;
    void ProcessSetFaceParamCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void ProcessGetFaceParamCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void ProcessGetFailedFaceInfoCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    //CWinThread* m_pProcThread;
    //CWinThread* m_pDisplayListThread;
    CComboBox	m_comboDelMode;

    int     m_dwCardReaderNo;
    BOOL	m_byClearAllCard;
    int     m_dwDataType;

    NET_DVR_FACE_PARAM_CTRL m_struDelFaceParam;
    NET_DVR_FACE_PARAM_CFG m_struFaceParamOne;
    NET_DVR_FACE_PARAM_CTRL m_struDelFace;
    CTreeCtrl	m_treeEnableCardReader;
    CTreeCtrl	m_treeReaderStatus;
    CTreeCtrl	m_treeDelFace;
    CListCtrl	m_listFaceParamCfg;
    CString	m_csCardNo;
    CString	m_csFacePath;
    int     m_dwFaceID;
    int     m_dwFaceNum;
    //int m_dwCardNum;
    void CreateTree();
    void GetTreeSel();
    void SetTreeSel(NET_DVR_FACE_PARAM_CFG *struFaceParamCfg);
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnLvnItemchangedListFaceCfg(NMHDR *pNMHDR, LRESULT *pResult);
    CComboBox m_comboFaceDataType;
    afx_msg void OnBnClickedBtnGetFailedFaceInfo();

    BOOL bFailedFaceInfo;
};
