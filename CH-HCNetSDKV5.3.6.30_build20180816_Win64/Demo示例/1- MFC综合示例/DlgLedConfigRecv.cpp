// DlgLedConfigRecv.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLedConfigRecv.h"
#include "DlgLEDVersion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLedConfigRecv dialog


CDlgLedConfigRecv::CDlgLedConfigRecv(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLedConfigRecv::IDD, pParent)
    , m_byDummyGClockHighTime(0)
    , m_byFirstGClockExtendedTime(0)
    , m_byDummyGClockCycle(0)
    , m_byEnabledExGradientOptimition(FALSE)
    , m_byChip4High(0)
    , m_byChip4Low(0)
    , m_byChip5High(0)
    , m_byChip5Low(0)
    , m_byChip6High(0)
    , m_byChip6Low(0)
{
	//{{AFX_DATA_INIT(CDlgLedConfigRecv)
	m_bEnableGrayUniformity = FALSE;
	m_bEnableHGrayStripes = FALSE;
	m_bClearBadPoint = FALSE;
	m_bGhostShadowEhancedMode1 = FALSE;
	m_bGhostShadowEhancedMode2 = FALSE;
	m_bEnableSelfdefineRegistor = FALSE;
	m_dwAfterGlowCtrl = 0;
	m_dwDClkPhase = 0;
	m_dwDClkRate = 0;
	m_dwEndCol = 0;
	m_dwEndRow = 0;
	m_dwGClkCountNum = 0;
	m_dwGClkNum = 0;
	m_dwGClkRate = 0;
	m_dwHBlank = 0;
	m_dwLineFeedTime = 0;
	m_dwLineScanNum = 0;
	m_dwOutputNo = 0;
	m_dwRefreshCompleteGrayNum = 0;
	m_dwRefreshRate = 0;
	m_dwStartCol = 0;
	m_dwStartRow = 0;
	m_dwGammaEndCol = 0;
	m_dwGammaEndRow = 0;
	m_dwGammaOutputNo = 0;
	m_dwGammaStartCol = 0;
	m_dwGammaStartRow = 0;
	m_dwGammaY = 0;
	m_dwChip1High = 0;
	m_dwChip1Low = 0;
	m_dwChip2High = 0;
	m_dwChip2Low = 0;
	m_dwChip3High = 0;
	m_dwChip3Low = 0;
	m_dwElimanateShadowy = 0;
	m_dwElimanateGhostShadowLevel = 0;
	m_dwGrayEqualize1 = 0;
	m_dwGrayEqualize2 = 0;
	m_strDClkDutyRadio = _T("");
	m_strGrayLevel = _T("");
	m_dwHighEndCol = 0;
	m_dwHighEndRow = 0;
	m_dwHighOutputNo = 0;
	m_dwHighStartCol = 0;
	m_dwHighStartRow = 0;
	//}}AFX_DATA_INIT
	m_iCurIndex = -1;
	m_lpRegistor = NULL;
	memset(&m_struGammaCfg, 0, sizeof(m_struGammaCfg));
	memset(&m_struAdvancedCfg, 0, sizeof(m_struAdvancedCfg));
}


void CDlgLedConfigRecv::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgLedConfigRecv)
    DDX_Control(pDX, IDC_LIST_GAMMA_Y, m_listGammaY);
    DDX_Control(pDX, IDC_COMBO_GROUP_NO, m_cmbGroupNo);
    DDX_Control(pDX, IDC_COMBO_BASIC_GRAY_LEVEL, m_cmbGrayLevel);
    DDX_Control(pDX, IDC_COMBO_BASIC_DCLK_DUTY_RADIO, m_cmbDClkDutyRadio);
    DDX_Check(pDX, IDC_CHK_GRAY_UNIFORMITY_ENABLE, m_bEnableGrayUniformity);
    DDX_Check(pDX, IDC_CHK_HGRAY_STRIPES_ENABLE, m_bEnableHGrayStripes);
    DDX_Check(pDX, IDC_CHK_HIGH_CLEAR_BAD_POINT, m_bClearBadPoint);
    DDX_Check(pDX, IDC_CHK_HIGH_GHOST_SHADOW_ENHANCED_MODE1, m_bGhostShadowEhancedMode1);
    DDX_Check(pDX, IDC_CHK_HIGH_GHOST_SHADOW_ENHANCED_MODE2, m_bGhostShadowEhancedMode2);
    DDX_Check(pDX, IDC_CHK_SELFDEFINE_REGISTOR_ENABLE, m_bEnableSelfdefineRegistor);
    DDX_Text(pDX, IDC_EDIT_BASIC_AFTER_GLOW_CTRL, m_dwAfterGlowCtrl);
    DDX_Text(pDX, IDC_EDIT_BASIC_DCLK_PHASE, m_dwDClkPhase);
    DDX_Text(pDX, IDC_EDIT_BASIC_DCLKRATE, m_dwDClkRate);
    DDX_Text(pDX, IDC_EDIT_BASIC_END_COL, m_dwEndCol);
    DDX_Text(pDX, IDC_EDIT_BASIC_END_ROW, m_dwEndRow);
    DDX_Text(pDX, IDC_EDIT_BASIC_GCLK_COUNTNUM, m_dwGClkCountNum);
    DDX_Text(pDX, IDC_EDIT_BASIC_GCLK_NUM, m_dwGClkNum);
    DDX_Text(pDX, IDC_EDIT_BASIC_GCLKRATE, m_dwGClkRate);
    DDX_Text(pDX, IDC_EDIT_BASIC_HBLANK, m_dwHBlank);
    DDX_Text(pDX, IDC_EDIT_BASIC_LINE_FEED_TIME, m_dwLineFeedTime);
    DDX_Text(pDX, IDC_EDIT_BASIC_LINE_SCAN_NUM, m_dwLineScanNum);
    DDX_Text(pDX, IDC_EDIT_BASIC_OUTPUTNO, m_dwOutputNo);
    DDX_Text(pDX, IDC_EDIT_BASIC_REFRESH_COMPLETE_GRAY_NUM, m_dwRefreshCompleteGrayNum);
    DDX_Text(pDX, IDC_EDIT_BASIC_REFRESH_RATE, m_dwRefreshRate);
    DDX_Text(pDX, IDC_EDIT_BASIC_START_COL, m_dwStartCol);
    DDX_Text(pDX, IDC_EDIT_BASIC_START_ROW, m_dwStartRow);
    DDX_Text(pDX, IDC_EDIT_GAMMA_END_COL, m_dwGammaEndCol);
    DDX_Text(pDX, IDC_EDIT_GAMMA_END_ROW, m_dwGammaEndRow);
    DDX_Text(pDX, IDC_EDIT_GAMMA_OUTPUTNO, m_dwGammaOutputNo);
    DDX_Text(pDX, IDC_EDIT_GAMMA_START_COL, m_dwGammaStartCol);
    DDX_Text(pDX, IDC_EDIT_GAMMA_START_ROW, m_dwGammaStartRow);
    DDX_Text(pDX, IDC_EDIT_GAMMA_Y, m_dwGammaY);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP1_HIGH, m_dwChip1High);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP1_LOW, m_dwChip1Low);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP2_HIGH, m_dwChip2High);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP2_LOW, m_dwChip2Low);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP3_HIGH, m_dwChip3High);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP3_LOW, m_dwChip3Low);
    DDX_Text(pDX, IDC_EDIT_HIGH_ELIMANATE_SHADOWY, m_dwElimanateShadowy);
    DDX_Text(pDX, IDC_EDIT_HIGH_ELIMINATE_GHOST_SHADOW_LEVEL, m_dwElimanateGhostShadowLevel);
    DDX_Text(pDX, IDC_EDIT_HIGH_GRAY_EQUALIZE1, m_dwGrayEqualize1);
    DDX_Text(pDX, IDC_EDIT_HIGH_GRAY_EQUALIZE2, m_dwGrayEqualize2);
    DDX_CBString(pDX, IDC_COMBO_BASIC_DCLK_DUTY_RADIO, m_strDClkDutyRadio);
    DDX_CBString(pDX, IDC_COMBO_BASIC_GRAY_LEVEL, m_strGrayLevel);
    DDX_Text(pDX, IDC_EDIT_HIGH_END_COL, m_dwHighEndCol);
    DDX_Text(pDX, IDC_EDIT_HIGH_END_ROW, m_dwHighEndRow);
    DDX_Text(pDX, IDC_EDIT_HIGH_OUTPUTNO, m_dwHighOutputNo);
    DDX_Text(pDX, IDC_EDIT_HIGH_START_COL, m_dwHighStartCol);
    DDX_Text(pDX, IDC_EDIT_HIGH_START_ROW, m_dwHighStartRow);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_GAMMATABTYPE, m_byGammaType);
    DDX_Control(pDX, IDC_COMBO_GAMMA_MODEL, m_byGammaModel);
    DDX_Text(pDX, IDC_EDIT_HIGH_CLOCK_TIME, m_byDummyGClockHighTime);
    DDX_Text(pDX, IDC_EDIT_FIRST_EXTEND_TIME, m_byFirstGClockExtendedTime);
    DDX_Text(pDX, IDC_EDIT_DUMMY_GCLOCK, m_byDummyGClockCycle);
    DDX_Check(pDX, IDC_CHK_GRANDIENT_OPTION, m_byEnabledExGradientOptimition);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP4_HIGH, m_byChip4High);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP4_LOW, m_byChip4Low);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP5_HIGH, m_byChip5High);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP5_LOW, m_byChip5Low);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP6_HIGH, m_byChip6High);
    DDX_Text(pDX, IDC_EDIT_HIGH_CHIP6_LOW, m_byChip6Low);
}


BEGIN_MESSAGE_MAP(CDlgLedConfigRecv, CDialog)
	//{{AFX_MSG_MAP(CDlgLedConfigRecv)
	ON_BN_CLICKED(IDC_BTN_BASIC_GET, OnBtnBasicGet)
	ON_BN_CLICKED(IDC_BTN_BASIC_SET, OnBtnBasicSet)
	ON_BN_CLICKED(IDC_BTN_GAMMA_GET, OnBtnGammaGet)
	ON_BN_CLICKED(IDC_BTN_GAMMA_MODIFY, OnBtnGammaModify)
	ON_BN_CLICKED(IDC_BTN_GAMMA_SET, OnBtnGammaSet)
	ON_BN_CLICKED(IDC_BTN_HIGH_GET, OnBtnHighGet)
	ON_BN_CLICKED(IDC_BTN_HIGH_SET, OnBtnHighSet)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP_NO, OnSelchangeComboGroupNo)
	ON_NOTIFY(NM_CLICK, IDC_LIST_GAMMA_Y, OnClickListGammaY)
	ON_BN_CLICKED(IDC_BTN_HIGH_OK, OnBtnHighOk)
	ON_BN_CLICKED(IDC_BTN_SAVE_CONFIGURATION, OnBtnSaveConfiguration)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_VERSION, &CDlgLedConfigRecv::OnBnClickedBtnVersion)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLedConfigRecv message handlers
void CDlgLedConfigRecv::UpdateCammaTable()
{
	m_listGammaY.DeleteAllItems();
	for (int iIndex = 0; iIndex < MAX_GAMMA_X_VALUE; iIndex++)
	{
		m_listGammaY.InsertItem(iIndex, "");
		CString str;
		str.Format("%d", iIndex);
		m_listGammaY.SetItemText(iIndex, 0, str);
		str.Format("%d", m_struGammaCfg.wGammaValue[iIndex]);
		m_listGammaY.SetItemText(iIndex, 1, str);
		m_listGammaY.SetItemData(iIndex, m_struGammaCfg.wGammaValue[iIndex]);
	}
}

BOOL CDlgLedConfigRecv::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szLan[128]; 
	m_listGammaY.SetExtendedStyle(m_listGammaY.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	g_StringLanType(szLan, "RGB输入X", "X");
	m_listGammaY.InsertColumn(0, szLan, LVCFMT_LEFT, 60);
	g_StringLanType(szLan, "屏幕输出Y", "Y");
	m_listGammaY.InsertColumn(1, szLan, LVCFMT_LEFT, 70);
    m_byGammaType.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLedConfigRecv::OnBtnBasicGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LED_RECV_CFG struRecvCfg;
	memset(&struRecvCfg, 0, sizeof(struRecvCfg));
	struRecvCfg.dwSize = sizeof(struRecvCfg);
	NET_DVR_LED_RECV_CARD_CFG_COND struCfgCond;
	memset(&struCfgCond, 0, sizeof(struCfgCond));
	struCfgCond.dwSize = sizeof(struCfgCond);
	struCfgCond.dwOutputNo = m_dwGammaOutputNo;
	struCfgCond.struPosStart.wColumn = m_dwStartCol;
	struCfgCond.struPosStart.wLine = m_dwStartRow;
	struCfgCond.struPosEnd.wColumn = m_dwEndCol;
	struCfgCond.struPosEnd.wLine = m_dwEndRow;
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_LED_RECV_CFG, 1, &struCfgCond, sizeof(struCfgCond), NULL, &struRecvCfg, sizeof(struRecvCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_RECV_CFG");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_RECV_CFG");
	CString str;
	str.Format("%d", struRecvCfg.byGrayLevel);
	m_strGrayLevel = str;
	m_dwLineScanNum = struRecvCfg.byLineScanNum;
	m_dwRefreshCompleteGrayNum = struRecvCfg.byRefreshCompleteGrayNum;
	m_dwRefreshRate = struRecvCfg.byRefreshRate;
	m_dwAfterGlowCtrl = struRecvCfg.dwAfterglowCtrl;
	m_dwHBlank = struRecvCfg.dwHBlank;
	m_dwLineFeedTime = struRecvCfg.dwLineFeedTime;
	str.Format("%d", struRecvCfg.struClockCfg.byDclkDutyRatio);
	m_strDClkDutyRadio = str;
	m_dwDClkPhase = struRecvCfg.struClockCfg.byDclkPhase;
	m_dwGClkNum = struRecvCfg.struClockCfg.byGclkNum;
	m_dwDClkRate = struRecvCfg.struClockCfg.dwDclkRate;
	m_dwGClkCountNum = struRecvCfg.struClockCfg.dwGclkCountNum;
	m_dwGClkRate = struRecvCfg.struClockCfg.dwGclkRate;
	UpdateData(FALSE);
}

void CDlgLedConfigRecv::OnBtnBasicSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LED_RECV_CFG struRecvCfg;
	memset(&struRecvCfg, 0, sizeof(struRecvCfg));
	struRecvCfg.dwSize = sizeof(struRecvCfg);
	NET_DVR_LED_RECV_CARD_CFG_COND struCfgCond;
	memset(&struCfgCond, 0, sizeof(struCfgCond));
	struCfgCond.dwSize = sizeof(struCfgCond);
	struCfgCond.dwOutputNo = m_dwGammaOutputNo;
	struCfgCond.struPosStart.wColumn = m_dwStartCol;
	struCfgCond.struPosStart.wLine = m_dwStartRow;
	struCfgCond.struPosEnd.wColumn = m_dwEndCol;
	struCfgCond.struPosEnd.wLine = m_dwEndRow;

	struRecvCfg.byGrayLevel = atoi(m_strGrayLevel);
	struRecvCfg.byLineScanNum = m_dwLineScanNum;
	struRecvCfg.byRefreshCompleteGrayNum = m_dwRefreshCompleteGrayNum;
	struRecvCfg.byRefreshRate = m_dwRefreshRate;
	struRecvCfg.dwAfterglowCtrl = m_dwAfterGlowCtrl;
	struRecvCfg.dwHBlank = m_dwHBlank;
	struRecvCfg.dwLineFeedTime = m_dwLineFeedTime;
	struRecvCfg.struClockCfg.byDclkDutyRatio = atoi(m_strDClkDutyRadio);
	struRecvCfg.struClockCfg.byDclkPhase = m_dwDClkPhase;
	struRecvCfg.struClockCfg.byGclkNum = m_dwGClkNum;
	struRecvCfg.struClockCfg.dwDclkRate = m_dwDClkRate;
	struRecvCfg.struClockCfg.dwGclkCountNum = m_dwGClkCountNum;
	struRecvCfg.struClockCfg.dwGclkRate = m_dwGClkRate;

	if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_LED_RECV_CFG, 1, &struCfgCond, sizeof(struCfgCond), NULL, &struRecvCfg, sizeof(struRecvCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_RECV_CFG");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_RECV_CFG");
}

void CDlgLedConfigRecv::OnBtnGammaGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struGammaCfg, 0, sizeof(m_struGammaCfg));
	m_struGammaCfg.byGammaModel = m_byGammaModel.GetCurSel();
	m_struGammaCfg.dwSize = sizeof(m_struGammaCfg);
	NET_DVR_LED_GAMMA_CFG_COND struCfgCond;
	memset(&struCfgCond, 0, sizeof(struCfgCond));
	struCfgCond.dwSize = sizeof(struCfgCond);
	struCfgCond.dwOutputNo = m_dwGammaOutputNo;
	struCfgCond.struPosStart.wColumn = m_dwGammaStartCol;
	struCfgCond.struPosStart.wLine = m_dwGammaStartRow;
	struCfgCond.struPosEnd.wColumn = m_dwGammaEndCol;
	struCfgCond.struPosEnd.wLine = m_dwGammaEndRow;
	struCfgCond.byGammaType = m_byGammaType.GetCurSel();
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_LED_RECV_GAMMA_CFG, 1, &struCfgCond, sizeof(struCfgCond), NULL, &m_struGammaCfg, sizeof(m_struGammaCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_RECV_GAMMA_CFG");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_RECV_GAMMA_CFG");
    m_byGammaModel.SetCurSel(m_struGammaCfg.byGammaModel);
	UpdateCammaTable();
}

void CDlgLedConfigRecv::OnBtnGammaModify() 
{
	// TODO: Add your control notification handler code here
	if (m_iCurIndex == -1)
	{
		return;
	}
	UpdateData(TRUE);
	CString str;
	str.Format("%d", m_dwGammaY);
	m_listGammaY.SetItemText(m_iCurIndex, 1, str);
	m_listGammaY.SetItemData(m_iCurIndex, m_dwGammaY);
	m_struGammaCfg.wGammaValue[m_iCurIndex] = m_dwGammaY;
}

void CDlgLedConfigRecv::OnBtnGammaSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_struGammaCfg.byGammaModel = m_byGammaModel.GetCurSel();
    if (m_struGammaCfg.byGammaModel != 0) //非自定义模式
    {
        ZeroMemory(&m_struGammaCfg.wGammaValue, sizeof(m_struGammaCfg.wGammaValue));
    }
	m_struGammaCfg.dwSize = sizeof(m_struGammaCfg);
	NET_DVR_LED_GAMMA_CFG_COND struCfgCond;
	memset(&struCfgCond, 0, sizeof(struCfgCond));
	struCfgCond.dwSize = sizeof(struCfgCond);
	struCfgCond.byGammaType= m_byGammaType.GetCurSel();
	struCfgCond.dwOutputNo = m_dwGammaOutputNo;
	struCfgCond.struPosStart.wColumn = m_dwGammaStartCol;
	struCfgCond.struPosStart.wLine = m_dwGammaStartRow;
	struCfgCond.struPosEnd.wColumn = m_dwGammaEndCol;
	struCfgCond.struPosEnd.wLine = m_dwGammaEndRow;
	if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_LED_RECV_GAMMA_CFG, 1, &struCfgCond, sizeof(struCfgCond), NULL, &m_struGammaCfg, sizeof(m_struGammaCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_RECV_GAMMA_CFG");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_RECV_GAMMA_CFG");
}

void CDlgLedConfigRecv::OnBtnHighGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struAdvancedCfg.dwSize = sizeof(m_struAdvancedCfg);
	NET_DVR_LED_RECV_CARD_CFG_COND struCfgCond;
	memset(&struCfgCond, 0, sizeof(struCfgCond));
	struCfgCond.dwSize = sizeof(struCfgCond);
	struCfgCond.dwOutputNo = m_dwHighOutputNo;
	struCfgCond.struPosStart.wColumn = m_dwHighStartCol;
	struCfgCond.struPosStart.wLine = m_dwHighStartRow;
	struCfgCond.struPosEnd.wColumn = m_dwHighEndCol;
	struCfgCond.struPosEnd.wLine = m_dwHighEndRow;
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_LED_RECV_ADVANCED_CFG, 1, &struCfgCond, sizeof(struCfgCond), NULL, &m_struAdvancedCfg, sizeof(m_struAdvancedCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_RECV_ADVANCED_CFG");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_RECV_ADVANCED_CFG");
	m_cmbGroupNo.SetCurSel(0);
	OnSelchangeComboGroupNo();
}

void CDlgLedConfigRecv::OnBtnHighSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struAdvancedCfg.dwSize = sizeof(m_struAdvancedCfg);
	NET_DVR_LED_RECV_CARD_CFG_COND struCfgCond;
	memset(&struCfgCond, 0, sizeof(struCfgCond));
	struCfgCond.dwSize = sizeof(struCfgCond);
	struCfgCond.dwOutputNo = m_dwHighOutputNo;
	struCfgCond.struPosStart.wColumn = m_dwHighStartCol;
	struCfgCond.struPosStart.wLine = m_dwHighStartRow;
	struCfgCond.struPosEnd.wColumn = m_dwHighEndCol;
	struCfgCond.struPosEnd.wLine = m_dwHighEndRow;
	if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_LED_RECV_ADVANCED_CFG, 1, &struCfgCond, sizeof(struCfgCond), NULL, &m_struAdvancedCfg, sizeof(m_struAdvancedCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_RECV_ADVANCED_CFG");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_RECV_ADVANCED_CFG");
}

void CDlgLedConfigRecv::OnSelchangeComboGroupNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nSel = m_cmbGroupNo.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	if (nSel == 0)
	{
		m_lpRegistor = &m_struAdvancedCfg.struFirstRegistor;
	}
	else if (nSel == 1)
	{
		m_lpRegistor = &m_struAdvancedCfg.struSecondRegistor;
	}
	else
	{
		m_lpRegistor = &m_struAdvancedCfg.struThirdRegistor;
	}
	m_bClearBadPoint = m_lpRegistor->byClearBadPoint;
	m_bEnableHGrayStripes = m_lpRegistor->byDisableHGrayStripes;
	m_dwElimanateGhostShadowLevel = m_lpRegistor->byEliminateGhostShadowLevel;
	m_dwElimanateShadowy = m_lpRegistor->byEliminateShadowy;
	m_bEnableGrayUniformity = m_lpRegistor->byEnableGrayUniformity;
	m_bEnableSelfdefineRegistor = m_lpRegistor->byEnableSelfDefineRegistor;
	m_bGhostShadowEhancedMode1 = m_lpRegistor->byGhostShadowEnhancedMode1;
	m_bGhostShadowEhancedMode2 = m_lpRegistor->byGhostShadowEnhancedMode2;
	m_dwGrayEqualize1 = m_lpRegistor->byGrayEqualize1;
	m_dwGrayEqualize2 = m_lpRegistor->byGrayEqualize2;
	m_dwChip1High = m_lpRegistor->struRegistorValue.byChip1High;
	m_dwChip1Low = m_lpRegistor->struRegistorValue.byChip1Low;
	m_dwChip2High = m_lpRegistor->struRegistorValue.byChip2High;
	m_dwChip2Low = m_lpRegistor->struRegistorValue.byChip2Low;
	m_dwChip3High = m_lpRegistor->struRegistorValue.byChip3High;
	m_dwChip3Low = m_lpRegistor->struRegistorValue.byChip3Low;

    m_byEnabledExGradientOptimition= m_lpRegistor->byEnabledExGradientOptimition;
    m_byDummyGClockCycle=m_lpRegistor->byDummyGClockCycle ;
    m_byDummyGClockHighTime=m_lpRegistor->byDummyGClockHighTime ;
    m_byFirstGClockExtendedTime=m_lpRegistor->byFirstGClockExtendedTime;

    m_byChip4High = m_lpRegistor->struRegistorValue.byChip4High;
    m_byChip4Low = m_lpRegistor->struRegistorValue.byChip4Low;
    m_byChip5High = m_lpRegistor->struRegistorValue.byChip5High;
    m_byChip5Low = m_lpRegistor->struRegistorValue.byChip5Low;
    m_byChip6High = m_lpRegistor->struRegistorValue.byChip6High;
    m_byChip6Low = m_lpRegistor->struRegistorValue.byChip6Low;
	UpdateData(FALSE);
}

void CDlgLedConfigRecv::OnClickListGammaY(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION posCur = m_listGammaY.GetFirstSelectedItemPosition();
	if (posCur)
	{
		m_iCurIndex = m_listGammaY.GetNextSelectedItem(posCur);
		m_dwGammaY = m_listGammaY.GetItemData(m_iCurIndex);
		UpdateData(FALSE);
	}
	
	*pResult = 0;
}

void CDlgLedConfigRecv::OnBtnHighOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_lpRegistor == NULL)
	{
		return;
	}
	m_lpRegistor->byClearBadPoint = m_bClearBadPoint;
	m_lpRegistor->byDisableHGrayStripes = m_bEnableHGrayStripes;
	m_lpRegistor->byEliminateGhostShadowLevel = m_dwElimanateGhostShadowLevel;
	m_lpRegistor->byEliminateShadowy = m_dwElimanateShadowy;
	m_lpRegistor->byEnableGrayUniformity = m_bEnableGrayUniformity;
	m_lpRegistor->byEnableSelfDefineRegistor = m_bEnableSelfdefineRegistor;
	m_lpRegistor->byGhostShadowEnhancedMode1 = m_bGhostShadowEhancedMode1;
	m_lpRegistor->byGhostShadowEnhancedMode2 = m_bGhostShadowEhancedMode2;
	m_lpRegistor->byGrayEqualize1 = m_dwGrayEqualize1;
	m_lpRegistor->byGrayEqualize2 = m_dwGrayEqualize2;
    m_lpRegistor->byEnabledExGradientOptimition = m_byEnabledExGradientOptimition;
    m_lpRegistor->byDummyGClockCycle = m_byDummyGClockCycle;
    m_lpRegistor->byDummyGClockHighTime = m_byDummyGClockHighTime;
    m_lpRegistor->byFirstGClockExtendedTime = m_byFirstGClockExtendedTime;

	m_lpRegistor->struRegistorValue.byChip1High = m_dwChip1High;
	m_lpRegistor->struRegistorValue.byChip1Low = m_dwChip1Low;
	m_lpRegistor->struRegistorValue.byChip2High = m_dwChip2High;
	m_lpRegistor->struRegistorValue.byChip2Low = m_dwChip2Low;
	m_lpRegistor->struRegistorValue.byChip3High = m_dwChip3High;
	m_lpRegistor->struRegistorValue.byChip3Low = m_dwChip3Low;

    m_lpRegistor->struRegistorValue.byChip4High = m_byChip4High;
    m_lpRegistor->struRegistorValue.byChip4Low = m_byChip4Low;
    m_lpRegistor->struRegistorValue.byChip5High = m_byChip5High;
    m_lpRegistor->struRegistorValue.byChip5Low = m_byChip5Low;
    m_lpRegistor->struRegistorValue.byChip6High = m_byChip6High;
    m_lpRegistor->struRegistorValue.byChip6Low = m_byChip6Low;
}

void CDlgLedConfigRecv::OnBtnSaveConfiguration() 
{
	// TODO: Add your control notification handler code here
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SAVE_LED_CONFIGURATION, NULL, 0))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SAVE_LED_CONFIGURATION");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SAVE_LED_CONFIGURATION");
}


void CDlgLedConfigRecv::OnBnClickedBtnVersion()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgLEDVersion dlg;
    dlg.DoModal();
}
