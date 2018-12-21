// DlgVcaITCTriggerCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaITCTriggerCfg.h"
#include "DrawFun.h"

#define UPLOAD_BLACK_WHITE_CONFIGURATION_FILE_TIMER 20
#define DOWNLOAD_BLACK_WHITE_CONFIGURATION_FILE_TIMER 21 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_POLYGON_POINT_NUM ITC_MAX_POLYGON_POINT_NUM
#define MIN_POLYGON_POINT_NUM 3

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITCTriggerCfg dialog

//CDlgVcaITCTriggerCfg *g_pDlgVcaITCTriggerCfg = NULL;

void CALLBACK g_DrawITCTriggerRgn(LONG lRealHandle, HDC hDc, DWORD dwUser)
{  
 	CDlgVcaITCTriggerCfg* pDlg = (CDlgVcaITCTriggerCfg*)dwUser;

 	if (pDlg != NULL)
 	{
 		pDlg->DrawRgnFun(hDc);
 	}
}

/*
DWORD WINAPI CDlgVcaITCTriggerCfg::UpLoadSendThread(LPVOID pParam)
{
    CDlgVcaITCTriggerCfg *pThis = ( CDlgVcaITCTriggerCfg*)pParam;
	char szOutPut[512] = {0};
	
	
	//发送文件内容
	
	BYTE *pSendData = new BYTE[MAX_BUFFER_LEN];
	DWORD iReadLen = 0;
	
	while(!pThis->m_bStop)
	{
		memset(pSendData, 0, MAX_BUFFER_LEN);
		ReadFile(pThis->m_hFile, pSendData, MAX_BUFFER_LEN, &iReadLen, NULL);
		
        if (iReadLen <= 0)
        {
            //OutputDebugString("iReadLen==0\n");
            break;
        }
		NET_DVR_SEND_PARAM_IN struSendParamIn = {0};
		struSendParamIn.pSendData = pSendData;
		struSendParamIn.dwSendDataLen = iReadLen;
		
        
		int iRet = NET_DVR_UploadSend(pThis->m_lUploadHandle, &struSendParamIn, NULL);
		sprintf(szOutPut, "send %d, iReadLen[%d]\n", iRet, iReadLen);
		OutputDebugString(szOutPut);
		if (iReadLen < MAX_BUFFER_LEN || iRet != iReadLen)
		{
			break;
		}
		
	}
	
    CloseHandle(pThis->m_hFile);
	delete [] pSendData;
	
	
	OutputDebugString("UpLoadSendThread exit \n");
    return FALSE;
}
*/


#if (_MSC_VER >= 1500)	//vs2008
void CDlgVcaITCTriggerCfg::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgVcaITCTriggerCfg::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
	char szLan[128] = {0};
	if (nIDEvent == DOWNLOAD_BLACK_WHITE_CONFIGURATION_FILE_TIMER)
	{
		DWORD dwProgress = 0;
		DWORD dwState = 0;
		dwState = NET_DVR_GetDownloadState(m_lDownloadHandle, &dwProgress);
		
		if (dwState == 1)
		{
			g_StringLanType(szLan, "下载成功", "Download successfully");
			m_strDownloadStatus.Format(szLan);
			
			
		}
		else if (dwState == 2)
		{
			g_StringLanType(szLan, "正在下载,已下载:%d", "Is Downloading,progress:%d");
			m_strDownloadStatus.Format(szLan, dwProgress);
		}
		else if (dwState == 3)
		{
			g_StringLanType(szLan, "下载失败", "Download failed");
			m_strDownloadStatus.Format(szLan);
		}
		else if (dwState == 19)
		{
			g_StringLanType(szLan, "文件格式不正确", "Upload Incorrent File Format");
			m_strUploadStatus.Format(szLan);
		}
		else if (dwState == 20)
		{
			g_StringLanType(szLan, "文件内容不正确", "Upload Incorrent File Content");
			m_strUploadStatus.Format(szLan);
		}
		else if (dwState == 4)
		{
			g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
			m_strDownloadStatus.Format(szLan);
			if (100 == dwProgress )
			{
				KillTimer(DOWNLOAD_BLACK_WHITE_CONFIGURATION_FILE_TIMER);
				g_StringLanType(szLan, "下载成功", "Download successfully");
				m_strDownloadStatus.Format(szLan);
			}
			
		}
		
		if (dwState != 2)
		{        
			KillTimer(DOWNLOAD_BLACK_WHITE_CONFIGURATION_FILE_TIMER);
			NET_DVR_StopDownload(m_lDownloadHandle);
			m_lDownloadHandle = -1;
		}
	}

	else if(nIDEvent == UPLOAD_BLACK_WHITE_CONFIGURATION_FILE_TIMER)
	{
		DWORD dwProgress = 0;
		int state = NET_DVR_GetUploadState(m_lUploadHandle, &dwProgress);
		
		if (state == 1)
		{
			g_StringLanType(szLan, "上传成功", "Upload successfully");
			m_strUploadStatus.Format(szLan);
		}
		else if (state == 2)
		{
			g_StringLanType(szLan, "正在上传", "Is uploading");
			m_strUploadStatus.Format(szLan);
		}
		else if (state == 3)
		{
			g_StringLanType(szLan, "上传失败", "Upload failed");
			m_strUploadStatus.Format(szLan);
		}
		else if (state == 4)
		{
			g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
			m_strUploadStatus.Format(szLan);
		}
		else if (state == 19)
		{
			g_StringLanType(szLan, "文件格式不正确", "Upload Incorrent File Format");
			m_strUploadStatus.Format(szLan);
		}
		else if (state == 20)
		{
			g_StringLanType(szLan, "文件内容不正确", "Upload Incorrent File Content");
			m_strUploadStatus.Format(szLan);
		}
		// 		g_StringLanType(szLan, "上传状态%d", "Upload successfully");
		// 		m_strUploadStatus.Format(szLan,state);
		if (state != 2)
		{        
			KillTimer(UPLOAD_BLACK_WHITE_CONFIGURATION_FILE_TIMER);
			NET_DVR_UploadClose(m_lUploadHandle);
			m_lUploadHandle = -1;
		}
	}

	
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}


CDlgVcaITCTriggerCfg::CDlgVcaITCTriggerCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaITCTriggerCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaITCTriggerCfg)
	m_bFarmVehicleRecog = FALSE;
	m_bMicroPlateRecog = FALSE;
	m_bPlateRecog = FALSE;
	m_bTriggerCfg = FALSE;
	m_bVehicleColorRecog = FALSE;
	m_bVehicleLogoRecog = FALSE;
	m_bViaVtcoil = FALSE;
	m_strProvinceName = _T("");
	m_bFuzzyRecog = FALSE;
	m_bMotocarRecog = FALSE;
	m_nAssociateLaneNO = 0;
	m_nLaneNum = 0;
	m_szSceneName = _T("");
	m_bEnable = FALSE;
	m_bIpcHvt = FALSE;
	m_dwPlatePixelWidthMax = 0;
	m_dwPlatePixelWidthMin = 0;
    m_szFilePath = _T("");
	m_strDownloadStatus = _T("");
	m_strUploadStatus = _T("");
	//}}AFX_DATA_INIT

	memset(&m_struItcTriggerCfg,0,sizeof(m_struItcTriggerCfg));
	memset(&m_struCalibration,0,sizeof(m_struCalibration));
	memset(&m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    m_nCurDrawType         =     DRAW_TYPE_NONE;
	m_bFirstDrawLaneBoundary = FALSE;
	m_bFirstDrawLaneLine = FALSE;
    m_bFirstDrawSnapLine = FALSE;
	m_nCurLaneIndex = 0;
	m_nDrawPointNum = 0;
	m_lPlayHandle = -1;
	m_iTriggerMode = 0;
	m_lDownloadHandle = -1;
	m_szFilePath.Format("%s\\BlackWhiteCfg.xls", g_struLocalParam.chRemoteCfgSavePath);
	m_timerHandle = -1;
	m_lUploadHandle = -1;
	m_bStop = FALSE;
    m_bCountryIndex = 0;
}

CDlgVcaITCTriggerCfg::~CDlgVcaITCTriggerCfg()
{
//	StopRealPlay();
}

void CDlgVcaITCTriggerCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgVcaITCTriggerCfg)
    DDX_Control(pDX, IDC_COMBO_REGION_TYPE, m_comRegion);
    DDX_Control(pDX, IDC_COMBO_PROVINCE_TYPE, m_comProvince);
    DDX_Control(pDX, IDC_COMBO_DETSCENE_ID, m_comDetSceneID);
    DDX_Control(pDX, IDC_COMBO_IO_NO, m_comIONo);
    DDX_Control(pDX, IDC_COMBO_TRIGGER_TYPE, m_comTriggerType);
    DDX_Control(pDX, IDC_COMBO_RELATE_CHAN, m_comRelateChan);
    DDX_Control(pDX, IDC_COMBO_SOURCE_TYPE, m_comSourceType);
    DDX_Control(pDX, IDC_COMBO_TRIGGER_MODE, m_comTriggerMode);
    DDX_Control(pDX, IDC_COMBO_CHAN, m_comChan);
    DDX_Control(pDX, IDC_COMBO_VEHICLE_TYPE, m_comboVehicleType);
    DDX_Control(pDX, IDC_COMBO_TIME_TYPE, m_comboTimeType);
    DDX_Control(pDX, IDC_COMBO_SCENE_TYPE, m_comboSceneType);
    DDX_Control(pDX, IDC_COMBO_RECOG_TYPE, m_comboRecogType);
    DDX_Control(pDX, IDC_COMBO_RECOG_POS, m_comboRecogPos);
    DDX_Control(pDX, IDC_COMBO_LOCATE_TYPE, m_comboLocateType);
    DDX_Control(pDX, IDC_COMBO_LANE_USEAGETYPE, m_comboLaneUseageType);
    DDX_Control(pDX, IDC_COMBO_LANE_NUMBER, m_comboLaneNumber);
    DDX_Control(pDX, IDC_COMBO_LANE_DIRECTION, m_comboLaneDirection);
    DDX_Control(pDX, IDC_COMBO_DRIVE_DIRECTION, m_comboDriveDirection);
    DDX_Control(pDX, IDC_COMBO_LANE_CAR_DRIVE_DIRECT, m_comboCarDriveDirect);
    DDX_Check(pDX, IDC_CHECK_FARM_VEHICLE_RECOG, m_bFarmVehicleRecog);
    DDX_Check(pDX, IDC_CHECK_MICRO_PLATE_RECOG, m_bMicroPlateRecog);
    DDX_Check(pDX, IDC_CHECK_PLATE_RECOG, m_bPlateRecog);
    DDX_Check(pDX, IDC_CHECK_TRIGGER_CFG, m_bTriggerCfg);
    DDX_Check(pDX, IDC_CHECK_VEHICLE_COLOR_RECOG, m_bVehicleColorRecog);
    DDX_Check(pDX, IDC_CHECK_VEHICLE_LOGO_RECOG, m_bVehicleLogoRecog);
    DDX_Check(pDX, IDC_CHECK_VIA_VTCOIL, m_bViaVtcoil);
    DDX_Text(pDX, IDC_EDIT_PROVINCE_NAME, m_strProvinceName);
    DDX_Check(pDX, IDC_CHECK_FUZZY_RECOG, m_bFuzzyRecog);
    DDX_Check(pDX, IDC_CHECK_MOTOCAR_RECOG, m_bMotocarRecog);
    DDX_Text(pDX, IDC_EDIT_ASSOCIATE_LANENO, m_nAssociateLaneNO);
    DDX_Text(pDX, IDC_EDIT_LANE_NUM, m_nLaneNum);
    DDX_Text(pDX, IDC_EDIT_SCENENAME, m_szSceneName);
    DDX_Text(pDX, IDC_EDIT_PIXELWIDTH_MAX, m_dwPlatePixelWidthMax);
    DDX_Text(pDX, IDC_EDIT_PIXELWIDTH_MIN, m_dwPlatePixelWidthMin);
    DDX_Text(pDX, IDC_EDIT_FILEPATH, m_szFilePath);
    DDX_Text(pDX, IDC_STATIC_DOWNLOAD_STATE, m_strDownloadStatus);
    DDX_Text(pDX, IDC_STATIC_UPLOAD_STATE, m_strUploadStatus);
    DDX_Text(pDX, IDC_EDIT_DELAY_TIME, m_wDelayTime);
    DDX_Control(pDX, IDC_COMBO_ROAD_TYPE, m_cmbRoadType);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_COUNTRY_INDEX, m_bCountryIndex);
}


BEGIN_MESSAGE_MAP(CDlgVcaITCTriggerCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaITCTriggerCfg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_DRAW_LANE_BOUNDARY_LINE, OnBtnDrawLaneBoundaryLine)
	ON_BN_CLICKED(IDC_BTN_DRAW_LANE_LINE, OnBtnDrawLaneLine)
	ON_BN_CLICKED(IDC_BTN_DRAW_PLATE_RECOG_RGN, OnBtnDrawPlateRecogRgn)
	ON_CBN_SELCHANGE(IDC_COMBO_LANE_NUMBER, OnSelchangeComboLaneNumber)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_END_DRAW, OnBtnEndDraw)
	ON_CBN_SELCHANGE(IDC_COMBO_TRIGGER_MODE, OnSelchangeComboTriggerMode)
	ON_CBN_SELCHANGE(IDC_COMBO_SOURCE_TYPE, OnSelchangeComboSourceType)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_GET_CURTRIGGERMODE, OnBtnGetCurtriggermode)
	ON_BN_CLICKED(IDC_BTN_SET_CURTRIGGERMODE, OnBtnSetCurtriggermode)
	ON_BN_CLICKED(IDC_BTN_GET_CALIBRATION, OnBtnGetCalibration)
	ON_BN_CLICKED(IDC_BTN_BLACKWHITELST_UPLOAD, OnBtnBlackwhitelstUpload)
	ON_BN_CLICKED(IDC_BTN_BLACKWHITELST_DOWNLOAD, OnBtnBlackwhitelstDownload)
	ON_BN_CLICKED(IDC_BTN_BLACKWHITELST_DOWNLOAD_STOP, OnBtnBlackwhitelstDownloadStop)
	ON_BN_CLICKED(IDC_BTN_BLACKWHITELST_UPLOAD_STOP, OnBtnBlackwhitelstUploadStop)
	ON_BN_CLICKED(IDC_BTN_BLACKWHITELST_BROWSE, OnBtnBlackwhitelistBrowse)
	ON_CBN_SELCHANGE(IDC_COMBO_ROAD_TYPE, OnSelchangeComboRoadType)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_DRAW_SNAP_LINE, &CDlgVcaITCTriggerCfg::OnBnClickedBtnDrawSnapLine)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITCTriggerCfg message handlers
BOOL CDlgVcaITCTriggerCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//g_pDlgVcaITCTriggerCfg = this;
	g_AddChanInfoToComBox(m_comChan,m_iDevIndex);
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);
//	m_comTriggerMode.SetCurSel(0);
//	OnSelchangeComboTriggerMode();
//	m_comSourceType.SetCurSel(0);
//	OnSelchangeComboSourceType();
//	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawITCTriggerRgn,this);
// 	NET_DVR_CURTRIGGERMODE struTrigCfg = {0};
// 	DWORD dwReturn = 0;
// 	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_CURTRIGGERMODE, m_lChannel, &struTrigCfg, sizeof(struTrigCfg), &dwReturn))
//     {
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITC_GET_TRIGGERCFG Chan[%d]", m_lChannel);
//         return FALSE;
//     }
// 
// 	if (struTrigCfg.dwTriggerType == ITC_POST_MPR_TYPE )
// 	{
// 		m_comTriggerMode.SetCurSel(1);
// 	} 
// 	else if (struTrigCfg.dwTriggerType == IPC_POST_HVT_TYPE)
// 	{
//         m_comTriggerMode.SetCurSel(2);
// 	}
//     else
// 	{
// 		m_comTriggerMode.SetCurSel(0);
// 	}

    m_comTriggerMode.SetCurSel(0);
	m_comDetSceneID.SetCurSel(0);

    m_szFilePath = "C://test.xls";

    OnBtnGetCurtriggermode();

	OnSelchangeComboTriggerMode();

	//StartRealPlay();
	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawITCTriggerRgn,this);

	InitCtrlState();

	GetITCTriggerCfg();
	LoadWndContent();
	GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(FALSE);
	return TRUE;
}

void CDlgVcaITCTriggerCfg::OnDestroy()
{   
	StopRealPlay();
	CDialog::OnDestroy();
}

// long CDlgVcaITCTriggerCfg::StartRealPlay()
// {
// 	NET_DVR_CLIENTINFO struPlay;
// 	struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
// 	struPlay.lChannel 	= m_lChannel; 
// 	struPlay.lLinkMode 	= 0;
// 	struPlay.sMultiCastIP = "";	
// 	if (m_lPlayHandle >= 0)
//     {
//         NET_DVR_StopRealPlay(m_lPlayHandle);
//     }
// 	m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE); 
// 	BOOL bRet = FALSE;
// 	if (m_lPlayHandle < 0)
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
// 		AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
// 		bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawITCTriggerRgn, 0);//DC Draw callback
// 	}
// 
//     return m_lPlayHandle;
// }
// 
// BOOL CDlgVcaITCTriggerCfg::StopRealPlay()
// {
//     BOOL bRet;
//     if (m_lPlayHandle >= 0)
//     {
//         bRet = NET_DVR_StopRealPlay(m_lPlayHandle);
//         if (!bRet)
//         {
//             AfxMessageBox("Fail to stop preview");
//         }
//     }
//     return bRet;
// }


void CDlgVcaITCTriggerCfg::OnBtnDrawLaneBoundaryLine() 
{

	if (0 == m_iTriggerMode)
	{
		NET_ITC_LINE& struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneBoundaryLine;
		memset(&struLaneBoundaryLine,0,sizeof(struLaneBoundaryLine));
		m_bFirstDrawLaneBoundary = TRUE;
		m_nCurDrawType = DRAW_TYPE_LANE_BOUNDARY_LINE;
	}
	else if (1 == m_iTriggerMode)
	{
		NET_ITC_LINE& struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneBoundaryLine;
		memset(&struLaneBoundaryLine,0,sizeof(struLaneBoundaryLine));
		m_bFirstDrawLaneBoundary = TRUE;
		m_nCurDrawType = DRAW_TYPE_LANE_BOUNDARY_LINE;
	}
	else if (2 == m_iTriggerMode)
    {
        NET_ITC_LINE& struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneBoundaryLine;
        memset(&struLaneBoundaryLine,0,sizeof(struLaneBoundaryLine));
        m_bFirstDrawLaneBoundary = TRUE;
		m_nCurDrawType = DRAW_TYPE_LANE_BOUNDARY_LINE; 
    }

}

void CDlgVcaITCTriggerCfg::OnBtnDrawLaneLine() 
{
	if (0 == m_iTriggerMode)
	{
		NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[m_nCurLaneIndex].struLaneLine;
		memset(&struLaneLine,0,sizeof(struLaneLine));
		m_bFirstDrawLaneLine = TRUE;
		m_nCurDrawType = DRAW_TYPE_LANE_LINE;
	}
	else if (1 == m_iTriggerMode)
	{
		NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[m_nCurLaneIndex].struLaneLine;
		memset(&struLaneLine,0,sizeof(struLaneLine));
		m_bFirstDrawLaneLine = TRUE;
		m_nCurDrawType = DRAW_TYPE_LANE_LINE;
	}
   	else if (2 == m_iTriggerMode)
    {
        NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[m_nCurLaneIndex].struLaneLine;
        memset(&struLaneLine,0,sizeof(struLaneLine));
        m_bFirstDrawLaneLine = TRUE;
		m_nCurDrawType = DRAW_TYPE_LANE_LINE;
    }
}

void CDlgVcaITCTriggerCfg::OnBtnDrawPlateRecogRgn() 
{   
	if (0 == m_iTriggerMode)
	{
		NET_ITC_POLYGON&  struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[m_nCurLaneIndex].struPlateRecog;
		memset(&struPlateRecog,0,sizeof(struPlateRecog));
		m_nCurDrawType = DRAW_TYPE_PLATE_RECOG_RGN;
		m_nDrawPointNum = 0;
	}
	else if (1 == m_iTriggerMode)
	{
		NET_ITC_POLYGON&  struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[m_nCurLaneIndex].struPlateRecog;
		memset(&struPlateRecog,0,sizeof(struPlateRecog));
		m_nCurDrawType = DRAW_TYPE_PLATE_RECOG_RGN;
		m_nDrawPointNum = 0;
	}
    else if (2 == m_iTriggerMode)
    {
        NET_ITC_POLYGON&  struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[m_nCurLaneIndex].struPlateRecog;
        memset(&struPlateRecog,0,sizeof(struPlateRecog));
        m_nCurDrawType = DRAW_TYPE_PLATE_RECOG_RGN;
		m_nDrawPointNum = 0;
    }
}

void CDlgVcaITCTriggerCfg::OnBtnEndDraw() 
{   
	if (m_nCurDrawType == DRAW_TYPE_PLATE_RECOG_RGN)
	{
		
		if (0 == m_iTriggerMode)
		{
			NET_ITC_POLYGON&  struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[m_nCurLaneIndex].struPlateRecog;
			if (m_nDrawPointNum >= MIN_POLYGON_POINT_NUM)
			{
				struPlateRecog.dwPointNum = m_nDrawPointNum;
			}
			else
			{
				
				memset(&struPlateRecog,0,sizeof(struPlateRecog));
			}
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
		else if (1 == m_iTriggerMode)
		{
			NET_ITC_POLYGON&  struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[m_nCurLaneIndex].struPlateRecog;
			if (m_nDrawPointNum >= MIN_POLYGON_POINT_NUM)
			{
				struPlateRecog.dwPointNum = m_nDrawPointNum;
			}
			else
			{
				
				memset(&struPlateRecog,0,sizeof(struPlateRecog));
			}
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
        else if (2 == m_iTriggerMode)
		{
            NET_ITC_POLYGON&  struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[m_nCurLaneIndex].struPlateRecog;
            if (m_nDrawPointNum >= MIN_POLYGON_POINT_NUM)
            {
                struPlateRecog.dwPointNum = m_nDrawPointNum;
            }
            else
            {
                
                memset(&struPlateRecog,0,sizeof(struPlateRecog));
            }
			m_nCurDrawType = DRAW_TYPE_NONE;
        }
	}
}

void CDlgVcaITCTriggerCfg::OnSelchangeComboLaneNumber() 
{
	int nCurSel = m_comboLaneNumber.GetCurSel();
	if (nCurSel != CB_ERR)
	{   
		UpdateData(TRUE);
		SaveViaLaneWndContent(m_nCurLaneIndex);
		m_nCurLaneIndex = nCurSel;
		LoadViaLaneWndContent(nCurSel);
		UpdateData(FALSE);
	}
}

void CDlgVcaITCTriggerCfg::OnBtnSave() 
{
	SaveWndContent();
    
	char szError[32] = "\0";
	if (SetITCTriggerCfg())
	{
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}


void CDlgVcaITCTriggerCfg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags,point);

	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	if (m_nCurDrawType == DRAW_TYPE_NONE)
	{
		return;
	}
	
	if (m_nCurDrawType == DRAW_TYPE_LANE_LINE)
	{
		if (0 == m_iTriggerMode)
		{
			NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[m_nCurLaneIndex].struLaneLine;
			if (m_bFirstDrawLaneLine)
			{
				struLaneLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
				struLaneLine.struLine.struEnd.fX   = struLaneLine.struLine.struStart.fX;
				struLaneLine.struLine.struEnd.fY   = struLaneLine.struLine.struStart.fY;
				m_bFirstDrawLaneLine= FALSE;
			}
			else
			{   
				struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
				m_nCurDrawType = DRAW_TYPE_NONE;
			}
		}
		else if (1 == m_iTriggerMode)
		{
			NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[m_nCurLaneIndex].struLaneLine;
			if (m_bFirstDrawLaneLine)
			{
				struLaneLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
				struLaneLine.struLine.struEnd.fX   = struLaneLine.struLine.struStart.fX;
				struLaneLine.struLine.struEnd.fY   = struLaneLine.struLine.struStart.fY;
				m_bFirstDrawLaneLine= FALSE;
			}
			else
			{   
				struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
				m_nCurDrawType = DRAW_TYPE_NONE;
			}
		}
		else if (2 == m_iTriggerMode)
        {
            NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[m_nCurLaneIndex].struLaneLine;
            if (m_bFirstDrawLaneLine)
            {
                struLaneLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
                struLaneLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
                struLaneLine.struLine.struEnd.fX   = struLaneLine.struLine.struStart.fX;
                struLaneLine.struLine.struEnd.fY   = struLaneLine.struLine.struStart.fY;
                m_bFirstDrawLaneLine= FALSE;
            }
            else
            {   
                struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
                struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
                m_nCurDrawType = DRAW_TYPE_NONE;
			}
        }
	
	}
	else if (m_nCurDrawType == DRAW_TYPE_LANE_BOUNDARY_LINE)
	{   
		if (0 == m_iTriggerMode)
		{
			NET_ITC_LINE& struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneBoundaryLine;
			if (m_bFirstDrawLaneBoundary)
			{
				struLaneBoundaryLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneBoundaryLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
				struLaneBoundaryLine.struLine.struEnd.fX   = struLaneBoundaryLine.struLine.struStart.fX;
				struLaneBoundaryLine.struLine.struEnd.fY   = struLaneBoundaryLine.struLine.struStart.fY;
				m_bFirstDrawLaneBoundary = FALSE;
			}
			else
			{   
				struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
				m_nCurDrawType = DRAW_TYPE_NONE;
			}
		}
		else if (1 == m_iTriggerMode)
		{
			NET_ITC_LINE& struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneBoundaryLine;
			if (m_bFirstDrawLaneBoundary)
			{
				struLaneBoundaryLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneBoundaryLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
				struLaneBoundaryLine.struLine.struEnd.fX   = struLaneBoundaryLine.struLine.struStart.fX;
				struLaneBoundaryLine.struLine.struEnd.fY   = struLaneBoundaryLine.struLine.struStart.fY;
				m_bFirstDrawLaneBoundary = FALSE;
			}
			else
			{   
				struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
				m_nCurDrawType = DRAW_TYPE_NONE;
			}
		}
        else if (2 == m_iTriggerMode)
        {
            NET_ITC_LINE& struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneBoundaryLine;
            if (m_bFirstDrawLaneBoundary)
            {
                struLaneBoundaryLine.struLine.struStart.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
                struLaneBoundaryLine.struLine.struStart.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
                struLaneBoundaryLine.struLine.struEnd.fX   = struLaneBoundaryLine.struLine.struStart.fX;
                struLaneBoundaryLine.struLine.struEnd.fY   = struLaneBoundaryLine.struLine.struStart.fY;
                m_bFirstDrawLaneBoundary = FALSE;
            }
            else
            {   
                struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
                struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
                m_nCurDrawType = DRAW_TYPE_NONE;
			}
        }
	}
	else if (m_nCurDrawType == DRAW_TYPE_PLATE_RECOG_RGN)
	{
		if (m_nDrawPointNum >= MAX_POLYGON_POINT_NUM)
		{
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
		else
		{   
			if (0 == m_iTriggerMode)
			{
				NET_ITC_POLYGON&  struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[m_nCurLaneIndex].struPlateRecog;
				if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//按CTRL键 画矩形图
				{
					if (m_nDrawPointNum == 1)
					{
						struPlateRecog.struPos[m_nDrawPointNum].fX = struPlateRecog.struPos[m_nDrawPointNum-1].fX;
						struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						
						struPlateRecog.struPos[m_nDrawPointNum+1].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
						struPlateRecog.struPos[m_nDrawPointNum+1].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						
						struPlateRecog.struPos[m_nDrawPointNum+2].fX = struPlateRecog.struPos[m_nDrawPointNum+1].fX;
						struPlateRecog.struPos[m_nDrawPointNum+2].fY = struPlateRecog.struPos[0].fY;
						
						m_nDrawPointNum = 4;
					}
					else if (m_nDrawPointNum == 0)
					{
						struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
						struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						m_nDrawPointNum = 1;
					}
				}
				else
				{
					struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
					struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
					m_nDrawPointNum++;
				}
			}
			else if (1 == m_iTriggerMode)
			{
				NET_ITC_POLYGON&  struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[m_nCurLaneIndex].struPlateRecog;
				if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//按CTRL键 画矩形图
				{
					if (m_nDrawPointNum == 1)
					{
						struPlateRecog.struPos[m_nDrawPointNum].fX = struPlateRecog.struPos[m_nDrawPointNum-1].fX;
						struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						
						struPlateRecog.struPos[m_nDrawPointNum+1].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
						struPlateRecog.struPos[m_nDrawPointNum+1].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						
						struPlateRecog.struPos[m_nDrawPointNum+2].fX = struPlateRecog.struPos[m_nDrawPointNum+1].fX;
						struPlateRecog.struPos[m_nDrawPointNum+2].fY = struPlateRecog.struPos[0].fY;
						
						m_nDrawPointNum = 4;
					}
					else if (m_nDrawPointNum == 0)
					{
						struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
						struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
						m_nDrawPointNum = 1;
					}
				}
				else
				{
					struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
					struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
					m_nDrawPointNum++;
				}
			}
            else if (2 == m_iTriggerMode)
            {
                NET_ITC_POLYGON&  struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[m_nCurLaneIndex].struPlateRecog;
                if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//按CTRL键 画矩形图
                {
                    if (m_nDrawPointNum == 1)
                    {
                        struPlateRecog.struPos[m_nDrawPointNum].fX = struPlateRecog.struPos[m_nDrawPointNum-1].fX;
                        struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                        
                        struPlateRecog.struPos[m_nDrawPointNum+1].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                        struPlateRecog.struPos[m_nDrawPointNum+1].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                        
                        struPlateRecog.struPos[m_nDrawPointNum+2].fX = struPlateRecog.struPos[m_nDrawPointNum+1].fX;
                        struPlateRecog.struPos[m_nDrawPointNum+2].fY = struPlateRecog.struPos[0].fY;
                        
                        m_nDrawPointNum = 4;
                    }
                    else if (m_nDrawPointNum == 0)
                    {
                        struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                        struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                        m_nDrawPointNum = 1;
                    }
                }
                else
                {
                    struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                    struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                    m_nDrawPointNum++;
				}
            }
		}
	}
    else if (m_nCurDrawType == DRAW_TYPE_SNAP_LINE)
    {
        if (1 == m_iTriggerMode)
        {
            NET_VCA_LINE& struSnapLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struSnapLine;
            if (m_bFirstDrawSnapLine)
            {
                struSnapLine.struStart.fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                struSnapLine.struStart.fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
                struSnapLine.struEnd.fX = struSnapLine.struStart.fX;
                struSnapLine.struEnd.fY = struSnapLine.struStart.fY;
                m_bFirstDrawSnapLine = FALSE;
            }
            else
            {
                struSnapLine.struEnd.fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                struSnapLine.struEnd.fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
                m_nCurDrawType = DRAW_TYPE_NONE;
            }
        }
        else if (2 == m_iTriggerMode)
        {
            NET_VCA_LINE& struSnapLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struSnapLine;
            if (m_bFirstDrawSnapLine)
            {
                struSnapLine.struStart.fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                struSnapLine.struStart.fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
                struSnapLine.struEnd.fX = struSnapLine.struStart.fX;
                struSnapLine.struEnd.fY = struSnapLine.struStart.fY;
                m_bFirstDrawSnapLine = FALSE;
            }
            else
            {
                struSnapLine.struEnd.fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                struSnapLine.struEnd.fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
                m_nCurDrawType = DRAW_TYPE_NONE;
            }
        }
    }
}

void CDlgVcaITCTriggerCfg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnRButtonDown(nFlags,point);
	
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	if (m_nCurDrawType == DRAW_TYPE_NONE)
	{
		return;
	}
	
	if (m_nCurDrawType == DRAW_TYPE_LANE_BOUNDARY_LINE)
	{   
		m_bFirstDrawLaneBoundary = FALSE;
	}
	else if (m_nCurDrawType == DRAW_TYPE_LANE_LINE)
	{
		m_bFirstDrawLaneLine = FALSE;
	}
    else if (m_nCurDrawType == DRAW_TYPE_SNAP_LINE)
    {
        m_bFirstDrawSnapLine = FALSE;
    }
	else if (m_nCurDrawType == DRAW_TYPE_PLATE_RECOG_RGN)
	{  
		if (0 == m_iTriggerMode)
		{
			NET_ITC_POLYGON& struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[m_nCurLaneIndex].struPlateRecog;
			if (m_nDrawPointNum < MIN_POLYGON_POINT_NUM)
			{
				memset(&struPlateRecog,0,sizeof(struPlateRecog));
			}
			else
			{   
				struPlateRecog.dwPointNum = m_nDrawPointNum;
			}
		}
		else if (1 == m_iTriggerMode)
		{
			NET_ITC_POLYGON& struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[m_nCurLaneIndex].struPlateRecog;
			if (m_nDrawPointNum < MIN_POLYGON_POINT_NUM)
			{
				memset(&struPlateRecog,0,sizeof(struPlateRecog));
			}
			else
			{   
				struPlateRecog.dwPointNum = m_nDrawPointNum;
			}
		}
        else if (2 == m_iTriggerMode)
        {
            NET_ITC_POLYGON& struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[m_nCurLaneIndex].struPlateRecog;
            if (m_nDrawPointNum < MIN_POLYGON_POINT_NUM)
            {
                memset(&struPlateRecog,0,sizeof(struPlateRecog));
            }
            else
            {   
                struPlateRecog.dwPointNum = m_nDrawPointNum;
			}
        }
	}
	m_nCurDrawType = DRAW_TYPE_NONE;	
}

void CDlgVcaITCTriggerCfg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags,point);
	
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	if (m_nCurDrawType == DRAW_TYPE_NONE)
	{
		return;
	}

	if (m_nCurDrawType == DRAW_TYPE_LANE_BOUNDARY_LINE)
	{   
		if (0 == m_iTriggerMode)
		{
			NET_ITC_LINE& struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneBoundaryLine;
			if (!m_bFirstDrawLaneBoundary)
			{
				struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
			}
		}
		else if (1 == m_iTriggerMode)
		{
			NET_ITC_LINE& struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneBoundaryLine;
			if (!m_bFirstDrawLaneBoundary)
			{
				struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
			}
		}
        else if (2 == m_iTriggerMode)
        {
            NET_ITC_LINE& struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneBoundaryLine;
            if (!m_bFirstDrawLaneBoundary)
            {
                struLaneBoundaryLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
                struLaneBoundaryLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
            }
		}
	}
	else if (m_nCurDrawType == DRAW_TYPE_LANE_LINE)
	{
		if (0 == m_iTriggerMode)
		{
			NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[m_nCurLaneIndex].struLaneLine;
			if (!m_bFirstDrawLaneLine)
			{
				struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
			}
		}
		else if (1 == m_iTriggerMode)
		{
			NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[m_nCurLaneIndex].struLaneLine;
			if (!m_bFirstDrawLaneLine)
			{
				struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
				struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
			}
		}
        else if (2 == m_iTriggerMode)
        {
            NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[m_nCurLaneIndex].struLaneLine;
            if (!m_bFirstDrawLaneLine)
            {
                struLaneLine.struLine.struEnd.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
                struLaneLine.struLine.struEnd.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
            }
		}
	}
    else if (m_nCurDrawType == DRAW_TYPE_SNAP_LINE)
    {
        if (1 == m_iTriggerMode)
        {
            NET_VCA_LINE& struSnapLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struSnapLine;
            if (!m_bFirstDrawSnapLine)
            {
                struSnapLine.struEnd.fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                struSnapLine.struEnd.fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
            }
        }
        else if (2 == m_iTriggerMode)
        {
            NET_VCA_LINE& struSnapLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struSnapLine;
            if (!m_bFirstDrawSnapLine)
            {
                struSnapLine.struEnd.fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                struSnapLine.struEnd.fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
            }
        }
    }
	else if (m_nCurDrawType == DRAW_TYPE_PLATE_RECOG_RGN)
	{   
		if (m_nDrawPointNum >= MAX_POLYGON_POINT_NUM || m_nDrawPointNum < 1)
		{
			return;
		}

		if (0 == m_iTriggerMode)
		{
			NET_ITC_POLYGON& struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[m_nCurLaneIndex].struPlateRecog;
			if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//按CTRL键 画矩形图
			{
				if (m_nDrawPointNum == 1)
				{
					struPlateRecog.struPos[m_nDrawPointNum].fX = struPlateRecog.struPos[m_nDrawPointNum-1].fX;
					struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
					
					struPlateRecog.struPos[m_nDrawPointNum+1].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
					struPlateRecog.struPos[m_nDrawPointNum+1].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
					
					struPlateRecog.struPos[m_nDrawPointNum+2].fX = struPlateRecog.struPos[m_nDrawPointNum+1].fX;
					struPlateRecog.struPos[m_nDrawPointNum+2].fY = struPlateRecog.struPos[0].fY;
					
					struPlateRecog.dwPointNum = 4;
				}
			}
			else
			{
				struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
				struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
				struPlateRecog.dwPointNum = m_nDrawPointNum + 1;
			}
		}
		else if (1 == m_iTriggerMode)
		{
			NET_ITC_POLYGON& struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[m_nCurLaneIndex].struPlateRecog;
			if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//按CTRL键 画矩形图
			{
				if (m_nDrawPointNum == 1)
				{
					struPlateRecog.struPos[m_nDrawPointNum].fX = struPlateRecog.struPos[m_nDrawPointNum-1].fX;
					struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
					
					struPlateRecog.struPos[m_nDrawPointNum+1].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
					struPlateRecog.struPos[m_nDrawPointNum+1].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
					
					struPlateRecog.struPos[m_nDrawPointNum+2].fX = struPlateRecog.struPos[m_nDrawPointNum+1].fX;
					struPlateRecog.struPos[m_nDrawPointNum+2].fY = struPlateRecog.struPos[0].fY;
					
					struPlateRecog.dwPointNum = 4;
				}
			}
			else
			{
				struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
				struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
				struPlateRecog.dwPointNum = m_nDrawPointNum + 1;
			}
		}
        else if (2 == m_iTriggerMode)
        {
            NET_ITC_POLYGON& struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[m_nCurLaneIndex].struPlateRecog;
            if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//按CTRL键 画矩形图
            {
                if (m_nDrawPointNum == 1)
                {
                    struPlateRecog.struPos[m_nDrawPointNum].fX = struPlateRecog.struPos[m_nDrawPointNum-1].fX;
                    struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                    
                    struPlateRecog.struPos[m_nDrawPointNum+1].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                    struPlateRecog.struPos[m_nDrawPointNum+1].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                    
                    struPlateRecog.struPos[m_nDrawPointNum+2].fX = struPlateRecog.struPos[m_nDrawPointNum+1].fX;
                    struPlateRecog.struPos[m_nDrawPointNum+2].fY = struPlateRecog.struPos[0].fY;
                    
                    struPlateRecog.dwPointNum = 4;
                }
            }
            else
            {
                struPlateRecog.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                struPlateRecog.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                struPlateRecog.dwPointNum = m_nDrawPointNum + 1;
            }
		}
	}
}

void CDlgVcaITCTriggerCfg::InitCtrlState()
{   
	char szText[32] = "\0";

	m_comboRecogPos.ResetContent();
    g_StringLanType(szText, "正向识别","Forward Plate");
	m_comboRecogPos.InsertString(0,szText);
	m_comboRecogPos.SetItemData(0,0);
    g_StringLanType(szText, "背向识别","Back Plate");
	m_comboRecogPos.InsertString(1,szText);
	m_comboRecogPos.SetItemData(1,1);
	m_comboRecogPos.SetCurSel(0);
    
	m_comboVehicleType.ResetContent();
	g_StringLanType(szText, "小车牌","Small Plate");
	m_comboVehicleType.InsertString(0,szText);
	m_comboVehicleType.SetItemData(0,0);
	g_StringLanType(szText, "大车牌","Big Plate");
	m_comboVehicleType.InsertString(1,szText);
	m_comboVehicleType.SetItemData(1,1);
	m_comboVehicleType.SetCurSel(0);
    
	m_cmbRoadType.ResetContent();
    g_StringLanType(szText, "出入口","Inward and outward");
    m_cmbRoadType.InsertString(0,szText);
    m_cmbRoadType.SetItemData(0,0);
    g_StringLanType(szText, "城市道路","Urban road");
    m_cmbRoadType.InsertString(1,szText);
    m_cmbRoadType.SetItemData(1,1);
    g_StringLanType(szText, "自定义","custom");
    m_cmbRoadType.InsertString(2,szText);
    m_cmbRoadType.SetItemData(2,2);
    g_StringLanType(szText, "报警输入", "alarm input");
    m_cmbRoadType.InsertString(3, szText);
    m_cmbRoadType.SetItemData(3, 3);
    g_StringLanType(szText, "卡口", "post");
    m_cmbRoadType.InsertString(4, szText);
    m_cmbRoadType.SetItemData(4, 4);
    g_StringLanType(szText, "治安监控", "security monitoring");
    m_cmbRoadType.InsertString(5, szText);
    m_cmbRoadType.SetItemData(5, 5);
	m_cmbRoadType.SetCurSel(0);
	
	m_comboTimeType.ResetContent();
	g_StringLanType(szText, "白天","Daytime");
	m_comboTimeType.InsertString(0,szText);
	m_comboTimeType.SetItemData(0,0);
	g_StringLanType(szText, "晚上","Night");
	m_comboTimeType.InsertString(1,szText);
	m_comboTimeType.SetItemData(1,1);
	m_comboTimeType.SetCurSel(0);
    
	m_comboSceneType.ResetContent();
	g_StringLanType(szText, "电警","Electrical Superintendent");
	m_comboSceneType.InsertString(0,szText);
	m_comboSceneType.SetItemData(0,0);
	g_StringLanType(szText, "卡口","Gate");
	m_comboSceneType.InsertString(1,szText);
	m_comboSceneType.SetItemData(1,1);
	m_comboSceneType.SetCurSel(0);
    
	m_comboLocateType.ResetContent();
	g_StringLanType(szText, "帧定位","Frame Locate");
	m_comboLocateType.InsertString(0,szText);
	m_comboLocateType.SetItemData(0,0);
	g_StringLanType(szText, "场定位","Field locate");
	m_comboLocateType.InsertString(1,szText);
	m_comboLocateType.SetItemData(1,1);
	m_comboLocateType.SetCurSel(0);
    
	m_comboRecogType.ResetContent();
	g_StringLanType(szText, "帧识别","Frame Recognition");
	m_comboRecogType.InsertString(0,szText);
	m_comboRecogType.SetItemData(0,0);
	g_StringLanType(szText, "场识别","Field Recognition");
	m_comboRecogType.InsertString(1,szText);
	m_comboRecogType.SetItemData(1,1);
	m_comboRecogType.SetCurSel(0);

	for (int i = 0; i < MAX_ITC_LANE_NUM; i++)
	{
		CString strLaneNumber  = "";
		strLaneNumber.Format("%d",i + 1);
		m_comboLaneNumber.InsertString(i,strLaneNumber);
		m_comboLaneNumber.SetItemData(i,i);
	}
	m_comboLaneNumber.SetCurSel(0);
    
	m_comboLaneDirection.ResetContent();
	g_StringLanType(szText, "未知", "Unknown");
	m_comboLaneDirection.InsertString(0, szText);
	m_comboLaneDirection.SetItemData(0, ITC_LANE_DIRECTION_UNKNOW);

	g_StringLanType(szText, "左转", "Left");
	m_comboLaneDirection.InsertString(1, szText);
	m_comboLaneDirection.SetItemData(1, ITC_LANE_LEFT);
	
	g_StringLanType(szText, "直行", "Straight");
	m_comboLaneDirection.InsertString(2, szText);
	m_comboLaneDirection.SetItemData(2, ITC_LANE_STRAIGHT);
	
	g_StringLanType(szText, "左转+直行", "Left and Straight");
	m_comboLaneDirection.InsertString(3, szText);
	m_comboLaneDirection.SetItemData(3, ITC_LANE_LEFT_STRAIGHT);
	
	g_StringLanType(szText, "右转", "Right");
	m_comboLaneDirection.InsertString(4, szText);
	m_comboLaneDirection.SetItemData(4, ITC_LANE_RIGHT);
	
	g_StringLanType(szText, "左转+右转", "Left and Right");
	m_comboLaneDirection.InsertString(5, szText);
	m_comboLaneDirection.SetItemData(5, ITC_LANE_LEFT_RIGHT);
	
	g_StringLanType(szText, "右转+直行", "Right and Straight");
	m_comboLaneDirection.InsertString(6, szText);
	m_comboLaneDirection.SetItemData(6, ITC_LANE_RIGHT_STRAIGHT);
	
	g_StringLanType(szText, "左转+右转+直行", "Left and Right and Straight");
	m_comboLaneDirection.InsertString(7, szText);
	m_comboLaneDirection.SetItemData(7, ITC_LANE_LEFT_RIGHT_STRAIGHT);
	
	g_StringLanType(szText, "左转待行", "Left Wait");
	m_comboLaneDirection.InsertString(8, szText);
	m_comboLaneDirection.SetItemData(8, ITC_LANE_LEFT_WAIT);
	
	g_StringLanType(szText, "直行待行", "Straight Wait");
	m_comboLaneDirection.InsertString(9, szText);
	m_comboLaneDirection.SetItemData(9, ITC_LANE_STRAIGHT_WAIT);

	g_StringLanType(szText, "正向行驶", "Forward");
	m_comboLaneDirection.InsertString(10, szText);
	m_comboLaneDirection.SetItemData(10, ITC_LANE_FORWARD);

	g_StringLanType(szText, "背向行驶", "Backward");
	m_comboLaneDirection.InsertString(11, szText);
	m_comboLaneDirection.SetItemData(11, ITC_LANE_BACKWARD);

	g_StringLanType(szText, "双向行驶", "Bothway");
	m_comboLaneDirection.InsertString(12, szText);
	m_comboLaneDirection.SetItemData(12, ITC_LANE_BOTHWAY);
	m_comboLaneDirection.SetCurSel(0);

	m_comboLaneUseageType.ResetContent();
	g_StringLanType(szText, "未知", "Unknown");
	m_comboLaneUseageType.InsertString(0, szText);
	m_comboLaneUseageType.SetItemData(0, ITC_LANE_USEAGE_UNKNOW);

	g_StringLanType(szText, "正常车道", "Ordinary lanes");
	m_comboLaneUseageType.InsertString(1, szText);
	m_comboLaneUseageType.SetItemData(1, ITC_LANE_CARRIAGEWAY);

	g_StringLanType(szText, "公交车专用道", "Bus lanes");
	m_comboLaneUseageType.InsertString(2, szText);
	m_comboLaneUseageType.SetItemData(2, ITC_LANE_BUS);

	g_StringLanType(szText, "快车道", "Fast lane");
	m_comboLaneUseageType.InsertString(3, szText);
	m_comboLaneUseageType.SetItemData(3, ITC_LANE_FAST);

	g_StringLanType(szText, "慢车道", "Slow lane");
	m_comboLaneUseageType.InsertString(4, szText);
	m_comboLaneUseageType.SetItemData(4, ITC_LANE_SLOW);

	g_StringLanType(szText, "摩托车道", "Motorcycle lane");
	m_comboLaneUseageType.InsertString(5, szText);
	m_comboLaneUseageType.SetItemData(5, ITC_LANE_MOTOR);

	g_StringLanType(szText, "非机动车道", "Non-motor vehicle lane");
	m_comboLaneUseageType.InsertString(6, szText);
	m_comboLaneUseageType.SetItemData(6, ITC_LANE_NONMOTOR);

	g_StringLanType(szText, "反向车道", "Reversed lane");
	m_comboLaneUseageType.InsertString(7, szText);
	m_comboLaneUseageType.SetItemData(7, ITC_LANE_REVERSE_LANE);

	g_StringLanType(szText, "禁止货车车道", "Ban trucks lane");
	m_comboLaneUseageType.InsertString(8, szText);
	m_comboLaneUseageType.SetItemData(8, ITC_LANE_BAN_TRUCKS);

	g_StringLanType(szText, "混合车道", "Mix lane");
	m_comboLaneUseageType.InsertString(9, szText);
	m_comboLaneUseageType.SetItemData(9, ITC_LANE_MIX);
	m_comboLaneUseageType.SetCurSel(0);

	m_comboDriveDirection.ResetContent();
    g_StringLanType(szText, "未知", "Unknown");
	m_comboDriveDirection.InsertString(0,szText);
	m_comboDriveDirection.SetItemData(0,ITC_LANE_DRIVE_UNKNOW);

	g_StringLanType(szText, "下行", "Up to down");
	m_comboDriveDirection.InsertString(1,szText);
	m_comboDriveDirection.SetItemData(1,ITC_LANE_DRIVE_UP_TO_DOWN);

	g_StringLanType(szText, "上行", "Down to up");
	m_comboDriveDirection.InsertString(2,szText);
	m_comboDriveDirection.SetItemData(2,ITC_LANE_DRIVE_DOWN_TO_UP);
	m_comboDriveDirection.SetCurSel(0);
}

void CDlgVcaITCTriggerCfg::DrawRgnFun(HDC hdc)
{   
    for (int i = 0; i < MAX_ITC_LANE_NUM; i++)
    {   
		DRAW_POLYGON_PARAM_EX struPolygonParam;
		memset(&struPolygonParam,0,sizeof(struPolygonParam));
		memcpy(&struPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));

		DRAW_LINE_PARAM  struLaneLineParam;
        if (i == m_nCurLaneIndex) 
        {
			struLaneLineParam.color = RGB(255,0,0);
			struPolygonParam.color = RGB(255,0,0);
			
        }
        else
        {  
			struLaneLineParam.color = RGB(0,255,0);
			struPolygonParam.color = RGB(85,170,255);
        }
        
		if (0 == m_iTriggerMode)
		{
			NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[i].struLaneLine;
			memcpy(&struLaneLineParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
			struLaneLineParam.struVcaLine = struLaneLine.struLine;
		} 
		else if(1 == m_iTriggerMode)
		{
			NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[i].struLaneLine;
			memcpy(&struLaneLineParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
			struLaneLineParam.struVcaLine = struLaneLine.struLine;
		}
        else if(2 == m_iTriggerMode)
        {
            NET_ITC_LINE& struLaneLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[i].struLaneLine;
            memcpy(&struLaneLineParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
            struLaneLineParam.struVcaLine = struLaneLine.struLine;
		}

		CDrawFun::DrawLine(hdc, &struLaneLineParam);

		if (0 == m_iTriggerMode)
		{
			NET_ITC_POLYGON& struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[i].struPlateRecog;
			struPolygonParam.pArryPt = struPlateRecog.struPos;
			struPolygonParam.dwPtNum = struPlateRecog.dwPointNum;
		}
		else if(1 == m_iTriggerMode)
		{
			NET_ITC_POLYGON& struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[i].struPlateRecog;
			struPolygonParam.pArryPt = struPlateRecog.struPos;
			struPolygonParam.dwPtNum = struPlateRecog.dwPointNum;
		}
        else if(2 == m_iTriggerMode)
        {
            NET_ITC_POLYGON& struPlateRecog = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[i].struPlateRecog;
            struPolygonParam.pArryPt = struPlateRecog.struPos;
            struPolygonParam.dwPtNum = struPlateRecog.dwPointNum;
		}

		CDrawFun::DrawPolygonEx(hdc,&struPolygonParam);
	}
    
	DRAW_LINE_PARAM  struLaneBoundaryParam;
	
	if (0 == m_iTriggerMode)
	{
		NET_ITC_LINE&  struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneBoundaryLine;
		struLaneBoundaryParam.color = RGB(255,255,0);
		memcpy(&struLaneBoundaryParam.rcWnd, &m_rcPlayWnd, sizeof(struLaneBoundaryParam.rcWnd));
		struLaneBoundaryParam.struVcaLine = struLaneBoundaryLine.struLine;
	}
	else if(1 == m_iTriggerMode)
	{
		NET_ITC_LINE&  struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneBoundaryLine;
		struLaneBoundaryParam.color = RGB(255,255,0);
		memcpy(&struLaneBoundaryParam.rcWnd, &m_rcPlayWnd, sizeof(struLaneBoundaryParam.rcWnd));
		struLaneBoundaryParam.struVcaLine = struLaneBoundaryLine.struLine;
	}
    else if(2 == m_iTriggerMode)
    {
        NET_ITC_LINE&  struLaneBoundaryLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneBoundaryLine;
        struLaneBoundaryParam.color = RGB(255,255,0);
        memcpy(&struLaneBoundaryParam.rcWnd, &m_rcPlayWnd, sizeof(struLaneBoundaryParam.rcWnd));
        struLaneBoundaryParam.struVcaLine = struLaneBoundaryLine.struLine;
	}

    CDrawFun::DrawLine(hdc, &struLaneBoundaryParam);
    DRAW_LINE_PARAM  struSnapLineParam;

    if (1 == m_iTriggerMode)
    {
        NET_VCA_LINE&  struSnapLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struSnapLine;
        struSnapLineParam.color = RGB(255, 255, 0);
        memcpy(&struSnapLineParam.rcWnd, &m_rcPlayWnd, sizeof(struSnapLineParam.rcWnd));
        struSnapLineParam.struVcaLine = struSnapLine;
    }
    else if (2 == m_iTriggerMode)
    {
        NET_VCA_LINE&  struSnapLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struSnapLine;
        struSnapLineParam.color = RGB(255, 255, 0);
        memcpy(&struSnapLineParam.rcWnd, &m_rcPlayWnd, sizeof(struSnapLineParam.rcWnd));
        struSnapLineParam.struVcaLine = struSnapLine;
    }

    CDrawFun::DrawLine(hdc, &struSnapLineParam);

}

void CDlgVcaITCTriggerCfg::LoadViaLaneWndContent(int nLaneIndex)
{
	if (0 == m_iTriggerMode)
	{
		NET_DVR_VIA_LANE_PARAM& struViaLaneParam = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[nLaneIndex];
		
		const NET_ITC_LANE_LOGIC_PARAM& struLaneLogicParam = struViaLaneParam.struLogicParam;
		
		m_nAssociateLaneNO = struViaLaneParam.byLaneNO;
		
		int i = 0;
		for (i = 0; i < m_comboLaneNumber.GetCount(); i++)
		{
			if (m_comboLaneNumber.GetItemData(i) == nLaneIndex)
			{
				m_comboLaneNumber.SetCurSel(i);
				break;
			}
		}
		
		for (i = 0; i < m_comboLaneUseageType.GetCount(); i++)
		{
			if (m_comboLaneUseageType.GetItemData(i) == struLaneLogicParam.byUseageType)
			{
				m_comboLaneUseageType.SetCurSel(i);
				break;
			}
		}
		
		for (i = 0; i < m_comboLaneDirection.GetCount(); i++)
		{
			if (m_comboLaneDirection.GetItemData(i) == struLaneLogicParam.byDirectionType)
			{
				m_comboLaneDirection.SetCurSel(i);
				break;
			}
		}
		
		for (i = 0; i < m_comboDriveDirection.GetCount(); i++)
		{
			if (m_comboDriveDirection.GetItemData(i) == struLaneLogicParam.byCarDriveDirect)
			{
				m_comboDriveDirection.SetCurSel(i);
				break;
			}
		}
	}
	else if (1 == m_iTriggerMode)
	{
		NET_ITC_LANE_MPR_PARAM& struMprLaneParam = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[nLaneIndex];
		m_nAssociateLaneNO = struMprLaneParam.byLaneNO;
		if (1 == m_comSourceType.GetCurSel())
		{
			m_comIONo.SetCurSel(struMprLaneParam.uTssParamInfo.struIO.byIONo - 1);
			m_comTriggerType.SetCurSel(struMprLaneParam.uTssParamInfo.struIO.byTriggerType);
		}
		else if (2 == m_comSourceType.GetCurSel())
		{
			m_comRelateChan.SetCurSel(struMprLaneParam.uTssParamInfo.struRS485.byRelateChan);
		}
		//m_szSceneName.Format(_T("%s"), struMprLaneParam.szSceneName);
		int i = 0;
		for (i = 0; i < m_comboDriveDirection.GetCount(); i++)
		{
			if (m_comboDriveDirection.GetItemData(i) == struMprLaneParam.byCarDriveDirect)
			{
				m_comboDriveDirection.SetCurSel(i);
				break;
			}
		}
	}
    else if (2 == m_iTriggerMode)
    {
        NET_IPC_LANE_HVT_PARAM& struIpcHvtLaneParam = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[nLaneIndex];
        m_nAssociateLaneNO = struIpcHvtLaneParam.byLaneNO;
		int i = 0;
		for (i = 0; i < m_comboDriveDirection.GetCount(); i++)
		{
			if (m_comboDriveDirection.GetItemData(i) == struIpcHvtLaneParam.byCarDriveDirect)
			{
				m_comboDriveDirection.SetCurSel(i);
				break;
			}
		}
    }
}

void CDlgVcaITCTriggerCfg::SaveViaLaneWndContent(int nLaneIndex)
{
	if (0 == m_iTriggerMode)
	{
		NET_DVR_VIA_LANE_PARAM& struViaLaneParam = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struViaVtCoil.struLaneParam[nLaneIndex];
		struViaLaneParam.byLaneNO = m_nAssociateLaneNO;
		NET_ITC_LANE_LOGIC_PARAM& struLaneLogicParam = struViaLaneParam.struLogicParam;
		struLaneLogicParam.byUseageType = m_comboLaneUseageType.GetItemData(m_comboLaneUseageType.GetCurSel());
		struLaneLogicParam.byDirectionType = m_comboLaneDirection.GetItemData(m_comboLaneDirection.GetCurSel());
		struLaneLogicParam.byCarDriveDirect = m_comboDriveDirection.GetItemData(m_comboDriveDirection.GetCurSel());
	}
	else if(1 == m_iTriggerMode)
	{
		NET_ITC_LANE_MPR_PARAM& struMprLaneParam = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struLaneParam[nLaneIndex];
		struMprLaneParam.byLaneNO = m_nAssociateLaneNO;
		if (1 == m_comSourceType.GetCurSel())
		{
			struMprLaneParam.uTssParamInfo.struIO.byIONo = m_comIONo.GetCurSel() + 1;
			struMprLaneParam.uTssParamInfo.struIO.byTriggerType = m_comTriggerType.GetCurSel();
		}
		else if (2 == m_comSourceType.GetCurSel())
		{
			struMprLaneParam.uTssParamInfo.struRS485.byRelateChan = m_comRelateChan.GetCurSel();
		}
		struMprLaneParam.byCarDriveDirect = m_comboDriveDirection.GetItemData(m_comboDriveDirection.GetCurSel());
	}
    else if(2 == m_iTriggerMode)
    {
        NET_IPC_LANE_HVT_PARAM& struIpcHvtLaneParam = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struLaneParam[nLaneIndex];
		struIpcHvtLaneParam.byLaneNO = m_nAssociateLaneNO;
		struIpcHvtLaneParam.byCarDriveDirect = m_comboDriveDirection.GetItemData(m_comboDriveDirection.GetCurSel());
    }
}

void CDlgVcaITCTriggerCfg::LoadWndContent()
{
	const NET_ITC_SINGLE_TRIGGERCFG&  struTriggerParam = m_struItcTriggerCfg.struTriggerParam;
	m_bTriggerCfg = struTriggerParam.byEnable;
	
 	if (0 == m_iTriggerMode)
	{
		const NET_DVR_VIA_VTCOIL_PARAM& struViaVtcoiParam = struTriggerParam.uTriggerParam.struViaVtCoil;
		m_bViaVtcoil = struViaVtcoiParam.byEnable;
		m_nLaneNum = struViaVtcoiParam.byLaneNum;

		const NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struViaVtcoiParam.struPlateRecog;
		m_strProvinceName = struPlateRecogParam.byDefaultCHN;
		m_bPlateRecog = struPlateRecogParam.byEnable;
		m_bVehicleLogoRecog = struPlateRecogParam.byVehicleLogoRecog;
		
		DWORD dwRecogMode = struPlateRecogParam.dwRecogMode;
		
		m_comboRecogPos.SetCurSel(dwRecogMode & 0x00000001 ? 1 : 0);
		m_comboVehicleType.SetCurSel(dwRecogMode & 0x00000002 ? 1 : 0);
		m_bVehicleColorRecog = (dwRecogMode & 0x00000004) ? TRUE : FALSE;
		m_bFarmVehicleRecog = (dwRecogMode & 0x00000008) ? TRUE : FALSE;
		m_bFuzzyRecog = (dwRecogMode & 0x00000010) ? TRUE : FALSE;
		m_comboLocateType.SetCurSel(dwRecogMode & 0x00000020 ? 1 : 0);
		m_comboRecogType.SetCurSel(dwRecogMode & 0x00000040 ? 1 : 0);
		m_comboTimeType.SetCurSel(dwRecogMode & 0x00000080 ? 1 : 0);
		m_bMotocarRecog = (dwRecogMode & 0x00000100) ? TRUE : FALSE;
		m_comboSceneType.SetCurSel(dwRecogMode & 0x00000200 ? 1 : 0);
		m_bMicroPlateRecog = (dwRecogMode & 0x00000400)? TRUE : FALSE;
		
		if (struPlateRecogParam.byProvince == 0xff)
		{
			m_comProvince.SetCurSel(35);
		} 
		else
		{
			m_comProvince.SetCurSel(struPlateRecogParam.byProvince);
		}

	    m_comRegion.SetCurSel(struPlateRecogParam.byRegion);
//		m_comboCarDriveDirect.SetCurSel(struPlateRecogParam.byCarDriveDirect);
        m_bCountryIndex = struPlateRecogParam.byCountry;
        m_dwPlatePixelWidthMin = struPlateRecogParam.wPlatePixelWidthMin;
        m_dwPlatePixelWidthMax = struPlateRecogParam.wPlatePixelWidthMax;
	}
	else if (1 == m_iTriggerMode)
	{
		const NET_ITC_POST_MPR_PARAM& struMprParam = struTriggerParam.uTriggerParam.struPostMpr;
		m_cmbRoadType.SetCurSel(struMprParam.byRoadType);
        if (struMprParam.byRoadType == 2)
        {
            GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(TRUE);
            m_wDelayTime = struMprParam.wCustomDelayTime;
        } 
        else if(struMprParam.byRoadType == 1)
        {
            GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(FALSE);
            m_wDelayTime = 5000;
        }
        else
        {
            GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(FALSE);
            m_wDelayTime = 0;
        }
		m_nLaneNum = struMprParam.byLaneNum;
		m_comSourceType.SetCurSel(struMprParam.bySourceType);
		m_szSceneName.Format(_T("%s"), struMprParam.szSceneName);
		OnSelchangeComboSourceType();
		const NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struMprParam.struPlateRecog;
		m_strProvinceName = struPlateRecogParam.byDefaultCHN;
		m_bPlateRecog = struPlateRecogParam.byEnable;
		m_bVehicleLogoRecog = struPlateRecogParam.byVehicleLogoRecog;
		
		DWORD dwRecogMode = struPlateRecogParam.dwRecogMode;
		
		m_comboRecogPos.SetCurSel(dwRecogMode & 0x00000001 ? 1 : 0);
		m_comboVehicleType.SetCurSel(dwRecogMode & 0x00000002 ? 1 : 0);
		m_bVehicleColorRecog = (dwRecogMode & 0x00000004) ? TRUE : FALSE;
		m_bFarmVehicleRecog = (dwRecogMode & 0x00000008) ? TRUE : FALSE;
		m_bFuzzyRecog = (dwRecogMode & 0x00000010) ? TRUE : FALSE;
		m_comboLocateType.SetCurSel(dwRecogMode & 0x00000020 ? 1 : 0);
		m_comboRecogType.SetCurSel(dwRecogMode & 0x00000040 ? 1 : 0);
		m_comboTimeType.SetCurSel(dwRecogMode & 0x00000080 ? 1 : 0);
		m_bMotocarRecog = (dwRecogMode & 0x00000100) ? TRUE : FALSE;
		m_comboSceneType.SetCurSel(dwRecogMode & 0x00000200 ? 1 : 0);
		m_bMicroPlateRecog = (dwRecogMode & 0x00000400)? TRUE : FALSE;
		
		if (struPlateRecogParam.byProvince == 0xff)
		{
			m_comProvince.SetCurSel(35);
		} 
		else
		{
			m_comProvince.SetCurSel(struPlateRecogParam.byProvince);
		}


		m_comRegion.SetCurSel(struPlateRecogParam.byRegion);
        m_bCountryIndex = struPlateRecogParam.byCountry;
//		m_comboCarDriveDirect.SetCurSel(struPlateRecogParam.byCarDriveDirect);
        m_dwPlatePixelWidthMin = struPlateRecogParam.wPlatePixelWidthMin;
        m_dwPlatePixelWidthMax = struPlateRecogParam.wPlatePixelWidthMax;
	}
    else if (2 == m_iTriggerMode)
    {
        const NET_IPC_POST_HVT_PARAM& struIpcHvtParam = struTriggerParam.uTriggerParam.struIpcHvt;
        m_bTriggerCfg = struIpcHvtParam.byEnable;
        m_nLaneNum = struIpcHvtParam.byLaneNum;
        m_szSceneName.Format(_T("%s"), struIpcHvtParam.szSceneName);
      
        const NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struIpcHvtParam.struPlateRecog;
        m_strProvinceName = struPlateRecogParam.byDefaultCHN;
        m_bPlateRecog = struPlateRecogParam.byEnable;
        m_bVehicleLogoRecog = struPlateRecogParam.byVehicleLogoRecog;
        
        DWORD dwRecogMode = struPlateRecogParam.dwRecogMode;
        
        m_comboRecogPos.SetCurSel(dwRecogMode & 0x00000001 ? 1 : 0);
        m_comboVehicleType.SetCurSel(dwRecogMode & 0x00000002 ? 1 : 0);
        m_bVehicleColorRecog = (dwRecogMode & 0x00000004) ? TRUE : FALSE;
        m_bFarmVehicleRecog = (dwRecogMode & 0x00000008) ? TRUE : FALSE;
        m_bFuzzyRecog = (dwRecogMode & 0x00000010) ? TRUE : FALSE;
        m_comboLocateType.SetCurSel(dwRecogMode & 0x00000020 ? 1 : 0);
        m_comboRecogType.SetCurSel(dwRecogMode & 0x00000040 ? 1 : 0);
        m_comboTimeType.SetCurSel(dwRecogMode & 0x00000080 ? 1 : 0);
        m_bMotocarRecog = (dwRecogMode & 0x00000100) ? TRUE : FALSE;
        m_comboSceneType.SetCurSel(dwRecogMode & 0x00000200 ? 1 : 0);
        m_bMicroPlateRecog = (dwRecogMode & 0x00000400)? TRUE : FALSE;
        
        if (struPlateRecogParam.byProvince == 0xff)
        {
            m_comProvince.SetCurSel(35);
        } 
        else
        {
            m_comProvince.SetCurSel(struPlateRecogParam.byProvince);
        }
		
		m_comRegion.SetCurSel(struPlateRecogParam.byRegion);
        m_bCountryIndex = struPlateRecogParam.byCountry;
		
//		m_comboCarDriveDirect.SetCurSel(struPlateRecogParam.byCarDriveDirect);
        m_dwPlatePixelWidthMin = struPlateRecogParam.wPlatePixelWidthMin;
        m_dwPlatePixelWidthMax = struPlateRecogParam.wPlatePixelWidthMax;
	}
	

	LoadViaLaneWndContent(m_nCurLaneIndex);

	UpdateData(FALSE);
}

void CDlgVcaITCTriggerCfg::SaveWndContent()
{
	UpdateData(TRUE);
    
    m_struItcTriggerCfg.dwSize = sizeof(m_struItcTriggerCfg);

	
	NET_ITC_SINGLE_TRIGGERCFG&  struTriggerParam = m_struItcTriggerCfg.struTriggerParam;
	struTriggerParam.byEnable = m_bTriggerCfg;

	if (0 == m_iTriggerMode)
	{
		struTriggerParam.dwTriggerType = ITC_VIA_VIRTUALCOIL_TYPE;
		NET_DVR_VIA_VTCOIL_PARAM& struViaVtcoiParam = struTriggerParam.uTriggerParam.struViaVtCoil;
		
		struViaVtcoiParam.byEnable = m_bTriggerCfg/* m_bViaVtcoil*/;
		struViaVtcoiParam.byLaneNum = m_nLaneNum;
		
		NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struViaVtcoiParam.struPlateRecog;

		strncpy((char*)struPlateRecogParam.byDefaultCHN,m_strProvinceName,MAX_CHJC_NUM);
		struPlateRecogParam.byEnable = m_bTriggerCfg/*m_bPlateRecog*/;
		struPlateRecogParam.byVehicleLogoRecog = m_bVehicleLogoRecog;
		if (35 == m_comProvince.GetCurSel())
		{
			struPlateRecogParam.byProvince = 0xff;
		} 
		else
		{
			struPlateRecogParam.byProvince = m_comProvince.GetCurSel();
		}

		struPlateRecogParam.byRegion = m_comRegion.GetCurSel();
        struPlateRecogParam.byCountry = m_bCountryIndex;
		
        struPlateRecogParam.wPlatePixelWidthMin = m_dwPlatePixelWidthMin;
        struPlateRecogParam.wPlatePixelWidthMax = m_dwPlatePixelWidthMax;
		
//		struPlateRecogParam.byCarDriveDirect = m_comboCarDriveDirect.GetCurSel();

		struPlateRecogParam.dwRecogMode = 0;
		struPlateRecogParam.dwRecogMode |= (m_comboRecogPos.GetItemData(m_comboRecogPos.GetCurSel())       == 0 ? 0x00000000 : 0x00000001);
		struPlateRecogParam.dwRecogMode |= (m_comboVehicleType.GetItemData(m_comboVehicleType.GetCurSel()) == 0 ? 0x00000000 : 0x00000002);
		struPlateRecogParam.dwRecogMode |= m_bVehicleColorRecog ? 0x00000004 : 0x00000000;
		struPlateRecogParam.dwRecogMode |= m_bFarmVehicleRecog  ? 0x00000008 : 0x00000000;
		struPlateRecogParam.dwRecogMode |= m_bFuzzyRecog        ? 0x00000010 : 0x00000000;
		struPlateRecogParam.dwRecogMode |= (m_comboLocateType.GetItemData(m_comboLocateType.GetCurSel())   == 0 ? 0x00000000 : 0x00000020);
		struPlateRecogParam.dwRecogMode |= (m_comboRecogType.GetItemData(m_comboRecogType.GetCurSel())     == 0 ? 0x00000000 : 0x00000040);
		struPlateRecogParam.dwRecogMode |= (m_comboTimeType.GetItemData(m_comboTimeType.GetCurSel())       == 0 ? 0x00000000 : 0x00000080);
		struPlateRecogParam.dwRecogMode |= m_bMotocarRecog      ? 0x00000100 : 0x00000000;
		struPlateRecogParam.dwRecogMode |= (m_comboSceneType.GetItemData(m_comboSceneType.GetCurSel())     == 0 ? 0x00000000 : 0x00000200);
		struPlateRecogParam.dwRecogMode |= m_bMicroPlateRecog   ? 0x00000400 : 0x00000000;
	}
	else if (1 == m_iTriggerMode)
	{
		struTriggerParam.dwTriggerType = ITC_POST_MPR_TYPE;
		NET_ITC_POST_MPR_PARAM& struMprParam = struTriggerParam.uTriggerParam.struPostMpr;
		struMprParam.byEnable = m_bTriggerCfg;
		struMprParam.byLaneNum = m_nLaneNum;
		struMprParam.bySourceType = m_comSourceType.GetCurSel();
		struMprParam.byRoadType = m_cmbRoadType.GetCurSel();
        if (struMprParam.byRoadType == 2)
        {
            GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(TRUE);
            struMprParam.wCustomDelayTime = m_wDelayTime;
        }
        else if (struMprParam.byRoadType == 1)
        {
            GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(FALSE);
             m_wDelayTime = 5000;
            struMprParam.wCustomDelayTime = 5000;
        }
        else
        {
            GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(FALSE);
            struMprParam.wCustomDelayTime = 0;
             m_wDelayTime = 0;
        }
		memcpy(struMprParam.szSceneName, m_szSceneName, m_szSceneName.GetLength());
		NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struMprParam.struPlateRecog;

		strncpy((char*)struPlateRecogParam.byDefaultCHN,m_strProvinceName,MAX_CHJC_NUM);
		struPlateRecogParam.byEnable = m_bTriggerCfg/*m_bPlateRecog*/;
		struPlateRecogParam.byVehicleLogoRecog = m_bVehicleLogoRecog;
		if (35 == m_comProvince.GetCurSel())
		{
			struPlateRecogParam.byProvince = 0xff;
		} 
		else
		{
			struPlateRecogParam.byProvince = m_comProvince.GetCurSel();
		}

		struPlateRecogParam.byRegion = m_comRegion.GetCurSel();
        struPlateRecogParam.byCountry = m_bCountryIndex;
		
        struPlateRecogParam.wPlatePixelWidthMin = m_dwPlatePixelWidthMin;
        struPlateRecogParam.wPlatePixelWidthMax = m_dwPlatePixelWidthMax;
		
//		struPlateRecogParam.byCarDriveDirect = m_comboCarDriveDirect.GetCurSel();

		struPlateRecogParam.dwRecogMode = 0;
		struPlateRecogParam.dwRecogMode |= (m_comboRecogPos.GetItemData(m_comboRecogPos.GetCurSel())       == 0 ? 0x00000000 : 0x00000001);
		struPlateRecogParam.dwRecogMode |= (m_comboVehicleType.GetItemData(m_comboVehicleType.GetCurSel()) == 0 ? 0x00000000 : 0x00000002);
		struPlateRecogParam.dwRecogMode |= m_bVehicleColorRecog ? 0x00000004 : 0x00000000;
		struPlateRecogParam.dwRecogMode |= m_bFarmVehicleRecog  ? 0x00000008 : 0x00000000;
		struPlateRecogParam.dwRecogMode |= m_bFuzzyRecog        ? 0x00000010 : 0x00000000;
		struPlateRecogParam.dwRecogMode |= (m_comboLocateType.GetItemData(m_comboLocateType.GetCurSel())   == 0 ? 0x00000000 : 0x00000020);
		struPlateRecogParam.dwRecogMode |= (m_comboRecogType.GetItemData(m_comboRecogType.GetCurSel())     == 0 ? 0x00000000 : 0x00000040);
		struPlateRecogParam.dwRecogMode |= (m_comboTimeType.GetItemData(m_comboTimeType.GetCurSel())       == 0 ? 0x00000000 : 0x00000080);
		struPlateRecogParam.dwRecogMode |= m_bMotocarRecog      ? 0x00000100 : 0x00000000;
		struPlateRecogParam.dwRecogMode |= (m_comboSceneType.GetItemData(m_comboSceneType.GetCurSel())     == 0 ? 0x00000000 : 0x00000200);
		struPlateRecogParam.dwRecogMode |= m_bMicroPlateRecog   ? 0x00000400 : 0x00000000;
	}
    else if (2 == m_iTriggerMode)
    {
        struTriggerParam.dwTriggerType = IPC_POST_HVT_TYPE;
        NET_IPC_POST_HVT_PARAM& struIpcHvtParam = struTriggerParam.uTriggerParam.struIpcHvt;
        struIpcHvtParam.byEnable = m_bTriggerCfg;
        struIpcHvtParam.byLaneNum = m_nLaneNum;
        memcpy(struIpcHvtParam.szSceneName, m_szSceneName, m_szSceneName.GetLength());
        NET_ITC_PLATE_RECOG_PARAM& struPlateRecogParam = struIpcHvtParam.struPlateRecog;
        
        strncpy((char*)struPlateRecogParam.byDefaultCHN,m_strProvinceName,MAX_CHJC_NUM);
        struPlateRecogParam.byEnable = m_bTriggerCfg/*m_bPlateRecog*/;
        struPlateRecogParam.byVehicleLogoRecog = m_bVehicleLogoRecog;
        if (35 == m_comProvince.GetCurSel())
        {
            struPlateRecogParam.byProvince = 0xff;
        } 
        else
        {
            struPlateRecogParam.byProvince = m_comProvince.GetCurSel();
        }
 

		struPlateRecogParam.byRegion = m_comRegion.GetCurSel();
        struPlateRecogParam.byCountry = m_bCountryIndex;
		
        struPlateRecogParam.wPlatePixelWidthMin = m_dwPlatePixelWidthMin;
        struPlateRecogParam.wPlatePixelWidthMax = m_dwPlatePixelWidthMax;
		
//		struPlateRecogParam.byCarDriveDirect = m_comboCarDriveDirect.GetCurSel();
		
        struPlateRecogParam.dwRecogMode = 0;
        struPlateRecogParam.dwRecogMode |= (m_comboRecogPos.GetItemData(m_comboRecogPos.GetCurSel())       == 0 ? 0x00000000 : 0x00000001);
        struPlateRecogParam.dwRecogMode |= (m_comboVehicleType.GetItemData(m_comboVehicleType.GetCurSel()) == 0 ? 0x00000000 : 0x00000002);
        struPlateRecogParam.dwRecogMode |= m_bVehicleColorRecog ? 0x00000004 : 0x00000000;
        struPlateRecogParam.dwRecogMode |= m_bFarmVehicleRecog  ? 0x00000008 : 0x00000000;
        struPlateRecogParam.dwRecogMode |= m_bFuzzyRecog        ? 0x00000010 : 0x00000000;
        struPlateRecogParam.dwRecogMode |= (m_comboLocateType.GetItemData(m_comboLocateType.GetCurSel())   == 0 ? 0x00000000 : 0x00000020);
        struPlateRecogParam.dwRecogMode |= (m_comboRecogType.GetItemData(m_comboRecogType.GetCurSel())     == 0 ? 0x00000000 : 0x00000040);
        struPlateRecogParam.dwRecogMode |= (m_comboTimeType.GetItemData(m_comboTimeType.GetCurSel())       == 0 ? 0x00000000 : 0x00000080);
        struPlateRecogParam.dwRecogMode |= m_bMotocarRecog      ? 0x00000100 : 0x00000000;
        struPlateRecogParam.dwRecogMode |= (m_comboSceneType.GetItemData(m_comboSceneType.GetCurSel())     == 0 ? 0x00000000 : 0x00000200);
        struPlateRecogParam.dwRecogMode |= m_bMicroPlateRecog   ? 0x00000400 : 0x00000000;
	}
	SaveViaLaneWndContent(m_nCurLaneIndex);
	UpdateData(FALSE);
}

BOOL CDlgVcaITCTriggerCfg::GetITCTriggerCfg()
{
	UpdateData(TRUE);

	NET_DVR_TRIGGER_COND struTriggerCond = {0};
    struTriggerCond.dwSize = sizeof(struTriggerCond);
	struTriggerCond.dwChannel = m_comChan.GetItemData(m_comChan.GetCurSel());
	if (0 == m_iTriggerMode)
	{
		struTriggerCond.dwTriggerMode = ITC_VIA_VIRTUALCOIL_TYPE;
	}
	else if (1 == m_iTriggerMode)
	{
		struTriggerCond.byDetSceneID = m_comDetSceneID.GetCurSel();
		struTriggerCond.dwTriggerMode = ITC_POST_MPR_TYPE;
	}
    else if (2 == m_iTriggerMode)
    {
        struTriggerCond.byDetSceneID = m_comDetSceneID.GetCurSel();
        struTriggerCond.dwTriggerMode = IPC_POST_HVT_TYPE;
	}
	
	
	DWORD dwStatus = 0;
	BOOL bRet = FALSE;
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_TRIGGEREX_CFG, 1,(LPVOID)&struTriggerCond, sizeof(struTriggerCond),
		&dwStatus,&m_struItcTriggerCfg, sizeof(m_struItcTriggerCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRIGGEREX_CFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRIGGEREX_CFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaITCTriggerCfg::SetITCTriggerCfg()
{
	UpdateData(TRUE);
	NET_DVR_TRIGGER_COND struTriggerCond = {0};
	struTriggerCond.dwSize = sizeof(struTriggerCond);
	struTriggerCond.dwChannel = m_comChan.GetItemData(m_comChan.GetCurSel());
	struTriggerCond.dwTriggerMode = ITC_VIA_VIRTUALCOIL_TYPE;

	if (0 == m_iTriggerMode)
	{
		struTriggerCond.dwTriggerMode = ITC_VIA_VIRTUALCOIL_TYPE;
	}
	else if (1 == m_iTriggerMode)
	{
		struTriggerCond.byDetSceneID = m_comDetSceneID.GetCurSel();
		struTriggerCond.dwTriggerMode = ITC_POST_MPR_TYPE;
	}
    else if (2 == m_iTriggerMode)
    {
        struTriggerCond.byDetSceneID = m_comDetSceneID.GetCurSel();
        struTriggerCond.dwTriggerMode = IPC_POST_HVT_TYPE;
	}
	
    DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_TRIGGEREX_CFG,1,(LPVOID)&struTriggerCond, sizeof(struTriggerCond),
		&dwStatus,&m_struItcTriggerCfg, sizeof(m_struItcTriggerCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRIGGEREX_CFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRIGGEREX_CFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

void CDlgVcaITCTriggerCfg::OnSelchangeComboTriggerMode() 
{
	// TODO: Add your control notification handler code here
	m_iTriggerMode = m_comTriggerMode.GetCurSel();
	int i = m_comTriggerMode.GetCurSel();
	if (0 == i)
	{
		GetDlgItem(IDC_COMBO_DETSCENE_ID)->EnableWindow(FALSE); 
		GetDlgItem(IDC_EDIT_LANE_NUM)->EnableWindow(TRUE);  
		GetDlgItem(IDC_COMBO_SOURCE_TYPE)->EnableWindow(FALSE); 
		GetDlgItem(IDC_COMBO_LANE_NUMBER)->EnableWindow(TRUE); 
		GetDlgItem(IDC_EDIT_ASSOCIATE_LANENO)->EnableWindow(TRUE); 
		GetDlgItem(IDC_COMBO_LANE_USEAGETYPE)->EnableWindow(TRUE); 
		GetDlgItem(IDC_COMBO_LANE_DIRECTION)->EnableWindow(TRUE); 
		GetDlgItem(IDC_COMBO_DRIVE_DIRECTION)->EnableWindow(TRUE); 
		GetDlgItem(IDC_EDIT_SCENENAME)->EnableWindow(FALSE); 
		GetDlgItem(IDC_COMBO_IO_NO)->EnableWindow(FALSE); 
		GetDlgItem(IDC_COMBO_TRIGGER_TYPE)->EnableWindow(FALSE); 
		GetDlgItem(IDC_COMBO_RELATE_CHAN)->EnableWindow(FALSE); 
		GetDlgItem(IDC_COMBO_PROVINCE_TYPE)->EnableWindow(FALSE); 
	}
	else if (1 == i)
	{
		GetDlgItem(IDC_COMBO_DETSCENE_ID)->EnableWindow(TRUE); 
		GetDlgItem(IDC_EDIT_LANE_NUM)->EnableWindow(TRUE);  
		GetDlgItem(IDC_COMBO_SOURCE_TYPE)->EnableWindow(TRUE); 
		GetDlgItem(IDC_COMBO_LANE_NUMBER)->EnableWindow(TRUE); 
		GetDlgItem(IDC_EDIT_ASSOCIATE_LANENO)->EnableWindow(TRUE); 
		GetDlgItem(IDC_COMBO_LANE_USEAGETYPE)->EnableWindow(FALSE); 
		GetDlgItem(IDC_COMBO_LANE_DIRECTION)->EnableWindow(FALSE); 
		GetDlgItem(IDC_COMBO_DRIVE_DIRECTION)->EnableWindow(TRUE); 
		GetDlgItem(IDC_EDIT_SCENENAME)->EnableWindow(TRUE); 
		GetDlgItem(IDC_COMBO_IO_NO)->EnableWindow(TRUE); 
		GetDlgItem(IDC_COMBO_TRIGGER_TYPE)->EnableWindow(TRUE); 
		GetDlgItem(IDC_COMBO_RELATE_CHAN)->EnableWindow(TRUE); 
		GetDlgItem(IDC_COMBO_PROVINCE_TYPE)->EnableWindow(TRUE); 
	}
	else if (2 == i)
    {
        GetDlgItem(IDC_COMBO_DETSCENE_ID)->EnableWindow(TRUE); 
        GetDlgItem(IDC_EDIT_LANE_NUM)->EnableWindow(TRUE);  
        GetDlgItem(IDC_COMBO_SOURCE_TYPE)->EnableWindow(FALSE); 
        GetDlgItem(IDC_COMBO_LANE_NUMBER)->EnableWindow(TRUE); 
        GetDlgItem(IDC_EDIT_ASSOCIATE_LANENO)->EnableWindow(TRUE); 
        GetDlgItem(IDC_COMBO_LANE_USEAGETYPE)->EnableWindow(FALSE); 
        GetDlgItem(IDC_COMBO_LANE_DIRECTION)->EnableWindow(FALSE); 
        GetDlgItem(IDC_COMBO_DRIVE_DIRECTION)->EnableWindow(TRUE); 
        GetDlgItem(IDC_EDIT_SCENENAME)->EnableWindow(TRUE); 
        GetDlgItem(IDC_COMBO_IO_NO)->EnableWindow(FALSE); 
        GetDlgItem(IDC_COMBO_TRIGGER_TYPE)->EnableWindow(FALSE); 
        GetDlgItem(IDC_COMBO_RELATE_CHAN)->EnableWindow(FALSE); 
		GetDlgItem(IDC_COMBO_PROVINCE_TYPE)->EnableWindow(TRUE); 
    }
	OnSelchangeComboSourceType();

}

void CDlgVcaITCTriggerCfg::OnSelchangeComboSourceType() 
{
	// TODO: Add your control notification handler code here
	int i = m_comSourceType.GetCurSel();
	if (0 == i)
	{
		GetDlgItem(IDC_COMBO_IO_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_TRIGGER_TYPE)->EnableWindow(FALSE); 
		GetDlgItem(IDC_COMBO_RELATE_CHAN)->EnableWindow(FALSE); 
	}
	else if (1 == i)
	{
		GetDlgItem(IDC_COMBO_IO_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_TRIGGER_TYPE)->EnableWindow(TRUE); 
		GetDlgItem(IDC_COMBO_RELATE_CHAN)->EnableWindow(FALSE); 
	}
	else if (2 == i)
	{
		GetDlgItem(IDC_COMBO_IO_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_TRIGGER_TYPE)->EnableWindow(FALSE); 
		GetDlgItem(IDC_COMBO_RELATE_CHAN)->EnableWindow(TRUE); 
	}
}

void CDlgVcaITCTriggerCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	
	GetITCTriggerCfg();
	LoadWndContent();

}

void CDlgVcaITCTriggerCfg::OnBtnGetCurtriggermode() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_CURTRIGGERMODE struTrigCfg = {0};
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_CURTRIGGERMODE, m_lChannel, &struTrigCfg, sizeof(struTrigCfg), &dwReturn))
     {
     	g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITC_GET_TRIGGERCFG Chan[%d]", m_lChannel);
         return ;
     }
	else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITC_GET_TRIGGERCFG Chan[%d]", m_lChannel);
    }

    if (struTrigCfg.dwTriggerType == ITC_POST_MPR_TYPE )
    {
    	m_comTriggerMode.SetCurSel(1);
    } 
    else if (struTrigCfg.dwTriggerType == IPC_POST_HVT_TYPE)
    {
         m_comTriggerMode.SetCurSel(2);
    }
     else if(struTrigCfg.dwTriggerType == ITC_VIA_VIRTUALCOIL_TYPE)
    {
     	m_comTriggerMode.SetCurSel(0);
    }

    OnSelchangeComboSourceType();
}

void CDlgVcaITCTriggerCfg::OnBtnSetCurtriggermode() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_CURTRIGGERMODE struTrigCfg = {0};
    struTrigCfg.dwSize = sizeof(struTrigCfg);
    if (m_comTriggerMode.GetCurSel() == 0)
    {
        struTrigCfg.dwTriggerType = ITC_VIA_VIRTUALCOIL_TYPE;
    } 
    else if (m_comTriggerMode.GetCurSel() == 1)
    {
        struTrigCfg.dwTriggerType = ITC_POST_MPR_TYPE;
    }
    else if (m_comTriggerMode.GetCurSel() == 2)
    {
        struTrigCfg.dwTriggerType = IPC_POST_HVT_TYPE;
    }
    
    
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_CURTRIGGERMODE, m_lChannel, &struTrigCfg, sizeof(struTrigCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CURTRIGGERMODE Chan[%d]", m_lChannel);
        return ;
    }
	else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CURTRIGGERMODE Chan[%d]", m_lChannel);
    }
}

void CDlgVcaITCTriggerCfg::OnBtnGetCalibration() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struCalibration;
    struCfg.dwOutSize = sizeof(m_struCalibration);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_VEHICLE_CALIBRATION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VEHICLE_CALIBRATION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VEHICLE_CALIBRATION");
    }
}

void CDlgVcaITCTriggerCfg::OnBtnBlackwhitelstUpload() 
{
	// TODO: Add your control notification handler code here

	char szLan[256] = {0};
	if (m_lUploadHandle != -1)
	{
        g_StringLanType(szLan, "上传已经开始", "Already start upload");
        AfxMessageBox(szLan);
        return;
	}

	m_bStop = FALSE;
	
// 	m_hFile = CreateFile(m_szFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
// // 	if (INVALID_HANDLE_VALUE == m_hFile)
// // 	{
// // 		g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
// // 		AfxMessageBox(szLan);
// // 		return;
// // 	}
// 	BY_HANDLE_FILE_INFORMATION struFileInfo = {0}; 
// 	if(!GetFileInformationByHandle(m_hFile, &struFileInfo))
// 	{
// 		g_StringLanType(szLan, "获取文件信息失败", "Get file info failed ");
// 		AfxMessageBox(szLan);
// 		return;
// 	}
// 	
// 	INT64 iFileSize = (((INT64)struFileInfo.nFileSizeHigh << 32)) + (INT64)struFileInfo.nFileSizeLow;
// 	if (iFileSize == 0)
// 	{
// 		g_StringLanType(szLan, "文件为空", "Configure file is empty");
// 		AfxMessageBox(szLan);
// 		return;
// 	}
	
// 	//打开上传句柄
// 	
// 	NET_DVR_UPLOAD_DB_IN struUploadDBIn = {0};
// 	NET_DVR_UPLOAD_DB_OUT struUploadDBOut = {0};
// 	if (m_strFileID == "")
// 	{
// 		struUploadDBIn.byContinueUpload = 0;
// 		struUploadDBIn.i64FileLen = iFileSize;
// 	}
// 	else
// 	{
// 		//断点续传可以不给长度
// 		struUploadDBIn.byContinueUpload = 1;
// 	}

	char szFilePath[256] = {0};
	sprintf(szFilePath, "%s", m_szFilePath.GetBuffer(0));
	
	m_lUploadHandle = NET_DVR_UploadFile_V40(m_lServerID, UPLOAD_VEHICLE_BLACKWHITELST_FILE, NULL, 0, szFilePath, NULL, 0);
    //m_lUploadHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_VEHICLE_BLACKWHITELST_FILE, &struUploadDBIn, sizeof(struUploadDBIn), m_strFileID, &struUploadDBOut, sizeof(struUploadDBOut));
    if (m_lUploadHandle < 0)
    {
		g_StringLanType(szLan, "上传失败", "Upload Failed");
		sprintf(szLan, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());     
        AfxMessageBox(szLan);
		m_strUploadStatus.Format(szLan);
        return;	
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "UPLOAD_VEHICLE_BLACKWHITELST_FILE");
		SetTimer(UPLOAD_BLACK_WHITE_CONFIGURATION_FILE_TIMER, 50, NULL);
		g_StringLanType(szLan, "开始上传", "Start upload");
		m_strUploadStatus.Format(szLan);
    }
	
/*
    m_hUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(UpLoadSendThread), this, 0, &m_dwThreadId);
    if (m_hUpLoadThread  == NULL)
    {
        g_StringLanType(szLan, "打开上传线程失败!", "Open UpLoad thread Fail!");
        AfxMessageBox(szLan);
        return;
    }
	
	//更新界面文件ID
	//m_strFileID.Format("%s", struUploadDBOut.szFileID);

	*/
	UpdateData(FALSE);
}

void CDlgVcaITCTriggerCfg::OnBtnBlackwhitelstDownload() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szFilePath[256] = {0};
	sprintf(szFilePath, "%s", m_szFilePath.GetBuffer(0));
	char szLan[1024] = {0};
	//m_iRecvFailedNum = 0;
    //m_strOutput = "";
    //m_bProcessing = FALSE;

	if (m_lDownloadHandle != -1)
	{
		g_StringLanType(szLan, "下载中，先停止下载", "It's downloading,stop download please.");
		AfxMessageBox(szLan);
		return;
	}
	
	m_lDownloadHandle = NET_DVR_StartDownload(m_lServerID, NET_SDK_DOWNLOAD_VEHICLE_BLACKWHITELST_FILE, NULL, 0, szFilePath);
	if (m_lDownloadHandle >= 0)
	{
 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload succ[%s]", szFilePath);
 		m_timerHandle = SetTimer(DOWNLOAD_BLACK_WHITE_CONFIGURATION_FILE_TIMER, 50, NULL);
		g_StringLanType(szLan, "开始下载", "Start download");
		m_strDownloadStatus.Format(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload err[%d]", NET_DVR_GetLastError());
		g_StringLanType(szLan, "下载失败", "Download failed");
		//AfxMessageBox(szLan);
		m_strDownloadStatus.Format(szLan);
	}
	UpdateData(FALSE);
}

void CDlgVcaITCTriggerCfg::OnBtnBlackwhitelstDownloadStop() 
{
	// TODO: Add your control notification handler code here

	char szLan[256] = {0};
	if (m_lDownloadHandle != -1)
	{
		if (!NET_DVR_StopDownload(m_lDownloadHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload err[%d]", NET_DVR_GetLastError());
			g_StringLanType(szLan, "停止下载失败", "NET_DVR_StopDownload failed.");
			AfxMessageBox(szLan);
		} 
		else
		{
			KillTimer(m_timerHandle);
			m_lDownloadHandle = -1;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload succ");
			g_StringLanType(szLan, "停止下载", "Stop download");
			m_strDownloadStatus.Format(szLan);
		}
	}
	UpdateData(FALSE);
}


void CDlgVcaITCTriggerCfg::OnBtnBlackwhitelstUploadStop() 
{
	// TODO: Add your control notification handler code here
	
	char szLan[256] = {0};
	if (m_lUploadHandle != -1)
	{
		if (!NET_DVR_UploadClose(m_lUploadHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose err[%d]", NET_DVR_GetLastError());
			g_StringLanType(szLan, "停止上传失败", "NET_DVR_UploadClose failed.");
			AfxMessageBox(szLan);
		} 
		else
		{
			m_bStop = TRUE;
			KillTimer(m_timerHandle);
			m_lUploadHandle = -1;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose succ");
			g_StringLanType(szLan, "停止上传", "Stop upload");
			m_strUploadStatus.Format(szLan);
		}
	}
	UpdateData(FALSE);
}

void CDlgVcaITCTriggerCfg::OnBtnBlackwhitelistBrowse()
{
	UpdateData(TRUE);
	
	static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE,"*.*", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
		m_szFilePath = dlg.GetPathName();
        //szFileName = dlg.GetPathName();
        UpdateData(FALSE);
	}
}

void CDlgVcaITCTriggerCfg::OnSelchangeComboRoadType() 
{
	// TODO: Add your control notification handler code here
    const NET_ITC_POST_MPR_PARAM& struMprParam = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr;
    if (m_cmbRoadType.GetCurSel() == 2)
    {
        GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(FALSE);
    }
    UpdateData(FALSE);
}



void CDlgVcaITCTriggerCfg::OnBnClickedBtnDrawSnapLine()
{
    if (1 == m_iTriggerMode)
    {
        NET_VCA_LINE& struSnapLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struPostMpr.struSnapLine;
        memset(&struSnapLine, 0, sizeof(struSnapLine));
        m_bFirstDrawSnapLine = TRUE;
        m_nCurDrawType = DRAW_TYPE_SNAP_LINE;
    }
    else if (2 == m_iTriggerMode)
    {
        NET_VCA_LINE& struSnapLine = m_struItcTriggerCfg.struTriggerParam.uTriggerParam.struIpcHvt.struSnapLine;
        memset(&struSnapLine, 0, sizeof(struSnapLine));
        m_bFirstDrawSnapLine = TRUE;
        m_nCurDrawType = DRAW_TYPE_SNAP_LINE;
    }
}

