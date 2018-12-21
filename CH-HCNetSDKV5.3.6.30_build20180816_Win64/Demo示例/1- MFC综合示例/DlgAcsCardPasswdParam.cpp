// DlgACCardParam.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsCardPasswdParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgACCardParam dialog


void CALLBACK g_fSetAccessCardCB1(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
void CALLBACK g_fGetAccessCardCB1(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
#define WM_AC_SETCARD_FINISH 1102
#define WM_AC_GETCARD_FINISH 1103


BOOL CheckDate1(const NET_DVR_TIME_EX& struItem)
{
    if (struItem.wYear < 1970 ||  struItem.byMonth > 12 || struItem.byDay > 31 )
    {
        return FALSE; 
    }
    
    if (struItem.byHour >23 ||  struItem.byMinute > 59 || struItem.bySecond > 59 )
    {
        return FALSE; 
    }
    return TRUE; 
}   

DlgAcsCardPasswdParam::DlgAcsCardPasswdParam(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAcsCardPasswdParam::IDD, pParent)
    , m_lSetCardCfgHandle(-1)
    , m_lGetCardCfgHandle(-1)
    , m_iLastDoorRightIndex(-1) 
    , m_iLastGroupIndex(-1) 
    , m_iLastPlanIndex(-1)
    , m_iMode(0)
    , m_BSaveCheckCardNo(FALSE)
{
	//{{AFX_DATA_INIT(CDlgACCardParam)
	m_dwCardNum = 0;
	m_csCardNo = _T("");
	m_csCardPasswd = _T("");
	m_BGBelong = FALSE;
	m_BCardVaildParam = FALSE;
	m_BCardPasswdParam = FALSE;
	m_BCardRightParam = FALSE;
	m_BCardTypeParam = FALSE;
	m_BCardVaild = FALSE;
	m_BDoorRight = FALSE;
	m_BDoorRightParam = FALSE;
	m_BGroupParam = FALSE;
	m_BLeaderCard = FALSE;
    m_BEnablePasswdOpen = FALSE;
	m_BLeaderCardParam = FALSE;
	m_BMaxUseTimeParam = FALSE;
	m_BVaildPeriodEnable = FALSE;
	m_BVaildPeriodParam = FALSE;
	m_DTBeginDate = COleDateTime::GetCurrentTime();
	m_DTBeginTime = COleDateTime::GetCurrentTime();
	m_DTEndDate = COleDateTime::GetCurrentTime();
	m_DTEndTime = COleDateTime::GetCurrentTime();
	m_dwMaxUseTime = 0;
	m_dwPlanNo = 0;
	m_BSelectAll = FALSE;
	m_dwAddCardNum = 100000;
	m_dwSwipeTime = 0;
	m_BSwipeCard = FALSE;
	m_BCheckCardNo = FALSE;
	//}}AFX_DATA_INIT
}


void DlgAcsCardPasswdParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgACCardParam)
	DDX_Control(pDX, IDC_LST_ACCC_PLANNO, m_lstPlanNo);
	DDX_Control(pDX, IDC_LST_ACCC_BELONGGROUPNO, m_lstBelongGroup);
	DDX_Control(pDX, IDC_LST_ACCC_DOORRIGHT, m_lstDoorRight);
	DDX_Control(pDX, IDC_COMB_ACCC_DOORRIGHTINDEX, m_cmbDoorRightIndex);
	DDX_Control(pDX, IDC_COMB_ACCC_CARDPLANINDEX, m_cmbCardPlanIndex);
	DDX_Control(pDX, IDC_COMB_ACCC_MAXDOORNUM, m_cmbDoorIndex);
	DDX_Control(pDX, IDC_COMB_ACCC_CARDTYPE, m_cmbCardType);
	DDX_Control(pDX, IDC_COMB_ACCC_CARDINDEX, m_cmbCardIndex);
	DDX_Control(pDX, IDC_COMB_ACCC_BELONGGROUP, m_cmbBelongGroup);
	DDX_Text(pDX, IDC_EDT_ACCC_CARDNUMBER, m_dwCardNum);
	DDX_Text(pDX, IDC_EDT_ACCC_CARDNO, m_csCardNo);
	DDX_Text(pDX, IDC_EDT_ACCC_CARDPASSWORD, m_csCardPasswd);
	DDV_MaxChars(pDX, m_csCardPasswd, 8);
	DDX_Check(pDX, IDC_CHK_ACCC_BELONG, m_BGBelong);
	DDX_Check(pDX, IDC_CHK_ACCC_CARDPARAMVALID, m_BCardVaildParam);
	DDX_Check(pDX, IDC_CHK_ACCC_CARDPASSWORDPARAM, m_BCardPasswdParam);
	DDX_Check(pDX, IDC_CHK_ACCC_CARDRIGHTPARAM, m_BCardRightParam);
	DDX_Check(pDX, IDC_CHK_ACCC_CARDTYPE, m_BCardTypeParam);
	DDX_Check(pDX, IDC_CHK_ACCC_CARDVAILD, m_BCardVaild);
	DDX_Check(pDX, IDC_CHK_ACCC_DOORRIGHT, m_BDoorRight);
	DDX_Check(pDX, IDC_CHK_ACCC_DOORRIGHTPARAM, m_BDoorRightParam);
	DDX_Check(pDX, IDC_CHK_ACCC_GROUPPARAM, m_BGroupParam);
	DDX_Check(pDX, IDC_CHK_ACCC_LEADERCARD, m_BLeaderCard);
    DDX_Check(pDX, IDC_CHK_ACCC_PASSWD_OPEN, m_BEnablePasswdOpen);
	DDX_Check(pDX, IDC_CHK_ACCC_LEADERCARDPARAM, m_BLeaderCardParam);
	DDX_Check(pDX, IDC_CHK_ACCC_MAXUSENUMBER, m_BMaxUseTimeParam);
	DDX_Check(pDX, IDC_CHK_ACCC_VAILDPERIOD_ENABLE, m_BVaildPeriodEnable);
	DDX_Check(pDX, IDC_CHK_ACCC_VALIDPERIOD, m_BVaildPeriodParam);
	DDX_DateTimeCtrl(pDX, IDC_DTP_ACCC_VAILDPERIOD_BEGINTIME_DATE, m_DTBeginDate);
	DDX_DateTimeCtrl(pDX, IDC_DTP_ACCC_VAILDPERIOD_BEGINTIME_TIME, m_DTBeginTime);
	DDX_DateTimeCtrl(pDX, IDC_DTP_ACCC_VAILDPERIOD_ENDTIME_DATE, m_DTEndDate);
	DDX_DateTimeCtrl(pDX, IDC_DTP_ACCC_VAILDPERIOD_ENDTIME_TIME, m_DTEndTime);
	DDX_Text(pDX, IDC_EDT_ACCC_MAXUSETIME, m_dwMaxUseTime);
	DDX_Text(pDX, IDC_EDT_ACCC_CR_PLANNO, m_dwPlanNo);
	DDX_Check(pDX, IDC_CHK_SELECT_ALL, m_BSelectAll);
	DDX_Text(pDX, IDC_EDT_ACCC_ADD_CARDNUM, m_dwAddCardNum);
	DDX_Text(pDX, IDC_EDT_ACCC_SWIPETIME, m_dwSwipeTime);
	DDX_Check(pDX, IDC_CHK_ACCC_SWIPECARDNUM, m_BSwipeCard);
	DDX_Check(pDX, IDC_CHK_ACCC_CHECK_CARDNO, m_BCheckCardNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAcsCardPasswdParam, CDialog)
	//{{AFX_MSG_MAP(CDlgACCardParam)
	ON_BN_CLICKED(IDC_BUT_ACCC_GET, OnButGet)
	ON_BN_CLICKED(IDC_BUT_ACCC_SET, OnButSet)
	ON_BN_CLICKED(IDC_BUT_ACCC_NEWITEM, OnButNewItem)
	ON_CBN_SELCHANGE(IDC_COMB_ACCC_CARDINDEX, OnSelectCardindex)
	ON_CBN_SELCHANGE(IDC_COMB_ACCC_DOORRIGHTINDEX, OnSelchangeDoorRightIndex)
	ON_CBN_SELCHANGE(IDC_COMB_ACCC_BELONGGROUP, OnSelchangeBelongGroup)
	ON_CBN_SELCHANGE(IDC_COMB_ACCC_MAXDOORNUM, OnSelchangeMaxDoorNum)
	ON_CBN_SELCHANGE(IDC_COMB_ACCC_CARDPLANINDEX, OnSelchangeCardPlanIndex)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_BN_CLICKED(IDC_CHK_SELECT_ALL, OnChkSelectAll)
	ON_BN_CLICKED(IDC_BUT_TEST_PARAM, OnButTestParam)
	ON_BN_CLICKED(IDC_CHK_ACCC_CHECK_CARDNO, OnChkAcccCheckCardno)
	ON_NOTIFY(NM_CLICK, IDC_LST_ACCC_PLANNO, OnClickLstAcccPlanno)
	ON_EN_KILLFOCUS(IDC_EDT_ACCC_CR_PLANNO, OnKillfocusEdtAcccCrPlanno)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_AC_SETCARD_FINISH, OnMsgSetcardCfgFinish)
	ON_MESSAGE(WM_AC_GETCARD_FINISH, OnMsgGetcardCfgFinish)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgACCardParam message handlers


void CALLBACK g_fGetAccessCardCB1(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    DlgAcsCardPasswdParam* pDlg = (DlgAcsCardPasswdParam*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
	pDlg->ProcGetCardCfgCD(dwType,lpBuffer,dwBufLen);

}

void CALLBACK g_fSetAccessCardCB1(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    DlgAcsCardPasswdParam* pDlg = (DlgAcsCardPasswdParam*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
	pDlg->ProcSetCardCfgCD(dwType,lpBuffer,dwBufLen);	
}

void DlgAcsCardPasswdParam::ProcSetCardCfgCD(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    static CString strItem;
    if (dwType != NET_SDK_CALLBACK_TYPE_STATUS)
    {
        return;
    }

    DWORD dwStatus = *(DWORD*)lpBuffer;

    if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
    {   
        char szCardNumber[ACS_CARD_NO_LEN + 1] = "\0";
        strncpy(szCardNumber,(char*)(lpBuffer) + 4, ACS_CARD_NO_LEN);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_SDK_CALLBACK_STATUS_PROCESSING %s", szCardNumber);
    }
    else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
    {
        char szCardNumber[ACS_CARD_NO_LEN + 1] = "\0";
        DWORD dwErrCode = *((DWORD*)lpBuffer + 1);
        strncpy(szCardNumber,(char*)(lpBuffer) + 8,ACS_CARD_NO_LEN);
        CString strErr ;
        strErr.Format("%s : %d \r\n",szCardNumber, dwErrCode);
        strItem += strErr; 
    }
    if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
    {
        MessageBox(strItem); 
        PostMessage(WM_AC_SETCARD_FINISH,0,0);
    }
    else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
    {
        MessageBox(strItem); 
        PostMessage(WM_AC_SETCARD_FINISH,0,0);
	}
}
	

void DlgAcsCardPasswdParam::ProcGetCardCfgCD(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_CARD_PASSWD_CFG* pCardCfg = (NET_DVR_CARD_PASSWD_CFG*)lpBuffer;
        AddCardParamItem(*pCardCfg);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_AC_GETCARD_FINISH,0,0);
        }
	}
}

void DlgAcsCardPasswdParam::AddCardParamItem(const NET_DVR_CARD_PASSWD_CFG &Item)
{
    LPNET_DVR_CARD_PASSWD_CFG lpCardCfg = new NET_DVR_CARD_PASSWD_CFG; 
    memcpy(lpCardCfg, &Item, sizeof(Item)); 
    AddPointerCardCombox(lpCardCfg); 
}

void DlgAcsCardPasswdParam::AddPointerCardCombox(void *p)
{
    UpdateData(TRUE);
    DWORD dwExitItem = m_cmbCardIndex.GetCount(); 
    CString csItemp; 
    csItemp.Format("%d", dwExitItem+1); 
    int iIndex = m_cmbCardIndex.InsertString(dwExitItem, csItemp);
    m_cmbCardIndex.SetItemData(iIndex, (DWORD)p); 
    m_cmbCardIndex.SetCurSel(dwExitItem); 
}

LRESULT DlgAcsCardPasswdParam::OnMsgSetcardCfgFinish(WPARAM wParam,LPARAM lParam)
{
    if ( m_lSetCardCfgHandle == -1)
    {
        return 0; 
    }
    NET_DVR_StopRemoteConfig(m_lSetCardCfgHandle);
    m_lSetCardCfgHandle = -1;
	return 0;	
}
	

LRESULT DlgAcsCardPasswdParam::OnMsgGetcardCfgFinish(WPARAM wParam,LPARAM lParam)
{
    if ( m_lGetCardCfgHandle == -1)
    {
        return 0; 
    }
    NET_DVR_StopRemoteConfig(m_lGetCardCfgHandle);
    m_lGetCardCfgHandle = -1;
	return 0;
}


BOOL DlgAcsCardPasswdParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i=0; 
    int iIndex; 
    CString tmp; 

    for (i=0; i<MAX_DOOR_NUM; i++ )
    {
        tmp.Format("%d", i+1);
        iIndex = m_cmbDoorRightIndex.AddString(tmp);
        m_cmbDoorRightIndex.SetItemData(iIndex, i); 
        iIndex = m_cmbDoorIndex.AddString(tmp);
        m_cmbDoorIndex.SetItemData(iIndex, i);     
    }
    m_cmbDoorIndex.SetCurSel(0);
    m_cmbDoorRightIndex.SetCurSel(0); 
    for (i=0; i<MAX_CARD_RIGHT_PLAN_NUM; i++ )
    {
        tmp.Format("%d", i+1);
        iIndex = m_cmbCardPlanIndex.AddString(tmp);
        m_cmbCardPlanIndex.SetItemData(iIndex, i); 
    }
    m_cmbCardPlanIndex.SetCurSel(0); 

    for (i=0; i<MAX_GROUP_NUM; i++ )
    {
        tmp.Format("%d", i+1);
        iIndex = m_cmbBelongGroup.AddString(tmp);
        m_cmbBelongGroup.SetItemData(iIndex, i); 
    }
    m_cmbBelongGroup.SetCurSel(0); 
    m_iLastDoorRightIndex = 0;  
    m_iLastGroupIndex = 0;
    m_iLastPlanIndex = 0; 

    m_lstDoorRight.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < MAX_DOOR_NUM; i++)
    {
        tmp.Format("Door %d", (i+1)); 
        m_lstDoorRight.InsertItem(i, tmp);
    }   
    
    m_lstBelongGroup.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < MAX_DOOR_NUM; i++)
    {
        tmp.Format("Group %d", (i+1)); 
        m_lstBelongGroup.InsertItem(i, tmp);
    }   
    i = 0; 
	m_lstPlanNo.InsertColumn( i++,"门编号",LVCFMT_LEFT,60);
    m_lstPlanNo.InsertColumn( i++,"卡权限编号",LVCFMT_LEFT,80);
    m_lstPlanNo.InsertColumn( i++,"计划编号",LVCFMT_LEFT,60);
    m_lstPlanNo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    UpdateInterface();
    if ( m_iMode == BATCH_ADD1)
    {
        GetDlgItem(IDC_EDT_ACCC_ADD_CARDNUM)->ShowWindow(SW_SHOW); 
        GetDlgItem(IDC_STATIC_ACCC_ADDCARD_NUM)->ShowWindow(SW_SHOW); 
    }


	// TODO: Add extra initialization here	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//获取所有
void DlgAcsCardPasswdParam::OnButGet() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_CARD_CFG_COND struCond = {0};
    struCond.dwSize  = sizeof(struCond);
    struCond.dwCardNum = 0xffffffff;

    m_lSetCardCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_GET_CARD_PASSWD_CFG,&struCond,sizeof(struCond),g_fGetAccessCardCB1, this);
    if (m_lSetCardCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CARD_PASSWD_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CARD_PASSWD_CFG");
	}
}

void DlgAcsCardPasswdParam::OnButSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_CARD_CFG_COND struCond = {0};
    struCond.dwSize  = sizeof(struCond);
    struCond.dwCardNum = m_cmbCardIndex.GetCount(); 

    m_lSetCardCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_SET_CARD_PASSWD_CFG,&struCond,sizeof(struCond), g_fSetAccessCardCB1, this);
    if (m_lSetCardCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CARD_PASSWD_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CARD_PASSWD_CFG");
	}
}


//新建某一项
void DlgAcsCardPasswdParam::OnButNewItem() 
{
	// TODO: Add your control notification handler code here
    LPNET_DVR_CARD_PASSWD_CFG lpCardCfg = new NET_DVR_CARD_PASSWD_CFG; 
    lpCardCfg->dwSize = sizeof(*lpCardCfg);
    AddPointerCardCombox(lpCardCfg); 
}

void DlgAcsCardPasswdParam::OnSelectCardindex() 
{
	// TODO: Add your control notification handler code here
	
}


void DlgAcsCardPasswdParam::SetCardCfg(const NET_DVR_CARD_PASSWD_CFG& struItem , const char *pCardNo )
{
    memcpy(&m_struCardCfg, &struItem, sizeof(struItem)); 
    if ( pCardNo )
    {
        m_csCardNo =  pCardNo;
        m_csSaveCardNo = m_csCardNo; 
    }
}
    


NET_DVR_CARD_PASSWD_CFG DlgAcsCardPasswdParam::GetCardCfg(char *pCardNo ) 
{
    if ( pCardNo )
    {
        strcpy(pCardNo, (LPCSTR)m_csSaveCardNo); 
    }

    return m_struCardCfg; 
}

//更新界面
void DlgAcsCardPasswdParam::UpdateInterface()
{
    m_csCardNo = m_csSaveCardNo ; 
    NET_DVR_CARD_PASSWD_CFG &struCardInfo =  m_struCardCfg;
    //BOOL bCheck; 
    int i=0;
//     if ( struCardInfo.dwModifyParamType &0x1)
//     {
//         m_BCardVaildParam = TRUE; 
//     }
        m_BCardVaild = struCardInfo.byCardValid; 
//    }
//     if (struCardInfo.dwModifyParamType &0x2)
//     {
//         m_BVaildPeriodParam = TRUE; 
//     }
 
//    }

//    }
    //门权限参数
//     if(struCardInfo.dwModifyParamType &0x8)
//     {
//         m_BDoorRightParam = TRUE;        
//     }
//     for (i=0; i<MAX_DOOR_NUM; i++)
//     {
//         if ((struCardInfo.dwDoorRight&(1<<i)) != 0)
//         {
//             bCheck = TRUE;                 
//         }
//         else
//         {
//             bCheck = FALSE; 
//         }
//         m_lstDoorRight.SetCheck(i, bCheck); 
//     }
//     m_BDoorRight = (struCardInfo.dwDoorRight&1)?TRUE:FALSE; 
//     if(struCardInfo.dwModifyParamType &0x10)
//     {
//         m_BLeaderCardParam = TRUE; 
//     }
//     m_BLeaderCard = struCardInfo.byLeaderCard; 
//     m_BEnablePasswdOpen = struCardInfo.byEnablePasswdOpen; 
// //    }
//     if (struCardInfo.dwModifyParamType &0x20)
//     {
//         m_BMaxUseTimeParam = TRUE; 
//     }
//     m_dwMaxUseTime = struCardInfo.dwMaxSwipeTime; 
// //    }
//     if (struCardInfo.dwModifyParamType &0x40)
//     {
//         m_BGroupParam = TRUE; 
//     }
//     for (i=0; i<MAX_DOOR_NUM; i++)
//     {
//         if ((struCardInfo.dwBelongGroup&(1<<i)) != 0)
//         {
//             bCheck = TRUE;                 
//         }
//         else
//         {
//             bCheck = FALSE; 
//         }
//         m_lstBelongGroup.SetCheck(i, bCheck); 
//     }
// //        m_BGBelong = (struCardInfo.dwBelongGroup&0x1); 
// //    }
//     if (struCardInfo.dwModifyParamType &0x80)
//     {
//         m_BCardPasswdParam = TRUE; 
//     }
    char szCardPassTemp[CARD_PASSWORD_LEN+1] = {0}; 
    memcpy(szCardPassTemp, struCardInfo.byCardPassword, sizeof(struCardInfo.byCardPassword)); 
    m_csCardPasswd.Format("%s", szCardPassTemp);
//    }
//     if (struCardInfo.dwModifyParamType &0x100)
//     {
//         m_BCardRightParam = TRUE; 
//     }
//     UpdatePlanList(&m_struCardCfg.byCardRightPlan[0][0]);  
// //        m_dwPlanNo = struCardInfo.byCardRightPlan[0][0]; 
// //    }
//     if (struCardInfo.dwModifyParamType & 0x200 )
//     {
//         m_BSwipeCard = TRUE; 
//     }
//     m_dwSwipeTime = struCardInfo.dwSwipeTime; 
    UpdateData(FALSE); 
}    

//更新结构体
void DlgAcsCardPasswdParam::UpdateInterface(BOOL bRefresh)
{
    UpdateData(TRUE); 
    m_csSaveCardNo = m_csCardNo; 
    NET_DVR_CARD_PASSWD_CFG &struCardInfo =  m_struCardCfg;
    struCardInfo.dwSize = sizeof(m_struCardCfg); 
    strncpy((char *)struCardInfo.byCardNo, (LPCSTR)m_csCardNo, sizeof(struCardInfo.byCardNo)); 
    
    struCardInfo.byCardValid = m_BCardVaild;
   
    //if( m_BCardPasswdParam )
    //{
        strncpy((char *)struCardInfo.byCardPassword, (LPCSTR)m_csCardPasswd, sizeof(struCardInfo.byCardPassword)); 
    //}
    m_iAddNum = m_dwAddCardNum; 
}

void DlgAcsCardPasswdParam::OnSelchangeDoorRightIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_iLastDoorRightIndex = m_cmbDoorRightIndex.GetCurSel(); 
    UpdateData(FALSE); 
}

void DlgAcsCardPasswdParam::OnSelchangeBelongGroup() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_iLastGroupIndex = m_cmbBelongGroup.GetCurSel(); 
    UpdateData(FALSE); 
}

void DlgAcsCardPasswdParam::OnSelchangeMaxDoorNum() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    BYTE byDay, byPlanNo; 
    if( m_iLastPlanIndex != -1 )
    {
        byDay = (m_iLastPlanIndex>>8)& 0xff; 
        byPlanNo = (m_iLastPlanIndex& 0xff); 
    } 
    byDay = m_cmbDoorIndex.GetCurSel(); 
    byPlanNo = m_cmbCardPlanIndex.GetCurSel(); 
    m_iLastPlanIndex = ((DWORD)byDay<<8) | ((DWORD)byPlanNo); 
    UpdateData(FALSE); 
}

void DlgAcsCardPasswdParam::OnSelchangeCardPlanIndex() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    BYTE byDay, byPlanNo; 
    if( m_iLastPlanIndex != -1 )
    {
        byDay = (m_iLastPlanIndex>>8)& 0xff; 
        byPlanNo = (m_iLastPlanIndex& 0xff); 
    } 
    byDay = m_cmbDoorIndex.GetCurSel(); 
    byPlanNo = m_cmbCardPlanIndex.GetCurSel(); 
    m_iLastPlanIndex = ((DWORD)byDay<<8) | ((DWORD)byPlanNo); 
    UpdateData(FALSE);	
}

void DlgAcsCardPasswdParam::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateInterface(FALSE); 
    CDialog::OnOK(); 
}

void DlgAcsCardPasswdParam::OnChkSelectAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    if ( m_BSelectAll )
    {
    	m_BCardVaildParam = TRUE;
    	m_BCardPasswdParam = TRUE;
    	m_BCardRightParam = TRUE;
    	m_BCardTypeParam = TRUE;
    	m_BDoorRightParam = TRUE;
    	m_BGroupParam = TRUE;
    	m_BLeaderCardParam = TRUE;
    	m_BMaxUseTimeParam = TRUE;
		m_BVaildPeriodParam = TRUE;
        m_BSwipeCard = TRUE; 
    }
    else
    {
        m_BCardVaildParam = FALSE;
        m_BCardPasswdParam = FALSE;
        m_BCardRightParam = FALSE;
        m_BCardTypeParam = FALSE;
        m_BDoorRightParam = FALSE;
        m_BGroupParam = FALSE;
        m_BLeaderCardParam = FALSE;
        m_BMaxUseTimeParam = FALSE;
		m_BVaildPeriodParam = FALSE;
        m_BSwipeCard = FALSE; 
    }
    UpdateData(FALSE); 
}


int  DlgAcsCardPasswdParam::GetAddNum() const
{
    return m_iAddNum; 
} 
void DlgAcsCardPasswdParam::SetAddMode(int iMode)
{
    if ( iMode  == BATCH_ADD1)
    {
        m_iMode = BATCH_ADD1; 
        return ; 
    }
    m_iMode = SINGEL_ADD1; 
}

void DlgAcsCardPasswdParam::OnButTestParam() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    m_BSelectAll = TRUE;
    m_csCardNo = "111"; 
    m_csCardPasswd = "222"; 
    m_BCardVaild = TRUE; 
    m_BLeaderCard = TRUE; 
    m_BEnablePasswdOpen = TRUE;
    m_BGBelong = TRUE; 
    m_BDoorRight = TRUE; 
    m_BVaildPeriodEnable = TRUE; 
    m_dwMaxUseTime = 32;
    m_dwPlanNo = 1;    
    UpdateData(FALSE); 
    m_cmbCardType.SetCurSel(0); 
    m_lstBelongGroup.SetCheck(0); 
	m_lstDoorRight.SetCheck(0); 
    //UpdatePlanList(lpCardRight);
    OnChkSelectAll(); 
}

void DlgAcsCardPasswdParam::OnChkAcccCheckCardno() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    m_BSaveCheckCardNo = m_BCheckCardNo; 
}

void DlgAcsCardPasswdParam::OnClickLstAcccPlanno(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    POSITION  iPos = m_lstPlanNo.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    m_iLastDoorRightIndex  = m_lstPlanNo.GetNextSelectedItem(iPos);
    DWORD dwIndex = m_lstPlanNo.GetItemData(m_iLastDoorRightIndex); 
    int i, j; 
    i = dwIndex>>16; 
    j = dwIndex & 0xffff; 
    UpdateData(FALSE); 
	*pResult = 0;
}

void DlgAcsCardPasswdParam::OnKillfocusEdtAcccCrPlanno() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    DWORD dwIndex = m_lstPlanNo.GetItemData(m_iLastDoorRightIndex);
    int i, j; 
    i = dwIndex>>16; 
    j = dwIndex & 0xffff; 
}

void DlgAcsCardPasswdParam::UpdatePlanList(const BYTE* byCardPlan)
{
//    UpdateData(TRUE); 
    m_lstPlanNo.DeleteAllItems(); 
    int i, j; 
    CString csTmp ; 
    for (i=0; i<MAX_DOOR_NUM; i++)
    {
        for (j=0; j<MAX_CARD_RIGHT_PLAN_NUM; j++)
        {
            csTmp.Format("%d", i+1); 
            m_lstPlanNo.InsertItem(i*MAX_CARD_RIGHT_PLAN_NUM+j, csTmp);        
            csTmp.Format("%d", j+1); 
            m_lstPlanNo.SetItemText(i*MAX_CARD_RIGHT_PLAN_NUM+j, 1, csTmp); 
            csTmp.Format("%d", byCardPlan[i*MAX_CARD_RIGHT_PLAN_NUM+j] );   // struCardInfo.byCardRightPlan[i][j]); 
            m_lstPlanNo.SetItemText(i*MAX_CARD_RIGHT_PLAN_NUM+j, 2, csTmp); 
            m_lstPlanNo.SetItemData(i*MAX_CARD_RIGHT_PLAN_NUM+j, (i<<16)+j);
        }
    }
    UpdateData(FALSE); 
}
