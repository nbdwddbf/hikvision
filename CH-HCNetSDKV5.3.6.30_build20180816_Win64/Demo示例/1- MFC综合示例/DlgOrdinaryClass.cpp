// DlgOrdinaryClass.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgOrdinaryClass.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgOrdinaryClass 对话框

IMPLEMENT_DYNAMIC(CDlgOrdinaryClass, CDialog)

CDlgOrdinaryClass::CDlgOrdinaryClass(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOrdinaryClass::IDD, pParent)
{
    m_iOrdinaryClassNo = 0;
    m_csClassName = _T("");
    m_iAttendanceRuleNo = 0;
    memset(m_dwTimeID, 0, 4 * sizeof(DWORD));
    for (int i = 0; i < 4; i++)
    {
        m_csOnDutyTime[i] = _T("");
    }
    for (int i = 0; i < 4; i++)
    {
        m_csOffDutyTime[i] = _T("");
    }
}

CDlgOrdinaryClass::~CDlgOrdinaryClass()
{
}

void CDlgOrdinaryClass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_cmbEnable);
    DDX_Text(pDX, IDC_EDIT_ORDINARY_CLASS_ID, m_iOrdinaryClassNo);
    DDX_Text(pDX, IDC_EDIT_CLASS_NAME, m_csClassName);
    DDX_Text(pDX, IDC_EDIT_ATTENDANCE_RULE_NO, m_iAttendanceRuleNo);
    DDX_Text(pDX, IDC_EDIT_TIME_ID1, m_dwTimeID[0]);
    DDX_Text(pDX, IDC_EDIT_TIME_ID2, m_dwTimeID[1]);
    DDX_Text(pDX, IDC_EDIT_TIME_ID3, m_dwTimeID[2]);
    DDX_Text(pDX, IDC_EDIT_TIME_ID4, m_dwTimeID[3]);
    DDX_Text(pDX, IDC_EDIT_ON_DUTY_TIME1, m_csOnDutyTime[0]);
    DDX_Text(pDX, IDC_EDIT_ON_DUTY_TIME2, m_csOnDutyTime[1]);
    DDX_Text(pDX, IDC_EDIT_ON_DUTY_TIME3, m_csOnDutyTime[2]);
    DDX_Text(pDX, IDC_EDIT_ON_DUTY_TIME4, m_csOnDutyTime[3]);
    DDX_Text(pDX, IDC_EDIT_OFF_DUTY_TIME1, m_csOffDutyTime[0]);
    DDX_Text(pDX, IDC_EDIT_OFF_DUTY_TIME2, m_csOffDutyTime[1]);
    DDX_Text(pDX, IDC_EDIT_OFF_DUTY_TIME3, m_csOffDutyTime[2]);
    DDX_Text(pDX, IDC_EDIT_OFF_DUTY_TIME4, m_csOffDutyTime[3]);
}

BOOL CDlgOrdinaryClass::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbEnable.SetCurSel(0);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgOrdinaryClass, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_ORDINARY_CLASS, &CDlgOrdinaryClass::OnBnClickedBtnGetOrdinaryClass)
    ON_BN_CLICKED(IDC_BTN_SET_ORDINARY_CLASS, &CDlgOrdinaryClass::OnBnClickedBtnSetOrdinaryClass)
END_MESSAGE_MAP()


// CDlgOrdinaryClass 消息处理程序


void CDlgOrdinaryClass::OnBnClickedBtnGetOrdinaryClass()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_csClassName = _T("");
    m_iAttendanceRuleNo = 0;
    memset(m_dwTimeID, 0, 4 * sizeof(DWORD));
    for (int i = 0; i < 4; i++)
    {
        m_csOnDutyTime[i] = _T("");
    }
    for (int i = 0; i < 4; i++)
    {
        m_csOffDutyTime[i] = _T("");
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/AccessControl/OrdinaryClass/OrdinaryClassNo/%d", m_iOrdinaryClassNo);
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
    if (xmlBase.FindElem("OrdinaryClass") && xmlBase.IntoElem())
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
        if (xmlBase.FindElem("attendanceRuleNo"))
        {
            m_iAttendanceRuleNo = atoi(xmlBase.GetData().c_str());
        }
        if (xmlBase.FindElem("TimeList") && xmlBase.IntoElem())
        {
            for (int i = 0; i < 4; i++)
            {
                if (xmlBase.FindElem("TimeAction") && xmlBase.IntoElem())
                {
                    if (xmlBase.FindElem("timeID"))
                    {
                        m_dwTimeID[i] = atoi(xmlBase.GetData().c_str());
                    }
                    if (xmlBase.FindElem("onDutyTime"))
                    {
                        m_csOnDutyTime[i] = xmlBase.GetData().c_str();
                    }
                    if (xmlBase.FindElem("offDutyTime"))
                    {
                        m_csOffDutyTime[i] = xmlBase.GetData().c_str();
                    }
                }
                xmlBase.OutOfElem();
                if (!xmlBase.NextSibElem())
                {
                    break;
                }
            }
        }
    }

    delete[]pOutBuf;
    pOutBuf = NULL;

    UpdateData(FALSE);
}


void CDlgOrdinaryClass::OnBnClickedBtnSetOrdinaryClass()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateOrdianaryClassXml(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/AccessControl/OrdinaryClass/OrdinaryClassNo/%d", m_iOrdinaryClassNo);
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

BOOL CDlgOrdinaryClass::CreateOrdianaryClassXml(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("OrdinaryClass");
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
    char szAttendanceRuleNo[32] = { 0 };
    sprintf(szAttendanceRuleNo, "%d", m_iAttendanceRuleNo);
    xmlBase.AddNode("attendanceRuleNo", szAttendanceRuleNo);
    xmlBase.OutOfElem();
    xmlBase.AddNode("TimeList");
    for (int i = 0; i < 4; i++)
    {
        xmlBase.AddNode("TimeAction");

        char szTimeID[32] = { 0 };
        sprintf(szTimeID, "%d", m_dwTimeID[i]);
        xmlBase.AddNode("timeID", szTimeID);
        xmlBase.OutOfElem();
        xmlBase.AddNode("onDutyTime", m_csOnDutyTime[i].GetBuffer(0));
        xmlBase.OutOfElem();
        xmlBase.AddNode("offDutyTime", m_csOffDutyTime[i].GetBuffer(0));
        xmlBase.OutOfElem();

        xmlBase.OutOfElem();
    }
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}
