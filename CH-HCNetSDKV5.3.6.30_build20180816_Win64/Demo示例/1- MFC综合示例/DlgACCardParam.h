#include "afxwin.h"
#if !defined(AFX_DLGACCARDPARAM_H__2EA20DAE_9C6C_4C37_8785_3FFAD4D6C882__INCLUDED_)
#define AFX_DLGACCARDPARAM_H__2EA20DAE_9C6C_4C37_8785_3FFAD4D6C882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgACCardParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgACCardParam dialog
//#include "ModifyRecord.h"
#define MAX_GROUP_NUM 32
#ifdef DEMO_LAN_CN
static char *pCardType[] = { "未知卡", "普通卡", "残疾人卡", "黑名单卡", "巡更卡", "胁迫卡", "超级卡", "来宾卡", "解除卡" , "员工卡", "应急卡", "应急管理卡"};
#else
static char *pCardType[] = { "unknow", "normalcard", "disabledcard", "blacklistcard", "nightwatchcard", "stresscard", "supercard", "guestcard", "removecard", "employeecard", "emergencycard", "emergencymanagementcard"};
#endif
enum AddModeEum{
    SINGEL_ADD = 0,
    BATCH_ADD
    };
class CDlgACCardParam : public CDialog
{
// Construction
public:
	CDlgACCardParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgACCardParam)
	enum { IDD = IDD_DLG_ACCC };
	CListCtrl	m_lstPlanNo;
	CListCtrl	m_lstBelongGroup;
	CListCtrl	m_lstDoorRight;
	CComboBox	m_cmbDoorRightIndex;
	CComboBox	m_cmbCardPlanIndex;
	CComboBox	m_cmbDoorIndex;
	CComboBox	m_cmbCardType;
    CComboBox	m_cmbRightType;
	CComboBox	m_cmbCardIndex;
	CComboBox	m_cmbBelongGroup;
	DWORD	m_dwCardNum;
	CString	m_csCardNo;
	CString	m_csCardPasswd;
	BOOL	m_BGBelong;
	BOOL	m_BCardVaildParam;
	BOOL	m_BCardPasswdParam;
	BOOL	m_BCardRightParam;
    BOOL    m_BEmployeeNo;
    BOOL    m_BName;
    BOOL    m_BDepartmentNo;
    BOOL    m_BSchedulePlanNo;
    BOOL    m_BSchedulePlanType;
	BOOL	m_BCardTypeParam;
	BOOL	m_BCardVaild;
	BOOL	m_BDoorRight;
	BOOL	m_BDoorRightParam;
	BOOL	m_BGroupParam;
	BOOL	m_BLeaderCard;
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
    DWORD	m_wRoomNumber;
    int	m_wFloorNumber;
    DWORD   m_dwEmployeeNo;
    CString m_csName;
    DWORD   m_wDepartmentNo;
    DWORD   m_wSchedulePlanNo;
    CComboBox  m_cmbRight;
    CComboBox  m_cmbSchedulePlanType;
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
    void AddCardParamItem(const NET_DVR_CARD_CFG_V50 &Item); 
    void AddPointerCardCombox(void *p); 

    LONG m_lSetCardCfgHandle;
	LONG m_lGetCardCfgHandle;
    int  m_iMode;          //模式，0-单个添加 1-批量添加
    BOOL m_BSaveCheckCardNo; 
public:
    void SetCardCfg(const NET_DVR_CARD_CFG_V50& struItem, const char *pCardNo = NULL);
    NET_DVR_CARD_CFG_V50 GetCardCfg(char *pCardNo = NULL);
    void UpdateInterface();      //更新界面
    void UpdateInterface(BOOL bRefresh); 
    int  GetAddNum() const; 
    void SetAddMode(int iMode); 

private:
    NET_DVR_CARD_CFG_V50 m_struCardCfg;
    CString m_csSaveCardNo; 
    int m_iLastDoorRightIndex; 
    int m_iLastGroupIndex; 
    int m_iLastPlanIndex; 
    int m_iAddNum; 

    void UpdatePlanList(const WORD* wCardPlan);
public:
    BOOL m_bRoomNo;
    BOOL m_bSIMNo;
    CString m_csSimNo;
    CComboBox m_cmbUserType;
    BOOL m_bUserType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACCARDPARAM_H__2EA20DAE_9C6C_4C37_8785_3FFAD4D6C882__INCLUDED_)
