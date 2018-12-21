// DlgITSIOinCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITSIOinCfg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITSIOinCfg dialog


CDlgITSIOinCfg::CDlgITSIOinCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITSIOinCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITSIOinCfg)
	m_byRelativeIndex = 0;
	m_csDevName = _T("");
	m_byGateWayDevCode = 0;
	m_byGateWayRS485No = 0;
	m_csLEDCustInfo = _T("");
	m_byLEDDevCode = 0;
	m_dwLEDDevPort = 0;
	m_byLEDRs485No = 0;
	m_dwReaderDevPort = 0;
	m_byDetCycle = 0;
	m_byDevCtrlCode = 0;
	m_byDevCode = 0;
	m_byManualIssuedData = 0;
	m_byEnissuedCode = 0;
	m_dwLEDScreenH = 0;
	m_dwLEDScreenW = 0;
	m_byEntrDetCycle = 0;
	m_bManualIssuedData = FALSE;
	//}}AFX_DATA_INIT
	m_lUserID = -1;
    m_iDevIndex = -1;
    m_dwChannel = -1;
	m_hGetInfoThread = NULL;
	m_bGetNext = FALSE;
	m_iStruCount = 0;
	m_pStruExternalDevCFG = NULL;
	//memset(&m_struExternalDevCFG, 0, sizeof(NET_DVR_EXTERNAL_DEVCFG));
	m_pStruExternalDevCond = NULL;
	m_lHandle = -1;
	m_pStruDevStatus = NULL;
}

CDlgITSIOinCfg::~CDlgITSIOinCfg()
{
	if (m_pStruExternalDevCFG != NULL)
	{
		delete [] m_pStruExternalDevCFG;
	}

	if (m_pStruExternalDevCond != NULL)
	{
		delete [] m_pStruExternalDevCond;
	}

	if (m_pStruDevStatus != NULL)
	{
		delete [] m_pStruDevStatus;
	}
}

void CDlgITSIOinCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITSIOinCfg)
	DDX_Control(pDX, IDC_COMBO_OFF_DET, m_comOfflineDet);
	DDX_Control(pDX, IDC_COMBO_OFFLINE, m_comOffLine);
	DDX_Control(pDX, IDC_IPADDRESS_READER_DEVIP, m_ReaderDevIP);
	DDX_Control(pDX, IDC_IPADDRESS_LED_DEVIP, m_LEDDevIP);
	DDX_Control(pDX, IDC_COMBO_LED_SCREEN_USE, m_comScreenUse);
	DDX_Control(pDX, IDC_COMBO_LED_SCREEN_TYPE, m_comLedScreenType);
	DDX_Control(pDX, IDC_COMBO_LED_EXTERNAL_MODE, m_comLedExteMode);
	DDX_Control(pDX, IDC_COMBO_LED_DIS_MODE, m_comLedDisMode);
	DDX_Control(pDX, IDC_COMBO_LED_CARD_TYPE, m_comLedCardType);
	DDX_Control(pDX, IDC_COMBO_GATEWAY_DATA, m_comGateWayIsData);
	DDX_Control(pDX, IDC_COMBO_DEV_TYPE3, m_comDevType3);
	DDX_Control(pDX, IDC_COMBO_RELATIVE_INDEX2, m_comRelativeIndex2);
	DDX_Control(pDX, IDC_COMBO_LANE_ID2, m_comLaneID2);
	DDX_Control(pDX, IDC_COMBO_DEV_TYPE2, m_comDevType2);
	DDX_Control(pDX, IDC_COMBO_RELATIVE_INDEX, m_comRelativeIndex);
	DDX_Control(pDX, IDC_LIST_ITS_EXDEVSTATUS, m_lstExDevStatus);
	DDX_Control(pDX, IDC_COMBO_LANE_ID, m_comLaneID);
	DDX_Control(pDX, IDC_COMBO_DEV_TYPE, m_comDevType);
	DDX_Text(pDX, IDC_EDIT_RELATIVE_INDEX, m_byRelativeIndex);
	DDX_Text(pDX, IDC_EDIT_DEV_NAME, m_csDevName);
	DDX_Text(pDX, IDC_EDIT_GATEWAY_DEVCODE, m_byGateWayDevCode);
	DDX_Text(pDX, IDC_EDIT_GATEWAY_RS485NO, m_byGateWayRS485No);
	DDX_Text(pDX, IDC_EDIT_LED_CUST_INFO, m_csLEDCustInfo);
	DDX_Text(pDX, IDC_EDIT_LED_DEVCODE, m_byLEDDevCode);
	DDX_Text(pDX, IDC_EDIT_LED_DEVPORT, m_dwLEDDevPort);
	DDX_Text(pDX, IDC_EDIT_LED_RS485NO, m_byLEDRs485No);
	DDX_Text(pDX, IDC_EDIT_READER_DEVPORT, m_dwReaderDevPort);
	DDX_Text(pDX, IDC_EDIT_DET_CYCLE, m_byDetCycle);
	DDX_Text(pDX, IDC_EDIT_CTRL_CODE, m_byDevCtrlCode);
	DDX_Text(pDX, IDC_EDIT_DEV_CODE, m_byDevCode);
	DDX_Text(pDX, IDC_EDIT_MANU_DATA, m_byManualIssuedData);
	DDX_Text(pDX, IDC_CHECK_MANU_DATA, m_bManualIssuedData);
	DDX_Text(pDX, IDC_EDIT_ENISSUED_CODE, m_byEnissuedCode);
	DDX_Text(pDX, IDC_EDIT_LED_SCREEN_H, m_dwLEDScreenH);
	DDX_Text(pDX, IDC_EDIT_LED_SCREEN_W, m_dwLEDScreenW);
	DDX_Text(pDX, IDC_EDIT_ENTR_DET_CYCLE, m_byEntrDetCycle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITSIOinCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgITSIOinCfg)
	ON_BN_CLICKED(IDC_BTN_GET_ITS_EXDEVSTATUS, OnBtnGetItsExdevstatus)
	ON_CBN_SELCHANGE(IDC_COMBO_DEV_TYPE, OnSelchangeComboDevType)
	ON_BN_CLICKED(IDC_BTN_SET_ITS_EXDEVCFG, OnBtnSetItsExdevcfg)
	ON_BN_CLICKED(IDC_BTN_GET_ITS_EXDEVCFG, OnBtnGetItsExdevcfg)
	ON_CBN_SELCHANGE(IDC_COMBO_DEV_TYPE2, OnSelchangeComboDevType2)
	ON_CBN_SELCHANGE(IDC_COMBO_DEV_TYPE3, OnSelchangeComboDevType3)
	ON_CBN_SELCHANGE(IDC_COMBO_LED_EXTERNAL_MODE, OnSelchangeComboLedExternalMode)
	ON_BN_CLICKED(IDC_BTN_SET_ENTRNCEDET, OnBtnSetEntrncedet)
	ON_BN_CLICKED(IDC_BTN_GET_ENTRNCEDET, OnBtnGetEntrncedet)
	ON_BN_CLICKED(IDC_BTN_CONTROL_ENTRANCEDEV, OnBtnControlEntrancedev)
	ON_BN_CLICKED(IDC_BTN_CONTROL_ENISSUED_DATADEL, OnBtnControlEnissuedDatadel)
	ON_BN_CLICKED(IDC_BTN_SAVE_ITS_EXDEVCFG, OnBtnSaveItsExdevcfg)
	ON_CBN_SELCHANGE(IDC_COMBO_RELATIVE_INDEX2, OnSelchangeComboRelativeIndex2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITSIOinCfg message handlers

BOOL CDlgITSIOinCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString strTemp;

	m_comDevType.SetCurSel(0);

	int i = 0;
	for (i = 0; i<8; i++)
	{
		strTemp.Format(_T("车道%d"), i+1);
		m_comLaneID.InsertString(i, strTemp);
	}
	m_comLaneID.SetCurSel(0);

	//m_comRelativeIndex.InsertString(0, _T("其它"));
	for (i = 0; i<8; i++)
	{
		strTemp.Format(_T("索引%d"), i+1);
		m_comRelativeIndex.InsertString(i, strTemp);
	}
	m_comRelativeIndex.InsertString(i, _T("全部信息"));
	m_comRelativeIndex.SetCurSel(0);

	m_comDevType2.SetCurSel(0);
	
	for (i = 0; i<8; i++)
	{
		strTemp.Format(_T("车道%d"), i+1);
		m_comLaneID2.InsertString(i, strTemp);
	}
	m_comLaneID2.SetCurSel(0);
	
	//m_comRelativeIndex2.InsertString(0, _T("其它"));
	for ( i = 0; i<8; i++)
	{
		strTemp.Format(_T("索引%d"), i+1);
		m_comRelativeIndex2.InsertString(i, strTemp);
	}
	m_comRelativeIndex2.SetCurSel(0);

	m_comDevType3.SetCurSel(0);
	OnSelchangeComboDevType3();

	m_comLedExteMode.SetCurSel(0);//默认为RS485
	OnSelchangeComboLedExternalMode(); 

	m_comOfflineDet.SetCurSel(0);

	char szLanTemp[128] = {0};
	m_lstExDevStatus.SetExtendedStyle(m_lstExDevStatus.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	g_StringLanType(szLanTemp, "设备名称", "Device Name");
    m_lstExDevStatus.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 175, -1);
	g_StringLanType(szLanTemp, "设备类型", "Device Type");
    m_lstExDevStatus.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 175, -1);
	g_StringLanType(szLanTemp, "相对索引", "Relative Index");
	m_lstExDevStatus.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 175, -1);
	g_StringLanType(szLanTemp, "是否在线", "Online");
    m_lstExDevStatus.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 90, -1);

	memset(&m_struExternalDevCond, 0, sizeof(NET_DVR_EXTERNAL_DEVCOND));
	memset(&m_struDevStatus, 0, sizeof(NET_DVR_EXTERNAL_DEVSTATUS));

	
	if (m_pStruExternalDevCFG != NULL)
	{
		delete [] m_pStruExternalDevCFG;
	}
	m_pStruExternalDevCFG = new NET_DVR_EXTERNAL_DEVCFG[8];
	memset(m_pStruExternalDevCFG, 0, 8*sizeof(NET_DVR_EXTERNAL_DEVCFG));

	if (m_pStruExternalDevCond != NULL)
	{
		delete [] m_pStruExternalDevCond;
	}
	m_pStruExternalDevCond = new NET_DVR_EXTERNAL_DEVCOND[8];
	memset(m_pStruExternalDevCond, 0, 8*sizeof(NET_DVR_EXTERNAL_DEVCOND));

	if (m_pStruDevStatus != NULL)
	{
		delete [] m_pStruDevStatus;
	}
	m_pStruDevStatus = new NET_DVR_EXTERNAL_DEVSTATUS[MAX_ALARMHOST_ALARMOUT_NUM];
	memset(m_pStruDevStatus, 0, MAX_ALARMHOST_ALARMOUT_NUM*sizeof(NET_DVR_EXTERNAL_DEVSTATUS));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

DWORD WINAPI CDlgITSIOinCfg::GetVehInfoThread(LPVOID lpVehInfo)
{
	//UpdateData(TRUE);
	CDlgITSIOinCfg* pThis = reinterpret_cast<CDlgITSIOinCfg*>(lpVehInfo);
	int iRet = 0;
	char szLan[128] = {0};
	char szInfoBuf[128] = {0};
	while (pThis->m_bGetNext)
	{
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_pStruDevStatus[pThis->m_iStruCount], sizeof(NET_DVR_EXTERNAL_DEVSTATUS)); 
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			int iItemCount = pThis->m_lstExDevStatus.GetItemCount();
			pThis->AddDevStatusToDlg(iItemCount, &pThis->m_pStruDevStatus[pThis->m_iStruCount]);
			pThis->m_iStruCount++;
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
				g_StringLanType(szLan, "终端出入口外接设备信息获取结束!", "Get External Device Info Finish");
				sprintf(szInfoBuf, "%s[Info Count:%d]", szLan, pThis->m_lstExDevStatus.GetItemCount());
				AfxMessageBox(szInfoBuf);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "终端出入口外接设备信息获取失败", "Get External Device Info Failed");
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
	//UpdateData(FALSE);
	return 0 ;
}

void CDlgITSIOinCfg::AddDevStatusToDlg(int iItemCount, LPNET_DVR_EXTERNAL_DEVSTATUS lpInter)
{
	if (iItemCount >= m_lstExDevStatus.GetItemCount())
	{
		m_lstExDevStatus.InsertItem(m_lstExDevStatus.GetItemCount(), "");
	}

	char szStr[128] = {0};
	sprintf(szStr, "%s", lpInter->sDevName);
	m_lstExDevStatus.SetItemText(iItemCount, 0, szStr);

	memset(szStr, 0, sizeof(szStr));
	if (0 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "其他", "Other");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);	
	}
	else if (1 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "远距离读头设备", "Long distance reading head device");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}
	else if (2 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "出入口控制机", "Entrance control device");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}
	else if (3 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "LED屏(外)", "LED Screen(external)");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}
	else if (4 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "LED屏(内)", "LED Screen(Internal)");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}
	else if (5 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "车检器", "Sensors");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}
	else if (6 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "道闸", "Gate");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}
	else if (7 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "票箱IC卡读写器", "Ballot Box IC Card Reader");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}
	else if (8 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "卡机IC卡读写器", "Card IC Card Reader");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}
	else if (9 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "发卡机", "Send Card Machine");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}
	else if (10 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "收卡机", "Receive Card Machine");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}
	else if (11 == lpInter->byExternalDevTpye)
	{
		g_StringLanType(szStr, "硬盘", "Hard Disk");
		m_lstExDevStatus.SetItemText(iItemCount, 1, szStr);
	}

	memset(szStr, 0, sizeof(szStr));
	sprintf(szStr, "%d", lpInter->byRelativeIndex);
	m_lstExDevStatus.SetItemText(iItemCount, 2, szStr);

	memset(szStr, 0, sizeof(szStr));
	if (0 == lpInter->byOnline)
	{
		g_StringLanType(szStr, "不在线", "Not Online");
		m_lstExDevStatus.SetItemText(iItemCount, 3, szStr);
	} 
	else if (1 == lpInter->byOnline)
	{
		g_StringLanType(szStr, "在线", "Online");
		m_lstExDevStatus.SetItemText(iItemCount, 3, szStr);
	}
	
}

void CDlgITSIOinCfg::OnBtnGetItsExdevstatus() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	//memset(&m_struVehCond, 0, sizeof(m_struVehCond));
	m_struExternalDevCond.dwSize = sizeof(NET_DVR_EXTERNAL_DEVCOND);
	if (11 == m_comDevType.GetCurSel())
	{
		m_struExternalDevCond.byExternalDevTpye = 0xff;
	} 
	else
	{
		m_struExternalDevCond.byExternalDevTpye = m_comDevType.GetCurSel() + 1;
	}
	//m_struExternalDevCond.byRelativeIndex = m_byRelativeIndex;
	if (8 == m_comRelativeIndex.GetCurSel())
	{
		m_struExternalDevCond.byRelativeIndex = 0xff;
	} 
	else
	{
		m_struExternalDevCond.byRelativeIndex = m_comRelativeIndex.GetCurSel() + 1;
	}
//	m_struExternalDevCond.byLaneID = m_comLaneID.GetCurSel();

	if (m_lHandle >= 0)
	{
		if (!NET_DVR_StopRemoteConfig(m_lHandle))
		{
			m_bGetNext = FALSE;
			g_StringLanType(szLan, "停止终端出入口外接设备信息获取失败", "Stop External Device Info Failed");
			AfxMessageBox(szLan);
			return;
		}
	} 
	
	m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_ITS_EXDEVSTATUS, &m_struExternalDevCond, sizeof(m_struExternalDevCond), NULL, NULL);
	if (m_lHandle >= 0)
	{
		m_bGetNext = TRUE;
		DWORD dwThreadId;
		m_lstExDevStatus.DeleteAllItems();
		m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetVehInfoThread), this, 0, &dwThreadId);
	}
	else
	{
		g_StringLanType(szLan, "终端出入口外接设备信息获取失败", "Get External Device Info Failed");
		AfxMessageBox(szLan);
		return;
	}
	
}


void CDlgITSIOinCfg::OnSelchangeComboDevType() 
{
	// TODO: Add your control notification handler code here
// 	int i = 0;
// 	CString strTemp;
// 	m_comRelativeIndex.InsertString(0, _T("其它"));
// 	if (3 == m_comDevType.GetCurSel())
// 	{
// 		for (i = 1; i<256; i++)
// 		{
// 			strTemp.Format(_T("索引%d"), i);
// 			m_comRelativeIndex.InsertString(i, strTemp);
// 		}
// 		m_comRelativeIndex.SetCurSel(0);	
// 	}
// 	else
// 	{
// 		for (i = 1; i<9; i++)
// 		{
// 			strTemp.Format(_T("索引%d"), i);
// 			m_comRelativeIndex.InsertString(i, strTemp);
// 		}
// 		m_comRelativeIndex.SetCurSel(0);
// 	}
// 	m_comRelativeIndex.InsertString(i+1, _T("全部信息"));
}

void CDlgITSIOinCfg::SetExternalDevCond(int iIndex)
{
	UpdateData(TRUE);

	LPNET_DVR_EXTERNAL_DEVCOND pStruExternalDevCond = m_pStruExternalDevCond;
	pStruExternalDevCond += iIndex;

	pStruExternalDevCond->dwSize = sizeof(NET_DVR_EXTERNAL_DEVCOND);
	pStruExternalDevCond->byExternalDevTpye = m_comDevType2.GetCurSel() + 1;
	pStruExternalDevCond->byRelativeIndex = iIndex+1;

	UpdateData(FALSE);
}

void CDlgITSIOinCfg::OnBtnSetItsExdevcfg() 
{
	// TODO: Add your control notification handler code here
	//SetExternalDevCond();
//	ExternalDevCFGToDlg(TRUE);
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	char szTemp[256] = {0};
	DWORD *pStatus = new DWORD[8];
    memset(pStatus, 0, sizeof(DWORD)*8);
	BOOL bStatus = FALSE;
	if(NULL == m_pStruExternalDevCFG || NULL == m_pStruExternalDevCond)
	{
		return;
	}

	if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_ITS_EXDEVCFG, 8, m_pStruExternalDevCond, 8*sizeof(NET_DVR_EXTERNAL_DEVCOND), \
		pStatus, m_pStruExternalDevCFG, 8*sizeof(NET_DVR_EXTERNAL_DEVCFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ITS_EXDEVCFG");
		delete [] pStatus;
		return;
	}
	else
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < 8; i++)
		{	
			if (*pStatusTmp != 0)
			{
				bStatus = TRUE;
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ITS_EXDEVCFG");
				delete [] pStatus;
				return;
			}
			pStatusTmp++;
		}

		if (!bStatus)
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ITS_EXDEVCFG");
		}
	}
	delete [] pStatus;
}

void CDlgITSIOinCfg::OnBtnGetItsExdevcfg() 
{
	// TODO: Add your control notification handler code here
	for(int i = 0; i<8; i++)
	{
		SetExternalDevCond(i);
	}
	

	BOOL bStatus = FALSE;
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	char szTemp[256] = {0};
	DWORD *pStatus = new DWORD[8];
    memset(pStatus, 0, sizeof(DWORD)*8);
	//memset(&m_struExternalDevCFG, 0, sizeof(NET_DVR_EXTERNAL_DEVCFG));
	memset(m_pStruExternalDevCFG, 0, 8*sizeof(NET_DVR_EXTERNAL_DEVCFG));
	if(NULL == m_pStruExternalDevCFG || NULL == m_pStruExternalDevCond)
	{
		return;
	}
	
	if (NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_ITS_EXDEVCFG, 8, m_pStruExternalDevCond, \
		8*sizeof(NET_DVR_EXTERNAL_DEVCOND), pStatus, m_pStruExternalDevCFG, 8*sizeof(NET_DVR_EXTERNAL_DEVCFG)))
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < 8; i++)
		{
			if (*pStatusTmp != 0)
			{
				bStatus = TRUE;
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ITS_EXDEVCFG");
				delete [] pStatus;
				return;
			}
			pStatusTmp++;
		}

		if (!pStatus)
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ITS_EXDEVCFG");
		} 
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ITS_EXDEVCFG");
		delete [] pStatus;
		return;
	}
	
	delete [] pStatus;
	
	m_comRelativeIndex2.SetCurSel(0);
	ExternalDevCFGToDlg(FALSE);

}

void CDlgITSIOinCfg::OnSelchangeComboDevType2() 
{
	// TODO: Add your control notification handler code here
// 	int i = 0;
// 	CString strTemp;
// 	m_comRelativeIndex2.InsertString(0, _T("其它"));
// 	if (3 == m_comDevType2.GetCurSel())
// 	{
// 		for (i = 1; i<256; i++)
// 		{
// 			strTemp.Format(_T("索引%d"), i);
// 			m_comRelativeIndex2.InsertString(i, strTemp);
// 		}
// 		m_comRelativeIndex2.SetCurSel(0);	
// 	}
// 	else
// 	{
// 		for (i = 1; i<9; i++)
// 		{
// 			strTemp.Format(_T("索引%d"), i);
// 			m_comRelativeIndex2.InsertString(i, strTemp);
// 		}
// 		m_comRelativeIndex2.SetCurSel(0);
// 	}
// 	m_comRelativeIndex2.InsertString(i+1, _T("全部信息"));
	m_comDevType3.SetCurSel(m_comDevType2.GetCurSel());
	OnSelchangeComboDevType3();
}

void CDlgITSIOinCfg::OnSelchangeComboDevType3() 
{
	// TODO: Add your control notification handler code here
	if (0 == m_comDevType3.GetCurSel())//远距离读头设备
	{
		//struRrReader 远距离读头设备
		GetDlgItem(IDC_IPADDRESS_READER_DEVIP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_READER_DEVPORT)->EnableWindow(TRUE);
		//struGateway 出入口控制机
		GetDlgItem(IDC_EDIT_GATEWAY_RS485NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GATEWAY_DEVCODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_GATEWAY_DATA)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_OFF_DET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ENTR_DET_CYCLE)->EnableWindow(FALSE);
		//struLed led屏
		GetDlgItem(IDC_COMBO_LED_EXTERNAL_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_IPADDRESS_LED_DEVIP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LED_DEVPORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LED_RS485NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LED_DEVCODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LED_CARD_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LED_SCREEN_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LED_SCREEN_USE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LED_DIS_MODE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_LED_CUST_INFO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LED_SCREEN_H)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LED_SCREEN_W)->EnableWindow(FALSE);
	}
	else if (1 == m_comDevType3.GetCurSel())//出入口控制机
	{
		//struRrReader 远距离读头设备
		GetDlgItem(IDC_IPADDRESS_READER_DEVIP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_READER_DEVPORT)->EnableWindow(FALSE);
		//struGateway 出入口控制机
		GetDlgItem(IDC_EDIT_GATEWAY_RS485NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_GATEWAY_DEVCODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_GATEWAY_DATA)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_OFF_DET)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ENTR_DET_CYCLE)->EnableWindow(TRUE);
		//struLed led屏
		GetDlgItem(IDC_COMBO_LED_EXTERNAL_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_IPADDRESS_LED_DEVIP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LED_DEVPORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LED_RS485NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LED_DEVCODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LED_CARD_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LED_SCREEN_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LED_SCREEN_USE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_LED_DIS_MODE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_LED_CUST_INFO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LED_SCREEN_H)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LED_SCREEN_W)->EnableWindow(FALSE);
	}
	else if (2 == m_comDevType3.GetCurSel())//led屏
	{
		//struRrReader 远距离读头设备
		GetDlgItem(IDC_IPADDRESS_READER_DEVIP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_READER_DEVPORT)->EnableWindow(FALSE);
		//struGateway 出入口控制机
		GetDlgItem(IDC_EDIT_GATEWAY_RS485NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_GATEWAY_DEVCODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_GATEWAY_DATA)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_OFF_DET)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ENTR_DET_CYCLE)->EnableWindow(FALSE);
		//struLed led屏
		m_comLedExteMode.SetCurSel(0);//默认为RS485
		GetDlgItem(IDC_COMBO_LED_EXTERNAL_MODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_IPADDRESS_LED_DEVIP)->EnableWindow(FALSE);//RS485时不生效
		GetDlgItem(IDC_EDIT_LED_DEVPORT)->EnableWindow(FALSE);//RS485时不生效
		GetDlgItem(IDC_EDIT_LED_RS485NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_LED_DEVCODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_LED_CARD_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_LED_SCREEN_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_LED_SCREEN_USE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_LED_DIS_MODE)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_LED_CUST_INFO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_LED_SCREEN_H)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_LED_SCREEN_W)->EnableWindow(TRUE);
	}

}

void CDlgITSIOinCfg::OnSelchangeComboLedExternalMode() 
{
	// TODO: Add your control notification handler code here
	if (0 == m_comLedExteMode.GetCurSel())
	{
		GetDlgItem(IDC_IPADDRESS_LED_DEVIP)->EnableWindow(FALSE);//RS485时不生效
		GetDlgItem(IDC_EDIT_LED_DEVPORT)->EnableWindow(FALSE);//RS485时不生效
	} 
	else if(1 == m_comLedExteMode.GetCurSel())
	{
		GetDlgItem(IDC_IPADDRESS_LED_DEVIP)->EnableWindow(TRUE);//RS485时不生效
		GetDlgItem(IDC_EDIT_LED_DEVPORT)->EnableWindow(TRUE);//RS485时不生效
	}
}

void CDlgITSIOinCfg::ExternalDevCFGToDlg(BOOL bSave)
{
	//bSave == TRUE时，从界面读到内存
	//bSave == FALSE时，从内存读到界面
	UpdateData(TRUE);

	CString csDevIP;
	
	if (bSave)
	{
		//m_pStruExternalDevCFG = &m_struExternalDevCFG;
		//pStruExternalDevCFG += (m_comRelativeIndex2.GetCurSel() - 1);
		LPNET_DVR_EXTERNAL_DEVCFG pStruExternalDevCFG = m_pStruExternalDevCFG;
		pStruExternalDevCFG += m_comRelativeIndex2.GetCurSel();

		pStruExternalDevCFG->dwSize = sizeof(NET_DVR_EXTERNAL_DEVCFG);
		pStruExternalDevCFG->byExternalDevTpye = m_comDevType3.GetCurSel() + 1;
		memcpy(pStruExternalDevCFG->sDevName, m_csDevName, m_csDevName.GetLength());
	
		if (0 == m_comDevType3.GetCurSel())
		{
			BYTE nField0,nField1,nField2,nField3; 
			m_ReaderDevIP.GetAddress(nField0,nField1,nField2,nField3);
			if(0 == nField0 && 0 == nField1 && 0 == nField2 && 0 == nField3)
			{
				csDevIP = _T("");
			}
			else
			{
				csDevIP.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);
			}
			memset(pStruExternalDevCFG->uExternalDevInfo.struRrReader.struDevIP.sIpV4, 0, \
				sizeof(pStruExternalDevCFG->uExternalDevInfo.struRrReader.struDevIP.sIpV4));
			memcpy(pStruExternalDevCFG->uExternalDevInfo.struRrReader.struDevIP.sIpV4, csDevIP, csDevIP.GetLength());
			
			pStruExternalDevCFG->uExternalDevInfo.struRrReader.wDevPort = m_dwReaderDevPort;
		} 
		else if (1 == m_comDevType3.GetCurSel())
		{
			pStruExternalDevCFG->uExternalDevInfo.struGateway.byRs485No = m_byGateWayRS485No;
			pStruExternalDevCFG->uExternalDevInfo.struGateway.byDevCtrlCode = m_byGateWayDevCode;
			pStruExternalDevCFG->uExternalDevInfo.struGateway.byAutoIssuedData = m_comGateWayIsData.GetCurSel();
			pStruExternalDevCFG->uExternalDevInfo.struGateway.byOfflineDetEnable = m_comOfflineDet.GetCurSel();
			pStruExternalDevCFG->uExternalDevInfo.struGateway.byDetCycle = m_byEntrDetCycle;
		}
		else if (2 == m_comDevType3.GetCurSel())
		{
			pStruExternalDevCFG->uExternalDevInfo.struLed.byExternalMode = m_comLedExteMode.GetCurSel();
			if (1 == m_comLedExteMode.GetCurSel())
			{
				BYTE nField0,nField1,nField2,nField3; 
				m_LEDDevIP.GetAddress(nField0,nField1,nField2,nField3);
				if(0 == nField0 && 0 == nField1 && 0 == nField2 && 0 == nField3)
				{
					csDevIP = _T("");
				}
				else
				{
					csDevIP.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);
				}
				memset(pStruExternalDevCFG->uExternalDevInfo.struLed.struDevIP.sIpV4, 0, \
					sizeof(pStruExternalDevCFG->uExternalDevInfo.struLed.struDevIP.sIpV4));
				memcpy(pStruExternalDevCFG->uExternalDevInfo.struLed.struDevIP.sIpV4, csDevIP, csDevIP.GetLength());

				pStruExternalDevCFG->uExternalDevInfo.struLed.wDevPort = m_dwLEDDevPort;
			}
			
			pStruExternalDevCFG->uExternalDevInfo.struLed.byRs485No = m_byLEDRs485No;
			pStruExternalDevCFG->uExternalDevInfo.struLed.byDevCtrlCode = m_byLEDDevCode;
			pStruExternalDevCFG->uExternalDevInfo.struLed.byCtrlCardType = m_comLedCardType.GetCurSel();
			pStruExternalDevCFG->uExternalDevInfo.struLed.byLedScreenType = m_comLedScreenType.GetCurSel();
			pStruExternalDevCFG->uExternalDevInfo.struLed.byLedScreenUse = m_comScreenUse.GetCurSel();
			pStruExternalDevCFG->uExternalDevInfo.struLed.byLedDisplayMode = m_comLedDisMode.GetCurSel() + 1;
			memcpy(pStruExternalDevCFG->uExternalDevInfo.struLed.sLedCustomInfo, m_csLEDCustInfo, m_csLEDCustInfo.GetLength());
			pStruExternalDevCFG->uExternalDevInfo.struLed.dwLedScreenH = m_dwLEDScreenH;
			pStruExternalDevCFG->uExternalDevInfo.struLed.dwLedScreenW = m_dwLEDScreenW;
		}
	} 
	else
	{

		if(NULL == m_pStruExternalDevCFG)
		{
			return;
		}

		LPNET_DVR_EXTERNAL_DEVCFG pStruExternalDevCFG = m_pStruExternalDevCFG;
		pStruExternalDevCFG += m_comRelativeIndex2.GetCurSel();

		//m_comDevType3.SetCurSel(pStruExternalDevCFG->byExternalDevTpye);
		m_csDevName.Format(_T("%s"), pStruExternalDevCFG->sDevName);
		
		if (1 == pStruExternalDevCFG->byExternalDevTpye)
		{
			csDevIP.Format(_T("%s"), pStruExternalDevCFG->uExternalDevInfo.struRrReader.struDevIP.sIpV4);
			BYTE nField0,nField1,nField2,nField3 = 0; 
			if (csDevIP.Compare(_T("")) != 0)
			{
				int nPos0 = csDevIP.FindOneOf(".");
				nField0 = atoi(csDevIP.Left(nPos0));
				
				int nPos1 = csDevIP.Find(".", nPos0 + 1);
				nField1 = atoi(csDevIP.Mid(nPos0 + 1, nPos1 - nPos0 -1));
				
				int nPos2 = csDevIP.Find(".", nPos1 + 1);
				nField2 = atoi(csDevIP.Mid(nPos1 + 1, nPos2 - nPos1 - 1));
				
				nField3 = atoi(csDevIP.Right(csDevIP.GetLength() - (nPos2 + 1)));
				
				m_ReaderDevIP.SetAddress(nField0, nField1, nField2, nField3);
			}
			else
			{
				m_ReaderDevIP.SetAddress(0, 0, 0, 0);
			}
			
			m_dwReaderDevPort = pStruExternalDevCFG->uExternalDevInfo.struRrReader.wDevPort;
		} 
		else if (2 == pStruExternalDevCFG->byExternalDevTpye)
		{
			m_byGateWayRS485No = pStruExternalDevCFG->uExternalDevInfo.struGateway.byRs485No;
			m_byGateWayDevCode = pStruExternalDevCFG->uExternalDevInfo.struGateway.byDevCtrlCode;
			m_comGateWayIsData.SetCurSel(pStruExternalDevCFG->uExternalDevInfo.struGateway.byAutoIssuedData);
			m_comOfflineDet.SetCurSel(pStruExternalDevCFG->uExternalDevInfo.struGateway.byOfflineDetEnable);
			m_byEntrDetCycle = pStruExternalDevCFG->uExternalDevInfo.struGateway.byDetCycle;
		}
		else if (3 == pStruExternalDevCFG->byExternalDevTpye)
		{
			m_comLedExteMode.SetCurSel(pStruExternalDevCFG->uExternalDevInfo.struLed.byExternalMode);
			OnSelchangeComboLedExternalMode();
			if (1 == pStruExternalDevCFG->uExternalDevInfo.struLed.byExternalMode)
			{
				csDevIP.Format(_T("%s"), (pStruExternalDevCFG->uExternalDevInfo.struLed.struDevIP.sIpV4));
				BYTE nField0,nField1,nField2,nField3 = 0; 
				if (csDevIP.Compare(_T("")) != 0)
				{
					int nPos0 = csDevIP.FindOneOf(".");
					nField0 = atoi(csDevIP.Left(nPos0));
					
					int nPos1 = csDevIP.Find(".", nPos0 + 1);
					nField1 = atoi(csDevIP.Mid(nPos0 + 1, nPos1 - nPos0 -1));
					
					int nPos2 = csDevIP.Find(".", nPos1 + 1);
					nField2 = atoi(csDevIP.Mid(nPos1 + 1, nPos2 - nPos1 - 1));
					
					nField3 = atoi(csDevIP.Right(csDevIP.GetLength() - (nPos2 + 1)));
					
					m_LEDDevIP.SetAddress(nField0, nField1, nField2, nField3);
				}
				else
				{
					m_LEDDevIP.SetAddress(0, 0, 0, 0);
				}

				m_dwLEDDevPort = pStruExternalDevCFG->uExternalDevInfo.struLed.wDevPort; 
			}
			
			m_byLEDRs485No = pStruExternalDevCFG->uExternalDevInfo.struLed.byRs485No;
			m_byLEDDevCode = pStruExternalDevCFG->uExternalDevInfo.struLed.byDevCtrlCode;
			m_comLedCardType.SetCurSel(pStruExternalDevCFG->uExternalDevInfo.struLed.byCtrlCardType);
			m_comLedScreenType.SetCurSel(pStruExternalDevCFG->uExternalDevInfo.struLed.byLedScreenType);
			m_comScreenUse.SetCurSel(pStruExternalDevCFG->uExternalDevInfo.struLed.byLedScreenUse);

			if (pStruExternalDevCFG->uExternalDevInfo.struLed.byLedDisplayMode > 0)
			{
				m_comLedDisMode.SetCurSel(pStruExternalDevCFG->uExternalDevInfo.struLed.byLedDisplayMode - 1);
			}

			m_csLEDCustInfo.Format(_T("%s"), pStruExternalDevCFG->uExternalDevInfo.struLed.sLedCustomInfo);
			m_dwLEDScreenH = pStruExternalDevCFG->uExternalDevInfo.struLed.dwLedScreenH; 
			m_dwLEDScreenW = pStruExternalDevCFG->uExternalDevInfo.struLed.dwLedScreenW;
		}
	}

	UpdateData(FALSE);
}


void CDlgITSIOinCfg::OnBtnSetEntrncedet() 
{
	// TODO: Add your control notification handler code here
//	(尚未开放)
// 	UpdateData(TRUE);
// 	NET_DVR_ENTRANCEDET_CFG struEntrancedet;
// 	memset(&struEntrancedet, 0, sizeof(struEntrancedet));
// 	struEntrancedet.dwSize = sizeof(NET_DVR_ENTRANCEDET_CFG);
// 	struEntrancedet.byOfflineDetEnable = m_comOffLine.GetCurSel();
// 	struEntrancedet.byDevCtrlCode = m_byDevCtrlCode;
// 	struEntrancedet.byDetCycle = m_byDetCycle;
// 
// 	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ITS_ENDETCFG, m_dwChannel, &struEntrancedet, sizeof(struEntrancedet)))
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ITS_ENDETCFG");
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ITS_ENDETCFG");
// 	}
// 	UpdateData(FALSE);
}

void CDlgITSIOinCfg::OnBtnGetEntrncedet() 
{
	// TODO: Add your control notification handler code here
//	(尚未开放)
// 	UpdateData(TRUE);
// 	DWORD dwReturn = 0;
// 	NET_DVR_ENTRANCEDET_CFG struEntrancedet;
// 	memset(&struEntrancedet, 0, sizeof(struEntrancedet));
// 	struEntrancedet.dwSize = sizeof(NET_DVR_ENTRANCEDET_CFG);
// 
// 	
// 	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ITS_ENDETCFG, m_dwChannel, &struEntrancedet, sizeof(struEntrancedet), &dwReturn))
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ITS_ENDETCFG");
// 	}
// 	else
// 	{
// 		m_comOffLine.SetCurSel(struEntrancedet.byOfflineDetEnable);
// 		m_byDevCtrlCode = struEntrancedet.byDevCtrlCode;
// 		m_byDetCycle = struEntrancedet.byDetCycle;
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ITS_ENDETCFG");
// 	}
// 	UpdateData(FALSE);
}

void CDlgITSIOinCfg::OnBtnControlEntrancedev() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_ENTRANCEDEV_COMMAND struEntranceDev;
	memset(&struEntranceDev, 0, sizeof(struEntranceDev));
	struEntranceDev.dwSize = sizeof(NET_DVR_ENTRANCEDEV_COMMAND);
	struEntranceDev.byDevCtrlCode = m_byDevCode;
	//struEntranceDev.byManualIssuedData = m_byManualIssuedData;
	struEntranceDev.byManualIssuedData = m_bManualIssuedData;
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SET_ITS_ENDEVCMD, &struEntranceDev, sizeof(struEntranceDev)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ITS_ENDEVCMD");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ITS_ENDEVCMD");
	}
	UpdateData(FALSE);
}

void CDlgITSIOinCfg::OnBtnControlEnissuedDatadel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_ENISSUED_DATADEL struDataDel;
	memset(&struDataDel, 0, sizeof(struDataDel));
	struDataDel.dwSize = sizeof(NET_DVR_ENISSUED_DATADEL);
	struDataDel.byDevCtrlCode = m_byEnissuedCode;
	
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SET_ENISSUED_DATADEL, &struDataDel, sizeof(struDataDel)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ENISSUED_DATADEL");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ENISSUED_DATADEL");
	}
	UpdateData(FALSE);
}

void CDlgITSIOinCfg::OnBtnSaveItsExdevcfg() 
{
	// TODO: Add your control notification handler code here
	SetExternalDevCond(m_comRelativeIndex2.GetCurSel());
	ExternalDevCFGToDlg(TRUE);
}

void CDlgITSIOinCfg::OnSelchangeComboRelativeIndex2() 
{
	// TODO: Add your control notification handler code here
	
	int i = m_comDevType2.GetCurSel();
	m_comDevType3.SetCurSel(i);

	OnSelchangeComboDevType3();
	ExternalDevCFGToDlg(FALSE);
}
