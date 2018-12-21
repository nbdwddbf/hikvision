// DlgMCUConferenceCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUConferenceCtrl.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUConferenceCtrl dialog


#define CSTRING_TO_CHARS(str,sz) memcpy((sz),str.GetBuffer(str.GetLength()),str.GetLength())

CDlgMCUConferenceCtrl::CDlgMCUConferenceCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUConferenceCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMCUConferenceCtrl)
		// NOTE: the ClassWizard will add member initialization here

	//}}AFX_DATA_INIT
}


void CDlgMCUConferenceCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMCUConferenceCtrl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_COM_CTRL_CMD,  m_comCtrlCMD);


	DDX_Text(pDX, IDC_EDT_CONF_ID,   m_csConfID);
    DDX_Text(pDX, IDC_COM_CTRL_CMD,  m_strCtrlCMD);
    DDX_Text(pDX, IDC_EDT_REMIND_CONTENT,    m_strRemindContent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMCUConferenceCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUConferenceCtrl)
		// NOTE: the ClassWizard will add message map macros here
		ON_BN_CLICKED(IDC_BTN_OK, OnBtnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUConferenceCtrl message handlers


BOOL CDlgMCUConferenceCtrl::OnInitDialog()
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

	//"startConference,endConference,remind,reconnect"
	m_comCtrlCMD.InsertString(0, _T("startConference"));
	m_comCtrlCMD.InsertString(1, _T("endConference"));
	m_comCtrlCMD.InsertString(2, _T("remind"));
	m_comCtrlCMD.InsertString(3, _T("reconnect"));
	m_comCtrlCMD.SetCurSel(0);


	UpdateData(FALSE);

	return TRUE;
}

void CDlgMCUConferenceCtrl::OnBtnOK()
{
	UpdateData(TRUE);

    memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
    memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
    m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));

	//ConferenceControlParam

	char szConfID[MAX_XML_ELEM_LEN] = {0};
	char szCtrlCMD[MAX_XML_ELEM_LEN] = {0};
	char szRemindContent[MAX_XML_ELEM_LEN] = {0};

	CSTRING_TO_CHARS(m_csConfID, szConfID);
	CSTRING_TO_CHARS(m_strCtrlCMD, szCtrlCMD);
	CSTRING_TO_CHARS(m_strRemindContent, szRemindContent);

	
	CXmlBase struXmlParam;
	struXmlParam.CreateRoot("ConferenceControlParam");
	struXmlParam.SetAttribute("version", "2.0");
	struXmlParam.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

	ConvertSingleNodeData((char*)&szConfID, struXmlParam, "id", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData((char*)&szCtrlCMD, struXmlParam, "controlCmd", NODE_ARRAY_TO_STRING);

    if (strcmp(szCtrlCMD, "remind") == 0)
    {
	    ConvertSingleNodeData((char*)&szRemindContent, struXmlParam, "remindContent", NODE_ARRAY_TO_STRING);
    }

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

	//lpInputParam->lpRequestUrl为：PUT /ISAPI/VCS/conferenceControl/<ID>；
	//lpInputParam->lpInBuffer为ConferenceControlParam；
	//lpOutputParam->lpOutBuffer为NULL；
	//lpOutputParam->lpStatusBuffer为ResponseStatus。

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "PUT /ISAPI/VCS/conferenceControl/%s", szConfID);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = m_pXMLParamBuf;
	struXMLCfgInput.dwInBufferSize  = strlen(m_pXMLParamBuf);
	
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

	//DWORD dwError = NET_DVR_GetLastError();

	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);
	
	delete[] m_pXMLParamBuf;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;

	UpdateData(FALSE);

}

CString CDlgMCUConferenceCtrl::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
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
