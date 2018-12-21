
#ifndef __INFORMATIONRELEASESYSTEM__PARSEXMLUTIL_H__
#define __INFORMATIONRELEASESYSTEM__PARSEXMLUTIL_H__


#include "ParseXMLHelper.h"
#include <libxml/parser.h>


using namespace Base;

namespace InformationReleaseSystem
{

    /** @fn void InformationReleaseSystem::TParseXmlDoc(T& tXmlParser, const string& strXmlDoc, const string& strRootNodeName)
     *  @brief 解析XML文档模板方法
     *  @param (OUT)T& tXmlParser xml解析类（必须实现void Parse(xmlNodePtr pNode)方法，否则会编译失败）
     *  @param (IN)const string& strXmlDoc xml字符串
     *  @param (IN)const string& strRootNodeName 根节点名称
     *  @return void
     */
    template<class T>
    void TParseXmlDoc(T& tXmlParser, const string& strXmlDoc, const string& strRootNodeName)
    {
        if (strXmlDoc.empty())
        {
            return;
        }

        string strXmlDocUtf8 = GB2UTF(strXmlDoc.c_str());

        if (g_hDllInst == NULL)
        {
            return;
        }
        dllxmlParseDoc xmlParseDoc = (dllxmlParseDoc)GetProcAddress(g_hDllInst, "xmlParseDoc");
        dllxmlGetLastError xmlGetLastError = (dllxmlGetLastError)GetProcAddress(g_hDllInst, "xmlGetLastError");
        dllxmlDocGetRootElement xmlDocGetRootElement = (dllxmlDocGetRootElement)GetProcAddress(g_hDllInst, "xmlDocGetRootElement");
        dllxmlFreeDoc xmlFreeDoc = (dllxmlFreeDoc)GetProcAddress(g_hDllInst, "xmlFreeDoc");

        //读取xml文件--------
        xmlDocPtr pDoc = xmlParseDoc(BAD_CAST strXmlDocUtf8.c_str()); // 解析文件
        if (NULL == pDoc)
        {
            xmlErrorPtr struXmlError = xmlGetLastError();
            int d =struXmlError->line ;
            string s=struXmlError->message;
           // IVMS_LOG_ERROR("TParseXmlDoc", "Cann't parse the XML, The error is at line[%d], the error message is [%s].", struXmlError->line, struXmlError->message);
            return;
        }

        //获取根节点--------
        xmlNodePtr rootNode = xmlDocGetRootElement(pDoc);
        if (NULL == rootNode)
        {
            xmlErrorPtr struXmlError = xmlGetLastError();
            xmlFreeDoc(pDoc);
            return;
        }

        //开始节点解析--------
        if (!FindElem(rootNode, strRootNodeName.c_str()))
        {
           
            xmlFreeDoc(pDoc);
            return;
        }

        //调用实际解析方法
        tXmlParser.Parse(rootNode);

        //释放xml解析库所用资源
        xmlFreeDoc(pDoc);
    }

    /** @fn std::string InformationReleaseSystem::TGenXmlDoc(const T& tXmlParser, const string& strVersion)
     *  @brief 生成XML文档模板方法
     *  @param (IN)const T& tXmlParser xml解析类（必须实现xmlNodePtr CreateXmlNodePtr()方法，否则会编译失败）
     *  @param (IN)const string& strVersion 版本号
     *  @return XML文档
     */
    template<class T>
    string TGenXmlDoc(T& tXmlParser, const string& strVersion)
    {
        string strXmlDoc;
        xmlDocPtr pXmlDoc = NULL;
        xmlNodePtr pNodeRoot = NULL;

        if (g_hDllInst == NULL)
        {
            return strXmlDoc;
        }
        dllxmlNewProp xmlNewProp = (dllxmlNewProp)GetProcAddress(g_hDllInst, "xmlNewProp");
        dllxmlNewDoc xmlNewDoc = (dllxmlNewDoc)GetProcAddress(g_hDllInst, "xmlNewDoc");
        dllxmlFreeDoc xmlFreeDoc = (dllxmlFreeDoc)GetProcAddress(g_hDllInst, "xmlFreeDoc");
        dllxmlDocSetRootElement xmlDocSetRootElement = (dllxmlDocSetRootElement)GetProcAddress(g_hDllInst, "xmlDocSetRootElement");
        dllxmlDocDumpFormatMemoryEnc xmlDocDumpFormatMemoryEnc = (dllxmlDocDumpFormatMemoryEnc)GetProcAddress(g_hDllInst, "xmlDocDumpFormatMemoryEnc");

        pXmlDoc = xmlNewDoc(BAD_CAST"1.0");
        if (NULL == pXmlDoc)
        {
            return strXmlDoc;
        }

        pNodeRoot = tXmlParser.CreateXmlNodePtr();
        if (NULL == pNodeRoot)
        {
            return strXmlDoc;
        }

        if (!strVersion.empty())
        {
            //增加根节点属性
            xmlNewProp(pNodeRoot, BAD_CAST"version", (xmlChar *)strVersion.c_str());
        }

        //将根节点添加到文档中
        xmlDocSetRootElement(pXmlDoc, pNodeRoot);

        //将文档保存到内存中，按照utf8编码格式保存
        xmlChar* pOutbuf = NULL;
        //保存输出字符长度
        int iOutbufLen = 0;
        xmlDocDumpFormatMemoryEnc(pXmlDoc, &pOutbuf, &iOutbufLen, "UTF-8", 1);

        if (NULL != pOutbuf)
        {
            strXmlDoc = string((char*)pOutbuf);
            xmlFreeFunc(pOutbuf);
        }

        //释放xml解析库所用资源
        xmlFreeDoc(pXmlDoc);

        return strXmlDoc;
    }
}
#endif // __INFORMATIONRELEASESYSTEM__PARSEXMLUTIL_H__

