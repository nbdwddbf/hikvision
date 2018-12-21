
#ifndef _LOCALCONFIGFILE_H_
#define _LOCALCONFIGFILE_H_

#include "DeviceCfgFile.h"

/**   @class LocalConfigFile
*    @brief 本地配置文件类,该类为单例类
*/
class LocalConfigFile
{
public:
    static LocalConfigFile& GetInstance();
    void SaveToFile();
    void ReadFromFile();
private:
    LocalConfigFile();
    ~LocalConfigFile();
    LocalConfigFile(const LocalConfigFile&);
    LocalConfigFile& operator=(const LocalConfigFile&);

    const static char* c_strNode_CycleTime;             //cycle time
    const static char* c_strNode_CyclePlay;             //cycle play
    const static char* c_strNode_UseCard;               //hadrware decode
    const static char* c_strNode_NTSC;                  //hardware decode mode
    const static char* c_strNode_RecordFileInterval;    //record file interval
    const static char* c_strNode_AutoRecord;            //auto record
    const static char* c_strNode_CycleRecord;           //cycle record
    const static char* c_strNode_StartRecordDriver;     //client record starting HD dirve
    const static char* c_strNode_EndRecordDriver;       //client record stop HD drive
    const static char* c_strNode_DownLoadPath;          //remote file download directory
    const static char* c_strNode_PictureSavePath;       //image capture directory
    const static char* c_strNode_RemoteCfgSavePath;     //remote config file saving directory
    const static char* c_strNode_AutoCheckDeviceTime;   //check time with device
    const static char* c_strNode_CheckDeviceTime;       //check time interval
    const static char* c_strNode_AlarmDelayTime;        //alarm delay time
    const static char* c_strNode_AlarmListenPort;       //alarm listen port
    const static char* c_strNode_AutoSaveLog;           //auto save local log info
    const static char* c_strNode_AlarmInfo;             //display alarm info on log list
    const static char* c_strNode_SuccLog;               //display log access on log list
    const static char* c_strNode_FailLog;               //display filaure operation on log list
    const static char* c_strNode_NoDecode;              //soft decode or not
    const static char* c_strNode_PreviewBlock;          //preview block or not
    const static char* c_strNode_OutputDebugString;     //output debug string or not
    const static char* c_strNode_BFrameNum;             //throw B frame number
    const static char* c_strNode_InSide;                //callback decode
    const static char* c_strNode_LogLevel;              //log level
    const static char* c_strNode_StandardCB;            //standard CB
    const static char* c_strNode_Timeout;               //time out
    const static char* c_strNode_RecordTimes;           //record time array

    const static char* c_strNode_StartTime;             //start time
    const static char* c_strNode_StopTime;              //stop time

    const static char* c_strNode_HourDiffWithUTC;             //time difference from UTC (HOUR)
    const static char* c_strNode_MinDiffWithUTC;              //time difference from UTC (Minute)
    const static char* c_strNode_ISO8601;              //time difference from UTC (Minute)
};
#endif
