/**********************************************************
FileName:    ClientDemoDlg.cpp
Description: main dialog, show the main function      
Date:        2008/12/12
Note: 		the global Macro definition and structure is in "GeneralDef.h", global variable and function is in "ClientDemo.cpp"
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/12/12>       <created>
***********************************************************/

#include "stdafx.h"
#include "string.h"
#include "ClientDemo.h"
#include ".\clientdemodlg.h"
#include "DlgAddDevice.h"
#include "DlgRemoteCfg.h"
#include "math.h"
#include "winver.h"
#include "DlgDeviceInfo.h"
#include "DlgUpgrade.h"
#include "DlgFormatHD.h"
#include "DlgRemoteKey.h"
#include "DlgDeviceState.h"
#include "DlgLocalLogConfig.h"
#include "DlgJPEGSnatchConfig.h"
#include "DlgBroadCast.h"
#include "DlgHardDiskCfg.h"
#include "DlgRemoteIPAccess.h"
#include "DlgVoiceTalk.h"
#include "DlgFortify.h"
#include "DlgLogSearch.h"
#include "DlgDeviceState.h"
#include "DlgCheckTime.h"
#include "DlgSerialTrans.h"
#include "DlgConfigFlash.h"
#include "DlgDoTest.h"
#include "process.h"
#include "DlgAtmFrameFormatV30.h"
#include "DlgInquestDvr.h"
#include "DlgPtzScope.h"
#include "DlgSensorAddPreview.h"
#include "DlgHolidayCfg.h"
#include "DlgNetServiceCfg.h"
#include "DlgCertInfo.h"
#include "DlgT1test.h"
#include "DlgDevServer.h"
#include "DlgProductionTest.h"
#include "DlgVedioAudioInCfg.h"
#include "DlgProductCfg.h"
#include "DlgVCADetionCfg.h"
#include "DlgTalkMREx.h"
#include "DlgVideoIntercomCall.h"
#include "DlgDebug.h"
#include "DlgUploadCalibrationFile.h"
#include "DlgIperf.h"
#include "MimeProtocolParsing.h"
#include "cjson/cJSON.h"
#include "DlgAlarmInfo.h"
#include "DlgAsynloginWait.h"

using namespace std;

#pragma   comment   (lib,   "version.lib")  
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static unsigned long ulAlarmPic = 0;

extern HINSTANCE g_hDSSDK;
extern HINSTANCE g_hDllInst;
extern HINSTANCE g_hDllCalib;
extern HINSTANCE g_hDllCurlLib;
CRITICAL_SECTION g_cs;






extern void InfoMinorTypeMap(const NET_DVR_LOG_V50 &stLogInfo, CString &szTemp);
extern void EventMinorTypeMap(const NET_DVR_LOG_V50 &stLogInfo, CString &szTemp);
extern void OperationMinorTypeMap(const NET_DVR_LOG_V50 &stLogInfo, CString &szTemp);
extern void ExceptionMinorTypeMap(const NET_DVR_LOG_V50 &stLogInfo, CString &szTemp);
extern void AlarmMinorTypeMap(const NET_DVR_LOG_V50 &stLogInfo, CString &szTemp);
extern void ParaTypeMap(const NET_DVR_LOG_V50 &stLogInfo, CString &szTemp);

int g_iCount = 0;
BOOL g_bJSONBroken  = FALSE;//JSON Broken flag
extern int m_giAsynLoginReturn;
extern bool m_gbAsynLogin;
extern int m_giErrNo;
extern const char* m_gpErrMsg;
extern CDlgAsynloginWait* m_gpDlgAsynloginWait;
//Alarm host
typedef struct tagLOCAL_ALARM_INFO
{
	int iDeviceIndex;
	LONG lCommand;
	char sDeviceIP[128];    			/* IP地址 */
	DWORD dwBufLen;
	tagLOCAL_ALARM_INFO()
	{
		iDeviceIndex = -1;
		lCommand = -1;
		memset(&sDeviceIP, 0, 128);
		dwBufLen = 0;
	}
}LOCAL_ALARM_INFO, *LPLOCAL_ALARM_INFO;

string UTF82ASCII(const char* cont)
{
    if (NULL == cont)
    {
        return string("");
    }
    int num = MultiByteToWideChar(CP_UTF8, NULL, cont, -1, NULL, NULL);
    wchar_t* buffw = new wchar_t[(unsigned int)num];
    MultiByteToWideChar(CP_UTF8, NULL, cont, -1, buffw, num);
    int len = WideCharToMultiByte(CP_ACP, 0, buffw, num - 1, NULL, NULL, NULL, NULL); 
    char* lpsz = new char[(unsigned int)len + 1]; 
    WideCharToMultiByte(CP_ACP, 0, buffw, num - 1, lpsz, len, NULL, NULL);
    lpsz[len]='\0';
    delete[] buffw;
    string rtn(lpsz);
    delete[] lpsz;
    return rtn ;  
}

/*********************************************************
函数名:	A2UTF8
函数描述:	多字节转UTF8
输入参数:	cont - 多字节字符串                       
输出参数:	
返回值:	    UTF8编码的字符串
**********************************************************/
string ASCII2UTF8(const char* cont)
{
    if (NULL == cont)
    {
        return string("");
    }
    
    int num = MultiByteToWideChar(CP_ACP, NULL, cont, -1, NULL, NULL);
    wchar_t* buffw = new wchar_t[(unsigned int)num];
    MultiByteToWideChar(CP_ACP, NULL, cont, -1, buffw, num);
    
    int len = WideCharToMultiByte(CP_UTF8, 0, buffw, num - 1, NULL, NULL, NULL, NULL); 
    char* lpsz = new char[(unsigned int)len + 1]; 
    WideCharToMultiByte(CP_UTF8, 0, buffw, num - 1, lpsz, len, NULL, NULL);
    lpsz[len]='\0';
    delete[] buffw;
    
    string rtn(lpsz);
    delete[] lpsz;
    return rtn;
}

/*********************************************************
Function:	g_ExceptionCallBack
Desc:		exception callback function
Input:	dwType: message type;lUserID: log-in device ID;lHandle, handle of connected channel ; pUser, user data；
Output:	
Return:	
**********************************************************/
void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
	UNREFERENCED_PARAMETER(pUser);
	if (g_bExitDemo)
	{
		return;
	}
	int i = 0, j=0;
	int iDeviceIndex = -1;
	CString sTemp;
	//	char szTmpBuf[256] = {0};
	
	for (i = 0; i < MAX_DEVICES ; i++)
	{				
		if (g_struDeviceInfo[i].lLoginID == lUserID)
		{
			iDeviceIndex = i;		
			break;
		}
	}
	
	switch (dwType) 
	{
    case EXCEPTION_RELOGIN:
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "EXCEPTION_RELOGIN");
        break;
    case RELOGIN_SUCCESS:
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "RELOGIN_SUCCESS");
        break;
	case EXCEPTION_EXCHANGE://the device is off line
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "EXCEPTION_EXCHANGE");
		break;
    case RESUME_EXCHANGE://the device is on line
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "RESUME_EXCHANGE");
		break;
	case EXCEPTION_AUDIOEXCHANGE:	//network exception while voice talk
		if (g_lVoiceHandle != -1)
		{	
			if (lHandle == g_lVoiceHandle)
			{//sdk do not reconnect, so close the exception thread
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "EXCEPTION_AUDIOEXCHANGE vt dev[%d],handle[%d]", iDeviceIndex,lHandle);
				goto ExceptionOut;
			}			
		}
		else
		{
			for (i = 0; i<MAX_DEVICES; i++)
			{
				for (j = 0; j<MAX_AUDIO_V40; j++)
				{
					if (g_struDeviceInfo[i].lVoiceCom[j] == lHandle)
					{
						g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "AUDIOEXCHANGE mr dev[%d]exception[%d]", iDeviceIndex, dwType);
						if (NET_DVR_StopVoiceCom(lHandle))
						{
							g_pMainDlg->AddLog(i, OPERATION_SUCC_T, "NET_DVR_StopVoiceCom audioindex[%d]", j);
							g_struDeviceInfo[i].lVoiceCom[j] = -1;
						}
						else
						{
							g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_StopVoiceCom audioindex[%d]", j);
						}
						goto ExceptionOut;
					}
				}
			}
		}	
		if (g_struLocalParam.bBroadCast)
		{
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "AUDIOEXCHANGE BC dev[%d]handle[%d]exception[%d]", iDeviceIndex, lHandle, dwType);
			NET_DVR_DelDVR_V30(lHandle);
		}

		break;
	case EXCEPTION_ALARM:			//network exception while uploading alarm
		for (i = 0; i < MAX_DEVICES; i++)
		{				
			if (g_struDeviceInfo[i].lFortifyHandle >= 0)
			{
				if (lHandle == g_struDeviceInfo[i].lFortifyHandle)
				{
					//	if (NET_DVR_CloseAlarmChan_V30(g_struDeviceInfo[i].lFortifyHandle))
					//	{
					g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "alarm fortify exception!");
					//		g_struDeviceInfo[i].lFortifyHandle = -1;
					//	}
					//	else
					//	{
					
					//	}			
					goto ExceptionOut;
				}
			}
		}	
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "ALARM dev[%d]exception[%d]", iDeviceIndex, dwType);
		break;
	case EXCEPTION_PREVIEW:			// exception while preview
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "PREVIEW dev[%d]exception[%d]", iDeviceIndex, dwType);
		for (i = 0; i < MAX_OUTPUTS; i++)
		{
			if (lHandle == g_dlgOutput[i].m_lPlayHandle)
			{
				g_dlgOutput[i].AddLog(OPERATION_FAIL_T, "preview exception!");
				if (g_dlgOutput[i].m_bLocalManualRec)
				{
					g_dlgOutput[i].StopLocalRecord();
				}
				g_dlgOutput[i].StopPlay();
				g_pMainDlg->ChangePlayBtnState();
				goto ExceptionOut;
			}
		}
		break;
	case EXCEPTION_SERIAL:			//exception while connecting in a transparent channel mode
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "EXCEPTION_SERIAL dev[%d]", iDeviceIndex);
		for (i = 0; i < MAX_DEVICES ; i++)
		{				
			if (g_struDeviceInfo[i].lTranHandle >= 0)
			{
				if (lHandle == g_struDeviceInfo[i].lTranHandle)
				{
					g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "serial transparent exception!!");		
					goto ExceptionOut;
				}
			}
		}
		break;
	case EXCEPTION_RECONNECT:		//reconnect while preview	
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "preview RECONNECT dev[%d]", iDeviceIndex);
		for (i = 0; i < MAX_OUTPUTS; i++)
		{
			if (lHandle == g_dlgOutput[i].m_lPlayHandle)
			{
				g_dlgOutput[i].AddLog(OPERATION_SUCC_T, "preview reconneting!");//reconnect to network while preview
				goto ExceptionOut;
			}	
		}
		break;
	case PREVIEW_RECONNECTSUCCESS:		//reconnect successfully while preview				
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "PREVIEW_RECONNECTSUCCESS dev[%d]", iDeviceIndex);
		break;
	case EXCEPTION_ALARMRECONNECT://reconnect alarm guard channel
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "ALARMRECONNECT dev[%d]", iDeviceIndex);
		for (i = 0; i < MAX_DEVICES ; i++)
		{				
			if (g_struDeviceInfo[i].lFortifyHandle >= 0)
			{
				if (lHandle == g_struDeviceInfo[i].lFortifyHandle)
				{
					g_pMainDlg->AddLog(i, OPERATION_SUCC_T, "alarm Fortify reconnecting!!");		
					goto ExceptionOut;
				}
			}
		}
		break;
	case ALARM_RECONNECTSUCCESS://reconnect alarm guard channel successfully
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "ALARM_RECONNECTSUCCESS dev[%d]", iDeviceIndex);
		break;
	case EXCEPTION_SERIALRECONNECT://reconnect transparent channel
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "SERIALRECONNECT dev[%d]exception[0x%x]", iDeviceIndex, dwType);
		for (i = 0; i < MAX_DEVICES ; i++)
		{				
			if (g_struDeviceInfo[i].lLoginID == lUserID)
			{
				g_pMainDlg->AddLog(i, OPERATION_SUCC_T, "serial transparent reconnecting!");		
				goto ExceptionOut;
			}
		}
		break;
	case EXCEPTION_PLAYBACK:
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "EXCEPTION_PLAYBACK dev[%d] exception[0x%x] error[%d]", iDeviceIndex, dwType, NET_DVR_GetLastError());
		break;
	case EXCEPTION_DISKFMT:
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "EXCEPTION_DISKFMT dev[%d]DISKFMT exception[0x%x]", iDeviceIndex, dwType);
		break;
    case EXCEPTION_PASSIVEDECODE:
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "EXCEPTION_PASSIVEDECODE dev[%d]PASSIVEDECODE exception[0x%x]", iDeviceIndex, dwType);		
        //NET_DVR_MatrixStopPassiveDecode(lHandle);

		break;
	case SERIAL_RECONNECTSUCCESS:
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "SERIAL_RECONNECTSUCCESS dev[%d]", iDeviceIndex);
		break;
	case EXCEPTION_LOST_ALARM:
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "EXCEPTION_LOST_ALARM");
		break;
	case EXCEPTION_MAX_ALARM_INFO:
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "EXCEPTION_MAX_ALARM_INFO");
		break;
    case EXCEPTION_PASSIVEDECODE_RECONNNECT:
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "EXCEPTION_PASSIVEDECODE_RECONNNECT");
		break;
	default:
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "else exception dev[%d]exception[0x%x]", iDeviceIndex, dwType);
		break;
	}
ExceptionOut:
	return;
}
/*********************************************************
Function:	AlarmMessage
Desc:		alarm
Input:	lCommand,message type; pAlarmer,info of device which upload message;pAlarmInfo, message info content;dwBufLen,message length;
Output:
Return:
**********************************************************/
void AlarmMessage(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen)
{
    UINT iDeviceIndex = 0xffff;
    UINT i = 0;
    if (g_pMainDlg == NULL || g_bExitDemo)
    {
        TRACE("exit ...\n");
        //return;
    }

    for (i = 0; i < MAX_DEVICES; i++)
    {//IP address that client have acquired
        if (strcmp(g_struDeviceInfo[i].chDeviceIP, pAlarmer->sDeviceIP) == 0)
        {
            iDeviceIndex = i;
            break;
        }
        //监听时候的设备IP为sSocketIP
        if (strcmp(g_struDeviceInfo[i].chDeviceIP, pAlarmer->sSocketIP) == 0)
        {
            iDeviceIndex = i;
            break;
        }
    }

    if (pAlarmer->bJSONBroken)
    {
        g_bJSONBroken = 1;
    }
    else
    {
        g_bJSONBroken = 0;
    }


    if (iDeviceIndex >= MAX_DEVICES || iDeviceIndex < 0)
    {
        g_pMainDlg->AddLog(-1, ALARM_INFO_T, "alarm host get alarm[%x] from device[%s] port[%d]", lCommand, pAlarmer->sDeviceIP, pAlarmer->wLinkPort);
        //return;
    }
    else
    {
        char szDeviceName[NAME_LEN] = { 0 };
        if (g_struDeviceInfo[iDeviceIndex].byCharaterEncodeType == ENUM_MEM_CHAR_ENCODE_UNICODE)
        {
            TranslateNetWcharToMutilChar(szDeviceName, (unsigned char*)(pAlarmer->sDeviceName), NAME_LEN);
        }
        else
        {
            strncpy(szDeviceName, pAlarmer->sDeviceName, NAME_LEN);
        }
        g_pMainDlg->AddLog(-1, ALARM_INFO_T, "alarm host get alarm[%x] from device[%s] port[%d] name[%s] mac:%x:%x:%x:%x:%x:%x serial:%s", \
            lCommand, pAlarmer->sDeviceIP, pAlarmer->wLinkPort, szDeviceName, pAlarmer->byMacAddr[0], pAlarmer->byMacAddr[1], pAlarmer->byMacAddr[2], \
            pAlarmer->byMacAddr[3], pAlarmer->byMacAddr[4], pAlarmer->byMacAddr[5],
            pAlarmer->sSerialNumber);
    }
    try
    {
        char *pAlarmMsg = NULL;
        if (lCommand == COMM_ALARM_WALL_CONFERNECE)
        {
            pAlarmMsg = new char[sizeof(DWORD) + dwBufLen];
            if (pAlarmMsg == NULL)
            {
                return;
            }
            memset(pAlarmMsg, 0, sizeof(DWORD) + dwBufLen);
            memcpy(pAlarmMsg, &dwBufLen, sizeof(DWORD));
            memcpy(pAlarmMsg + sizeof(DWORD), pAlarmInfo, dwBufLen);
        }
        else
        {
            pAlarmMsg = new char[dwBufLen];
            if (pAlarmMsg == NULL)
            {
                return;
            }
            memset(pAlarmMsg, 0, dwBufLen);
            memcpy(pAlarmMsg, pAlarmInfo, dwBufLen);
        }

        if (lCommand == COMM_ISAPI_ALARM)
        {
            ((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pAlarmData = new char[((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->dwAlarmDataLen + 1];
            memset(((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pAlarmData, 0, ((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->dwAlarmDataLen + 1);
            memcpy(((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pAlarmData, ((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmInfo)->pAlarmData, ((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->dwAlarmDataLen);

            if (((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmInfo)->byPicturesNumber != 0)
            {
                ((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pPicPackData = (NET_DVR_ALARM_ISAPI_PICDATA *)new BYTE[sizeof(NET_DVR_ALARM_ISAPI_PICDATA)* ((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmInfo)->byPicturesNumber];
                memset(((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pPicPackData, 0, sizeof(NET_DVR_ALARM_ISAPI_PICDATA)* ((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmInfo)->byPicturesNumber);
                memcpy(((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pPicPackData, ((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmInfo)->pPicPackData, sizeof(NET_DVR_ALARM_ISAPI_PICDATA)* ((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmInfo)->byPicturesNumber);
                for (int i = 0; i < ((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmInfo)->byPicturesNumber; i++)
                {
                    ((NET_DVR_ALARM_ISAPI_PICDATA *)((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pPicPackData)[i].pPicData = new BYTE[((NET_DVR_ALARM_ISAPI_PICDATA *)((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pPicPackData)[i].dwPicLen];
                    memset(((NET_DVR_ALARM_ISAPI_PICDATA *)((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pPicPackData)[i].pPicData, 0, ((NET_DVR_ALARM_ISAPI_PICDATA *)((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pPicPackData)[i].dwPicLen);
                    memcpy(((NET_DVR_ALARM_ISAPI_PICDATA *)((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pPicPackData)[i].pPicData, ((NET_DVR_ALARM_ISAPI_PICDATA *)((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmInfo)->pPicPackData)[i].pPicData, ((NET_DVR_ALARM_ISAPI_PICDATA *)((LPNET_DVR_ALARM_ISAPI_INFO)pAlarmMsg)->pPicPackData)[i].dwPicLen);
                }
            }
        }
        else if (lCommand == COMM_ALARM_RULE)
        {
            ((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pImage = new BYTE[((LPNET_VCA_RULE_ALARM)pAlarmMsg)->dwPicDataLen];
            memset(((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pImage, 0, ((LPNET_VCA_RULE_ALARM)pAlarmMsg)->dwPicDataLen);
            memcpy(((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pImage, ((LPNET_VCA_RULE_ALARM)pAlarmInfo)->pImage, ((LPNET_VCA_RULE_ALARM)pAlarmMsg)->dwPicDataLen);

            if (((LPNET_VCA_RULE_ALARM)pAlarmMsg)->byAppendInfoUploadEnabled == 1)
            {
                ((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pAppendInfo = new BYTE[sizeof(NET_VCA_APPEND_INFO)];
                memset(((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pAppendInfo, 0, sizeof(NET_VCA_APPEND_INFO));
                memcpy(((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pAppendInfo, ((LPNET_VCA_RULE_ALARM)pAlarmInfo)->pAppendInfo, sizeof(NET_VCA_APPEND_INFO));

                ((LPNET_VCA_APPEND_INFO)((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pAppendInfo)->pAppendPicBuff = new BYTE[((LPNET_VCA_APPEND_INFO)((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pAppendInfo)->dwAppendPicLen];
                memset(((LPNET_VCA_APPEND_INFO)((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pAppendInfo)->pAppendPicBuff, 0, ((LPNET_VCA_APPEND_INFO)((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pAppendInfo)->dwAppendPicLen);
                memcpy(((LPNET_VCA_APPEND_INFO)((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pAppendInfo)->pAppendPicBuff, ((LPNET_VCA_APPEND_INFO)((LPNET_VCA_RULE_ALARM)pAlarmInfo)->pAppendInfo)->pAppendPicBuff, ((LPNET_VCA_APPEND_INFO)((LPNET_VCA_RULE_ALARM)pAlarmMsg)->pAppendInfo)->dwAppendPicLen);
            }
        }
        else if (COMM_ALARM_AID == lCommand)
        {
            ((LPNET_DVR_AID_ALARM)pAlarmMsg)->pImage = new BYTE[((LPNET_DVR_AID_ALARM)pAlarmMsg)->dwPicDataLen];
            memset(((LPNET_DVR_AID_ALARM)pAlarmMsg)->pImage, 0, ((LPNET_DVR_AID_ALARM)pAlarmMsg)->dwPicDataLen);
            memcpy(((LPNET_DVR_AID_ALARM)pAlarmMsg)->pImage, ((LPNET_DVR_AID_ALARM)pAlarmInfo)->pImage, ((LPNET_DVR_AID_ALARM)pAlarmMsg)->dwPicDataLen);
        }
        else if (COMM_ALARM_FACE == lCommand)
        {
            ((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->pImage = new BYTE[((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->dwPicDataLen];
            memset(((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->pImage, 0, ((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->dwPicDataLen);
            memcpy(((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->pImage, ((LPNET_DVR_FACEDETECT_ALARM)pAlarmInfo)->pImage, ((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->dwPicDataLen);

            ((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->pFaceImage = new BYTE[((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->dwFacePicDataLen];
            memset(((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->pFaceImage, 0, ((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->dwFacePicDataLen);
            memcpy(((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->pFaceImage, ((LPNET_DVR_FACEDETECT_ALARM)pAlarmInfo)->pFaceImage, ((LPNET_DVR_FACEDETECT_ALARM)pAlarmMsg)->dwFacePicDataLen);

        }
        else if (COMM_UPLOAD_FACESNAP_RESULT == lCommand)
        {
            DWORD dwPrePicLen = 0;
            if (((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->dwFacePicLen > 0)
            {
                ((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->pBuffer1 = (BYTE*)pAlarmMsg + sizeof(NET_VCA_FACESNAP_RESULT) + dwPrePicLen;
                dwPrePicLen += ((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->dwFacePicLen;
            }

            if (((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->dwBackgroundPicLen > 0)
            {
                ((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->pBuffer2 = (BYTE*)pAlarmMsg + sizeof(NET_VCA_FACESNAP_RESULT) + dwPrePicLen;               
                dwPrePicLen += ((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->dwBackgroundPicLen;
            }

            if (((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->byUIDLen > 0)
            {
                ((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->pUIDBuffer = (BYTE*)pAlarmMsg + sizeof(NET_VCA_FACESNAP_RESULT) + dwPrePicLen;           
                dwPrePicLen += ((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->byUIDLen;
            }

            if (((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->byAddInfo > 0)
            {
                ((LPNET_VCA_FACESNAP_RESULT)pAlarmMsg)->pAddInfoBuffer = (BYTE*)pAlarmMsg + sizeof(NET_VCA_FACESNAP_RESULT) + dwPrePicLen;               
                dwPrePicLen += sizeof(NET_VCA_FACESNAP_ADDINFO);
            }     
        }
        else if (COMM_ALARM_FACE_DETECTION == lCommand)
        {
            ((LPNET_DVR_FACE_DETECTION)pAlarmMsg)->pBackgroundPicpBuffer = new BYTE[((LPNET_DVR_FACE_DETECTION)pAlarmMsg)->dwBackgroundPicLen];
            memset(((LPNET_DVR_FACE_DETECTION)pAlarmMsg)->pBackgroundPicpBuffer, 0, ((LPNET_DVR_FACE_DETECTION)pAlarmMsg)->dwBackgroundPicLen);
            memcpy(((LPNET_DVR_FACE_DETECTION)pAlarmMsg)->pBackgroundPicpBuffer, ((LPNET_DVR_FACE_DETECTION)pAlarmInfo)->pBackgroundPicpBuffer, \
                ((LPNET_DVR_FACE_DETECTION)pAlarmMsg)->dwBackgroundPicLen);
        }
        else if (COMM_SNAP_MATCH_ALARM == lCommand)
        {
            if (((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.dwSnapFacePicLen > 0)
            {
                ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.pBuffer1 = new BYTE[((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.dwSnapFacePicLen];
                memset(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.pBuffer1, 0, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.dwSnapFacePicLen);
                memcpy(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.pBuffer1, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmInfo)->struSnapInfo.pBuffer1, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.dwSnapFacePicLen);
            }

            if (((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwBlackListPicLen > 0)
            {
                ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.pBuffer1 = new BYTE[((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwBlackListPicLen];
                memset(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.pBuffer1, 0, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwBlackListPicLen);
                memcpy(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.pBuffer1, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmInfo)->struBlackListInfo.pBuffer1, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwBlackListPicLen);
            }

            if (((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->dwSnapPicLen > 0)
            {
                ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->pSnapPicBuffer = new BYTE[((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->dwSnapPicLen];
                memset(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->pSnapPicBuffer, 0, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->dwSnapPicLen);
                memcpy(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->pSnapPicBuffer, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmInfo)->pSnapPicBuffer, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->dwSnapPicLen);
            }

            if (((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->dwModelDataLen > 0)
            {
                ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->pModelDataBuffer = new BYTE[((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->dwModelDataLen];
                memset(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->pModelDataBuffer, 0, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->dwModelDataLen);
                memcpy(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->pModelDataBuffer, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmInfo)->pModelDataBuffer, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->dwModelDataLen);
            }

            if (((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.struAttribute.dwPersonInfoExtendLen > 0)
            {
                ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend = new BYTE[((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.struAttribute.dwPersonInfoExtendLen];
                memset(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend, 0, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.struAttribute.dwPersonInfoExtendLen);
                memcpy(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmInfo)->struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.struAttribute.dwPersonInfoExtendLen);
            }

            if (((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.dwUIDLen > 0)
            {
                ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.pUIDBuffer = new BYTE[((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.dwUIDLen];
                memset(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.pUIDBuffer, 0, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.dwUIDLen);
                memcpy(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.pUIDBuffer, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmInfo)->struSnapInfo.pUIDBuffer, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struSnapInfo.dwUIDLen);
            }

            if (((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwFDIDLen > 0)
            {
                ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.pFDID = new BYTE[((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwFDIDLen];
                memset(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.pFDID, 0, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwFDIDLen);
                memcpy(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.pFDID, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmInfo)->struBlackListInfo.pFDID, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwFDIDLen);
            }

            if (((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwPIDLen > 0)
            {
                ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.pPID = new BYTE[((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwPIDLen];
                memset(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.pPID, 0, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwPIDLen);
                memcpy(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.pPID, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmInfo)->struBlackListInfo.pPID, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.dwPIDLen);
            }

            if (((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.dwFDDescriptionLen > 0)
            {
                ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.pFDDescriptionBuffer = new BYTE[((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.dwFDDescriptionLen];
                memset(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.pFDDescriptionBuffer, 0, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.dwFDDescriptionLen);
                memcpy(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.pFDDescriptionBuffer, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmInfo)->struBlackListInfo.struBlackListInfo.pFDDescriptionBuffer, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.dwFDDescriptionLen);
            }

            if (((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.dwFCAdditionInfoLen > 0)
            {
                ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.pFCAdditionInfoBuffer = new BYTE[((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.dwFCAdditionInfoLen];
                memset(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.pFCAdditionInfoBuffer, 0, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.dwFCAdditionInfoLen);
                memcpy(((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.pFCAdditionInfoBuffer, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmInfo)->struBlackListInfo.struBlackListInfo.pFCAdditionInfoBuffer, ((LPNET_VCA_FACESNAP_MATCH_ALARM)pAlarmMsg)->struBlackListInfo.struBlackListInfo.dwFCAdditionInfoLen);
            }
        }
        else if (COMM_ALARM_CAPTURE_UPLOAD == lCommand)
        {
            ((LPNET_DVR_CAPTURE_UPLOAD)pAlarmMsg)->pBuffer = new BYTE[((LPNET_DVR_CAPTURE_UPLOAD)pAlarmMsg)->dwPicLen];
            memset(((LPNET_DVR_CAPTURE_UPLOAD)pAlarmMsg)->pBuffer, 0, ((LPNET_DVR_CAPTURE_UPLOAD)pAlarmMsg)->dwPicLen);
            memcpy(((LPNET_DVR_CAPTURE_UPLOAD)pAlarmMsg)->pBuffer, ((LPNET_DVR_CAPTURE_UPLOAD)pAlarmInfo)->pBuffer, ((LPNET_DVR_CAPTURE_UPLOAD)pAlarmMsg)->dwPicLen);
        }
        else if (COMM_FACESNAP_RAWDATA_ALARM == lCommand)
        {
            ((LPNET_VCA_FACESNAP_RAWDATA_ALARM)pAlarmMsg)->pJsonBuff = new BYTE[((LPNET_VCA_FACESNAP_RAWDATA_ALARM)pAlarmMsg)->dwJsonDataLen];
            memset(((LPNET_VCA_FACESNAP_RAWDATA_ALARM)pAlarmMsg)->pJsonBuff, 0, ((LPNET_VCA_FACESNAP_RAWDATA_ALARM)pAlarmMsg)->dwJsonDataLen);
            memcpy(((LPNET_VCA_FACESNAP_RAWDATA_ALARM)pAlarmMsg)->pJsonBuff, ((LPNET_VCA_FACESNAP_RAWDATA_ALARM)pAlarmInfo)->pJsonBuff, ((LPNET_VCA_FACESNAP_RAWDATA_ALARM)pAlarmMsg)->dwJsonDataLen);
        }
        else if (COMM_FRAMES_PEOPLE_COUNTING_ALARM == lCommand)
        {
            ((LPNET_DVR_FRAMES_PEOPLE_COUNTING)pAlarmMsg)->pPicBuffer = new BYTE[((LPNET_DVR_FRAMES_PEOPLE_COUNTING)pAlarmMsg)->dwPicLen];
            memset(((LPNET_DVR_FRAMES_PEOPLE_COUNTING)pAlarmMsg)->pPicBuffer, 0, ((LPNET_DVR_FRAMES_PEOPLE_COUNTING)pAlarmMsg)->dwPicLen);
            memcpy(((LPNET_DVR_FRAMES_PEOPLE_COUNTING)pAlarmMsg)->pPicBuffer, ((LPNET_DVR_FRAMES_PEOPLE_COUNTING)pAlarmInfo)->pPicBuffer, ((LPNET_DVR_FRAMES_PEOPLE_COUNTING)pAlarmMsg)->dwPicLen);
        }
        else if (COMM_FIREDETECTION_ALARM == lCommand)
        {
            ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->pBuffer = new BYTE[((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->dwPicDataLen];
            memset(((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->pBuffer, 0, ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->dwPicDataLen);
            memcpy(((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->pBuffer, ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmInfo)->pBuffer, ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->dwPicDataLen);

            ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->pVisiblePicBuf = new BYTE[((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->dwVisiblePicLen];
            memset(((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->pVisiblePicBuf, 0, ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->dwVisiblePicLen);
            memcpy(((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->pVisiblePicBuf, ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmInfo)->pVisiblePicBuf, ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->dwVisiblePicLen);
            if (((LPNET_DVR_FIREDETECTION_ALARM)pAlarmInfo)->byAlarmSubType == 1 || ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmInfo)->byAlarmSubType == 2)
            {
                ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->pSmokeBuf = new BYTE[sizeof(NET_DVR_SMOKEDETECTION_ALARM)];
                memset(((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->pSmokeBuf, 0, sizeof(NET_DVR_SMOKEDETECTION_ALARM));
                memcpy(((LPNET_DVR_FIREDETECTION_ALARM)pAlarmMsg)->pSmokeBuf, ((LPNET_DVR_FIREDETECTION_ALARM)pAlarmInfo)->pSmokeBuf, sizeof(NET_DVR_SMOKEDETECTION_ALARM));
            }
        }
        else if (COMM_FACE_THERMOMETRY_ALARM == lCommand)
        {
            ((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->pVisibleLightImage = new BYTE[((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->dwVisibleLightImageLen];
            memset(((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->pVisibleLightImage, 0, ((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->dwVisibleLightImageLen);
            memcpy(((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->pVisibleLightImage, ((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmInfo)->pVisibleLightImage, ((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->dwVisibleLightImageLen);

            ((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->pFaceImage = new BYTE[((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->dwFaceImageLen];
            memset(((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->pFaceImage, 0, ((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->dwFaceImageLen);
            memcpy(((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->pFaceImage, ((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmInfo)->pFaceImage, ((LPNET_DVR_FACE_THERMOMETRY_ALARM)pAlarmMsg)->dwFaceImageLen);
        }
        else if (COMM_ALARM_SHIPSDETECTION == lCommand)
        {
            ((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->pPicBuffer = new BYTE[((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->dwPicLen];
            memset(((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->pPicBuffer, 0, ((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->dwPicLen);
            memcpy(((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->pPicBuffer, ((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmInfo)->pPicBuffer, ((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->dwPicLen);

            ((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->pThermalPicBuffer = new BYTE[((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->dwThermalPicLen];
            memset(((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->pThermalPicBuffer, 0, ((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->dwThermalPicLen);
            memcpy(((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->pThermalPicBuffer, ((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmInfo)->pThermalPicBuffer, ((LPNET_DVR_SHIPSDETECTION_ALARM)pAlarmMsg)->dwThermalPicLen);
        }
        else if (COMM_VEHICLE_CONTROL_ALARM == lCommand)
        {
            ((LPNET_DVR_VEHICLE_CONTROL_ALARM)pAlarmMsg)->pPicData = new char[((LPNET_DVR_VEHICLE_CONTROL_ALARM)pAlarmMsg)->dwPicDataLen];
            memset(((LPNET_DVR_VEHICLE_CONTROL_ALARM)pAlarmMsg)->pPicData, 0, ((LPNET_DVR_VEHICLE_CONTROL_ALARM)pAlarmMsg)->dwPicDataLen);
            memcpy(((LPNET_DVR_VEHICLE_CONTROL_ALARM)pAlarmMsg)->pPicData, ((LPNET_DVR_VEHICLE_CONTROL_ALARM)pAlarmInfo)->pPicData, ((LPNET_DVR_VEHICLE_CONTROL_ALARM)pAlarmMsg)->dwPicDataLen);
        }
        else if (COMM_THERMOMETRY_ALARM == lCommand)
        {
            ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->pPicBuff = new char[((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->dwPicLen];
            memset(((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->pPicBuff, 0, ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->dwPicLen);
            memcpy(((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->pPicBuff, ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmInfo)->pPicBuff, ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->dwPicLen);

            ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->pThermalPicBuff = new char[((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->dwThermalPicLen];
            memset(((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->pThermalPicBuff, 0, ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->dwThermalPicLen);
            memcpy(((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->pThermalPicBuff, ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmInfo)->pThermalPicBuff, ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->dwThermalPicLen);

            ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->pThermalInfoBuff = new char[((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->dwThermalInfoLen];
            memset(((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->pThermalInfoBuff, 0, ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->dwThermalInfoLen);
            memcpy(((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->pThermalInfoBuff, ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmInfo)->pThermalInfoBuff, ((LPNET_DVR_THERMOMETRY_ALARM)pAlarmMsg)->dwThermalInfoLen);
        }
        else if (COMM_THERMOMETRY_DIFF_ALARM == lCommand)
        {
            ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->pPicBuff = new char[((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->dwPicLen];
            memset(((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->pPicBuff, 0, ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->dwPicLen);
            memcpy(((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->pPicBuff, ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmInfo)->pPicBuff, ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->dwPicLen);

            ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->pThermalPicBuff = new char[((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->dwThermalPicLen];
            memset(((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->pThermalPicBuff, 0, ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->dwThermalPicLen);
            memcpy(((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->pThermalPicBuff, ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmInfo)->pThermalPicBuff, ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->dwThermalPicLen);

            ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->pThermalInfoBuff = new char[((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->dwThermalInfoLen];
            memset(((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->pThermalInfoBuff, 0, ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->dwThermalInfoLen);
            memcpy(((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->pThermalInfoBuff, ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmInfo)->pThermalInfoBuff, ((LPNET_DVR_THERMOMETRY_DIFF_ALARM)pAlarmMsg)->dwThermalInfoLen);
        }
        else if (COMM_VEHICLE_RECOG_RESULT == lCommand)
        {
            //车辆
            ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pVehicleBuffer = new BYTE[((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwVehicleBufferLen];
            memset(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pVehicleBuffer, 0, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwVehicleBufferLen);
            memcpy(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pVehicleBuffer, \
                ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmInfo)->pVehicleBuffer, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwVehicleBufferLen);
            //车牌
            ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pPlateBuffer = new BYTE[((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwPlateBufferLen];
            memset(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pPlateBuffer, 0, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwPlateBufferLen);
            memcpy(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pPlateBuffer, \
                ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmInfo)->pPlateBuffer, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwPlateBufferLen);
            //人脸（主驾驶)
            ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pPilotFaceBuffer = new BYTE[((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwPilotFaceBufferLen];
            memset(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pPilotFaceBuffer, 0, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwPilotFaceBufferLen);
            memcpy(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pPilotFaceBuffer, \
                ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmInfo)->pPilotFaceBuffer, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwPilotFaceBufferLen);
            //人脸（副驾驶）
            ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pCopilotFaceBuffer = new BYTE[((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwCopilotFaceBufferLen];
            memset(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pCopilotFaceBuffer, 0, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwCopilotFaceBufferLen);
            memcpy(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pCopilotFaceBuffer, \
                ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmInfo)->pCopilotFaceBuffer, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwCopilotFaceBufferLen);
            //安全带（主驾驶）
            ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pPilotSafebeltBuffer = new BYTE[((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwPilotSafebeltBufferLen];
            memset(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pPilotSafebeltBuffer, 0, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwPilotSafebeltBufferLen);
            memcpy(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pPilotSafebeltBuffer, \
                ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmInfo)->pPilotSafebeltBuffer, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwPilotSafebeltBufferLen);
            //安全带（副驾驶）
            ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pCopilotSafebeltBuffer = new BYTE[((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwCopilotSafebeltBufferLen];
            memset(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pCopilotSafebeltBuffer, 0, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwCopilotSafebeltBufferLen);
            memcpy(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pCopilotSafebeltBuffer, \
                ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmInfo)->pCopilotSafebeltBuffer, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwCopilotSafebeltBufferLen);
            //json
            ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pJsonBuffer = new BYTE[((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwJsonBufferLen];
            memset(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pJsonBuffer, 0, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwJsonBufferLen);
            memcpy(((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->pJsonBuffer, \
                ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmInfo)->pJsonBuffer, ((LPNET_DVR_VEHICLE_RECOG_RESULT)pAlarmMsg)->dwJsonBufferLen);

        }
        else if (COMM_ITS_PLATE_RESULT == lCommand)
        {
            int i = 0;
            DWORD dwPrePicLen = 0;
            int iIllegalInfoLen = 0;
            for (i = 0; i < 6; i++)
            {
                if (((LPNET_ITS_PLATE_RESULT)pAlarmMsg)->struPicInfo[i].dwDataLen > 0)
                {
                    ((LPNET_ITS_PLATE_RESULT)pAlarmMsg)->struPicInfo[i].pBuffer = (BYTE*)pAlarmMsg + sizeof(NET_ITS_PLATE_RESULT) + dwPrePicLen;
                    dwPrePicLen += ((LPNET_ITS_PLATE_RESULT)pAlarmMsg)->struPicInfo[i].dwDataLen;
                }
            }

            if (1 == ((LPNET_ITS_PLATE_RESULT)pAlarmMsg)->byIllegalFromatType)
            {
                ((LPNET_ITS_PLATE_RESULT)pAlarmMsg)->pIllegalInfoBuf = (BYTE*)pAlarmMsg + sizeof(NET_ITS_PLATE_RESULT) + dwPrePicLen;
                iIllegalInfoLen = sizeof(NET_ITS_ILLEGAL_INFO);
            }

            if (((LPNET_ITS_PLATE_RESULT)pAlarmMsg)->struPlateInfo.dwXmlLen > 0)
            {
                ((LPNET_ITS_PLATE_RESULT)pAlarmMsg)->struPlateInfo.pXmlBuf =
                    (char*)pAlarmMsg + sizeof(NET_ITS_PLATE_RESULT) + dwPrePicLen + iIllegalInfoLen;
            }
        }
        else if (COMM_PEOPLE_DETECTION_UPLOAD == lCommand)
        {
            int i = 0;
            DWORD dwPrePicLen = 0;
            for (i = 0; i < MAX_PEOPLE_DETECTION_NUM; i++)
            {
                if (((LPNET_DVR_PEOPLE_DETECTION_RESULT)pAlarmMsg)->struPeopleRegion[i].dwPicLen > 0)
                {
                    ((LPNET_DVR_PEOPLE_DETECTION_RESULT)pAlarmMsg)->struPeopleRegion[i].pPicBuffer = (char*)pAlarmMsg + sizeof(NET_DVR_PEOPLE_DETECTION_RESULT) + dwPrePicLen;
                    dwPrePicLen += ((LPNET_DVR_PEOPLE_DETECTION_RESULT)pAlarmMsg)->struPeopleRegion[i].dwPicLen;
                }
            }
        }
        else if (COMM_TME_VEHICLE_INDENTIFICATION == lCommand)
        {
            int i = 0;
            DWORD dwPrePicLen = 0;
            for (i = 0; i < 4; i++)
            {
                if (((LPNET_DVR_TME_VEHICLE_RESULT)pAlarmMsg)->struPicInfo[i].dwDataLen > 0)
                {
                    ((LPNET_DVR_TME_VEHICLE_RESULT)pAlarmMsg)->struPicInfo[i].pBuffer = (BYTE*)pAlarmMsg + sizeof(NET_DVR_TME_VEHICLE_RESULT) + dwPrePicLen;
                    dwPrePicLen += ((LPNET_DVR_TME_VEHICLE_RESULT)pAlarmMsg)->struPicInfo[i].dwDataLen;
                }
            }
        }
        else if (COMM_PLATE_RESULT_V50 == lCommand)
        {
            int i = 0;
            DWORD dwPrePicLen = 0;
            for (i = 0; i < 6; i++)
            {
                if (((LPNET_DVR_PLATE_RESULT_V50)pAlarmMsg)->struPicInfo[i].dwDataLen > 0)
                {
                    ((LPNET_DVR_PLATE_RESULT_V50)pAlarmMsg)->struPicInfo[i].pBuffer = (BYTE*)pAlarmMsg + sizeof(NET_DVR_PLATE_RESULT_V50) + dwPrePicLen;
                    dwPrePicLen += ((LPNET_DVR_PLATE_RESULT_V50)pAlarmMsg)->struPicInfo[i].dwDataLen;
                }
            }
        }
        else if (COMM_ITS_GATE_VEHICLE == lCommand)
        {
            int i = 0;
            DWORD dwPrePicLen = 0;
            for (i = 0; i < 4; i++)
            {
                if (((LPNET_ITS_GATE_VEHICLE)pAlarmMsg)->struPicInfo[i].dwDataLen > 0)
                {
                    ((LPNET_ITS_GATE_VEHICLE)pAlarmMsg)->struPicInfo[i].pBuffer = (BYTE*)pAlarmMsg + sizeof(NET_ITS_GATE_VEHICLE) + dwPrePicLen;
                    dwPrePicLen += ((LPNET_ITS_GATE_VEHICLE)pAlarmMsg)->struPicInfo[i].dwDataLen;
                }
            }
        }
        else if (COMM_ITS_GATE_FACE == lCommand)
        {
            ((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.pBuffer1 = new BYTE[((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.dwFacePicLen];
            memset(((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.pBuffer1, 0, ((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.dwFacePicLen);
            memcpy(((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.pBuffer1, ((LPNET_ITS_GATE_FACE)pAlarmInfo)->struFaceInfo.pBuffer1, \
                ((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.dwFacePicLen);

            ((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.pBuffer2 = new BYTE[((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.dwBackgroundPicLen];
            memset(((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.pBuffer2, 0, ((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.dwBackgroundPicLen);
            memcpy(((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.pBuffer2, ((LPNET_ITS_GATE_FACE)pAlarmInfo)->struFaceInfo.pBuffer2, \
                ((LPNET_ITS_GATE_FACE)pAlarmMsg)->struFaceInfo.dwBackgroundPicLen);

        }
        else if (COMM_ITS_PARK_VEHICLE == lCommand)
        {
            int i = 0;
            DWORD dwPrePicLen = 0;
            for (i = 0; i < 2; i++)
            {
                if (((LPNET_ITS_PARK_VEHICLE)pAlarmMsg)->struPicInfo[i].dwDataLen > 0)
                {
                    ((LPNET_ITS_PARK_VEHICLE)pAlarmMsg)->struPicInfo[i].pBuffer = (BYTE*)pAlarmMsg + sizeof(NET_ITS_PARK_VEHICLE) + dwPrePicLen;
                    dwPrePicLen += ((LPNET_ITS_PARK_VEHICLE)pAlarmMsg)->struPicInfo[i].dwDataLen;
                }
            }
        }
        else if (COMM_ALARM_AID_V41 == lCommand)
        {
            ((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->pImage = new BYTE[((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->dwPicDataLen];
            memset(((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->pImage, 0, ((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->dwPicDataLen);
            memcpy(((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->pImage, ((LPNET_DVR_AID_ALARM_V41)pAlarmInfo)->pImage, ((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->dwPicDataLen);

            ((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->pXmlBuf = new char[((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->dwXmlLen];
            memset(((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->pXmlBuf, 0, ((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->dwXmlLen);
            memcpy(((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->pXmlBuf, ((LPNET_DVR_AID_ALARM_V41)pAlarmInfo)->pXmlBuf, ((LPNET_DVR_AID_ALARM_V41)pAlarmMsg)->dwXmlLen);

        }
        else if (COMM_ALARM_TFS == lCommand)
        {
            int i = 0;
            DWORD dwPrePicLen = 0;
            for (i = 0; i < 8; i++)
            {
                if (((LPNET_DVR_TFS_ALARM)pAlarmMsg)->struPicInfo[i].dwDataLen > 0)
                {
                    ((LPNET_DVR_TFS_ALARM)pAlarmMsg)->struPicInfo[i].pBuffer = (BYTE*)pAlarmMsg + sizeof(NET_DVR_TFS_ALARM) + dwPrePicLen;
                    dwPrePicLen += ((LPNET_DVR_TFS_ALARM)pAlarmMsg)->struPicInfo[i].dwDataLen;
                }
            }
        }
        else if (COMM_ALARM_VQD_EX == lCommand)
        {
            if (((LPNET_DVR_VQD_ALARM)pAlarmMsg)->dwPicDataLen > 0)
            {
                ((LPNET_DVR_VQD_ALARM)pAlarmMsg)->pImage = new BYTE[((LPNET_DVR_VQD_ALARM)pAlarmMsg)->dwPicDataLen];
                memset(((LPNET_DVR_VQD_ALARM)pAlarmMsg)->pImage, 0, ((LPNET_DVR_VQD_ALARM)pAlarmMsg)->dwPicDataLen);
                memcpy(((LPNET_DVR_VQD_ALARM)pAlarmMsg)->pImage, ((LPNET_DVR_VQD_ALARM)pAlarmInfo)->pImage, ((LPNET_DVR_VQD_ALARM)pAlarmMsg)->dwPicDataLen);
            }
        }
        else if (COMM_UPLOAD_HEATMAP_RESULT == lCommand || COMM_UPLOAD_HEATMAP_RESULT_DURATION == lCommand || COMM_UPLOAD_HEATMAP_RESULT_INTERSECTION == lCommand)
        {
            if ((((LPNET_DVR_HEATMAP_RESULT)pAlarmMsg)->wArrayColumn > 0) || (((LPNET_DVR_HEATMAP_RESULT)pAlarmMsg)->wArrayLine > 0))
            {
                ((LPNET_DVR_HEATMAP_RESULT)pAlarmMsg)->pBuffer = (BYTE *)pAlarmMsg + sizeof(NET_DVR_HEATMAP_RESULT);
            }
        }
        else if (COMM_ALARM_V40 == lCommand)
        {
            DWORD dwVerDataNum = 0;
            switch (((LPNET_DVR_ALARMINFO_V40)pAlarmMsg)->struAlarmFixedHeader.dwAlarmType)
            {
            case 0:
            case 23:
                dwVerDataNum = (((LPNET_DVR_ALARMINFO_V40)pAlarmMsg)->struAlarmFixedHeader.uStruAlarm.struIOAlarm.dwTrigerAlarmOutNum + \
                    ((LPNET_DVR_ALARMINFO_V40)pAlarmMsg)->struAlarmFixedHeader.uStruAlarm.struIOAlarm.dwTrigerRecordChanNum);
                break;
            case 1:
            case 4:
            case 5:
                dwVerDataNum = ((LPNET_DVR_ALARMINFO_V40)pAlarmMsg)->struAlarmFixedHeader.uStruAlarm.struAlarmHardDisk.dwAlarmHardDiskNum;
                break;
            case 2:
            case 3:
            case 6:
            case 9:
            case 10:
            case 11:
            case 13:
            case 15:
            case 19:
            case 28:
                dwVerDataNum = ((LPNET_DVR_ALARMINFO_V40)pAlarmMsg)->struAlarmFixedHeader.uStruAlarm.struAlarmChannel.dwAlarmChanNum;
                break;
            default:
                dwVerDataNum = 0;
                break;

            }
            if (dwVerDataNum != 0)
            {
                ((LPNET_DVR_ALARMINFO_V40)pAlarmMsg)->pAlarmData = new DWORD[dwVerDataNum];
                memset(((LPNET_DVR_ALARMINFO_V40)pAlarmMsg)->pAlarmData, 0, dwVerDataNum * sizeof(DWORD));
                memcpy(((LPNET_DVR_ALARMINFO_V40)pAlarmMsg)->pAlarmData, ((LPNET_DVR_ALARMINFO_V40)pAlarmInfo)->pAlarmData, dwVerDataNum* sizeof(DWORD));

            }
            else
            {
                ((LPNET_DVR_ALARMINFO_V40)pAlarmMsg)->pAlarmData = NULL;
            }

        }
        else if (COMM_UPLOAD_VIDEO_INTERCOM_EVENT == lCommand)
        {
            LPNET_DVR_VIDEO_INTERCOM_EVENT pVideoIntercomEvent = (LPNET_DVR_VIDEO_INTERCOM_EVENT)pAlarmMsg;
            if (pVideoIntercomEvent->byEventType == 1 && pVideoIntercomEvent->uEventInfo.struUnlockRecord.dwPicDataLen > 0)
            {
                pVideoIntercomEvent->uEventInfo.struUnlockRecord.pImage = new BYTE[pVideoIntercomEvent->uEventInfo.struUnlockRecord.dwPicDataLen];
                memcpy(pVideoIntercomEvent->uEventInfo.struUnlockRecord.pImage, ((LPNET_DVR_VIDEO_INTERCOM_EVENT)pAlarmInfo)->uEventInfo.struUnlockRecord.pImage,
                    pVideoIntercomEvent->uEventInfo.struUnlockRecord.dwPicDataLen);
            }
            if (pVideoIntercomEvent->byEventType == 3 && pVideoIntercomEvent->uEventInfo.struAuthInfo.dwPicDataLen > 0)
            {
                pVideoIntercomEvent->uEventInfo.struAuthInfo.pImage = new BYTE[pVideoIntercomEvent->uEventInfo.struAuthInfo.dwPicDataLen];
                memcpy(pVideoIntercomEvent->uEventInfo.struAuthInfo.pImage, ((LPNET_DVR_VIDEO_INTERCOM_EVENT)pAlarmInfo)->uEventInfo.struAuthInfo.pImage,
                    pVideoIntercomEvent->uEventInfo.struAuthInfo.dwPicDataLen);
            }
        }
        else if (lCommand == COMM_UPLOAD_NOTICE_DATA)
        {
            for (int i = 0; i < MAX_NOTICE_PIC_NUM; i++)
            {
                if (((LPNET_DVR_NOTICE_DATA)pAlarmMsg)->struNoticePic[i].dwPicDataLen > 0)
                {
                    ((LPNET_DVR_NOTICE_DATA)pAlarmMsg)->struNoticePic[i].pPicData = new BYTE[((LPNET_DVR_NOTICE_DATA)pAlarmMsg)->struNoticePic[i].dwPicDataLen];
                    memset(((LPNET_DVR_NOTICE_DATA)pAlarmMsg)->struNoticePic[i].pPicData, 0, ((LPNET_DVR_NOTICE_DATA)pAlarmMsg)->struNoticePic[i].dwPicDataLen);
                    memcpy(((LPNET_DVR_NOTICE_DATA)pAlarmMsg)->struNoticePic[i].pPicData, ((LPNET_DVR_NOTICE_DATA)pAlarmInfo)->struNoticePic[i].pPicData, ((LPNET_DVR_NOTICE_DATA)pAlarmMsg)->struNoticePic[i].dwPicDataLen);
                }
            }
        }
        else if (lCommand == COMM_SWITCH_LAMP_ALARM)
        {
            ((LPNET_DVR_SWITCH_LAMP_ALARM)pAlarmMsg)->pPicData = new char[((LPNET_DVR_SWITCH_LAMP_ALARM)pAlarmMsg)->dwPicDataLen];
            memset(((LPNET_DVR_SWITCH_LAMP_ALARM)pAlarmMsg)->pPicData, 0, ((LPNET_DVR_SWITCH_LAMP_ALARM)pAlarmMsg)->dwPicDataLen);
            memcpy(((LPNET_DVR_SWITCH_LAMP_ALARM)pAlarmMsg)->pPicData, ((LPNET_DVR_SWITCH_LAMP_ALARM)pAlarmInfo)->pPicData, ((LPNET_DVR_SWITCH_LAMP_ALARM)pAlarmMsg)->dwPicDataLen);
        }

        else if (lCommand == COMM_ALARM_ACS)
        {
            ((LPNET_DVR_ACS_ALARM_INFO)pAlarmMsg)->pPicData = new char[((LPNET_DVR_ACS_ALARM_INFO)pAlarmMsg)->dwPicDataLen];
            memset(((LPNET_DVR_ACS_ALARM_INFO)pAlarmMsg)->pPicData, 0, ((LPNET_DVR_ACS_ALARM_INFO)pAlarmMsg)->dwPicDataLen);
            memcpy(((LPNET_DVR_ACS_ALARM_INFO)pAlarmMsg)->pPicData, ((LPNET_DVR_ACS_ALARM_INFO)pAlarmInfo)->pPicData, ((LPNET_DVR_ACS_ALARM_INFO)pAlarmMsg)->dwPicDataLen);
        }
        else if (lCommand == COMM_ID_INFO_ALARM)
        {
            if (((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pPicData > 0 && ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmInfo)->pPicData != NULL)
            {
                ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pPicData = new char[((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->dwPicDataLen];
                memset(((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pPicData, 0, ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->dwPicDataLen);
                memcpy(((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pPicData, ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmInfo)->pPicData, ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->dwPicDataLen);
            }
            if ((((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pFingerPrintData > 0) && (((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmInfo)->pFingerPrintData != NULL))
            {
                ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pFingerPrintData = new char[((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->dwFingerPrintDataLen];
                memset(((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pFingerPrintData, 0, ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->dwFingerPrintDataLen);
                memcpy(((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pFingerPrintData, ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmInfo)->pFingerPrintData, ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->dwFingerPrintDataLen);
            }
            if ((((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pCapturePicData > 0) && (((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmInfo)->pCapturePicData != NULL))
            {
                ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pCapturePicData = new char[((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->dwCapturePicDataLen];
                memset(((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pCapturePicData, 0, ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->dwCapturePicDataLen);
                memcpy(((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->pCapturePicData, ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmInfo)->pCapturePicData, ((LPNET_DVR_ID_CARD_INFO_ALARM)pAlarmMsg)->dwCapturePicDataLen);
            }
        }
        else if (lCommand == COMM_PANORAMIC_LINKAGE_ALARM)
        {
            if (((LPNET_DVR_PANORAMIC_LINKAGE)pAlarmMsg)->pPicBuff > 0 && ((LPNET_DVR_PANORAMIC_LINKAGE)pAlarmInfo)->pPicBuff != NULL)
            {
                ((LPNET_DVR_PANORAMIC_LINKAGE)pAlarmMsg)->pPicBuff = new char[((LPNET_DVR_PANORAMIC_LINKAGE)pAlarmMsg)->dwPicLen];
                memset(((LPNET_DVR_PANORAMIC_LINKAGE)pAlarmMsg)->pPicBuff, 0, ((LPNET_DVR_PANORAMIC_LINKAGE)pAlarmMsg)->dwPicLen);
                memcpy(((LPNET_DVR_PANORAMIC_LINKAGE)pAlarmMsg)->pPicBuff, ((LPNET_DVR_PANORAMIC_LINKAGE)pAlarmInfo)->pPicBuff, ((LPNET_DVR_PANORAMIC_LINKAGE)pAlarmMsg)->dwPicLen);
            }
        }

        else if (COMM_UPLOAD_HEATMAP_RESULT_PDC == lCommand)
        {
            int iLen = 0;
            for (int i = 0; i < 2; i++)
            {
                if ((((LPNET_DVR_HEATMAP_RESULT_PDC)pAlarmMsg)->struSingleHeatMap[i].wArrayColumn > 0) || (((LPNET_DVR_HEATMAP_RESULT_PDC)pAlarmMsg)->struSingleHeatMap[i].wArrayLine > 0))
                {
                    ((LPNET_DVR_HEATMAP_RESULT_PDC)pAlarmMsg)->struSingleHeatMap[i].pBuffer = (BYTE*)pAlarmMsg + sizeof(NET_DVR_HEATMAP_RESULT_PDC) + iLen;
                    iLen = ((LPNET_DVR_HEATMAP_RESULT_PDC)pAlarmMsg)->struSingleHeatMap[i].wArrayColumn * ((LPNET_DVR_HEATMAP_RESULT_PDC)pAlarmMsg)->struSingleHeatMap[i].wArrayLine;
                }
            }
        }
        LPLOCAL_ALARM_INFO pAlarmDev = new LOCAL_ALARM_INFO;
        if (pAlarmDev == NULL)
        {
            delete[] pAlarmMsg;
            pAlarmMsg = NULL;
            return;
        }
        pAlarmDev->iDeviceIndex = iDeviceIndex;
        pAlarmDev->lCommand = lCommand;
        memcpy(pAlarmDev->sDeviceIP, pAlarmer->sDeviceIP, 128);
        pAlarmDev->dwBufLen = dwBufLen;
        //the memery may be free.
        //g_pMainDlg->ProcDeviceAlarm((DWORD)pAlarmDev, (LONG)pAlarmMsg);


        ::PostMessage(g_pMainDlg->m_hWnd, WM_PROC_ALARM, (WPARAM)pAlarmDev, (LPARAM)pAlarmMsg);


    }
    catch (...)
    {
        OutputDebugString("New Alarm Exception!\n");
    }

    return;
}

/*********************************************************
Function:	MessageCallback
Desc:		alarm, callback functions dealing with the info of card in ATM
Input:	lCommand,message type; pAlarmer,info of device which upload message;pAlarmInfo, message info content;dwBufLen,message length; pUser, user parameter
Output:	
Return:	
**********************************************************/
void CALLBACK MessageCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void* pUser)
{
	//Sleep(100000);
	UNREFERENCED_PARAMETER(pUser);	
    AlarmMessage(lCommand, pAlarmer, pAlarmInfo, dwBufLen);
	
}

/*********************************************************
Function:	CClientDemoDlg
Desc:		Constructor
Input:	
Output:	
Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CClientDemoDlg, CDialog)
CClientDemoDlg::CClientDemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CClientDemoDlg::IDD, pParent)
, m_iCurDeviceIndex(-1)
, m_iCurChanIndex(-1)
, m_iCurWndIndex(0)//select current Output
, m_iMainType(PREVIEW_T)
, m_hCurDeviceItem(NULL)
, m_hCurChanItem(NULL)
, m_iCurRecDriver(0)
, m_pAutoRecTimer(NULL)
, m_pChkDevTimer(NULL)
, m_pCyclePlayTimer(NULL)
, m_pFreeSpaceTimer(NULL)
, m_pFileIntervalTimer(NULL)
, m_pSysTimer(NULL)
, m_iCardChanCount(0)
, m_iDriverNum(0)
, m_iTreeWidth(0)
, m_iRightWidth(0)
, m_iFunBtnHeight(0)
, m_iListLogHeight(0)
, m_bDrag(FALSE)
, m_iDragType(0)
, m_iDragChanIndex(-1)
, m_iDragParentIndex(-1)
, m_iCurWndNum(4)
, m_bListLogEnlarge(FALSE)
, m_bListAlarmEnlarge(FALSE)
, m_lListenHandle(-1)
, m_fLog(NULL)
, m_fAlarm(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    
	memset(&m_cHardDriver[0], 0, 26);
	memset(&m_struOldWndpl, 0, sizeof(WINDOWPLACEMENT));
    memset(&m_struSensorAlarm, 0, sizeof(m_struSensorAlarm));
	InitializeCriticalSection(&m_struLock);  //most thread might use log print function, especially alarm part, needing to add a lock
    InitializeCriticalSection(&g_cs);
	m_bSupportChanEx = FALSE;
	memset(&m_struVcaCtrlInfo, 0, sizeof(m_struVcaCtrlInfo));
	memset(&m_struIFrame, 0, sizeof(m_struIFrame));
	
}

/*********************************************************
Function:	~CClientDemoDlg
Desc:		destructor
Input:	
Output:	
Return:	
**********************************************************/
CClientDemoDlg::~CClientDemoDlg()
{
	if (m_fLog != NULL)
	{
		fclose(m_fLog);
	}
	if (m_fAlarm!= NULL)
	{
		fclose(m_fAlarm);
	}
	m_hIcon = NULL;
	m_hCurDeviceItem = NULL;
	m_hCurChanItem = NULL;
	g_pMainDlg = NULL;
	
	delete m_dlgRemoteCfg;
	
	delete m_dlgLocalCfg;
	
	delete m_dlgIPAccess;
	
	delete m_dlgHDConfig;
	
	delete m_dlgConfigAll;
	
	delete m_dlgOutputCtrl;
	
	delete m_dlgPlayBack;

	//delete m_pStreamIDDlg;

	delete m_dlgBatchCfg;

	delete m_dlgProductCfg;

	for (int i = 0; i < MAX_DEVICES; i++)
    {
        if (g_struDeviceInfo[i].pStruChanInfo != NULL)
        {
            delete[] g_struDeviceInfo[i].pStruChanInfo;
            g_struDeviceInfo[i].pStruChanInfo = NULL;
        }
		
        if (g_struDeviceInfo[i].pStruIPParaCfgV40 != NULL)
        {
            delete[] g_struDeviceInfo[i].pStruIPParaCfgV40;
            g_struDeviceInfo[i].pStruIPParaCfgV40 = NULL;
        }     
        
        if (g_struDeviceInfo[i].pStruIPAlarmInCfgV40 != NULL)
        {
            delete[]  g_struDeviceInfo[i].pStruIPAlarmInCfgV40 ;
            g_struDeviceInfo[i].pStruIPAlarmInCfgV40 = NULL;
        }
        
        if (g_struDeviceInfo[i].pStruIPAlarmOutCfgV40 != NULL)
        {
            delete[] g_struDeviceInfo[i].pStruIPAlarmOutCfgV40;
            g_struDeviceInfo[i].pStruIPAlarmOutCfgV40 = NULL;
        }
		
		
    }
    
	DeleteCriticalSection(&g_cs);
	DeleteCriticalSection(&m_struLock);
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDemoDlg)
	DDX_Control(pDX, IDC_BTN_PLAY, m_btnPlay);
	DDX_Control(pDX, IDC_BTN_RECORD, m_btnRecord);
	DDX_Control(pDX, IDC_TREE_DEVICE_LIST, m_treeDeviceList);
	DDX_Control(pDX, IDC_COMBO_WNDNUM, m_comboWinNum);
	DDX_Control(pDX, IDC_COMBO_NETDELAY, m_comboNetDelayBufNum);
	DDX_Control(pDX, IDC_LIST_ALL_LOG, m_listAllLog);
	DDX_Control(pDX, IDC_LIST_ALARM_INFO, m_listAlarmInfo);
	//}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CClientDemoDlg, CDialog)
//{{AFX_MSG_MAP(CClientDemoDlg)
ON_WM_TIMER()
ON_WM_MOVE()
ON_NOTIFY(NM_CLICK, IDC_TREE_DEVICE_LIST, OnNMClickTreeDeviceList)
ON_NOTIFY(NM_RCLICK, IDC_TREE_DEVICE_LIST, OnNMRclickTreeDeviceList)
ON_NOTIFY(NM_DBLCLK, IDC_TREE_DEVICE_LIST, OnNMDblclkTreeDeviceList)
ON_CBN_SELCHANGE(IDC_COMBO_WNDNUM, OnCbnSelchangeComboWndNum)
ON_BN_CLICKED(IDC_BTN_CONFIG, OnBnClickedBtnConfig)
ON_BN_CLICKED(IDC_BTN_RECORD, OnBnClickedBtnRecord)
ON_CBN_SELCHANGE(IDC_COMBO_NETDELAY, OnCbnSelchangeComboNetdelay)
ON_BN_CLICKED(IDC_BTN_PLAY_BACK, OnBnClickedBtnPlayback)
ON_BN_CLICKED(IDC_BTN_MANAGE, OnBnClickedBtnManage)
ON_BN_CLICKED(IDC_BTN_LOG_CLEAR, OnBnClickedBtnLogClear)
ON_BN_CLICKED(IDC_BTN_LOG_SAVE, OnBnClickedBtnLogSave)
ON_BN_CLICKED(IDC_BTN_MAKE_IFRAME, OnBnClickedBtnMakeIframe)
ON_BN_CLICKED(IDC_BTN_LOG_CONFIG, OnBnClickedBtnLogConfig)
ON_NOTIFY(NM_CLICK, IDC_LIST_ALL_LOG, OnNMClickListAllLog)
ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBnClickedBtnPreview)
ON_BN_CLICKED(IDC_BTN_EXIT, OnBnClickedBtnExit)
ON_BN_CLICKED(IDC_BTN_PLAY, OnBnClickedBtnPlay)
ON_BN_CLICKED(IDC_BTN_PICTURE_SNATCH, OnBnClickedBtnPictureSnatch)
ON_BN_CLICKED(IDC_BTN_ELSE, OnBnClickedBtnElse)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_ALL_LOG, OnDblclkListAllLog)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_ALARM_INFO, OnDblclkListAlarmInfo)
ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_ALL_LOG, OnColumnclickListAllLog)
ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_ALARM_INFO, OnColumnclickListAlarmInfo)
ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
ON_BN_CLICKED(IDC_RADIO_LOCAL_LOG, OnRadioLocalLog)
ON_BN_CLICKED(IDC_RADIO_ALARM_INFO, OnRadioAlarmInfo)
ON_COMMAND(ID_MENU_SENSOR_ADD_PREVIEW, OnMenuSensorAddPreview)
ON_COMMAND(ID_MENU_HOLIDAY_CFG, OnMenuHolidayCfg)
ON_COMMAND(ID_MENU_T1Test, OnMENUT1Test)
ON_COMMAND(ID_MENU_T1Test, OnMENUT1Test)
ON_COMMAND(ID_MENU_PRODUCTION_LINE_TEST, OnMenuProductionLineTest)
ON_COMMAND(ID_MEMU_IPERF, OnMenuIperf)
ON_WM_HSCROLL()
ON_COMMAND(ID_MENU_DEVICE_ADD, OnMenuDeviceAdd)
ON_COMMAND(ID_MENU_DEVICE_DELETE, OnMenuDeviceDelete)
ON_COMMAND(ID_MENU_LOGOUT, OnMenuLogout)
ON_COMMAND(ID_MENU_DEVICE_INFO, OnMenuDeviceInfo)
ON_COMMAND(ID_MENU_CHANNEL_INFO, OnMenuChannelInfo)
ON_COMMAND(ID_MENU_JPEG_SNATCH_CONFIG, OnMenuJPEGSnatchConfig)
ON_COMMAND(ID_MENU_DEVICE_CHECK_TIME, OnMenuCheckTime)
ON_COMMAND(ID_MENU_UPGRADE, OnMenuUpgrade)
ON_COMMAND(ID_MENU_REBOOT, OnMenuReboot)
ON_COMMAND(ID_MENU_HD_FORMAT, OnMenuHDFormat)
ON_COMMAND(ID_MENU_POWEROFF, OnMenuPoweroff)
ON_COMMAND(ID_MENU_FORTIFY, OnMenuFortify)
ON_COMMAND(ID_MENU_VOICE_TALK, OnMenuVoiceTalk)
ON_COMMAND(ID_MENU_REMOTE_KEY, OnMenuRemoteKey)
ON_COMMAND(ID_MENU_VOICE_BROADCAST, OnMenuBroadCast)
ON_COMMAND(ID_MENU_DVR_LOCAL_RECORD, OnMenuDVRRecordStart)
ON_COMMAND(ID_MENU_LOG_SEARCH, OnMenuLogSearch)
ON_COMMAND(ID_MENU_WORK_STATE, OnMenuWorkState)
ON_COMMAND(ID_MENU_CONFIG_RESTORE, OnMenuDefaultConfig)
ON_COMMAND(ID_MENU_SERIAL_TRANS, OnMenuSerialTrans)
ON_COMMAND(ID_MENU_CONFIG_FLASH, OnMenuConfigFlash)
ON_COMMAND(ID_MENU_TALK_MR, OnMenuTalkMR)
ON_MESSAGE(WM_PROC_ALARM, OnWMProcAlarm)
ON_MESSAGE(WM_CHANGE_CHANNEL_ITEM_IMAGE,ChangeChannelItemImage)
ON_MESSAGE(WM_CHANGE_DEVICE_ITEM_IMAGE,ChangeDeviceItemImage)
ON_MESSAGE(WM_ADD_LOG, OnWMAddLog)
ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
ON_COMMAND(ID_MENU_PRODUCTION_LINE_TEST_EN, OnMenuProductionLineTest)
ON_COMMAND(IDM_MENU_VCA, OnMenuVca)
ON_BN_CLICKED(IDC_BTN_PRODUCT_CFG,OnBtntProductCfg)
ON_COMMAND(ID_MENU_COMPLETE_RESTORE, OnMenuCompleteRestore)
ON_COMMAND(ID_MENU_DEBUG, OnMenuDebug)
ON_COMMAND(ID_MENU_UPLOAD_CALIBRATION_FILE, OnMenuUploadCalibrationFile)
	//}}AFX_MSG_MAP
    ON_COMMAND(ID_ALARM_SEARCH, &CClientDemoDlg::OnMenuSearchAlarm)
END_MESSAGE_MAP()


// CClientDemoDlg message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CClientDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//CBrush cbr.CreateSolidBrush(COLORREF(0xffffff));//white
	// TODO: Add extra initialization here//////////////////////////////////////////////////////////////
	//
	//get path of configuration file
	char szLan[128] = {0};
	
	memset(g_szWorkDir, 0, MAX_PATH);
	GetCurrentPath(g_szWorkDir);
	//2012-06-21 先按照默认目录创建，否则当本地配置文件无数据时将无保存目录，此时导出配置文件将失败
	g_CreateLocalDir();
	ReadLocalConfig();
	g_ReadDeviceConfig();
    g_ReadLocalReadSensorAdd();
	InitGlobalSysInfo();
	InitChildWindow();
	
	//initialize main window
	InitMainWin();
	
	LoadTreeImage();
	CreateTree();
	//for the demo log and alarm info
	CreateNewLogFile(g_struLocalParam.bAutoSaveLog);
	
	m_iCurRecDriver = m_cHardDriver[g_struLocalParam.iStartRecordDriver];
	
	m_pAutoRecTimer = SetTimer(AUTORECORD_TIMER, 2000, NULL);
	
	if (g_struLocalParam.bAutoCheckDeviceTime)
	{
		AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "Start DVR timing, the school time is %06d", g_struLocalParam.lCheckDeviceTime);
		m_pChkDevTimer = SetTimer(CHECK_DEVICE_TIMER, 1000, NULL);
	}
	m_pFreeSpaceTimer = SetTimer(FREESPACE_TIMER, 5000, NULL);
	m_pFileIntervalTimer = SetTimer(FILEINTERVAL_TIMER, 2000, NULL);
	
	m_pSysTimer = SetTimer(SYSTEM_TIMER, 1000, NULL);//refresh time on time
	
	//SDK uploads the info such as alarm and log sent from DVR by calling callback function 
    //NET_DVR_SetDVRMessageCallBack_V30(MessageCallback, NULL);
    NET_DVR_SetDVRMessageCallBack_V51(0, MessageCallback, NULL);
	//SDK detects exception and uploads it, such as network disconnect
	
	NET_DVR_SetLogToFile(g_struLocalParam.nLogLevel, "c:\\SdkLogTest\\", g_struLocalParam.bCycleWriteLog);
	AddLog(-1, OPERATION_FAIL_T, "sdk v%x", NET_DVR_GetSDKBuildVersion());
	NET_DVR_SetExceptionCallBack_V30(WM_NULL/*WM_MYCOMMAND*/, NULL/*this->m_hWnd*/, g_ExceptionCallBack, NULL);
	NET_DVR_SetReconnect(5000, g_struLocalParam.bReconnect);
	if (!NET_DVR_SetShowMode(NORMALMODE, RGB(255, 255, 255)))
	{
		AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SetShowMode");
	}
	PlayM4_InitDDrawDevice();

    char exeFullPath[MAX_PATH] = { 0 }; // Full path
    CString strExePath = "";

    //获取exe所在路径

    GetModuleFileName(NULL, exeFullPath, MAX_PATH);
    strExePath = exeFullPath;    // Get full path of the file
    int pos = strExePath.ReverseFind('\\');
    CString stringXSDPath = strExePath.Left(pos);  // Return the directory without the file name
    stringXSDPath = stringXSDPath + "\\ClientDemoDll\\libxml2.dll";

    g_hDllInst = LoadLibraryEx(stringXSDPath ,NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	//calib.dll
	CString stringcalibath = strExePath.Left(pos);  // Return the directory without the file name
	stringcalibath = stringXSDPath + "\\ClientDemoDll\\calib.dll";

	g_hDllCalib = LoadLibraryEx(stringcalibath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

    //libcurl.dll
    CString stringCurlPath = strExePath.Left(pos);  // Return the directory without the file name
    stringCurlPath = strExePath.Left(pos) + "\\ClientDemoDll\\libcurl.dll";

    g_hDllCurlLib = LoadLibraryEx(stringCurlPath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*********************************************************
Function:	RegisterPlayer
Desc:		register the player or unregister
Input:	bRegister, TRUE=register, FALSE=unregister;
Output:	none
Return:	TRUE/FALSE
**********************************************************/
BOOL CClientDemoDlg::RegisterPlayer(BOOL bRegister)
{
	STARTUPINFO  si;  
	ZeroMemory(&si,  sizeof(si));  
	si.cb  =  sizeof  STARTUPINFO;  
	
	char* pCmdLine=new char[4096];
	
	PROCESS_INFORMATION  pi;  
	BOOL  res  =  FALSE;
	char szCurPath[256] = {0};
	GetCurrentPath(szCurPath);
	//sprintf(szCurPath, "%s\\", szCurPath);
	if (bRegister)
	{
	sprintf(pCmdLine, "regsvr32 %s\\PLAYSDK_DefSource.dll /s\
															  %s\\PLAYSDK_StreamSource.dll /s\
															  %s\\PLAYSDK_Sample.dll /s\
															  %s\\PLAYSDK_DefDemux.dll /s\
															  %s\\PLAYSDK_RFCDemux.dll /s\
															  %s\\PLAYSDK_MPEG2Source.dll /s\
															  %s\\PLAYSDK_MPEG2Demux.dll /s\
															  %s\\PLAYSDK_H264Dec.dll /s\
															  %s\\PLAYSDK_Mpeg4Dec.dll /s\
															  %s\\PLAYSDK_G722Dec.dll /s\
															  %s\\PLAYSDK_G711Dec.dll /s\
															  %s\\PLAYSDK_VTrans.dll /s\
															  %s\\PLAYSDK_ARenderer.dll /s\
															  %s\\PLAYSDK_VRenderer.dll /s\
															  %s\\PLAYSDK_Image.dll /s",\
															  szCurPath, szCurPath, szCurPath, szCurPath, szCurPath\
															  , szCurPath, szCurPath, szCurPath, szCurPath, szCurPath,\
															  szCurPath, szCurPath, szCurPath, szCurPath, szCurPath);
	}
	else
	{
	sprintf(pCmdLine, "regsvr32 -u %s\\PLAYSDK_DefSource.dll /s\
																 -u %s\\PLAYSDK_StreamSource.dll /s\
																 -u %s\\PLAYSDK_Sample.dll /s\
																 -u %s\\PLAYSDK_DefDemux.dll /s\
																 -u %s\\PLAYSDK_RFCDemux.dll /s\
																 -u %s\\PLAYSDK_MPEG2Source.dll /s\
																 -u %s\\PLAYSDK_MPEG2Demux.dll /s\
																 -u %s\\PLAYSDK_H264Dec.dll /s\
																 -u %s\\PLAYSDK_Mpeg4Dec.dll /s\
																 -u %s\\PLAYSDK_G722Dec.dll /s\
																 -u %s\\PLAYSDK_G711Dec.dll /s\
																 -u %s\\PLAYSDK_VTrans.dll /s\
																 -u %s\\PLAYSDK_ARenderer.dll /s\
																 -u %s\\PLAYSDK_VRenderer.dll /s\
																 -u %s\\PLAYSDK_Image.dll /s",\
																 szCurPath, szCurPath, szCurPath, szCurPath, szCurPath\
																 , szCurPath, szCurPath, szCurPath, szCurPath, szCurPath,\
																 szCurPath, szCurPath, szCurPath, szCurPath, szCurPath);
	}
	res = CreateProcess(NULL,  
		pCmdLine,  // execute dos command 
		NULL,  
		NULL,  
		NULL,  
		NORMAL_PRIORITY_CLASS,//    |  CREATE_NO_WINDOW,  
		NULL,  
		NULL,  
		&si,  
		&pi);  
	
	
	if  (TRUE == res)  
	{  
		CloseHandle(pi.hProcess);  
		CloseHandle(pi.hThread);  
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "register player fail!");
	}
	if (pCmdLine != NULL)
	{
		delete [] pCmdLine;
	}
	return res;
}

/*********************************************************
Function:	OnPaint
Desc:	    refresh dialog
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the szUser drags
//  the minimized window.
/*********************************************************
Function:	OnQueryDragIcon
Desc:	    drag mouse to initialize function
Input:	
Output:	
Return:	
**********************************************************/
HCURSOR CClientDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*********************************************************
Function:	InitHardDriver
Desc:		get pc basic info
Input:	
Output:	
Return:	
**********************************************************/
BOOL CClientDemoDlg::InitHardDriver()
{
	DWORD dw=GetLogicalDriveStrings(0,NULL);
	LPTSTR pAllDrivers=new char[dw];
	::GetLogicalDriveStrings(dw,pAllDrivers);
	LPTSTR pDriver=pAllDrivers;
	char tempDriver[26];
	DWORD nDriverNum=0;
	char *pTmp;
	
	while (pDriver[0]!=0)
	{
		tempDriver[nDriverNum++]=*pDriver;
		if ( (pTmp = _tcschr(pDriver,0)) != NULL)
		{
			pDriver=pTmp+1;          //locate to next driver
		}
		
	}
	
	//volume information
	TCHAR lpVolumeNameBuffer[200];
	DWORD dwVolumeSerialNumber,dwMaxComLength;
	DWORD dwFileSystemFlags;
	TCHAR lpFileSystemNameBuffer[50];
	
	DWORD nHardNum=0;
	for (DWORD i=0;i<nDriverNum;i++)
	{
		CString csRecRootPath;
		csRecRootPath.Format("%c%s",tempDriver[i],":\\");
		
		if (GetDriveType(csRecRootPath)==DRIVE_FIXED)
		{
			if (GetVolumeInformation(csRecRootPath,lpVolumeNameBuffer,sizeof(lpVolumeNameBuffer),&dwVolumeSerialNumber,
				&dwMaxComLength,&dwFileSystemFlags,lpFileSystemNameBuffer,sizeof(lpFileSystemNameBuffer)))
			{			
				this->m_cHardDriver[nHardNum++]=tempDriver[i];
			}
		}
	}
	m_iDriverNum=nHardNum;	
	delete[] pAllDrivers;
	return TRUE;
}

/*********************************************************
Function:	InitDecodeCard
Desc:		initialize decode card
Input:	
Output:	
Return:	TRUE,initialization succeed;FALSE,initialization failed;
**********************************************************/
BOOL CClientDemoDlg::InitDecodeCard()
{
	SetDecoderVideoExtOutputProc DLINK_SetDecoderVideoExtOutput;
	SetDisplayRegionProc DLINK_SetDisplayRegion;
	SetDisplayStandardProc DLINK_SetDisplayStandard;
	GetDisplayChannelCountProc DLINK_GetDisplayChannelCount;
	
	DLINK_SetDecoderVideoExtOutput = (SetDecoderVideoExtOutputProc)GetProcAddress(g_hDSSDK, "SetDecoderVideoExtOutput");
	DLINK_SetDisplayRegion = (SetDisplayRegionProc)GetProcAddress(g_hDSSDK, "SetDisplayRegion");
	DLINK_SetDisplayStandard = (SetDisplayStandardProc)GetProcAddress(g_hDSSDK, "SetDisplayStandard");
	DLINK_GetDisplayChannelCount = (GetDisplayChannelCountProc)GetProcAddress(g_hDSSDK, "GetDisplayChannelCount");

	int nDispNum = 0;
	char szLan[128] = {0};
	
	if (!NET_DVR_InitDDraw_Card(GetDlgItem(IDC_STATIC_PREVIEWBG)->m_hWnd,0xffffff))//dark blue 0xff2200
	{
		AddLog(-1, OPERATION_FAIL_T, "NET_DVR_InitDDraw_Card\n");
		return FALSE;
	}
	
	m_iCardChanCount = 0;
	if (!NET_DVR_InitDevice_Card(&m_iCardChanCount))
	{
		AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InitDevice_Card\n");
		return FALSE;
	}
	AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "Decoder Card Channel Num=%d", m_iCardChanCount);	
	if (m_iCardChanCount <= 0)
	{
		g_StringLanType(szLan, "请插入解码卡", "Please Insert Decoder Card");
		//AfxMessageBox(szLan);
		return FALSE;
	}
	else if (m_iCardChanCount > 16)
	{
		m_iCardChanCount = 16;
	}
	
	if (g_struLocalParam.bNTSC)
	{
		nDispNum = DLINK_GetDisplayChannelCount();
		if (nDispNum >= 2)
		{
			REGION_PARAM struDisplayRegion[MAX_DISPLAY_REGION];
			int i;
			memset(struDisplayRegion, 0, sizeof(struDisplayRegion));
			for (i=0; i<MAX_DISPLAY_REGION; i++)
				struDisplayRegion[i].color = RGB(i, i*8, i*16);
			for (i=0; i<nDispNum/2; i++)
			{
				DLINK_SetDisplayStandard(2*i,StandardNTSC);
				struDisplayRegion[0].left=0;	struDisplayRegion[0].top=0;		struDisplayRegion[0].width=352;		struDisplayRegion[0].height=240;
				struDisplayRegion[1].left=352;	struDisplayRegion[1].top=0;		struDisplayRegion[1].width=352;		struDisplayRegion[1].height=240;
				struDisplayRegion[2].left=0;	struDisplayRegion[2].top=240;	struDisplayRegion[2].width=352;		struDisplayRegion[2].height=240;
				struDisplayRegion[3].left=352;	struDisplayRegion[3].top=240;	struDisplayRegion[3].width=352;		struDisplayRegion[3].height=240;
				if (DLINK_SetDisplayRegion(2*i, 4, struDisplayRegion, 0) != HWERR_SUCCESS)
				{
					AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "SetDisplayRegion!");
				}				
				DLINK_SetDecoderVideoExtOutput(4*i, 0, 1, 2*i, 0, 0);
				DLINK_SetDecoderVideoExtOutput(4*i+1, 0, 1, 2*i, 1, 0);		
				DLINK_SetDecoderVideoExtOutput(4*i+2, 0, 1, 2*i, 2, 0);
				DLINK_SetDecoderVideoExtOutput(4*i+3, 0, 1, 2*i, 3, 0);
				
				DLINK_SetDisplayStandard(2*i+1,StandardNTSC);
				struDisplayRegion[0].left=0;	struDisplayRegion[0].top=0;		struDisplayRegion[0].width=704;		struDisplayRegion[0].height=480;
				if (DLINK_SetDisplayRegion(2*i+1, 1, struDisplayRegion, 0) != HWERR_SUCCESS)
				{
					AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "SetDisplayRegion failed!");
				}
				
				DLINK_SetDecoderVideoExtOutput(4*i, 1, 1, 2*i+1, 0, 0);		
			}			
		}
	}
	else
	{
		nDispNum = DLINK_GetDisplayChannelCount();
		if (nDispNum >= 2)
		{
			REGION_PARAM struDisplayRegion[MAX_DISPLAY_REGION];
			int i;
			memset(struDisplayRegion, 0, sizeof(struDisplayRegion));
			for (i=0; i<MAX_DISPLAY_REGION; i++)
				struDisplayRegion[i].color = RGB(i, i*8, i*16);
			for (i=0; i<nDispNum/2; i++)
			{
				DLINK_SetDisplayStandard(2*i,StandardPAL);
				struDisplayRegion[0].left=0;	struDisplayRegion[0].top=0;		struDisplayRegion[0].width=352;		struDisplayRegion[0].height=288;
				struDisplayRegion[1].left=352;	struDisplayRegion[1].top=0;		struDisplayRegion[1].width=352;		struDisplayRegion[1].height=288;
				struDisplayRegion[2].left=0;	struDisplayRegion[2].top=288;	struDisplayRegion[2].width=352;		struDisplayRegion[2].height=288;
				struDisplayRegion[3].left=352;	struDisplayRegion[3].top=288;	struDisplayRegion[3].width=352;		struDisplayRegion[3].height=288;
				if (DLINK_SetDisplayRegion(2*i, 4, struDisplayRegion, 0) != HWERR_SUCCESS)
				{
					AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "SetDisplayRegion failed!");
				}				
				DLINK_SetDecoderVideoExtOutput(4*i, 0, 1, 2*i, 0, 0);
				DLINK_SetDecoderVideoExtOutput(4*i+1, 0, 1, 2*i, 1, 0);		
				DLINK_SetDecoderVideoExtOutput(4*i+2, 0, 1, 2*i, 2, 0);
				DLINK_SetDecoderVideoExtOutput(4*i+3, 0, 1, 2*i, 3, 0);
				
				DLINK_SetDisplayStandard(2*i+1,StandardPAL);
				struDisplayRegion[0].left=0;	struDisplayRegion[0].top=0;		struDisplayRegion[0].width=704;		struDisplayRegion[0].height=576;
				if (DLINK_SetDisplayRegion(2*i+1, 1, struDisplayRegion, 0) != HWERR_SUCCESS)
				{
					AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "SetDisplayRegion failed!");
				}
				
				DLINK_SetDecoderVideoExtOutput(4*i, 1, 1, 2*i+1, 0, 0);		
			}			
		}
	}
	
	if (m_iCardChanCount==1)
	{
		m_iCurWndNum =1;
		m_comboWinNum.SetCurSel(0); 
	}
	else if (m_iCardChanCount<=4)
	{
		m_iCurWndNum = 4;
		m_comboWinNum.SetCurSel(1);
	}
	else if (m_iCardChanCount<=9)
	{
		m_iCurWndNum = 9;
		m_comboWinNum.SetCurSel(2);
	}
	else
	{
		m_iCurWndNum = 16;
		m_comboWinNum.SetCurSel(3);
	}
    m_comboWinNum.EnableWindow(FALSE);
	return TRUE;
}

/*********************************************************
Function:	InitGlobalSysInfo
Desc:		initialize global system info
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::InitGlobalSysInfo()
{
	InitHardDriver();
	
	g_pMainDlg = this;
	//initialize hardware decode background
	g_hPlayHardBgBrush = ::CreateSolidBrush(COLORREF(0xff2200));//dark blue0xff2200
	
	//initialize software decode background
	g_hPlaySoftBgBrush = ::CreateSolidBrush(COLORREF(0xffffff));//white
	if (g_struLocalParam.bUseCard)
	{
		if (InitDecodeCard())
		{
			g_bCardInit = TRUE;
			AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "InitDecodeCard success");
		}
		else
		{
			g_bCardInit = FALSE;
			AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "InitDecodeCard fail");
		}
	}
	
	//get current system resolution
	g_iCurScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	g_iCurScreenHeight = GetSystemMetrics(SM_CYSCREEN);
}

/*********************************************************
Function:	GetVersionInfor
Desc:		get version information
Input:	
Output:	
Return:	
**********************************************************/
typedef DWORD (WINAPI *VGetFileVersionInfoSize)(LPSTR lptstrFilename, LPDWORD lpdwHandle);  
typedef BOOL (WINAPI *VGetFileVersionInfo)(LPSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
typedef BOOL(WINAPI *VVerQueryValue)(const LPVOID pBlock,LPSTR lpSubBlock,LPVOID * lplpBuffer, PUINT puLen);
VGetFileVersionInfoSize vgetsize;
VGetFileVersionInfo vfileinfo;
VVerQueryValue vqureyvalue;
void CClientDemoDlg::GetVersionInfor()
{
	DWORD m_dwSize = 0;
	HMODULE handle = LoadLibrary("version.dll"); //there is no this library on win2000
	if (handle == NULL)
	{
		return;
	}
	vgetsize = (VGetFileVersionInfoSize)GetProcAddress(handle, "GetFileVersionInfoSizeA");
	m_dwSize = GetLastError();
	vfileinfo = (VGetFileVersionInfo)GetProcAddress(handle, "GetFileVersionInfoA");
	vqureyvalue = (VVerQueryValue)GetProcAddress(handle, "VerQueryValueA");
	char szInfo[128] = {0};
	m_dwSize = vgetsize("HCNetSDK.dll", NULL); 
	if (m_dwSize > 0)
	{
		char * m_lpBuffer   =   new char[m_dwSize];   
		char *lpSDKVersion = NULL;    
		//Get   the   versioninformation   block   
		BOOL bRet = vfileinfo("HCNetSDK.dll", 0, m_dwSize, m_lpBuffer);   
		
		struct LANGANDCODEPAGE {
		  WORD wLanguage;
		  WORD wCodePage;
		} *lpTranslate;
		DWORD cbTranslate = 0;
		vqureyvalue(m_lpBuffer, 
					  TEXT("\\VarFileInfo\\Translation"),
					  (LPVOID*)&lpTranslate,
					  (PUINT)&cbTranslate);
		wsprintf(szInfo, TEXT( "\\StringFileInfo\\%04x%04x\\FileVersion"), 
				lpTranslate-> wLanguage, 
				lpTranslate-> wCodePage); 

		bRet = vqureyvalue(m_lpBuffer,   
				szInfo,   
				(void **) &lpSDKVersion,   
				NULL); 
		char * m_lpSDKBuild = NULL;
		wsprintf(szInfo, TEXT( "\\StringFileInfo\\%04x%04x\\FileDescription"), 
				lpTranslate-> wLanguage, 
				lpTranslate-> wCodePage); 
		bRet = vqureyvalue(m_lpBuffer,   
				szInfo,  
				(void **) &m_lpSDKBuild,   
				NULL);   
		GetDlgItem(IDC_STATIC_DEMO_VERSION)->SetWindowText(m_lpSDKBuild);
		AddLog(-1, OPERATION_SUCC_T, "FileVersion%s %s", lpSDKVersion, m_lpSDKBuild);
		delete [] m_lpBuffer;
	}
	else
	{
		m_dwSize = GetLastError();
	}
}

/*********************************************************
Function:	InitMainWin
Desc:		demo main window layout
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::InitMainWin()
{
	m_iTreeWidth = 165;		//device tree width
	m_iRightWidth = 160;	//PTZ pic box width
	m_iFunBtnHeight = 85;	 //column height
	m_iListLogHeight = 110 ;//list log height
	char szLan[128] = {0};
	
	
	m_listAlarmInfo.InsertColumn(0,"",LVCFMT_LEFT,0,-1); 
	g_StringLanType(szLan, "时间", "Time");
	m_listAlarmInfo.InsertColumn(1, szLan,LVCFMT_LEFT,150);
	g_StringLanType(szLan, "报警信息", "Alarm Info");
	m_listAlarmInfo.InsertColumn(2, szLan,LVCFMT_LEFT,400);
	g_StringLanType(szLan, "设备信息", "Device Info");
	m_listAlarmInfo.InsertColumn(3, szLan,LVCFMT_LEFT,160);
	m_listAlarmInfo.SetExtendedStyle(m_listAlarmInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	
	m_listAllLog.InsertColumn(0, "", LVCFMT_LEFT, 0, -1); 
	g_StringLanType(szLan, "时间", "Time");
	m_listAllLog.InsertColumn(1, szLan, LVCFMT_LEFT, 120);
	g_StringLanType(szLan, "状态", "State");
	m_listAllLog.InsertColumn(2, szLan, LVCFMT_LEFT, 40);
	g_StringLanType(szLan, "操作", "Operation");
	m_listAllLog.InsertColumn(3, szLan, LVCFMT_LEFT, 300);
	g_StringLanType(szLan, "设备信息", "Device Info");
	m_listAllLog.InsertColumn(4,szLan,LVCFMT_LEFT,140);
	g_StringLanType(szLan, "错误信息", "Error Info");
	m_listAllLog.InsertColumn(5,szLan,LVCFMT_LEFT,80);
	m_listAllLog.SetExtendedStyle(m_listAllLog.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	if (g_bInSide)
	{
		m_comboWinNum.ResetContent();
		m_comboWinNum.AddString("1");
		m_comboWinNum.AddString("4");
		m_comboWinNum.AddString("9");
		m_comboWinNum.AddString("16");
		m_comboWinNum.AddString("25");
		m_comboWinNum.AddString("36");
		m_comboWinNum.AddString("49");
		m_comboWinNum.AddString("64");
		m_comboWinNum.AddString("81");
        m_comboWinNum.AddString("100");
        m_comboWinNum.AddString("121");
        m_comboWinNum.AddString("144");
        m_comboWinNum.AddString("169");
        m_comboWinNum.AddString("196");
        m_comboWinNum.AddString("225");
        m_comboWinNum.AddString("256");
	}
	
	m_iSelListType = 0;//local log
	((CButton *)GetDlgItem(IDC_RADIO_LOCAL_LOG))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO_ALARM_INFO))->SetCheck(FALSE);
	OnSelchangeComboListType();
	MoveWindow(0, 0, DEMO_FULL_WIDTH, DEMO_FULL_HEIGHT, TRUE);

    GetVersionInfor();
	CString csTemp = _T("");
	DWORD dwVersion = NET_DVR_GetSDKBuildVersion();
	
	csTemp.Format("HCNetSDK V%d.%d.%d.%d", (0xff000000 & dwVersion)>>24, (0x00ff0000 & dwVersion)>>16,\
		(0x0000ff00 & dwVersion)>>8, (0x000000ff & dwVersion));//%.d,0x0000ff & dwVersion,build NO. do not expose
	GetDlgItem(IDC_STATIC_SDK_VERSION)->SetWindowText(csTemp);
	
	dwVersion = PlayM4_GetSdkVersion();
	csTemp.Format("PlayCtrl V%d.%d.%d.%d", (0xff000000 & dwVersion)>>24, (0x00ff0000 & dwVersion)>>16,\
		(0x0000ff00 & dwVersion)>>8, (0x000000ff & dwVersion));
	GetDlgItem(IDC_STATIC_PLAYM4_VERSION)->SetWindowText(csTemp);
	
	InitPreviewRect();//preview window, part of main window
}


/*********************************************************
Function:	InitChildWindow
Desc:		initialize child window
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::InitChildWindow(void)
{
	for (int i = 0; i < MAX_OUTPUTS; i++)
	{
		g_dlgOutput[i].m_iSubWndIndex = i;
		g_dlgOutput[i].Create(IDD_DLG_OUTPUT,this);
	}
	m_dlgRemoteCfg = new CDlgRemoteCfg;
	m_dlgRemoteCfg->Create(IDD_DLG_REMOTE_CFG,this);
	m_dlgRemoteCfg->ShowWindow(SW_HIDE);
	
	m_dlgLocalCfg = new CDlgLocalConfig;
	m_dlgLocalCfg->Create(IDD_DLG_LOCAL_CONFIG, this);
	m_dlgLocalCfg->ShowWindow(SW_HIDE);
	
	m_dlgIPAccess = new CDlgRemoteIPAccess;
	m_dlgIPAccess->Create(IDD_DLG_REMOTE_IP_ACCESS_CFG, this);
	m_dlgIPAccess->ShowWindow(SW_HIDE);
	
	m_dlgHDConfig = new CDlgHardDiskCfg;
	m_dlgHDConfig->Create(IDD_DLG_HARD_DISK_CFG, this);
	m_dlgHDConfig->ShowWindow(SW_HIDE);
	
	m_dlgConfigAll = new CDlgConfigAll;
	m_dlgConfigAll->Create(IDD_DLG_CONFIG_ALL, this);
	m_dlgConfigAll->ShowWindow(SW_HIDE);
	
	m_dlgOutputCtrl = new CDlgOutputCtrl;
	m_dlgOutputCtrl->Create(IDD_DLG_OUTPUT_CTRL, this);
	m_dlgOutputCtrl->ShowWindow(SW_HIDE);

	m_dlgPlayBack = new CDlgPlayBack;
	m_dlgPlayBack->Create(IDD_DLG_PLAY_BACK, this);
	m_dlgPlayBack->ShowWindow(SW_HIDE);

// 	m_pStreamIDDlg = new CDlgStreamID;
// 	m_pStreamIDDlg->Create(IDD_DLG_STREAM_ID, this);
// 	m_pStreamIDDlg->ShowWindow(SW_HIDE);

	m_dlgBatchCfg = new CDlgBatchConfig;
	m_dlgBatchCfg->Create(IDD_DLG_BATCH_CONFIG, this);
	m_dlgBatchCfg->ShowWindow(SW_HIDE);

	m_dlgProductCfg = new CDlgProductCfg;
	m_dlgProductCfg->Create(IDD_DLG_PRODUCT_CFG,this);
	m_dlgProductCfg->ShowWindow(SW_HIDE);
}
/*********************************************************
Function:	CreateTree
Desc:		create device tree
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::CreateTree(void)
{
	m_treeDeviceList.DeleteAllItems();
	char szLan[128] = {0};
	g_StringLanType(szLan, "设备树(右击添加设备)", "Device Tree(Right Click to Add Device)");
	HTREEITEM hRoot = m_treeDeviceList.InsertItem(szLan, TREE_ALL, TREE_ALL);
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	int j = 0;
	HTREEITEM hDevice = NULL;
	HTREEITEM hChan = NULL;
	for (i = 0; i < MAX_DEVICES; i++)
	{
		if (g_struDeviceInfo[i].iDeviceChanNum != -1)
		{
			strTemp.Format("%s", g_struDeviceInfo[i].chLocalNodeName);
			hDevice = m_treeDeviceList.InsertItem(strTemp, g_struDeviceInfo[i].dwImageType, g_struDeviceInfo[i].dwImageType, hRoot);
			m_treeDeviceList.SetItemData(hDevice, DEVICETYPE*1000 + g_struDeviceInfo[i].iDeviceIndex);
			for (j=0; j< MAX_CHANNUM_V40; j++)
			{
				if (g_struDeviceInfo[i].pStruChanInfo[j].bEnable)
				{
					strChanTmp.Format("%s", g_struDeviceInfo[i].pStruChanInfo[j].chChanName);
					hChan = m_treeDeviceList.InsertItem(strChanTmp, g_struDeviceInfo[i].pStruChanInfo[j].dwImageType, g_struDeviceInfo[i].pStruChanInfo[j].dwImageType, hDevice);
					m_treeDeviceList.SetItemData(hChan,CHANNELTYPE * 1000 + g_struDeviceInfo[i].pStruChanInfo[j].iChanIndex);
				}
				else
				{
					g_struDeviceInfo[i].pStruChanInfo[j].iChanIndex = -1;
				}
			}
			if (g_struDeviceInfo[i].lLoginID >= 0)
			{
				m_treeDeviceList.Expand(hDevice,TVE_EXPAND);
			}
			else
			{
				m_treeDeviceList.Expand(hDevice,TVE_COLLAPSE);
			}
			
		}
	}
	m_treeDeviceList.Expand(hRoot,TVE_EXPAND);
	m_treeDeviceList.Expand(m_treeDeviceList.GetRootItem(),TVE_EXPAND);
}

/*********************************************************
Function:	OnBnClickedBtnPreview
Desc:		preview button response, switch to preview interface
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnPreview()
{
	if (m_iMainType != PREVIEW_T)
	{
		//modify preview flag
		m_iMainType = PREVIEW_T;
		
		
		//hide configuration and button control
		ConfigAllHide();
		m_dlgPlayBack->HideAll();
		if (g_struLocalParam.bUseCard)
		{
			if (!g_bCardInit)
			{
				if (InitDecodeCard())
				{
					g_bCardInit = TRUE;
				}
				else
				{
					g_bCardInit = FALSE;
				}
			}
		}
		else
		{
			if (g_bCardInit)
			{
				g_bCardInit = FALSE;
				NET_DVR_ReleaseDevice_Card();
				NET_DVR_ReleaseDDraw_Card();
			}
		}
		PreviewReferShow(TRUE);
	}
}

/*********************************************************
Function:	LoopSvc
Desc:		preview loop service
Input:	none
Output:	none
Return:	none
**********************************************************/
void *LoopSvc(void *pParam)
{
	int i = 0;
	while (1)
	{
		for (i=0; i<g_struLocalParam.iCycleTime; i++)
		{
			Sleep(1000);
			if (!g_struLocalParam.bCycling)
			{
				goto exitsvc;
			}
		}
		g_pMainDlg->CyclePlayAllDevicesLogined();
	}
exitsvc:
	g_pMainDlg->StopPlayAll();
	
	g_pMainDlg->ChangePlayBtnState();
	return NULL;
}


/*********************************************************
Function:	StartPlayAll
Desc:		play all, only log-in device
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::StartPlayAll(void)
{
	//stop all play window
	StopPlayAll();
	
	//get and save all surveillance points that can be previewed
	int i = 0;
	int j = 0;
	int iFirstPlayNum = 0;//first surveillance point
	int iDeviceIndex = -1;
	int iChanIndex = -1;
	int iSurveillanceNumLeft = 0;
	g_nSurveillanceTotalNum = 0;

	//get current surveillance to play
	for (i = 0; i < MAX_DEVICES; i++)
	{
        if (g_struDeviceInfo[i].byURL &&  g_struDeviceInfo[i].lLoginID != -1)
        {
            //配置使用URL预览时，在设备没有通道时，使能第一个通道作为预览通道
            g_struDeviceInfo[i].pStruChanInfo[0].bEnable = TRUE;
            if (g_struDeviceInfo[i].pStruChanInfo[0].iChannelNO == -1)
            {
                g_struDeviceInfo[i].pStruChanInfo[0].iChannelNO = 1;
            }
        }

        if ((-1 != g_struDeviceInfo[i].iDeviceChanNum || g_struDeviceInfo[i].byURL) &&  g_struDeviceInfo[i].lLoginID != -1)
		{
			for (j = 0; j < MAX_CHANNUM_V30; j++)
			{	
				if (g_struDeviceInfo[i].pStruChanInfo[j].bEnable)
				{
					g_struPlayAllInfo[g_nSurveillanceTotalNum].iDeviceIndex = i;//serial starts from 0
					g_struPlayAllInfo[g_nSurveillanceTotalNum].iChanIndex = j;
					g_nSurveillanceTotalNum ++;
				}
			}
		}
	}
	
    if (g_nSurveillanceTotalNum == 0)
	{
		return;//no monitoring points that can be played
	}

	AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "StartPlayAll:Total Chan Number= %d", g_nSurveillanceTotalNum);
	
	if (g_nSurveillanceTotalNum > m_iCurWndNum)
	{//first group of mornitoring points
		iFirstPlayNum = m_iCurWndNum;
		iSurveillanceNumLeft = g_nSurveillanceTotalNum - m_iCurWndNum;
		g_iNextSurveillanceIndex = m_iCurWndNum;
		g_struLocalParam.bNextPage = TRUE;
		g_struLocalParam.bFrontPage =FALSE ;
	}
	else//only one group
	{
		iFirstPlayNum = g_nSurveillanceTotalNum;
		iSurveillanceNumLeft = 0;
		g_iNextSurveillanceIndex = g_nSurveillanceTotalNum;
		g_struLocalParam.bFrontPage = FALSE;
		g_struLocalParam.bNextPage = FALSE;
	}
	//preview first group
	for (i = 0; i < iFirstPlayNum; i++)
	{
		iDeviceIndex = g_struPlayAllInfo[i].iDeviceIndex;
		iChanIndex = g_struPlayAllInfo[i].iChanIndex;

        //没有通道设置了URL方式预览
        if (g_struDeviceInfo[iDeviceIndex].byURL && g_nSurveillanceTotalNum == 1)
        {
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[0].iDeviceIndex = iDeviceIndex;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[0].iChanIndex = 0;
        }

		g_dlgOutput[i].StartPlay(&g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex], GetChanItem(iDeviceIndex, iChanIndex));
		Sleep(10);
	}
	
	//cycle play
	if (g_struLocalParam.bCyclePlay)
	{	
		if (!g_struLocalParam.bCycling)
		{
			g_struLocalParam.bCycling = TRUE;
			g_struLocalParam.bPaused = FALSE;
			_beginthread((void (__cdecl *)(void *))LoopSvc, 0, NULL);
		}
		// 		if (g_pCycleTimer == NULL)
		// 		{
		// 			g_pCycleTimer = SetTimer(CYCLE_PREVIEW_TIMER, g_struLocalParam.iCycleTime*1000, NULL);
		// 		}
		// 		g_struLocalParam.bCycling = TRUE;
		// 		g_struLocalParam.bPaused = FALSE;
	}
	
	if (iSurveillanceNumLeft != 0)
	{
		g_struLocalParam.bNextPage = TRUE;
	}
	else
	{
		g_struLocalParam.bNextPage = FALSE;
	}
	g_struLocalParam.bFrontPage = FALSE;
	g_bPlayAllDevice = TRUE;
	ChangePlayBtnState();
}

/*********************************************************
Function:	OnBnClickedBtnPlay
Desc:		play all or stop all
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnPlay()
{
	if (IsPlaying())//stop all playing windows
	{
		if (!g_struLocalParam.bCycling)
		{
			StopPlayAll();
			ChangePlayBtnState();
		}
		g_struLocalParam.bPaused = TRUE;
		g_bPlayAllDevice = FALSE;
		g_struLocalParam.bCycling = FALSE;
		// 		if (g_pCycleTimer != NULL)
		
		// 			KillTimer(CYCLE_PREVIEW_TIMER);
		// 			g_pCycleTimer = NULL;
		// 		}
		return;
	}
	
	StartPlayAll();	
}

/*********************************************************
Function:	OnBnClickedBtnMakeIframe
Desc:		mandatory I frame
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnMakeIframe()
{
	int i = m_iCurWndIndex;
	if (g_dlgOutput[i].m_lPlayHandle < 0)
	{
		return;
	}
	int iDeviceIndex = g_dlgOutput[i].m_struChanInfo.iDeviceIndex;
	int iChanIndex = g_dlgOutput[i].m_struChanInfo.iChanIndex;
	if (iDeviceIndex == -1 || iChanIndex == -1)
	{
		return;
	}
	
    if (iChanIndex < ZERO_CHAN_INDEX) // 500 以上为零通道
    {
		if (((g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwProtocol>>31)&0x1) == 0)
		{
			//if (!NET_DVR_MakeKeyFrame(g_struDeviceInfo[iDeviceIndex].lLoginID,  g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO))
			memset(&m_struIFrame, 0, sizeof(m_struIFrame));
			m_struIFrame.dwSize = sizeof(NET_DVR_I_FRAME);
			if (g_struDeviceInfo[iDeviceIndex].byMirrorChanNum > 0 && iChanIndex >= MIRROR_CHAN_INDEX)
			{
                m_struIFrame.dwChan = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].iChannelNO;
			}
			else
			{
				m_struIFrame.dwChan = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
			}
			m_struIFrame.byStreamType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwStreamType;
			if(!NET_DVR_RemoteControl(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_MAKE_I_FRAME, &m_struIFrame, sizeof(m_struIFrame)))
			{
				AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MAKE_I_FRAME");
				char szLan[128] = {0};
				g_StringLanType(szLan, "强制I帧失败！", "Make I Frame Failed");
				AfxMessageBox(szLan);
			}
			else
			{
				AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MAKE_I_FRAME");
			}
		}
	    else
		{
			//if (!NET_DVR_MakeKeyFrameSub(g_struDeviceInfo[iDeviceIndex].lLoginID,  g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO))
			memset(&m_struIFrame, 0, sizeof(m_struIFrame));
			m_struIFrame.dwSize = sizeof(NET_DVR_I_FRAME);
            if (g_struDeviceInfo[iDeviceIndex].byMirrorChanNum > 0 && iChanIndex >= MIRROR_CHAN_INDEX)
			{
                m_struIFrame.dwChan = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].iChannelNO;
			}
			else
			{
				m_struIFrame.dwChan = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
			}
			m_struIFrame.byStreamType = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].dwStreamType;
			if(!NET_DVR_RemoteControl(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_MAKE_I_FRAME, &m_struIFrame, sizeof(m_struIFrame)))
			{
				AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MAKE_I_FRAME");
				char szLan[128] = {0};
				g_StringLanType(szLan, "强制I帧失败！", "Make I Frame Failed");
				AfxMessageBox(szLan);
			}
			else
			{
				AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MAKE_I_FRAME");
			}
		}
	}
    else
    {
        int iZeroChannel = iChanIndex - ZERO_CHAN_INDEX + g_struDeviceInfo[iDeviceIndex].iStartChan;
        if (!NET_DVR_ZeroMakeKeyFrame(g_struDeviceInfo[iDeviceIndex].lLoginID, iChanIndex - ZERO_CHAN_INDEX + g_struDeviceInfo[iDeviceIndex].iStartChan))
        {
            AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ZeroMakeKeyFrame Chan[%d]", iZeroChannel);
        }
        else
        {
            AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_ZeroMakeKeyFrame Chan[%d]", iZeroChannel);
        }
    }

}

/*********************************************************
Function:	PreviewReferShow
Desc:		display or hide control and dialog related to preview
Input:	bShow,TRUE,display,FALSE,hide;
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::PreviewReferShow(BOOL bShow)
{
	int iShowStat = bShow?SW_SHOW:SW_HIDE;
	
	if (bShow)
	{
		if (g_struLocalParam.bUseCard)
		{
			NET_DVR_ClearSurface_Card();
		}
		if (g_struLocalParam.bEnlarged)
		{
			ArrangeOutputs(1);
		}
		else
		{
			ArrangeOutputs(m_iCurWndNum);
		}	
	}
	else
	{
		if (g_struLocalParam.bUseCard)
		{
			NET_DVR_ClearSurface_Card();
		}
		for (int i=0; i<MAX_OUTPUTS; i++)
		{
			g_dlgOutput[i].ShowWindow(SW_HIDE);
		}
	}
	GetDlgItem(IDC_STATIC_PREVIEWBG)->ShowWindow(iShowStat);
	//GetDlgItem(IDC_STATIC_PREVIEWBG)->Invalidate(!bShow);
	GetDlgItem(IDC_BTN_PLAY)->ShowWindow(iShowStat);
	GetDlgItem(IDC_BTN_RECORD)->ShowWindow(iShowStat);
	GetDlgItem(IDC_BTN_PICTURE_SNATCH)->ShowWindow(iShowStat);
	GetDlgItem(IDC_BTN_MAKE_IFRAME)->ShowWindow(iShowStat);
	
	GetDlgItem(IDC_STATIC_PREVIEW1)->ShowWindow(iShowStat);
	GetDlgItem(IDC_STATIC_PREVIEW2)->ShowWindow(iShowStat);
	GetDlgItem(IDC_STATIC_PREVIEW3)->ShowWindow(iShowStat);
	GetDlgItem(IDC_STATIC_NETDELAY)->ShowWindow(iShowStat);
	GetDlgItem(IDC_STATIC_WIN_NUM)->ShowWindow(iShowStat);
	GetDlgItem(IDC_COMBONETDELAY)->ShowWindow(iShowStat);
	GetDlgItem(IDC_COMBO_WNDNUM)->ShowWindow(iShowStat);
	
	m_dlgOutputCtrl->ShowWindow(iShowStat);
}

/*********************************************************
Function:	InitPreviewRect
Desc:		initialize preview area
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::InitPreviewRect()
{
	m_rectPreviewBG.top    = m_iFunBtnHeight;
	m_rectPreviewBG.left   = m_iTreeWidth;
	m_rectPreviewBG.right  = DEMO_FULL_WIDTH - m_iRightWidth;
	m_rectPreviewBG.bottom = m_rectPreviewBG.Width()*3/4 + m_iFunBtnHeight+4;//+4
	
	m_rectRightArea.top    = m_iFunBtnHeight - 3;
	m_rectRightArea.left   = DEMO_FULL_WIDTH - m_iRightWidth + 5;//
	m_rectRightArea.right  = DEMO_FULL_WIDTH;//
	m_rectRightArea.bottom = m_rectPreviewBG.Width()*3/4 + m_iFunBtnHeight + 55; //+55button height
	
	GetDlgItem(IDC_STATIC_PREVIEWBG)->MoveWindow(&m_rectPreviewBG,TRUE);
	
	m_dlgOutputCtrl->MoveWindow(&m_rectRightArea,TRUE);
	m_dlgOutputCtrl->ShowWindow(SW_SHOW);
	
	if (!g_struLocalParam.bUseCard)
	{
		m_iCurWndNum = 4;//default window number is 4
		m_comboWinNum.SetCurSel(1);
		
	}
	m_comboNetDelayBufNum.SetCurSel(1);
	//output box layout
	ArrangeOutputs(m_iCurWndNum);//
}

/*********************************************************
Function:	LoadTreeImage
Desc:		load tree iamge
Input:	
Output:	
Return:	
**********************************************************/
#define MAX_BMPS 14
void CClientDemoDlg::LoadTreeImage(void)
{
	CBitmap cBmp[MAX_BMPS];
	
	m_imageTreeList.Create(16,16,ILC_COLOR32 | ILC_MASK,1,1);
	
	cBmp[TREE_ALL].LoadBitmap(IDB_BITMAP_TREE);
	m_imageTreeList.Add(&cBmp[TREE_ALL],RGB(1,1,1));
	
	cBmp[DEVICE_LOGOUT].LoadBitmap(IDB_BITMAP_LOGOUT);
	m_imageTreeList.Add(&cBmp[DEVICE_LOGOUT],RGB(1,1,1));
	cBmp[DEVICE_LOGIN].LoadBitmap(IDB_BITMAP_LOGIN);
	m_imageTreeList.Add(&cBmp[DEVICE_LOGIN],RGB(1,1,1));
	cBmp[DEVICE_FORTIFY].LoadBitmap(IDB_BITMAP_FORTIFY);
	m_imageTreeList.Add(&cBmp[DEVICE_FORTIFY],RGB(1,1,1));
	cBmp[DEVICE_ALARM].LoadBitmap(IDB_BITMAP_DEV_ALARM);
	m_imageTreeList.Add(&cBmp[DEVICE_ALARM],RGB(1,1,1));
	
	cBmp[DEVICE_FORTIFY_ALARM].LoadBitmap(IDB_BITMAP_FORTIFY_ALARM);
	m_imageTreeList.Add(&cBmp[DEVICE_FORTIFY_ALARM],RGB(1,1,1));
	
	cBmp[CHAN_ORIGINAL].LoadBitmap(IDB_BITMAP_CAMERA);
	m_imageTreeList.Add(&cBmp[CHAN_ORIGINAL],RGB(1,1,1));
	cBmp[CHAN_PLAY].LoadBitmap(IDB_BITMAP_PLAY);
	m_imageTreeList.Add(&cBmp[CHAN_PLAY],RGB(1,1,1));
	cBmp[CHAN_RECORD].LoadBitmap(IDB_BITMAP_REC);
	m_imageTreeList.Add(&cBmp[CHAN_RECORD],RGB(1,1,1));
	cBmp[CHAN_PLAY_RECORD].LoadBitmap(IDB_BITMAP_PLAYANDREC);
	m_imageTreeList.Add(&cBmp[CHAN_PLAY_RECORD],RGB(1,1,1));
	
	cBmp[CHAN_ALARM].LoadBitmap(IDB_BITMAP_ALARM);
	m_imageTreeList.Add(&cBmp[CHAN_ALARM],RGB(1,1,1));
	cBmp[CHAN_PLAY_ALARM].LoadBitmap(IDB_BITMAP_PLAY_ALARM);
	m_imageTreeList.Add(&cBmp[CHAN_PLAY_ALARM],RGB(1,1,1));
	
	cBmp[CHAN_PLAY_RECORD_ALARM].LoadBitmap(IDB_BITMAP_P_R_A);
	m_imageTreeList.Add(&cBmp[CHAN_PLAY_RECORD_ALARM],RGB(1,1,1));
	
	cBmp[CHAN_OFF_LINE].LoadBitmap(IDB_BITMAP_CHAN_OFF);
	m_imageTreeList.Add(&cBmp[CHAN_OFF_LINE],RGB(1,1,1));
	
	m_treeDeviceList.SetImageList(&m_imageTreeList, LVSIL_NORMAL);
}

/*********************************************************
Function:	IsPlaying
Desc:		whether any window is previewing
Input:	
Output:	
Return:	
**********************************************************/
BOOL CClientDemoDlg::IsPlaying(void)
{
	if (m_iMainType == PREVIEW_T)
	{
		for (int i = 0; i < MAX_OUTPUTS; i ++)
		{
			if (g_dlgOutput[i].m_lPlayHandle >= 0)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}


/*********************************************************
Function:	ArrangeOutputs
Desc:		output layout
Input:	iNumber, current output number
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::ArrangeOutputs(int iNumber)
{
	if (iNumber == 0)
	{
		AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "ArrangeOutputs number=0!");
		return;
	}
	int i = 0;
	CRect crect;
	
	int iSqrtNum = 0;//sqrt value of window number
	int iWidth = 0;//window width
	int iHeight = 0;//window height
	
	iSqrtNum = (int)sqrt((double)iNumber);
	
	for (i = 0;i < MAX_OUTPUTS;i++)
	{
		g_dlgOutput[i].ShowWindow(SW_HIDE);	
	}
	
	if (g_struLocalParam.bMultiScreen)
	{//muti-window full screen
		iWidth = (g_iCurScreenWidth - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;
		iHeight = (g_iCurScreenHeight - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;
		
		for (i = 0; i < iNumber; i++)
		{
			g_dlgOutput[i].MoveWindow((i%iSqrtNum)*(iWidth+OUTPUT_INTERVAL),(i/iSqrtNum)*(iHeight+OUTPUT_INTERVAL),iWidth,iHeight,TRUE);
			g_dlgOutput[i].m_struCardPlayParam.nLeft = (i%iSqrtNum)*(iWidth+OUTPUT_INTERVAL);
			g_dlgOutput[i].m_struCardPlayParam.nTop = (i/iSqrtNum)*(iHeight+OUTPUT_INTERVAL);
			g_dlgOutput[i].m_struCardPlayParam.nWidth = iWidth;
			g_dlgOutput[i].m_struCardPlayParam.nHeight = iHeight;
			g_dlgOutput[i].ShowWindow(SW_SHOW);
		}
	}
	else
	{
		iWidth = (m_rectPreviewBG.Width()-OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;//a single pic width in partition
		iHeight = (m_rectPreviewBG.Height()-OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;//a single pic height in partition
		int iPlayIndex = 0;
		for (i = 0; i < iNumber; i++)
		{
			if (g_struLocalParam.bEnlarged)
			{//double click to zoom some pic, iNumber = 1
				iPlayIndex = m_iCurWndIndex;
			}
			else
			{
				iPlayIndex = i;
			}
			g_dlgOutput[iPlayIndex].MoveWindow(m_iTreeWidth + (i%iSqrtNum)*(iWidth+OUTPUT_INTERVAL),\
				m_iFunBtnHeight+(i/iSqrtNum)*(iHeight+OUTPUT_INTERVAL),iWidth,iHeight,TRUE);
			g_dlgOutput[iPlayIndex].m_struCardPlayParam.nLeft = (i%iSqrtNum)*(iWidth+OUTPUT_INTERVAL);//m_iTreeWidth+
			g_dlgOutput[iPlayIndex].m_struCardPlayParam.nTop = (i/iSqrtNum)*(iHeight+OUTPUT_INTERVAL);//m_iFunBtnHeight+
			g_dlgOutput[iPlayIndex].m_struCardPlayParam.nWidth = iWidth;
			g_dlgOutput[iPlayIndex].m_struCardPlayParam.nHeight = iHeight;
			g_dlgOutput[iPlayIndex].ShowWindow(SW_SHOW);
			g_dlgOutput[iPlayIndex].DrawOutputBorder();
		}
	}
	//hardware decode window set
	NET_DVR_DISPLAY_PARA struDisPlayParam;
	if (g_struLocalParam.bUseCard)
	{
		//clear and hide previous pic
		NET_DVR_ClearSurface_Card();
		for (i = 0; i < MAX_OUTPUTS; i++)
		{
			struDisPlayParam.bToScreen = 0;
			struDisPlayParam.bToVideoOut = 1;
			struDisPlayParam.nLeft = g_dlgOutput[i].m_struCardPlayParam.nLeft;
			struDisPlayParam.nTop = g_dlgOutput[i].m_struCardPlayParam.nTop;
			struDisPlayParam.nWidth = g_dlgOutput[i].m_struCardPlayParam.nWidth;
			struDisPlayParam.nHeight = g_dlgOutput[i].m_struCardPlayParam.nHeight;
			NET_DVR_ResetPara_Card(g_dlgOutput[i].m_lPlayHandle,&struDisPlayParam);
		}
		
		if (g_struLocalParam.bMultiScreen)
		{
			for (i = 0; i < m_iCurWndNum; i++)
			{
				struDisPlayParam.bToScreen = 1;
				struDisPlayParam.bToVideoOut = 1;
				struDisPlayParam.nLeft = g_dlgOutput[i].m_struCardPlayParam.nLeft;
				struDisPlayParam.nTop = g_dlgOutput[i].m_struCardPlayParam.nTop;
				struDisPlayParam.nWidth = g_dlgOutput[i].m_struCardPlayParam.nWidth;
				struDisPlayParam.nHeight = g_dlgOutput[i].m_struCardPlayParam.nHeight;
				NET_DVR_ResetPara_Card(g_dlgOutput[i].m_lPlayHandle,&struDisPlayParam);
			}
		}
		else
		{
			if (iNumber == 1)
			{//single channel hardware decode or single window zoom
				struDisPlayParam.bToScreen = 1;
				struDisPlayParam.bToVideoOut = 1;
				struDisPlayParam.nLeft = g_dlgOutput[m_iCurWndIndex].m_struCardPlayParam.nLeft;
				struDisPlayParam.nTop = g_dlgOutput[m_iCurWndIndex].m_struCardPlayParam.nTop;
				struDisPlayParam.nWidth = g_dlgOutput[m_iCurWndIndex].m_struCardPlayParam.nWidth;
				struDisPlayParam.nHeight = g_dlgOutput[m_iCurWndIndex].m_struCardPlayParam.nHeight;
				NET_DVR_ResetPara_Card(g_dlgOutput[m_iCurWndIndex].m_lPlayHandle,&struDisPlayParam);
			}
			else
			{//narrow
				for (i = 0; i < iNumber; i++)
				{
					struDisPlayParam.bToScreen = 1;
					struDisPlayParam.bToVideoOut = 1;
					struDisPlayParam.nLeft = g_dlgOutput[i].m_struCardPlayParam.nLeft;
					struDisPlayParam.nTop = g_dlgOutput[i].m_struCardPlayParam.nTop;
					struDisPlayParam.nWidth = g_dlgOutput[i].m_struCardPlayParam.nWidth;
					struDisPlayParam.nHeight = g_dlgOutput[i].m_struCardPlayParam.nHeight;
					NET_DVR_ResetPara_Card(g_dlgOutput[i].m_lPlayHandle,&struDisPlayParam);
				}
			}
		}
	}
}


/*********************************************************
Function:	FullScreen
Desc:		display/hide main control while single or multiple pic preview in full screen
Input:	bFullScreen: TRUE, full screen, hide some control, FALSE, recover display control and previous pic
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::FullScreen(BOOL bFullScreen)
{
	int iShowStat = bFullScreen?SW_HIDE:SW_SHOW;
	
	m_treeDeviceList.ShowWindow(iShowStat);
	
	GetDlgItem(IDC_BTN_LOG_SAVE)->ShowWindow(iShowStat);
	GetDlgItem(IDC_RADIO_LOCAL_LOG)->ShowWindow(iShowStat);
	GetDlgItem(IDC_RADIO_ALARM_INFO)->ShowWindow(iShowStat);
	// 	GetDlgItem(IDC_COMBO_LIST_TYPE)->ShowWindow(iShowStat);
	// 	GetDlgItem(IDC_STATIC_LIST_TYPE)->ShowWindow(iShowStat);
	
	GetDlgItem(IDC_BTN_LOG_CLEAR)->ShowWindow(iShowStat);
	GetDlgItem(IDC_BTN_LOG_CONFIG)->ShowWindow(iShowStat);
	
	GetDlgItem(IDC_STATIC_MAIN)->ShowWindow(iShowStat);
	GetDlgItem(IDC_BTN_CONFIG)->ShowWindow(iShowStat);
	GetDlgItem(IDC_BTN_PREVIEW)->ShowWindow(iShowStat);
	GetDlgItem(IDC_BTN_PLAY_BACK)->ShowWindow(iShowStat);
	GetDlgItem(IDC_BTN_MANAGE)->ShowWindow(iShowStat);
	GetDlgItem(IDC_BTN_ELSE)->ShowWindow(iShowStat);
	GetDlgItem(IDC_BTN_EXIT)->ShowWindow(iShowStat);
	
	GetDlgItem(IDC_STATIC_VERSION)->ShowWindow(iShowStat);
	//GetDlgItem(IDC_STATIC_SYS)->ShowWindow(iShowStat);
	GetDlgItem(IDC_STATIC_DEMO_VERSION)->ShowWindow(iShowStat);
	GetDlgItem(IDC_STATIC_SDK_VERSION)->ShowWindow(iShowStat);
	GetDlgItem(IDC_STATIC_PLAYM4_VERSION)->ShowWindow(iShowStat);
	
	if (bFullScreen)
	{
		//for full screen while backplay
		GetWindowPlacement(&m_struOldWndpl);
		
		CRect rectWholeDlg;//entire client(including title bar)
		CRect rectClient;//client area(not including title bar)
		CRect rectFullScreen;
		GetWindowRect(&rectWholeDlg);
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rectClient);
		ClientToScreen(&rectClient);
		
		rectFullScreen.left = rectWholeDlg.left-rectClient.left;
		rectFullScreen.top = rectWholeDlg.top-rectClient.top;
		rectFullScreen.right = rectWholeDlg.right+g_iCurScreenWidth - rectClient.right;
		rectFullScreen.bottom = rectWholeDlg.bottom+g_iCurScreenHeight - rectClient.bottom;
		//enter into full screen;
		WINDOWPLACEMENT struWndpl;
		struWndpl.length = sizeof(WINDOWPLACEMENT);
		struWndpl.flags = 0;
		struWndpl.showCmd = SW_SHOWNORMAL;
		struWndpl.rcNormalPosition = rectFullScreen;
		SetWindowPlacement(&struWndpl);
	}
	else
	{
		SetWindowPlacement(&m_struOldWndpl);
	}
	
	if (m_iMainType == PREVIEW_T)//dealing while preview
	{
		//refresh backgroud box
		if (bFullScreen)
		{	
			GetDlgItem(IDC_STATIC_PREVIEWBG)->MoveWindow(0,0,g_iCurScreenWidth,g_iCurScreenHeight,true);	
		}
		else
		{
			GetDlgItem(IDC_STATIC_PREVIEWBG)->MoveWindow(&m_rectPreviewBG,true);	
		}
		PreviewReferShow(!bFullScreen);
		GetDlgItem(IDC_STATIC_PREVIEWBG)->ShowWindow(SW_SHOW);
		
		if (g_struLocalParam.bFullScreen)
		{
			if (g_struLocalParam.bUseCard)
			{
				NET_DVR_DISPLAY_PARA struDisPlayParam;
				struDisPlayParam.bToVideoOut = 1;
				struDisPlayParam.bToScreen = 1;
				struDisPlayParam.nLeft = 0;
				struDisPlayParam.nTop = 0;
				struDisPlayParam.nWidth = g_iCurScreenWidth;
				struDisPlayParam.nHeight = g_iCurScreenHeight;
				NET_DVR_ResetPara_Card(g_dlgOutput[m_iCurWndIndex].m_lPlayHandle,&struDisPlayParam);
				g_dlgOutput[m_iCurWndIndex].MoveWindow(0,0,g_iCurScreenWidth, g_iCurScreenHeight, TRUE);
				g_dlgOutput[m_iCurWndIndex].ShowWindow(SW_SHOW);
			}
			else
			{
				g_dlgOutput[m_iCurWndIndex].MoveWindow(0,0,g_iCurScreenWidth, g_iCurScreenHeight, TRUE);
				g_dlgOutput[m_iCurWndIndex].ShowWindow(SW_SHOW);
			}
		}
	}
	if (bFullScreen)
	{
		m_listAlarmInfo.ShowWindow(SW_HIDE);
		m_listAllLog.ShowWindow(SW_HIDE);
	}
	else
	{
		OnSelchangeComboListType();
	}
}


/*********************************************************
Function:	OnNMClickTreeDeviceList
Desc:		click tree node response function, type of node; device node, log in operation, clear device and its related alarm
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnNMClickTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//get node handle through mouse position
	CPoint pt(0,0);
	GetCursorPos(&pt);
	
	CRect rect(0,0,0,0);
	ScreenToClient(&pt);
	GetDlgItem(IDC_TREE_DEVICE_LIST)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	
	pt.x = pt.x-rect.left;
	pt.y = pt.y-rect.top;
	
	UINT uFlags = 0;
	HTREEITEM hSelect = m_treeDeviceList.HitTest(pt,&uFlags);
	if (hSelect == NULL)
	{
		AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "please click the right node!");
		return;
	}
	BOOL bLogined = FALSE;
	DWORD dwNoteData = m_treeDeviceList.GetItemData(hSelect);
	int iType = dwNoteData/1000;
	int iIndex = dwNoteData%1000;
	if (DEVICETYPE == iType)
	{
		m_iCurDeviceIndex = iIndex;
		m_hCurDeviceItem = hSelect;
		m_iCurChanIndex = -1;
		m_hCurChanItem = NULL;
		bLogined = DoLogin(m_iCurDeviceIndex, hSelect);
	}
	else if (CHANNELTYPE == iType)
	{
		m_iCurChanIndex = iIndex;
		m_hCurChanItem = hSelect;
		HTREEITEM hParent = m_treeDeviceList.GetParentItem(hSelect);
		if (hParent != NULL)
		{
			dwNoteData = m_treeDeviceList.GetItemData(hParent);
			iType = dwNoteData/1000;
			iIndex = dwNoteData%1000;
			if (DEVICETYPE == iType)
			{
				m_iCurDeviceIndex = iIndex;
				m_hCurDeviceItem = hParent;
				bLogined = DoLogin(m_iCurDeviceIndex, hParent);
			}
		}
		
	}
	else
	{
		m_iCurDeviceIndex = -1;
		m_hCurDeviceItem = NULL;
		m_iCurChanIndex = -1;
		m_hCurChanItem = NULL;
	}
	
	if (m_iMainType == CONFIG_ALL_T)
	{
		m_dlgConfigAll->ConfigWndUpdate();
	}
	else if (m_iMainType == PLAY_BACK_T)
	{
		m_dlgPlayBack->PlayBackWinUpdate();
	}
	else if (m_iMainType == PRODUCT_RELATE_T)
	{
		m_dlgProductCfg->UpdateWindowParam(GetCurDeviceIndex(),GetCurChanIndex());
	}
	
	//clear alarm status on manual
	if (bLogined)
	{
		ManualClearAlarm(m_iCurDeviceIndex, m_iCurChanIndex);
	}
	
	*pResult = 0;
}


/*********************************************************
Function:	OnNMDblclkTreeDeviceList
Desc:		double click tree node response function, play one channel or whole device
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnNMDblclkTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hSelect = m_treeDeviceList.GetSelectedItem();
	if (NULL == hSelect || m_iMainType != PREVIEW_T)//it works to double click device tree only while preview
	{
		return;
	}
	
	if (g_bPlayAllDevice)//disable to single designated play while all play
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "请先停止全部播放", "Please stop all play first");
		AfxMessageBox(szLan);
		return;
	}
	
	DWORD dwNodeData = (DWORD)m_treeDeviceList.GetItemData(hSelect);
	HTREEITEM hParent = NULL;
	int iType = dwNodeData/1000;
	int iIndex = dwNodeData%1000;
	int iDeviceIndex  = GetCurDeviceIndex();
	switch (iType)
	{
	case TREE_ALL_T:
		DblAllTree();
		break;
	case DEVICETYPE:
		m_iCurDeviceIndex = iIndex;
		m_hCurDeviceItem = hSelect;
		m_iCurChanIndex = -1;
		m_hCurChanItem = NULL;
		if (GetCurDeviceIndex() != -1)
		{
			DblPlayDevice(m_iCurDeviceIndex, m_iCurWndIndex);
		}		
		m_treeDeviceList.Expand(hSelect, TVE_COLLAPSE);//expend reverse operation
		//	m_treeDeviceList.Expand(hSelect,TVE_EXPAND);
		break;
	case CHANNELTYPE:  //double click channel
		m_iCurChanIndex = iIndex;
		m_hCurChanItem = hSelect;
		hParent = m_treeDeviceList.GetParentItem(hSelect);
		if (hParent != NULL)
		{
			if (DEVICETYPE == m_treeDeviceList.GetItemData(hParent)/1000)
			{
				m_iCurDeviceIndex = m_treeDeviceList.GetItemData(hParent)%1000;
				m_hCurDeviceItem = hParent;
			}
		}
        if (m_iCurDeviceIndex >= 0)
        {
            if (iIndex < MIRROR_CHAN_INDEX)
            {
                DblPlayChan(m_iCurDeviceIndex,iIndex,hSelect);
            }
            else if (iIndex < ZERO_CHAN_INDEX)
            {
                PlayMirrorChan(m_iCurDeviceIndex,iIndex,hSelect);
            }
            else
            {
                PlayZeroChan(m_iCurDeviceIndex,iIndex,hSelect);
            }
            
        }	
		break;
	default:
		{
			m_iCurChanIndex = -1;
			m_hCurChanItem = NULL;
			m_iCurDeviceIndex = -1;
			m_hCurDeviceItem = NULL;
		}
		break;
	}
	*pResult = 0;
}

/*********************************************************
Function:	OnNMRclickTreeDeviceList
Desc:		right-click tree node, pop up related menu
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnNMRclickTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMenu pMenu;
	HTREEITEM hParent=NULL;
	CPoint pt(0,0);
	GetCursorPos(&pt);
	HTREEITEM hRoot = m_treeDeviceList.GetRootItem();
	if (hRoot == NULL)
	{
		if (!pMenu.LoadMenu(IDR_MENU_TREE_ALL))
		{
			return;
		}
	}
	else
	{
		CRect rect(0,0,0,0);
		ScreenToClient(&pt);
		GetDlgItem(IDC_TREE_DEVICE_LIST)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		pt.x = pt.x-rect.left;
		pt.y = pt.y-rect.top;
		//while select first node or blank
		//HTREEITEM hSelect = m_treeDeviceList.GetSelectedItem();
		UINT uFlags = 0;
		HTREEITEM hSelect = m_treeDeviceList.HitTest(pt,&uFlags);
		if (hSelect == NULL )//|| m_iMainType != PREVIEW_T
		{
			return;
		}
		
		m_treeDeviceList.SelectItem(hSelect);
		
		int iType = int(m_treeDeviceList.GetItemData(hSelect) / 1000);
		
		switch (iType)
		{
		case TREE_ALL_T:
			// 			if (!pMenu.LoadMenu(IDR_MENU_TREE_ALL))
			// 			{
			// 				return;
			// 			}
			OnMenuDeviceAdd();
			return;
			break;
		case DEVICETYPE:
			m_iCurDeviceIndex = int(m_treeDeviceList.GetItemData(hSelect) % 1000);
			m_hCurDeviceItem = hSelect;
			m_iCurChanIndex = -1;
			m_hCurChanItem = NULL;
			if (!pMenu.LoadMenu(IDR_MENU_DEVICE))
			{
				return;
			}
			break;
		case CHANNELTYPE:
			m_iCurChanIndex = int(m_treeDeviceList.GetItemData(hSelect) % 1000);
			m_hCurChanItem = hSelect;
			
			hParent = m_treeDeviceList.GetParentItem(hSelect);
			if (hParent != NULL)
			{
				if (DEVICETYPE == m_treeDeviceList.GetItemData(hParent)/1000)
				{
					m_iCurDeviceIndex = m_treeDeviceList.GetItemData(hParent)%1000;
					m_hCurDeviceItem = hParent;
				}
			}
			if (!pMenu.LoadMenu(IDR_MENU_CHANNEL))
			{
				return;
			}
			
			break;
		default:
			break;
		}
	}
	//display menu
	GetCursorPos(&pt);
	pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pt.x ,pt.y,this);	
	*pResult = 0;
}

/*********************************************************
Function:	GetAfterItem
Desc:		get device insert point, make sure new device insert afterword last node
Input:	hRoot:handle of item tree root
Output:	
Return:	
**********************************************************/
HTREEITEM CClientDemoDlg::GetAfterItem(HTREEITEM hRoot)
{
	HTREEITEM hReturn = TVI_FIRST;
	HTREEITEM hChild = m_treeDeviceList.GetChildItem(hRoot);
	
	while (hChild)
	{
		if (TREE_ALL_T ==  m_treeDeviceList.GetItemData(hChild) / 1000)   //break if it si device tree node
		{
			break;
		}
		
		hReturn = hChild;
		hChild = m_treeDeviceList.GetNextSiblingItem(hChild);
	}
	
	return hReturn;
}

/*********************************************************
Function:	OnMenuDeviceAdd
Desc:		menu,device adding response 
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuDeviceAdd()
{
	int i = 0;
    int j = 0;
	for (i = 0; i < MAX_DEVICES; i++)
	{
		if (-1 == g_struDeviceInfo[i].iDeviceChanNum)
		{
			break;
		}
	}
	char szLan[128] = {0};
	if (i == MAX_DEVICES)
	{
		g_StringLanType(szLan, "所添加的设备已达到最大数", "Added device has reached the maximum number");
		AfxMessageBox(szLan);
		return;
	}
	
	HTREEITEM hSelect = m_treeDeviceList.GetSelectedItem();
	
	for (i = 0; i < MAX_DEVICES; i++)
	{
		if (g_struDeviceInfo[i].iDeviceChanNum == -1)
		{
			CDlgAddDevice dlg;
            dlg.m_iDeviceIndex = i;
            //memset(&g_struDeviceInfo[i], 0, sizeof(STRU_DEVICE_INFO));
            if (dlg.DoModal() == IDOK)
            {
                HTREEITEM hDevice = m_treeDeviceList.InsertItem(g_struDeviceInfo[i].chLocalNodeName, DEVICE_LOGIN, DEVICE_LOGIN,hSelect,GetAfterItem(hSelect));
                m_treeDeviceList.SetItemData(hDevice, DEVICETYPE * 1000 + g_struDeviceInfo[i].iDeviceIndex);//
                HTREEITEM hChannel = NULL;

				//analog channel & IP channel
                for (j= 0; j < MAX_CHANNUM_V40; j++)
                {
					if (g_struDeviceInfo[i].pStruChanInfo[j].iChanIndex != -1 )
					{
						 if (g_struDeviceInfo[i].pStruChanInfo[j].bEnable)
                         {
                             hChannel = m_treeDeviceList.InsertItem(g_struDeviceInfo[i].pStruChanInfo[j].chChanName,CHAN_ORIGINAL,CHAN_ORIGINAL,hDevice);
						 }
						 else
						 {
							 hChannel = m_treeDeviceList.InsertItem(g_struDeviceInfo[i].pStruChanInfo[j].chChanName,CHAN_OFF_LINE,CHAN_OFF_LINE,hDevice);                            
                         }

						 m_treeDeviceList.SetItemData(hChannel, CHANNELTYPE * 1000 + g_struDeviceInfo[i].pStruChanInfo[j].iChanIndex);
					}  
                }

				//zero
                for (j= 0; j < g_struDeviceInfo[i].byZeroChanNum; j++)
                {
                    hChannel = m_treeDeviceList.InsertItem(g_struDeviceInfo[i].struZeroChan[j].chChanName,CHAN_ORIGINAL,CHAN_ORIGINAL,hDevice);
                    m_treeDeviceList.SetItemData(hChannel, CHANNELTYPE * 1000 + g_struDeviceInfo[i].struZeroChan[j].iChanIndex);
                }
				for (j= 0; j < g_struDeviceInfo[i].byMirrorChanNum&&j < 16; j++)
                {
                    hChannel = m_treeDeviceList.InsertItem(g_struDeviceInfo[i].struMirrorChan[j].chChanName,CHAN_ORIGINAL,CHAN_ORIGINAL,hDevice);
                    m_treeDeviceList.SetItemData(hChannel, CHANNELTYPE * 1000 + g_struDeviceInfo[i].struMirrorChan[j].iChanIndex);
                }
                m_iCurDeviceIndex = dlg.m_iDeviceIndex;
                m_treeDeviceList.Expand(hSelect,TVE_EXPAND);
                m_treeDeviceList.Expand(hDevice,TVE_EXPAND);
                ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_DEVICE_ITEM_IMAGE, WPARAM(hDevice), LPARAM(i));
            }
            return;
        }
    }
    g_StringLanType(szLan, "超过最大设备数", "Exceeds the maximum number of Devices");
    AfxMessageBox(szLan);
}

/*********************************************************
Function:	DblPlayChan
Desc:		double click playing channel, stop if it is already playing
Input:		hChanItem,pic switch wile play status changes;iChanIndex:channel index;hChanItem,channel node pointer;
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::DblPlayChan(int iDeviceIndex, int iChanIndex,HTREEITEM hChanItem)
{
	if (!DoLogin(iDeviceIndex, m_treeDeviceList.GetParentItem(hChanItem)))
	{
		return;
	}
	char szLan[128] = {0};
	if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].lRealHandle < 0)
	{
		CHANNEL_INFO pStruChanInfo;
		if (iChanIndex >= MIRROR_CHAN_INDEX)
		{
			memcpy(&pStruChanInfo, &g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex- MIRROR_CHAN_INDEX], sizeof(CHANNEL_INFO));
		}
		else
		{
			memcpy(&pStruChanInfo, &g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex], sizeof(CHANNEL_INFO));
		}
		
		if (g_dlgOutput[m_iCurWndIndex].StartPlay(&pStruChanInfo,hChanItem)<0)
		{
			g_StringLanType(szLan, "预览失败！", "Preview Failed");
			AfxMessageBox(szLan);
		}
		
		ChangePlayBtnState();
		return;
	}
	
	//if the channel is already previewed, stop it
	if (!StopPlayedChan(iDeviceIndex,iChanIndex))
	{
		g_StringLanType(szLan, "停止预览失败！", "Stop previewing Failed");
		AfxMessageBox(szLan);
	}
	ChangePlayBtnState();
}

void CClientDemoDlg::PlayMirrorChan(int iDeviceIndex, int iChanIndex,HTREEITEM hChanItem)
{
    if (!DoLogin(iDeviceIndex, m_treeDeviceList.GetParentItem(hChanItem)))
    {
        return;
    }
    char szLan[128] = {0};
    if (g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].lRealHandle < 0)
    {
        CHANNEL_INFO struMirrorChan;
        memcpy(&struMirrorChan, &g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX], sizeof(CHANNEL_INFO));
        
        if (g_dlgOutput[m_iCurWndIndex].MirrorStartPlay(&struMirrorChan,hChanItem) <0)
        {
            g_StringLanType(szLan, "预览失败！", "Preview Failed");
            //AddLog(iDeviceIndex, OPERATION_FAIL_T, "Zero play chan", iChanIndex-ZERO_CHAN_INDEX);
            AfxMessageBox(szLan);
        }

        ChangePlayBtnState();
        return;
    }
    
    //if the channel is already previewed, stop it
    if (!StopPlayedChan(iDeviceIndex,iChanIndex))
    {
        g_StringLanType(szLan, "停止预览失败！", "Stop previewing Failed");
        AfxMessageBox(szLan);
    }
	ChangePlayBtnState();
}

/*********************************************************
Function:	PlayZeroChan
Desc:		double click playing channel, stop if it is already playing
Input:		hChanItem,pic switch wile play status changes;iChanIndex:channel index;hChanItem,channel node pointer;
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::PlayZeroChan(int iDeviceIndex, int iChanIndex,HTREEITEM hChanItem)
{
    if (!DoLogin(iDeviceIndex, m_treeDeviceList.GetParentItem(hChanItem)))
    {
        return;
    }
    char szLan[128] = {0};
    
    if (g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex-ZERO_CHAN_INDEX].lRealHandle < 0)
    {
        CHANNEL_INFO struZeroChan;
        memcpy(&struZeroChan, &g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex-ZERO_CHAN_INDEX], sizeof(CHANNEL_INFO));
        
        if (g_dlgOutput[m_iCurWndIndex].ZeroStartPlay(&struZeroChan,hChanItem)<0)
        {
            g_StringLanType(szLan, "预览失败！", "Preview Failed");
            //AddLog(iDeviceIndex, OPERATION_FAIL_T, "Zero play chan", iChanIndex-ZERO_CHAN_INDEX);
            AfxMessageBox(szLan);
        }
        
        ChangePlayBtnState();
        return;
    }
    
    //if the channel is already previewed, stop it
    if (!StopPlayedChan(iDeviceIndex,iChanIndex))
    {
        g_StringLanType(szLan, "停止预览失败！", "Stop previewing Failed");
        AfxMessageBox(szLan);
    }
    ChangePlayBtnState();
}

/*********************************************************
Function:	OnMenuLogout
Desc:		menu on logout response function
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuLogout()
{
	int iDeviceIndex = GetCurDeviceIndex();
	
	if (iDeviceIndex == -1)
	{
		return;
	}
	HTREEITEM hDeviceItem = m_treeDeviceList.GetSelectedItem();
	if (hDeviceItem == NULL)
	{
		AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "CClientDemoDlg::OnMenuLogout: hDeviceItem err\n");
		return;
	}
	DoLogout(iDeviceIndex, hDeviceItem);
	ManualClearAlarm(iDeviceIndex, -1);
}

/*********************************************************
Function:	DoLogout
Desc:		logout
Input:		iDeviceIndex:device serial number;hDeviceItem,device pointer;
Output:		
Return:		TRUE,log out successfullyFALSE,log out failed
**********************************************************/
BOOL CClientDemoDlg::DoLogout(int iDeviceIndex, HTREEITEM hDeviceItem)
{
	int i = 0;
	char szLan[128] = {0};
	g_StringLanType(szLan, "该设备有通道正在预览或录像", "Some channels of this device is recording or preview");
	for (i = 0; i<g_struDeviceInfo[iDeviceIndex].iDeviceChanNum; i++)
	{
		if ((g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].lRealHandle >= 0 && i < MAX_CHANNUM_V30*2)|| g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bLocalManualRec )
		{
			AfxMessageBox(szLan);
			return FALSE;
		}
	}
	// 2011-11-16 silujie
	g_StringLanType(szLan, "该设备有通道正在被动解码", "some channels of this device is passive decode");
	for(i =0; i<256; i++)
	{
		if (g_struDeviceInfo[iDeviceIndex].struPassiveDecode[i].lPassiveHandle >=0 || g_struDeviceInfo[iDeviceIndex].struPassiveDecode[i].hFileThread != NULL)
		{
			AfxMessageBox(szLan);
			return FALSE;
		}
	}
	g_StringLanType(szLan, "该设备有通道正在语音对讲", "Some channels of this device is voice talk");
	if (g_lVoiceHandle >= 0)
	{
		AfxMessageBox(szLan);
		return FALSE;
	}
	if (g_struDeviceInfo[iDeviceIndex].lLoginID >= 0)
	{
		//remove guard
		if (g_struDeviceInfo[iDeviceIndex].lFortifyHandle >= 0)
		{
			if (NET_DVR_CloseAlarmChan_V30(g_struDeviceInfo[iDeviceIndex].lFortifyHandle))
			{
				g_struDeviceInfo[iDeviceIndex].lFortifyHandle = -1;	
			}
		}
		
		if (!NET_DVR_Logout_V30(g_struDeviceInfo[iDeviceIndex].lLoginID))
		{
			//g_struDeviceInfo[iDeviceIndex].lLoginID = -1;
			g_StringLanType(szLan, "注销失败", "Logout Failed");
			AfxMessageBox(szLan);
			::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_DEVICE_ITEM_IMAGE, WPARAM(hDeviceItem), LPARAM(iDeviceIndex));
			return FALSE;
		}
	}
	AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_Logout_V30");
	g_struDeviceInfo[iDeviceIndex].lLoginID	    = -1;
	g_struDeviceInfo[iDeviceIndex].bPlayDevice  = FALSE;	
	
	for (i = 0; i < g_struDeviceInfo[iDeviceIndex].iDeviceChanNum; i++)
	{
		g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].lRealHandle = -1;
		g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = FALSE;
		g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bLocalManualRec = FALSE;
	}
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_DEVICE_ITEM_IMAGE, WPARAM(hDeviceItem), LPARAM(iDeviceIndex));
	return TRUE;
}


/*********************************************************
Function:	OnMenuDeviceDelete
Desc:		delete devices, and initialize structure
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuDeviceDelete()
{
	char szLan[128] = {0};
	g_StringLanType(szLan, "确定要删除该结点", "Sure to delete this node");
	
	if (MessageBox(szLan,"Warning",MB_OKCANCEL) == IDOK)
	{
		int iDeviceIndex = GetCurDeviceIndex();
		HTREEITEM hDeviceItem = m_treeDeviceList.GetSelectedItem();
		if (DoLogout(iDeviceIndex, hDeviceItem))//先注销这个设备
		{
			LOCAL_DEVICE_INFO struDevInfo;
			//memcpy(&(g_struDeviceInfo[iDeviceIndex]), &struDevInfo, sizeof(LOCAL_DEVICE_INFO));
			 sprintf(g_struDeviceInfo[iDeviceIndex].chLoginUserName , "%s", _T(""));
			 sprintf(g_struDeviceInfo[iDeviceIndex].chLoginPwd  , "%s", _T(""));
			 sprintf(g_struDeviceInfo[iDeviceIndex].chLocalNodeName      , "%s", _T(""));
			 sprintf(g_struDeviceInfo[iDeviceIndex].chDeviceIP, "%s", _T(""));
			// sprintf(g_struDeviceInfo[iDeviceIndex].chDevNetCard1IP, "%s", _T(""));
		     sprintf(g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP   , "%s", _T(""));
		     sprintf(g_struDeviceInfo[iDeviceIndex].chSerialNumber    , "%s", _T(""));
		    // sprintf(g_struDeviceInfo[iDeviceIndex].chIPServerIP, "%s", _T(""));
	      	 g_struDeviceInfo[iDeviceIndex].lLoginID	    = -1;
	     	 g_struDeviceInfo[iDeviceIndex].iDeviceChanNum   = -1;
		     g_struDeviceInfo[iDeviceIndex].lDevicePort      = 8000;
	         g_struDeviceInfo[iDeviceIndex].iDeviceType      = 0;
		     g_struDeviceInfo[iDeviceIndex].iDeviceLoginType  = 0;
             g_struDeviceInfo[iDeviceIndex].byHttps = 0;
             g_struDeviceInfo[iDeviceIndex].byLoginMode = 0;
             g_struDeviceInfo[iDeviceIndex].byLoginModeRes = 0;
		
	     	for (int j = 0; j < g_struDeviceInfo[iDeviceIndex].iDeviceChanNum; j++)
			{
		    	sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[j].chChanName ,"%s", _T(""));
		        g_struDeviceInfo[iDeviceIndex].pStruChanInfo[j].iChanIndex    = -1;
			    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[j].dwProtocol    = 0;
			    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[j].iDeviceIndex  = -1;
			}
			
			m_treeDeviceList.DeleteItem(hDeviceItem);
			g_SaveDeviceConfig();
		}
		
	}
}

/*********************************************************
Function:	OnMenuDeviceInfo
Desc:		menu on device info response function
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuDeviceInfo()
{
	int iDeviceIndex  = GetCurDeviceIndex();
	if (iDeviceIndex == -1 )
	{
		return;
	}
	
	CDlgDeviceInfo dlgDeviceInfo;
	dlgDeviceInfo.m_iDeviceIndex = iDeviceIndex;
	
	if (IDOK == dlgDeviceInfo.DoModal())
	{
		HTREEITEM hSelect = m_treeDeviceList.GetSelectedItem();
		m_treeDeviceList.SetItemText(hSelect,g_struDeviceInfo[iDeviceIndex].chLocalNodeName);
	}	
}


/*********************************************************
Function:	OnMenuJPEGSnatchConfig
Desc:		local 'jpeg' capture pic configuration
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuJPEGSnatchConfig()
{
	
	int iDeviceIndex  = GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return;
	}
	
	int iChanIndex = GetCurChanIndex();
	if (iChanIndex == -1)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "通道号错误！", "Channel Error");
		AfxMessageBox(szLan);
		return;
	}
    if (iChanIndex >= ZERO_CHAN_INDEX)
    {
        AfxMessageBox("Zero not support  NET_DVR_CaptureJPEGPicture");
    }
	CDlgJPEGSnatchConfig dlg;
    if (g_struDeviceInfo[iDeviceIndex].byMirrorChanNum > 0 && iChanIndex >= MIRROR_CHAN_INDEX)
	{
        dlg.m_pChanInfo = &g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX];
	}
	else
	{
		dlg.m_pChanInfo = &g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex];
	}
	
	dlg.DoModal();
	
}

/*********************************************************
Function:	OnMenuChannelInfo
Desc:		menu on channel info response function
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuChannelInfo()
{
	int iDeviceIndex  = GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return;
	}
	int iChanIndex = GetCurChanIndex();
	if (iChanIndex == -1)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "通道号错误！", "Channel Error");
		AfxMessageBox(szLan);
		return;
	}
	CDlgChannelInfo dlgChannelInfo;
    if (iChanIndex >= ZERO_CHAN_INDEX)
    {
        dlgChannelInfo.m_pChanInfo = &g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex - ZERO_CHAN_INDEX];
    }
	else if (iChanIndex >= g_struDeviceInfo[iDeviceIndex].iDeviceChanNum)
	{
        dlgChannelInfo.m_pChanInfo = &g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX];
	}
    else if (iChanIndex >= 0 && iChanIndex < g_struDeviceInfo[iDeviceIndex].iDeviceChanNum)
    {
		dlgChannelInfo.m_pChanInfo = &g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex];
    }
	
	if (IDOK == dlgChannelInfo.DoModal() && dlgChannelInfo.m_bChanged)
	{
		HTREEITEM hSelect = m_treeDeviceList.GetSelectedItem();
        if (iChanIndex >= ZERO_CHAN_INDEX)
        {
            m_treeDeviceList.SetItemText(hSelect,g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex-ZERO_CHAN_INDEX].chChanName);
        }
		else if (iChanIndex >= MIRROR_CHAN_INDEX)
		{
			m_treeDeviceList.SetItemText(hSelect,g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex-MIRROR_CHAN_INDEX].chChanName);
		}
        else
        {
			m_treeDeviceList.SetItemText(hSelect,g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
		}	
        g_SaveDeviceConfig();
    }	
}

/*********************************************************
Function:	ChangeChannelItemImage
Desc:		change status icon related to channel node, including play, record, alarm status
Input:	wParam, tree channel pointer;lParam,Pointer to channel structure;
Output:	
Return:	0 succeed
**********************************************************/
LRESULT CClientDemoDlg::ChangeChannelItemImage(WPARAM wParam, LPARAM lParam)
{
	int iDeviceIndex = int(wParam);
	int iChanIndex = int(lParam);
	if (iDeviceIndex < 0 || iDeviceIndex >MAX_DEVICES\
        || iChanIndex > 512 || iChanIndex < 0)
	{
		OutputDebugString("dev index and chan num err!\n");
		return NULL;
	}
	
	HTREEITEM hChanItem = GetChanItem(iDeviceIndex, iChanIndex);
	if (NULL == hChanItem)
	{
		OutputDebugString("chan item NULL!\n");
		return NULL;
	}
	int iImage = CHAN_ORIGINAL;
	CHANNEL_INFO pStruChanInfo;
	BOOL bPlaying = FALSE;
    if (iChanIndex >= ZERO_CHAN_INDEX)
    {
        memcpy(&pStruChanInfo, &g_struDeviceInfo[iDeviceIndex].struZeroChan[iChanIndex - ZERO_CHAN_INDEX], sizeof(pStruChanInfo));
    }
    else if (iChanIndex >= MIRROR_CHAN_INDEX)
    {
        memcpy(&pStruChanInfo, &g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX], sizeof(pStruChanInfo));
    }
    else
    {
        memcpy(&pStruChanInfo, &g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex], sizeof(pStruChanInfo));
    }
    
	
	bPlaying = pStruChanInfo.lRealHandle >= 0? TRUE:FALSE;
	if (bPlaying && !pStruChanInfo.bLocalManualRec && !pStruChanInfo.bAlarm)
	{
		iImage = CHAN_PLAY;	
	}
	else if ( bPlaying && pStruChanInfo.bLocalManualRec && !pStruChanInfo.bAlarm)
	{
		iImage = CHAN_PLAY_RECORD;	
	}
	else if (!bPlaying && pStruChanInfo.bLocalManualRec && !pStruChanInfo.bAlarm)
	{
		iImage = CHAN_RECORD;	
	}
	else if (!bPlaying && !pStruChanInfo.bLocalManualRec && pStruChanInfo.bAlarm)
	{
		iImage = CHAN_ALARM;	
	}
	else if (bPlaying && !pStruChanInfo.bLocalManualRec && pStruChanInfo.bAlarm)
	{
		iImage = CHAN_PLAY_ALARM;
	}
	else if (bPlaying && pStruChanInfo.bLocalManualRec && pStruChanInfo.bAlarm)
	{
		iImage = CHAN_PLAY_RECORD_ALARM;	
	}
	else if (!bPlaying && !pStruChanInfo.bLocalManualRec && !pStruChanInfo.bAlarm)
	{
		iImage = CHAN_ORIGINAL;	
	}
	
	m_treeDeviceList.SetItemImage(hChanItem,iImage,iImage);	
	//modify status!!
    if (iChanIndex >= ZERO_CHAN_INDEX)
    {
		g_struDeviceInfo[pStruChanInfo.iDeviceIndex].struZeroChan[iChanIndex - ZERO_CHAN_INDEX].dwImageType = iImage;
    }
	else if (iChanIndex >= MIRROR_CHAN_INDEX)
	{
		g_struDeviceInfo[pStruChanInfo.iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].dwImageType = iImage;
	}
    else
    {
		g_struDeviceInfo[pStruChanInfo.iDeviceIndex].pStruChanInfo[pStruChanInfo.iChanIndex].dwImageType = iImage;
    }
    
	return 0;
}

/*********************************************************
Function:	ChangeDeviceItemImage
Desc:		设备节点状态改变的消息函数,维护设备"登陆","布防","告警"等状态
Input:	wParam,树设备节点的指针;lParam,设备的序列号;
Output:	
Return:	0 成功
**********************************************************/
LRESULT CClientDemoDlg::ChangeDeviceItemImage(WPARAM wParam, LPARAM lParam)
{
	HTREEITEM hDeviceItem     = HTREEITEM(wParam);
	int iDeviceIndex = int(lParam);
	
	if (NULL == hDeviceItem || iDeviceIndex < 0)
	{
		AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "change dev item");
		return NULL;
	}
	int iImage = DEVICE_LOGOUT;
	if (g_struDeviceInfo[iDeviceIndex].lLoginID >= 0 \
		&& g_struDeviceInfo[iDeviceIndex].lFortifyHandle < 0&& !g_struDeviceInfo[iDeviceIndex].bAlarm)
	{
		iImage = DEVICE_LOGIN;	
	}
	else if (g_struDeviceInfo[iDeviceIndex].lLoginID >= 0 \
		&& g_struDeviceInfo[iDeviceIndex].lFortifyHandle >= 0&& !g_struDeviceInfo[iDeviceIndex].bAlarm)
	{
		iImage = DEVICE_FORTIFY;
	}
	else if (g_struDeviceInfo[iDeviceIndex].lLoginID >= 0 \
		&& g_struDeviceInfo[iDeviceIndex].lFortifyHandle >= 0 && g_struDeviceInfo[iDeviceIndex].bAlarm)
	{
		iImage = DEVICE_FORTIFY_ALARM;
	}
	else if (g_struDeviceInfo[iDeviceIndex].lLoginID >= 0 \
        &&g_struDeviceInfo[iDeviceIndex].lFortifyHandle < 0 && g_struDeviceInfo[iDeviceIndex].bAlarm)
	{
		iImage = DEVICE_ALARM;
	}
	else
	{
		iImage = DEVICE_LOGOUT;
	}
	
	m_treeDeviceList.SetItemImage(hDeviceItem,iImage,iImage);	
	g_struDeviceInfo[iDeviceIndex].dwImageType = iImage;
	return 0;
}
typedef struct tagLOCAL_LOGIN_PARAM
{
    int iDeviceIndex;
	HTREEITEM hSelect;
	BOOL bMsgBox;
}LOCAL_LOGIN_PARAM, *LPLOCAL_LOGIN_PARAM;
void ClassifyDevClass(char *pDevClass, unsigned long ulDevClassLen, unsigned short wDevClass)
{
    if (pDevClass == NULL)
    {
        return;
    }
    if (ulDevClassLen < 100)
    {
        return;
    }
    if ((wDevClass >= 1) && (wDevClass <= 50))
    {
        sprintf(pDevClass, "DVR\n");
    }
    else if ((wDevClass >= 51) && (wDevClass <= 100))
    {
        sprintf(pDevClass, "DVS\n");
    }
    else if ((wDevClass >= 101) && (wDevClass <= 150))
    {
        sprintf(pDevClass, "NVR\n");
    }
    else if ((wDevClass >= 151) && (wDevClass <= 200))
    {
        sprintf(pDevClass, "IPC\n");
    }
    //
    else if ((wDevClass >= 201) && (wDevClass <= 250))
    {
        sprintf(pDevClass, "CVR\n");
    }
    else if ((wDevClass >= 251) && (wDevClass <= 300))
    {
        sprintf(pDevClass, "Transfer & Display\n");
    }
    else if ((wDevClass >= 301) && (wDevClass <= 350))
    {
        sprintf(pDevClass, "Alarm Host\n");
    }
    else if ((wDevClass >= 351) && (wDevClass <= 400))
    {
        sprintf(pDevClass, "Access Control\n");
    }
    else if ((wDevClass >= 401) && (wDevClass <= 450))
    {
        sprintf(pDevClass, "Video Intercom\n");
    }
    else if ((wDevClass >= 451) && (wDevClass <= 500))
    {
        sprintf(pDevClass, "Ummanned Aerial Vehicle\n");
    }
    else if ((wDevClass >= 501) && (wDevClass <= 550))
    {
        sprintf(pDevClass, "Mobile\n");
    }
    else if ((wDevClass >= 551) && (wDevClass <= 600))
    {
        sprintf(pDevClass, "MObile Vehicle\n");
    }
	//智能分析仪
	else if ((wDevClass >= 601) && (wDevClass <= 650))
	{
		sprintf(pDevClass, "Intelligent analyzer\n");
	}
	//智能交通服务器
	else if ((wDevClass >= 651) && (wDevClass <= 700))
	{
		sprintf(pDevClass, "Intelligent traffic server \n");
	}
    //NVS
    else if ((wDevClass >= 701) && (wDevClass <= 750))
    {
        sprintf(pDevClass, "NVS\n");
    }
    //SMART LOCK
    else if ((wDevClass >= 851) && (wDevClass <= 900))
    {
        sprintf(pDevClass, "Smart Lock\n");
    }
    else
    {
        sprintf(pDevClass, "the others\n");
    }
    return;
}

void CALLBACK LoginResultCallBack(LONG lUserID, DWORD dwResult, LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo, void* pUser)
{
    char strTmp[125] = { 0 };
    sprintf(strTmp, "%d\n", dwResult);
    OutputDebugString(strTmp);

    if (dwResult == ASYN_LOGIN_SUCC && pUser != NULL)
    {
        memcpy(pUser, lpDeviceInfo, sizeof(NET_DVR_DEVICEINFO_V30));
        m_giAsynLoginReturn = 1;
    }
    else
    {
        m_giAsynLoginReturn = 2;
    }
    if (m_gpDlgAsynloginWait != NULL)
    {
        m_gpDlgAsynloginWait->PostMessageA(WM_CLOSE, NULL, NULL);
    }

    m_giErrNo = NET_DVR_GetLastError();
    m_gpErrMsg = NET_DVR_GetErrorMsg();
}

/*********************************************************
Function:	DoLogin
Desc:		check the device has logged in, if not, log in 
Input:	iDeviceIndex,device serial number ;hDeviceItem pointer to device node
Output:	
Return:	FALSE,device log in failed;TRUE; logged in;
**********************************************************/
void *CClientDemoDlg::DoLoginEx(void *lpParam)
{
	if (lpParam == NULL)
	{
		return FALSE;
	}
	int iDeviceIndex = ((LPLOCAL_LOGIN_PARAM)lpParam)->iDeviceIndex;
	HTREEITEM hDeviceItem = ((LPLOCAL_LOGIN_PARAM)lpParam)->hSelect;
	BOOL bMsgBox = ((LPLOCAL_LOGIN_PARAM)lpParam)->bMsgBox;
	
	delete lpParam;
	lpParam = NULL;
	
	NET_DVR_NETCFG_V30* pStruNetCfg = new  NET_DVR_NETCFG_V30;
	NET_DVR_DEVICECFG_V40* pStruDevCfg = new NET_DVR_DEVICECFG_V40;
	
	if (pStruNetCfg == NULL || pStruDevCfg == NULL)
	{
		return NULL;
	}

    memset(pStruNetCfg, 0, sizeof(NET_DVR_NETCFG_V30));
    memset(pStruDevCfg, 0, sizeof(NET_DVR_DEVICECFG_V40));
	
	DWORD dwReturned = 0;
	CString csTemp;
	int i = 0;
	if (g_struDeviceInfo[iDeviceIndex].lLoginID < 0)
	{
		LONG lUserID = -1;
		NET_DVR_DEVICEINFO_V30 struDeviceInfo;
		//		char szDeviceSN[SERIALNO_LEN] = {0};
		memset(&struDeviceInfo, 0, sizeof(NET_DVR_DEVICEINFO_V30));
		
        m_giAsynLoginReturn = 0;
        m_giErrNo = 0;
        m_gpErrMsg = NULL;
        NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
        NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
        if (m_gbAsynLogin)
        {
            struLoginInfo.bUseAsynLogin = true;
            struLoginInfo.cbLoginResult = LoginResultCallBack;
            struLoginInfo.pUser = &struDeviceInfoV40;
        }
        else
        {
            struLoginInfo.bUseAsynLogin = false;
        }
        struLoginInfo.wPort = g_struDeviceInfo[iDeviceIndex].lDevicePort;
        memcpy(struLoginInfo.sDeviceAddress, g_struDeviceInfo[iDeviceIndex].chDeviceIP, NET_DVR_DEV_ADDRESS_MAX_LEN);
        memcpy(struLoginInfo.sUserName, g_struDeviceInfo[iDeviceIndex].chLoginUserName, NAME_LEN);
        memcpy(struLoginInfo.sPassword, g_struDeviceInfo[iDeviceIndex].chLoginPwd, NAME_LEN);
        struLoginInfo.byProxyType = g_struDeviceInfo[iDeviceIndex].byProxyType;
        //struLoginInfo.byUseTransport = 1;
        //struLoginInfo.byRes3[119] = 2;

        //DEBUG
        //struLoginInfo.byHttps = 2;
        //struLoginInfo.byLoginMode = 2;

        struLoginInfo.byHttps = g_struDeviceInfo[iDeviceIndex].byHttps;
        struLoginInfo.byLoginMode = g_struDeviceInfo[iDeviceIndex].byLoginMode; //自适应方式
//        struLoginInfo.byVerifyMode = 2;

        lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
        
        if (m_gbAsynLogin)
        {
            m_gpDlgAsynloginWait = new CDlgAsynloginWait();
            m_gpDlgAsynloginWait->DoModal();
            delete m_gpDlgAsynloginWait;
            m_gpDlgAsynloginWait = NULL;
        }
        if ((m_gbAsynLogin && m_giAsynLoginReturn == 2) || lUserID < 0)
		{
			char szLan[1024] = {0};
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_Login_V30");
			if (bMsgBox)
			{
				if (NET_DVR_GetLastError() == NET_DVR_PASSWORD_ERROR)
				{
					g_StringLanType(szLan, "用户名密码错误!", "user name or password error!");
					AfxMessageBox(szLan);
                    if (1 == struDeviceInfoV40.bySupportLock)
                    {
                        sprintf(szLan, "还剩%d尝试机会", struDeviceInfoV40.byRetryLoginTime);
                        AfxMessageBox(szLan);
                    }
                }
                else if (NET_DVR_GetLastError() == NET_DVR_USER_LOCKED)
                {
                    if (1 == struDeviceInfoV40.bySupportLock)
                    {
                        sprintf(szLan, "IP被锁定，剩余锁定时间%d秒", struDeviceInfoV40.dwSurplusLockTime);
                        AfxMessageBox(szLan);
                    }
                }
                else
                {				
                    g_StringLanType(szLan, "由于网络原因或DVR忙, 注册失败!", "net error or dvr is busy!");
                    AfxMessageBox(szLan);
                }
            }
            if (pStruNetCfg != NULL)
            {
                delete pStruNetCfg ;
                pStruNetCfg = NULL;
            }
            
            if (pStruDevCfg != NULL)
            {
                delete pStruDevCfg;
                pStruDevCfg = NULL;
            }
            if (lUserID > 0)
            {
                NET_DVR_Logout_V30(lUserID);
            }
            m_giAsynLoginReturn = 0;
            return NULL;
        }
        else
        {
            g_struDeviceInfo[iDeviceIndex].byLoginModeRes = struDeviceInfoV40.byLoginMode;
            if (struDeviceInfoV40.byLoginMode == 0)
            {
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "登录成功，采用协议为私有协议", "Login SUCC, Use Private");
                //AfxMessageBox(szLan);
                g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, szLan);
            }
            else
            {
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "登录成功，采用协议为ISAPI", "Login SUCC, Use ISAPI");
                //AfxMessageBox(szLan);
                g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, szLan);
            }

            if (1 == struDeviceInfoV40.byPasswordLevel)
            {
                char szLan[128] = {0};
                g_StringLanType(szLan, "默认密码，请修改", "default password, please change the password");
                AfxMessageBox(szLan);
            }
            else if (3 == struDeviceInfoV40.byPasswordLevel)
            {
                char szLan[128] = {0};
                g_StringLanType(szLan, "风险密码，请修改", "risk password, please change the password");
                AfxMessageBox(szLan);
            }
            memcpy(&struDeviceInfo, &struDeviceInfoV40.struDeviceV30, sizeof(struDeviceInfo));
        }
        m_giAsynLoginReturn = 0;

        g_struDeviceInfo[iDeviceIndex].byCharaterEncodeType = struDeviceInfoV40.byCharEncodeType;
		g_struDeviceInfo[iDeviceIndex].byAudioInputChanNum = struDeviceInfo.byVoiceInChanNum;
        g_struDeviceInfo[iDeviceIndex].byStartAudioInputChanNo = struDeviceInfo.byStartVoiceInChanNo;
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_Login_V30");
		LOCAL_DEVICE_INFO temp, temp1;
		//initialize the information of device
		memcpy(&temp1, &(g_struDeviceInfo[iDeviceIndex]), sizeof(LOCAL_DEVICE_INFO));
		//memcpy(&(g_struDeviceInfo[iDeviceIndex]), &temp, sizeof(LOCAL_DEVICE_INFO));
		
		g_struDeviceInfo[iDeviceIndex].lLoginID = lUserID;// located ID from re-log in
		g_struDeviceInfo[iDeviceIndex].iDeviceIndex = iDeviceIndex;
		sprintf(g_struDeviceInfo[iDeviceIndex].chDeviceIP, "%s", temp1.chDeviceIP);
		//if the device ip is in ipv6 version, change the ':' to '.' ,
		//for ':' is not allowed in Windows OS's file name 
		char sIPV6Addr[130] = {0};
		int i = 0; 
		for (;i < sizeof(g_struDeviceInfo[iDeviceIndex].chDeviceIP); i ++)
		{
			if(g_struDeviceInfo[iDeviceIndex].chDeviceIP[i] == '\0')
			{
				break;
			}
			else if(g_struDeviceInfo[iDeviceIndex].chDeviceIP[i] == ':')
			{
				sIPV6Addr[i] = '.';
			}
			else
			{
				sIPV6Addr[i] = g_struDeviceInfo[iDeviceIndex].chDeviceIP[i];
			}
		}
		strncpy(g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, sIPV6Addr, sizeof(sIPV6Addr));

		sprintf(g_struDeviceInfo[iDeviceIndex].chLocalNodeName, "%s", temp1.chLocalNodeName);
		g_struDeviceInfo[iDeviceIndex].lDevicePort = temp1.lDevicePort;
        g_struDeviceInfo[iDeviceIndex].byHttps = temp1.byHttps;
        g_struDeviceInfo[iDeviceIndex].byLoginMode = temp1.byLoginMode;
		
		sprintf(g_struDeviceInfo[iDeviceIndex].chLoginPwd, "%s", temp1.chLoginPwd);
		sprintf(g_struDeviceInfo[iDeviceIndex].chLoginUserName, "%s", temp1.chLoginUserName);
		sprintf(g_struDeviceInfo[iDeviceIndex].chLoginUserName, "%s", temp1.chLoginUserName);
		
		g_struDeviceInfo[iDeviceIndex].dwImageType = DEVICE_LOGIN;
		g_struDeviceInfo[iDeviceIndex].lLoginID = lUserID;
		sprintf(g_struDeviceInfo[iDeviceIndex].chSerialNumber, "%s", struDeviceInfo.sSerialNumber);
		g_struDeviceInfo[iDeviceIndex].iDeviceType = struDeviceInfo.wDevType;  //扩展字段表示类型，原为byDVRType
		g_struDeviceInfo[iDeviceIndex].iDeviceChanNum = struDeviceInfo.byChanNum + struDeviceInfo.byIPChanNum+ struDeviceInfo.byHighDChanNum *256;
		g_struDeviceInfo[iDeviceIndex].iStartChan = struDeviceInfo.byStartChan;
		g_struDeviceInfo[iDeviceIndex].iDiskNum = struDeviceInfo.byDiskNum;
		g_struDeviceInfo[iDeviceIndex].iAlarmOutNum = struDeviceInfo.byAlarmOutPortNum;
		g_struDeviceInfo[iDeviceIndex].iAlarmInNum = struDeviceInfo.byAlarmInPortNum;
		g_struDeviceInfo[iDeviceIndex].iAudioNum = struDeviceInfo.byAudioChanNum;
		g_struDeviceInfo[iDeviceIndex].iAnalogChanNum = struDeviceInfo.byChanNum;
		g_struDeviceInfo[iDeviceIndex].iIPChanNum = struDeviceInfo.byIPChanNum + struDeviceInfo.byHighDChanNum*256;
        g_struDeviceInfo[iDeviceIndex].byZeroChanNum = struDeviceInfo.byZeroChanNum;
		g_struDeviceInfo[iDeviceIndex].byStartDTalkChan = struDeviceInfo.byStartDTalkChan;
        g_struDeviceInfo[iDeviceIndex].byLanguageType = struDeviceInfo.byLanguageType;
		g_struDeviceInfo[iDeviceIndex].byMirrorChanNum = struDeviceInfo.byMirrorChanNum;
		g_struDeviceInfo[iDeviceIndex].wStartMirrorChanNo = struDeviceInfo.wStartMirrorChanNo;

        if (struDeviceInfo.bySupport & 0x80)
		{
			g_struDeviceInfo[iDeviceIndex].byMainProto = struDeviceInfo.byMainProto + 2;
			g_struDeviceInfo[iDeviceIndex].bySubProto = struDeviceInfo.bySubProto + 2;
		}
		else
		{
			g_struDeviceInfo[iDeviceIndex].byMainProto = struDeviceInfo.byMainProto;
			g_struDeviceInfo[iDeviceIndex].bySubProto = struDeviceInfo.bySubProto;
		}  
		
        g_struDeviceInfo[iDeviceIndex].bySupport = struDeviceInfo.bySupport;
		g_struDeviceInfo[iDeviceIndex].bySupport1 = struDeviceInfo.bySupport1;
        g_struDeviceInfo[iDeviceIndex].bySupport2 = struDeviceInfo.bySupport2;
		g_struDeviceInfo[iDeviceIndex].bySupport5 = struDeviceInfo.bySupport5;
		g_struDeviceInfo[iDeviceIndex].bySupport7 = struDeviceInfo.bySupport7;

        for (i = 0; i<MAX_CHANNUM_V40; i++)
		{
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].dwProtocol = temp1.pStruChanInfo[i].dwProtocol;
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iPicResolution = temp1.pStruChanInfo[i].iPicResolution;
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iPicQuality = temp1.pStruChanInfo[i].iPicQuality;
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].dwPreviewMode = temp1.pStruChanInfo[i].dwPreviewMode;
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].nPreviewProtocolType = temp1.pStruChanInfo[i].nPreviewProtocolType;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].nVideoCodingType = temp1.pStruChanInfo[i].nVideoCodingType;
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO = temp1.pStruChanInfo[i].iChannelNO;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].lRealHandle = -1;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex = -1;
		}

        if (g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_B20_MSU_NP || \
            g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_MMC_B20_CLASS || \
            g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_B21_MCU_NP_CLASS || \
            g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_C20N_VWMS || \
            g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_AIOH_MCU_NP || \
            g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_Y10_MCU) //B20/B21/C20N主控
        {
            int nAllChanNums = 0;
            int nPreChanNums = 0;
            NET_DVR_ALLSUBSYSTEMINFO_V40 struSubSystemInfoV40 = { 0 };
            if (NET_DVR_MatrixGetSubSystemInfo_V40(lUserID, &struSubSystemInfoV40))
            {
                for (int nSysCnt = 0; nSysCnt < MAX_SUBSYSTEM_NUM_V40; nSysCnt++)
                {
                    if (struSubSystemInfoV40.struSubSystemInfo[nSysCnt].bySubSystemType == 2 &&
                        struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byBelongBoard != 0xff &&
                        struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceNums != 0)
                    {
                        for (int nChanCnt = 0; nChanCnt < struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceNums; nChanCnt++)
                        {
                            DWORD dwDevNo = 1;
                            DWORD dwBelongBoard = struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byBelongBoard;
                            DWORD dwChanNo = struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceStartNum + nChanCnt;
                            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].iDeviceIndex = iDeviceIndex;
                            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].iChanIndex = nPreChanNums + nChanCnt;
                            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].bEnable = TRUE;
                            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].iChanType = DEMO_CHANNEL_TYPE_ANALOG;
                            sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].chChanName, "Camera_%d_%d_%d", dwDevNo, dwBelongBoard, dwChanNo);
                            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt].iChannelNO = dwDevNo << 24 | dwBelongBoard << 16 | dwChanNo;
                        }
                        nAllChanNums += struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceNums;
                        nPreChanNums = nAllChanNums;
                    }
                }
                g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixGetSubSystemInfo_V40");
            }
            else
            {
                g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixGetSubSystemInfo_V40");
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "获取主板子系统信息失败", "failed to get subsystem information");
                AfxMessageBox(szLan);
                return NULL;
            }
            g_struDeviceInfo[iDeviceIndex].iAnalogChanNum = nAllChanNums;

            if (g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_C20N_VWMS || g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_Y10_MCU) //C20N服务器有预监通道
            {
                int iMinWallNo = 0;
                int iMaxWallNo = 0;

                char *pszBuf = new char[XML_BUF];
                memset(pszBuf, 0, XML_BUF);
                if (!NET_DVR_GetDeviceAbility(lUserID, WALL_ABILITY, NULL, 0, pszBuf, XML_BUF))
                {
                    g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceAbility WALL_ABILITY");
                    char szLan[128] = { 0 };
                    g_StringLanType(szLan, "获取电视墙能力集失败", "failed to get video wall ability");
                    AfxMessageBox(szLan);
                    return NULL;
                }

                char *pStart = strstr(pszBuf, "<wallNo min=\"");
                if (pStart == NULL)
                {
                    char szLan[128] = { 0 };
                    g_StringLanType(szLan, "电视墙能力集中wallNo字段返回有误", "the format of wallNo of video wall ability is error");
                    AfxMessageBox(szLan);
                    return NULL;
                }
                pStart += strlen("<wallNo min=\"");
                char* pEnd = strstr(pStart, "\"");
                if (pEnd == NULL)
                {
                    char szLan[128] = { 0 };
                    g_StringLanType(szLan, "电视墙能力集中wallNo字段返回有误", "the format of wallNo of video wall ability is error");
                    AfxMessageBox(szLan);
                }
                char sMinWallNo[32] = { 0 };
                memcpy(sMinWallNo, pStart, pEnd - pStart);
                iMinWallNo = atoi(sMinWallNo); //从能力集中解析到电视墙编号的最小值

                pStart = strstr(pEnd, "max=\"");
                if (pStart == NULL)
                {
                    char szLan[128] = { 0 };
                    g_StringLanType(szLan, "电视墙能力集中wallNo字段返回有误", "the format of wallNo of video wall ability is error");
                    AfxMessageBox(szLan);
                    return NULL;
                }
                pStart += strlen("max=\"");
                pEnd = strstr(pStart, "\"");
                if (pEnd == NULL)
                {
                    char szLan[128] = { 0 };
                    g_StringLanType(szLan, "电视墙能力集中wallNo字段返回有误", "the format of wallNo of video wall ability is error");
                    AfxMessageBox(szLan);
                    return NULL;
                }
                char sMaxWallNo[32] = { 0 };
                memcpy(sMaxWallNo, pStart, pEnd - pStart);
                iMaxWallNo = atoi(sMaxWallNo); //从能力集中解析到电视墙编号的最大值

                //生成电视墙预监通道
                for (int nChanCnt = iMinWallNo; nChanCnt < iMaxWallNo + 1; nChanCnt++)
                {
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].iDeviceIndex = iDeviceIndex;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].iChanIndex = nPreChanNums + nChanCnt - iMinWallNo;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].bEnable = TRUE;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].iChanType = DEMO_CHANNEL_TYPE_IP;
                    sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].chChanName, "PreMonitor_%02d", nChanCnt);
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[nPreChanNums + nChanCnt - iMinWallNo].iChannelNO = 0xff000000 | nChanCnt;
                }
                nAllChanNums += (iMaxWallNo - iMinWallNo + 1);
                nPreChanNums = nAllChanNums;

                g_struDeviceInfo[iDeviceIndex].iIPChanNum = iMaxWallNo - iMinWallNo + 1;
            }

            g_struDeviceInfo[iDeviceIndex].iDeviceChanNum = nAllChanNums;
        }
		else
		{
			for (i = 0; i <  g_struDeviceInfo[iDeviceIndex].iAnalogChanNum; i++)
			{
				g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iDeviceIndex = iDeviceIndex;
				g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex = i;
				g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO = i + g_struDeviceInfo[iDeviceIndex].iStartChan;
				g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable = TRUE;
				g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanType = DEMO_CHANNEL_TYPE_ANALOG;
				g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].dwImageType = CHAN_ORIGINAL;
				sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName, ANALOG_C_FORMAT, i+g_struDeviceInfo[iDeviceIndex].iStartChan);
			}
		}

		for (i = 0; i <  g_struDeviceInfo[iDeviceIndex].byMirrorChanNum && i < 16; i++)
        {
            g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].iDeviceIndex = iDeviceIndex;
            g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].iChanIndex = i+MIRROR_CHAN_INDEX;
            g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].iChannelNO = i + g_struDeviceInfo[iDeviceIndex].wStartMirrorChanNo;
            g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].bEnable = TRUE;
            g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].iChanType = DEMO_CHANNEL_TYPE_MIRROR;
            g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].dwImageType = CHAN_ORIGINAL;
            sprintf(g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].chChanName, MIRROR_C_FORMAT, i+g_struDeviceInfo[iDeviceIndex].wStartMirrorChanNo);	
        }
        
        if (g_struDeviceInfo[iDeviceIndex].byZeroChanNum > 0)
        {
            for (i=0; i<g_struDeviceInfo[iDeviceIndex].byZeroChanNum; i++)
            {
                g_struDeviceInfo[iDeviceIndex].struZeroChan[i].iDeviceIndex = iDeviceIndex;
                g_struDeviceInfo[iDeviceIndex].struZeroChan[i].iChanIndex = i+ZERO_CHAN_INDEX;
                g_struDeviceInfo[iDeviceIndex].struZeroChan[i].iChannelNO = 0;
                sprintf(g_struDeviceInfo[iDeviceIndex].struZeroChan[i].chChanName, "ZeroChan%d", i);	
                //analog devices
                if (1)
                {
                    g_struDeviceInfo[iDeviceIndex].struZeroChan[i].bEnable = TRUE;
                    g_struDeviceInfo[iDeviceIndex].struZeroChan[i].dwImageType = CHAN_ORIGINAL;
                    //				g_struDeviceInfo[iDeviceIndex].iEnableChanNum ++;
                }
                else
                {
                    g_struDeviceInfo[iDeviceIndex].struZeroChan[i].dwImageType = CHAN_OFF_LINE;
                    g_struDeviceInfo[iDeviceIndex].struZeroChan[i].bEnable = FALSE;		
                }
            }
		}

		
		if (!NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_NETCFG_V30, 0,pStruNetCfg, sizeof(NET_DVR_NETCFG_V30), &dwReturned))
		{
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETCFG_V30");	
		}
		else
		{
			//sprintf(g_struDeviceInfo[m_iDeviceIndex].chDevNetCard1IP, "%s", struNetCfg.struEtherNet[0].struDVRIP.sIpV4);
			
            if (!g_ValidIPv6((BYTE *)(g_struDeviceInfo[iDeviceIndex].chDeviceIP)))
            {
                sprintf(g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP, "%s", pStruNetCfg->struMulticastIpAddr.sIpV4);
                g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "multi-cast ipv4[%s]", pStruNetCfg->struMulticastIpAddr.sIpV4);
			}
            else //ipv6
			{
				sprintf(g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP, "%s", pStruNetCfg->struMulticastIpAddr.byIPv6);
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "multi-cast ipv6[%s]", pStruNetCfg->struMulticastIpAddr.byIPv6);
			}
#if 0
			//IPv6多播测试，临时性地址写死
			memset(g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP, 0, sizeof(g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP));
			sprintf(g_struDeviceInfo[iDeviceIndex].chDeviceMultiIP, "ff02::1234");
#endif
		}

// 		string strContent = "<?xml version=\"1.0\"><StorageServer version=\"1.0\"><PCNVRUI>1<PCNVRUI> </StorageServer>";
// 	    NET_DVR_SetTransparentParam(lUserID, (char*)strContent.c_str(), strContent.size());

        NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_DEVICECFG_V40, 0, pStruDevCfg, sizeof(NET_DVR_DEVICECFG_V40), &dwReturned);
        NET_DVR_DEVICEINFO_V40 struDevInfoV40 = { 0 };
        if (!NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_DEV_LOGIN_RET_INFO, 0, &struDevInfoV40, sizeof(NET_DVR_DEVICEINFO_V40), &dwReturned))
		{
            int nError = NET_DVR_GetLastError();
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEV_LOGIN_RET_INFO");
		}
		else
		{
            //
            pStruDevCfg->byDVRType = struDevInfoV40.struDeviceV30.byDVRType;
            pStruDevCfg->wDevType = struDevInfoV40.struDeviceV30.wDevType;
            pStruDevCfg->byChanNum = struDevInfoV40.struDeviceV30.byChanNum;
            pStruDevCfg->byStartChan = struDevInfoV40.struDeviceV30.byStartChan;
            pStruDevCfg->byIPChanNum = struDevInfoV40.struDeviceV30.byIPChanNum;
            pStruDevCfg->byZeroChanNum = struDevInfoV40.struDeviceV30.byZeroChanNum;
            
			if (g_struDeviceInfo[iDeviceIndex].iDeviceType != (int)pStruDevCfg->wDevType)
			{
				char szLan[256] = {0};
				char szLanShow[256] = {0};
				g_StringLanType(szLan, "登陆返回设备类型值与获取设备参数返回设备类型值不同", "returned device type is different between login and get device config");
                sprintf(szLanShow,"%s %d,%d",szLan,g_struDeviceInfo[iDeviceIndex].iDeviceType,pStruDevCfg->wDevType);
				AfxMessageBox(szLanShow);
			}
			
			sprintf(g_struDeviceInfo[iDeviceIndex].chDeviceName,"%s",pStruDevCfg->byDevTypeName);	
			g_struDeviceInfo[iDeviceIndex].dwDevSoftVer = pStruDevCfg->dwSoftwareVersion;
            ClassifyDevClass(g_struDeviceInfo[iDeviceIndex].chDeviceClassName, 100, pStruDevCfg->wDevClass);
		}

		g_pMainDlg->m_treeDeviceList.Expand(hDeviceItem,TVE_EXPAND);
		//get the new device resource configure when login device/
        if (g_pMainDlg->DoGetDeviceResoureCfg(iDeviceIndex))
        {
            g_pMainDlg->DoGetIPAlarmInCfg(iDeviceIndex);
            g_pMainDlg->DoGetIPAlarmOutCfg(iDeviceIndex);
        }
		g_pMainDlg->RedrawDeviceNode(iDeviceIndex);

		
		::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_DEVICE_ITEM_IMAGE, WPARAM(hDeviceItem), LPARAM(iDeviceIndex));	
	}

	//return if already logged in

	if (pStruNetCfg != NULL)
	{
		delete pStruNetCfg;
		pStruNetCfg = NULL;
	}
	
	if (pStruDevCfg  != NULL)
	{
		delete pStruDevCfg ;
		pStruDevCfg = NULL;
	}
	
	return NULL;
}

/*********************************************************
Function:	DoLogin
Desc:		check the device has logged in, if not, log in 
Input:	iDeviceIndex,device serial number ;hDeviceItem pointer to device node
Output:	
Return:	FALSE,device log in failed;TRUE; logged in;
**********************************************************/
BOOL CClientDemoDlg::DoLogin(int iDeviceIndex, HTREEITEM hDeviceItem)
{
	LPLOCAL_LOGIN_PARAM lpParam = new LOCAL_LOGIN_PARAM;
	if (lpParam == NULL)
    {
        return FALSE;
    }

	lpParam->iDeviceIndex = iDeviceIndex;
	lpParam->hSelect = hDeviceItem;
	lpParam->bMsgBox = TRUE;
	DoLoginEx(lpParam);	
	//return if already logged in
	return TRUE;
}

/*********************************************************
Function:	StopPlayedChan
Desc:		stop one play channel in preview
Input:	iDeviceIndex, device index, iChanIndex,channel index
Output:	
Return:	
**********************************************************/
BOOL CClientDemoDlg::StopPlayedChan(int iDeviceIndex, int iChanIndex)
{
	for (int i = 0; i < MAX_OUTPUTS; i ++)
	{
		if (g_dlgOutput[i].m_lPlayHandle < 0)
		{
			continue;
		}
		
		if (g_dlgOutput[i].m_struChanInfo.iDeviceIndex == iDeviceIndex && \
			g_dlgOutput[i].m_struChanInfo.iChanIndex == iChanIndex )
		{
            if (g_dlgOutput[i].m_struChanInfo.iChanIndex < MIRROR_CHAN_INDEX)
            {
				return g_dlgOutput[i].StopPlay();
			}
            else if (g_dlgOutput[i].m_struChanInfo.iChanIndex < ZERO_CHAN_INDEX)
            {
                return g_dlgOutput[i].MirrorStopPlay();
            }
            else
            {
                return g_dlgOutput[i].ZeroStopPlay();
            }            
        }
	}
	
	return TRUE;
}

/*********************************************************
Function:	CreateNewLogFile
Desc:		create new log file
Input:	bCreate, TRUE/FALSE
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::CreateNewLogFile(BOOL bCreate)
{
	CString csLogFile;
	
	// 	if ((LONG *)m_fLog.m_hFile != INVALID_HANDLE_VALUE)
	// 	{
	// 		TRACE("Close alarm file");	
	// 		m_fLog.Close();
	// 		m_fLog.Abort();
	// 	}
	// 
	// 	if ((LONG *)m_fAlarm.m_hFile != INVALID_HANDLE_VALUE)
	// 	{
	// 		TRACE("Close alarm file");
	// 		
	// 		m_fAlarm.Close();
	// 		m_fAlarm.Abort();
	// 	}
	if (m_fLog != NULL)
	{
		fclose(m_fLog);
	}
	if (m_fAlarm!= NULL)
	{
		fclose(m_fAlarm);
	}
	if (!bCreate)
	{
		return;
	}
	COleDateTime dtCurTime = COleDateTime::GetCurrentTime();
	csLogFile.Format("%s\\LogFile_%4d%02d%02d.txt",\
		g_struLocalParam.chRemoteCfgSavePath, dtCurTime.GetYear(), dtCurTime.GetMonth(),\
		dtCurTime.GetDay());
	if ((m_fLog = fopen(csLogFile.GetBuffer(0), "a+")) == NULL)
	{
		GetDlgItem(IDC_BTN_LOG_SAVE)->EnableWindow(FALSE);
		g_struLocalParam.bAutoSaveLog = FALSE;
	}		
	csLogFile.Format("%s\\AlarmInfo_%4d%02d%02d.txt",\
		g_struLocalParam.chRemoteCfgSavePath, dtCurTime.GetYear(), dtCurTime.GetMonth(),\
		dtCurTime.GetDay());
	if ((m_fAlarm = fopen(csLogFile.GetBuffer(0), "a+")) == NULL)
	{
		GetDlgItem(IDC_BTN_LOG_SAVE)->EnableWindow(FALSE);
		g_struLocalParam.bAutoSaveLog = FALSE;
	}
}

/*********************************************************
Function:	OnTimer
Desc:		timer response function
Input:	nIDEvent, ID event value
Output:	
Return:	
**********************************************************/
#if (_MSC_VER >= 1500)	//vs2008
void CClientDemoDlg::OnTimer(UINT_PTR nIDEvent)
#else
void CClientDemoDlg::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	char szLan[128] = {0};
	
	CString csTemp = _T("");
	int i = 0;
	int j = 0;
	time_t	lCurrentTime;
	CString	csRecRootPath;
	
	CTime ctCurTime = CTime::GetCurrentTime();
	int iWeekday = ctCurTime.GetDayOfWeek() - 1;
	WORD	iNowTime = (WORD)(ctCurTime.GetHour() * 100 + ctCurTime.GetMinute());
	NET_DVR_TIME CurTime;
	CurTime.dwYear = ctCurTime.GetYear();
	CurTime.dwMonth = ctCurTime.GetMonth();
	CurTime.dwDay = ctCurTime.GetDay();
	CurTime.dwHour = ctCurTime.GetHour();
	CurTime.dwMinute = ctCurTime.GetMinute();
	CurTime.dwSecond = ctCurTime.GetSecond();
	switch (nIDEvent)
	{
	case SYSTEM_TIMER:
		if (g_struLocalParam.bAutoSaveLog && ctCurTime.GetHour() == 0\
			&& ctCurTime.GetMinute() == 0 && ctCurTime.GetSecond() == 0)
		{//one day
			CreateNewLogFile(TRUE);
		}
		
		break;
	case CYCLE_PREVIEW_TIMER:
		CyclePlayAllDevicesLogined();
		break;
	case FREESPACE_TIMER:
		csRecRootPath.Format("%c:\\", m_iCurRecDriver);	
		ULARGE_INTEGER FreeSpace,CallerSpace,TotalSpace;
		GetDiskFreeSpaceEx(csRecRootPath,&CallerSpace,&TotalSpace,&FreeSpace);
		g_struLocalParam.bAllDiskFull = FALSE;
		if (CallerSpace.QuadPart < MINSPACE)
		{
			csTemp.Format("%4d-%02d-%02d %02d:%02d:%02d HD Partition%c is Full", CurTime.dwYear, CurTime.dwMonth,\
				CurTime.dwDay, CurTime.dwHour, CurTime.dwMinute, CurTime.dwSecond, m_iCurRecDriver);
			AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, csTemp.GetBuffer(0));
			if (IsDiskFull())		//delete first 8 record files if hard disk is full
			{
				if (g_struLocalParam.bCycleRecord)
				{
					DeleteClientRecordFile();
				}
				else
				{
					for (i = 0; i < MAX_OUTPUTS; i++)
					{
						if ((g_dlgOutput[i].m_lPlayHandle >= 0) && (g_dlgOutput[i].m_bLocalManualRec))
						{
							AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "CClientDemoDlg::FREESPACE_TIMER stop");
							g_dlgOutput[i].StopLocalRecord();
						}
					}
					g_StringLanType(szLan, "客户端录像硬盘驱动器已满，无法继续录像", "Client hard disk drive is full, unable to continue record");
					g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, szLan);
					return;
				}
			}
			else
			{	//storage to other partition which is free
				if (MakeRecDir())
				{
					AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "switch to Hard disk partition%c", m_iCurRecDriver);
					for (i = 0; i < MAX_OUTPUTS; i++)
					{
						if ((g_dlgOutput[i].m_lPlayHandle >= 0) && (g_dlgOutput[i].m_bLocalManualRec))
						{
							g_dlgOutput[i].ChangeRecordFileName();
						}
					}
				}
			}
		}
		break;
	case FILEINTERVAL_TIMER:
		for (i = 0; i < MAX_OUTPUTS; i++)
		{
			if ((g_dlgOutput[i].m_lPlayHandle >= 0) && (g_dlgOutput[i].m_bLocalManualRec))
			{
				lCurrentTime = (time_t)ctCurTime.GetTime();
				if (lCurrentTime - g_dlgOutput[i].m_lChangeFileNameTime >= 0)
				{
					if (MakeRecDir())
					{
						g_dlgOutput[i].ChangeRecordFileName();
					}
				}
			}
		}
		break;
	case AUTORECORD_TIMER:
		if (g_struLocalParam.bCycling)
		{
			return;	//no record in client while cycle play
		}
		if (!g_struLocalParam.bAutoRecord)
		{
			return;
		}
		for (i = 0; i < 4; i++)
		{
			if ((iNowTime >= g_struLocalParam.struLocalRecordTime[iWeekday][i].iStartTime) && 
				(iNowTime < g_struLocalParam.struLocalRecordTime[iWeekday][i].iStopTime))
			{	//it is time auto record
				for (j = 0; j < MAX_OUTPUTS; j++)
				{
					if (g_dlgOutput[j].m_lPlayHandle >= 0)
					{
						if ( !g_dlgOutput[j].m_bLocalManualRec)
						{
							if (g_struLocalParam.bAllDiskFull)
							{
								AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "Client Hard Disk is full, pause recording");
								return;		//no record if client hard disk is full
							}
							if (MakeRecDir())
							{
								g_dlgOutput[j].AddLog(OPERATION_SUCC_T, "%02d:%02d start auto record", CurTime.dwHour, CurTime.dwMinute);
								g_dlgOutput[j].StartLocalRecord();
							}
						}
					}
				}
				break;
			}
			else
				i++;
		}
		if (i == 4)
		{
			for (j = 0; j < MAX_OUTPUTS; j++)
			{
				if (g_dlgOutput[j].m_bLocalManualRec)
				{
					g_dlgOutput[j].AddLog(OPERATION_SUCC_T, "%02d:%02d stop auto record", CurTime.dwHour, CurTime.dwMinute);
					g_dlgOutput[j].StopLocalRecord();
				}
			}
		}
		break;
	case CHECK_DEVICE_TIMER:
		if (g_struLocalParam.lCheckDeviceTime == (LONG)(CurTime.dwHour*10000 + CurTime.dwMinute*100 + CurTime.dwSecond))
		{
			for (i = 0; i < MAX_DEVICES; i++)
			{
				if (g_struDeviceInfo[i].lLoginID >= 0)
				{
					if (NET_DVR_SetDVRConfig(g_struDeviceInfo[i].lLoginID, NET_DVR_SET_TIMECFG, 0, &CurTime, sizeof(NET_DVR_TIME)))
					{
						AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SetDVRConfig");
					}
					else
					{
						AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetDVRConfig");
					}
				}
			}
		}
		break;
	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

/*********************************************************
Function:	OnCbnSelchangeComboWndNum
Desc:		change pic number in preview
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnCbnSelchangeComboWndNum()
{
	int iIndex = m_comboWinNum.GetCurSel();
	m_iCurWndNum = (int)pow(double(iIndex+1), 2);//current window number
	if (!IsPlaying())
	{
		m_iCurWndIndex = 0;//initialize current window index while switch window
		ArrangeOutputs(m_iCurWndNum);
		GetDlgItem(IDC_STATIC_PREVIEWBG)->Invalidate(TRUE);
	}
	else
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "请先停止播放", "Please stop previewing");
		AfxMessageBox(szLan);
	}
}

/*********************************************************
Function:	OnWMProcAlarm
Desc:		process alarm information when 
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::ProcAlarm(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	//	int iRet = 0;
	BOOL bDisk = FALSE;
	int i = 0;
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	char szLan[128] ={0};
	NET_DVR_ALARMINFO m_struAlarmInfo;
	memcpy(&m_struAlarmInfo, pAlarmInfo, sizeof(NET_DVR_ALARMINFO));
	if (!(g_struDeviceInfo[iDeviceIndex].bAlarm))
	{
		g_struDeviceInfo[iDeviceIndex].bAlarm = TRUE;
		::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_DEVICE_ITEM_IMAGE, WPARAM(g_pMainDlg->GetDeviceItem(iDeviceIndex)), LPARAM(iDeviceIndex));		
	}

	int iAChanNum = g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].dwAChanNum;

	switch (m_struAlarmInfo.dwAlarmType)
	{
	case 0://signal alarm
		g_StringLanType(szLan, "信号量报警 报警输入", "Signal alarm input");
		sprintf(szInfoBuf,"%s%d", szLan, m_struAlarmInfo.dwAlarmInputNumber+1); 
		g_StringLanType(szLan, ",触发通道录像:", ", Invoke record Channel:");
		sprintf(szInfoBuf,"%s%s", szInfoBuf, szLan); 
		for (i=0; i<MAX_CHANNUM; i++)
		{
			if (m_struAlarmInfo.dwAlarmRelateChannel[i] == 1)
			{
				sprintf(szInfoBuf,"%s %d,", szInfoBuf, i+g_struDeviceInfo[iDeviceIndex].iStartChan); 
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
		break;
	case 1://hard disk full alarm
		g_StringLanType(szInfoBuf, "硬盘满报警:", "HDD is Full:");
		for (i=0; i<MAX_DISKNUM; i++)
		{
			if (m_struAlarmInfo.dwDiskNumber[i] == 1)
			{
				sprintf(szInfoBuf, "%s HDD%d ", szInfoBuf, i);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
		break;
	case 2://video loss alarm
		g_StringLanType(szInfoBuf, "视频信号丢失报警:", "The video signal lost:");
		for (i=0; i<MAX_CHANNUM; i++)
		{
			if (m_struAlarmInfo.dwChannel[i] == 1)
			{
				if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
				{
					g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));	
				}
				sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);				
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 3://motion detection alarm
		g_StringLanType(szInfoBuf, "移动侦测报警", "motion detection");
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (m_struAlarmInfo.dwChannel[i] == 1)
			{
				
				if (g_struDeviceInfo[iDeviceIndex].iStartChan ==0)
				{
					//模拟通道
					if (i < MAX_ANALOG_CHANNUM)
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
						}
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
					}
					else   // 数字通道，i
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i-32+iAChanNum].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i-32+iAChanNum].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i-32+iAChanNum));		
						}
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i-32+iAChanNum].chChanName);
					}
				}
				else
				{
					if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i-g_struDeviceInfo[iDeviceIndex].iStartChan+iAChanNum));		
					}
					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i-g_struDeviceInfo[iDeviceIndex].iStartChan+iAChanNum].chChanName);
				}
				
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 4://hard disk unformatted alarm
		g_StringLanType(szInfoBuf, "硬盘未格式化报警", "HDD not formatted:");
		for (i=0; i<MAX_DISKNUM; i++)
		{
			if (m_struAlarmInfo.dwDiskNumber[i] == 1)
			{
				sprintf(szInfoBuf, "%s HDD%d", szInfoBuf, i);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 5://hard disk alarm
		for (i=0; i<MAX_DISKNUM; i++)
		{
			if (m_struAlarmInfo.dwDiskNumber[i] == 1)
			{
				bDisk = TRUE;
				g_StringLanType(szLan, "读写硬盘出错", "failed to read and write HDD");
				sprintf(szInfoBuf, "%sHDD%d ", szLan, i);
				g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
			}
		}
		if (bDisk == FALSE)
		{
			g_StringLanType(szInfoBuf, "未接硬盘出错报警", "no HDD");
			g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		}
		bDisk = FALSE;
		break;
	case 6://mask alarm
		g_StringLanType(szInfoBuf, "发生遮挡报警", "Mask alarm");
		for (i=0; i<MAX_CHANNUM; i++)
		{
			if (m_struAlarmInfo.dwChannel[i] == 1)
			{
				if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
				{
					g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
				}
				sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
			}
		}	
		
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 7:	//type unmatched
		g_StringLanType(szInfoBuf, "制式不匹配", "input and output video standard not match");
		for (i=0; i<MAX_CHANNUM; i++)
		{
			if (m_struAlarmInfo.dwChannel[i] == 1)
			{
				if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
				{
					g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
				}
				sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 8:
		g_StringLanType(szInfoBuf, "非法访问", "illegal access");
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);		
break;
	case 9:
        g_StringLanType(szInfoBuf, "视频信号异常", "video exception");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);		
		break;
    case 10:
        g_StringLanType(szInfoBuf, "录像异常", "record exception");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);		
		break;
    case 11:
        g_StringLanType(szInfoBuf, "智能场景变化", "Vca scene change");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
        break;
	default:
		g_StringLanType(szLan, "未知报警类型:", "Unknown Alarm Type:");
		sprintf(szInfoBuf, "%s 0x%x", szLan, m_struAlarmInfo.dwAlarmType);
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	}
}

/*********************************************************
Function:	ProcAlarmV30
Desc:		process alarm information for version 30
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::ProcAlarmV30(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	BOOL bDisk = FALSE;
	int i = 0;
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
    if (iDeviceIndex > 512)
    {
        return;
    }
	char szLan[128] ={0};
	NET_DVR_ALARMINFO_V30 m_struAlarmInfoV30;
	memcpy(&m_struAlarmInfoV30, pAlarmInfo, sizeof(NET_DVR_ALARMINFO_V30));
	if (!(g_struDeviceInfo[iDeviceIndex].bAlarm))
	{
		g_struDeviceInfo[iDeviceIndex].bAlarm = TRUE;
		::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_DEVICE_ITEM_IMAGE, WPARAM(g_pMainDlg->GetDeviceItem(iDeviceIndex)), LPARAM(iDeviceIndex));		
	}

	//模拟通道数
	int iAChanNum = g_struDeviceInfo[iDeviceIndex].iAnalogChanNum;
	
	//数字通道数
	int iDChanNum = g_struDeviceInfo[iDeviceIndex].iIPChanNum;

	switch (m_struAlarmInfoV30.dwAlarmType)
	{
	case 0://signal alarm
		g_StringLanType(szLan, "信号量报警 报警输入", "Signal alarm input");
		sprintf(szInfoBuf,"%s%d", szLan, m_struAlarmInfoV30.dwAlarmInputNumber+1); 
		g_StringLanType(szLan, ",触发通道录像:", "Invoke record Channel:");
		sprintf(szInfoBuf,"%s%s", szInfoBuf, szLan); 
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byAlarmRelateChannel[i] == 1)
			{
				// 					if (i<MAX_ANALOG_CHANNUM)
				// 					{
				sprintf(szInfoBuf,"%s %d,", szInfoBuf, i+g_struDeviceInfo[iDeviceIndex].iStartChan); 	
				// 					}
				// 					else
				// 					{
				// 						sprintf(szInfoBuf,"%s %s%d,", szInfoBuf,"IPChan", i+g_struDeviceInfo[iDeviceIndex].iStartChan); 
				// 					}
				
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
		break;
	case 1://hard disk full alarm
		g_StringLanType(szInfoBuf, "硬盘满报警", "HD is full:");
		for (i=0; i<MAX_DISKNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byDiskNumber[i] == 1)
			{
				sprintf(szInfoBuf, "%s HDD%d ", szInfoBuf, i+1);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
		break;
	case 2://video loss alarm
		g_StringLanType(szInfoBuf, "视频信号丢失报警", "The signal lost");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				//模拟通道
				if (i < MAX_ANALOG_CHANNUM)
				{
					if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
					}
					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);	
				}
				else
				{
					if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i-32+iAChanNum].bAlarm))
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i-32+iAChanNum].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i-32+iAChanNum));			
					}
					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i-32+iAChanNum].chChanName);	
				}

	
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
 		break;
	case 3://motion detection alarm
		g_StringLanType(szInfoBuf, "移动侦测报警", "motion detection");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				//纯模拟通道或纯数字通道
				if (0 == iDChanNum || 0 == iAChanNum)
				{
					if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
					}

					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);	
				}
				else if(iAChanNum > 0 && iDChanNum > 0)  //混合通道
				{
					//模拟通道
					if (i < MAX_ANALOG_CHANNUM)
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
						}

						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);		
					}
					else //数字通道
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iAChanNum+i-MAX_ANALOG_CHANNUM));		
						}

						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].chChanName);
					}
				}
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 4://hard disk unformatted alarm
		g_StringLanType(szInfoBuf, "硬盘未格式化报警", "not formatted");
		for (i=0; i<MAX_DISKNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byDiskNumber[i] == 1)
			{
				sprintf(szInfoBuf, "%s HDD%d ", szInfoBuf, i);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 5://hard disk alarm
		for (i=0; i<MAX_DISKNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byDiskNumber[i] == 1)
			{
				bDisk = TRUE;
				g_StringLanType(szLan, "读写硬盘出错", "failed to read and write HDD");
				sprintf(szInfoBuf, "%sHDD%d ", szLan, i+1);
				g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
			}
		}
		if (bDisk == FALSE)
		{
			g_StringLanType(szInfoBuf, "未接硬盘出错报警", "No HDD");
			g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		}
		bDisk = FALSE;
		break;
	case 6://mask alarm
		g_StringLanType(szInfoBuf, "发生遮挡报警", "Mask alarm");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				//纯模拟通道或纯数字通道
				if (0 == iDChanNum || 0 == iAChanNum)
				{
					if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
					}
					
					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);	
				}
				else if(iAChanNum > 0 && iDChanNum > 0)  //混合通道
				{
					//模拟通道
					if (i < MAX_ANALOG_CHANNUM)
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);		
					}
					else //数字通道
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iAChanNum+i-MAX_ANALOG_CHANNUM));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].chChanName);
					}
				}
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 7:	//type unmatched
		g_StringLanType(szInfoBuf, "制式不匹配", "input and output video standard not match");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				//纯模拟通道或纯数字通道
				if (0 == iDChanNum || 0 == iAChanNum)
				{
					if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
					}
					
					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);	
				}
				else if(iAChanNum > 0 && iDChanNum > 0)  //混合通道
				{
					//模拟通道
					if (i < MAX_ANALOG_CHANNUM)
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);		
					}
					else //数字通道
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iAChanNum+i-MAX_ANALOG_CHANNUM));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].chChanName);
					}
				}
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 8:
		g_StringLanType(szInfoBuf, "非法访问", "illegal access");
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);		
		break;
    case 9:
        g_StringLanType(szInfoBuf, "视频信号异常", "video exception");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				//纯模拟通道或纯数字通道
				if (0 == iDChanNum || 0 == iAChanNum)
				{
					if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
					}
					
					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);	
				}
				else if(iAChanNum > 0 && iDChanNum > 0)  //混合通道
				{
					//模拟通道
					if (i < MAX_ANALOG_CHANNUM)
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);		
					}
					else //数字通道
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iAChanNum+i-MAX_ANALOG_CHANNUM));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].chChanName);
					}
				}
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
    case 10:
        g_StringLanType(szInfoBuf, "录像异常", "record exception");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				//纯模拟通道或纯数字通道
				if (0 == iDChanNum || 0 == iAChanNum)
				{
					if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
					}
					
					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);	
				}
				else if(iAChanNum > 0 && iDChanNum > 0)  //混合通道
				{
					//模拟通道
					if (i < MAX_ANALOG_CHANNUM)
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);		
					}
					else //数字通道
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iAChanNum+i-MAX_ANALOG_CHANNUM));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].chChanName);
					}
				}
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
    case 11:
        g_StringLanType(szInfoBuf, "智能场景变化", "Vca scene change");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				//纯模拟通道或纯数字通道
				if (0 == iDChanNum || 0 == iAChanNum)
				{
					if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
					}
					
					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);	
				}
				else if(iAChanNum > 0 && iDChanNum > 0)  //混合通道
				{
					//模拟通道
					if (i < MAX_ANALOG_CHANNUM)
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);		
					}
					else //数字通道
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iAChanNum+i-MAX_ANALOG_CHANNUM));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].chChanName);
					}
				}
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
    case 12:
        g_StringLanType(szInfoBuf, "阵列异常", "Array exception");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
        break;
	case 13:
		g_StringLanType(szInfoBuf, "前端/录像分辨率不匹配", "resolution mismatch");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				//纯模拟通道或纯数字通道
				if (0 == iDChanNum || 0 == iAChanNum)
				{
					if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
					}
					
					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);	
				}
				else if(iAChanNum > 0 && iDChanNum > 0)  //混合通道
				{
					//模拟通道
					if (i < MAX_ANALOG_CHANNUM)
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);		
					}
					else //数字通道
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iAChanNum+i-MAX_ANALOG_CHANNUM));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].chChanName);
					}
				}
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 14:
		g_StringLanType(szInfoBuf, "申请解码资源失败", "Alloc decoede resource fail");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				//纯模拟通道或纯数字通道
				if (0 == iDChanNum || 0 == iAChanNum)
				{
					if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
					{
						g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
						::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
					}
					
					sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);	
				}
				else if(iAChanNum > 0 && iDChanNum > 0)  //混合通道
				{
					//模拟通道
					if (i < MAX_ANALOG_CHANNUM)
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);		
					}
					else //数字通道
					{
						if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm)
						{
							g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].bAlarm = TRUE;
							::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iAChanNum+i-MAX_ANALOG_CHANNUM));		
						}
						
						sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+i-MAX_ANALOG_CHANNUM].chChanName);
					}
				}
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
    case 15:
	    g_StringLanType(szInfoBuf, "智能侦测", "VCA Detction");
	    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
    case 16:
        g_StringLanType(szInfoBuf, "POE供电异常", "POE Power Exception");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 17:
        g_StringLanType(szInfoBuf, "闪光灯异常", "Flash anomaly");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
    case 18:
        g_StringLanType(szInfoBuf, "磁盘满负荷异常", "Disk full load anomaly");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 19:
        g_StringLanType(szInfoBuf, "音频信号丢失报警", "The audio signal lost");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
    case 23:
        g_StringLanType(szLan, "脉冲报警 报警输入", "Pulse alarm input");
        sprintf(szInfoBuf, "%s%d", szLan, m_struAlarmInfoV30.dwAlarmInputNumber + 1);
        g_StringLanType(szLan, ",触发通道录像:", "Invoke record Channel:");
        sprintf(szInfoBuf, "%s%s", szInfoBuf, szLan);
        for (i = 0; i < MAX_CHANNUM_V30; i++)
        {
            if (m_struAlarmInfoV30.byAlarmRelateChannel[i] == 1)
            {
                sprintf(szInfoBuf, "%s %d,", szInfoBuf, i + g_struDeviceInfo[iDeviceIndex].iStartChan);
            }
        }
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 24:
        g_StringLanType(szInfoBuf, "人脸库硬盘异常", "FDLib Disk lost alarm");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 25:
        g_StringLanType(szInfoBuf, "人脸库变更", "FDLib changed");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 26:
        g_StringLanType(szInfoBuf, "人脸库图片变更", "FDLib picture changed");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 27:
        g_StringLanType(szInfoBuf, "POC 异常", "POC Exception");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 28://camera angle anomaly
        g_StringLanType(szInfoBuf, "相机视角异常", "camera angle anomaly");
        for (i = 0; i < MAX_CHANNUM_V30; i++)
        {
            if (m_struAlarmInfoV30.byChannel[i] == 1)
            {
                //纯模拟通道或纯数字通道
                if (0 == iDChanNum || 0 == iAChanNum)
                {
                    if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm))
                    {
                        g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
                        ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
                    }

                    sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
                }
                else if (iAChanNum > 0 && iDChanNum > 0)  //混合通道
                {
                    //模拟通道
                    if (i < MAX_ANALOG_CHANNUM)
                    {
                        if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
                        {
                            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
                            ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
                        }

                        sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
                    }
                    else //数字通道
                    {
                        if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum + i - MAX_ANALOG_CHANNUM].bAlarm)
                        {
                            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum + i - MAX_ANALOG_CHANNUM].bAlarm = TRUE;
                            ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iAChanNum + i - MAX_ANALOG_CHANNUM));
                        }

                        sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum + i - MAX_ANALOG_CHANNUM].chChanName);
                    }
                }
            }
        }
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
	default:
		g_StringLanType(szLan, "未知报警类型:", "Unknown Alarm Type:");
		sprintf(szInfoBuf, "%s 0x%x-htonl%d", szLan, m_struAlarmInfoV30.dwAlarmType, ntohl(m_struAlarmInfoV30.dwAlarmType));
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	}
}


/*********************************************************
Function:	ProcAlarmV40
Desc:		process alarm information for version 40
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::ProcAlarmV40(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[10240] = {0};
	BOOL bDisk = FALSE;
	int i = 0;
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	if (MAX_DEVICES < iDeviceIndex || 0 > iDeviceIndex)
	{
		return;
	}
	char szLan[128] ={0};
    NET_DVR_ALARMINFO_V40 m_struAlarmInfoV40 = {0};
	memcpy(&m_struAlarmInfoV40, pAlarmInfo, sizeof(NET_DVR_ALARMINFO_V40));
    DWORD *pContent = m_struAlarmInfoV40.pAlarmData;
	if (!(g_struDeviceInfo[iDeviceIndex].bAlarm))
	{
		g_struDeviceInfo[iDeviceIndex].bAlarm = TRUE;
		::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_DEVICE_ITEM_IMAGE, WPARAM(g_pMainDlg->GetDeviceItem(iDeviceIndex)), LPARAM(iDeviceIndex));		
	}

	//模拟通道数
	int iAChanNum = g_struDeviceInfo[iDeviceIndex].iAnalogChanNum;
	
	//数字通道数
	int iDChanNum = g_struDeviceInfo[iDeviceIndex].iIPChanNum;

    int dwOffSetLen = 0;

    DWORD dwTemp = 0;
    BOOL bAlarmOut = FALSE;

    //打印时间
    char szTimeLog[256] = {0};
    sprintf(szTimeLog, "%04d-%02d-%02d %02d:%02d:%02d flag(%d)%02d%02d", m_struAlarmInfoV40.struAlarmFixedHeader.struAlarmTime.wYear, 
        m_struAlarmInfoV40.struAlarmFixedHeader.struAlarmTime.byMonth,
        m_struAlarmInfoV40.struAlarmFixedHeader.struAlarmTime.byDay,
        m_struAlarmInfoV40.struAlarmFixedHeader.struAlarmTime.byHour,
        m_struAlarmInfoV40.struAlarmFixedHeader.struAlarmTime.byMinute,
        m_struAlarmInfoV40.struAlarmFixedHeader.struAlarmTime.bySecond,
        m_struAlarmInfoV40.struAlarmFixedHeader.byTimeDiffFlag,
        m_struAlarmInfoV40.struAlarmFixedHeader.cTimeDifferenceH,
        m_struAlarmInfoV40.struAlarmFixedHeader.cTimeDifferenceM);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szTimeLog);

    switch (m_struAlarmInfoV40.struAlarmFixedHeader.dwAlarmType)
    {
    case 0://signal alarm
        g_StringLanType(szLan, "信号量报警 报警输入号", "Signal alarm input No.");
        sprintf(szInfoBuf,"%s%d", szLan, m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struIOAlarm.dwAlarmInputNo +1); 
        g_StringLanType(szLan, ",关联报警输出号:", "Invoke Alarm Out:");
        sprintf(szInfoBuf,"%s%s", szInfoBuf, szLan); 
        
        for (i=0; i<m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struIOAlarm.dwTrigerAlarmOutNum; i++)
        {
            if (*(m_struAlarmInfoV40.pAlarmData + i) != 0xffffffff)
            {
                sprintf(szInfoBuf,"%s %d,", szInfoBuf, *(m_struAlarmInfoV40.pAlarmData + i)); 
            }
        }
        
        g_StringLanType(szLan, ",触发通道录像:", "Invoke record Channel:");
        sprintf(szInfoBuf,"%s%s", szInfoBuf, szLan); 
        dwOffSetLen += m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struIOAlarm.dwTrigerAlarmOutNum;
        for (i=0; i<m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struIOAlarm.dwTrigerRecordChanNum; i++)
        {
            if (*(m_struAlarmInfoV40.pAlarmData + dwOffSetLen) != 0xffffffff)
            {
                sprintf(szInfoBuf,"%s %d,", szInfoBuf, *(m_struAlarmInfoV40.pAlarmData + dwOffSetLen)); 
                dwOffSetLen++;
            }
        }
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
        break;
    case 1://hard disk full alarm
        g_StringLanType(szInfoBuf, "硬盘满报警", "HD is full:");
        for (i=0; i<m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struAlarmHardDisk.dwAlarmHardDiskNum; i++)
        {
            // 			if (m_struAlarmInfoV40.dwAlarmData[dwOffSetLen/4] != 0xffffffff )
            // 			{
            // 				sprintf(szInfoBuf, "%s HDD%d ", szInfoBuf, m_struAlarmInfoV40.dwAlarmData[dwOffSetLen/4]);
            //                 dwOffSetLen ++;
            // 			}
            
            if (*(m_struAlarmInfoV40.pAlarmData + dwOffSetLen) != 0xffffffff )
            {
                sprintf(szInfoBuf, "%s HDD%d ", szInfoBuf, *(m_struAlarmInfoV40.pAlarmData + dwOffSetLen));
                dwOffSetLen ++;
            }
        }
        
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
		break;	
	case 4://hard disk unformatted alarm
		g_StringLanType(szInfoBuf, "硬盘未格式化报警", "not formatted");
		for (i=0; i<m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struAlarmHardDisk.dwAlarmHardDiskNum; i++)
		{
		
            dwTemp = *(m_struAlarmInfoV40.pAlarmData + dwOffSetLen);
			if (dwTemp > 0)
			{
				sprintf(szInfoBuf, "%s HDD%d ", szInfoBuf,dwTemp);
                dwOffSetLen++;
			}
            else
            {
                break;
            }
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 5://hard disk alarm
		for (i=0; i<m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struAlarmHardDisk.dwAlarmHardDiskNum; i++)
		{
            dwTemp = *(m_struAlarmInfoV40.pAlarmData + dwOffSetLen);
            if (dwTemp > 0)
            {
                bDisk = TRUE;
                g_StringLanType(szLan, "读写硬盘出错", "failed to read and write HDD");
                sprintf(szInfoBuf, "%sHDD%d ", szLan, dwTemp);
				g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
                dwOffSetLen++;
            }
            else
            {
                break;
            }
		}

        if (bDisk == FALSE)
        {
            g_StringLanType(szInfoBuf, "未接硬盘导致出错报警", "No HDD");
            g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        }
        bDisk = FALSE;
        break;
        
    case 2://video loss alarm
        bAlarmOut = TRUE;
        g_StringLanType(szInfoBuf, "视频信号丢失报警", "The signal lost");
        break;
    case 3://motion detection alarm
        bAlarmOut = TRUE;
        g_StringLanType(szInfoBuf, "移动侦测报警", "motion detection");
        break;
    case 6://mask alarm
        bAlarmOut = TRUE;
        g_StringLanType(szInfoBuf, "发生遮挡报警", "Mask alarm");
        break;
    case 9:
        bAlarmOut = TRUE;
        g_StringLanType(szInfoBuf, "视频信号异常", "video exception");
        break;
    case 10:
        bAlarmOut = TRUE;
        g_StringLanType(szInfoBuf, "录像异常", "record exception");
        break;
    case 11:
        bAlarmOut = TRUE;
        g_StringLanType(szInfoBuf, "智能场景变化", "Vca scene change");
        break;
    case 13:
        bAlarmOut = TRUE;
        g_StringLanType(szInfoBuf, "前端/录像分辨率不匹配", "resolution mismatch");
        break;
        
    case 7:	//type unmatched
        g_StringLanType(szInfoBuf, "制式不匹配", "input and output video standard not match");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 8:
        g_StringLanType(szInfoBuf, "非法访问", "illegal access");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);		
        break;
    case 12:
        g_StringLanType(szInfoBuf, "阵列异常", "Array exception");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
        break;
	case 14:
        g_StringLanType(szInfoBuf, "申请解码资源失败", "Alloc decoede resource fail");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
    case 15:
        bAlarmOut = TRUE;
        g_StringLanType(szInfoBuf, "智能侦测报警", "VCA Detection");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 16:
		g_StringLanType(szInfoBuf, "热备异常报警", "host record alarm");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 17:
		g_StringLanType(szInfoBuf, "录播主机报警", "hot spare alarm");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
    case 18:
        g_StringLanType(szInfoBuf, "语音对讲请求报警", "Talkback requesting alarm");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
    case 19:
        bAlarmOut = TRUE;
        g_StringLanType(szInfoBuf, "音频信号丢失报警", "The audio signal lost");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 22:
        g_StringLanType(szInfoBuf, "车辆检测算法异常报警", "Vehicle Detection Algorithm alarm");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 23:
        g_StringLanType(szLan, "脉冲报警 报警输入号", "Pulse alarm input No.");
        sprintf(szInfoBuf, "%s%d", szLan, m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struIOAlarm.dwAlarmInputNo + 1);
        g_StringLanType(szLan, ",关联报警输出号:", "Invoke Alarm Out:");
        sprintf(szInfoBuf, "%s%s", szInfoBuf, szLan);

        for (i = 0; i < m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struIOAlarm.dwTrigerAlarmOutNum; i++)
        {
            if (*(m_struAlarmInfoV40.pAlarmData + i) != 0xffffffff)
            {
                sprintf(szInfoBuf, "%s %d,", szInfoBuf, *(m_struAlarmInfoV40.pAlarmData + i));
            }
        }

        g_StringLanType(szLan, ",触发通道录像:", "Invoke record Channel:");
        sprintf(szInfoBuf, "%s%s", szInfoBuf, szLan);
        dwOffSetLen += m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struIOAlarm.dwTrigerAlarmOutNum;
        for (i = 0; i < m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struIOAlarm.dwTrigerRecordChanNum; i++)
        {
            if (*(m_struAlarmInfoV40.pAlarmData + dwOffSetLen) != 0xffffffff)
            {
                sprintf(szInfoBuf, "%s %d,", szInfoBuf, *(m_struAlarmInfoV40.pAlarmData + dwOffSetLen));
                dwOffSetLen++;
            }
        }
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 24:
        g_StringLanType(szInfoBuf, "人脸库硬盘异常", "FDLib Disk lost alarm");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 25:
        g_StringLanType(szInfoBuf, "人脸库变更", "FDLib changed");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 26:
        g_StringLanType(szInfoBuf, "人脸库图片变更", "FDLib picture changed");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 27:
        g_StringLanType(szInfoBuf, "POC 异常", "POC Exception");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
    case 28:
        bAlarmOut = TRUE;
        g_StringLanType(szInfoBuf, "相机视角异常", "camera angle anomaly");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
        break;
	default:
		g_StringLanType(szLan, "未知报警类型:", "Unknown Alarm Type:");
		sprintf(szInfoBuf, "%s 0x%x-htonl%d", szLan, m_struAlarmInfoV40.struAlarmFixedHeader.dwAlarmType, ntohl(m_struAlarmInfoV40.struAlarmFixedHeader.dwAlarmType));
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	}
   
    if (bAlarmOut && pContent != NULL)
    {
        for (i=0; i<m_struAlarmInfoV40.struAlarmFixedHeader.uStruAlarm.struAlarmChannel.dwAlarmChanNum; i++)
        {
            dwTemp = *(m_struAlarmInfoV40.pAlarmData + dwOffSetLen);
            dwTemp = *(pContent + i); 
            sprintf(szInfoBuf, "%s ,AlarmChan[%d]", szInfoBuf, dwTemp);
            if (dwTemp > 0 && dwTemp < MAX_CHANNUM_V40)
            {
                //纯模拟通道或纯数字通道
                if (0 == iDChanNum || 0 == iAChanNum)
                {
                    if (!(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwTemp- 1].bAlarm))
                    {
                        g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwTemp- 1].bAlarm = TRUE;
                        ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(dwTemp- 1));			
                       }
                    
                    sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwTemp- 1].chChanName);	
                }
                else if(iAChanNum > 0 && iDChanNum > 0)  //混合通道
                {
                    //模拟通道
                    if (i < MAX_ANALOG_CHANNUM)
                    {
                        if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwTemp- 1].bAlarm)
                        {
                            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwTemp- 1].bAlarm = TRUE;
                            ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(dwTemp- 1));		
                        }
                        
                        sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwTemp- 1].chChanName);		
                    }
                    else //数字通道
                    {
                        if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+dwTemp- 1-MAX_ANALOG_CHANNUM].bAlarm)
                        {
                            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+dwTemp- 1-MAX_ANALOG_CHANNUM].bAlarm = TRUE;
                            ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(iAChanNum+dwTemp- 1-MAX_ANALOG_CHANNUM));		
                        }
                        
                        sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iAChanNum+dwTemp- 1-MAX_ANALOG_CHANNUM].chChanName);
                    }
                }
                dwOffSetLen++;
            }
            else
            {
                break;
            }
        }
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    }
    if (m_struAlarmInfoV40.pAlarmData != NULL)
    {
        delete[](m_struAlarmInfoV40.pAlarmData);
        m_struAlarmInfoV40.pAlarmData = NULL;
    }
}


/*********************************************************
Function:	
Desc:		
Input:	void
Output:	void
Return:	0, same, else-difference
**********************************************************/
int CmpIPCfgAndIPCfgV31(LPNET_DVR_IPDEVINFO_V31 lpDevInfoV31, LPNET_DVR_IPDEVINFO lpDevInfo)
{
	if (lpDevInfo->dwEnable != lpDevInfoV31->byEnable)
	{
		return -1;
	}
	if (lpDevInfo->wDVRPort != lpDevInfoV31->wDVRPort)
	{
		return -1;
	}
	if (memcmp((char *)(lpDevInfoV31->sPassword), (char *)(lpDevInfoV31->sPassword), PASSWD_LEN) != 0)
	{
		return -1;
	}
	if (memcmp((char *)(lpDevInfo->sUserName), (char *)(lpDevInfoV31->sUserName), MAX_NAMELEN) != 0)
	{
		return -1;
	}
	if (memcmp((char *)&(lpDevInfo->struIP), (char *)&(lpDevInfoV31->struIP), sizeof(NET_DVR_IPDEVINFO)) != 0)
	{
		return -1;
	}
	memset((char *)(lpDevInfoV31->byDomain), 0, MAX_DOMAIN_NAME);//the old ipc parameter change need to clear domain information
	return 0;
}

/*********************************************************
Function:	ProcIPCfgAlarm
Desc:		process alarm information when 
Input:	void
Output:	void
Return:	void
**********************************************************/
void CClientDemoDlg::ProcIPCfgAlarm(WPARAM wParam, LPARAM lParam)
{
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	int iRet = 0;
	int i = 0;
	NET_DVR_IPALARMINFO struIPAlarmInfo;
	memcpy(&struIPAlarmInfo, pAlarmInfo, sizeof(NET_DVR_IPALARMINFO));
    for (i = 0; i < ARRAY_SIZE(struIPAlarmInfo.struIPChanInfo); i++)
    {
        memcpy(&g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].struStreamMode[i].uGetStream.struChanInfo, \
           &struIPAlarmInfo.struIPChanInfo[i], sizeof(NET_DVR_IPCHANINFO));
    }
	iRet |= memcmp(g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].byAnalogChanEnable, struIPAlarmInfo.byAnalogChanEnable, sizeof(struIPAlarmInfo.byAnalogChanEnable));
	for (i=0; i < MAX_IP_DEVICE; i++)
	{
		iRet |= CmpIPCfgAndIPCfgV31(&(g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].struIPDevInfo[i]), &(struIPAlarmInfo.struIPDevInfo[i]));
	}
	
	if (iRet != 0)
	{
        for (i = 0; i < ARRAY_SIZE(struIPAlarmInfo.struIPChanInfo); i++)
        {
            memcpy(&g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].struStreamMode[i].uGetStream.struChanInfo, \
                &struIPAlarmInfo.struIPChanInfo[i], sizeof(NET_DVR_IPCHANINFO));
        }
		memcpy(g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].byAnalogChanEnable, struIPAlarmInfo.byAnalogChanEnable, sizeof(struIPAlarmInfo.byAnalogChanEnable));
		memcpy(g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].struIPDevInfo, struIPAlarmInfo.struIPDevInfo, sizeof(struIPAlarmInfo.struIPDevInfo));
	//	memcpy(g_struDeviceInfo[iDeviceIndex].struAlarmInCfg.struIPAlarmInInfo, struIPAlarmInfo.struIPAlarmInInfo, MAX_IP_ALARMIN*sizeof(NET_DVR_IPALARMININFO));
	//	memcpy(g_struDeviceInfo[iDeviceIndex].struAlarmOutCfg.struIPAlarmOutInfo, struIPAlarmInfo.struIPAlarmOutInfo, MAX_IP_ALARMOUT*sizeof(NET_DVR_IPALARMOUTINFO));
		g_pMainDlg->RefreshIPDevLocalCfg(iDeviceIndex);
		g_pMainDlg->RedrawDeviceNode(iDeviceIndex);
	}
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "ip parameter is channged!");
}


/*********************************************************
Function:	ProcIPCfgAlarmV31
Desc:		process alarm information when 
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::ProcIPCfgAlarmV31(WPARAM wParam, LPARAM lParam)
{
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	int iRet = 0;
	NET_DVR_IPALARMINFO_V31 struIPAlarmInfo;
	memcpy(&struIPAlarmInfo, pAlarmInfo, sizeof(NET_DVR_IPALARMINFO_V31));
    int i = 0;
    for (i = 0; i < ARRAY_SIZE(struIPAlarmInfo.struIPChanInfo); i++)
    {
        memcpy(&g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].struStreamMode[i].uGetStream.struChanInfo, \
            &struIPAlarmInfo.struIPChanInfo[i], sizeof(NET_DVR_IPCHANINFO));
    }
	iRet |= memcmp(g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].byAnalogChanEnable, struIPAlarmInfo.byAnalogChanEnable, sizeof(struIPAlarmInfo.byAnalogChanEnable));
	iRet |= memcmp(g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].struIPDevInfo, struIPAlarmInfo.struIPDevInfo, sizeof(struIPAlarmInfo.struIPDevInfo));//9000_1.1 need change
	if (iRet != 0)
	{
        for (i = 0; i < ARRAY_SIZE(struIPAlarmInfo.struIPChanInfo); i++)
        {
            memcpy(&g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].struStreamMode[i].uGetStream.struChanInfo, \
                &struIPAlarmInfo.struIPChanInfo[i], sizeof(NET_DVR_IPCHANINFO));
        }
        memcpy(g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].byAnalogChanEnable, struIPAlarmInfo.byAnalogChanEnable, sizeof(struIPAlarmInfo.struIPChanInfo));
		memcpy(g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].struIPDevInfo, struIPAlarmInfo.struIPDevInfo, sizeof(struIPAlarmInfo.struIPDevInfo));
		//memcpy(g_struDeviceInfo[iDeviceIndex].struAlarmInCfg.struIPAlarmInInfo, struIPAlarmInfo.struIPAlarmInInfo, MAX_IP_ALARMIN*sizeof(NET_DVR_IPALARMININFO));
		//memcpy(g_struDeviceInfo[iDeviceIndex].struAlarmOutCfg.struIPAlarmOutInfo, struIPAlarmInfo.struIPAlarmOutInfo, MAX_IP_ALARMOUT*sizeof(NET_DVR_IPALARMOUTINFO));
		g_pMainDlg->RefreshIPDevLocalCfg(iDeviceIndex);
		g_pMainDlg->RedrawDeviceNode(iDeviceIndex);
	}
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "ip parameter v31 is channged!");
}


void CClientDemoDlg::ProcPdcAlarm(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iWinIndex = -1;
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	
	NET_DVR_PDC_ALRAM_INFO  struPDCAlarmInfo;
    memset(&struPDCAlarmInfo, 0, sizeof(struPDCAlarmInfo));
	CTime time = CTime::GetCurrentTime();
	memcpy(&struPDCAlarmInfo, pAlarmInfo, sizeof(struPDCAlarmInfo));
    i = struPDCAlarmInfo.byChannel-g_struDeviceInfo[iDeviceIndex].iStartChan;
    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));	

	
    if (struPDCAlarmInfo.byMode == 0 )
    {
        //  打印信息
        NET_DVR_TIME  struAbsTime = {0};
        struAbsTime.dwYear = GET_YEAR(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwAbsTime);
        struAbsTime.dwMonth = GET_MONTH(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwAbsTime);
        struAbsTime.dwDay = GET_DAY(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwAbsTime);
        struAbsTime.dwHour = GET_HOUR(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwAbsTime);
        struAbsTime.dwMinute = GET_MINUTE(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwAbsTime);
        struAbsTime.dwSecond = GET_SECOND(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwAbsTime);
        
        NET_DVR_TIME  struRelativeTime = {0};
        struRelativeTime.dwYear = GET_YEAR(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwRelativeTime);
        struRelativeTime.dwMonth = GET_MONTH(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwRelativeTime);
        struRelativeTime.dwDay = GET_DAY(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwRelativeTime);
        struRelativeTime.dwHour = GET_HOUR(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwRelativeTime);
        struRelativeTime.dwMinute = GET_MINUTE(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwRelativeTime);
        struRelativeTime.dwSecond = GET_SECOND(struPDCAlarmInfo.uStatModeParam.struStatFrame.dwRelativeTime);

        sprintf(szInfoBuf, "Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d flag[%d] %2.2d%2.2d]] Rel[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] DevIP:[%s]Port[%d]Channel[%d] IvmsChannel[%d]IvmsChannelEx[%d] single frame:Channel[%d]LeaveNum[%d]EnterNum[%d]Passing[%d]Smart[%d] BrokenNetHttp[%d] ",
            struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond,
            struPDCAlarmInfo.uStatModeParam.struStatFrame.byTimeDiffFlag, struPDCAlarmInfo.uStatModeParam.struStatFrame.cTimeDifferenceH, struPDCAlarmInfo.uStatModeParam.struStatFrame.cTimeDifferenceM,
            struRelativeTime.dwYear, struRelativeTime.dwMonth, struRelativeTime.dwDay, struRelativeTime.dwHour, struRelativeTime.dwMinute, struRelativeTime.dwSecond,
            struPDCAlarmInfo.struDevInfo.struDevIP.sIpV4, struPDCAlarmInfo.struDevInfo.wPort, struPDCAlarmInfo.struDevInfo.byChannel,
            struPDCAlarmInfo.struDevInfo.byIvmsChannel, struPDCAlarmInfo.wDevInfoIvmsChannelEx,
            struPDCAlarmInfo.byChannel, struPDCAlarmInfo.dwLeaveNum, struPDCAlarmInfo.dwEnterNum, struPDCAlarmInfo.dwPassingNum, struPDCAlarmInfo.bySmart, struPDCAlarmInfo.byBrokenNetHttp);//2014-03-21
    }
    else if (struPDCAlarmInfo.byMode == 1 || struPDCAlarmInfo.byMode == 2)
    {
        sprintf(szInfoBuf, "DevIP:[%s]Port[%d]Channel[%d]:time range:Start Y[%d]M[%d]D[%d]H[%d]M[%d]S[%d] flag[%d] [%2.2d%2.2d]  End Y[%d]M[%d]D[%d]H[%d]M[%d]S[%d] [%2.2d%2.2d]IvmsChannel[%d]IvmsChannelEx[%d]Channel[%d]LeaveNum[%d]EnterNum[%d]Passing[%d]Smart[%d]BrokenNetHttp[%d]Mode[%d]", 
            struPDCAlarmInfo.struDevInfo.struDevIP.sIpV4, struPDCAlarmInfo.struDevInfo.wPort, struPDCAlarmInfo.struDevInfo.byChannel,
            struPDCAlarmInfo.uStatModeParam.struStatTime.tmStart.dwYear,struPDCAlarmInfo.uStatModeParam.struStatTime.tmStart.dwMonth,struPDCAlarmInfo.uStatModeParam.struStatTime.tmStart.dwDay,
            struPDCAlarmInfo.uStatModeParam.struStatTime.tmStart.dwHour,struPDCAlarmInfo.uStatModeParam.struStatTime.tmStart.dwMinute,struPDCAlarmInfo.uStatModeParam.struStatTime.tmStart.dwSecond,
            struPDCAlarmInfo.uStatModeParam.struStatTime.byTimeDifferenceFlag, struPDCAlarmInfo.uStatModeParam.struStatTime.cStartTimeDifferenceH, struPDCAlarmInfo.uStatModeParam.struStatTime.cStartTimeDifferenceM,
            struPDCAlarmInfo.uStatModeParam.struStatTime.tmEnd.dwYear,struPDCAlarmInfo.uStatModeParam.struStatTime.tmEnd.dwMonth,struPDCAlarmInfo.uStatModeParam.struStatTime.tmEnd.dwDay,
            struPDCAlarmInfo.uStatModeParam.struStatTime.tmEnd.dwHour,struPDCAlarmInfo.uStatModeParam.struStatTime.tmEnd.dwMinute,struPDCAlarmInfo.uStatModeParam.struStatTime.tmEnd.dwSecond,
            struPDCAlarmInfo.uStatModeParam.struStatTime.cStopTimeDifferenceH, struPDCAlarmInfo.uStatModeParam.struStatTime.cStopTimeDifferenceM,
            struPDCAlarmInfo.struDevInfo.byIvmsChannel, struPDCAlarmInfo.wDevInfoIvmsChannelEx,
            struPDCAlarmInfo.byChannel, struPDCAlarmInfo.dwLeaveNum, struPDCAlarmInfo.dwEnterNum, struPDCAlarmInfo.dwPassingNum, struPDCAlarmInfo.bySmart, struPDCAlarmInfo.byBrokenNetHttp, struPDCAlarmInfo.byMode);//2014-03-21
    }
    g_pMainDlg->AddLog(iDeviceIndex,ALARM_INFO_T,szInfoBuf);
	
}

/*********************************************************
Function:	ProcRuleAlarm
Desc:		process behavior alarm information
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::ProcRuleAlarm(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iWinIndex = -1;         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
    if (iDeviceIndex > 512)
    {
        return;
    }
    NET_VCA_RULE_ALARM  struVcaRuleAlarm;
	CTime time = CTime::GetCurrentTime();
	memcpy(&struVcaRuleAlarm, pAlarmInfo, sizeof(NET_VCA_RULE_ALARM));
	i = struVcaRuleAlarm.struDevInfo.byIvmsChannel-g_struDeviceInfo[iDeviceIndex].iStartChan;
	g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));	

    char szAlarmBufEx[64] = { 0 };
    switch(struVcaRuleAlarm.struRuleInfo.wEventTypeEx)
    {
    case ENUM_VCA_EVENT_TRAVERSE_PLANE:
        sprintf(szAlarmBufEx, "traverse plane detection byDetectionTarget[%d]", struVcaRuleAlarm.struRuleInfo.uEventParam.struTraversePlane.byDetectionTarget);
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szAlarmBufEx);
        break;
    case ENUM_VCA_EVENT_INTRUSION:
        sprintf(szAlarmBufEx, "field detection byDetectionTarget[%d]", struVcaRuleAlarm.struRuleInfo.uEventParam.struIntrusion.byDetectionTarget);
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szAlarmBufEx);
        break;
    case ENUM_VCA_EVENT_ENTER_AREA:
        sprintf(szAlarmBufEx, "enter area detection byDetectionTarget[%d]", struVcaRuleAlarm.struRuleInfo.uEventParam.struArea.byDetectionTarget);
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szAlarmBufEx);
        break;
    case ENUM_VCA_EVENT_EXIT_AREA:
        sprintf(szAlarmBufEx, "exit area detection byDetectionTarget[%d]", struVcaRuleAlarm.struRuleInfo.uEventParam.struArea.byDetectionTarget);
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szAlarmBufEx);
        break;

    default:
        break;
    
    }


    NET_DVR_TIME struAbsTime = { 0 };
    struAbsTime.dwYear = GET_YEAR(struVcaRuleAlarm.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struVcaRuleAlarm.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struVcaRuleAlarm.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struVcaRuleAlarm.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struVcaRuleAlarm.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struVcaRuleAlarm.dwAbsTime);

    NET_DVR_TIME struRelativeTime = { 0 };
    struRelativeTime.dwYear = GET_YEAR(struVcaRuleAlarm.dwRelativeTime);
    struRelativeTime.dwMonth = GET_MONTH(struVcaRuleAlarm.dwRelativeTime);
    struRelativeTime.dwDay = GET_DAY(struVcaRuleAlarm.dwRelativeTime);
    struRelativeTime.dwHour = GET_HOUR(struVcaRuleAlarm.dwRelativeTime);
    struRelativeTime.dwMinute = GET_MINUTE(struVcaRuleAlarm.dwRelativeTime);
    struRelativeTime.dwSecond = GET_SECOND(struVcaRuleAlarm.dwRelativeTime);

    char szTime[128] = {0};
    sprintf(szTime, "VCA Alarm time flag[%d] Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] relative[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]", struVcaRuleAlarm.byRelativeTimeFlag,
        struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond, 
        struRelativeTime.dwYear, struRelativeTime.dwMonth, struRelativeTime.dwDay, struRelativeTime.dwHour, struRelativeTime.dwMinute, struRelativeTime.dwSecond);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szTime);


    char csRuleName[33] = {0};
    memcpy(csRuleName, struVcaRuleAlarm.struRuleInfo.byRuleName, 32);
	//行为分析结果上报结构
    sprintf(szInfoBuf, "Smart:[%d] DevIP:[%s]TargetID[%d]RuleID[%d]RuleName[%s]AbsTime[%d]piclen[%d]PicType[%d]RelAlarmPicNum[%d]AlarmID[%d]IvmsChannel[%d]IvmsChannelEx[%d]EventTypeEx[%d]byPicTransType[%d]RECT[X:%f][Y:%f][H:%f][W:%f]",
        struVcaRuleAlarm.bySmart,
		struVcaRuleAlarm.struDevInfo.struDevIP.sIpV4,struVcaRuleAlarm.struTargetInfo.dwID,
        struVcaRuleAlarm.struRuleInfo.byRuleID, csRuleName,
		struVcaRuleAlarm.dwAbsTime, struVcaRuleAlarm.dwPicDataLen, struVcaRuleAlarm.byPicType,struVcaRuleAlarm.byRelAlarmPicNum,struVcaRuleAlarm.dwAlarmID,
        struVcaRuleAlarm.struDevInfo.byIvmsChannel, struVcaRuleAlarm.wDevInfoIvmsChannelEx,\
        struVcaRuleAlarm.struRuleInfo.wEventTypeEx, struVcaRuleAlarm.byPicTransType, struVcaRuleAlarm.struTargetInfo.struRect.fX, struVcaRuleAlarm.struTargetInfo.struRect.fY, struVcaRuleAlarm.struTargetInfo.struRect.fHeight, struVcaRuleAlarm.struTargetInfo.struRect.fWidth);
    g_pMainDlg->AddLog(iDeviceIndex,ALARM_INFO_T,szInfoBuf);
	
	
	NET_VCA_DEV_INFO tmpDevInfo;
	memcpy(&tmpDevInfo, &struVcaRuleAlarm.struDevInfo, sizeof(NET_VCA_DEV_INFO));
	sprintf(szInfoBuf,"\nNET_VCA_DEV_INFO:DevIP[%s]Port[%d]Channel[%d]\n",
		tmpDevInfo.struDevIP.sIpV4, tmpDevInfo.wPort, tmpDevInfo.byChannel);
	OutputDebugString(szInfoBuf);
	
	NET_VCA_TARGET_INFO tmpTargetInfo;
	memcpy(&tmpTargetInfo, &struVcaRuleAlarm.struTargetInfo, sizeof(NET_VCA_TARGET_INFO));
	sprintf(szInfoBuf, "NET_VCA_TARGET_INFO:ID[%d]RECT[%f][%f][%f][%f]\n",
		tmpTargetInfo.dwID, tmpTargetInfo.struRect.fX, tmpTargetInfo.struRect.fY,
		tmpTargetInfo.struRect.fWidth, tmpTargetInfo.struRect.fHeight);
	OutputDebugString(szInfoBuf);
	
	
	switch (struVcaRuleAlarm.struRuleInfo.wEventTypeEx)
	{
		
	case ENUM_VCA_EVENT_TRAVERSE_PLANE://
		{
			sprintf(szInfoBuf,"ENUM_VCA_EVENT_TRAVERSE_PLANE:struRul:start[%f][%f]end[%f][%f]\ndwCrossDirection:[%d]bySensitivity[%d]\n"
				,struVcaRuleAlarm.struRuleInfo.uEventParam.struTraversePlane.struPlaneBottom.struStart.fX,
				struVcaRuleAlarm.struRuleInfo.uEventParam.struTraversePlane.struPlaneBottom.struStart.fY,
				struVcaRuleAlarm.struRuleInfo.uEventParam.struTraversePlane.struPlaneBottom.struEnd.fX,
				struVcaRuleAlarm.struRuleInfo.uEventParam.struTraversePlane.struPlaneBottom.struEnd.fY,
				struVcaRuleAlarm.struRuleInfo.uEventParam.struTraversePlane.dwCrossDirection/*,
				struVcaRuleAlarm.struRuleInfo.uEventParam.struTraversePlane.bySensitivity*/);
				OutputDebugString(szInfoBuf);
		}
		break;
	case ENUM_VCA_EVENT_ENTER_AREA:
		{
			// 			sprintf(szInfoBuf,"VCA_ENTER_AREA:Senetity[%d]\nNET_VCA_POLYGON",struVcaRuleAlarm.struRuleInfo.uEventParam.struArea.bySensitivity);
			// 			OutputDebugString(szInfoBuf);
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struArea.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				sprintf(szInfoBuf,"[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				OutputDebugString(szInfoBuf);
			}
			
			
		}
		break;
	case ENUM_VCA_EVENT_EXIT_AREA:
		{
			// 			sprintf(szInfoBuf,"VCA_EXIT_AREA:Senetity[%d]\nNET_VCA_POLYGON",struVcaRuleAlarm.struRuleInfo.uEventParam.struArea.bySensitivity);
			// 			OutputDebugString(szInfoBuf);
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struArea.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				sprintf(szInfoBuf,"[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				OutputDebugString(szInfoBuf);
			}
			
		}
		break;
	case ENUM_VCA_EVENT_INTRUSION:
		{
			// 			sprintf(szInfoBuf,"VCA_INTRUSION:Sensitivity[%d]\nNET_VCA_POLYGON",
			// 				struVcaRuleAlarm.struRuleInfo.uEventParam.struIntrusion.bySensitivity);
			// 			OutputDebugString(szInfoBuf);
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struIntrusion.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				sprintf(szInfoBuf,"[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				OutputDebugString(szInfoBuf);
			}
			
		}
		break;
	case ENUM_VCA_EVENT_LOITER:
		{
			// 			sprintf(szInfoBuf,"VCA_LOITER:Senetity[%d]\nNET_VCA_POLYGON",
			// 				struVcaRuleAlarm.struRuleInfo.uEventParam.struLoiter.bySensitivity);
			// 			OutputDebugString(szInfoBuf);
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struLoiter.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				sprintf(szInfoBuf,"[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				OutputDebugString(szInfoBuf);
			}
			
		}
		break;
	case ENUM_VCA_EVENT_LEFT_TAKE:
		{
			// 			sprintf(szInfoBuf,"VCA_LEFT_TAKE:Senetity[%d]\nNET_VCA_POLYGON",
			// 				struVcaRuleAlarm.struRuleInfo.uEventParam.struTakeTeft.bySensitivity);
			// 			OutputDebugString(szInfoBuf);
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struTakeTeft.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				sprintf(szInfoBuf,"[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				OutputDebugString(szInfoBuf);
			}
			
		}
		break;
	case ENUM_VCA_EVENT_PARKING:
		{
			// 			sprintf(szInfoBuf,"VCA_PARKING:Senetity[%d]\nNET_VCA_POLYGON",
			// 				struVcaRuleAlarm.struRuleInfo.uEventParam.struParking.bySensitivity);
			// 			OutputDebugString(szInfoBuf);
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struParking.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				sprintf(szInfoBuf,"[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				OutputDebugString(szInfoBuf);
			}
			
		}
		break;
	case ENUM_VCA_EVENT_RUN:
		{
			// 			sprintf(szInfoBuf,"VCA_RUN:Senetity[%d]\nNET_VCA_POLYGON",
			// 				struVcaRuleAlarm.struRuleInfo.uEventParam.struRun.bySensitivity);
			// 			OutputDebugString(szInfoBuf);
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struRun.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				sprintf(szInfoBuf,"[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				OutputDebugString(szInfoBuf);
			}
		}
		break;
	case ENUM_VCA_EVENT_HIGH_DENSITY:
		{
			// 			sprintf(szInfoBuf,"VCA_HIGH_DENSITY:Senetity[%d]\nNET_VCA_POLYGON",
			// 				struVcaRuleAlarm.struRuleInfo.uEventParam.struHighDensity.bySensitivity);
			// 			OutputDebugString(szInfoBuf);
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struHighDensity.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				sprintf(szInfoBuf,"[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				OutputDebugString(szInfoBuf);
			}
			
		}
		break;
	case ENUM_VCA_EVENT_LECTURE:
	case VCA_LECTURE:
		{
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struLecture.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				if (struVcaRuleAlarm.struRuleInfo.uEventParam.struLecture.byAlarmState == 1)
				{
					sprintf(szInfoBuf,"Lecture  Event Start[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);	
				}
				else if (struVcaRuleAlarm.struRuleInfo.uEventParam.struLecture.byAlarmState == 2)
				{
					sprintf(szInfoBuf,"Lecture  Event End[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				}
				
                sprintf(szInfoBuf, "%s ZoomOver[%d]", szInfoBuf, struVcaRuleAlarm.struRuleInfo.uEventParam.struLecture.byZoomOver);
				OutputDebugString(szInfoBuf);
				g_pMainDlg->AddLog(iDeviceIndex,ALARM_INFO_T,szInfoBuf);
			}
			
		}
		break;
	case ENUM_VCA_EVENT_ANSWER:
	case VCA_ANSWER:
		{
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struAnswer.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				if (struVcaRuleAlarm.struRuleInfo.uEventParam.struAnswer.byAlarmState == 1)
				{
					sprintf(szInfoBuf,"Answering Questions Event [%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				}
				else if(struVcaRuleAlarm.struRuleInfo.uEventParam.struAnswer.byAlarmState == 2)
				{
					sprintf(szInfoBuf,"Answering Questions Event [%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				}

                sprintf(szInfoBuf, "%s ZoomOver[%d] AnswerStudent[%d]", szInfoBuf, struVcaRuleAlarm.struRuleInfo.uEventParam.struAnswer.byZoomOver, struVcaRuleAlarm.struRuleInfo.uEventParam.struAnswer.byAnswerStudent);
				OutputDebugString(szInfoBuf);
				g_pMainDlg->AddLog(iDeviceIndex,ALARM_INFO_T,szInfoBuf);
			}
			
		}
		break;
	case ENUM_VCA_EVENT_COMBINED_RULE:
		{
			sprintf(szInfoBuf, "Combined Rule, RuleSequence[%d] MinInterval[%d] MaxInterval[%d] RuleID1[%d] RuleID2[%d]", struVcaRuleAlarm.struRuleInfo.uEventParam.struCombinedRule.byRuleSequence,\
				struVcaRuleAlarm.struRuleInfo.uEventParam.struCombinedRule.dwMinInterval, struVcaRuleAlarm.struRuleInfo.uEventParam.struCombinedRule.dwMaxInterval, \
				struVcaRuleAlarm.struRuleInfo.uEventParam.struCombinedRule.struRule1Raram.byRuleID, struVcaRuleAlarm.struRuleInfo.uEventParam.struCombinedRule.struRule2Raram.byRuleID);
			OutputDebugString(szInfoBuf);
			g_pMainDlg->AddLog(iDeviceIndex,ALARM_INFO_T,szInfoBuf);
		}
		break;
	case ENUM_VCA_EVENT_HIGH_DENSITY_STATUS:
		{
			// 			sprintf(szInfoBuf,"VCA_HIGH_DENSITY:Senetity[%d]\nNET_VCA_POLYGON",
			// 				struVcaRuleAlarm.struRuleInfo.uEventParam.struHighDensity.bySensitivity);
			// 			OutputDebugString(szInfoBuf);
			NET_VCA_POLYGON tempPolygon;
			memcpy(&tempPolygon,&struVcaRuleAlarm.struRuleInfo.uEventParam.struHighDensityStatus.struRegion,sizeof(NET_VCA_POLYGON));
			
			for (i = 0; i < (int)tempPolygon.dwPointNum ;i ++)
			{
				sprintf(szInfoBuf,"[%f][%f]",tempPolygon.struPos[i].fX,tempPolygon.struPos[i].fY);
				OutputDebugString(szInfoBuf);
			}
		}
		break;
	default:
		break;
	}

    int appendnum = 0;
	if (struVcaRuleAlarm.dwPicDataLen > 0 && struVcaRuleAlarm.pImage != NULL)
	{
		int num = ulAlarmPic/1000+1;
        appendnum = num;
		ulAlarmPic++;
		
		char cFilename[256] = {0};
		HANDLE hFile;
		DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
		
		sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
        
        if (struVcaRuleAlarm.byPicTransType)
        {
            sprintf(cFilename, "%s\\LocalTime[%s]TargetID[%d]RuleName[%s]AlarmID[%d]_%d.txt", cFilename, chTime, \
                struVcaRuleAlarm.struTargetInfo.dwID, csRuleName, struVcaRuleAlarm.dwAlarmID, rand() % GetTickCount());
        }
        else
        {
            sprintf(cFilename, "%s\\LocalTime[%s]TargetID[%d]RuleName[%s]AlarmID[%d]_%d.jpg", cFilename, chTime, \
                struVcaRuleAlarm.struTargetInfo.dwID, csRuleName, struVcaRuleAlarm.dwAlarmID, rand() % GetTickCount());
        }

		hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		WriteFile(hFile, struVcaRuleAlarm.pImage, struVcaRuleAlarm.dwPicDataLen, &dwReturn, NULL);
		CloseHandle(hFile);
		hFile = NULL;
	}

    if (struVcaRuleAlarm.byAppendInfoUploadEnabled==1)
    {
        NET_VCA_APPEND_INFO struAppendInfo = { 0 };
        memset(&struAppendInfo, 0, sizeof(struAppendInfo));
        memcpy(&struAppendInfo, struVcaRuleAlarm.pAppendInfo, sizeof(struAppendInfo));

        sprintf(szInfoBuf, "append info:append pic type[%d];append pic len[%d]",
            struAppendInfo.byAppendPicType, struAppendInfo.dwAppendPicLen);
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

        if (struAppendInfo.dwAppendPicLen>0 && struAppendInfo.pAppendPicBuff!=NULL)
        {
            char cFilename[256] = { 0 };
            HANDLE hFile;
            DWORD dwReturn;

            SYSTEMTIME t;
            GetLocalTime(&t);
            char chTime[128];
            sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

            sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, appendnum);
            if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFilename, NULL);
            }

            sprintf(cFilename, "%s\\LocalTime[%s]_appendPic.jpg", cFilename, chTime);

            hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return;
            }
            WriteFile(hFile, struAppendInfo.pAppendPicBuff, struAppendInfo.dwAppendPicLen, &dwReturn, NULL);
            CloseHandle(hFile);
            hFile = NULL;
        }

        if (struAppendInfo.pAppendPicBuff != NULL)
        {
            delete[](struAppendInfo.pAppendPicBuff);
        }
    }

	if (struVcaRuleAlarm.pImage != NULL)
	{
		delete [] (struVcaRuleAlarm.pImage);
	}  

    if (struVcaRuleAlarm.pAppendInfo != NULL)
    {
        delete[](struVcaRuleAlarm.pAppendInfo);
    }


}

void CClientDemoDlg::ProcAidAlarm(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iWinIndex = -1;         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_AID_ALARM  struAidAlarm = {0};
	CTime time = CTime::GetCurrentTime();
	memcpy(&struAidAlarm, pAlarmInfo, sizeof(struAidAlarm));
	i = struAidAlarm.struDevInfo.byIvmsChannel-g_struDeviceInfo[iDeviceIndex].iStartChan;
	g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));

    NET_DVR_TIME struAbsTime = {0};     
    struAbsTime.dwYear = GET_YEAR(struAidAlarm.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struAidAlarm.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struAidAlarm.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struAidAlarm.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struAidAlarm.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struAidAlarm.dwAbsTime);

    CString str = "";
    sprintf(szInfoBuf, "Aid Alarm IvmsChan[%d]ID[%d]Name[%s]Type[%d]Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]Dev IP[%s]Port[%d]Chan[%d] \
        Direction Start[%0.3f,%0.3f]Stop[%0.3f,%0.3f]", 
        struAidAlarm.struDevInfo.byIvmsChannel, struAidAlarm.struAIDInfo.byRuleID, struAidAlarm.struAIDInfo.byRuleName,
        struAidAlarm.struAIDInfo.dwAIDType, struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay,
        struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond, struAidAlarm.struDevInfo.struDevIP.sIpV4,
        struAidAlarm.struDevInfo.wPort, struAidAlarm.struDevInfo.byChannel,
        struAidAlarm.struAIDInfo.struDirect.struStartPoint.fX, struAidAlarm.struAIDInfo.struDirect.struStartPoint.fY,
        struAidAlarm.struAIDInfo.struDirect.struEndPoint.fX, struAidAlarm.struAIDInfo.struDirect.struEndPoint.fY);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

    if (struAidAlarm.dwPicDataLen > 0 && struAidAlarm.pImage != NULL)
	{
		int num = ulAlarmPic/1000+1;
		ulAlarmPic++;
		
		char cFilename[256] = {0};
		HANDLE hFile;
		DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
		
		sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
        
		sprintf(cFilename, "%s\\LocalTime[%s].jpg",cFilename, chTime);
		hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		WriteFile(hFile, struAidAlarm.pImage, struAidAlarm.dwPicDataLen, &dwReturn, NULL);
		CloseHandle(hFile);
		hFile = NULL;
	}
	if (struAidAlarm.pImage != NULL)
	{
		delete [] (struAidAlarm.pImage);
        struAidAlarm.pImage = NULL;
	}		
}

void CClientDemoDlg::ProcTpsAlarm(WPARAM wParam, LPARAM lParam)
{

    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iWinIndex = -1;
    unsigned int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    NET_DVR_TPS_ALARM struTpsAlarm = {0};
    memcpy(&struTpsAlarm, pAlarmInfo, sizeof(struTpsAlarm));
    i = struTpsAlarm.struDevInfo.byIvmsChannel - g_struDeviceInfo[iDeviceIndex].iStartChan;
    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
    ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
    
    NET_DVR_TIME  struAbsTime = {0};
    struAbsTime.dwYear = GET_YEAR(struTpsAlarm.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struTpsAlarm.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struTpsAlarm.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struTpsAlarm.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struTpsAlarm.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struTpsAlarm.dwAbsTime);
    
    sprintf(szInfoBuf, "Tps alarm Dev ip[%s]port[%d]Chan[%d] IvmsChan[%d] Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] LaneNum[%d]" , \
        struTpsAlarm.struDevInfo.struDevIP.sIpV4, struTpsAlarm.struDevInfo.wPort, struTpsAlarm.struDevInfo.byChannel,struTpsAlarm.struDevInfo.byIvmsChannel, 
        struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

    for (i = 0; i < struTpsAlarm.struTPSInfo.dwLanNum; i++)
    {
		sprintf(szInfoBuf, "ID[%d] Name[%s] VaryType[%d] LaneType[%d] Volume[%d] Velocity[%d] TimeHeadway[%d] SpaceHeadway[%d] SpceOccupy[%0.3f]",
            struTpsAlarm.struTPSInfo.struLaneParam[i].byRuleID, struTpsAlarm.struTPSInfo.struLaneParam[i].byRuleName,
            struTpsAlarm.struTPSInfo.struLaneParam[i].byVaryType, struTpsAlarm.struTPSInfo.struLaneParam[i].byLaneType,
            struTpsAlarm.struTPSInfo.struLaneParam[i].dwLaneVolume, struTpsAlarm.struTPSInfo.struLaneParam[i].dwLaneVelocity,
            struTpsAlarm.struTPSInfo.struLaneParam[i].dwTimeHeadway, struTpsAlarm.struTPSInfo.struLaneParam[i].dwSpaceHeadway,
            struTpsAlarm.struTPSInfo.struLaneParam[i].fSpaceOccupyRation);
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    }
}

void CClientDemoDlg::ProcTpsAlarmV41(WPARAM wParam,LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo  = (char *)(lParam);		
    int iWinIndex     = -1;
    int i             = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    if (iDeviceIndex < 0 || iDeviceIndex >= MAX_DEVICES)
    {
        return;
    }
	
    NET_DVR_TPS_ALARM_V41 struTpsAlarm = {0};
    memcpy(&struTpsAlarm, pAlarmInfo, sizeof(struTpsAlarm));
    i = struTpsAlarm.struDevInfo.byIvmsChannel - g_struDeviceInfo[iDeviceIndex].iStartChan;
    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
    ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
    
    NET_DVR_TIME  struAbsTime = {0};
    struAbsTime.dwYear   =  GET_YEAR(struTpsAlarm.dwAbsTime);
    struAbsTime.dwMonth  =  GET_MONTH(struTpsAlarm.dwAbsTime);
    struAbsTime.dwDay    =  GET_DAY(struTpsAlarm.dwAbsTime);
    struAbsTime.dwHour   =  GET_HOUR(struTpsAlarm.dwAbsTime);
    struAbsTime.dwMinute =  GET_MINUTE(struTpsAlarm.dwAbsTime);
    struAbsTime.dwSecond =  GET_SECOND(struTpsAlarm.dwAbsTime);

	NET_DVR_TIME  struStartTime = {0};
    struStartTime.dwYear   =  GET_YEAR(struTpsAlarm.dwStartTime);
    struStartTime.dwMonth  =  GET_MONTH(struTpsAlarm.dwStartTime);
    struStartTime.dwDay    =  GET_DAY(struTpsAlarm.dwStartTime);
    struStartTime.dwHour   =  GET_HOUR(struTpsAlarm.dwStartTime);
    struStartTime.dwMinute =  GET_MINUTE(struTpsAlarm.dwStartTime);
    struStartTime.dwSecond =  GET_SECOND(struTpsAlarm.dwStartTime);

	NET_DVR_TIME  struStopTime = {0};
    struStopTime.dwYear   =  GET_YEAR(struTpsAlarm.dwStopTime);
    struStopTime.dwMonth  =  GET_MONTH(struTpsAlarm.dwStopTime);
    struStopTime.dwDay    =  GET_DAY(struTpsAlarm.dwStopTime);
    struStopTime.dwHour   =  GET_HOUR(struTpsAlarm.dwStopTime);
    struStopTime.dwMinute =  GET_MINUTE(struTpsAlarm.dwStopTime);
    struStopTime.dwSecond =  GET_SECOND(struTpsAlarm.dwStopTime);

    
    sprintf(szInfoBuf, "Tps alarm v41 Dev ip[%s]port[%d]Chan[%d] IvmsChan[%d] Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] LaneNum[%d]SceneId[%d] MonitoringSiteID[%s] DeviceID[%s] StartTime[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] StopTime[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]" , \
        struTpsAlarm.struDevInfo.struDevIP.sIpV4, struTpsAlarm.struDevInfo.wPort, struTpsAlarm.struDevInfo.byChannel,struTpsAlarm.struDevInfo.byIvmsChannel, 
        struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond,struTpsAlarm.struTPSInfo.dwLanNum,
        struTpsAlarm.struTPSInfo.dwSceneID, struTpsAlarm.byMonitoringSiteID, struTpsAlarm.byDeviceID,
		struStartTime.dwYear, struStartTime.dwMonth, struStartTime.dwDay, struStartTime.dwHour, struStartTime.dwMinute, struStartTime.dwSecond,
		struStopTime.dwYear, struStopTime.dwMonth, struStopTime.dwDay, struStopTime.dwHour, struStopTime.dwMinute, struStopTime.dwSecond);
	
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
    for (i = 0; i < struTpsAlarm.struTPSInfo.dwLanNum; i++)
    {
        sprintf(szInfoBuf, "ID[%d] Name[%s] VaryType[%d] LaneType[%d] Volume[%d] Velocity[%d] TimeHeadway[%d] SpaceHeadway[%d] SpaceOccupy[%0.3f] \
			TimeOccupy[%.3f] LightVehicle[%d] MidVehicle[%d] HeavyVehicle[%d] OversizeVehicle[%d] TrafficState[%d] LaneQueueHead[%0.3f,%0.3f] LaneQueueTail[%0.3f,%0.3f]  \
			LaneQueueLength[%d] LaneNo[%d]",
            struTpsAlarm.struTPSInfo.struLaneParam[i].byRuleID, struTpsAlarm.struTPSInfo.struLaneParam[i].byRuleName,
            struTpsAlarm.struTPSInfo.struLaneParam[i].dwVaryType, struTpsAlarm.struTPSInfo.struLaneParam[i].byLaneType,
            struTpsAlarm.struTPSInfo.struLaneParam[i].dwLaneVolume, struTpsAlarm.struTPSInfo.struLaneParam[i].dwLaneVelocity,
            struTpsAlarm.struTPSInfo.struLaneParam[i].dwTimeHeadway, struTpsAlarm.struTPSInfo.struLaneParam[i].dwSpaceHeadway,
            struTpsAlarm.struTPSInfo.struLaneParam[i].fSpaceOccupyRation, struTpsAlarm.struTPSInfo.struLaneParam[i].fTimeOccupyRation,
			struTpsAlarm.struTPSInfo.struLaneParam[i].dwLightVehicle, struTpsAlarm.struTPSInfo.struLaneParam[i].dwMidVehicle,
			struTpsAlarm.struTPSInfo.struLaneParam[i].dwHeavyVehicle, struTpsAlarm.struTPSInfo.struLaneParam[i].dwOversizeVehicle,
			struTpsAlarm.struTPSInfo.struLaneParam[i].byTrafficState,
			struTpsAlarm.struTPSInfo.struLaneParam[i].struLaneQueue.struHead.fX,struTpsAlarm.struTPSInfo.struLaneParam[i].struLaneQueue.struHead.fY,
			struTpsAlarm.struTPSInfo.struLaneParam[i].struLaneQueue.struTail.fX,struTpsAlarm.struTPSInfo.struLaneParam[i].struLaneQueue.struTail.fY,
			struTpsAlarm.struTPSInfo.struLaneParam[i].struLaneQueue.dwLength,
			struTpsAlarm.struTPSInfo.struLaneParam[i].byLaneNo);
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    }
}


void CClientDemoDlg::ProcAidAlarmV41(WPARAM wParam,LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iWinIndex = -1;         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_AID_ALARM_V41  struAidAlarm = {0};
	CTime time = CTime::GetCurrentTime();
	memcpy(&struAidAlarm, pAlarmInfo, sizeof(struAidAlarm));
	i = struAidAlarm.struDevInfo.byIvmsChannel-g_struDeviceInfo[iDeviceIndex].iStartChan;
	g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
	
    NET_DVR_TIME struAbsTime = {0};     
    struAbsTime.dwYear   = GET_YEAR(struAidAlarm.dwAbsTime);
    struAbsTime.dwMonth  = GET_MONTH(struAidAlarm.dwAbsTime);
    struAbsTime.dwDay    = GET_DAY(struAidAlarm.dwAbsTime);
    struAbsTime.dwHour   = GET_HOUR(struAidAlarm.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struAidAlarm.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struAidAlarm.dwAbsTime);
	
    char szAIDType[32] = { 0 };
    if ((struAidAlarm.struAIDInfo.dwAIDType&ROADBLOCK) != 0)
    {
        g_StringLanType(szAIDType, "路障", "RoadBlock");
    }
    if ((struAidAlarm.struAIDInfo.dwAIDType&CONSTRUCTION) != 0)
    {
        char szAIDTypeTmp[32] = { 0 };
        g_StringLanType(szAIDTypeTmp, "施工", "Construction");
        sprintf(szAIDType, "%s%s", szAIDType, szAIDTypeTmp);
    }
    //重新拷贝，解决48个字节时，打印乱码的问题
    BYTE   tempMonitoringSiteID[MONITORSITE_ID_LEN + 1/*49*/] = { 0 };
    memcpy(tempMonitoringSiteID, struAidAlarm.byMonitoringSiteID, sizeof(struAidAlarm.byMonitoringSiteID));


	CString str = "";
    sprintf(szInfoBuf, "Aid AlarmV41 xmlLen[%d]IvmsChan[%d]ID[%d]Name[%s]Type[%d]newType[%s] LaneNo[%d] Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]Dev IP[%s]Port[%d]Chan[%d] \
        Direction Start[%0.3f,%0.3f]Stop[%0.3f,%0.3f] SceneID[%d] SceneName[%s] Direction[%d] PTZ[%d,%d,%d] MonitoringSiteID[%s] DeviceID[%s] VehicleEnterState[%d] State[%d] ParkingID[%s]", 
        struAidAlarm.dwXmlLen, struAidAlarm.struDevInfo.byIvmsChannel, struAidAlarm.struAIDInfo.byRuleID, struAidAlarm.struAIDInfo.byRuleName,
        struAidAlarm.struAIDInfo.dwAIDType, szAIDType, struAidAlarm.byLaneNo, struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay,
        struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond, struAidAlarm.struDevInfo.struDevIP.sIpV4,
        struAidAlarm.struDevInfo.wPort, struAidAlarm.struDevInfo.byChannel,
        struAidAlarm.struAIDInfo.struDirect.struStartPoint.fX, struAidAlarm.struAIDInfo.struDirect.struStartPoint.fY,
        struAidAlarm.struAIDInfo.struDirect.struEndPoint.fX, struAidAlarm.struAIDInfo.struDirect.struEndPoint.fY,
		struAidAlarm.struSceneInfo.dwSceneID,struAidAlarm.struSceneInfo.bySceneName,struAidAlarm.struSceneInfo.byDirection,
		struAidAlarm.struSceneInfo.struPtzPos.wPanPos,struAidAlarm.struSceneInfo.struPtzPos.wTiltPos,struAidAlarm.struSceneInfo.struPtzPos.wZoomPos,
        tempMonitoringSiteID, struAidAlarm.byDeviceID, struAidAlarm.struAIDInfo.byVehicleEnterState,
        struAidAlarm.struAIDInfo.byState, struAidAlarm.struAIDInfo.byParkingID);
	
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
    if (struAidAlarm.dwPicDataLen > 0 && struAidAlarm.pImage != NULL)
	{
		int num = ulAlarmPic/1000+1;
		ulAlarmPic++;
		
		char cFilename[256] = {0};
		HANDLE hFile;
		DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
		
		sprintf(cFilename, "%s\\AIDPic%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
        
		if (struAidAlarm.byDataType == 0)
		{
			sprintf(cFilename, "%s\\LocalTime[%s].jpg",cFilename, chTime);
		} 
		else if (struAidAlarm.byDataType == 1)
		{
			sprintf(cFilename, "%s\\URL_LocalTime[%s].txt",cFilename, chTime);
		}

		//sprintf(cFilename, "%s\\LocalTime[%s].jpg",cFilename, chTime);
		hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		WriteFile(hFile, struAidAlarm.pImage, struAidAlarm.dwPicDataLen, &dwReturn, NULL);
		CloseHandle(hFile);
		hFile = NULL;
	}

    if (struAidAlarm.dwXmlLen > 0 && struAidAlarm.pXmlBuf != NULL)
    {
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        char cFilename[256] = { 0 };
        HANDLE hFile;
        DWORD dwReturn;

        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

        sprintf(cFilename, "%s\\AIDXml%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\Xml[%s].txt", cFilename, chTime);

        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struAidAlarm.pXmlBuf, struAidAlarm.dwXmlLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }

	if (struAidAlarm.pImage != NULL)
	{
		delete [] (struAidAlarm.pImage);
        struAidAlarm.pImage = NULL;
	}		

    if (struAidAlarm.pXmlBuf != NULL)
    {
        delete[](struAidAlarm.pXmlBuf);
        struAidAlarm.pXmlBuf = NULL;
    }
}

void CClientDemoDlg::ProcTpsStatistics(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szInfoBuf[1024] = { 0 };
    NET_DVR_TPS_STATISTICS_INFO struTpsStatistics = { 0 };
    memcpy(&struTpsStatistics, pAlarmInfo, sizeof(struTpsStatistics));


    sprintf(szInfoBuf, "TPS Alarm CMD[%d]DeviceID[%d]TotalLaneNum[%d]DataLen[%d]StartTime[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d]SamplePeriod[%d]Chan[%d]", \
        struTpsStatistics.struTPSStatisticsInfo.byCMD, struTpsStatistics.struTPSStatisticsInfo.wDeviceID, \
        struTpsStatistics.struTPSStatisticsInfo.byTotalLaneNum, struTpsStatistics.struTPSStatisticsInfo.wDataLen, \
        struTpsStatistics.struTPSStatisticsInfo.struStartTime.wYear, struTpsStatistics.struTPSStatisticsInfo.struStartTime.byMonth, \
        struTpsStatistics.struTPSStatisticsInfo.struStartTime.byDay, struTpsStatistics.struTPSStatisticsInfo.struStartTime.byHour, \
        struTpsStatistics.struTPSStatisticsInfo.struStartTime.byMinute, struTpsStatistics.struTPSStatisticsInfo.struStartTime.bySecond, \
        struTpsStatistics.struTPSStatisticsInfo.struStartTime.wMilliSec, struTpsStatistics.struTPSStatisticsInfo.dwSamplePeriod, struTpsStatistics.dwChan);
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    for (int i = 0; i < struTpsStatistics.struTPSStatisticsInfo.byTotalLaneNum; i++)
    {
        sprintf(szInfoBuf, "LaneNum[%d](Lane[%d]Speed[%d]LightVehicle[%d]MidVehicle[%d]HeavyVehicle[%d]TimeHeadway[%d]SpaceHeadway[%d]SpaceOccupyRation[%0.3f]TimeOccupyRation[%0.3f])",
            (i + 1), struTpsStatistics.struTPSStatisticsInfo.struLaneParam[i].byLane, struTpsStatistics.struTPSStatisticsInfo.struLaneParam[i].bySpeed,\
            struTpsStatistics.struTPSStatisticsInfo.struLaneParam[i].dwLightVehicle, struTpsStatistics.struTPSStatisticsInfo.struLaneParam[i].dwMidVehicle,\
            struTpsStatistics.struTPSStatisticsInfo.struLaneParam[i].dwHeavyVehicle, struTpsStatistics.struTPSStatisticsInfo.struLaneParam[i].dwTimeHeadway,\
            struTpsStatistics.struTPSStatisticsInfo.struLaneParam[i].dwSpaceHeadway, struTpsStatistics.struTPSStatisticsInfo.struLaneParam[i].fSpaceOccupyRation,\
            struTpsStatistics.struTPSStatisticsInfo.struLaneParam[i].fTimeOccupyRation);
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    }
    return;
}

void CClientDemoDlg::ProcTpsRealtime(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szInfoBuf[1024] = { 0 };
    NET_DVR_TPS_REAL_TIME_INFO struTpsRealtime = { 0 };
    memcpy(&struTpsRealtime, pAlarmInfo, sizeof(struTpsRealtime));

    sprintf(szInfoBuf, "TPS Real Time Alarm Channel[%d]Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d]Start[%d]CMD[%d]DeviceID[%d]DataLen[%d]Lane[%d] \
                      Speed[%d]LaneState[%d]QueueLen[%d]LoopState[%d]StateMask[%d]DownwardFlow[%d]UpwardFlow[%d]JamLevel[%d]", \
        struTpsRealtime.dwChan, \
        struTpsRealtime.struTime.wYear, struTpsRealtime.struTime.byMonth, struTpsRealtime.struTime.byDay, \
        struTpsRealtime.struTime.byHour, struTpsRealtime.struTime.byMinute, struTpsRealtime.struTime.bySecond, \
        struTpsRealtime.struTime.wMilliSec, struTpsRealtime.struTPSRealTimeInfo.byStart, \
        struTpsRealtime.struTPSRealTimeInfo.byCMD, struTpsRealtime.struTPSRealTimeInfo.wDeviceID, \
        struTpsRealtime.struTPSRealTimeInfo.wDataLen, struTpsRealtime.struTPSRealTimeInfo.byLane, \
        struTpsRealtime.struTPSRealTimeInfo.bySpeed, struTpsRealtime.struTPSRealTimeInfo.byLaneState, \
        struTpsRealtime.struTPSRealTimeInfo.byQueueLen, struTpsRealtime.struTPSRealTimeInfo.wLoopState, \
        struTpsRealtime.struTPSRealTimeInfo.wStateMask, struTpsRealtime.struTPSRealTimeInfo.dwDownwardFlow, \
        struTpsRealtime.struTPSRealTimeInfo.dwUpwardFlow, struTpsRealtime.struTPSRealTimeInfo.byJamLevel);
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    return;
}

void CClientDemoDlg::ProcTfsAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[2048] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iWinIndex = -1;
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    NET_DVR_TFS_ALARM struTfsAlarm = { 0 };
    memcpy(&struTfsAlarm, pAlarmInfo, sizeof(struTfsAlarm));
    i = struTfsAlarm.struDevInfo.byIvmsChannel - g_struDeviceInfo[iDeviceIndex].iStartChan;
    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
    ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));

    NET_DVR_TIME struAbsTime = { 0 };
    struAbsTime.dwYear = GET_YEAR(struTfsAlarm.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struTfsAlarm.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struTfsAlarm.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struTfsAlarm.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struTfsAlarm.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struTfsAlarm.dwAbsTime);

    CString str = "";

    char chTfsTime[128] = { 0 };
    sprintf(chTfsTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", struTfsAlarm.struTime.wYear, struTfsAlarm.struTime.byMonth, struTfsAlarm.struTime.byDay, \
        struTfsAlarm.struTime.byHour, struTfsAlarm.struTime.byMinute, struTfsAlarm.struTime.bySecond, struTfsAlarm.struTime.wMilliSec);

    //重新拷贝，解决48个字节时，打印乱码的问题
    BYTE   tempMonitoringSiteID[MONITORSITE_ID_LEN + 1/*49*/] = { 0 };
    memcpy(tempMonitoringSiteID, struTfsAlarm.byMonitoringSiteID, sizeof(struTfsAlarm.byMonitoringSiteID));

    sprintf(szInfoBuf, "Tfs Alarm IvmsChan: [%d]\r\nID: [%d]\r\nName: [%s]\r\nType: [%d]\r\nAbs: [%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]\r\nDevIP: [%s]\r\nPort: [%d]\r\nChan: [%d]\r\nSpecificVehicleType: [%d]\
            \r\nLaneNo: [%d]\r\nDirection Start: [%0.3f,%0.3f]\r\nStop: [%0.3f,%0.3f]\r\nSceneID: [%d]\r\nSceneName: [%s]\r\nDirection: [%d]\r\nPTZ: [%d,%d,%d]\r\nIllegalType: [%u]\r\nIllegalTime: [%d]\r\nMonitorSiteID: [%s]\
            \r\nDeviceID: [%s]\r\nLicence: [%s]\r\nBelieve: [%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u]\r\nTime: [%s]\r\nSerialNo: [%d]\r\nVehicleAttribute: [%d]\r\nPilotSafebelt: [%d]\r\nCopilotSafebelt: [%d]\
            \r\nPilotSunVisor: [%d]\r\nCopilotSunVisor: [%d]\r\nPilotCall: [%d]\r\nIllegalCode: [%s]\r\nVehicleEnterState: [%d]\r\nCountry: [%d]\r\nRegion: [%d]\r\nState:[%d]\r\nParkingID:[%s]\r\nCrossLine:[%d]\r\nParkingCrossLine:[%s]\
            \r\nCrossSpaces:[%d]AngledParking:[%d]\r\nAlarmValidity:[%d]",
            struTfsAlarm.struDevInfo.byIvmsChannel, struTfsAlarm.struAIDInfo.byRuleID, struTfsAlarm.struAIDInfo.byRuleName,
            struTfsAlarm.struAIDInfo.dwAIDType, struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay,
            struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond, struTfsAlarm.struDevInfo.struDevIP.sIpV4,
            struTfsAlarm.struDevInfo.wPort, struTfsAlarm.struDevInfo.byChannel, struTfsAlarm.bySpecificVehicleType,
            struTfsAlarm.byLaneNo, struTfsAlarm.struAIDInfo.struDirect.struStartPoint.fX, struTfsAlarm.struAIDInfo.struDirect.struStartPoint.fY,
            struTfsAlarm.struAIDInfo.struDirect.struEndPoint.fX, struTfsAlarm.struAIDInfo.struDirect.struEndPoint.fY,
            struTfsAlarm.struSceneInfo.dwSceneID, struTfsAlarm.struSceneInfo.bySceneName, struTfsAlarm.struSceneInfo.byDirection,
            struTfsAlarm.struSceneInfo.struPtzPos.wPanPos, struTfsAlarm.struSceneInfo.struPtzPos.wTiltPos, struTfsAlarm.struSceneInfo.struPtzPos.wZoomPos,
            struTfsAlarm.dwIllegalType, struTfsAlarm.dwIllegalDuration, tempMonitoringSiteID, struTfsAlarm.byDeviceID,
            struTfsAlarm.struPlateInfo.sLicense, struTfsAlarm.struPlateInfo.byBelieve[0], struTfsAlarm.struPlateInfo.byBelieve[1], struTfsAlarm.struPlateInfo.byBelieve[2], struTfsAlarm.struPlateInfo.byBelieve[3],
            struTfsAlarm.struPlateInfo.byBelieve[4], struTfsAlarm.struPlateInfo.byBelieve[5], struTfsAlarm.struPlateInfo.byBelieve[6], struTfsAlarm.struPlateInfo.byBelieve[7],
            struTfsAlarm.struPlateInfo.byBelieve[8], struTfsAlarm.struPlateInfo.byBelieve[9], struTfsAlarm.struPlateInfo.byBelieve[10], struTfsAlarm.struPlateInfo.byBelieve[11],
            struTfsAlarm.struPlateInfo.byBelieve[12], struTfsAlarm.struPlateInfo.byBelieve[13], struTfsAlarm.struPlateInfo.byBelieve[14], struTfsAlarm.struPlateInfo.byBelieve[15],
            chTfsTime, struTfsAlarm.dwSerialNo, struTfsAlarm.byVehicleAttribute, struTfsAlarm.byPilotSafebelt, struTfsAlarm.byCopilotSafebelt, struTfsAlarm.byPilotSunVisor,
            struTfsAlarm.byCopilotSunVisor, struTfsAlarm.byPilotCall, struTfsAlarm.byIllegalCode, struTfsAlarm.struAIDInfo.byVehicleEnterState, struTfsAlarm.wCountry,
            struTfsAlarm.byRegion, struTfsAlarm.struAIDInfo.byState, struTfsAlarm.struAIDInfo.byParkingID, struTfsAlarm.byCrossLine, struTfsAlarm.byParkingSerialNO, struTfsAlarm.byCrossSpaces, 
            struTfsAlarm.byAngledParking, struTfsAlarm.byAlarmValidity);
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char dataFilename[256] = { 0 };
    char chTime[128] = { 0 };
    char txtFilename[256] = { 0 };
    char cFilename[256] = { 0 };
    HANDLE hFile;
    DWORD dwReturn;

    int num = ulAlarmPic / 1000 + 1;
    ulAlarmPic++;

    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    sprintf(dataFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
    if (GetFileAttributes(dataFilename) != FILE_ATTRIBUTE_DIRECTORY)
    {
        CreateDirectory(dataFilename, NULL);
    }
    sprintf(txtFilename, "%s\\TfsAlarm_%s.txt", dataFilename, chTime);
    hFile = CreateFile(txtFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return;
    }
    WriteFile(hFile, szInfoBuf, sizeof(szInfoBuf) + 1, &dwReturn, NULL);
    CloseHandle(hFile);
    hFile = NULL;

    for (int i = 0; i < 8; i++)
    {
        if (struTfsAlarm.struPicInfo[i].dwDataLen > 0 && struTfsAlarm.struPicInfo[i].pBuffer != NULL)
        {

            char cPicType[256] = { 0 };
            if (struTfsAlarm.struPicInfo[i].byDataType == 0)
            {
                if (0 == struTfsAlarm.struPicInfo[i].byType)
                {
                    sprintf(cPicType, "License");
                }
                else if (1 == struTfsAlarm.struPicInfo[i].byType)
                {
                    sprintf(cPicType, "Scene");
                }
                sprintf(cFilename, "%s\\%s_LocalTime[%s]_%d.jpg", dataFilename, cPicType, chTime, i);
            }
            else if (struTfsAlarm.struPicInfo[i].byDataType == 1)
            {
                if (0 == struTfsAlarm.struPicInfo[i].byType)
                {
                    sprintf(cPicType, "License");
                }
                else if (1 == struTfsAlarm.struPicInfo[i].byType)
                {
                    sprintf(cPicType, "Scene");
                }
                sprintf(cFilename, "%s\\%s_URL_LocalTime[%s]_%d.txt", dataFilename, cPicType, chTime, i);
            }
            hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return;
            }
            WriteFile(hFile, struTfsAlarm.struPicInfo[i].pBuffer, struTfsAlarm.struPicInfo[i].dwDataLen + 1, &dwReturn, NULL);
            CloseHandle(hFile);
            hFile = NULL;
        }
    }
}

void CClientDemoDlg::ProcFaceDetectAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    const char *szFaceType[] = { "abn", "nor", "mul", "sgl", "cal" };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_FACEDETECT_ALARM struFaceDetectAlarm = {0};
    memcpy(&struFaceDetectAlarm, pAlarmInfo, sizeof(struFaceDetectAlarm));
	
    int i = struFaceDetectAlarm.struDevInfo.byChannel - g_struDeviceInfo[iDeviceIndex].iStartChan;
    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
    ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
//  打印信息
    NET_DVR_TIME  struAbsTime = {0};
    struAbsTime.dwYear = GET_YEAR(struFaceDetectAlarm.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struFaceDetectAlarm.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struFaceDetectAlarm.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struFaceDetectAlarm.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struFaceDetectAlarm.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struFaceDetectAlarm.dwAbsTime);
	
    sprintf(szInfoBuf, "Face alarm Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] RuleName[%s] AlarmPicType[%d] PanelChan[%d] RelAlarmPicNum[%d] AlarmID[%d] IvmsChannel[%d]IvmsChannelEx[%d]",
        struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour,
        struAbsTime.dwMinute, struAbsTime.dwSecond, struFaceDetectAlarm.byRuleName,struFaceDetectAlarm.byAlarmPicType,struFaceDetectAlarm.byPanelChan,
		struFaceDetectAlarm.byRelAlarmPicNum,struFaceDetectAlarm.dwAlarmID,\
        struFaceDetectAlarm.struDevInfo.byIvmsChannel, struFaceDetectAlarm.wDevInfoIvmsChannelEx);
    AddLog(m_iCurDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
    if (struFaceDetectAlarm.dwPicDataLen > 0 && struFaceDetectAlarm.pImage != NULL)
    {
        int num = ulAlarmPic/1000+1;
        ulAlarmPic++;

        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];

        if (struFaceDetectAlarm.byAlarmPicType < 0 || struFaceDetectAlarm.byAlarmPicType > 4)
        {
            return;
        }

        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
        sprintf(cFilename, "%s\\LocalTime[%s]AlarmID[%d]_%d_%s.jpg", cFilename, chTime, struFaceDetectAlarm.dwAlarmID, rand() % GetTickCount(), szFaceType[struFaceDetectAlarm.byAlarmPicType]);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
		sprintf(cFilename, "%s\\LocalTime[%s]AlarmID[%d]_%d.jpg",cFilename, chTime,struFaceDetectAlarm.dwAlarmID,rand() % GetTickCount());
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceDetectAlarm.pImage, struFaceDetectAlarm.dwPicDataLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
	}
	
	if (struFaceDetectAlarm.dwFacePicDataLen > 0 && struFaceDetectAlarm.pFaceImage != NULL)
    {
        int num = ulAlarmPic/1000+1;
        ulAlarmPic++;
        
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        if (struFaceDetectAlarm.byAlarmPicType < 0 || struFaceDetectAlarm.byAlarmPicType > 4)
        {
            return;
        }

        sprintf(cFilename, "%s\\Face_LocalTime[%s]AlarmID[%d]_%d_%s.jpg", cFilename, chTime, struFaceDetectAlarm.dwAlarmID, rand() % GetTickCount(), szFaceType[struFaceDetectAlarm.byAlarmPicType]);
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceDetectAlarm.pFaceImage, struFaceDetectAlarm.dwFacePicDataLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
	}
	
    if (struFaceDetectAlarm.pImage != NULL)
    {
        delete [] (struFaceDetectAlarm.pImage);
        struFaceDetectAlarm.pImage = NULL;
	}
	
	if (struFaceDetectAlarm.pFaceImage != NULL)
    {
        delete [] (struFaceDetectAlarm.pFaceImage);
        struFaceDetectAlarm.pFaceImage = NULL;
	}
}

void CClientDemoDlg::ProcFaceSnapAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_VCA_FACESNAP_RESULT struFaceSnapAlarm = {0};
    memcpy(&struFaceSnapAlarm, pAlarmInfo, sizeof(struFaceSnapAlarm));
	
    int i = struFaceSnapAlarm.struDevInfo.byChannel - g_struDeviceInfo[iDeviceIndex].iStartChan;
    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
    ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
	//  打印信息
    NET_DVR_TIME  struAbsTime = {0};
    struAbsTime.dwYear = GET_YEAR(struFaceSnapAlarm.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struFaceSnapAlarm.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struFaceSnapAlarm.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struFaceSnapAlarm.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struFaceSnapAlarm.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struFaceSnapAlarm.dwAbsTime);
    NET_VCA_FACESNAP_ADDINFO struFaceSnapAddInfo = { 0 };
    if (struFaceSnapAlarm.byAddInfo > 0 && struFaceSnapAlarm.pAddInfoBuffer != NULL)
    {
        memcpy(&struFaceSnapAddInfo, struFaceSnapAlarm.pAddInfoBuffer, sizeof(struFaceSnapAddInfo));
    }

    sprintf(szInfoBuf, "Face Snap alarm BrokenNetHttp[%d]Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d flag[%d] %2.2d%2.2d] FaceID[%d] Smart[%d] AgeGroup[%d] Sex[%d] EyeGlass[%d] \
                        StayDuration[%.3f] FaceScore[%d] AlarmEndMark[%d] RepeatTimes[%d]-StorageIP[%s] Storage Port[%d],IvmsChannel[%d]IvmsChannelEx[%d] \
                        Age[%d], AgeDeviation[%d] FacePicQuality[%d] UIDLen[%d] Ethnic[%d] Mask[%d] Smile[%d] AddInfo[%d] AddInfo:X[%.3f] Y[%.3f] Height[%.3f] Width[%.3f] \
                        SwingAngle[%d] TiltAngle[%d] PupilDistance[%d] BlockingState[d]\n",
                        struFaceSnapAlarm.byBrokenNetHttp, struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond, \
        struFaceSnapAlarm.byTimeDiffFlag, struFaceSnapAlarm.cTimeDifferenceH, struFaceSnapAlarm.cTimeDifferenceM, \
                        struFaceSnapAlarm.dwFacePicID, struFaceSnapAlarm.bySmart, struFaceSnapAlarm.struFeature.byAgeGroup, struFaceSnapAlarm.struFeature.bySex, \
                        struFaceSnapAlarm.struFeature.byEyeGlass, struFaceSnapAlarm.fStayDuration, struFaceSnapAlarm.dwFaceScore, struFaceSnapAlarm.byAlarmEndMark, \
                        struFaceSnapAlarm.byRepeatTimes, struFaceSnapAlarm.sStorageIP, struFaceSnapAlarm.wStoragePort, \
                        struFaceSnapAlarm.struDevInfo.byIvmsChannel, struFaceSnapAlarm.wDevInfoIvmsChannelEx, struFaceSnapAlarm.struFeature.byAge, struFaceSnapAlarm.struFeature.byAgeDeviation, struFaceSnapAlarm.byFacePicQuality, struFaceSnapAlarm.byUIDLen, \
                        struFaceSnapAlarm.struFeature.byEthnic, struFaceSnapAlarm.struFeature.byMask, struFaceSnapAlarm.struFeature.bySmile, struFaceSnapAlarm.byAddInfo, struFaceSnapAddInfo.struFacePicRect.fX, struFaceSnapAddInfo.struFacePicRect.fY, \
                        struFaceSnapAddInfo.struFacePicRect.fHeight, struFaceSnapAddInfo.struFacePicRect.fWidth, struFaceSnapAddInfo.iSwingAngle, struFaceSnapAddInfo.iTiltAngle, struFaceSnapAddInfo.dwPupilDistance, struFaceSnapAddInfo.byBlockingState);
    AddLog(m_iCurDeviceIndex, ALARM_INFO_T, szInfoBuf);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    if (struFaceSnapAlarm.byUIDLen > 0 && struFaceSnapAlarm.pUIDBuffer != NULL)
    {

        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        char cFilename[256] = { 0 };
        HANDLE hFile;
        DWORD dwReturn;

        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        sprintf(cFilename, "%s\\SnapUID[%s].txt", cFilename, chTime);

        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceSnapAlarm.pUIDBuffer, struFaceSnapAlarm.byUIDLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }
	
    if (struFaceSnapAlarm.dwFacePicLen > 0 && struFaceSnapAlarm.pBuffer1 != NULL)
    {
        int num = ulAlarmPic/1000+1;
        ulAlarmPic++;
        
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
		if (struFaceSnapAlarm.byUploadEventDataType == 0)
		{
			sprintf(cFilename, "%s\\SnapPic[%s].jpg", cFilename, chTime);
		}
		else
		{
			sprintf(cFilename, "%s\\SnapURL[%s].txt", cFilename, chTime);
		}

        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceSnapAlarm.pBuffer1, struFaceSnapAlarm.dwFacePicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
	}
	
	if (struFaceSnapAlarm.dwBackgroundPicLen > 0 && struFaceSnapAlarm.pBuffer2 != NULL)
    {
        int num = ulAlarmPic/1000+1;
        ulAlarmPic++;
        
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
		if (struFaceSnapAlarm.byUploadEventDataType == 0)
		{
			sprintf(cFilename, "%s\\BackgroundPic[%s].jpg", cFilename, chTime);
		}
		else
		{
			sprintf(cFilename, "%s\\BackgroundPic[%s].txt", cFilename, chTime);
		}

        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceSnapAlarm.pBuffer2, struFaceSnapAlarm.dwBackgroundPicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
	}
}

void CClientDemoDlg::ProcFaceDetectionAlarm(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	char szPicFace[1024] = {0};
	//char *pPicFace = szPicFace;
	
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
	
	NET_DVR_FACE_DETECTION struFaceDetectionAlarm = {0};
    memcpy(&struFaceDetectionAlarm, pAlarmInfo, sizeof(struFaceDetectionAlarm));
	
	//  打印信息
    NET_DVR_TIME  struAbsTime = {0};
    struAbsTime.dwYear = GET_YEAR(struFaceDetectionAlarm.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struFaceDetectionAlarm.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struFaceDetectionAlarm.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struFaceDetectionAlarm.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struFaceDetectionAlarm.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struFaceDetectionAlarm.dwAbsTime);
	
	NET_DVR_TIME  struRelativeTime = {0};
    struRelativeTime.dwYear = GET_YEAR(struFaceDetectionAlarm.dwRelativeTime);
    struRelativeTime.dwMonth = GET_MONTH(struFaceDetectionAlarm.dwRelativeTime);
    struRelativeTime.dwDay = GET_DAY(struFaceDetectionAlarm.dwRelativeTime);
    struRelativeTime.dwHour = GET_HOUR(struFaceDetectionAlarm.dwRelativeTime);
    struRelativeTime.dwMinute = GET_MINUTE(struFaceDetectionAlarm.dwRelativeTime);
    struRelativeTime.dwSecond = GET_SECOND(struFaceDetectionAlarm.dwRelativeTime);
	
	for (int i = 0; i < MAX_FACE_PIC_NUM; i++)
	{
		if (struFaceDetectionAlarm.struFacePic[i].fHeight != 0 && \
			struFaceDetectionAlarm.struFacePic[i].fWidth != 0)
// 			struFaceDetectionAlarm.struFacePic[i].fX != 0 && \
// 			struFaceDetectionAlarm.struFacePic[i].fY != 0)
		{
			sprintf(szPicFace, "[Detection Face Snap alarm]facePic:%d fHeight:%f,fWidth:%f,fX:%f,fY:%f \n", i+1, \
				struFaceDetectionAlarm.struFacePic[i].fHeight,
				struFaceDetectionAlarm.struFacePic[i].fWidth,
				struFaceDetectionAlarm.struFacePic[i].fX,
				struFaceDetectionAlarm.struFacePic[i].fY);
			//pPicFace = pPicFace + strlen(pPicFace);
            AddLog(m_iCurDeviceIndex, ALARM_INFO_T, szPicFace);
		}
	}
	
    sprintf(szInfoBuf, "[Detection Face Snap alarm] Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d flag[%d] %2.2d%2.2d] RelativeTime[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] Dev[ip:%s,port:%d,ivmsChan:%d] IvmsChannelEx[%d] UploadEventDataType[%d] \n", \
        struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour,struAbsTime.dwMinute, struAbsTime.dwSecond, \
        struFaceDetectionAlarm.byTimeDiffFlag, struFaceDetectionAlarm.cTimeDifferenceH, struFaceDetectionAlarm.cTimeDifferenceM, \
		struRelativeTime.dwYear, struRelativeTime.dwMonth, struRelativeTime.dwDay, struRelativeTime.dwHour,struRelativeTime.dwMinute, struRelativeTime.dwSecond, \
		struFaceDetectionAlarm.struDevInfo.struDevIP.sIpV4, struFaceDetectionAlarm.struDevInfo.wPort, struFaceDetectionAlarm.struDevInfo.byIvmsChannel,\
        struFaceDetectionAlarm.wDevInfoIvmsChannelEx, struFaceDetectionAlarm.byUploadEventDataType/*szPicFace*/);
	
    AddLog(m_iCurDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
	if (struFaceDetectionAlarm.dwBackgroundPicLen > 0 && struFaceDetectionAlarm.pBackgroundPicpBuffer != NULL)
    {
        int num = ulAlarmPic/1000+1;
        ulAlarmPic++;
        
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
        sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP);
      //  sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        

        if (struFaceDetectionAlarm.byUploadEventDataType == 0)
        {
            sprintf(cFilename, "%s\\Face Detection BackGround Pic[%s].jpg", cFilename, chTime);
        }
        else
        {
            sprintf(cFilename, "%s\\Face Detection BackGround Pic[%s].txt", cFilename, chTime);
        }

        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            delete[](struFaceDetectionAlarm.pBackgroundPicpBuffer);
            struFaceDetectionAlarm.pBackgroundPicpBuffer = NULL;
            return;
        }
        WriteFile(hFile, struFaceDetectionAlarm.pBackgroundPicpBuffer, struFaceDetectionAlarm.dwBackgroundPicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
        delete[] (struFaceDetectionAlarm.pBackgroundPicpBuffer);
        struFaceDetectionAlarm.pBackgroundPicpBuffer = NULL;
	}
	
}

void CClientDemoDlg::ProcTargetLeftRegionAlarm(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	

	NET_DVR_TARGET_LEFT_REGION_ALARM struTargetLeftRegionAlarm = {0};
    memcpy(&struTargetLeftRegionAlarm, pAlarmInfo, sizeof(struTargetLeftRegionAlarm));

    NET_DVR_TIME  struAbsTime = {0};
    struAbsTime.dwYear = GET_YEAR(struTargetLeftRegionAlarm.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struTargetLeftRegionAlarm.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struTargetLeftRegionAlarm.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struTargetLeftRegionAlarm.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struTargetLeftRegionAlarm.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struTargetLeftRegionAlarm.dwAbsTime);
	
	NET_DVR_TIME  struRelativeTime = {0};
    struRelativeTime.dwYear = GET_YEAR(struTargetLeftRegionAlarm.dwRelativeTime);
    struRelativeTime.dwMonth = GET_MONTH(struTargetLeftRegionAlarm.dwRelativeTime);
    struRelativeTime.dwDay = GET_DAY(struTargetLeftRegionAlarm.dwRelativeTime);
    struRelativeTime.dwHour = GET_HOUR(struTargetLeftRegionAlarm.dwRelativeTime);
    struRelativeTime.dwMinute = GET_MINUTE(struTargetLeftRegionAlarm.dwRelativeTime);
    struRelativeTime.dwSecond = GET_SECOND(struTargetLeftRegionAlarm.dwRelativeTime);

	sprintf(szInfoBuf, "Target Left Region alarm Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] RelativeTime[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] Dev[ip:%s,port:%d,ivmsChan:%d] TargetType[%d] leftDirection[%d]\n",\
        struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour,struAbsTime.dwMinute, struAbsTime.dwSecond, \
		struRelativeTime.dwYear, struRelativeTime.dwMonth, struRelativeTime.dwDay, struRelativeTime.dwHour,struRelativeTime.dwMinute, struRelativeTime.dwSecond, \
		struTargetLeftRegionAlarm.struDevInfo.struDevIP.sIpV4, struTargetLeftRegionAlarm.struDevInfo.wPort, struTargetLeftRegionAlarm.struDevInfo.byIvmsChannel, \
		struTargetLeftRegionAlarm.byTargetType, struTargetLeftRegionAlarm.byLeftDirection);
	
    AddLog(m_iCurDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcFaceSnapMatchAlarm(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[2048] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_VCA_FACESNAP_MATCH_ALARM struFaceSnapMatchAlarm = {0};
    memcpy(&struFaceSnapMatchAlarm, pAlarmInfo, sizeof(struFaceSnapMatchAlarm));
	
	//  打印信息
    NET_DVR_TIME  struAbsTime = {0};
    struAbsTime.dwYear = GET_YEAR(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);

    if (struFaceSnapMatchAlarm.struSnapInfo.dwUIDLen > 0 && struFaceSnapMatchAlarm.struSnapInfo.pUIDBuffer != NULL)
    {
        FaceSnapMatchAlarmInfo(wParam, lParam);
        return;
    }
    char tempFDID[256] = {0};
    if (struFaceSnapMatchAlarm.struBlackListInfo.dwFDIDLen > 0 
        && struFaceSnapMatchAlarm.struBlackListInfo.dwFDIDLen < sizeof(tempFDID)
        && struFaceSnapMatchAlarm.struBlackListInfo.pFDID != NULL)
    {
        memcpy(tempFDID, struFaceSnapMatchAlarm.struBlackListInfo.pFDID, struFaceSnapMatchAlarm.struBlackListInfo.dwFDIDLen);
    }
    char temppID[256] = { 0 };
    if (struFaceSnapMatchAlarm.struBlackListInfo.dwPIDLen > 0 
        && struFaceSnapMatchAlarm.struBlackListInfo.dwPIDLen < sizeof(temppID)
        && struFaceSnapMatchAlarm.struBlackListInfo.pPID != NULL)
    {
        memcpy(temppID, struFaceSnapMatchAlarm.struBlackListInfo.pPID, struFaceSnapMatchAlarm.struBlackListInfo.dwPIDLen);
    }
    char tempFDDesc[256] = { 0 };
    if (struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwFDDescriptionLen > 0 
        && struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwFDDescriptionLen < sizeof(tempFDDesc)
        && struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.pFDDescriptionBuffer != NULL)
    {
        memcpy(tempFDDesc, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.pFDDescriptionBuffer, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwFDDescriptionLen);
    }
    string strFDDesc = UTF82ASCII(tempFDDesc);

    char tempFCAddition[256] = { 0 };
    if (struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwFCAdditionInfoLen > 0 
        && struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwFCAdditionInfoLen < sizeof(tempFCAddition)
        && struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.pFCAdditionInfoBuffer != NULL)
    {
        memcpy(tempFCAddition, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.pFCAdditionInfoBuffer, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwFCAdditionInfoLen);
    }


    string strFCAddition = UTF82ASCII(tempFCAddition);

    sprintf(szInfoBuf, "Face Snap Match alarm BrokenNetHttp[%d] Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d  diff[%2.2d%2.2d] FaceID[%d] BlackList ID[%d] StorageIP[%s]-StoragePort[%d] Sex[%d] Glasses[%d] Age[%d] FacePicQuality[%d]\
             StayDuration[%0.3f] MatchPicNum[%d] struRegion[%0.1f, %0.1f, %0.1f, %0.1f] PicTransType[%d]  FDID[%s]   PID[%s] FDDesc[%s] Similarity[%f]  ThresholdValue[%d]\
              ListType[%d] ContrastStatus[%d] ModelingStatus[%d] Mask[%d] Smile[%d] FCAddtion[%s] Ethnic[%d] LivenessDetectionStatus[%d] IsNoSaveFDPicture[%d]\n",
               struFaceSnapMatchAlarm.byBrokenNetHttp, struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour,
               struAbsTime.dwMinute, struAbsTime.dwSecond,         \
               struFaceSnapMatchAlarm.cTimeDifferenceH, struFaceSnapMatchAlarm.cTimeDifferenceM, \
               struFaceSnapMatchAlarm.struSnapInfo.dwSnapFacePicID, \
               struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwRegisterID, \
               struFaceSnapMatchAlarm.sStorageIP, struFaceSnapMatchAlarm.wStoragePort, \
               struFaceSnapMatchAlarm.struSnapInfo.bySex, struFaceSnapMatchAlarm.struSnapInfo.byGlasses, \
               struFaceSnapMatchAlarm.struSnapInfo.byAge, struFaceSnapMatchAlarm.struSnapInfo.byFacePicQuality, struFaceSnapMatchAlarm.struSnapInfo.fStayDuration, struFaceSnapMatchAlarm.byMatchPicNum, \
               struFaceSnapMatchAlarm.struRegion.fX, struFaceSnapMatchAlarm.struRegion.fY, struFaceSnapMatchAlarm.struRegion.fWidth, struFaceSnapMatchAlarm.struRegion.fHeight, struFaceSnapMatchAlarm.byPicTransType, tempFDID, temppID, strFDDesc.c_str(), struFaceSnapMatchAlarm.fSimilarity, struFaceSnapMatchAlarm.struBlackListInfo.wThresholdValue, \
               struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.byType, struFaceSnapMatchAlarm.byContrastStatus, struFaceSnapMatchAlarm.byModelingStatus, struFaceSnapMatchAlarm.byMask, struFaceSnapMatchAlarm.bySmile, strFCAddition.c_str(), struFaceSnapMatchAlarm.struSnapInfo.byEthnic, struFaceSnapMatchAlarm.byLivenessDetectionStatus,\
               struFaceSnapMatchAlarm.struBlackListInfo.byIsNoSaveFDPicture);
    AddLog(m_iCurDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    if (struFaceSnapMatchAlarm.struSnapInfo.dwSnapFacePicLen > 0 && struFaceSnapMatchAlarm.struSnapInfo.pBuffer1 != NULL)
    {
        int num = ulAlarmPic/1000+1;
        ulAlarmPic++;
        
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
//         SYSTEMTIME t;
//         GetLocalTime(&t);
//         char chTime[128];
//         sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
        if (struFaceSnapMatchAlarm.byPicTransType)
        {
            sprintf(cFilename, "%s\\Match_SnapPic[%s].txt", cFilename, chTime);
        }
        else
        {
            sprintf(cFilename, "%s\\Match SnapPic[%s].jpg", cFilename, chTime);
        }
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceSnapMatchAlarm.struSnapInfo.pBuffer1, struFaceSnapMatchAlarm.struSnapInfo.dwSnapFacePicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
	}
	
    if (struFaceSnapMatchAlarm.struBlackListInfo.dwBlackListPicLen > 0 && struFaceSnapMatchAlarm.struBlackListInfo.pBuffer1 != NULL)
    {
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        char cFilename[256] = { 0 };
        HANDLE hFile;
        DWORD dwReturn;

        //         SYSTEMTIME t;
        //         GetLocalTime(&t);
        //         char chTime[128];
        //         sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);

        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        if (struFaceSnapMatchAlarm.byPicTransType)
        {
            sprintf(cFilename, "%s\\Match_BlackList_Pic[%s].txt", cFilename, chTime);
        }
        else
        {
            sprintf(cFilename, "%s\\Match BlackList Pic[%s].jpg", cFilename, chTime);
        }
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceSnapMatchAlarm.struBlackListInfo.pBuffer1, struFaceSnapMatchAlarm.struBlackListInfo.dwBlackListPicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
	}

    if (struFaceSnapMatchAlarm.dwSnapPicLen > 0 && struFaceSnapMatchAlarm.pSnapPicBuffer != NULL)
    {
        char cFilename[256] = { 0 };
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        HANDLE hFile;
        DWORD dwReturn;
        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        if (struFaceSnapMatchAlarm.byPicTransType)
            sprintf(cFilename, "%s\\Match_SnapBigPic[%s].txt", cFilename, chTime);
        else
            sprintf(cFilename, "%s\\MatchSnapBigPic[%s].jpg", cFilename, chTime);
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceSnapMatchAlarm.pSnapPicBuffer, struFaceSnapMatchAlarm.dwSnapPicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }
	
    if (struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.dwPersonInfoExtendLen > 0 && struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend != NULL)
    {
        char cFilename[256] = { 0 };
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        HANDLE hFile;
        DWORD dwReturn;
        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\PersonInfoXML[%s].txt", cFilename, chTime);

        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.dwPersonInfoExtendLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }

	if (struFaceSnapMatchAlarm.struSnapInfo.pBuffer1 != NULL)
	{
		delete []struFaceSnapMatchAlarm.struSnapInfo.pBuffer1;
		struFaceSnapMatchAlarm.struSnapInfo.pBuffer1 = NULL;
	}
	
	if (struFaceSnapMatchAlarm.struBlackListInfo.pBuffer1 != NULL)
	{
		delete []struFaceSnapMatchAlarm.struBlackListInfo.pBuffer1;
		struFaceSnapMatchAlarm.struBlackListInfo.pBuffer1 = NULL;
	}

    if (struFaceSnapMatchAlarm.pSnapPicBuffer != NULL)
    {
        delete[]struFaceSnapMatchAlarm.pSnapPicBuffer;
        struFaceSnapMatchAlarm.pSnapPicBuffer = NULL;
    }

    if (struFaceSnapMatchAlarm.pModelDataBuffer != NULL)
    {
        delete[]struFaceSnapMatchAlarm.pModelDataBuffer;
        struFaceSnapMatchAlarm.pModelDataBuffer = NULL;
    }

    if (struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend != NULL)
    {
        delete[]struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend;
        struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend = NULL;
    }

    if (struFaceSnapMatchAlarm.struSnapInfo.pUIDBuffer != NULL)
    {
        delete[]struFaceSnapMatchAlarm.struSnapInfo.pUIDBuffer;
        struFaceSnapMatchAlarm.struSnapInfo.pUIDBuffer = NULL;
    }

    if (struFaceSnapMatchAlarm.struBlackListInfo.pFDID != NULL)
    {
        delete[]struFaceSnapMatchAlarm.struBlackListInfo.pFDID;
        struFaceSnapMatchAlarm.struBlackListInfo.pFDID = NULL;
    }

    if (struFaceSnapMatchAlarm.struBlackListInfo.pPID != NULL)
    {
        delete[]struFaceSnapMatchAlarm.struBlackListInfo.pPID;
        struFaceSnapMatchAlarm.struBlackListInfo.pPID = NULL;
    }

}

void CClientDemoDlg::FaceSnapMatchAlarmInfo(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[2048] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    NET_VCA_FACESNAP_MATCH_ALARM struFaceSnapMatchAlarm = { 0 };
    memcpy(&struFaceSnapMatchAlarm, pAlarmInfo, sizeof(struFaceSnapMatchAlarm));


    char sInfo[5120] = { 0 };

    // NET_VCA_FACESNAP_MATCH_ALARM
    sprintf(sInfo, "NET_VCA_FACESNAP_MATCH_ALARM \r\n");
    sprintf(sInfo, "%s fSimilarity=%0.3f \r\n", sInfo, struFaceSnapMatchAlarm.fSimilarity);
    sprintf(sInfo, "%s byMatchPicNum=%d \r\n", sInfo, struFaceSnapMatchAlarm.byMatchPicNum);
    sprintf(sInfo, "%s wStoragePort=%d \r\n", sInfo, struFaceSnapMatchAlarm.wStoragePort);
    sprintf(sInfo, "%s dwSnapPicLen=%d \r\n", sInfo, struFaceSnapMatchAlarm.dwSnapPicLen);
    sprintf(sInfo, "%s dwModelDataLen=%d \r\n", sInfo, struFaceSnapMatchAlarm.dwModelDataLen);
    sprintf(sInfo, "%s sStorageIP=%s \r\n", sInfo, struFaceSnapMatchAlarm.sStorageIP);
    sprintf(sInfo, "%s struRegion[%0.1f, %0.1f, %0.1f, %0.1f] \r\n", sInfo, \
        struFaceSnapMatchAlarm.struRegion.fX, struFaceSnapMatchAlarm.struRegion.fY, struFaceSnapMatchAlarm.struRegion.fWidth, struFaceSnapMatchAlarm.struRegion.fHeight);
    sprintf(sInfo, "%s byLivenessDetectionStatus=%d \r\n", sInfo, struFaceSnapMatchAlarm.byLivenessDetectionStatus);

    // NET_VCA_FACESNAP_INFO_ALARM
    sprintf(sInfo, "%sNET_VCA_FACESNAP_INFO_ALARM \r\n", sInfo);
    sprintf(sInfo, "%s dwRelativeTime=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.dwRelativeTime);
    sprintf(sInfo, "%s dwAbsTime=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    sprintf(sInfo, "%s dwSnapFacePicID=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.dwSnapFacePicID);
    sprintf(sInfo, "%s dwSnapFacePicLen=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.dwSnapFacePicLen);
    sprintf(sInfo, "%s byFaceScore=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.byFaceScore);
    sprintf(sInfo, "%s bySex=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.bySex);
    sprintf(sInfo, "%s byGlasses=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.byGlasses);
    sprintf(sInfo, "%s byAge=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.byAge);
    sprintf(sInfo, "%s byAgeDeviation=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.byAgeDeviation);
    sprintf(sInfo, "%s byAgeGroup=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.byAgeGroup);
    sprintf(sInfo, "%s byFacePicQuality=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.byFacePicQuality);
    sprintf(sInfo, "%s dwUIDLen=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.dwUIDLen);
    sprintf(sInfo, "%s fStayDuration=%0.3f \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.fStayDuration);
    sprintf(sInfo, "%s byEthnic=%d \r\n", sInfo, struFaceSnapMatchAlarm.struSnapInfo.byEthnic);


    // NET_VCA_BLACKLIST_INFO_ALARM
    sprintf(sInfo, "%sNET_VCA_BLACKLIST_INFO_ALARM", sInfo);
    sprintf(sInfo, "%s dwBlackListPicLen=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.dwBlackListPicLen);
    sprintf(sInfo, "%s byIsNoSaveFDPicture=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.byIsNoSaveFDPicture);

    // NET_VCA_BLACKLIST_INFO
    sprintf(sInfo, "%sNET_VCA_BLACKLIST_INFO", sInfo);

    sprintf(sInfo, "%s dwRelativeTime=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwRegisterID);
    sprintf(sInfo, "%s dwGroupNo=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwGroupNo);
    sprintf(sInfo, "%s byType=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.byType);
    sprintf(sInfo, "%s byLevel=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.byLevel);
    sprintf(sInfo, "%s byRemark=%s \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.byRemark);


    // NET_VCA_HUMAN_ATTRIBUTE
    sprintf(sInfo, "%sNET_VCA_HUMAN_ATTRIBUTE\r\n", sInfo);
    sprintf(sInfo, "%s bySex=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.bySex);
    sprintf(sInfo, "%s byCertificateType=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.byCertificateType);
    sprintf(sInfo, "%s byBirthDate=%s \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.byBirthDate);
    sprintf(sInfo, "%s byName=%s \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.byName);
    sprintf(sInfo, "%s byCertificateNumber=%s \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.byCertificateNumber);
    sprintf(sInfo, "%s byAgeGroup=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.byAgeGroup);



    // NET_DVR_AREAINFOCFG
    sprintf(sInfo, "%sNET_DVR_AREAINFOCFG \r\n", sInfo);
    sprintf(sInfo, "%s dwCode=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.struNativePlace.dwCode);
    sprintf(sInfo, "%s wNationalityID=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.struNativePlace.wNationalityID);
    sprintf(sInfo, "%s wProvinceID=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.struNativePlace.wProvinceID);
    sprintf(sInfo, "%s wCityID=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.struNativePlace.wCityID);
    sprintf(sInfo, "%s wCountyID=%d \r\n", sInfo, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.struNativePlace.wCountyID);

    //  打印信息
    NET_DVR_TIME  struAbsTime = { 0 };
    struAbsTime.dwYear = GET_YEAR(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struFaceSnapMatchAlarm.struSnapInfo.dwAbsTime);

    char tempFDID[256] = { 0 };
    if (struFaceSnapMatchAlarm.struBlackListInfo.dwFDIDLen > 0 && struFaceSnapMatchAlarm.struBlackListInfo.pFDID != NULL)
    {
        memcpy(tempFDID, struFaceSnapMatchAlarm.struBlackListInfo.pFDID, struFaceSnapMatchAlarm.struBlackListInfo.dwFDIDLen);
    }
    char temppID[256] = { 0 };
    if (struFaceSnapMatchAlarm.struBlackListInfo.dwPIDLen > 0 && struFaceSnapMatchAlarm.struBlackListInfo.pPID != NULL)
    {
        memcpy(temppID, struFaceSnapMatchAlarm.struBlackListInfo.pPID, struFaceSnapMatchAlarm.struBlackListInfo.dwPIDLen);
    }

    char tempFDDesc[256] = { 0 };
    if (struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwFDDescriptionLen > 0 && struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.pFDDescriptionBuffer != NULL)
    {
        memcpy(tempFDDesc, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.pFDDescriptionBuffer, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwFDDescriptionLen);
    }
    string strFDDesc = UTF82ASCII(tempFDDesc);

    sprintf(szInfoBuf, "Face Snap Match alarm BrokenNetHttp[%d] FDID[%s] PID[%s] ThresholdValue[%d] FDDesc[%s] Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] FaceID[%d] BlackList ID[%d] StorageIP[%s]-StoragePort[%d] FaceScore[%d]\
                        Sex[%d] Glasses[%d] Age[%d] FacePicQuality[%d] AgeDeviation[%d] StayDuration[%0.3f] MatchPicNum[%d] struRegion[%0.1f, %0.1f, %0.1f, %0.1f] PicTransType[%d] ListType[%d] ContrastStatus[%d] ModelingStatus[%d]\
                        Mask[%d] Smile[%d] Ethnic[%d] LivenessDetectionStatus[%d]\n",
        struFaceSnapMatchAlarm.byBrokenNetHttp, tempFDID, temppID, struFaceSnapMatchAlarm.struBlackListInfo.wThresholdValue, strFDDesc.c_str(), struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour,
        struAbsTime.dwMinute, struAbsTime.dwSecond, struFaceSnapMatchAlarm.struSnapInfo.dwSnapFacePicID, \
        struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.dwRegisterID, \
        struFaceSnapMatchAlarm.sStorageIP, struFaceSnapMatchAlarm.wStoragePort, \
        struFaceSnapMatchAlarm.struSnapInfo.byFaceScore, struFaceSnapMatchAlarm.struSnapInfo.bySex, struFaceSnapMatchAlarm.struSnapInfo.byGlasses, \
        struFaceSnapMatchAlarm.struSnapInfo.byAge, struFaceSnapMatchAlarm.struSnapInfo.byFacePicQuality, struFaceSnapMatchAlarm.struSnapInfo.byAgeDeviation, struFaceSnapMatchAlarm.struSnapInfo.fStayDuration, struFaceSnapMatchAlarm.byMatchPicNum, \
        struFaceSnapMatchAlarm.struRegion.fX, struFaceSnapMatchAlarm.struRegion.fY, struFaceSnapMatchAlarm.struRegion.fWidth, struFaceSnapMatchAlarm.struRegion.fHeight, \
        struFaceSnapMatchAlarm.byPicTransType, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.byType, struFaceSnapMatchAlarm.byContrastStatus, struFaceSnapMatchAlarm.byModelingStatus,struFaceSnapMatchAlarm.byMask, struFaceSnapMatchAlarm.bySmile,\
        struFaceSnapMatchAlarm.struSnapInfo.byEthnic, struFaceSnapMatchAlarm.byLivenessDetectionStatus);


    AddLog(m_iCurDeviceIndex, ALARM_INFO_T, szInfoBuf);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    char cFilename[256] = { 0 };
    char cFilenameTemp[256] = { 0 };
    memset(cFilenameTemp, 0, 256);
    BYTE cUID[64] = { 0 };
    if (struFaceSnapMatchAlarm.struSnapInfo.dwUIDLen > 0 && struFaceSnapMatchAlarm.struSnapInfo.pUIDBuffer != NULL)
    {

        memcpy(cUID, struFaceSnapMatchAlarm.struSnapInfo.pUIDBuffer, struFaceSnapMatchAlarm.struSnapInfo.dwUIDLen - 1);
        sprintf(cFilename, "%s\\%s[facematch]\\", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            int i = GetLastError();
            CreateDirectory(cFilename, NULL);
        }
        sprintf(cFilename, "%sAbs_%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d_", cFilename, struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, \
            struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond);
        for (int i = 0; i < 17; i++)
        {
            if (cUID[i] != '0')
            {
                sprintf(cFilename, "%s%c", cFilename, cUID[i]);
            }
        }
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            int i = GetLastError();
            CreateDirectory(cFilename, NULL);
        }
        DWORD dwReturn = 0;
        HANDLE hFile = NULL;
        sprintf(cFilenameTemp, "%s\\AlarmInfo[%s--fSimilarity=%0.3f].txt", cFilename, chTime, struFaceSnapMatchAlarm.fSimilarity);
        hFile = CreateFile(cFilenameTemp, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }

        WriteFile(hFile, sInfo, 5120, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }
    else
    {
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
    }
    memset(cFilenameTemp, 0, 256);
    if (struFaceSnapMatchAlarm.struSnapInfo.dwSnapFacePicLen > 0 && struFaceSnapMatchAlarm.struSnapInfo.pBuffer1 != NULL)
    {
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        HANDLE hFile;
        DWORD dwReturn;

        if (struFaceSnapMatchAlarm.byPicTransType)
        {
            sprintf(cFilenameTemp, "%s\\Match_SnapPic[%s].txt", cFilename, chTime);
        }
        else
        {
            sprintf(cFilenameTemp, "%s\\MatchSnapPic.jpg", cFilename);
        }
        hFile = CreateFile(cFilenameTemp, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            int i = GetLastError();
            return;
        }
        WriteFile(hFile, struFaceSnapMatchAlarm.struSnapInfo.pBuffer1, struFaceSnapMatchAlarm.struSnapInfo.dwSnapFacePicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }
    memset(cFilenameTemp, 0, 256);
    if (struFaceSnapMatchAlarm.dwSnapPicLen > 0 && struFaceSnapMatchAlarm.pSnapPicBuffer != NULL)
    {
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        HANDLE hFile;
        DWORD dwReturn;

        if (struFaceSnapMatchAlarm.byPicTransType)
        {
            sprintf(cFilenameTemp, "%s\\Match_SnapBigPic[%s].txt", cFilename, chTime);
        }
        else
        {
            sprintf(cFilenameTemp, "%s\\MatchSnapBigPic.jpg", cFilename);
        }
        hFile = CreateFile(cFilenameTemp, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceSnapMatchAlarm.pSnapPicBuffer, struFaceSnapMatchAlarm.dwSnapPicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }
    memset(cFilenameTemp, 0, 256);
    if (struFaceSnapMatchAlarm.struBlackListInfo.dwBlackListPicLen > 0 && struFaceSnapMatchAlarm.struBlackListInfo.pBuffer1 != NULL)
    {
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        HANDLE hFile;
        DWORD dwReturn;

        if (struFaceSnapMatchAlarm.byPicTransType)
        {
            sprintf(cFilenameTemp, "%s\\Match_BlackList_Pic[%s].txt", cFilename, chTime);
        }
        else
        {
            sprintf(cFilenameTemp, "%s\\MatchBlackListPic[%d%d].jpg", cFilename, struFaceSnapMatchAlarm.struBlackListInfo.dwBlackListPicLen, g_iCount);
        }
        hFile = CreateFile(cFilenameTemp, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }

        WriteFile(hFile, struFaceSnapMatchAlarm.struBlackListInfo.pBuffer1, struFaceSnapMatchAlarm.struBlackListInfo.dwBlackListPicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }
    memset(cFilenameTemp, 0, 256);
    if (struFaceSnapMatchAlarm.dwModelDataLen > 0 && struFaceSnapMatchAlarm.pModelDataBuffer != NULL)
    {
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        HANDLE hFile;
        DWORD dwReturn;
        sprintf(cFilenameTemp, "%s\\MatchBlackLisModelData.txt", cFilename);
        hFile = CreateFile(cFilenameTemp, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceSnapMatchAlarm.pModelDataBuffer, struFaceSnapMatchAlarm.dwModelDataLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }
    memset(cFilenameTemp, 0, 256);
    if (struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.dwPersonInfoExtendLen > 0 && struFaceSnapMatchAlarm.pModelDataBuffer != NULL)
    {
        HANDLE hFile;
        DWORD dwReturn;
        sprintf(cFilenameTemp, "%s\\MatchBlackListCustomInfoLen[%d%d].txt", cFilename, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.dwPersonInfoExtendLen, g_iCount);
        hFile = CreateFile(cFilenameTemp, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend, struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.dwPersonInfoExtendLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }
    g_iCount++;
    if (struFaceSnapMatchAlarm.struSnapInfo.pBuffer1 != NULL)
    {
        delete[]struFaceSnapMatchAlarm.struSnapInfo.pBuffer1;
        struFaceSnapMatchAlarm.struSnapInfo.pBuffer1 = NULL;
    }

    if (struFaceSnapMatchAlarm.struBlackListInfo.pBuffer1 != NULL)
    {
        delete[]struFaceSnapMatchAlarm.struBlackListInfo.pBuffer1;
        struFaceSnapMatchAlarm.struBlackListInfo.pBuffer1 = NULL;
    }
    if (struFaceSnapMatchAlarm.pSnapPicBuffer != NULL)
    {
        delete[]struFaceSnapMatchAlarm.pSnapPicBuffer;
        struFaceSnapMatchAlarm.pSnapPicBuffer = NULL;
    }
    if (struFaceSnapMatchAlarm.struSnapInfo.pUIDBuffer != NULL)
    {
        delete[]struFaceSnapMatchAlarm.struSnapInfo.pUIDBuffer;
        struFaceSnapMatchAlarm.struSnapInfo.pUIDBuffer = NULL;
    }
    if (struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend != NULL)
    {
        delete[]struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend;
        struFaceSnapMatchAlarm.struBlackListInfo.struBlackListInfo.struAttribute.pPersonInfoExtend = NULL;
    }
    if (struFaceSnapMatchAlarm.pModelDataBuffer != NULL)
    {
        delete[]struFaceSnapMatchAlarm.pModelDataBuffer;
        struFaceSnapMatchAlarm.pModelDataBuffer = NULL;
    }
    if (struFaceSnapMatchAlarm.struBlackListInfo.pFDID != NULL)
    {
        delete[]struFaceSnapMatchAlarm.struBlackListInfo.pFDID;
        struFaceSnapMatchAlarm.struBlackListInfo.pFDID = NULL;
    }
}

void CClientDemoDlg::ProcRuleInfoUpload(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    NET_DVR_RULE_INFO_ALARM struRuleInfo = {0};
    memcpy(&struRuleInfo, pAlarmInfo, sizeof(struRuleInfo));
    
    int i = struRuleInfo.struDevInfo.byChannel - g_struDeviceInfo[iDeviceIndex].iStartChan;
    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
    ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));

    NET_DVR_TIME  struAbsTime = {0};
    struAbsTime.dwYear = GET_YEAR(struRuleInfo.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struRuleInfo.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struRuleInfo.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struRuleInfo.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struRuleInfo.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struRuleInfo.dwAbsTime);

    sprintf(szInfoBuf, "Rule info Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]  relative[%d] DevInfo ip[%d]port[%d]chan[%d]",
    struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour,
    struAbsTime.dwMinute, struAbsTime.dwSecond, struRuleInfo.dwRelativeTime, 
    struRuleInfo.struDevInfo.struDevIP.sIpV4, struRuleInfo.struDevInfo.wPort, struRuleInfo.struDevInfo.byChannel);

    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

    NET_DVR_EVENT_INFO struEventInfo = {0};
    for ( i = 0; i < struRuleInfo.struEventInfoList.byNum; i++)
    {
        memcpy(&struEventInfo, &struRuleInfo.struEventInfoList.struEventInfo[i], sizeof(struEventInfo));
        if (VCA_HIGH_DENSITY == struEventInfo.dwEventType)
        {
            sprintf(szInfoBuf, "High density RuleID[%d]Name[%s]density[%f]", struEventInfo.byRuleID, struEventInfo.byRuleName, 
                struEventInfo.uEventParam.fCrowdDensity);
        }
        else if (VCA_HUMAN_ENTER == struEventInfo.dwEventType)
        {
            sprintf(szInfoBuf, "Human enter RuleID[%d]Name[%s]Human enter[%d]",struEventInfo.byRuleID,
                struEventInfo.byRuleName, struEventInfo.uEventParam.dwHumanIn);
        }
        else
        {
            sprintf(szInfoBuf, "event info RuleID[%d]Name[%s]", struEventInfo.byRuleID, struEventInfo.byRuleName);
        }
        
        AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    }

}

void CClientDemoDlg::ProcSensorAlarm(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_SENSOR_ALARM struSensorAlarm = {0};
    memcpy(&struSensorAlarm, pAlarmInfo, sizeof(struSensorAlarm));
    
    if (struSensorAlarm.bySensorChannel>48)
    {
        AfxMessageBox("模拟量通道号异常");
        return;
    }
    memcpy(&m_struSensorAlarm[struSensorAlarm.bySensorChannel - 1], &struSensorAlarm, sizeof(struSensorAlarm));
    
    // memcpy(&m_struSensorAlarm, &struSensorAlarm, sizeof(m_struSensorAlarm));
    char szLan[1024] = {0};

    char szName[33] = { 0 };
    strncpy(szName, (char*)struSensorAlarm.byName, NAME_LEN);
    
    sprintf(szLan, "Sensor Alarm:AbsTime[%d]Name[%s]SensorChan[%d]Type[%d]AlramType[%d]AlarmMode[%u]Value[%f]",
        struSensorAlarm.dwAbsTime, szName, struSensorAlarm.bySensorChannel,
        struSensorAlarm.byType, struSensorAlarm.byAlarmType, struSensorAlarm.byAlarmMode, struSensorAlarm.fValue);
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
    if (g_pDlgSensor != NULL)
    {
        g_pDlgSensor->SetSensorDate(struSensorAlarm);
    }
    
}

void CClientDemoDlg::ProcCVRAlarm(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_CVR_ALARM struCVRAlarm = {0};
    memcpy(&struCVRAlarm, pAlarmInfo, sizeof(struCVRAlarm));
    
    char szLan[1024] = {0};
    
    sprintf(szLan, "CVR ALARM Time[%04d-%02d-%02d %02d-%02d-%02d] AlarmLevel[%d] Status[%d] FirstType[%s] FirstIndex[%s] SecondType[%s] SecondIndex[%s]  \
		ThirdType[%s] ThirdIndex[%s] FourthType[%s] FourthIndex[%s]", 
        struCVRAlarm.struTime.dwYear, struCVRAlarm.struTime.dwMonth, struCVRAlarm.struTime.dwDay,
        struCVRAlarm.struTime.dwHour, struCVRAlarm.struTime.dwMinute, struCVRAlarm.struTime.dwSecond, 
		struCVRAlarm.byAlarmLevel, struCVRAlarm.byStatus,
		struCVRAlarm.szFirstType, struCVRAlarm.szFirstIndex, struCVRAlarm.szSecondType, struCVRAlarm.szSecondIndex,
		struCVRAlarm.szThirdType, struCVRAlarm.szThirdIndex, struCVRAlarm.szFourthType, struCVRAlarm.szFourthIndex);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);

    
}

void CClientDemoDlg::ProcSensorValueUpload(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_SENSOR_ALARM struSensorValue = {0};
    memcpy(&struSensorValue, pAlarmInfo, sizeof(struSensorValue));

    if (struSensorValue.bySensorChannel > 48)
    {
        AfxMessageBox("模拟量通道号异常");
        return;
    }
    memcpy(&m_struSensorAlarm[struSensorValue.bySensorChannel - 1], &struSensorValue, sizeof(struSensorValue));
    // memcpy(&m_struSensorAlarm, &struSensorValue, sizeof(m_struSensorAlarm));
    char szLan[1024] = {0};
    sprintf(szLan, "ValueUpload:AbsTime[%d]Name[%s]SensorChan[%d]Type[%d]Value[%f]",
        struSensorValue.dwAbsTime, struSensorValue.byName, struSensorValue.bySensorChannel,
        struSensorValue.byType,  struSensorValue.fValue);
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
    if (g_pDlgSensor != NULL)
    {
        g_pDlgSensor->SetSensorDate(struSensorValue);
    }
}

void CClientDemoDlg::ProcSwitchAlarm(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_SWITCH_ALARM struSwitchAlarm = {0};
    memcpy(&struSwitchAlarm, pAlarmInfo, sizeof(struSwitchAlarm));

    char szLan[1024] = {0};
	char szName[33] = {0};
	memcpy(szName, struSwitchAlarm.byName, NAME_LEN);
    //报警

    CString tmp;
    if (struSwitchAlarm.byAlarmType == 0)
    {
        tmp = "normal";
    }
    else if (struSwitchAlarm.byAlarmType == 1)
    {
        tmp = "short circuit";
    }
    else if (struSwitchAlarm.byAlarmType == 2)
    {
        tmp = "broken circuit";
    }
    else if (struSwitchAlarm.byAlarmType == 3)
    {
        tmp = "exception";
    }
    else
    {
        tmp = "unknown";
    }
    sprintf(szLan, "Switch alarm[%s], Name[%s]AlarmIn[%d]"\
        , tmp, szName, struSwitchAlarm.wSwitchChannel);

	
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
}

void CClientDemoDlg::ProcAlarmHostException(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
	
    NET_DVR_ALARMHOST_EXCEPTION_ALARM struAlarmHostException = {0};
    memcpy(&struAlarmHostException, pAlarmInfo, sizeof(struAlarmHostException));
    CString tmType;
    // 异常参数  1-设备防拆报警 2-设备防拆后后恢复正常 3-主电源掉电报警 4-主电源掉电后恢复正常 5-内部通信故障报警 
    // 6-内部通信故障后恢复正常  7-电话线断线 8-电话线断线恢复 9-自检失败报警  10-自检失败后恢复正常    
    // 11蓄电池欠压  12蓄电池电压恢复正常，13-蓄电池故障；14-MBUS模块掉线；15-MBUS模块掉线恢复；16-键盘掉线；
    //17-键盘掉线恢复；18-设备被移动；19-设备被移动复位  20-485外设线路断报警  21-485外设线路断后恢复正常
    //100-子板1插上,101-子板1拔出, 103-子板2插上,104-子板2拔出
	if (struAlarmHostException.dwExceptionType == 1)
    {
        tmType = "设备防拆报警";
    }
	else if (struAlarmHostException.dwExceptionType == 2)
	{
		tmType = "设备防拆后后恢复正常";
	}
	else if (struAlarmHostException.dwExceptionType == 3)
	{
		tmType = "主电源掉电报警";
	}
	else if (struAlarmHostException.dwExceptionType == 4)
	{
		tmType = "主电源掉电后恢复正常";
	}
	else if (struAlarmHostException.dwExceptionType == 5)
	{
		tmType = "内部通信故障报警";
	}
	else if (struAlarmHostException.dwExceptionType == 6)
	{
		tmType = "内部通信故障后恢复正常";
	}
	else if (struAlarmHostException.dwExceptionType == 7)
	{
		tmType = "电话线断线";
	}	
	else if (struAlarmHostException.dwExceptionType == 8)
	{
		tmType = "电话线断线恢复";
	}
	else if (struAlarmHostException.dwExceptionType == 9)
	{
		tmType = "自检失败报警";
	}
	else if (struAlarmHostException.dwExceptionType == 10)
	{
		tmType = "自检失败后恢复正常";
	}	
	else if (struAlarmHostException.dwExceptionType == 11)
	{
		tmType = "蓄电池欠压";
	}
	else if (struAlarmHostException.dwExceptionType == 12)
	{
		tmType = "蓄电池电压恢复正常";
	}
	else if (struAlarmHostException.dwExceptionType == 13)
	{
		tmType = "蓄电池故障";
	}	
	else if (struAlarmHostException.dwExceptionType == 14)
	{
		tmType = "MBUS模块掉线";
	}
	else if (struAlarmHostException.dwExceptionType == 15)
	{
		tmType = "MBUS模块掉线恢复";
	}
	else if (struAlarmHostException.dwExceptionType == 16)
	{
		tmType = "键盘掉线";
	}	
	else if (struAlarmHostException.dwExceptionType == 17)
	{
		tmType = "键盘掉线恢复";
	}
	else if (struAlarmHostException.dwExceptionType == 18)
	{
		tmType = "设备被移动";
	}
	else if (struAlarmHostException.dwExceptionType == 19)
	{
		tmType = "设备被移动复位";
	}
	else if (struAlarmHostException.dwExceptionType == 20)
	{
		tmType = "485外设线路断报警";
	}
	else if (struAlarmHostException.dwExceptionType == 21)
	{
		tmType = "485外设线路断后恢复正常";
	}
	else if (struAlarmHostException.dwExceptionType == 22)
	{
		tmType = "硬盘满";
	}
	else if (struAlarmHostException.dwExceptionType == 23)
	{
		tmType = "硬盘未格式化";
	}
	else if (struAlarmHostException.dwExceptionType == 24)
	{
		tmType = "硬盘读写出错";
	}
	else if (struAlarmHostException.dwExceptionType == 25)
	{
		tmType = "子板1插上";
	}
	else if (struAlarmHostException.dwExceptionType == 26)
	{
		tmType = "子板1拔出";
	}
	else if (struAlarmHostException.dwExceptionType == 27)
	{
		tmType = "子板2插上";
	}
	else if (struAlarmHostException.dwExceptionType == 28)
	{
		tmType = "子板2拔出";
	}

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, tmType);
   
}

void CClientDemoDlg::ProcDeviceAlarm(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	if (COMM_ALARM_DEVICE == pAlarmDev->lCommand)
	{
		char *pAlarmInfo = (char *)(lParam);		
		int iDeviceIndex = pAlarmDev->iDeviceIndex;

		NET_DVR_ALARMINFO_DEV struDeviceAlarm = {0};
		memcpy(&struDeviceAlarm, pAlarmInfo, sizeof(struDeviceAlarm));
    
		char szLan[1024] = {0};

		sprintf(szLan, "Device Alarm(CVR): type[%d], num[%d]", struDeviceAlarm.dwAlarmType, struDeviceAlarm.dwNumber);

		int iNumber = struDeviceAlarm.dwNumber;
		WORD *pContent = struDeviceAlarm.pNO; 
		for (int i = 0; i < iNumber && i < 10; i++)
		{
			sprintf(szLan, "%s %d", szLan, *(pContent));
			pContent = pContent + 1;
		}

		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
	}
}

void CClientDemoDlg::ProcDeviceV40Alarm(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    if (COMM_ALARM_DEVICE_V40 == pAlarmDev->lCommand)
    {
        char *pAlarmInfo = (char *)(lParam);		
        int iDeviceIndex = pAlarmDev->iDeviceIndex;
        
        NET_DVR_ALARMINFO_DEV_V40 struDeviceAlarm = {0};
        memcpy(&struDeviceAlarm, pAlarmInfo, sizeof(struDeviceAlarm));
        
        char szLan[1024] = {0};
        
        sprintf(szLan, "Device Alarm(COMM_ALARM_DEVICE_V40): type[%d], num[%d],byLevel[%d]", struDeviceAlarm.dwAlarmType, struDeviceAlarm.dwNumber,struDeviceAlarm.uSubAlarmInfo.struResourceUsage.byLevel);
        
        int iNumber = struDeviceAlarm.dwNumber;
        WORD *pContent = struDeviceAlarm.pNO; 
        for (int i = 0; i < iNumber && i < 10; i++)
        {
            sprintf(szLan, "%s %d", szLan, *(pContent));
            pContent = pContent + 1;
        }
        
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
    }
}

void CClientDemoDlg::ProcAlarmHostSatetyCabinState(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_ALARMHOST_SAFETYCABINSTATE struAlarm = {0};
    memcpy(&struAlarm, pAlarmInfo, sizeof(struAlarm));

	char szLan[1024] = {0};
	char szLan1[64] = {0};
	char szLan2[64] = {0};
	char szLan3[64] = {0};
	char szLan4[64] = {0};
	char szLan5[64] = {0};
	char szLan6[64] = {0};
	char szLan7[64] = {0};
	char szLan8[64] = {0};
	char szLan9[64] = {0};
	char szLan10[64] = {0};
	char szLan11[64] = {0};
	char szLan12[64] = {0};

	if (1 == struAlarm.byManState)
	{
		g_StringLanType(szLan1, "舱内有人; ", "someone in the cabin;  ");
	}
	else
	{
		g_StringLanType(szLan1, "舱内没有人; ", "no one in the cabin;  ");
	}

	if (1 == struAlarm.byEnterButton)
	{
		g_StringLanType(szLan2, "进门按钮: 按下; ", "EnterButton: on;  ");
	}
	else
	{
		g_StringLanType(szLan2, "进门按钮: 不按下; ", "EnterButton: off;  ");
	}
	
	if (1 == struAlarm.byExitButton)
	{
		g_StringLanType(szLan3, "出门按钮: 按下; ", "ExitButton: on;  ");
	}
	else
	{
		g_StringLanType(szLan3, "出门按钮: 不按下; ", "ExitButton: off;  ");
	}

	if (1 == struAlarm.byUrgencyButton)
	{
		g_StringLanType(szLan4, "紧急按钮: 按下; ", "UrgencyButton: off;  ");
	}
	else
	{
		g_StringLanType(szLan4, "紧急按钮: 不按下; ", "UrgencyButton: off;  ");
	}

	if (0 == struAlarm.byDoorState)
	{
		g_StringLanType(szLan5, "门关; ", "Door: close;  ");
	}
	else
	{
		g_StringLanType(szLan5, "门开; ", "Door: open;  ");
	}

	if (0 == struAlarm.byLockState)
	{
		g_StringLanType(szLan6, "锁关; ", "locker: close;  ");
	}
	else
	{
		g_StringLanType(szLan6, "锁开; ", "locker: open;  ");
	}

	if (0 == struAlarm.byAbnormal)
	{
		g_StringLanType(szLan7, "正常;", "Normal");
	}
	else
	{
		g_StringLanType(szLan7, "异常;", "Abnormal");
	}
	
	if (0 == struAlarm.byFanState)
	{
		g_StringLanType(szLan8, "风扇关; ", "Fan: off;  ");
	}
	else
	{
		g_StringLanType(szLan8, "风扇开; ", "Fan: on;  ");
	}
	
	if (0 == struAlarm.byLightState)
	{
		g_StringLanType(szLan9, "灯光关; ", "Light: off;  ");
	}
	else
	{
		g_StringLanType(szLan9, "灯光开; ", "Light: on;  ");
	}
	if (0 == struAlarm.byFollow)
	{
		g_StringLanType(szLan10, "无尾随", "Follow: no");
	}
	else
	{
		g_StringLanType(szLan10, "有尾随", "Follow: yes");
	}
	if (0 == struAlarm.byFaint)
	{
		g_StringLanType(szLan11, "无晕倒", "Faint: no");
	}
	else
	{
		g_StringLanType(szLan11, "有晕倒", "Faint: yes");
	}
	if (0 == struAlarm.byManyPerson)
	{
		g_StringLanType(szLan12, "无多人", "Single");
	}
	else
	{
		g_StringLanType(szLan12, "有多人", "ManyPerson");
	}

    sprintf(szLan, "%s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s", szLan1, szLan2, szLan3, szLan4, szLan5, szLan6, szLan7,szLan8,szLan9, szLan10, szLan11, szLan12);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
}

void CClientDemoDlg::ProcAlarmHostAlarmoutStatus(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_ALARMHOST_ALARMOUTSTATUS struAlarm = {0};
    memcpy(&struAlarm, pAlarmInfo, sizeof(struAlarm));
	char szLan[1024] = {0};
	char szLanCn[1024] = {0};
	char szLanEn[1024] = {0};
	switch(struAlarm.byAlarmType)
	{
	case 1: //报警输出口状态
		if(struAlarm.byAlarmStatus == 1)
		{
			sprintf(szLanCn, "报警输出口 %d(%s) 报警", struAlarm.wChan, struAlarm.byName);
			sprintf(szLanEn, "Get Alarm from AlarmOut channel %d(%s)", struAlarm.wChan, struAlarm.byName);
			g_StringLanType(szLan, szLanCn, szLanEn);
		}
		else
		{
			sprintf(szLanCn, "报警输出口 %d(%s) 报警取消", struAlarm.wChan, struAlarm.byName);
			sprintf(szLanEn, "Alarm from AlarmOut channel %d(%s) clean", struAlarm.wChan, struAlarm.byName);
			g_StringLanType(szLan, szLanCn, szLanEn);
		}
	break;
	case 2: //警号状态
		if(struAlarm.byAlarmStatus == 1)
		{
			sprintf(szLanCn, "警号 %d(%s) 警号输出", struAlarm.wChan, struAlarm.byName);
			sprintf(szLanEn, "Get Alarm from siren  %d(%s)", struAlarm.wChan, struAlarm.byName);
			g_StringLanType(szLan, szLanCn, szLanEn);
		}
		else
		{
			sprintf(szLanCn, "警号 %d(%s) 警号关闭", struAlarm.wChan, struAlarm.byName);
			sprintf(szLanEn, "Alarm from siren  %d(%s) clean", struAlarm.wChan, struAlarm.byName);
			g_StringLanType(szLan, szLanCn, szLanEn);
		}
	break;
	default:
	break;
	}
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
}

void CClientDemoDlg::ProcAlarmHostCIDAlarm(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_CID_ALARM struAlarm = {0};
    memcpy(&struAlarm, pAlarmInfo, sizeof(struAlarm));

	char szLan[1024] = {0};
	char szLanCn[1024] = {0};
	char szLanEn[1024] = {0};

	switch (struAlarm.byReportType)
	{
	case NET_DVR_DEFENCE_ALARM:
		sprintf(szLanCn, "防区报警: ");
		sprintf(szLanEn, "Zone Alarm: ");
		break;
	case NET_DVR_VIDEO_ALARM:
		sprintf(szLanCn, "视频报警：");
		sprintf(szLanEn, "Video Alarm：");
		break;
	case NET_DVR_VIRTUAL_DEFENCE_ALARM:
		 sprintf(szLanCn, "软防区报警：");
		 sprintf(szLanEn, "Soft Zone Alarm：");
		break;
	case NET_DVR_HOSTAGE_ALARM:
		sprintf(szLanCn, "挟持报警: ");
		sprintf(szLanEn, "Hostage Alarm：");
		break;
	case NET_DVR_KNOCK_DOWN_ALARM:
		sprintf(szLanCn, "防拆报警: ");
		sprintf(szLanEn, "Tamper Alarm: ");
		break;
	case NET_DVR_OPERATE_ALARM:
		sprintf(szLanCn, "操作：");
		sprintf(szLanEn, "Operate：");
		break;
	case NET_DVR_OHTER_ABNORMAL_ALARM:
		sprintf(szLanCn, "异常：");
		sprintf(szLanEn, "Abnormal：");
		break;

	default:
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "Unknown Alarm");
		return;
	}
	char sTemp1[5] = {0};
	char sTemp2[33] = {0};
	memcpy(sTemp1, struAlarm.sCIDCode, 4);
	sprintf(szLanCn, "%sCID事件号：%s", szLanCn, sTemp1);
	sprintf(szLanEn, "%sCID：%s", szLanEn, sTemp1);

	if (memcmp((char*)struAlarm.sCIDDescribe, "", NAME_LEN) != 0)
	{
		memcpy(sTemp2, struAlarm.sCIDDescribe, NAME_LEN);
		sprintf(szLanCn, "%s, CID事件名：%s", szLanCn, sTemp2);
		sprintf(szLanEn, "%s, CID describe：%s", szLanEn, sTemp2);
	} 
	else
	{
		char sTempCn[64] = {0};
		char sTempEn[64] = {0};
		switch (atoi((char*)struAlarm.sCIDCode))
		{
		case CID_ENTER+CID_ALARM:
			sprintf(sTempCn, "即时防区报警");
			sprintf(sTempEn, "Instant Zone Alarm");
			break;
		case CID_ENTER+CID_FIRE_ALARM:
			sprintf(sTempCn, "火警防区报警");
			sprintf(sTempEn, "Fire Zone Alarm");
			break;
		case CID_ENTER+CID_ABDUCT_REPORT:
			sprintf(sTempCn, "挟持报告");
			sprintf(sTempEn, "Hostage Report");
			break;
		case CID_ENTER+CID_SILENT_24:
			sprintf(sTempCn, "24小时无声防区报警");
			sprintf(sTempEn, "24 H Non-audio Zone Alarm");
			break;
		case CID_ENTER+CID_AUDIO_24:
			sprintf(sTempCn, "24小时有声防区报警");
			sprintf(sTempEn, "24 H Audio Zone Alarm");
			break;
		case CID_ENTER+CID_AUXILIARY_24:
			sprintf(sTempCn, "24小时辅助防区报警");
			sprintf(sTempEn, "24 H Aux Zone Alarm");
			break;
		case CID_ENTER+CID_SHOCK_24:
			sprintf(sTempCn, "24小时震动防区报警");
			sprintf(sTempEn, "24 H Vib Zone Alarm");
			break;
		case CID_ENTER+CID_PERIMETER_ALARM:
			sprintf(sTempCn, "周界防区报警");
			sprintf(sTempEn, "Perimeter Zone Alarm");
			break;
		case CID_ENTER+CID_INNET_ALARM:
			sprintf(sTempCn, "内部延时防区报警");
			sprintf(sTempEn, "Internal Delay Zone Alarm");
			break;
		case CID_ENTER+CID_ENTER_EXIT:
			sprintf(sTempCn, "延时防区报警");
			sprintf(sTempEn, "Delay Zone Alarm");
			break;
		case CID_ENTER+CID_DEVICE_OPEN:
			sprintf(sTempCn, "设备防拆");
			sprintf(sTempEn, "Device Tampering Alarm");
			break;

		case CID_ENTER+CID_AC_LOSS:
			sprintf(sTempCn, "交流电掉电");
			sprintf(sTempEn, "AC Power Down");
			break;
		case CID_ENTER+CID_LOW_BATT_VOL:
			sprintf(sTempCn, "蓄电池电压低");
			sprintf(sTempEn, "Low Battery Voltage");
			break;
		case CID_ENTER+CID_DEV_RESET:
			sprintf(sTempCn, "主机复位");
			sprintf(sTempEn, "Host Reset");
			break;
		case CID_ENTER+CID_PRINTER_FAIL:
			sprintf(sTempCn, "打印机掉线");
			sprintf(sTempEn, "Printer Disconnected");
			break;
		case CID_ENTER+CID_LINE_LOSS:
			sprintf(sTempCn, "电话线断开");
			sprintf(sTempEn, "Telephone Disconnected");
			break;
		case CID_ENTER+CID_BUS_LOSS:
			sprintf(sTempCn, "扩展总线模块掉线");
			sprintf(sTempEn, "XBUS Module Disconnection");
			break;
		case CID_ENTER+CID_DETECTOR_OPEN:
			sprintf(sTempCn, "防区感应器被拆");
			sprintf(sTempEn, "Zone Sensor Demolishing");
			break;

		case CID_ENTER+CID_GUARD:
			sprintf(sTempCn, "撤防");
			sprintf(sTempEn, "Disarming");
			break;
		case CID_ENTER+CID_GUARD_AUTO:
			sprintf(sTempCn, "自动撤防");
			sprintf(sTempEn, "Auto Disarming");
			break;
		case CID_ENTER+CID_CANCEL_ARM:
			sprintf(sTempCn, "消警");
			sprintf(sTempEn, "Clear");
			break;
		case CID_ENTER+CID_GUARD_IMME:
			sprintf(sTempCn, "即时撤防");
			sprintf(sTempEn, "Instant Disarming");
			break;
		case CID_ENTER+CID_KEY_ZONE_GUARD:
			sprintf(sTempCn, "钥匙防区撤防");
			sprintf(sTempEn, "Key Zone Disarming");
			break;
		case CID_ENTER+CID_GUARD_STAY:
			sprintf(sTempCn, "留守撤防");
			sprintf(sTempEn, "Stay Disarming");
			break;
		case CID_ENTER+CID_AUTOCTRL_TRIG:
			sprintf(sTempCn, "定时开启触发器");
			sprintf(sTempEn, "Activate Trigger by Schedule");
			break;
		case CID_ENTER + CID_ONETOUCH_AWAY_ARMING:
			sprintf(sTempCn, "一键外出布防");
			sprintf(sTempEn, "One-touch away arming");
			break;
		case CID_ENTER + CID_ONETOUCH_STAY_ARMING:
			sprintf(sTempCn, "一键留守布防");
			sprintf(sTempEn, "One-touch stay arming");
			break;
		case CID_ENTER + CID_CARD_ARMING_OR_DISARMING:
			sprintf(sTempCn, "刷卡撤防");
			sprintf(sTempEn, "Card disarming");
			break;
		case CID_ENTER+CID_AUTOGUARD_FAIL:
			sprintf(sTempCn, "自动布撤防失败");
			sprintf(sTempEn, "Failed to automatically arm");
			break;
		case CID_ENTER+CID_AOPEN_TRIG_FAIL:
			sprintf(sTempCn, "定时开启触发器失败");
			sprintf(sTempEn, "Failed to activate the trigger");
			break;
		case CID_ENTER+CID_ACLOSE_TRIG_FAIL:
			sprintf(sTempCn, "定时关闭触发器失败");
			sprintf(sTempEn, "Failed to deactivate the trigger");
			break;
		case CID_ENTER+CID_AUTOUNGUARD_FAIL:
			sprintf(sTempCn, "自动撤防失败");
			sprintf(sTempEn, "Failed to auto disarm");
			break;

		case CID_ENTER+CID_BYPASS:
			sprintf(sTempCn, "旁路");
			sprintf(sTempEn, "Bypass");
			break;
		case CID_ENTER+CID_GROUP_BYPASS:
			sprintf(sTempCn, "子系统组旁路");
			sprintf(sTempEn, "Partition Group Bypass");
			break;


		case CID_ENTER+CID_MANUAL_TEST_RPT:
			sprintf(sTempCn, "手动测试报告");
			sprintf(sTempEn, "Manual Test Report");
			break;
		case CID_ENTER+CID_AUTO_TEST_RPT:
			sprintf(sTempCn, "定时测试报告");
			sprintf(sTempEn, "Timing Test Report");
			break;
		case CID_ENTER+CID_ENTER_PROG:
			sprintf(sTempCn, "进入编程");
			sprintf(sTempEn, "Enter Programming");
			break;
		case CID_ENTER+CID_EXIT_PROG:
			sprintf(sTempCn, "退出编程");
			sprintf(sTempEn, "Exit Programming");
			break;

		case CID_ENTER+CID_SOFT_INSTAND:
			sprintf(sTempCn, "软防区紧急报警");
			sprintf(sTempEn, "Soft Zone Emergency Alarm");
			break;
		case CID_ENTER+CID_SOFT_FIRE:
			sprintf(sTempCn, "软防区火警");
			sprintf(sTempEn, "Soft Zone Fire Alarm");
			break;
		case CID_ENTER+CID_SOFT_MOBS:
			sprintf(sTempCn, "软防区匪警");
			sprintf(sTempEn, "Soft Zone Bandit Alarm");
			break;

		case CID_ENTER+CID_KEY_FAIL:
			sprintf(sTempCn, "键盘掉线");
			sprintf(sTempEn, "Keyboard Loss Connection");
			break;
		case CID_ENTER+CID_TRIGGER_FAIL:
			sprintf(sTempCn, "键盘总线上触发器掉线");
			sprintf(sTempEn, "KBUS Trigger Disconnection");
			break;
		case CID_ENTER+CID_GPK_FAIL:
			sprintf(sTempCn, "键盘总线上GP/K掉线");
			sprintf(sTempEn, "KBUS GP/K Disconnection");
			break;
		case CID_ENTER+CID_MODULE_FAIL:
			sprintf(sTempCn, "键盘总线上MN/K掉线");
			sprintf(sTempEn, "KBUS MN/K Disconnection");
			break;
        case CID_ENTER + CID_WIRELESS_DETECTOR_FAIL:
            sprintf(sTempCn, "无线探测器掉线");
            sprintf(sTempEn, "Wireless Detector fail");
            break;
        case CID_ENTER + CID_WIRELESS_DETECTOR_BATTERY_LOW:
            sprintf(sTempCn, "无线探测器欠压");
            sprintf(sTempEn, "Wireless Detector battery low");
            break;
		case CID_ENTER+CID_WRIE_LESS_NET:
			sprintf(sTempCn, "无线网络异常");
			sprintf(sTempEn, "Wireless Network Exception");
			break;
		case CID_ENTER+CID_SIM_FAULT:
			sprintf(sTempCn, "SIM卡异常");
			sprintf(sTempEn, "SIM Card Exception");
			break;
        case CID_ENTER + CID_WIFI_ABNORMAL:
            sprintf(sTempCn, "WIFI通信异常");
            sprintf(sTempEn, "Wifi Abnormal");
            break;
        case CID_ENTER + CID_RF_ABNORMAL:
            sprintf(sTempCn, "RF信号异常");
            sprintf(sTempEn, "Rf signal Abnormal");
            break;
		case CID_ENTER+CID_IPADDR_CONFLICT:
			sprintf(sTempCn, "IP冲突");
			sprintf(sTempEn, "IP Address Conflict");
			break;
		case CID_ENTER+CID_ETHERNET_BROKEN:
			sprintf(sTempCn, "网线断");
			sprintf(sTempEn, "Network Disconnected");
			break;
		case CID_ENTER+CID_MOTION_DECTECT:
			sprintf(sTempCn, "移动侦测报警开始");
			sprintf(sTempEn, "Motion Detection Alarm Started");
			break;
		case CID_ENTER+CID_MASK_ALARM:
			sprintf(sTempCn, "遮挡报警开始");
			sprintf(sTempEn, "Tampering Alarm Started");
			break;
		case CID_ENTER+CID_VI_LOST:
			sprintf(sTempCn, "视频信号丢失");
			sprintf(sTempEn, "Video Signal Loss");
			break;
		case CID_ENTER+CID_VS_MISMATCH:
			sprintf(sTempCn, "输入/输出视频制式不匹配");
			sprintf(sTempEn, "Input/output Format Mismatch");
			break;
		case CID_ENTER+CID_VI_EXCEPTION:
			sprintf(sTempCn, "视频输入异常");
			sprintf(sTempEn, "Video Input Exception");
			break;
		case CID_ENTER+CID_HD_FULL:
			sprintf(sTempCn, "硬盘满");
			sprintf(sTempEn, "Hard disk is full");
			break;
		case CID_ENTER+CID_HD_ERROR:
			sprintf(sTempCn, "硬盘出错");
			sprintf(sTempEn, "Hard Disk Exception");
			break;
		case CID_ENTER+CID_PIC_SEND_FAILED:
			sprintf(sTempCn, "图片上传失败");
			sprintf(sTempEn, "Failed to upload the picture");
			break;
		case CID_ENTER + CID_KEY_LOCKED:
			sprintf(sTempCn, "键盘锁定");
			sprintf(sTempEn, "Keyboard locked");
			break;
		case CID_ENTER+CID_GUARD_SINGLE:
			sprintf(sTempCn, "单防区撤防");
			sprintf(sTempEn, "Single-Zone Disarming");
			break;
        case CID_ENTER + CID_ZONE_ASSOCIATED_DETECTOR:
            sprintf(sTempCn, "防区添加探测器");
            sprintf(sTempEn, "Zone add detector");
            break;

		case CID_EXIT+CID_ALARM:
			sprintf(sTempCn, "即时防区恢复");
			sprintf(sTempEn, "Instant Zone Recovered");
			break;
		case CID_EXIT+CID_FIRE_ALARM:
			sprintf(sTempCn, "火警防区恢复");
			sprintf(sTempEn, "Fire Zone Recovered");
			break;
		case CID_EXIT+CID_SILENT_24:
			sprintf(sTempCn, "24小时无声防区恢复");
			sprintf(sTempEn, "24 H Non-audio Zone Recovered");
			break;
		case CID_EXIT+CID_AUDIO_24:
			sprintf(sTempCn, "24小时有声防区恢复");
			sprintf(sTempEn, "24 H Audio Zone Recovered");
			break;
		case CID_EXIT+CID_AUXILIARY_24:
			sprintf(sTempCn, "24小时辅助防区恢复");
			sprintf(sTempEn, "24 H Aux Zone Recovered");
			break;
		case CID_EXIT+CID_SHOCK_24:
			sprintf(sTempCn, "24小时震动防区恢复");
			sprintf(sTempEn, "24 H Vib Zone Recovered");
			break;
		case CID_EXIT+CID_PERIMETER_ALARM:
			sprintf(sTempCn, "周界防区恢复");
			sprintf(sTempEn, "Perimeter Zone Recovered");
			break;
		case CID_EXIT+CID_INNET_ALARM:
			sprintf(sTempCn, "内部延时防区恢复");
			sprintf(sTempEn, "Internal Delay Zone Recovered");
			break;
		case CID_EXIT+CID_ENTER_EXIT:
			sprintf(sTempCn, "延时防区恢复");
			sprintf(sTempEn, "Delay Zone Recovered");
			break;
		case CID_EXIT+CID_DEVICE_OPEN:
			sprintf(sTempCn, "设备防拆恢复");
			sprintf(sTempEn, "Device Tampering Recovered");
			break;

		case CID_EXIT+CID_AC_LOSS:
			sprintf(sTempCn, "交流电恢复");
			sprintf(sTempEn, "AC Recovered");
			break;
		case CID_EXIT+CID_LOW_BATT_VOL:
			sprintf(sTempCn, "蓄电池电压正常");
			sprintf(sTempEn, "Normal Battery Voltage");
			break;
		case CID_EXIT+CID_PRINTER_FAIL:
			sprintf(sTempCn, "打印机恢复");
			sprintf(sTempEn, "Printer Recovered");
			break;
		case CID_EXIT+CID_LINE_LOSS:
			sprintf(sTempCn, "电话线连接");
			sprintf(sTempEn, "Telephone Connected");
			break;
		case CID_EXIT+CID_BUS_LOSS:
			sprintf(sTempCn, "扩展总线模块恢复");
			sprintf(sTempEn, "XBUS Module Connectioned");
			break;
		case CID_EXIT+CID_DETECTOR_OPEN:
			sprintf(sTempCn, "防区感应器被拆恢复");
			sprintf(sTempEn, "Zone Sensor Recovered");
			break;

		case CID_EXIT+CID_GUARD:
			sprintf(sTempCn, "布防");
			sprintf(sTempEn, "Arming");
			break;
		case CID_EXIT+CID_GUARD_AUTO:
			sprintf(sTempCn, "自动布防");
			sprintf(sTempEn, "Auto Arming");
			break;
		case CID_EXIT+CID_GUARD_IMME:
			sprintf(sTempCn, "即时布防");
			sprintf(sTempEn, "Instant Arming");
			break;
		case CID_EXIT+CID_KEY_ZONE_GUARD:
			sprintf(sTempCn, "钥匙防区布防");
			sprintf(sTempEn, "Key Zone Arming");
			break;
		case CID_EXIT+CID_GUARD_STAY:
			sprintf(sTempCn, "留守布防");
			sprintf(sTempEn, "Stay Arming");
			break;
		case CID_EXIT+CID_FORCED_ARM:
			sprintf(sTempCn, "强制布防");
			sprintf(sTempEn, "Forced Arming");
			break;
		case CID_EXIT+CID_AUTOCTRL_TRIG:
			sprintf(sTempCn, "定时关闭触发器");
			sprintf(sTempEn, "Deactivate Trigger by Schedule");
			break;
		case CID_EXIT + CID_ONETOUCH_AWAY_ARMING:
			sprintf(sTempCn, "一键外出布防");
			sprintf(sTempEn, "One-touch away arming");
			break;
		case CID_EXIT + CID_ONETOUCH_STAY_ARMING:
			sprintf(sTempCn, "一键留守布防");
			sprintf(sTempEn, "One-touch stay arming");
			break;
		case CID_EXIT + CID_CARD_ARMING_OR_DISARMING:
			sprintf(sTempCn, "刷卡布防");
			sprintf(sTempEn, "Card arming");
			break;
		case CID_EXIT+CID_BYPASS:
			sprintf(sTempCn, "旁路恢复");
			sprintf(sTempEn, "Bypass Recovered");
			break;
		case CID_EXIT+CID_GROUP_BYPASS:
			sprintf(sTempCn, "子系统组旁路恢复");
			sprintf(sTempEn, "Partition Group Bypass Recovered");
			break;

		case CID_EXIT+CID_KEY_FAIL:
			sprintf(sTempCn, "键盘恢复");
			sprintf(sTempEn, "Keyboard Recovered");
			break;
		case CID_EXIT+CID_TRIGGER_FAIL:
			sprintf(sTempCn, "键盘总线上触发器恢复");
			sprintf(sTempEn, "KBUS Trigger Recovered");
			break;
		case CID_EXIT+CID_GPK_FAIL:
			sprintf(sTempCn, "键盘总线上GP/K恢复");
			sprintf(sTempEn, "KBUS GP/K Recovered");
			break;
		case CID_EXIT+CID_MODULE_FAIL:
			sprintf(sTempCn, "键盘总线上MN/K恢复");
			sprintf(sTempEn, "KBUS MN/K Recovered");
			break;
        case CID_EXIT + CID_WIRELESS_DETECTOR_FAIL:
            sprintf(sTempCn, "无线探测器恢复");
            sprintf(sTempEn, "Wireless Detector Recovered");
            break;
        case CID_EXIT + CID_WIRELESS_DETECTOR_BATTERY_LOW:
            sprintf(sTempCn, "无线探测器电量恢复正常");
            sprintf(sTempEn, "Wireless Detector battery Recovered");
            break;
		case CID_EXIT+CID_WRIE_LESS_NET:
			sprintf(sTempCn, "无线网络正常");
			sprintf(sTempEn, "Wireless Network Recovered");
			break;
		case CID_EXIT+CID_SIM_FAULT:
			sprintf(sTempCn, "SIM卡正常");
			sprintf(sTempEn, "SIM Card Recovered");
			break;
        case CID_EXIT + CID_WIFI_ABNORMAL:
            sprintf(sTempCn, "WIFI通信恢复");
            sprintf(sTempEn, "Wifi Recovered");
            break;
        case CID_EXIT + CID_RF_ABNORMAL:
            sprintf(sTempCn, "RF信号恢复");
            sprintf(sTempEn, "Rf signal Recovered");
            break;
		case CID_EXIT+CID_IPADDR_CONFLICT:
			sprintf(sTempCn, "IP正常");
			sprintf(sTempEn, "IP address is normal");
			break;
		case CID_EXIT+CID_ETHERNET_BROKEN:
			sprintf(sTempCn, "网线正常");
			sprintf(sTempEn, "Network is normal");
			break;
		case CID_EXIT+CID_MOTION_DECTECT:
			sprintf(sTempCn, "移动侦测报警结束");
			sprintf(sTempEn, "Motion Detection Alarm Stopped");
			break;
		case CID_EXIT+CID_MASK_ALARM:
			sprintf(sTempCn, "遮挡报警结束");
			sprintf(sTempEn, "Tampering Alarm Stopped");
			break;
		case CID_EXIT+CID_VI_LOST:
			sprintf(sTempCn, "视频信号恢复");
			sprintf(sTempEn, "Video Signal Recovered");
			break;
		case CID_EXIT+CID_VS_MISMATCH:
			sprintf(sTempCn, "输入/输出视频制式恢复正常");
			sprintf(sTempEn, "Input/output Format Recovered");
			break;
		case CID_EXIT+CID_VI_EXCEPTION:
			sprintf(sTempCn, "视频输入恢复正常");
			sprintf(sTempEn, "Video Input Recovered");
			break;
		case CID_EXIT+CID_HD_FULL:
			sprintf(sTempCn, "硬盘空闲");
			sprintf(sTempEn, "Hard disk is free");
			break;
		case CID_EXIT+CID_HD_ERROR:
			sprintf(sTempCn, "硬盘恢复正常");
			sprintf(sTempEn, "Hard Disk Recovered");
			break;
		case CID_EXIT + CID_KEY_LOCKED:
			sprintf(sTempCn, "键盘解锁");
			sprintf(sTempEn, "Keyboard locked");
			break;
		case CID_EXIT+CID_GUARD_SINGLE:
			sprintf(sTempCn, "单防区布防");
			sprintf(sTempEn, "Single-Zone Arming");
			break;
        case CID_EXIT + CID_ZONE_ASSOCIATED_DETECTOR:
            sprintf(sTempCn, "防区删除探测器");
            sprintf(sTempEn, "Zone delete associated detector");
            break;
			
		default:
			g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "Unknown CID describe");
			return;
		}
		sprintf(szLanCn, "%s, CID事件名：%s", szLanCn, sTempCn);
		sprintf(szLanEn, "%s, CID describe：%s", szLanEn, sTempEn);
	}
	
	//中心账号
	//if (strcmp((char*)struAlarm.sCenterAccount, ""))
	{
		memset(sTemp2, 0, sizeof(sTemp2));
		memcpy(sTemp2, struAlarm.sCenterAccount, ACCOUNTNUM_LEN);
		if (0 == struAlarm.byCenterType || 1 == struAlarm.byCenterType)
		{	 
			memcpy(sTemp2, struAlarm.sCenterAccount, ACCOUNTNUM_LEN);
		} 
		else if (2 == struAlarm.byCenterType)
		{
			memcpy(sTemp2, struAlarm.sCenterAccountV40, ACCOUNTNUM_LEN_V40);
		}
		sprintf(szLanCn, "%s, 中心账号：%s", szLanCn, sTemp2);
		sprintf(szLanEn, "%s, Center account：%s", szLanEn, sTemp2);
	}

	//用户名
	if (0xff != struAlarm.byUserType)
	{
		if (0 == struAlarm.byUserType)//网络用户
		{
			memset(sTemp2, 0, sizeof(sTemp2));
			memcpy(sTemp2, struAlarm.sUserName, NAME_LEN);
			sprintf(szLanCn, "%s，网络用户名：%s", szLanCn, struAlarm.sUserName);
			sprintf(szLanEn, "%s，Net User Name：%s", szLanEn, struAlarm.sUserName);
		}
		else if(1 == struAlarm.byUserType)//键盘用户
		{
			sprintf(szLanCn, "%s, 键盘用户号：%d", szLanCn, struAlarm.wKeyUserNo);
			sprintf(szLanEn, "%s, Keypad UserID：%d", szLanEn, struAlarm.wKeyUserNo);
		}
		else if(2 == struAlarm.byUserType)//手机用户
		{
			memset(sTemp2, 0, sizeof(sTemp2));
			memcpy(sTemp2, struAlarm.sUserName, NAME_LEN);
			sprintf(szLanCn, "%s，手机号：%s", szLanCn, struAlarm.sUserName);
			sprintf(szLanEn, "%s，Cellphone No：%s", szLanEn, struAlarm.sUserName);
		}
		else if(3 == struAlarm.byUserType)//系统用户
		{
			memset(sTemp2, 0, sizeof(sTemp2));
			memcpy(sTemp2, struAlarm.sUserName, NAME_LEN);
			sprintf(szLanCn, "%s，系统用户名：%s", szLanCn, struAlarm.sUserName);
			sprintf(szLanEn, "%s，System User Name：%s", szLanEn, struAlarm.sUserName);
		}
		else
		{
			sprintf(szLanCn, "%s, 未知用户类型", szLanCn);
			sprintf(szLanEn, "%s, Unknown User Type", szLanEn);
		}
	}
	
	//键盘号
	if (0xff != struAlarm.byKeypadNo)
	{
		sprintf(szLanCn, "%s, 键盘号：%d", szLanCn, struAlarm.byKeypadNo);
		sprintf(szLanEn, "%s, KeyPad No：%d", szLanEn, struAlarm.byKeypadNo);
	}
	//子系统号
	if (0xff != struAlarm.bySubSysNo)
	{
		sprintf(szLanCn, "%s, 子系统号：%d", szLanCn, struAlarm.bySubSysNo);
		sprintf(szLanEn, "%s, Subsystem No：%d", szLanEn, struAlarm.bySubSysNo);
	}
	//防区号
	if (0xffff != struAlarm.wDefenceNo)
	{
		sprintf(szLanCn, "%s, 防区号：%d", szLanCn, struAlarm.wDefenceNo+1);
		sprintf(szLanEn, "%s, Zone No：%d", szLanEn, struAlarm.wDefenceNo+1);
	}
	//视频通道号
	if (0xff != struAlarm.byVideoChanNo)
	{
		sprintf(szLanCn, "%s, 视频通道号：%d", szLanCn, struAlarm.byVideoChanNo);
		sprintf(szLanEn, "%s, Viedo Chan No：%d", szLanEn, struAlarm.byVideoChanNo);
	}
	//硬盘号
	if (0xff != struAlarm.byDiskNo)
	{
		sprintf(szLanCn, "%s, 硬盘号：%d", szLanCn, struAlarm.byDiskNo);
		sprintf(szLanEn, "%s, HD No：%d", szLanEn, struAlarm.byDiskNo);
	}
	//模块地址号
	if (0xffff != struAlarm.wModuleAddr)
	{
		sprintf(szLanCn, "%s, 模块地址：%d", szLanCn, struAlarm.wModuleAddr);
		sprintf(szLanEn, "%s, Module Address：%d", szLanEn, struAlarm.wModuleAddr);
	}

    if (memcmp((char*)struAlarm.byDevSerialNo, "", DEV_SERIAL_LEN) != 0)
    {
        memset(sTemp2, 0, sizeof(sTemp2));
        memcpy(sTemp2, struAlarm.byDevSerialNo, DEV_SERIAL_LEN);
        sprintf(szLanCn, "%s, 序列号：%s", szLanCn, sTemp2);
        sprintf(szLanEn, "%s, serial：%s", szLanEn, sTemp2);
    }

	g_StringLanType(szLan, szLanCn, szLanEn);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
	
	memset(szLanCn, 0, sizeof(szLanCn));
	memset(szLanEn, 0, sizeof(szLanEn));
	memset(szLan, 0, sizeof(szLan));
	sprintf(szLanCn, "触发报警时间：%04d-%02d-%02d %02d:%02d:%02d, 上传报警时间：%04d-%02d-%02d %02d:%02d:%02d", struAlarm.struTriggerTime.wYear, struAlarm.struTriggerTime.byMonth, struAlarm.struTriggerTime.byDay, struAlarm.struTriggerTime.byHour, \
		struAlarm.struTriggerTime.byMinute, struAlarm.struTriggerTime.bySecond, struAlarm.struUploadTime.wYear, struAlarm.struUploadTime.byMonth, struAlarm.struUploadTime.byDay, struAlarm.struUploadTime.byHour\
		, struAlarm.struUploadTime.byMinute, struAlarm.struUploadTime.bySecond);
	sprintf(szLanEn, "Trigger Time：%d-%d-%d %d:%d:%d, Upload Time：%d-%d-%d %d:%d:%d", struAlarm.struTriggerTime.wYear, struAlarm.struTriggerTime.byMonth, struAlarm.struTriggerTime.byDay, struAlarm.struTriggerTime.byHour, \
		struAlarm.struTriggerTime.byMinute, struAlarm.struTriggerTime.bySecond, struAlarm.struUploadTime.wYear, struAlarm.struUploadTime.byMonth, struAlarm.struUploadTime.byDay, struAlarm.struUploadTime.byHour\
		, struAlarm.struUploadTime.byMinute, struAlarm.struUploadTime.bySecond);	
	g_StringLanType(szLan, szLanCn, szLanEn);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);	
}

void CClientDemoDlg::ProcessAlarmhostUPSAlarm(char* szLanCn, char* szLanEn, LPNET_DVR_ALARMHOST_UPS_ALARMINFO lpAlarm)
{
	//默认除以10
	DWORD dwDivisionCoefficient = 10;
	switch (lpAlarm->byAlarmType)
	{
	case 1:
		sprintf(szLanCn, "%s", "A相输入电压越限");
		break;
	case 2:
		sprintf(szLanCn, "%s", "B相输入电压越限");
		break;
	case 3:
		sprintf(szLanCn, "%s", "C相输入电压越限");
		break;
	case 4:
		sprintf(szLanCn, "%s", "A相输出电压越限5");
		break;
	case 5:
		sprintf(szLanCn, "%s", "B相输出电压越限");
		break;
	case 6:
		sprintf(szLanCn, "%s", "C相输出电压越限");
		break;		
	case 7:
		sprintf(szLanCn, "%s", "A相输入频率越限");
		break;
	case 8:
		sprintf(szLanCn, "%s", "B相输入频率越限");
		break;
	case 9:
		sprintf(szLanCn, "%s", "C相输入频率越限");
		break;
	case 10:
		sprintf(szLanCn, "%s", "整流器电压越限报警");
		break;
	case 11:
		sprintf(szLanCn, "%s", "过载报警");
		break;
	case 12:
		sprintf(szLanCn, "%s", "电池电压低报警");
		break;
	case 13:
		sprintf(szLanCn, "%s", "电池后备时间超低报警");
		dwDivisionCoefficient = 1;
		break;
	case 14:
		sprintf(szLanCn, "%s", "电池温度超高报警");
		break;
	case 15:
		sprintf(szLanCn, "%s", "逆变器关闭报警");
		break;
	case 16:
		sprintf(szLanCn, "%s", "自动旁路开报警");
		break;		
	case 17:
		sprintf(szLanCn, "%s", "整流器故障报警");
		break;
	case 18:
		sprintf(szLanCn, "%s", "逆变器故障报警");
		break;
	case 19:
		sprintf(szLanCn, "%s", "充电器故障报警");
		break;
	case 20:
		sprintf(szLanCn, "%s", "电池故障报警");
		break;
	case 21:
		sprintf(szLanCn, "%s", "自动旁路故障报警");
		break;
	default:
		sprintf(szLanCn, "%s", "未知报警类型");
		break;
	}
	if (0xffffffff == lpAlarm->iAlarmValue)
	{
		sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo);
	}
	else
	{
		if (1 == dwDivisionCoefficient)
		{
			sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d, 报警值：%d", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo, lpAlarm->iAlarmValue);
		}
		else	
		{
			sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d, 报警值：%0.1f", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo, (float)lpAlarm->iAlarmValue/dwDivisionCoefficient);
		}
	}
}

void CClientDemoDlg::ProcessAlarmhostSwitchPowerAlarm(char* szLanCn, char* szLanEn, LPNET_DVR_ALARMHOST_SWITCH_POWER_SUPPLY_ALARMINFO lpAlarm)
{
	//默认除以10
	DWORD dwDivisionCoefficient = 10;

		/*报警类型：1-电池测试失败 2-AC-DC转换器故障，3-输入线/相电压AB/A越限，4-输入线/相电压BC/B越限，5-输入线/相电压CA/C越限，
	6-输出电流A越限，7-输出电流B越限，8-输出电流C越限，9整流模块故障，10-风扇故障，11-直流电压越限*/
	switch (lpAlarm->byAlarmType)
	{
	case 1:
		sprintf(szLanCn, "%s", "电池测试失败");
		break;
	case 2:
		sprintf(szLanCn, "%s", "AC-DC转换器故障");
		break;
	case 3:
		sprintf(szLanCn, "%s", "输入线/相电压AB/A越限");
		break;
	case 4:
		sprintf(szLanCn, "%s", "输入线/相电压BC/B越限");
		break;
	case 5:
		sprintf(szLanCn, "%s", "输入线/相电压CA/C越限");
		break;
	case 6:
		sprintf(szLanCn, "%s", "A相输出电流越限");
		break;		
	case 7:
		sprintf(szLanCn, "%s", "B相输出电流越限");
		break;
	case 8:
		sprintf(szLanCn, "%s", "C相输出电流越限");
		break;
	case 9:
		sprintf(szLanCn, "%s", "整流模块故障");
		break;
	case 10:
		sprintf(szLanCn, "%s", "风扇故障");
		break;
	case 11:
		sprintf(szLanCn, "%s", "直流电压越限");
		break;
	default:
		sprintf(szLanCn, "%s", "未知报警类型");
		break;
	}
	if (0xffffffff == lpAlarm->iAlarmValue)
	{
		sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo);
	}
	else
	{
		if (1 == dwDivisionCoefficient)
		{
			sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d, 报警值：%d", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo, lpAlarm->iAlarmValue);
		}
		else	
		{
			sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d, 报警值：%0.1f", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo, (float)lpAlarm->iAlarmValue/dwDivisionCoefficient);
		}
	}
}


void CClientDemoDlg::ProcessAlarmhostGasDetectAlarm(char* szLanCn, char* szLanEn, LPNET_DVR_ALARMHOST_GAS_DETECT_SYS_ALARMINFO lpAlarm)
{
	//默认除以10
	DWORD dwDivisionCoefficient = 10;
	/*报警类型：1- SF6气体含量异常，2-氧气含量异常，3-温度值异常，4-湿度值异常，5-流量*/
	switch (lpAlarm->byAlarmType)
	{
	case 1:
		sprintf(szLanCn, "%s", "SF6气体含量异常");
		dwDivisionCoefficient = 1;
		break;
	case 2:
		sprintf(szLanCn, "%s", "氧气含量异常");
		break;
	case 3:
		sprintf(szLanCn, "%s", "温度值异常");
		break;
	case 4:
		sprintf(szLanCn, "%s", "湿度值异常");
		break;
	case 5:
		sprintf(szLanCn, "%s", "流量");
		dwDivisionCoefficient = 1;
		break;
	default:
		sprintf(szLanCn, "%s", "未知报警类型");
		break;
	}
	if (0xffffffff == lpAlarm->iAlarmValue)
	{
		sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo);
	}
	else
	{
		if (1 == dwDivisionCoefficient)
		{
			sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d, 报警值：%d", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo, lpAlarm->iAlarmValue);
		}
		else	
		{
			sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d, 报警值：%0.1f", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo, (float)lpAlarm->iAlarmValue/dwDivisionCoefficient);
		}
	}
}

void CClientDemoDlg::ProcessAlarmhostTempHumiSensorAlarm(char* szLanCn, char* szLanEn, LPNET_DVR_ALARMHOST_TEMP_HUMIDITY_SENSOR_ALARMINFO lpAlarm)
{
	//默认除以10
	DWORD dwDivisionCoefficient = 10;
	//1-温度异常，2-湿度异常
	switch (lpAlarm->byAlarmType)
	{
	case 1:
		sprintf(szLanCn, "%s", "温度异常");
		break;
	case 2:
		sprintf(szLanCn, "%s", "湿度异常");
		break;
	default:
		sprintf(szLanCn, "%s", "未知报警类型");
		break;
	}
	if (0xffffffff == lpAlarm->iAlarmValue)
	{
		sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo);
	}
	else
	{
		if (1 == dwDivisionCoefficient)
		{
			sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d, 报警值：%d", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo, lpAlarm->iAlarmValue);
		}
		else	
		{
			sprintf(szLanCn, "%s, 485通道：%d, 槽位号：%d, 报警值：%0.1f", szLanCn, lpAlarm->byChanNo, lpAlarm->bySlotNo, (float)lpAlarm->iAlarmValue/dwDivisionCoefficient);
		}
	}
}

void CClientDemoDlg::ProcAlarmHostExternalDevAlarm(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_485_EXTERNAL_DEVICE_ALARMINFO struAlarm = {0};
    memcpy(&struAlarm, pAlarmInfo, sizeof(struAlarm));

	char szLan[1024] = {0};
	char szLanCn[1024] = {0};
	char szLanEn[1024] = {0};

	switch (struAlarm.byAlarmType)
	{
	case 1:
		ProcessAlarmhostUPSAlarm(szLanCn, szLanEn, &struAlarm.struAlarmInfo.struUPSAlarm);
		break;
	case 2:
		ProcessAlarmhostSwitchPowerAlarm(szLanCn, szLanEn, &struAlarm.struAlarmInfo.struSwitchPowerAlarm);
		break;
	case 3:
		ProcessAlarmhostGasDetectAlarm(szLanCn, szLanEn, &struAlarm.struAlarmInfo.struGasDetectSystemAlarm);
		break;
	case 4:
		ProcessAlarmhostTempHumiSensorAlarm(szLanCn, szLanEn, &struAlarm.struAlarmInfo.struTempHumiditySensorAlarm);
		break;
	default:
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "Unknown Alarm");
		return;
	}

	g_StringLanType(szLan, szLanCn, szLanEn);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
}

void CClientDemoDlg::ProcessAlarmhostPointValue(char* szLanCn, char* szLanEn, LPNET_DVR_ALARMHOST_POINT_VALUE lpAlarm)
{
	//默认除以10
	DWORD dwDivisionCoefficient = 1;
	if (1 == lpAlarm->byPointType)
	{
		dwDivisionCoefficient = 1000;
	}
	
	//1-本地模拟量通道，2-本地开关量通道，3-485通道，4-网络通道
	switch (lpAlarm->byChanType)
	{
	case 1:
		sprintf(szLanCn, "本地模拟量通道%u,变量号:%u,点号%u 报警值:%0.3f", lpAlarm->dwChanNo, lpAlarm->dwVariableNo, lpAlarm->dwPointNo, (float)((float)(lpAlarm->iValue)/dwDivisionCoefficient));
		break;
	case 2:
		sprintf(szLanCn, "本地开关量通道%u,变量号:%u,点号%u 报警值:%d", lpAlarm->dwChanNo, lpAlarm->dwVariableNo, lpAlarm->dwPointNo, lpAlarm->iValue);
		break;
	case 3:
		sprintf(szLanCn, "485通道%u槽位%u,变量号:%u,点号%u 报警值:%0.3f", lpAlarm->dwChanNo, lpAlarm->dwSubChanNo, lpAlarm->dwVariableNo, lpAlarm->dwPointNo, (float)((float)(lpAlarm->iValue)/dwDivisionCoefficient));
		break;
	case 4:
		sprintf(szLanCn, "网络通道%u,变量号:%u,点号%u 报警值:%d", lpAlarm->dwChanNo, lpAlarm->dwVariableNo, lpAlarm->dwPointNo, (float)((float)(lpAlarm->iValue)/dwDivisionCoefficient));
		break;
	default:
		sprintf(szLanCn, "%s", "未知通道类型");
		break;
	}
}

void CClientDemoDlg::ProcAlarmHostData(WPARAM wParam, LPARAM lParam)
{
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_ALARMHOST_DATA_UPLOAD struAlarm = {0};
    memcpy(&struAlarm, pAlarmInfo, sizeof(struAlarm));
	
	char szLan[1024] = {0};
	char szLanCn[1024] = {0};
	char szLanEn[1024] = {0};
	
	switch (struAlarm.byDataType)
	{
	case 1: //监测点数据上传
		ProcessAlarmhostPointValue(szLanCn, szLanEn, &struAlarm.struAlarmData.struPointValue);
		break;
	default:
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "Unknown Alarm");
		return;
	}
	
	g_StringLanType(szLan, szLanCn, szLanEn);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
}

void CClientDemoDlg::ProcGateAlarmHostData(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_GATE_ALARMINFO struAlarm = {0};
    memcpy(&struAlarm, pAlarmInfo, sizeof(struAlarm));	
	
	sprintf(szInfoBuf, "AlarmType:[%d] DevType[%d] DevStatus[%d] AlarmTime[%d:%d:%d %d:%d:%d]\n",\
		struAlarm.byAlarmType, struAlarm.byExternalDevType, struAlarm.byExternalDevStatus, struAlarm.struAlarmTime.wYear, struAlarm.struAlarmTime.byMonth, struAlarm.struAlarmTime.byDay, \
		struAlarm.struAlarmTime.byHour, struAlarm.struAlarmTime.byMinute, struAlarm.struAlarmTime.bySecond);
	
	if (struAlarm.byAlarmType == 0x01)
	{
		sprintf(szInfoBuf, "%s License[%s] VehicleType[%d]", szInfoBuf, struAlarm.uAlarmInfo.struVehicleInfo.sLicense, \
			struAlarm.uAlarmInfo.struVehicleInfo.byVehicleType);
	}
	
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcAlarmHostWirelessInfo(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    NET_DVR_ALARMWIRELESSINFO struAlarm = { 0 };
    memcpy(&struAlarm, pAlarmInfo, sizeof(struAlarm));

    sprintf(szInfoBuf, "deveciID[%s] dataTraffic[%f] signalIntensity[%d]\n", struAlarm.byDeviceID, struAlarm.fDataTraffic, struAlarm.bySignalIntensity);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}


void CClientDemoDlg::ProcExternalControlAlarmHostData(WPARAM wParam, LPARAM lParam)//布防报警(外控报警)2013-06-09
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_EXTERNAL_CONTROL_ALARM struAlarm = {0};
    memcpy(&struAlarm, pAlarmInfo, sizeof(struAlarm));
	
	sprintf(szInfoBuf,"ChannelNo:[%d] Flicker:[%d] IONo:[%d] ParkingIndex:[%d] ExternalBeginTime:[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] \n",
		struAlarm.dwChannelNo, struAlarm.struLampStateCtrl.byFlicker, struAlarm.struLampStateCtrl.dwIONo, struAlarm.struLampStateCtrl.byParkingIndex
		,struAlarm.struExternalBeginTime.dwYear, struAlarm.struExternalBeginTime.dwMonth, struAlarm.struExternalBeginTime.dwDay,
		struAlarm.struExternalBeginTime.dwHour, struAlarm.struExternalBeginTime.dwMinute,struAlarm.struExternalBeginTime.dwSecond);
	
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
}

void CClientDemoDlg::ProcSceneChangeDetection(WPARAM wParam, LPARAM lParam)//2013-07-17场景变更侦测报警
{
	char szInfoBuf[1024] = {0};
	char szLan[128] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	NET_DVR_SCENECHANGE_DETECTION_RESULT struSceneChange = {0};
	memcpy(&struSceneChange, pAlarmInfo, sizeof(struSceneChange));
	
	g_StringLanType(szLan, "场景变更侦测报警","Scene Change Detection");

	sprintf(szInfoBuf, "%s: (Device IP:[%s]  Port:[%d]  Device Channel:[%d]  Ivms Channel:[%d]IvmsChannelEx[%d])\n", szLan,
		struSceneChange.struDevInfo.struDevIP.sIpV4, struSceneChange.struDevInfo.wPort, 
        struSceneChange.struDevInfo.byChannel, struSceneChange.struDevInfo.byIvmsChannel, struSceneChange.wDevInfoIvmsChannelEx);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcHotSpare(WPARAM wParam, LPARAM lParam)//2013-07-17热备异常报警
{
	char szInfoBuf[1024] = {0};
	char szLan[128] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	NET_DVR_ALARM_HOT_SPARE struAlarmHotSpare = {0};
	memcpy(&struAlarmHotSpare, pAlarmInfo, sizeof(struAlarmHotSpare));
	
	g_StringLanType(szLan, "热备异常报警","Scene Change Detection");
	switch (struAlarmHotSpare.dwExceptionCase)
	{
	case 0:
		sprintf(szInfoBuf, "%s: (网络异常 Device IP:[%s])\n", szLan,
			struAlarmHotSpare.struDeviceIP.sIpV4);
	}
	
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcVehCostItem(WPARAM wParam, LPARAM lParam)//2013-11-19 出入口过车收费明细
{
	char szInfoBuf1[1024] = {0};
	char szInfoBuf2[1024] = {0};
	char szInfoBuf3[1024] = {0};
	char szInfoBuf4[1024] = {0};
	char szLan[128] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	NET_ITS_PASSVEHICLE_COST_ITEM struVehCostItem = {0};
	memset(&struVehCostItem, 0, sizeof(NET_ITS_PASSVEHICLE_COST_ITEM));
	memcpy(&struVehCostItem, pAlarmInfo, sizeof(NET_ITS_PASSVEHICLE_COST_ITEM));
	
	g_StringLanType(szLan, "出入口过车收费明细","Vehicle Cost Item");
	sprintf(szInfoBuf4,"%s End: \n", szLan);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf4);
	
	sprintf(szInfoBuf3, "Operator Name:[%s]; Vehicle Type:[%d]; Pay Rule ID:[%d]; Free Rule ID:[%d]\n",struVehCostItem.byOperatorName,\
        struVehCostItem.byVehicleType, struVehCostItem.dwPayRuleID, struVehCostItem.dwFreeRuleID);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf3);
	
	sprintf(szInfoBuf2, "Vehicle ID:[%d]; In Time:[%s]; Out Time:[%s]; Card No:[%s]; Plate No:[%s]; Pay Cost:[%0.2f]\n", struVehCostItem.dwPassVehicleID,\
		struVehCostItem.byIntime, struVehCostItem.byOuttime, struVehCostItem.byCardNo, struVehCostItem.byPlateInfo, struVehCostItem.fPayCost);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf2);
	
	sprintf(szInfoBuf1,"%s Begin: \n", szLan);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf1);
}

void CClientDemoDlg::ProcVehHandOver(WPARAM wParam, LPARAM lParam)//2013-11-19 出入口交接班数据
{
	char szInfoBuf[1024] = {0};
	char szLan[128] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	NET_ITS_HANDOVER_INFO struHandOverInfo = {0};
	memset(&struHandOverInfo, 0, sizeof(NET_ITS_HANDOVER_INFO));
	memcpy(&struHandOverInfo, pAlarmInfo, sizeof(NET_ITS_HANDOVER_INFO));
	
	g_StringLanType(szLan, "出入口交接班数据","Vehicle Handover Info");
	
	sprintf(szInfoBuf, "%s(Operator Name:[%s]; Operator Card:[%s]; Start Time:[%s]; End Time:[%s]; Total Pay:[%0.2f]; Total Records:[%d])\n", szLan,\
		struHandOverInfo.byOperatorName, struHandOverInfo.byOperatorCard, struHandOverInfo.byStartTime, struHandOverInfo.byEndTime,\
		struHandOverInfo.fTotal_Pay, struHandOverInfo.dwTotal_Records);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
}

void CClientDemoDlg::ProcDefocus(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    char szLan[128] = { 0 };
    char szAlarmType[128] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    NET_DVR_DEFOCUS_ALARM struDefocus = { 0 };
    memset(&struDefocus, 0, sizeof(NET_DVR_DEFOCUS_ALARM));
    memcpy(&struDefocus, pAlarmInfo, sizeof(NET_DVR_DEFOCUS_ALARM));

    NET_DVR_TIME  struAbsTime = { 0 };
    struAbsTime.dwYear = GET_YEAR(struDefocus.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struDefocus.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struDefocus.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struDefocus.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struDefocus.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struDefocus.dwAbsTime);

    g_StringLanType(szLan, "虚焦报警", "Audio Exception");
    sprintf(szInfoBuf, "flag[%d] Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d %2.2d%2.2d]%s: IvmsChannel:%d]IvmsChannelEx[%d]\n",  \
        struDefocus.byTimeDiffFlag, struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, \
        struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond, struDefocus.cTimeDifferenceH, struDefocus.cTimeDifferenceM, \
        szLan, struDefocus.struDevInfo.byIvmsChannel, struDefocus.wDevInfoIvmsChannelEx);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcAudioException(WPARAM wParam, LPARAM lParam)//声音异常报警上传 2014-03-21
{
	char szInfoBuf[1024] = {0};
	char szLan[128] = {0};
	char szAlarmType[128] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	NET_DVR_AUDIOEXCEPTION_ALARM struAudioException = {0};
	memset(&struAudioException, 0, sizeof(NET_DVR_AUDIOEXCEPTION_ALARM));
	memcpy(&struAudioException, pAlarmInfo, sizeof(NET_DVR_AUDIOEXCEPTION_ALARM));
	switch (struAudioException.byAlarmType)
	{
	case 1:
		g_StringLanType(szAlarmType, "音频输入异常","Audio Input Exception");
		break;
	case 2:
		g_StringLanType(szAlarmType, "音频输入突变","Audio Input Mutation");
		break;
	case 3:
		g_StringLanType(szAlarmType, "声强陡降","Audio Decibel Dropped");
		break;
    case 4:
        g_StringLanType(szAlarmType, "音频丢失","Audio Loss");
		break;
	default:
		g_StringLanType(szAlarmType, "未知","Unknow");
		break;
	}
	
	g_StringLanType(szLan, "声音异常报警","Audio Exception");
	sprintf(szInfoBuf, "%s:[AlarmType:%s AudioDecibel:%d IP:%s Port:%d Channel:%d IvmsChannel:%d]IvmsChannelEx[%d]\n", szLan,\
		szAlarmType, struAudioException.wAudioDecibel, struAudioException.struDevInfo.struDevIP.sIpV4, struAudioException.struDevInfo.wPort, \
        struAudioException.struDevInfo.byChannel, struAudioException.struDevInfo.byIvmsChannel, struAudioException.wDevInfoIvmsChannelEx);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcHeatMapResult(WPARAM wParam, LPARAM lParam)//热度图报警上传 2014-03-21
{
	char szInfoBuf[1024] = {0};
	char szLan[128] = {0};
	char szAlarmType[128] = {0};
	char cFilename[256] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	NET_DVR_HEATMAP_RESULT struHeatMapResult = {0};
	memset(&struHeatMapResult, 0, sizeof(NET_DVR_HEATMAP_RESULT));
	memcpy(&struHeatMapResult, pAlarmInfo, sizeof(NET_DVR_HEATMAP_RESULT));
	sprintf(cFilename, "No heat map");
	
	if (struHeatMapResult.wArrayColumn > 0 && struHeatMapResult.wArrayLine > 0 && struHeatMapResult.pBuffer != NULL)
	{
		sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName);
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
		
		SYSTEMTIME t;
		GetLocalTime(&t);
		char chTime[128];
		sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
		
		sprintf(cFilename, "%s\\HeatMapValue[%s].txt", cFilename, chTime);
		HANDLE hFile;	
		DWORD dwReturn = 0;
		hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		WriteFile(hFile, struHeatMapResult.pBuffer, struHeatMapResult.wArrayColumn*struHeatMapResult.wArrayLine, &dwReturn, NULL);
		CloseHandle(hFile);
		hFile = NULL;
	}
	
	g_StringLanType(szLan, "热度图报警","Heat Map Result");
	sprintf(szInfoBuf, "%s:[IP:%s Port:%d Channel:%d IvmsChannel:%d StartTime%d-%d-%d %d:%d:%d flag[%d] %2.2d%2.2d] EndTime:%d-%d-%d %d:%d:%d %2.2d%2.2d] ArrayLine:%d ArrayColumn:%d HeatMapPath:%s \
		MaxHeatMapValue:%d MinHeatMapValue:%d TimeHeatMapValue:%d DetSceneID:%d BrokenNetHttp:%d]IvmsChannel[%d]IvmsChannelEx[%d]\n", \
		szLan, struHeatMapResult.struDevInfo.struDevIP.sIpV4, struHeatMapResult.struDevInfo.wPort, struHeatMapResult.struDevInfo.byChannel,\
		struHeatMapResult.struDevInfo.byIvmsChannel, struHeatMapResult.struStartTime.wYear, struHeatMapResult.struStartTime.byMonth,\
		struHeatMapResult.struStartTime.byDay, struHeatMapResult.struStartTime.byHour, struHeatMapResult.struStartTime.byMinute,\
        struHeatMapResult.struStartTime.bySecond, struHeatMapResult.byTimeDiffFlag, struHeatMapResult.cStartTimeDifferenceH, struHeatMapResult.cStartTimeDifferenceM,
        struHeatMapResult.struEndTime.wYear, struHeatMapResult.struEndTime.byMonth, struHeatMapResult.struEndTime.byDay, \
		struHeatMapResult.struEndTime.byHour, struHeatMapResult.struEndTime.byMinute, struHeatMapResult.struEndTime.bySecond, \
        struHeatMapResult.cStopTimeDifferenceH, struHeatMapResult.cStopTimeDifferenceM,\
        struHeatMapResult.wArrayLine,\
		struHeatMapResult.wArrayColumn, cFilename, struHeatMapResult.dwMaxHeatMapValue, struHeatMapResult.dwMinHeatMapValue, struHeatMapResult.dwTimeHeatMapValue,\
        struHeatMapResult.byDetSceneID, struHeatMapResult.byBrokenNetHttp, struHeatMapResult.struDevInfo.byIvmsChannel, struHeatMapResult.wDevInfoIvmsChannelEx);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProVCAAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		         
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    LPNET_DVR_DEC_VCA_ALARM pStruVcaAlarm = (LPNET_DVR_DEC_VCA_ALARM)pAlarmInfo;
    sprintf(szInfoBuf, "COMM_ALARM_DEC_VCA dwDisplayNo[%d] bySubWinNo[%d] dwAlarmPicSize[%d]",\
        pStruVcaAlarm->dwDisplayNo, pStruVcaAlarm->bySubWinNo, pStruVcaAlarm->dwAlarmPicSize);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProLCDAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		         
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
	//char *szAlarmType[] = {"温度异常", "风扇异常", "屏幕离线" }; 
    LPNET_DVR_LCD_ALARM pStruLCDAlarm = (LPNET_DVR_LCD_ALARM)pAlarmInfo;
	//DWORD dwIndex = (pStruLCDAlarm->byAlarmType-1)%3;
	
	//     sprintf(szInfoBuf, "COMM_ALARM_LCD dwScreenID[%d], byOnOffLine[%d], byTempState[%d],byFanState[%d],byTemperature[%d] ",
	// 		pStruLCDAlarm->dwScreenID, pStruLCDAlarm->byOnOffLine,pStruLCDAlarm->byTempState, pStruLCDAlarm->byFanState, pStruLCDAlarm->byTemperature );
	
	sprintf(szInfoBuf, "COMM_ALARM_LCD dwScreenID[%d]", pStruLCDAlarm->dwScreenID);
	if (! pStruLCDAlarm->byOnOffLine) //离线
	{
		sprintf(szInfoBuf+strlen(szInfoBuf), ", 屏幕离线");
	}
	else
	{
		sprintf(szInfoBuf+strlen(szInfoBuf), ", 屏幕在线");
		sprintf(szInfoBuf+strlen(szInfoBuf), ", 板卡温度%s", (pStruLCDAlarm->byTempState==0)?"正常":"异常");
		sprintf(szInfoBuf+strlen(szInfoBuf), ", 风扇%s", (pStruLCDAlarm->byFanState==0)?"关":"开");
		sprintf(szInfoBuf+strlen(szInfoBuf), ", 板卡温度[%d]", pStruLCDAlarm->byTemperature);
		switch(pStruLCDAlarm->byFanException)
		{
		case 0:
			sprintf(szInfoBuf+strlen(szInfoBuf), ", 风扇异常状态: 不支持");
			break; 
		case 1:
			sprintf(szInfoBuf+strlen(szInfoBuf), ", 风扇异常状态: 正常");
			break; 
		case 2:
			sprintf(szInfoBuf+strlen(szInfoBuf), ", 风扇异常状态: 异常");
			break; 
		default:
			;
		}
	}
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}


//门禁主机报警 2014-07-23
void CClientDemoDlg::ProcAccessCardAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    char szLan[128] = {0};
    char szAlarmType[128] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
    NET_DVR_ACS_ALARM_INFO struAcsAlarmInfo = {0};
    memset(&struAcsAlarmInfo, 0, sizeof(struAcsAlarmInfo));
    memcpy(&struAcsAlarmInfo,pAlarmInfo, sizeof(struAcsAlarmInfo) ); 
    NET_DVR_LOG_V50 struFileInfo = {0};
    struFileInfo.dwMajorType = struAcsAlarmInfo.dwMajor; 
    struFileInfo.dwMinorType = struAcsAlarmInfo.dwMinor; 
    CString csTmp; 
    if (MAJOR_ALARM == struFileInfo.dwMajorType )
    {
        AlarmMinorTypeMap(struFileInfo, csTmp);
    }
    else if(MAJOR_OPERATION == struFileInfo.dwMajorType)
    {
        OperationMinorTypeMap(struFileInfo, csTmp);
    }         
    else if(MAJOR_EXCEPTION == struFileInfo.dwMajorType)
    {
        ExceptionMinorTypeMap(struFileInfo, csTmp);
    }
    else if(MAJOR_EVENT == struFileInfo.dwMajorType)
    {
        EventMinorTypeMap(struFileInfo, csTmp);     	
    }
 
    sprintf(szInfoBuf, "[%s] ", (LPCSTR)csTmp); 
 //   strcpy(szInfoBuf, szLan); 
    char szNetUser[sizeof(struAcsAlarmInfo.sNetUser)+1] = {0};
    memcpy(szNetUser, struAcsAlarmInfo.sNetUser, sizeof(struAcsAlarmInfo.sNetUser)); 
    //时间
    sprintf( szInfoBuf + strlen(szInfoBuf), " %4d-%2d-%d %2d:%2d:%2d [%s](%s)", struAcsAlarmInfo.struTime.dwYear, struAcsAlarmInfo.struTime.dwMonth ,\
        struAcsAlarmInfo.struTime.dwDay, struAcsAlarmInfo.struTime.dwHour, struAcsAlarmInfo.struTime.dwMinute, struAcsAlarmInfo.struTime.dwSecond, \
        struAcsAlarmInfo.struRemoteHostAddr.sIpV4, szNetUser); 
    if (struAcsAlarmInfo.struAcsEventInfo.byCardNo[0] != 0 )
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " CardNo:%s", (char *)struAcsAlarmInfo.struAcsEventInfo.byCardNo); 
    }
#ifdef DEMO_LAN_CN
    const char *szCardType[] = { "未知卡", "普通卡", "残疾人卡", "黑名单卡", "巡更卡", "胁迫卡", "超级卡", "来宾卡" };
#else
    const char *szCardType[] = { "unknow", "normalcard", "disabledcard", "blacklistcard", "nightwatchcard", "stresscard", "supercard", "guestcard" };
#endif
    BYTE byCardType = struAcsAlarmInfo.struAcsEventInfo.byCardType;
    if (byCardType > 0 && byCardType <= sizeof(szCardType) / sizeof(szCardType[0]))
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " CardType:%s", szCardType[byCardType]);
    }

    if (struAcsAlarmInfo.struAcsEventInfo.dwCardReaderNo != 0  )
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " CardReaderNo:%d", struAcsAlarmInfo.struAcsEventInfo.dwCardReaderNo); 
    }
    if (struAcsAlarmInfo.struAcsEventInfo.dwDoorNo != 0  )
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " DoorNo:%d", struAcsAlarmInfo.struAcsEventInfo.dwDoorNo); 
    }
    if (struAcsAlarmInfo.struAcsEventInfo.dwVerifyNo != 0  )
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " VerifyNo:%d", struAcsAlarmInfo.struAcsEventInfo.dwVerifyNo); 
    }
    if (struAcsAlarmInfo.struAcsEventInfo.dwAlarmInNo != 0  )
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " AlarmInNo:%d", struAcsAlarmInfo.struAcsEventInfo.dwAlarmInNo); 
    }
    if (struAcsAlarmInfo.struAcsEventInfo.dwAlarmOutNo != 0  )
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " AlarmOutNo:%d", struAcsAlarmInfo.struAcsEventInfo.dwAlarmOutNo); 
    }
    if (struAcsAlarmInfo.struAcsEventInfo.dwCaseSensorNo != 0  )
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " CaseSensorNo:%d", struAcsAlarmInfo.struAcsEventInfo.dwCaseSensorNo); 
    }
    if (struAcsAlarmInfo.struAcsEventInfo.dwRs485No != 0  )
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " Rs485No:%d", struAcsAlarmInfo.struAcsEventInfo.dwRs485No); 
    }
    if (struAcsAlarmInfo.struAcsEventInfo.dwMultiCardGroupNo != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " MultiCardGroupNo:%d", struAcsAlarmInfo.struAcsEventInfo.dwMultiCardGroupNo); 
    }
    if (struAcsAlarmInfo.struAcsEventInfo.byCardReaderKind != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " CardReaderKind:%d", struAcsAlarmInfo.struAcsEventInfo.byCardReaderKind); 
    }
	if (struAcsAlarmInfo.struAcsEventInfo.wAccessChannel >= 0)
	{
		sprintf(szInfoBuf + strlen(szInfoBuf), " wAccessChannel:%d", struAcsAlarmInfo.struAcsEventInfo.wAccessChannel); 
    }
    if (struAcsAlarmInfo.struAcsEventInfo.dwEmployeeNo != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " EmployeeNo:%d", struAcsAlarmInfo.struAcsEventInfo.dwEmployeeNo);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.byDeviceNo != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " DeviceNo:%d", struAcsAlarmInfo.struAcsEventInfo.byDeviceNo);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.byDistractControlNo != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " DistractControlNo:%d", struAcsAlarmInfo.struAcsEventInfo.byDistractControlNo);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.wLocalControllerID >= 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " wLocalControllerID:%d", struAcsAlarmInfo.struAcsEventInfo.wLocalControllerID);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.byInternetAccess >= 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " byInternetAccess:%d", struAcsAlarmInfo.struAcsEventInfo.byInternetAccess);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.byType >= 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " byType:%d", struAcsAlarmInfo.struAcsEventInfo.byType);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.bySwipeCardType != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " bySwipeCardType:%d", struAcsAlarmInfo.struAcsEventInfo.bySwipeCardType);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.byChannelControllerID != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " byChannelControllerID:%d", struAcsAlarmInfo.struAcsEventInfo.byChannelControllerID);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.byChannelControllerLampID != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " byChannelControllerLampID:%d", struAcsAlarmInfo.struAcsEventInfo.byChannelControllerLampID);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.byChannelControllerIRAdaptorID != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " byChannelControllerIRAdaptorID:%d", struAcsAlarmInfo.struAcsEventInfo.byChannelControllerIRAdaptorID);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.byChannelControllerIREmitterID != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " byChannelControllerIREmitterID:%d", struAcsAlarmInfo.struAcsEventInfo.byChannelControllerIREmitterID);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.byMACAddr[0] != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " MACAddr:%02x:%02x:%02x:%02x:%02x:%02x", struAcsAlarmInfo.struAcsEventInfo.byMACAddr[0], \
            struAcsAlarmInfo.struAcsEventInfo.byMACAddr[1], struAcsAlarmInfo.struAcsEventInfo.byMACAddr[2], struAcsAlarmInfo.struAcsEventInfo.byMACAddr[3], \
            struAcsAlarmInfo.struAcsEventInfo.byMACAddr[4], struAcsAlarmInfo.struAcsEventInfo.byMACAddr[5]);
    }
    if (struAcsAlarmInfo.struAcsEventInfo.dwSerialNo != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " dwSerialNo:%d", struAcsAlarmInfo.struAcsEventInfo.dwSerialNo);
    }

    if (struAcsAlarmInfo.wInductiveEventType != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " wInductiveEventType:%d", struAcsAlarmInfo.wInductiveEventType);
    }

    if (struAcsAlarmInfo.dwIOTChannelNo != 0)
    {
        sprintf(szInfoBuf + strlen(szInfoBuf), " dwIOTChannelNo:%d", struAcsAlarmInfo.dwIOTChannelNo);
    }


    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
    if (struAcsAlarmInfo.dwPicDataLen > 0 && struAcsAlarmInfo.pPicData != NULL)
    {
        int num = ulAlarmPic/1000+1;
        ulAlarmPic++;
        
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, struAcsAlarmInfo.struRemoteHostAddr.sIpV4/*g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName*/, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
        if (struAcsAlarmInfo.byPicTransType)
        {
            sprintf(cFilename, "%s\\LocalTime[%s]Major[%d]Minor[%d]NetUser[%s]_%d.txt", cFilename, chTime, \
                struAcsAlarmInfo.dwMajor, struAcsAlarmInfo.dwMinor, struAcsAlarmInfo.sNetUser, rand() % GetTickCount());
        }
        else
        {
            sprintf(cFilename, "%s\\LocalTime[%s]Major[%d]Minor[%d]NetUser[%s]_%d.png", cFilename, chTime, \
                struAcsAlarmInfo.dwMajor, struAcsAlarmInfo.dwMinor, struAcsAlarmInfo.sNetUser, rand() % GetTickCount());
        }

        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        AddLog(iDeviceIndex, ALARM_INFO_T, cFilename);
        WriteFile(hFile, struAcsAlarmInfo.pPicData, struAcsAlarmInfo.dwPicDataLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }
    if (struAcsAlarmInfo.pPicData != NULL)
    {
        delete [] (struAcsAlarmInfo.pPicData);
	}
}



//压线报警暂时不对外开放。
void CClientDemoDlg::ProcCrossLineData(WPARAM wParam, LPARAM lParam)//2013-09-27 压线报警
{
	char szInfoBuf[1024] = {0};
	char szTriggerTime[128] = {0};
	char szLan[128] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	NET_DVR_CROSSLINE_ALARM struCrossLine = {0};
	memcpy(&struCrossLine, pAlarmInfo, sizeof(struCrossLine));
	
	g_StringLanType(szLan, "压线报警","Cross Line");
	
	sprintf(szTriggerTime, "%d-%d-%d %d:%d:%d", struCrossLine.struTriggerTime.wYear, 
		struCrossLine.struTriggerTime.byMonth, struCrossLine.struTriggerTime.byDay,
		struCrossLine.struTriggerTime.byHour, struCrossLine.struTriggerTime.byMinute,
		struCrossLine.struTriggerTime.byDay);
	
	sprintf(szInfoBuf, "%s: (Trigger Time:[%s]  Device IP:[%s]  Port:[%d]  Device Channel:[%d]  Ivms Channel:[%d]  Plate Number:[%s]  Park Index:[%s])\n", 
		szLan, szTriggerTime, struCrossLine.struDevInfo.struDevIP.sIpV4, struCrossLine.struDevInfo.wPort, 
		struCrossLine.struDevInfo.byChannel, struCrossLine.struDevInfo.byIvmsChannel, struCrossLine.struParkInfo.sPlateNo,
		struCrossLine.struParkInfo.sParkIndex);
	
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}


void CClientDemoDlg::ProcAuxAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
	char sAlarmName[33] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
	
	NET_IPC_AUXALARM_RESULT struAuxAlarm = {0};
	memcpy(&struAuxAlarm, pAlarmInfo, sizeof(struAuxAlarm));
	
	//     g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
	//     ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
	//  打印信息
    CTime time = CTime::GetCurrentTime();
    
	if (struAuxAlarm.byAlarmType == IPC_AUXALARM_PIR)
	{
		memcpy(sAlarmName, struAuxAlarm.struAuxAlarm.struPIRAlarm.byAlarmName, NAME_LEN);
	}
	else if (struAuxAlarm.byAlarmType == IPC_AUXALARM_WIRELESS)
	{
		memcpy(sAlarmName, struAuxAlarm.struAuxAlarm.struWirelessAlarm.byAlarmName, NAME_LEN);
	}
	else
	{
		strncpy(sAlarmName, "Call help", NAME_LEN);
	}
	
    sprintf(szInfoBuf, "AuxAlarm Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] Type[%d] AlarmName[%s]\n",
        time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(),
        time.GetMinute(), time.GetSecond(), struAuxAlarm.byAlarmType, sAlarmName);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcTMEVehicleAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iWinIndex = -1;         
    int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	
    NET_DVR_TME_VEHICLE_RESULT  struTMEVehicle = {0};	
	memcpy(&struTMEVehicle, pAlarmInfo, sizeof(struTMEVehicle));
	
    sprintf(szInfoBuf, "TME Vehicle Alarm Region[%d]Country[%d]LaneID[%d]CamLaneId[%d]ChanIndex[%d]MonitoringSiteID[%s]DeviceID[%s]Dir[%d]PicNum[%d]License[%s]VehicleLogoRecog[%d]VehicleSubLogoRecog[%d]PassVehicleID[%s]CardNo[%s]SwipeTime[%s]Charge[%d]History[%d]LetPass[%d]", 
		struTMEVehicle.struPlateInfo.byRegion, struTMEVehicle.struPlateInfo.byCountry,
		struTMEVehicle.wLaneid, struTMEVehicle.byCamLaneId, struTMEVehicle.dwChanIndex, \
		struTMEVehicle.byMonitoringSiteID, struTMEVehicle.byDeviceID, \
		struTMEVehicle.byDir, struTMEVehicle.dwPicNum,struTMEVehicle.struPlateInfo.sLicense, \
		struTMEVehicle.struVehicleInfo.byVehicleLogoRecog, struTMEVehicle.struVehicleInfo.byVehicleSubLogoRecog, \
		struTMEVehicle.byPassVehicleID, struTMEVehicle.byCardNo, struTMEVehicle.bySwipeTime, struTMEVehicle.dwCharge,\
		struTMEVehicle.byHistory, struTMEVehicle.byLetPass);
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);	
    
    for (i = 0; i < 4; i++)
    {
        if (struTMEVehicle.struPicInfo[i].dwDataLen > 0 && struTMEVehicle.struPicInfo[i].pBuffer != NULL)
        {
            sprintf(szInfoBuf, "TME picture[%d]infoType[%d]RedLightTime[%d]AbsTime[%s]CloseUpType[%d]Len[%d]", i+1, struTMEVehicle.struPicInfo[i].byType,
                struTMEVehicle.struPicInfo[i].dwRedLightTime, struTMEVehicle.struPicInfo[i].byAbsTime, struTMEVehicle.struPicInfo[i].byCloseUpType,\
                struTMEVehicle.struPicInfo[i].dwDataLen);
            g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);	
            
            int num = ulAlarmPic/1000+1;
            ulAlarmPic++;
            
            char cFilename[256] = {0};
            HANDLE hFile;
            DWORD dwReturn;
            
            SYSTEMTIME t;
            GetLocalTime(&t);
            char chTime[128];
            sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
            
            sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
            if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFilename, NULL);
            }
            
            if (struTMEVehicle.struPicInfo[i].byDataType == 0)
            {
                sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
            } 
            else if (struTMEVehicle.struPicInfo[i].byDataType == 1)
            {
                sprintf(cFilename, "%s\\URL_LocalTime[%s]_%d.txt",cFilename, chTime,rand() % GetTickCount());
            }
            
            //sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime, i);
            hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return;
            }
            WriteFile(hFile, struTMEVehicle.struPicInfo[i].pBuffer, struTMEVehicle.struPicInfo[i].dwDataLen, &dwReturn, NULL);
            CloseHandle(hFile);
            hFile = NULL;
        }
	}    		
}

void CClientDemoDlg::ProcITSPlateAlarm(WPARAM wParam, LPARAM lParam)
{
    //有扩展的XML要打印，防止不够
	char szInfoBuf[2048 * 2] = {0};
	
	char *pAlarmInfo = (char *)(lParam);		
	int iWinIndex = -1;         
	int i = 0;
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_ITS_PLATE_RESULT  struPlateResult = {0};	
	memcpy(&struPlateResult, pAlarmInfo, sizeof(struPlateResult));
	//i = struPlateResult.byChanIndex;
	//if (iDeviceIndex != -1 && iDeviceIndex < 512)
	//{
	//	g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
	//	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
	//}

	// CString str = "";
	//新增区域和国家信息的打印 2015-01-21

    char sIllegalInfo[MAX_ILLEGAL_LEN/*64*/] = { 0 };
    if (1 == struPlateResult.byIllegalFromatType)
    {
        LPNET_ITS_ILLEGAL_INFO pIllegalInfo = (LPNET_ITS_ILLEGAL_INFO)struPlateResult.pIllegalInfoBuf;
        if (NULL != pIllegalInfo)
        {
            memcpy(sIllegalInfo, pIllegalInfo->byIllegalInfo, MAX_ILLEGAL_LEN);
        }

    }

	sprintf(szInfoBuf, "ITS Plate Alarm Channel NO[%d] DriveChan[%d] IllegalFromatType[%d]IllegalInfo[%s]Analysis[%d]YellowLabel[%d]DangerousVeh[%d]MatchNo[%d]IllegalType[%d]IllegalSubType[%s]\
	  MonitoringSiteID[%s]DeviceID[%s]Dir[%d]PicNum[%d] DetSceneID[%d] VehicleType[%d] DetectType[%d] Type[%d] DataType[%d] CloseUpType[%d]", \
        struPlateResult.byChanIndexEx * 256 + struPlateResult.byChanIndex, struPlateResult.byDriveChan, \
        struPlateResult.byIllegalFromatType, sIllegalInfo, \
	    struPlateResult.byDataAnalysis, struPlateResult.byYellowLabelCar, struPlateResult.byDangerousVehicles,\
	    struPlateResult.dwMatchNo, struPlateResult.wIllegalType,
	    struPlateResult.byIllegalSubType, struPlateResult.byMonitoringSiteID, struPlateResult.byDeviceID,
	    struPlateResult.byDir, struPlateResult.dwPicNum, struPlateResult.byDetSceneID, struPlateResult.byVehicleType, struPlateResult.byDetectType, \
		struPlateResult.struPicInfo->byType, struPlateResult.struPicInfo->byDataType, struPlateResult.struPicInfo->byCloseUpType);
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);	

    sprintf(szInfoBuf, "ITS Plate Alarm PlateInfo PlateType[%d]Color[%d]Bright[%d]LicenseLen[%d]EntireBelieve[%d]Region[%d]Country[%d]Area[%d]PlateSize[%d]PlateCategory[%s]License[%s]PlateRect[x-%f y-%f w-%f h-%f] \
       VehicleInfo:Index[%d]VehicleType[%d] Color[%d] RadarState[%d] Speed[%d] VehicleLogoRecog[%d] VehicleSubLogoRecog[%d] VehicleModel[%d]", \
       struPlateResult.struPlateInfo.byPlateType, struPlateResult.struPlateInfo.byColor, struPlateResult.struPlateInfo.byBright,
       struPlateResult.struPlateInfo.byLicenseLen, struPlateResult.struPlateInfo.byEntireBelieve, struPlateResult.struPlateInfo.byRegion, struPlateResult.struPlateInfo.byCountry,
       struPlateResult.struPlateInfo.byArea, struPlateResult.struPlateInfo.byPlateSize, struPlateResult.struPlateInfo.sPlateCategory,
       struPlateResult.struPlateInfo.sLicense, struPlateResult.struPlateInfo.struPlateRect.fX, struPlateResult.struPlateInfo.struPlateRect.fY, \
       struPlateResult.struPlateInfo.struPlateRect.fWidth, struPlateResult.struPlateInfo.struPlateRect.fHeight, struPlateResult.struVehicleInfo.dwIndex,\
       struPlateResult.struVehicleInfo.byVehicleType, struPlateResult.struVehicleInfo.byColor,
       struPlateResult.struVehicleInfo.byRadarState, struPlateResult.struVehicleInfo.wSpeed, \
       struPlateResult.struVehicleInfo.wVehicleLogoRecog, struPlateResult.struVehicleInfo.byVehicleSubLogoRecog, \
       struPlateResult.struVehicleInfo.byVehicleModel);
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

	for (i = 0; i < 6; i++)
	{
		if (struPlateResult.struPicInfo[i].dwDataLen > 0 && struPlateResult.struPicInfo[i].pBuffer != NULL)
		{
			sprintf(szInfoBuf, "ITS picture[%d] info Type[%d] RedLightTime[%d] AbsTime[%s %2.2d%2.2d] flag[%d]  CloseUpType[%d]PlateRect[x-%f y-%f w-%f h-%f]PlateRecgRect[x-%f y-%f w-%f h-%f]", i+1, struPlateResult.struPicInfo[i].byType,
                struPlateResult.struPicInfo[i].dwRedLightTime, struPlateResult.struPicInfo[i].byAbsTime, struPlateResult.struPicInfo[i].cTimeDifferenceH, struPlateResult.struPicInfo[i].cTimeDifferenceM, struPlateResult.struPicInfo[i].byTimeDiffFlag,
                struPlateResult.struPicInfo[i].byCloseUpType, struPlateResult.struPicInfo[i].struPlateRect.fX, struPlateResult.struPicInfo[i].struPlateRect.fY, struPlateResult.struPicInfo[i].struPlateRect.fWidth, struPlateResult.struPicInfo[i].struPlateRect.fHeight,
                struPlateResult.struPicInfo[i].struPlateRecgRect.fX, struPlateResult.struPicInfo[i].struPlateRecgRect.fY, struPlateResult.struPicInfo[i].struPlateRecgRect.fWidth, struPlateResult.struPicInfo[i].struPlateRecgRect.fHeight);
			g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);	
			
			int num = ulAlarmPic/1000+1;
			ulAlarmPic++;
			
			char cFilename[256] = {0};
			HANDLE hFile;
			DWORD dwReturn;
			
			SYSTEMTIME t;
			GetLocalTime(&t);
			char chTime[128];
            sprintf(chTime, "%s flag[%d] %2.2d%2.2d", struPlateResult.struPicInfo[i].byAbsTime,
                struPlateResult.struPicInfo[i].byTimeDiffFlag, struPlateResult.struPicInfo[i].cTimeDifferenceH, struPlateResult.struPicInfo[i].cTimeDifferenceM);
			if (iDeviceIndex != -1 && iDeviceIndex < 512)
			{
				sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
			}
			else
			{
				sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, num);
			}
			if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(cFilename, NULL);
			}
            
			char cPicType[256] = {0};
			if (struPlateResult.struPicInfo[i].byDataType == 0)
			{
				if (0 == struPlateResult.struPicInfo[i].byType)
				{
					sprintf(cPicType,"License");
				} 
				else if (1 == struPlateResult.struPicInfo[i].byType)
				{
					sprintf(cPicType,"Scene");
				}
				sprintf(cFilename, "%s\\%sLocalTime[%s]_%d.jpg",cFilename, cPicType, chTime,rand() % GetTickCount());
			} 
			else if (struPlateResult.struPicInfo[i].byDataType == 1)
			{
				if (0 == struPlateResult.struPicInfo[i].byType)
				{
					sprintf(cPicType,"License");
				} 
				else if (1 == struPlateResult.struPicInfo[i].byType)
				{
					sprintf(cPicType,"Scene");
				}
				sprintf(cFilename, "%s\\%sURL_LocalTime[%s]_%d.txt",cFilename, cPicType, chTime,rand() % GetTickCount());
			}
			
			//sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime, i);
			hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				return;
			}
			WriteFile(hFile, struPlateResult.struPicInfo[i].pBuffer, struPlateResult.struPicInfo[i].dwDataLen, &dwReturn, NULL);
			CloseHandle(hFile);
			hFile = NULL;
		}
	}
    if (struPlateResult.struPlateInfo.dwXmlLen > 0)
    {
        char sXMLFileName[256] = { 0 };
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;
        if (iDeviceIndex != -1 && iDeviceIndex < 512)
        {
            sprintf(sXMLFileName, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        }
        else
        {
            sprintf(sXMLFileName, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, num);
        }
        if (GetFileAttributes(sXMLFileName) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(sXMLFileName, NULL);
        }
        SYSTEMTIME tNow = { 0 };
        GetLocalTime(&tNow);
        sprintf(sXMLFileName, "%s\\ANPR_XML[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d].xml", 
            sXMLFileName, tNow.wYear, tNow.wMonth, tNow.wDay, tNow.wHour, tNow.wMinute, tNow.wSecond, tNow.wMilliseconds);

        HANDLE hXMLFile = CreateFile(sXMLFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hXMLFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwReturn = 0;
        WriteFile(hXMLFile, struPlateResult.struPlateInfo.pXmlBuf, struPlateResult.struPlateInfo.dwXmlLen, &dwReturn, NULL);
        CloseHandle(hXMLFile);
        hXMLFile = NULL;

        sprintf(szInfoBuf, "ANPR XML Block Path:%s", sXMLFileName);
        szInfoBuf[sizeof(szInfoBuf) - 1] = 0;   //防止溢出
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    }
}

void CClientDemoDlg::ProcITSPlateAlarmV50(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iWinIndex = -1;         
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    if (iDeviceIndex < 0 || iDeviceIndex >= MAX_DEVICES)
    {
        return;
    }
    
    NET_DVR_PLATE_RESULT_V50  struPlateResult = {0};	
    memcpy(&struPlateResult, pAlarmInfo, sizeof(struPlateResult));
    i = struPlateResult.byChanIndex;
    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
    ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
    
    // CString str = "";
    //新增区域和国家信息的打印 2015-01-21
    
    sprintf(szInfoBuf, "ITS Plate Alarm V50;IsOverWeight[%d]AxleNum[%d]AxleModel[%d]OverWeight[%f]Weight[%f]LimitWeight[%f]AxleLen[%f]DevDescInfo[%s]\
          Region[%d]Country[%d]MatchNo[%d]DriveChan[%d]IllegalType[%d]IllegalSubType[%s]\
          MonitoringSiteID[%s]DeviceID[%s]Dir[%d]PicNum[%d]License[%s]VehicleLogoRecog[%d]\
          VehicleSubLogoRecog[%d]DetSceneID[%d]VehicleType[%d]DetectType[%d]\
          Type[%d]DataType[%d]CloseUpType[%d]", 
          struPlateResult.struWeightResult.byIsOverWeight, struPlateResult.struWeightResult.byAxleNum, struPlateResult.struWeightResult.wAxleModel,
          struPlateResult.struWeightResult.fOverWeight,struPlateResult.struWeightResult.fWeight,
          struPlateResult.struWeightResult.fLimitWeight,struPlateResult.struWeightResult.fAxleLen,
          struPlateResult.struWeightResult.sDevDescInfo,
          struPlateResult.struPlateInfo.byRegion, struPlateResult.struPlateInfo.byCountry,
          struPlateResult.dwMatchNo, struPlateResult.byDriveChan, struPlateResult.wIllegalType,
          struPlateResult.byIllegalSubType, struPlateResult.byMonitoringSiteID, struPlateResult.byDeviceID,
          struPlateResult.byDir, struPlateResult.dwPicNum,struPlateResult.struPlateInfo.sLicense, \
          struPlateResult.struVehicleInfo.byVehicleLogoRecog, struPlateResult.struVehicleInfo.byVehicleSubLogoRecog, \
          struPlateResult.byDetSceneID, struPlateResult.byVehicleType, struPlateResult.byDetectType, \
          struPlateResult.struPicInfo->byType, struPlateResult.struPicInfo->byDataType, struPlateResult.struPicInfo->byCloseUpType);
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);	

    std::string strInfo = "AxleWeight[";
    for (i = 0; i < ARRAY_SIZE(struPlateResult.struWeightResult.wAxleWeight); ++i)
    {
        sprintf(szInfoBuf, " %d", struPlateResult.struWeightResult.wAxleWeight[i]);
        strInfo += szInfoBuf;
    }
    strInfo += "]\nAxleDistance[";
    for (i = 0; i < ARRAY_SIZE(struPlateResult.struWeightResult.wAxleDistance); ++i)
    {
        sprintf(szInfoBuf, " %d", struPlateResult.struWeightResult.wAxleDistance[i]);
        strInfo += szInfoBuf;
    }
    strInfo += "]";
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, strInfo.c_str());
    
    for (i = 0; i < 6; i++)
    {
        if (struPlateResult.struPicInfo[i].dwDataLen > 0 && struPlateResult.struPicInfo[i].pBuffer != NULL)
        {
            sprintf(szInfoBuf, "ITS picture[%d] info Type[%d] RedLightTime[%d] AbsTime[%s]  CloseUpType[%d]", i+1, struPlateResult.struPicInfo[i].byType,
                struPlateResult.struPicInfo[i].dwRedLightTime, struPlateResult.struPicInfo[i].byAbsTime, struPlateResult.struPicInfo[i].byCloseUpType);
            g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);	
            
            int num = ulAlarmPic/1000+1;
            ulAlarmPic++;
            
            char cFilename[256] = {0};
            HANDLE hFile;
            DWORD dwReturn;
            
            SYSTEMTIME t;
            GetLocalTime(&t);
            char chTime[128];
            sprintf(chTime, "%s", struPlateResult.struPicInfo[i].byAbsTime);
            
            sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
            if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFilename, NULL);
            }
            
 			char cPicType[256] = {0};
			if (struPlateResult.struPicInfo[i].byDataType == 0)
			{
				if (0 == struPlateResult.struPicInfo[i].byType)
				{
					sprintf(cPicType,"License");
				} 
				else if (1 == struPlateResult.struPicInfo[i].byType)
				{
					sprintf(cPicType,"Scene");
				}
				sprintf(cFilename, "%s\\%sLocalTime[%s]_%d.jpg",cFilename, cPicType, chTime,rand() % GetTickCount());
			} 
			else if (struPlateResult.struPicInfo[i].byDataType == 1)
			{
				if (0 == struPlateResult.struPicInfo[i].byType)
				{
					sprintf(cPicType,"License");
				} 
				else if (1 == struPlateResult.struPicInfo[i].byType)
				{
					sprintf(cPicType,"Scene");
				}
				sprintf(cFilename, "%s\\%sURL_LocalTime[%s]_%d.txt",cFilename, cPicType, chTime,rand() % GetTickCount());
			}
            
            //sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime, i);
            hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return;
            }
            WriteFile(hFile, struPlateResult.struPicInfo[i].pBuffer, struPlateResult.struPicInfo[i].dwDataLen, &dwReturn, NULL);
            CloseHandle(hFile);
            hFile = NULL;
        }
	}  
}

void CClientDemoDlg::ProcITSGateVehicle(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;

	NET_ITS_GATE_VEHICLE  struGateVehicle = {0};
	memcpy(&struGateVehicle, pAlarmInfo, sizeof(struGateVehicle));
	
	sprintf(szInfoBuf, "ITS Gate Vehicle MatchNo[%d] LaneID[%d] CamLaneId[%d] ChanIndex[%d] MonitoringSiteID[%s] DeviceID[%s] Dir[%d] PicNum[%d]",\
		struGateVehicle.dwMatchNo, struGateVehicle.wLaneid, struGateVehicle.byCamLaneId, struGateVehicle.dwChanIndex,\
		struGateVehicle.byMonitoringSiteID, struGateVehicle.byDeviceID, struGateVehicle.byDir, struGateVehicle.dwPicNum);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

	for (i = 0; i < 4; i++)
	{
		if (struGateVehicle.struPicInfo[i].dwDataLen > 0 && struGateVehicle.struPicInfo[i].pBuffer != NULL)
		{
			sprintf(szInfoBuf, "ITS picture[%d] info Type[%d] RedLightTime[%d] AbsTime[%s]", i+1, struGateVehicle.struPicInfo[i].byType,
				struGateVehicle.struPicInfo[i].dwRedLightTime, struGateVehicle.struPicInfo[i].byAbsTime);
			g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);	
			
			int num = ulAlarmPic/1000+1;
			ulAlarmPic++;
			
			char cFilename[256] = {0};
			HANDLE hFile;
			DWORD dwReturn;
			
			SYSTEMTIME t;
			GetLocalTime(&t);
			char chTime[128];
            sprintf(chTime, "%s", struGateVehicle.struPicInfo[i].byAbsTime);
			
			sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
			if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(cFilename, NULL);
			}
			
			sprintf(cFilename, "%s\\ITSGateVehicle[%s]_%d.jpg",cFilename, chTime, i);
			hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			
			if (hFile == INVALID_HANDLE_VALUE)
			{
				return;
			}
			WriteFile(hFile, struGateVehicle.struPicInfo[i].pBuffer, struGateVehicle.struPicInfo[i].dwDataLen, &dwReturn, NULL);
			CloseHandle(hFile);
			hFile = NULL;
		}
	}
}

void CClientDemoDlg::ProcITSGateFace(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	
	NET_ITS_GATE_FACE  struGateFace = {0};
	memcpy(&struGateFace, pAlarmInfo, sizeof(struGateFace));

	sprintf(szInfoBuf, "ITS Gate Face Laneid[%d] CamLaneId[%d] MonitoringSiteID[%s] DeviceID[%s]",\
		struGateFace.wLaneid, struGateFace.byCamLaneId, struGateFace.byMonitoringSiteID, struGateFace.byDeviceID);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

	//  打印信息
    NET_DVR_TIME  struAbsTime = {0};
    struAbsTime.dwYear = GET_YEAR(struGateFace.struFaceInfo.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struGateFace.struFaceInfo.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struGateFace.struFaceInfo.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struGateFace.struFaceInfo.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struGateFace.struFaceInfo.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struGateFace.struFaceInfo.dwAbsTime);
	
    sprintf(szInfoBuf, "Face Snap alarm Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] FaceID[%d]\n",
        struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour,
        struAbsTime.dwMinute, struAbsTime.dwSecond, struGateFace.struFaceInfo.dwFacePicID);
    AddLog(m_iCurDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
    if (struGateFace.struFaceInfo.dwFacePicLen > 0 && struGateFace.struFaceInfo.pBuffer1 != NULL)
    {
        int num = ulAlarmPic/1000+1;
        ulAlarmPic++;
        
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
        sprintf(cFilename, "%s\\ITSGateFace[%s].jpg",cFilename, chTime);
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struGateFace.struFaceInfo.pBuffer1, struGateFace.struFaceInfo.dwFacePicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
	}
	
	if (struGateFace.struFaceInfo.dwBackgroundPicLen > 0 && struGateFace.struFaceInfo.pBuffer2 != NULL)
    {
        int num = ulAlarmPic/1000+1;
        ulAlarmPic++;
        
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
        sprintf(cFilename, "%s\\BackgroundPic[%s].jpg",cFilename, chTime);
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struGateFace.struFaceInfo.pBuffer2, struGateFace.struFaceInfo.dwBackgroundPicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
	}
	
	if (struGateFace.struFaceInfo.pBuffer1 != NULL)
	{
		delete []struGateFace.struFaceInfo.pBuffer1;
		struGateFace.struFaceInfo.pBuffer1 = NULL;
	}
	
	if (struGateFace.struFaceInfo.pBuffer2 != NULL)
	{
		delete []struGateFace.struFaceInfo.pBuffer2;
		struGateFace.struFaceInfo.pBuffer2 = NULL;
	}
}

void CClientDemoDlg::ProcITSParkVehicle(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	
	NET_ITS_PARK_VEHICLE  struParkVehicle = {0};
	memcpy(&struParkVehicle, pAlarmInfo, sizeof(struParkVehicle));

	sprintf(szInfoBuf, "ITS Park Vehicle LocationStatus[%d] MonitoringSiteID[%s] DeviceID[%s] PicNum[%d] struPlateRect0[%f,%f,%f,%f] struPlateRect1[%f,%f,%f,%f]",\
		struParkVehicle.byLocationStatus, struParkVehicle.byMonitoringSiteID, struParkVehicle.byDeviceID, struParkVehicle.dwPicNum,
        struParkVehicle.struPicInfo[0].struPlateRect.fX, struParkVehicle.struPicInfo[0].struPlateRect.fY,
        struParkVehicle.struPicInfo[0].struPlateRect.fWidth, struParkVehicle.struPicInfo[0].struPlateRect.fHeight,
        struParkVehicle.struPicInfo[1].struPlateRect.fX, struParkVehicle.struPicInfo[1].struPlateRect.fY,
        struParkVehicle.struPicInfo[1].struPlateRect.fWidth, struParkVehicle.struPicInfo[1].struPlateRect.fHeight);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

	for (i = 0; i < 2; i++)
	{
		if (struParkVehicle.struPicInfo[i].dwDataLen > 0 && struParkVehicle.struPicInfo[i].pBuffer != NULL)
		{
			sprintf(szInfoBuf, "ITS picture[%d] info Type[%d] RedLightTime[%d] AbsTime[%s]", i+1, struParkVehicle.struPicInfo[i].byType,
				struParkVehicle.struPicInfo[i].dwRedLightTime, struParkVehicle.struPicInfo[i].byAbsTime);
			g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);	
			
			int num = ulAlarmPic/1000+1;
			ulAlarmPic++;
			
			char cFilename[256] = {0};
			HANDLE hFile;
			DWORD dwReturn;
			
			SYSTEMTIME t;
			GetLocalTime(&t);
			char chTime[128];
            sprintf(chTime, "%s", struParkVehicle.struPicInfo[i].byAbsTime);
			
            sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, num);
			if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(cFilename, NULL);
			}
			
			sprintf(cFilename, "%s\\LocalTimeITSParkVehicle[%s]_%d.jpg",cFilename, chTime, i);
			hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				return;
			}
			WriteFile(hFile, struParkVehicle.struPicInfo[i].pBuffer, struParkVehicle.struPicInfo[i].dwDataLen, &dwReturn, NULL);
			CloseHandle(hFile);
			hFile = NULL;
		}
	}
}

void CClientDemoDlg::ProcITSBalckListInfo(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;

	NET_ITS_ECT_BLACKLIST struBlackList = {0};
	memcpy(&struBlackList, pAlarmInfo, sizeof(struBlackList));
	
	sprintf(szInfoBuf, "ITS BLACK LIST INFO Channel[%d] LogicalLaneNo[%d] LaneName[%d] License[%s]",\
		struBlackList.dwChannel, struBlackList.bylogicalLaneNo, struBlackList.bylogicalLaneNo, struBlackList.struPlateInfo.sLicense);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcVehicleControlListDS(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "车辆黑白名单数据需要同步报警上传", "Vehicle control list");
    NET_DVR_VEHICLE_CONTROL_LIST_DSALARM  struVehicleControl;
    memset(&struVehicleControl, 0, sizeof(struVehicleControl));
    memcpy(&struVehicleControl, pAlarmInfo, sizeof(struVehicleControl));
    LPNET_DVR_VEHICLE_CONTROL_LIST_DSALARM pVehicle = (LPNET_DVR_VEHICLE_CONTROL_LIST_DSALARM)(pAlarmInfo);

    sprintf(szInfoBuf, "%s:  Data index[%d] sOperateIndex[%s]", \
        szLan, pVehicle->dwDataIndex, pVehicle->sOperateIndex);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcVehicleControl(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "黑白名单车辆报警上传", "Vehicle control");

    LPNET_DVR_VEHICLE_CONTROL_ALARM pVehicle = (LPNET_DVR_VEHICLE_CONTROL_ALARM)(pAlarmInfo);
    sprintf(szInfoBuf, "time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d flag[%d] %2.2d%2.2d] %s:  byListType[%d] byPlateType[%d] byPlateColor[%d] sLicense[%s] dwChannel[%d]byPicTransType[%d]", \
        pVehicle->struAlarmTime.wYear, pVehicle->struAlarmTime.byMonth, pVehicle->struAlarmTime.byDay, 
        pVehicle->struAlarmTime.byHour, pVehicle->struAlarmTime.byMinute, pVehicle->struAlarmTime.bySecond,
        pVehicle->struAlarmTime.byISO8601, pVehicle->struAlarmTime.cTimeDifferenceH, pVehicle->struAlarmTime.cTimeDifferenceM,
        szLan, pVehicle->byListType, pVehicle->byPlateType, pVehicle->byPlateColor, pVehicle->sLicense, pVehicle->dwChannel, pVehicle->byPicTransType);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    if (pVehicle->dwPicDataLen > 0 && pVehicle->pPicData != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "blackwhitelist");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        if (pVehicle->byPicTransType)
        {
            sprintf(cFilename, "%s\\LocalTime[%s]_%d.txt", cFilename, chTime, rand() % GetTickCount());
        }
        else
        {
            sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());
        }

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, pVehicle->pPicData, pVehicle->dwPicDataLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < pVehicle->dwPicDataLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Plate Picture Wtite to File Fail.System Error:%d, dwPlateBufferLen:%d, dwWrittenBytes:%d ", dwError, pVehicle->dwPicDataLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    //释放图片内存
    if (pVehicle->pPicData != NULL)
    {
        delete[](pVehicle->pPicData);
        pVehicle->pPicData = NULL;
    }
}


void CClientDemoDlg::ProcITSRoadException(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iWinIndex = -1;         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_ITS_ROADINFO  struResult = {0};	
	memcpy(&struResult, pAlarmInfo, sizeof(struResult));
	g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
	
	// CString str = "";
    sprintf(szInfoBuf, "ITS Road Exception ChanNo[%d]DeviceNum[%d]", 
		struResult.dwChannel, struResult.dwDeviceNum);
	
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
       

    char sInfo[10240] = {0};
    sprintf(sInfo, "NET_ITS_ROADINFO \r\n");
    sprintf(sInfo, "%s dwChannel=%d \r\n", sInfo, struResult.dwChannel);
    sprintf(sInfo, "%s byTriggerMode=%d \r\n", sInfo, struResult.byTriggerMode);
    sprintf(sInfo, "%s dwDeviceNum=%d \r\n", sInfo, struResult.dwDeviceNum);
    sprintf(sInfo, "%s byMonitoringSiteID=%s \r\n", sInfo, struResult.byMonitoringSiteID);
    sprintf(sInfo, "%s byRoadInfo=%s \r\n", sInfo, struResult.byRoadInfo);

    for (i = 0; i < ITS_MAX_DEVICE_NUM; i++)
    {
        sprintf(sInfo, "%s NET_ITS_SINGLE_DEVICE_INFO[i] \r\n", sInfo, i);  
        sprintf(sInfo, "%s dwDeviceType=%d \r\n", sInfo, struResult.struSingleDevice[i].dwDeviceType);
        sprintf(sInfo, "%s dwDirID=%d \r\n", sInfo, struResult.struSingleDevice[i].dwDirID);
        sprintf(sInfo, "%s dwLaneID=%d \r\n", sInfo, struResult.struSingleDevice[i].dwLaneID);
        sprintf(sInfo, "%s dwDeviceState=%d \r\n", sInfo, struResult.struSingleDevice[i].dwDeviceState);
        sprintf(sInfo, "%s byDeviceName=%s \r\n", sInfo, struResult.struSingleDevice[i].byDeviceName);
        sprintf(sInfo, "%s byDeviceID=%s \r\n", sInfo, struResult.struSingleDevice[i].byDeviceID);
        sprintf(sInfo, "%s struTriggerTime=%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d \r\n", sInfo, \
            struResult.struSingleDevice[i].struTriggerTime.wYear, struResult.struSingleDevice[i].struTriggerTime.byMonth,\
            struResult.struSingleDevice[i].struTriggerTime.byDay, struResult.struSingleDevice[i].struTriggerTime.byHour,\
            struResult.struSingleDevice[i].struTriggerTime.byMinute, struResult.struSingleDevice[i].struTriggerTime.bySecond,\
            struResult.struSingleDevice[i].struTriggerTime.wMilliSec);
        sprintf(sInfo, "%s byRelateChan=%d \r\n", sInfo, struResult.struSingleDevice[i].byRelateChan);
    }


    char cFilename[256] = {0};
    DWORD dwWrittenBytes = 0;
    HANDLE hFile = NULL;
    SYSTEMTIME t;
    
    GetLocalTime(&t);
    char chLocalTime[128];
    sprintf(chLocalTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[ITSRoadException]");
    if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
    {
        CreateDirectory(cFilename, NULL);
    }
    
    sprintf(cFilename, "%s\\LocalTime[%s].txt",cFilename, chLocalTime);
    
    hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return;
    }
    DWORD dwRet = WriteFile(hFile, sInfo, 10240, &dwWrittenBytes, NULL);
    CloseHandle(hFile);
    hFile = NULL;
}

/*********************************************************
Function:	OnWMProcAlarm
Desc:		process alarm information when 
Input:	none
Output:	none
Return:	none
**********************************************************/
LRESULT CClientDemoDlg::OnWMProcAlarm(WPARAM wParam, LPARAM lParam)
{	
	//EnterCriticalSection(&g_cs);

	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	if (iDeviceIndex < 0 && iDeviceIndex >= MAX_DEVICES)
	{
		delete [] pAlarmInfo;
		delete pAlarmDev;
		return NULL;
	}
	char szLan[128] ={0};
	char szInfoBuf[1024] = {0};
	switch (pAlarmDev->lCommand)
	{
    case COMM_ISAPI_ALARM:
        ProcISAPIAlarm(wParam, lParam);
        break;
	case COMM_IPC_AUXALARM_RESULT:
		ProcAuxAlarm(wParam, lParam);
		break;
	case COMM_ALARM:
		ProcAlarm(wParam, lParam);
		break;
	case COMM_ALARM_V30:
		ProcAlarmV30(wParam, lParam);
		break;
	case COMM_ALARM_V40:
        ProcAlarmV40(wParam, lParam);
        break;
	case COMM_TRADEINFO:
		NET_DVR_TRADEINFO m_TradeInfo;
		memcpy(&m_TradeInfo, pAlarmInfo, sizeof(NET_DVR_TRADEINFO));
		g_StringLanType(szLan, "收到卡号信息", "receive trade card number");
		sprintf(szInfoBuf, "%s%s", m_TradeInfo.CardNumber);
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);  
		break;
	case COMM_IPCCFG://input parameters modified
		ProcIPCfgAlarm(wParam, lParam);
		break;
	case COMM_IPCCFG_V31:
		ProcIPCfgAlarmV31(wParam, lParam);
		break;
	case COMM_ALARM_RULE:
		ProcRuleAlarm(wParam, lParam);
		break;
    case COMM_ALARM_PDC:
        ProcPdcAlarm(wParam, lParam);
        break;
    case COMM_SENSOR_VALUE_UPLOAD:
        ProcSensorValueUpload(wParam, lParam);
        break;
    case COMM_SENSOR_ALARM:
        ProcSensorAlarm(wParam, lParam);
        break;
    case COMM_ALARM_AID:
        ProcAidAlarm(wParam, lParam);
        break;
    case COMM_ALARM_TPS:
        ProcTpsAlarm(wParam, lParam);
        break;
	case COMM_ALARM_AID_V41:
		ProcAidAlarmV41(wParam,lParam);
		break;
    case COMM_ALARM_TPS_REAL_TIME:
        ProcTpsRealtime(wParam, lParam);
        break;
    case COMM_ALARM_TPS_STATISTICS:
        ProcTpsStatistics(wParam, lParam);
        break;
	case COMM_ALARM_TFS:
		ProcTfsAlarm(wParam,lParam);
		break;
	case COMM_ALARM_TPS_V41:
		ProcTpsAlarmV41(wParam,lParam);
		break;
    case COMM_ALARM_FACE:
        ProcFaceDetectAlarm(wParam, lParam);
        break;
	case COMM_UPLOAD_FACESNAP_RESULT:
		ProcFaceSnapAlarm(wParam, lParam);
		break;
	case COMM_ALARM_FACE_DETECTION:
		ProcFaceDetectionAlarm(wParam, lParam);
		break;
	case COMM_SNAP_MATCH_ALARM:
		ProcFaceSnapMatchAlarm(wParam, lParam);
		break;
	case COMM_ALARM_TARGET_LEFT_REGION:
		ProcTargetLeftRegionAlarm(wParam, lParam);
		break;
    case COMM_RULE_INFO_UPLOAD:
        ProcRuleInfoUpload(wParam, lParam);
        break;
	//2010-06-01
	case COMM_ALARM_VIDEOPLATFORM:
		memset(&m_struVideoPlatform, 0, sizeof(m_struVideoPlatform));
		memcpy(&m_struVideoPlatform, pAlarmInfo, sizeof(m_struVideoPlatform));

		if (m_struVideoPlatform.byAlarmType == 0)
		{
			g_StringLanType(szLan, "收到视频综合平台拔出子板报警,起始槽位号:", "receive videoplatform pull board alarm, start slotnum:");
			sprintf(szInfoBuf, "%s%d", szLan, m_struVideoPlatform.bySubSystemChan[0]);
		}
		else if (m_struVideoPlatform.byAlarmType == 1)
		{
			g_StringLanType(szLan, "收到视频综合平台插入子板报警,起始槽位号:", "receive videoplatform push board alarm, start slotnum:");
			sprintf(szInfoBuf, "%s%d", szLan, m_struVideoPlatform.bySubSystemChan[0]);
		}
		else if (m_struVideoPlatform.byAlarmType == 2)
		{
			g_StringLanType(szLan, "收到视频综合平台温度超上限报警,温度:", "receive videoplatform temperature uplimited alarm, temp:");
			sprintf(szInfoBuf, "%s%d.%d", szLan, (m_struVideoPlatform.iTemperature / 100), m_struVideoPlatform.iTemperature % 100);
		}
		else if (m_struVideoPlatform.byAlarmType == 3)
		{
			g_StringLanType(szLan, "收到视频综合平台温度超下限报警,温度:", "receive videoplatform temperature downlimited alarm, temp:");
			sprintf(szInfoBuf, "%s%d.%d", szLan, (m_struVideoPlatform.iTemperature / 100), m_struVideoPlatform.iTemperature % 100);
		}
        else if (m_struVideoPlatform.byAlarmType == 4)
        {
            g_StringLanType(szLan, "收到视频综合平台风扇状态异常报警,风扇号:", "receive videoplatform fan exception alarm, fan num:");
            sprintf(szInfoBuf, "%s", szLan);
            
            for (int i = 0; i < 32; i++)
            {
                sprintf(&szInfoBuf[i + strlen(szLan)], "%d", m_struVideoPlatform.byFanSequence[i]);                
            }
        }
        else if (m_struVideoPlatform.byAlarmType == 5)
        {
            g_StringLanType(szLan, "收到视频综合平台子系统异常报警,子系统号:", "receive videoplatform sub system exception alarm, sub system slot:");
            sprintf(szInfoBuf, "%s%d", szLan, m_struVideoPlatform.bySubSystemChan[0]);
        }
        else if (m_struVideoPlatform.byAlarmType == 6)
        {
            g_StringLanType(szLan, "收到视频综合平台非法访问报警", "receive videoplatform illegal visit alarm");
            sprintf(szInfoBuf, "%s", szLan);
        }

		if (m_struVideoPlatform.byBoardNum != 0xff)
		{
			g_StringLanType(szLan, "子板号:", "Board number:");
			sprintf(szInfoBuf, "%s%s%d", szInfoBuf, szLan, m_struVideoPlatform.byBoardNum);
		}

		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);  
		break;
    case COMM_ALARM_ALARMHOST:
        //2010-06-30
        ProcAlarmHostAlarm(wParam, lParam);
        break;
    case COMM_SWITCH_ALARM:
        ProcSwitchAlarm(wParam, lParam);
        break;
    case COMM_ALARMHOST_EXCEPTION:
        ProcAlarmHostException(wParam, lParam);
        break;
	case COMM_ALARM_DEVICE:
		ProcDeviceAlarm(wParam, lParam);
		break;
    case COMM_ALARM_DEVICE_V40:
        ProcDeviceV40Alarm(wParam, lParam);
		break;
	case COMM_ALARM_CVR:
		ProcCVRAlarm(wParam, lParam);
		break;
	case COMM_ALARMHOST_SAFETYCABINSTATE:
		ProcAlarmHostSatetyCabinState(wParam, lParam);
		break;
	case COMM_ALARMHOST_ALARMOUTSTATUS:
		ProcAlarmHostAlarmoutStatus(wParam, lParam);
		break;
	case COMM_ITS_PLATE_RESULT:
		ProcITSPlateAlarm(wParam, lParam);
		break;
    case COMM_TME_VEHICLE_INDENTIFICATION:
        ProcTMEVehicleAlarm(wParam, lParam);
        break;
    case COMM_PLATE_RESULT_V50:
        ProcITSPlateAlarmV50(wParam, lParam);
		break;
	case COMM_ITS_ROAD_EXCEPTION:
		ProcITSRoadException(wParam, lParam);
		break;
	case COMM_ALARMHOST_CID_ALARM:
		ProcAlarmHostCIDAlarm(wParam, lParam);
		break;
	case COMM_ALARMHOST_EXTERNAL_DEVICE_ALARM:
		ProcAlarmHostExternalDevAlarm(wParam, lParam);
		break;
	case COMM_ALARM_VQD:
		ProcAlarmVQD(wParam,lParam);
		break;
	case COMM_ALARM_VQD_EX:
		ProcAlarmVQDEx(wParam,lParam);
		break;
	case COMM_ITS_GATE_VEHICLE:
		ProcITSGateVehicle(wParam, lParam);
		break;
	case COMM_ITS_GATE_FACE:
		ProcITSGateFace(wParam, lParam);
		break;
	case COMM_ITS_PARK_VEHICLE:
		ProcITSParkVehicle(wParam, lParam);
		break;
	case COMM_ITS_BLACKLIST_ALARM:
		ProcITSBalckListInfo(wParam, lParam);
		break;
    case COMM_VEHICLE_CONTROL_LIST_DSALARM:
        ProcVehicleControlListDS(wParam, lParam);
        break;
    case COMM_VEHICLE_CONTROL_ALARM:
        ProcVehicleControl(wParam, lParam);
        break;
	case COMM_ALARMHOST_DATA_UPLOAD:
		ProcAlarmHostData(wParam, lParam);
		break;
    case COMM_ALARM_WIRELESS_INFO:
        ProcAlarmHostWirelessInfo(wParam, lParam);
        break;
	case COMM_ITS_GATE_ALARMINFO:
		ProcGateAlarmHostData(wParam, lParam);
		break;
	case COMM_ITS_EXTERNAL_CONTROL_ALARM://布防报警(外控报警)2013-06-09
		ProcExternalControlAlarmHostData(wParam, lParam);
		break;
	case COMM_SCENECHANGE_DETECTION_UPLOAD://2013-07-17场景变更侦测报警
		ProcSceneChangeDetection(wParam, lParam);
		break;
	case COMM_FACECAPTURE_STATISTICS_RESULT://人脸抓拍统计上传
		ProcFacecaptureStatistics(wParam, lParam);
		break;
    case COMM_VIDEO_PARKING_POLE_ALARM:
        ProcVideoParkingPoleAlarm(wParam, lParam);
        break;
	case COMM_CROSSLINE_ALARM://压线报警 2013-09-27
		ProcCrossLineData(wParam, lParam);
		break;
	case COMM_ALARM_HOT_SPARE:
		ProcHotSpare(wParam,lParam);
		break;
		//2013-11-19
	case COMM_ITS_GATE_COSTITEM://出入口过车收费明细
		ProcVehCostItem(wParam, lParam);
		break;
	case COMM_ITS_GATE_HANDOVER://出入口交接班数据
		ProcVehHandOver(wParam, lParam);
		break;
	case COMM_ALARM_AUDIOEXCEPTION://声音异常报警上传 2014-03-21
		ProcAudioException(wParam, lParam);
		break;
    case COMM_ALARM_DEFOCUS:
        ProcDefocus(wParam, lParam);
        break;
	case COMM_UPLOAD_HEATMAP_RESULT://热度图报警上传 2014-03-21
		ProcHeatMapResult(wParam, lParam);
		break;
    case COMM_ALARM_ACS: //门禁主机报警 2014-7-23
        ProcAccessCardAlarm(wParam, lParam); 
        break; 
	case COMM_ALARM_DEC_VCA:
        ProVCAAlarm(wParam, lParam); 
        break; 
	case COMM_VEHICLE_RECOG_RESULT://车辆二次识别数据上传2014-11-12
		ProVehicleRecogResult(wParam, lParam);
		break;
	case COMM_ALARM_LCD:
		ProLCDAlarm(wParam, lParam); 
		break; 
	case COMM_ALARM_SENSORINFO_UPLOAD:
		ProSensorInfoAlarm(wParam, lParam);
		break;
	case COMM_ALARM_CAPTURE_UPLOAD:
		ProCaptureAlarm(wParam, lParam);
		break;
    case COMM_FIREDETECTION_ALARM:
        ProFirDetectionAlarm(wParam, lParam);
		break;
    case COMM_FACE_THERMOMETRY_ALARM:
        ProFaceThermometryAlarm(wParam, lParam);
        break;
    case COMM_PANORAMIC_LINKAGE_ALARM:
        ProPicInfoUploadAlarm(wParam, lParam);
        break;
    case COMM_GISINFO_UPLOAD:
        ProGISInfoAlarm(wParam, lParam);
		break;
    case COMM_VANDALPROOF_ALARM:
        ProVandalproofAlarm(wParam, lParam);
		break;
	case COMM_UPLOAD_VIDEO_INTERCOM_EVENT:
		ProcVideoIntercomEvent(wParam,lParam);
		break;
	case COMM_ALARM_VIDEO_INTERCOM:
		ProcVideoIntercomAlarm(wParam,lParam);
		break;
    case COMM_UPLOAD_NOTICE_DATA:
        ProcUploadNoticeData(wParam, lParam);
        break;
    case COMM_PEOPLE_DETECTION_UPLOAD:
        ProcPeopleDetectionUpload(wParam,lParam);
		break;
    case COMM_ALARM_FIBER_CONVERT:
        ProcFiberConvertAlarm(wParam, lParam);
        break;
    case COMM_ALARM_SWITCH_CONVERT:
        ProcNetSwitchAlarm(wParam, lParam);
        break;
    case COMM_SWITCH_LAMP_ALARM:
        ProcSwicthLampAlarm(wParam, lParam);
		break;
	case COMM_GATE_CARDINFO_UPLOAD: //出入口卡片信息上传
		ProGateCardIndoAlarm(wParam, lParam);
		break;
    case COMM_GATE_CHARGEINFO_UPLOAD:
        ProGateCardChargeAlarm(wParam, lParam);
        break;
    case COMM_CONFERENCE_CALL_ALARM:
        ProConferenceAlarm(wParam, lParam);
        break;
    case COMM_ID_INFO_ALARM:
        ProcIDInfoAlarm(wParam, lParam);
        break;
    case COMM_PASSNUM_INFO_ALARM:
        ProcPassNumInfoAlarm(wParam, lParam);
        break;
    case COMM_ALARM_STORAGE_DETECTION:
        ProcStorageDetAlarm(wParam, lParam);
        break;
    case COMM_MVM_REGISTER:
        ProcMVMRegisterInfo(wParam, lParam);
        break;
    case COMM_MVM_STATUS_INFO:
        ProcMVMStatusInfo(wParam, lParam);
        break;
    case COMM_ALARM_SHIPSDETECTION:
        ProcShipsDetAlarm(wParam, lParam);
        break;
    case COMM_THERMOMETRY_ALARM:
        ProThermometryAlarm(wParam, lParam);
        break;
    case COMM_BASE_STATION_INFO_ALARM:
        ProBaseStationInfoAlarm(wParam, lParam);
        break;
    case COMM_THERMOMETRY_DIFF_ALARM:
        ProThermometryDiffAlarm(wParam, lParam);
        break;
	case COMM_DIAGNOSIS_UPLOAD:
		ProDiagnosisUpload(wParam, lParam);
		break;
    case COMM_ALARM_WALL_CONFERNECE:
        ProcessWallConferenceAlarm(wParam, lParam);
        break;
    case COMM_GPS_STATUS_ALARM:
        ProGPSStatusUpload(wParam, lParam);
        break;
    case COMM_TAG_INFO_ALARM:
        ProTagInfoUpload(wParam, lParam);
        break;
    case COMM_INQUEST_ALARM:
        ProcessInquestAlarm(wParam, lParam);
        break;
    case COMM_FACESNAP_RAWDATA_ALARM:
        ProFaceSnapRawData(wParam, lParam);
        break;
	case COMM_VCA_ALARM:
		ProcessEventWithJsonData(wParam, lParam);
		break;
    case COMM_ALARM_ALARMGPS:
        ProcessAlarmGps(wParam, lParam);
        break;
    case COMM_FRAMES_PEOPLE_COUNTING_ALARM:
        ProFramesPeopleCounting(wParam, lParam);
        break;
    case COMM_CLUSTER_ALARM:
        ProcessClusterAlarm(wParam, lParam);
        break;
    case COMM_SIGN_ABNORMAL_ALARM:
        ProcessEventWithJsonData(wParam, lParam);
        break;
    case COMM_TAPE_ARCHIVE_ALARM:
        ProcessEventWithJsonData(wParam, lParam);
        break;
    case COMM_HFPD_ALARM:
        ProcessEventWithJsonData(wParam, lParam);
        break;
    case COMM_DEV_STATUS_CHANGED:
        ProcessEventWithJsonDataNoBoundary(wParam, lParam);
        break;
    case COMM_UPLOAD_HEATMAP_RESULT_PDC://热度图按人数统计数据上传事件 2018-07-17
        ProcHeatMapResultPDC(wParam, lParam);
        break;
    case COMM_UPLOAD_HEATMAP_RESULT_DURATION://热度图按人员停留时间统计数据上传事件 2018-07-17
        ProcHeatMapResultDuration(wParam, lParam);
        break;
    case COMM_UPLOAD_HEATMAP_RESULT_INTERSECTION://路口分析热度值结果上传 2018-07-17
        ProcHeatMapResultIntersection(wParam, lParam);
        break;
	default:
		break;
	}
	if (pAlarmInfo != NULL)
	{
		delete[] pAlarmInfo;
		pAlarmInfo = NULL;
	}
	if (pAlarmDev != NULL)
	{
		delete pAlarmDev;
		pAlarmDev = NULL;
	}
	//LeaveCriticalSection(&g_cs);
	return NULL;
}
//the structure of the log information
typedef struct tagLOCAL_LOG_INFO 
{
	int iLogType;
	char szTime[64];
	char szLogInfo[1024];
	char szDevInfo[128];
	char szErrInfo[256];
	tagLOCAL_LOG_INFO ()
	{
		iLogType = 0;
		szTime[0] = '\0';
		szLogInfo[0] = '\0';
		szDevInfo[0] = '\0';
		szErrInfo[0] = '\0';
	}
}LOCAL_LOG_INFO, *LPLOCAL_LOG_INFO;

/*********************************************************
Function:	OnWMAddLog
Desc:		responding to the message WM_ADD_LOG
Input:	wParam, parameter 1;lParam, parameter 2;
Output:	none
Return:	result code
**********************************************************/
LRESULT CClientDemoDlg::OnWMAddLog(WPARAM wParam, LPARAM lParam)
{
	EnterCriticalSection(&g_cs);
	LPLOCAL_LOG_INFO pLogInfo = LPLOCAL_LOG_INFO(lParam);
	if (NULL == pLogInfo)
	{
        LeaveCriticalSection(&g_cs);
		return 0;
	}
	char szLogType[32] = "FAIL";
	
	char szTime[64] = {0};
	char szLogInfo[1024*5] = {0};
	char szDevInfo[128] = {0};
	char szErrInfo[256] = {0};
	memcpy(szTime, pLogInfo->szTime, 64);
	memcpy(szLogInfo, pLogInfo->szLogInfo, 1024);
	memcpy(szDevInfo, pLogInfo->szDevInfo, 128);
	memcpy(szErrInfo, pLogInfo->szErrInfo, 256);
	if ( m_listAllLog.GetItemCount() >= 5000)
	{
		m_listAllLog.DeleteAllItems();
	}
    if ( m_listAlarmInfo.GetItemCount() >= 5000)
    {
        m_listAlarmInfo.DeleteAllItems();
	}
	
	switch (pLogInfo->iLogType)
	{
	case ALARM_INFO_T:
		sprintf(szLogType, "Alarm");
		m_listAlarmInfo.InsertItem(0, "", -1);
		m_listAlarmInfo.SetItemText(0, 1, szTime);
		m_listAlarmInfo.SetItemText(0, 2, szLogInfo);
		m_listAlarmInfo.SetItemText(0, 3, szDevInfo);
		break;
	case DDNS_SUCC_T:
		sprintf(szLogType, "SUCC");
		if (g_struLocalParam.bSuccLog)
		{
			m_listAllLog.InsertItem(0, "", -1);
			m_listAllLog.SetItemText(0, 1, szTime);
			m_listAllLog.SetItemText(0, 2, szLogType);
			m_listAllLog.SetItemText(0, 3, szLogInfo);
			m_listAllLog.SetItemText(0, 4, szDevInfo);
			m_listAllLog.SetItemText(0, 5, szErrInfo);
		}
		break;
	case OPERATION_SUCC_T:
		sprintf(szLogType, "SUCC");	
		if (g_struLocalParam.bSuccLog)
		{
			m_listAllLog.InsertItem(0, "", -1);
			m_listAllLog.SetItemText(0, 1, szTime);
			m_listAllLog.SetItemText(0, 2, szLogType);
			m_listAllLog.SetItemText(0, 3, szLogInfo);
			m_listAllLog.SetItemText(0, 4, szDevInfo);
			m_listAllLog.SetItemText(0, 5, szErrInfo);
		}
		break;
	case OPERATION_FAIL_T:
		sprintf(szLogType, "FAIL");		
		if (g_struLocalParam.bFailLog)
		{
			m_listAllLog.InsertItem(0, "", -1);
			m_listAllLog.SetItemText(0, 1, szTime);
			m_listAllLog.SetItemText(0, 2, szLogType);
			m_listAllLog.SetItemText(0, 3, szLogInfo);
			m_listAllLog.SetItemText(0, 4, szDevInfo);
			m_listAllLog.SetItemText(0, 5, szErrInfo);
		}
		break;
	case PLAY_SUCC_T:
		sprintf(szLogType, "SUCC");
		if (g_struLocalParam.bSuccLog)
		{
			m_listAllLog.InsertItem(0, "", -1);
			m_listAllLog.SetItemText(0, 1, szTime);
			m_listAllLog.SetItemText(0, 2, szLogType);
			m_listAllLog.SetItemText(0, 3, szLogInfo);
			m_listAllLog.SetItemText(0, 4, szDevInfo);
			m_listAllLog.SetItemText(0, 5, szErrInfo);
		}
		break;
	case DDNS_FAIL_T:
		sprintf(szLogType, "FAIL");
		if (g_struLocalParam.bFailLog)
		{
			m_listAllLog.InsertItem(0, "", -1);
			m_listAllLog.SetItemText(0, 1, szTime);
			m_listAllLog.SetItemText(0, 2, szLogType);
			m_listAllLog.SetItemText(0, 3, szLogInfo);
			m_listAllLog.SetItemText(0, 4, szDevInfo);
			m_listAllLog.SetItemText(0, 5, szErrInfo);
		}
		break;
	case PLAY_FAIL_T:
		sprintf(szLogType, "FAIL");	
		if (g_struLocalParam.bFailLog)
		{
			m_listAllLog.InsertItem(0, "", -1);
			m_listAllLog.SetItemText(0, 1, szTime);
			m_listAllLog.SetItemText(0, 2, szLogType);
			m_listAllLog.SetItemText(0, 3, szLogInfo);
			m_listAllLog.SetItemText(0, 4, szDevInfo);
			m_listAllLog.SetItemText(0, 5, szErrInfo);
		}
		break;
	default:
		sprintf(szLogType, "FAIL");	
		if (g_struLocalParam.bFailLog)
		{
			m_listAllLog.InsertItem(0, "", -1);
			m_listAllLog.SetItemText(0, 1, szTime);
			m_listAllLog.SetItemText(0, 2, szLogType);
			m_listAllLog.SetItemText(0, 3, szLogInfo);
			m_listAllLog.SetItemText(0, 4, szDevInfo);
			m_listAllLog.SetItemText(0, 5, szErrInfo);
		}
		break;
	}
	if (pLogInfo != NULL)
	{
		delete pLogInfo;
		pLogInfo = NULL;
	}
	LeaveCriticalSection(&g_cs);
	return 0;
}

/*********************************************************
Function:	AddLog
Desc:		add local log
Input:	iLogType, log type, 0-alam, 1-operate log, 2-debug info; csLogInfo log info
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::AddLog(int iDeviceIndex, int iLogType, const char* format, ...)
{	
	if (g_bExitDemo)
	{
		return;
	}
	CTime  cTime = CTime::GetCurrentTime();
	int iLen = 0;
	char szTime[64] = {0};
	char szLogType[32] = "FAIL";
	char szLogInfo[1024*5] = {0};
	char szDevInfo[256] = {0};
	char szErrInfo[256] = {0};
	char szLog[1024*5] = {0};
	va_list arglist;
	va_start(arglist,format);
	vsprintf(szLogInfo,format,arglist); 
	va_end(arglist);
	
	sprintf(szTime, "%s", cTime.Format("%y-%m-%d %H:%M:%S").GetBuffer(0));
	
	if (iDeviceIndex != -1 && iDeviceIndex < 512)
	{
		sprintf(szDevInfo, "[%s]-[%s]", g_struDeviceInfo[iDeviceIndex].chDeviceIP, g_struDeviceInfo[iDeviceIndex].chLocalNodeName);
	}
	
	switch (iLogType)
	{
	case OPERATION_SUCC_T:
	case PLAY_SUCC_T:
		sprintf(szErrInfo, "");
		sprintf(szLogType, "SUCC");
		break;
	case PLAY_FAIL_T:
		sprintf(szErrInfo, "PLAY_M4 Eorror!!!");	
		break;
	case OPERATION_FAIL_T:
	default:
        if (m_giAsynLoginReturn != 0)
        {
            sprintf(szErrInfo, "err[%d:%s]", 
                m_giErrNo, m_gpErrMsg);
        }
        else
        {
            sprintf(szErrInfo, "err[%d:%s]", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        }
		break;
	}
	//sprintf(szErrInfo, "err[%d:%s]", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
	if (iLogType == ALARM_INFO_T )
	{
		iLen = sprintf(szLog, "%s %s %s\n", szTime, szLogInfo, szDevInfo);
		if (m_fAlarm != NULL && g_struLocalParam.bAutoSaveLog)
		{
			if (fwrite(szLog, 1, iLen, m_fAlarm) != (unsigned)iLen)
			{
				OutputDebugString("write err");
			}
		}
	}
	else
	{
		iLen = sprintf(szLog, "%s %s %s %s %s\n", szTime, szLogType, szLogInfo, szDevInfo, szErrInfo);
		if (m_fLog != NULL && g_struLocalParam.bAutoSaveLog)
		{
			if (fwrite(szLog, 1, iLen, m_fLog) != (unsigned)iLen)
			{
				OutputDebugString("write err");
			}
		}
	}
	
	if (g_struLocalParam.bOutputDebugString)
	{
		OutputDebugString(szLog);
	}
	if (!g_struLocalParam.bSuccLog && !g_struLocalParam.bFailLog && (iLogType != ALARM_INFO_T ))
	{
		return;
	}
	LPLOCAL_LOG_INFO pLogInfo = NULL;
	try
    {  
		
		pLogInfo = new LOCAL_LOG_INFO;
		memset(pLogInfo, 0, sizeof(LOCAL_LOG_INFO));
		if (pLogInfo == NULL)
		{
			return;
		}
		pLogInfo->iLogType = iLogType;
		memcpy(pLogInfo->szTime, szTime, 64);
        memcpy(pLogInfo->szLogInfo, szLogInfo, 1024);
		memcpy(pLogInfo->szDevInfo, szDevInfo, 128);
		memcpy(pLogInfo->szErrInfo, szErrInfo, 256);
        ::PostMessage(g_pMainDlg->m_hWnd, WM_ADD_LOG, iDeviceIndex, (LPARAM)pLogInfo);
	}
	catch (...)
	{
		if (pLogInfo != NULL)
		{
			return;
		}
		OutputDebugString("New Log Exception!!\n");
	}
}

/*************************************************
Function:    	DblAllTree
Description:	preview all device if some are not previewed, or stop all previewing devices
Input:          iDeviceIndex, device index; iStartOutputIndex, preview start index;
Return:		    无
*************************************************/
void CClientDemoDlg::DblAllTree()
{
	HTREEITEM hSelect = m_treeDeviceList.GetSelectedItem();
	
	int i=0;
	int iDevIndex = 0;
	
	hSelect = m_treeDeviceList.GetChildItem(hSelect);
	
	for (i=0; i<MAX_DEVICES; i++)
	{
		//shut down all play channel
		
		if (g_struDeviceInfo[i].lLoginID < 0)
		{//play the window that is not previewed
			iDevIndex = m_treeDeviceList.GetItemData(hSelect)%1000;
            /*LPLOCAL_LOGIN_PARAM lpParam = new LOCAL_LOGIN_PARAM;
            lpParam->iDeviceIndex = iDevIndex;
            lpParam->hSelect = hSelect;
            lpParam->bMsgBox = FALSE;*/
//  			_beginthread((void (__cdecl *)(void *))DoLoginEx, 0, lpParam);
//  			Sleep(200);
			LONG lReturn = DoLogin(iDevIndex, hSelect);
 			hSelect = m_treeDeviceList.GetNextSiblingItem(hSelect);
			if (hSelect == NULL)
			{
				break;
			}
		}
	}
}
/*************************************************
Function:    	DblPlayDevice
Description:	preview all device if some are not previewed, or stop all previewing devices
Input:          iDeviceIndex, device index; iStartOutputIndex, preview start index;
Return:		    无
*************************************************/
void CClientDemoDlg::DblPlayDevice(int iDeviceIndex, int iStartOutputIndex)
{
	HTREEITEM hSelect = m_treeDeviceList.GetSelectedItem();
	if (!DoLogin(iDeviceIndex, hSelect))
	{
		return;
	}
	
	int i=0;
	int iChanIndex = 0;
	
	HTREEITEM hChannel = m_treeDeviceList.GetChildItem(hSelect);
	
    //既未配置URL方式预览时又无通道
    if (hChannel == NULL && !g_struDeviceInfo[iDeviceIndex].byURL)
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "there is no channels!!");
		return;
	}
	
	if (g_struDeviceInfo[iDeviceIndex].bPlayDevice)
	{
		g_struDeviceInfo[iDeviceIndex].bPlayDevice = FALSE;
		//StopPlayAll();
		for (i=0; i< m_iCurWndNum; i++)
		{
			if (g_dlgOutput[i].m_struChanInfo.iDeviceIndex == iDeviceIndex)
			{
				g_dlgOutput[i].StopPlay();
			}	
		}
	}
	else
	{
		for (i=0; i<m_iCurWndNum; i++)
		{
			//shut down all play channel
			if (g_dlgOutput[i].m_struChanInfo.iDeviceIndex == iDeviceIndex)
			{
				g_dlgOutput[i].StopPlay();
			}	
			
			if (g_dlgOutput[i].m_lPlayHandle < 0)
			{//play the window that is not previewed

                //没有通道配置了URL预览，此时要收到设置通道号（虚假的通道，用于后续代码逻辑复用有通道的设备）
                if (g_struDeviceInfo[iDeviceIndex].byURL && hChannel == NULL)
                {
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[0].iChannelNO = 1;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[0].iDeviceIndex = iDeviceIndex;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[0].iChanIndex = 0;
                    LONG lReturn = g_dlgOutput[i].StartPlay(&g_struDeviceInfo[iDeviceIndex].pStruChanInfo[0], hChannel);
                    break;
                }
                else
                {
                    iChanIndex = m_treeDeviceList.GetItemData(hChannel) % 1000;
                    if ((g_struDeviceInfo[iDeviceIndex].wStartMirrorChanNo != 0) && (iChanIndex >= MIRROR_CHAN_INDEX))
                    {
                        LONG lReturn = g_dlgOutput[i].StartPlay(&g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX], hChannel);
                    }
                    else
                    {
                        LONG lReturn = g_dlgOutput[i].StartPlay(&g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex], hChannel);
                    }
                    hChannel = m_treeDeviceList.GetNextSiblingItem(hChannel);
                    if (hChannel == NULL)
                    {
                        break;
                    }
                }
			}
			
		}
		g_struDeviceInfo[iDeviceIndex].bPlayDevice = TRUE;
	}
	
	ChangePlayBtnState();
}

/*********************************************************
Function:	StopPlayAll
Desc:		stop all playing windows
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::StopPlayAll(void)
{
	int i = 0;
	for (i = 0; i < MAX_OUTPUTS; i ++)
	{
		if (g_dlgOutput[i].m_lPlayHandle < 0)
		{
			continue;
		}
		g_dlgOutput[i].StopPlay();
	}
}

/*********************************************************
Function:	ChangePlayBtnState
Desc:		change 'play' button text state
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::ChangePlayBtnState(void)
{
	int i = 0;
	char szLan[32] = {0};
	if (m_iMainType == PREVIEW_T)
	{
		for (i = 0; i < MAX_OUTPUTS; i++)
		{
			if (g_dlgOutput[i].m_lPlayHandle < 0)
			{
				if (!g_bPlayAllDevice && i == m_iCurWndIndex)
				{//change network delay
					m_comboNetDelayBufNum.EnableWindow(TRUE);
				}				
				continue;
			}
			
			if (i == m_iCurWndIndex)
			{
				m_comboNetDelayBufNum.EnableWindow(FALSE);
			}
			m_comboWinNum.EnableWindow(FALSE);
			g_StringLanType(szLan, "停止", "Stop");
			GetDlgItem(IDC_BTN_PLAY)->SetWindowText(szLan);
			return;
		}
	}
	
	m_comboWinNum.EnableWindow(TRUE);
	g_StringLanType(szLan, "播放", "Play");
    g_bPlayAllDevice = FALSE;
	GetDlgItem(IDC_BTN_PLAY)->SetWindowText(szLan);
}

/*********************************************************
Function:	GetChanItem
Desc:		get channel item and its structure
Input:	iDeviceIndex,device serial number;iChanIndex,channel index;
Output:	
Return:	
**********************************************************/
HTREEITEM CClientDemoDlg::GetChanItem(int iDeviceIndex, int iChanIndex)
{
	HTREEITEM hRoot = m_treeDeviceList.GetRootItem();
	if (hRoot == NULL)
	{
		return NULL;
	}
	int iChanData = 0;
	HTREEITEM hChannel = NULL;
	
	HTREEITEM hDevItem = m_treeDeviceList.GetChildItem(hRoot);
	while (hDevItem != NULL)
	{
		if (DEVICETYPE == (int)m_treeDeviceList.GetItemData(hDevItem)/1000)
		{
			if (iDeviceIndex ==  (int)m_treeDeviceList.GetItemData(hDevItem)%1000)
			{
				hChannel = m_treeDeviceList.GetChildItem(hDevItem);	
				if (hChannel == NULL)
				{
					return NULL;
				}
				iChanData = m_treeDeviceList.GetItemData(hChannel);
				while (iChanData%1000 != iChanIndex)
				{
					hChannel = m_treeDeviceList.GetNextSiblingItem(hChannel);
					if (hChannel == NULL)
					{
						AddLog(iDeviceIndex, OPERATION_FAIL_T, "don't find chanindex[%d] node!!!", iChanIndex);
						return NULL;
					}
					else
					{
						iChanData = m_treeDeviceList.GetItemData(hChannel);
					}
					
				}
				return hChannel;
			}
		}
		hDevItem = m_treeDeviceList.GetNextVisibleItem(hDevItem);
	}//end while
	
	return NULL;
}


/*********************************************************
Function:	GetDeviceItem
Desc:		get device item and its structure
Input:	iDeviceIndex, device index
Output:	
Return:	
**********************************************************/
HTREEITEM CClientDemoDlg::GetDeviceItem(int iDeviceIndex)
{
	HTREEITEM hRoot = m_treeDeviceList.GetRootItem();
	if (hRoot == NULL)
	{
		return NULL;
	}
	HTREEITEM hItem = m_treeDeviceList.GetChildItem(hRoot);
	
	while (hItem)
	{
		if (DEVICETYPE == m_treeDeviceList.GetItemData(hItem)/1000)
		{
			if (iDeviceIndex ==  (int)m_treeDeviceList.GetItemData(hItem)%1000)
			{
				return hItem;
			}
		}//end else if
		
		hItem = m_treeDeviceList.GetNextVisibleItem(hItem);
	}//end while
	
	return NULL;
}

/*********************************************************
Function:	GetCurDeviceIndex
Desc:		check the channel, return device index related to this channel
Input:	
Output:	
Return:	
**********************************************************/
int CClientDemoDlg::GetCurDeviceIndex()
{
	if (m_iCurDeviceIndex < MAX_DEVICES && m_iCurDeviceIndex >= 0)
	{
		return m_iCurDeviceIndex;
	}
	AddLog(-1, OPERATION_SUCC_T, "please select a device at first!");
	return -1;
}

/*********************************************************
Function:	GetCurChanIndex
Desc:		Get current channel serial number.  When channel number < 64, this function is used.
Input:	
Output:	
Return:	
**********************************************************/
int CClientDemoDlg::GetCurChanIndex()
{
    if (m_iCurChanIndex >= 0 && m_iCurChanIndex < 512)
	{
		return m_iCurChanIndex;
	}

	//AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "please select a camera at first!");
	return -1;
} 

int CClientDemoDlg::GetCurChanIndexInTree()
{
    if (m_iCurChanIndex >= 0 && m_iCurChanIndex < 512)
	{	
		return m_iCurChanIndex;
	}
	//AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "please select a camera at first!");
	return -1; 
}

/*********************************************************
Function:	OnBnClickedBtnElse
Desc:		other operation
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnElse()
{
	CMenu pMenu;
	CRect rectBtnElse(0,0,0,0);
	GetDlgItem(IDC_BTN_ELSE)->GetWindowRect(&rectBtnElse);
	
	// 	int iDeviceIndex = GetCurDeviceIndex();
	// 	if (iDeviceIndex == -1)
	// 	{
	// 		AfxMessageBox("请选中对应的设备!");
	// 		return;
	// 	}
	
	if (!pMenu.LoadMenu(IDR_MENU_ELSE))
	{
		return;
	}
	
	// 	if (g_struDeviceInfo[iDeviceIndex].iDiskNum > 0)
	// 	{//device local record on disk or other store devices
	// 		pMenu.GetSubMenu(0)->EnableMenuItem(5, MF_BYPOSITION | MF_ENABLED);		
	// 	}
	// 	else
	// 	{
	// 		pMenu.GetSubMenu(0)->EnableMenuItem(5, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
	// 	}
	
	pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, rectBtnElse.left,rectBtnElse.bottom,this);
}

/*********************************************************
Function:	OnMenuRemoteKey
Desc:		menu on remote key response function
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuRemoteKey()
{
	int iDeviceIndex = GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return;
	}
	CDlgRemoteKey dlgRemoteKey;
	dlgRemoteKey.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	dlgRemoteKey.DoModal();
}

/*********************************************************
Function:	OnMenuCheckTime
Desc:		menu on time checking response function
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuCheckTime()
{
	CDlgCheckTime dlg;
	dlg.DoModal();
}

/*********************************************************
Function:	OnMenuWorkState
Desc:		get device work sate	
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnMenuWorkState()
{
	int iDeviceIndex = GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return;
	}
	
	CDlgDeviceState dlg;
	dlg.m_lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	dlg.DoModal();
}

/*********************************************************
Function:	OnMenuLogSearch
Desc:		dvr log search
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnMenuLogSearch()
{
	int iDeviceIndex = GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return;
	}
	CDlgLogSearch dlg;
	dlg.m_lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	dlg.DoModal();
}

/*********************************************************
Function:	OnMenuDVRRecordStart
Desc:		DVR local record
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuDVRRecordStart()
{
	int iDeviceIndex = GetCurDeviceIndex();
	int iChanIndex = GetCurChanIndex();
	int iChanShowNum = 1;
	int i= 0;
	CString sTemp;
	if (iDeviceIndex == -1)
	{
		return;
	}

	NET_DVR_WORKSTATE_V40 *pStruWorkStateV40 = new NET_DVR_WORKSTATE_V40;
	if (pStruWorkStateV40 == NULL)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "申请内存失败", "alloc memory error");
		AfxMessageBox(szLan);
		return;
	}
	
	NET_DVR_GETWORKSTATE_COND struWorkStateCond = {0};
	struWorkStateCond.dwSize =  sizeof(NET_DVR_GETWORKSTATE_COND);
	struWorkStateCond.byFindChanByCond = 0;
	struWorkStateCond.byFindHardByCond = 0;
	DWORD dwStatusChanIndex = 0;
	DWORD dwList = 0;
	
	if (!NET_DVR_GetDeviceConfig(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_GET_WORK_STATUS,1,\
		&struWorkStateCond,sizeof(NET_DVR_GETWORKSTATE_COND),&dwList,pStruWorkStateV40, sizeof(NET_DVR_WORKSTATE_V40)) ||(dwList != 0))
	{
		AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WORK_STATUS");
		return;
	}

	
	if (iChanIndex == -1)  // All Cameras
	{
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (!g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable)
			{
				continue;
			}
			int iChannelNO = -1;
			if (g_struDeviceInfo[iDeviceIndex].byMirrorChanNum&&iChanIndex >= MIRROR_CHAN_INDEX)
			{
				iChannelNO = g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].iChannelNO;
			}
			else
			{
				iChannelNO = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO;
			}
			 
			for (int j = 0;j<MAX_CHANNUM_V40;j++)
			{
				if (iChannelNO == pStruWorkStateV40->struChanStatic[j].dwChannelNo)
				{
					dwStatusChanIndex = j;
					break;
				}
			}
			if (pStruWorkStateV40->struChanStatic[dwStatusChanIndex].byRecordStatic == 0) //
			{
				if (NET_DVR_StartDVRRecord(g_struDeviceInfo[iDeviceIndex].lLoginID, iChannelNO, 0))
				{
					AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDVRRecord %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
				}	
				else
				{
					AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDVRRecord %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
				}
			}
			else if(pStruWorkStateV40->struChanStatic[dwStatusChanIndex].byRecordStatic == 1) //
			{
				if (NET_DVR_StopDVRRecord(g_struDeviceInfo[iDeviceIndex].lLoginID, iChannelNO))
				{
					AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDVRRecord %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
				}
				else
				{
					AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDVRRecord %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);	
				}
			}
		}
	}
	else
	{
		i = iChanIndex;

		if (g_struDeviceInfo[iDeviceIndex].byMirrorChanNum&&iChanIndex >= MIRROR_CHAN_INDEX)
		{
			iChanShowNum = g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex].iChannelNO;
		}
		else
		{
			iChanShowNum = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
		}
		for (int j = 0;j<MAX_CHANNUM_V40;j++)
		{
			if (iChanShowNum == pStruWorkStateV40->struChanStatic[j].dwChannelNo)
			{
				dwStatusChanIndex = j;
				break;
			}
		}

		if (pStruWorkStateV40->struChanStatic[dwStatusChanIndex].byRecordStatic == 0)
		{
			if (NET_DVR_StartDVRRecord(g_struDeviceInfo[iDeviceIndex].lLoginID, iChanShowNum, 0))
			{
				AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDVRRecord %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
				char szLan[128] = {0};
				g_StringLanType(szLan, "开始DVR本地录像成功", "Start Local Record successfully");
				AfxMessageBox(szLan);
			}	
			else
			{
				AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDVRRecord %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
			}
		}
		else if (pStruWorkStateV40->struChanStatic[dwStatusChanIndex].byRecordStatic == 1)
		{
			if (NET_DVR_StopDVRRecord(g_struDeviceInfo[iDeviceIndex].lLoginID, iChanShowNum))
			{
				AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDVRRecord %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
				char szLan[128] = {0};
				g_StringLanType(szLan, "停止DVR本地录像成功", "Stop Local Record successfully");
				AfxMessageBox(szLan);
			}
			else
			{
				AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDVRRecord %s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].chChanName);
			}
		}
	}

	
	if (pStruWorkStateV40 != NULL)
	{
		delete pStruWorkStateV40 ;
		pStruWorkStateV40 = NULL;
	}
}

/*********************************************************
Function:	ConfigAllHide
Desc:		hide all configure box
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::ConfigAllHide()
{
	m_dlgConfigAll->ShowWindow(SW_HIDE);
	m_dlgRemoteCfg->ShowWindow(SW_HIDE);	
	m_dlgLocalCfg->ShowWindow(SW_HIDE);
	m_dlgIPAccess->ShowWindow(SW_HIDE);	
	m_dlgHDConfig->ShowWindow(SW_HIDE);
//	m_pStreamIDDlg->ShowWindow(SW_HIDE);
	m_dlgBatchCfg->ShowWindow(SW_HIDE);
	m_dlgProductCfg->ShowWindow(SW_HIDE);
	m_dlgPlayBack->ShowWindow(SW_HIDE);
}

/*********************************************************
Function:	OnCbnSelchangeComboNetdelay
Desc:		set current network delay
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnCbnSelchangeComboNetdelay()
{
	UpdateData(TRUE);
	int iTmp = m_comboNetDelayBufNum.GetCurSel();
	switch (iTmp) 
	{
	case 0:
		g_dlgOutput[m_iCurWndIndex].m_iNetDelayBufNum = 1;
		break;
	case 1:
		g_dlgOutput[m_iCurWndIndex].m_iNetDelayBufNum = 3;
		break;
	case 2:
		g_dlgOutput[m_iCurWndIndex].m_iNetDelayBufNum = 6;
		break;
	case 3:
		g_dlgOutput[m_iCurWndIndex].m_iNetDelayBufNum = 15;
		break;
	default:
		g_dlgOutput[m_iCurWndIndex].m_iNetDelayBufNum= 1;
		break;
	}
}
/*********************************************************
Function:	CyclePlayAllDevicesLogined
Desc:		循环播放已经登陆的设备
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::CyclePlayAllDevicesLogined()
{
	int i = 0;
	int iPlayNum = 0;//current monitoring points that will be played
	int iFirstIndex = -1;//current first monitoring point index 
	int iDeviceIndex = -1;
	int iChanIndex = -1;
	int iSurveillanceNumLeft = 0;
	
	if (g_nSurveillanceTotalNum<=m_iCurWndNum)
	{
		return;
	}
	
	if (g_nSurveillanceTotalNum == g_iNextSurveillanceIndex)		//turn to first page while cycle to last page
	{
		iPlayNum = m_iCurWndNum;
		iFirstIndex = 0;
	}
	else
	{
		iPlayNum = g_nSurveillanceTotalNum - g_iNextSurveillanceIndex;
		
		if (iPlayNum > m_iCurWndNum)
		{
			iPlayNum = m_iCurWndNum;
		}
		iFirstIndex = g_iNextSurveillanceIndex;
	}
	
	//stop all the windows which is playing
	StopPlayAll();
	
	for (i = 0; i < iPlayNum; i++)
	{
		if (i+iFirstIndex < MAX_PREVIEWS)
		{
			iDeviceIndex = g_struPlayAllInfo[i+iFirstIndex].iDeviceIndex;
			iChanIndex = g_struPlayAllInfo[i+iFirstIndex].iChanIndex;
			g_dlgOutput[i].StartPlay(&g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex], GetChanItem(iDeviceIndex, iChanIndex));
		}
	}
	
	iSurveillanceNumLeft = g_nSurveillanceTotalNum - g_iNextSurveillanceIndex;
	
	if (iSurveillanceNumLeft == 0)//restart afer a cycle
	{
		g_iNextSurveillanceIndex = m_iCurWndNum;
		g_struLocalParam.bFrontPage = FALSE;
		g_struLocalParam.bNextPage = TRUE;
	}
	else if (iSurveillanceNumLeft <= m_iCurWndNum)//last several monitoring points
	{
		g_iNextSurveillanceIndex = g_nSurveillanceTotalNum;
		g_struLocalParam.bNextPage = FALSE;
		g_struLocalParam.bFrontPage = TRUE;
	}	
	else
	{
		g_struLocalParam.bFrontPage = TRUE;
		g_struLocalParam.bNextPage = TRUE;
		g_iNextSurveillanceIndex += m_iCurWndNum;
	}
	
	//UpdateData(FALSE);
}

/*********************************************************
Function:	PlayNextPage
Desc:		preview next pic in play list
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::PlayNextPage()
{
	int iPlayNum = 0;
	int i = 0;
	int iDeviceIndex = -1;
	int iChanIndex = -1;
	int iSurveillanceLeftNum = 0;
	
	if ((g_struLocalParam.bEnlarged)||(g_struLocalParam.bFullScreen))
	{
		if (g_struLocalParam.bFullScreen)
		{
			g_struLocalParam.bFullScreen = FALSE;
			FullScreen(g_struLocalParam.bFullScreen);
		}
		g_struLocalParam.bEnlarged = FALSE;
		ArrangeOutputs(m_iCurWndNum);						
	}
	
	iSurveillanceLeftNum = g_nSurveillanceTotalNum - g_iNextSurveillanceIndex;
	if (iSurveillanceLeftNum > m_iCurWndNum)
	{// left monitoring points surpass current playing windows number
		iPlayNum = m_iCurWndNum;
		g_struLocalParam.bNextPage = TRUE;
	}
	else
	{
		iPlayNum = iSurveillanceLeftNum;
		g_struLocalParam.bNextPage = FALSE;
	}
	
	StopPlayAll();//shut down previous page preview
	
	for (i=0;i<iPlayNum;i++)
	{
		if (i+g_iNextSurveillanceIndex < MAX_PREVIEWS)
		{
			iDeviceIndex = g_struPlayAllInfo[i+g_iNextSurveillanceIndex].iDeviceIndex;
			iChanIndex = g_struPlayAllInfo[i+g_iNextSurveillanceIndex].iChanIndex;
			g_dlgOutput[i].StartPlay(&g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex], GetChanItem(iDeviceIndex, iChanIndex));
			Sleep(100);
		}
	}
	
	g_iNextSurveillanceIndex += iPlayNum;
	g_struLocalParam.bFrontPage = TRUE;
	ChangePlayBtnState();
	UpdateData(FALSE);
}

/*********************************************************
Function:	PlayFrontPage
Desc:		play front group of monitoring points
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::PlayFrontPage()
{
	int iPlayIndex = 0;
	int i = 0;
	int iDeviceIndex = -1;
	int iChanIndex = -1;
	
	if (g_iNextSurveillanceIndex <= m_iCurWndNum || m_iCurWndNum == 0)
	{
		return;
	}
	
	if ((g_struLocalParam.bEnlarged) || (g_struLocalParam.bFullScreen))
	{
		if (g_struLocalParam.bFullScreen)
		{
			g_struLocalParam.bFullScreen = FALSE;
			FullScreen(g_struLocalParam.bFullScreen);
		}
		g_struLocalParam.bEnlarged = FALSE;
		ArrangeOutputs(m_iCurWndNum);	//while windos is zoomed, turn to next pic and restore original window number				
	}
	
	if (g_iNextSurveillanceIndex < 2*m_iCurWndNum)
	{
		iPlayIndex = 0;//if front page is first index, set play index as 0
	}
	else
	{
		i = g_iNextSurveillanceIndex % m_iCurWndNum;
		if (i == 0)
		{
			iPlayIndex = g_iNextSurveillanceIndex - 2*m_iCurWndNum ;
		}
		else
		{
			iPlayIndex = g_iNextSurveillanceIndex - m_iCurWndNum - i;
		}
	}
	
	StopPlayAll();//stop all preview
	
	for (i=0;i<m_iCurWndNum;i++)
	{
		if (i+iPlayIndex < MAX_PREVIEWS)
		{
			iDeviceIndex = g_struPlayAllInfo[i+iPlayIndex].iDeviceIndex;
			iChanIndex = g_struPlayAllInfo[i+iPlayIndex].iChanIndex;
			g_dlgOutput[i].StartPlay(&g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex], GetChanItem(iDeviceIndex, iChanIndex));
			Sleep(100);
		}
	}
	
	if (g_iNextSurveillanceIndex <= 2*m_iCurWndNum)
	{
		g_iNextSurveillanceIndex = m_iCurWndNum;
		g_struLocalParam.bFrontPage = FALSE;		//no front page
	}
	else
	{
		i = g_iNextSurveillanceIndex % m_iCurWndNum;
		if (i == 0)
		{
			g_iNextSurveillanceIndex -= m_iCurWndNum;
		}
		else
		{
			g_iNextSurveillanceIndex -= i;
		}
		g_struLocalParam.bFrontPage = TRUE;
	}
	g_struLocalParam.bNextPage = TRUE;
}

/*********************************************************
Function:	CyclePause
Desc:		suspend or continue cycle
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::CyclePause()
{
	if (!g_struLocalParam.bPaused)
	{	
		g_struLocalParam.bPaused = TRUE;
		if (g_pCycleTimer != NULL)
		{
			KillTimer(CYCLE_PREVIEW_TIMER);
			g_pCycleTimer = NULL;	
		}
	}
	else//continue cycle
	{
		CyclePlayAllDevicesLogined();
		if (g_pCycleTimer == NULL)
		{
			g_pCycleTimer = SetTimer(CYCLE_PREVIEW_TIMER, g_struLocalParam.iCycleTime*1000,NULL);
		}
		g_struLocalParam.bPaused = FALSE;
	}
	ChangePlayBtnState();
}

/*********************************************************
Function:	OnMove
Desc:		dealing with preview and backplay in double screen
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);	
	
	GetWindowRect(&g_rcWindow);
	if (g_rcWindow.left < 0)
	{
		return;
	}
	int iTmpMonitorNum = 0;
	int i=0;
	//#if (WINVER > 0x0400)
	DWORD dwNewDeviceNum = 0;
	LONG lTmpHandle = -1;
	if (((DWORD)g_rcWindow.right + (DWORD)g_rcWindow.left > (DWORD)2 * g_iCurScreenWidth )||((DWORD)g_rcWindow.top + (DWORD)g_rcWindow.bottom > (DWORD)2 * g_iCurScreenHeight))
	{
		dwNewDeviceNum = 1;
	}
	else
	{
		dwNewDeviceNum = 0;	
	}
	if (dwNewDeviceNum != g_dwOldDeviceNum)
	{
		if (m_iMainType == PREVIEW_T)
		{
			int iPlayNum = 0;
			// 			if (g_nSurveillanceTotalNum == 0)
			// 			{
			// 				return;	
			// 			}
			if (g_nSurveillanceTotalNum < m_iCurWndNum)
			{
				iPlayNum = g_nSurveillanceTotalNum;
			}
			else
			{
				iPlayNum = g_nSurveillanceTotalNum;
			}
			iTmpMonitorNum = PlayM4_GetDDrawDeviceTotalNums();
			if (iTmpMonitorNum >= 1)
			{
				for (i=0; i<m_iCurWndNum; i++)
				{
					if (g_dlgOutput[i].m_lPlayHandle>=0)
					{
						LONG lPort = -1;
						if (g_dlgOutput[i].m_lPort >= 0)
						{
							lPort = g_dlgOutput[i].m_lPort;
						}
						else
						{
							lPort = NET_DVR_GetRealPlayerIndex(g_dlgOutput[i].m_lPlayHandle);
						}
						if (lPort < 0)
						{
							return;
						}
						if (PlayM4_SetDDrawDevice(lPort, dwNewDeviceNum + 1))//
						{
							AddLog(m_iCurDeviceIndex, PLAY_SUCC_T, "PlayM4_SetDDrawDevice output[%d]", i);
						}
						else
						{
							AddLog(m_iCurDeviceIndex, PLAY_FAIL_T, "PlayM4_SetDDrawDevice output[%d] err[%d]", i, PlayM4_GetLastError(NET_DVR_GetRealPlayerIndex(g_dlgOutput[i].m_lPlayHandle)));
						}
						
					}			
				}			
			}
			
		}
		else if (m_iMainType == PLAY_BACK_T)
		{
			switch (m_dlgPlayBack->m_iPlayBackType)
			{
			case 0://remote file
				if (m_dlgPlayBack->m_dlgPlayRemoteFile.m_nPlayHandle == -1)
				{
					return;		
				}	
				iTmpMonitorNum = PlayM4_GetDDrawDeviceTotalNums();
				lTmpHandle = NET_DVR_GetPlayBackPlayerIndex(m_dlgPlayBack->m_dlgPlayRemoteFile.m_nPlayHandle);
				AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "lTmpHandle is %d", lTmpHandle);
				PlayM4_SetDDrawDevice(lTmpHandle, dwNewDeviceNum + 1);
				g_dwOldDeviceNum = dwNewDeviceNum;		
				break;
			case 1://local
				iTmpMonitorNum = PlayM4_GetDDrawDeviceTotalNums();
				AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "iTmpMonitorNum is %d", iTmpMonitorNum);
				PlayM4_SetDDrawDevice(99, dwNewDeviceNum + 1);	
				break;
			case 2://play back by time
				if (m_dlgPlayBack->m_dlgPlayRemoteTime.m_lPlayHandle == -1)
				{
					return;
				}
				//nVal = NET_DVR_GetDDrawDeviceTotalNums();
				iTmpMonitorNum = PlayM4_GetDDrawDeviceTotalNums();
				lTmpHandle = NET_DVR_GetPlayBackPlayerIndex(m_dlgPlayBack->m_dlgPlayRemoteTime.m_lPlayHandle);
				AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "lTmpHandle is %d", lTmpHandle);
				//NET_DVR_SetDDrawDevice(temp, dwNewDeviceNum + 1);			
				PlayM4_SetDDrawDevice(lTmpHandle, dwNewDeviceNum + 1);			
				break;
			default:
				break;
			}
		}
		g_dwOldDeviceNum = dwNewDeviceNum;		
	}
	//#endif
	
	if (g_struLocalParam.bUseCard)
	{
		NET_DVR_RefreshSurface_Card();
	}
	UpdateWindow();
}

/*********************************************************
Function:	OnBnClickedBtnConfig
Desc:		configure operation
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnConfig()
{
	if (m_iMainType != CONFIG_ALL_T)
	{
		m_iMainType = CONFIG_ALL_T;
		PreviewReferShow(FALSE);
		ConfigAllHide();
		m_dlgPlayBack->HideAll();
		InitConfigAllRefer();
	}
}

/*********************************************************
Function:	InitConfigAllRefer
Desc:		initialize interface dealing related to configuration
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::InitConfigAllRefer()
{
	if (!m_dlgConfigAll->IsWindowVisible())
	{
		CRect rectConfig(0,0,0,0);	
		
		rectConfig.top    = m_iFunBtnHeight-2;
		rectConfig.left   = m_iTreeWidth-2;//-2 cover preview box
		rectConfig.right  = DEMO_FULL_WIDTH - m_iRightWidth ;
		rectConfig.bottom = DEMO_FULL_HEIGHT - m_iListLogHeight;//+4
		
		m_dlgLocalCfg->MoveWindow(&rectConfig,TRUE);
		m_dlgLocalCfg->ShowWindow(SW_HIDE);
		
		m_dlgRemoteCfg->MoveWindow(&rectConfig,TRUE);
		m_dlgRemoteCfg->ShowWindow(SW_SHOW);
		
		m_dlgIPAccess->MoveWindow(&rectConfig,TRUE);
		m_dlgIPAccess->ShowWindow(SW_SHOW);
		
		m_dlgHDConfig->MoveWindow(&rectConfig,TRUE);
		m_dlgHDConfig->ShowWindow(SW_SHOW);

		m_dlgBatchCfg->MoveWindow(&rectConfig,TRUE);
		m_dlgBatchCfg->ShowWindow(SW_SHOW);
		
		m_dlgConfigAll->MoveWindow(&m_rectRightArea,TRUE);
		m_dlgConfigAll->ShowWindow(SW_SHOW);
		m_dlgConfigAll->ConfigWndUpdate();
	}
}

/*********************************************************
Function:	OnBnClickedBtnPlayback
Desc:		switch to backplay interface
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnPlayback()
{
	if (m_iMainType != PLAY_BACK_T)
	{
		m_iMainType = PLAY_BACK_T;
		ListRestore();
		PreviewReferShow(FALSE);
		ConfigAllHide();
		InitPlayBackRefer();
	}
}

/*********************************************************
Function:	InitPlayBackRefer
Desc:		initialize backplay interface operation
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::InitPlayBackRefer()
{
	if (!m_dlgPlayBack->IsWindowVisible())
	{
		CRect rectPlayBack(0,0,0,0);	
		
		rectPlayBack.top    = m_iFunBtnHeight-2;
		rectPlayBack.left   = m_iTreeWidth-2;//-2 cover preview box
		rectPlayBack.right  = DEMO_FULL_WIDTH;
		rectPlayBack.bottom = DEMO_FULL_HEIGHT - m_iListLogHeight;//+4
		
		m_dlgPlayBack->MoveWindow(&rectPlayBack,TRUE);
		m_dlgPlayBack->PlayBackWinUpdate();
		m_dlgPlayBack->ShowWindow(SW_SHOW);
	}
}

/*********************************************************
Function:	OnBnClickedBtnRecord
Desc:		manually record uner preview interface
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnRecord()
{
	if (g_struLocalParam.bAutoRecord)
	{
		OnTimer(AUTORECORD_TIMER);
		return;
	}
	
	if ((g_dlgOutput[m_iCurWndIndex].m_lPlayHandle >= 0) && (!g_dlgOutput[m_iCurWndIndex].m_bLocalManualRec))
	{
		if (MakeRecDir())
		{
			g_dlgOutput[m_iCurWndIndex].StartLocalRecord();	
		}
	}
	else if (g_dlgOutput[m_iCurWndIndex].m_bLocalManualRec)
	{
		g_dlgOutput[m_iCurWndIndex].StopLocalRecord();
		g_dlgOutput[m_iCurWndIndex].m_bSaveHead = FALSE;
	}
}

/*********************************************************
Function:	MakeRecDir
Desc:		create record directory
Input:	
Output:	
Return:	TRUE,create successful;FALSE,create failed;
**********************************************************/
BOOL CClientDemoDlg::MakeRecDir()
{
	CString sTemp;
	DWORD dwDirAttr;
	CTime time = CTime::GetCurrentTime();
	char szLan[256] = {0};
	//m_iCurRecDriver = g_pMainDlg->m_cHardDriver[g_struLocalParam.iStartRecordDriver];
	sTemp.Format("%c:\\mpeg4record\\", m_iCurRecDriver);
	dwDirAttr = GetFileAttributes(sTemp);
	if ((dwDirAttr == -1) || !(dwDirAttr & FILE_ATTRIBUTE_DIRECTORY))
	{
		if (!CreateDirectory(sTemp, NULL))
		{
			g_StringLanType(szLan, "创建年月日目录失败", "create year-month-day directory failed");
			AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, szLan);
			AfxMessageBox(szLan);
			return FALSE;
		}	
	}
	else
	{
		sTemp.Format("%c:\\mpeg4record\\%4d-%02d-%02d\\", m_iCurRecDriver, time.GetYear(), time.GetMonth(), time.GetDay());
		dwDirAttr=GetFileAttributes(sTemp);
		if ((dwDirAttr == -1) || !(dwDirAttr & FILE_ATTRIBUTE_DIRECTORY))
		{
			if (!CreateDirectory(sTemp, NULL))
			{
				g_StringLanType(szLan, "创建年月日目录失败", "create year-month-day directory failed");
				AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, szLan);
				AfxMessageBox(szLan);
				return FALSE;
			}
			else
			{
				sprintf(g_struLocalParam.chClientRecordPath, "%s", sTemp.GetBuffer(0));
				AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "create %c:\\mpeg4record\\%4d-%02d-%02d", m_iCurRecDriver, time.GetYear(), time.GetMonth(), time.GetDay());
				return TRUE;
			}
		}
		else
		{
			sprintf(g_struLocalParam.chClientRecordPath, "%s", sTemp.GetBuffer(0));
			AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "create directory:%s", sTemp.GetBuffer(0));
			return TRUE;	
		}
	}
	
	sTemp.Format("%c:\\mpeg4record\\%4d-%02d-%02d\\",m_iCurRecDriver, time.GetYear(), time.GetMonth(), time.GetDay());
	if (!CreateDirectory(sTemp, NULL))
	{
		return FALSE;
	}
	sprintf(g_struLocalParam.chClientRecordPath, "%s", sTemp.GetBuffer(0));
	AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "create %c:\\mpeg4record first, then create %4d-%02d-%02d", m_iCurRecDriver, time.GetYear(), time.GetMonth(), time.GetDay());
	return TRUE;
}

/*********************************************************
Function:	IsDiskFull
Desc:		check disk full
Input:	
Output:	
Return:	TRUE,disk is full;FALSE,disk is not full
**********************************************************/
BOOL CClientDemoDlg::IsDiskFull()
{
	int i;
	ULARGE_INTEGER FreeSpace,CallerSpace,TotalSpace;
	CString csRecRootPath;	
	
	for (i = g_struLocalParam.iStartRecordDriver; i < g_struLocalParam.iEndRecordDriver + 1; i++)
	{	
		csRecRootPath.Format("%c%s",m_cHardDriver[i],":\\");	//start from hard driver
		GetDiskFreeSpaceEx(csRecRootPath,&CallerSpace,&TotalSpace,&FreeSpace);
		if (CallerSpace.QuadPart > MINSPACE)
		{
			m_iCurRecDriver = m_cHardDriver[i];
			g_struLocalParam.bAllDiskFull = FALSE;
			return	FALSE;
		}
	}
	g_struLocalParam.bAllDiskFull = TRUE;
	return TRUE;
}

/*********************************************************
Function:	DeleteClientRecordFile
Desc:		delete local record file
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::DeleteClientRecordFile()
{
	CFileFind cFile,cFileMp4;
	BOOL bFineDir,bFileFind;
	CString sDeleteDir,sTempDelete;
	CString sDir;
	CString sDate;
	CString sFileName;
	CTime time,temptime;
	
	int i = 0;
	//	int iDelNum = 0;
	sDeleteDir.Format("0000-00-00");
	sTempDelete.Format("3000-00-00");
	
	time=CTime::GetCurrentTime();
	
	for (i = g_struLocalParam.iStartRecordDriver; i < (g_struLocalParam.iEndRecordDriver + 1); i++)
	{
		sDir.Format("%c:\\mpeg4record\\*.*",m_cHardDriver[i]);
		bFineDir=cFile.FindFile(sDir);//judge whether the current directory has files
		while (bFineDir)
		{
			bFineDir=cFile.FindNextFile();
			if (cFile.IsDots())//'.'mean current directory, & '..' means up directory.
			{
				continue;
			}
			if (cFile.IsDirectory())
			{
				if (cFile.GetFileName()==_T("download"))//not download record
				{
					continue;
				}
				if (cFile.GetFileName()==_T("alarm"))//not alarm record
				{
					continue;
				}
				sFileName.Format("%c:\\mpeg4record\\%s\\*.mp4", m_cHardDriver[i], cFile.GetFileName().GetBuffer(0));
				bFileFind=cFileMp4.FindFile(sFileName);
				if (!bFileFind)
				{
					RemoveDirectory(cFile.GetFilePath());
					AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, cFile.GetFilePath().GetBuffer(0));
				}
				while (bFileFind)
				{
					bFileFind=cFileMp4.FindNextFile();
					if (cFile.IsDots())
					{
						continue;
					}
					cFileMp4.GetCreationTime(temptime);
					if (temptime<time)
					{
						time=temptime;
						sTempDelete.Format("%s",cFileMp4.GetFilePath().GetBuffer(0));
					}
				}
			}			
		}
	}
	sFileName.Format("%s",sTempDelete.GetBuffer(0));
	sTempDelete.Format("delete[%s]",sFileName.GetBuffer(0));
	if (!DeleteFile(sFileName))
	{
		AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T,sTempDelete.GetBuffer(0));
		for (i = 0; i < MAX_OUTPUTS; i++)
		{
			if ((g_dlgOutput[i].m_lPlayHandle >= 0) || (g_dlgOutput[i].m_bLocalManualRec))
			{
				g_dlgOutput[i].StopLocalRecord();
			}
		}
		char szLan[128] = {0};
		g_StringLanType(szLan, "硬盘容量不足，自动删除文件失败，请清理硬盘后重新开始录像！",\
			"Lack of hard drive capacity, automatic delete file failed, please clean up after the hard disk to start record!");
		AfxMessageBox(szLan);
	}
	else
	{
		AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, sTempDelete.GetBuffer(0));
		//iDelNum++;
	}
}

/*********************************************************
Function:	OnBnClickedBtnManage
Desc:		advanded management operantion
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnManage()
{
	CMenu pMenu;
	CRect cRectBtnManage(0,0,0,0);
	//GetCursorPos(&pt);
	GetDlgItem(IDC_BTN_MANAGE)->GetWindowRect(&cRectBtnManage);
	//select first node or blank
	
	if (!pMenu.LoadMenu(IDR_MENU_MANAGE))
	{
		return;
	}
	
	pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,cRectBtnManage.left ,cRectBtnManage.bottom,this);
}

/*********************************************************
Function:	OnMenuUpgrade
Desc:		device upgrade
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuUpgrade()
{
	int iDeviceIndex = GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return;
	}
	
	
    int iChanIndex = GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;
    }

	CDlgUpgrade dlgUpgrade;
	dlgUpgrade.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	dlgUpgrade.m_lChannel = iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
	dlgUpgrade.m_iDeviceIndex = iDeviceIndex;
	dlgUpgrade.DoModal();
}

/*********************************************************
Function:	OnMenuReboot
Desc:		device reboot
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuReboot()
{
	int iDeviceIndex = GetCurDeviceIndex();
	int i = 0;
	char szLan[128] = {0};
	
	if (iDeviceIndex == -1)
	{
		return;
	}
	g_StringLanType(szLan, "确定要重启设备?", "Sure to reboot device?");
	if (IDOK!=MessageBox(szLan, "Warning",IDOK))
	{
		return;
	}
	if (NET_DVR_RebootDVR(g_struDeviceInfo[iDeviceIndex].lLoginID))
	{
		g_struDeviceInfo[iDeviceIndex].bAlarm = FALSE;
		g_struDeviceInfo[iDeviceIndex].bPlayDevice = FALSE;
		g_struDeviceInfo[iDeviceIndex].bVoiceTalk = FALSE;
		//		g_struDeviceInfo[iDeviceIndex].dwImageType = DEVICE_LOGOUT;
		
		for (i = 0; i<MAX_CHANNUM_V30; i++)
		{
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = FALSE;
		}
		AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RebootDVR");
		g_StringLanType(szLan, "设备正在重启", "Device is rebooting");
		AfxMessageBox(szLan);
	}
	else
	{
		AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RebootDVR");
		g_StringLanType(szLan, "设备重启失败", "Reboot device failed");
		AfxMessageBox(szLan);	
	}
}

/*********************************************************
Function:	OnMenuHDFormat
Desc:		disk format
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuHDFormat()
{
	int iDeviceIndex = GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return;
	}
	CDlgFormatHD dlgFormatDisk;
	dlgFormatDisk.m_iDeviceIndex = iDeviceIndex;
	dlgFormatDisk.m_dwDiskNum = g_struDeviceInfo[iDeviceIndex].iDiskNum;
	dlgFormatDisk.DoModal();
}

/*********************************************************
Function:	OnMenuPoweroff
Desc:		power off
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuPoweroff()
{
	
	int iDeviceIndex = GetCurDeviceIndex();
	char szLan[128] = {0};
	
	if (iDeviceIndex == -1)
	{
		return;
	}
	g_StringLanType(szLan, "确定要关闭设备?", "Sure to shut down device?");
	if (IDOK!=MessageBox(szLan, "Warning",IDOK))
	{
		return;
	}
	
	if (NET_DVR_ShutDownDVR(g_struDeviceInfo[iDeviceIndex].lLoginID))
	{
		AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_ShutDownDVR");
		g_StringLanType(szLan, "设备正在关机", "Device is shutting down");
		AfxMessageBox(szLan);
	}
	else
	{
		AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ShutDownDVR");
		g_StringLanType(szLan, "设备关机失败", "Shut down device failed");
		AfxMessageBox(szLan);
	}
}

/*********************************************************
Function:	OnMenuFortify
Desc:		switch between setting guard and removing guard 
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuFortify()
{
	CDlgFortify dlg;
	int i = 0;
	dlg.DoModal();
	if (dlg.m_bFortify)
	{
		for (i=0; i<MAX_DEVICES; i++)
		{
			if (g_struDeviceInfo[i].lLoginID >= 0)
			{
				::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_DEVICE_ITEM_IMAGE, WPARAM(GetDeviceItem(i)), LPARAM(i));
			}		
		}
	}
	
}

/*********************************************************
Function:	OnMenuVoiceTalk
Desc:		start or stop voice talk
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuVoiceTalk()
{
	int iDeviceIndex = GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return;
	}
	CDlgVoiceTalk dlg;
	dlg.m_dwDeviceIndex = iDeviceIndex;
	dlg.DoModal();
}

/*********************************************************
Function:	OnMenuSerialTrans
Desc:		transport the data on serial ports
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnMenuSerialTrans()
{
	int iDeviceIndex = GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return;
	}
	CTransparentTrans dlg;
	dlg.m_iDeviceIndex = iDeviceIndex;
	dlg.DoModal();
}

void CClientDemoDlg::OnMenuDebug()
{
    int iDeviceIndex = GetCurDeviceIndex();
    if (iDeviceIndex == -1)
    {
        return;
	}
	
    CDlgDebug dlg;
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	dlg.DoModal();
}

void CClientDemoDlg::OnMenuUploadCalibrationFile()
{
    int iDeviceIndex = GetCurDeviceIndex();
    if (iDeviceIndex == -1)
    {
        return;
    }
    
    CDlgUploadCalibrationFile dlg;
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.DoModal();
}

void CClientDemoDlg::OnMenuIperf()
{
	CDlgIperf dlg;
	dlg.DoModal(); 
}

void CClientDemoDlg::OnMenuCompleteRestore()
{
    int iDeviceIndex = GetCurDeviceIndex();
    char szLan[128] = {0};
    
    if (iDeviceIndex == -1)
    {
        return;
    }
	
    int iChanIndex = GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;
    }
	
    g_StringLanType(szLan, "确定要完全恢复默认参数?", "Sure to Complete restore the default parameters?");
    if (IDOK!=MessageBox(szLan, "Warning",IDOK))
    {
        return;
    }
    
    if (g_struDeviceInfo[iDeviceIndex].lLoginID<0)
    {
        return;
	}
	
    NET_DVR_COMPLETE_RESTORE_INFO m_struRestoreInfo = {0};
    m_struRestoreInfo.dwSize = sizeof(NET_DVR_COMPLETE_RESTORE_INFO);
    m_struRestoreInfo.dwChannel = iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
	
    if (!NET_DVR_RemoteControl(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_COMPLETE_RESTORE_CTRL, &m_struRestoreInfo, sizeof(NET_DVR_COMPLETE_RESTORE_INFO)))
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_COMPLETE_RESTORE_CTRL ");
		g_StringLanType(szLan, "恢复默认值失败", "Restore the default parameters failed");
		AfxMessageBox(szLan);//DS9000 restore configure, reboot auto
    }
    else
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_COMPLETE_RESTORE_CTRL");
        g_StringLanType(szLan, "恢复默认值成功，请重启", "Restore the default parameters successfully");
		AfxMessageBox(szLan);
	}
}
/*********************************************************
Function:	OnMenuDefaultConfig
Desc:		restore the default configure of the device
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnMenuDefaultConfig()
{
	int iDeviceIndex = GetCurDeviceIndex();
	char szLan[128] = {0};
	
	if (iDeviceIndex == -1)
	{
		return;
	}
	g_StringLanType(szLan, "确定要恢复默认参数?", "Sure to restore the default parameters?");
	if (IDOK!=MessageBox(szLan, "Warning",IDOK))
	{
		return;
	}
	
	
	if (g_struDeviceInfo[iDeviceIndex].lLoginID<0)
	{
		return;
	}
	
	if (NET_DVR_RestoreConfig(g_struDeviceInfo[iDeviceIndex].lLoginID))
	{
		AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RestoreConfig");
		g_StringLanType(szLan, "恢复默认值成功，请重启", "Restore the default parameters successfully");
		AfxMessageBox(szLan);//DS9000 restore configure, reboot auto
	}
	else
	{
		AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RestoreConfig");
		g_StringLanType(szLan, "恢复默认值失败", "Restore the default parameters failed");
		AfxMessageBox(szLan);	
	}
}


/*********************************************************
Function:	OnMenuConfigFlash
Desc:		set or get the configure file
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnMenuConfigFlash()
{
	CDlgConfigFlash dlg;
	dlg.DoModal();
}

/*********************************************************
Function:	OnMenuImExportIPCCfgFile
Desc:		set or get the configure file
Input:	none
Output:	none
Return:	none
**********************************************************/
// void CClientDemoDlg::OnMenuImExportIPCCfgFile()
// {
// 	DlgImexporIPCCfgFile dlg;
// 	dlg.DoModal();
// }

/*********************************************************
Function:	OnMenuTalkMR
Desc:		voice media redirect
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnMenuTalkMR()
{
	CDlgTalkMREx dlg;
	int iDevIndex = GetCurDeviceIndex();
	if (iDevIndex < 0)
	{
		return;
	}
	dlg.m_iDeviceIndex = iDevIndex;
	dlg.DoModal();
}

/*********************************************************
Function:	OnBnClickedBtnPictureSnatch
Desc:		capture pic in bmp under preview
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::PictureSnatchInSide()
{
	int i = m_iCurWndIndex;
	
	if (g_dlgOutput[i].m_lPlayHandle < 0)
	{
		return;
	}
	char cFilename[256];
	CString sTemp;
	CTime time = CTime::GetCurrentTime();
	sTemp.Format("%s\\", g_struLocalParam.chPictureSavePath);		
	DWORD dwRet = GetFileAttributes(sTemp);
	if ((dwRet == -1) || !(dwRet & FILE_ATTRIBUTE_DIRECTORY))
	{
		CreateDirectory(sTemp, NULL);
	}
	PCHANNEL_INFO pChanInfo = &(g_dlgOutput[i].m_struChanInfo);
	sprintf(cFilename, "%s\\Preview_%s_%02d_%4d%02d%02d_%02d%02d%02d_%d.bmp", \
		g_struLocalParam.chPictureSavePath, g_struDeviceInfo[pChanInfo->iDeviceIndex].chDeviceIPInFileName, \
		g_struDeviceInfo[pChanInfo->iDeviceIndex].iStartChan+pChanInfo->iChanIndex,	\
		time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), GetTickCount());
	if (g_struLocalParam.bUseCard)
	{			
		if (NET_DVR_CapturePicture_Card(g_dlgOutput[i].m_lPlayHandle, cFilename))
		{
			CString sTemp;	
			sTemp.Format("Capture picture succeed %s!",cFilename);
			AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, sTemp.GetBuffer(0));
			return;
		}
		else
		{
			AfxMessageBox("Failed to capture picture!");
		}
	}
	else
	{
		if (NET_DVR_CapturePicture(g_dlgOutput[i].m_lPlayHandle, cFilename))
		{
			AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CapturePicture[%s]", cFilename);
		}
		else
		{
			AddLog(m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CapturePicture[%s]", cFilename);
			char szLan[128] = {0};
			g_StringLanType(szLan, "bmp抓图失败", "bmp snatch failed");
			AfxMessageBox(szLan);
		}
	}
}

void CClientDemoDlg::OnBnClickedBtnPictureSnatch()
{
	if (g_bInSide)
	{
		PictureSnatchInSide();
		return;
	}
	if (g_struLocalParam.bUseCard)
	{
		g_dlgOutput[m_iCurWndIndex].CapturePicture();
	}
	
	g_bCapPic[m_iCurWndIndex] = TRUE;
}

/*********************************************************
Function:	OnMenuBroadCast
Desc:		audio broadcast deal
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnMenuBroadCast()
{
	CBroadCast dlg;
	dlg.DoModal();
}

/*********************************************************
Function:	OnBnClickedBtnLogClear
Desc:		clear up all log items in list
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnLogClear()
{
	char szLan[128] = {0};
	g_StringLanType(szLan, "确定清空列表吗?", "Sure to clear list?");
	if (IDOK==MessageBox(szLan,"Warning",IDOK))
	{
		if (m_iSelListType == 1)
		{
			m_listAlarmInfo.DeleteAllItems();
			for (int i = 0; i< MAX_DEVICES; i++)
			{
				if (g_struDeviceInfo[i].lFortifyHandle >= 0)
				{
					ManualClearAlarm(i, -1);
				}
			}
		}
		else
		{
			m_listAllLog.DeleteAllItems();
		}	
	}
}

/*********************************************************
Function:	OnBnClickedBtnLogSave
Desc:		save all the log items in list
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnLogSave()
{
	CString csFileName;
	CTime time;
	if (g_struLocalParam.bAutoSaveLog)
	{
		return;
	}
	int i;
	CString sTemp;
	CStdioFile myFile;
	
	int iCount = 0;
	
	time = CTime::GetCurrentTime();
	
	if (m_iSelListType == 1)
	{
		iCount = m_listAlarmInfo.GetItemCount();
		csFileName.Format("%s\\AlarmInfo_%4d%02d%02d_%02d%02d%02d.txt",\
			g_struLocalParam.chRemoteCfgSavePath, time.GetYear(), time.GetMonth(),\
			time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	}
	else
	{
		iCount = m_listAllLog.GetItemCount();
		csFileName.Format("%s\\LogFile_%4d%02d%02d_%02d%02d%02d.txt",\
			g_struLocalParam.chRemoteCfgSavePath, time.GetYear(), time.GetMonth(),\
			time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	}
	if (iCount <=  0)
	{
		return;
	}
	if (myFile.Open(csFileName, CFile::modeCreate|CFile::modeWrite) == FALSE)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "文件创建失败", "create file failed");
		AfxMessageBox(szLan);
		return;
	}
	for (i = 0; i < iCount; i++)
	{
		if (m_iSelListType == 1)
		{
			sTemp.Format("%s\t%s\n", m_listAllLog.GetItemText(i, 1).GetBuffer(0),\
				m_listAllLog.GetItemText(i, 2).GetBuffer(0));
		}
		else
		{
			sTemp.Format("%s\t%s\t%s\t%s\r\n", m_listAllLog.GetItemText(i, 1).GetBuffer(0),\
				m_listAllLog.GetItemText(i, 2).GetBuffer(0), m_listAllLog.GetItemText(i, 3).GetBuffer(0),\
				m_listAllLog.GetItemText(i, 4).GetBuffer(0));
		}
		
		myFile.WriteString(sTemp);
	}
	myFile.Close();
}

/*********************************************************
Function:	ManualClearAlarm
Desc:		clear alarm manually
Input:	iDeviceIndex,device index; iChanIndex,channel index, -1 clear all channel;
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::ManualClearAlarm(int iDeviceIndex, int iChanIndex)
{
	CString csTemp;
	int i=0;
	if (iChanIndex == -1)
	{//select device node
		//give out hints while switch alarm logo
		if (g_struDeviceInfo[iDeviceIndex].bAlarm)
		{
			g_struDeviceInfo[iDeviceIndex].bAlarm = FALSE;
			::PostMessage(m_hWnd, WM_CHANGE_DEVICE_ITEM_IMAGE, WPARAM(GetDeviceItem(iDeviceIndex)), LPARAM(iDeviceIndex));		
		}
		
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable && g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm)
			{
				g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = FALSE;
				AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "ch[%d] clear alarm status", i+g_struDeviceInfo[iDeviceIndex].iStartChan);
				::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));	
			}
		}
	}
	else
	{
		if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].bAlarm)
		{
			g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].bAlarm = FALSE;
			AddLog(m_iCurDeviceIndex, OPERATION_SUCC_T, "ch[%d] clear alarm status", iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan);
			::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(m_iCurDeviceIndex), LPARAM(iChanIndex));		
		}
	}
}

/*********************************************************
Function:	OnBnClickedBtnLogConfig
Desc:		local log configuration
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnLogConfig()
{
	CDlgLocalLogConfig dlg;
	dlg.DoModal();
}

/*********************************************************
Function:	IsCurDevMatDec
Desc:		check current device is decoder
Input:	
Output:	
Return:	
**********************************************************/
BOOL CClientDemoDlg::IsCurDevMatDec(int iDeviceIndex)
{
	BOOL bRet = FALSE;
	if (iDeviceIndex != -1)
	{
		if (DEC == g_struDeviceInfo[iDeviceIndex].iDeviceType||DEC_MAT == g_struDeviceInfo[iDeviceIndex].iDeviceType || \
			DS_6504D_B10 == g_struDeviceInfo[iDeviceIndex].iDeviceType||DS630X_D == g_struDeviceInfo[iDeviceIndex].iDeviceType
			|| DS640X_HD == g_struDeviceInfo[iDeviceIndex].iDeviceType \
			|| DS_B10_XY == g_struDeviceInfo[iDeviceIndex].iDeviceType || DS610X_D == g_struDeviceInfo[iDeviceIndex].iDeviceType) 
		{
			bRet = TRUE;
		}
	}
	return TRUE;
}

/*********************************************************
Function:	IsNeedRebootDevType
Desc:		some devices(8-ch,16-ch 7000,8000HS_S)need to reboot after modifying resolution
Input:	
Output:	
Return:	
**********************************************************/
BOOL CClientDemoDlg::IsNeedRebootDevType(void)
{
	int iDevIndex = GetCurDeviceIndex();
	BOOL bRet = FALSE;
	if (iDevIndex != -1)
	{
		if ((DVR_HS_S == g_struDeviceInfo[iDevIndex].iDeviceType)\
			||(( DVR_7000H== g_struDeviceInfo[iDevIndex].iDeviceType) && (g_struDeviceInfo[iDevIndex].iDeviceChanNum == 8))\
			||(( DVR_7000H== g_struDeviceInfo[iDevIndex].iDeviceType) && (g_struDeviceInfo[iDevIndex].iDeviceChanNum == 16)))
		{
			bRet = TRUE;
		}
	}
	return bRet;
}

/*********************************************************
Function:	OnNMClickListAllLog
Desc:		Copy the contents to the clipboard
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnNMClickListAllLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iItemSel = 0;
	CString csTxt;
	
	POSITION  iPos = m_listAllLog.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	iItemSel = m_listAllLog.GetNextSelectedItem(iPos);
	csTxt.Format("%s",m_listAllLog.GetItemText(iItemSel,3));
	if (OpenClipboard())   
	{   
		HGLOBAL   clipbuffer;   
		char   *   buffer;   
		EmptyClipboard();   
		clipbuffer   =   GlobalAlloc(GMEM_DDESHARE,  csTxt.GetLength()+1);   
		buffer   =   (char*)GlobalLock(clipbuffer);   
		strcpy(buffer,   LPCSTR(csTxt));   
		GlobalUnlock(clipbuffer);   
		SetClipboardData(CF_TEXT,clipbuffer);   
		CloseClipboard();   
	}   
	*pResult = 0;
}

/*********************************************************
Function:	PreTranslateMessage
Desc:		capture push enter button or esc button
Input:	none
Output:	none
Return:	none
**********************************************************/
BOOL CClientDemoDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE)
	{
		if (g_struLocalParam.bFullScreen)
		{
			g_struLocalParam.bEnlarged    = FALSE;
			g_struLocalParam.bMultiScreen = FALSE;
			g_struLocalParam.bFullScreen  = FALSE;
			g_pMainDlg->GetDlgItem(IDC_COMBO_WNDNUM)->EnableWindow(TRUE);
			g_pMainDlg->FullScreen(g_struLocalParam.bFullScreen);
			if (g_struLocalParam.bFullScreen)
			{
				g_pMainDlg->ArrangeOutputs(g_pMainDlg->m_iCurWndNum);
			}
			else//multi-pic zoom
			{
				g_pMainDlg->ArrangeOutputs(g_pMainDlg->m_iCurWndNum);
				
				g_pMainDlg->GetDlgItem(IDC_STATIC_PREVIEWBG)->Invalidate(TRUE);
			}
		}
		else
		{
			GetDlgItem(IDC_BTN_TEST)->ShowWindow(SW_HIDE);
		}
		return TRUE;
	}
	if (pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	{
		GetDlgItem(IDC_BTN_TEST)->ShowWindow(SW_SHOW);
		return TRUE; 
	}
	else
	{
		return CDialog::PreTranslateMessage(pMsg);
	}
}

/*********************************************************
Function:	OnBnClickedBtnExit
Desc:		leave response function, release resource and exit demo
Input:	
Output:	
Return:	
**********************************************************/
void CClientDemoDlg::OnBnClickedBtnExit()
{
	char szLan[128] = {0};
	g_bExitDemo = TRUE;//make not post message
	g_StringLanType(szLan, "确定要退出吗?", "Sure to exit?");
	if (IDOK != MessageBox(szLan,"Warning",IDOK))
	{
		return;
	}
	StopPlayAll();//stop all previews
	m_dlgPlayBack->FinishAll();//stop all play back
	if (m_pCyclePlayTimer)
	{
		KillTimer(CYCLE_PREVIEW_TIMER); 
		m_pCyclePlayTimer = 0;
	}
	if (m_pFreeSpaceTimer)
	{
		KillTimer(FREESPACE_TIMER);
		m_pFreeSpaceTimer = 0;
	}
	if (m_pFileIntervalTimer)
	{
		KillTimer(FILEINTERVAL_TIMER);
		m_pFileIntervalTimer = 0;
	}
	if (m_pChkDevTimer)
	{
		KillTimer(CHECK_DEVICE_TIMER);
		m_pChkDevTimer = 0;
	}
	if (m_pSysTimer)
	{
		KillTimer(SYSTEM_TIMER);
		m_pSysTimer=0;
	}
	
	if (g_struLocalParam.bUseCard)
	{
		NET_DVR_ReleaseDevice_Card();
		NET_DVR_ReleaseDDraw_Card();
	}
	
	if (m_lListenHandle > 0)
	{
		NET_DVR_StopListen_V30(m_lListenHandle); 
	}
	
	if (g_struLocalParam.bBroadCast)
	{
		NET_DVR_ClientAudioStop();
	}
	
	//remove guard, log out
	int i = 0, j = 0;
	for (i=0; i<MAX_DEVICES; i++)  
	{
		if (g_struDeviceInfo[i].lLoginID >= 0)
		{
			for (j=0; j<MAX_AUDIO_V40; j++)
			{
				if (g_struDeviceInfo[i].lVoiceCom[j] >= 0)
				{
					if (NET_DVR_StopVoiceCom(g_struDeviceInfo[i].lVoiceCom[j]))
					{
						g_struDeviceInfo[i].lVoiceCom[j] = -1;
					}
				}			
			}
			
			if (g_struDeviceInfo[i].lFortifyHandle >= 0)
			{
				if (NET_DVR_CloseAlarmChan(g_struDeviceInfo[i].lFortifyHandle))
				{
					g_struDeviceInfo[i].lFortifyHandle = -1;
				}
			}
			
			NET_DVR_Logout_V30(g_struDeviceInfo[i].lLoginID);
			
			g_struDeviceInfo[i].lLoginID = -1;
		}
	}

	//2011-11-16退出被动解码
	int iPassiveChanIndex = 0;
	CString csStr;
	for (i=0; i<MAX_DEVICES; i++)
	{
		//64-T解码器被动解码通道为32个
		for (int iPassiveChanIndex=0; iPassiveChanIndex<32; iPassiveChanIndex++)
		{
			if (g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].lRealHandle >= 0)
			{
				NET_DVR_SetRealDataCallBack(g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].lRealHandle, NULL, iPassiveChanIndex);
				if (!NET_DVR_StopRealPlay(g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].lRealHandle))
				{
					g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_StopRealPlay FAILED");
				}
				else
				{
					g_pMainDlg->AddLog(i, OPERATION_SUCC_T, "NET_DVR_StopRealPlay SUCC");
					g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].lRealHandle = -1;
				}
			}
			if (g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].lUserID >= 0)
			{
				if (!NET_DVR_Logout(g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].lUserID))
				{
					g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_Logout FAILED");
				}
				else
				{
					g_pMainDlg->AddLog(i, OPERATION_SUCC_T, "NET_DVR_Logout SUCC");
					g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].lUserID = -1;
				}
			}  
			if (g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].hFileThread != NULL)
			{
				SetEvent(g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].hExitThread);
				WaitForSingleObject(g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].hThreadExit, INFINITE);
				TRACE("### Wait for Thread Exit...\n");
			}
			if (g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].lPassiveHandle >= 0)
			{
				if (!NET_DVR_MatrixStopPassiveDecode(g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].lPassiveHandle))
				{
					g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_MatrixStopPassiveDecode FAILED");
					//return;
				}
				else
				{
					g_pMainDlg->AddLog(i, OPERATION_SUCC_T, "NET_DVR_MatrixStopPassiveDecode SUCC");
					g_struDeviceInfo[i].struPassiveDecode[iPassiveChanIndex].lPassiveHandle = -1; 
				}   
			} 
		}
		
	}

	g_SaveDeviceConfig();
	i = 0;
	
	CDialog::OnCancel();
}

/*********************************************************
Function:	OnCancel
Desc:		shutdown button response deal
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnCancel()
{
	OnBnClickedBtnExit();
}

/*********************************************************
Function:	DoGetDeviceResoureCfg
Desc:		get input device IP parameters
Input:	iDeviceIndex, the device index
Output:	none
Return:	TRUE/FALSE
**********************************************************/
BOOL CClientDemoDlg::DoGetDeviceResoureCfg(int iDeviceIndex, int iGroupNO)
{
	int i = 0;
	CString csTemp;
	LPNET_DVR_IPPARACFG_V40 lpIPAccessCfgV40 = &g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[iGroupNO];
 	DWORD dwReturned = 0;
    if (lpIPAccessCfgV40 == NULL)
    {
        return FALSE;
    }
    memset(lpIPAccessCfgV40, 0, sizeof(NET_DVR_IPPARACFG_V40));
    //2008-9-15 13:44 ip input configuration
    g_struDeviceInfo[iDeviceIndex].bIPRet = NET_DVR_GetDVRConfig(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_GET_IPPARACFG_V40, iGroupNO, &g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[iGroupNO], sizeof(NET_DVR_IPPARACFG_V40), &dwReturned);
    if (!g_struDeviceInfo[iDeviceIndex].bIPRet && g_struDeviceInfo[iDeviceIndex].byLoginModeRes == 0)
    {	///device no support ip access
        if (g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_B20_MSU_NP || \
            g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_MMC_B20_CLASS || \
            g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_B21_MCU_NP_CLASS || \
            g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_C20N_VWMS || \
            g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_AIOH_MCU_NP || \
            g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_Y10_MCU) //B20/B21主控
        {
            //这里不需要做任何处理
        }
        else
        {
            g_struDeviceInfo[iDeviceIndex].lFirstEnableChanIndex = 0;
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_IPPARACFG_V40");
            for (i = 0; i < MAX_CHANNUM_V30; i++)
            {
                if (i < g_struDeviceInfo[iDeviceIndex].iAnalogChanNum)
                {
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iDeviceIndex = iDeviceIndex;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex = i;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO = i + g_struDeviceInfo[iDeviceIndex].iStartChan;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable = TRUE;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanType = DEMO_CHANNEL_TYPE_ANALOG;
                    sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName, ANALOG_C_FORMAT, i + g_struDeviceInfo[iDeviceIndex].iStartChan);
                }
                else//clear the state of other channel
                {
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iDeviceIndex = -1;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex = -1;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable = FALSE;
                    sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName, "");
                }
            }

            g_struDeviceInfo[iDeviceIndex].iGroupNO = -1;
        }
    }
    else
    {
        //ISAPI登录时，NET_DVR_GET_IPPARACFG_V40会失败，此时利用登录返回参数刷新数组通道
        if (g_struDeviceInfo[iDeviceIndex].byLoginModeRes == 1)
        {
            for (i = 0; i < MAX_CHANNUM_V30; i++)
            {
                if (i < g_struDeviceInfo[iDeviceIndex].iIPChanNum)
                {
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iDeviceIndex = iDeviceIndex;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex = i;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO = i + g_struDeviceInfo[iDeviceIndex].iStartChan;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable = TRUE; //此处默认显示在线，因为暂时没有获取状态，通过这个获取/ISAPI/ContentMgmt/InputProxy/channels/status
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanType = DEMO_CHANNEL_TYPE_IP;
                    sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName, DIGITAL_C_FORMAT, i + g_struDeviceInfo[iDeviceIndex].iStartChan);
                }
                else//clear the state of other channel
                {
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iDeviceIndex = -1;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex = -1;
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable = FALSE;
                    sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName, "");
                }
            }

            lpIPAccessCfgV40->dwDChanNum = g_struDeviceInfo[iDeviceIndex].iIPChanNum;
            lpIPAccessCfgV40->dwStartDChan = g_struDeviceInfo[iDeviceIndex].iStartChan;
        }

        g_struDeviceInfo[iDeviceIndex].iGroupNO = iGroupNO;
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_IPPARACFG_V40");
        RefreshIPDevLocalCfg(iDeviceIndex);
    }

	if (g_struDeviceInfo[iDeviceIndex].byMirrorChanNum > 0 && g_struDeviceInfo[iDeviceIndex].wStartMirrorChanNo > g_struDeviceInfo[iDeviceIndex].iDeviceChanNum)
    {
        for (i=0; i<g_struDeviceInfo[iDeviceIndex].byMirrorChanNum&&i < 16; i++)
        {
            if (1)
            {
                g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].iDeviceIndex = iDeviceIndex;
                g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].iChanIndex = i+MIRROR_CHAN_INDEX;
                sprintf(g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].chChanName, "MirrorChan%d", i+1);	
                //analog devices
                if (1)
                {
                    g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].bEnable = TRUE;
                    g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].dwImageType = CHAN_ORIGINAL;
					g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].iChannelNO = i + g_struDeviceInfo[iDeviceIndex].wStartMirrorChanNo;
                    //				g_struDeviceInfo[iDeviceIndex].iEnableChanNum ++;
                }
                else
                {
                    g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].dwImageType = CHAN_OFF_LINE;
                    g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].bEnable = FALSE;		
                }
            }
        }
    }
    if (g_struDeviceInfo[iDeviceIndex].byZeroChanNum > 0)
    {
        for (i=0; i<g_struDeviceInfo[iDeviceIndex].byZeroChanNum; i++)
        {
            if (1)
            {
                g_struDeviceInfo[iDeviceIndex].struZeroChan[i].iDeviceIndex = iDeviceIndex;
                g_struDeviceInfo[iDeviceIndex].struZeroChan[i].iChanIndex = i+ZERO_CHAN_INDEX;
                sprintf(g_struDeviceInfo[iDeviceIndex].struZeroChan[i].chChanName, "ZeroChan%d", i);	
                //analog devices
                if (1)
                {
                    g_struDeviceInfo[iDeviceIndex].struZeroChan[i].bEnable = TRUE;
                    g_struDeviceInfo[iDeviceIndex].struZeroChan[i].dwImageType = CHAN_ORIGINAL;
                    //				g_struDeviceInfo[iDeviceIndex].iEnableChanNum ++;
                }
                else
                {
                    g_struDeviceInfo[iDeviceIndex].struZeroChan[i].dwImageType = CHAN_OFF_LINE;
                    g_struDeviceInfo[iDeviceIndex].struZeroChan[i].bEnable = FALSE;		
                }
            }
        }
    }
	return g_struDeviceInfo[iDeviceIndex].bIPRet;
}

/*********************************************************
Function:	DoGetIPAlarmInCfg
Desc:		get device alarm input configuration
Input:	iDeviceIndex, the device index
		bSupportMultiGroup, support multi group
		GroupNo, group number
Output:	none
Return:	TRUE/FALSE
**********************************************************/
BOOL CClientDemoDlg::DoGetIPAlarmInCfg(int iDeviceIndex, BOOL bSupportMultiGroup, int GroupNO)
{
	int i = 0;
	char szTmp[1024*5] = { 0 };
	char szTmp1[32] = {0};
	DWORD dwReturned = 0;
//	memset(&g_struDeviceInfo[iDeviceIndex].struAlarmInCfg, 0, sizeof(NET_DVR_IPALARMINCFG));
	if (g_struDeviceInfo[iDeviceIndex].pStruIPAlarmInCfgV40 == NULL)
    {
        return FALSE;
    }
    memset(g_struDeviceInfo[iDeviceIndex].pStruIPAlarmInCfgV40, 0, sizeof(NET_DVR_IPALARMINCFG_V40));

	if (bSupportMultiGroup)
	{
		g_struDeviceInfo[iDeviceIndex].bIPRet = NET_DVR_GetDVRConfig(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_GET_IP_ALARM_IN, GroupNO, &g_struDeviceInfo[iDeviceIndex].struAlarmInCfg, sizeof(NET_DVR_IPALARMINCFG), &dwReturned);
	} 
	else
	{
		g_struDeviceInfo[iDeviceIndex].bIPRet = NET_DVR_GetDVRConfig(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_GET_IPALARMINCFG_V40, 0,  g_struDeviceInfo[iDeviceIndex].pStruIPAlarmInCfgV40 , sizeof(NET_DVR_IPALARMINCFG_V40), &dwReturned);
	}
	
	if (g_struDeviceInfo[iDeviceIndex].bIPRet)
	{	//8000 device
// 		for (i=0; i< MAX_IP_ALARMIN; i++)
// 		{
// 			if (g_struDeviceInfo[iDeviceIndex].struAlarmInCfg.struIPAlarmInInfo[i].byIPID != 0)
// 			{
// 				sprintf(szTmp1, "%d[%d-%d]", i, g_struDeviceInfo[iDeviceIndex].struAlarmInCfg.struIPAlarmInInfo[i].byIPID, \
// 					g_struDeviceInfo[iDeviceIndex].struAlarmInCfg.struIPAlarmInInfo[i].byAlarmIn);
// 				strcat(szTmp, szTmp1);
// 			}
// 		}
		for (i= 0; i < MAX_IP_ALARMIN_V40; i++)
        {
            if (g_struDeviceInfo[iDeviceIndex].pStruIPAlarmInCfgV40->struIPAlarmInInfo[i].dwIPID != 0)
            {
                sprintf(szTmp1, "%d[%d-%d]", i, g_struDeviceInfo[iDeviceIndex].pStruIPAlarmInCfgV40->struIPAlarmInInfo[i].dwIPID, \
					g_struDeviceInfo[iDeviceIndex].pStruIPAlarmInCfgV40->struIPAlarmInInfo[i].dwAlarmIn);
				strcat(szTmp, szTmp1);
            }
        }

		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_IPALARMINCFG:%s", szTmp);
	} 
	else
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_IPALARMINCFG");
	}
	
	return g_struDeviceInfo[iDeviceIndex].bIPRet;
}

/*********************************************************
Function:	DoGetIPAlarmOutCfg
Desc:		get device output configuration
Input:	iDeviceIndex, the device index
		bSupportMultiGroup, support multi group
		GroupNo, group number
Output:	none
Return:	TRUE/FALSE
**********************************************************/
BOOL CClientDemoDlg::DoGetIPAlarmOutCfg(int iDeviceIndex, BOOL bSupportMultiGroup, int GroupNO)
{
	int i = 0;
	char szTmp[1024] = {0};
	char szTmp1[32] = {0};
	DWORD dwReturned = 0;
//	memset(&g_struDeviceInfo[iDeviceIndex].struAlarmOutCfg, 0, sizeof(NET_DVR_IPALARMOUTCFG));
	
	if (g_struDeviceInfo[iDeviceIndex].pStruIPAlarmOutCfgV40 == NULL)
    {
        return FALSE;
    }
    memset(g_struDeviceInfo[iDeviceIndex].pStruIPAlarmOutCfgV40, 0, sizeof(NET_DVR_IPALARMOUTCFG_V40));


	if (bSupportMultiGroup)
	{
		g_struDeviceInfo[iDeviceIndex].bIPRet = NET_DVR_GetDVRConfig(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_GET_IP_ALARM_OUT, GroupNO, &g_struDeviceInfo[iDeviceIndex].struAlarmOutCfg, sizeof(NET_DVR_IPALARMOUTCFG), &dwReturned);
	} 
	else
	{
		g_struDeviceInfo[iDeviceIndex].bIPRet = NET_DVR_GetDVRConfig(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_GET_IPALARMOUTCFG_V40, 0, g_struDeviceInfo[iDeviceIndex].pStruIPAlarmOutCfgV40, sizeof(NET_DVR_IPALARMOUTCFG_V40), &dwReturned);
	}
	
	if (g_struDeviceInfo[iDeviceIndex].bIPRet)
	{	//8000 device
		for (i=0; i< MAX_IP_ALARMOUT_V40; i++)
		{
			if (g_struDeviceInfo[iDeviceIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i].dwIPID != 0)
			{
				sprintf(szTmp1, "%d[%d-%d]", i, g_struDeviceInfo[iDeviceIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i].dwIPID, \
                    g_struDeviceInfo[iDeviceIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i].dwAlarmOut);
				strcat(szTmp, szTmp1);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_IPALARMOUTCFG_V40-%s", szTmp);
	} 
	else
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_IPALARMOUTCFG_V40");
	}
	
	return g_struDeviceInfo[iDeviceIndex].bIPRet;
}

/*********************************************************
Function:	DoSetIPAccessCfg
Desc:		set the ip configure of device/设备ip接入参数
Input:	iDeviceIndex, the device index
		dwGroupNo  Group No. 
Output:	none
Return:	TRUE/FALSE
**********************************************************/
BOOL CClientDemoDlg::DoSetIPAccessCfg(int iDeviceIndex, DWORD dwGroupNo)
{
	BOOL bIPRet = FALSE;
	//2008-9-15 13:44 ip input configuration
	bIPRet = NET_DVR_SetDVRConfig(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_SET_IPPARACFG_V40, dwGroupNo, &g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[dwGroupNo], sizeof(g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0]));
	if (bIPRet)
	{		
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_IPPARACFG_V40");
		RefreshIPDevLocalCfg(iDeviceIndex);
	}
	else
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_IPPARACFG_V40");
	}
	
	return bIPRet;
}

/*********************************************************
Function:	RefreshIPDevLocalCfg
Desc:		refresh the ip device configure of local device configure
Input:	iDeviceIndex, the device index in the local device group
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::RefreshIPDevLocalCfg(int iDeviceIndex)
{
	EnterCriticalSection(&m_struLock);


	LPNET_DVR_IPPARACFG_V40 lpIPAccessCfgV40 = &g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[g_struDeviceInfo[iDeviceIndex].iGroupNO];
	DWORD dwChanShow = 0;
	int iIPChanIndex = 0;
	int i = 0;
	// 	for (i=0; i<MAX_IP_DEVICE; i++)
	// 	{
	// 		AddLog(-1, OPERATION_SUCC_T, "IP dev chan[%d] ip=%s name=%s", i,\
	// 		lpIPAccessCfg->struIPDevInfo[i].struIP.sIpV4, lpIPAccessCfg->struIPDevInfo[i].sUserName);
	// 	}

	//Update MAX IP channel number.
	g_struDeviceInfo[iDeviceIndex].iIPChanNum = lpIPAccessCfgV40->dwDChanNum;

	int iAnalogChanCount = 0;
	int iIPChanCount = 0;
	int iGroupNO   = g_struDeviceInfo[iDeviceIndex].iGroupNO;    //Group NO.
	int iGroupNum  = lpIPAccessCfgV40->dwGroupNum;
	int iIPChanNum = g_struDeviceInfo[iDeviceIndex].iIPChanNum;

    int iMaxGroupDeviceNum = 0;

    if (0 == iGroupNO)
    {
        iMaxGroupDeviceNum = MAX_CHANNUM_V30 + g_struDeviceInfo[iDeviceIndex].iAnalogChanNum;
    }
    else
    {
        iMaxGroupDeviceNum = MAX_CHANNUM_V30;
    }
	
    for (i = 0; i < iMaxGroupDeviceNum; i++)
    {

        //analog channel
        if (iAnalogChanCount < g_struDeviceInfo[iDeviceIndex].iAnalogChanNum && 0 == iGroupNO)
        {
            dwChanShow = iAnalogChanCount + g_struDeviceInfo[iDeviceIndex].iStartChan/* + g_struDeviceInfo[iDeviceIndex].iGroupNO*64*/;

            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iDeviceIndex = iDeviceIndex;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex = i;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanType = DEMO_CHANNEL_TYPE_ANALOG;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO = dwChanShow;
            
            sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName, ANALOG_C_FORMAT, dwChanShow);	
            //analog devices
            if (lpIPAccessCfgV40->byAnalogChanEnable[i])
            {
                g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable = TRUE;
                g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].dwImageType = CHAN_ORIGINAL;
                //g_struDeviceInfo[iDeviceIndex].iEnableChanNum ++;
            }
            else
            {
                g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable = FALSE;
                g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].dwImageType = CHAN_OFF_LINE;
            }
            
            iAnalogChanCount++;
        }
        //IP channel  //(i>=MAX_ANALOG_CHANNUM && i<MAX_ANALOG_CHANNUM+g_struDeviceInfo[iDeviceIndex].iIPChanNum) )
//         else if (iGroupNO >= 0 && ((iIPChanCount + iGroupNO * MAX_CHANNUM_V30)  <  iIPChanNum) && (iIPChanCount < iIPChanNum ))   
//         {
//             dwChanShow = iIPChanCount + iGroupNO * MAX_CHANNUM_V30 + lpIPAccessCfgV40->dwStartDChan - 1;
//             
//             g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwChanShow].iChanType  = DEMO_CHANNEL_TYPE_IP;
//             g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwChanShow].iChannelNO = dwChanShow + 1;
//             
//             iIPChanIndex = iIPChanCount;
//             g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwChanShow].iDeviceIndex = iDeviceIndex;
//             g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwChanShow].iChanIndex =i + g_struDeviceInfo[iDeviceIndex].iGroupNO*64;	
//             sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i + g_struDeviceInfo[iDeviceIndex].iGroupNO*64].chChanName, DIGITAL_C_FORMAT, iIPChanCount + iGroupNO * MAX_CHANNUM_V30 + 1);				
//             // 			AddLog(-1, OPERATION_SUCC_T, "IPc%d id%d chan[%d] ", iIPChanIndex,\
//             // 				lpIPAccessCfg->struIPChanInfo[iIPChanIndex].byIPID, lpIPAccessCfg->struIPChanInfo[iIPChanIndex].byChannel);
//             if (lpIPAccessCfgV40->struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byIPID != 0 && lpIPAccessCfgV40->struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byEnable == TRUE)
//             {
//                 g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwChanShow].bEnable = TRUE;//
//                 if (lpIPAccessCfgV40->struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byEnable)
//                 {
//                     g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwChanShow].dwImageType = CHAN_ORIGINAL;
//                 }
//                 else
//                 {
//                     g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwChanShow].dwImageType = CHAN_OFF_LINE;
//                 }
//                 
//                 //				g_struDeviceInfo[iDeviceIndex].iEnableChanNum ++;
//             }
//             else
//             {
//                 g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwChanShow].dwImageType = CHAN_OFF_LINE;
//                 g_struDeviceInfo[iDeviceIndex].pStruChanInfo[dwChanShow].bEnable = FALSE;	
//                 //g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = FALSE;
//             }
//             
//             iIPChanCount++;
//         }
        else if (iGroupNO >= 0 && ((iIPChanCount + iGroupNO * MAX_CHANNUM_V30)  <  iIPChanNum) && (iIPChanCount < iIPChanNum))   
        {
            dwChanShow = iIPChanCount + iGroupNO * MAX_CHANNUM_V30 + lpIPAccessCfgV40->dwStartDChan;
            
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanType = DEMO_CHANNEL_TYPE_IP;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO = dwChanShow;
            
            iIPChanIndex = iIPChanCount;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iDeviceIndex = iDeviceIndex;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex = i;
            sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName, DIGITAL_C_FORMAT, iIPChanCount + iGroupNO * MAX_CHANNUM_V30 + 1);
           
            if (g_struDeviceInfo[iDeviceIndex].byLoginModeRes == 1 || (lpIPAccessCfgV40->struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byIPID != 0 && lpIPAccessCfgV40->struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byEnable == TRUE))
            {
                g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable = TRUE;//ISAPI登录需要获取通道是否在线
                if (lpIPAccessCfgV40->struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byEnable)
                {
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].dwImageType = CHAN_ORIGINAL;
                }
                else
                {
                    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].dwImageType = CHAN_OFF_LINE;
                }
                
                //				g_struDeviceInfo[iDeviceIndex].iEnableChanNum ++;
            }
            else
            {
                g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].dwImageType = CHAN_OFF_LINE;
                g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable = FALSE;
                //g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = FALSE;
            }
            
            iIPChanCount++;
        }
        else
        {
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iDeviceIndex = -1;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex = -1;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanType = DEMO_CHANNEL_TYPE_INVALID;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChannelNO = -1;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable = FALSE;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = FALSE;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bLocalManualRec = FALSE;
            g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].lRealHandle = -1;
            sprintf(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName, "");
        }
    }
 
    for (i = 0; i < iMaxGroupDeviceNum; i++)
	{
        if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable)
		{
			g_struDeviceInfo[iDeviceIndex].lFirstEnableChanIndex = i;
			break;
		}
	}

    if (g_struDeviceInfo[iDeviceIndex].byZeroChanNum > 0)
    {
        //get配置
    }
	
	LeaveCriticalSection(&m_struLock);
}

/*********************************************************
Function:	RedrawDeviceNode
Desc:		redraw the device node on device tree, delete all channels node first, then add new channels
Input:	iDeviceIndex, the device index in the local device group
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::RedrawDeviceNode(int iDeviceIndex)
{
	HTREEITEM hChanItem = NULL;
	HTREEITEM hPreItem = NULL;
	CString csTmp;
	int i = 0;
	int iData = 0;
	int iLoginStat = DEVICE_LOGIN;
	if (iDeviceIndex >= 1000)//设备序号大于1000时表示只添加不登陆
	{
		iDeviceIndex-=1000;
		iLoginStat = DEVICE_LOGOUT;
	}
	else
	{
		iLoginStat = DEVICE_LOGIN;
	}
	if (g_bPlayAllDevice || g_struDeviceInfo[iDeviceIndex].bPlayDevice)
	{
		return;
	}
	
	
	
	HTREEITEM hRoot = m_treeDeviceList.GetRootItem();
	if (hRoot == NULL)
	{
		return;
	}
	
	HTREEITEM hDevItem = m_treeDeviceList.GetChildItem(hRoot);
	
	//find the select device
	while (hDevItem != NULL)
	{
		iData = m_treeDeviceList.GetItemData(hDevItem);
		if (DEVICETYPE == iData/1000)
		{
			if (iDeviceIndex ==  iData%1000)
			{
				HTREEITEM hChanItem = m_treeDeviceList.GetChildItem(hDevItem);
				
                while (i < MAX_CHANNUM_V30 * 2 + g_struDeviceInfo[iDeviceIndex].byZeroChanNum && hChanItem != NULL)
				{
					hPreItem = hChanItem;
					hChanItem = m_treeDeviceList.GetNextSiblingItem(hChanItem);
					if (CHANNELTYPE != (int)m_treeDeviceList.GetItemData(hPreItem)/1000)
					{
						AddLog(iDeviceIndex, OPERATION_FAIL_T, "to next channel node error");
						break;
					}
					i++;
				}
				break;
			}
		}//end else if
		
		hDevItem = m_treeDeviceList.GetNextVisibleItem(hDevItem);
	}//end while

	if (hDevItem != NULL)
	{
		while(i>0 && hPreItem != NULL)
		{
			hChanItem = hPreItem;
			hPreItem = m_treeDeviceList.GetPrevSiblingItem(hChanItem);
			if (hPreItem == NULL)
			{
				
				//				AddLog(iDeviceIndex, OPERATION_SUCC_T, "del last chan[%d]", m_treeDeviceList.GetItemData(hChanItem)%1000);
				hPreItem = m_treeDeviceList.GetParentItem(hChanItem);
				m_treeDeviceList.DeleteItem(hChanItem);
				
				if (hPreItem == NULL)
				{
					AddLog(-1, OPERATION_FAIL_T, "get the device node err");
					break;
				}	
				if (CHANNELTYPE != (int)m_treeDeviceList.GetItemData(hPreItem)/1000)
				{
					//		AddLog(iDeviceIndex, OPERATION_SUCC_T, "dev[%d] node all delete", m_treeDeviceList.GetItemData(hPreItem)%1000);
					break;
				}				
			}
			//AddLog(iDeviceIndex, OPERATION_SUCC_T, "del chan[%d]", m_treeDeviceList.GetItemData(hChanItem)%1000);
			m_treeDeviceList.DeleteItem(hChanItem);
			
			i--;
		}
	}
	
	if (hDevItem == NULL)
	{//added 9000 devices
		hDevItem = m_treeDeviceList.InsertItem(g_struDeviceInfo[iDeviceIndex].chLocalNodeName, iLoginStat, iLoginStat, hRoot, GetAfterItem(hRoot));	
	}
	
	//add channel node//g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bEnable || 
    for (i = 0; i< MAX_CHANNUM_V30 * 2; i++)
	{
		if (g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex != -1 )
		{
			csTmp.Format("%s", g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].chChanName);
			hChanItem =  m_treeDeviceList.InsertItem(csTmp, g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].dwImageType, \
				g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].dwImageType, hDevItem);
			m_treeDeviceList.SetItemData(hChanItem, CHANNELTYPE * 1000 + g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].iChanIndex);
		}
	}
    for (i=0; i< g_struDeviceInfo[iDeviceIndex].byZeroChanNum; i++)
    {
        if (g_struDeviceInfo[iDeviceIndex].struZeroChan[i].iChanIndex != -1 )
        {
            csTmp.Format("%s", g_struDeviceInfo[iDeviceIndex].struZeroChan[i].chChanName);
            hChanItem =  m_treeDeviceList.InsertItem(csTmp, g_struDeviceInfo[iDeviceIndex].struZeroChan[i].dwImageType, \
                g_struDeviceInfo[iDeviceIndex].struZeroChan[i].dwImageType, hDevItem);
            m_treeDeviceList.SetItemData(hChanItem, CHANNELTYPE * 1000 + g_struDeviceInfo[iDeviceIndex].struZeroChan[i].iChanIndex);
        }
    }
	for (i=0; i< g_struDeviceInfo[iDeviceIndex].byMirrorChanNum && i < 16; i++)
    {
        if (g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].iChanIndex != -1 )
        {
            csTmp.Format("%s", g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].chChanName);
            hChanItem =  m_treeDeviceList.InsertItem(csTmp, g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].dwImageType, \
                g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].dwImageType, hDevItem);
            m_treeDeviceList.SetItemData(hChanItem, CHANNELTYPE * 1000 + g_struDeviceInfo[iDeviceIndex].struMirrorChan[i].iChanIndex);
        }
    }
    
}

/*********************************************************
Function:	DoTestElseFunction
Desc:		test 
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::DoTestElseFunction()
{
	int iDevIndex = GetCurDeviceIndex();
	CDlgDoTest dlg;
	dlg.m_iDeviceIndex = iDevIndex;
	dlg.DoModal();
}

/*********************************************************
Function:	OnDbclkListAllLog
Desc:		get current device fault info
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnDblclkListAllLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int iItemSel = 0;
	CString csTxt;
	
	POSITION  iPos = m_listAllLog.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	iItemSel = m_listAllLog.GetNextSelectedItem(iPos);//%s\t%s\tm_listAllLog.GetItemText(iItemSel,1),\m_listAllLog.GetItemText(iItemSel,2)
	csTxt.Format("%s",m_listAllLog.GetItemText(iItemSel,5));
	if (csTxt.GetLength() > 3)
	{
		AfxMessageBox(csTxt);	
	}
	
	*pResult = 0;
}

/*********************************************************
Function:	OnDblclkListAlarmInfo
Desc:		get current Alarm Info
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnDblclkListAlarmInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int iItemSel = 0;
    CString csTxt;
    
    POSITION  iPos = m_listAlarmInfo.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    iItemSel = m_listAlarmInfo.GetNextSelectedItem(iPos);
    csTxt.Format("%s",m_listAlarmInfo.GetItemText(iItemSel,2));
    if (csTxt.GetLength() > 3)
    {
        AfxMessageBox(csTxt);	
    }
    
    *pResult = 0;
}

/*********************************************************
Function:	OnSelchangeComboListType
Desc:		select the corresponding list, alarm or log
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnSelchangeComboListType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ListRestore();
	
	if (m_iMainType == CONFIG_ALL_T)
	{
		m_dlgConfigAll->ConfigWndUpdate();			
	}
	else if (m_iMainType == PLAY_BACK_T)
	{
		m_dlgPlayBack->ShowWindow(SW_SHOW);
		m_dlgPlayBack->PlayBackWinUpdate();
	}
	else if (m_iMainType == PREVIEW_T)
	{
		PreviewReferShow(TRUE);
	}
	switch (m_iSelListType)
	{
	case 0:
		m_listAlarmInfo.ShowWindow(SW_HIDE);
		m_listAllLog.ShowWindow(SW_SHOW);	
		break;
	case 1:		
		m_listAllLog.ShowWindow(SW_HIDE);
		m_listAlarmInfo.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}

/*********************************************************
Function:	OnColumnclickListAllLog
Desc:		response the Column-click of all log list  
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnColumnclickListAllLog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	EnlargeList(m_listAllLog, m_bListLogEnlarge);
	*pResult = 0;
}

/*********************************************************
Function:	OnColumnclickListAlarmInfo
Desc:		response the Column-click of all log list
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnColumnclickListAlarmInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	EnlargeList(m_listAlarmInfo, m_bListAlarmEnlarge);
	*pResult = 0;	
}

/*********************************************************
Function:	EnlargeList
Desc:		enlarge list when click the column
Input:	list, log or alarm information tree; bEnargeList, TRUE/FALSE;
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::EnlargeList(CListCtrl &list, BOOL &bEnargeList)
{
	CRect rc(0,0,0,0);
	list.GetWindowRect(&rc);
	ScreenToClient(&rc);
	
	if (!bEnargeList)
	{
		rc.top-=LIST_ENLARGE_HIGH;//move top upper, stretch
		list.MoveWindow(&rc);
		bEnargeList = TRUE;
		if (m_iMainType == CONFIG_ALL_T)
		{
			m_dlgRemoteCfg->ShowWindow(SW_HIDE);
			// m_dlgRemoteCfg->ChangeCurConfigWnd(REMOTE_MAT_DEC_CFG_T+1);     
            m_dlgRemoteCfg->ChangeCurConfigWnd(REMOTE_DEVICE_CFG_T);
			m_dlgLocalCfg->ShowWindow(SW_HIDE);
			m_dlgIPAccess->ShowWindow(SW_HIDE);	
			m_dlgHDConfig->ShowWindow(SW_HIDE);
			m_dlgBatchCfg->ShowWindow(SW_HIDE);
		}
		else if (m_iMainType == PLAY_BACK_T)
		{
			m_dlgPlayBack->ShowWindow(SW_HIDE);
			// 			m_dlgPlayBack->m_dlgPlayRemoteFile.ShowWindow(SW_HIDE);
			// 			m_dlgPlayBack->m_dlgPlayLocalFile.ShowWindow(SW_HIDE);
			// 			m_dlgPlayBack->m_dlgPlayRemoteTime.ShowWindow(SW_HIDE);			
		}
		else if(m_iMainType == STREAM_ID_T)
		{
		//	m_pStreamIDDlg->ShowWindow(SW_HIDE);
		}
		else if (m_iMainType == PRODUCT_RELATE_T)
		{
			m_dlgProductCfg->ShowWindow(SW_HIDE);
		}
		else
		{
			PreviewReferShow(FALSE);
			m_dlgOutputCtrl->ShowWindow(SW_SHOW);
		}
		
	}
	else
	{
		rc.top+=LIST_ENLARGE_HIGH;//move top down, compress
		list.MoveWindow(&rc);
		bEnargeList = FALSE;
		if (m_iMainType == CONFIG_ALL_T)
		{
			m_dlgConfigAll->ConfigWndUpdate();			
		}
		else if (m_iMainType == PLAY_BACK_T)
		{
			m_dlgPlayBack->ShowWindow(SW_SHOW);
			//			m_dlgPlayBack->PlayBackWinUpdate();
		}
		else if (m_iMainType == STREAM_ID_T)
		{
			//m_pStreamIDDlg->ShowWindow(SW_SHOW);
		}
		else if (m_iMainType ==  PRODUCT_RELATE_T)
		{
			m_dlgProductCfg->ShowWindow(SW_SHOW);
		}
		else
		{
			PreviewReferShow(TRUE);
		}
		
	}
	if (!g_struLocalParam.bFullScreen)
	{
		list.ShowWindow(SW_SHOW);
	}
	
}
void CClientDemoDlg::ProcAlarmHostAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    char szLan[128] ={0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iWinIndex = -1;
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_ALARMHOST_ALARMINFO  struAlarmInfo;
    memset(&struAlarmInfo, 0, sizeof(struAlarmInfo));
    CTime time = CTime::GetCurrentTime();
    memcpy(&struAlarmInfo, pAlarmInfo, sizeof(struAlarmInfo));
    
    g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
    ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));	
    
    g_StringLanType(szLan, "收到网络报警主机报警", "receive alarmhost alarm");
    memcpy(szInfoBuf, szLan, strlen(szLan));
    for (i = 0; i < ARRAY_SIZE(struAlarmInfo.byAlarmInputNumber); i++)
    {
        sprintf(&szInfoBuf[i + strlen(szLan)], "%d", struAlarmInfo.byAlarmInputNumber[i]);                
    }

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

}
/*********************************************************
Function:	OnBtnTest
Desc:		for testing the interfaces those are not used usually
Input:	none
Output:	none
Return:	none
**********************************************************/
void CClientDemoDlg::OnBtnTest() 
{
	// TODO: Add your control notification handler code here
	DoTestElseFunction();
	NET_DVR_SDKSTATE SDKState;
	NET_DVR_GetSDKState( &SDKState );
	g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "SDKState.dwTotalRealPlayNum %d", SDKState.dwTotalRealPlayNum);
	return;
}

void CClientDemoDlg::ListRestore()
{
	CRect rc(0,0,0,0);
	if (m_bListLogEnlarge)
	{
		m_listAllLog.GetWindowRect(&rc);
		ScreenToClient(&rc);
		rc.top+=LIST_ENLARGE_HIGH;//move top down, compress
		m_listAllLog.MoveWindow(&rc);
		m_bListLogEnlarge = FALSE;
	}
	
	if (m_bListAlarmEnlarge)
	{
		m_listAlarmInfo.GetWindowRect(&rc);
		ScreenToClient(&rc);
		rc.top+=LIST_ENLARGE_HIGH;//move top down, compress
		m_listAlarmInfo.MoveWindow(&rc);
		m_bListAlarmEnlarge = FALSE;
	}
}

void CClientDemoDlg::OnRadioLocalLog() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iSelListType = 0;
	OnSelchangeComboListType();
	UpdateData(FALSE);
}

void CClientDemoDlg::OnRadioAlarmInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iSelListType = 1;
	OnSelchangeComboListType();
	UpdateData(FALSE);	
}

void CClientDemoDlg::OnMenuAtmFrameFormat() 
{
	// TODO: Add your command handler code here
    int iDeviceIndex = GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    
    int iChanIndex = GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    
    CDlgAtmFrameFormatV30 dlg;
    dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.m_iChannelNum = g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;
    dlg.DoModal();
}

void CClientDemoDlg::OnMenuSensorAddPreview() 
{
   int iDeviceIndex = GetCurDeviceIndex();
   if (iDeviceIndex < 0)
   {
       return;
   }
   CDlgSensorAddPreview dlg;
   dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
   dlg.m_iDevIndex = iDeviceIndex;
   dlg.DoModal();
}

void CClientDemoDlg::OnMenuHolidayCfg() 
{
   
    int iDeviceIndex = GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }

    CDlgHolidayCfg dlg;
    dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.DoModal();


    DWORD dwGetCommand = NET_DVR_GET_ALARMOUT_HOLIDAY_HANDLE;
    DWORD dwSetCommand = NET_DVR_SET_ALARMOUT_HOLIDAY_HANDLE;
    NET_DVR_HOLIDAY_HANDLE struHolidayHandle = {0};
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(g_struDeviceInfo[iDeviceIndex].lLoginID, dwGetCommand, 1, &struHolidayHandle, sizeof(struHolidayHandle), &dwReturn))
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get Holiday handle");
    }
    else
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Get Holiday handle");
    }
    
    memset(&struHolidayHandle, 0, sizeof(struHolidayHandle));
    if (NET_DVR_SetDVRConfig(g_struDeviceInfo[iDeviceIndex].lLoginID, dwSetCommand, 1, &struHolidayHandle, sizeof(struHolidayHandle)))
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Set Holiday handle");
    }
    else
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Set Holiday handle");
    }
}

void CClientDemoDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_Cleanup();
	NET_DVR_Init();
	NET_DVR_SDKSTATE SDKState;
	NET_DVR_GetSDKState(&SDKState);
}

void CClientDemoDlg::ProcAlarmVQD(WPARAM wParam, LPARAM lParam)
{
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_VQD_DIAGNOSE_INFO struVQDAlarm = {0};
    memcpy(&struVQDAlarm, pAlarmInfo, sizeof(struVQDAlarm));
	
	char szLan[1024] = {0};
	char szLanCn[1024] = {0};
	char szLanEn[1024] = {0};
	if (struVQDAlarm.struVQDDiagnoseExceptionInfo.dwChannelNO <= g_struDeviceInfo[iDeviceIndex].iAnalogChanNum)
	{
		sprintf(szLanCn,"Camera%d",struVQDAlarm.struVQDDiagnoseExceptionInfo.dwChannelNO);
		sprintf(szLanEn,"Camera%d",struVQDAlarm.struVQDDiagnoseExceptionInfo.dwChannelNO);
	}
	else
	{
		sprintf(szLanCn,"IPCamera%02d",struVQDAlarm.struVQDDiagnoseExceptionInfo.dwChannelNO);
		sprintf(szLanEn,"IPCamera%02d",struVQDAlarm.struVQDDiagnoseExceptionInfo.dwChannelNO);
	}
	
	switch (struVQDAlarm.struVQDDiagnoseExceptionInfo.dwVQDType)
	{
	case VQD_BLUR_FLAG:
		sprintf(szLanCn,"%s 图像模糊",szLanCn);
		sprintf(szLanEn,"%s Blur",szLanEn);
		
		break;
	case VQD_LUMA_FLAG:
		sprintf(szLanCn,"%s 亮度异常",szLanCn);
		sprintf(szLanEn,"%s Luma",szLanEn);
		break;
	case VQD_CHROMA_FLAG:
		sprintf(szLanCn,"%s 图像偏色",szLanCn);
		sprintf(szLanEn,"%s Chroma",szLanEn);
		break;
	case VQD_SNOW_FLAG:
		sprintf(szLanCn,"%s 雪花干扰",szLanCn);
		sprintf(szLanEn,"%s Snow",szLanEn);
		break;
	case VQD_STREAK_FLAG:
		sprintf(szLanCn,"%s 条纹干扰",szLanCn);
		sprintf(szLanEn,"%s Streak",szLanEn);
		break;
	case VQD_FREEZE_FLAG:
		sprintf(szLanCn,"%s 画面冻结",szLanCn);
		sprintf(szLanEn,"%s Freeze",szLanEn);
		break;
	case VQD_SIGLOSE_FLAG:
		sprintf(szLanCn,"%s 信号丢失",szLanCn);
		sprintf(szLanEn,"%s Signal Lose",szLanEn);
		break;
	case VQD_PTZ_FLAG:
		sprintf(szLanCn,"%s 云台失控",szLanCn);
		sprintf(szLanEn,"%s PTZ",szLanEn);
		break;	
	default:
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "Unknown Alarm");
		return;
	}
	
	sprintf(szLanCn,"%s %4d-%2d-%2d %2d:%2d:%2d",szLanCn, struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwYear,\
		struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwMonth, struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwDay,\
		struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwHour, struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwMinute,\
		struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwSecond);
	
	sprintf(szLanEn,"%s %4d-%2d-%2d %2d:%2d:%2d",szLanEn, struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwYear,\
		struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwMonth, struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwDay,\
		struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwHour, struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwMinute,\
		struVQDAlarm.struVQDDiagnoseExceptionInfo.struDiagnoseTime.dwSecond);
	
	g_StringLanType(szLan,szLanCn,szLanEn);
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
}

void CClientDemoDlg::ProcAlarmVQDEx(WPARAM wParam,LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iWinIndex = -1;         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_VQD_ALARM  struVQDAlarm = {0};
	CTime time = CTime::GetCurrentTime();
	memcpy(&struVQDAlarm, pAlarmInfo, sizeof(struVQDAlarm));
	i = struVQDAlarm .struDevInfo.byIvmsChannel-g_struDeviceInfo[iDeviceIndex].iStartChan;
	g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i].bAlarm = TRUE;
	::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));
	
    NET_DVR_TIME struAbsTime = {0};     
    struAbsTime.dwYear   = GET_YEAR(struVQDAlarm.dwAbsTime);
    struAbsTime.dwMonth  = GET_MONTH(struVQDAlarm.dwAbsTime);
    struAbsTime.dwDay    = GET_DAY(struVQDAlarm.dwAbsTime);
    struAbsTime.dwHour   = GET_HOUR(struVQDAlarm.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struVQDAlarm.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struVQDAlarm.dwAbsTime);
	
    CString str = "";
    sprintf(szInfoBuf, "VQD extended Alarm Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]Dev IP[%s] Port[%d] Chan[%d]  \
        EventType[%d],Threshold[%.3f]", 
        struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay,
        struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond, struVQDAlarm.struDevInfo.struDevIP.sIpV4,
        struVQDAlarm.struDevInfo.wPort, struVQDAlarm.struDevInfo.byChannel,struVQDAlarm.dwEventType,struVQDAlarm.fThreshold);
	
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
    if (struVQDAlarm.dwPicDataLen > 0 && struVQDAlarm.pImage != NULL)
	{
		int num = ulAlarmPic/1000+1;
		ulAlarmPic++;
		
		char cFilename[256] = {0};
		HANDLE hFile;
		DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
		
		sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
        
		sprintf(cFilename, "%s\\LocalTime[%s].jpg",cFilename, chTime);
		hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		WriteFile(hFile, struVQDAlarm.pImage, struVQDAlarm.dwPicDataLen, &dwReturn, NULL);
		CloseHandle(hFile);
		hFile = NULL;
	}
	if (struVQDAlarm.pImage != NULL)
	{
		delete [] (struVQDAlarm.pImage);
        struVQDAlarm.pImage = NULL;
	}		
}

// void CClientDemoDlg::OnMenuTs()
// {
// 	int iDeviceIndex = GetCurDeviceIndex();
//     if (iDeviceIndex < 0)
//     {
//         return;
//     }
// 	
//     int iChanIndex = GetCurChanIndex();
//     if (iChanIndex < 0)
//     {
//         iChanIndex = 0;//default to config channel one
//     }
// 	
// 	STRU_CHANNEL_INFO *pChannelInfo = &(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex]);
// 	int iChanShow = pChannelInfo->iChannelNO;
// 	
// 	CDlgTsSeries dlg;
// 	dlg.m_lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;	
// 	dlg.m_iDeviceIndex = iDeviceIndex;			
// 	dlg.m_lChannel = iChanShow;
// 	dlg.DoModal();
// }

// void CClientDemoDlg::OnMenuIPIntell()
// {
// 	// TODO: Add your command handler code here
// 	int iDeviceIndex = GetCurDeviceIndex();
//     if (iDeviceIndex < 0)
//     {
//         return;
//     }
//     
//     
//     int iChanIndex = GetCurChanIndex();
//     if (iChanIndex < 0)
//     {
//         iChanIndex = 0;//default to config channel one
//     }
// 
// 	CDlgIPCSimpIntellCfg dlg;
// 	dlg.m_lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;	
// 	dlg.m_iDeviceIndex = iDeviceIndex;			
// 	dlg.m_lChannel = iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
// 	dlg.m_iChanCount = g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;
// 	dlg.m_iAnaChanCount = g_struDeviceInfo[iDeviceIndex].iAnalogChanNum;
// 	dlg.m_iDStartChannel = g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan;
// 
// 	dlg.DoModal();
// }

// void CClientDemoDlg::OnMenuIpcSpecialex() 
// {
// 	//2013-06-17
// 	int iDeviceIndex = GetCurDeviceIndex();
//     if (iDeviceIndex < 0)
//     {
//         return;
//     }
//     
//     
//     int iChanIndex = GetCurChanIndex();
//     if (iChanIndex < 0)
//     {
//         iChanIndex = 0;
//     }
// 	
// 	CDlgIPCSpeclalEx dlg;
// 	dlg.m_lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;	
// 	dlg.m_iDeviceIndex = iDeviceIndex;			
// 	dlg.m_lChannel = iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
// 	dlg.m_iChanCount = g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;
// 	dlg.m_iAnaChanCount = g_struDeviceInfo[iDeviceIndex].iAnalogChanNum;
// 	dlg.m_iDStartChannel = g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan;
// 	
// 	dlg.DoModal();
// }

void CClientDemoDlg::OnMENUT1Test() 
{
	// TODO: Add your command handler code here
	CDlgT1test dlg;
	int iDevIndex = GetCurDeviceIndex();
	if (iDevIndex < 0)
	{
		return;
	}
	dlg.m_iDeviceIndex = iDevIndex;
	dlg.DoModal();
}
// void CClientDemoDlg::OnMenuGBT28181Protocol()
// {
// 	int iDeviceIndex = GetCurDeviceIndex();
// 	if (iDeviceIndex < 0)
// 	{
// 		return;
// 	}
// 	CDlgGBT28181ProtocolAccess dlg;
// 	dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
// 	dlg.m_dwAlarmOutNum = g_struDeviceInfo[iDeviceIndex].iAlarmOutNum;
// 	dlg.m_dwDevIndex = iDeviceIndex;
// 	dlg.m_nChannel = g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;
// 	dlg.m_lStartChan = g_struDeviceInfo[iDeviceIndex].iStartChan;
// 	dlg.m_dwAlarmInNum = g_struDeviceInfo[iDeviceIndex].iAlarmInNum;
// 	dlg.DoModal();
// }

// void CClientDemoDlg::OnMenuDevServer()
// {
// 	int iDeviceIndex = GetCurDeviceIndex();
// 	if (iDeviceIndex < 0)
// 	{
// 		return;
// 	}
// 	CDlgDevServer dlg;
// 	dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
// 	dlg.m_dwAlarmOutNum = g_struDeviceInfo[iDeviceIndex].iAlarmOutNum;
// 	dlg.m_dwDevIndex = iDeviceIndex;
// 	dlg.m_nChannel = g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;
// 	dlg.m_lStartChan = g_struDeviceInfo[iDeviceIndex].iStartChan;
// 	dlg.m_dwAlarmInNum = g_struDeviceInfo[iDeviceIndex].iAlarmInNum;
// 	dlg.DoModal();
// }

void CClientDemoDlg::OnMenuProductionLineTest() 
{
	// TODO: Add your command handler code here
    int iDeviceIndex = GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }  
    int iChanIndex = GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;
    }
    CDlgProductionTest dlg; 
    dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.m_dwChannel = iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.DoModal();
}



void CClientDemoDlg::OnMenuVca() 
{
	// TODO: Add your command handler code here
	DlgVCADetionCfg dlg;
	dlg.DoModal();
}


// void CClientDemoDlg::OnMenuItsIoinCfg() 
// {
// 	// TODO: Add your command handler code here
// 	int iDeviceIndex = GetCurDeviceIndex();
//     if (iDeviceIndex < 0)
//     {
//         return;
//     }  
//     int iChanIndex = GetCurChanIndex();
//     if (iChanIndex < 0)
//     {
//         iChanIndex = 0;
//     }
//     CDlgITSIOinCfg dlg; 
//     dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
//     dlg.m_dwChannel = iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
//     dlg.m_iDevIndex = iDeviceIndex;
//     dlg.DoModal();
// }


void CClientDemoDlg::OnBtntProductCfg()
{   
	CRect rectConfig(0,0,0,0);	
	
	rectConfig.top    = m_iFunBtnHeight-2;
	rectConfig.left   = m_iTreeWidth-2;//-2 cover preview box
	rectConfig.right  = DEMO_FULL_WIDTH - m_iRightWidth ;
	rectConfig.bottom = DEMO_FULL_HEIGHT - m_iListLogHeight;//+4
	
	if (m_iMainType != PRODUCT_RELATE_T)
	{
		m_iMainType = PRODUCT_RELATE_T;
		PreviewReferShow(FALSE);
		ConfigAllHide();

	//	m_dlgPlayBack->HideAll();
		//InitConfigAllRefer();
	//	m_dlgProductCfg->MoveWindow(rectConfig);
	//	m_dlgProductCfg->ShowWindow(SW_SHOW);
		InitProdouctCfgRefer();
		m_dlgProductCfg->UpdateWindowParam(GetCurDeviceIndex(),GetCurChanIndex());
	}
	/*
	int iDeviceIndex = GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }  

	if (g_struDeviceInfo[iDeviceIndex].lLoginID < 0)
	{
		AddLog(-1, OPERATION_SUCC_T, "device is offline!");
		return;
	}

	LONG lChannel = -1;
    int iChanIndex = GetCurChanIndex();
    if (iChanIndex >= 0)
    {
        lChannel = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
    }

	CDlgProductCfg dlg;
	dlg.m_lUserID   = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.m_lChannel  = lChannel;
    dlg.m_iDevIndex = iDeviceIndex;
	dlg.DoModal();
	*/
}

void CClientDemoDlg::InitProdouctCfgRefer()
{
	if (!m_dlgProductCfg->IsWindowVisible())
	{
		CRect rectProductCfg(0,0,0,0);	
		
		rectProductCfg.top    = m_iFunBtnHeight-2;
		rectProductCfg.left   = m_iTreeWidth-2;//-2 cover preview box
		rectProductCfg.right  = DEMO_FULL_WIDTH;
		rectProductCfg.bottom = DEMO_FULL_HEIGHT - m_iListLogHeight;//+4
		
		m_dlgProductCfg->MoveWindow(&rectProductCfg,TRUE);
		m_dlgProductCfg->ShowWindow(SW_SHOW);
	}
}


//车辆二次识别数据上传
void CClientDemoDlg::ProVehicleRecogResult( WPARAM wParam, LPARAM lParam )
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);	
	int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	char szLan[128] = {0};
	g_StringLanType(szLan, "车辆二次识别数据上传","Upload a secondary vehicle identification data");
	NET_DVR_VEHICLE_RECOG_RESULT  struVehicleRecogResult;
    memset(&struVehicleRecogResult, 0, sizeof(struVehicleRecogResult));
	memcpy(&struVehicleRecogResult, pAlarmInfo, sizeof(struVehicleRecogResult));

    sprintf(szInfoBuf, "%s:PostID[%d] PostTime{wYear[%d] byMonth[%d] byDay[%d] byHour[%d] byMinute[%d] bySecond[%d] wMilliSec[%d]}DataIndex[%s] TaskNo[%d]   PlateRect{fX[%f] fY[%f] fWidth[%f] fHeight[%f]} sLicense[%s] VehicleType[%d] ColorDepth[%d] CarColor[%d] \
            VehicleLogoRecog[%d] VehicleSubLogoRecog[%d] PilotSafebelt[%d] CopilotSafebelt[%d] PilotSunVisor[%d] CopilotSunVisor[%d] DataType[%d] PicType[%d] \
            VehicleModel[%d] VehicleLogoRecogEx[%d] VehicleRect{fX[%f] fY[%f] fWidth[%f] fHeight[%f]} PilotRect{fX[%f] fY[%f] fWidth[%f] fHeight[%f]} CopilotRect{fX[%f] fY[%f] fWidth[%f] fHeight[%f]}", \
            szLan, struVehicleRecogResult.dwPostID, struVehicleRecogResult.struPostTime.wYear, struVehicleRecogResult.struPostTime.byMonth, struVehicleRecogResult.struPostTime.byDay, \
            struVehicleRecogResult.struPostTime.byHour, struVehicleRecogResult.struPostTime.byMinute, struVehicleRecogResult.struPostTime.bySecond, struVehicleRecogResult.struPostTime.wMilliSec, \
            struVehicleRecogResult.sDataIndex, struVehicleRecogResult.wTaskNo, struVehicleRecogResult.struPlateRect.fX, struVehicleRecogResult.struPlateRect.fY, \
            struVehicleRecogResult.struPlateRect.fWidth, struVehicleRecogResult.struPlateRect.fHeight, struVehicleRecogResult.sLicense, struVehicleRecogResult.byVehicleType, \
            struVehicleRecogResult.byColorDepth, struVehicleRecogResult.byColor, struVehicleRecogResult.byVehicleLogoRecog, struVehicleRecogResult.byVehicleSubLogoRecog, \
            struVehicleRecogResult.byPilotSafebelt, struVehicleRecogResult.byCopilotSafebelt, struVehicleRecogResult.byPilotSunVisor, struVehicleRecogResult.byCopilotSunVisor, \
            struVehicleRecogResult.byDataType, struVehicleRecogResult.dwPicType, struVehicleRecogResult.byVehicleLogoRecog, struVehicleRecogResult.wVehicleLogoRecog, \
            struVehicleRecogResult.struVehicleRect.fX, struVehicleRecogResult.struVehicleRect.fY, struVehicleRecogResult.struVehicleRect.fWidth, struVehicleRecogResult.struVehicleRect.fHeight, \
            struVehicleRecogResult.struPilotRect.fX, struVehicleRecogResult.struPilotRect.fY, struVehicleRecogResult.struPilotRect.fWidth, struVehicleRecogResult.struPilotRect.fHeight, \
            struVehicleRecogResult.struCopilotRect.fX, struVehicleRecogResult.struCopilotRect.fY, struVehicleRecogResult.struCopilotRect.fWidth, struVehicleRecogResult.struCopilotRect.fHeight);
     AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

	
	SYSTEMTIME t;
	GetLocalTime(&t);
	char chTime[128];
	sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);

	


	if (struVehicleRecogResult.dwVehicleBufferLen > 0 && struVehicleRecogResult.pVehicleBuffer != NULL)
	{
		char cFilename[256] = {0};
		DWORD dwWrittenBytes = 0;
        if (iDeviceIndex != -1 && iDeviceIndex < 512)
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[Vehicle]");
        }
        else
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, "[Vehicle]");
        }

		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
		
		sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());

		HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		DWORD dwRet = WriteFile(hFile, struVehicleRecogResult.pVehicleBuffer, struVehicleRecogResult.dwVehicleBufferLen, &dwWrittenBytes, NULL);
		if (dwRet == 0 || dwWrittenBytes < struVehicleRecogResult.dwVehicleBufferLen )
		{
			DWORD dwError = GetLastError();
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Vehicle Picture Wtite to File Fail.System Error:%d, dwVehicleBufferLen:%d, dwWrittenBytes:%d ", dwError, struVehicleRecogResult.dwVehicleBufferLen, dwWrittenBytes);
		}
		CloseHandle(hFile);
		hFile = NULL;

	}
	if (struVehicleRecogResult.dwPlateBufferLen> 0 && struVehicleRecogResult.pPlateBuffer != NULL)
	{
		char cFilename[256] = {0};
		DWORD dwWrittenBytes = 0;
        if (iDeviceIndex != -1 && iDeviceIndex < 512)
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[Plate]");
        }
        else
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, "[Plate]");
        }

		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
		
		sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
		
		HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		DWORD dwRet = WriteFile(hFile, struVehicleRecogResult.pPlateBuffer, struVehicleRecogResult.dwPlateBufferLen, &dwWrittenBytes, NULL);
		if (dwRet == 0 || dwWrittenBytes < struVehicleRecogResult.dwPlateBufferLen )
		{
			DWORD dwError = GetLastError();
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Plate Picture Wtite to File Fail.System Error:%d, dwPlateBufferLen:%d, dwWrittenBytes:%d ", dwError, struVehicleRecogResult.dwPlateBufferLen, dwWrittenBytes);
		}
		CloseHandle(hFile);
		hFile = NULL;
	}
	if (struVehicleRecogResult.dwPilotFaceBufferLen > 0 && struVehicleRecogResult.pPilotFaceBuffer != NULL)
	{
		char cFilename[256] = {0};
		DWORD dwWrittenBytes = 0;
        if (iDeviceIndex != -1 && iDeviceIndex < 512)
        {
            sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[PilotFace]");
        }
        else
        {
            sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, "[PilotFace]");
        }
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
		
		sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
		
		HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		DWORD dwRet = WriteFile(hFile, struVehicleRecogResult.pPilotFaceBuffer, struVehicleRecogResult.dwPilotFaceBufferLen , &dwWrittenBytes, NULL);
		if (dwRet == 0 || dwWrittenBytes < struVehicleRecogResult.dwPilotFaceBufferLen )
		{
			DWORD dwError = GetLastError();
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "PilotFace Picture Wtite to File Fail.System Error:%d, dwPilotFaceBufferLen:%d, dwWrittenBytes:%d ", dwError, struVehicleRecogResult.dwPilotFaceBufferLen, dwWrittenBytes);
		}
		CloseHandle(hFile);
		hFile = NULL;
	}
	if (struVehicleRecogResult.dwCopilotFaceBufferLen > 0 && struVehicleRecogResult.pCopilotFaceBuffer != NULL)
	{
		char cFilename[256] = {0};
		DWORD dwWrittenBytes = 0;
        if (iDeviceIndex != -1 && iDeviceIndex < 512)
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[CopilotFace]");
        }
        else
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, "[CopilotFace]");
        }

		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
		
		sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
		
		HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		DWORD dwRet = WriteFile(hFile, struVehicleRecogResult.pCopilotFaceBuffer, struVehicleRecogResult.dwCopilotFaceBufferLen , &dwWrittenBytes, NULL);
		if (dwRet == 0 || dwWrittenBytes < struVehicleRecogResult.dwCopilotFaceBufferLen )
		{
			DWORD dwError = GetLastError();
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "CopilotFace Picture Wtite to File Fail.System Error:%d, dwCopilotFaceBufferLen:%d, dwWrittenBytes:%d ", dwError, struVehicleRecogResult.dwCopilotFaceBufferLen, dwWrittenBytes);

		}
		CloseHandle(hFile);
		hFile = NULL;
	}
	if (struVehicleRecogResult.dwPilotSafebeltBufferLen > 0 && struVehicleRecogResult.pPilotSafebeltBuffer != NULL)
	{
		char cFilename[256] = {0};
		DWORD dwWrittenBytes = 0;

        if (iDeviceIndex != -1 && iDeviceIndex < 512)
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[PilotSafe]");
        }
        else
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, "[PilotSafe]");
        }
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
		
		sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
		
		HANDLE  hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		DWORD dwRet = WriteFile(hFile, struVehicleRecogResult.pPilotSafebeltBuffer, struVehicleRecogResult.dwPilotSafebeltBufferLen , &dwWrittenBytes, NULL);
		if (dwRet == 0 || dwWrittenBytes < struVehicleRecogResult.dwPilotSafebeltBufferLen )
		{
			DWORD dwError = GetLastError();
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "PilotSafe Picture Wtite to File Fail.System Error:%d, dwPilotSafebeltBufferLen:%d, dwWrittenBytes:%d ", dwError, struVehicleRecogResult.dwPilotSafebeltBufferLen, dwWrittenBytes);
		}
		CloseHandle(hFile);
		hFile = NULL;
	}
	if (struVehicleRecogResult.dwCopilotSafebeltBufferLen > 0 && struVehicleRecogResult.pCopilotSafebeltBuffer != NULL)
	{
		char cFilename[256] = {0};
		DWORD dwWrittenBytes = 0;
        if (iDeviceIndex != -1 && iDeviceIndex < 512)
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[CopilotSafe]");
        }
        else
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, "[CopilotSafe]");
        }

		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
		
		sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
		
		HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		DWORD dwRet = WriteFile(hFile, struVehicleRecogResult.pCopilotSafebeltBuffer, struVehicleRecogResult.dwCopilotSafebeltBufferLen , &dwWrittenBytes, NULL);
		if (dwRet == 0 || dwWrittenBytes < struVehicleRecogResult.dwCopilotSafebeltBufferLen )
		{
			DWORD dwError = GetLastError();
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "CopilotSafe Picture Wtite to File Fail.System Error:%d, dwCopilotSafebeltBufferLen:%d, dwWrittenBytes:%d ", dwError, struVehicleRecogResult.dwCopilotSafebeltBufferLen, dwWrittenBytes);
		}
		CloseHandle(hFile);
		hFile = NULL;
	}

    if (struVehicleRecogResult.dwJsonBufferLen > 0 && struVehicleRecogResult.pJsonBuffer != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        if (iDeviceIndex != -1 && iDeviceIndex < 512)
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[JSON]");
        }
        else
        {
            sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, pAlarmDev->sDeviceIP, "[JSON]");
        }

        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\LocalTime[%s]_%d.txt", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struVehicleRecogResult.pJsonBuffer, struVehicleRecogResult.dwJsonBufferLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struVehicleRecogResult.dwJsonBufferLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Json Data Write to File Fail.System Error:%d, dwJsonBufferLen :%d, dwWrittenBytes:%d ", dwError, struVehicleRecogResult.dwJsonBufferLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    //释放图片内存
	if (struVehicleRecogResult.pVehicleBuffer != NULL)
	{
		delete [] (struVehicleRecogResult.pVehicleBuffer);
		struVehicleRecogResult.pVehicleBuffer = NULL;
	}
	//释放图片内存
	if (struVehicleRecogResult.pPlateBuffer != NULL)
	{
		delete [] (struVehicleRecogResult.pPlateBuffer);
		struVehicleRecogResult.pPlateBuffer = NULL;
	}
	//释放图片内存
	if (struVehicleRecogResult.pPilotFaceBuffer != NULL)
	{
		delete [] (struVehicleRecogResult.pPilotFaceBuffer);
		struVehicleRecogResult.pPilotFaceBuffer = NULL;
	}
	//释放图片内存
	if (struVehicleRecogResult.pCopilotFaceBuffer != NULL)
	{
		delete [] (struVehicleRecogResult.pCopilotFaceBuffer);
		struVehicleRecogResult.pCopilotFaceBuffer = NULL;
		}
	//释放图片内存
	if (struVehicleRecogResult.pPilotSafebeltBuffer != NULL)
	{
		delete [] (struVehicleRecogResult.pPilotSafebeltBuffer);
		struVehicleRecogResult.pPilotSafebeltBuffer = NULL;
	}
	//释放图片内存
	if (struVehicleRecogResult.pCopilotSafebeltBuffer != NULL)
	{
		delete [] (struVehicleRecogResult.pCopilotSafebeltBuffer);
		struVehicleRecogResult.pCopilotSafebeltBuffer = NULL;
	}

    //释放JSON内存
    if (struVehicleRecogResult.pJsonBuffer != NULL)
    {
        delete[](struVehicleRecogResult.pJsonBuffer);
        struVehicleRecogResult.pJsonBuffer = NULL;
    }
}

void CClientDemoDlg::ProSensorInfoAlarm(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);	
	int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	char szLan[128] = {0};
	g_StringLanType(szLan, "传感器信息上传","Sensor Info Upload");
	NET_DVR_SENSOR_INFO_UPLOAD  struSensorInfo;
    memset(&struSensorInfo, 0, sizeof(struSensorInfo));
	memcpy(&struSensorInfo, pAlarmInfo, sizeof(struSensorInfo));
	
	sprintf(szInfoBuf, "%s: Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d] SensorName[%s] SensorChan[%s] Reboot[%d] PowerSupply[%d] StatusType[%d],\
		SensorType[%d] VoltageValue[%f] CurrentValue[%f] ActualValue[%f] Description[%s]", szLan, struSensorInfo.struTime.wYear, struSensorInfo.struTime.byMonth, \
		struSensorInfo.struTime.byDay, struSensorInfo.struTime.byHour, struSensorInfo.struTime.byMinute, struSensorInfo.struTime.bySecond, struSensorInfo.struTime.wMilliSec, \
		struSensorInfo.szSensorName, struSensorInfo.szSensorChan, struSensorInfo.byReboot, struSensorInfo.byPowerSupply, struSensorInfo.byStatusType, \
		struSensorInfo.bySensorType, struSensorInfo.fVoltageValue, struSensorInfo.fCurrentValue, struSensorInfo.fActualValue, struSensorInfo.szDescription);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProCaptureAlarm(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);	
	int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	char szLan[128] = {0};
	g_StringLanType(szLan, "抓拍图片上传","Capture Upload");
	NET_DVR_CAPTURE_UPLOAD  struCaptureUplad;
    memset(&struCaptureUplad, 0, sizeof(struCaptureUplad));
	memcpy(&struCaptureUplad, pAlarmInfo, sizeof(struCaptureUplad));
	
	sprintf(szInfoBuf, "%s: Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d], Channel[%d], DevName[%s], PicLen[%d]", szLan, struCaptureUplad.struTime.wYear,\
		struCaptureUplad.struTime.byMonth, struCaptureUplad.struTime.byDay, struCaptureUplad.struTime.byHour, struCaptureUplad.struTime.byMinute,\
		struCaptureUplad.struTime.bySecond, struCaptureUplad.struTime.wMilliSec, struCaptureUplad.dwChannel, struCaptureUplad.szDevName, struCaptureUplad.dwPicLen);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
	
	SYSTEMTIME t;
	GetLocalTime(&t);
	char chTime[128];
	sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
	if (struCaptureUplad.dwPicLen > 0 && struCaptureUplad.pBuffer != NULL)
	{
		char cFilename[256] = {0};
		DWORD dwWrittenBytes = 0;
		sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[Sensor]");
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
		
		sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
		
		HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		DWORD dwRet = WriteFile(hFile, struCaptureUplad.pBuffer, struCaptureUplad.dwPicLen, &dwWrittenBytes, NULL);
		if (dwRet == 0 || dwWrittenBytes < struCaptureUplad.dwPicLen )
		{
			DWORD dwError = GetLastError();
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Vehicle Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struCaptureUplad.dwPicLen, dwWrittenBytes);
		}
		CloseHandle(hFile);
		hFile = NULL;
	}

    if (struCaptureUplad.pBuffer != NULL)
    {
        delete [] (struCaptureUplad.pBuffer);
        struCaptureUplad.pBuffer = NULL;
	}
}

void CClientDemoDlg::ProFaceThermometryAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "人脸测温报警上传", "Fire Detection");
    NET_DVR_FACE_THERMOMETRY_ALARM  struFaceThermometry;
    memset(&struFaceThermometry, 0, sizeof(struFaceThermometry));
    memcpy(&struFaceThermometry, pAlarmInfo, sizeof(struFaceThermometry));

    sprintf(szInfoBuf, "%s Channel[%d] RuleID[%d] FaceDetectionState[%d] FaceRect[x:%f y:%f width:%f hight:%f] AlarmTemperature[%f] RuleTemperature[%f] VisibleLightImageLen[%d] RuleName[%s] RelativeTime[%d] AbsTime[%d] ThermometryUnit[%d] ",
        szLan, struFaceThermometry.dwChannel, struFaceThermometry.byRuleID, struFaceThermometry.byFaceDetectionState, struFaceThermometry.struFaceRegion.fX, struFaceThermometry.struFaceRegion.fY, struFaceThermometry.struFaceRegion.fWidth, struFaceThermometry.struFaceRegion.fHeight, struFaceThermometry.fAlarmTemperature, struFaceThermometry.fRuleTemperature, struFaceThermometry.dwVisibleLightImageLen, struFaceThermometry.byRuleName, struFaceThermometry.dwRelativeTime, struFaceThermometry.dwAbsTime, struFaceThermometry.byThermometryUnit);

    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    char cFilepath[256] = { 0 };

    DWORD dwWrittenBytes = 0;
    sprintf(cFilepath, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[Sensor]");
    if (GetFileAttributes(cFilepath) != FILE_ATTRIBUTE_DIRECTORY)
    {
        CreateDirectory(cFilepath, NULL);
    }

    if (struFaceThermometry.dwVisibleLightImageLen > 0 && struFaceThermometry.pVisibleLightImage != NULL)
    {
        char cFilename[256] = { 0 };
        sprintf(cFilename, "%s\\FT_Vis[%s].jpg", cFilepath, chTime);

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struFaceThermometry.pVisibleLightImage, struFaceThermometry.dwVisibleLightImageLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struFaceThermometry.dwVisibleLightImageLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "FaceThermometry vis Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struFaceThermometry.dwVisibleLightImageLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struFaceThermometry.pVisibleLightImage != NULL)
    {
        delete[](struFaceThermometry.pVisibleLightImage);
        struFaceThermometry.pVisibleLightImage = NULL;
    }


    if (struFaceThermometry.dwFaceImageLen > 0 && struFaceThermometry.pFaceImage != NULL)
    {
        char cFilename[256] = { 0 };
        sprintf(cFilename, "%s\\FT_Face[%s].jpg", cFilepath, chTime);

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struFaceThermometry.pFaceImage, struFaceThermometry.dwFaceImageLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struFaceThermometry.dwFaceImageLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "FaceThermometry face Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struFaceThermometry.dwFaceImageLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struFaceThermometry.pFaceImage != NULL)
    {
        delete[](struFaceThermometry.pFaceImage);
        struFaceThermometry.pFaceImage = NULL;
    }
}

void CClientDemoDlg::ProFirDetectionAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    char szSmokeInfoBuf[1024] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);	
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
    char szLan[128] = {0};
    g_StringLanType(szLan, "火点检测报警上传","Fire Detection");
    NET_DVR_FIREDETECTION_ALARM  struFireDetection;
    memset(&struFireDetection, 0, sizeof(struFireDetection));
    memcpy(&struFireDetection, pAlarmInfo, sizeof(struFireDetection));
    
    sprintf(szInfoBuf, "flag[%d] %2.2d%2.2d] %s,FireScanWaitMode[%d] VisibleChannel[%d] RelativeTime:%d, AbsTime:%d, PTZ{PanPos:%d, TiltPos:%d, ZoomPos:%d}, PicDataLen:%d, DevInfo{DevIP:%s, Port:%d, Channel:%d, IvmsChannel:%d,  IvmsChannelEx:%d}, \
        FireMaxTemperature:%d, TargetDistance:%d, fireRectInfo{fX:%f,fY:%f,fWidth%f,fHeight%f}, fireMaxTemperaturePoint{fX:%f,fY:%f}, PTZEx{P:%f,T:%f,Z:%f,F:%d},AlarmSubType:%d",
        struFireDetection.byTimeDiffFlag, struFireDetection.cTimeDifferenceH, struFireDetection.cTimeDifferenceM, \
        szLan, struFireDetection.byFireScanWaitMode, struFireDetection.dwVisibleChannel, struFireDetection.dwRelativeTime, struFireDetection.dwAbsTime, struFireDetection.wPanPos, struFireDetection.wTiltPos, struFireDetection.wZoomPos, \
        struFireDetection.dwPicDataLen, struFireDetection.struDevInfo.struDevIP.sIpV4, struFireDetection.struDevInfo.wPort, struFireDetection.struDevInfo.byChannel, \
        struFireDetection.struDevInfo.byIvmsChannel, struFireDetection.wDevInfoIvmsChannelEx, \
        struFireDetection.wFireMaxTemperature, struFireDetection.wTargetDistance, \
        struFireDetection.struRect.fX, struFireDetection.struRect.fY, struFireDetection.struRect.fWidth, struFireDetection.struRect.fHeight, \
        struFireDetection.struPoint.fX, struFireDetection.struPoint.fY, \
        struFireDetection.struPtzPosEx.fPan, struFireDetection.struPtzPosEx.fTilt, struFireDetection.struPtzPosEx.fZoom, struFireDetection.struPtzPosEx.dwFocus, struFireDetection.byAlarmSubType);


    if (struFireDetection.byAlarmSubType > 0 && struFireDetection.pSmokeBuf != NULL)
    {
        NET_DVR_SMOKEDETECTION_ALARM struSmokeDetection;
        memset(&struSmokeDetection, 0, sizeof(struSmokeDetection));
        memcpy(&struSmokeDetection, struFireDetection.pSmokeBuf, sizeof(struSmokeDetection));

        sprintf_s(szSmokeInfoBuf, "SMOKEDELETECTION ALARM INFO: PTZPos{P:%f, T:%f, Z:%f, Focus:%d}, ThermalPTZPos{P:%f, T:%f, Z:%f, Focus:%d}, Latitude{Type:%d, Sec:%f, Degree:%d, Minute:%d}, Longitude{Type:%d, Sec:%f, Degree:%d, Minute:%d}, SmokePos{X:%f, Y:%f, Width:%f, Height:%f}",
            struSmokeDetection.struPTZPos.fPan, struSmokeDetection.struPTZPos.fTilt, struSmokeDetection.struPTZPos.fZoom, struSmokeDetection.struPTZPos.dwFocus, \
            struSmokeDetection.struThermalPTZPos.fPan, struSmokeDetection.struThermalPTZPos.fTilt, struSmokeDetection.struThermalPTZPos.fZoom, struSmokeDetection.struThermalPTZPos.dwFocus, \
            struSmokeDetection.struLLPos.byLatitudeType, struSmokeDetection.struLLPos.struLatitude.fSec, struSmokeDetection.struLLPos.struLatitude.byDegree, struSmokeDetection.struLLPos.struLatitude.byMinute, \
            struSmokeDetection.struLLPos.byLongitudeType, struSmokeDetection.struLLPos.struLongitude.fSec, struSmokeDetection.struLLPos.struLongitude.byDegree, struSmokeDetection.struLLPos.struLongitude.byMinute, \
            struSmokeDetection.struSmokePos.fX, struSmokeDetection.struSmokePos.fY, struSmokeDetection.struSmokePos.fWidth, struSmokeDetection.struSmokePos.fHeight);

        strcat(szInfoBuf, szSmokeInfoBuf);
    }

    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    
    if (struFireDetection.pSmokeBuf != NULL)
    {
        delete[](struFireDetection.pSmokeBuf);
        struFireDetection.pSmokeBuf = NULL;
    }
    
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    if (struFireDetection.dwPicDataLen > 0 && struFireDetection.pBuffer != NULL)
    {
        char cFilename[256] = {0};
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[Sensor]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
        sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
        
        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struFireDetection.pBuffer, struFireDetection.dwPicDataLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struFireDetection.dwPicDataLen )
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fire Detection Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struFireDetection.dwPicDataLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
	}

    if (struFireDetection.pBuffer != NULL)
    {
        delete [] (struFireDetection.pBuffer);
        struFireDetection.pBuffer = NULL;
	}

    if (struFireDetection.dwVisiblePicLen > 0 && struFireDetection.pVisiblePicBuf != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[Sensor]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struFireDetection.pVisiblePicBuf, struFireDetection.dwVisiblePicLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struFireDetection.dwVisiblePicLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fire Detection VisiblePicture Wtite to File Fail.System Error:%d, dwVisiblePicLen:%d, pVisibleBuffer:%d ", dwError, struFireDetection.dwVisiblePicLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struFireDetection.pVisiblePicBuf != NULL)
    {
        delete[](struFireDetection.pVisiblePicBuf);
        struFireDetection.pVisiblePicBuf = NULL;
    }
}

void CClientDemoDlg::ProPicInfoUploadAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "图片信息上传报警", "PicInfo Upload");
    NET_DVR_PANORAMIC_LINKAGE  struPicInfoUpload;
    memset(&struPicInfoUpload, 0, sizeof(struPicInfoUpload));
    memcpy(&struPicInfoUpload, pAlarmInfo, sizeof(struPicInfoUpload));

    sprintf(szInfoBuf, "%s, Channel:%d, Type:%d, MACAddr:%x:%x:%x:%x:%x:%x, PicDataLen:%d",
        szLan, struPicInfoUpload.dwChannel, struPicInfoUpload.byType, struPicInfoUpload.byMACAddr[0], struPicInfoUpload.byMACAddr[1], struPicInfoUpload.byMACAddr[2], struPicInfoUpload.byMACAddr[3], struPicInfoUpload.byMACAddr[4], struPicInfoUpload.byMACAddr[5], struPicInfoUpload.dwPicLen);

    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);


    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    if (struPicInfoUpload.dwPicLen > 0 && struPicInfoUpload.pPicBuff != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[Sensor]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struPicInfoUpload.pPicBuff, struPicInfoUpload.dwPicLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struPicInfoUpload.dwPicLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "PicInfo Upload Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struPicInfoUpload.dwPicLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struPicInfoUpload.pPicBuff != NULL)
    {
        delete[](struPicInfoUpload.pPicBuff);
        struPicInfoUpload.pPicBuff = NULL;
    }
}

void CClientDemoDlg::ProGISInfoAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);	
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
    char szLan[128] = {0};
    g_StringLanType(szLan, "GIS信息报警上传","GIS Info");
    NET_DVR_GIS_UPLOADINFO  struGISInfo;
    memset(&struGISInfo, 0, sizeof(struGISInfo));
    memcpy(&struGISInfo, pAlarmInfo, sizeof(struGISInfo));
    
    sprintf(szInfoBuf, "%s:PtzPos{PanPos:%.1fTiltPos:%.1fZoomPos:%.1f}RelTime:%dAbsTime:%dAzimuth:%fLongitudeType:%dLatitudeType:%dLongitude{Sec:%.6fDegree:%dMinute:%d}Latitude{Sec:%.6fDegree:%dMinute:%d}Horizontal:%fVertical:%fVisibleRadius:%fMaxView:%fSensor{Type:%dWidth:%fWidth:%fFold:%f}DevInfo{DevIP:%sPort:%dChan:%dIvmsChan:%d}", 
        szLan, struGISInfo.struPtzPos.fPanPos, struGISInfo.struPtzPos.fTiltPos, struGISInfo.struPtzPos.fZoomPos, struGISInfo.dwRelativeTime, struGISInfo.dwAbsTime, \
        struGISInfo.fAzimuth, struGISInfo.byLongitudeType,\
        struGISInfo.byLatitudeType, struGISInfo.struLongitude.fSec, struGISInfo.struLongitude.byDegree, struGISInfo.struLongitude.byMinute,\
        struGISInfo.struLatitude.fSec, struGISInfo.struLatitude.byDegree, struGISInfo.struLatitude.byMinute, struGISInfo.fHorizontalValue, struGISInfo.fVerticalValue, struGISInfo.fVisibleRadius, struGISInfo.fMaxViewRadius,\
        struGISInfo.struSensorParam.bySensorType, struGISInfo.struSensorParam.fHorWidth, struGISInfo.struSensorParam.fVerWidth, struGISInfo.struSensorParam.fFold,\
        struGISInfo.struDevInfo.struDevIP.sIpV4, struGISInfo.struDevInfo.wPort, struGISInfo.struDevInfo.byChannel, struGISInfo.struDevInfo.byIvmsChannel);
       
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProVandalproofAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);	
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
    char szLan[128] = {0};
    g_StringLanType(szLan, "防破坏报警上传","Vandalproof Alarm");
    NET_DVR_VANDALPROOF_ALARM  struVandalproof;
    memset(&struVandalproof, 0, sizeof(struVandalproof));
    memcpy(&struVandalproof, pAlarmInfo, sizeof(struVandalproof));
    
    sprintf(szInfoBuf, "%s: RelativeTime:%d, AbsTime:%d, DevInfo{DevIP:%s, Port:%d, Channel:%d, IvmsChannel:%d}", szLan, struVandalproof.dwRelativeTime, struVandalproof.dwAbsTime, struVandalproof.struDevInfo.struDevIP.sIpV4, \
        struVandalproof.struDevInfo.wPort, struVandalproof.struDevInfo.byChannel, struVandalproof.struDevInfo.byIvmsChannel);
    
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcVideoIntercomEvent(WPARAM wParam,LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iWinIndex = -1;         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_VIDEO_INTERCOM_EVENT  struVideoIntercomEvent = {0};
	CTime time = CTime::GetCurrentTime();
	memcpy(&struVideoIntercomEvent, pAlarmInfo, sizeof(struVideoIntercomEvent));
	
    if (struVideoIntercomEvent.byEventType == 3)
    {
        sprintf(szInfoBuf, "Video Intercom Event Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] DevNumber[%s] EventType[%d] AuthResult[%d] AuthType[%d] CardNo[%s]",
            struVideoIntercomEvent.struTime.wYear, struVideoIntercomEvent.struTime.byMonth, struVideoIntercomEvent.struTime.byDay,
            struVideoIntercomEvent.struTime.byHour, struVideoIntercomEvent.struTime.byMinute, struVideoIntercomEvent.struTime.bySecond,
            struVideoIntercomEvent.byDevNumber, struVideoIntercomEvent.byEventType, struVideoIntercomEvent.uEventInfo.struAuthInfo.byAuthResult,
            struVideoIntercomEvent.uEventInfo.struAuthInfo.byAuthType, struVideoIntercomEvent.uEventInfo.struAuthInfo.byCardNo);
    }
    else if (struVideoIntercomEvent.byEventType == 4)
    {
        sprintf(szInfoBuf, "Video Intercom Event Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] DevNumber[%s] EventType[%d] License[%s] Color[%d]",
            struVideoIntercomEvent.struTime.wYear, struVideoIntercomEvent.struTime.byMonth, struVideoIntercomEvent.struTime.byDay,
            struVideoIntercomEvent.struTime.byHour, struVideoIntercomEvent.struTime.byMinute, struVideoIntercomEvent.struTime.bySecond,
            struVideoIntercomEvent.byDevNumber, struVideoIntercomEvent.byEventType, struVideoIntercomEvent.uEventInfo.struUploadPlateInfo.sLicense,
            struVideoIntercomEvent.uEventInfo.struUploadPlateInfo.byColor);
    }
    else if (struVideoIntercomEvent.byEventType == 1)
    {
        sprintf(szInfoBuf, "Video Intercom Event Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] DevNumber[%s] EventType[%d], FloorNumber[%d], RoomNumber[%d], LockID[%d],LockName[%s],EmployeeNo[%s]",
            struVideoIntercomEvent.struTime.wYear, struVideoIntercomEvent.struTime.byMonth, struVideoIntercomEvent.struTime.byDay,
            struVideoIntercomEvent.struTime.byHour, struVideoIntercomEvent.struTime.byMinute, struVideoIntercomEvent.struTime.bySecond,
            struVideoIntercomEvent.byDevNumber, struVideoIntercomEvent.byEventType,
            struVideoIntercomEvent.uEventInfo.struUnlockRecord.nFloorNumber,
            struVideoIntercomEvent.uEventInfo.struUnlockRecord.wRoomNumber,
            struVideoIntercomEvent.uEventInfo.struUnlockRecord.wLockID,
            struVideoIntercomEvent.uEventInfo.struUnlockRecord.byLockName,
            struVideoIntercomEvent.uEventInfo.struUnlockRecord.byEmployeeNo);
    }
    else if (struVideoIntercomEvent.byEventType == 5 || struVideoIntercomEvent.byEventType == 6)
    {
        sprintf(szInfoBuf, "Video Intercom Event Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] DevNumber[%s] EventType[%d] CardNo[%s]",
            struVideoIntercomEvent.struTime.wYear, struVideoIntercomEvent.struTime.byMonth, struVideoIntercomEvent.struTime.byDay,
            struVideoIntercomEvent.struTime.byHour, struVideoIntercomEvent.struTime.byMinute, struVideoIntercomEvent.struTime.bySecond,
            struVideoIntercomEvent.byDevNumber, struVideoIntercomEvent.byEventType,
            struVideoIntercomEvent.uEventInfo.struSendCardInfo.byCardNo);
    }
    else
    {
        sprintf(szInfoBuf, "Video Intercom Event Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] DevNumber[%s] EventType[%d]",
            struVideoIntercomEvent.struTime.wYear, struVideoIntercomEvent.struTime.byMonth, struVideoIntercomEvent.struTime.byDay,
            struVideoIntercomEvent.struTime.byHour, struVideoIntercomEvent.struTime.byMinute, struVideoIntercomEvent.struTime.bySecond,
            struVideoIntercomEvent.byDevNumber, struVideoIntercomEvent.byEventType);
    }

    if (struVideoIntercomEvent.dwIOTChannelNo != 0)
    {
        sprintf(szInfoBuf, "%s IOTChannelNo", struVideoIntercomEvent.dwIOTChannelNo);
    }
	
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
	if (struVideoIntercomEvent.byEventType == 1 && struVideoIntercomEvent.uEventInfo.struUnlockRecord.dwPicDataLen > 0)
	{
		int num = ulAlarmPic/1000+1;
		ulAlarmPic++;
		
		char cFilename[256] = {0};
		HANDLE hFile;
		DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
		
		sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
        
        if (struVideoIntercomEvent.byPicTransType)
        {
            sprintf(cFilename, "%s\\LocalTime[%s]_%d.txt", cFilename, chTime, rand() % GetTickCount());
        }
        else
        {
            sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());
        }
		hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		WriteFile(hFile, struVideoIntercomEvent.uEventInfo.struUnlockRecord.pImage, struVideoIntercomEvent.uEventInfo.struUnlockRecord.dwPicDataLen, &dwReturn, NULL);
		CloseHandle(hFile);
		hFile = NULL;
		
		delete [] struVideoIntercomEvent.uEventInfo.struUnlockRecord.pImage;
		struVideoIntercomEvent.uEventInfo.struUnlockRecord.pImage = NULL;	
	}

    if (struVideoIntercomEvent.byEventType == 3 && struVideoIntercomEvent.uEventInfo.struAuthInfo.dwPicDataLen > 0)
    {
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;

        char cFilename[256] = { 0 };
        HANDLE hFile;
        DWORD dwReturn;

        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

        sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\LocalTime[%s].jpg", cFilename, chTime);
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struVideoIntercomEvent.uEventInfo.struAuthInfo.pImage, struVideoIntercomEvent.uEventInfo.struAuthInfo.dwPicDataLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;

        delete[] struVideoIntercomEvent.uEventInfo.struAuthInfo.pImage;
        struVideoIntercomEvent.uEventInfo.struAuthInfo.pImage = NULL;
    }
}

void CClientDemoDlg::ProcVideoIntercomAlarm(WPARAM wParam,LPARAM lParam)
{  
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iWinIndex = -1;         
	int i = 0;
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_VIDEO_INTERCOM_ALARM  struVideoIntercomAlarm = {0};
	CTime time = CTime::GetCurrentTime();
	memcpy(&struVideoIntercomAlarm, pAlarmInfo, sizeof(struVideoIntercomAlarm));
	
	if (struVideoIntercomAlarm.byAlarmType == 1)
	{
        sprintf(szInfoBuf, "Video Intercom Alarm Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] DevNumber[%s] AlarmType[%d] ZoneName[%s] ZoneIndex[%d] ZoneType[%d] IOTChannelNo[%d]",
            struVideoIntercomAlarm.struTime.wYear, struVideoIntercomAlarm.struTime.byMonth, struVideoIntercomAlarm.struTime.byDay,
            struVideoIntercomAlarm.struTime.byHour, struVideoIntercomAlarm.struTime.byMinute, struVideoIntercomAlarm.struTime.bySecond,
            struVideoIntercomAlarm.byDevNumber, struVideoIntercomAlarm.byAlarmType, struVideoIntercomAlarm.uAlarmInfo.struZoneAlarm.byZoneName,
            struVideoIntercomAlarm.uAlarmInfo.struZoneAlarm.dwZonendex, struVideoIntercomAlarm.uAlarmInfo.struZoneAlarm.byZoneType,
            struVideoIntercomAlarm.dwIOTChannelNo);
	}
	else
	{
        sprintf(szInfoBuf, "Video Intercom Alarm Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] DevNumber[%s] AlarmType[%d] LockID[%d] IOTChannelNo[%d]",
            struVideoIntercomAlarm.struTime.wYear, struVideoIntercomAlarm.struTime.byMonth, struVideoIntercomAlarm.struTime.byDay,
            struVideoIntercomAlarm.struTime.byHour, struVideoIntercomAlarm.struTime.byMinute, struVideoIntercomAlarm.struTime.bySecond,
            struVideoIntercomAlarm.byDevNumber, struVideoIntercomAlarm.byAlarmType,
            struVideoIntercomAlarm.wLockID, struVideoIntercomAlarm.dwIOTChannelNo);
        if (struVideoIntercomAlarm.byAlarmType == 8)
        {
            CDlgVideoIntercomCall dlg;
            dlg.m_iDevIndex = pAlarmDev->iDeviceIndex;
            dlg.m_lUserID = m_iCardChanCount;
            dlg.m_byRequestType = 1;
            dlg.DoModal();
        }
	}
	
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcUploadNoticeData(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[4096] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iWinIndex = -1;
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    NET_DVR_NOTICE_DATA  struNoticeData = { 0 };
    CTime time = CTime::GetCurrentTime();
    memcpy(&struNoticeData, pAlarmInfo, sizeof(struNoticeData));

    sprintf(szInfoBuf, "Notice Data Event Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] NoticeNumber[%s] NoticeTheme[%s] NoticeDetail[%s] Level[%d] PicNum[%d]",
        struNoticeData.struTime.wYear, struNoticeData.struTime.byMonth, struNoticeData.struTime.byDay,
        struNoticeData.struTime.byHour, struNoticeData.struTime.byMinute, struNoticeData.struTime.bySecond,
        struNoticeData.byNoticeNumber, struNoticeData.byNoticeTheme, struNoticeData.byNoticeDetail, struNoticeData.byLevel, struNoticeData.byPicNum);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

    if (struNoticeData.byPicNum > 0)
    {
        int num = ulAlarmPic / 1000 + 1;
        ulAlarmPic++;
        char cFileDirectory[256] = { 0 };
        HANDLE hFile;
        DWORD dwReturn;
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

        sprintf(cFileDirectory, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName, num);
        if (GetFileAttributes(cFileDirectory) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFileDirectory, NULL);
        }

        char cFileName[256] = { 0 };

        for (int i = 0; i < MAX_NOTICE_PIC_NUM; i++)
        {
            if (struNoticeData.struNoticePic[i].dwPicDataLen > 0)
            {
                memset(cFileName, 0, 256);
                sprintf(cFileName, "%s\\LocalTime[%s]No[%d].jpg", cFileDirectory, chTime, i);
                hFile = CreateFile(cFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hFile == INVALID_HANDLE_VALUE)
                {
                    return;
                }
                WriteFile(hFile, struNoticeData.struNoticePic[i].pPicData, struNoticeData.struNoticePic[i].dwPicDataLen, &dwReturn, NULL);
                CloseHandle(hFile);
                hFile = NULL;

                delete[] struNoticeData.struNoticePic[i].pPicData;
                struNoticeData.struNoticePic[i].pPicData = NULL;
            }
        }
    }
}

void CClientDemoDlg::ProcPeopleDetectionUpload(WPARAM wParam,LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
//    char szAlarmInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iWinIndex = -1;         
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_PEOPLE_DETECTION_RESULT  struPeopleDetcetion = {0};
	memcpy(&struPeopleDetcetion, pAlarmInfo, sizeof(struPeopleDetcetion));
    
    //  打印信息
    NET_DVR_TIME  struAbsTime = {0};
    struAbsTime.dwYear = GET_YEAR(struPeopleDetcetion.dwAbsTime);
    struAbsTime.dwMonth = GET_MONTH(struPeopleDetcetion.dwAbsTime);
    struAbsTime.dwDay = GET_DAY(struPeopleDetcetion.dwAbsTime);
    struAbsTime.dwHour = GET_HOUR(struPeopleDetcetion.dwAbsTime);
    struAbsTime.dwMinute = GET_MINUTE(struPeopleDetcetion.dwAbsTime);
    struAbsTime.dwSecond = GET_SECOND(struPeopleDetcetion.dwAbsTime);
    
    NET_DVR_TIME  struRelativeTime = {0};
    struRelativeTime.dwYear = GET_YEAR(struPeopleDetcetion.dwRelativeTime);
    struRelativeTime.dwMonth = GET_MONTH(struPeopleDetcetion.dwRelativeTime);
    struRelativeTime.dwDay = GET_DAY(struPeopleDetcetion.dwRelativeTime);
    struRelativeTime.dwHour = GET_HOUR(struPeopleDetcetion.dwRelativeTime);
    struRelativeTime.dwMinute = GET_MINUTE(struPeopleDetcetion.dwRelativeTime);
    struRelativeTime.dwSecond = GET_SECOND(struPeopleDetcetion.dwRelativeTime);


//     for (i = 0; i < 8; i++)
//     {
//         if (struPeopleDetcetion.struPeopleRegion[i].byNumber != 0)
//         {
//             sprintf(szAlarmInfoBuf, "RegionID:RegionNumberOfPeople [%d: %d],[%d: %d],[%d: %d],[%d: %d],[%d: %d],[%d: %d],[%d: %d],[%d: %d]", \
//                 struPeopleDetcetion.struPeopleRegion[0].byID, struPeopleDetcetion.struPeopleRegion[0].byNumber, 
//                 struPeopleDetcetion.struPeopleRegion[1].byID, struPeopleDetcetion.struPeopleRegion[1].byNumber, 
//                 struPeopleDetcetion.struPeopleRegion[2].byID, struPeopleDetcetion.struPeopleRegion[2].byNumber, 
//                 struPeopleDetcetion.struPeopleRegion[3].byID, struPeopleDetcetion.struPeopleRegion[3].byNumber,               
//                 struPeopleDetcetion.struPeopleRegion[4].byID, struPeopleDetcetion.struPeopleRegion[4].byNumber, 
//                 struPeopleDetcetion.struPeopleRegion[5].byID, struPeopleDetcetion.struPeopleRegion[5].byNumber, 
//                 struPeopleDetcetion.struPeopleRegion[6].byID, struPeopleDetcetion.struPeopleRegion[6].byNumber, 
//                 struPeopleDetcetion.struPeopleRegion[7].byID, struPeopleDetcetion.struPeopleRegion[7].byNumber);
//         }
//         
//     }
    char cTempInfo[256] = {0};
    for (i = 0; i < MAX_PEOPLE_DETECTION_NUM; i++)
    {
        if (struPeopleDetcetion.struPeopleRegion[i].byNumber != 0)
        {
            sprintf(cTempInfo + strlen(cTempInfo), "RegionID[%d] RegionNumberOfPeople[%d] DressType[%d]", \
                struPeopleDetcetion.struPeopleRegion[i].byID, struPeopleDetcetion.struPeopleRegion[i].byNumber, struPeopleDetcetion.struPeopleRegion[i].byDressType);
            //cTempInfo += strlen(cTempInfo);
        }
    }

    sprintf(szInfoBuf, "[people Detection Alarm Time] AlarmInfoBuf[%s] Abs[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] RelativeTime[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d] Dev[ip:%s,port:%d,ivmsChan:%d] PeopleAlarmType[%d]\n",\
        cTempInfo
        ,struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour,struAbsTime.dwMinute, struAbsTime.dwSecond, \
        struRelativeTime.dwYear, struRelativeTime.dwMonth, struRelativeTime.dwDay, struRelativeTime.dwHour,struRelativeTime.dwMinute, struRelativeTime.dwSecond, \
        struPeopleDetcetion.struDevInfo.struDevIP.sIpV4, struPeopleDetcetion.struDevInfo.wPort, struPeopleDetcetion.struDevInfo.byIvmsChannel,\
        struPeopleDetcetion.byPeopleAlarmType);

    for (i=0; i<MAX_PEOPLE_DETECTION_NUM; i++)
    {
        if (struPeopleDetcetion.struPeopleRegion[i].dwPicLen > 0 && struPeopleDetcetion.struPeopleRegion[i].pPicBuffer != NULL)
        {
            int num = ulAlarmPic/1000+1;
            ulAlarmPic++;
            
            char cFilename[256] = {0};
            HANDLE hFile;
            DWORD dwReturn;
            
            SYSTEMTIME t;
            GetLocalTime(&t);
            char chTime[128];
            sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
            
            sprintf(cFilename, "%s\\%s[%d]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, num);
            if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFilename, NULL);
            }           
            
            sprintf(cFilename, "%s\\peopleDet_LocalTime[%s]_%d.jpg",cFilename, chTime, i);
            hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return;
            }
            WriteFile(hFile, struPeopleDetcetion.struPeopleRegion[i].pPicBuffer, struPeopleDetcetion.struPeopleRegion[i].dwPicLen, &dwReturn, NULL);
            CloseHandle(hFile);
			hFile = NULL;
        }
    }

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    
}

void CClientDemoDlg::ProcFiberConvertAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    char szAlarmInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iWinIndex = -1;         
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    
    NET_DVR_FIBER_CONVERT_ALARM  struFiberConvertAlarm = {0};
	memcpy(&struFiberConvertAlarm, pAlarmInfo, sizeof(struFiberConvertAlarm));

    int iLen = sprintf(szInfoBuf, "[FIBER_CONVERT_ALARM]");

    if (struFiberConvertAlarm.dwEventType == 1)
    {
        sprintf(szInfoBuf, "%sType:Alarm", szInfoBuf);
        if (struFiberConvertAlarm.dwEvent == FC_OPTICAL_PORT_LOST)
        {
            sprintf(szInfoBuf, "%s Event:Optical port lost", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_ELECTRICAL_PORT_LOST)
        {
            sprintf(szInfoBuf, "%s Event:Electrical port lost", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_FUNC_CARD_LOST)
        {
            sprintf(szInfoBuf, "%s Event:Function card lost", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_CARD_DISCONNECTED)
        {
            sprintf(szInfoBuf, "%s Event:Card disconnected", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_MAX_TEMP_LIMITED)
        {
            sprintf(szInfoBuf, "%s Event:Maximum temperature limited", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_MIN_TEMP_LIMITED)
        {
            sprintf(szInfoBuf, "%s Event:Minimum temperature limited", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_MAX_VOLTAGE_LIMITED)
        {
            sprintf(szInfoBuf, "%s Event:Maximum voltage limited", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_MIN_VOLTAGE_LIMITED)
        {
            sprintf(szInfoBuf, "%s Event:Minimum voltage limited", szInfoBuf);
        }
    }
    else if (struFiberConvertAlarm.dwEventType == 2)
    {
        sprintf(szInfoBuf, "%sType:Notification", szInfoBuf);
        if (struFiberConvertAlarm.dwEvent == FC_OPTICAL_PORT_CONNECTED)
        {
            sprintf(szInfoBuf, "%s Event:Optical port connected", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_ELECTRICAL_PORT_CONNECTED)
        {
            sprintf(szInfoBuf, "%s Event:Electrical port connected", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_FUNC_CARD_INSERT)
        {
            sprintf(szInfoBuf, "%s Event:Function card insert", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_CARD_CONNECTED)
        {
            sprintf(szInfoBuf, "%s Event:Card connected", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_TEMP_RECOVERY)
        {
            sprintf(szInfoBuf, "%s Event:Temperature recovery", szInfoBuf);
        }
        else if (struFiberConvertAlarm.dwEvent == FC_VOLTAGE_RECOVERY)
        {
            sprintf(szInfoBuf, "%s Event:Voltage recovery", szInfoBuf);
        }
    }

    if (struFiberConvertAlarm.byCardType == 1)
    {
        sprintf(szInfoBuf, "%s CardType:NetMgr card", szInfoBuf);        
    }
    else if (struFiberConvertAlarm.byCardType == 2)
    {
        sprintf(szInfoBuf, "%s CardType:Function card", szInfoBuf);
    }
    else if (struFiberConvertAlarm.byCardType == 3)
    {
        sprintf(szInfoBuf, "%s CardType:Remote send card", szInfoBuf);
    }
    else if (struFiberConvertAlarm.byCardType == 4)
    {
        sprintf(szInfoBuf, "%s CardType:Device crate", szInfoBuf);
    }

    sprintf(szInfoBuf, "%s SlotNum:%d PortNo:%d Temp:%d Voltage:%d", 
        szInfoBuf, struFiberConvertAlarm.bySlotNum, struFiberConvertAlarm.byPortNo, struFiberConvertAlarm.byCurTemperature, struFiberConvertAlarm.wCurVoltage);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcFacecaptureStatistics(WPARAM wParam, LPARAM lParam)//人脸抓拍统计上传
{
	char szInfoBuf[1024] = {0}; 
	char szLan[128] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	NET_DVR_FACECAPTURE_STATISTICS_RESULT struFacecapture = {0};
	memcpy(&struFacecapture, pAlarmInfo, sizeof(struFacecapture));
	
	g_StringLanType(szLan, "人脸抓拍统计上传","Face Capture Statistics Upload");
	
	int len = 0,oldlen = 0,sexlen = 0;
	len = sprintf(szInfoBuf, "%s: (开始时间:%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d,结束时间:%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d)\n", \
		szLan, struFacecapture.struStartTime.wYear,struFacecapture.struStartTime.byMonth,struFacecapture.struStartTime.byDay,struFacecapture.struStartTime.byHour,\
		struFacecapture.struStartTime.byMinute,struFacecapture.struStartTime.bySecond,struFacecapture.struEndTime.wYear,\
		struFacecapture.struEndTime.byMonth,struFacecapture.struEndTime.byDay,struFacecapture.struEndTime.byHour,struFacecapture.struEndTime.byMinute,\
		struFacecapture.struEndTime.bySecond);
	if ((struFacecapture.byStatType >> 2) & 1)
	{
		oldlen = sprintf(szInfoBuf+len,"%s","年龄段有效");
	}
	if ((struFacecapture.byStatType >> 1) & 1)
	{
		sexlen = sprintf(szInfoBuf+len+oldlen,"%s","性别有效");
	}
	if (struFacecapture.byStatType & 1)
	{
		sprintf(szInfoBuf+len+oldlen+sexlen,"%s","人数有效");
	}
	g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    char szTmpCN[200] = {0};
    sprintf(szTmpCN, "统计人数:%d,少年:%d,青年:%d,中年:%d,老年:%d,儿童:%d,青少年:%d,壮年:%d,中老年:%d,男:%d,女:%d", struFacecapture.dwPeopleNum, struFacecapture.struAgeGroupParam.dwTeenage, \
        struFacecapture.struAgeGroupParam.dwYouth, struFacecapture.struAgeGroupParam.dwMidLife, struFacecapture.struAgeGroupParam.dwElderly, \
        struFacecapture.struAgeGroupParam.dwChild, struFacecapture.struAgeGroupParam.dwAdolescent, struFacecapture.struAgeGroupParam.dwPrime, struFacecapture.struAgeGroupParam.dwMidage,\
        struFacecapture.struSexGroupParam.dwMale, struFacecapture.struSexGroupParam.dwFemale);

    char szTmpEN[200] = {0};
    sprintf(szTmpEN, "PeopleNum:%d，Teen：%d, Youth：%d，Midlife：%d， Elderly：%d，Child:%d,Adolescent:%d,Prime:%d,Midage:%d, male：%d，female：%d", struFacecapture.dwPeopleNum, struFacecapture.struAgeGroupParam.dwTeenage, \
        struFacecapture.struAgeGroupParam.dwYouth, struFacecapture.struAgeGroupParam.dwMidLife, struFacecapture.struAgeGroupParam.dwElderly,\
        struFacecapture.struAgeGroupParam.dwChild, struFacecapture.struAgeGroupParam.dwAdolescent, struFacecapture.struAgeGroupParam.dwPrime, struFacecapture.struAgeGroupParam.dwMidage, \
        struFacecapture.struSexGroupParam.dwMale, struFacecapture.struSexGroupParam.dwFemale);

    g_StringLanType(szInfoBuf, szTmpCN, szTmpEN);
    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
	
}

void CClientDemoDlg::ProcVideoParkingPoleAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    char szLan[128] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    NET_DVR_VIDEO_PARKING_POLE_ALARM struVideoParkingPoleAlarm = { 0 };
    memcpy(&struVideoParkingPoleAlarm, pAlarmInfo, sizeof(struVideoParkingPoleAlarm));

    g_StringLanType(szLan, "视频桩报警", "Video Parking Pole Alarm");

    sprintf(szInfoBuf, "%s: Time[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d],ParkingNum[%s],AlarmType[%d]", szLan, \
        struVideoParkingPoleAlarm.struTime.wYear, struVideoParkingPoleAlarm.struTime.byMonth, struVideoParkingPoleAlarm.struTime.byDay, \
        struVideoParkingPoleAlarm.struTime.byHour, struVideoParkingPoleAlarm.struTime.byMinute, struVideoParkingPoleAlarm.struTime.bySecond, struVideoParkingPoleAlarm.struTime.wMilliSec, \
        struVideoParkingPoleAlarm.byParkingNum, struVideoParkingPoleAlarm.byAlarmType);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcSwicthLampAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);	
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
    char szLan[128] = {0};
    g_StringLanType(szLan, "开关灯检测报警上传","Switch Lamp Detection");
    NET_DVR_SWITCH_LAMP_ALARM  struSwitchLamp = {0};
    memset(&struSwitchLamp, 0, sizeof(struSwitchLamp));
    memcpy(&struSwitchLamp, pAlarmInfo, sizeof(struSwitchLamp));
    
    sprintf(szInfoBuf, "%s AlarmTime[%04d-%02d-%02d %02d:%02d:%02d], lamp Status:%d, PicDataLen:%d, DevInfo{DevIP:%s, Port:%d, Channel:%d, IvmsChannel:%d}",\
        szLan, struSwitchLamp.struTime.wYear,struSwitchLamp.struTime.byMonth,struSwitchLamp.struTime.byDay,struSwitchLamp.struTime.byHour,\
        struSwitchLamp.struTime.byMinute,struSwitchLamp.struTime.bySecond,struSwitchLamp.byLampStatus,\
        struSwitchLamp.dwPicDataLen, struSwitchLamp.struDevInfo.struDevIP.sIpV4, struSwitchLamp.struDevInfo.wPort, struSwitchLamp.struDevInfo.byChannel,\
        struSwitchLamp.struDevInfo.byIvmsChannel);
    
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    
    
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    if (struSwitchLamp.dwPicDataLen > 0 && struSwitchLamp.pPicData != NULL)
    {
        char cFilename[256] = {0};
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[SwitchLamp]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
        sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
        
        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struSwitchLamp.pPicData, struSwitchLamp.dwPicDataLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struSwitchLamp.dwPicDataLen )
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "SwitchLamp Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struSwitchLamp.dwPicDataLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }
    
    if (struSwitchLamp.pPicData != NULL)
    {
        delete [] (struSwitchLamp.pPicData);
        struSwitchLamp.pPicData = NULL;
    }
}

void CClientDemoDlg::ProGateCardIndoAlarm( WPARAM wParam, LPARAM lParam )
{
	char szInfoBuf[1024] = {0};
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);	
	int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	char szLan[128] = {0};
	g_StringLanType(szLan, "出入口卡片信息上传","Entrance card information upload");
	NET_DVR_GATE_CARDINFO  struGateCardInfo;
    memset(&struGateCardInfo, 0, sizeof(struGateCardInfo));
	memcpy(&struGateCardInfo, pAlarmInfo, sizeof(struGateCardInfo));
	
	sprintf(szInfoBuf, "%s: DevInfo{DevIP:%s, Port:%d, Channel:%d, IvmsChannel:%d} RelativeTime:%d, AbsTime:%d, CardNo:%s, PassVehicleID:%s, InVehicleID:%s,\
LetPass:%d, CardType:%d",\
szLan, struGateCardInfo.struDevInfo.struDevIP.sIpV4, struGateCardInfo.struDevInfo.wPort, struGateCardInfo.struDevInfo.byChannel,\
struGateCardInfo.struDevInfo.byIvmsChannel, struGateCardInfo.dwRelativeTime, struGateCardInfo.dwAbsTime, struGateCardInfo.szCardNo,\
struGateCardInfo.szPassVehicleID, struGateCardInfo.szInVehicleID, struGateCardInfo.byLetPass, struGateCardInfo.byCardType);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProGateCardChargeAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);	
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
    char szLan[128] = {0};
    g_StringLanType(szLan, "出入口收费上传","Entrance Charge information upload");
    NET_DVR_GATE_CHARGEINFO  struGateChargeInfo;
    memset(&struGateChargeInfo, 0, sizeof(struGateChargeInfo));
    memcpy(&struGateChargeInfo, pAlarmInfo, sizeof(struGateChargeInfo));
    
    sprintf(szInfoBuf, "%s:DevInfo{DevIP:%s,Port:%d,Channel:%d,IvmsChannel:%d}RelativeTime:%d,AbsTime:%d,sLicense:%s,CardNo:%s,\
			Entrance:%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d,Departure:%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d,DepartureID:%s,EntranceID:%s,\
			TotalCost:%d,OperateName:%s,ChargeRuleId:%d,VehicleType:%d",\
			szLan, struGateChargeInfo.struDevInfo.struDevIP.sIpV4, struGateChargeInfo.struDevInfo.wPort, struGateChargeInfo.struDevInfo.byChannel,\
			struGateChargeInfo.struDevInfo.byIvmsChannel, struGateChargeInfo.dwRelativeTime, struGateChargeInfo.dwAbsTime, struGateChargeInfo.sLicense,\
			struGateChargeInfo.szCardNo,struGateChargeInfo.struEntranceTime.wYear,struGateChargeInfo.struEntranceTime.byMonth,\
			struGateChargeInfo.struEntranceTime.byDay,struGateChargeInfo.struEntranceTime.byHour, struGateChargeInfo.struEntranceTime.byMinute,\
			struGateChargeInfo.struEntranceTime.bySecond,struGateChargeInfo.struEntranceTime.wMilliSec,struGateChargeInfo.struDepartureTime.wYear,\
			struGateChargeInfo.struDepartureTime.byMonth,struGateChargeInfo.struDepartureTime.byDay,struGateChargeInfo.struDepartureTime.byHour, \
			struGateChargeInfo.struDepartureTime.byMinute,struGateChargeInfo.struDepartureTime.bySecond,struGateChargeInfo.struDepartureTime.wMilliSec,\
			struGateChargeInfo.szDepartureID,struGateChargeInfo.szEntranceID,struGateChargeInfo.dwTotalCost,struGateChargeInfo.szOperateName,\
			struGateChargeInfo.szOperateName,struGateChargeInfo.byChargeRuleId,struGateChargeInfo.byVehicleType);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProConferenceAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);	
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
	char szLan[128] = {0};
    NET_DVR_CONFERENCE_CALL_ALARM  struConference = {0};    
    memcpy(&struConference, pAlarmInfo, sizeof(struConference));
	if (struConference.byAlarmType == 1) //会议呼叫
	{
		
		g_StringLanType(szLan, "会议呼叫告警","Conference Call Alarm");
		if (struConference.byCallType == 1)
		{
			sprintf(szInfoBuf, "%s: type:point to point, url:%s", szLan, struConference.struCallInfo.struTerminalCallInfo.byTermianlURL); 
		}
		else if (struConference.byCallType == 2)
		{
			sprintf(szInfoBuf, "%s: type:conference call,ID:%s,name:%s,start:%4d-%2d-%2d %2d:%2d:%2d,end:%4d-%2d-%2d %2d:%2d:%2d", szLan,\
				struConference.struCallInfo.struConferenceCallInfo.byConferenceID,\
				struConference.struCallInfo.struConferenceCallInfo.byConferenceName,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwYear,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwMonth,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwDay,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwHour,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwMinute,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwSecond,\
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwYear,\
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwMonth,\
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwDay, \
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwHour,\
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwMinute,\
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwSecond);
		}    
	}
	else if (struConference.byAlarmType == 2) //呼叫状态切换
	{
		g_StringLanType(szLan, "呼叫状态切换告警", "Call Answer Alarm");
		char szAnswerType[32] = {0};
		if (struConference.byCallStatusSwitch == 1)
		{
			g_StringLanType(szAnswerType, "开始呼叫", "Start Call");
		}
		else if (struConference.byCallStatusSwitch == 2)
		{
			g_StringLanType(szAnswerType, "呼叫成功", "Call succeed");
		}
		else if (struConference.byCallStatusSwitch == 3)
		{
			g_StringLanType(szAnswerType, "呼叫结束", "Call over");
		}
		else if (struConference.byCallStatusSwitch == 4)
		{
			g_StringLanType(szAnswerType, "对端挂断", "Hang up");
		}
		if (struConference.byCallType == 1)
		{
			sprintf(szInfoBuf, "%s[%s]: type:point to point, url:%s", szLan, szAnswerType, struConference.struCallInfo.struTerminalCallInfo.byTermianlURL); 
		}
		else if (struConference.byCallType == 2)
		{
			sprintf(szInfoBuf, "%s[%s]: type:conference call,ID:%s,name:%s,start:%4d-%2d-%2d %2d:%2d:%2d,end:%4d-%2d-%2d %2d:%2d:%2d", szLan, szAnswerType, \
				struConference.struCallInfo.struConferenceCallInfo.byConferenceID,\
				struConference.struCallInfo.struConferenceCallInfo.byConferenceName,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwYear,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwMonth,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwDay,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwHour,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwMinute,\
				struConference.struCallInfo.struConferenceCallInfo.struStartTime.dwSecond,\
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwYear,\
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwMonth,\
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwDay, \
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwHour,\
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwMinute,\
				struConference.struCallInfo.struConferenceCallInfo.struEndTime.dwSecond);
		}
	}
   
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);   
}

void CClientDemoDlg::ProcIDInfoAlarm(WPARAM wParam, LPARAM lParam)
{
    //char szInfoBuf[1024] = {0};
    char szTriggerTime[1024] = {0};
    char szLan[128] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
    NET_DVR_ID_CARD_INFO_ALARM struIDCardInfo = {0};
    memset(&struIDCardInfo, 0, sizeof(NET_DVR_ID_CARD_INFO_ALARM));
    memcpy(&struIDCardInfo, pAlarmInfo, sizeof(NET_DVR_ID_CARD_INFO_ALARM));

    g_StringLanType(szLan, "身份证信息上传", "ID Information upload");

    CString szTmp = "";
    szTmp.Format("%s", struIDCardInfo.struIDCardCfg.byName);
    string szName = UTF82ASCII(szTmp);

    szTmp.Format("%s", struIDCardInfo.struIDCardCfg.byAddr);
    string szAddr = UTF82ASCII(szTmp);

    szTmp.Format("%s", struIDCardInfo.struIDCardCfg.byIssuingAuthority);
    string szIssuingAuthority = UTF82ASCII(szTmp);

    sprintf(szTriggerTime, "%s start,name:%s,\r\nAddr:%s\r\nIssuingAuthority:%s\r\nID:%s,%d-%d-%d\r\nbyCardType:%d", szLan, szName.c_str(), szAddr.c_str(), szIssuingAuthority.c_str(),
        struIDCardInfo.struIDCardCfg.byIDNum, struIDCardInfo.struIDCardCfg.struStartDate.wYear, struIDCardInfo.struIDCardCfg.struStartDate.byMonth,
        struIDCardInfo.struIDCardCfg.struStartDate.byDay, struIDCardInfo.byCardType);
    AddLog(iDeviceIndex, ALARM_INFO_T,szTriggerTime);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    if (struIDCardInfo.dwPicDataLen > 0 && struIDCardInfo.pPicData != NULL)
    {
        char cFilename[256] = {0};
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "Sensor");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
        sprintf(cFilename, "%s\\LocalTime[%s]_%d.bin",cFilename, chTime,rand() % GetTickCount());
        
        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struIDCardInfo.pPicData, struIDCardInfo.dwPicDataLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struIDCardInfo.dwPicDataLen )
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "ID Card Info Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struIDCardInfo.dwPicDataLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
	}

    // 指纹数据
    if (struIDCardInfo.dwFingerPrintDataLen > 0 && struIDCardInfo.pFingerPrintData != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "Sensor");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\LocalTime[%s]_FingerPrintData_%d.bin", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struIDCardInfo.pFingerPrintData, struIDCardInfo.dwFingerPrintDataLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struIDCardInfo.dwFingerPrintDataLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "ID Card Info Fingerprint Data Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struIDCardInfo.dwFingerPrintDataLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    //抓拍图片数据
    if (struIDCardInfo.dwCapturePicDataLen > 0 && struIDCardInfo.pCapturePicData != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "Sensor");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\LocalTime[%s]_CapturePic_%d.bin", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struIDCardInfo.pCapturePicData, struIDCardInfo.dwCapturePicDataLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struIDCardInfo.dwCapturePicDataLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "ID Card Info Capture Picture Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struIDCardInfo.dwCapturePicDataLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struIDCardInfo.pPicData != NULL)
    {
        delete[](struIDCardInfo.pPicData);
        struIDCardInfo.pPicData = NULL;
    }
    if (struIDCardInfo.pFingerPrintData != NULL)
    {
        delete[](struIDCardInfo.pFingerPrintData);
        struIDCardInfo.pFingerPrintData = NULL;
    }
    if (struIDCardInfo.pCapturePicData != NULL)
    {
        delete[](struIDCardInfo.pCapturePicData);
        struIDCardInfo.pCapturePicData = NULL;
    }
}

void CClientDemoDlg::ProcPassNumInfoAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};
    char szTriggerTime[128] = {0};
    char szLan[128] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
    NET_DVR_PASSNUM_INFO_ALARM struPassNumInfo = {0};
    memcpy(&struPassNumInfo, pAlarmInfo, sizeof(NET_DVR_PASSNUM_INFO_ALARM));
    
    g_StringLanType(szLan, "通行人数上报", "pass number Information upload");
    
    sprintf(szTriggerTime, "%s start,EntryTimes:%d,ExitTimes:%d,TotalTimes:%d", szLan, struPassNumInfo.dwEntryTimes, struPassNumInfo.dwExitTimes, struPassNumInfo.dwTotalTimes);
    AddLog(iDeviceIndex, ALARM_INFO_T,szTriggerTime);
}

void CClientDemoDlg::ProcStorageDetAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = {0};

    char szLan[128] = {0};
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);		
    int iDeviceIndex = pAlarmDev->iDeviceIndex;	
    NET_DVR_STORAGE_DETECTION_ALARM struStorageDet = {0};
    memcpy(&struStorageDet, pAlarmInfo, sizeof(NET_DVR_STORAGE_DETECTION_ALARM));
    
    g_StringLanType(szLan, "存储智能检测报警上传", "Storage Detection");
    
    sprintf(szInfoBuf, "%s RelativeTime[%d]AbsTime[%d]DevIP[%s]Port[%d]Channel[%d]CardID[%d]PowerLoss[%d]BadBlocks[%d]HealthState[%d]ResidualLife[%0.1f%]", szLan, \
        struStorageDet.dwRelativeTime, struStorageDet.dwAbsTime, struStorageDet.struDevInfo.struDevIP.sIpV4, struStorageDet.struDevInfo.wPort, \
        struStorageDet.struDevInfo.byChannel, struStorageDet.dwCardID, struStorageDet.wAbnormalPowerLoss, struStorageDet.wBadBlocks, struStorageDet.byHealthState,struStorageDet.fResidualLife * 100);
    AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
}

void CClientDemoDlg::ProcMVMRegisterInfo(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };

    char szLan[128] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    NET_DVR_MVMRegisterInfo struMVMRegisterInfo = { 0 };
    memcpy(&struMVMRegisterInfo, pAlarmInfo, sizeof(NET_DVR_MVMRegisterInfo));

    g_StringLanType(szLan, "地磁管理器注册信息", "MVM Register Info");

    sprintf(szInfoBuf, "%s DetectorID[%s]ManagerID[%s]Sim[%s]LocalIP[0x%x]LocalIPMask[0x%x]LocalGateway[0x%x]DstIP[0x%x]LocalPort[%d]Firmware[%d-%d-%d]Version[%d.%d]", szLan, \
        struMVMRegisterInfo.sDetectorID, struMVMRegisterInfo.sManagerID, struMVMRegisterInfo.sSim, struMVMRegisterInfo.dwLocalIP, struMVMRegisterInfo.dwLocalIPMask, \
        struMVMRegisterInfo.dwLocalGateway, struMVMRegisterInfo.dwDstIP, struMVMRegisterInfo.wLocalPort, struMVMRegisterInfo.wFirmwareYear, struMVMRegisterInfo.byFirmwareMonth, \
        struMVMRegisterInfo.byFirmwareDay, struMVMRegisterInfo.byMajorVersion, struMVMRegisterInfo.byMinorVersion);
    sprintf(szInfoBuf, "%sMACAddr[", szInfoBuf);
    for (int i = 0; i < 6; i++)
    {
        sprintf(szInfoBuf, "%s%x", szInfoBuf, struMVMRegisterInfo.byMACAddr[i]);
    }
    sprintf(szInfoBuf, "%s]", szInfoBuf);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcMVMStatusInfo(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };

    char szLan[128] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    NET_DVR_SingleMagneticStatus struMagneticStatus = { 0 };
    memcpy(&struMagneticStatus, pAlarmInfo, sizeof(NET_DVR_SingleMagneticStatus));

    g_StringLanType(szLan, "地磁管理器状态上报", "Magnetic Status Info");

    sprintf(szInfoBuf, "%s DetectorID[%s]ManagerID[%s]ParkNum[%s]DetectorTime[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d]Rssi[%d]ParkinglotState[%d]BatteryState[%d]DeviceState[%d]CMD[%d]", szLan, \
        struMagneticStatus.sDetectorID, struMagneticStatus.sManagerID, struMagneticStatus.sParkNum, struMagneticStatus.struDetectorTime.wYear, struMagneticStatus.struDetectorTime.byMonth, \
        struMagneticStatus.struDetectorTime.byDay, struMagneticStatus.struDetectorTime.byHour, struMagneticStatus.struDetectorTime.byMinute, struMagneticStatus.struDetectorTime.bySecond, struMagneticStatus.struDetectorTime.wMilliSec, \
        struMagneticStatus.dwRssi, struMagneticStatus.byParkinglotState, struMagneticStatus.byBatteryState, struMagneticStatus.byDeviceState, struMagneticStatus.byCMD);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcShipsDetAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "船只检测报警上传", "Ship detection alarm ");
    NET_DVR_SHIPSDETECTION_ALARM  struShipsDetection;
    memset(&struShipsDetection, 0, sizeof(struShipsDetection));
    memcpy(&struShipsDetection, pAlarmInfo, sizeof(struShipsDetection));
    LPNET_DVR_SHIPSDETECTION_ALARM pShipsDetection = (LPNET_DVR_SHIPSDETECTION_ALARM)(pAlarmInfo);

    sprintf(szInfoBuf, "flag[%d] [%2.2d%2.2d]%s: IPv4[%s] IPv6[%s] Port[%d] Channel[%d] IvmsChannel[%d]  IvmsChannelEx[%d] RelativeTime[%d] AbsTime[%d] ShipsNum[%d] ShipsNumHead[%d] ShipsNumEnd[%d]", \
        struShipsDetection.byTimeDiffFlag, struShipsDetection.cTimeDifferenceH, struShipsDetection.cTimeDifferenceM, \
        szLan, struShipsDetection.struDevInfo.struDevIP.sIpV4, struShipsDetection.struDevInfo.struDevIP.byIPv6, struShipsDetection.struDevInfo.wPort, \
        struShipsDetection.struDevInfo.byChannel, struShipsDetection.struDevInfo.byIvmsChannel, struShipsDetection.wDevInfoIvmsChannelEx,\
        struShipsDetection.dwRelativeTime, struShipsDetection.dwAbsTime, \
        struShipsDetection.byShipsNum, struShipsDetection.byShipsNumHead, struShipsDetection.byShipsNumEnd);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    for (int i = 0; i < struShipsDetection.byShipsNum; i++)
    {
        sprintf(szInfoBuf, "%s: shipsNum[%d] TriggerLineID[%d] ShipsLength[%0.1f] ShipsHeight[%0.1f] ShipsWidth[%0.1f] ShipsSpeed[%0.1f] ShipsDirection[%d] ShipsDetState[%d]", \
            szLan, i + 1, struShipsDetection.struShipInfo[i].byTriggerLineID, struShipsDetection.struShipInfo[i].fShipsLength, struShipsDetection.struShipInfo[i].fShipsHeight, struShipsDetection.struShipInfo[i].fShipsWidth, \
            struShipsDetection.struShipInfo[i].fShipsSpeed, struShipsDetection.struShipInfo[i].byShipsDirection, struShipsDetection.struShipInfo[i].byShipsDetState);
    }
	shipsDetectionToTxt(pShipsDetection, iDeviceIndex);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);


    if (struShipsDetection.dwPicLen > 0 && struShipsDetection.pPicBuffer != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "VisibleLight");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struShipsDetection.pPicBuffer, struShipsDetection.dwPicLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struShipsDetection.dwPicLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Plate Picture Wtite to File Fail.System Error:%d, dwPlateBufferLen:%d, dwWrittenBytes:%d ", dwError, struShipsDetection.dwPicLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }
    if (struShipsDetection.dwThermalPicLen > 0 && struShipsDetection.pThermalPicBuffer != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "ThermalImaging");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struShipsDetection.pThermalPicBuffer, struShipsDetection.dwThermalPicLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struShipsDetection.dwThermalPicLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "PilotFace Picture Wtite to File Fail.System Error:%d, dwPilotFaceBufferLen:%d, dwWrittenBytes:%d ", dwError, struShipsDetection.dwThermalPicLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    //释放图片内存
    if (struShipsDetection.pPicBuffer != NULL)
    {
        delete[](struShipsDetection.pPicBuffer);
        struShipsDetection.pPicBuffer = NULL;
    }
    //释放图片内存
    if (struShipsDetection.pThermalPicBuffer != NULL)
    {
        delete[](struShipsDetection.pThermalPicBuffer);
        struShipsDetection.pThermalPicBuffer = NULL;
    }
}
void CClientDemoDlg::shipsDetectionToTxt(LPNET_DVR_SHIPSDETECTION_ALARM pShipsDetection, int iDeviceIndex)
{
    if (NULL == pShipsDetection)
    {
        return;
    }

    int i = 0;
    int j = 0;
    char sInfo[5120] = { 0 };

    // NET_DVR_SHIPSDETECTION_ALARM
    sprintf(sInfo, "NET_DVR_SHIPSDETECTION_ALARM \r\n");
    sprintf(sInfo, "%s dwRelativeTime=%d \r\n", sInfo, pShipsDetection->dwRelativeTime);
    sprintf(sInfo, "%s dwAbsTime=%d \r\n", sInfo, pShipsDetection->dwAbsTime);
    sprintf(sInfo, "%s byShipsNum=%d \r\n", sInfo, pShipsDetection->byShipsNum);
	sprintf(sInfo, "%s byShipsNumHead=%d \r\n", sInfo, pShipsDetection->byShipsNumHead);
	sprintf(sInfo, "%s byShipsNumEnd=%d \r\n", sInfo, pShipsDetection->byShipsNumEnd);
    sprintf(sInfo, "%s dwPicLen=%d \r\n", sInfo, pShipsDetection->dwPicLen);
    sprintf(sInfo, "%s dwThermalPicLen=%d \r\n", sInfo, pShipsDetection->dwThermalPicLen);


    //NET_VCA_DEV_INFO
    sprintf(sInfo, "%s NET_VCA_DEV_INFO \r\n", sInfo);
    sprintf(sInfo, "%s wPort=%d \r\n", sInfo, pShipsDetection->struDevInfo.wPort);
    sprintf(sInfo, "%s byChannel=%d \r\n", sInfo, pShipsDetection->struDevInfo.byChannel);
    sprintf(sInfo, "%s byIvmsChannel=%d \r\n", sInfo, pShipsDetection->struDevInfo.byIvmsChannel);

    //NET_DVR_IPADDR
    sprintf(sInfo, "%s NET_DVR_IPADDR \r\n", sInfo);
    sprintf(sInfo, "%s sIpV4=%s \r\n", sInfo, pShipsDetection->struDevInfo.struDevIP.sIpV4);
    sprintf(sInfo, "%s byIPv6=%s \r\n", sInfo, pShipsDetection->struDevInfo.struDevIP.byIPv6);


    //NET_DVR_SHIPSINFO  
    for (i = 0; i < MAX_SHIPS_NUM; i++)
    {
        sprintf(sInfo, "%s NET_DVR_SHIPSINFO Ships Number[%d] \r\n", sInfo, i);
        sprintf(sInfo, "%s fShipsLength=%0.1f \r\n", sInfo, pShipsDetection->struShipInfo[i].fShipsLength);
        sprintf(sInfo, "%s fShipsHeight=%0.1f \r\n", sInfo, pShipsDetection->struShipInfo[i].fShipsHeight);
        sprintf(sInfo, "%s fShipsWidth=%0.1f \r\n", sInfo, pShipsDetection->struShipInfo[i].fShipsWidth);
        sprintf(sInfo, "%s fShipsSpeed=%0.1f \r\n", sInfo, pShipsDetection->struShipInfo[i].fShipsSpeed);
        sprintf(sInfo, "%s byShipsDirection=%d \r\n", sInfo, pShipsDetection->struShipInfo[i].byShipsDirection);
		sprintf(sInfo, "%s byShipsDetState=%d \r\n", sInfo, pShipsDetection->struShipInfo[i].byShipsDetState);
        //NET_VCA_POLYGON 
        sprintf(sInfo, "%s NET_VCA_POLYGON dwPointNum=%d \r\n", sInfo, pShipsDetection->struShipInfo[i].struShipsRect.dwPointNum);
		if (pShipsDetection->struShipInfo[i].struShipsRect.dwPointNum > 0 && pShipsDetection->struShipInfo[i].struShipsRect.dwPointNum <= VCA_MAX_POLYGON_POINT_NUM)
		{
			for (j = 0; j < pShipsDetection->struShipInfo[i].struShipsRect.dwPointNum; j++)
			{
				// NET_VCA_POINT
				sprintf(sInfo, "%s NET_VCA_POINT fX=%0.3f \r\n", sInfo, pShipsDetection->struShipInfo[i].struShipsRect.struPos[j].fX);
				sprintf(sInfo, "%s NET_VCA_POINT fY=%0.3f \r\n", sInfo, pShipsDetection->struShipInfo[i].struShipsRect.struPos[j].fY);
			}
		}
        sprintf(sInfo, "%s TriggerLineID=%d \r\n", sInfo, pShipsDetection->struShipInfo[i].byTriggerLineID);
    }

    char cFilename[256] = { 0 };
    sprintf(cFilename, "");


    HANDLE hFile = NULL;
    DWORD dwReturn = 0;

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chLocalTime[128];
    sprintf(chLocalTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

   // sprintf(cFilename, "%s\\LocalTime[%s].txt", cFilename, chLocalTime);
	sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "ShipsInfo");
	if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
	{
		CreateDirectory(cFilename, NULL);
	}

	sprintf(cFilename, "%s\\LocalTime[%s]_%d.txt", cFilename, chLocalTime, rand() % GetTickCount());

    hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return;
    }

    WriteFile(hFile, sInfo, 5120, &dwReturn, NULL);
    CloseHandle(hFile);
    hFile = NULL;

    UpdateData(FALSE);
}

void CClientDemoDlg::ProThermometryAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[2048] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "温度报警上传", "Thermometry Alarm");
    NET_DVR_THERMOMETRY_ALARM  struThermometryAlarm;
    memset(&struThermometryAlarm, 0, sizeof(struThermometryAlarm));
    memcpy(&struThermometryAlarm, pAlarmInfo, sizeof(struThermometryAlarm));

    if (0 == struThermometryAlarm.byRuleCalibType)
    {
        sprintf(szInfoBuf, "%s: Channel:%d, RuleID:%d,TemperatureSuddenChangeCycle:%d; TemperatureSuddenChangeValue:%f;  ToleranceTemperature:%f, AlertFilteringTime:%d, AlarmFilteringTime:%d,ThermometryUnit:%d, PresetNo:%d, RuleTemperature:%.1f, CurrTemperature:%.1f, PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], AlarmLevel:%d, \
                                                                  AlarmType:%d, AlarmRule:%d, RuleCalibType:%d,  Point[x:%f, y:%f], PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d", szLan, \
                                                                  struThermometryAlarm.dwChannel, struThermometryAlarm.byRuleID, struThermometryAlarm.dwTemperatureSuddenChangeCycle, struThermometryAlarm.fTemperatureSuddenChangeValue, struThermometryAlarm.fToleranceTemperature, struThermometryAlarm.dwAlertFilteringTime, struThermometryAlarm.dwAlarmFilteringTime, struThermometryAlarm.byThermometryUnit, struThermometryAlarm.wPresetNo, \
                                                                  struThermometryAlarm.fRuleTemperature, struThermometryAlarm.fCurrTemperature, \
                                                                  struThermometryAlarm.struPtzInfo.fPan, struThermometryAlarm.struPtzInfo.fTilt, struThermometryAlarm.struPtzInfo.fZoom, \
                                                                  struThermometryAlarm.byAlarmLevel, struThermometryAlarm.byAlarmType, struThermometryAlarm.byAlarmRule, struThermometryAlarm.byRuleCalibType, \
                                                                  struThermometryAlarm.struPoint.fX, struThermometryAlarm.struPoint.fY, struThermometryAlarm.dwPicLen, struThermometryAlarm.dwThermalPicLen, struThermometryAlarm.dwThermalInfoLen);
        AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    }
    else if (1 == struThermometryAlarm.byRuleCalibType || 2 == struThermometryAlarm.byRuleCalibType)
    {
        char szRegionInfo[512] = { 0 };
        int iPointNum = struThermometryAlarm.struRegion.dwPointNum;
        for (int i = 0; i < iPointNum; i++)
        {
            float fX = struThermometryAlarm.struRegion.struPos[i].fX;
            float fY = struThermometryAlarm.struRegion.struPos[i].fY;
            sprintf(szRegionInfo, "%sX%d:%f,Y%d:%f;", szRegionInfo, iPointNum + 1, fX, iPointNum + 1, fY);
        }

        sprintf(szInfoBuf, "%s: Channel:%d, RuleID:%d,TemperatureSuddenChangeCycle:%d; TemperatureSuddenChangeValue:%f; ToleranceTemperature:%f, AlertFilteringTime:%d, AlarmFilteringTime:%d,HighestPoint[x:%f, y:%f],ThermometryUnit:%d, PresetNo:%d, RuleTemperature:%.1f, CurrTemperature:%.1f, PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], AlarmLevel:%d, \
                                                                  AlarmType:%d, AlarmRule:%d, RuleCalibType:%d,  Region[%s], PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d", szLan, \
                                                                  struThermometryAlarm.dwChannel, struThermometryAlarm.byRuleID, struThermometryAlarm.dwTemperatureSuddenChangeCycle, struThermometryAlarm.fTemperatureSuddenChangeValue, struThermometryAlarm.fToleranceTemperature, struThermometryAlarm.dwAlertFilteringTime, struThermometryAlarm.dwAlarmFilteringTime, struThermometryAlarm.struHighestPoint.fX, struThermometryAlarm.struHighestPoint.fY, struThermometryAlarm.byThermometryUnit, struThermometryAlarm.wPresetNo, \
                                                                  struThermometryAlarm.fRuleTemperature, struThermometryAlarm.fCurrTemperature, struThermometryAlarm.struPtzInfo.fPan, struThermometryAlarm.struPtzInfo.fTilt, struThermometryAlarm.struPtzInfo.fZoom, \
                                                                  struThermometryAlarm.byAlarmLevel, struThermometryAlarm.byAlarmType, struThermometryAlarm.byAlarmRule, struThermometryAlarm.byRuleCalibType, \
                                                                  szRegionInfo, struThermometryAlarm.dwPicLen, struThermometryAlarm.dwThermalPicLen, struThermometryAlarm.dwThermalInfoLen);
        AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    }

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    if (struThermometryAlarm.dwPicLen > 0 && struThermometryAlarm.pPicBuff != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[Thermometry]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\Pic[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struThermometryAlarm.pPicBuff, struThermometryAlarm.dwPicLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struThermometryAlarm.dwPicLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Thermometry Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struThermometryAlarm.dwPicLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struThermometryAlarm.dwThermalPicLen > 0 && struThermometryAlarm.pThermalPicBuff != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[Thermometry]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\ThermalPic[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struThermometryAlarm.pThermalPicBuff, struThermometryAlarm.dwThermalPicLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struThermometryAlarm.dwThermalPicLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Thermometry Thermal Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struThermometryAlarm.dwThermalPicLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struThermometryAlarm.dwThermalInfoLen > 0 && struThermometryAlarm.pThermalInfoBuff != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[Thermometry]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\ThermalInfo[%s]_%d.txt", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struThermometryAlarm.pThermalInfoBuff, struThermometryAlarm.dwThermalInfoLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struThermometryAlarm.dwThermalInfoLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Thermometry Thermal Info Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struThermometryAlarm.dwThermalInfoLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struThermometryAlarm.pPicBuff != NULL)
    {
        delete[](struThermometryAlarm.pPicBuff);
        struThermometryAlarm.pPicBuff = NULL;
    }

    if (struThermometryAlarm.pThermalPicBuff != NULL)
    {
        delete[](struThermometryAlarm.pThermalPicBuff);
        struThermometryAlarm.pThermalPicBuff = NULL;
    }

    if (struThermometryAlarm.pThermalInfoBuff != NULL)
    {
        delete[](struThermometryAlarm.pThermalInfoBuff);
        struThermometryAlarm.pThermalInfoBuff = NULL;
    }
}

void CClientDemoDlg::ProBaseStationInfoAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[2048] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "基站信息上传", "BaseStationInfo Alarm");
    NET_DVR_BASE_STATION_INFO_ALARM  struBaseStationInfoAlarm;
    memset(&struBaseStationInfoAlarm, 0, sizeof(struBaseStationInfoAlarm));
    memcpy(&struBaseStationInfoAlarm, pAlarmInfo, sizeof(struBaseStationInfoAlarm));


    sprintf(szInfoBuf, "%s: Channel[%d] NetBarWaCode[%s] CollectionEquipmentID[%s] MCC[%s] MNC[%s] LAC[%s] CI[%s] BSCI[%s] BCCH[%s] LEV[%s] CollectionEquipmentLongitude[%s] CollectionEquipmentLatitude[%s] CaptureTime[%s]", szLan, \
        struBaseStationInfoAlarm.dwChannel, struBaseStationInfoAlarm.sNetBarWaCode, struBaseStationInfoAlarm.sCollectionEquipmentID, struBaseStationInfoAlarm.sMCC, struBaseStationInfoAlarm.sMNC, struBaseStationInfoAlarm.sLAC, struBaseStationInfoAlarm.sCI, \
        struBaseStationInfoAlarm.sBSCI, struBaseStationInfoAlarm.sBCCH, struBaseStationInfoAlarm.sLEV, struBaseStationInfoAlarm.sCollectionEquipmentLongitude, struBaseStationInfoAlarm.sCollectionEquipmentLatitude, struBaseStationInfoAlarm.sCaptureTime);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

}



void CClientDemoDlg::ProThermometryDiffAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[2048] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "温差报警上传", "Thermometry Difference Alarm");
    NET_DVR_THERMOMETRY_DIFF_ALARM  struThermometryAlarm;
    memset(&struThermometryAlarm, 0, sizeof(struThermometryAlarm));
    memcpy(&struThermometryAlarm, pAlarmInfo, sizeof(struThermometryAlarm));

    if (0 == struThermometryAlarm.byRuleCalibType)
    {
        sprintf(szInfoBuf, "%s: Channel:%d, AlarmID1:%d, ToleranceTemperature:%f, AlarmFilteringTime:%d,AlarmID2:%d, PresetNo:%d, RuleTemperatureDiff:%.1f, CurTemperatureDiff:%.1f, \
                AlarmLevel:%d, AlarmType:%d, AlarmRule:%d, RuleCalibType:%d,  \
                Point1[x:%f, y:%f], point2[x:%f, y:%f], PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], PicLen:%d, \
                ThermalPicLen:%d, ThermalInfoLen:%d, ThermometryUnit:%d", szLan, \
                struThermometryAlarm.dwChannel, struThermometryAlarm.byAlarmID1, struThermometryAlarm.fToleranceTemperature, struThermometryAlarm.dwAlarmFilteringTime, struThermometryAlarm.byAlarmID2, struThermometryAlarm.wPresetNo, \
                struThermometryAlarm.fRuleTemperatureDiff, struThermometryAlarm.fCurTemperatureDiff, \
                struThermometryAlarm.byAlarmLevel, struThermometryAlarm.byAlarmType, struThermometryAlarm.byAlarmRule, struThermometryAlarm.byRuleCalibType, \
                struThermometryAlarm.struPoint[0].fX, struThermometryAlarm.struPoint[0].fY, struThermometryAlarm.struPoint[1].fX, struThermometryAlarm.struPoint[1].fY, \
                struThermometryAlarm.struPtzInfo.fPan, struThermometryAlarm.struPtzInfo.fTilt, struThermometryAlarm.struPtzInfo.fZoom, \
                struThermometryAlarm.dwPicLen, struThermometryAlarm.dwThermalPicLen, struThermometryAlarm.dwThermalInfoLen, struThermometryAlarm.byThermometryUnit);
        AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    }
    else if (1 == struThermometryAlarm.byRuleCalibType || 2 == struThermometryAlarm.byRuleCalibType)
    {
        int i = 0;
        char szRegionInfo[512] = { 0 };
        int iPointNum = struThermometryAlarm.struRegion[0].dwPointNum;
        for (i = 0; i < iPointNum; i++)
        {
            float fX = struThermometryAlarm.struRegion[0].struPos[i].fX;
            float fY = struThermometryAlarm.struRegion[0].struPos[i].fY;
            sprintf(szRegionInfo, "%sX%d:%f,Y%d:%f;", szRegionInfo, iPointNum + 1, fX, iPointNum + 1, fY);
        }

        char szRegionInfo1[512] = { 0 };
        iPointNum = struThermometryAlarm.struRegion[1].dwPointNum;
        for (i = 0; i < iPointNum; i++)
        {
            float fX = struThermometryAlarm.struRegion[1].struPos[i].fX;
            float fY = struThermometryAlarm.struRegion[1].struPos[i].fY;
            sprintf(szRegionInfo1, "%sX%d:%f,Y%d:%f;", szRegionInfo1, iPointNum + 1, fX, iPointNum + 1, fY);
        }

        sprintf(szInfoBuf, "%s: Channel:%d, AlarmID1:%d, AlarmID2:%d,   ToleranceTemperature:%f, AlarmFilteringTime:%d,PresetNo:%d, RuleTemperatureDiff:%.1f, CurTemperatureDiff:%.1f, AlarmLevel:%d, AlarmType:%d, AlarmRule:%d, RuleCalibType:%d,  \
                                                       Region1[%s], Region2[%s], PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d, ThermometryUnit:%d", szLan, \
                                                       struThermometryAlarm.dwChannel, struThermometryAlarm.byAlarmID1, struThermometryAlarm.byAlarmID2, struThermometryAlarm.fToleranceTemperature, struThermometryAlarm.dwAlarmFilteringTime, struThermometryAlarm.wPresetNo, \
                                                       struThermometryAlarm.fRuleTemperatureDiff, struThermometryAlarm.fCurTemperatureDiff, \
                                                       struThermometryAlarm.byAlarmLevel, struThermometryAlarm.byAlarmType, struThermometryAlarm.byAlarmRule, struThermometryAlarm.byRuleCalibType, \
                                                       szRegionInfo, szRegionInfo1, \
                                                       struThermometryAlarm.struPtzInfo.fPan, struThermometryAlarm.struPtzInfo.fTilt, struThermometryAlarm.struPtzInfo.fZoom, \
                                                       struThermometryAlarm.dwPicLen, struThermometryAlarm.dwThermalPicLen, struThermometryAlarm.dwThermalInfoLen, struThermometryAlarm.byThermometryUnit);
        AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
    }



    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
    if (struThermometryAlarm.dwPicLen > 0 && struThermometryAlarm.pPicBuff != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[ThermometryDiff]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struThermometryAlarm.pPicBuff, struThermometryAlarm.dwPicLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struThermometryAlarm.dwPicLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Thermometry Difference Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struThermometryAlarm.dwPicLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struThermometryAlarm.dwThermalPicLen > 0 && struThermometryAlarm.pThermalPicBuff != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[ThermometryDiff]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\ThermalPic[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struThermometryAlarm.pThermalPicBuff, struThermometryAlarm.dwThermalPicLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struThermometryAlarm.dwThermalPicLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Thermometry Difference Thermal Picture Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struThermometryAlarm.dwThermalPicLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struThermometryAlarm.dwThermalInfoLen > 0 && struThermometryAlarm.pThermalInfoBuff != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP, "[ThermometryDiff]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\ThermalInfo[%s]_%d.txt", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struThermometryAlarm.pThermalInfoBuff, struThermometryAlarm.dwThermalInfoLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struThermometryAlarm.dwThermalInfoLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Thermometry Difference Thermal Info Wtite to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, struThermometryAlarm.dwThermalInfoLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    if (struThermometryAlarm.pPicBuff != NULL)
    {
        delete[](struThermometryAlarm.pPicBuff);
        struThermometryAlarm.pPicBuff = NULL;
    }

    if (struThermometryAlarm.pThermalPicBuff != NULL)
    {
        delete[](struThermometryAlarm.pThermalPicBuff);
        struThermometryAlarm.pThermalPicBuff = NULL;
    }

    if (struThermometryAlarm.pThermalInfoBuff != NULL)
    {
        delete[](struThermometryAlarm.pThermalInfoBuff);
        struThermometryAlarm.pThermalInfoBuff = NULL;
    }
}

void CClientDemoDlg::ProDiagnosisUpload(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = { 0 };
	char szTime[128] = { 0 };
	char szLan[128] = { 0 };
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	NET_DVR_DIAGNOSIS_UPLOAD struDiagnosisUpload = { 0 };
	memcpy(&struDiagnosisUpload, pAlarmInfo, sizeof(NET_DVR_DIAGNOSIS_UPLOAD));

	g_StringLanType(szLan, "诊断服务器结果信息上传", "Diagnosis Upload");

	sprintf(szTime, "%d-%d-%d %d:%d:%d", struDiagnosisUpload.struCheckTime.dwYear, struDiagnosisUpload.struCheckTime.dwMonth, struDiagnosisUpload.struCheckTime.dwDay,
		struDiagnosisUpload.struCheckTime.dwHour, struDiagnosisUpload.struCheckTime.dwMinute, struDiagnosisUpload.struCheckTime.dwSecond);

	sprintf(szInfoBuf, "%s StreamID[%s]MonitorIP[%s]ChanIndex[%d]Width[%d]Height[%d]CheckTime[%s]Result[%d]", szLan, \
		struDiagnosisUpload.sStreamID, struDiagnosisUpload.sMonitorIP, struDiagnosisUpload.dwChanIndex, struDiagnosisUpload.dwWidth, \
		struDiagnosisUpload.dwHeight, szTime, struDiagnosisUpload.byResult);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

	sprintf(szInfoBuf, "%s SignalResult[%d]BlurResult[%d]LumaResult[%d]ChromaResult[%d]SnowResult[%d]StreakResult[%d]FreezeResult[%d]PTZResult[%d]NapShotURL[%s]", szLan, \
		struDiagnosisUpload.bySignalResult, struDiagnosisUpload.byBlurResult, struDiagnosisUpload.byLumaResult, struDiagnosisUpload.byChromaResult, \
		struDiagnosisUpload.bySnowResult, struDiagnosisUpload.byStreakResult, struDiagnosisUpload.byFreezeResult, struDiagnosisUpload.byPTZResult, struDiagnosisUpload.sSNapShotURL);
	AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcessWallConferenceAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    char szTime[128] = { 0 };
    char szLan[128] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    char *pAlarmInfo = (char *)(lParam);
    DWORD dwLen = *(DWORD*)pAlarmInfo;

    CFile file;
    if (!file.Open("C:\\WallConferenceInfo.txt", CFile::modeWrite))
    {
        return;
    }
    file.SeekToEnd();
    file.Write(pAlarmInfo + sizeof(DWORD), dwLen);
    file.Close();

    g_StringLanType(szLan, "开会的会议信息告警", "Wall Conference Alarm");

    CTime time(NULL);
    sprintf(szTime, "%d-%d-%d %d:%d:%d", time.GetYear(), time.GetMonth(), time.GetDay(),
        time.GetHour(), time.GetMinute(), time.GetSecond());

    sprintf(szInfoBuf, "%s DeviceIndex[%d] Alarm Time[%s]", szLan, iDeviceIndex, szTime);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProGPSStatusUpload(WPARAM wParam, LPARAM lParam)
{
    char szLan[256] = { 0 };
    char szLocateMode[64] = { 0 };
    char szGPSTime[128] = { 0 };
    char szInfoBuf[1024] = { 0 };
    char szDegree[128] = { 0 };
    char szUploadBuf[1024] = { 0 };
    char szRetransFlag[32] = { 0 };
    char szNeedsResponse[32] = { 0 };
    char szType[32] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    LPNET_DVR_GPS_STATUS_ALARM pStruGPSStatusAlarm = (LPNET_DVR_GPS_STATUS_ALARM)pAlarmInfo;

    g_StringLanType(szLan, "GPS状态上传", "GPS Status Upload");

    sprintf(szGPSTime, "%d-%d-%d %d:%d:%d", pStruGPSStatusAlarm->struGPSTime.wYear,
        pStruGPSStatusAlarm->struGPSTime.byMonth, pStruGPSStatusAlarm->struGPSTime.byDay,
        pStruGPSStatusAlarm->struGPSTime.byHour, pStruGPSStatusAlarm->struGPSTime.byMinute,
        pStruGPSStatusAlarm->struGPSTime.bySecond);

    if (pStruGPSStatusAlarm->struGPSInfo.byDirection[0] == 0)
    {
        if (pStruGPSStatusAlarm->struGPSInfo.byDirection[1] == 0)
        {
            sprintf(szDegree, "%s %d %s %d", "East longitude", pStruGPSStatusAlarm->struGPSInfo.dwLatitude, "North latitude", pStruGPSStatusAlarm->struGPSInfo.dwLongitude);
        }
        if (pStruGPSStatusAlarm->struGPSInfo.byDirection[1] == 1)
        {
            sprintf(szDegree, "%s %d %s %d", "East longitude", pStruGPSStatusAlarm->struGPSInfo.dwLatitude, "South latitude", pStruGPSStatusAlarm->struGPSInfo.dwLongitude);
        }
    }
    else if (pStruGPSStatusAlarm->struGPSInfo.byDirection[0] == 1)
    {
        if (pStruGPSStatusAlarm->struGPSInfo.byDirection[1] == 0)
        {
            sprintf(szDegree, "%s %d %s %d", "West longitude", pStruGPSStatusAlarm->struGPSInfo.dwLatitude, "North latitude", pStruGPSStatusAlarm->struGPSInfo.dwLongitude);
        }
        if (pStruGPSStatusAlarm->struGPSInfo.byDirection[1] == 1)
        {
            sprintf(szDegree, "%s %d %s %d", "West longitude", pStruGPSStatusAlarm->struGPSInfo.dwLatitude, "South latitude", pStruGPSStatusAlarm->struGPSInfo.dwLongitude);
        }
    }

    switch (pStruGPSStatusAlarm->struGPSInfo.byLocateMode)
    {
    case 0:
        g_StringLanType(szLocateMode, "自主定位", "self-localization");
        break;
    case 1:
        g_StringLanType(szLocateMode, "差分", "difference");
        break;
    case 2:
        g_StringLanType(szLocateMode, "估算", "estimate");
        break;
    case 3:
        g_StringLanType(szLocateMode, "数据无效", "data is invalid");
        break;
    default:
        break;
    }

    switch (pStruGPSStatusAlarm->byRetransFlag)
    {
    case 0:
        g_StringLanType(szRetransFlag, "本条 GPS 为实时包", "GPS real-time package");
        break;
    case 1:
        g_StringLanType(szRetransFlag, "本条 GPS 为重传包", "GPS retransmission package ");
        break;
    default:
        break;
    }

    switch (pStruGPSStatusAlarm->byNeedsResponse)
    {
    case 0:
        g_StringLanType(szNeedsResponse, "不需回应包", "no need respond package");
        break;
    case 1:
        g_StringLanType(szNeedsResponse, "需回应包", "need respond package");
        break;
    default:
        break;
    }

    switch (pStruGPSStatusAlarm->byType)
    {
    case 0:
        g_StringLanType(szType, "无人机", "Unmanned aerial vehicle");
        break;
    default:
        break;
    }

    sprintf(szInfoBuf, "%s: (GPS Time:[%s]  GPS Direction:[%s]  GPS LocateMode:[%s]  HDOP:[%d]  Height:[%d]  Vehicle Speed:[%d]  Vehicle Direction:[%d])\n",
        szLan, szGPSTime, szDegree, szLocateMode, pStruGPSStatusAlarm->struGPSInfo.wHDOP, pStruGPSStatusAlarm->struGPSInfo.wHeight,
        pStruGPSStatusAlarm->struGPSInfo.dwVehicleSpeed, pStruGPSStatusAlarm->struGPSInfo.dwVehicleDirection);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

    sprintf(szUploadBuf, "%s: (RetransFlag:[%s] NeedsResponse:[%s] Type:[%s] BatteryRemaining:[%d] RollAngle:[%d] PitchAngle:[%d] RelativeHeight:[%d] VerticalSpeed:[%d])\n",
        szLan, szRetransFlag, szNeedsResponse, szType, pStruGPSStatusAlarm->byBatteryRemaining, pStruGPSStatusAlarm->iRollAngle,
        pStruGPSStatusAlarm->iPitchAngle, pStruGPSStatusAlarm->wRelativeHeight, pStruGPSStatusAlarm->wVerticalSpeed);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szUploadBuf);
}

void CClientDemoDlg::ProTagInfoUpload(WPARAM wParam, LPARAM lParam)
{
    char szLan[256] = { 0 };
    char szInfoBuf[1024] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int i = 0;
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    LPNET_DVR_TAG_INFO_ALARM pStruTagInfoAlarm = (LPNET_DVR_TAG_INFO_ALARM)pAlarmInfo;

    g_StringLanType(szLan, "标签信息上传", "Tag Information Upload");

    char szRfidInfo[180] = { 0 };
    for (int index = 0; index < sizeof(pStruTagInfoAlarm->byRFIDInfo); ++index)
    {
        sprintf(szRfidInfo, "%s0x%02x ", szRfidInfo, pStruTagInfoAlarm->byRFIDInfo[index]);
    }
    
    sprintf(szInfoBuf, "%s Card No:[%s],Rssi:[%d],byIndexCode[%s],AcquisitionTime[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d],RFIDInfo[%s],RFIDInfoLen[%d],byVoltageLow[%d],byAlarmFlag[%d]\n", 
        szLan, 
        pStruTagInfoAlarm->byCardNo, 
        pStruTagInfoAlarm->iRssi,
        pStruTagInfoAlarm->byIndexCode,
        pStruTagInfoAlarm->struAcquisitionTime.wYear,
        pStruTagInfoAlarm->struAcquisitionTime.byMonth,
        pStruTagInfoAlarm->struAcquisitionTime.byDay,
        pStruTagInfoAlarm->struAcquisitionTime.byHour,
        pStruTagInfoAlarm->struAcquisitionTime.byMinute,
        pStruTagInfoAlarm->struAcquisitionTime.bySecond,
        pStruTagInfoAlarm->struAcquisitionTime.wMilliSec,
        szRfidInfo,
        pStruTagInfoAlarm->byRFIDInfoLen,
        pStruTagInfoAlarm->byVoltageLow,
        pStruTagInfoAlarm->byAlarmFlag);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcessInquestAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    char szStatus[256] = { 0 };
    char szAlarmType[128] = { 0 };
    char szLan[128] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    NET_DVR_INQUEST_ALARM struTrayAbnormalAlarm = { 0 };
    memcpy(&struTrayAbnormalAlarm, pAlarmInfo, sizeof(NET_DVR_INQUEST_ALARM));

    g_StringLanType(szLan, "审讯主机报警上传", "Inquest Alarm Upload");

    switch (struTrayAbnormalAlarm.dwAlarmType)
    {
    case 0:
        g_StringLanType(szAlarmType, "光盘满报警", "Tray full");
        break;
    case 1:
        g_StringLanType(szAlarmType, "光盘错误报警", "Tray error");
        break;
    default:
        break;
    }

    sprintf(szInfoBuf, "%s: (Alarm type:[%s]  Tray No.:[%d])\n", szLan, szAlarmType, struTrayAbnormalAlarm.byTrayNo);

    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProFaceSnapRawData(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    char szLan[128] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    NET_VCA_FACESNAP_RAWDATA_ALARM struFaceSnap = { 0 };
    memcpy(&struFaceSnap, pAlarmInfo, sizeof(NET_VCA_FACESNAP_RAWDATA_ALARM));

    g_StringLanType(szLan, "人脸Json报警", "Face Json Alarm");

    sprintf(szInfoBuf, "%s: IPv4[%s] IPv6[%s] Port[%d] Channel[%d] IvmsChannel[%d] RelativeTime[%d] AbsTime[%d]", \
        szLan, struFaceSnap.struDevInfo.struDevIP.sIpV4, struFaceSnap.struDevInfo.struDevIP.byIPv6, struFaceSnap.struDevInfo.wPort, \
        struFaceSnap.struDevInfo.byChannel, struFaceSnap.struDevInfo.byIvmsChannel, struFaceSnap.dwRelativeTime, struFaceSnap.dwAbsTime);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    if (struFaceSnap.dwJsonDataLen > 0 && struFaceSnap.pJsonBuff != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\[%s]", g_struLocalParam.chPictureSavePath, "[FaceSnapJson]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\Json[%s]_%d.txt", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            delete[] struFaceSnap.pJsonBuff;
            struFaceSnap.pJsonBuff = NULL;
            return;
        }
        DWORD dwRet = WriteFile(hFile, struFaceSnap.pJsonBuff, struFaceSnap.dwJsonDataLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struFaceSnap.dwJsonDataLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Face Snap Json Info Wtite to File Fail.System Error:%d, dwJsonDataLen:%d, WrittenBytes:%d ", dwError, struFaceSnap.dwJsonDataLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
        delete[] struFaceSnap.pJsonBuff;
        struFaceSnap.pJsonBuff = NULL;
    }
}

void CClientDemoDlg::ProcNetSwitchAlarm(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "交换机端口检测报警上传", "Switch port detection");
    NET_DVR_SWITCH_CONVERT_ALARM  struSwitchAlarm = { 0 };
    memset(&struSwitchAlarm, 0, sizeof(struSwitchAlarm));
    memcpy(&struSwitchAlarm, pAlarmInfo, sizeof(struSwitchAlarm));

    sprintf(szInfoBuf, "%s Port:%d, EventType:%d, Event:%d", szLan, struSwitchAlarm.byPortNo, struSwitchAlarm.dwEventType, struSwitchAlarm.dwEvent);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcessAlarmGps(WPARAM wParam, LPARAM lParam)
{
    char szLan[256] = { 0 };
    char szLocateMode[64] = { 0 };
    char szGPSTime[512] = { 0 };
    char szInfoBuf[1024] = { 0 };
    char szDegree[128] = { 0 };

    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;

    NET_DVR_GPSALARMINFO struGPSAlarm = { 0 };
    memset(&struGPSAlarm, 0, sizeof(struGPSAlarm));
    memcpy(&struGPSAlarm, pAlarmInfo, sizeof(struGPSAlarm));

    g_StringLanType(szLan, "GPS报警信息上传", "GPS Alarm Information Upload");

    sprintf(szGPSTime, "上传时间：%d-%d-%d %d:%d:%d", struGPSAlarm.struGpsTime.wYear,
        struGPSAlarm.struGpsTime.byMonth, struGPSAlarm.struGpsTime.byDay,
        struGPSAlarm.struGpsTime.byHour, struGPSAlarm.struGpsTime.byMinute,
        struGPSAlarm.struGpsTime.bySecond);

    if (struGPSAlarm.sDirection[0] == 'E')
    {
        if (struGPSAlarm.sDirection[1] == 'N')
        {
            sprintf(szDegree, "%s %d %s %d", "East longitude", struGPSAlarm.dwLongitude, "North latitude", struGPSAlarm.dwLatitude);
        }
        if (struGPSAlarm.sDirection[1] == 'S')
        {
            sprintf(szDegree, "%s %d %s %d", "East longitude", struGPSAlarm.dwLongitude, "South latitude", struGPSAlarm.dwLatitude);
        }
    }
    else if (struGPSAlarm.sDirection[0] == 'W')
    {
        if (struGPSAlarm.sDirection[1] == 'N')
        {
            sprintf(szDegree, "%s %d %s %d", "West longitude", struGPSAlarm.dwLongitude, "North latitude", struGPSAlarm.dwLatitude);
        }
        if (struGPSAlarm.sDirection[1] == 'S')
        {
            sprintf(szDegree, "%s %d %s %d", "West longitude", struGPSAlarm.dwLongitude, "South latitude", struGPSAlarm.dwLatitude);
        }
    }

    switch (struGPSAlarm.byLocateMode)
    {
    case 0:
        g_StringLanType(szLocateMode, "自主定位", "self-localization");
        break;
    case 1:
        g_StringLanType(szLocateMode, "差分", "difference");
        break;
    case 2:
        g_StringLanType(szLocateMode, "估算", "estimate");
        break;
    case 3:
        g_StringLanType(szLocateMode, "数据无效", "data is invalid");
        break;
    default:
        break;
    }

    sprintf(szInfoBuf, "%s: DeviceID:[%s] GPS Time:[%s]  GPS Direction:[%s]  GPS LocateMode:[%s]  TimeZone:[%d]  Vehicle Direction:[%d] Satellites:[%d] Precision:[%d]\
                                                                                Height:[%d]  GPSSeq:[%d] Speed:[%d]", szLan, struGPSAlarm.byDeviceID, szGPSTime, szDegree, szLocateMode, struGPSAlarm.iTimeZone, struGPSAlarm.dwDirection,
                                                                                struGPSAlarm.wSatellites, struGPSAlarm.wPrecision, struGPSAlarm.dwHeight, struGPSAlarm.dwGPSSeq, struGPSAlarm.wSpeed);

    g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

}

void CClientDemoDlg::ProcessEventWithJsonData(WPARAM wParam, LPARAM lParam)
{
	char szLan[64] = { 0 };
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	DWORD dwBufLen = pAlarmDev->dwBufLen;

    if (!(g_struDeviceInfo[iDeviceIndex].bAlarm))
    {
        g_struDeviceInfo[iDeviceIndex].bAlarm = TRUE;
        ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_DEVICE_ITEM_IMAGE, WPARAM(g_pMainDlg->GetDeviceItem(iDeviceIndex)), LPARAM(iDeviceIndex));
    }

    char szInfoBuf[128] = { 0 };

	char* pCBBuf = new char[dwBufLen];
	if (pCBBuf == NULL)
	{
		sprintf(szLan, "内存申请失败 EventJson dwBufLen:%d", dwBufLen);
		AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
		return;
	}
	memcpy(pCBBuf, pAlarmInfo, dwBufLen);
	char *mfd = pCBBuf;
	//analysisJson(pCBBuf, g_struLocalParam.chPictureSavePath);

	char* boundary = get_boundary(pCBBuf);
	int contentLen = 0;
	int offsetLen = 0;
	int i = 0;
	while (1) {
		char *type, *content;
 		mfd = mutipart_form_data(mfd, boundary, &type, &content, (dwBufLen - offsetLen), contentLen, offsetLen);
		if (mfd == NULL) {
			break;
		}
		// show   
		//printf("name=\"%s\" content=\"%s\"\n"/*, name*/, content);

        //printf
        cJSON *root;
        root = cJSON_Parse(content);

        if (!root)
        {
            OutputDebugString("get json root failed !\n");
        }
        else
        {
            cJSON *eventType = cJSON_GetObjectItem(root, "eventType");

            if (!eventType)
            {
                OutputDebugString("get json eventType failed !\n");

                cJSON *TargetList = cJSON_GetObjectItem(root, "Target");

                if (TargetList != NULL)
                {
                    int  iCount = cJSON_GetArraySize(TargetList); /*获取数组长度*/
                    if (iCount > 0)
                    {
                        cJSON *Target = cJSON_GetArrayItem(TargetList, 0);

                        if (Target != NULL)
                        {
                            cJSON *recognitionType = cJSON_GetObjectItem(Target, "recognitionType");

                            if (recognitionType != NULL)
                            {
                                sprintf(szInfoBuf, "Json format alarm  recognitionType:[%s] Broken:[%d]", recognitionType->valuestring, g_bJSONBroken);

                                g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
                            }
                        }

                    }
                }
            }
            else
            {
                sprintf(szInfoBuf, "Json format alarm  eventType:[%s]", eventType->valuestring);

                g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
            }
        }

        if (root)
        {
            cJSON_Delete(root);
        }

		SYSTEMTIME t;
		GetLocalTime(&t);
		char chTime[128];
		sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

		char cFilename[256] = { 0 };

        sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\%s_%d.%s", cFilename, chTime, i, type);

		HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		DWORD dwWrittenBytes = 0;
		DWORD dwRet = WriteFile(hFile, content, contentLen, &dwWrittenBytes, NULL);
		if (dwRet == 0 || dwWrittenBytes < contentLen)
		{
			DWORD dwError = GetLastError();
			//g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Face Snap Json Info Wtite to File Fail.System Error:%d, dwJsonDataLen:%d, WrittenBytes:%d ", dwError, struFaceSnap.dwJsonDataLen, dwWrittenBytes);
		}
		CloseHandle(hFile);
		hFile = NULL;

		free(type);
		free(content);
		if (mfd == NULL) {
			break;
			i = 0;
		}
		i++;
	}

	if (pCBBuf != NULL)
	{
		delete[] pCBBuf;
		pCBBuf = NULL;
	}

	if (boundary != NULL)
	{
		delete[] boundary;
		boundary = NULL;
	}
}


void CClientDemoDlg::ProcessEventWithJsonDataNoBoundary(WPARAM wParam, LPARAM lParam)
{
    char szLan[64] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    DWORD dwBufLen = pAlarmDev->dwBufLen;

    //将报警内容写入文件
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    char cFilename[256] = { 0 };

    sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIP);
    if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
    {
        CreateDirectory(cFilename, NULL);
    }

    sprintf(cFilename, "%s\\%s.json", cFilename, chTime);

    HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return;
    }
    DWORD dwWrittenBytes = 0;
    DWORD dwRet = WriteFile(hFile, pAlarmInfo, pAlarmDev->dwBufLen, &dwWrittenBytes, NULL);
    if (dwRet == 0 || dwWrittenBytes < pAlarmDev->dwBufLen)
    {
        DWORD dwError = GetLastError();
        //g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Face Snap Json Info Wtite to File Fail.System Error:%d, dwJsonDataLen:%d, WrittenBytes:%d ", dwError, struFaceSnap.dwJsonDataLen, dwWrittenBytes);
    }
    CloseHandle(hFile);
    hFile = NULL;
}


void CClientDemoDlg::ProFramesPeopleCounting(WPARAM wParam, LPARAM lParam)
{
    char szInfoBuf[1024] = { 0 };
    char szLan[128] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    NET_DVR_FRAMES_PEOPLE_COUNTING struFramesPeopleCounting = { 0 };
    memcpy(&struFramesPeopleCounting, pAlarmInfo, sizeof(NET_DVR_FRAMES_PEOPLE_COUNTING));

    g_StringLanType(szLan, "定制 单帧画面人数统计", "Frames People Counting Alarm");

    sprintf(szInfoBuf, "%s: IPv4[%s] IPv6[%s] Port[%d] Channel[%d] IvmsChannel[%d] RelativeTime[%d] AbsTime[%d] PeopleCountingNum[%d]", \
        szLan, struFramesPeopleCounting.struDevInfo.struDevIP.sIpV4, struFramesPeopleCounting.struDevInfo.struDevIP.byIPv6, struFramesPeopleCounting.struDevInfo.wPort, \
        struFramesPeopleCounting.struDevInfo.byChannel, struFramesPeopleCounting.struDevInfo.byIvmsChannel, struFramesPeopleCounting.dwRelativeTime, struFramesPeopleCounting.dwAbsTime, struFramesPeopleCounting.dwPeopleCountingNum);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    if (struFramesPeopleCounting.dwPicLen > 0 && struFramesPeopleCounting.pPicBuffer != NULL)
    {
        char cFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\[%s]", g_struLocalParam.chPictureSavePath, "[FramesPeopleCounting]");
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        sprintf(cFilename, "%s\\FramesPeopleCounting[%s]_%d.txt", cFilename, chTime, rand() % GetTickCount());

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwRet = WriteFile(hFile, struFramesPeopleCounting.pPicBuffer, struFramesPeopleCounting.dwPicLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < struFramesPeopleCounting.dwPicLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Frames People Counting Info Wtite to File Fail.System Error:%d, dwJsonDataLen:%d, WrittenBytes:%d ", dwError, struFramesPeopleCounting.dwPicLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
        delete[] struFramesPeopleCounting.pPicBuffer;
        struFramesPeopleCounting.pPicBuffer = NULL;
    }
}
void CClientDemoDlg::ProcessClusterAlarm(WPARAM wParam, LPARAM lParam)
{
    char szLan[64] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    DWORD dwBufLen = pAlarmDev->dwBufLen;

    char* pCBBuf = new char[dwBufLen];
    if (pCBBuf == NULL)
    {
        sprintf(szLan, "内存申请失败 EventCluster dwBufLen:%d", dwBufLen);
        AddLog(iDeviceIndex, ALARM_INFO_T, szLan);
        return;
    }
    memcpy(pCBBuf, pAlarmInfo, dwBufLen);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    char cFilename[256] = { 0 };
    sprintf(cFilename, "%s\\%s.%s", g_struLocalParam.chPictureSavePath, chTime, "xml");

    HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return;
    }
    DWORD dwWrittenBytes = 0;
    DWORD dwRet = WriteFile(hFile, pCBBuf, dwBufLen, &dwWrittenBytes, NULL);
    if (dwRet == 0 || dwWrittenBytes < dwBufLen)
    {
        DWORD dwError = GetLastError();
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Cluster alarm Write to File Fail.System Error:%d, dwDataLen:%d, WrittenBytes:%d ", dwError, dwBufLen, dwWrittenBytes);
    }

    AddLog(iDeviceIndex, ALARM_INFO_T, "Receive Cluster Alarm.Check in saved files");

    CloseHandle(hFile);
    hFile = NULL;

    if (pCBBuf != NULL)
    {
        delete[] pCBBuf;
        pCBBuf = NULL;
    }
}

void CClientDemoDlg::ProcISAPIAlarm(WPARAM wParam, LPARAM lParam)
{
    //char szInfoBuf[1024] = { 0 };
    char szLan[128] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    NET_DVR_ALARM_ISAPI_INFO struISAPIAlarm = { 0 };
    memcpy(&struISAPIAlarm, pAlarmInfo, sizeof(NET_DVR_ALARM_ISAPI_INFO));

    g_StringLanType(szLan, "ISAPI报警上传", "ISAPI Alarm");
    AddLog(iDeviceIndex, ALARM_INFO_T, szLan);

    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

    if (struISAPIAlarm.pAlarmData != NULL)
    {
        char cFilename[256] = { 0 };
        char cExt[12] = { 0 };
        char cSubFilename[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(cFilename, "%s\\%s[%s]", g_struLocalParam.chPictureSavePath, "ISAPIAlarmData", pAlarmDev->sDeviceIP);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        memcpy(cSubFilename, cFilename, 256);

        if (struISAPIAlarm.byDataType == 2)
        {
            sprintf(cExt, "%s", "json");
        }
        else if (struISAPIAlarm.byDataType == 1)
        {
            sprintf(cExt, "%s", "xml");
        }
        else
        {
            sprintf(cExt, "%s", "txt");
        }

//         sprintf(cFilename, "%s\\ISAPI[%s]_%d.%s", cFilename, chTime, rand() % GetTickCount(), cExt);
// 
//         HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//         if (hFile == INVALID_HANDLE_VALUE)
//         {
//             return;
//         }
//         DWORD dwRet = WriteFile(hFile, struISAPIAlarm.pAlarmData, struISAPIAlarm.dwAlarmDataLen, &dwWrittenBytes, NULL);
//         if (dwRet == 0 || dwWrittenBytes < struISAPIAlarm.dwAlarmDataLen)
//         {
//             DWORD dwError = GetLastError();
//             g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Frames People Counting Info Wtite to File Fail.System Error:%d, dwJsonDataLen:%d, WrittenBytes:%d ", dwError, struISAPIAlarm.dwAlarmDataLen, dwWrittenBytes);
//         }
//         CloseHandle(hFile);

        sprintf(cFilename, "%s\\%s.%s", cFilename, "COMM_ISAPI_ALARM", cExt);

        CFile file;
        if (!file.Open(cFilename, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeReadWrite))
        {
            return;
        }
        file.SeekToEnd();
        file.Write(struISAPIAlarm.pAlarmData, struISAPIAlarm.dwAlarmDataLen);
        char szEnd[3] = { 0 };
        szEnd[0] = '\r';
        szEnd[1] = '\n';
        file.Write(szEnd, strlen(szEnd));
        file.Close();

        if (struISAPIAlarm.pPicPackData != NULL)
        {
            int i = 0;
            while (i <= struISAPIAlarm.byPicturesNumber - 1)
            {
                DWORD dwWrittenBytes = 0;
                if (1 == ((NET_DVR_ALARM_ISAPI_PICDATA *)struISAPIAlarm.pPicPackData)[i].byPicType)
                {
                    sprintf(cFilename, "%s\\PicData[%s]_%s_%d.jpg", cSubFilename, chTime, ((NET_DVR_ALARM_ISAPI_PICDATA *)struISAPIAlarm.pPicPackData)[i].szFilename, rand() % GetTickCount());
                }
                else
                {
                    sprintf(cFilename, "%s\\PicData[%s]_%s_%d.dat", cSubFilename, chTime, ((NET_DVR_ALARM_ISAPI_PICDATA *)struISAPIAlarm.pPicPackData)[i].szFilename, rand() % GetTickCount());
                }

                HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hFile == INVALID_HANDLE_VALUE)
                {
                    return;
                }
                DWORD dwRet = WriteFile(hFile, ((NET_DVR_ALARM_ISAPI_PICDATA *)struISAPIAlarm.pPicPackData)[i].pPicData, ((NET_DVR_ALARM_ISAPI_PICDATA *)struISAPIAlarm.pPicPackData)[i].dwPicLen, &dwWrittenBytes, NULL);
                if (dwRet == 0 || dwWrittenBytes < ((NET_DVR_ALARM_ISAPI_PICDATA *)struISAPIAlarm.pPicPackData)[i].dwPicLen)
                {
                    DWORD dwError = GetLastError();
                    g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Frames People Counting Info Wtite to File Fail.System Error:%d, dwJsonDataLen:%d, WrittenBytes:%d ", dwError, ((NET_DVR_ALARM_ISAPI_PICDATA *)struISAPIAlarm.pPicPackData)[i].dwPicLen, dwWrittenBytes);
                }
                CloseHandle(hFile);
                delete ((NET_DVR_ALARM_ISAPI_PICDATA *)struISAPIAlarm.pPicPackData)[i].pPicData;
                i++;
            }
            delete struISAPIAlarm.pPicPackData;
        }
        delete struISAPIAlarm.pAlarmData;
    }
}


void CClientDemoDlg::OnMenuSearchAlarm()
{
    // TODO:  在此添加命令处理程序代码
    CDlgAlarmInfo dlg;
    dlg.m_iDevIndex = GetCurDeviceIndex();
    dlg.m_lServerID = g_struDeviceInfo[dlg.m_iDevIndex].lLoginID;
    dlg.DoModal();
}

void CClientDemoDlg::ProcHeatMapResultPDC(WPARAM wParam, LPARAM lParam)//热度图按人数统计数据上传事件 2018-06-05
{
    char szInfoBuf[1024] = { 0 };
    char szLan[128] = { 0 };
    char szAlarmType[128] = { 0 };
    char cFilename[256] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    NET_DVR_HEATMAP_RESULT_PDC struHeatMapResult = { 0 };
    memset(&struHeatMapResult, 0, sizeof(NET_DVR_HEATMAP_RESULT_PDC));
    memcpy(&struHeatMapResult, pAlarmInfo, sizeof(NET_DVR_HEATMAP_RESULT_PDC));
    sprintf(cFilename, "No heat map");

    for (int i = 0; i < 2; i++)
    {
        if (struHeatMapResult.struSingleHeatMap[i].wArrayColumn > 0 && struHeatMapResult.struSingleHeatMap[i].wArrayLine > 0 && struHeatMapResult.struSingleHeatMap[i].pBuffer != NULL)
        {
            sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName);
            if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
            {
                CreateDirectory(cFilename, NULL);
            }

            SYSTEMTIME t;
            GetLocalTime(&t);
            char chTime[128];
            sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

            sprintf(cFilename, "%s\\HeatMapValue_%d_[%s].txt", cFilename, i, chTime);
            HANDLE hFile;
            DWORD dwReturn = 0;
            hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile == INVALID_HANDLE_VALUE)
            {
                return;
            }
            WriteFile(hFile, struHeatMapResult.struSingleHeatMap[i].pBuffer, struHeatMapResult.struSingleHeatMap[i].wArrayColumn*struHeatMapResult.struSingleHeatMap[i].wArrayLine, &dwReturn, NULL);
            CloseHandle(hFile);
            hFile = NULL;
        }
    }


    g_StringLanType(szLan, "热度图按人数统计报警", "Heat Map Result PDC");
    sprintf(szInfoBuf, "%s:[IP:%s Port:%d Channel:%d IvmsChannel:%d StartTime%d-%d-%d %d:%d:%d EndTime:%d-%d-%d %d:%d:%d BrokenNetHttp:%d] IvmsChannelEx[%d] CurNumber[%d] LeaveNumber[%d] SingleHeatMap[0]:ArrayLine:%d ArrayColumn:%d MaxHeatMapValue:%d MinHeatMapValue:%d TimeHeatMapValue:%d\
                                                                      SingleHeatMap[1]:ArrayLine:%d ArrayColumn:%d MaxHeatMapValue:%d MinHeatMapValue:%d TimeHeatMapValue:%d\n", \
                                                                      szLan, struHeatMapResult.struDevInfo.struDevIP.sIpV4, struHeatMapResult.struDevInfo.wPort, struHeatMapResult.struDevInfo.byChannel, \
                                                                      struHeatMapResult.struDevInfo.byIvmsChannel, struHeatMapResult.struStartTime.wYear, struHeatMapResult.struStartTime.byMonth, \
                                                                      struHeatMapResult.struStartTime.byDay, struHeatMapResult.struStartTime.byHour, struHeatMapResult.struStartTime.byMinute, \
                                                                      struHeatMapResult.struStartTime.bySecond, struHeatMapResult.struEndTime.wYear, struHeatMapResult.struEndTime.byMonth, struHeatMapResult.struEndTime.byDay, \
                                                                      struHeatMapResult.struEndTime.byHour, struHeatMapResult.struEndTime.byMinute, struHeatMapResult.struEndTime.bySecond, struHeatMapResult.byBrokenNetHttp, struHeatMapResult.wDevInfoIvmsChannelEx, struHeatMapResult.wCurNumber,struHeatMapResult.wLeaveNumber, \
                                                                      struHeatMapResult.struSingleHeatMap[0].wArrayLine, struHeatMapResult.struSingleHeatMap[0].wArrayColumn, struHeatMapResult.struSingleHeatMap[0].dwMaxHeatMapValue, struHeatMapResult.struSingleHeatMap[0].dwMinHeatMapValue, struHeatMapResult.struSingleHeatMap[0].dwTimeHeatMapValue, \
                                                                      struHeatMapResult.struSingleHeatMap[1].wArrayLine, struHeatMapResult.struSingleHeatMap[1].wArrayColumn, struHeatMapResult.struSingleHeatMap[1].dwMaxHeatMapValue, struHeatMapResult.struSingleHeatMap[1].dwMinHeatMapValue, struHeatMapResult.struSingleHeatMap[1].dwTimeHeatMapValue);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcHeatMapResultDuration(WPARAM wParam, LPARAM lParam)//热度图按人员停留时间统计数据上传事件 2018-06-05
{
    char szInfoBuf[1024] = { 0 };
    char szLan[128] = { 0 };
    char szAlarmType[128] = { 0 };
    char cFilename[256] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    NET_DVR_HEATMAP_RESULT struHeatMapResult = { 0 };
    memset(&struHeatMapResult, 0, sizeof(NET_DVR_HEATMAP_RESULT));
    memcpy(&struHeatMapResult, pAlarmInfo, sizeof(NET_DVR_HEATMAP_RESULT));
    sprintf(cFilename, "No heat map");

    if (struHeatMapResult.wArrayColumn > 0 && struHeatMapResult.wArrayLine > 0 && struHeatMapResult.pBuffer != NULL)
    {
        sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

        sprintf(cFilename, "%s\\HeatMapValue[%s].txt", cFilename, chTime);
        HANDLE hFile;
        DWORD dwReturn = 0;
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struHeatMapResult.pBuffer, struHeatMapResult.wArrayColumn*struHeatMapResult.wArrayLine, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }

    g_StringLanType(szLan, "热度图按人员停留时间报警", "Heat Map Duration Result");
    sprintf(szInfoBuf, "%s:[IP:%s Port:%d Channel:%d IvmsChannel:%d StartTime%d-%d-%d %d:%d:%d EndTime:%d-%d-%d %d:%d:%d ArrayLine:%d ArrayColumn:%d HeatMapPath:%s \
            MaxHeatMapValue:%d MinHeatMapValue:%d TimeHeatMapValue:%d DetSceneID:%d BrokenNetHttp:%d]IvmsChannel[%d]IvmsChannelEx[%d]TotalTime[%d]\n", \
            szLan, struHeatMapResult.struDevInfo.struDevIP.sIpV4, struHeatMapResult.struDevInfo.wPort, struHeatMapResult.struDevInfo.byChannel, \
            struHeatMapResult.struDevInfo.byIvmsChannel, struHeatMapResult.struStartTime.wYear, struHeatMapResult.struStartTime.byMonth, \
            struHeatMapResult.struStartTime.byDay, struHeatMapResult.struStartTime.byHour, struHeatMapResult.struStartTime.byMinute, \
            struHeatMapResult.struStartTime.bySecond, struHeatMapResult.struEndTime.wYear, struHeatMapResult.struEndTime.byMonth, struHeatMapResult.struEndTime.byDay, \
            struHeatMapResult.struEndTime.byHour, struHeatMapResult.struEndTime.byMinute, struHeatMapResult.struEndTime.bySecond, struHeatMapResult.wArrayLine, \
            struHeatMapResult.wArrayColumn, cFilename, struHeatMapResult.dwMaxHeatMapValue, struHeatMapResult.dwMinHeatMapValue, struHeatMapResult.dwTimeHeatMapValue, \
            struHeatMapResult.byDetSceneID, struHeatMapResult.byBrokenNetHttp, struHeatMapResult.struDevInfo.byIvmsChannel, struHeatMapResult.wDevInfoIvmsChannelEx, struHeatMapResult.dwTotalTime);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}

void CClientDemoDlg::ProcHeatMapResultIntersection(WPARAM wParam, LPARAM lParam)//路口分析热度值结果上传 2018-06-05
{
    char szInfoBuf[1024] = { 0 };
    char szLan[128] = { 0 };
    char szAlarmType[128] = { 0 };
    char cFilename[256] = { 0 };
    LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
    char *pAlarmInfo = (char *)(lParam);
    int iDeviceIndex = pAlarmDev->iDeviceIndex;
    NET_DVR_HEATMAP_RESULT struHeatMapResult = { 0 };
    memset(&struHeatMapResult, 0, sizeof(NET_DVR_HEATMAP_RESULT));
    memcpy(&struHeatMapResult, pAlarmInfo, sizeof(NET_DVR_HEATMAP_RESULT));

    if (struHeatMapResult.wArrayColumn > 0 && struHeatMapResult.wArrayLine > 0 && struHeatMapResult.pBuffer != NULL)
    {
        char szIntersectionValueBuf[1024] = { 0 };
        int iLine = 65;
        int iColumn = 65;
        for (int i = 0; i < struHeatMapResult.wArrayLine; i++)
        {
            //先在第一行打印A-J
            if (i == 0)
            {
                sprintf(szIntersectionValueBuf, "  ");
                for (int k = 0; k < struHeatMapResult.wArrayColumn; k++)
                {
                    sprintf(szIntersectionValueBuf, "%s  %c ", szIntersectionValueBuf, iLine);
                    iLine++;
                }
                sprintf(szIntersectionValueBuf, "%s\r\n", szIntersectionValueBuf);
            }
            //打印每一行数据，数据之前会先打印一个字母
            for (int j = 0; j < struHeatMapResult.wArrayColumn; j++)
            {
                if (j == 0)
                {
                    sprintf(szIntersectionValueBuf, "%s%c  ", szIntersectionValueBuf, iColumn);
                    iColumn++;
                }
                sprintf(szIntersectionValueBuf, "%s %d |", szIntersectionValueBuf,*(struHeatMapResult.pBuffer + i*struHeatMapResult.wArrayColumn + j));
            }
            sprintf(szIntersectionValueBuf, "%s\r\n", szIntersectionValueBuf);
        }
        sprintf(szIntersectionValueBuf, "%s StartTime%d-%d-%d %d:%d:%d EndTime:%d-%d-%d %d:%d:%d", szIntersectionValueBuf, \
            struHeatMapResult.struStartTime.wYear, struHeatMapResult.struStartTime.byMonth, struHeatMapResult.struStartTime.byDay, \
            struHeatMapResult.struStartTime.byHour, struHeatMapResult.struStartTime.byMinute,struHeatMapResult.struStartTime.bySecond, \
            struHeatMapResult.struEndTime.wYear, struHeatMapResult.struEndTime.byMonth, struHeatMapResult.struEndTime.byDay, \
            struHeatMapResult.struEndTime.byHour, struHeatMapResult.struEndTime.byMinute, struHeatMapResult.struEndTime.bySecond);
        sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[iDeviceIndex].chDeviceIPInFileName);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }

        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

        sprintf(cFilename, "%s\\HeatMapResultIntersectionValue[%s].txt", cFilename, chTime);
        HANDLE hFile;
        DWORD dwReturn = 0;
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, szIntersectionValueBuf, sizeof(szIntersectionValueBuf), &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
    }

    g_StringLanType(szLan, "路口分析热度值报警", "Heat Map Result Intersection");
    sprintf(szInfoBuf, "%s:[IP:%s Port:%d Channel:%d IvmsChannel:%d StartTime%d-%d-%d %d:%d:%d EndTime:%d-%d-%d %d:%d:%d ArrayLine:%d ArrayColumn:%d HeatMapPath:%s \
             MaxHeatMapValue:%d MinHeatMapValue:%d TimeHeatMapValue:%d DetSceneID:%d BrokenNetHttp:%d]IvmsChannel[%d]IvmsChannelEx[%d]\n", \
             szLan, struHeatMapResult.struDevInfo.struDevIP.sIpV4, struHeatMapResult.struDevInfo.wPort, struHeatMapResult.struDevInfo.byChannel, \
             struHeatMapResult.struDevInfo.byIvmsChannel, struHeatMapResult.struStartTime.wYear, struHeatMapResult.struStartTime.byMonth, \
             struHeatMapResult.struStartTime.byDay, struHeatMapResult.struStartTime.byHour, struHeatMapResult.struStartTime.byMinute, \
             struHeatMapResult.struStartTime.bySecond, struHeatMapResult.struEndTime.wYear, struHeatMapResult.struEndTime.byMonth, struHeatMapResult.struEndTime.byDay, \
             struHeatMapResult.struEndTime.byHour, struHeatMapResult.struEndTime.byMinute, struHeatMapResult.struEndTime.bySecond, struHeatMapResult.wArrayLine, \
             struHeatMapResult.wArrayColumn, cFilename, struHeatMapResult.dwMaxHeatMapValue, struHeatMapResult.dwMinHeatMapValue, struHeatMapResult.dwTimeHeatMapValue, \
             struHeatMapResult.byDetSceneID, struHeatMapResult.byBrokenNetHttp, struHeatMapResult.struDevInfo.byIvmsChannel, struHeatMapResult.wDevInfoIvmsChannelEx);
    AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
}
