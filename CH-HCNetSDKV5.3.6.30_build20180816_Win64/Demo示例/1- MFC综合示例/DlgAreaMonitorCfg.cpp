// DlgAreaMonitorCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAreaMonitorCfg.h"
#include "DlgVcaSingleProcImg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAreaMonitorCfg dialog

/*********************************************************
函数名:	UTF82A
函数描述:	UTF8转多字节
输入参数:	cont - UTF8编码字符串                       
输出参数:	
返回值:	    多字节字符串
**********************************************************/
string UTF82A(const char* cont)
{
	if (NULL == cont)
    {
        return string("");
    }
    int num = MultiByteToWideChar(CP_UTF8, NULL, cont, -1, NULL, NULL);
    wchar_t* buffw = new wchar_t[(unsigned int)num];
    MultiByteToWideChar(CP_UTF8, NULL, cont, -1, buffw, num);
    int len = WideCharToMultiByte(CP_ACP, 0, buffw, num - 1, NULL, NULL, NULL, NULL); 
    char* lpsz = new char[(unsigned int)len + 1]; 
    WideCharToMultiByte(CP_ACP, 0, buffw, num - 1, lpsz, len, NULL, NULL);
    lpsz[len]='\0';
    delete[] buffw;
    string rtn(lpsz);
    delete[] lpsz;
    return rtn ;

}

/*********************************************************
函数名:	A2UTF8
函数描述:	多字节转UTF8
输入参数:	cont - 多字节字符串                       
输出参数:	
返回值:	    UTF8编码的字符串
**********************************************************/
string A2UTF8(const char* cont)
{
    if (NULL == cont)
    {
        return string("");
    }
    
#ifdef OS_WINDOWS
    int num = MultiByteToWideChar(CP_ACP, NULL, cont, -1, NULL, NULL);
    wchar_t* buffw = new wchar_t[(unsigned int)num];
    MultiByteToWideChar(CP_ACP, NULL, cont, -1, buffw, num);
    
    int len = WideCharToMultiByte(CP_UTF8, 0, buffw, num - 1, NULL, NULL, NULL, NULL); 
    char* lpsz = new char[(unsigned int)len + 1]; 
    WideCharToMultiByte(CP_UTF8, 0, buffw, num - 1, lpsz, len, NULL, NULL);
    lpsz[len]='\0';
    delete[] buffw;
    
    string rtn(lpsz);
    delete[] lpsz;
    return rtn;
#elif (defined(OS_POSIX) || defined(OS_MAC) || defined(OS_IPHONE)) && !defined OS_ANDROID
    char* outbuf = 0;
    string str;
    if (cont)
    {
        iconv_t cd = iconv_open("UTF-8", "EUC-CN");
        if (cd)
        {
            size_t contlen = strlen(cont);
            size_t outbuflen = contlen * 3 + 1;
            outbuf = new char[outbuflen];
            memset(outbuf, 0, outbuflen);
            
            char* inptr = const_cast<char*>(cont);
            char* outptr = outbuf;
            
            size_t inlen = contlen;
            size_t outlen = outbuflen;
            if (iconv(cd, &inptr, &inlen, &outptr, &outlen) == (size_t)(-1))
            {
                outbuf = 0;
            }
            
            iconv_close(cd);
            str = outbuf;
            delete[] outbuf;
        }
    }
    return str;
#else
    return string("");
#endif
}

CDlgAreaMonitorCfg::CDlgAreaMonitorCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAreaMonitorCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAreaMonitorCfg)
	m_csInputCond = _T("");
	m_csConfigParam = _T("");
	m_csLastError = _T("");
	m_csReturnValue = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAreaMonitorCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAreaMonitorCfg)
	DDX_Control(pDX, IDC_CMB_CFG_TYPE, m_cmbType);
	DDX_Text(pDX, IDC_EDIT_INPUT_PARAM, m_csInputCond);
	DDX_Text(pDX, IDC_EDT_CFG_PARAM, m_csConfigParam);
	DDX_Text(pDX, IDC_EDT_LAST_ERROR, m_csLastError);
	DDX_Text(pDX, IDC_EDT_RETURN_VALUE, m_csReturnValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAreaMonitorCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAreaMonitorCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnProcess)
	ON_CBN_SELCHANGE(IDC_CMB_CFG_TYPE, OnSelchangeCmbCfgType)
	ON_BN_CLICKED(IDC_BTN_DETECT, OnBtnDetect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAreaMonitorCfg message handlers

void CDlgAreaMonitorCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_STD_CONFIG struCfg = {0};
    DWORD dwTemp =1;
    struCfg.lpCondBuffer = &dwTemp;
    struCfg.dwCondSize = sizeof(1);
    char szLan[512] = {0};
    sprintf(szLan,"Just For Test");

//     struCfg.lpInBuffer = szLan;
//     struCfg.dwInSize = strlen(szLan);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
//     if(!NET_DVR_SetSTDConfig(m_lUserID, 5237, &struCfg))
//     {
//         OutputDebugString(m_szStatusBuf);
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AREA_MONITOR_CFG");
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AREA_MONITOR_CFG");
//     }

    NET_DVR_BLACKLIST_ALARM_RECORD struAlarmRecord = {0};
    struAlarmRecord.dwSize = sizeof(struAlarmRecord);
    struAlarmRecord.dwSnapFacePicID = 1;
    struAlarmRecord.dwRegisterID =1;
    struAlarmRecord.dwGroupNo =1;

     
    NET_DVR_STD_CONTROL struSTDCtrl = {0};
    struSTDCtrl.dwXmlSize = strlen(szLan);
    struSTDCtrl.lpXmlBuffer = szLan;
    struSTDCtrl.byDataType = 1;

//     if (NET_DVR_STDControl(m_lUserID,NET_DVR_DEL_BLACKLIST_ALARM_RECORD,&struSTDCtrl))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DEL_BLACKLIST_ALARM_RECORD");
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DEL_BLACKLIST_ALARM_RECORD");
//     }


    
        NET_DVR_BLACKLIST_GROUP_COND struGetCond = {0};
       struGetCond.dwSize = sizeof(NET_DVR_BLACKLIST_GROUP_COND);
       struGetCond.dwGroupID = 12;
       struCfg.lpInBuffer = &struGetCond;
       struCfg.dwInSize = sizeof(NET_DVR_BLACKLIST_GROUP_COND);

       
       if (!NET_DVR_GetSTDConfig(m_lUserID,NET_DVR_GET_BLACKLIST_GROUP_INFO,&struCfg))
       {
           
           g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BLACKLIST_GROUP_INFO");
       }
       else
       {
           g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BLACKLIST_GROUP_INFO");
       }

}

void CDlgAreaMonitorCfg::OnBtnProcess() 
{
	// TODO: Add your control notification handler code here
    //GetDlgItem(IDC_EDT_CFG_PARAM)->SetWindowText("");
    UpdateData(TRUE);
	CString strTemp = m_csInputCond.GetBuffer(0);

	strTemp = m_csConfigParam.GetBuffer(0);
    if (m_dwCfgType == 0)
    {
        AfxMessageBox("请选择类型!");
        return ;
    }

	NET_DVR_STD_CONFIG struSTDCfg = {0};
	NET_DVR_STD_CONTROL struSTDCtrl = {0};


	char *pCondBuf = new char[1024];
	if(pCondBuf == NULL)
	{
		return;
	}
	memset(pCondBuf,0,1024);

	char *pOutBuf = new char[10*1024*1024];
	if(pOutBuf == NULL)
	{
		return;
	}
	memset(pOutBuf,0,10*1024*1024);
	char* pSetXmlBuf = NULL;
	DWORD dwSetDataLen = 0;

	switch(m_dwCfgType)
	{
	case NET_DVR_GET_AREA_MONITOR_CFG:
		{
			NET_DVR_AREA_MONITOR_COND *pCondTemp = (NET_DVR_AREA_MONITOR_COND *)pCondBuf;
			ParseAreaMonitorCond(pCondTemp);
			struSTDCfg.lpCondBuffer = pCondBuf;
			struSTDCfg.dwCondSize = sizeof(NET_DVR_AREA_MONITOR_COND);
			struSTDCfg.byDataType = 1;
			m_dwInterfaceType = INTERFACE_STD_GET;
		}
		break;
	case NET_DVR_SET_AREA_MONITOR_CFG:
		{
			m_dwInterfaceType = INTERFACE_STD_SET; 
			DWORD *pCondTemp = (DWORD *)pCondBuf;
			ParseSetAreaMonitorCond(pCondTemp);
			struSTDCfg.lpCondBuffer = pCondTemp;
			struSTDCfg.dwCondSize = sizeof(DWORD);
			struSTDCfg.byDataType = 1;
			dwSetDataLen = m_csConfigParam.GetLength();

			pSetXmlBuf = new char[dwSetDataLen];
			if (pSetXmlBuf == NULL)
			{
				if (pOutBuf != NULL)
				{
					delete[] pOutBuf;
					pOutBuf = NULL;
				}
				
				return;
			}
			memset(pSetXmlBuf,0,dwSetDataLen);
			memcpy(pSetXmlBuf,m_csConfigParam.GetBuffer(0),dwSetDataLen);
		}	
		break;
	case NET_DVR_DEL_AREA_MONITOR_CFG:
        {
            //std::string strConfigXML = "\n<AreaMonitorDelCond xmlns=\"http://www.isapi.org/ver20/XMLSchema\" version=\"2.0\"><deleteType>delSingle</deleteType><areaID>1</areaID><monitorID>31</monitorID></AreaMonitorDelCond>\n";
            std::string strConfigXML = "<AreaMonitorDelCond xmlns=\"http://www.isapi.org/ver20/XMLSchema\" version=\"2.0\"><deleteType>delSingle</deleteType><areaID>1</areaID><monitorID>31</monitorID></AreaMonitorDelCond>";

           //     std::string strConfigXML = "<AreaMonitorDelCond version=\"2.0\" xmlns=\"http://www.isapi.org/ver20/XMLSchema\">\<deleteType>delAll</deleteType><areaID>1</areaID></AreaMonitorDelCond>";
            
            char* pStatusBuffer = new char[1024];
            memset(pStatusBuffer, 0, 1024);

            struSTDCtrl.lpStatusBuffer = pStatusBuffer;
            struSTDCtrl.dwStatusSize = 1024;
            
            m_dwInterfaceType = INTERFACE_STD_CTRL;
            struSTDCtrl.byDataType = 1;
            struSTDCtrl.dwXmlSize = strConfigXML.length();
            pSetXmlBuf = new char[struSTDCtrl.dwXmlSize];
 
            if (pSetXmlBuf == NULL)
            {
                if (pOutBuf != NULL)
                {
                    delete[] pOutBuf;
                    pOutBuf = NULL;
                }
                return;
            }
            
            memset(pSetXmlBuf,0,struSTDCtrl.dwXmlSize);
            memcpy(pSetXmlBuf, strConfigXML.c_str(),struSTDCtrl.dwXmlSize);
            

            int iSdkCmd = NET_DVR_DEL_AREA_MONITOR_CFG;//删除区域监控点
   //         std::string strConfigXML = "<AreaMonitorDelCond xmlns=\"http://www.isapi.org/ver20/XMLSchema\" version=\"2.0\"><deleteType>delSingle</deleteType><areaID>1</areaID><monitorID>31</monitorID></AreaMonitorDelCond>";
            //std::string strConfigXML = "\n<AreaMonitorDelCond xmlns=\"http://www.isapi.org/ver20/XMLSchema\" version=\"2.0\"><deleteType>delSingle</deleteType><areaID>1</areaID><monitorID>31</monitorID></AreaMonitorDelCond>\n";
            
 

            char* pXmlBuffer = new char[1024];
            memset(pXmlBuffer, 0, 1024);
            int dwXmlSize = strConfigXML.length();
            memcpy(pXmlBuffer, strConfigXML.c_str(), dwXmlSize);
            
            
           
            NET_DVR_STD_CONTROL struSTDCtrl;
            memset(&struSTDCtrl, 0, sizeof(NET_DVR_STD_CONTROL));
            struSTDCtrl.lpXmlBuffer = pXmlBuffer;
            struSTDCtrl.dwXmlSize = dwXmlSize;
            struSTDCtrl.byDataType = 1;
            struSTDCtrl.lpStatusBuffer = pStatusBuffer;
            struSTDCtrl.dwStatusSize = 1024;
            
            BOOL iSdkRet = NET_DVR_STDControl(m_lUserID, m_dwCfgType, &struSTDCtrl);
            if (iSdkRet)
            {
                g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_DEL_AREA_MONITOR_CFG");
                return;
            }
            else
            {
                g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_DEL_AREA_MONITOR_CFG");
                return;
            }

            struSTDCtrl.lpXmlBuffer = pSetXmlBuf;
            if (!NET_DVR_STDControl(m_lUserID,m_dwCfgType,&struSTDCtrl))
            {
                g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_STDControl Cmd[%d]",m_dwCfgType);
                if (pOutBuf != NULL)
                {
                    delete[] pOutBuf;
                    pOutBuf = NULL;
                }
                
                if (pSetXmlBuf != NULL)
                {
                    delete[] pSetXmlBuf;
                    pSetXmlBuf = NULL;
                }
                return;
            }
            else
            {
                g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_STDControl Cmd[%d]",m_dwCfgType);
		}

      }
        break;
	case NET_DVR_GET_BLACKLIST_ALARM_INFO:
		{
			struSTDCfg.dwCondSize =m_csInputCond.GetLength();
			memcpy(pCondBuf,m_csInputCond.GetBuffer(0),struSTDCfg.dwCondSize);
			struSTDCfg.lpCondBuffer = pCondBuf;
			struSTDCfg.byDataType = 1;
			m_dwInterfaceType = INTERFACE_STD_GET;
		} 
		break;
	case NET_DVR_GET_STORAGE_RESOURCE_CFG:
		{
			NET_DVR_STORAGE_RESOURCE_COND *pCondTemp = (NET_DVR_STORAGE_RESOURCE_COND *)pCondBuf;
			ParseGetStorageResourceCond(pCondTemp);
			struSTDCfg.lpCondBuffer = pCondBuf;
			struSTDCfg.dwCondSize = sizeof(NET_DVR_STORAGE_RESOURCE_COND);
			struSTDCfg.byDataType = 1;
			m_dwInterfaceType = INTERFACE_STD_GET;
		}
		break;
 	case NET_DVR_SET_STORAGE_RESOURCE_CFG:
		{
			m_dwInterfaceType = INTERFACE_STD_SET; 
			DWORD *pCondTemp = (DWORD *)pCondBuf;
			struSTDCfg.byDataType = 1;
			dwSetDataLen = m_csConfigParam.GetLength();
			pSetXmlBuf = new char[dwSetDataLen];
			if (pSetXmlBuf == NULL)
			{
				if (pOutBuf != NULL)
				{
					delete[] pOutBuf;
					pOutBuf = NULL;
				}
				return;
			}
			memset(pSetXmlBuf,0,dwSetDataLen);
			memcpy(pSetXmlBuf,m_csConfigParam.GetBuffer(0),dwSetDataLen);
		}	
		break;
	case NET_DVR_GET_ALARMLIST:
		{
			struSTDCfg.dwInSize =m_csInputCond.GetLength();
			
			pSetXmlBuf = new char[struSTDCfg.dwInSize];
			if (pSetXmlBuf == NULL)
			{
				if (pOutBuf != NULL)
				{
					delete[] pOutBuf;
					pOutBuf = NULL;
				}
				
				return;
			}
			memset(pSetXmlBuf,0,struSTDCfg.dwInSize);

			memcpy(pSetXmlBuf,m_csInputCond.GetBuffer(0),struSTDCfg.dwInSize);
			struSTDCfg.lpInBuffer = pSetXmlBuf;
			struSTDCfg.byDataType = 1;
			m_dwInterfaceType = INTERFACE_STD_GET;
		} 
		break;
	case NET_DVR_DEL_BLACKLIST_ALARM_RECORD:
		m_dwInterfaceType = INTERFACE_STD_CTRL;
		struSTDCtrl.byDataType = 1;
		struSTDCtrl.dwXmlSize =m_csConfigParam.GetLength();
		pSetXmlBuf = new char[struSTDCtrl.dwXmlSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			return;
		}
		
		memset(pSetXmlBuf,0,struSTDCtrl.dwXmlSize);
		memcpy(pSetXmlBuf, m_csConfigParam.GetBuffer(0),struSTDCtrl.dwXmlSize);
		break;
	case NET_DVR_GET_BLACKLIST_GROUP_INFO:
		{
			NET_DVR_BLACKLIST_GROUP_COND *pCondTemp = (NET_DVR_BLACKLIST_GROUP_COND *)pCondBuf;
			ParseGetBlackListGroupInfoCond(pCondTemp);
			struSTDCfg.lpCondBuffer = pCondBuf;
			struSTDCfg.dwCondSize = sizeof(NET_DVR_BLACKLIST_GROUP_COND);
			struSTDCfg.byDataType = 1;
			m_dwInterfaceType = INTERFACE_STD_GET;
		}
		break;
	case NET_DVR_SET_BLACKLIST_GROUP_INFO:
		{	
			m_dwInterfaceType = INTERFACE_STD_SET; 
			DWORD *pCondTemp = (DWORD *)pCondBuf;
			struSTDCfg.byDataType = 1;
			dwSetDataLen = m_csConfigParam.GetLength();
			pSetXmlBuf = new char[dwSetDataLen];
			if (pSetXmlBuf == NULL)
			{
				if (pOutBuf != NULL)
				{
					delete[] pOutBuf;
					pOutBuf = NULL;
				}
				return;
			}
			memset(pSetXmlBuf,0,dwSetDataLen);
			memcpy(pSetXmlBuf,m_csConfigParam.GetBuffer(0),dwSetDataLen);

            char szStatusBuf[1024] = {0};

			struSTDCfg.dwInSize = 1024;
			struSTDCfg.lpInBuffer = szStatusBuf;
             
		}	
		break;
	case NET_DVR_DEL_BLACKLIST_GROUP_INFO:
		m_dwInterfaceType = INTERFACE_STD_CTRL;
		struSTDCtrl.byDataType = 1;
		struSTDCtrl.dwXmlSize =m_csConfigParam.GetLength();
		pSetXmlBuf = new char[struSTDCtrl.dwXmlSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			return;
		}
		
		memset(pSetXmlBuf,0,struSTDCtrl.dwXmlSize);
		memcpy(pSetXmlBuf, m_csConfigParam.GetBuffer(0),struSTDCtrl.dwXmlSize);
		break;
	case NET_DVR_GET_BLACKLIST_GROUP_RECORD_CFG:
		{
			struSTDCfg.dwInSize =m_csInputCond.GetLength();
			
			pSetXmlBuf = new char[struSTDCfg.dwInSize];
			if (pSetXmlBuf == NULL)
			{
				if (pOutBuf != NULL)
				{
					delete[] pOutBuf;
					pOutBuf = NULL;
				}
				
				return;
			}
			memset(pSetXmlBuf,0,struSTDCfg.dwInSize);
			
			memcpy(pSetXmlBuf,m_csInputCond.GetBuffer(0),struSTDCfg.dwInSize);
			struSTDCfg.lpInBuffer = pSetXmlBuf;
			struSTDCfg.byDataType = 1;
			m_dwInterfaceType = INTERFACE_STD_GET;
		} 
		break;
	case NET_DVR_SET_BLACKLIST_GROUP_RECORD_CFG:
		{
			m_dwInterfaceType = INTERFACE_STD_SET; 
			DWORD *pCondTemp = (DWORD *)pCondBuf;
			struSTDCfg.byDataType = 1;
			dwSetDataLen = m_csConfigParam.GetLength();
			pSetXmlBuf = new char[dwSetDataLen];
			if (pSetXmlBuf == NULL)
			{
				if (pOutBuf != NULL)
				{
					delete[] pOutBuf;
					pOutBuf = NULL;
				}
				return;
			}
			memset(pSetXmlBuf,0,dwSetDataLen);
			memcpy(pSetXmlBuf,m_csConfigParam.GetBuffer(0),dwSetDataLen);
		//	struSTDCfg.dwInSize = dwSetDataLen;
		//	struSTDCfg.lpInBuffer = pSetXmlBuf;
		}	
		break;
	case NET_DVR_DEL_BLACKLIST_GROUP_RECORD_CFG:
		m_dwInterfaceType = INTERFACE_STD_CTRL;
		struSTDCtrl.byDataType = 1;
		struSTDCtrl.dwXmlSize =m_csConfigParam.GetLength();
		pSetXmlBuf = new char[struSTDCtrl.dwXmlSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			return;
		}
		
		memset(pSetXmlBuf,0,struSTDCtrl.dwXmlSize);
		memcpy(pSetXmlBuf, m_csConfigParam.GetBuffer(0),struSTDCtrl.dwXmlSize);
		break;
	case NET_DVR_RETRIEVAL_SNAP_RECORD:
		{
			if (!LoadRetrievalSnapRecordPicData(&struSTDCfg.dwInSize, pSetXmlBuf))
			{
				return;
			}
			struSTDCfg.lpInBuffer = pSetXmlBuf;
			struSTDCfg.byDataType = 1;
			m_dwInterfaceType = INTERFACE_STD_GET;
		}
		break;
	case NET_DVR_DETECT_IMAGE:
		{
			if (!LoadDetectImagePicData(&struSTDCfg.dwInSize, pSetXmlBuf))
			{
				return;
			}
			struSTDCfg.lpInBuffer = pSetXmlBuf;
			struSTDCfg.byDataType = 1;
			m_dwInterfaceType = INTERFACE_STD_GET;
		}
		break;
		break;
	case NET_DVR_GET_SNAP_RECORD:
		struSTDCfg.dwInSize =m_csInputCond.GetLength();
		pSetXmlBuf = new char[struSTDCfg.dwInSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			
			return;
		}
		memset(pSetXmlBuf,0,struSTDCfg.dwInSize);
		
		memcpy(pSetXmlBuf,m_csInputCond.GetBuffer(0),struSTDCfg.dwInSize);
		struSTDCfg.lpInBuffer = pSetXmlBuf;
		struSTDCfg.byDataType = 1;
		m_dwInterfaceType = INTERFACE_STD_GET;
		break;
	case NET_DVR_DEL_SNAP_RECORD:
		m_dwInterfaceType = INTERFACE_STD_CTRL;
		struSTDCtrl.byDataType = 1;
		struSTDCtrl.dwXmlSize =m_csConfigParam.GetLength();
		pSetXmlBuf = new char[struSTDCtrl.dwXmlSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			return;
		}
		
		memset(pSetXmlBuf,0,struSTDCtrl.dwXmlSize);
		memcpy(pSetXmlBuf, m_csConfigParam.GetBuffer(0),struSTDCtrl.dwXmlSize);
		break;

	case NET_DVR_GET_FACE_RECORD:
		struSTDCfg.dwInSize =m_csInputCond.GetLength();
		pSetXmlBuf = new char[struSTDCfg.dwInSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			
			return;
		}
		memset(pSetXmlBuf,0,struSTDCfg.dwInSize);
		
		memcpy(pSetXmlBuf,m_csInputCond.GetBuffer(0),struSTDCfg.dwInSize);
		struSTDCfg.lpInBuffer = pSetXmlBuf;
		struSTDCfg.byDataType = 1;
		m_dwInterfaceType = INTERFACE_STD_GET;
		break;
	case NET_DVR_SET_FACE_RECORD://设置人脸记录
		{
			m_dwInterfaceType = INTERFACE_STD_SET; 
			DWORD *pCondTemp = (DWORD *)pCondBuf;
			struSTDCfg.byDataType = 1;
			dwSetDataLen = m_csConfigParam.GetLength();
			pSetXmlBuf = new char[dwSetDataLen];
			if (pSetXmlBuf == NULL)
			{
				if (pOutBuf != NULL)
				{
					delete[] pOutBuf;
					pOutBuf = NULL;
				}
				return;
			}
			memset(pSetXmlBuf,0,dwSetDataLen);
			memcpy(pSetXmlBuf,m_csConfigParam.GetBuffer(0),dwSetDataLen);
			//struSTDCfg.dwInSize = dwSetDataLen;
			//struSTDCfg.lpInBuffer = pSetXmlBuf;
		}	
		break;
	case NET_DVR_DEL_FACE_RECORD: //删除人脸记录
		m_dwInterfaceType = INTERFACE_STD_CTRL;
		struSTDCtrl.byDataType = 1;
		struSTDCtrl.dwXmlSize =m_csConfigParam.GetLength();
		pSetXmlBuf = new char[struSTDCtrl.dwXmlSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			return;
		}
		
		memset(pSetXmlBuf,0,struSTDCtrl.dwXmlSize);
		memcpy(pSetXmlBuf, m_csConfigParam.GetBuffer(0),struSTDCtrl.dwXmlSize);
		break;
	case NET_DVR_GET_FACE_DATABASE:
		struSTDCfg.dwInSize =m_csInputCond.GetLength();
		pSetXmlBuf = new char[struSTDCfg.dwInSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			
			return;
		}
		memset(pSetXmlBuf,0,struSTDCfg.dwInSize);
		
		memcpy(pSetXmlBuf,m_csInputCond.GetBuffer(0),struSTDCfg.dwInSize);
		struSTDCfg.lpInBuffer = pSetXmlBuf;
		struSTDCfg.byDataType = 1;
		m_dwInterfaceType = INTERFACE_STD_GET;
		break;
	case NET_DVR_SET_FACE_DATABASE://设置人脸库配置参数
		{
			m_dwInterfaceType = INTERFACE_STD_SET; 
			DWORD *pCondTemp = (DWORD *)pCondBuf;
			struSTDCfg.byDataType = 1;
			dwSetDataLen = m_csConfigParam.GetLength();
			pSetXmlBuf = new char[dwSetDataLen];
			if (pSetXmlBuf == NULL)
			{
				if (pOutBuf != NULL)
				{
					delete[] pOutBuf;
					pOutBuf = NULL;
				}
				return;
			}
			memset(pSetXmlBuf,0,dwSetDataLen);
			memcpy(pSetXmlBuf,m_csConfigParam.GetBuffer(0),dwSetDataLen);
			//struSTDCfg.dwInSize = dwSetDataLen;
			//struSTDCfg.lpInBuffer = pSetXmlBuf;
		}	
		break;
	case NET_DVR_DEL_FACE_DATABASE://删除人脸库
		m_dwInterfaceType = INTERFACE_STD_CTRL;
		struSTDCtrl.byDataType = 1;
		struSTDCtrl.dwXmlSize =m_csConfigParam.GetLength();
		pSetXmlBuf = new char[struSTDCtrl.dwXmlSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			return;
		}
		
		memset(pSetXmlBuf,0,struSTDCtrl.dwXmlSize);
		memcpy(pSetXmlBuf, m_csConfigParam.GetBuffer(0),struSTDCtrl.dwXmlSize);
		break;
	case NET_DVR_RETRIEVAL_FACE_DATABASE:
		struSTDCfg.dwInSize =m_csInputCond.GetLength();
		pSetXmlBuf = new char[struSTDCfg.dwInSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			
			return;
		}
		memset(pSetXmlBuf,0,struSTDCfg.dwInSize);
		
		memcpy(pSetXmlBuf,m_csInputCond.GetBuffer(0),struSTDCfg.dwInSize);
		struSTDCfg.lpInBuffer = pSetXmlBuf;
		struSTDCfg.byDataType = 1;
		m_dwInterfaceType = INTERFACE_STD_GET;
		break;
	case NET_DVR_SET_BLACKLIST_REL_DEV_CFG:
		{
			m_dwInterfaceType = INTERFACE_STD_SET; 
			DWORD *pCondTemp = (DWORD *)pCondBuf;
			struSTDCfg.byDataType = 1;
			dwSetDataLen = m_csConfigParam.GetLength();
			pSetXmlBuf = new char[dwSetDataLen];
			if (pSetXmlBuf == NULL)
			{
				if (pOutBuf != NULL)
				{
					delete[] pOutBuf;
					pOutBuf = NULL;
				}
				return;
			}
			memset(pSetXmlBuf,0,dwSetDataLen);
			memcpy(pSetXmlBuf,m_csConfigParam.GetBuffer(0),dwSetDataLen);
			//struSTDCfg.dwInSize = dwSetDataLen;
			//struSTDCfg.lpInBuffer = pSetXmlBuf;
		}	
		break;
	case NET_DVR_DEL_BLACKLIST_REL_DEV:
		m_dwInterfaceType = INTERFACE_STD_CTRL;
		struSTDCtrl.byDataType = 1;
		struSTDCtrl.dwXmlSize =m_csConfigParam.GetLength();
		pSetXmlBuf = new char[struSTDCtrl.dwXmlSize];
		if (pSetXmlBuf == NULL)
		{
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			return;
		}
		
		memset(pSetXmlBuf,0,struSTDCtrl.dwXmlSize);
		memcpy(pSetXmlBuf, m_csConfigParam.GetBuffer(0),struSTDCtrl.dwXmlSize);
		break;
		break;
	default:
		if (pOutBuf != NULL)
		{
			delete[] pOutBuf;
			pOutBuf = NULL;
		}
		
		if (pSetXmlBuf != NULL)
		{
			delete[] pSetXmlBuf;
			pSetXmlBuf = NULL;
		}
		return;
	}
	

	struSTDCfg.lpStatusBuffer = m_szStatusBuf;
	struSTDCfg.dwStatusSize = ISAPI_STATUS_LEN;
	if (m_dwInterfaceType == INTERFACE_STD_GET)
	{
		
		struSTDCfg.dwXmlSize = 10*1024*1024;
		struSTDCfg.lpXmlBuffer = pOutBuf;

		if (!NET_DVR_GetSTDConfig(m_lUserID,m_dwCfgType,&struSTDCfg))
		{
			g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GetSTDConfig Cmd[%d]",m_dwCfgType);
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			
			if (pSetXmlBuf != NULL)
			{
				delete[] pSetXmlBuf;
				pSetXmlBuf = NULL;
			}
			return;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_GetSTDConfig Cmd[%d]",m_dwCfgType);

			CXmlBase xmlBase;
			xmlBase.Parse(pOutBuf);
			xmlBase.SetRoot();
			m_csConfigParam = xmlBase.GetChildren().c_str();
			//	m_strDevAbility = m_pOutBuf;
			m_csConfigParam.Replace("\n", "\r\n");
		}
	}
	else if (m_dwInterfaceType == INTERFACE_STD_SET)
	{
		struSTDCfg.dwXmlSize = dwSetDataLen;
		struSTDCfg.lpXmlBuffer = pSetXmlBuf;
		if (!NET_DVR_SetSTDConfig(m_lUserID,m_dwCfgType,&struSTDCfg))
		{
			g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SetSTDConfig Cmd[%d]",m_dwCfgType);
			if (pOutBuf != NULL) 
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}

			if (pSetXmlBuf != NULL)
			{
				delete[] pSetXmlBuf;
				pSetXmlBuf = NULL;
			}
			return;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SetSTDConfig Cmd[%d]",m_dwCfgType);
		}
	}
	else if (m_dwInterfaceType == INTERFACE_STD_CTRL)
	{
		struSTDCtrl.lpXmlBuffer = pSetXmlBuf;
		if (!NET_DVR_STDControl(m_lUserID,m_dwCfgType,&struSTDCtrl))
		{
			g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_STDControl Cmd[%d]",m_dwCfgType);
			if (pOutBuf != NULL)
			{
				delete[] pOutBuf;
				pOutBuf = NULL;
			}
			
			if (pSetXmlBuf != NULL)
			{
				delete[] pSetXmlBuf;
				pSetXmlBuf = NULL;
			}
			return;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_STDControl Cmd[%d]",m_dwCfgType);
		}
	}
	
	if (pOutBuf != NULL)
	{
		delete[] pOutBuf;
		pOutBuf = NULL;
	}
	
	if (pSetXmlBuf != NULL)
	{
		delete[] pSetXmlBuf;
		pSetXmlBuf = NULL;
	}
	UpdateData(FALSE);
}

void CDlgAreaMonitorCfg::OnSelchangeCmbCfgType() 
{
	// TODO: Add your control notification handler code here
	CXmlBase xmlInputCond;
	CXmlBase xmlCfgParam;
	switch (m_cmbType.GetCurSel())
	{
	case 0:  //获取区域监控点参数
		m_dwCfgType = NET_DVR_GET_AREA_MONITOR_CFG;	
		xmlInputCond.Parse("<AreaMonitorCond><dwAreaID>1</dwAreaID><dwMonitorID>0</dwMonitorID><byIsNeedGroup>0</byIsNeedGroup></AreaMonitorCond>");
		break;
	case 1:
		m_dwCfgType = NET_DVR_SET_AREA_MONITOR_CFG;
		xmlInputCond.Parse("<AreaMonitorCond><dwAreaID>1</dwAreaID></AreaMonitorCond>");
		
		xmlCfgParam.Parse("<Monitor>\
									  <DeviceIPAddress>\
									  <Address>\
									  <ipVersion>0</ipVersion>\
									  <ipAddress>10.6.34.102</ipAddress>\
									  <port>8000</port>\
									  </Address>\
									  </DeviceIPAddress>\
									  <userName>admin</userName>\
									  <userPassword>12345</userPassword>\
									  </Monitor>");
		break;
	case 2: //区域监控点参数设置
		m_dwCfgType = NET_DVR_SET_AREA_MONITOR_CFG;
		xmlInputCond.Parse("<AreaMonitorCond><dwAreaID>1</dwAreaID></AreaMonitorCond>");
		
		xmlCfgParam.Parse("<Monitor>\
									  <id>1</id>\
									  <deviceID>1</deviceID>\
									  <DeviceIPAddress>\
									  <Address>\
									  <ipVersion>0</ipVersion>\
									  <ipAddress>10.6.34.102</ipAddress>\
									  <port>8000</port>\
									  </Address>\
									  </DeviceIPAddress>\
									  <StoreServerIPAddress>\
									  <Address>\
									  <ipVersion>0</ipVersion>\
									  <ipAddress>10.6.34.101</ipAddress>\
									  <port>7000</port>\
									  </Address>\
									  </StoreServerIPAddress>\
									  <userName>admin</userName>\
									  <userPassword>12345</userPassword>\
									  <deviceType>1</deviceType>\
									  <RelatedGroupList>\
									  <RelatedGroup>\
									  <groupID>1</groupID>\
									  <isRelated>1</isRelated>\
									  <groupType>0</groupType>\
									  </RelatedGroup>\
									  </RelatedGroupList>\
									  </Monitor>");
		break;
	case 3: //删除区域的所有监控点
		m_dwCfgType = NET_DVR_DEL_AREA_MONITOR_CFG;	
		xmlCfgParam.Parse("<AreaMonitorDelCond version=\"2.0\" xmlns=\"http://www.isapi.org/ver20/XMLSchema\">\
																												<deleteType>delAll</deleteType>\
																												<areaID>1</areaID>\
																												</AreaMonitorDelCond>");
		break;
	case 4://删除区域的单个监控点
		m_dwCfgType = NET_DVR_DEL_AREA_MONITOR_CFG;	
		xmlCfgParam.Parse("<AreaMonitorDelCond version=\"2.0\" xmlns=\"http://www.isapi.org/ver20/XMLSchema\">\
																												<deleteType>delSingle</deleteType>\
																												<areaID>1</areaID>\
																												<monitorID>1</monitorID>\
																												</AreaMonitorDelCond>");
		break;
	case 5:  //获取黑名单轨迹
		m_dwCfgType = NET_DVR_GET_BLACKLIST_ALARM_INFO;	
		xmlInputCond.Parse("<ListAlarmParam>\
											  <listType>all</listType>\
											  <listID>1</listID>\
											  <Address>\
											  <ipVersion>0</ipVersion>\
											  <ipAddress>10.10.1.1</ipAddress>\
											  <port>8000</port>\
											  </Address>\
											  <maxSnapNum>1</maxSnapNum>\
											  </ListAlarmParam>");
		break;
	case 6:  //获取存储资源
		m_dwCfgType = NET_DVR_GET_STORAGE_RESOURCE_CFG;	
		xmlInputCond.Parse("<StorageResourceCond>\
												   <currentID>1</currentID>\
												   </StorageResourceCond>");
		break;
	case 7:  //修改存储资源
		m_dwCfgType = NET_DVR_SET_STORAGE_RESOURCE_CFG;	
		xmlCfgParam.Parse("<StorageResource>\
											  <StorageVolume>\
											  <StorageInfo>\
											  <Address>\
											  <ipVersion>0</ipVersion>\
											  <ipAddress>10.10.1.1</ipAddress>\
											  <port>8000</port>\
											  </Address>\
											  <storageDays>10</storageDays>\
											  <storageNum>20/storageNum>\
											  </StorageInfo>\
											  <ResourceList>\
											  <Resource>\
											  <id>1</id>\
											  <storageName>A10-08</storageName>\
											  <storagePath>c:\\download</storagePath>\
											  <storageDescription>zhinengtuxiang</storageDescription>\
											  <storageType>1</storageType>\
											  </Resource>\
											  <Resource>\
											  <id>2</id>\
											  <storageName>A10-09</storageName>\
											  <storagePath>c:\\download</storagePath>\
											  <storageDescription>zhinengtuxiang_1</storageDescription>\
											  <storageType>2</storageType>\
											  </Resource>\
											  </ResourceList>\
											  <StorageVolume>\
											  </StorageResource>");
		break;
	case 8:  //获取设备名单报警列表
		m_dwCfgType = NET_DVR_GET_ALARMLIST;	
		xmlInputCond.Parse("<AlarmListCond>\
											 <inquireType>0</inquireType>\
											 <DevChanInfoList>\
											 <DevChanInfo>\
											 <Address>\
											 <ipVersion>0</ipVersion>\
											 <ipAddress>10.10.4.115</ipAddress>\
											 <port>8000</port>\
											 </Address>\
											 <chanNo>1</chanNo>\
											 </DevChanInfo>\
											 </DevChanInfoList>\
											 <startTime>2015-3-24T00:00:00+08:00</startTime>\
											 <endTime>2015-3-24T23:59:59+08:00</endTime>\
											 <minValue>1</minValue>\
											 <maxValue>100</maxValue>\
											 <alarmType>1</alarmType>\
											 <resultType>1</resultType>\
											 <startListNo>0</startListNo>\
											 <maxRetListNum>10</maxRetListNum>\
											 <searchNum>20</searchNum>\
											 </AlarmListCond>");
		break;
	case 9:  //由分组信息获取名单报警列表
		m_dwCfgType = NET_DVR_GET_ALARMLIST;	
		xmlInputCond.Parse("<AlarmListCond>\
											 <inquireType>1</inquireType>\
											 <GroupIDList>\
											 <groupID>1,2,3</groupID>\
											 </GroupIDList>\
											 </DevChanInfoList>\
											 <startTime>2015-3-23T00:00:00+08:00</startTime>\
											 <endTime>2015-3-23T23:59:59+08:00</endTime>\
											 <minValue>1</minValue>\
											 <maxValue>1</maxValue>\
											 <alarmType>0</alarmType>\
											 <resultType>1</resultType>\
											 <startListNo>0</startListNo>\
											 <maxRetListNum>10</maxRetListNum>\
											 <searchNum>20</searchNum>\
											 </AlarmListCond>");
		break;
	case 10://删除名单报警记录
		m_dwCfgType = NET_DVR_DEL_BLACKLIST_ALARM_RECORD;	
		xmlCfgParam.Parse("<AlarmRecord>\
										  <snapFaceID>1</snapFaceID>\
										  <alarmType>1</alarmType>\
										  <StorageInfo>\
										  <Address>\
										  <ipVersion>0</ipVersion>\
										  <ipAddress>10.10.4.115</ipAddress>\
										  <port>8000</port>\
										  </Address>\
										  </StorageInfo>\
										  </AlarmRecord>");
		break;
	case 11://获取名单分组列表
		m_dwCfgType = NET_DVR_GET_BLACKLIST_GROUP_INFO;
		xmlInputCond.Parse("<BlackListGroupCond>\
												  <groupID>0</groupID>\
												  </BlackListGroupCond>");
		break;
	case 12:  //添加名单分组参数
		m_dwCfgType = NET_DVR_SET_BLACKLIST_GROUP_INFO;	
		xmlCfgParam.Parse("<ListGroupInfo>\
											<groupType>blackList</groupType>\
											<threshold>90</threshold>\
											<groupName>TestABC</groupName>\
											<remark>测试数据</remark>\
											</ListGroupInfo>");
		break;
		// 	case 13: //修改名单分组参数
		// 		m_dwCfgType = NET_DVR_SET_BLACKLIST_GROUP_INFO;	
		// 		xmlCfgParam.Parse("<ListGroupInfo>\
		// 											 <groupNo>1</groupNo>\
		// 											 <groupType>blackList</groupType>\
		// 											 <threshold>90</threshold>\
		// 											 <groupNum>20</groupNum>\
		// 											 <groupName>TestABC</groupName>\
		// 											 <remark>测试数据</remark>\
		// 											 <Address>\
		// 											 <ipVersion>0</ipVersion>\
		// 											 <ipAddress>10.10.1.1</ipAddress>\
		// 											 <port>8000</port>\
		// 											 </Address>\
		// 											 </ListGroupInfo>");
		// 											 break;
	case 14: //删除名单分组
		m_dwCfgType = NET_DVR_DEL_BLACKLIST_GROUP_INFO;	
		xmlCfgParam.Parse("<ListGroupDelParam>\
												<Address>\
												<ipVersion>0</ipVersion>\
												<ipAddress>10.10.1.1</ipAddress>\
												<port>8000</port>\
												</Address>\
												<groupID>1</groupID>\
												</ListGroupDelParam>");
		break;
		
	case 15://获取名单分组记录
		m_dwCfgType = NET_DVR_GET_BLACKLIST_GROUP_RECORD_CFG;
		xmlInputCond.Parse("<SearchRecordCond>\
												<groupId>1</groupId>\
												<HumanAttribute>\
												<sex>male</sex>\
												<certificateType>identityCard</certificateType>\
												<certificateNumber>310101198801011111</certificateNumber>\
												<birthDate>198801</birthDate>\
												<name>zhangsan</name>\
												<NativePlace>\
												<nationalityID>1</nationalityID>\
												<provinceID>2</provinceID>\
												<cityID>3</cityID>\
												<countyID>4</countyID>\
												</NativePlace>\
												<ageGroup>youth</ageGroup>\
												<withGlass>true</withGlass>\
												</HumanAttribute>\
												<searchScopeNum>100</searchScopeNum>\
												<picType>1</picType>\
												<startId>1</startId>\
												<maxRetNum>10</maxRetNum>\
												</SearchRecordCond>");
		break;
	case 16: //添加名单分组记录
		m_dwCfgType = NET_DVR_SET_BLACKLIST_GROUP_RECORD_CFG;
		xmlCfgParam.Parse("<RecordInfo>\
										 <faceDBID>1</faceDBID>\
										 <faceRecordID>1</faceRecordID>\
										 <alarmLevel>high</alarmLevel>\
										 <Address>\
										 <ipVersion>0</ipVersion>\
										 <ipAddress>10.10.1.1</ipAddress>\
										 <port>8000</port>\
										 </Address>\
										 </RecordInfo>");
		break;
	case 17: //修改名单分组记录
		m_dwCfgType = NET_DVR_SET_BLACKLIST_GROUP_RECORD_CFG;
		xmlCfgParam.Parse("<RecordInfo>\
										 <groupID>1</groupID>\
										 <faceDBID>1</faceDBID>\
										 <faceRecordID>1</faceRecordID>\
										 <alarmLevel>high</alarmLevel>\
										 <Address>\
										 <ipVersion>0</ipVersion>\
										 <ipAddress>10.10.1.1</ipAddress>\
										 <port>8000</port>\
										 </Address>\
										 </RecordInfo>");
		break;
	case 18: //删除名单分组记录
		m_dwCfgType = NET_DVR_DEL_BLACKLIST_GROUP_RECORD_CFG;
		xmlCfgParam.Parse("<RecordInfo>\
										 <groupID>1</groupID>\
										 <faceDBID>1</faceDBID>\
										 <faceRecordID>1</faceRecordID>\
										 <alarmLevel>high</alarmLevel>\
										 <Address>\
										 <ipVersion>0</ipVersion>\
										 <ipAddress>10.10.1.1</ipAddress>\
										 <port>8000</port>\
										 </Address>\
										 </RecordInfo>");
		break;
	case 19:  //抓拍库检索
		m_dwCfgType =  NET_DVR_RETRIEVAL_SNAP_RECORD;
		xmlInputCond.Parse("<RetrievalSnapRecord>\
												   <userName>test1</userName>\
												   <SnapCond>\
												   <DevChanInfoList>\
												   <DevChanInfo>\
												   <Address>\
												   <ipVersion>0</ipVersion>\
												   <ipAddress>10.10.1.1</ipAddress>\
												   <port>8000</port>\
												   </Address>\
												   <chanNo>1</chanNo>\
												   </DevChanInfo>\
												   </DevChanInfoList>\
												   <picType>1</picType>\
												   <TimeRange>\
												   <startTime>2015-3-23T00:00:00+08:00</startTime>\
												   <endTime>2015-3-23T23:59:59+08:00</endTime>\
												   </TimeRange>\
												   <minSimilarity>60</minSimilarity>\
												   <maxSimilarity>90</maxSimilarity>\
												   <sex>male</sex>\
												   <ageGroup>youth</ageGroup>\
												   <withGlass>true</withGlass>\
												   <startId>1</startId>\
												   <maxRetNum>10</maxRetNum>\
												   <searchNum>200</searchNum>\
												   </SnapCond>\
												   <picData>C:\\Picture\\828_10_10_5_19_sub.jpg</picData>\
												   </RetrievalSnapRecord>");
		break;
	case 20: //大图识别	
		m_dwCfgType = NET_DVR_DETECT_IMAGE;
		xmlInputCond.Parse("<FDProcImage>\
												<picData>C:\\Picture\\828_10_10_5_19_sub.jpg</picData>\
												</FDProcImage>");
		break;		
	case 21://获取抓拍记录
		m_dwCfgType = NET_DVR_GET_SNAP_RECORD;
		xmlInputCond.Parse("<SnapRecordCond>\
											  <searchType>0</searchType>\
											  <BatchCond>\
											  <DevChanInfoList>\
											  <DevChanInfo>\
											  <Address>\
											  <ipVersion>0</ipVersion>\
											  <ipAddress>10.10.5.20</ipAddress>\
											  <port>7000</port>\
											  </Address>\
											  <chanNo>1</chanNo>\
											  </DevChanInfo>\
											  </DevChanInfoList>\
											  <picType>1</picType>\
											  <TimeRange>\
											  <startTime>2015-3-23T00:00:00+08:00</startTime>\
											  <endTime>2015-3-23T23:59:59+08:00</endTime>\
											  </TimeRange>\
											  <sex>male</sex>\
											  <ageGroup>prime</ageGroup>\
											  <withGlass>true</withGlass>\
											  <startId>1</startId>\
											  <maxRetNum>10</maxRetNum>\
											  <searchNum>100</searchNum>\
											  </BatchCond>\
											  </SnapRecordCond>");
		break;
	case 22: //删除抓拍记录
		m_dwCfgType = NET_DVR_DEL_SNAP_RECORD;	
		xmlCfgParam.Parse("<DelSnapRecordCond>\
												<recordId>1</recordId>\
												<Address>\
												<ipVersion>0</ipVersion>\
												<ipAddress>10.10.5.20</ipAddress>\
												<port>7000</port>\
												</Address>\
												</DelSnapRecordCond>");
		break;
	case 23://获取人脸记录列表
		m_dwCfgType = NET_DVR_GET_FACE_RECORD;
		xmlInputCond.Parse("<InquireRecordCond>\
												 <searchType>0</searchType>\
												 <BatchCond>\
												 <faceDbId>1</faceDbId>\
												 <Address>\
												 <ipVersion>0</ipVersion>\
												 <ipAddress>10.10.5.20</ipAddress>\
												 <port>7000</port>\
												 </Address>\
												 <HumanAttribute>\
												 <sex>male</sex>\
												 <certificateType>identityCard</certificateType>\
												 <certificateNumber>310101198801011111</certificateNumber>\
												 <birthDate>198801</birthDate>\
												 <name>zhangsan</name>\
												 <NativePlace>\
												 <nationalityID>1</nationalityID>\
												 <provinceID>2</provinceID>\
												 <cityID>3</cityID>\
												 <countyID>4</countyID>\
												 </NativePlace>\
												 <ageGroup>adoleScent</ageGroup>\
												 <withGlass>true</withGlass>\
												 </HumanAttribute>\
												 <picType>1</picType>\
												 <startId>1</startId>\
												 <maxRetNum>10</maxRetNum>\
												 <searchScopeNum>100</searchScopeNum>\
												 </BatchCond>\
												 </InquireRecordCond>");
		break;
	case 24: //添加人脸记录
		m_dwCfgType = NET_DVR_SET_FACE_RECORD;
		xmlCfgParam.Parse("<FaceRecord>\
										 <faceDBId>2</faceDBId>\
										 <similarity>100</similarity>\
										 <HumanAttribute>\
										 <sex>male</sex>\
										 <certificateType>identityCard</certificateType>\
										 <certificateNumber>310101198801011111</certificateNumber>\
										 <birthDate>198801</birthDate>\
										 <name>zhangsan</name>\
										 <NativePlace>\
										 <nationalityID>1</nationalityID>\
										 <provinceID>2</provinceID>\
										 <cityID>3</cityID>\
										 <countyID>4</countyID>\
										 </NativePlace>\
										 <ageGroup>adoleScent</ageGroup>\
										 <withGlass>true</withGlass>\
										 </HumanAttribute>\
										 <group>2</group>\
										 <type>1</type>\
										 <StorageInfo>\
										 <Address>\
										 <ipVersion>0</ipVersion>\
										 <ipAddress>10.10.5.20</ipAddress>\
										 <port>8000</port>\
										 </Address>\
										 </StorageInfo>\
										 <picData>1111111</picData>\
										 <note1>23456</note1>\
										 <note2>11111</note2>\
										 </FaceRecord>");
		break;
	case 25: //修改人脸记录
		m_dwCfgType = NET_DVR_SET_FACE_RECORD;
		xmlCfgParam.Parse("<FaceRecord>\
										 <id>1</id>\
										 <faceDBId>2</faceDBId>\
										 <similarity>100</similarity>\
										 <HumanAttribute>\
										 <sex>male</sex>\
										 <certificateType>identityCard</certificateType>\
										 <certificateNumber>310101198801011111</certificateNumber>\
										 <birthDate>198801</birthDate>\
										 <name>zhangsan</name>\
										 <NativePlace>\
										 <nationalityID>1</nationalityID>\
										 <provinceID>2</provinceID>\
										 <cityID>3</cityID>\
										 <countyID>4</countyID>\
										 </NativePlace>\
										 <ageGroup>adoleScent</ageGroup>\
										 <withGlass>true</withGlass>\
										 </HumanAttribute>\
										 <group>2</group>\
										 <type>1</type>\
										 <StorageInfo>\
										 <Address>\
										 <ipVersion>0</ipVersion>\
										 <ipAddress>10.10.5.20</ipAddress>\
										 <port>8000</port>\
										 </Address>\
										 </StorageInfo>\
										 <picData>1111111</picData>\
										 <note1>23456</note1>\
										 <note2>11111</note2>\
										 </FaceRecord>");
		break;			
	case 26: //删除人脸记录
		m_dwCfgType = NET_DVR_DEL_FACE_RECORD;	
		xmlCfgParam.Parse("<DelFaceRecordCond>\
												<recordId>1</recordId>\
												<faceDbId>20</faceDbId>\
												<Address>\
												<ipVersion>0</ipVersion>\
												<ipAddress>10.10.5.20</ipAddress>\
												<port>8000</port>\
												</Address>\
												</DelFaceRecordCond>");
		break;			
		
	case 27: //添加人脸库
		m_dwCfgType = NET_DVR_SET_FACE_DATABASE;
		xmlCfgParam.Parse("<FaceDataBase>\
										   <name>Test1</name>\
										   <note>ForTest1</note>\
										   <Address>\
										   <ipVersion>0</ipVersion>\
										   <ipAddress>10.10.5.20</ipAddress>\
										   <port>8000</port>\
										   </Address>\
										   </FaceDataBase>");
		break;
	case 28: //修改人脸库
		m_dwCfgType = NET_DVR_SET_FACE_DATABASE;
		xmlCfgParam.Parse("<FaceDataBase>\
										   <dataBaseID>20</dataBaseID>\
										   <name>Test1</name>\
										   <note>ForTest1</note>\
										   <Address>\
										   <ipVersion>0</ipVersion>\
										   <ipAddress>10.10.5.20</ipAddress>\
										   <port>8000</port>\
										   </Address>\
										   </FaceDataBase>");
		break;
	case 29://获取人脸库列表
		m_dwCfgType = NET_DVR_GET_FACE_DATABASE;
		xmlInputCond.Parse("<RetrievalFaceDBCond>\
												   <startId>1</startId>\
												   <maxRetNum>10</maxRetNum>\
												   </RetrievalFaceDBCond>");
		break;
	case 30: //删除人脸库
		m_dwCfgType = NET_DVR_DEL_FACE_DATABASE;	
		xmlCfgParam.Parse("<FaceDataBase>\
										   <dataBaseID>1</dataBaseID>\
										   <name>testaaa</name> \
										   <note>note</note>\
										   <Address>\
										   <ipVersion>0</ipVersion>\
										   <ipAddress>10.10.5.20</ipAddress>\
										   <port>8000</port>\
										   </Address>\
										   </FaceDataBase>");
		break;			
	case 31: //人脸库检索
		m_dwCfgType = NET_DVR_RETRIEVAL_FACE_DATABASE;
		xmlInputCond.Parse("<RetrievalFaceRecord>\
												   <userName>test123</userName>\
												   <FaceCond>\
												   <FaceDbInfoList>\
												   <faceDbId>1</faceDbId>\
												   <Address>\
												   <ipVersion>0</ipVersion>\
												   <ipAddress>10.10.5.20</ipAddress>\
												   <port>8000</port>\
												   </Address>\
												   </FaceDbInfoList>\
												   <picType>1</picType>\
												   <minSimilarity>1</minSimilarity>\
												   <maxSimilarity>100</maxSimilarity>\
												   <HumanAttribute>\
												   <sex>male</sex>\
												   <certificateType>identityCard</certificateType>\
												   <certificateNumber>310101198801011111</certificateNumber>\
												   <birthDate>198801</birthDate>\
												   <name>zhangsan</name>\
												   <NativePlace>\
												   <nationalityID>1</nationalityID>\
												   <provinceID>2</provinceID>\
												   <cityID>3</cityID>\
												   <countyID>4</countyID>\
												   </NativePlace>\
												   <ageGroup>adoleScent</ageGroup>\
												   <withGlass>true</withGlass>\
												   </HumanAttribute>\
												   <startId>10</startId>\
												   <maxRetNum>10</maxRetNum>\
												   <searchNum>10000</searchNum>\
												   <picData>111</picData>\
												   </FaceCond>\
												   </RetrievalFaceRecord>");
		break;		
	case 32: //添加分组名单关联设备
		m_dwCfgType = NET_DVR_SET_BLACKLIST_REL_DEV_CFG;
		xmlCfgParam.Parse("<GroupRelDevInfo><RelateInfoList>\
											  <RelateInfo>\
											  <devID>1</devID>\
											  <groupID>1</groupID>\
											  <Address>\
											  <ipVersion>0</ipVersion>\
											  <ipAddress>10.10.5.19</ipAddress>\
											  <port>8003</port>\
											  </Address>\
											  </RelateInfo>\
											  </RelateInfoList>\
											  </GroupRelDevInfo>");
		break;
	case 33: //修改分组名单关联设备
		m_dwCfgType = NET_DVR_SET_BLACKLIST_REL_DEV_CFG;
		xmlCfgParam.Parse("<GroupRelDevInfo>\
											  <RelateInfoList>\
											  <RelateInfo>\
											  <devID>1</devID>\
											  <groupID>1</groupID>\
											  <Address>\
											  <ipVersion>0</ipVersion>\
											  <ipAddress>10.10.5.19</ipAddress>\
											  <port>8003</port>\
											  </Address>\
											  </RelateInfo>\
											  </RelateInfoList>\
											  </GroupRelDevInfo>");
		break;
	case 34: //删除分组名单关联设备
		m_dwCfgType = NET_DVR_DEL_BLACKLIST_REL_DEV;	
		xmlCfgParam.Parse("<GroupRelDevInfo>\
											  <RelateInfoList>\
											  <RelateInfo>\
											  <devID>1</devID>\
											  <groupID>1</groupID>\
											  <Address>\
											  <ipVersion>0</ipVersion>\
											  <ipAddress>10.10.5.19</ipAddress>\
											  <port>8003</port>\
											  </Address>\
											  </RelateInfo>\
											  </RelateInfoList>\
											  </GroupRelDevInfo>");
		break;			
	default:
		break;
	}
	
	xmlInputCond.SetRoot();
	m_csInputCond = xmlInputCond.GetChildren().c_str();
	m_csInputCond.Replace("\n", "\r\n");


	xmlCfgParam.SetRoot();
	m_csConfigParam = xmlCfgParam.GetChildren().c_str();
	m_csConfigParam.Replace("\n", "\r\n");
	UpdateData(FALSE);

}

BOOL  CDlgAreaMonitorCfg::ParseAreaMonitorCond(NET_DVR_AREA_MONITOR_COND* pStruCond)
{
	CXmlBase    struXml;
	char szLan[128] = {0};
    if (struXml.Parse(m_csInputCond.GetBuffer(0)) == NULL)
    {
        return FALSE;
    }
       
	pStruCond->dwSize = sizeof(NET_DVR_AREA_MONITOR_COND);
    string csDetectionTarget = "";
    if (struXml.FindElem("AreaMonitorCond") && struXml.IntoElem())
    {
        ConvertSingleNodeData(&pStruCond->dwAreaID, struXml, "dwAreaID", NODE_STRING_TO_INT);
		ConvertSingleNodeData(&pStruCond->dwMonitorID, struXml, "dwMonitorID", NODE_STRING_TO_INT);							
		ConvertSingleNodeData(&pStruCond->byIsNeedGroup, struXml, "byIsNeedGroup", NODE_STRING_TO_BYTE);							
        struXml.OutOfElem();
    }
	return TRUE;
}

BOOL    CDlgAreaMonitorCfg::ParseSetAreaMonitorCond(DWORD* pData)
{
	CXmlBase    struXml;
	char szLan[128] = {0};
    if (struXml.Parse(m_csInputCond.GetBuffer(0)) == NULL)
    {
        return FALSE;
    }
	
	string strTemp = UTF82A(struXml.GetData().c_str());
    string csDetectionTarget = "";
    if (struXml.FindElem("AreaMonitorCond") && struXml.IntoElem())
    {
        ConvertSingleNodeData(pData, struXml, "dwAreaID", NODE_STRING_TO_INT);		
        struXml.OutOfElem();
    }
	return TRUE;
}

BOOL CDlgAreaMonitorCfg::ParseSetAreaMonitorParam()
{
	CXmlBase    struXml;
	char szLan[128] = {0};
    if (struXml.Parse(m_csInputCond.GetBuffer(0)) == NULL)
    {
        return FALSE;
    }
	
    
	return TRUE;
}

BOOL  CDlgAreaMonitorCfg::ParseGetStorageResourceCond(NET_DVR_STORAGE_RESOURCE_COND* pData)
{
	CXmlBase    struXml;
	char szLan[128] = {0};
    if (struXml.Parse(m_csInputCond.GetBuffer(0)) == NULL)
    {
        return FALSE;
    }
	
	pData->dwSize = sizeof(NET_DVR_STORAGE_RESOURCE_COND);
    string csDetectionTarget = "";
    if (struXml.FindElem("StorageResourceCond") && struXml.IntoElem())
    {
        ConvertSingleNodeData(&pData->dwStorageID, struXml, "currentID", NODE_STRING_TO_INT);						
        struXml.OutOfElem();
  }
	return TRUE;
}

BOOL    CDlgAreaMonitorCfg::ParseGetBlackListGroupInfoCond(NET_DVR_BLACKLIST_GROUP_COND* pData)
{
	CXmlBase    struXml;
	char szLan[128] = {0};
    if (struXml.Parse(m_csInputCond.GetBuffer(0)) == NULL)
    {
        return FALSE;
    }
	
	pData->dwSize = sizeof(NET_DVR_BLACKLIST_GROUP_COND);
    string csDetectionTarget = "";
    if (struXml.FindElem("BlackListGroupCond") && struXml.IntoElem())
    {
        ConvertSingleNodeData(&pData->dwGroupID, struXml, "groupID", NODE_STRING_TO_INT);						
        struXml.OutOfElem();
	}
	return TRUE;
}
/*********************************************************
函数名:	ConvertSingleNodeData
函数描述:	简单数据类型的单个节点数据转换
输入参数:	pStructVale: 码字类型的数据指针,按类型不同可能作为输出参数;            
            struXml:xml数据类对象,按类型不同可能作为输出参数
            pNodeName:要转换的当前xml节点名称
            byDataType:转换类型,具体参见XML_NODE_TYPE
            nArrayLen:string to array时的数组大小,增加判断避免溢出
输出参数:	            
返回值:	    TRUE-成功,FALSE-失败
**********************************************************/
BOOL CDlgAreaMonitorCfg::ConvertSingleNodeData(void *pStructVale, CXmlBase &struXml, const char* pNodeName, BYTE byDataType, DWORD nArrayLen)
{
    if (byDataType < NODE_TYPE_REVERSE)
    {
        if (struXml.FindElem(pNodeName))
        {
            //string to
            if (byDataType == NODE_STRING_TO_BOOL)    //bool类型
            {
                if (struXml.GetData().compare("true") == 0)
                {
                    *(BYTE*)pStructVale = 1;
                    return TRUE;
                }
                else if(struXml.GetData().compare("false") == 0)
                {
                    *(BYTE*)pStructVale = 0;
                    return TRUE;
                }            
            }
            else if (byDataType == NODE_STRING_TO_INT)   //int类型
            {
                if (struXml.GetData() != "")
                {
                    *(DWORD*)pStructVale = (DWORD)atoi(struXml.GetData().c_str());
                    return TRUE;
                }                       
            }
            else if (byDataType == NODE_STRING_TO_ARRAY)
            {
                string strTmp = UTF82A(struXml.GetData().c_str());
                if (strTmp != "")
                {
                    int nLen = (int)strTmp.length();
                    if (nLen > nArrayLen)
                    {
                        nLen = nArrayLen;
                    }
                    memcpy((char*)pStructVale, strTmp.c_str(), (DWORD)nLen);
                    return TRUE;
                }
            }
            else if (byDataType == NODE_STRING_TO_BYTE)
            {
                if (struXml.GetData() != "")
                {
                    *(BYTE*)pStructVale = (BYTE)atoi(struXml.GetData().c_str());
                    return TRUE;
                }
            }
            else if (byDataType == NODE_STRING_TO_WORD)
            {
                if (struXml.GetData() != "")
                {
                    *(WORD*)pStructVale = (WORD)atoi(struXml.GetData().c_str());
                    return TRUE;
                }
            }
            else if(byDataType == NODE_STRING_TO_FLOAT)
            {
                if (struXml.GetData() != "")
                {
                    *(float*)pStructVale = (float)atof(struXml.GetData().c_str());
                    return TRUE;
                }
            }
        }
        else
        {
            //Core_WriteLogStr(DEBUG_LEVEL, __FILE__, __LINE__, "find node %s failed", pNodeName);
            return TRUE;//没找到节点认为设备不支持,也返回正确
        }
        
    }
    else if(byDataType > NODE_TYPE_REVERSE)
    {
        if (byDataType == NODE_BOOL_TO_STRING)
        {
            if (*(BYTE*)pStructVale == 0)
            {
                if (struXml.AddNode(pNodeName, "false"))
                {
                    struXml.OutOfElem();
                    return TRUE;
                }
            }
            else if (*(BYTE*)pStructVale == 1)
            {
                if(struXml.AddNode(pNodeName, "true"))
                {
                    struXml.OutOfElem();
                    return TRUE;
                }                
            }
        }
        else if (byDataType == NODE_INT_TO_STRING)
        {
            char szBuf[16] = {0};
            //itoa(szBuf, *(int*)pStructVale, 10);
            if (struXml.AddNode(pNodeName, szBuf))
            {
                struXml.OutOfElem();
                return TRUE;
            }
        }
        else if (byDataType == NODE_ARRAY_TO_STRING)
        {
            string strValue = "";
            if (nArrayLen == 0)
            {
                strValue = A2UTF8((char*)pStructVale);
            }
            else 
            {
                int nValueLen = (int)strlen((char*)pStructVale);
                if (nValueLen < nArrayLen) //数组没有被填满,有结束符
                {
                    strValue = A2UTF8((char*)pStructVale);
                }
                else    
                {
                    char *lpTmp = NULL;
                    lpTmp =  new char(nArrayLen + 1);
                    if (lpTmp == NULL)
                    {
                        return FALSE;
                    }
                    memset(lpTmp,0, nArrayLen + 1);
                    memcpy(lpTmp, (char*)pStructVale, (DWORD)nArrayLen);//增加一个结束符
                    strValue = A2UTF8(lpTmp);
                    if (lpTmp != NULL)
                    {
						delete[] lpTmp;
						lpTmp = NULL;
                    }   
                }
            }
            if (struXml.AddNode(pNodeName, strValue.c_str()))
            {
                struXml.OutOfElem();
                return TRUE;
            }
        }
        else if (byDataType == NODE_BYTE_TO_STRING)
        {
            char szBuf[16] = {0};
            int nTmp = (int)*(BYTE*)pStructVale; 
            //HPR_Itoa(szBuf, nTmp, 10);
            if (struXml.AddNode(pNodeName, szBuf))
            {
                struXml.OutOfElem();
                return TRUE;
            }
        }
        else if (byDataType == NODE_WORD_TO_STRING)
        {
            char szBuf[16] = {0};
            int nTmp = (int)*(WORD*)pStructVale; 
           // HPR_Itoa(szBuf, nTmp, 10);
            if (struXml.AddNode(pNodeName, szBuf))
            {
                struXml.OutOfElem();
                return TRUE;
            }
        }
    }

    return FALSE;
}

/*********************************************************
函数名:	ConvertSingleNodeStringData
函数描述:	简单数据类型的单个节点数据转换
输入参数:	pStructVale: 码字类型的数据指针,按类型不同可能作为输出参数;            
            struXml:xml数据类对象,按类型不同可能作为输出参数
            pNodeName:要转换的当前xml节点名称
            byDataType:转换类型,具体参见XML_NODE_TYPE
            nArrayLen:string to array时的数组大小,增加判断避免溢出
输出参数:	            
返回值:	    TRUE-成功,FALSE-失败
**********************************************************/
BOOL CDlgAreaMonitorCfg::ConvertSingleNodeStringData(void *pStructVale, CXmlBase &struXml, const char* pNodeName, BYTE byDataType)
{
	string csDetectionTarget = "";
	if (NODE_STRING_TO_BYTE_DETECTION_TARGET == byDataType)
	{
		if (struXml.FindElem(pNodeName))
		{
			csDetectionTarget = struXml.GetData();
			if (csDetectionTarget.compare("all") == 0)
			{	
				*(BYTE*)pStructVale = 0;
				return TRUE;
			}
			else if (csDetectionTarget.compare("human") == 0)
			{
				*(BYTE*)pStructVale = 1;
				return TRUE;
			}
			else if (csDetectionTarget.compare("vehicle") == 0)
			{
				*(BYTE*)pStructVale = 2;
				return TRUE;
			}	
		}	
	}
	else if (NODE_BYTE_TO_STRING_DETECTION_TARGET == byDataType)
	{
		if ((*(BYTE*)pStructVale) == 0)
		{
			struXml.AddNode(pNodeName, "all");
			struXml.OutOfElem();
			return TRUE;
		}
		else if ((*(BYTE*)pStructVale) == 1)
		{
			struXml.AddNode(pNodeName, "human");
			struXml.OutOfElem();
			return TRUE;
		}
		else if ((*(BYTE*)pStructVale) == 2)
		{
			struXml.AddNode(pNodeName, "vehicle");
			struXml.OutOfElem();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL	CDlgAreaMonitorCfg::LoadRetrievalSnapRecordPicData(DWORD* dwAllDataLen,char *&pAllData)
{

	CXmlBase    struXml;
	char szLan[128] = {0};
    if (struXml.Parse(m_csInputCond.GetBuffer(0)) == NULL)
    {
        return FALSE;
    }
	
    string csDetectionTarget = "";
	char csFileName[260] = {0};
    if (struXml.FindElem("RetrievalSnapRecord") && struXml.IntoElem())
    {
		ConvertSingleNodeData(csFileName, struXml, "picData", NODE_STRING_TO_ARRAY, 260);					
        struXml.OutOfElem();
	}
	
	CFile cFile;
	
	if (!cFile.Open(csFileName, CFile::modeRead))
	{
		g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
		AfxMessageBox(szLan);
		return FALSE;
	}
	else
	{
		DWORD dwPicDataLen = (DWORD)cFile.GetLength();
		if (dwPicDataLen == 0)
		{
			g_StringLanType(szLan, "文件大小为空", "Picture file is empty");
			AfxMessageBox(szLan);
			return FALSE;
		}          
		
		char *pPicData = new char[dwPicDataLen];
		if (pPicData == NULL)
		{
			g_StringLanType(szLan, "申请内存失败", "Application of memory failure");
			AfxMessageBox(szLan);
			return FALSE;
		}
		
		cFile.Read(pPicData, dwPicDataLen);
		cFile.Close();
		
		
		if (pAllData != NULL)
		{
			return FALSE;
		}
		
		CString csCondData = m_csInputCond;
		DWORD dwLen = csCondData.GetLength();
		pAllData = new char[dwLen+dwPicDataLen];
		if (*pAllData == NULL)
		{
			return FALSE;
		}
		
		memset(pAllData,0,dwPicDataLen+dwLen);
		
	
		m_csInputCond = "";
		
		m_csInputCond = csCondData.Left(csCondData.Find("<picData>"));
		dwLen = m_csInputCond.GetLength();
		memcpy(pAllData,m_csInputCond.GetBuffer(0),dwLen);

		m_csInputCond ="<picData>";
	
		memcpy(pAllData+dwLen,m_csInputCond.GetBuffer(0),m_csInputCond.GetLength());
		dwLen += m_csInputCond.GetLength();
		memcpy(pAllData+dwLen,pPicData,dwPicDataLen);
		dwLen += dwPicDataLen;
		
		m_csInputCond ="</picData>";
		memcpy(pAllData+dwLen,m_csInputCond.GetBuffer(0),m_csInputCond.GetLength());
		dwLen += m_csInputCond.GetLength();
		m_csInputCond =csCondData.Right(csCondData.GetLength() - csCondData.Find("</picData>")-strlen("</picData>"));
		memcpy(pAllData+dwLen,m_csInputCond.GetBuffer(0),m_csInputCond.GetLength());
		dwLen += m_csInputCond.GetLength();
		//
		m_csInputCond = csCondData;
		*dwAllDataLen = dwLen;
		if (pPicData != NULL)
		{
			delete[] pPicData;
			pPicData = NULL;
		}
	}


	return TRUE;
}

BOOL    CDlgAreaMonitorCfg::LoadDetectImagePicData(DWORD* dwAllDataLen, char* &pAllData)
{
	
	CXmlBase    struXml;
	char szLan[128] = {0};
    if (struXml.Parse(m_csInputCond.GetBuffer(0)) == NULL)
    {
        return FALSE;
    }
	
    string csDetectionTarget = "";
	char csFileName[260] = {0};
    if (struXml.FindElem("FDProcImage") && struXml.IntoElem())
    {
		ConvertSingleNodeData(csFileName, struXml, "picData", NODE_STRING_TO_ARRAY, 260);					
        struXml.OutOfElem();
	}
	
	CFile cFile;
	
	if (!cFile.Open(csFileName, CFile::modeRead))
	{
		g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
		AfxMessageBox(szLan);
		return FALSE;
	}
	else
	{
		DWORD dwPicDataLen = (DWORD)cFile.GetLength();
		if (dwPicDataLen == 0)
		{
			g_StringLanType(szLan, "文件大小为空", "Picture file is empty");
			AfxMessageBox(szLan);
			return FALSE;
		}          
		
		char *pPicData = new char[dwPicDataLen];
		if (pPicData == NULL)
		{
			g_StringLanType(szLan, "申请内存失败", "Application of memory failure");
			AfxMessageBox(szLan);
			return FALSE;
		}
		
		cFile.Read(pPicData, dwPicDataLen);
		cFile.Close();
		
		
		if (pAllData != NULL)
		{
			return FALSE;
		}
		
		CString csCondData = m_csInputCond;
		DWORD dwLen = csCondData.GetLength();
		pAllData = new char[dwLen+dwPicDataLen];
		if (*pAllData == NULL)
		{
			return FALSE;
		}
		
		memset(pAllData,0,dwPicDataLen+dwLen);
		
		
		m_csInputCond = "";
		
		m_csInputCond = csCondData.Left(csCondData.Find("<picData>"));
		dwLen = m_csInputCond.GetLength();
		memcpy(pAllData,m_csInputCond.GetBuffer(0),dwLen);
		
		m_csInputCond ="<picData>";
		
		memcpy(pAllData+dwLen,m_csInputCond.GetBuffer(0),m_csInputCond.GetLength());
		dwLen += m_csInputCond.GetLength();
		memcpy(pAllData+dwLen,pPicData,dwPicDataLen);
		dwLen += dwPicDataLen;
		
		m_csInputCond ="</picData>";
		memcpy(pAllData+dwLen,m_csInputCond.GetBuffer(0),m_csInputCond.GetLength());
		dwLen += m_csInputCond.GetLength();
		m_csInputCond =csCondData.Right(csCondData.GetLength() - csCondData.Find("</picData>")-strlen("</picData>"));
		memcpy(pAllData+dwLen,m_csInputCond.GetBuffer(0),m_csInputCond.GetLength());
		dwLen += m_csInputCond.GetLength();
		//
		m_csInputCond = csCondData;
		*dwAllDataLen = dwLen;
		if (pPicData != NULL)
		{
			delete[] pPicData;
			pPicData = NULL;
		}
	}
	
	
	return TRUE;
}
void CDlgAreaMonitorCfg::OnBtnDetect() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaSingleProcImg dlg;
    dlg.m_lServerID = m_lUserID;
//	dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}
