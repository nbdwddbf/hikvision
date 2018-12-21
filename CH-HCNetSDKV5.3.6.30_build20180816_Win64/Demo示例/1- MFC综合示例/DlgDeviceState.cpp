/**********************************************************
FileName:    DlgDeviceState.cpp
Description: device state dialog, in 'configuration' function     
Date:        2008/05/17
Note: 		 <global>struct, define refer to GeneralDef.h, global variables and functions refer to ClientDemo.cpp     
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgDeviceState.h"
#include ".\dlgdevicestate.h"
#include "DlgLinkStatus.h"


#define WM_STATE_ADD_TOLIST 1001
#define WM_STATE_FINISH 1002
void CALLBACK g_fGetStateCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);

/*********************************************************
  Function:	CDlgDeviceState
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgDeviceState, CDialog)
CDlgDeviceState::CDlgDeviceState(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceState::IDD, pParent)
	, m_csLocalNodeName(_T(""))
	, m_csDeviceState(_T(""))
	, m_iDeviceIndex(-1)
	, m_csRecState(_T(""))
	, m_csSignalState(_T(""))
	, m_csHardWareState(_T(""))
	, m_csBitrate(_T(""))
	, m_csDiskVolume(_T(""))
	, m_csDiskFreeSpace(_T(""))
	, m_csDiskState(_T(""))
	, m_lLoginID(-1)
	, m_csDeviceIP(_T(""))
	, m_csAllBitRate(_T(""))
{
    m_lGetStateHandle = -1;
    m_dwHddIndex = 0;
    m_dwChannelIndex = 0;
}

/*********************************************************
  Function:	~CDlgDeviceState
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgDeviceState::~CDlgDeviceState()
{
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		map between control and variable
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgDeviceState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeviceState)

	DDX_Control(pDX, IDC_LIST_CHAN_STATE, m_listChanState);
	DDX_Control(pDX, IDC_LIST_DISK_STATE, m_listDiskState);
	DDX_Text(pDX, IDC_STATIC_DEV_STATE_IP, m_csDeviceIP);
	DDX_Text(pDX, IDC_STATIC_HUMIDITY, m_csHumidity);
	DDX_Text(pDX, IDC_STATIC_TEMPERATURE, m_csTemperature);
    //}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		map between control and function
  Input:	
  Output:	
  Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgDeviceState, CDialog)
	//{{AFX_MSG_MAP(CDlgDeviceState)
	ON_BN_CLICKED(ID_BTN_REFRESH, OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_LINK_STATUS, OnBtnLinkStatus)
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_STATE_ADD_TOLIST, &CDlgDeviceState::OnStateAddTolist)
    ON_MESSAGE(WM_STATE_FINISH, &CDlgDeviceState::OnStateFinish)
END_MESSAGE_MAP()


/*********************************************************
  Function:	OnInitDialog
  Desc:		initialize device state box
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgDeviceState::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	char szLan[128] = {0};
	g_StringLanType(szLan, "通道号", "Chan No.");
	m_listChanState.InsertColumn(0, szLan, LVCFMT_LEFT, 90, -1);
	g_StringLanType(szLan, "录像状态", "Record Status");
	m_listChanState.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "信号状态", "Signal Status");
	m_listChanState.InsertColumn(2, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "硬件状态", "Hardware Status");
	m_listChanState.InsertColumn(3, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "连接数", "Link Nums");
	m_listChanState.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "当前码率(bps)", "Current Bitrate(bps)");
	m_listChanState.InsertColumn(5, szLan,LVCFMT_LEFT,110, -1);
	g_StringLanType(szLan, "客户端", "Client IP");
	m_listChanState.InsertColumn(6, szLan,LVCFMT_LEFT,80, -1);
	g_StringLanType(szLan, "IPC链接数", "IPC link No.");
	m_listChanState.InsertColumn(7, szLan,LVCFMT_LEFT,80, -1);
	g_StringLanType(szLan, "实际码率总和", "All Bit Rate");
	m_listChanState.InsertColumn(8, szLan,LVCFMT_LEFT,80, -1);

	g_StringLanType(szLan, "硬盘号", "HD No.");
	m_listDiskState.InsertColumn(0, szLan, LVCFMT_LEFT, 90, -1);
	g_StringLanType(szLan, "硬盘容量(MB)", "HD Capacity");
	m_listDiskState.InsertColumn(1, szLan, LVCFMT_LEFT, 130, -1);
	g_StringLanType(szLan, "剩余空间(MB)", "Last Capacity");
	m_listDiskState.InsertColumn(2, szLan, LVCFMT_LEFT, 130, -1);
	g_StringLanType(szLan, "硬盘状态", "HD Status");
	m_listDiskState.InsertColumn(3, szLan, LVCFMT_LEFT,250,-1);

	m_listChanState.SetExtendedStyle(m_listChanState.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_listDiskState.SetExtendedStyle(m_listDiskState.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	CheckInitParam();
	return TRUE;
}

void CALLBACK g_fGetStateCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgDeviceState* pDlg = (CDlgDeviceState*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessGetStateCallbackData(dwType, lpBuffer, dwBufLen);
}

void CDlgDeviceState::ProcessGetStateCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_WORKSTATE_V40 lpStateCfg = new NET_DVR_WORKSTATE_V40;
        memset(lpStateCfg, 0, sizeof(NET_DVR_WORKSTATE_V40));
        memcpy(lpStateCfg, lpBuffer, sizeof(*lpStateCfg));
        PostMessage(WM_STATE_ADD_TOLIST, (WPARAM)lpStateCfg, 0);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_STATE_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GetDevice STATUS_FAILED, Error code %d", NET_DVR_GetLastError());
            PostMessage(WM_STATE_FINISH, 0, 0);
        }
    }
}

/*********************************************************
  Function:	OnBnClickedBtnRefresh
  Desc:		refresh device state info
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgDeviceState::OnBnClickedBtnRefresh()
{
    char szLan[1024] = { 0 };
	m_listChanState.DeleteAllItems();
	m_listDiskState.DeleteAllItems();
    m_dwChannelIndex = 0;
    m_dwHddIndex = 0;
    if (m_lGetStateHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lGetStateHandle);
        m_lGetStateHandle = -1;
    }

    NET_DVR_GETWORKSTATE_COND struWorkStateCond = { 0 };
    struWorkStateCond.dwSize = sizeof(NET_DVR_GETWORKSTATE_COND);
    struWorkStateCond.byFindChanByCond = 0;
    struWorkStateCond.byFindHardByCond = 0;

    //切换测试代码，测试V50接口
    if (1)
    {
        m_lGetStateHandle = NET_DVR_StartRemoteConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_WORK_STATUS_V50, &struWorkStateCond, sizeof(struWorkStateCond),
            g_fGetStateCallback, this);
        if (m_lGetStateHandle == -1)
        {
            g_StringLanType(szLan, "获取设备状态失败!", "Get Device Status Err!");
            AfxMessageBox(szLan);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WORK_STATUS_V50 failed");
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WORK_STATUS_V50 success");
        }
    }
    else
    {
        int i = 0;
        int iIndex = 0;
        int iTotalLen = 0;
        CString strDiskNum = _T("");
        CString strChanNum = _T("");
        CString strTemp = _T("");
        char szLan[1024] = { 0 };
        NET_DVR_WORKSTATE_V40 *pStruWorkStateV40 = new NET_DVR_WORKSTATE_V40;
        if (pStruWorkStateV40 == NULL)
        {
            g_StringLanType(szLan, "申请内存失败", "alloc memory error");
            AfxMessageBox(szLan);
            return;
        }
        memset(pStruWorkStateV40, 0, sizeof(NET_DVR_WORKSTATE_V40));
        DWORD dwList = 0;

        if (!NET_DVR_GetDeviceConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_WORK_STATUS, 1, \
            &struWorkStateCond, sizeof(NET_DVR_GETWORKSTATE_COND), &dwList, pStruWorkStateV40, sizeof(NET_DVR_WORKSTATE_V40)) || (dwList != 0))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WORK_STATUS");

            g_StringLanType(szLan, "获取设备状态失败!", "Get Device Status Err!");
            AfxMessageBox(szLan);
            return;
        }

        switch (pStruWorkStateV40->dwDeviceStatic)
        {
        case 0:
            g_StringLanType(szLan, "正常", "Normal");
            m_csDeviceState.Format(szLan);
            break;
        case 1:
            g_StringLanType(szLan, "CPU占用率太高,超过85%", "CPU occupancy rate is too high");
            m_csDeviceState.Format(szLan);
            break;
        case 2:
            g_StringLanType(szLan, "硬件错误", "Hardware error");
            m_csDeviceState.Format(szLan);
            break;
        default:
            break;
        }

        GetDlgItem(IDC_STATIC_DEVSTATE)->SetWindowText(m_csDeviceState);

        int iDeviceChannel = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
        if (g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum&&g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo > g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum)
        {
            for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum && i < 16; i++)
            {
                int iChannelIndex = g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChannelNO - 1;

                strChanNum.Format("%s", g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].chChanName);

                if (0 == pStruWorkStateV40->struChanStatic[iChannelIndex].byRecordStatic)
                {
                    g_StringLanType(szLan, "不录像", "Not Record");
                    m_csRecState.Format(szLan);
                }
                else if (1 == pStruWorkStateV40->struChanStatic[iChannelIndex].byRecordStatic)
                {
                    g_StringLanType(szLan, "录像", "Record");
                    m_csRecState.Format(szLan);
                }

                if (0 == pStruWorkStateV40->struChanStatic[iChannelIndex].bySignalStatic)
                {
                    g_StringLanType(szLan, "正常", "Normal");
                    m_csSignalState.Format(szLan);
                }
                else if (1 == pStruWorkStateV40->struChanStatic[iChannelIndex].bySignalStatic)
                {
                    g_StringLanType(szLan, "信号丢失", "Signal loss");
                    m_csSignalState.Format(szLan);
                }

                if (0 == pStruWorkStateV40->struChanStatic[iChannelIndex].byHardwareStatic)
                {
                    g_StringLanType(szLan, "正常", "Normal");
                    m_csHardWareState.Format(szLan);
                }
                else if (1 == pStruWorkStateV40->struChanStatic[iChannelIndex].byHardwareStatic)
                {
                    g_StringLanType(szLan, "异常", "Abnormal");
                    m_csHardWareState.Format(szLan);
                }

                m_csLinkCount.Format("%d", pStruWorkStateV40->struChanStatic[iChannelIndex].dwLinkNum);
                iTotalLen += pStruWorkStateV40->struChanStatic[iChannelIndex].dwLinkNum;
                m_csBitrate.Format("%ld", pStruWorkStateV40->struChanStatic[iChannelIndex].dwBitRate);

                m_listChanState.InsertItem(iIndex, strChanNum, 0);
                m_listChanState.SetItemText(iIndex, 1, m_csRecState);
                m_listChanState.SetItemText(iIndex, 2, m_csSignalState);
                m_listChanState.SetItemText(iIndex, 3, m_csHardWareState);
                m_listChanState.SetItemText(iIndex, 4, m_csLinkCount);
                m_listChanState.SetItemText(iIndex, 5, m_csBitrate);
                m_listChanState.SetItemText(iIndex, 6, pStruWorkStateV40->struChanStatic[iChannelIndex].struClientIP[0].sIpV4);
                strTemp.Format("%d", pStruWorkStateV40->struChanStatic[iChannelIndex].dwIPLinkNum);
                m_listChanState.SetItemText(iIndex, 7, strTemp);
                m_csAllBitRate.Format("%ld", pStruWorkStateV40->struChanStatic[iChannelIndex].dwAllBitRate);
                m_listChanState.SetItemText(iIndex, 8, m_csAllBitRate);
                iIndex++;
            }
        }
        //monitoring point state
        for (i = 0; i < iDeviceChannel; i++)  //
        {


            //由于pStruWorkStateV40->struChanStatic[i]是按64个通道排列，而g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i]是按48个紧凑排列
            //所以需要转换一下，i按紧凑排列
            int iChannelIndex = 0;
            DWORD dwChanNo = pStruWorkStateV40->struChanStatic[i].dwChannelNo;
            if (dwChanNo == 0xffffffff)
            {
                break;
            }

            iChannelIndex = -1;
            for (int j = 0; j < iDeviceChannel; j++)
            {
                if (dwChanNo == g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[j].iChannelNO)
                {
                    iChannelIndex = j;
                    break;
                }
            }

            if (iChannelIndex == -1)
            {
                //后面的通道是没有意义的，直接下个循环
                continue;
            }

            strChanNum.Format("%s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[iChannelIndex].chChanName);

            if (0 == pStruWorkStateV40->struChanStatic[i].byRecordStatic)
            {
                g_StringLanType(szLan, "不录像", "Not Record");
                m_csRecState.Format(szLan);
            }
            else if (1 == pStruWorkStateV40->struChanStatic[i].byRecordStatic)
            {
                g_StringLanType(szLan, "录像", "Record");
                m_csRecState.Format(szLan);
            }

            if (0 == pStruWorkStateV40->struChanStatic[i].bySignalStatic)
            {
                g_StringLanType(szLan, "正常", "Normal");
                m_csSignalState.Format(szLan);
            }
            else if (1 == pStruWorkStateV40->struChanStatic[i].bySignalStatic)
            {
                g_StringLanType(szLan, "信号丢失", "Signal loss");
                m_csSignalState.Format(szLan);
            }

            if (0 == pStruWorkStateV40->struChanStatic[i].byHardwareStatic)
            {
                g_StringLanType(szLan, "正常", "Normal");
                m_csHardWareState.Format(szLan);
            }
            else if (1 == pStruWorkStateV40->struChanStatic[i].byHardwareStatic)
            {
                g_StringLanType(szLan, "异常", "Abnormal");
                m_csHardWareState.Format(szLan);
            }

            m_csLinkCount.Format("%d", pStruWorkStateV40->struChanStatic[i].dwLinkNum);
            iTotalLen += pStruWorkStateV40->struChanStatic[i].dwLinkNum;
            m_csBitrate.Format("%ld", pStruWorkStateV40->struChanStatic[i].dwBitRate);

            m_csAllBitRate.Format("%ld", pStruWorkStateV40->struChanStatic[i].dwAllBitRate);
            m_listChanState.InsertItem(iIndex, strChanNum, 0);
            m_listChanState.SetItemText(iIndex, 1, m_csRecState);
            m_listChanState.SetItemText(iIndex, 2, m_csSignalState);
            m_listChanState.SetItemText(iIndex, 3, m_csHardWareState);
            m_listChanState.SetItemText(iIndex, 4, m_csLinkCount);
            m_listChanState.SetItemText(iIndex, 5, m_csBitrate);
            m_listChanState.SetItemText(iIndex, 6, pStruWorkStateV40->struChanStatic[i].struClientIP[0].sIpV4);
            strTemp.Format("%d", pStruWorkStateV40->struChanStatic[i].dwIPLinkNum);
            m_listChanState.SetItemText(iIndex, 7, strTemp);
            m_listChanState.SetItemText(iIndex, 8, m_csAllBitRate);
            iIndex++;
        }

        //disk state
        for (i = 0; i < MAX_DISKNUM_V30; i++)
        {
            g_StringLanType(szLan, "硬盘", "HD");
            strDiskNum.Format("%s%02d", szLan, i + 1);

            m_csDiskVolume.Format("%ld", pStruWorkStateV40->struHardDiskStatic[i].dwVolume);
            m_csDiskFreeSpace.Format("%ld", pStruWorkStateV40->struHardDiskStatic[i].dwFreeSpace);

            if (pStruWorkStateV40->struHardDiskStatic[i].dwVolume != 0)
            {
                switch (pStruWorkStateV40->struHardDiskStatic[i].dwHardDiskStatic)
                {
                case 0:
                    g_StringLanType(szLan, "活动", "Active");
                    m_csDiskState.Format(szLan);
                    break;
                case 1:
                    g_StringLanType(szLan, "休眠", "Dormancy");
                    m_csDiskState.Format(szLan);
                    break;
                case 2:
                    g_StringLanType(szLan, "不正常", "Abnormal");
                    m_csDiskState.Format(szLan);
                    m_csDiskState.Format("%s", "不正常");
                    break;
                case 3:
                    g_StringLanType(szLan, "休眠且不正常", "Dormancy and Abnormal");
                    m_csDiskState.Format(szLan);
                    break;
                case 4:
                    g_StringLanType(szLan, "未格式化", "Not Format");
                    m_csDiskState.Format(szLan);
                    break;
                case 5:
                    g_StringLanType(szLan, "未连接(网络硬盘)", "Not Connect(Net Disk)");
                    m_csDiskState.Format(szLan);
                    break;
                case 6:
                    g_StringLanType(szLan, "正在格式化", "Being Formating");
                    m_csDiskState.Format(szLan);
                    break;
                default:

                    break;
                }
            }
            else
            {
                m_csDiskState.Format("");
            }

            strTemp.Format("%d", i);
            m_listDiskState.InsertItem(i, strDiskNum, 0);
            m_listDiskState.SetItemText(i, 1, m_csDiskVolume);
            m_listDiskState.SetItemText(i, 2, m_csDiskFreeSpace);
            m_listDiskState.SetItemText(i, 3, m_csDiskState);
        }

        strTemp.Format("%d", iTotalLen);
        GetDlgItem(IDC_STATIC_TOTAL_LINK)->SetWindowText(strTemp);

        m_csHumidity.Format("%.1f", pStruWorkStateV40->fHumidity);
        m_csTemperature.Format("%.1f", pStruWorkStateV40->fTemperature);

        if (pStruWorkStateV40 != NULL)
        {
            delete pStruWorkStateV40;
            pStruWorkStateV40 = NULL;
        }
        UpdateData(false);
    }
    return;
}

/*********************************************************
  Function:	CheckInitParam
  Desc:		check current selected device, and initialize parameters in the dialog
  Input:	
  Output:	
  Return:	TRUE,checked and got state info;FALSE,failed;
**********************************************************/
BOOL CDlgDeviceState::CheckInitParam(void)
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	if (iDeviceIndex == -1)
	{
		m_lLoginID = -1;
		GetDlgItem(ID_BTN_REFRESH)->EnableWindow(FALSE);
		return FALSE;
	}

	if (m_iDeviceIndex == iDeviceIndex)
	{
		return TRUE;
	}
	else
	{
		m_iDeviceIndex = iDeviceIndex;
		m_listChanState.DeleteAllItems();
		m_listDiskState.DeleteAllItems();
	}

	m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

	if (m_lLoginID < 0)
	{
		GetDlgItem(ID_BTN_REFRESH)->EnableWindow(FALSE);
		return FALSE;
	}
	m_csLocalNodeName.Format("%s", g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName);//device title:
	m_csDeviceIP.Format("%s", g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);//device IP address:
	GetDlgItem(IDC_STATIC_DEVNAME)->SetWindowText(m_csLocalNodeName);
	OnBnClickedBtnRefresh();
	EnableWindow(TRUE);
	return TRUE;
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		exit the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgDeviceState::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgDeviceState::OnBtnLinkStatus() 
{
    CDlgLinkStatus dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}


afx_msg LRESULT CDlgDeviceState::OnStateAddTolist(WPARAM wParam, LPARAM lParam)
{
    int i = 0;
    int iIndex = m_dwChannelIndex;
    int iTotalLen = 0;
    CString strDiskNum = _T("");
    CString strChanNum = _T("");
    CString strTemp = _T("");
    char szLan[1024] = { 0 };

    NET_DVR_WORKSTATE_V40 *pStruWorkStateV40 = (NET_DVR_WORKSTATE_V40 *)wParam;
    if (pStruWorkStateV40 == NULL)
    {
        g_StringLanType(szLan, "申请内存失败", "alloc memory error");
        AfxMessageBox(szLan);
        return NULL;
    }

    switch (pStruWorkStateV40->dwDeviceStatic)
    {
    case 0:
        g_StringLanType(szLan, "正常", "Normal");
        m_csDeviceState.Format(szLan);
        break;
    case 1:
        g_StringLanType(szLan, "CPU占用率太高,超过85%", "CPU occupancy rate is too high");
        m_csDeviceState.Format(szLan);
        break;
    case 2:
        g_StringLanType(szLan, "硬件错误", "Hardware error");
        m_csDeviceState.Format(szLan);
        break;
    default:
        break;
    }

    GetDlgItem(IDC_STATIC_DEVSTATE)->SetWindowText(m_csDeviceState);

    int iDeviceChannel = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
    if (g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum&&g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo > g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum)
    {
        for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum && i < 16; i++)
        {
            int iChannelIndex = g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChannelNO - 1;

            strChanNum.Format("%s", g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].chChanName);

            if (0 == pStruWorkStateV40->struChanStatic[iChannelIndex].byRecordStatic)
            {
                g_StringLanType(szLan, "不录像", "Not Record");
                m_csRecState.Format(szLan);
            }
            else if (1 == pStruWorkStateV40->struChanStatic[iChannelIndex].byRecordStatic)
            {
                g_StringLanType(szLan, "录像", "Record");
                m_csRecState.Format(szLan);
            }

            if (0 == pStruWorkStateV40->struChanStatic[iChannelIndex].bySignalStatic)
            {
                g_StringLanType(szLan, "正常", "Normal");
                m_csSignalState.Format(szLan);
            }
            else if (1 == pStruWorkStateV40->struChanStatic[iChannelIndex].bySignalStatic)
            {
                g_StringLanType(szLan, "信号丢失", "Signal loss");
                m_csSignalState.Format(szLan);
            }

            if (0 == pStruWorkStateV40->struChanStatic[iChannelIndex].byHardwareStatic)
            {
                g_StringLanType(szLan, "正常", "Normal");
                m_csHardWareState.Format(szLan);
            }
            else if (1 == pStruWorkStateV40->struChanStatic[iChannelIndex].byHardwareStatic)
            {
                g_StringLanType(szLan, "异常", "Abnormal");
                m_csHardWareState.Format(szLan);
            }

            m_csLinkCount.Format("%d", pStruWorkStateV40->struChanStatic[iChannelIndex].dwLinkNum);
            iTotalLen += pStruWorkStateV40->struChanStatic[iChannelIndex].dwLinkNum;
            m_csBitrate.Format("%ld", pStruWorkStateV40->struChanStatic[iChannelIndex].dwBitRate);

            m_listChanState.InsertItem(iIndex, strChanNum, 0);
            m_listChanState.SetItemText(iIndex, 1, m_csRecState);
            m_listChanState.SetItemText(iIndex, 2, m_csSignalState);
            m_listChanState.SetItemText(iIndex, 3, m_csHardWareState);
            m_listChanState.SetItemText(iIndex, 4, m_csLinkCount);
            m_listChanState.SetItemText(iIndex, 5, m_csBitrate);
            m_listChanState.SetItemText(iIndex, 6, pStruWorkStateV40->struChanStatic[iChannelIndex].struClientIP[0].sIpV4);
            strTemp.Format("%d", pStruWorkStateV40->struChanStatic[iChannelIndex].dwIPLinkNum);
            m_listChanState.SetItemText(iIndex, 7, strTemp);
            m_csAllBitRate.Format("%ld", pStruWorkStateV40->struChanStatic[iChannelIndex].dwAllBitRate);
            m_listChanState.SetItemText(iIndex, 8, m_csAllBitRate);
            iIndex++;
        }
    }
    //monitoring point state
    for (i = 0; i < MAX_CHANNUM_V40; i++)  //
    {
        //由于pStruWorkStateV40->struChanStatic[i]是按64个通道排列，而g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i]是按48个紧凑排列
        //所以需要转换一下，i按紧凑排列
        int iChannelIndex = 0;
        DWORD dwChanNo = pStruWorkStateV40->struChanStatic[i].dwChannelNo;
        if (dwChanNo == 0xffffffff)
        {
            break;
        }

        iChannelIndex = -1;
        for (int j = 0; j < iDeviceChannel; j++)
        {
            if (dwChanNo == g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[j].iChannelNO)
            {
                iChannelIndex = j;
                break;
            }
        }

        if (iChannelIndex == -1)
        {
            strChanNum.Format("%s%d", "IPCarmera", dwChanNo);
        }
        else
        {
            strChanNum.Format("%s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[iChannelIndex].chChanName);
        }

        if (0 == pStruWorkStateV40->struChanStatic[i].byRecordStatic)
        {
            g_StringLanType(szLan, "不录像", "Not Record");
            m_csRecState.Format(szLan);
        }
        else if (1 == pStruWorkStateV40->struChanStatic[i].byRecordStatic)
        {
            g_StringLanType(szLan, "录像", "Record");
            m_csRecState.Format(szLan);
        }

        if (0 == pStruWorkStateV40->struChanStatic[i].bySignalStatic)
        {
            g_StringLanType(szLan, "正常", "Normal");
            m_csSignalState.Format(szLan);
        }
        else if (1 == pStruWorkStateV40->struChanStatic[i].bySignalStatic)
        {
            g_StringLanType(szLan, "信号丢失", "Signal loss");
            m_csSignalState.Format(szLan);
        }

        if (0 == pStruWorkStateV40->struChanStatic[i].byHardwareStatic)
        {
            g_StringLanType(szLan, "正常", "Normal");
            m_csHardWareState.Format(szLan);
        }
        else if (1 == pStruWorkStateV40->struChanStatic[i].byHardwareStatic)
        {
            g_StringLanType(szLan, "异常", "Abnormal");
            m_csHardWareState.Format(szLan);
        }

        m_csLinkCount.Format("%d", pStruWorkStateV40->struChanStatic[i].dwLinkNum);
        iTotalLen += pStruWorkStateV40->struChanStatic[i].dwLinkNum;
        m_csBitrate.Format("%ld", pStruWorkStateV40->struChanStatic[i].dwBitRate);

        m_csAllBitRate.Format("%ld", pStruWorkStateV40->struChanStatic[i].dwAllBitRate);
        m_listChanState.InsertItem(iIndex, strChanNum, 0);
        m_listChanState.SetItemText(iIndex, 1, m_csRecState);
        m_listChanState.SetItemText(iIndex, 2, m_csSignalState);
        m_listChanState.SetItemText(iIndex, 3, m_csHardWareState);
        m_listChanState.SetItemText(iIndex, 4, m_csLinkCount);
        m_listChanState.SetItemText(iIndex, 5, m_csBitrate);
        m_listChanState.SetItemText(iIndex, 6, pStruWorkStateV40->struChanStatic[i].struClientIP[0].sIpV4);
        strTemp.Format("%d", pStruWorkStateV40->struChanStatic[i].dwIPLinkNum);
        m_listChanState.SetItemText(iIndex, 7, strTemp);
        m_listChanState.SetItemText(iIndex, 8, m_csAllBitRate);
        iIndex++;
    }

    //disk state
    for (i = 0; i < MAX_DISKNUM_V30; i++)
    {
        g_StringLanType(szLan, "硬盘", "HD");
        strDiskNum.Format("%s%02d", szLan, m_dwHddIndex + i + 1);

        m_csDiskVolume.Format("%ld", pStruWorkStateV40->struHardDiskStatic[i].dwVolume);
        m_csDiskFreeSpace.Format("%ld", pStruWorkStateV40->struHardDiskStatic[i].dwFreeSpace);

        if (pStruWorkStateV40->struHardDiskStatic[i].dwVolume != 0)
        {
            switch (pStruWorkStateV40->struHardDiskStatic[i].dwHardDiskStatic)
            {
            case 0:
                g_StringLanType(szLan, "活动", "Active");
                m_csDiskState.Format(szLan);
                break;
            case 1:
                g_StringLanType(szLan, "休眠", "Dormancy");
                m_csDiskState.Format(szLan);
                break;
            case 2:
                g_StringLanType(szLan, "不正常", "Abnormal");
                m_csDiskState.Format(szLan);
                m_csDiskState.Format("%s", "不正常");
                break;
            case 3:
                g_StringLanType(szLan, "休眠且不正常", "Dormancy and Abnormal");
                m_csDiskState.Format(szLan);
                break;
            case 4:
                g_StringLanType(szLan, "未格式化", "Not Format");
                m_csDiskState.Format(szLan);
                break;
            case 5:
                g_StringLanType(szLan, "未连接(网络硬盘)", "Not Connect(Net Disk)");
                m_csDiskState.Format(szLan);
                break;
            case 6:
                g_StringLanType(szLan, "正在格式化", "Being Formating");
                m_csDiskState.Format(szLan);
                break;
            default:
                break;
            }
        }
        else
        {
            m_csDiskState.Format("");
        }

        m_listDiskState.InsertItem(m_dwHddIndex + i, strDiskNum, 0);
        m_listDiskState.SetItemText(m_dwHddIndex + i, 1, m_csDiskVolume);
        m_listDiskState.SetItemText(m_dwHddIndex + i, 2, m_csDiskFreeSpace);
        m_listDiskState.SetItemText(m_dwHddIndex + i, 3, m_csDiskState);
    }

    strTemp.Format("%d", iTotalLen);
    GetDlgItem(IDC_STATIC_TOTAL_LINK)->SetWindowText(strTemp);

    m_csHumidity.Format("%.1f", pStruWorkStateV40->fHumidity);
    m_csTemperature.Format("%.1f", pStruWorkStateV40->fTemperature);

    if (pStruWorkStateV40 != NULL)
    {
        delete pStruWorkStateV40;
        pStruWorkStateV40 = NULL;
    }
    UpdateData(false);

    m_dwChannelIndex = iIndex;
    m_dwHddIndex += MAX_DISKNUM_V30;

    return NULL;
}


afx_msg LRESULT CDlgDeviceState::OnStateFinish(WPARAM wParam, LPARAM lParam)
{
    if (m_lGetStateHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lGetStateHandle);
        m_lGetStateHandle = -1;
    }
    return NULL;
}
