// DlgFishEyePtzControl.cpp : implementation file
//

#include "stdafx.h"
#include "DlgFishEyePtzControl.h"
#include "ClientDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
void CALLBACK fFishEyeRemoteCfgCallback(DWORD dwType, void *lpBuffer, DWORD dwBufLen, void *pUserData);
void CALLBACK g_DrawFisheyevFun(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
	CDlgFishEyePtzControl* pDlg = (CDlgFishEyePtzControl*)(dwUser);
	pDlg->DrawTrackDevFun(hDc);
}
/////////////////////////////////////////////////////////////////////////////
// CDlgFishEyePtzControl dialog


CDlgFishEyePtzControl::CDlgFishEyePtzControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFishEyePtzControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFishEyePtzControl)
	m_fPtzX = 0.0f;
	m_fPtzY = 0.0f;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_lChannel = -1;
	m_iDevIndex = -1;
	m_lFishEyeCfgHandle = -1;
	m_bDragFishEyePTZ = FALSE;
	m_dwPtzChannel = 0;
	m_lRealHandle = -1;
	m_byCurChannelStreamStatus = 0;

	m_penRed.CreatePen(PS_SOLID,1,RGB(255,0,0));
}


void CDlgFishEyePtzControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFishEyePtzControl)
	DDX_Control(pDX, IDC_COMBO_PTZ_CHANNEL, m_comboPtzChannel);
	DDX_Control(pDX, IDC_LIST_CALLBACK_DATA, m_listCallbackData);
	DDX_Text(pDX, IDC_EDIT_PTZ_X, m_fPtzX);
	DDX_Text(pDX, IDC_EDIT_PTZ_Y, m_fPtzY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFishEyePtzControl, CDialog)
	//{{AFX_MSG_MAP(CDlgFishEyePtzControl)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_CREATE_LONGLINK, OnBtnCreateLonglink)
	ON_BN_CLICKED(IDC_BTN_CLOSE_LONGLINK, OnBtnCloseLonglink)
	ON_BN_CLICKED(IDC_BTN_GET_PTZ_POINT, OnBtnGetPtzPoint)
	ON_BN_CLICKED(IDC_BTN_SET_PTZ_POINT, OnBtnSetPtzPoint)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_CBN_SELCHANGE(IDC_COMBO_PTZ_CHANNEL, OnSelchangeComboPtzChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFishEyePtzControl message handlers

BOOL CDlgFishEyePtzControl::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitCtrlState();

	m_dlgPtzPlayWnd.Create(CDlgFisheyePtzPlayWnd::IDD,this);
    m_dlgPtzPlayWnd.m_lServerID = m_lServerID;
	m_dlgPtzPlayWnd.m_lChannel = m_lChannel;
	m_dlgPtzPlayWnd.m_iDevIndex = m_iDevIndex;
   
	StartRealPlay();
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);

	return TRUE;
}

void CDlgFishEyePtzControl::OnDestroy()
{   
	StopRealPlay();
	OnBtnCloseLonglink();
	CDialog::OnDestroy();
}

void CDlgFishEyePtzControl::OnMouseMove(UINT nFlags, CPoint point)
{   
	CDialog::OnMouseMove(nFlags,point);
	
	if (!m_rcPlayWnd.PtInRect(point))
	{   
		m_bDragFishEyePTZ = FALSE;
        PostMessage(WM_SETCURSOR,0,0);
		return;
	}
	PostMessage(WM_SETCURSOR,0,0);
	SendDragPtzPos(point);
}

void CDlgFishEyePtzControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags,point);
	
	if (!m_rcPlayWnd.PtInRect(point))
	{   
		return;
	}
    
	if (m_byCurChannelStreamStatus == FISHEYE_STREAM_MODE_FISHEYE &&
		m_lFishEyeCfgHandle != -1)
	{   
		if (!m_dlgPtzPlayWnd.IsWindowVisible())
		{
			m_dlgPtzPlayWnd.ShowWindow(SW_SHOW);
		}
		 m_dlgPtzPlayWnd.SwitchChannel(m_dwPtzChannel);
	}

	if (m_lFishEyeCfgHandle != -1)
	{   
		m_bDragFishEyePTZ = TRUE;
		m_ptOriDrag = point;
		PostMessage(WM_SETCURSOR,0,0);
	}
}

void CDlgFishEyePtzControl::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags,point);
	m_bDragFishEyePTZ = FALSE;
	PostMessage(WM_SETCURSOR,0,0);
}

BOOL CDlgFishEyePtzControl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_bDragFishEyePTZ)
	{
		SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(32649)));
		return TRUE;
	}
	else
	{
		SetCursor(LoadCursor(NULL,IDC_ARROW));
	}
	return CDialog::OnSetCursor(pWnd,nHitTest,message);
}

void CDlgFishEyePtzControl::OnBtnCreateLonglink() 
{
	m_lFishEyeCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_FISHEYE_CFG,NULL,0,fFishEyeRemoteCfgCallback,this);
	if (m_lFishEyeCfgHandle == -1)
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig NET_DVR_FISHEYE_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig NET_DVR_FISHEYE_CFG");
		GetDlgItem(IDC_BTN_CREATE_LONGLINK)->EnableWindow(FALSE);
	}
	
}

void CDlgFishEyePtzControl::OnBtnCloseLonglink() 
{
	if (m_lFishEyeCfgHandle == -1)
	{
		return;
	}
	
	if (!NET_DVR_StopRemoteConfig(m_lFishEyeCfgHandle))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig NET_DVR_FISHEYE_CFG");
	}
	else
	{  
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig NET_DVR_FISHEYE_CFG");
		GetDlgItem(IDC_BTN_CREATE_LONGLINK)->EnableWindow(TRUE);
	}
	m_lFishEyeCfgHandle = -1;
	
}

void CDlgFishEyePtzControl::OnBtnGetPtzPoint() 
{
	NET_VCA_POINT struPtzPoint = {0};
	DWORD dwReturn = 0;
	
	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_PTZ_POINT,m_lChannel,&struPtzPoint,sizeof(struPtzPoint),&dwReturn))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_GET_PTZ_POINT");
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_GET_PTZ_POINT");
	}
	
	m_fPtzX= struPtzPoint.fX;
	m_fPtzY = struPtzPoint.fY;
	UpdateData(FALSE);
	
}

void CDlgFishEyePtzControl::OnBtnSetPtzPoint() 
{
	UpdateData(TRUE);
	
	NET_VCA_POINT struPtzPoint = {0};
	struPtzPoint.fX  = m_fPtzX;
	struPtzPoint.fY  = m_fPtzY;
	
	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_PTZ_POINT,m_lChannel,&struPtzPoint,sizeof(struPtzPoint)))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_SET_PTZ_POINT");
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_SET_PTZ_POINT");
	}
}


void CDlgFishEyePtzControl::SendDragPtzPos(CPoint pt)
{   
	if (!m_bDragFishEyePTZ    || 
		!m_rcPlayWnd.PtInRect(pt) || 
		m_lFishEyeCfgHandle == -1)
	{
		return;
	}
    
	static DWORD s_LastSendTime = 0;
	
	DWORD dwCurSendTime = GetTickCount();
    DWORD dwInterval    = dwCurSendTime - s_LastSendTime;
	if (dwInterval < 60)
	{
		return;
	}
	
	
	NET_VCA_POINT ptTargetPtz;
	ptTargetPtz.fX = (float)(pt.x- m_rcPlayWnd.left)/ (float)m_rcPlayWnd.Width();
	ptTargetPtz.fY = (float)(pt.y- m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
	
	NET_VCA_POINT ptOriPtz;
    ptOriPtz.fX = (float)(m_ptOriDrag.x- m_rcPlayWnd.left)/ (float)m_rcPlayWnd.Width();
	ptOriPtz.fY = (float)(m_ptOriDrag.y- m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
	
	
	NET_DVR_DRAG_POS_PARAM     struDragPtzParam;
	struDragPtzParam.dwChannel    = m_lChannel;
	struDragPtzParam.dwPtzChannel = m_dwPtzChannel; // Only effecvice under fisheye mode
	struDragPtzParam.struToPoint  = ptTargetPtz;
	struDragPtzParam.struOriPoint = ptOriPtz;
	
	if (!NET_DVR_SendRemoteConfig(m_lFishEyeCfgHandle,DRAG_PTZ,(char*)&struDragPtzParam,sizeof(struDragPtzParam)))
	{
		//g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig DRAG_PTZ");
	}
	else
	{
		//g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_SendRemoteConfig DRAG_PTZ");
	}
	
	s_LastSendTime = GetTickCount();
}

void CDlgFishEyePtzControl::AddFishEyeCallbackData(CString strData)
{   
	int nItemCount = m_listCallbackData.GetCount();
	if (nItemCount > 100)
	{
		m_listCallbackData.DeleteString(nItemCount - 1);
	}
	m_listCallbackData.InsertString(0,strData);
}


BOOL CDlgFishEyePtzControl::StartRealPlay()
{
	NET_DVR_CLIENTINFO struPlay;
	struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
	struPlay.lChannel 	= m_lChannel; 
	struPlay.lLinkMode 	= 0;
	struPlay.sMultiCastIP = "";	
	m_lRealHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE); 
	BOOL bRet = FALSE;
	if (m_lRealHandle < 0)
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
		AfxMessageBox("NET_DVR_RealPlay_V30 failed");		
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
		bRet = NET_DVR_RigisterDrawFun(m_lRealHandle, g_DrawFisheyevFun, (DWORD)this);//DC Draw callback
	}
	return bRet;
}

BOOL CDlgFishEyePtzControl::StopRealPlay()
{
	BOOL bRet = FALSE;
    if (!NET_DVR_StopRealPlay(m_lRealHandle))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRealPlay");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRealPlay");
		m_lRealHandle = -1;
        bRet = TRUE;
    }

    return bRet;
}

void CDlgFishEyePtzControl::DrawTrackDevFun(HDC hdc)
{
	CPoint pt;
	GetCursorPos(&pt);
	CPoint ptTemp = pt;
	ScreenToClient(&ptTemp);
	if (m_rcPlayWnd.PtInRect(ptTemp))
	{   
		GetDlgItem(IDC_PLAYWND)->ScreenToClient(&pt);
		SelectObject(hdc,GetStockObject(NULL_BRUSH));
		SelectObject(hdc,m_penRed);
		//Ellipse(hdc,pt.x - 10, pt.y - 10, pt.x + 10, pt.y + 10);
		MoveToEx(hdc,pt.x,       pt.y - 10,   NULL);
		LineTo(hdc,  pt.x,       pt.y + 10);
		MoveToEx(hdc,pt.x - 10,  pt.y ,       NULL);
	    LineTo(hdc,  pt.x + 10,  pt.y);
	}
}

void CALLBACK fFishEyeRemoteCfgCallback(DWORD dwType, void *lpBuffer, DWORD dwBufLen, void *pUserData)
{  
	CDlgFishEyePtzControl* pDlg = (CDlgFishEyePtzControl*)pUserData;
	if (pDlg == NULL)
	{
		return;
	}
    
	CString strItem = "";
	
	switch (dwType)
	{
	case NET_SDK_CALLBACK_TYPE_STATUS:
		{
			if (lpBuffer != NULL)
			{
				DWORD dwStatus = *(DWORD*)lpBuffer;
				if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
				{
					
					strItem = "Fisheye remote config link maybe closed";
					pDlg->AddFishEyeCallbackData(strItem);
				}
			}
		}
		break;
	case NET_SDK_CALLBACK_TYPE_DATA:
		{
			if (lpBuffer != NULL)
			{
				NET_DVR_CALLBACK_TYPE_DATA* pCallbackData = (NET_DVR_CALLBACK_TYPE_DATA*)lpBuffer;
				if (pCallbackData->dwDataType == ENUM_FISHEYE_STREAM_STATUS)
				{   
					NET_DVR_FISHEYE_STREAM_STATUS* pStreamStatus = (NET_DVR_FISHEYE_STREAM_STATUS*)pCallbackData->pData;
					DWORD dwStreamMode = pStreamStatus->byStreamMode;
					DWORD dwChannel    = pCallbackData->dwChannel;
					
					CString strStatus = "Unknown";
					if (dwStreamMode == FISHEYE_STREAM_MODE_FISHEYE)
					{
						strStatus = "FishEye";
					}
					else if (dwStreamMode == FISHEYE_STREAM_MODE_PANORAMA)
					{
						strStatus = "PANORAMA";
					}
					else if (dwStreamMode == FISHEYE_STREAM_MODE_PTZ)
					{
						strStatus = "PTZ";
					}
					strItem.Format("Channel[%d] stream mode: %s",pCallbackData->dwChannel,strStatus);
					pDlg->AddFishEyeCallbackData(strItem);
				}
				else if (pCallbackData->dwDataType == ENUM_FISHEYE_PTZPOS)
				{   
					NET_VCA_POINT* pPoint = (NET_VCA_POINT*)pCallbackData->pData;
					strItem.Format("Channel[%d] ptz pos: [%.3f,%.3f]",pCallbackData->dwChannel,pPoint->fX,pPoint->fY);
					pDlg->AddFishEyeCallbackData(strItem);
				}
				else if (pCallbackData->dwDataType == ENUM_FISHEYE_REALTIME_OUTPUT)
				{
					DWORD dwOutputMode = *(DWORD*)pCallbackData->pData;
					strItem.Format("Channel[%d] realtime output: %s",pCallbackData->dwChannel,dwOutputMode == 0 ? "off" : "on");
					pDlg->AddFishEyeCallbackData(strItem);
				}
			}
		}
		break;
	default:
		break;
	}
}

void CDlgFishEyePtzControl::OnSelchangeComboPtzChannel() 
{
	int nCurSel = m_comboPtzChannel.GetCurSel();

	if (nCurSel != CB_ERR)
	{
		m_dwPtzChannel = m_comboPtzChannel.GetItemData(nCurSel);

		m_dlgPtzPlayWnd.SwitchChannel(m_dwPtzChannel);
	}
}


void CDlgFishEyePtzControl::InitCtrlState()
{   
	GetChannelStreamStatus(m_lChannel,m_byCurChannelStreamStatus);

	if (m_byCurChannelStreamStatus == FISHEYE_STREAM_MODE_FISHEYE)
	{
		CString strChannel = "";
		int nIndex = 0;
		for (int i = 1; i <= 5; i++)
		{   
			BYTE byStreamStatus = 0;
			if (GetChannelStreamStatus(i,byStreamStatus))
			{   
				if (byStreamStatus !=  FISHEYE_STREAM_MODE_PTZ)
				{
					continue;
				}
				strChannel.Format("%d",i);
				m_comboPtzChannel.InsertString(nIndex,strChannel);
				m_comboPtzChannel.SetItemData(nIndex,i);
				nIndex++;
			}
		}
		
		if (m_comboPtzChannel.GetCount() > 0)
		{
			m_comboPtzChannel.SetCurSel(0);
			m_dwPtzChannel = m_comboPtzChannel.GetItemData(0);
		}
	}
	else
	{
		m_comboPtzChannel.EnableWindow(FALSE);
		m_dwPtzChannel = 0;
	}
}

BOOL CDlgFishEyePtzControl::GetChannelStreamStatus(LONG lChannel,BYTE& byStreamStatus)
{   
	byStreamStatus = 0;

	NET_DVR_FISHEYE_STREAM_STATUS struStreamStatus = {0};
	struStreamStatus.dwSize = sizeof(struStreamStatus);
	
	DWORD dwStatus = 0;
	BOOL  bResult  = FALSE;
	
	if (!NET_DVR_GetDeviceStatus(m_lServerID,NET_DVR_GET_FISHEYE_STREAM_STATUS,1,&lChannel,sizeof(lChannel),
		&dwStatus,&struStreamStatus,sizeof(struStreamStatus)))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_GetDeviceStatus NET_DVR_GET_FISHEYE_STREAM_STATUS");
	}
	else
	{   
		bResult = TRUE;
		//g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_GetDeviceStatus NET_DVR_GET_FISHEYE_STREAM_STATUS");
	}
	
	if (bResult)
	{   
		byStreamStatus = struStreamStatus.byStreamMode;
	}

	return bResult;
}