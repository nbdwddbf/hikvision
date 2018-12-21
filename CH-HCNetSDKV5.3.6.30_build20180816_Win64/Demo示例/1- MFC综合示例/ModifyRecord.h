#ifndef MODIFYRECORD_H
#define MODIFYRECORD_H

//条件函数格式
typedef bool (*ConditionCmp)(const void *ItemF, const void *ItemS); 

//管理资源，记录修改
//Update 是刷新某一项 本地修改记录删除
//Add 添加本地修改项  或新增 或修改
//Modify 修改本地已有的项 
//Del  删除某一项  
//Clear 清楚本地修改记录  
class ModRecord
{
public:
	ModRecord();   
	~ModRecord();
//operate function 
	BOOL Init(void *p, int iNum, int iItemSize);            //初始化资源，修改记录，同时起删除记录作用
	int Update(const void *pItem , ConditionCmp pFunc = NULL);   //按条件更新一项 ConditionCmp返回为true时  更新
	int Update(const void *pItem, int iIndex);   //按条件更新一项 在iIndex下标的结构体 用于同步
	int  Add(const void *pItem, ConditionCmp pFunc = NULL);                     //添加或更新 某一项 添加修改记录
	BOOL Add(const void *pItem, int iIndex);         //添加或更新 按下标添加 用于同步 添加修改记录
	int  Modify(const void *pItem, ConditionCmp pFunc);                       //修改已有项
	int  Modify(const void *pItem, int iIndex);                       //按下标， 修改已有项 用于同步
	BOOL Del(const void *pItem , ConditionCmp pFunc);            //按条件删除某项
	BOOL Del(int iIndex);            //按下标删除某项
	BOOL Clear();                            //清除记录

//get infomation function
	int  GetMod(void * *p);                  //获取修改资源
	int  GetUsedNum();                      //获取使用数目
	void* GetSrc();                          //获取原始资源地址
    int  GetItemSize();                      //获取每一项的大小
protected:
	int _Cmpadd(const void *pItem, ConditionCmp pFunc = NULL);     
	int _add(const void *pItem, int iIndex);   //
	int _del(int iIndex); 
	BOOL ReAllocSource();                //重新申请资源  原来资源不够大
private:
	int m_iMaxNum;                        //历史最大资源数
	int m_iAvailableNum;                   //可用资源数
	int m_iItemSize;                     //单个资源大小
	int m_iUsedNum;                       //使用资源数
	int m_iModNum;					      //修改资源数

	char *m_pSrc;                         //资源
	char *m_pModSrc;                      //修改资源
	BYTE *m_pRecord;                      //记录
};


//两项结合使用，一项为索引匹配条件管理，一项为配置内容按照下标管理
class TwoItemBM
{
public:
    BOOL Init(void * lpIndex, int iFSize,  void * lpSrc, int iSSize,  DWORD max);             //初始化资源
    int  GetModify(void **lpIndex, void **lpModifySrc);        //获取修改过资源, 返回个数
    BOOL Clear();                           //清楚修改记录
    int  GetNum();                         //获取数量
    BOOL GetSrc(void **lpIndex, void **lpModifySrc);    //获取原来的内存

    BOOL Update(DWORD dwNum, const void *struIndex, const void* ItemCfg, ConditionCmp pFunc=NULL);    //批量刷新项
    BOOL Update(const void *IndexInfo, const void* ItemCfg, ConditionCmp pFunc);   //刷新某一项 
    BOOL Modify(const void *IndexInfo, const void* ItemCfg, ConditionCmp pFunc);  //修改已有项
    BOOL Add(const void *IndexInfo, const void* ItemCfg, ConditionCmp pFunc);  //本地修改某一项   
    BOOL Del(const void *IndexInfo,  ConditionCmp pFunc);       //删除某一项
protected:            
        

private:
    ModRecord m_RecordInfo; 
    ModRecord m_RecordCfg;
};


#endif