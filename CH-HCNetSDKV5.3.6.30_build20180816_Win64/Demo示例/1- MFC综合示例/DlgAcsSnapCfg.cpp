// DlgAcsSnapCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsSnapCfg.h"
#include "xml/XmlBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAcsSnapCfg dialog


DlgAcsSnapCfg::DlgAcsSnapCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAcsSnapCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAcsSnapCfg)
	m_dwSnapTimes = 0;
    m_IntervalTime1 = 0;
    m_IntervalTime2 = 0;
    m_IntervalTime3 = 0;
	m_IntervalTime4 = 0; 
	m_iSnapWaitTime = 0;
	//}}AFX_DATA_INIT
}


void DlgAcsSnapCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAcsSnapCfg)
	DDX_Text(pDX, IDC_EDIT_TIMES, m_dwSnapTimes);
    DDX_Text(pDX, IDC_EDIT_INTERVAL_TIME1, m_IntervalTime1);
    DDX_Text(pDX, IDC_EDIT_INTERVAL_TIME2, m_IntervalTime2);
    DDX_Text(pDX, IDC_EDIT_INTERVAL_TIME3, m_IntervalTime3);
    DDX_Text(pDX, IDC_EDIT_INTERVAL_TIME4, m_IntervalTime4);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_SNAP_WAIT_TIME, m_iSnapWaitTime);
	DDX_Control(pDX, IDC_COMBO_JPEG_RESOLUTION, m_comboJpegResolution);
	DDX_Control(pDX, IDC_COMBO_JPEG_QUALITY, m_comboJpegQuality);
}


BEGIN_MESSAGE_MAP(DlgAcsSnapCfg, CDialog)
	//{{AFX_MSG_MAP(DlgAcsSnapCfg)
    ON_BN_CLICKED(IDC_BUTTON_SET, OnSet)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_GET, &DlgAcsSnapCfg::OnBnClickedButtonGet)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAcsSnapCfg message handlers

BOOL DlgAcsSnapCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    UpdateData(TRUE);
    DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    
    UpdateData(FALSE);
    return TRUE;
}
void DlgAcsSnapCfg::OnSet()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struSnapCfg.bySnapTimes = m_dwSnapTimes;
    m_struSnapCfg.wIntervalTime[0] = m_IntervalTime1;
    m_struSnapCfg.wIntervalTime[1] = m_IntervalTime2;
    m_struSnapCfg.wIntervalTime[2] = m_IntervalTime3;
    m_struSnapCfg.wIntervalTime[3] = m_IntervalTime4;
	if (m_comboJpegResolution.GetCurSel() == m_comboJpegResolution.GetCount() - 1)
	{
		m_struSnapCfg.struJpegPara.wPicSize = 255;
	}
    else if (m_comboJpegResolution.GetCurSel() == 30)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 161;/*288*320*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 31)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 162;/*144*176*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 32)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 163;/*480*640*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 33)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 164;/*240*320*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 34)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 165;/*120*160*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 35)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 166;/*576*720*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 36)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 167;/*720*1280*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 37)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 168;/*576*960*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 38)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 180;/*180*240*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 39)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 181;/*360*480*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 40)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 182;/*540*720*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 41)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 183;/*720*960*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 42)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 184;/*960*1280*/
    }
    else if (m_comboJpegResolution.GetCurSel() == 43)
    {
        m_struSnapCfg.struJpegPara.wPicSize = 185;/*1080*1440*/
    }
	else
	{
		m_struSnapCfg.struJpegPara.wPicSize = m_comboJpegResolution.GetCurSel();
	}
	m_struSnapCfg.struJpegPara.wPicQuality = m_comboJpegQuality.GetCurSel();
	m_struSnapCfg.wSnapWaitTime = m_iSnapWaitTime;

    m_struSnapCfg.dwSize = sizeof(m_struSnapCfg);
    
    DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    char szLan[128] = {0};
    if(NET_DVR_ContinuousShoot(g_struDeviceInfo[dwDeviceIndex].lLoginID, &m_struSnapCfg))
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_ContinuousShoot SUCC");
        g_StringLanType(szLan, "设置成功", "NET_DVR_ContinuousShoot successed!");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_ContinuousShoot Failed");
        g_StringLanType(szLan, "设置失败", "NET_DVR_ContinuousShoot failed!");
        AfxMessageBox(szLan);
    }
}



void DlgAcsSnapCfg::OnBnClickedButtonGet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
	NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
	struInput.dwSize = sizeof(struInput);
	struOuput.dwSize = sizeof(struOuput);
	char szUrl[256] = { 0 };
	sprintf(szUrl, "GET /ISAPI/AccessControl/SnapConfig\r\n");
	struInput.lpRequestUrl = szUrl;
	struInput.dwRequestUrlLen = strlen(szUrl);
	DWORD dwOutputLen = 1024 * 1024;
	char *pOutBuf = new char[dwOutputLen];
	memset(pOutBuf, 0, dwOutputLen);
	struOuput.lpOutBuffer = pOutBuf;
	struOuput.dwOutBufferSize = dwOutputLen;

	if (!NET_DVR_STDXMLConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID, &struInput, &struOuput))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, szUrl);
		delete[]pOutBuf;
		pOutBuf = NULL;
		return;
	}
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, szUrl);
	}

	int iTempXML = 0;
	CXmlBase xmlBase;
	xmlBase.Parse(pOutBuf);
	if (xmlBase.FindElem("SnapConfig") && xmlBase.IntoElem())
	{
		if (xmlBase.FindElem("snapTimes"))
		{
			m_dwSnapTimes = atoi(xmlBase.GetData().c_str());
		}
		if (xmlBase.FindElem("snapWaitTime"))
		{
			m_iSnapWaitTime = atoi(xmlBase.GetData().c_str());
		}
		if (xmlBase.FindElem("intervalTimeList") && xmlBase.IntoElem())
		{
			if (xmlBase.FindElem("intervalTime"))
			{
				m_IntervalTime1 = atoi(xmlBase.GetData().c_str());
			}
			xmlBase.RemoveNode();
		}
		if (xmlBase.FindElem("intervalTimeList") && xmlBase.IntoElem())
		{
			if (xmlBase.FindElem("intervalTime"))
			{
				m_IntervalTime2 = atoi(xmlBase.GetData().c_str());
			}
			xmlBase.RemoveNode();
		}
		if (xmlBase.FindElem("intervalTimeList") && xmlBase.IntoElem())
		{
			if (xmlBase.FindElem("intervalTime"))
			{
				m_IntervalTime3 = atoi(xmlBase.GetData().c_str());
			}
			xmlBase.RemoveNode();
		}
		if (xmlBase.FindElem("intervalTimeList") && xmlBase.IntoElem())
		{
			if (xmlBase.FindElem("intervalTime"))
			{
				m_IntervalTime4 = atoi(xmlBase.GetData().c_str());
			}
			xmlBase.RemoveNode();
		}
		if (xmlBase.FindElem("JPEGParam") && xmlBase.IntoElem())
		{
			if (xmlBase.FindElem("pictureSize"))
			{
				iTempXML = atoi(xmlBase.GetData().c_str());
				if (iTempXML == 255)
				{
					m_comboJpegResolution.SetCurSel(m_comboJpegResolution.GetCount() - 1);
				}
                else if (iTempXML == 161)
                {
                    m_comboJpegResolution.SetCurSel(30);
                }
                else if (iTempXML == 162)
                {
                    m_comboJpegResolution.SetCurSel(31);
                }
                else if (iTempXML == 163)
                {
                    m_comboJpegResolution.SetCurSel(32);
                }
                else if (iTempXML == 164)
                {
                    m_comboJpegResolution.SetCurSel(33);
                }
                else if (iTempXML == 165)
                {
                    m_comboJpegResolution.SetCurSel(34);
                }
                else if (iTempXML == 166)
                {
                    m_comboJpegResolution.SetCurSel(35);
                }
                else if (iTempXML == 167)
                {
                    m_comboJpegResolution.SetCurSel(36);
                }
                else if (iTempXML == 168)
                {
                    m_comboJpegResolution.SetCurSel(37);
                }
                else if (iTempXML == 180)
                {
                    m_comboJpegResolution.SetCurSel(38);
                }
                else if (iTempXML == 181)
                {
                    m_comboJpegResolution.SetCurSel(39);
                }
                else if (iTempXML == 182)
                {
                    m_comboJpegResolution.SetCurSel(40);
                }
                else if (iTempXML == 183)
                {
                    m_comboJpegResolution.SetCurSel(41);
                }
                else if (iTempXML == 184)
                {
                    m_comboJpegResolution.SetCurSel(42);
                }
                else if (iTempXML == 185)
                {
                    m_comboJpegResolution.SetCurSel(43);
                }
                else
                {
                    m_comboJpegResolution.SetCurSel(iTempXML);
                }
			}
			if (xmlBase.FindElem("pictureQuality"))
			{
				if (xmlBase.GetData().compare("best") == 0)
				{
					m_comboJpegQuality.SetCurSel(0);
				}
				else if (xmlBase.GetData().compare("better") == 0)
				{
					m_comboJpegQuality.SetCurSel(1);
				}
				else if (xmlBase.GetData().compare("general") == 0)
				{
					m_comboJpegQuality.SetCurSel(2);
				}
			}
			xmlBase.OutOfElem();
		}
		xmlBase.OutOfElem();
	}

	if (NULL != pOutBuf)
	{
		delete[]pOutBuf;
		pOutBuf = NULL;
	}
	UpdateData(FALSE);

	return;
}
