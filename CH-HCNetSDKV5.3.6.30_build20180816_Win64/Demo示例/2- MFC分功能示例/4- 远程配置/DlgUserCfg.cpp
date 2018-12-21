// DlgUserCfg.cpp : implementation file
//
/**********************************************************
FileName:    DlgUserCfg.cpp
Description: 用户信息配置      
Date:        
Note: 		<全局>结构体,宏见GeneralDef.h, 全局变量,函数见config.cpp   
Modification History:      
<version>   <time>         <desc>

***********************************************************/

#include "stdafx.h"
#include "config.h"
#include "DlgUserCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUserCfg dialog


CDlgUserCfg::CDlgUserCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUserCfg::IDD, pParent)
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
{
	memset(&m_struUserCfg, 0, sizeof(m_struUserCfg));
	memset(m_bLocalChan, 0, sizeof(BOOL)*MAX_CHANNUM_V30);
	memset(m_bRemoteChan, 0, sizeof(BOOL)*MAX_CHANNUM_V30);
}


void CDlgUserCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUserCfg)
	DDX_Control(pDX, IDC_COMBO_PRIORITY, m_comboPriority);
	DDX_Control(pDX, IDC_TREE_REMOTE_CHAN, m_treeRemoteChan);
	DDX_Control(pDX, IDC_TREE_LOCAL_CHAN, m_treeLocalChan);
	DDX_Control(pDX, IDC_COMBO_USER_SEL, m_comboUserSel);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_USER_PWD, m_csUserPwd);
	DDX_Text(pDX, IDC_EDIT_USER_VERIFY_PWD, m_csVerifyPwd);
	DDX_Text(pDX, IDC_EDIT_USER_IP, m_csUserIP);
	DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR1, m_csMacAddr1);
	DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR2, m_csMacAddr2);
	DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR3, m_csMacAddr3);
	DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR4, m_csMacAddr4);
	DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR5, m_csMacAddr5);
	DDX_Text(pDX, IDC_EDIT_USER_MAC_ADDR6, m_csMacAddr6);
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUserCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgUserCfg)
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUserCfg message handlers


/*********************************************************
  Function:	CheckInitParam
  Desc:		校验并初始化用户配置,在树设备节点(序列号)更新时重新初始化并获取对应的用户配置
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgUserCfg::CheckInitParam()
{
	int iDeviceIndex = 0;
	if (iDeviceIndex == -1)
	{
		return FALSE;
	}
	if (g_struDeviceInfo[iDeviceIndex].lLoginID < 0)
	{
		m_iChanCount = 0;
		return FALSE;
	}
	
	m_iDeviceIndex = iDeviceIndex;
	m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_lStartChannel = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
	m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	if (strcmp(g_struDeviceInfo[m_iDeviceIndex].chLoginUserName, "admin")==0)
	{
		m_bSuperUserLogin = TRUE;
	}
	else
	{
		m_bSuperUserLogin = FALSE;
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
	
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_USERCFG_V30, 0, &m_struUserCfg, sizeof(NET_DVR_USER_V30), &dwReturned))
	{
		//g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_USERCFG_V30");
		char szLan[128] = {0};
		g_StringLanType(szLan, "获取用户参数失败！", "Get User Parameter failed");
		AfxMessageBox(szLan);
		return FALSE;
	}
	m_bGetUserParams = TRUE;

	return TRUE;
}

/*********************************************************
  Function:	CurCfgUpdate
  Desc:		当前设备对应的信息的刷新
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUserCfg::CurCfgUpdate()
{
	if (!CheckInitParam())
	{
		m_iDeviceIndex = -1;	
		EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}
	EnableWindow(TRUE);

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
			memcpy(cTemp, m_struUserCfg.struUser[i].sUserName, MAX_NAMELEN);
			csUserName.Format("%s", cTemp);
			if (strcmp(csUserName, g_struDeviceInfo[m_iDeviceIndex].chLoginUserName) == 0)
			{
				break;
			}
		}
		m_iUserIndex = i;
		m_comboUserSel.SetCurSel(m_iUserIndex);
	}

	OnCbnSelchangeComboUserSel();
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnUserOk
  Desc:		用户配置参数确定
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedBtnUserOk()
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}

	UpdateData(TRUE);
	int i = 0;
	strncpy((char *)m_struUserCfg.struUser[m_iUserIndex].sUserName, m_csUserName, MAX_NAMELEN);
	if (strcmp(m_csUserPwd,m_csVerifyPwd) != 0)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "密码与确认密码不一致", "Password and Confirm Password inconsistent");
		AfxMessageBox(szLan);
		return;
	}
	int iLength = strlen(m_csUserPwd);
	iLength = iLength>PASSWD_LEN ? PASSWD_LEN:iLength;
	char temp[PASSWD_LEN];
	strncpy(temp,m_csUserPwd,PASSWD_LEN);

	strncpy((char *)m_struUserCfg.struUser[m_iUserIndex].sPassword, m_csUserPwd,PASSWD_LEN);
	strncpy((char *)m_struUserCfg.struUser[m_iUserIndex].struUserIP.sIpV4, m_csUserIP,16);
	int nVal;
	sscanf(m_csMacAddr1, "%02x", &nVal);
	m_struUserCfg.struUser[m_iUserIndex].byMACAddr[0] = (BYTE)nVal;
	sscanf(m_csMacAddr2, "%02x", &nVal);
	m_struUserCfg.struUser[m_iUserIndex].byMACAddr[1] = (BYTE)nVal;
	sscanf(m_csMacAddr3, "%02x", &nVal);
	m_struUserCfg.struUser[m_iUserIndex].byMACAddr[2] = (BYTE)nVal;
	sscanf(m_csMacAddr4, "%02x", &nVal);
	m_struUserCfg.struUser[m_iUserIndex].byMACAddr[3] = (BYTE)nVal;
	sscanf(m_csMacAddr5, "%02x", &nVal);
	m_struUserCfg.struUser[m_iUserIndex].byMACAddr[4] = (BYTE)nVal;
	sscanf(m_csMacAddr6, "%02x", &nVal);
	m_struUserCfg.struUser[m_iUserIndex].byMACAddr[5] = (BYTE)nVal;

	m_struUserCfg.struUser[m_iUserIndex].byPriority = m_comboPriority.GetCurSel();
	m_struUserCfg.struUser[m_iUserIndex].byLocalRight[0] = m_bChkLocalPTZCtrl;
	m_struUserCfg.struUser[m_iUserIndex].byLocalRight[1] = m_bChkLocalRecManul;
	m_struUserCfg.struUser[m_iUserIndex].byLocalRight[2] = m_bChkLocalPlayBack;
	m_struUserCfg.struUser[m_iUserIndex].byLocalRight[3] = m_bChkLocalSetParam;
	m_struUserCfg.struUser[m_iUserIndex].byLocalRight[4] = m_bChkLocalShowStat;
	m_struUserCfg.struUser[m_iUserIndex].byLocalRight[5] = m_bChkLocalHighOperation;
	m_struUserCfg.struUser[m_iUserIndex].byLocalRight[7] = m_bChkLocalCameraManage;
	m_struUserCfg.struUser[m_iUserIndex].byLocalRight[8] = m_bChkLocalBackup;
	m_struUserCfg.struUser[m_iUserIndex].byLocalRight[9] = m_bChkLocalReboot;

	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[0] = m_bChkRemotePTZCtrl;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[1] = m_bChkRemoteRecManul;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[2] = m_bChkRemotePlayBack;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[3] = m_bChkRemoteSetParam;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[4] = m_bChkRemoteShowStat;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[5] = m_bChkRemoteHighOperation;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[6] = m_bChkRemoteVoiceTalk;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[7] = m_bChkRemotePreview;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[8] = m_bChkRemoteAlarm;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[9] = m_bChkRemoteLocalOut;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[10] = m_bChkRemoteSerialCtrl;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[12] = m_bChkNetCameraManage;
	m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[13] = m_bChkLocalReboot;
	//OnBnClickedBtnLocalChanOk();
//	OnBnClickedBtnRemoteChanOk();

	m_bSetUserParams = TRUE;
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_USERCFG_V30, 0,&(m_struUserCfg), sizeof(NET_DVR_USER_V30)))
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "设置用户参数失败！", "Set User Parameter failed");
		AfxMessageBox(szLan);	
	}
}

/*********************************************************
  Function:	OnCbnSelchangeComboUserSel
  Desc:		用户选择响应函数,更新对应用户的数据
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUserCfg::OnCbnSelchangeComboUserSel()
{
	UpdateData(TRUE);
	char cTemp[100] = {0};
	int i = 0;
	m_iUserIndex = m_comboUserSel.GetCurSel();
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struUserCfg.struUser[m_iUserIndex].sUserName, MAX_NAMELEN);
	m_csUserName.Format("%s", cTemp);
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struUserCfg.struUser[m_iUserIndex].sPassword, PASSWD_LEN);
	m_csUserPwd.Format("%s", cTemp);
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struUserCfg.struUser[m_iUserIndex].sPassword, PASSWD_LEN);
	m_csVerifyPwd.Format("%s", cTemp);

	m_csUserIP.Format("%s",m_struUserCfg.struUser[m_iUserIndex].struUserIP.sIpV4);
	m_csMacAddr1.Format("%02x",m_struUserCfg.struUser[m_iUserIndex].byMACAddr[0]);
	m_csMacAddr2.Format("%02x",m_struUserCfg.struUser[m_iUserIndex].byMACAddr[1]);
	m_csMacAddr3.Format("%02x",m_struUserCfg.struUser[m_iUserIndex].byMACAddr[2]);
	m_csMacAddr4.Format("%02x",m_struUserCfg.struUser[m_iUserIndex].byMACAddr[3]);
	m_csMacAddr5.Format("%02x",m_struUserCfg.struUser[m_iUserIndex].byMACAddr[4]);
	m_csMacAddr6.Format("%02x",m_struUserCfg.struUser[m_iUserIndex].byMACAddr[5]);	
	m_bChkLocalPTZCtrl = m_struUserCfg.struUser[m_iUserIndex].byLocalRight[0];
	m_bChkLocalRecManul = m_struUserCfg.struUser[m_iUserIndex].byLocalRight[1];
	m_bChkLocalPlayBack = m_struUserCfg.struUser[m_iUserIndex].byLocalRight[2];
	m_bChkLocalSetParam = m_struUserCfg.struUser[m_iUserIndex].byLocalRight[3];
	m_bChkLocalShowStat = m_struUserCfg.struUser[m_iUserIndex].byLocalRight[4];
	m_bChkLocalHighOperation = m_struUserCfg.struUser[m_iUserIndex].byLocalRight[5];
	m_bChkLocalCameraManage = m_struUserCfg.struUser[m_iUserIndex].byLocalRight[7];
	m_bChkLocalBackup = m_struUserCfg.struUser[m_iUserIndex].byLocalRight[8];
	m_bChkLocalReboot = m_struUserCfg.struUser[m_iUserIndex].byLocalRight[9];

	m_bChkRemotePTZCtrl = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[0];
	m_bChkRemoteRecManul = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[1];
	m_bChkRemotePlayBack = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[2];
	m_bChkRemoteSetParam = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[3];
	m_bChkRemoteShowStat = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[4];
	m_bChkRemoteHighOperation = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[5];
	m_bChkRemoteVoiceTalk = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[6];
	m_bChkRemotePreview = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[7];
	m_bChkRemoteAlarm = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[8];
	m_bChkRemoteLocalOut = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[9];
	m_bChkRemoteSerialCtrl = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[10];
	m_bChkNetCameraManage = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[12];
	m_bChkNetReboot = m_struUserCfg.struUser[m_iUserIndex].byRemoteRight[13];
	m_iSelNetRightType = 0;
	m_iSelLocalRightType = 0;
	m_comboLocalRightType.SetCurSel(m_iSelLocalRightType);
	m_comboNetRightType.SetCurSel(m_iSelNetRightType);
	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		m_bLocalChan[i] = m_struUserCfg.struUser[m_iUserIndex].byLocalPlaybackRight[i];
	}
	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		m_bRemoteChan[i] = m_struUserCfg.struUser[m_iUserIndex].byNetPlaybackRight[i];
	}
	char szLan[128] = {0};

	m_comboPriority.ResetContent();
	if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType > 70)
	{
		g_StringLanType(szLan, "普通用户", "Normal User");
		m_comboPriority.AddString(szLan);
		g_StringLanType(szLan, "管理员", "Administrator");
		m_comboPriority.AddString(szLan);
		m_comboPriority.EnableWindow(TRUE);
	}
	else
	{
		m_comboPriority.EnableWindow(FALSE);
	}

	if (m_iUserIndex != 0 && m_bSuperUserLogin)
	{//普通用户权限可以修改下列参数
		GetDlgItem(IDC_EDIT_USER_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_USER_PWD)->EnableWindow(TRUE);
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
		m_bLocalEnable = m_bChkLocalPlayBack;
		m_bRemoteEnable = m_bChkRemotePlayBack;
	}
	else
	{
		if (m_bSuperUserLogin)
		{
			if (m_iUserIndex == 0)
			{
				GetDlgItem(IDC_EDIT_USER_NAME)->EnableWindow(FALSE);
				g_StringLanType(szLan, "管理员", "Administrator");
				m_comboPriority.AddString(szLan);
			}
			else
			{
				GetDlgItem(IDC_EDIT_USER_NAME)->EnableWindow(TRUE);
			}
		
			GetDlgItem(IDC_COMBO_USER_SEL)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_EDIT_USER_NAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_USER_SEL)->EnableWindow(FALSE);
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
		m_bLocalEnable = FALSE;
		m_bRemoteEnable = FALSE;
	}
	m_comboPriority.SetCurSel(m_struUserCfg.struUser[m_iUserIndex].byPriority);
	
	CreateLocalTree();
	CreateRemoteTree();
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedChkLocalPlayBack
  Desc:		本地回放通道设置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedChkLocalPlayBack()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboLocalRightType();
}

/*********************************************************
Function:	OnBnClickedChkRemotePlayBack
Desc:		远程回放设置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedChkRemotePlayBack()
{
	UpdateData(TRUE);
	//ShowNetChanRight(m_iChanCount, m_bChkRemotePlayBack);
	OnCbnSelchangeComboRemoteRightType();
}

/*********************************************************
  Function:	OnBnClickedChkNetPreview
  Desc:		网络预览通道设置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedChkNetPreview()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboRemoteRightType();
}


/*********************************************************
  Function:	OnCbnSelchangeComboLocalRightType
  Desc:		本地权限的类型选择后相应处理
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUserCfg::OnCbnSelchangeComboLocalRightType()
{
	UpdateData(TRUE);
	BOOL bFlag = FALSE;//权限可更改使能标志
	BYTE byRight[MAX_CHANNUM_V30] = {0};
	int i = 0;
	m_iSelLocalRightType = m_comboLocalRightType.GetCurSel();
	switch(m_iSelLocalRightType)
	{
	case 0:
		bFlag = m_bChkLocalPlayBack;
		memcpy(byRight, &(m_struUserCfg.struUser[m_iUserIndex].byLocalPlaybackRight[0]), MAX_CHANNUM_V30);
		break;
	case 1:
		bFlag = m_bChkLocalRecManul;
		memcpy(byRight, &(m_struUserCfg.struUser[m_iUserIndex].byLocalRecordRight[0]), MAX_CHANNUM_V30);
		break;
	case 2:
		bFlag = m_bChkLocalPTZCtrl;
		memcpy(byRight, &(m_struUserCfg.struUser[m_iUserIndex].byLocalPTZRight[0]), MAX_CHANNUM_V30);
		break;
	case 3:
		bFlag = m_bChkLocalBackup;
		memcpy(byRight, &(m_struUserCfg.struUser[m_iUserIndex].byLocalBackupRight[0]), MAX_CHANNUM_V30);
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
	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		m_bLocalChan[i] = byRight[i];
	}
	m_bLocalEnable = bFlag;
	CreateLocalTree();
}

/*********************************************************
Function:	OnCbnSelchangeComboRemoteRightType
Desc:		远程可以控制通道的类型选择
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUserCfg::OnCbnSelchangeComboRemoteRightType()
{
	UpdateData(TRUE);
	int i = 0;
	BOOL bFlag = FALSE;
	BYTE byRight[MAX_CHANNUM_V30] = {0};
	m_iSelNetRightType = m_comboNetRightType.GetCurSel();
	switch(m_iSelNetRightType)
	{
	case 0:
		bFlag = m_bChkRemotePlayBack;
		memcpy(byRight, &(m_struUserCfg.struUser[m_iUserIndex].byNetPlaybackRight[0]), MAX_CHANNUM_V30);
		break;
	case 1:
		bFlag = m_bChkRemotePreview;
		memcpy(byRight, &(m_struUserCfg.struUser[m_iUserIndex].byNetPreviewRight[0]), MAX_CHANNUM_V30);
		break;
	case 2:
		bFlag = m_bChkRemoteRecManul;
		memcpy(byRight, &(m_struUserCfg.struUser[m_iUserIndex].byNetRecordRight[0]), MAX_CHANNUM_V30);
		break;
	case 3:
		bFlag = m_bChkRemotePTZCtrl;
		memcpy(byRight, &(m_struUserCfg.struUser[m_iUserIndex].byNetPTZRight[0]), MAX_CHANNUM_V30);
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

	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		m_bRemoteChan[i] = byRight[i];
	}
	m_bRemoteEnable = bFlag;
	CreateRemoteTree();
}

/*********************************************************
Function:	OnBnClickedChkLocalRecManual
Desc:		本地录像状态切换
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedChkLocalRecManual()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboLocalRightType();
}

/*********************************************************
Function:	OnBnClickedChkLocalPtzCtrl
Desc:		本地云台状态切换
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedChkLocalPtzCtrl()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboLocalRightType();
}

/*********************************************************
Function:	OnBnClickedChkLocalBackup
Desc:		本地备份状态切换
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedChkLocalBackup()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboLocalRightType();
}

/*********************************************************
Function:	OnBnClickedChkLocalRecManual
Desc:		确定当前本地控制类型的通道可控制状态配置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedBtnLocalChanOk()
{
	UpdateData(TRUE);
	BYTE byRight[MAX_CHANNUM_V30] = {0};
	int i = 0;
	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		byRight[i] = m_bLocalChan[i];
	}
	switch(m_iSelLocalRightType)
	{
	case 0:
		memcpy(&(m_struUserCfg.struUser[m_iUserIndex].byLocalPlaybackRight[0]), &(byRight[0]), MAX_CHANNUM_V30);
		break;
	case 1:
		memcpy(&(m_struUserCfg.struUser[m_iUserIndex].byLocalRecordRight[0]), &(byRight[0]), MAX_CHANNUM_V30);
		break;
	case 2:
		memcpy(&(m_struUserCfg.struUser[m_iUserIndex].byLocalPTZRight[0]), &(byRight[0]), MAX_CHANNUM_V30);
		break;
	case 3:
		memcpy(&(m_struUserCfg.struUser[m_iUserIndex].byLocalBackupRight[0]), &(byRight[0]), MAX_CHANNUM_V30);
		break;	
	default:
		break;
	}
	GetDlgItem(IDC_BTN_LOCAL_CHAN_OK)->EnableWindow(FALSE);
}

/*********************************************************
Function:	OnBnClickedBtnRemoteChanOk
Desc:		确定当前远程控制类型的通道可控制状态配置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedBtnRemoteChanOk()
{
	UpdateData(TRUE);
	BYTE byRight[MAX_CHANNUM_V30] = {0};
	int i = 0;
	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		byRight[i] = m_bRemoteChan[i];
	}
	switch(m_iSelNetRightType)
	{
	case 0:
		memcpy(&(m_struUserCfg.struUser[m_iUserIndex].byNetPlaybackRight[0]), &(byRight[0]), MAX_CHANNUM_V30);
		break;
	case 1:
		memcpy(&(m_struUserCfg.struUser[m_iUserIndex].byNetPreviewRight[0]), &(byRight[0]), MAX_CHANNUM_V30);
		break;
	case 2:
		memcpy(&(m_struUserCfg.struUser[m_iUserIndex].byNetRecordRight[0]), &(byRight[0]), MAX_CHANNUM_V30);
		break;
	case 3:
		memcpy(&(m_struUserCfg.struUser[m_iUserIndex].byNetPTZRight[0]), &(byRight[0]), MAX_CHANNUM_V30);
		break;
	default:
		break;
	}
	GetDlgItem(IDC_BTN_REMOTE_CHAN_OK)->EnableWindow(FALSE);
}

/*********************************************************
Function:	OnBnClickedChkRemoteRecManual
Desc:		远程手动录像权限设置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedChkRemoteRecManual()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboRemoteRightType();
}

/*********************************************************
Function:	OnBnClickedChkRemotePtzCtrl
Desc:		远程云台控制权限设置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUserCfg::OnBnClickedChkRemotePtzCtrl()
{
	UpdateData(TRUE);
	OnCbnSelchangeComboRemoteRightType();
}


/*********************************************************
  Function:	CreateLocalTree
  Desc:		创建本地通道权限树
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUserCfg::CreateLocalTree(void)
{
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	if (m_iChanCount <= 0)
	{
		m_treeLocalChan.EnableWindow(FALSE);
		return;
	}
	m_treeLocalChan.DeleteAllItems();

	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if (g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].bEnable)
		{
			if (i<m_iChanCount)
			{
				strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_iDeviceIndex].iStartChan);
				hChanItem =  m_treeLocalChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
				m_treeLocalChan.SetItemData(hChanItem, 0*1000 + i);	
				if (m_bLocalChan[i] == 1)
				{
					m_treeLocalChan.SetCheck(hChanItem, TRUE);
				}
			}
			else if (i >= MAX_ANALOG_CHANNUM && m_iSelLocalRightType != 2)
			{
				strTemp.Format(DIGITAL_C_FORMAT, i+g_struDeviceInfo[m_iDeviceIndex].iStartChan-MAX_ANALOG_CHANNUM);
				hChanItem =  m_treeLocalChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
				m_treeLocalChan.SetItemData(hChanItem, 1*1000 + i);	
				if (m_bLocalChan[i] == 1)
				{
					m_treeLocalChan.SetCheck(hChanItem, TRUE);
				}
			}
		}
	}
	m_treeLocalChan.Expand(m_treeLocalChan.GetRootItem(),TVE_EXPAND);	
	m_treeLocalChan.SelectItem(hChanItem);
	m_treeLocalChan.EnableWindow(m_bLocalEnable);
}

/*********************************************************
  Function:	CreateRemoteTree
  Desc:		创建远程通道权限树
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUserCfg::CreateRemoteTree(void)
{
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	
	if (m_iChanCount <= 0)
	{
		m_treeRemoteChan.EnableWindow(FALSE);
		return;
	}	
	m_treeRemoteChan.DeleteAllItems();
	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if (g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].bEnable)
		{
			if (i < m_iChanCount)
			{
				strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_iDeviceIndex].iStartChan);
				hChanItem =  m_treeRemoteChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
				m_treeRemoteChan.SetItemData(hChanItem, 0*1000 + i);	
				if (m_bRemoteChan[i] == 1)
				{
					m_treeRemoteChan.SetCheck(hChanItem, TRUE);
				}
			}
			else if (i >= MAX_ANALOG_CHANNUM && m_iSelNetRightType != 3)
			{
				strTemp.Format(DIGITAL_C_FORMAT, i+g_struDeviceInfo[m_iDeviceIndex].iStartChan-MAX_ANALOG_CHANNUM);
				hChanItem =  m_treeRemoteChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
				m_treeRemoteChan.SetItemData(hChanItem, 1*1000 + i);	
				if (m_bRemoteChan[i] == 1)
				{
					m_treeRemoteChan.SetCheck(hChanItem, TRUE);
				}
			}
		}
	}
	m_treeRemoteChan.Expand(m_treeRemoteChan.GetRootItem(),TVE_EXPAND);
	m_treeRemoteChan.SelectItem(hChanItem);
	m_treeRemoteChan.EnableWindow(m_bRemoteEnable);
}

/*********************************************************
  Function:	OnClickTreeLocalChan
  Desc:		change the check status of the channel for local right
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgUserCfg::OnClickTreeLocalChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
 	UpdateData(TRUE);
// 	DWORD dwPos = GetMessagePos();
// 	CPoint point( LOWORD(dwPos), HIWORD(dwPos));
// 	point.x -=2;
// 	m_treeLocalChan.ScreenToClient(&point);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_LOCAL_CHAN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left - 2;
	pt.y = pt.y - rc.top - 2;

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

	m_bLocalChan[dwIndex] = !bCheck;
	//单击的时候改变checkbox的选中状态
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
void CDlgUserCfg::OnClickTreeRemoteChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_REMOTE_CHAN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;

	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeRemoteChan.HitTest(pt, &uFlag);

	if (NULL == hSelect) 
	{
		return;
	}

	m_treeRemoteChan.SelectItem(hSelect);
	DWORD dwIndex = m_treeRemoteChan.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeRemoteChan.GetCheck(hSelect);
	
	if (!m_bRemoteEnable)//current remote right is disalbe, don't change the status when click
	{
		if (uFlag == LVHT_TOLEFT)//0x0040, 
		{
			m_treeRemoteChan.SetCheck(hSelect, !bCheck);
		}
		return;
	}

	m_bRemoteChan[dwIndex] = !bCheck;
	//单击的时候改变checkbox的选中状态
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
void CDlgUserCfg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (m_bGetUserParams)
	{
		CreateLocalTree();
		CreateRemoteTree();
	}
}

