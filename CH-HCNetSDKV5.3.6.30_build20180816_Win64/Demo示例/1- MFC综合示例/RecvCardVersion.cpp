#include "RecvCardVersion.h"  
#include "ParseXMLHelper.h"
using namespace InformationReleaseSystem;

//////////////////////////////////////////////////////////////////////////
//RecvCardVersion

/** @fn  RecvCardVersion::RecvCardVersion(xmlNodePtr pNode)
 *  @brief 构造函数
 *  @param (IN)xmlNodePtr pNode 节点指针
 *  @return None
 */
RecvCardVersion::RecvCardVersion(xmlNodePtr pNode)
{
    Parse(pNode);
}

/** @fn voidRecvCardVersion::Parse(xmlNodePtr pNode)
 *  @brief 解析函数
 *  @param (IN)xmlNodePtr pNode 节点指针
 *  @return void
 */
void RecvCardVersion::Parse(xmlNodePtr pNode)
{
    if (NULL == pNode)
    {
        return;
    }
    
    pNode = pNode->children;
    if (NULL == pNode)
    {
        return;
    }


    if (FindElem(pNode, "boardType"))
    {
        strBoardType = GetValueFormNodePtr<string>(pNode);
        pNode = pNode->next;
    }

    if (FindElem(pNode, "softwareType"))
    {
        strSoftwareType = GetValueFormNodePtr<string>(pNode);
        pNode = pNode->next;
    }

    if (FindElem(pNode, "softwareVersion"))
    {
        strSoftwareVersion = GetValueFormNodePtr<string>(pNode);
        pNode = pNode->next;
    }
    
}

/** @fn xmlNodePtrRecvCardVersion::CreateXmlNodePtr()
 *  @brief 生成xml节点
 *  @return 节点指针
 */
xmlNodePtr RecvCardVersion::CreateXmlNodePtr()
{
    if (g_hDllInst == NULL)
    {
        return NULL;
    }

    dllxmlNewChild xmlNewChild = (dllxmlNewChild)GetProcAddress(g_hDllInst, "xmlNewChild");
    dllxmlNewNode xmlNewNode = (dllxmlNewNode)GetProcAddress(g_hDllInst, "xmlNewNode");


    xmlNodePtr pNodeRecvCardVersion = xmlNewNode(NULL, BAD_CAST"RecvCardVersion");

    xmlNewChild(pNodeRecvCardVersion, NULL, BAD_CAST"boardType", (xmlChar *)strBoardType.c_str());

    xmlNewChild(pNodeRecvCardVersion, NULL, BAD_CAST"softwareType", (xmlChar *)strSoftwareType.c_str());

    xmlNewChild(pNodeRecvCardVersion, NULL, BAD_CAST"softwareVersion", (xmlChar *)strSoftwareVersion.c_str());

    return pNodeRecvCardVersion;
}


