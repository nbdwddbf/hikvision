// DlgAttendanceRule.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAttendanceRule.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgAttendanceRule 对话框

IMPLEMENT_DYNAMIC(CDlgAttendanceRule, CDialog)

CDlgAttendanceRule::CDlgAttendanceRule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAttendanceRule::IDD, pParent)
{
    m_iAttendanceRuleID = 0;
    m_iOnDutyAdvance = 0;
    m_iOnDutyDelay = 0;
    m_iOnDutyAbsence = 0;
    m_iOffDutyAdvance = 0;
    m_iOffDutyDelay = 0;
    m_iOffDutyAbsence = 0;
    m_iRest = 0;
}

CDlgAttendanceRule::~CDlgAttendanceRule()
{
}

void CDlgAttendanceRule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ON_DUTY_ENABLE, m_cmbOnDutyEnable);
    DDX_Control(pDX, IDC_COMBO_OFF_DUTY_ENABLE, m_cmbOffDutyEnable);
    DDX_Control(pDX, IDC_COMBO_REST_ENABLE, m_cmbRestEnable);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_cmbEnable);
    DDX_Text(pDX, IDC_EDIT_ATTENDANCE_RULE_ID, m_iAttendanceRuleID);
    DDX_Text(pDX, IDC_EDIT_ON_DUTY_ADVANCE, m_iOnDutyAdvance);
    DDX_Text(pDX, IDC_EDIT_ON_DUTY_DELAY, m_iOnDutyDelay);
    DDX_Text(pDX, IDC_EDIT_ON_DUTY_ABSENCE, m_iOnDutyAbsence);
    DDX_Text(pDX, IDC_EDIT_OFF_DUTY_ADVANCE, m_iOffDutyAdvance);
    DDX_Text(pDX, IDC_EDIT_OFF_DUTY_DELAY, m_iOffDutyDelay);
    DDX_Text(pDX, IDC_EDIT_OFF_DUTY_ABSENCE, m_iOffDutyAbsence);
    DDX_Text(pDX, IDC_EDIT_REST, m_iRest);
}

BOOL CDlgAttendanceRule::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbOnDutyEnable.SetCurSel(0);
    m_cmbOffDutyEnable.SetCurSel(0);
    m_cmbRestEnable.SetCurSel(0);
    m_cmbEnable.SetCurSel(0);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgAttendanceRule, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_ATTENDANCE_RULE, &CDlgAttendanceRule::OnBnClickedBtnGetAttendanceRule)
    ON_BN_CLICKED(IDC_BTN_SET_ATTENDANCE_RULE, &CDlgAttendanceRule::OnBnClickedBtnSetAttendanceRule)
END_MESSAGE_MAP()


// CDlgAttendanceRule 消息处理程序


void CDlgAttendanceRule::OnBnClickedBtnGetAttendanceRule()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_iOnDutyAdvance = 0;
    m_iOnDutyDelay = 0;
    m_iOnDutyAbsence = 0;
    m_iOffDutyAdvance = 0;
    m_iOffDutyDelay = 0;
    m_iOffDutyAbsence = 0;
    m_iRest = 0;
    m_cmbOnDutyEnable.SetCurSel(0);
    m_cmbOffDutyEnable.SetCurSel(0);
    m_cmbRestEnable.SetCurSel(0);

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/AccessControl/AttendanceRule/AttendanceRuleNo/%d", m_iAttendanceRuleID);
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
    if (xmlBase.FindElem("AttendanceRule") && xmlBase.IntoElem())
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
        if (xmlBase.FindElem("OnDutyRule") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("enabled"))
            {
                if (xmlBase.GetData().compare("true") == 0)
                {
                    m_cmbOnDutyEnable.SetCurSel(1);
                }
                else
                {
                    m_cmbOnDutyEnable.SetCurSel(0);
                }
            }
            if (xmlBase.FindElem("onDutyAdvanceMinutes"))
            {
                m_iOnDutyAdvance = atoi(xmlBase.GetData().c_str());
            }
            if (xmlBase.FindElem("onDutyDelayMinutes"))
            {
                m_iOnDutyDelay = atoi(xmlBase.GetData().c_str());
            }
            if (xmlBase.FindElem("onDutyAbsenceMinutes"))
            {
                m_iOnDutyAbsence = atoi(xmlBase.GetData().c_str());
            }
        }
        xmlBase.OutOfElem();
        if (xmlBase.FindElem("OffDutyRule") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("enabled"))
            {
                if (xmlBase.GetData().compare("true") == 0)
                {
                    m_cmbOffDutyEnable.SetCurSel(1);
                }
                else
                {
                    m_cmbOffDutyEnable.SetCurSel(0);
                }
            }
            if (xmlBase.FindElem("offDutyAdvanceMinutes"))
            {
                m_iOffDutyAdvance = atoi(xmlBase.GetData().c_str());
            }
            if (xmlBase.FindElem("offDutyDelayMinutes"))
            {
                m_iOffDutyDelay = atoi(xmlBase.GetData().c_str());
            }
            if (xmlBase.FindElem("offDutyAbsenceMinutes"))
            {
                m_iOffDutyAbsence = atoi(xmlBase.GetData().c_str());
            }
        }
        xmlBase.OutOfElem();
        if (xmlBase.FindElem("RestRule") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("enabled"))
            {
                if (xmlBase.GetData().compare("true") == 0)
                {
                    m_cmbRestEnable.SetCurSel(1);
                }
                else
                {
                    m_cmbRestEnable.SetCurSel(0);
                }
            }
            if (xmlBase.FindElem("restMinutes"))
            {
                m_iRest = atoi(xmlBase.GetData().c_str());
            }
        }
        xmlBase.OutOfElem();
    }

    delete[]pOutBuf;
    pOutBuf = NULL;

    UpdateData(FALSE);
}


void CDlgAttendanceRule::OnBnClickedBtnSetAttendanceRule()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateAttendanceRuleXml(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/AccessControl/AttendanceRule/AttendanceRuleNo/%d", m_iAttendanceRuleID);
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

BOOL CDlgAttendanceRule::CreateAttendanceRuleXml(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("AttendanceRule");
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
    xmlBase.AddNode("OnDutyRule");
    if (m_cmbOnDutyEnable.GetCurSel() == 0)
    {
        xmlBase.AddNode("enabled", "false");
    }
    else
    {
        xmlBase.AddNode("enabled", "true");
    }
    xmlBase.OutOfElem();
    char szOnDutyAdvance[32] = { 0 };
    sprintf(szOnDutyAdvance, "%d", m_iOnDutyAdvance);
    xmlBase.AddNode("onDutyAdvanceMinutes", szOnDutyAdvance);
    xmlBase.OutOfElem();
    char szOnDutyDelay[32] = { 0 };
    sprintf(szOnDutyDelay, "%d", m_iOnDutyDelay);
    xmlBase.AddNode("onDutyDelayMinutes", szOnDutyDelay);
    xmlBase.OutOfElem();
    char szOnDutyAbsence[32] = { 0 };
    sprintf(szOnDutyAbsence, "%d", m_iOnDutyAbsence);
    xmlBase.AddNode("onDutyAbsenceMinutes", szOnDutyAbsence);
    xmlBase.OutOfElem();
    xmlBase.OutOfElem();

    xmlBase.AddNode("OffDutyRule");
    if (m_cmbOffDutyEnable.GetCurSel() == 0)
    {
        xmlBase.AddNode("enabled", "false");
    }
    else
    {
        xmlBase.AddNode("enabled", "true");
    }
    xmlBase.OutOfElem();
    char szOffDutyAdvance[32] = { 0 };
    sprintf(szOffDutyAdvance, "%d", m_iOffDutyAdvance);
    xmlBase.AddNode("offDutyAdvanceMinutes", szOffDutyAdvance);
    xmlBase.OutOfElem();
    char szOffDutyDelay[32] = { 0 };
    sprintf(szOffDutyDelay, "%d", m_iOffDutyDelay);
    xmlBase.AddNode("offDutyDelayMinutes", szOffDutyDelay);
    xmlBase.OutOfElem();
    char szOffDutyAbsence[32] = { 0 };
    sprintf(szOffDutyAbsence, "%d", m_iOffDutyAbsence);
    xmlBase.AddNode("offDutyAbsenceMinutes", szOffDutyAbsence);
    xmlBase.OutOfElem();
    xmlBase.OutOfElem();

    xmlBase.AddNode("RestRule");
    if (m_cmbRestEnable.GetCurSel() == 0)
    {
        xmlBase.AddNode("enabled", "false");
    }
    else
    {
        xmlBase.AddNode("enabled", "true");
    }
    xmlBase.OutOfElem();
    char szRest[32] = { 0 };
    sprintf(szRest, "%d", m_iRest);
    xmlBase.AddNode("restMinutes", szRest);
    xmlBase.OutOfElem();
    xmlBase.OutOfElem();

    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}