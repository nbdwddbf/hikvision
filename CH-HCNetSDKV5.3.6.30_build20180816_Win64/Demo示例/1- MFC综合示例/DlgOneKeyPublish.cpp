// DlgOneKeyPublish.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgOneKeyPublish.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgOneKeyPublish dialog


DlgOneKeyPublish::DlgOneKeyPublish(CWnd* pParent /*=NULL*/)
	: CDialog(DlgOneKeyPublish::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgOneKeyPublish)
	m_bDefine = FALSE;
	m_bRecordPublish = FALSE;
	m_ctEndData = 0;
	m_ctEndTime = 0;
	m_ctStartData = 0;
	m_ctStartTime = 0;
	m_bRecordMainStream = FALSE;
	m_bRecordSubStream = FALSE;
	m_bRecordStreamThree = FALSE;
	//}}AFX_DATA_INIT
	m_lUserID = 0;
	m_iDeviceIndex = 0;
	m_iStartChannel = 0;
	m_iMirrorNum = 0;
	m_lTranHandle = -1;
	memset(&m_struOnekeyPublish,0,sizeof(m_struOnekeyPublish));
}


void DlgOneKeyPublish::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgOneKeyPublish)
	DDX_Control(pDX, IDC_COMBO_RECORD_CHAN, m_comRecordChan);
	DDX_Check(pDX, IDC_CHK_DEFINE, m_bDefine);
	DDX_Check(pDX, IDC_CHK_RECORD_PUBLISH, m_bRecordPublish);
	DDX_DateTimeCtrl(pDX, IDC_END_DATA, m_ctEndData);
	DDX_DateTimeCtrl(pDX, IDC_END_TIME, m_ctEndTime);
	DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_ctStartData);
	DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_ctStartTime);
	DDX_Check(pDX, IDC_RECORD_MAIN_STREAM, m_bRecordMainStream);
	DDX_Check(pDX, IDC_RECORD_SUB_STREAM, m_bRecordSubStream);
	DDX_Check(pDX, IDC_RECORD_STREAM_THREE, m_bRecordStreamThree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgOneKeyPublish, CDialog)
	//{{AFX_MSG_MAP(DlgOneKeyPublish)
	ON_BN_CLICKED(IDC_BTN_PUBLISH, OnBtnPublish)
	ON_BN_CLICKED(IDC_BTN_RECORD_OK, OnBtnRecordOk)
	ON_CBN_SELCHANGE(IDC_COMBO_RECORD_CHAN, OnSelchangeComboRecordChan)
	ON_BN_CLICKED(IDC_CHK_DEFINE, OnChkDefine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgOneKeyPublish message handlers

BOOL DlgOneKeyPublish::OnInitDialog()
{
	CDialog::OnInitDialog();
    DWORD dwIndex = 0;
    m_comRecordChan.ResetContent();

    int i = 0;
    for ( i = 0; i< g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
    {
        if (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
        {
            m_comRecordChan.AddString(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
            m_comRecordChan.SetItemData(dwIndex, g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO);
            dwIndex++;
        }
    }
    
    for( i = 0; i < g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum;i++)
    {
        if (i == 0)
        {
            m_comRecordChan.AddString(g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].chChanName);
            m_comRecordChan.SetItemData(dwIndex, g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChannelNO);
            dwIndex++;
        }
    }

	m_comRecordChan.SetCurSel(0);
	CTime timeCur = CTime::GetCurrentTime();
	CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
	CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
	m_ctStartData = timeStart;
	m_ctStartTime = timeStart;
	m_ctEndData = timeStop;
	m_ctEndTime = timeStop;
	m_bGetNext = FALSE;
	UpdateData(FALSE);
	OnChkDefine();
	OnSelchangeComboRecordChan();
	return TRUE;
}
void DlgOneKeyPublish::SetText(CString cstemp)
{
	SetDlgItemText(IDC_PROCESS_STATIC,cstemp);
}

DWORD WINAPI DlgOneKeyPublish::GetPublishInfoThread(LPVOID lpArg)
{
	DlgOneKeyPublish *pThis = (DlgOneKeyPublish*)lpArg;
	DWORD dwProgress = 0;
	int iRet = 0;
    char szLan[128] = {0};
	while(pThis->m_bGetNext)
	{
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lTranHandle, &dwProgress, sizeof(DWORD));
		if(NET_SDK_GET_NEXT_STATUS_FAILED == iRet)
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "publish failed");
            g_StringLanType(szLan,"处理失败","Failed");
            pThis->SetText(szLan);
			break;
		}
        else if (NET_SDK_GET_NETX_STATUS_NEED_WAIT == iRet)
        {
            g_StringLanType(szLan,"处理中","Processing");
            pThis->SetText(szLan);
            Sleep(5);
            continue;
        }
        else if(iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
        {
            CString cstemp;
            char sStr[32];
            sprintf(sStr,"发布进度值：%d%",dwProgress);
            cstemp.Format("%s", sStr);
            pThis->SetText(cstemp);
            continue;
        }
        else if(iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
        {
            CString cstemp;
            DWORD dwProgress = 100;
            char sStr[32];
            sprintf(sStr,"发布进度值：%d%",dwProgress);
            cstemp.Format("%s", sStr);
            pThis->SetText(cstemp);
            g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "publish success");
            AfxMessageBox("success record publish cfg!");
            break;
        }
        else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
        {
            g_StringLanType(szLan,"出现异常","Exception");
            pThis->SetText(szLan);
        }
        else
        {
            
            g_StringLanType(szLan,"未知异常","Unkown Exception");
            pThis->SetText(szLan);
            break;
        }
	}

	if (-1 != pThis->m_lTranHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lTranHandle))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
			pThis->m_bGetNext = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_bGetNext = FALSE;
			pThis->m_lTranHandle = -1;
		}
	}
	
	return 0;
}

void DlgOneKeyPublish::OnBtnPublish() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struOnekeyPublish.byUseDefine = m_bDefine;
	if (m_struOnekeyPublish.byUseDefine == 1)
	{
		OnBtnRecordOk();
	}
	else
	{
		memset(&m_struOnekeyPublish,0,sizeof(m_struOnekeyPublish.byUseDefine));
	}
	m_struOnekeyPublish.struStartTime.wYear = m_ctStartData.GetYear();
	m_struOnekeyPublish.struStartTime.byMonth = m_ctStartData.GetMonth();
	m_struOnekeyPublish.struStartTime.byDay = m_ctStartData.GetDay();
	m_struOnekeyPublish.struStartTime.byHour = m_ctStartTime.GetHour();
	m_struOnekeyPublish.struStartTime.byMinute = m_ctStartTime.GetMinute();
	m_struOnekeyPublish.struStartTime.bySecond = m_ctStartTime.GetSecond();
	m_struOnekeyPublish.struEndTime.wYear = m_ctEndData.GetYear();
	m_struOnekeyPublish.struEndTime.byMonth = m_ctEndData.GetMonth();
	m_struOnekeyPublish.struEndTime.byDay = m_ctEndData.GetDay();
	m_struOnekeyPublish.struEndTime.byHour = m_ctEndTime.GetHour();
	m_struOnekeyPublish.struEndTime.byMinute = m_ctEndTime.GetMinute();
	m_struOnekeyPublish.struEndTime.bySecond = m_ctEndTime.GetSecond();
	m_struOnekeyPublish.dwSize = sizeof(m_struOnekeyPublish);

	char szLan[128] = {0};
	m_lTranHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_RECORDING_PUBLISH,&m_struOnekeyPublish,sizeof(m_struOnekeyPublish),NULL,this);
	if (m_lTranHandle  == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig Failed!");
		AfxMessageBox("record publish cfg Failed");
		return;
	}
	m_bGetNext = TRUE;
	DWORD dwThreadId;
	m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetPublishInfoThread), this, 0, &dwThreadId);
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig Success!");
	//MessageBox("success record publish cfg!");
// 	if(!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_RECORDING_PUBLISH,m_iStartChannel,&m_struOnekeyPublish,sizeof(m_struOnekeyPublish)))
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RECORDING_PUBLISH,  %s", "Set record publish faild");
// 		g_StringLanType(szLan, "发布失败", "Set record publish cfg failed");
// 		AfxMessageBox(szLan);
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RECORDING_PUBLISH,  %s", " publish sucess");
// 		g_StringLanType(szLan, "发布成功", "publish sucess");
// 		AfxMessageBox(szLan);
// 	}
}

void DlgOneKeyPublish::OnBtnRecordOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_comRecordChan.GetItemData(m_comRecordChan.GetCurSel());
    if (sel == g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[0].iChannelNO)
    {
        m_struOnekeyPublish.struDirectChanPublish.byPublish = m_bRecordPublish;
        m_struOnekeyPublish.struDirectChanPublish.dwStreamType |= (m_bRecordMainStream << 0);
        m_struOnekeyPublish.struDirectChanPublish.dwStreamType |= (m_bRecordSubStream << 1);
        m_struOnekeyPublish.struDirectChanPublish.dwStreamType |= (m_bRecordStreamThree << 2);
    }
    else
    {
        m_struOnekeyPublish.struChanPublish[sel -1].byPublish = m_bRecordPublish;
        m_struOnekeyPublish.struChanPublish[sel -1].dwStreamType |= (m_bRecordMainStream << 0);
        m_struOnekeyPublish.struChanPublish[sel -1].dwStreamType |= (m_bRecordSubStream << 1);
        m_struOnekeyPublish.struChanPublish[sel -1].dwStreamType |= (m_bRecordStreamThree << 2);
    }
}

void DlgOneKeyPublish::OnSelchangeComboRecordChan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_comRecordChan.GetItemData(m_comRecordChan.GetCurSel());

    if (sel == g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[0].iChannelNO)
    {
        m_bRecordPublish = m_struOnekeyPublish.struDirectChanPublish.byPublish;
        m_bRecordMainStream = m_struOnekeyPublish.struDirectChanPublish.dwStreamType&0x01;
        m_bRecordSubStream = (m_struOnekeyPublish.struDirectChanPublish.dwStreamType >> 1)&0x01;
        m_bRecordStreamThree = (m_struOnekeyPublish.struDirectChanPublish.dwStreamType >> 2)&0x01;
    }
    else
    {
        m_bRecordPublish = m_struOnekeyPublish.struChanPublish[sel-1].byPublish;
        m_bRecordMainStream = m_struOnekeyPublish.struChanPublish[sel-1].dwStreamType&0x01;
        m_bRecordSubStream = (m_struOnekeyPublish.struChanPublish[sel-1].dwStreamType >> 1)&0x01;
        m_bRecordStreamThree = (m_struOnekeyPublish.struChanPublish[sel-1].dwStreamType >> 2)&0x01;
    }
    UpdateData(FALSE);
}

void DlgOneKeyPublish::OnChkDefine() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (m_bDefine == 1)
    {
        //GetDlgItem(IDC_COMBO_RECORD_STREAM_TYPE)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBO_RECORD_CHAN)->EnableWindow(TRUE);
        GetDlgItem(IDC_RECORD_MAIN_STREAM)->EnableWindow(TRUE);
        GetDlgItem(IDC_RECORD_SUB_STREAM)->EnableWindow(TRUE);
        GetDlgItem(IDC_RECORD_STREAM_THREE)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHK_RECORD_PUBLISH)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_RECORD_OK)->EnableWindow(TRUE);
    }
    else
    {
        //	GetDlgItem(IDC_COMBO_RECORD_STREAM_TYPE)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_RECORD_CHAN)->EnableWindow(FALSE);
        GetDlgItem(IDC_RECORD_MAIN_STREAM)->EnableWindow(FALSE);
        GetDlgItem(IDC_RECORD_SUB_STREAM)->EnableWindow(FALSE);
        GetDlgItem(IDC_RECORD_STREAM_THREE)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHK_RECORD_PUBLISH)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_RECORD_OK)->EnableWindow(FALSE);
    }
    UpdateData(FALSE);
}