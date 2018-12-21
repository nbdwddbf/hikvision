// DlgLcdParamCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLcdParamCfg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdParamCfg dialog


CDlgLcdParamCfg::CDlgLcdParamCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLcdParamCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLcdParamCfg)
	m_bAutoAdjust = FALSE;
	m_bEnableEdge = FALSE;
	m_bEnablePip = FALSE;
	m_bEnableLogo = FALSE;
	m_byBackLight = 0;
	m_byBlue = 0;
	m_iBoardTemp = 0;
	m_byBrightness = 0;
	m_byBlueOffset = 0;
	m_byClock = 0;
	m_byContrast = 0;
	m_byGainB = 0;
	m_byGainG = 0;
	m_byGainR = 0;
	m_byGreen = 0;
	m_dwPipHeight = 0;
	m_byGreenOffset = 0;
	m_byHorizontal = 0;
	m_byHue = 0;
	m_byLeft = 0;
	m_byLower = 0;
	m_byOffsetB = 0;
	m_byOffsetG = 0;
	m_byOffsetR = 0;
	m_byPhase = 0;
	m_byRed = 0;
	m_byRedOffset = 0;
	m_byRight = 0;
	m_bySaturation = 0;
	m_bySharpness = 0;
	m_csSoftVersion = _T("");
	m_byTempValue = 0;
	m_byTop = 0;
	m_byVertical = 0;
	m_byWallNo = 1;
	m_dwPipWidth = 0;
	m_dwWorkingHours = 0;
	m_dwPipX = 0;
	m_dwPipY = 0;
	m_bEnableMute = FALSE;
	m_iBalance = 0;
	m_dwVolume = 0;
	//}}AFX_DATA_INIT
    m_lpScreenParam = NULL;
    m_lCfgHandle = -1;
    m_bExitThread = NULL;
    m_dwCfgNum = 0;
    m_dwCurrentScreenNo = 1;
    m_hThread = NULL;
    m_BPressGetParamBut = FALSE; 
}


void CDlgLcdParamCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLcdParamCfg)
	DDX_Control(pDX, IDC_COMBO_TEMPTURE_EXCEPTION_STATUS, m_cmbTemperatureStatus);
	DDX_Control(pDX, IDC_COMBO_FAN_EXCEPTION_STATUS, m_cmbExceptStatus);
	DDX_Control(pDX, IDC_COMBO_IMAGE_MODE, m_comboImageMode);
	DDX_Control(pDX, IDC_COMBO_NO_SIGNAL, m_comboNoSignal);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_csStatus);
	DDX_Control(pDX, IDC_COMBO_Y, m_comboY);
	DDX_Control(pDX, IDC_COMBO_X, m_comboX);
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comboWorkMode);
	DDX_Control(pDX, IDC_COMBO_WIDTH, m_comboWidth);
	DDX_Control(pDX, IDC_COMBO_TRANSPARENCY, m_comboTransparent);
	DDX_Control(pDX, IDC_COMBO_SOURCE_PIP, m_comboSourcePip);
	DDX_Control(pDX, IDC_COMBO_SCREEN_NO, m_comboScreenNo);
	DDX_Control(pDX, IDC_COMBO_PARAM_TYPE, m_comboParamType);
	DDX_Control(pDX, IDC_COMBO_LANGUAGE, m_comboLanguage);
	DDX_Control(pDX, IDC_COMBO_INTERFACE, m_comboInterface);
	DDX_Control(pDX, IDC_COMBO_HEIGHT, m_comboHeight);
	DDX_Control(pDX, IDC_COMBO_FAN_STATUS, m_comboFanStatus);
	DDX_Control(pDX, IDC_COMBO_DURATION, m_comboDuration);
	DDX_Control(pDX, IDC_COMBO_DISPLAY_MODE, m_comboDisplayMode);
	DDX_Control(pDX, IDC_COMBO_DEFOG_MODE, m_comboDefogMode);
	DDX_Control(pDX, IDC_COMBO_DEFOG_LEVEL, m_comboDefogLevel);
	DDX_Control(pDX, IDC_COMBO_DEFOG_ENABLE, m_comboDefogEnable);
	DDX_Control(pDX, IDC_COMBO_COLOR_PIP, m_comboPipColor);
	DDX_Check(pDX, IDC_CHK_AUTO_ADJUST, m_bAutoAdjust);
	DDX_Check(pDX, IDC_CHK_EDGE_ENABLE, m_bEnableEdge);
	DDX_Check(pDX, IDC_CHK_ENABLE_PIP, m_bEnablePip);
	DDX_Check(pDX, IDC_CHK_LOGO, m_bEnableLogo);
	DDX_Text(pDX, IDC_EDIT_BACKLIGHT, m_byBackLight);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_byBlue);
	DDX_Text(pDX, IDC_EDIT_BOARD_TEMP, m_iBoardTemp);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_byBrightness);
	DDX_Text(pDX, IDC_EDIT_BULEOFFSET, m_byBlueOffset);
	DDX_Text(pDX, IDC_EDIT_CLOCK, m_byClock);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_byContrast);
	DDX_Text(pDX, IDC_EDIT_GAIN_B, m_byGainB);
	DDX_Text(pDX, IDC_EDIT_GAIN_G, m_byGainG);
	DDX_Text(pDX, IDC_EDIT_GAIN_R, m_byGainR);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_byGreen);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_PIP, m_dwPipHeight);
	DDX_Text(pDX, IDC_EDIT_GREENOFFSET, m_byGreenOffset);
	DDX_Text(pDX, IDC_EDIT_HORIZONTAL, m_byHorizontal);
	DDX_Text(pDX, IDC_EDIT_HUE, m_byHue);
	DDX_Text(pDX, IDC_EDIT_LEFT, m_byLeft);
	DDX_Text(pDX, IDC_EDIT_LOWER, m_byLower);
	DDX_Text(pDX, IDC_EDIT_OFFSET_B, m_byOffsetB);
	DDX_Text(pDX, IDC_EDIT_OFFSET_G, m_byOffsetG);
	DDX_Text(pDX, IDC_EDIT_OFFSET_R, m_byOffsetR);
	DDX_Text(pDX, IDC_EDIT_PHASE, m_byPhase);
	DDX_Text(pDX, IDC_EDIT_RED, m_byRed);
	DDX_Text(pDX, IDC_EDIT_REDOFFSET, m_byRedOffset);
	DDX_Text(pDX, IDC_EDIT_RIGHT, m_byRight);
	DDX_Text(pDX, IDC_EDIT_SATURATION, m_bySaturation);
	DDX_Text(pDX, IDC_EDIT_SHARPNESS, m_bySharpness);
	DDX_Text(pDX, IDC_EDIT_SOFT_VERSION, m_csSoftVersion);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_VALUE, m_byTempValue);
	DDX_Text(pDX, IDC_EDIT_TOP, m_byTop);
	DDX_Text(pDX, IDC_EDIT_VERTICAL, m_byVertical);
	DDX_Text(pDX, IDC_EDIT_WALL_NO, m_byWallNo);
	DDX_Text(pDX, IDC_EDIT_WIDTH_PIP, m_dwPipWidth);
	DDX_Text(pDX, IDC_EDIT_WORKING_HOURS, m_dwWorkingHours);
	DDX_Text(pDX, IDC_EDIT_X_COORDINATE, m_dwPipX);
	DDX_Text(pDX, IDC_EDIT_Y_COORDINATE, m_dwPipY);
	DDX_Check(pDX, IDC_CHK_LCD_PARAM_MUTE, m_bEnableMute);
	DDX_Text(pDX, IDC_EDT_LCD_PARAM_BALANCE, m_iBalance);
	DDX_Text(pDX, IDC_EDT_LCD_PARAM_VOLUME, m_dwVolume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLcdParamCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgLcdParamCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_WM_CANCELMODE()
	ON_CBN_SELCHANGE(IDC_COMBO_SCREEN_NO, OnSelchangeComboScreenNo)    
    
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_PROC_LCD_PARAM, OnMessUpdateInterface)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdParamCfg message handlers

UINT CDlgLcdParamCfg::LcdParamCfgWaitThread(LPVOID pParam)
{
    CDlgLcdParamCfg *ptr = (CDlgLcdParamCfg *)pParam;
    
    while (!ptr->m_bExitThread)
    {
        Sleep(500);        
    }    

    if (ptr->m_lCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(ptr->m_lCfgHandle);
        ptr->m_lCfgHandle = -1;
    }
    if ( ptr->m_BPressGetParamBut )
    {
        ::PostMessage(ptr->m_hWnd, WM_PROC_LCD_PARAM, NULL, NULL);
        ptr->m_BPressGetParamBut = FALSE; 
    }
    
    // Get Param

    //ptr->OnSelchangeComboScreenNo();
    //ptr->aa();
    OutputDebugString("LcdParamCfgWaitThread exit!");
    return 0;
}

void CALLBACK ScreenConfigCallBack(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgLcdParamCfg *ptr = (CDlgLcdParamCfg *)pUserData;
    DWORD dwStatus;
    char szLan[64] = {0};
    NET_DVR_MSC_SCREEN_PARAM_CFG *lpData = NULL;
    
    switch (dwType)
    {
    case NET_SDK_CALLBACK_TYPE_STATUS:
        try
        {
            dwStatus = *((DWORD *)lpBuffer);
        }
        catch (...)
        {
        	ptr->m_bExitThread = TRUE;
            g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "ScreenConfigCallBack ((DWORD *)lpBuffer) = %x", lpBuffer);
            return ; 
        }
     
        
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            sprintf(szLan, "Screen %d success", ptr->m_dwCurrentScreenNo);
            ptr->m_csStatus.SetWindowText(szLan);            
            ptr->m_dwCurrentScreenNo++;
            ptr->m_bExitThread = TRUE;
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            sprintf(szLan, "Screen %d processing", ptr->m_dwCurrentScreenNo);
            ptr->m_csStatus.SetWindowText(szLan);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            sprintf(szLan, "Screen %d fail", ptr->m_dwCurrentScreenNo);
            ptr->m_csStatus.SetWindowText(szLan);
            ptr->m_dwCurrentScreenNo++;
            ptr->m_bExitThread = TRUE;
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            sprintf(szLan, "Config exception");
            ptr->m_csStatus.SetWindowText(szLan); 
            ptr->m_bExitThread = TRUE;
        }
        break;
    case NET_SDK_CALLBACK_TYPE_DATA:
        lpData = (NET_DVR_MSC_SCREEN_PARAM_CFG *)lpBuffer;
        memcpy(ptr->m_lpScreenParam + (ptr->m_dwCurrentScreenNo - 1), lpData, sizeof(NET_DVR_MSC_SPLICE_CFG));        
        sprintf(szLan, "Screen %d success", ptr->m_dwCurrentScreenNo);
        ptr->m_csStatus.SetWindowText(szLan); 
        ptr->m_dwCurrentScreenNo++;        
        break;
    default:
        break;
    }
    
    if (ptr->m_dwCurrentScreenNo > ptr->m_dwCfgNum)
    {
        ptr->m_bExitThread = TRUE;
        sprintf(szLan, "Screen config over");
        ptr->m_csStatus.SetWindowText(szLan);
    }

    //ptr->UpdateData(FALSE);
}

BOOL CDlgLcdParamCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    char szLan[64] = {0};

    memset(&m_struCond, 0, sizeof(m_struCond));
    m_struCond.dwSize = sizeof(m_struCond);
    memset(&m_struSet, 0, sizeof(m_struSet));
    m_struSet.dwSize = sizeof(m_struSet);
    m_struSet.struScreenParam.dwSize = sizeof(m_struSet.struScreenParam);

    m_lpScreenParam = new(std::nothrow) NET_DVR_MSC_SCREEN_PARAM_CFG[100];

    if (m_lpScreenParam == NULL)
    {
        g_StringLanType(szLan, "分配内存失败", "Alloc memory fail");
        AfxMessageBox(szLan);
    }
    else
    {
        memset(m_lpScreenParam, 0, sizeof(NET_DVR_MSC_SCREEN_PARAM_CFG) * 100);
    }
	
    for (int i = 0; i < 10; i++)
    {
        sprintf(szLan, "%d", i);
        m_comboX.AddString(szLan);
        m_comboY.AddString(szLan);
        sprintf(szLan, "%d", i + 1);
        m_comboWidth.AddString(szLan);
        m_comboHeight.AddString(szLan);        
    }

    m_comboX.SetCurSel(0);
    m_comboY.SetCurSel(0);
    m_comboWidth.SetCurSel(0);
    m_comboHeight.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLcdParamCfg::SaveParam()
{
    UpdateData(TRUE);
//     输入源参数
//         风扇工作模式参数
//         VGA信号参数
//         屏幕菜单参数
//         显示效果参数
//         色温参数
//         ADC参数
//         屏幕边缘参数
//         背光参数
//         画中画参数
//         透雾参数
//         屏幕工作状态
// 开关机LOGO显示参数
    int iSel = m_comboParamType.GetCurSel();
    if (iSel == CB_ERR)
    {
        return;
    }

    memset(&m_struSet.struScreenParam.struParam, 0, sizeof(m_struSet.struScreenParam.struParam));

    switch (iSel)
    {
    case 0:
        m_struSet.struScreenParam.struParam.struInterfaceCfg.dwSize = sizeof(m_struSet.struScreenParam.struParam.struInterfaceCfg);
        m_struSet.struScreenParam.struParam.struInterfaceCfg.byInterfaceType = m_comboInterface.GetCurSel();
        m_struSet.struScreenParam.struParam.struInterfaceCfg.byNoSignalPic = m_comboNoSignal.GetCurSel() + 1;
    	break;
    case 1:
        m_struSet.struScreenParam.struParam.struFanWorkMode.dwSize = sizeof(m_struSet.struScreenParam.struParam.struFanWorkMode);
        m_struSet.struScreenParam.struParam.struFanWorkMode.byWorkMode = m_comboWorkMode.GetCurSel() + 1;
        m_struSet.struScreenParam.struParam.struFanWorkMode.byTemperatureLimitValue = m_byTempValue;
        break;
    case 2:
        m_struSet.struScreenParam.struParam.struVgaCfg.dwSize = sizeof(m_struSet.struScreenParam.struParam.struVgaCfg);
        m_struSet.struScreenParam.struParam.struVgaCfg.byEnableAutoAdjust = m_bAutoAdjust;
        m_struSet.struScreenParam.struParam.struVgaCfg.byHorizontalPosition = m_byHorizontal;
        m_struSet.struScreenParam.struParam.struVgaCfg.byVerticalPosition = m_byVertical;
        m_struSet.struScreenParam.struParam.struVgaCfg.byClock = m_byClock;
        m_struSet.struScreenParam.struParam.struVgaCfg.byPhase = m_byPhase;
        break;
    case 3:
        m_struSet.struScreenParam.struParam.struMenuCfg.dwSize = sizeof(m_struSet.struScreenParam.struParam.struMenuCfg);
        m_struSet.struScreenParam.struParam.struMenuCfg.byMenuLanguage = m_comboLanguage.GetCurSel() + 1;
        m_struSet.struScreenParam.struParam.struMenuCfg.byTransparency = m_comboTransparent.GetCurSel();
        m_struSet.struScreenParam.struParam.struMenuCfg.byDuration = m_comboDuration.GetCurSel();
        break;
    case 4:
        m_struSet.struScreenParam.struParam.struOutEffectCfg.byDisplayMode = m_comboDisplayMode.GetCurSel();
        if (m_struSet.struScreenParam.struParam.struOutEffectCfg.byDisplayMode == 0)
        {
            m_struSet.struScreenParam.struParam.struOutEffectCfg.byDisplayMode = 0xff;
        }
        m_struSet.struScreenParam.struParam.struOutEffectCfg.byBrightnessLevel = m_byBrightness;
        m_struSet.struScreenParam.struParam.struOutEffectCfg.byContrastLevel = m_byContrast;
        m_struSet.struScreenParam.struParam.struOutEffectCfg.bySharpnessLevel = m_bySharpness;
        m_struSet.struScreenParam.struParam.struOutEffectCfg.bySaturationLevel = m_bySaturation;
        m_struSet.struScreenParam.struParam.struOutEffectCfg.byHueLevel = m_byHue;
        m_struSet.struScreenParam.struParam.struOutEffectCfg.byImageMode = m_comboImageMode.GetCurSel();
        break;
    case 5:
        m_struSet.struScreenParam.struParam.struColorTemperatureCfg.byRed = m_byRed;
        m_struSet.struScreenParam.struParam.struColorTemperatureCfg.byGreen = m_byGreen;
        m_struSet.struScreenParam.struParam.struColorTemperatureCfg.byBlue = m_byBlue;
        m_struSet.struScreenParam.struParam.struColorTemperatureCfg.byRedOffset = m_byRedOffset;
        m_struSet.struScreenParam.struParam.struColorTemperatureCfg.byGreenOffset = m_byGreenOffset;
        m_struSet.struScreenParam.struParam.struColorTemperatureCfg.byBlueOffset = m_byBlueOffset;
        break;
    case 6:
        m_struSet.struScreenParam.struParam.struAdcCfg.byGainR = m_byGainR;
        m_struSet.struScreenParam.struParam.struAdcCfg.byGainG = m_byGainG;
        m_struSet.struScreenParam.struParam.struAdcCfg.byGainB = m_byGainB;
        m_struSet.struScreenParam.struParam.struAdcCfg.byOffsetR = m_byOffsetR;
        m_struSet.struScreenParam.struParam.struAdcCfg.byOffsetG = m_byOffsetG;
        m_struSet.struScreenParam.struParam.struAdcCfg.byOffsetB = m_byOffsetB;
        break;
    case 7:
        m_struSet.struScreenParam.struParam.struScreenEdgeCfg.byEnable = m_bEnableEdge;
        m_struSet.struScreenParam.struParam.struScreenEdgeCfg.byLeftEdge = m_byLeft;
        m_struSet.struScreenParam.struParam.struScreenEdgeCfg.byRightEdge = m_byRight;
        m_struSet.struScreenParam.struParam.struScreenEdgeCfg.byTopEdge = m_byTop;
        m_struSet.struScreenParam.struParam.struScreenEdgeCfg.byLowerEdge = m_byLower;
        break;
    case 8:
        m_struSet.struScreenParam.struParam.struBacklight.dwSize = sizeof(m_struSet.struScreenParam.struParam.struBacklight);
        m_struSet.struScreenParam.struParam.struBacklight.byBacklight = m_byBackLight;
        break;
    case 9:
        m_struSet.struScreenParam.struParam.struPicInPicCfg.dwSize = sizeof(m_struSet.struScreenParam.struParam.struPicInPicCfg);
        m_struSet.struScreenParam.struParam.struPicInPicCfg.byEnable = m_bEnablePip;
        m_struSet.struScreenParam.struParam.struPicInPicCfg.bySubWindowSource = m_comboSourcePip.GetCurSel();
        m_struSet.struScreenParam.struParam.struPicInPicCfg.bySubWindowBorderColor = m_comboPipColor.GetCurSel() + 1;
        m_struSet.struScreenParam.struParam.struPicInPicCfg.struPosition.dwXCoordinate = m_dwPipX;
        m_struSet.struScreenParam.struParam.struPicInPicCfg.struPosition.dwYCoordinate = m_dwPipY;
        m_struSet.struScreenParam.struParam.struPicInPicCfg.struPosition.dwWidth = m_dwPipWidth;
        m_struSet.struScreenParam.struParam.struPicInPicCfg.struPosition.dwHeight = m_dwPipHeight;
        break;
    case 10:
        m_struSet.struScreenParam.struParam.struDefog.dwSize = sizeof(m_struSet.struScreenParam.struParam.struDefog);
        m_struSet.struScreenParam.struParam.struDefog.byDefogEnable = m_comboDefogEnable.GetCurSel();
        m_struSet.struScreenParam.struParam.struDefog.byDefogModel = m_comboDefogMode.GetCurSel();
        m_struSet.struScreenParam.struParam.struDefog.byDefogLevel = m_comboDefogLevel.GetCurSel() + 1;
        break;
    case 11:
        break;
    case 12:
        m_struSet.struScreenParam.struParam.struBootLogoCfg.dwSize = sizeof(m_struSet.struScreenParam.struParam.struBootLogoCfg);
        m_struSet.struScreenParam.struParam.struBootLogoCfg.byEnable = m_bEnableLogo;
        break;
	case 13:
        m_struSet.struScreenParam.struParam.struAudioCfg.dwSize = sizeof(m_struSet.struScreenParam.struParam.struAudioCfg);
        m_struSet.struScreenParam.struParam.struAudioCfg.byMute = m_bEnableMute; 
        m_struSet.struScreenParam.struParam.struAudioCfg.byVolume = m_dwVolume; 
        m_struSet.struScreenParam.struParam.struAudioCfg.byBalance = m_iBalance;         
        break; 
    default:
        break;
    }

    m_struCond.byParamType = m_comboParamType.GetCurSel() + 1;
    m_struCond.byWallNo = m_byWallNo;
    m_struCond.struRectCfg.dwXCoordinate = m_comboX.GetCurSel() * 1920;
    m_struCond.struRectCfg.dwYCoordinate = m_comboY.GetCurSel() * 1920;
    m_struCond.struRectCfg.dwWidth = (m_comboWidth.GetCurSel() + 1) * 1920;
    m_struCond.struRectCfg.dwHeight = (m_comboHeight.GetCurSel() + 1) * 1920;

    m_struSet.struScreenParam.byParamType = m_comboParamType.GetCurSel() + 1;
    m_struSet.byWallNo = m_byWallNo;
    m_struSet.struRectCfg.dwXCoordinate = m_comboX.GetCurSel() * 1920;
    m_struSet.struRectCfg.dwYCoordinate = m_comboY.GetCurSel() * 1920;
    m_struSet.struRectCfg.dwWidth = (m_comboWidth.GetCurSel() + 1) * 1920;
    m_struSet.struRectCfg.dwHeight = (m_comboHeight.GetCurSel() + 1) * 1920;

}


void CDlgLcdParamCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (CB_ERR == m_comboParamType.GetCurSel())
    {
        return;
    }

    if (m_lCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lCfgHandle);
        m_lCfgHandle = -1;
    }

    if (NULL != m_hThread)
    {
        m_bExitThread = TRUE;
        //TerminateThread(m_hThread, 0);
        WaitForSingleObject(m_hThread, INFINITE);
        CloseHandle(m_hThread);
        m_hThread = NULL;
    }

    char szLan[64] = {0};
    DWORD dwThreadId = 0;
    m_bExitThread = FALSE;
    m_dwCfgNum = 0;
    m_dwCurrentScreenNo = 1;
    //memset();

    SaveParam();

    m_lCfgHandle = NET_DVR_StartRemoteConfig(m_lUserId, NET_DVR_SET_SCREEN_PARAM, &m_struSet, sizeof(m_struSet), ScreenConfigCallBack, this);

    if (m_lCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_PARAM");
        g_StringLanType(szLan, "设置屏幕参数失败", "Set screen parameter fail");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_PARAM");
        m_dwCfgNum = (m_struSet.struRectCfg.dwWidth/1920) * (m_struSet.struRectCfg.dwHeight/1920);
        m_dwCurrentScreenNo = 1;
        m_hThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(LcdParamCfgWaitThread), this, 0, &dwThreadId);
        if (m_hThread == NULL)
        {
            g_StringLanType(szLan, "创建等待线程失败", "Create wait thread fail");
            NET_DVR_StopRemoteConfig(m_lCfgHandle);
            return;
        } 
    }	
}

void CDlgLcdParamCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (CB_ERR == m_comboParamType.GetCurSel())
    {
        return;
    }
    
    if (m_lCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lCfgHandle);
        m_lCfgHandle = -1;
    }
    
    if (NULL != m_hThread)
    {
        m_bExitThread = TRUE;
        TerminateThread(m_hThread, 0);
        WaitForSingleObject(m_hThread, INFINITE);
        CloseHandle(m_hThread);
        m_hThread = NULL;
    }
    
    char szLan[64] = {0};
    DWORD dwThreadId = 0;
    m_bExitThread = FALSE;
    m_dwCfgNum = 0;
    m_dwCurrentScreenNo = 1;
    
    memset(m_lpScreenParam, 0, sizeof(NET_DVR_MSC_SCREEN_PARAM_CFG) * 100);

    SaveParam();
    m_BPressGetParamBut = TRUE; 
    m_lCfgHandle = NET_DVR_StartRemoteConfig(m_lUserId, NET_DVR_GET_SCREEN_PARAM, &m_struCond, sizeof(m_struCond), ScreenConfigCallBack, this);
    
    if (m_lCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_PARAM");
        g_StringLanType(szLan, "获取屏幕参数失败", "Get screen parameter fail");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_PARAM");
        m_dwCfgNum = (m_struSet.struRectCfg.dwWidth/1920) * (m_struSet.struRectCfg.dwHeight/1920);
        m_dwCurrentScreenNo = 1;
        m_comboScreenNo.ResetContent();

        for (int i = 0; i < m_dwCfgNum; i++)
        {
            sprintf(szLan, "%d", i + 1);
            m_comboScreenNo.AddString(szLan);
        }
        if ( m_dwCfgNum )
        {
            m_comboScreenNo.SetCurSel(0); 
            UpdateData(FALSE);
        }
        m_hThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(LcdParamCfgWaitThread), this, 0, &dwThreadId);
        if (m_hThread == NULL)
        {
            g_StringLanType(szLan, "创建等待线程失败", "Create wait thread fail");
            NET_DVR_StopRemoteConfig(m_lCfgHandle);
            return;
        }
        
        sprintf(szLan, "thread id = %d\n", dwThreadId);
        OutputDebugString(szLan);
    }
}

void CDlgLcdParamCfg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    if (NULL != m_lpScreenParam)
    {
        delete []m_lpScreenParam;
        m_lpScreenParam = NULL;
    }

    if (m_lCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lCfgHandle);
        m_lCfgHandle = -1;
    }
    
    if (NULL != m_hThread)
    {
        TerminateThread(m_hThread, 0);
        CloseHandle(m_hThread);
        m_hThread = NULL;
    }
    
    CDialog::OnCancel();
}

void CDlgLcdParamCfg::OnSelchangeComboScreenNo() 
{
	// TODO: Add your control notification handler code here
//     UpdateData(TRUE); 
//     OutputDebugString("OnSelchangeComboScreenNo in");
//     if (m_comboScreenNo.GetCount() == 0)
//     {
//         return;
//     }
// 	
//     int iSel = m_comboScreenNo.GetCurSel();
//     int iParamType = m_comboParamType.GetCurSel() + 1;
// 
//     //     输入源参数
//     //         风扇工作模式参数
//     //         VGA信号参数
//     //         屏幕菜单参数
//     //         显示效果参数
//     //         色温参数
//     //         ADC参数
//     //         屏幕边缘参数
//     //         背光参数
//     //         画中画参数
//     //         透雾参数
//     //         屏幕工作状态
// // 开关机LOGO显示参数
// 
//     NET_DVR_MSC_SCREEN_PARAM_CFG *lpTemp = m_lpScreenParam + iSel;
// 
//     CString tmp; 
//     tmp.Format("\niParamType %d %d %d\n", iParamType, lpTemp->struParam.struInterfaceCfg.byInterfaceType, lpTemp->struParam.struInterfaceCfg.byNoSignalPic);
//     OutputDebugString(tmp);
// //     NET_DVR_MSC_SCREEN_PARAM_CFG *lpTemp = m_struSet + iSel;
//     switch (iParamType)
//     {
//     case 1:
//         m_comboInterface.SetCurSel(lpTemp->struParam.struInterfaceCfg.byInterfaceType);
//         m_comboNoSignal.SetCurSel(lpTemp->struParam.struInterfaceCfg.byNoSignalPic - 1);
//     	break;
//     case 2:
//         m_comboWorkMode.SetCurSel(lpTemp->struParam.struFanWorkMode.byWorkMode - 1);
//         m_byTempValue = lpTemp->struParam.struFanWorkMode.byTemperatureLimitValue;
//         break;
//     case 3:
//         m_bAutoAdjust = lpTemp->struParam.struVgaCfg.byEnableAutoAdjust;
//         m_byHorizontal = lpTemp->struParam.struVgaCfg.byHorizontalPosition;
//         m_byVertical = lpTemp->struParam.struVgaCfg.byVerticalPosition;
//         m_byClock = lpTemp->struParam.struVgaCfg.byClock;
//         m_byPhase = lpTemp->struParam.struVgaCfg.byPhase;
//         break;
//     case 4:
//         m_comboLanguage.SetCurSel(lpTemp->struParam.struMenuCfg.byMenuLanguage - 1);
//         m_comboTransparent.SetCurSel(lpTemp->struParam.struMenuCfg.byTransparency);
//         m_comboDuration.SetCurSel(lpTemp->struParam.struMenuCfg.byDuration);
//         break;
//     case 5:
//         if (lpTemp->struParam.struOutEffectCfg.byDisplayMode == 0xff)
//         {
//             m_comboDisplayMode.SetCurSel(0);
//         }
//         else if(lpTemp->struParam.struOutEffectCfg.byDisplayMode == 0)
//         {
//             m_comboDisplayMode.SetCurSel(-1);           
//         }
//         else 
//         {
//             m_comboDisplayMode.SetCurSel(lpTemp->struParam.struOutEffectCfg.byDisplayMode);
//         }
//         m_byBrightness = lpTemp->struParam.struOutEffectCfg.byBrightnessLevel;
//         m_byContrast = lpTemp->struParam.struOutEffectCfg.byContrastLevel;
//         m_bySharpness = lpTemp->struParam.struOutEffectCfg.bySharpnessLevel;
//         m_bySaturation = lpTemp->struParam.struOutEffectCfg.bySaturationLevel;
//         m_byHue = lpTemp->struParam.struOutEffectCfg.byHueLevel;
//         m_comboImageMode.SetCurSel(lpTemp->struParam.struOutEffectCfg.byImageMode);
//         break;
//     case 6:
//         m_byRed = lpTemp->struParam.struColorTemperatureCfg.byRed;
//         m_byGreen = lpTemp->struParam.struColorTemperatureCfg.byGreen;
//         m_byBlue = lpTemp->struParam.struColorTemperatureCfg.byBlue;
//         m_byRedOffset = lpTemp->struParam.struColorTemperatureCfg.byRedOffset;
//         m_byGreenOffset = lpTemp->struParam.struColorTemperatureCfg.byGreenOffset;
//         m_byBlueOffset = lpTemp->struParam.struColorTemperatureCfg.byBlue;
//         break;
//     case 7:
//         m_byGainR = lpTemp->struParam.struAdcCfg.byGainR;
//         m_byGainG = lpTemp->struParam.struAdcCfg.byGainG;
//         m_byGainB = lpTemp->struParam.struAdcCfg.byGainB;
//         m_byOffsetR = lpTemp->struParam.struAdcCfg.byOffsetR;
//         m_byOffsetG = lpTemp->struParam.struAdcCfg.byOffsetG;
//         m_byOffsetB = lpTemp->struParam.struAdcCfg.byOffsetB;
//         break;
//     case 8:
//         m_bEnableEdge = lpTemp->struParam.struScreenEdgeCfg.byEnable;
//         m_byLeft = lpTemp->struParam.struScreenEdgeCfg.byLeftEdge;
//         m_byRight = lpTemp->struParam.struScreenEdgeCfg.byRightEdge;
//         m_byTop = lpTemp->struParam.struScreenEdgeCfg.byTopEdge;
//         m_byLower = lpTemp->struParam.struScreenEdgeCfg.byLowerEdge;
//         break;
//     case 9:
//         m_byBackLight = lpTemp->struParam.struBacklight.byBacklight;
//         break;
//     case 10:
//         m_bEnablePip = lpTemp->struParam.struPicInPicCfg.byEnable;
//         m_comboSourcePip.SetCurSel(lpTemp->struParam.struPicInPicCfg.bySubWindowSource);
//         m_comboPipColor.SetCurSel(lpTemp->struParam.struPicInPicCfg.bySubWindowBorderColor);
//         m_dwPipX = lpTemp->struParam.struPicInPicCfg.struPosition.dwXCoordinate;
//         m_dwPipY = lpTemp->struParam.struPicInPicCfg.struPosition.dwYCoordinate;
//         m_dwPipWidth = lpTemp->struParam.struPicInPicCfg.struPosition.dwWidth;
//         m_dwPipHeight = lpTemp->struParam.struPicInPicCfg.struPosition.dwHeight;
//         break;
//     case 11:
//         m_comboDefogEnable.SetCurSel(lpTemp->struParam.struDefog.byDefogEnable);
//         m_comboDefogMode.SetCurSel(lpTemp->struParam.struDefog.byDefogModel);
//         m_comboDefogLevel.SetCurSel(lpTemp->struParam.struDefog.byDefogLevel - 1);
//         break;
//     case 12:
//         m_comboFanStatus.SetCurSel(lpTemp->struParam.struWorkState.byFanStatus);
//         m_dwWorkingHours = lpTemp->struParam.struWorkState.dwWorkingHours;
//         m_iBoardTemp = lpTemp->struParam.struWorkState.iTemperature;
//         m_csSoftVersion = lpTemp->struParam.struWorkState.byVersion;
//         break;
//     case 13:
//         m_bEnableLogo = lpTemp->struParam.struBootLogoCfg.byEnable;
//         break;
//     default:
//         break;        
//     }
//     
//     UpdateData(FALSE);
//     OutputDebugString("OnSelchangeComboScreenNo out");
    OnMessUpdateInterface(0, 0); 
}


LRESULT CDlgLcdParamCfg::OnMessUpdateInterface(WPARAM wParam, LPARAM lParam)
{
   UpdateData(TRUE); 
    OutputDebugString("OnSelchangeComboScreenNo in");
    if (m_comboScreenNo.GetCount() == 0)
    {
        return 0;
    }
	
    int iSel = m_comboScreenNo.GetCurSel();
    int iParamType = m_comboParamType.GetCurSel() + 1;

    //     输入源参数
    //         风扇工作模式参数
    //         VGA信号参数
    //         屏幕菜单参数
    //         显示效果参数
    //         色温参数
    //         ADC参数
    //         屏幕边缘参数
    //         背光参数
    //         画中画参数
    //         透雾参数
    //         屏幕工作状态
	// 开关机LOGO显示参数
    //         音频参数
    NET_DVR_MSC_SCREEN_PARAM_CFG *lpTemp = m_lpScreenParam + iSel;

    CString tmp; 
    tmp.Format("\niParamType %d %d %d\n", iParamType, lpTemp->struParam.struInterfaceCfg.byInterfaceType, lpTemp->struParam.struInterfaceCfg.byNoSignalPic);
    OutputDebugString(tmp);
//     NET_DVR_MSC_SCREEN_PARAM_CFG *lpTemp = m_struSet + iSel;
    switch (iParamType)
    {
    case 1:
        m_comboInterface.SetCurSel(lpTemp->struParam.struInterfaceCfg.byInterfaceType);
        m_comboNoSignal.SetCurSel(lpTemp->struParam.struInterfaceCfg.byNoSignalPic - 1);
    	break;
    case 2:
        m_comboWorkMode.SetCurSel(lpTemp->struParam.struFanWorkMode.byWorkMode - 1);
        m_byTempValue = lpTemp->struParam.struFanWorkMode.byTemperatureLimitValue;
        break;
    case 3:
        m_bAutoAdjust = lpTemp->struParam.struVgaCfg.byEnableAutoAdjust;
        m_byHorizontal = lpTemp->struParam.struVgaCfg.byHorizontalPosition;
        m_byVertical = lpTemp->struParam.struVgaCfg.byVerticalPosition;
        m_byClock = lpTemp->struParam.struVgaCfg.byClock;
        m_byPhase = lpTemp->struParam.struVgaCfg.byPhase;
        break;
    case 4:
        m_comboLanguage.SetCurSel(lpTemp->struParam.struMenuCfg.byMenuLanguage - 1);
        m_comboTransparent.SetCurSel(lpTemp->struParam.struMenuCfg.byTransparency);
        m_comboDuration.SetCurSel(lpTemp->struParam.struMenuCfg.byDuration);
        break;
    case 5:
        if (lpTemp->struParam.struOutEffectCfg.byDisplayMode == 0xff)
        {
            m_comboDisplayMode.SetCurSel(0);
        }
        else if(lpTemp->struParam.struOutEffectCfg.byDisplayMode == 0)
        {
            m_comboDisplayMode.SetCurSel(-1);           
        }
        else 
        {
            m_comboDisplayMode.SetCurSel(lpTemp->struParam.struOutEffectCfg.byDisplayMode);
        }
        m_byBrightness = lpTemp->struParam.struOutEffectCfg.byBrightnessLevel;
        m_byContrast = lpTemp->struParam.struOutEffectCfg.byContrastLevel;
        m_bySharpness = lpTemp->struParam.struOutEffectCfg.bySharpnessLevel;
        m_bySaturation = lpTemp->struParam.struOutEffectCfg.bySaturationLevel;
        m_byHue = lpTemp->struParam.struOutEffectCfg.byHueLevel;
        m_comboImageMode.SetCurSel(lpTemp->struParam.struOutEffectCfg.byImageMode);
        break;
    case 6:
        m_byRed = lpTemp->struParam.struColorTemperatureCfg.byRed;
        m_byGreen = lpTemp->struParam.struColorTemperatureCfg.byGreen;
        m_byBlue = lpTemp->struParam.struColorTemperatureCfg.byBlue;
        m_byRedOffset = lpTemp->struParam.struColorTemperatureCfg.byRedOffset;
        m_byGreenOffset = lpTemp->struParam.struColorTemperatureCfg.byGreenOffset;
        m_byBlueOffset = lpTemp->struParam.struColorTemperatureCfg.byBlue;
        break;
    case 7:
        m_byGainR = lpTemp->struParam.struAdcCfg.byGainR;
        m_byGainG = lpTemp->struParam.struAdcCfg.byGainG;
        m_byGainB = lpTemp->struParam.struAdcCfg.byGainB;
        m_byOffsetR = lpTemp->struParam.struAdcCfg.byOffsetR;
        m_byOffsetG = lpTemp->struParam.struAdcCfg.byOffsetG;
        m_byOffsetB = lpTemp->struParam.struAdcCfg.byOffsetB;
        break;
    case 8:
        m_bEnableEdge = lpTemp->struParam.struScreenEdgeCfg.byEnable;
        m_byLeft = lpTemp->struParam.struScreenEdgeCfg.byLeftEdge;
        m_byRight = lpTemp->struParam.struScreenEdgeCfg.byRightEdge;
        m_byTop = lpTemp->struParam.struScreenEdgeCfg.byTopEdge;
        m_byLower = lpTemp->struParam.struScreenEdgeCfg.byLowerEdge;
        break;
    case 9:
        m_byBackLight = lpTemp->struParam.struBacklight.byBacklight;
        break;
    case 10:
        m_bEnablePip = lpTemp->struParam.struPicInPicCfg.byEnable;
        m_comboSourcePip.SetCurSel(lpTemp->struParam.struPicInPicCfg.bySubWindowSource);
        m_comboPipColor.SetCurSel(lpTemp->struParam.struPicInPicCfg.bySubWindowBorderColor);
        m_dwPipX = lpTemp->struParam.struPicInPicCfg.struPosition.dwXCoordinate;
        m_dwPipY = lpTemp->struParam.struPicInPicCfg.struPosition.dwYCoordinate;
        m_dwPipWidth = lpTemp->struParam.struPicInPicCfg.struPosition.dwWidth;
        m_dwPipHeight = lpTemp->struParam.struPicInPicCfg.struPosition.dwHeight;
        break;
    case 11:
        m_comboDefogEnable.SetCurSel(lpTemp->struParam.struDefog.byDefogEnable);
        m_comboDefogMode.SetCurSel(lpTemp->struParam.struDefog.byDefogModel);
        m_comboDefogLevel.SetCurSel(lpTemp->struParam.struDefog.byDefogLevel - 1);
        break;
//         屏幕工作状态
    case 12:  
        m_comboFanStatus.SetCurSel(lpTemp->struParam.struWorkState.byFanStatus);
		m_cmbExceptStatus.SetCurSel(lpTemp->struParam.struWorkState.byFanExceptionStatus); 
        m_dwWorkingHours = lpTemp->struParam.struWorkState.dwWorkingHours;
        m_iBoardTemp = lpTemp->struParam.struWorkState.iTemperature;
		m_cmbTemperatureStatus.SetCurSel(lpTemp->struParam.struWorkState.byTempState); 
        m_csSoftVersion = lpTemp->struParam.struWorkState.byVersion;
        break;
    case 13:
        m_bEnableLogo = lpTemp->struParam.struBootLogoCfg.byEnable;
        break;
	case 14: //音频参数
        m_bEnableMute = lpTemp->struParam.struAudioCfg.byMute; 
        m_dwVolume  = lpTemp->struParam.struAudioCfg.byVolume; 
        m_iBalance = lpTemp->struParam.struAudioCfg.byBalance; 
        break; 
    default:
        break;        
    }
    
    UpdateData(FALSE);
    OutputDebugString("OnSelchangeComboScreenNo out"); 
	
	return 1;
}
