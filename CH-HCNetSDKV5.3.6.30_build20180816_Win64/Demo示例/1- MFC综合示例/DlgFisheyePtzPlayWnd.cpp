// DlgFisheyePtzPlayWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DlgFisheyePtzPlayWnd.h"
#include "ClientDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CALLBACK g_DrawFun(LONG lRealHandle, HDC hDc, DWORD dwUser)
{  
	CDlgFisheyePtzPlayWnd* pDlg = (CDlgFisheyePtzPlayWnd*)(dwUser);
	if (pDlg != NULL)
	{
		pDlg->DrawFun(hDc);
	}
}
/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyePtzPlayWnd dialog


CDlgFisheyePtzPlayWnd::CDlgFisheyePtzPlayWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFisheyePtzPlayWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFisheyePtzPlayWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_lChannel = -1;
	m_iDevIndex = -1;
	m_lRealHandle = -1;

	m_pen.CreatePen(PS_SOLID,1,RGB(0,255,0));
}


void CDlgFisheyePtzPlayWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFisheyePtzPlayWnd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFisheyePtzPlayWnd, CDialog)
	//{{AFX_MSG_MAP(CDlgFisheyePtzPlayWnd)
		// NOTE: the ClassWizard will add message map macros here
		ON_WM_DESTROY()
		ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyePtzPlayWnd message handlers
BOOL CDlgFisheyePtzPlayWnd::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);

	return TRUE;
}

void CDlgFisheyePtzPlayWnd::OnDestroy()
{   
	StopRealPlay();
	CDialog::OnDestroy();
}

void CDlgFisheyePtzPlayWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if (bShow)
	{   
		CRect rcParent;
		GetParent()->GetWindowRect(&rcParent);

		CRect rcWindow;
		GetWindowRect(&rcWindow);

		MoveWindow(rcParent.right,rcParent.top,rcWindow.Width(),rcWindow.Height());
		StartRealPlay();
	}
	else
	{
		StopRealPlay();
	}
}

BOOL CDlgFisheyePtzPlayWnd::StartRealPlay()
{
	NET_DVR_CLIENTINFO struPlay;
	struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
	struPlay.lChannel 	= m_lChannel; 
	struPlay.lLinkMode 	= 0;
	struPlay.sMultiCastIP = "";	
	m_lRealHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE); 
	BOOL bRet = FALSE;
	if (m_lRealHandle < 0)
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
		AfxMessageBox("NET_DVR_RealPlay_V30 failed");		
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
		bRet = NET_DVR_RigisterDrawFun(m_lRealHandle, g_DrawFun, (DWORD)this);//DC Draw callback
	}
	return bRet;
}

BOOL CDlgFisheyePtzPlayWnd::StopRealPlay()
{
	BOOL bRet = FALSE;
    if (!NET_DVR_StopRealPlay(m_lRealHandle))
    {
       // g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRealPlay");
        bRet = FALSE;
    }
    else
    {
        //g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRealPlay");
		m_lRealHandle = -1;
        bRet = TRUE;
    }
	
    return bRet;
}

void CDlgFisheyePtzPlayWnd::SwitchChannel(LONG lChannel)
{
	if (m_lChannel == lChannel)
	{
		return;
	}
    
	StopRealPlay();
	if (IsWindowVisible())
	{   
	    m_lChannel = lChannel;
		StartRealPlay();
	}
}

void CDlgFisheyePtzPlayWnd::DrawFun(HDC hdc)
{
	SelectObject(hdc,m_pen);
	
	int nHCenter = m_rcPlayWnd.Width() / 2;
	int nVCenter = m_rcPlayWnd.Height() / 2;
	
	CPoint pt1(nHCenter - 10,nVCenter);
	CPoint pt2(nHCenter + 10,nVCenter);
	CPoint pt3(nHCenter,nVCenter - 10);
	CPoint pt4(nHCenter,nVCenter + 10);
	
	MoveToEx(hdc,pt1.x,pt1.y,NULL);
	LineTo(hdc,pt2.x,pt2.y);
	
	MoveToEx(hdc,pt3.x,pt3.y,NULL);
	LineTo(hdc,pt4.x,pt4.y);
}
