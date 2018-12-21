// DlgAttendanceHolidayGroup.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAttendanceHolidayGroup.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"

// CDlgAttendanceHolidayGroup 对话框

IMPLEMENT_DYNAMIC(CDlgAttendanceHolidayGroup, CDialog)

CDlgAttendanceHolidayGroup::CDlgAttendanceHolidayGroup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAttendanceHolidayGroup::IDD, pParent)
{
    m_iHolidayGroupID = 0;
    m_csHolidayGroupName = _T("");
    memset(m_dwHolidayPlanID, 0, 32 * sizeof(DWORD));
}

CDlgAttendanceHolidayGroup::~CDlgAttendanceHolidayGroup()
{

}

void CDlgAttendanceHolidayGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_cmbEnable);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE1, m_cmbHolidayPlanEnable[0]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE2, m_cmbHolidayPlanEnable[1]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE3, m_cmbHolidayPlanEnable[2]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE4, m_cmbHolidayPlanEnable[3]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE5, m_cmbHolidayPlanEnable[4]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE6, m_cmbHolidayPlanEnable[5]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE7, m_cmbHolidayPlanEnable[6]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE8, m_cmbHolidayPlanEnable[7]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE9, m_cmbHolidayPlanEnable[8]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE10, m_cmbHolidayPlanEnable[9]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE11, m_cmbHolidayPlanEnable[10]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE12, m_cmbHolidayPlanEnable[11]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE13, m_cmbHolidayPlanEnable[12]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE14, m_cmbHolidayPlanEnable[13]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE15, m_cmbHolidayPlanEnable[14]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE16, m_cmbHolidayPlanEnable[15]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE17, m_cmbHolidayPlanEnable[16]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE18, m_cmbHolidayPlanEnable[17]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE19, m_cmbHolidayPlanEnable[18]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE20, m_cmbHolidayPlanEnable[19]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE21, m_cmbHolidayPlanEnable[20]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE22, m_cmbHolidayPlanEnable[21]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE23, m_cmbHolidayPlanEnable[22]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE24, m_cmbHolidayPlanEnable[23]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE25, m_cmbHolidayPlanEnable[24]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE26, m_cmbHolidayPlanEnable[25]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE27, m_cmbHolidayPlanEnable[26]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE28, m_cmbHolidayPlanEnable[27]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE29, m_cmbHolidayPlanEnable[28]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE30, m_cmbHolidayPlanEnable[29]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE31, m_cmbHolidayPlanEnable[30]);
    DDX_Control(pDX, IDC_COMBO_HOLIDAY_PLAN_ENABLE32, m_cmbHolidayPlanEnable[31]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_GROUP_ID, m_iHolidayGroupID);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_GROUP_NAME, m_csHolidayGroupName);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID1, m_dwHolidayPlanID[0]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID2, m_dwHolidayPlanID[1]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID3, m_dwHolidayPlanID[2]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID4, m_dwHolidayPlanID[3]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID5, m_dwHolidayPlanID[4]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID6, m_dwHolidayPlanID[5]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID7, m_dwHolidayPlanID[6]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID8, m_dwHolidayPlanID[7]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID9, m_dwHolidayPlanID[8]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID10, m_dwHolidayPlanID[9]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID11, m_dwHolidayPlanID[10]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID12, m_dwHolidayPlanID[11]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID13, m_dwHolidayPlanID[12]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID14, m_dwHolidayPlanID[13]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID15, m_dwHolidayPlanID[14]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID16, m_dwHolidayPlanID[15]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID17, m_dwHolidayPlanID[16]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID18, m_dwHolidayPlanID[17]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID19, m_dwHolidayPlanID[18]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID20, m_dwHolidayPlanID[19]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID21, m_dwHolidayPlanID[20]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID22, m_dwHolidayPlanID[21]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID23, m_dwHolidayPlanID[22]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID24, m_dwHolidayPlanID[23]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID25, m_dwHolidayPlanID[24]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID26, m_dwHolidayPlanID[25]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID27, m_dwHolidayPlanID[26]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID28, m_dwHolidayPlanID[27]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID29, m_dwHolidayPlanID[28]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID30, m_dwHolidayPlanID[29]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID31, m_dwHolidayPlanID[30]);
    DDX_Text(pDX, IDC_EDIT_HOLIDAY_PLAN_ID32, m_dwHolidayPlanID[31]);
}

BOOL CDlgAttendanceHolidayGroup::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbEnable.SetCurSel(0);
    for (int i = 0; i < 32; i++)
    {
        m_cmbHolidayPlanEnable[i].SetCurSel(0);
    }

    return TRUE;
}


BEGIN_MESSAGE_MAP(CDlgAttendanceHolidayGroup, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET_ATTENDANCE_HOLIDAY_GROUP, &CDlgAttendanceHolidayGroup::OnBnClickedBtnGetAttendanceHolidayGroup)
    ON_BN_CLICKED(IDC_BTN_SET_ATTENDANCE_HOLIDAY_GROUP, &CDlgAttendanceHolidayGroup::OnBnClickedBtnSetAttendanceHolidayGroup)
END_MESSAGE_MAP()


// CDlgAttendanceHolidayGroup 消息处理程序


void CDlgAttendanceHolidayGroup::OnBnClickedBtnGetAttendanceHolidayGroup()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_cmbEnable.SetCurSel(0);
    for (int i = 0; i < 32; i++)
    {
        m_cmbHolidayPlanEnable[i].SetCurSel(0);
    }
    m_csHolidayGroupName = _T("");
    memset(m_dwHolidayPlanID, 0, 32 * sizeof(DWORD));

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/AccessControl/AttendanceHolidayGroup/HolidayGroupNo/%d", m_iHolidayGroupID);
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
    if (xmlBase.FindElem("AttendanceHolidayGroup") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("holidayGroupName"))
        {
            m_csHolidayGroupName = xmlBase.GetData().c_str();
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
        if (xmlBase.FindElem("HolidayPlanList") && xmlBase.IntoElem())
        {
            for (int i = 0; i < 32; i++)
            {
                if (xmlBase.FindElem("HolidayPlanAction") && xmlBase.IntoElem())
                {
                    if (xmlBase.FindElem("id"))
                    {
                        m_dwHolidayPlanID[i] = atoi(xmlBase.GetData().c_str());
                    }
                    if (xmlBase.FindElem("enabled"))
                    {
                        if (xmlBase.GetData().compare("false") == 0)
                        {
                            m_cmbHolidayPlanEnable[i].SetCurSel(0);
                        }
                        else
                        {
                            m_cmbHolidayPlanEnable[i].SetCurSel(1);
                        }
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


void CDlgAttendanceHolidayGroup::OnBnClickedBtnSetAttendanceHolidayGroup()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateAttendanceHolidayGroupXml(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/AccessControl/AttendanceHolidayGroup/HolidayGroupNo/%d", m_iHolidayGroupID);
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

BOOL CDlgAttendanceHolidayGroup::CreateAttendanceHolidayGroupXml(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("AttendanceHolidayGroup");
    xmlBase.SetAttribute("version", "2.0");
    
    xmlBase.AddNode("holidayGroupName", m_csHolidayGroupName.GetBuffer(0));
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
    xmlBase.AddNode("HolidayPlanList");
    for (int i = 0; i < 32; i++)
    {
        if (m_dwHolidayPlanID[i] != 0)
        {
            xmlBase.AddNode("HolidayPlanAction");

            char szHolidayPlanID[32] = { 0 };
            sprintf(szHolidayPlanID, "%d", m_dwHolidayPlanID[i]);
            xmlBase.AddNode("id", szHolidayPlanID);
            xmlBase.OutOfElem();

            if (m_cmbHolidayPlanEnable[i].GetCurSel() == 0)
            {
                xmlBase.AddNode("enabled", "false");
            }
            else
            {
                xmlBase.AddNode("enabled", "true");
            }
            xmlBase.OutOfElem();

            xmlBase.OutOfElem();
        }
    }
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}