// DlgUHFBasicInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgUHFBasicInfo.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgUHFBasicInfo 对话框

IMPLEMENT_DYNAMIC(CDlgUHFBasicInfo, CDialogEx)

CDlgUHFBasicInfo::CDlgUHFBasicInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUHFBasicInfo::IDD, pParent)
    , m_lUserID(-1)
    , m_iDeviceIndex(-1)
    , m_iOutputPower(0)
    , m_iRepeatLabelFilterTime(0)
    , m_iStartHour1(0)
    , m_iStartHour2(0)
    , m_iStartHour3(0)
    , m_iStartMinute1(0)
    , m_iStartMinute2(0)
    , m_iStartMinute3(0)
    , m_iStopHour1(0)
    , m_iStopHour2(0)
    , m_iStopHour3(0)
    , m_iStopMinute1(0)
    , m_iStopMinute2(0)
    , m_iStopMinute3(0)
    , m_ctDate(COleDateTime::GetCurrentTime())
    , m_ctTime(COleDateTime::GetCurrentTime())
{

}

CDlgUHFBasicInfo::~CDlgUHFBasicInfo()
{
}

void CDlgUHFBasicInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_READ_WRITE_MODE, m_comboReadWriteMode);
    DDX_Control(pDX, IDC_COMBO_WORK_FREQUENCY_TYPE, m_comboWorkFrequencyType);
    DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comboWorkMode);
    DDX_Text(pDX, IDC_EDIT_OUTPUT_POWER, m_iOutputPower);
    DDX_Text(pDX, IDC_EDIT_REPEAT_LABEL_FILTER_TIME, m_iRepeatLabelFilterTime);
    DDX_Text(pDX, IDC_EDIT_START_HOUR1, m_iStartHour1);
    DDX_Text(pDX, IDC_EDIT_START_HOUR2, m_iStartHour2);
    DDX_Text(pDX, IDC_EDIT_START_HOUR3, m_iStartHour3);
    DDX_Text(pDX, IDC_EDIT_START_MINUTE1, m_iStartMinute1);
    DDX_Text(pDX, IDC_EDIT_START_MINUTE2, m_iStartMinute2);
    DDX_Text(pDX, IDC_EDIT_START_MINUTE3, m_iStartMinute3);
    DDX_Text(pDX, IDC_EDIT_STOP_HOUR1, m_iStopHour1);
    DDX_Text(pDX, IDC_EDIT_STOP_HOUR2, m_iStopHour2);
    DDX_Text(pDX, IDC_EDIT_STOP_HOUR3, m_iStopHour3);
    DDX_Text(pDX, IDC_EDIT_STOP_MINUTE1, m_iStopMinute1);
    DDX_Text(pDX, IDC_EDIT_STOP_MINUTE2, m_iStopMinute2);
    DDX_Text(pDX, IDC_EDIT_STOP_MINUTE3, m_iStopMinute3);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE, m_ctDate);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TIME, m_ctTime);
}


BEGIN_MESSAGE_MAP(CDlgUHFBasicInfo, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgUHFBasicInfo::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgUHFBasicInfo::OnBnClickedButtonSet)
    ON_BN_CLICKED(IDC_BUTTON_GET_TIME, &CDlgUHFBasicInfo::OnBnClickedButtonGetTime)
    ON_BN_CLICKED(IDC_BUTTON_SET_TIME, &CDlgUHFBasicInfo::OnBnClickedButtonSetTime)
END_MESSAGE_MAP()


// CDlgUHFBasicInfo 消息处理程序

BOOL CDlgUHFBasicInfo::CreateUHFBasicInfo(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CTime timeCur = CTime::GetCurrentTime();
    CXmlBase xmlBase;
    CString strParam = _T("");
    xmlBase.CreateRoot("BasicInformation");
    xmlBase.SetAttribute("version", "2.0");
    if (m_comboWorkMode.GetCurSel() == 0)
    {
        xmlBase.AddNode("workMode", "network");
        xmlBase.OutOfElem();
    }
    else if (m_comboWorkMode.GetCurSel() == 1)
    {
        xmlBase.AddNode("workMode", "serialPort");
        xmlBase.OutOfElem();
    }
    else if (m_comboWorkMode.GetCurSel() == 2)
    {
        xmlBase.AddNode("workMode", "wiegand");
        xmlBase.OutOfElem();
    }

    if (m_comboWorkFrequencyType.GetCurSel() == 0)
    {
        xmlBase.AddNode("workFrequencyType", "chinese");
        xmlBase.OutOfElem();
    }
    else if (m_comboWorkFrequencyType.GetCurSel() == 1)
    {
        xmlBase.AddNode("workFrequencyType", "american");
        xmlBase.OutOfElem();
    }
    else if (m_comboWorkFrequencyType.GetCurSel() == 2)
    {
        xmlBase.AddNode("workFrequencyType", "european");
        xmlBase.OutOfElem();
    }
    else if (m_comboWorkFrequencyType.GetCurSel() == 3)
    {
        xmlBase.AddNode("workFrequencyType", "japanese");
        xmlBase.OutOfElem();
    }

    strParam.Format("%d", m_iOutputPower);
    xmlBase.AddNode("outputPower", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    if (m_comboReadWriteMode.GetCurSel() == 0)
    {
        xmlBase.AddNode("readWriteMode", "single");
        xmlBase.OutOfElem();
    }
    else if (m_comboReadWriteMode.GetCurSel() == 1)
    {
        xmlBase.AddNode("readWriteMode", "timing");
        xmlBase.OutOfElem();

        if (xmlBase.AddNode("TimeBlockList"))
        {
            if (xmlBase.AddNode("TimeBlock"))
            {
                if (xmlBase.AddNode("TimeRange"))
                {
                    strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d+08:00", timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), m_iStartHour1, m_iStartMinute1, 0);
                    xmlBase.AddNode("beginTime", strParam.GetBuffer(0));
                    xmlBase.OutOfElem();
                    strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d+08:00", timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), m_iStopHour1, m_iStopMinute1, 0);
                    xmlBase.AddNode("endTime", strParam.GetBuffer(0));
                    xmlBase.OutOfElem();

                    xmlBase.OutOfElem();
                }
                xmlBase.OutOfElem();
            }

            if (xmlBase.AddNode("TimeBlock"))
            {
                if (xmlBase.AddNode("TimeRange"))
                {
                    strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d+08:00", timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), m_iStartHour2, m_iStartMinute2, 0);
                    xmlBase.AddNode("beginTime", strParam.GetBuffer(0));
                    xmlBase.OutOfElem();
                    strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d+08:00", timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), m_iStopHour2, m_iStopMinute2, 0);
                    xmlBase.AddNode("endTime", strParam.GetBuffer(0));
                    xmlBase.OutOfElem();

                    xmlBase.OutOfElem();
                }
                xmlBase.OutOfElem();
            }


            if (xmlBase.AddNode("TimeBlock"))
            {
                if (xmlBase.AddNode("TimeRange"))
                {
                    strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d+08:00", timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), m_iStartHour3, m_iStartMinute3, 0);
                    xmlBase.AddNode("beginTime", strParam.GetBuffer(0));
                    xmlBase.OutOfElem();
                    strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d+08:00", timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), m_iStopHour3, m_iStopMinute3, 0);
                    xmlBase.AddNode("endTime", strParam.GetBuffer(0));
                    xmlBase.OutOfElem();

                    xmlBase.OutOfElem();
                }
                xmlBase.OutOfElem();
            }
            xmlBase.OutOfElem();
        }

    }
    else if (m_comboReadWriteMode.GetCurSel() == 2)
    {
        xmlBase.AddNode("readWriteMode", "trigger");
        xmlBase.OutOfElem();
    }

    strParam.Format("%d", m_iRepeatLabelFilterTime);
    xmlBase.AddNode("repeatLabelFilterTime", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}


void CDlgUHFBasicInfo::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/Traffic/UHFRFIDReader/basicInformation\r\n");
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        if (pOutBuf != NULL)
        {
            delete[]pOutBuf;
            pOutBuf = NULL;
        }
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("BasicInformation") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("workMode"))
        {
            if (xmlBase.GetData().compare("network") == 0)
            {
                m_comboWorkMode.SetCurSel(0);
            }
            else if (xmlBase.GetData().compare("serialPort") == 0)
            {
                m_comboWorkMode.SetCurSel(1);
            }
            else if (xmlBase.GetData().compare("wiegand") == 0)
            {
                m_comboWorkMode.SetCurSel(2);
            }
        }

        if (xmlBase.FindElem("workFrequencyType"))
        {
            if (xmlBase.GetData().compare("chinese") == 0)
            {
                m_comboWorkFrequencyType.SetCurSel(0);
            }
            else if (xmlBase.GetData().compare("american") == 0)
            {
                m_comboWorkFrequencyType.SetCurSel(1);
            }
            else if (xmlBase.GetData().compare("european") == 0)
            {
                m_comboWorkFrequencyType.SetCurSel(2);
            }
            else if (xmlBase.GetData().compare("japanese") == 0)
            {
                m_comboWorkFrequencyType.SetCurSel(3);
            }
        }

        if (xmlBase.FindElem("outputPower"))
        {
            m_iOutputPower = atoi(xmlBase.GetData().c_str());
        }

        if (xmlBase.FindElem("readWriteMode"))
        {
            if (xmlBase.GetData().compare("single") == 0)
            {
                m_comboReadWriteMode.SetCurSel(0);
            }
            else if (xmlBase.GetData().compare("timing") == 0)
            {
                m_comboReadWriteMode.SetCurSel(1);

                if (xmlBase.FindElem("TimeBlockList") && xmlBase.IntoElem())
                {
                    if (xmlBase.FindElem("TimeBlock") && xmlBase.IntoElem())
                    {
                        if (xmlBase.FindElem("TimeRange") && xmlBase.IntoElem())
                        {
                            if (xmlBase.FindElem("beginTime"))
                            {
                                m_iStartHour1 = atoi(xmlBase.GetData().substr(11, 2).c_str());
                                m_iStartMinute1 = atoi(xmlBase.GetData().substr(14, 2).c_str());
                            }
                            if (xmlBase.FindElem("endTime"))
                            {
                                m_iStopHour1 = atoi(xmlBase.GetData().substr(11, 2).c_str());
                                m_iStopMinute1 = atoi(xmlBase.GetData().substr(14, 2).c_str());
                            }
                            xmlBase.OutOfElem();
                        }
                        xmlBase.OutOfElem();
                    }
                    xmlBase.NextSibElem();
                    if (xmlBase.FindElem("TimeBlock") && xmlBase.IntoElem())
                    {
                        if (xmlBase.FindElem("TimeRange") && xmlBase.IntoElem())
                        {
                            if (xmlBase.FindElem("beginTime"))
                            {
                                m_iStartHour2 = atoi(xmlBase.GetData().substr(11, 2).c_str());
                                m_iStartMinute2 = atoi(xmlBase.GetData().substr(14, 2).c_str());
                            }
                            if (xmlBase.FindElem("endTime"))
                            {
                                m_iStopHour2 = atoi(xmlBase.GetData().substr(11, 2).c_str());
                                m_iStopMinute2 = atoi(xmlBase.GetData().substr(14, 2).c_str());
                            }
                            xmlBase.OutOfElem();
                        }
                        xmlBase.OutOfElem();
                    }
                    xmlBase.NextSibElem();
                    if (xmlBase.FindElem("TimeBlock") && xmlBase.IntoElem())
                    {
                        if (xmlBase.FindElem("TimeRange") && xmlBase.IntoElem())
                        {
                            if (xmlBase.FindElem("beginTime"))
                            {
                                m_iStartHour3 = atoi(xmlBase.GetData().substr(11, 2).c_str());
                                m_iStartMinute3 = atoi(xmlBase.GetData().substr(14, 2).c_str());
                            }
                            if (xmlBase.FindElem("endTime"))
                            {
                                m_iStopHour3 = atoi(xmlBase.GetData().substr(11, 2).c_str());
                                m_iStopMinute3 = atoi(xmlBase.GetData().substr(14, 2).c_str());
                            }
                            xmlBase.OutOfElem();
                        }
                        xmlBase.OutOfElem();
                    }
                    xmlBase.OutOfElem();
                }
                xmlBase.NextSibElem();
            }
            else if (xmlBase.GetData().compare("trigger") == 0)
            {
                m_comboReadWriteMode.SetCurSel(2);
            }
        }

        if (xmlBase.FindElem("repeatLabelFilterTime"))
        {
            m_iRepeatLabelFilterTime = atoi(xmlBase.GetData().c_str());
        }

        xmlBase.OutOfElem();
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }
    UpdateData(FALSE);

    return;
}


void CDlgUHFBasicInfo::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateUHFBasicInfo(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/Traffic/UHFRFIDReader/basicInformation\r\n");
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }

    UpdateData(FALSE);
}


void CDlgUHFBasicInfo::OnBnClickedButtonGetTime()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_TIME struTime = { 0 };
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_TIMECFG, 0, &struTime, sizeof(NET_DVR_TIME), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TIMECFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TIMECFG");
        m_ctDate.SetDate(struTime.dwYear, struTime.dwMonth, struTime.dwDay);
        m_ctTime.SetTime(struTime.dwHour, struTime.dwMinute, struTime.dwSecond);
    }
    UpdateData(FALSE);
}


void CDlgUHFBasicInfo::OnBnClickedButtonSetTime()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_TIME struTime = { 0 };
    struTime.dwYear = m_ctDate.GetYear();
    struTime.dwMonth = m_ctDate.GetMonth();
    struTime.dwDay = m_ctDate.GetDay();
    struTime.dwHour = m_ctTime.GetHour();
    struTime.dwMinute = m_ctTime.GetMinute();
    struTime.dwSecond = m_ctTime.GetSecond();
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_TIMECFG, 0, &struTime, sizeof(NET_DVR_TIME)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TIMECFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TIMECFG");
    }
}
