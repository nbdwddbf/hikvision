// DlgOnlineUserList.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgOnlineUserList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_AC_GET_ONLINE_USER_LIST_FINISH 10001
void CALLBACK g_fGetOnlineUserlList(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
/////////////////////////////////////////////////////////////////////////////
// DlgOnlineUserList dialog


DlgOnlineUserList::DlgOnlineUserList(CWnd* pParent /*=NULL*/)
	: CDialog(DlgOnlineUserList::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgOnlineUserList)
	//}}AFX_DATA_INIT
}


void DlgOnlineUserList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgOnlineUserList)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_dwChannel);
	DDX_Control(pDX, IDC_LIST_ONLINE_USER, m_listOnlineUser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgOnlineUserList, CDialog)
	//{{AFX_MSG_MAP(DlgOnlineUserList)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
    ON_MESSAGE(WM_AC_GET_ONLINE_USER_LIST_FINISH, OnMsgGetOnlineUserListFinish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgOnlineUserList message handlers

BOOL DlgOnlineUserList::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    m_lOnlineUserHandle = -1;
    
    char szLanTemp[128] = {0};
    m_listOnlineUser.SetExtendedStyle(m_listOnlineUser.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLanTemp, "用户序列号", "Serial number");
    m_listOnlineUser.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLanTemp, "用户类型", "User Type");
    m_listOnlineUser.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLanTemp, "IP地址", "user IP");
    m_listOnlineUser.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 150, -1);
    g_StringLanType(szLanTemp, "登录时间", "login time");
    m_listOnlineUser.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLanTemp, "用户名", "user name");
    m_listOnlineUser.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLanTemp, "数据类型", "Data Type");
    m_listOnlineUser.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 100, -1);

    m_dwChannel.ResetContent();
    CString csStr;
    char szLan[128] = {0};
    for (int i=0; i<512; i++)
    {
        g_StringLanType(szLan, "", "");
        csStr.Format("%s%d", szLan, i);
        m_dwChannel.InsertString(i, csStr);
    }
    m_dwChannel.SetCurSel(0);
    
    return TRUE;
}

void CALLBACK g_fGetOnlineUserlList(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    DlgOnlineUserList* pDlg = (DlgOnlineUserList*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcGetOnlineUserList(dwType,lpBuffer,dwBufLen);
    
}

void DlgOnlineUserList::ProcGetOnlineUserList(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_ONLINEUSER_CFG* pConnectDevCfg = (NET_DVR_ONLINEUSER_CFG*)lpBuffer;
        AddOnlineUserListItem(*pConnectDevCfg);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_AC_GET_ONLINE_USER_LIST_FINISH,0,0);
        }
    }
}

void DlgOnlineUserList::AddOnlineUserListItem(const NET_DVR_ONLINEUSER_CFG &Item)
{
    BOOL bTemp = FALSE;
    
    int iItemCount = m_listOnlineUser.GetItemCount();
    m_listOnlineUser.InsertItem(iItemCount, "");
    
    char szStr[128] = {0};

    //0序列号
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.byID);
    m_listOnlineUser.SetItemText(iItemCount, 0, szStr);
    
    //1用户类型
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.byUserType);
    m_listOnlineUser.SetItemText(iItemCount, 1, szStr);

    //2IP地址
    memset(szStr, 0, sizeof(szStr));
    if(ValidIPv6((BYTE *)Item.struIpAddr.byIPv6))
    {
        sprintf(szStr, "%s", Item.struIpAddr.byIPv6);
    }
    else
    {
        sprintf(szStr, "%s", Item.struIpAddr.sIpV4);
    }
    
    m_listOnlineUser.SetItemText(iItemCount, 2, szStr);
    
    //3登陆时间
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr,"%04d-%02d-%02dT%02d-%02d-%02d",Item.struLoginTime.wYear, \
        Item.struLoginTime.byMonth, Item.struLoginTime.byDay, Item.struLoginTime.byHour,\
        Item.struLoginTime.byMinute, Item.struLoginTime.bySecond);
    m_listOnlineUser.SetItemText(iItemCount, 3, szStr);

    //4用户名
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%0s", Item.szUserName);
    m_listOnlineUser.SetItemText(iItemCount, 4, szStr);

    //5数据类型
    memset(szStr, 0, sizeof(szStr));
    if (0 == Item.byDataType)
    {
        sprintf(szStr, "检测中");
    } 
    else if (1 == Item.byDataType)
    {
        sprintf(szStr, "开始");
    }
    else if (2 == Item.byDataType)
    {
        sprintf(szStr, "结束");
    }
    m_listOnlineUser.SetItemText(iItemCount, 5, szStr);
}

BOOL DlgOnlineUserList::ValidIPv6(BYTE *ip)
{
    if (strlen((char *)ip) > 2 && strchr((char *)ip, ':') != NULL)
    {
        return TRUE;
    }
    return FALSE;
}

LRESULT DlgOnlineUserList::OnMsgGetOnlineUserListFinish(WPARAM wParam,LPARAM lParam)
{
    StopOnlineUserlList();
    return 0;
}

void DlgOnlineUserList::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    if (m_lOnlineUserHandle>=0)
    {
        StopOnlineUserlList();
    }
    
    NET_DVR_ONLINEUSER_COND struOnlineUserCond = {0};
    struOnlineUserCond.dwSize = sizeof(struOnlineUserCond);
    struOnlineUserCond.dwChannel = m_dwChannel.GetCurSel();

    m_lOnlineUserHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_GET_ONLINEUSER_INFO,&struOnlineUserCond,sizeof(struOnlineUserCond),g_fGetOnlineUserlList, this);
    if (m_lOnlineUserHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ONLINEUSER_INFO");
        return;
    }
    else
    {
        m_listOnlineUser.DeleteAllItems();
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ONLINEUSER_INFO");
	}
}

void DlgOnlineUserList::StopOnlineUserlList()
{
    char szLan[128] = {0};
    if (m_lOnlineUserHandle>=0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lOnlineUserHandle))
        {
            g_StringLanType(szLan, "获取在线用户列表停止失败", "online user List Stop Failed");
            AfxMessageBox(szLan);
            return;
        }
        m_lOnlineUserHandle = -1;
    }
}
