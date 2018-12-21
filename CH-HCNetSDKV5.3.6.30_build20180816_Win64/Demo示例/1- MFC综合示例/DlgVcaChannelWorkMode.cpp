// DlgVcaChannelWorkMode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaChannelWorkMode.h"
#include "DlgVcaDevChannel.h"
#include "DlgVcaRemoteChannel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaChannelWorkMode dialog


CDlgVcaChannelWorkMode::CDlgVcaChannelWorkMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaChannelWorkMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaChannelWorkMode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(&m_struChannelWorkMode,0,sizeof(m_struChannelWorkMode));
	memset(&m_struSlaveChannel,0,sizeof(m_struSlaveChannel));
}


void CDlgVcaChannelWorkMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaChannelWorkMode)
	DDX_Control(pDX, IDC_LIST_SLAVE_CHANNEL, m_listSlaveChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaChannelWorkMode, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaChannelWorkMode)
	ON_BN_CLICKED(IDC_BTN_ADD_LOCALCHANNEL, OnBtnAddLocalChannel)
	ON_BN_CLICKED(IDC_BTN_ADD_REMOTECHANNEL, OnBtnAddRemoteChannel)
	ON_BN_CLICKED(IDC_BTN_MODIFY_SLAVECHANNEL, OnBtnModifySlaveChannel)
	ON_BN_CLICKED(IDC_BTN_DEL_SLAVECHANNEL, OnBtnDelSlaveChannel)
	ON_BN_CLICKED(IDC_RADIO_INDEPENDENT, OnRadioIndependent)
	ON_BN_CLICKED(IDC_RADIO_MASTER, OnRadioMaster)
	ON_BN_CLICKED(IDC_RADIO_SLAVE, OnRadioSlave)
	ON_BN_CLICKED(IDC_BTN_GET_CHANNEL_WORKMODE, OnBtnGetChannelWorkmode)
	ON_BN_CLICKED(IDC_BTN_SET_CHANNEL_WORKMODE, OnBtnSetChannelWorkmode)
	ON_BN_CLICKED(IDC_BTN_GET_SLAVE_CHANNEL, OnBtnGetSlaveChannel)
	ON_BN_CLICKED(IDC_BTN_SET_SLAVE_CHANNEL, OnBtnSetSlaveChannel)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LIST_SLAVE_CHANNEL, OnDeleteitemListSlaveChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaChannelWorkMode message handlers

BOOL CDlgVcaChannelWorkMode::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	InitCtrlState();
	return TRUE;
}

void CDlgVcaChannelWorkMode::InitCtrlState()
{
	CRect rcChanList;
	m_listSlaveChannel.GetClientRect(rcChanList);
   
	char szNumber[32] = "\0";
	char szDevIP[32] = "\0";
	char szChannelType[32] = "\0";
	char szChannelNumber[32] = "\0";
	g_StringLanType(szNumber, "编号","No."); 
    g_StringLanType(szDevIP, "设备IP","Device IP"); 	
    g_StringLanType(szChannelType, "类型","Channel Type"); 	
    g_StringLanType(szChannelNumber, "通道号","Channel Number"); 	
		
	m_listSlaveChannel.InsertColumn(0,szNumber,  LVCFMT_CENTER);
	m_listSlaveChannel.InsertColumn(1,szChannelType,  LVCFMT_CENTER);
	m_listSlaveChannel.InsertColumn(2,szDevIP,LVCFMT_CENTER);
	m_listSlaveChannel.InsertColumn(3,szChannelNumber,LVCFMT_CENTER);
	m_listSlaveChannel.ModifyStyle(0,LVS_SINGLESEL);
	m_listSlaveChannel.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	int nDevListWidth  = rcChanList.Width();
	m_listSlaveChannel.SetColumnWidth(0,int(nDevListWidth * 0.2));
	m_listSlaveChannel.SetColumnWidth(1,int(nDevListWidth * 0.3));
	m_listSlaveChannel.SetColumnWidth(2,int(nDevListWidth * 0.3));
	m_listSlaveChannel.SetColumnWidth(3,int(nDevListWidth * 0.2));
}

void CDlgVcaChannelWorkMode::OnBtnAddLocalChannel() 
{
	CDlgVcaDevChannel dlg;
	dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel  = m_lChannel;
    dlg.m_lServerID = m_lServerID;
     
	vector<DWORD> vctChannel;
	int nItemCount = m_listSlaveChannel.GetItemCount();
	for (int i = 0; i < nItemCount; i++)
	{
		SLAVE_CHANNEL_PARAM* pChannelParam = (SLAVE_CHANNEL_PARAM*)m_listSlaveChannel.GetItemData(i);
		if (pChannelParam != NULL)
		{
			if (pChannelParam->byLocal)
			{
				vctChannel.push_back(pChannelParam->dwChannel);
			}
		}
	}

	dlg.SetSelChannel(vctChannel);
	if (dlg.DoModal() == IDOK)
	{   
		//delete all local channels and readd them
		for (int i = nItemCount - 1; i >= 0; i--)
		{
			SLAVE_CHANNEL_PARAM* pChannelParam = (SLAVE_CHANNEL_PARAM*)m_listSlaveChannel.GetItemData(i);
			if (pChannelParam != NULL)
			{
				if (pChannelParam->byLocal)
				{
					m_listSlaveChannel.DeleteItem(i);
				}
			}
		}

		dlg.GetSelChannel(vctChannel);

		char szLan[64] = {0};
		for (vector<DWORD>::iterator iter = vctChannel.begin(); iter != vctChannel.end(); iter++)
		{
			SLAVE_CHANNEL_PARAM* pChannelParam = new SLAVE_CHANNEL_PARAM;
			pChannelParam->byLocal   = TRUE;
			pChannelParam->dwChannel = *iter;
			pChannelParam->strDevIP  = g_struDeviceInfo[m_iDevIndex].chDeviceIP;
           
			AddSlaveChannel(pChannelParam);
		}
	}
	UpdateSlaveChanListIndex();
}

void CDlgVcaChannelWorkMode::OnBtnAddRemoteChannel() 
{
	CDlgVcaRemoteChannel dlg;
	if (dlg.DoModal() ==IDOK)
	{   
		SLAVE_CHANNEL_PARAM* pChannelParam = new SLAVE_CHANNEL_PARAM;
		pChannelParam->byLocal = FALSE;

		dlg.GetRemoteChannelParam(pChannelParam->strDevIP,pChannelParam->dwPort,pChannelParam->strUserName,
			pChannelParam->strPassword,pChannelParam->dwChannel);
        
	    AddSlaveChannel(pChannelParam);
	}
	
}

void CDlgVcaChannelWorkMode::OnBtnModifySlaveChannel() 
{   
	int nSelDevIndex = m_listSlaveChannel.GetNextItem(-1,LVNI_SELECTED);
	if (nSelDevIndex == -1)
	{   
		return;
	}

	SLAVE_CHANNEL_PARAM* pChannelParam = (SLAVE_CHANNEL_PARAM*)m_listSlaveChannel.GetItemData(nSelDevIndex);
	if (pChannelParam == NULL || pChannelParam->byLocal)
	{
		return;
	}

	CDlgVcaRemoteChannel dlg;
	dlg.SetRemoteChannelParam(pChannelParam->strDevIP,pChannelParam->dwPort,pChannelParam->strUserName,
		pChannelParam->strPassword,pChannelParam->dwChannel);
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetRemoteChannelParam(pChannelParam->strDevIP,pChannelParam->dwPort,pChannelParam->strUserName,
			pChannelParam->strPassword,pChannelParam->dwChannel);
		UpdateSlaveChannel(nSelDevIndex,pChannelParam);
	}
	
}

void CDlgVcaChannelWorkMode::OnBtnDelSlaveChannel() 
{
	int nSelDevIndex = m_listSlaveChannel.GetNextItem(-1,LVNI_SELECTED);
	if (nSelDevIndex == -1)
	{   
		return;
	}
    m_listSlaveChannel.DeleteItem(nSelDevIndex);
    UpdateSlaveChanListIndex();
}


void CDlgVcaChannelWorkMode::OnRadioIndependent() 
{
	UpdateChanenlWorkModeRadio(ENUM_CHAN_WORKMODE_INDEPENDENT);
}

void CDlgVcaChannelWorkMode::OnRadioMaster() 
{
	UpdateChanenlWorkModeRadio(ENUM_CHAN_WORKMODE_MASTER);
	
}

void CDlgVcaChannelWorkMode::OnRadioSlave() 
{
	UpdateChanenlWorkModeRadio(ENUM_CHAN_WORKMODE_SLAVE);
}

void CDlgVcaChannelWorkMode::OnBtnGetChannelWorkmode() 
{
	char szError[32] = "\0";
	if (!GetChannelWorkMode())
	{
       	g_StringLanType(szError, "获取失败","Get failed");
		AfxMessageBox(szError);
		
	}
	else
	{
		LoadWorkModeWndContent();
	}
	
}

void CDlgVcaChannelWorkMode::OnBtnSetChannelWorkmode() 
{
	SaveWorkModeWndContent();
	
	char szError[32] = "\0";
	if (SetChannelWorkMode())
	{
        g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
	
}

void CDlgVcaChannelWorkMode::OnBtnGetSlaveChannel() 
{
	char szError[32] = "\0";
	if (!GetSlaveChannel())
	{
       	g_StringLanType(szError, "获取失败","Get failed");
		AfxMessageBox(szError);
	}
	else
	{
		LoadSlaveChannelWndContent();
	}
	
}

void CDlgVcaChannelWorkMode::OnBtnSetSlaveChannel() 
{   
	int nItemCount = m_listSlaveChannel.GetItemCount();
	if (nItemCount > MAX_SLAVE_CHANNEL_NUM)
	{
		char szError[64] = "\0";
		g_StringLanType(szError, "最大支持16个从通道","Maximum support 16 slave channels");
		AfxMessageBox(szError);
		return;
	}

	SaveSlaveChannelWndContent();
	
	char szError[32] = "\0";
	if (SetSlaveChannel())
	{
        g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
	
}

void CDlgVcaChannelWorkMode::UpdateChanenlWorkModeRadio(DWORD dwChannelWorkMode)
{
	CheckDlgButton(IDC_RADIO_INDEPENDENT,dwChannelWorkMode == ENUM_CHAN_WORKMODE_INDEPENDENT ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO_MASTER,     dwChannelWorkMode == ENUM_CHAN_WORKMODE_MASTER      ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO_SLAVE,      dwChannelWorkMode == ENUM_CHAN_WORKMODE_SLAVE       ? BST_CHECKED : BST_UNCHECKED);
}

void CDlgVcaChannelWorkMode::OnDeleteitemListSlaveChannel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	int nItemIndex     = pNMListView->iItem;
	SLAVE_CHANNEL_PARAM* pChannelParam = (SLAVE_CHANNEL_PARAM*)m_listSlaveChannel.GetItemData(nItemIndex);
	if (pChannelParam  != NULL)
	{
		delete pChannelParam;
	}
	*pResult = 0;
}

void CDlgVcaChannelWorkMode::AddSlaveChannel(SLAVE_CHANNEL_PARAM* pChannelParam)
{
	if (pChannelParam == NULL)
	{
		return;
	}

	CString strTextItemNo = "";
	CString strChannelNo  = "";
	int nItemIndex = m_listSlaveChannel.GetItemCount();
	 
	strTextItemNo.Format(_T("%d"),nItemIndex + 1);
	strChannelNo.Format(_T("%d"),pChannelParam->dwChannel);
	
	
	char szChannelType[64] = {0};
	if (pChannelParam->byLocal)
	{
		g_StringLanType(szChannelType, "本机通道", "Local");
	}
	else
	{
		g_StringLanType(szChannelType, "远程通道", "Remote");
	}
    m_listSlaveChannel.InsertItem(nItemIndex,strTextItemNo);
	m_listSlaveChannel.SetItemText(nItemIndex,1,szChannelType);
	m_listSlaveChannel.SetItemText(nItemIndex,2,pChannelParam->strDevIP);
	m_listSlaveChannel.SetItemText(nItemIndex,3,strChannelNo);

	m_listSlaveChannel.SetItemData(nItemIndex,(DWORD)pChannelParam);
}

void CDlgVcaChannelWorkMode::UpdateSlaveChanListIndex()
{
	int nItemCount = m_listSlaveChannel.GetItemCount();
	for (int i = 0; i < nItemCount; i++)
	{
		CString strNo = TEXT("");
		strNo.Format(TEXT("%d"),i + 1);
		m_listSlaveChannel.SetItemText(i,0,strNo);
	}
}

void CDlgVcaChannelWorkMode::UpdateSlaveChannel(int nIndex,SLAVE_CHANNEL_PARAM* pChannelParam)
{
	if (pChannelParam == NULL)
	{
		return;
	}
	
	CString strChannelNo  = "";
	strChannelNo.Format(_T("%d"),pChannelParam->dwChannel);
	
	char szChannelType[64] = {0};
	if (pChannelParam->byLocal)
	{
		g_StringLanType(szChannelType, "本机通道", "Local");
	}
	else
	{
		g_StringLanType(szChannelType, "远程通道", "Remote");
	}

	m_listSlaveChannel.SetItemText(nIndex,1,szChannelType);
	m_listSlaveChannel.SetItemText(nIndex,2,pChannelParam->strDevIP);
	m_listSlaveChannel.SetItemText(nIndex,3,strChannelNo);
	
	m_listSlaveChannel.SetItemData(nIndex,(DWORD)pChannelParam);
}

BOOL CDlgVcaChannelWorkMode::GetChannelWorkMode()
{
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_CHAN_WORKMODE, 1,(LPVOID)&m_lChannel, sizeof(DWORD),
		&dwStatus,&m_struChannelWorkMode,sizeof(m_struChannelWorkMode)))
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CHAN_WORKMODE Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CHAN_WORKMODE Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaChannelWorkMode::SetChannelWorkMode()
{
    DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_CHAN_WORKMODE,1,(LPVOID)&m_lChannel, sizeof(DWORD),
		&dwStatus,&m_struChannelWorkMode, sizeof(m_struChannelWorkMode)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CHAN_WORKMODE Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CHAN_WORKMODE Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaChannelWorkMode::GetSlaveChannel()
{
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SLAVE_CHANNEL, 1,(LPVOID)&m_lChannel, sizeof(DWORD),
		&dwStatus,&m_struSlaveChannel,sizeof(m_struSlaveChannel)) || dwStatus != 0)
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SLAVE_CHANNEL Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SLAVE_CHANNEL Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaChannelWorkMode::SetSlaveChannel()
{
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_SLAVE_CHANNEL,1,(LPVOID)&m_lChannel, sizeof(DWORD),
		&dwStatus,&m_struSlaveChannel, sizeof(m_struSlaveChannel)) || dwStatus != 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SLAVE_CHANNEL Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SLAVE_CHANNEL Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

void CDlgVcaChannelWorkMode::LoadWorkModeWndContent()
{
	UpdateChanenlWorkModeRadio(m_struChannelWorkMode.byWorkMode);
}

void CDlgVcaChannelWorkMode::SaveWorkModeWndContent()
{   
	BYTE byChannelWorkMode = 0;
	if (IsDlgButtonChecked(IDC_RADIO_INDEPENDENT))
	{
		byChannelWorkMode = ENUM_CHAN_WORKMODE_INDEPENDENT;
	}
	else if (IsDlgButtonChecked(IDC_RADIO_MASTER))
	{
		byChannelWorkMode = ENUM_CHAN_WORKMODE_MASTER;
	}
	else if (IsDlgButtonChecked(IDC_RADIO_SLAVE))
	{
		byChannelWorkMode = ENUM_CHAN_WORKMODE_SLAVE;
	}
	m_struChannelWorkMode.byWorkMode = byChannelWorkMode;
}

void CDlgVcaChannelWorkMode::LoadSlaveChannelWndContent()
{
	m_listSlaveChannel.DeleteAllItems();

	for (int i = 0; i < MAX_SLAVE_CHANNEL_NUM; i++)
	{ 
		SLAVE_CHANNEL_PARAM* pChannelParam = NULL;
		
		NET_DVR_SLAVE_CHANNEL_PARAM& struSlaveChannel = m_struSlaveChannel.struChanParam[i];
		if (struSlaveChannel.byChanType == SLAVE_CHANNEL_LOCAL)
		{   
			pChannelParam = new SLAVE_CHANNEL_PARAM;
			pChannelParam->byLocal   = TRUE;
			pChannelParam->strDevIP  = g_struDeviceInfo[m_iDevIndex].chDeviceIP;
			pChannelParam->dwChannel = struSlaveChannel.uSlaveChannel.dwLocalChannel;
		}
		else if (struSlaveChannel.byChanType == SLAVE_CHANNEL_REMOTE)
		{  
			NET_DVR_CHANNEL& struRemoteChannel = struSlaveChannel.uSlaveChannel.struRemoteChannel;

			pChannelParam = new SLAVE_CHANNEL_PARAM;
			pChannelParam->byLocal     = FALSE;
			pChannelParam->strDevIP    = struRemoteChannel.byAddress;
			pChannelParam->strUserName = struRemoteChannel.sUserName;
			pChannelParam->strPassword = struRemoteChannel.sPassword;
			pChannelParam->dwPort      = struRemoteChannel.wDVRPort;
			pChannelParam->dwChannel   = struRemoteChannel.dwChannel;

		}

		if (pChannelParam != NULL)
		{
			AddSlaveChannel(pChannelParam);
		}
	}
}

void CDlgVcaChannelWorkMode::SaveSlaveChannelWndContent()
{
	int nItemCount = m_listSlaveChannel.GetItemCount();
	int nIndex     = 0;

	m_struSlaveChannel.dwSize = sizeof(m_struSlaveChannel);

	for (int i = 0; i < nItemCount; i++)
	{   
		if (nIndex >= MAX_SLAVE_CHANNEL_NUM)
		{
			break;
		}

		SLAVE_CHANNEL_PARAM* pChannelParam = (SLAVE_CHANNEL_PARAM*)m_listSlaveChannel.GetItemData(i);
		if (pChannelParam == NULL)
		{
			continue;
		}
		NET_DVR_SLAVE_CHANNEL_PARAM& struSlaveChannel = m_struSlaveChannel.struChanParam[nIndex];
		if (pChannelParam->byLocal)
		{
			struSlaveChannel.byChanType = SLAVE_CHANNEL_LOCAL;
			struSlaveChannel.uSlaveChannel.dwLocalChannel = pChannelParam->dwChannel;
		}
		else
		{
			struSlaveChannel.byChanType = SLAVE_CHANNEL_REMOTE;

			NET_DVR_CHANNEL& struRemoteChannel = struSlaveChannel.uSlaveChannel.struRemoteChannel;
			strncpy((char*)struRemoteChannel.byAddress,pChannelParam->strDevIP,MAX_DOMAIN_NAME);
			strncpy((char*)struRemoteChannel.sUserName,pChannelParam->strUserName,NAME_LEN);
			strncpy((char*)struRemoteChannel.sPassword,pChannelParam->strPassword,PASSWD_LEN);
			struRemoteChannel.wDVRPort = pChannelParam->dwPort;
			struRemoteChannel.dwChannel = pChannelParam->dwChannel;
		}
		nIndex++;
	}
}
