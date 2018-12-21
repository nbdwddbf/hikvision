// DlgGopInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGopInfo.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_PROC_GOP_INFO_SHOW		WM_USER + 1

void CALLBACK g_GetGopInfoCallback(DWORD dwDataType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgGopInfo *pThis = static_cast<CDlgGopInfo*>(pUserData);
    
    HWND hWnd = pThis->GetSafeHwnd();
    if (NULL == hWnd)
    {
        return;
    }
    if (dwDataType == NET_SDK_CALLBACK_TYPE_STATUS)
    {       
        g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), OPERATION_SUCC_T, "Get GOP Info status[%d]", *(DWORD*)lpBuffer);
        if (*((DWORD*) lpBuffer) == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {

            ::PostMessage(hWnd,WM_PROC_GOP_INFO_SHOW, NULL,1);

            //NET_DVR_StopRemoteConfig(pThis->m_lRemoteHandle);
        }
    }
    else if (dwDataType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_GOP_INFO_RET* pStruRetInfo = new NET_DVR_GOP_INFO_RET;

        if (pStruRetInfo == NULL)
        {
            return;
        }
        memcpy(pStruRetInfo,lpBuffer,sizeof(NET_DVR_GOP_INFO_RET));
 
        char *pSzTemp = new char[pStruRetInfo->dwDataSize];
        if (pSzTemp == NULL)
        {
            return;
        }
        memset(pSzTemp,0, pStruRetInfo->dwDataSize);
        
        memcpy(pSzTemp,pStruRetInfo->pBuf,pStruRetInfo->dwDataSize);
        pStruRetInfo->pBuf = pSzTemp;
        ::PostMessage(hWnd,WM_PROC_GOP_INFO_SHOW, (WPARAM)(pStruRetInfo),dwBufLen);
        
    }
}

/////////////////////////////////////////////////////////////////////////////
// CDlgGopInfo dialog


CDlgGopInfo::CDlgGopInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGopInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGopInfo)
	m_DataStart = 0;
	m_DataStop = 0;
	m_timeStart = 0;
	m_timeStop = 0;
    m_lRemoteHandle = -1;
    m_lUserID = -1;
    m_iDevIndex = -1;
	//}}AFX_DATA_INIT
}


void CDlgGopInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGopInfo)
	DDX_Control(pDX, IDC_LIST_RET_INFO, m_listRetInfo);
	DDX_Control(pDX, IDC_CMB_CHAN, m_cmbChan);
	DDX_DateTimeCtrl(pDX, IDC_DATE_RT_START, m_DataStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_RT_STOP, m_DataStop);
	DDX_DateTimeCtrl(pDX, IDC_TIME_RT_START, m_timeStart);
	DDX_DateTimeCtrl(pDX, IDC_TIME_RT_STOP, m_timeStop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGopInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgGopInfo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
    ON_MESSAGE(WM_PROC_GOP_INFO_SHOW, OnShowGOPInfo)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGopInfo message handlers

void CDlgGopInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    memset(&m_struGopInfo,0,sizeof(m_struGopInfo));
    m_struGopInfo.dwSize = sizeof(m_struGopInfo);
    m_struGopInfo.lChannel = m_cmbChan.GetItemData(m_cmbChan.GetCurSel());
    m_struGopInfo.struStartTime.wYear = m_DataStart.GetYear();
    m_struGopInfo.struStartTime.byMonth = m_DataStart.GetMonth();
    m_struGopInfo.struStartTime.byDay = m_DataStart.GetDay();
    m_struGopInfo.struStartTime.byHour = m_timeStart.GetHour();
    m_struGopInfo.struStartTime.byMinute = m_timeStart.GetMinute();
    m_struGopInfo.struStartTime.bySecond = m_timeStart.GetSecond();

    m_struGopInfo.struEndTime.wYear = m_DataStop.GetYear();
    m_struGopInfo.struEndTime.byMonth = m_DataStop.GetMonth();
    m_struGopInfo.struEndTime.byDay = m_DataStop.GetDay();
    m_struGopInfo.struEndTime.byHour = m_timeStop.GetHour();
    m_struGopInfo.struEndTime.byMinute = m_timeStop.GetMinute();
    m_struGopInfo.struEndTime.bySecond = m_timeStop.GetSecond();

    if (m_lRemoteHandle == -1)
    {
        m_lRemoteHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_GET_GOP_INFO,&m_struGopInfo,sizeof(m_struGopInfo),g_GetGopInfoCallback,this);
        if (m_lRemoteHandle != -1)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_GOP_INFO");
            GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
            GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_GOP_INFO");
        }
    }

    UpdateData(FALSE);


}

BOOL CDlgGopInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&m_struGopInfo,0,sizeof(m_struGopInfo));
    memset(&m_struGopInfoRet,0,sizeof(m_struGopInfoRet));



    CTime timeCur = CTime::GetCurrentTime();
    CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
    CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
    m_DataStart = timeStart;
    m_timeStart = timeStart;
    m_DataStop = timeStop;
	m_timeStop = timeStop;

    //AddChanInfo 
    m_cmbChan.ResetContent();
	g_AddChanInfoToComBox(m_cmbChan, m_iDevIndex);
    m_cmbChan.SetCurSel(0);


    m_listRetInfo.SetExtendedStyle(m_listRetInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    char szLan[128] = {0};
    g_StringLanType(szLan, "序号", "Serial No.");
    m_listRetInfo.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);
    
    g_StringLanType(szLan, "GOP时间点", "GOP Time");
    m_listRetInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
    
    g_StringLanType(szLan, "持续时间", "Duration Time");
    m_listRetInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);
    
    g_StringLanType(szLan, "信息长度", "Info Length");
    m_listRetInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 60, -1);
    
    g_StringLanType(szLan, "信息内容", "Content");
    m_listRetInfo.InsertColumn(4, szLan, LVCFMT_LEFT, 400, -1);
    
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CDlgGopInfo::OnShowGOPInfo(WPARAM wParam, LPARAM lParam)
{

    DWORD len = (DWORD)lParam;
    if (len == 1)
    {
        OnBtnStop();
        return NULL;
    }
    LPNET_DVR_GOP_INFO_RET pStruRetInfo = (LPNET_DVR_GOP_INFO_RET)wParam;
    
    DWORD dwListCount = m_listRetInfo.GetItemCount();
    int nIndex = 0;
    
    
    char szLan[5*1024] = {0};

  
    sprintf(szLan, "%d",dwListCount);   
    m_listRetInfo.InsertItem(dwListCount, szLan);
    
   nIndex++;
    sprintf(szLan, "%04d-%02d_%02d %02d:%02d:%02d.%04d", pStruRetInfo->struGopTime.wYear,pStruRetInfo->struGopTime.byMonth,\
        pStruRetInfo->struGopTime.byDay, pStruRetInfo->struGopTime.byHour, pStruRetInfo->struGopTime.byMinute,\
        pStruRetInfo->struGopTime.bySecond, pStruRetInfo->struGopTime.wMilliSec);
    m_listRetInfo.SetItemText(dwListCount,nIndex, szLan);
    nIndex++;
    
    sprintf(szLan, "%d", pStruRetInfo->dwDuration);
    m_listRetInfo.SetItemText(dwListCount,nIndex, szLan);
    nIndex ++;
    
    sprintf(szLan, "%d", pStruRetInfo->dwDataSize);
    m_listRetInfo.SetItemText(dwListCount,nIndex, szLan);
    nIndex ++;
   
   memset(szLan,0,5*1024);
   for (int i = 0; (i < pStruRetInfo->dwDataSize) &&(i < 5*1024);i++)
   {
       sprintf(&szLan[i],"%d",pStruRetInfo->pBuf[i]);
   }
    //memcpy(szLan, &(pStruRetInfo->pBuf),pStruRetInfo->dwDataSize);
    m_listRetInfo.SetItemText(dwListCount,nIndex, szLan);
    nIndex ++;


    
    if (pStruRetInfo->pBuf != NULL)
    {
       delete [](pStruRetInfo->pBuf);
        pStruRetInfo->pBuf = NULL;
    }

    if (pStruRetInfo != NULL)
    {
        delete pStruRetInfo;
        pStruRetInfo = NULL;
    }
    
    UpdateData(FALSE);
    return NULL;
}

void CDlgGopInfo::OnBtnStop() 
{
	// TODO: Add your control notification handler code here

    if (m_lRemoteHandle == -1)
    {
        return;
    }
    if(NET_DVR_StopRemoteConfig(m_lRemoteHandle))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig");
        GetDlgItem(IDC_BTN_GET)->EnableWindow(TRUE);
            GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
        m_lRemoteHandle = -1;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig");
    }
}
