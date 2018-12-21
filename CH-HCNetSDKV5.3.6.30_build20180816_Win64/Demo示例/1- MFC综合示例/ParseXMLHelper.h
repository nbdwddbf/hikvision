
#ifndef _PARSEXMLHELPER_H_
#define _PARSEXMLHELPER_H_


#include <libxml/parser.h>
#include "StringUtil.h"
#include <windows.h>

using namespace std;
using namespace Base;

extern HINSTANCE g_hDllInst;




namespace InformationReleaseSystem
{
    typedef xmlDocPtr(*dllxmlParseDoc)(const xmlChar *cur);
    typedef xmlErrorPtr(*dllxmlGetLastError)(void);
    typedef xmlNodePtr(*dllxmlDocGetRootElement)(xmlDocPtr doc);
    typedef void(*dllxmlFreeDoc)(xmlDocPtr cur);
    typedef xmlAttrPtr(*dllxmlNewProp)(xmlNodePtr node, const xmlChar *name, const xmlChar *value);
    typedef xmlNodePtr(*dllxmlNewNode)(xmlNsPtr ns, const xmlChar *name);
    typedef xmlDocPtr(*dllxmlNewDoc)(const xmlChar *version);
    typedef xmlNodePtr(*dllxmlNewChild)(xmlNodePtr parent, xmlNsPtr ns, const xmlChar *name, const xmlChar *content);
    typedef xmlChar*(*dllxmlNodeGetContent)(xmlNodePtr cur);
    typedef int(*dllxmlStrcmp)(const xmlChar *str1, const xmlChar *str2);
    typedef xmlNodePtr(*dllxmlDocSetRootElement)(xmlDocPtr doc, xmlNodePtr root);
    typedef void(*dllxmlDocDumpFormatMemoryEnc)(xmlDocPtr out_doc, xmlChar **doc_txt_ptr, int * doc_txt_len, const char *txt_encoding, int format);
    typedef xmlNodePtr(*dllxmlAddChild)(xmlNodePtr parent, xmlNodePtr cur);
    //寻找节点
    bool FindElem(xmlNodePtr& pNode, const char* pCStr);
    //GB2312转UTF-8
    string GB2UTF(const char* gb2312);
    //GB2312转UTF-8
    string UTF2GB(const char* utf8);
    //xml特殊字符替换
    string SpecialCharacterReplace(string strInfo);

    //!! 现在只需要二种（unsigned int; int;）
    template<typename T>
    T GetValueFormNodePtr(xmlNodePtr pNode)
    {
        if (g_hDllInst == NULL)
        {
            return NULL;
        }

        dllxmlNodeGetContent xmlNodeGetContent = (dllxmlNodeGetContent)GetProcAddress(g_hDllInst, "xmlNodeGetContent");
        xmlChar* pContent = xmlNodeGetContent(pNode);
        T tValue = StringUtil::String2T<T>(StringUtil::T2String(pContent));//xmlChar*变为string,再变为Bool
        xmlFreeFunc((void*)pContent);

        return tValue;
    }

    //string类型 模板特例化，避免使用StringUtil::String2T导致含空格的字符串内容丢失
    template<>
    inline string GetValueFormNodePtr(xmlNodePtr pNode)
    {
        if (g_hDllInst == NULL)
        {
            return "";
        }

        dllxmlNodeGetContent xmlNodeGetContent= (dllxmlNodeGetContent)GetProcAddress(g_hDllInst, "xmlNodeGetContent");
        xmlChar* pContent = xmlNodeGetContent(pNode);
        string strContent((char*)pContent);
        xmlFreeFunc((void*)pContent);

        return strContent;
    }

    // 特化bool值
    // 适合<xxx>true</xxx> <xxx>false</xxx>
    //      <xxx>1</xxx> <xxx>0</xxx> 
    template<>
    inline bool GetValueFormNodePtr(xmlNodePtr pNode)
    {
        if (g_hDllInst == NULL)
        {
            return false;
        }

        dllxmlNodeGetContent xmlNodeGetContent=(dllxmlNodeGetContent)GetProcAddress(g_hDllInst, "xmlNodeGetContent");
        xmlChar* pContent = xmlNodeGetContent(pNode);
        string strContent = StringUtil::T2String(pContent);
        bool bValue = ("true" == strContent || "1" == strContent);
        xmlFreeFunc((void*)pContent);

        return bValue;
    }

}
#endif    //_PARSEXMLHELPER_H_