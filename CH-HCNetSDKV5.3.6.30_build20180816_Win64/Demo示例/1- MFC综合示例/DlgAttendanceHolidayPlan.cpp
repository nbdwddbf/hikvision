// DlgAttendanceHolidayPlan.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAttendanceHolidayPlan.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgAttendanceHolidayPlan 对话框

IMPLEMENT_DYNAMIC(CDlgAttendanceHolidayPlan, CDialog)

CDlgAttendanceHolidayPlan::CDlgAttendanceHolidayPlan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAttendanceHolidayPlan::IDD, pParent)
{
    m_iHolidayPlanID = 0;
    m_csHolidayPlanName = _T("");
    m_csStartTime = _T("");
    m_csEndTime = _T("");
}

CDlgAttendanceHolidayPlan::~CDlgAttendanceHolidayPlan()
{
}

void CDlgAttendanceHolidayPlan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID, m_iHolidayPlanID);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_NAME, m_csHolidayPlanName);
    DDX_Text(pDX, IDC_EDIT_START_TIME, m_csStartTime);
    DDX_Text(pDX, IDC_EDIT_END_TIME, m_csEndTime);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_cmbEnable);
}

BOOL CDlgAttendanceHolidayPlan::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbEnable.SetCurSel(0);

    return TRUE;
}


BEGIN_MESSAGE_MAP(CDlgAttendanceHolidayPlan, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_ATTENDANCE_HOLIDAY_PLAN, &CDlgAttendanceHolidayPlan::OnBnClickedBtnGetAttendanceHolidayPlan)
    ON_BN_CLICKED(IDC_BTN_SET_ATTENDANCE_HOLIDAY_PLAN, &CDlgAttendanceHolidayPlan::OnBnClickedBtnSetAttendanceHolidayPlan)
END_MESSAGE_MAP()


// CDlgAttendanceHolidayPlan 消息处理程序


void CDlgAttendanceHolidayPlan::OnBnClickedBtnGetAttendanceHolidayPlan()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_csHolidayPlanName = _T("");
    m_csStartTime = _T("");
    m_csEndTime = _T("");

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/AccessControl/AttendanceHolidayPlan/HolidayPlanNo/%d", m_iHolidayPlanID);
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
    if (xmlBase.FindElem("AttendanceHolidayPlan") && xmlBase.IntoElem())
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
        if (xmlBase.FindElem("holidayPlanName"))
        {
            m_csHolidayPlanName = xmlBase.GetData().c_str();
        }
        if (xmlBase.FindElem("startTime"))
        {
            m_csStartTime = xmlBase.GetData().c_str();
        }
        if (xmlBase.FindElem("endTime"))
        {
            m_csEndTime = xmlBase.GetData().c_str();
        }
    }

    delete[]pOutBuf;
    pOutBuf = NULL;

    UpdateData(FALSE);
}


void CDlgAttendanceHolidayPlan::OnBnClickedBtnSetAttendanceHolidayPlan()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateAttendanceHolidayPlanXml(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/AccessControl/AttendanceHolidayPlan/HolidayPlanNo/%d", m_iHolidayPlanID);
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

BOOL CDlgAttendanceHolidayPlan::CreateAttendanceHolidayPlanXml(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("AttendanceHolidayPlan");
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
    xmlBase.AddNode("holidayPlanName", m_csHolidayPlanName.GetBuffer(0));
    xmlBase.OutOfElem();
    xmlBase.AddNode("startTime", m_csStartTime.GetBuffer(0));
    xmlBase.OutOfElem();
    xmlBase.AddNode("endTime", m_csEndTime.GetBuffer(0));
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}
