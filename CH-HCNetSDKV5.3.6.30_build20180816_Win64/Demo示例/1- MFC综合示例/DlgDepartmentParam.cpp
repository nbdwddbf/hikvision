// DlgDepartmentParam.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgDepartmentParam.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgDepartmentParam 对话框

IMPLEMENT_DYNAMIC(CDlgDepartmentParam, CDialog)

CDlgDepartmentParam::CDlgDepartmentParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDepartmentParam::IDD, pParent)
{
    m_iDepartmentID = 0;
    m_csDepartmentName = _T("");
}

CDlgDepartmentParam::~CDlgDepartmentParam()
{
}

void CDlgDepartmentParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_DEPARTMENT_ID, m_iDepartmentID);
    DDX_Text(pDX, IDC_EDIT_DEPARTMENT_NAME, m_csDepartmentName);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_cmbEnable);
}

BOOL CDlgDepartmentParam::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbEnable.SetCurSel(0);

    return TRUE;
}


BEGIN_MESSAGE_MAP(CDlgDepartmentParam, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_DEPARTMENT_PARAM, &CDlgDepartmentParam::OnBnClickedBtnGetDepartmentParam)
    ON_BN_CLICKED(IDC_BTN_SET_DEPARTMENT_PARAM, &CDlgDepartmentParam::OnBnClickedBtnSetDepartmentParam)
END_MESSAGE_MAP()


// CDlgDepartmentParam 消息处理程序


void CDlgDepartmentParam::OnBnClickedBtnGetDepartmentParam()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_csDepartmentName = _T("");

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/AccessControl/DepartmentParam/DepartmentNo/%d", m_iDepartmentID);
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
    if (xmlBase.FindElem("DepartmentParam") && xmlBase.IntoElem())
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
        if (xmlBase.FindElem("departmentName"))
        {
            m_csDepartmentName = xmlBase.GetData().c_str();
        }
    }

    delete[]pOutBuf;
    pOutBuf = NULL;

    UpdateData(FALSE);
}


void CDlgDepartmentParam::OnBnClickedBtnSetDepartmentParam()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateDepartmentParamXml(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/AccessControl/DepartmentParam/DepartmentNo/%d", m_iDepartmentID);
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

BOOL CDlgDepartmentParam::CreateDepartmentParamXml(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("DepartmentParam");
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
    xmlBase.AddNode("departmentName", m_csDepartmentName.GetBuffer(0));
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}
