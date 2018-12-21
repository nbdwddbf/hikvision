// DlgMouseEvent.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMouseEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void CALLBACK g_MouseLoacaInfoCallback(DWORD dwDataType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgMouseEvent *pThis = static_cast<CDlgMouseEvent*>(pUserData);
    
    HWND hWnd = pThis->GetSafeHwnd();
    if (NULL == hWnd)
    {
        return;
    }
    if (dwDataType == NET_SDK_CALLBACK_TYPE_STATUS)
    {       
        DWORD dwStates = (DWORD)lpBuffer;
        g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), OPERATION_SUCC_T, "Start local Mouse Event Info status[%d]", (DWORD)lpBuffer);
        
        if (dwStates != NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            if (*((DWORD*) lpBuffer) == NET_SDK_CALLBACK_STATUS_SUCCESS)
            {
                NET_DVR_StopRemoteConfig(pThis->m_lStartLocalRecordHanlde);
                pThis->m_lStartLocalRecordHanlde = -1;
            }
        }
        else
        {
            g_pMainDlg->AddLog(pThis->m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_START_LOCAL_MOUSE_EVENT Processing...");
        }
    }
    
}

void CALLBACK g_RemoteMouseInfoCallback(DWORD dwDataType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgMouseEvent *pThis = static_cast<CDlgMouseEvent*>(pUserData);
    
    HWND hWnd = pThis->GetSafeHwnd();
    if (NULL == hWnd)
    {
        return;
    }
    if (dwDataType == NET_SDK_CALLBACK_TYPE_STATUS)
    {       
        DWORD dwStates = (DWORD)lpBuffer;
        g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), OPERATION_SUCC_T, "Start local Mouse Event Info status[%d]", (DWORD)lpBuffer);
        
        if (dwStates != NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            if (*((DWORD*) lpBuffer) == NET_SDK_CALLBACK_STATUS_SUCCESS)
            {
                NET_DVR_StopRemoteConfig(pThis->m_lStartRemoteTestHanlde);
                pThis->m_lStartRemoteTestHanlde = -1;
            }
        }
        else
        {
            NET_DVR_MOUSE_EVENT_PARAM struMouseParam = {0};
            struMouseParam.dwSize = sizeof(struMouseParam);
            struMouseParam.byMouseEvent = 1;
            struMouseParam.struPoint.fX = (float)0.1237;
            struMouseParam.struPoint.fX = (float)0.2341;
            if (NET_DVR_SendRemoteConfig(pThis->m_lStartRemoteTestHanlde,4,(char*)&struMouseParam,sizeof(struMouseParam)))
            {
                g_pMainDlg->AddLog(pThis->m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SendRemoteConfig ");
            }
            else
            {
                g_pMainDlg->AddLog(pThis->m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SendRemoteConfig");
            }
            
        }
    }
    
}

/////////////////////////////////////////////////////////////////////////////
// CDlgMouseEvent dialog


CDlgMouseEvent::CDlgMouseEvent(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMouseEvent::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMouseEvent)
		// NOTE: the ClassWizard will add member initialization here
    m_iDevIndex = -1;
    m_lUserID = -1;
    m_lStartLocalRecordHanlde = -1;
    m_lStartRemoteTestHanlde = -1;
    m_bStop =FALSE;
	//}}AFX_DATA_INIT
}


void CDlgMouseEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMouseEvent)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMouseEvent, CDialog)
	//{{AFX_MSG_MAP(CDlgMouseEvent)
	ON_BN_CLICKED(IDC_BTN_START_LOCAL_RECORD, OnBtnStartLocalRecord)
	ON_BN_CLICKED(IDC_BTN_STOP_LOCAL_RECORD, OnBtnStopLocalRecord)
	ON_BN_CLICKED(IDC_BTN_START_REMOTE_TEST, OnBtnStartRemoteTest)
	ON_BN_CLICKED(IDC_BTN_STOP_REMOTE_TEST, OnBtnStopRemoteTest)
	ON_BN_CLICKED(IDC_BTN_SEND_DATA, OnBtnSendData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMouseEvent message handlers

void CDlgMouseEvent::OnBtnStartLocalRecord() 
{
	// TODO: Add your control notification handler code here

    m_lStartLocalRecordHanlde = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_START_LOCAL_MOUSE_EVENT,NULL,0,g_MouseLoacaInfoCallback,this);
	
    if(m_lStartLocalRecordHanlde < 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_START_LOCAL_MOUSE_EVENT");
       return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_START_LOCAL_MOUSE_EVENT");
    }
}

void CDlgMouseEvent::OnBtnStopLocalRecord() 
{
	// TODO: Add your control notification handler code here
	if (m_lStartLocalRecordHanlde >-1)
	{
        if (NET_DVR_StopRemoteConfig(m_lStartLocalRecordHanlde))
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_START_LOCAL_MOUSE_EVENT");
            m_lStartLocalRecordHanlde = -1;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_START_LOCAL_MOUSE_EVENT");
            return;
        }
	}
}

void CDlgMouseEvent::OnBtnStartRemoteTest() 
{
	// TODO: Add your control notification handler code here
    
    m_lStartRemoteTestHanlde = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_START_SIMULARE_MOUSE_EVENT,NULL,0,g_RemoteMouseInfoCallback,this);
    
    if(m_lStartRemoteTestHanlde < 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_START_SIMULARE_MOUSE_EVENT");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_START_SIMULARE_MOUSE_EVENT");
            m_bStop =FALSE;
    }
}

void CDlgMouseEvent::OnBtnStopRemoteTest() 
{
	// TODO: Add your control notification handler code here
    if (m_lStartRemoteTestHanlde >-1)
    {
        if (NET_DVR_StopRemoteConfig(m_lStartRemoteTestHanlde))
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_START_SIMULARE_MOUSE_EVENT");
            m_lStartRemoteTestHanlde = -1;
            m_bStop =TRUE;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_START_SIMULARE_MOUSE_EVENT");
            return;
        }
	}
}

void CDlgMouseEvent::OnBtnSendData() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[1024] = {0};
    if (m_lStartRemoteTestHanlde < 0)
    {
        g_StringLanType(szLan,"请先建立连接","establish connection First"); 
        AfxMessageBox(szLan);
        return;
    }

    int iIndex = 0;
    while (!m_bStop)
    {
        
        memset(&m_struMousePara,0,sizeof(m_struMousePara));
        m_struMousePara.dwSize = sizeof(m_struMousePara);
        m_struMousePara.byMouseEvent = iIndex%5 ;
        switch(m_struMousePara.byMouseEvent)
        {
        case 0:
            m_struMousePara.struPoint.fX = (float)0.123789;
            m_struMousePara.struPoint.fY = (float)0.456123;
            break;
        case 1:
            m_struMousePara.struPoint.fX = (float)0.456123;
            m_struMousePara.struPoint.fY = (float)0.123789;
            break;
        case 2:
            m_struMousePara.struPoint.fX = (float)0.1111;
            m_struMousePara.struPoint.fY = (float)0.2222;
            break;
        case 3:
            m_struMousePara.struPoint.fX = (float)0.33344;
            m_struMousePara.struPoint.fY = (float)0.444634;
            break;
        case 4:
            m_struMousePara.struPoint.fX = (float)0.55555;
            m_struMousePara.struPoint.fY = (float)0.123498;
            break;
        default:
            m_struMousePara.struPoint.fX = (float)0.66666;
            m_struMousePara.struPoint.fY = (float)0.77777;
            break;
        }
        
        iIndex ++;
        
        if (!NET_DVR_SendRemoteConfig(m_lStartRemoteTestHanlde,4,(char*)&m_struMousePara,sizeof(m_struMousePara)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T,"NET_DVR_SendRemoteConfig");
            break;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T,"NET_DVR_SendRemoteConfig");
        }
        UpdateData(FALSE);
        Sleep(500);
    }
    
    
    UpdateData(FALSE);
}
