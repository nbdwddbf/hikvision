// DlgVcaSceneCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaSceneCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneCfg dialog


LONG CScenePTZButton::m_lPlayHandle = -1;

CScenePTZButton::CScenePTZButton()
{
	m_dwPtzCommand = 0;
}

CScenePTZButton::~CScenePTZButton()
{
}


BEGIN_MESSAGE_MAP(CScenePTZButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CScenePTZButton::PTZControlAll(LONG lRealHandle,DWORD dwPTZCommand,DWORD dwStop)
{
	BOOL bRet = FALSE;
	if (m_lPlayHandle >= 0 )
	{
		bRet = NET_DVR_PTZControl(m_lPlayHandle, dwPTZCommand, dwStop);//not on the preview socket	
	}
	return bRet;
}


void CScenePTZButton::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (m_lPlayHandle >= 0)
	{
		PTZControlAll(m_lPlayHandle,m_dwPtzCommand,0);
	}
	CButton::OnLButtonDown(nFlags, point);
}


void CScenePTZButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	PTZControlAll(m_lPlayHandle,m_dwPtzCommand,1);
	CButton::OnLButtonUp(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneCfg dialog


CDlgVcaSceneCfg::CDlgVcaSceneCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaSceneCfg::IDD, pParent)
{
	m_lPlayHandle    = -1;
	m_lPUServerID    = -1;
    
	m_nCurSceneIndex =  0;
	m_nSceneID       =  0;
	m_nTrackTime     =  0;
	m_nPtzXPos       =  0;
	m_nPtzYPos       =  0;
	m_nPtzZPos       =  0;
	m_strSceneName   = _T("");

	memset(&m_struSceneCfg,0,sizeof(m_struSceneCfg));
	m_struSceneCfg.dwSize = sizeof(m_struSceneCfg);
}


void CDlgVcaSceneCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_COMBO_SCENENO,      m_comboSceneNo);
	DDX_Check(pDX,  IDC_CHECK_SCENE_ENABLE, m_bSceneEnable);
	DDX_Text(pDX,   IDC_EDIT_SCENE_NAME,    m_strSceneName);
	DDX_Text(pDX,   IDC_EDIT_SCENE_ID,      m_nSceneID);
	DDX_Control(pDX,IDC_COMBO_DIRECTION,    m_comboDirection);
	DDX_Text(pDX,   IDC_EDIT_TRACKTIME,     m_nTrackTime);
	DDX_Text(pDX,   IDC_EDIT_PTZ_X,         m_nPtzXPos);
	DDX_Text(pDX,   IDC_EDIT_PTZ_Y,         m_nPtzYPos);
	DDX_Text(pDX,   IDC_EDIT_PTZ_Z,         m_nPtzZPos);
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
}


BEGIN_MESSAGE_MAP(CDlgVcaSceneCfg, CDialog)
    ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_SCENENO,  OnSelchangeComboSceneno)
    ON_BN_CLICKED(IDC_BTN_GETPTZPOS,     OnBtnClickedGetPtzPos)
    ON_BN_CLICKED(IDC_BTN_SAVE_SCENE_CFG,OnBtnClickedSaveSceneCfg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneCfg message handlers

BOOL CDlgVcaSceneCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitCtrlState();

	if (!GetSceneCfg())
	{
		char szError[64] = {0};
		g_StringLanType(szError, "获取场景配置信息失败", "Get Scene cfg failed!");
		AfxMessageBox(szError);
	}

	StartRealPlay(GetDlgItem(IDC_STATIC_PLAYWND)->GetSafeHwnd(),NULL,NULL);

    LoadSceneParam(m_nCurSceneIndex);

	CScenePTZButton::m_lPlayHandle = m_lPlayHandle;

	return TRUE;
}

void CDlgVcaSceneCfg::OnDestroy()
{
    StopRealPlay();
	CDialog::OnDestroy();
}

void CDlgVcaSceneCfg::OnSelchangeComboSceneno() 
{
	int nCurSel = m_comboSceneNo.GetCurSel();
	if (nCurSel != CB_ERR)
	{
		SaveSceneParam(m_nCurSceneIndex);

		m_nCurSceneIndex = nCurSel;

		LoadSceneParam(nCurSel);
	}
}

void CDlgVcaSceneCfg::OnBtnClickedGetPtzPos()
{
	NET_DVR_PTZPOS struPtzPos = {0};
    DWORD  dwReturn  = 0;
	BOOL   bRst      = FALSE;
	if (m_lPUServerID >= 0)
	{
		bRst = NET_DVR_GetDVRConfig(m_lPUServerID,NET_DVR_GET_PTZPOS,1,&struPtzPos,sizeof(struPtzPos),&dwReturn);
	}
	else
	{
		bRst = NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_PTZPOS, m_lChannel,&struPtzPos,sizeof(struPtzPos),&dwReturn);
	}

    if (!bRst)
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS Chan[%d]", m_lChannel);

		char szLan[32] = {0};
		g_StringLanType(szLan, "获取PTZ坐标失败", "Get PTZ pos failed!");
		AfxMessageBox(szLan);
	}
	m_nPtzXPos  = HexToDec(struPtzPos.wPanPos);
	m_nPtzYPos  = HexToDec(struPtzPos.wTiltPos);
	m_nPtzZPos  = HexToDec(struPtzPos.wZoomPos);

	SetDlgItemInt(IDC_EDIT_PTZ_X,m_nPtzXPos);
	SetDlgItemInt(IDC_EDIT_PTZ_Y,m_nPtzYPos);
	SetDlgItemInt(IDC_EDIT_PTZ_Z,m_nPtzZPos);
}


void CDlgVcaSceneCfg::OnBtnClickedSaveSceneCfg()
{   
	SaveSceneParam(m_nCurSceneIndex);
    
	char szError[32] = "\0";
	if (SaveSceneCfg())
	{
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVcaSceneCfg::InitCtrlState()
{   
	CString strItemText = _T("");
	for (int i = 0; i < 16; i++)
	{    
		 strItemText.Format(_T("%d"), i + 1);
		 m_comboSceneNo.InsertString(i,strItemText);
		 m_comboSceneNo.SetItemData(i,i);
	}
    m_comboSceneNo.SetCurSel(0);
    
	char szDirection[50] = "\0";
	
	g_StringLanType(szDirection, "上行",     "Up");
	m_comboDirection.InsertString(0,szDirection);
	m_comboDirection.SetItemData(0,CHAN_DIRECTION_UP);
	
	g_StringLanType(szDirection, "下行",     "Down");
	m_comboDirection.InsertString(1,szDirection);
	m_comboDirection.SetItemData(1,CHAN_DIRECTION_DOWN);
	
	g_StringLanType(szDirection, "双向",     "Bi");
	m_comboDirection.InsertString(2,szDirection);
	m_comboDirection.SetItemData(2,CHAN_DIRECTION_BI);
	
	g_StringLanType(szDirection, "由东向西", "East->West");
	m_comboDirection.InsertString(3,szDirection);
	m_comboDirection.SetItemData(3,CHAN_DIRECTION_EAST_WEST);
	
    g_StringLanType(szDirection, "由南向北", "South->North");
	m_comboDirection.InsertString(4,szDirection);
	m_comboDirection.SetItemData(4,CHAN_DIRECTION_SOUTH_NORTH);
	
	g_StringLanType(szDirection, "由西向东", "West->East");
	m_comboDirection.InsertString(5,szDirection);
	m_comboDirection.SetItemData(5,CHAN_DIRECTION_WEST_EAST);
	
	g_StringLanType(szDirection, "由北向南", "North->South");
	m_comboDirection.InsertString(6,szDirection);
	m_comboDirection.SetItemData(6,CHAN_DIRECTION_NORTH_SOUTH);
	
	g_StringLanType(szDirection, "其他",     "Other");
	m_comboDirection.InsertString(7,szDirection);
	m_comboDirection.SetItemData(7,CHAN_DIRECTION_OTHER);

	m_comboDirection.SetCurSel(0);
    
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
}


BOOL CDlgVcaSceneCfg::GetSceneCfg()
{   
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;

    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SCENE_CFG, 1,(LPVOID)&m_lChannel, sizeof(m_lChannel),
		&dwStatus,&m_struSceneCfg, sizeof(m_struSceneCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCENE_CFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCENE_CFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaSceneCfg::SaveSceneCfg()
{   
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;

    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_SCENE_CFG,1,(LPVOID)&m_lChannel, sizeof(m_lChannel),
		&dwStatus,&m_struSceneCfg, sizeof(m_struSceneCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCENE_CFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCENE_CFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

void CDlgVcaSceneCfg::LoadSceneParam(int nSceneIndex)
{
	m_bSceneEnable  = m_struSceneCfg.struSceneCfg[nSceneIndex].byEnable;
	m_strSceneName  = m_struSceneCfg.struSceneCfg[nSceneIndex].bySceneName;
	m_nSceneID      = m_struSceneCfg.struSceneCfg[nSceneIndex].dwSceneID;
	m_nTrackTime    = m_struSceneCfg.struSceneCfg[nSceneIndex].dwTrackTime;
	m_nPtzXPos      = HexToDec(m_struSceneCfg.struSceneCfg[nSceneIndex].struPtzPos.wPanPos);
	m_nPtzYPos      = HexToDec(m_struSceneCfg.struSceneCfg[nSceneIndex].struPtzPos.wTiltPos);
	m_nPtzZPos      = HexToDec(m_struSceneCfg.struSceneCfg[nSceneIndex].struPtzPos.wZoomPos);
	
	int nDirection      = m_struSceneCfg.struSceneCfg[nSceneIndex].byDirection;
	int nDirectionCount = m_comboDirection.GetCount();
	for (int i = 0; i < nDirectionCount; i++)
	{
		if (nDirection == m_comboDirection.GetItemData(i))
		{
			m_comboDirection.SetCurSel(i);
			break;
		}
	}

	UpdateData(FALSE);
}

void CDlgVcaSceneCfg::SaveSceneParam(int nSceneIndex)
{   
	UpdateData(TRUE);

	m_struSceneCfg.struSceneCfg[nSceneIndex].byEnable   = m_bSceneEnable;
	strncpy((char*)m_struSceneCfg.struSceneCfg[nSceneIndex].bySceneName, m_strSceneName.GetBuffer(0), 
		sizeof(m_struSceneCfg.struSceneCfg[nSceneIndex].bySceneName));
	m_struSceneCfg.struSceneCfg[nSceneIndex].dwSceneID   = m_nSceneID;
	m_struSceneCfg.struSceneCfg[nSceneIndex].dwTrackTime = m_nTrackTime;
	m_struSceneCfg.struSceneCfg[nSceneIndex].struPtzPos.wPanPos  =  DecToHex(m_nPtzXPos);
	m_struSceneCfg.struSceneCfg[nSceneIndex].struPtzPos.wTiltPos =  DecToHex(m_nPtzYPos);
	m_struSceneCfg.struSceneCfg[nSceneIndex].struPtzPos.wZoomPos =  DecToHex(m_nPtzZPos);
	
	int nDirectionIndex = m_comboDirection.GetCurSel();
	if (nDirectionIndex != CB_ERR)
	{
		m_struSceneCfg.struSceneCfg[nSceneIndex].byDirection = m_comboDirection.GetItemData(nDirectionIndex);
	}
}
