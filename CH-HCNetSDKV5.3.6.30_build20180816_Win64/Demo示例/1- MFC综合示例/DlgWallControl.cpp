// DlgWallControl.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWallControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWallControl dialog


CDlgWallControl::CDlgWallControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWallControl::IDD, pParent)
    , m_dwSubboard(0)
{
	//{{AFX_DATA_INIT(CDlgWallControl)
	m_bySerialNo = 0;
	m_dwX = 0;
	m_dwY = 0;
	//}}AFX_DATA_INIT
}


void CDlgWallControl::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgWallControl)
    DDX_Control(pDX, IDC_COMBVIDEOWALL_WCONTROL_COLORTYPE, m_CmColorType);
    DDX_Control(pDX, IDC_COMB_VIDEOWALL_WCONTROL_WIDTH, m_CmWidth);
    DDX_Control(pDX, IDC_COMB_VIDEOWALL_WCONTROL_WALLNO, m_CmWallNo);
    DDX_Control(pDX, IDC_COMB_VIDEOWALL_WCONTROL_SERIALPROTOCOL, m_CmSerialPro);
    DDX_Control(pDX, IDC_COMB_VIDEOWALL_WCONTROL_POSITIONTYPE, m_CmPosType);
    DDX_Control(pDX, IDC_COMB_VIDEOWALL_WCONTROL_PADJUST, m_CmPosAjd);
    DDX_Control(pDX, IDC_COMB_VIDEOWALL_WCONTROL_OPERATOR, m_CmOperator);
    DDX_Control(pDX, IDC_COMB_VIDEOWALL_WCONTROL_INPUTESOURCE, m_CmInputSource);
    DDX_Control(pDX, IDC_COMB_VIDEOWALL_WCONTROL_HEIGHT, m_CmHeight);
    DDX_Control(pDX, IDC_COMB_VIDEOWALL_WCONTROL_CADJUST, m_CmColorAdj);
    DDX_Text(pDX, IDC_EDT_VIDEOWALL_WCONTROL_SERIALNO, m_bySerialNo);
    DDX_Text(pDX, IDC_EDT_VIDEOWALL_WCONTROL_XCOORDINATE, m_dwX);
    DDX_Text(pDX, IDC_EDT_VIDEOWALL_WCONTROL_YCOORDINATE, m_dwY);
    DDX_Text(pDX, IDC_EDIT_SUBBOARD_NO, m_dwSubboard);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWallControl, CDialog)
	//{{AFX_MSG_MAP(CDlgWallControl)
	ON_BN_CLICKED(IDC_BUT_VIDEOWALL_WCONTROL_SET, OnButWcontrolSet)
	ON_CBN_SELCHANGE(IDC_COMB_VIDEOWALL_WCONTROL_OPERATOR, OnSelchangeOperator)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWallControl message handlers

BOOL CDlgWallControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitVaildWallNo(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWallControl::OnButWcontrolSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_SCREEN_CONTROL_V41 ScreenControl={0}; 
    UpdateControlStru(&ScreenControl); 
    char szLan[128] = {0}; 
    if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_CONTROL_SCREEN, &ScreenControl, sizeof(ScreenControl)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CONTROL_SCREEN");
        g_StringLanType(szLan, "发送控制命令失败", "Failed to send control command");
        sprintf(szLan, "%s. Error Code %d", szLan, NET_DVR_GetLastError());
        MessageBox(szLan); 
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CONTROL_SCREEN ");
	}	
}

void  CDlgWallControl::SetWallRange(BYTE byMax, BYTE byMin)
{
    m_byMaxWallNo = byMax; 
    m_byMinWallNo = byMin; 
}

void  CDlgWallControl::InitVaildWallNo()
{
//     NET_DVR_VIDEOWALLDISPLAYMODE struDisplayMode = {0}; 
//     struDisplayMode.dwSize = sizeof(struDisplayMode);
//     DWORD dwRet;  
//     m_CmWallNo.ResetContent(); 
//     BYTE bySelWallNo = m_byWallNo; 
//     DWORD dwMarkIndex =0; 
//     char szlan[10]; 
//     //轮询查询墙
//     int i=0; 
//     for (i=m_byMinWallNo; i<m_byMaxWallNo; i++)
//     {    
//         if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYMODE, i, &struDisplayMode, sizeof(struDisplayMode), &dwRet))
//         {
//             sprintf(szlan, "%d", i); 
//             int itemIndex = m_CmWallNo.AddString(szlan);
//             m_CmWallNo.SetItemData(itemIndex, i); 
//             if ( bySelWallNo == i)
//             {
//                 dwMarkIndex = itemIndex; 
//             }
//         }
//     }
//     if (i!=m_byMinWallNo)
//     {
//         m_CmWallNo.SetCurSel(dwMarkIndex); 
//     }
}


BOOL  CDlgWallControl::UpdateControlStru(LPNET_DVR_SCREEN_CONTROL_V41 lpStru)
 {
    UpdateData(TRUE); 
    if ( lpStru == NULL)
    {
        return false; 
    }
    memset(lpStru, 0, sizeof(*lpStru));
    lpStru->dwSize = sizeof(*lpStru);
    lpStru->byWallNo = m_CmWallNo.GetCurSel() + 1;
    lpStru->byProtocol = m_CmSerialPro.GetCurSel()+1;
    lpStru->struRect.dwXCoordinate = m_dwX; 
    lpStru->struRect.dwYCoordinate = m_dwY; 
    lpStru->struRect.dwWidth = m_CmWidth.GetCurSel() *BASEWIDTH; 
    lpStru->struRect.dwHeight = m_CmHeight.GetCurSel() *BASEHEIGHT; 
    lpStru->dwCommand = m_CmOperator.GetCurSel()+1;
    memset(& (lpStru->struControlParam), 0, sizeof(lpStru->struControlParam)); 
    lpStru->byDevNo = 1;
    lpStru->bySubboardNo = m_dwSubboard;
    lpStru->bySerialNo = m_bySerialNo;
    switch (lpStru->dwCommand)
    {
    case 1:
    case 2:
        //开关操作，不需要赋值
        break; 

    case 3:
        lpStru->struControlParam.struInputCtrl.byInputSourceType = m_CmInputSource.GetCurSel(); 
        break; 
    case 4:
        lpStru->struControlParam.struDisplayCtrl.byColorType = m_CmColorType.GetCurSel() + 1; 
        lpStru->struControlParam.struDisplayCtrl.byScale = (m_CmColorAdj.GetCurSel() == 0)? 0xff:1; 
        break; 
    case 5:
        lpStru->struControlParam.struPositionCtrl.byPositionType = m_CmPosType.GetCurSel() + 1; 
        lpStru->struControlParam.struPositionCtrl.byScale = (m_CmPosAjd.GetCurSel() == 0)? 0xff:1; 
        break; 
    default:
        ;
    }
    return TRUE; 
}

void CDlgWallControl::OnSelchangeOperator() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    BYTE byCommand = m_CmOperator.GetCurSel()+1;
    switch (byCommand)
    {
    case 1:
    case 2:
       //所有操作不能选择
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_INPUTESOURCE)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMBVIDEOWALL_WCONTROL_COLORTYPE)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_CADJUST)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_POSITIONTYPE)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_PADJUST)->EnableWindow(FALSE);
       break; 
    case 3:
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_INPUTESOURCE)->EnableWindow(TRUE);
       GetDlgItem(IDC_COMBVIDEOWALL_WCONTROL_COLORTYPE)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_CADJUST)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_POSITIONTYPE)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_PADJUST)->EnableWindow(FALSE);  
       break;
    case 4:
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_INPUTESOURCE)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMBVIDEOWALL_WCONTROL_COLORTYPE)->EnableWindow(TRUE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_CADJUST)->EnableWindow(TRUE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_POSITIONTYPE)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_PADJUST)->EnableWindow(FALSE);
       break; 

    case 5:
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_INPUTESOURCE)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMBVIDEOWALL_WCONTROL_COLORTYPE)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_CADJUST)->EnableWindow(FALSE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_POSITIONTYPE)->EnableWindow(TRUE);
       GetDlgItem(IDC_COMB_VIDEOWALL_WCONTROL_PADJUST)->EnableWindow(TRUE);
       break; 
    }
    UpdateData(FALSE); 
}
