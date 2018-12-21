// DlgVideoIntercomCallRoomCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomCallRoomCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomCallRoomCfg dialog


CDlgVideoIntercomCallRoomCfg::CDlgVideoIntercomCallRoomCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomCallRoomCfg::IDD, pParent)
    , m_csCalledName(_T(""))
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomCallRoomCfg)
	m_iFloorNumber = 0;
	m_nRoomNumber = 0;
	m_bCallManageCenter = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgVideoIntercomCallRoomCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgVideoIntercomCallRoomCfg)
    DDX_Control(pDX, IDC_COMBO_BUTTON_NUMBER, m_cmbButtonNumber);
    DDX_Text(pDX, IDC_EDIT_FLOOR_NUMBER, m_iFloorNumber);
    DDX_Text(pDX, IDC_EDIT_ROOM_NUMBER, m_nRoomNumber);
    DDX_Check(pDX, IDC_CHECK_CALL_MANAGE_CENTER, m_bCallManageCenter);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_CALLED_NAME, m_csCalledName);
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomCallRoomCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomCallRoomCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomCallRoomCfg message handlers

void CDlgVideoIntercomCallRoomCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    memset(&m_struCallRoomCfg,0,sizeof(m_struCallRoomCfg));

    DWORD dwReturn = 0;

    DWORD dwButtonNum = m_cmbButtonNumber.GetItemData(m_cmbButtonNumber.GetCurSel());
    if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_CALL_ROOM_CFG,dwButtonNum,&m_struCallRoomCfg,sizeof(m_struCallRoomCfg),&dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GET_CALL_ROOM_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_GET_CALL_ROOM_CFG");
    }

    m_iFloorNumber = m_struCallRoomCfg.nFloorNumber;
    m_nRoomNumber  = m_struCallRoomCfg.wRoomNumber;
	m_bCallManageCenter = m_struCallRoomCfg.byManageCenter;
    sprintf_s((LPSTR)(LPCTSTR)m_csCalledName, 64, "%s", m_struCallRoomCfg.byCalledName);
    UpdateData(FALSE);
}

void CDlgVideoIntercomCallRoomCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
  
    DWORD dwButtonNum = m_cmbButtonNumber.GetItemData(m_cmbButtonNumber.GetCurSel());
    m_struCallRoomCfg.nFloorNumber = (SHORT)m_iFloorNumber;
    m_struCallRoomCfg.wRoomNumber = m_nRoomNumber;
	m_struCallRoomCfg.byManageCenter = m_bCallManageCenter;
    memcpy_s(m_struCallRoomCfg.byCalledName, 64, (LPSTR)(LPCTSTR)m_csCalledName, 64);
    if (!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_CALL_ROOM_CFG,dwButtonNum,&m_struCallRoomCfg,sizeof(m_struCallRoomCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SET_CALL_ROOM_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SET_CALL_ROOM_CFG");
    }
    
    UpdateData(FALSE);
}

BOOL CDlgVideoIntercomCallRoomCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbButtonNumber.ResetContent();
    DWORD dwIndex = 0;
    char szLan[128] = {0};
    for (int i = 0; i< 4; i++)
    {
        sprintf(szLan,"%d",i+1);
        m_cmbButtonNumber.AddString(szLan);
        m_cmbButtonNumber.SetItemData(dwIndex,i+1);
        dwIndex++;
    }

    m_cmbButtonNumber.SetCurSel(0);

    OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
