// DlgMCUTerminalCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUTerminalCtrl.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CSTRING_TO_CHARS(str,sz) memcpy((sz),str.GetBuffer(str.GetLength()),str.GetLength())


/////////////////////////////////////////////////////////////////////////////
// CDlgMCUTerminalCtrl dialog


CDlgMCUTerminalCtrl::CDlgMCUTerminalCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUTerminalCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMCUTerminalCtrl)
		// NOTE: the ClassWizard will add member initialization here
	
	m_bMute = FALSE;
	m_dwVolume = 0;
	m_bAudioInputDisabled = FALSE;
	m_dwAudioInputVolume = 0;

	memset(&m_szRequestURL, '\0' ,sizeof(m_szRequestURL));
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	memset(&m_szXMLStatus, '\0', sizeof(m_szXMLStatus));

	//}}AFX_DATA_INIT
}


void CDlgMCUTerminalCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMCUTerminalCtrl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_CHK_MUTE, m_btnMute);
    DDX_Control(pDX, IDC_CHK_AUDIO_INPUT_DISABLED, m_btnAudioInput);
	DDX_Control(pDX, IDC_EDT_VOLUME,  m_edtVolume);

	//DDX_Text(pDX, IDC_EDT_CONF_ID,         m_csConfID);
	//DDX_Text(pDX, IDC_EDT_TERM_ID,         m_csTermID);
    DDX_Control(pDX, IDC_COM_OPER_TYPE,  m_comOperType);

    DDX_Control(pDX, IDC_EDT_AUDIO_INPUT_VOLUME, m_edtAudioInputVol);

    

    DDX_Text(pDX, IDC_COM_OPER_TYPE, m_csOperType);
    DDX_Text(pDX, IDC_EDT_URL, m_csURL);

	DDX_Text(pDX, IDC_EDT_VOLUME,          m_dwVolume);
    DDX_Text(pDX, IDC_EDT_AUDIO_INPUT_VOLUME,   m_dwAudioInputVolume);

	DDX_Check(pDX, IDC_CHK_MUTE,               m_bMute);
	DDX_Check(pDX, IDC_CHK_AUDIO_INPUT_DISABLED,   m_bAudioInputDisabled);


	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMCUTerminalCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUTerminalCtrl)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_CHK_MUTE, OnChkMute)
    ON_BN_CLICKED(IDC_CHK_AUDIO_INPUT_DISABLED, OnChkAudioInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUTerminalCtrl message handlers


BOOL CDlgMCUTerminalCtrl::OnInitDialog()
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


    m_comOperType.InsertString(0, _T("answer"));
    m_comOperType.InsertString(1, _T("reject"));
    m_comOperType.InsertString(2, _T("call"));
    m_comOperType.InsertString(3, _T("adjustAudio"));
    m_comOperType.InsertString(4, _T("askStart"));
    m_comOperType.InsertString(5, _T("askStop"));
	m_comOperType.SetCurSel(0);
	
	UpdateData(TRUE);
	
	return TRUE;
}

void CDlgMCUTerminalCtrl::OnBtnOk() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

    char szURLSeg[] = "URL";

    char szOperType[MAX_XML_ELEM_LEN] = {0};
    char szURL[MAX_XML_ELEM_LEN] = {0};

    CSTRING_TO_CHARS(m_csOperType, szOperType);
    CSTRING_TO_CHARS(m_csURL, szURL);

    memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
    memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
    m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));

	//TerminalControlParam XML Block

	CXmlBase struXmlParam;
	struXmlParam.CreateRoot("ControlParam");
	struXmlParam.SetAttribute("version", "2.0");
	struXmlParam.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");
	
	ConvertSingleNodeData(&szOperType, struXmlParam, "operateType", NODE_ARRAY_TO_STRING);

    if (m_comOperType.GetCurSel() != 3)
    {
        if (strlen(szURL) != 0 && struXmlParam.AddNode("CallParam"))
        {
            ConvertSingleNodeData(&szURLSeg, struXmlParam, "addressType", NODE_ARRAY_TO_STRING);
            ConvertSingleNodeData(&szURL, struXmlParam, "URL", NODE_ARRAY_TO_STRING);
            struXmlParam.OutOfElem();
        }
    } 
    else
    {
        if (struXmlParam.AddNode("AudioParam"))
        {
            ConvertSingleNodeData(&m_bMute, struXmlParam, "mute", NODE_BOOL_TO_STRING);
            if (!m_bMute)
            {
                ConvertSingleNodeData(&m_dwVolume, struXmlParam, "volume", NODE_INT_TO_STRING);
            }
            
            ConvertSingleNodeData(&m_bAudioInputDisabled, struXmlParam, "audioInputDisabled", NODE_BOOL_TO_STRING);
            if (m_dwAudioInputVolume)
            {
                ConvertSingleNodeData(&m_dwAudioInputVolume, struXmlParam, "audioInputVolume", NODE_INT_TO_STRING);
            }
            
            struXmlParam.OutOfElem();
        }
    }
    
	
		//将XML转存到buffer中
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	if (!PrintXmlToNewBuffer(&m_pXMLParamBuf, m_dwXMLParamBufLen, struXmlParam))
	{
		//g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PrintXmlToNewBuffer Error");
		return;
	}
	
	//Debug
	CString strMsg = m_pXMLParamBuf;
	MessageBox(strMsg);


	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);

	sprintf((char*)m_szRequestURL, "PUT /ISAPI/VCS/terminals/control");
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
	
	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);
	
	delete[] m_pXMLParamBuf;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	UpdateData(TRUE);
}

CString CDlgMCUTerminalCtrl::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
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

void CDlgMCUTerminalCtrl::OnChkMute() 
{
	// TODO: Add your control notification handler code here

	if (m_btnMute.GetCheck())
    {
        m_edtVolume.EnableWindow(FALSE);
    }
    else
    {
        m_edtVolume.EnableWindow(TRUE);
    }		
}

void CDlgMCUTerminalCtrl::OnChkAudioInput() 
{
    // TODO: Add your control notification handler code here
    
    if (m_btnAudioInput.GetCheck())
    {
        m_edtAudioInputVol.EnableWindow(FALSE);
    }
    else
    {
        m_edtAudioInputVol.EnableWindow(TRUE);
    }		
}