#include "ParseXMLUtil.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
/** @struct Area
 *  @brief Area节点xml解析类
 *
 */
struct Area
{
    explicit Area(xmlNodePtr pNode = NULL);
    void Parse(xmlNodePtr pNode);
    xmlNodePtr CreateXmlNodePtr();

    int iStartLine;
    int iStartColumn;
    int iEndLine;
    int iEndColumn;
};

/** @struct RecvCardArea
 *  @brief RecvCardArea节点xml解析类
 *
 */
struct RecvCardArea
{
    explicit RecvCardArea(xmlNodePtr pNode = NULL);
    void Parse(xmlNodePtr pNode);
    xmlNodePtr CreateXmlNodePtr();

    int iOutputNo;
    Area struArea;
};
