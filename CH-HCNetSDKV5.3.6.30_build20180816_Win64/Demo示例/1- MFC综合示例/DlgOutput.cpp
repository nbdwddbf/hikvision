/**********************************************************
FileName:    DlgOutput.cpp
Description: operation to implement preview
Date:        2008/05/17
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp    
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgOutput.h"
#include "HCNetSDK.h"
#include "DrawFun.h"

RECT g_rectZoomInShow;
RECT g_rectZoomInMouse;
NET_VCA_POINT g_struPoint;
int g_iTrackType = 0;

extern BOOL g_bPtzMaualTrace;
extern BOOL g_bStandardCB;
extern HINSTANCE g_hDSSDK;


void CALLBACK RemoteDisplayCBFun(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved);
void CALLBACK DrawNPQState(long lRealHandle, HDC hDc, LONG nUser);

/*********************************************************
  Function:	g_RealDataCallBack_V30
  Desc:		use the player interface to decode the stream
  Input:	lRealHandle, player port;
            dwDataType,data type;
			pBuffer, stream data;
			dwBufSize, data length;
			pUser, user data,here is the current play output window index;
  Output:	
  Return:	
**********************************************************/
void CALLBACK g_RealDataCallBack_V30(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{
	ChannelOpenProc DLINK_HW_ChannelOpen;
	SetStreamOpenModeProc DLINK_HW_SetStreamOpenMode;
	OpenStreamProc DLINK_HW_OpenStream;
	SetDisplayParaProc DLINK_HW_SetDisplayPara;
	PlayProc DLINK_HW_Play;
	InputDataProc DLINK_HW_InputData;
	InputVideoDataProc DLINK_HW_InputVideoData;
	BOOL iRet = FALSE;
	DWORD dwWinIndex = *((unsigned long *)pUser);
	if (dwDataType == NET_DVR_SYSHEAD)
	{
		memcpy(g_dlgOutput[dwWinIndex].m_sHeader, pBuffer, 40);
		g_dlgOutput[dwWinIndex].AddLog(PLAY_SUCC_T, "header %x%x%x%x %d", pBuffer[0],\
			pBuffer[1], pBuffer[2], pBuffer[3], dwBufSize);
	}
	
	if (g_dlgOutput[dwWinIndex].m_bLocalManualRec)
	{
		if (dwBufSize > 0 && g_dlgOutput[dwWinIndex].m_fp != NULL)
		{
			if (!g_dlgOutput[dwWinIndex].m_bSaveHead)
			{
				iRet = fwrite(g_dlgOutput[dwWinIndex].m_sHeader, 1, 40, g_dlgOutput[dwWinIndex].m_fp);
				g_dlgOutput[dwWinIndex].m_bSaveHead =TRUE;			
			}
			if (dwDataType != NET_DVR_SYSHEAD)
			{
                if (g_bStandardCB)
                {
                    iRet = fwrite(&dwBufSize, 1, 4, g_dlgOutput[dwWinIndex].m_fp);
                }
				iRet = fwrite(pBuffer, 1, dwBufSize, g_dlgOutput[dwWinIndex].m_fp);
			}
		}
	}
	if (g_struLocalParam.bNoDecode)
	{
		return;
	}


	//get player port to protect the process safe
	LONG lPort = g_dlgOutput[dwWinIndex].m_lPort;//software decode play handle of software decode
	HANDLE hCardHandle = g_dlgOutput[dwWinIndex].m_hCardHandle;//hardware decode play handle of software decode

	HIK_MEDIAINFO* pTestBuff = NULL;
	WORD	wTemp = 0;
	WORD	wVolumevalue = 0;

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD://coming the stream header, open stream
		
		pTestBuff = (HIK_MEDIAINFO*)pBuffer;
		//card decode /
		if (g_struLocalParam.bUseCard && g_bCardInit)
		{
			//get play handle
			DLINK_HW_ChannelOpen = (ChannelOpenProc)GetProcAddress(g_hDSSDK, "HW_ChannelOpen");
			iRet = DLINK_HW_ChannelOpen(dwWinIndex, &hCardHandle);
			if (iRet != 0)
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "HW_ChannelOpen err[%x]", iRet);
			}
			//save the card handle of corresponding out put window
			g_dlgOutput[dwWinIndex].m_hCardHandle = hCardHandle;
			DLINK_HW_SetStreamOpenMode = (SetStreamOpenModeProc)GetProcAddress(g_hDSSDK, "HW_SetStreamOpenMode");
			iRet = DLINK_HW_SetStreamOpenMode(hCardHandle, (g_dlgOutput[dwWinIndex].m_iNetDelayBufNum+9)/10);
			if (iRet != 0)
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "HW_SetStreamOpenMode err[%x]", iRet);
				g_dlgOutput[dwWinIndex].m_hCardHandle = INVALID_HANDLE_VALUE;
				break;
			}
			//deal with 40 byte head, and start player
			DLINK_HW_OpenStream = (OpenStreamProc)GetProcAddress(g_hDSSDK, "HW_OpenStream");
			iRet = DLINK_HW_OpenStream(hCardHandle, pBuffer, dwBufSize);
			if (iRet != 0)
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "HW_OpenStream err[%x]", iRet);
				g_dlgOutput[dwWinIndex].m_hCardHandle = INVALID_HANDLE_VALUE;
				break;
			}
			else
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_SUCC_T, "HW_OpenStream buf[%d]",  (g_dlgOutput[dwWinIndex].m_iNetDelayBufNum+9)/10);
			}
			//set play area and mode
			DISPLAY_PARA struCardPlayInfo;
			struCardPlayInfo.nLeft = g_dlgOutput[dwWinIndex].m_struCardPlayParam.nLeft;
			struCardPlayInfo.nTop = g_dlgOutput[dwWinIndex].m_struCardPlayParam.nTop;
			struCardPlayInfo.nWidth = g_dlgOutput[dwWinIndex].m_struCardPlayParam.nWidth;
			struCardPlayInfo.nHeight = g_dlgOutput[dwWinIndex].m_struCardPlayParam.nHeight;
			struCardPlayInfo.bToScreen = 1;
			struCardPlayInfo.bToVideoOut = 1;
			DLINK_HW_SetDisplayPara = (SetDisplayParaProc)GetProcAddress(g_hDSSDK, "HW_SetDisplayPara");
			iRet = DLINK_HW_SetDisplayPara(hCardHandle, &struCardPlayInfo);
			if (iRet != 0)
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "HW_SetDisplayPara err[%x]", iRet);
				g_dlgOutput[dwWinIndex].m_hCardHandle = INVALID_HANDLE_VALUE;
				break;
			}
			//start to play
			DLINK_HW_Play = (PlayProc)GetProcAddress(g_hDSSDK, "HW_Play");
			iRet = DLINK_HW_Play(hCardHandle);
			if (iRet != 0)
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "HW_Play err[%x]", iRet);
				g_dlgOutput[dwWinIndex].m_hCardHandle = INVALID_HANDLE_VALUE;			
			}
			break;
		}
		///////////////////////////////////////////////////////////////////
		//soft decode
		
        if (lPort < 0)
        {
            //PlayM4_FreePort(lPort);
			if (!PlayM4_GetPort(&lPort))
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "PlayM4_GetPort");
				break;
			}
			else
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_SUCC_T, "PlayM4_GetPort");
			}
        }

		//set the port of the out put window
		g_dlgOutput[dwWinIndex].m_lPort = lPort;

		
	
		if (dwBufSize > 0)
		{   
			if(strcmp(g_sSecretKey, "StreamNotEncrypt") != 0)
			{
				if(!PlayM4_SetSecretKey(lPort, 1, g_sSecretKey, 128))
				{
					g_dlgOutput[dwWinIndex].AddLog(OPERATION_FAIL_T, "PlayM4_SetSecretKey %d", PlayM4_GetLastError(lPort));
				}
			}
			
			//set as stream mode, real-time stream under preview
			if (!PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME))
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "PlayM4_SetStreamOpenMode err[%d]", PlayM4_GetLastError(lPort));
			}
			//start player
			if (!PlayM4_OpenStream(lPort, pBuffer, dwBufSize, 2*1024*1024))
			{
				g_dlgOutput[dwWinIndex].m_lPort = -1;
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "PlayM4_OpenStream err[%d]", PlayM4_GetLastError(lPort));
				break;
			}
			//set soft decode display callback function to capture
			if (!PlayM4_SetDisplayCallBack(lPort, RemoteDisplayCBFun))
			{
				g_pMainDlg->AddLog(-1, PLAY_FAIL_T, "PlayM4_SetDisplayCallBack err[%d]", PlayM4_GetLastError(lPort));
			}
			//set frame buffer number
			if (!PlayM4_SetDisplayBuf(lPort, g_dlgOutput[dwWinIndex].m_iNetDelayBufNum))
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "PlayM4_SetDisplayBuf [%d] err[%d]", g_dlgOutput[dwWinIndex].m_iNetDelayBufNum, PlayM4_GetLastError(lPort));
			}
			
			//start play, set play window
			if (!PlayM4_Play(lPort, g_dlgOutput[dwWinIndex].m_hWnd))
			{
				g_dlgOutput[dwWinIndex].m_lPort = -1;
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "PlayM4_Play err[%d]", PlayM4_GetLastError(lPort));
				break;
			}


			
			//set display mode
			if (!PlayM4_SetOverlayMode(lPort, FALSE, COLORREF(0)))//play off screen
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "PlayM4_SetOverlayMode err[%d]", PlayM4_GetLastError(lPort));
			}

			//set discarded B frame number
			if (g_struLocalParam.dwBFrameNum > 0)
			{
				if (!PlayM4_ThrowBFrameNum(lPort, g_struLocalParam.dwBFrameNum))
				{
					g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "PlayM4_ThrowBFrameNum err[%d]", PlayM4_GetLastError(lPort));
				}
			}

            if (8 == g_dlgOutput[dwWinIndex].m_dwLinkMode)
            {
                //回调状态信息
                PlayM4_RegisterDrawFun(lPort, DrawNPQState, (LONG)dwWinIndex);
            }

		}
		
		/*预览声音*/	
		wTemp = (0xFFFF) / 100;
		wVolumevalue = (WORD)(50 * wTemp);
		if (g_dlgOutput[dwWinIndex].m_bPlaySound)
		{
			g_dlgOutput[dwWinIndex].StopSound();
		}
		else// if (g_bShareSound)
		{
			g_dlgOutput[dwWinIndex].StartSound(wVolumevalue);
		}
		break;
	case NET_DVR_STD_VIDEODATA:
	case NET_DVR_STD_AUDIODATA:
	case NET_DVR_STREAMDATA:
		//start card decode
		if (g_struLocalParam.bUseCard && g_bCardInit)
		{
			if (dwBufSize > 0 && hCardHandle != INVALID_HANDLE_VALUE)
			{
				DLINK_HW_InputData = (InputDataProc)GetProcAddress(g_hDSSDK, "HW_InputData");
				iRet = DLINK_HW_InputData(hCardHandle, pBuffer, dwBufSize);
				if (iRet <= 0)
				{
					g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "HW_InputData err[%d]", iRet);
				}
			}
			break;
		}

		//start soft decode
		if (dwBufSize > 0 && lPort != -1)
		{
// 			char szTemp[32] = {0};
// 			sprintf(szTemp, "PlayM4_InputData: data size is %d\n", dwBufSize);
// 			OutputDebugString(szTemp);
			if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "PlayM4_InputData err[%d]", PlayM4_GetLastError(lPort));
			}
		}
		break;
	case NET_DVR_AUDIOSTREAMDATA:
		if (g_struLocalParam.bUseCard && g_bCardInit)
		{
			if (dwBufSize > 0 && hCardHandle != NULL)
			{
				DLINK_HW_InputVideoData = (InputVideoDataProc)GetProcAddress(g_hDSSDK, "HW_InputVideoData");
				if (DLINK_HW_InputVideoData(hCardHandle, pBuffer, dwBufSize) != 0)
				{
					g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "HW_InputVideoData");
				}
			}
			break;
		}
		if (dwBufSize > 0 && lPort != -1)
		{
			if (!PlayM4_InputVideoData(lPort, pBuffer, dwBufSize))
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "PlayM4_InputVideoData err[%d]", PlayM4_GetLastError(lPort));
			}
		}
		break;

	default:   //如果是rtp流类型，可能不在上述范围之内，也是需要将数据塞到播放库中的
		if (dwBufSize > 0 && lPort != -1)
		{
			// 			char szTemp[32] = {0};
			// 			sprintf(szTemp, "PlayM4_InputData: data size is %d\n", dwBufSize);
			// 			OutputDebugString(szTemp);
			if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
			{
				g_dlgOutput[dwWinIndex].AddLog(PLAY_FAIL_T, "PlayM4_InputData err[%d]", PlayM4_GetLastError(lPort));
			}
		}
		break;
	}
	
    PlayM4_GetPictureSize(lPort, &g_dlgOutput[dwWinIndex].m_iWidth, &g_dlgOutput[dwWinIndex].m_iHeight);
	return ;
}


/*********************************************************
  Function:	g_fStdDataCallBack
  Desc:		the call back function to deal standard stream
  Input:	lRealHandle,the handle of real play return;
			dwDataType,the type of data;
			pBuffer, point ot stream buffer;
			dwBufSize, the size of the buffer;
			dwUser, the user data;
  Output:	none
  Return:	none
**********************************************************/
void CALLBACK g_fStdDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser)
{
	if (g_bStandardCB)
	{
		g_RealDataCallBack_V30(lRealHandle, dwDataType, pBuffer, dwBufSize, &dwUser);
	}
	
}

/*********************************************************
  Function:	DrawFunZoomInInside
  Desc:		the callback function to draw on video which set by interface NET_DVR_RigisterDrawFun
  Input:	lRealHandle, the return handle of real play;
			hDc, the device content;
			dwUser, the data of user;
  Output:	none
  Return:	none
**********************************************************/
void CALLBACK DrawFunZoomInInside(LONG lRealHandle,HDC hDc, DWORD dwUser)
{
    for (int i = 0; i < 32; i++)
    {
        if (g_dlgOutput[i].m_lPlayHandle >=0 && g_dlgOutput[i].m_lPlayHandle < 512)
        {
            if (lRealHandle == g_dlgOutput[i].m_lPlayHandle)
            {
                g_dlgOutput[i].DrawSensorValuText(hDc, g_dlgOutput[i].m_csDeviceIP, g_dlgOutput[i].m_lChannel);
            }
        }
    }
	::DrawEdge(hDc, &g_rectZoomInShow, BDR_SUNKENOUTER, BF_RECT);
	
	SetBkMode(hDc, TRANSPARENT);
}

void CALLBACK DrawNPQState(long lRealHandle, HDC hDc, LONG nUser)
{
    //DWORD dwWinIndex = *((unsigned long *)nUser);
    LONG dwWinIndex = nUser;
    char szBuffer[256] = { 0 };
    int iPos = 0;

    int nFontSize = 0;
    if (g_struLocalParam.bEnlarged)
    {
        if (g_struLocalParam.bFullScreen)
        {
            nFontSize = 2;
        }
        else
        {
            nFontSize = 1;
        }
    }
    else
    {
        nFontSize = 0;
    }

    RECT rect;
    //rect.left = 100;
    //rect.top = 300;
    //rect.right = 600;
    //rect.bottom = 600;
    memset(&rect, 0, sizeof(rect));
    GetClientRect(g_dlgOutput[dwWinIndex].m_hWnd, &rect);

    //     NET_SDK_NPQ_STATE struStat = { 0 };
    //     if (!NET_DVR_GetNPQStat(g_dlgOutput[dwWinIndex].m_lPlayHandle, &struStat))
    //     {
    //         return;
    //     }

    iPos += _snprintf(szBuffer, sizeof(szBuffer), "Real RTT: %dms\n", g_dlgOutput[dwWinIndex].m_struNPQStat.struVideoState.dwRealRttUs / 1000);
    iPos += _snprintf(szBuffer + iPos, sizeof(szBuffer) - iPos, "Bitrate: %dkbps\n", g_dlgOutput[dwWinIndex].m_struNPQStat.struVideoState.dwBitRate / 1024);
    iPos += _snprintf(szBuffer + iPos, sizeof(szBuffer) - iPos, "Packet Loss Rate: %2.2f%%\n", (float)g_dlgOutput[dwWinIndex].m_struNPQStat.struVideoState.byLossFraction * 100 / 256);
    iPos += _snprintf(szBuffer + iPos, sizeof(szBuffer) - iPos, "Packet Loss Rate(corrected): %2.2f%%\n", (float)g_dlgOutput[dwWinIndex].m_struNPQStat.struVideoState.byLossFraction2 * 100 / 256);
    iPos += _snprintf(szBuffer + iPos, sizeof(szBuffer) - iPos, "Resolution: %dx%d\n", g_dlgOutput[dwWinIndex].m_iWidth, g_dlgOutput[dwWinIndex].m_iHeight);

    CFont cFont;
    if (0 == nFontSize)
    {
        rect.top += 40;
        rect.left += 4;
        cFont.CreateFont(14, 8, 0, 0, FW_DONTCARE, false, false, false,
            GB2312_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            FF_DONTCARE, "宋体");

    }
    else if (1 == nFontSize)
    {
        rect.top += 40 * 2;
        rect.left += 4 * 2;
        cFont.CreateFont(28, 16, 0, 0, FW_DONTCARE, false, false, false,
            GB2312_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            FF_DONTCARE, "宋体");
    }
    else if (2 == nFontSize)
    {
        rect.top += 40 * 3;
        rect.left += 4 * 3;
        cFont.CreateFont(42, 24, 0, 0, FW_DONTCARE, false, false, false,
            GB2312_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            FF_DONTCARE, "宋体");
    }

    CPen DrawPen;
    DrawPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    SetTextColor(hDc, RGB(255, 0, 0));
    SetBkMode(hDc, TRANSPARENT);

    SelectObject(hDc, cFont);

    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);

    DrawText(hDc, szBuffer, strlen(szBuffer), &rect, DT_WORDBREAK);

    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
    DeleteObject(cFont);
    return;
}


/*********************************************************
  Function:	DrawFunZoomIn
  Desc:		the callback function to draw on video which set by interface PlayM4_RigisterDrawFun
  Input:	nPort, the return handle of PlayM4_GetPort;
			hDc, the device content;
			nUser, the data of user;
  Output:	none
  Return:	none
**********************************************************/
void CALLBACK DrawFunZoomIn(long nPort,HDC hDc, long nUser)
{
	::DrawEdge(hDc, &g_rectZoomInShow, BDR_SUNKENOUTER, BF_RECT);
	
	SetBkMode(hDc, TRANSPARENT);
}

/*********************************************************
  Function:	DisplayCBFun
  Desc:		the call back function to snatch the bmp pictrue
  Input:	nPort,port;pBuf,pic buffer;nSize,pic size;nWidth,pic width;nHeight,pic height;nType,type;
  Output:	none
  Return:	none
**********************************************************/
void CALLBACK RemoteDisplayCBFun(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved)
{
	int i=0;
	int iWndIndex = 0;
  	for (i=0; i<MAX_OUTPUTS; i++)
	{
		if (g_dlgOutput[i].m_lPort == nPort)
		{
			iWndIndex = i;
			break;
		}
	}
	if (i == MAX_OUTPUTS)
	{
		return;
	}
	if (!g_bCapPic[iWndIndex])
	{
		return;
	}

    //switch function, time-consuming, do not call if you do not want to save pic
	char szFileName[256] = {0};
	CTime time=CTime::GetCurrentTime();
	PCHANNEL_INFO pChanInfo = &(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_struChanInfo);
	sprintf(szFileName, "%s\\Preview_%s_%02d_%4d%02d%02d_%02d%02d%02d_%d.bmp", \
		g_struLocalParam.chPictureSavePath, g_struDeviceInfo[pChanInfo->iDeviceIndex].chDeviceIPInFileName, \
		g_struDeviceInfo[pChanInfo->iDeviceIndex].iStartChan+pChanInfo->iChanIndex,\
		time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), GetTickCount());
	if (!PlayM4_ConvertToBmpFile(pBuf, nSize, nWidth, nHeight, nType, szFileName))
	{
		g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), PLAY_FAIL_T, "PlayM4_ConvertToBmpFile");
	}
	else
	{
		g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), PLAY_SUCC_T, "PlayM4_ConvertToBmpFile [%s]", szFileName);
	}
	g_bCapPic[iWndIndex]=FALSE;
}

// CDlgOutput dialog

/*********************************************************
  Function:	CDlgOutput
  Desc:		Constructor
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgOutput, CDialog)
CDlgOutput::CDlgOutput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOutput::IDD, pParent)
	, m_lPlayHandle(-1)
	, m_bPlaySound(FALSE)//enable audio under preview by default 
    , m_bShowOSD(FALSE)
    , m_lDeviceType(-1)
	, m_iNetDelayBufNum(1)
	, m_bLocalManualRec(FALSE)
	, m_lChangeFileNameTime(0)
	, m_iSubWndIndex(-1)
	, m_hChanItem(NULL)
	, m_lPort(-1)
	, m_bRestart(FALSE)
	, m_bSaveHead(FALSE)
{
	memset(&m_struCardPlayParam, 0, sizeof(NET_DVR_DISPLAY_PARA));
    memset(&m_struZeroZoomCfg, 0, sizeof(m_struZeroZoomCfg));
    m_lChannel = -1;     // 通道号
    m_iHeight = 0;
    m_iWidth = 0;
    m_dwLinkMode = 0;
    m_pNpqTimer = NULL;
    memset(&m_struNPQStat, 0, sizeof(m_struNPQStat));
}

/*********************************************************
  Function:	~CDlgOutput
  Desc:		destructor
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
CDlgOutput::~CDlgOutput()
{
	m_hChanItem = NULL;
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOutput)	
        //}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgOutput, CDialog)
	//{{AFX_MSG_MAP(CDlgOutput)	
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_COMMAND(ID_MENU_NEXT_PAGE, OnMenuNextPage)
	ON_COMMAND(ID_MENU_FRONT_PAGE, OnMenuFrontPage)
	ON_COMMAND(ID_MENU_PAUSE_CYCLE, OnMenuPauseCycle)
	ON_COMMAND(ID_MENU_SOUND, OnMenuSound)
	ON_COMMAND(ID_MENU_MULTI_SCREEN, OnMenuMultiScreenLarge)
	ON_COMMAND(ID_MENU_STOP_PLAY, OnMenuStopPlay)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_ZERO_FRONT_PAGE, OnMenuZeroFrontPage)
	ON_COMMAND(ID_MENU_ZERO_NEXT_PAGE, OnMenuZeroNextPage)
    ON_COMMAND(ID_MENU_SHOWOSD, OnMenuShowOSD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgOutput message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		initialize dialog
  Input:	none
  Output:	none
  Return:	TRUE, means successful;FALSE, means failed;	
**********************************************************/
BOOL CDlgOutput::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_hWnd = GetSafeHwnd();
	return TRUE; 
}

/*********************************************************
  Function:	OnPaint
  Desc:		update dialog image
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::OnPaint()
{
	CPaintDC dc(this);

	if (g_struLocalParam.bUseCard)
	{
		NET_DVR_RestoreSurface_Card();
	}
	DrawOutputBorder();
}

/*************************************************
Function:	 DrawOutputBorder	
Description: draw preview window output border
Input:		 none
Output:      none
Return:		 none
*************************************************/
void CDlgOutput::DrawOutputBorder(void)
{
	if (!IsWindowVisible())
	{
		return;
	}

	CPen *pOldPen = NULL;
	CPen pPen;
	CRect rc(0,0,0,0);
	GetWindowRect(&rc);
	g_pMainDlg->GetDlgItem(IDC_STATIC_PREVIEWBG)->ScreenToClient(&rc);   
	if (g_pMainDlg->m_iCurWndIndex == m_iSubWndIndex)
	{
		pPen.CreatePen(PS_SOLID, 2, RGB(0,255,0));//green
	}
	else
	{
		pPen.CreatePen(PS_SOLID, 2, RGB(125, 125, 116));  
	}
// 	rc.top-=1;
// 	rc.left-=1;
	rc.right += OUTPUT_INTERVAL/2;
	rc.bottom += OUTPUT_INTERVAL/2;

	CDC *pDC = g_pMainDlg->GetDlgItem(IDC_STATIC_PREVIEWBG)->GetDC();   
	ASSERT(pDC);

	pDC->SelectStockObject(NULL_BRUSH);
	pOldPen = pDC->SelectObject(&pPen);
	pDC->Rectangle(&rc);
	if (g_struLocalParam.bNoDecode && !g_struLocalParam.bUseCard)
	{
		CString csTxt;
		if (m_lPlayHandle>=0)
		{
			csTxt.Format("play");
		}
		else
		{
			csTxt.Format("stop");
		}
		
		pDC->DrawText(csTxt, rc, DT_CENTER);
	}

	if (pOldPen)
	{
		pDC->SelectObject(pOldPen);
	}

	ReleaseDC(pDC);
}

/*********************************************************
  Function:	OnLButtonDown
  Desc:		left click and drag with control button to draw the zoom in area
  Input:	nFlags,the flag message of mouse;
			point, the position of the mouse click;			
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::OnLButtonDown(UINT nFlags, CPoint point)
{
	ChangeCurWinCfg();	
	
    if (MK_SHIFT & nFlags && (m_lPlayHandle != -1) && m_struChanInfo.iChanIndex >= ZERO_CHAN_INDEX)
    {
        int iZeroChan = m_struChanInfo.iChanIndex - ZERO_CHAN_INDEX + g_struDeviceInfo[m_struChanInfo.iDeviceIndex].iStartChan;
        DWORD dwReturned = 0;
        if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_struChanInfo.iDeviceIndex].lLoginID, NET_DVR_GET_ZERO_ZOOM, iZeroChan, &m_struZeroZoomCfg, sizeof(m_struZeroZoomCfg), &dwReturned))
        {
            AddLog(OPERATION_FAIL_T, "NET_DVR_GET_ZERO_ZOOM Chan[%d] State[%d]PreNum[%d]",
                iZeroChan, m_struZeroZoomCfg.byState, m_struZeroZoomCfg.byPreviewNumber);

        }
        else
        {
            AddLog(OPERATION_SUCC_T, "NET_DVR_GET_ZERO_ZOOM Chan[%d]State[%d]PreNum[%d]",iZeroChan, m_struZeroZoomCfg.byState, m_struZeroZoomCfg.byPreviewNumber);

            char chPreSeq[256] = {0};
            CString str;
            for (int i = 0; i < MAX_WINDOW_V30; i++)
            {
                sprintf(chPreSeq, "%d[%d]", i, m_struZeroZoomCfg.byPreviewSeq[i]);
                str += chPreSeq;
                if ((i+1)%8 == 0)
                {
                    AddLog(OPERATION_SUCC_T, "PreSeq %s", str);
                    str = "";
                }
            }
            AddLog(OPERATION_SUCC_T, "PreSeq %s", str);
        }
        
        CRect  rcWnd(0,0,0,0);
        GetWindowRect(&rcWnd);

        m_struZeroZoomCfg.struPoint.fX  = (float)(point.x)/(float)rcWnd.Width();
        m_struZeroZoomCfg.struPoint.fY = (float)(point.y)/(float)rcWnd.Height();

        if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_struChanInfo.iDeviceIndex].lLoginID, NET_DVR_SET_ZERO_ZOOM, iZeroChan, &m_struZeroZoomCfg, sizeof(m_struZeroZoomCfg)))
        {
            AddLog(OPERATION_FAIL_T, "NET_DVR_SET_ZERO_ZOOM Chan[%d]", iZeroChan);
        }
        else
        {
            AddLog(OPERATION_SUCC_T, "NET_DVR_SET_ZERO_ZOOM Chan[%d]", iZeroChan);
        }

    }
    
	if (MK_CONTROL&nFlags)
	{
		if (g_bPtzMaualTrace)
		{
			CRect  rcWnd(0,0,0,0);
            GetWindowRect(&rcWnd);
			if (point.x < 0)
			{
				point.x = 0;
			}
			g_struPoint.fX=(float)(point.x)/(float)rcWnd.Width();
			if (point.y < 0)
			{
				point.y = 0;
			}
			g_struPoint.fY=(float)(point.y)/(float)rcWnd.Height();
			AddLog(OPERATION_SUCC_T, "x%d-y%d", point.x, point.y);
		}
		else
		{
			if (m_lPlayHandle >= 0 && g_bInSide)
			{
				NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawFunZoomInInside, 0);
			}
			else if (m_lPort >= 0)
			{
				PlayM4_RigisterDrawFun(m_lPort, DrawFunZoomIn, 0);
			}
			if (point.x < 0)
			{
				point.x = 0;
			}
			g_rectZoomInMouse.left=point.x;
			if (point.y < 0)
			{
				point.y = 0;
			}
			g_rectZoomInMouse.top=point.y;
			g_rectZoomInMouse.right=g_rectZoomInMouse.left;
			g_rectZoomInMouse.bottom=g_rectZoomInMouse.top;
			POINT tPoint=point;
			g_rectZoomInShow.left=tPoint.x;
			g_rectZoomInShow.top=tPoint.y;
			g_rectZoomInShow.right=tPoint.x;
			g_rectZoomInShow.bottom=tPoint.y;
			AddLog(OPERATION_SUCC_T, "x%d-y%d x%d-y%d x%d-y%d x%d-y%d", point.x, point.y, m_iXPrecision, m_iYPrecision,\
				g_rectZoomInMouse.left, g_rectZoomInMouse.top,\
			g_rectZoomInMouse.right, g_rectZoomInMouse.bottom);
		}
	}
	WORD	wTemp = 0;
	WORD	wVolumevalue = 0;
	wTemp = (0xFFFF) / 100;
	wVolumevalue = (WORD)(50 * wTemp);
	if (m_bPlaySound)
	{
		StopSound();
	}
	else// if (g_bShareSound)
	{
		StartSound(wVolumevalue);
	}
	CDialog::OnLButtonDown(nFlags, point);
}

/*********************************************************
  Function:	OnCtlColor
  Desc:		change the color of background
  Input:	pDC, point to device content;
			pWnd, point to the window of dialog;
			nCtlColor,the color of the control;
  Output:	none
  Return:	the brush of the dialog
**********************************************************/
HBRUSH CDlgOutput::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (g_struLocalParam.bUseCard && g_bCardInit)
	{
		hbr = g_hPlayHardBgBrush;
	}
	else
	{
		hbr = g_hPlaySoftBgBrush;
	}
	return hbr;
}

void CALLBACK g_RealDataCallBack_V30_Test(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{
    OutputDebugString("pyd---Get data,the size is d.\n");
}
/*********************************************************
  Function:	StartPlayInsideDecode
  Desc:		begin to preview and decode by RealPlay interface
  Input:	pChanInfo：the information of the channel;
			hChanItem：point to the channel item information;
  Output:	none
  Return:	the play handle
**********************************************************/
LONG CDlgOutput::StartPlayInsideDecode(PCHANNEL_INFO pChanInfo, HTREEITEM hChanItem)
{
	int iDeviceIndex = pChanInfo->iDeviceIndex;
	int iChanIndex   = pChanInfo->iChanIndex;
    
	CString csLog = _T("");
	StopPlay();
	if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].lRealHandle < 0)
	{
		if (g_struLocalParam.bUseCard && g_bCardInit)
		{		
			NET_DVR_CARDINFO struCardPlayInfo = {0};
			struCardPlayInfo.struDisplayPara.nLeft = m_struCardPlayParam.nLeft;
			struCardPlayInfo.struDisplayPara.nTop = m_struCardPlayParam.nTop;
			struCardPlayInfo.struDisplayPara.nWidth = m_struCardPlayParam.nWidth;
			struCardPlayInfo.struDisplayPara.nHeight = m_struCardPlayParam.nHeight;
			struCardPlayInfo.struDisplayPara.bToScreen = 1;
			struCardPlayInfo.struDisplayPara.bToVideoOut = 1;

		//	struCardPlayInfo.lChannel = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
			struCardPlayInfo.lChannel = m_lChannel;
			struCardPlayInfo.lLinkMode = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwProtocol;
//			struCardPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;// require pointer assignment
			//start card decode
			m_lPlayHandle = NET_DVR_RealPlay_Card(g_struDeviceInfo[iDeviceIndex].lLoginID, &struCardPlayInfo, m_iSubWndIndex);
		}
		else
		{
			NET_DVR_PREVIEWINFO struPlayInfo = {0};


			if (g_struLocalParam.bNoDecode)
			{
				struPlayInfo.hPlayWnd = NULL;
			}
			else
			{
				struPlayInfo.hPlayWnd = GetSafeHwnd();
			}
			
			struPlayInfo.lChannel = pChanInfo->iChannelNO;
//			struPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;
			struPlayInfo.dwLinkMode = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwLinkMode;
			struPlayInfo.dwStreamType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwStreamType;

			//start soft decode
			struPlayInfo.byPreviewMode = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwPreviewMode;
			struPlayInfo.bBlocked = g_struLocalParam.bPreviewBlock;
			struPlayInfo.bPassbackRecord = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].bPassbackRecord;
			struPlayInfo.byProtoType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].nPreviewProtocolType;
            struPlayInfo.byVideoCodingType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].nVideoCodingType;
            struPlayInfo.dwDisplayBufNum = m_iNetDelayBufNum;
            if (!g_struDeviceInfo[iDeviceIndex].byURL)
            {
                m_lPlayHandle = NET_DVR_RealPlay_V40(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfo, NULL, &m_iNetDelayBufNum);
            }
            else
            {
                NET_DVR_PREVIEWINFO_SPECIAL struPlayInfoSp = { 0 };
                struPlayInfoSp.hPlayWnd = struPlayInfo.hPlayWnd;
                struPlayInfoSp.bBlocked = g_struLocalParam.bPreviewBlock;
                struPlayInfoSp.dwDisplayBufNum = m_iNetDelayBufNum;
                strncpy(struPlayInfoSp.sURL, g_struDeviceInfo[iDeviceIndex].szURL, strlen(g_struDeviceInfo[iDeviceIndex].szURL));
                //strncpy(struPlayInfoSp.sURL,"rtsp://admin:abcd12345@10.7.37.2:554/Streaming/Channels/101?transportmode=unicast",1024);
                m_lPlayHandle = NET_DVR_RealPlaySpecial(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfoSp, NULL, NULL);
            }
		}
	}

	if (m_lPlayHandle >= 0)
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V40 %s stream[%d] pro[%d]",\
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName, \
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwProtocol>>31 &0x1, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwProtocol&0xff);
        if (NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawFunZoomInInside, NULL))
        {
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RigisterDrawFun");
        }
        else
        {
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun");
        }

		if (g_bShareSound)
		{
			m_bPlaySound = TRUE;
		}
		
	//	if (!NET_DVR_MakeKeyFrame(g_struDeviceInfo[iDeviceIndex].lLoginID,  g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO))    //重置I帧
		NET_DVR_I_FRAME struIFrame;
		memset(&struIFrame, 0, sizeof(struIFrame));
		struIFrame.dwSize = sizeof(NET_DVR_I_FRAME);
        if (g_struDeviceInfo[iDeviceIndex].byMirrorChanNum > 0 && iChanIndex >= MIRROR_CHAN_INDEX)
		{
            struIFrame.dwChan = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].iChannelNO;
		}
		else
		{
			struIFrame.dwChan = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
		}
		struIFrame.byStreamType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwStreamType;
		if(!NET_DVR_RemoteControl(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_MAKE_I_FRAME, &struIFrame, sizeof(struIFrame)))
		{
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MAKE_I_FRAME %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
		}	
		//set player buffer
//  		if (!NET_DVR_SetPlayerBufNumber(m_lPlayHandle,m_iNetDelayBufNum))
//  		{
// 			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetPlayerBufNumber[%d] %s",m_iNetDelayBufNum, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
//  		}

		if (g_struLocalParam.dwBFrameNum > 0)
		{
 			if (!NET_DVR_ThrowBFrame(m_lPlayHandle, g_struLocalParam.dwBFrameNum))
 			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ThrowBFrame[%d] %s",g_struLocalParam.dwBFrameNum, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
 			}
		}


		g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(FALSE);

		m_hChanItem = hChanItem;
		memcpy(&m_struChanInfo, pChanInfo, sizeof(CHANNEL_INFO));
		g_struDeviceInfo[pChanInfo->iDeviceIndex].pStruChanInfo[pChanInfo->iChanIndex].lRealHandle = m_lPlayHandle;
			//set channel node icon of device tree in main interface
		
		::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iChanIndex));		
		ChangeCurWinCfg();
		//if auto record, call record interface at once
		if (g_struLocalParam.bAutoRecord)
		{
			g_pMainDlg->OnTimer(AUTORECORD_TIMER);
		}
	}
	else
	{
 		g_pMainDlg->AddLog(pChanInfo->iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V40 chanindex[%d] stream[%d] pro[%d]", \
 			iChanIndex, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwProtocol>>31 &0x1, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwProtocol&0xff);

		int iErr = NET_DVR_GetLastError();
		TRACE("err = %d\n", iErr);
		if (iErr == NET_DVR_CHANNEL_ERROR && !g_bPlayAllDevice)
		{//should do this
			g_pMainDlg->DoGetDeviceResoureCfg(pChanInfo->iDeviceIndex);
			g_pMainDlg->RedrawDeviceNode(pChanInfo->iDeviceIndex);
		}	
	}

	return m_lPlayHandle;
}

/*********************************************************
  Function:	StartPlay
  Desc:		begin to preview and decode by RealPlay interface
  Input:	pChanInfo：the information of the channel;
			hChanItem：point to the channel item information;
  Output:	none
  Return:	the play handle
**********************************************************/
LONG CDlgOutput::StartPlay(PCHANNEL_INFO pChanInfo, HTREEITEM hChanItem)
{

    int iDeviceIndex = pChanInfo->iDeviceIndex;
    int iChanIndex   = pChanInfo->iChanIndex;
    
    //debug
    //iChanIndex = 0;
    //pChanInfo->iChannelNO = 1;
    //iDeviceIndex = 0;

    //DEBUG
    //NET_DVR_PREVIEWINFO_SPECIAL struPlayInfoSp = { 0 };
    //struPlayInfoSp.hPlayWnd = GetSafeHwnd();
    //struPlayInfoSp.bBlocked = g_struLocalParam.bPreviewBlock;
    //struPlayInfoSp.dwDisplayBufNum = m_iNetDelayBufNum;
    //strncpy(struPlayInfoSp.sURL, "rtsp://admin:abcd12345@10.7.37.2:554/Streaming/Channels/101?transportmode=unicast", 1024);
    ////strncpy(struPlayInfoSp.sURL,"rtsp://admin:abcd12345@10.7.37.2:554/Streaming/Channels/101?transportmode=unicast",1024);
    //m_lPlayHandle = NET_DVR_RealPlaySpecial(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfoSp, NULL, NULL);
    //return m_lPlayHandle;

    m_lChannel = pChanInfo->iChannelNO; //iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
    int iTmpChan = (DWORD)m_lChannel >> 24;
    if (m_lChannel < 0 && iTmpChan != 0x000000ff)
    {
        return -1;
    }

    if (iDeviceIndex < 0 || iChanIndex < 0)
    {
        return -1;
    }
 
    m_csDeviceIP = g_struDeviceInfo[iDeviceIndex].chDeviceIP;

	if (g_bInSide)
	{
		return StartPlayInsideDecode(pChanInfo, hChanItem);
	}

	CString csLog = _T("");
	StopPlay();
	if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].lRealHandle < 0)
	{
		NET_DVR_PREVIEWINFO struPlayInfo = {0};
		struPlayInfo.hPlayWnd = NULL;	
		struPlayInfo.lChannel = m_lChannel;//iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
		struPlayInfo.dwLinkMode = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwLinkMode;
        m_dwLinkMode = struPlayInfo.dwLinkMode; //保存起来
		struPlayInfo.dwStreamType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwStreamType;
	//	struPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;
		struPlayInfo.byPreviewMode = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwPreviewMode;
		struPlayInfo.bBlocked = g_struLocalParam.bPreviewBlock;
		struPlayInfo.bPassbackRecord = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].bPassbackRecord;
		struPlayInfo.byProtoType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].nPreviewProtocolType;
        struPlayInfo.byVideoCodingType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].nVideoCodingType;
		if (g_bStandardCB) //call back standard stream or not
		{

			m_lPlayHandle = NET_DVR_RealPlay_V40(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfo, NULL, &m_iSubWndIndex);
			if (m_lPlayHandle >= 0)
			{
				if (!NET_DVR_SetStandardDataCallBack(m_lPlayHandle, g_fStdDataCallBack, m_iSubWndIndex))
				{
					g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetStandardDataCallBack %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
				}
			}
		}
		else
		{
			m_lPlayHandle = NET_DVR_RealPlay_V40(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfo, g_RealDataCallBack_V30, &m_iSubWndIndex);
		}

	}

	
	if (m_lPlayHandle >= 0)
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V40 %s stream[%d] pro[%d]",\
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName, \
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwProtocol>>31 &0x1, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwProtocol&0xff);
       
        //if (NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawFunZoomInInside, NULL))
        //{
        //    g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RigisterDrawFun");
        //}
        //else
        //{
        //    g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun");
        //}
		if (g_bShareSound)
		{
			m_bPlaySound = TRUE;
		}

        //开启定时器，获取NPQ状态
        m_pNpqTimer = SetTimer(GET_NPQ_STATE_TIMER, 40, NULL);
		
		//if (!NET_DVR_MakeKeyFrame(g_struDeviceInfo[iDeviceIndex].lLoginID, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO))   
		NET_DVR_I_FRAME struIFrame;
		memset(&struIFrame, 0, sizeof(struIFrame));
		struIFrame.dwSize = sizeof(NET_DVR_I_FRAME);
        if (g_struDeviceInfo[iDeviceIndex].byMirrorChanNum > 0 && iChanIndex >= MIRROR_CHAN_INDEX)
		{
            struIFrame.dwChan = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].iChannelNO;
		}
		else
		{
			struIFrame.dwChan = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
		}
		struIFrame.byStreamType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwStreamType;
		if(!NET_DVR_RemoteControl(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_MAKE_I_FRAME, &struIFrame, sizeof(struIFrame)))
		{
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MAKE_I_FRAME %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
		}

		g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(FALSE);

		m_hChanItem = hChanItem;
		memcpy(&m_struChanInfo, pChanInfo, sizeof(CHANNEL_INFO));
		g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].lRealHandle = m_lPlayHandle;
		
		::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iChanIndex));		
		//if auto record, record at once
		if (g_struLocalParam.bAutoRecord)
		{
			g_pMainDlg->OnTimer(AUTORECORD_TIMER);
		}
		DrawOutputBorder();
	}
	else
	{
 		g_pMainDlg->AddLog(pChanInfo->iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V40 chanindex[%d] stream[%d] pro[%d]", \
 			iChanIndex, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwStreamType, g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].dwLinkMode);

		int iErr = NET_DVR_GetLastError();
		TRACE("err = %d\n", iErr);
		if (iErr == NET_DVR_CHANNEL_ERROR && !g_bPlayAllDevice)
		{
			g_pMainDlg->DoGetDeviceResoureCfg(pChanInfo->iDeviceIndex);
			g_pMainDlg->RedrawDeviceNode(pChanInfo->iDeviceIndex);
		}
		
	}

	return m_lPlayHandle;
}

/*********************************************************
  Function:	ZeroStartPlay
  Desc:		begin to preview and decode by RealPlay interface
  Input:	pChanInfo：the information of the channel;
			hChanItem：point to the channel item information;
  Output:	none
  Return:	the play handle
**********************************************************/
LONG CDlgOutput::ZeroStartPlay(PCHANNEL_INFO pChanInfo, HTREEITEM hChanItem)
{
    if (g_bInSide)
    {
        return ZeroStartPlayInsideDecode(pChanInfo, hChanItem);
    }

    int iDeviceIndex = pChanInfo->iDeviceIndex;
    int iChanIndex   = pChanInfo->iChanIndex - ZERO_CHAN_INDEX;
    CString csLog = _T("");
    StopPlay();
    if (g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].lRealHandle < 0)
    {
        NET_DVR_CLIENTINFO struPlayInfo = {0};
        struPlayInfo.hPlayWnd = NULL;	
        struPlayInfo.lChannel = iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
        struPlayInfo.lLinkMode = g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].dwProtocol;
//        struPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;
		struPlayInfo.byProtoType = g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].nPreviewProtocolType;
        if (g_bStandardCB) //call back standard stream or not
        {
            m_lPlayHandle = NET_DVR_ZeroStartPlay(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfo, NULL, &m_iSubWndIndex, g_struLocalParam.bPreviewBlock);
            if (m_lPlayHandle >= 0)
            {
                if (!NET_DVR_SetStandardDataCallBack(m_lPlayHandle, g_fStdDataCallBack, m_iSubWndIndex))
                {
                    g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetStandardDataCallBack %s", g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].chChanName);
                }
            }
        }
        else
        {
            m_lPlayHandle = NET_DVR_ZeroStartPlay(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfo, g_RealDataCallBack_V30, &m_iSubWndIndex, g_struLocalParam.bPreviewBlock);
        }	
    }
    
    if (m_lPlayHandle >= 0)
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V40 %s stream[%d] pro[%d]",\
            g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].chChanName, \
            g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].dwProtocol>>31 &0x1, g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].dwProtocol&0xff);
        if (g_bShareSound)
        {
            m_bPlaySound = TRUE;
        }
        
        if (!NET_DVR_ZeroMakeKeyFrame(g_struDeviceInfo[iDeviceIndex].lLoginID, iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan))   
        {
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MakeKeyFrame %s", g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].chChanName);
        }
        
        g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(FALSE);
        
        m_hChanItem = hChanItem;
        memcpy(&m_struChanInfo, pChanInfo, sizeof(CHANNEL_INFO));
        g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].lRealHandle = m_lPlayHandle;
        
        ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(pChanInfo->iChanIndex));		
        //if auto record, record at once
        if (g_struLocalParam.bAutoRecord)
        {
            g_pMainDlg->OnTimer(AUTORECORD_TIMER);
        }
        DrawOutputBorder();
    }
    else
    {
        g_pMainDlg->AddLog(pChanInfo->iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ZeroStartPlay chanindex[%d] stream[%d] pro[%d]", \
            iChanIndex, g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].dwProtocol>>31 &0x1, g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].dwProtocol&0xff);
        
        int iErr = NET_DVR_GetLastError();
        TRACE("err = %d\n", iErr);
        if (iErr == NET_DVR_CHANNEL_ERROR && !g_bPlayAllDevice)
        {
            g_pMainDlg->DoGetDeviceResoureCfg(pChanInfo->iDeviceIndex);
            g_pMainDlg->RedrawDeviceNode(pChanInfo->iDeviceIndex);
        }
        
    }
    
    return m_lPlayHandle;


}

LONG CDlgOutput::ZeroStartPlayInsideDecode(PCHANNEL_INFO pChanInfo, HTREEITEM hChanItem)
{
	int iDeviceIndex = pChanInfo->iDeviceIndex;
	int iChanIndex   = pChanInfo->iChanIndex - ZERO_CHAN_INDEX;
	CString csLog = _T("");
	StopPlay();
	if (iChanIndex  < 0)
	{
		return -1;
	}
	if (g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].lRealHandle < 0)
	{
		if (g_struLocalParam.bUseCard && g_bCardInit)
		{
			AfxMessageBox("no support hard zero channel");
			return -1;
			NET_DVR_CARDINFO struCardPlayInfo = {0};
			struCardPlayInfo.struDisplayPara.nLeft = m_struCardPlayParam.nLeft;
			struCardPlayInfo.struDisplayPara.nTop = m_struCardPlayParam.nTop;
			struCardPlayInfo.struDisplayPara.nWidth = m_struCardPlayParam.nWidth;
			struCardPlayInfo.struDisplayPara.nHeight = m_struCardPlayParam.nHeight;
			struCardPlayInfo.struDisplayPara.bToScreen = 1;
			struCardPlayInfo.struDisplayPara.bToVideoOut = 1;

            struCardPlayInfo.lChannel = g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
            struCardPlayInfo.lLinkMode = g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].dwProtocol;
//			struCardPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;// require pointer assignment
			//start card decode
			m_lPlayHandle = NET_DVR_RealPlay_Card(g_struDeviceInfo[iDeviceIndex].lLoginID, &struCardPlayInfo, m_iSubWndIndex);
		}
		else
		{
			NET_DVR_CLIENTINFO struPlayInfo = {0};
			struPlayInfo.hPlayWnd = GetSafeHwnd();
			
			struPlayInfo.lChannel = iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;  // 增加起始通道号，零通道从1开始
            struPlayInfo.lLinkMode = g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].dwProtocol;
//			struPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;
			struPlayInfo.byProtoType = g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].nPreviewProtocolType;
			//start soft decode
			m_lPlayHandle = NET_DVR_ZeroStartPlay(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfo, NULL, &m_iNetDelayBufNum, 0/*g_struLocalParam.bPreviewBlock*/);
            if (m_lPlayHandle >= 0)
            {
                g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_ZeroStartPlay Channel[%d]", struPlayInfo.lChannel);
            }
            else
            {
                g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ZeroStartPlay Channel[%d]", struPlayInfo.lChannel);
            }
		}
	}
	if (m_lPlayHandle >= 0)
	{
		if (g_bShareSound)
		{
			m_bPlaySound = TRUE;
		}
		
		if (!NET_DVR_ZeroMakeKeyFrame(g_struDeviceInfo[iDeviceIndex].lLoginID, iChanIndex))    //重置I帧
		{
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ZeroMakeKeyFrame %s", g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].chChanName);
		}	

		g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(FALSE);

		m_hChanItem = hChanItem;
		memcpy(&m_struChanInfo, pChanInfo, sizeof(CHANNEL_INFO));
		g_struDeviceInfo[pChanInfo->iDeviceIndex].struZeroChan[iChanIndex].lRealHandle = m_lPlayHandle;
			//set channel node icon of device tree in main interface
		
		::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(pChanInfo->iChanIndex));		
		ChangeCurWinCfg();
		//if auto record, call record interface at once
		if (g_struLocalParam.bAutoRecord)
		{
			g_pMainDlg->OnTimer(AUTORECORD_TIMER);
		}
	}
	else
	{
 		g_pMainDlg->AddLog(pChanInfo->iDeviceIndex, OPERATION_FAIL_T, "Zero play");

		int iErr = NET_DVR_GetLastError();
		TRACE("err = %d\n", iErr);
		if (iErr == NET_DVR_CHANNEL_ERROR && !g_bPlayAllDevice)
		{//should do this
			g_pMainDlg->DoGetDeviceResoureCfg(pChanInfo->iDeviceIndex);
			g_pMainDlg->RedrawDeviceNode(pChanInfo->iDeviceIndex);
		}	
	}

	return m_lPlayHandle;
}

/*************************************************
Function:	 ZeroStopPlay	
Description: stop prewiew
Input:		 none
Output:      none
Return:		 TRUE succeed；FALSE failed
*************************************************/
BOOL CDlgOutput::ZeroStopPlay(void)
{
	StopProc DLINK_HW_Stop;
	CloseStreamProc DLINK_HW_CloseStream;
	int iDeviceIndex = m_struChanInfo.iDeviceIndex;
	int iChanIndex   = m_struChanInfo.iChanIndex - ZERO_CHAN_INDEX;
	int iRet = 0;

	if (iDeviceIndex < 0)
	{
		return FALSE;
	}

	if (iChanIndex < 0)
	{
		return FALSE;
	}

	CString strTemp =_T("");
	if (m_lPlayHandle < 0)
	{
		return TRUE;
	}
	
	StopSound();
	
	if (g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].lRealHandle >= 0)
	{
		if (!NET_DVR_ZeroStopPlay(m_lPlayHandle))
		{
			AddLog(OPERATION_FAIL_T, "NET_DVR_ZeroStopPlay");
		}
		else
		{
			AddLog(OPERATION_SUCC_T, "NET_DVR_ZeroStopPlay");
		}		
	}

	//decode, need to call decoding library to stop decode
	if (!g_struLocalParam.bNoDecode && !g_bInSide)
	{
		if (!g_struLocalParam.bUseCard)
		{
			if (m_lPort >= 0)
			{
				if (!PlayM4_Stop(m_lPort))
				{
					AddLog(PLAY_FAIL_T, "PlayM4_Stop err[%d]", PlayM4_GetLastError(m_lPort));
				}
				else
				{
					AddLog(PLAY_SUCC_T, "PlayM4_Stop");
				}
				if (!PlayM4_CloseStream(m_lPort))
				{
					AddLog(PLAY_FAIL_T, "PlayM4_CloseStream err[%d]", PlayM4_GetLastError(m_lPort));
				}
				else
				{
					AddLog(PLAY_SUCC_T, "PlayM4_CloseStream");
				}
				if (!PlayM4_FreePort(m_lPort))
				{
					AddLog(PLAY_FAIL_T, "PlayM4_FreePort err[%d]", PlayM4_GetLastError(m_lPort));
				}
				else
				{
					AddLog(PLAY_SUCC_T, "PlayM4_FreePort");
				}
				
				m_lPort = -1;
			}
		}
		else
		{
			if (m_hCardHandle != INVALID_HANDLE_VALUE)
			{
				DLINK_HW_Stop = (StopProc)GetProcAddress(g_hDSSDK, "HW_Stop");
				iRet = DLINK_HW_Stop(m_hCardHandle);
				if (iRet != 0 )
				{
					AddLog(PLAY_FAIL_T, "HW_Stop err[%d]", iRet);
				}
				DLINK_HW_CloseStream = (CloseStreamProc)GetProcAddress(g_hDSSDK, "HW_CloseStream");
				iRet = DLINK_HW_CloseStream(m_hCardHandle);
				if (iRet != 0 )
				{
					AddLog(PLAY_FAIL_T, "HW_CloseStream err[%d]", iRet);
				}
				
				m_hCardHandle = INVALID_HANDLE_VALUE;
			}
		}		
	}
	
	g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex].lRealHandle = -1;
	g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(TRUE);

	DrawOutputBorder();
	//set channel node icon of device tree in main interface
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(m_struChanInfo.iChanIndex));		

	m_hChanItem = NULL;
	CHANNEL_INFO tmpChanInfo;
	memcpy(&m_struChanInfo, &tmpChanInfo, sizeof(CHANNEL_INFO));
	m_lPlayHandle = -1;
	Invalidate(TRUE);

	return TRUE;
}

/*********************************************************
  Function:	ZeroStartPlay
  Desc:		begin to preview and decode by RealPlay interface
  Input:	pChanInfo：the information of the channel;
			hChanItem：point to the channel item information;
  Output:	none
  Return:	the play handle
**********************************************************/
LONG CDlgOutput::MirrorStartPlay(PCHANNEL_INFO pChanInfo, HTREEITEM hChanItem)
{
    if (g_bInSide)
    {
        return MirrorStartPlayInsideDecode(pChanInfo, hChanItem);
    }

    int iDeviceIndex = pChanInfo->iDeviceIndex;
    int iChanIndex   = pChanInfo->iChanIndex;
    CString csLog = _T("");
    StopPlay();
    if (g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].lRealHandle < 0)
    {
        NET_DVR_PREVIEWINFO struPlayInfo = {0};
        struPlayInfo.hPlayWnd = NULL;	
        struPlayInfo.lChannel = m_lChannel;//iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
        struPlayInfo.dwLinkMode = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwLinkMode;
        struPlayInfo.dwStreamType = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwStreamType;
        //	struPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;
        struPlayInfo.byPreviewMode = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwPreviewMode;
        struPlayInfo.bBlocked = g_struLocalParam.bPreviewBlock;
        struPlayInfo.bPassbackRecord = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].bPassbackRecord;
        struPlayInfo.byProtoType = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].nPreviewProtocolType;
        if (g_bStandardCB) //call back standard stream or not
        {
            
            m_lPlayHandle = NET_DVR_RealPlay_V40(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfo, NULL, &m_iSubWndIndex);
            if (m_lPlayHandle >= 0)
            {
                if (!NET_DVR_SetStandardDataCallBack(m_lPlayHandle, g_fStdDataCallBack, m_iSubWndIndex))
                {
                    g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetStandardDataCallBack %s", g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].chChanName);
                }
            }
        }
        else
        {
            m_lPlayHandle = NET_DVR_RealPlay_V40(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfo, g_RealDataCallBack_V30, &m_iSubWndIndex);
        }
        
    }
    
    
    if (m_lPlayHandle >= 0)
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V40 %s stream[%d] pro[%d]",\
            g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].chChanName, \
            g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwProtocol>>31 &0x1, g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwProtocol&0xff);
        
        if (NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawFunZoomInInside, NULL))
        {
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RigisterDrawFun");
        }
        else
        {
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun");
        }
        if (g_bShareSound)
        {
            m_bPlaySound = TRUE;
        }
        
        //if (!NET_DVR_MakeKeyFrame(g_struDeviceInfo[iDeviceIndex].lLoginID, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO))   
        NET_DVR_I_FRAME struIFrame;
        memset(&struIFrame, 0, sizeof(struIFrame));
        struIFrame.dwSize = sizeof(NET_DVR_I_FRAME);

        struIFrame.dwChan = m_lChannel;        
        struIFrame.byStreamType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwStreamType;

        if(!NET_DVR_RemoteControl(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_MAKE_I_FRAME, &struIFrame, sizeof(struIFrame)))
        {
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MAKE_I_FRAME %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
        }
        
        g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(FALSE);
        
        m_hChanItem = hChanItem;
        memcpy(&m_struChanInfo, pChanInfo, sizeof(CHANNEL_INFO));
        g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].lRealHandle = m_lPlayHandle;
        
        ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iChanIndex));		
        //if auto record, record at once
        if (g_struLocalParam.bAutoRecord)
        {
            g_pMainDlg->OnTimer(AUTORECORD_TIMER);
        }
        DrawOutputBorder();
    }
    else
    {
        g_pMainDlg->AddLog(pChanInfo->iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V40 chanindex[%d] stream[%d] pro[%d]", \
            iChanIndex, g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwStreamType, g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwLinkMode);
        
        int iErr = NET_DVR_GetLastError();
        TRACE("err = %d\n", iErr);
        if (iErr == NET_DVR_CHANNEL_ERROR && !g_bPlayAllDevice)
        {
            g_pMainDlg->DoGetDeviceResoureCfg(pChanInfo->iDeviceIndex);
            g_pMainDlg->RedrawDeviceNode(pChanInfo->iDeviceIndex);
        }
        
    }
    
	return m_lPlayHandle;

}

LONG CDlgOutput::MirrorStartPlayInsideDecode(PCHANNEL_INFO pChanInfo, HTREEITEM hChanItem)
{
	int iDeviceIndex = pChanInfo->iDeviceIndex;
	int iChanIndex   = pChanInfo->iChanIndex;
    
	CString csLog = _T("");
	StopPlay();
	if (g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].lRealHandle < 0)
	{
		if (g_struLocalParam.bUseCard && g_bCardInit)
		{		
			NET_DVR_CARDINFO struCardPlayInfo = {0};
			struCardPlayInfo.struDisplayPara.nLeft = m_struCardPlayParam.nLeft;
			struCardPlayInfo.struDisplayPara.nTop = m_struCardPlayParam.nTop;
			struCardPlayInfo.struDisplayPara.nWidth = m_struCardPlayParam.nWidth;
			struCardPlayInfo.struDisplayPara.nHeight = m_struCardPlayParam.nHeight;
			struCardPlayInfo.struDisplayPara.bToScreen = 1;
			struCardPlayInfo.struDisplayPara.bToVideoOut = 1;

		//	struCardPlayInfo.lChannel = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
			struCardPlayInfo.lChannel = m_lChannel;
			struCardPlayInfo.lLinkMode = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwProtocol;
//			struCardPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;// require pointer assignment
			//start card decode
			m_lPlayHandle = NET_DVR_RealPlay_Card(g_struDeviceInfo[iDeviceIndex].lLoginID, &struCardPlayInfo, m_iSubWndIndex);
		}
		else
		{
			NET_DVR_PREVIEWINFO struPlayInfo = {0};

			if (g_struLocalParam.bNoDecode)
			{
				struPlayInfo.hPlayWnd = NULL;
			}
			else
			{
				struPlayInfo.hPlayWnd = GetSafeHwnd();
			}
			
			struPlayInfo.lChannel = pChanInfo->iChannelNO;
//			struPlayInfo.sMultiCastIP = g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP;
			struPlayInfo.dwLinkMode = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwLinkMode;
			struPlayInfo.dwStreamType = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwStreamType;

			//start soft decode
			struPlayInfo.byPreviewMode = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwPreviewMode;
			struPlayInfo.bBlocked = g_struLocalParam.bPreviewBlock;
			struPlayInfo.bPassbackRecord = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].bPassbackRecord;
			struPlayInfo.byProtoType = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].nPreviewProtocolType;
            struPlayInfo.dwDisplayBufNum = m_iNetDelayBufNum;
			m_lPlayHandle = NET_DVR_RealPlay_V40(g_struDeviceInfo[iDeviceIndex].lLoginID, &struPlayInfo, NULL, &m_iNetDelayBufNum);
		}
	}

	if (m_lPlayHandle >= 0)
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V40 %s stream[%d] pro[%d]",\
			g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].chChanName, \
			g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwProtocol>>31 &0x1, g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwProtocol&0xff);
        if (NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawFunZoomInInside, NULL))
        {
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RigisterDrawFun");
        }
        else
        {
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun");
        }

		if (g_bShareSound)
		{
			m_bPlaySound = TRUE;
		}
		
	//	if (!NET_DVR_MakeKeyFrame(g_struDeviceInfo[iDeviceIndex].lLoginID,  g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO))    //重置I帧
		NET_DVR_I_FRAME struIFrame;
		memset(&struIFrame, 0, sizeof(struIFrame));
		struIFrame.dwSize = sizeof(NET_DVR_I_FRAME);
        struIFrame.dwChan = pChanInfo->iChannelNO;
		
		struIFrame.byStreamType = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwStreamType;
		if(!NET_DVR_RemoteControl(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_MAKE_I_FRAME, &struIFrame, sizeof(struIFrame)))
		{
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MAKE_I_FRAME %s", g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].chChanName);
		}	
		//set player buffer
//  		if (!NET_DVR_SetPlayerBufNumber(m_lPlayHandle,m_iNetDelayBufNum))
//  		{
// 			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetPlayerBufNumber[%d] %s",m_iNetDelayBufNum, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
//  		}

		if (g_struLocalParam.dwBFrameNum > 0)
		{
 			if (!NET_DVR_ThrowBFrame(m_lPlayHandle, g_struLocalParam.dwBFrameNum))
 			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ThrowBFrame[%d] %s",g_struLocalParam.dwBFrameNum, g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].chChanName);
 			}
		}


		g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(FALSE);

		m_hChanItem = hChanItem;
		memcpy(&m_struChanInfo, pChanInfo, sizeof(CHANNEL_INFO));
		g_struDeviceInfo[pChanInfo->iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].lRealHandle = m_lPlayHandle;
			//set channel node icon of device tree in main interface
		
		::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iChanIndex));		
		ChangeCurWinCfg();
		//if auto record, call record interface at once
		if (g_struLocalParam.bAutoRecord)
		{
			g_pMainDlg->OnTimer(AUTORECORD_TIMER);
		}
	}
	else
	{
 		g_pMainDlg->AddLog(pChanInfo->iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V40 chanindex[%d] stream[%d] pro[%d]", \
 			iChanIndex, g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwProtocol>>31 &0x1, g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwProtocol&0xff);

		int iErr = NET_DVR_GetLastError();
		TRACE("err = %d\n", iErr);
		if (iErr == NET_DVR_CHANNEL_ERROR && !g_bPlayAllDevice)
		{//should do this
			g_pMainDlg->DoGetDeviceResoureCfg(pChanInfo->iDeviceIndex);
			g_pMainDlg->RedrawDeviceNode(pChanInfo->iDeviceIndex);
		}	
	}

	return m_lPlayHandle;
}

/*************************************************
Function:	 ZeroStopPlay	
Description: stop prewiew
Input:		 none
Output:      none
Return:		 TRUE succeed；FALSE failed
*************************************************/
BOOL CDlgOutput::MirrorStopPlay(void)
{
	StopProc DLINK_HW_Stop;
	CloseStreamProc DLINK_HW_CloseStream;
	int iDeviceIndex = m_struChanInfo.iDeviceIndex;
	int iChanIndex   = m_struChanInfo.iChanIndex;
	int iRet = 0;

	if (iDeviceIndex < 0)
	{
		return FALSE;
	}

	if (iChanIndex < 0)
	{
		return FALSE;
	}

	CString strTemp =_T("");
	if (m_lPlayHandle < 0)
	{
		return TRUE;
	}

	StopSound();
	
	if (m_bLocalManualRec)
	{
		StopLocalRecord();
	}

	if (m_lPlayHandle >= 0)
	{
		if (!NET_DVR_StopRealPlay(m_lPlayHandle))
		{
			AddLog(OPERATION_FAIL_T, "NET_DVR_StopRealPlay");
		}
		else
		{
			AddLog(OPERATION_SUCC_T, "NET_DVR_StopRealPlay");
		}		
	}

	//decode, need to call decoding library to stop decode
	if (!g_struLocalParam.bNoDecode && !g_bInSide)
	{
		if (!g_struLocalParam.bUseCard)
		{
			if (m_lPort >= 0)
			{
				if (!PlayM4_Stop(m_lPort))
				{
					AddLog(PLAY_FAIL_T, "PlayM4_Stop err[%d]", PlayM4_GetLastError(m_lPort));
				}
				else
				{
					AddLog(PLAY_SUCC_T, "PlayM4_Stop");
				}
				if (!PlayM4_CloseStream(m_lPort))
				{
					AddLog(PLAY_FAIL_T, "PlayM4_CloseStream err[%d]", PlayM4_GetLastError(m_lPort));
				}
				else
				{
					AddLog(PLAY_SUCC_T, "PlayM4_CloseStream");
				}
				if (!PlayM4_FreePort(m_lPort))
				{
					AddLog(PLAY_FAIL_T, "PlayM4_FreePort err[%d]", PlayM4_GetLastError(m_lPort));
				}
				else
				{
					AddLog(PLAY_SUCC_T, "PlayM4_FreePort");
				}
				
				m_lPort = -1;
			}
		}
		else
		{
			if (m_hCardHandle != INVALID_HANDLE_VALUE)
			{
				DLINK_HW_Stop = (StopProc)GetProcAddress(g_hDSSDK, "HW_Stop");
				iRet = DLINK_HW_Stop(m_hCardHandle);
				if (iRet != 0 )
				{
					AddLog(PLAY_FAIL_T, "HW_Stop err[%d]", iRet);
				}
				DLINK_HW_CloseStream = (CloseStreamProc)GetProcAddress(g_hDSSDK, "HW_CloseStream");
				iRet = DLINK_HW_CloseStream(m_hCardHandle);
				if (iRet != 0 )
				{
					AddLog(PLAY_FAIL_T, "HW_CloseStream err[%d]", iRet);
				}
		
				m_hCardHandle = INVALID_HANDLE_VALUE;
			}
		}
	}
	
	if (iChanIndex >= ZERO_CHAN_INDEX)
	{
		g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex-ZERO_CHAN_INDEX].lRealHandle = -1;
	}
    else if (iChanIndex >= MIRROR_CHAN_INDEX)
    {
        g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].lRealHandle = -1;
    }
	else
	{
		g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].lRealHandle = -1;
	}
	
	g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(TRUE);

	DrawOutputBorder();
	//set channel node icon of device tree in main interface
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iChanIndex));		

	m_hChanItem = NULL;
	CHANNEL_INFO tmpChanInfo;
	memcpy(&m_struChanInfo, &tmpChanInfo, sizeof(CHANNEL_INFO));
	m_lPlayHandle = -1;
	Invalidate(TRUE);

	return TRUE;
}

/*************************************************
Function:	 StopPlay	
Description: stop prewiew
Input:		 none
Output:      none
Return:		 TRUE succeed；FALSE failed
*************************************************/
BOOL CDlgOutput::StopPlay(void)
{
	StopProc DLINK_HW_Stop;
	CloseStreamProc DLINK_HW_CloseStream;
	int iDeviceIndex = m_struChanInfo.iDeviceIndex;
	int iChanIndex   = m_struChanInfo.iChanIndex;
	int iRet = 0;

    if (m_pNpqTimer)
    {
        KillTimer(GET_NPQ_STATE_TIMER);
        m_pNpqTimer = NULL;
    }

	if (iDeviceIndex < 0)
	{
		return FALSE;
	}

	if (iChanIndex < 0)
	{
		return FALSE;
	}

	CString strTemp =_T("");
	if (m_lPlayHandle < 0)
	{
		return TRUE;
	}

	StopSound();
	
	if (m_bLocalManualRec)
	{
		StopLocalRecord();
	}

	if (m_lPlayHandle >= 0)
	{
		if (!NET_DVR_StopRealPlay(m_lPlayHandle))
		{
			AddLog(OPERATION_FAIL_T, "NET_DVR_StopRealPlay");
		}
		else
		{
			AddLog(OPERATION_SUCC_T, "NET_DVR_StopRealPlay");
		}		
	}

	//decode, need to call decoding library to stop decode
	if (!g_struLocalParam.bNoDecode && !g_bInSide)
	{
		if (!g_struLocalParam.bUseCard)
		{
			if (m_lPort >= 0)
			{
				if (!PlayM4_Stop(m_lPort))
				{
					AddLog(PLAY_FAIL_T, "PlayM4_Stop err[%d]", PlayM4_GetLastError(m_lPort));
				}
				else
				{
					AddLog(PLAY_SUCC_T, "PlayM4_Stop");
				}
				if (!PlayM4_CloseStream(m_lPort))
				{
					AddLog(PLAY_FAIL_T, "PlayM4_CloseStream err[%d]", PlayM4_GetLastError(m_lPort));
				}
				else
				{
					AddLog(PLAY_SUCC_T, "PlayM4_CloseStream");
				}
				if (!PlayM4_FreePort(m_lPort))
				{
					AddLog(PLAY_FAIL_T, "PlayM4_FreePort err[%d]", PlayM4_GetLastError(m_lPort));
				}
				else
				{
					AddLog(PLAY_SUCC_T, "PlayM4_FreePort");
				}
				
				m_lPort = -1;
			}
		}
		else
		{
			if (m_hCardHandle != INVALID_HANDLE_VALUE)
			{
				DLINK_HW_Stop = (StopProc)GetProcAddress(g_hDSSDK, "HW_Stop");
				iRet = DLINK_HW_Stop(m_hCardHandle);
				if (iRet != 0 )
				{
					AddLog(PLAY_FAIL_T, "HW_Stop err[%d]", iRet);
				}
				DLINK_HW_CloseStream = (CloseStreamProc)GetProcAddress(g_hDSSDK, "HW_CloseStream");
				iRet = DLINK_HW_CloseStream(m_hCardHandle);
				if (iRet != 0 )
				{
					AddLog(PLAY_FAIL_T, "HW_CloseStream err[%d]", iRet);
				}
		
				m_hCardHandle = INVALID_HANDLE_VALUE;
			}
		}
	}
	
	if (iChanIndex >= ZERO_CHAN_INDEX)
	{
		g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex-ZERO_CHAN_INDEX].lRealHandle = -1;
	}
    else if (iChanIndex >= MIRROR_CHAN_INDEX)
    {
        g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].lRealHandle = -1;
    }
	else
	{
		g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].lRealHandle = -1;
	}
	
	g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(TRUE);

	DrawOutputBorder();
	//set channel node icon of device tree in main interface
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iChanIndex));		

	m_hChanItem = NULL;
	CHANNEL_INFO tmpChanInfo;
	memcpy(&m_struChanInfo, &tmpChanInfo, sizeof(CHANNEL_INFO));
	m_lPlayHandle = -1;
	Invalidate(TRUE);

	return TRUE;
}

/*********************************************************
  Function:	OnRButtonDown
  Desc:		right click window with attached menu, including image dealing operation
  Input:    nFlags,the flag message of mouse;
			point, the position of the mouse click;			
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::OnRButtonDown(UINT nFlags, CPoint point)
{
	//switch of parameters while selecting window
	ChangeCurWinCfg();
	
	if (g_struLocalParam.bMultiScreen||g_struLocalParam.bFullScreen)
	{
		return;
	}

	CMenu pMenu;

	if (!pMenu.LoadMenu(IDR_MENU_MYOUTPUT))
	{
		return;
	}

	pMenu.GetSubMenu(0)->EnableMenuItem(0, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
	pMenu.GetSubMenu(0)->EnableMenuItem(1, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
	pMenu.GetSubMenu(0)->EnableMenuItem(2, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
	pMenu.GetSubMenu(0)->EnableMenuItem(3, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);//sporater is a sub node
	pMenu.GetSubMenu(0)->EnableMenuItem(4, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
	pMenu.GetSubMenu(0)->EnableMenuItem(5, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
	pMenu.GetSubMenu(0)->EnableMenuItem(6, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
    pMenu.GetSubMenu(0)->EnableMenuItem(7, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
    pMenu.GetSubMenu(0)->EnableMenuItem(8, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
    pMenu.GetSubMenu(0)->EnableMenuItem(9, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);

	char szLan[128] = {0};
	if (g_bPlayAllDevice)
	{
		if (g_struLocalParam.bCycling)
		{
			pMenu.GetSubMenu(0)->EnableMenuItem(0, MF_BYPOSITION | MF_ENABLED);
			if (g_struLocalParam.bPaused)
			{
				g_StringLanType(szLan, "开始循环", "Begin Cycle");
				pMenu.GetSubMenu(0)->ModifyMenu(0, MF_BYPOSITION, ID_MENU_PAUSE_CYCLE, szLan);
			}
			else
			{
				g_StringLanType(szLan, "暂停循环", "Pause Cycle");
				pMenu.GetSubMenu(0)->ModifyMenu(0, MF_BYPOSITION, ID_MENU_PAUSE_CYCLE, szLan);
			}
		}
		else
		{
			pMenu.GetSubMenu(0)->EnableMenuItem(0, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
		}
	
		if (g_struLocalParam.bNextPage)
		{
			pMenu.GetSubMenu(0)->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
		}
		else
		{
			pMenu.GetSubMenu(0)->EnableMenuItem(1, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
		}
		if (g_struLocalParam.bFrontPage)
		{		
			pMenu.GetSubMenu(0)->EnableMenuItem(2, MF_BYPOSITION | MF_ENABLED);
		}
		else
		{
			pMenu.GetSubMenu(0)->EnableMenuItem(2, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
		}
	}

	if (m_lPlayHandle >= 0)
	{
		if (m_bPlaySound)
		{
			g_StringLanType(szLan, "关闭声音", "Close Sound");
			pMenu.GetSubMenu(0)->ModifyMenu(4, MF_BYPOSITION, ID_MENU_SOUND, szLan);
		}
		else
		{
			g_StringLanType(szLan, "打开声音", "Open Sound");
			pMenu.GetSubMenu(0)->ModifyMenu(4, MF_BYPOSITION, ID_MENU_SOUND, szLan);
		}
	}

        CString struAlarmOutText = "";
    LONG lPlayerPort = -1;
    BOOL bRet = FALSE;
    if (m_lPlayHandle >= 0)
    {
        if (m_bShowOSD)
        {
            g_StringLanType(szLan,"关闭ATM信息", "Close OSD");
        }
        else
        {            
            g_StringLanType(szLan,"显示ATM信息", "Show OSD");            
        }
         pMenu.GetSubMenu(0)->ModifyMenu(9, MF_BYPOSITION, ID_MENU_SHOWOSD, szLan);
    }

    m_lDeviceType = g_struDeviceInfo[m_struChanInfo.iDeviceIndex].iDeviceType;
       
    pMenu.GetSubMenu(0)->EnableMenuItem(9, MF_BYPOSITION | MF_ENABLED);

	if (g_pMainDlg->IsPlaying())
	{
		pMenu.GetSubMenu(0)->EnableMenuItem(5, MF_BYPOSITION | MF_ENABLED);
	}

	if (m_lPlayHandle >= 0 && !g_bPlayAllDevice)
	{
		g_StringLanType(szLan, "关闭预览", "Stop Preview");
		pMenu.GetSubMenu(0)->ModifyMenu(6, MF_BYPOSITION, ID_MENU_STOP_PLAY, szLan);
	}

    if (m_struChanInfo.iChanIndex >= ZERO_CHAN_INDEX && m_lPlayHandle >= 0) //Zero chan preview 
    {
        pMenu.GetSubMenu(0)->EnableMenuItem(7, MF_BYPOSITION | MF_ENABLED);
        pMenu.GetSubMenu(0)->EnableMenuItem(8, MF_BYPOSITION | MF_ENABLED);
    }
    else
    {
        pMenu.GetSubMenu(0)->EnableMenuItem(7, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
        pMenu.GetSubMenu(0)->EnableMenuItem(8, MF_BYPOSITION|MF_DISABLED|MF_GRAYED);
    }

	ClientToScreen(&point);
	pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);	
	CDialog::OnRButtonDown(nFlags, point);
    UpdateData(FALSE);
}

/*********************************************************
  Function:	PreTranslateMessage
  Desc:		mouse drag dealing
  Input:    pMsg, point to the message of the mouse	
  Output:	none
  Return:	TRUE, means successful; FALSE, means failed;
**********************************************************/
BOOL CDlgOutput::PreTranslateMessage(MSG* pMsg)
{
	CPoint pt(0,0);
	GetCursorPos(&pt);
	ScreenToClient(&pt);

	GetWindowRect(&m_OutputRect);
	ScreenToClient(&m_OutputRect);

	switch (pMsg->message)
	{
	case WM_MOUSEMOVE:	
		if (!g_pMainDlg->m_bDrag)
		{
			break;
		}

		break;
	case WM_LBUTTONUP:
		if (!g_pMainDlg->m_bDrag|| !m_OutputRect.PtInRect(pt))
		{
			return FALSE;
		}

		g_pMainDlg->m_bDrag = FALSE;
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		break;
	default:
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

/*********************************************************
  Function:	OnLButtonDblClk
  Desc:		double click to zoom or retore related window
  Input:    nFlags,the flag message of mouse;
			point, the position of the mouse click;		
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	ChangeCurWinCfg();
	//can be enlarged when play
	if (m_lPlayHandle < 0 && !g_struLocalParam.bEnlarged && !g_struLocalParam.bMultiScreen)
	{
		return;
	}

	//return to original preview when muti-screen or full screen
	if (g_struLocalParam.bMultiScreen || g_struLocalParam.bFullScreen)
	{
		g_struLocalParam.bEnlarged    = FALSE;
		g_struLocalParam.bMultiScreen = FALSE;
		g_struLocalParam.bFullScreen  = FALSE;
		g_pMainDlg->GetDlgItem(IDC_COMBO_WNDNUM)->EnableWindow(TRUE);
		g_pMainDlg->FullScreen(g_struLocalParam.bFullScreen);
		if (g_struLocalParam.bFullScreen)
		{
			g_pMainDlg->ArrangeOutputs(g_pMainDlg->m_iCurWndNum);
		}
		else//muti-screen
		{
			g_pMainDlg->ArrangeOutputs(g_pMainDlg->m_iCurWndNum);

			g_pMainDlg->GetDlgItem(IDC_STATIC_PREVIEWBG)->Invalidate(TRUE);
		}
		return;
	}
	g_pMainDlg->GetDlgItem(IDC_COMBO_WNDNUM)->EnableWindow(FALSE);
	
	if (g_struLocalParam.bEnlarged || 1 == g_pMainDlg->m_iCurWndNum)
	{
		g_struLocalParam.bFullScreen = TRUE;

		//brush chosen line
		g_pMainDlg->GetDlgItem(IDC_STATIC_PREVIEWBG)->Invalidate(TRUE);
		g_pMainDlg->FullScreen(g_struLocalParam.bFullScreen);
	}
	else
	{//single pic enlarge
		g_struLocalParam.bEnlarged = TRUE;
		g_pMainDlg->ArrangeOutputs(1);
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}

/*********************************************************
  Function:	OnDestroy
  Desc:		release output dialog resource when exit
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgOutput::OnDestroy()
{
	CDialog::OnDestroy();
}

/*********************************************************
  Function:	StopSound
  Desc:		stop sound playing
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::StopSound()
{
	SetAudioPreviewProc DLINK_HW_SetAudioPreview;
	int iRet = -1;
	if (g_struLocalParam.bUseCard && g_bCardInit)
	{
		if (m_bPlaySound && m_hCardHandle >= 0)
		{
			DLINK_HW_SetAudioPreview = (SetAudioPreviewProc)GetProcAddress(g_hDSSDK, "HW_SetAudioPreview");
			iRet = DLINK_HW_SetAudioPreview(m_hCardHandle, FALSE);
			if (iRet != 0)
			{
				AddLog(PLAY_FAIL_T, "HW_SetAudioPreview err[%x]", iRet);	
				return;
			}
		}
		else if (m_lPlayHandle >= 0)
		{
			if (!NET_DVR_CloseSound_Card(m_lPlayHandle))
			{
				AddLog(OPERATION_FAIL_T, "NET_DVR_CloseSound_Card");
				return;
			}	
		}
	}
	else if(!g_struLocalParam.bNoDecode)
	{
		if (!g_bInSide && m_lPort >= 0)
		{		
			if (!g_bShareSound && m_bPlaySound)
			{				
				if (!PlayM4_StopSound())
				{
					AddLog(PLAY_FAIL_T, "PlayM4_StopSound err[%d]", PlayM4_GetLastError(m_lPort));
					return;
				}	
			}
			if (m_bPlaySound)
			{	
				if (g_bShareSound)
				{
					if (!PlayM4_StopSoundShare(m_lPort))
					{
						AddLog(PLAY_FAIL_T, "PlayM4_StopSound err[%d]", PlayM4_GetLastError(m_lPort));
						return;
					}
				}
			}			
		}
		else
		{//
			if (!g_bShareSound)
			{
				if (!NET_DVR_CloseSound())
				{
					AddLog(OPERATION_FAIL_T, "NET_DVR_CloseSound");
					return;
				}				
			}
			if (m_bPlaySound)
			{
				m_bPlaySound = FALSE;
				if (g_bShareSound)
				{
					if (!NET_DVR_CloseSoundShare(m_lPlayHandle))
					{
						AddLog(OPERATION_FAIL_T, "NET_DVR_CloseSoundShare");
						return;
					}				
				}
			}
		}
	}
	AddLog(OPERATION_SUCC_T, "StopSound");
	m_bPlaySound = FALSE;
}

/*********************************************************
  Function:	StartSound
  Desc:		start to play sound
  Input:	wVolumeValue,the value of volume
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::StartSound(WORD wVolumeValue)
{
	SetAudioPreviewProc DLINK_HW_SetAudioPreview;
	SetVolumeProc DLINK_HW_SetVolume;
	SetDecoderAudioOutputProc DLINK_SetDecoderAudioOutput;
	int i = 0;
	int iRet = -1;
	if (g_struLocalParam.bUseCard && g_bCardInit)
	{
		if (!g_bInSide && m_hCardHandle != INVALID_HANDLE_VALUE)
		{
			DLINK_SetDecoderAudioOutput = (SetDecoderAudioOutputProc)GetProcAddress(g_hDSSDK, "SetDecoderAudioOutput");
			iRet = DLINK_SetDecoderAudioOutput((UINT)m_hCardHandle, TRUE, (UINT)m_hCardHandle/2);
			if (iRet != 0)
			{
				AddLog(PLAY_FAIL_T, "SetDecoderAudioOutput err[%d]", iRet);
				return;
			}
			DLINK_HW_SetAudioPreview = (SetAudioPreviewProc)GetProcAddress(g_hDSSDK, "HW_SetAudioPreview");
			iRet = DLINK_HW_SetAudioPreview(m_hCardHandle, TRUE);
			if (iRet != 0)
			{
				AddLog(PLAY_FAIL_T, "HW_SetAudioPreview err[%d]", iRet);
				return;
			}
			DLINK_HW_SetVolume = (SetVolumeProc)GetProcAddress(g_hDSSDK, "HW_SetVolume");
			iRet = DLINK_HW_SetVolume(m_hCardHandle, wVolumeValue);
			if (iRet != 0)
			{
				AddLog(PLAY_FAIL_T, "HW_SetVolume err[%d]", iRet);
				return;
			}
		}
		else
		{
			if (!NET_DVR_OpenSound_Card(m_lPlayHandle))
			{
				AddLog(OPERATION_FAIL_T, "NET_DVR_OpenSound_Card");
				return;
			}
			if (!NET_DVR_AudioPreview_Card(m_lPlayHandle, TRUE))
			{
				AddLog(OPERATION_FAIL_T, "NET_DVR_AudioPreview_Card");
				return;
			}
			if (!NET_DVR_SetVolume_Card(m_lPlayHandle, wVolumeValue))
			{
				AddLog(OPERATION_FAIL_T, "NET_DVR_SetVolume_Card");
				return;
			}
		}
	}
	else
	{
		if (!g_bInSide && m_lPort >= 0)
		{
			if (g_bShareSound)
			{
				if (!PlayM4_PlaySoundShare(m_lPort))
				{
					g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, PLAY_FAIL_T, "PlayM4_PlaySoundShare err[%d]", PlayM4_GetLastError(m_lPort));
					return;
				}
			}
			else
			{
				if (!PlayM4_PlaySound(m_lPort))
				{
					g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, PLAY_FAIL_T, "PlayM4_PlaySound err[%d]", PlayM4_GetLastError(m_lPort));
					return;
				}
			}
			if (!PlayM4_SetVolume(m_lPort, wVolumeValue))
			{
				g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, PLAY_FAIL_T, "PlayM4_SetVolume err[%d]", PlayM4_GetLastError(m_lPort));
			}
		}
		else if(!g_struLocalParam.bNoDecode)
		{
			if (g_bShareSound)
			{
				if (!NET_DVR_OpenSoundShare(m_lPlayHandle))
				{
					g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_OpenSoundShare");
					return;
				}
			}
			else
			{
				if (!NET_DVR_OpenSound(m_lPlayHandle))
				{
                    for (i = 0; i < MAX_OUTPUTS; i++)
                    {	//shut down other window's audio sign
                        if (i == (int)m_iSubWndIndex)
                        {
                            continue;
                        }
                        g_dlgOutput[i].m_bPlaySound = FALSE;
                    }
					g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_OpenSound");
					return;
				}
			}
			if (!NET_DVR_Volume(m_lPlayHandle, wVolumeValue))
			{
				g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_Volume");
			}
		}
	}
	AddLog(OPERATION_SUCC_T, "StartSound");
	m_bPlaySound = TRUE;
	if (!g_bShareSound)
	{
		for (i = 0; i < MAX_OUTPUTS; i++)
		{	//shut down other window's audio sign
			if (i == (int)m_iSubWndIndex)
			{
				continue;
			}
			g_dlgOutput[i].m_bPlaySound = FALSE;
		}	
	}	
}

/*********************************************************
  Function:	OnMenuSound
  Desc:		start sound play or stop
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::OnMenuSound()
{
	int i = 0;
	WORD	wTemp = 0;
	WORD	wVolumevalue = 0;

	wTemp = (0xFFFF) / 100;
	wVolumevalue = (WORD)(50 * wTemp);
	if (m_bPlaySound)
	{
		StopSound();
	}
	else// if (g_bShareSound)
	{
		StartSound(wVolumevalue);
	}
		
}

/*********************************************************
  Function:	OnMenuNextPage
  Desc:		preview next channel while play all
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutput::OnMenuNextPage()
{
	g_pMainDlg->PlayNextPage();
}

/*********************************************************
  Function:	OnMenuFrontPage
  Desc:		preview front page while all play or cycle play
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutput::OnMenuFrontPage()
{
	g_pMainDlg->PlayFrontPage();
}

/*********************************************************
  Function:	OnMenuPauseCycle
  Desc:		suspend or continue cycle play
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutput::OnMenuPauseCycle()
{
	g_pMainDlg->CyclePause();
}

/*********************************************************
  Function:	OnMenuMultiScreenLarge
  Desc:		multi-screen preview
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::OnMenuMultiScreenLarge()
{
	g_struLocalParam.bMultiScreen = TRUE;
	//brush the sidelines of chosen box
	g_pMainDlg->GetDlgItem(IDC_STATIC_PREVIEWBG)->Invalidate(TRUE);
	g_pMainDlg->FullScreen(g_struLocalParam.bMultiScreen);
	g_pMainDlg->ArrangeOutputs(g_pMainDlg->m_iCurWndNum);
}

/*********************************************************
  Function:	OnMenuStopPlay
  Desc:		stop preview 
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::OnMenuStopPlay()
{
	// TODO: Add your command handler code here
	if (m_lPlayHandle < 0 || g_bPlayAllDevice)
	{
		return ;
	}
	//NET_DVR_SetRealDataCallBack(m_lPlayHandle, NULL, 0);
	StopPlay();

	//change the color of 'play' button
	g_pMainDlg->ChangePlayBtnState();
}

/*********************************************************
  Function:	StartLocalRecord
  Desc:		start local record manually
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutput::StartLocalRecord()
{
	char cFilename[256];
	CTime time = CTime::GetCurrentTime();

    if (!g_bInSide && g_bStandardCB)
    {
        sprintf(cFilename, "%s%s_%02d_%d_%4d%02d%02d_%02d%02d%02d_%d_RTP.mp4", g_struLocalParam.chClientRecordPath, g_struDeviceInfo[m_struChanInfo.iDeviceIndex].chDeviceIPInFileName, \
            g_struDeviceInfo[m_struChanInfo.iDeviceIndex].iStartChan + m_struChanInfo.iChanIndex, (m_struChanInfo.dwProtocol & 0x80000000) >> 31, \
            time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), g_bInSide);
    }
    else
    {
        sprintf(cFilename, "%s%s_%02d_%d_%4d%02d%02d_%02d%02d%02d_%d.mp4", g_struLocalParam.chClientRecordPath, g_struDeviceInfo[m_struChanInfo.iDeviceIndex].chDeviceIPInFileName, \
            g_struDeviceInfo[m_struChanInfo.iDeviceIndex].iStartChan + m_struChanInfo.iChanIndex, (m_struChanInfo.dwProtocol & 0x80000000) >> 31, \
            time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), g_bInSide);
    }

	if (g_bInSide)
	{
		if (!NET_DVR_SaveRealData(m_lPlayHandle, cFilename))
		{
			AddLog(OPERATION_FAIL_T, "NET_DVR_SaveRealData:Filename = %s", cFilename);
			return;
		}
		else
		{
			AddLog(OPERATION_SUCC_T, "NET_DVR_SaveRealData:Filename = %s", cFilename);
 		}
	}
	else
	{
		if (m_fp == NULL)
		{
			m_fp = fopen(cFilename,"wb");
		}
        m_bSaveHead = FALSE;
	}

	m_lChangeFileNameTime = (time_t)(time.GetTime() + g_struLocalParam.iRecordFileInterval * 60);
	m_bLocalManualRec = TRUE;
    if (m_struChanInfo.iChanIndex >= ZERO_CHAN_INDEX)
    {
        g_struDeviceInfo[m_struChanInfo.iDeviceIndex].struZeroChan[m_struChanInfo.iChanIndex - ZERO_CHAN_INDEX].bLocalManualRec = TRUE;
    }
    else
    {
		g_struDeviceInfo[m_struChanInfo.iDeviceIndex].pStruChanInfo[m_struChanInfo.iChanIndex].bLocalManualRec = TRUE;
    }
	
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(m_struChanInfo.iDeviceIndex), LPARAM(m_struChanInfo.iChanIndex));	
}

/*********************************************************
  Function:	StopLocalRecord
  Desc:		stop local record
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::StopLocalRecord()
{
	if (!g_bInSide)// 
	{
		m_bSaveHead = FALSE;
		if (m_fp != NULL)
		{
			fclose(m_fp);
			m_fp = NULL;	
		}
	}
	else
	{
		if (NET_DVR_StopSaveRealData(m_lPlayHandle))
		{
			AddLog(OPERATION_SUCC_T, "NET_DVR_StopSaveRealData");
		}
		else
		{
			AddLog(OPERATION_FAIL_T, "NET_DVR_StopSaveRealData");
		}
	}

	m_bLocalManualRec = FALSE;
    if (m_struChanInfo.iChanIndex >= ZERO_CHAN_INDEX)
    {
        g_struDeviceInfo[m_struChanInfo.iDeviceIndex].struZeroChan[m_struChanInfo.iChanIndex - ZERO_CHAN_INDEX].bLocalManualRec = FALSE;
    }
    else
    {
		g_struDeviceInfo[m_struChanInfo.iDeviceIndex].pStruChanInfo[m_struChanInfo.iChanIndex].bLocalManualRec = FALSE;
    }
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(m_struChanInfo.iDeviceIndex), LPARAM(m_struChanInfo.iChanIndex));
}

/*********************************************************
  Function:	ChangeRecordFileName
  Desc:		change record file name, fixed time and size
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgOutput::ChangeRecordFileName()
{
	char cFilename[256] = {0};
	CTime time = CTime::GetCurrentTime();
	if (m_bLocalManualRec)
	{
		if (NET_DVR_StopSaveRealData(m_lPlayHandle))
		{
			AddLog(OPERATION_SUCC_T, "NET_DVR_StopSaveRealData");
		}
		else
		{
			AddLog(OPERATION_FAIL_T, "NET_DVR_StopSaveRealData");
		}
	}
	if (m_lPlayHandle >= 0)
	{
		sprintf(cFilename, "%s%s_%02d_%d_%4d%02d%02d_%02d%02d%02d.mp4", g_struLocalParam.chClientRecordPath, g_struDeviceInfo[m_struChanInfo.iDeviceIndex].chDeviceIPInFileName,\
			g_struDeviceInfo[m_struChanInfo.iDeviceIndex].iStartChan+m_struChanInfo.iChanIndex, (m_struChanInfo.dwProtocol & 0x80000000)>>31, \
			time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

		if (!NET_DVR_SaveRealData(m_lPlayHandle, cFilename))
		{
			AddLog(OPERATION_FAIL_T, "NET_DVR_SaveRealData:Filename = %s", cFilename);
			return;
		}
		else
		{
			AddLog(OPERATION_SUCC_T, "NET_DVR_SaveRealData:Filename = %s", cFilename);
 		}
		m_lChangeFileNameTime = (time_t)(time.GetTime() + g_struLocalParam.iRecordFileInterval * 60);
		m_bLocalManualRec = TRUE;
	}
}

/*********************************************************
  Function:	ChangeCurWinCfg
  Desc:		change current window configuration
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::ChangeCurWinCfg()
{
	if (g_pMainDlg->m_iCurWndIndex != m_iSubWndIndex && !g_bPlayAllDevice)
	{
		AddLog(OPERATION_SUCC_T, "win change");
	}
	g_pMainDlg->m_iCurWndIndex = m_iSubWndIndex;

	if (!g_struLocalParam.bUseCard)
	{
		DWORD dwBright,dwContrast, dwSaturation, dwHue;
		dwBright = dwContrast = dwSaturation = dwHue = 0;
		if (m_lPlayHandle >= 0)
		{
			if (!NET_DVR_ClientGetVideoEffect(m_lPlayHandle, &dwBright,&dwContrast, &dwSaturation, &dwHue))
			{
				AddLog(OPERATION_FAIL_T, "NET_DVR_ClientGetVideoEffect");
			}
		}
		else
		{
			dwBright = dwContrast = dwSaturation = dwHue = 6;//by default
		}
		g_struLocalParam.struVideoInfo[g_pMainDlg->m_iCurWndIndex].m_iBrightness = dwBright;
		g_struLocalParam.struVideoInfo[g_pMainDlg->m_iCurWndIndex].m_iContrast = dwContrast;
		g_struLocalParam.struVideoInfo[g_pMainDlg->m_iCurWndIndex].m_iSaturation = dwSaturation;
		g_struLocalParam.struVideoInfo[g_pMainDlg->m_iCurWndIndex].m_iHue = dwHue;		
	}

	//update current window video parameters
	g_pMainDlg->m_dlgOutputCtrl->UpdateVideoEff();

	//line around output window
	for (int i = 0;i < MAX_OUTPUTS;i++)
	{
		g_dlgOutput[i].DrawOutputBorder();
	}

	switch (m_iNetDelayBufNum)
	{
	case 1:
		g_pMainDlg->m_comboNetDelayBufNum.SetCurSel(0);
		break;
	case 3:
		g_pMainDlg->m_comboNetDelayBufNum.SetCurSel(1);
		break;
	case 6:
		g_pMainDlg->m_comboNetDelayBufNum.SetCurSel(2);
		break;
	case 15:
		g_pMainDlg->m_comboNetDelayBufNum.SetCurSel(3);
		break;
// 	case 30:
// 		g_pMainDlg->m_comboNetDelayBufNum.SetCurSel(4);
// 		break;
// 	case 45:
// 		g_pMainDlg->m_comboNetDelayBufNum.SetCurSel(4);
// 		break;
	default:
		g_pMainDlg->m_comboNetDelayBufNum.SetCurSel(0);
		break;
	}

	if (m_lPlayHandle >= 0)
	{
		g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(FALSE);
	}
	else
	{
		g_pMainDlg->m_comboNetDelayBufNum.EnableWindow(TRUE);
	}

	//UpdateData(FALSE);
}

/*********************************************************
  Function:	AddLog
  Desc:		add the log
  Input:	iLogType, log type;
			format, the list of parameter
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::AddLog(int iLogType, const char* format, ...)
{
	char szLogInfo[256] = {0};
	va_list arglist;
	va_start(arglist, format);	
	vsprintf(szLogInfo, format, arglist); 
	va_end(arglist);
	int iDeviceIndex = -1;
	int iChanIndex = -1;
	if (m_struChanInfo.iDeviceIndex == -1)
	{
		iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
		iChanIndex = g_pMainDlg->GetCurChanIndex();
	}
	else
	{
		iDeviceIndex = m_struChanInfo.iDeviceIndex;
		iChanIndex = m_struChanInfo.iChanIndex;		
	}
	if (iChanIndex == -1 || m_lPlayHandle < 0)
	{
		g_pMainDlg->AddLog(iDeviceIndex, iLogType, "winindex[%d] %s", m_iSubWndIndex, szLogInfo);
	}
	else
	{
		g_pMainDlg->AddLog(iDeviceIndex, iLogType, "%s %s winindex[%d] ", szLogInfo, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName, m_iSubWndIndex);
	}
}

/*********************************************************
  Function:	OnLButtonUp
  Desc:		send the zoom in command to device
  Input:    nFlags,the flag message of mouse;
			point, the position of the mouse click;	
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::OnLButtonUp(UINT nFlags, CPoint point) 
{
	BOOL bRet = FALSE;
	char szLan[32] = {0};
	if ((MK_CONTROL&nFlags) && (m_lPlayHandle != -1))
	{
		if (g_bPtzMaualTrace)
		{
			NET_DVR_PTZ_MANUALTRACE struPtzTrace = {0};
			struPtzTrace.dwSize = sizeof(struPtzTrace);
			struPtzTrace.dwChannel = 1;
			struPtzTrace.struPoint.fX = g_struPoint.fX;
			struPtzTrace.struPoint.fY = g_struPoint.fY;
			//有时候会没有选择类型
			if (g_iTrackType < 0)
			{
				g_iTrackType = 0;
			}
			struPtzTrace.byTrackType = g_iTrackType;
			if (!NET_DVR_RemoteControl(g_struDeviceInfo[m_struChanInfo.iDeviceIndex].lLoginID, NET_DVR_CONTROL_PTZ_MANUALTRACE, &struPtzTrace, sizeof(struPtzTrace)))
			{
				g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_CONTROL_PTZ_MANUALTRACE");
				return;
			}
			else
			{
				g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_CONTROL_PTZ_MANUALTRACE");
			}
		}
		else
		{
			POINT tPoint=point;	
			NET_DVR_POINT_FRAME ptFrame;
			
			g_rectZoomInShow.right=tPoint.x;
			g_rectZoomInShow.bottom=tPoint.y;
			//divides the width and height to 255 proportion
			ptFrame.xTop = (int)(g_rectZoomInMouse.left*255/m_struCardPlayParam.nWidth);
			ptFrame.yTop = (int)(g_rectZoomInMouse.top*255/m_struCardPlayParam.nHeight);
			ptFrame.xBottom = (int)(g_rectZoomInShow.right*255/m_struCardPlayParam.nWidth);
			ptFrame.yBottom = (int)(g_rectZoomInShow.bottom*255/m_struCardPlayParam.nHeight);
			
			if (g_rectZoomInMouse.left < g_rectZoomInShow.right)
			{
				if (g_rectZoomInMouse.top < g_rectZoomInShow.bottom)
				{
					ptFrame.bCounter = 4;
				}
				else
				{
					ptFrame.bCounter = 2;
				}
			}
			else
			{
				if (g_rectZoomInMouse.top < g_rectZoomInShow.bottom)
				{
					ptFrame.bCounter = 3;
				}
				else
				{
					ptFrame.bCounter = 1;
				}
			}
			
			if (m_lPlayHandle >= 0 && g_bInSide)
			{
				bRet =  NET_DVR_PTZSelZoomIn(m_lPlayHandle, &ptFrame);
			}
			else if (g_struDeviceInfo[m_struChanInfo.iDeviceIndex].lLoginID >= 0 )
			{
				bRet = NET_DVR_PTZSelZoomIn_EX(g_struDeviceInfo[m_struChanInfo.iDeviceIndex].lLoginID, \
					m_struChanInfo.iChanIndex+g_struDeviceInfo[m_struChanInfo.iDeviceIndex].iStartChan, &ptFrame);
			}
			
			if (bRet)
			{
				AddLog(OPERATION_SUCC_T, "NET_DVR_PTZSelZoomIn[%d][%d][%d][%d]count[%d]", ptFrame.xTop, ptFrame.yTop, ptFrame.xBottom, ptFrame.yBottom, ptFrame.bCounter);
			}
			else
			{
				AddLog(OPERATION_FAIL_T, "NET_DVR_PTZSelZoomIn");
				g_StringLanType(szLan, "区域缩放失败！", "Select Zoomin Failed");
				AfxMessageBox(szLan);
			}
		    CancelSelectZoom();  // todo!!!
		}
		
	}
	else
	{
		CancelSelectZoom();   // todo!!!
	}
	CDialog::OnLButtonUp(nFlags, point);
}

/*********************************************************
  Function:	CancelSelectZoom
  Desc:		cancel the range of selected
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::CancelSelectZoom()
{
	if (m_lPlayHandle != -1)
	{
		g_rectZoomInMouse.top = 0;
		g_rectZoomInMouse.left = 0;
		g_rectZoomInMouse.right = 0;
		g_rectZoomInMouse.bottom = 0;
		g_rectZoomInShow.top = 0;
		g_rectZoomInShow.left = 0;
		g_rectZoomInShow.right = 0;
		g_rectZoomInShow.bottom = 0;
		
		NET_DVR_RigisterDrawFun(m_lPlayHandle, NULL, 0);
	}
}
/*********************************************************
  Function:	OnMouseMove
  Desc:		get the area of zoom in
  Input:    nFlags,the flag message of mouse;
			point, the position of the mouse;	
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ((MK_CONTROL&nFlags) && (MK_LBUTTON&nFlags) && (m_lPlayHandle != -1))
	{
		POINT tPoint=point;
		g_rectZoomInShow.right=tPoint.x;
		g_rectZoomInShow.bottom=tPoint.y;
	}
	CDialog::OnMouseMove(nFlags, point);
}

/*********************************************************
  Function:	CapturePicture
  Desc:		capture the picture when decode the stream by hard card
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::CapturePicture()
{
	GetPictureSizeProc DLINK_HW_GetPictureSize;
	GetYV12ImageProc DLINK_HW_GetYV12Image;
	ConvertToBmpFileProc DLINK_HW_ConvertToBmpFile;
	if (m_hCardHandle != INVALID_HANDLE_VALUE)
	{
		DWORD dwWidth = 0;
		DWORD dwHeight = 0;
		char szFileName[256] = {0};
		CTime time=CTime::GetCurrentTime();
		PCHANNEL_INFO pChanInfo = &(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_struChanInfo);
		sprintf(szFileName, "%s\\PreviewCard_%s_%02d_%4d%02d%02d_%02d%02d%02d_%d.bmp", \
			g_struLocalParam.chPictureSavePath, g_struDeviceInfo[pChanInfo->iDeviceIndex].chDeviceIPInFileName, \
			g_struDeviceInfo[pChanInfo->iDeviceIndex].iStartChan+pChanInfo->iChanIndex,\
			time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), GetTickCount());
		DLINK_HW_GetPictureSize = (GetPictureSizeProc)GetProcAddress(g_hDSSDK, "HW_GetPictureSize");
		int iRet = DLINK_HW_GetPictureSize(m_hCardHandle, &dwWidth, &dwHeight);
		if (iRet == 0)
		{
				DWORD dwImageSize = dwWidth * dwHeight * 3 / 2;
				BYTE *pYV12 = NULL;

				pYV12 = new BYTE[dwImageSize];
				DLINK_HW_GetYV12Image = (GetYV12ImageProc)GetProcAddress(g_hDSSDK, "HW_GetYV12Image");
				iRet = DLINK_HW_GetYV12Image(m_hCardHandle, (BYTE*)pYV12, dwImageSize);
				if (iRet != 0)
				{
					if (pYV12 != NULL)
					{
						delete [] pYV12;
					}
					return;
				}
				DLINK_HW_ConvertToBmpFile = (ConvertToBmpFileProc)GetProcAddress(g_hDSSDK, "HW_ConvertToBmpFile");
				iRet = DLINK_HW_ConvertToBmpFile(pYV12, dwImageSize, dwWidth, dwHeight, szFileName, 0);
				if (pYV12 != NULL)
				{
					delete [] pYV12;
				}
				if (iRet != 0)
				{
					return;
				}		
		}
	}
	
}

/*********************************************************
  Function:	Restart
  Desc:		set the window for playing or cancel
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutput::Restart()
{
	if (g_bInSide && m_lPlayHandle >= 0)
	{
		if (m_bRestart)
		{
			if (NET_DVR_RealPlayRestart(m_lPlayHandle, GetSafeHwnd()))
			{
				AddLog(OPERATION_SUCC_T, "NET_DVR_RealPlayRestart");
			}
			else
			{
				AddLog(OPERATION_FAIL_T, "NET_DVR_RealPlayRestart");
			}
		}
		else
		{
			if (NET_DVR_RealPlayPause(m_lPlayHandle))
			{
				AddLog(OPERATION_SUCC_T, "NET_DVR_RealPlayPause");
			}
			else
			{
				AddLog(OPERATION_FAIL_T, "NET_DVR_RealPlayPause");
			}
		}
		m_bRestart = !m_bRestart;
	}
}

void CDlgOutput::OnMenuZeroFrontPage() 
{
    int iZeroChan = m_struChanInfo.iChanIndex - ZERO_CHAN_INDEX + g_struDeviceInfo[m_struChanInfo.iDeviceIndex].iStartChan;
	if (!NET_DVR_ZeroTurnOver(g_struDeviceInfo[m_struChanInfo.iDeviceIndex].lLoginID, iZeroChan, FALSE))
	{
        g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ZeroTurnOver Front Page");
    }
    else
    {
        g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_ZeroTurnOver Front Page");
    }
}

void CDlgOutput::OnMenuZeroNextPage() 
{
    int iZeroChan = m_struChanInfo.iChanIndex - ZERO_CHAN_INDEX + g_struDeviceInfo[m_struChanInfo.iDeviceIndex].iStartChan;
    if (!NET_DVR_ZeroTurnOver(g_struDeviceInfo[m_struChanInfo.iDeviceIndex].lLoginID, iZeroChan, TRUE))
    {
        g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ZeroTurnOver Next Page");
    }
    else
    {
        g_pMainDlg->AddLog(m_struChanInfo.iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_ZeroTurnOver Next Page");
    }

}


void CDlgOutput::DrawSensorValuText(HDC hDc, CString csDeciceIP, LONG lChannel)
{
    CRect rect;
    memset(&rect, 0, sizeof(rect));
    GetClientRect(&rect);

    char szLan[128] = {0};
    
    int nFontSize  = 0;
    if (g_struLocalParam.bEnlarged)
    {
        if (g_struLocalParam.bFullScreen)
        {
            nFontSize = 2;
        }
        else
        {
            nFontSize = 1;
        }
    }
    else
    {
        nFontSize = 0;
    }
    
    int bySensorChannel = 0;
    for (int i = 0; i < 16; i++) // todo!!! sensor num
    {
        if (g_struSensorAddPreview[i].byEnable == TRUE
            && 0 == strncmp(csDeciceIP.GetBuffer(0), g_struSensorAddPreview[i].struIPAddr.sIpV4, sizeof(g_struSensorAddPreview[i].struIPAddr.sIpV4)) 
            && lChannel == g_struSensorAddPreview[i].lChannel)
        {
            if (g_pMainDlg->m_struSensorAlarm[i].bySensorChannel != 0)
            {
                if (g_pMainDlg->m_struSensorAlarm[i].byAlarmType != 0)
                {

                    sprintf(szLan, "模拟量%d:%s %s %s %0.3f", i+1,g_pMainDlg->m_struSensorAlarm[i].byName, 
                        GetSensorType(g_pMainDlg->m_struSensorAlarm[i].byType),
                        GetSensorAlarmTypeStr(g_pMainDlg->m_struSensorAlarm[i].byAlarmType), g_pMainDlg->m_struSensorAlarm[i].fValue);
                    CDrawFun::DrawSensorText(hDc, szLan, RGB(255,0,0), rect,nFontSize);
                }
                else
                {
                    sprintf(szLan, "模拟量%d: %s %s 正常 %0.3f", i+1,
                        g_pMainDlg->m_struSensorAlarm[i].byName, 
                        GetSensorType(g_pMainDlg->m_struSensorAlarm[i].byType),
                        g_pMainDlg->m_struSensorAlarm[i].fValue);
                    CDrawFun::DrawSensorText(hDc, szLan, RGB(255,255,255), rect,nFontSize);
                }
                rect.top += 20*(nFontSize + 1);
            }
        }
    }
}


CString CDlgOutput::GetSensorType(DWORD dwSensorType)
{
//     SENSOR_TYPE_NONE = 0,       //无
//         SENSOR_TYPE_TEMPERATURE = 1, // 温度
//         SENSOR_TYPE_HUMIDITY ,      // 湿度
//         SENSOR_TYPE_WINDSPEED,      // 风速
//         SENSOR_TYPE_GAS,            //气体
//         SENSOR_TYPE_UNKNOW = 255    //未定义

    CString strTmp = "";
    switch (dwSensorType)
    {
    case SENSOR_TYPE_NONE:
        strTmp = "无";
        break;
    case SENSOR_TYPE_TEMPERATURE:
        strTmp = "温度";
        break;
    case SENSOR_TYPE_HUMIDITY :
        strTmp = "湿度";
        break;
    case SENSOR_TYPE_WINDSPEED:
        strTmp = "风速";
        break;
    case SENSOR_TYPE_GAS:
        strTmp = "气体";
        break;
    case SENSOR_TYPE_UNKNOW:
        strTmp = "未定义";
        break;
    
    default:
        strTmp = "未定义";
        break;
    }
    return strTmp;
}

CString CDlgOutput::GetSensorAlarmTypeStr(DWORD dwAlarmTye)
{
    CString strTmp = "";

    switch (dwAlarmTye)
    {
    case 0:
        strTmp = "正常";
        break;
    case 1:
        strTmp = "上4";
        break;
    case 2:
        strTmp = "上3";
        break;
    case 3:
        strTmp = "上2";
        break;
    case 4:
        strTmp = "上1";
        break;
    case 5:
        strTmp = "下1";
        break;
    case 6:
        strTmp = "下2";
        break;
    case 7:
        strTmp = "下3";
        break;
    case 8:
        strTmp = "下4";
        break;
    case 0xff:
        strTmp = "异常";
        break;
    default:
        strTmp = "未知";
        break;
    }
    return strTmp;
}

void CDlgOutput::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    BOOL bRet = FALSE;
    switch (nIDEvent)
    {
    case GET_NPQ_STATE_TIMER:
        if (8 == m_dwLinkMode && m_lPlayHandle >= 0)
        {
            NET_DVR_GetNPQStat(m_lPlayHandle, &m_struNPQStat);
        }
    default:
        break;
    }

    CDialog::OnTimer(nIDEvent);
}

void CDlgOutput::OnMenuShowOSD()
{
    UpdateData(TRUE);
    if (m_lPlayHandle < 0 || g_bPlayAllDevice)
    {
        return ;
    }
    //NET_DVR_SetRealDataCallBack(m_lPlayHandle, NULL, 0);
    char szLan[128] = {0};
    LONG lPlayerPort = NET_DVR_GetRealPlayerIndex(m_lPlayHandle);
    BOOL bRet = FALSE;
    
    
    CString struAlarmOutText = "";
    DWORD dwID = 0;
   	CMenu pMenu;
    
    if (!pMenu.LoadMenu(IDR_MENU_MYOUTPUT))
    {
        return;
    }
    
    //GetMenutem(ID_MENU_SHOWOSD)->GetWindowText(struAlarmOutText);
    pMenu.GetSubMenu(0)->GetMenuString(ID_MENU_SHOWOSD,struAlarmOutText,MF_BYCOMMAND);
    // if (struAlarmOutText.Find("显示ATM信息") != -1 || struAlarmOutText.Find("Show OSD") != -1)
    DWORD dwPRIDATA_RENDER = RENDER_ANA_INTEL_DATA | RENDER_MD | RENDER_ADD_POS | RENDER_ADD_PIC | RENDER_FIRE_DETCET | RENDER_TEM;
    if (!m_bShowOSD)
    {
        if (lPlayerPort > -1)
        {
            
           // bRet = RenderPrivateData(lPlayerPort, dwPRIDATA_RENDER,TRUE );
            bRet = NET_DVR_RenderPrivateData(lPlayerPort, dwPRIDATA_RENDER, TRUE);
            if (!bRet)
            {
                g_StringLanType(szLan, "调用EnablePOS接口设置 打开OSD 失败", "Load EnablePOS show OSD show  failed");
                AfxMessageBox(szLan);
                return;
            }
            dwPRIDATA_RENDER = FIRE_FRAME_DIS | FIRE_MAX_TEMP | FIRE_MAX_TEMP_POSITION | FIRE_DISTANCE;
            NET_DVR_RenderPrivateDataEx(lPlayerPort, RENDER_FIRE_DETCET, dwPRIDATA_RENDER, TRUE);
            dwPRIDATA_RENDER = TEM_REGION_BOX | TEM_REGION_LINE | TEM_REGION_POINT;
            NET_DVR_RenderPrivateDataEx(lPlayerPort, RENDER_TEM, dwPRIDATA_RENDER, TRUE);
            m_bShowOSD = TRUE;
        }
        else
        {
            g_StringLanType(szLan, "获取预览时用来解码显示的播放库句柄失败", "Get Preview Player Index Failed");
            AfxMessageBox(szLan);
            m_bShowOSD = FALSE;
            return;
        }
    } 
    else
    {
        if (lPlayerPort > -1)
        {
            bRet = NET_DVR_RenderPrivateData(lPlayerPort, dwPRIDATA_RENDER, FALSE);
            if (!bRet)
            {
                m_bShowOSD = TRUE;
                g_StringLanType(szLan, "调用EnablePOS接口 关闭OSD 失败", "Load EnablePOS Close OSD show  failed");
                AfxMessageBox(szLan);
                return;
            }
            m_bShowOSD = FALSE;
        }
        else
        {
            g_StringLanType(szLan, "获取预览时用来解码显示的播放库句柄失败", "Get Preview Player Index Failed");
            AfxMessageBox(szLan);
            return;
        }
    }
    
}
