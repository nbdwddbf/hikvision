// DlgWorkingClass.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgWorkingClass.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgWorkingClass 对话框

IMPLEMENT_DYNAMIC(CDlgWorkingClass, CDialog)

CDlgWorkingClass::CDlgWorkingClass(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWorkingClass::IDD, pParent)
{
    m_iWorkingClassID = 0;
    m_csClassName = _T("");
    m_iWorkingTime = 0;
    m_csOnDutyDelay = _T("");
    memset(m_dwTimeID, 0, 4 * sizeof(DWORD));
    for (int i = 0; i < 4; i++)
    {
        m_csStartRestTime[i] = _T("");
    }
    for (int i = 0; i < 4; i++)
    {
        m_csEndRestTime[i] = _T("");
    }
}

CDlgWorkingClass::~CDlgWorkingClass()
{
}

void CDlgWorkingClass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_WORKING_CLASS_ID, m_iWorkingClassID);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_cmbEnable);
    DDX_Text(pDX, IDC_EDIT_CLASS_NAME, m_csClassName);
    DDX_Text(pDX, IDC_EDIT_WORKING_TIME, m_iWorkingTime);
    DDX_Control(pDX, IDC_COMBO_DELAY_ENABLE, m_cmbDelayEnable);
    DDX_Text(pDX, IDC_EDIT_ON_DUTY_DELAY_TIME, m_csOnDutyDelay);
    DDX_Text(pDX, IDC_EDIT_REST_TIME_ID1, m_dwTimeID[0]);
    DDX_Text(pDX, IDC_EDIT_REST_TIME_ID2, m_dwTimeID[1]);
    DDX_Text(pDX, IDC_EDIT_REST_TIME_ID3, m_dwTimeID[2]);
    DDX_Text(pDX, IDC_EDIT_REST_TIME_ID4, m_dwTimeID[3]);
    DDX_Text(pDX, IDC_EDIT_START_REST_TIME1, m_csStartRestTime[0]);
    DDX_Text(pDX, IDC_EDIT_START_REST_TIME2, m_csStartRestTime[1]);
    DDX_Text(pDX, IDC_EDIT_START_REST_TIME3, m_csStartRestTime[2]);
    DDX_Text(pDX, IDC_EDIT_START_REST_TIME4, m_csStartRestTime[3]);
    DDX_Text(pDX, IDC_EDIT_END_REST_TIME1, m_csEndRestTime[0]);
    DDX_Text(pDX, IDC_EDIT_END_REST_TIME2, m_csEndRestTime[1]);
    DDX_Text(pDX, IDC_EDIT_END_REST_TIME3, m_csEndRestTime[2]);
    DDX_Text(pDX, IDC_EDIT_END_REST_TIME4, m_csEndRestTime[3]);
}

BOOL CDlgWorkingClass::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbEnable.SetCurSel(0);
    m_cmbDelayEnable.SetCurSel(0);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgWorkingClass, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_WORKING_CLASS, &CDlgWorkingClass::OnBnClickedBtnGetWorkingClass)
    ON_BN_CLICKED(IDC_BTN_SET_WORKING_CLASS, &CDlgWorkingClass::OnBnClickedBtnSetWorkingClass)
END_MESSAGE_MAP()


// CDlgWorkingClass 消息处理程序


void CDlgWorkingClass::OnBnClickedBtnGetWorkingClass()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_csClassName = _T("");
    m_iWorkingTime = 0;
    m_csOnDutyDelay = _T("");
    memset(m_dwTimeID, 0, 4 * sizeof(DWORD));
    for (int i = 0; i < 4; i++)
    {
        m_csStartRestTime[i] = _T("");
    }
    for (int i = 0; i < 4; i++)
    {
        m_csEndRestTime[i] = _T("");
    }
    m_cmbEnable.SetCurSel(0);
    m_cmbDelayEnable.SetCurSel(0);

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/AccessControl/WorkingClass/WorkingClassNo/%d", m_iWorkingClassID);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, szUrl);
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szUrl);

    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("WorkingClass") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("enabled"))
        {
            if (xmlBase.GetData().compare("true") == 0)
            {
                m_cmbEnable.SetCurSel(1);
            }
            else
            {
                m_cmbEnable.SetCurSel(0);
            }
        }
        if (xmlBase.FindElem("className"))
        {
            m_csClassName = xmlBase.GetData().c_str();
        }
        if (xmlBase.FindElem("workingTimeMinutes"))
        {
            m_iWorkingTime = atoi(xmlBase.GetData().c_str());
        }
        if (xmlBase.FindElem("RestList") && xmlBase.IntoElem())
        {
            for (int i = 0; i < 3; i++)
            {
                if (xmlBase.FindElem("RestAction") && xmlBase.IntoElem())
                {
                    if (xmlBase.FindElem("timeID"))
                    {
                        m_dwTimeID[i] = atoi(xmlBase.GetData().c_str());
                    }
                    if (xmlBase.FindElem("startRestTime"))
                    {
                        m_csStartRestTime[i] = xmlBase.GetData().c_str();
                    }
                    if (xmlBase.FindElem("endRestTime"))
                    {
                        m_csEndRestTime[i] = xmlBase.GetData().c_str();
                    }
                }
                xmlBase.OutOfElem();
                if (!xmlBase.NextSibElem())
                {
                    break;
                }
            }
        }
        xmlBase.OutOfElem();
        if (xmlBase.FindElem("onDutyDelayEnabled"))
        {
            if (xmlBase.GetData().compare("true") == 0)
            {
                m_cmbDelayEnable.SetCurSel(1);
            }
            else
            {
                m_cmbDelayEnable.SetCurSel(0);
            }
        }
        if (xmlBase.FindElem("onDutyDelayTime"))
        {
            m_csOnDutyDelay = xmlBase.GetData().c_str();
        }
    }

    delete[]pOutBuf;
    pOutBuf = NULL;

    UpdateData(FALSE);
}


void CDlgWorkingClass::OnBnClickedBtnSetWorkingClass()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateWorkingClassXml(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/AccessControl/WorkingClass/WorkingClassNo/%d", m_iWorkingClassID);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    struOuput.dwSize = sizeof(struOuput);
    if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szUrl);
    }

    delete[]pBuf;
    pBuf = NULL;

    UpdateData(TRUE);
}

BOOL CDlgWorkingClass::CreateWorkingClassXml(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("WorkingClass");
    xmlBase.SetAttribute("version", "2.0");

    if (m_cmbEnable.GetCurSel() == 0)
    {
        xmlBase.AddNode("enabled", "false");
    }
    else
    {
        xmlBase.AddNode("enabled", "true");
    }
    xmlBase.OutOfElem();
    xmlBase.AddNode("className", m_csClassName.GetBuffer(0));
    xmlBase.OutOfElem();
    char szWorkingTime[32] = { 0 };
    sprintf(szWorkingTime, "%d", m_iWorkingTime);
    xmlBase.AddNode("workingTimeMinutes", szWorkingTime);
    xmlBase.OutOfElem();
    xmlBase.AddNode("RestList");
    for (int i = 0; i < 3; i++)
    {
        xmlBase.AddNode("RestAction");

        char szTimeID[32] = { 0 };
        sprintf(szTimeID, "%d", m_dwTimeID[i]);
        xmlBase.AddNode("timeID", szTimeID);
        xmlBase.OutOfElem();
        xmlBase.AddNode("startRestTime", m_csStartRestTime[i].GetBuffer(0));
        xmlBase.OutOfElem();
        xmlBase.AddNode("endRestTime", m_csEndRestTime[i].GetBuffer(0));
        xmlBase.OutOfElem();
        
        xmlBase.OutOfElem();
    }
    xmlBase.OutOfElem();
    if (m_cmbDelayEnable.GetCurSel() == 0)
    {
        xmlBase.AddNode("onDutyDelayEnabled", "false");
    }
    else
    {
        xmlBase.AddNode("onDutyDelayEnabled", "true");
    }
    xmlBase.OutOfElem();
    xmlBase.AddNode("onDutyDelayTime", m_csOnDutyDelay.GetBuffer(0));
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}