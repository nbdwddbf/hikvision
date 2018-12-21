
#ifndef GENERALDEF_H
#define GENERALDEF_H

#include "HCNetSDK.h"
#include "plaympeg4.h"

//设备区域配置
#define TREE_ALL_T	 0        //代表根节点
#define DEVICETYPE 	 1		  //代表设备
#define CHANNELTYPE	 2	      //代表通道

#define MAX_AUDIO_V30 2        //最大语音通道数


//Wav
#define BITS_PER_SAMPLE		16
#define CHANNEL				1
#define SAMPLES_PER_SECOND	16000

#define BIT_RATE_16000		16000
#define AUDENCSIZE          1280
#define AUDDECSIZE          80
#define BUFFER_SIZE         1280
#define BUFFER_NUM           6
#define AUDIOBUF			(80*40L)



typedef struct STRU_DEVICE_INFO
{
	LONG	lLoginID;				//注册ID
	char	chLocalNodeName[100];	//本地设备节点名称
	char	chDeviceName[100];		//设备名称
	char	chDeviceIP[40];			//可以直接连接的设备IP
	UINT	lDevicePort;			//设备主端口号
	char	chLoginUserName[40];	//登陆设备的用户名，在用户管理的时候用到
	char	chLoginPwd[40];	         //登陆设备的密码
	//char	chDeviceMultiIP[20];	//多播组地址
	char	chSerialNumber[60];		//序列号
	int		iDeviceType;			//设备类型
	BOOL    bIsLogin;               //是否已注册该设备
	int     iVoiceChanNum;             //语音通道数
	BYTE    AudioChanStatus[MAX_AUDIO_V30];   //语音通道状态     

	STRU_DEVICE_INFO()
	{
         lLoginID            = -1;
		 chLocalNodeName[0]  = '\0';
		 chDeviceName[0]     = '\0';
		 chDeviceIP[0]       = '\0';
         lDevicePort         = 8000;
         chLoginUserName[0]  = '\0';
         chLoginPwd[0]       ='\0';
         //chDeviceMultiIP[0]   ='\0';
		 chSerialNumber[0]   = '\0';
		 iDeviceType         = 0;
		 bIsLogin            = FALSE;
	}	 
}LOCAL_DEVICE_INFO,*pLOCAL_DEVICE_INFO;


typedef struct STRU_VOICEMR_INFO{
	int iDeviceIndex;   //设备号
	int iChanIndex;     //语音通道号，1，2
	LONG hVoiceHandle;  //语音句柄

    STRU_VOICEMR_INFO()
	{
        iDeviceIndex = -1;
        iChanIndex = -1;
		hVoiceHandle = -1;
	}
}VOICEMR_INFO,*PVOICEMR_INFO;

#endif