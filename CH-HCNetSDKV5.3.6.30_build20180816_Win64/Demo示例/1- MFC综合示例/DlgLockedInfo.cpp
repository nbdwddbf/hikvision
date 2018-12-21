// DlgAlarmHostTriggerCode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLockedInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


DWORD WINAPI CDlgLockedInfo::GetLockedListThread(LPVOID lpArg)
{
	CDlgLockedInfo* pThis = reinterpret_cast<CDlgLockedInfo*>(lpArg);
	int bRet = 0;
	char szLan[128] = {0};
    pThis->m_iStruCount = 0;
	while(pThis->m_bGetNext)
	{
        if (pThis->m_iStruCount == MAX_LOCKED_NUM)
        {
            g_StringLanType(szLan, "设备返回的数目超过1024个", "over max num");
            AfxMessageBox(szLan);
            break;
        }
		bRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_lpStruLockedInfo[pThis->m_iStruCount], sizeof(NET_DVR_LOCKED_INFO));
		if (bRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddInfoToDlg(&(pThis->m_lpStruLockedInfo[pThis->m_iStruCount]));
			pThis->m_iStruCount++;
		}
		else
		{
			if (bRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
                g_StringLanType(szLan, "正在获取信息.....", "Getting locked info......");
                g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, szLan);
				Sleep(50);
				continue;
			}
			if (bRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
				g_StringLanType(szLan, "获取锁定列表结束!", "Get locked info Ending");
				g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, szLan);
				//AfxMessageBox(szLan);
				break;
			}
			else if(bRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "获取锁定列表失败!", "Get locked info failed");
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
	if (-1 != pThis->m_lHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lHandle))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
			pThis->m_bGetNext = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_bGetNext = FALSE;
			pThis->m_lHandle = -1;
			pThis->m_btnGet.EnableWindow(TRUE);
		}
	}
	return 0 ;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgLockedInfo dialog

CDlgLockedInfo::CDlgLockedInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLockedInfo::IDD, pParent)
	, m_iLastItem(-1)
	, m_lHandle(-1)
	, m_iDeviceIndex(-1)
	, m_lUserID(-1)
	, m_lpStruLockedInfo(NULL)
	, m_bGetNext(FALSE)
    , m_iStruCount(0)
{
	//{{AFX_DATA_INIT(CDlgLockedInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgLockedInfo::~CDlgLockedInfo()
{
	delete[] m_lpStruLockedInfo;
}
void CDlgLockedInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLockedInfo)
	DDX_Control(pDX, IDC_BTN_GET, m_btnGet);
	DDX_Control(pDX, IDC_LIST_TRIGGER, m_listLockedInfo);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLockedInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgLockedInfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TRIGGER, OnDblclkListTrigger)
	ON_EN_KILLFOCUS(IDC_EDIT_TEXT, OnKillfocusEditText)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TRIGGER, OnClickListTrigger)
	ON_BN_CLICKED(IDC_BTN_UNLOCK_ALL, OnBtnUnlockAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLockedInfo message handlers

BOOL CDlgLockedInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	
	CString csStr;
	int i = 0;
	char szLan[128] = {0};
	m_lpStruLockedInfo = new NET_DVR_LOCKED_INFO[MAX_LOCKED_NUM];
	memset(m_lpStruLockedInfo, 0, sizeof(NET_DVR_LOCKED_INFO)*MAX_LOCKED_NUM);
	
	RECT  m_rect;
	m_listLockedInfo.GetClientRect(&m_rect); //获取list的客户区
	m_listLockedInfo.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT); //设置list风格
	
	g_StringLanType(szLan, "锁定类型", "Locked Type");
	m_listLockedInfo.InsertColumn(0, szLan, LVCFMT_LEFT, m_rect.right/6);
	g_StringLanType(szLan, "锁定信息", "Information");
	m_listLockedInfo.InsertColumn(1, szLan, LVCFMT_LEFT, m_rect.right/6);

	
// 	m_listLockedInfo.InsertItem(0,_T("001"));
// 	m_listLockedInfo.SetItemText(0,1,_T("离线"));
// 	m_listLockedInfo.SetItemText(0,2,_T("1"));
// 	m_listLockedInfo.SetItemText(0,3,_T("1"));
// 	m_listLockedInfo.SetItemText(0,4,_T("测试区"));
// 	m_listLockedInfo.SetItemText(0,5,_T("单模块"));
// 	
// 	m_listLockedInfo.InsertItem(1,_T("001"));
// 	m_listLockedInfo.SetItemText(1,1,_T("在线"));
// 	m_listLockedInfo.SetItemText(1,2,_T("1"));
// 	m_listLockedInfo.SetItemText(1,3,_T("1"));
// 	m_listLockedInfo.SetItemText(1,4,_T("9楼"));
// 	m_listLockedInfo.SetItemText(1,5,_T("8路触发器"));
	m_iRowCount = m_listLockedInfo.GetItemCount();  //获取行数
	
	m_bNeedSave = FALSE; //初始化为FLASE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLockedInfo::OnDblclkListTrigger(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
// 	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
// 	CRect  EditRect;
// 	m_iItem = pEditCtrl->iItem;
// 	m_iSubItem = pEditCtrl->iSubItem;
// 	
// 	if (m_iItem == -1)
// 	{
// 		return;
// 	}
// 	if (0==m_iSubItem || 1==m_iSubItem || 5==m_iSubItem)
// 	{
// 		return;
// 	}
// 	
// 	if (m_iItem < m_iRowCount)
// 	{	
// 		m_listLockedInfo.GetSubItemRect(m_iItem,m_iSubItem,LVIR_LABEL,EditRect);
// 		m_bNeedSave = TRUE;
// 		m_Edit.SetParent(&m_listLockedInfo); //将list control设置为父窗口,生成的Edit才能正确定位
// 		
// 		EditRect.SetRect(EditRect.left,EditRect.top,EditRect.left+m_listLockedInfo.GetColumnWidth(m_iSubItem),EditRect.bottom);
// 		
// 		//将选中的list控件中的内容copy到edit控件中
// 		CString strItem = m_listLockedInfo.GetItemText(m_iItem,m_iSubItem);
// 		m_Edit.MoveWindow(&EditRect);
// 		m_Edit.ShowWindow(SW_SHOW);
// 		m_Edit.SetWindowText(strItem);
// 		m_Edit.SetFocus();//设置为焦点
// 		m_Edit.SetSel(0,-1);  //0,-1表示单元格内容全选中
// 	}
// 	else
// 	{
// 		m_Edit.ShowWindow(SW_HIDE);
// 	}
	*pResult = 0;
}

void CDlgLockedInfo::OnKillfocusEditText() 
{
	// TODO: Add your control notification handler code here
	CString  csEditStr;
	char  szListStr[NAME_LEN];
	m_listLockedInfo.GetItemText(m_iItem, m_iSubItem, szListStr, NAME_LEN);
	m_Edit.GetWindowText(csEditStr); 
	if (csEditStr.Compare(szListStr))
	{
		m_listLockedInfo.SetItemText(m_iItem, m_iSubItem, csEditStr); 
		m_iLastItem = m_iItem;
	}	
	m_Edit.ShowWindow(SW_HIDE);
}


void CDlgLockedInfo::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szStr[128] = {0};
	if (m_iLastItem == -1)
	{
		g_StringLanType(szStr, "没有选择", "No choose");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szStr);
		return;
	}
	m_listLockedInfo.GetItemText(m_iLastItem, 0, szStr, 128);

    NET_DVR_UNLOCK_INFO struUnLock = {0};
	struUnLock.dwSize = sizeof(struUnLock);

    struUnLock.byUnlockType = 1;
    struUnLock.byIPVersion = m_lpStruLockedInfo[m_iLastItem].byIPType;
    memcpy(&struUnLock.struIPAddr, &m_lpStruLockedInfo[m_iLastItem].struIPAddress, sizeof(struUnLock.struIPAddr));

	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_UNLOCK_USER, &struUnLock, sizeof(struUnLock)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "unlock IP failed");
		return;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "unlock IP successful");
	}
}

void CDlgLockedInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

    UpdateData(TRUE);
	char szLan[128] = {0};
	m_listLockedInfo.DeleteAllItems();
	m_iRowCount = 0;
	if (m_lHandle>=0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	}
	else
	{
		m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_LOCKED_INFO_LIST, NULL, 0, NULL, this);
		if (m_lHandle>=0)
		{
			m_bGetNext = TRUE;
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			DWORD dwThreadId;
			m_hGetInfoThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetLockedListThread),this,0,&dwThreadId);
			GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Start Remote Config failed");
			return;
		}
	}
}

void CDlgLockedInfo::AddInfoToDlg(LPNET_DVR_LOCKED_INFO lpInter) 
{
	char szStr[128] = {0};
    char szInfo[128] = {0};
	//锁定类型
    if (1 == lpInter->byIPType)
    {
        sprintf(szStr, "%s", "IPV4");
        memcpy(szInfo, lpInter->struIPAddress.sIpV4, sizeof(lpInter->struIPAddress.sIpV4)); 
    }
    else if(2 == lpInter->byIPType)
    {
        sprintf(szStr, "%s", "IPV6");
        memcpy(szInfo, lpInter->struIPAddress.byIPv6, sizeof(lpInter->struIPAddress.byIPv6)); 
    }
    else
    {
        sprintf(szStr, "%s", "未知类型");
    }

	m_listLockedInfo.InsertItem(m_iRowCount, szStr);
	//锁定信息
    m_listLockedInfo.SetItemText(m_iRowCount++, 1, szInfo);
}

void CDlgLockedInfo::OnCancel()
{
	m_bGetNext = FALSE;
	if(WAIT_TIMEOUT == WaitForSingleObject(m_hGetInfoThread, 3000))
	{
		TerminateThread(m_hGetInfoThread, 0);
	}
	m_hGetInfoThread = NULL;
	CDialog::OnCancel();
}

void CDlgLockedInfo::OnClickListTrigger(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
    CRect  EditRect;
    m_iItem = pEditCtrl->iItem;
    m_iSubItem = pEditCtrl->iSubItem;
    
    if (m_iItem == -1)
    {
        return;
    }
    
    m_iLastItem = m_iItem;
	*pResult = 0;
}

void CDlgLockedInfo::OnBtnUnlockAll() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_UNLOCK_INFO struUnLock = {0};
    struUnLock.dwSize = sizeof(struUnLock);
    
    struUnLock.byUnlockType = 2;
    
    if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_UNLOCK_USER, &struUnLock, sizeof(struUnLock)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "unlock all IP failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "unlock all IP successful");
	}
}
