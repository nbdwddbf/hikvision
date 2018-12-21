// DlgFisheyeFECWnd.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgFisheyeFECWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyeFECWnd dialog
void CALLBACK g_fFEC_Callback(LONG lRealHandle,HDC hDC, DWORD dwWidth,DWORD dwHeight,void* pUser,void* pReserve1,void* pReserve2)
{
	CDlgFisheyeFECWnd* pDlg = (CDlgFisheyeFECWnd*)pUser;
	if (pDlg != NULL)
	{
		pDlg->DrawFun(hDC,dwWidth,dwHeight);
	}
}



CDlgFisheyeFECWnd::CDlgFisheyeFECWnd(CWnd* pParent /*=NULL*/)
: CDialog(CDlgFisheyeFECWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFisheyeFECWnd)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgFisheyeFECWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFisheyeFECWnd)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFisheyeFECWnd, CDialog)
//{{AFX_MSG_MAP(CDlgFisheyeFECWnd)
// NOTE: the ClassWizard will add message map macros here
ON_WM_SHOWWINDOW()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFisheyeFECWnd message handlers
BOOL CDlgFisheyeFECWnd::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);
	
	return TRUE;
}

HWND CDlgFisheyeFECWnd::GetPlayWnd()
{
	return GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
}

void CDlgFisheyeFECWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if (bShow)
	{   
		CRect rcParent;
		GetParent()->GetWindowRect(&rcParent);
		
		CRect rcWindow;
		GetWindowRect(&rcWindow);
		
		MoveWindow(rcParent.right,rcParent.top,rcWindow.Width(),rcWindow.Height());
	}
	
	CDialog::OnShowWindow(bShow,nStatus);
}

void CDlgFisheyeFECWnd::DrawFun(HDC hdc,DWORD dwWidth,DWORD dwHeight)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,255,0));
	SelectObject(hdc,pen);
	
	int nHCenter = 20;
	int nVCenter = 20;
	
	CPoint pt1(nHCenter - 15,nVCenter);
	CPoint pt2(nHCenter + 15,nVCenter);
	CPoint pt3(nHCenter,nVCenter - 15);
	CPoint pt4(nHCenter,nVCenter + 15);
	
	MoveToEx(hdc,pt1.x,pt1.y,NULL);
	LineTo(hdc,pt2.x,pt2.y);
	
	MoveToEx(hdc,pt3.x,pt3.y,NULL);
	LineTo(hdc,pt4.x,pt4.y);
}

void CDlgFisheyeFECWnd::SetRealHandle(LONG lRealHandle)
{

}