// DlgFisheyeTrackCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgFisheyeTrackCfg.h"
#include "DlgVcaRemoteChannel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyeTrackCfg dialog
void CALLBACK g_DrawFisheyeCalibPoint(LONG lRealHandle, HDC hDc, DWORD dwUser)
{  
	CDlgFisheyeTrackCfg* pDlg = (CDlgFisheyeTrackCfg*)(dwUser);
	if (pDlg != NULL)
	{
		pDlg->DrawFisheyeFun(hDc);
	}
}

void CALLBACK g_DrawTrackDevFun(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
	CDlgFisheyeTrackCfg* pDlg = (CDlgFisheyeTrackCfg*)(dwUser);
	pDlg->DrawTrackDevFun(hDc);
}

CDlgFisheyeTrackCfg::CDlgFisheyeTrackCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFisheyeTrackCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFisheyeTrackCfg)
	m_fFisheyePtX = 0.0f;
	m_nTrackDevPosP = 0;
	m_nTrackDevPosT = 0;
	m_nTrackDevPosZ = 0;
	m_nTrackDevHPosP = 0;
	m_nTrackDevHPosT = 0;
	m_nTrackDevHPosZ = 0;
	//}}AFX_DATA_INIT
	memset(&m_struTrackDevParam,0,sizeof(m_struTrackDevParam));
	m_nCurCBIndex = 0;
	m_bIsFisheyePlaying = FALSE;
	m_lTrackDevRealhandle = -1;
	m_lTrackDevUserID = -1;
	m_nOperationType = OP_TYPE_NONE;
	m_bDrawTrackPoint = FALSE;
}


void CDlgFisheyeTrackCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFisheyeTrackCfg)
	DDX_Control(pDX, IDC_COMBO_CALIB_PT_NO, m_comboCalibPtNO);
	DDX_Control(pDX, IDC_COMBO_TRANS_MODE, m_comboTransMode);
	DDX_Text(pDX, IDC_EDIT_FISHEYE_PT_X, m_fFisheyePtX);
	DDX_Text(pDX, IDC_EDIT_FISHEYE_PT_Y, m_fFisheyePtY);
	DDX_Text(pDX, IDC_EDIT_TRACKDEV_POS_P, m_nTrackDevPosP);
	DDX_Text(pDX, IDC_EDIT_TRACKDEV_POS_T, m_nTrackDevPosT);
	DDX_Text(pDX, IDC_EDIT_TRACKDEV_POS_Z, m_nTrackDevPosZ);
	DDX_Text(pDX, IDC_EDIT_TRACKDEV_HPOS_P, m_nTrackDevHPosP);
	DDX_Text(pDX, IDC_EDIT_TRACKDEV_HPOS_T, m_nTrackDevHPosT);
	DDX_Text(pDX, IDC_EDIT_TRACKDEV_HPOS_Z, m_nTrackDevHPosZ);
	DDX_Check(pDX, IDC_CHECK_TRACKDEV_ENABLE,m_bTrackDevEnable);
	DDX_Control(pDX,IDC_BTN_TILT_UP,        m_btnUp);
	DDX_Control(pDX,IDC_BTN_TILT_DOWN,      m_btnDown);
	DDX_Control(pDX,IDC_BTN_PAN_LEFT,       m_btnLeft);
	DDX_Control(pDX,IDC_BTN_PAN_RIGHT,      m_btnRight);
	DDX_Control(pDX,IDC_BTN_ZOOM_OUT,       m_btnZoomOut);
	DDX_Control(pDX,IDC_BTN_ZOOM_IN,        m_btnZoomIn);
	DDX_Control(pDX,IDC_BTN_FOCUS_NEAR,     m_btnFocusNear);
	DDX_Control(pDX,IDC_BTN_FOCUS_FAR,      m_btnFocusFar);
	DDX_Control(pDX,IDC_BTN_IRIS_CLOSE,     m_btnIrisClose);
	DDX_Control(pDX,IDC_BTN_IRIS_OPEN,      m_btnIrisOpen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFisheyeTrackCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgFisheyeTrackCfg)
	ON_BN_CLICKED(IDC_BTN_FISHEYE_STARTREALPLAY, OnBtnFisheyeStartrealplay)
	ON_BN_CLICKED(IDC_BTN_FISHEYE_STOPREALPLAY, OnBtnFisheyeStoprealplay)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_TRACKDEV_CFG, OnBtnTrackdevCfg)
	ON_BN_CLICKED(IDC_BTN_TRACKDEV_STARTREALPLAY, OnBtnTrackdevStartrealplay)
	ON_BN_CLICKED(IDC_BTN_TRACKDEV_STOPREALPLAY, OnBtnTrackdevStoprealplay)
	ON_CBN_SELCHANGE(IDC_COMBO_CALIB_PT_NO, OnSelchangeComboCalibPtNo)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_CALIB_PT_NUM, OnBtnCalibPtNum)
	ON_BN_CLICKED(IDC_BTN_GET_TRACKDEV_HORIZON_POS, OnBtnGetTrackdevHorizonPos)
	ON_BN_CLICKED(IDC_BTN_GET_TRACKDEV_CALIB_POS, OnBtnGetTrackdevCalibPos)
	ON_BN_CLICKED(IDC_RADIO_CALIB, OnRadioCalib)
	ON_BN_CLICKED(IDC_RADIO_TRACK, OnRadioTrack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyeTrackCfg message handlers

BOOL CDlgFisheyeTrackCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitCtrlState();
    OnBtnFisheyeStartrealplay();

	GetDlgItem(IDC_FISHEYE_PLAYWND)->GetWindowRect(&m_rcFisheyePlayWnd);
	ScreenToClient(&m_rcFisheyePlayWnd);

	GetDlgItem(IDC_TRACKDEV_PLAYWND)->GetWindowRect(&m_rcTrackDevPlayWnd);
	ScreenToClient(&m_rcTrackDevPlayWnd);

	if (!GetTrackDevParam())
	{
		char szErr[100] = "\0";
		char szCn[50] = "\0";
		char szEn[50] ="\0";
		sprintf(szCn,"获取跟踪设备参数失败，错误代码 %d",NET_DVR_GetLastError());
		sprintf(szCn,"Get track device param failed,error code %d",NET_DVR_GetLastError());
		g_StringLanType(szErr,szCn,szEn);
		AfxMessageBox(szErr);
	}

	LoadWndContent();
	OnRadioCalib();

	return TRUE;
}

void CDlgFisheyeTrackCfg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags,point);
	if (m_rcFisheyePlayWnd.PtInRect(point))
	{   
		int nXOffset = point.x - m_rcFisheyePlayWnd.left;
		int nYOffset = point.y - m_rcFisheyePlayWnd.top;
		
		float fX = float((nXOffset * 1.000)) / m_rcFisheyePlayWnd.Width();
		float fY = float((nYOffset * 1.000)) / m_rcFisheyePlayWnd.Height();

		if (m_nOperationType == OP_TYPE_CALIB)
		{
			int nCalibPtNum = GetDlgItemInt(IDC_EDIT_CALIB_PT_NUM);
			if (nCalibPtNum < 2 || nCalibPtNum > MAX_CALIB_PT)
			{
				return;
				
			}
			int nXOffset = point.x - m_rcFisheyePlayWnd.left;
			int nYOffset = point.y - m_rcFisheyePlayWnd.top;
			
			m_fFisheyePtX = fX;
			m_fFisheyePtY = fY;
			
			UpdateData(FALSE);
			
		    SaveCalibPointFromWnd(m_nCurCBIndex);
		}
		else if (m_nOperationType == OP_TYPE_TRACK)
		{   
            NET_DVR_PTZ_MANUALTRACE struPTZManualTrace = {0};
            struPTZManualTrace.dwSize = sizeof(struPTZManualTrace);
			struPTZManualTrace.struPoint.fX = fX;
			struPTZManualTrace.struPoint.fY = fY;
            struPTZManualTrace.dwChannel = m_lChannel;
			if (!NET_DVR_RemoteControl(m_lServerID,NET_DVR_CONTROL_PTZ_MANUALTRACE,&struPTZManualTrace,sizeof(struPTZManualTrace)))
			{
				CString strErr = "";
				strErr.Format(_T("Track failed,error ID = %d"),NET_DVR_GetLastError());
				AfxMessageBox(strErr);
			}
		}
	}
}

void CDlgFisheyeTrackCfg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags,point);
	if (m_rcFisheyePlayWnd.PtInRect(point))
	{
		if (m_nOperationType != OP_TYPE_TRACK)
		{
			return;
		}
		m_ptTrack = point;
		m_bDrawTrackPoint = TRUE;
	}
	else
	{
		m_bDrawTrackPoint = FALSE;
	}
}


void CDlgFisheyeTrackCfg::OnDestroy()
{
	StopRealPlay();
	LogoutTrackDev();
	CDialog::OnDestroy();
}

void CDlgFisheyeTrackCfg::OnBtnFisheyeStartrealplay() 
{
	if (!m_bIsFisheyePlaying)
	{
		m_bIsFisheyePlaying = StartRealPlay(GetDlgItem(IDC_FISHEYE_PLAYWND)->GetSafeHwnd(),g_DrawFisheyeCalibPoint,this);
	}
}

void CDlgFisheyeTrackCfg::OnBtnFisheyeStoprealplay() 
{   
	if (m_bIsFisheyePlaying)
	{
		StopRealPlay();
		m_bIsFisheyePlaying = FALSE;
		GetDlgItem(IDC_FISHEYE_PLAYWND)->Invalidate();
	}
}


void CDlgFisheyeTrackCfg::OnBtnSave() 
{   
	SaveWndContent();

	char szErr[100] = "\0";
	char szCn[50] = "\0";
	char szEn[50] ="\0";
	if (!SetTrackDevParam())
	{
	
		sprintf(szCn,"设置跟踪设备参数失败，错误代码 %d",NET_DVR_GetLastError());
		sprintf(szCn,"Set track device param failed,error code %d",NET_DVR_GetLastError());
		g_StringLanType(szErr,szCn,szEn);
		AfxMessageBox(szErr);
	}
	else
	{
		g_StringLanType(szErr,"保存跟踪设备参数成功","Set track device param successfully");
		AfxMessageBox(szErr);
	}
}


void CDlgFisheyeTrackCfg::OnBtnTrackdevCfg() 
{   
	const NET_DVR_CHANNEL& struChannel = m_struTrackDevParam.struTrackDevChan;
	CDlgVcaRemoteChannel dlg;
	dlg.SetRemoteChannelParam(struChannel.byAddress,struChannel.wDVRPort,struChannel.sUserName,struChannel.sPassword,struChannel.dwChannel);
	if (dlg.DoModal() == IDOK)
	{   
		CString strAddress = "";
		CString strUserName = "";
		CString strPwd = "";
		DWORD   dwChannel = 0;
		DWORD   wPort = 0;
		dlg.GetRemoteChannelParam(strAddress,wPort,strUserName,strPwd,dwChannel);
		strncpy((char*)m_struTrackDevParam.struTrackDevChan.byAddress,strAddress.GetBuffer(strAddress.GetLength()),MAX_DOMAIN_NAME);
		strncpy((char*)m_struTrackDevParam.struTrackDevChan.sUserName,strUserName.GetBuffer(strUserName.GetLength()),NAME_LEN);
		strncpy((char*)m_struTrackDevParam.struTrackDevChan.sPassword,strPwd.GetBuffer(strPwd.GetLength()),PASSWD_LEN);
		m_struTrackDevParam.struTrackDevChan.wDVRPort = wPort;
		m_struTrackDevParam.struTrackDevChan.dwChannel = dwChannel;

		LogoutTrackDev();
		LoginTrackDev();
		StartTrackDevRealPlay();
	}
}

void CDlgFisheyeTrackCfg::OnBtnTrackdevStartrealplay() 
{   
	LoginTrackDev();
	if (m_lTrackDevRealhandle < 0)
	{
		StartTrackDevRealPlay();
	}
	
}

void CDlgFisheyeTrackCfg::OnBtnTrackdevStoprealplay() 
{
	StopTrackDevRealPlay();
}


void CDlgFisheyeTrackCfg::OnSelchangeComboCalibPtNo() 
{
	int nCurSel = m_comboCalibPtNO.GetCurSel();
	if (nCurSel != CB_ERR)
	{   
		UpdateData(TRUE);
		SaveCalibPointFromWnd(m_nCurCBIndex);
		m_nCurCBIndex = nCurSel;
		LoadCalibPointToWnd(nCurSel);
		UpdateData(FALSE);
	}
}

void CDlgFisheyeTrackCfg::InitCtrlState()
{   
	m_btnUp.m_dwPtzCommand        =  TILT_UP;
	m_btnDown.m_dwPtzCommand      =  TILT_DOWN;
	m_btnLeft.m_dwPtzCommand      =  PAN_LEFT;
	m_btnRight.m_dwPtzCommand     =  PAN_RIGHT;
	m_btnZoomIn.m_dwPtzCommand    =  ZOOM_IN;
	m_btnZoomOut.m_dwPtzCommand   =  ZOOM_OUT;
	m_btnFocusNear.m_dwPtzCommand =  FOCUS_NEAR;
	m_btnFocusFar.m_dwPtzCommand  =  FOCUS_FAR;
	m_btnIrisOpen.m_dwPtzCommand  =  IRIS_OPEN;
	m_btnIrisClose.m_dwPtzCommand =  IRIS_CLOSE;

	m_comboTransMode.ResetContent();
	m_comboTransMode.InsertString(0,_T("Net SDK"));
	m_comboTransMode.SetItemData(0,TRANS_MODE_NETSDK);
	m_comboTransMode.InsertString(1,_T("RS485"));
	m_comboTransMode.SetItemData(1,TRANS_MODE_RS485);
	m_comboTransMode.SetCurSel(0);
}

BOOL CDlgFisheyeTrackCfg::GetTrackDevParam()
{
	DWORD dwReturn = 0;
	BOOL bResult = FALSE;
	
	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_TRACK_DEV_PARAM,m_lChannel,&m_struTrackDevParam,sizeof(m_struTrackDevParam),&dwReturn))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_GET_TRACK_DEV_PARAM");
		bResult = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_GET_TRACK_DEV_PARAM");
		bResult = TRUE;
	}

	return TRUE;
}

BOOL CDlgFisheyeTrackCfg::SetTrackDevParam()
{   
	BOOL bResult = FALSE;
	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_TRACK_DEV_PARAM,m_lChannel,&m_struTrackDevParam,sizeof(m_struTrackDevParam)))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_SET_TRACK_DEV_PARAM");
		bResult = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_SET_TRACK_DEV_PARAM");
		bResult = TRUE;
	}

	return bResult;
}

void CDlgFisheyeTrackCfg::LoadWndContent()
{   
	SetDlgItemInt(IDC_EDIT_CALIB_PT_NUM,m_struTrackDevParam.struCalParam.byPointNum);
	m_comboCalibPtNO.ResetContent();
	CString strItem = "";
	int i = 0;
	for (i = 0; i < m_struTrackDevParam.struCalParam.byPointNum && i < MAX_CALIB_PT; i++)
	{
		strItem.Format("%d",i + 1);
		m_comboCalibPtNO.InsertString(i,strItem);
		m_comboCalibPtNO.SetItemData(i,i + 1);
	}
	m_comboCalibPtNO.SetCurSel(0);

	const NET_DVR_TRACK_CALIBRATION_PARAM_V41& struTrackCalib = m_struTrackDevParam.struCalParam;
	m_nTrackDevHPosP  = HexToDec(struTrackCalib.struHorizonPtzPos.wPanPos);
	m_nTrackDevHPosT  = HexToDec(struTrackCalib.struHorizonPtzPos.wTiltPos);
	m_nTrackDevHPosZ  = HexToDec(struTrackCalib.struHorizonPtzPos.wZoomPos);

	int nCurSelCBIndex = m_comboCalibPtNO.GetCurSel();
	LoadCalibPointToWnd(nCurSelCBIndex);

	m_bTrackDevEnable = m_struTrackDevParam.byEnable;

	for (i = 0; i < m_comboTransMode.GetCount(); i++)
	{
		if (m_comboTransMode.GetItemData(i) == m_struTrackDevParam.byTransMode)
		{
			m_comboTransMode.SetCurSel(i);
			break;
		}
	}

	UpdateData(FALSE);
}

void CDlgFisheyeTrackCfg::SaveWndContent()
{   
	UpdateData(TRUE);

	NET_DVR_TRACK_CALIBRATION_PARAM_V41& struTrackCalib = m_struTrackDevParam.struCalParam;
	struTrackCalib.struHorizonPtzPos.wPanPos  = DecToHex(m_nTrackDevHPosP);
	struTrackCalib.struHorizonPtzPos.wTiltPos = DecToHex(m_nTrackDevHPosT);
	struTrackCalib.struHorizonPtzPos.wZoomPos = DecToHex(m_nTrackDevHPosZ);

    int nCurSelCBIndex = m_comboCalibPtNO.GetCurSel();
	SaveCalibPointFromWnd(nCurSelCBIndex);

	m_struTrackDevParam.byEnable = m_bTrackDevEnable;
	m_struTrackDevParam.byTransMode = m_comboTransMode.GetItemData(m_comboTransMode.GetCurSel());
}


void CDlgFisheyeTrackCfg::LoadCalibPointToWnd(int nIndex)
{
	const NET_DVR_TRACK_CALIBRATION_PARAM_V41& struTrackCalib = m_struTrackDevParam.struCalParam;
	m_fFisheyePtX = struTrackCalib.struCBPoint[nIndex].struPoint.fX;
	m_fFisheyePtY = struTrackCalib.struCBPoint[nIndex].struPoint.fY;
	
	m_nTrackDevPosP = HexToDec(struTrackCalib.struCBPoint[nIndex].struPtzPos.wPanPos);
	m_nTrackDevPosT = HexToDec(struTrackCalib.struCBPoint[nIndex].struPtzPos.wTiltPos);
	m_nTrackDevPosZ = HexToDec(struTrackCalib.struCBPoint[nIndex].struPtzPos.wZoomPos);
     
	NET_DVR_PTZPOS struPtzPos = struTrackCalib.struCBPoint[nIndex].struPtzPos;
    
	if (m_lTrackDevUserID != -1)
	{   
		struPtzPos.wAction = 1;
		NET_DVR_SetDVRConfig(m_lTrackDevUserID,NET_DVR_SET_PTZPOS,m_lChannel,&struPtzPos,sizeof(NET_DVR_PTZPOS));
	}
}


void CDlgFisheyeTrackCfg::SaveCalibPointFromWnd(int nIndex)
{   
	UpdateData(TRUE);

	NET_DVR_TRACK_CALIBRATION_PARAM_V41& struTrackCalib = m_struTrackDevParam.struCalParam;
	struTrackCalib.struCBPoint[nIndex].struPoint.fX = m_fFisheyePtX;
	struTrackCalib.struCBPoint[nIndex].struPoint.fY = m_fFisheyePtY;
	
	struTrackCalib.struCBPoint[nIndex].struPtzPos.wPanPos  = DecToHex(m_nTrackDevPosP);
	struTrackCalib.struCBPoint[nIndex].struPtzPos.wTiltPos = DecToHex(m_nTrackDevPosT);
	struTrackCalib.struCBPoint[nIndex].struPtzPos.wZoomPos = DecToHex(m_nTrackDevPosZ);
}


void CDlgFisheyeTrackCfg::LoginTrackDev()
{   
	CWaitCursor wait;
	if (m_lTrackDevUserID < 0)
	{   
		NET_DVR_DEVICEINFO_V30 struDevInfo = {0};
		const NET_DVR_CHANNEL& struChannel = m_struTrackDevParam.struTrackDevChan;
		m_lTrackDevUserID = NET_DVR_Login_V30((char*)struChannel.byAddress,struChannel.wDVRPort,(char*)struChannel.sUserName,
			(char*)struChannel.sPassword,&struDevInfo);

		if (m_lTrackDevUserID < 0)
		{
			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_Login_V30");
			AfxMessageBox("Login track device failed");
		}
	}
}

void CDlgFisheyeTrackCfg::LogoutTrackDev()
{
	if (m_lTrackDevUserID >= 0)
	{
		StopTrackDevRealPlay();
		if (!NET_DVR_Logout_V30(m_lTrackDevUserID))
		{
			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_Logout_V30");
		}
		m_lTrackDevUserID = -1;
	}
}

void CDlgFisheyeTrackCfg::StartTrackDevRealPlay()
{
	NET_DVR_CLIENTINFO struPlay;
	struPlay.hPlayWnd 	= GetDlgItem(IDC_TRACKDEV_PLAYWND)->GetSafeHwnd();
	struPlay.lChannel 	= m_struTrackDevParam.struTrackDevChan.dwChannel; 
	struPlay.lLinkMode 	= 0;
	struPlay.sMultiCastIP = "";	
	m_lTrackDevRealhandle = NET_DVR_RealPlay_V30(m_lTrackDevUserID, &struPlay, NULL,NULL, TRUE); 
	BOOL bRet = FALSE;
	if (m_lTrackDevRealhandle < 0)
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
		NET_DVR_RigisterDrawFun(m_lTrackDevRealhandle, g_DrawTrackDevFun, (DWORD)this);//DC Draw callback
	}

	CScenePTZButton::m_lPlayHandle = m_lTrackDevRealhandle;
}

void CDlgFisheyeTrackCfg::StopTrackDevRealPlay()
{   
	if (m_lTrackDevRealhandle >= 0)
	{
		if (!NET_DVR_StopRealPlay(m_lTrackDevRealhandle))
		{
			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_StopRealPlay");
		}
		m_lTrackDevRealhandle = -1;
		GetDlgItem(IDC_TRACKDEV_PLAYWND)->Invalidate();
	}
}


void CDlgFisheyeTrackCfg::DrawTrackDevFun(HDC hdc)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,255,0));
	SelectObject(hdc,pen);

	int nHCenter = m_rcTrackDevPlayWnd.Width() / 2;
	int nVCenter = m_rcTrackDevPlayWnd.Height() / 2;

	CPoint pt1(nHCenter - 15,nVCenter);
	CPoint pt2(nHCenter + 15,nVCenter);
	CPoint pt3(nHCenter,nVCenter - 15);
	CPoint pt4(nHCenter,nVCenter + 15);

	MoveToEx(hdc,pt1.x,pt1.y,NULL);
	LineTo(hdc,pt2.x,pt2.y);

	MoveToEx(hdc,pt3.x,pt3.y,NULL);
	LineTo(hdc,pt4.x,pt4.y);
}


void CDlgFisheyeTrackCfg::DrawFisheyeFun(HDC hdc)
{
	const NET_DVR_TRACK_CALIBRATION_PARAM_V41& struTrackCalib = m_struTrackDevParam.struCalParam;

	SetBkMode(hdc,TRANSPARENT);

    for (int i = 0; i < struTrackCalib.byPointNum; i++)
	{   
		if (i == m_nCurCBIndex)
		{
			SetTextColor(hdc,RGB(255,0,0));
		}
		else
		{
			SetTextColor(hdc,RGB(0,255,0));
		}
		int nLeft = struTrackCalib.struCBPoint[i].struPoint.fX * m_rcFisheyePlayWnd.Width();
		int nTop = struTrackCalib.struCBPoint[i].struPoint.fY * m_rcFisheyePlayWnd.Height();
		int nRight = nLeft + 30;
	    int nBottom = nTop + 20;
		CRect rcText(nLeft,nTop,nRight,nBottom);
		char szText[10] = "\0";
		sprintf(szText,"+[%d]",i +1);
		DrawText(hdc,szText,strlen(szText),rcText,DT_VCENTER | DT_LEFT);
	}

	if (m_nOperationType == OP_TYPE_TRACK && m_bDrawTrackPoint)
	{   
		CPoint pt;
		GetCursorPos(&pt);
		GetDlgItem(IDC_FISHEYE_PLAYWND)->ScreenToClient(&pt);
		using namespace Gdiplus;
		Graphics graphics(hdc);
		SolidBrush  brush(Color(100, 255, 0, 0));
		Rect rcEllipse(pt.x - 12, pt.y - 12, 24, 24);
		graphics.FillEllipse(&brush,rcEllipse);

	}
}

void CDlgFisheyeTrackCfg::OnBtnCalibPtNum() 
{   
	int nCalibPtNum = 0;
	nCalibPtNum = GetDlgItemInt(IDC_EDIT_CALIB_PT_NUM);

	if (nCalibPtNum < 2 || nCalibPtNum > MAX_CALIB_PT)
	{
		AfxMessageBox("Incorrect range,[2,6] is reasonable");
		return;
	}

	m_struTrackDevParam.struCalParam.byPointNum = nCalibPtNum;

	m_comboCalibPtNO.ResetContent();
	CString strItem = "";
	for (int i = 0; i < nCalibPtNum; i++)
	{
		strItem.Format("%d",i + 1);
		m_comboCalibPtNO.InsertString(i,strItem);
		m_comboCalibPtNO.SetItemData(i,i + 1);
	}
	m_comboCalibPtNO.SetCurSel(0);
}

void CDlgFisheyeTrackCfg::OnBtnGetTrackdevHorizonPos() 
{   
	LoginTrackDev();
	if (m_lTrackDevUserID < 0)
	{
		return;
	}
	NET_DVR_PTZPOS struPtzPos = {0};
	DWORD  dwReturn  = 0;
	BOOL bRst  = NET_DVR_GetDVRConfig(m_lTrackDevUserID,NET_DVR_GET_PTZPOS,1,&struPtzPos,sizeof(struPtzPos),&dwReturn);
	
	if (!bRst)
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS Chan[%d]", m_struTrackDevParam.struTrackDevChan.dwChannel);
		char szLan[32] = {0};
		g_StringLanType(szLan, "获取PTZ坐标失败", "Get PTZ pos failed!");
		AfxMessageBox(szLan);
	}
	else
	{
		m_nTrackDevHPosP  = HexToDec(struPtzPos.wPanPos);
		m_nTrackDevHPosT  = HexToDec(struPtzPos.wTiltPos);
		m_nTrackDevHPosZ  = HexToDec(struPtzPos.wZoomPos);
	    UpdateData(FALSE);
	}
}

void CDlgFisheyeTrackCfg::OnBtnGetTrackdevCalibPos() 
{
    LoginTrackDev();
	if (m_lTrackDevUserID < 0)
	{
		return;
	}

	NET_DVR_PTZPOS struPtzPos = {0};
	DWORD  dwReturn  = 0;
	BOOL bRst  = NET_DVR_GetDVRConfig(m_lTrackDevUserID,NET_DVR_GET_PTZPOS,1,&struPtzPos,sizeof(struPtzPos),&dwReturn);
	
	if (!bRst)
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS Chan[%d]", m_struTrackDevParam.struTrackDevChan.dwChannel);
		char szLan[32] = {0};
		g_StringLanType(szLan, "获取PTZ坐标失败", "Get PTZ pos failed!");
		AfxMessageBox(szLan);
	}
	else
	{
		m_nTrackDevPosP  = HexToDec(struPtzPos.wPanPos);
		m_nTrackDevPosT  = HexToDec(struPtzPos.wTiltPos);
		m_nTrackDevPosZ  = HexToDec(struPtzPos.wZoomPos);
		UpdateData(FALSE);
	}
}

void CDlgFisheyeTrackCfg::OnRadioCalib() 
{
	m_nOperationType = OP_TYPE_CALIB;
	CheckDlgButton(IDC_RADIO_CALIB,BST_CHECKED);
	CheckDlgButton(IDC_RADIO_TRACK,BST_UNCHECKED);
	EnableCalib(TRUE);
}

void CDlgFisheyeTrackCfg::OnRadioTrack() 
{
	m_nOperationType = OP_TYPE_TRACK;
	CheckDlgButton(IDC_RADIO_CALIB,BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO_TRACK,BST_CHECKED);
	EnableCalib(FALSE);
}


void CDlgFisheyeTrackCfg::EnableCalib(BOOL bEnable)
{
	GetDlgItem(IDC_BTN_GET_TRACKDEV_HORIZON_POS)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_GET_TRACKDEV_CALIB_POS)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_CALIB_PT_NUM)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_CALIB_PT_NO)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_TILT_UP)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_TILT_DOWN)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_PAN_LEFT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_PAN_RIGHT)->EnableWindow(bEnable);


	GetDlgItem(IDC_BTN_ZOOM_OUT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_ZOOM_IN)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_FOCUS_NEAR)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_FOCUS_FAR)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_IRIS_CLOSE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_IRIS_OPEN)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEnable);
}
