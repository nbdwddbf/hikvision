/**********************************************************
FileName:    SubDlgUserCfg.cpp
Description: User right configuration      
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "SubDlgUserCfg.h"
#include ".\subdlgusercfg.h"


// CSubDlgUserCfg dialog
/*********************************************************
  Function:	CSubDlgUserCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CSubDlgUserCfg, CDialog)
CSubDlgUserCfg::CSubDlgUserCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgUserCfg::IDD, pParent)
	, m_csUserName(_T(""))
	, m_csUserPwd(_T(""))
	, m_csVerifyPwd(_T(""))
	, m_csUserIP(_T(""))
	, m_csMacAddr1(_T(""))
	, m_csMacAddr2(_T(""))
	, m_csMacAddr3(_T(""))
	, m_csMacAddr4(_T(""))
	, m_csMacAddr5(_T(""))
	, m_csMacAddr6(_T(""))
	, m_bChkLocalPTZCtrl(FALSE)
	, m_bChkLocalRecManul(FALSE)
	, m_bChkLocalSetParam(FALSE)
	, m_bChkLocalShowStat(FALSE)
	, m_bChkLocalHighOperation(FALSE)
	, m_bChkLocalPlayBack(FALSE)
	, m_bChkLocalCameraManage(FALSE)
	, m_bChkLocalReboot(FALSE)
	, m_bChkRemotePTZCtrl(FALSE)
	, m_bChkRemoteRecManul(FALSE)
	, m_bChkRemoteSetParam(FALSE)
	, m_bChkRemoteShowStat(FALSE)
	, m_bChkRemoteHighOperation(FALSE)
	, m_bChkRemotePlayBack(FALSE)
	, m_bChkRemoteVoiceTalk(FALSE)
	, m_bChkRemoteAlarm(FALSE)
	, m_bChkRemoteLocalOut(FALSE)
	, m_bChkNetCameraManage(FALSE)
	, m_bChkNetReboot(FALSE)
	, m_iDeviceIndex(-1)
	, m_lLoginID(-1)
	, m_bChkRemoteRecRight(FALSE)
	, m_bChkRemoteUserPtz(FALSE)
	, m_bChkRemotePreview(FALSE)
	, m_bChkRemoteSerialCtrl(FALSE)
	, m_iChanCount(0)
	, m_lStartChannel(0)
	, m_iUserIndex(-1)
	, m_bSuperUserLogin(FALSE)
	, m_bSetUserParams(FALSE)
	, m_bChkLocalBackup(FALSE)
	, m_bLocalEnable(FALSE)
	, m_bRemoteEnable(FALSE)
    , m_bMaterial(FALSE)
    , m_bSchedule(FALSE)
    , m_bProgramAdd(FALSE)
    , m_bPlay(FALSE)
    , m_bShop(FALSE)
    , m_bTerminal(FALSE)
    , m_bScheduleAdd(FALSE)
    , m_bMaterialUpload(FALSE)
    , m_bProgram(FALSE)
    , m_sloginPassword(_T(""))
    , m_bChkLocalPreview(FALSE)
{
    m_pbLocalChan = new BOOL[MAX_CHANNUM_V40];
    if (m_pbLocalChan != NULL)
    {
        memset(m_pbLocalChan, 0, sizeof(BOOL)*MAX_CHANNUM_V40);
    }
    
    m_pbRemoteChan = new BOOL[MAX_CHANNUM_V40];
    if (m_pbRemoteChan != NULL)
    {
        memset(m_pbRemoteChan, 0, sizeof(BOOL)*MAX_CHANNUM_V40);
    }
}

/*********************************************************
  Function:	~CSubDlgUserCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CSubDlgUserCfg::~CSubDlgUserCfg()
{
    //delete alloc memory 
    if (m_pbLocalChan != NULL)
    {
        delete[] m_pbLocalChan;
        m_pbLocalChan = NULL;
    }

    if(m_pbRemoteChan != NULL)
    {
        delete[] m_pbRemoteChan;
        m_pbRemoteChan = NULL;
    }

    if (m_pStruUserCfg_V51 != NULL)
    {
        delete m_pStruUserCfg_V51;
        m_pStruUserCfg_V51 = NULL;
    }
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSubDlgUserCfg)
    DDX_Control(pDX, IDC_COMBO_PRIORITY, m_comboPriority);
    DDX_Control(pDX, IDC_TREE_REMOTE_CHAN, m_treeRemoteChan);
    DDX_Control(pDX, IDC_TREE_LOCAL_CHAN, m_treeLocalChan);
    DDX_Control(pDX, IDC_COMBO_USER_SEL, m_comboUserSel);
    DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
    DDV_MaxChars(pDX, m_csUserName, 32);
    DDX_Text(pDX, IDC_EDIT_USER_PWD, m_csUserPwd);
    DDV_MaxChars(pDX, m_csUserPwd, 16);
    DDX_Text(pDX, IDC_EDIT_USER_VERIFY_PWD, m_csVerifyPwd);
    DDV_MaxChars(pDX, m_csVerifyPwd, 16);
    DDX_Text(pDX, IDC_EDIT_USER_IP, m_csUserIP);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR1, m_csMacAddr1);
    DDV_MaxChars(pDX, m_csMacAddr1, 2);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR2, m_csMacAddr2);
    DDV_MaxChars(pDX, m_csMacAddr2, 2);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR3, m_csMacAddr3);
    DDV_MaxChars(pDX, m_csMacAddr3, 2);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR4, m_csMacAddr4);
    DDV_MaxChars(pDX, m_csMacAddr4, 2);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR5, m_csMacAddr5);
    DDV_MaxChars(pDX, m_csMacAddr5, 2);
    DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR6, m_csMacAddr6);
    DDV_MaxChars(pDX, m_csMacAddr6, 2);
    DDX_Check(pDX, IDC_CHK_LOCAL_PTZ_CTRL, m_bChkLocalPTZCtrl);
    DDX_Check(pDX, IDC_CHK_LOCAL_REC_MANUAL, m_bChkLocalRecManul);
    DDX_Check(pDX, IDC_CHK_LOCAL_SET_PARAM, m_bChkLocalSetParam);
    DDX_Check(pDX, IDC_CHK_LOCAL_SHOW_STAT, m_bChkLocalShowStat);
    DDX_Check(pDX, IDC_CHK_LOCAL_HIGH_OPERATION, m_bChkLocalHighOperation);
    DDX_Check(pDX, IDC_CHK_LOCAL_PLAY_BACK, m_bChkLocalPlayBack);
    DDX_Check(pDX, IDC_CHK_REMOTE_PTZ_CTRL, m_bChkRemotePTZCtrl);
    DDX_Check(pDX, IDC_CHK_REMOTE_REC_MANUAL, m_bChkRemoteRecManul);
    DDX_Check(pDX, IDC_CHK_REMOTE_SET_PARAM, m_bChkRemoteSetParam);
    DDX_Check(pDX, IDC_CHK_REMOTE_SHOW_STAT, m_bChkRemoteShowStat);
    DDX_Check(pDX, IDC_CHK_REMOTE_HIGH_OPERATION, m_bChkRemoteHighOperation);
    DDX_Check(pDX, IDC_CHK_REMOTE_PLAY_BACK, m_bChkRemotePlayBack);
    DDX_Check(pDX, IDC_CHK_VOICE_TALK, m_bChkRemoteVoiceTalk);
    DDX_Check(pDX, IDC_CHK_REMOTE_ALARM, m_bChkRemoteAlarm);
    DDX_Check(pDX, IDC_CHK_REMOTE_CTRL_LOCAL_OUT, m_bChkRemoteLocalOut);
    DDX_Check(pDX, IDC_CHK_NET_PREVIEW, m_bChkRemotePreview);
    DDX_Check(pDX, IDC_CHK_REOMTE_SERIAL_CTRL, m_bChkRemoteSerialCtrl);
    DDX_Check(pDX, IDC_CHK_LOCAL_BACKUP, m_bChkLocalBackup);
    DDX_Control(pDX, IDC_COMBO_NET_RIGHT_TYPE, m_comboNetRightType);
    DDX_Control(pDX, IDC_COMBO_LOCAL_RIGHT_TYPE, m_comboLocalRightType);
    DDX_Check(pDX, IDC_CHK_LOCAL_IP_ACCESS, m_bChkLocalCameraManage);
    DDX_Check(pDX, IDC_CHK_LOCAL_REBOOT, m_bChkLocalReboot);
    DDX_Check(pDX, IDC_CHK_NET_IP_ACCESS, m_bChkNetCameraManage);
    DDX_Check(pDX, IDC_CHK_NET_REBOOT, m_bChkNetReboot);
    DDX_Check(pDX, IDC_CHK_ALARM_ON, m_bAlarmOn);
    DDX_Check(pDX, IDC_CHK_BYPASS, m_bBypass);
    DDX_Check(pDX, IDC_CHK_ALARM_OFF, m_bAlarmOff);
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHECK_MATERIAL, m_bMaterial);
    DDX_Check(pDX, IDC_CHECKSCHEDUL, m_bSchedule);
    DDX_Check(pDX, IDC_CHECK_NEW_PRO, m_bProgramAdd);
    DDX_Check(pDX, IDC_CHECK_INFO_PLAY, m_bPlay);
    DDX_Check(pDX, IDC_CHECK_SHOP, m_bShop);
    DDX_Check(pDX, IDC_CHECK_TERMINAL, m_bTerminal);
    DDX_Check(pDX, IDC_CHECK_NEW_SCHEDULE, m_bScheduleAdd);
    DDX_Check(pDX, IDC_CHECK_UP_MATERIAL, m_bMaterialUpload);
    DDX_Check(pDX, IDC_CHECK_PROGRAM, m_bProgram);
    DDX_Text(pDX, IDC_EDIT_LOGIN_PASSWORD, m_sloginPassword);
    DDX_Check(pDX, IDC_CHK_LOCAL_PREVIEW, m_bChkLocalPreview);
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CSubDlgUserCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgUserCfg)	
	ON_CBN_SELCHANGE(IDC_COMBO_USER_SEL, OnCbnSelchangeComboUserSel)
	ON_BN_CLICKED(ID_BTN_USER_OK, OnBnClickedBtnUserOk)
	ON_CBN_SELCHANGE(IDC_COMBO_LOCAL_RIGHT_TYPE, OnCbnSelchangeComboLocalRightType)
	ON_BN_CLICKED(IDC_CHK_LOCAL_REC_MANUAL, OnBnClickedChkLocalRecManual)
	ON_BN_CLICKED(IDC_CHK_LOCAL_PTZ_CTRL, OnBnClickedChkLocalPtzCtrl)
	ON_BN_CLICKED(IDC_CHK_LOCAL_BACKUP, OnBnClickedChkLocalBackup)
	ON_BN_CLICKED(IDC_BTN_LOCAL_CHAN_OK, OnBnClickedBtnLocalChanOk)
	ON_BN_CLICKED(IDC_BTN_REMOTE_CHAN_OK, OnBnClickedBtnRemoteChanOk)
	ON_BN_CLICKED(IDC_CHK_REMOTE_REC_MANUAL, OnBnClickedChkRemoteRecManual)
	ON_BN_CLICKED(IDC_CHK_REMOTE_PTZ_CTRL, OnBnClickedChkRemotePtzCtrl)
	ON_BN_CLICKED(IDC_CHK_LOCAL_PLAY_BACK, OnBnClickedChkLocalPlayBack)
	ON_BN_CLICKED(IDC_CHK_NET_PREVIEW, OnBnClickedChkNetPreview)
	ON_BN_CLICKED(IDC_CHK_REMOTE_PLAY_BACK, OnBnClickedChkRemotePlayBack)
	ON_CBN_SELCHANGE(IDC_COMBO_NET_RIGHT_TYPE, OnCbnSelchangeComboRemoteRightType)
	ON_NOTIFY(NM_CLICK, IDC_TREE_LOCAL_CHAN, OnClickTreeLocalChan)
	ON_NOTIFY(NM_CLICK, IDC_TREE_REMOTE_CHAN, OnClickTreeRemoteChan)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SYNC_IPC_PASSWD, OnButtonSyncIpcPasswd)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_CHK_LOCAL_PREVIEW, &CSubDlgUserCfg::OnBnClickedChkLocalPreview)

END_MESSAGE_MAP()


// CSubDlgUserCfg message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initial displag box
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CSubDlgUserCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_pStruUserCfg_V51 = new NET_DVR_USER_V51;
    if (m_pStruUserCfg_V51 == NULL)
	{
		return FALSE;
	}

    memset(m_pStruUserCfg_V51, 0, sizeof(NET_DVR_USER_V51));
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	return TRUE;
}

/*********************************************************
  Function:	CheckInitParam
  Desc:		check and refresh dialog box whenthere is modification on nodes
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CSubDlgUserCfg::CheckInitParam()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return FALSE;
	}
	if (g_struDeviceInfo[iDeviceIndex].lLoginID < 0)
	{
		m_iChanCount = 0;
		return FALSE;
	}
	
//	if (m_iDeviceIndex == iDeviceIndex)
//	{
//		return TRUE;
//	}
//	else
	{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
		m_lStartChannel = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
		
		// 总通道数 = 模拟通道 + 数字通道
		m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum + g_struDeviceInfo[m_iDeviceIndex].iIPChanNum;
		if (strcmp(g_struDeviceInfo[m_iDeviceIndex].chLoginUserName, "admin")==0)
		{
			m_bSuperUserLogin = TRUE;
		}
		else
		{
			m_bSuperUserLogin = FALSE;
		}
	}
	m_iSelLocalRightType = 0;
	m_iSelNetRightType = 0;
	m_comboUserSel.SetCurSel(-1);
	m_csUserName = _T("");
	m_csUserPwd = _T("");
	m_csVerifyPwd = _T("");
	m_csUserIP = _T("");
	m_csMacAddr1 = _T("");
	m_csMacAddr2 = _T("");
	m_csMacAddr3 = _T("");
	m_csMacAddr4 = _T("");
	m_csMacAddr5 = _T("");
	m_csMacAddr6 = _T("");
	m_bChkLocalPTZCtrl = FALSE;
	m_bChkLocalRecManul = FALSE;
	m_bChkLocalSetParam = FALSE;
	m_bChkLocalShowStat = FALSE;
	m_bChkLocalHighOperation = FALSE;
	m_bChkLocalPlayBack = FALSE;


	m_bChkRemotePTZCtrl = FALSE;
	m_bChkRemoteRecManul = FALSE;
	m_bChkRemoteSetParam = FALSE;
	m_bChkRemoteShowStat = FALSE;
	m_bChkRemoteHighOperation = FALSE;
	m_bChkRemotePlayBack = FALSE;
	m_bChkRemoteVoiceTalk = FALSE;
	m_bChkRemoteAlarm = FALSE;
	m_bChkRemoteLocalOut = FALSE;

	m_bChkRemoteRecRight = FALSE;
	m_bChkRemoteUserPtz = FALSE;
	m_bChkRemotePreview = FALSE;
	m_bChkRemoteSerialCtrl = FALSE;
	GetDlgItem(IDC_BTN_LOCAL_CHAN_OK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_REMOTE_CHAN_OK)->EnableWindow(FALSE);

	if (m_lLoginID < 0)
	{
		return FALSE;
	}
	DWORD dwReturned;
	m_bSetUserParams = FALSE;
	m_bGetUserParams = FALSE;	

    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_USERCFG_V51, 0, &m_StruUserCfg_V51, sizeof(m_StruUserCfg_V51), &dwReturned))
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_USERCFG_V51");
		char szLan[128] = {0};
		g_StringLanType(szLan, "获取用户参数失败！", "Get User Parameter failed");

		AfxMessageBox(szLan);
		return FALSE;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_USERCFG_V51");
	}

	m_bGetUserParams = TRUE;

	return TRUE;
}

/*********************************************************
  Function:	CurCfgUpdate
  Desc:		refresh device info
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgUserCfg::CurCfgUpdate()
{
	if (!CheckInitParam())
	{
		m_iDeviceIndex = -1;	
		EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}
	EnableWindow(TRUE);
    memcpy(m_pStruUserCfg_V51->struUser, m_StruUserCfg_V51.struUser, sizeof(m_StruUserCfg_V51.struUser));
	CString csUserName;
	char cTemp[100] = {0};
	int i = 0;
	if (m_bSuperUserLogin)
	{
		m_iUserIndex = 0;			
		m_comboUserSel.SetCurSel(m_iUserIndex);
	}
	else
	{
		for (i=0; i<MAX_USERNUM_V30; i++)
		{
			ZeroMemory(cTemp, 100);
            memcpy(cTemp, m_pStruUserCfg_V51->struUser[i].sUserName, MAX_NAMELEN);
			csUserName.Format("%s", cTemp);
			if (strcmp(csUserName, g_struDeviceInfo[m_iDeviceIndex].chLoginUserName) == 0)
			{
				break;
			}
		}
        if ( i == MAX_USERNUM_V30 )
        {
            return ; 
        }
		m_iUserIndex = i;
		m_comboUserSel.SetCurSel(m_iUserIndex);
	}

	OnCbnSelchangeComboUserSel();
	UpdateData(FALSE);
}

/*********************************************************
  Function:	CfgSetup
  Desc:		update user configuration info
  Input:	
  Output:	
  Return:	TRUE,settinsg succeeds;FALSE,setting fails;
**********************************************************/
BOOL CSubDlgUserCfg::CfgSetup()
{
	if (m_bSetUserParams)
	{
        if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_USERCFG_V51, 0, &m_StruUserCfg_V51, sizeof(m_StruUserCfg_V51)))
		{
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_USERCFG_V51");
			char szLan[128] = {0};
			g_StringLanType(szLan, "设置用户参数失败！", "Set User Parameter failed");
			AfxMessageBox(szLan);	
			return FALSE;		
		}
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_USERCFG_V51");
        }
    }
	return TRUE;
}

/*********************************************************
  Function:	OnBnClickedBtnUserOk
  Desc:		user configuration parameter settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedBtnUserOk()
{
    m_pStruUserCfg_V51->dwSize = sizeof(*m_pStruUserCfg_V51);
	SaveLastLocalChan();
	SaveLastRemoteChan();

	UpdateData(TRUE);
    strncpy((char *)m_pStruUserCfg_V51->struUser[m_iUserIndex].sUserName, m_csUserName, MAX_NAMELEN);
	if (strcmp(m_csUserPwd,m_csVerifyPwd) != 0)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "密码与确认密码不一致", "Password and Confirm Password inconsistent");
		AfxMessageBox(szLan);
		return;
	}
    if (strstr(m_csVerifyPwd, m_csUserName)!=NULL)
    {
        char szLan[128] = { 0 };
        g_StringLanType(szLan, "密码不能包含用户名", "Password can not include the user name");
        AfxMessageBox(szLan);
        return;
    }
	int iLength = strlen(m_csUserPwd);
	iLength = iLength>PASSWD_LEN ? PASSWD_LEN:iLength;
	if (iLength < MIN_PASSWD_LEN || iLength > PASSWD_LEN)
    {
        char szLan[128] = { 0 };
        g_StringLanType(szLan, "密码长度应该介于8~16", "Password should Between 8 and 16");
        AfxMessageBox(szLan);
        return;
    }
    char temp[PASSWD_LEN] = { 0 };
	strncpy(temp,m_csUserPwd,PASSWD_LEN);

    strncpy((char *)m_pStruUserCfg_V51->struUser[m_iUserIndex].sPassword, m_csUserPwd, PASSWD_LEN);
	if (m_csUserIP.Find(':') != -1)
	{
        strncpy((char *)m_pStruUserCfg_V51->struUser[m_iUserIndex].struUserIP.byIPv6, m_csUserIP, 128);
	}
	else
	{
        strncpy((char *)m_pStruUserCfg_V51->struUser[m_iUserIndex].struUserIP.sIpV4, m_csUserIP, 16);
	}
	int nVal;
	sscanf(m_csMacAddr1, "%02x", &nVal);
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[0] = (BYTE)nVal;
	sscanf(m_csMacAddr2, "%02x", &nVal);
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[1] = (BYTE)nVal;
	sscanf(m_csMacAddr3, "%02x", &nVal);
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[2] = (BYTE)nVal;
	sscanf(m_csMacAddr4, "%02x", &nVal);
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[3] = (BYTE)nVal;
	sscanf(m_csMacAddr5, "%02x", &nVal);
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[4] = (BYTE)nVal;
	sscanf(m_csMacAddr6, "%02x", &nVal);
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[5] = (BYTE)nVal;

	m_pStruUserCfg_V51->struUser[m_iUserIndex].byPriority = (BYTE)m_comboPriority.GetCurSel();
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[0] = (BYTE)m_bChkLocalPTZCtrl;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[1] = (BYTE)m_bChkLocalRecManul;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[2] = (BYTE)m_bChkLocalPlayBack;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[3] = (BYTE)m_bChkLocalSetParam;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[4] = (BYTE)m_bChkLocalShowStat;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[5] = (BYTE)m_bChkLocalHighOperation;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[7] = (BYTE)m_bChkLocalCameraManage;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[8] = (BYTE)m_bChkLocalBackup;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[9] = (BYTE)m_bChkLocalReboot;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[10] = (BYTE)m_bChkLocalPreview;

	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[0] = (BYTE)m_bChkRemotePTZCtrl;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[1] = (BYTE)m_bChkRemoteRecManul;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[2] = (BYTE)m_bChkRemotePlayBack;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[3] = (BYTE)m_bChkRemoteSetParam;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[4] = (BYTE)m_bChkRemoteShowStat;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[5] = (BYTE)m_bChkRemoteHighOperation;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[6] = (BYTE)m_bChkRemoteVoiceTalk;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[7] = (BYTE)m_bChkRemotePreview;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[8] = (BYTE)m_bChkRemoteAlarm;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[9] = (BYTE)m_bChkRemoteLocalOut;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[10] = (BYTE)m_bChkRemoteSerialCtrl;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[12] = (BYTE)m_bChkNetCameraManage;
	m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[13] = (BYTE)m_bChkNetReboot;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byAlarmOnRight = m_bAlarmOn;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byAlarmOffRight = m_bAlarmOff;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byBypassRight = m_bBypass;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[0] = (BYTE)m_bMaterial;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[1] = (BYTE)m_bProgram;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[2] = (BYTE)m_bSchedule;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[3] = (BYTE)m_bMaterialUpload;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[4] = (BYTE)m_bProgramAdd;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[5] = (BYTE)m_bScheduleAdd;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[6] = (BYTE)m_bPlay;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[7] = (BYTE)m_bTerminal;
    m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[8] = (BYTE)m_bShop;

	//OnBnClickedBtnLocalChanOk();
//	OnBnClickedBtnRemoteChanOk();
    strncpy((char *)m_StruUserCfg_V51.sloginPassword, m_sloginPassword, PASSWD_LEN);
    m_StruUserCfg_V51.dwSize = sizeof(m_StruUserCfg_V51);
    m_StruUserCfg_V51.dwMaxUserNum = m_pStruUserCfg_V51->dwMaxUserNum;
    memcpy((char *)m_StruUserCfg_V51.struUser, (char *)m_pStruUserCfg_V51->struUser, sizeof(m_pStruUserCfg_V51->struUser));
	m_bSetUserParams = TRUE;
}

/*********************************************************
  Function:	OnCbnSelchangeComboUserSel
  Desc:		update user info
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgUserCfg::OnCbnSelchangeComboUserSel()
{
	UpdateData(TRUE);
	char cTemp[100] = {0};
	int i = 0;
	m_iUserIndex = m_comboUserSel.GetCurSel();
    if (m_iUserIndex < 0)
    {
        m_iUserIndex = 0;
    }
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_pStruUserCfg_V51->struUser[m_iUserIndex].sUserName, MAX_NAMELEN);
	m_csUserName.Format("%s", cTemp);
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_pStruUserCfg_V51->struUser[m_iUserIndex].sPassword, PASSWD_LEN);
	m_csUserPwd.Format("%s", cTemp);
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_pStruUserCfg_V51->struUser[m_iUserIndex].sPassword, PASSWD_LEN);
	m_csVerifyPwd.Format("%s", cTemp);

	if (strlen((char *)m_pStruUserCfg_V51->struUser[m_iUserIndex].struUserIP.byIPv6) != 0 && strlen((char *)m_pStruUserCfg_V51->struUser[m_iUserIndex].struUserIP.byIPv6) != 2)
	{
		m_csUserIP.Format("%s", m_pStruUserCfg_V51->struUser[m_iUserIndex].struUserIP.byIPv6);
	}
	else
	{
		m_csUserIP.Format("%s", m_pStruUserCfg_V51->struUser[m_iUserIndex].struUserIP.sIpV4);
	}
	m_csMacAddr1.Format("%02x",m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[0]);
	m_csMacAddr2.Format("%02x",m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[1]);
	m_csMacAddr3.Format("%02x",m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[2]);
	m_csMacAddr4.Format("%02x",m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[3]);
	m_csMacAddr5.Format("%02x",m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[4]);
	m_csMacAddr6.Format("%02x",m_pStruUserCfg_V51->struUser[m_iUserIndex].byMACAddr[5]);	
	m_bChkLocalPTZCtrl = m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[0];
	m_bChkLocalRecManul = m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[1];
	m_bChkLocalPlayBack = m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[2];
	m_bChkLocalSetParam = m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[3];
	m_bChkLocalShowStat = m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[4];
	m_bChkLocalHighOperation = m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[5];
	m_bChkLocalCameraManage = m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[7];
	m_bChkLocalBackup = m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[8];
	m_bChkLocalReboot = m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[9];
    m_bChkLocalPreview = m_pStruUserCfg_V51->struUser[m_iUserIndex].byLocalRight[10];

	m_bChkRemotePTZCtrl = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[0];
	m_bChkRemoteRecManul = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[1];
	m_bChkRemotePlayBack = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[2];
	m_bChkRemoteSetParam = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[3];
	m_bChkRemoteShowStat = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[4];
	m_bChkRemoteHighOperation = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[5];
	m_bChkRemoteVoiceTalk = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[6];
	m_bChkRemotePreview = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[7];
	m_bChkRemoteAlarm = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[8];
	m_bChkRemoteLocalOut = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[9];
	m_bChkRemoteSerialCtrl = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[10];
	m_bChkNetCameraManage = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[12];
	m_bChkNetReboot = m_pStruUserCfg_V51->struUser[m_iUserIndex].byRemoteRight[13];
    m_bAlarmOn = m_pStruUserCfg_V51->struUser[m_iUserIndex].byAlarmOnRight;
    m_bAlarmOff = m_pStruUserCfg_V51->struUser[m_iUserIndex].byAlarmOffRight;
    m_bBypass = m_pStruUserCfg_V51->struUser[m_iUserIndex].byBypassRight;

    m_bMaterial = m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[0];
    m_bProgram = m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[1];
    m_bSchedule = m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[2];
    m_bMaterialUpload = m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[3];
    m_bProgramAdd = m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[4];
    m_bScheduleAdd = m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[5];
    m_bPlay = m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[6];
    m_bTerminal = m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[7];
    m_bShop = m_pStruUserCfg_V51->struUser[m_iUserIndex].byPublishRight[8];

	m_iSelNetRightType = 0;
	m_iSelLocalRightType = 0;
	m_comboLocalRightType.SetCurSel(m_iSelLocalRightType);
	m_comboNetRightType.SetCurSel(m_iSelNetRightType);

    memset(m_pbLocalChan, 0, sizeof(BOOL)* MAX_CHANNUM_V40);
    for (i=0; i<MAX_CHANNUM_V40; i++)
    {
        if( (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPlaybackRight[i]) != 0xffffffff && (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPlaybackRight[i] < MAX_CHANNUM_V40))
        {
            m_pbLocalChan[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPlaybackRight[i] - 1] = (BYTE)1;
        }
    }

    memset(m_pbRemoteChan, 0, sizeof(BOOL)* MAX_CHANNUM_V40);
	for (i=0; i<MAX_CHANNUM_V40; i++)
	{
		if ((m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPlaybackRight[i] != 0xffffffff) && (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPlaybackRight[i] < MAX_CHANNUM_V40))
		{
			m_pbRemoteChan[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPlaybackRight[i] - 1] = (BYTE)1;
		}
	}
	char szLan[128] = {0};

	m_comboPriority.ResetContent();
 	if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType > 70)
	{
		g_StringLanType(szLan, "普通用户", "Normal User");
		m_comboPriority.AddString(szLan);
		g_StringLanType(szLan, "操作员", "Operator");
		m_comboPriority.AddString(szLan);
		g_StringLanType(szLan, "管理员", "Administrator");
		m_comboPriority.AddString(szLan);
		m_comboPriority.EnableWindow(TRUE);
	}
 	else
 	{
		g_StringLanType(szLan, "普通用户", "Normal User");
		m_comboPriority.AddString(szLan);
		g_StringLanType(szLan, "操作员", "Operator");
		m_comboPriority.AddString(szLan);
		g_StringLanType(szLan, "管理员", "Administrator");
		m_comboPriority.AddString(szLan);
 		m_comboPriority.EnableWindow(FALSE);
 	}

	if (m_iUserIndex != 0 && m_bSuperUserLogin)
	{//Operator can modify these parameters
		//GetDlgItem(IDC_EDIT_USER_NAME)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDIT_USER_PWD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USER_VERIFY_PWD)->EnableWindow(TRUE);
		
		//GetDlgItem(IDC_COMBO_PRIORITY)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_LOCAL_PTZ_CTRL)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_LOCAL_REC_MANUAL)->EnableWindow(TRUE);	
		GetDlgItem(IDC_CHK_LOCAL_SET_PARAM)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_LOCAL_SHOW_STAT)->EnableWindow(TRUE);	
		GetDlgItem(IDC_CHK_LOCAL_HIGH_OPERATION)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_LOCAL_PLAY_BACK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_LOCAL_BACKUP)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_LOCAL_IP_ACCESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_LOCAL_REBOOT)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHK_LOCAL_PREVIEW)->EnableWindow(TRUE);

		GetDlgItem(IDC_CHK_REMOTE_PTZ_CTRL)->EnableWindow(TRUE);	
		GetDlgItem(IDC_CHK_REMOTE_REC_MANUAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_REMOTE_SET_PARAM)->EnableWindow(TRUE);	
		GetDlgItem(IDC_CHK_REMOTE_SHOW_STAT)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_REMOTE_HIGH_OPERATION)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_REMOTE_PLAY_BACK)->EnableWindow(TRUE);	
		GetDlgItem(IDC_CHK_VOICE_TALK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_NET_PREVIEW)->EnableWindow(TRUE);	
		GetDlgItem(IDC_CHK_REMOTE_ALARM)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_REMOTE_CTRL_LOCAL_OUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_REOMTE_SERIAL_CTRL)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_NET_IP_ACCESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_NET_REBOOT)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHK_ALARM_ON)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHK_ALARM_OFF)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHK_BYPASS)->EnableWindow(TRUE);
		m_bLocalEnable = m_bChkLocalPlayBack;
		m_bRemoteEnable = m_bChkRemotePlayBack;
	}
	else
	{
		if (m_bSuperUserLogin)
		{
			if (m_iUserIndex == 0)
			{
			//	GetDlgItem(IDC_EDIT_USER_NAME)->EnableWindow(FALSE);
				g_StringLanType(szLan, "普通用户", "Normal User");
				m_comboPriority.AddString(szLan);
				g_StringLanType(szLan, "操作员", "Operator");
				m_comboPriority.AddString(szLan);
				g_StringLanType(szLan, "管理员", "Administrator");
				m_comboPriority.AddString(szLan);
			}
			else
			{
				//GetDlgItem(IDC_EDIT_USER_NAME)->EnableWindow(TRUE);
			}
		
		//	GetDlgItem(IDC_COMBO_USER_SEL)->EnableWindow(TRUE);
		}
		else
		{
		//	GetDlgItem(IDC_EDIT_USER_NAME)->EnableWindow(FALSE);
		//	GetDlgItem(IDC_COMBO_USER_SEL)->EnableWindow(FALSE);
		}
		GetDlgItem(IDC_COMBO_PRIORITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_LOCAL_PTZ_CTRL)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_LOCAL_REC_MANUAL)->EnableWindow(FALSE);	
		GetDlgItem(IDC_CHK_LOCAL_SET_PARAM)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_LOCAL_SHOW_STAT)->EnableWindow(FALSE);	
		GetDlgItem(IDC_CHK_LOCAL_HIGH_OPERATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_LOCAL_PLAY_BACK)->EnableWindow(FALSE);	
		GetDlgItem(IDC_CHK_LOCAL_BACKUP)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_LOCAL_IP_ACCESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_LOCAL_REBOOT)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHK_LOCAL_PREVIEW)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHK_REMOTE_PTZ_CTRL)->EnableWindow(FALSE);	
		GetDlgItem(IDC_CHK_REMOTE_REC_MANUAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_REMOTE_SET_PARAM)->EnableWindow(FALSE);	
		GetDlgItem(IDC_CHK_REMOTE_SHOW_STAT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_REMOTE_HIGH_OPERATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_REMOTE_PLAY_BACK)->EnableWindow(FALSE);	
		GetDlgItem(IDC_CHK_VOICE_TALK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_NET_PREVIEW)->EnableWindow(FALSE);	
		GetDlgItem(IDC_CHK_REMOTE_ALARM)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_REMOTE_CTRL_LOCAL_OUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_REOMTE_SERIAL_CTRL)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_NET_IP_ACCESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_NET_REBOOT)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHK_ALARM_ON)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHK_ALARM_OFF)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHK_BYPASS)->EnableWindow(FALSE);

		m_bLocalEnable = FALSE;
		m_bRemoteEnable = FALSE;
	}
	m_comboPriority.SetCurSel(m_pStruUserCfg_V51->struUser[m_iUserIndex].byPriority);
	CreateLocalTree();
	CreateRemoteTree();
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedChkLocalPlayBack
  Desc:		local playback channel settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedChkLocalPlayBack()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboLocalRightType();
}

/*********************************************************
Function:	OnBnClickedChkRemotePlayBack
Desc:		远remote playback settings
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedChkRemotePlayBack()
{
	UpdateData(TRUE);
	//ShowNetChanRight(m_iChanCount, m_bChkRemotePlayBack);
	OnCbnSelchangeComboRemoteRightType();
}

/*********************************************************
  Function:	OnBnClickedChkNetPreview
  Desc:		network preview settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedChkNetPreview()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboRemoteRightType();
}


/*********************************************************
  Function:	OnCbnSelchangeComboLocalRightType
  Desc:		Handling after selecting local user right
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgUserCfg::OnCbnSelchangeComboLocalRightType()
{
	SaveLastLocalChan();
	UpdateData(TRUE);
	BOOL bFlag = FALSE;//enable/disable user right modification
	BYTE byRight[MAX_CHANNUM_V40] = {0};
	int i = 0;
	m_iSelLocalRightType = m_comboLocalRightType.GetCurSel();
	switch(m_iSelLocalRightType)
	{
	case 0:
		bFlag = m_bChkLocalPlayBack;
		for (i=0;i<MAX_CHANNUM_V40;i++)
		{
			if (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPlaybackRight[i] != 0xffffffff)
			{
				byRight[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPlaybackRight[i]-1] = (BYTE)1;
			}
		}
		break;
	case 1:
		bFlag = m_bChkLocalRecManul;
		for (i=0;i<MAX_CHANNUM_V40;i++)
		{
			if (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalRecordRight[i] != 0xffffffff)
			{
				byRight[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalRecordRight[i]-1] = (BYTE)1;
			}
		}
		break;
	case 2:
		bFlag = m_bChkLocalPTZCtrl;
		for (i=0;i<MAX_CHANNUM_V40;i++)
		{
			if (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPTZRight[i] != 0xffffffff)
			{
				byRight[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPTZRight[i]-1] = (BYTE)1;
			}
		}
		break;
	case 3:
		bFlag = m_bChkLocalBackup;
		for (i=0;i<MAX_CHANNUM_V40;i++)
		{
			if (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalBackupRight[i] != 0xffffffff)
			{
				byRight[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalBackupRight[i]-1] = (BYTE)1;
			}
		}
		break;			
    case 4:
        bFlag = m_bChkLocalPreview;
        for (i = 0; i < MAX_CHANNUM_V40; i++)
        {
            if (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPreviewRight[i] != 0xffffffff)
            {
                byRight[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPreviewRight[i] - 1] = (BYTE)1;
            }
        }
        break;
	default:
		bFlag = FALSE;
		break;
	}
	if (m_bSuperUserLogin)//user 'admin' login 
	{
		if (m_iUserIndex == 0)
		{//the rights of admin cann't be change
			bFlag = FALSE;
		}
	}
	else
	{
		bFlag = FALSE;
	}
	for (i=0; i<MAX_CHANNUM_V40; i++)
	{
		m_pbLocalChan[i] = byRight[i];
	}
	m_bLocalEnable = bFlag;
	CreateLocalTree();
}

/*********************************************************
Function:	OnCbnSelchangeComboRemoteRightType
Desc:		remote channel operation right selection
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::OnCbnSelchangeComboRemoteRightType()
{
	SaveLastRemoteChan();
	UpdateData(TRUE);
	int i = 0;
	BOOL bFlag = FALSE;
	BYTE byRight[MAX_CHANNUM_V40] = {0};
	m_iSelNetRightType = m_comboNetRightType.GetCurSel();
	switch(m_iSelNetRightType)
	{
	case 0:
		bFlag = m_bChkRemotePlayBack;
		for (i=0;i<MAX_CHANNUM_V40;i++)
		{
			if (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPlaybackRight[i] != 0xffffffff)
			{
				byRight[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPlaybackRight[i]-1] = (BYTE)1;
			}
		}
		break;
	case 1:
		bFlag = m_bChkRemotePreview;
		for (i=0;i<MAX_CHANNUM_V40;i++)
		{
			if (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPreviewRight[i] != 0xffffffff)
			{
				byRight[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPreviewRight[i]-1] = (BYTE)1;
			}
		}
		break;
	case 2:
		bFlag = m_bChkRemoteRecManul;
		for (i=0;i<MAX_CHANNUM_V40;i++)
		{
			if (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetRecordRight[i] != 0xffffffff)
			{
				byRight[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetRecordRight[i]-1] = (BYTE)1;
			}
		}
		break;
	case 3:
		bFlag = m_bChkRemotePTZCtrl;
		for (i=0;i<MAX_CHANNUM_V40;i++)
		{
			if (m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPTZRight[i] != 0xffffffff)
			{
				byRight[m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPTZRight[i]-1] = (BYTE)1;
			}
		}
		break;
	default:
		bFlag = FALSE;
		break;
	}
	if (m_bSuperUserLogin)
	{
		if (m_iUserIndex == 0)
		{
			bFlag = FALSE;
		}
	}
	else
	{
		bFlag = FALSE;
	}

	for (i=0; i<MAX_CHANNUM_V40; i++)
	{
		m_pbRemoteChan[i] = byRight[i];
	}
	m_bRemoteEnable = bFlag;
	CreateRemoteTree();
}

/*********************************************************
Function:	OnBnClickedChkLocalRecManual
Desc:		switchlocal record status
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedChkLocalRecManual()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboLocalRightType();
}

/*********************************************************
Function:	OnBnClickedChkLocalPtzCtrl
Desc:		switch local PTZ status
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedChkLocalPtzCtrl()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboLocalRightType();
}

/*********************************************************
Function:	OnBnClickedChkLocalBackup
Desc:		switch local backup status
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedChkLocalBackup()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboLocalRightType();
}

/*********************************************************
Function:	OnBnClickedChkLocalRecManual
Desc:		Confirm local channel user right settings
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedBtnLocalChanOk()
{
	UpdateData(TRUE);
	BYTE byRight[MAX_CHANNUM_V40] = {0};
	int i = 0,j = 0;
    
	switch(m_iSelLocalRightType)
	{
	case 0:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPlaybackRight,0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
        for (i=0; i<MAX_CHANNUM_V40; i++)
        {
            
            if (m_pbLocalChan[i] == (BYTE)1)
            {
                m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPlaybackRight[j++] = i+1;
            }
        }
		break;
	case 1:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalRecordRight,0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
        for (i=0; i<MAX_CHANNUM_V40; i++)
        {		
            if (m_pbLocalChan[i] == (BYTE)1)
            {
                m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalRecordRight[j++] = i+1;
            }
		}
		break;
	case 2:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPTZRight,0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);

		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
            if (m_pbLocalChan[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPTZRight[j++] = i+1;
			}
		}
	
		break;
	case 3:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalBackupRight,0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);

		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
            if (m_pbLocalChan[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalBackupRight[j++] = i+1;
			}
		}
		break;
    case 4:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPreviewRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);

        for (i = 0; i < MAX_CHANNUM_V40; i++)
        {
            if (m_pbLocalChan[i] == (BYTE)1)
            {
                m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPreviewRight[j++] = i + 1;
            }
        }
        break;
	default:
		break;
	}
	GetDlgItem(IDC_BTN_LOCAL_CHAN_OK)->EnableWindow(FALSE);
}


/*********************************************************
Function:	SaveLastLocalChan
Desc:		Save the channels when ComboBox selection changed
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::SaveLastLocalChan()
{
    UpdateData(TRUE);
	BYTE byRight[MAX_CHANNUM_V40] = {0};
	int i = 0,j = 0;
	for (i=0; i<MAX_CHANNUM_V40; i++)
	{
		byRight[i] = (BYTE)m_pbLocalChan[i];
	}
	switch(m_iSelLocalRightType)
	{
	case 0:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPlaybackRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPlaybackRight[j++] = i+1;
			}
		}
       
		break;
	case 1:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalRecordRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);

		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalRecordRight[j++] = i+1;
			}
		}
		break;
	case 2:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPTZRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPTZRight[j++] = i+1;
			}
		}
		break;
	case 3:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalBackupRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalBackupRight[j++] = i+1;	 
			}
		}
	
		break;	
    case 4:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPreviewRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
        for (i = 0; i < MAX_CHANNUM_V40; i++)
        {
            if (byRight[i] == (BYTE)1)
            {
                m_pStruUserCfg_V51->struUser[m_iUserIndex].dwLocalPreviewRight[j++] = i + 1;
            }
        }

        break;
	default:
		break;
	}
}

/*********************************************************
Function:	OnBnClickedBtnRemoteChanOk
Desc:		Confirm remote channel user right settings
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedBtnRemoteChanOk()
{
	UpdateData(TRUE);
	BYTE byRight[MAX_CHANNUM_V40] = {0};
	int i = 0,j = 0;
	for (i=0; i<MAX_CHANNUM_V40; i++)
	{
		byRight[i] = (BYTE)m_pbRemoteChan[i];
	}
	switch(m_iSelNetRightType)
	{
	case 0:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPlaybackRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPlaybackRight[j++] = i+1;
			}
		}
		break;
	case 1:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPreviewRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPreviewRight[j++] = i+1;
			}
		}
		break;
    case 2:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetRecordRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetRecordRight[j++] = i+1;
			}
		}
		break;
	case 3:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPTZRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPTZRight[j++] = i+1;
			}
		}
		break;
	default:
		break;
	}
	GetDlgItem(IDC_BTN_REMOTE_CHAN_OK)->EnableWindow(FALSE);
}


/*********************************************************
Function:	SaveLastRemoteChan
Desc:		Save the channels when ComboBox sel changed
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::SaveLastRemoteChan()
{
	UpdateData(TRUE);
	BYTE byRight[MAX_CHANNUM_V40] = {0};
	int i = 0,j = 0;
	for (i=0; i<MAX_CHANNUM_V40; i++)
	{
		byRight[i] = (BYTE)m_pbRemoteChan[i];
	}
	switch(m_iSelNetRightType)
	{
	case 0:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPlaybackRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPlaybackRight[j++] = i+1;
			}
		}
		break;
	case 1:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPreviewRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPreviewRight[j++] = i+1;
			}
		}
		break;
	case 2:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetRecordRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetRecordRight[j++] = i+1;
			}
		}
		break;
	case 3:
        memset(m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPTZRight, 0xffffffff, sizeof(DWORD)*MAX_CHANNUM_V40);
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (byRight[i] == (BYTE)1)
			{
				m_pStruUserCfg_V51->struUser[m_iUserIndex].dwNetPTZRight[j++] = i+1;
			}
		}
		break;
	default:
		break;
	}
}


/*********************************************************
Function:	OnBnClickedChkRemoteRecManual
Desc:		remote manual record user right
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedChkRemoteRecManual()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboRemoteRightType();
}

/*********************************************************
Function:	OnBnClickedChkRemotePtzCtrl
Desc:		remote PTZ control user right
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgUserCfg::OnBnClickedChkRemotePtzCtrl()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboRemoteRightType();
}


/*********************************************************
  Function:	CreateLocalTree
  Desc:		local user right settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgUserCfg::CreateLocalTree(void)
{
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
    if (m_iDeviceIndex < 0)
    {
        return;
    }
    DWORD dwStartDChanNo = 33;
    if (g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40 != NULL)
    {
        dwStartDChanNo = g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan;
    }
    
    
    if (m_iChanCount <= 0)
	{
		m_treeLocalChan.EnableWindow(FALSE);
		return;
	}
	m_treeLocalChan.DeleteAllItems();
    for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
    {
        if (i < g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum)
        {
            if (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
            {
                strTemp.Format(ANALOG_C_FORMAT, i + g_struDeviceInfo[m_iDeviceIndex].iStartChan);
                hChanItem = m_treeLocalChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
                m_treeLocalChan.SetItemData(hChanItem, 0 * 1000 + i);
                if (1 == m_pbLocalChan[g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO - 1])
                {
                    m_treeLocalChan.SetCheck(hChanItem, TRUE);
                }
            }

        }
        else if (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable /*&& m_iSelNetRightType != 3*/)
        {
            strTemp.Format(DIGITAL_C_FORMAT, (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO + g_struDeviceInfo[m_iDeviceIndex].iStartChan - dwStartDChanNo));
            hChanItem = m_treeLocalChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
            m_treeLocalChan.SetItemData(hChanItem, 1 * 1000 + i);
            if (1 == m_pbLocalChan[g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO - 1])
            {
                m_treeLocalChan.SetCheck(hChanItem, TRUE);
            }
        }
    }

	if (g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum)
	{
		for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum && i < 16; i++)
		{
			if (g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].bEnable)
            {
				strTemp.Format(MIRROR_C_FORMAT, i + 1);
                hChanItem =  m_treeLocalChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
                m_treeLocalChan.SetItemData(hChanItem, 0 * 1000 + i + MIRROR_CHAN_INDEX);
				if (1 == m_pbLocalChan[g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChannelNO - 1])
                {
                    m_treeLocalChan.SetCheck(hChanItem, TRUE);
                }
			}
		}
	}
	m_treeLocalChan.Expand(m_treeLocalChan.GetRootItem(),TVE_EXPAND);	
	m_treeLocalChan.SelectItem(hChanItem);

   // g_CreateChannelTree(m_treeLocalChan,m_iDeviceIndex,m_pbLocalChan);
    UpdateData(FALSE);
	//m_treeLocalChan.EnableWindow(m_bLocalEnable);
}

/*********************************************************
  Function:	CreateRemoteTree
  Desc:		remote user right settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgUserCfg::CreateRemoteTree(void)
{
    BYTE byRight[MAX_CHANNUM_V40] = {0};
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;

	if (m_iDeviceIndex < 0)
	{
		return;
	}
	DWORD dwStartDChanNo = 0;
    if (g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40 != NULL)
    {
        dwStartDChanNo = g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan;
    }
   
	if (m_iChanCount <= 0)
	{
		m_treeRemoteChan.EnableWindow(FALSE);
		return;
	}	
	m_treeRemoteChan.DeleteAllItems();
    
    for(i =0; i< MAX_CHANNUM_V40; i++)
    {
        byRight[i] = (BYTE)m_pbRemoteChan[i];
    }
	
    for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
	{
        if (i < g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum)
        {
            if (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
            {
                strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_iDeviceIndex].iStartChan);
                hChanItem =  m_treeRemoteChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
                m_treeRemoteChan.SetItemData(hChanItem, 0*1000 + i);	
                if (1 == m_pbRemoteChan[g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO -1])
                {
                    m_treeRemoteChan.SetCheck(hChanItem, TRUE);
                }
            }
            
        }
        else if (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable /*&& m_iSelNetRightType != 3*/)
        {
            strTemp.Format(DIGITAL_C_FORMAT, (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO+g_struDeviceInfo[m_iDeviceIndex].iStartChan-dwStartDChanNo));
            hChanItem =  m_treeRemoteChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
            m_treeRemoteChan.SetItemData(hChanItem, 1*1000 + i);	
            if (1 == m_pbRemoteChan[g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO -1])
            {
                m_treeRemoteChan.SetCheck(hChanItem, TRUE);
            }
        }
	}
	if (g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum)
	{
		for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum && i < 16; i++)
		{
			if (g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].bEnable)
            {
				strTemp.Format(MIRROR_C_FORMAT, i + 1);
                hChanItem =  m_treeRemoteChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
                m_treeRemoteChan.SetItemData(hChanItem, 0 * 1000 + i + MIRROR_CHAN_INDEX);
				if (1 == m_pbRemoteChan[g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChannelNO - 1])
                {
                    m_treeRemoteChan.SetCheck(hChanItem, TRUE);
                }
			}
		}
	}
	m_treeRemoteChan.Expand(m_treeRemoteChan.GetRootItem(),TVE_EXPAND);
	m_treeRemoteChan.SelectItem(hChanItem);
   // g_CreateChannelTree(m_treeRemoteChan,m_iDeviceIndex,m_pbRemoteChan);
//	m_treeRemoteChan.EnableWindow(m_bRemoteEnable);
    UpdateData(FALSE);
}

/*********************************************************
  Function:	OnClickTreeLocalChan
  Desc:		change the check status of the channel for local right
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CSubDlgUserCfg::OnClickTreeLocalChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
  	UpdateData(TRUE);
    if (m_csUserName.GetLength() == 0)
    {
        return;
    }
// 	DWORD dwPos = GetMessagePos();
// 	CPoint point( LOWORD(dwPos), HIWORD(dwPos));
// 	point.x -=2;
// 	m_treeLocalChan.ScreenToClient(&point);
// 	CPoint pt(0,0);
// 	CRect rc(0,0,0,0);
// 	GetCursorPos(&pt);
// 	GetDlgItem(IDC_TREE_LOCAL_CHAN)->GetWindowRect(&rc);
// 	ScreenToClient(&rc);
// 	ScreenToClient(&pt);
// 	pt.x = pt.x - rc.left - 2;
// 	pt.y = pt.y - rc.top - 2;

    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeLocalChan.ScreenToClient(&pt);
    GetDlgItem(IDC_TREE_LOCAL_CHAN)->GetWindowRect(&rc);
    m_treeLocalChan.ScreenToClient(&rc);
    
    pt.x = pt.x - rc.left;
  	pt.y = pt.y - rc.top;

	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeLocalChan.HitTest(pt, &uFlag);	

	if (NULL == hSelect) 
	{
		return;
	}

	m_treeLocalChan.SelectItem(hSelect);
	DWORD dwIndex = m_treeLocalChan.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeLocalChan.GetCheck(hSelect);
	if (!m_bLocalEnable)
	{
		if (uFlag == LVHT_TOLEFT)
		{
			m_treeLocalChan.SetCheck(hSelect, !bCheck);
		}
		return;
	}
	if (g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum && dwIndex + 1 > g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum)
	{
		m_pbLocalChan[g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[dwIndex - MIRROR_CHAN_INDEX].iChannelNO-1] = !bCheck;
	}
	else
	{
        m_pbLocalChan[g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[dwIndex].iChannelNO - 1] = !bCheck;
	}
	
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeLocalChan.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeLocalChan.SetCheck(hSelect, bCheck);
	}

	GetDlgItem(IDC_BTN_LOCAL_CHAN_OK)->EnableWindow(m_bLocalEnable);
	*pResult = 0;
}

/*********************************************************
  Function:	OnClickTreeRemoteChan
  Desc:		change the check status of the channel for remote right	
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CSubDlgUserCfg::OnClickTreeRemoteChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
 	CRect rc(0,0,0,0);
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
	DWORD dwIndex = m_treeRemoteChan.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeRemoteChan.GetCheck(hSelect);
	m_treeRemoteChan.SetCheck(hSelect, !uFlag);
	if (!m_bRemoteEnable)//current remote right is disalbe, don't change the status when click
	{
		if (uFlag == LVHT_TOLEFT)//0x0040, 
		{
			m_treeRemoteChan.SetCheck(hSelect, !uFlag);
 		}
		return;
	}

	if (g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum && dwIndex + 1 > g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum)
	{
		m_pbRemoteChan[g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[dwIndex - MIRROR_CHAN_INDEX].iChannelNO-1] = !bCheck;
	}
	else
	{
		m_pbRemoteChan[g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[dwIndex].iChannelNO-1] = !bCheck;
	}
	
	
	if (uFlag != LVHT_TOLEFT)//0x0040
	{
		m_treeRemoteChan.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeRemoteChan.SetCheck(hSelect, bCheck);
	}

	GetDlgItem(IDC_BTN_REMOTE_CHAN_OK)->EnableWindow(m_bRemoteEnable);
	*pResult = 0;
}

/*********************************************************
  Function:	OnPaint
  Desc:		paint the tree
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CSubDlgUserCfg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (m_bGetUserParams)
	{
		CreateLocalTree();
		CreateRemoteTree();
	}
}

void CSubDlgUserCfg::OnButtonSyncIpcPasswd() 
{
	// TODO: Add your control notification handler code here

    NET_DVR_STD_CONTROL struControl = {0};

    if (!NET_DVR_STDControl(m_lLoginID, NET_DVR_SYNC_IPC_PASSWD, &struControl))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SYNC_IPC_PASSWD");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SYNC_IPC_PASSWD");
    }
}

void CSubDlgUserCfg::OnBnClickedChkLocalPreview()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    OnCbnSelchangeComboLocalRightType();
}

