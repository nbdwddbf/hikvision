// DlgGetAccessDeviceChannelInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGetAccessDeviceChannelInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGetAccessDeviceChannelInfo dialog


CDlgGetAccessDeviceChannelInfo::CDlgGetAccessDeviceChannelInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGetAccessDeviceChannelInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGetAccessDeviceChannelInfo)
	m_strDomain = _T("");
	m_strIP = _T("");
	m_strPasswd = _T("");
	m_strUserName = _T("");
	m_strOutput = _T("");
	m_wPort = 0;
	m_dwGroup = 0;
	//}}AFX_DATA_INIT

	m_lUserID = -1;
	m_dwDevIndex = 0;
	m_dwGroup = 0;
}


void CDlgGetAccessDeviceChannelInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGetAccessDeviceChannelInfo)
	DDX_Control(pDX, IDC_COMBO_ACCESS_MODE, m_cmbAccessMode);
	DDX_Control(pDX, IDC_COMBO_PROTYPE, m_comboProType);
	DDX_Text(pDX, IDC_DEVICE_DOMAIN, m_strDomain);
	DDX_Text(pDX, IDC_DEVICE_IP, m_strIP);
	DDX_Text(pDX, IDC_DEVICE_PSW, m_strPasswd);
	DDX_Text(pDX, IDC_DEVICE_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_strOutput);
	DDX_Text(pDX, IDC_DEVICE_PORT, m_wPort);
	DDX_Text(pDX, IDC_EDIT_GROUP, m_dwGroup);
	DDV_MinMaxDWord(pDX, m_dwGroup, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGetAccessDeviceChannelInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgGetAccessDeviceChannelInfo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_PRO_LIST, OnButtonUpdateProList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGetAccessDeviceChannelInfo message handlers

void CDlgGetAccessDeviceChannelInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_strOutput = "";
	UpdateData(FALSE);
	NET_DVR_ACCESS_DEVICE_INFO struDevInfo = {0};
	NET_DVR_ACCESS_DEVICE_CHANNEL_INFO struChannelInfo = {0};
	struDevInfo.dwSize = sizeof(NET_DVR_ACCESS_DEVICE_INFO);
	struDevInfo.byGroup = (BYTE)m_dwGroup;
	struDevInfo.byAccessMode = m_cmbAccessMode.GetCurSel();
	struDevInfo.byProType = m_comboProType.GetCurSel();
	strcpy(struDevInfo.szDomain, m_strDomain);
	strcpy(struDevInfo.struIP.sIpV4, m_strIP);
	strcpy(struDevInfo.szUserName, m_strUserName);
	strcpy(struDevInfo.szPassword, m_strPasswd);
	struDevInfo.wPort = m_wPort;
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_ACCESS_DEVICE_CHANNEL_INFO, 0, &struDevInfo, sizeof(struDevInfo), NULL, &struChannelInfo, sizeof(struChannelInfo)))
	{
		char szLan[256] = {0};
		g_StringLanType(szLan, "获取接入设备通道信息失败!", "Fail to Get Access Device Channel info!");
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ACCESS_DEVICE_CHANNEL_INFO");
        AfxMessageBox(szLan);
 		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ACCESS_DEVICE_CHANNEL_INFO");
	}

	CString strTemp;
	m_strOutput.Format("Total Channel Num = %d\r\n", struChannelInfo.dwTotalChannelNum);
	for (int i=0; i<64; i++)
	{
		strTemp.Format("Channel[%d]=%d\r\n",  i, struChannelInfo.byChannel[i]);
		m_strOutput += strTemp;
	}

	UpdateData(FALSE);
	
}

void CDlgGetAccessDeviceChannelInfo::OnButtonUpdateProList() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	char szLan[1024] = {0};

	NET_DVR_IPC_PROTO_LIST m_struProtoList = {0};
	
	m_comboProType.ResetContent();
	if (NET_DVR_GetIPCProtoList(g_struDeviceInfo[m_dwDevIndex].lLoginID, &m_struProtoList))
	{
		for (i = 0; i < (int)m_struProtoList.dwProtoNum; i++)
		{
			memset(szLan, 0, DESC_LEN);
			memcpy(szLan, m_struProtoList.struProto[i].byDescribe, DESC_LEN);
			m_comboProType.AddString(szLan);	
			m_comboProType.SetItemData(i, m_struProtoList.struProto[i].dwType);
		}
		m_comboProType.SetCurSel(0);
	}  
	else
	{
		//default	
		m_comboProType.AddString("0");
		m_comboProType.SetItemData(0, 0);
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GetIPCProtoList");
		GetDlgItem(IDC_COMBO_PROTYPE)->EnableWindow(TRUE);
	}
	
	m_comboProType.SetCurSel(0);
}

BOOL CDlgGetAccessDeviceChannelInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbAccessMode.SetCurSel(0);
	m_comboProType.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
