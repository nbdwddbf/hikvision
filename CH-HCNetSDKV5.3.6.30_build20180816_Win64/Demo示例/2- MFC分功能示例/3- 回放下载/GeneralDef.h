
#ifndef GENERALDEF_H
#define GENERALDEF_H

#include "HCNetSDK.h"
#include "plaympeg4.h"



#define MAX_CHANS      24              //设备支持的最大通道数
#define MAX_DEVICE     10             //最大设备数
#define MAX_OUTPUTS	   16	//16最大的窗口数
#define MAX_PREVIEWS		512	//可预览的最大数

//设备区域配置
#define TREE_ALL_T	 0        //代表根节点
#define DEVICETYPE 	 1		  //代表设备
#define CHANNELTYPE	 2	      //代表通道


#define DEMO_FULL_WIDTH 1024	//demo默认的宽度
#define DEMO_FULL_HEIGHT 768	//demo默认的高度
#define OUTPUT_INTERVAL 4		//每个画面的间隔大小


//定时器时间
#define CYCLE_PREVIEW_TIMER        2    //循环预览定时器
#define REMOTE_PLAY_STATE_TIMER	   8		//远程回放文件播放状态时钟
#define DOWNSTATE_TIMER		       9	 //下载文件时钟
#define LOCAL_PLAY_STATE_TIMER     10
#define PLAYBYTIME_TIMER	       12		// 按时间回放
#define DOWNBYTIME_TIMER		   13		//按时间下载

//远程文件查找返回值
#define NET_DVR_FILE_SUCCESS    1000
#define NET_DVR_FILE_NOFIND     1001
#define NET_DVR_ISFINDING       1002
#define NET_DVR_NOMOREFILE      1003
#define NET_DVR_FILE_EXCEPTION  1004

typedef struct STRU_CHANNEL_INFO
{
	int		iDeviceIndex;			//对应的设备的数组下标
	int		iChanIndex;			//监控通道号
	char	chChanName[100];	//本地通道结点名称

	int		iPicResolution;				//图片分辨率
	int		iPicQuality;				//图片质量
	LONG	lRealHandle;          //实时预览句柄

	int     iWinowIndex;           //预览时与通道关联的窗口索引
	BOOL    isRecording;           //正在录像
    BOOL    bEnable;               //通道是否使能
	char	chAccessChanIP[16];//ip接入通道的ip地址

	STRU_CHANNEL_INFO *pNext;

	STRU_CHANNEL_INFO()
	{
		iDeviceIndex        = -1;
		iChanIndex          = -1;
		chChanName[0]       = '\0';
		iPicResolution		= 0;
		iPicQuality			= 2;
		lRealHandle         = -1;
		chAccessChanIP[0]	= '\0';	
		iWinowIndex         = -1;
		isRecording         = FALSE;
		bEnable             = FALSE;
		pNext				= NULL;
	}
}CHANNEL_INFO,*pCHANNEL_INFO;

typedef struct STRU_DEVICE_INFO
{
	int		iDeviceIndex;			//设备数组下标
	LONG	lLoginID;				//注册ID
	char	chLocalNodeName[100];	//本地设备节点名称
	char	chDeviceName[100];		//设备名称
	char	chDeviceIP[33];			//可以直接连接的设备IP
	UINT	lDevicePort;			//设备主端口号
	char	chLoginUserName[30];	//登陆设备的用户名，在用户管理的时候用到
	char	chLoginPwd[30];	//登陆设备的密码
	//char	chDeviceMultiIP[20];	//多播组地址
	char	chSerialNumber[50];		//序列号
	int		iDeviceChanNum;		    //设备的通道数
	int		iStartChan;				//设备开始通道号
	int		iDeviceType;			//设备类型
	int 	iIPChanNum;				//最大数字通道个数
    BOOL    bIPRet;                 //是否IP接入
//	BOOL	bCycle;					//该设备是否在循环播放
	BOOL	bPlayDevice;			//该设备是不是所有通道都在播放
	BOOL    bIsLogin;               //是否已注册该设备
	int		iEnableChanNum;			//有效通道数
	CHANNEL_INFO struChanInfo[MAX_CHANNUM_V30];
    STRU_DEVICE_INFO *pNext;

	STRU_DEVICE_INFO()
	{
       //  iDeviceIndex  = -1;
         lLoginID            = -1;
		 chLocalNodeName[0]  = '\0';
		 chDeviceName[0]     = '\0';
		 chDeviceIP[0]       = '\0';
         lDevicePort         = 8000;
         chLoginUserName[0]  = '\0';
         chLoginPwd[0]       ='\0';
         //chDeviceMultiIP[0]   ='\0';
		 chSerialNumber[0]   = '\0';
		 iDeviceChanNum      =  -1;
		 iStartChan          = 0;
		 iDeviceType         = 0;
		 iIPChanNum          = 0;
		 bIPRet              = 0;
		 bIsLogin            = FALSE;
//		 bCycle              = FALSE;
		 bPlayDevice         = FALSE;
		 iEnableChanNum      = -1;
		 pNext=NULL;
	}	 
}LOCAL_DEVICE_INFO,*pLOCAL_DEVICE_INFO;


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


typedef struct STRU_LOCAL_FILE_INFO{
	char chName[100];             //文件名
	DWORD FileSize;               //大小
	CTime StartTime;              //开始时间
	CTime StopTime;               //结束时间
	int iType;                    //文件类型

	STRU_LOCAL_FILE_INFO()
	{
        chName[0] = '\0';
		FileSize = 0;
        iType = -1;
	}
}LOCAL_FILE_INFO,*PLOCAL_FILE_INFO;

#endif