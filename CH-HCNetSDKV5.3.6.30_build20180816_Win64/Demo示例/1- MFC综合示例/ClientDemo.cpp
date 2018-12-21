/**********************************************************
FileName:    ClientDemo.cpp
Description: the initiale class of the application, declare the global variable and function      
Date:        2008/05/17
Note: 		 define global variables, implement global function
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "String.h"
#include "DeviceCfgFile.h"
#include "LocalConfigFile.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*Declare all the global variables in ClientDemo.cpp, then add extern to them in ClientDemo.h. 
if other files need to call these global variables, just include ClientDemo.h file*/
LOCAL_SENSOR_ADD_PREVIEW g_struSensorAddPreview[MAX_ALARMHOST_ALARMIN_NUM] = {0};
//memset(&m_struSensorAddPreview, 0,sizeof(m_struSensorAddPreview));

LOCAL_FACE_PICTURE_INFO g_struFacePic[MAX_HUMAN_PICTURE_NUM];
LOCAL_FACE_MODEL_INFO g_struFaceModel[MAX_HUMAN_PICTURE_NUM];
LOCAL_DEVICE_INFO g_struDeviceInfo[MAX_DEVICES];
LOCAL_PARAM g_struLocalParam;		//demo local configure
CClientDemoDlg * g_pMainDlg = NULL;	//
CDlgSensorCfg* g_pDlgSensor = NULL;
BOOL g_bCapPic[MAX_OUTPUTS];//capture pic
BOOL g_bLocalCapPic = TRUE;
BOOL g_bInSide = TRUE;//FALSE; //callback decode
BOOL g_bExitDemo = FALSE;//control post message when exit, so can release the buffer.
BOOL g_bPtzMaualTrace = FALSE;
CASE_INFO g_caseInfo;

CDlgOutput g_dlgOutput[MAX_OUTPUTS];//video output dialog
BOOL g_bShareSound = FALSE;
HBRUSH	g_hPlayHardBgBrush = NULL;		//brush fo preview background, different color in hardware decode from in software decode
HBRUSH	g_hPlaySoftBgBrush =  NULL;
BOOL g_bCardInit = FALSE;			//card initialized successfully or not

LONG g_lVoiceHandle = -1;	//voice talk index
int g_nNetDelay = 2;

char g_szWorkDir[MAX_PATH] = {0};//demo application path

//parameters of all play or circulation play
PLAY_INFO g_struPlayAllInfo[MAX_PREVIEWS];
BOOL g_bPlayAllDevice = FALSE;		//play all the devices that have logged in
WORD g_nSurveillanceTotalNum = 0;	//surveillance points for preview(camera number)
int g_iNextSurveillanceIndex = 0;	//last surveillance point's next serial NO.
int g_pCycleTimer = 0;				//cycle timer index
BOOL g_bStandardCB = FALSE;
//support multi-VGA output
CRect g_rcWindow;				//entire area of dialog
DWORD g_dwOldDeviceNum = 0;		//display card number
int	g_iCurScreenWidth = 0;		//current screen width
int	g_iCurScreenHeight = 0;		//current screen height

BOOL g_bMustReboot = FALSE;		//reboot after modifying some configuration of the device

//time different frome UTC
int g_iHourDiffWithUTC = 0;
int g_iMinDiffWithUTC = 0;
BOOL g_bISO8601 = FALSE;
int g_iDisplayBufNum = 0;

//2009-7-22 
DWORD g_dwStreamTransType = 0;
//2009-7-22

//demo global key
char g_sSecretKey[17] = "StreamNotEncrypt";

//the handle of DSSDK
HINSTANCE g_hDSSDK; 
HINSTANCE g_hDllInst;;
HINSTANCE g_hDllCalib;;
HINSTANCE g_hDllCurlLib;

//global function
void g_ReadDeviceConfig();

void g_SaveDeviceConfig();
void WriteLocalConfig();
void ReadLocalConfig();

void GetCurrentPath(char *path);
BOOL CheckIPStr(CString ip);
void g_CreateLocalDir();
void g_StringLanType(char *szDstLan, char *szLanCn, char *szLanEn);
/////////////////////////////////////////////////////////////////////////////
// CClientDemoApp

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		map between message and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CClientDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CClientDemoApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDemoApp construction

/*********************************************************
Function:	CClientDemoApp
Desc:		Constructor
Input:	
Output:	
Return:	
**********************************************************/
CClientDemoApp::CClientDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/*********************************************************
Function:	CClientDemoApp
Desc:		destructor
Input:	
Output:	
Return:	
**********************************************************/
CClientDemoApp::~CClientDemoApp()
{
	// TODO: add construction code here,
	for (int i = 0; i < MAX_DEVICES; i++)
	{
		if (g_struDeviceInfo[i].pStruIPParaCfgV40 != NULL)
		{
			delete[] g_struDeviceInfo[i].pStruIPParaCfgV40;
			g_struDeviceInfo[i].pStruIPParaCfgV40 = NULL;
		}
	}
    
	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClientDemoApp object

CClientDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClientDemoApp initialization
/*********************************************************
Function:	InitInstance
Desc:		initialize instance
Input:	
Output:	
Return:	
**********************************************************/
BOOL CClientDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

//     _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//     _CrtSetBreakAlloc(21060);
//     _CrtSetBreakAlloc(21082);
//     _CrtSetBreakAlloc(21094);


    g_hDSSDK = LoadLibrary("DsSdk.dll");
	NET_DVR_INIT_CHECK_MODULE_COM struInitCheckModuleCom = { 0 };
	struInitCheckModuleCom.byEnable = 1;//默认启用
	if (!NET_DVR_SetSDKInitCfg(NET_SDK_INIT_CFG_TYPE_CHECK_MODULE_COM, &struInitCheckModuleCom))
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		char szErrLan[128] = { 0 };
		sprintf_s(szErrLan, "ErrCode:%d", dwErrCode);
		AfxMessageBox(szErrLan);
		return FALSE;
	}
    //登录、布防默认最大2048路
    NET_DVR_INIT_CFG_ABILITY struCfgAbility = { INIT_CFG_NUM_2048, INIT_CFG_NUM_2048, 0 };
    if (!NET_DVR_SetSDKInitCfg(NET_SDK_INIT_CFG_ABILITY, &struCfgAbility))
    {
        DWORD dwErrCode = NET_DVR_GetLastError();
        char szErrLan[128] = { 0 };
        sprintf_s(szErrLan, "ErrCode:%d", dwErrCode);
        AfxMessageBox(szErrLan);
        return FALSE;
    }

    //获取应用程序所在路径
    HINSTANCE hInst = NULL;
    hInst = AfxGetApp()->m_hInstance;
    char path_buffer[_MAX_PATH];
    GetModuleFileName(hInst, path_buffer, sizeof(path_buffer));//得到exe文件的全路径
    //分离路径和文件名。
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    _splitpath(path_buffer, drive, dir, fname, ext);
    char path[300];
    strcpy(path, drive);
    strcat(path, dir);

//     NET_DVR_LOCAL_COM_PATH struLocalComPath = { 0 };
//     sprintf(struLocalComPath.sPath, "%sHCNetSDKCom", path);
// 
//     if (!NET_DVR_SetSDKInitCfg(NET_SDK_INIT_CFG_COM_PATH, &struLocalComPath))
//     {
//         DWORD dwErrCode = NET_DVR_GetLastError();
//         char szErrLan[128] = { 0 };
//         sprintf_s(szErrLan, "ErrCode:%d", dwErrCode);
//         AfxMessageBox(szErrLan);
//         return FALSE;
//     }

    printf("-------------hhhhhhhhhhhh---\n");
	if (!NET_DVR_Init())
	{
		DWORD dwErrCode = NET_DVR_GetLastError();
		char szErrLan[128] = { 0 };
		sprintf_s(szErrLan, "ErrCode:%d", dwErrCode);
		AfxMessageBox(szErrLan);
		return FALSE;
	}

	NET_DVR_SDKLOCAL_CFG struSdkLocalCfg = {0};
	struSdkLocalCfg.byEnableAbilityParse = 1; //
	struSdkLocalCfg.byVoiceComMode = 0;   //0 use windows Api , 1 Use liabrary
    struSdkLocalCfg.byLoginWithSimXml = 1;
    struSdkLocalCfg.byCompatibleType = 0;
	NET_DVR_SetSDKLocalConfig(&struSdkLocalCfg);
 
	//NET_DVR_SetConnectTime(3000, 3);
	CClientDemoDlg dlg;
	m_pMainWnd = &dlg;

    try
    {
        dlg.DoModal();
    }
    catch (...)
    {
        return FALSE;	
    }
    
    return TRUE;

// 	int nResponse = dlg.DoModal();
// 	if (nResponse == IDOK)
// 	{
// 		// TODO: Place code here to handle when the dialog is
// 		//  dismissed with OK
// 	}
// 	else if (nResponse == IDCANCEL)
// 	{
// 		// TODO: Place code here to handle when the dialog is
// 		//  dismissed with Cancel
// 	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	//return FALSE;
}



/*********************************************************
Function:	ExitInstance
Desc:	    exit instance
Input:	
Output:	
Return:	
**********************************************************/
int CClientDemoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	NET_DVR_Cleanup(); 

    Gdiplus::GdiplusShutdown(m_gdiplusToken);

	return CWinApp::ExitInstance();
}

/*********************************************************
  Function:	GetCurrentPath
  Desc:		get current path of running application folder
  Input:	
  Output:	szPath, folder path
  Return:	
**********************************************************/
void GetCurrentPath(char *pPath)
{
	CString strPath;
	//get entire path of running application and its title
	GetModuleFileName(NULL,pPath,MAX_PATH);
	strPath.Format(pPath);
	int iPos=strPath.ReverseFind('\\');
	if ((unsigned)iPos == -1)
	{
		return ;
	}
	memset(pPath, 0, MAX_PATH);
	strncpy(pPath, strPath.Left(iPos).GetBuffer(0), iPos);
	pPath[iPos]='\0';
}

/*********************************************************
Function:	
Desc:		change the IP address type from CString to DWORD
Input:		strIP,CString IP address;
Output:	
Return:		DWORD IP address
**********************************************************/
DWORD CStringTodwIP(CString strIP)
{
	DWORD dwRet = 0;
	CString strIPTemp = _T("");
	CString strLeft = _T("");
	CString strRight= _T("");
	int iPos = 0,iLen = 0;

	strIPTemp.Format("%s",strIP.GetBuffer(0));
	strRight = strIPTemp;
	iPos=strRight.Find(".",0);
	iLen=strRight.GetLength();

	while (iPos>0)
	{
		strLeft.Format("%s",strRight.Left(iPos));
		dwRet=(dwRet<<8) + (unsigned)atoi(strLeft);
		strRight.Format("%s",strRight.Right(iLen - iPos - 1));
		iLen=strRight.GetLength();
		iPos=strRight.Find(".",0);
	}
	dwRet=(dwRet<<8) + (unsigned)atoi(strRight);
	return dwRet;
}

/*********************************************************
Function:	IPToStr
Desc:		change the IP address type from DWORD to CString
Input:		dwIP, DWORD;
Output:	
Return:		CString ip address;
**********************************************************/
CString IPToStr(DWORD dwIP)
{
	CString strIP = _T("");
	WORD add1,add2,add3,add4;

	add1=(WORD)(dwIP&255);
	add2=(WORD)((dwIP>>8)&255);
	add3=(WORD)((dwIP>>16)&255);
	add4=(WORD)((dwIP>>24)&255);
	strIP.Format("%d.%d.%d.%d",add4,add3,add2,add1);
	return strIP;
}

int GetIPChannelInfoByIPID(DWORD dwIPID, int iDevIndex)
{
	if (dwIPID == 0)
	{
		return -1;
	}

	DWORD dwGroup = dwIPID/MAX_CHANNUM_V30;
	if (dwIPID%MAX_CHANNUM_V30 == 0)
	{
		dwIPID -=1;
	}



	if (&g_struDeviceInfo[iDevIndex].pStruIPParaCfgV40[dwGroup] == NULL)
	{
		return -1;
	}
	DWORD dwIPIDTemp =0;
	int i ;
	for ( i = 0; i< MAX_CHANNUM_V30;i++)
	{
		dwIPIDTemp = g_struDeviceInfo[iDevIndex].pStruIPParaCfgV40[dwGroup].struStreamMode[i].uGetStream.struChanInfo.byIPID +\
			(g_struDeviceInfo[iDevIndex].pStruIPParaCfgV40[dwGroup].struStreamMode[i].uGetStream.struChanInfo.byIPIDHigh<<8);
		if (dwIPID == dwIPIDTemp)
		{
			break;
		}
	}
	int  iIPChanIndex  = 0;
	iIPChanIndex = dwGroup *MAX_CHANNUM_V30 +i +g_struDeviceInfo[iDevIndex].iAnalogChanNum + iIPChanIndex;

	return iIPChanIndex;

}

void g_CreateAlarmOutTree(CTreeCtrl &m_treeAlarmOut, int iDeviceIndex, BOOL *bAlarmOut)
{
	if (iDeviceIndex == -1)
	{
		return;
	}
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	m_treeAlarmOut.DeleteAllItems();

	HTREEITEM hChanItem = NULL;
	HTREEITEM hFirstItem = NULL;

	BOOL* m_pbAlarmOut = new BOOL[MAX_ALARMOUT_V40];
	if (m_pbAlarmOut == NULL)
	{
		return;
	}

	memset(m_pbAlarmOut,0,sizeof(BOOL)*MAX_ALARMOUT_V40);

	DWORD dwID = 0;
	/*  DWORD dwLoopNum = dwAlarmOutNum;*/
	memset(m_pbAlarmOut,0, sizeof(BOOL)* MAX_ALARMOUT_V40);


	for (i = 0; i < /*g_struDeviceInfo[iDeviceIndex].iAlarmOutNum*/MAX_ALARMOUT_V40; i++)
	{
		m_pbAlarmOut[i] = BOOL(*(bAlarmOut+i));
		if ((i <  g_struDeviceInfo[iDeviceIndex].iAlarmOutNum))
		{
			strTemp.Format(ALARM_OUT_FORMAT, i+1);
			hChanItem =  m_treeAlarmOut.InsertItem(strTemp, 0, 0, TVI_ROOT);
			if (hFirstItem == NULL)
			{
				hFirstItem = hChanItem;
			}
			m_treeAlarmOut.SetItemData(hChanItem, 0*1000 + i);	
			if (m_pbAlarmOut[i])
			{
				m_treeAlarmOut.SetCheck(hChanItem, TRUE);
			}

		}
		else if (i >= MAX_ANALOG_ALARMOUT)
		{
			dwID = g_struDeviceInfo[iDeviceIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i-MAX_ANALOG_ALARMOUT].dwIPID;
			if (dwID != 0)
			{
				int iIPChanIndex = GetIPChannelInfoByIPID(dwID,iDeviceIndex);
				if ( iIPChanIndex <0)
				{
					strTemp.Format(IP_ALARM_OUT_NAME, i+1-MAX_ANALOG_ALARMOUT);
				}
				else
				{
					strTemp.Format(IP_ALARM_OUT_BYCHAN, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iIPChanIndex].chChanName,\
						g_struDeviceInfo[iDeviceIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i-MAX_ANALOG_ALARMOUT].dwAlarmOut);      
				}
				hChanItem =  m_treeAlarmOut.InsertItem(strTemp, 0, 0, TVI_ROOT);
				m_treeAlarmOut.SetItemData(hChanItem, 1*1000 + i);	
				if (m_pbAlarmOut[i])
				{
					m_treeAlarmOut.SetCheck(hChanItem, TRUE);
				}
			}

		}
	}

	//     for (i = MAX_ALARMOUT_V30; i < MAX_ALARMOUT_V40 ; i++)
	//     {
	// 		m_bAlarmOut[i] = FALSE;
	//     }
	m_treeAlarmOut.SelectItem(hFirstItem);//avoid keeping clearing screen
	m_treeAlarmOut.Expand(m_treeAlarmOut.GetRootItem(),TVE_EXPAND);

	if (m_pbAlarmOut != NULL)
	{
		delete[] m_pbAlarmOut;
		m_pbAlarmOut = NULL;
	}
}
//[add] by zja 2014-2-28 
//注： 升级IPC功能时，调用该接口得到的通道号是不正确的，
// 应该将 m_treeChannel.SetItemData(hChanItem, 0*1000 + i);
// 改为m_treeChannel.SetItemData(hChanItem, 0*1000 + g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO)
// 由于好几个地方调用该接口，并没有反映该问题，不做修改。
void g_CreateChannelTree(CTreeCtrl &m_treeChannel, int iDeviceIndex, BOOL *bChannelChecked)
{
	if (iDeviceIndex == -1)
	{
		return;
	}
	m_treeChannel.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	HTREEITEM hFirstItem = NULL;
	DWORD dwID = 0;

	BOOL *pbChanChecked = new BOOL[MAX_CHANNUM_V40];
	if (pbChanChecked == NULL)
	{
		return;
	}

	memset(pbChanChecked,0,sizeof(BOOL)*MAX_CHANNUM_V40);

	for(i = 0; i < g_struDeviceInfo[iDeviceIndex].iDeviceChanNum ; i++)
	{
		if(i < g_struDeviceInfo[iDeviceIndex].iAnalogChanNum)
		{
			if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable)
			{
				pbChanChecked[i] = BOOL(*(bChannelChecked+i));
				strTemp.Format(ANALOG_C_FORMAT, i+1);
				hChanItem =  m_treeChannel.InsertItem(strTemp, 0, 0, TVI_ROOT);
				if (hFirstItem == NULL)
				{
					hFirstItem = hChanItem;
				}

				m_treeChannel.SetItemData(hChanItem, 0 * 1000 + g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO);
				if (bChannelChecked[g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO -1])
				{
					m_treeChannel.SetCheck(hChanItem, TRUE);
				}
			}
		}
		else
		{
			if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable)
			{
				pbChanChecked[i] = BOOL(*(bChannelChecked+i));
				strTemp.Format(IP_CAMERA_NAME, i+1 - g_struDeviceInfo[iDeviceIndex].iAnalogChanNum);
				hChanItem =  m_treeChannel.InsertItem(strTemp, 0, 0, TVI_ROOT);
				if (hFirstItem == NULL)
				{
					hFirstItem = hChanItem;
				}
				m_treeChannel.SetItemData(hChanItem, 0 * 1000 + g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO);
				if (bChannelChecked[g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO -1])
				{
					m_treeChannel.SetCheck(hChanItem, TRUE);
				}
			}
		}
	}
	for(i = 0; i < g_struDeviceInfo[iDeviceIndex].byMirrorChanNum &&i < 16; i++)
	{
		if (g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].bEnable)
		{
			pbChanChecked[i] = BOOL(*(bChannelChecked+i));
			strTemp.Format(MIRROR_C_FORMAT, i+1);
			hChanItem =  m_treeChannel.InsertItem(strTemp, 0, 0, TVI_ROOT);
			if (hFirstItem == NULL)
			{
				hFirstItem = hChanItem;
			}

			m_treeChannel.SetItemData(hChanItem, 0*1000 + i);
			if (bChannelChecked[g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO -1])
			{
				m_treeChannel.SetCheck(hChanItem, TRUE);
			}
		}
	}

	m_treeChannel.SelectItem(hFirstItem);//avoid keeping clearing screen
	m_treeChannel.Expand(m_treeChannel.GetRootItem(),TVE_EXPAND);

	if (pbChanChecked != NULL)
	{
		delete[] pbChanChecked;
		pbChanChecked = NULL;
	}
}

void g_CreateAlarmOutTreeByGroup(CTreeCtrl &m_treeAlarmOut, int iDeviceIndex, BOOL *bAlarmOut, DWORD dwGroupNo)
{
	if (iDeviceIndex == -1)
	{
		return;
	}
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	m_treeAlarmOut.DeleteAllItems();

	HTREEITEM hChanItem = NULL;
	HTREEITEM hFirstItem = NULL;

	BOOL* m_pbAlarmOut = new BOOL[MAX_ALARMOUT_V40];
	if (m_pbAlarmOut == NULL)
	{
		return;
	}

	memset(m_pbAlarmOut,0,sizeof(BOOL)*MAX_ALARMOUT_V40);
	DWORD dwID = 0;


	for (i = (0+ dwGroupNo*MAX_CHANNUM_V30); i < (dwGroupNo+1)*MAX_CHANNUM_V30; i++)
	{
		m_pbAlarmOut[i] = BOOL(*(bAlarmOut+i));
		if ((i <  g_struDeviceInfo[iDeviceIndex].iAlarmOutNum))
		{
			strTemp.Format(ALARM_OUT_FORMAT, i+1);
			hChanItem =  m_treeAlarmOut.InsertItem(strTemp, 0, 0, TVI_ROOT);
			if (hFirstItem == NULL)
			{
				hFirstItem = hChanItem;
			}
			m_treeAlarmOut.SetItemData(hChanItem, 0*1000 + i);	
			if (m_pbAlarmOut[i])
			{
				m_treeAlarmOut.SetCheck(hChanItem, TRUE);
			}

		}
		else if (i >= MAX_ANALOG_ALARMOUT)
		{
			dwID = g_struDeviceInfo[iDeviceIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i-MAX_ANALOG_ALARMOUT].dwIPID;
			if (dwID != 0)
			{
				int iIPChanIndex = GetIPChannelInfoByIPID(dwID,iDeviceIndex);
				if ( iIPChanIndex <0)
				{
					strTemp.Format(IP_ALARM_OUT_NAME, i+1-MAX_ANALOG_ALARMOUT);
				}
				else
				{
					strTemp.Format(IP_ALARM_OUT_BYCHAN, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iIPChanIndex].chChanName,\
						g_struDeviceInfo[iDeviceIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i-MAX_ANALOG_ALARMOUT].dwAlarmOut);      
				}
				hChanItem =  m_treeAlarmOut.InsertItem(strTemp, 0, 0, TVI_ROOT);
				m_treeAlarmOut.SetItemData(hChanItem, 1*1000 + i);	
				if (m_pbAlarmOut[i])
				{
					m_treeAlarmOut.SetCheck(hChanItem, TRUE);
				}
			}

		}
	}
	m_treeAlarmOut.SelectItem(hFirstItem);//avoid keeping clearing screen
	m_treeAlarmOut.Expand(m_treeAlarmOut.GetRootItem(),TVE_EXPAND);

	if (m_pbAlarmOut != NULL)
	{
		delete[] m_pbAlarmOut;
		m_pbAlarmOut = NULL;
	}
}

void g_CreateChannelTreeByGroup(CTreeCtrl &m_treeChannel, int iDeviceIndex, BOOL *bChannelChecked, DWORD dwGroupNo)
{
	if (iDeviceIndex == -1)
	{
		return;
	}
	m_treeChannel.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0,j;
	HTREEITEM hChanItem = NULL;
	HTREEITEM hFirstItem = NULL;
	DWORD dwID = 0;

	BOOL *pbChanChecked = new BOOL[MAX_CHANNUM_V40];
	if (pbChanChecked == NULL)
	{
		return;
	}

	memset(pbChanChecked,0,sizeof(BOOL)*MAX_CHANNUM_V40);

	j = MAX_CHANNUM_V30*dwGroupNo;
	for(i = 0; i < g_struDeviceInfo[iDeviceIndex].iDeviceChanNum ; i++)
	{
		if(i < g_struDeviceInfo[iDeviceIndex].iAnalogChanNum && i>MAX_CHANNUM_V30*dwGroupNo && i<=MAX_CHANNUM_V30*(dwGroupNo+1))
		{
			if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable)
			{
				pbChanChecked[j++] = BOOL(*(bChannelChecked+i));
				strTemp.Format(ANALOG_C_FORMAT, i+1);
				hChanItem =  m_treeChannel.InsertItem(strTemp, 0, 0, TVI_ROOT);
				if (hFirstItem == NULL)
				{
					hFirstItem = hChanItem;
				}

				m_treeChannel.SetItemData(hChanItem, 0*1000 + i);
				if (bChannelChecked[g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO -1])
				{
					m_treeChannel.SetCheck(hChanItem, TRUE);
				}
			}
		}
		else
		{
			if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable&& i>MAX_CHANNUM_V30*dwGroupNo && i<=MAX_CHANNUM_V30*(dwGroupNo+1))
			{
				pbChanChecked[j++] = BOOL(*(bChannelChecked+i));
				strTemp.Format(IP_CAMERA_NAME, i+1 - g_struDeviceInfo[iDeviceIndex].iAnalogChanNum);
				hChanItem =  m_treeChannel.InsertItem(strTemp, 0, 0, TVI_ROOT);
				if (hFirstItem == NULL)
				{
					hFirstItem = hChanItem;
				}
				m_treeChannel.SetItemData(hChanItem, 0*1000 + i);
				if (bChannelChecked[g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO -1])
				{
					m_treeChannel.SetCheck(hChanItem, TRUE);
				}
			}
		}
	}


	m_treeChannel.SelectItem(hFirstItem);//avoid keeping clearing screen
	m_treeChannel.Expand(m_treeChannel.GetRootItem(),TVE_EXPAND);

	if (pbChanChecked != NULL)
	{
		delete[] pbChanChecked;
		pbChanChecked = NULL;
	}
}

/*********************************************************
  Function:	g_CreateLocalDir
  Desc:		create the local directory
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void g_CreateLocalDir()
{
	CString csDir;
	if (g_struLocalParam.chDownLoadPath != NULL)
	{
		csDir.Format("%s\\", g_struLocalParam.chDownLoadPath);
		if (GetFileAttributes(g_struLocalParam.chDownLoadPath) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(csDir, NULL);
		}
	}
	if (g_struLocalParam.chPictureSavePath != NULL)
	{
		csDir.Format("%s\\", g_struLocalParam.chPictureSavePath);
		if (GetFileAttributes(g_struLocalParam.chPictureSavePath) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(csDir, NULL);
		}
	}
	if (g_struLocalParam.chRemoteCfgSavePath != NULL)
	{
		csDir.Format("%s\\", g_struLocalParam.chRemoteCfgSavePath);
		if (GetFileAttributes(g_struLocalParam.chRemoteCfgSavePath) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(csDir, NULL);
		}
	}
}

int g_buflen(char *buf)
{
	char *pos = NULL;
	int iBufLen = 0;
	pos = strchr(buf, '\r');
	if (pos != NULL)
	{
		iBufLen = pos - buf;
		return iBufLen;
	}
	pos = strchr(buf, '\n');
	if (pos != NULL)
	{
		iBufLen = pos - buf;
	}
	return iBufLen;
}

/*********************************************************
  Function:	g_ReadDeviceConfig
  Desc:		read configure of the devices and their channels from "DeviceCfg.dat"
  Input:	
  Output:	
  Return:	
**********************************************************/
void g_ReadDeviceConfig()
{
    DeviceCfgFile::GetInstance().ReadFromFile();
}

/*********************************************************
  Function:	g_ValidIPv6
  Desc:		Is ipv6? 
  Input:	ip
  Output:	none
  Return:	true, false
**********************************************************/
BOOL g_ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) > 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}

	return FALSE;
}

void g_replace(char* pOldString, char* pNewString, char* pSearchString, char* pRepalceString)
{
	string temp2("");
	string searchString("");
	string replaceString("");
	temp2 = temp2.insert(0, pOldString);
	searchString = searchString.insert(0, pSearchString);
	replaceString = replaceString.insert(0, pRepalceString);

    string::size_type pos = 0;
	while ( (pos = temp2.find(searchString, pos)) != string::npos )
	{	
	    temp2.replace( pos, searchString.size(), replaceString);	
	    pos++;	
	}
	strncpy(pNewString,temp2.c_str(),temp2.length());
}

/*********************************************************
  Function:	g_SaveDeviceConfig
  Desc:		save the device configure in "DeivceCfg.dat" 
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void g_SaveDeviceConfig()
{
    DeviceCfgFile::GetInstance().SaveToFile();
}

/*********************************************************
  Function:	ReadLocalConfig
  Desc:		read local configure in "DemoLocalCfg.dat"
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void ReadLocalConfig()
{
    LocalConfigFile::GetInstance().ReadFromFile();
}

/*********************************************************
  Function:	WriteLocalConfig
  Desc:		save local configuration, LocalCfg.dat is called when application exit
  Input:	
  Output:	
  Return:	
**********************************************************/
void WriteLocalConfig()
{
    LocalConfigFile::GetInstance().SaveToFile();
	
	g_CreateLocalDir();
}

/*********************************************************
  Function:	CheckIPStr
  Desc:		check IP address available
  Input:	ip, 
  Output:	
  Return:	TRUE,IP address correct;FALSE,IP address fault;
**********************************************************/
BOOL CheckIPStr(CString ip)
{	//check IP address correct
    char str[64] = { 0 };
	strcpy(str,ip);
    BOOL bIPV4 =  TRUE; 
	char a;
	int dot=0;
	int a3,a2,a1,a0,i = 0;
	a3 = a2 = a1 = a0 = -1;
	if (strlen(str)==0)
		return TRUE;
	while (a=str[i++])
	{
		if ((a==' ')||(a=='.')||((a>='0')&&(a<='9')))
		{
			if (a=='.')
				dot++;
		}
		else
        {
           bIPV4 = FALSE;
        }
			 
	}

    if (!bIPV4)
    {
        
        strcpy(str,ip);
        return g_ValidIPv6((BYTE*)str);
    }
	if (dot!=3)
	{
		return FALSE;
	}
	else
	{
		sscanf(str,"%d.%d.%d.%d",&a3,&a2,&a1,&a0);
		if ((a0>255)||(a1>255)||(a2>255)||(a3>255))
		{
			return FALSE;
		}
		if ((a0 < 0) || (a1 < 0) || (a2 < 0) || (a3 < 0))
		{
			return FALSE;
		}
	}
	return TRUE;
}

/*********************************************************
  Function:	g_StringLanType
  Desc:		get the current operation language string type
  Input:	szLanCn, Chinese string; szLanEn, English string;
  Output:	szDstLan, current string
  Return:	none
**********************************************************/
void g_StringLanType(char *szDstLan, char *szLanCn, char *szLanEn)
{
#ifdef DEMO_LAN_CN
		sprintf(szDstLan, "%s", szLanCn);	
#else	
		sprintf(szDstLan, "%s", szLanEn);
#endif
	return;
    WORD wLangID=(WORD)(PRIMARYLANGID(::GetSystemDefaultLangID()));
    switch(wLangID)
    {
        case LANG_ENGLISH:
			sprintf(szDstLan, "%s", szLanEn);
			break;
		case LANG_CHINESE:
			sprintf(szDstLan, "%s", szLanCn);
			break;
		default:
			sprintf(szDstLan, "%s", szLanEn);
			break;
	}	
}

char szDstLan[1024] = {0};
/*********************************************************
  Function:	g_StringLanType
  Desc:		get the current operation language string type
  Input:	szLanCn, Chinese string; szLanEn, English string;
  Output:	szDstLan, current string
  Return:	none
**********************************************************/
char *gg_StringLanType(char *szLanCn, char *szLanEn, const char* format, ...)
{
	va_list arglist;
	va_start(arglist,format);
	vsprintf(szDstLan, format, arglist); 
	va_end(arglist);
#ifdef DEMO_LAN_CN
		sprintf(szDstLan, "%s%s", szLanCn, szDstLan);	
#else	
		sprintf(szDstLan, "%s%s", szLanEn, szDstLan);
#endif
	return szDstLan;
}

void g_ReadLocalReadSensorAdd()
{
    CFile myFile;
    CString csFilename;

    csFilename.Format("%s\\LocalSensorAdd.dat", g_szWorkDir);
    if (myFile.Open(csFilename, CFile::modeRead) == FALSE)
    {
        myFile.Open(csFilename, CFile::modeCreate);
        return;
	}

    myFile.Read(g_struSensorAddPreview, sizeof(g_struSensorAddPreview));
       
    myFile.Close();
}

void g_SaveLocalReadSensorAdd()
{
    CFile myFile;
    CString csFilename;
    
    csFilename.Format("%s\\LocalSensorAdd.dat", g_szWorkDir);
    if (myFile.Open(csFilename, CFile::modeRead|CFile::modeWrite) == FALSE)
    {
        myFile.Open(csFilename, CFile::modeCreate);
        return;
    }

    myFile.Write(g_struSensorAddPreview, sizeof(g_struSensorAddPreview));
    
    myFile.Close();	
}

int g_DelFromArray(DWORD *dwArray, int iMaxArrayIndex, int iCurIndex)
{
    // TODO: Add your control notification handler code here
    if (dwArray == NULL)
    {
        return FALSE;
    }
    
    DWORD *pArrayTemp = (DWORD *)dwArray;
    int i;
    for (i = 0; i < iMaxArrayIndex -1; i++)
    {
        if (iCurIndex <= i)
        {
            *(pArrayTemp + i) = *(pArrayTemp + i+1);
        }
    }
    *(pArrayTemp + iMaxArrayIndex -1) = 0 ;
    return TRUE;	
}

int g_FindFromArray(DWORD *dwArray, int iMaxArrayIndex, DWORD dwFindValue)
{
    if (dwArray == NULL)
    {
        return -1;
    }
    
    for (int i = 0; i < iMaxArrayIndex ; i++)
    {
        if (dwFindValue == *(dwArray +i))
        {
            return i;
        }
    }
    
    return -1;
}


void g_DrawRect(HDC hDc, NET_VCA_RECT struRect,  CRect rcWnd, DWORD dwCurRect, COLORREF color)
{
	CPen DrawPen;
	// 	COLORREF color;
	// 	color = RGB(255, 255, 0);

	DrawPen.CreatePen(PS_SOLID, 3, color);
	CBrush brTmp;
	brTmp.CreateSolidBrush(color);

	HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
	CRect rect;
	rect.left = (int)(struRect.fX * rcWnd.Width());
	rect.top = (int)(struRect.fY * rcWnd.Height());
	rect.right = (int)((struRect.fX + struRect.fWidth) * rcWnd.Width());
	rect.bottom = (int)((struRect.fY + struRect.fHeight) * rcWnd.Height());
	FrameRect(hDc, rect, brTmp);

	SelectObject(hDc, pOldPen);
	DeleteObject(DrawPen);
}

void g_AddChanInfoToComBox(CComboBox &cmbChanBox, int iDeviceIndex, BOOL bShowOfflineChannel)
{
    if (iDeviceIndex < 0)
    {
        return;
    }
    
	cmbChanBox.ResetContent();

    DWORD dwChanIndex = 0;
    for (int i = 0; i < g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;i++)
    {
        if (bShowOfflineChannel)
        {
            cmbChanBox.AddString(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
            cmbChanBox.SetItemData(dwChanIndex++,g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO);
        }
        else
        {
            if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable)
            {
                cmbChanBox.AddString(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
                cmbChanBox.SetItemData(dwChanIndex++,g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO);
            }
        }
    }
    
    cmbChanBox.SetCurSel(0);
}

BOOL IsDevWinControl(int iDeviceIndex)
{
	if (g_struDeviceInfo[iDeviceIndex].lLoginID < 0)
		return FALSE;
	int	iDeviceType = g_struDeviceInfo[iDeviceIndex].iDeviceType;
    if (iDeviceType == DS_6800M || iDeviceType == DS_64XXHD_S|| iDeviceType == DS_C10S|| iDeviceType == DS_B20_MSU_NP || 
        iDeviceType == DS_MMC_B20_CLASS || iDeviceType == DS_B21_MCU_NP_CLASS || iDeviceType == DS_C10H || iDeviceType == DS_C20N_VWMS || \
        iDeviceType == DS_AIOH_MCU_NP)
	{
		return  TRUE; 
	}
	return FALSE; 
}

//获取传显LCD 串口协议列表 
void GetSerialProto(unsigned int *&pOut, DWORD &dwNum)
{
	//传显串口协议
	static char *pSerialProto[] = {"LCD-S1", "LCD-S2","LCD-L1","LCD-DLP", "LCD-S3","LCD-D20","LCD-L2","LCD-Z1","LCD-D20/D", "LCD-D20/S", 
		"LCD-D20/P", "LCD-D20/T", "LCD-D20/F", "LCD-D20/DF", "LCD-D20/FS", "LCD-D20/FP", "LCD-D20/FT", "LCD-D5022",
		"LCD-D5032", "LCD-D5042+" ,"LCD-D20/Z" };
	pOut = (unsigned int *)pSerialProto; 
	dwNum = sizeof(pSerialProto)/sizeof(pSerialProto[0]); 
} 

float g_GetFloatValue(float fValue)
{
    
    WORD i = (WORD)(fValue*1000000); //解决浮点的精度问题 
    WORD j = (WORD)(fValue*100000);
    
    if (i - j * 10 >= 5)
    {
        j = (WORD)(j + 1) ;
    }
	
    return (j/100000.000000);
}
