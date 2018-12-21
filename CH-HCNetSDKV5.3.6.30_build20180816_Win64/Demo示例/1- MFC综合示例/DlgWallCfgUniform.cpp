// DlgWallCfgUniform.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWallCfgUniform.h"
#include  "DlgWallWinVideoWall.h"
#include "DlgWallVirLED.h"
#include "DlgWallControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWallCfg_Uniform dialog


CDlgWallCfg_Uniform::CDlgWallCfg_Uniform(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWallCfg_Uniform::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWallCfg_Uniform)
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
	m_byWallNo = 1;
	m_dwOutputNum = 0;
	m_dwDisplayNoC = 0;
	m_BShowC = FALSE;
	m_BAllDisplayNo = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgWallCfg_Uniform::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWallCfg_Uniform)
	DDX_Control(pDX, IDC_COMB_VWSC_CHANTYPE, m_CmChanTypeC);
	DDX_Control(pDX, IDC_COMB_VIDEOWALL_VIDEOFORMAT, m_combVideoFormat);
	DDX_Control(pDX, IDC_COMB_VIDEOWALL_BACKGROUND, m_combBackGround);
	DDX_Control(pDX, IDC_COMB_VIDEOWALL_DISPLAYMODE, m_combDisplayMode);
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
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_WALLNO, m_byWallNo);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_OUTPUTNUM, m_dwOutputNum);
	DDX_Text(pDX, IDC_EDT_VWSC_DISPLAYNO, m_dwDisplayNoC);
	DDX_Check(pDX, IDC_CHK_VWSC_ENABLE, m_BShowC);
	DDX_Check(pDX, IDC_CHK_VWS_ALLDISPLAYNO, m_BAllDisplayNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWallCfg_Uniform, CDialog)
	//{{AFX_MSG_MAP(CDlgWallCfg_Uniform)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)	
	ON_NOTIFY(NM_CLICK, IDC_LIST_SCREEN, OnClickListScreen)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_SAVE_CFG, OnBtnSaveCfg)
	ON_BN_CLICKED(IDC_BTN_SET_CFG, OnBtnSetCfg)
	ON_BN_CLICKED(IDC_BTN_GET_CFG, OnBtnGetCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT, OnSelchangeComboOutput)
	ON_BN_CLICKED(IDC_BTN_UPDATE_OUTPUT, OnBtnUpdateOutput)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BUT_VIDEOWALL_CONTROL, OnButVideowallControl)
	ON_BN_CLICKED(IDC_BUT_VWSC_SEND, OnButVwscSend)
	ON_BN_CLICKED(IDC_CHK_VWS_ALLDISPLAYNO, OnChkVwsAlldisplayno)
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
	ON_BN_CLICKED(IDC_BUT_DISPLAYPARAM_ALLSAME, OnButDispParamAllSame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWallCfg_Uniform message handlers

BOOL CDlgWallCfg_Uniform::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_dwCount = 0;
	m_dwDispNum = 0;
	m_iCurSel = -1;
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    memset(m_ModifyChan, 0, sizeof(m_ModifyChan)); 
	memset(m_lDispChan, 0, sizeof(m_lDispChan));
	memset(m_lDispChanSet, 0, sizeof(m_lDispChanSet));
	memset(m_dwStatus, 0, sizeof(m_dwStatus));
	memset(m_struWallParam, 0, sizeof(m_struWallParam));
	memset(&m_struAblity, 0, sizeof(m_struAblity));
	memset(&m_struWallParamSet, 0, sizeof(m_struWallParamSet));

    m_lPapamCount = 0; 
    m_lRecordCount = 0; 
	memset(&m_struOutput, 0, sizeof(m_struOutput));
	memset(&m_struOutputSet, 0, sizeof(m_struOutputSet));
	memset(&m_lDispOutputSet, 0, sizeof(m_lDispOutputSet));
    memset(m_dwRecordPapam, 0, sizeof(m_dwRecordPapam)); 
	m_dwOutputSet = 0;
	CString tmp;
	int i = 0;
    int ChanNo = -1;
    char szLan[128] = {0};

	
	m_listScreen.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "显示输出号", "DispChan No.");
	m_listScreen.InsertColumn(0, szLan, LVCFMT_LEFT,80, -1);	
    g_StringLanType(szLan, "墙号", "VideoWall No.");
    m_listScreen.InsertColumn(1, szLan,LVCFMT_LEFT,80, -1); 
	m_listScreen.InsertColumn(2, "X",LVCFMT_LEFT,80,-1);
    m_listScreen.InsertColumn(3, "Y",LVCFMT_LEFT,80,-1);	
	g_StringLanType(szLan, "使能", "Enable");
	m_listScreen.InsertColumn(4, szLan,LVCFMT_LEFT,80,-1);
	g_StringLanType(szLan, "连接模式", "LinkMode");
    m_listScreen.InsertColumn(5, szLan,LVCFMT_LEFT,120,-1);
//	OnBtnGetAll();
	
    
	i = 0;
	m_comboResolution.AddString("SVGA_60HZ");
	m_comboResolution.SetItemData(i++, SVGA_60HZ);
	m_comboResolution.AddString("SVGA_75HZ");
	m_comboResolution.SetItemData(i++, SVGA_75HZ);
	m_comboResolution.AddString("XGA_60HZ");
    DWORD test = XGA_60HZ; 
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
    
    m_combDisplayMode.SetCurSel(0); 
    InitOutputLinkMode(); 
    OnBtnGetAll(); 
	OnBtnUpdateOutput();
    m_CmChanTypeC.SetCurSel(0); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWallCfg_Uniform::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_comboX.GetCurSel() == CB_ERR || m_comboY.GetCurSel() == CB_ERR)
	{
		g_StringLanType(szLan, "请选择坐标", "Please select Coordinate");
		AfxMessageBox(szLan);
		return;
	}
    NET_DVR_VIDEOWALLDISPLAYPOSITION struDisplayPos ={0}; 
    UpdateDisplayPos(struDisplayPos); 
    UpdateOutputNum(struDisplayPos);

    DrawList(); 
	UpdateData(FALSE);
    
}

void CDlgWallCfg_Uniform::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	memset(m_dwStatus, 0, sizeof(m_dwStatus)); 
    LPNET_DVR_VIDEOWALLDISPLAYPOSITION lpDisplayPos = GetModifyDisplayPos();
    LONG *  lDisplayChan = GetModifyChan(); 
    char csError[1024]={0};
    char csNum[128] = {0};
    if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_VIDEOWALLDISPLAYPOSITION, m_dwCount, lDisplayChan, 4 * m_dwCount, m_dwStatus, lpDisplayPos, m_dwCount * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION)))
    {
        sprintf(csError, "设置修改失败, Error code: %d", NET_DVR_GetLastError());
        AfxMessageBox(csError);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEOWALLDISPLAYPOSITION");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEOWALLDISPLAYPOSITION");
    int i = 0; 
    BOOL bOneFail = FALSE; 
    for (i = 0; i <m_dwCount; i++)
    {
        if (m_dwStatus[i] > 0)
        {
            sprintf(csNum, "%d ", lpDisplayPos[i].dwDisplayNo);
            strcat(csError, csNum); 
            bOneFail = TRUE;
	    } 	
    }
    if (bOneFail)
    {
//        sprintf(csError, "the outputnum failed to set: %s ", csError); 
        AfxMessageBox(csError); 
        return ; 
    }
    OnBtnGetAll(); 
	
}

//输出号位置获取
void CDlgWallCfg_Uniform::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    POSITION  iPos = m_listScreen.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
	}
    NET_DVR_VIDEOWALLDISPLAYPOSITION struDisplayPos={0}; 
    struDisplayPos.dwSize = sizeof(struDisplayPos); 
    DWORD dwDispChan = m_dwOutputNum; 
	CString csTemp;
    char szLan[128]={0}; 
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYPOSITION, 1, &dwDispChan, sizeof(dwDispChan), NULL, &struDisplayPos, sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION)))
	{
		sprintf(szLan, "刷新该项失败, Error code %d",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLDISPLAYPOSITION");		
		//return;
	}
    else
    {
        NewOutputNum(struDisplayPos); 
        DrawList(); 
    }
}

void CDlgWallCfg_Uniform::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgWallCfg_Uniform::DrawList()
{
    m_listScreen.DeleteAllItems(); 
	int i = 0;
	int j = 0;
	char szLan[128] = {0};
	for(i = 0; i < m_dwDispNum; i++)
	{
		sprintf(szLan, "%d_%d_%d", m_struWallParam[i].dwDisplayNo>>24, (m_struWallParam[i].dwDisplayNo>>16) &0xff, (m_struWallParam[i].dwDisplayNo&0xffff));
		m_listScreen.InsertItem(i, szLan);
        sprintf(szLan, "%d", (m_struWallParam[i].dwVideoWallNo>>24)); 
        m_listScreen.SetItemText(i, 1, szLan);
		sprintf(szLan, "%d", m_struWallParam[i].struRectCfg.dwXCoordinate);
		m_listScreen.SetItemText(i, 2, szLan);
		sprintf(szLan, "%d", m_struWallParam[i].struRectCfg.dwYCoordinate);
		m_listScreen.SetItemText(i, 3, szLan);
		if (m_struWallParam[i].byEnable == 0)
		{
			sprintf(szLan, "Disable");
		}
		else
		{
			sprintf(szLan, "Enable");
		}
		m_listScreen.SetItemText(i, 4, szLan);
		m_listScreen.SetItemData(i, m_struWallParam[i].dwDisplayNo);
        //从现在位置寻找循环，可能快点
        int j=i; 
        BYTE byLinkMode=0xff; 
        do 
        {
            if (m_struDisplayCfg.struDisplayParam[j].dwDisplayNo == m_struWallParam[i].dwDisplayNo)
            {
                byLinkMode = m_struDisplayCfg.struDisplayParam[j].byDispChanType; 
            }
            j++; 
        } while ((j%MAX_DISPLAY_NUM) != i);
        switch (byLinkMode)
        {
        case 1:
            sprintf(szLan, "BNC");
            break; 
        case 2:
            sprintf(szLan, "VGA");
            break; 
        case 3:
            sprintf(szLan, "HDMI");
            break; 
        case 4:
            sprintf(szLan, "DVI");
            break; 
        case 0xff:
            sprintf(szLan, "无效");
            break;
        default:
            sprintf(szLan, "");
        }
        m_listScreen.SetItemText(i, 5, szLan);
	}
}


void CDlgWallCfg_Uniform::OnClickListScreen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION  iPos = m_listScreen.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
 	m_iCurSel = m_listScreen.GetNextSelectedItem(iPos);
    m_dwOutputNum = m_struWallParam[m_iCurSel].dwDisplayNo;  
	m_bEnable = m_struWallParam[m_iCurSel].byEnable;
	m_byWallNo = (BYTE)(m_struWallParam[m_iCurSel].dwVideoWallNo>>24); 
    m_comboX.SetCurSel(m_struWallParam[m_iCurSel].struRectCfg.dwXCoordinate/WIDTH);
	m_comboY.SetCurSel(m_struWallParam[m_iCurSel].struRectCfg.dwYCoordinate/HEIGHT);
    
	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgWallCfg_Uniform::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	int i = 0;
	BOOL bOneFail = FALSE;
	char cs[1024] = {0};
	CString csTemp;
	char *pTemp = new char[4 + MAX_COUNT * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION)];
	memset(pTemp, 0, 4 + MAX_COUNT * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION));
// 	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYPOSITION, 0xffffffff, NULL, 0, NULL, pTemp, 4 + MAX_COUNT * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION)))
// 	{
// 		sprintf(cs, "获取所有位置失败, Error code: %d", NET_DVR_GetLastError());
// 		AfxMessageBox(cs);
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLDISPLAYPOSITION");		
// 		//return;
// 	}
    DWORD dwWallNo = m_byWallNo; 
    dwWallNo <<= 24; 
    if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYPOSITION, 0xffffffff, &dwWallNo, sizeof(DWORD), NULL, pTemp, 4 + MAX_COUNT * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION)))
    {
        sprintf(cs, "获取墙所有输出位置失败, Error code: %d", NET_DVR_GetLastError());
        AfxMessageBox(cs);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLDISPLAYPOSITION");		
        //return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEOWALLDISPLAYPOSITION");
		m_dwDispNum = *((DWORD*)pTemp);	
		memcpy(m_struWallParam, pTemp + 4, m_dwDispNum * sizeof(NET_DVR_VIDEOWALLDISPLAYPOSITION));
		memset(m_dwStatus, 0, sizeof(m_dwStatus));
        ClearModify(); 	
		m_comboOutput.ResetContent();
		for (i = 0; i<m_dwDispNum; i++)
		{	
            m_lDispChan[i] = m_struWallParam[i].dwDisplayNo; 
			sprintf(cs, "%d", m_lDispChan[i]);
			m_comboOutput.AddString(cs);
			m_comboOutput.SetItemData(i, m_lDispChan[i]);
		}
        m_lPapamCount = m_dwDispNum; 
	}
	delete []pTemp;
	//m_listScreen.DeleteAllItems();
	DrawList();
    m_listScreen.UpdateData(FALSE); 
    m_listScreen.SetItemState(m_iCurSel, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED); 
}

void CDlgWallCfg_Uniform::OnBtnSaveCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128];	
	int iSel = m_comboOutput.GetCurSel();
	int j = 0;
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
    NET_DVR_WALLOUTPUTPARAM struOuputPapam={0}; 
    UpdateOutputPapam(struOuputPapam); 
    //增加修改记录
    for(j=0; j<m_lRecordCount; j++)
    {
        if (m_dwRecordPapam[j] == iSel)
        {
            break; 
        }
    }
    if (j>=m_lRecordCount)
    {
        m_dwRecordPapam[j] = iSel; 
        m_lRecordCount ++; 
    }
    m_struOutput[iSel] = struOuputPapam; 
}

void CDlgWallCfg_Uniform::OnBtnSetCfg() 
{
	// TODO: Add your control notification handler code here
	char cs[2048] = {0};
	BOOL bOneFail = FALSE;
	CString csTemp;
	int i = 0;
	int j = 0;
    LPNET_DVR_WALLOUTPUTPARAM lpOutputPapma = GetModifyPapam();
    LPDWORD lpModifyOutputNO = (LPDWORD)GetModifyPapamChan(); 
    if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_WALLOUTPUT_SET, m_lRecordCount, lpModifyOutputNO, 4 * m_lRecordCount, m_dwStatus, lpOutputPapma, m_lRecordCount * sizeof(NET_DVR_WALLOUTPUTPARAM)))
    {
        sprintf(cs, "设置修改失败, Error code: %d", NET_DVR_GetLastError());
        AfxMessageBox(cs);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLOUTPUT_SET");
        return;
    }
    
    sprintf(cs, "Not succeed:\n");
    for (i = 0; i < m_lRecordCount; i++)
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
    OnBtnUpdateOutput(); 
}

//单个输出号的参数获取
void CDlgWallCfg_Uniform::OnBtnGetCfg() 
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
    CString csError; 
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_WALLOUTPUT_GET, 1, &dwOutputNum, 4, &dwStatus, &struTemp, sizeof(struTemp)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLOUTPUT_GET");
        csError.Format("获取输出参数失败， Error Code %d" , NET_DVR_GetLastError()); 
		MessageBox(csError);
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
        m_combVideoFormat.SetCurSel(struTemp.byVideoFormat); 
        if (struTemp.byDisplayMode == 0xff)
        {
            m_combDisplayMode.SetCurSel(4); 
        }
        else
            m_combDisplayMode.SetCurSel(struTemp.byDisplayMode-1); 
        m_combBackGround.SetCurSel(struTemp.byBackgroundColor);
        
		memcpy(&m_struOutput[m_comboOutput.GetCurSel()], &struTemp, sizeof(NET_DVR_WALLOUTPUTPARAM));
        RemovePapamRecord(m_lDispChan[m_comboOutput.GetCurSel()]); 
		UpdateData(FALSE);

		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLOUTPUT_GET");
	}
}


void CDlgWallCfg_Uniform::OnSelchangeComboOutput() 
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
    m_combVideoFormat.SetCurSel(m_struOutput[iSel].byVideoFormat); 
    if (m_struOutput[iSel].byDisplayMode == 0xff )
    {
        m_combDisplayMode.SetCurSel(4);             //4 对应无效
    }
    else
    {
         m_combDisplayMode.SetCurSel(m_struOutput[iSel].byDisplayMode + 1); 
    }
    m_combBackGround.SetCurSel(m_struOutput[iSel].byBackgroundColor);

    m_byWallNo = m_byInitWallNo; 
	UpdateData(FALSE);
	
}

//获取所有
void CDlgWallCfg_Uniform::OnBtnUpdateOutput() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	BOOL bOneFail = FALSE;
	char cs[128] = {0};
	CString csTemp;
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_WALLOUTPUT_GET, m_dwDispNum, m_lDispChan, m_dwDispNum * 4, m_dwStatus, m_struOutput, m_dwDispNum * sizeof(NET_DVR_WALLOUTPUTPARAM)))
	{
		sprintf(cs, "获取所有属性失败, Error code: %d", NET_DVR_GetLastError());
		AfxMessageBox(cs);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLOUTPUT_GET");		
		return;
	}
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
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLOUTPUT_GET");
		m_dwCount = 0;		
		memset(m_dwStatus, 0, sizeof(m_dwStatus));
	}
    //DrawList(); 
	OnSelchangeComboOutput();
}



//更新项记录
BOOL CDlgWallCfg_Uniform::UpdateOutputNum(const NET_DVR_VIDEOWALLDISPLAYPOSITION &struDisplayPos)
{
    //判断是否新修改项
    int  i=0; 
	int j = 0;
    for (i=0; i<m_dwDispNum; i++)
    {
        if ( struDisplayPos.dwDisplayNo == m_struWallParam[i].dwDisplayNo)
        {
            break; 
        }
    }
 
    m_struWallParam[i] = struDisplayPos; 
    if (i >= m_dwDispNum)
    {
        //新项
        m_dwDispNum ++; 
        //添加修改记录
        m_lDispChanSet[m_dwCount] = i; 
        m_dwCount ++; 
    }
    else
    {
        //原有项
        // 判断是否添加修改记录
        for( j=0; j<m_dwCount; j++)
        {
            if (m_lDispChanSet[j] == i)
            {
                break; 
            }
        }
        if(j>=m_dwCount)
        {
            m_lDispChanSet[m_dwCount] = i; 
            m_dwCount ++; 
        }
    }
    return TRUE; 
}

//更新界面数值到变量
BOOL CDlgWallCfg_Uniform::UpdateDisplayPos(NET_DVR_VIDEOWALLDISPLAYPOSITION &struDisplayPos)
{
    UpdateData(TRUE); 
    struDisplayPos.dwSize = sizeof(struDisplayPos);
    struDisplayPos.byEnable = m_bEnable; 
    struDisplayPos.dwDisplayNo = m_dwOutputNum; 
    struDisplayPos.dwVideoWallNo = m_byWallNo; 
    struDisplayPos.dwVideoWallNo <<= 24;                         //墙号是占高字节            
    struDisplayPos.struRectCfg.dwXCoordinate = WIDTH * m_comboX.GetCurSel();
    struDisplayPos.struRectCfg.dwYCoordinate = HEIGHT * m_comboY.GetCurSel();
    return TRUE; 
}

BOOL CDlgWallCfg_Uniform::NewOutputNum(const NET_DVR_VIDEOWALLDISPLAYPOSITION &struDisplayPos)
{
    int  i=0; 
    for (i=0; i<m_dwDispNum; i++)
    {
        if ( struDisplayPos.dwDisplayNo == m_struWallParam[i].dwDisplayNo)
        {
            break; 
        }
    }
    m_struWallParam[i] = struDisplayPos; 
    if (i >= m_dwDispNum)
    {
        //新项
        m_dwDispNum ++; 
    }
    else
    {
        //原有项
        //判断是否添加修改记录 删除修改记录
        int j; 
        int iCount = m_dwCount;
        for(j=0; j<iCount; j++)
        {
            if (m_lDispChanSet[j] == i)
            {
                break; 
            }
        }
        for ( ; j<iCount; j++)
        {
            m_lDispChanSet[j] = m_lDispChanSet[j+1]; 
        }
        if ( m_dwCount )
        {
            m_dwCount --; 
        }     
    }
    return TRUE; 
} 

//获取修改过项
LPNET_DVR_VIDEOWALLDISPLAYPOSITION CDlgWallCfg_Uniform::GetModifyDisplayPos()                             
{
    memset(m_struWallParamSet, 0, sizeof(m_struWallParamSet));
    for (int i=0; i<m_dwCount; i++)
    {
        m_struWallParamSet[i] = m_struWallParam[m_lDispChanSet[i]]; 
        m_ModifyChan[i] = m_struWallParamSet[i].dwDisplayNo; 
    }
    return m_struWallParamSet; 
}    

LONG * CDlgWallCfg_Uniform::GetModifyChan()                                                                //获取修改过显示输出号数组
{   
    memset(m_ModifyChan, 0, sizeof(m_ModifyChan));
    for (int i=0; i<m_dwCount; i++)
    {
        m_ModifyChan[i] = m_struWallParam[m_lDispChanSet[i] ].dwDisplayNo ;
    }
    return m_ModifyChan; 
}

BOOL CDlgWallCfg_Uniform::ClearModify()
{
    memset(m_struWallParamSet, 0, sizeof(m_struWallParamSet));
    m_dwCount = 0; 
    memset(m_ModifyChan, 0, sizeof(m_ModifyChan)); 
    return TRUE; 
}

BOOL CDlgWallCfg_Uniform::UpdateOutputPapam(NET_DVR_WALLOUTPUTPARAM &struOutputPapam)
{
    UpdateData(TRUE); 
    struOutputPapam.dwSize = sizeof(struOutputPapam);
    struOutputPapam.dwResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
    struOutputPapam.struRes.byBrightnessLevel = m_byBrightness;
    struOutputPapam.struRes.byContrastLevel = m_byContrast;
    struOutputPapam.struRes.bySharpnessLevel = m_bySharpness;
    struOutputPapam.struRes.bySaturationLevel = m_bySaturation;
    struOutputPapam.struRes.byHueLevel = m_byHue;
    struOutputPapam.struRes.byEnableFunc = (BYTE)(m_bFgb | (m_bDzd << 1) | (m_bQgyz << 2));
    if (m_comboLevel.GetCurSel() != CB_ERR)
    {
        struOutputPapam.struRes.byLightInhibitLevel = m_comboLevel.GetCurSel() + 1;
    }
    struOutputPapam.struRes.byGrayLevel = m_byGray;
    struOutputPapam.byVideoFormat = m_combVideoFormat.GetCurSel();
    int iSel = m_combDisplayMode.GetCurSel(); 
    struOutputPapam.byDisplayMode = (iSel == 4)? 0xff : iSel+1; 
    struOutputPapam.byBackgroundColor = m_combDisplayMode.GetCurSel()+1; 
    return TRUE; 
}


BOOL CDlgWallCfg_Uniform::RemovePapamRecord(DWORD dwOutputNO)
{
    int i=0; 
    for (i=0; i<m_dwCount; i++)
    {
        if (dwOutputNO == m_lDispChan[m_dwRecordPapam[i] ])
        {
            break; 
        }
    }
    if (i<m_dwCount)
    {
        for ( ; i<m_dwCount-1; i++)
        {
            m_dwRecordPapam[i] = m_dwRecordPapam[i+1];
        }
        m_dwCount --; 
    }
    return TRUE; 
}


BOOL CDlgWallCfg_Uniform::UpdatePapams(DWORD dwOutputNO, NET_DVR_WALLOUTPUTPARAM &struOutputPapam)
{
    return TRUE; 
}

LPNET_DVR_WALLOUTPUTPARAM CDlgWallCfg_Uniform::GetModifyPapam()
{
    memset(m_struOutputSet, 0, sizeof(m_struOutputSet));
    for (int i=0; i<m_lRecordCount; i++)
    {
        m_struOutputSet[i] = m_struOutput[m_dwRecordPapam[i] ];
    }
    return m_struOutputSet; 
}

LONG * CDlgWallCfg_Uniform::GetModifyPapamChan()
{
    memset(m_ModifyChan, 0, sizeof(m_ModifyChan));
    for (int i=0; i<m_lRecordCount; i++)
    {
        m_ModifyChan[i] = m_lDispChan[m_dwRecordPapam[i] ];
    }
    return m_ModifyChan; 
}

void CDlgWallCfg_Uniform::InitOutputLinkMode()
{
    memset(&m_struDisplayCfg, 0, sizeof(m_struDisplayCfg)); 
    m_struDisplayCfg.dwSize = sizeof(m_struDisplayCfg);
    char szLan[128] = {0}; 
    DWORD dwRet; 
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYNO, 0, &m_struDisplayCfg, sizeof(m_struDisplayCfg), &dwRet))
    {
        g_StringLanType(szLan, "获取显示输出号状态失败", "Failed to get Output Num");
        sprintf(szLan, "%s Error Code %d", szLan, NET_DVR_GetLastError()); 
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLDISPLAYNO");
    }
}

void CDlgWallCfg_Uniform::OnButVideowallControl() 
{
	// TODO: Add your control notification handler code here
	CDlgWallControl dlg; 
    dlg.m_lUserID = m_lUserID; 
    dlg.m_iDeviceIndex = m_iDeviceIndex; 
    dlg.DoModal(); 
}

void CDlgWallCfg_Uniform::OnButVwscSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    char szLan[128] = {0}; 
    NET_DVR_SHOW_CONTROL_INFO  struControlInfo = {0}; 
    struControlInfo.dwSize = sizeof(struControlInfo);
    struControlInfo.byChanType = m_CmChanTypeC.GetCurSel() + 1; 
    struControlInfo.byEnable = m_BShowC; 
    struControlInfo.dwDisplayNo = (m_BAllDisplayNo)?0xffffffff : m_dwDisplayNoC;
    struControlInfo.dwWallNo = m_byWallNo; 
    struControlInfo.dwWallNo <<=  24 ;
    if (! NET_DVR_RemoteControl(m_lUserID, NET_DVR_DISPLAY_CHANNO_CONTROL,  &struControlInfo, sizeof(struControlInfo)))
    {
        g_StringLanType(szLan, "发送编号显示控制失败", "Failed to send Display Show Control");
        sprintf(szLan, "%s Error Code %d", szLan, NET_DVR_GetLastError()); 
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_DISPLAY_CHANNO_CONTROL");
    }
}

void CDlgWallCfg_Uniform::OnChkVwsAlldisplayno() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	if (m_BAllDisplayNo)
	{
        GetDlgItem(IDC_EDT_VWSC_DISPLAYNO)->EnableWindow(FALSE);
	}
    else
    {
        GetDlgItem(IDC_EDT_VWSC_DISPLAYNO)->EnableWindow(TRUE);
    }
}


void CDlgWallCfg_Uniform::OnButDispParamAllSame() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_WALLOUTPUTPARAM struOuputPapam={0}; 
	UpdateOutputPapam(struOuputPapam); 
    char szLan[128]; 
    int iSelData = m_comboOutput.GetItemData(m_comboOutput.GetCurSel());
//     if (iSel == -1)
//     {
//         g_StringLanType(szLan, "请选择显示输出号", "please select output No.");
//         AfxMessageBox(szLan);
//         return;
// 	}

    DWORD dwDispNo = (iSelData & 0xff000000) + 0xffffff;  
    if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_WALLOUTPUT_SET, 0xffffffff, &dwDispNo, sizeof(DWORD), NULL, &struOuputPapam, sizeof(NET_DVR_WALLOUTPUTPARAM)))
    {
        sprintf(szLan, "设置修改失败, Error code: %d", NET_DVR_GetLastError());
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLOUTPUT_SET");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLOUTPUT_SET");
//    OnBtnUpdateOutput(); 
}
