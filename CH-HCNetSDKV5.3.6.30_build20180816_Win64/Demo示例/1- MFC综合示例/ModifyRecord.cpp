#include "StdAfx.h"
#include "ModifyRecord.h"

ModRecord::ModRecord():
	m_iMaxNum(0),
	m_iModNum(0),
	m_iUsedNum(0),
	m_pRecord (NULL),
	m_iItemSize(0),
	m_pSrc(NULL),
	m_pModSrc(NULL)
{
	
};

ModRecord::~ModRecord()
{
	if ( m_pRecord)
	{
		delete [] m_pRecord; 
		m_pRecord = NULL; 
	}
	if ( m_pModSrc)
	{
		delete [] m_pModSrc	; 
		m_pModSrc = NULL; 
	}
}

//初始化资源，修改记录，同时起删除记录作用
BOOL ModRecord::Init(void *p, int iNum ,int iItemSize)
{
	if ( p == NULL || iNum == 0 || iItemSize == 0)
	{
		return FALSE; 
	}
	m_pSrc = (char *)p ; 
	m_iAvailableNum = iNum; 
	m_iItemSize = iItemSize ;  
	m_iModNum = 0; 
	m_iUsedNum = 0;
	if ( m_iAvailableNum > m_iMaxNum)
	{
		ReAllocSource(); 
		m_iMaxNum = m_iAvailableNum; 
	}
	return TRUE; 
}

//重新申请资源  原来资源不够大
BOOL ModRecord::ReAllocSource()
{
	//释放掉原来
	if ( m_pRecord )
	{
		delete [] m_pRecord; 
		m_pRecord = NULL; 
	}

	//申请新的
	try
	{
		m_pRecord = new BYTE[m_iAvailableNum]; 
		memset(m_pRecord, 0, sizeof(BYTE)*m_iAvailableNum); 
		m_pModSrc = new char[m_iAvailableNum * m_iItemSize];
	}
	catch (...)
	{
		m_pRecord = NULL;
		return FALSE; 
	}
	return TRUE; 
}

//按条件更新 pFunc返回为true时 更新 或pFunc 为NULL， 直接在末尾添加 (删除本地记录)
//返回下标  
int ModRecord::Update(const void *Item , ConditionCmp pFunc)
{
	if ( !m_pSrc || !m_pRecord || !Item )
	{
		return -1; 
	} 
	if ( !pFunc )
	{
		//直接在末尾添加
		if ( _add( Item, m_iUsedNum) != -1)
		{
			m_pRecord[m_iUsedNum] = 0;          //删除记录
			return m_iUsedNum++; 
		}
		return -1; 
	}
	//有判断条件 按条件判断
	for (int i=0; i<m_iUsedNum; i++)
	{
		//条件返回为真 替换掉原来的 删掉修改记录 
		if ( pFunc( m_pSrc+i*m_iItemSize, Item) )
		{
			memcpy( m_pSrc+i*m_iItemSize, Item, m_iItemSize); 
			m_pRecord[i] = 0;          //删除记录
			return i; 
		}	
	}
	return -1; 
}
//按条件更新一项 在iIndex下标的结构体，且 ConditionCmp返回为true时
BOOL ModRecord::Update(const void *pItem, int iIndex)
{ 
	if ( !m_pSrc || !m_pRecord || iIndex > m_iUsedNum)
	{
		return FALSE; 
	} 
	try
	{
		memcpy( m_pSrc+iIndex*m_iItemSize, pItem, m_iItemSize); 
		m_pRecord[iIndex] = 0;          //删除记录
		if ( iIndex == m_iUsedNum)
		{
			m_iUsedNum ++; 
		}
	}
	catch (...)
	{
		return FALSE; 
	}
	return TRUE; 
}

int ModRecord::_add(const void *pItem, int iIndex)
{
	if ( !m_pSrc || !m_pRecord || !pItem  || iIndex > m_iUsedNum )
	{
		return -1; 
	}
	try
	{
		void *pAdd = m_pSrc + (iIndex)*m_iItemSize; 
		memcpy( pAdd, pItem, m_iItemSize);
		m_pRecord[iIndex] = 1; 
		return iIndex; 
	}
	catch (...)
	{
		return -1; 
	}
}

//在原有结构体对比查找，条件为真  覆盖掉
int ModRecord::_Cmpadd(const void *pItem, ConditionCmp pFunc ) 
{
	if ( !m_pSrc || !m_pRecord || !pItem )
	{
		return  -1; 
	}
	if ( pFunc )
	{
		for (int i=0; i<m_iUsedNum; i++)
		{
			//条件返回为真  覆盖原来 
			if ( pFunc( m_pSrc+i*m_iItemSize, pItem) )
			{
				if ( _add(pItem, i) != -1)
				{
					return i; 
				}
				return -1;  
			}
		}
	}	
	return -1; 
}
//添加或修改某一项 
//返回值 -1为失败  其他为返回下标 
//没有对比条件，直接在末尾添加
//有的尝试对比，对比不成功，在末尾添加
int ModRecord::Add(const void *pItem , ConditionCmp pFunc )
{
	int iIndex = -1; 
	if ( (iIndex = _Cmpadd( pItem,  pFunc)) != -1)
	{
		return iIndex; 
	}
	
	//原来没有符合条件的 末尾添加新的
	if ( _add(pItem, m_iUsedNum) != -1)
	{
        
		return m_iUsedNum++; 
	}
	return -1; 
}
//按下标添加 用于同步 
BOOL ModRecord::Add(const void *pItem, int iIndex)
{
	if ( _add(pItem, iIndex) != -1 )
	{
		if ( iIndex == m_iUsedNum)
		{
			m_iUsedNum ++; 
		}
		return TRUE; 
	}
	return FALSE; 
}

//删除下标iIndex的项
int ModRecord::_del(int iIndex)
{
	if ( !m_pSrc || !m_pRecord ||  iIndex >= m_iUsedNum)
	{
		return -1; 
	}
	for (int j=iIndex; j<(m_iUsedNum-1); j++)           
	{
		memcpy(m_pSrc+j*m_iItemSize, m_pSrc+(j+1)*m_iItemSize, m_iItemSize); 
		m_pRecord[j] = m_pRecord[j+1];
	}
	return iIndex; 
}
//按条件删除某项
BOOL ModRecord::Del( const void *Item ,ConditionCmp pFunc)
{
	if ( !m_pSrc || !m_pRecord || !Item || !pFunc )
	{
		return FALSE; 
	}
	for (int i=0; i<m_iUsedNum; i++)
	{
		//条件返回为真 替换掉原来的 删掉修改记录 
		if ( pFunc( m_pSrc+i*m_iItemSize, Item) && _del(i) != -1)
		{
			m_iUsedNum --; 
			return TRUE; 
		}	
	}
	return FALSE; 
}
//按下标删除某项
BOOL ModRecord::Del(int iIndex)
{
	return (_del(iIndex) != -1)?TRUE:FALSE; 
}


//获取修改资源
int ModRecord::GetMod(void * *p)
{
	if ( !m_pSrc || !m_pRecord || !m_pModSrc )
	{
		return -1; 
	} 
	int j = 0; 
	for (int i=0; i<m_iUsedNum; i++)
	{
		if ( m_pRecord[i] == 1)
		{
			memcpy(m_pModSrc+j*m_iItemSize, m_pSrc+i*m_iItemSize, m_iItemSize);
			j++; 
		}
	}
	m_iModNum = j; 
	*p = m_pModSrc; 
	return m_iModNum; 
}

//清除修改记录
BOOL ModRecord::Clear()
{
	m_iUsedNum = 0; 
	m_iModNum = 0;
	memset(m_pRecord , 0 , sizeof(BYTE)*m_iAvailableNum); 
	return TRUE; 
}
//获取使用数目
int  ModRecord::GetUsedNum()
{
	return m_iUsedNum; 
}

//修改已有项
int  ModRecord::Modify(const void *pItem, ConditionCmp pFunc)
{	
	return _Cmpadd( pItem,  pFunc); 
}
//按下标， 修改已有项
int  ModRecord::Modify(const void *pItem, int iIndex)
{
	return Add( pItem, iIndex); 
}

 //获取原始资源地址
void* ModRecord::GetSrc()
{
	return m_pSrc; 
}

//获取每一项的大小
int  ModRecord::GetItemSize()
{
    return m_iItemSize; 
}                     

//初始化资源
BOOL TwoItemBM::Init(void * lpIndex, int iFSize,  void * lpSrc, int iSSize,  DWORD max)
{
    return (m_RecordInfo.Init( lpIndex, max, iFSize) && m_RecordCfg.Init( lpSrc, max, iSSize));
}   

//获取修改过资源, 返回个数
int TwoItemBM::GetModify(void **lpIndex, void **lpModifySrc)
{
    int iRetNumCfg = 0;
    int iRetNumInfo = 0; 
    iRetNumInfo	 = m_RecordInfo.GetMod(lpIndex);
    iRetNumCfg	 = m_RecordCfg.GetMod(lpModifySrc);
    return (iRetNumCfg == iRetNumInfo)?iRetNumInfo:-1; 
}   

//获取数量
int  TwoItemBM::GetNum()  
{
    return (m_RecordCfg.GetUsedNum() == m_RecordInfo.GetUsedNum()) ? m_RecordCfg.GetUsedNum() : -1; 
}   

//获取原始资源地址
BOOL TwoItemBM::GetSrc(void **lpIndex, void **lpModifySrc)
{
    *lpIndex = m_RecordInfo.GetSrc(); 
    *lpModifySrc =  m_RecordCfg.GetSrc();   
    return TRUE;   
}

//清楚修改记录                    
BOOL TwoItemBM::Clear()
{
    m_RecordInfo.Clear(); 
    m_RecordCfg.Clear(); 
    return TRUE; 
}


//重新
BOOL TwoItemBM::Update(DWORD dwNum, const void *ItemInfo, const void* ItemCfg, ConditionCmp pFunc)    
{
    m_RecordInfo.Clear(); 
    m_RecordCfg.Clear(); 
    int iIndex = -1; 
    const BYTE * byItemInfo = (BYTE *)ItemInfo; 
    const BYTE * byItemCfg = (BYTE *)ItemCfg;
    int iInfoSize = m_RecordInfo.GetItemSize(); 
    int iCfgSize = m_RecordCfg.GetItemSize(); 
    try
    {
        
        for (DWORD i=0 ; i<dwNum; i++)
        {
            Update(byItemInfo+i*iInfoSize, byItemCfg+i*iCfgSize, pFunc); 
        }
    }
    catch (...)
    {
        return FALSE; 
    }
    return TRUE; 
}


//刷新某一项 
BOOL TwoItemBM::Update(const void *IndexInfo, const void* ItemCfg, ConditionCmp pFunc)
{
    int iIndex; 
    if (( iIndex = m_RecordInfo.Update(IndexInfo , pFunc)) != -1)
    {
        return  m_RecordCfg.Update(ItemCfg, iIndex); 
    }
    return FALSE; 
}

//本地添加某一项
BOOL TwoItemBM::Add(const void *IndexInfo, const void* ItemCfg, ConditionCmp pFunc)
{
    int iIndex; 
    if (( iIndex = m_RecordInfo.Add(IndexInfo, pFunc)) != -1)
    {
        return m_RecordCfg.Add(ItemCfg, iIndex); 
    }
    return FALSE; 
}  

////修改已有项
BOOL TwoItemBM::Modify(const void *IndexInfo, const void* ItemCfg, ConditionCmp pFunc)
{
    int iIndex; 
    if (( iIndex = m_RecordInfo.Modify(IndexInfo, pFunc)) != -1)
    {
        return m_RecordCfg.Modify(ItemCfg, iIndex); 
    }
    return FALSE; 
}  

//删除某一项场景
BOOL TwoItemBM::Del(const void *ItemInfo,  ConditionCmp pFunc)
{
    int iIndex = -1; 
    if ((iIndex = m_RecordCfg.Del(ItemInfo, pFunc)) != -1)
    {
        m_RecordInfo.Del(iIndex);
    }
    return TRUE; 
}