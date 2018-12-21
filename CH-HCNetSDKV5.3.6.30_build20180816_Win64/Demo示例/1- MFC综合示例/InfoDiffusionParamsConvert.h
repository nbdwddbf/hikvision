
#ifndef _INFO_DIFFUSION_PARAMS_CONVERT_H_
#define _INFO_DIFFUSION_PARAMS_CONVERT_H_

#include "XMLParamsConvert.h"

/************************************************************************/
/* 宏定义                                                                 
/************************************************************************/
#define MAX_LEN_32                  32    //长度32
#define MAX_LEN_128                 128   //长度128
#define MAX_LEN_NAME                64    //名称最大长度
#define MAX_LEN_REMARKS             256   //备注最大长度
#define MAX_LEN_URL                 512   //URL最大长度
#define MAX_LEN_TEXT                512   //文本最大长度 
#define MAX_NUM_MATERIAL            1024  //素材最大数量
#define MAX_PAGES_A_PROGRAM         128   //一个节目的页面最大数量
#define MAX_CONTENTS_A_PAGE         32    //一个页面的内容最大数量
#define MAX_NUM_PROGRAM             32    //节目最大数量
#define MAX_NUM_CONTAINER           128   //垫片最大数量
#define MAX_SPANS_A_DAY             8     //一天的播放时段最大数量
#define MAX_NUM_SELDEFINE           32    //自定义时段的最大数量
#define MAX_PROGRAMS_A_LOOP         16    //循环日程的节目最大数量
#define MAX_DAYS_A_WEEK             7     //一周的天数
#define MAX_NUM_SCHEDULE            128   //日程最大数量
#define MAX_NUM_TERMINAL            1024  //终端最大数量
#define MAX_IPCS_A_TERMINAL         32    //一个终端支持的IPC最大数量
#define MAX_CPUS_A_TERMINAL         32    //一个终端的CPU最大个数
#define MAX_MEMS_A_TERMINAL         32    //一个终端的内存最大个数
#define MAX_DISK_A_TERMINAL         32    //一个终端的磁盘最大个数
#define MAX_NUM_TERGROUP            128   //终端组最大数量
#define MAX_TERS_A_GROUP            128   //组内终端最大数量
#define MAX_ITEMS_A_PLAYLIST        8     //播放列表中表项最大数量
#define MAX_NUM_SWITCH_PLAN         32    //开关机计划最大数量
#define MAX_NUM_VOLUME_PLAN         32    //音量计划最大数量

/************************************************************************/
/* 结构体定义                                              
/************************************************************************/
//素材管理
typedef struct tagRGB //RGB
{
	DWORD dwRed;   //红色
	DWORD dwGreen; //绿色
	DWORD dwBlue;  //蓝色
}RGB, *LPRGB;

typedef struct tagNET_DVR_DISP_PARAM
{
	BOOL byEnable;
	DWORD dwFontSize;
	RGB struFontColor;
	RGB struBackColor;
	DWORD dwPositionX;
	DWORD dwPositionY;
	DWORD dwHeight;
	DWORD dwWidth;
}NET_DVR_DISP_PARAM,*LPDVR_DISP_PARAM;

typedef struct tagNET_DVR_CLOCK
{
	DWORD dwTotalHeight;
	DWORD dwTotalWidth;
	DWORD dwBackPicId;
	BOOL byIconEnable;
	char szIconType[MAX_LEN_32];
	DWORD dwIconX;
	DWORD dwIconY;
	DWORD dwIconH;
	DWORD dwIconW;
	NET_DVR_DISP_PARAM struYmd;
	NET_DVR_DISP_PARAM struHms;
	NET_DVR_DISP_PARAM struWeek;
}NET_DVR_CLOCK,*LPNET_DVR_CLOCK;

typedef struct tagNET_DVR_WEATHER
{
	DWORD dwTotalHeight;
	DWORD dwTotalWidth;
	DWORD dwBackPicId;
	BOOL byIconEnable;
	DWORD dwIconX;
	DWORD dwIconY;
	DWORD dwIconH;
	DWORD dwIconW;
	NET_DVR_DISP_PARAM struDate;
	NET_DVR_DISP_PARAM struTemp;
	NET_DVR_DISP_PARAM struContent;
	NET_DVR_DISP_PARAM struCity;
	NET_DVR_DISP_PARAM struHum;
	NET_DVR_DISP_PARAM struAir;
	NET_DVR_DISP_PARAM struUpdate;
	NET_DVR_DISP_PARAM struWind;
}NET_DVR_WEATHER,*LPNET_DVR_WEATHER;

typedef struct tagNET_DVR_STATIC_MATERIAL //静态素材
{
	char  szStaticMaterialType[MAX_LEN_32];   //静态素材类型
	char  szStaticMaterialFormat[MAX_LEN_32]; //静态素材格式
	DWORD dwFileSize;                         //素材文件大小，单位：字节
	DWORD dwDuration;                         //素材时间
	NET_DVR_CLOCK struLock;                    //时钟
	NET_DVR_WEATHER struWeather;              //天气
}NET_DVR_STATIC_MATERIAL, *LPNET_DVR_STATIC_MATERIAL;

typedef struct tagNET_DVR_IPADDR_ //IP地址
{		
    char	szIpV4[16];	 //IPv4地址
    char 	szIpV6[128]; //保留
}NET_DVR_IPADDR_, *LPNET_DVR_IPADDR_;

typedef struct tagNET_DVR_ADDRESS_ //流媒体地址
{
	char  szAddressType[MAX_LEN_32]; //地址类型
	char  szHostName[MAX_LEN_32];    //主机名称
	NET_DVR_IPADDR_ struIPAddr;      //IP地址
	DWORD dwPortNo;                  //端口号
}NET_DVR_ADDRESS_, *LPNET_DVR_ADDRESS_;

typedef struct tagNET_DVR_STREAM_MEDIA //流媒体
{
	NET_DVR_ADDRESS_ struAddress; //流媒体地址
	char szUrl[MAX_LEN_URL];                  //url
}NET_DVR_STREAM_MEDIA, *LPNET_DVR_STREAM_MEDIA;

typedef struct tagNET_DVR_DYNAMIC_MATERIAL //动态素材
{
	char szDynamicMaterialType[MAX_LEN_32]; //动态素材类型
	NET_DVR_STREAM_MEDIA struStreamMedia;   //流媒体
	char szWebUrl[MAX_LEN_URL];             //Web Url
	char szRssUrl[MAX_LEN_URL];             //Rss Url
}NET_DVR_DYNAMIC_MATERIAL, *LPNET_DVR_DYNAMIC_MATERIAL;

typedef struct tagNET_DVR_MATERIAL //素材
{
	DWORD dwSize;
	DWORD dwMaterialID;                           //素材ID
	char  szMaterialName[MAX_LEN_NAME];           //素材名称
	char  szMaterialRemarks[MAX_LEN_REMARKS];     //素材描述
	char  szMaterialType[MAX_LEN_32];             //素材类型
	char  szApprove[MAX_LEN_32];                  //审核
	char  szApproveRemarks[MAX_LEN_REMARKS];      //审核意见
	char  szSharePropery[MAX_LEN_32];             //共享属性
	char  szUploadUser[MAX_LEN_32];               //上传者
	char  szUploadTime[MAX_LEN_32];               //上传时间
	NET_DVR_STATIC_MATERIAL struStaticMaterial;   //静态素材
	NET_DVR_DYNAMIC_MATERIAL struDynamicMaterial; //动态素材
    char szOperatorType[MAX_LEN_32];              //批量设置类型
    DWORD dwOrgNo;
}NET_DVR_MATERIAL, *LPNET_DVR_MATERIAL;

typedef struct tagNET_DVR_MATERIAL_LIST //素材列表
{
	DWORD dwSize;
	NET_DVR_MATERIAL struMaterialList[MAX_NUM_MATERIAL]; //素材列表
}NET_DVR_MATERIAL_LIST, *LPNET_DVR_MATERIAL_LIST;

//节目管理
typedef struct tagNET_DVR_RESOLUTION //分辨率
{
	DWORD dwImageWidth;                 //图像宽度
	DWORD dwImageHeight;                //图像高度
}NET_DVR_RESOLUTION, *LPNET_DVR_RESOLUTION;

typedef struct tagNET_DVR_POSITION //位置
{
	DWORD dwPositionX; //左上角X坐标
	DWORD dwPositionY; //左上角Y坐标
	DWORD dwWidth;     //宽度
	DWORD dwHeight;    //高度
}NET_DVR_POSITION, *LPNET_DVR_POSITION;

typedef struct tagNET_DVR_TEXT //文本
{
	char  szContent[MAX_LEN_TEXT];       //文本内容
	char  szFontType[MAX_LEN_32];        //字体类型
	DWORD dwFontSize;                    //字体大小
	char  szAlign[MAX_LEN_32];           //对齐方式
	DWORD dwRowHeight;                   //行高
	char  szScrollType[MAX_LEN_32];      //滚动类型
	char  szScrollDirection[MAX_LEN_32]; //滚动方向
	DWORD dwScrollSpeed;                 //滚动速度
}NET_DVR_TEXT, *LPNET_DVR_TEXT;

typedef struct tagNET_DVR_MARQUEE //跑马灯
{
	char  szScrollType[MAX_LEN_32];      //滚动类型
	char  szScrollDirection[MAX_LEN_32]; //滚动方向
	DWORD dwScrollSpeed;                 //滚动速度
}NET_DVR_MARQUEE, *LPNET_DVR_MARQUEE;

typedef struct tagNET_DVR_DURATION //播放时间
{
	char  szDurationType[MAX_LEN_32]; //时间类型
	DWORD dwDuration;                 //播放时间
}NET_DVR_DURATION, *LPNET_DVR_DURATION;



typedef struct tagNET_DVR_CHARACTERS_EFECT//文字显示效果
{
	DWORD dwFontSize;                  //字体大小
	RGB struFontColor;                 //字体颜色
	RGB struBackColor;                 //背景颜色
	DWORD dwBackTransparent;           //背景透明度
	BYTE bySubtitlesEnabled;           //使能字符显示模式
	char szScrollDirection[MAX_LEN_32];//文字滚动方向
	DWORD dwScrollSpeed;               //文字滚动速度
}NET_DVR_CHARACTERS_EFECT,*LPNET_DVR_CHARACTERS_EFECT;

typedef struct tagNET_DVR_PLAY_ITEM_ //播放项目 
{
	DWORD dwPlayID;  
	DWORD dwMaterialID;                //素材ID
	char  szPlayEffect[MAX_LEN_32];    //播放效果
	NET_DVR_MARQUEE  struMarquee;      //跑马灯
	NET_DVR_DURATION struPlayDuration; //播放时间 
	NET_DVR_CHARACTERS_EFECT struCharactersEffect;//文字显示效果，当素材类型为文本txt时有效
	char szSwitchEffect[MAX_LEN_32];               //窗口素材切换效果，图片素材时有效
}NET_DVR_PLAY_ITEM_, *LPNET_DVR_PLAY_ITEM_;

typedef struct tagNET_DVR_CONTENT //页面内容
{
	DWORD dwContentID;                     //内容ID
	NET_DVR_POSITION  struPosition;        //内容位置
	DWORD dwLayerID;                       //图层ID
	char  sWinMaterialType[MAX_LEN_32];    //窗口素材类型
	char  sStaticMaterialType[MAX_LEN_32]; //静态素材类型
	NET_DVR_PLAY_ITEM_ struPlayList[MAX_ITEMS_A_PLAYLIST]; //播放列表
}NET_DVR_CONTENT, *LPNET_DVR_CONTENT;



typedef struct tagNET_DVR_PAGE_BASIC //页面基本信息
{
	char  sPageName[MAX_LEN_NAME];       //页面名称
	RGB   struBkColor;                   //背景色
	char  sPlayMode[MAX_LEN_32];         //播放模式
	DWORD dwPlayDuration;                //播放时间
	DWORD dwSwitchDuraton;               //切换时间
	char  szSwitchEffect[MAX_LEN_32];    //切换效果
	DWORD dwBackgroundPic;               //背景图片
}NET_DVR_PAGE_BASIC, *LPNET_DVR_PAGE_BASIC;

typedef struct tagNET_DVR_PAGE //页面
{
	DWORD dwSize;
	DWORD dwPageID;                   //页面ID
	NET_DVR_PAGE_BASIC struBasicInfo; //页面基本信息
	NET_DVR_CONTENT struContentList[MAX_CONTENTS_A_PAGE]; //内容列表
}NET_DVR_PAGE, *LPNET_DVR_PAGE;

typedef struct tagNET_DVR_PAGE_LIST //页面列表
{
	DWORD dwSize;
	NET_DVR_PAGE struPageList[MAX_PAGES_A_PROGRAM]; //页面列表
}NET_DVR_PAGE_LIST, *LPNET_DVR_PAGE_LIST;

typedef struct tagNET_DVR_PROGRAM //节目
{
	DWORD dwSize;
	DWORD dwProgramID;                       //节目ID
	char  szProgramName[MAX_LEN_NAME];       //节目名称
	char  szProgramRemarks[MAX_LEN_REMARKS]; //节目备注
	char  szShareProp[MAX_LEN_32];           //共享属性
	char  szApprove[MAX_LEN_32];             //审核
	char  szApproveRemarks[MAX_LEN_REMARKS]; //审核意见
	NET_DVR_RESOLUTION struResolution;       //分辨率
	DWORD dwProgramSize;                     //节目总大小
	DWORD dwProgramLength;                   //节目总时长
	NET_DVR_PAGE_LIST  struPageList;         //页面列表
    char szOperatorType[MAX_LEN_32];         //批量配置类型
}NET_DVR_PROGRAM, *LPNET_DVR_PROGRAM;

typedef struct tagNET_DVR_PROGRAM_LIST //节目列表
{
	DWORD dwSize;
	NET_DVR_PROGRAM struProgramList[MAX_NUM_PROGRAM]; //节目列表
}NET_DVR_PROGRAM_LIST, *LPNET_DVR_PROGRAM_LIST;

typedef struct tagNET_DVR_CONTAINER //垫片
{
	DWORD dwSize;
	DWORD dwContainerID; //垫片ID
	char  szContainerName[MAX_LEN_NAME]; //垫片名称
	DWORD dwPlayDuration;                //播放时间
	DWORD dwSwitchTime;                  //切换时间
	char  szSwitchEffect[MAX_LEN_32];    //切换效果
}NET_DVR_CONTAINER, *LPNET_DVR_CONTAINER;

typedef struct tagNET_DVR_CONTAINER_LIST //垫片列表
{
	DWORD dwSize;
	NET_DVR_CONTAINER struContainerList[MAX_NUM_CONTAINER]; //垫片列表
}NET_DVR_CONTAINER_LIST, *LPNET_DVR_CONTAINER_LIST;

//日程管理
typedef struct tagNET_DVR_TIME_ //时间
{
    DWORD dwYear;		//年
    DWORD dwMonth;		//月
    DWORD dwDay;		//日
    DWORD dwHour;		//时
    DWORD dwMinute;		//分
    DWORD dwSecond;		//秒
}NET_DVR_TIME_, *LPNET_DVR_TIME_;

typedef struct tagNET_DVR_TIME_RANGE //时间段
{
	NET_DVR_TIME_ struBeginTime; //开始时间
	NET_DVR_TIME_ struEndTime;   //结束时间
}NET_DVR_TIME_RANGE, *LPNET_DVR_TIME_RANGE;

typedef struct tagNET_DVR_PLAY_SPAN //时段播放
{
	DWORD dwSpanID;    //时段ID
	DWORD dwProgramID; //关联的节目ID
	NET_DVR_TIME_RANGE struTimeRange; //时间段
}NET_DVR_PLAY_SPAN, *LPNET_DVR_PLAY_SPAN;

typedef struct tagNET_DVR_PLAY_DAY //按天播放
{
	DWORD dwDayID;               //天ID
	char  szWeekday[MAX_LEN_32]; //周几
	NET_DVR_PLAY_SPAN struSpanList[MAX_SPANS_A_DAY]; //时段列表
}NET_DVR_PLAY_DAY, *LPNET_DVR_PLAY_DAY;

typedef struct tagNET_DVR_PLAY_SELDEFINE //自定义播放
{
	DWORD dwSeldefineID; //自定义编号
	DWORD dwProgramID;   //节目ID
	NET_DVR_TIME_RANGE struTimeRange; //时间段
}NET_DVR_PLAY_SELDEFINE, *LPNET_DVR_PLAY_SELDEFINE;

typedef struct tagNET_DVR_PLAY_LOOP //循环播放
{
	DWORD dwLoopID;    //循环节点ID
	DWORD dwProgramID; //节目ID
}NET_DVR_PLAY_LOOP, *LPNET_DVR_PLAY_LOOP;

typedef struct tagNET_DVR_PLAY_SCHEDULE //日程
{
	DWORD dwSize;
	DWORD dwScheduleID;                       //日程ID
	char  szScheduleName[MAX_LEN_NAME];       //日程名称
	char  szScheduleRemarks[MAX_LEN_REMARKS]; //日程备注
	char  szScheduleType[MAX_LEN_32];         //日程类型
	char  szApprove[MAX_LEN_32];              //审核
	char  szApproveRemarks[MAX_LEN_REMARKS];  //审核意见
	char  szShareProp[MAX_LEN_32];            //共享属性
    char szScheduleMode[MAX_LEN_32];
    DWORD dwOrgNo;
	NET_DVR_PLAY_SPAN struDailySchedule[MAX_SPANS_A_DAY];            //天日程
	NET_DVR_PLAY_DAY struWeeklySchedule[MAX_DAYS_A_WEEK];            //周日程
	NET_DVR_PLAY_LOOP struLoopSchedule[MAX_PROGRAMS_A_LOOP];         //节目循环日程
	NET_DVR_PLAY_SELDEFINE struSeldefineSchedule[MAX_NUM_SELDEFINE]; //自定义日程
}NET_DVR_PLAY_SCHEDULE, *LPNET_DVR_PLAY_SCHEDULE;


typedef struct tagNET_DVR_SCHEDULE_RELEASE //日程发布
{
	DWORD dwSize;
	DWORD dwScheduleID;                          //日程ID
	char  szReleaseType[MAX_LEN_32];             //发布类型
	DWORD dwTerminalCount;                       //终端数量
	DWORD dwGroupCount;                          //终端组数量
	DWORD dwTerminalList[MAX_NUM_TERMINAL];      //终端列表
	DWORD dwTerminalGroupList[MAX_NUM_TERGROUP]; //终端组列表
    char  szEffectTime[MAX_LEN_32];
}NET_DVR_SCHEDULE_RELEASE, *LPNET_DVR_SCHEDULE_RELEASE;

//播放控制
typedef struct tagNET_DVR_INSERT_INFO //插入信息
{
	char  szInsertType[MAX_LEN_32]; //插入类型
	DWORD dwMaterialID;             //素材编号
	DWORD dwProgramID;              //节目编号
	char  szPlayMode[MAX_LEN_32];   //控制模式
	DWORD dwCount;                  //播放次数
	DWORD dwDuration;               //播放时间
	DWORD dwPositionX;              //左上角X坐标
	DWORD dwPositionY;              //左上角Y坐标
	DWORD dwPositionWidth;          //宽度
	DWORD dwPostionHeight;          //高度
	NET_DVR_CHARACTERS_EFECT struChacEff;//播放显示效果
    char  szEndTime[MAX_LEN_32];
}NET_DVR_INSERT_INFO, *LPNET_DVR_INSERT_INFO;

typedef struct tagNET_DVR_PLAN_CTRL
{
	char szPlanType[MAX_LEN_32];             //计划类型
	BYTE byEnable;               //计划启停
}NET_DVR_PLAN_CTRL,*LPNET_DVR_PLAN_CTRL;

typedef struct tagNET_DVR_PLAY_CONTROL //播放控制
{
	DWORD dwSize;
	char  szControlType[MAX_LEN_32];             //控制类型
	char  szTargetType[MAX_LEN_32];              //目标类型
	DWORD dwTerminalCount;                       //终端数量
	DWORD dwGroupCount;                          //终端组数量
	DWORD dwTerminalList[MAX_NUM_TERMINAL];      //终端列表
	DWORD dwTerminalGroupList[MAX_NUM_TERGROUP]; //终端组列表
	NET_DVR_INSERT_INFO struInsertInfo;          //插入信息
	NET_DVR_PLAN_CTRL  struPlanCtrl;             //计划控制
}NET_DVR_PLAY_CONTROL, *LPNET_DVR_PLAY_CONTROL;

//终端组
typedef struct tagNET_DVR_TERMINAL_GROUP //终端组
{
	DWORD dwSize;                  
	DWORD dwGroupID;               //组ID
	char  szGroupName[MAX_LEN_32]; //组名称
	DWORD dwTermCount;             //组内终端数量
	DWORD dwTerminalList[MAX_TERS_A_GROUP]; //终端列表
}NET_DVR_TERMINAL_GROUP, *LPNET_DVR_TERMINAL_GROUP;

typedef struct tagNET_DVR_TERMINAL_GROUP_LIST //终端组列表
{
	DWORD dwSize;
	NET_DVR_TERMINAL_GROUP struGroupList[MAX_NUM_TERGROUP]; //终端组列表
}NET_DVR_TERMINAL_GROUP_LIST, *LPNET_DVR_TERMINAL_GROUP_LIST;


typedef struct tagNET_DVR_PUBLISH_SERVER_ADDR
{
    DWORD dwSize;
    char szFormatType[MAX_LEN_32]; //地址类型
    char szHostName[MAX_LEN_32]; //主机名
    char szIpv4[128]; //Ipv4
    char szIpv6[128]; //Ipv6
    WORD wPort; //端口号
    char szOparaType[MAX_LEN_32]; //设置对象
    BOOL byRegister; //注册状态
    DWORD dwTerminalNo;//终端个数
    DWORD arrTerminal[MAX_NUM_TERMINAL];
    DWORD dwGroupNo;//终端组个数
    DWORD arrGroup[MAX_NUM_TERGROUP];//终端组编号
    char szUserName[MAX_LEN_32]; 
    char szPwd[MAX_LEN_32]; 
}NET_DVR_PUBLISH_SERVER_ADDR,*LPNET_DVR_PUBLISH_SERVER_ADDR;


//播放配置
typedef struct tagNET_DVR_SCREEN_PARAM //屏幕参数
{
	DWORD dwBackLightLevel;  //背光参数
	BYTE  byBootLogoEnabled;  //开机logo是否显示
}NET_DVR_SCREEN_PARAM, *LPNET_DVR_SCREEN_PARAM;

typedef struct tagNET_DVR_PLAY_CFG //播放配置
{
	DWORD dwSize;
	DWORD dwTerminalID;   //终端ID
	DWORD dwPlayerVolume; //播放器音量
	NET_DVR_SCREEN_PARAM struScreenParam; //屏幕参数
}NET_DVR_PLAY_CFG, *LPNET_DVR_PLAY_CFG;

typedef struct tagNET_DVR_PLAY_CFG_LIST //播放配置列表
{
	DWORD dwSize;
	NET_DVR_PLAY_CFG struPlayCfgList[MAX_NUM_TERMINAL]; //终端的播放配置
}NET_DVR_PLAY_CFG_LIST, *LPNET_DVR_PLAY_CFG_LIST;

//开关机计划
typedef struct tagNET_DVR_SWITCH_SPAN //开关机时间
{
	DWORD dwSpanID;                //ID
	char  sSwitchType[MAX_LEN_32]; //开机/关机
	NET_DVR_TIME_ struTime;        //时间
}NET_DVR_SWITCH_SPAN, LPNET_DVR_SWITCH_SPAN;

typedef struct tagNET_DVR_SWITCH_DAY //日开关机时间
{
	DWORD dwDayID;              //ID
	char  sWeekday[MAX_LEN_32]; //周几
	NET_DVR_SWITCH_SPAN struSpanList[MAX_SPANS_A_DAY]; //时间列表
}NET_DVR_SWITCH_DAY, *LPNET_DVR_SWITCH_DAY;

typedef struct tagNET_DVR_SWITCH_PLAN //开关机计划
{
	DWORD dwSize;
	char  sPlanType[MAX_LEN_32];   //计划类型
	NET_DVR_SWITCH_SPAN struDailyPlan[MAX_SPANS_A_DAY];        //日计划
	NET_DVR_SWITCH_DAY  struWeekyPlan[MAX_DAYS_A_WEEK];        //周计划
	NET_DVR_SWITCH_SPAN struSelfdefinePlan[MAX_NUM_SELDEFINE]; //自定义计划
}NET_DVR_SWITCH_PLAN, *LPNET_DVR_SWITCH_PLAN;

typedef struct tagNET_DVR_SWITCH_PLAN_LIST //开关机配置列表
{
	DWORD dwSize;
	NET_DVR_SWITCH_PLAN struSwitchPlanList[MAX_NUM_SWITCH_PLAN];
}NET_DVR_SWITCH_PLAN_LIST, *LPNET_DVR_SWITCH_PLAN_LIST;

typedef struct tagNET_DVR_SWITCH_PLAN_CFG
{
    DWORD dwSize;
    NET_DVR_SWITCH_PLAN struSwitchPlan;
    char szOperType[MAX_LEN_NAME]; //操作类型
    DWORD dwGroupNo; //终端组个数
    DWORD dwListGroup[MAX_NUM_TERGROUP];
    DWORD dwTerminalNo; //终端个数
    DWORD dwListTerminal[MAX_NUM_TERMINAL];

}NET_DVR_SWITCH_PLAN_CFG,*LPNET_DVR_SWITCH_PLAN_CFG;


typedef struct tagNET_DVR_VOLUME_SPAN //开关机时间
{
    DWORD dwSpanID;                //ID
    DWORD  dwVolume;               //音量
    NET_DVR_TIME_ struTime;        //时间
    NET_DVR_TIME_ struTimeEnd;
}NET_DVR_VOLUME_SPAN, LPNET_DVR_VOLUME_SPAN;

typedef struct tagNET_DVR_VOLUME_DAY //日开关机时间
{
    DWORD dwDayID;              //ID
    char  sWeekday[MAX_LEN_32]; //周几
    NET_DVR_VOLUME_SPAN struSpanList[MAX_SPANS_A_DAY]; //时间列表
}NET_DVR_VOLUME_DAY, *LPNET_DVR_VOLUME_DAY;

typedef struct tagNET_DVR_VOLUME_PLAN //音量机计划
{
    DWORD dwSize;
    char  sPlanType[MAX_LEN_32];   //计划类型
    NET_DVR_VOLUME_SPAN struDailyPlan[MAX_SPANS_A_DAY];        //日计划
    NET_DVR_VOLUME_DAY  struWeekyPlan[MAX_DAYS_A_WEEK];        //周计划
}NET_DVR_VOLUME_PLAN, *LPNET_DVR_VOLUME_PLAN;


typedef struct tagNET_DVR_VOLUME_PLAN_LIST //开关机配置列表
{
    DWORD dwSize;
    NET_DVR_VOLUME_PLAN struVolumePlanList[MAX_NUM_VOLUME_PLAN];
}NET_DVR_VOLUME_PLAN_LIST, *LPNET_DVR_VOLUME_PLAN_LIST;

typedef struct tagNET_DVR_VOLUME_PLAN_CFG
{
    DWORD dwSize;
    NET_DVR_VOLUME_PLAN struVolumePlan;
    char szOperType[MAX_LEN_32];
    DWORD dwTerminalNo;
    DWORD dwListTerminal[MAX_NUM_TERMINAL];
    DWORD dwGroupNo;
    DWORD dwListGroup[MAX_NUM_TERGROUP];
}NET_DVR_VOLUME_PLAN_CFG,*LPNET_DVR_VOLUME_PLAN_CFG;

typedef struct tagNET_DVR_MATERIAL_SEARCH_DESCRIPTION //素材查询条件
{
	char  sSearchID[MAX_LEN_32];            //搜索ID
	char  sApproveState[MAX_LEN_32];        //审核状态
	char  sMaterialType[MAX_LEN_32];        //素材类型
	char  sShareProperty[MAX_LEN_32];       //共享属性
	char  sUploader[MAX_LEN_32];            //上传者
	char  sStaticMaterialType[MAX_LEN_32];  //静态素材类型
	DWORD dwMinStaticMaterialSize;          //静态素材大小最小值
	DWORD dwMaxStaticMaterialSize;          //静态素材大小最大值
	char  sDynamicMaterialType[MAX_LEN_32]; //动态素材类型
	NET_DVR_TIME_RANGE struTimeRange;       //查询时间范围
	DWORD dwMaxResults;                     //最多返回的素材数量
	DWORD dwSearchResultsPosition;          //从查询结果中指定位置开始返回素材信息
}NET_DVR_MATERIAL_SEARCH_DESCRIPTION, *LPNET_DVR_MATERIAL_SEARCH_DESCRIPTION;

typedef struct tagNET_DVR_MATERIAL_SEARCH_RESULT //素材查询结果
{
	char  sSearchID[MAX_LEN_32];             //搜索ID
	BOOL  bResponseStatus;                   //查询状态
	char  sResponseStatusString[MAX_LEN_32]; //查询状态字符串
	DWORD dwTotalMatches;                    //查询到的素材总数量
	DWORD dwNumOfMatches;                    //返回的素材数量
	NET_DVR_MATERIAL struMaterialList[MAX_NUM_MATERIAL]; //素材列表
}NET_DVR_MATERIAL_SEARCH_RESULT, *LPNET_DVR_MATERIAL_SEARCH_RESULT;

typedef struct tagNET_DVR_PROGRAM_SEARCH_DESCRIPTION //节目查询条件
{
	char  sSearchID[MAX_LEN_32];            //搜索ID
	char  sApproveState[MAX_LEN_32];        //审核状态
	char  sShareProperty[MAX_LEN_32];       //共享属性
	char  sUploader[MAX_LEN_32];            //上传者
	NET_DVR_RESOLUTION struResolution;      //节目分辨率
	NET_DVR_TIME_RANGE struTimeRange;       //查询时间范围
	DWORD dwMaxResults;                     //最多返回的节目数量
	DWORD dwSearchResultsPosition;          //从查询结果中指定位置开始返回节目信息
}NET_DVR_PROGRAM_SEARCH_DESCRIPTION, *LPNET_DVR_PROGRAM_SEARCH_DESCRIPTION;

typedef struct tagNET_DVR_PROGRAM_BASIC_INFO //节目基本信息
{
	DWORD dwProgramID;                       //节目ID
	char  szProgramName[MAX_LEN_NAME];       //节目名称
	char  szProgramRemarks[MAX_LEN_REMARKS]; //节目备注
	char  szShareProp[MAX_LEN_32];           //共享属性
	char  szApprove[MAX_LEN_32];             //审核
	char  szApproveRemarks[MAX_LEN_REMARKS]; //审核意见
	NET_DVR_RESOLUTION struResolution;       //分辨率
	DWORD dwProgramSize;                     //节目总大小
	DWORD dwProgramLength;                   //节目总时长
}NET_DVR_PROGRAM_BASIC_INFO, *LPNET_DVR_PROGRAM_BASIC_INFO;

typedef struct tagNET_DVR_PROGRAM_SEARCH_RESULT //节目查询结果
{
	char  sSearchID[MAX_LEN_32];             //搜索ID
	BOOL  bResponseStatus;                   //查询状态
	char  sResponseStatusString[MAX_LEN_32]; //查询状态字符串
	DWORD dwTotalMatches;                    //查询到的节目总数量
	DWORD dwNumOfMatches;                    //返回的节目数量
	NET_DVR_PROGRAM_BASIC_INFO struProgramList[MAX_NUM_PROGRAM]; //节目列表
}NET_DVR_PROGRAM_SEARCH_RESULT, *LPNET_DVR_PROGRAM_SEARCH_RESULT;

typedef struct tagNET_DVR_SCHEDULE_SEARCH_DESCRIPTION //日程查询条件
{
	char  sSearchID[MAX_LEN_32];            //搜索ID
	char  sApproveState[MAX_LEN_32];        //审核状态
	char  sShareProperty[MAX_LEN_32];       //共享属性
	char  sUploader[MAX_LEN_32];            //上传者
	char  sScheduleType[MAX_LEN_32];        //日程类型
	NET_DVR_TIME_RANGE struTimeRange;       //查询时间范围
	DWORD dwMaxResults;                     //最多返回的日程数量
	DWORD dwSearchResultsPosition;          //从查询结果中指定位置开始返回日程信息
}NET_DVR_SCHEDULE_SEARCH_DESCRIPTION, *LPNET_DVR_SCHEDULE_SEARCH_DESCRIPTION;

typedef struct tagNET_DVR_SCHEDULE_BASIC_INFO //日程基本信息
{
	DWORD dwScheduleID;                       //日程ID
	char  szScheduleName[MAX_LEN_NAME];       //日程名称
	char  szScheduleRemarks[MAX_LEN_REMARKS]; //日程备注
	char  szScheduleType[MAX_LEN_32];         //日程类型
	char  szApprove[MAX_LEN_32];              //审核
	char  szApproveRemarks[MAX_LEN_REMARKS];  //审核意见
	char  szShareProp[MAX_LEN_32];            //共享属性
}NET_DVR_SCHEDULE_BASIC_INFO, *LPNET_DVR_SCHEDULE_BASIC_INFO;

typedef struct tagNET_DVR_SCHEDULE_SEARCH_RESULT //日程查询结果
{
	char  sSearchID[MAX_LEN_32];             //搜索ID
	BOOL  bResponseStatus;                   //查询状态
	char  sResponseStatusString[MAX_LEN_32]; //查询状态字符串
	DWORD dwTotalMatches;                    //查询到的日程总数量
	DWORD dwNumOfMatches;                    //返回的日程数量
	NET_DVR_SCHEDULE_BASIC_INFO struScheduleList[MAX_NUM_SCHEDULE]; //日程列表
}NET_DVR_SCHEDULE_SEARCH_RESULT, *LPNET_DVR_SCHEDULE_SEARCH_RESULT;

/************************************************************************/
/* 转换函数                                                             */
/************************************************************************/
//提取ResponseStatus中的状态码字符串
char* GetStatusCodeInfo(const DWORD dwStatusCide);

//提取ResponseStatus的ID
DWORD GetResponseStatusID(const char* pXmlBuf);

//素材
BOOL ConvertMaterialParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertMaterialParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertMaterialParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertMaterialParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertMaterialSearchDescriptionParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertMaterialSearchResultXmlToStru(const char* pXmlBuf, LPVOID pStruct);

//页面
BOOL ConvertPageParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertPageParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertPageParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertPageParamsStruToXml(LPVOID pStruct, CXmlBase& struXml);
BOOL ConvertPageParamsXmlToStruList(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertPageParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertPageParamsStruToXmlList(LPVOID pStruct, CXmlBase& struXml);

//节目
BOOL ConvertProgramParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertProgramParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertProgramParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertProgramParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertProgramSearchDescriptionParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertProgramSearchResultParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);

//垫片
BOOL ConvertContainerParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertContainerParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertContainerParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertContainerParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct);

//日程
BOOL ConvertTimeNodeData(CXmlBase &struXml, LPVOID pStruct, const char* pNodeName, BOOL bXmlToStru);
BOOL ConvertScheduleParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertScheduleParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertScheduleParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertScheduleReleaseParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertScheduleSearchDescriptionParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertScheduleSearchResultParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);

//播放控制
BOOL ConvertPlayControlParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);

//终端组
BOOL ConvertTermGrpParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertTermGrpParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertTermGrpParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertTermGrpParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct);

//播放配置
BOOL ConvertPlayParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertPlayParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertPlayParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertPlayParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct);

//开关机计划
BOOL ConvertSwitchPlanXmlToStru(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertSwitchPlanXmlToStru(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertSwitchPlanStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertSwitchPlanXmlToStruList(const char* pXmlBuf, LPVOID pStruct);

 
BOOL ConvertClockParam(NET_DVR_CLOCK &struLock,CXmlBase &struXml);			
BOOL ConvertWeatherParam(NET_DVR_WEATHER &struWeather,CXmlBase &struXml);
BOOL AddClockNode(NET_DVR_DISP_PARAM &struDisp,CXmlBase &struXml);

BOOL ConvertPlanParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertPlanParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertSwitchPlanListParamsXmlToStruList(const char *pXmlBuf,LPVOID pStruct);
BOOL ConvertPlanParamStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertVolumePlanParamStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertVolumePlanParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct);
BOOL ConvertVolumePlanParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);
BOOL ConvertVolumePlanListParamsXmlToStruList(const char *pXmlBuf,LPVOID pStruct);

BOOL ConvertTermServerParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertTerServerParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct);

BOOL ConvertProgramIdToXml(LPVOID pStruct, int count,char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertMaterialIdToXml(LPVOID pStruct, int count, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertMaterialBatchInfoToXml(LPVOID ArrayId, int CountId, LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertScheduleIdToXml(LPVOID pStruct, int count, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertTerminalIdToXml(LPVOID pStruct, int Count, char* *pXmlBuf, DWORD &dwXmlLen);
BOOL ConvertProgramBatchInfoToXml(LPVOID ArrayId, int CountId, LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen);

#endif //_INFO_DIFFUSION_PARAMS_CONVERT_H_