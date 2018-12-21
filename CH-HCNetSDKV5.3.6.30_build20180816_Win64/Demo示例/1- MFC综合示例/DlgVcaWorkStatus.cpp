// DlgVcaWorkStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaWorkStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaWorkStatus dialog


CDlgVcaWorkStatus::CDlgVcaWorkStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaWorkStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaWorkStatus)
	m_iCpuLoad = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChanNum = -1;
    memset(&m_struDevWorkStatus, 0, sizeof(m_struDevWorkStatus));
}


void CDlgVcaWorkStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaWorkStatus)
	DDX_Control(pDX, IDC_COMBO_WORK_STATUS, m_comboWorkStatus);
	DDX_Control(pDX, IDC_LIST_CHAN_STATUS, m_listChanStatus);
	DDX_Text(pDX, IDC_EDIT_CPU_LOAD, m_iCpuLoad);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaWorkStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaWorkStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaWorkStatus message handlers

BOOL CDlgVcaWorkStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    InitWnd();	

    GetVcaDevWorkStatus(m_struDevWorkStatus);
    SetVcaDevWorkStatusToWnd(m_struDevWorkStatus);
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaWorkStatus::InitWnd()
{
    char szLan[128] = {0};
    m_comboWorkStatus.ResetContent();
    m_comboWorkStatus.AddString("Normal");
    m_comboWorkStatus.AddString("UnNormal");

    
    m_listChanStatus.DeleteAllItems();
    m_listChanStatus.SetExtendedStyle(m_listChanStatus.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    int nIndex = 0;
    
    //     BYTE	byJointed;				// 0-没有关联  1-已经关联
    //     BYTE	byRes1[3];
    //     NET_DVR_IPADDR	struIP;					// 关联的取流设备IP地址
    //     WORD	wPort;					// 关联的取流设备端口号
    //     WORD	wChannel;				// 关联的取流设备通道号
//     BYTE	byVcaChanStatus;		// 0 - 未启用 1 - 启用
    g_StringLanType(szLan, "关联", "ointed");
    m_listChanStatus.InsertColumn(nIndex, szLan, LVCFMT_RIGHT, 60, -1);
    nIndex++;
    
    g_StringLanType(szLan, "IP", "IP");
    m_listChanStatus.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 140, -1);
    nIndex++;

    g_StringLanType(szLan, "Port", "Port");
    m_listChanStatus.InsertColumn(nIndex, szLan, LVCFMT_LEFT,80, -1);
    nIndex++;

    g_StringLanType(szLan, "Channel", "Channel");
    m_listChanStatus.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 150, -1);
    nIndex++;

    g_StringLanType(szLan, "Enable", "Enable");
    m_listChanStatus.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 100, -1);
    nIndex++;

}

BOOL CDlgVcaWorkStatus::GetVcaDevWorkStatus(NET_DVR_VCA_DEV_WORKSTATUS &struDevWorkStatus)
{
    if (!NET_DVR_GetVcaDevWorkState(m_lServerID, &struDevWorkStatus))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetVcaDevWorkState");
        return FALSE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetVcaDevWorkState");
        return TRUE;
    }
}

void CDlgVcaWorkStatus::SetVcaDevWorkStatusToWnd(NET_DVR_VCA_DEV_WORKSTATUS &struDevWorkStatus)
{
    m_listChanStatus.DeleteAllItems();
    m_comboWorkStatus.SetCurSel(struDevWorkStatus.byDeviceStatus);
    m_iCpuLoad = struDevWorkStatus.byCpuLoad;
    
    for (int i = 0; i < m_lChanNum; i++)
    {
        m_listChanStatus.InsertItem(i, NULL, 0);
        SetVcaChanWorkStatusToWnd(struDevWorkStatus.struVcaChanStatus[i], i); 
    }
}


void CDlgVcaWorkStatus::SetVcaChanWorkStatusToWnd(NET_DVR_VCA_CHAN_WORKSTATUS &strVcaChanWorkStatus, int nIntem)
{
    int nIndex = 0;
//     {
//         BYTE	byJointed;				// 0-没有关联  1-已经关联
//         BYTE	byRes1[3];
//         NET_DVR_IPADDR	struIP;					// 关联的取流设备IP地址
//         WORD	wPort;					// 关联的取流设备端口号
//         WORD	wChannel;				// 关联的取流设备通道号
//         BYTE	byVcaChanStatus;		// 0 - 未启用 1 - 启用
//         BYTE	byRes2[19];				// 保留字节

    char szLan[128] = {0};

    if (strVcaChanWorkStatus.byJointed == 0)
    {
        sprintf(szLan, "No");
    }
    else
    {
        sprintf(szLan, "yes");
    }
    m_listChanStatus.SetItemText(nIntem, nIndex, szLan);
    nIndex++;

    m_listChanStatus.SetItemText(nIntem, nIndex, strVcaChanWorkStatus.struIP.sIpV4);
    nIndex++;

    sprintf(szLan, "%d", strVcaChanWorkStatus.wPort);
    m_listChanStatus.SetItemText(nIntem, nIndex, szLan);
    nIndex++;

    sprintf(szLan, "%d", strVcaChanWorkStatus.wChannel);
    m_listChanStatus.SetItemText(nIntem, nIndex, szLan);
    nIndex++;
    
    if (strVcaChanWorkStatus.byVcaChanStatus == 0)
    {
        sprintf(szLan, "No");
    }
    else
    {
        sprintf(szLan, "yes");
    }
    m_listChanStatus.SetItemText(nIntem, nIndex, szLan);
    nIndex++;
}

