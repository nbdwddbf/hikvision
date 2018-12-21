// DlgIPDomeLocalCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPDomeLocalCfg.h"
#include "DlgPtzCtrl.h"
#include "DlgLimitAngle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPDomeLocalCfg dialog


CDlgIPDomeLocalCfg::CDlgIPDomeLocalCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPDomeLocalCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIPDomeLocalCfg)
	m_iAlarmDelay = 0;
	m_iTrackHold = 0;
	m_iDwellTime = 0;
	m_csPositionName = _T("");
	m_bEnablePosition = FALSE;
	m_bPreDirection = FALSE;
	m_bTrackSmooth = FALSE;
	m_iMaxTrackZoom = 0;
	m_bStopTrack = FALSE;
	m_iStopValue = 0;
	//}}AFX_DATA_INIT
    m_lServerID     = -1;;
    m_iDevIndex     = -1;
    m_iChannel      = -1;
    m_iPositionID   = 0;
    m_lPlayHandle   = -1;
    m_iTrackIPointndex = -1;
    memset(&m_struPtzPosition, 0, sizeof(m_struPtzPosition));
    memset(&m_struTrackParam, 0, sizeof(m_struTrackParam));
    memset(&m_struPatrolTrack, 0, sizeof(m_struPatrolTrack));
}


void CDlgIPDomeLocalCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPDomeLocalCfg)
	DDX_Control(pDX, IDC_COMBO_ZOOM_ADJUST, m_comboZoomAdjust);
	DDX_Control(pDX, IDC_COMBO_POSITION_ID2, m_comboPositionID2);
	DDX_Control(pDX, IDC_COMBO_TRACK_POINT, m_comboTrackPoint);
	DDX_Control(pDX, IDC_COMBO_POSITION_ID, m_comboPositionID);
	DDX_Control(pDX, IDC_COMBO_TRACK_MODE, m_comboTrackMode);
	DDX_Text(pDX, IDC_EDIT_ALARM_DELAY, m_iAlarmDelay);
	DDX_Text(pDX, IDC_EDIT_TRACK_HOLD, m_iTrackHold);
	DDX_Text(pDX, IDC_EDIT_DWELL_TIME, m_iDwellTime);
	DDX_Text(pDX, IDC_EDIT_POSITION_NAME, m_csPositionName);
	DDV_MaxChars(pDX, m_csPositionName, 32);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnablePosition);
	DDX_Check(pDX, IDC_CHK_PRE_DIRECTION, m_bPreDirection);
	DDX_Check(pDX, IDC_CHK_TRACK_SMOOTH, m_bTrackSmooth);
	DDX_Text(pDX, IDC_EDIT_MAX_TRACK_ZOOM, m_iMaxTrackZoom);
	DDX_Check(pDX, IDC_CHK_STOPTTRACK, m_bStopTrack);
	DDX_Text(pDX, IDC_EDT_STOPTRACKVALUE, m_iStopValue);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgIPDomeLocalCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgIPDomeLocalCfg)
	ON_BN_CLICKED(IDC_BTN_SET_UP, OnBtnSetUp)
	ON_BN_CLICKED(IDC_BTN_REALPLAY, OnBtnRealplay)
	ON_BN_CLICKED(IDC_BTN_PATROL_SET, OnBtnPatrolSet)
	ON_BN_CLICKED(IDC_BTN_PATROL_CONFIRM, OnBtnPatrolConfirm)
	ON_CBN_SELCHANGE(IDC_COMBO_TRACK_POINT, OnSelchangeComboTrackPoint)
	ON_BN_CLICKED(IDC_BTN_SET_POSITION, OnBtnSetPosition)
	ON_BN_CLICKED(IDC_BTN_GET_PTZ, OnBtnGetPtz)
	ON_BN_CLICKED(IDC_BTN_PTZ_CTRL, OnBtnPtzCtrl)
	ON_CBN_SELCHANGE(IDC_COMBO_POSITION_ID2, OnSelchangeComboPositionId2)
	ON_BN_CLICKED(IDC_CHK_ENABLE, OnChkEnable)
	ON_BN_CLICKED(IDC_BTN_SET_PATROL_LIMITANGLE, OnBtnSetPatrolLimitangle)
	ON_BN_CLICKED(IDC_BTN_GET_MOVEMENT, OnBtnGetMovement)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIPDomeLocalCfg message handlers

BOOL CDlgIPDomeLocalCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_TRACK_PARAMCFG, m_iChannel, &m_struTrackParam, sizeof(m_struTrackParam), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRACK_PARAMCFG %d", m_iChannel);
        AfxMessageBox("NET_DVR_GET_TRACK_PARAMCFG Fail");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRACK_PARAMCFG %d", m_iChannel);
    }
    	
    if (!NET_DVR_GetPatrolTrack(m_lServerID, m_iChannel, 0, &m_struPatrolTrack))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PATROL_TRACKCFG");
        AfxMessageBox("NET_DVR_GetPatrolTrack Fail");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PATROL_TRACKCFG");
    }
	

    m_iPositionID = 1;
    m_comboPositionID2.SetCurSel(m_iPositionID-1);
    
    if (!NET_DVR_GetPtzPosition(m_lServerID, m_iChannel, m_iPositionID, &m_struPtzPosition))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPtzPosition ID[%d]", m_iPositionID);
        AfxMessageBox("NET_DVR_GetPtzPosition Fail");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPtzPosition ID[%d]", m_iPositionID);
    }

    InitComboZoomAdjust();
    m_iAlarmDelay = m_struTrackParam.wAlarmDelayTime;
    m_iTrackHold = m_struTrackParam.wTrackHoldTime;
    m_comboTrackMode.SetCurSel(m_struTrackParam.byTrackMode);
    m_comboZoomAdjust.SetCurSel(m_struTrackParam.byZoomAdjust);
    m_bPreDirection = m_struTrackParam.byPreDirection;
    m_bTrackSmooth = m_struTrackParam.byTrackSmooth;
    m_iMaxTrackZoom = m_struTrackParam.byMaxTrackZoom;
	m_bStopTrack = m_struTrackParam.byStopTrackWhenFindFace;
	m_iStopValue = m_struTrackParam.byStopTrackThreshold;

    m_iTrackIPointndex = 0;
    m_comboTrackPoint.SetCurSel(m_iTrackIPointndex);
    m_comboPositionID.SetCurSel(m_struPatrolTrack.struPatrolSceneInfo[m_iTrackIPointndex].byPositionID);
    m_iDwellTime = m_struPatrolTrack.struPatrolSceneInfo[m_iTrackIPointndex].wDwell;


    m_csPositionName = m_struPtzPosition.byPtzPositionName;
    m_bEnablePosition = m_struPtzPosition.byEnable;
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIPDomeLocalCfg::InitComboZoomAdjust()
{
    m_comboZoomAdjust.ResetContent();
    int nIndex = 0;
    m_comboZoomAdjust.AddString("Off");
    m_comboZoomAdjust.SetItemData(nIndex, nIndex);
    nIndex++;

    m_comboZoomAdjust.AddString("0.5");
    m_comboZoomAdjust.SetItemData(nIndex, nIndex);
    nIndex++;

    m_comboZoomAdjust.AddString("0.65");
    m_comboZoomAdjust.SetItemData(nIndex, nIndex);
    nIndex++;

    m_comboZoomAdjust.AddString("0.75");
    m_comboZoomAdjust.SetItemData(nIndex, nIndex);
    nIndex++;

    m_comboZoomAdjust.AddString("0.9");
    m_comboZoomAdjust.SetItemData(nIndex, nIndex);
    nIndex++;

    m_comboZoomAdjust.AddString("1.1");
    m_comboZoomAdjust.SetItemData(nIndex, nIndex);
    nIndex++;

    m_comboZoomAdjust.AddString("1.2");
    m_comboZoomAdjust.SetItemData(nIndex, nIndex);
    nIndex++;

    m_comboZoomAdjust.AddString("1.3");
    m_comboZoomAdjust.SetItemData(nIndex, nIndex);
}

void CDlgIPDomeLocalCfg::OnBtnSetUp() 
{
    UpdateData(TRUE);
    m_struTrackParam.wAlarmDelayTime = m_iAlarmDelay;
    m_struTrackParam.wTrackHoldTime = m_iTrackHold;
    m_struTrackParam.byTrackMode = m_comboTrackMode.GetCurSel();
    m_struTrackParam.byTrackSmooth = m_bTrackSmooth;
    m_struTrackParam.byPreDirection = m_bPreDirection;
    m_struTrackParam.byZoomAdjust = m_comboZoomAdjust.GetCurSel();
    m_struTrackParam.byMaxTrackZoom = m_iMaxTrackZoom;
	m_struTrackParam.byStopTrackWhenFindFace = m_bStopTrack;
	m_struTrackParam.byStopTrackThreshold = m_iStopValue;


    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_TRACK_PARAMCFG, m_iChannel, &m_struTrackParam, sizeof(m_struTrackParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACK_PARAMCFG %d", m_iChannel);
        AfxMessageBox("NET_DVR_SET_TRACK_PARAMCFG  Fail");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACK_PARAMCFG %d", m_iChannel);
    }
}

void CDlgIPDomeLocalCfg::OnBtnRealplay() 
{
    NET_DVR_CLIENTINFO struClientInfo;
    struClientInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    struClientInfo.lChannel = m_iChannel;
    struClientInfo.lLinkMode = 0; 
    struClientInfo.sMultiCastIP = "";
    if (m_lPlayHandle < 0)
    {
        m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo);
        if (m_lPlayHandle > 0)
        {
            GetDlgItem(IDC_BTN_REALPLAY)->SetWindowText("Stop preview");
        }
    }
    else
    {
        if (!NET_DVR_StopRealPlay(m_lPlayHandle))
        {
            MessageBox("Stop preview fail");
            return;
        }
        else
        {
            m_lPlayHandle = -1;
            GetDlgItem(IDC_BTN_REALPLAY)->SetWindowText("Preview");
            Invalidate(TRUE);
        }
        
    }
}

void CDlgIPDomeLocalCfg::OnBtnPatrolSet() 
{
    UpdateData(TRUE);
    m_iTrackIPointndex = m_comboTrackPoint.GetCurSel();
    m_struPatrolTrack.struPatrolSceneInfo[m_iTrackIPointndex].byPositionID = m_comboPositionID.GetCurSel();
    m_struPatrolTrack.struPatrolSceneInfo[m_iTrackIPointndex].wDwell = m_iDwellTime;
    
    if (!NET_DVR_SetPatrolTrack(m_lServerID, m_iChannel, 0, &m_struPatrolTrack))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PATROL_TRACKCFG");
        AfxMessageBox("NET_DVR_SetPatrolTrack fail");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PATROL_TRACKCFG");
    }
}

void CDlgIPDomeLocalCfg::OnBtnPatrolConfirm() 
{
    UpdateData(TRUE);
    m_iTrackIPointndex = m_comboTrackPoint.GetCurSel();
    m_struPatrolTrack.struPatrolSceneInfo[m_iTrackIPointndex].byPositionID = m_comboPositionID.GetCurSel();
    m_struPatrolTrack.struPatrolSceneInfo[m_iTrackIPointndex].wDwell = m_iDwellTime;
}

void CDlgIPDomeLocalCfg::OnSelchangeComboTrackPoint() 
{
	m_iTrackIPointndex = m_comboTrackPoint.GetCurSel();
    m_comboPositionID.SetCurSel(m_struPatrolTrack.struPatrolSceneInfo[m_iTrackIPointndex].byPositionID);
    m_iDwellTime = m_struPatrolTrack.struPatrolSceneInfo[m_iTrackIPointndex].wDwell;
    UpdateData(FALSE);
}

void CDlgIPDomeLocalCfg::OnBtnSetPosition() 
{
    m_iPositionID = m_comboPositionID2.GetCurSel()+1;
    
    DWORD dwReturn;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PTZPOS, m_iChannel, &m_struPtzPosition.struPtzPos, sizeof(m_struPtzPosition.struPtzPos), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS");
        AfxMessageBox("NET_DVR_GET_PTZPOS fail");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZPOS %d t%d z%d", \
            m_struPtzPosition.struPtzPos.wPanPos, m_struPtzPosition.struPtzPos.wTiltPos, m_struPtzPosition.struPtzPos.wZoomPos);
    }
    UpdateData(TRUE);
    m_struPtzPosition.byEnable = m_bEnablePosition;
    strncpy((char*)m_struPtzPosition.byPtzPositionName, m_csPositionName.GetBuffer(0), sizeof(m_struPtzPosition.byPtzPositionName));
    if (!NET_DVR_SetPtzPosition(m_lServerID, m_iChannel, m_iPositionID, &m_struPtzPosition))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetPtzPosition ID[%d]", m_iPositionID);
        AfxMessageBox("NET_DVR_SetPtzPosition fail");
    }
    else 
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetPtzPosition ID[%d]", m_iPositionID);
    }

}

void CDlgIPDomeLocalCfg::OnBtnGetPtz() 
{
    m_struPtzPosition.struPtzPos.wAction = 1;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PTZPOS, m_iChannel, &m_struPtzPosition.struPtzPos, sizeof(m_struPtzPosition.struPtzPos)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PTZPOS");
        
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,     OPERATION_SUCC_T, "NET_DVR_SET_PTZPOS %d t%d z%d", \
            m_struPtzPosition.struPtzPos.wPanPos, m_struPtzPosition.struPtzPos.wTiltPos, m_struPtzPosition.struPtzPos.wZoomPos);
    }
}

void CDlgIPDomeLocalCfg::OnBtnPtzCtrl() 
{
    CDlgPtzCtrl dlg;
    dlg.m_lPlayHandle = m_lPlayHandle;
    dlg.DoModal();	
}

void CDlgIPDomeLocalCfg::OnSelchangeComboPositionId2() 
{
    m_iPositionID = m_comboPositionID2.GetCurSel() +1;
    if (!NET_DVR_GetPtzPosition(m_lServerID, m_iChannel, m_iPositionID, &m_struPtzPosition))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPtzPosition ID[%d]", m_iPositionID);
        AfxMessageBox("NET_DVR_GetPtzPosition fail");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPtzPosition ID[%d]", m_iPositionID);
    }
    m_csPositionName = m_struPtzPosition.byPtzPositionName;
    m_bEnablePosition = m_struPtzPosition.byEnable;
    UpdateData(FALSE);
}

void CDlgIPDomeLocalCfg::PostNcDestroy() 
{
    if (m_lPlayHandle > 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
    }
	CDialog::PostNcDestroy();
}

void CDlgIPDomeLocalCfg::OnChkEnable() 
{
	UpdateData(TRUE);
}

void CDlgIPDomeLocalCfg::OnBtnSetPatrolLimitangle() 
{
    CDlgLimitAngle dlg;
    dlg.m_lPlayHandle = m_lPlayHandle;
    dlg.m_iPatrolIndex = m_iPositionID;
    dlg.m_iLimitAngleType = PATROL_LIMIT_ANGLE;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CDlgIPDomeLocalCfg::OnBtnGetMovement() 
{
    NET_DVR_DOME_MOVEMENT_PARAM struDomeMovement = {0};
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DOME_MOVEMENT_PARAM, m_iChannel, &struDomeMovement, sizeof(struDomeMovement), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DOME_MOVEMENT_PARAM");
    }
    else
    {
        char szLan[138] = {0};
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DOME_MOVEMENT_PARAM");
        
        sprintf(szLan, "Max Zoom is %d", struDomeMovement.wMaxZoom);
        AfxMessageBox(szLan);
    }
    	
}
