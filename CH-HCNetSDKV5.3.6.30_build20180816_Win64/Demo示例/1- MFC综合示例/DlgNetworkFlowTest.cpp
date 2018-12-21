// DlgNetworkFlowTest.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgNetworkFlowTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkFlowTest dialog
CDlgNetworkFlowTest* g_pFlowTest = NULL;

void __stdcall g_fFlowTestCallback(LONG lFlowHandle, LPNET_DVR_FLOW_INFO pFlowInfo, void *pUser)
{
    g_pFlowTest->SetFlowTestText(pFlowInfo);
}


CDlgNetworkFlowTest::CDlgNetworkFlowTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetworkFlowTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNetworkFlowTest)
	m_iInterval = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lHandle = -1;
    memset(&m_struFlowTestParam, 0, sizeof(m_struFlowTestParam));
}


void CDlgNetworkFlowTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNetworkFlowTest)
	DDX_Control(pDX, IDC_COMBO_CARD_INDEX, m_comboCardIndex);
	DDX_Text(pDX, IDC_EDIT_TIME, m_iInterval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNetworkFlowTest, CDialog)
	//{{AFX_MSG_MAP(CDlgNetworkFlowTest)
	ON_BN_CLICKED(IDC_BTN_FLOW_TEST, OnBtnFlowTest)
	ON_BN_CLICKED(IDC_BTN_STOP_TEST, OnBtnStopTest)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkFlowTest message handlers

void CDlgNetworkFlowTest::OnBtnFlowTest() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

	char szLan[128] = {0};
	m_struFlowTestParam.dwSize = sizeof(m_struFlowTestParam);
    m_struFlowTestParam.dwInterval = m_iInterval;
	m_struFlowTestParam.lCardIndex =m_comboCardIndex.GetItemData(m_comboCardIndex.GetCurSel());
    m_lHandle = StartNetworkFlowTest(m_struFlowTestParam, g_fFlowTestCallback, NULL);
    if (m_lHandle < 0)
    {
		g_StringLanType(szLan, "¿ªÊ¼ÍøÂçÁ÷Á¿¼ì²âÊ§°Ü", "Failed to start network flow test");
        AfxMessageBox(szLan);
    }
	else
	{
		GetDlgItem(IDC_STATIC_FLOW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_FLOWRECV)->ShowWindow(SW_SHOW);
	}
}

LONG CDlgNetworkFlowTest::StartNetworkFlowTest(NET_DVR_FLOW_TEST_PARAM &sturFlowTestParam, FLOWTESTCALLBACK fFlowtestCallback, void* pUser)
{
    LONG lHandle = -1;
    lHandle = NET_DVR_StartNetworkFlowTest(m_lServerID, &sturFlowTestParam, fFlowtestCallback, pUser);
    if (lHandle >=0 )
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StartNetworkFlowTest [%d]", lHandle);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartNetworkFlowTest");
    }
    return lHandle;
}


BOOL CDlgNetworkFlowTest::StopTest(LONG lHandle)
{
    if (NET_DVR_StopNetworkFlowTest(lHandle))
    {
		lHandle = -1;
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "succ stop network flow test");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "fail to stop network flow test");
        return FALSE;
    }
}

void CDlgNetworkFlowTest::OnBtnStopTest() 
{
	char szLan[128] = {0};

	if (!StopTest(m_lHandle))
	{
		g_StringLanType(szLan, "Í£Ö¹ÍøÂçÁ÷Á¿¼ì²âÊ§°Ü", "Failed to stop network flow test");
        AfxMessageBox(szLan);
	}
	else
	{
		GetDlgItem(IDC_STATIC_FLOW)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_FLOWRECV)->ShowWindow(SW_HIDE);
	}
}

BOOL CDlgNetworkFlowTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_pFlowTest = this;
	InitWnd();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNetworkFlowTest::InitWnd()
{
	m_comboCardIndex.ResetContent();
	int nIndex = 0;
	m_comboCardIndex.InsertString(nIndex, "eht 0");
	m_comboCardIndex.SetItemData(nIndex, 0);
	nIndex++;

	m_comboCardIndex.InsertString(nIndex, "eht 1");
	m_comboCardIndex.SetItemData(nIndex, 1);
	nIndex++;

	m_comboCardIndex.InsertString(nIndex, "eht 2");
	m_comboCardIndex.SetItemData(nIndex, 2);
	nIndex++;

	m_comboCardIndex.InsertString(nIndex, "eht 3");
	m_comboCardIndex.SetItemData(nIndex, 3);
	nIndex++;

	m_comboCardIndex.InsertString(nIndex, "bonding 0");
	m_comboCardIndex.SetItemData(nIndex, 0x80000000);
	nIndex++;

	m_comboCardIndex.SetCurSel(0);
	
	m_iInterval = 10;
}

void CDlgNetworkFlowTest::PostNcDestroy() 
{
    if (m_lHandle >= 0)
    {
        StopTest(m_lHandle);
    }
    
	CDialog::PostNcDestroy();
}

void CDlgNetworkFlowTest::SetFlowTestText(LPNET_DVR_FLOW_INFO pFlowInfo)
{
    CString str = "";
    str.Format("Send %d kbps",pFlowInfo->dwSendFlowSize);
    GetDlgItem(IDC_STATIC_FLOW)->SetWindowText(str);
	str.Format("Recv %d kbps",pFlowInfo->dwRecvFlowSize);
    GetDlgItem(IDC_STATIC_FLOWRECV)->SetWindowText(str);
}

void CDlgNetworkFlowTest::OnButtonExit() 
{
	if(m_lHandle!=-1)
	{
		NET_DVR_StopNetworkFlowTest(m_lHandle);
		m_lHandle = -1;
	}	
	CDialog::OnCancel();
}
