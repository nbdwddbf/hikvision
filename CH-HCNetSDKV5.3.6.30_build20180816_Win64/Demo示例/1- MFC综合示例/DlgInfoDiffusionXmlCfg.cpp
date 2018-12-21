// DlgInfoDiffusionXmlCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionXmlCfg.h"
#include "DlgInfoGerenal.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionXmlCfg dialog


CDlgInfoDiffusionXmlCfg::CDlgInfoDiffusionXmlCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionXmlCfg::IDD, pParent)
    , m_binputFileData(FALSE)
    , m_strFilePath(_T(""))
    , m_dwRecvTimeOut(5000)
    , m_bChanConvert(FALSE)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionXmlCfg)
	m_szCommandStr = _T("");
	m_szInputParam = _T("");
	m_szOutputParam = _T("");
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	memset(m_szCommandBuf, 0, sizeof(m_szCommandBuf));
	m_lpOutputXml = new char[MAX_LEN_XML];
	memset(m_lpOutputXml, 0, MAX_LEN_XML);
}


void CDlgInfoDiffusionXmlCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInfoDiffusionXmlCfg)
    DDX_Control(pDX, IDC_COMBO_OPERATE_TYPE, m_cmbOperateType);
    DDX_Text(pDX, IDC_EDIT_COMMAND, m_szCommandStr);
    DDX_Text(pDX, IDC_EDIT_PARAM_INPUT, m_szInputParam);
    DDX_Text(pDX, IDC_EDIT_PARAM_OUTPUT, m_szOutputParam);
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHECK1, m_binputFileData);
    DDX_Text(pDX, IDC_EDT_FILE_PATH, m_strFilePath);
    DDX_Text(pDX, IDC_EDIT_RECV_TIME_OUT, m_dwRecvTimeOut);
    DDV_MinMaxUInt(pDX, m_dwRecvTimeOut, 0, ULONG_MAX);
    DDX_Check(pDX, IDC_CHECK_CHAN_CONVERT, m_bChanConvert);
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionXmlCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionXmlCfg)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_SELECT_FILE, &CDlgInfoDiffusionXmlCfg::OnBnClickedBtnSelectFile)
    ON_BN_CLICKED(IDC_BUTTON_TEST_MIME, &CDlgInfoDiffusionXmlCfg::OnBnClickedButtonTestMime)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionXmlCfg message handlers

void CDlgInfoDiffusionXmlCfg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionXmlCfg::OnBtnGet() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    BYTE *m_pPicInfo = NULL;
    char szLan[128] = { 0 };
    string utf_8;
    NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
    struInputParam.dwSize = sizeof(struInputParam);
    int nSel = m_cmbOperateType.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    CString szCommand = _T("");
    m_cmbOperateType.GetLBText(nSel, szCommand);
    
    szCommand = szCommand + _T(" ") + m_szCommandStr;
    memset(m_szCommandBuf, 0, sizeof(m_szCommandBuf));
    sprintf(m_szCommandBuf, "%s", szCommand);
    struInputParam.lpRequestUrl = m_szCommandBuf;
    struInputParam.dwRequestUrlLen = strlen(m_szCommandBuf);
    struInputParam.dwRecvTimeOut = m_dwRecvTimeOut;
    
    char szStatusBuff[1024] = {0};
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
    struOutputParam.dwSize = sizeof(struOutputParam);

    if (m_binputFileData)
    {
        CFile cPicFile;
        if (!cPicFile.Open(m_strFilePath, CFile::modeRead))
        {
            g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
            AfxMessageBox(szLan);
        }
        else
        {
            struInputParam.dwInBufferSize = (DWORD)cPicFile.GetLength();
            if (struInputParam.dwInBufferSize == 0)
            {
                g_StringLanType(szLan, "Pic文件为空", "Pic file is empty");
                AfxMessageBox(szLan);
            }

            m_pPicInfo = new BYTE[struInputParam.dwInBufferSize];
            cPicFile.Read(m_pPicInfo, struInputParam.dwInBufferSize);
            struInputParam.lpInBuffer = m_pPicInfo;

            cPicFile.Close();
        }

    }
    else
    {
        struInputParam.dwInBufferSize = m_szInputParam.GetLength();
        if (struInputParam.dwInBufferSize != 0)
        {
            utf_8 = GB2UTF(m_szInputParam.GetBuffer(0));
            struInputParam.lpInBuffer = (void*)utf_8.c_str();
            struInputParam.dwInBufferSize = utf_8.length();
        }

    }

    memset(m_lpOutputXml, 0, MAX_LEN_XML);
    struOutputParam.lpOutBuffer = m_lpOutputXml;
    struOutputParam.dwOutBufferSize = MAX_LEN_XML;
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);
    //启用对xml内容中的通道号节点进行转换，则调用V50接口：NET_DVR_STDXMLConfig_Conv
    if (m_bChanConvert)
    {
        if (!NET_DVR_STDXMLConfig_Conv(m_lUserID, &struInputParam, &struOutputParam))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfigV50");
            return;
        }
    }
    else
    {
        if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
            string str_gb2312 = UTF2GB(szStatusBuff);
            m_szOutputParam = str_gb2312.c_str();
            UpdateData(FALSE);
            return;
        }
    }
    
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
    string str_gb2312 = UTF2GB(m_lpOutputXml);
    m_szOutputParam = str_gb2312.c_str();
    m_szOutputParam.Replace("\n", "\r\n");
    
	UpdateData(FALSE);
    if (NULL != m_pPicInfo)
    {
        delete[]m_pPicInfo;
        m_pPicInfo = NULL;
    }
}

void CDlgInfoDiffusionXmlCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	int nSel = m_cmbOperateType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString szCommand = _T("");
	m_cmbOperateType.GetLBText(nSel, szCommand);
	if (0 == strcmp(szCommand, _T("GET")))
	{
		return;
	}
	else if (strcmp(szCommand, _T("DELETE")))
	{
		struInputParam.lpInBuffer = m_szInputParam.GetBuffer(0);
		struInputParam.dwInBufferSize = m_szInputParam.GetLength();
	}
	szCommand = szCommand + _T(" ") + m_szCommandStr + _T("\r\n");
	memset(m_szCommandBuf, 0, sizeof(m_szCommandBuf));
	sprintf(m_szCommandBuf, "%s", szCommand);
	struInputParam.lpRequestUrl = m_szCommandBuf;
	struInputParam.dwRequestUrlLen = strlen(m_szCommandBuf);
    struInputParam.dwRecvTimeOut = m_dwRecvTimeOut;
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
    SYSTEMTIME struTime1 = { 0 };
    SYSTEMTIME struTime2 = { 0 };
    ::GetSystemTime(&struTime1);
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
    ::GetSystemTime(&struTime2);
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig, timeDiff[%d:%d]", (struTime2.wSecond-struTime1.wSecond),
        (struTime2.wMilliseconds-struTime1.wMilliseconds));
	
	UpdateData(FALSE);
}

BOOL CDlgInfoDiffusionXmlCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbOperateType.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgInfoDiffusionXmlCfg::OnBnClickedBtnSelectFile()
{
    UpdateData(TRUE);

    char szLan[1024] = { 0 };
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFilePath = dlg.GetPathName();
        SetDlgItemText(IDC_EDT_FILE_PATH, m_strFilePath);
    }
}


void CDlgInfoDiffusionXmlCfg::OnBnClickedButtonTestMime()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    int nSel = m_cmbOperateType.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    CString szCommand = _T("");
    m_cmbOperateType.GetLBText(nSel, szCommand);
    if (strcmp(szCommand, _T("PUT")) && strcmp(szCommand, _T("POST")))
    {
        return;
    }
    else if (strcmp(szCommand, _T("DELETE")))
    {
        NET_DVR_MIME_UNIT struUnit[2] = { 0 };
        if (m_binputFileData)
        {
            char szLan[128] = { 0 };
            CFile cPicFile;
            if (!cPicFile.Open(m_strFilePath, CFile::modeRead))
            {
                g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
                AfxMessageBox(szLan);
            }
            else
            {
                cPicFile.Close();
                struUnit[0].pContent = NULL;
                struUnit[0].dwContentLen = 0;
                struUnit[0].bySelfRead = 1;
                //memcpy(struUnit[0].szContentType, _T("image/jpeg"), strlen(_T("application/octet-stream""image/jpeg")));
                memcpy(struUnit[0].szContentType, _T("application/octet-stream"), strlen(_T("application/octet-stream")));
                memcpy(struUnit[0].szName, _T("updateFile"), strlen(_T("updateFile")));
                memcpy(struUnit[0].szFilename, m_strFilePath, m_strFilePath.GetLength());
                struInputParam.lpInBuffer = (void*)struUnit;
                struInputParam.dwInBufferSize = 1 * sizeof(NET_DVR_MIME_UNIT);
                struInputParam.byNumOfMultiPart = 1;
            }
        }
        else
        {
            struUnit[0].pContent = m_szInputParam.GetBuffer(0);
            struUnit[0].dwContentLen = m_szInputParam.GetLength();

            if (strcmp(szCommand, _T("{")))
            {
                memcpy(struUnit[0].szContentType, _T("text/json"), strlen(_T("text/json")));
            }
            else
            {
                memcpy(struUnit[0].szContentType, _T("text/xml"), strlen(_T("text/xml")));
            }

            memcpy(struUnit[0].szName, _T("test"), strlen(_T("test")));
            memcpy(struUnit[0].szFilename, _T("\\test.bat"), strlen(_T("\\test.bat")));


            struUnit[1].pContent = NULL;
            struUnit[1].dwContentLen = 0;
            struUnit[1].bySelfRead = 1;
            memcpy(struUnit[1].szContentType, _T("image/jpeg"), strlen(_T("image/jpeg")));
            memcpy(struUnit[1].szName, _T("test"), strlen(_T("test")));
            memcpy(struUnit[1].szFilename, m_strFilePath, m_strFilePath.GetLength());
            struInputParam.lpInBuffer = (void*)struUnit;
            struInputParam.dwInBufferSize = 2 * sizeof(NET_DVR_MIME_UNIT);
            struInputParam.byNumOfMultiPart = 2;
        }


        //struUnit[2].pContent = _T("a@@#$%^&*()_.............1234...^&*()");
        //struUnit[2].dwContentLen = strlen(_T("a@@#$%^&*()_.............1234...^&*()"));
        //memcpy(struUnit[2].szContentType, _T("image/jpeg"), strlen(_T("image/jpeg")));
        //memcpy(struUnit[2].szName, _T("test2"), strlen(_T("test2")));
        //memcpy(struUnit[2].szFilename, _T("C:\\test\\test2.jpg"), strlen(_T("C:\\test\\test2.jpg")));
    }
    szCommand = szCommand + _T(" ") + m_szCommandStr + _T("\r\n");
    memset(m_szCommandBuf, 0, sizeof(m_szCommandBuf));
    sprintf(m_szCommandBuf, "%s", szCommand);
    struInputParam.lpRequestUrl = m_szCommandBuf;
    struInputParam.dwRequestUrlLen = strlen(m_szCommandBuf);
    struInputParam.dwRecvTimeOut = m_dwRecvTimeOut;


    char szStatusBuff[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpOutBuffer = m_lpOutputXml;
    struOutputParam.dwOutBufferSize = MAX_LEN_XML;
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        string str_gb2312 = UTF2GB(szStatusBuff);
        m_szOutputParam = str_gb2312.c_str();
        UpdateData(FALSE);
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    string str_gb2312 = UTF2GB(m_lpOutputXml);
    m_szOutputParam = str_gb2312.c_str();

    UpdateData(FALSE);
}
