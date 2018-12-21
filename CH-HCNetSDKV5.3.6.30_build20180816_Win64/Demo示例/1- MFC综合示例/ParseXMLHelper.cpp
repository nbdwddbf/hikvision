

#include "stdafx.h"
#include "ParseXMLHelper.h"
//#include "iVMSGUIToolkit/PublicControlFunc.h"


namespace InformationReleaseSystem
{
    /** @fn: InformationReleaseSystem::FindElem
    * @brief: 遍历节点下全部节点，若找到则返回true
    * @param: xmlNodePtr & pNode  节点
    * @param: const char * pCStr  查找的节点名称
    * @return: bool
    */
    bool FindElem(xmlNodePtr& pNode, const char* pCStr)
    {
        if (g_hDllInst == NULL)
        {
            return false;
        }
        dllxmlStrcmp xmlStrcmp = (dllxmlStrcmp)GetProcAddress(g_hDllInst, "xmlStrcmp");

        xmlNodePtr pFindNode = pNode;

        while (1)
        {
            while (pFindNode != NULL && pFindNode->type != XML_ELEMENT_NODE)
            {
                pFindNode = pFindNode->next;
            }

            if (pFindNode == NULL)
            {
                break;
            }

            // 因为总是要在 xmlChar* 和 char* 之间进行类型转换，所以定义了一个宏 BAD_CAST ，其定义如下： xmlstring.h
            //!! 原则上来说，unsigned char和char之间进行强制类型转换是没有问题的
            //!! xmlChar* == unsigned char*
            if (xmlStrcmp(pFindNode->name, BAD_CAST(pCStr)) == 0)
            {
                pNode = pFindNode;
                return true;
            }

            pFindNode = pFindNode->next;
        }

        return false;
    }

    /** @fn: InformationReleaseSystem::GB2UTF
    * @brief: GB2312转UTF-8
    * @param: const char * gb2312
    * @return: string
    */
    string GB2UTF(const char* gb2312)
    {
        int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
        wchar_t* wstr = new wchar_t[len + 1];
        memset(wstr, 0, len + 1);
        MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
        len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
        char* sztr = new char[len + 1];
        memset(sztr, 0, len + 1);
        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, sztr, len, NULL, NULL);
        if (wstr) delete[] wstr;

        string str = sztr;
        delete[] sztr;
        sztr = NULL;
        return str;
    }

    /** @fn: InformationReleaseSystem::U2G
    * @brief: UTF-8 转GB2312
    * @param: const char * utf8
    * @return: string
    */
    string UTF2GB(const char* utf8)
    {
        int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
        wchar_t* wstr = new wchar_t[len + 1];
        memset(wstr, 0, len + 1);
        MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
        len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
        char* sztr = new char[len + 1];
        memset(sztr, 0, len + 1);
        WideCharToMultiByte(CP_ACP, 0, wstr, -1, sztr, len, NULL, NULL);
        if (wstr) delete[] wstr;

        string str = sztr;
        delete[] sztr;
        sztr = NULL;
        return str;
    }

    /** @fn: InformationReleaseSystem::SpecialCharacterReplace
    * @brief: xml特殊字符替换函数
    * @brief: 字符替换内容
    * @brief: 1. " 转 &quot;  2. ' 转 &apos;  3. & 转 &amp;  4. < 转 &lt;  5. > 转 &gt;
    * @param: string strInfo
    * @return: std::string
    */
    string SpecialCharacterReplace(string strInfo)
    {
        //         QString qstrInfo = iVMSGUIToolkit::ConvertToUnicode(strInfo.c_str());
        //         //必须要先转&，不然会把其他转义字符中的&再次转义
        //         qstrInfo.replace(QString("&"), QString("&amp;"));
        //         qstrInfo.replace(QString("\""), QString("&quot;"));
        //         qstrInfo.replace(QString("'"), QString("&apos;"));
        //         qstrInfo.replace(QString("<"), QString("&lt;"));
        //         qstrInfo.replace(QString(">"), QString("&gt;"));
        // 
        //         return iVMSGUIToolkit::ConvertFromUnicode(qstrInfo).data();
        string strTemp = strInfo;
        strTemp = strTemp.replace(strTemp.begin(), strTemp.end(), "&", "&amp;");
        strTemp = strTemp.replace(strInfo.begin(), strInfo.end(), "\"", "&quot;");
        strTemp = strTemp.replace(strInfo.begin(), strInfo.end(), "'", "&apos;");
        strTemp = strTemp.replace(strInfo.begin(), strInfo.end(), "<", "&lt;");
        strTemp = strTemp.replace(strInfo.begin(), strInfo.end(), ">", "&gt;");
        return strTemp;
    }


    /** @fn bool InformationReleaseSystem::GetValueFormNodePtr(xmlNodePtr pNode)
    *  @brief 节点值解析函数
    *  @param (IN)xmlNodePtr pNode 节点
    *  @return 值
    */
}