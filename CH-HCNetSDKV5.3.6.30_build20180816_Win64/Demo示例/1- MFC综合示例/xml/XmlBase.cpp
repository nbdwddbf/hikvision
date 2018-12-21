
#include "XmlBase.h"

/****************************************************
函数名:     CXmlBase
函数描述: 构造函数
输入参数: 无  
输出参数: 无  
返回值:   无
*****************************************************/
CXmlBase::CXmlBase()
{
	m_pBase = NULL;
}

/****************************************************
函数名:   CXmlBase
函数描述: 拷贝构造函数
输入参数: 
copy:	CXmlBase对象  
输出参数: 无  
返回值:   无
*****************************************************/
CXmlBase::CXmlBase(CXmlBase const &struCopy)
{
	m_doc = struCopy.m_doc;
	m_pBase = m_doc.RootElement();
}

/****************************************************
函数名:   ~CXmlBase
函数描述: 析构函数
输入参数: 无  
输出参数: 无  
返回值:   无
*****************************************************/
CXmlBase::~CXmlBase()
{
	m_pBase = NULL;
}

/****************************************************
函数名:   LoadFile
函数描述: 载入XML文件
输入参数:   
pFileName: XML文件名
输出参数:  无
返回值:  
true—载入成功,false—载入失败 
*****************************************************/
bool CXmlBase::LoadFile(const char* pFileName)
{
	m_doc.Clear();
	return m_doc.LoadFile(pFileName);
}

/****************************************************
函数名:   FindElem
函数描述: 在当前层中查找节点
输入参数:   
pName: 节点名称
输出参数:  无
返回值:  
true—已找到,false—未找到 
*****************************************************/
bool CXmlBase::FindElem(const char* pName)
{
	if (m_pBase == NULL)
	{
		m_pBase = m_doc.RootElement();
//		m_pBase = m_pBase->FirstChildElement();
	}
	TiXmlElement* pTmp = m_pBase;
	while(m_pBase != NULL)
	{				
		string str = m_pBase->Value();
		if (str.compare(pName) == 0)
		{			
			return true;
		}
		m_pBase = m_pBase->NextSiblingElement();
	}
	m_pBase = pTmp;
	return false;
}

/****************************************************
函数名:   IntoElem
函数描述: 指向当前节点的第一个子节点
输入参数:  无
输出参数:  无
返回值:  
true—有子节点并已指向该子节点,false—无子节点 
*****************************************************/
bool CXmlBase::IntoElem()
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlElement *pTmp = m_pBase->FirstChildElement();	
	if (pTmp == NULL)
	{
		return false;
	}
	m_pBase = pTmp;
	return true;
}

/****************************************************
函数名:   OutOfElem
函数描述: 指向当前节点的父节点
输入参数:  无
输出参数:  无
返回值:  
true—有父节点并已指向父节点,false—无父节点 
*****************************************************/
bool CXmlBase::OutOfElem()
{
	if (m_pBase == NULL)
	{
		return false;
	}
	m_pBase = m_pBase->Parent()->ToElement();
	if (m_pBase == NULL)
	{
		return false;
	}
	return true;
}

/****************************************************
函数名:   GetData
函数描述: 获取当前节点文本数据
输入参数:  无
输出参数:  无
返回值:  当前节点文本数据 
*****************************************************/
string  CXmlBase::GetData() const
{
	string str = "";
	if (m_pBase == NULL)
	{
		return str;
	}

	if (m_pBase->GetText() == NULL)
	{
        return str;
	}

	return  m_pBase->GetText();
}

/****************************************************
函数名:   GetNodeName
函数描述: 获取当前节点名称
输入参数:  无
输出参数:  无
返回值:  当前节点名称
*****************************************************/
string	CXmlBase::GetNodeName() const
{
	if (m_pBase == NULL)
	{
		return NULL;
	}
	return m_pBase->Value();
}

/****************************************************
函数名:   ModifyData
函数描述: 修改节点文本数据
输入参数: 
strElem:  节点名
pData:	  新文本数据
输出参数: 无
返回值:   true-修改成功,false-无此节点
*****************************************************/
bool	CXmlBase::ModifyData(const string &strElem, const char *pData)
{
	if (!FindElem(strElem.c_str()))
	{
		return false;
	}
	TiXmlNode *pNode = m_pBase->FirstChild();
	pNode->SetValue(pData);
	return true;
}

/****************************************************
函数名:   SetRoot
函数描述: 设置根节点
输入参数: 无
输出参数: 无
返回值:   true--成功,false--失败
*****************************************************/
bool CXmlBase::SetRoot()
{
	m_pBase = m_doc.RootElement();
	if (m_pBase == NULL)
	{
		return false;
	}
	return true;
}

/****************************************************
函数名:   Parse
函数描述: 解析XML文本数据，建立DOM树
输入参数: 
pBuf:	  XML文本数据
输出参数: 无
返回值:   
*****************************************************/
const void*	CXmlBase::Parse(const char *pBuf)
{
	m_doc.Clear();
	return m_doc.Parse(pBuf);
}

/****************************************************
函数名:   WriteToFile
函数描述: 数据存文件
输入参数: 
pFileName:文件名
输出参数: 无
返回值:   true—保存成功,false—保存失败
*****************************************************/
bool	CXmlBase::WriteToFile(const char* pFileName) const
{ 	
	return m_doc.SaveFile(pFileName);
}

/****************************************************
函数名:   AddNode
函数描述: 在当前节点插入子节点，并指向该子节点
输入参数: 
strElem:  节点名
strTxt:   节点文本
输出参数: 无
返回值:   true—插入成功,false—插入失败
*****************************************************/
bool	CXmlBase::AddNode(const string &strElem, const string &strTxt)
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlNode *pNode = m_pBase->LinkEndChild(new TiXmlElement(strElem.c_str()));
	pNode->LinkEndChild(new TiXmlText(strTxt.c_str()));
	m_pBase = pNode->ToElement();
	return true;
}

/****************************************************
函数名:   AddNode
函数描述: 在当前节点插入子节点，并指向该子节点
输入参数: 
strElem:  节点名
输出参数: 无
返回值:   true—插入成功,false—插入失败
*****************************************************/
bool	CXmlBase::AddNode(const string &strElem)
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlNode *pNode = m_pBase->LinkEndChild(new TiXmlElement(strElem.c_str()));
	m_pBase = pNode->ToElement();
	return true;
}

/****************************************************
函数名:   AddNode
函数描述: 在当前节点插入子节点，并指向该子节点
输入参数: 
abtNode:  CXmlBase对象,可以有多级节点
输出参数: 无
返回值:   true—插入成功,false—插入失败
*****************************************************/
bool	CXmlBase::AddNode(const CXmlBase &abtNode)
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlNode *pNode = m_pBase->LinkEndChild(new TiXmlElement(*abtNode.m_pBase));
	m_pBase = pNode->ToElement();
	return true;
}

/****************************************************
函数名:   WriteToBuf
函数描述: 输出全部XML数据至buf
输入参数: 
pBuf:	  缓冲区指针
dwBufSize:缓冲区大小
输出参数: 
dwReturn: XML数据实际占用大小
返回值:   true—成功,false—失败
*****************************************************/
bool	CXmlBase::WriteToBuf(char* pBuf, size_t dwBufSize, int &dwReturn) const
{
	TiXmlPrinter printer;
	m_doc.Accept( &printer );
	if (dwBufSize < printer.Size())
	{
		return false;
	}
	size_t dwSize = printer.Size();
	memcpy(pBuf,printer.CStr(),dwSize);
	dwReturn = printer.Size();
	return true;
}

/****************************************************
函数名:   GetChildren
函数描述: 输出当前节点、子节点及从子节点数据至buf
输入参数: 
pBuf:	  缓冲区指针
dwBufSize:缓冲区大小
输出参数: 
dwReturn: 数据实际占用大小
返回值:   
*****************************************************/
size_t	CXmlBase::GetChildren(char* pBuf, size_t dwBufSize, size_t &dwReturn) const
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlPrinter printer;
	m_pBase->Accept(&printer);
	if (dwBufSize < printer.Size())
	{
		return true;
	}
	memset(pBuf,0,dwBufSize);
	size_t dwSize = printer.Size();
	memcpy(pBuf,printer.CStr(),dwSize);
	dwReturn = printer.Size();
	return false;
}

/****************************************************
函数名:   GetChildren
函数描述: 获取当前节点、子节点及从子节点数据文本
输入参数: 无
输出参数: 无
返回值:   string—文本数据
*****************************************************/
string CXmlBase::GetChildren() const
{
	if (m_pBase == NULL)
	{
		return "";
	}
	TiXmlPrinter printer;
	m_pBase->Accept(&printer);
	return printer.CStr();
}


/****************************************************
函数名:   RemoveNode
函数描述: 删除当前节点,删除后指向父节点
输入参数: 无
输出参数: 无
返回值:   true-删除成功,false—无此节点
*****************************************************/
bool	CXmlBase::RemoveNode()
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlNode *pNode = m_pBase->Parent();
	pNode->RemoveChild(m_pBase);
	m_pBase = pNode->ToElement();
	return true;
}

/****************************************************
函数名:   RemoveNode
函数描述: 删除子节点
输入参数: 
strElem:  子节点名
strTxt:	  子节点文本数据
输出参数: 无
返回值:   true-删除成功,false—失败
****************************************************/
bool	CXmlBase::RemoveNode(const string &strElem,const string &strTxt)
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlElement* pTmp = m_pBase;
	pTmp = pTmp->FirstChildElement();
	while(pTmp != NULL)
	{				
		string str = pTmp->Value();
		if (str == strElem && strTxt.compare(pTmp->GetText()) == 0)
		{			
			return m_pBase->RemoveChild(pTmp);
		}
		pTmp = pTmp->NextSiblingElement();
	}
	return false;
}

/****************************************************
函数名:   RemoveNode
函数描述: 删除子节点
输入参数: 
strElem:  子节点名
输出参数: 无
返回值:   true-删除成功,false—失败
****************************************************/
bool	CXmlBase::RemoveNode(const string &strElem)
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlElement* pTmp = m_pBase;
	pTmp = pTmp->FirstChildElement();
	while(pTmp != NULL)
	{				
		string str = pTmp->Value();
		if (str == strElem)
		{			
			return m_pBase->RemoveChild(pTmp);
		}
		pTmp = pTmp->NextSiblingElement();
	}
	return false;
}

/****************************************************
函数名:   RemoveNode
函数描述: 删除子节点
输入参数: 
nIndex:   子节点序号
输出参数: 无
返回值:   true-删除成功,false—失败
****************************************************/
bool	CXmlBase::RemoveNode(size_t nIndex)
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlElement *pTmp = m_pBase->FirstChildElement(); 
	size_t i;
	for (i = 1; i < nIndex; i++)
	{
		if (pTmp != NULL)
		{
			pTmp = pTmp->NextSiblingElement();
		}	
	}
	m_pBase->RemoveChild(pTmp);

	return true;
}

/****************************************************
函数名:   NextSibElem
函数描述: 指向下一个兄弟节点
输入参数: 无
输出参数: 无
返回值:   true-成功,false—失败
****************************************************/
bool	CXmlBase::NextSibElem()
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlElement *pElem = m_pBase->NextSiblingElement();
	if (!pElem)
	{
		return false;
	}
	m_pBase = pElem;
	return 	true;
}

/****************************************************
函数名:   PreSibElem
函数描述: 指向上一个兄弟节点
输入参数: 无
输出参数: 无
返回值:   true-成功,false—失败
****************************************************/
bool	CXmlBase::PreSibElem()
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlNode *pNode = m_pBase->PreviousSibling();
	if (!pNode)
	{
		return false;
	}	
	m_pBase = pNode->ToElement();	
	return true;
}

/****************************************************
函数名:   RemovePreSibElem
函数描述: 删除上一个兄弟节点
输入参数: 无
输出参数: 无
返回值:   true-成功,false—失败
****************************************************/
bool	CXmlBase::RemovePreSibElem()
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlNode *pNode = m_pBase->PreviousSibling();
	if (pNode == NULL)
	{
		return false;
	}	
	TiXmlNode *pNodeParent = m_pBase->Parent();
	return pNodeParent->RemoveChild(pNode);	
}

/****************************************************
函数名:   RemoveNextSilElem
函数描述: 删除下一个兄弟节点
输入参数: 无
输出参数: 无
返回值:   true-成功,false—失败
****************************************************/
bool	CXmlBase::RemoveNextSilElem()
{
	if (m_pBase == NULL)
	{
		return false;
	}
	TiXmlElement *pElem = m_pBase->NextSiblingElement();
	if (pElem == NULL)
	{
		return false;
	}
	TiXmlNode *pNode = m_pBase->Parent();
	return pNode->RemoveChild(pElem);
}

/****************************************************
函数名:   GetFirstAttributeValue
函数描述: 获取当前节点的第一个属性值
输入参数: 无
输出参数: 无
返回值:   string—属性值
****************************************************/
string	CXmlBase::GetFirstAttributeValue()
{
	if (m_pBase == NULL)
	{
		return NULL;
	}
	TiXmlAttribute *pAttr = NULL;
	pAttr = m_pBase->FirstAttribute();
	if (pAttr == NULL)
	{
		return "";
	}
	return pAttr->Value();
}

/****************************************************
函数名:   GetAttributeValue
函数描述: 获取指定属性的属性值
输入参数: 无
输出参数: 无
返回值:   string—属性值
****************************************************/
string	CXmlBase::GetAttributeValue(const string &strAttriName) const
{
	if (m_pBase == NULL)
	{
		return "";
	}
	return m_pBase->Attribute(strAttriName.c_str());
}

/****************************************************
函数名:   SetAttribute
函数描述: 设置当前节点属性
输入参数: 
pName:	  属性名称
pValue:	  属性值
输出参数: 无
返回值:   true—成功,false—失败
****************************************************/
bool	CXmlBase::SetAttribute(const char* pName, const char* pValue)
{
	if (m_pBase == NULL)
	{
		return false;
	}
	m_pBase->SetAttribute(pName,pValue);
	return true;
}

/****************************************************
函数名:   CreateRoot
函数描述: 创建根节点
输入参数: 
strRoot:  根节点名称
输出参数: 无
返回值:   无
****************************************************/
void	CXmlBase::CreateRoot(const string &strRoot)
{
	TiXmlElement* rootElem = new TiXmlElement(strRoot.c_str());
	m_doc.LinkEndChild(rootElem);
	m_pBase = m_doc.RootElement();
	//2012-01-31 不需要delete,m_doc析构的时候会逐个节点进行delete
	rootElem = NULL;//lint !e423
}
