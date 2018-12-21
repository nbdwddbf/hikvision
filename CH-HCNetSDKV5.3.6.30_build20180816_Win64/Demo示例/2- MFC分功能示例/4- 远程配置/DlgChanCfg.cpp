// DlgChanCfg.cpp : implementation file
//
/**********************************************************
FileName:    DlgChanCfg.cpp
Description: 通道信息配置      
Date:        
Note: 		<全局>结构体,宏见GeneralDef.h, 全局变量,函数见config.cpp   
Modification History:      
<version>   <time>         <desc>

***********************************************************/

#include "stdafx.h"
#include "config.h"
#include "DlgChanCfg.h"
#include "DlgRemoteShowString.h"
#include "DlgRemoteHideArea.h"
#include "DlgRemoteHideAlarm.h"
#include "DlgRemoteRecordSchedule.h"
#include "DlgRemoteMotionDetect.h"
#include "DlgRemoteVideoInLost.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern LPNET_DVR_HIDEALARM_V30 g_lpHideAlarm;//告警遮挡区域

/////////////////////////////////////////////////////////////////////////////
// CDlgChanCfg dialog


CDlgChanCfg::CDlgChanCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChanCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChanCfg)
	m_iFrame_I_Iterval = 0;
	m_bCheckRecord = FALSE;
	m_dwDurationTime = 0;
	m_bCheckOsd = FALSE;
	m_iOsdX = 0;
	m_iOsdY = 0;
	m_bChkDispWeek = FALSE;
	m_bCheckChanName = FALSE;
	m_iChanNameX = 0;
	m_iChanNameY = 0;
	m_bCheckHideArea = FALSE;
	m_bCheckMotion = FALSE;
	m_bCheckHideAlarm = FALSE;
	m_bCheckVILost = FALSE;
	m_iBitRate = 0;
	m_csChannelName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgChanCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChanCfg)
	DDX_Control(pDX, IDC_COMBO_COPY_CHAN, m_comboCopyChan);
	DDX_Control(pDX, IDC_COMBO_HOUR_TYPE, m_comboHourType);
	DDX_Control(pDX, IDC_COMBO_OSD_TYPE, m_comboOsdType);
	DDX_Control(pDX, IDC_COMBO_OSD_ATTRIB, m_comboOsdAttrib);
	DDX_Control(pDX, IDC_COMBO_REC_DELAY, m_comboRecordDelay);
	DDX_Control(pDX, IDC_COMBO_PRERECORD_TIME, m_comboPrerecordTime);
	DDX_Control(pDX, IDC_COMBO_COMPRESSION_TYPE, m_comboCompressionType);
	DDX_Control(pDX, IDC_COMBO_CHAN, m_comboChanNum);
	DDX_Control(pDX, IDC_COMBO_FRAME_BP_INTERVAL, m_comboFrameBPInterval);
	DDX_Control(pDX, IDC_COMBO_MAX_BIT_RATE, m_comboMaxBitRate);
	DDX_Control(pDX, IDC_COMBO_FRAME_RATE, m_comboFrameRate);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
	DDX_Control(pDX, IDC_COMBO_BIT_RATE_TYPE, m_comboBitRateType);
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_COMBO_IMAGE_QUALITY, m_comboImageQuality);
	DDX_Text(pDX, IDC_EDIT_FRAME_I_INTERVAL, m_iFrame_I_Iterval);
	DDX_Check(pDX, IDC_CHK_RECORD, m_bCheckRecord);
	DDX_Text(pDX, IDC_EDIT_DURATION_TIME, m_dwDurationTime);
	DDX_Check(pDX, IDC_CHK_OSD, m_bCheckOsd);
	DDX_Text(pDX, IDC_EDIT_OSD_X, m_iOsdX);
	DDX_Text(pDX, IDC_EDIT_OSD_Y, m_iOsdY);
	DDX_Check(pDX, IDC_CHK_DISPLAY_WEEK, m_bChkDispWeek);
	DDX_Check(pDX, IDC_CHK_CHAN_NAME, m_bCheckChanName);
	DDX_Text(pDX, IDC_EDIT_CHAN_NAME_X, m_iChanNameX);
	DDX_Text(pDX, IDC_EDIT_CHAN_NAME_Y, m_iChanNameY);
	DDX_Check(pDX, IDC_CHK_HIDE_AREA, m_bCheckHideArea);
	DDX_Check(pDX, IDC_CHK_MOTION, m_bCheckMotion);
	DDX_Check(pDX, IDC_CHK_HIDE_ALARM, m_bCheckHideAlarm);
	DDX_Check(pDX, IDC_CHK_VILOST, m_bCheckVILost);
	DDX_Text(pDX, IDC_EDIT_BIT_RATE, m_iBitRate);
	DDX_Text(pDX, IDC_EDIT_CHANNEL_NAME, m_csChannelName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChanCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgChanCfg)
	ON_BN_CLICKED(IDC_CHK_HIDE_AREA, OnBnClickedChkHideArea)
	ON_BN_CLICKED(IDC_CHK_RECORD, OnBnClickedChkRecord)
	ON_BN_CLICKED(IDC_CHK_MOTION, OnBnClickedChkMotion)
	ON_BN_CLICKED(IDC_CHK_VILOST, OnBnClickedChkVilost)
	ON_BN_CLICKED(IDC_CHK_HIDE_ALARM, OnBnClickedChkHideAlarm)
	ON_BN_CLICKED(IDC_CHK_OSD, OnBnClickedChkOsd)
	ON_BN_CLICKED(IDC_CHK_CHAN_NAME, OnBnClickedChkChanNamePos)
	ON_BN_CLICKED(IDC_BTN_CMP_OK, OnButtonSetCompressionCfg)
	ON_BN_CLICKED(IDC_BTN_RECORD_OK, OnButtonSetRecordCfg)
	ON_BN_CLICKED(IDC_BTN_PIC_OK, OnButtonSetPictureCfg)
	ON_BN_CLICKED(IDC_BTN_STRING, OnBnClickedBtnString)
	ON_BN_CLICKED(IDC_BTN_HIDE_SETUP, OnBnClickedBtnHideSetup)
	ON_BN_CLICKED(IDC_BTN_HIDE_ALARM_SETUP, OnBnClickedBtnHideAlarmSetup)
	ON_BN_CLICKED(IDC_BTN_REMOTE_RECORD_SETUP, OnBnClickedBtnRemoteRecordSetup)
	ON_BN_CLICKED(IDC_BTN_MOTION_SETUP, OnBnClickedBtnMotionSetup)
	ON_BN_CLICKED(IDC_BTN_VILOST_SETUP, OnBnClickedBtnVilostSetup)
	ON_CBN_SELCHANGE(IDC_COMBO_CHAN, OnCbnSelchangeComboChan)
	ON_CBN_SELCHANGE(IDC_COMBO_MAX_BIT_RATE, OnCbnSelchangeComboMaxBitRate)
	ON_BN_CLICKED(IDC_BTN_ChanCfg_OK, OnBnClickedChanCfgOK)
	ON_BN_CLICKED(IDC_BTN_CHAN_COPY, OnBnClickedChanCfgCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChanCfg message handlers
/*********************************************************
  Function:	CurCfgUpdate
  Desc:		读取所有通道的压缩、录像、图像参数配置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChanCfg::CurCfgUpdate()
{
	
	if (g_lUserID < 0)
	{
		return;
	}
	
	int i;
	DWORD dwReturned = 0;
	int iChanShow = 0;
	int iCopyIndex = 0;
	m_lStartChannel = g_struDeviceInfo[0].iStartChan;//设备的起始通道，一般从1开始。
	int m_iChanCount = g_struDeviceInfo[0].iDeviceChanNum;//设备的模拟通道数。

	m_comboChanNum.ResetContent();//登陆不同设备时，删除combobox里面的上一轮的记录。不可或缺。
	m_comboCopyChan.ResetContent();//登陆不同设备时，删除combobox里面的上一轮的记录。

	m_comboCopyChan.AddString("全部通道");
	m_comboCopyChan.SetItemData(iCopyIndex, -1);


	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		iChanShow = i+g_struDeviceInfo[0].iStartChan;
		CString sTemp;
		CString sTempIP;
		
		sTemp.Format("%s%d", "通道", iChanShow);
		sTempIP.Format("%s%d", "IP通道", iChanShow-MAX_ANALOG_CHANNUM);//ip通道号要减去32才能从1开始。
    
    
		
		//通道是否使能
		if (g_struDeviceInfo[0].struChanInfo[i].bEnable)
		{
			//模拟通道
			if (i<m_iChanCount)
			{
				m_comboChanNum.AddString(sTemp);
				m_comboChanNum.SetItemData(iCopyIndex, i);
				
				iCopyIndex++;
				m_comboCopyChan.AddString(sTemp);
				m_comboCopyChan.SetItemData(iCopyIndex, i);

				memset(&m_struCompressionCfg[i], 0, sizeof(m_struCompressionCfg[i]));
				if (!NET_DVR_GetDVRConfig(g_lUserID, NET_DVR_GET_COMPRESSCFG_V30, iChanShow, &m_struCompressionCfg[i], sizeof(NET_DVR_COMPRESSIONCFG_V30), &dwReturned))
				{
					AfxMessageBox("获得压缩参数失败！");	
				}
				memset(&m_struRecordCfg[i], 0, sizeof(m_struRecordCfg[i]));
				if (!NET_DVR_GetDVRConfig(g_lUserID, NET_DVR_GET_RECORDCFG_V30, iChanShow,&m_struRecordCfg[i], sizeof(NET_DVR_RECORD_V30), &dwReturned))
				{
					MessageBox("获得录像参数失败","warning");
				}
				memset(&m_struPicCfg[i], 0, sizeof(m_struPicCfg[i]));
				if (!NET_DVR_GetDVRConfig(g_lUserID, NET_DVR_GET_PICCFG_V30, iChanShow,&m_struPicCfg[i], sizeof(NET_DVR_PICCFG_V30), &dwReturned))
				{
					MessageBox("获得图像参数失败","warning");
				}
				
				
				//直接将第一个使能通道（一般是通道1）的设置先显示出来，再进行for循环。否则从注册到显示出来会感觉有一段时间的延时。
				if(i==g_struDeviceInfo[0].lFirstEnableChanIndex)//从第一个使能通道开始先显示。
				{
					//**压缩部分的参数**//
					m_comboImageQuality.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.byPicQuality);
					m_comboResolution.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.byResolution);
					m_comboStreamType.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.byStreamType);
					m_comboBitRateType.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.byBitrateType);
					m_comboFrameRate.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.dwVideoFrameRate);
					if ((m_struCompressionCfg[i].struNormHighRecordPara.dwVideoBitrate >> 31) && 0x01)
					{
						GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
						m_comboMaxBitRate.SetCurSel(22);		//自定义码流
						m_iBitRate = (m_struCompressionCfg[i].struNormHighRecordPara.dwVideoBitrate & 0x7fffffff)/1024;
					}
					else
					{
						m_comboMaxBitRate.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.dwVideoBitrate-2);			
						m_iBitRate = 0;
						GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
					}
					m_comboFrameBPInterval.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.byIntervalBPFrame);
					m_comboChanNum.SetCurSel(0);//不管前面有几个通道被禁掉，但是这里总是从没禁掉的通道开始加入到combobox的，所以肯定是从0开始。也就是从第一个没被禁掉的通道开始。
					m_comboCopyChan.SetCurSel(0);
					m_comboCompressionType.SetCurSel(0);
					GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
					m_iFrame_I_Iterval=m_struCompressionCfg[i].struNormHighRecordPara.wIntervalFrameI;
					
					//**录像部分的参数**//
					m_bCheckRecord = m_struRecordCfg[i].dwRecord;
					m_comboPrerecordTime.SetCurSel(m_struRecordCfg[i].dwPreRecordTime);
					m_comboRecordDelay.SetCurSel(m_struRecordCfg[i].dwRecordTime);
					
					//下面几句是判断定时录像是否打开，是否可以进行远程录像计划的配置。
					if (m_bCheckRecord)
					{
						GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO_PRERECORD_TIME)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO_REC_DELAY)->EnableWindow(TRUE);
					}
					else
					{
						GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(FALSE);
						GetDlgItem(IDC_COMBO_PRERECORD_TIME)->EnableWindow(FALSE);
						GetDlgItem(IDC_COMBO_REC_DELAY)->EnableWindow(FALSE);
					}
					
					//**图像部分的参数**//
					m_csChannelName=m_struPicCfg[i].sChanName;
					

					m_bCheckOsd=m_struPicCfg[i].dwShowOsd;
					GetDlgItem(IDC_EDIT_OSD_X)->EnableWindow(m_bCheckOsd);
					GetDlgItem(IDC_EDIT_OSD_Y)->EnableWindow(m_bCheckOsd);
					GetDlgItem(IDC_COMBO_OSD_ATTRIB)->EnableWindow(m_bCheckOsd);
					GetDlgItem(IDC_COMBO_OSD_TYPE)->EnableWindow(m_bCheckOsd);
					GetDlgItem(IDC_CHK_DISPLAY_WEEK)->EnableWindow(m_bCheckOsd);
					m_comboOsdType.SetCurSel(m_struPicCfg[i].byOSDType);
					m_comboOsdAttrib.SetCurSel(m_struPicCfg[i].byOSDAttrib-1);//这里之所以要减1，是因为本来的0对应的OSD属性：0－不显示OSD；1－透明,闪烁等，不显示OSD被单独提取出来做check控件了。所以少了一项下标为0的项目。
					m_bChkDispWeek=m_struPicCfg[i].byDispWeek;
					m_iOsdX=m_struPicCfg[i].wOSDTopLeftX;
					m_iOsdY=m_struPicCfg[i].wOSDTopLeftY;
					m_comboHourType.SetCurSel(m_struPicCfg[i].byHourOSDType);
					
					m_bCheckChanName=m_struPicCfg[i].dwShowChanName;
					GetDlgItem(IDC_EDIT_CHAN_NAME_X)->EnableWindow(m_bCheckChanName);
					GetDlgItem(IDC_EDIT_CHAN_NAME_Y)->EnableWindow(m_bCheckChanName);
					m_iChanNameX=m_struPicCfg[i].wShowNameTopLeftX;
					m_iChanNameY=m_struPicCfg[i].wShowNameTopLeftY;
					
					m_bCheckHideArea=m_struPicCfg[i].dwEnableHide;//判断是否打开遮盖功能，使“遮盖”按钮使能。
					GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(m_bCheckHideArea);
					
					m_bCheckMotion = m_struPicCfg[i].struMotion.byEnableHandleMotion;
					GetDlgItem(IDC_BTN_MOTION_SETUP)->EnableWindow(m_bCheckMotion);
					
					m_bCheckVILost=m_struPicCfg[i].struVILost.byEnableHandleVILost;
					GetDlgItem(IDC_BTN_VILOST_SETUP)->EnableWindow(m_bCheckVILost);
					
					if (m_struPicCfg[i].struHideAlarm.dwEnableHideAlarm > 0)//这里要对是否遮盖报警的参数进行判断，因为它的值可能取0，1，2，3，如果超过1，复选框将无法打上勾。
					{
						m_bCheckHideAlarm = TRUE;
					}
					else
					{
						m_bCheckHideAlarm = FALSE;
					}
					//m_bCheckHideAlarm=m_struPicCfg[i].struHideAlarm.dwEnableHideAlarm;如果不做上面的判断，按这句写的话，会出现复选框没打钩的情况。
	                GetDlgItem(IDC_BTN_HIDE_ALARM_SETUP)->EnableWindow(m_bCheckHideAlarm);

					
					UpdateData(FALSE);
				}
			}
			//考虑9000设备的ip通道
			else if (i >= MAX_ANALOG_CHANNUM)
			{
				m_comboChanNum.AddString(sTempIP);
				m_comboChanNum.SetItemData(iCopyIndex, i);
				
				iCopyIndex++;
				m_comboCopyChan.AddString(sTempIP);
				m_comboCopyChan.SetItemData(iCopyIndex, i);

				memset(&m_struCompressionCfg[i], 0, sizeof(m_struCompressionCfg[i]));
				if (!NET_DVR_GetDVRConfig(g_lUserID, NET_DVR_GET_COMPRESSCFG_V30, iChanShow, &m_struCompressionCfg[i], sizeof(NET_DVR_COMPRESSIONCFG_V30), &dwReturned))
				{
					AfxMessageBox("获得压缩参数失败！");	
				}
				memset(&m_struRecordCfg[i], 0, sizeof(m_struRecordCfg[i]));
				if (!NET_DVR_GetDVRConfig(g_lUserID, NET_DVR_GET_RECORDCFG_V30, iChanShow,&m_struRecordCfg[i], sizeof(NET_DVR_RECORD_V30), &dwReturned))
				{
					MessageBox("获得录像参数失败","warning");
				}
				memset(&m_struPicCfg[i], 0, sizeof(m_struPicCfg[i]));
				if (!NET_DVR_GetDVRConfig(g_lUserID, NET_DVR_GET_PICCFG_V30, iChanShow,&m_struPicCfg[i], sizeof(NET_DVR_PICCFG_V30), &dwReturned))
				{
					MessageBox("获得图像参数失败","warning");
				}
				
				
				//直接将第一个使能通道（一般是通道1）的设置先显示出来，再进行for循环。否则从注册到显示出来会感觉有一段时间的延时。
				if(i==g_struDeviceInfo[0].lFirstEnableChanIndex)//从第一个使能通道开始先显示。
				{
					//**压缩部分的参数**//
					m_comboImageQuality.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.byPicQuality);
					m_comboResolution.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.byResolution);
					m_comboStreamType.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.byStreamType);
					m_comboBitRateType.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.byBitrateType);
					m_comboFrameRate.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.dwVideoFrameRate);
					if ((m_struCompressionCfg[i].struNormHighRecordPara.dwVideoBitrate >> 31) && 0x01)
					{
						GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
						m_comboMaxBitRate.SetCurSel(22);		//自定义码流
						m_iBitRate = (m_struCompressionCfg[i].struNormHighRecordPara.dwVideoBitrate & 0x7fffffff)/1024;
					}
					else
					{
						m_comboMaxBitRate.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.dwVideoBitrate-2);			
						m_iBitRate = 0;
						GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
					}
					m_comboFrameBPInterval.SetCurSel(m_struCompressionCfg[i].struNormHighRecordPara.byIntervalBPFrame);
					m_comboChanNum.SetCurSel(0);//不管前面有几个通道被禁掉，但是这里总是从没禁掉的通道开始加入到combobox的，所以肯定是从0开始。也就是从第一个没被禁掉的通道开始。
					m_comboCopyChan.SetCurSel(0);
					m_comboCompressionType.SetCurSel(0);
					GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
					m_iFrame_I_Iterval=m_struCompressionCfg[i].struNormHighRecordPara.wIntervalFrameI;
					
					//**录像部分的参数**//
					m_bCheckRecord = m_struRecordCfg[i].dwRecord;
					m_comboPrerecordTime.SetCurSel(m_struRecordCfg[i].dwPreRecordTime);
					m_comboRecordDelay.SetCurSel(m_struRecordCfg[i].dwRecordTime);
					
					//下面几句是判断定时录像是否打开，是否可以进行远程录像计划的配置。
					if (m_bCheckRecord)
					{
						GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO_PRERECORD_TIME)->EnableWindow(TRUE);
						GetDlgItem(IDC_COMBO_REC_DELAY)->EnableWindow(TRUE);
					}
					else
					{
						GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(FALSE);
						GetDlgItem(IDC_COMBO_PRERECORD_TIME)->EnableWindow(FALSE);
						GetDlgItem(IDC_COMBO_REC_DELAY)->EnableWindow(FALSE);
					}
					
					//**图像部分的参数**//
					GetDlgItem(IDC_BTN_STRING)->EnableWindow(FALSE);//通道数超过32，NET_DVR_SHOWSTRING_V30的获得配置GET函数会出错。
					m_csChannelName=m_struPicCfg[i].sChanName;
					m_bCheckOsd=m_struPicCfg[i].dwShowOsd;
					GetDlgItem(IDC_EDIT_OSD_X)->EnableWindow(m_bCheckOsd);
					GetDlgItem(IDC_EDIT_OSD_Y)->EnableWindow(m_bCheckOsd);
					GetDlgItem(IDC_COMBO_OSD_ATTRIB)->EnableWindow(m_bCheckOsd);
					GetDlgItem(IDC_COMBO_OSD_TYPE)->EnableWindow(m_bCheckOsd);
					GetDlgItem(IDC_CHK_DISPLAY_WEEK)->EnableWindow(m_bCheckOsd);
					m_comboOsdType.SetCurSel(m_struPicCfg[i].byOSDType);
					m_comboOsdAttrib.SetCurSel(m_struPicCfg[i].byOSDAttrib-1);//这里之所以要减1，是因为本来的0对应的OSD属性：0－不显示OSD；1－透明,闪烁等，不显示OSD被单独提取出来做check控件了。所以少了一项下标为0的项目。
					m_bChkDispWeek=m_struPicCfg[i].byDispWeek;
					m_iOsdX=m_struPicCfg[i].wOSDTopLeftX;
					m_iOsdY=m_struPicCfg[i].wOSDTopLeftY;
					m_comboHourType.SetCurSel(m_struPicCfg[i].byHourOSDType);
					
					m_bCheckChanName=m_struPicCfg[i].dwShowChanName;
					GetDlgItem(IDC_EDIT_CHAN_NAME_X)->EnableWindow(m_bCheckChanName);
					GetDlgItem(IDC_EDIT_CHAN_NAME_Y)->EnableWindow(m_bCheckChanName);
					m_iChanNameX=m_struPicCfg[i].wShowNameTopLeftX;
					m_iChanNameY=m_struPicCfg[i].wShowNameTopLeftY;
					
					m_bCheckHideArea=m_struPicCfg[i].dwEnableHide;//判断是否打开遮盖功能，使“遮盖”按钮使能。
					GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(m_bCheckHideArea);
					
					m_bCheckMotion = m_struPicCfg[i].struMotion.byEnableHandleMotion;
					GetDlgItem(IDC_BTN_MOTION_SETUP)->EnableWindow(m_bCheckMotion);
					
					m_bCheckVILost=m_struPicCfg[i].struVILost.byEnableHandleVILost;
					GetDlgItem(IDC_BTN_VILOST_SETUP)->EnableWindow(m_bCheckVILost);
					
					if (m_struPicCfg[i].struHideAlarm.dwEnableHideAlarm > 0)//这里要对是否遮盖报警的参数进行判断，因为它的值可能取0，1，2，3，如果超过1，复选框将无法打上勾。
					{
						m_bCheckHideAlarm = TRUE;
					}
					else
					{
						m_bCheckHideAlarm = FALSE;
					}
					//m_bCheckHideAlarm=m_struPicCfg[i].struHideAlarm.dwEnableHideAlarm;如果不做上面的判断，按这句写的话，会出现复选框没打钩的情况。
	                GetDlgItem(IDC_BTN_HIDE_ALARM_SETUP)->EnableWindow(m_bCheckHideAlarm);

					
					UpdateData(FALSE);
				}
            
			}
		}
	}
}

/*********************************************************
Function:	OnBnClickedChkHideArea
Desc:		是否进行遮盖区域的设置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedChkHideArea() 
{
	UpdateData(TRUE);
	if (m_bCheckHideArea)
	{
		GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(FALSE);
	}	
}

/*********************************************************
Function:	OnBnClickedChkRecord
Desc:		是否进行远程录像计划的配置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedChkRecord() 
{
	UpdateData(TRUE);
	if (m_bCheckRecord)
	{
		GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PRERECORD_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_REC_DELAY)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PRERECORD_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_REC_DELAY)->EnableWindow(FALSE);
	}	
}

/*********************************************************
Function:	OnBnClickedChkMotion
Desc:		是否进行移动侦测配置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedChkMotion() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_MOTION_SETUP)->EnableWindow(m_bCheckMotion);	
}

/*********************************************************
Function:	OnBnClickedChkVilost
Desc:		是否进行视频丢失告警的布防配置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedChkVilost() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_VILOST_SETUP)->EnableWindow(m_bCheckVILost);	
}

/*********************************************************
Function:	OnBnClickedChkHideAlarm
Desc:		是否进行遮挡告警配置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedChkHideAlarm() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_HIDE_ALARM_SETUP)->EnableWindow(m_bCheckHideAlarm);	
}

/*********************************************************
Function:	OnBnClickedChkOsd
Desc:		是否进行osd的设置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedChkOsd() 
{
	UpdateData(TRUE);
    if (m_bCheckOsd)
    {
		GetDlgItem(IDC_EDIT_OSD_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_OSD_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_OSD_ATTRIB)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_OSD_TYPE)->EnableWindow(TRUE);
	    GetDlgItem(IDC_CHK_DISPLAY_WEEK)->EnableWindow(TRUE);
		//GetDlgItem(IDC_COMBO_HOUR_TYPE)->EnableWindow(TRUE);//12小时制好像在客户端和demo上都还没实现。
	} 
    else
    {
		GetDlgItem(IDC_EDIT_OSD_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OSD_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_OSD_ATTRIB)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_OSD_TYPE)->EnableWindow(FALSE);
	    GetDlgItem(IDC_CHK_DISPLAY_WEEK)->EnableWindow(FALSE);
		//GetDlgItem(IDC_COMBO_HOUR_TYPE)->EnableWindow(FALSE);
    }	
}

/*********************************************************
Function:	OnBnClickedChkChanNamePos
Desc:		是否设置通道名称的位置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedChkChanNamePos() 
{
	UpdateData(TRUE);
	if (m_bCheckChanName)
	{
		GetDlgItem(IDC_EDIT_CHAN_NAME_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CHAN_NAME_Y)->EnableWindow(TRUE);
	} 
	else
	{
		GetDlgItem(IDC_EDIT_CHAN_NAME_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CHAN_NAME_Y)->EnableWindow(FALSE);
	}
}

/*********************************************************
Function:	OnButtonSetCompressionCfg
Desc:		设置压缩参数信息
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnButtonSetCompressionCfg() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}

	UpdateData(TRUE);
	int iSel = m_comboChanNum.GetCurSel();
	int m_iCurChanIndex = m_comboChanNum.GetItemData(iSel);

	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byPicQuality=m_comboImageQuality.GetCurSel();
	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byStreamType=m_comboStreamType.GetCurSel();
	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution=m_comboResolution.GetCurSel();
	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byBitrateType=m_comboBitRateType.GetCurSel();
	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoFrameRate=m_comboFrameRate.GetCurSel();
    
	DWORD dwDefBitRate = 0;
	if (m_comboMaxBitRate.GetCurSel() == 22)	//自定义码流
	{
		dwDefBitRate = m_iBitRate*1024;		
		if (dwDefBitRate < 32*1024)
		{
			dwDefBitRate = 32*1024;
		}
		if (dwDefBitRate > 8192*1024)
		{
			dwDefBitRate =  8192*1024;
		}
		dwDefBitRate |= 0x80000000;
		m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoBitrate = dwDefBitRate;
	}
	else
	{
		m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoBitrate = m_comboMaxBitRate.GetCurSel()+2;
	}

	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byIntervalBPFrame=m_comboFrameBPInterval.GetCurSel();
	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.wIntervalFrameI=m_iFrame_I_Iterval;
	
	if (!NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_COMPRESSCFG_V30, m_iCurChanIndex+1,&m_struCompressionCfg[m_iCurChanIndex], sizeof(NET_DVR_COMPRESSIONCFG_V30)))
	{
		MessageBox("设置压缩参数失败!","warning");
	}
// 	else
// 	{
// 		MessageBox("设置压缩参数成功!","warning");
// 	}
	
}

/*********************************************************
Function:	OnButtonSetRecordCfg
Desc:		设置录像参数信息
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnButtonSetRecordCfg() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}

	UpdateData(TRUE);
	int iSel = m_comboChanNum.GetCurSel();
	int m_iCurChanIndex = m_comboChanNum.GetItemData(iSel);

	m_struRecordCfg[m_iCurChanIndex].dwRecord = m_bCheckRecord;
	m_struRecordCfg[m_iCurChanIndex].dwPreRecordTime=m_comboPrerecordTime.GetCurSel();
	m_struRecordCfg[m_iCurChanIndex].dwRecordTime=m_comboRecordDelay.GetCurSel();
	if (!NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_RECORDCFG_V30, m_iCurChanIndex+1,&m_struRecordCfg[m_iCurChanIndex], sizeof(NET_DVR_RECORD_V30)))
	{

		MessageBox("设置录像参数失败!","warning");
	}
// 	else
// 	{
// 		MessageBox("设置录像参数成功!","warning");
// 	}	
}

/*********************************************************
Function:	OnButtonSetPictureCfg
Desc:		设置图像参数信息
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnButtonSetPictureCfg() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	UpdateData(TRUE);
	int iSel = m_comboChanNum.GetCurSel();
	int m_iCurChanIndex = m_comboChanNum.GetItemData(iSel);

    //本页面的通道名的获取与设置，都是在图像参数结构体中。
    memcpy(m_struPicCfg[m_iCurChanIndex].sChanName,m_csChannelName,NAME_LEN);

	m_struPicCfg[m_iCurChanIndex].dwEnableHide=m_bCheckHideArea;
	m_struPicCfg[m_iCurChanIndex].struMotion.byEnableHandleMotion=m_bCheckMotion;
	m_struPicCfg[m_iCurChanIndex].struVILost.byEnableHandleVILost=m_bCheckVILost;
	if (!m_bCheckHideAlarm)//如果没选上“遮挡报警”，即m_bCheckHideAlarm等0，则使dwEnableHideAlarm等于0，否则dwEnableHideAlarm代表遮挡灵敏度，不一定等于1，还有可能是2、3。
	{
		m_struPicCfg[m_iCurChanIndex].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
	}


	m_struPicCfg[m_iCurChanIndex].dwShowOsd=m_bCheckOsd;
	m_struPicCfg[m_iCurChanIndex].byOSDType=m_comboOsdType.GetCurSel();
	m_struPicCfg[m_iCurChanIndex].byOSDAttrib=m_comboOsdAttrib.GetCurSel()+1;//这里之所以要加1，是因为本来的0对应的OSD属性：0－不显示OSD；1－透明,闪烁等，不显示OSD被单独提取出来做check控件了。所以少了一项下标为0的项目。
	m_struPicCfg[m_iCurChanIndex].byDispWeek=m_bChkDispWeek;
	m_struPicCfg[m_iCurChanIndex].wOSDTopLeftX=m_iOsdX;
	m_struPicCfg[m_iCurChanIndex].wOSDTopLeftY=m_iOsdY;
	m_struPicCfg[m_iCurChanIndex].byHourOSDType=m_comboHourType.GetCurSel();
	m_struPicCfg[m_iCurChanIndex].dwShowChanName=m_bCheckChanName;
	m_struPicCfg[m_iCurChanIndex].wShowNameTopLeftX=m_iChanNameX;
	m_struPicCfg[m_iCurChanIndex].wShowNameTopLeftY=m_iChanNameY;
	if (!NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_PICCFG_V30, m_iCurChanIndex+1,&m_struPicCfg[m_iCurChanIndex], sizeof(NET_DVR_PICCFG_V30)))
	{
		MessageBox("设置图像参数失败!","warning");
	}
// 	else
// 	{
// 		MessageBox("设置图像参数成功!","warning");
// 	}
	
}

/*********************************************************
  Function:	OnBnClickedBtnString	
  Desc:		进行字符叠加的配置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedBtnString() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	int iSel = m_comboChanNum.GetCurSel();
	int m_iCurChanIndex = m_comboChanNum.GetItemData(iSel);

	CDlgRemoteShowString dlgRemoteShowString;
	
	dlgRemoteShowString.m_lLoginID = g_lUserID;
	dlgRemoteShowString.m_iChanShowNum = m_iCurChanIndex+1;
	dlgRemoteShowString.DoModal();
	
}

/*********************************************************
  Function:	OnBnClickedBtnHideSetup
  Desc:		进行遮盖区域的设置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedBtnHideSetup() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	
	CDlgRemoteHideArea dlg;

	int iSel = m_comboChanNum.GetCurSel();
	int m_iCurChanIndex = m_comboChanNum.GetItemData(iSel);

	int i = 0;
	
	for (i=0; i<MAX_SHELTERNUM; i++)
	{
		memcpy(&(dlg.m_struShelter[i]), &(m_struPicCfg[m_iCurChanIndex].struShelter[i]),sizeof(NET_DVR_SHELTER));
	}
	dlg.m_iChanShowNum = m_iCurChanIndex+1;//播放通道的通道数
	dlg.m_lLoginID = g_lUserID;
	if (dlg.DoModal() == IDOK)
	{
		for (i=0; i<MAX_SHELTERNUM; i++)
		{
			memcpy(&(m_struPicCfg[m_iCurChanIndex].struShelter[i]), &(dlg.m_struShelter[i]),sizeof(NET_DVR_SHELTER));
		}
		//m_bSetChannelPara[m_iCurChanIndex] = TRUE;
	}
    m_struPicCfg[m_iCurChanIndex].dwEnableHide=m_bCheckHideArea;
	NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_PICCFG_V30, m_iCurChanIndex+1,&m_struPicCfg[m_iCurChanIndex], sizeof(NET_DVR_PICCFG_V30));
	
}

/*********************************************************
  Function:	OnBnClickedBtnHideAlarmSetup
  Desc:		进行遮挡告警布防的配置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedBtnHideAlarmSetup() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	
	CDlgRemoteHideAlarm dlgRemoteHideAlarm;

	int iSel = m_comboChanNum.GetCurSel();
	int m_iCurChanIndex = m_comboChanNum.GetItemData(iSel);
	
	g_lpHideAlarm = &(m_struPicCfg[m_iCurChanIndex].struHideAlarm);
	dlgRemoteHideAlarm.m_iChanShowNum = m_iCurChanIndex+1;
	dlgRemoteHideAlarm.m_lLoginID = g_lUserID;
	//dlgRemoteHideAlarm.m_dwAlarmOutNum = g_struDeviceInfo[0].iAlarmOutNum;
	dlgRemoteHideAlarm.m_dwDevIndex = 0;
	if (dlgRemoteHideAlarm.DoModal() == IDOK)
	{
		NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_PICCFG_V30, m_iCurChanIndex+1,&m_struPicCfg[m_iCurChanIndex], sizeof(NET_DVR_PICCFG_V30));
	}
	
}

/*********************************************************
  Function:	OnBnClickedBtnRemoteRecordSetup
  Desc:		进行远程录像计划的配置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedBtnRemoteRecordSetup() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	
	CDlgRemoteRecordSchedule dlg;

	int iSel = m_comboChanNum.GetCurSel();
	int m_iCurChanIndex = m_comboChanNum.GetItemData(iSel);
	
	dlg.m_struRemoteRecSchedule = &(m_struRecordCfg[m_iCurChanIndex]);
	if (dlg.DoModal() == IDOK)
	{
		m_struRecordCfg[m_iCurChanIndex].dwRecord = m_bCheckRecord;
		//在设置录像时间窗口中，设置完后，按“退出”按钮，然后调用函数直接设定录像时间。
		NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_RECORDCFG_V30, m_iCurChanIndex+1,&m_struRecordCfg[m_iCurChanIndex], sizeof(NET_DVR_RECORD_V30));	
	}
	
}

/*********************************************************
Function:	OnBnClickedBtnMotionSetup
Desc:		进行移动侦测布防时间区域等的设置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedBtnMotionSetup() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	
	CDlgRemoteMotionDetect dlgRemoteMotionDetect;

	int iSel = m_comboChanNum.GetCurSel();
	int m_iCurChanIndex = m_comboChanNum.GetItemData(iSel);
	
	g_lpMotionDetect = &(m_struPicCfg[m_iCurChanIndex].struMotion);
	dlgRemoteMotionDetect.m_iChanShowNum = m_iCurChanIndex+1;
	dlgRemoteMotionDetect.m_lLoginID = g_lUserID;
	// 	dlgRemoteMotionDetect.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlgRemoteMotionDetect.m_iChanCount = g_struDeviceInfo[0].iDeviceChanNum;
	dlgRemoteMotionDetect.m_dwDevIndex = 0;
	if (dlgRemoteMotionDetect.DoModal() == IDOK)
	{
		//m_bSetChannelPara[m_iCurChanIndex] = TRUE;
		m_struPicCfg[m_iCurChanIndex].struMotion.byEnableHandleMotion=m_bCheckMotion;
		NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_PICCFG_V30, m_iCurChanIndex+1,&m_struPicCfg[m_iCurChanIndex], sizeof(NET_DVR_PICCFG_V30));
		
	}
 	
}

/*********************************************************
Function:	OnBnClickedBtnVilostSetup
Desc:		进行视频丢失告警布防的配置
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedBtnVilostSetup() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	
	CDlgRemoteVideoInLost dlgRemoteVideoInLost;

	int iSel = m_comboChanNum.GetCurSel();
	int m_iCurChanIndex = m_comboChanNum.GetItemData(iSel);
	
	g_lpVILost = &(m_struPicCfg[m_iCurChanIndex].struVILost);
	dlgRemoteVideoInLost.m_iChanShowNum = m_iCurChanIndex+1;
	dlgRemoteVideoInLost.m_lLoginID = g_lUserID;
	//dlgRemoteVideoInLost.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlgRemoteVideoInLost.m_dwDevIndex = 0;
	if (dlgRemoteVideoInLost.DoModal() == IDOK)
	{
		m_struPicCfg[m_iCurChanIndex].struVILost.byEnableHandleVILost=m_bCheckVILost;
		NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_PICCFG_V30, m_iCurChanIndex+1,&m_struPicCfg[m_iCurChanIndex], sizeof(NET_DVR_PICCFG_V30));
	}	
}

/*********************************************************
Function:	OnCbnSelchangeComboChan
Desc:		通道combobox的通道选择消息响应函数
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnCbnSelchangeComboChan() 
{
	UpdateData(TRUE);
	int iSel = m_comboChanNum.GetCurSel();
	int m_iCurChanIndex = m_comboChanNum.GetItemData(iSel);	

	if (m_iCurChanIndex < MAX_ANALOG_CHANNUM)
	{
		GetDlgItem(IDC_BTN_STRING)->EnableWindow(TRUE);	
	}
	else
	{
		GetDlgItem(IDC_BTN_STRING)->EnableWindow(FALSE);
	}

	//**压缩部分的参数**//
	m_comboImageQuality.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byPicQuality);
	m_comboResolution.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution);
	m_comboStreamType.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byStreamType);
	m_comboBitRateType.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byBitrateType);
	m_comboFrameRate.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoFrameRate);
	if ((m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoBitrate >> 31) && 0x01)
	{
		GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
		m_comboMaxBitRate.SetCurSel(22);		//自定义码流
		m_iBitRate = (m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoBitrate & 0x7fffffff)/1024;
	}
	else
	{
		m_comboMaxBitRate.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoBitrate-2);			
		m_iBitRate = 0;
		GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
	}
	m_comboFrameBPInterval.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byIntervalBPFrame);
	m_comboCopyChan.SetCurSel(0);
	m_comboCompressionType.SetCurSel(0);
	GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
	m_iFrame_I_Iterval=m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.wIntervalFrameI;
	
	//**录像部分的参数**//
	m_bCheckRecord = m_struRecordCfg[m_iCurChanIndex].dwRecord;
	m_comboPrerecordTime.SetCurSel(m_struRecordCfg[m_iCurChanIndex].dwPreRecordTime);
	m_comboRecordDelay.SetCurSel(m_struRecordCfg[m_iCurChanIndex].dwRecordTime);
	
	//下面几句是判断定时录像是否打开，是否可以进行远程录像计划的配置。
	if (m_bCheckRecord)
	{
		GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PRERECORD_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_REC_DELAY)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PRERECORD_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_REC_DELAY)->EnableWindow(FALSE);
	}
	
	//**图像部分的参数**//
	m_csChannelName=m_struPicCfg[m_iCurChanIndex].sChanName;
	m_bCheckOsd=m_struPicCfg[m_iCurChanIndex].dwShowOsd;
	GetDlgItem(IDC_EDIT_OSD_X)->EnableWindow(m_bCheckOsd);
	GetDlgItem(IDC_EDIT_OSD_Y)->EnableWindow(m_bCheckOsd);
	GetDlgItem(IDC_COMBO_OSD_ATTRIB)->EnableWindow(m_bCheckOsd);
	GetDlgItem(IDC_COMBO_OSD_TYPE)->EnableWindow(m_bCheckOsd);
	GetDlgItem(IDC_CHK_DISPLAY_WEEK)->EnableWindow(m_bCheckOsd);
	m_comboOsdType.SetCurSel(m_struPicCfg[m_iCurChanIndex].byOSDType);
	m_comboOsdAttrib.SetCurSel(m_struPicCfg[m_iCurChanIndex].byOSDAttrib-1);//这里之所以要减1，是因为本来的0对应的OSD属性：0－不显示OSD；1－透明,闪烁等，不显示OSD被单独提取出来做check控件了。所以少了一项下标为0的项目。
	m_bChkDispWeek=m_struPicCfg[m_iCurChanIndex].byDispWeek;
	m_iOsdX=m_struPicCfg[m_iCurChanIndex].wOSDTopLeftX;
	m_iOsdY=m_struPicCfg[m_iCurChanIndex].wOSDTopLeftY;
	m_comboHourType.SetCurSel(m_struPicCfg[m_iCurChanIndex].byHourOSDType);
	
	m_bCheckChanName=m_struPicCfg[m_iCurChanIndex].dwShowChanName;
	GetDlgItem(IDC_EDIT_CHAN_NAME_X)->EnableWindow(m_bCheckChanName);
	GetDlgItem(IDC_EDIT_CHAN_NAME_Y)->EnableWindow(m_bCheckChanName);
	m_iChanNameX=m_struPicCfg[m_iCurChanIndex].wShowNameTopLeftX;
	m_iChanNameY=m_struPicCfg[m_iCurChanIndex].wShowNameTopLeftY;
	
	m_bCheckHideArea=m_struPicCfg[m_iCurChanIndex].dwEnableHide;//判断是否打开遮盖功能，使“遮盖”按钮使能。
	GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(m_bCheckHideArea);
	
	m_bCheckMotion = m_struPicCfg[m_iCurChanIndex].struMotion.byEnableHandleMotion;
	GetDlgItem(IDC_BTN_MOTION_SETUP)->EnableWindow(m_bCheckMotion);
	
	m_bCheckVILost=m_struPicCfg[m_iCurChanIndex].struVILost.byEnableHandleVILost;
	GetDlgItem(IDC_BTN_VILOST_SETUP)->EnableWindow(m_bCheckVILost);
	
	if (m_struPicCfg[m_iCurChanIndex].struHideAlarm.dwEnableHideAlarm > 0)//这里要对是否遮盖报警的参数进行判断，因为它的值可能取0，1，2，3，如果超过1，复选框将无法打上勾。
	{
		m_bCheckHideAlarm = TRUE;
	}
	else
	{
		m_bCheckHideAlarm = FALSE;
	}
	//m_bCheckHideAlarm=m_struPicCfg[i].struHideAlarm.dwEnableHideAlarm;如果不做上面的判断，按这句写的话，会出现复选框没打钩的情况。
	GetDlgItem(IDC_BTN_HIDE_ALARM_SETUP)->EnableWindow(m_bCheckHideAlarm);
	
	UpdateData(FALSE);
}

/*********************************************************
Function:	OnCbnSelchangeComboMaxBitRate
Desc:		选中自定义码率
Input:	
Output:	
Return:	
**********************************************************/

void CDlgChanCfg::OnCbnSelchangeComboMaxBitRate() 
{
	UpdateData(TRUE);
	if (m_comboMaxBitRate.GetCurSel() == 22)	//self-define bitrate
	{
		GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
	}
	
}

/*********************************************************
Function:	OnBnClickedChanCfgOK
Desc:		设置通道配置信息
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedChanCfgOK() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	OnButtonSetCompressionCfg();
	OnButtonSetRecordCfg();
	OnButtonSetPictureCfg();
	GetDlgItem(IDC_BTN_CHAN_COPY)->EnableWindow(TRUE);	
}

/*********************************************************
Function:	OnBnClickedChanCfgCopy
Desc:		复制通道配置信息
Input:	
Output:	
Return:	
**********************************************************/
void CDlgChanCfg::OnBnClickedChanCfgCopy() 
{
	UpdateData(TRUE);
	int i = 0,j = 0,k = 0;
	int m_iChanNum = g_struDeviceInfo[0].iDeviceChanNum;//获取设备的模拟通道数
	int m_iCurChanIndex = m_comboChanNum.GetItemData(m_comboChanNum.GetCurSel());
	int m_iCopyChanIndex = m_comboCopyChan.GetItemData(m_comboCopyChan.GetCurSel());
	if (m_iCopyChanIndex == m_iCurChanIndex)
	{
		AfxMessageBox("通道相同，不用复制！");
		return;
	}
	if (m_iCopyChanIndex == -1)//复制到全部通道
	{
		for ( i=0; i<m_iChanNum/*MAX_CHANNUM_V30*/; i++)//目前只复制到模拟通道，复制到ip通道会有些问题。
		{
			//压缩参数类型
			m_struCompressionCfg[i].struNormHighRecordPara.byStreamType = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byStreamType;
			m_struCompressionCfg[i].struNormHighRecordPara.byPicQuality = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byPicQuality;
			m_struCompressionCfg[i].struNormHighRecordPara.dwVideoBitrate = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoBitrate;
			m_struCompressionCfg[i].struNormHighRecordPara.byResolution = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution;
			m_struCompressionCfg[i].struNormHighRecordPara.dwVideoFrameRate = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoFrameRate;
			m_struCompressionCfg[i].struNormHighRecordPara.byBitrateType = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byBitrateType;
			m_struCompressionCfg[i].struNormHighRecordPara.byIntervalBPFrame = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byIntervalBPFrame;	
			m_struCompressionCfg[i].struNormHighRecordPara.wIntervalFrameI = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.wIntervalFrameI;
            //录像类型
			m_struRecordCfg[i].dwRecord = m_struRecordCfg[m_iCurChanIndex].dwRecord;
			m_struRecordCfg[i].dwRecordTime = m_struRecordCfg[m_iCurChanIndex].dwRecordTime;
			m_struRecordCfg[i].dwPreRecordTime = m_struRecordCfg[m_iCurChanIndex].dwPreRecordTime;
			//m_struRecordCfg[i].dwRecorderDuration = m_struRecordCfg[m_iCurChanIndex].dwRecorderDuration;
			//复制时间表
			for (k=0; k<MAX_DAYS; k++)
			{
				memcpy(&(m_struRecordCfg[i].struRecAllDay[k]), &(m_struRecordCfg[m_iCurChanIndex].struRecAllDay[k]), sizeof(NET_DVR_RECORDDAY));
				for (j=0; j<MAX_TIMESEGMENT_V30; j++)
				{
					memcpy(&m_struRecordCfg[i].struRecordSched[k][j],&m_struRecordCfg[m_iCurChanIndex].struRecordSched[k][j],sizeof(NET_DVR_RECORDSCHED));				
				}
			}
			//图像参数类型
			m_struPicCfg[i].dwEnableHide = m_bCheckHideArea;//这里直接用了页面上面的值，其实和m_struPicCfg[m_iCurChanIndex].dwEnableHide是一致的。下面也一样。
			m_struPicCfg[i].struMotion.byEnableHandleMotion = m_bCheckMotion;
			m_struPicCfg[i].struVILost.byEnableHandleVILost = m_bCheckVILost;
			if (!m_bCheckHideAlarm)
			{
				m_struPicCfg[i].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
			}
			m_struPicCfg[i].dwShowChanName = m_bCheckChanName;
			m_struPicCfg[i].wShowNameTopLeftX = m_iChanNameX;
			m_struPicCfg[i].wShowNameTopLeftY = m_iChanNameY;
			m_struPicCfg[i].dwShowOsd = m_bCheckOsd;
			m_struPicCfg[i].wOSDTopLeftX = m_iOsdX;
			m_struPicCfg[i].wOSDTopLeftY = m_iOsdY;
			m_struPicCfg[i].byDispWeek = m_bChkDispWeek;
			m_struPicCfg[i].byOSDAttrib = m_comboOsdAttrib.GetCurSel()+1;
			m_struPicCfg[i].byOSDType = m_comboOsdType.GetCurSel();
			m_struPicCfg[i].byHourOSDType = m_comboHourType.GetCurSel();

			char szLan[128] = {0};
			int iChanShow = i+m_lStartChannel;
			if (!NET_DVR_SetDVRConfig(g_lUserID,NET_DVR_SET_COMPRESSCFG_V30, iChanShow,&(m_struCompressionCfg[i]), sizeof(NET_DVR_COMPRESSIONCFG_V30)))
			{
				g_StringLanType(szLan, "压缩参数保存失败", "CompressCfg Save failed");
				AfxMessageBox(szLan);
			}
						
			if (!NET_DVR_SetDVRConfig(g_lUserID,NET_DVR_SET_RECORDCFG_V30, iChanShow,&(m_struRecordCfg[i]), sizeof(NET_DVR_RECORD_V30)))	
			{
				g_StringLanType(szLan, "录像参数保存失败", " RecordCfg Save failed");
				AfxMessageBox(szLan);
			}
			if (!NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_PICCFG_V30, iChanShow, &(m_struPicCfg[i]), sizeof(NET_DVR_PICCFG_V30)))
			{
				g_StringLanType(szLan, "图像参数保存失败", "PictureCfg Save failed");
				AfxMessageBox(szLan);
			}
		}
		//AfxMessageBox("复制到所有通道成功!");
	}
	else//复制到单个通道
	{
		//压缩参数类型
		m_struCompressionCfg[m_iCopyChanIndex].struNormHighRecordPara.byStreamType = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byStreamType;
		m_struCompressionCfg[m_iCopyChanIndex].struNormHighRecordPara.byPicQuality = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byPicQuality;
		m_struCompressionCfg[m_iCopyChanIndex].struNormHighRecordPara.dwVideoBitrate = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoBitrate;
		m_struCompressionCfg[m_iCopyChanIndex].struNormHighRecordPara.byResolution = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution;
		m_struCompressionCfg[m_iCopyChanIndex].struNormHighRecordPara.dwVideoFrameRate = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoFrameRate;
		m_struCompressionCfg[m_iCopyChanIndex].struNormHighRecordPara.byBitrateType = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byBitrateType;
		m_struCompressionCfg[m_iCopyChanIndex].struNormHighRecordPara.byIntervalBPFrame = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byIntervalBPFrame;	
		m_struCompressionCfg[m_iCopyChanIndex].struNormHighRecordPara.wIntervalFrameI = m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.wIntervalFrameI;
		//录像类型
		m_struRecordCfg[m_iCopyChanIndex].dwRecord = m_struRecordCfg[m_iCurChanIndex].dwRecord;
		m_struRecordCfg[m_iCopyChanIndex].dwRecordTime = m_struRecordCfg[m_iCurChanIndex].dwRecordTime;
		m_struRecordCfg[m_iCopyChanIndex].dwPreRecordTime = m_struRecordCfg[m_iCurChanIndex].dwPreRecordTime;
		//m_struRecordCfg[m_iCopyChanIndex].dwRecorderDuration = m_struRecordCfg[m_iCurChanIndex].dwRecorderDuration;
		//复制时间表
		for (k=0; k<MAX_DAYS; k++)
		{
			memcpy(&(m_struRecordCfg[m_iCopyChanIndex].struRecAllDay[k]), &(m_struRecordCfg[m_iCurChanIndex].struRecAllDay[k]), sizeof(NET_DVR_RECORDDAY));
			for (j=0; j<MAX_TIMESEGMENT_V30; j++)
			{
				memcpy(&m_struRecordCfg[m_iCopyChanIndex].struRecordSched[k][j],&m_struRecordCfg[m_iCurChanIndex].struRecordSched[k][j],sizeof(NET_DVR_RECORDSCHED));				
			}
		}
		//图像参数类型
		m_struPicCfg[m_iCopyChanIndex].dwEnableHide = m_bCheckHideArea;//这里直接用了页面上面的值，其实和m_struPicCfg[m_iCurChanIndex].dwEnableHide是一致的。下面也一样。
		m_struPicCfg[m_iCopyChanIndex].struMotion.byEnableHandleMotion = m_bCheckMotion;
		m_struPicCfg[m_iCopyChanIndex].struVILost.byEnableHandleVILost = m_bCheckVILost;
		if (!m_bCheckHideAlarm)
		{
			m_struPicCfg[m_iCopyChanIndex].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
		}
		m_struPicCfg[m_iCopyChanIndex].dwShowChanName = m_bCheckChanName;
		m_struPicCfg[m_iCopyChanIndex].wShowNameTopLeftX = m_iChanNameX;
		m_struPicCfg[m_iCopyChanIndex].wShowNameTopLeftY = m_iChanNameY;
		m_struPicCfg[m_iCopyChanIndex].dwShowOsd = m_bCheckOsd;
		m_struPicCfg[m_iCopyChanIndex].wOSDTopLeftX = m_iOsdX;
		m_struPicCfg[m_iCopyChanIndex].wOSDTopLeftY = m_iOsdY;
		m_struPicCfg[m_iCopyChanIndex].byDispWeek = m_bChkDispWeek;
		m_struPicCfg[m_iCopyChanIndex].byOSDAttrib = m_comboOsdAttrib.GetCurSel()+1;
		m_struPicCfg[m_iCopyChanIndex].byOSDType = m_comboOsdType.GetCurSel();
		m_struPicCfg[m_iCopyChanIndex].byHourOSDType = m_comboHourType.GetCurSel();	
		
		char szLan[128] = {0};
		int iChanShow = m_iCopyChanIndex+m_lStartChannel;
		if (!NET_DVR_SetDVRConfig(g_lUserID,NET_DVR_SET_COMPRESSCFG_V30, iChanShow,&(m_struCompressionCfg[m_iCopyChanIndex]), sizeof(NET_DVR_COMPRESSIONCFG_V30)))
		{
			g_StringLanType(szLan, "压缩参数保存失败", "CompressionCfg Save failed");
			AfxMessageBox(szLan);
		}
		
		if (!NET_DVR_SetDVRConfig(g_lUserID,NET_DVR_SET_RECORDCFG_V30, iChanShow,&(m_struRecordCfg[m_iCopyChanIndex]), sizeof(NET_DVR_RECORD_V30)))	
		{
			g_StringLanType(szLan, "录像参数保存失败", " RecordCfg Save failed");
			AfxMessageBox(szLan);
		}
		if (!NET_DVR_SetDVRConfig(g_lUserID, NET_DVR_SET_PICCFG_V30, iChanShow, &(m_struPicCfg[m_iCopyChanIndex]), sizeof(NET_DVR_PICCFG_V30)))
		{
			g_StringLanType(szLan, "图像参数保存失败", "PictureCfg Save failed");
			AfxMessageBox(szLan);
		}
		//AfxMessageBox("复制成功!");
	}
	
}
