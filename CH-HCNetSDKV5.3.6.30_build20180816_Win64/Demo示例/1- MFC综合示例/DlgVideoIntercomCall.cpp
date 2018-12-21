// DlgVideoIntercomCall.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomCall.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define WM_DLG_VIDEO_CALL_PROCESS		WM_USER + 1
#define VIS_TALK_TIMER		            WM_USER+2		//timer for one talk
/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomCall dialog


CDlgVideoIntercomCall::CDlgVideoIntercomCall(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomCall::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomCall)
		// NOTE: the ClassWizard will add member initialization here
     m_lUserID = -1;
     m_iDevIndex = -1;
     m_byRequestType = 0; 
     m_lRemoteHandle = -1;
     m_lRealPlayHandle = -1;
     m_lVoiceTalkHandle = -1;
     m_bClientCall = TRUE;
 
     m_dwPeriod = 0;
     m_dwBuildingNumber = 0;
     m_dwUnitNumber = 0;
     m_dwFloorNumber = 0;
     m_dwRoomNumber = 0;
     m_dwDevIndex = 0;

	//}}AFX_DATA_INIT
}

void CALLBACK g_fProcessVideoCallDataCallBack(DWORD dwDataType, void *pRecvDataBuffer, DWORD dwBufSize, void* pUserData)
{
    CDlgVideoIntercomCall *pThis = static_cast<CDlgVideoIntercomCall*>(pUserData);
    
    HWND hWnd = pThis->GetSafeHwnd();
    
    if (NULL == hWnd)
    {
        return;
    }
    if (dwDataType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStates = *(DWORD*)pRecvDataBuffer;
        g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), OPERATION_SUCC_T, "Process Video Call Data Call Back status[%d]", dwStates);
        
        if (dwStates != NET_SDK_CALLBACK_STATUS_PROCESSING)
        {


//                 g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), OPERATION_SUCC_T, "Process Video Call Data Call Back status[%d]", dwStates);
                
        ::PostMessage(hWnd,WM_DLG_VIDEO_CALL_PROCESS, (DWORD)dwStates,dwBufSize);
        }
        
    }
    else if (dwDataType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_VIDEO_CALL_PARAM struVideoCallParam = {0};
        
        
        memcpy(&struVideoCallParam,pRecvDataBuffer,dwBufSize);
        char *pSzTemp = new char[dwBufSize];
        if (pSzTemp == NULL)
        {
            return;
        }
        memset(pSzTemp,0, dwBufSize);
        
        memcpy(pSzTemp,&struVideoCallParam,dwBufSize);
        ::PostMessage(hWnd,WM_DLG_VIDEO_CALL_PROCESS, (WPARAM)pSzTemp,dwBufSize);
    }
}

void CDlgVideoIntercomCall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_PERIOD, m_dwPeriod);
    DDX_Text(pDX, IDC_EDIT_BUILDING_NUMBER, m_dwBuildingNumber);
    DDX_Text(pDX, IDC_EDIT_UNIT_NUMBER, m_dwUnitNumber);
    DDX_Text(pDX, IDC_EDIT_FLOOR_NUMBER, m_dwFloorNumber);
    DDX_Text(pDX, IDC_EDIT_ROOM_NUMBER, m_dwRoomNumber);
    DDX_Text(pDX, IDC_EDIT_DEVICE_INDEX, m_dwDevIndex);
    DDX_Control(pDX, IDC_CMB_UNIT_TYPE, m_cmbUnitType);
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomCall, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomCall)
	ON_BN_CLICKED(IDC_BTN_INQUEST, OnBtnInquest)
	ON_BN_CLICKED(IDC_BTN_ANSWER, OnBtnAnswer)
	ON_BN_CLICKED(IDC_BTN_HANG_UP, OnBtnHangUp)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_WM_TIMER()
    ON_MESSAGE(WM_DLG_VIDEO_CALL_PROCESS, OnVideoCallProcess)
	ON_BN_CLICKED(IDC_BTN_REFUSE, OnBtnRefuse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomCall message handlers

void CDlgVideoIntercomCall::OnBtnInquest() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};
    m_byRequestType = 0;
    SendCallCmd();
    
   
}

void CDlgVideoIntercomCall::OnBtnAnswer() 
{
	// TODO: Add your control notification handler code here
 
    if (m_lRemoteHandle < 0)
    {
        return ;
    }
    else
    {
        if (!m_bClientCall)
        {
            KillTimer(VIS_TALK_TIMER);
        }
        StartPlay();
        SendAcceptCmd();
        return;
    }
}

void CDlgVideoIntercomCall::OnBtnHangUp() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};
	if (m_lRemoteHandle < 0)
	{
        /*StartRemoteCfg();
        SendRefuseCmd();
        StopRemoteCfg();
        */
	}
    else
    {
        if (!m_bClientCall)
        {
            KillTimer(VIS_TALK_TIMER);
        }
        SendByeCmd();  

        
        if (m_lRealPlayHandle>=0)
        {
            StopPlay();
            StopAudioIntercom();
        }
        
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
        g_StringLanType(szLan,"","");
        GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
    }
}

void CDlgVideoIntercomCall::ChangeBtnStates()
{

    return;
}

void CDlgVideoIntercomCall::StartRemoteCfg()
{
    char szLan[128] = {0};

    if (m_lRemoteHandle < 0)
    {
        memset(&m_struVideoCallCond,0,sizeof(m_struVideoCallCond));
        m_struVideoCallCond.dwSize = sizeof(m_struVideoCallCond);
        //m_struVideoCallCond.byRequestType = m_byRequestType;
        m_lRemoteHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_VIDEO_CALL_SIGNAL_PROCESS,&m_struVideoCallCond,sizeof(m_struVideoCallCond),g_fProcessVideoCallDataCallBack,this);
        if (m_lRemoteHandle < 0)
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_StartRemoteConfig NET_DVR_VIDEO_CALL_SIGNAL_PROCESS");
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_StartRemoteConfig NET_DVR_VIDEO_CALL_SIGNAL_PROCESS");
           
        }


 /*       if (m_byRequestType == 0)
        {
            GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(FALSE);
            GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(TRUE);
            GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
            GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(TRUE);
        }
        else
        {
            GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(FALSE);
            GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
            GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
            GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(TRUE);
        }
            StartPlay();
        if (m_byRequestType == 0)
        {
            g_StringLanType(szLan,"客户端主动请求对讲...","Calling...");
        }
        else
        {
            g_StringLanType(szLan,"设备端主动请求对讲...","Calling...");
        }
        GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
*/

    }
    else
    {
        g_StringLanType(szLan,"已开启对讲","In Calling");
        AfxMessageBox(szLan);
    }
	
}

void CDlgVideoIntercomCall::StopRemoteCfg()
{
    char szLan[128] = {0};
    if (m_lRemoteHandle < 0)
    {        
        g_StringLanType(szLan,"调用顺序错误","Order Error");
        AfxMessageBox(szLan);  
        return;
    }
    else
    {

        BOOL bRet = NET_DVR_StopRemoteConfig(m_lRemoteHandle);
        if (m_lRemoteHandle < 0)
        {
            
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_StopRemoteConfig");
            return;
        }
        else
        {
            m_lRemoteHandle = -1;
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_StopRemoteConfig");
        }
    }
}

void CDlgVideoIntercomCall::StartPlay()
{
    char szLan[128] = {0};

    if (m_lRealPlayHandle < 0)
    {
        NET_DVR_CLIENTINFO struClientInfo = {0};        
        struClientInfo.hPlayWnd = GetDlgItem(IDC_PIC_REALPLAY)->GetSafeHwnd();
        struClientInfo.lChannel = 1;
        struClientInfo.lLinkMode = 0;
        struClientInfo.sMultiCastIP = "";
        
        m_lRealPlayHandle = NET_DVR_RealPlay_V30(m_lUserID, &struClientInfo, NULL, NULL, TRUE);
        if (-1 == m_lRealPlayHandle)
        {
            AfxMessageBox("Fail to preview");
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
        }
    }
    else
    {
        g_StringLanType(szLan,"已经开启了预览","In RealPlaying");
        AfxMessageBox(szLan);
        return;
    }
    
}   

void CDlgVideoIntercomCall::StartVoiceTalk()
{
    char szLan[128] = {0};

    if (m_lVoiceTalkHandle < 0 )
    {
        m_lVoiceTalkHandle = NET_DVR_StartVoiceCom_V30(m_lUserID, 1,0, NULL,  NULL);//fVoiceDataCallBack
        if (g_lVoiceHandle == -1)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartVoiceCom_V30");
            
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StartVoiceCom_V30 ");
        }
    }
    else
    {
        g_StringLanType(szLan,"已经开启了对讲","In Talking");
        AfxMessageBox(szLan);
        return;
    }
    
}
 
void CDlgVideoIntercomCall::StopPlay()
{
    char szLan[128] = {0};


    if (NET_DVR_StopRealPlay(m_lRealPlayHandle))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_StopRealPlay ");
        m_lRealPlayHandle = -1;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_StopRealPlay ");
    }
    Invalidate();
    UpdateData(FALSE);
}

void CDlgVideoIntercomCall::StopAudioIntercom()
{
    char szLan[128] = {0};
        
    if (m_lVoiceTalkHandle >= 0)
    {
        if (NET_DVR_StopVoiceCom(m_lVoiceTalkHandle))
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_StopVoiceCom ");
            m_lVoiceTalkHandle = -1;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_StopVoiceCom ");
        }
    }
//     else
//     {
//         g_StringLanType(szLan,"请先开启对讲","Please Open VoiceTalk First!");
//         AfxMessageBox(szLan);
//         return;
//     }
    
}


void CDlgVideoIntercomCall::SendCancellCmd()
{
    UpdateData(TRUE);

    char szLan[128] = {0};
    if (m_lRemoteHandle < 0)
    {
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        m_struVideoCallParam.wPeriod = (WORD)m_dwPeriod;
        m_struVideoCallParam.wBuildingNumber = (WORD)m_dwBuildingNumber;
        m_struVideoCallParam.wUnitNumber = (WORD)m_dwUnitNumber;
        m_struVideoCallParam.wFloorNumber = (SHORT)m_dwFloorNumber;
        m_struVideoCallParam.wRoomNumber = (WORD)m_dwRoomNumber;
        m_struVideoCallParam.wDevIndex = (WORD)m_dwDevIndex;
        m_struVideoCallParam.byUnitType = m_cmbUnitType.GetCurSel();

        m_struVideoCallParam.dwCmdType = 1;
        if (!NET_DVR_SendRemoteConfig(m_lRemoteHandle,0,(char*)&m_struVideoCallParam,sizeof(m_struVideoCallParam)))
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
        }

        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
    }     
}


void CDlgVideoIntercomCall::SendCallCmd()
{
    UpdateData(TRUE);

    char szLan[128] = {0};
    if (m_lRemoteHandle < 0)
    {
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        m_struVideoCallParam.wPeriod = (WORD)m_dwPeriod;
        m_struVideoCallParam.wBuildingNumber = (WORD)m_dwBuildingNumber;
        m_struVideoCallParam.wUnitNumber = (WORD)m_dwUnitNumber;
        m_struVideoCallParam.wFloorNumber = (SHORT)m_dwFloorNumber;
        m_struVideoCallParam.wRoomNumber = (WORD)m_dwRoomNumber;
        m_struVideoCallParam.wDevIndex = (WORD)m_dwDevIndex;
        m_struVideoCallParam.byUnitType = m_cmbUnitType.GetCurSel();

        m_struVideoCallParam.dwCmdType = 0;
        if (!NET_DVR_SendRemoteConfig(m_lRemoteHandle,0,(char*)&m_struVideoCallParam,sizeof(m_struVideoCallParam)))
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
        }

        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
    }  
    

}

void CDlgVideoIntercomCall::SendAcceptCmd()
{
    UpdateData(TRUE);

    char szLan[128] = {0};
    if (m_lRemoteHandle < 0)
    {
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        m_struVideoCallParam.wPeriod = (WORD)m_dwPeriod;
        m_struVideoCallParam.wBuildingNumber = (WORD)m_dwBuildingNumber;
        m_struVideoCallParam.wUnitNumber = (WORD)m_dwUnitNumber;
        m_struVideoCallParam.wFloorNumber = (SHORT)m_dwFloorNumber;
        m_struVideoCallParam.wRoomNumber = (WORD)m_dwRoomNumber;
        m_struVideoCallParam.wDevIndex = (WORD)m_dwDevIndex;
        m_struVideoCallParam.byUnitType = m_cmbUnitType.GetCurSel();

        m_struVideoCallParam.dwCmdType = 2;
        if (!NET_DVR_SendRemoteConfig(m_lRemoteHandle,0,(char*)&m_struVideoCallParam,sizeof(m_struVideoCallParam)))
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
        }

        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
    }
}

void CDlgVideoIntercomCall::SendRefuseCmd()
{
    char szLan[128] = {0};
    if (m_lRemoteHandle < 0)
    {
        g_StringLanType(szLan,"请先建立连接","Please Start Remote Config First");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        m_struVideoCallParam.dwCmdType = 3;
        if (!NET_DVR_SendRemoteConfig(m_lRemoteHandle,0,(char*)&m_struVideoCallParam,sizeof(m_struVideoCallParam)))
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
        }        
        
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
        
    }
}

void CDlgVideoIntercomCall::SendBellTimeoutCmd()
{
    char szLan[128] = {0};
    if (m_lRemoteHandle < 0)
    {
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        m_struVideoCallParam.dwCmdType = 4;
        if (!NET_DVR_SendRemoteConfig(m_lRemoteHandle,0,(char*)&m_struVideoCallParam,sizeof(m_struVideoCallParam)))
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
        }

        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
    }   
}

void CDlgVideoIntercomCall::SendByeCmd()
{
    UpdateData(TRUE);

    char szLan[128] = {0};
    if (m_lRemoteHandle < 0)
    {
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        m_struVideoCallParam.wPeriod = (WORD)m_dwPeriod;
        m_struVideoCallParam.wBuildingNumber = (WORD)m_dwBuildingNumber;
        m_struVideoCallParam.wUnitNumber = (WORD)m_dwUnitNumber;
        m_struVideoCallParam.wFloorNumber = (SHORT)m_dwFloorNumber;
        m_struVideoCallParam.wRoomNumber = (WORD)m_dwRoomNumber;
        m_struVideoCallParam.wDevIndex = (WORD)m_dwDevIndex;
        m_struVideoCallParam.byUnitType = m_cmbUnitType.GetCurSel();

        m_struVideoCallParam.dwCmdType = 5;
        if (!NET_DVR_SendRemoteConfig(m_lRemoteHandle,0,(char*)&m_struVideoCallParam,sizeof(m_struVideoCallParam)))
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SendRemoteConfig dwCmdType[%d]",m_struVideoCallParam.dwCmdType);
        }

        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
    }
}

LRESULT CDlgVideoIntercomCall::OnVideoCallProcess(WPARAM wParam, LPARAM lParam)
{
    char szLan[128] = {0};
 
    //if (!NET_DVR_StopRemoteConfig(m_lRemoteHandle))
    //{
    //    g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_StopRemoteConfig");

    //}
    //else
    //{
    //    g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_StopRemoteConfig");

    //    return NULL;
    //}

    LPNET_DVR_VIDEO_CALL_PARAM pStruVideoCallParam = (LPNET_DVR_VIDEO_CALL_PARAM)wParam;
    
    if (pStruVideoCallParam->dwCmdType == 0) //设备侧发起呼叫请求
    {
        m_bClientCall = FALSE;

        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(TRUE);
        g_StringLanType(szLan,"设备发起对讲请求","Device initiates Talk request");
        GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
        SetTimer(VIS_TALK_TIMER, 30*1000, NULL);
    }
    if (pStruVideoCallParam->dwCmdType == 1) //取消本次呼叫
    {
        StopPlay();

        if (m_bClientCall)
        {
            SendCancellCmd();
            g_StringLanType(szLan,"已取消对讲","Cancel Talk ");
        }
        else
        {
            g_StringLanType(szLan,"设备已取消对讲","Device Cancel Talk ");
            KillTimer(VIS_TALK_TIMER);
        }
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
        
        GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
    }
    else if (pStruVideoCallParam->dwCmdType == 2) //接听本次呼叫
    {
        StartPlay();
        StartVoiceTalk();
//         if (!m_bClientCall)
//         {
//             SendAcceptCmd();
//         }
        
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
        g_StringLanType(szLan,"通话中...","Calling...");
       GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
    }
    else if (pStruVideoCallParam->dwCmdType == 3) //拒绝来电呼叫
    {
//         if (!m_bClientCall)
//         {
//             SendRefuseCmd();
//         }
       
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
        if (m_bClientCall)
        {
            g_StringLanType(szLan,"拒绝接听","Refuse Answer...");
        }
        else
        {
            g_StringLanType(szLan,"对方拒绝接听...","Other Party Refuse Answer...");
        }
        
       GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
    }
    else if (pStruVideoCallParam->dwCmdType == 4) //被叫响铃超时
    {
//         if (!m_bClientCall)
//         {
//             SendBellTimeoutCmd();
//         }
        
        StopPlay();
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
        if (!m_bClientCall)
        {
            g_StringLanType(szLan,"无人接听","No answer"); 
        }
        else
        {
            g_StringLanType(szLan,"响铃超时","Bell Timeout");
        }
        GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
    }
    else if (pStruVideoCallParam->dwCmdType == 5) // 结束本次通话
    {
//         if (!m_bClientCall)
//         {
//             SendByeCmd();
//         }
//          
         StopPlay();
         StopAudioIntercom();

         GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
         GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
         GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
         GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
         GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
         if (m_bClientCall)
         {
             g_StringLanType(szLan,"已挂断","Closed...");
         }
         else
         {
             g_StringLanType(szLan,"对方已挂断...","Other Party Closed...");
         }
         
       GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
    }
    else if (pStruVideoCallParam->dwCmdType == 6) //正在通话中
    {
        StopPlay();
        StopAudioIntercom();
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
        g_StringLanType(szLan,"对方正在通话中...","Other Party In Calling...");
        GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
    }
    else 
    {
        sprintf(szLan,"Unknown Command Type[%d]",pStruVideoCallParam->dwCmdType);
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,szLan);
    }
   
    if (pStruVideoCallParam != NULL)
    {
        delete pStruVideoCallParam;
        pStruVideoCallParam = NULL;
    }
    return NULL;
}

BOOL CDlgVideoIntercomCall::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_cmbUnitType.SetCurSel(0);

    memset(&m_struVideoCallCond,0,sizeof(m_struVideoCallCond)) ;
    memset(&m_struVideoCallParam,0,sizeof(m_struVideoCallParam)) ;
    
    m_struVideoCallParam.dwSize = sizeof(m_struVideoCallParam);

//     CRect rc(0, 0, 0, 0);
//     GetParent()->GetClientRect(&rc);
//     ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
//     MoveWindow(&rc);
    
    CRect rcMotion(0, 0, 0, 0);
    GetDlgItem(IDC_PIC_REALPLAY)->GetWindowRect(&rcMotion);
    ScreenToClient(&rcMotion);
    rcMotion.right = rcMotion.left - 5 + 16*22;
    rcMotion.bottom = rcMotion.top - 12 + 16*18;
    GetDlgItem(IDC_PIC_REALPLAY)->MoveWindow(rcMotion);
    if (m_byRequestType == 0)
    {
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);

    }
    else
    {
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
    }

    StartRemoteCfg();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVideoIntercomCall::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_lRemoteHandle >-1)
	{
        NET_DVR_StopRemoteConfig(m_lRemoteHandle);
        m_lRemoteHandle = -1;
	}

    if (m_lRealPlayHandle > -1)
    {
        NET_DVR_StopRealPlay(m_lRealPlayHandle);
        m_lRealPlayHandle = -1;
    }

    if (m_lVoiceTalkHandle > -1)
    {
        NET_DVR_StopVoiceCom(m_lVoiceTalkHandle);
        m_lVoiceTalkHandle = -1;
    }
	CDialog::OnClose();
}

void CDlgVideoIntercomCall::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lRemoteHandle < 0)
	{
        /*StartRemoteCfg();
        SendRefuseCmd();
        StopRemoteCfg();
        */
	}
    else
    {
        SendCancellCmd();
        
        if (m_lRealPlayHandle>=0)
        {
            StopPlay();
            StopAudioIntercom();
        }
        //StopRemoteCfg();
        
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);

        g_StringLanType(szLan,"","");
        GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
    }
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgVideoIntercomCall::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgVideoIntercomCall::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == VIS_TALK_TIMER)
    {
        DWORD dwState = 0;
        char szLan[128] = {0};
        if (!m_bClientCall)
        {
            SendBellTimeoutCmd();
        }
        
        StopPlay();
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
        if (!m_bClientCall)
        {
            g_StringLanType(szLan,"无人接听","No answer"); 
        }
        else
        {
            g_StringLanType(szLan,"响铃超时","Bell Timeout");
        }
        GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);

    }
	CDialog::OnTimer(nIDEvent);
}

void CDlgVideoIntercomCall::OnBtnRefuse() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lRemoteHandle < 0)
	{
        /*StartRemoteCfg();
        SendRefuseCmd();
        StopRemoteCfg();
        */
	}
    else
    {

        SendRefuseCmd();  

        
        if (m_lRealPlayHandle>=0)
        {
            StopPlay();
            StopAudioIntercom();
        }
        
        GetDlgItem(IDC_BTN_INQUEST)->ShowWindow(TRUE);
        GetDlgItem(IDC_BTN_ANSWER)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_HANG_UP)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_CANCEL)->ShowWindow(FALSE);
        GetDlgItem(IDC_BTN_REFUSE)->ShowWindow(FALSE);
        g_StringLanType(szLan,"拒接","Refuse");
        GetDlgItem(IDC_STATIC_SHOW_STATUS)->SetWindowText(szLan);
    }
}
