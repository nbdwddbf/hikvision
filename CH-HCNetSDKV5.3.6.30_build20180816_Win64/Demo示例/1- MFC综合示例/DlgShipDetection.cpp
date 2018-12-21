// DlgShipDetection.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgShipDetection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
void CALLBACK g_fGetShipsNolList(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
/////////////////////////////////////////////////////////////////////////////
// CDlgShipDetection dialog

#define WM_SHIPS_NO_INFO_FINSH		WM_USER + 1
CDlgShipDetection::CDlgShipDetection(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShipDetection::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShipDetection)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgShipDetection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShipDetection)
	DDX_Control(pDX, IDC_LIST_SHIP_DETECTION, m_listShipDetection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShipDetection, CDialog)
	//{{AFX_MSG_MAP(CDlgShipDetection)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SHIP_INFO, OnButtonDeleteShipInfo)
	ON_MESSAGE(WM_SHIPS_NO_INFO_FINSH, StopShipsNoList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgShipDetection message handlers

BOOL CDlgShipDetection::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    //m_lShipDetectionHandle = -1;
    
    char szLanTemp[128] = {0};
    m_listShipDetection.SetExtendedStyle(m_listShipDetection.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLanTemp, "船只总计数", "total ships number");
    m_listShipDetection.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 95, -1);
    g_StringLanType(szLanTemp, "上行船只数", "up ships number");
    m_listShipDetection.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 95, -1);
    g_StringLanType(szLanTemp, "下行船只数", "down ships number");
    m_listShipDetection.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 95, -1);
    g_StringLanType(szLanTemp, "左行船只数", "left ships number");
    m_listShipDetection.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 95, -1);
    g_StringLanType(szLanTemp, "右行船只数", "right ships number");
    m_listShipDetection.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 95, -1);
	g_StringLanType(szLanTemp, "相对时标", "relative time");
    m_listShipDetection.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 90, -1);
	g_StringLanType(szLanTemp, "绝对时标", "absolute time");
    m_listShipDetection.InsertColumn(6, szLanTemp, LVCFMT_LEFT, 90, -1);
	g_StringLanType(szLanTemp, "数据状态", "data State");
    m_listShipDetection.InsertColumn(7, szLanTemp, LVCFMT_LEFT, 90, -1);
    

	m_lShipDetectionHandle = -1;
    return TRUE;

}


void CDlgShipDetection::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
    if (m_lShipDetectionHandle>=0)
    {
        StopShipsNoList(NULL, NULL);
    }
    
    NET_DVR_SHIPSCOUNT_COND struShipCond = {0};
    struShipCond.dwSize = sizeof(struShipCond);
    struShipCond.dwChannel = m_lChannel;
	
    m_lShipDetectionHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_SHIPSDETECTION_COUNT, &struShipCond, sizeof(struShipCond), g_fGetShipsNolList, this);
    if (m_lShipDetectionHandle < 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SHIPSDETECTION_COUNT");
        return;
    }
    else
    {
        m_listShipDetection.DeleteAllItems();
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SHIPSDETECTION_COUNT");
	}

}

void CALLBACK g_fGetShipsNolList(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgShipDetection* pDlg = (CDlgShipDetection*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcGetShipsNoList(dwType,lpBuffer,dwBufLen);
    
}

void CDlgShipDetection::AddShipsNoListItem(const NET_DVR_SHIPSCOUNT_CFG &Item)
{
    BOOL bTemp = FALSE;
    
    int iItemCount = m_listShipDetection.GetItemCount();
    m_listShipDetection.InsertItem(iItemCount, "");
    
    char szStr[128] = {0};

    //船只总计数
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.dwTotalCount);
    m_listShipDetection.SetItemText(iItemCount, 0, szStr);
    
    //上行船只数
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.dwUpShipsCount);
    m_listShipDetection.SetItemText(iItemCount, 1, szStr);

	//下行船只数
	memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.dwDownShipsCount);
    m_listShipDetection.SetItemText(iItemCount, 2, szStr);

	//左行船只数
	memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.dwLeftShipsCount);
    m_listShipDetection.SetItemText(iItemCount, 3, szStr);

	//右行船只数
	memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.dwRightShipsCount);
    m_listShipDetection.SetItemText(iItemCount, 4, szStr);
	
    //相对时标
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.dwRelativeTime);
    m_listShipDetection.SetItemText(iItemCount, 5, szStr);
    
    //绝对时标
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.dwAbsTime);
    m_listShipDetection.SetItemText(iItemCount, 6, szStr);
	
    //数据状态类型
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.byDataType);
    m_listShipDetection.SetItemText(iItemCount, 7, szStr);
}

void CDlgShipDetection::ProcGetShipsNoList(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
	HWND hWnd = this->GetSafeHwnd();
    if (NULL == hWnd)
    {
        return;
    }

    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
		
		NET_DVR_SHIPSCOUNT_CFG* pConnectDevCfg = (NET_DVR_SHIPSCOUNT_CFG*)lpBuffer;
        AddShipsNoListItem(*pConnectDevCfg);  
    }

    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
		DWORD dwStatus = *(DWORD*)lpBuffer;
		if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
		{

			::PostMessage(hWnd,WM_SHIPS_NO_INFO_FINSH, NULL,1);
        }
    }
}

LRESULT CDlgShipDetection::StopShipsNoList(WPARAM wParam, LPARAM lParam)
{
    char szLan[128] = {0};
    if (m_lShipDetectionHandle>=0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lShipDetectionHandle))
        {
            g_StringLanType(szLan, "获取船只计数信息停止失败", "Failed to get ships to stop counting information");
            AfxMessageBox(szLan);
            return -1;
        }
		m_lShipDetectionHandle = -1;
    }
	return 0;
}


void CDlgShipDetection::OnButtonDeleteShipInfo() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &m_lChannel;
    struControl.dwCondSize = 4;  
	BOOL bRet = NET_DVR_STDControl(m_lUserID, NET_DVR_SHIPSCOUNT_DELETE_CTRL, &struControl);
	if (!bRet)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SHIPSCOUNT_DELETE_CTRL");
		return;
	}
	else
	{
		m_listShipDetection.DeleteAllItems();
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SHIPSCOUNT_DELETE_CTRL");
	}
	
}
