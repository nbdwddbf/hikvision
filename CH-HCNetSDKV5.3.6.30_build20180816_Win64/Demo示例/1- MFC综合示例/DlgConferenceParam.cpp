// DlgConferenceParam.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgConferenceParam.h"
#include "./xml/XmlBase.h"

#include "DlgMCUCall.h"
#include "DlgTerminalConferenceStatus.h"
#include "DlgConferenceRegion.h"

#include "DlgMCUAddConference.h"
#include "DlgMCUSearchConference.h"
#include "DlgMCUGetConfStatus.h"
#include "DlgMCUGetDailyDistribution.h"
#include "DlgMCUConferenceCtrl.h"
#include "DlgMCUClearConfHistory.h"
#include "DlgMCUDelConference.h"
#include "DlgMCUTerminalCtrl.h"
#include "DlgMCUGetTermGroupList.h"
#include "DlgMCUTerminalGroupCfg.h"
#include "DlgMCUTerminalManageCfg.h"
#include "DlgMCUAbilityDetect.h"
#include "DlgTerminalGkCfg.h"
#include "DlgGKServer.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConferenceParam dialog


CDlgConferenceParam::CDlgConferenceParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConferenceParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConferenceParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgConferenceParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConferenceParam)
	DDX_Control(pDX, IDC_COMBO_CONFERENCE_INPUT, m_comboConferenceInput);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMB_STREAM_TYPE, m_comboStreamType);
}


BEGIN_MESSAGE_MAP(CDlgConferenceParam, CDialog)
	//{{AFX_MSG_MAP(CDlgConferenceParam)
	ON_BN_CLICKED(IDC_BUT_CALL, OnButCall)
	ON_BN_CLICKED(IDC_BUT_CONFERENCE_REGION, OnButConferenceRegion)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BUT_TERMINAL_CONFERENCE_STATUS, OnButTerminalConferenceStatus)
	ON_BN_CLICKED(IDC_BTN_ADD_CONFERENCE, OnBtnAddConference)
	ON_BN_CLICKED(IDC_BTN_SEARCH_CONF, OnBtnSearchConferenceStatus)
	ON_BN_CLICKED(IDC_BTN_GET_CONF_STATUS, OnBtnGetConferenceStatus)
	ON_BN_CLICKED(IDC_BTN_GET_CONF_DAILY_DIST, OnBtnGetConfDailyDistribution)
	ON_BN_CLICKED(IDC_BTN_CONF_CTRL, OnBtnGetConfCtrl)
	ON_BN_CLICKED(IDC_BTN_CLEAR_HISTORY, OnBtnClearConfHistory)
	ON_BN_CLICKED(IDC_BTN_DEL_CONFERENCE, OnBtnDelConference)
	ON_BN_CLICKED(IDC_BTN_TERM_CTRL, OnBtnTerminalCtrl)
	ON_BN_CLICKED(IDC_BTN_GET_DROUP_LIST, OnBtnTermGroupList)
	ON_BN_CLICKED(IDC_BTN_TERM_GROUP_CFG, OnBtnTermGroupCfg)
	ON_BN_CLICKED(IDC_BTN_TERM_MAN_CFG, OnBtnTermManCfg)
	ON_BN_CLICKED(IDC_BTN_CAP, OnBtnGetAbility)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_GK_CONFIG, &CDlgConferenceParam::OnBnClickedBtnGkConfig)
    ON_BN_CLICKED(IDC_BTN_GK_SERVER, &CDlgConferenceParam::OnBnClickedBtnGkServer)
    ON_CBN_SELCHANGE(IDC_COMBO_CONFERENCE_INPUT, &CDlgConferenceParam::OnCbnSelchangeComboConferenceInput)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConferenceParam message handlers

BOOL CDlgConferenceParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    char szLan[64] = { 0 };

    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    m_comboStreamType.ResetContent();
    g_StringLanType(szLan, "主码流", "Main stream");
    m_comboStreamType.InsertString(0, szLan);
    g_StringLanType(szLan, "子码流", "Sub stream");
    m_comboStreamType.InsertString(1, szLan);
    g_StringLanType(szLan, "三码流", "Three stream");
    m_comboStreamType.InsertString(2, szLan);
    m_comboStreamType.SetCurSel(0);

    NET_DVR_STD_ABILITY struAbility = {0};

    char *pXmlBuf = new(std::nothrow) char[1024*1024];

    if (pXmlBuf == NULL)
    {
        return FALSE;
    }
    else
    {
        struAbility.lpOutBuffer = (void *)pXmlBuf;
        struAbility.dwOutSize = 1024*1024;        

        if (!NET_DVR_GetSTDAbility(m_lUserID, NET_DVR_GET_VCS_CAP, &struAbility))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCS_CAP");
        }
        else
        {
            //输入源下拉框填充
            CXmlBase xmlBase;
            char szInputName[16] = {0};
            CString csInputName;
            DWORD dwMinNo = 0;
            DWORD dwMaxNo = 0;
            int i = 0;
            if (xmlBase.Parse((const char *)struAbility.lpOutBuffer))
            {
                if (xmlBase.FindElem("VCSCap") && xmlBase.IntoElem())
                {
                    if (xmlBase.FindElem("TerminalCap") && xmlBase.IntoElem())
                    {
                        if (xmlBase.FindElem("InputList") && xmlBase.IntoElem())
                        {
                            do 
                            {
                                if (xmlBase.FindElem("Input") && xmlBase.IntoElem())
                                {
                                    if (xmlBase.FindElem("inputType"))
                                    {
                                        if (xmlBase.GetData().compare("DVI") == 0)
                                        {
                                            sprintf(szInputName, "DVI");
                                        }
                                        else if (xmlBase.GetData().compare("SDI") == 0)
                                        {
                                            sprintf(szInputName, "SDI");
                                        }
                                        else if (xmlBase.GetData().compare("YPbPr") == 0)
                                        {
                                            sprintf(szInputName, "YPbPr");
                                        }
                                        else if (xmlBase.GetData().compare("VGA") == 0)
                                        {
                                            sprintf(szInputName, "VGA");
                                        }
                                        else if (xmlBase.GetData().compare("HDMI") == 0)
                                        {
                                            sprintf(szInputName, "HDMI");
                                        }
                                    }
                                    
                                    if (xmlBase.FindElem("inputNo"))
                                    {
                                        string temp = xmlBase.GetAttributeValue("min");
                                        dwMinNo = atoi(xmlBase.GetAttributeValue("min").c_str());
                                        dwMaxNo = atoi(xmlBase.GetAttributeValue("max").c_str());
                                    }
                                    
                                    xmlBase.OutOfElem();
                                    
                                    for (i = 0; i < dwMaxNo - dwMinNo + 1; i++)
                                    {
                                        csInputName.Format("%s%d", szInputName, i + 1);
                                        m_comboConferenceInput.AddString(csInputName);
                                        m_comboConferenceInput.SetItemData(m_comboConferenceInput.GetCount() - 1, dwMinNo + i);
                                    }
                                }
                            } while (xmlBase.NextSibElem());                           
                        }
                    }
                }
            }
        }
    }	

    delete[] pXmlBuf;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgConferenceParam::OnButCall() 
{
	// TODO: Add your control notification handler code here
	CDlgMCUCall dlg; 
	dlg.DoModal(); 
}


void CDlgConferenceParam::OnButConferenceRegion() 
{
	// TODO: Add your control notification handler code here
	CDlgConferenceRegion dlg; 
	dlg.DoModal(); 
}

void CDlgConferenceParam::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    NET_DVR_STD_CONFIG struStdConfig = {0};

    NET_DVR_TERMINAL_INPUT_CFG struTerminalInputCfg = {0};
    struTerminalInputCfg.dwSize = sizeof(struTerminalInputCfg);
    struTerminalInputCfg.dwInputNo = m_comboConferenceInput.GetItemData(m_comboConferenceInput.GetCurSel());
    struTerminalInputCfg.byStreamType = m_comboStreamType.GetCurSel();

    struStdConfig.lpInBuffer = &struTerminalInputCfg;
    struStdConfig.dwInSize = sizeof(struTerminalInputCfg);

    if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_TERMINAL_INPUT_CFG, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TERMINAL_INPUT_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TERMINAL_INPUT_CFG");
    }	
}

void CDlgConferenceParam::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_STD_CONFIG struStdConfig = {0};    
    NET_DVR_TERMINAL_INPUT_CFG struTerminalInputCfg = {0};
    struTerminalInputCfg.dwSize = sizeof(struTerminalInputCfg);

    struStdConfig.lpOutBuffer = &struTerminalInputCfg;
    struStdConfig.dwOutSize = sizeof(struTerminalInputCfg);

    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_TERMINAL_INPUT_CFG, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TERMINAL_INPUT_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TERMINAL_INPUT_CFG");

        int i = 0;

        for (i = 0; i < m_comboConferenceInput.GetCount(); i++)
        {
            if (struTerminalInputCfg.dwInputNo == m_comboConferenceInput.GetItemData(i))
            {
                m_comboConferenceInput.SetCurSel(i);
                break;
            }
        }
        m_comboStreamType.SetCurSel(struTerminalInputCfg.byStreamType);
    }	
}


void CDlgConferenceParam::OnButTerminalConferenceStatus() 
{
	// TODO: Add your control notification handler code here
	CDlgTerminalConferenceStatus dlg;
    dlg.DoModal();
}



void CDlgConferenceParam::OnBtnAddConference()
{
	CDlgMCUAddConference dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}


void CDlgConferenceParam::OnBtnSearchConferenceStatus()
{
	CDlgMCUSearchConference dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}


void CDlgConferenceParam::OnBtnGetConferenceStatus()
{
	CDlgMCUGetConfStatus dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}

void CDlgConferenceParam::OnBtnGetConfDailyDistribution()
{
	CDlgMCUGetDailyDistribution dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}

void CDlgConferenceParam::OnBtnGetConfCtrl()
{
	CDlgMCUConferenceCtrl dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}

void CDlgConferenceParam::OnBtnClearConfHistory()
{
	CDlgMCUClearConfHistory dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}

void CDlgConferenceParam::OnBtnDelConference()
{
	CDlgMCUDelConference dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}

void CDlgConferenceParam::OnBtnTerminalCtrl()
{
	CDlgMCUTerminalCtrl dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}

void CDlgConferenceParam::OnBtnTermGroupList()
{
    int i = m_iDeviceIndex;
    int iD = m_lUserID;
	CDlgMCUGetTermGroupList dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}

void CDlgConferenceParam::OnBtnTermGroupCfg()
{
	CDlgMCUTerminalGroupCfg dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}

void CDlgConferenceParam::OnBtnTermManCfg()
{
	CDlgMCUTerminalManageCfg dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}

void CDlgConferenceParam::OnBtnGetAbility()
{
	CDlgMCUAbilityDetect dlg;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.DoModal();
}





void CDlgConferenceParam::OnBnClickedBtnGkConfig()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgTerminalGkCfg dlg;
    dlg.DoModal();
}


void CDlgConferenceParam::OnBnClickedBtnGkServer()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgGKServer dlg;
    dlg.DoModal();
}


void CDlgConferenceParam::OnCbnSelchangeComboConferenceInput()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[64] = { 0 };
    int iIndex = m_comboConferenceInput.GetCurSel();
    DWORD dwNodeData = m_comboConferenceInput.GetItemData(iIndex);
    if (dwNodeData < g_struDeviceInfo[m_iDeviceIndex].iStartChan + g_struDeviceInfo[m_iDeviceIndex].iIPChanNum + g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum
        && dwNodeData >= g_struDeviceInfo[m_iDeviceIndex].iStartChan + g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum)
    {
        m_comboStreamType.ResetContent();
        g_StringLanType(szLan, "主码流", "Main stream");
        m_comboStreamType.InsertString(0, szLan);
        g_StringLanType(szLan, "子码流", "Sub stream");
        m_comboStreamType.InsertString(1, szLan);
        m_comboStreamType.SetCurSel(0);
    }
    else
    {
        m_comboStreamType.ResetContent();
        g_StringLanType(szLan, "主码流", "Main stream");
        m_comboStreamType.InsertString(0, szLan);
        g_StringLanType(szLan, "子码流", "Sub stream");
        m_comboStreamType.InsertString(1, szLan);
        g_StringLanType(szLan, "三码流", "Three stream");
        m_comboStreamType.InsertString(2, szLan);
        m_comboStreamType.SetCurSel(0);
    }
}
