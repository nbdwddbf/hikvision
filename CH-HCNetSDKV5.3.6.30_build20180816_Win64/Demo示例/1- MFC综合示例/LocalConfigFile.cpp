
#include "stdafx.h"
#include "LocalConfigFile.h"
#include "ClientDemo.h"

const char* LocalConfigFile::c_strNode_CycleTime = _T("CycleTime");
const char* LocalConfigFile::c_strNode_CyclePlay = _T("CyclePlay");
const char* LocalConfigFile::c_strNode_UseCard = _T("UseCard");
const char* LocalConfigFile::c_strNode_NTSC = _T("NTSC");
const char* LocalConfigFile::c_strNode_RecordFileInterval = _T("RecordFileInterval");
const char* LocalConfigFile::c_strNode_AutoRecord = _T("AutoRecord");
const char* LocalConfigFile::c_strNode_CycleRecord = _T("CycleRecord");
const char* LocalConfigFile::c_strNode_StartRecordDriver = _T("StartRecordDriver");
const char* LocalConfigFile::c_strNode_EndRecordDriver = _T("EndRecordDriver");
const char* LocalConfigFile::c_strNode_DownLoadPath = _T("DownLoadPath");
const char* LocalConfigFile::c_strNode_PictureSavePath = _T("PictureSavePath");
const char* LocalConfigFile::c_strNode_RemoteCfgSavePath = _T("RemoteCfgSavePath");
const char* LocalConfigFile::c_strNode_AutoCheckDeviceTime = _T("AutoCheckDeviceTime");
const char* LocalConfigFile::c_strNode_CheckDeviceTime = _T("CheckDeviceTime");
const char* LocalConfigFile::c_strNode_AlarmDelayTime = _T("AlarmDelayTime");
const char* LocalConfigFile::c_strNode_AlarmListenPort = _T("AlarmListenPort");
const char* LocalConfigFile::c_strNode_AutoSaveLog = _T("AutoSaveLog");
const char* LocalConfigFile::c_strNode_AlarmInfo = _T("AlarmInfo");
const char* LocalConfigFile::c_strNode_SuccLog = _T("SuccLog");
const char* LocalConfigFile::c_strNode_FailLog = _T("FailLog");
const char* LocalConfigFile::c_strNode_NoDecode = _T("NoDecode");
const char* LocalConfigFile::c_strNode_PreviewBlock = _T("PreviewBlock");
const char* LocalConfigFile::c_strNode_OutputDebugString = _T("OutputDebugString");
const char* LocalConfigFile::c_strNode_BFrameNum = _T("BFrameNum");
const char* LocalConfigFile::c_strNode_InSide = _T("InSide");
const char* LocalConfigFile::c_strNode_LogLevel = _T("LogLevel");
const char* LocalConfigFile::c_strNode_StandardCB = _T("StandardCB");
const char* LocalConfigFile::c_strNode_Timeout = _T("Timeout");
const char* LocalConfigFile::c_strNode_RecordTimes = _T("RecordTimes");
const char* LocalConfigFile::c_strNode_StartTime = _T("StartTime");
const char* LocalConfigFile::c_strNode_StopTime = _T("StopTime");
const char* LocalConfigFile::c_strNode_HourDiffWithUTC = _T("HourDiffWithUTC");
const char* LocalConfigFile::c_strNode_MinDiffWithUTC = _T("MinDiffWithUTC");
const char* LocalConfigFile::c_strNode_ISO8601 = _T("ISO8601");


/** @fn LocalConfigFile& LocalConfigFile::GetInstance()
*  @brief 获取LocalConfigFile的单例引用
*  @return LocalConfigFile&
*/
LocalConfigFile& LocalConfigFile::GetInstance()
{
    static LocalConfigFile localConfigFile;
    return localConfigFile;
}

/** @fn  LocalConfigFile::LocalConfigFile()
*  @brief
*  @return none
*/
LocalConfigFile::LocalConfigFile()
{}

/** @fn  LocalConfigFile::~LocalConfigFile()
*  @brief
*  @return none
*/
LocalConfigFile::~LocalConfigFile()
{}

void LocalConfigFile::SaveToFile()
{
    CStdioFile myFile;
    CString csFilename;
    BOOL bSucc = FALSE;
    cJSON* pRoot = NULL;
    cJSON* pRecordTimes = NULL;
    cJSON* pRecordTime = NULL;

    csFilename.Format(_T("%s\\DemoLocalCfg.json"), g_szWorkDir);
    if (myFile.Open(csFilename, CFile::modeCreate | CFile::modeWrite) == FALSE)
    {
        return;
    }

    pRoot = cJSON_CreateObject();
    if (pRoot == NULL)
    {
        return;
    }

    do
    {
        cJSON_AddNumberToObject(pRoot, c_strNode_CycleTime, g_struLocalParam.iCycleTime);
        cJSON_AddNumberToObject(pRoot, c_strNode_CyclePlay
                                , g_struLocalParam.bCyclePlay == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_UseCard
                                , g_struLocalParam.bUseCard == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_NTSC
                                , g_struLocalParam.bNTSC == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_RecordFileInterval
                                , g_struLocalParam.iRecordFileInterval);
        cJSON_AddNumberToObject(pRoot, c_strNode_AutoRecord
                                , g_struLocalParam.bAutoRecord == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_CycleRecord
                                , g_struLocalParam.bCycleRecord == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_StartRecordDriver
                                , g_struLocalParam.iStartRecordDriver);
        cJSON_AddNumberToObject(pRoot, c_strNode_EndRecordDriver
                                , g_struLocalParam.iEndRecordDriver);
        cJSON_AddStringToObject(pRoot, c_strNode_DownLoadPath, g_struLocalParam.chDownLoadPath);
        cJSON_AddStringToObject(pRoot, c_strNode_PictureSavePath, g_struLocalParam.chPictureSavePath);
        cJSON_AddStringToObject(pRoot, c_strNode_RemoteCfgSavePath, g_struLocalParam.chRemoteCfgSavePath);
        cJSON_AddNumberToObject(pRoot, c_strNode_AutoCheckDeviceTime, g_struLocalParam.bAutoCheckDeviceTime);
        cJSON_AddNumberToObject(pRoot, c_strNode_CheckDeviceTime
                                , g_struLocalParam.lCheckDeviceTime != 0 ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_AlarmDelayTime, g_struLocalParam.iAlarmDelayTime);
        cJSON_AddNumberToObject(pRoot, c_strNode_AlarmListenPort, g_struLocalParam.iAlarmListenPort);
        cJSON_AddNumberToObject(pRoot, c_strNode_AutoSaveLog
                                , g_struLocalParam.bAutoSaveLog == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_AlarmInfo
                                , g_struLocalParam.bAlarmInfo == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_SuccLog
                                , g_struLocalParam.bSuccLog == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_FailLog
                                , g_struLocalParam.bFailLog == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_NoDecode
                                , g_struLocalParam.bNoDecode == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_PreviewBlock
                                , g_struLocalParam.bPreviewBlock == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_OutputDebugString
                                , g_struLocalParam.bOutputDebugString == TRUE ? 1 : 0);

        cJSON* pRecordTimes = cJSON_CreateArray();
        if (pRecordTimes == NULL)
        {
            break;
        }

        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cJSON* pRecordTime = cJSON_CreateObject();
                if (pRecordTime == NULL)
                {
                    break;
                }
                cJSON_AddNumberToObject(pRecordTime, c_strNode_StartTime
                                        , g_struLocalParam.struLocalRecordTime[i][j].iStartTime);
                cJSON_AddNumberToObject(pRecordTime, c_strNode_StopTime
                                        , g_struLocalParam.struLocalRecordTime[i][j].iStopTime);
                cJSON_AddItemToArray(pRecordTimes, pRecordTime);
            }
        }
        cJSON_AddItemToObject(pRoot, c_strNode_RecordTimes, pRecordTimes);

        cJSON_AddNumberToObject(pRoot, c_strNode_BFrameNum, g_struLocalParam.dwBFrameNum);
        cJSON_AddNumberToObject(pRoot, c_strNode_InSide
                                , g_bInSide == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_LogLevel, g_struLocalParam.nLogLevel);
        cJSON_AddNumberToObject(pRoot, c_strNode_StandardCB
                                , g_bStandardCB == TRUE ? 1 : 0);
        cJSON_AddNumberToObject(pRoot, c_strNode_Timeout, g_struLocalParam.nTimeout);
        cJSON_AddNumberToObject(pRoot, c_strNode_HourDiffWithUTC, g_iHourDiffWithUTC);
        cJSON_AddNumberToObject(pRoot, c_strNode_MinDiffWithUTC, g_iMinDiffWithUTC);
        cJSON_AddNumberToObject(pRoot, c_strNode_ISO8601, g_bISO8601);

        bSucc = TRUE;
    } while (0);

    if (bSucc)
    {
        char* strOut = cJSON_Print(pRoot);
        myFile.WriteString(CString(strOut));
        cJSON_Delete(pRoot);
        free(strOut);
    }
    else
    {
        if (NULL != pRecordTime)
        {
            cJSON_Delete(pRecordTime);
            pRecordTime = NULL;
        }
        if (NULL != pRecordTimes)
        {
            cJSON_Delete(pRecordTimes);
            pRecordTimes = NULL;
        }
        if (NULL != pRoot)
        {
            cJSON_Delete(pRoot);
            pRoot = NULL;
        }
    }
    myFile.Close();
}

void LocalConfigFile::ReadFromFile()
{
    CStdioFile myFile;
    CString csFilename;

    csFilename.Format(_T("%s\\DemoLocalCfg.json"), g_szWorkDir);
    if (myFile.Open(csFilename, CFile::modeRead | CFile::typeBinary) == FALSE)
    {
        myFile.Open(csFilename, CFile::modeCreate);
        return;
    }

    ULONGLONG ullFileLen = myFile.GetLength() + 1;
    char* strConfig = new char[ullFileLen]();
    myFile.Seek(SEEK_SET, 0);
    if (myFile.Read(strConfig, ullFileLen - 1) == FALSE)
    {
        delete[] strConfig;
        myFile.Close();
        return;
    }

    myFile.Close();
    cJSON* pRoot = cJSON_Parse(strConfig);
    delete[] strConfig;
    if (pRoot == NULL)
    {
        return;
    }

    do 
    {
        int nTmp = 0;
        if (GetNodeVal_JSON(pRoot, c_strNode_CycleTime, &nTmp) == FALSE)
        {
            break;
        }
        if (nTmp < 5)
        {
            g_struLocalParam.iCycleTime = 5;				//cycle play enduration
        }
        else
        {
            g_struLocalParam.iCycleTime = nTmp;
        }

        if (GetNodeVal_JSON(pRoot, c_strNode_CyclePlay, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bCyclePlay = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_UseCard, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bUseCard = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_NTSC, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bNTSC = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_RecordFileInterval, &nTmp) == FALSE)
        {
            break;
        }
        if (nTmp > 60)
        {
            g_struLocalParam.iRecordFileInterval = 60;				//cycle play enduration
        }
        else
        {
            g_struLocalParam.iRecordFileInterval = nTmp;
        }

        if (GetNodeVal_JSON(pRoot, c_strNode_AutoRecord, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bAutoRecord = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_CycleRecord, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bCycleRecord = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_StartRecordDriver, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.iStartRecordDriver = nTmp;

        if (GetNodeVal_JSON(pRoot, c_strNode_EndRecordDriver, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.iEndRecordDriver = nTmp;

        if (GetNodeVal_JSON(pRoot, c_strNode_DownLoadPath
            , g_struLocalParam.chDownLoadPath, 100) == FALSE)
        {
            break;
        }

        if (GetNodeVal_JSON(pRoot, c_strNode_PictureSavePath
            , g_struLocalParam.chPictureSavePath, 100) == FALSE)
        {
            break;
        }

        if (GetNodeVal_JSON(pRoot, c_strNode_RemoteCfgSavePath
            , g_struLocalParam.chRemoteCfgSavePath, 100) == FALSE)
        {
            break;
        }

        if (GetNodeVal_JSON(pRoot, c_strNode_AutoCheckDeviceTime, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bAutoCheckDeviceTime = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_CheckDeviceTime, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.lCheckDeviceTime = nTmp < 0 ? 0 : nTmp;

        if (GetNodeVal_JSON(pRoot, c_strNode_AlarmDelayTime, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.iAlarmDelayTime = nTmp;

        if (GetNodeVal_JSON(pRoot, c_strNode_AlarmListenPort, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.iAlarmListenPort = nTmp;

        if (GetNodeVal_JSON(pRoot, c_strNode_AutoSaveLog, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bAutoSaveLog = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_AlarmInfo, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bAlarmInfo = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_SuccLog, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bSuccLog = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_FailLog, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bFailLog = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_NoDecode, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bNoDecode = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_PreviewBlock, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bPreviewBlock = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_OutputDebugString, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.bOutputDebugString = nTmp == 1 ? TRUE : FALSE;

        cJSON* pRecordTimes = cJSON_GetObjectItem(pRoot, c_strNode_RecordTimes);
        if (pRecordTimes == NULL || pRecordTimes->type != cJSON_Array)
        {
            break;
        }
        int nRecordTimes = cJSON_GetArraySize(pRecordTimes);
        for (int i = 0; i < nRecordTimes; i++)
        {
            int nDay = i / 4;
            int nIndex = i % 4;
            if (i >= 4 * MAX_DAYS)
            {
                continue;
            }
            cJSON* pRecordTime = cJSON_GetArrayItem(pRecordTimes, i);
            if (pRecordTime == NULL || pRecordTime->type != cJSON_Object)
            {
                break;
            }

            if (GetNodeVal_JSON(pRecordTime, c_strNode_StartTime, &nTmp) == FALSE)
            {
                break;
            }
            g_struLocalParam.struLocalRecordTime[nDay][nIndex].iStartTime = nTmp;
            
            if (GetNodeVal_JSON(pRecordTime, c_strNode_StopTime, &nTmp) == FALSE)
            {
                break;
            }
            g_struLocalParam.struLocalRecordTime[nDay][nIndex].iStopTime = nTmp;
        }

        for (int i = 0; i < MAX_DAYS; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                g_struLocalParam.struLocalRecordTime[i][j].iStartHour = 
                    (WORD)(g_struLocalParam.struLocalRecordTime[i][j].iStartTime / 100);
                g_struLocalParam.struLocalRecordTime[i][j].iStartMinute = 
                    (WORD)(g_struLocalParam.struLocalRecordTime[i][j].iStartTime % 100);
                g_struLocalParam.struLocalRecordTime[i][j].iStopHour = 
                    (WORD)(g_struLocalParam.struLocalRecordTime[i][j].iStopTime / 100);
                g_struLocalParam.struLocalRecordTime[i][j].iStopMinute = 
                    (WORD)(g_struLocalParam.struLocalRecordTime[i][j].iStopTime % 100);
            }
        }

        if (GetNodeVal_JSON(pRoot, c_strNode_BFrameNum, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.dwBFrameNum = nTmp;

        if (GetNodeVal_JSON(pRoot, c_strNode_InSide, &nTmp) == FALSE)
        {
            break;
        }
        g_bInSide = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_LogLevel, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.nLogLevel = nTmp;

        if (GetNodeVal_JSON(pRoot, c_strNode_StandardCB, &nTmp) == FALSE)
        {
            break;
        }
        g_bStandardCB = nTmp == 1 ? TRUE : FALSE;

        if (GetNodeVal_JSON(pRoot, c_strNode_Timeout, &nTmp) == FALSE)
        {
            break;
        }
        g_struLocalParam.nTimeout = nTmp;

        if (GetNodeVal_JSON(pRoot, c_strNode_HourDiffWithUTC, &nTmp) == FALSE)
        {
            break;
        }
        g_iHourDiffWithUTC = nTmp;

        if (GetNodeVal_JSON(pRoot, c_strNode_MinDiffWithUTC, &nTmp) == FALSE)
        {
            break;
        }
        g_iMinDiffWithUTC = nTmp;

        if (GetNodeVal_JSON(pRoot, c_strNode_ISO8601, &nTmp) == FALSE)
        {
            break;
        }
        g_bISO8601 = nTmp;

    } while (0);

    cJSON_Delete(pRoot);
}