// DlgLcdMatrixSwitch.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLcdMatrixSwitch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdMatrixSwitch dialog


CDlgLcdMatrixSwitch::CDlgLcdMatrixSwitch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLcdMatrixSwitch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLcdMatrixSwitch)
	m_dwMatrixInput = 0;
	m_dwScreenIndex = 0;
	//}}AFX_DATA_INIT
}


void CDlgLcdMatrixSwitch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLcdMatrixSwitch)
	DDX_Control(pDX, IDC_LIST_IO_RELATION, m_listIoRelation);
	DDX_Text(pDX, IDC_EDIT_MATRIX_INPUT, m_dwMatrixInput);
	DDX_Text(pDX, IDC_EDIT_SCREEN_INDEX, m_dwScreenIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLcdMatrixSwitch, CDialog)
	//{{AFX_MSG_MAP(CDlgLcdMatrixSwitch)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_SWITCH, OnBtnSwitch)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdMatrixSwitch message handlers

BOOL CDlgLcdMatrixSwitch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    char szLan[64] = {0};

    memset(&m_struMatrixSwitchInfo, 0, sizeof(m_struMatrixSwitchInfo));
    memset(&m_struMatrixIoRelation, 0, sizeof(m_struMatrixIoRelation));

    m_struMatrixIoRelation.dwSize = sizeof(m_struMatrixIoRelation);
    m_struMatrixSwitchInfo.dwSize = sizeof(m_struMatrixSwitchInfo);

    m_listIoRelation.SetExtendedStyle(m_listIoRelation.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    g_StringLanType(szLan, "ÆÁÄ»Ë÷ÒýºÅ", "Screen index");
    m_listIoRelation.InsertColumn(0, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "¾ØÕóÊäÈëºÅ", "Matrix input No");
    m_listIoRelation.InsertColumn(1, szLan, LVCFMT_LEFT, 120, -1);
	
    OnBtnUpdate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLcdMatrixSwitch::OnBtnUpdate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[64] = {0};
    DWORD dwReturned = 0;

    if (!NET_DVR_GetDVRConfig(m_lUserId, NET_DVR_GET_EXTERNAL_MATRIX_RELATION, m_dwMatrixId, &m_struMatrixIoRelation, sizeof(m_struMatrixIoRelation), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_EXTERNAL_MATRIX_RELATION");
        g_StringLanType(szLan, "»ñÈ¡¹ØÁª×´Ì¬ÐÅÏ¢Ê§°Ü", "Get external matrix relation fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_EXTERNAL_MATRIX_RELATION");
        DrawList();
    }
}

void CDlgLcdMatrixSwitch::DrawList()
{
    m_listIoRelation.DeleteAllItems();

    int i = 0;
    CString cs;

    for (i = 0; i < 100; i++)
    {
        cs.Format("%d", i + 1);
        m_listIoRelation.InsertItem(i, cs, 0);
        cs.Format("%d", m_struMatrixIoRelation.dwIORelation[i]);
        m_listIoRelation.SetItemText(i, 1, cs);
    }

    UpdateData(FALSE);
}

void CDlgLcdMatrixSwitch::OnBtnSwitch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[64] = {0};

    m_struMatrixSwitchInfo.dwInputChan = m_dwMatrixInput;
    m_struMatrixSwitchInfo.dwOutputChan = m_dwScreenIndex | 0x01000000;
    m_struMatrixSwitchInfo.dwMatrixID = m_dwMatrixId;

    if (!NET_DVR_RemoteControl(m_lUserId, NET_DVR_SWITCH_MATRIX_IO, &m_struMatrixSwitchInfo, sizeof(m_struMatrixSwitchInfo)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SWITCH_MATRIX_IO");
        g_StringLanType(szLan, "¾ØÕóÇÐ»»Ê§°Ü", "Matrix switch fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SWITCH_MATRIX_IO");
    }
}

void CDlgLcdMatrixSwitch::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}
