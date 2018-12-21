// DlgGatewayCardCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsCardPasswdCfg.h"
#include "DlgAcsCardPasswdParam.h"
#include "DlgACCardParam.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAcsCardPasswdCfg dialog

void CALLBACK g_fSetGatewayCardCallback1(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
void CALLBACK g_fGetGatewayCardCallback1(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
UINT __cdecl  g_fSendCardCfgThread1(LPVOID pParam);
UINT __cdecl  g_fShowCardListThread1(LPVOID pParam);
#define WM_MSG_SETCARD_FINISH 1002
#define WM_MSG_GETCARD_FINISH 1003
#define WM_MSG_ADD_CARDCFG_TOLIST 1004
#define WM_MSG_UPDATEDATA_INTERFACE   1005






DlgAcsCardPasswdCfg::DlgAcsCardPasswdCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAcsCardPasswdCfg::IDD, pParent)
    , m_dwNowSendItem(0)
    , m_iSelListItem(-1)
    , m_lpRecordCardCfg(NULL)
    ,m_pDisplayListThread(NULL)
    ,m_dwBatchAddNum(0)
	,m_lpNowSendCard(NULL)
	,m_byLastCardSendTime(0)
{
	//{{AFX_DATA_INIT(DlgAcsCardPasswdCfg)
	m_BcheckCardNo = FALSE;
	m_csBatchFlag = _T("Ready to Add");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iDevIndex = -1;
	m_lSetCardCfgHandle = -1;
	m_lGetCardCfgHandle = -1;
	m_hStopProcEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_pProcThread = NULL;
    m_BSendSel = FALSE; 
    m_lpSelSendCardCfg = NULL; 
}

DlgAcsCardPasswdCfg::~DlgAcsCardPasswdCfg()
{
	CloseHandle(m_hStopProcEvent);

	if (m_pProcThread != NULL && !m_pProcThread->m_bAutoDelete)
	{
		delete m_pProcThread;
	}

	if ( m_lpRecordCardCfg )
    {
		LPDWORD lpArr = m_lpRecordCardCfg;
//         for (int i=0; i<m_dwCardNum; i++)
//         {
//             delete (LPNET_DVR_CARD_PASSWD_CFG)lpArr[i]; 
//         }
        delete [] m_lpRecordCardCfg; 
    }
}

void DlgAcsCardPasswdCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAcsCardPasswdCfg)
	DDX_Control(pDX, IDC_LIST_BELONGGROUP, m_listBelongGroup);
	DDX_Control(pDX, IDC_LIST_CARDRIGHTPLAN, m_listCardRightPlan);
	DDX_Control(pDX, IDC_LIST_DOORRIGHT, m_listDoorRight);
	DDX_Control(pDX, IDC_LIST_CARD, m_listCard);
	DDX_Check(pDX, IDC_CHK_ACGC_CHECKCARDNO, m_BcheckCardNo);
	DDX_Text(pDX, IDC_STATIC_BATCH_ADD_FLAG, m_csBatchFlag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAcsCardPasswdCfg, CDialog)
	//{{AFX_MSG_MAP(DlgAcsCardPasswdCfg)
	ON_BN_CLICKED(IDC_BTN_ADD_TO_LIST, OnBtnAddToList)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_CARD, OnDeleteitemListCard)
	ON_BN_CLICKED(IDC_BTN_MODIFY_TO_LIST, OnBtnModifyToList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CARD, OnDblclkListCard)
	ON_BN_CLICKED(IDC_BTN_DEL_CARD, OnBtnDelCard)
	ON_BN_CLICKED(IDC_BTN_SET_CARDCFG, OnBtnSetCardcfg)
	ON_BN_CLICKED(IDC_BTN_GET_ALL_CARD, OnBtnGetAllCard)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_MSG_SETCARD_FINISH,OnMsgSetcardCfgFinish)
	ON_MESSAGE(WM_MSG_GETCARD_FINISH,OnMsgGetcardCfgFinish)
    ON_MESSAGE(WM_MSG_ADD_CARDCFG_TOLIST,OnMsgAddCardCfgToList)
    ON_MESSAGE(WM_MSG_UPDATEDATA_INTERFACE,OnMsgUpdateData)
	ON_BN_CLICKED(IDC_BTN_CLEAR_ALL_CARD, OnBtnClearAllCard)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CARD, OnClickListCardCfg)
	ON_BN_CLICKED(IDC_BUT_SIMULATION_ADD, OnButSimulationAdd)
	ON_BN_CLICKED(IDC_BTN_GET_SELECT, OnBtnGetSel)
	ON_BN_CLICKED(IDC_BTN_SET_SELECT, OnBtnSetSel)
	ON_BN_CLICKED(IDC_BUT_BATCH_ADD, OnButBatchAdd)
	ON_BN_CLICKED(IDC_BTN_STOP_SEND, OnBtnStopSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAcsCardPasswdCfg message handlers

BOOL DlgAcsCardPasswdCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitCtrlState();

	return TRUE; 
}

void DlgAcsCardPasswdCfg::OnClose()
{
	static BOOL bNotifyQuit = FALSE;
	if ((m_pProcThread   != NULL &&  WaitForSingleObject(m_pProcThread->m_hThread,0) != WAIT_OBJECT_0))
	{  
		if (!bNotifyQuit)
		{
			SetEvent(m_hStopProcEvent);
			if (m_pProcThread != NULL)
			{
				m_pProcThread->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
			}
			
			PostMessage(WM_CLOSE);
			bNotifyQuit = TRUE;
		}
		PostMessage(WM_CLOSE);
		return;
	}

	bNotifyQuit = FALSE;
	CDialog::OnClose();
}

void DlgAcsCardPasswdCfg::OnDestroy()
{
	StopProcThread();
	CDialog::OnDestroy();
}

LRESULT DlgAcsCardPasswdCfg::OnMsgSetcardCfgFinish(WPARAM wParam,LPARAM lParam)
{   
	NET_DVR_StopRemoteConfig(m_lSetCardCfgHandle);
	m_lSetCardCfgHandle = -1;
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CARD_PASSWD_CFG Set finish");
    ShowSelListItem(); 
	return 0;
}

LRESULT DlgAcsCardPasswdCfg::OnMsgGetcardCfgFinish(WPARAM wParam,LPARAM lParam)
{
	NET_DVR_StopRemoteConfig(m_lGetCardCfgHandle);
	m_lGetCardCfgHandle = -1;
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CARD_PASSWD_CFG Get finish");
    ShowSelListItem(); 
	return 0;
}

LRESULT DlgAcsCardPasswdCfg::OnMsgAddCardCfgToList(WPARAM wParam,LPARAM lParam)
{
    char *pCardNo; 
    LPNET_DVR_CARD_PASSWD_CFG lpCardCfg = (LPNET_DVR_CARD_PASSWD_CFG)wParam; 
    if ( lpCardCfg->dwSize == 0)
    {
        return 0; 
    }
    pCardNo = (char *)lpCardCfg->byCardNo; 
    AddToCardList(*lpCardCfg, pCardNo); 
    delete lpCardCfg; 
    return 0; 
}

LRESULT DlgAcsCardPasswdCfg::OnMsgUpdateData(WPARAM wParam,LPARAM lParam)
{
    DWORD dwTrue = (DWORD)wParam; 
    UpdateData(dwTrue); 
    return 0; 
}


void DlgAcsCardPasswdCfg::InitCtrlState()
{
    int iIndex = 0;
	char szLan[64] = {0};

	g_StringLanType(szLan, "编号", "No.");
	m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,60);
	g_StringLanType(szLan, "卡号", "CardNo");
	m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,100); //1
	g_StringLanType(szLan, "卡有效", "Card Valid");
    m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,60);
	g_StringLanType(szLan, "卡密码", "Card Password");
    m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,60);
	g_StringLanType(szLan, "卡类型", "Card Type");
    m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,60);
	
	g_StringLanType(szLan, "首卡", "First Card");
    m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,60); //5
	g_StringLanType(szLan, "最大刷卡", "Maximum Card");
    m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,80);
	g_StringLanType(szLan, "已刷卡", "Swiped");
    m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,80);
	g_StringLanType(szLan, "卡有效期使能", "Card Valid Enabled");
    m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,100);  //8 
	g_StringLanType(szLan, "卡有效开始时间", "Card Valid Start Time");
    m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,150); 
	g_StringLanType(szLan, "卡有效结束时间", "Card Valid End Time");
    m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,150);
	g_StringLanType(szLan, "发送状态", "Send Status");
    m_listCard.InsertColumn( iIndex++,szLan,LVCFMT_LEFT,150);
    m_byListSendStatus = iIndex - 1 ; 
	m_listCard.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	g_StringLanType(szLan, "门编号", "DoorNo");
    m_listDoorRight.InsertColumn(0, szLan, LVCFMT_LEFT,60);
	g_StringLanType(szLan, "有权限", "Permission");
    m_listDoorRight.InsertColumn(1, szLan, LVCFMT_LEFT,60);
    m_listDoorRight.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	g_StringLanType(szLan, "群组号", "Group No");
    m_listBelongGroup.InsertColumn(0, szLan, LVCFMT_LEFT,60);
	g_StringLanType(szLan, "属于", "Belong");
    m_listBelongGroup.InsertColumn(1, szLan, LVCFMT_LEFT,60);
    m_listBelongGroup.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	g_StringLanType(szLan, "门下标", "Door Subscript");
    m_listCardRightPlan.InsertColumn(0, szLan, LVCFMT_LEFT,55);
	g_StringLanType(szLan, "卡权限下标", "Card Privileges Subscript");
    m_listCardRightPlan.InsertColumn(1, szLan, LVCFMT_LEFT,70);
	g_StringLanType(szLan, "计划模板编号", "Plan Template No.");
    m_listCardRightPlan.InsertColumn(2, szLan, LVCFMT_LEFT,150);
    m_listCardRightPlan.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}

void DlgAcsCardPasswdCfg::OnBtnAddToList() 
{
//	CDlgGatewayCardInfo dlg;
    DlgAcsCardPasswdParam  dlg; 
    NET_DVR_CARD_PASSWD_CFG struCardCfg = {0};
    dlg.SetCardCfg(struCardCfg);     
	if (dlg.DoModal() == IDOK)
	{
        char szCardNo[ACS_CARD_NO_LEN]; 
		struCardCfg = dlg.GetCardCfg(szCardNo);
		AddToCardList(struCardCfg, szCardNo);
        UpdateSubList(&struCardCfg);
	}
}

void DlgAcsCardPasswdCfg::OnDeleteitemListCard(NMHDR* pNMHDR, LRESULT* pResult) 
{
// 	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
// 	GATEWAY_CARD_INFO* pCardInfo = (GATEWAY_CARD_INFO*)pNMListView->lParam;
// 	if (pCardInfo != NULL)
// 	{
// 		delete pCardInfo;
// 	}	
// 	*pResult = 0;
}


int DlgAcsCardPasswdCfg::GetExistItem(const NET_DVR_CARD_PASSWD_CFG *lpCardCfg)
{
    int nItemCount = m_listCard.GetItemCount();
    int i = 0; 
    LPNET_DVR_CARD_PASSWD_CFG lpTemp = NULL; 
    for (i=0; i<nItemCount; i++)
    {
        lpTemp = (LPNET_DVR_CARD_PASSWD_CFG)  m_listCard.GetItemData(i);
        if ( ! lpCardCfg )
        {
            continue; 
        }
        if ( strcmp((char *)lpCardCfg->byCardNo, (char *)lpTemp->byCardNo) == 0)
        {
            return i; 
        }
    }
    return -1; 
} 


void DlgAcsCardPasswdCfg::AddToCardList(const NET_DVR_CARD_PASSWD_CFG& struCardInfo, const char * pCardNo)
{
    LPNET_DVR_CARD_PASSWD_CFG pCardInfo = NULL; 
    int iItemIndex   = GetExistItem(&struCardInfo); 
    if ( iItemIndex == -1)
    {
        pCardInfo = new NET_DVR_CARD_PASSWD_CFG;        
        int iSize = sizeof(NET_DVR_CARD_PASSWD_CFG);
        int nItemCount = m_listCard.GetItemCount();
    
        CString strItem = "";
        strItem.Format("%d",nItemCount + 1);
        iItemIndex = m_listCard.InsertItem(nItemCount,strItem);
	    m_listCard.SetItemData(nItemCount,(DWORD)pCardInfo);
    }
    else
    {
        pCardInfo = (LPNET_DVR_CARD_PASSWD_CFG)m_listCard.GetItemData(iItemIndex); 
    }
    memcpy(pCardInfo,&struCardInfo,sizeof(struCardInfo));
    UpdateList(iItemIndex, pCardNo, *pCardInfo); 
    LPDWORD lpArr = GetCardCfgPoint();    
    lpArr[iItemIndex] = (DWORD)pCardInfo; 

}

void DlgAcsCardPasswdCfg::ModifyToCardList(int nItemIndex, const NET_DVR_CARD_PASSWD_CFG& struCardInfo)
{
//    UpdateList(nItemIndex, struCardInfo); 
}





void DlgAcsCardPasswdCfg::OnBtnModifyToList() 
{
	int nSelIndex = m_listCard.GetNextItem(-1,LVNI_SELECTED);
	if (nSelIndex == -1)
	{
		return;
	}

	NET_DVR_CARD_PASSWD_CFG* pCardInfo = (NET_DVR_CARD_PASSWD_CFG*)m_listCard.GetItemData(nSelIndex);
	if (pCardInfo == NULL)
	{
		return;
	}
    CString csCardNo; 
    csCardNo = m_listCard.GetItemText(nSelIndex, 1); //卡编号 
    char szCardNo[ACS_CARD_NO_LEN]; 
    strncpy(szCardNo, (LPCTSTR)csCardNo, sizeof(szCardNo));
	DlgAcsCardPasswdParam dlg;
	dlg.SetCardCfg(*pCardInfo, szCardNo);
	if (dlg.DoModal() == IDOK)
    {
		*pCardInfo = dlg.GetCardCfg (szCardNo);
        UpdateList(nSelIndex, szCardNo, *pCardInfo); 
        UpdateSubList(pCardInfo);
	}
}

void DlgAcsCardPasswdCfg::OnDblclkListCard(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnBtnModifyToList();
	*pResult = 0;
}

void DlgAcsCardPasswdCfg::OnBtnDelCard() 
{
	// TODO: Add your control notification handler code here
	
}



void DlgAcsCardPasswdCfg::OnBtnSetCardcfg() 
{
	if (m_lSetCardCfgHandle != -1)
	{
		NET_DVR_StopRemoteConfig(m_lSetCardCfgHandle);
	}
    UpdateData(TRUE);
    m_dwCardNum = m_listCard.GetItemCount();
	NET_DVR_CARD_CFG_COND struCond = {0};
	struCond.dwSize  = sizeof(struCond);
	struCond.dwCardNum = m_dwCardNum;
    struCond.byCheckCardNo = (BYTE)m_BcheckCardNo; 
	m_lSetCardCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_SET_CARD_PASSWD_CFG,&struCond,sizeof(struCond),g_fSetGatewayCardCallback1,this);
	if (m_lSetCardCfgHandle == -1)
	{
    	g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CARD_PASSWD_CFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CARD_PASSWD_CFG");
	}
//	StartProcThread();
	//发送第一张卡, 失败关闭连接
	if ( !SendFirstCard())
	{
		NET_DVR_StopRemoteConfig(m_lSetCardCfgHandle);
		m_lSetCardCfgHandle = -1;
	}
	
}


void DlgAcsCardPasswdCfg::OnBtnGetAllCard() 
{
	if (m_lSetCardCfgHandle != -1)
	{
		NET_DVR_StopRemoteConfig(m_lSetCardCfgHandle);
	}
    //清除所有卡项
//    ClearList(); 
    m_listCard.DeleteAllItems(); 
    UpdateData(TRUE); 
	NET_DVR_CARD_CFG_COND struCond = {0};
	struCond.dwSize  = sizeof(struCond);
	struCond.dwCardNum = 0xffffffff;
	struCond.byCheckCardNo = (BYTE)m_BcheckCardNo; 

	m_lGetCardCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_GET_CARD_PASSWD_CFG,&struCond,sizeof(struCond),g_fGetGatewayCardCallback1,this);
	if (m_lGetCardCfgHandle == -1)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CARD_PASSWD_CFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CARD_PASSWD_CFG");
	}
}

void DlgAcsCardPasswdCfg::SendCardData(LPNET_DVR_CARD_PASSWD_CFG lpCardCfg, DWORD dwDiffTime)
{
    if ( m_lSetCardCfgHandle == -1)
    {
        return; 
    }
    LPNET_DVR_CARD_PASSWD_CFG lpCardCfg1  = GetSelItem();
    if (!NET_DVR_SendRemoteConfig(m_lSetCardCfgHandle,3/*ENUM_ACS_SEND_DATA*/, (char *)lpCardCfg ,sizeof(*lpCardCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Send Fail,CardNO: %s", m_lpNowSendCard->byCardNo);    
        //发送失败  关闭连接
        PostMessage(WM_MSG_SETCARD_FINISH,0,0);
        return ; 
    }
	return ; 
}

void DlgAcsCardPasswdCfg::SendCardData()
{   
	if (m_lSetCardCfgHandle == -1)
	{
		return;
	}
    LPNET_DVR_CARD_PASSWD_CFG lpCardCfg = NULL; 
    if ( m_BSendSel )
    {
//         lpCardCfg = GetSelItem();
        SendCardData( m_lpSelSendCardCfg ); 
        m_BSendSel = FALSE; 
        m_lpSelSendCardCfg = NULL; 
        return; 
    }
	int nItemCount = m_listCard.GetItemCount();
	LPDWORD lpArr = GetCardCfgPoint();
	DWORD beforeWait = 0;  
	DWORD afterWait = 0;
	for (int i = 0; i < nItemCount; i++)
	{
	
//        lpCardCfg = (LPNET_DVR_CARD_CFG) m_listCard.GetItemData(i);
		lpCardCfg = (LPNET_DVR_CARD_PASSWD_CFG)lpArr[i]; 
        if ( ! lpCardCfg )
        {
            continue; 
        }
//		beforeWait = GetTickCount(); 
        if ( i%10 == 9 && WaitForSingleObject(m_hStopProcEvent,0) == WAIT_OBJECT_0)
        {
            break;
		}
//		afterWait = GetTickCount(); 
        m_dwNowSendItem = i; 
        SendCardData(lpCardCfg, afterWait-beforeWait); 
	}
}

void DlgAcsCardPasswdCfg::ProcessSetCardCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{   
	CString strItem = "";
	if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
	{
        DWORD dwStatus = *(DWORD*)lpBuffer;
        
        
        if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {   
            char szCardNumber[ACS_CARD_NO_LEN + 1] = "\0";
            strncpy(szCardNumber,(char*)(lpBuffer) + 4,ACS_CARD_NO_LEN);
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "SetCard PROCESSING %s", szCardNumber);
            //SetCardCfgState(szCardNumber,TRUE);
            SendNextCard(); 
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            char szCardNumber[ACS_CARD_NO_LEN + 1] = "\0";
            DWORD dwErrCode = *((DWORD*)lpBuffer + 1);
            strncpy(szCardNumber,(char*)(lpBuffer) + 8,ACS_CARD_NO_LEN);
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "SetCard Err:%d,CardNo:%s", dwErrCode,  szCardNumber);
            if (ReSendLastCard())
            {
                return ; 
            }
            SendNextCard(); 
        }
        //下面两个关闭长连接
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "SetCard SUCCESS");
            PostMessage(WM_MSG_SETCARD_FINISH,0,0);
            
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            PostMessage(WM_MSG_SETCARD_FINISH,0,0);
	    }
	}
    else if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_CARD_PASSWD_STATUS struCfg = {0};
        memcpy(&struCfg, lpBuffer, sizeof(struCfg));
        if (struCfg.dwErrorCode == 0)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "SetCard PROCESSING %s", struCfg.byCardNo);
            SendNextCard();
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "SetCard Err:%d,CardNo:%s", struCfg.dwErrorCode,  struCfg.byCardNo);
            SendNextCard();
        }
    }
}

void DlgAcsCardPasswdCfg::ProcessGetCardCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{   
	CString strItem = "";
	if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
	{
        LPNET_DVR_CARD_PASSWD_CFG lpCardCfg =  new NET_DVR_CARD_PASSWD_CFG; 
        memcpy(lpCardCfg, lpBuffer, sizeof(*lpCardCfg)); 
        if (lpCardCfg->dwErrorCode == 0)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "GetCard PROCESSING %s", lpCardCfg->byCardNo);
            PostMessage(WM_MSG_ADD_CARDCFG_TOLIST, (WPARAM)lpCardCfg,0);
        } 
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GetCard STATUS_FAILED, Error code %d, Card Number %s", lpCardCfg->dwErrorCode,  lpCardCfg->byCardNo);
        }
		
	}
	else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
	{
		DWORD dwStatus = *(DWORD*)lpBuffer;
		if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
		{
			PostMessage(WM_MSG_GETCARD_FINISH,0,0);
		}
		else if ( dwStatus == NET_SDK_CALLBACK_STATUS_FAILED )
		{
			char szCardNumber[ACS_CARD_NO_LEN + 1] = "\0";
			DWORD dwErrCode = *(DWORD*)((char *)lpBuffer + 4); 
			strncpy(szCardNumber,(char*)(lpBuffer) + 8,ACS_CARD_NO_LEN);
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GetCard STATUS_FAILED, Error code %d, Card Number %s", dwErrCode,  szCardNumber);
		}
	}
}

BOOL DlgAcsCardPasswdCfg::StartProcThread()
{
	if (m_pProcThread != NULL)
	{
		StopProcThread();
	}
	m_pProcThread = AfxBeginThread(g_fSendCardCfgThread1,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED,NULL);
	if (m_pProcThread != NULL)
	{
		m_pProcThread->m_bAutoDelete = FALSE;
		m_pProcThread->ResumeThread();
	}
	BOOL bResult =  m_pProcThread != NULL;
	return bResult;
}

BOOL DlgAcsCardPasswdCfg::StopProcThread()
{
	BOOL bResult = TRUE;	
	if (m_pProcThread != NULL)
	{   
		DWORD dwResult = WaitForSingleObject(m_pProcThread->m_hThread,5 * 1000);
		if (dwResult == WAIT_TIMEOUT)
		{   
			DWORD dwExitCode = 0;
			if (GetExitCodeThread(m_pProcThread->m_hThread,&dwExitCode) && dwExitCode == STILL_ACTIVE)
			{   
				bResult = TerminateThread(m_pProcThread->m_hThread,0);
			}
		}		
		if (bResult)
		{
			if (!m_pProcThread->m_bAutoDelete)
			{
				delete m_pProcThread;
				m_pProcThread = NULL;
			}
		}
	}
	if (m_pDisplayListThread != NULL)
	{   
		DWORD dwResult = WaitForSingleObject(m_pDisplayListThread->m_hThread,0);
		if (dwResult == WAIT_TIMEOUT)
		{   
			DWORD dwExitCode = 0;
			if (GetExitCodeThread(m_pDisplayListThread->m_hThread,&dwExitCode) && dwExitCode == STILL_ACTIVE)
			{   
				bResult = TerminateThread(m_pDisplayListThread->m_hThread,0);
			}
		}		
		if (bResult)
		{
			if (!m_pDisplayListThread->m_bAutoDelete)
			{
				delete m_pDisplayListThread;
				m_pDisplayListThread = NULL;
			}
		}
	}
	return bResult;
}

void DlgAcsCardPasswdCfg::SetCardCfgState(CString strCardNumber,BOOL bSucc,CString strUserDefineState /*= ""*/)
{   
	CString strCardNO = "";
    int nItemCount = m_listCard.GetItemCount();
    //先尝试匹配现在发送记录项
    if ( nItemCount > m_dwNowSendItem)
    {
        strCardNO = m_listCard.GetItemText(m_dwNowSendItem,1);
        if (strCardNO == strCardNumber)
		{   
//			g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "match now Send Item"); 
            if (strUserDefineState.IsEmpty())
            {
                m_listCard.SetItemText(m_dwNowSendItem, m_byListSendStatus,bSucc ? "OK" : "Error");
            }
            else
            {
				m_listCard.SetItemText(m_dwNowSendItem, m_byListSendStatus, strUserDefineState);
			}
			return; 
        }
    }
    //记录项不准确时候，循环查询
    for (int i = 0; i < nItemCount; i++)
	{
		strCardNO = m_listCard.GetItemText(i,1);
		if (strCardNO == strCardNumber)
		{   
			if (strUserDefineState.IsEmpty())
			{
				m_listCard.SetItemText(i, m_byListSendStatus,bSucc ? "OK" : "Error");
			}
			else
			{
				m_listCard.SetItemText(i, m_byListSendStatus, strUserDefineState);
			}
			break;
		}
	}
}

void DlgAcsCardPasswdCfg::OnBtnClearAllCard() 
{   
	char szCn[128] = "";
	char szEn[128] = "";
	char szErrInfo[128] = "";
	sprintf(szCn,"%s","此操作将清空所有的门禁卡信息，请确认?");
	sprintf(szEn,"%s","Note:This operation will clear all of the access card information, continue? ");
    g_StringLanType(szErrInfo,szCn,szEn);
	if (AfxMessageBox(szErrInfo,MB_OKCANCEL) != IDOK)
	{
		return;
	}

	NET_DVR_ACS_PARAM_TYPE struAcsParamType = {0};

	memset(&struAcsParamType,0,sizeof(struAcsParamType));
	struAcsParamType.dwSize = sizeof(struAcsParamType);
	struAcsParamType.dwParamType |= ACS_PARAM_CARD;

	if (NET_DVR_RemoteControl(m_lServerID,NET_DVR_CLEAR_ACS_PARAM,&struAcsParamType,sizeof(struAcsParamType)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CLEAR_ACS_PARAM");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CLEAR_ACS_PARAM");
	}
}

void DlgAcsCardPasswdCfg::UpdateSubList(const NET_DVR_CARD_PASSWD_CFG *lpCardCfg)
{
    if ( ! lpCardCfg )
    {
        return; 
    }
    m_listDoorRight.DeleteAllItems(); 
    m_listBelongGroup.DeleteAllItems(); 
    m_listCardRightPlan.DeleteAllItems(); 
    int i=0; 
    CString csTemp; 
//     if ( lpCardCfg->dwModifyParamType & 0x8 ) //门权限 
//     {
    
        for ( i =0; i<MAX_DOOR_NUM; i++)
        {
            csTemp.Format("%d", i+1); 
            m_listDoorRight.InsertItem(i, csTemp);
            //m_listDoorRight.SetItemText(i, 1, ( (lpCardCfg->dwDoorRight>>i)&0x1 )>0 ? "Yes": "No" );  
        }
//     }
//     if ( lpCardCfg->dwModifyParamType & 0x40 ) //所属群组参数
//     {
    
        for ( i =0; i<GROUP_COMBINATION_NUM; i++)
        {
            csTemp.Format("%d", i+1); 
            m_listBelongGroup.InsertItem(i, csTemp);
//            m_listBelongGroup.SetItemText(i, 1, ( (lpCardCfg->dwBelongGroup>>i)&0x1 )>0 ? "Yes": "No" );  
        }
//     }
//     if ( lpCardCfg->dwModifyParamType & 0x100 ) //卡权限计划参数
//     {
//     
        for ( i =0; i<MAX_DOOR_NUM; i++)
        {
            for (int j=0; j<MAX_CARD_RIGHT_PLAN_NUM; j++)
            {
                csTemp.Format("%d", i+1); 
                m_listCardRightPlan.InsertItem(i*MAX_CARD_RIGHT_PLAN_NUM+j, csTemp);
                csTemp.Format("%d", j+1); 
                m_listCardRightPlan.SetItemText(i*MAX_CARD_RIGHT_PLAN_NUM+j, 1, csTemp); 
//                csTemp.Format("%d", lpCardCfg->byCardRightPlan[i][j] ); 
                m_listCardRightPlan.SetItemText(i*MAX_CARD_RIGHT_PLAN_NUM+j, 2, csTemp); 
            }
        }
//     }
    UpdateData(FALSE);     
}
void DlgAcsCardPasswdCfg::UpdateList(int iInsertIndex, const char * pCardNo, const NET_DVR_CARD_PASSWD_CFG& struCardInfo)
{ 
    CString strItem = "";
    strItem.Format("%d",iInsertIndex + 1);
//    m_listCard.InsertItem(iInsertIndex,strItem);
    
    m_listCard.SetItemText(iInsertIndex,1, (char *)struCardInfo.byCardNo);
//     if ( struCardInfo.dwModifyParamType &0x1)
//     {
        
        strItem = (struCardInfo.byCardValid )?"Yes":"No";
        m_listCard.SetItemText(iInsertIndex,2, strItem);
//    }
//     if (struCardInfo.dwModifyParamType &0x2)
//     {
//        strItem = (struCardInfo.struValid.byEnable )?"Yes":"No";
//         m_listCard.SetItemText(iInsertIndex,8, strItem);
//         if ( struCardInfo.struValid.byEnable )
//         {
//             const NET_DVR_TIME_EX *lpTimeEx = & struCardInfo.struValid.struBeginTime; 
//             strItem.Format("%d-%d-%d, %2d:%2d:%2d", lpTimeEx->wYear, lpTimeEx->byMonth, lpTimeEx->byDay, lpTimeEx->byHour, lpTimeEx->byMinute, lpTimeEx->bySecond);
//             m_listCard.SetItemText(iInsertIndex, 9, strItem); 
//             lpTimeEx = & struCardInfo.struValid.struEndTime;
//             strItem.Format("%d-%d-%d, %2d:%2d:%2d", lpTimeEx->wYear, lpTimeEx->byMonth, lpTimeEx->byDay, lpTimeEx->byHour, lpTimeEx->byMinute, lpTimeEx->bySecond);
//             m_listCard.SetItemText(iInsertIndex, 10, strItem); 
//         }
//    }
//     if(struCardInfo.dwModifyParamType &0x4)
//     {
//         char *p ; 
//         if (struCardInfo.byCardType == 0 || struCardInfo.byCardType > 7)
//         {
//             p = pCardType1[0];
//         }
//         else 
//             p = pCardType1[struCardInfo.byCardType];
//         m_listCard.SetItemText(iInsertIndex, 4, p); 
//    }
//     if(struCardInfo.dwModifyParamType &0x10)
//     {
       // strItem = (struCardInfo.byLeaderCard )?"Yes":"No";
       // m_listCard.SetItemText(iInsertIndex, 5, strItem);

//    }
//     if (struCardInfo.dwModifyParamType &0x20)
//     {
       // strItem.Format("%d", struCardInfo.dwMaxSwipeTime); 
//        m_listCard.SetItemText(iInsertIndex, 6, strItem);
//    }
 //       strItem.Format("%d", struCardInfo.dwSwipeTime); 
//        m_listCard.SetItemText(iInsertIndex, 7, strItem);  
//     if (struCardInfo.dwModifyParamType &0x80)
//     {
        char szCardPassTemp[CARD_PASSWORD_LEN+1] = {0}; 
        memcpy(szCardPassTemp, struCardInfo.byCardPassword, sizeof(struCardInfo.byCardPassword)); 
        strItem.Format("%s", szCardPassTemp); 
        m_listCard.SetItemText(iInsertIndex, 3, strItem);
//    }

}



void CALLBACK g_fSetGatewayCardCallback1(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	DlgAcsCardPasswdCfg* pDlg = (DlgAcsCardPasswdCfg*)pUserData;
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->ProcessSetCardCfgCallbackData(dwType,lpBuffer,dwBufLen);
}

void CALLBACK g_fGetGatewayCardCallback1(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	DlgAcsCardPasswdCfg* pDlg = (DlgAcsCardPasswdCfg*)pUserData;
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->ProcessGetCardCfgCallbackData(dwType,lpBuffer,dwBufLen);
}


UINT __cdecl  g_fSendCardCfgThread1(LPVOID pParam)
{
	DlgAcsCardPasswdCfg* pDlg = (DlgAcsCardPasswdCfg*)pParam;
	if (pParam != NULL)
	{
		pDlg->SendCardData();
	}
	return 0;
}

UINT __cdecl  g_fShowCardListThread1(LPVOID pParam)
{
    DlgAcsCardPasswdCfg* pDlg = (DlgAcsCardPasswdCfg*)pParam;
    if (pParam != NULL)
    {
        pDlg->BatchAddCardToList();
    }
	return 0;    	
}

void DlgAcsCardPasswdCfg::OnClickListCardCfg(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    LPNET_DVR_CARD_PASSWD_CFG lpCardCfg  = GetSelItem(); 
    UpdateSubList(lpCardCfg);  
	*pResult = 0;
}

void DlgAcsCardPasswdCfg::OnButSimulationAdd() 
{
	// TODO: Add your control notification handler code here
	int iAddNum = 10; 
    NET_DVR_CARD_PASSWD_CFG struCardCfg = {0};	
    struCardCfg.dwSize = sizeof(struCardCfg); 
//    struCardCfg.dwModifyParamType = 1;    //卡权限
//    struCardCfg.dwModifyParamType |= 0x8;  //门权限
//    struCardCfg.dwDoorRight = 1; 
    struCardCfg.byCardValid = 1; 
    int i; 
    char szCardNo[128]; 
    for (i=0; i<iAddNum ; i++)
    {
        sprintf(szCardNo, "%d%d%d",i,i+1, i+2); 
        strncpy((char*)struCardCfg.byCardNo, szCardNo, sizeof(struCardCfg.byCardNo));
        AddToCardList(struCardCfg, szCardNo);
    }   
    
}

LPNET_DVR_CARD_PASSWD_CFG DlgAcsCardPasswdCfg::GetSelItem(char *lpCardNo)
{
    UpdateData(TRUE);
    POSITION  iPos = m_listCard.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return NULL;
    }
    int iCurSel = m_listCard.GetNextSelectedItem(iPos);
    m_iSelListItem = iCurSel;
    m_listCard.SetItemState( m_iSelListItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
    if ( lpCardNo )
    {
        m_listCard.GetItemText(iCurSel, 1, lpCardNo,  ACS_CARD_NO_LEN);
    }
    LPNET_DVR_CARD_PASSWD_CFG lpCardCfg = (LPNET_DVR_CARD_PASSWD_CFG) m_listCard.GetItemData(iCurSel);
    return lpCardCfg; 
} 

void DlgAcsCardPasswdCfg::OnBtnGetSel() 
{
	// TODO: Add your control notification handler code here
    if (m_lSetCardCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lSetCardCfgHandle);
	}
    //发送选择项
    NET_DVR_CARD_CFG_SEND_DATA struSendData = {0}; 
    struSendData.dwSize = sizeof(struSendData);
    if ( !GetSelItem((char *)struSendData.byCardNo) )
    {
        MessageBox("Select list item first"); 
        return ; 
    }

    UpdateData(TRUE); 
    NET_DVR_CARD_CFG_COND struCond = {0};
    struCond.dwSize  = sizeof(struCond);
    struCond.dwCardNum = 1;
    struCond.byCheckCardNo = (BYTE)m_BcheckCardNo; 

    m_lSetCardCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_GET_CARD_PASSWD_CFG,&struCond,sizeof(struCond), g_fGetGatewayCardCallback1,this);
    if (m_lSetCardCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CARD_PASSWD_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CARD_PASSWD_CFG");
       
        if (! NET_DVR_SendRemoteConfig(m_lSetCardCfgHandle, ENUM_ACS_SEND_DATA, (char *)(&struSendData), sizeof(struSendData)) )
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig ENUM_ACS_SEND_DATA");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SendRemoteConfig ENUM_ACS_SEND_DATA");
        }                
	}
    ShowSelListItem(); 
}

void DlgAcsCardPasswdCfg::OnBtnSetSel() 
{
	// TODO: Add your control notification handler code here
    if (m_lSetCardCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lSetCardCfgHandle);
	}
    m_lpSelSendCardCfg = GetSelItem();
    if ( ! m_lpSelSendCardCfg )
    {
        MessageBox("Select list item first"); 
        return ; 
    }
    UpdateData(TRUE);  
    NET_DVR_CARD_CFG_COND struCond = {0};
    struCond.dwSize  = sizeof(struCond);
    struCond.dwCardNum = 1;
    struCond.byCheckCardNo = (BYTE)m_BcheckCardNo;
    m_BSendSel = TRUE; 
   
    m_lSetCardCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_SET_CARD_PASSWD_CFG,&struCond,sizeof(struCond),g_fSetGatewayCardCallback1,this);
    if (m_lSetCardCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CARD_PASSWD_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CARD_PASSWD_CFG");
    }
	if (m_lSetCardCfgHandle == -1)
	{
		return;
	}
    LPNET_DVR_CARD_PASSWD_CFG lpCardCfg = NULL; 
    if ( m_BSendSel )
    {
        m_dwCardNum = 1;
        m_dwSendIndex = 0;
        SendCardData(m_lpSelSendCardCfg); 
        m_BSendSel = FALSE; 
        m_lpSelSendCardCfg = NULL; 
        return; 
    }
}


void DlgAcsCardPasswdCfg::ClearList()
{
}

void DlgAcsCardPasswdCfg::OnButBatchAdd() 
{
	// TODO: Add your control notification handler code here
    DlgAcsCardPasswdParam  dlg; 
    NET_DVR_CARD_PASSWD_CFG struCardCfg = {0};
    dlg.SetAddMode(BATCH_ADD1); 
    dlg.SetCardCfg(struCardCfg);     
    if (dlg.DoModal() == IDOK)
    {
        char szCardNo[ACS_CARD_NO_LEN];
        struCardCfg = dlg.GetCardCfg(szCardNo);
        m_dwCardNum = dlg.GetAddNum(); 
        CreateSameCfgCard(m_dwCardNum, struCardCfg); 
        if ( m_pDisplayListThread )
        {
            //停止之前的线程
        }
        m_pDisplayListThread = AfxBeginThread(g_fShowCardListThread1,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED,NULL);
        if (m_pDisplayListThread)
        {
            //m_pDisplayListThread->m_bAutoDelete = FALSE;
            m_pDisplayListThread->ResumeThread();
	    }
	}
}
void DlgAcsCardPasswdCfg::ShowSelListItem()
{
}

LPDWORD DlgAcsCardPasswdCfg::GetCardCfgPoint()
{
    if ( !m_lpRecordCardCfg)
    {
        const int iMaxCardNum = 100100; 
        m_lpRecordCardCfg = new DWORD[iMaxCardNum]; 
    }
    return m_lpRecordCardCfg; 
} 

void DlgAcsCardPasswdCfg::CreateSameCfgCard(DWORD dwNum, const NET_DVR_CARD_PASSWD_CFG &struCardCfg)
{
    int i = 0;
    LPDWORD lpArr = GetCardCfgPoint();
    LPNET_DVR_CARD_PASSWD_CFG pCardInfo = NULL; 
    for (i=0; i<dwNum; i++)
    {
        pCardInfo = new NET_DVR_CARD_PASSWD_CFG;
        memcpy(pCardInfo, &struCardCfg, sizeof(struCardCfg)); 
        sprintf( (char *)pCardInfo->byCardNo, "%s%d", (char *)struCardCfg.byCardNo, i); 
        lpArr[i] = (DWORD)pCardInfo; 
    }
}

void DlgAcsCardPasswdCfg::BatchAddCardToList()
{
    LPNET_DVR_CARD_PASSWD_CFG pCardInfo = NULL; 
    LPDWORD lpArr = GetCardCfgPoint(); 
    int i = 0; 
    int nItemCount = m_listCard.GetItemCount();   
    CString strItem ;
    m_csBatchFlag.Format("adding"); 
    PostMessage(WM_MSG_UPDATEDATA_INTERFACE, FALSE,0);
    for (i=0; i<m_dwCardNum; i++)
    {
        pCardInfo = (LPNET_DVR_CARD_PASSWD_CFG)lpArr[i];                   
        strItem.Format("%d",nItemCount + 1);
        int iItemIndex = m_listCard.InsertItem(nItemCount,strItem);
        m_listCard.SetItemData(iItemIndex,(DWORD)pCardInfo);
        UpdateList(iItemIndex, (char *)pCardInfo->byCardNo, *pCardInfo); 
        nItemCount ++; 
    }
    m_csBatchFlag.Format("finish add"); 
    PostMessage(WM_MSG_UPDATEDATA_INTERFACE, FALSE,0);
}

void DlgAcsCardPasswdCfg::OnBtnStopSend() 
{
	// TODO: Add your control notification handler code here
	StopProcThread(); 
}


BOOL DlgAcsCardPasswdCfg::SendFirstCard()
{
	if ( m_lSetCardCfgHandle == -1)
	{
		return FALSE; 
	}
	if ( m_BSendSel )
    {
		//         lpCardCfg = GetSelItem();
        SendCardData( m_lpSelSendCardCfg ); 
        m_BSendSel = FALSE; 
        m_lpSelSendCardCfg = NULL; 
        return TRUE; 
    }
	m_dwSendIndex = 0; 
	//一张卡没有，返回FALSE
	if( m_dwCardNum < 1)
	{
		return FALSE; 
	}
	LPDWORD lpArr = GetCardCfgPoint();
	m_lpNowSendCard = (LPNET_DVR_CARD_PASSWD_CFG)lpArr[m_dwSendIndex]; 
	if (!NET_DVR_SendRemoteConfig(m_lSetCardCfgHandle,3/*ENUM_ACS_SEND_DATA*/, (char *)m_lpNowSendCard ,sizeof(*m_lpNowSendCard)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Send Fail,CardNO: %s", m_lpNowSendCard->byCardNo);        
		return FALSE; 
    }
	return TRUE; 
} 

//重发卡
BOOL DlgAcsCardPasswdCfg::ReSendLastCard()
{
	if ( m_lSetCardCfgHandle == -1)
	{
		return FALSE; 
	}
	m_byLastCardSendTime ++; 
	if ( m_byLastCardSendTime >= MAX_RESEND_CARD_TIME)
	{
		return FALSE; 
	}
	if (!NET_DVR_SendRemoteConfig(m_lSetCardCfgHandle,3/*ENUM_ACS_SEND_DATA*/, (char *)m_lpNowSendCard ,sizeof(*m_lpNowSendCard)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Send Fail,CardNO: %s", m_lpNowSendCard->byCardNo);        
		return FALSE; 
    }
	return TRUE; 
}     

//发送下一张卡
BOOL DlgAcsCardPasswdCfg::SendNextCard()
{
	if ( m_lSetCardCfgHandle == -1)
	{
		return FALSE; 
	}
	m_dwSendIndex++;
	if ( m_dwSendIndex >= m_dwCardNum)
	{
		PostMessage(WM_MSG_SETCARD_FINISH,0,0);
		return TRUE; 
	}
	LPDWORD lpArr = GetCardCfgPoint();
	m_lpNowSendCard = (LPNET_DVR_CARD_PASSWD_CFG)lpArr[m_dwSendIndex]; 
	if (!NET_DVR_SendRemoteConfig(m_lSetCardCfgHandle,3/*ENUM_ACS_SEND_DATA*/, (char *)m_lpNowSendCard ,sizeof(*m_lpNowSendCard)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Send Fail,CardNO: %s", m_lpNowSendCard->byCardNo);    
		//发送失败  关闭连接
		PostMessage(WM_MSG_SETCARD_FINISH,0,0);
		return FALSE; 
    }
	return TRUE; 
}      