// DlgWhiteList.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWhiteList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgWhiteList dialog


DlgWhiteList::DlgWhiteList(CWnd* pParent /*=NULL*/)
	: CDialog(DlgWhiteList::IDD, pParent)
    , m_bChkDetectorConnectionReport(FALSE)
    , m_bChkDetectorPowerReport(FALSE)
    , m_bChkVideoAlarm(FALSE)
{
	//{{AFX_DATA_INIT(DlgWhiteList)
	m_bAlarmRestore = FALSE;
	m_bArm = FALSE;
	m_bBypass = FALSE;
	m_bBypassRestore = FALSE;
	m_bCancelReport = FALSE;
	m_bDisarm = FALSE;
	m_bEnable = FALSE;
	m_bHjack = FALSE;
	m_bSoftZone = FALSE;
	m_bSystemState = FALSE;
	m_bTest = FALSE;
	m_sPhone = _T("");
	m_defineTime = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = 0;
	m_lUserID = 0;
}


void DlgWhiteList::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(DlgWhiteList)
    DDX_Control(pDX, IDC_LIST_DISARM, m_listDisArm);
    DDX_Control(pDX, IDC_LIST_CLEAR_ALARM, m_listClearAlarm);
    DDX_Control(pDX, IDC_LIST_ARM, m_listArm);
    DDX_Control(pDX, IDC_LIST_ZONE_REPORT, m_listZoneReport);
    DDX_Control(pDX, IDC_COMB_INTERVAL_TIME, m_comIntervalTime);
    DDX_Control(pDX, IDC_COM_ALARM_PHONE_CFG, m_comAlarmPhoneCfg);
    DDX_Check(pDX, IDC_CHK_ALARM_RESTORE, m_bAlarmRestore);
    DDX_Check(pDX, IDC_CHK_ARM, m_bArm);
    DDX_Check(pDX, IDC_CHK_BYPASS, m_bBypass);
    DDX_Check(pDX, IDC_CHK_BYPASS_RESTORE, m_bBypassRestore);
    DDX_Check(pDX, IDC_CHK_CANCEL_REPORT, m_bCancelReport);
    DDX_Check(pDX, IDC_CHK_DISARM, m_bDisarm);
    DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
    DDX_Check(pDX, IDC_CHK_HJACK, m_bHjack);
    DDX_Check(pDX, IDC_CHK_SOFT_ZONE, m_bSoftZone);
    DDX_Check(pDX, IDC_CHK_SYSTEM_STATE, m_bSystemState);
    DDX_Check(pDX, IDC_CHK_TEST, m_bTest);
    DDX_Text(pDX, IDC_PHONE, m_sPhone);
    DDX_Text(pDX, IDC_DEFINE_TIME, m_defineTime);
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHK_DETECTOR_CONNECTION, m_bChkDetectorConnectionReport);
    DDX_Check(pDX, IDC_CHK_DETECTOR_POWER, m_bChkDetectorPowerReport);
    DDX_Check(pDX, IDC_CHECK_ALARM_VIDEO, m_bChkVideoAlarm);
}


BEGIN_MESSAGE_MAP(DlgWhiteList, CDialog)
	//{{AFX_MSG_MAP(DlgWhiteList)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMB_INTERVAL_TIME, OnSelchangeCombIntervalTime)
	ON_CBN_SELCHANGE(IDC_COM_ALARM_PHONE_CFG, OnSelchangeComAlarmPhoneCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgWhiteList message handlers


BOOL DlgWhiteList::OnInitDialog()
{
	CDialog::OnInitDialog();
	NET_DVR_ALARMHOST_ABILITY struAbility = {0};
	struAbility.dwSize = sizeof(NET_DVR_ALARMHOST_ABILITY);
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	if(!NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&struAbility, sizeof(NET_DVR_ALARMHOST_ABILITY)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceAbility FAILED");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceAbility SUCC");
	}

	CString csStr;
	int i=0;
	m_listZoneReport.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i=0; i<struAbility.wLocalAlarmInNum + struAbility.wExpandAlarmInNum; i++)
	{
		csStr.Format("Zone%d", i+1);
		m_listZoneReport.InsertItem(i, csStr);
	}
	m_listArm.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i=0; i<32; i++)
	{
		csStr.Format("system%d", i+1);
		m_listArm.InsertItem(i, csStr);
	}
	m_listDisArm.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i=0; i<32; i++)
	{
		csStr.Format("system%d", i+1);
		m_listDisArm.InsertItem(i, csStr);
	}
	m_listClearAlarm.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i=0; i<32; i++)
	{
		csStr.Format("system%d", i+1);
		m_listClearAlarm.InsertItem(i, csStr);
	}

	m_comAlarmPhoneCfg.SetCurSel(0);
	OnBtnGet();
	UpdateData(FALSE);
	return TRUE;
}

void DlgWhiteList::OnBtnSet() 
{ 
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int iSel = m_comAlarmPhoneCfg.GetCurSel() + 1;
	
	NET_DVR_ALARM_PHONECFG struAlarmPhoneCfg = {0};

	struAlarmPhoneCfg.dwSize = sizeof(struAlarmPhoneCfg);

	memset((char*)struAlarmPhoneCfg.byPhoneNumber,0,32);
	strncpy((char*)struAlarmPhoneCfg.byPhoneNumber, (LPSTR)(LPCTSTR)m_sPhone, 32);
	struAlarmPhoneCfg.byEnable = m_bEnable;
	
	struAlarmPhoneCfg.byIntervalTime = m_comIntervalTime.GetCurSel();
	if (6 == struAlarmPhoneCfg.byIntervalTime)
	{
		struAlarmPhoneCfg.wDefineIntervalTime = m_defineTime;
	}
	else
	{
		struAlarmPhoneCfg.wDefineIntervalTime = 0;
	}

	struAlarmPhoneCfg.dwNonZoneReport |= (m_bSoftZone << 0);
	struAlarmPhoneCfg.dwNonZoneReport |= (m_bSystemState << 1);
	struAlarmPhoneCfg.dwNonZoneReport |= (m_bCancelReport << 2);
	struAlarmPhoneCfg.dwNonZoneReport |= (m_bTest << 3);
	struAlarmPhoneCfg.dwNonZoneReport |= (m_bArm << 4);
	struAlarmPhoneCfg.dwNonZoneReport |= (m_bDisarm << 5);
	struAlarmPhoneCfg.dwNonZoneReport |= (m_bHjack << 6);
	struAlarmPhoneCfg.dwNonZoneReport |= (m_bAlarmRestore<<7);
	struAlarmPhoneCfg.dwNonZoneReport |= (m_bBypass << 8);
	struAlarmPhoneCfg.dwNonZoneReport |= (m_bBypassRestore << 9);
    struAlarmPhoneCfg.dwNonZoneReport |= (m_bChkDetectorConnectionReport << 10);
    struAlarmPhoneCfg.dwNonZoneReport |= (m_bChkDetectorPowerReport << 11);
    struAlarmPhoneCfg.dwNonZoneReport |= (m_bChkVideoAlarm << 12);
	int i = 0;
	for (i=0; i<m_listArm.GetItemCount(); i++)
	{
		struAlarmPhoneCfg.dwArmRight |= (m_listArm.GetCheck(i) << i);
	}
	for (i=0; i<m_listDisArm.GetItemCount(); i++)
	{
		struAlarmPhoneCfg.dwDisArmRight |= (m_listDisArm.GetCheck(i)<<i);
	}
	for (i=0; i<m_listClearAlarm.GetItemCount(); i++)
	{
		struAlarmPhoneCfg.dwClearAlarmRight |= (m_listClearAlarm.GetCheck(i)<<i);
	}
	//	m_struWhitelistAlarm.struWhiteList[sel].byAlarmOnRight = m_comAlarmType.GetCurSel();
	for (i=0; i<m_listZoneReport.GetItemCount(); i++)
	{
		struAlarmPhoneCfg.byZoneReport[i] = m_listZoneReport.GetCheck(i);
	}

	char szLan[128] = {0};
	
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_WHITELIST_ALARM, iSel, &struAlarmPhoneCfg, sizeof(struAlarmPhoneCfg)))
	{
		g_StringLanType(szLan, "ÉèÖÃ°×Ãûµ¥ÅäÖÃÊ§°Ü" , "NET_DVR_SET_WHITELIST_ALARM FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WHITELIST_ALARM FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WHITELIST_ALARM SUCC");
	}
}

void DlgWhiteList::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_comAlarmPhoneCfg.GetCurSel() + 1;
	
	NET_DVR_ALARM_PHONECFG struAlarmPhoneCfg = {0};

	DWORD returned = 0;
	char szLan[128] = {0};
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_WHITELIST_ALARM, iSel, &struAlarmPhoneCfg, sizeof(struAlarmPhoneCfg), &returned))
	{
		g_StringLanType(szLan, "»ñÈ¡°×Ãûµ¥ÅäÖÃÊ§°Ü" , "NET_DVR_GET_WHITELIST_ALARM FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WHITELIST_ALARM FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WHITELIST_ALARM SUCC");
	}

	m_comIntervalTime.SetCurSel(struAlarmPhoneCfg.byIntervalTime);
	if(6 == struAlarmPhoneCfg.byIntervalTime)
	{
		m_defineTime = struAlarmPhoneCfg.wDefineIntervalTime;
		GetDlgItem(IDC_DEFINE_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DEFINE_TIME)->EnableWindow(FALSE);
	}

	m_bEnable = struAlarmPhoneCfg.byEnable;
	//m_sPhone.Format("%s",m_struWhitelistAlarm.struWhiteList[sel].byWhiteList,32);
	char sPhone[33] = {0};
	strncpy(sPhone, (char*)struAlarmPhoneCfg.byPhoneNumber, MAX_PHONE_NUM);
	m_sPhone = 	sPhone;
	
	//m_comAlarmType.SetCurSel((int)m_struWhitelistAlarm.struWhiteList[sel].byAlarmOnRight);
	//m_bClearAlarmPermission = (m_struWhitelistAlarm.struWhiteList[sel].byAlarmOnRight >> 2)&0x01;
	int i = 0;
	for (i=0; i<m_listZoneReport.GetItemCount(); i++)
	{
		m_listZoneReport.SetCheck(i, (BOOL)struAlarmPhoneCfg.byZoneReport[i]);
	}
	for (i=0; i<m_listArm.GetItemCount(); i++)
	{
		m_listArm.SetCheck(i, (BOOL)((struAlarmPhoneCfg.dwArmRight >> i)&0x01));
	}
	for (i=0; i<m_listDisArm.GetItemCount(); i++)
	{
		m_listDisArm.SetCheck(i, (BOOL)((struAlarmPhoneCfg.dwDisArmRight >> i)&0x01));
	}
	for (i=0; i<m_listClearAlarm.GetItemCount(); i++)
	{
		m_listClearAlarm.SetCheck(i, (BOOL)((struAlarmPhoneCfg.dwClearAlarmRight >> i)&0x01));
	}
	m_bSoftZone = (struAlarmPhoneCfg.dwNonZoneReport >> 0)&0x01;
	m_bSystemState = (struAlarmPhoneCfg.dwNonZoneReport >> 1)&0x01;
	m_bCancelReport = (struAlarmPhoneCfg.dwNonZoneReport >> 2)&0x01;
	m_bTest = (struAlarmPhoneCfg.dwNonZoneReport >> 3)&0x01;
	m_bArm = (struAlarmPhoneCfg.dwNonZoneReport >> 4)&0x01;
	m_bDisarm = (struAlarmPhoneCfg.dwNonZoneReport >> 5)&0x01;
	m_bHjack = (struAlarmPhoneCfg.dwNonZoneReport >> 6)&0x01;
	m_bAlarmRestore = (struAlarmPhoneCfg.dwNonZoneReport >> 7)&0x01;
	m_bBypass = (struAlarmPhoneCfg.dwNonZoneReport >> 8)&0x01;
	m_bBypassRestore = (struAlarmPhoneCfg.dwNonZoneReport >> 9)&0x01;
    m_bChkDetectorConnectionReport = (struAlarmPhoneCfg.dwNonZoneReport >> 10) & 0x01;
    m_bChkDetectorPowerReport = (struAlarmPhoneCfg.dwNonZoneReport >> 11) & 0x01;
    m_bChkVideoAlarm = (struAlarmPhoneCfg.dwNonZoneReport >> 12) & 0x01;
	UpdateData(FALSE);
}


void DlgWhiteList::OnSelchangeCombIntervalTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_comIntervalTime.GetCurSel() == 6)
	{
		GetDlgItem(IDC_DEFINE_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DEFINE_TIME)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void DlgWhiteList::OnSelchangeComAlarmPhoneCfg() 
{
// 	// TODO: Add your control notification handler code here
// 	UpdateData(TRUE);
// 	int sel = m_comAlarmPhoneCfg.GetCurSel();
// 	m_bEnable = m_struWhitelistAlarm.struWhiteList[sel].byEnable;
// 	//m_sPhone.Format("%s",m_struWhitelistAlarm.struWhiteList[sel].byWhiteList,32);
// 	char sPhone[33] = {0};
// 	strncpy(sPhone, (char*)m_struWhitelistAlarm.struWhiteList[sel].byWhiteList, MAX_PHONE_NUM);
// 	m_sPhone = 	sPhone;
// 
// 	//m_comAlarmType.SetCurSel((int)m_struWhitelistAlarm.struWhiteList[sel].byAlarmOnRight);
// 	//m_bClearAlarmPermission = (m_struWhitelistAlarm.struWhiteList[sel].byAlarmOnRight >> 2)&0x01;
// 	for (int i=0; i<m_listZoneReport.GetItemCount(); i++)
// 	{
// 		m_listZoneReport.SetCheck(i, (BOOL)m_struWhitelistAlarm.struWhiteList[sel].byZoneReport[i]);
// 	}
// 	for (i=0; i<m_listArm.GetItemCount(); i++)
// 	{
// 		m_listArm.SetCheck(i, (BOOL)((m_struWhitelistAlarm.struWhiteList[sel].dwArmRight >> i)&0x01));
// 	}
// 	for (i=0; i<m_listDisArm.GetItemCount(); i++)
// 	{
// 		m_listDisArm.SetCheck(i, (BOOL)((m_struWhitelistAlarm.struWhiteList[sel].dwDisArmRight >> i)&0x01));
// 	}
// 	for (i=0; i<m_listClearAlarm.GetItemCount(); i++)
// 	{
// 		m_listClearAlarm.SetCheck(i, (BOOL)((m_struWhitelistAlarm.struWhiteList[sel].dwClearAlarmRight >> i)&0x01));
// 	}
// 	m_bSoftZone = (m_struWhitelistAlarm.struWhiteList[sel].dwNonZoneReport >> 0)&0x01;
// 	m_bSystemState = (m_struWhitelistAlarm.struWhiteList[sel].dwNonZoneReport >> 1)&0x01;
// 	m_bCancelReport = (m_struWhitelistAlarm.struWhiteList[sel].dwNonZoneReport >> 2)&0x01;
// 	m_bTest = (m_struWhitelistAlarm.struWhiteList[sel].dwNonZoneReport >> 3)&0x01;
// 	m_bArm = (m_struWhitelistAlarm.struWhiteList[sel].dwNonZoneReport >> 4)&0x01;
// 	m_bDisarm = (m_struWhitelistAlarm.struWhiteList[sel].dwNonZoneReport >> 5)&0x01;
// 	m_bHjack = (m_struWhitelistAlarm.struWhiteList[sel].dwNonZoneReport >> 6)&0x01;
// 	m_bAlarmRestore = (m_struWhitelistAlarm.struWhiteList[sel].dwNonZoneReport >> 7)&0x01;
// 	m_bBypass = (m_struWhitelistAlarm.struWhiteList[sel].dwNonZoneReport >> 8)&0x01;
// 	m_bBypassRestore = (m_struWhitelistAlarm.struWhiteList[sel].dwNonZoneReport >> 9)&0x01;
// 	UpdateData(FALSE);
}
