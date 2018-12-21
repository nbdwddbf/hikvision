// DlgQuickAddIpc.cpp : implementation file
//
#include "stdafx.h"
#include "clientdemo.h"
#include "DlgQuickAddIpc.h"
#include "DlgRemoteIPAccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQuickAddIpc dialog


CDlgQuickAddIpc::CDlgQuickAddIpc(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQuickAddIpc::IDD, pParent)
    , m_lServerID (-1)
    , m_iDevIndex(-1)
    , m_bIPCActivatePassword(FALSE)
{
    memset(&m_struSadpInfoList, 0, sizeof(m_struSadpInfoList));
    memset(&m_struIpcProtoList, 0, sizeof(m_struIpcProtoList));
    memset(&m_struIpParaCfgV40, 0, sizeof(m_struIpParaCfgV40));
    memset(m_byMacAddr, 0, MACADDR_LEN);
	//{{AFX_DATA_INIT(CDlgQuickAddIpc)
	m_csDevIP = _T("");
	m_iDevPort = 0;
	m_csPassword = _T("");
	m_csSubnetMask = _T("");
	m_ProtocolType = 0;
	m_strActivatePwd = _T("");
	m_csGB28181DevID = _T("");
	//}}AFX_DATA_INIT
}


void CDlgQuickAddIpc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQuickAddIpc)
	DDX_Control(pDX, IDC_LIST_IP_CHAN, m_listIPChan);
	DDX_Control(pDX, IDC_LIST_SADP_INFO, m_listSadpInfo);
	DDX_Text(pDX, IDC_EDIT_DEV_IP, m_csDevIP);
	DDX_Text(pDX, IDC_EDIT_DEV_PORT, m_iDevPort);
	DDV_MinMaxInt(pDX, m_iDevPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_SUBNET_MASK, m_csSubnetMask);
	DDX_Text(pDX, IDC_PROTOCOL_TYPE, m_ProtocolType);
	DDX_Text(pDX, IDC_EDIT_ACTIVATE_PASSWORD, m_strActivatePwd);
	DDV_MaxChars(pDX, m_strActivatePwd, 16);
	DDX_Text(pDX, IDC_EDIT_GB28181_DEVID, m_csGB28181DevID);
	//}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHECK_IPC_ACTIVATE_PASSWORD, m_bIPCActivatePassword);
}


BEGIN_MESSAGE_MAP(CDlgQuickAddIpc, CDialog)
	//{{AFX_MSG_MAP(CDlgQuickAddIpc)
	ON_BN_CLICKED(IDC_BTN_GET_SADPINFO, OnBtnGetSadpinfo)
	ON_BN_CLICKED(IDC_BTN_QUICK_ADD, OnBtnQuickAdd)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_QUICK_SET, OnBtnQuickSet)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SADP_INFO, OnClickListSadpInfo)
	ON_BN_CLICKED(IDC_BTN_SAVE_SADPINFO, OnBtnSaveSadpinfo)
	ON_BN_CLICKED(IDC_BTN_ACTIVATE, OnBtnActivate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQuickAddIpc message handlers

void CDlgQuickAddIpc::OnBtnGetSadpinfo() 
{
    char szLan[256] = {0};
	if (!NET_DVR_GetSadpInfoList(m_lServerID, &m_struSadpInfoList))
	{
        g_pMainDlg->AddLog(m_iDevIndex ,OPERATION_FAIL_T, "NET_DVR_GetSadpInfoList");
        g_StringLanType(szLan, "获取远程扫描IPC列表失败", "Fail to get sadp info list");
        AfxMessageBox(szLan);
        return;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex ,OPERATION_SUCC_T, "NET_DVR_GetSadpInfoList");
    }

    m_listSadpInfo.DeleteAllItems();

    CString strTemp = _T("");
    int nSadpIndex = 0;
    
    for (nSadpIndex = 0; nSadpIndex < m_struSadpInfoList.wSadpNum; nSadpIndex++)
    {
        int nIndex = 0;
        strTemp.Format("%02d", nSadpIndex + 1);
        m_listSadpInfo.InsertItem(nSadpIndex, strTemp, nIndex);
        nIndex++;

        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, m_struSadpInfoList.struSadpInfo[nSadpIndex].struIP.sIpV4);
        nIndex++;

        strTemp.Format("%d", m_struSadpInfoList.struSadpInfo[nSadpIndex].wPort);
        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, strTemp);
        nIndex++;
        
        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, GetFactoryStr(m_struSadpInfoList.struSadpInfo[nSadpIndex].wFactoryType));
        nIndex++;

        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, m_struSadpInfoList.struSadpInfo[nSadpIndex].chSoftwareVersion);
        nIndex++;

        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, m_struSadpInfoList.struSadpInfo[nSadpIndex].chSerialNo);
        nIndex++;
        
        strTemp.Format("%d", m_struSadpInfoList.struSadpInfo[nSadpIndex].wEncCnt);
        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, strTemp);
        nIndex++;
        
        strTemp.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struSadpInfoList.struSadpInfo[nSadpIndex].byMACAddr[0],\
            m_struSadpInfoList.struSadpInfo[nSadpIndex].byMACAddr[1],m_struSadpInfoList.struSadpInfo[nSadpIndex].byMACAddr[2],\
            m_struSadpInfoList.struSadpInfo[nSadpIndex].byMACAddr[3],m_struSadpInfoList.struSadpInfo[nSadpIndex].byMACAddr[4],\
            m_struSadpInfoList.struSadpInfo[nSadpIndex].byMACAddr[5]);
        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, strTemp);
        nIndex++;

        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, m_struSadpInfoList.struSadpInfo[nSadpIndex].struSubDVRIPMask.sIpV4);
        nIndex++;

        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, m_struSadpInfoList.struSadpInfo[nSadpIndex].struGatewayIpAddr.sIpV4);
        nIndex++;

        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, m_struSadpInfoList.struSadpInfo[nSadpIndex].struDnsServer1IpAddr.sIpV4);
        nIndex++;

        m_listSadpInfo.SetItemText(nSadpIndex, nIndex, m_struSadpInfoList.struSadpInfo[nSadpIndex].struDnsServer2IpAddr.sIpV4);
        nIndex++;

        if (m_struSadpInfoList.struSadpInfo[nSadpIndex].byActivated == 1)
        {
            m_listSadpInfo.SetItemText(nSadpIndex, nIndex, "Yes");
        }
        else if (m_struSadpInfoList.struSadpInfo[nSadpIndex].byActivated == 2)
        {
            m_listSadpInfo.SetItemText(nSadpIndex, nIndex, "No");
        }
        else
        {
            m_listSadpInfo.SetItemText(nSadpIndex, nIndex, "Invalid");
        }
        nIndex++;
    }

}

BOOL CDlgQuickAddIpc::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    GetIPParamConfig();
    m_listSadpInfo.SetExtendedStyle(m_listSadpInfo.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
    char szLan[128] = {0};
    int nIndex = 0;
    g_StringLanType(szLan, "序号", "Serial No.");
    m_listSadpInfo.InsertColumn(nIndex, "序号",LVCFMT_LEFT,40,-1);
    nIndex++;
    g_StringLanType(szLan, "IP地址", "IP Address");
    m_listSadpInfo.InsertColumn(nIndex,szLan,LVCFMT_LEFT,100,-1);
    nIndex++;
    g_StringLanType(szLan, "端口", "Port");
    m_listSadpInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,40,-1);
    nIndex++;
    g_StringLanType(szLan, "厂家类型", "Factory type");
    m_listSadpInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,80,-1);
    nIndex++;
    g_StringLanType(szLan, "软件版本号", "Software version");
    m_listSadpInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,120,-1);
    nIndex++;
    g_StringLanType(szLan, "序列号", "Serial No.");
    m_listSadpInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,100,-1);
    nIndex++;
    g_StringLanType(szLan, "编码通道", "Enc cnt");
    m_listSadpInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,50,-1);
    nIndex++;
    g_StringLanType(szLan, "MAC", "MAC");
    m_listSadpInfo.InsertColumn(nIndex, szLan, LVCFMT_LEFT,100, -1);
    nIndex++;
    g_StringLanType(szLan, "子网掩码", "Subnet mask");
    m_listSadpInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT, 100, -1);
    nIndex++;
    g_StringLanType(szLan, "网关", "Gateway");
    m_listSadpInfo.InsertColumn(nIndex,szLan, LVCFMT_LEFT,100, -1);
    nIndex++;

    g_StringLanType(szLan, "首选DNS", "Preferred DNS");
    m_listSadpInfo.InsertColumn(nIndex,szLan, LVCFMT_LEFT,100, -1);
    nIndex++;
    
    g_StringLanType(szLan, "备选DNS", "Alternative DNS");
    m_listSadpInfo.InsertColumn(nIndex,szLan, LVCFMT_LEFT,100, -1);
    nIndex++;

    g_StringLanType(szLan, "已激活", "Activated");
    m_listSadpInfo.InsertColumn(nIndex,szLan, LVCFMT_LEFT, 80, -1);
    nIndex++; 

    nIndex = 0;

    m_listIPChan.SetExtendedStyle(m_listIPChan.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "序号", "Serial No.");
    m_listIPChan.InsertColumn(nIndex, szLan,LVCFMT_LEFT,40,-1);
    nIndex++;
    g_StringLanType(szLan, "通道号", "Channel");
    m_listIPChan.InsertColumn(nIndex,szLan,LVCFMT_LEFT,80,-1);
    nIndex++;
    g_StringLanType(szLan, "IP地址", "IP Address/Domain");
    m_listIPChan.InsertColumn(nIndex, szLan,LVCFMT_LEFT,120,-1);
    nIndex++;
    g_StringLanType(szLan, "端口号", "Port");
    m_listIPChan.InsertColumn(nIndex, szLan,LVCFMT_LEFT,80,-1);
    nIndex++;
    g_StringLanType(szLan, "IP通道号", "IP Channel");
    m_listIPChan.InsertColumn(nIndex, szLan,LVCFMT_LEFT,80,-1);
    nIndex++;
    g_StringLanType(szLan, "是否在线", "Whether online");
    m_listIPChan.InsertColumn(nIndex, szLan,LVCFMT_LEFT,80,-1);
    nIndex++;
    g_StringLanType(szLan, "协议", "Protocol");
    m_listIPChan.InsertColumn(nIndex, szLan,LVCFMT_LEFT,100,-1);
    nIndex++;

	g_StringLanType(szLan, "GB28181设备编号", "GB28181Dev ID");
	m_listIPChan.InsertColumn(nIndex, szLan,LVCFMT_LEFT,100,-1);
	nIndex++;
		
    CheckInitparam();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

char* CDlgQuickAddIpc::GetFactoryStr(int nFactoryType)
{
    for (int i = 0; i < m_struIpcProtoList.dwProtoNum; i++)
    {
        if (nFactoryType == m_struIpcProtoList.struProto[i].dwType)
        {
            return (char*)m_struIpcProtoList.struProto[i].byDescribe;
        }
    }
    return NULL;
}

void CDlgQuickAddIpc::OnBtnQuickAdd() 
{
    char szLan[256] = {0};
    POSITION posSadp = m_listSadpInfo.GetFirstSelectedItemPosition();
    if (posSadp == 0)
    {
        g_StringLanType(szLan, "请选择Sadp信息", "please select sadp info");
        AfxMessageBox(szLan);
        return;
    }
    int iSadpCurSel = m_listIPChan.GetNextSelectedItem(posSadp);
    
    POSITION posIPChan = m_listIPChan.GetFirstSelectedItemPosition();
    if (posIPChan == 0)
    {
        g_StringLanType(szLan, "请选择IP通道", "please select ipchan");
        return;
    }
    
    int iIPCurSel = m_listIPChan.GetNextSelectedItem(posIPChan);

    int i = 0;
    for (i = 0;  i < MAX_IP_DEVICE; i++)
    {
        if (m_struIpParaCfgV40.struIPDevInfo[i].byEnable == 0)
        {
            m_struIpParaCfgV40.struIPDevInfo[i].byEnable = 1;
            m_struIpParaCfgV40.struIPDevInfo[i].byEnableQuickAdd = TRUE;
            memcpy(&m_struIpParaCfgV40.struIPDevInfo[i].struIP, &m_struSadpInfoList.struSadpInfo[iSadpCurSel].struIP, sizeof(m_struSadpInfoList.struSadpInfo[iSadpCurSel].struIP));
            m_struIpParaCfgV40.struIPDevInfo[i].wDVRPort = m_struSadpInfoList.struSadpInfo[iSadpCurSel].wPort;
            m_struIpParaCfgV40.struIPDevInfo[i].byProType = m_struSadpInfoList.struSadpInfo[iSadpCurSel].wFactoryType; // 厂家协议类型
            
            m_struIpParaCfgV40.struStreamMode[iIPCurSel].byGetStreamType = NET_SDK_IP_DEVICE;
            m_struIpParaCfgV40.struStreamMode[iIPCurSel].uGetStream.struChanInfo.byEnable = TRUE;
            m_struIpParaCfgV40.struStreamMode[iIPCurSel].uGetStream.struChanInfo.byIPID = i+1;
            m_struIpParaCfgV40.struStreamMode[iIPCurSel].uGetStream.struChanInfo.byChannel = 1;  //   IPC have one channel
            
            break;
        }   
    }

    m_listIPChan.SetItemText(iIPCurSel, 2, GetDeviceAddress(&(m_struIpParaCfgV40.struIPDevInfo[i])));
    m_listIPChan.SetItemText(iIPCurSel, 6, GetFactoryStr(m_struIpParaCfgV40.struIPDevInfo[i].byProType));
}

void CDlgQuickAddIpc::CheckInitparam()
{
    //	HTREEITEM hChanItem = NULL;
    m_listIPChan.DeleteAllItems();
    CString strTemp = "";
    DWORD dwChanNum;
    int iIndex = 0; 
    char szLan[256] = {0};
    for (int i = 0; i < MAX_CHANNUM_V30; i++)
    {
        dwChanNum = i + g_struDeviceInfo[m_iDevIndex].iStartChan;
        
        if (i < g_struDeviceInfo[m_iDevIndex].iDeviceChanNum - g_struDeviceInfo[m_iDevIndex].iIPChanNum)
        {          
//             strTemp.Format("%02d", iIndex+1);
//             m_listIPChan.InsertItem(iIndex, strTemp, 0);
//             strTemp.Format(ANALOG_C_FORMAT, dwChanNum);
//             m_listIPChan.SetItemText(iIndex, 1, strTemp);
//             g_StringLanType(szLan, "本地", "local");
//             m_listIPChan.SetItemText(iIndex, 2, szLan);
//             m_listIPChan.SetItemText(iIndex, 3, "0");
//             m_listIPChan.SetItemText(iIndex, 4, "0");
//             if (m_struIpParaCfgV40.byAnalogChanEnable[i])
//             {
//                 g_StringLanType(szLan, "是", "Yes");
//                 m_listIPChan.SetItemText(i, 5, szLan);
//                 m_listIPChan.SetItemData(iIndex, ANALOG_CHAN_ENABLE*1000+i);
//             }
//             else
//             {
//                 g_StringLanType(szLan, "否", "No");
//                 m_listIPChan.SetItemText(i, 5, szLan);
//                 m_listIPChan.SetItemData(iIndex, ANALOG_CHAN_DISABLE*1000+i);
//             }
//             iIndex++;
        }
        else if (i >= g_struDeviceInfo[m_iDevIndex].iDeviceChanNum && i < MAX_ANALOG_CHANNUM)
        {
        }
        else if (i >= MAX_ANALOG_CHANNUM  && i < (g_struDeviceInfo[m_iDevIndex].iIPChanNum+MAX_ANALOG_CHANNUM))
        {
            DWORD dwIPChanIndex = i-MAX_ANALOG_CHANNUM;
            dwChanNum = dwIPChanIndex + g_struDeviceInfo[m_iDevIndex].iStartChan;
            DWORD dwID = m_struIpParaCfgV40.struStreamMode[dwIPChanIndex].uGetStream.struChanInfo.byIPID;
            
            strTemp.Format("%02d", iIndex+1);
            m_listIPChan.InsertItem(iIndex, strTemp, 0);
            
            strTemp.Format(IP_CAMERA_NAME, dwChanNum);
            m_listIPChan.SetItemText(iIndex, 1, strTemp);
            if (m_struIpParaCfgV40.struStreamMode[dwIPChanIndex].uGetStream.struChanInfo.byIPID != 0)
            {
                
                m_listIPChan.SetItemText(iIndex, 2, GetDeviceAddress(&(m_struIpParaCfgV40.struIPDevInfo[dwID-1])));
                
                strTemp.Format("%d", m_struIpParaCfgV40.struIPDevInfo[dwID-1].wDVRPort);
                m_listIPChan.SetItemText(iIndex, 3, strTemp);
                strTemp.Format("%d", m_struIpParaCfgV40.struStreamMode[dwIPChanIndex].uGetStream.struChanInfo.byChannel);
                m_listIPChan.SetItemText(iIndex, 4, strTemp);
                if (m_struIpParaCfgV40.struStreamMode[dwIPChanIndex].uGetStream.struChanInfo.byEnable)
                {
                    g_StringLanType(szLan, "在线", "Online");
                    m_listIPChan.SetItemText(iIndex, 5, szLan);	
                }		
                else
                {
                    g_StringLanType(szLan, "离线", "Offline");
                    m_listIPChan.SetItemText(iIndex, 5, szLan);
                }
                m_listIPChan.SetItemText(iIndex, 6, (char *)(m_struIpcProtoList.struProto[m_struIpParaCfgV40.struIPDevInfo[dwID-1].byProType].byDescribe));				
                m_listIPChan.SetItemData(iIndex, IP_CHAN_ENABLE*1000+i);
            }
            else
            {
                m_listIPChan.SetItemText(iIndex, 2, "0.0.0.0");
                m_listIPChan.SetItemText(iIndex, 3, "0");
                m_listIPChan.SetItemText(iIndex, 4, "0");
                g_StringLanType(szLan, "否", "No");
                m_listIPChan.SetItemText(iIndex, 5, szLan);
                m_listIPChan.SetItemData(iIndex, IP_CHAN_DISABLE*1000+i);
            }	
            iIndex++;
        }
    }	
    
}

void CDlgQuickAddIpc::OnBtnRefresh() 
{
	GetIPParamConfig();
    CheckInitparam();
}

BOOL CDlgQuickAddIpc::SetIPParamConfig()
{
    BOOL bRet = FALSE;
    bRet = NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_IPPARACFG_V40, 0, &m_struIpParaCfgV40, sizeof(m_struIpParaCfgV40));
	char szLan[256] = {0};
    if (bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IPPARACFG_V40");
        g_StringLanType(szLan, "设置成功", "Succ to set IP param");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IPPARACFG_V40");
        g_StringLanType(szLan, "设置失败", "Fail to set IP param");
        AfxMessageBox(szLan);
    }
    return bRet;
}

BOOL CDlgQuickAddIpc::GetIPParamConfig()
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    char szLan[256] = {0};
    bRet = NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_IPPARACFG_V40, 0, &m_struIpParaCfgV40, sizeof(m_struIpParaCfgV40), &dwReturn);
    if (bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IPPARACFG_V40");
        //g_StringLanType(szLan, "获取成功", "Succ to get ip param");
        //AfxMessageBox(szLan);
    }
    else
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IPPARACFG_V40");
//         g_StringLanType(szLan, "获取失败", "fail to get ip param");
//         AfxMessageBox(szLan);
    }
    return bRet;
}
void CDlgQuickAddIpc::OnBtnQuickSet() 
{
    SetIPParamConfig();
}

void CDlgQuickAddIpc::OnClickListSadpInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
    
    char szLan[256] = {0};
    POSITION posSadp = m_listSadpInfo.GetFirstSelectedItemPosition();
    if (posSadp == 0)
    {
        g_StringLanType(szLan, "请选择Sadp信息", "please select sadp info");
        AfxMessageBox(szLan);
        return;
    }
    int iSadpCurSel = m_listIPChan.GetNextSelectedItem(posSadp);

    m_csDevIP = m_struSadpInfoList.struSadpInfo[iSadpCurSel].struIP.sIpV4;
    m_csSubnetMask = m_struSadpInfoList.struSadpInfo[iSadpCurSel].struSubDVRIPMask.sIpV4;
    m_iDevPort = m_struSadpInfoList.struSadpInfo[iSadpCurSel].wPort;
	m_csGB28181DevID = m_struSadpInfoList.struSadpInfo[iSadpCurSel].szGB28181DevID;

    memcpy(m_byMacAddr, m_struSadpInfoList.struSadpInfo[iSadpCurSel].byMACAddr, MACADDR_LEN);

    UpdateData(FALSE);
	
	*pResult = 0;
}

void CDlgQuickAddIpc::OnBtnSaveSadpinfo() 
{
    char szLan[256] = {0};
    POSITION posSadp = m_listSadpInfo.GetFirstSelectedItemPosition();
    if (posSadp == 0)
    {
        g_StringLanType(szLan, "请选择Sadp信息", "please select sadp info");
        AfxMessageBox(szLan);
        return;
    }
    int iSadpCurSel = m_listIPChan.GetNextSelectedItem(posSadp);
    
    UpdateData(TRUE);
    NET_DVR_SADPINFO struSadpInfo = {0};
    NET_DVR_SADP_VERIFY struSadpVerify = {0};

    memcpy(&struSadpVerify.struOldIP, &m_struSadpInfoList.struSadpInfo[iSadpCurSel].struIP, sizeof(struSadpVerify.struOldIP));
    struSadpVerify.wOldPort = m_struSadpInfoList.struSadpInfo[iSadpCurSel].wPort;
    strncpy(struSadpVerify.chPassword, m_csPassword.GetBuffer(0), sizeof(struSadpVerify.chPassword));

    memcpy(&struSadpInfo, &m_struSadpInfoList.struSadpInfo[iSadpCurSel], sizeof(struSadpInfo));
    strncpy(struSadpInfo.struIP.sIpV4, m_csDevIP.GetBuffer(0), sizeof(struSadpInfo.struIP.sIpV4));
    strncpy(struSadpInfo.struSubDVRIPMask.sIpV4, m_csSubnetMask.GetBuffer(0), sizeof(struSadpInfo.struSubDVRIPMask.sIpV4));
	strncpy((char*)struSadpInfo.szGB28181DevID,m_csGB28181DevID,DEV_ID_LEN);
    if (NET_DVR_UpdateSadpInfo(m_lServerID, &struSadpVerify, &struSadpInfo))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_UpdateSadpInfo");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_UpdateSadpInfo");
        AfxMessageBox("Fail to update Sadp Info");
    }
}

void CDlgQuickAddIpc::OnBtnActivate() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_IPDEVICE_ACTIVATE_CFG   struActivateCfg = {0};
    struActivateCfg.dwSize = sizeof(struActivateCfg);
    struActivateCfg.byMode = 1;
    memcpy(struActivateCfg.sUserName, "admin", strlen("admin"));
    if (m_bIPCActivatePassword)
    {
        struActivateCfg.bySelfDefinePassword = 2;
    }
    else if (m_strActivatePwd != "")
    {
        struActivateCfg.bySelfDefinePassword = 1;
        memcpy(struActivateCfg.sPassword, m_strActivatePwd.GetBuffer(0), m_strActivatePwd.GetLength());
    }
    memcpy(struActivateCfg.unActivateDeviceInfo.struAddrInfo.struIp.sIpV4, m_csDevIP.GetBuffer(0), m_csDevIP.GetLength());
    struActivateCfg.unActivateDeviceInfo.struAddrInfo.wPort = m_iDevPort;
    memcpy(struActivateCfg.unActivateDeviceInfo.struAddrInfo.byMacAddr, m_byMacAddr, MACADDR_LEN);
    memcpy(struActivateCfg.unActivateDeviceInfo.struAddrInfo.sProtocolDesc, "HIKVISION", strlen("HIKVISION"));

    NET_DVR_STD_CONFIG  struCfg = {0};
    struCfg.lpInBuffer = &struActivateCfg;
    struCfg.dwInSize = sizeof(struActivateCfg);
    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_IPDEVICE_ACTIVATED, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IPDEVICE_ACTIVATED");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IPDEVICE_ACTIVATED");
    }

}
