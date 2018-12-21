/**********************************************************
FileName:    DlgFormatHD.cpp
Description: hard disk format    
Date:        2008/05/17
Note: 		 <global>struct, define refer to GeneralDef.h, global variables and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgFormatHD.h"
#include ".\dlgformathd.h"


/*********************************************************
  Function:	CDlgFormatHD
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgFormatHD, CDialog)
CDlgFormatHD::CDlgFormatHD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFormatHD::IDD, pParent)
	, m_csFormatStat(_T(""))
	, m_iDeviceIndex(-1)
	, m_lFormatAll(-1)
	, m_nTime(0)
	, m_bFormatAll(FALSE)
	, m_dwDiskNum(0)
	, m_lDiskSel(0)
	, m_iDiskIndex(0)
    , m_dwHddNo(0)
    , m_csIp(_T(""))
    , m_bAll(FALSE)
    , m_bIpv6(FALSE)
  {
	for (int i = 0; i<MAX_DISKNUM_V30; i++)
	{
		m_lFormat[i] = -1; 
		m_bFormat[i] = FALSE;
	}
}

/*********************************************************
  Function:	~CDlgFormatHD
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgFormatHD::~CDlgFormatHD()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgFormatHD::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgFormatHD)
    DDX_Control(pDX, IDC_COMBO_HD_DRIVER, m_comboHDDriver);
    DDX_Text(pDX, IDC_STATIC_FORMAT, m_csFormatStat);
    DDX_Control(pDX, IDC_PROGRESS_FORMAT, m_progressFormat);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_HDD_NO, m_dwHddNo);
    DDX_Text(pDX, IDC_EDIT_HDD_IP, m_csIp);
    DDX_Check(pDX, IDC_CHECK1, m_bAll);
    DDX_Check(pDX, IDC_CHECK2, m_bIpv6);
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgFormatHD, CDialog)
	//{{AFX_MSG_MAP(CDlgFormatHD)
	ON_BN_CLICKED(IDC_BTN_DO_FORMAT, OnBnClickedBtnDoFormat)
	ON_BN_CLICKED(IDC_BTN_FORMAT_EXIT, OnBnClickedBtnFormatExit)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP

    ON_BN_CLICKED(IDC_BUTTON_FROAMT_V50, &CDlgFormatHD::OnBnClickedButtonFroamtV50)
END_MESSAGE_MAP()


// CDlgFormatHD message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgFormatHD::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	NET_DVR_HDCFG struHDCfg;
	CString csTemp;
	int i = 0;
	DWORD dwReturned = 0;
	char szLan[1024] = {0};
	
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_HDCFG, 0, &struHDCfg, sizeof(NET_DVR_HDCFG), &dwReturned))
	{
		g_StringLanType(szLan, "全部硬盘", "All Hard Disk");
		m_comboHDDriver.AddString(szLan);
		for (i=0; i<(int)m_dwDiskNum; i++)
		{
			g_StringLanType(szLan, "硬盘", "HD");
			csTemp.Format("%s%d", szLan, i);
			m_comboHDDriver.AddString(csTemp);
			m_comboHDDriver.SetItemData(i+1, i);
			m_bFormat[i] = FALSE;
			m_lFormat[i] = -1;
		}		
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_HDCFG"); 
		g_StringLanType(szLan, "全部硬盘", "All Hard Disk");
		m_comboHDDriver.AddString(szLan);
		m_comboHDDriver.SetItemData(0, 0xff);
		for (i=0; i<(int)struHDCfg.dwHDCount; i++)
		{
			g_StringLanType(szLan, "硬盘", "HD");
			csTemp.Format("%s%d", szLan, struHDCfg.struHDInfo[i].dwHDNo);
			m_comboHDDriver.AddString(csTemp);
			m_comboHDDriver.SetItemData(i+1, struHDCfg.struHDInfo[i].dwHDNo);
			m_bFormat[i] = FALSE;
			m_lFormat[i] = -1;
		}
	}
	m_lDiskSel = 0;

	m_comboHDDriver.SetCurSel(m_lDiskSel);
	GetDlgItem(IDC_STATIC_FORMAT)->ShowWindow(SW_SHOW);
	m_progressFormat.SetRange(0,100);
	m_progressFormat.SetPos(0);
	m_nTime = SetTimer(FORMAT_TIMER, 5000, NULL);
	UpdateData(FALSE);
	return TRUE; 
}

/*********************************************************
Function:	OnBnClickedBtnDoFormat
Desc:		execute format
Input:	
Output:	
Return:	
**********************************************************/
void CDlgFormatHD::OnBnClickedBtnDoFormat()
{
	LONG lDiskSel;
	char szLan[1024] = {0};
	lDiskSel = m_comboHDDriver.GetCurSel();
	if (lDiskSel == 0)
	{
		m_lFormatAll = NET_DVR_FormatDisk(g_struDeviceInfo[m_iDeviceIndex].lLoginID, 0xFF);//0xFF means hard disk
		if (m_lFormatAll < 0)
		{
			g_pMainDlg->AddLog(OPERATION_FAIL_T, m_iDeviceIndex, "NET_DVR_FormatDisk All");
			int Err = GetLastError();
			if (Err == NET_DVR_DISK_FORMATING)
			{
				g_StringLanType(szLan, "硬盘正在格式化,不能启动操作", "Hard disk is formatted, can not start operation");
				AfxMessageBox(szLan);
			}
			else
			{
				g_StringLanType(szLan, "格式化失败", "Format fail");
				AfxMessageBox(szLan);
			}
		}
		else
		{
			g_StringLanType(szLan, "状态：正在格式化硬盘，请等待......", "Status:Is to reformat your hard disk, please wait");		
			m_csFormatStat.Format(szLan);
			m_bFormatAll = TRUE;
			GetDlgItem(IDC_BTN_DO_FORMAT)->EnableWindow(FALSE);
		}	
	}
	else
	{
		m_iDiskIndex = m_comboHDDriver.GetItemData(lDiskSel);
		m_lFormat[m_iDiskIndex] = NET_DVR_FormatDisk(g_struDeviceInfo[m_iDeviceIndex].lLoginID, m_iDiskIndex);
		if (m_lFormat[m_iDiskIndex] < 0)
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_FormatDisk %d", m_iDiskIndex);
			g_StringLanType(szLan, "格式化失败", "Format fail");
			AfxMessageBox(szLan);
		}
		else
		{
			g_StringLanType(szLan, "状态：正在格式化硬盘，请等待......", "Status:Is to reformat your hard disk, please wait");		
			m_csFormatStat.Format(szLan);
			m_bFormat[m_iDiskIndex] = TRUE;			
		}
	}
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnFormatExit
  Desc:		exit hard disk initial box
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgFormatHD::OnBnClickedBtnFormatExit()
{
	if (m_bFormatAll)
	{
		m_bFormatAll = FALSE;
		NET_DVR_CloseFormatHandle(m_lFormatAll);
	}
	else
	{
		for (int i=0; i<MAX_DISKNUM_V30; i++)
		{
			if (m_bFormat[i])
			{
				m_bFormat[i] = FALSE;
				NET_DVR_CloseFormatHandle(m_lFormat[i]);
			}
		}
	}
	if (m_nTime)
	{
		KillTimer(FORMAT_TIMER);
	}

	CDialog::OnCancel();
}

/*********************************************************
  Function:	OnTimer
  Desc:		timer message response function
  Input:	nIDEvent,timer value
  Output:	
  Return:	
**********************************************************/
#if (_MSC_VER >= 1500)	//vs2008
void CDlgFormatHD::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgFormatHD::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	LONG lCurDisk;
	LONG lCurDiskPos;
	LONG lFormatStatic;
	CString sTemp;
	char szLan[1024] = {0};

	if (nIDEvent == FORMAT_TIMER)
	{
		if (m_bFormatAll)
		{
			if (NET_DVR_GetFormatProgress(m_lFormatAll, &lCurDisk, &lCurDiskPos, &lFormatStatic))
			{
				switch (lFormatStatic) 
				{
				case 0:	
					g_StringLanType(szLan, "状态：正在格式化硬盘", "Status: formatting hard disk");		
					m_csFormatStat.Format("%s%d", szLan, lCurDisk);
					break;
				case 1:
					g_StringLanType(szLan, "状态：硬盘格式化成功", "Status: format hard disk successfully");	
					m_csFormatStat.Format(szLan);					
					GetDlgItem(IDC_BTN_DO_FORMAT)->EnableWindow(TRUE);
					m_bFormatAll = FALSE;
					lCurDiskPos = 100;
					NET_DVR_CloseFormatHandle(m_lFormatAll);
                    m_lFormatAll = -1;
					break;			
				case 2:	
					g_StringLanType(szLan, "状态：格式化异常,状态未知, 硬盘", "Status: Unusual format, status unknown, HD");	
					m_csFormatStat.Format("%s%d", szLan, lCurDisk);				
					GetDlgItem(IDC_BTN_DO_FORMAT)->EnableWindow(TRUE);
					m_bFormatAll = FALSE;
					NET_DVR_CloseFormatHandle(m_lFormatAll);
                    m_lFormatAll = -1;
					break;
				default:
                    NET_DVR_CloseFormatHandle(m_lFormatAll);
                    m_lFormatAll = -1;
					break;
				}
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetFormatProgress [%d][%d]", lCurDisk, lCurDiskPos);
				m_progressFormat.SetPos(lCurDiskPos);
                UpdateData(FALSE);
			}
		}
		for (int i=0; i<MAX_DISKNUM_V30; i++)
		{
			if (m_bFormat[i])
			{
				if (NET_DVR_GetFormatProgress(m_lFormat[i], &lCurDisk, &lCurDiskPos, &lFormatStatic))
				{
					switch (lFormatStatic) 
					{
					case 0:	
						g_StringLanType(szLan, "状态：正在格式化硬盘", "Status: formatting hard disk");		
						m_csFormatStat.Format("%s%d", szLan, lCurDisk);
						break;
					case 1:
						g_StringLanType(szLan, "状态：硬盘格式化成功", "Status: format hard disk successfully");	
						m_csFormatStat.Format(szLan);
						m_bFormat[i] = FALSE;
						lCurDiskPos = 100;
						NET_DVR_CloseFormatHandle(m_lFormat[i]);
						break;			
					case 2:	
						g_StringLanType(szLan, "状态：格式化异常,状态未知, 硬盘", "Status: Unusual format, status unknown, HD");	
						m_csFormatStat.Format("%s%d", szLan, lCurDisk);	
						m_bFormat[i] = FALSE;
						NET_DVR_CloseFormatHandle(m_lFormat[i]);
						break;
					default:
						break;
					}
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetFormatProgress  disk%d [%d]", i, lCurDiskPos);
					m_progressFormat.SetPos(lCurDiskPos);
				}
                UpdateData(FALSE);
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgFormatHD::OnBnClickedButtonFroamtV50()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[1024] = { 0 };
    UpdateData(TRUE);

    if (m_bAll)
    {
        g_StringLanType(szLan, "确定要格式化全部硬盘?", "Sure to format all disk?");
        if (IDOK != MessageBox(szLan, "Warning", IDOK))
        {
            return;
        }

        NET_DVR_FORMAT_HDD struHddForamtCond = { 0 };
        struHddForamtCond.dwSize = sizeof(NET_DVR_FORMAT_HDD);
        struHddForamtCond.dwDiskNo = 0xFF;
        if (m_bIpv6)
        {
            strncpy((char *)struHddForamtCond.struLocateIP.byIPv6, m_csIp, 128);
        }
        else
        {
            strncpy(struHddForamtCond.struLocateIP.sIpV4, m_csIp, 16);
        }

        m_lFormatAll = NET_DVR_FormatDisk_V50(g_struDeviceInfo[m_iDeviceIndex].lLoginID, &struHddForamtCond);//0xFF means all hard disk
        if (m_lFormatAll < 0)
        {
            g_pMainDlg->AddLog(OPERATION_FAIL_T, m_iDeviceIndex, "NET_DVR_FormatDisk All");
            int Err = GetLastError();
            if (Err == NET_DVR_DISK_FORMATING)
            {
                g_StringLanType(szLan, "硬盘正在格式化,不能启动操作", "Hard disk is formatted, can not start operation");
                AfxMessageBox(szLan);
            }
            else
            {
                g_StringLanType(szLan, "格式化失败", "Format fail");
                AfxMessageBox(szLan);
            }
        }
        else
        {
            g_StringLanType(szLan, "状态：正在格式化硬盘，请等待......", "Status:Is to reformat your hard disk, please wait");
            m_csFormatStat.Format(szLan);
            m_bFormatAll = TRUE;
            GetDlgItem(IDC_BTN_DO_FORMAT)->EnableWindow(FALSE);
        }
    }
    else
    {
        NET_DVR_FORMAT_HDD struHddForamtCond = { 0 };
        struHddForamtCond.dwSize = sizeof(NET_DVR_FORMAT_HDD);
        struHddForamtCond.dwDiskNo = m_dwHddNo;
        if (m_bIpv6)
        {
            strncpy((char *)struHddForamtCond.struLocateIP.byIPv6, m_csIp, 128);
        }
        else
        {
            strncpy(struHddForamtCond.struLocateIP.sIpV4, m_csIp, 16);
        }

        int iIndex = -1;
        for (int i = 0; i < MAX_DISKNUM_V30; i++)
        {
            if (!m_bFormat[i])
            {
                iIndex = i;
                break;
            }
        }

        if (iIndex == -1)
        {
            g_StringLanType(szLan, "格式化队列已满，稍后再试", "queue full, try again later");
            AfxMessageBox(szLan);
            return;
        }

        m_lFormat[iIndex] = NET_DVR_FormatDisk_V50(g_struDeviceInfo[m_iDeviceIndex].lLoginID, &struHddForamtCond);
        if (m_lFormat[iIndex] < 0)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_FormatDisk %d", m_iDiskIndex);
            g_StringLanType(szLan, "格式化失败", "Format fail");
            AfxMessageBox(szLan);
        }
        else
        {
            g_StringLanType(szLan, "状态：正在格式化硬盘，请等待......", "Status:Is to reformat your hard disk, please wait");
            m_csFormatStat.Format(szLan);
            m_bFormat[iIndex] = TRUE;
        }
    }

    UpdateData(FALSE);
}

