
#include "stdafx.h"
#include "ConvertC10S21Param.h"

/** @fn         BOOL ConvertScreenServerLoginParamXmlToStru(CXmlBase& struXml, void* pStruct);
 *  @brief      屏幕服务器登陆参数XML到结构体转换
 *  @param (in)	CXmlBase& struXml    
 *  @param (in)	void*     pStruct    
 *  @return     BOOL
 */
BOOL ConvertScreenServerLoginParamXmlToStru(CXmlBase& struXml, void* pStruct)
{
	if (pStruct == NULL)
    {
        return FALSE;
    }
	
	LPNET_DVR_SCREEN_SERVER_LOGIN_CFG  pStructItem =  (LPNET_DVR_SCREEN_SERVER_LOGIN_CFG)pStruct;
	
	if (struXml.FindElem("ServerLoginCfg") && struXml.IntoElem())
	{
		if (!ConvertSingleNodeData(&pStructItem->dwServerNo, struXml, "id", NODE_STRING_TO_INT))
		{
			return FALSE;
		}
		if (struXml.FindElem("IpAddress") && struXml.IntoElem())
		{
			BYTE byIPVersion[8] = {0};
			if (!ConvertSingleNodeData(byIPVersion, struXml, "ipVersion", NODE_STRING_TO_ARRAY, sizeof(byIPVersion)))
			{
				return FALSE;
			}
			if (0 == strcmp((char*)byIPVersion, "v4"))
			{
				if (!ConvertSingleNodeData(pStructItem->struIPAddr.sIpV4, struXml, "ipAddress", NODE_STRING_TO_ARRAY, sizeof(pStructItem->struIPAddr.sIpV4)))
				{
					return FALSE;
				}
			}
			else if (0 == strcmp((char*)byIPVersion, "v6"))
			{
				if (!ConvertSingleNodeData(pStructItem->struIPAddr.sIpV6, struXml, "ipv6Address", NODE_STRING_TO_ARRAY, sizeof(pStructItem->struIPAddr.sIpV6)))
				{
					return FALSE;
				}
			}
			struXml.OutOfElem();
		}
		if (!ConvertSingleNodeData(&pStructItem->dwPortNo, struXml, "portNo", NODE_STRING_TO_INT))
		{
			return FALSE;
		}
		if (!ConvertSingleNodeData(pStructItem->sUserName, struXml, "userName", NODE_STRING_TO_ARRAY, sizeof(pStructItem->sUserName)))
		{
			return FALSE;
		}
		if (!ConvertSingleNodeData(pStructItem->sPassword, struXml, "password", NODE_STRING_TO_ARRAY, sizeof(pStructItem->sPassword)))
		{
			return FALSE;
		}
		if (!ConvertSingleNodeData(&pStructItem->dwInputNo, struXml, "inputNo", NODE_STRING_TO_INT))
		{
			return FALSE;
		}
		struXml.OutOfElem();
	}
	
	return TRUE;
}

/** @fn         BOOL ConvertScreenServerLoginParamXmlToStru(const char* pXmlBuf, void* pStruct)
 *  @brief      屏幕服务器登陆参数XML到结构体转换
 *  @param (in)	const char* pXmlBuf    
 *  @param (in)	void*       pStruct    
 *  @return     BOOL
 */
BOOL ConvertScreenServerLoginParamXmlToStru(const char* pXmlBuf, void* pStruct)
{
	if (pXmlBuf == NULL)
    {
        //这里不用置错误码,如果数据为空,则设备返回的状态里面有错误码
        return FALSE;
    }
    //增加结构体是否为空判断 
    if (pStruct == NULL)
    {
        return FALSE;
    }
	LPNET_DVR_SCREEN_SERVER_LOGIN_CFG  pStructItem =  (LPNET_DVR_SCREEN_SERVER_LOGIN_CFG)pStruct;
	if (pStructItem->dwSize != sizeof(*pStructItem))
	{
        return FALSE;
	}
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuf) == NULL)
    {
        return FALSE;
    }
	
	return ConvertScreenServerLoginParamXmlToStru(struXml, pStruct);
}

/** @fn         BOOL ConvertScreenServerLoginParamXmlToStruList(const char* pXmlBuf, void* pStruct)
 *  @brief      屏幕服务器登陆参数XML到结构体转换
 *  @param (in)	const char* pXmlBuf    
 *  @param (in)	void*       pStruct    
 *  @return     BOOL
 */
BOOL ConvertScreenServerLoginParamXmlToStruList(const char* pXmlBuf, void* pStruct)
{
	if (pXmlBuf == NULL)
    {
        //这里不用置错误码,如果数据为空,则设备返回的状态里面有错误码
        return FALSE;
    }
    //增加结构体是否为空判断 
    if (pStruct == NULL)
    {
        return FALSE;
    }
	LPNET_DVR_SCREEN_SERVER_LOGIN_CFG_LIST  pStructItemList =  (LPNET_DVR_SCREEN_SERVER_LOGIN_CFG_LIST)pStruct;
	if (pStructItemList->dwSize != sizeof(*pStructItemList))
	{
        return FALSE;
	}
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuf) == NULL)
    {
        return FALSE;
    }
	
	if (struXml.FindElem("ServerLoginCfgList") && struXml.IntoElem())
	{
		DWORD dwCfgCnt = 0;
		LPNET_DVR_SCREEN_SERVER_LOGIN_CFG pStructItem = (LPNET_DVR_SCREEN_SERVER_LOGIN_CFG)&pStructItemList->struList[dwCfgCnt];
		pStructItem->dwSize = sizeof(*pStructItem);
		if (struXml.FindElem("ServerLoginCfg"))
		{
			if (!ConvertScreenServerLoginParamXmlToStru(struXml, pStructItem))
			{
				return FALSE;
			}
			while (struXml.NextSibElem())
			{
				dwCfgCnt++;
				pStructItem = (LPNET_DVR_SCREEN_SERVER_LOGIN_CFG)&pStructItemList->struList[dwCfgCnt];
				pStructItem->dwSize = sizeof(*pStructItem);
				if (!ConvertScreenServerLoginParamXmlToStru(struXml, pStructItem))
				{
					return FALSE;
				}
			}
		}
		struXml.OutOfElem();
	}
	
	return TRUE;
}

/** @fn         BOOL ConvertScreenServerLoginParamStruToXml(void* pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief      屏幕服务器登陆参数结构体到XML转换
 *  @param (in)	void*  pStruct    
 *  @param (in)	char** pXmlBuf    
 *  @param (in)	DWORD& dwXmlLen    
 *  @return     BOOL
 */
BOOL ConvertScreenServerLoginParamStruToXml(void* pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pStruct == NULL || pXmlBuf == NULL)
    {  
        return FALSE;
    }
    LPNET_DVR_SCREEN_SERVER_LOGIN_CFG  pStructItem =  (LPNET_DVR_SCREEN_SERVER_LOGIN_CFG)pStruct;
    if (pStructItem->dwSize != sizeof(*pStructItem))
    {     
        return FALSE;
    }
	
    CXmlBase struXml;
    struXml.CreateRoot("ServerLoginCfg");
    struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(&pStructItem->dwServerNo, struXml, "id", NODE_INT_TO_STRING);
	if (struXml.AddNode("IpAddress"))
	{
		BYTE byIPVersion[8] = {"v4"};
		ConvertSingleNodeData(byIPVersion, struXml, "ipVersion", NODE_ARRAY_TO_STRING, strlen((char*)byIPVersion));
		ConvertSingleNodeData(pStructItem->struIPAddr.sIpV4, struXml, "ipAddress", NODE_ARRAY_TO_STRING, strlen((char*)pStructItem->struIPAddr.sIpV4));
		struXml.OutOfElem();
	}
	ConvertSingleNodeData(&pStructItem->dwPortNo, struXml, "portNo", NODE_INT_TO_STRING);
	ConvertSingleNodeData(pStructItem->sUserName, struXml, "userName", NODE_ARRAY_TO_STRING, strlen((char*)pStructItem->sUserName));
	ConvertSingleNodeData(pStructItem->sPassword, struXml, "password", NODE_ARRAY_TO_STRING, strlen((char*)pStructItem->sPassword));
	ConvertSingleNodeData(&pStructItem->dwInputNo, struXml, "inputNo", NODE_INT_TO_STRING);
	
	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }
	
	return TRUE;
}

DWORD GetIDFromResponseStatus(const char* pXmlBuf)
{
	if (pXmlBuf == NULL)
    {
        //这里不用置错误码,如果数据为空,则设备返回的状态里面有错误码
        return FALSE;
    }
	
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuf) == NULL)
    {
        return FALSE;
    }
	
	DWORD dwID = 0;
	if (struXml.FindElem("ResponseStatus") && struXml.IntoElem())
	{
		ConvertSingleNodeData(&dwID, struXml, "id", NODE_STRING_TO_INT);
		struXml.OutOfElem();
	}
	
	return dwID;
}