// DlgACCardParam.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgACCardParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgACCardParam dialog


void CALLBACK g_fSetAccessCardCB(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
void CALLBACK g_fGetAccessCardCB(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
#define WM_AC_SETCARD_FINISH 1102
#define WM_AC_GETCARD_FINISH 1103


BOOL CheckDate(const NET_DVR_TIME_EX& struItem)
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

CDlgACCardParam::CDlgACCardParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgACCardParam::IDD, pParent)
    , m_lSetCardCfgHandle(-1)
    , m_lGetCardCfgHandle(-1)
    , m_iLastDoorRightIndex(-1) 
    , m_iLastGroupIndex(-1) 
    , m_iLastPlanIndex(-1)
    , m_iMode(0)
    , m_BSaveCheckCardNo(FALSE)
    , m_bRoomNo(FALSE)
    , m_bSIMNo(FALSE)
    , m_csSimNo(_T(""))
    , m_bUserType(FALSE)
{
	//{{AFX_DATA_INIT(CDlgACCardParam)
	m_dwCardNum = 0;
	m_csCardNo = _T("");
	m_csCardPasswd = _T("");
	m_BGBelong = FALSE;
	m_BCardVaildParam = FALSE;
	m_BCardPasswdParam = FALSE;
	m_BCardRightParam = FALSE;
    m_BEmployeeNo = FALSE;
    m_BName = FALSE;
    m_BDepartmentNo = FALSE;
    m_BSchedulePlanNo = FALSE;
    m_BSchedulePlanType = FALSE;
	m_BCardTypeParam = FALSE;
	m_BCardVaild = FALSE;
	m_BDoorRight = FALSE;
	m_BDoorRightParam = FALSE;
	m_BGroupParam = FALSE;
	m_BLeaderCard = FALSE;
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
	m_dwAddCardNum = 0;
	m_dwSwipeTime = 0;
	m_BSwipeCard = FALSE;
	m_BCheckCardNo = FALSE;
    m_wRoomNumber= 0;
    m_wFloorNumber= 0;
    m_dwEmployeeNo = 0;
    m_csName = _T("");
    m_wDepartmentNo = 0;
    m_wSchedulePlanNo = 0;
	//}}AFX_DATA_INIT
}


void CDlgACCardParam::DoDataExchange(CDataExchange* pDX)
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
    DDX_Control(pDX, IDC_CMB_ACCC_RIGHT_TYPE, m_cmbRightType);
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
    DDX_Check(pDX, IDC_CHK_ACCC_EMPLOYEENO, m_BEmployeeNo);
    DDX_Check(pDX, IDC_CHK_ACCC_NAME, m_BName);
    DDX_Check(pDX, IDC_CHK_ACCC_DEPARTMENT_NO, m_BDepartmentNo);
    DDX_Check(pDX, IDC_CHK_ACCC_SCHEDULE_PLAN_NO, m_BSchedulePlanNo);
    DDX_Check(pDX, IDC_CHK_ACCC_SCHEDULE_PLAN_TYPE, m_BSchedulePlanType);
    DDX_Check(pDX, IDC_CHK_ACCC_CARDTYPE, m_BCardTypeParam);
    DDX_Check(pDX, IDC_CHK_ACCC_CARDVAILD, m_BCardVaild);
    DDX_Check(pDX, IDC_CHK_ACCC_DOORRIGHT, m_BDoorRight);
    DDX_Check(pDX, IDC_CHK_ACCC_DOORRIGHTPARAM, m_BDoorRightParam);
    DDX_Check(pDX, IDC_CHK_ACCC_GROUPPARAM, m_BGroupParam);
    DDX_Check(pDX, IDC_CHK_ACCC_LEADERCARD, m_BLeaderCard);
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
    DDX_Text(pDX, IDC_EDIT_ROOM_NUMBER, m_wRoomNumber);
    DDX_Text(pDX, IDC_EDIT_FLOOR_NUMBER, m_wFloorNumber);
    DDX_Text(pDX, IDC_EDIT_EMPLOYEE_NO, m_dwEmployeeNo);
    DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
    DDX_Text(pDX, IDC_EDIT_DEPARTMENT_NO, m_wDepartmentNo);
    DDX_Text(pDX, IDC_EDIT_SCHEDULE_PLAN_NO, m_wSchedulePlanNo);
    DDX_Control(pDX, IDC_COMBO_RIGHT, m_cmbRight);
    DDX_Control(pDX, IDC_COMBO_SCHEDULE_PLAN_TYPE, m_cmbSchedulePlanType);
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHK_ACCC_ROOM_NO, m_bRoomNo);
    DDX_Check(pDX, IDC_CHK_ACCC_SIM_NO, m_bSIMNo);
    DDX_Text(pDX, IDC_EDIT_SIM_NO, m_csSimNo);
    DDX_Control(pDX, IDC_COMB_ACCC_USERTYPE, m_cmbUserType);
    DDX_Check(pDX, IDC_CHK_ACCC_USER_TYPE, m_bUserType);
}


BEGIN_MESSAGE_MAP(CDlgACCardParam, CDialog)
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


void CALLBACK g_fGetAccessCardCB(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgACCardParam* pDlg = (CDlgACCardParam*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
	pDlg->ProcGetCardCfgCD(dwType,lpBuffer,dwBufLen);

}

void CALLBACK g_fSetAccessCardCB(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgACCardParam* pDlg = (CDlgACCardParam*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
	pDlg->ProcSetCardCfgCD(dwType,lpBuffer,dwBufLen);	
}

void CDlgACCardParam::ProcSetCardCfgCD(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
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
	

void CDlgACCardParam::ProcGetCardCfgCD(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_CARD_CFG_V50* pCardCfg = (NET_DVR_CARD_CFG_V50*)lpBuffer;
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

void CDlgACCardParam::AddCardParamItem(const NET_DVR_CARD_CFG_V50 &Item)
{
    LPNET_DVR_CARD_CFG_V50 lpCardCfg = new NET_DVR_CARD_CFG_V50;
    memcpy(lpCardCfg, &Item, sizeof(Item)); 
    AddPointerCardCombox(lpCardCfg); 
}

void CDlgACCardParam::AddPointerCardCombox(void *p)
{
    UpdateData(TRUE);
    DWORD dwExitItem = m_cmbCardIndex.GetCount(); 
    CString csItemp; 
    csItemp.Format("%d", dwExitItem+1); 
    int iIndex = m_cmbCardIndex.InsertString(dwExitItem, csItemp);
    m_cmbCardIndex.SetItemData(iIndex, (DWORD)p); 
    m_cmbCardIndex.SetCurSel(dwExitItem); 
}

LRESULT CDlgACCardParam::OnMsgSetcardCfgFinish(WPARAM wParam,LPARAM lParam)
{
    if ( m_lSetCardCfgHandle == -1)
    {
        return 0; 
    }
    NET_DVR_StopRemoteConfig(m_lSetCardCfgHandle);
    m_lSetCardCfgHandle = -1;
	return 0;	
}
	

LRESULT CDlgACCardParam::OnMsgGetcardCfgFinish(WPARAM wParam,LPARAM lParam)
{
    if ( m_lGetCardCfgHandle == -1)
    {
        return 0; 
    }
    NET_DVR_StopRemoteConfig(m_lGetCardCfgHandle);
    m_lGetCardCfgHandle = -1;
	return 0;
}


BOOL CDlgACCardParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i=0; 
    int iIndex; 
    CString tmp; 

    m_cmbRight.SetCurSel(3);
    m_cmbSchedulePlanType.SetCurSel(1);

    for (i = 0; i<MAX_DOOR_NUM_256; i++)
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

    for (i = 0; i<MAX_GROUP_NUM_128; i++)
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
    for (i = 0; i < MAX_DOOR_NUM_256; i++)
    {
        tmp.Format("Door %d", (i+1)); 
        m_lstDoorRight.InsertItem(i, tmp);
    }   
    
    m_lstBelongGroup.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < MAX_GROUP_NUM_128; i++)
    {
        tmp.Format("Group %d", (i+1)); 
        m_lstBelongGroup.InsertItem(i, tmp);
    }   
    i = 0;
    char szLan[128];
    g_StringLanType(szLan, "门编号", "door number");
	m_lstPlanNo.InsertColumn( i++,szLan,LVCFMT_LEFT,60);
    g_StringLanType(szLan, "卡权限下标", "card right index");
    m_lstPlanNo.InsertColumn( i++,szLan,LVCFMT_LEFT,80);
    g_StringLanType(szLan, "计划模板编号", "plan index");
    m_lstPlanNo.InsertColumn( i++,szLan,LVCFMT_LEFT,60);
    m_lstPlanNo.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    UpdateInterface();
    if ( m_iMode == BATCH_ADD)
    {
        GetDlgItem(IDC_EDT_ACCC_ADD_CARDNUM)->ShowWindow(SW_SHOW); 
        GetDlgItem(IDC_STATIC_ACCC_ADDCARD_NUM)->ShowWindow(SW_SHOW); 
    }


	// TODO: Add extra initialization here	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//获取所有
void CDlgACCardParam::OnButGet() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_CARD_CFG_COND struCond = {0};
    struCond.dwSize  = sizeof(struCond);
    struCond.dwCardNum = 0xffffffff;

    m_lSetCardCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_GET_CARD_CFG_V50,&struCond,sizeof(struCond),g_fGetAccessCardCB, this);
    if (m_lSetCardCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CARD_CFG_V50");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CARD_CFG_V50");
	}
}

void CDlgACCardParam::OnButSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_CARD_CFG_COND struCond = {0};
    struCond.dwSize  = sizeof(struCond);
    struCond.dwCardNum = m_cmbCardIndex.GetCount(); 

    m_lSetCardCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_SET_CARD_CFG_V50,&struCond,sizeof(struCond), g_fSetAccessCardCB, this);
    if (m_lSetCardCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CARD_CFG_V50");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CARD_CFG_V50");
	}
}


//新建某一项
void CDlgACCardParam::OnButNewItem() 
{
	// TODO: Add your control notification handler code here
    LPNET_DVR_CARD_CFG_V50 lpCardCfg = new NET_DVR_CARD_CFG_V50;
    lpCardCfg->dwSize = sizeof(*lpCardCfg);
    AddPointerCardCombox(lpCardCfg); 
}

void CDlgACCardParam::OnSelectCardindex() 
{
	// TODO: Add your control notification handler code here
	
}


void CDlgACCardParam::SetCardCfg(const NET_DVR_CARD_CFG_V50& struItem, const char *pCardNo)
{
    memcpy(&m_struCardCfg, &struItem, sizeof(struItem)); 
    if ( pCardNo )
    {
        m_csCardNo =  pCardNo;
        m_csSaveCardNo = m_csCardNo; 
    }
}
    


NET_DVR_CARD_CFG_V50 CDlgACCardParam::GetCardCfg(char *pCardNo)
{
    if ( pCardNo )
    {
        strcpy(pCardNo, (LPCSTR)m_csSaveCardNo); 
    }

    return m_struCardCfg; 
}

//更新界面
void CDlgACCardParam::UpdateInterface()
{
    m_csCardNo = m_csSaveCardNo ; 
    NET_DVR_CARD_CFG_V50 &struCardInfo = m_struCardCfg;
    BOOL bCheck; 
    int i=0;
    if ( struCardInfo.dwModifyParamType &0x1)
    {
        m_BCardVaildParam = TRUE; 
    }
        m_BCardVaild = struCardInfo.byCardValid; 
//    }
    if (struCardInfo.dwModifyParamType &0x2)
    {
        m_BVaildPeriodParam = TRUE; 
    }
        m_BVaildPeriodEnable = struCardInfo.struValid.byEnable; 
        if ( m_BVaildPeriodEnable )
        {
            if ( CheckDate(struCardInfo.struValid.struBeginTime) )
            {
                m_DTBeginDate.SetDate(struCardInfo.struValid.struBeginTime.wYear, struCardInfo.struValid.struBeginTime.byMonth, struCardInfo.struValid.struBeginTime.byDay); 
                m_DTBeginTime.SetTime(struCardInfo.struValid.struBeginTime.byHour, struCardInfo.struValid.struBeginTime.byMinute, struCardInfo.struValid.struBeginTime.bySecond);     
            }
            if ( CheckDate(struCardInfo.struValid.struEndTime) )
            {
                m_DTEndDate.SetDate(struCardInfo.struValid.struEndTime.wYear, struCardInfo.struValid.struEndTime.byMonth, struCardInfo.struValid.struEndTime.byDay); 
                m_DTEndTime.SetTime(struCardInfo.struValid.struEndTime.byHour, struCardInfo.struValid.struEndTime.byMinute, struCardInfo.struValid.struEndTime.bySecond); 
            }
         }   
//    }
    if(struCardInfo.dwModifyParamType &0x4)
    {
        m_BCardTypeParam = TRUE; 
    }
        m_cmbCardType.SetCurSel(struCardInfo.byCardType-1);  
        m_cmbRightType.SetCurSel(struCardInfo.byRightType);
//    }
    //门权限参数
    if(struCardInfo.dwModifyParamType &0x8)
    {
        m_BDoorRightParam = TRUE;        
    }
    for (i=0; i<MAX_DOOR_NUM_256; i++)
    {
        if ((struCardInfo.byDoorRight[i]) == 1)
        {
            bCheck = TRUE;                 
        }
        else
        {
            bCheck = FALSE; 
        }
        m_lstDoorRight.SetCheck(i, bCheck); 
    }
    //m_BDoorRight = (struCardInfo.dwDoorRight&1)?TRUE:FALSE; 
    if(struCardInfo.dwModifyParamType &0x10)
    {
        m_BLeaderCardParam = TRUE; 
    }
    m_BLeaderCard = struCardInfo.byLeaderCard;
//    }
    if (struCardInfo.dwModifyParamType &0x20)
    {
        m_BMaxUseTimeParam = TRUE; 
    }
    m_dwMaxUseTime = struCardInfo.dwMaxSwipeTime;
    m_wRoomNumber = struCardInfo.wRoomNumber;
    m_wFloorNumber = struCardInfo.wFloorNumber;
    m_dwEmployeeNo = struCardInfo.dwEmployeeNo;
    m_csName = struCardInfo.byName;
    m_csSimNo = struCardInfo.bySIMNum;
    m_wDepartmentNo = struCardInfo.wDepartmentNo;
    m_wSchedulePlanNo = struCardInfo.wSchedulePlanNo;
    //m_cmbRight.SetCurSel(struCardInfo.byRight-1);
    m_cmbSchedulePlanType.SetCurSel(struCardInfo.bySchedulePlanType-1);
    m_cmbUserType.SetCurSel(struCardInfo.byUserType);
//    }
    if (struCardInfo.dwModifyParamType &0x40)
    {
        m_BGroupParam = TRUE; 
    }
    for (i = 0; i<MAX_GROUP_NUM_128; i++)
    {
        if ((struCardInfo.byBelongGroup[i]) == 1)
        {
            bCheck = TRUE;                 
        }
        else
        {
            bCheck = FALSE; 
        }
        m_lstBelongGroup.SetCheck(i, bCheck); 
    }
//        m_BGBelong = (struCardInfo.dwBelongGroup&0x1); 
//    }
    if (struCardInfo.dwModifyParamType &0x80)
    {
        m_BCardPasswdParam = TRUE; 
    }
    char szCardPassTemp[CARD_PASSWORD_LEN+1] = {0}; 
    memcpy(szCardPassTemp, struCardInfo.byCardPassword, sizeof(struCardInfo.byCardPassword)); 
    m_csCardPasswd.Format("%s", szCardPassTemp);
//    }
    if (struCardInfo.dwModifyParamType &0x100)
    {
        m_BCardRightParam = TRUE; 
    }
    if (struCardInfo.dwModifyParamType & 0x400)
    {
        m_BEmployeeNo = TRUE;
    }
    if (struCardInfo.dwModifyParamType & 0x800)
    {
        m_BName = TRUE;
    }
    if (struCardInfo.dwModifyParamType & 0x1000)
    {
        m_BDepartmentNo = TRUE;
    }
    if (struCardInfo.dwModifyParamType & 0x2000)
    {
        m_BSchedulePlanNo = TRUE;
    }
    if (struCardInfo.dwModifyParamType & 0x4000)
    {
        m_BSchedulePlanType = TRUE;
    }
    if (struCardInfo.dwModifyParamType & 0x8000)
    {
        m_bRoomNo = TRUE;
    }
    if (struCardInfo.dwModifyParamType & 0x10000)
    {
        m_bSIMNo = TRUE;
    }
    if (struCardInfo.dwModifyParamType & 0x40000)
    {
        m_bUserType = TRUE;
    }
    UpdatePlanList(&m_struCardCfg.wCardRightPlan[0][0]);  
//        m_dwPlanNo = struCardInfo.byCardRightPlan[0][0]; 
//    }
    if (struCardInfo.dwModifyParamType & 0x200 )
    {
        m_BSwipeCard = TRUE; 
    }
    m_dwSwipeTime = struCardInfo.dwSwipeTime; 
    UpdateData(FALSE); 
}    

//更新结构体
void CDlgACCardParam::UpdateInterface(BOOL bRefresh)
{
    UpdateData(TRUE); 
    m_csSaveCardNo = m_csCardNo; 
    NET_DVR_CARD_CFG_V50 &struCardInfo =  m_struCardCfg;
    struCardInfo.dwSize = sizeof(m_struCardCfg); 
    strncpy((char *)struCardInfo.byCardNo, (LPCSTR)m_csCardNo, sizeof(struCardInfo.byCardNo)); 
    if(m_BCardVaildParam)
    {
        struCardInfo.dwModifyParamType |= 0x1; 
        struCardInfo.byCardValid = m_BCardVaild;
    }
    if( m_BVaildPeriodParam)
    {
        struCardInfo.dwModifyParamType |= 0x2;
        struCardInfo.struValid.byEnable = m_BVaildPeriodEnable;
        if ( m_BVaildPeriodEnable )
        {
            struCardInfo.struValid.struBeginTime.wYear = m_DTBeginDate.GetYear(); 
            struCardInfo.struValid.struBeginTime.byMonth = m_DTBeginDate.GetMonth();
            struCardInfo.struValid.struBeginTime.byDay = m_DTBeginDate.GetDay();
            struCardInfo.struValid.struBeginTime.byHour = m_DTBeginTime.GetHour(); 
            struCardInfo.struValid.struBeginTime.byMinute = m_DTBeginTime.GetMinute();
            struCardInfo.struValid.struBeginTime.bySecond = m_DTBeginTime.GetSecond();
            struCardInfo.struValid.struEndTime.wYear = m_DTEndDate.GetYear(); 
            struCardInfo.struValid.struEndTime.byMonth = m_DTEndDate.GetMonth();
            struCardInfo.struValid.struEndTime.byDay = m_DTEndDate.GetDay();
            struCardInfo.struValid.struEndTime.byHour = m_DTEndTime.GetHour(); 
            struCardInfo.struValid.struEndTime.byMinute = m_DTEndTime.GetMinute();
            struCardInfo.struValid.struEndTime.bySecond = m_DTEndTime.GetSecond();     
        }   
    }
    if( m_BCardTypeParam )
    {
        struCardInfo.dwModifyParamType |= 0x4; 
        struCardInfo.byCardType = m_cmbCardType.GetCurSel()+1; 
    }
    struCardInfo.byRightType = m_cmbRightType.GetCurSel();
    if( m_BDoorRightParam )
    {
        struCardInfo.dwModifyParamType |= 0x8; 
        struCardInfo.byDoorRight[0] = 0;
        for (int i = 0; i<MAX_DOOR_NUM_256; i++)
        {
            if ( m_lstDoorRight.GetCheck(i))
            {
                struCardInfo.byDoorRight[i] = 1;
            }
            else
            {
                struCardInfo.byDoorRight[i] = 0;
            }
        }
    }
    if( m_BLeaderCardParam )
    {
        struCardInfo.dwModifyParamType |= 0x10; 
        struCardInfo.byLeaderCard = m_BLeaderCard; 
    }
    if( m_BMaxUseTimeParam )
    {
        struCardInfo.dwModifyParamType |= 0x20; 
        struCardInfo.dwMaxSwipeTime = m_dwMaxUseTime;
    }
    struCardInfo.wRoomNumber = m_wRoomNumber;
    struCardInfo.wFloorNumber = m_wFloorNumber;
    struCardInfo.dwEmployeeNo = m_dwEmployeeNo;
    memcpy(struCardInfo.byName, (LPCSTR)m_csName, m_csName.GetAllocLength());
    memcpy(struCardInfo.bySIMNum, (LPCSTR)m_csSimNo, m_csSimNo.GetAllocLength());
    struCardInfo.wDepartmentNo = m_wDepartmentNo;
    struCardInfo.wSchedulePlanNo = m_wSchedulePlanNo;
    //struCardInfo.byRight = m_cmbRight.GetCurSel()+1;
    struCardInfo.bySchedulePlanType = m_cmbSchedulePlanType.GetCurSel()+1;
    struCardInfo.byUserType = m_cmbUserType.GetCurSel();

    if( m_BGroupParam )
    {
        struCardInfo.dwModifyParamType |= 0x40; 
        for (int i = 0; i<MAX_GROUP_NUM_128; i++)
        {
            if ( m_lstBelongGroup.GetCheck(i))
            {
                struCardInfo.byBelongGroup[i] = 1;
            }
            else
            {
                struCardInfo.byBelongGroup[i] = 0;
            }
        }     
    }
    if( m_BCardPasswdParam )
    {
        struCardInfo.dwModifyParamType |= 0x80; 
        strncpy((char *)struCardInfo.byCardPassword, (LPCSTR)m_csCardPasswd, sizeof(struCardInfo.byCardPassword)); 
    }
    if( m_BCardRightParam)
    {      
        struCardInfo.dwModifyParamType |= 0x100; 
    }
    if ( m_BSwipeCard )
    {
        struCardInfo.dwModifyParamType |= 0x200; 
        struCardInfo.dwSwipeTime = m_dwSwipeTime; 
    }
    if (m_BEmployeeNo)
    {
        struCardInfo.dwModifyParamType |= 0x400;
        struCardInfo.dwEmployeeNo = m_dwEmployeeNo;
    }
    if (m_BName)
    {
        struCardInfo.dwModifyParamType |= 0x800;
    }
    if (m_BDepartmentNo)
    {
        struCardInfo.dwModifyParamType |= 0x1000;
    }
    if (m_BSchedulePlanNo)
    {
        struCardInfo.dwModifyParamType |= 0x2000;
    }
    if (m_BSchedulePlanType)
    {
        struCardInfo.dwModifyParamType |= 0x4000;
    }
    if (m_bRoomNo)
    {
        struCardInfo.dwModifyParamType |= 0x8000;
    }
    if (m_bSIMNo)
    {
        struCardInfo.dwModifyParamType |= 0x10000;
    }
    if (m_bUserType)
    {
        struCardInfo.dwModifyParamType |= 0x40000;
    }
    m_iAddNum = m_dwAddCardNum; 
}

void CDlgACCardParam::OnSelchangeDoorRightIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if( m_BDoorRight)
    {
        m_struCardCfg.byDoorRight[m_iLastDoorRightIndex] = 1;
    }  
    m_iLastDoorRightIndex = m_cmbDoorRightIndex.GetCurSel(); 
    m_BDoorRight = (m_struCardCfg.byDoorRight[m_iLastDoorRightIndex]) > 0 ? TRUE : FALSE;
    UpdateData(FALSE); 
}

void CDlgACCardParam::OnSelchangeBelongGroup() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if( m_BGBelong)
    {
        m_struCardCfg.byBelongGroup[m_iLastGroupIndex] = 1;
    }  
    m_iLastGroupIndex = m_cmbBelongGroup.GetCurSel(); 
    m_BGBelong = (m_struCardCfg.byBelongGroup[m_iLastGroupIndex]) > 0 ? TRUE : FALSE;
    UpdateData(FALSE); 
}

void CDlgACCardParam::OnSelchangeMaxDoorNum() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    BYTE byDay, byPlanNo; 
    if( m_iLastPlanIndex != -1 )
    {
        byDay = (m_iLastPlanIndex>>8)& 0xff; 
        byPlanNo = (m_iLastPlanIndex& 0xff); 
        m_struCardCfg.wCardRightPlan[byDay][byPlanNo] = (BYTE)m_dwPlanNo;
    } 
    byDay = m_cmbDoorIndex.GetCurSel(); 
    byPlanNo = m_cmbCardPlanIndex.GetCurSel(); 
    m_iLastPlanIndex = ((DWORD)byDay<<8) | ((DWORD)byPlanNo); 
    m_dwPlanNo = m_struCardCfg.wCardRightPlan[byDay][byPlanNo];
    UpdateData(FALSE); 
}

void CDlgACCardParam::OnSelchangeCardPlanIndex() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    BYTE byDay, byPlanNo; 
    if( m_iLastPlanIndex != -1 )
    {
        byDay = (m_iLastPlanIndex>>8)& 0xff; 
        byPlanNo = (m_iLastPlanIndex& 0xff); 
        m_struCardCfg.wCardRightPlan[byDay][byPlanNo] = (BYTE)m_dwPlanNo;
    } 
    byDay = m_cmbDoorIndex.GetCurSel(); 
    byPlanNo = m_cmbCardPlanIndex.GetCurSel(); 
    m_iLastPlanIndex = ((DWORD)byDay<<8) | ((DWORD)byPlanNo); 
    m_dwPlanNo = m_struCardCfg.wCardRightPlan[byDay][byPlanNo];
    UpdateData(FALSE);	
}

void CDlgACCardParam::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateInterface(FALSE); 
    CDialog::OnOK(); 
}

void CDlgACCardParam::OnChkSelectAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    if ( m_BSelectAll )
    {
    	m_BCardVaildParam = TRUE;
    	m_BCardPasswdParam = TRUE;
    	m_BCardRightParam = TRUE;
        m_BEmployeeNo = TRUE;
        m_BName = TRUE;
        m_BDepartmentNo = TRUE;
        m_BSchedulePlanNo = TRUE;
        m_BSchedulePlanType = TRUE;
    	m_BCardTypeParam = TRUE;
    	m_BDoorRightParam = TRUE;
    	m_BGroupParam = TRUE;
    	m_BLeaderCardParam = TRUE;
    	m_BMaxUseTimeParam = TRUE;
		m_BVaildPeriodParam = TRUE;
        m_BSwipeCard = TRUE; 
        m_bUserType = TRUE;
    }
    else
    {
        m_BCardVaildParam = FALSE;
        m_BCardPasswdParam = FALSE;
        m_BCardRightParam = FALSE;
        m_BEmployeeNo = FALSE;
        m_BName = FALSE;
        m_BDepartmentNo = FALSE;
        m_BSchedulePlanNo = FALSE;
        m_BSchedulePlanType = FALSE;
        m_BCardTypeParam = FALSE;
        m_BDoorRightParam = FALSE;
        m_BGroupParam = FALSE;
        m_BLeaderCardParam = FALSE;
        m_BMaxUseTimeParam = FALSE;
		m_BVaildPeriodParam = FALSE;
        m_BSwipeCard = FALSE; 
        m_bUserType = FALSE;
    }
    UpdateData(FALSE); 
}


int  CDlgACCardParam::GetAddNum() const
{
    return m_iAddNum; 
} 
void CDlgACCardParam::SetAddMode(int iMode)
{
    if ( iMode  == BATCH_ADD)
    {
        m_iMode = BATCH_ADD; 
        return ; 
    }
    m_iMode = SINGEL_ADD; 
}

void CDlgACCardParam::OnButTestParam() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    m_BSelectAll = TRUE;
    m_csCardNo = "111"; 
    m_csCardPasswd = "222"; 
    m_BCardVaild = TRUE; 
    m_BLeaderCard = TRUE; 
    m_BGBelong = TRUE; 
    m_BDoorRight = TRUE; 
    m_BVaildPeriodEnable = TRUE; 
    m_dwMaxUseTime = 32;
    m_wRoomNumber = 0;
    m_wFloorNumber = 0;
    m_dwPlanNo = 1;    
    m_dwEmployeeNo = 1000;
    m_csName = "name";
    m_csSimNo = "12345678901";
    m_wDepartmentNo = 1;
    m_wSchedulePlanNo = 1;
    m_cmbRight.SetCurSel(3);
    m_cmbSchedulePlanType.SetCurSel(1);
    UpdateData(FALSE); 
    m_cmbCardType.SetCurSel(0); 
    m_cmbRightType.SetCurSel(0);
    m_lstBelongGroup.SetCheck(0); 
	m_lstDoorRight.SetCheck(0); 
    m_struCardCfg.wCardRightPlan[0][0] = 1;
    m_struCardCfg.wCardRightPlan[0][1] = 2;
    WORD * lpCardRight = &m_struCardCfg.wCardRightPlan[0][0];
    UpdatePlanList(lpCardRight);
    OnChkSelectAll(); 
}

void CDlgACCardParam::OnChkAcccCheckCardno() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    m_BSaveCheckCardNo = m_BCheckCardNo; 
}

void CDlgACCardParam::OnClickLstAcccPlanno(NMHDR* pNMHDR, LRESULT* pResult) 
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
    m_dwPlanNo = m_struCardCfg.wCardRightPlan[i][j];
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgACCardParam::OnKillfocusEdtAcccCrPlanno() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    DWORD dwIndex = m_lstPlanNo.GetItemData(m_iLastDoorRightIndex);
    int i, j; 
    i = dwIndex>>16; 
    j = dwIndex & 0xffff; 
    m_struCardCfg.wCardRightPlan[i][j] = m_dwPlanNo;
    UpdatePlanList(&m_struCardCfg.wCardRightPlan[0][0]);
}

void CDlgACCardParam::UpdatePlanList(const WORD* wCardPlan)
{
//    UpdateData(TRUE); 
    m_lstPlanNo.DeleteAllItems(); 
    int i, j; 
    CString csTmp ; 
    for (i = 0; i<MAX_DOOR_NUM_256; i++)
    {
        for (j=0; j<MAX_CARD_RIGHT_PLAN_NUM; j++)
        {
            csTmp.Format("%d", i+1); 
            m_lstPlanNo.InsertItem(i*MAX_CARD_RIGHT_PLAN_NUM+j, csTmp);        
            csTmp.Format("%d", j+1); 
            m_lstPlanNo.SetItemText(i*MAX_CARD_RIGHT_PLAN_NUM+j, 1, csTmp); 
            csTmp.Format("%d", wCardPlan[i*MAX_CARD_RIGHT_PLAN_NUM + j]);   // struCardInfo.byCardRightPlan[i][j]); 
            m_lstPlanNo.SetItemText(i*MAX_CARD_RIGHT_PLAN_NUM+j, 2, csTmp); 
            m_lstPlanNo.SetItemData(i*MAX_CARD_RIGHT_PLAN_NUM+j, (i<<16)+j);
        }
    }
    UpdateData(FALSE); 
}
