#pragma once


// CDlgVideoIntercomRoomCustomCfg 对话框

class CDlgVideoIntercomRoomCustomCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgVideoIntercomRoomCustomCfg)

public:
	CDlgVideoIntercomRoomCustomCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVideoIntercomRoomCustomCfg();
    virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_ROOM_CUSTOM_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonSet();
    afx_msg void OnBnClickedButtonGet();
    afx_msg LRESULT OnMsgSetRoomCustomCfgFinish(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgGetRoomCustomCfgFinish(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgAddRoomCustomCfgTolist(WPARAM wParam, LPARAM lParam);
    LONG m_lServerID;
    LONG m_iDevIndex;
    DWORD m_dwFormerRoomNo;
    DWORD m_dwCustomRoomNo;
    afx_msg void OnBnClickedButtonDel();
    CListCtrl	m_listRoomCustomCfg;
    afx_msg void OnLvnItemchangedListRoomCustomCfg(NMHDR *pNMHDR, LRESULT *pResult);
    BOOL UpdateRoomCustomCfg(NET_DVR_ROOM_CUSTOM_CFG &struRoomCustomCfg);
    void AddToRoomCustomList(const NET_DVR_ROOM_CUSTOM_CFG &struRoomCustomCfg);
    int GetExistItem(const NET_DVR_ROOM_CUSTOM_CFG *lpRoomCustomCfg);
    void UpdateList(int iInsertIndex, const NET_DVR_ROOM_CUSTOM_CFG& struRoomCustomCfg);
    LPDWORD GetRoomCustomCfgPoint();    //获取指向房间自定义配置的指针
    LPDWORD m_lpRoomCustomCfg;  //指向房间自定义配置的指针
    LONG m_lSetRoomCustomCfgHandle;
    LONG m_lGetRoomCustomCfgHandle;
    DWORD m_dwSendIndex;       //下发序号
    BOOL SendFirstRoomCustom();
    BOOL SendNextRoomCustom();
    LPNET_DVR_ROOM_CUSTOM_CFG m_lpNowSendRoomCustom;
    void ProcessSetRoomCustomCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void ProcessGetRoomCustomCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
};
