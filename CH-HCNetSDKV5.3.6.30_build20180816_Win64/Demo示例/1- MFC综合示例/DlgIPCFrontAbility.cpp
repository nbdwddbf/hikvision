// DlgIPCFrontAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPCFrontAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCFrontAbility dialog


CDlgIPCFrontAbility::CDlgIPCFrontAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPCFrontAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIPCFrontAbility)
	m_iMaxContrastLevel = 0;
	m_iMaxDayNightFilterTime = 0;
	m_iMaxExposure = 0;
	m_iMaxGainLevel = 0;
	m_iMaxSaturationLevel = 0;
	m_iMaxSharpLevel = 0;
	m_iMinBrightLevel = 0;
	m_iMinContrastLevel = 0;
	m_iMinDayNightFilterTime = 0;
	m_iMinExposure = 0;
	m_iMinGainLevel = 0;
	m_iMinSaturationLevel = 0;
	m_iMinSharpLevel = 0;
	m_iMaxBrightLevel = 0;
	//}}AFX_DATA_INIT
    m_pRecvBuf = NULL;
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struCameraParam, 0, sizeof(m_struCameraParam));
}


void CDlgIPCFrontAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPCFrontAbility)
	DDX_Control(pDX, IDC_LIST_WHITE_BALANCE_MODE, m_listWhiteBalanceMode);
	DDX_Control(pDX, IDC_LIST_SWITCH_SCHED_ENABLE, m_listSwitchSchedEnable);
	DDX_Control(pDX, IDC_LIST_NIGHT_TO_DAY_FILTER_LEVEL, m_listNightToDayFilterLevel);
	DDX_Control(pDX, IDC_LIST_MIRROR, m_listMirror);
	DDX_Control(pDX, IDC_LIST_LOCAL_OUTPUT, m_listLocalOutput);
	DDX_Control(pDX, IDC_LIST_IRIS_MODE, m_listIrisMode);
	DDX_Control(pDX, IDC_LIST_EXPOSURE_SET, m_listExposureSet);
	DDX_Control(pDX, IDC_LIST_EXPOSURE_MODE, m_listExposureMode);
	DDX_Control(pDX, IDC_LIST_DAYLIGHT_FILTER_TYPE, m_listDaylightFilterType);
	DDX_Control(pDX, IDC_LIST_DAY_TO_NIGHT_FILTER_LEVEL, m_listDayToNightFilterLevel);
	DDX_Control(pDX, IDC_LIST_BACK_LIGHT_MODE, m_listBackLightMode);
	DDX_Text(pDX, IDC_EDIT_MAX_CONTRAST_LEVEL, m_iMaxContrastLevel);
	DDX_Text(pDX, IDC_EDIT_MAX_DAY_NIGHT_FILTER_TIME, m_iMaxDayNightFilterTime);
	DDX_Text(pDX, IDC_EDIT_MAX_EXPOSURE, m_iMaxExposure);
	DDX_Text(pDX, IDC_EDIT_MAX_GAINLEVEL, m_iMaxGainLevel);
	DDX_Text(pDX, IDC_EDIT_MAX_SATURATION_LEVEL, m_iMaxSaturationLevel);
	DDX_Text(pDX, IDC_EDIT_MAX_SHARP_LEVEL, m_iMaxSharpLevel);
	DDX_Text(pDX, IDC_EDIT_MIN_BRIGHT_LEVEL, m_iMinBrightLevel);
	DDX_Text(pDX, IDC_EDIT_MIN_CONTRAST_LEVEL, m_iMinContrastLevel);
	DDX_Text(pDX, IDC_EDIT_MIN_DAY_NIGHT_FILTER_TIME, m_iMinDayNightFilterTime);
	DDX_Text(pDX, IDC_EDIT_MIN_EXPOSURE, m_iMinExposure);
	DDX_Text(pDX, IDC_EDIT_MIN_GAINLEVEL, m_iMinGainLevel);
	DDX_Text(pDX, IDC_EDIT_MIN_SATURATION_LEVEL, m_iMinSaturationLevel);
	DDX_Text(pDX, IDC_EDIT_MIN_SHARP_LEVEL, m_iMinSharpLevel);
	DDX_Text(pDX, IDC_EDIT_MAX_BRIGHT_LEVEL, m_iMaxBrightLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIPCFrontAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgIPCFrontAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCFrontAbility message handlers

BOOL CDlgIPCFrontAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    if (m_pRecvBuf == NULL)
    {
        m_pRecvBuf = new char[XML_BUF] ;
    }
    
    GetIPCFrontAbility();
    
    ParseIPCFrontAbility(m_pRecvBuf, strlen(m_pRecvBuf));

//    SetIPCFrontAbilityToWnd(m_struCameraParam);
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgIPCFrontAbility::PostNcDestroy() 
{
    if (m_pRecvBuf != NULL)
    {
        delete []m_pRecvBuf;
        m_pRecvBuf = NULL;
    }
    CDialog::PostNcDestroy();
}

BOOL CDlgIPCFrontAbility::GetIPCFrontAbility()
{
	char *pInBuf = new char[2*1024*1024];
	memset(pInBuf,0,2*1024*1024);
	strcpy(pInBuf,"<CAMERAPARA version=\"2.0\"><ChannelNumber>0xff</ChannelNumber></CAMERAPARA>");
    if (NET_DVR_GetDeviceAbility(m_lServerID, IPC_FRONT_PARAMETER_V20, pInBuf,strlen(pInBuf), m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "IPC_FRONT_PARAMETER_V20");
		if (pInBuf != NULL)
		{
			delete []pInBuf;
			pInBuf = NULL;
		}
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "IPC_FRONT_PARAMETER_V20");
		if (pInBuf != NULL)
		{
			delete []pInBuf;
			pInBuf = NULL;
		}
        return FALSE;
    }
}

BOOL CDlgIPCFrontAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    char cFilename[256] = {0};
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    
    sprintf(cFilename, "%s\\CCD_%s.xml", g_struLocalParam.chPictureSavePath, chTime);
    
    
    HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        int nError = 0;
        nError = GetLastError();
        return FALSE;
    }
    DWORD dwReturn = 0;
    WriteFile(hFile, pBuf, dwBufSize, &dwReturn, NULL);
    CloseHandle(hFile);
    hFile = NULL;
    
    return TRUE;
}

BOOL CDlgIPCFrontAbility::ParseIPCFrontAbility(char *pBuf, DWORD dwBufSize)
{
    WirteBufToFile(pBuf, dwBufSize);
    
    CMarkup	XmlMaker;
    XmlMaker.SetDoc(pBuf);
    
    ParseIPCFrontAbilityXml(XmlMaker);   
    return TRUE;
}

BOOL CDlgIPCFrontAbility::ParseIPCFrontAbilityXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("CAMERAPARA"))
    {
        struMarkup.IntoElem();

        ParseWhilteBalanceXml(struMarkup);
        ParseExposureXml(struMarkup);
        ParseIrisModeXml(struMarkup);
        ParseGainLevelXml(struMarkup);
        ParseBrightLevelXml(struMarkup);
        ParseContrastLevelXml(struMarkup);
        ParseSharpLevelXml(struMarkup);
        ParseSaturationLevelXml(struMarkup);
        ParseDayligthFilterXml(struMarkup);
        ParseSwitchScheduleXml(struMarkup);
        ParseBackLightXml(struMarkup);
        ParseMirrorXml(struMarkup);
        ParseLocalOutput(struMarkup);

        struMarkup.OutOfElem();
    }
    else
    {
        AfxMessageBox("Find CAMERAPARA fail");
    }
    return TRUE;
}

BOOL CDlgIPCFrontAbility::ParseWhilteBalanceXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("WhiteBalance"))
    {
        struMarkup.IntoElem();
        if (struMarkup.FindElem("WhiteBalanceMode"))
        {
            struMarkup.IntoElem();
            if (struMarkup.FindElem("Range"))
            {
                CString str;
                str = struMarkup.GetData();
                ParseStrIndex(str, m_struCameraParam.struWhiteBalance.byWhiteBalanceMode, sizeof(m_struCameraParam.struWhiteBalance.byWhiteBalanceMode));
            }

            struMarkup.OutOfElem();
        }
        
        struMarkup.OutOfElem();
    }
    return TRUE;
}

BOOL CDlgIPCFrontAbility::ParseExposureXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("Exposure"))
    {
        struMarkup.IntoElem();

        if (struMarkup.FindElem("ExposureMode"))
        {
            struMarkup.IntoElem();
            if (struMarkup.FindElem("Range"))
            {
                CString str;
                str = struMarkup.GetData();
                ParseStrIndex(str, m_struCameraParam.struExposure.byExposureMode, sizeof(m_struCameraParam.struExposure.byExposureMode));
            }
            struMarkup.OutOfElem();
        }

        if (struMarkup.FindElem("ExposureSet"))
        {
            struMarkup.IntoElem();
            if (struMarkup.FindElem("Range"))
            {
                CString str;
                str = struMarkup.GetData();
                ParseStrIndex(str, m_struCameraParam.struExposure.byExposureSet, sizeof(m_struCameraParam.struExposure.byExposureSet));
            }

            struMarkup.OutOfElem();
        }

        if (struMarkup.FindElem("exposureUSERSET"))
        {
            struMarkup.IntoElem();
            if (struMarkup.FindElem("Min"))
            {
                m_struCameraParam.struExposure.dwMinExposureUserSet = atoi(struMarkup.GetData());
            }

            if (struMarkup.FindElem("Max"))
            {
                m_struCameraParam.struExposure.dwMaxExposureUserSet = atoi(struMarkup.GetData());
            }
                
            struMarkup.OutOfElem();
        }
        struMarkup.OutOfElem();
    }
    return TRUE;
}

BOOL CDlgIPCFrontAbility::ParseIrisModeXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("IrisMode"))
    {
        struMarkup.IntoElem();
        
        if (struMarkup.FindElem("Range"))
        {
            CString str;
            str = struMarkup.GetData();
            ParseStrIndex(str, m_struCameraParam.struIrisMode.byIrisMode, sizeof(m_struCameraParam.struIrisMode.byIrisMode));
        }
        
        struMarkup.OutOfElem();
    }
    else
    {
        TRACE("Fail to find IrisMode");
    }
    return TRUE;
}

BOOL CDlgIPCFrontAbility::ParseGainLevelXml(CMarkup &struMarkup)
{
    //     <GainLevel>
    //         <Min>0</Min>
    //         <Max>100</Max>
// 	</>
    if (struMarkup.FindElem("GainLevel"))
    {
        struMarkup.IntoElem();

        if (struMarkup.FindElem("Min"))
        {
            m_struCameraParam.struGainLevel.dwMinGainLevel = atoi(struMarkup.GetData());
        }

        if (struMarkup.FindElem("Max"))
        {
            m_struCameraParam.struGainLevel.dwMaxGainLevel = atoi(struMarkup.GetData());
        }

        struMarkup.OutOfElem();
    }
    return TRUE;
}

BOOL CDlgIPCFrontAbility::ParseBrightLevelXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("BrightnessLevel"))
    {
        struMarkup.IntoElem();
        
        if (struMarkup.FindElem("Min"))
        {
            m_struCameraParam.struBrightLevel.dwMinBrightLevel= atoi(struMarkup.GetData());
        }
        
        if (struMarkup.FindElem("Max"))
        {
            m_struCameraParam.struBrightLevel.dwMaxBrightLevel = atoi(struMarkup.GetData());
        }
        
        struMarkup.OutOfElem();
    }
    
    return TRUE;
}
BOOL CDlgIPCFrontAbility::ParseContrastLevelXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("ContrastLevel"))
    {
        struMarkup.IntoElem();
        
        if (struMarkup.FindElem("Min"))
        {
            m_struCameraParam.struContrastLevel.dwMinContrastLevel = atoi(struMarkup.GetData());
        }
        
        if (struMarkup.FindElem("Max"))
        {
            m_struCameraParam.struContrastLevel.dwMaxContrastLevel = atoi(struMarkup.GetData());
        }
        
        struMarkup.OutOfElem();
    }

    return TRUE;
}
BOOL CDlgIPCFrontAbility::ParseSharpLevelXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("SharpnessLevel"))
    {
        struMarkup.IntoElem();
        
        if (struMarkup.FindElem("Min"))
        {
            m_struCameraParam.struSharpLevel.dwMinSharpnessLevel = atoi(struMarkup.GetData());
        }
        
        if (struMarkup.FindElem("Max"))
        {
            m_struCameraParam.struSharpLevel.dwMaxSharpnessLevel = atoi(struMarkup.GetData());
        }
        
        struMarkup.OutOfElem();
    }
    
    return TRUE;
}
BOOL CDlgIPCFrontAbility::ParseSaturationLevelXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("SaturationLevel"))
    {
        struMarkup.IntoElem();
        
        if (struMarkup.FindElem("Min"))
        {
            m_struCameraParam.struSaturationLevel.dwMinSaturationLevel = atoi(struMarkup.GetData());
        }
        
        if (struMarkup.FindElem("Max"))
        {
            m_struCameraParam.struSaturationLevel.dwMaxSaturationLevel = atoi(struMarkup.GetData());
        }
        
        struMarkup.OutOfElem();
    }
    return TRUE;
}
BOOL CDlgIPCFrontAbility::ParseDayligthFilterXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("DayNightFilter"))
    {
        struMarkup.IntoElem();
        
        if (struMarkup.FindElem("DayNightFilterType"))
        {
            struMarkup.IntoElem();

            if (struMarkup.FindElem("Range"))
            {
                CString str;
                str = struMarkup.GetData();
                ParseStrIndex(str, m_struCameraParam.struDaylightFilter.byFilterType, sizeof(m_struCameraParam.struDaylightFilter.byFilterType));
            }

            struMarkup.OutOfElem();
        }
        
        struMarkup.OutOfElem();
    }

    return TRUE;
}
BOOL CDlgIPCFrontAbility::ParseSwitchScheduleXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("SwitchSchedule"))
    {
        struMarkup.IntoElem();
        if (struMarkup.FindElem("SwitchScheduleEnabled"))
        {
            struMarkup.IntoElem();
            if (struMarkup.FindElem("Range"))
            {
                CString str;
                str = struMarkup.GetData();
                ParseStrIndex(str, m_struCameraParam.struSwitchSchedule.bySwitchScheduleEnabled, sizeof(m_struCameraParam.struSwitchSchedule.bySwitchScheduleEnabled));
            }
            struMarkup.OutOfElem();
        }

        if (struMarkup.FindElem("DayToNightFilterLevel"))
        {
            struMarkup.IntoElem();
            
            if (struMarkup.FindElem("Range"))
            {
                CString str;
                str = struMarkup.GetData();
                ParseStrIndex(str, m_struCameraParam.struSwitchSchedule.byDayToNightFilterLevel, sizeof(m_struCameraParam.struSwitchSchedule.byDayToNightFilterLevel));
            }
            struMarkup.OutOfElem();
        }

        if (struMarkup.FindElem("NightToDayFilterLevel"))
        {
            struMarkup.IntoElem();
            
            if (struMarkup.FindElem("Range"))
            {
                CString str;
                str = struMarkup.GetData();
                ParseStrIndex(str, m_struCameraParam.struSwitchSchedule.byNightToDayFilterLevel, sizeof(m_struCameraParam.struSwitchSchedule.byNightToDayFilterLevel));
            }
            struMarkup.OutOfElem();
        }


        if (struMarkup.FindElem("DayNightFilterTime"))
        {
            struMarkup.IntoElem();
            
            if (struMarkup.FindElem("Min"))
            {
                m_struCameraParam.struSwitchSchedule.dwMinDayNightFilterTime = atoi(struMarkup.GetData());
            }

            if (struMarkup.FindElem("Max"))
            {
                m_struCameraParam.struSwitchSchedule.dwMaxDayNightFilterTime = atoi(struMarkup.GetData());
            }
            
            struMarkup.OutOfElem();
        }
        struMarkup.OutOfElem();
    }

    return TRUE;
}
BOOL CDlgIPCFrontAbility::ParseBackLightXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("Backlight"))
    {
        struMarkup.IntoElem();

        if (struMarkup.FindElem("BacklightMode"))
        {
            struMarkup.IntoElem();
    
            if (struMarkup.FindElem("Range"))
            {
                CString str;
                str = struMarkup.GetData();
                ParseStrIndex(str, m_struCameraParam.struBackLight.byBacklightMode, sizeof(m_struCameraParam.struBackLight.byBacklightMode));
            }
            struMarkup.OutOfElem();
        }

        struMarkup.OutOfElem();
    }
    return TRUE;
}
BOOL CDlgIPCFrontAbility::ParseMirrorXml(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("Mirror"))
    {
        struMarkup.IntoElem();
        
        if (struMarkup.FindElem("Range"))
        {
            CString str;
            str = struMarkup.GetData();
            ParseStrIndex(str, m_struCameraParam.struMirror.byMirror, sizeof(m_struCameraParam.struMirror.byMirror));
        }
        struMarkup.OutOfElem();
    }

    return TRUE;
}
BOOL CDlgIPCFrontAbility::ParseLocalOutput(CMarkup &struMarkup)
{
    if (struMarkup.FindElem("LOCALOUTPUT"))
    {
        struMarkup.IntoElem();
        if (struMarkup.FindElem("Range"))
        {
            CString str;
            str = struMarkup.GetData();
            ParseStrIndex(str, m_struCameraParam.struLocalOutput.byLocalOutput, sizeof(m_struCameraParam.struLocalOutput.byLocalOutput));
        }
        struMarkup.OutOfElem();
    }
    return TRUE;
}


void CDlgIPCFrontAbility::SetWhiteBalanceToWnd(CAMERA_WHITE_BALANCE &struWhiteBalance)
{
    char szLan[128] = {0};
    for (int i = 0; i <ARRAY_SIZE(struWhiteBalance.byWhiteBalanceMode); i++)
    {
        if (1 == struWhiteBalance.byWhiteBalanceMode[i])
        {
            sprintf(szLan, "%d", i);
            m_listWhiteBalanceMode.AddString(szLan);
        }
    }
}

void CDlgIPCFrontAbility::SetExposureToWnd(CAMERA_EXPOSURE &struExposure)
{
    char szLan[128] = {0};
	int i =0;
    for (i =0; i < ARRAY_SIZE(struExposure.byExposureMode); i++)
    {
        if (1 == struExposure.byExposureMode[i])
        {
            sprintf(szLan, "%d", i);
            m_listExposureMode.AddString(szLan);
        }
    }

    for (i =0; i < ARRAY_SIZE(struExposure.byExposureSet); i++)
    {
        if (1 == struExposure.byExposureSet[i])
        {
            sprintf(szLan, "%d", i);
            m_listExposureSet.AddString(szLan);
        }
    }

    m_iMinExposure = struExposure.dwMinExposureUserSet;
    m_iMaxExposure = struExposure.dwMaxExposureUserSet;
}

void CDlgIPCFrontAbility::SetIrisModeToWnd(CAMERA_IRIS_MODE &struIrisMode)
{
    char szLan[128] = {0};
    for (int i =0; i < ARRAY_SIZE(struIrisMode.byIrisMode); i++)
    {
        if (1 == struIrisMode.byIrisMode[i])
        {
            sprintf(szLan, "%d", i);
            m_listIrisMode.AddString(szLan);
        }
    }
}

void CDlgIPCFrontAbility::SetGainLevelToWnd(CAMERA_GAINLEVEL &struGainLevel)
{
    m_iMaxGainLevel = struGainLevel.dwMaxGainLevel;
    m_iMinGainLevel = struGainLevel.dwMinGainLevel;
}

void CDlgIPCFrontAbility::SetBrightLevelToWnd(CAMERA_BRIGTH_LEVEL &struBrightLevel)
{
    m_iMinBrightLevel = struBrightLevel.dwMinBrightLevel;
    m_iMaxBrightLevel = struBrightLevel.dwMaxBrightLevel;
}

void CDlgIPCFrontAbility::SetContrastLevelToWnd(CAMERA_CONTRAST_LEVEL &struContrastLevel)
{
    m_iMinContrastLevel = struContrastLevel.dwMinContrastLevel;
    m_iMaxContrastLevel = struContrastLevel.dwMaxContrastLevel;
}

void CDlgIPCFrontAbility::SetSharpLevelToWnd(CAMERA_SHARP_LEVEL &struSharpLevel)
{
    m_iMinSharpLevel = struSharpLevel.dwMinSharpnessLevel;
    m_iMaxSharpLevel = struSharpLevel.dwMaxSharpnessLevel;
}

void CDlgIPCFrontAbility::SetSaturationLevel(CAMERA_SATURATION_LEVEL &struSaturationLevel)
{
    m_iMinSaturationLevel = struSaturationLevel.dwMinSaturationLevel;
    m_iMaxSaturationLevel = struSaturationLevel.dwMaxSaturationLevel;
}

void CDlgIPCFrontAbility::SetDayligthFilterToWnd(CAMERA_DAYLIGHT_FILTER &struDaylightFilter)
{
    char szLan[128] = {0};
	int i = 0;
	for (i = 0; i < ARRAY_SIZE(struDaylightFilter.byFilterType); i++)
    {
        if (1 == struDaylightFilter.byFilterType[i])
        {
            sprintf(szLan, "%d", i);
            m_listDaylightFilterType.AddString(szLan);
        }
    }
}

void CDlgIPCFrontAbility::SetSwitchScheduleToWnd(CAMERA_SWITCH_SCHEDULE &struSwitchSchedule)
{
    char szLan[128] = {0};
	int i = 0;
    for (i = 0; i < ARRAY_SIZE(struSwitchSchedule.bySwitchScheduleEnabled); i++)
    {
        if (1 == struSwitchSchedule.bySwitchScheduleEnabled[i])
        {
            sprintf(szLan, "%d", i);
            m_listSwitchSchedEnable.AddString(szLan);
        }
    }

    for (i = 0; i < ARRAY_SIZE(struSwitchSchedule.byDayToNightFilterLevel); i++)
    {
        if (1 == struSwitchSchedule.byDayToNightFilterLevel[i])
        {
            sprintf(szLan, "%d", i);
            m_listDayToNightFilterLevel.AddString(szLan);
        }
    }

    for (i = 0; i < ARRAY_SIZE(struSwitchSchedule.byNightToDayFilterLevel); i++)
    {
        if (1 == struSwitchSchedule.byNightToDayFilterLevel[i])
        {
            sprintf(szLan, "%d", i);
            m_listNightToDayFilterLevel.AddString(szLan);
        }
    }

    m_iMinDayNightFilterTime = struSwitchSchedule.dwMinDayNightFilterTime;
    m_iMaxDayNightFilterTime = struSwitchSchedule.dwMaxDayNightFilterTime;
}

void CDlgIPCFrontAbility::SetBackLightToWnd(CAMERA_BACKLIGHT &struBackLight)
{    
    // BYTE    byBacklightMode[MAX_BACKLIGHT_MODE];
    char szLan[128] = {0};
    for (int i = 0; i < ARRAY_SIZE(struBackLight.byBacklightMode); i++)
    {
        if (1 == struBackLight.byBacklightMode[i])
        {
            sprintf(szLan, "%d", i);
            m_listBackLightMode.AddString(szLan);
        }
    }
}

void CDlgIPCFrontAbility::SetMirrorToWnd(CAMERA_MIRROR &struMirror)
{
    char szLan[128] = {0};
    for (int i = 0; i < ARRAY_SIZE(struMirror.byMirror); i++)
    {
        if (1 == struMirror.byMirror[i])
        {
            sprintf(szLan, "%d", i);
            m_listMirror.AddString(szLan);
        }
    }
}

void CDlgIPCFrontAbility::SetLocalOutputToWnd(CAMERA_LOCALOUTPUT &struLocakOutput)
{
    char szLan[128] = {0};
    for (int i = 0; i < ARRAY_SIZE(struLocakOutput.byLocalOutput); i++)
    {
        if (1 == struLocakOutput.byLocalOutput[i])
        {
            sprintf(szLan, "%d", i);
            m_listLocalOutput.AddString(szLan);
        }
    }
}

void CDlgIPCFrontAbility::SetIPCFrontAbilityToWnd(CAMERA_PARAM &struCameraParam)
{
    SetWhiteBalanceToWnd(struCameraParam.struWhiteBalance);
    SetExposureToWnd(struCameraParam.struExposure);
    SetIrisModeToWnd(struCameraParam.struIrisMode);
    SetGainLevelToWnd(struCameraParam.struGainLevel);
    SetBrightLevelToWnd(struCameraParam.struBrightLevel);
    SetContrastLevelToWnd(struCameraParam.struContrastLevel);
    SetSharpLevelToWnd(struCameraParam.struSharpLevel);
    SetSaturationLevel(struCameraParam.struSaturationLevel);
    SetDayligthFilterToWnd(struCameraParam.struDaylightFilter);
    SetSwitchScheduleToWnd(struCameraParam.struSwitchSchedule);
    SetBackLightToWnd(struCameraParam.struBackLight);
    SetMirrorToWnd(struCameraParam.struMirror);
    SetLocalOutputToWnd(struCameraParam.struLocalOutput);
}

void CDlgIPCFrontAbility::ParseStrIndex(CString strIndex, byte* array, int iArrayLength)
{
    CString strTemp1 = _T("");
    CString strTemp2 = _T("");
    int iIndex = -1;
    
    strTemp1.Format("%s", strIndex);
    
    iIndex = strTemp1.Find(',', 0);
    
    //当没有','时，直接转换为数字
    if (-1 == iIndex)
    {
        //若转换得到的数字大于数组的维数或者小于0，则返回
        if (atoi(strTemp1) >= iArrayLength || atoi(strTemp1) < 0)
        {
            return;
        }
        array[atoi(strTemp1)] = 1;
        return;
    }
    
    //解析strIndex，设置数组的值
    while (iIndex != -1 )
    {
        strTemp2.Format("%s", strTemp1.Left(iIndex));
        //若转换得到的数字大于数组的维数或者小于0，则返回
        if (atoi(strTemp2) >= iArrayLength || atoi(strTemp2) < 0)
        {
            return;
        }
        array[atoi(strTemp2)] = 1;
        strTemp1.Delete(0, iIndex + 1);
        iIndex = strTemp1.Find(',', 0);
    }
    
    //若转换得到的数字大于数组的维数或者小于0，则返回
    if (atoi(strTemp2) >= iArrayLength || atoi(strTemp2) < 0)
    {
        return;
    }
    array[atoi(strTemp1)] = 1;
}
