// DlgMCUGetDailyDistribution.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUGetDailyDistribution.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUGetDailyDistribution dialog


CDlgMCUGetDailyDistribution::CDlgMCUGetDailyDistribution(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUGetDailyDistribution::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMCUGetDailyDistribution)
		// NOTE: the ClassWizard will add member initialization here

	m_dwCondYear = 2015;
	m_dwCondMonth = 1;
	
	m_dwConfCount = 0;

    m_nIndex  = 0;

	for (int i = 0; i < MAX_DAILY_CONF_COUNT; i++)
	{
		memset(&m_ConfDailyLst[i], 0, sizeof(ConfDaliyInfo));
	}


	//}}AFX_DATA_INIT
}


void CDlgMCUGetDailyDistribution::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMCUGetDailyDistribution)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_EDT_YEAR, m_dwCondYear);
	DDX_Text(pDX, IDC_EDT_MONTH, m_dwCondMonth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMCUGetDailyDistribution, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUGetDailyDistribution)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUGetDailyDistribution message handlers

BOOL CDlgMCUGetDailyDistribution::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_szRequestURL = new char[ISAPI_DATA_LEN];  
    if (m_szRequestURL == NULL)
    {
        return FALSE;
    }
    memset(m_szRequestURL, '\0' , ISAPI_DATA_LEN);
    m_szXMLResultBuf = new char[ISAPI_DATA_LEN];
    if (m_szXMLResultBuf == NULL)
    {
        return FALSE;
    }
    memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
    m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    m_szXMLStatus = new char[ISAPI_STATUS_LEN];
    if (m_szXMLStatus == NULL)
    {
        return FALSE;
    }
    memset(m_szXMLStatus, '\0', ISAPI_STATUS_LEN);

	
	m_pListDailyDistribute      = (CListCtrl*)GetDlgItem(IDC_LST_CONF_DISTRIBUTE);
	
	LONG lStyle;
    lStyle = GetWindowLong(m_pListDailyDistribute->m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT;    //设置style
    SetWindowLong(m_pListDailyDistribute->m_hWnd, GWL_STYLE, lStyle);//设置style
    
    DWORD dwStyle = m_pListDailyDistribute->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;    //网格线（只适用与report风格的listctrl）
    //dwStyle |= LVS_EX_CHECKBOXES;   //item前生成checkbox控件
    m_pListDailyDistribute->SetExtendedStyle(dwStyle); //设置扩展风格
	
	m_pListDailyDistribute->InsertColumn(0, "Index", LVCFMT_LEFT, 60);//插入列
    m_pListDailyDistribute->InsertColumn(1, "ID", LVCFMT_LEFT, 80);//插入列
    m_pListDailyDistribute->InsertColumn(2, "日期", LVCFMT_LEFT, 80);//插入列
	m_pListDailyDistribute->InsertColumn(3, "是否为会议", LVCFMT_LEFT, 100);//插入列
 	
	UpdateData(FALSE);

	return true;
}

void CDlgMCUGetDailyDistribution::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

    memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
    memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
    m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));

	UpdateData(TRUE);


    m_pListDailyDistribute->DeleteAllItems();

    m_nIndex = 0;

	//ConferenceDailyParam

	//生成XML数据流
	CXmlBase struXmlParam;
	struXmlParam.CreateRoot("ConferenceDailyParam");
	struXmlParam.SetAttribute("version", "2.0");
	struXmlParam.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

	ConvertSingleNodeData(&m_dwCondYear, struXmlParam, "year", NODE_INT_TO_STRING);
	ConvertSingleNodeData(&m_dwCondMonth, struXmlParam, "monthOfYear", NODE_INT_TO_STRING);

	//将XML转存到buffer中
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	if (!PrintXmlToNewBuffer(&m_pXMLParamBuf, m_dwXMLParamBufLen, struXmlParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PrintXmlToNewBuffer Error");
		return;
	}
	
	//Debug
	//CString strMsg = m_pXMLParamBuf;
	//MessageBox(strMsg);

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "GET /ISAPI/VCS/conferenceDailyDistribution\r\n%s", m_pXMLParamBuf);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = NULL;
	struXMLCfgInput.dwInBufferSize  = 0;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = (char*)m_szXMLResultBuf;
	struXMLCfgOutput.dwOutBufferSize = ISAPI_DATA_LEN;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = ISAPI_STATUS_LEN;
	
	LPNET_DVR_XML_CONFIG_OUTPUT lpXMLCfgOutput = &struXMLCfgOutput;

	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, lpXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);

		delete[] m_pXMLParamBuf;
		m_pXMLParamBuf = NULL;
		m_dwXMLParamBufLen = 0;

		return;
    }

	//状态处理
	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);

	delete[] m_pXMLParamBuf;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;

	//处理struXMLCfgOutput.lpOutBuffer
	CXmlBase struXmlResult;
	
	if (struXmlResult.Parse((char*)struXMLCfgOutput.lpOutBuffer))
	{
		if (struXmlResult.FindElem("ConferenceDailyDistribution") && struXmlResult.IntoElem())
		{
			if (struXmlResult.FindElem("DayList") && struXmlResult.IntoElem())
			{
				ConfDaliyInfo struConfDailyInfo = {0};

                do 
				
				{
                    if (struXmlResult.FindElem("Day") && struXmlResult.IntoElem())
                    {
                                    
                        memset(&struConfDailyInfo, 0, sizeof(struConfDailyInfo));
                        
                        if (struXmlResult.FindElem("id"))
                        {
                            ConvertSingleNodeData(&(struConfDailyInfo.dwID), struXmlResult, "id", NODE_STRING_TO_INT);
                        }
                        if (struXmlResult.FindElem("dayOfMonth"))
                        {
                            ConvertSingleNodeData(&(struConfDailyInfo.dwDay), struXmlResult, "dayOfMonth", NODE_STRING_TO_INT);
                        }
                        if (struXmlResult.FindElem("conference"))
                        {
                            ConvertSingleNodeData(&(struConfDailyInfo.bConf), struXmlResult, "conference", NODE_STRING_TO_BOOL);
                        }
                        
                        InsertConfDailyInfo(struConfDailyInfo);
                        
                        m_ConfDailyLst[m_dwConfCount] = struConfDailyInfo;
                        
                        m_dwConfCount++;
                        
                        struXmlResult.OutOfElem();
                    }

                }while (struXmlResult.NextSibElem());

				struXmlResult.OutOfElem();
			}

			struXmlResult.OutOfElem();
		}
	}

	UpdateData(FALSE);
	
}


CString CDlgMCUGetDailyDistribution::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
{
    DWORD dwStatusCode = 0;
    char  szStatusInfo  [256] = {0};
    char  szStatusString[128] = {0};
    char  szID          [256] = {0};
    
    CString csRet;
    
    CXmlBase struXmlStatus;
    if (struXmlStatus.Parse(lpStatusBuf))
    {
        if (struXmlStatus.FindElem("ResponseStatus") && struXmlStatus.IntoElem())
        {
            if (struXmlStatus.FindElem("statusCode"))
            {
                ConvertSingleNodeData(&dwStatusCode, struXmlStatus, "statusCode", NODE_STRING_TO_INT);
                
                sprintf((char*)szStatusInfo, "%s", GetStatusCodeInfo(dwStatusCode));
                if (dwStatusCode == 0 || dwStatusCode == 1)
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szStatusInfo);
                }
                else
                {
                    if (struXmlStatus.FindElem("statusString"))
                    {
                        ConvertSingleNodeData((char*)&szStatusString, struXmlStatus, "statusString", NODE_STRING_TO_ARRAY, 128);
                        sprintf((char*)szStatusInfo, "StatusString: %s", szStatusString);
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szStatusInfo);
                        struXmlStatus.OutOfElem();
                    }	
                }
                if (struXmlStatus.FindElem("ID"))
                {
                    ConvertSingleNodeData(&szID, struXmlStatus, "ID", NODE_STRING_TO_ARRAY, 256);
                    csRet = szID;
                }	
            }
        }
    }
    else
    {
        //g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Status XML Parse Error");
    }
    return csRet;
}

void CDlgMCUGetDailyDistribution::InsertConfDailyInfo(const ConfDaliyInfo& struConfDailyInfo)
{
	m_nIndex++;
	CString strTemp;
	
	strTemp.Format("%d", m_nIndex);
	int nHeadNum = m_pListDailyDistribute->GetItemCount();	
	int nRow = m_pListDailyDistribute->InsertItem(nHeadNum, strTemp);//插入行

	strTemp.Format("%d", struConfDailyInfo.dwID);
    m_pListDailyDistribute->SetItemText(nRow, 1, strTemp);//设置数据
	
	strTemp.Format("%d", struConfDailyInfo.dwDay);
    m_pListDailyDistribute->SetItemText(nRow, 2, strTemp);//设置数据

	if (struConfDailyInfo.bConf)
	{
		strTemp = _T("是");
	}
	else
	{
		strTemp = _T("否");
	}
    m_pListDailyDistribute->SetItemText(nRow, 3, strTemp);//设置数据
	
}
