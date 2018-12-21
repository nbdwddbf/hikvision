// DlgVcaLF.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaLF.h"
#include "DlgOutputCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaLF dialog
extern BOOL PTZControlAll(LONG lRealHandle, int iDevIndex, int iChanIndex, DWORD dwPTZCommand, DWORD dwPresetIndex, char *szCmdString);

CDlgVcaLF::CDlgVcaLF(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaLF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaLF)
	m_fCurVcaPointX = 0.0f;
	m_fCurVcaPointY = 0.0f;
	m_bLFEnable = FALSE;
	m_iFollowChan = 2;
	m_iMainChan = 1;
	//}}AFX_DATA_INIT
// 	m_lPlayHandle1 = -1;
	m_lPlayHandle2 = -1;
	
	memset(&m_rect1, 0, sizeof(CRect));
	memset(&m_rect2, 0, sizeof(CRect));
	
	memset(&m_struLFTrackMode, 0, sizeof(NET_DVR_TRACK_MODE));
	memset(&m_struLFCfg, 0, sizeof(NET_DVR_TRACK_CFG ));
	memset(&m_struCurCBPPoint, 0, sizeof(NET_DVR_CB_POINT));
    memset(&m_struPUStream, 0, sizeof(m_struPUStream));
    m_lPUMainServerID = -1;
    m_lPUSubServerID = 1;
}


void CDlgVcaLF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaLF)
	DDX_Control(pDX, IDC_COMBO_CAL_POINT_NUM, m_comboCalPointNum);
	DDX_Control(pDX, IDC_COMBO_POINT_INDEX, m_comboPointIndex);
	DDX_Text(pDX, IDC_EDIT_CUR_VCA_POINT_X, m_fCurVcaPointX);
	DDX_Text(pDX, IDC_EDIT_CUR_VCA_POINT_Y, m_fCurVcaPointY);
	DDX_Check(pDX, IDC_CHECK_LF_ENABLE, m_bLFEnable);
	DDX_Text(pDX, IDC_EDIT_FOLLOW_CHAN, m_iFollowChan);
	DDX_Text(pDX, IDC_EDIT_MAIN_CHAN, m_iMainChan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaLF, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaLF)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_CBN_SELCHANGE(IDC_COMBO_POINT_INDEX, OnSelchangeComboPointIndex)
	ON_BN_CLICKED(IDC_BTN_ADD_CAL_POINT, OnBtnAddCalPoint)
	ON_CBN_SELCHANGE(IDC_COMBO_CAL_POINT_NUM, OnSelchangeComboCalPointNum)
	ON_BN_CLICKED(IDC_CHECK_LF_ENABLE, OnCheckLfEnable)
	ON_BN_CLICKED(IDC_RADIO_MANUAL_CTRL, OnRadioManualCtrl)
	ON_BN_CLICKED(IDC_RADIO_ALARM_TRACK, OnRadioAlarmTrack)
	ON_BN_CLICKED(IDC_RADIO_TARGET_TRACK, OnRadioTargetTrack)
	ON_BN_CLICKED(IDC_BTN_LF_CFG, OnBtnLfCfg)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBtnPreview)
	ON_BN_CLICKED(IDC_BTN_PREVIEW2, OnBtnPreview2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaLF message handlers

BOOL CDlgVcaLF::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	GetDlgItem(IDC_PLAYWND1)->GetWindowRect(&m_rect1);
	ScreenToClient(&m_rect1);
	GetDlgItem(IDC_PLAYWND2)->GetWindowRect(&m_rect2);
	ScreenToClient(&m_rect2); 

	TRACE("m_rect1[%d][%d][%d][%d]\n", m_rect1.left,m_rect1.top,m_rect1.right,m_rect1.bottom);
	TRACE("m_rect2[%d][%d][%d][%d] \n", m_rect2.left,m_rect2.top,m_rect2.right,m_rect2.bottom);
	m_btnPtzUp.SubclassDlgItem(IDC_BTN_PTZ_UP,this);
	m_btnPtzDown.SubclassDlgItem(IDC_BTN_PTZ_DOWN,this);
	m_btnPtzLeft.SubclassDlgItem(IDC_BTN_PTZ_LEFT,this);
	m_btnPtzRight.SubclassDlgItem(IDC_BTN_PTZ_RIGHT,this);	
	m_btnZoomOut.SubclassDlgItem(IDC_BTN_ZOOM_OUT,this);
	m_btnZoomIn.SubclassDlgItem(IDC_BTN_ZOOM_IN,this);

	m_btnPtzUp.m_iPTZType = TILT_UP;
	m_btnPtzDown.m_iPTZType = TILT_DOWN;
	m_btnPtzLeft.m_iPTZType = PAN_LEFT;
	m_btnPtzRight.m_iPTZType = PAN_RIGHT;
	m_btnZoomOut.m_iPTZType = ZOOM_OUT;
	m_btnZoomIn.m_iPTZType = ZOOM_IN;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgVcaLF::GetLFCfg()
{
	BOOL bRet = FALSE;
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_TRACK_CFG, m_iMainChan, &m_struLFCfg, sizeof(m_struLFCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRACK_CFG %d", m_struLFCfg.byEnable);
		bRet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRACK_CFG %d num%d",m_struLFCfg.byEnable, m_struLFCfg.struCalParam.byPointNum);
		bRet = TRUE;
	}	
	return bRet;
}

BOOL CDlgVcaLF::SetLFCfg()
{
	BOOL bRet = FALSE;
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_TRACK_CFG, m_iMainChan, &m_struLFCfg, sizeof(m_struLFCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACK_CFG %d", m_struLFCfg.byEnable);
		bRet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACK_CFG %d num%d",m_struLFCfg.byEnable, m_struLFCfg.struCalParam.byPointNum);
		bRet = TRUE;
	}	
	return bRet;
}

BOOL CDlgVcaLF::GetLFTrackMode()
{
	BOOL bRet = FALSE;
	if (!NET_DVR_GetTrackMode(m_lServerID, m_iMainChan, &m_struLFTrackMode))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetTrackMode");
		bRet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetTrackMode");
		bRet = TRUE;
	}
	return bRet;
}

BOOL CDlgVcaLF::SetLfTrackMode()
{
	BOOL bRet = FALSE;

	if (!NET_DVR_SetTrackMode(m_lServerID, m_iMainChan, &m_struLFTrackMode))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetTrackMode");
		bRet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetTrackMode");
		bRet = TRUE;
	}
	return bRet;
}

BOOL CDlgVcaLF::GetPtzPos()
{
	DWORD dwReturn = 0;
	BOOL bRet = FALSE;
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PTZPOS, m_iFollowChan, &m_struCurCBPPoint.struPtzPos, sizeof(NET_DVR_PTZPOS), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS");
		bRet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZPOS %d t%d z%d", \
			m_struCurCBPPoint.struPtzPos.wPanPos, m_struCurCBPPoint.struPtzPos.wTiltPos, m_struCurCBPPoint.struPtzPos.wZoomPos);
		bRet = TRUE;
	}
	return bRet;
}

BOOL CDlgVcaLF::SetPtzPos()
{
	BOOL bRet = FALSE;
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PTZPOS, m_iFollowChan, &m_struCurCBPPoint.struPtzPos, sizeof(NET_DVR_PTZPOS) ))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PTZPOS");
		bRet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex,     OPERATION_SUCC_T, "NET_DVR_SET_PTZPOS %d t%d z%d", \
			m_struCurCBPPoint.struPtzPos.wPanPos, m_struCurCBPPoint.struPtzPos.wTiltPos, m_struCurCBPPoint.struPtzPos.wZoomPos);
		bRet = TRUE;
	}
	return bRet;
}


long CDlgVcaLF::StartPlay(int iUserID, int iChannel, HWND hPlayWnd, LONG &lServerID)
{
    if (GetPUStreamCfg(m_struPUStream, iChannel))
    {
        NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
        
        lServerID = NET_DVR_Login_V30(m_struPUStream.struDevChanInfo.struIP.sIpV4, m_struPUStream.struDevChanInfo.wDVRPort,
            (char*)m_struPUStream.struDevChanInfo.sUserName, (char*)m_struPUStream.struDevChanInfo.sPassword, &struDeviceInfo);
        if (lServerID < 0)
        {
            AfxMessageBox("Fail to login front device");
            return -1;
        }

        NET_DVR_CLIENTINFO struPlay;
        struPlay.hPlayWnd 	= hPlayWnd;
        struPlay.lChannel 	= iChannel;
        struPlay.lLinkMode 	= 0;
        struPlay.sMultiCastIP = "";	
        
        long lPlayHandle;
        lPlayHandle = NET_DVR_RealPlay_V30(lServerID, &struPlay, NULL, NULL, TRUE); 
        BOOL bRet = FALSE;
        if (lPlayHandle< 0)
        {
            g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30 ch%d", iChannel);
        }
        else
        {
            
        }
        return lPlayHandle;

    }
    else
{
	NET_DVR_CLIENTINFO struPlay;
	struPlay.hPlayWnd 	= hPlayWnd;
	struPlay.lChannel 	= iChannel;
	struPlay.lLinkMode 	= 0;
	struPlay.sMultiCastIP = "";	
	
	long lPlayHandle;
	lPlayHandle = NET_DVR_RealPlay_V30(iUserID, &struPlay, NULL, NULL, TRUE); 
	BOOL bRet = FALSE;
	if (lPlayHandle< 0)
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30 ch%d", iChannel);
	}
	else
	{

	}
	return lPlayHandle;
}
}

BOOL CDlgVcaLF::StopPlay()
{
	if(m_lPlayHandle1 >=  0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle1);
	}
	if (m_lPlayHandle2 >= 0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle2);
	}
    if (m_lPUMainServerID >= 0)
    {
        NET_DVR_Logout(m_lPUMainServerID);
    }
    if (m_lPUSubServerID >= 0)
    {
        NET_DVR_Logout(m_lPUSubServerID);
    }
	return TRUE;
}

void CDlgVcaLF::PostNcDestroy() 
{
	StopPlay();
	
	CDialog::PostNcDestroy();
}


BOOL CDlgVcaLF::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch (pMsg->message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	default:
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgVcaLF::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (MK_CONTROL & nFlags)
	{
		TRACE("POINT[%d][%d]\n",point.x,point.y );

		if (PtInRect(m_rect1, point)) // 
		{
			TRACE("PtInRect(m_rect1 POINT[%d][%d] \n",point.x, point.y);
			m_fCurVcaPointX = ((float)(point.x - m_rect1.left)/m_rect1.Width());
			m_fCurVcaPointY = ((float)(point.y - m_rect1.top)/m_rect1.Height());
			m_fCurVcaPointX = ((float)((int)(m_fCurVcaPointX*1000)))/1000;  // precision of displayed value is 0.001
			m_fCurVcaPointY = ((float)((int)(m_fCurVcaPointY*1000)))/1000;	// 

			m_struCurCBPPoint.struPoint.fX = m_fCurVcaPointX;
			m_struCurCBPPoint.struPoint.fY = m_fCurVcaPointY;

			UpdateData(FALSE);
		}
		
	}
	else
	{
		if (PtInRect(m_rect1, point))
		{
			if (m_struLFTrackMode.byTrackMode == MANUAL_CTRL)
			{
				m_struLFTrackMode.uModeParam.struManualCtrl.struCtrlPoint.fX = ((float)point.x)/m_rect1.Width();
				m_struLFTrackMode.uModeParam.struManualCtrl.struCtrlPoint.fY = ((float)point.y)/m_rect1.Height();
				SetLfTrackMode();
			}
//			else if (m_struLFTrackMode.byTrackMode == TARGET_TRACK)
//			{

// 				m_struLFTrackMode.uModeParam.struTargetTrack.dwTargetID = g_pMainDlg->m_struVcaTargetInfo.dwID;
// 				SetLfTrackMode();
//			}
		}
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgVcaLF::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (MK_CONTROL & nFlags)
	{
		TRACE("m_rect2[%d][%d][%d][%d] \n", m_rect2.left,m_rect2.top,m_rect2.right,m_rect2.bottom);
		if (PtInRect(m_rect2, point)) // 
		{
			BOOL bRet;
			TRACE("m_rect2 pt[%d][%d]\n",point.x,point.y );
			if (m_lPlayHandle2 >= 0 )
			{
				POINT tPoint=point;	
				NET_DVR_POINT_FRAME ptFrame;
				
				//divides the width and height to 255 proportion
				ptFrame.xTop = ((tPoint.x - m_rect2.left)*255)/m_rect2.Width();
				ptFrame.yTop = ((tPoint.y - m_rect2.top)*255)/m_rect2.Height();
				ptFrame.xBottom = ((tPoint.x - m_rect2.left)*255)/m_rect2.Width();
				ptFrame.yBottom = ((tPoint.y - m_rect2.top)*255)/m_rect2.Height();
				ptFrame.bCounter = 0;
				// 				
			
				if (m_lPlayHandle2 >= 0 )
				{
					bRet =  NET_DVR_PTZSelZoomIn(m_lPlayHandle2, &ptFrame);
					TRACE("POINT[%d][%d]\n",tPoint.x,tPoint.y);
					TRACE("NET_DVR_PTZSelZoomIn ptFrame xtop[%d] xbotoom[%d] ytop[%d]  ybottom[%d] bCont[%d]\n" ,
						ptFrame.xTop, ptFrame.xBottom, ptFrame.yTop, ptFrame.yBottom, ptFrame.bCounter);
				}
			}

			GetPtzPos();
		}
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgVcaLF::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgVcaLF::OnSelchangeComboPointIndex() 
{
	// TODO: Add your control notification handler code here
	int index ;
	index = m_comboPointIndex.GetCurSel();
	if (index == CB_ERR)
	{
		return;
	}
	else
	{
		memcpy(&m_struCurCBPPoint, &m_struLFCfg.struCalParam.struCBPoint[index], sizeof(NET_DVR_CB_POINT));
		
//		SetPtzPos();

		m_fCurVcaPointX = m_struCurCBPPoint.struPoint.fX;
		m_fCurVcaPointY = m_struCurCBPPoint.struPoint.fY;

		UpdateData(FALSE);
	}
}

void CDlgVcaLF::OnBtnAddCalPoint() 
{
	// TODO: Add your control notification handler code here
	AddCalPoint();
}

void CDlgVcaLF::AddCalPoint() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int iIndex = m_comboPointIndex.GetCurSel();
	if(iIndex == CB_ERR)
	{
		return;
	}
	
	GetPtzPos();
	memcpy(&m_struLFCfg.struCalParam.struCBPoint[iIndex], &m_struCurCBPPoint, sizeof(NET_DVR_CB_POINT));
	if (iIndex == 5)
	{
		m_comboPointIndex.SetCurSel(0);
		OnSelchangeComboPointIndex();
	}
	else
	{
		if (iIndex >= 3)
		{
			GetDlgItem(IDC_COMBO_CAL_POINT_NUM)->EnableWindow(TRUE);
			m_comboCalPointNum.SetCurSel(0);	
		}
		
		m_comboPointIndex.SetCurSel(iIndex+1);
		OnSelchangeComboPointIndex();
	}
}

void CDlgVcaLF::OnSelchangeComboCalPointNum() 
{
	// TODO: Add your control notification handler code here
	m_struLFCfg.struCalParam.byPointNum = (BYTE)(m_comboCalPointNum.GetCurSel() + 4);
}

void CDlgVcaLF::OnCheckLfEnable() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struLFCfg.byEnable = m_bLFEnable;
	EnableLFWnd(m_struLFCfg.byEnable);
	UpdateData(FALSE);
}

void CDlgVcaLF::EnableLFWnd(BOOL bEnable)
{
// 	GetDlgItem(IDC_COMBO_CAL_POINT_NUM)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_COMBO_POINT_INDEX)->EnableWindow(bEnable);
// 	GetDlgItem(IDC_BTN_ADD_CAL_POINT)->EnableWindow(bEnable);
}

void CDlgVcaLF::OnRadioManualCtrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struLFTrackMode.byTrackMode = MANUAL_CTRL;
	if (!SetLfTrackMode())
	{
		AfxMessageBox("Set track mode failed");
		RefreshTrackMode();
	}
	UpdateData(FALSE);
}

void CDlgVcaLF::OnRadioAlarmTrack() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struLFTrackMode.byTrackMode = ALARM_TRACK;
	if (!SetLfTrackMode())
	{
		AfxMessageBox("Set track mode failed");
		RefreshTrackMode();
	}
	UpdateData(FALSE);
}

void CDlgVcaLF::OnRadioTargetTrack() 
{
	UpdateData(FALSE);
}

BOOL CDlgVcaLF::RefreshTrackMode()
{
	if (!GetLFTrackMode())
	{
		AfxMessageBox("Get track mode failed");
		return FALSE;
	}
	
	switch(m_struLFTrackMode.byTrackMode)
	{
	case MANUAL_CTRL:
		((CButton *)GetDlgItem(IDC_RADIO_MANUAL_CTRL))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO_ALARM_TRACK))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO_TARGET_TRACK))->SetCheck(FALSE);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetTrackMode MANUAL_CTRL");
		break;
	case ALARM_TRACK:
		((CButton *)GetDlgItem(IDC_RADIO_MANUAL_CTRL))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO_ALARM_TRACK))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO_TARGET_TRACK))->SetCheck(FALSE);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetTrackMode ALARM_TRACK");
		break;
	default:
		break;
	}
	return TRUE;
}

BOOL CDlgVcaLF::RefreshLFCfg(int nIndex) // refresh the calibration
{
	if(!GetLFCfg())
	{
		AfxMessageBox("Get calibration failed");
		return FALSE;
	}
	m_bLFEnable = m_struLFCfg.byEnable;
	EnableLFWnd(m_bLFEnable);
	m_comboCalPointNum.SetCurSel(m_struLFCfg.struCalParam.byPointNum-4);

	memcpy(&m_struCurCBPPoint, &m_struLFCfg.struCalParam.struCBPoint[nIndex], sizeof(NET_DVR_CB_POINT));
	
	m_fCurVcaPointX = m_struCurCBPPoint.struPoint.fX;
	m_fCurVcaPointY = m_struCurCBPPoint.struPoint.fY;
	
    m_iFollowChan = m_struLFCfg.byFollowChan;

	UpdateData(FALSE);	
	return TRUE;
}

void CDlgVcaLF::OnBtnLfCfg() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struLFCfg.byFollowChan = m_iFollowChan;
	SetLFCfg();
}

void CDlgVcaLF::OnBtnPreview() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
		// do something
	if (!RefreshTrackMode())
	{
		return;
	}


	m_comboPointIndex.SetCurSel(0);
	if (!RefreshLFCfg(0))
	{
		return;
	}
	HWND hPlayWnd1 = GetDlgItem(IDC_PLAYWND1)->GetSafeHwnd();
	m_lPlayHandle1 = StartPlay(m_lServerID, m_iMainChan, hPlayWnd1, m_lPUMainServerID); 

}

void CDlgVcaLF::OnBtnPreview2() 
{
	// TODO: Add your control notifi
//	handler code here
	UpdateData(TRUE);
	
	HWND hPlayWnd2 = GetDlgItem(IDC_PLAYWND2)->GetSafeHwnd();
    m_lPlayHandle2 =StartPlay(m_lServerID, m_iFollowChan, hPlayWnd2, m_lPUSubServerID);

	m_btnPtzUp.m_lPlayHandle = m_lPlayHandle2;
	m_btnPtzDown.m_lPlayHandle = m_lPlayHandle2;
	m_btnPtzLeft.m_lPlayHandle = m_lPlayHandle2;
	m_btnPtzRight.m_lPlayHandle = m_lPlayHandle2;
	m_btnZoomOut.m_lPlayHandle = m_lPlayHandle2;
	m_btnZoomIn.m_lPlayHandle = m_lPlayHandle2;	
}

BOOL CDlgVcaLF::GetPUStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream, LONG lChannel)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG,lChannel, &struPUStream, sizeof(struPUStream), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PU_STREAMCFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PU_STREAMCFG");
        return FALSE;
    }
    
}