#if !defined(AFX_DLGACSCARDPASSWDPARAM_H__23CEFD79_D32E_46C7_B1F8_274118632C88__INCLUDED_)
#define AFX_DLGACSCARDPASSWDPARAM_H__23CEFD79_D32E_46C7_B1F8_274118632C88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgACCardParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgACCardParam dialog
//#include "ModifyRecord.h"
#define MAX_GROUP_NUM 32
static char *pCardType1[] = { "未知卡", "普通卡", "残疾人卡", "黑名单卡" , "巡更卡", "胁迫卡", "超级卡", "来宾卡"};
enum AddModeEum1{
    SINGEL_ADD1 = 0,
    BATCH_ADD1
    };
class DlgAcsCardPasswdParam : public CDialog
{
// Construction
public:
	DlgAcsCardPasswdParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgACCardParam)
	enum { IDD = IDD_DLG_ACS_CARD_PASSWD };
	CListCtrl	m_lstPlanNo;
	CListCtrl	m_lstBelongGroup;
	CListCtrl	m_lstDoorRight;
	CComboBox	m_cmbDoorRightIndex;
	CComboBox	m_cmbCardPlanIndex;
	CComboBox	m_cmbDoorIndex;
	CComboBox	m_cmbCardType;
	CComboBox	m_cmbCardIndex;
	CComboBox	m_cmbBelongGroup;
	DWORD	m_dwCardNum;
	CString	m_csCardNo;
	CString	m_csCardPasswd;
	BOOL	m_BGBelong;
	BOOL	m_BCardVaildParam;
	BOOL	m_BCardPasswdParam;
	BOOL	m_BCardRightParam;
	BOOL	m_BCardTypeParam;
	BOOL	m_BCardVaild;
	BOOL	m_BDoorRight;
	BOOL	m_BDoorRightParam;
	BOOL	m_BGroupParam;
	BOOL	m_BLeaderCard;
    BOOL	m_BEnablePasswdOpen;
	BOOL	m_BLeaderCardParam;
	BOOL	m_BMaxUseTimeParam;
	BOOL	m_BVaildPeriodEnable;
	BOOL	m_BVaildPeriodParam;
	COleDateTime	m_DTBeginDate;
	COleDateTime	m_DTBeginTime;
	COleDateTime	m_DTEndDate;
	COleDateTime	m_DTEndTime;
	DWORD	m_dwMaxUseTime;
	DWORD	m_dwPlanNo;
	BOOL	m_BSelectAll;
	DWORD	m_dwAddCardNum;
	DWORD	m_dwSwipeTime;
	BOOL	m_BSwipeCard;
	BOOL	m_BCheckCardNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgACCardParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgACCardParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnButGet();
	afx_msg void OnButSet();
	afx_msg void OnButNewItem();
    afx_msg LRESULT OnMsgSetcardCfgFinish(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMsgGetcardCfgFinish(WPARAM wParam,LPARAM lParam);
	afx_msg void OnSelectCardindex();
	afx_msg void OnSelchangeDoorRightIndex();
	afx_msg void OnSelchangeBelongGroup();
	afx_msg void OnSelchangeMaxDoorNum();
	afx_msg void OnSelchangeCardPlanIndex();
	afx_msg void OnOk();
	afx_msg void OnChkSelectAll();
	afx_msg void OnButTestParam();
	afx_msg void OnChkAcccCheckCardno();
	afx_msg void OnClickLstAcccPlanno(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdtAcccCrPlanno();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()




public:
    void ProcSetCardCfgCD(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
	void ProcGetCardCfgCD(DWORD dwType, void* lpBuffer, DWORD dwBufLen);



	LONG m_lServerID;
	LONG m_iDevIndex;

protected:
    void AddCardParamItem(const NET_DVR_CARD_PASSWD_CFG &Item); 
    void AddPointerCardCombox(void *p); 

    LONG m_lSetCardCfgHandle;
	LONG m_lGetCardCfgHandle;
    int  m_iMode;          //模式，0-单个添加 1-批量添加
    BOOL m_BSaveCheckCardNo; 
public:
    void SetCardCfg(const NET_DVR_CARD_PASSWD_CFG& struItem , const char *pCardNo = NULL ); 
    NET_DVR_CARD_PASSWD_CFG GetCardCfg(char *pCardNo = NULL); 
    void UpdateInterface();      //更新界面
    void UpdateInterface(BOOL bRefresh); 
    int  GetAddNum() const; 
    void SetAddMode(int iMode); 

private:
    NET_DVR_CARD_PASSWD_CFG m_struCardCfg; 
    CString m_csSaveCardNo; 
    int m_iLastDoorRightIndex; 
    int m_iLastGroupIndex; 
    int m_iLastPlanIndex; 
    int m_iAddNum; 

    void UpdatePlanList(const BYTE* byCardPlan);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSCARDPASSWDPARAM_H__23CEFD79_D32E_46C7_B1F8_274118632C88__INCLUDED_)
