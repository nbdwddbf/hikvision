
#ifndef GENERALDEF_H
#define GENERALDEF_H

#include "HCNetSDK.h"
#include "plaympeg4.h"

#define MAX_CHANS      24     //设备支持的最大通道数
#define MAX_DEVICE     10     //最大设备数
#define MAX_OUTPUTS	   16	//16最大的窗口数
#define MAX_PREVIEWS   512	//可预览的最大数

//设备区域配置
#define TREE_ALL_T	 0        //代表根节点
#define DEVICETYPE 	 1		  //代表设备
#define CHANNELTYPE	 2	      //代表通道


#define DEMO_FULL_WIDTH 1024	//demo默认的宽度
#define DEMO_FULL_HEIGHT 768	//demo默认的高度
#define OUTPUT_INTERVAL 4		//每个画面的间隔大小


//定时器时间
#define UPGRADE_TIMER			6		//升级时钟
#define FORMAT_TIMER			10		//远程格式化硬盘

typedef struct STRU_CHANNEL_INFO
{
	char    chChanName[40];     //通道名称
	int		iChanIndex;			//监控通道号 = 数组索引+startchan
	int		iPicResolution;				//图片分辨率
	int		iPicQuality;				//图片质量
	char	chAccessChanIP[16];     //ip接入通道的ip地址
	BOOL    bEnable;              //是否有效

	STRU_CHANNEL_INFO()
	{
		chChanName[0]       ='\0';
		iChanIndex          = -1;
		iPicResolution		= 0;
		iPicQuality			= 2;
		chAccessChanIP[0]	= '\0';	
		bEnable             = FALSE;
	}
}CHANNEL_INFO,*pCHANNEL_INFO;

typedef struct STRU_DEVICE_INFO
{

	char    chDevName[100];        //设备名称
	char    sSerialNumber[100];     //设备序列号
	char    chDevIP[40];            //设备IP
	LONG    lLoginID;
	int		iDeviceChanNum;		    //设备的通道数
	int		iStartChan;				//设备开始通道号
	int 	iIPChanNum;				//最大数字通道个数
	int		iEnableChanNum;			//有效通道数
	BOOL    bIPRet;                 //是否支持ip接入
	BYTE    byDiskNum;				    //硬盘个数
    BYTE    byDVRType;				    //设备类型, 1:DVR 2:ATM DVR 3:DVS ......
	
	CHANNEL_INFO struChanInfo[MAX_CHANNUM_V30];


	STRU_DEVICE_INFO()
	{
         chDevName[0]        = '\0';
		 sSerialNumber[0]    = '\0';
		 chDevIP[0]          = '\0';
		 lLoginID = -1;
		 iDeviceChanNum      =  -1;
		 iStartChan          = 0;
		 iIPChanNum          = 0;
		 iEnableChanNum      = -1;
		 bIPRet              = FALSE;
		 byDiskNum           = 0;
         byDVRType           = 0;
	}	 
}LOCAL_DEVICE_INFO,*pLOCAL_DEVICE_INFO;




#endif