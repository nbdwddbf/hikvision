
#include "stdafx.h"
#include "DeviceCfgFile.h"
#include "ClientDemo.h"

//静态常量赋值
const char* DeviceCfgFile::c_strNode_Devices = _T("Devices");
const char* DeviceCfgFile::c_strNode_DeviceID = _T("ID");
const char* DeviceCfgFile::c_strNode_SerialNo = _T("SerialNumber");
const char* DeviceCfgFile::c_strNode_ChanNum = _T("ChannelNumber");
const char* DeviceCfgFile::c_strNode_StartChan = _T("StartChannel");
const char* DeviceCfgFile::c_strNode_AlarmInNum = _T("AlarmInNum");
const char* DeviceCfgFile::c_strNode_AlarmOutNum = _T("AlarmOutNum");
const char* DeviceCfgFile::c_strNode_IPChanNum = _T("IPChanNum");
const char* DeviceCfgFile::c_strNode_MirrorChanNum = _T("MirrorChanNum");
const char* DeviceCfgFile::c_strNode_StartMirrorChanNo = _T("StartMirrorChanNo");
const char* DeviceCfgFile::c_strNode_LocalNodeName = _T("LocalNodeName");
const char* DeviceCfgFile::c_strNode_DeviceType = _T("DeviceType");
const char* DeviceCfgFile::c_strNode_DiskNum = _T("DiskNum");
const char* DeviceCfgFile::c_strNode_LoginUserName = _T("LoginUserName");
const char* DeviceCfgFile::c_strNode_LoginUserPwd = _T("LoginUserPwd");
const char* DeviceCfgFile::c_strNode_DeviceIP = _T("DeviceIP");
const char* DeviceCfgFile::c_strNode_DeviceMultiIP = _T("DeviceMultiIP");
const char* DeviceCfgFile::c_strNode_DevicePort = _T("DevicePort");
const char* DeviceCfgFile::c_strNode_DeviceName = _T("DeviceName");
const char* DeviceCfgFile::c_strNode_Chans = _T("Channels");
const char* DeviceCfgFile::c_strNode_ChanID = _T("ChanID");
const char* DeviceCfgFile::c_strNode_DeviceIndex = _T("DeviceIndex");
const char* DeviceCfgFile::c_strNode_ChanIndex = _T("ChanIndex");
const char* DeviceCfgFile::c_strNode_ChanName = _T("ChanName");
const char* DeviceCfgFile::c_strNode_Protocol = _T("Protocol");
const char* DeviceCfgFile::c_strNode_PicResolution = _T("PicResolution");
const char* DeviceCfgFile::c_strNode_PicQuality = _T("PicQuality");
const char* DeviceCfgFile::c_strNode_Enable = _T("Enable");
const char* DeviceCfgFile::c_strPreviewMode = _T("PreviewMode");
const char* DeviceCfgFile::c_strPreviewProtocolType = _T("PreviewProtocolType");
const char* DeviceCfgFile::c_strVideoCodingType = _T("VideoCodingType");
const char* DeviceCfgFile::c_strStreamType = _T("StreamType");
const char* DeviceCfgFile::c_strLinkMode = _T("LinkMode");
const char* DeviceCfgFile::c_strNode_LoginMode = _T("LoginMode");
const char* DeviceCfgFile::c_strNode_Https = _T("Https");

/** @fn DeviceCfgFile& DeviceCfgFile::GetInstance()
 *  @brief 获取DeviceCfgFile的单例引用
 *  @return DeviceCfgFile&
 */
DeviceCfgFile& DeviceCfgFile::GetInstance()
{
    static DeviceCfgFile deviceCfgFile;
    return deviceCfgFile;
}

/** @fn  DeviceCfgFile::DeviceCfgFile()
 *  @brief
 *  @return none
 */
DeviceCfgFile::DeviceCfgFile()
{}

/** @fn  DeviceCfgFile::~DeviceCfgFile()
 *  @brief
 *  @return none
 */
DeviceCfgFile::~DeviceCfgFile()
{}

/** @fn cJSON* DeviceCfgFile::WriteDeviceToNode(const STRU_DEVICE_INFO& device, int nIndex)
 *  @brief
 *  @param (in)	const STRU_DEVICE_INFO & device 设备引用
 *  @param (in)	int nIndex 设备序号
 *  @return cJSON* 返回cjson节点 NULL-fail other-succ
 */
cJSON* DeviceCfgFile::WriteDeviceToNode(const STRU_DEVICE_INFO& device, int nIndex)
{
    cJSON* pDevice = cJSON_CreateObject();
    cJSON* pChannels = NULL;
    cJSON* pChannel = NULL;
    if (NULL == pDevice)
    {
        return NULL;
    }

    BOOL bSucc = FALSE;
    do
    {
        cJSON_AddNumberToObject(pDevice, c_strNode_DeviceID, nIndex);
        cJSON_AddStringToObject(pDevice, c_strNode_SerialNo, device.chSerialNumber);
        cJSON_AddNumberToObject(pDevice, c_strNode_ChanNum, device.iDeviceChanNum);
        cJSON_AddNumberToObject(pDevice, c_strNode_StartChan, device.iStartChan);
        cJSON_AddNumberToObject(pDevice, c_strNode_AlarmInNum, device.iAlarmInNum);
        cJSON_AddNumberToObject(pDevice, c_strNode_AlarmOutNum, device.iAlarmOutNum);
        cJSON_AddNumberToObject(pDevice, c_strNode_IPChanNum, device.iIPChanNum);
        cJSON_AddNumberToObject(pDevice, c_strNode_MirrorChanNum, device.byMirrorChanNum);
        cJSON_AddNumberToObject(pDevice, c_strNode_StartMirrorChanNo, device.wStartMirrorChanNo);
        cJSON_AddStringToObject(pDevice, c_strNode_LocalNodeName, device.chLocalNodeName);
        cJSON_AddNumberToObject(pDevice, c_strNode_DeviceType, device.iDeviceType);
        cJSON_AddNumberToObject(pDevice, c_strNode_DiskNum, device.iDiskNum);
        cJSON_AddStringToObject(pDevice, c_strNode_LoginUserName, device.chLoginUserName);
        cJSON_AddStringToObject(pDevice, c_strNode_LoginUserPwd, device.chLoginPwd);
        cJSON_AddStringToObject(pDevice, c_strNode_DeviceIP, device.chDeviceIP);
        cJSON_AddStringToObject(pDevice, c_strNode_DeviceMultiIP, device.chDeviceMultiIP);
        cJSON_AddNumberToObject(pDevice, c_strNode_DevicePort, device.lDevicePort);
        cJSON_AddStringToObject(pDevice, c_strNode_DeviceName, device.chDeviceName);
        cJSON_AddNumberToObject(pDevice, c_strNode_LoginMode, device.byLoginMode);
        cJSON_AddNumberToObject(pDevice, c_strNode_Https, device.byHttps);

        pChannels = cJSON_CreateArray();
        if (NULL == pChannels)
        {
            break;
        }

        for (int j = 0; j < MAX_CHANNUM_V40; j++)
        {
            if (device.pStruChanInfo[j].iChanIndex == -1)
            {
                continue;
            }
            pChannel = cJSON_CreateObject();
            if (NULL == pChannel)
            {
                break;
            }

            cJSON_AddNumberToObject(pChannel, c_strNode_ChanID, j);
            cJSON_AddNumberToObject(pChannel, c_strNode_DeviceIndex
                , device.pStruChanInfo[j].iDeviceIndex);
            cJSON_AddNumberToObject(pChannel, c_strNode_ChanIndex
                , device.pStruChanInfo[j].iChanIndex);
            cJSON_AddStringToObject(pChannel, c_strNode_ChanName
                , device.pStruChanInfo[j].chChanName);
            cJSON_AddNumberToObject(pChannel, c_strNode_Protocol
                , device.pStruChanInfo[j].dwProtocol);
            cJSON_AddNumberToObject(pChannel, c_strNode_PicResolution
                , device.pStruChanInfo[j].iPicResolution);
            cJSON_AddNumberToObject(pChannel, c_strNode_PicQuality
                , device.pStruChanInfo[j].iPicQuality);
            cJSON_AddNumberToObject(pChannel, c_strNode_Enable
                , device.pStruChanInfo[j].bEnable);
            cJSON_AddNumberToObject(pChannel, c_strPreviewMode
                , device.pStruChanInfo[j].dwPreviewMode);
            cJSON_AddNumberToObject(pChannel, c_strPreviewProtocolType
                , device.pStruChanInfo[j].nPreviewProtocolType);
            cJSON_AddNumberToObject(pChannel, c_strVideoCodingType
                , device.pStruChanInfo[j].nVideoCodingType);
            cJSON_AddNumberToObject(pChannel, c_strStreamType
                , device.pStruChanInfo[j].dwStreamType);
            cJSON_AddNumberToObject(pChannel, c_strLinkMode
                , device.pStruChanInfo[j].dwLinkMode);

            cJSON_AddItemToArray(pChannels, pChannel);
        }

        cJSON_AddItemToObject(pDevice, c_strNode_Chans, pChannels);
        bSucc = TRUE;
    } while (0);

    if (bSucc)
    {
        return pDevice;
    }
    else
    {
        if (NULL != pChannel)
        {
            cJSON_Delete(pChannel);
            pChannel = NULL;
        }
        if (NULL != pChannels)
        {
            cJSON_Delete(pChannels);
            pChannels = NULL;
        }
        if (NULL != pDevice)
        {
            cJSON_Delete(pDevice);
            pDevice = NULL;
        }
        return NULL;
    }
}

/** @fn void DeviceCfgFile::SaveToFile()
 *  @brief 将设备信息保存到json文件中
 *  @return void
 */
void DeviceCfgFile::SaveToFile()
{
    CStdioFile myFile;
    CString csFilename;
    cJSON* pRoot = NULL;
    cJSON* pDevices = NULL;
    cJSON* pDevice = NULL;

    csFilename.Format(_T("%s\\DeviceCfg.json"), g_szWorkDir);
    if (myFile.Open(csFilename, CFile::modeCreate | CFile::modeWrite) == FALSE)
    {
        return;
    }

    pRoot = cJSON_CreateObject();
    pDevices = cJSON_CreateArray();
    if (NULL == pRoot || NULL == pDevices)
    {
        return;
    }

    BOOL bSucc = TRUE;
    for (int i = 0; i < MAX_DEVICES && bSucc; i++)
    {
        if (g_struDeviceInfo[i].iDeviceChanNum == -1)
        {
            continue;
        }
        
        pDevice = WriteDeviceToNode(g_struDeviceInfo[i], i);
        if (pDevice != NULL)
        {
            cJSON_AddItemToArray(pDevices, pDevice);
        }
        else
        {
            bSucc = FALSE;
            continue;
        }
    }

    if (bSucc)
    {
        cJSON_AddItemToObject(pRoot, c_strNode_Devices, pDevices);
        char* strOut = cJSON_Print(pRoot);
        myFile.WriteString(CString(strOut));
        cJSON_Delete(pRoot);
        free(strOut);
    }
    else
    {
        if (NULL != pDevice)
        {
            cJSON_Delete(pDevice);
            pDevice = NULL;
        }
        if (NULL != pDevices)
        {
            cJSON_Delete(pDevices);
            pDevices = NULL;
        }
        if (NULL != pRoot)
        {
            cJSON_Delete(pRoot);
            pRoot = NULL;
        }
    }
    myFile.Close();
}


/** @fn BOOL GetNodeVal(const cJSON* pFather, const char* strName, char* strVal, int nLen)
 *  @brief 读取单个cjson节点值(字符串)
 *  @param (in)	const cJSON * pFather 父节点 
 *  @param (in)	const char * strName 节点名
 *  @param (in)	char * strVal 读取结果字符串
 *  @param (in)	int nLen 字符串长度
 *  @return BOOL TRUE-succ FALSE-fail
 */
BOOL GetNodeVal_JSON(const cJSON* pFather, const char* strName, char* strVal, int nLen)
{
    cJSON* pNode = cJSON_GetObjectItem(const_cast<cJSON*>(pFather), strName);
    if (pNode == NULL || pNode->type != cJSON_String)
    {
        return FALSE;
    }
    strncpy(strVal, pNode->valuestring, nLen - 1);
    return TRUE;
}

/** @fn BOOL GetNodeVal(const cJSON* pFather, const char* strName, int* nVal)
 *  @brief 读取单个cjson节点值(数值)
 *  @param (in)	const cJSON * pFather 父节点  
 *  @param (in)	const char * strName 节点名  
 *  @param (in)	int * nVal 读取结果
 *  @return BOOL TRUE-succ FALSE-fail
 */
BOOL GetNodeVal_JSON(const cJSON* pFather, const char* strName, int* nVal)
{
    cJSON* pNode = cJSON_GetObjectItem(const_cast<cJSON*>(pFather), strName);
    if (pNode == NULL || pNode->type != cJSON_Number)
    {
        return FALSE;
    }
    
    *nVal = pNode->valueint;
    return TRUE;
}

/** @fn BOOL DeviceCfgFile::ReadDeviceFromNode(const cJSON* pNode, PLOCAL_DEVICE_INFO pDevice, int* pIndex)
 *  @brief 从单个节点中读取设备信息
 *  @param (in)	const cJSON * pNode  节点  
 *  @param (in)	PLOCAL_DEVICE_INFO pDevice  读取结果
 *  @param (in)	int * pIndex  设备序号
 *  @return BOOL TRUE-succ FALSE-fail
 */
BOOL DeviceCfgFile::ReadDeviceFromNode(const cJSON* pNode, PLOCAL_DEVICE_INFO pDevice, int* pIndex)
{
    int nTmp = 0;
    BOOL bSucc = FALSE;

    do
    {
        if (pNode == NULL || pDevice == NULL || pIndex == NULL
            || pDevice->pStruChanInfo == NULL)
        {
            break;
        }

        if (GetNodeVal_JSON(pNode, c_strNode_DeviceID, &nTmp) == FALSE)
        {
            break;
        }
        *pIndex = nTmp;
        pDevice->iDeviceIndex = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_SerialNo, pDevice->chSerialNumber, 50) == FALSE)
        {
            break;
        }

        if (GetNodeVal_JSON(pNode, c_strNode_ChanNum, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->iDeviceChanNum = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_StartChan, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->iStartChan = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_AlarmInNum, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->iAlarmInNum = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_AlarmOutNum, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->iAlarmOutNum = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_IPChanNum, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->iIPChanNum = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_MirrorChanNum, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->byMirrorChanNum = (BYTE)nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_StartMirrorChanNo, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->wStartMirrorChanNo = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_LocalNodeName, pDevice->chLocalNodeName, 100) == FALSE)
        {
            break;
        }

        if (GetNodeVal_JSON(pNode, c_strNode_DeviceType, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->iDeviceType = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_DiskNum, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->iDiskNum = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_LoginUserName, pDevice->chLoginUserName, NAME_LEN) == FALSE)
        {
            break;
        }

        if (GetNodeVal_JSON(pNode, c_strNode_LoginUserPwd, pDevice->chLoginPwd, NAME_LEN) == FALSE)
        {
            break;
        }

        if (GetNodeVal_JSON(pNode, c_strNode_DeviceIP, pDevice->chDeviceIP, 130) == FALSE)
        {
            break;
        }

        if (GetNodeVal_JSON(pNode, c_strNode_DeviceMultiIP, pDevice->chDeviceMultiIP, 130) == FALSE)
        {
            break;
        }

        if (GetNodeVal_JSON(pNode, c_strNode_DevicePort, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->lDevicePort = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_DeviceName, pDevice->chDeviceName, 100) == FALSE)
        {
            break;
        }

        if (GetNodeVal_JSON(pNode, c_strNode_LoginMode, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->byLoginMode = nTmp;

        if (GetNodeVal_JSON(pNode, c_strNode_Https, &nTmp) == FALSE)
        {
            break;
        }
        pDevice->byHttps = nTmp;

        cJSON* pChannels = cJSON_GetObjectItem(const_cast<cJSON*>(pNode), c_strNode_Chans);
        if (pChannels == NULL || pChannels->type != cJSON_Array)
        {
            break;
        }

        

        int nChannels = cJSON_GetArraySize(pChannels);
        for (int i = 0; i < nChannels; i++)
        {
            int nChannelIndex = 0;
            struct STRU_CHANNEL_INFO struChannel;
         
            cJSON* pChannel = cJSON_GetArrayItem(pChannels, i);
            if (pChannel == NULL || pChannel->type != cJSON_Object)
            {
                break;
            }

            if (GetNodeVal_JSON(pChannel, c_strNode_ChanID, &nTmp) == FALSE)
            {
                break;
            }
            nChannelIndex = nTmp;
            if (nChannelIndex >= MAX_CHANNUM_V40)
            {
                continue;
            }

            if (GetNodeVal_JSON(pChannel, c_strNode_DeviceIndex, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.iDeviceIndex = nTmp;

            if (GetNodeVal_JSON(pChannel, c_strNode_ChanIndex, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.iChanIndex = nTmp;

            if (GetNodeVal_JSON(pChannel, c_strNode_ChanName, struChannel.chChanName, 100) == FALSE)
            {
                break;
            }

            if (GetNodeVal_JSON(pChannel, c_strNode_Protocol, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.dwProtocol = nTmp;

            if (GetNodeVal_JSON(pChannel, c_strNode_PicResolution, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.iPicResolution = nTmp;

            if (GetNodeVal_JSON(pChannel, c_strNode_PicQuality, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.iPicQuality = nTmp;

            if (GetNodeVal_JSON(pChannel, c_strNode_Enable, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.bEnable = nTmp == 0 ? FALSE : TRUE;

            if (GetNodeVal_JSON(pChannel, c_strPreviewMode, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.dwPreviewMode = nTmp;

            if (GetNodeVal_JSON(pChannel, c_strPreviewProtocolType, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.nPreviewProtocolType = nTmp;

            if (GetNodeVal_JSON(pChannel, c_strVideoCodingType, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.nVideoCodingType = nTmp;

            if (GetNodeVal_JSON(pChannel, c_strStreamType, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.dwStreamType = nTmp;

            if (GetNodeVal_JSON(pChannel, c_strLinkMode, &nTmp) == FALSE)
            {
                break;
            }
            struChannel.dwLinkMode = nTmp;

            memcpy(&(pDevice->pStruChanInfo[nChannelIndex]), &struChannel
                    , sizeof(struct STRU_CHANNEL_INFO));
        }

        bSucc = TRUE;
    } while (0);

    return bSucc;
}

/** @fn void DeviceCfgFile::ReadFromFile()
 *  @brief 从json文件中读取设备信息
 *  @return void
 */
void DeviceCfgFile::ReadFromFile()
{
    CStdioFile myFile;
    CString csFilename;

    csFilename.Format(_T("%s\\DeviceCfg.json"), g_szWorkDir);
    if (myFile.Open(csFilename, CFile::modeRead | CFile::typeBinary) == FALSE)
    {
        myFile.Open(csFilename, CFile::modeCreate);
        return;
    }

    ULONGLONG ullFileLen = myFile.GetLength() + 1;
    char* strDevices = new char[ullFileLen]();
    myFile.Seek(SEEK_SET, 0);
    if (myFile.Read(strDevices, ullFileLen - 1) == FALSE)
    {
        delete [] strDevices;
        myFile.Close();
        return;
    }
    
    myFile.Close();
    cJSON* pRoot = cJSON_Parse(strDevices);
    delete [] strDevices;
    if (pRoot == NULL)
    {
        return;
    }
    do
    {
        cJSON* pDevices = cJSON_GetObjectItem(pRoot, c_strNode_Devices);
        if (pDevices == NULL || pDevices->type != cJSON_Array)
        {
            break;
        }

        int nDevices = cJSON_GetArraySize(pDevices);
        for (int i = 0; i < nDevices; i++)
        {
            STRU_DEVICE_INFO struDeviceInfo;
            STRU_CHANNEL_INFO struChannels[MAX_CHANNUM_V40];
            struDeviceInfo.pStruChanInfo = struChannels;
            int nIndex = 0;
            cJSON* pDevice = cJSON_GetArrayItem(pDevices, i);
            if (pDevice == NULL || pDevice->type != cJSON_Object)
            {
                break;
            }

            if(ReadDeviceFromNode(pDevice, &struDeviceInfo, &nIndex) == FALSE)
            {
                break;
            }

            if (g_struDeviceInfo[nIndex].pStruChanInfo == NULL)
            {
                g_struDeviceInfo[nIndex].pStruChanInfo = new STRU_CHANNEL_INFO[MAX_CHANNUM_V40];
                if (g_struDeviceInfo[nIndex].pStruChanInfo == NULL)
                {
                    break;
                }
            }
            if (g_struDeviceInfo[nIndex].pStruIPAlarmInCfgV40 == NULL)
            {
                g_struDeviceInfo[nIndex].pStruIPAlarmInCfgV40 = new NET_DVR_IPALARMINCFG_V40;
                if (g_struDeviceInfo[nIndex].pStruIPAlarmInCfgV40 == NULL)
                {
                    break;
                }
                memset(g_struDeviceInfo[nIndex].pStruIPAlarmInCfgV40, 0, sizeof(NET_DVR_IPALARMINCFG_V40));
            }
            if (g_struDeviceInfo[nIndex].pStruIPAlarmOutCfgV40 == NULL)
            {
                g_struDeviceInfo[nIndex].pStruIPAlarmOutCfgV40 = new NET_DVR_IPALARMOUTCFG_V40;

                if (g_struDeviceInfo[nIndex].pStruIPAlarmOutCfgV40 == NULL)
                {
                    break;
                }
                memset(g_struDeviceInfo[nIndex].pStruIPAlarmOutCfgV40, 0, sizeof(NET_DVR_IPALARMOUTCFG_V40));
            }

            STRU_CHANNEL_INFO* pStruChanInfo_Tmp = g_struDeviceInfo[nIndex].pStruChanInfo;
            NET_DVR_IPALARMINCFG_V40* pStruIPAlarmInCfgV40_Tmp = g_struDeviceInfo[nIndex].pStruIPAlarmInCfgV40;
            NET_DVR_IPALARMOUTCFG_V40* pStruIPAlarmOutCfgV40_Tmp = g_struDeviceInfo[nIndex].pStruIPAlarmOutCfgV40;

            memcpy(&g_struDeviceInfo[nIndex], &struDeviceInfo, sizeof(STRU_DEVICE_INFO));
            g_struDeviceInfo[nIndex].pStruChanInfo = pStruChanInfo_Tmp;
            g_struDeviceInfo[nIndex].pStruIPAlarmInCfgV40 = pStruIPAlarmInCfgV40_Tmp;
            g_struDeviceInfo[nIndex].pStruIPAlarmOutCfgV40 = pStruIPAlarmOutCfgV40_Tmp;

            memcpy(g_struDeviceInfo[nIndex].pStruChanInfo, struChannels, sizeof(STRU_CHANNEL_INFO)*MAX_CHANNUM_V40);

            if (g_struDeviceInfo[nIndex].iIPChanNum >= 0 && g_struDeviceInfo[nIndex].pStruIPParaCfgV40 == NULL)
            {
                g_struDeviceInfo[nIndex].pStruIPParaCfgV40 = new NET_DVR_IPPARACFG_V40[g_struDeviceInfo[nIndex].iIPChanNum / MAX_CHANNUM_V30 + 1];
                if (g_struDeviceInfo[nIndex].pStruIPParaCfgV40 == NULL)
                {
                    char szLan[256] = { 0 };
                    g_StringLanType(szLan, _T("申请内存失败"), _T("Alloc memory  failed"));
                    AfxMessageBox(szLan);
                    break;
                }

                for (int k = 0; k < g_struDeviceInfo[nIndex].iIPChanNum / MAX_CHANNUM_V30 + 1; k++)
                {
                    memset(&g_struDeviceInfo[nIndex].pStruIPParaCfgV40[k], 0, sizeof(NET_DVR_IPPARACFG_V40));
                }
            }
        }
    } while (0);
    cJSON_Delete(pRoot);
}
