

#include "stdafx.h"
#include "InfoDiffusionParamsConvert.h"

/** @fn          DWORD GetResponseStatusID(const char* pXmlBuf)
 *  @brief       提取ResponseStatus的ID
 *  @param (in)  const char* pXmlBuf xml参数
 *  @return      DWORD
 */
DWORD GetResponseStatusID(const char* pXmlBuf)
{
	if (pXmlBuf == NULL)
	{
		return 0;
	}
	
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	DWORD dwID;
	if (struXml.FindElem("ResponseStatus") && struXml.IntoElem())
	{
		ConvertSingleNodeData(&dwID, struXml, "ID", NODE_STRING_TO_INT);
		struXml.OutOfElem();
		return dwID;
	}
	
	return 0;
}

/** @fn          BOOL ConvertMaterialParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
 *  @brief       素材转换 xml转结构体
 *  @param (in)  CXmlBase& struXml xml对象
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertMaterialParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_MATERIAL lpMaterial = (LPNET_DVR_MATERIAL)pStruct;
	
	if (struXml.FindElem("Material") && struXml.IntoElem())
	{
		ConvertSingleNodeData(&lpMaterial->dwMaterialID, struXml, "id", NODE_STRING_TO_INT);
		ConvertSingleNodeData(lpMaterial->szMaterialName, struXml, "materialName", NODE_STRING_TO_ARRAY, MAX_LEN_NAME);
		ConvertSingleNodeData(lpMaterial->szMaterialRemarks, struXml, "materialRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
		ConvertSingleNodeData(lpMaterial->szMaterialType, struXml, "materialType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(lpMaterial->szApprove, struXml, "approveState", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(lpMaterial->szApproveRemarks, struXml, "approveRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
		ConvertSingleNodeData(lpMaterial->szSharePropery, struXml, "shareProperty", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(lpMaterial->szUploadUser, struXml, "uploadUser", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(lpMaterial->szUploadTime, struXml, "uploadTime", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		if (0 == strcmp(lpMaterial->szMaterialType, "static"))
		{
			if (struXml.FindElem("StaticMaterial") && struXml.IntoElem())
			{
				char szStaticMaterialType[MAX_LEN_32] = {0};
				ConvertSingleNodeData(szStaticMaterialType, struXml, "staticMaterialType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				memcpy(lpMaterial->struStaticMaterial.szStaticMaterialType, szStaticMaterialType, sizeof(szStaticMaterialType));
				if (0 == strcmp(szStaticMaterialType, "picture"))
				{
					ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "picFormat", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				}
				else if (0 == strcmp(szStaticMaterialType, "flash"))
				{
					ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "flashFormat", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				}
				else if (0 == strcmp(szStaticMaterialType, "audio"))
				{
					ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "audioFormat", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				}
				else if (0 == strcmp(szStaticMaterialType, "video"))
				{
					ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "videoFormat", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				}
				else if (0 == strcmp(szStaticMaterialType, "document"))
				{
					ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "documentFormat", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				}
				else if (0 == strcmp(szStaticMaterialType, "template"))
				{
					ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "templateFormat", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				}
				ConvertSingleNodeData(&lpMaterial->struStaticMaterial.dwFileSize, struXml, "fileSize", NODE_STRING_TO_INT);
				ConvertSingleNodeData(&lpMaterial->struStaticMaterial.dwDuration, struXml, "duration", NODE_STRING_TO_INT);
				struXml.OutOfElem();
			}
		}
		else if (0 == strcmp(lpMaterial->szMaterialType, "dynamic"))
		{
			if (struXml.FindElem("DynamicMaterial") && struXml.IntoElem())
			{
				char szDynamicMaterialType[MAX_LEN_32] = {0};
				ConvertSingleNodeData(szDynamicMaterialType, struXml, "dynamicMaterialType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				memcpy(lpMaterial->struDynamicMaterial.szDynamicMaterialType, szDynamicMaterialType, sizeof(szDynamicMaterialType));
				if (0 == strcmp(szDynamicMaterialType, "streamMedia"))
				{
					if (struXml.FindElem("StreamMedia") && struXml.IntoElem())
					{
						if (struXml.FindElem("Address") && struXml.IntoElem())
						{
							char szAddressType[MAX_LEN_32] = {0};
							ConvertSingleNodeData(szAddressType, struXml, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
							memcpy(lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.szAddressType, szAddressType, sizeof(szAddressType));
							if (0 == strcmp(szAddressType, "hostname"))
							{
								ConvertSingleNodeData(lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.szHostName, struXml, "hostName", NODE_STRING_TO_ARRAY, MAX_LEN_32);
							}
							else if (0 == strcmp(szAddressType, "ipaddress"))
							{
								if (struXml.FindElem("IpAddress") && struXml.IntoElem())
								{
									char szIPVersion[MAX_LEN_32] = {0};
									ConvertSingleNodeData(szIPVersion, struXml, "ipVersion", NODE_STRING_TO_ARRAY, MAX_LEN_32);
									if (0 == strcmp(szIPVersion, "v4"))
									{
										ConvertSingleNodeData(lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.struIPAddr.szIpV4, struXml, "ipAddress", NODE_STRING_TO_ARRAY, MAX_LEN_32);
									}
									else if (0 == strcmp(szIPVersion, "v6"))
									{
										ConvertSingleNodeData(lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.struIPAddr.szIpV6, struXml, "ipAddress", NODE_STRING_TO_ARRAY, MAX_LEN_128);
									}
									struXml.OutOfElem();
								}
							}
							ConvertSingleNodeData(&lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.dwPortNo, struXml, "portNo", NODE_STRING_TO_INT);
							struXml.IntoElem();
						}
						ConvertSingleNodeData(lpMaterial->struDynamicMaterial.struStreamMedia.szUrl, struXml, "url", NODE_STRING_TO_ARRAY, MAX_LEN_URL);
						struXml.OutOfElem();
					}
				}
				else if (0 == strcmp(szDynamicMaterialType, "web"))
				{
					ConvertSingleNodeData(lpMaterial->struDynamicMaterial.szWebUrl, struXml, "url", NODE_STRING_TO_ARRAY, MAX_LEN_URL);
				}
				else if (0 == strcmp(szDynamicMaterialType, "rss"))
				{
					ConvertSingleNodeData(lpMaterial->struDynamicMaterial.szRssUrl, struXml, "url", NODE_STRING_TO_ARRAY, MAX_LEN_URL);
				}
				struXml.OutOfElem();
			}
		}
		struXml.OutOfElem();
		return TRUE;
	}

	return FALSE;
}

/** @fn          BOOL ConvertMaterialParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       素材转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
 BOOL ConvertMaterialParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 {
	 if (pXmlBuf == NULL || pStruct == NULL)
	 {
		 return FALSE;
	 }
	 LPNET_DVR_MATERIAL lpMaterial = (LPNET_DVR_MATERIAL)pStruct;
	 if (lpMaterial->dwSize != sizeof(NET_DVR_MATERIAL))
	 {
		 return FALSE;
	 }
	 CXmlBase struXml;
	 if (struXml.Parse(pXmlBuf) == NULL)
	 {
		 return FALSE;
	 }
	 
	 return ConvertMaterialParamsXmlToStru(struXml, pStruct);
 }

 /** @fn          BOOL ConvertMaterialParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
  *  @brief       素材转换 结构体转xml
  *  @param (in)  LPVOID pStruct 结构体参数
  *  @param (out) const char* pXmlBuf xml参数
  *  @param (out) DWORD &dwXmlLen xml长度
  *  @return      BOOL
  */
BOOL ConvertMaterialParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_MATERIAL lpMaterial = (LPNET_DVR_MATERIAL)pStruct;
	if (lpMaterial->dwSize != sizeof(NET_DVR_MATERIAL))
	{
		return FALSE;
	}
	
	CXmlBase struXml;
	struXml.CreateRoot("Material");
	struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(&lpMaterial->dwMaterialID, struXml, "id", NODE_INT_TO_STRING);
	ConvertSingleNodeData(lpMaterial->szMaterialName, struXml, "materialName", NODE_ARRAY_TO_STRING, MAX_LEN_NAME);
	ConvertSingleNodeData(lpMaterial->szMaterialRemarks, struXml, "materialRemarks", NODE_ARRAY_TO_STRING, MAX_LEN_REMARKS);
	ConvertSingleNodeData(lpMaterial->szMaterialType, struXml, "materialType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpMaterial->szApprove, struXml, "approveState", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpMaterial->szApproveRemarks, struXml, "approveRemarks", NODE_ARRAY_TO_STRING, MAX_LEN_REMARKS);
	ConvertSingleNodeData(lpMaterial->szSharePropery, struXml, "shareProperty", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpMaterial->szUploadUser, struXml, "uploadUser", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpMaterial->szUploadTime, struXml, "uploadTime", NODE_ARRAY_TO_STRING, MAX_LEN_32);
    ConvertSingleNodeData(&lpMaterial->dwOrgNo,struXml, "orgNo", NODE_INT_TO_STRING);
	if (0 == strcmp(lpMaterial->szMaterialType, "static"))
	{
		if (struXml.AddNode("StaticMaterial"))
		{
			char szStaticMaterialType[MAX_LEN_32] = {0};
			memcpy(szStaticMaterialType, lpMaterial->struStaticMaterial.szStaticMaterialType, sizeof(lpMaterial->struStaticMaterial.szStaticMaterialType));
			ConvertSingleNodeData(szStaticMaterialType, struXml, "staticMaterialType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
			if (0 == strcmp(szStaticMaterialType, "picture"))
			{
				ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "picFormat", NODE_ARRAY_TO_STRING, MAX_LEN_32);
			}
			else if (0 == strcmp(szStaticMaterialType, "flash"))
			{
				ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "flashFormat", NODE_ARRAY_TO_STRING, MAX_LEN_32);
			}
			else if (0 == strcmp(szStaticMaterialType, "audio"))
			{
				ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "audioFormat", NODE_ARRAY_TO_STRING, MAX_LEN_32);
			}
			else if (0 == strcmp(szStaticMaterialType, "video"))
			{
				ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "videoFormat", NODE_ARRAY_TO_STRING, MAX_LEN_32);
			}
			else if (0 == strcmp(szStaticMaterialType, "document"))
			{
				ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "documentFormat", NODE_ARRAY_TO_STRING, MAX_LEN_32);
			}
			else if (0 == strcmp(szStaticMaterialType, "template"))
			{
				ConvertSingleNodeData(lpMaterial->struStaticMaterial.szStaticMaterialFormat, struXml, "templateFormat", NODE_ARRAY_TO_STRING, MAX_LEN_32);
			}
			ConvertSingleNodeData(&lpMaterial->struStaticMaterial.dwFileSize, struXml, "fileSize", NODE_DWORD_TO_STRING);
			ConvertSingleNodeData(&lpMaterial->struStaticMaterial.dwDuration, struXml, "duration", NODE_INT_TO_STRING);
			if (0 == strcmp(szStaticMaterialType, "clock"))
			{
				ConvertClockParam(lpMaterial->struStaticMaterial.struLock,struXml);
			}
			else if (0 == strcmp(szStaticMaterialType, "weather"))
			{
				ConvertWeatherParam(lpMaterial->struStaticMaterial.struWeather,struXml);
			}
			struXml.OutOfElem();
		}
	}
	else if (0 == strcmp(lpMaterial->szMaterialType, "dynamic"))
	{
		if (struXml.AddNode("DynamicMaterial"))
		{
			char szDynamicMaterialType[MAX_LEN_32] = {0};
			memcpy(szDynamicMaterialType, lpMaterial->struDynamicMaterial.szDynamicMaterialType, sizeof(lpMaterial->struDynamicMaterial.szDynamicMaterialType));
			ConvertSingleNodeData(szDynamicMaterialType, struXml, "dynamicMaterialType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
			if (0 == strcmp(szDynamicMaterialType, "streamMedia"))
			{
				if (struXml.AddNode("StreamMedia"))
				{
					if (struXml.AddNode("Address"))
					{
						char szAddressType[MAX_LEN_32] = {0};
						memcpy(szAddressType, lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.szAddressType, sizeof(lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.szAddressType));
						ConvertSingleNodeData(szAddressType, struXml, "addressingFormatType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
						if (0 == strcmp(szAddressType, "hostname"))
						{
							ConvertSingleNodeData(lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.szHostName, struXml, "hostName", NODE_ARRAY_TO_STRING, MAX_LEN_32);
						}
						else if (0 == strcmp(szAddressType, "ipaddress"))
						{
							if (struXml.AddNode("IpAddress"))
							{
								char szIPVersion[MAX_LEN_32] = {0};
								if (strlen(lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.struIPAddr.szIpV4))
								{
									memcpy(szIPVersion, "v4", sizeof("v4"));
									ConvertSingleNodeData(szIPVersion, struXml, "ipVersion", NODE_ARRAY_TO_STRING, MAX_LEN_32);
									ConvertSingleNodeData(lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.struIPAddr.szIpV4, struXml, "ipAddress", NODE_ARRAY_TO_STRING, MAX_LEN_32);
								}
								else if (strlen(lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.struIPAddr.szIpV6))
								{
									memcpy(szIPVersion, "v6", sizeof("v6"));
									ConvertSingleNodeData(szIPVersion, struXml, "ipVersion", NODE_ARRAY_TO_STRING, MAX_LEN_32);
									ConvertSingleNodeData(lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.struIPAddr.szIpV6, struXml, "ipAddress", NODE_ARRAY_TO_STRING, MAX_LEN_128);
								}
								struXml.OutOfElem();
							}
						}
						ConvertSingleNodeData(&lpMaterial->struDynamicMaterial.struStreamMedia.struAddress.dwPortNo, struXml, "portNo", NODE_INT_TO_STRING);
						struXml.OutOfElem();
					}
					ConvertSingleNodeData(lpMaterial->struDynamicMaterial.struStreamMedia.szUrl, struXml, "url", NODE_ARRAY_TO_STRING, MAX_LEN_URL);
					struXml.OutOfElem();
				}
			}
			else if (0 == strcmp(szDynamicMaterialType, "web"))
			{
				ConvertSingleNodeData(lpMaterial->struDynamicMaterial.szWebUrl, struXml, "url", NODE_ARRAY_TO_STRING, MAX_LEN_URL);
			}
			else if (0 == strcmp(szDynamicMaterialType, "rss"))
			{
				ConvertSingleNodeData(lpMaterial->struDynamicMaterial.szRssUrl, struXml, "url", NODE_ARRAY_TO_STRING, MAX_LEN_URL);
			}
			struXml.OutOfElem();
		}
	}

	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}

	return TRUE;
}

/** @fn          BOOL ConvertMaterialParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       素材列表转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertMaterialParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_MATERIAL_LIST lpMaterialList = (LPNET_DVR_MATERIAL_LIST)pStruct;
	if (lpMaterialList->dwSize != sizeof(NET_DVR_MATERIAL_LIST))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	
	if (struXml.FindElem("MaterialList") && struXml.IntoElem())
	{
		int nMaterialCnt= 0;
		LPNET_DVR_MATERIAL lpMaterial = &lpMaterialList->struMaterialList[nMaterialCnt];
		if (ConvertMaterialParamsXmlToStru(struXml, lpMaterial))
		{
			nMaterialCnt++;
			lpMaterial = &lpMaterialList->struMaterialList[nMaterialCnt];
			while (struXml.NextSibElem())
			{	
				ConvertMaterialParamsXmlToStru(struXml, lpMaterial);
				nMaterialCnt++;
				if (nMaterialCnt >= MAX_NUM_MATERIAL)
				{
					break;
				}
				lpMaterial = &lpMaterialList->struMaterialList[nMaterialCnt];
			}
		}
		struXml.OutOfElem();
		return TRUE;
	}
	
	return FALSE;
}

 /** @fn          BOOL ConvertMaterialSearchDescriptionParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
  *  @brief       素材查询条件转换 结构体转xml
  *  @param (in)  LPVOID pStruct 结构体参数
  *  @param (out) const char* pXmlBuf xml参数
  *  @param (out) DWORD &dwXmlLen xml长度
  *  @return      BOOL
  */
BOOL ConvertMaterialSearchDescriptionParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	
	LPNET_DVR_MATERIAL_SEARCH_DESCRIPTION lpDescription = (LPNET_DVR_MATERIAL_SEARCH_DESCRIPTION)pStruct;
	CXmlBase struXml;
	struXml.CreateRoot("MaterialSearchDescription");
	struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(lpDescription->sSearchID, struXml, "searchID", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpDescription->sApproveState, struXml, "approveState", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpDescription->sMaterialType, struXml, "materialType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpDescription->sShareProperty, struXml, "shareProperty", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (strlen(lpDescription->sUploader) != 0)
	{
		ConvertSingleNodeData(lpDescription->sUploader, struXml, "uploader", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	}
	if (0 == strcmp(lpDescription->sMaterialType, "static"))
	{
		ConvertSingleNodeData(lpDescription->sStaticMaterialType, struXml, "staticMaterialType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
		ConvertSingleNodeData(&lpDescription->dwMinStaticMaterialSize, struXml, "minStaticMaterialSize", NODE_INT_TO_STRING);
		if (lpDescription->dwMaxStaticMaterialSize != 0)
		{
			ConvertSingleNodeData(&lpDescription->dwMaxStaticMaterialSize, struXml, "maxStaticMaterialSize", NODE_INT_TO_STRING);
		}
	}
	else if (0 == strcmp(lpDescription->sMaterialType, "dynamic"))
	{
		ConvertSingleNodeData(lpDescription->sDynamicMaterialType, struXml, "dynamicMaterialType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	}
	if (struXml.AddNode("TimeSpanList"))
	{
		if (struXml.AddNode("TimeSpan"))
		{
			ConvertTimeNodeData(struXml, &lpDescription->struTimeRange.struBeginTime, "startTime", FALSE);
			ConvertTimeNodeData(struXml, &lpDescription->struTimeRange.struEndTime, "endTime", FALSE);
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
	}
	if (lpDescription->dwMaxResults != 0)
	{
		ConvertSingleNodeData(&lpDescription->dwMaxResults, struXml, "maxResults", NODE_INT_TO_STRING);
	}
	ConvertSingleNodeData(&lpDescription->dwSearchResultsPosition, struXml, "searchResultsPosition", NODE_INT_TO_STRING);

	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}
	
	return TRUE;
}

/** @fn          BOOL ConvertMaterialSearchResultXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       素材查询结果转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertMaterialSearchResultXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	
	LPNET_DVR_MATERIAL_SEARCH_RESULT lpResult = (LPNET_DVR_MATERIAL_SEARCH_RESULT)pStruct;
	if (struXml.FindElem("MaterialSearchResult") && struXml.IntoElem())
	{
		ConvertSingleNodeData(lpResult->sSearchID, struXml, "searchID", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(&lpResult->bResponseStatus, struXml, "responseStatus", NODE_STRING_TO_BOOL);
		ConvertSingleNodeData(lpResult->sResponseStatusString, struXml, "responseStatusString", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(&lpResult->dwNumOfMatches, struXml, "numOfMatches", NODE_STRING_TO_INT);
        ConvertSingleNodeData(&lpResult->dwTotalMatches, struXml, "totalMatches", NODE_STRING_TO_INT);
		if (struXml.FindElem("MaterialList") && struXml.IntoElem())
		{
			int nMaterialCnt= 0;
			LPNET_DVR_MATERIAL lpMaterial = &lpResult->struMaterialList[nMaterialCnt];
			if (ConvertMaterialParamsXmlToStru(struXml, lpMaterial))
			{
				nMaterialCnt++;
				lpMaterial = &lpResult->struMaterialList[nMaterialCnt];
				while (struXml.NextSibElem())
				{	
					ConvertMaterialParamsXmlToStru(struXml, lpMaterial);
					nMaterialCnt++;
					if (nMaterialCnt >= MAX_NUM_MATERIAL)
					{
						break;
					}
					lpMaterial = &lpResult->struMaterialList[nMaterialCnt];
				}
			}
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
	}
	
	return TRUE;
}

/** @fn          BOOL ConvertPageParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
 *  @brief       页面转换 xml转结构体
 *  @param (in)  CXmlBase& struXml xml对象
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertPageParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PAGE lpPage = (LPNET_DVR_PAGE)pStruct;

	if (struXml.FindElem("Page") && struXml.IntoElem())
	{
		ConvertSingleNodeData(&lpPage->dwPageID, struXml, "id", NODE_STRING_TO_INT);
		if (struXml.FindElem("PageBasicInfo") && struXml.IntoElem())
		{
			ConvertSingleNodeData(lpPage->struBasicInfo.sPageName, struXml, "pageName", NODE_STRING_TO_ARRAY, MAX_LEN_NAME);
			if (struXml.FindElem("BackgroundColor") && struXml.IntoElem())
			{
				DWORD dwRGB = 0;
				ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_STRING_TO_INT);
				lpPage->struBasicInfo.struBkColor.dwRed = dwRGB>>16;
				lpPage->struBasicInfo.struBkColor.dwGreen = dwRGB>>8&0x000000ff;
				lpPage->struBasicInfo.struBkColor.dwBlue = dwRGB&0x000000ff;
				struXml.OutOfElem();
			}
			ConvertSingleNodeData(lpPage->struBasicInfo.sPlayMode, struXml, "playDurationMode", NODE_STRING_TO_ARRAY, MAX_LEN_32);
			if (0 == strcmp(lpPage->struBasicInfo.sPlayMode, "selfDefine"))
			{
				ConvertSingleNodeData(&lpPage->struBasicInfo.dwPlayDuration, struXml, "playDuration", NODE_STRING_TO_INT);
			}
			ConvertSingleNodeData(&lpPage->struBasicInfo.dwSwitchDuraton, struXml, "switchDuration", NODE_STRING_TO_INT);
			ConvertSingleNodeData(lpPage->struBasicInfo.szSwitchEffect, struXml, "switchEffect", NODE_STRING_TO_ARRAY, MAX_LEN_32);
			ConvertSingleNodeData(&lpPage->struBasicInfo.dwBackgroundPic, struXml, "backgroundPic", NODE_STRING_TO_INT);
			struXml.OutOfElem();
		}
		if (struXml.FindElem("WindowsList") && struXml.IntoElem())
		{
			int nContentCnt = 0;
			if (struXml.FindElem("Windows") && struXml.IntoElem())
			{
				ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].dwContentID, struXml, "id", NODE_STRING_TO_INT);
				if (struXml.FindElem("Position") && struXml.IntoElem())
				{
					ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwPositionX, struXml, "positionX", NODE_STRING_TO_INT);
					ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwPositionY, struXml, "positionY", NODE_STRING_TO_INT);
					ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwHeight, struXml, "height", NODE_STRING_TO_INT);
					ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwWidth, struXml, "width", NODE_STRING_TO_INT);
					struXml.OutOfElem();
				}
				ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].dwLayerID, struXml, "layerNo", NODE_STRING_TO_INT);
				if (struXml.FindElem("WinMaterialInfo") && struXml.IntoElem())
				{
					ConvertSingleNodeData(lpPage->struContentList[nContentCnt].sWinMaterialType, struXml, "materialType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
					if (0 == strcmp(lpPage->struContentList[nContentCnt].sWinMaterialType, "static"))
					{
						ConvertSingleNodeData(lpPage->struContentList[nContentCnt].sStaticMaterialType, struXml, "staticMaterialType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
					}
					struXml.OutOfElem();
				}
				if (struXml.FindElem("PlayItemList") && struXml.IntoElem())
				{
					int nPlayCnt = 0;
					if (struXml.FindElem("PlayItem") && struXml.IntoElem())
					{
						ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwPlayID, struXml, "id", NODE_STRING_TO_INT);
						ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwMaterialID, struXml, "materialNo", NODE_STRING_TO_INT);
						ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szPlayEffect, struXml, "playEffect", NODE_STRING_TO_ARRAY, MAX_LEN_32);
						if (0 == strcmp(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szPlayEffect, "marquee"))
						{
							if (struXml.FindElem("MarqueeInfo") && struXml.IntoElem())
							{
								ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.szScrollType, struXml, "scrollType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
								ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.szScrollDirection, struXml, "scrollDeriction", NODE_STRING_TO_ARRAY, MAX_LEN_32);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.dwScrollSpeed, struXml, "scrollSpeed", NODE_STRING_TO_INT);
								struXml.OutOfElem();
							}
						}
						if (struXml.FindElem("PlayDuration") && struXml.IntoElem())
						{
							ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struPlayDuration.szDurationType, struXml, "durationType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struPlayDuration.dwDuration, struXml, "duration", NODE_STRING_TO_INT);
							struXml.OutOfElem();
						}

						if(struXml.FindElem("CharactersEffect")&&struXml.IntoElem())
						{
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwFontSize, struXml, "fontSize", NODE_STRING_TO_INT);
							if (struXml.FindElem("FontColor") && struXml.IntoElem())
							{
								DWORD dwRGB = 0;
								ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_STRING_TO_INT);
								lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwRed = dwRGB>>16;
								lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwGreen = dwRGB>>8&0x000000ff;
								lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwBlue = dwRGB&0x000000ff;
								struXml.OutOfElem();
							}
							
							if (struXml.FindElem("BackColor") && struXml.IntoElem())
							{
								DWORD dwRGB = 0;
								ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_STRING_TO_INT);
								lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwRed = dwRGB>>16;
								lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwGreen = dwRGB>>8&0x000000ff;
								lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwBlue = dwRGB&0x000000ff;
								struXml.OutOfElem();
							}
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwBackTransparent, struXml, "backTransparent", NODE_STRING_TO_INT);
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.bySubtitlesEnabled, struXml, "subtitlesEnabled", NODE_STRING_TO_BOOL);
							ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.szScrollDirection, struXml, "scrollDirection", NODE_STRING_TO_ARRAY,MAX_LEN_32);
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwScrollSpeed, struXml, "scrollSpeed", NODE_STRING_TO_INT);

							struXml.OutOfElem();
						}
						ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szSwitchEffect, struXml, "switchEffect", NODE_STRING_TO_ARRAY,MAX_LEN_32);
						nPlayCnt++;
						struXml.OutOfElem();
						while (struXml.NextSibElem() && struXml.IntoElem())
						{
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwPlayID, struXml, "id", NODE_STRING_TO_INT);
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwMaterialID, struXml, "materialNo", NODE_STRING_TO_INT);
							ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szPlayEffect, struXml, "playEffect", NODE_STRING_TO_ARRAY, MAX_LEN_32);
							if (0 == strcmp(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szPlayEffect, "marquee"))
							{
								if (struXml.FindElem("MarqueeInfo") && struXml.IntoElem())
								{
									ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.szScrollType, struXml, "scrollType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
									ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.szScrollDirection, struXml, "scrollDeriction", NODE_STRING_TO_ARRAY, MAX_LEN_32);
									ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.dwScrollSpeed, struXml, "scrollSpeed", NODE_STRING_TO_INT);
									struXml.OutOfElem();
								}
							}
							if (struXml.FindElem("PlayDuration") && struXml.IntoElem())
							{
								ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struPlayDuration.szDurationType, struXml, "durationType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struPlayDuration.dwDuration, struXml, "duration", NODE_STRING_TO_INT);
								struXml.OutOfElem();
							}
							if(struXml.FindElem("CharactersEffect")&&struXml.IntoElem())
							{
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwFontSize, struXml, "fontSize", NODE_STRING_TO_INT);
								if (struXml.FindElem("FontColor") && struXml.IntoElem())
								{
									DWORD dwRGB = 0;
									ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_STRING_TO_INT);
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwRed = dwRGB>>16;
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwGreen = dwRGB>>8&0x000000ff;
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwBlue = dwRGB&0x000000ff;
									struXml.OutOfElem();
								}
								
								if (struXml.FindElem("BackColor") && struXml.IntoElem())
								{
									DWORD dwRGB = 0;
									ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_STRING_TO_INT);
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwRed = dwRGB>>16;
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwGreen = dwRGB>>8&0x000000ff;
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwBlue = dwRGB&0x000000ff;
									struXml.OutOfElem();
								}
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwBackTransparent, struXml, "backTransparent", NODE_STRING_TO_INT);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.bySubtitlesEnabled, struXml, "subtitlesEnabled", NODE_STRING_TO_BOOL);
								ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.szScrollDirection, struXml, "scrollDirection", NODE_STRING_TO_ARRAY,MAX_LEN_32);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwScrollSpeed, struXml, "scrollSpeed", NODE_STRING_TO_INT);
								
								struXml.OutOfElem();
							}
							ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szSwitchEffect, struXml, "switchEffect", NODE_STRING_TO_ARRAY,MAX_LEN_32);
						
							nPlayCnt++;
							if (nPlayCnt >= MAX_ITEMS_A_PLAYLIST)
							{
								break;
							}
							struXml.OutOfElem();
						}
					}
					struXml.OutOfElem();
				}
				nContentCnt++;
				struXml.OutOfElem();
				while (struXml.NextSibElem() && struXml.IntoElem())
				{
					ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].dwContentID, struXml, "id", NODE_STRING_TO_INT);
					if (struXml.FindElem("Position") && struXml.IntoElem())
					{
						ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwPositionX, struXml, "positionX", NODE_STRING_TO_INT);
						ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwPositionY, struXml, "positionY", NODE_STRING_TO_INT);
						ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwHeight, struXml, "height", NODE_STRING_TO_INT);
						ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwWidth, struXml, "width", NODE_STRING_TO_INT);
						struXml.OutOfElem();
					}
					ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].dwLayerID, struXml, "layerNo", NODE_STRING_TO_INT);
					if (struXml.FindElem("WinMaterialInfo") && struXml.IntoElem())
					{
						ConvertSingleNodeData(lpPage->struContentList[nContentCnt].sWinMaterialType, struXml, "materialType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
						if (0 == strcmp(lpPage->struContentList[nContentCnt].sWinMaterialType, "static"))
						{
							ConvertSingleNodeData(lpPage->struContentList[nContentCnt].sStaticMaterialType, struXml, "staticMaterialType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
						}
						struXml.OutOfElem();
					}
					if (struXml.FindElem("PlayItemList") && struXml.IntoElem())
					{
						int nPlayCnt = 0;
						if (struXml.FindElem("PlayItem") && struXml.IntoElem())
						{
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwPlayID, struXml, "id", NODE_STRING_TO_INT);
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwMaterialID, struXml, "materialNo", NODE_STRING_TO_INT);
							ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szPlayEffect, struXml, "playEffect", NODE_STRING_TO_ARRAY, MAX_LEN_32);
							if (0 == strcmp(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szPlayEffect, "marquee"))
							{
								if (struXml.FindElem("MarqueeInfo") && struXml.IntoElem())
								{
									ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.szScrollType, struXml, "scrollType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
									ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.szScrollDirection, struXml, "scrollDeriction", NODE_STRING_TO_ARRAY, MAX_LEN_32);
									ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.dwScrollSpeed, struXml, "scrollSpeed", NODE_STRING_TO_INT);
									struXml.OutOfElem();
								}
							}
							if (struXml.FindElem("PlayDuration") && struXml.IntoElem())
							{
								ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struPlayDuration.szDurationType, struXml, "durationType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struPlayDuration.dwDuration, struXml, "duration", NODE_STRING_TO_INT);
								struXml.OutOfElem();
							}
							if(struXml.FindElem("CharactersEffect")&&struXml.IntoElem())
							{
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwFontSize, struXml, "fontSize", NODE_STRING_TO_INT);
								if (struXml.FindElem("FontColor") && struXml.IntoElem())
								{
									DWORD dwRGB = 0;
									ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_STRING_TO_INT);
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwRed = dwRGB>>16;
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwGreen = dwRGB>>8&0x000000ff;
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwBlue = dwRGB&0x000000ff;
									struXml.OutOfElem();
								}
								
								if (struXml.FindElem("BackColor") && struXml.IntoElem())
								{
									DWORD dwRGB = 0;
									ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_STRING_TO_INT);
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwRed = dwRGB>>16;
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwGreen = dwRGB>>8&0x000000ff;
									lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwBlue = dwRGB&0x000000ff;
									struXml.OutOfElem();
								}
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwBackTransparent, struXml, "backTransparent", NODE_STRING_TO_INT);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.bySubtitlesEnabled, struXml, "subtitlesEnabled", NODE_STRING_TO_BOOL);
								ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.szScrollDirection, struXml, "scrollDirection", NODE_STRING_TO_ARRAY,MAX_LEN_32);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwScrollSpeed, struXml, "scrollSpeed", NODE_STRING_TO_INT);
								
								struXml.OutOfElem();
							}
							ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szSwitchEffect, struXml, "switchEffect", NODE_STRING_TO_ARRAY,MAX_LEN_32);
						
							nPlayCnt++;
							struXml.OutOfElem();
							while (struXml.NextSibElem() && struXml.IntoElem())
							{
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwPlayID, struXml, "id", NODE_STRING_TO_INT);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwMaterialID, struXml, "materialNo", NODE_STRING_TO_INT);
								ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szPlayEffect, struXml, "playEffect", NODE_STRING_TO_ARRAY, MAX_LEN_32);
								if (0 == strcmp(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szPlayEffect, "marquee"))
								{
									if (struXml.FindElem("MarqueeInfo") && struXml.IntoElem())
									{
										ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.szScrollType, struXml, "scrollType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
										ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.szScrollDirection, struXml, "scrollDeriction", NODE_STRING_TO_ARRAY, MAX_LEN_32);
										ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.dwScrollSpeed, struXml, "scrollSpeed", NODE_STRING_TO_INT);
										struXml.OutOfElem();
									}
								}
								if (struXml.FindElem("PlayDuration") && struXml.IntoElem())
								{
									ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struPlayDuration.szDurationType, struXml, "durationType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
									ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struPlayDuration.dwDuration, struXml, "duration", NODE_STRING_TO_INT);
									struXml.OutOfElem();
								}
								if(struXml.FindElem("CharactersEffect")&&struXml.IntoElem())
								{
									ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwFontSize, struXml, "fontSize", NODE_STRING_TO_INT);
									if (struXml.FindElem("FontColor") && struXml.IntoElem())
									{
										DWORD dwRGB = 0;
										ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_STRING_TO_INT);
										lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwRed = dwRGB>>16;
										lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwGreen = dwRGB>>8&0x000000ff;
										lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwBlue = dwRGB&0x000000ff;
										struXml.OutOfElem();
									}
									
									if (struXml.FindElem("BackColor") && struXml.IntoElem())
									{
										DWORD dwRGB = 0;
										ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_STRING_TO_INT);
										lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwRed = dwRGB>>16;
										lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwGreen = dwRGB>>8&0x000000ff;
										lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwBlue = dwRGB&0x000000ff;
										struXml.OutOfElem();
									}
									ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwBackTransparent, struXml, "backTransparent", NODE_STRING_TO_INT);
									ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.bySubtitlesEnabled, struXml, "subtitlesEnabled", NODE_STRING_TO_BOOL);
									ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.szScrollDirection, struXml, "scrollDirection", NODE_STRING_TO_ARRAY,MAX_LEN_32);
									ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwScrollSpeed, struXml, "scrollSpeed", NODE_STRING_TO_INT);
									
									struXml.OutOfElem();
								}
								ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szSwitchEffect, struXml, "switchEffect", NODE_STRING_TO_ARRAY,MAX_LEN_32);
						
								nPlayCnt++;
								if (nPlayCnt >= MAX_ITEMS_A_PLAYLIST)
								{
									break;
								}
								struXml.OutOfElem();
							}
						}
						struXml.OutOfElem();
					}
					nContentCnt++;
					if (nContentCnt >= MAX_CONTENTS_A_PAGE)
					{
						break;
					}
					struXml.OutOfElem();
				}
			}
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
		return TRUE;
	}

	return FALSE;
}

/** @fn          BOOL ConvertPageParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       页面转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertPageParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PAGE lpPage = (LPNET_DVR_PAGE)pStruct;
	if (lpPage->dwSize != sizeof(NET_DVR_PAGE))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	
	return ConvertPageParamsXmlToStru(struXml, pStruct);
}

/** @fn          BOOL ConvertPageParamsStruToXml(LPVOID pStruct, CXmlBase& struXml)
 *  @brief       页面转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) CXmlBase& struXml xml对象
 *  @return      BOOL
 */
BOOL ConvertPageParamsStruToXml(LPVOID pStruct, CXmlBase& struXml)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PAGE lpPage = (LPNET_DVR_PAGE)pStruct;
	
	ConvertSingleNodeData(&lpPage->dwPageID, struXml, "id", NODE_INT_TO_STRING);
	if (struXml.AddNode("PageBasicInfo"))
	{
		ConvertSingleNodeData(lpPage->struBasicInfo.sPageName, struXml, "pageName", NODE_ARRAY_TO_STRING, MAX_LEN_NAME);
		if (struXml.AddNode("BackgroundColor"))
		{
			DWORD dwRGB = (lpPage->struBasicInfo.struBkColor.dwRed<<16)|(lpPage->struBasicInfo.struBkColor.dwGreen<<8)|(lpPage->struBasicInfo.struBkColor.dwBlue);
			ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_INT_TO_STRING);
			struXml.OutOfElem();
		}
		ConvertSingleNodeData(lpPage->struBasicInfo.sPlayMode, struXml, "playDurationMode", NODE_ARRAY_TO_STRING, MAX_LEN_32);
		if (0 == strcmp(lpPage->struBasicInfo.sPlayMode, "selfDefine"))
		{
			ConvertSingleNodeData(&lpPage->struBasicInfo.dwPlayDuration, struXml, "playDuration", NODE_ARRAY_TO_STRING);
		}
		ConvertSingleNodeData(&lpPage->struBasicInfo.dwSwitchDuraton, struXml, "switchDuration", NODE_INT_TO_STRING);
		ConvertSingleNodeData(lpPage->struBasicInfo.szSwitchEffect, struXml, "switchEffect", NODE_ARRAY_TO_STRING, MAX_LEN_32);
		ConvertSingleNodeData(&lpPage->struBasicInfo.dwBackgroundPic, struXml, "backgroundPic", NODE_INT_TO_STRING);
		struXml.OutOfElem();
	}
	if (struXml.AddNode("WindowsList"))
	{
		for (int nContentCnt = 0; nContentCnt < MAX_CONTENTS_A_PAGE; nContentCnt++)
		{
			if (0 == lpPage->struContentList[nContentCnt].dwContentID)
			{
				continue;
			}
			if (struXml.AddNode("Windows"))
			{
				ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].dwContentID, struXml, "id", NODE_INT_TO_STRING);
				if (struXml.AddNode("Position"))
				{
					ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwPositionX, struXml, "positionX", NODE_INT_TO_STRING);
					ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwPositionY, struXml, "positionY", NODE_INT_TO_STRING);
					ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwHeight, struXml, "height", NODE_INT_TO_STRING);
					ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPosition.dwWidth, struXml, "width", NODE_INT_TO_STRING);
					struXml.OutOfElem();
				}
				ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].dwLayerID, struXml, "layerNo", NODE_INT_TO_STRING);
				if (struXml.AddNode("WinMaterialInfo"))
				{
					ConvertSingleNodeData(lpPage->struContentList[nContentCnt].sWinMaterialType, struXml, "materialType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
					if (0 == strcmp(lpPage->struContentList[nContentCnt].sWinMaterialType, "static"))
					{
						ConvertSingleNodeData(lpPage->struContentList[nContentCnt].sStaticMaterialType, struXml, "staticMaterialType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
					}
					struXml.OutOfElem();
				}
				if (struXml.AddNode("PlayItemList"))
				{
					for (int nPlayCnt = 0; nPlayCnt < MAX_ITEMS_A_PLAYLIST; nPlayCnt++)
					{
						if (0 == lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwPlayID)
						{
							continue;
						}
						if (struXml.AddNode("PlayItem"))
						{
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwPlayID, struXml, "id", NODE_INT_TO_STRING);
							ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].dwMaterialID, struXml, "materialNo", NODE_INT_TO_STRING);
							ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szPlayEffect, struXml, "playEffect", NODE_ARRAY_TO_STRING, MAX_LEN_32);
							if (0 == strcmp(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szPlayEffect, "marquee"))
							{
								if (struXml.AddNode("MarqueeInfo"))
								{
									ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.szScrollType, struXml, "scrollType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
									ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.szScrollDirection, struXml, "scrollDeriction", NODE_ARRAY_TO_STRING, MAX_LEN_32);
									ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struMarquee.dwScrollSpeed, struXml, "scrollSpeed", NODE_INT_TO_STRING);
									struXml.OutOfElem();
								}
							}
							if (struXml.AddNode("PlayDuration"))
							{
								ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struPlayDuration.szDurationType, struXml, "durationType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struPlayDuration.dwDuration, struXml, "duration", NODE_INT_TO_STRING);
								struXml.OutOfElem();
							}
							if(struXml.AddNode("CharactersEffect"))
							{
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwFontSize, struXml, "fontSize", NODE_INT_TO_STRING);
								if (struXml.AddNode("FontColor"))
								{
									DWORD dwRGB = (lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwRed<<16)|
										(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwGreen<<8)|
										(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struFontColor.dwBlue);
									ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_INT_TO_STRING);
									struXml.OutOfElem();
								}
								if (struXml.AddNode("BackColor"))
								{
									DWORD dwRGB = (lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwRed<<16)|
										(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwGreen<<8)|
										(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.struBackColor.dwBlue);
									ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_INT_TO_STRING);
									struXml.OutOfElem();
								}
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwBackTransparent, struXml, "backTransparent", NODE_INT_TO_STRING);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.bySubtitlesEnabled, struXml, "subtitlesEnabled", NODE_BOOL_TO_STRING);
								ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.szScrollDirection, struXml, "scrollDirection", NODE_ARRAY_TO_STRING, MAX_LEN_32);
								ConvertSingleNodeData(&lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].struCharactersEffect.dwScrollSpeed, struXml, "scrollSpeed", NODE_INT_TO_STRING);
								
								struXml.OutOfElem();
							}
							ConvertSingleNodeData(lpPage->struContentList[nContentCnt].struPlayList[nPlayCnt].szSwitchEffect, struXml, "switchEffect", NODE_ARRAY_TO_STRING,MAX_LEN_32);
								
							struXml.OutOfElem();
						}
					}
					struXml.OutOfElem();
				}
				struXml.OutOfElem();
			}
		}
		struXml.OutOfElem();
	}

	return TRUE;
}

/** @fn          BOOL ConvertPageParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       页面转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertPageParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PAGE lpPage = (LPNET_DVR_PAGE)pStruct;
	if (lpPage->dwSize != sizeof(NET_DVR_PAGE))
	{
		return FALSE;
	}
	
	CXmlBase struXml;
	struXml.CreateRoot("Page");
	struXml.SetAttribute("version", "2.0");

	ConvertPageParamsStruToXml(lpPage, struXml);

	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}

	return TRUE;
}

/** @fn          BOOL ConvertPageParamsXmlToStruList(CXmlBase& struXml, LPVOID pStruct)
 *  @brief       页面列表转换 xml转结构体
 *  @param (in)  CXmlBase& struXml xml对象
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertPageParamsXmlToStruList(CXmlBase& struXml, LPVOID pStruct)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PAGE_LIST lpPageList = (LPNET_DVR_PAGE_LIST)pStruct;
	
	if (struXml.FindElem("PageList") && struXml.IntoElem())
	{
		int nPageCnt = 0;
		LPNET_DVR_PAGE lpPage = &lpPageList->struPageList[nPageCnt];
		if (ConvertPageParamsXmlToStru(struXml, lpPage))
		{
			nPageCnt++;
			lpPage = &lpPageList->struPageList[nPageCnt];
			while (struXml.NextSibElem())
			{
				ConvertPageParamsXmlToStru(struXml, lpPage);
				nPageCnt++;
				if (nPageCnt >= MAX_PAGES_A_PROGRAM)
				{
					break;
				}
				lpPage = &lpPageList->struPageList[nPageCnt];
			}
		}
		struXml.OutOfElem();
		return TRUE;
	}

	return FALSE;
}

/** @fn          BOOL ConvertPageParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       页面列表转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertPageParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PAGE_LIST lpPageList = (LPNET_DVR_PAGE_LIST)pStruct;
	if (lpPageList->dwSize != sizeof(NET_DVR_PAGE_LIST))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}

	return ConvertPageParamsXmlToStruList(struXml, lpPageList);
}

/** @fn          BOOL ConvertProgramParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
 *  @brief       节目转换 xml转结构体
 *  @param (in)  CXmlBase& struXml xml对象
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertProgramParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PROGRAM lpProgram = (LPNET_DVR_PROGRAM)pStruct;

	if (struXml.FindElem("Program") && struXml.IntoElem())
	{
		ConvertSingleNodeData(&lpProgram->dwProgramID, struXml, "id", NODE_STRING_TO_INT);
		ConvertSingleNodeData(lpProgram->szProgramName, struXml, "programName", NODE_STRING_TO_ARRAY, MAX_LEN_NAME);
		ConvertSingleNodeData(lpProgram->szProgramRemarks, struXml, "programRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
		ConvertSingleNodeData(lpProgram->szShareProp, struXml, "shareProperty", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(lpProgram->szApprove, struXml, "approveState", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(lpProgram->szApproveRemarks, struXml, "approveRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		if (struXml.FindElem("Resolution") && struXml.IntoElem())
		{
			ConvertSingleNodeData(&lpProgram->struResolution.dwImageWidth, struXml, "imageWidth", NODE_STRING_TO_INT);
			ConvertSingleNodeData(&lpProgram->struResolution.dwImageHeight, struXml, "imageHeight", NODE_STRING_TO_INT);
			struXml.OutOfElem();
		}
		ConvertSingleNodeData(&lpProgram->dwProgramSize, struXml, "programSize", NODE_STRING_TO_INT);
		ConvertSingleNodeData(&lpProgram->dwProgramLength, struXml, "programLength", NODE_STRING_TO_INT);
		ConvertPageParamsXmlToStruList(struXml, &lpProgram->struPageList);
		struXml.OutOfElem();
		return TRUE;
	}

	return FALSE;
}

/** @fn          BOOL ConvertProgramParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       节目转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertProgramParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PROGRAM lpProgram = (LPNET_DVR_PROGRAM)pStruct;
	if (lpProgram->dwSize != sizeof(NET_DVR_PROGRAM))
	{
		return FALSE;
	}

	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	return ConvertProgramParamsXmlToStru(struXml, lpProgram);
}

/** @fn          BOOL ConvertProgramParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       节目转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertProgramParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PROGRAM lpProgram = (LPNET_DVR_PROGRAM)pStruct;
	if (lpProgram->dwSize != sizeof(NET_DVR_PROGRAM))
	{
		return FALSE;
	}
	
	CXmlBase struXml;
	struXml.CreateRoot("Program");
	struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(&lpProgram->dwProgramID, struXml, "id", NODE_INT_TO_STRING);
	ConvertSingleNodeData(lpProgram->szProgramName, struXml, "programName", NODE_ARRAY_TO_STRING, MAX_LEN_NAME);
	ConvertSingleNodeData(lpProgram->szProgramRemarks, struXml, "programRemarks", NODE_ARRAY_TO_STRING, MAX_LEN_REMARKS);
	ConvertSingleNodeData(lpProgram->szShareProp, struXml, "shareProperty", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpProgram->szApprove, struXml, "approveState", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpProgram->szApproveRemarks, struXml, "approveRemarks", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (struXml.AddNode("Resolution"))
	{
		ConvertSingleNodeData(&lpProgram->struResolution.dwImageWidth, struXml, "imageWidth", NODE_INT_TO_STRING);
		ConvertSingleNodeData(&lpProgram->struResolution.dwImageHeight, struXml, "imageHeight", NODE_INT_TO_STRING);
		struXml.OutOfElem();
	}
	ConvertSingleNodeData(&lpProgram->dwProgramSize, struXml, "programSize", NODE_INT_TO_STRING);
	ConvertSingleNodeData(&lpProgram->dwProgramLength, struXml, "programLength", NODE_INT_TO_STRING);
	if (struXml.AddNode("PageList"))
	{
		for (int nPageCnt = 0; nPageCnt < MAX_PAGES_A_PROGRAM; nPageCnt++)
		{
			if (0 == lpProgram->struPageList.struPageList[nPageCnt].dwPageID)
			{
				continue;
			}
			if (struXml.AddNode("Page"))
			{
				ConvertPageParamsStruToXml(&lpProgram->struPageList.struPageList[nPageCnt], struXml);
				struXml.OutOfElem();
			}
		}
		struXml.OutOfElem();
	}
	
	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}
	
	return TRUE;
}

/** @fn          BOOL ConvertProgramParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       节目列表转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertProgramParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PROGRAM_LIST lpProgramList = (LPNET_DVR_PROGRAM_LIST)pStruct;
	if (lpProgramList->dwSize != sizeof(NET_DVR_PROGRAM_LIST))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	
	if (struXml.FindElem("ProgramList") && struXml.IntoElem())
	{
		int nProCnt = 0;
		LPNET_DVR_PROGRAM lpProgram = &lpProgramList->struProgramList[nProCnt];
		if (ConvertProgramParamsXmlToStru(struXml, lpProgram))
		{
			nProCnt++;
			lpProgram = &lpProgramList->struProgramList[nProCnt];
			while (struXml.NextSibElem())
			{
				ConvertProgramParamsXmlToStru(struXml, lpProgram);
				nProCnt++;
				if (nProCnt >= MAX_NUM_PROGRAM)
				{
					break;
				}
				lpProgram = &lpProgramList->struProgramList[nProCnt];
			}
		}
		struXml.OutOfElem();
		return TRUE;
	}
	
	return FALSE;
}

/** @fn          BOOL ConvertProgramSearchDescriptionParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       节目查询条件转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertProgramSearchDescriptionParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	
	LPNET_DVR_PROGRAM_SEARCH_DESCRIPTION lpDescription = (LPNET_DVR_PROGRAM_SEARCH_DESCRIPTION)pStruct;
	CXmlBase struXml;
	struXml.CreateRoot("ProgramSearchDescription");
	struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(lpDescription->sSearchID, struXml, "searchID", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpDescription->sApproveState, struXml, "approveState", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpDescription->sShareProperty, struXml, "shareProperty", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (strlen(lpDescription->sUploader) != 0)
	{
		ConvertSingleNodeData(lpDescription->sUploader, struXml, "uploader", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	}
	if (lpDescription->struResolution.dwImageWidth != 0 && lpDescription->struResolution.dwImageHeight != 0)
	{
		if (struXml.AddNode("Resolution"))
		{
			ConvertSingleNodeData(&lpDescription->struResolution.dwImageWidth, struXml, "imageWidth", NODE_INT_TO_STRING);
			ConvertSingleNodeData(&lpDescription->struResolution.dwImageHeight, struXml, "imageHeight", NODE_INT_TO_STRING);
			struXml.OutOfElem();
		}
	}
	if (struXml.AddNode("TimeSpanList"))
	{
		if (struXml.AddNode("TimeSpan"))
		{
			ConvertTimeNodeData(struXml, &lpDescription->struTimeRange.struBeginTime, "startTime", FALSE);
			ConvertTimeNodeData(struXml, &lpDescription->struTimeRange.struEndTime, "endTime", FALSE);
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
	}
	if (lpDescription->dwMaxResults != 0)
	{
		ConvertSingleNodeData(&lpDescription->dwMaxResults, struXml, "maxResults", NODE_INT_TO_STRING);
	}
	ConvertSingleNodeData(&lpDescription->dwSearchResultsPosition, struXml, "searchResultsPosition", NODE_INT_TO_STRING);

	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}

	return TRUE;
}

/** @fn          BOOL ConvertProgramSearchResultParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
 *  @brief       节目查询结果转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertProgramSearchResultParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	
	LPNET_DVR_PROGRAM_SEARCH_RESULT lpResult = (LPNET_DVR_PROGRAM_SEARCH_RESULT)pStruct;
	if (struXml.FindElem("ProgramSearchResult") && struXml.IntoElem())
	{
		ConvertSingleNodeData(lpResult->sSearchID, struXml, "searchID", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(&lpResult->bResponseStatus, struXml, "responseStatus", NODE_STRING_TO_BOOL);
		ConvertSingleNodeData(lpResult->sResponseStatusString, struXml, "responseStatusString", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(&lpResult->dwTotalMatches, struXml, "totalMatches", NODE_STRING_TO_INT);
		ConvertSingleNodeData(&lpResult->dwNumOfMatches, struXml, "numOfMatches", NODE_STRING_TO_INT);
		if (struXml.FindElem("MatchElementList") && struXml.IntoElem())
		{
			int iCnt = 0;
			if (struXml.FindElem("MatchElement") && struXml.IntoElem())
			{
				LPNET_DVR_PROGRAM_BASIC_INFO lpProgram = (LPNET_DVR_PROGRAM_BASIC_INFO)&lpResult->struProgramList[iCnt];
				
				ConvertSingleNodeData(&lpProgram->dwProgramID, struXml, "id", NODE_STRING_TO_INT);
				ConvertSingleNodeData(lpProgram->szProgramName, struXml, "programName", NODE_STRING_TO_ARRAY, MAX_LEN_NAME);
				ConvertSingleNodeData(lpProgram->szProgramRemarks, struXml, "programRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
				ConvertSingleNodeData(lpProgram->szShareProp, struXml, "shareProperty", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				ConvertSingleNodeData(lpProgram->szApprove, struXml, "approveState", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				ConvertSingleNodeData(lpProgram->szApproveRemarks, struXml, "approveRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
				if (struXml.FindElem("Resolution") && struXml.IntoElem())
				{
					ConvertSingleNodeData(&lpProgram->struResolution.dwImageWidth, struXml, "imageWidth", NODE_STRING_TO_INT);
					ConvertSingleNodeData(&lpProgram->struResolution.dwImageHeight, struXml, "imageHeight", NODE_STRING_TO_INT);
					struXml.OutOfElem();
				}
				ConvertSingleNodeData(&lpProgram->dwProgramSize, struXml, "programSize", NODE_STRING_TO_INT);
				ConvertSingleNodeData(&lpProgram->dwProgramLength, struXml, "programLength", NODE_STRING_TO_INT);
				
				struXml.OutOfElem();
				iCnt++;
				
				while (struXml.NextSibElem() && struXml.IntoElem())
				{
					LPNET_DVR_PROGRAM_BASIC_INFO lpProgram = (LPNET_DVR_PROGRAM_BASIC_INFO)&lpResult->struProgramList[iCnt];
					
					ConvertSingleNodeData(&lpProgram->dwProgramID, struXml, "id", NODE_STRING_TO_INT);
					ConvertSingleNodeData(lpProgram->szProgramName, struXml, "programName", NODE_STRING_TO_ARRAY, MAX_LEN_NAME);
					ConvertSingleNodeData(lpProgram->szProgramRemarks, struXml, "programRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
					ConvertSingleNodeData(lpProgram->szShareProp, struXml, "shareProperty", NODE_STRING_TO_ARRAY, MAX_LEN_32);
					ConvertSingleNodeData(lpProgram->szApprove, struXml, "approveState", NODE_STRING_TO_ARRAY, MAX_LEN_32);
					ConvertSingleNodeData(lpProgram->szApproveRemarks, struXml, "approveRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
					if (struXml.FindElem("Resolution") && struXml.IntoElem())
					{
						ConvertSingleNodeData(&lpProgram->struResolution.dwImageWidth, struXml, "imageWidth", NODE_STRING_TO_INT);
						ConvertSingleNodeData(&lpProgram->struResolution.dwImageHeight, struXml, "imageHeight", NODE_STRING_TO_INT);
						struXml.OutOfElem();
					}
					ConvertSingleNodeData(&lpProgram->dwProgramSize, struXml, "programSize", NODE_STRING_TO_INT);
					ConvertSingleNodeData(&lpProgram->dwProgramLength, struXml, "programLength", NODE_STRING_TO_INT);
					
					struXml.OutOfElem();
					iCnt++;
					if (iCnt >= MAX_NUM_PROGRAM)
					{
						break;
					}
				}
			}
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
	}

	return TRUE;
}

/** @fn          BOOL ConvertProgramParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
 *  @brief       垫片转换 xml转结构体
 *  @param (in)  CXmlBase& struXml xml对象
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertContainerParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_CONTAINER lpContainer = (LPNET_DVR_CONTAINER)pStruct;

	if (struXml.FindElem("Container") && struXml.IntoElem())
	{
		ConvertSingleNodeData(&lpContainer->dwContainerID, struXml, "id", NODE_STRING_TO_INT);
		ConvertSingleNodeData(lpContainer->szContainerName, struXml, "name", NODE_STRING_TO_ARRAY, MAX_LEN_NAME);
		ConvertSingleNodeData(&lpContainer->dwPlayDuration, struXml, "palyDuration", NODE_STRING_TO_INT);
		ConvertSingleNodeData(&lpContainer->dwSwitchTime, struXml, "switchTime", NODE_STRING_TO_INT);
		ConvertSingleNodeData(lpContainer->szSwitchEffect, struXml, "switchEffect", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		struXml.OutOfElem();
		return TRUE;
	}

	return FALSE;
}

/** @fn          BOOL ConvertContainerParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       垫片转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertContainerParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_CONTAINER lpContainer = (LPNET_DVR_CONTAINER)pStruct;
	if (lpContainer->dwSize != sizeof(NET_DVR_CONTAINER))
	{
		return FALSE;
	}
	
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	return ConvertContainerParamsXmlToStru(struXml, lpContainer);
}

/** @fn          BOOL ConvertContainerParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       垫片转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertContainerParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pStruct == NULL || pXmlBuf == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_CONTAINER lpContainer = (LPNET_DVR_CONTAINER)pStruct;
	if (lpContainer->dwSize != sizeof(NET_DVR_CONTAINER))
	{
		return FALSE;
	}

	CXmlBase struXml;
	struXml.CreateRoot("Container");
	ConvertSingleNodeData(&lpContainer->dwContainerID, struXml, "id", NODE_INT_TO_STRING);
	ConvertSingleNodeData(lpContainer->szContainerName, struXml, "name", NODE_ARRAY_TO_STRING, MAX_LEN_NAME);
	ConvertSingleNodeData(&lpContainer->dwPlayDuration, struXml, "palyDuration", NODE_INT_TO_STRING);
	ConvertSingleNodeData(&lpContainer->dwSwitchTime, struXml, "switchTime", NODE_INT_TO_STRING);
	ConvertSingleNodeData(lpContainer->szSwitchEffect, struXml, "switchEffect", NODE_ARRAY_TO_STRING, MAX_LEN_32);

	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}

	return TRUE;
}

/** @fn          BOOL ConvertContainerParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       垫片列表转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertContainerParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
{
	if (pStruct == NULL || pXmlBuf == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_CONTAINER_LIST lpContainerList = (LPNET_DVR_CONTAINER_LIST)pStruct;
	if (lpContainerList->dwSize != sizeof(NET_DVR_CONTAINER_LIST))
	{
		return FALSE;
	}

	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	if (struXml.FindElem("ContainerList") && struXml.IntoElem())
	{
		int nContainerCnt = 0;
		LPNET_DVR_CONTAINER lpContainer = &lpContainerList->struContainerList[nContainerCnt];
		if (ConvertContainerParamsXmlToStru(struXml, lpContainer))
		{
			nContainerCnt++;
			lpContainer = &lpContainerList->struContainerList[nContainerCnt];
			while (struXml.NextSibElem())
			{
				ConvertContainerParamsXmlToStru(struXml, lpContainer);
				nContainerCnt++;
				if (nContainerCnt >= MAX_NUM_CONTAINER)
				{
					break;
				}
				lpContainer = &lpContainerList->struContainerList[nContainerCnt];
			}
		}
		struXml.OutOfElem();
		return TRUE;
	}

	return FALSE;
}

/** @fn             BOOL ConvertTimeNodeData(CXmlBase &struXml, LPVOID pStruct, const char* pNodeName, BOOL bXmlToStru)
 *  @brief          时间节点转换
 *  @param (in/out) CXmlBase &struXml xml对象
 *  @param (in/out) HPR_VOIDPTR pStruct 结构体参数
 *  @param (in)     const char* pNodeName xml节点名称
 *  @param (in)     BOOL bXmlToStru 转换方向
 *  @return         BOOL
 */
BOOL ConvertTimeNodeData(CXmlBase &struXml, LPVOID pStruct, const char* pNodeName, BOOL bXmlToStru)
{
	if (pStruct == NULL || pNodeName == NULL)
	{
        return FALSE;
	}
	LPNET_DVR_TIME_ pTime = (LPNET_DVR_TIME_)pStruct;
	if (bXmlToStru)
	{
		string strTime;
		BYTE byPos = 0; 
		if (struXml.FindElem(pNodeName))
		{
			strTime = struXml.GetData();
			pTime->dwYear = (DWORD)atoi(strTime.substr(byPos, 4).c_str());
			byPos += 4; 
			pTime->dwMonth = (DWORD)atoi(strTime.substr(byPos, 2).c_str());
			byPos += 2; 
			pTime->dwDay = (DWORD)atoi(strTime.substr(byPos, 2).c_str());
			byPos += 2 + 1; 
			pTime->dwHour = (DWORD)atoi(strTime.substr(byPos, 2).c_str());
			byPos += 2;
			pTime->dwMinute = (DWORD)atoi(strTime.substr(byPos, 2).c_str());
			byPos += 2;
			pTime->dwSecond = (DWORD)atoi(strTime.substr(byPos, 2).c_str());
		}
	}
	else
	{
		char szTime[MAX_LEN_32] = {0};
		sprintf(szTime, "%d%02d%02dT%02d%02d%02d+08", pTime->dwYear, pTime->dwMonth, pTime->dwDay, pTime->dwHour, pTime->dwMinute, pTime->dwSecond);
		ConvertSingleNodeData(szTime, struXml, pNodeName, NODE_ARRAY_TO_STRING, MAX_LEN_32);
	}

	return TRUE;
}

/** @fn          BOOL ConvertScheduleParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
 *  @brief       日程转换 xml转结构体
 *  @param (in)  CXmlBase& struXml xml对象
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertScheduleParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PLAY_SCHEDULE lpSchedule = (LPNET_DVR_PLAY_SCHEDULE)pStruct;

	if (struXml.FindElem("PlaySchedule") && struXml.IntoElem())
	{
		ConvertSingleNodeData(&lpSchedule->dwScheduleID, struXml, "id", NODE_STRING_TO_INT);
		ConvertSingleNodeData(lpSchedule->szScheduleName, struXml, "scheduleName", NODE_STRING_TO_ARRAY, MAX_LEN_NAME);
		ConvertSingleNodeData(lpSchedule->szScheduleRemarks, struXml, "scheduleRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
        ConvertSingleNodeData(lpSchedule->szApprove, struXml, "approveState", NODE_STRING_TO_ARRAY, MAX_LEN_32);
        ConvertSingleNodeData(lpSchedule->szApproveRemarks, struXml, "approveRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
        ConvertSingleNodeData(lpSchedule->szScheduleMode, struXml, "scheduleMode", NODE_STRING_TO_ARRAY, MAX_LEN_32);
        ConvertSingleNodeData(&lpSchedule->dwOrgNo, struXml, "orgNo", NODE_STRING_TO_INT);
		ConvertSingleNodeData(lpSchedule->szScheduleType, struXml, "scheduleType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(lpSchedule->szShareProp, struXml, "shareProperty", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		if (0 == strcmp(lpSchedule->szScheduleType, "daily"))
		{
			if (struXml.FindElem("DailySchedule") && struXml.IntoElem())
			{
				if (struXml.FindElem("PlaySpanList") && struXml.IntoElem())
				{
					int nSpanCnt = 0;
					if (struXml.FindElem("PlaySpan") && struXml.IntoElem())
					{
						ConvertSingleNodeData(&lpSchedule->struDailySchedule[nSpanCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
						ConvertSingleNodeData(&lpSchedule->struDailySchedule[nSpanCnt].dwProgramID, struXml, "programNo", NODE_STRING_TO_INT);
						if (struXml.FindElem("TimeRange") && struXml.IntoElem())
						{
							ConvertTimeNodeData(struXml, &lpSchedule->struDailySchedule[nSpanCnt].struTimeRange.struBeginTime, "beginTime", TRUE);
							ConvertTimeNodeData(struXml, &lpSchedule->struDailySchedule[nSpanCnt].struTimeRange.struEndTime, "endTime", TRUE);
							struXml.OutOfElem();
						}
						nSpanCnt++;
						struXml.OutOfElem();
						while (struXml.NextSibElem() && struXml.IntoElem())
						{
							ConvertSingleNodeData(&lpSchedule->struDailySchedule[nSpanCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
							ConvertSingleNodeData(&lpSchedule->struDailySchedule[nSpanCnt].dwProgramID, struXml, "programNo", NODE_STRING_TO_INT);
							if (struXml.FindElem("TimeRange") && struXml.IntoElem())
							{
								ConvertTimeNodeData(struXml, &lpSchedule->struDailySchedule[nSpanCnt].struTimeRange.struBeginTime, "beginTime", TRUE);
								ConvertTimeNodeData(struXml, &lpSchedule->struDailySchedule[nSpanCnt].struTimeRange.struEndTime, "endTime", TRUE);
								struXml.OutOfElem();
							}
							nSpanCnt++;
							if (nSpanCnt >= MAX_SPANS_A_DAY)
							{
								break;
							}
							struXml.OutOfElem();
						}
					}
					struXml.OutOfElem();
				}
				struXml.OutOfElem();
			}
		}
		else if (0 == strcmp(lpSchedule->szScheduleType, "weekly"))
		{
			if (struXml.FindElem("WeeklySchedule") && struXml.IntoElem())
			{
				if (struXml.FindElem("DayList") && struXml.IntoElem())
				{
					int nDayCnt = 0;
					if (struXml.FindElem("Day") && struXml.IntoElem())
					{
						ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].dwDayID, struXml, "id", NODE_STRING_TO_INT);
						ConvertSingleNodeData(lpSchedule->struWeeklySchedule[nDayCnt].szWeekday, struXml, "dayOfWeek", NODE_STRING_TO_ARRAY, MAX_LEN_32);
						if (struXml.FindElem("PlaySpanList") && struXml.IntoElem())
						{
							int nSpanCnt = 0;
							if (struXml.FindElem("PlaySpan") && struXml.IntoElem())
							{
								ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
								ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwProgramID, struXml, "programNo", NODE_STRING_TO_INT);
								if (struXml.FindElem("TimeRange") && struXml.IntoElem())
								{
									ConvertTimeNodeData(struXml, &lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].struTimeRange.struBeginTime, "beginTime", TRUE);
									ConvertTimeNodeData(struXml, &lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].struTimeRange.struEndTime, "endTime", TRUE);
									struXml.OutOfElem();
								}
								nSpanCnt++;
								struXml.OutOfElem();
								while (struXml.NextSibElem() && struXml.IntoElem())
								{
									ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
									ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwProgramID, struXml, "programNo", NODE_STRING_TO_INT);
									if (struXml.FindElem("TimeRange") && struXml.IntoElem())
									{
										ConvertTimeNodeData(struXml, &lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].struTimeRange.struBeginTime, "beginTime", TRUE);
										ConvertTimeNodeData(struXml, &lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].struTimeRange.struEndTime, "endTime", TRUE);
										struXml.OutOfElem();
									}
									nSpanCnt++;
									if (nSpanCnt >= MAX_SPANS_A_DAY)
									{
										break;
									}
									struXml.OutOfElem();
								}
							}
							struXml.OutOfElem();
						}
						nDayCnt++;
						struXml.OutOfElem();
						while (struXml.NextSibElem() && struXml.IntoElem())
						{
							ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].dwDayID, struXml, "id", NODE_STRING_TO_INT);
							ConvertSingleNodeData(lpSchedule->struWeeklySchedule[nDayCnt].szWeekday, struXml, "dayOfWeek", NODE_STRING_TO_ARRAY, MAX_LEN_32);
							if (struXml.FindElem("PlaySpanList") && struXml.IntoElem())
							{
								int nSpanCnt = 0;
								if (struXml.FindElem("PlaySpan") && struXml.IntoElem())
								{
									ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
									ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwProgramID, struXml, "programNo", NODE_STRING_TO_INT);
									if (struXml.FindElem("TimeRange") && struXml.IntoElem())
									{
										ConvertTimeNodeData(struXml, &lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].struTimeRange.struBeginTime, "beginTime", TRUE);
										ConvertTimeNodeData(struXml, &lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].struTimeRange.struEndTime, "endTime", TRUE);
										struXml.OutOfElem();
									}
									nSpanCnt++;
									struXml.OutOfElem();
									while (struXml.NextSibElem() && struXml.IntoElem())
									{
										ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
										ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwProgramID, struXml, "programNo", NODE_STRING_TO_INT);
										if (struXml.FindElem("TimeRange") && struXml.IntoElem())
										{
											ConvertTimeNodeData(struXml, &lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].struTimeRange.struBeginTime, "beginTime", TRUE);
											ConvertTimeNodeData(struXml, &lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].struTimeRange.struEndTime, "endTime", TRUE);
											struXml.OutOfElem();
										}
										nSpanCnt++;
										if (nSpanCnt >= MAX_SPANS_A_DAY)
										{
											break;
										}
										struXml.OutOfElem();
									}
								}
								struXml.OutOfElem();
							}
							nDayCnt++;
							if (nDayCnt >= MAX_DAYS_A_WEEK)
							{
								break;
							}
							struXml.OutOfElem();
						}
					}
					struXml.OutOfElem();
				}
				struXml.OutOfElem();
			}
		}
		else if (0 == strcmp(lpSchedule->szScheduleType, "loop"))
		{
			if (struXml.FindElem("LoopSchedule") && struXml.IntoElem())
			{
				if (struXml.FindElem("ProgramNoList") && struXml.IntoElem())
				{
					int nProCnt = 0;
					if (struXml.FindElem("programNo"))
					{
						ConvertSingleNodeData(&lpSchedule->struLoopSchedule[nProCnt].dwProgramID, struXml, "programNo", NODE_STRING_TO_INT);
						lpSchedule->struLoopSchedule[nProCnt].dwLoopID = nProCnt+1;
						nProCnt++;
						while (struXml.NextSibElem())
						{
							ConvertSingleNodeData(&lpSchedule->struLoopSchedule[nProCnt].dwProgramID, struXml, "programNo", NODE_STRING_TO_INT);
							lpSchedule->struLoopSchedule[nProCnt].dwLoopID = nProCnt+1;
							nProCnt++;
							if (nProCnt >= MAX_PROGRAMS_A_LOOP)
							{
								break;
							}
						}
					}
					struXml.OutOfElem();
				}
				struXml.OutOfElem();
			}
		}
		if (struXml.FindElem("SelfDefineSchedule") && struXml.IntoElem())
		{
			if (struXml.FindElem("SelfDefineList") && struXml.IntoElem())
			{
				int nSelfCnt = 0;
				if (struXml.FindElem("SelfDefine") && struXml.IntoElem())
				{
					ConvertSingleNodeData(&lpSchedule->struSeldefineSchedule[nSelfCnt].dwSeldefineID, struXml, "id", NODE_STRING_TO_INT);
					ConvertSingleNodeData(&lpSchedule->struSeldefineSchedule[nSelfCnt].dwProgramID, struXml, "programNo", NODE_STRING_TO_INT);
					if (struXml.FindElem("TimeRange") && struXml.IntoElem())
					{
						ConvertTimeNodeData(struXml, &lpSchedule->struSeldefineSchedule[nSelfCnt].struTimeRange.struBeginTime, "beginTime", TRUE);
						ConvertTimeNodeData(struXml, &lpSchedule->struSeldefineSchedule[nSelfCnt].struTimeRange.struEndTime, "endTime", TRUE);
						struXml.OutOfElem();
					}
					nSelfCnt++;
					struXml.OutOfElem();
					while (struXml.NextSibElem() && struXml.IntoElem())
					{
						ConvertSingleNodeData(&lpSchedule->struSeldefineSchedule[nSelfCnt].dwSeldefineID, struXml, "id", NODE_STRING_TO_INT);
						ConvertSingleNodeData(&lpSchedule->struSeldefineSchedule[nSelfCnt].dwProgramID, struXml, "programNo", NODE_STRING_TO_INT);
						if (struXml.FindElem("TimeRange") && struXml.IntoElem())
						{
							ConvertTimeNodeData(struXml, &lpSchedule->struSeldefineSchedule[nSelfCnt].struTimeRange.struBeginTime, "beginTime", TRUE);
							ConvertTimeNodeData(struXml, &lpSchedule->struSeldefineSchedule[nSelfCnt].struTimeRange.struEndTime, "endTime", TRUE);
							struXml.OutOfElem();
						}
						nSelfCnt++;
						if (nSelfCnt >= MAX_NUM_SELDEFINE)
						{
							break;
						}
						struXml.OutOfElem();
					}
				}
				struXml.OutOfElem();
			}
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
		return TRUE;
	}

	return FALSE;
}

/** @fn          BOOL ConvertScheduleParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       日程转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertScheduleParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PLAY_SCHEDULE lpSchedule = (LPNET_DVR_PLAY_SCHEDULE)pStruct;
	if (lpSchedule->dwSize != sizeof(*lpSchedule))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}

	return ConvertScheduleParamsXmlToStru(struXml, lpSchedule);
}

/** @fn          BOOL ConvertScheduleParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       日程转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertScheduleParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PLAY_SCHEDULE lpSchedule = (LPNET_DVR_PLAY_SCHEDULE)pStruct;
	if (lpSchedule->dwSize != sizeof(*lpSchedule))
	{
		return FALSE;
	}

	CXmlBase struXml;
	struXml.CreateRoot("PlaySchedule");
	struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(&lpSchedule->dwScheduleID, struXml, "id", NODE_INT_TO_STRING);
	ConvertSingleNodeData(lpSchedule->szScheduleName, struXml, "scheduleName", NODE_ARRAY_TO_STRING, MAX_LEN_NAME);
	ConvertSingleNodeData(lpSchedule->szScheduleRemarks, struXml, "scheduleRemarks", NODE_ARRAY_TO_STRING, MAX_LEN_REMARKS);
    ConvertSingleNodeData(lpSchedule->szApprove, struXml, "approveState", NODE_ARRAY_TO_STRING, MAX_LEN_32);
    ConvertSingleNodeData(lpSchedule->szApproveRemarks, struXml, "approveRemarks", NODE_ARRAY_TO_STRING, MAX_LEN_REMARKS);
    ConvertSingleNodeData(lpSchedule->szScheduleMode, struXml, "scheduleMode", NODE_ARRAY_TO_STRING, MAX_LEN_32);
    ConvertSingleNodeData(&lpSchedule->dwOrgNo, struXml, "orgNo", NODE_INT_TO_STRING);
	ConvertSingleNodeData(lpSchedule->szScheduleType, struXml, "scheduleType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpSchedule->szShareProp, struXml, "shareProperty", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (0 == strcmp(lpSchedule->szScheduleType, "daily"))
	{
		if (struXml.AddNode("DailySchedule"))
		{
			if (struXml.AddNode("PlaySpanList"))
			{
				for (int nSpanCnt = 0; nSpanCnt < MAX_SPANS_A_DAY; nSpanCnt++)
				{
					if (0 == lpSchedule->struDailySchedule[nSpanCnt].dwSpanID)
					{
						continue;
					}
					if (struXml.AddNode("PlaySpan"))
					{
						ConvertSingleNodeData(&lpSchedule->struDailySchedule[nSpanCnt].dwSpanID, struXml, "id", NODE_INT_TO_STRING);
						ConvertSingleNodeData(&lpSchedule->struDailySchedule[nSpanCnt].dwProgramID, struXml, "programNo", NODE_INT_TO_STRING);
						if (struXml.AddNode("TimeRange"))
						{
							ConvertTimeNodeData(struXml, &lpSchedule->struDailySchedule[nSpanCnt].struTimeRange.struBeginTime, "beginTime", FALSE);
							ConvertTimeNodeData(struXml, &lpSchedule->struDailySchedule[nSpanCnt].struTimeRange.struEndTime, "endTime", FALSE);
							struXml.OutOfElem();
						}
						struXml.OutOfElem();
					}
				}
				struXml.OutOfElem();
			}
			struXml.OutOfElem();
		}
	}
	else if (0 == strcmp(lpSchedule->szScheduleType, "weekly"))
	{
		if (struXml.AddNode("WeeklySchedule"))
		{
			if (struXml.AddNode("DayList"))
			{
				for (int nDayCnt = 0; nDayCnt < MAX_DAYS_A_WEEK; nDayCnt++)
				{
					if (0 == lpSchedule->struWeeklySchedule[nDayCnt].dwDayID)
					{
						continue;
					}
					if (struXml.AddNode("Day"))
					{
						ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].dwDayID, struXml, "id", NODE_INT_TO_STRING);
						ConvertSingleNodeData(lpSchedule->struWeeklySchedule[nDayCnt].szWeekday, struXml, "dayOfWeek", NODE_ARRAY_TO_STRING, MAX_LEN_32);
						if (struXml.AddNode("PlaySpanList"))
						{
							for (int nSpanCnt = 0; nSpanCnt < MAX_SPANS_A_DAY; nSpanCnt++)
							{
								if (0 == lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwSpanID)
								{
									continue;
								}
								if (struXml.AddNode("PlaySpan"))
								{
									ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwSpanID, struXml, "id", NODE_INT_TO_STRING);
									ConvertSingleNodeData(&lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].dwProgramID, struXml, "programNo", NODE_INT_TO_STRING);
									if (struXml.AddNode("TimeRange"))
									{
										ConvertTimeNodeData(struXml, &lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].struTimeRange.struBeginTime, "beginTime", FALSE);
										ConvertTimeNodeData(struXml, &lpSchedule->struWeeklySchedule[nDayCnt].struSpanList[nSpanCnt].struTimeRange.struEndTime, "endTime", FALSE);
										struXml.OutOfElem();
									}
									struXml.OutOfElem();
								}
							}
							struXml.OutOfElem();
						}
						struXml.OutOfElem();
					}
				}
				struXml.OutOfElem();
			}
			struXml.OutOfElem();
		}
	}
	else if (0 == strcmp(lpSchedule->szScheduleType, "loop"))
	{
		if (struXml.AddNode("LoopSchedule"))
		{
			if (struXml.AddNode("ProgramNoList"))
			{
				for (int nProCnt = 0; nProCnt < MAX_PROGRAMS_A_LOOP; nProCnt++)
				{
					if (0 == lpSchedule->struLoopSchedule[nProCnt].dwLoopID)
					{
						continue;
					}
					ConvertSingleNodeData(&lpSchedule->struLoopSchedule[nProCnt].dwProgramID, struXml, "programNo", NODE_INT_TO_STRING);
				}
				struXml.OutOfElem();
			}
			struXml.OutOfElem();
		}
	}
	if (struXml.AddNode("SelfDefineSchedule"))
	{
		if (struXml.AddNode("SelfDefineList"))
		{
			for (int nSelfCnt = 0; nSelfCnt < MAX_NUM_SELDEFINE; nSelfCnt++)
			{
				if (0 == lpSchedule->struSeldefineSchedule[nSelfCnt].dwSeldefineID)
				{
					continue;
				}
				if (struXml.AddNode("SelfDefine"))
				{
					ConvertSingleNodeData(&lpSchedule->struSeldefineSchedule[nSelfCnt].dwSeldefineID, struXml, "id", NODE_INT_TO_STRING);
					ConvertSingleNodeData(&lpSchedule->struSeldefineSchedule[nSelfCnt].dwProgramID, struXml, "programNo", NODE_INT_TO_STRING);
					if (struXml.AddNode("TimeRange"))
					{
						ConvertTimeNodeData(struXml, &lpSchedule->struSeldefineSchedule[nSelfCnt].struTimeRange.struBeginTime, "beginTime", FALSE);
						ConvertTimeNodeData(struXml, &lpSchedule->struSeldefineSchedule[nSelfCnt].struTimeRange.struEndTime, "endTime", FALSE);
						struXml.OutOfElem();
					}
					struXml.OutOfElem();
				}
			}
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
	}

	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}

	return TRUE;
}

/** @fn          BOOL ConvertScheduleReleaseParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       日程发布转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertScheduleReleaseParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_SCHEDULE_RELEASE lpRelease = (LPNET_DVR_SCHEDULE_RELEASE)pStruct;
	if (lpRelease->dwSize != sizeof(*lpRelease))
	{
		return FALSE;
	}
	
	CXmlBase struXml;
	struXml.CreateRoot("ScheduleRelease");
	struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(&lpRelease->dwScheduleID, struXml, "scheduleNo", NODE_INT_TO_STRING);
	ConvertSingleNodeData(lpRelease->szReleaseType, struXml, "releaseType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
    ConvertSingleNodeData(lpRelease->szEffectTime, struXml, "effectiveTime", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (0 == strcmp(lpRelease->szReleaseType, "byTerminal"))
	{
		if (struXml.AddNode("TerminalNoList"))
		{
			for (int nTerminalCnt = 0; nTerminalCnt < (int)lpRelease->dwTerminalCount; nTerminalCnt++)
			{
				ConvertSingleNodeData(&lpRelease->dwTerminalList[nTerminalCnt], struXml, "terminalNo", NODE_INT_TO_STRING);
			}
			struXml.OutOfElem();
		}
	}
	else if (0 == strcmp(lpRelease->szReleaseType, "byGroup"))
	{
		if (struXml.AddNode("TerminalGroupNoList"))
		{
			for (int nGrpCnt = 0; nGrpCnt < (int)lpRelease->dwGroupCount; nGrpCnt++)
			{
				ConvertSingleNodeData(&lpRelease->dwTerminalGroupList[nGrpCnt], struXml, "terminalGroupNo", NODE_INT_TO_STRING);
			}
			struXml.OutOfElem();
		}
	}
    else if (0 == strcmp(lpRelease->szReleaseType, "byOrg"))
    {
        if (struXml.AddNode("OrgNoList"))
        {
            for (int nGrpCnt = 0; nGrpCnt < (int)lpRelease->dwGroupCount; nGrpCnt++)
            {
                ConvertSingleNodeData(&lpRelease->dwTerminalGroupList[nGrpCnt], struXml, "orgNo", NODE_INT_TO_STRING);
            }
            struXml.OutOfElem();
        }
    }

	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}

	return TRUE;
}

/** @fn          BOOL ConvertScheduleSearchDescriptionParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       日程查询条件转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertScheduleSearchDescriptionParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	
	LPNET_DVR_SCHEDULE_SEARCH_DESCRIPTION lpDescription = (LPNET_DVR_SCHEDULE_SEARCH_DESCRIPTION)pStruct;
	CXmlBase struXml;
	struXml.CreateRoot("ScheduleSearchDescription");
	struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(lpDescription->sSearchID, struXml, "searchID", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpDescription->sApproveState, struXml, "approveState", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	ConvertSingleNodeData(lpDescription->sShareProperty, struXml, "shareProperty", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (strlen(lpDescription->sUploader) != 0)
	{
		ConvertSingleNodeData(lpDescription->sUploader, struXml, "uploader", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	}
	ConvertSingleNodeData(lpDescription->sScheduleType, struXml, "scheduleType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (struXml.AddNode("TimeSpanList"))
	{
		if (struXml.AddNode("TimeSpan"))
		{
			ConvertTimeNodeData(struXml, &lpDescription->struTimeRange.struBeginTime, "startTime", FALSE);
			ConvertTimeNodeData(struXml, &lpDescription->struTimeRange.struEndTime, "endTime", FALSE);
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
	}
	if (lpDescription->dwMaxResults != 0)
	{
		ConvertSingleNodeData(&lpDescription->dwMaxResults, struXml, "maxResults", NODE_INT_TO_STRING);
	}
	ConvertSingleNodeData(&lpDescription->dwSearchResultsPosition, struXml, "searchResultsPosition", NODE_INT_TO_STRING);

	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}

	return TRUE;
}

/** @fn          BOOL ConvertScheduleSearchResultParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       日程查询结果转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertScheduleSearchResultParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	
	LPNET_DVR_SCHEDULE_SEARCH_RESULT lpResult = (LPNET_DVR_SCHEDULE_SEARCH_RESULT)pStruct;
	if (struXml.FindElem("ScheduleSearchResult") && struXml.IntoElem())
	{
		ConvertSingleNodeData(lpResult->sSearchID, struXml, "searchID", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(&lpResult->bResponseStatus, struXml, "responseStatus", NODE_STRING_TO_BOOL);
		ConvertSingleNodeData(lpResult->sResponseStatusString, struXml, "responseStatusString", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		ConvertSingleNodeData(&lpResult->dwTotalMatches, struXml, "totalMatches", NODE_STRING_TO_INT);
		ConvertSingleNodeData(&lpResult->dwNumOfMatches, struXml, "numOfMatches", NODE_STRING_TO_INT);
		if (struXml.FindElem("MatchElementList") && struXml.IntoElem())
		{
			int iCnt = 0;
			if (struXml.FindElem("MatchElement") && struXml.IntoElem())
			{
				LPNET_DVR_SCHEDULE_BASIC_INFO lpSchedule = (LPNET_DVR_SCHEDULE_BASIC_INFO)&lpResult->struScheduleList[iCnt];
				
				ConvertSingleNodeData(&lpSchedule->dwScheduleID, struXml, "id", NODE_STRING_TO_INT);
				ConvertSingleNodeData(lpSchedule->szScheduleName, struXml, "scheduleName", NODE_STRING_TO_ARRAY, MAX_LEN_NAME);
				ConvertSingleNodeData(lpSchedule->szScheduleRemarks, struXml, "scheduleRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
				ConvertSingleNodeData(lpSchedule->szShareProp, struXml, "shareProperty", NODE_STRING_TO_ARRAY, MAX_LEN_32);
 				ConvertSingleNodeData(lpSchedule->szApprove, struXml, "approveState", NODE_STRING_TO_ARRAY, MAX_LEN_32);
 				ConvertSingleNodeData(lpSchedule->szApproveRemarks, struXml, "approveRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
				ConvertSingleNodeData(lpSchedule->szScheduleType, struXml, "scheduleType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
				struXml.OutOfElem();
				iCnt++;
				
				while (struXml.NextSibElem() && struXml.IntoElem())
				{
					LPNET_DVR_SCHEDULE_BASIC_INFO lpSchedule = (LPNET_DVR_SCHEDULE_BASIC_INFO)&lpResult->struScheduleList[iCnt];
					
					ConvertSingleNodeData(&lpSchedule->dwScheduleID, struXml, "id", NODE_STRING_TO_INT);
					ConvertSingleNodeData(lpSchedule->szScheduleName, struXml, "scheduleName", NODE_STRING_TO_ARRAY, MAX_LEN_NAME);
					ConvertSingleNodeData(lpSchedule->szScheduleRemarks, struXml, "scheduleRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
					ConvertSingleNodeData(lpSchedule->szShareProp, struXml, "shareProperty", NODE_STRING_TO_ARRAY, MAX_LEN_32);
					ConvertSingleNodeData(lpSchedule->szApprove, struXml, "approveState", NODE_STRING_TO_ARRAY, MAX_LEN_32);
					ConvertSingleNodeData(lpSchedule->szApproveRemarks, struXml, "approveRemarks", NODE_STRING_TO_ARRAY, MAX_LEN_REMARKS);
					ConvertSingleNodeData(lpSchedule->szScheduleType, struXml, "scheduleType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
					
					struXml.OutOfElem();
					iCnt++;
					if (iCnt >= MAX_NUM_PROGRAM)
					{
						break;
					}
				}
			}
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
	}
	
	return TRUE;
}

/** @fn          BOOL ConvertPlayControlParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       播放控制转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertPlayControlParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PLAY_CONTROL lpControl = (LPNET_DVR_PLAY_CONTROL)pStruct;
	if (lpControl->dwSize != sizeof(*lpControl))
	{
		return FALSE;
	}
	
	CXmlBase struXml;
	struXml.CreateRoot("ControlParam");
	struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(lpControl->szControlType, struXml, "operateType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (0 == strcmp(lpControl->szControlType, "insert"))
	{
		if (struXml.AddNode("InsertInfo"))
		{
			ConvertSingleNodeData(lpControl->struInsertInfo.szInsertType, struXml, "insertType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
			if (0 == strcmp(lpControl->struInsertInfo.szInsertType, "material"))
			{
				if (struXml.AddNode("MaterialInfo"))
				{
					ConvertSingleNodeData(&lpControl->struInsertInfo.dwMaterialID, struXml, "materialNo", NODE_INT_TO_STRING);
					ConvertSingleNodeData(lpControl->struInsertInfo.szPlayMode, struXml, "playMode", NODE_ARRAY_TO_STRING, MAX_LEN_32);
					if (0 ==strcmp(lpControl->struInsertInfo.szPlayMode, "byCount"))
					{
						ConvertSingleNodeData(&lpControl->struInsertInfo.dwCount, struXml, "countNum", NODE_INT_TO_STRING);
					}
					else if (0 == strcmp(lpControl->struInsertInfo.szPlayMode, "byTime"))
					{
						ConvertSingleNodeData(&lpControl->struInsertInfo.dwDuration, struXml, "playDuration", NODE_INT_TO_STRING);
					}
                    else if (0 == strcmp(lpControl->struInsertInfo.szPlayMode, "byEndTime"))
                    {
                        ConvertSingleNodeData(&lpControl->struInsertInfo.szEndTime, struXml, "playEndTime", NODE_ARRAY_TO_STRING, MAX_LEN_32);
                    }
					struXml.OutOfElem();
				}
			}
			else if (0 == strcmp(lpControl->struInsertInfo.szInsertType, "program"))
			{
				if (struXml.AddNode("ProgramInfo"))
				{
					ConvertSingleNodeData(&lpControl->struInsertInfo.dwProgramID, struXml, "programNo", NODE_INT_TO_STRING);
					ConvertSingleNodeData(lpControl->struInsertInfo.szPlayMode, struXml, "playMode", NODE_ARRAY_TO_STRING, MAX_LEN_32);
					if (0 ==strcmp(lpControl->struInsertInfo.szPlayMode, "byCount"))
					{
						ConvertSingleNodeData(&lpControl->struInsertInfo.dwCount, struXml, "countNum", NODE_INT_TO_STRING);
					}
					else if (0 == strcmp(lpControl->struInsertInfo.szPlayMode, "byTime"))
					{
						ConvertSingleNodeData(&lpControl->struInsertInfo.dwDuration, struXml, "playDuration", NODE_INT_TO_STRING);
					}
                    else if (0 == strcmp(lpControl->struInsertInfo.szPlayMode, "byEndTime"))
                    {
                        ConvertSingleNodeData(&lpControl->struInsertInfo.szEndTime, struXml, "playEndTime", NODE_ARRAY_TO_STRING, MAX_LEN_32);
                    }
					struXml.OutOfElem();
				}
			}
			if (struXml.AddNode("Position"))
			{
				ConvertSingleNodeData(&lpControl->struInsertInfo.dwPositionX, struXml, "positionX", NODE_INT_TO_STRING);
				ConvertSingleNodeData(&lpControl->struInsertInfo.dwPositionY, struXml, "positionY", NODE_INT_TO_STRING);
				ConvertSingleNodeData(&lpControl->struInsertInfo.dwPostionHeight, struXml, "height", NODE_INT_TO_STRING);
				ConvertSingleNodeData(&lpControl->struInsertInfo.dwPositionWidth, struXml, "width", NODE_INT_TO_STRING);
				struXml.OutOfElem();
			}
			if(struXml.AddNode("InsertEffect"))
			{
				if(struXml.AddNode("CharactersEffect"))
				{
					ConvertSingleNodeData(&lpControl->struInsertInfo.struChacEff.dwFontSize, struXml, "fontSize", NODE_INT_TO_STRING);
					if (struXml.AddNode("FontColor"))
					{
						DWORD dwRGB = (lpControl->struInsertInfo.struChacEff.struFontColor.dwRed<<16)|(lpControl->struInsertInfo.struChacEff.struFontColor.dwGreen<<8)|(lpControl->struInsertInfo.struChacEff.struFontColor.dwBlue);
						ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_INT_TO_STRING);
						struXml.OutOfElem();
					}
					if (struXml.AddNode("BackColor"))
					{
						DWORD dwRGB1 = (lpControl->struInsertInfo.struChacEff.struBackColor.dwRed<<16)|(lpControl->struInsertInfo.struChacEff.struBackColor.dwGreen<<8)|(lpControl->struInsertInfo.struChacEff.struBackColor.dwBlue);
						ConvertSingleNodeData(&dwRGB1, struXml, "RGB", NODE_INT_TO_STRING);
						struXml.OutOfElem();
					}
					
					ConvertSingleNodeData(&lpControl->struInsertInfo.struChacEff.dwBackTransparent, struXml, "backTransparent", NODE_INT_TO_STRING);
					ConvertSingleNodeData(&lpControl->struInsertInfo.struChacEff.bySubtitlesEnabled, struXml, "subtitlesEnabled", NODE_BOOL_TO_STRING);
					ConvertSingleNodeData(lpControl->struInsertInfo.struChacEff.szScrollDirection, struXml, "scrollDirection", NODE_ARRAY_TO_STRING);
					ConvertSingleNodeData(&lpControl->struInsertInfo.struChacEff.dwScrollSpeed, struXml, "scrollSpeed", NODE_INT_TO_STRING);
					struXml.OutOfElem();
				}
				struXml.OutOfElem();
			}
			struXml.OutOfElem();
		}
	}
	if (0 == strcmp(lpControl->szControlType, "planCtrl"))
	{
		if (struXml.AddNode("PlanCtrlParam"))
		{
			ConvertSingleNodeData(lpControl->struPlanCtrl.szPlanType, struXml, "planType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
			ConvertSingleNodeData(&lpControl->struPlanCtrl.byEnable, struXml, "enabled", NODE_BOOL_TO_STRING);
			struXml.OutOfElem();
		}
	}
	ConvertSingleNodeData(lpControl->szTargetType, struXml, "targetType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (0 == strcmp(lpControl->szTargetType, "terminals"))
	{
		if (struXml.AddNode("TerminalNoList"))
		{
			for (int nTerCnt = 0; nTerCnt < (int)lpControl->dwTerminalCount; nTerCnt++)
			{
				ConvertSingleNodeData(&lpControl->dwTerminalList[nTerCnt], struXml, "terminalNo", NODE_INT_TO_STRING);
			}
			struXml.OutOfElem();
		}
		
	}
	else if (0 == strcmp(lpControl->szTargetType, "terminalGroups"))
	{
		if (struXml.AddNode("GroupNoList"))
		{
			for (int nGrpCnt = 0; nGrpCnt < (int)lpControl->dwGroupCount; nGrpCnt++)
			{
				ConvertSingleNodeData(&lpControl->dwTerminalGroupList[nGrpCnt], struXml, "groupNo", NODE_INT_TO_STRING);
			}
			struXml.OutOfElem();
		}
	}
    else if (0 == strcmp(lpControl->szTargetType, "byOrg"))
    {
        if (struXml.AddNode("OrgNoList"))
        {
            for (int nGrpCnt = 0; nGrpCnt < (int)lpControl->dwGroupCount; nGrpCnt++)
            {
                ConvertSingleNodeData(&lpControl->dwTerminalGroupList[nGrpCnt], struXml, "orgNo", NODE_INT_TO_STRING);
            }
            struXml.OutOfElem();
        }
    }
	
	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}

	return TRUE;
}

/** @fn          char* GetStatusCodeInfo(const DWORD dwStatusCode)
 *  @brief       解析xml中的状态码
 *  @param (in)  const DWORD dwStatusCode
 *  @return      状态码字符串
 */
char* gStatusCodeInfo[] = {"0-OK", 
                           "1-OK", 
                           "2-Device Busy", 
                           "3-Device Error", 
                           "4-Invalid Operation", 
                           "5-Invalid XML Format", 
                           "6-Invalid XML Content", 
                           "7-Reboot Required"};

char* gInvalidCodeInfo = "无效状态值";

char* GetStatusCodeInfo(const DWORD dwStatusCode)
{
	if (dwStatusCode >= 0 && dwStatusCode < 8)
	{
		return  gStatusCodeInfo[dwStatusCode];
	}
	else
	{
		return gInvalidCodeInfo;
	}
}

/** @fn          BOOL ConvertTermGrpParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
 *  @brief       终端组转换 xml转结构体
 *  @param (in)  CXmlBase& struXml xml对象
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertTermGrpParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_TERMINAL_GROUP lpGroup = (LPNET_DVR_TERMINAL_GROUP)pStruct;

	if (struXml.FindElem("TerminalGroups") && struXml.IntoElem())
	{
		ConvertSingleNodeData(&lpGroup->dwGroupID, struXml, "id", NODE_STRING_TO_INT);
		ConvertSingleNodeData(lpGroup->szGroupName, struXml, "groupName", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		if (struXml.FindElem("TerminalNoList") && struXml.IntoElem())
		{
			lpGroup->dwTermCount = 0;
			if (struXml.FindElem("terminalNo"))
			{
				ConvertSingleNodeData(&lpGroup->dwTerminalList[lpGroup->dwTermCount], struXml, "terminalNo", NODE_STRING_TO_INT);
				lpGroup->dwTermCount++;
				while (struXml.NextSibElem())
				{
					ConvertSingleNodeData(&lpGroup->dwTerminalList[lpGroup->dwTermCount], struXml, "terminalNo", NODE_STRING_TO_INT);
					lpGroup->dwTermCount++;
					if (lpGroup->dwTermCount >= MAX_TERS_A_GROUP)
					{
						break;
					}
				}
			}
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
		return TRUE;
	}

	return FALSE;
}

/** @fn          BOOL ConvertTermGrpParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       终端组转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertTermGrpParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_TERMINAL_GROUP lpGroup = (LPNET_DVR_TERMINAL_GROUP)pStruct;
	if (lpGroup->dwSize != sizeof(*lpGroup))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	
	return ConvertTermGrpParamsXmlToStru(struXml, lpGroup);
}

/** @fn          BOOL ConvertTermGrpParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       终端组转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertTermGrpParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pStruct == NULL || pXmlBuf == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_TERMINAL_GROUP lpGroup = (LPNET_DVR_TERMINAL_GROUP)pStruct;
	if (lpGroup->dwSize != sizeof(*lpGroup))
	{
		return FALSE;
	}
	
	CXmlBase struXml;
	struXml.CreateRoot("TerminalGroups");
	struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(&lpGroup->dwGroupID, struXml, "id", NODE_INT_TO_STRING);
	ConvertSingleNodeData(lpGroup->szGroupName, struXml, "groupName", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (struXml.AddNode("TerminalNoList"))
	{
		for (int nTerCnt = 0; nTerCnt < (int)lpGroup->dwTermCount; nTerCnt++)
		{
			ConvertSingleNodeData(&lpGroup->dwTerminalList[nTerCnt], struXml, "terminalNo", NODE_INT_TO_STRING);
		}
		struXml.OutOfElem();
	}

	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}
	
	return TRUE;
}

/** @fn          BOOL ConvertTermGrpParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       终端组列表转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertTermGrpParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_TERMINAL_GROUP_LIST lpGroupList = (LPNET_DVR_TERMINAL_GROUP_LIST)pStruct;
	if (lpGroupList->dwSize != sizeof(*lpGroupList))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	
	if (struXml.FindElem("TerminalGroupsList") && struXml.IntoElem())
	{
		int nGroupCnt = 0;
		LPNET_DVR_TERMINAL_GROUP lpGroup = &lpGroupList->struGroupList[nGroupCnt];
		if (ConvertTermGrpParamsXmlToStru(struXml, lpGroup))
		{
			nGroupCnt++;
			lpGroup = &lpGroupList->struGroupList[nGroupCnt];
			while (struXml.NextSibElem())
			{
				ConvertTermGrpParamsXmlToStru(struXml, lpGroup);
				nGroupCnt++;
				if (nGroupCnt >= MAX_NUM_TERGROUP)
				{
					break;
				}
				lpGroup = &lpGroupList->struGroupList[nGroupCnt];
			}
		}
		struXml.OutOfElem();
		return TRUE;
	}
	
	return FALSE;
}

/** @fn          BOOL ConvertPlayParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
 *  @brief       播放配置转换 xml转结构体
 *  @param (in)  CXmlBase& struXml xml对象
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertPlayParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PLAY_CFG lpPlayCfg = (LPNET_DVR_PLAY_CFG)pStruct;

	if (struXml.FindElem("TerminalConfig") && struXml.IntoElem())
	{
		ConvertSingleNodeData(&lpPlayCfg->dwTerminalID, struXml, "id", NODE_STRING_TO_INT);
		if (struXml.FindElem("PlayerParam") && struXml.IntoElem())
		{
			ConvertSingleNodeData(&lpPlayCfg->dwPlayerVolume, struXml, "volume", NODE_STRING_TO_INT);
			struXml.OutOfElem();
		}
		if (struXml.FindElem("ScreenParam") && struXml.IntoElem())
		{
			ConvertSingleNodeData(&lpPlayCfg->struScreenParam.dwBackLightLevel, struXml, "backLightLevel", NODE_STRING_TO_INT);
			ConvertSingleNodeData(&lpPlayCfg->struScreenParam.byBootLogoEnabled, struXml, "bootLogoEnabled", NODE_STRING_TO_BOOL);
			struXml.OutOfElem();
		}
		struXml.OutOfElem();
		return TRUE;
	}

	return FALSE;
}

/** @fn          BOOL ConvertPlayParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       播放配置转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertPlayParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PLAY_CFG lpPlayCfg = (LPNET_DVR_PLAY_CFG)pStruct;
	if (lpPlayCfg->dwSize != sizeof(*lpPlayCfg))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}

	return ConvertPlayParamsXmlToStru(struXml, lpPlayCfg);
}

/** @fn          BOOL ConvertPlayParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       播放配置转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertPlayParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PLAY_CFG lpPlayCfg = (LPNET_DVR_PLAY_CFG)pStruct;
	if (lpPlayCfg->dwSize != sizeof(*lpPlayCfg))
	{
		return FALSE;
	}
	
	CXmlBase struXml;
	struXml.CreateRoot("TerminalConfig");
	struXml.SetAttribute("version", "2.0");
	ConvertSingleNodeData(&lpPlayCfg->dwTerminalID, struXml, "id", NODE_INT_TO_STRING);
	if (struXml.AddNode("PlayerParam"))
	{
		ConvertSingleNodeData(&lpPlayCfg->dwPlayerVolume, struXml, "volume", NODE_INT_TO_STRING);
		struXml.OutOfElem();
	}
	if (struXml.AddNode("ScreenParam"))
	{
		ConvertSingleNodeData(&lpPlayCfg->struScreenParam.dwBackLightLevel, struXml, "backLightLevel", NODE_INT_TO_STRING);
		ConvertSingleNodeData(&lpPlayCfg->struScreenParam.byBootLogoEnabled, struXml, "bootLogoEnabled", NODE_BOOL_TO_STRING);
		struXml.OutOfElem();
	}
	
	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}
	
	return TRUE;
}

/** @fn          BOOL ConvertPlayParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       播放配置列表转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertPlayParamsXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_PLAY_CFG_LIST lpPlayCfgList = (LPNET_DVR_PLAY_CFG_LIST)pStruct;
	if (lpPlayCfgList->dwSize != sizeof(*lpPlayCfgList))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	
	if (struXml.FindElem("TerminalConfigList") && struXml.IntoElem())
	{
		int nCfgCnt = 0;
		LPNET_DVR_PLAY_CFG lpPlayCfg = &lpPlayCfgList->struPlayCfgList[nCfgCnt];
		if (ConvertPlayParamsXmlToStru(struXml, lpPlayCfg))
		{
			nCfgCnt++;
			lpPlayCfg = &lpPlayCfgList->struPlayCfgList[nCfgCnt];
			while (struXml.NextSibElem())
			{
				ConvertPlayParamsXmlToStru(struXml, lpPlayCfg);
				nCfgCnt++;
				if (nCfgCnt >= MAX_NUM_TERMINAL)
				{
					break;
				}
				lpPlayCfg = &lpPlayCfgList->struPlayCfgList[nCfgCnt];
			}
		}
		struXml.OutOfElem();
		return TRUE;
	}
	
	return FALSE;
}

/** @fn          BOOL ConvertSwitchPlanXmlToStru(CXmlBase& struXml, LPVOID pStruct)
 *  @brief       开关机计划转换 xml转结构体
 *  @param (in)  CXmlBase& struXml xml对象
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertSwitchPlanXmlToStru(CXmlBase& struXml, LPVOID pStruct)
{
	if (pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_SWITCH_PLAN_CFG lpPlanCfg = (LPNET_DVR_SWITCH_PLAN_CFG)pStruct;
	
	if (struXml.FindElem("SwitchPlan") && struXml.IntoElem())
	{
		ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.sPlanType, struXml, "planType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
		if (0 == strcmp(lpPlanCfg->struSwitchPlan.sPlanType, "daily"))
		{
			if (struXml.FindElem("DailyPlan") && struXml.IntoElem())
			{
				if (struXml.FindElem("SwitchSpanList") && struXml.IntoElem())
				{
					DWORD dwCnt = 0;
					if (struXml.FindElem("SwitchSpan") && struXml.IntoElem())
					{
						ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
						ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
						ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].struTime, "time", TRUE);
						struXml.OutOfElem();
						dwCnt++;
						while (struXml.NextSibElem() && struXml.IntoElem())
						{
							ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
							ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
							ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].struTime, "time", TRUE);
							struXml.OutOfElem();
							dwCnt++;
						}
					}
					struXml.OutOfElem();
				}
				struXml.OutOfElem();
			}
		}
		else if (0 == strcmp(lpPlanCfg->struSwitchPlan.sPlanType, "weekly"))
		{
			if (struXml.FindElem("WeeklyPlan") && struXml.IntoElem())
			{
				if (struXml.FindElem("DayList") && struXml.IntoElem())
				{
					DWORD dwDayCnt = 0;
					if (struXml.FindElem("Day") && struXml.IntoElem())
					{
						ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].dwDayID, struXml, "id", NODE_STRING_TO_INT);
						ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].sWeekday, struXml, "dayOfWeek", NODE_STRING_TO_ARRAY, MAX_LEN_32);
						if (struXml.FindElem("SwitchSpanList") && struXml.IntoElem())
						{
							DWORD dwCnt = 0;
							if (struXml.FindElem("SwitchSpan") && struXml.IntoElem())
							{
								ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
								ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
								ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].struTime, "time", TRUE);
								struXml.OutOfElem();
								dwCnt++;
								while (struXml.NextSibElem() && struXml.IntoElem())
								{
									ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
									ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
									ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].struTime, "time", TRUE);
									struXml.OutOfElem();
									dwCnt++;
								}
							}
							struXml.OutOfElem();
						}
						struXml.OutOfElem();
						dwDayCnt++;
						while (struXml.NextSibElem() && struXml.IntoElem())
						{
							ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].dwDayID, struXml, "id", NODE_STRING_TO_INT);
							ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].sWeekday, struXml, "dayOfWeek", NODE_STRING_TO_ARRAY, MAX_LEN_32);
							if (struXml.FindElem("SwitchSpanList") && struXml.IntoElem())
							{
								DWORD dwCnt = 0;
								if (struXml.FindElem("SwitchSpan") && struXml.IntoElem())
								{
									ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
									ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
									ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].struTime, "time", TRUE);
									struXml.OutOfElem();
									dwCnt++;
									while (struXml.NextSibElem() && struXml.IntoElem())
									{
										ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
										ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
										ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].struSpanList[dwCnt].struTime, "time", TRUE);
										struXml.OutOfElem();
										dwCnt++;
									}
								}
								struXml.OutOfElem();
							}
							struXml.OutOfElem();
							dwDayCnt++;
						}
					}
					struXml.IntoElem();
				}
				struXml.OutOfElem();
			}
		}
// 		if (struXml.FindElem("SelfDefinePlan") && struXml.IntoElem())
// 		{
// 			if (struXml.FindElem("SwitchSpanList") && struXml.IntoElem())
// 			{
// 				DWORD dwCnt = 0;
// 				if (struXml.FindElem("SwitchSpan") && struXml.IntoElem())
// 				{
// 					ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struSelfdefinePlan[dwCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
// 					ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struSelfdefinePlan[dwCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
// 					ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struSelfdefinePlan[dwCnt].struTime, "time", TRUE);
// 					struXml.OutOfElem();
// 					dwCnt++;
// 					while (struXml.NextSibElem() && struXml.IntoElem())
// 					{
// 						ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struSelfdefinePlan[dwCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
// 						ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struSelfdefinePlan[dwCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
// 						ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struSelfdefinePlan[dwCnt].struTime, "time", TRUE);
// 						struXml.OutOfElem();
// 						dwCnt++;
// 					}
// 				}
// 				struXml.OutOfElem();
// 			}
// 		}
		struXml.OutOfElem();
        return TRUE;
	}
	
	return FALSE;
}

/** @fn          BOOL ConvertSwitchPlanXmlToStru(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       开关机计划转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertSwitchPlanXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_SWITCH_PLAN_CFG lpPlanCfg = (LPNET_DVR_SWITCH_PLAN_CFG)pStruct;
	if (lpPlanCfg->dwSize != sizeof(*lpPlanCfg))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}
	
	return ConvertSwitchPlanXmlToStru(struXml, lpPlanCfg);
}

/** @fn          BOOL ConvertSwitchPlanStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
 *  @brief       开关机计划转换 结构体转xml
 *  @param (in)  LPVOID pStruct 结构体参数
 *  @param (out) const char* pXmlBuf xml参数
 *  @param (out) DWORD &dwXmlLen xml长度
 *  @return      BOOL
 */
BOOL ConvertSwitchPlanStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_SWITCH_PLAN_CFG lpPlanCfg = (LPNET_DVR_SWITCH_PLAN_CFG)pStruct;
	if (lpPlanCfg->dwSize != sizeof(*lpPlanCfg))
	{
		return FALSE;
	}
	
	CXmlBase struXml;
	struXml.CreateRoot("SwitchPlan");
	struXml.SetAttribute("version", "2.0");

	ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.sPlanType, struXml, "planType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
	if (0 == strcmp(lpPlanCfg->struSwitchPlan.sPlanType, "daily"))
	{
		if (struXml.AddNode("DailyPlan"))
		{
			if (struXml.AddNode("SwitchSpanList"))
			{
				for (DWORD dwCnt = 0; dwCnt < MAX_SPANS_A_DAY; dwCnt++)
				{
					if (0 == lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].dwSpanID)
					{
						continue;
					}
					if (struXml.AddNode("SwitchSpan"))
					{
						ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].dwSpanID, struXml, "id", NODE_INT_TO_STRING);
						ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].sSwitchType, struXml, "switchType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
						ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].struTime, "time", FALSE);
						struXml.OutOfElem();
					}
				}
				struXml.OutOfElem();
			}
			struXml.OutOfElem();
		}
	}
	else if (0 == strcmp(lpPlanCfg->struSwitchPlan.sPlanType, "weekly"))
	{
		if (struXml.AddNode("WeeklyPlan"))
		{
			if (struXml.AddNode("DayList"))
			{
				for (DWORD dwDayCnt = 0; dwDayCnt < MAX_DAYS_A_WEEK; dwDayCnt++)
				{
					if (0 == lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].dwDayID)
					{
						continue;
					}
					if (struXml.AddNode("Day"))
					{
						ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].dwDayID, struXml, "id", NODE_STRING_TO_INT);
						ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struWeekyPlan[dwDayCnt].sWeekday, struXml, "dayOfWeek", NODE_STRING_TO_ARRAY, MAX_LEN_32);
						if (struXml.AddNode("SwitchSpanList"))
						{
							for (DWORD dwCnt = 0; dwCnt < MAX_SPANS_A_DAY; dwCnt++)
							{
								if (0 == lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].dwSpanID)
								{
									continue;
								}
								if (struXml.AddNode("SwitchSpan"))
								{
									ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].dwSpanID, struXml, "id", NODE_INT_TO_STRING);
									ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].sSwitchType, struXml, "switchType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
									ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].struTime, "time", FALSE);
									struXml.OutOfElem();
								}
							}
							struXml.OutOfElem();
						}
						struXml.OutOfElem();
					}
				}
				struXml.OutOfElem();
			}
			struXml.OutOfElem();
		}
	}
// 	if (struXml.AddNode("SelfDefinePlan"))
// 	{
// 		if (struXml.AddNode("SwitchSpanList"))
// 		{
// 			for (DWORD dwCnt = 0; dwCnt < MAX_NUM_SELDEFINE; dwCnt++)
// 			{
// 				if (0 == lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].dwSpanID)
// 				{
// 					continue;
// 				}
// 				if (struXml.AddNode("SwitchSpan"))
// 				{
// 					ConvertSingleNodeData(&lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].dwSpanID, struXml, "id", NODE_INT_TO_STRING);
// 					ConvertSingleNodeData(lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].sSwitchType, struXml, "switchType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
// 					ConvertTimeNodeData(struXml, &lpPlanCfg->struSwitchPlan.struDailyPlan[dwCnt].struTime, "time", FALSE);
// 					struXml.OutOfElem();
// 				}
// 			}
// 			struXml.OutOfElem();
// 		}
// 		struXml.OutOfElem();
// 	}
	
	if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
	{
		return FALSE;
	}
	
	return TRUE;
}

/** @fn          BOOL ConvertSwitchPlanXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
 *  @brief       开关机计划列表转换 xml转结构体
 *  @param (in)  const char* pXmlBuf xml参数
 *  @param (out) LPVOID pStruct 结构体参数
 *  @return      BOOL
 */
BOOL ConvertSwitchPlanXmlToStruList(const char* pXmlBuf, LPVOID pStruct)
{
	if (pXmlBuf == NULL || pStruct == NULL)
	{
		return FALSE;
	}
	LPNET_DVR_SWITCH_PLAN_LIST lpPlanCfgList = (LPNET_DVR_SWITCH_PLAN_LIST)pStruct;
	if (lpPlanCfgList->dwSize != sizeof(*lpPlanCfgList))
	{
		return FALSE;
	}
	CXmlBase struXml;
	if (struXml.Parse(pXmlBuf) == NULL)
	{
		return FALSE;
	}

	if (struXml.FindElem("SwitchPlanList") && struXml.IntoElem())
	{
	//	if (struXml.FindElem("SwitchPlan"))
	//	{
			DWORD dwPlanCnt = 0;
			LPNET_DVR_SWITCH_PLAN lpPlanCfg = &lpPlanCfgList->struSwitchPlanList[dwPlanCnt];
 			if (!ConvertSwitchPlanXmlToStru(struXml, lpPlanCfg))
 			{
 				return FALSE;
 			}
 			while (struXml.NextSibElem())
 			{
				dwPlanCnt++;
				if (dwPlanCnt >= MAX_NUM_SWITCH_PLAN)
				{
 					break;
 				}
 				lpPlanCfg = &lpPlanCfgList->struSwitchPlanList[dwPlanCnt];
 				if (!ConvertSwitchPlanXmlToStru(struXml, lpPlanCfg))
 				{
 					return FALSE;
 				}
 			}
		//}
		struXml.OutOfElem();
        return TRUE;
	}
	
	return FALSE;
}

//时钟素材结构体转xml
BOOL ConvertClockParam(NET_DVR_CLOCK &struLock,CXmlBase &struXml)
{
	if (struXml.AddNode("ClockParam"))
	{
		ConvertSingleNodeData(&struLock.dwTotalHeight, struXml, "totalHeight", NODE_INT_TO_STRING);
		ConvertSingleNodeData(&struLock.dwTotalWidth, struXml, "totalWidth", NODE_INT_TO_STRING);
		ConvertSingleNodeData(&struLock.dwBackPicId, struXml, "backPicId", NODE_INT_TO_STRING);
		if(struXml.AddNode("ClockIcon"))
		{
			ConvertSingleNodeData(&struLock.byIconEnable, struXml, "enabled", NODE_BOOL_TO_STRING);
			ConvertSingleNodeData(struLock.szIconType, struXml, "type", NODE_ARRAY_TO_STRING,MAX_LEN_32);
			if(struXml.AddNode("Position"))
			{
				ConvertSingleNodeData(&struLock.dwIconX, struXml, "positionX", NODE_INT_TO_STRING);
				ConvertSingleNodeData(&struLock.dwIconY, struXml, "positionY", NODE_INT_TO_STRING);
				ConvertSingleNodeData(&struLock.dwIconH, struXml, "height", NODE_INT_TO_STRING);
				ConvertSingleNodeData(&struLock.dwIconW, struXml, "width", NODE_INT_TO_STRING);
				struXml.OutOfElem();
			}
			struXml.OutOfElem();
		}

		if (struXml.AddNode("YmdParam"))
		{
			AddClockNode(struLock.struYmd,struXml);
			struXml.OutOfElem();
		}
		if (struXml.AddNode("HmsParam"))
		{
			AddClockNode(struLock.struHms,struXml);
			struXml.OutOfElem();
		}
		if (struXml.AddNode("WeekParam"))
		{
			AddClockNode(struLock.struWeek,struXml);
			struXml.OutOfElem();
		}
		
		struXml.OutOfElem();
	
	}
	return TRUE;
	

}	

//时钟参数结构体转xml
BOOL AddClockNode(NET_DVR_DISP_PARAM &struDisp,CXmlBase &struXml)
{

	ConvertSingleNodeData(&struDisp.byEnable, struXml, "enabled", NODE_BOOL_TO_STRING);
	ConvertSingleNodeData(&struDisp.dwFontSize, struXml, "fontSize", NODE_INT_TO_STRING);
	if(struXml.AddNode("FontColor"))
	{
		DWORD dwRGB = (struDisp.struFontColor.dwRed<<16)|(struDisp.struFontColor.dwGreen<<8)|(struDisp.struFontColor.dwBlue);
		ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_INT_TO_STRING);
		struXml.OutOfElem();
	}
	if(struXml.AddNode("BackColor"))
	{
		DWORD dwRGB = (struDisp.struBackColor.dwRed<<16)|(struDisp.struBackColor.dwGreen<<8)|(struDisp.struBackColor.dwBlue);
		ConvertSingleNodeData(&dwRGB, struXml, "RGB", NODE_INT_TO_STRING);
		struXml.OutOfElem();
	}	
	if(struXml.AddNode("Position"))
	{
		ConvertSingleNodeData(&struDisp.dwPositionX, struXml, "positionX", NODE_INT_TO_STRING);
		ConvertSingleNodeData(&struDisp.dwPositionY, struXml, "positionY", NODE_INT_TO_STRING);
		ConvertSingleNodeData(&struDisp.dwHeight, struXml, "height", NODE_INT_TO_STRING);
		ConvertSingleNodeData(&struDisp.dwWidth, struXml, "width", NODE_INT_TO_STRING);
		struXml.OutOfElem();
	}
	return TRUE;
}

//天气参数结构体转xml		
BOOL ConvertWeatherParam(NET_DVR_WEATHER &struWeather,CXmlBase &struXml)
{
	if (struXml.AddNode("WeatherParam"))
	{
		ConvertSingleNodeData(&struWeather.dwTotalHeight, struXml, "totalHeight", NODE_INT_TO_STRING);
		ConvertSingleNodeData(&struWeather.dwTotalWidth, struXml, "totalWidth", NODE_INT_TO_STRING);
		ConvertSingleNodeData(&struWeather.dwBackPicId, struXml, "backPicId", NODE_INT_TO_STRING);
		if(struXml.AddNode("WeatherIcon"))
		{
			ConvertSingleNodeData(&struWeather.byIconEnable, struXml, "enabled", NODE_BOOL_TO_STRING);
			if(struXml.AddNode("Position"))
			{
				ConvertSingleNodeData(&struWeather.dwIconX, struXml, "positionX", NODE_INT_TO_STRING);
				ConvertSingleNodeData(&struWeather.dwIconY, struXml, "positionY", NODE_INT_TO_STRING);
				ConvertSingleNodeData(&struWeather.dwIconH, struXml, "height", NODE_INT_TO_STRING);
				ConvertSingleNodeData(&struWeather.dwIconW, struXml, "width", NODE_INT_TO_STRING);
				struXml.OutOfElem();
			}
			struXml.OutOfElem();
		}
		if (struXml.AddNode("Date"))
		{
			AddClockNode(struWeather.struDate,struXml);
			struXml.OutOfElem();
		}
		if (struXml.AddNode("Temperature"))
		{
			AddClockNode(struWeather.struTemp,struXml);
			struXml.OutOfElem();
		}
		if (struXml.AddNode("WeatherContent"))
		{
			AddClockNode(struWeather.struContent,struXml);
			struXml.OutOfElem();
		}
		if (struXml.AddNode("City"))
		{
			AddClockNode(struWeather.struCity,struXml);
			struXml.OutOfElem();
		}
		if (struXml.AddNode("Humidity"))
		{
			AddClockNode(struWeather.struHum,struXml);
			struXml.OutOfElem();
		}
		if (struXml.AddNode("AirQuality"))
		{
			AddClockNode(struWeather.struAir,struXml);
			struXml.OutOfElem();
		}
		if (struXml.AddNode("UpdateTime"))
		{
			AddClockNode(struWeather.struUpdate,struXml);
			struXml.OutOfElem();
		}
		if (struXml.AddNode("Wind"))
		{
			AddClockNode(struWeather.struWind,struXml);
			struXml.OutOfElem();
		}		
		struXml.OutOfElem();
		
	}
	return TRUE;
}


BOOL ConvertSwitchPlanListParamsXmlToStruList(const char *pXmlBuf,LPVOID pStruct)
{
    if (pXmlBuf == NULL || pStruct == NULL)
    {
        return FALSE;
    }
    LPNET_DVR_SWITCH_PLAN_LIST lpPlanList = (LPNET_DVR_SWITCH_PLAN_LIST)pStruct;
    if (lpPlanList->dwSize != sizeof(*lpPlanList))
    {
        return FALSE;
    }
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuf) == NULL)
    {
        return FALSE;
    }
    if (struXml.FindElem("SwitchPlanList") && struXml.IntoElem())
    {
        int nPlanCnt = 0;
        LPNET_DVR_SWITCH_PLAN lpPlan = &lpPlanList->struSwitchPlanList[nPlanCnt];
        if (ConvertPlanParamsXmlToStru(struXml, lpPlan))
        {
            nPlanCnt++;
            lpPlan = &lpPlanList->struSwitchPlanList[nPlanCnt];
            while (struXml.NextSibElem())
            {
                ConvertPlanParamsXmlToStru(struXml, lpPlan);
                nPlanCnt++;
                if (nPlanCnt >= MAX_NUM_SWITCH_PLAN)
                {
                    break;
                }
                lpPlan = &lpPlanList->struSwitchPlanList[nPlanCnt];
            }
        }
        struXml.OutOfElem();
        return TRUE;
    }
    
    return FALSE;
}

BOOL ConvertPlanParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
    if (pXmlBuf == NULL || pStruct == NULL)
    {
        return FALSE;
    }
    LPNET_DVR_SWITCH_PLAN lpPlan = (LPNET_DVR_SWITCH_PLAN)pStruct;
    if (lpPlan->dwSize != sizeof(*lpPlan))
    {
        return FALSE;
    }
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuf) == NULL)
    {
        return FALSE;
    }
    return ConvertPlanParamsXmlToStru(struXml, lpPlan);
}

BOOL ConvertPlanParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
{
    if (pStruct == NULL)
    {
        return FALSE;
    }
    LPNET_DVR_SWITCH_PLAN lpPlan= (LPNET_DVR_SWITCH_PLAN)pStruct;

    
    
    if (struXml.FindElem("SwitchPlan") && struXml.IntoElem())
    {

        ConvertSingleNodeData(lpPlan->sPlanType, struXml, "planType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
        if(0 == strcmp(lpPlan->sPlanType,"daily"))
        {
            if (struXml.FindElem("DailyPlan") && struXml.IntoElem())
            {
                if (struXml.FindElem("SwitchSpanList") && struXml.IntoElem())
                {
                    int nDailyCnt = 0;
                    if (struXml.FindElem("SwitchSpan")&& struXml.IntoElem())
                    {
                        ConvertSingleNodeData(&lpPlan->struDailyPlan[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                        ConvertSingleNodeData(lpPlan->struDailyPlan[nDailyCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
                        ConvertTimeNodeData(struXml,&lpPlan->struDailyPlan[nDailyCnt].struTime, "time", TRUE);
                        nDailyCnt++;
                        struXml.OutOfElem();
                        while (struXml.NextSibElem()&& struXml.IntoElem())
                        {
                            ConvertSingleNodeData(&lpPlan->struDailyPlan[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                            ConvertSingleNodeData(lpPlan->struDailyPlan[nDailyCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
                            ConvertTimeNodeData(struXml,&lpPlan->struDailyPlan[nDailyCnt].struTime, "time", TRUE);
               
                            nDailyCnt++;
                            if (nDailyCnt >= MAX_SPANS_A_DAY )
                            {
                                break;
                            }
                            struXml.OutOfElem();
                        }
                        
                    }
                    struXml.OutOfElem();
                }
                struXml.OutOfElem();
            }
        }
        else if(0 == strcmp(lpPlan->sPlanType,"weekly"))
        {
            if (struXml.FindElem("WeeklyPlan") && struXml.IntoElem())
            {
                if (struXml.FindElem("DayList") && struXml.IntoElem())
                {
                    int nDayCnt = 0;
                    if (struXml.FindElem("Day") && struXml.IntoElem())
                    {
                        ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].dwDayID, struXml, "id", NODE_STRING_TO_INT);
                        ConvertSingleNodeData(lpPlan->struWeekyPlan[nDayCnt].sWeekday, struXml, "dayOfWeek", NODE_STRING_TO_ARRAY, MAX_LEN_32);          
                        if (struXml.FindElem("SwitchSpanList") && struXml.IntoElem())
                        {
                            int nDailyCnt = 0;
                            if (struXml.FindElem("SwitchSpan")&& struXml.IntoElem())
                            {
                                ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                                ConvertSingleNodeData(lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
                                ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTime, "time", TRUE);
                                nDailyCnt++;
                                struXml.OutOfElem();
                                while (struXml.NextSibElem()&& struXml.IntoElem())
                                {
                                    ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                                    ConvertSingleNodeData(lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
                                    ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTime, "time", TRUE);
                                    nDailyCnt++;
                                    if (nDailyCnt >= MAX_SPANS_A_DAY )
                                    {
                                        break;
                                    }
                                    struXml.OutOfElem();
                                }                                
                            }
                            struXml.OutOfElem();
                        }
                        struXml.OutOfElem();
                        nDayCnt++;
                        while(struXml.NextSibElem()&&struXml.IntoElem())
                        {
                            ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].dwDayID, struXml, "id", NODE_STRING_TO_INT);
                            ConvertSingleNodeData(lpPlan->struWeekyPlan[nDayCnt].sWeekday, struXml, "dayOfWeek", NODE_STRING_TO_ARRAY, MAX_LEN_32);          
                            if (struXml.FindElem("SwitchSpanList") && struXml.IntoElem())
                            {
                                int nDailyCnt = 0;
                                if (struXml.FindElem("SwitchSpan")&& struXml.IntoElem())
                                {
                                    ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                                    ConvertSingleNodeData(lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
                                    ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTime, "time", TRUE);
                                    nDailyCnt++;
                                    struXml.OutOfElem();
                                    while (struXml.NextSibElem()&& struXml.IntoElem())
                                    {
                                        ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                                        ConvertSingleNodeData(lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].sSwitchType, struXml, "switchType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
                                        ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTime, "time", TRUE);
                                        nDailyCnt++;
                                        if (nDailyCnt >= MAX_SPANS_A_DAY )
                                        {
                                            break;
                                        }
                                        struXml.OutOfElem();
                                    }                                
                                }
                               // nDayCnt++;
                                struXml.OutOfElem();
                            }
                            nDayCnt++;
                            struXml.OutOfElem();
                        }
                        //struXml.OutOfElem();
                    }
                    struXml.OutOfElem();
                }
                struXml.OutOfElem();
                
            }
        }
        
        
        struXml.OutOfElem();
        return TRUE;
        }
        
        return FALSE;
}

//定时开关机配置结构体转成xml
BOOL ConvertPlanParamStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (pStruct == NULL || pXmlBuf == NULL)
    {
        return FALSE;
    }
    LPNET_DVR_SWITCH_PLAN_CFG lpPlan = (LPNET_DVR_SWITCH_PLAN_CFG)pStruct;
    if (lpPlan->dwSize != sizeof(*lpPlan))
    {
        return FALSE;
    }
    
    CXmlBase struXml;
    struXml.CreateRoot("SwitchPlanCfg");
    struXml.SetAttribute("version", "2.0");
    if(struXml.AddNode("SwitchPlan"))
    {
        ConvertSingleNodeData(lpPlan->struSwitchPlan.sPlanType, struXml, "planType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
        if(0== strcmp(lpPlan->struSwitchPlan.sPlanType,"daily"))
        {
            if (struXml.AddNode("DailyPlan"))
            {
                if (struXml.AddNode("SwitchSpanList"))
                {
                    for (int nDailyCnt = 0; nDailyCnt < MAX_SPANS_A_DAY; nDailyCnt++)
                    {
                        if(0 == lpPlan->struSwitchPlan.struDailyPlan[nDailyCnt].dwSpanID)
                        {
                            continue;
                         }
                        if (struXml.AddNode("SwitchSpan"))
                        {
                       
                            ConvertSingleNodeData(&lpPlan->struSwitchPlan.struDailyPlan[nDailyCnt].dwSpanID, struXml, "id", NODE_INT_TO_STRING);
                            ConvertSingleNodeData(lpPlan->struSwitchPlan.struDailyPlan[nDailyCnt].sSwitchType, struXml, "switchType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
                            ConvertTimeNodeData(struXml, &lpPlan->struSwitchPlan.struDailyPlan[nDailyCnt].struTime, "time", FALSE);
                            struXml.OutOfElem();
                        }
                    }
                    struXml.OutOfElem();
                }
                struXml.OutOfElem();
            }
        
        }
        else if(0== strcmp(lpPlan->struSwitchPlan.sPlanType,"weekly"))
        {     
            if (struXml.AddNode("WeeklyPlan"))
            {
                if (struXml.AddNode("DayList"))
                {
                    for (int nDay = 0; nDay < MAX_DAYS_A_WEEK; nDay++)
                    {
                        if(0 == lpPlan->struSwitchPlan.struWeekyPlan[nDay].dwDayID)
                        {
                            continue;
                        }
                        if (struXml.AddNode("Day"))
                        {
                            ConvertSingleNodeData(&lpPlan->struSwitchPlan.struWeekyPlan[nDay].dwDayID, struXml, "id", NODE_INT_TO_STRING);
                            ConvertSingleNodeData(lpPlan->struSwitchPlan.struWeekyPlan[nDay].sWeekday, struXml, "dayOfWeek", NODE_ARRAY_TO_STRING, MAX_LEN_32);
                            if (struXml.AddNode("SwitchSpanList"))
                            {
                                for (int nDailyCnt = 0; nDailyCnt < MAX_SPANS_A_DAY; nDailyCnt++)
                                {
                                    if(0 == lpPlan->struSwitchPlan.struWeekyPlan[nDay].struSpanList[nDailyCnt].dwSpanID)
                                    {
                                        continue;
                                    }
                                    if (struXml.AddNode("SwitchSpan"))
                                    {
                                        ConvertSingleNodeData(&lpPlan->struSwitchPlan.struWeekyPlan[nDay].struSpanList[nDailyCnt].dwSpanID, struXml, "id", NODE_INT_TO_STRING);
                                        ConvertSingleNodeData(lpPlan->struSwitchPlan.struWeekyPlan[nDay].struSpanList[nDailyCnt].sSwitchType, struXml, "switchType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
                                        ConvertTimeNodeData(struXml, &lpPlan->struSwitchPlan.struWeekyPlan[nDay].struSpanList[nDailyCnt].struTime, "time", FALSE);
                                        struXml.OutOfElem();
                                    }
                                }
                                struXml.OutOfElem();
                            }
                            struXml.OutOfElem();
                        }
                    }
                    struXml.OutOfElem();
                }
                struXml.OutOfElem();
            }
        }
        struXml.OutOfElem();
    }
    if(struXml.AddNode("OperateParam"))
    {
        ConvertSingleNodeData(lpPlan->szOperType, struXml, "operateType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
        if(0 == strcmp(lpPlan->szOperType,"byTerminal"))
        {    
            if(struXml.AddNode("TerminalNoList"))
            {
                for(int nTer=0;nTer<lpPlan->dwTerminalNo;nTer++)
                {
                    ConvertSingleNodeData(&lpPlan->dwListTerminal[nTer], struXml, "terminalNo", NODE_INT_TO_STRING);
                }
                struXml.OutOfElem();
            }
        }
        else if(0 == strcmp(lpPlan->szOperType,"byGroup"))
        {    
            if(struXml.AddNode("TerminalGroupNoList"))
            {
                for(int nGroup=0;nGroup<lpPlan->dwGroupNo;nGroup++)
                {
                    ConvertSingleNodeData(&lpPlan->dwListGroup[nGroup], struXml, "terminalGroupNo", NODE_INT_TO_STRING);
                }
                struXml.OutOfElem();
            }
        }
        else if (0 == strcmp(lpPlan->szOperType, "byOrg"))
        {
            if (struXml.AddNode("OrgNoList"))
            {
                for (int nGroup = 0; nGroup < lpPlan->dwGroupNo; nGroup++)
                {
                    ConvertSingleNodeData(&lpPlan->dwListGroup[nGroup], struXml, "orgNo", NODE_INT_TO_STRING);
                }
                struXml.OutOfElem();
            }
        }
     
        struXml.OutOfElem();
    }
    
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }
    
	return TRUE;

}

//音量计划配置结构体转xml
BOOL ConvertVolumePlanParamStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (pStruct == NULL || pXmlBuf == NULL)
    {
        return FALSE;
    }
    LPNET_DVR_VOLUME_PLAN_CFG lpPlan = (LPNET_DVR_VOLUME_PLAN_CFG)pStruct;
    if (lpPlan->dwSize != sizeof(*lpPlan))
    {
        return FALSE;
    }
    
    CXmlBase struXml;
    struXml.CreateRoot("VolumePlanCfg");
    struXml.SetAttribute("version", "2.0");
    if(struXml.AddNode("VolumePlan"))
    {
        ConvertSingleNodeData(lpPlan->struVolumePlan.sPlanType, struXml, "planType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
        if(0== strcmp(lpPlan->struVolumePlan.sPlanType,"daily"))
        {
            if (struXml.AddNode("DailyPlan"))
            {
                if (struXml.AddNode("VolumeSpanList"))
                {
                    for (int nDailyCnt = 0; nDailyCnt < MAX_SPANS_A_DAY; nDailyCnt++)
                    {
                        if (0 == lpPlan->struVolumePlan.struDailyPlan[nDailyCnt].dwSpanID)
                        {
                            continue;
					    }
                        if (struXml.AddNode("VolumeSpan"))
                        {
                            ConvertSingleNodeData(&lpPlan->struVolumePlan.struDailyPlan[nDailyCnt].dwSpanID, struXml, "id", NODE_INT_TO_STRING);
                            ConvertSingleNodeData(&lpPlan->struVolumePlan.struDailyPlan[nDailyCnt].dwVolume, struXml, "volume", NODE_INT_TO_STRING);
                            ConvertTimeNodeData(struXml, &lpPlan->struVolumePlan.struDailyPlan[nDailyCnt].struTime, "beginTime", FALSE);
                            ConvertTimeNodeData(struXml, &lpPlan->struVolumePlan.struDailyPlan[nDailyCnt].struTimeEnd, "endTime", FALSE);
                            struXml.OutOfElem();
                        }
                    }
                    struXml.OutOfElem();
                }
                struXml.OutOfElem();
            }
        
        }
        else if(0== strcmp(lpPlan->struVolumePlan.sPlanType,"weekly"))
        {     
            if (struXml.AddNode("WeeklyPlan"))
            {
                if (struXml.AddNode("DayList"))
                {
                    for (int nDay = 0; nDay < MAX_DAYS_A_WEEK; nDay++)
                    {
                        if(0 == lpPlan->struVolumePlan.struWeekyPlan[nDay].dwDayID)
                        {
                            continue;
                        }
                        if (struXml.AddNode("Day"))
                        {
                            ConvertSingleNodeData(&lpPlan->struVolumePlan.struWeekyPlan[nDay].dwDayID, struXml, "id", NODE_INT_TO_STRING);
                            ConvertSingleNodeData(lpPlan->struVolumePlan.struWeekyPlan[nDay].sWeekday, struXml, "dayOfWeek", NODE_ARRAY_TO_STRING, MAX_LEN_32);
                            if (struXml.AddNode("VolumeSpanList"))
                            {
                                for (int nDailyCnt = 0; nDailyCnt < MAX_SPANS_A_DAY; nDailyCnt++)
                                {
                                    if (0 == lpPlan->struVolumePlan.struWeekyPlan[nDay].struSpanList[nDailyCnt].dwSpanID)
                                    {
                                        continue;
				            	    }

                                    if (struXml.AddNode("VolumeSpan"))
                                    {
                                        ConvertSingleNodeData(&lpPlan->struVolumePlan.struWeekyPlan[nDay].struSpanList[nDailyCnt].dwSpanID, struXml, "id", NODE_INT_TO_STRING);
                                        ConvertSingleNodeData(&lpPlan->struVolumePlan.struWeekyPlan[nDay].struSpanList[nDailyCnt].dwVolume, struXml, "volume", NODE_INT_TO_STRING);
                                        ConvertTimeNodeData(struXml, &lpPlan->struVolumePlan.struWeekyPlan[nDay].struSpanList[nDailyCnt].struTime, "beginTime", FALSE);
                                        ConvertTimeNodeData(struXml, &lpPlan->struVolumePlan.struWeekyPlan[nDay].struSpanList[nDailyCnt].struTimeEnd, "endTime", FALSE);
                                        struXml.OutOfElem();
                                    }
                                }
                                struXml.OutOfElem();
                            }
                            struXml.OutOfElem();
                        }
                    }
                    struXml.OutOfElem();
                }
                struXml.OutOfElem();
            }
        }
        struXml.OutOfElem();
    }
    if(struXml.AddNode("OperateParam"))
    {
        ConvertSingleNodeData(lpPlan->szOperType, struXml, "operateType", NODE_ARRAY_TO_STRING);
        if(0 == strcmp(lpPlan->szOperType,"byTerminal"))
        {
            if(struXml.AddNode("TerminalNoList"))
            {
                for(int nTer = 0;nTer<lpPlan->dwTerminalNo;nTer++)
                {
                     ConvertSingleNodeData(&lpPlan->dwListTerminal[nTer], struXml, "terminalNo", NODE_INT_TO_STRING);
                }
                struXml.OutOfElem();
            }
        }
        else if(0 == strcmp(lpPlan->szOperType,"byGroup"))
        {
            if(struXml.AddNode("TerminalGroupNoList"))
            {
                for(int nGroup = 0;nGroup<lpPlan->dwGroupNo;nGroup++)
                {
                    ConvertSingleNodeData(&lpPlan->dwListGroup[nGroup], struXml, "terminalGroupNo", NODE_INT_TO_STRING);
                }
                struXml.OutOfElem();
            }
        }
        else if (0 == strcmp(lpPlan->szOperType, "byOrg"))
        {
            if (struXml.AddNode("OrgNoList"))
            {
                for (int nGroup = 0; nGroup < lpPlan->dwGroupNo; nGroup++)
                {
                    ConvertSingleNodeData(&lpPlan->dwListGroup[nGroup], struXml, "orgNo", NODE_INT_TO_STRING);
                }
                struXml.OutOfElem();
            }
        }
        struXml.OutOfElem();
    }

    
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }
    
    return TRUE;
    
}

BOOL ConvertVolumePlanListParamsXmlToStruList(const char *pXmlBuf,LPVOID pStruct)
{
    if (pXmlBuf == NULL || pStruct == NULL)
    {
        return FALSE;
    }
    LPNET_DVR_VOLUME_PLAN_LIST lpPlanList = (LPNET_DVR_VOLUME_PLAN_LIST)pStruct;
    if (lpPlanList->dwSize != sizeof(*lpPlanList))
    {
        return FALSE;
    }
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuf) == NULL)
    {
        return FALSE;
    }
    if (struXml.FindElem("VolumePlanList") && struXml.IntoElem())
    {
        int nPlanCnt = 0;
        LPNET_DVR_VOLUME_PLAN lpPlan = &lpPlanList->struVolumePlanList[nPlanCnt];
        if (ConvertVolumePlanParamsXmlToStru(struXml, lpPlan))
        {
            nPlanCnt++;
            lpPlan = &lpPlanList->struVolumePlanList[nPlanCnt];
            while (struXml.NextSibElem())
            {
                ConvertVolumePlanParamsXmlToStru(struXml, lpPlan);
                nPlanCnt++;
                if (nPlanCnt >= MAX_NUM_TERGROUP)
                {
                    break;
                }
                lpPlan = &lpPlanList->struVolumePlanList[nPlanCnt];
            }
        }
        struXml.OutOfElem();
        return TRUE;
    }
    
    return FALSE;
}

//音量计划xml转结构体
BOOL ConvertVolumePlanParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
    if (pXmlBuf == NULL || pStruct == NULL)
    {
        return FALSE;
    }
    LPNET_DVR_VOLUME_PLAN lpPlan = (LPNET_DVR_VOLUME_PLAN)pStruct;
    if (lpPlan->dwSize != sizeof(*lpPlan))
    {
        return FALSE;
    }
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuf) == NULL)
    {
        return FALSE;
    }
    return ConvertVolumePlanParamsXmlToStru(struXml, lpPlan);
       
}

//音量计划xml转结构体
BOOL ConvertVolumePlanParamsXmlToStru(CXmlBase& struXml, LPVOID pStruct)
{
    if (pStruct == NULL)
    {
        return FALSE;
    }
    LPNET_DVR_VOLUME_PLAN lpPlan= (LPNET_DVR_VOLUME_PLAN)pStruct;
    
    if (struXml.FindElem("VolumePlan") && struXml.IntoElem())
    {
        ConvertSingleNodeData(lpPlan->sPlanType, struXml, "planType", NODE_STRING_TO_ARRAY, MAX_LEN_32);
        if(0 == strcmp(lpPlan->sPlanType,"daily"))
        {
            if (struXml.FindElem("DailyPlan") && struXml.IntoElem())
            {
                if (struXml.FindElem("VolumeSpanList") && struXml.IntoElem())
                {
                    int nDailyCnt = 0;
                    if (struXml.FindElem("VolumeSpan")&& struXml.IntoElem())
                    {
                        ConvertSingleNodeData(&lpPlan->struDailyPlan[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                        ConvertSingleNodeData(&lpPlan->struDailyPlan[nDailyCnt].dwVolume, struXml, "volume", NODE_STRING_TO_INT);
                        ConvertTimeNodeData(struXml,&lpPlan->struDailyPlan[nDailyCnt].struTime, "beginTime", TRUE);
                        ConvertTimeNodeData(struXml,&lpPlan->struDailyPlan[nDailyCnt].struTimeEnd, "endTime", TRUE);
                        nDailyCnt++;
                        struXml.OutOfElem();
                        while (struXml.NextSibElem()&& struXml.IntoElem())
                        {
                            ConvertSingleNodeData(&lpPlan->struDailyPlan[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                            ConvertSingleNodeData(&lpPlan->struDailyPlan[nDailyCnt].dwVolume, struXml, "volume", NODE_STRING_TO_INT);
                            ConvertTimeNodeData(struXml,&lpPlan->struDailyPlan[nDailyCnt].struTime, "beginTime", TRUE);
                            ConvertTimeNodeData(struXml,&lpPlan->struDailyPlan[nDailyCnt].struTimeEnd, "endTime", TRUE);
               
                            nDailyCnt++;
                            if (nDailyCnt >= MAX_SPANS_A_DAY )
                            {
                                break;
                            }
                            struXml.OutOfElem();
                        }
                        
                    }
                    struXml.OutOfElem();
                }
                struXml.OutOfElem();
            }
        }
        else if(0 == strcmp(lpPlan->sPlanType,"weekly"))
        {
            if (struXml.FindElem("WeeklyPlan") && struXml.IntoElem())
            {
                if (struXml.FindElem("DayList") && struXml.IntoElem())
                {
                    int nDayCnt = 0;
                    if (struXml.FindElem("Day") && struXml.IntoElem())
                    {
                        ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].dwDayID, struXml, "id", NODE_STRING_TO_INT);
                        ConvertSingleNodeData(lpPlan->struWeekyPlan[nDayCnt].sWeekday, struXml, "dayOfWeek", NODE_STRING_TO_ARRAY, MAX_LEN_32);          
                        if (struXml.FindElem("VolumeSpanList") && struXml.IntoElem())
                        {
                            int nDailyCnt = 0;
                            if (struXml.FindElem("VolumeSpan")&& struXml.IntoElem())
                            {
                                ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                                ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwVolume, struXml, "volume", NODE_STRING_TO_INT);
                                ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTime, "beginTime", TRUE);
                                ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTimeEnd, "endTime", TRUE);
                                nDailyCnt++;
                                struXml.OutOfElem();
                                while (struXml.NextSibElem()&& struXml.IntoElem())
                                {
                                    ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                                    ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwVolume, struXml, "volume", NODE_STRING_TO_INT);
                                    ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTime, "beginTime", TRUE);
                                    ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTimeEnd, "endTime", TRUE);
                                    nDailyCnt++;
                                    if (nDailyCnt >= MAX_DAYS_A_WEEK )
                                    {
                                        break;
                                    }
                                    struXml.OutOfElem();
                                }                                
                            }
                            struXml.OutOfElem();
                        }
                        struXml.OutOfElem();
                        nDayCnt++;
                        while(struXml.NextSibElem()&&struXml.IntoElem())
                        {
                            ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].dwDayID, struXml, "id", NODE_STRING_TO_INT);
                            ConvertSingleNodeData(lpPlan->struWeekyPlan[nDayCnt].sWeekday, struXml, "dayOfWeek", NODE_STRING_TO_ARRAY, MAX_LEN_32);          
                            if (struXml.FindElem("VolumeSpanList") && struXml.IntoElem())
                            {
                                int nDailyCnt = 0;
                                if (struXml.FindElem("VolumeSpan")&& struXml.IntoElem())
                                {
                                    ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                                    ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwVolume, struXml, "volume", NODE_STRING_TO_INT);
                                    ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTime, "beginTime", TRUE);
                                    ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTimeEnd, "endTime", TRUE);
                                    nDailyCnt++;
                                    struXml.OutOfElem();
                                    while (struXml.NextSibElem()&& struXml.IntoElem())
                                    {
                                        ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwSpanID, struXml, "id", NODE_STRING_TO_INT);
                                        ConvertSingleNodeData(&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].dwVolume, struXml, "volume", NODE_STRING_TO_INT);
                                        ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTime, "beginTime", TRUE);
                                        ConvertTimeNodeData(struXml,&lpPlan->struWeekyPlan[nDayCnt].struSpanList[nDailyCnt].struTimeEnd, "endTime", TRUE);
                                        nDailyCnt++;
                                        if (nDailyCnt >= MAX_DAYS_A_WEEK )
                                        {
                                            break;
                                        }
                                        struXml.OutOfElem();
                                    }                                
                                }
                                nDayCnt++;
                                struXml.OutOfElem();
                            }
                            struXml.OutOfElem();
                        }
                        
                    }
                    struXml.OutOfElem();
                }
                struXml.OutOfElem();
                
            }
        }
        
        struXml.OutOfElem();
        return TRUE;
        }
        
        return FALSE;
}

//终端服务器配置参数结构体转xml
BOOL ConvertTermServerParamsStruToXml(LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
    if(pStruct == NULL || pXmlBuf == NULL)
    {
        return FALSE;
    }

    LPNET_DVR_PUBLISH_SERVER_ADDR lpAddr = (LPNET_DVR_PUBLISH_SERVER_ADDR)pStruct;
    if (lpAddr->dwSize != sizeof(*lpAddr))
    {
        return FALSE;
    }
    
    CXmlBase struXml;
    struXml.CreateRoot("PublishServerAddr");
    struXml.SetAttribute("version", "2.0");
    if(0 == strcmp(lpAddr->szFormatType,"hostname"))
    {
        ConvertSingleNodeData("hostname", struXml, "addressingFormatType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
        ConvertSingleNodeData(lpAddr->szHostName, struXml, "hostName", NODE_ARRAY_TO_STRING, MAX_LEN_32);
    }
    else if(0 == strcmp(lpAddr->szFormatType,"ipaddress"))
    {
        ConvertSingleNodeData("ipaddress", struXml, "addressingFormatType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
        ConvertSingleNodeData(lpAddr->szIpv4, struXml, "ipAddress", NODE_ARRAY_TO_STRING, MAX_LEN_32);
    }
    else if(0 == strcmp(lpAddr->szFormatType,"ipv6address"))
    {
        ConvertSingleNodeData("ipaddress", struXml, "addressingFormatType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
        ConvertSingleNodeData(lpAddr->szIpv6, struXml, "ipAddress", NODE_ARRAY_TO_STRING, MAX_LEN_32);
    }
    ConvertSingleNodeData(&lpAddr->wPort, struXml, "portNo", NODE_WORD_TO_STRING);
    ConvertSingleNodeData(&lpAddr->byRegister, struXml, "registerStatus", NODE_BOOL_TO_STRING);
    ConvertSingleNodeData(lpAddr->szOparaType, struXml, "operateType", NODE_ARRAY_TO_STRING, MAX_LEN_32);
    ConvertSingleNodeData(lpAddr->szUserName, struXml, "userName", NODE_ARRAY_TO_STRING, MAX_LEN_32);
    ConvertSingleNodeData(lpAddr->szPwd, struXml, "password", NODE_ARRAY_TO_STRING, MAX_LEN_32);
    if(0 == strcmp(lpAddr->szOparaType,"byTerminal"))
    {
        if (struXml.AddNode("TerminalNoList"))
        {
            for (int nTer = 0; nTer < lpAddr->dwTerminalNo; nTer++)
            {
                ConvertSingleNodeData(&lpAddr->arrTerminal[nTer], struXml, "terminalNo", NODE_INT_TO_STRING);  
            }
            struXml.OutOfElem();
        }
    }
    else if(0 == strcmp(lpAddr->szOparaType,"byGroup"))
    {
        if (struXml.AddNode("TerminalGroupNoList"))
        {
            for (int nGroup = 0; nGroup < lpAddr->dwGroupNo; nGroup++)
            {
                ConvertSingleNodeData(&lpAddr->arrGroup[nGroup], struXml, "terminalGroupNo", NODE_INT_TO_STRING);  
            }
            struXml.OutOfElem();
        }
    }
    else if (0 == strcmp(lpAddr->szOparaType, "byOrg"))
    {
        if (struXml.AddNode("OrgNoList"))
        {
            for (int nGroup = 0; nGroup < lpAddr->dwGroupNo; nGroup++)
            {
                ConvertSingleNodeData(&lpAddr->arrGroup[nGroup], struXml, "orgNo", NODE_INT_TO_STRING);
            }
            struXml.OutOfElem();
        }
    }
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }
    
	return TRUE;
    

}

//终端服务器配置xml转结构体
BOOL ConvertTerServerParamsXmlToStru(const char* pXmlBuf, LPVOID pStruct)
{
    if (pXmlBuf == NULL || pStruct == NULL)
    {
        return FALSE;
    }
    LPNET_DVR_PUBLISH_SERVER_ADDR lpAddr = (LPNET_DVR_PUBLISH_SERVER_ADDR)pStruct;
    if (lpAddr->dwSize != sizeof(*lpAddr))
    {
        return FALSE;
    }
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuf) == NULL)
    {
        return FALSE;
    }
    
    if (struXml.FindElem("PublishServerAddr") && struXml.IntoElem())
	{
        ConvertSingleNodeData(lpAddr->szFormatType, struXml, "addressingFormatType", NODE_STRING_TO_ARRAY,MAX_LEN_32);
        if(strcmp(lpAddr->szFormatType,"hostname"))
        {
            ConvertSingleNodeData(lpAddr->szHostName, struXml, "hostName", NODE_STRING_TO_ARRAY,MAX_LEN_32);
        }
        else if(strcmp(lpAddr->szFormatType,"ipaddress"))
        {
            ConvertSingleNodeData(lpAddr->szIpv4, struXml, "ipAddress", NODE_STRING_TO_ARRAY,MAX_LEN_32);
        }
        else if(strcmp(lpAddr->szFormatType,"ipaddress"))
        {
            ConvertSingleNodeData(lpAddr->szIpv6, struXml, "ipv6Address", NODE_STRING_TO_ARRAY,MAX_LEN_32);
            memcpy(lpAddr->szFormatType,"ipv6address",strlen("ipv6address"));
        }
         ConvertSingleNodeData(&lpAddr->wPort, struXml, "portNo", NODE_STRING_TO_WORD);
         ConvertSingleNodeData(&lpAddr->byRegister, struXml, "registerStatus", NODE_STRING_TO_BOOL);
         ConvertSingleNodeData(lpAddr->szOparaType, struXml, "operateType", NODE_STRING_TO_ARRAY,MAX_LEN_32);
         if(strcmp(lpAddr->szOparaType,"byTerminal"))
         {
             if (struXml.FindElem("TerminalNoList") && struXml.IntoElem())
             {
                 ConvertSingleNodeData(&lpAddr->arrTerminal[lpAddr->dwTerminalNo], struXml, "terminalNo", NODE_STRING_TO_INT);
                 lpAddr->dwTerminalNo++;
                 while (struXml.NextSibElem())
                 {
                     ConvertSingleNodeData(&lpAddr->arrTerminal[lpAddr->dwTerminalNo], struXml, "terminalNo", NODE_STRING_TO_INT);
                     lpAddr->dwTerminalNo++;
                     if(lpAddr->dwTerminalNo > MAX_NUM_TERMINAL)
                     {
                         break;
                     }
                 }
                 struXml.OutOfElem();
                
             }
         }
         else if(strcmp(lpAddr->szOparaType,"byGroup"))
         {
             if (struXml.FindElem("TerminalGroupNoList") && struXml.IntoElem())
             {
                 ConvertSingleNodeData(&lpAddr->arrGroup[lpAddr->dwGroupNo], struXml, "terminalGroupNo", NODE_STRING_TO_INT);
                 lpAddr->dwGroupNo++;
                 while (struXml.NextSibElem())
                 {
                     ConvertSingleNodeData(&lpAddr->arrTerminal[lpAddr->dwGroupNo], struXml, "terminalGroupNo", NODE_STRING_TO_INT);
                     lpAddr->dwGroupNo++;
                     if(lpAddr->dwGroupNo > MAX_NUM_TERGROUP)
                     {
                         break;
                     }
                 }
                 struXml.OutOfElem();
                 
             }
         }
         struXml.OutOfElem();
        return TRUE;
    }
    return FALSE;

}

//批量节目id转xml
BOOL ConvertProgramIdToXml(LPVOID pStruct, int Count,char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (pStruct == NULL || pXmlBuf == NULL)
    {
        return FALSE;
    }

    int *ArrId = (int *)pStruct;

    CXmlBase struXml;
    struXml.CreateRoot("ProgramIdList");
    struXml.SetAttribute("version", "2.0");
    for (int nCnt = 0; nCnt<Count; nCnt++)
    {
          ConvertSingleNodeData(&ArrId[nCnt], struXml, "programId", NODE_INT_TO_STRING);
    }
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }

    return TRUE;
}

//批量素材id转xml
BOOL ConvertMaterialIdToXml(LPVOID pStruct, int Count, char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (pStruct == NULL || pXmlBuf == NULL)
    {
        return FALSE;
    }

    int *ArrId = (int *)pStruct;

    CXmlBase struXml;
    struXml.CreateRoot("MaterialIdList");
    struXml.SetAttribute("version", "2.0");
    for (int nCnt = 0; nCnt < Count; nCnt++)
    {
        ConvertSingleNodeData(&ArrId[nCnt], struXml, "materialId", NODE_INT_TO_STRING);
    }
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }

    return TRUE;
}

//批量素材参数配置转XML
BOOL ConvertMaterialBatchInfoToXml(LPVOID ArrayId, int CountId, LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (ArrayId == NULL|| pStruct == NULL || pXmlBuf == NULL)
    {
        return FALSE;
    }

    int *Array = (int *)ArrayId;
    LPNET_DVR_MATERIAL lpMaterial = (LPNET_DVR_MATERIAL)pStruct;
    CXmlBase struXml;
    struXml.CreateRoot("MaterialBatchInfo");
    struXml.SetAttribute("version", "2.0");
    ConvertSingleNodeData(lpMaterial->szOperatorType, struXml, "operatorType", NODE_ARRAY_TO_STRING);
    if (!(strcmp(lpMaterial->szOperatorType, "property")))
    {
        ConvertSingleNodeData(lpMaterial->szSharePropery, struXml, "shareProperty", NODE_ARRAY_TO_STRING);
    }
    else if (!(strcmp(lpMaterial->szOperatorType, "remark")))
    {
        ConvertSingleNodeData(lpMaterial->szMaterialRemarks, struXml, "materialRemarks", NODE_ARRAY_TO_STRING);
    }
    else if (!(strcmp(lpMaterial->szOperatorType, "approve")))
    {
        ConvertSingleNodeData(lpMaterial->szApprove, struXml, "approveState", NODE_ARRAY_TO_STRING);
        ConvertSingleNodeData(lpMaterial->szApproveRemarks, struXml, "approveRemarks", NODE_ARRAY_TO_STRING);
    }
    if (struXml.AddNode("MaterialIdList"))
    {
        for (int nCnt = 0; nCnt < CountId; nCnt++)
        {
            ConvertSingleNodeData(&Array[nCnt], struXml, "materialId", NODE_INT_TO_STRING);
        }
        struXml.OutOfElem();
    }
    if(!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }

    return TRUE;
}

//批量日程计划id转xml
BOOL ConvertScheduleIdToXml(LPVOID pStruct, int Count, char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (pStruct == NULL || pXmlBuf == NULL)
    {
        return FALSE;
    }

    int *ArrId = (int *)pStruct;

    CXmlBase struXml;
    struXml.CreateRoot("PlayScheduleIdList");
    struXml.SetAttribute("version", "2.0");
    for (int nCnt = 0; nCnt < Count; nCnt++)
    {
        ConvertSingleNodeData(&ArrId[nCnt], struXml, "playScheduleId", NODE_INT_TO_STRING);
    }
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }

    return TRUE;
}

//批量终端id转xml
BOOL ConvertTerminalIdToXml(LPVOID pStruct, int Count, char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (pStruct == NULL || pXmlBuf == NULL)
    {
        return FALSE;
    }

    int *ArrId = (int *)pStruct;

    CXmlBase struXml;
    struXml.CreateRoot("TerminalsIdList");
    struXml.SetAttribute("version", "2.0");
    for (int nCnt = 0; nCnt < Count; nCnt++)
    {
        ConvertSingleNodeData(&ArrId[nCnt], struXml, "terminalsId", NODE_INT_TO_STRING);
    }
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }

    return TRUE;
}

//批量节目参数配置转XML
BOOL ConvertProgramBatchInfoToXml(LPVOID ArrayId, int CountId, LPVOID pStruct, char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (ArrayId == NULL || pStruct == NULL || pXmlBuf == NULL)
    {
        return FALSE;
    }

    int *Array = (int *)ArrayId;
    LPNET_DVR_PROGRAM lpProgram = (LPNET_DVR_PROGRAM)pStruct;
    CXmlBase struXml;
    struXml.CreateRoot("ProgramBatchInfo");
    struXml.SetAttribute("version", "2.0");
    ConvertSingleNodeData(lpProgram->szOperatorType, struXml, "operatorType", NODE_ARRAY_TO_STRING);
    if (!(strcmp(lpProgram->szOperatorType, "property")))
    {
        ConvertSingleNodeData(lpProgram->szShareProp, struXml, "shareProperty", NODE_ARRAY_TO_STRING);
    }
    else if (!(strcmp(lpProgram->szOperatorType, "remark")))
    {
        ConvertSingleNodeData(lpProgram->szProgramRemarks, struXml, "programRemarks", NODE_ARRAY_TO_STRING);
    }
    else if (!(strcmp(lpProgram->szOperatorType, "approve")))
    {
        ConvertSingleNodeData(lpProgram->szApprove, struXml, "approveState", NODE_ARRAY_TO_STRING);
        ConvertSingleNodeData(lpProgram->szApproveRemarks, struXml, "approveRemarks", NODE_ARRAY_TO_STRING);
    }
    if (struXml.AddNode("ProgramIdList"))
    {
        for (int nCnt = 0; nCnt < CountId; nCnt++)
        {
            ConvertSingleNodeData(&Array[nCnt], struXml, "programId", NODE_INT_TO_STRING);
        }
        struXml.OutOfElem();
    }
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }

    return TRUE;
}