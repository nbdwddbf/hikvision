// DlgConnectList.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgConnectList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_AC_GET_DEV_LIST_FINISH 10001
void CALLBACK g_fGetDevlList(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);

/////////////////////////////////////////////////////////////////////////////
// DlgConnectList dialog


DlgConnectList::DlgConnectList(CWnd* pParent /*=NULL*/)
	: CDialog(DlgConnectList::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgConnectList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

DlgConnectList::~DlgConnectList()
{
}

void DlgConnectList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgConnectList)
	DDX_Control(pDX, IDC_LIST_CONNECT_DEV, m_listGetConnectDev);
    DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comChannel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DlgConnectList, CDialog)
	//{{AFX_MSG_MAP(DlgConnectList)
	ON_BN_CLICKED(IDC_GET, OnBtnGetDevList)
    ON_MESSAGE(WM_AC_GET_DEV_LIST_FINISH, OnMsgGetDevListFinish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgConnectList message handlers

BOOL DlgConnectList::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    m_lDevListHandle = -1;
    
    char szLanTemp[128] = {0};
    m_listGetConnectDev.SetExtendedStyle(m_listGetConnectDev.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLanTemp, "序列号", "Serial number");
    m_listGetConnectDev.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "物理地址", "Address");
    m_listGetConnectDev.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 150, -1);
    g_StringLanType(szLanTemp, "设备IP", "Equipment IP");
    m_listGetConnectDev.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "接入时间", "Access time");
    m_listGetConnectDev.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 100, -1);
    
    m_comChannel.ResetContent();
    m_comChannel.InsertString(0,"无效");
    m_comChannel.InsertString(1,"网卡1");
    m_comChannel.InsertString(2,"网卡2");
    m_comChannel.SetCurSel(1);
    
    return TRUE;
}

void CALLBACK g_fGetDevlList(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    DlgConnectList* pDlg = (DlgConnectList*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcGetDevList(dwType,lpBuffer,dwBufLen);
    
}

void DlgConnectList::ProcGetDevList(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_CONNECTDEV_CFG* pConnectDevCfg = (NET_DVR_CONNECTDEV_CFG*)lpBuffer;
        AddDevListItem(*pConnectDevCfg);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_AC_GET_DEV_LIST_FINISH,0,0);
        }
    }
}

void DlgConnectList::AddDevListItem(const NET_DVR_CONNECTDEV_CFG &Item)
{
    BOOL bTemp = FALSE;
    
    int iItemCount = m_listGetConnectDev.GetItemCount();
    m_listGetConnectDev.InsertItem(iItemCount, "");
    
    char szStr[128] = {0};

    //0序列号
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.byID);
    m_listGetConnectDev.SetItemText(iItemCount, 0, szStr);
    
    //1物理地址
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%02X:%02X:%02X:%02X:%02X:%02X", Item.byMACAddr[0], Item.byMACAddr[1], Item.byMACAddr[2], Item.byMACAddr[3], Item.byMACAddr[4], Item.byMACAddr[5]);
    //szStr[MACADDR_LEN] = 0;
    m_listGetConnectDev.SetItemText(iItemCount, 1, szStr);

    //2设备IP
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%s", Item.struDVRIP.sIpV4);
    m_listGetConnectDev.SetItemText(iItemCount, 2, szStr);
    
    //3接入时间
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr,"%04d-%02d-%02d-%02d-%02d-%02d",Item.struConnectTime.dwYear, \
        Item.struConnectTime.dwMonth, Item.struConnectTime.dwDay, Item.struConnectTime.dwHour,\
        Item.struConnectTime.dwMinute, Item.struConnectTime.dwSecond);
    m_listGetConnectDev.SetItemText(iItemCount, 3, szStr);

}

LRESULT DlgConnectList::OnMsgGetDevListFinish(WPARAM wParam,LPARAM lParam)
{
    StopDevlList();
    return 0;
}

void DlgConnectList::OnBtnGetDevList() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    if (m_lDevListHandle>=0)
    {
        StopDevlList();
    }
    
    NET_DVR_CONNECTDEV_COND struConnectDevCond = {0};
    struConnectDevCond.dwSize = sizeof(struConnectDevCond);
    struConnectDevCond.dwChannel = m_comChannel.GetCurSel();

    m_lDevListHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_GET_CONNECT_LIST,&struConnectDevCond,sizeof(struConnectDevCond),g_fGetDevlList, this);
    if (m_lDevListHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CONNECT_LIST");
        return;
    }
    else
    {
        m_listGetConnectDev.DeleteAllItems();
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CONNECT_LIST");
	}
}

void DlgConnectList::StopDevlList()
{
    char szLan[128] = {0};
    if (m_lDevListHandle>=0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lDevListHandle))
        {
            g_StringLanType(szLan, "获取设备列表停止失败", "Dev List Stop Failed");
            AfxMessageBox(szLan);
            return;
        }
        m_lDevListHandle = -1;
    }
}
