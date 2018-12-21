#ifndef _XML_BASE_H
#define _XML_BASE_H

#pragma once
//#include "tinystr.h"
#include "tinyxml.h"
#include <string>
#include <sstream>

using namespace std;

class CXmlBase  
{

private:
	TiXmlDocument m_doc;
	TiXmlElement *m_pBase;

public:
	CXmlBase();
	CXmlBase(CXmlBase const &struCopy);
	virtual ~CXmlBase();
	bool	LoadFile(const char* pFileName);
	const void*	Parse(const char *pBuf);
	bool	FindElem(const char* pName);
	string  GetData() const;
	string	GetNodeName() const;
	size_t	GetChildren(char* pBuf, size_t dwBufSize, size_t &dwReturn) const;
	string  GetChildren() const;
	bool	IntoElem();
	bool	OutOfElem();
	bool	NextSibElem();
	bool	PreSibElem();
	bool	ModifyData(const string &strElem, const char *pData);
	bool	SetRoot();
	bool	WriteToFile(const char* pFileName) const;
	bool	AddNode(const string &strElem, const string &strTxt);
	bool	AddNode(const string &strElem);
	bool	AddNode(const CXmlBase &abtNode);
	bool	WriteToBuf(char* pBuf, size_t dwBufSize, int &dwReturn) const;
	bool	RemoveNode(const string &strElem, const string &strTxt);
	bool	RemoveNode(const string &strElem);
	bool	RemoveNode(size_t nIndex);

	bool	RemoveNode();
	bool	RemovePreSibElem();
	bool	RemoveNextSilElem();
	string	GetFirstAttributeValue();
	string	GetAttributeValue(const string &strAttriName) const;
	bool	SetAttribute(const char* pName, const char* pValue);
	void	CreateRoot(const string &strRoot);
	
};

#endif 
