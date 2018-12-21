// DlgAlarmNetUser.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmNetUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmNetUser dialog


CDlgAlarmNetUser::CDlgAlarmNetUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmNetUser::IDD, pParent)
	, m_lChanNum(-1)
	, m_iCurChanIndex(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmNetUser)
	m_bAlarmOff = FALSE;
	m_bAlarmOn = FALSE;
	m_bBypass = FALSE;
	m_bDefault = FALSE;
	m_bGetParam = FALSE;
	m_bLog = FALSE;
	m_bRestartShuntdown = FALSE;
	m_bSetParam = FALSE;
	m_bSiren = FALSE;
	m_bUpgrade = FALSE;
	m_csPassword = _T("");
    m_csOriginalPassword = _T("");
	m_csUserName = _T("");
	m_csUserIP = _T("");
	m_csMacAddr1 = _T("");
	m_csMacAddr2 = _T("");
	m_csMacAddr3 = _T("");
	m_csMacAddr4 = _T("");
	m_csMacAddr5 = _T("");
	m_csMacAddr6 = _T("");
	m_bAlarmoutCtrl = FALSE;
	m_bAudioTalk = FALSE;
	m_bDiskCfg = FALSE;
	m_bFormatDisk = FALSE;
	m_bGatewayCtrl = FALSE;
	m_bSensorCtrl = FALSE;
	m_bSerialCtrl = FALSE;
	m_bLocalCtrl = FALSE;
	m_bPtzControl = FALSE;
	//}}AFX_DATA_INIT
    m_lLoginID = -1;
    m_iDevIndex = -1;
    m_dwNetUserNum = -1;
    m_lStartChannel = -1;
    m_bSuperUserLogin = FALSE;
    m_bSetUserParams = FALSE;
    m_bGetUserParams = FALSE;
    m_iSelNetRightType = 0;
    
    m_lUserIndex = -1;
    memset(&m_struDeviceUser, 0, sizeof(m_struDeviceUser));

    m_pbRemoteChan = new BOOL[MAX_CHANNUM_V40];
    if (m_pbRemoteChan != NULL)
    {
        memset(m_pbRemoteChan, 0, sizeof(BOOL)*MAX_CHANNUM_V40);
    }
}


/*********************************************************
Function:	~CDlgAlarmNetUser
Desc:		destructor
Input:
Output:
Return:
**********************************************************/
CDlgAlarmNetUser::~CDlgAlarmNetUser()
{
    if (m_pbRemoteChan != NULL)
    {
        delete[] m_pbRemoteChan;
        m_pbRemoteChan = NULL;
    }
}

void CDlgAlarmNetUser::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAlarmNetUser)
    DDX_Control(pDX, IDC_LIST_VIDEO_CHAN, m_listChan);
    DDX_Control(pDX, IDC_COMBO_RIGHT_TYPE, m_cmRightType);
    DDX_Control(pDX, IDC_COMBO_USERTYPE, m_comboUserType);
    DDX_Control(pDX, IDC_COMBO_USER_INDEX, m_comboUserIndex);
    DDX_Check(pDX, IDC_CHK_ALARM_OFF, m_bAlarmOff);
    DDX_Check(pDX, IDC_CHK_ALARM_ON, m_bAlarmOn);
    DDX_Check(pDX, IDC_CHK_BYPASS, m_bBypass);
    DDX_Check(pDX, IDC_CHK_DEFAULT, m_bDefault);
    DDX_Check(pDX, IDC_CHK_GET_PARAM, m_bGetParam);
    DDX_Check(pDX, IDC_CHK_LOG, m_bLog);
    DDX_Check(pDX, IDC_CHK_RESTART_SHUTDOWN, m_bRestartShuntdown);
    DDX_Check(pDX, IDC_CHK_SET_PARAM, m_bSetParam);
    DDX_Check(pDX, IDC_CHK_SIREN, m_bSiren);
    DDX_Check(pDX, IDC_CHK_UPGRADE, m_bUpgrade);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
    DDV_MaxChars(pDX, m_csPassword, 16);
    DDX_Text(pDX, IDC_EDIT_PASSWORD_ORIGINAL, m_csOriginalPassword);
    DDV_MaxChars(pDX, m_csOriginalPassword, 16);
    DDX_Text(pDX, IDC_EDIT_USRE_NAME, m_csUserName);
    DDV_MaxChars(pDX, m_csUserName, 32);
    DDX_Text(pDX, IDC_EDIT_USER_IP, m_csUserIP);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR1, m_csMacAddr1);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR2, m_csMacAddr2);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR3, m_csMacAddr3);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR4, m_csMacAddr4);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR5, m_csMacAddr5);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR6, m_csMacAddr6);
    DDX_Check(pDX, IDC_CHK_ALARMOUT_CTRL, m_bAlarmoutCtrl);
    DDX_Check(pDX, IDC_CHK_AUDIO_TALK, m_bAudioTalk);
    DDX_Check(pDX, IDC_CHK_DISK_CFG, m_bDiskCfg);
    DDX_Check(pDX, IDC_CHK_FORMAT_DISK, m_bFormatDisk);
    DDX_Check(pDX, IDC_CHK_GATEWAY_CTRL, m_bGatewayCtrl);
    DDX_Check(pDX, IDC_CHK_SENSOR_CTRL, m_bSensorCtrl);
    DDX_Check(pDX, IDC_CHK_SERIAL_CTRL, m_bSerialCtrl);
    DDX_Check(pDX, IDC_CHK_LOCAL_CTRL, m_bLocalCtrl);
    DDX_Check(pDX, IDC_CHECK_PTZ_CTRL, m_bPtzControl);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_TREE_REMOTE_CHAN, m_treeRemoteChan);
}


BEGIN_MESSAGE_MAP(CDlgAlarmNetUser, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmNetUser)
	ON_CBN_SELCHANGE(IDC_COMBO_USER_INDEX, OnSelchangeComboUserIndex)
	ON_BN_CLICKED(IDC_BTN_SET_NET_USER, OnBtnSetNetUser)
	ON_CBN_SELCHANGE(IDC_COMBO_USERTYPE, OnSelchangeComboUsertype)
	ON_CBN_SELCHANGE(IDC_COMBO_RIGHT_TYPE, OnSelchangeComboRightType)
    ON_NOTIFY(NM_CLICK, IDC_TREE_REMOTE_CHAN, OnClickTreeRemoteChan)
    ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmNetUser message handlers

BOOL CDlgAlarmNetUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	memset(&m_struDeviceUser, 0, sizeof(m_struDeviceUser));

    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex == -1)
    {
        return FALSE;
    }
    if (g_struDeviceInfo[iDeviceIndex].lLoginID < 0)
    {
        m_lChanNum = 0;
        return FALSE;
    }

    //	if (m_iDeviceIndex == iDeviceIndex)
    //	{
    //		return TRUE;
    //	}
    //	else
    {
        m_iDevIndex = iDeviceIndex;
        m_lLoginID = g_struDeviceInfo[m_iDevIndex].lLoginID;
        m_lStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;
        // 总通道数 = 模拟通道 + 数字通道
        m_lChanNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum + g_struDeviceInfo[m_iDevIndex].iIPChanNum;
        if (strcmp(g_struDeviceInfo[m_iDevIndex].chLoginUserName, "admin") == 0)
        {
            m_bSuperUserLogin = TRUE;
        }
        else
        {
            m_bSuperUserLogin = FALSE;
        }
    }

    if (m_lLoginID < 0)
    {
        return FALSE;
    }
    DWORD dwReturned;
    m_bSetUserParams = FALSE;
    m_bGetUserParams = FALSE;

//     if (!GetDeviceUser(m_struDeviceUser))
//     {
//     }
    if (NET_DVR_GetAlarmDeviceUser(m_lLoginID, 1, &m_struDeviceUser))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetAlarmDeviceUser");
        //SetDeviceUserToWnd(struDeviceUser);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetAlarmDeviceUser");
        char szLan[128] = { 0 };
        g_StringLanType(szLan, "获取用户参数失败！", "Get User Parameter failed");
        AfxMessageBox(szLan);
        return FALSE;
    }

    m_bGetUserParams = TRUE;

	InitWnd();
	
    m_comboUserIndex.SetCurSel(0);
    OnSelchangeComboUserIndex();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgAlarmNetUser::GetDeviceUser(NET_DVR_ALARM_DEVICE_USER &struDeviceUser)
{
//     (SetAlarmDeviceUser)(HPR_INT32 lUserID, LONG lUserIndex, NET_DVR_ALARM_DEVICE_USER* lpDeviceUser);
//     
//     (GetAlarmDeviceUser)(HPR_INT32 lUserID, LONG lUserIndex, NET_DVR_ALARM_DEVICE_USER* lpDeviceUser);
    if (NET_DVR_GetAlarmDeviceUser(m_lLoginID, m_lUserIndex, &struDeviceUser))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetAlarmDeviceUser");
		SetDeviceUserToWnd(struDeviceUser);
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetAlarmDeviceUser");
        return FALSE;
    }
}

BOOL CDlgAlarmNetUser::SetDeviceUser(NET_DVR_ALARM_DEVICE_USER &struDeviceUser)
{
    if (NET_DVR_SetAlarmDeviceUser(m_lLoginID, m_lUserIndex, &struDeviceUser))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetAlarmDeviceUser");
        return TRUE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetAlarmDeviceUser");
        return FALSE;
    }
}

void CDlgAlarmNetUser::InitWnd()
{
    InitUserIndexCombo();
    InitUserTypeCombo();
	InitRightTypeCombo();
	InitRightList();
}

void CDlgAlarmNetUser::InitRightList()
{
	char szLan[128] = {0};
	//char szTemp[128] = {0};
	m_listChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (int i=0; i<m_lChanNum; i++)
	{
		g_StringLanType(szLan, "通道", "Chan");
		sprintf(szLan, "%s%d", szLan, i+1);
		m_listChan.InsertItem(i, szLan);
	}
	UpdateData(FALSE);
}

void CDlgAlarmNetUser::InitRightTypeCombo()
{
	char szLan[128] = {0};
	m_cmRightType.ResetContent();
	g_StringLanType(szLan, "远程预览", "Remote Preview");
	m_cmRightType.AddString(szLan);
	g_StringLanType(szLan, "远程手动录像", "Manual Record");
	m_cmRightType.AddString(szLan);
	g_StringLanType(szLan, "远程回放", "Remote PlayBack");
	m_cmRightType.AddString(szLan);
	g_StringLanType(szLan, "PTZ控制", "PTZ");
	m_cmRightType.AddString(szLan);
	UpdateData(FALSE);
}

void CDlgAlarmNetUser::InitUserIndexCombo()
{
    char szLan[128] = {0};
    m_comboUserIndex.ResetContent();
    for (int i = 0; i < m_dwNetUserNum; i ++)
    {
        sprintf(szLan, "User %d", i + 1);
        m_comboUserIndex.AddString(szLan);
    }
}

void CDlgAlarmNetUser::InitUserTypeCombo()
{
    char szLan[124] = {0};
    m_comboUserType.ResetContent();
	g_StringLanType(szLan, "普通用户", "Normal user");
    m_comboUserType.AddString(szLan);
	g_StringLanType(szLan, "管理员", "administrator");
    m_comboUserType.AddString(szLan);
}


void CDlgAlarmNetUser::GetDeviceUserFromWnd(NET_DVR_ALARM_DEVICE_USER &struDeviceUser)
{
    struDeviceUser.dwSize = sizeof(NET_DVR_ALARM_DEVICE_USER);
    strncpy((char*)struDeviceUser.sUserName, m_csUserName.GetBuffer(0), sizeof(struDeviceUser.sUserName));
    strncpy((char*)struDeviceUser.sPassword, m_csPassword.GetBuffer(0), sizeof(struDeviceUser.sPassword));
    strncpy((char*)struDeviceUser.sOriginalPassword, m_csOriginalPassword.GetBuffer(0), sizeof(struDeviceUser.sOriginalPassword));
    struDeviceUser.byUserType = m_comboUserType.GetCurSel();
    strncpy(struDeviceUser.struUserIP.sIpV4, m_csUserIP.GetBuffer(0), sizeof(struDeviceUser.struUserIP.sIpV4));
    int nVal = 0;
    sscanf(m_csMacAddr1, "%02x", &nVal);
    struDeviceUser.byMACAddr[0] = (BYTE)nVal;
    sscanf(m_csMacAddr2, "%02x", &nVal);
    struDeviceUser.byMACAddr[1] = (BYTE)nVal;
    sscanf(m_csMacAddr3, "%02x", &nVal);
    struDeviceUser.byMACAddr[2] = (BYTE)nVal;
    sscanf(m_csMacAddr4, "%02x", &nVal);
    struDeviceUser.byMACAddr[3] = (BYTE)nVal;
    sscanf(m_csMacAddr5, "%02x", &nVal);
    struDeviceUser.byMACAddr[4] = (BYTE)nVal;
    sscanf(m_csMacAddr6, "%02x", &nVal);
    struDeviceUser.byMACAddr[5] = (BYTE)nVal;

    struDeviceUser.byAlarmOnRight = m_bAlarmOn;
    struDeviceUser.byAlarmOffRight = m_bAlarmOff;
    struDeviceUser.byBypassRight = m_bBypass;
    struDeviceUser.byOtherRight[0] = m_bLog;
    struDeviceUser.byOtherRight[1] = m_bRestartShuntdown;
    struDeviceUser.byOtherRight[2] = m_bSetParam;
    struDeviceUser.byOtherRight[3] = m_bGetParam;
    struDeviceUser.byOtherRight[4] = m_bDefault;
    struDeviceUser.byOtherRight[5] = m_bSiren;
    struDeviceUser.byOtherRight[6] = m_bPtzControl;
    struDeviceUser.byOtherRight[7] = m_bUpgrade;
	
    struDeviceUser.byOtherRight[8] = m_bAlarmoutCtrl;
    struDeviceUser.byOtherRight[9] = m_bSerialCtrl;
    struDeviceUser.byOtherRight[10] = m_bGatewayCtrl;
    struDeviceUser.byOtherRight[11] = m_bAudioTalk;
    struDeviceUser.byOtherRight[12] = m_bLocalCtrl;
    struDeviceUser.byOtherRight[13] = m_bDiskCfg;
    struDeviceUser.byOtherRight[14] = m_bFormatDisk;
    struDeviceUser.byOtherRight[15] = m_bSensorCtrl;

	GetChanInfoFromWnd();
    SaveLastRemoteChan();

	//管理员用户
	if (1 == struDeviceUser.byUserType)
	{
// 		struDeviceUser.byAlarmOnRight = 1;
// 		struDeviceUser.byAlarmOffRight = 1;
// 		struDeviceUser.byBypassRight = 1;
// 		for (int i=0; i<MAX_RIGHT; i++)
// 		{
// 			struDeviceUser.byOtherRight[i] = 1;
// 		}
// 		for (i=0; i<(MAX_ALARMHOST_VIDEO_CHAN/8); i++)
// 		{
// 			struDeviceUser.byNetPreviewRight[i] = 1;
// 			struDeviceUser.byNetPTZRight[i] = 1;
// 			struDeviceUser.byNetPlaybackRight[i] = 1;
// 			struDeviceUser.byNetRecordRight[i] = 1;
// 		}
	}
	//除了admin用户以外的，不能拥有重启关机，恢复默认参数权限，远程升级权限，格式化硬盘
// 	if (0 != m_comboUserIndex.GetCurSel())
// 	{
// 		struDeviceUser.byOtherRight[1] = 0;
// 		struDeviceUser.byOtherRight[4] = 0;
// 		struDeviceUser.byOtherRight[7] = 0;
// 		struDeviceUser.byOtherRight[14] = 0;
// 	}
}

void CDlgAlarmNetUser::SetDeviceUserToWnd(NET_DVR_ALARM_DEVICE_USER &struDeviceUser)
{
    char szLan[40] = {0};
    strncpy(szLan, (char*)struDeviceUser.sUserName, sizeof(struDeviceUser.sUserName));
    m_csUserName = szLan;
    
    memset(szLan, 0, sizeof(szLan));
    strncpy(szLan, (char*)struDeviceUser.sPassword, sizeof(struDeviceUser.sPassword));
    m_csPassword = szLan;

    memset(szLan, 0, sizeof(szLan));
    strncpy(szLan, (char*)struDeviceUser.sOriginalPassword, sizeof(struDeviceUser.sOriginalPassword));
    m_csOriginalPassword = szLan;

    m_comboUserType.SetCurSel(struDeviceUser.byUserType);
	UpdateData(FALSE);
    OnSelchangeComboUsertype();
    m_csUserIP = struDeviceUser.struUserIP.sIpV4;
    m_csMacAddr1.Format("%02x", struDeviceUser.byMACAddr[0]);
    m_csMacAddr2.Format("%02x", struDeviceUser.byMACAddr[1]);
    m_csMacAddr3.Format("%02x", struDeviceUser.byMACAddr[2]);
    m_csMacAddr4.Format("%02x", struDeviceUser.byMACAddr[3]);
    m_csMacAddr5.Format("%02x", struDeviceUser.byMACAddr[4]);
    m_csMacAddr6.Format("%02x", struDeviceUser.byMACAddr[5]);
    m_bAlarmOn = struDeviceUser.byAlarmOnRight;
    m_bAlarmOff = struDeviceUser.byAlarmOffRight;
    m_bBypass = struDeviceUser.byBypassRight;
    m_bLog = struDeviceUser.byOtherRight[0];
    m_bRestartShuntdown = struDeviceUser.byOtherRight[1];
    m_bSetParam = struDeviceUser.byOtherRight[2];
    m_bGetParam = struDeviceUser.byOtherRight[3];
    m_bDefault = struDeviceUser.byOtherRight[4];
    m_bSiren = struDeviceUser.byOtherRight[5];
    m_bPtzControl = struDeviceUser.byOtherRight[6];
    m_bUpgrade = struDeviceUser.byOtherRight[7];

   m_bAlarmoutCtrl = struDeviceUser.byOtherRight[8];
   m_bSerialCtrl = struDeviceUser.byOtherRight[9];
   m_bGatewayCtrl = struDeviceUser.byOtherRight[10];
   m_bAudioTalk = struDeviceUser.byOtherRight[11];
   m_bLocalCtrl = struDeviceUser.byOtherRight[12];
   m_bDiskCfg = struDeviceUser.byOtherRight[13];
   m_bFormatDisk = struDeviceUser.byOtherRight[14];
   m_bSensorCtrl = struDeviceUser.byOtherRight[15];

   memset(m_pbRemoteChan, 0, sizeof(BOOL)* MAX_CHANNUM_V40);
   int i = 0;
   for (i = 0; i < 8 * 8; i++)// 8个字节*8位
   {
       if ((m_struDeviceUser.byNetPreviewRight[i / 8] >> i) & 0x01 == 1)
       {
           m_pbRemoteChan[i] = (BYTE)1;
       }
   }

	UpdateData(FALSE);
	m_cmRightType.SetCurSel(0);
	UpdateData(FALSE);
	SetChanInfoToDlg();
    CreateRemoteTree();
}

void CDlgAlarmNetUser::OnSelchangeComboUserIndex() 
{
	UpdateData(TRUE);
    m_lUserIndex = m_comboUserIndex.GetCurSel() + 1;
    m_iSelNetRightType = 0;
    m_cmRightType.SetCurSel(m_iSelNetRightType);
    GetDeviceUser(m_struDeviceUser);
    SetDeviceUserToWnd(m_struDeviceUser);
    UpdateData(FALSE);
}

void CDlgAlarmNetUser::OnBtnSetNetUser() 
{
    UpdateData(TRUE);
    GetDeviceUserFromWnd(m_struDeviceUser);
    if (m_struDeviceUser.sUserName[0]=='\0')
    {
        AfxMessageBox("用户名不能为空");
        return;
    }
    SetDeviceUser(m_struDeviceUser);
}

void CDlgAlarmNetUser::OnSelchangeComboUsertype() 
{
	UpdateData(TRUE);
	UserTypeEnable();
}

void CDlgAlarmNetUser::UserTypeEnable()
{
	int iIndex = m_comboUserType.GetCurSel();
	//admin用户和管理员
	if (1 == iIndex)
	{
// 		GetDlgItem(IDC_CHK_ALARM_ON)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_ALARM_OFF)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_BYPASS)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_LOG)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_RESTART_SHUTDOWN)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_SET_PARAM)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_GET_PARAM)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_DEFAULT)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_SIREN)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_UPGRADE)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_ALARMOUT_CTRL)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_AUDIO_TALK)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_DISK_CFG)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_FORMAT_DISK)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_GATEWAY_CTRL)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_SENSOR_CTRL)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_SERIAL_CTRL)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_LOCAL_CTRL)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHECK_PTZ_CTRL)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_LIST_VIDEO_CHAN)->EnableWindow(FALSE);
		//GetDlgItem(IDC_COMBO_RIGHT_TYPE)->EnableWindow(FALSE);
	}
	//普通用户
	else
	{
// 		GetDlgItem(IDC_CHK_ALARM_ON)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_ALARM_OFF)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_BYPASS)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_LOG)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_SET_PARAM)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_GET_PARAM)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_SIREN)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_ALARMOUT_CTRL)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_AUDIO_TALK)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_DISK_CFG)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_GATEWAY_CTRL)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_SENSOR_CTRL)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_SERIAL_CTRL)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHK_LOCAL_CTRL)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_CHECK_PTZ_CTRL)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_LIST_VIDEO_CHAN)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_COMBO_RIGHT_TYPE)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_LIST_VIDEO_CHAN)->EnableWindow(TRUE);
// 
// 		GetDlgItem(IDC_CHK_UPGRADE)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_DEFAULT)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_FORMAT_DISK)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_CHK_RESTART_SHUTDOWN)->EnableWindow(FALSE);
	}
}

void CDlgAlarmNetUser::GetChanInfoFromWnd() 
{
	UpdateData(TRUE);
	int i = 0;
	int iUserIndex = m_comboUserIndex.GetCurSel();
	if (m_iCurChanIndex == 0)
	{
		memset(m_struDeviceUser.byNetPreviewRight, 0, sizeof(m_struDeviceUser.byNetPreviewRight));
		for (i=0; i<m_listChan.GetItemCount(); i++)
		{
			m_struDeviceUser.byNetPreviewRight[i/8] |= (m_listChan.GetCheck(i)<<i);
		}
	}
	else if(m_iCurChanIndex==1)
	{
		memset(m_struDeviceUser.byNetRecordRight, 0, sizeof(m_struDeviceUser.byNetRecordRight));
		for (i=0; i<m_listChan.GetItemCount(); i++)
		{
			m_struDeviceUser.byNetRecordRight[i/8] |= (m_listChan.GetCheck(i)<<i);
		}
	}
	else if (m_iCurChanIndex==2)
	{
		memset(m_struDeviceUser.byNetPlaybackRight, 0, sizeof(m_struDeviceUser.byNetPlaybackRight));
		for (i=0; i<m_listChan.GetItemCount(); i++)
		{
			m_struDeviceUser.byNetPlaybackRight[i/8] |= (m_listChan.GetCheck(i)<<i);
		}
	}
	else if (m_iCurChanIndex==3)
	{
		memset(m_struDeviceUser.byNetPTZRight, 0, sizeof(m_struDeviceUser.byNetPTZRight));
		for (i=0; i<m_listChan.GetItemCount(); i++)
		{
			m_struDeviceUser.byNetPTZRight[i/8] |= (m_listChan.GetCheck(i)<<i);
		}
	}
}

void CDlgAlarmNetUser::SetChanInfoToDlg() 
{
	UpdateData(TRUE);
	int iIndex = m_cmRightType.GetCurSel();
	int i=0;
	if (iIndex == 0)	//远程预览
	{
		for (i=0; i<m_listChan.GetItemCount(); i++)
		{
			m_listChan.SetCheck(i, ((m_struDeviceUser.byNetPreviewRight[i/8]>>i) & 0x01));
		}
	}
	else if (iIndex == 1)//远程手动录像
	{
		for (i=0; i<m_listChan.GetItemCount(); i++)
		{
			m_listChan.SetCheck(i, ((m_struDeviceUser.byNetRecordRight[i/8]>>i) & 0x01));
		}
	}
	else if (iIndex == 2)//远程回放
	{
		for (i=0; i<m_listChan.GetItemCount(); i++)
		{
			m_listChan.SetCheck(i, (m_struDeviceUser.byNetPlaybackRight[i/8]>>i) & 0x01);
		}
	}
	else if (iIndex == 3)	//PTZ控制
	{
		for (i=0; i<m_listChan.GetItemCount(); i++)
		{
			m_listChan.SetCheck(i, (m_struDeviceUser.byNetPTZRight[i/8]>>i) & 0x01);
		}
	}
	
	m_iCurChanIndex = iIndex;
	UpdateData(FALSE);
}

// void CDlgAlarmNetUser::GetRightFromDlg() 
// {
// 	
// }

void CDlgAlarmNetUser::OnSelchangeComboRightType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetChanInfoFromWnd();
	SetChanInfoToDlg();
    UpdateData(FALSE);


    SaveLastRemoteChan();
    UpdateData(TRUE);
    int i = 0;
    //BOOL bFlag = FALSE;
    BYTE byRight[MAX_CHANNUM_V40] = { 0 };
    m_iSelNetRightType = m_cmRightType.GetCurSel();
    switch (m_iSelNetRightType)
    {
    case 0:
        //bFlag = m_bChkRemotePreview;
        //for (i = 0; i < MAX_CHANNUM_V40; i++)
        for (i = 0; i < MAX_ALARMHOST_VIDEO_CHAN / 8 * 8; i++)// 通道数*8位
        {
            if ((m_struDeviceUser.byNetPreviewRight[i / 8] >> i) & 0x01 == 1)
            {
                byRight[i] = (BYTE)1;
            }
        }
        break;
    case 1:
        //bFlag = m_bChkRemoteRecManul;
        //for (i = 0; i < MAX_CHANNUM_V40; i++)
        for (i = 0; i < MAX_ALARMHOST_VIDEO_CHAN / 8 * 8; i++)// 通道数*8位
        {
            if ((m_struDeviceUser.byNetRecordRight[i / 8] >> i) & 0x01 == 1)
            {
                byRight[i] = (BYTE)1;
            }
        }
        break;
    case 2:
        //bFlag = m_bChkRemotePlayBack;
        //for (i = 0; i < MAX_CHANNUM_V40; i++)
        for (i = 0; i < MAX_ALARMHOST_VIDEO_CHAN / 8 * 8; i++)// 通道数*8位
        {
            if ((m_struDeviceUser.byNetPlaybackRight[i / 8] >> i) & 0x01 == 1)
            {
                byRight[i] = (BYTE)1;
            }
        }
        break;
    case 3:
        //bFlag = m_bChkRemotePTZCtrl;
        //for (i = 0; i < MAX_CHANNUM_V40; i++)
        for (i = 0; i < MAX_ALARMHOST_VIDEO_CHAN / 8 * 8; i++)// 通道数*8位
        {
            if ((m_struDeviceUser.byNetPTZRight[i / 8] >> i) & 0x01 == 1)
            {
                byRight[i] = (BYTE)1;
            }
        }
        break;
    default:
        //bFlag = FALSE;
        break;
    }

//     if (m_bSuperUserLogin)
//     {
//         if (m_iUserIndex == 0)
//         {
//             //bFlag = FALSE;
//         }
//     }
//     else
//     {
//         //bFlag = FALSE;
//     }

    for (i = 0; i < MAX_CHANNUM_V40; i++)
    {
        m_pbRemoteChan[i] = byRight[i];
    }
    //m_bRemoteEnable = bFlag;
    CreateRemoteTree();
}

/*********************************************************
Function:	OnPaint
Desc:		paint the tree
Input:	none
Output:	none
Return:	none
**********************************************************/
void CDlgAlarmNetUser::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    if (m_bGetUserParams)
    {
        //CreateLocalTree();
        CreateRemoteTree();
    }
}


/*********************************************************
Function:	OnClickTreeRemoteChan
Desc:		change the check status of the channel for remote right
Input:	none
Output:	none
Return:	none
**********************************************************/
void CDlgAlarmNetUser::OnClickTreeRemoteChan(NMHDR* pNMHDR, LRESULT* pResult)
{
    UpdateData(TRUE);
    CPoint pt(0, 0);
    CRect rc(0, 0, 0, 0);
    GetCursorPos(&pt);
    m_treeRemoteChan.ScreenToClient(&pt);
    GetDlgItem(IDC_TREE_REMOTE_CHAN)->GetWindowRect(&rc);
    m_treeRemoteChan.ScreenToClient(&rc);

    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;


    // 	CPoint pt(0, 0);
    // 	GetCursorPos(&pt);
    // 	m_treeRemoteChan.ScreenToClient(&pt);

    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeRemoteChan.HitTest(pt, &uFlag);
    if (NULL == hSelect)
    {
        return;
    }
    m_treeRemoteChan.SelectItem(hSelect);
    DWORD dwIndex = m_treeRemoteChan.GetItemData(hSelect) % 1000;
    BOOL bCheck = m_treeRemoteChan.GetCheck(hSelect);
    m_treeRemoteChan.SetCheck(hSelect, !uFlag);
//     if (!m_bRemoteEnable)//current remote right is disalbe, don't change the status when click
//     {
//         if (uFlag == LVHT_TOLEFT)//0x0040, 
//         {
//             m_treeRemoteChan.SetCheck(hSelect, !uFlag);
//         }
//         return;
//     }

    if (g_struDeviceInfo[m_iDevIndex].byMirrorChanNum && dwIndex + 1 > g_struDeviceInfo[m_iDevIndex].iDeviceChanNum)
    {
        m_pbRemoteChan[g_struDeviceInfo[m_iDevIndex].struMirrorChan[dwIndex - MIRROR_CHAN_INDEX].iChannelNO - 1] = !bCheck;
    }
    else
    {
        m_pbRemoteChan[g_struDeviceInfo[m_iDevIndex].pStruChanInfo[dwIndex].iChannelNO - 1] = !bCheck;
    }


    if (uFlag != LVHT_TOLEFT)//0x0040
    {
        m_treeRemoteChan.SetCheck(hSelect, !bCheck);
    }
    else
    {
        m_treeRemoteChan.SetCheck(hSelect, bCheck);
    }

    //GetDlgItem(IDC_BTN_REMOTE_CHAN_OK)->EnableWindow(m_bRemoteEnable);
    *pResult = 0;
}

/*********************************************************
Function:	CreateRemoteTree
Desc:		remote user right settings
Input:
Output:
Return:
**********************************************************/
void CDlgAlarmNetUser::CreateRemoteTree(void)
{
    BYTE byRight[MAX_CHANNUM_V40] = { 0 };
    CString strTemp = _T("");
    CString strChanTmp = _T("");
    int i = 0;
    HTREEITEM hChanItem = NULL;

    if (m_iDevIndex < 0)
    {
        return;
    }
    DWORD dwStartDChanNo = 0;
    if (g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40 != NULL)
    {
        dwStartDChanNo = g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40[0].dwStartDChan;
    }

    if (m_lChanNum <= 0)
    {
        m_treeRemoteChan.EnableWindow(FALSE);
        return;
    }
    m_treeRemoteChan.DeleteAllItems();

    for (i = 0; i< MAX_CHANNUM_V40; i++)
    {
        byRight[i] = (BYTE)m_pbRemoteChan[i];
    }

    for (i = 0; i < g_struDeviceInfo[m_iDevIndex].iDeviceChanNum; i++)
    {
        if (i < g_struDeviceInfo[m_iDevIndex].iAnalogChanNum)
        {
            if (g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].bEnable)
            {
                strTemp.Format(ANALOG_C_FORMAT, i + g_struDeviceInfo[m_iDevIndex].iStartChan);
                hChanItem = m_treeRemoteChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
                m_treeRemoteChan.SetItemData(hChanItem, 0 * 1000 + i);
                if (1 == m_pbRemoteChan[g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].iChannelNO - 1])
                {
                    m_treeRemoteChan.SetCheck(hChanItem, TRUE);
                }
            }

        }
        else if (g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].bEnable /*&& m_iSelNetRightType != 3*/)
        {
            strTemp.Format(DIGITAL_C_FORMAT, (g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].iChannelNO + g_struDeviceInfo[m_iDevIndex].iStartChan - dwStartDChanNo));
            hChanItem = m_treeRemoteChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
            m_treeRemoteChan.SetItemData(hChanItem, 1 * 1000 + i);
            if (1 == m_pbRemoteChan[g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].iChannelNO - 1])
            {
                m_treeRemoteChan.SetCheck(hChanItem, TRUE);
            }
        }
    }
    if (g_struDeviceInfo[m_iDevIndex].byMirrorChanNum)
    {
        for (i = 0; i < g_struDeviceInfo[m_iDevIndex].byMirrorChanNum && i < 16; i++)
        {
            if (g_struDeviceInfo[m_iDevIndex].struMirrorChan[i].bEnable)
            {
                strTemp.Format(MIRROR_C_FORMAT, i + 1);
                hChanItem = m_treeRemoteChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
                m_treeRemoteChan.SetItemData(hChanItem, 0 * 1000 + i + MIRROR_CHAN_INDEX);
                if (1 == m_pbRemoteChan[g_struDeviceInfo[m_iDevIndex].struMirrorChan[i].iChannelNO - 1])
                {
                    m_treeRemoteChan.SetCheck(hChanItem, TRUE);
                }
            }
        }
    }
    m_treeRemoteChan.Expand(m_treeRemoteChan.GetRootItem(), TVE_EXPAND);
    m_treeRemoteChan.SelectItem(hChanItem);
    // g_CreateChannelTree(m_treeRemoteChan,m_iDevIndex,m_pbRemoteChan);
    //	m_treeRemoteChan.EnableWindow(m_bRemoteEnable);
    UpdateData(FALSE);
}


/*********************************************************
Function:	SaveLastRemoteChan
Desc:		Save the channels when ComboBox sel changed
Input:
Output:
Return:
**********************************************************/
void CDlgAlarmNetUser::SaveLastRemoteChan()
{
    UpdateData(TRUE);

    BYTE byRight[MAX_CHANNUM_V40] = { 0 };
    int i = 0, j = 0;
    for (i = 0; i < MAX_CHANNUM_V40; i++)
    {
        byRight[i] = (BYTE)m_pbRemoteChan[i];
    }
    switch (m_iSelNetRightType)
    {
    case 0:
        memset(m_struDeviceUser.byNetPreviewRight, 0, sizeof(m_struDeviceUser.byNetPreviewRight));
        //for (i = 0; i < MAX_CHANNUM_V40; i++)
        for (i = 0; i < (MAX_ALARMHOST_VIDEO_CHAN/8) * 8; i++)// 通道数*8位
        {
            if (byRight[i] == (BYTE)1)
            {
                m_struDeviceUser.byNetPreviewRight[i / 8] |= 1 << i;
            }
        }
        break;
    case 1:
        memset(m_struDeviceUser.byNetRecordRight, 0, sizeof(m_struDeviceUser.byNetRecordRight));
        //for (i = 0; i < MAX_CHANNUM_V40; i++)
        for (i = 0; i < (MAX_ALARMHOST_VIDEO_CHAN / 8) * 8; i++)// 通道数*8位
        {
            if (byRight[i] == (BYTE)1)
            {
                m_struDeviceUser.byNetRecordRight[i / 8] |= 1 << i;
            }
        }
        break;
    case 2:
        memset(m_struDeviceUser.byNetPlaybackRight, 0, sizeof(m_struDeviceUser.byNetPlaybackRight));
        //for (i = 0; i < MAX_CHANNUM_V40; i++)
        for (i = 0; i < (MAX_ALARMHOST_VIDEO_CHAN / 8) * 8; i++)// 通道数*8位
        {
            if (byRight[i] == (BYTE)1)
            {
                m_struDeviceUser.byNetPlaybackRight[i / 8] |= 1 << i;
            }
        }
        break;
    case 3:
        memset(m_struDeviceUser.byNetPTZRight, 0, sizeof(m_struDeviceUser.byNetPTZRight));
        //for (i = 0; i < MAX_CHANNUM_V40; i++)
        for (i = 0; i < (MAX_ALARMHOST_VIDEO_CHAN / 8) * 8; i++)// 通道数*8位
        {
            if (byRight[i] == (BYTE)1)
            {
                m_struDeviceUser.byNetPTZRight[i / 8] |= 1 << i;
            }
        }
        break;
    default:
        break;
    }

}
