// DlgVISRegisterInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVISRegisterInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVISRegisterInfo dialog


CDlgVISRegisterInfo::CDlgVISRegisterInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVISRegisterInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVISRegisterInfo)
		// NOTE: the ClassWizard will add member initialization here
    m_lUserID = -1;
    m_iDevIndex = -1;
	//}}AFX_DATA_INIT
}


void CDlgVISRegisterInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVISRegisterInfo)
	DDX_Control(pDX, IDC_LIST_REGISTER_INFO, m_lstRegisterInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVISRegisterInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgVISRegisterInfo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVISRegisterInfo message handlers

void CDlgVISRegisterInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    m_lHande = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_GET_VIS_REGISTER_INFO,NULL, 0,NULL,this);
	if (m_lHande < 0)
	{
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GET_VIS_REGISTER_INFO");
        m_bGetNext = FALSE;
        return;
	}
    else
    {

        m_lstRegisterInfo.DeleteAllItems();
        m_bGetNext = TRUE;
        DWORD dwThreadId;
        m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetRegisterDevInfoThread), this, 0, &dwThreadId);
    }
}

BOOL CDlgVISRegisterInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_lHande = -1;
	// TODO: Add extra initialization here
    m_lstRegisterInfo.SetExtendedStyle(m_lstRegisterInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    char szLan[128] = {0};
    g_StringLanType(szLan, "序号", "Serial No.");
    m_lstRegisterInfo.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);
    
    g_StringLanType(szLan, "ID", "ID");
    m_lstRegisterInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 50, -1);
    
    g_StringLanType(szLan, "设备编号", "DevNum");
    m_lstRegisterInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 120, -1);
    
    g_StringLanType(szLan, "MAC地址", "MAC ADDR");
    m_lstRegisterInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 140, -1);
    
    g_StringLanType(szLan, "设备序列号", "Serial No");
    m_lstRegisterInfo.InsertColumn(4, szLan, LVCFMT_LEFT, 200, -1);
    
    g_StringLanType(szLan, "设备IP地址", "IP Addr");
    m_lstRegisterInfo.InsertColumn(5, szLan, LVCFMT_LEFT, 120, -1);
    
    g_StringLanType(szLan, "注册机类型", "RegisterDev Type");
    m_lstRegisterInfo.InsertColumn(6, szLan, LVCFMT_LEFT, 100, -1);

    g_StringLanType(szLan, "注册时间", "Register Time");
    m_lstRegisterInfo.InsertColumn(7, szLan, LVCFMT_LEFT, 180, -1);
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVISRegisterInfo::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	if (m_lHande >-1)
	{
        if (!NET_DVR_StopRemoteConfig(m_lHande))
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_StopRemoteConfig");
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_StopRemoteConfig");
            m_lHande = -1;
            m_bGetNext = FALSE;
        }
	}
}

DWORD WINAPI CDlgVISRegisterInfo::GetRegisterDevInfoThread(LPVOID lpVehInfo)
{
    CDlgVISRegisterInfo* pThis = reinterpret_cast<CDlgVISRegisterInfo*>(lpVehInfo);
    int iRet = 0;
    char szLan[128] = {0};
    char szInfoBuf[128] = {0};
    NET_DVR_VIS_REGISTER_INFO struRegisterInfo = {0};
    while (pThis->m_bGetNext)
    {
        memset(&struRegisterInfo,0,sizeof(struRegisterInfo));
        iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHande, &struRegisterInfo, sizeof(struRegisterInfo)); 
        if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
        {
            
            DWORD dwListCount = pThis->m_lstRegisterInfo.GetItemCount();
            int nIndex = 0;
            
            
            char szLan[5*1024] = {0};
            
            
            sprintf(szLan, "%d",dwListCount);   
            pThis->m_lstRegisterInfo.InsertItem(dwListCount, szLan);
            
            nIndex++;

            sprintf(szLan, "%d", struRegisterInfo.dwID);
            pThis->m_lstRegisterInfo.SetItemText(dwListCount,nIndex, szLan);
            nIndex++;
            
            sprintf(szLan, "%s", struRegisterInfo.szDevNumber);
            pThis->m_lstRegisterInfo.SetItemText(dwListCount,nIndex, szLan);
            nIndex ++;
            
            sprintf(szLan, "%02x:%02x:%02x:%02x:%02x:%02x", struRegisterInfo.byMACAddr[0],struRegisterInfo.byMACAddr[1],\
                struRegisterInfo.byMACAddr[2],struRegisterInfo.byMACAddr[3],struRegisterInfo.byMACAddr[4],struRegisterInfo.byMACAddr[5]);

            pThis->m_lstRegisterInfo.SetItemText(dwListCount,nIndex, szLan);
            nIndex ++;

            sprintf(szLan, "%s", struRegisterInfo.sSerialNumber);
            pThis->m_lstRegisterInfo.SetItemText(dwListCount,nIndex, szLan);
            nIndex ++;

            sprintf(szLan, "%s", struRegisterInfo.struDevIP.sIpV4);
            pThis->m_lstRegisterInfo.SetItemText(dwListCount,nIndex, szLan);
            nIndex ++;

            switch (struRegisterInfo.byRegisterType)
            {
            case 1:
                g_StringLanType(szLan,"门口机","");
                break;
            case 2:
                g_StringLanType(szLan,"管理机","");
                break;
            case 3:
                g_StringLanType(szLan,"室内机","");
                break;
            case 4:
                g_StringLanType(szLan,"围墙机","");
                break;
            case 5:
                g_StringLanType(szLan,"别墅门口机","");
                break;
            case 6:
                g_StringLanType(szLan,"二次确认机","");
                break;
            case 7:
                g_StringLanType(szLan,"8700客户端","");
                break;
            case 8:
                g_StringLanType(szLan,"4200客户端","");
                break;
            default:
                g_StringLanType(szLan,"未知","Unkown");
                break;
            }
            pThis->m_lstRegisterInfo.SetItemText(dwListCount,nIndex, szLan);
            nIndex ++;

            sprintf(szLan, "%04d-%02d-%02d %02d:%02d:%02d", struRegisterInfo.struRegisterTime.wYear,struRegisterInfo.struRegisterTime.byMonth,\
                struRegisterInfo.struRegisterTime.byDay,\
                struRegisterInfo.struRegisterTime.byHour,struRegisterInfo.struRegisterTime.byMinute,struRegisterInfo.struRegisterTime.bySecond);
            pThis->m_lstRegisterInfo.SetItemText(dwListCount,nIndex, szLan);
            nIndex ++;

        }
        else
        {
            if (iRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
            {
                Sleep(5);
                continue;
            }
            if (iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
            {
                g_StringLanType(szLan, "查询结束!", "Search Finished!");
                AfxMessageBox(szLan);
                break;
            }
            else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
            {
                g_StringLanType(szLan, "查询失败", "Search failed");
                AfxMessageBox(szLan);
                break;
            }
            else
            {
                g_StringLanType(szLan, "未知状态", "Unknown status");
                AfxMessageBox(szLan);
                break;
            }
        }
    }
    
    return 0;
}