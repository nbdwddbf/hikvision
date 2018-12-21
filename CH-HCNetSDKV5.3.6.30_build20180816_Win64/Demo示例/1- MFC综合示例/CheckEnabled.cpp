#include "CheckEnabled.h"
#include "ParseXMLHelper.h"


using namespace InformationReleaseSystem;
//////////////////////////////////////////////////////////////////////////
//CheckEnabled

/** @fn  CheckEnabled::CheckEnabled(xmlNodePtr pNode)
 *  @brief 构造函数
 *  @param (IN)xmlNodePtr pNode 节点指针
 *  @return None
 */
CheckEnabled::CheckEnabled(xmlNodePtr pNode)
    :iId(0),
     bEnabled(false)
{
    Parse(pNode);
}

/** @fn voidCheckEnabled::Parse(xmlNodePtr pNode)
 *  @brief 解析函数
 *  @param (IN)xmlNodePtr pNode 节点指针
 *  @return void
 */
void CheckEnabled::Parse(xmlNodePtr pNode)
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

    if (FindElem(pNode, "id"))
    {
        iId = GetValueFormNodePtr<int>(pNode);
        pNode = pNode->next;
    }

    if (FindElem(pNode, "enabled"))
    {
        bEnabled = GetValueFormNodePtr<bool>(pNode);
        pNode = pNode->next;
    }
}

/** @fn xmlNodePtrCheckEnabled::CreateXmlNodePtr()
 *  @brief 生成xml节点
 *  @return 节点指针
 */
xmlNodePtr CheckEnabled::CreateXmlNodePtr()
{
    if (g_hDllInst == NULL)
    {
        return NULL;
    }
    dllxmlNewNode xmlNewNode = (dllxmlNewNode)GetProcAddress(g_hDllInst, "xmlNewNode");
    dllxmlNewChild xmlNewChild= (dllxmlNewChild)GetProcAddress(g_hDllInst, "xmlNewChild");
    xmlNodePtr pNodeCheckEnabled = xmlNewNode(NULL, BAD_CAST"CheckEnabled");

    xmlNewChild(pNodeCheckEnabled, NULL, BAD_CAST"id", (xmlChar *)StringUtil::T2String(iId).c_str());

    xmlNewChild(pNodeCheckEnabled, NULL, BAD_CAST"enabled", (xmlChar *)StringUtil::T2String(bEnabled).c_str());

    return pNodeCheckEnabled;
}


