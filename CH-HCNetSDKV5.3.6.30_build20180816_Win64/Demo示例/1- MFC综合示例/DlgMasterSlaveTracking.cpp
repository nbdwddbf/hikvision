// DlgMasterSlaveTracking.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMasterSlaveTracking.h"
#include "DlgSlaveCameraInfo.h"
#include "DlgPtzCtrl.h"

#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CDlgMasterSlaveTracking *g_pDlgMasterSlaveTracking = NULL;
/////////////////////////////////////////////////////////////////////////////
// CDlgMasterSlaveTracking dialog


void CDlgMasterSlaveTracking::F_DrawFrame(HDC hDc)
{
//     DRAW_POLYGON_PARAM struPolygonParam;
//     memset(&struPolygonParam, 0, sizeof(struPolygonParam));
//     struPolygonParam.color = RGB(255, 255, 0);
//     memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
//     memcpy(&struPolygonParam.struVcaPolygon, &m_struTracking.struRegion, sizeof(m_struTracking.struRegion));
//     struPolygonParam.bCloseIn = m_bCloseIn;
//     struPolygonParam.bMouseMove = m_bMouseMove;

	DRAW_POLYGON_PARAM_EX struPolygonParam;
	memset(&struPolygonParam,0,sizeof(struPolygonParam));
	struPolygonParam.color = RGB(255, 0, 0);
	memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
	struPolygonParam.pArryPt = m_struTracking.struRegion.struPos;
	struPolygonParam.dwPtNum = m_struTracking.struRegion.dwPointNum;
    CDrawFun::DrawPolygonEx(hDc, &struPolygonParam);
	
//     if (m_bFilterActive)
//     {
//         DRAW_RECT_PARAM struDrawRect;
//         memset(&struDrawRect, 0, sizeof(struDrawRect));
//         struDrawRect.color = RGB(0, 255, 125);
//         memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
//         memcpy(&struDrawRect.struVcaRect, &m_struFaceDetectRule.struSizeFilter.struMaxRect, sizeof(struDrawRect.struVcaRect));
//         CDrawFun::DrawVcaRect(hDc, &struDrawRect);
//         
//         memset(&struDrawRect, 0, sizeof(struDrawRect));
//         struDrawRect.color = RGB(0, 255, 125);
//         memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
//         memcpy(&struDrawRect.struVcaRect, &m_struFaceDetectRule.struSizeFilter.struMiniRect, sizeof(struDrawRect.struVcaRect));
//         CDrawFun::DrawVcaRect(hDc, &struDrawRect);
//     }
	
}

void CALLBACK g_DrawSlaveMaster(LONG lRealHandle, HDC hDc, DWORD dwUser)
{  

	g_pDlgMasterSlaveTracking->F_DrawFrame(hDc);
	
}

CDlgMasterSlaveTracking::CDlgMasterSlaveTracking(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMasterSlaveTracking::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMasterSlaveTracking)
	m_iTrackingTime = 0;
	m_iCoefficient = 0;
    m_iHorValue = 0;
    m_iVerValue = 0;
    m_dwChannel = 1;
    m_fInitialP = 0.0f;
    m_fInitialT = 0.0f;
    m_fInitialZ = 0.0f;
    m_fAdjustP = 0.0f;
    m_fAdjustT = 0.0f;
    m_fAdjustZ = 0.0f;
    m_fLeftposX = 0.0f;
    m_fLeftposY = 0.0f;
    m_fRightposX = 0.0f;
    m_fRightposY = 0.0f;
	//}}AFX_DATA_INIT
	m_lChannel = 1;
	m_bTrackMode = FALSE;
	memset(m_lPlayHandle, 0, sizeof(LONG)*4);
	memset(&m_struSlaveCameraStatus, 0, sizeof(m_struSlaveCameraStatus));
	memset(&m_struSlaveCameraCalibCfg, 0, sizeof(m_struSlaveCameraCalibCfg));
	memset(&m_struTrackMode, 0, sizeof(m_struTrackMode));
	memset(&m_struTracking, 0, sizeof(m_struTracking));
	memset(&m_struRegionTemp, 0, sizeof(m_struRegionTemp));
    memset(&m_struTrackPoint, 0, sizeof(m_struTrackPoint));
    memset(&m_struTrackInitPostion, 0, sizeof(m_struTrackInitPostion));
    memset(&m_struManualTrackRatio, 0, sizeof(m_struManualTrackRatio));
    memset(&m_struPoint, 0, sizeof(m_struPoint));
    memset(&m_struBvCalibPosotion, 0, sizeof(m_struBvCalibPosotion));
    
	m_bCloseIn = FALSE;
	m_bMouseMove = FALSE;

	for (int i=0; i<5; i++)
	{
		m_lPlayHandle[i] = -1;
	}
}

CDlgMasterSlaveTracking::~CDlgMasterSlaveTracking()
{
	for (int i = 0; i<5; i++)
	{
		if (m_lPlayHandle[i] >= 0)
		{
			NET_DVR_StopRealPlay(m_lPlayHandle[i]);
			m_lPlayHandle[i] = -1;
		}
	}

}

void CDlgMasterSlaveTracking::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMasterSlaveTracking)
    DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChannel);
	DDX_Control(pDX, IDC_COMBO_TRACKMODE, m_comboTrackMode);
	DDX_Control(pDX, IDC_COMBO_CALIBMODE, m_comboCalibMode);
	DDX_Control(pDX, IDC_LIST_CALIB, m_lstCalib);
	DDX_Control(pDX, IDC_COMBO_SLAVE_CAMERAID, m_comboSlaveCameraID);
	DDX_Text(pDX, IDC_EDIT_TRACKING_TIME, m_iTrackingTime);
	DDX_Text(pDX, IDC_EDIT_TRACKING_RATIO, m_iCoefficient);
    DDX_Text(pDX, IDC_EDIT_HORVALUE, m_iHorValue);
    DDX_Text(pDX, IDC_EDIT_VERVALUE, m_iVerValue);
    DDX_Text(pDX, IDC_EDIT_InitialP, m_fInitialP);
    DDX_Text(pDX, IDC_EDIT_InitialT, m_fInitialT);
    DDX_Text(pDX, IDC_EDIT_InitialZ, m_fInitialZ);
    DDX_Text(pDX, IDC_EDIT_AdjustP, m_fAdjustP);
    DDX_Text(pDX, IDC_EDIT_AdjustT, m_fAdjustT);
    DDX_Text(pDX, IDC_EDIT_AdjustZ, m_fAdjustZ);
    DDX_Text(pDX, IDC_EDIT_LeftposX, m_fLeftposX);
    DDX_Text(pDX, IDC_EDIT_LeftposY, m_fLeftposY);
    DDX_Text(pDX, IDC_EDIT_RightposX, m_fRightposX);
    DDX_Text(pDX, IDC_EDIT_RightposY, m_fRightposY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMasterSlaveTracking, CDialog)
	//{{AFX_MSG_MAP(CDlgMasterSlaveTracking)
	ON_BN_CLICKED(IDC_BTN_LOGIN_SLAVE1, OnBtnLoginSlave1)
	ON_BN_CLICKED(IDC_BTN_PREVIEW_SLAVE1, OnBtnPreviewSlave)
	ON_BN_CLICKED(IDC_BTN_PTZ, OnBtnPtz)
	ON_BN_CLICKED(IDC_BTN_REFLASH_SLAVE_STATUS, OnBtnReflashSlaveStatus)
	ON_BN_CLICKED(IDC_BTN_TACKINGRATIO, OnBtnTackingratio)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_REFUSH, OnBtnRefush)
	ON_BN_CLICKED(IDC_BTN_TRACKCFG, OnBtnTrackcfg)
	ON_BN_CLICKED(IDC_BTN_CALIB, OnBtnCalib)
	ON_BN_CLICKED(IDC_BTN_CALIB_DEL, OnBtnCalibDel)
	ON_CBN_SELCHANGE(IDC_COMBO_TRACKMODE, OnSelchangeComboTrackmode)
	ON_BN_CLICKED(IDC_BTN_CONTROL_PTZ_MANUALTRACE, OnBtnControlPtzManualtrace)
	ON_BN_CLICKED(IDC_BTN_TACK_INITPOSITION, OnBtnTackInitposition)
	ON_BN_CLICKED(_SET_TRACKRATIO, OnSetTrackratio)
	ON_BN_CLICKED(IDC_BTN_GET_TRACKRATIO, OnBtnGetTrackratio)
    ON_BN_CLICKED(IDC_BUTTON_PTZ_ADJUST, OnButtonPtzAdjust)
    ON_BN_CLICKED(IDC_BUTTON_AdjustPTZ, OnBUTTONAdjustPTZ)
    ON_BN_CLICKED(IDC_BUTTON_GET_HUMAN_CALIB, OnButtonGetHumanCalib)
    ON_BN_CLICKED(IDC_BUTTON_SET_HUMAN_CALIB, OnButtonSetHumanCalib)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMasterSlaveTracking message handlers

BOOL CDlgMasterSlaveTracking::SlaveLoginPlay(char *sDVRIP, WORD wDVRPort, char *sUserName, char *sPassword, NET_DVR_CLIENTINFO* struClientInfo, int index)
{
	NET_DVR_DEVICEINFO_V30 struDeviceInfoV30 ={0};
	m_lUserID[index] = NET_DVR_Login_V30(sDVRIP, wDVRPort, sUserName, sPassword, &struDeviceInfoV30);
	if (m_lUserID[index] < 0)
	{
		DWORD nErr = NET_DVR_GetLastError();
	}

    Play(struClientInfo, m_lUserID[index], index);

	return TRUE;
}

BOOL CDlgMasterSlaveTracking::Play(NET_DVR_CLIENTINFO* struClientInfo, LONG loginID, int index)
{
	char szLan[128] = {0};
	char szTemp[256] = {0};
	
	if (m_lPlayHandle[index] >= 0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle[index]);
		m_lPlayHandle[index] = -1;
	}

    if (index > 0)
    {
        struClientInfo->lChannel = m_comboChannel.GetCurSel();
    }

	m_lPlayHandle[index] = NET_DVR_RealPlay_V30(loginID, struClientInfo, NULL, NULL, TRUE); 
	BOOL bRet = FALSE;
	if (m_lPlayHandle[index] < 0)
	{
		g_StringLanType(szLan, "Ô¤ÀÀÊ§°Ü", "Realplay failed");
		sprintf(szTemp, "%s %s ErrCode:%d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
        AfxMessageBox(szTemp);
		return FALSE;
	}
	
	//bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawRoiDetectShow, 0);
	UpdateData(FALSE);
	return TRUE;
}

void CDlgMasterSlaveTracking::OnBtnLoginSlave1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDlgSlaveCameraInfo dlg;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;

	m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel()+1;
	m_struSlaveCameraCond.dwChannel = m_lChannel;
	m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);

 	dlg.m_struSlaveCameraCond = m_struSlaveCameraCond;
// 	dlg.m_struSlaveCameraCfg = &m_struSlaveCameraCfg;

	dlg.DoModal();
}

void CDlgMasterSlaveTracking::OnBtnPreviewSlave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = {0};
// 
 	m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel()+1;
 	m_struSlaveCameraCond.dwChannel = m_lChannel;
 	m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);
// 
    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpOutBuffer = &m_struSlaveCameraCfg;
    struCfg.dwOutSize = sizeof(m_struSlaveCameraCfg);
// 
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
//     
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_SLAVECAMERA, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SLAVECAMERA");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SLAVECAMERA");        
    }

	NET_DVR_CLIENTINFO struPlayInfo; 
	memset(&struPlayInfo, 0, sizeof(NET_DVR_CLIENTINFO));
	
	if (m_struSlaveCameraCond.byID == 1)
	{
		struPlayInfo.hPlayWnd = GetDlgItem(IDC_SLAVE1_PLAYWND)->GetSafeHwnd();
	}
	else if (m_struSlaveCameraCond.byID == 2)
	{
		struPlayInfo.hPlayWnd = GetDlgItem(IDC_SLAVE2_PLAYWND)->GetSafeHwnd();
	}
	else if (m_struSlaveCameraCond.byID == 3)
	{
		struPlayInfo.hPlayWnd = GetDlgItem(IDC_SLAVE3_PLAYWND)->GetSafeHwnd();
	}
	else if (m_struSlaveCameraCond.byID == 4)
	{
		struPlayInfo.hPlayWnd = GetDlgItem(IDC_SLAVE4_PLAYWND)->GetSafeHwnd();
	}
    
	struPlayInfo.lChannel = m_lChannel;
	struPlayInfo.lLinkMode = 0;


//  	SlaveLoginPlay(g_struLocalParam.struSlaveCameraCfg[m_struSlaveCameraCond.byID].unionServer.struAddrIP.struIp.sIpV4, \
// 		g_struLocalParam.struSlaveCameraCfg[m_struSlaveCameraCond.byID].wPort, \
//  		(char*)g_struLocalParam.struSlaveCameraCfg[m_struSlaveCameraCond.byID].szUserName, \
// 		(char*)g_struLocalParam.struSlaveCameraCfg[m_struSlaveCameraCond.byID].szPassWord, \
// 		&struPlayInfo, m_struSlaveCameraCond.byID);

    SlaveLoginPlay(m_struSlaveCameraCfg.unionServer.struAddrIP.struIp.sIpV4,\
        m_struSlaveCameraCfg.wPort,(char*)m_struSlaveCameraCfg.szUserName,(char*)m_struSlaveCameraCfg.szPassWord,\
        &struPlayInfo, m_struSlaveCameraCond.byID);

}



BOOL CDlgMasterSlaveTracking::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_lstCalib.SetExtendedStyle(m_lstCalib.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_lstCalib.InsertColumn(0, "ÐòºÅ", LVCFMT_LEFT, 50, -1);	
	m_lstCalib.InsertColumn(1, "×ø±ê(x,y)", LVCFMT_LEFT, 100, -1);	
	m_lstCalib.InsertColumn(2, "PTZÎ»ÖÃ(p,t,z)", LVCFMT_LEFT, 150, -1);

	CString  strTemp;
	for (int i=0; i < 6; i++)
	{
		strTemp.Format("%02d", i+1);
		m_lstCalib.InsertItem(i, strTemp);
	}
    m_comboTrackMode.SetCurSel(0);
	m_comboSlaveCameraID.SetCurSel(0);
	m_comboCalibMode.SetCurSel(0);

	NET_DVR_CLIENTINFO struPlayInfo; 
	memset(&struPlayInfo, 0, sizeof(NET_DVR_CLIENTINFO));

	struPlayInfo.hPlayWnd = GetDlgItem(IDC_MASTER_PLAYWND)->GetSafeHwnd();
	struPlayInfo.lChannel = 1;
 	struPlayInfo.lLinkMode = 0;

	g_pDlgMasterSlaveTracking = this;
	Play(&struPlayInfo, m_lLoginID, 0);
	BOOL bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle[0], g_DrawSlaveMaster, 0);

    m_comboChannel.SetCurSel(1);
    //StartRealPlay(GetDlgItem(IDC_MASTER_PLAYWND)->GetSafeHwnd(),g_DrawSlaveMaster,this, );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMasterSlaveTracking::OnBtnPtz() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int index = m_comboSlaveCameraID.GetCurSel()+1;
	CDlgPtzCtrl dlg;
	dlg.m_lPlayHandle = m_lPlayHandle[index];
    dlg.DoModal();
}

void CDlgMasterSlaveTracking::OnBtnReflashSlaveStatus() 
{
	// TODO: Add your control notification handler code here
	
    NET_DVR_STD_CONFIG struCfg = {0};

    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struSlaveCameraStatus;
    struCfg.dwOutSize = sizeof(m_struSlaveCameraStatus);

    memset(m_szStatusBuf, 0, 1024);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = 1024;
    
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_SLAVECAMERA_STATUS, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SLAVECAMERA_STATUS ");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SLAVECAMERA_STATUS ");        
    }

	CString str;
	if (m_struSlaveCameraStatus.struSlaveCamera[0].byLinkStatus == 0)
	{
		str.Format("OffLine");
	}
	else
	{
		str.Format("OnLine");
	}
	GetDlgItem(IDC_STATIC_SLAVE_STATUS1)->SetWindowText(str);

	if (m_struSlaveCameraStatus.struSlaveCamera[1].byLinkStatus == 0)
	{
		str.Format("OffLine");
	}
	else
	{
		str.Format("OnLine");
	}
	GetDlgItem(IDC_STATIC_SLAVE_STATUS2)->SetWindowText(str);
	
	if (m_struSlaveCameraStatus.struSlaveCamera[2].byLinkStatus == 0)
	{
		str.Format("OffLine");
	}
	else
	{
		str.Format("OnLine");
	}
	GetDlgItem(IDC_STATIC_SLAVE_STATUS3)->SetWindowText(str);

	if (m_struSlaveCameraStatus.struSlaveCamera[3].byLinkStatus == 0)
	{
		str.Format("OffLine");
	}
	else
	{
		str.Format("OnLine");
	}
	GetDlgItem(IDC_STATIC_SLAVE_STATUS4)->SetWindowText(str);
	

	UpdateData(FALSE);
}

void CDlgMasterSlaveTracking::OnBtnTackingratio() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel()+1;
	m_struSlaveCameraCond.dwChannel = m_lChannel;
	m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);
    
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &m_struSlaveCameraCond;
    struControl.dwCondSize = sizeof(m_struSlaveCameraCond);

    memset(m_szStatusBuf, 0, 1024);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = 1024;
	
    if (!NET_DVR_STDControl(m_lLoginID, NET_DVR_SET_TRACKINGRATIO, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TACKINGRATIO");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TACKINGRATIO");
    }
}

void CDlgMasterSlaveTracking::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel()+1;
	m_struSlaveCameraCond.dwChannel = m_lChannel;
	m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);

	m_struSlaveCameraCalibCfg.dwSize = sizeof(m_struSlaveCameraCalibCfg);
	m_struSlaveCameraCalibCfg.byCalibMode = m_comboCalibMode.GetCurSel();
//	m_struSlaveCameraCalibCfg.wTrackingTime = m_iTrackingTime;

    NET_DVR_STD_CONFIG struCfg = {0};
	
    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpInBuffer = &m_struSlaveCameraCalibCfg;
    struCfg.dwInSize = sizeof(m_struSlaveCameraCalibCfg);
	
    memset(m_szStatusBuf, 0, 1024);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = 1024;

    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_SLAVECAMERA_CALIB_V50, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SLAVECAMERA_CALIB_V50");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SLAVECAMERA_CALIB_V50");
    }

}

void CDlgMasterSlaveTracking::OnBtnRefush() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	
	m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel()+1;
	m_struSlaveCameraCond.dwChannel = m_lChannel;
	m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);
	
	m_struSlaveCameraCalibCfg.dwSize = sizeof(m_struSlaveCameraCalibCfg);
		
    NET_DVR_STD_CONFIG struCfg = {0};
	
    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpOutBuffer = &m_struSlaveCameraCalibCfg;
    struCfg.dwOutSize = sizeof(m_struSlaveCameraCalibCfg);
	
    memset(m_szStatusBuf, 0, 1024);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = 1024;

	if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_SLAVECAMERA_CALIB_V50, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SLAVECAMERA_CALIB_V50");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SLAVECAMERA_CALIB_V50");
    }
	
	m_comboCalibMode.SetCurSel(m_struSlaveCameraCalibCfg.byCalibMode);
	SetDataToCalibList(&m_struSlaveCameraCalibCfg);

    UpdateData(FALSE);
}

BOOL CDlgMasterSlaveTracking::SetDataToCalibList(NET_DVR_SLAVECAMERA_CALIB_V50* m_struSlaveCameraCalibCfg)
{
	CString strTemp;
	m_lstCalib.DeleteAllItems();
	for (int i=0; i < MAX_CALIB_NUM_EX; i++)
	{		
		strTemp.Format("%02d", i+1);
		m_lstCalib.InsertItem(i, strTemp);

		strTemp.Format("(%.3f,%.3f)", m_struSlaveCameraCalibCfg->struCalibParam[i].struCalibCoordinates.fX, \
			m_struSlaveCameraCalibCfg->struCalibParam[i].struCalibCoordinates.fY);
		m_lstCalib.SetItemText(i, 1, strTemp);

		strTemp.Format("(%.1f,%.1f,%.1f)", m_struSlaveCameraCalibCfg->struCalibParam[i].struPtzInfo.fPan, \
			m_struSlaveCameraCalibCfg->struCalibParam[i].struPtzInfo.fTilt, \
			m_struSlaveCameraCalibCfg->struCalibParam[i].struPtzInfo.fZoom);
		m_lstCalib.SetItemText(i, 2, strTemp);

        m_iVerValue = m_struSlaveCameraCalibCfg->struCalibParam[i].iVerValue;
        m_iHorValue = m_struSlaveCameraCalibCfg->struCalibParam[i].iHorValue;
	}
	return TRUE;
}

BOOL CDlgMasterSlaveTracking::PreTranslateMessage(MSG* pMsg) 
{
	UpdateData(TRUE);
	int index = m_comboSlaveCameraID.GetCurSel();
	CPoint pt(0,0);
	GetDlgItem(IDC_MASTER_PLAYWND)->GetWindowRect(&m_rcWnd);
    GetCursorPos(&pt);
	ScreenToClient(&m_rcWnd);
	ScreenToClient(&pt);
    CString strTemp = _T("");
    DWORD i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    
    switch(pMsg->message)  // Message of Draw
    {
    case WM_LBUTTONDOWN:
        if((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))//Press CTRL to draw
        {
			if(PtInRect(&m_rcWnd,pt))
			{
                m_struTrackPoint.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struTrackPoint.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                OnBtnControlPtzManualtrace();

				memset(&m_struTracking.struRegion, 0, sizeof(m_struTracking.struRegion));
				int nItem = m_lstCalib.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);

				m_struSlaveCameraCalibCfg.struCalibParam[nItem].struCalibCoordinates.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
				m_struSlaveCameraCalibCfg.struCalibParam[nItem].struCalibCoordinates.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
				
                if (!m_bMouseMove && (m_comboTrackMode.GetCurSel() == 1))
                {
                    m_struTrackMode.uModeParam.struManualCtrl.struCtrlPoint.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                    m_struTrackMode.uModeParam.struManualCtrl.struCtrlPoint.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                    
                    m_struTracking.struRegion.struPos[0].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                    m_struTracking.struRegion.struPos[0].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                    
                    m_struTracking.struRegion.dwPointNum = 1;
                    
				    m_bMouseMove = TRUE;
                }

			}
		}
		break;
	case WM_MOUSEMOVE:
		if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && m_comboTrackMode.GetCurSel() == 1)
		{
			if (PtInRect(&m_rcWnd,pt) && m_bMouseMove)
			{

				m_struTracking.struRegion.struPos[1].fX = m_struTracking.struRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
				m_struTracking.struRegion.struPos[1].fY = m_struTracking.struRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;

				m_struTracking.struRegion.struPos[3].fX = m_struTracking.struRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
				m_struTracking.struRegion.struPos[3].fY = m_struTracking.struRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;

				m_struTracking.struRegion.struPos[2].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
				m_struTracking.struRegion.struPos[2].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();

				m_struTracking.struRegion.dwPointNum = 4;

				memcpy(&m_struRegionTemp, &m_struTracking.struRegion, sizeof(NET_VCA_POLYGON));
			}
		}
		
		break;

	case WM_LBUTTONUP:
// 		if( m_comboTrackMode.GetCurSel() == 1)
// 		{
// 		//	m_bCloseIn = TRUE;
		if((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && m_comboTrackMode.GetCurSel() == 1)//Press CTRL to draw
        {
			m_struTracking.struRegion.struPos[1].fX = m_struTracking.struRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
			m_struTracking.struRegion.struPos[1].fY = m_struTracking.struRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
			
			m_struTracking.struRegion.struPos[3].fX = m_struTracking.struRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
			m_struTracking.struRegion.struPos[3].fY = m_struTracking.struRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
			
			m_struTracking.struRegion.struPos[2].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
			m_struTracking.struRegion.struPos[2].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();

			memcpy(&m_struRegionTemp, &m_struTracking.struRegion, sizeof(NET_VCA_POLYGON));
 		}
		m_bMouseMove = FALSE;
		break;
	default:
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgMasterSlaveTracking::OnBtnTrackcfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_comboTrackMode.GetCurSel() == 0)
	{
		m_struTracking.byEnable = 0;
		m_struTracking.byMode = 0;
	}
	else if (m_comboTrackMode.GetCurSel() == 1)  //manual
	{
		m_struTracking.byEnable = 1;
		m_struTracking.byMode = 1;

// 		m_struTracking.struRegion.dwPointNum = 4;
// 		m_struTracking.struRegion.struPos[0].fX = 0.231;
// 		m_struTracking.struRegion.struPos[0].fX = 0.231;
// 
// 		m_struTracking.struRegion.struPos[1].fX = 0.231;
// 		m_struTracking.struRegion.struPos[1].fX = 0.231;
// 
// 		m_struTracking.struRegion.struPos[2].fX = 0.231;
// 		m_struTracking.struRegion.struPos[2].fX = 0.231;
// 		
// 		m_struTracking.struRegion.struPos[3].fX = 0.231;
// 		m_struTracking.struRegion.struPos[3].fX = 0.231;
	}
	else if (m_comboTrackMode.GetCurSel() == 2)  //auto
	{
		m_struTracking.byEnable = 1;
		m_struTracking.byMode = 2;
	}
		
	m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel()+1;
	m_struSlaveCameraCond.dwChannel = m_lChannel;
	m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);
	
	m_struTracking.dwSize = sizeof(m_struTracking);
	m_struTracking.wTrackingTime = m_iTrackingTime;
	
    NET_DVR_STD_CONFIG struCfg = {0};
	
    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpInBuffer = &m_struTracking;
    struCfg.dwInSize = sizeof(m_struTracking);
	
    memset(m_szStatusBuf, 0, 1024);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = 1024;
	
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_TRACKING, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACKING");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACKING");
    }
}

DWORD HexToDecMa(DWORD wHex)
{
    return (wHex / 4096) * 1000 + ((wHex % 4096) / 256) * 100 + ((wHex % 256) / 16) * 10 + (wHex % 16);
}

void CDlgMasterSlaveTracking::OnBtnCalib() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    int nItem = m_comboSlaveCameraID.GetCurSel();
	CString strTemp;
     
    NET_DVR_PTZPOS m_ptzPos = {0};
    DWORD dwReturned;

    m_struSlaveCameraCalibCfg.struCalibParam[nItem].iHorValue = m_iHorValue;
    m_struSlaveCameraCalibCfg.struCalibParam[nItem].iVerValue = m_iVerValue;

    BOOL bRet = NET_DVR_GetDVRConfig(m_lUserID[m_struSlaveCameraCond.byID], NET_DVR_GET_PTZPOS, m_comboChannel.GetCurSel(), &m_ptzPos, sizeof(NET_DVR_PTZPOS), &dwReturned);

    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS");
        return;
	}

    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZPOS");
    int m_iPara1 = HexToDecMa(m_ptzPos.wPanPos);
    int m_iPara2 = HexToDecMa(m_ptzPos.wTiltPos);
	int m_iPara3 = HexToDecMa(m_ptzPos.wZoomPos);

	nItem = m_lstCalib.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
	strTemp.Format("(%.3f,%.3f)", m_struSlaveCameraCalibCfg.struCalibParam[nItem].struCalibCoordinates.fX, \
		m_struSlaveCameraCalibCfg.struCalibParam[nItem].struCalibCoordinates.fY);
		m_lstCalib.SetItemText(nItem, 1, strTemp);

    float fP = (float)((float)m_iPara1/10);
    float fT = (float)((float)m_iPara2/10);
    float fZ = (float)((float)m_iPara3/10);

    strTemp.Format("(%.1f,%.1f,%.1f)", fP, fT, fZ);
	m_lstCalib.SetItemText(nItem, 2, strTemp);  

    m_struSlaveCameraCalibCfg.struCalibParam[nItem].struPtzInfo.fPan = fP;
    m_struSlaveCameraCalibCfg.struCalibParam[nItem].struPtzInfo.fTilt = fT;
    m_struSlaveCameraCalibCfg.struCalibParam[nItem].struPtzInfo.fZoom = fZ;

    m_struSlaveCameraCalibCfg.struCalibParam[nItem].iHorValue = m_iHorValue;
    m_struSlaveCameraCalibCfg.struCalibParam[nItem].iVerValue = m_iVerValue;
}

void CDlgMasterSlaveTracking::OnBtnCalibDel() 
{
	// TODO: Add your control notification handler code here
	int nItem = 0;
	CString strTemp;
	while(m_lstCalib.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		nItem = m_lstCalib.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_lstCalib.DeleteItem(nItem);
		
		strTemp.Format("%02d", nItem+1);
		m_lstCalib.InsertItem(nItem, strTemp);
	}
	
	memset(&m_struSlaveCameraCalibCfg.struCalibParam[nItem], 0, sizeof(NET_DVR_CALIB_PARAM));
}


void CDlgMasterSlaveTracking::OnSelchangeComboTrackmode() 
{
	// TODO: Add your control notification handler code here
	//memcpy(&m_struRegionTemp, &m_struTracking.struRegion, sizeof(NET_VCA_POLYGON));
	if(m_comboTrackMode.GetCurSel() != 1)
	{
		memset(&m_struTracking.struRegion, 0, sizeof(NET_VCA_POLYGON));
	}
	else
	{
		memcpy(&m_struTracking.struRegion, &m_struRegionTemp, sizeof(NET_VCA_POLYGON));
	}
}

void CDlgMasterSlaveTracking::OnBtnControlPtzManualtrace() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_PTZ_MANUALTRACE struTrack = {0};
    struTrack.dwSize = sizeof(NET_DVR_PTZ_MANUALTRACE);
    struTrack.byTrackType = 2;
    struTrack.dwSerialNo = 0;
    SYSTEMTIME t;
    GetLocalTime(&t);
    
    struTrack.struTime.wYear = t.wYear;
    struTrack.struTime.byMonth = t.wMonth;
    struTrack.struTime.byDay = t.wDay;
    struTrack.struTime.byHour = t.wHour;
    struTrack.struTime.byMinute = t.wMinute;
    struTrack.struTime.bySecond = t.wSecond;
    struTrack.struTime.wMilliSec = t.wMilliseconds;
    
    struTrack.struPoint.fX = m_struTrackPoint.fX;
    struTrack.struPoint.fY = m_struTrackPoint.fY;
    
    //struTrack.struPointEnd.fX = m_struTracking.struRegion.struPos[2].fX;
    //struTrack.struPointEnd.fY = m_struTracking.struRegion.struPos[2].fY;
    struTrack.dwChannel = m_lChannel;
    DWORD iRet = 0;
    if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_CONTROL_PTZ_MANUALTRACE, &struTrack, sizeof(struTrack)))
    {
        g_pMainDlg->AddLog(m_lLoginID, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_CONTROL_PTZ_MANUALTRACE");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_lLoginID, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_CONTROL_PTZ_MANUALTRACE");
	}
}

void CDlgMasterSlaveTracking::OnButtonPtzAdjust()
{
    // TODO: Add your control notification handler code here
    NET_DVR_PTZPOS m_ptzInitialPos = { 0 };
    NET_DVR_PTZPOS m_ptzAdjustPos = { 0 };
    DWORD dwReturned = 0;
    int index = m_comboSlaveCameraID.GetCurSel() + 1;
    BOOL bRet = FALSE;
    bRet = NET_DVR_GetDVRConfig(m_lUserID[index], NET_DVR_GET_PTZPOS, m_lChannel, &m_ptzInitialPos, sizeof(NET_DVR_PTZPOS), &dwReturned);
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS");
        return;
    }

    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZPOS");
    int m_iPara1 = HexToDecMa(m_ptzInitialPos.wPanPos);
    int m_iPara2 = HexToDecMa(m_ptzInitialPos.wTiltPos);
    int m_iPara3 = HexToDecMa(m_ptzInitialPos.wZoomPos);


    m_fInitialP = (float)((float)m_iPara1 / 10);
    m_fInitialT = (float)((float)m_iPara2 / 10);
    m_fInitialZ = (float)((float)m_iPara3 / 10);


    m_struBvCalibPosotion.struInitialPos.fPan = m_fInitialP;
    m_struBvCalibPosotion.struInitialPos.fTilt = m_fInitialT;
    m_struBvCalibPosotion.struInitialPos.fZoom = m_fInitialZ;

    CDlgPtzCtrl dlg;
    dlg.m_lPlayHandle = m_lPlayHandle[index];
    dlg.DoModal();

    bRet = NET_DVR_GetDVRConfig(m_lUserID[index], NET_DVR_GET_PTZPOS, m_lChannel, &m_ptzAdjustPos, sizeof(NET_DVR_PTZPOS), &dwReturned);
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS");
        return;
    }

    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZPOS");
    m_iPara1 = HexToDecMa(m_ptzAdjustPos.wPanPos);
    m_iPara2 = HexToDecMa(m_ptzAdjustPos.wTiltPos);
    m_iPara3 = HexToDecMa(m_ptzAdjustPos.wZoomPos);


    m_fAdjustP = (float)((float)m_iPara1 / 10);
    m_fAdjustT = (float)((float)m_iPara2 / 10);
    m_fAdjustZ = (float)((float)m_iPara3 / 10);


    m_struBvCalibPosotion.struAdjustPos.fPan = m_fAdjustP;
    m_struBvCalibPosotion.struAdjustPos.fTilt = m_fAdjustT;
    m_struBvCalibPosotion.struAdjustPos.fZoom = m_fAdjustZ;

    UpdateData(FALSE);
}

void CDlgMasterSlaveTracking::OnBUTTONAdjustPTZ()
{
    // TODO: Add your control notification handler code here
    char szStatusBuf[ISAPI_STATUS_LEN];
    NET_DVR_STD_CONFIG struStdConfig = { 0 };
    m_struBvCalibPosotion.dwSize = sizeof(m_struBvCalibPosotion);
    struStdConfig.lpCondBuffer = &m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpInBuffer = &m_struBvCalibPosotion;
    struStdConfig.dwInSize = sizeof(m_struBvCalibPosotion);
    struStdConfig.lpOutBuffer = NULL;
    struStdConfig.dwOutSize = 0;
    memset(szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdConfig.lpStatusBuffer = szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_ADJUST_BV_CALIB, &struStdConfig))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ADJUST_BV_CALIB");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ADJUST_BV_CALIB");
    }

    UpdateData(FALSE);
}

void CDlgMasterSlaveTracking::OnButtonGetHumanCalib()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szStatusBuf[ISAPI_STATUS_LEN];

    NET_DVR_HUMAN_CALIB_CFG struHumanCalib = { 0 };

    m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel() + 1;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);

    NET_DVR_STD_CONFIG struCfg = { 0 };

    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);

    struHumanCalib.dwSize = sizeof(struHumanCalib);

    struCfg.lpOutBuffer = &struHumanCalib;
    struCfg.dwOutSize = sizeof(struHumanCalib);
    memset(szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_HUMAN_CALIB, &struCfg))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_HUMAN_CALIB");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_HUMAN_CALIB");
    }

    m_fLeftposX = struHumanCalib.struLeftPos.fX;
    m_fLeftposY = struHumanCalib.struLeftPos.fY;
    m_fRightposX = struHumanCalib.struRightPos.fX;
    m_fRightposY = struHumanCalib.struRightPos.fY;

    UpdateData(FALSE);
}

void CDlgMasterSlaveTracking::OnButtonSetHumanCalib()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szStatusBuf[ISAPI_STATUS_LEN];

    NET_DVR_HUMAN_CALIB_CFG struHumanCalib = { 0 };

    m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel() + 1;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);


    NET_DVR_STD_CONFIG struCfg = { 0 };

    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);

    struHumanCalib.dwSize = sizeof(struHumanCalib);
    struHumanCalib.struLeftPos.fX = m_fLeftposX;
    struHumanCalib.struLeftPos.fY = m_fLeftposY;
    struHumanCalib.struRightPos.fX = m_fRightposX;
    struHumanCalib.struRightPos.fY = m_fRightposY;

    struCfg.lpInBuffer = &struHumanCalib;
    struCfg.dwInSize = sizeof(struHumanCalib);
    struCfg.lpOutBuffer = NULL;
    struCfg.dwOutSize = 0;
    memset(szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_HUMAN_CALIB, &struCfg))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_HUMAN_CALIB");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_HUMAN_CALIB");
    }

    UpdateData(FALSE);
}

void CDlgMasterSlaveTracking::OnBtnTackInitposition() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    m_struTrackInitPostion.byID = m_comboSlaveCameraID.GetCurSel()+1;
    m_struTrackInitPostion.dwChannel = m_lChannel;
    m_struTrackInitPostion.dwSize = sizeof(m_struTrackInitPostion);
    
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &m_struTrackInitPostion;
    struControl.dwCondSize = sizeof(m_struTrackInitPostion);
    
    memset(m_szStatusBuf, 0, 1024);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = 1024;
    
    if (!NET_DVR_STDControl(m_lLoginID, NET_DVR_SET_TRACK_INITPOSTION, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACK_INITPOSTION");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACK_INITPOSTION");
    }   	
}

void CDlgMasterSlaveTracking::OnSetTrackratio() 
{
	// TODO: Add your control notification handler code here
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel()+1;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);
    
    m_struManualTrackRatio.dwSize = sizeof(m_struManualTrackRatio);
    m_struManualTrackRatio.byCoefficient = m_iCoefficient;
    
    NET_DVR_STD_CONFIG struCfg = {0};
    
    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpInBuffer = &m_struManualTrackRatio;
    struCfg.dwInSize = sizeof(m_struManualTrackRatio);
    
    memset(m_szStatusBuf, 0, 1024);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = 1024;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_TRACKINGRATIO_MANUAL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACKINGRATIO_MANUAL");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACKINGRATIO_MANUAL");
    }	
}

void CDlgMasterSlaveTracking::OnBtnGetTrackratio() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = {0};
    // 
    m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel()+1;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);
    // 
    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpOutBuffer = &m_struManualTrackRatio;
    struCfg.dwOutSize = sizeof(m_struManualTrackRatio);
    // 
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    //     
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_TRACKINGRATIO_MANUAL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRACKINGRATIO_MANUAL");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRACKINGRATIO_MANUAL");        
    }
    
    m_iCoefficient = m_struManualTrackRatio.byCoefficient;

    UpdateData(FALSE);
}
