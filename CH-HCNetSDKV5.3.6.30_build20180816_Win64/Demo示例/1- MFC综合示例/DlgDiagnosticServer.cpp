// DlgDiagnosticServer.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "Picture.h"
#include "DlgDiagnosticServer.h"
#include "DlgVcaDevAccessCfg.h"
#include "DlgVqdPlan.h"
#include "DlgMonitorInfo.h"
#include "DlgSceneChangeUpdate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDiagnosticServer dialog

static CPicture *picture = NULL;

CDlgDiagnosticServer::CDlgDiagnosticServer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiagnosticServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiagnosticServer)
	m_sTotalPlanNum = 0;
	m_sRemainAbility = 0;
	m_sAbility = 0;
	m_byCPULoad = 0;
	m_byMEMLoad = 0;
 	m_dwPlanNum = 0;
	m_csVqdStreamID = _T("");
	m_csVqdUrl = _T("");
	m_dwPicLength = 0;
	m_iCurPlanNum = 0;
	m_lPlanCount = 0;
	m_csIP = _T("");
	m_dwPort = 0;
	//}}AFX_DATA_INIT
//	memset(g_struStreamIDPlanCfg, 0 ,sizeof(NET_DVR_STREAMID_PLAN_CFG)*64);	 
}


void CDlgDiagnosticServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiagnosticServer)
	DDX_Control(pDX, IDC_STATIC_PICVQD, m_VqdPic);
	DDX_Control(pDX, IDC_COMBO_STATUS, m_comboStatus);
	DDX_Text(pDX, IDC_EDIT_TOTALPLANNUM, m_sTotalPlanNum);
	DDX_Text(pDX, IDC_EDIT_REMAINABILITY, m_sRemainAbility);
	DDX_Text(pDX, IDC_EDIT_ABILITY, m_sAbility);
	DDX_Text(pDX, IDC_EDIT_CPULOAD, m_byCPULoad);
	DDX_Text(pDX, IDC_EDIT_MEMLOAD, m_byMEMLoad);
	DDX_Text(pDX, IDC_EDIT_VQD_STREAMID, m_csVqdStreamID);
	DDX_Text(pDX, IDC_EDIT_VQD_URL, m_csVqdUrl);
	DDX_Text(pDX, IDC_EDIT_PIC_LENGTH, m_dwPicLength);
	DDX_Text(pDX, IDC_EDIT_CURPLANNUM, m_iCurPlanNum);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiagnosticServer, CDialog)
	//{{AFX_MSG_MAP(CDlgDiagnosticServer)
	ON_BN_CLICKED(IDC_BTN_STATUS_GET, OnBtnStatusGet)
	ON_BN_CLICKED(IDC_BTN_DATASERVER_MANAGMENT, OnBtnDataserverManagment)
 	ON_BN_CLICKED(IDC_BTN_VQD_RESULT_GET, OnBtnVqdResultGet)
	ON_BN_CLICKED(IDC_BTN_VQD_PLAN, OnBtnVqdPlan)
	ON_BN_CLICKED(IDC_BTN_MONITOR_INFO, OnBtnMonitorInfo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SCENE_CHANGE_UPDATE, OnBtnSceneChangeUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDiagnosticServer message handlers

void CDlgDiagnosticServer::OnBtnStatusGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwStatus = 0;
	char szLan[128] = {0};
	memset(&m_struQueryStatus, 0 ,sizeof(NET_DVR_QUERY_STATUS));
	if (!NET_DVR_GetDeviceStatus(m_lServerID, NET_DVR_GET_MONITOR_VQD_STATUS, 1, NULL, 0, &dwStatus, &m_struQueryStatus, sizeof(m_struQueryStatus)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Get DiagnosticServer Status Err ");
		g_StringLanType(szLan, "获取诊断服务器状态失败", "Get DiagnosticServer Status Err!");
		AfxMessageBox(szLan);
		return;
	}
	m_byCPULoad = m_struQueryStatus.byCpuLoad;
	m_byMEMLoad = m_struQueryStatus.byMemLoad;
	m_sAbility = m_struQueryStatus.wAbility;
	m_sRemainAbility = m_struQueryStatus.wRemainAbility;
	m_sTotalPlanNum = m_struQueryStatus.wTotalPlanNum;
	m_iCurPlanNum = m_struQueryStatus.wCurPlanNum;
	UpdateData(FALSE);
}


void CDlgDiagnosticServer::OnBtnDataserverManagment() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaDevAccessCfg dt;
	dt.m_lServerID = m_lServerID;
	dt.m_iDevIndex = m_iDevIndex;
	dt.m_lChannel = m_lChannel;
	dt.DoModal();
}

void CDlgDiagnosticServer::OnBtnVqdResultGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	DWORD dwReturn = 0;
	NET_DVR_DOWN_LOAD_REQUEST struDownLoadRequest;
	memset(&struDownLoadRequest, 0, sizeof(NET_DVR_DOWN_LOAD_REQUEST));
		
	struDownLoadRequest.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);

	if (m_csVqdStreamID.GetLength() > 32)
	{
		g_StringLanType(szLan, "流ID参数错误!", "Stream ID parameter error!");
		AfxMessageBox(szLan);
		return;
	}
	if (m_csVqdUrl.GetLength() > 256)
	{
		g_StringLanType(szLan, "URL参数错误!", "URL parameter error!");
		AfxMessageBox(szLan);
		return;
	}
	memcpy(struDownLoadRequest.struStreamInfo.byID, m_csVqdStreamID, STREAM_ID_LEN);
	memcpy(struDownLoadRequest.sSnapShotURL, m_csVqdUrl, 256);

	NET_DVR_VQD_RESULT_INFO struResultInfo;
	memset(&struResultInfo, 0, sizeof(NET_DVR_VQD_RESULT_INFO));
	
	struResultInfo.pSnapShot = new char[700*1024];
	int dwSize = sizeof(struResultInfo);

	char* pTemp = new char[sizeof(NET_DVR_VQD_RESULT_INFO)+700*1024];
	if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_RECORD_INFO, 1, &struDownLoadRequest, sizeof(NET_DVR_DOWN_LOAD_REQUEST), &dwReturn, pTemp, sizeof(struResultInfo) + 700*1024))
	{
		g_StringLanType(szLan,"资源图片查询失败","Fail to Result of VQD INFO");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Fail to Result of VQD INFO");
		AfxMessageBox(szLan);
	}
	
	char csFileName[128] = "C:\\Test.jpg";
	LPNET_DVR_VQD_RESULT_INFO struResultInfoTemp = (LPNET_DVR_VQD_RESULT_INFO)pTemp;

	m_comboStatus.SetCurSel(struResultInfoTemp->byStatus);
	m_dwPicLength = struResultInfoTemp->dwPicLength;
	UpdateData(FALSE);

	if (struResultInfoTemp->byStatus == 0)
	{
		HANDLE lHandle = CreateFile(csFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (lHandle == INVALID_HANDLE_VALUE)
		{
			TRACE("create file failed! Error code:%d", WSAGetLastError());
			return;
		}  
		WriteFile(lHandle, struResultInfoTemp->pSnapShot, struResultInfoTemp->dwPicLength, &dwReturn, NULL);
		delete[] struResultInfo.pSnapShot;
		
		CloseHandle(lHandle);
		
		CRect rc;
		CDC* pDC = m_VqdPic.GetDC();
		m_VqdPic.GetClientRect(&rc);
		pDC->SetViewportOrg(rc.left, rc.top);
		rc.bottom = -rc.bottom;
		if (!picture)
		{
			picture = new CPicture;	
		}	
		picture->LoadPicture((char *)csFileName, pDC->m_hDC, abs(rc.Width()), abs(rc.Height()));
		
		DeleteFile(csFileName);
	}
	else
	{
		m_VqdPic.Invalidate();
	}

}

void CDlgDiagnosticServer::OnBtnVqdPlan() 
{
	// TODO: Add your control notification handler code here
	CDlgVqdPlan dt;
	dt.m_lServerID = m_lServerID;
	dt.m_iDevIndex = m_iDevIndex;
	dt.m_lChannel = m_lChannel;
	dt.DoModal();
}

void CDlgDiagnosticServer::OnBtnMonitorInfo() 
{
	// TODO: Add your control notification handler code here
	CDlgMonitorInfo dt;
	dt.m_lServerID = m_lServerID;
	dt.m_iDevIndex = m_iDevIndex;
	dt.m_lChannel = m_lChannel;
	dt.DoModal();
}

void CDlgDiagnosticServer::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	char szLan[33] = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_NETCFG_V30, m_lChannel, &m_struNetCfgV30, sizeof(m_struNetCfgV30), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETCFG_V30");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_NETCFG_V30");
    }
	
	m_dwPort = m_struNetCfgV30.wAlarmHostIpPort;
	memcpy(szLan, m_struNetCfgV30.struAlarmHostIpAddr.sIpV4, 16);
	m_csIP.Format(szLan);

	UpdateData(FALSE);
}

void CDlgDiagnosticServer::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	memset(&m_struNetCfgV30, 0, sizeof(m_struNetCfgV30));
	m_struNetCfgV30.dwSize = sizeof(m_struNetCfgV30);
	m_struNetCfgV30.wAlarmHostIpPort = m_dwPort;

	if (!CheckIPStr(m_csIP))
	{
		g_StringLanType(szLan, "IP无效!", "IP Parameter error!");
		AfxMessageBox(szLan);
		return;
	}

	if (m_csIP.GetLength() > 16)
	{
		g_StringLanType(szLan, "参数错误!", "Parameter error!");
		AfxMessageBox(szLan);
		return;
	}
	memcpy(m_struNetCfgV30.struAlarmHostIpAddr.sIpV4, m_csIP, 16);

	

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_NETCFG_V30, m_lChannel, &m_struNetCfgV30, sizeof(m_struNetCfgV30)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_NETCFG_V30");
		g_StringLanType(szLan, "设置错误!", "Fail to Set!");
		AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_NETCFG_V30");
    }
}

void CDlgDiagnosticServer::OnBtnSceneChangeUpdate() 
{
	// TODO: Add your control notification handler code here
	CDlgSceneChangeUpdate dt;
	dt.m_lServerID = m_lServerID;
	dt.m_iDevIndex = m_iDevIndex;
	dt.m_lChannel = m_lChannel;
	dt.DoModal();
}
