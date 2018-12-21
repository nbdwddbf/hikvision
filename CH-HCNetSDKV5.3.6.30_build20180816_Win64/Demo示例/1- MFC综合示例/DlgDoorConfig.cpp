// DlgDoorConfig.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDoorConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDoorConfig dialog


CDlgDoorConfig::CDlgDoorConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDoorConfig::IDD, pParent)
    , m_bUserLocalController(FALSE)
    , m_iLocalControllerID(0)
    , m_iLocalControllerDoorNumber(0)
    , m_bLockInputCheck(FALSE)
    , m_bOpenButton(FALSE)
{
	//{{AFX_DATA_INIT(CDlgDoorConfig)
	m_dwDoorChan = 1;
	m_csDoorName = _T("");
	m_csStressPasswd = _T("");
	m_csSuperPasswd = _T("");
    m_csUnlockPassword = _T("");
	m_BDoorLock = FALSE;
	m_BLeaderCard = FALSE;
	m_csDOpenDuration = _T("");
	m_csLOpenDuration = _T("");
	m_csOpenDuration = _T("");
	m_csAlarmTimeout = _T("");
    m_iLadderControlDelayTime = 0;
	//}}AFX_DATA_INIT
}


void CDlgDoorConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDoorConfig)
	DDX_Control(pDX, IDC_COM_ACDC_OPENBUTTONTYPE, m_cmbOpenButType);
	DDX_Control(pDX, IDC_COM_ACDC_MAGNETICTYPE, m_cmbMagneticType);
	DDX_Control(pDX, IDC_SLIDER_ACDC_LEADEROPENDURATION, m_SlidLOpenDuration);
	DDX_Control(pDX, IDC_SLIDER_ACDC_DISABLEDOPENDURATION, m_SlidDOpenDuration);
	DDX_Control(pDX, IDC_SLIDER_ACDC_ALARMTIMEOUT, m_SlidAlarmTimeout);
	DDX_Control(pDX, IDC_SLIDER_ACDC_OPENDURATION, m_SlidOpenDuration);
	DDX_Text(pDX, IDC_EDT_ACDC_DOORCHANNEL, m_dwDoorChan);
	DDX_Text(pDX, IDC_EDT_ACDC_DOORNAME, m_csDoorName);
	DDX_Text(pDX, IDC_EDT_ACDC_STRESSPASSWORD, m_csStressPasswd);
	DDX_Text(pDX, IDC_EDT_ACDC_SUPERPASSWORD, m_csSuperPasswd);
    DDX_Text(pDX, IDC_EDT_ACDC_UNLOCKPASSWORD, m_csUnlockPassword);
	DDX_Check(pDX, IDC_CHK_ACDC_DOORLOCK, m_BDoorLock);
	DDX_Check(pDX, IDC_CHK_ACDC_LEADERCARD, m_BLeaderCard);
	DDX_Text(pDX, IDC_STATIC_ACDC_DOPENDURATION, m_csDOpenDuration);
	DDX_Text(pDX, IDC_STATIC_ACDC_LOPENDURATION, m_csLOpenDuration);
	DDX_Text(pDX, IDC_STATIC_ACDC_OPENDURATION, m_csOpenDuration);
	DDX_Text(pDX, IDC_STATIC_ADSC_ALARMTIMEOUT, m_csAlarmTimeout);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COM_ACDC_LEADERCARDMODE, m_cmbLeaderCardMode);
    DDX_Check(pDX, IDC_CHK_ACDC_USELOCALCONTROLLER, m_bUserLocalController);
    DDX_Text(pDX, IDC_EDT_ACDC_LOCALCONTROLLERID, m_iLocalControllerID);
    DDX_Text(pDX, IDC_EDT_ACDC_LOCALCONTROLLER_DOORNUMBER, m_iLocalControllerDoorNumber);
    DDX_Control(pDX, IDC_COM_ACDC_LOCALCONTROLLERSTATUS, m_cmbLocalControllerStatus);
    DDX_Check(pDX, IDC_CHK_ACDC_LOCKINPUTCHECK, m_bLockInputCheck);
    DDX_Control(pDX, IDC_COM_ACDC_LOCK_INPUT_TYPE, m_cmbLockInputType);
    DDX_Control(pDX, IDC_COM_ACDC_DOOR_TERMINAL_MODE, m_cmbDoorTerminalMode);
    DDX_Check(pDX, IDC_CHK_ACDC_OPEN_BUTTON, m_bOpenButton);
    DDX_Text(pDX, IDC_EDIT_LADDER_CONTROL_DELAY_TIME, m_iLadderControlDelayTime);
}


BEGIN_MESSAGE_MAP(CDlgDoorConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgDoorConfig)
	ON_BN_CLICKED(IDC_BUT_ACDC_GET, OnButGet)
	ON_BN_CLICKED(IDC_BUT_ACDC_SET, OnButSet)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ACDC_OPENDURATION, OnCdrawOpenduration)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ACDC_DISABLEDOPENDURATION, OnCdrawDOpenduration)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ACDC_LEADEROPENDURATION, OnCdrawLOpenduration)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ACDC_ALARMTIMEOUT, OnCdrawAlarmtimeout)
	//}}AFX_MSG_MAP
    ON_CBN_SELCHANGE(IDC_COM_ACDC_LEADERCARDMODE, &CDlgDoorConfig::OnCbnSelchangeComAcdcLeadercardmode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDoorConfig message handlers



BOOL CDlgDoorConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
    char szLan[64] = { 0 };

    m_lDeviceID = g_pMainDlg->GetCurDeviceIndex(); 
    m_lUserID = g_struDeviceInfo[m_lDeviceID].lLoginID; 
	// TODO: Add extra initialization here
	m_SlidOpenDuration.SetRange(1, 255); 
    m_SlidDOpenDuration.SetRange(1, 255); 
    m_SlidLOpenDuration.SetRange(1, 1440);
    m_SlidAlarmTimeout.SetRange(0, 255);
    m_SlidOpenDuration.SetPos(1); 
    m_SlidDOpenDuration.SetPos(1); 
    m_SlidLOpenDuration.SetPos(1); 
    m_SlidAlarmTimeout.SetPos(0);
    m_csOpenDuration = " "; 
    m_csDOpenDuration = " "; 
    m_csLOpenDuration = " "; 
    m_csAlarmTimeout = " "; 
    m_cmbLeaderCardMode.SetCurSel(0);
    GetDlgItem(IDC_CHK_ACDC_LEADERCARD)->EnableWindow(FALSE);
    m_iLocalControllerID = 0;
    m_iLocalControllerDoorNumber = 0;
    m_cmbLocalControllerStatus.ResetContent();
    g_StringLanType(szLan, "离线", "offline");
    m_cmbLocalControllerStatus.InsertString(0, szLan);
    g_StringLanType(szLan, "网络在线", "online");
    m_cmbLocalControllerStatus.InsertString(1, szLan);
    g_StringLanType(szLan, "环路1上的RS485串口1", "loop 1 of RS485 serial port 1");
    m_cmbLocalControllerStatus.InsertString(2, szLan);
    g_StringLanType(szLan, "环路1上的RS485串口2", "loop 1 of RS485 serial port 2");
    m_cmbLocalControllerStatus.InsertString(3, szLan);
    g_StringLanType(szLan, "环路2上的RS485串口1", "loop 2 of RS485 serial port 1");
    m_cmbLocalControllerStatus.InsertString(4, szLan);
    g_StringLanType(szLan, "环路2上的RS485串口2", "loop 2 of RS485 serial port 2");
    m_cmbLocalControllerStatus.InsertString(5, szLan);
    g_StringLanType(szLan, "环路3上的RS485串口1", "loop 3 of RS485 serial port 1");
    m_cmbLocalControllerStatus.InsertString(6, szLan);
    g_StringLanType(szLan, "环路3上的RS485串口2", "loop 3 of RS485 serial port 2");
    m_cmbLocalControllerStatus.InsertString(7, szLan);
    g_StringLanType(szLan, "环路4上的RS485串口1", "loop 4 of RS485 serial port 1");
    m_cmbLocalControllerStatus.InsertString(8, szLan);
    g_StringLanType(szLan, "环路4上的RS485串口2", "loop 4 of RS485 serial port 2");
    m_cmbLocalControllerStatus.InsertString(9, szLan);
    m_cmbLocalControllerStatus.SetCurSel(0);

    m_cmbLockInputType.ResetContent();
    g_StringLanType(szLan, "常闭", "normally close");
    m_cmbLockInputType.InsertString(0, szLan);
    g_StringLanType(szLan, "常开", "normally open");
    m_cmbLockInputType.InsertString(1, szLan);
    m_cmbLockInputType.SetCurSel(0);

    m_cmbDoorTerminalMode.ResetContent();
    g_StringLanType(szLan, "防剪防短", "prevent cut short");
    m_cmbDoorTerminalMode.InsertString(0, szLan);
    g_StringLanType(szLan, "普通", "normally");
    m_cmbDoorTerminalMode.InsertString(1, szLan);
    m_cmbDoorTerminalMode.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgDoorConfig::OnButGet() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    DWORD dwReturned; 
    NET_DVR_DOOR_CFG struDoorCfg = {0}; 
    char szLan[128]; 
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DOOR_CFG, m_dwDoorChan, &struDoorCfg, sizeof(struDoorCfg), &dwReturned) )
    {
        sprintf(szLan, "NET_DVR_GET_DOOR_CFG, Error code %d", NET_DVR_GetLastError());
        MessageBox(szLan); 
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_DOOR_CFG"); 
        return ; 
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_DOOR_CFG"); 
		char szName[DOOR_NAME_LEN+1] = {0}; 
		memcpy(szName, struDoorCfg.byDoorName,  DOOR_NAME_LEN);  
        m_csDoorName.Format("%s", szName) ;
        m_BDoorLock = struDoorCfg.byEnableDoorLock; 
        m_BLeaderCard = struDoorCfg.byEnableLeaderCard; 
        m_cmbLeaderCardMode.SetCurSel(struDoorCfg.byLeaderCardMode);

        m_cmbMagneticType.SetCurSel(struDoorCfg.byMagneticType); 
        m_cmbOpenButType.SetCurSel(struDoorCfg.byOpenButtonType); 
        m_SlidOpenDuration.SetPos(struDoorCfg.byOpenDuration); 
        m_csOpenDuration.Format("%d (s)", struDoorCfg.byOpenDuration); 
        m_SlidDOpenDuration.SetPos(struDoorCfg.byDisabledOpenDuration); 
        m_csDOpenDuration.Format("%d (s)", struDoorCfg.byDisabledOpenDuration); 
        m_SlidLOpenDuration.SetPos(struDoorCfg.dwLeaderCardOpenDuration); 
        m_csLOpenDuration.Format("%d (min)", struDoorCfg.dwLeaderCardOpenDuration);
        m_SlidAlarmTimeout.SetPos(struDoorCfg.byMagneticAlarmTimeout); 
        m_csAlarmTimeout.Format("%d (s)", struDoorCfg.byMagneticAlarmTimeout); 
        char szPassWord[STRESS_PASSWORD_LEN+1];
        szPassWord[STRESS_PASSWORD_LEN] = 0; 
        memcpy(szPassWord, struDoorCfg.byStressPassword, STRESS_PASSWORD_LEN); 
        m_csStressPasswd.Format("%s", szPassWord);

        memset(szPassWord, 0 ,sizeof(szPassWord));
        szPassWord[STRESS_PASSWORD_LEN] = '\0';
        memcpy(szPassWord, struDoorCfg.bySuperPassword, SUPER_PASSWORD_LEN);
        m_csSuperPasswd.Format("%s", szPassWord);

        memset(szPassWord, 0 ,sizeof(szPassWord));
        szPassWord[STRESS_PASSWORD_LEN] = '\0';
        memcpy(szPassWord, struDoorCfg.byUnlockPassword, UNLOCK_PASSWORD_LEN);
        m_csUnlockPassword.Format("%s", szPassWord);

        m_bUserLocalController = struDoorCfg.byUseLocalController;
        m_iLocalControllerID = struDoorCfg.wLocalControllerID;
        m_iLocalControllerDoorNumber = struDoorCfg.wLocalControllerDoorNumber;
        m_cmbLocalControllerStatus.SetCurSel(struDoorCfg.wLocalControllerStatus);

        m_bLockInputCheck = struDoorCfg.byLockInputCheck;
        m_cmbLockInputType.SetCurSel(struDoorCfg.byLockInputType);
        m_cmbDoorTerminalMode.SetCurSel(struDoorCfg.byDoorTerminalMode);
        if (0 == struDoorCfg.byOpenButton)
        {
            m_bOpenButton = TRUE;
        }
        else
        {
            m_bOpenButton = FALSE;
        }
        m_iLadderControlDelayTime = struDoorCfg.byLadderControlDelayTime;
        UpdateData(FALSE); 
    }
}

void CDlgDoorConfig::OnButSet() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_DOOR_CFG struDoorCfg = {0}; 
    struDoorCfg.dwSize = sizeof(struDoorCfg);
	strncpy((char *)struDoorCfg.byDoorName, (LPCTSTR)m_csDoorName, DOOR_NAME_LEN); 
    struDoorCfg.byMagneticType = m_cmbMagneticType.GetCurSel();
    struDoorCfg.byOpenButtonType = m_cmbOpenButType.GetCurSel(); 
    struDoorCfg.byEnableDoorLock = m_BDoorLock;
    struDoorCfg.byEnableLeaderCard = m_BLeaderCard;
    struDoorCfg.byLeaderCardMode = m_cmbLeaderCardMode.GetCurSel();

    struDoorCfg.byOpenDuration = m_SlidOpenDuration.GetPos(); 
    struDoorCfg.byDisabledOpenDuration = m_SlidDOpenDuration.GetPos(); 
    struDoorCfg.dwLeaderCardOpenDuration = m_SlidLOpenDuration.GetPos(); 
    struDoorCfg.byMagneticAlarmTimeout = m_SlidAlarmTimeout.GetPos(); 

    strncpy((char *)struDoorCfg.byStressPassword, (LPCTSTR)m_csStressPasswd, STRESS_PASSWORD_LEN);
    strncpy((char *)struDoorCfg.bySuperPassword, (LPCTSTR)m_csSuperPasswd, SUPER_PASSWORD_LEN);
    strncpy((char *)struDoorCfg.byUnlockPassword, (LPCTSTR)m_csUnlockPassword, UNLOCK_PASSWORD_LEN);

    struDoorCfg.byUseLocalController = m_bUserLocalController;
    struDoorCfg.wLocalControllerID = m_iLocalControllerID;
    struDoorCfg.wLocalControllerDoorNumber = m_iLocalControllerDoorNumber;
    struDoorCfg.wLocalControllerStatus = m_cmbLocalControllerStatus.GetCurSel();

    struDoorCfg.byLockInputCheck = m_bLockInputCheck;

    struDoorCfg.byLockInputType = m_cmbLockInputType.GetCurSel();
    struDoorCfg.byDoorTerminalMode = m_cmbDoorTerminalMode.GetCurSel();
    if (m_bOpenButton)
    {
        struDoorCfg.byOpenButton = 0;
    }
    else
    {
        struDoorCfg.byOpenButton = 1;
    }
    struDoorCfg.byLadderControlDelayTime = (BYTE)m_iLadderControlDelayTime;

    char szLan[128];
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_DOOR_CFG, m_dwDoorChan, &struDoorCfg, sizeof(struDoorCfg)))
    {
        sprintf(szLan, "NET_DVR_SET_DOOR_CFG, Error Code %d", NET_DVR_GetLastError());
        MessageBox(szLan); 
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_SET_DOOR_CFG");
        return ; 
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_DOOR_CFG");
	}
}

void CDlgDoorConfig::OnCdrawOpenduration(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    m_csOpenDuration.Format("%d (s)", m_SlidOpenDuration.GetPos()); 
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgDoorConfig::OnCdrawDOpenduration(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    m_csDOpenDuration.Format("%d (s)", m_SlidDOpenDuration.GetPos()); 
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgDoorConfig::OnCdrawLOpenduration(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    m_csLOpenDuration.Format("%d (min)", m_SlidLOpenDuration.GetPos()); 
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgDoorConfig::OnCdrawAlarmtimeout(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    m_csAlarmTimeout.Format("%d (s)", m_SlidAlarmTimeout.GetPos()); 
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgDoorConfig::OnCbnSelchangeComAcdcLeadercardmode()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (1 == m_cmbLeaderCardMode.GetCurSel())
    {
        GetDlgItem(IDC_CHK_ACDC_LEADERCARD)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_CHK_ACDC_LEADERCARD)->EnableWindow(FALSE);
    }
    UpdateData(FALSE);
}
