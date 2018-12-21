// DlgMatOutputCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMatOutputCfg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMatOutputCfg dialog


CDlgMatOutputCfg::CDlgMatOutputCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMatOutputCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMatOutputCfg)
	m_bAudio = FALSE;
	m_dwHeight = 0;
	m_dwWidth = 0;
	m_BVEffcetEnable = FALSE;
	m_byBrightness = 0;
	m_byContrast = 0;
	m_byGray = 0;
	m_byHue = 0;
	m_bySharpness = 0;
	m_bySaturation = 0;
	m_BSmarkIR = FALSE;
	m_BLowLight = FALSE;
	m_BLightInhibit = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgMatOutputCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMatOutputCfg)
	DDX_Control(pDX, IDC_COMBO_LEVEL, m_cmbLightInhibit);
	DDX_Control(pDX, IDC_COMBO_SUBWIN_NUM, m_comboSubWinNum);
	DDX_Control(pDX, IDC_LIST_OUTPUT, m_listOutput);
	DDX_Control(pDX, IDC_COMBO_WINDOW_MODE, m_comboWinMode);
	DDX_Control(pDX, IDC_COMBO_VIDEO_FORMAT, m_comboVideoFarmat);
	DDX_Control(pDX, IDC_COMBO_SUBSYS_NUM, m_comboSubSysNum);
	DDX_Control(pDX, IDC_COMBO_SUBSYS_DISPNUM, m_comboSubSysDispNum);
	DDX_Control(pDX, IDC_COMBO_SUB_WIN_RES, m_comboSubWinRes);
	DDX_Control(pDX, IDC_COMBO_SCALE, m_comboScale);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
	DDX_Control(pDX, IDC_COMBO_PS_Y, m_comboPsY);
	DDX_Control(pDX, IDC_COMBO_PS_X, m_comboPsX);
	DDX_Control(pDX, IDC_COMBO_AUDIO_SUBWIN, m_comboAudioSubWin);
	DDX_Check(pDX, IDC_CHK_AUDIO, m_bAudio);
	DDX_Text(pDX, IDC_EDT_LED_RESOLUTION_HEIGHT, m_dwHeight);
	DDX_Text(pDX, IDC_EDT_LED_RESOLUTION_WIDTH, m_dwWidth);
	DDX_Check(pDX, IDC_CHK_VIDEOEFFECT_ENABLE, m_BVEffcetEnable);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_byBrightness);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_byContrast);
	DDX_Text(pDX, IDC_EDIT_GRAY, m_byGray);
	DDX_Text(pDX, IDC_EDIT_HUE, m_byHue);
	DDX_Text(pDX, IDC_EDIT_SHARPNESS, m_bySharpness);
	DDX_Text(pDX, IDC_EDIT_SATURATION2, m_bySaturation);
	DDX_Check(pDX, IDC_CHK_FGB, m_BSmarkIR);
	DDX_Check(pDX, IDC_CHK_DZD, m_BLowLight);
	DDX_Check(pDX, IDC_CHK_QGYZ, m_BLightInhibit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMatOutputCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgMatOutputCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBSYS_NUM, OnSelchangeComboSubsysNum)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBSYS_DISPNUM, OnSelchangeComboSubsysDispnum)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_GET_OUTPUT, OnBtnGetOutput)
	ON_BN_CLICKED(IDC_BTN_SET_OUTPUT, OnBtnSetOutput)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_OUTPUT, OnClickListOutput)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBWIN_NUM, OnSelchangeComboSubwinNum)
	ON_BN_CLICKED(IDC_BTN_RES_SAVE, OnBtnResSave)
	ON_CBN_SELCHANGE(IDC_COMBO_WINDOW_MODE, OnSelchangeComboWindowMode)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMatOutputCfg message handlers

BOOL CDlgMatOutputCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lServerID = g_struDeviceInfo[m_iDeviceIndex ].lLoginID; 
	m_lSubSysID = -1;
	m_iCurSel = -1;
	memset(&m_struAllSubSysInfo, 0, sizeof(m_struAllSubSysInfo));
	memset(m_struOutputCfg, 0, sizeof(m_struOutputCfg));
	memset(m_struOutputCfgSet, 0, sizeof(m_struOutputCfgSet));
	memset(m_bParamSaved, 0, sizeof(m_bParamSaved));
	memset(&m_struDecoderAbility, 0, sizeof(m_struDecoderAbility));
	
	int i= 0;
	char szLan[64] = {0};

	for (i = 0; i < 16; i++)
	{
		sprintf(szLan, "%d", i);
		m_comboPsX.AddString(szLan);
		m_comboPsY.AddString(szLan);
	}

	if (!NET_DVR_MatrixGetSubSystemInfo_V40(m_lServerID, &m_struAllSubSysInfo))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixGetSubSystemInfo_V40");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixGetSubSystemInfo_V40");
		for (i = 0; i < MAX_SUBSYSTEM_NUM_V40; i++)
		{
			if (m_struAllSubSysInfo.struSubSystemInfo[i].bySubSystemType == 1)
			{
				sprintf(szLan, "%d", m_struAllSubSysInfo.struSubSystemInfo[i].bySlotNum);
				int iIndex = m_comboSubSysNum.AddString(szLan);
				m_comboSubSysNum.SetItemData(iIndex, i);				
			}
		}		
	}

	m_listOutput.SetExtendedStyle(m_listOutput.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	g_StringLanType(szLan, "子系统号", "Sub system num");
	m_listOutput.InsertColumn(0, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "显示通道号", "Display chan Num");
	m_listOutput.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "音频开启", "Audio enabled");
	m_listOutput.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "音频开启子窗口", "Audio related Subwin");
	m_listOutput.InsertColumn(3, szLan, LVCFMT_LEFT, 120, -1);
	g_StringLanType(szLan, "视频制式", "Video format");
	m_listOutput.InsertColumn(4, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "分辨率", "Resolution");
	m_listOutput.InsertColumn(5, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "画面模式", "Window mode");
	m_listOutput.InsertColumn(6, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "显示模式", "Display mode");
	m_listOutput.InsertColumn(7, szLan, LVCFMT_LEFT, 80, -1);	
	g_StringLanType(szLan, "坐标X", "X");
	m_listOutput.InsertColumn(8, szLan, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLan, "坐标Y", "Y");
	m_listOutput.InsertColumn(9, szLan, LVCFMT_LEFT, 60, -1);
	g_StringLanType(szLan, "状态", "Status");
	m_listOutput.InsertColumn(10, szLan, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLan, "LED分辨率宽", "LED Resolution Width");
	m_listOutput.InsertColumn(11, szLan, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLan, "LED分辨率高", "LED Resolution Height");
	m_listOutput.InsertColumn(12, szLan, LVCFMT_LEFT, 60, -1);
	OnBtnGetAll();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMatOutputCfg::OnSelchangeComboSubsysNum() 
{
	// TODO: Add your control notification handler code here
	if (m_comboSubSysNum.GetCurSel() == CB_ERR)
	{
		return;
	}

	char szLan[64] = {0};
	int i = 0;
	int j = 0;
	int ChanNo = -1;
	CString tmp;

	BYTE bySlotNum = m_comboSubSysNum.GetItemData(m_comboSubSysNum.GetCurSel());
	NET_DVR_DEVICEINFO_V30 struDevInfo = {0};

	if (m_lSubSysID != -1)
	{
		NET_DVR_Logout_V30(m_lSubSysID);
		m_lSubSysID = -1;
	}

	if ((m_lSubSysID = NET_DVR_Login_V30(m_struAllSubSysInfo.struSubSystemInfo[bySlotNum].struSubSystemIP.sIpV4, m_struAllSubSysInfo.struSubSystemInfo[bySlotNum].wSubSystemPort,\
		(char *)m_struAllSubSysInfo.struSubSystemInfo[bySlotNum].sUserName, (char *)m_struAllSubSysInfo.struSubSystemInfo[bySlotNum].sPassword, &struDevInfo)) == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_Login_V30");
	}
	else
	{
		if (!NET_DVR_GetDeviceAbility(m_lSubSysID, MATRIXDECODER_ABILITY_V41, NULL, 0, (char *)&m_struDecoderAbility, sizeof(m_struDecoderAbility)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "MATRIXDECODER_ABILITY_V41");
		}
		else
		{			
			m_comboSubSysDispNum.ResetContent();
			m_comboResolution.ResetContent();

			for(i = 0; i < m_struDecoderAbility.struBncInfo.byChanNums; i++)
			{				
				ChanNo = i + 1;
				g_StringLanType(szLan, "BNC", "BNC");
				tmp.Format("%s %d", szLan, ChanNo);
				m_comboSubSysDispNum.AddString(tmp);
				m_comboSubSysDispNum.SetItemData(m_comboSubSysDispNum.GetCount() - 1, m_struDecoderAbility.struBncInfo.byStartChan + i);				
			}
			
			for(i = 0; i < m_struDecoderAbility.struVgaInfo.byChanNums; i++)
			{	
				ChanNo = i + 1;
				g_StringLanType(szLan, "VGA", "VGA");
				tmp.Format("%s %d", szLan, ChanNo);
				m_comboSubSysDispNum.AddString(tmp);
				m_comboSubSysDispNum.SetItemData(m_comboSubSysDispNum.GetCount() - 1, m_struDecoderAbility.struVgaInfo.byStartChan + i);
			}
			
			for(i = 0; i < m_struDecoderAbility.struHdmiInfo.byChanNums; i++)
			{	
				ChanNo = i + 1;
				g_StringLanType(szLan, "HDMI", "HDMI");
				tmp.Format("%s %d", szLan, ChanNo);
				m_comboSubSysDispNum.AddString(tmp);
				m_comboSubSysDispNum.SetItemData(m_comboSubSysDispNum.GetCount() - 1, m_struDecoderAbility.struHdmiInfo.byStartChan + i);
			}
			
			for(i = 0; i < m_struDecoderAbility.struDviInfo.byChanNums; i++)
			{
				ChanNo = i + 1;
				g_StringLanType(szLan, "DVI", "DVI");
				tmp.Format("%s %d", szLan, ChanNo);
				m_comboSubSysDispNum.AddString(tmp);
				m_comboSubSysDispNum.SetItemData(m_comboSubSysDispNum.GetCount() - 1, m_struDecoderAbility.struDviInfo.byStartChan + i);
			}

			for(i = 0; i < m_struDecoderAbility.struSDIInfo.byChanNums; i++)
			{
				ChanNo = i + 1;
				g_StringLanType(szLan, "SDI", "SDI");
				tmp.Format("%s %d", szLan, ChanNo);
				m_comboSubSysDispNum.AddString(tmp);
				m_comboSubSysDispNum.SetItemData(m_comboSubSysDispNum.GetCount() - 1, m_struDecoderAbility.struSDIInfo.byStartChan + i);
			}

		}
	}
}


void CDlgMatOutputCfg::GetResolutionString(DWORD dwRes, char *lpResString)
{
	switch (dwRes)
	{
	case NOT_AVALIABLE:
		sprintf(lpResString, "%s", "NOT_AVALIABLE");
		break;
	case SVGA_60HZ:
		sprintf(lpResString, "%s", "SVGA_60HZ");
		break;
	case SVGA_75HZ:
		sprintf(lpResString, "%s", "SVGA_75HZ");
		break;	
	case XGA_60HZ:
		sprintf(lpResString, "%s", "XGA_60HZ");
		break;	
	case XGA_75HZ:
		sprintf(lpResString, "%s", "XGA_75HZ");
		break;	
	case SXGA_60HZ:
		sprintf(lpResString, "%s", "SXGA_60HZ");
		break;	
	case SXGA2_60HZ:
		sprintf(lpResString, "%s", "SXGA2_60HZ");
		break;	
	case _720P_24HZ:
		sprintf(lpResString, "%s", "_720P_24HZ");
		break; 
	case _720P_25HZ:
		sprintf(lpResString, "%s", "_720P_25HZ");
		break;
	case _720P_30HZ:
		sprintf(lpResString, "%s", "_720P_30HZ");
		break;
	case _720P_60HZ:
		sprintf(lpResString, "%s", "_720P_60HZ");
		break;	
	case _720P_50HZ:
		sprintf(lpResString, "%s", "_720P_50HZ");
		break;	
	case _1080I_60HZ:
		sprintf(lpResString, "%s", "_1080I_60HZ");
		break;	
	case _1080I_50HZ:
		sprintf(lpResString, "%s", "_1080I_50HZ");
		break;	
	case _1080P_60HZ:
		sprintf(lpResString, "%s", "_1080P_60HZ");
		break;
	case _1080P_50HZ:
		sprintf(lpResString, "%s", "_1080P_50HZ");
		break;	
	case _1080P_30HZ:
		sprintf(lpResString, "%s", "_1080P_30HZ");
		break;	
	case _1080P_25HZ:
		sprintf(lpResString, "%s", "_1080P_25HZ");
		break;	
	case _1080P_24HZ:
		sprintf(lpResString, "%s", "_1080P_24HZ");
		break;	
	case UXGA_60HZ:
		sprintf(lpResString, "%s", "UXGA_60HZ");
		break;
	case UXGA_30HZ:
		sprintf(lpResString, "%s", "UXGA_30HZ");
		break;	
	case WSXGA_60HZ:
		sprintf(lpResString, "%s", "WSXGA_60HZ");
		break;	
	case WUXGA_60HZ:
		sprintf(lpResString, "%s", "WUXGA_60HZ");
		break;
	case WUXGA_30HZ:
		sprintf(lpResString, "%s", "WUXGA_30HZ");
		break;
	case WXGA_60HZ:
		sprintf(lpResString, "%s", "WXGA_60HZ");
		break;
	case SXGA_PLUS_60HZ:
		sprintf(lpResString, "%s", "SXGA_PLUS_60HZ");
	default:
		break;
	}
}

void CDlgMatOutputCfg::GetResolutionDword(DWORD *dwRes, CString lpResString)
{
	if (lpResString == "NOT_AVALIABLE")
	{
		*dwRes = NOT_AVALIABLE;
	}
	else if (lpResString == "SVGA_60HZ")
	{
		*dwRes = SVGA_60HZ;
	}
	else if (lpResString == "SVGA_75HZ")
	{
		*dwRes = SVGA_75HZ;
	}
	else if (lpResString == "XGA_60HZ")
	{
		*dwRes = XGA_60HZ;
	}
	else if (lpResString == "XGA_75HZ")
	{
		*dwRes = XGA_75HZ;
	}
	else if (lpResString == "SXGA_60HZ")
	{
		*dwRes = SXGA_60HZ;
	}
	else if (lpResString == "SXGA2_60HZ")
	{
		*dwRes = SXGA2_60HZ;
	}
	else if (lpResString == "_720P_60HZ")
	{
		*dwRes = _720P_60HZ;
	}
	else if (lpResString == "_720P_50HZ")
	{
		*dwRes = _720P_50HZ;
	}else if (lpResString == "_1080I_60HZ")
	{
		*dwRes = _1080I_60HZ;
	}
	else if (lpResString == "_1080I_50HZ")
	{
		*dwRes = _1080I_50HZ;
	}
	else if (lpResString == "_1080P_60HZ")
	{
		*dwRes = _1080P_60HZ;
	}
	else if (lpResString == "_1080P_50HZ")
	{
		*dwRes = _1080P_50HZ;
	}
	else if (lpResString == "_1080P_30HZ")
	{
		*dwRes = _1080P_30HZ;
	}
	else if (lpResString == "_1080P_60HZ")
	{
		*dwRes = _1080P_60HZ;
	}
	else if (lpResString == "_1080P_25HZ")
	{
		*dwRes = _1080P_25HZ;
	}
	else if (lpResString == "_1080P_24HZ")
	{
		*dwRes = _1080P_24HZ;
	}
	else if (lpResString == "UXGA_60HZ")
	{
		*dwRes = UXGA_60HZ;
	}
	else if (lpResString == "UXGA_30HZ")
	{
		*dwRes = UXGA_30HZ;
	}
	else if (lpResString == "WSXGA_60HZ")
	{
		*dwRes = WSXGA_60HZ;
	}
	else if (lpResString == "WUXGA_60HZ")
	{
		*dwRes = WUXGA_60HZ;
	}
	else if (lpResString == "WUXGA_30HZ")
	{
		*dwRes = WUXGA_30HZ;
	}
	else if (lpResString == "WXGA_60HZ")
	{
		*dwRes = WXGA_60HZ;
	}
	else if (lpResString == "SXGA_PLUS_60HZ")
	{
		*dwRes = SXGA_PLUS_60HZ;
	}
}

void CDlgMatOutputCfg::OnSelchangeComboSubsysDispnum() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	char szLan[64] = {0};	
	DWORD dwChanIndex = m_comboSubSysDispNum.GetCurSel();
	m_comboWinMode.ResetContent();
	WORD wBncChanMaxIndex =  m_struDecoderAbility.struBncInfo.byChanNums;
	WORD wVgaChanMaxIndex =   m_struDecoderAbility.struVgaInfo.byChanNums + wBncChanMaxIndex;
	WORD wHdmiChanMaxIndex =  m_struDecoderAbility.struHdmiInfo.byChanNums + wVgaChanMaxIndex;
	WORD wDviChanMaxIndex =   m_struDecoderAbility.struDviInfo.byChanNums + wHdmiChanMaxIndex;
	WORD wSdiChanMaxIndex =   m_struDecoderAbility.struSDIInfo.byChanNums + wDviChanMaxIndex;
	if (dwChanIndex < wBncChanMaxIndex)
	{
		//窗口分屏模式
		for (i = 0; i < MAX_DISPNUM_V41; i++)
		{
			if (m_struDecoderAbility.struDispMode[i].byDispChanType != 0)
			{
				continue;
			}
			break;
		}
		
		int iKeep = i + dwChanIndex;

		for (i = 0; i < MAX_WINDOWS_NUM; i++)
		{
			if (m_struDecoderAbility.struDispMode[iKeep].byDispMode[i] != 0)
			{
				sprintf(szLan, "%d", m_struDecoderAbility.struDispMode[iKeep].byDispMode[i]);
				m_comboWinMode.AddString(szLan);
				m_comboWinMode.SetItemData(m_comboWinMode.GetCount() - 1, m_struDecoderAbility.struDispMode[iKeep].byDispMode[i]);
			}
		}

		//增加0分屏表示取消分屏
		m_comboWinMode.AddString("0");
		m_comboWinMode.SetItemData(m_comboWinMode.GetCount() - 1, 0);

		//分辨率
		for (i = 0; i < MAX_SUPPORT_RES; i++)
		{
			memset(szLan, 0, sizeof(szLan));
			GetResolutionString(m_struDecoderAbility.struBncInfo.dwSupportResolution[i], szLan);
			if (m_comboResolution.FindStringExact(0, szLan) == CB_ERR)
			{
				m_comboResolution.AddString(szLan);
				m_comboResolution.SetItemData(m_comboResolution.GetCount() - 1, m_struDecoderAbility.struBncInfo.dwSupportResolution[i]);
			}
		}
	}
	else if ((dwChanIndex >= wBncChanMaxIndex) && (dwChanIndex <wVgaChanMaxIndex))
	{
		DWORD dwSeq = m_comboSubSysDispNum.GetCurSel() - wBncChanMaxIndex;
		//窗口分屏模式
		for (i = 0; i < MAX_DISPNUM_V41; i++)
		{
			if (m_struDecoderAbility.struDispMode[i].byDispChanType != 1)
			{
				continue;
			}
			break;
		}

		int iKeep = i + dwSeq;
		for (i = 0; i < MAX_WINDOWS_NUM; i++)
		{
			if (m_struDecoderAbility.struDispMode[iKeep].byDispMode[i] != 0)
			{
				sprintf(szLan, "%d", m_struDecoderAbility.struDispMode[iKeep].byDispMode[i]);
				m_comboWinMode.AddString(szLan);
				m_comboWinMode.SetItemData(m_comboWinMode.GetCount() - 1, m_struDecoderAbility.struDispMode[iKeep].byDispMode[i]);
			}
		}
		
		//增加0分屏表示取消分屏
		m_comboWinMode.AddString("0");
		m_comboWinMode.SetItemData(m_comboWinMode.GetCount() - 1, 0);

		//分辨率
		for (i = 0; i < MAX_SUPPORT_RES; i++)
		{
			memset(szLan, 0, sizeof(szLan));
			GetResolutionString(m_struDecoderAbility.struVgaInfo.dwSupportResolution[i], szLan);
			if (m_comboResolution.FindStringExact(0, szLan) == CB_ERR)
			{
				m_comboResolution.AddString(szLan);
				m_comboResolution.SetItemData(m_comboResolution.GetCount() - 1, m_struDecoderAbility.struVgaInfo.dwSupportResolution[i]);
			}
		}
	}
	else if ((dwChanIndex >= wVgaChanMaxIndex) && (dwChanIndex < wHdmiChanMaxIndex))
	{
		DWORD dwSeq = m_comboSubSysDispNum.GetCurSel() - wVgaChanMaxIndex;
		//窗口分屏模式
		for (i = 0; i < MAX_DISPNUM_V41; i++)
		{
			if (m_struDecoderAbility.struDispMode[i].byDispChanType != 2)
			{
				continue;
			}
			break;
		}
		
		int iKeep = i + dwSeq;
		for (i = 0; i < MAX_WINDOWS_NUM; i++)
		{
			if (m_struDecoderAbility.struDispMode[iKeep].byDispMode[i] != 0)
			{
				sprintf(szLan, "%d", m_struDecoderAbility.struDispMode[iKeep].byDispMode[i]);
				m_comboWinMode.AddString(szLan);
				m_comboWinMode.SetItemData(m_comboWinMode.GetCount() - 1, m_struDecoderAbility.struDispMode[iKeep].byDispMode[i]);
			}
		}
		//增加0分屏表示取消分屏
		m_comboWinMode.AddString("0");
		m_comboWinMode.SetItemData(m_comboWinMode.GetCount() - 1, 0);

		//分辨率
		for (i = 0; i < MAX_SUPPORT_RES; i++)
		{
			memset(szLan, 0, sizeof(szLan));
			GetResolutionString(m_struDecoderAbility.struHdmiInfo.dwSupportResolution[i], szLan);
			if (m_comboResolution.FindStringExact(0, szLan) == CB_ERR)
			{
				m_comboResolution.AddString(szLan);
				m_comboResolution.SetItemData(m_comboResolution.GetCount() - 1, m_struDecoderAbility.struHdmiInfo.dwSupportResolution[i]);
			}
		}
	}
	else if (dwChanIndex >= wHdmiChanMaxIndex && (dwChanIndex < wDviChanMaxIndex))
	{
		DWORD dwSeq = m_comboSubSysDispNum.GetCurSel() - wHdmiChanMaxIndex;
		//窗口分屏模式
		for (i = 0; i < MAX_DISPNUM_V41; i++)
		{
			if (m_struDecoderAbility.struDispMode[i].byDispChanType != 3)
			{
				continue;
			}
			break;
		}
		
		int iKeep = i + dwSeq;
		for (i = 0; i < MAX_WINDOWS_NUM; i++)
		{
			if (m_struDecoderAbility.struDispMode[iKeep].byDispMode[i] != 0)
			{
				sprintf(szLan, "%d", m_struDecoderAbility.struDispMode[iKeep].byDispMode[i]);
				m_comboWinMode.AddString(szLan);
				m_comboWinMode.SetItemData(m_comboWinMode.GetCount() - 1, m_struDecoderAbility.struDispMode[iKeep].byDispMode[i]);
			}
		}
		
		//增加0分屏表示取消分屏
		m_comboWinMode.AddString("0");
		m_comboWinMode.SetItemData(m_comboWinMode.GetCount() - 1, 0);
		//分辨率
		for (i = 0; i < MAX_SUPPORT_RES; i++)
		{
			memset(szLan, 0, sizeof(szLan));
			GetResolutionString(m_struDecoderAbility.struDviInfo.dwSupportResolution[i], szLan);
			if (m_comboResolution.FindStringExact(0, szLan) == CB_ERR)
			{
				m_comboResolution.AddString(szLan);
				m_comboResolution.SetItemData(m_comboResolution.GetCount() - 1, m_struDecoderAbility.struDviInfo.dwSupportResolution[i]);
			}
		}
	}	
	else if ((dwChanIndex >= wDviChanMaxIndex) && (dwChanIndex < wSdiChanMaxIndex))
	{
		DWORD dwSeq = m_comboSubSysDispNum.GetCurSel() - wDviChanMaxIndex ;
		//窗口分屏模式
		for (i = 0; i < MAX_DISPNUM_V41; i++)
		{
			if (m_struDecoderAbility.struDispMode[i].byDispChanType != 4)
			{
				continue;
			}
			break;
		}
		
		int iKeep = i + dwSeq;
		for (i = 0; i < MAX_WINDOWS_NUM; i++)
		{
			if (m_struDecoderAbility.struDispMode[iKeep].byDispMode[i] != 0)
			{
				sprintf(szLan, "%d", m_struDecoderAbility.struDispMode[iKeep].byDispMode[i]);
				m_comboWinMode.AddString(szLan);
				m_comboWinMode.SetItemData(m_comboWinMode.GetCount() - 1, m_struDecoderAbility.struDispMode[iKeep].byDispMode[i]);
			}
		}
		//增加0分屏表示取消分屏
		m_comboWinMode.AddString("0");
		m_comboWinMode.SetItemData(m_comboWinMode.GetCount() - 1, 0);

		//分辨率
		for (i = 0; i < MAX_SUPPORT_RES; i++)
		{
			memset(szLan, 0, sizeof(szLan));
			GetResolutionString(m_struDecoderAbility.struSDIInfo.dwSupportResolution[i], szLan);
			if (m_comboResolution.FindStringExact(0, szLan) == CB_ERR)
			{
				m_comboResolution.AddString(szLan);
				m_comboResolution.SetItemData(m_comboResolution.GetCount() - 1, m_struDecoderAbility.struSDIInfo.dwSupportResolution[i]);
			}
		}
	}

	int iMaxWindows = 0;
	m_comboAudioSubWin.ResetContent();
	for (i = 0; i < MAX_WINDOWS_NUM; i++)
    {
        if (m_struDecoderAbility.struDispMode[dwChanIndex].byDispMode[i] > iMaxWindows)
        {
            iMaxWindows = m_struDecoderAbility.struDispMode[dwChanIndex].byDispMode[i];
        }
    }

    for(i = 1; i <= iMaxWindows; i++)
    {
        sprintf(szLan, "%d", i);
        m_comboAudioSubWin.InsertString(i - 1, szLan);        
    }
}

void CDlgMatOutputCfg::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
	char szLan[64] = {0};
	memset(m_struOutputCfg, 0, sizeof(m_struOutputCfg));

	char *pRecvbuf = new(std::nothrow) char[4 + sizeof(m_struOutputCfg)];
	if (pRecvbuf == NULL)
	{
		g_StringLanType(szLan, "分配内存失败", "Alloc memory fail");
		AfxMessageBox(szLan);
		return;
	}

	memset(pRecvbuf, 0, 4 + sizeof(m_struOutputCfg));

	if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_DISPCHAN_CFG, 0xffffffff, NULL, 0, NULL, pRecvbuf, sizeof(m_struOutputCfg) + 4))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_OUTPUT_CFG");
		AfxMessageBox(NET_DVR_GetErrorMsg());
	}
	else
	{
		m_dwDispNum = *((DWORD *)pRecvbuf);
		memcpy(m_struOutputCfg, pRecvbuf + 4, sizeof(m_struOutputCfg));		
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_OUTPUT_CFG");
		AddDataToList();
		for (int i = 0; i < m_dwDispNum; i++)
		{
			m_listOutput.SetItemText(i, 10, "0");
		}
		AfxMessageBox("Success");

		memset(m_struOutputCfgSet, 0, sizeof(m_struOutputCfgSet));
		memset(m_bParamSaved, 0, sizeof(m_bParamSaved));
		m_iCurSel = -1;
	}

	delete []pRecvbuf;
	pRecvbuf = NULL;
}

void CDlgMatOutputCfg::AddDataToList()
{
	m_listOutput.DeleteAllItems();
	char szLan[64] = {0};
	int i = 0;
	BYTE byTemp = 0;

	for (i = 0; i < m_dwDispNum; i++)
	{
		byTemp = m_struOutputCfg[i].dwDispChanNum >> 16;
		int iIndex = m_listOutput.InsertItem(i, itoa(byTemp, szLan, 10));

		byTemp = m_struOutputCfg[i].dwDispChanNum >> 8;
		m_listOutput.SetItemText(i, 1, itoa(byTemp, szLan, 10));

		m_lOutputNum[i] = m_struOutputCfg[i].dwDispChanNum;

		if (m_struOutputCfg[i].byAudio)
		{
			m_listOutput.SetItemText(i, 2, "Yes");
			m_listOutput.SetItemText(i, 3, itoa(m_struOutputCfg[i].byAudioWindowIdx, szLan, 10));			
		}
		else
		{
			m_listOutput.SetItemText(i, 2, "No");
			m_listOutput.SetItemText(i, 3, "");
		}

		if (m_struOutputCfg[i].byVedioFormat == 1)
		{
			m_listOutput.SetItemText(i, 4, "NTSC");
		}
		else if (m_struOutputCfg[i].byVedioFormat == 2)
		{
			m_listOutput.SetItemText(i, 4, "PAL");
		}
		else
		{
			m_listOutput.SetItemText(i, 4, "NULL");
		}

		GetResolutionString(m_struOutputCfg[i].dwResolution, szLan);
		m_listOutput.SetItemText(i, 5, szLan);

		m_listOutput.SetItemText(i, 6, itoa(m_struOutputCfg[i].dwWindowMode, szLan, 10));

		if (m_struOutputCfg[i].byScale == 0)
		{
			g_StringLanType(szLan, "真实显示", "realty show");
		}
		else
		{
			g_StringLanType(szLan, "缩放显示", "zoom show");
		}
		m_listOutput.SetItemText(i, 7, szLan);		

		m_listOutput.SetItemText(i, 8, itoa(m_struOutputCfg[i].struDiff.struVideoPlatform.struPosition.wXCoordinate, szLan, 10));

		m_listOutput.SetItemText(i, 9, itoa(m_struOutputCfg[i].struDiff.struVideoPlatform.struPosition.wYCoordinate, szLan, 10));
        sprintf(szLan, "%d", m_struOutputCfg[i].wLEDWidth);
        m_listOutput.SetItemText(i, 11, szLan); 
        sprintf(szLan, "%d", m_struOutputCfg[i].wLEDHeight); 
        m_listOutput.SetItemText(i, 12, szLan);
		m_listOutput.SetItemData(iIndex, i); 
	}

	UpdateData(FALSE);
}

void CDlgMatOutputCfg::OnBtnGetOutput() 
{
	// TODO: Add your control notification handler code here
	if (m_listOutput.GetItemCount() == 0)
	{
		return;
	}

	char szLan[64] = {0};
	DWORD *dwStatusList = new(std::nothrow) DWORD[m_dwDispNum * 4];
	BOOL bAllSuccess = TRUE;

	if (dwStatusList == NULL)
	{
		g_StringLanType(szLan, "分配内存失败", "Alloc memory fail");
		AfxMessageBox(szLan);
		return;
	}

	if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_DISPCHAN_CFG, m_dwDispNum, m_lOutputNum, 4 * m_dwDispNum, dwStatusList, m_struOutputCfg, sizeof(m_struOutputCfg) * m_dwDispNum))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_OUTPUT_CFG");
		AfxMessageBox(NET_DVR_GetErrorMsg());
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_OUTPUT_CFG");
		AddDataToList();
		for (int i = 0; i < m_dwDispNum; i++)
		{
			if (*(dwStatusList + i) != 0)
			{
				bAllSuccess = FALSE;
			}
			m_listOutput.SetItemText(i, 10, itoa(*(dwStatusList + i), szLan, 10));
		}

		if (bAllSuccess)
		{
			AfxMessageBox("Success");
		}
		else
		{
			g_StringLanType(szLan, "未完全成功", "Not all success");
			AfxMessageBox(szLan);
		}
		
		memset(m_struOutputCfgSet, 0, sizeof(m_struOutputCfgSet));
		memset(m_bParamSaved, 0, sizeof(m_bParamSaved));
		m_iCurSel = -1;
	}
}

void CDlgMatOutputCfg::OnBtnSetOutput() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	int j = 0;
	int k = 0;
	BOOL bAllSuccess = TRUE;
	char szLan[64] = {0};
	DWORD dwOutputNum[MAX_OUTPUT_NUM];
	DWORD dwStatus[MAX_OUTPUT_NUM];
	memset(dwOutputNum, 0, sizeof(dwOutputNum));
	memset(dwStatus, 0, sizeof(dwStatus));

	for (i = 0; i < m_listOutput.GetItemCount(); i++)
	{
		if (m_bParamSaved[i] == TRUE)
		{
			dwOutputNum[j] = ((atoi(m_listOutput.GetItemText(i, 0)) << 16) | (atoi(m_listOutput.GetItemText(i, 1)) << 8));

			m_struOutputCfgSet[j].dwSize = sizeof(m_struOutputCfgSet[j]);

			if (0 == strcmp("Yes", m_listOutput.GetItemText(i, 2)))
			{
				m_struOutputCfgSet[j].byAudio = 1;
			}
			else
			{
				m_struOutputCfgSet[j].byAudio = 0;
			}

			if (0 == strcmp("NTSC", m_listOutput.GetItemText(i, 4)))
			{
				m_struOutputCfgSet[j].byVedioFormat = 1;
			}
			else if (0 == strcmp("PAL", m_listOutput.GetItemText(i, 4)))
			{
				m_struOutputCfgSet[j].byVedioFormat = 2;
			}
			else
			{
				m_struOutputCfgSet[j].byVedioFormat = 0;
			}
			
			GetResolutionDword(&m_struOutputCfgSet[j].dwResolution, m_listOutput.GetItemText(i, 5));	
			
			m_struOutputCfgSet[j].dwWindowMode = atoi(m_listOutput.GetItemText(i, 6));
			
			g_StringLanType(szLan, "真实显示", "realty show");
			if (0 == strcmp(szLan, m_listOutput.GetItemText(i, 7)))
			{
				m_struOutputCfgSet[j].byScale = 0;
			}
			else
			{
				m_struOutputCfgSet[j].byScale = 1;
			}

			m_struOutputCfgSet[j].struDiff.struVideoPlatform.struPosition.wXCoordinate = atoi(m_listOutput.GetItemText(i, 8));

			m_struOutputCfgSet[j].struDiff.struVideoPlatform.struPosition.wYCoordinate = atoi(m_listOutput.GetItemText(i, 9));

            m_struOutputCfgSet[j].struDiff.struVideoPlatform.struPosition.wHeight = 128;

            m_struOutputCfgSet[j].struDiff.struVideoPlatform.struPosition.wWidth = 128;

			memcpy(m_struOutputCfgSet[j].struDiff.struVideoPlatform.byDecResolution, m_struOutputCfg[i].struDiff.struVideoPlatform.byDecResolution, \
				sizeof(m_struOutputCfg[i].struDiff.struVideoPlatform.byDecResolution));

			m_struOutputCfgSet[j].wLEDWidth = m_dwWidth; 
			m_struOutputCfgSet[j].wLEDHeight = m_dwHeight; 
			m_struOutputCfgSet[j].byEnableVideoEffect = m_struOutputCfg[i].byEnableVideoEffect;
			memcpy(&m_struOutputCfgSet[j].struVideoEffect, &m_struOutputCfg[i].struVideoEffect, sizeof(m_struOutputCfg[i].struVideoEffect)); 
			j++;
		}
	}

	//什么参数也没改就把列表中数据原封不动设回去
	if (j == 0)
	{
		if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_DISPCHAN_CFG, m_dwDispNum, m_lOutputNum, 4 * m_dwDispNum, dwStatus, m_struOutputCfg, sizeof(m_struOutputCfg[0]) * m_dwDispNum))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_OUTPUT_CFG");
			AfxMessageBox(NET_DVR_GetErrorMsg());
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_OUTPUT_CFG");
			memset(m_struOutputCfgSet, 0, sizeof(m_struOutputCfgSet));
			memset(m_bParamSaved, 0, sizeof(m_bParamSaved));
			m_iCurSel = -1;
			for (i = 0; i < m_dwDispNum; i++)
			{
				if (dwStatus[i] != 0)
				{
					bAllSuccess = FALSE;
				}

				m_listOutput.SetItemText(i, 10, itoa(dwStatus[i], szLan, 10));
			}
			
			if (bAllSuccess)
			{
				AfxMessageBox("Success");
			}
			else
			{
				g_StringLanType(szLan, "未完全成功", "Not all success");
			}
		}

	}
	else
	{
		if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_DISPCHAN_CFG, j, dwOutputNum, 4 * j, dwStatus, m_struOutputCfgSet, sizeof(m_struOutputCfgSet[0]) * j))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_OUTPUT_CFG");
			AfxMessageBox(NET_DVR_GetErrorMsg());
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_OUTPUT_CFG");
			memset(m_struOutputCfgSet, 0, sizeof(m_struOutputCfgSet));
			memset(m_bParamSaved, 0, sizeof(m_bParamSaved));
			m_iCurSel = -1;
			for (i = 0; i < j; i++)
			{
				if (dwStatus[i] != 0)
				{
					bAllSuccess = FALSE;
				}
				
				for (k = 0; k < m_dwDispNum; k++)
				{
					if (m_lOutputNum[k] == dwOutputNum[i])
					{
						break;
					}
				}
				m_listOutput.SetItemText(k, 10, itoa(dwStatus[i], szLan, 10));
			}
			
			if (bAllSuccess)
			{
				AfxMessageBox("Success");
			}
			else
			{
				g_StringLanType(szLan, "未完全成功", "Not all success");
			}			
		}
	}	
}

void CDlgMatOutputCfg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[64] = {0};
	CString cs;
	if (m_iCurSel == -1)
	{
		g_StringLanType(szLan, "请选择一个条目", "Please select one item");
		AfxMessageBox(szLan);
		return;
	}

	if (m_bAudio)
	{
		m_listOutput.SetItemText(m_iCurSel, 2, "Yes");
	}
	else
	{
		m_listOutput.SetItemText(m_iCurSel, 2, "No");
	}

	cs.Empty();
	if (m_comboAudioSubWin.GetCurSel() != CB_ERR)
	{
		m_comboAudioSubWin.GetLBText(m_comboAudioSubWin.GetCurSel(), cs);
	}

	m_listOutput.SetItemText(m_iCurSel, 3, cs);

	cs.Empty();
	if (m_comboVideoFarmat.GetCurSel() != CB_ERR)
	{
		m_comboVideoFarmat.GetLBText(m_comboVideoFarmat.GetCurSel(), cs);
	}

	m_listOutput.SetItemText(m_iCurSel, 4, cs);

	cs.Empty();
	if (m_comboResolution.GetCurSel() != CB_ERR)
	{
		m_comboResolution.GetLBText(m_comboResolution.GetCurSel(), cs);
	}
	m_listOutput.SetItemText(m_iCurSel, 5, cs);

	cs.Empty();
	if (m_comboWinMode.GetCurSel() != CB_ERR)
	{
		m_comboWinMode.GetLBText(m_comboWinMode.GetCurSel(), cs);
	}
	m_listOutput.SetItemText(m_iCurSel, 6, cs);

	cs.Empty();
	if (m_comboScale.GetCurSel() != CB_ERR)
	{
		m_comboScale.GetLBText(m_comboScale.GetCurSel(), cs);
	}
	m_listOutput.SetItemText(m_iCurSel, 7, cs);

	m_listOutput.SetItemText(m_iCurSel, 8, itoa(m_comboPsX.GetCurSel() * 128, szLan, 10));

	m_listOutput.SetItemText(m_iCurSel, 9, itoa(m_comboPsY.GetCurSel() * 128, szLan, 10));

    m_listOutput.SetItemText(m_iCurSel, 11, itoa(m_dwWidth, szLan, 10));

    m_listOutput.SetItemText(m_iCurSel, 12, itoa(m_dwHeight, szLan, 10));
	m_bParamSaved[m_iCurSel] = TRUE;
	DWORD dwIndex = m_listOutput.GetItemData(m_iCurSel); 
    m_struOutputCfg[dwIndex].byEnableVideoEffect = m_BVEffcetEnable; 
	NET_DVR_VIDEOEFFECT &struVideoEffect = m_struOutputCfg[dwIndex].struVideoEffect;
	if ( !m_BVEffcetEnable )
	{
		memset(&struVideoEffect, 0, sizeof(struVideoEffect));
		return ; 
	}
	struVideoEffect.byBrightnessLevel = m_byBrightness; 
	struVideoEffect.byContrastLevel = m_byContrast; 
	struVideoEffect.bySharpnessLevel = m_bySharpness;
	struVideoEffect.bySaturationLevel = m_bySaturation;
	struVideoEffect.byHueLevel = m_byHue; 
	struVideoEffect.byGrayLevel = m_byGray; 
	struVideoEffect.byEnableFunc = m_BSmarkIR? 1:0;
	struVideoEffect.byEnableFunc += m_BLowLight? 0x2:0; 
	struVideoEffect.byEnableFunc += m_BLightInhibit? 0x4:0; 
	struVideoEffect.byLightInhibitLevel = m_cmbLightInhibit.GetCurSel()+1; 

}

void CDlgMatOutputCfg::OnClickListOutput(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION  iPos = m_listOutput.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}

	int i = 0;
	char szLan[64] = {0};
 	m_iCurSel = m_listOutput.GetNextSelectedItem(iPos);
	m_comboSubSysNum.SetCurSel(-1); 
	for (i = 0; i < m_comboSubSysNum.GetCount(); i++)
	{
		if (atoi(m_listOutput.GetItemText(m_iCurSel, 0))  == m_struAllSubSysInfo.struSubSystemInfo[m_comboSubSysNum.GetItemData(i)].bySlotNum) 
		{
			m_comboSubSysNum.SetCurSel(i);
			OnSelchangeComboSubsysNum();
			break;
		}
	}

	for (i = 0; i < m_comboSubSysDispNum.GetCount(); i++)
	{
		if (atoi(m_listOutput.GetItemText(m_iCurSel, 1)) == m_comboSubSysDispNum.GetItemData(i))
		{
			m_comboSubSysDispNum.SetCurSel(i);
			OnSelchangeComboSubsysDispnum();
			break;
		}
	}

	if (0 == strcmp("Yes", m_listOutput.GetItemText(m_iCurSel, 2)))
	{
		m_bAudio = TRUE;
	}
	else
	{
		m_bAudio = FALSE;
	}

	m_comboAudioSubWin.SetCurSel(atoi(m_listOutput.GetItemText(m_iCurSel, 3) - 1));

	if (0 == strcmp("NTSC", m_listOutput.GetItemText(m_iCurSel, 4)))
	{
		m_comboVideoFarmat.SetCurSel(1);
	}
	else if (0 == strcmp("PAL", m_listOutput.GetItemText(m_iCurSel, 4)))
	{
		m_comboVideoFarmat.SetCurSel(2);
	}
	else
	{
		m_comboVideoFarmat.SetCurSel(0);
	}

	m_comboResolution.SetCurSel(m_comboResolution.FindStringExact(0, m_listOutput.GetItemText(m_iCurSel, 5)));	

	m_comboWinMode.SetCurSel(m_comboWinMode.FindStringExact(0, m_listOutput.GetItemText(m_iCurSel, 6)));

	g_StringLanType(szLan, "真实显示", "realty show");

	if (0 == strcmp(szLan, m_listOutput.GetItemText(m_iCurSel, 7)))
	{
		m_comboScale.SetCurSel(0);
	}
	else
	{
		m_comboScale.SetCurSel(1);
	}

	m_comboPsX.SetCurSel(atoi(m_listOutput.GetItemText(m_iCurSel, 8))/128);

	m_comboPsY.SetCurSel(atoi(m_listOutput.GetItemText(m_iCurSel, 9))/128);
	
	OnSelchangeComboWindowMode();
    m_dwWidth = atoi(m_listOutput.GetItemText(m_iCurSel,11) ); 
    m_dwHeight = atoi(m_listOutput.GetItemText(m_iCurSel,12) ); 

	DWORD dwIndex = m_listOutput.GetItemData(m_iCurSel); 
    m_BVEffcetEnable =  m_struOutputCfg[dwIndex].byEnableVideoEffect;
	NET_DVR_VIDEOEFFECT &struVideoEffect = m_struOutputCfg[dwIndex].struVideoEffect;
	m_byBrightness = 	struVideoEffect.byBrightnessLevel ; 
	m_byContrast = 	struVideoEffect.byContrastLevel ; 
	m_bySharpness = 	struVideoEffect.bySharpnessLevel ;
	m_bySaturation = 	struVideoEffect.bySaturationLevel ;
	m_byHue = 	struVideoEffect.byHueLevel ; 
	m_byGray = struVideoEffect.byGrayLevel; 
	m_BSmarkIR = struVideoEffect.byEnableFunc & 0x1 ? TRUE:FALSE;
	m_BLowLight = struVideoEffect.byEnableFunc & 0x2 ? TRUE:FALSE;
	m_BLightInhibit = struVideoEffect.byEnableFunc & 0x4 ? TRUE:FALSE;
	m_cmbLightInhibit.SetCurSel(-1); 
	if (m_BLightInhibit)
	{
		m_cmbLightInhibit.SetCurSel(struVideoEffect.byLightInhibitLevel-1); 		
	}
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgMatOutputCfg::OnSelchangeComboSubwinNum() 
{
	// TODO: Add your control notification handler code here
	if (m_iCurSel == -1)
	{
		return;
	}

	int iSel = m_comboSubWinNum.GetCurSel();
	m_comboSubWinRes.SetCurSel(m_struOutputCfg[m_iCurSel].struDiff.struVideoPlatform.byDecResolution[iSel] - 1);
}

void CDlgMatOutputCfg::OnBtnResSave() 
{
	// TODO: Add your control notification handler code here
	if (m_iCurSel == -1)
	{
		return;
	}

	m_struOutputCfg[m_iCurSel].struDiff.struVideoPlatform.byDecResolution[m_comboSubWinNum.GetCurSel()] = m_comboSubWinRes.GetCurSel() + 1;
}

void CDlgMatOutputCfg::OnSelchangeComboWindowMode() 
{
	// TODO: Add your control notification handler code here
	if (m_comboWinMode.GetCurSel() == -1)
	{
		return;
	}
	
	DWORD dwMaxSubWinNum = m_comboWinMode.GetItemData(m_comboWinMode.GetCurSel());
	int i = 0;
	CString cs;

	m_comboSubWinNum.ResetContent();
	for (i = 0; i < dwMaxSubWinNum; i++)
	{
		cs.Format("%d", i + 1);
		m_comboSubWinNum.AddString(cs);
	}
}

void CDlgMatOutputCfg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
