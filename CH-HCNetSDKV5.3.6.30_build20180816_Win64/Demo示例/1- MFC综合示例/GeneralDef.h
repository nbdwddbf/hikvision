/**********************************************************
FileName:    GeneralDef.h
Description: demo and struct define for clientdemo      
Date:        2008/03/27   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/03/27>       <created>
***********************************************************/

#ifndef _GLOBLE_DEF_H_
#define _GLOBLE_DEF_H_

//include header file for SDK and decoding lib
#include "HCNetSDK.h"
#include "DecodeCardSdk.h"
#include "DataType.h"
#include "plaympeg4.h"
#define ARRAY_SIZE(A)	(sizeof(A)/sizeof((A)[0]))	// Array size

//vca
#define MIN_PNT_NUM 3			//minixum number of polygon points
#define PI 3.1415926
#define WM_MYCOMMAND					WM_USER + 1		//for sdk
#define WM_CHANGE_CHANNEL_ITEM_IMAGE	WM_USER + 2     //change channel node icon
#define WM_CHANGE_DEVICE_ITEM_IMAGE		WM_USER + 3     //change device node icon
#define WM_ADD_LOG						WM_USER + 4		//add log 
#define WM_PROC_ALARM					WM_USER + 5		//alarm handle
#define WM_PROC_SNAPCALLBACK			WM_USER + 6		//vca face callback handle
#define WM_PROC_FACECALLBACK			WM_USER + 7		//vca face callback handle
#define WM_PROC_ALARMHOST_EXTERNAL_MODULE		WM_USER + 8
#define WM_PROC_LCD_PARAM               WM_USER + 9
#define WM_PROC_LCD_SPLICE              WM_USER + 109

#define DEMO_FULL_WIDTH 1024	//default demo width
#define DEMO_FULL_HEIGHT 768	//default demo height
#define OUTPUT_INTERVAL 4		//interval between each display window
#define LIST_ENLARGE_HIGH 575	//enlarge height of	local log or alarm list

#define WIDTH_4CIF			704
#define HEIGHT_4CIF_PAL		576
#define HEIGHT_4CIF_NTSC	480
#define WIDTH_CIF			352
#define HEIGHT_CIF_PAL		288
#define HEIGHT_CIF_NTSC		240
#define PRECISION_4CIF_FRAME	32//zone setting unit precision under 4cif

#define ISAPI_STATUS_LEN      (4096*4)
#define ISAPI_DATA_LEN        (4096*4)

//m_iMainType mian fuction bar main function type
#define PREVIEW_T		0
#define CONFIG_ALL_T	1
#define PLAY_BACK_T		2
#define STREAM_ID_T     3
#define PRODUCT_RELATE_T   4

//config dialog type 
	//remote config type
#define REMOTE_DEVICE_CFG_T		0	//device config
#define REMOTE_NETWORK_CFG_T    1   //network config
#define REMOTE_CHANNEL_CFG_T	2	//channel info configuration
#define REMOTE_SEREIAL_CFG_T	3	//serial port info configuration
#define REMOTE_AlARM_CFG_T		4	//alarm input/output configuration
#define REMOTE_USER_CFG_T		5	//user info configuration
#define REMOTE_EXCEPTION_CFG_T	6	//exception info configuration
#define REMOTE_ATM_INFO_CFG_T	7	//ATM info configuration
//#define REMOTE_MAT_DEC_CFG_T	8	//multi-channel decoder configuration
#define REMOTE_ZERO_CHAN_CFG_T  8   // Zero Chan Cfg


enum DEMO_CHANNEL_TYPE
{
	DEMO_CHANNEL_TYPE_INVALID = -1,
	DEMO_CHANNEL_TYPE_ANALOG  = 0,
	DEMO_CHANNEL_TYPE_IP = 1,
	DEMO_CHANNEL_TYPE_MIRROR = 2
};

	
#define LOCAL_CFG_T				8
#define LOG_QUERY_T				9
#define DECODE_CARD_CFG_T		10
#define BATCH_CFG_T				11

//play back dialog type
#define  PLAY_REMOTE_FILE_T 0
#define  PLAY_LOCAL_FILE_T 1
#define  PLAY_REMOTE_TIME_T 2
#define  PLAY_REMOTE_EVENT_T 3
#define  PLAY_REMOTE_MOTION_T 4
#define  PLAY_REMOTE_PIC_T 5
#define  PLAY_REMOTE_SMART_PIC_T 6
#define  PLAY_RECORD_LABEL  7
#define  PLAY_LOCK_FILE_T  8 //2011-8-23
#define  PLAY_DVR_RECORD_T  9 //2011-8-25
//local log type
#define ALARM_INFO_T		0	//alarm
#define OPERATION_SUCC_T	1	//operation succeed
#define OPERATION_FAIL_T	2	//operation fail
#define PLAY_SUCC_T			3	//player succeed
#define PLAY_FAIL_T			4	//player fail
#define DDNS_SUCC_T			5	//ddns succeed
#define DDNS_FAIL_T			6	//ddns fail

#define DETECT_AREA_LEFT 10//left position of detection zone
#define DETECT_AREA_TOP 10//upper position of detection zone
#define SCREEN_EDGE 30		//size of screen edge

#define MINSPACE		(200*1024*1024)//min HD size

//timer
#define SYSTEM_TIMER			1		//timer for system parameter,cpu
#define CYCLE_PREVIEW_TIMER		2		//switch display timer
#define	AUTORECORD_TIMER		3		//suto record timer
#define	FREESPACE_TIMER			4		//check HD timer
#define	FILEINTERVAL_TIMER		5		//save file interval timer
#define UPGRADE_TIMER			6		//update timer
#define PLAY_TIMER				7		//local playback status timer
#define REMOTE_PLAY_STATE_TIMER	8		//remote playback status timer
#define DOWNSTATE_TIMER			9		//file download timer
#define FORMAT_TIMER			10		//remote HD format timer
#define EVENTLOG_TIMER			11		//event log timer
#define PLAYBYTIME_TIMER		12		//timer for playback on time
#define DOWNBYTIME_TIMER		13		//timerfor download on time
#define SERIAL_TIMER			14		//timer for serial port send data
#define	CHECK_DEVICE_TIMER		15		//timer for device time checking
#define AUDIOUPLOAD_TIMER		16		//timer for audio upload
#define AUDIODOWNLOAD_TIMER		17		//timer for audio download
#define FACE_DATABASE_INQUIRE   18      //timer for inquire face database
#define SNAP_DATABASE_INQUIRE   19      //timer for inquire snap database
#define WALL_WINSTATUS_TIMER    20      //timer for wall window status
#define TRANS_DEVICE_TIMER      21      //timer for Trans device
#define PLAYBACK_NPQ_STATUS_TIMER      22      //timer for npq playback
//default image parameter
#define DEFAULT_BRIGHTNESS	6			//default brightness
#define DEFAULT_CONTRAST	6			//default contrast
#define DEFAULT_SATURATION  6			//default saturation
#define DEFAULT_HUE			6			//default hue
#define DEFAULT_SHARPNESS   6			//default sharpness
#define DEFAULT_DENOISING	6			//default denoising
#define DEFAULT_VOLUME		50			//default volume


#define MAX_DEVICES			512	//max device number
#define MAX_OUTPUTS			512	//16max windownumber
#define MAX_PREVIEWS		512	//max preview number

//device list config
#define TREE_ALL_T	 0        //root node
#define DEVICETYPE 	 1		  //device
#define CHANNELTYPE	 2	      //channel		

/////
//bmp status
#define TREE_ALL			 0	//device list	
#define DEVICE_LOGOUT	     1   //device not log in
#define DEVICE_LOGIN	     2   //devic3e login
#define DEVICE_FORTIFY	     3   //on guard
#define DEVICE_ALARM		 4   //alarm on device
#define DEVICE_FORTIFY_ALARM 5	//onguard & alarm on device

#define CHAN_ORIGINAL		 6   //no preview, no record
#define CHAN_PLAY		 	 7   //preview
#define CHAN_RECORD			 8   //record
#define CHAN_PLAY_RECORD	 9   //preview and record

#define CHAN_ALARM		 	 10   //no preview, no record, only alarm
#define CHAN_PLAY_ALARM			 11   //review, no record, with alarm info
#define CHAN_PLAY_RECORD_ALARM	 12   //preview & record & alarm
#define CHAN_OFF_LINE			 13	 //channel off-line

#define CHAN_AUDIO				 1   //audio channel

//ATM info input
#define NET_LISTEN				0	//network listen;
#define NET_ACCEPT				1	//network receive;
#define SERIAL_INPUT_DIRECTLY	2	//serial port input;
#define SERIAL_ATM_CMD_INPUT	3	//serial port ATM command input;

//compression parameter
#define NORM_HIGH_STREAM_COMPRESSION		0//主码流图像压缩参数,压缩能力强,性能可以更高
#define SUB_STREAM_COMPRESSION		1//子码流图像压缩参数
#define EVENT_INVOKE_COMPRESSION	2//事件触发图像压缩参数,一些参数相对固定
//#define NORM_LOW_STREAM_COMPRESSION		3//主码流图像压缩参数,压缩能力强,性能可以更高
#define THIRD_STREAM_COMPRESSION    3  //第三码流
#define TRANS_STREAM_COMPRESSION    4  //转码码流
//serial port type
#define SERIAL_232		1	//232
#define SERIAL_485		2	//485


#define	ANALOG_CHAN_DISABLE 0
#define	ANALOG_CHAN_ENABLE	1
#define	IP_CHAN_DISABLE		2
#define	IP_CHAN_ENABLE		3

#define ALARM_OUT_FORMAT		("AlarmOut%d")
#define ALARM_IN_NAME			("AlarmIn%d")
#define IP_ALARM_IN_NAME		("IPAlarmIn%d")
#define IP_ALARM_OUT_NAME		("IPAlarmOut%d")
#define IP_ALARM_OUT_BYCHAN		("%s-%d")
#define ANALOG_C_FORMAT			("Camera%d")
#define IP_CAMERA_NAME			("IPCamera%02d")
#define DIGITAL_C_FORMAT		("IPCamera%d")
#define MIRROR_C_FORMAT			("Mirror%d")

#define ZERO_CHAN_INDEX     500
#define MIRROR_CHAN_INDEX   400

typedef struct tagLOCAL_SENSOR_ADD_PREVIEW
{
    BYTE    byEnable;      // 是否启用
    BYTE    byRes[3];       // 保留字节
    NET_DVR_IPADDR struIPAddr;  //  IP地址
    LONG    lChannel;       // 通道号
}LOCAL_SENSOR_ADD_PREVIEW, *LPLOCAL_SENSOR_ADD_PREVIEW;

//device index on play-all/group play mode
typedef struct STRU_PLAY_INFO{

	int		iDeviceIndex;		//device index
	int		iChanIndex;			//channel index

	STRU_PLAY_INFO()
	{
		iDeviceIndex = -1;
		iChanIndex   = -1;
	}
}PLAY_INFO,*PPLAY_INFO;

//device index info
typedef struct STRU_CHANNEL_INFO{ 
	int		iDeviceIndex;			//device index
	int		iChanIndex;			//channel index

	DEMO_CHANNEL_TYPE iChanType;
	int     iChannelNO;         //channel NO.       

	char	chChanName[100];	//channel name
	DWORD	dwProtocol;			//network protocol
	
	DWORD dwStreamType; //码流类型，0-主码流，1-子码流，2-码流3，
	DWORD dwLinkMode;//码流连接方式: 0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-RTP/RTSP,5-RSTP/HTTP

	BOOL	bPassbackRecord; //0-不启用录像回传,1启用录像回传
	DWORD	dwPreviewMode;		//预览模式 0-正常模式 1-延时预览
	int		iPicResolution;				//resolution
	int		iPicQuality;				//image quality
	LONG	lRealHandle;          //preview handle
	BOOL    bLocalManualRec;     //manual record
	BOOL    bAlarm;				//alarm
	BOOL	bEnable;			//enable
	DWORD	dwImageType;		//channel status icon
	char	chAccessChanIP[16];//ip addr of IP channel
	DWORD	nPreviewProtocolType;	//取流协议类型 0-私有协议 1-RTSP协议
    DWORD   nVideoCodingType; //码流数据编解码类型 0-通用编码类型(YUV)（一个像素点8BIT） 1-裸码流类型（一个像素点14BIT）（SDK内部头文件中保留，不开放给用户）

	STRU_CHANNEL_INFO *pNext;
	STRU_CHANNEL_INFO()
	{
		iDeviceIndex		= -1;
		iChanIndex			= -1;
		iChannelNO          = -1;
		iChanType           = DEMO_CHANNEL_TYPE_INVALID;
		chChanName[0]		= '\0';
		dwProtocol			= 0;

		dwStreamType        = 0;
		dwLinkMode          = 0;

		iPicResolution		= 0;
		iPicQuality			= 2;

		lRealHandle			= -1; 
		bLocalManualRec		= FALSE;
		bAlarm				= FALSE;
		bEnable				= FALSE;
		dwImageType			= CHAN_ORIGINAL;
		chAccessChanIP[0]	= '\0';	 		  
		pNext				= NULL;
		dwPreviewMode		= 0;
		bPassbackRecord     = FALSE;
		nPreviewProtocolType = 0;
	}
}CHANNEL_INFO,*PCHANNEL_INFO;

//2011-12-16 被动解码结构 silujie
typedef struct STRU_PASSIVEDECODE_CHANINFO
{
	LONG	lPassiveHandle;
	LONG lRealHandle;
	LONG lUserID;
	LONG lSel;
	HANDLE hFileThread;
	HANDLE hFileHandle;
	HANDLE hExitThread;
	HANDLE hThreadExit;
    CString strRecordFilePath;
	STRU_PASSIVEDECODE_CHANINFO()
	{
		lPassiveHandle = -1;
		lRealHandle = -1;
		lUserID = -1;
		lSel = -1;
		hFileThread = NULL;
		hFileHandle = NULL;
		hExitThread = NULL;
		hThreadExit = NULL;
		strRecordFilePath = "";
	}
}PASSIVEDECODE_CHANINFO, *LPPASSIVEDECODE_CHANINFO;

//有些设备语音对讲端子大于2，但又不能更改NET_DVR_WORKSTATE_V30
#define MAX_AUDIO_V40  8

//device info
typedef struct STRU_DEVICE_INFO{
	int		iDeviceIndex;			//device index
	LONG	lLoginID;				//ID
	DWORD	dwDevSoftVer;			//erserved
	
	char	chLocalNodeName[100];	//local device node
	char	chDeviceName[100];		//device name
    char	chDeviceClassName[100];		//device class name
	char	chDeviceIP[130];			//device IP: IP,pppoe address, or network gate address, etc
	char    chDeviceIPInFileName[130];  //if chDeviceIP includes ':'(IPV6),change it to '.', for '.'is not allowed in window's file name
	//char	chDevNetCard1IP[33];	//IP
	char	chLoginUserName[NAME_LEN];	//login user name
	char	chLoginPwd[NAME_LEN];	//password
	char	chDeviceMultiIP[130];	//multi-cast group address
	//char	chIPServerIP[32];		//IP
	char	chSerialNumber[50];		//SN
	int		iDeviceChanNum;		    //channel numder  (analog + ip)
	int		iStartChan;				//start channel number
	int		iDeviceType;			//device type
	int 	iDiskNum;				//HD number
	LONG 	lDevicePort;			//port number
	int		iAlarmInNum;			//alarm in number
	int		iAlarmOutNum;			//alarm out number
	int 	iAudioNum;				//voice talk number
	int		iAnalogChanNum;			//analog channel number
	int 	iIPChanNum;				//IP channel number
	int     iGroupNO;               //IP Group NO.

	BOOL	bCycle;					//if this device is on cycle recording
	BOOL	bPlayDevice;			//will be added later
	BOOL	bVoiceTalk;				//on voice talkor not
	LONG    lAudioHandle[MAX_AUDIO_V40]; //voicebroadcast handle
	BOOL	bCheckBroadcast[MAX_AUDIO_V40]; //Add to broad cast group
	LONG	lFortifyHandle;			//on guard handle
	BOOL    bAlarm;					//whether there is alarm
	int	    iDeviceLoginType;		//register mode  0 - fix IP   1- IPSERVER mode    2 -  domain name 
	DWORD	dwImageType;			//device status icon
	BOOL	bIPRet;					//support IP conection
	int		iEnableChanNum;			//valid channel number
	BOOL	bDVRLocalAllRec;		//local recording
	LONG	lVoiceCom[MAX_AUDIO_V40];	//voice transmit
	LONG	lFirstEnableChanIndex;			//first enabled channel index
	LONG	lTranHandle;				//232 transparent channel handle
    BYTE byZeroChanNum;		//Zero channel number
    BYTE byMainProto;			//main stream protocol type 0-Private, 1-rtp/tcp, 2-rtp/rtsp
    BYTE bySubProto;				//sub stream protocol type 0-Private, 1-rtp/tcp, 2-rtp/rtsp
    BYTE bySupport;             //ability
	BYTE byStartDTalkChan;
	BYTE byAudioInputChanNum;
    BYTE byStartAudioInputChanNo;
    BYTE byLanguageType;
	STRU_CHANNEL_INFO *pStruChanInfo; //channel structure
	NET_DVR_IPPARACFG_V40 *pStruIPParaCfgV40;				//IP channel parameters
	NET_DVR_IPALARMINCFG struAlarmInCfg;
    NET_DVR_IPALARMINCFG_V40   *pStruIPAlarmInCfgV40;  // IP alarm In parameters
	NET_DVR_IPALARMOUTCFG_V40  *pStruIPAlarmOutCfgV40; // IP alarm Out parameters
	NET_DVR_IPALARMOUTCFG struAlarmOutCfg;
	STRU_DEVICE_INFO *pNext;
	CHANNEL_INFO struZeroChan[16];	
	char sSecretKey[16];
	int iAudioEncType;
	PASSIVEDECODE_CHANINFO struPassiveDecode[256];
	BYTE bySupport1;	//能力，位与结果为0表示不支持，1表示支持
	// bySupport1 & 0x1, 表示是否支持snmp v30
	//bySupport1 & 0x2, 支持区分回放和下载	
	//bySupport1 & 0x4, 是否支持布防优先级	
	//bySupport1 & 0x8, 智能设备是否支持布防时间段扩展
	//bySupport1 & 0x10, 表示是否支持多磁盘数（超过33个）
	//bySupport1 & 0x40 表示是否支持延迟预览
	BYTE bySupport2; //能力集扩展，位与结果为0表示不支持，1表示支持
	//bySupport2 & 0x1, 表示解码器是否支持通过URL取流解码
	//bySupport2 & 0x2,  表示支持FTPV40
	//bySupport2 & 0x4,  表示支持ANR(断网录像)
    BYTE  byStartIPAlarmOutNo;  //起始IP报警输出号
	BYTE byMirrorChanNum; //镜像通道个数，<录播主机中用于表示导播通道>
	WORD wStartMirrorChanNo;  //起始镜像通道号
	CHANNEL_INFO struMirrorChan[16];
	BYTE bySupport5;
    BYTE bySupport7;// bySupport7 & 0x2  表示设备是否支持 IPC HVT 模式扩展
    BYTE byCharaterEncodeType;
    BYTE byProxyType; //代理类型，0-不使用代理，1-使用标准代理，2-使用EHome代理

    BYTE byLoginMode; 
    BYTE byHttps;

    BYTE byLoginModeRes;
    char szURL[1024];
    BYTE byURL;

	STRU_DEVICE_INFO()
	{	
		iGroupNO = -1;
		iDeviceIndex		= -1;
		lLoginID            = -1;	
		dwDevSoftVer		= 0;
		chLocalNodeName[0]  = '\0';	
		chDeviceName[0]     = '\0';	
		chDeviceIP[0]	    = '\0';	
		chDeviceIPInFileName[0] = '\0';	
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
		iAnalogChanNum		= 0;
		iIPChanNum			= 0;
		byAudioInputChanNum = 0;
        byStartAudioInputChanNo = 0;
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
		for(int i = 0; i < sizeof(lVoiceCom)/sizeof(int);i++)
        {
            lVoiceCom[i] = -1;
        }
		lFirstEnableChanIndex = 0;
		lTranHandle = -1;
		byZeroChanNum = 0;
        lAudioHandle[0] = -1;
        lAudioHandle[1] = -1;
		memset(&struAlarmOutCfg,0, sizeof(NET_DVR_IPALARMOUTCFG));
        memset(&struAlarmInCfg,0, sizeof(NET_DVR_IPALARMINCFG));
        memcpy(sSecretKey, "StreamNotEncrypt", 16);
        iAudioEncType = 0;   
        bySupport1 = 0;
        bySupport2 = 0;
		bySupport5 = 0;
		bySupport7 = 0;
        byStartDTalkChan = 0;
        byLanguageType = 0;
        byCharaterEncodeType = 0;

        pStruChanInfo = NULL;
        pStruIPParaCfgV40 = NULL;

        byLoginMode = 0;
        byHttps = 0;

        byLoginModeRes = 0;
        byURL = 0;
        byProxyType = 0;
        memset(szURL, 0, sizeof(szURL));
	}	
	
	~STRU_DEVICE_INFO()
	{
		// 	           if (pStruChanInfo != NULL)
		// 			   {
		// 	               delete[] pStruChanInfo;
		// 	              pStruChanInfo = NULL;
		// 	          }
		// 	          if (pStruIPAlarmInCfgV40 != NULL)
		// 	          {
		// 	              delete pStruIPAlarmInCfgV40;
		// 	              pStruIPAlarmInCfgV40 = NULL;
		// 	          }
		// 	          
		// 	          if (pStruIPAlarmOutCfgV40 != NULL)
		// 	          {
		// 	              delete pStruIPAlarmOutCfgV40;
		// 	              pStruIPAlarmOutCfgV40 =  NULL;
		// 	          }     
	} 
	
}LOCAL_DEVICE_INFO, *PLOCAL_DEVICE_INFO;


//video parameter
typedef struct STRU_VIDEO_EFFECT{
	UINT	m_iBrightness;				//1-10
	UINT	m_iContrast;				//1-10
	UINT	m_iSaturation;				//1-10
	UINT	m_iHue;						//1-10
	UINT	m_iSharpness;
	UINT	m_iDenoising;
	STRU_VIDEO_EFFECT()
	{
		m_iBrightness = DEFAULT_BRIGHTNESS;
		m_iContrast = DEFAULT_CONTRAST;	
		m_iSaturation = DEFAULT_SATURATION;
		m_iHue = DEFAULT_HUE;
		m_iSharpness = DEFAULT_SHARPNESS;
		m_iDenoising = DEFAULT_DENOISING;
	}
}VIDEO_INFO, *PVIDEO_INFO;

//local recording structure
typedef struct STRU_LOCAL_RECORD_TIME{
	WORD	iStartHour;
	WORD	iStartMinute;
	WORD	iStopHour;
	WORD	iStopMinute;
	WORD	iStartTime;
	WORD	iStopTime;
}LOCAL_RECORD_TIME,*PLOCAL_RECORD_TIME;

//local config
typedef struct STRU_LOCAL_PARAM
{
    BOOL        bReconnect;                 //reconnect
	BOOL		bCyclePlay;				    //cycle play
	int			iCycleTime;				    //cycle time, default 20
	BOOL		bUseCard;					//hadrware decode
	BOOL		bNTSC;						//hardware decode mode,FALSE,PAL;TRUE,NTSC;default as pal

	BOOL		bAutoRecord;				//auto record;
	BOOL		bCycleRecord;				//cycle record
	int			iStartRecordDriver;		    //client record starting HD dirve
	int			iEndRecordDriver;			//client record stop HD drive
	int			iRecFileSize;				//record file size
	int			iRecordFileInterval;		//record file interval
	char		chDownLoadPath[100];		//remote file download directory
	char		chPictureSavePath[100];		//image capture directory
	char		chRemoteCfgSavePath[100];	//remote config file saving directory
	char		chClientRecordPath[100];		//client record path

	BOOL		bAutoCheckDeviceTime;		//check time with device
	LONG		lCheckDeviceTime;			//check time interval

	int			iAlarmDelayTime ;			//alarm delay time

	int         iAlarmListenPort;

	BOOL		bAutoSaveLog;				//auto save local log info
	BOOL		bAlarmInfo;					//display alarm info on log list
	BOOL		bSuccLog;				//display log access on log list
	BOOL		bFailLog;					//display filaure operation on log list
	BOOL		bAllDiskFull;				//HD full

	//preview
	BOOL		bPlaying;					//on playing
	BOOL		bCycling;					//cycle playing
	BOOL		bPaused;					//cycle pause
	BOOL		bNextPage;				    //next page
	BOOL		bFrontPage;				    //previous page
	BOOL		bEnlarged;				    //enlarge image
	BOOL		bFullScreen;				//full screen
	BOOL		bMultiScreen;				//multi-split-window full screen
	BOOL		bNoDecode;					//soft decode or not
	BOOL		bPreviewBlock;				//preview block or not

	VIDEO_INFO	struVideoInfo[MAX_OUTPUTS];	//video parameter
	int			iVolume;					//volume
	BOOL		bBroadCast;					//voice broadcast
	char		chIPServerIP[128];
	BOOL		bOutputDebugString;

	LOCAL_RECORD_TIME struLocalRecordTime[7][4];
	DWORD		dwBFrameNum;//throw B frame number
	DWORD   nLogLevel;
    BOOL    bCycleWriteLog;
	DWORD   nTimeout;
	NET_DVR_SLAVECAMERA_CFG struSlaveCameraCfg[4];
	STRU_LOCAL_PARAM()
	{
        bReconnect          = TRUE;
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
		sprintf(chIPServerIP ,"%s", "172.7.28.123");

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
		bOutputDebugString	= FALSE;
		dwBFrameNum			= 0;
		nLogLevel				= 3;
        bCycleWriteLog      = FALSE;
		nTimeout				= 5000;
		memset(&struLocalRecordTime[0][0], 0, sizeof(LOCAL_RECORD_TIME)*7*4);
		memset(struSlaveCameraCfg, 0, sizeof(NET_DVR_SLAVECAMERA_CFG));
	}
}LOCAL_PARAM, *PLOCAL_PARAM;



//人脸注册黑名单的人脸子图
typedef struct LOCAL_FACE_PICTURE_INFO{
	DWORD dwImageID; //大图ID
	DWORD dwFaceScore; //人脸评分，0-100
	NET_VCA_RECT struVcaRect; //人脸区域
	LOCAL_FACE_PICTURE_INFO()
	{
		dwImageID = 0;
		dwFaceScore = 0;
		memset(&struVcaRect, 0, sizeof(NET_VCA_RECT));
	}
}LOCAL_FACE_PICTURE_INFO,*PLOCAL_FACE_PICTURE_INFO;

typedef struct LOCAL_FACE_MODEL_INFO{
	DWORD dwFacePicLen;
	DWORD dwFaceModelLen;
	BYTE byFacePic[10*1024];
	BYTE byModelData[10*1024];
	LOCAL_FACE_MODEL_INFO()
	{
		dwFacePicLen = 0;
		dwFaceModelLen = 0;
		memset(byFacePic, 0, 10*1024);
		memset(byModelData, 0, 10*1024);
	}
}LOCAL_FACE_MODEL_INFO, *PLOCAL_FACE_MODEL_INFO;

typedef struct LOCAL_ALARMIN_HANDLE{
	NET_DVR_HANDLEEXCEPTION_V41 struAlarmHandleType;	/* 处理方式 */ 
	NET_DVR_SCHEDTIME struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30];//布防时间
	DWORD dwRelRecordChan[MAX_CHANNUM_V40]; //被触发的录像通道
}LOCAL_ALARMIN_HANDLE, *LPLOCAL_ALARMIN_HANDLE;

typedef struct CASE_INFO
{
	BYTE	byCaseNo[SEARCH_CASE_NO_LEN];
	BYTE	byCaseName[SEARCH_CASE_NAME_LEN];
	BYTE	byLitigant1[SEARCH_LITIGANT_LEN];
	BYTE	byLitigant2[SEARCH_LITIGANT_LEN];
	BYTE	byChiefJudge[SEARCH_CHIEF_JUDGE_LEN];
	BYTE	byCaseType;
	BYTE	byRes[3];
}CASE_INFO,*LPCASE_INFO;

#define  XML_BUF 3*1024*1024


#endif
