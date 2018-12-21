/**********************************************************
FileName:    DlgOutputCtrl.cpp
Description: PTZ,video/audio parameters set while preview      
Date:        2008/05/17
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp  
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgOutputCtrl.h"
#include ".\dlgoutputctrl.h"
#include "DlgPTZPreset.h"
#include "DlgPTZCruise.h"
#include "DlgPtzParkActionCfg.h"

extern BOOL g_bPtzMaualTrace;
extern int g_iTrackType;
/*********************************************************
  Function:	PTZPresetAll
  Desc:		include NET_DVR_PTZPreset_EX and NET_DVR_PTZPreset_Other
  Input:	lRealHandle, the handle of real play;
			iDevIndex, the index of the device in local structure;
			iChanIndex, the index of channel;
			dwPTZCommand, the command of ptz;
			dwPresetIndex, the index of preset;
			szCmdString, the string to print;
  Output:	none
  Return:	TRUE,means successful; FALSE, means failed;
**********************************************************/
BOOL PTZPresetAll(LONG lRealHandle, int iDevIndex, int iChanIndex, \
						  DWORD dwPTZCommand, DWORD dwPresetIndex, char *szCmdString)
{
	BOOL bRet = FALSE;
	LONG lLoginID = -1;
	LONG lChanNum = -1;

	if (iDevIndex >= 0)
	{
		lLoginID = g_struDeviceInfo[iDevIndex].lLoginID;
		lChanNum = g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;
		//lChanNum = iChanIndex + g_struDeviceInfo[iDevIndex].iStartChan;
	}
	if (lRealHandle >= 0 && g_bInSide)
	{
		bRet = NET_DVR_PTZPreset(lRealHandle, dwPTZCommand, dwPresetIndex);//not preview socket
		if (bRet)
		{
			g_dlgOutput[g_pMainDlg->m_iCurWndIndex].AddLog(OPERATION_SUCC_T, "NET_DVR_PTZPreset[%d] %s[%d]presetindex[%d]", g_struLocalParam.bPreviewBlock, szCmdString, dwPTZCommand, dwPresetIndex);
		}
		else
		{
			g_dlgOutput[g_pMainDlg->m_iCurWndIndex].AddLog(OPERATION_FAIL_T, "NET_DVR_PTZPreset[%d] %s[%d]presetindex[%d]", g_struLocalParam.bPreviewBlock, szCmdString,dwPTZCommand, dwPresetIndex);
		}
	}
	else if (lLoginID >= 0 && iChanIndex >= 0)
	{
		bRet = NET_DVR_PTZPreset_Other(lLoginID, lChanNum, dwPTZCommand, dwPresetIndex);
		if (bRet)
		{
			g_pMainDlg->AddLog(iDevIndex, OPERATION_SUCC_T, "NET_DVR_PTZPreset_Other %s %s[%d]presetindex[%d]", g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].chChanName, szCmdString, dwPTZCommand, dwPresetIndex);
		}
		else
		{
			g_pMainDlg->AddLog(iDevIndex, OPERATION_FAIL_T, "NET_DVR_PTZPreset_Other %s %s[%d]presetindex[%d]", g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].chChanName, szCmdString, dwPTZCommand, dwPresetIndex);
		}
	}
	return bRet;
}

/*********************************************************
  Function:	PTZCruiseAll
  Desc:		include NET_DVR_PTZPreset_EX and NET_DVR_PTZPreset_Other
  Input:	lRealHandle, the handle of real play;
			iDevIndex, the index of the device in local structure;
			iChanIndex, the index of channel;
			dwPTZCruiseCmd, the curise command of ptz;
			byCruiseRoute, the index of curise route;
			szCmdString, the string to print;
  Output:	none
  Return:	none
**********************************************************/
BOOL PTZCruiseAll(LONG lRealHandle, int iDevIndex, int iChanIndex, DWORD dwPTZCruiseCmd,BYTE byCruiseRoute, BYTE byCruisePoint, WORD wInput, char *szCmdString)
{
	BOOL bRet = FALSE;
	LONG lLoginID = -1;
	LONG lChanNum = -1;

	if (iDevIndex >= 0)
	{
		lLoginID = g_struDeviceInfo[iDevIndex].lLoginID;
		//lChanNum = iChanIndex + g_struDeviceInfo[iDevIndex].iStartChan;
		lChanNum = g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;
	}
	if (lRealHandle >= 0 && g_bInSide)
	{

		bRet = NET_DVR_PTZCruise(lRealHandle, dwPTZCruiseCmd, byCruiseRoute, byCruisePoint, wInput);//not preview socket	
		if (bRet)
		{
			g_dlgOutput[g_pMainDlg->m_iCurWndIndex].AddLog(OPERATION_SUCC_T, "NET_DVR_PTZCruise[%d] %s cruise[%d] point[%d] input[%d]", g_struLocalParam.bPreviewBlock, szCmdString, byCruiseRoute, byCruisePoint, wInput);
		}
		else
		{
			g_dlgOutput[g_pMainDlg->m_iCurWndIndex].AddLog(OPERATION_FAIL_T, "NET_DVR_PTZCruise[%d] %s cruise[%d] point[%d] input[%d]", g_struLocalParam.bPreviewBlock, szCmdString, byCruiseRoute, byCruisePoint, wInput);
		}	
	
	}
	else if (lLoginID >= 0 && iChanIndex >= 0)
	{
		bRet = NET_DVR_PTZCruise_Other(lLoginID, lChanNum, dwPTZCruiseCmd, byCruiseRoute, byCruisePoint, wInput);
		if (bRet)
		{
			g_pMainDlg->AddLog(iDevIndex, OPERATION_SUCC_T, "NET_DVR_PTZCruise_Other %s cruise[%d] point[%d] input[%d] %s", szCmdString, byCruiseRoute, byCruisePoint, wInput, g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].chChanName);
		}
		else
		{
			g_pMainDlg->AddLog(iDevIndex, OPERATION_FAIL_T, "NET_DVR_PTZCruise_Other %s cruise[%d] point[%d] input[%d] %s", szCmdString, byCruiseRoute, byCruisePoint, wInput, g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].chChanName);
		}
	}
	return bRet;
}

/*********************************************************
  Function:	PTZTrackAll
  Desc:		include NET_DVR_PTZTrack_EX and NET_DVR_PTZTrack_Other
  Input:	lRealHandle, the handle of real play;
			iDevIndex, the index of the device in local structure;
			iChanIndex, the index of channel;
			dwPTZCmd, the track command of ptz;
			szCmdString, the string to print;
  Output:	none
  Return:	none
**********************************************************/
BOOL PTZTrackAll(LONG lRealHandle, int iDevIndex, int iChanIndex, DWORD dwPTZCommand, char *szCmdString, int iPatternID)
{
	BOOL bRet = FALSE;
	LONG lLoginID = -1;
	LONG lChanNum = -1;

	if (iDevIndex >= 0)
	{
		lLoginID = g_struDeviceInfo[iDevIndex].lLoginID;
		//lChanNum = iChanIndex + g_struDeviceInfo[iDevIndex].iStartChan;
		lChanNum = g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;
	}
// 	if (lRealHandle >= 0 && g_bInSide)
// 	{
// 		bRet = NET_DVR_PTZTrack(lRealHandle, dwPTZCommand);//not preview socket
// 		if (bRet)
// 		{
// 			g_dlgOutput[g_pMainDlg->m_iCurWndIndex].AddLog(OPERATION_SUCC_T, "NET_DVR_PTZTrack[%d] %s[%d]", g_struLocalParam.bPreviewBlock, szCmdString, dwPTZCommand);
// 		}
// 		else
// 		{
// 			g_dlgOutput[g_pMainDlg->m_iCurWndIndex].AddLog(OPERATION_FAIL_T, "NET_DVR_PTZTrack[%d] %s[%d]", g_struLocalParam.bPreviewBlock, szCmdString, dwPTZCommand);
// 		}
// 	}
// 	else if (lLoginID >= 0 && iChanIndex >= 0)
// 	{
// 		bRet = NET_DVR_PTZTrack_Other(lLoginID, lChanNum, dwPTZCommand);
// 		if (bRet)
// 		{
// 			g_pMainDlg->AddLog(iDevIndex, OPERATION_SUCC_T, "NET_DVR_PTZTrack_Other %s %s[%d]", g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].chChanName, szCmdString, dwPTZCommand);
// 		}
// 		else
// 		{
// 			g_pMainDlg->AddLog(iDevIndex, OPERATION_FAIL_T, "NET_DVR_PTZTrack_Othe %s %s[%d]", g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].chChanName, szCmdString, dwPTZCommand);
// 		}
// 	}

    NET_DVR_PTZ_PATTERN struPtzPattern = {0};
	struPtzPattern.dwSize = sizeof(struPtzPattern);
    struPtzPattern.dwChannel = lChanNum;
	struPtzPattern.dwPatternCmd = dwPTZCommand;
	struPtzPattern.dwPatternID = iPatternID;
	if (!NET_DVR_RemoteControl(lLoginID, NET_DVR_CONTROL_PTZ_PATTERN, &struPtzPattern, sizeof(struPtzPattern)))
	{
		g_pMainDlg->AddLog(iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_CONTROL_PTZ_PATTERN failed");
	}
	else
	{
		g_pMainDlg->AddLog(iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_CONTROL_PTZ_PATTERN SUCCESS");
	}
	return bRet;
}

// CDlgOutputCtrl dialog
/*********************************************************
  Function:	CDlgOutputCtrl
  Desc:		Constructor
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgOutputCtrl, CDialog)
CDlgOutputCtrl::CDlgOutputCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOutputCtrl::IDD, pParent)
	, m_iCruiseRoute(0)
	, m_iSelSpeed(0)
{

}

/*********************************************************
  Function:	~CDlgOutputCtrl
  Desc:		destructor
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
CDlgOutputCtrl::~CDlgOutputCtrl()
{
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutputCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOutputCtrl)
	DDX_Control(pDX, IDC_COMBO_TRACKTYPE, m_comboTrackType);
	DDX_Control(pDX, IDC_COMBO_PATTERN_ID, m_comboPatternID);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_sliderVolume);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_sliderHue);
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_sliderSaturation);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_sliderContrast);
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_sliderBrightness);
	DDX_Control(pDX, IDC_SLIDER_SHARPNESS_EFFECT, m_sliderSharpness);
	DDX_Control(pDX, IDC_SLIDER_DENOISING_EFFECT, m_sliderDenoising);
	DDX_Control(pDX, IDC_COMBO_PRESET, m_comboPreset);
	DDX_Control(pDX, IDC_COMBO_CRUISE, m_comboCruise);
	DDX_Control(pDX, IDC_COMBO_SPEED, m_comboSpeed);
//	DDX_Check(pDX, IDC_CHK_TRACK_MODE, m_bChkTrack);
	DDX_Check(pDX, IDC_CHK_PTZ_MANUALTRACE, m_bChkPtzManualTrace);
	//}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgOutputCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgOutputCtrl)	
	ON_BN_CLICKED(IDC_BTN_CRUISE_ADJUST, OnBnClickedBtnCruiseAdjust)
	ON_BN_CLICKED(IDC_BTN_PRESET_ADJUST, OnBnClickedBtnAdjustPreset)
	ON_BN_CLICKED(IDC_BTN_DEFAUT, OnBnClickedBtnDefaut)
	ON_BN_CLICKED(IDC_BTN_PRESET_SETUP, OnBnClickedBtnPresetSetup)
	ON_BN_CLICKED(IDC_BTN_CRUISE_SETUP, OnBnClickedBtnCruiseSetup)
	ON_BN_CLICKED(IDC_BTN_TRACK_START_MEM, OnBnClickedBtnTrackStartMem)
	ON_BN_CLICKED(IDC_BTN_TRACK_STOP_MEM, OnBnClickedBtnTrackStopMem)
	ON_BN_CLICKED(IDC_BTN_TRACK_RUN, OnBnClickedBtnTrackRun)
	ON_CBN_SELCHANGE(IDC_COMBO_CRUISE, OnCbnSelchangeComboCruise)
	ON_WM_HSCROLL()
	ON_CBN_SELCHANGE(IDC_COMBO_SPEED, OnSelchangeComboSpeed)
	ON_BN_CLICKED(IDC_BTN_TRACK_DELETE_ID, OnBtnTrackDeleteId)
	ON_BN_CLICKED(IDC_BTN_TRACK_DELETE_ALL, OnBtnTrackDeleteAll)
	ON_BN_CLICKED(IDC_BTN_TRACK_STOP, OnBtnTrackStop)
	ON_BN_CLICKED(IDC_BTN_PTZ_PARKACTION, OnBtnPtzParkaction)
	ON_BN_CLICKED(IDC_CHK_PTZ_MANUALTRACE, OnChkPtzManualtrace)
	ON_CBN_EDITCHANGE(IDC_COMBO_TRACKTYPE, OnEditchangeComboTracktype)
	ON_BN_CLICKED(IDC_BTN_CRUISE_DEL, OnBtnCruiseDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgOutputCtrl message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		initialize dialog box
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BOOL CDlgOutputCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_sliderBrightness.SetRange(1,10,TRUE);
	m_sliderHue.SetRange(1,10,TRUE);
	m_sliderSaturation.SetRange(1,10,TRUE);
	m_sliderContrast.SetRange(1,10,TRUE);
	m_sliderSharpness.SetRange(1, 10, TRUE);
	m_sliderDenoising.SetRange(1, 10, TRUE);
	m_sliderVolume.SetRange(1,100,TRUE);
	m_sliderBrightness.SetPos(DEFAULT_BRIGHTNESS);
	m_sliderHue.SetPos(DEFAULT_HUE);
	m_sliderSaturation.SetPos(DEFAULT_SATURATION);
	m_sliderContrast.SetPos(DEFAULT_CONTRAST);
	m_sliderSharpness.SetPos(DEFAULT_SHARPNESS);
	m_sliderDenoising.SetPos(DEFAULT_DENOISING);
	m_sliderVolume.SetPos(DEFAULT_VOLUME);

	m_btnPtzUp.SubclassDlgItem(IDC_BTN_PTZ_UP,this);
	m_btnPtzDown.SubclassDlgItem(IDC_BTN_PTZ_DOWN,this);
	m_btnPtzLeft.SubclassDlgItem(IDC_BTN_PTZ_LEFT,this);
	m_btnPtzRight.SubclassDlgItem(IDC_BTN_PTZ_RIGHT,this);	
	m_btnZoomOut.SubclassDlgItem(IDC_BTN_ZOOM_OUT,this);
	m_btnZoomIn.SubclassDlgItem(IDC_BTN_ZOOM_IN,this);
	m_btnFocusNear.SubclassDlgItem(IDC_BTN_FOCUS_NEAR,this);
	m_btnFocusFar.SubclassDlgItem(IDC_BTN_FOCUS_FAR,this);
	m_btnIrisOpen.SubclassDlgItem(IDC_BTN_IRIS_OPEN,this);
	m_btnIrisClose.SubclassDlgItem(IDC_BTN_IRIS_CLOSE,this);

	int i=0;
	char szNum[8] = {0};
	m_comboPreset.ResetContent();
	for (i=0; i<300/*MAX_PRESET_V40+1*/; i++)
	{
		sprintf(szNum, "%d", i+1);
		m_comboPreset.AddString(szNum);
	}
	m_comboPreset.SetCurSel(0);

	m_comboCruise.ResetContent();
	for (i=1; i<MAX_CRUISE_V30 +1; i++)//in fact, MAX index is decided by the type of ptz;here 256 is just for test
	{
		sprintf(szNum, "%d", i);
		m_comboCruise.AddString(szNum);
	}
	m_iCruiseRoute = 1;
	m_comboCruise.SetCurSel(0);
	m_comboSpeed.SetCurSel(1); //0 default mean send the control command on the preview socket, but the rtsp protocol doesn't realize this function.
	m_comboPatternID.SetCurSel(0);
// 	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
// 	int iChanIndex = g_pMainDlg->GetCurChanIndex();
// 	LONG lLoginID = -1;
// 	LONG lChanNum = -1;
// 	
// 	if (iDevIndex >= 0)
// 	{
// 		lLoginID = g_struDeviceInfo[iDevIndex].lLoginID;
// 		lChanNum = g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;
// 	}
// 	NET_DVR_MOTION_TRACK_CFG strMotionTtackCfg = {0};
// 	DWORD dwReturn;
// 	if (!NET_DVR_GetDVRConfig(lLoginID,  NET_DVR_GET_MOTION_TRACK_CFG, 1, &strMotionTtackCfg, sizeof(strMotionTtackCfg), &dwReturn))
//     {
//         g_pMainDlg->AddLog(iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_MOTION_TRACK_CFG Fail");
//     }
//     else
//     {
//         g_pMainDlg->AddLog(iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_MOTION_TRACK_CFG Success");
//     }
// 	m_bChkTrack = strMotionTtackCfg.byEnableTrack;
	
	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
  Function:	UpdateVideoEff
  Desc:		update video/audio parameters in control box 
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutputCtrl::UpdateVideoEff()
{
	m_sliderBrightness.SetPos(g_struLocalParam.struVideoInfo[g_pMainDlg->m_iCurWndIndex].m_iBrightness);
	m_sliderHue.SetPos(g_struLocalParam.struVideoInfo[g_pMainDlg->m_iCurWndIndex].m_iHue);
	m_sliderSaturation.SetPos(g_struLocalParam.struVideoInfo[g_pMainDlg->m_iCurWndIndex].m_iSaturation);
	m_sliderContrast.SetPos(g_struLocalParam.struVideoInfo[g_pMainDlg->m_iCurWndIndex].m_iContrast);
	m_sliderSharpness.SetPos(g_struLocalParam.struVideoInfo[g_pMainDlg->m_iCurWndIndex].m_iSharpness);
	m_sliderDenoising.SetPos(g_struLocalParam.struVideoInfo[g_pMainDlg->m_iCurWndIndex].m_iDenoising);
	m_sliderVolume.SetPos(g_struLocalParam.iVolume);
	//UpdateData(FALSE);
}


/*********************************************************
  Function:	OnHScroll
  Desc:		drag mouse response function, setting video effect and volume
  Input:	nSBCode, code of scroll;
			nPos, the position of scroll;
			pScrollBar, point to the scroll bar;
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutputCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int i;
	WORD	wTemp;
	WORD	wVolumevalue;
	BOOL bRet = FALSE;
	char szLan[1024] = {0};

	i = g_pMainDlg->m_iCurWndIndex;
	wTemp = (0xFFFF) / 100;

	NET_DVR_VIDEOPARA_V40 struVideoPara;
	memset(&struVideoPara, 0, sizeof(NET_DVR_VIDEOPARA_V40));
	static DWORD DvrVal[10] = {0, 25, 50, 75, 100, 128, 160, 192, 224, 255};


	if (g_dlgOutput[i].m_lPlayHandle >= 0)
	{
		if (GetDlgItem(IDC_SLIDER_BRIGHTNESS) == pScrollBar)
		{
			g_struLocalParam.struVideoInfo[i].m_iBrightness = /*10 - */m_sliderBrightness.GetPos();
			struVideoPara.dwVideoParamType = 0;
			struVideoPara.dwVideoParamValue = DvrVal[m_sliderBrightness.GetPos()-1];
			bRet = TRUE;
		}
		else if (GetDlgItem(IDC_SLIDER_CONTRAST) == pScrollBar)
		{
			g_struLocalParam.struVideoInfo[i].m_iContrast = /*10 - */m_sliderContrast.GetPos();
			struVideoPara.dwVideoParamType = 1;
			struVideoPara.dwVideoParamValue = DvrVal[m_sliderContrast.GetPos()-1];
			bRet = TRUE;
		}
		else if (GetDlgItem(IDC_SLIDER_SATURATION) == pScrollBar)
		{
			g_struLocalParam.struVideoInfo[i].m_iSaturation = /*10 - */m_sliderSaturation.GetPos();
			struVideoPara.dwVideoParamType = 2;
			struVideoPara.dwVideoParamValue = DvrVal[m_sliderSaturation.GetPos()-1];
			bRet = TRUE;
		}
		else if (GetDlgItem(IDC_SLIDER_HUE) == pScrollBar)
		{
			g_struLocalParam.struVideoInfo[i].m_iHue= /*10 - */m_sliderHue.GetPos();
			struVideoPara.dwVideoParamType = 3;
			struVideoPara.dwVideoParamValue = DvrVal[m_sliderHue.GetPos()-1];
			bRet = TRUE;
		}
		else if (GetDlgItem(IDC_SLIDER_SHARPNESS_EFFECT) == pScrollBar)
		{
			g_struLocalParam.struVideoInfo[i].m_iSharpness= /*10 - */m_sliderSharpness.GetPos();
			struVideoPara.dwVideoParamType = 4;
			struVideoPara.dwVideoParamValue = DvrVal[m_sliderSharpness.GetPos()-1];
			bRet = TRUE;
		}
		else if (GetDlgItem(IDC_SLIDER_DENOISING_EFFECT) == pScrollBar)
		{
			g_struLocalParam.struVideoInfo[i].m_iDenoising= /*10 - */m_sliderDenoising.GetPos();
			struVideoPara.dwVideoParamType = 5;
			struVideoPara.dwVideoParamValue = DvrVal[m_sliderDenoising.GetPos()-1];
			bRet = TRUE;
		}


		struVideoPara.dwChannel = g_dlgOutput[i].m_lChannel;

		int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

		if (bRet)
		{
			if (!NET_DVR_RemoteControl(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_SET_VIDEO_EFFECT, &struVideoPara, sizeof(NET_DVR_VIDEOPARA_V40)))
			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SET_VIDEO_EFFECT failed");

				//失败了，使用老接口设置
				bRet = NET_DVR_ClientSetVideoEffect(g_dlgOutput[i].m_lPlayHandle, g_struLocalParam.struVideoInfo[i].m_iBrightness, g_struLocalParam.struVideoInfo[i].m_iContrast, 
					g_struLocalParam.struVideoInfo[i].m_iSaturation, g_struLocalParam.struVideoInfo[i].m_iHue);
				if (!bRet)
				{
					g_dlgOutput[i].AddLog(OPERATION_FAIL_T, "NET_DVR_ClientSetVideoEffect");
					g_StringLanType(szLan, "设置视频参数失败", "Fail to Set video parameters");
					AfxMessageBox(szLan);
				}
				else
				{
					g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_ClientSetVideoEffect");
				}

			}
			else
			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SET_VIDEO_EFFECT SUCCESS");
			}
		}
	}

	if (GetDlgItem(IDC_SLIDER_VOLUME) == pScrollBar)
	{
		g_struLocalParam.iVolume = m_sliderVolume.GetPos();
		wVolumevalue = (WORD)((WORD)(m_sliderVolume.GetPos()) * wTemp);
		if (g_lVoiceHandle >= 0)
		{
			g_dlgOutput[i].AddLog(OPERATION_SUCC_T, "NET_DVR_SetVoiceComClientVolume");

			NET_DVR_SetVoiceComClientVolume(g_lVoiceHandle, wVolumevalue);
		}
		else if (g_dlgOutput[i].m_bPlaySound && (g_dlgOutput[i].m_lPlayHandle >= 0))
		{
			g_dlgOutput[i].StartSound(wVolumevalue);
		}
	}	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/*********************************************************
  Function:	OnBnClickedBtnDefaut
  Desc:		restore video/audio parameters by default
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutputCtrl::OnBnClickedBtnDefaut()
{
	int i = g_pMainDlg->m_iCurWndIndex;
	WORD wTemp = (0xFFFF) / 100;
	WORD	wVolumevalue;

	g_struLocalParam.struVideoInfo[i].m_iBrightness = DEFAULT_BRIGHTNESS;
	g_struLocalParam.struVideoInfo[i].m_iContrast = DEFAULT_CONTRAST;
	g_struLocalParam.struVideoInfo[i].m_iSaturation = DEFAULT_SATURATION;
	g_struLocalParam.struVideoInfo[i].m_iHue = DEFAULT_HUE;
	NET_DVR_ClientSetVideoEffect(g_dlgOutput[i].m_lPlayHandle, \
		g_struLocalParam.struVideoInfo[i].m_iBrightness, g_struLocalParam.struVideoInfo[i].m_iContrast, \
		g_struLocalParam.struVideoInfo[i].m_iSaturation, g_struLocalParam.struVideoInfo[i].m_iHue);

	g_struLocalParam.iVolume = DEFAULT_VOLUME;
	if (g_lVoiceHandle >= 0)
	{	
		wVolumevalue = (WORD)(g_struLocalParam.iVolume) * 10 *wTemp;
		if (NET_DVR_SetVoiceComClientVolume(g_lVoiceHandle, wVolumevalue))
		{
			g_dlgOutput[i].AddLog(OPERATION_SUCC_T, "NET_DVR_SetVoiceComClientVolume volume[%d]", wVolumevalue);
		}
		else
		{
			g_dlgOutput[i].AddLog(OPERATION_FAIL_T, "NET_DVR_SetVoiceComClientVolume volume[%d]", wVolumevalue);
		}
	}
	else if (g_dlgOutput[i].m_bPlaySound)
	{
		wVolumevalue = (WORD)((WORD)(g_struLocalParam.iVolume) * 10 * wTemp);
		g_dlgOutput[i].StartSound(wVolumevalue);
	}
	m_sliderBrightness.SetPos(g_struLocalParam.struVideoInfo[i].m_iBrightness);
	m_sliderHue.SetPos(g_struLocalParam.struVideoInfo[i].m_iHue);
	m_sliderSaturation.SetPos(g_struLocalParam.struVideoInfo[i].m_iSaturation);
	m_sliderContrast.SetPos(g_struLocalParam.struVideoInfo[i].m_iContrast);
	m_sliderVolume.SetPos(g_struLocalParam.iVolume);
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnPresetSetup
  Desc:		set preset
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutputCtrl::OnBnClickedBtnPresetSetup()
{
	CDlgPTZPreset dlg;
	dlg.DoModal();
}

/*********************************************************
  Function:	OnBnClickedBtnPresetSetup
  Desc:		set preset
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutputCtrl::OnBnClickedBtnCruiseAdjust()
{
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	m_iCruiseRoute = m_comboCruise.GetCurSel()+1;//start with 1 

	PTZCruiseAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex,\
			iChanIndex, RUN_SEQ, BYTE(m_iCruiseRoute), 0, 0, "RUN_SEQ");	
}


/*********************************************************
  Function:	OnBnClickedBtnAdjustPreset
  Desc:		adjust preset
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutputCtrl::OnBnClickedBtnAdjustPreset()
{
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPreset = m_comboPreset.GetCurSel()+1;//start with 1 

	PTZPresetAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, GOTO_PRESET, iPreset, "GOTO_PRESET");
}


/*********************************************************
  Function:	OnCbnSelchangeComboCruise
  Desc:		stop last cruise when change the select
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutputCtrl::OnCbnSelchangeComboCruise()
{
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	
	PTZCruiseAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, STOP_SEQ, BYTE(m_iCruiseRoute), 0, 0, "STOP_SEQ");	
}

/*********************************************************
  Function:	OnBnClickedBtnCruiseSetup
  Desc:		set cruise
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutputCtrl::OnBnClickedBtnCruiseSetup()
{
	CDlgPTZCruise dlg;
	dlg.DoModal();
}

/*********************************************************
  Function:	OnBnClickedBtnTrackStartMem
  Desc:		start track memorization
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutputCtrl::OnBnClickedBtnTrackStartMem()
{
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPatternID = m_comboPatternID.GetCurSel()+1;
	PTZTrackAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, STA_MEM_CRUISE, "STA_MEM_CRUISE", iPatternID);	
}

/*********************************************************
  Function:	OnBnClickedBtnTrackStopMem
  Desc:		stop track memorization
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CDlgOutputCtrl::OnBnClickedBtnTrackStopMem()
{
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPatternID = m_comboPatternID.GetCurSel()+1;
	PTZTrackAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, STO_MEM_CRUISE, "STO_MEM_CRUISE", iPatternID);	
}


/*********************************************************
  Function:	OnBnClickedBtnTrackRun
  Desc:		run tracking
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutputCtrl::OnBnClickedBtnTrackRun()
{
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPatternID = m_comboPatternID.GetCurSel()+1;
	PTZTrackAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, RUN_CRUISE, "RUN_CRUISE", iPatternID);	
}

/*********************************************************
  Function:	OnSelchangeComboSpeed
  Desc:		speed of NET_DVR_PTZControlWithSpeed
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgOutputCtrl::OnSelchangeComboSpeed() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iSelSpeed = m_comboSpeed.GetCurSel();
}

/*********************************************************
  Function:	PreTranslateMessage
  Desc:		the get the enter and escape key message
  Input:	pMsg, the message of key
  Output:	none
  Return:	TRUE, means successful; FALSE, means failed;
**********************************************************/
BOOL CDlgOutputCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE)
	{
		return TRUE;
	}
	if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	{
		return TRUE; 
	}
	else
	{
		return CDialog::PreTranslateMessage(pMsg);
	}	
}

void CDlgOutputCtrl::OnBtnTrackDeleteId() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPatternID = m_comboPatternID.GetCurSel()+1;
	PTZTrackAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, DELETE_CRUISE, "DELETE_CRUISE", iPatternID);
}

void CDlgOutputCtrl::OnBtnTrackDeleteAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPatternID = m_comboPatternID.GetCurSel()+1;
	PTZTrackAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, DELETE_ALL_CRUISE, "DELETE_CRUISE", iPatternID);
}

void CDlgOutputCtrl::OnBtnTrackStop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPatternID = m_comboPatternID.GetCurSel()+1;
	PTZTrackAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, STOP_CRUISE, "DELETE_CRUISE", iPatternID);
}

void CDlgOutputCtrl::OnBtnPtzParkaction() 
{
	// TODO: Add your control notification handler code here
	CDlgPtzParkActionCfg dlg;
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	if (iDevIndex >= 0 && iChanIndex >= 0)
	{
		dlg.m_lLoginID = g_struDeviceInfo[iDevIndex].lLoginID;
		dlg.m_lChanNum = g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;
		dlg.m_iDevIndex = iDevIndex;
		dlg.DoModal();
	}
	else
	{
		return;
	}
}

/*
void CDlgOutputCtrl::OnChkTrackMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	LONG lLoginID = -1;
	LONG lChanNum = -1;
	
	if (iDevIndex >= 0)
	{
		lLoginID = g_struDeviceInfo[iDevIndex].lLoginID;
		lChanNum = g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;
	}
	NET_DVR_MOTION_TRACK_CFG strMotionTtackCfg = {0};
	memset(&strMotionTtackCfg, 0, sizeof(strMotionTtackCfg));
	strMotionTtackCfg.dwSize = sizeof(strMotionTtackCfg);
	strMotionTtackCfg.byEnableTrack = m_bChkTrack;
	
	if (NET_DVR_SetDVRConfig(lLoginID, NET_DVR_SET_MOTION_TRACK_CFG, 1, &strMotionTtackCfg, sizeof(strMotionTtackCfg)))
	{
		g_pMainDlg->AddLog(iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MOTION_TRACK_CFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MOTION_TRACK_CFG");
		return;
	}
}
*/

void CDlgOutputCtrl::OnChkPtzManualtrace() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	g_bPtzMaualTrace = m_bChkPtzManualTrace;
	g_iTrackType = m_comboTrackType.GetCurSel();
}

void CDlgOutputCtrl::OnEditchangeComboTracktype() 
{
	// TODO: Add your control notification handler code here
	g_iTrackType = m_comboTrackType.GetCurSel();
	if (g_iTrackType < 0)
	{
		g_iTrackType = 0;
	}
}

void CDlgOutputCtrl::OnBtnCruiseDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	m_iCruiseRoute = m_comboCruise.GetCurSel()+1;//start with 1 
	
	PTZCruiseAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex,\
			iChanIndex, DEL_SEQ, BYTE(m_iCruiseRoute), 0, 0, "DEL_SEQ");	
}

