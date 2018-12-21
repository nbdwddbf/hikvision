// DlgLedConfig.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLedConfig.h"
#include "DlgLedConfigDisplay.h"
#include "DlgLedConfigRecv.h"
#include "DlgLEDCheckCond.h"
#include "CheckEnabled.h"
#include "ParseXMLUtil.h"
#include "DlgPictureUpload.h"
#include "JPEGPicDownload.h"
#include "DlgSmartSearchPicture.h"
#include "LEDScreenAdjust.h"

using namespace InformationReleaseSystem;

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLedConfig dialog


CDlgLedConfig::CDlgLedConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLedConfig::IDD, pParent)
    , m_dwEnableID(0)
    , m_bCheckEnable(FALSE)
{
	//{{AFX_DATA_INIT(CDlgLedConfig)
	m_BOutputEnable = FALSE;
	m_dwOutputPort = 0;
	m_dwOutputNo = 0;
	m_BZoom = FALSE;
	m_dwOutputNoCfg = 0;
	m_dwRefresh = 0;
	m_dwRelateInput = 0;
	m_dwHeight = 0;
	m_dwWidth = 0;
	m_dwOutputNoDisplay = 0;
	m_dwLineNo = 0;
	m_dwColumnNo = 0;
	m_dwDisplayWidth = 0;
	m_dwDisplayHeight = 0;
	m_BPortCfgEnable = FALSE;
	m_dwOutputJs = 0;
	m_dwPortIndexJs = 0;
	m_dwColumnNoPort = 0;
	m_dwHeightPortCfg = 0;
	m_dwWidthPortCfg = 0;
	m_dwLineNoPortCfg = 0;
	m_dwOutputPortCfgOne = 0;
	m_dwRealOutputPortCfg = 0;
	m_dwPairPort = 0;
	m_bBackupEnable = FALSE;
	m_bBlackedgeEnable = FALSE;
	m_dwCardWidth = 0;
	m_dwCardHeight = 0;
	m_bAutoAjust = FALSE;
	m_dwClock = 0;
	m_dwHPosition = 0;
	m_dwPhase = 0;
	m_dwRefreshRate = 0;
	m_dwResolutionHeight = 0;
	m_dwResolutionWidth = 0;
	m_dwVPosition = 0;
	m_dwInputNo = 0;
	m_iCurSel = -1; 
	m_iCurSelOutputPortCfg = -1; 
	m_iCurSelRecvCardInfo = -1;
	m_dwCount = 0;
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_lDeviceID = -1;
	memset(m_struPortCfg, 0, sizeof(m_struPortCfg));
	memset(m_status, 0, sizeof(m_status));
	memset(m_dwOutputPortCfg, 0, sizeof(m_dwOutputPortCfg));
}


void CDlgLedConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLedConfig)
	DDX_Control(pDX, IDC_COMBO_PORTCFG_MODE, m_cmbPortMode);
	DDX_Control(pDX, IDC_LST_PORTCFG_RECVCARDINFO, m_lstRecvCardInfo);
	DDX_Control(pDX, IDC_LST_PORTCFG_OUTPUT, m_lstOutput);
	DDX_Control(pDX, IDC_LST_LED_OUTPUT_PORT, m_lstOutputPort);
	DDX_Check(pDX, IDC_CHK_LED_OUTPUT_ENABLE, m_BOutputEnable);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUT_PORT, m_dwOutputPort);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTNO, m_dwOutputNo);
	DDX_Check(pDX, IDC_CHK_LED_OUTPUT_ZOOM, m_BZoom);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTCFG_OUTPUTNO, m_dwOutputNoCfg);
	DDX_Text(pDX, IDC_EDT_LED_REFRESH, m_dwRefresh);
	DDX_Text(pDX, IDC_EDT_LED_RELATEINPUT, m_dwRelateInput);
	DDX_Text(pDX, IDC_EDT_LED_RESOLUTIONHEIGHT, m_dwHeight);
	DDX_Text(pDX, IDC_EDT_LED_RESOLUTIONWIDTH, m_dwWidth);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTCFG_DISPLAY_OUTPUTNO, m_dwOutputNoDisplay);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTCFG_LINENO, m_dwLineNo);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTCFG_COLUMNNO, m_dwColumnNo);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTCFG_DIAPLAY_WIDTH, m_dwDisplayWidth);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTCFG_DISPLAY_HEIGHT, m_dwDisplayHeight);
	DDX_Check(pDX, IDC_CHK_PORTCFG_ENABLE, m_BPortCfgEnable);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTCFG_PORTCFG_OUTPUTNO_JS, m_dwOutputJs);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTCFG_PORTCFG_PORTINDEX, m_dwPortIndexJs);
	DDX_Text(pDX, IDC_EDT_LED_PORTCFG_COLUMNNO, m_dwColumnNoPort);
	DDX_Text(pDX, IDC_EDT_LED_PORTCFG_HEIGHT, m_dwHeightPortCfg);
	DDX_Text(pDX, IDC_EDT_LED_PORTCFG_WIDTH, m_dwWidthPortCfg);
	DDX_Text(pDX, IDC_EDT_LED_PROTCFG_LINENO, m_dwLineNoPortCfg);
	DDX_Text(pDX, IDC_EDT_PORTCFG_OUTPUT, m_dwOutputPortCfgOne);
	DDX_Text(pDX, IDC_EDT_PORTCFG_OUTPUT_REALOUTPUT, m_dwRealOutputPortCfg);
	DDX_Text(pDX, IDC_EDIT_PORTCFG_PAIRPORT, m_dwPairPort);
	DDX_Check(pDX, IDC_CHK_PORTCFG_BACKUP_ENABLE, m_bBackupEnable);
	DDX_Check(pDX, IDC_CHECK_LED_OUTPUTCFG_BLACKEDGE, m_bBlackedgeEnable);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTCFG_DIAPLAY_CARDWIDTH, m_dwCardWidth);
	DDX_Text(pDX, IDC_EDT_LED_OUTPUTCFG_DISPLAY_CARDHEIGHT, m_dwCardHeight);
	DDX_Check(pDX, IDC_CHK_INPUTCFG_AUTOAJUST_ENABLE, m_bAutoAjust);
	DDX_Text(pDX, IDC_EDIT_INPUTCFG_CLOCK, m_dwClock);
	DDX_Text(pDX, IDC_EDIT_INPUTCFG_HPOSITION, m_dwHPosition);
	DDX_Text(pDX, IDC_EDIT_INPUTCFG_PHASE, m_dwPhase);
	DDX_Text(pDX, IDC_EDIT_INPUTCFG_REFRESH, m_dwRefreshRate);
	DDX_Text(pDX, IDC_EDIT_INPUTCFG_RESOLUTION_HEIGHT, m_dwResolutionHeight);
	DDX_Text(pDX, IDC_EDIT_INPUTCFG_RESOLUTION_WIDTH, m_dwResolutionWidth);
	DDX_Text(pDX, IDC_EDIT_INPUTCFG_VPOSITION, m_dwVPosition);
	DDX_Text(pDX, IDC_EDIT_INPUT_INPUTNO, m_dwInputNo);
	DDX_Text(pDX, IDC_EDIT_PORTCFG_COUNT, m_dwCount);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_LED_ID, m_dwEnableID);
	DDX_Check(pDX, IDC_CHECK_LED_ENABLE, m_bCheckEnable);
	DDX_Control(pDX, IDC_PROGRESS_UPLOADLEDPIC, m_ProUploadLedPic);
	DDX_Control(pDX, IDC_LIST_LEDPIC, m_ListLedPic);
}


BEGIN_MESSAGE_MAP(CDlgLedConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgLedConfig)
	ON_BN_CLICKED(IDC_BUT_OUTPUT_PORT_ADD, OnButOutputPortAdd)
	ON_BN_CLICKED(IDC_BUT_OUTPUT_PORT_DELETE, OnButOutputPortDelete)
	ON_BN_CLICKED(IDC_BUT_OUTPUT_PORT_GET, OnButOutputCfgGet)
	ON_BN_CLICKED(IDC_BUT_OUTPUT_PORT_SET, OnButOutputCfgSet)
	ON_NOTIFY(NM_CLICK, IDC_LST_LED_OUTPUT_PORT, OnClickLstLedOutputPort)
	ON_BN_CLICKED(IDC_BUT_OUTPUTCFG_GET, OnButOutputGet)
	ON_BN_CLICKED(IDC_BUT_OUTPUTCFG_SET, OnButOutputSet)
	ON_BN_CLICKED(IDC_BUT_OUTPUTCFG_DISPLAY_GET, OnButDisplayGet)
	ON_BN_CLICKED(IDC_BUT_OUTPUT_DISPLAY_SET, OnButDisplaySet)
//	ON_BN_CLICKED(IDC_BUT_OUTPUT_PORTCFG_ADD, OnButPortcfgAdd)
	ON_BN_CLICKED(IDC_BUT_PORTCFG_DEL, OnButPortCfgPortDel)
	ON_BN_CLICKED(IDC_BUT_PORTCFG_MOD, OnButPortCfgPortMod)
	ON_BN_CLICKED(IDC_BUT_OUTPUT_PORTCFG_GET, OnButPortcfgGet)
	ON_NOTIFY(NM_CLICK, IDC_LST_PORTCFG_OUTPUT, OnClickLstPortcfgOutput)
	ON_NOTIFY(NM_CLICK, IDC_LST_PORTCFG_RECVCARDINFO, OnClickLstRecvcardinfo)
	ON_BN_CLICKED(IDC_BUT_OUTPUT_PORTCFG_GETALL, OnButPortcfgGetall)
	ON_BN_CLICKED(IDC_BUT_PORTCFG_SET, OnButPortcfgSet)
	ON_BN_CLICKED(IDC_BTN_INPUTCFG_GET, OnBtnInputcfgGet)
	ON_BN_CLICKED(IDC_BTN_INPUTCFG_SET, OnBtnInputcfgSet)
	ON_BN_CLICKED(IDC_BTN_DISPLAY_CONFIG, OnBtnDisplayConfig)
	ON_BN_CLICKED(IDC_BTN_RECVCARD_CONFIG, OnBtnRecvcardConfig)
	ON_BN_CLICKED(IDC_BUT_OUTPUT_PORT_MODIFY, OnButOutputPortModify)
	ON_BN_CLICKED(IDC_BUT_OUTPUT_PORTCFG_MOD, OnButOutputPortcfgMod)
	ON_BN_CLICKED(IDC_BUT_PORTCFG_ADD, OnButPortCfgPortAdd)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_CHECK, &CDlgLedConfig::OnBnClickedBtnCheck)
    ON_BN_CLICKED(IDC_BTN_ENABLE_GET, &CDlgLedConfig::OnBnClickedBtnEnableGet)
    ON_BN_CLICKED(IDC_BTN_ENABLE_SET, &CDlgLedConfig::OnBnClickedBtnEnableSet)
	ON_BN_CLICKED(IDC_BTN_BROSEPICPATH, &CDlgLedConfig::OnBnClickedBtnBrosepicpath)
	ON_BN_CLICKED(IDC_BTN_UPLOADLEDPIC, &CDlgLedConfig::OnBnClickedBtnUploadledpic)
	ON_BN_CLICKED(IDC_BTN_DELLEDPIC, &CDlgLedConfig::OnBnClickedButDelLedPic)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgLedConfig::OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLedConfig message handlers

void CDlgLedConfig::OnButOutputPortAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	CString csTmp; 
	DWORD dwCount = m_lstOutputPort.GetItemCount();
	csTmp.Format("%d", dwCount+1);
	int iIndex =  m_lstOutputPort.InsertItem(dwCount, csTmp);
	csTmp.Format("%d", m_dwOutputPort);
	m_lstOutputPort.SetItemText(iIndex, 1, csTmp); 
	m_lstOutputPort.SetItemData(iIndex, m_dwOutputPort);
	UpdateData(FALSE); 
}

void CDlgLedConfig::OnButOutputPortDelete() 
{
	// TODO: Add your control notification handler code here
	if (m_iCurSel == -1)
	{
		return;
	}
	DWORD dwCount = m_lstOutputPort.GetItemCount(); 
	CString csTmp; 
	DWORD dwNextData = 0; 
	for(int i = m_iCurSel;  i < dwCount-1;  i++)
	{
		dwNextData = m_lstOutputPort.GetItemData(i+1);
		csTmp.Format("%d", dwNextData ); 
		m_lstOutputPort.SetItemText(i, 1, csTmp);
		m_lstOutputPort.SetItemData(i, dwNextData);
	}
	m_lstOutputPort.DeleteItem(dwCount-1);
	m_dwOutputPort = 0;
	m_iCurSel = -1;
	UpdateData(FALSE);
}

void CDlgLedConfig::UpdatePortList(const NET_DVR_LED_OUTPUT_PORT_CFG &struOutputCfg)
{
	m_lstOutputPort.DeleteAllItems(); 
	CString csTmp; 
	for (int i = 0; i < struOutputCfg.dwPortNum; i++)
	{
		csTmp.Format("%d", i+1); 
		m_lstOutputPort.InsertItem(i, csTmp); 
		csTmp.Format("%d", struOutputCfg.dwPortNo[i]); 
		m_lstOutputPort.SetItemText(i,1, csTmp); 
		m_lstOutputPort.SetItemData(i, struOutputCfg.dwPortNo[i]);
	}
} 
void CDlgLedConfig::OnButOutputCfgGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_LED_OUTPUT_PORT_CFG struPortCfg = {0};
	struPortCfg.dwSize = sizeof(struPortCfg);
	DWORD dwRet; 
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_OUTPUT_PORT_CFG, m_dwOutputNo, &struPortCfg, sizeof(struPortCfg), &dwRet))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_LED_OUTPUT_PORT_CFG");
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_LED_OUTPUT_PORT_CFG");
	m_BOutputEnable = struPortCfg.byEnabled; 
	UpdatePortList(struPortCfg); 
	UpdateData(FALSE); 
}

void CDlgLedConfig::OnButOutputCfgSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_LED_OUTPUT_PORT_CFG struPortCfg = {0};
	struPortCfg.dwSize = sizeof(struPortCfg);
	struPortCfg.byEnabled = m_BOutputEnable; 
	struPortCfg.dwPortNum = m_lstOutputPort.GetItemCount();
	for (int i = 0; i < struPortCfg.dwPortNum; i++)
	{
		struPortCfg.dwPortNo[i] = m_lstOutputPort.GetItemData(i); 
	}
	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_LED_OUTPUT_PORT_CFG, m_dwOutputNo, &struPortCfg, sizeof(struPortCfg)))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_SET_LED_OUTPUT_PORT_CFG");
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_LED_OUTPUT_PORT_CFG");

}

BOOL CDlgLedConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	char szLan[128]; 
	m_lstOutputPort.SetExtendedStyle(m_lstOutputPort.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	g_StringLanType(szLan, "序号", "Index");
	m_lstOutputPort.InsertColumn(0, szLan, LVCFMT_LEFT, 60);
	g_StringLanType(szLan, "端口号", "PortNo.");
	m_lstOutputPort.InsertColumn(1, szLan, LVCFMT_LEFT, 60);

	m_lstOutput.SetExtendedStyle(m_lstOutput.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	g_StringLanType(szLan, "序号", "Index");
	m_lstOutput.InsertColumn(0, szLan, LVCFMT_LEFT, 60);
	g_StringLanType(szLan, "输出端口", "PortNo.");
	m_lstOutput.InsertColumn(1, szLan, LVCFMT_LEFT, 60);
	g_StringLanType(szLan, "启用", "Enable");
	m_lstOutput.InsertColumn(2, szLan, LVCFMT_LEFT, 60);
	g_StringLanType(szLan, "启用备份", "Backup Enable");
	m_lstOutput.InsertColumn(3, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "端口模式", "Port Mode");
	m_lstOutput.InsertColumn(4, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "配对端口", "Pair PortNo.");
	m_lstOutput.InsertColumn(5, szLan, LVCFMT_LEFT, 80);

	m_lstRecvCardInfo.SetExtendedStyle(m_lstRecvCardInfo.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	g_StringLanType(szLan, "序号", "Index");
	m_lstRecvCardInfo.InsertColumn(0, szLan, LVCFMT_LEFT, 60);
	g_StringLanType(szLan, "行号", "LineNo.");
	m_lstRecvCardInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 50);
	g_StringLanType(szLan, "列号", "ColumnNo.");
	m_lstRecvCardInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 50);
	g_StringLanType(szLan, "宽度", "Width.");
	m_lstRecvCardInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 50);
	g_StringLanType(szLan, "高度", "Height.");
	m_lstRecvCardInfo.InsertColumn(4, szLan, LVCFMT_LEFT, 50);
	m_ListLedPic.SetExtendedStyle(m_ListLedPic.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	g_StringLanType(szLan, "文件编号", "FileNo.");
	m_ListLedPic.InsertColumn(0, szLan, LVCFMT_LEFT, 70);
	g_StringLanType(szLan, "文件路径", "FilePath");
	m_ListLedPic.InsertColumn(2, szLan, LVCFMT_LEFT, 350);
	g_StringLanType(szLan, "上传状态", "Upload Status");
	m_ListLedPic.InsertColumn(3, szLan, LVCFMT_LEFT, 60);
	m_lDeviceID = g_pMainDlg->GetCurDeviceIndex();
	m_ProUploadLedPic.SetPos(0);
	//m_fileNo[MAX_COUNT] = {0};
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgLedConfig::OnClickLstLedOutputPort(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	POSITION  iPos = m_lstOutputPort.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	m_iCurSel = m_lstOutputPort.GetNextSelectedItem(iPos);
	m_dwOutputPort = atoi(m_lstOutputPort.GetItemText(m_iCurSel, 1).GetBuffer(0));
	UpdateData(FALSE);
	*pResult = 0;
}


void CDlgLedConfig::OnButOutputGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_LED_OUTPUT_CFG struOutputCfg = {0};
	struOutputCfg.dwSize = sizeof(struOutputCfg);
	DWORD dwRet; 
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_OUTPUT_CFG, m_dwOutputNoCfg, &struOutputCfg, sizeof(struOutputCfg), &dwRet))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_LED_OUTPUT_CFG");
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_LED_OUTPUT_CFG");
	m_BZoom = struOutputCfg.byEnableZoom; 
	m_dwWidth = struOutputCfg.wLEDWidth; 
	m_dwHeight = struOutputCfg.wLEDHeight; 
	m_dwRefresh = struOutputCfg.dwRefreshRate; 
	m_dwRelateInput = struOutputCfg.dwInputNO;
	m_bBlackedgeEnable = struOutputCfg.byAutoCutBlackEdge;
	UpdateData(FALSE); 
}

void CDlgLedConfig::OnButOutputSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_LED_OUTPUT_CFG struOutputCfg = {0}; 
	struOutputCfg.dwSize = sizeof(struOutputCfg);
	struOutputCfg.byEnableZoom	= m_BZoom; 
	struOutputCfg.wLEDWidth = m_dwWidth; 
	struOutputCfg.wLEDHeight = m_dwHeight; 
	struOutputCfg.dwRefreshRate = m_dwRefresh; 
	struOutputCfg.dwInputNO = m_dwRelateInput;
	struOutputCfg.byAutoCutBlackEdge = m_bBlackedgeEnable;

	if(! NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_LED_OUTPUT_CFG, m_dwOutputNoCfg, &struOutputCfg, sizeof(struOutputCfg)))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_SET_LED_OUTPUT_CFG");
		return ; 
	}
	
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_LED_OUTPUT_CFG");
}

void CDlgLedConfig::OnButDisplayGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_LED_DISPLAY_AREA struDisplayArea = {0}; 
	struDisplayArea.dwSize = sizeof(struDisplayArea);
	DWORD dwRet; 
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_DISPLAY_AREA_CFG, m_dwOutputNoDisplay, &struDisplayArea, sizeof(struDisplayArea), &dwRet))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_LED_DISPLAY_AREA_CFG");
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_LED_DISPLAY_AREA_CFG");
	m_dwLineNo = struDisplayArea.struLCInfo.wLine; 
	m_dwColumnNo = struDisplayArea.struLCInfo.wColumn; 
	m_dwDisplayWidth = struDisplayArea.wWidth; 
	m_dwDisplayHeight = struDisplayArea.wHeight;
	m_dwCardHeight = struDisplayArea.wRecvCardHeigt;
	m_dwCardWidth = struDisplayArea.wRecvCardWidth;
	UpdateData(FALSE); 
}

void CDlgLedConfig::OnButDisplaySet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_LED_DISPLAY_AREA struDisplayArea = {0};
	struDisplayArea.dwSize = sizeof(struDisplayArea); 
	struDisplayArea.struLCInfo.wLine = m_dwLineNo ; 
	struDisplayArea.struLCInfo.wColumn = m_dwColumnNo; 
	struDisplayArea.wWidth = m_dwDisplayWidth ; 
	struDisplayArea.wHeight = m_dwDisplayHeight;
	struDisplayArea.wRecvCardHeigt = m_dwCardHeight;
	struDisplayArea.wRecvCardWidth = m_dwCardWidth;

	if(! NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_LED_DISPLAY_AREA_CFG, m_dwOutputNoDisplay, &struDisplayArea, sizeof(struDisplayArea)))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_SET_LED_DISPLAY_AREA_CFG");
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_LED_DISPLAY_AREA_CFG");
}

void CDlgLedConfig::OnButPortcfgAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwCount = m_lstOutput.GetItemCount(); 
	memset(&m_struPortCfg[dwCount], 0, sizeof(m_struPortCfg[0]));
	m_struPortCfg[dwCount].dwSize = sizeof(m_struPortCfg[0]); 
	m_dwOutputPortCfg[dwCount] = m_dwOutputPortCfgOne;
	m_struPortCfg[dwCount].byEnabled = m_BPortCfgEnable;
	m_struPortCfg[dwCount].struLedPortBackup.byEnabled = m_bBackupEnable;
	m_struPortCfg[dwCount].struLedPortBackup.byPortMode = m_cmbPortMode.GetCurSel()+1;
	m_struPortCfg[dwCount].struLedPortBackup.dwPairPort = m_dwPairPort;
	CString csTmp; 
	csTmp.Format("%d", dwCount+1); 
	m_lstOutput.InsertItem(dwCount, csTmp); 
	csTmp.Format("%d", m_dwOutputPortCfgOne); 
	m_lstOutput.SetItemText(dwCount, 1, csTmp); 
	csTmp = (m_BPortCfgEnable)?"Yes":"No"; 
	m_lstOutput.SetItemText(dwCount, 2, csTmp); 
	csTmp = (m_bBackupEnable)?"Yes":"No";
	m_lstOutput.SetItemText(dwCount, 3, csTmp);
	csTmp = "";
	if (m_struPortCfg[dwCount].struLedPortBackup.byPortMode == 1)
	{
		csTmp = "主口";
	}
	else if (m_struPortCfg[dwCount].struLedPortBackup.byPortMode == 2)
	{
		csTmp = "备份口";
	}
	m_lstOutput.SetItemText(dwCount, 4, csTmp);
	csTmp.Format("%d", m_dwPairPort);
	m_lstOutput.SetItemText(dwCount, 5, csTmp);
	UpdateData(FALSE);
}

void CDlgLedConfig::UpdateOutputListPortCfg(DWORD dwCount)
{
	UpdateData(TRUE); 
	m_lstOutput.DeleteAllItems(); 
	CString csTmp; 
	for (int i = 0; i < dwCount; i++)
	{
		csTmp.Format("%d", i+1); 
		m_lstOutput.InsertItem(i, csTmp);
		csTmp.Format("%d", m_dwOutputPortCfg[i]);
		m_lstOutput.SetItemText(i, 1, csTmp); 
		csTmp = (m_struPortCfg[i].byEnabled)?"Yes":"No"; 
		m_lstOutput.SetItemText(i, 2, csTmp);
		csTmp = (m_struPortCfg[i].struLedPortBackup.byEnabled)?"Yes":"No";
		m_lstOutput.SetItemText(i, 3, csTmp);
		csTmp = "";
		if (m_struPortCfg[i].struLedPortBackup.byPortMode == 1)
		{
			csTmp = "主口";
		}
		else if (m_struPortCfg[i].struLedPortBackup.byPortMode == 2)
		{
			csTmp = "备份口";
		}
		m_lstOutput.SetItemText(i, 4, csTmp);
		csTmp.Format("%d", m_struPortCfg[i].struLedPortBackup.dwPairPort);
		m_lstOutput.SetItemText(i, 5, csTmp);
	}
	UpdateData(FALSE);
}


void CDlgLedConfig::OnButPortcfgDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	DWORD dwCount = m_lstOutput.GetItemCount(); 
	if (m_iCurSelOutputPortCfg == -1)
	{
		return ; 
	}
	for (int i = m_iCurSelOutputPortCfg; i < dwCount-1; i++)
	{
		m_dwOutputPortCfg[i] = m_dwOutputPortCfg[i+1]; 
		m_struPortCfg[i] = m_struPortCfg[i+1];
	}
	m_dwOutputPortCfg[dwCount-1] = 0;
	memset(&m_struPortCfg[dwCount-1], 0, sizeof(m_struPortCfg[dwCount-1]));
	UpdateOutputListPortCfg(dwCount-1);
	m_dwOutputPortCfgOne = 0;
	m_BPortCfgEnable = FALSE;
	m_bBackupEnable = FALSE;
	m_cmbPortMode.SetCurSel(-1);
	m_dwPairPort = 0;
	m_iCurSelOutputPortCfg = -1;
	m_lstRecvCardInfo.DeleteAllItems();
	m_dwOutputJs = 0;
	m_dwPortIndexJs = 0;
	m_dwLineNoPortCfg = 0;
	m_dwColumnNoPort = 0;
	m_dwWidthPortCfg = 0;
	m_dwHeightPortCfg = 0;
	m_iCurSelRecvCardInfo = -1;
	UpdateData(FALSE);
}

void CDlgLedConfig::OnButPortCfgPortAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	if (m_iCurSelOutputPortCfg == -1)
	{
		return ; 
	}
	DWORD dwCount = m_lstRecvCardInfo.GetItemCount(); 
	LPNET_DVR_LED_RECV_CARD_INFO lpCardInfo = &m_struPortCfg[m_iCurSelOutputPortCfg].struRecvCard[dwCount];
	memset(lpCardInfo, 0, sizeof(NET_DVR_LED_RECV_CARD_INFO));
	lpCardInfo->struPos.wLine = m_dwLineNoPortCfg; 
	lpCardInfo->struPos.wColumn = m_dwColumnNoPort; 
	lpCardInfo->wRecvCardWidth = m_dwWidthPortCfg; 
	lpCardInfo->wRecvCardHeigt = m_dwHeightPortCfg; 
	CString csTmp; 
	csTmp.Format("%d", dwCount+1); 
	m_lstRecvCardInfo.InsertItem(dwCount, csTmp); 
	csTmp.Format("%d", m_dwLineNoPortCfg); 
	m_lstRecvCardInfo.SetItemText(dwCount, 1, csTmp); 
	csTmp.Format("%d", m_dwColumnNoPort); 
	m_lstRecvCardInfo.SetItemText(dwCount, 2, csTmp); 
	csTmp.Format("%d", m_dwWidthPortCfg); 
	m_lstRecvCardInfo.SetItemText(dwCount, 3, csTmp); 
	csTmp.Format("%d", m_dwHeightPortCfg); 
	m_lstRecvCardInfo.SetItemText(dwCount, 4, csTmp);
	m_struPortCfg[m_iCurSelOutputPortCfg].dwRecvCardNum ++;
	UpdateData(FALSE); 

}

void CDlgLedConfig::UpdatRecvCardList()
{
	UpdateData(TRUE); 
	m_lstRecvCardInfo.DeleteAllItems(); 
	CString csTmp; 
	LPNET_DVR_LED_RECV_CARD_INFO lpCardInfo = &m_struPortCfg[m_iCurSelOutputPortCfg].struRecvCard[0];
	for (int i = 0; i < m_struPortCfg[m_iCurSelOutputPortCfg].dwRecvCardNum ; i++)
	{
		csTmp.Format("%d", i+1); 
		m_lstRecvCardInfo.InsertItem(i, csTmp); 
		csTmp.Format("%d", lpCardInfo[i].struPos.wLine); 
		m_lstRecvCardInfo.SetItemText(i, 1, csTmp); 
		csTmp.Format("%d", lpCardInfo[i].struPos.wColumn); 
		m_lstRecvCardInfo.SetItemText(i, 2, csTmp); 
		csTmp.Format("%d", lpCardInfo[i].wRecvCardWidth); 
		m_lstRecvCardInfo.SetItemText(i, 3, csTmp); 
		csTmp.Format("%d", lpCardInfo[i].wRecvCardHeigt);
		m_lstRecvCardInfo.SetItemText(i, 4, csTmp);
	}
	UpdateData(FALSE);
}


void CDlgLedConfig::OnButPortCfgPortDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_iCurSelRecvCardInfo == -1)
	{
		return ; 
	}
	DWORD dwCount = m_lstRecvCardInfo.GetItemCount(); 
	LPNET_DVR_LED_RECV_CARD_INFO lpCardInfo = &m_struPortCfg[m_iCurSelOutputPortCfg].struRecvCard[m_iCurSelRecvCardInfo];
	for (int i=m_iCurSelRecvCardInfo; i<dwCount-1; i++)
	{
		*lpCardInfo = *(lpCardInfo+1); 
        lpCardInfo++; 
	}
	memset(lpCardInfo, 0, sizeof(*lpCardInfo));
	m_struPortCfg[m_iCurSelOutputPortCfg].dwRecvCardNum--;
	UpdatRecvCardList();
	m_dwPortIndexJs = 0;
	m_dwLineNoPortCfg = 0;
	m_dwColumnNoPort = 0;
	m_dwWidthPortCfg = 0;
	m_dwHeightPortCfg = 0;
	UpdateData(FALSE);
}

void CDlgLedConfig::OnButPortCfgPortMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_iCurSelRecvCardInfo == -1)
	{
		return ; 
	}
	LPNET_DVR_LED_RECV_CARD_INFO lpCardInfo = &m_struPortCfg[m_iCurSelOutputPortCfg].struRecvCard[m_iCurSelRecvCardInfo];
	memset(lpCardInfo, 0, sizeof(NET_DVR_LED_RECV_CARD_INFO));
	lpCardInfo->struPos.wLine = m_dwLineNoPortCfg; 
	lpCardInfo->struPos.wColumn = m_dwColumnNoPort; 
	lpCardInfo->wRecvCardWidth = m_dwWidthPortCfg; 
	lpCardInfo->wRecvCardHeigt = m_dwHeightPortCfg; 

	CString csTmp; 
	DWORD dwIndex = m_iCurSelRecvCardInfo;
	csTmp.Format("%d", m_dwLineNoPortCfg); 
	m_lstRecvCardInfo.SetItemText(dwIndex, 1, csTmp); 
	csTmp.Format("%d", m_dwColumnNoPort); 
	m_lstRecvCardInfo.SetItemText(dwIndex, 2, csTmp); 
	csTmp.Format("%d", m_dwWidthPortCfg); 
	m_lstRecvCardInfo.SetItemText(dwIndex, 3, csTmp); 
	csTmp.Format("%d", m_dwHeightPortCfg); 
	m_lstRecvCardInfo.SetItemText(dwIndex, 4, csTmp); 
	UpdateData(FALSE); 
}



void CDlgLedConfig::OnClickLstPortcfgOutput(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdateData(TRUE); 
	POSITION  iPos = m_lstOutput.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	m_iCurSelOutputPortCfg = m_lstOutput.GetNextSelectedItem(iPos);
	m_dwOutputPortCfgOne = m_dwOutputPortCfg[m_iCurSelOutputPortCfg];
	m_dwOutputJs = m_dwOutputPortCfgOne; 
	m_BPortCfgEnable = m_struPortCfg[m_iCurSelOutputPortCfg].byEnabled;
	m_bBackupEnable = m_struPortCfg[m_iCurSelOutputPortCfg].struLedPortBackup.byEnabled;
	m_cmbPortMode.SetCurSel(m_struPortCfg[m_iCurSelOutputPortCfg].struLedPortBackup.byPortMode-1);
	m_dwPairPort = m_struPortCfg[m_iCurSelOutputPortCfg].struLedPortBackup.dwPairPort;
	UpdateData(FALSE); 
    UpdatRecvCardList(); 
}

void CDlgLedConfig::OnClickLstRecvcardinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here	
	*pResult = 0;
	UpdateData(TRUE); 
	POSITION  iPos = m_lstRecvCardInfo.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	m_iCurSelRecvCardInfo = m_lstRecvCardInfo.GetNextSelectedItem(iPos);
	if (m_iCurSelRecvCardInfo > m_lstRecvCardInfo.GetItemCount())
	{
		m_iCurSelRecvCardInfo = -1; 
		return; 
	}
	if (m_iCurSelOutputPortCfg == -1)
	{
		m_iCurSelOutputPortCfg = 0;
	}
	m_dwOutputJs = m_dwOutputPortCfg[m_iCurSelOutputPortCfg]; 
	m_dwPortIndexJs = m_iCurSelRecvCardInfo;
	m_dwLineNoPortCfg = m_struPortCfg[m_iCurSelOutputPortCfg].struRecvCard[m_iCurSelRecvCardInfo].struPos.wLine; 
	m_dwColumnNoPort = m_struPortCfg[m_iCurSelOutputPortCfg].struRecvCard[m_iCurSelRecvCardInfo].struPos.wColumn; 
	m_dwWidthPortCfg =  m_struPortCfg[m_iCurSelOutputPortCfg].struRecvCard[m_iCurSelRecvCardInfo].wRecvCardWidth; 
	m_dwHeightPortCfg = m_struPortCfg[m_iCurSelOutputPortCfg].struRecvCard[m_iCurSelRecvCardInfo].wRecvCardHeigt;
	UpdateData(FALSE); 
}

void CDlgLedConfig::OnButPortcfgGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	DWORD dwCount = m_dwCount;
	for (int nCnt = 0; nCnt < dwCount; nCnt++)
	{
		m_dwOutputPortCfg[nCnt] = nCnt+1;
	}
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_LED_PORT_CFG, dwCount, m_dwOutputPortCfg, dwCount*sizeof(DWORD), \
		m_status, &m_struPortCfg, dwCount*sizeof(NET_DVR_LED_PORT_CFG)))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_LED_PORT_CFG");
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_LED_PORT_CFG");

	UpdateOutputListPortCfg(dwCount); 
	m_dwOutputPortCfgOne = 0;
	m_BPortCfgEnable = FALSE;
	m_bBackupEnable = FALSE;
	m_cmbPortMode.SetCurSel(-1);
	m_dwPairPort = 0;
	m_iCurSelOutputPortCfg = -1;
	m_lstRecvCardInfo.DeleteAllItems();
	m_dwOutputJs = 0;
	m_dwPortIndexJs = 0;
	m_dwLineNoPortCfg = 0;
	m_dwColumnNoPort = 0;
	m_dwWidthPortCfg = 0;
	m_dwHeightPortCfg = 0;
	m_iCurSelRecvCardInfo = -1;
	UpdateData(FALSE);
}

void CDlgLedConfig::OnButPortcfgGetall() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	char pMen[sizeof(DWORD) + sizeof(m_struPortCfg)] = {0};
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_ALL_LED_PORT_CFG, 0xffffffff, &m_dwRealOutputPortCfg, sizeof(m_dwRealOutputPortCfg), \
		m_status, pMen, sizeof(DWORD) + sizeof(m_struPortCfg)))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_LED_PORT_CFG 0xffffffff");
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_LED_PORT_CFG 0xffffffff");
	DWORD dwCount = *((LPDWORD) pMen);
	LPNET_DVR_LED_PORT_CFG lpPortCfg = (LPNET_DVR_LED_PORT_CFG)(pMen +sizeof(DWORD));
	memcpy(m_struPortCfg, lpPortCfg, dwCount*sizeof(NET_DVR_LED_PORT_CFG));
	for (int i = 0; i < dwCount; i++)
	{
		m_dwOutputPortCfg[i] = m_struPortCfg[i].dwPortNo;
	}

	UpdateOutputListPortCfg(dwCount);
	m_dwOutputPortCfgOne = 0;
	m_BPortCfgEnable = FALSE;
	m_bBackupEnable = FALSE;
	m_cmbPortMode.SetCurSel(-1);
	m_dwPairPort = 0;
	m_iCurSelOutputPortCfg = -1;
	m_lstRecvCardInfo.DeleteAllItems();
	m_dwOutputJs = 0;
	m_dwPortIndexJs = 0;
	m_dwLineNoPortCfg = 0;
	m_dwColumnNoPort = 0;
	m_dwWidthPortCfg = 0;
	m_dwHeightPortCfg = 0;
	m_iCurSelRecvCardInfo = -1;
	UpdateData(FALSE);
}

void CDlgLedConfig::OnButPortcfgSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	DWORD dwCount = m_lstOutput.GetItemCount();
	for (int i = 0; i < dwCount; i++)
	{
		m_struPortCfg[i].dwSize = sizeof(m_struPortCfg[i]);
	}
	if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_LED_PORT_CFG, dwCount,  m_dwOutputPortCfg, dwCount*sizeof(DWORD),\
		 m_status, m_struPortCfg, dwCount*sizeof(NET_DVR_LED_PORT_CFG)))
    {
        g_pMainDlg->AddLog(m_lDeviceID,OPERATION_FAIL_T, "NET_DVR_SET_LED_PORT_CFG");
        return;
    }
    g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_LED_PORT_CFG");
}

void CDlgLedConfig::OnBtnInputcfgGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LED_INPUT_CFG struInputCfg = {0};
	struInputCfg.dwSize = sizeof(struInputCfg);
	DWORD dwRet; 
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_INPUT_CFG, m_dwInputNo, &struInputCfg, sizeof(struInputCfg), &dwRet))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_LED_INPUT_CFG");
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_LED_INPUT_CFG");
	m_dwRefreshRate = struInputCfg.dwRefreshRate;
	m_dwResolutionHeight = struInputCfg.dwResolutionHeight;
	m_dwResolutionWidth = struInputCfg.dwResolutionWidth;
	m_dwVPosition = struInputCfg.struVgaCfg.byVerticalPosition;
	m_dwHPosition = struInputCfg.struVgaCfg.byHorizontalPosition;
	m_dwClock = struInputCfg.struVgaCfg.byClock;
	m_dwPhase = struInputCfg.struVgaCfg.byPhase;
	m_bAutoAjust = struInputCfg.struVgaCfg.byEnableAutoAdjust;
	UpdateData(FALSE);
}

void CDlgLedConfig::OnBtnInputcfgSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LED_INPUT_CFG struInputCfg = {0};
	struInputCfg.dwSize = sizeof(struInputCfg);
	struInputCfg.dwRefreshRate = m_dwRefreshRate;
	struInputCfg.dwResolutionHeight = m_dwResolutionHeight;
	struInputCfg.dwResolutionWidth = m_dwResolutionWidth;
	struInputCfg.struVgaCfg.byClock = m_dwClock;
	struInputCfg.struVgaCfg.byEnableAutoAdjust = m_bAutoAjust;
	struInputCfg.struVgaCfg.byHorizontalPosition = m_dwHPosition;
	struInputCfg.struVgaCfg.byPhase = m_dwPhase;
	struInputCfg.struVgaCfg.byVerticalPosition = m_dwVPosition;
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_LED_INPUT_CFG, m_dwInputNo, &struInputCfg, sizeof(struInputCfg)))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_SET_LED_INPUT_CFG");
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_LED_INPUT_CFG");
}

void CDlgLedConfig::OnBtnDisplayConfig() 
{
	// TODO: Add your control notification handler code here
	CDlgLedConfigDisplay dlg;
	dlg.Init(m_lUserID, m_lDeviceID);
	dlg.DoModal();
}

void CDlgLedConfig::OnBtnRecvcardConfig() 
{
	// TODO: Add your control notification handler code here
	CDlgLedConfigRecv dlg;
	dlg.Init(m_lUserID, m_lDeviceID);
	dlg.DoModal();
}

void CDlgLedConfig::OnButOutputPortModify() 
{
	// TODO: Add your control notification handler code here
	if (m_iCurSel == -1)
	{
		return;
	}
	UpdateData(TRUE); 
	CString csTmp; 
	csTmp.Format("%d", m_dwOutputPort);
	m_lstOutputPort.SetItemText(m_iCurSel, 1, csTmp); 
	m_lstOutputPort.SetItemData(m_iCurSel, m_dwOutputPort);
	UpdateData(FALSE);
}

void CDlgLedConfig::OnButOutputPortcfgMod() 
{
	// TODO: Add your control notification handler code here
	if (m_iCurSelOutputPortCfg == -1)
	{
		return;
	}
	UpdateData(TRUE);
	m_dwOutputPortCfg[m_iCurSelOutputPortCfg] = m_dwOutputPortCfgOne;
	m_struPortCfg[m_iCurSelOutputPortCfg].byEnabled = m_BPortCfgEnable;
	m_struPortCfg[m_iCurSelOutputPortCfg].struLedPortBackup.byEnabled = m_bBackupEnable;
	m_struPortCfg[m_iCurSelOutputPortCfg].struLedPortBackup.byPortMode = m_cmbPortMode.GetCurSel()+1;
	m_struPortCfg[m_iCurSelOutputPortCfg].struLedPortBackup.dwPairPort = m_dwPairPort;
	CString csTmp; 
	csTmp.Format("%d", m_dwOutputPortCfgOne); 
	m_lstOutput.SetItemText(m_iCurSelOutputPortCfg, 1, csTmp); 
	csTmp = (m_BPortCfgEnable)?"Yes":"No"; 
	m_lstOutput.SetItemText(m_iCurSelOutputPortCfg, 2, csTmp); 
	csTmp = (m_bBackupEnable)?"Yes":"No";
	m_lstOutput.SetItemText(m_iCurSelOutputPortCfg, 3, csTmp);
	csTmp = "";
	if (m_struPortCfg[m_iCurSelOutputPortCfg].struLedPortBackup.byPortMode == 1)
	{
		csTmp = "主口";
	}
	else if (m_struPortCfg[m_iCurSelOutputPortCfg].struLedPortBackup.byPortMode == 2)
	{
		csTmp = "备份口";
	}
	m_lstOutput.SetItemText(m_iCurSelOutputPortCfg, 4, csTmp);
	csTmp.Format("%d", m_dwPairPort);
	m_lstOutput.SetItemText(m_iCurSelOutputPortCfg, 5, csTmp);
	UpdateData(FALSE);
}


void CDlgLedConfig::OnBnClickedBtnCheck()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgLEDCheckCond dlg;
    dlg.DoModal();
}


void CDlgLedConfig::OnBnClickedBtnEnableGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CString strCommand;
    strCommand.Format("GET /ISAPI/LED/RecvCard/Operate/checkEnabled/%d\r\n", m_dwEnableID);
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();

    char szStatusBuff[1024] = { 0 };
    char szOutputXml[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpOutBuffer = szOutputXml;
    struOutputParam.dwOutBufferSize = 1024;
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    CheckEnabled struCheck;
    string stringCheck = (char*)struOutputParam.lpOutBuffer;
    TParseXmlDoc<CheckEnabled>(struCheck, stringCheck.c_str(), "CheckEnabled");

    m_bCheckEnable = struCheck.bEnabled;
    m_dwEnableID = struCheck.iId;
    UpdateData(FALSE);
}


void CDlgLedConfig::OnBnClickedBtnEnableSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CheckEnabled struCheck;
    struCheck.bEnabled = m_bCheckEnable;
    struCheck.iId = m_dwEnableID;
    string stringCkeck;
    stringCkeck = TGenXmlDoc<CheckEnabled>(struCheck, "V2.0");

    CString strCommand;
    strCommand.Format("PUT /ISAPI/LED/RecvCard/Operate/checkEnabled/%d\r\n", struCheck.iId);
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
    struInputParam.lpInBuffer = (void*)stringCkeck.c_str();
    struInputParam.dwInBufferSize = stringCkeck.length();

    NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = { 0 };
    char szXMLStatus[1024] = { 0 };
    memset(szXMLStatus, 0, 1024);
    struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
    struXMLCfgOutput.lpOutBuffer = NULL;
    struXMLCfgOutput.dwOutBufferSize = 0;
    struXMLCfgOutput.lpStatusBuffer = szXMLStatus;
    struXMLCfgOutput.dwStatusSize = 1024;


    if (NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struXMLCfgOutput))
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
    }
}


void CDlgLedConfig::OnBnClickedBtnBrosepicpath()
{
	// TODO:  在此添加控件通知处理程序代码
	static char szFilter[] = "All File(*.*)|*.*||";
	UpdateData(TRUE);
	CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, szFilter);
	dlg.m_pOFN->lpstrTitle = _T("请选择需要上传的文件");
	dlg.m_pOFN->nMaxFile = MAX_COUNT * MAX_PATH;
	dlg.m_pOFN->lpstrFile = new TCHAR[dlg.m_ofn.nMaxFile];
	ZeroMemory(dlg.m_pOFN->lpstrFile, sizeof(TCHAR)*dlg.m_ofn.nMaxFile);
	int i = 0;
	int j = 0;
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();
		while(NULL != pos)
		{		
			m_filePathSel[i] = dlg.GetNextPathName(pos);
			i++;
		}
		for (i = 0; i < MAX_COUNT; i++)
		{
			if (m_filePathOld[i] == "\0")
			{
				m_filePathOld[i] = m_filePathSel[j];
				if (m_filePathSel[j] == "\0")
				{
					break;
				}
				m_filePathSel[j] = "";
				j++;
			}
		}
	}
	delete dlg.m_pOFN->lpstrFile;
	RefreshList();
	UpdateData(FALSE);
}

void CDlgLedConfig::RefreshList()
{
	int index = 0;
	int i = 0;
	ZeroMemory(m_fileNo, MAX_COUNT);
	for (index = 0; index < MAX_COUNT; index++)
	{
		m_filePathNew[index] = "\0";
		if (m_filePathOld[index] != "\0")
		{
			m_filePathNew[i] = m_filePathOld[index];
			m_fileNo[i] = i + 1;
			i++;
		}
	}
	
	for (index = 0; index < MAX_COUNT; index++)
	{
		m_filePathOld[index] = m_filePathNew[index];
	}

	index = 0;
	m_ListLedPic.DeleteAllItems();
	while (m_filePathNew[index] != "\0")
	{
		m_ListLedPic.InsertItem(index, NULL);
		CString csTmp;
		csTmp.Format("%d", m_fileNo[index]);
		m_ListLedPic.SetItemText(index, 0, csTmp);
		m_ListLedPic.SetItemText(index, 1, m_filePathNew[index]);
		index++;
	}
}

void CDlgLedConfig::OnBnClickedButDelLedPic()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	POSITION pos;
 	pos = m_ListLedPic.GetFirstSelectedItemPosition();
	while(NULL != pos)
	{
		int selItem = m_ListLedPic.GetNextSelectedItem(pos);
		m_ListLedPic.DeleteItem(selItem);
		m_filePathOld[selItem] = "\0";
	}
	RefreshList();
	UpdateData(FALSE);
}
void CDlgLedConfig::OnBnClickedBtnUploadledpic()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CString csErr;
	char szLan[128] = { 0 };
	m_ProUploadLedPic.SetPos(0);
	BYTE byPicType = 0;
	int i = 0;

	while (1)   //一张图片一次循环
	{			
			CString strFileName = m_filePathNew[i];
			if ("\0" == strFileName)
			{
				break;
			}
			if (strFileName.Find(".jpg") != -1 || strFileName.Find(".JPG") != -1)
			{
				byPicType = 1;
			}
			else if (strFileName.Find(".bmp") != -1 || strFileName.Find(".BMP") != -1)
			{
				byPicType = 2;
			}
			else if (strFileName.Find(".png") != -1 || strFileName.Find(".PNG") != -1)
			{
				byPicType = 3;
			}
			else
			{
				continue;
			}
			BOOL bStatus = UploadLedPic(strFileName, byPicType, i);
			UpdateData(FALSE);
			i++;
			if (i > MAX_COUNT)
			{
				i = MAX_COUNT;
			}
	}
	UpdateData(FALSE);
}

BOOL CDlgLedConfig::UploadLedPic(CString csFileName, BYTE byPicType, int listIndex)
{
	
	CFile cFile;
	char szFileName[MAX_PATH];
	CString csErr;
	char szLan[256] = { 0 };

	if (!cFile.Open(csFileName, CFile::modeRead))
	{
		g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
		AfxMessageBox(szLan);
		return FALSE;
	}
	DWORD dwFileSize = (DWORD)cFile.GetLength();
	if (dwFileSize == 0)
	{
		g_StringLanType(szLan, "配置文件为空", "Configure file is empty");
		AfxMessageBox(szLan);
	}

	memset(&m_struPicInfo, 0, sizeof(m_struPicInfo));
	m_struPicInfo.dwSize = sizeof(m_struPicInfo);
	m_struPicInfo.byPictureType = byPicType;
	m_struPicInfo.dwPicMangeNo = m_fileNo[listIndex];
	strncpy((char*)&m_struPicInfo.sPicName[0], csFileName, sizeof(m_struPicInfo.sPicName));

	m_pPicInfo = new char[dwFileSize];
	cFile.Read(m_pPicInfo, dwFileSize);
	m_struPicInfo.sPictureBuffer = m_pPicInfo;
	m_struPicInfo.dwPictureLength = dwFileSize;
	cFile.Close();
	m_lUploadLedPicHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_PICTURE_FILE, &m_struPicInfo, sizeof(m_struPicInfo), NULL, NULL, 0);
	if (m_lUploadLedPicHandle < 0)
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "UPLOAD_PICTURE_FILE");
		csErr.Format("上传失败, filename[%s], fileNo[%d], ErrCode[%d]", csFileName, m_fileNo[listIndex], NET_DVR_GetLastError());
		AfxMessageBox(csErr);
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "UPLOAD_PICTURE_FILE");
	}


	DWORD dwProgress = 0;
	int iStatus = -1;
	char szStatus[256] = { 0 };
	BOOL bRet = FALSE;
	CString	csTmp;
	while (1)
	{
		memset(szStatus, 0, 256);
		iStatus = NET_DVR_GetUploadState(m_lUploadLedPicHandle, &dwProgress);
		if (iStatus == -1)  //即入口返回失败
		{
			g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GetUploadState");
			sprintf(szStatus, "%d%%",dwProgress);
			SetDlgItemText(IDC_STATIC_UPPROGRESS, szStatus);
			csTmp.Format("fail");
			m_ListLedPic.SetItemText(listIndex, 2, csTmp);
			//Sleep(100);
			bRet = FALSE;
			break;
		}
		else if (iStatus == 2) //正在上传
		{
			m_ProUploadLedPic.SetPos(dwProgress);
			sprintf(szStatus, "%d%%",dwProgress);
			SetDlgItemText(IDC_STATIC_UPPROGRESS, szStatus);
			csTmp.Format("uploading");
			m_ListLedPic.SetItemText(listIndex, 2, csTmp);
			Sleep(100);
			continue;
		}
		else if (iStatus == 1) //上传成功
		{
			sprintf(szStatus, "%d%%", dwProgress);
			SetDlgItemText(IDC_STATIC_UPPROGRESS, szStatus);
			csTmp.Format("success fileNo[%d]", m_fileNo[listIndex]);
			m_ListLedPic.SetItemText(listIndex, 2, csTmp);
			Sleep(100);
			bRet = TRUE;
			break;
		}
		else //上传失败,显示状态
		{
			sprintf(szStatus, "%d%%", dwProgress);
			SetDlgItemText(IDC_STATIC_UPPROGRESS, szStatus);
			csTmp.Format("fail");
			m_ListLedPic.SetItemText(listIndex, 2, csTmp);
			Sleep(100);
			bRet = FALSE;
			break;
		}
	}
	return bRet;
}


extern HWND g_Hwnd;
void CDlgLedConfig::OnBnClickedButton1()
{
	LEDScreenAdjust dlg;
	dlg.Init(m_lUserID, m_lDeviceID);
	dlg.DoModal();
	HWND hwnd1 = dlg.GetSafeHwnd();
	HWND hwnd2 = this->GetSafeHwnd();
}
