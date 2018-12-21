#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <libxml/tree.h>
#include <libxml/parser.h> 
#include "ParseXMLUtil.h"
/** @struct CheckEnabled
 *  @brief CheckEnabled节点xml解析类
 *
 */
struct CheckEnabled
{
    explicit CheckEnabled(xmlNodePtr pNode = NULL);
    void Parse(xmlNodePtr pNode);
    xmlNodePtr CreateXmlNodePtr();

    int iId;
    bool bEnabled;
};
