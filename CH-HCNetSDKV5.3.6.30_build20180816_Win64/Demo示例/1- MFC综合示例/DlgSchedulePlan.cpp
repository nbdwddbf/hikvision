// DlgSchedulePlan.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgSchedulePlan.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgSchedulePlan 对话框

IMPLEMENT_DYNAMIC(CDlgSchedulePlan, CDialog)

CDlgSchedulePlan::CDlgSchedulePlan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSchedulePlan::IDD, pParent)
{
    m_iSchedulePlanID = 0;
    m_csScheduleStartTime = _T("");
    m_csScheduleEndTime = _T("");
    m_iHolidayGroupNo = 0;
    for (int i = 0; i < 7; i++)
    {
        m_csDayOfWeek[i] = _T("");
    }
    memset(m_dwClassNo, 0, 7 * sizeof(DWORD));
}

CDlgSchedulePlan::~CDlgSchedulePlan()
{
}

void CDlgSchedulePlan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_SCHEDULE_PLAN_ID, m_iSchedulePlanID);
    DDX_Control(pDX, IDC_COMBO_SCHEDULE_PLAN_TYPE, m_cmbSchedulePlanType);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_cmbEnable);
    DDX_Text(pDX, IDC_EDIT_SCHEDULE_START_TIME, m_csScheduleStartTime);
    DDX_Text(pDX, IDC_EDIT_SCHEDULE_END_TIME, m_csScheduleEndTime);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_GROUP_NO, m_iHolidayGroupNo);
    DDX_Text(pDX, IDC_EDIT_DAY_OF_WEEK1, m_csDayOfWeek[0]);
    DDX_Text(pDX, IDC_EDIT_DAY_OF_WEEK2, m_csDayOfWeek[1]);
    DDX_Text(pDX, IDC_EDIT_DAY_OF_WEEK3, m_csDayOfWeek[2]);
    DDX_Text(pDX, IDC_EDIT_DAY_OF_WEEK4, m_csDayOfWeek[3]);
    DDX_Text(pDX, IDC_EDIT_DAY_OF_WEEK5, m_csDayOfWeek[4]);
    DDX_Text(pDX, IDC_EDIT_DAY_OF_WEEK6, m_csDayOfWeek[5]);
    DDX_Text(pDX, IDC_EDIT_DAY_OF_WEEK7, m_csDayOfWeek[6]);
    DDX_Control(pDX, IDC_COMBO_CLASS_TYPE1, m_cmbClassType[0]);
    DDX_Control(pDX, IDC_COMBO_CLASS_TYPE2, m_cmbClassType[1]);
    DDX_Control(pDX, IDC_COMBO_CLASS_TYPE3, m_cmbClassType[2]);
    DDX_Control(pDX, IDC_COMBO_CLASS_TYPE4, m_cmbClassType[3]);
    DDX_Control(pDX, IDC_COMBO_CLASS_TYPE5, m_cmbClassType[4]);
    DDX_Control(pDX, IDC_COMBO_CLASS_TYPE6, m_cmbClassType[5]);
    DDX_Control(pDX, IDC_COMBO_CLASS_TYPE7, m_cmbClassType[6]);
    DDX_Text(pDX, IDC_EDIT_CLASS_NO1, m_dwClassNo[0]);
    DDX_Text(pDX, IDC_EDIT_CLASS_NO2, m_dwClassNo[1]);
    DDX_Text(pDX, IDC_EDIT_CLASS_NO3, m_dwClassNo[2]);
    DDX_Text(pDX, IDC_EDIT_CLASS_NO4, m_dwClassNo[3]);
    DDX_Text(pDX, IDC_EDIT_CLASS_NO5, m_dwClassNo[4]);
    DDX_Text(pDX, IDC_EDIT_CLASS_NO6, m_dwClassNo[5]);
    DDX_Text(pDX, IDC_EDIT_CLASS_NO7, m_dwClassNo[6]);
}

BOOL CDlgSchedulePlan::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbSchedulePlanType.SetCurSel(0);
    m_cmbEnable.SetCurSel(0);
    for (int i = 0; i < 7; i++)
    {
        m_cmbClassType[i].SetCurSel(0);
    }

    return TRUE;
}


BEGIN_MESSAGE_MAP(CDlgSchedulePlan, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_SCHEDULE_PLAN, &CDlgSchedulePlan::OnBnClickedBtnGetSchedulePlan)
    ON_BN_CLICKED(IDC_BTN_SET_SCHEDULE_PLAN, &CDlgSchedulePlan::OnBnClickedBtnSetSchedulePlan)
END_MESSAGE_MAP()


// CDlgSchedulePlan 消息处理程序


void CDlgSchedulePlan::OnBnClickedBtnGetSchedulePlan()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_csScheduleStartTime = _T("");
    m_csScheduleEndTime = _T("");
    m_iHolidayGroupNo = 0;
    for (int i = 0; i < 7; i++)
    {
        m_csDayOfWeek[i] = _T("");
    }
    memset(m_dwClassNo, 0, 7 * sizeof(DWORD));
    for (int i = 0; i < 7; i++)
    {
        m_cmbClassType[i].SetCurSel(0);
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/AccessControl/SchedulePlan/SchedulePlanNo/%d", m_iSchedulePlanID);
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
    if (xmlBase.FindElem("SchedulePlan") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("schedulePlanType"))
        {
            if (xmlBase.GetData().compare("personal") == 0)
            {
                m_cmbSchedulePlanType.SetCurSel(0);
            }
            else
            {
                m_cmbSchedulePlanType.SetCurSel(1);
            }
        }
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
        if (xmlBase.FindElem("ScheduleList") && xmlBase.IntoElem())
        {
            for (int i = 0; i < 7; i++)
            {
                if (xmlBase.FindElem("ScheduleAction") && xmlBase.IntoElem())
                {
                    if (xmlBase.FindElem("dayOfWeek"))
                    {
                        m_csDayOfWeek[i] = xmlBase.GetData().c_str();
                    }
                    if (xmlBase.FindElem("classType"))
                    {
                        if (xmlBase.GetData().compare("OrdinaryClass") == 0)
                        {
                            m_cmbClassType[i].SetCurSel(1);
                        }
                        else if (xmlBase.GetData().compare("WorkingClass") == 0)
                        {
                            m_cmbClassType[i].SetCurSel(2);
                        }
                        else
                        {
                            m_cmbClassType[i].SetCurSel(0);
                        }
                    }
                    if (xmlBase.FindElem("classNo"))
                    {
                        m_dwClassNo[i] = atoi(xmlBase.GetData().c_str());
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
        if (xmlBase.FindElem("scheduleStartTime"))
        {
            m_csScheduleStartTime = xmlBase.GetData().c_str();
        }
        if (xmlBase.FindElem("scheduleEndTime"))
        {
            m_csScheduleEndTime = xmlBase.GetData().c_str();
        }
        if (xmlBase.FindElem("holidayGroupNo"))
        {
            m_iHolidayGroupNo = atoi(xmlBase.GetData().c_str());
        }
    }
    
    delete[]pOutBuf;
    pOutBuf = NULL;

    UpdateData(FALSE);
}


void CDlgSchedulePlan::OnBnClickedBtnSetSchedulePlan()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateSchedulePlanXml(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/AccessControl/SchedulePlan/SchedulePlanNo/%d", m_iSchedulePlanID);
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

BOOL CDlgSchedulePlan::CreateSchedulePlanXml(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("SchedulePlan");
    xmlBase.SetAttribute("version", "2.0");

    if (m_cmbSchedulePlanType.GetCurSel() == 0)
    {
        xmlBase.AddNode("schedulePlanType", "personal");
    }
    else
    {
        xmlBase.AddNode("schedulePlanType", "department");
    }
    xmlBase.OutOfElem();
    if (m_cmbEnable.GetCurSel() == 0)
    {
        xmlBase.AddNode("enabled", "false");
    }
    else
    {
        xmlBase.AddNode("enabled", "true");
    }
    xmlBase.OutOfElem();
    xmlBase.AddNode("ScheduleList");
    for (int i = 0; i < 7; i++)
    {
        xmlBase.AddNode("ScheduleAction");

        xmlBase.AddNode("dayOfWeek", m_csDayOfWeek[i].GetBuffer(0));
        xmlBase.OutOfElem();

        if (m_cmbClassType[i].GetCurSel() == 0)
        {
            xmlBase.AddNode("classType", "NoClass");
        }
        else if (m_cmbClassType[i].GetCurSel() == 1)
        {
            xmlBase.AddNode("classType", "OrdinaryClass");
        }
        else
        {
            xmlBase.AddNode("classType", "WorkingClass");
        }
        xmlBase.OutOfElem();

        char szClassNo[32] = { 0 };
        sprintf(szClassNo, "%d", m_dwClassNo[i]);
        xmlBase.AddNode("classNo", szClassNo);
        xmlBase.OutOfElem();

        xmlBase.OutOfElem();
    }
    xmlBase.OutOfElem();
    xmlBase.AddNode("scheduleStartTime", m_csScheduleStartTime.GetBuffer(0));
    xmlBase.OutOfElem();
    xmlBase.AddNode("scheduleEndTime", m_csScheduleEndTime.GetBuffer(0));
    xmlBase.OutOfElem();
    char szHolidayGroupNo[32] = { 0 };
    sprintf(szHolidayGroupNo, "%d", m_iHolidayGroupNo);
    xmlBase.AddNode("holidayGroupNo", szHolidayGroupNo);
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}
