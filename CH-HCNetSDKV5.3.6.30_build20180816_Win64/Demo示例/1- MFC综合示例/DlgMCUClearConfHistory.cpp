// DlgMCUClearConfHistory.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUClearConfHistory.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUClearConfHistory dialog


CDlgMCUClearConfHistory::CDlgMCUClearConfHistory(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUClearConfHistory::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMCUClearConfHistory)
		// NOTE: the ClassWizard will add member initialization here

	memset((char*)&m_szRequestURL, 0, sizeof(m_szRequestURL));
	memset((char*)&m_szXMLStatus, 0, sizeof(m_szXMLStatus));
	//}}AFX_DATA_INIT
}


void CDlgMCUClearConfHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMCUClearConfHistory)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMCUClearConfHistory, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUClearConfHistory)
		// NOTE: the ClassWizard will add message map macros here
		ON_BN_CLICKED(IDC_BTN_CLEAR_HISTORY, OnBtnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUClearConfHistory message handlers

BOOL CDlgMCUClearConfHistory::OnInitDialog()
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

    return TRUE;

}


void CDlgMCUClearConfHistory::OnBtnClear()
{
    memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
    memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
    m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));

	//lpInputParam->lpRequestUrl为：PUT /ISAPI/VCS/historyClear；
	//lpInputParam->lpInBuffer为NULL；
	//lpOutputParam->lpOutBuffer为NULL；
	//lpOutputParam->lpStatusBuffer为ResponseStatus。

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "PUT /ISAPI/VCS/historyClear");
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer = NULL;
	struXMLCfgInput.dwInBufferSize = 0;
	
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

	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);
	
}

CString CDlgMCUClearConfHistory::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
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
