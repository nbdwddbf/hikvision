/**********************************************************
FileName:    GeneralDef.h
Description: clientdemo中使用到的通用的宏定义和结构体定义      
Date:        2008/03/27   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/03/27>       <created>
***********************************************************/

#ifndef _GLOBLE_DEF_H_
#define _GLOBLE_DEF_H_

//将sdk库和解码库需要的变量的头文件一起导入
#include "HCNetSDK.h"
#include "DecodeCardSdk.h"
#include "DataType.h"
#include "plaympeg4.h"

#define WM_MYCOMMAND					WM_USER + 1		//for sdk
#define WM_CHANGE_CHANNEL_ITEM_IMAGE	WM_USER + 2     //修改通道结点上的图标
#define WM_CHANGE_DEVICE_ITEM_IMAGE		WM_USER + 3     //修改设备结点上的图标
#define WM_ADD_LOG						WM_USER + 4		//添加日志
#define WM_PROC_ALARM					WM_USER + 5		//报警处理

#define DEMO_FULL_WIDTH 1024	//demo默认的宽度
#define DEMO_FULL_HEIGHT 768	//demo默认的高度
#define OUTPUT_INTERVAL 4		//每个画面的间隔大小
#define LIST_ENLARGE_HIGH 575	//本地日志或告警列表的拉升高度	

#define WIDTH_4CIF			704
#define HEIGHT_4CIF_PAL		576
#define HEIGHT_4CIF_NTSC	480
#define WIDTH_CIF			352
#define HEIGHT_CIF_PAL		288
#define HEIGHT_CIF_NTSC		240
#define PRECISION_4CIF_FRAME	32//4cif分辨率下小方框的边长精度

//m_iMainType mian fuction bar主功能类型,顺序对应上面每个button
#define PREVIEW_T		0
#define CONFIG_ALL_T	1
#define PLAY_BACK_T		2

//config dialog type 
	//remote config type, 顺序对应上面的tab页
#define REMOTE_DEVICE_CFG_T		0	//设备基本信息及网络信息配置界面
#define REMOTE_CHANNEL_CFG_T	1	//通道及智能信息配置界面
#define REMOTE_SEREIAL_CFG_T	2	//串口信息配置界面
#define REMOTE_AlARM_CFG_T		3	//告警输入/输出信息配置界面
#define REMOTE_USER_CFG_T		4	//用户信息配置界面
#define REMOTE_EXCEPTION_CFG_T	5	//异常信息配置界面
#define REMOTE_ATM_INFO_CFG_T	6	//ATM机信息配置界面
#define REMOTE_MAT_DEC_CFG_T	7	//多路解码器配置界面

	//顺序对应后续的配置按钮
#define LOCAL_CFG_T				8
#define LOG_QUERY_T				9
#define DECODE_CARD_CFG_T		10

//回放类型,play back dialog type,顺序对应回放的tab页
#define  PLAY_REMOTE_FILE_T 0
#define  PLAY_LOCAL_FILE_T 1
#define  PLAY_REMOTE_TIME_T 2

//本地日志处理类型
#define ALARM_INFO_T		0	//告警消息
#define OPERATION_SUCC_T	1	//操作成功日志
#define OPERATION_FAIL_T	2	//操作失败日志
#define PLAY_SUCC_T			3	//播放器成功日志
#define PLAY_FAIL_T			4	//播放器失败日志

#define DETECT_AREA_LEFT 10//侦测区域最左坐标
#define DETECT_AREA_TOP 10//侦测区域最上坐标
#define SCREEN_EDGE 30		//侦测区域边框的大小

#define MINSPACE		(200*1024*1024)//硬盘最小空间

//定时器
#define SYSTEM_TIMER			1		//系统相关的参数,时间,cpu等的定时器
#define CYCLE_PREVIEW_TIMER		2		//轮巡相关,定时器
#define	AUTORECORD_TIMER		3		//自动录像时钟
#define	FREESPACE_TIMER			4		//检查硬盘时钟
#define	FILEINTERVAL_TIMER		5		//保存文件时间间隔时钟
#define UPGRADE_TIMER			6		//升级时钟
#define PLAY_TIMER				7		//本地回放时显示播放状态时钟
#define REMOTE_PLAY_STATE_TIMER	8		//远程回放文件播放状态时钟
#define DOWNSTATE_TIMER			9		//下载文件时钟
#define FORMAT_TIMER			10		//远程格式化硬盘
#define EVENTLOG_TIMER			11		//事件日志
#define PLAYBYTIME_TIMER		12		// 按时间回放
#define DOWNBYTIME_TIMER		13		//按时间下载
#define SERIAL_TIMER			14		//串口透明通道发送
#define	CHECK_DEVICE_TIMER		15		//硬盘录像机校时时钟

//画面对应的一些默认参数
#define DEFAULT_BRIGHTNESS	6			//默认亮度
#define DEFAULT_CONTRAST	6			//默认对比度
#define DEFAULT_SATURATION  6			//默认饱和度
#define DEFAULT_HUE			6			//默认色度
#define DEFAULT_VOLUME		50			//默认音量


#define MAX_DEVICES			50	//可监控的最大设备数
#define MAX_OUTPUTS			81	//16最大的窗口数
#define MAX_PREVIEWS		512	//可预览的最大数

//设备区域配置
#define TREE_ALL_T	 0        //代表根节点
#define DEVICETYPE 	 1		  //代表设备
#define CHANNELTYPE	 2	      //代表通道		

/////
//bmp 代表state
//与位图的数据相对应
#define TREE_ALL			 0	//设备树	
#define DEVICE_LOGOUT	     1   //设备已经注销,或未登陆
#define DEVICE_LOGIN	     2   //设备已经登陆
#define DEVICE_FORTIFY	     3   //设备布防
#define DEVICE_ALARM		 4   //设备有告警
#define DEVICE_FORTIFY_ALARM 5	//设备布防且有告警

#define CHAN_ORIGINAL		 6   //不预览,不录像的状态
#define CHAN_PLAY		 	 7   //只在预览
#define CHAN_RECORD			 8   //只在录像
#define CHAN_PLAY_RECORD	 9   //预览且在录像

#define CHAN_ALARM		 	 10   //不预览,不录像,只有告警的状态
#define CHAN_PLAY_ALARM			 11   //预览,不录像,有告警
#define CHAN_PLAY_RECORD_ALARM	 12   //预览且在录像且有告警
#define CHAN_OFF_LINE			 13	 //对应的通道不在线

#define CHAN_AUDIO				 1   //音频通道

//ATM专用,消息输入方式
#define NET_LISTEN				0	//网络侦听;
#define NET_ACCEPT				1	//网络接收;
#define SERIAL_INPUT_DIRECTLY	2	//串口直接输入;
#define SERIAL_ATM_CMD_INPUT	3	//串口ATM命令输入;

//压缩参数类型compression parameter
#define NORM_HIGH_STREAM_COMPRESSION		0//主码流图像压缩参数,压缩能力强,性能可以更高
#define SUB_STREAM_COMPRESSION		1//子码流图像压缩参数
#define EVENT_INVOKE_COMPRESSION	2//事件触发图像压缩参数,一些参数相对固定
#define NORM_LOW_STREAM_COMPRESSION		3//主码流图像压缩参数,压缩能力强,性能可以更高

//串口类型
#define SERIAL_232		1	//232串口
#define SERIAL_485		2	//485串口


#define	ANALOG_CHAN_DISABLE 0
#define	ANALOG_CHAN_ENABLE	1
#define	IP_CHAN_DISABLE		2
#define	IP_CHAN_ENABLE		3

#define ALARM_OUT_FORMAT		("AlarmOut%d")
#define ALARM_IN_NAME			("AlarmIn%d")
#define IP_ALARM_IN_NAME		("IPAlarmIn%d")
#define IP_ALARM_OUT_NAME		("IPAlarmOut%d")
#define ANALOG_C_FORMAT			("Camera%d")
#define IP_CAMERA_NAME			("IPCamera%02d")
#define DIGITAL_C_FORMAT		("IPCamera%d")

//全部播放和轮巡的时候播放设备对应的序列号
typedef struct STRU_PLAY_INFO{

	int		iDeviceIndex;		//对应的设备的数组下标
	int		iChanIndex;			//监控通道号

	STRU_PLAY_INFO()
	{
		iDeviceIndex = -1;
		iChanIndex   = -1;
	}
}PLAY_INFO,*PPLAY_INFO;

//设备通道的信息
typedef struct STRU_CHANNEL_INFO{ 
	int		iDeviceIndex;			//对应的设备的数组下标
	int		iChanIndex;			//监控通道号
	char	chChanName[100];	//本地通道结点名称
	DWORD	dwProtocol;			//网络协议

	int		iPicResolution;				//图片分辨率
	int		iPicQuality;				//图片质量
	LONG	lRealHandle;          //实时预览句柄
	BOOL    bLocalManualRec;     //是否录象;
	BOOL    bAlarm;				//是否有报警;
	BOOL	bEnable;			//是否使能
	DWORD	dwImageType;		//通道状态对应的图片类型
	char	chAccessChanIP[16];//ip接入通道的ip地址

	STRU_CHANNEL_INFO *pNext;
	STRU_CHANNEL_INFO()
	{
		iDeviceIndex		= -1;
		iChanIndex			= -1;
		chChanName[0]		= '\0';
		dwProtocol			= 0;

		iPicResolution		= 0;
		iPicQuality			= 2;

		lRealHandle			= -1; 
		bLocalManualRec		= FALSE;
		bAlarm				= FALSE;
		bEnable				= FALSE;
		dwImageType			= CHAN_ORIGINAL;
		chAccessChanIP[0]	= '\0';	 		  
		pNext				= NULL;
	}
}CHANNEL_INFO,*PCHANNEL_INFO;

//设备信息
typedef struct STRU_DEVICE_INFO{
	int		iDeviceIndex;			//设备数组下标
	LONG	lLoginID;				//注册ID
	DWORD	dwDevSoftVer;			//保留

	char	chLocalNodeName[100];	//本地设备节点名称
	char	chDeviceName[100];		//设备名称
	char	chDeviceIP[33];			//可以直接连接的设备IP,有可能是:设备第一张网卡上设置的IP,pppoe地址,设备所在网关地址
	//char	chDevNetCard1IP[33];	//设备第一张网卡上设置的IP
	char	chLoginUserName[30];	//登陆设备的用户名，在用户管理的时候用到
	char	chLoginPwd[30];	//登陆设备的密码
	char	chDeviceMultiIP[20];	//多播组地址
	//char	chIPServerIP[32];		//IP地址
	char	chSerialNumber[50];		//序列号
	int		iDeviceChanNum;		    //设备的通道数
	int		iStartChan;				//设备开始通道号
	int		iDeviceType;			//设备类型
	int 	iDiskNum;				//硬盘个数
	LONG 	lDevicePort;			//设备主端口号
	int		iAlarmInNum;			//设备告警输入的个数
	int		iAlarmOutNum;			//设备报警输出的个数
	int 	iAudioNum;				//语音对讲个数
	int 	iIPChanNum;				//最大数字通道个数

	BOOL	bCycle;					//该设备是否在循环播放
	BOOL	bPlayDevice;			//该设备是不是所有通道都在播放, add after
	BOOL	bVoiceTalk;				//是否在语音对讲
	LONG    lAudioHandle[MAX_AUDIO_V30]; //语音广播句柄
	BOOL	bCheckBroadcast[MAX_AUDIO_V30]; //是否加入语音广播队列
	LONG	lFortifyHandle;			//布防句柄 
	BOOL    bAlarm;					//是否有报警;
	int	    iDeviceLoginType;		//注册模式  0 - 固定IP   1- IPSERVER 模式    2 -  普通域名 
	DWORD	dwImageType;			//设备状态对应的图片
	BOOL	bIPRet;					//是否支持ip接入
	int		iEnableChanNum;			//有效通道数
	BOOL	bDVRLocalAllRec;		//设备本地全部录像
	LONG	lVoiceCom[MAX_AUDIO_V30];	//语音转发句柄
	LONG	lFirstEnableChanIndex;			//第一个使能通道下标
	LONG	lTranHandle;				//232透明通道句柄

	STRU_CHANNEL_INFO struChanInfo[MAX_CHANNUM_V30]; //通道结构
	NET_DVR_IPPARACFG struIPParaCfg;				//IP接入参数
	NET_DVR_IPALARMINCFG struAlarmInCfg;
	NET_DVR_IPALARMOUTCFG struAlarmOutCfg;
	STRU_DEVICE_INFO *pNext;
	STRU_DEVICE_INFO()
	{						
		iDeviceIndex		= -1;
		lLoginID            = -1;	
		dwDevSoftVer		= 0;
		chLocalNodeName[0]  = '\0';	
		chDeviceName[0]     = '\0';	
		chDeviceIP[0]	    = '\0';	
		//chDevNetCard1IP[0]	= '\0';
		chLoginUserName[0]= '\0';	
		chLoginPwd[0] = '\0';	
		chDeviceMultiIP[0]  = '\0';		
		chSerialNumber[0]   = '\0';	 
		iDeviceChanNum      = -1;
		iStartChan			= 0;
		iDeviceType         = 0;	
		iDiskNum            = 0;				
		lDevicePort         = 8000;	
		iAlarmInNum			= 0;	
		iAlarmOutNum        = 0;
		iIPChanNum			= 0;
			
		bCycle              = FALSE;
		bPlayDevice			= FALSE;
		bVoiceTalk			= FALSE;
		bCheckBroadcast[0]     = FALSE;	
		bCheckBroadcast[1]     = FALSE;	
		lFortifyHandle      = -1;	
		bAlarm				= FALSE;
		iDeviceLoginType    = 0;	
		dwImageType			= DEVICE_LOGOUT;
		bIPRet				= FALSE;
		pNext = NULL;
		lVoiceCom[0] = -1;
		lVoiceCom[1] = -1;
		lFirstEnableChanIndex = 0;
		lTranHandle = -1;
		memset(&struIPParaCfg,0, sizeof(NET_DVR_IPPARACFG));
		memset(&struAlarmOutCfg,0, sizeof(NET_DVR_IPALARMOUTCFG));
		memset(&struAlarmInCfg,0, sizeof(NET_DVR_IPALARMINCFG));
	}

}LOCAL_DEVICE_INFO, *PLOCAL_DEVICE_INFO;

//视频参数
typedef struct STRU_VIDEO_EFFECT{
	UINT	m_iBrightness;				//1-10
	UINT	m_iContrast;				//1-10
	UINT	m_iSaturation;				//1-10
	UINT	m_iHue;						//1-10
	STRU_VIDEO_EFFECT()
	{
		m_iBrightness = DEFAULT_BRIGHTNESS;
		m_iContrast = DEFAULT_CONTRAST;	
		m_iSaturation = DEFAULT_SATURATION;
		m_iHue = DEFAULT_HUE;
	}
}VIDEO_INFO, *PVIDEO_INFO;

//本地录像时间结构
typedef struct STRU_LOCAL_RECORD_TIME{
	WORD	iStartHour;
	WORD	iStartMinute;
	WORD	iStopHour;
	WORD	iStopMinute;
	WORD	iStartTime;
	WORD	iStopTime;
}LOCAL_RECORD_TIME,*PLOCAL_RECORD_TIME;

//本地配置
typedef struct STRU_LOCAL_PARAM
{
	BOOL		bCyclePlay;				    //是否循环播放
	int			iCycleTime;				    //循环播放时间, default 20
	BOOL		bUseCard;					//是否采用硬解码
	BOOL		bNTSC;						//硬解码视频制式,FALSE,PAL制;TRUE,NTSC制;默认为pal制

	BOOL		bAutoRecord;				//是否自动录像;
	BOOL		bCycleRecord;				//是否循环录像
	int			iStartRecordDriver;		    //客户端录像起始盘符
	int			iEndRecordDriver;			//客户端录像终止盘符
	int			iRecFileSize;				//录像文件打包大小
	int			iRecordFileInterval;		//录像打包时间间隔
	char		chDownLoadPath[100];		//远程文件下载保存路径
	char		chPictureSavePath[100];		//抓图保存路径
	char		chRemoteCfgSavePath[100];	//远程配置文件保存路径
	char		chClientRecordPath[100];		//远程文件下载保存路径

	BOOL		bAutoCheckDeviceTime;		//硬盘录像机校时
	LONG		lCheckDeviceTime;			//硬盘录像机校时时间间隔

	int			iAlarmDelayTime ;			//报警延时时间,检测报警是否超时
	int			iAlarmListenPort;			//本地报警监听端口

	BOOL		bAutoSaveLog;				//是否自动保存本地日志列表中信息
	BOOL		bAlarmInfo;					//是否在本地日志列表中显示告警信息
	BOOL		bSuccLog;				//是否在本地日志列表中显示操作日志
	BOOL		bFailLog;					//是否在本地日志列表中显示调试信息
	BOOL		bAllDiskFull;				//硬盘满

	//预览的一些标志参数
	BOOL		bPlaying;					//正在播放的标志
	BOOL		bCycling;					//正在循环播放的标志
	BOOL		bPaused;					//循环暂停
	BOOL		bNextPage;				    //手动循环下一页
	BOOL		bFrontPage;				    //手动循环上一页
	BOOL		bEnlarged;				    //图像窗口放大
	BOOL		bFullScreen;				//图像全屏放大
	BOOL		bMultiScreen;				//多窗口全屏
	BOOL		bNoDecode;					//soft decode or not
	BOOL		bPreviewBlock;				//preview block or not

	VIDEO_INFO	struVideoInfo[MAX_OUTPUTS];	//视频参数
	int			iVolume;					//音量
	BOOL		bBroadCast;					//是否进行语音广播
	char		chIPServerIP[16];
	BOOL		bOutputDebugString;

	LOCAL_RECORD_TIME struLocalRecordTime[7][4];

	STRU_LOCAL_PARAM()
	{
		bCyclePlay			= FALSE;
		iCycleTime			= 20;
		bUseCard		    = FALSE;
		bNTSC				= FALSE;
		bAutoRecord			= FALSE;
		bCycleRecord		= FALSE;
		iStartRecordDriver = 0;
		iEndRecordDriver   = 0;
		iRecFileSize	   = 1;
		iRecordFileInterval = 60;
		sprintf(chDownLoadPath, "%s","C:\\DownLoad");
		sprintf(chPictureSavePath, "%s", "C:\\Picture");
		sprintf(chRemoteCfgSavePath ,"%s", "C:\\SaveRemoteCfgFile");
		sprintf(chClientRecordPath ,"%s", "C:\\mpeg4record\\2008-04-30");

		bAutoCheckDeviceTime	=  FALSE;
		lCheckDeviceTime	= 0;

		iAlarmDelayTime		= 10;
		iAlarmListenPort	= 7200;

		bAutoSaveLog		= TRUE;
		bAlarmInfo			= TRUE;
		bSuccLog			= TRUE;
		bFailLog			= TRUE;

		bAllDiskFull		= FALSE;
		bPlaying			= FALSE;
		bCycling			= FALSE;
		bPaused				= FALSE;
		bNextPage			= FALSE;
		bFrontPage			= FALSE;
		bEnlarged			= FALSE;
		bFullScreen			= FALSE;
		bMultiScreen		= FALSE;
		iVolume				= DEFAULT_VOLUME;
		bBroadCast			= FALSE;
		bNoDecode			= FALSE;
		bPreviewBlock		= TRUE;
		chIPServerIP[0] 	= '\0';
		bOutputDebugString	= FALSE;
		memset(&struLocalRecordTime[0][0], 0, sizeof(LOCAL_RECORD_TIME)*7*4);
	}
}LOCAL_PARAM, *PLOCAL_PARAM;

#endif
