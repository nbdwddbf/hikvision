// DlgFishEye.cpp : implementation file
//

#include "stdafx.h"
#include "DlgFishEye.h"
#include "ClientDemo.h"
#include "DlgFishEyePtzControl.h"
#include "DlgFisheyeTrackCfg.h"
#include "DlgPtzTrackParamCfg.h"
#include "DlgFisheyeCorrect.h"
#include "DlgCenterPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFishEye dialog


CDlgFishEye::CDlgFishEye(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFishEye::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFishEye)
	m_bRealtimeOutput = FALSE;
	m_nCruiseGroupNo = 1;
	m_nCruiseGroupNumber = 0;
	m_nCruiseNumber = 0;
	m_nPresetGroupNo = 1;
	m_nPresetGroupNumber = 0;
	m_nPresetNumber = 0;
	m_byEnableEPTZ = FALSE;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_lChannel = -1;
	m_iDevIndex = -1;
}


void CDlgFishEye::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFishEye)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_COMBO_REALTIME_OUTPUT, m_comboRealTimeOutput);
	DDX_Control(pDX, IDC_LIST_PRESET, m_listPreset);
	DDX_Control(pDX, IDC_LIST_CRUISE_PATH, m_listCruisePath);
	DDX_Control(pDX, IDC_COMBO_STREAM_STATUS, m_comboStreamStatus);
	DDX_Control(pDX, IDC_COMBO_MOUNTTYPE, m_comboMountType);
	DDX_Control(pDX, IDC_COMBO_CORRECTMODE, m_comboCorrectMode);
	DDX_Check(pDX, IDC_CHECK_REALTIME_OUTPUT, m_bRealtimeOutput);
	DDX_Text(pDX, IDC_EDIT_CRUISE_GROUP_NO, m_nCruiseGroupNo);
	DDX_Text(pDX, IDC_EDIT_CRUISE_GROUP_NUMBER, m_nCruiseGroupNumber);
	DDX_Text(pDX, IDC_EDIT_CRUISE_NUMBER, m_nCruiseNumber);
	DDX_Text(pDX, IDC_EDIT_PRESET_GROUP_NO, m_nPresetGroupNo);
	DDX_Text(pDX, IDC_EDIT_PRESET_GROUP_NUMBER, m_nPresetGroupNumber);
	DDX_Text(pDX, IDC_EDIT_PRESET_NUMBER, m_nPresetNumber);
	DDX_Check(pDX, IDC_CHECK_EPTZ, m_byEnableEPTZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFishEye, CDialog)
	//{{AFX_MSG_MAP(CDlgFishEye)
	ON_BN_CLICKED(IDC_BTN_GET_CRUISE_GROUPINFO, OnBtnGetCruiseGroupinfo)
	ON_BN_CLICKED(IDC_BTN_GET_CRUISE_PATH_INFO, OnBtnGetCruisePathInfo)
	ON_BN_CLICKED(IDC_BTN_GET_PRESET_GROUPINFO, OnBtnGetPresetGroupinfo)
	ON_BN_CLICKED(IDC_BTN_GET_PRESET_PARAMINFO, OnBtnGetPresetParaminfo)
	ON_BN_CLICKED(IDC_BTN_GET_DISPLAY_CFG, OnBtnGetDisplayCfg)
	ON_BN_CLICKED(IDC_BTN_GET_STREAM_STATUS, OnBtnGetStreamStatus)
	ON_BN_CLICKED(IDC_BTN_PTZ_CONTROL, OnBtnPtzControl)
	ON_BN_CLICKED(IDC_BTN_SET_DISPLAY_CFG, OnBtnSetDisplayCfg)
	ON_BN_CLICKED(IDC_BTN_TRACKLINKAGE, OnBtnTracklinkage)
	ON_BN_CLICKED(IDC_BTN_PTZ_TRACKCFG, OnBtnPtzTrackcfg)
	ON_BN_CLICKED(IDC_BTN_FEC, OnBtnFec)
	ON_BN_CLICKED(IDC_BUTTON_EPTZ_GET, OnButtonEptzGet)
	ON_BN_CLICKED(IDC_BUTTON_EPTZ_SET, OnButtonEptzSet)
	ON_BN_CLICKED(IDC_BUTTON_CENTER_POINT, OnButtonCenterPoint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFishEye message handlers
BOOL CDlgFishEye::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_AddChanInfoToComBox(m_cmbChannel, m_iDevIndex);
    InitCtrlState();
	return TRUE;
}

void CDlgFishEye::InitCtrlState()
{   
	char szLan[32] = "\0";
	g_StringLanType(szLan,"Èí¼þÐ£Õý","Software");
	m_comboCorrectMode.ResetContent();
	m_comboCorrectMode.InsertString(0,szLan);
	m_comboCorrectMode.SetItemData(0,0);
	g_StringLanType(szLan,"Ð¾Æ¬Ð£Õý","Chip");
	m_comboCorrectMode.InsertString(1,szLan);
	m_comboCorrectMode.SetItemData(1,1);

	m_comboMountType.ResetContent();
	g_StringLanType(szLan,"Îü¶¥","Ceiling");
	m_comboMountType.InsertString(0,szLan);
	m_comboMountType.SetItemData(0,0);
	g_StringLanType(szLan,"×ÀÃæ","Desktop");
	m_comboMountType.InsertString(1,szLan);
	m_comboMountType.SetItemData(1,1);
	g_StringLanType(szLan,"Ç½Ãæ","Wall");
	m_comboMountType.InsertString(2,szLan);
	m_comboMountType.SetItemData(2,2);

	m_comboStreamStatus.ResetContent();
	m_comboStreamStatus.InsertString(0,_T("None"));
	m_comboStreamStatus.SetItemData(0,0);
	g_StringLanType(szLan,"ÓãÑÛ","Fish Eye");
	m_comboStreamStatus.InsertString(1,szLan);
	m_comboStreamStatus.SetItemData(1,FISHEYE_STREAM_MODE_FISHEYE);
	m_comboStreamStatus.InsertString(2,_T("PTZ"));
	m_comboStreamStatus.SetItemData(2,FISHEYE_STREAM_MODE_PTZ);
	g_StringLanType(szLan,"È«¾°","Panorama");
	m_comboStreamStatus.InsertString(3,szLan);
	m_comboStreamStatus.SetItemData(3,FISHEYE_STREAM_MODE_PANORAMA);
    
	g_StringLanType(szLan,"Ñ²º½Â·¾¶±àºÅ","Cruise Path  NO.");
	m_listCruisePath.InsertColumn(0,szLan,LVCFMT_LEFT,120);
	g_StringLanType(szLan,"Ñ²º½Â·¾¶µãºÅ","Cruise Point NO.");
	m_listCruisePath.InsertColumn(1,szLan,LVCFMT_LEFT,120);
	g_StringLanType(szLan,"Ô¤ÖÃµã±àºÅ","Preset NO.");
	m_listCruisePath.InsertColumn(2,szLan,LVCFMT_LEFT,100);
	g_StringLanType(szLan,"Ô¤ÖÃµã","Preset Point");
	m_listCruisePath.InsertColumn(3,szLan,LVCFMT_LEFT,150);
	g_StringLanType(szLan,"Í£ÁôÊ±¼ä","Dwell");
	m_listCruisePath.InsertColumn(4,szLan,LVCFMT_LEFT,80);
	g_StringLanType(szLan,"ËÙ¶È","Speed");
	m_listCruisePath.InsertColumn(5,szLan,LVCFMT_LEFT,80);
	m_listCruisePath.SetExtendedStyle(m_listCruisePath.GetExtendedStyle() |LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    
	g_StringLanType(szLan,"Ô¤ÖÃµãË÷Òý","Preset Index");
	m_listPreset.InsertColumn(0,szLan,LVCFMT_LEFT,120);
	g_StringLanType(szLan,"Ô¤ÖÃµã","Preset Point");
	m_listPreset.InsertColumn(1,szLan,LVCFMT_LEFT,200);
	m_listPreset.SetExtendedStyle(m_listPreset.GetExtendedStyle() |LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

}
void CDlgFishEye::OnBtnGetCruiseGroupinfo()
{   
	UpdateData(TRUE);

	DWORD dwReturn = 0;
	NET_DVR_PTZCRUISE_INFO strPtzCruiseinfo = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_PTZCRUISE_NUM, m_lChannel, &strPtzCruiseinfo, sizeof(strPtzCruiseinfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_PTZCRUISE_NUM");
        AfxMessageBox("Get ptz cruise group info failed");
		return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_PTZCRUISE_NUM");
    }
	m_nCruiseNumber = strPtzCruiseinfo.dwPtzCruiseNum;
	m_nCruiseGroupNumber = strPtzCruiseinfo.dwGroupNum;
	
	UpdateData(FALSE);
}

void CDlgFishEye::OnBtnGetCruisePathInfo() 
{
	UpdateData(TRUE);
    
	m_listCruisePath.DeleteAllItems();
	if (m_nCruiseNumber == 0)
	{
        AfxMessageBox("No cruise path available");
		return;
	}
	

	NET_DVR_PTZCRUISE_COND strPtzCruiseCond = {0};                  
	strPtzCruiseCond.dwChannel = m_lChannel; 
	strPtzCruiseCond.dwGroupNO = m_nCruiseGroupNo;
	strPtzCruiseCond.dwSize    = sizeof(strPtzCruiseCond);
	
	DWORD dwCount = 0;
	
	if (m_nCruiseGroupNumber <= 1)
	{
		dwCount = m_nCruiseNumber;
	}
	else
	{   
		int nGourpNum = max(m_nCruiseGroupNo,1);
		dwCount = m_nCruiseNumber - (nGourpNum - 1) * 64;  
	}
    
	if (dwCount > m_nCruiseNumber)
	{   
		AfxMessageBox("Group No. is not correct");
		return;
	}
	
	LPNET_DVR_PTZCRUISECFG pPtzCuisePointCfg = new NET_DVR_PTZCRUISECFG[dwCount];  
	DWORD *pStatus                           = new DWORD[dwCount];
	
	memset(pPtzCuisePointCfg, 0, dwCount * sizeof(NET_DVR_PTZCRUISECFG));
	memset(pStatus,           0, dwCount * sizeof(DWORD));
	
	BOOL bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PTZCRUISECFG, dwCount, &strPtzCruiseCond, sizeof(NET_DVR_PTZCRUISE_COND), pStatus, pPtzCuisePointCfg, dwCount*sizeof(NET_DVR_PTZCRUISECFG));
	if (!bRet)
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZCRUISECFG");
		AfxMessageBox("Get PTZ Cruise Path failed");
	}
	else
	{  
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZCRUISECFG");
		
		CString   strPtzCruiseIndex  = "";
		CString   strPtzCruisepoint  = "";
		CString   strPresetIndex     = ""; 
		CString   strPresetPoint     = ""; 
		CString   strDwell           = "";		
		CString   strSpeed           = "";
		
		NET_DVR_PTZCRUISECFG* pPtzCuisePointCfgTemp = pPtzCuisePointCfg;
		for(int j = 0; j< dwCount; j++)
		{
			for (int i = 0; i < MAX_PTZCRUISE_POINT_NUM; i++)
			{   
			
				strPtzCruiseIndex.Format("%d", (pPtzCuisePointCfgTemp->dwCruiseRoute + 1));
				strPtzCruisepoint.Format("%d", i + 1);
				strPresetIndex.Format("%d",(pPtzCuisePointCfgTemp->struCruisePoint[i].dwPresetIndex + 1));
				strPresetPoint.Format("( %.3f,%.3f )",pPtzCuisePointCfgTemp->struCruisePoint[i].struVcaPoint.fX,
					pPtzCuisePointCfgTemp->struCruisePoint[i].struVcaPoint.fY);
				strDwell.Format("%d", pPtzCuisePointCfgTemp->struCruisePoint[i].byDwell);
				strSpeed.Format("%d", pPtzCuisePointCfgTemp->struCruisePoint[i].bySpeed);
				
				int nIndex = j * MAX_PTZCRUISE_POINT_NUM + i;
				m_listCruisePath.InsertItem(nIndex,strPtzCruiseIndex);
				m_listCruisePath.SetItemText(nIndex, 1, strPtzCruisepoint);
				m_listCruisePath.SetItemText(nIndex, 2, strPresetIndex);
				m_listCruisePath.SetItemText(nIndex, 3, strPresetPoint);
				m_listCruisePath.SetItemText(nIndex, 4, strDwell);
				m_listCruisePath.SetItemText(nIndex, 5, strSpeed);
			}
			pPtzCuisePointCfgTemp++;
		}
	}
	
	delete [] pPtzCuisePointCfg;
	delete [] pStatus;
}

void CDlgFishEye::OnBtnGetPresetGroupinfo() 
{   
	UpdateData(TRUE);

	DWORD dwReturn = 0;
	char szLan[128] = {0};
	NET_DVR_PRESET_INFO strPrsetinfo = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_PRESET_NUM, m_lChannel, &strPrsetinfo, sizeof(strPrsetinfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_PRESET_NUM");
        AfxMessageBox("Get ptz preset group info failed");
		return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_PRESET_NUM");
    }
	m_nPresetNumber = strPrsetinfo.dwPresetNum;
	m_nPresetGroupNumber = strPrsetinfo.dwGroupNum;
	
	UpdateData(FALSE);	
}

void CDlgFishEye::OnBtnGetPresetParaminfo() 
{
	UpdateData(TRUE);

	m_listPreset.DeleteAllItems();
	if (m_nPresetNumber == 0)
	{
		AfxMessageBox("No preset points available");
		return;
	}
	
	NET_DVR_PRESET_COND struPresetCond = {0};
	struPresetCond.dwSize              = sizeof(struPresetCond);
	struPresetCond.dwChannel           = m_lChannel;
	struPresetCond.dwGroupNO           = m_nPresetGroupNo;
	
	DWORD dwCount = 0;
	if (m_nPresetGroupNumber <= 1)
	{
		dwCount = m_nPresetNumber;
	}
	else
	{   
		int nGourpNum = max(m_nPresetGroupNo,1);
		dwCount       = m_nPresetNumber - (nGourpNum - 1) * 64;
	}
	
	if (dwCount > m_nPresetNumber)
	{   
    	AfxMessageBox("Group No. is not correct");
		return;
	}
	
	NET_DVR_PRESETCFG*pPresetcfg = new NET_DVR_PRESETCFG[dwCount];
	DWORD            *pStatus    = new DWORD[dwCount];

	memset(pPresetcfg, 0, dwCount * sizeof(NET_DVR_PRESETCFG));
	memset(pStatus,    0, dwCount * sizeof(DWORD));
	
    BOOL bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PRESETCFG, dwCount, &struPresetCond, sizeof(NET_DVR_PRESET_COND), pStatus, pPresetcfg, dwCount*sizeof(NET_DVR_PRESETCFG));
	if (!bRet)
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRESETCFG");
		AfxMessageBox("Get preset points param failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PRESETCFG");
		
		CString   strPresetIndex = ""; 
		CString   strPresetPoint = "";

		for(int i = 0; i < dwCount; i++)
		{   
			strPresetIndex.Format("%d", pPresetcfg[i].dwPresetIndex + 1);
			strPresetPoint.Format("( %.3f,%.3f )", pPresetcfg[i].struVcaPoint.fX,pPresetcfg[i].struVcaPoint.fY);
			m_listPreset.InsertItem(i,strPresetIndex);	
			m_listPreset.SetItemText(i, 1, strPresetPoint);				
		}
	}
	
	delete [] pStatus;
	delete [] pPresetcfg;
	
}

void CDlgFishEye::OnBtnGetDisplayCfg() 
{
    UpdateData(TRUE);
	DWORD dwReturn = 0;

    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	
	NET_DVR_PREVIEW_DISPLAYCFG struPreviewDisplayCfg = {0};
	struPreviewDisplayCfg.dwSize = sizeof(struPreviewDisplayCfg);

    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PREVIEW_DISPLAYCFG, m_lChannel, &struPreviewDisplayCfg, sizeof(struPreviewDisplayCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_PREVIEW_DISPLAYCFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_PREVIEW_DISPLAYCFG");
		
		int i = 0;
		for (i = 0; i < m_comboCorrectMode.GetCount(); i++)
		{
			if (m_comboCorrectMode.GetItemData(i) == struPreviewDisplayCfg.byCorrectMode)
			{
				m_comboCorrectMode.SetCurSel(i);
				break;
			}
		}

		for (i = 0; i < m_comboMountType.GetCount(); i++)
		{
			if (m_comboMountType.GetItemData(i) == struPreviewDisplayCfg.byMountType)
			{
				m_comboMountType.SetCurSel(i);
				break;
			}
		}
		//m_bRealtimeOutput = struPreviewDisplayCfg.byRealTimeOutput;
		m_comboRealTimeOutput.SetCurSel(struPreviewDisplayCfg.byRealTimeOutput);
		UpdateData(FALSE);
    }
	
}


void CDlgFishEye::OnBtnSetDisplayCfg() 
{
	UpdateData(TRUE);
	NET_DVR_PREVIEW_DISPLAYCFG struPreviewDisplayCfg;
	m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	memset(&struPreviewDisplayCfg, 0, sizeof(struPreviewDisplayCfg));
	struPreviewDisplayCfg.dwSize =  sizeof(struPreviewDisplayCfg);
	struPreviewDisplayCfg.byMountType = m_comboMountType.GetItemData(m_comboMountType.GetCurSel());
	struPreviewDisplayCfg.byCorrectMode = m_comboCorrectMode.GetItemData(m_comboCorrectMode.GetCurSel());
	struPreviewDisplayCfg.byRealTimeOutput = m_comboRealTimeOutput.GetCurSel()/*m_bRealtimeOutput*/;
	
	if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PREVIEW_DISPLAYCFG, m_lChannel, &struPreviewDisplayCfg, sizeof(struPreviewDisplayCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PREVIEW_DISPLAYCFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PREVIEW_DISPLAYCFG");
	}
}

void CDlgFishEye::OnBtnGetStreamStatus() 
{
	NET_DVR_FISHEYE_STREAM_STATUS struStreamStatus = {0};
	struStreamStatus.dwSize = sizeof(struStreamStatus);

	DWORD dwStatus = 0;
	BOOL  bResult  = FALSE;
	
	if (!NET_DVR_GetDeviceStatus(m_lServerID,NET_DVR_GET_FISHEYE_STREAM_STATUS,1,&m_lChannel,sizeof(m_lChannel),
		&dwStatus,&struStreamStatus,sizeof(struStreamStatus)))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_GetDeviceStatus NET_DVR_GET_FISHEYE_STREAM_STATUS");
	}
	else
	{   
		bResult = TRUE;
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_GetDeviceStatus NET_DVR_GET_FISHEYE_STREAM_STATUS");
	}
	
	if (bResult)
	{   
		for (int i = 0; i < m_comboStreamStatus.GetCount(); i++)
		{
			if (m_comboStreamStatus.GetItemData(i) == struStreamStatus.byStreamMode)
			{
				m_comboStreamStatus.SetCurSel(i);
				break;
			}
		}
	}
	
}

void CDlgFishEye::OnButtonEptzGet() 
{
    // TODO: Add your control notification handler code here
    NET_DVR_EPTZ_CFG struEPTZCfg = {0};

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &struEPTZCfg;
    struCfg.dwOutSize = sizeof(struEPTZCfg);
    char szStatusBuf[ISAPI_STATUS_LEN];
    memset(szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_EPTZ_CFG, &struCfg))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_GET_EPTZ_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_GET_EPTZ_CFG");
    }
    m_byEnableEPTZ = struEPTZCfg.byEnableEPTZ;
    
    UpdateData(FALSE);
    
}

void CDlgFishEye::OnButtonEptzSet() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[512] = {0};
    NET_DVR_EPTZ_CFG struEPTZCfg = {0};

    struEPTZCfg.byEnableEPTZ = m_byEnableEPTZ;
    struEPTZCfg.dwSize = sizeof(struEPTZCfg);

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpInBuffer = &struEPTZCfg;
    struCfg.dwInSize = sizeof(struEPTZCfg);
    char szStatusBuf[ISAPI_STATUS_LEN];
    memset(szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_EPTZ_CFG, &struCfg))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_SET_EPTZ_CFG");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_SET_EPTZ_CFG");
    }
    
}

void CDlgFishEye::OnBtnPtzControl() 
{
	CDlgFishEyePtzControl dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_lChannel;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgFishEye::OnBtnTracklinkage() 
{
	CDlgFisheyeTrackCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = 1;
	dlg.DoModal();
}

void CDlgFishEye::OnBtnPtzTrackcfg() 
{
 	CDlgPtzTrackParamCfg dlg;
 	dlg.m_lServerID = m_lServerID;
 	dlg.m_lChannel = m_lChannel;
 	dlg.m_iDevIndex = m_iDevIndex;
 	dlg.DoModal();
}

void CDlgFishEye::OnBtnFec() 
{
	CDlgFisheyeCorrect dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_lChannel;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgFishEye::OnButtonCenterPoint() 
{
	// TODO: Add your control notification handler code here
    DlgCenterPoint dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_lChannel;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
	
}
