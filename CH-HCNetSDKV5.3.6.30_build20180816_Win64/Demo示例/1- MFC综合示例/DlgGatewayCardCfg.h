#if !defined(AFX_DLGGATEWAYCARDCFG_H__C5C5ED64_1D7C_402D_B70B_6DED16CE8609__INCLUDED_)
#define AFX_DLGGATEWAYCARDCFG_H__C5C5ED64_1D7C_402D_B70B_6DED16CE8609__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DlgGatewayCardInfo.h"
#include "cjson/cJSON.h"
// DlgGatewayCardCfg.h : header file
//

#define MAX_RESEND_CARD_TIME 5

/////////////////////////////////////////////////////////////////////////////
// CDlgGatewayCardCfg dialog

class CDlgGatewayCardCfg : public CDialog
{
// Construction
public:
	CDlgGatewayCardCfg(CWnd* pParent = NULL);   // standard constructor
	~CDlgGatewayCardCfg();

// Dialog Data
	//{{AFX_DATA(CDlgGatewayCardCfg)
	enum { IDD = IDD_DLG_GATEWAY_CARD };
	CListCtrl	m_listBelongGroup;
	CListCtrl	m_listCardRightPlan;
	CListCtrl	m_listDoorRight;
	CListCtrl	m_listCard;
	BOOL	m_BcheckCardNo;
	CString	m_csBatchFlag;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGatewayCardCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGatewayCardCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAddToList();
	afx_msg void OnDeleteitemListCard(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnModifyToList();
	afx_msg void OnDblclkListCard(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnDelCard();
	afx_msg void OnBtnSetCardcfg();
	afx_msg void OnBtnGetAllCard();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnMsgSetcardCfgFinish(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMsgGetcardCfgFinish(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnMsgAddCardCfgToList(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnMsgCardParamSyncFinish(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgUpdateData(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBtnClearAllCard();
	afx_msg void OnClickListCardCfg(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButSimulationAdd();
	afx_msg void OnBtnGetSel();
	afx_msg void OnBtnSetSel();
	afx_msg void OnButBatchAdd();
	afx_msg void OnBtnStopSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void InitCtrlState();
	void AddToCardList(const NET_DVR_CARD_CFG_V50& struCardInfo , const char * pCardNo);
    void ModifyToCardList(int nItemIndex, const NET_DVR_CARD_CFG_V50& struCardInfo);
public:
	void ProcessSetCardCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
	void ProcessGetCardCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    void ProcessCardParamSyncCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
	void SendCardData();
    void SendCardData(LPNET_DVR_CARD_CFG_V50 lpCardCfg, DWORD dtest = 0);  //dtest 内部测试用 
	void SetCardCfgState(CString strCardNumber,BOOL bSucc,CString strUserDefineState = "");

protected:
	BOOL    StartProcThread();
	BOOL    StopProcThread();
    BOOL    m_BSendSel; 
    LPNET_DVR_CARD_CFG_V50 m_lpSelSendCardCfg;
public:
	LONG m_lServerID;
	LONG m_iDevIndex;
	LONG m_lSetCardCfgHandle;
	LONG m_lGetCardCfgHandle;
	CWinThread* m_pProcThread; 
	HANDLE m_hStopProcEvent;
    LONG m_lCardParamSyncHandle;
public:
    void UpdateList(int iInsertIndex, const char * pCardNo, const NET_DVR_CARD_CFG_V50& struCardInfo);
    void UpdateSubList(const NET_DVR_CARD_CFG_V50 *lpCardCfg);
    LPNET_DVR_CARD_CFG_V50 GetSelItem(char *lpCardNo = NULL);
    int GetExistItem(const NET_DVR_CARD_CFG_V50 *lpCardCfg);
    void ClearList(); 

private:
    //类辅助记录变量
    DWORD m_dwNowSendItem; 
    BYTE  m_byListSendStatus; 
    int   m_iSelListItem; 

protected:
    void ShowSelListItem(); 

//10万张
protected:
    LPDWORD m_lpRecordCardCfg; 
    CWinThread* m_pDisplayListThread; 
    DWORD m_dwBatchAddNum;    //添加卡号码

    LPDWORD GetCardCfgPoint();    //获取指向卡参数的指针
    void CreateSameCfgCard(DWORD dwNum, const NET_DVR_CARD_CFG_V50 &lpCardCfg); //建立具有相同参数的卡，卡号不一样

//上层维护同步修改
protected:
	BOOL SendFirstCard();      //发送第一张卡
	BOOL ReSendLastCard();     //重发卡
	BOOL SendNextCard();       //发送下一张卡
	DWORD m_dwCardNum;         //下发卡数
	DWORD m_dwSendIndex;       //下发序号	
    LPNET_DVR_CARD_CFG_V50 m_lpNowSendCard;
	BYTE m_byLastCardSendTime;   //重发次数
public:
    void BatchAddCardToList();
    int m_iLocalControllerNo;
    afx_msg void OnBnClickedBtnCardParamSync();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGATEWAYCARDCFG_H__C5C5ED64_1D7C_402D_B70B_6DED16CE8609__INCLUDED_)
