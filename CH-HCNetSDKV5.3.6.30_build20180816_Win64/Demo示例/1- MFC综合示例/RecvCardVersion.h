#include "ParseXMLUtil.h" 
#include <libxml/tree.h>
#include <libxml/parser.h>

/** @struct RecvCardVersion
 *  @brief RecvCardVersion节点xml解析类
 *
 */
struct RecvCardVersion
{
    explicit RecvCardVersion(xmlNodePtr pNode = NULL);
    void Parse(xmlNodePtr pNode);
    xmlNodePtr CreateXmlNodePtr();

    string strBoardType;
    string strSoftwareType;
    string strSoftwareVersion;
};
