// DlgITSOverlapCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITSOverlapCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITSOverlapCfg dialog


CDlgITSOverlapCfg::CDlgITSOverlapCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITSOverlapCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITSOverlapCfg)
	m_bChkColorAdapt = FALSE;
	m_bChkEnable = FALSE;
	m_dwBackColorRGB = 0;
	m_csCameraNum = _T("");
	m_byChangeLineNum = 0;
	m_dwCharInterval = 0;
	m_csDirection = _T("");
	m_csDirectionInfo = _T("");
	m_dwForeColorRGB = 0;
	m_csInstrumentNum = _T("");
	m_csLaneInfo = _T("");
	m_dwItemLength = 0;
	m_dwLinePercent = 0;
	m_csMonitor1Info = _T("");
	m_csMonitor2Info = _T("");
	m_csRoadNum = _T("");
	m_csSite = _T("");
	m_bySpaceNum = 0;
	m_dwStartLeftPos = 0;
	m_dwStartTopPos = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
	m_lChannel = -1;
	m_dwOverlapSel = 0;
	memset(&m_struOverlap, 0, sizeof(m_struOverlap));
}


void CDlgITSOverlapCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITSOverlapCfg)
	DDX_Control(pDX, IDC_COMBO_RELATE_TYPE, m_comRelateType);
	DDX_Control(pDX, IDC_COMBO_SCENE_ID, m_comSceneID);
	DDX_Control(pDX, IDC_COMBO_PIC_MODE, m_comPicMode);
	DDX_Control(pDX, IDC_COMBO_OVERLAP_TYPE, m_comboOverlapType);
	DDX_Control(pDX, IDC_COMBO_OVERLAP_NO, m_comboOverlapNO);
	DDX_Control(pDX, IDC_COMBO_ITEM_STLYE, m_comboItemStlye);
	DDX_Control(pDX, IDC_COMBO_CONFIG_MODE, m_comboConfigMode);
	DDX_Control(pDX, IDC_COMBO_CHAR_STLYE, m_comboCharStlye);
	DDX_Control(pDX, IDC_COMBO_CHAR_SIZE, m_comboCharSize);
	DDX_Check(pDX, IDC_CHK_COLOR_ADAPT, m_bChkColorAdapt);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bChkEnable);
	DDX_Text(pDX, IDC_EDIT_BACK_COLOR_RGB, m_dwBackColorRGB);
	DDX_Text(pDX, IDC_EDIT_CAMERA_NUM, m_csCameraNum);
	DDX_Text(pDX, IDC_EDIT_CHANGELINE_NUM, m_byChangeLineNum);
	DDX_Text(pDX, IDC_EDIT_CHAR_INTERVAL, m_dwCharInterval);
	DDX_Text(pDX, IDC_EDIT_DIRECTION, m_csDirection);
	DDX_Text(pDX, IDC_EDIT_DIRECTION_INFO, m_csDirectionInfo);
	DDX_Text(pDX, IDC_EDIT_FORE_COLOR_RGB, m_dwForeColorRGB);
	DDX_Text(pDX, IDC_EDIT_INSTRUMENT_NUM, m_csInstrumentNum);
	DDX_Text(pDX, IDC_EDIT_LANE_INFO, m_csLaneInfo);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_dwItemLength);
	DDX_Text(pDX, IDC_EDIT_LINE_PERCENT, m_dwLinePercent);
	DDX_Text(pDX, IDC_EDIT_MONITOR1_INFO, m_csMonitor1Info);
	DDX_Text(pDX, IDC_EDIT_MONITOR2_INFO, m_csMonitor2Info);
	DDX_Text(pDX, IDC_EDIT_ROAD_NUM, m_csRoadNum);
	DDX_Text(pDX, IDC_EDIT_SITE, m_csSite);
	DDX_Text(pDX, IDC_EDIT_SPACE_NUM, m_bySpaceNum);
	DDX_Text(pDX, IDC_EDIT_START_LEFTPOS, m_dwStartLeftPos);
	DDX_Text(pDX, IDC_EDIT_START_TOPPOS, m_dwStartTopPos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITSOverlapCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgITSOverlapCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SURE, OnBtnSure)
	ON_CBN_SELCHANGE(IDC_COMBO_OVERLAP_NO, OnSelchangeComboOverlapNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITSOverlapCfg message handlers
BOOL CDlgITSOverlapCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString tmp;
	m_comboOverlapNO.ResetContent();
	for (int i=0; i<MAX_OVERLAP_ITEM_NUM; i++)
	{
		tmp.Format("%d", i+1);
		m_comboOverlapNO.AddString(tmp);
	}

	return TRUE;
}

void CDlgITSOverlapCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwStatus = 0;
	DWORD dwChanShow = 0;//display channel number
//	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	
	if (m_iDevIndex == -1)
	{
		return;
	}
// 	STRU_CHANNEL_INFO *pChannelInfo = &(g_struDeviceInfo[m_iDevIndex].struChanInfo[m_lChannel]);
// 	if (pChannelInfo->iChanIndex < 0)
// 	{
// 		return;
// 	}
// 	
// 	dwChanShow = pChannelInfo->iChannelNO;

// 	if (!g_struDeviceInfo[m_iDevIndex].struChanInfo[m_lChannel].bEnable)
// 	{
// 		return;
// 	}

	char szLan[129] = {0};
	NET_ITS_OVERLAPCFG_COND struCond = {0};
	struCond.dwSize = sizeof(struCond);
	struCond.dwChannel = m_lChannel;
	struCond.dwConfigMode = m_comboConfigMode.GetCurSel();
	struCond.byPicModeType = m_comPicMode.GetCurSel();
	struCond.byRelateType = m_comRelateType.GetCurSel();

	BOOL bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_ITS_GET_OVERLAP_CFG, 1, &struCond,sizeof(struCond),&dwStatus, &m_struOverlap, sizeof(m_struOverlap));
	
	if (!(bRet && (0 == dwStatus)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITS_GET_OVERLAP_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITS_GET_OVERLAP_CFG");
	}

	m_dwOverlapSel = 0;
	m_comboOverlapNO.SetCurSel(0);
	m_bChkEnable = m_struOverlap.byEnable;
//	m_comSceneID.SetCurSel(m_struOverlap.byDetSceneID);
//	m_dwItemLength = m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].wItemLen;
	m_comboOverlapType.SetCurSel(m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].byItemType-1);
	m_byChangeLineNum = m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].byChangeLineNum;
	m_bySpaceNum = m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].bySpaceNum;
	m_dwLinePercent = m_struOverlap.struOverLapItem.dwLinePercent;
	m_comboItemStlye.SetCurSel(m_struOverlap.struOverLapItem.dwItemsStlye);
	m_dwStartLeftPos = m_struOverlap.struOverLapItem.wStartPosLeft;
	m_dwStartTopPos = m_struOverlap.struOverLapItem.wStartPosTop;
	m_comboCharStlye.SetCurSel(m_struOverlap.struOverLapItem.wCharStyle);
	m_comboCharSize.SetCurSel(m_struOverlap.struOverLapItem.wCharSize);
	m_dwCharInterval = m_struOverlap.struOverLapItem.wCharInterval;
	m_dwForeColorRGB = m_struOverlap.struOverLapItem.dwForeClorRGB;
	m_dwBackColorRGB = m_struOverlap.struOverLapItem.dwBackClorRGB;
	m_bChkColorAdapt = m_struOverlap.struOverLapItem.byColorAdapt;

	memcpy(szLan, m_struOverlap.struOverLapInfo.bySite, 128);
	m_csSite.Format("%s",szLan);
	memset(szLan, 0, 129);
	memcpy(szLan, m_struOverlap.struOverLapInfo.byRoadNum,32);
	m_csRoadNum.Format("%s",szLan);
	memset(szLan, 0, 129);
	memcpy(szLan,m_struOverlap.struOverLapInfo.byInstrumentNum,32);
	m_csInstrumentNum.Format("%s",szLan);
	memset(szLan,0, 129);
	memcpy(szLan,m_struOverlap.struOverLapInfo.byDirection,32);
	m_csDirection.Format("%s", szLan);
	memset(szLan, 0, 129);
	memcpy(szLan, m_struOverlap.struOverLapInfo.byDirectionDesc, 32);
	m_csDirectionInfo.Format("%s", szLan);
	memset(szLan, 0, 129);
	memcpy(szLan, m_struOverlap.struOverLapInfo.byLaneDes,32);
	m_csLaneInfo.Format("%s",szLan);
//	memset(szLan, 0, 129);
//	memcpy(szLan,m_struOverlap.struOverLapInfo.byCameraNum, 32);
//	m_csCameraNum.Format("%s", szLan);
	memset(szLan,0,129);
	memcpy(szLan,m_struOverlap.struOverLapInfo.byMonitoringSite1,44);
	m_csMonitor1Info.Format("%s", szLan);
	memset(szLan, 0,129);
	memcpy(szLan,m_struOverlap.struOverLapInfo.byMonitoringSite2,32);
	m_csMonitor2Info.Format("%s",szLan);
	
	UpdateData(FALSE);
}

void CDlgITSOverlapCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwStatus = 0;
	NET_ITS_OVERLAPCFG_COND struCond = {0};
	struCond.dwSize = sizeof(struCond);
	struCond.dwChannel = m_lChannel;
	struCond.dwConfigMode = m_comboConfigMode.GetCurSel();
	struCond.byPicModeType = m_comPicMode.GetCurSel();
	struCond.byRelateType = m_comRelateType.GetCurSel();

	m_struOverlap.byEnable = m_bChkEnable;
	m_struOverlap.struOverLapItem.dwLinePercent = m_dwLinePercent;
	m_struOverlap.struOverLapItem.dwItemsStlye = m_comboItemStlye.GetCurSel();
	m_struOverlap.struOverLapItem.wStartPosLeft = m_dwStartLeftPos;
	m_struOverlap.struOverLapItem.wStartPosTop = m_dwStartTopPos;
	m_struOverlap.struOverLapItem.wCharStyle = m_comboCharStlye.GetCurSel();
	m_struOverlap.struOverLapItem.wCharSize = m_comboCharSize.GetCurSel();
	m_struOverlap.struOverLapItem.wCharInterval = m_dwCharInterval;
	m_struOverlap.struOverLapItem.dwForeClorRGB = m_dwForeColorRGB;
	m_struOverlap.struOverLapItem.dwBackClorRGB = m_dwBackColorRGB;
	m_struOverlap.struOverLapItem.byColorAdapt = m_bChkColorAdapt;

	memcpy(m_struOverlap.struOverLapInfo.bySite, m_csSite, 128);
	memcpy(m_struOverlap.struOverLapInfo.byRoadNum, m_csRoadNum, 32);
	memcpy(m_struOverlap.struOverLapInfo.byInstrumentNum, m_csInstrumentNum, 32);
	memcpy(m_struOverlap.struOverLapInfo.byDirection, m_csDirection, 32);
	memcpy(m_struOverlap.struOverLapInfo.byDirectionDesc, m_csDirectionInfo, 32);
	memcpy(m_struOverlap.struOverLapInfo.byLaneDes, m_csLaneInfo, 32);
//	memcpy(m_struOverlap.struOverLapInfo.byCameraNum, m_csCameraNum, 32);
	memcpy(m_struOverlap.struOverLapInfo.byMonitoringSite1, m_csMonitor1Info, 44);
	memcpy(m_struOverlap.struOverLapInfo.byMonitoringSite2, m_csMonitor2Info, 32);
	m_struOverlap.dwSize = sizeof(m_struOverlap);
	BOOL bRet = NET_DVR_SetDeviceConfig(m_lServerID, NET_ITS_SET_OVERLAP_CFG, 1, &struCond,sizeof(struCond),&dwStatus, &m_struOverlap, sizeof(m_struOverlap));
	
	if (!(bRet && (0 == dwStatus)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITS_SET_OVERLAP_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITS_SET_OVERLAP_CFG");
	}
}

void CDlgITSOverlapCfg::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwOverlapSel = m_comboOverlapNO.GetCurSel();
//	m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].wItemLen = m_dwItemLength;
	m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].byChangeLineNum = m_byChangeLineNum;
	m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].bySpaceNum = m_bySpaceNum;
	m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].byItemType = m_comboOverlapType.GetCurSel()+1;
}

void CDlgITSOverlapCfg::OnSelchangeComboOverlapNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwOverlapSel = m_comboOverlapNO.GetCurSel();
//	m_dwItemLength = m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].wItemLen;
	m_byChangeLineNum = m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].byChangeLineNum;
	m_bySpaceNum = m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].bySpaceNum;
	m_comboOverlapType.SetCurSel(m_struOverlap.struOverLapItem.struSingleItem[m_dwOverlapSel].byItemType-1);

	UpdateData(FALSE);
}
