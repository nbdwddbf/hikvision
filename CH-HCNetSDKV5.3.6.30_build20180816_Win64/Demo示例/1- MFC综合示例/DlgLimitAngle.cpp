// DlgLimitAngle.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLimitAngle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLimitAngle dialog


CDlgLimitAngle::CDlgLimitAngle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLimitAngle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLimitAngle)
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
    memset(&m_struLimiteAngle, 0, sizeof(m_struLimiteAngle));
    m_iPositionIndex = 0;
    m_iPatrolIndex = 0;
    m_iLimitAngleType = POSITION_LIMIT_ANGLE;
    m_lServerID = -1;
    m_lChannel = -1;
    m_iDevIndex = -1;

}


void CDlgLimitAngle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLimitAngle)	 
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLimitAngle, CDialog)
	//{{AFX_MSG_MAP(CDlgLimitAngle)
	ON_BN_CLICKED(IDC_BTN_SET_LIMITANGLE, OnBtnSetLimitangle)
	ON_BN_CLICKED(IDC_BTN_SET_DOWN_LIMITANGEL, OnBtnSetDownLimitangel)
	ON_BN_CLICKED(IDC_BTN_SET_LEFT_LIMITANGLE, OnBtnSetLeftLimitangle)
	ON_BN_CLICKED(IDC_BTN_SET_RIGHT_LIMITANGLE, OnBtnSetRightLimitangle)
	ON_BN_CLICKED(IDC_BTN_SET_UP_LIMITANGLE, OnBtnSetUpLimitangle)
	ON_BN_CLICKED(IDC_BTN_GET_DOWN_LIMITANGEL, OnBtnGetDownLimitangel)
	ON_BN_CLICKED(IDC_BTN_GET_LEFT_LIMITANGLE, OnBtnGetLeftLimitangle)
	ON_BN_CLICKED(IDC_BTN_GET_RIGHT_LIMITANGLE, OnBtnGetRightLimitangle)
	ON_BN_CLICKED(IDC_BTN_GET_UP_LIMITANGLE, OnBtnGetUpLimitangle)
	ON_BN_CLICKED(IDC_BTN_POSITION_PTZ, OnBtnPositionPtz)
	ON_BN_CLICKED(IDC_BTN_GET_LIMITANGLE, OnBtnGetLimitangle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLimitAngle message handlers

void CDlgLimitAngle::OnBtnSetLimitangle() 
{
    UpdateData(TRUE);
    m_struLimiteAngle.byEnable = m_bEnable;
	if (POSITION_LIMIT_ANGLE == m_iLimitAngleType)
	{
        if (!SetPositionLimitAngle())
        {
            AfxMessageBox("Fail to set position limit angle");
        }
	}
    else if (PATROL_LIMIT_ANGLE == m_iLimitAngleType)
    {
        if (!SetPatrolLimitAngle())
        {
            AfxMessageBox("Fail to set patrol limit angle");
        }
    }
}

void CDlgLimitAngle::InitPTZButton()
{
    m_btnPtzUp.SubclassDlgItem(IDC_BTN_PTZ_UP,this);
    m_btnPtzDown.SubclassDlgItem(IDC_BTN_PTZ_DOWN,this);
    m_btnPtzLeft.SubclassDlgItem(IDC_BTN_PTZ_LEFT,this);
    m_btnPtzRight.SubclassDlgItem(IDC_BTN_PTZ_RIGHT,this);	
    m_btnZoomOut.SubclassDlgItem(IDC_BTN_ZOOM_OUT,this);
    m_btnZoomIn.SubclassDlgItem(IDC_BTN_ZOOM_IN,this);
    m_btnFocusNear.SubclassDlgItem(IDC_BTN_FOCUS_NEAR,this);
    m_btnFocusFar.SubclassDlgItem(IDC_BTN_FOCUS_FAR,this);
    m_btnIrisOpen.SubclassDlgItem(IDC_BTN_IRIS_OPEN,this);
    m_btnIrisClose.SubclassDlgItem(IDC_BTN_IRIS_CLOSE,this);
    
    m_btnPtzUp.m_iPTZType = TILT_UP;
    m_btnPtzDown.m_iPTZType = TILT_DOWN;
    m_btnPtzLeft.m_iPTZType = PAN_LEFT;
    m_btnPtzRight.m_iPTZType = PAN_RIGHT;
    m_btnZoomOut.m_iPTZType = ZOOM_OUT;
    m_btnZoomIn.m_iPTZType = ZOOM_IN;
    m_btnFocusNear.m_iPTZType = FOCUS_NEAR;
    m_btnFocusFar.m_iPTZType = FOCUS_FAR;
    m_btnIrisOpen.m_iPTZType = IRIS_OPEN;
    m_btnIrisClose.m_iPTZType = IRIS_CLOSE;
    
    m_btnPtzUp.m_lPlayHandle = m_lPlayHandle;
    m_btnPtzDown.m_lPlayHandle = m_lPlayHandle;
    m_btnPtzLeft.m_lPlayHandle = m_lPlayHandle;
    m_btnPtzRight.m_lPlayHandle = m_lPlayHandle;
    m_btnZoomOut.m_lPlayHandle = m_lPlayHandle;
    m_btnZoomIn.m_lPlayHandle = m_lPlayHandle;	
    m_btnFocusNear.m_lPlayHandle = m_lPlayHandle;
    m_btnFocusFar.m_lPlayHandle = m_lPlayHandle;
    m_btnIrisOpen.m_lPlayHandle = m_lPlayHandle;
    m_btnIrisClose.m_lPlayHandle = m_lPlayHandle;

}

BOOL CDlgLimitAngle::OnInitDialog() 
{
	CDialog::OnInitDialog();

	g_AddChanInfoToComBox(m_cmbChannel,m_iDevIndex);
	m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	InitPTZButton();

	if (POSITION_LIMIT_ANGLE == m_iLimitAngleType)
	{
		if (!GetPositionLimitAngle())
		{
			AfxMessageBox("fail to get position limit angle ");
		}
	}
	else if (PATROL_LIMIT_ANGLE == m_iLimitAngleType)
	{
		if (!GetPatrolLimitAngle())
		{
			AfxMessageBox("fail to get patrol limit angle");
		}
	}
    m_bEnable = m_struLimiteAngle.byEnable;
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgLimitAngle::GetPositionLimitAngle()
{
	UpdateData(TRUE);
	m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

    if (!NET_DVR_GetPositionLimitAngle(m_lServerID, m_lChannel, m_iPositionIndex, &m_struLimiteAngle))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPositionLimitAngle");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPositionLimitAngle");
        return TRUE;
    }
}

BOOL CDlgLimitAngle::SetPositionLimitAngle()
{
	UpdateData(TRUE);
	m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    m_struLimiteAngle.byEnable = TRUE;
    if (!NET_DVR_SetPositionLimitAngle(m_lServerID, m_lChannel, m_iPositionIndex, &m_struLimiteAngle))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetPositionLimitAngle");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetPositionLimitAngle");
        return TRUE;
    }
}

BOOL CDlgLimitAngle::GetPatrolLimitAngle()
{

	UpdateData(TRUE);
	m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());	
    if (!NET_DVR_GetPatrolLimitAngle(m_lServerID, m_lChannel, m_iPatrolIndex, &m_struLimiteAngle))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPatrolLimitAngle");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPatrolLimitAngle");
        return TRUE;
    }
}

BOOL CDlgLimitAngle::SetPatrolLimitAngle()
{
    if (!NET_DVR_SetPatrolLimitAngle(m_lServerID, m_lChannel, m_iPatrolIndex, &m_struLimiteAngle))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetPatrolLimitAngle");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetPatrolLimitAngle");
        return TRUE;
    }
}

void CDlgLimitAngle::GetPtzPos(NET_DVR_PTZPOS &struPtzPos)
{
	UpdateData(TRUE);
	m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PTZPOS, m_lChannel, &struPtzPos, sizeof(struPtzPos), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZPOS");
    }
}

void CDlgLimitAngle::SetPtzPos(NET_DVR_PTZPOS &struPtzPos)
{
	UpdateData(TRUE);
	m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

    struPtzPos.wAction = 1;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PTZPOS, m_lChannel, &struPtzPos, sizeof(struPtzPos)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PTZPOS");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PTZPOS");
    }
}

void CDlgLimitAngle::OnBtnSetDownLimitangel() 
{
	SetPtzPos(m_struLimiteAngle.struDown);
}

void CDlgLimitAngle::OnBtnSetLeftLimitangle() 
{
	SetPtzPos(m_struLimiteAngle.struLeft);
}

void CDlgLimitAngle::OnBtnSetRightLimitangle() 
{
	SetPtzPos(m_struLimiteAngle.struRight);
}

void CDlgLimitAngle::OnBtnSetUpLimitangle() 
{
	SetPtzPos(m_struLimiteAngle.struUp);
}

void CDlgLimitAngle::OnBtnGetDownLimitangel() 
{
	GetPtzPos(m_struLimiteAngle.struDown);	
}

void CDlgLimitAngle::OnBtnGetLeftLimitangle() 
{
	GetPtzPos(m_struLimiteAngle.struLeft);
}

void CDlgLimitAngle::OnBtnGetRightLimitangle() 
{
	GetPtzPos(m_struLimiteAngle.struRight);
}

void CDlgLimitAngle::OnBtnGetUpLimitangle() 
{
	GetPtzPos(m_struLimiteAngle.struUp);
}

void CDlgLimitAngle::OnBtnPositionPtz() 
{
	UpdateData(TRUE);
	m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

    if (POSITION_LIMIT_ANGLE == m_iLimitAngleType)
    {
        NET_DVR_POSITION_RULE_CFG struPositionRule = {0};
        if (!NET_DVR_GetPositionRule(m_lServerID, m_lChannel, m_iPositionIndex, &struPositionRule))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPositionRule");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPositionRule");
            SetPtzPos(struPositionRule.struPtzPosition.struPtzPos);
        }
    }
    else if (PATROL_LIMIT_ANGLE == m_iLimitAngleType)
    {
        NET_DVR_PTZ_POSITION struPtzPosition = {0};
        if (!NET_DVR_GetPtzPosition(m_lServerID, m_lChannel, m_iPatrolIndex, &struPtzPosition))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPtzPosition");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPtzPosition");
            SetPtzPos(struPtzPosition.struPtzPos);
        }
    }
        	
}

void CDlgLimitAngle::OnBtnGetLimitangle() 
{
	// TODO: Add your control notification handler code here
	GetPositionLimitAngle();
}
