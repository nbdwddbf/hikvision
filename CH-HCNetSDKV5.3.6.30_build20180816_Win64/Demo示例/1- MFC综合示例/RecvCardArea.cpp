#include "RecvCardArea.h"

extern  HINSTANCE g_hDllInst;

using namespace InformationReleaseSystem;
//////////////////////////////////////////////////////////////////////////
//Area

/** @fn  Area::Area(xmlNodePtr pNode)
 *  @brief 构造函数
 *  @param (IN)xmlNodePtr pNode 节点指针
 *  @return None
 */


Area::Area(xmlNodePtr pNode)
    :iStartLine(0),
     iStartColumn(0),
     iEndLine(0),
     iEndColumn(0)
{
    Parse(pNode);
}

/** @fn voidArea::Parse(xmlNodePtr pNode)
 *  @brief 解析函数
 *  @param (IN)xmlNodePtr pNode 节点指针
 *  @return void
 */
void Area::Parse(xmlNodePtr pNode)
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


    if (FindElem(pNode, "startLine"))
    {
        iStartLine = GetValueFormNodePtr<int>(pNode);
        pNode = pNode->next;
    }

    if (FindElem(pNode, "startColumn"))
    {
        iStartColumn = GetValueFormNodePtr<int>(pNode);
        pNode = pNode->next;
    }

    if (FindElem(pNode, "endLine"))
    {
        iEndLine = GetValueFormNodePtr<int>(pNode);
        pNode = pNode->next;
    }

    if (FindElem(pNode, "endColumn"))
    {
        iEndColumn = GetValueFormNodePtr<int>(pNode);
        pNode = pNode->next;
    }
}

/** @fn xmlNodePtrArea::CreateXmlNodePtr()
 *  @brief 生成xml节点
 *  @return 节点指针
 */
xmlNodePtr Area::CreateXmlNodePtr()
{
    if (g_hDllInst == NULL)
    {
        return NULL;
    }

    dllxmlNewChild xmlNewChild= (dllxmlNewChild)GetProcAddress(g_hDllInst, "xmlNewChild");
    dllxmlNewNode xmlNewNode = (dllxmlNewNode)GetProcAddress(g_hDllInst, "xmlNewNode");
    xmlNodePtr pNodeArea = xmlNewNode(NULL, BAD_CAST"Area");

    xmlNewChild(pNodeArea, NULL, BAD_CAST"startLine", (xmlChar *)StringUtil::T2String(iStartLine).c_str());

    xmlNewChild(pNodeArea, NULL, BAD_CAST"startColumn", (xmlChar *)StringUtil::T2String(iStartColumn).c_str());

    xmlNewChild(pNodeArea, NULL, BAD_CAST"endLine", (xmlChar *)StringUtil::T2String(iEndLine).c_str());

    xmlNewChild(pNodeArea, NULL, BAD_CAST"endColumn", (xmlChar *)StringUtil::T2String(iEndColumn).c_str());

    return pNodeArea;
}



//////////////////////////////////////////////////////////////////////////
//RecvCardArea

/** @fn  RecvCardArea::RecvCardArea(xmlNodePtr pNode)
 *  @brief 构造函数
 *  @param (IN)xmlNodePtr pNode 节点指针
 *  @return None
 */
RecvCardArea::RecvCardArea(xmlNodePtr pNode)
    :iOutputNo(0)
{
    Parse(pNode);
}

/** @fn voidRecvCardArea::Parse(xmlNodePtr pNode)
 *  @brief 解析函数
 *  @param (IN)xmlNodePtr pNode 节点指针
 *  @return void
 */
void RecvCardArea::Parse(xmlNodePtr pNode)
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


    if (FindElem(pNode, "outputNo"))
    {
        iOutputNo = GetValueFormNodePtr<int>(pNode);
        pNode = pNode->next;
    }

    if (FindElem(pNode, "Area"))
    {
        struArea.Parse(pNode);
        pNode = pNode->next;
    }
}

/** @fn xmlNodePtrRecvCardArea::CreateXmlNodePtr()
 *  @brief 生成xml节点
 *  @return 节点指针
 */
xmlNodePtr RecvCardArea::CreateXmlNodePtr()
{
    if (g_hDllInst == NULL)
    {
        return NULL;
    }
    dllxmlNewChild xmlNewChild = (dllxmlNewChild)GetProcAddress(g_hDllInst, "xmlNewChild");
    dllxmlNewNode xmlNewNode = (dllxmlNewNode)GetProcAddress(g_hDllInst, "xmlNewNode");
    dllxmlAddChild xmlAddChild = (dllxmlAddChild)GetProcAddress(g_hDllInst, "xmlAddChild");
    xmlNodePtr pNodeRecvCardArea = xmlNewNode(NULL, BAD_CAST"RecvCardArea");

    xmlNewChild(pNodeRecvCardArea, NULL, BAD_CAST"outputNo", (xmlChar *)StringUtil::T2String(iOutputNo).c_str());

    xmlNodePtr pNodeArea = struArea.CreateXmlNodePtr();
    xmlAddChild(pNodeRecvCardArea, pNodeArea);

    return pNodeRecvCardArea;
}


