// DlgRecordHostFrameCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostFrameCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostFrameCfg dialog


CDlgRecordHostFrameCfg::CDlgRecordHostFrameCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordHostFrameCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordHostFrameCfg)
		// NOTE: the ClassWizard will add member initialization here

    m_dwPicNo = 0;
    m_byFrameEnable = 0;

    m_byTopWidth = 0;
    m_byTopR = 0;
    m_byTopG = 0;
    m_byTopB = 0;

    m_byBottomWidth = 0;
    m_byBottomR = 0;
    m_byBottomG = 0;
    m_byBottomB = 0;

    m_byLeftWidth = 0;
    m_byLeftR = 0;
    m_byLeftG = 0;
    m_byLeftB = 0;

    m_byRightWidth = 0;
    m_byRightR = 0;
    m_byRightG = 0;
    m_byRightB = 0;

    memset(&m_struFrameCfg, 0, sizeof(m_struFrameCfg));
	//}}AFX_DATA_INIT
}


void CDlgRecordHostFrameCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordHostFrameCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
    DDX_Text(pDX, IDC_EDT_PIC_NO, m_dwPicNo);
    DDX_Control(pDX, IDC_COM_FRAME_ENABLE, m_comFrameEnable);

	DDX_Control(pDX, IDC_COM_TOP_WIDTH, m_comTopWidth);
	DDX_Control(pDX, IDC_COM_BOTTOM_WIDTH, m_comBottomWidth);
	DDX_Control(pDX, IDC_COM_LEFT_WIDTH, m_comLeftWidth);
	DDX_Control(pDX, IDC_COM_RIGHT_WIDTH, m_comRightWidth);

    DDX_Text(pDX, IDC_EDT_TOP_RED, m_byTopR);
    DDX_Text(pDX, IDC_EDT_TOP_GREEN, m_byTopG);
    DDX_Text(pDX, IDC_EDT_TOP_BLUE, m_byTopB);
    
    DDX_Text(pDX, IDC_EDT_BOTTOM_RED, m_byBottomR);
    DDX_Text(pDX, IDC_EDT_BOTTOM_GREEN, m_byBottomG);
    DDX_Text(pDX, IDC_EDT_BOTTOM_BLUE, m_byBottomB);

    DDX_Text(pDX, IDC_EDT_LEFT_RED, m_byLeftR);
    DDX_Text(pDX, IDC_EDT_LEFT_GREEN, m_byLeftG);
    DDX_Text(pDX, IDC_EDT_LEFT_BLUE, m_byLeftB);

    DDX_Text(pDX, IDC_EDT_RIGHT_RED, m_byRightR);
    DDX_Text(pDX, IDC_EDT_RIGHT_GREEN, m_byRightG);
    DDX_Text(pDX, IDC_EDT_RIGHT_BLUE, m_byRightB);
    

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecordHostFrameCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordHostFrameCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgRecordHostFrameCfg::OnInitDialog()
{
    CDialog::OnInitDialog();

    UpdateData(FALSE);

    m_comFrameEnable.SetCurSel(0);
    m_comTopWidth.SetCurSel(0);
    m_comBottomWidth.SetCurSel(0);
    m_comLeftWidth.SetCurSel(0);
    m_comRightWidth.SetCurSel(0);
    
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostFrameCfg message handlers

void CDlgRecordHostFrameCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    NET_DVR_FRAME_COND struFrameCond = {0};
    struFrameCond.dwSize = sizeof(struFrameCond);
    struFrameCond.dwPicNo = m_dwPicNo;

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struFrameCond;
    struCfg.dwCondSize = sizeof(struFrameCond);

    struCfg.lpOutBuffer = &m_struFrameCfg;
    struCfg.dwOutSize = sizeof(m_struFrameCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_FRAME_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FRAME_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FRAME_CFG");
    }

    m_byFrameEnable = m_struFrameCfg.byFrameEnable;
    m_comFrameEnable.SetCurSel(m_byFrameEnable);

    m_byTopWidth = m_struFrameCfg.struTopFrame.byFrameWide;
    m_comTopWidth.SetCurSel(m_byTopWidth/2);
    m_byTopR = m_struFrameCfg.struTopFrame.byRed;
    m_byTopG = m_struFrameCfg.struTopFrame.byGreen;
    m_byTopB = m_struFrameCfg.struTopFrame.byBlue;

    m_byBottomWidth = m_struFrameCfg.struBottomFrame.byFrameWide;
    m_comBottomWidth.SetCurSel(m_byBottomWidth/2);
    m_byBottomR = m_struFrameCfg.struBottomFrame.byRed;
    m_byBottomG = m_struFrameCfg.struBottomFrame.byGreen;
    m_byBottomB = m_struFrameCfg.struBottomFrame.byBlue;

    m_byLeftWidth = m_struFrameCfg.struLeftFrame.byFrameWide;
    m_comLeftWidth.SetCurSel(m_byLeftWidth/2);
    m_byLeftR = m_struFrameCfg.struLeftFrame.byRed;
    m_byLeftG = m_struFrameCfg.struLeftFrame.byGreen;
    m_byLeftB = m_struFrameCfg.struLeftFrame.byBlue;

    m_byRightWidth = m_struFrameCfg.struRightFrame.byFrameWide;
    m_comRightWidth.SetCurSel(m_byRightWidth/2);
    m_byRightR = m_struFrameCfg.struRightFrame.byRed;
    m_byRightG = m_struFrameCfg.struRightFrame.byGreen;
    m_byRightB = m_struFrameCfg.struRightFrame.byBlue;

    UpdateData(FALSE);
	
}

void CDlgRecordHostFrameCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    m_byFrameEnable = m_comFrameEnable.GetCurSel();
    m_struFrameCfg.byFrameEnable = m_byFrameEnable;
	m_struFrameCfg.dwSize = sizeof(m_struFrameCfg);
    NET_DVR_FRAME_COND struFrameCond = {0};
    struFrameCond.dwSize = sizeof(struFrameCond);
    struFrameCond.dwPicNo = m_dwPicNo;

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struFrameCond;
    struCfg.dwCondSize = sizeof(struFrameCond);

    m_byTopWidth = m_comTopWidth.GetCurSel() * 2;
    m_struFrameCfg.struTopFrame.byFrameWide = m_byTopWidth;
    m_struFrameCfg.struTopFrame.byRed = m_byTopR;
    m_struFrameCfg.struTopFrame.byGreen = m_byTopG;
    m_struFrameCfg.struTopFrame.byBlue = m_byTopB;

    m_byBottomWidth = m_comBottomWidth.GetCurSel() * 2;
    m_struFrameCfg.struBottomFrame.byFrameWide = m_byBottomWidth;
    m_struFrameCfg.struBottomFrame.byRed = m_byBottomR;
    m_struFrameCfg.struBottomFrame.byGreen = m_byBottomG;
    m_struFrameCfg.struBottomFrame.byBlue = m_byBottomB;

    m_byLeftWidth = m_comLeftWidth.GetCurSel() * 2;
    m_struFrameCfg.struLeftFrame.byFrameWide = m_byLeftWidth;
    m_struFrameCfg.struLeftFrame.byRed = m_byLeftR;
    m_struFrameCfg.struLeftFrame.byGreen = m_byLeftG;
    m_struFrameCfg.struLeftFrame.byBlue = m_byLeftB;

    m_byRightWidth = m_comRightWidth.GetCurSel() * 2;
    m_struFrameCfg.struRightFrame.byFrameWide = m_byRightWidth;
    m_struFrameCfg.struRightFrame.byRed = m_byRightR;
    m_struFrameCfg.struRightFrame.byGreen = m_byRightG;
    m_struFrameCfg.struRightFrame.byBlue = m_byRightB;

    struCfg.lpInBuffer = &m_struFrameCfg;
    struCfg.dwInSize = sizeof(m_struFrameCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_FRAME_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FRAME_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FRAME_CFG");
    }
	
}
