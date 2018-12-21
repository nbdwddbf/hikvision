// DlgSensorAddPreview.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSensorAddPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgSensorAddPreview dialog


CDlgSensorAddPreview::CDlgSensorAddPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSensorAddPreview::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSensorAddPreview)
	m_bEnable = FALSE;
	m_iChannel = 0;
	m_csIPAddress = _T("");
	//}}AFX_DATA_INIT
    memset(&m_struAlarmHostAbility, 0, sizeof(m_struAlarmHostAbility));
    m_lServerID = -1;
    m_iDevIndex = -1;
    
}


void CDlgSensorAddPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSensorAddPreview)
	DDX_Control(pDX, IDC_COMBO_SENSOR_INDEX, m_comboSensorIndex);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_iChannel);
	DDX_Text(pDX, IDC_EDIT_IP_ADDRESS, m_csIPAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSensorAddPreview, CDialog)
	//{{AFX_MSG_MAP(CDlgSensorAddPreview)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSOR_INDEX, OnSelchangeComboSensorIndex)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSensorAddPreview message handlers


BOOL CDlgSensorAddPreview::GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility)
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if (NET_DVR_GetDeviceAbility(m_lServerID, ALARMHOST_ABILITY, NULL, 0, (char*)&struAlarmHostAbility, sizeof(struAlarmHostAbility)))
    {
        char szLan[128] = {0};
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgSensorAddPreview::OnInitDialog() 
{
	CDialog::OnInitDialog();
    GetAlarmHostAbility(m_struAlarmHostAbility);
    g_ReadLocalReadSensorAdd();
    InitWnd();
	GetSensorAddPreviewList();
    m_comboSensorIndex.SetCurSel(0);
    OnSelchangeComboSensorIndex();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSensorAddPreview::InitWnd()
{
    char szLan[128] = {0};
    for (int i = 0; i < 16; i++)
    {
        sprintf(szLan, "Sensor %d", i+1);
        m_comboSensorIndex.AddString(szLan);
    }
}

BOOL CDlgSensorAddPreview::GetSensorAddPreviewList()
{
    return TRUE;
}

BOOL CDlgSensorAddPreview::SetSensorAddPreviewList()
{
    return TRUE;
}

void CDlgSensorAddPreview::GetSensorAddPreviewFromWnd(LOCAL_SENSOR_ADD_PREVIEW &struSensorAddPreview)
{
    UpdateData(TRUE);
    struSensorAddPreview.byEnable = m_bEnable;
    strncpy(struSensorAddPreview.struIPAddr.sIpV4, m_csIPAddress.GetBuffer(0), sizeof(struSensorAddPreview.struIPAddr.sIpV4));
    struSensorAddPreview.lChannel = m_iChannel;
}

void CDlgSensorAddPreview::SetSensorAddPreviewToWnd(LOCAL_SENSOR_ADD_PREVIEW &struSensorAddPreview)
{
    m_bEnable = struSensorAddPreview.byEnable;
    m_csIPAddress = struSensorAddPreview.struIPAddr.sIpV4;
    m_iChannel = struSensorAddPreview.lChannel;
    UpdateData(FALSE);
}

void CDlgSensorAddPreview::OnSelchangeComboSensorIndex() 
{
    SetSensorAddPreviewToWnd(g_struSensorAddPreview[m_comboSensorIndex.GetCurSel()]);
}

void CDlgSensorAddPreview::OnBtnSave() 
{
    GetSensorAddPreviewFromWnd(g_struSensorAddPreview[m_comboSensorIndex.GetCurSel()]);
    SetSensorAddPreviewList();
    g_SaveLocalReadSensorAdd();
}

void CDlgSensorAddPreview::OnBtnConfirm() 
{
    GetSensorAddPreviewFromWnd(g_struSensorAddPreview[m_comboSensorIndex.GetCurSel()]);
    
}
