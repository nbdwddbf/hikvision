
#ifndef _DEVICECFGFILE_H_
#define _DEVICECFGFILE_H_

#include "cjson/cJSON.h"
#include "GeneralDef.h"

/**   @class DeviceCfgFile
 *    @brief 设备配置文件类,该类为单例类
 */
class DeviceCfgFile
{
public:
    static DeviceCfgFile& GetInstance();
    void SaveToFile();
    void ReadFromFile();
private:
    DeviceCfgFile();
    ~DeviceCfgFile();
    DeviceCfgFile(const DeviceCfgFile&);
    DeviceCfgFile& operator=(const DeviceCfgFile&);
    
    static cJSON* WriteDeviceToNode(const STRU_DEVICE_INFO& device, int nIndex);
    static BOOL ReadDeviceFromNode(const cJSON* pNode, PLOCAL_DEVICE_INFO pDevice, int* pIndex);

    const static char* c_strNode_Devices;               //主节点名

    const static char* c_strNode_DeviceID;              //设备ID节点
    const static char* c_strNode_SerialNo;              //设备serial number节点
    const static char* c_strNode_ChanNum;               //设备channel number节点
    const static char* c_strNode_StartChan;             //设备start channel number节点
    const static char* c_strNode_AlarmInNum;            //设备alarm in number节点
    const static char* c_strNode_AlarmOutNum;           //设备alarm out number节点
    const static char* c_strNode_IPChanNum;             //设备ip channel number节点
    const static char* c_strNode_MirrorChanNum;         //设备镜像通道个数节点
    const static char* c_strNode_StartMirrorChanNo;     //设备起始镜像通道号节点
    const static char* c_strNode_LocalNodeName;         //设备local device node节点
    const static char* c_strNode_DeviceType;            //设备device type节点
    const static char* c_strNode_DiskNum;               //设备HD number节点
    const static char* c_strNode_LoginUserName;         //设备login user name节点
    const static char* c_strNode_LoginUserPwd;          //设备login user password节点
    const static char* c_strNode_DeviceIP;              //设备device ip节点
    const static char* c_strNode_DeviceMultiIP;         //设备multi-cast group address节点
    const static char* c_strNode_DevicePort;            //设备port number节点
    const static char* c_strNode_DeviceName;            //设备device name节点
    const static char* c_strNode_Chans;                 //设备channels节点
    const static char* c_strNode_LoginMode;             //设备LoginMode节点
    const static char* c_strNode_Https;                 //设备Https节点

    const static char* c_strNode_ChanID;                //设备channel id节点
    const static char* c_strNode_DeviceIndex;           //设备device name节点
    const static char* c_strNode_ChanIndex;             //设备channel index节点
    const static char* c_strNode_ChanName;              //设备channel name节点
    const static char* c_strNode_Protocol;              //设备network protocol节点
    const static char* c_strNode_PicResolution;         //设备pic resolution节点
    const static char* c_strNode_PicQuality;            //设备pic quality节点
    const static char* c_strNode_Enable;                //设备channel enable节点
    const static char* c_strPreviewMode;                //设备priview mode节点
    const static char* c_strPreviewProtocolType;        //设备priview protocol type节点
    const static char* c_strVideoCodingType;            //设备video coding type节点
    const static char* c_strStreamType;                 //设备码流类型节点
    const static char* c_strLinkMode;                   //设备码流连接方式节点
};

BOOL GetNodeVal_JSON(const cJSON* pFather, const char* strName, int* nVal);
BOOL GetNodeVal_JSON(const cJSON* pFather, const char* strName, char* strVal, int nLen);
#endif
