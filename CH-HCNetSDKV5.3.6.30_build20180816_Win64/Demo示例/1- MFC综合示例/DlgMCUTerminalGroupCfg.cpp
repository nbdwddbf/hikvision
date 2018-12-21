// DlgMCUTerminalGroupCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUTerminalGroupCfg.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CSTRING_TO_CHARS(str,sz) memcpy((sz),str.GetBuffer(str.GetLength()),str.GetLength())

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUTerminalGroupCfg dialog


CDlgMCUTerminalGroupCfg::CDlgMCUTerminalGroupCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUTerminalGroupCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMCUTerminalGroupCfg)
		// NOTE: the ClassWizard will add member initialization here
	//for (int i = 0; i < MAX_GROUP_COUNT; i++)
	//{
	//	memset(&m_TermGroupInfoList[i], 0, sizeof(TermGroupInfo));
	//}

	memset(&m_struTermGroupInfo, 0, sizeof(m_struTermGroupInfo));
	
	//m_dwGroupNum = 0;

	m_bEnable  = FALSE;



	//}}AFX_DATA_INIT
}


void CDlgMCUTerminalGroupCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMCUTerminalGroupCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Check(pDX, IDC_CHK_ENABLE,     m_bEnable);

	DDX_Text(pDX, IDC_EDT_TERM_NO,  m_csTermNO);
	DDX_Text(pDX, IDC_EDT_GROUP_ID,  m_csGroupID);
	DDX_Text(pDX, IDC_EDT_GROUP_NAME, m_strGroupName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMCUTerminalGroupCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUTerminalGroupCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_CFG, OnBtnCfg)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_ADD_TERM, OnBtnAddTerm)
	//ON_NOTIFY(NM_CLICK, IDC_LST_GROUP_INFO, OnClickLstGroupInfo)
	ON_BN_CLICKED(IDC_RAD_GET, OnRadGet)
	ON_BN_CLICKED(IDC_RAD_CFG, OnRadCfg)
	ON_BN_CLICKED(IDC_RAD_ADD, OnRadAdd)
	ON_BN_CLICKED(IDC_RAD_DEL, OnRadDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUTerminalGroupCfg message handlers



BOOL CDlgMCUTerminalGroupCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_szRequestURL = new char[REQUEST_URL_LEN];  
    if (m_szRequestURL == NULL)
    {
        return FALSE;
    }
    
    memset(m_szRequestURL, '\0' , REQUEST_URL_LEN);
    
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
	
	//m_pListGroupInfo = (CListCtrl*)GetDlgItem(IDC_LST_GROUP_INFO);
    m_pListTermInfo  = (CListCtrl*)GetDlgItem(IDC_LST_TERM_INFO);
	
	LONG lStyle;
    lStyle = GetWindowLong(m_pListTermInfo->m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT;    //设置style
    //SetWindowLong(m_pListGroupInfo->m_hWnd, GWL_STYLE, lStyle);//设置style
	SetWindowLong(m_pListTermInfo->m_hWnd, GWL_STYLE, lStyle);//设置style
    
    DWORD dwStyle = m_pListTermInfo->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;    //网格线（只适用与report风格的listctrl）
    //dwStyle |= LVS_EX_CHECKBOXES;   //item前生成checkbox控件
    //m_pListGroupInfo->SetExtendedStyle(dwStyle); //设置扩展风格
	m_pListTermInfo->SetExtendedStyle(dwStyle); //设置扩展风格
	
	//m_pListGroupInfo->InsertColumn(0, "Index", LVCFMT_LEFT, 50);//插入列
	//m_pListGroupInfo->InsertColumn(1, "ID", LVCFMT_LEFT, 80);
    //m_pListGroupInfo->InsertColumn(2, "使能", LVCFMT_LEFT, 50);
	//m_pListGroupInfo->InsertColumn(3, "分组名称", LVCFMT_LEFT, 105);
	//m_pListGroupInfo->InsertColumn(4, "终端数目", LVCFMT_LEFT, 80);
	
	m_pListTermInfo->InsertColumn(0, "Index", LVCFMT_LEFT, 50);//插入列
    m_pListTermInfo->InsertColumn(1, "终端号", LVCFMT_LEFT, 250);

	((CButton*)GetDlgItem(IDC_RAD_GET))->SetCheck(TRUE);

	OnRadGet();
	
	UpdateData(FALSE);
	
	return TRUE;
}



void CDlgMCUTerminalGroupCfg::OnBtnAddTerm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);


    CSTRING_TO_CHARS(m_csTermNO, m_struTermGroupInfo.TermNOList[m_struTermGroupInfo.dwTermNum]);

	InsertTermInfo(m_struTermGroupInfo.dwTermNum+1, m_struTermGroupInfo.TermNOList[m_struTermGroupInfo.dwTermNum]);

    m_struTermGroupInfo.dwTermNum++;

	UpdateData(FALSE);
		
}


void CDlgMCUTerminalGroupCfg::OnBtnCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
	memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));
    
	//TerminalGroup

	//memset(&m_TermGroupInfo, 0, sizeof(m_TermGroupInfo));

    CSTRING_TO_CHARS(m_csGroupID, m_struTermGroupInfo.szID);
	m_struTermGroupInfo.bEnabled = m_bEnable;
	CSTRING_TO_CHARS(m_strGroupName, m_struTermGroupInfo.szGroupName);

	CXmlBase struXmlParam;

	struXmlParam.CreateRoot("TerminalGroup");
	struXmlParam.SetAttribute("version", "2.0");
	struXmlParam.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

	ConvertSingleNodeData((char*)&m_struTermGroupInfo.szID, struXmlParam, "id", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData(&m_struTermGroupInfo.bEnabled, struXmlParam, "enabled", NODE_BOOL_TO_STRING);
	ConvertSingleNodeData((char*)&m_struTermGroupInfo.szGroupName, struXmlParam, "groupName", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData(&m_struTermGroupInfo.dwTermNum, struXmlParam, "terminalNum", NODE_INT_TO_STRING);

	if (struXmlParam.AddNode("terminalNoList"))
	{
		for (int i = 0; i < (int)m_struTermGroupInfo.dwTermNum; i++)
		{
			ConvertSingleNodeData((char*)&m_struTermGroupInfo.TermNOList[i], struXmlParam, "terminalNo", NODE_ARRAY_TO_STRING);
		}
		struXmlParam.OutOfElem();
	}
	

	//将XML转存到buffer中
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	if (!PrintXmlToNewBuffer(&m_pXMLParamBuf, m_dwXMLParamBufLen, struXmlParam))
	{
		//g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PrintXmlToNewBuffer Error");
		return;
	}

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "PUT /ISAPI/VCS/terminalGroups/%s", m_struTermGroupInfo.szID);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = m_pXMLParamBuf;
	struXMLCfgInput.dwInBufferSize  = m_dwXMLParamBufLen;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer     = NULL;
	struXMLCfgOutput.dwOutBufferSize = 0;
	struXMLCfgOutput.lpStatusBuffer  = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize    = ISAPI_STATUS_LEN;

	LPNET_DVR_XML_CONFIG_OUTPUT lpXMLCfgOutput = &struXMLCfgOutput;
	
	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, lpXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
    }
	
	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);

	delete[] m_pXMLParamBuf;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;

	UpdateData(FALSE);
	
}

//终端分组获取
void CDlgMCUTerminalGroupCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

    m_pListTermInfo->DeleteAllItems();
    memset(&m_struTermGroupInfo, 0, sizeof(m_struTermGroupInfo));

    CSTRING_TO_CHARS(m_csGroupID, m_struTermGroupInfo.szID);

	memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
	memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));
    
	//lpInputParam->lpRequestUrl为：GET /ISAPI/VCS/terminalGroups/<ID>；
	//lpInputParam->lpInBuffer为NULL；
	//lpOutputParam->lpOutBuffer为TerminalGroup；
	//lpOutputParam->lpStatusBuffer为ResponseStatus，获取成功时不返回。

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "GET /ISAPI/VCS/terminalGroups/%s", m_struTermGroupInfo.szID);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer = NULL;
	struXMLCfgInput.dwInBufferSize = 0;
	
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
		return;
    }
	
	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);

	CXmlBase struXmlResult;
	
	if (struXmlResult.Parse((char*)struXMLCfgOutput.lpOutBuffer))
	{
			if (struXmlResult.FindElem("TerminalGroup") && struXmlResult.IntoElem())
			{
				if (struXmlResult.FindElem("id"))
				{
					ConvertSingleNodeData((char*)&m_struTermGroupInfo.TermNOList, struXmlResult, "id", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				}

				if (struXmlResult.FindElem("enabled"))
				{
					ConvertSingleNodeData(&m_struTermGroupInfo.bEnabled, struXmlResult, "enabled", NODE_STRING_TO_BOOL);
				}

				if (struXmlResult.FindElem("groupName"))
				{
					ConvertSingleNodeData((char*)&m_struTermGroupInfo.szGroupName, struXmlResult, "groupName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				}

				if (struXmlResult.FindElem("terminalNum"))
				{
					ConvertSingleNodeData(&m_struTermGroupInfo.dwTermNum, struXmlResult, "terminalNum", NODE_STRING_TO_INT);
				}

				if (struXmlResult.FindElem("terminalNoList") && struXmlResult.IntoElem())
				{
					m_struTermGroupInfo.dwTermNum = 0;

                    do 
                    {

					    if(struXmlResult.FindElem("terminalNo"))
					    {
						    ConvertSingleNodeData(&(m_struTermGroupInfo.TermNOList[m_struTermGroupInfo.dwTermNum]), struXmlResult, "terminalNo", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);

						    InsertTermInfo(m_struTermGroupInfo.dwTermNum+1, m_struTermGroupInfo.TermNOList[m_struTermGroupInfo.dwTermNum]);

						    m_struTermGroupInfo.dwTermNum++;
					    }
					    
                    } while (struXmlResult.NextSibElem());

                    struXmlResult.OutOfElem();
				}

				//InsertGroupInfo(struTermGroupInfo);

				m_csGroupID = m_struTermGroupInfo.szID;
				m_strGroupName = m_struTermGroupInfo.szGroupName;
				m_bEnable = m_struTermGroupInfo.bEnabled;

				struXmlResult.OutOfElem();
			}// end if (struXmlResult.FindElem("TerminalGroup") && struXmlResult.IntoElem())

	}//if (struXmlResult.Parse((char*)struXMLCfgOutput.lpOutBuffer))
	
	UpdateData(FALSE);
}

void CDlgMCUTerminalGroupCfg::OnBtnAdd()
{
	UpdateData(TRUE);

	memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
	memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));
    
	//TerminalGroup

	//memset(&m_TermGroupInfo, 0, sizeof(m_TermGroupInfo));

    CSTRING_TO_CHARS(m_csGroupID, m_struTermGroupInfo.szID);
	m_struTermGroupInfo.bEnabled = m_bEnable;
	CSTRING_TO_CHARS(m_strGroupName, m_struTermGroupInfo.szGroupName);

	CXmlBase struXmlParam;

	struXmlParam.CreateRoot("TerminalGroup");
	struXmlParam.SetAttribute("version", "2.0");
	struXmlParam.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

	ConvertSingleNodeData((char*)&m_struTermGroupInfo.szID, struXmlParam, "id", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData(&m_struTermGroupInfo.bEnabled, struXmlParam, "enabled", NODE_BOOL_TO_STRING);
	ConvertSingleNodeData((char*)&m_struTermGroupInfo.szGroupName, struXmlParam, "groupName", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData(&m_struTermGroupInfo.dwTermNum, struXmlParam, "terminalNum", NODE_INT_TO_STRING);

	if (struXmlParam.AddNode("terminalNoList"))
	{
		for (int i = 0; i < (int)m_struTermGroupInfo.dwTermNum; i++)
		{
			ConvertSingleNodeData((char*)&m_struTermGroupInfo.TermNOList[i], struXmlParam, "terminalNo", NODE_ARRAY_TO_STRING);
		}
		struXmlParam.OutOfElem();
	}

	//将XML转存到buffer中
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	if (!PrintXmlToNewBuffer(&m_pXMLParamBuf, m_dwXMLParamBufLen, struXmlParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PrintXmlToNewBuffer");
		return;
	}
	
	//Debug
	CString strMsg = m_pXMLParamBuf;
	MessageBox(strMsg);

	//lpInputParam->lpRequestUrl为：POST /ISAPI/VCS/terminalGroups；
	//lpInputParam->lpInBuffer为TerminalGroup；
	//lpOutputParam->lpOutBuffer为NULL；
	//lpOutputParam->lpStatusBuffer为ResponseStatus。

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "POST /ISAPI/VCS/terminalGroups");
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = m_pXMLParamBuf;
	struXMLCfgInput.dwInBufferSize  = m_dwXMLParamBufLen;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = NULL;
	struXMLCfgOutput.dwOutBufferSize = 0;
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
    }

	//状态处理
	m_csGroupID = ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);
	
	delete[] m_pXMLParamBuf;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	
	UpdateData(FALSE);

}


void CDlgMCUTerminalGroupCfg::OnBtnDel()
{
	UpdateData(TRUE);

    CSTRING_TO_CHARS(m_csGroupID, m_struTermGroupInfo.szID);



	memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
	memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));
    
	//lpInputParam->lpRequestUrl为：DELETE /ISAPI/VCS/terminalGroups/<ID>；
	//lpInputParam->lpInBuffer为NULL；
	//lpOutputParam->lpOutBuffer为NULL；
	//lpOutputParam->lpStatusBuffer为ResponseStatus。

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "DELETE /ISAPI/VCS/terminalGroups/%s", m_struTermGroupInfo.szID);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = NULL;
	struXMLCfgInput.dwInBufferSize  = 0;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = NULL;
	struXMLCfgOutput.dwOutBufferSize = 0;
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
    }

	//状态处理
	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);

	m_csGroupID = _T("");

	UpdateData(FALSE);

}

void CDlgMCUTerminalGroupCfg::InsertTermInfo(DWORD dwTermNumTmp, char* TermNo)
{
	CString strTemp;

	strTemp.Format("%d", dwTermNumTmp);
	int nHeadNum = m_pListTermInfo->GetItemCount();	
	int nRow = m_pListTermInfo->InsertItem(nHeadNum, strTemp);//插入行&设置Index
	
	strTemp = TermNo;
    m_pListTermInfo->SetItemText(nRow, 1, strTemp);//设置终端号
}

void CDlgMCUTerminalGroupCfg::OnRadGet()
{
	//GetDlgItem(IDC_LST_GROUP_INFO)->EnableWindow(TRUE);
	GetDlgItem(IDC_LST_TERM_INFO)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDT_TERM_NO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD_TERM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_GROUP_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_GROUP_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHK_ENABLE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BTN_GET)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CFG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

    m_pListTermInfo->DeleteAllItems();
    memset(&m_struTermGroupInfo, 0, sizeof(m_struTermGroupInfo));
}

void CDlgMCUTerminalGroupCfg::OnRadCfg()
{
	//GetDlgItem(IDC_LST_GROUP_INFO)->EnableWindow(TRUE);
	GetDlgItem(IDC_LST_TERM_INFO)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_EDT_TERM_NO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_ADD_TERM)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_GROUP_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_GROUP_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHK_ENABLE)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CFG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
}

void CDlgMCUTerminalGroupCfg::OnRadAdd()
{
	//GetDlgItem(IDC_LST_GROUP_INFO)->EnableWindow(FALSE);
	GetDlgItem(IDC_LST_TERM_INFO)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_EDT_TERM_NO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_ADD_TERM)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_GROUP_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_GROUP_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHK_ENABLE)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CFG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);

    m_pListTermInfo->DeleteAllItems();
    memset(&m_struTermGroupInfo, 0, sizeof(m_struTermGroupInfo));
}

void CDlgMCUTerminalGroupCfg::OnRadDel()
{
	//GetDlgItem(IDC_LST_GROUP_INFO)->EnableWindow(FALSE);
	GetDlgItem(IDC_LST_TERM_INFO)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_EDT_TERM_NO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD_TERM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_GROUP_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_GROUP_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHK_ENABLE)->EnableWindow(FALSE);

    m_pListTermInfo->DeleteAllItems();
    memset(&m_struTermGroupInfo, 0, sizeof(m_struTermGroupInfo));
	
	GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CFG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

CString CDlgMCUTerminalGroupCfg::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
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

