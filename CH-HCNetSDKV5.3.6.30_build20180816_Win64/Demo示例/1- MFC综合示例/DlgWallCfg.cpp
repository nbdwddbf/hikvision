// DlgWallCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWallCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWallCfg dialog


CDlgWallCfg::CDlgWallCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWallCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWallCfg)
	m_bEnable = FALSE;
	m_bDzd = FALSE;
	m_bFgb = FALSE;
	m_bQgyz = FALSE;
	m_byBrightness = 0;
	m_byContrast = 0;
	m_byGray = 0;
	m_byHue = 0;
	m_bySaturation = 0;
	m_bySharpness = 0;
	//}}AFX_DATA_INIT
}


void CDlgWallCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWallCfg)
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
	DDX_Control(pDX, IDC_COMBO_OUTPUT, m_comboOutput);
	DDX_Control(pDX, IDC_COMBO_LEVEL, m_comboLevel);
	DDX_Control(pDX, IDC_LIST_SCREEN, m_listScreen);
	DDX_Control(pDX, IDC_COMBO_Y, m_comboY);
	DDX_Control(pDX, IDC_COMBO_X, m_comboX);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHK_DZD, m_bDzd);
	DDX_Check(pDX, IDC_CHK_FGB, m_bFgb);
	DDX_Check(pDX, IDC_CHK_QGYZ, m_bQgyz);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_byBrightness);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_byContrast);
	DDX_Text(pDX, IDC_EDIT_GRAY, m_byGray);
	DDX_Text(pDX, IDC_EDIT_HUE, m_byHue);
	DDX_Text(pDX, IDC_EDIT_SATURATION, m_bySaturation);
	DDX_Text(pDX, IDC_EDIT_SHARPNESS, m_bySharpness);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWallCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgWallCfg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)	
	ON_NOTIFY(NM_CLICK, IDC_LIST_SCREEN, OnClickListScreen)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_SAVE_CFG, OnBtnSaveCfg)
	ON_BN_CLICKED(IDC_BTN_SET_CFG, OnBtnSetCfg)
	ON_BN_CLICKED(IDC_BTN_GET_CFG, OnBtnGetCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT, OnSelchangeComboOutput)
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
	ON_BN_CLICKED(IDC_BTN_UPDATE_OUTPUT, OnBtnUpdateOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWallCfg message handlers

BOOL CDlgWallCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_dwCount = 0;
	m_dwDispNum = 0;
	m_iCurSel = -1;
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	memset(m_lDispChan, 0, sizeof(m_lDispChan));
	memset(m_lDispChanSet, 0, sizeof(m_lDispChanSet));
	memset(m_dwStatus, 0, sizeof(m_dwStatus));
	memset(m_struWallParam, 0, sizeof(m_struWallParam));
	memset(&m_struAblity, 0, sizeof(m_struAblity));
	memset(&m_struWallParamSet, 0, sizeof(m_struWallParamSet));

	memset(&m_struOutput, 0, sizeof(m_struOutput));
	memset(&m_struOutputSet, 0, sizeof(m_struOutputSet));
	memset(&m_lDispOutputSet, 0, sizeof(m_lDispOutputSet));
	m_dwOutputSet = 0;
	CString tmp;
// 	if (!NET_DVR_GetDeviceAbility(m_lUserID, MATRIXDECODER_ABILITY_V41, NULL, 0, (char*)&m_struAblity, sizeof(NET_DVR_MATRIX_ABILITY_V41)))
//     {
//         tmp.Format("Error code : %d", NET_DVR_GetLastError());
//         AfxMessageBox(tmp);
//         return FALSE;
//     }
	int i = 0;
    int ChanNo = -1;
    char szLan[128] = {0};

	
	m_listScreen.SetExtendedStyle(m_listScreen.GetExtendedStyle()|LVS_EX_FULLROWSELECT);

    g_StringLanType(szLan, "显示通道号", "DispChan No.");
	m_listScreen.InsertColumn(0, szLan, LVCFMT_LEFT,80, -1);	
	m_listScreen.InsertColumn(1, "X",LVCFMT_LEFT,80,-1);
    m_listScreen.InsertColumn(2, "Y",LVCFMT_LEFT,80,-1);	
	g_StringLanType(szLan, "使能", "Enable");
	m_listScreen.InsertColumn(3, szLan,LVCFMT_LEFT,120,-1);
	
	
// 	for(i = 0; i < m_struAblity.struBncInfo.byChanNums; i++)
//     {
//         m_lDispChan[m_dwDispNum] = m_struAblity.struBncInfo.byStartChan + i;		
// 		m_dwDispNum++;
//     }
// 	
// 	for(i = 0; i < m_struAblity.struVgaInfo.byChanNums; i++)
//     {
//         m_lDispChan[m_dwDispNum] = m_struAblity.struVgaInfo.byStartChan + i;        
// 		m_dwDispNum++;
//     }
// 	
// 	for(i = 0; i < m_struAblity.struHdmiInfo.byChanNums; i++)
//     {
//         m_lDispChan[m_dwDispNum] = m_struAblity.struHdmiInfo.byStartChan + i;        
// 		m_dwDispNum++;
//     }
// 	
// 	for(i = 0; i < m_struAblity.struDviInfo.byChanNums; i++)
//     {
//         m_lDispChan[m_dwDispNum] = m_struAblity.struDviInfo.byStartChan + i;
//         m_dwDispNum++;
//     }

	OnBtnGetAll();
	
    
	i = 0;
	m_comboResolution.AddString("SVGA_60HZ");
	m_comboResolution.SetItemData(i++, SVGA_60HZ);
	m_comboResolution.AddString("SVGA_75HZ");
	m_comboResolution.SetItemData(i++, SVGA_75HZ);
	m_comboResolution.AddString("XGA_60HZ");
	m_comboResolution.SetItemData(i++, XGA_60HZ);
	m_comboResolution.AddString("XGA_75HZ");
	m_comboResolution.SetItemData(i++, XGA_75HZ);
	m_comboResolution.AddString("SXGA_60HZ");
	m_comboResolution.SetItemData(i++, SXGA_60HZ);
	m_comboResolution.AddString("SXGA2_60HZ");
	m_comboResolution.SetItemData(i++, SXGA2_60HZ);
	m_comboResolution.AddString("_720P_60HZ");
	m_comboResolution.SetItemData(i++, _720P_60HZ);
	m_comboResolution.AddString("_720P_50HZ");
	m_comboResolution.SetItemData(i++, _720P_50HZ);
	m_comboResolution.AddString("_1080I_60HZ");
	m_comboResolution.SetItemData(i++, _1080I_60HZ);
	m_comboResolution.AddString("_1080I_50HZ");
	m_comboResolution.SetItemData(i++, _1080I_50HZ);
	m_comboResolution.AddString("_1080P_60HZ");
	m_comboResolution.SetItemData(i++, _1080P_60HZ);
	m_comboResolution.AddString("_1080P_50HZ");
	m_comboResolution.SetItemData(i++, _1080P_50HZ);
	m_comboResolution.AddString("_1080P_30HZ");
	m_comboResolution.SetItemData(i++, _1080P_30HZ);
	m_comboResolution.AddString("_1080P_25HZ");
	m_comboResolution.SetItemData(i++, _1080P_25HZ);
	m_comboResolution.AddString("_1080P_24HZ");
	m_comboResolution.SetItemData(i++, _1080P_24HZ);
	m_comboResolution.AddString("UXGA_60HZ");
	m_comboResolution.SetItemData(i++, UXGA_60HZ);
	m_comboResolution.AddString("UXGA_30HZ");
	m_comboResolution.SetItemData(i++, UXGA_30HZ);
	m_comboResolution.AddString("WSXGA_60HZ");
	m_comboResolution.SetItemData(i++, WSXGA_60HZ);
	m_comboResolution.AddString("WUXGA_60HZ");
	m_comboResolution.SetItemData(i++, WUXGA_60HZ);
	m_comboResolution.AddString("WUXGA_30HZ");
	m_comboResolution.SetItemData(i++, WUXGA_30HZ);

	OnBtnUpdateOutput();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWallCfg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_iCurSel == -1)
	{
		g_StringLanType(szLan, "请选择显示通道", "Please select display channel");
		AfxMessageBox(szLan);
		return;
	}
	if (m_comboX.GetCurSel() == CB_ERR || m_comboY.GetCurSel() == CB_ERR)
	{
		g_StringLanType(szLan, "请选择坐标", "Please select Coordinate");
		AfxMessageBox(szLan);
		return;
	}
	int i = 0;
	LONG lDispChan = m_listScreen.GetItemData(m_iCurSel);
	for (i = 0; i < MAX_COUNT; i++)
	{
		if (m_lDispChanSet[i] == lDispChan)
		{
			break;
		}
		if (m_lDispChanSet[i] == 0)
		{
			m_lDispChanSet[i] = lDispChan;
            m_dwCount++;
			break;
		}
	}
	m_struWallParamSet[i].dwSize = sizeof(NET_DVR_SINGLEWALLPARAM);
	m_struWallParamSet[i].byEnable = m_bEnable;	
	m_struWallParamSet[i].dwWallNum = m_lDispChanSet[i];
	m_struWallParamSet[i].struRectCfg.wXCoordinate = WIDTH * m_comboX.GetCurSel();
	m_struWallParamSet[i].struRectCfg.wYCoordinate = HEIGHT * m_comboY.GetCurSel();
   
	sprintf(szLan, "%d", m_struWallParamSet[i].struRectCfg.wXCoordinate);
	m_listScreen.SetItemText(m_iCurSel, 1, szLan);
	sprintf(szLan, "%d", m_struWallParamSet[i].struRectCfg.wYCoordinate);
	m_listScreen.SetItemText(m_iCurSel, 2, szLan);
	if (m_bEnable)
	{
		sprintf(szLan, "Enable");
	}
	else
	{
		sprintf(szLan, "Disable");
	}
	m_listScreen.SetItemText(m_iCurSel, 3, szLan);
	UpdateData(FALSE);
}

void CDlgWallCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	char cs[2048] = {0};
	BOOL bOneFail = FALSE;
	CString csTemp;
	int i = 0;
	int j = 0;
	if (m_dwCount == 0)
	{
		if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_MATRIX_WALL_SET, m_dwDispNum, m_lDispChan, 4 * m_dwDispNum, m_dwStatus, m_struWallParam, m_dwDispNum * sizeof(NET_DVR_SINGLEWALLPARAM)))
		{
			i = NET_DVR_GetLastError();
			sprintf(cs, "error code: %d", i);
			AfxMessageBox(cs);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MATRIX_WALL_SET");
		    return;
		}

		sprintf(cs, "Not succeed:\n");
		for (i = 0; i < m_dwDispNum; i++)
		{
			if (m_dwStatus[i] > 0)
			{
				csTemp = m_listScreen.GetItemText(i, 0);
				sprintf(cs, "%sDispchan: %s\n", cs, csTemp);
				bOneFail = TRUE;
			}
		}
		
		if (bOneFail)
		{
			AfxMessageBox(cs);			
			
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MATRIX_WALL_SET");
			m_dwCount = 0;			
		}
	}
	else
	{
		if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_MATRIX_WALL_SET, m_dwCount, m_lDispChanSet, 4 * m_dwCount, m_dwStatus, m_struWallParamSet, m_dwCount * sizeof(NET_DVR_SINGLEWALLPARAM)))
		{
			i = NET_DVR_GetLastError();
			sprintf(cs, "error code: %d", i);
			AfxMessageBox(cs);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MATRIX_WALL_SET");
			return;
		}
		
		sprintf(cs, "Not succeed:\n");
		for (i = 0; i < m_dwCount; i++)
		{
			if (m_dwStatus[i] > 0)
			{
				for(j = 0; j < m_dwDispNum; j++)
				{
					if (m_lDispChanSet[i] == m_lDispChan[j])
					{
						csTemp = m_listScreen.GetItemText(j, 0);
						sprintf(cs, "%sDispchan: %s\n", cs, csTemp);
				        bOneFail = TRUE;
					}

				}
				
			}
		}
		
		if (bOneFail)
		{
			AfxMessageBox(cs);			
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MATRIX_WALL_SET");			
		}

		m_dwCount = 0;
		memset(m_lDispChanSet, 0, sizeof(m_lDispChanSet));
		memset(m_dwStatus, 0, sizeof(m_dwStatus));
		memset(m_struWallParamSet, 0, sizeof(m_struWallParamSet));
	}
	
}

void CDlgWallCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	BOOL bOneFail = FALSE;
	char cs[2048] = {0};
	CString csTemp;
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_MATRIX_WALL_GET, m_dwDispNum, m_lDispChan, m_dwDispNum * 4, m_dwStatus, m_struWallParam, m_dwDispNum * sizeof(NET_DVR_SINGLEWALLPARAM)))
	{
        i = NET_DVR_GetLastError();
		sprintf(cs, "error code: %d", i);
		AfxMessageBox(cs);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MATRIX_WALL_GET");		
		//return;
	}

	sprintf(cs, "Not succeed:\n");
	for (i = 0; i < m_dwDispNum; i++)
	{
        if (m_dwStatus[i] > 0)
        {
			csTemp = m_listScreen.GetItemText(i, 0);
			sprintf(cs, "%sDispchan: %s\n", cs, csTemp);
			bOneFail = TRUE;
        }
	}
	
	if (bOneFail)
	{
		AfxMessageBox(cs);
		m_dwCount = 0;		
		memset(m_dwStatus, 0, sizeof(m_dwStatus));
	    memset(m_struWallParamSet, 0, sizeof(m_struWallParamSet));
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MATRIX_WALL_GET");
		m_dwCount = 0;		
		memset(m_dwStatus, 0, sizeof(m_dwStatus));
	    memset(m_struWallParamSet, 0, sizeof(m_struWallParamSet));
	}
	m_listScreen.DeleteAllItems();
	DrawList();
}

void CDlgWallCfg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgWallCfg::DrawList()
{
	int i = 0;
	int j = 0;
	char szLan[128] = {0};
	for(i = 0; i < m_dwDispNum; i++)
	{
// 		if (i < m_struAblity.struBncInfo.byChanNums)
// 		{
//             sprintf(szLan, "BNC %d", i+1);			
// 		}
// 		else if (i < m_struAblity.struBncInfo.byChanNums + m_struAblity.struVgaInfo.byChanNums)
// 		{
// 			sprintf(szLan, "VGA %d", i + 1 - m_struAblity.struBncInfo.byChanNums);
// 		}
// 		else if (i < m_struAblity.struBncInfo.byChanNums + m_struAblity.struVgaInfo.byChanNums + m_struAblity.struHdmiInfo.byChanNums)
// 		{
// 			sprintf(szLan, "HDMI %d", i + 1 - m_struAblity.struBncInfo.byChanNums - m_struAblity.struVgaInfo.byChanNums);
// 		}
// 		else if (i < m_dwDispNum)
// 		{
// 			sprintf(szLan, "DVI %d", i + 1 - m_struAblity.struBncInfo.byChanNums - m_struAblity.struVgaInfo.byChanNums - m_struAblity.struHdmiInfo.byChanNums);
// 		}
// 		else
// 		{
// 			continue;
// 		}

		sprintf(szLan, "%d", m_struWallParam[i].dwWallNum);
		m_listScreen.InsertItem(j, szLan, 0);
		sprintf(szLan, "%d", m_struWallParam[i].struRectCfg.wXCoordinate);
		m_listScreen.SetItemText(j, 1, szLan);
		sprintf(szLan, "%d", m_struWallParam[i].struRectCfg.wYCoordinate);
		m_listScreen.SetItemText(j, 2, szLan);
		if (m_struWallParam[i].byEnable == 0)
		{
			sprintf(szLan, "Disable");
		}
		else
		{
			sprintf(szLan, "Enable");
		}
		m_listScreen.SetItemText(j, 3, szLan);
		m_listScreen.SetItemData(j, m_lDispChan[i]);
		j++;
	}
}

void CDlgWallCfg::OnClickListScreen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION  iPos = m_listScreen.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
 	m_iCurSel = m_listScreen.GetNextSelectedItem(iPos);

	m_bEnable = m_struWallParam[m_iCurSel].byEnable;
	m_comboX.SetCurSel(m_struWallParam[m_iCurSel].struRectCfg.wXCoordinate/WIDTH);
	m_comboY.SetCurSel(m_struWallParam[m_iCurSel].struRectCfg.wYCoordinate/HEIGHT);

	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgWallCfg::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	BOOL bOneFail = FALSE;
	char cs[2048] = {0};
	CString csTemp;
	char *pTemp = new char[4 + MAX_COUNT * sizeof(NET_DVR_SINGLEWALLPARAM)];
	memset(pTemp, 0, 4 + MAX_COUNT * sizeof(NET_DVR_SINGLEWALLPARAM));
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_MATRIX_WALL_GET, 0xffffffff, NULL, 0, NULL, pTemp, 4 + MAX_COUNT * sizeof(NET_DVR_SINGLEWALLPARAM)))
	{
        i = NET_DVR_GetLastError();
		sprintf(cs, "error code: %d", i);
		AfxMessageBox(cs);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MATRIX_WALL_GET");		
		//return;
	}
	
// 	sprintf(cs, "Not succeed:\n");
// 	for (i = 0; i < m_dwDispNum; i++)
// 	{
//         if (m_dwStatus[i] > 0)
//         {
// 			csTemp = m_listScreen.GetItemText(i, 0);
// 			sprintf(cs, "%sDispchan: %s\n", cs, csTemp);
// 			bOneFail = TRUE;
//         }
// 	}
// 	
// 	if (bOneFail)
// 	{
// 		AfxMessageBox(cs);
// 		m_dwCount = 0;		
// 		memset(m_dwStatus, 0, sizeof(m_dwStatus));
// 		memset(m_struWallParamSet, 0, sizeof(m_struWallParamSet));
// 	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MATRIX_WALL_GET");
		m_dwDispNum = *((DWORD*)pTemp);	
		memcpy(&m_struWallParam, pTemp + 4, m_dwDispNum * sizeof(NET_DVR_SINGLEWALLPARAM));
		for (i = 0; i<m_dwDispNum; i++)
		{
			m_lDispChan[i] = m_struWallParam[i].dwWallNum;
		}
		memset(m_dwStatus, 0, sizeof(m_dwStatus));
		memset(m_struWallParamSet, 0, sizeof(m_struWallParamSet));

		m_comboOutput.ResetContent();
		for (i = 0; i<m_dwDispNum; i++)
		{			
			sprintf(cs, "%d", m_lDispChan[i]);
			m_comboOutput.AddString(cs);
			m_comboOutput.SetItemData(i, m_lDispChan[i]);
		}
	}
	delete []pTemp;
	m_listScreen.DeleteAllItems();
	DrawList();
}

void CDlgWallCfg::OnBtnSaveCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128];	
	int i = 0;
	int iSel = m_comboOutput.GetCurSel();
	if (iSel == -1)
	{
		g_StringLanType(szLan, "请选择显示输出号", "please select output No.");
		AfxMessageBox(szLan);
		return;
	}

	if (m_comboResolution.GetCurSel() == CB_ERR)
	{
		g_StringLanType(szLan, "请选择分辨率", "please select resolution");
		AfxMessageBox(szLan);
		return;
	}
	
	
	for (i = 0; i < MAX_COUNT; i++)
	{
		
		if (m_lDispChan[iSel] == m_lDispOutputSet[i])
		{
			break;
		}
		

		if (m_lDispOutputSet[i] == 0)
		{
			m_lDispOutputSet[i] = m_lDispChan[iSel];
            m_dwOutputSet++;
			break;
		}
	}

	m_struOutputSet[i].dwSize = sizeof(NET_DVR_WALLOUTPUTPARAM);
	m_struOutputSet[i].dwResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
	m_struOutputSet[i].struRes.byBrightnessLevel = m_byBrightness;
	m_struOutputSet[i].struRes.byContrastLevel = m_byContrast;
	m_struOutputSet[i].struRes.bySharpnessLevel = m_bySharpness;
	m_struOutputSet[i].struRes.bySaturationLevel = m_bySaturation;
	m_struOutputSet[i].struRes.byHueLevel = m_byHue;
	m_struOutputSet[i].struRes.byEnableFunc = (BYTE)(m_bFgb | (m_bDzd << 1) | (m_bQgyz << 2));
	if (m_comboLevel.GetCurSel() != CB_ERR)
	{
		m_struOutputSet[i].struRes.byLightInhibitLevel = m_comboLevel.GetCurSel() + 1;
	}
	m_struOutputSet[i].struRes.byGrayLevel = m_byGray;
}

void CDlgWallCfg::OnBtnSetCfg() 
{
	// TODO: Add your control notification handler code here
	char cs[2048] = {0};
	BOOL bOneFail = FALSE;
	CString csTemp;
	int i = 0;
	int j = 0;
	if (m_dwOutputSet == 0)
	{
		if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_WALLOUTPUT_SET, m_dwDispNum, m_lDispChan, 4 * m_dwDispNum, m_dwStatus, m_struOutput, m_dwDispNum * sizeof(NET_DVR_WALLOUTPUTPARAM)))
		{
			i = NET_DVR_GetLastError();
			sprintf(cs, "error code: %d", i);
			AfxMessageBox(cs);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLOUTPUT_SET");
			return;
		}
		
		sprintf(cs, "Not succeed:\n");
		for (i = 0; i < m_dwDispNum; i++)
		{
			if (m_dwStatus[i] > 0)
			{
				csTemp = m_listScreen.GetItemText(i, 0);
				sprintf(cs, "%sDispchan: %s\n", cs, csTemp);
				bOneFail = TRUE;
			}
		}
		
		if (bOneFail)
		{
			AfxMessageBox(cs);			
			
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLOUTPUT_SET");
			m_dwCount = 0;			
		}
	}
	else
	{
		if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_WALLOUTPUT_SET, m_dwOutputSet, m_lDispOutputSet, 4 * m_dwOutputSet, m_dwStatus, m_struOutputSet, m_dwOutputSet * sizeof(NET_DVR_WALLOUTPUTPARAM)))
		{
			i = NET_DVR_GetLastError();
			sprintf(cs, "error code: %d", i);
			AfxMessageBox(cs);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLOUTPUT_SET");
			return;
		}
		
		sprintf(cs, "Not succeed:\n");
		for (i = 0; i < m_dwOutputSet; i++)
		{
			if (m_dwStatus[i] > 0)
			{
				sprintf(cs, "%sDispChan: %d", cs, m_lDispOutputSet[i]);
				bOneFail = TRUE;				
			}
		}
		
		if (bOneFail)
		{
			AfxMessageBox(cs);			
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLOUTPUT_SET");			
		}
		
		m_dwOutputSet = 0;
		memset(m_lDispOutputSet, 0, sizeof(m_lDispOutputSet));
		memset(m_dwStatus, 0, sizeof(m_dwStatus));
		memset(m_struOutputSet, 0, sizeof(m_struOutputSet));
	}
}

void CDlgWallCfg::OnBtnGetCfg() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_comboOutput.GetCurSel() == CB_ERR)
	{
		g_StringLanType(szLan, "请选择显示输出号", "please select output channel No.");
		AfxMessageBox(szLan);
		return;
	}

	DWORD dwStatus = 0;
	int i = 0;
	DWORD dwOutputNum = m_comboOutput.GetItemData(m_comboOutput.GetCurSel());
	NET_DVR_WALLOUTPUTPARAM struTemp = {0};
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_WALLOUTPUT_GET, 1, &dwOutputNum, 4, &dwStatus, &struTemp, sizeof(struTemp)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLOUTPUT_GET");
		g_StringLanType(szLan, "获取失败", "Get fail");
		AfxMessageBox(szLan);
	}
	else
	{
		for(int i = 0; i<m_comboResolution.GetCount(); i++)
		{
			if (struTemp.dwResolution == m_comboResolution.GetItemData(i))
			{
				m_comboResolution.SetCurSel(i);
				break;
			}
		}

		m_byBrightness = struTemp.struRes.byBrightnessLevel;
		m_byContrast = struTemp.struRes.byContrastLevel;
		m_bySharpness = struTemp.struRes.bySharpnessLevel;
		m_bySaturation = struTemp.struRes.bySaturationLevel;
		m_byHue = struTemp.struRes.byHueLevel;

		m_bFgb = struTemp.struRes.byEnableFunc & 0x01;
		m_bDzd = struTemp.struRes.byEnableFunc & 0x02;
		m_bQgyz = struTemp.struRes.byEnableFunc & 0x04;

		m_comboLevel.SetCurSel(struTemp.struRes.byLightInhibitLevel);
		m_byGray = struTemp.struRes.byGrayLevel;

		memcpy(&m_struOutput[m_comboOutput.GetCurSel()], &struTemp, sizeof(NET_DVR_WALLOUTPUTPARAM));

		UpdateData(FALSE);

		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLOUTPUT_GET");
		
		memset(&m_struOutputSet, 0, sizeof(m_struOutputSet));
		memset(&m_lDispOutputSet, 0, sizeof(m_lDispOutputSet));
		m_dwOutputSet = 0;
	}
}


void CDlgWallCfg::OnSelchangeComboOutput() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_comboOutput.GetCurSel();
	if (iSel == CB_ERR)
	{
		return;
	}
	int i = 0;

	for(i = 0; i<m_comboResolution.GetCount(); i++)
	{
		if (m_struOutput[iSel].dwResolution == m_comboResolution.GetItemData(i))
		{
			m_comboResolution.SetCurSel(i);
			break;
		}
	}
	
	m_byBrightness = m_struOutput[iSel].struRes.byBrightnessLevel;
	m_byContrast = m_struOutput[iSel].struRes.byContrastLevel;
	m_bySharpness = m_struOutput[iSel].struRes.bySharpnessLevel;
	m_bySaturation = m_struOutput[iSel].struRes.bySaturationLevel;
	m_byHue = m_struOutput[iSel].struRes.byHueLevel;
	
	m_bFgb = m_struOutput[iSel].struRes.byEnableFunc & 0x01;
	m_bDzd = m_struOutput[iSel].struRes.byEnableFunc & 0x02;
	m_bQgyz = m_struOutput[iSel].struRes.byEnableFunc & 0x04;
	
	m_comboLevel.SetCurSel(m_struOutput[iSel].struRes.byLightInhibitLevel);
	m_byGray = m_struOutput[iSel].struRes.byGrayLevel;	
	
	UpdateData(FALSE);
	
}

void CDlgWallCfg::OnBtnUpdateOutput() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	BOOL bOneFail = FALSE;
	char cs[2048] = {0};
	CString csTemp;
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_WALLOUTPUT_GET, m_dwDispNum, m_lDispChan, m_dwDispNum * 4, m_dwStatus, m_struOutput, m_dwDispNum * sizeof(NET_DVR_WALLOUTPUTPARAM)))
	{
        i = NET_DVR_GetLastError();
		sprintf(cs, "error code: %d", i);
		AfxMessageBox(cs);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLOUTPUT_GET");		
		return;
	}
	
	sprintf(cs, "Not succeed:\n");
	for (i = 0; i < m_dwDispNum; i++)
	{
        if (m_dwStatus[i] > 0)
        {
			
			sprintf(cs, "%sDispchan: %d\n", cs, m_lDispChan[i]);
			bOneFail = TRUE;
        }
	}
	
	if (bOneFail)
	{
		AfxMessageBox(cs);
		m_dwOutputSet = 0;		
		memset(m_dwStatus, 0, sizeof(m_dwStatus));
		memset(m_struOutputSet, 0, sizeof(m_struOutputSet));
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLOUTPUT_GET");
		m_dwCount = 0;		
		memset(m_dwStatus, 0, sizeof(m_dwStatus));
		memset(m_struWallParamSet, 0, sizeof(m_struWallParamSet));
	}

	OnSelchangeComboOutput();
}
