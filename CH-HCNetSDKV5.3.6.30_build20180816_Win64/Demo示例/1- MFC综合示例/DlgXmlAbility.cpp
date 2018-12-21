// DlgXmlAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgXmlAbility.h"
#include "DlgEncodeAbility.h"
#include "DlgNetworkAbility.h"
#include "DlgIPCFrontAbility.h"
#include "DlgCurrentEncodeAbility.h"
#include "DlgDynChanAbility.h"
#include "DlgXmlItcAbility.h"
#include "XmlUserAbility.h"
#include "DlgXmlJpegCapAbility.h"
#include "DlgXmlNetAppAbility.h"
#include "DlgXmlVideoPic.h"
#include "DlgXmlSerialAbility.h"
#include "DlgXmlAlarmAbility.h"
#include "DlgXmlDecoderAbility.h"
#include "DlgXmlRaidAbility.h"
#include "DlgXmlWallAblity.h"
#include "DlgChanInputAbility.h"
#include "DlgRecordAbility.h"
#include "DlgRemoteControlAbility.h"
#include "DlgXmlEventAbility.h"
#include "DlgXmlLCDAbility.h"
#include "DlgRecordHostAbility.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlAbility dialog

CDlgXmlAbility::CDlgXmlAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXmlAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgXmlAbility)
	m_dwVideoChan = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
}

CDlgXmlAbility::~CDlgXmlAbility()
{
	if (NULL != m_pRecvBuf)
	{
		delete[] m_pRecvBuf;
	}
}

void CDlgXmlAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgXmlAbility)
	DDX_Text(pDX, IDC_EDIT_ENCODE_VIDEO_CHAN, m_dwVideoChan);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comChannel);
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXmlAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgXmlAbility)
	ON_BN_CLICKED(IDC_BTN_ENCODE_ABILITY, OnBtnEncodeAbility)
	ON_BN_CLICKED(IDC_BTN_NETWORK, OnBtnNetwork)
	ON_BN_CLICKED(IDC_BTN_IPC_FRONT_ABILITY, OnBtnIpcFrontAbility)
	ON_BN_CLICKED(IDC_BTN_DYNCHAN_ABILITY, OnBtnDynchanAbility)
	ON_BN_CLICKED(IDC_BTN_ITC_ITS_ABILITY, OnBtnItcItsAbility)
	ON_BN_CLICKED(IDC_BTN_USER_ABILITY, OnBtnUserAbility)
	ON_BN_CLICKED(IDC_BTN_JPEG_CAP_ABILITY, OnBtnJpegCapAbility)
	ON_BN_CLICKED(IDC_BTN_NETAPP_ABILITY, OnBtnNetappAbility)
	ON_BN_CLICKED(IDC_BTN_VIDEO_PIC_ABILITY, OnBtnVideoPicAbility)
	ON_BN_CLICKED(IDC_BTN_SERIAL_ABILITY, OnBtnSerialAbility)
	ON_BN_CLICKED(IDC_BTN_ALARM_ABILITY, OnBtnAlarmAbility)
	ON_BN_CLICKED(IDC_BTN_DECODER_ABILITY, OnBtnDecoderAbility)
	ON_BN_CLICKED(IDC_BTN_RAID_ABILITY, OnBtnRaidAbility)
	ON_BN_CLICKED(IDC_BTN_WALL_ABILITY, OnBtnWallAbility)
	ON_BN_CLICKED(IDC_BTN_CHAN_INPUT_ABILITY, OnBtnChanInputAbility)
	ON_BN_CLICKED(IDC_BTN_RECORD_ABILITY, OnBtnRecordAbility)
	ON_BN_CLICKED(IDC_BTN_REMOTE_CONTROL_ABILITY, OnBtnRemoteControlAbility)
	ON_BN_CLICKED(IDC_BTN_EVENT_ABILITY, OnBtnEventAbility)
	ON_BN_CLICKED(IDC_BTN_ALARMHOST, OnBtnAlarmhost)
	ON_BN_CLICKED(IDC_BTN_LCD, OnBtnLcd)
	ON_BN_CLICKED(IDC_BTN_RECORDHOST_ABILITY, OnBtnRecordhostAbility)
	ON_BN_CLICKED(IDC_BTN_ALL_XML_ABILITY, OnBtnAllXMLAbility)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlAbility message handlers

BOOL CDlgXmlAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();

     m_pRecvBuf = new char[XML_BUF]; // 3M数据接收XML缓冲区
    m_comChannel.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgXmlAbility::OnBtnEncodeAbility() 
{
//     GetEncodeAbility();	
//     ParseEncodeAbility(m_pRecvBuf, strlen(m_pRecvBuf));
	UpdateData(TRUE);
    CDlgEncodeAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_dwVideoChan = m_dwVideoChan;
    dlg.DoModal();
}



void CDlgXmlAbility::OnBtnNetwork() 
{
    CDlgNetworkAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CDlgXmlAbility::OnBtnIpcFrontAbility() 
{
    CDlgIPCFrontAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnDynchanAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgDynChanAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnItcItsAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlItcAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnUserAbility() 
{
	// TODO: Add your control notification handler code here
	CXmlUserAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnJpegCapAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlJpegCapAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnNetappAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlNetAppAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnVideoPicAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlVideoPic dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnSerialAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlSerialAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnAlarmAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlAlarmAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnDecoderAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlDecoderAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnRaidAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlRaidAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnWallAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlWallAblity dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}

void CDlgXmlAbility::OnBtnChanInputAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgChanInputAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnRecordAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgRecordAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnRemoteControlAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgRemoteControlAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnEventAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlEventAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnAlarmhost() 
{
	// TODO: Add your control notification handler code here
	char sSendBuf[1024] = "<AlarmHostAbility version=\"2.0\"></AlarmHostAbility>";
	char sAbilityName[256] = "AlarmHostAbility";
	GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 0);
}


/****************************************************
函数名:     GetDeviceAbility
函数描述:   获取指定节点的xml能力
输入参数:   
dwCommand:	能力集命令
sSendBuf：	发送缓冲区
dwBufLen：  发送缓冲区长度
返回值:  
TRUE表示成功, FALSE表示失败 
*****************************************************/
BOOL CDlgXmlAbility::GetDeviceAbility(DWORD dwCommand, char* sSendBuf, DWORD dwBufLen, char* sAbilityName, DWORD dwChannel) 
{
	if (NET_DVR_GetDeviceAbility(m_lServerID, dwCommand, sSendBuf, dwBufLen, m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "successful! AbilityName = %s; Type = %04X; Channel = %d", sAbilityName, dwCommand, dwChannel);
		//MessageBox("获取成功");
		WirteBufToFile(m_pRecvBuf, strlen(m_pRecvBuf), sAbilityName, dwChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "failed!  AbilityName = %s; Type = %04X; Channel = %d", sAbilityName, dwCommand, dwChannel);
		//MessageBox("获取失败");
		return FALSE;
    }
	return TRUE;
}

/****************************************************
函数名:     WirteBufToFile
函数描述:   将缓冲区中的能力集数据写成XML文件
输入参数:   
pBuf：缓冲区指针
dwBufSize：缓冲区大小
返回值:  
TRUE表示成功, FALSE表示失败 
*****************************************************/
BOOL CDlgXmlAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize, char* sAbilityName, DWORD dwChannel)
{
	SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    char cFilename[256] = {0};
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    
	sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);
	if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
	{
		CreateDirectory(cFilename, NULL);
	}

    sprintf(cFilename, "%s\\%s_%d_%s.xml",cFilename, sAbilityName, dwChannel, chTime);
    
    
    HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        int nError = 0;
        nError = GetLastError();
        return FALSE;
    }
    DWORD dwReturn = 0;
    WriteFile(hFile, pBuf, dwBufSize, &dwReturn, NULL);
    CloseHandle(hFile);
    hFile = NULL;
    
    return TRUE;
}

void CDlgXmlAbility::OnBtnLcd() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlLCDAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnRecordhostAbility() 
{
	// TODO: Add your control notification handler code here
	DlgRecordHostAbility dlg;
	dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgXmlAbility::OnBtnAllXMLAbility()
{
	char sSendBuf[1024] = {0};
	char sAbilityName[256] = {0};
	int iChannel = m_comChannel.GetCurSel();
	//char sSendBuf[1024] = "<AlarmHostAbility version=\"2.0\"></AlarmHostAbility>";
	//设备软硬件能力
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_SOFTHARDWARE_ABILITY");
	GetDeviceAbility(DEVICE_SOFTHARDWARE_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//Wifi能力
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_NETWORK_ABILITY");
	GetDeviceAbility(DEVICE_NETWORK_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//获取设备编码能力
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_ENCODE_ALL_ABILITY");
	GetDeviceAbility(DEVICE_ENCODE_ALL_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//当前编码能力
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_ENCODE_CURRENT");
	GetDeviceAbility(DEVICE_ENCODE_CURRENT, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//前端参数能力
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "IPC_FRONT_PARAMETER");
	GetDeviceAbility(IPC_FRONT_PARAMETER, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

    //获取设备升级能力
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "IPC_UPGRADE_DESCRIPTION");
	GetDeviceAbility(IPC_UPGRADE_DESCRIPTION, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//获取设备编码能力2.0
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_ENCODE_ALL_ABILITY_V20");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<AudioVideoCompressInfo><AudioChannelNumber>1</AudioChannelNumber><VoiceTalkChannelNumber>1</VoiceTalkChannelNumber><VideoChannelNumber>1</VideoChannelNumber></AudioVideoCompressInfo>"); 
		GetDeviceAbility(DEVICE_ENCODE_ALL_ABILITY_V20, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<AudioVideoCompressInfo><AudioChannelNumber>2</AudioChannelNumber><VoiceTalkChannelNumber>2</VoiceTalkChannelNumber><VideoChannelNumber>2</VideoChannelNumber></AudioVideoCompressInfo>"); 
		GetDeviceAbility(DEVICE_ENCODE_ALL_ABILITY_V20, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<AudioVideoCompressInfo><AudioChannelNumber>%d</AudioChannelNumber><VoiceTalkChannelNumber>%d</VoiceTalkChannelNumber><VideoChannelNumber>%d</VideoChannelNumber></AudioVideoCompressInfo>", iChannel, iChannel, iChannel); 
		GetDeviceAbility(DEVICE_ENCODE_ALL_ABILITY_V20, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//获取设备前端参数能力（V2.0XML扩展）
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "IPC_FRONT_PARAMETER_V20");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<CAMERAPARA><ChannelNumber>1</ChannelNumber></CAMERAPARA>"); 
		GetDeviceAbility(IPC_FRONT_PARAMETER_V20, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<CAMERAPARA><ChannelNumber>2</ChannelNumber></CAMERAPARA>"); 
		GetDeviceAbility(IPC_FRONT_PARAMETER_V20, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<CAMERAPARA><ChannelNumber>%d</ChannelNumber></CAMERAPARA>", iChannel); 
		GetDeviceAbility(IPC_FRONT_PARAMETER_V20, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}
	
	//设备报警能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_ALARM_ABILITY");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<AlarmAbility version='2.0'><channelID>1</channelID></AlarmAbility>"); 
		GetDeviceAbility(DEVICE_ALARM_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<AlarmAbility version='2.0'><channelID>2</channelID></AlarmAbility>"); 
		GetDeviceAbility(DEVICE_ALARM_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<AlarmAbility version='2.0'><channelID>%d</channelID></AlarmAbility>", iChannel); 
		GetDeviceAbility(DEVICE_ALARM_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//用户管理能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_USER_ABILITY");
	sprintf(sSendBuf, "<UserAbility version='2.0'></UserAbility>");
	GetDeviceAbility(DEVICE_USER_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//网络应用能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_NETAPP_ABILITY");
	sprintf(sSendBuf, "<NetAppAbility version='2.0'></NetAppAbility>");
	GetDeviceAbility(DEVICE_NETAPP_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//视频图像能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_VIDEOPIC_ABILITY");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<VideoPicAbility version='2.0'>	<channelNO>1</channelNO></VideoPicAbility>");
		GetDeviceAbility(DEVICE_VIDEOPIC_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<VideoPicAbility version='2.0'>	<channelNO>2</channelNO></VideoPicAbility>");
		GetDeviceAbility(DEVICE_VIDEOPIC_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<VideoPicAbility version='2.0'>	<channelNO>%d</channelNO></VideoPicAbility>", iChannel);
		GetDeviceAbility(DEVICE_VIDEOPIC_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//JPEG抓图能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_JPEG_CAP_ABILITY");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<JpegCaptureAbility version='2.0'><channelNO>1</channelNO></JpegCaptureAbility>");
		GetDeviceAbility(DEVICE_JPEG_CAP_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<JpegCaptureAbility version='2.0'><channelNO>2</channelNO></JpegCaptureAbility>");
		GetDeviceAbility(DEVICE_JPEG_CAP_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<JpegCaptureAbility version='2.0'><channelNO>%d</channelNO></JpegCaptureAbility>", iChannel);
		GetDeviceAbility(DEVICE_JPEG_CAP_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//串口能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "DEVICE_SERIAL_ABILITY");
	sprintf(sSendBuf, "<SerialAbility version='2.0'></SerialAbility>");
	GetDeviceAbility(DEVICE_SERIAL_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//远程控制能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "RemoteControlAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<RemoteControlAbility version=\"2.0\"><channelNO>1</channelNO></RemoteControlAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<RemoteControlAbility version=\"2.0\"><channelNO>2</channelNO></RemoteControlAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<RemoteControlAbility version=\"2.0\"><channelNO>%d</channelNO></RemoteControlAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//设备事件能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "EventAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<EventAbility version='2.0'><channelNO>1</channelNO></EventAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<EventAbility version='2.0'><channelNO>2</channelNO></EventAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<EventAbility version='2.0'><channelNO>%d</channelNO></EventAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//报警触发录像
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "AlarmTriggerRecordAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<AlarmTriggerRecordAbility version='2.0'><channelNO>1</channelNO></AlarmTriggerRecordAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<AlarmTriggerRecordAbility version='2.0'><channelNO>2</channelNO></AlarmTriggerRecordAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<AlarmTriggerRecordAbility version='2.0'><channelNO>%d</channelNO></AlarmTriggerRecordAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//录像参数能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "RecordAbility");
	sprintf(sSendBuf, "<RecordAbility version='2.0'></RecordAbility>");
	GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//ROI能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "ROIAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<ROIAbility version='2.0'><channelNO>1</channelNO></ROIAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<ROIAbility version='2.0'><channelNO>2</channelNO></ROIAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<ROIAbility version='2.0'><channelNO>%d</channelNO></ROIAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}
	
	//云台能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "PTZAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<PTZAbility><channelNO>1</channelNO></PTZAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<PTZAbility><channelNO>2</channelNO></PTZAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<PTZAbility><channelNO>%d</channelNO></PTZAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//磁盘相关能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "HardDiskAbility");
	sprintf(sSendBuf, "<HardDiskAbility version='2.0'></HardDiskAbility>");
	GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//图片显示参数能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "ImageDisplayParamAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<ImageDisplayParamAbility version='2.0'><channelNO>1</channelNO></ImageDisplayParamAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<ImageDisplayParamAbility version='2.0'><channelNO>2</channelNO></ImageDisplayParamAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<ImageDisplayParamAbility version='2.0'><channelNO>%d</channelNO></ImageDisplayParamAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//GBT28181协议
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "GBT28181AccessAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<GBT28181AccessAbility version='2.0'><channelNO>1</channelNO></GBT28181AccessAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<GBT28181AccessAbility version='2.0'><channelNO>2</channelNO></GBT28181AccessAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<GBT28181AccessAbility version='2.0'><channelNO>%d</channelNO></GBT28181AccessAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//日志搜索能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "SearchLogAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<SearchLogAbility version='2.0'><channelNO>1</channelNO></SearchLogAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<SearchLogAbility version='2.0'><channelNO>2</channelNO></SearchLogAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<SearchLogAbility version='2.0'><channelNO>%d</channelNO></SearchLogAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//前端动态能力获取（CaptureMode）
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "CameraParaDynamicAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<CameraParaDynamicAbility version='2.0'><channelNO>1</channelNO><AudioVideoCompressInfoDynamicLinkTo><captureMode opt='640*480@30fps'/></AudioVideoCompressInfoDynamicLinkTo></CameraParaDynamicAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<CameraParaDynamicAbility version='2.0'><channelNO>2</channelNO><AudioVideoCompressInfoDynamicLinkTo><captureMode opt='640*480@30fps'/></AudioVideoCompressInfoDynamicLinkTo></CameraParaDynamicAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<CameraParaDynamicAbility version='2.0'><channelNO>%d</channelNO><AudioVideoCompressInfoDynamicLinkTo><captureMode opt='640*480@30fps'/></AudioVideoCompressInfoDynamicLinkTo></CameraParaDynamicAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//通道输入能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "ChannelInputAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<ChannelInputAbility version='2.0'><channelNO>1</channelNO></ChannelInputAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<ChannelInputAbility version='2.0'><channelNO>2</channelNO></ChannelInputAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<ChannelInputAbility version='2.0'><channelNO>%d</channelNO></ChannelInputAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//IO能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "IOAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<IOAbility version='2.0'><channelNO>1</channelNO></IOAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<IOAbility version='2.0'><channelNO>2</channelNO></IOAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<IOAbility version='2.0'><channelNO>%d</channelNO></IOAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//AccessProtocolAbility
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "AccessProtocolAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<AccessProtocolAbility version='2.0'><channelNO>1</channelNO></AccessProtocolAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<AccessProtocolAbility version='2.0'><channelNO>2</channelNO></AccessProtocolAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<AccessProtocolAbility version='2.0'><channelNO>%d</channelNO></AccessProtocolAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//智能设备能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "VcaDevAbility");
	sprintf(sSendBuf, "<VcaDevAbility version='2.0'></VcaDevAbility>");
	GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 0);

	//智能控制能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "VcaCtrlAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<VcaCtrlAbility  version='2.0'><channelNO>1</channelNO></VcaCtrlAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<VcaCtrlAbility  version='2.0'><channelNO>2</channelNO></VcaCtrlAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<VcaCtrlAbility  version='2.0'><channelNO>%d</channelNO></VcaCtrlAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}
	
	//智能通道能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "VcaChanAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<VcaChanAbility  version='2.0'><channelNO>1</channelNO></VcaChanAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<VcaChanAbility  version='2.0'><channelNO>2</channelNO></VcaChanAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<VcaChanAbility  version='2.0'><channelNO>%d</channelNO></VcaChanAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//CameraMountAbility
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "CameraMountAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<CameraMountAbility  version='2.0'><channelNO>1</channelNO></CameraMountAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<CameraMountAbility  version='2.0'><channelNO>2</channelNO></CameraMountAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<CameraMountAbility  version='2.0'><channelNO>%d</channelNO></CameraMountAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//SecurityAbility
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "SecurityAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<SecurityAbility version='2.0'><channelNO>1</channelNO></SecurityAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<SecurityAbility version='2.0'><channelNO>2</channelNO></SecurityAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<SecurityAbility version='2.0'><channelNO>%d</channelNO></SecurityAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//双目能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "BinocularAbility");
	if (0 == iChannel)
	{
		sprintf(sSendBuf, "<BinocularAbility  version='2.0'><channelNO>1</channelNO></BinocularAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 1);
		sprintf(sSendBuf, "<BinocularAbility  version='2.0'><channelNO>2</channelNO></BinocularAbility>");
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, 2);
	} 
	else
	{
		sprintf(sSendBuf, "<BinocularAbility  version='2.0'><channelNO>%d</channelNO></BinocularAbility>", iChannel);
		GetDeviceAbility(DEVICE_ABILITY_INFO, sSendBuf, strlen(sSendBuf), sAbilityName, iChannel);
	}

	//鱼眼能力
	memset(sSendBuf, 0, 1024);
	memset(sAbilityName, 0, 256);
	sprintf(sAbilityName, "FISHEYE_ABILITY");
	GetDeviceAbility(FISHEYE_ABILITY, sSendBuf, strlen(sSendBuf), sAbilityName, 0);
}
