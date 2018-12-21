// DlgAlarmHostEnableCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostEnableCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostEnableCfg dialog


CDlgAlarmHostEnableCfg::CDlgAlarmHostEnableCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostEnableCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostEnableCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struAbility, 0, sizeof(m_struAbility));
    memset(&m_struEnableCfg, 0, sizeof(m_struEnableCfg));
}


void CDlgAlarmHostEnableCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostEnableCfg)
	DDX_Control(pDX, IDC_LIST_SIREN, m_listSiren);
	DDX_Control(pDX, IDC_LIST_MOBILE_GATE, m_listMobileGate);
	DDX_Control(pDX, IDC_LIST_ELECTOR_LOCK, m_listElectorLock);
	DDX_Control(pDX, IDC_LIST_AUDIO_OUT, m_listAudioOut);
	DDX_Control(pDX, IDC_COMBO_SERIAL_PURPOSE, m_comboSirenPurpose);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostEnableCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostEnableCfg)
	ON_BN_CLICKED(IDC_BTN_SETUP, OnBtnSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostEnableCfg message handlers

BOOL CDlgAlarmHostEnableCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    InitWnd();
	
    GetAlarmHostEnable(m_struEnableCfg);
    SetAlarmHostEnableToWnd(m_struEnableCfg);
    UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAlarmHostEnableCfg::InitWnd()
{
    InitAudioOutList();
    InitElectroLockList();
    InitMobileGateList();
    InitSirenList();
    InitSerialPurposr();
}

void CDlgAlarmHostEnableCfg::InitAudioOutList()
{
    /*SetExtendedStyle(LVS_EX_CHECKBOXES);*/
    m_listAudioOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
    char szLan[128] = {0};
    for (int i = 0; i < m_struAbility.wAudioOutNum; i++)
    {
        sprintf(szLan, "Audio out %d", i + 1);
        m_listAudioOut.InsertItem(i, szLan);
    }
}

void CDlgAlarmHostEnableCfg::InitElectroLockList()
{
    m_listElectorLock.SetExtendedStyle(LVS_EX_CHECKBOXES);
    char szLan[128] = {0};
    for (int i = 0; i < m_struAbility.wElectroLockNum; i++)
    {
        sprintf(szLan, "Electrol lock %d", i + 1);
        m_listElectorLock.InsertItem(i, szLan);
    }
}

void CDlgAlarmHostEnableCfg::InitMobileGateList()
{
    m_listMobileGate.SetExtendedStyle(LVS_EX_CHECKBOXES);
    char szLan[128] = {0};
    for (int i = 0; i < m_struAbility.wGatewayNum; i++)
    {
        sprintf(szLan, "Mobile gate %d", i + 1);
        m_listMobileGate.InsertItem(i, szLan);
    }
}

void CDlgAlarmHostEnableCfg::InitSirenList()
{
    m_listSiren.SetExtendedStyle(LVS_EX_CHECKBOXES);
    char szLan[128] = {0};

    for (int i = 0; i< m_struAbility.wSirenNum; i++)
    {
        sprintf(szLan, "Siren %d", i + 1);
        m_listSiren.InsertItem(i, szLan);
    }
}

void CDlgAlarmHostEnableCfg::InitSerialPurposr()
{
	char szLan[128] = {0};
    m_comboSirenPurpose.ResetContent();
    g_StringLanType(szLan, "级联控制", "CONCATENATION CONTROL");
	m_comboSirenPurpose.AddString(szLan);
	g_StringLanType(szLan, "PTZ控制", "PTZ CONTROL");
    m_comboSirenPurpose.AddString(szLan);
}

BOOL CDlgAlarmHostEnableCfg::GetAlarmHostEnable(NET_DVR_ALARMHOST_ENABLECFG &struEnableCfg)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMHOST_ENABLECFG, 0, &struEnableCfg, sizeof(struEnableCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOST_ENABLECFG");
        return TRUE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOST_ENABLECFG");
        return FALSE;
    }
}

BOOL CDlgAlarmHostEnableCfg::SetAlarmHostEnable(NET_DVR_ALARMHOST_ENABLECFG &struEnableCfg)
{
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARMHOST_ENABLECFG, 0, &struEnableCfg, sizeof(struEnableCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMHOST_ENABLECFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMHOST_ENABLECFG");
        return FALSE;
    }
}

void CDlgAlarmHostEnableCfg::OnBtnSetup() 
{
	UpdateData(TRUE);
    GetAlarmHostEnableFromWnd(m_struEnableCfg);
    SetAlarmHostEnable(m_struEnableCfg);
}

void CDlgAlarmHostEnableCfg::GetAlarmHostEnableFromWnd(NET_DVR_ALARMHOST_ENABLECFG &struEnableCfg)
{
    struEnableCfg.bySerialPurpose = m_comboSirenPurpose.GetCurSel();
    GetAudioOutFromWnd(struEnableCfg.byAudioOutEnable, ARRAY_SIZE(struEnableCfg.byAudioOutEnable));
    GetElectroLockFromWnd(struEnableCfg.byElectroLockEnable, ARRAY_SIZE(struEnableCfg.byElectroLockEnable));
    GetMobileGateFromWnd(struEnableCfg.byMobileGateEnable, ARRAY_SIZE(struEnableCfg.byMobileGateEnable));
	GetSirenFromWnd(struEnableCfg.bySirenEnable, ARRAY_SIZE(struEnableCfg.bySirenEnable));
}

void CDlgAlarmHostEnableCfg::SetAlarmHostEnableToWnd(NET_DVR_ALARMHOST_ENABLECFG &struEnableCfg)
{
    m_comboSirenPurpose.SetCurSel(struEnableCfg.bySerialPurpose);
    SetAudioOutToWnd(struEnableCfg.byAudioOutEnable, ARRAY_SIZE(struEnableCfg.byAudioOutEnable));
    SetElectroLockToWnd(struEnableCfg.byElectroLockEnable, ARRAY_SIZE(struEnableCfg.byElectroLockEnable));
    SetMobileGateToWnd(struEnableCfg.byMobileGateEnable, ARRAY_SIZE(struEnableCfg.byMobileGateEnable));
	SetSirenToWnd(struEnableCfg.bySirenEnable, ARRAY_SIZE(struEnableCfg.bySirenEnable));
}

void CDlgAlarmHostEnableCfg::GetAudioOutFromWnd(BYTE *byAudioOut, DWORD dwSize)
{
    for (int i = 0; i < m_listAudioOut.GetItemCount(); i++)
    {
        if (TRUE == m_listAudioOut.GetCheck(i))
        {
            byAudioOut[i] = TRUE;
        }
        else
        {
            byAudioOut[i] = FALSE;
        }
    }
}

void CDlgAlarmHostEnableCfg::SetAudioOutToWnd(BYTE *byAudioOut, DWORD dwSize)
{
    for (int i = 0; i < m_listAudioOut.GetItemCount(); i++)
    {
        if (1 == byAudioOut[i])
        {
            m_listAudioOut.SetCheck(i, TRUE);
        }
        else
        {
            m_listAudioOut.SetCheck(i, FALSE);
        }
    }
}

void CDlgAlarmHostEnableCfg::GetElectroLockFromWnd(BYTE *byElectroLock, DWORD dwSize)
{
    for (int i = 0; i < m_listElectorLock.GetItemCount(); i++)
    {
        if (TRUE == m_listElectorLock.GetCheck(i))
        {
            byElectroLock[i] = TRUE;
        }
        else
        {
            byElectroLock[i] = FALSE;
        }
    }
}

void CDlgAlarmHostEnableCfg::SetElectroLockToWnd(BYTE *byElectroLock, DWORD dwSize)
{
    for (int i = 0; i < m_listElectorLock.GetItemCount(); i++)
    {
        if (1 == byElectroLock[i])
        {
            m_listElectorLock.SetCheck(i, TRUE);
        }
        else
        {
            m_listElectorLock.SetCheck(i, FALSE);
        }
    }
}

void CDlgAlarmHostEnableCfg::GetMobileGateFromWnd(BYTE *byMobileGate, DWORD dwSize)
{
    for (int i = 0; i < m_listMobileGate.GetItemCount(); i++)
    {
        if (TRUE == m_listMobileGate.GetCheck(i))
        {
            byMobileGate[i] = TRUE;
        }
        else
        {
            byMobileGate[i] = FALSE;
        }
    }
}

void CDlgAlarmHostEnableCfg::SetMobileGateToWnd(BYTE *byMobileGate, DWORD dwSize)
{
    for (int i = 0; i < m_listMobileGate.GetItemCount(); i++)
    {
        if (1 == byMobileGate[i])
        {
            m_listMobileGate.SetCheck(i, TRUE);
        }
        else
        {
            m_listMobileGate.SetCheck(i, FALSE);
        }
    }
}

void CDlgAlarmHostEnableCfg::GetSirenFromWnd(BYTE *bySiren, DWORD dwSize)
{
    for (int i = 0; i < m_listSiren.GetItemCount(); i++)
    {
        if (TRUE == m_listSiren.GetCheck(i))
        {
            bySiren[i] = TRUE;
        }
        else
        {
            bySiren[i] = FALSE;
        }
    }
}

void CDlgAlarmHostEnableCfg::SetSirenToWnd(BYTE *bySiren, DWORD dwSize)
{
    for (int i = 0; i < m_listSiren.GetItemCount(); i++)
    {
        if (1 == bySiren[i])
        {
            m_listSiren.SetCheck(i, TRUE);
        }
        else
        {
            m_listSiren.SetCheck(i, FALSE);
        }
    }
}
