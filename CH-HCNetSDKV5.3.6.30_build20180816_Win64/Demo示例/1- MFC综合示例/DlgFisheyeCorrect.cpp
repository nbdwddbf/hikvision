// DlgFisheyeCorrect.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgFisheyeCorrect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyeCorrect dialog


CDlgFisheyeCorrect::CDlgFisheyeCorrect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFisheyeCorrect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFisheyeCorrect)
	//}}AFX_DATA_INIT
	m_dwCorrectType = 0;
	//m_dwMountType = ENUM_FEC_MOUNT_DESKTOP;
	m_bDragFishEyePTZ = FALSE;
	m_dwCorrectHandle = 0;
//	memset(&m_struFisheyeParam,0,sizeof(m_struFisheyeParam));
}


void CDlgFisheyeCorrect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFisheyeCorrect)
	DDX_Control(pDX, IDC_COMBO_MOUNT_TYPE, m_comboMountType);
	DDX_Control(pDX, IDC_COMBO_CORRECT_TYPE, m_comboCorrectType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFisheyeCorrect, CDialog)
	//{{AFX_MSG_MAP(CDlgFisheyeCorrect)
		// NOTE: the ClassWizard will add message map macros here
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_DESTROY()
		ON_WM_SETCURSOR()
		ON_CBN_SELCHANGE(IDC_COMBO_MOUNT_TYPE, OnCbnSelchangeComboMounttype)
	    ON_CBN_SELCHANGE(IDC_COMBO_CORRECT_TYPE,OnCbnSelchangeComboCorrecttype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyeCorrect message handlers
BOOL CDlgFisheyeCorrect::OnInitDialog()
{
	CDialog::OnInitDialog();
    InitUI();

	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);

	m_dlgFECWnd.Create(CDlgFisheyeFECWnd::IDD,this);

	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),NULL,NULL);
    
	/*
	if (!NET_DVR_FEC_Enable(m_lPlayHandle,TRUE))
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FEC_Enable");            
		return FALSE;
	}
	*/

	StartFECPlay();

	return TRUE;
}

void CDlgFisheyeCorrect::InitUI()
{
	m_comboCorrectType.ResetContent();
	m_comboMountType.ResetContent();
	/*
	char szLan[32] = "\0";
	g_StringLanType(szLan,"吸顶","Ceiling");
	m_comboMountType.InsertString(0,szLan);
	m_comboMountType.SetItemData(0,ENUM_FEC_MOUNT_CEILING);
	g_StringLanType(szLan,"桌面","Desktop");
	m_comboMountType.InsertString(1,szLan);
	m_comboMountType.SetItemData(1,ENUM_FEC_MOUNT_DESKTOP);
	g_StringLanType(szLan,"墙面","Wall");
	m_comboMountType.InsertString(2,szLan);
	m_comboMountType.SetItemData(2,ENUM_FEC_MOUNT_WALL);
	
	g_StringLanType(szLan,"原始图像","Original Image");
	m_comboCorrectType.InsertString(0,szLan);
	m_comboCorrectType.SetItemData(0,0);
	m_comboCorrectType.InsertString(1,_T("PTZ"));
	m_comboCorrectType.SetItemData(1,ENUM_FEC_CORRECT_PTZ);
	*/
	int i = 0;
	for (i = 0; i < m_comboCorrectType.GetCount(); i++)
	{
		if (m_comboCorrectType.GetItemData(i) == m_dwCorrectType)
		{
			m_comboCorrectType.SetCurSel(i);
			break;
		}
	}
	
	for (i = 0; i < m_comboMountType.GetCount(); i++)
	{
		if (m_comboMountType.GetItemData(i) == m_dwMountType)
		{
			m_comboMountType.SetCurSel(i);
			break;
		}
	}
	ArrangeCtrlPos();
}

void CDlgFisheyeCorrect::OnDestroy()
{   
	/*
	if (!NET_DVR_FEC_CloseCorrectHandle(m_lPlayHandle,m_dwCorrectHandle))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FEC_CloseCorrectHandle");            
	}

	if (!NET_DVR_FEC_Enable(m_lPlayHandle,FALSE))
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FEC_Enable");            
	}
	*/

	StopRealPlay();
	CDialog::OnDestroy();
}

BOOL CDlgFisheyeCorrect::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_bDragFishEyePTZ)
	{
		SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(32649)));
		return TRUE;
	}
	else
	{
		SetCursor(LoadCursor(NULL,IDC_ARROW));
	}
	return CDialog::OnSetCursor(pWnd,nHitTest,message);
}

void CDlgFisheyeCorrect::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags,point);
    /*
	if (!m_rcPlayWnd.PtInRect(point))
	{   
		return;
	}
	
	m_bDragFishEyePTZ = TRUE;
	PostMessage(WM_SETCURSOR,0,0);
	
	switch (m_dwCorrectType)
	{
	case ENUM_FEC_CORRECT_PTZ:
		{
			if (!m_dlgFECWnd.IsWindowVisible())
			{
				m_dlgFECWnd.ShowWindow(SW_SHOW);
				m_dlgFECWnd.SetRealHandle(m_lPlayHandle);
			}
		}
		break;
	}
	*/
}

void CDlgFisheyeCorrect::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags,point);

	m_bDragFishEyePTZ = FALSE;
	PostMessage(WM_SETCURSOR,0,0);
}

void CDlgFisheyeCorrect::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags,point);
    /*
	if (!(nFlags & MK_LBUTTON))
	{
		return;
	}
    
	if (!m_rcPlayWnd.PtInRect(point))
	{   
		m_bDragFishEyePTZ = FALSE;
		PostMessage(WM_SETCURSOR,0,0);
		return;
	}
	
	switch (m_dwCorrectType)
	{
	case ENUM_FEC_CORRECT_PTZ:
		{
			float fX = (float)(point.x- m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
			float fY = (float)(point.y- m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
			
			m_struFisheyeParam.struPTZParam.fX = fX;
			m_struFisheyeParam.struPTZParam.fY = fY;
			m_struFisheyeParam.dwUpdateType = ENUM_FEC_UPDATE_PTZPARAM;
			NET_DVR_FEC_SetParam(m_lPlayHandle,m_dwCorrectHandle,&m_struFisheyeParam);
		}
		break;
	}
	PostMessage(WM_SETCURSOR,0,0);
	*/
}


BOOL CDlgFisheyeCorrect::StartFECPlay()
{   
	/*
	int nShowFECWnd = SW_HIDE;
	int nShowPlayWnd = SW_HIDE;
	int nShowPLAYWndFEC = SW_HIDE;
	
	if (m_dwCorrectType == 0)
	{
		nShowPlayWnd = SW_SHOW;
	}
	else
	{
		if (m_dwCorrectType == ENUM_FEC_CORRECT_PTZ)
		{
			nShowFECWnd = SW_SHOW;
			nShowPlayWnd = SW_SHOW;
		}
		else if (m_dwCorrectType == ENUM_FEC_CORRECT_360 ||
			m_dwCorrectType == ENUM_FEC_CORRECT_180)
		{
			nShowPLAYWndFEC = SW_SHOW;
		}
	}
	
	GetDlgItem(IDC_PLAYWND)->ShowWindow(nShowPlayWnd);
	GetDlgItem(IDC_PLAYWND_FEC)->ShowWindow(nShowPLAYWndFEC);

	m_dlgFECWnd.ShowWindow(nShowFECWnd);
	
	if (m_dwCorrectType != 0)
	{   
		if (m_dwCorrectHandle > 0)
		{
			if (!NET_DVR_FEC_CloseCorrectHandle(m_lPlayHandle,m_dwCorrectHandle))
			{
			    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FEC_CloseCorrectHandle");          
				return FALSE;
			}
			m_dwCorrectHandle = 0;
		}

		if (!NET_DVR_FEC_GetCorrectHandle(m_lPlayHandle,FEC_MOUNT_TYPE_ENUM(m_dwMountType),FEC_CORRECT_TYPE_ENUM(m_dwCorrectType),&m_dwCorrectHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FEC_GetCorrectHandle"); 
			return FALSE;
		}

		
		if (!NET_DVR_FEC_GetParam(m_lPlayHandle,m_dwCorrectHandle,&m_struFisheyeParam))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FEC_GetParam"); 
			return FALSE;
		}
		
		HWND hWnd = NULL;
		if (m_dwCorrectType == ENUM_FEC_CORRECT_PTZ)
		{
			hWnd = m_dlgFECWnd.GetPlayWnd();
		}
		else
		{   
			hWnd = GetDlgItem(IDC_PLAYWND_FEC)->GetSafeHwnd();
		}

		if (!NET_DVR_FEC_SetWnd(m_lPlayHandle,m_dwCorrectHandle,hWnd))
		{   
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FEC_SetWnd"); 
			return FALSE;
		}
	}
	*/
	
	return TRUE;
}


void CDlgFisheyeCorrect::ArrangeCtrlPos()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	
	CRect rcSeperator;
	GetDlgItem(IDC_LINE_1)->GetWindowRect(&rcSeperator);
	ScreenToClient(&rcSeperator);
	
	CRect rcPlayWnd = CRect(rcClient.left,rcSeperator.bottom + 3,rcClient.right,rcClient.bottom);
	GetDlgItem(IDC_PLAYWND)->MoveWindow(rcPlayWnd);
	GetDlgItem(IDC_PLAYWND_FEC)->MoveWindow(rcPlayWnd);
}

void CDlgFisheyeCorrect::OnCbnSelchangeComboMounttype()
{
	int nCurSel = m_comboMountType.GetCurSel();
	if (nCurSel != CB_ERR)
	{
		m_dwMountType = m_comboMountType.GetItemData(nCurSel);
		StartFECPlay();
	}
}

void CDlgFisheyeCorrect::OnCbnSelchangeComboCorrecttype()
{
	int nCurSel = m_comboCorrectType.GetCurSel();
	if (nCurSel != CB_ERR)
	{
		m_dwCorrectType = m_comboCorrectType.GetItemData(nCurSel);
		StartFECPlay();
	}
}
