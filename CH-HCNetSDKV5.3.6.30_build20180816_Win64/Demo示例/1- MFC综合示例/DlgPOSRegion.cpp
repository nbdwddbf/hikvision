// DlgPOSRegion.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPOSRegion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDlgPOSRegion dialog


CDlgPOSRegion::CDlgPOSRegion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPOSRegion::IDD, pParent)
	//, m_pPreviewPlay(NULL)
	, m_bLBDown(FALSE)
	, m_iZoomType(-1)
	, m_bEdge(false)
	, m_bInRect(false)
	, m_bStartZoom(false)
	, m_bGetClient(false)
	, m_iFunPtrIndex(-1)
	, m_iDeviceID(-1)
	, m_iCameraID(-1)
	, m_bStart(false)
	, m_nDeviceIndex(-1)
{
	//{{AFX_DATA_INIT(CDlgPOSRegion)
		// NOTE: the ClassWizard will add member initialization here
//	m_brush.CreateSolidBrush(RGB(10, 10, 10));
//	memset(&m_stPOSDisplay, 0, sizeof(POSDISPLAY));
	//}}AFX_DATA_INIT
}


void CDlgPOSRegion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPOSRegion)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgPOSRegion, CDialog)
	//{{AFX_MSG_MAP(CDlgPOSRegion)
	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPOSRegion message handlers

void CALLBACK DrawFun_POS(long nport, HDC hDc,LONG nUser)
{
	CDlgPOSRegion*pDlg = (CDlgPOSRegion*)nUser;
	
	CDC *pDC = CDC::FromHandle(hDc);
	pDlg->DrawRect(pDC);
}

void CDlgPOSRegion::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// TODO: Add your message handler code here
	SetDoubleScreen();
	
}

void CDlgPOSRegion::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bGetClient)
	{
		GetClientRect(&m_rcClient);
		m_bGetClient = m_bGetClient;
	}
    if (m_bInRect)
    {
		int xoffset = point.x - m_ptMoveSt.x;
		int yoffset = point.y - m_ptMoveSt.y;

		int nWidth = m_rcRegion.Width();
		int nHeight = m_rcRegion.Height();

		if (xoffset < 0)
		{
			m_rcRegion.left += xoffset;
			if(m_rcRegion.left <= 0)
			{
				m_rcRegion.left = 0;
				m_rcRegion.right = m_rcRegion.left + nWidth;
			}
			else
			{
				m_rcRegion.right += xoffset;
			}
		}
		else
		{
			m_rcRegion.right += xoffset;
			if(m_rcRegion.right > m_rcClient.Width())
			{
				m_rcRegion.right = m_rcClient.Width();
				m_rcRegion.left = m_rcRegion.right - nWidth;
			}
			else
			{
				m_rcRegion.left += xoffset;
			}
		}
		
		if (yoffset < 0)
		{
			m_rcRegion.top += yoffset;
			if(m_rcRegion.top < 0)
			{
				m_rcRegion.top = 0;
				m_rcRegion.bottom = m_rcRegion.top + nHeight;
			}
			else
			{
				m_rcRegion.bottom += yoffset;
			}
		}
		else
		{
			m_rcRegion.bottom += yoffset;
			if(m_rcRegion.bottom > m_rcClient.Height())
			{
				m_rcRegion.bottom = m_rcClient.Height();
				m_rcRegion.top = m_rcRegion.bottom - nHeight;
			}
			else
			{
				m_rcRegion.top += yoffset;
			}
		}
		m_ptMoveSt = point;
    }
	else
	{
		if (m_bEdge)
		{
			if (m_bStartZoom)
			{
				int xoffset = point.x - m_ptZoomSt.x;
				int yoffset = point.y - m_ptZoomSt.y;
				m_ptZoomSt = point;
				switch(m_iZoomType)
				{
				case _LEFT_TOP:/*左上*/
					m_rcRegion.left += xoffset;
					m_rcRegion.top  += yoffset;
					if(m_rcRegion.left <= 0)
					{
						m_rcRegion.left = 0;
					}
					if(m_rcRegion.left + 16 >= m_rcRegion.right)
					{
						m_rcRegion.left = m_rcRegion.right - 16;
					}

					if(m_rcRegion.top <= 0)
					{
						m_rcRegion.top = 0;
					}
					if (m_rcRegion.top + 16 >= m_rcRegion.bottom)
					{
						m_rcRegion.top = m_rcRegion.bottom - 16;
					}
					break;

				case _LEFT_BOTTOM:/*左下*/
					m_rcRegion.left += xoffset;
					m_rcRegion.bottom  += yoffset;
					if(m_rcRegion.left <= 0)
					{
						m_rcRegion.left = 0;
					}
					if(m_rcRegion.left + 16 >= m_rcRegion.right)
					{
						m_rcRegion.left = m_rcRegion.right - 16;
					}

					if (m_rcRegion.bottom >= m_rcClient.Height())
					{
						m_rcRegion.bottom = m_rcClient.Height();
					}
					if (m_rcRegion.bottom - 16 <= m_rcRegion.top)
					{
						m_rcRegion.bottom = m_rcRegion.top + 16;
					}
	
					break;
				case _RIGHT_TOP:/*右上*/
					m_rcRegion.top += yoffset;
					m_rcRegion.right+= xoffset;
					if (m_rcRegion.right >= m_rcClient.Width())
					{
						m_rcRegion.right = m_rcClient.Width();
					}
					
					if (m_rcRegion.right - 16 <= m_rcRegion.left)
					{
						m_rcRegion.right = m_rcRegion.left + 16;
					}
					if(m_rcRegion.top <= 0)
					{
						m_rcRegion.top = 0;
					}
					if (m_rcRegion.top + 16 >= m_rcRegion.bottom)
					{
						m_rcRegion.top = m_rcRegion.bottom - 16;
					}
					break;
				case _RIGHT_BOTTOM:/*右下*/
					m_rcRegion.right+= xoffset;
					m_rcRegion.bottom  += yoffset;
					if (m_rcRegion.right >= m_rcClient.Width())
					{
						m_rcRegion.right = m_rcClient.Width();
					}
					if (m_rcRegion.right - 16 <= m_rcRegion.left)
					{
						m_rcRegion.right = m_rcRegion.left + 16;
					}

					if (m_rcRegion.bottom >= m_rcClient.Height())
					{
						m_rcRegion.bottom = m_rcClient.Height();
					}
					if (m_rcRegion.bottom - 16 <= m_rcRegion.top)
					{
						m_rcRegion.bottom = m_rcRegion.top + 16;
					}
					break;
				case _LEFT_POS:/*左*/
					m_rcRegion.left += xoffset;
					if(m_rcRegion.left <= 0)
					{
						m_rcRegion.left = 0;
					}
					if(m_rcRegion.left + 16 >= m_rcRegion.right)
					{
						m_rcRegion.left = m_rcRegion.right - 16;
					}
					break;
				case _TOP_POS:/*上*/
					m_rcRegion.top += yoffset;
					if(m_rcRegion.top <= 0)
					{
						m_rcRegion.top = 0;
					}
					if (m_rcRegion.top + 16 >= m_rcRegion.bottom)
					{
						m_rcRegion.top = m_rcRegion.bottom - 16;
					}
					break;
				case _RIGHT_POS:/*右*/
					m_rcRegion.right+= xoffset;
					if(m_rcRegion.right >= m_rcClient.Width())
					{
						m_rcRegion.right = m_rcClient.Width();
					}

					if (m_rcRegion.right - 16 <= m_rcRegion.left)
					{
						m_rcRegion.right = m_rcRegion.left + 16;
					}
					break;
				case _BOTTOM_POS:/*下*/
					m_rcRegion.bottom  += yoffset;
					if (m_rcRegion.bottom > m_rcClient.Height())
					{
						m_rcRegion.bottom = m_rcClient.Height();
					}
					if (m_rcRegion.bottom - 16 <= m_rcRegion.top)
					{
						m_rcRegion.bottom = m_rcRegion.top + 16;
					}
					break;
				default:
					break;
				}

				CDialog::OnMouseMove(nFlags, point);
				return;
			}
			else
			{
				ReadyForZoom(point);
			}
		}
		else
		{//本次移动前，鼠标不在当前选中矩形的8个关键点上

			//判断当前鼠标的位置是否在当前选中矩形的8个关键点上，并改变鼠标状态
			ReadyForZoom(point);

		}
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CDlgPOSRegion::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_bLBDown = false;
	if (m_bEdge)
	{
		m_bEdge = false;
		m_bStartZoom = false;
		m_iZoomType = -1;
		::ReleaseCapture();
		::SetCursor(::LoadCursor(NULL, IDC_ARROW));
		CDialog::OnLButtonUp(nFlags, point);
		return;
	}
	if (m_bInRect)
	{
		m_bInRect = false;
		::SetCursor(::LoadCursor(NULL, IDC_ARROW));
		CDialog::OnLButtonUp(nFlags, point);
		return;
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgPOSRegion::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bLBDown = true;
	if (m_bEdge)
	{
		m_bStartZoom = true;
		m_ptZoomSt = point;
		switch(m_iZoomType)
		{
		case _LEFT_TOP:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
			break;
		case _LEFT_BOTTOM:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENESW));
			break;
		case _RIGHT_TOP:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENESW));
			break;
		case _RIGHT_BOTTOM:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
			break;
		case _LEFT_POS:
			::SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
			break;
		case _TOP_POS:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENS));
			break;
		case _RIGHT_POS:
			::SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
			break;
		case _BOTTOM_POS:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENS));
			break;
		default:
			break;
		}
		this->SetCapture();
		CDialog::OnLButtonDown(nFlags, point);
		return;
	}
	
	if (m_rcRegion.PtInRect(point))
	{
		m_bInRect = true;
	}
	else
	{
		m_bInRect = false;
	}
	if (m_bInRect)
	{
		m_ptMoveSt = point;
		::SetCursor(m_hCurDrag);
		CDialog::OnLButtonDown(nFlags, point);
		return;
	}

	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CDlgPOSRegion::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	HINSTANCE hResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDC_CURSOR_HAND1),RT_GROUP_CURSOR);
//	m_hCurDrag = (HCURSOR)::LoadImage(hResource,MAKEINTRESOURCE(IDC_CURSOR_HAND1),IMAGE_CURSOR,0,0,0);
	
// 	if (m_iDeviceID >=0)
// 	{
// 		StartPreview(m_iDeviceID, 0);
// 		m_pPreviewPlay->RegisterDrawFun(DrawFun_POS,(LONG)this);
// 	}
	
	GetClientRect(&m_rcClient);
	m_rcClient = m_rcRegion;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPOSRegion::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

int CDlgPOSRegion::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CDlgPOSRegion::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgPOSRegion::SetDoubleScreen(void)
{
// 	HMONITOR hMonitor = MonitorFromWindow(m_hWnd,MONITOR_DEFAULTTONEAREST);
// 	if (hMonitor)
// 	{   
// 		// get the display monitor index
// 		int iIndex = theApp.m_MultiScreen.GetDeviceIndex(hMonitor); 
// 		if ((iIndex >= 0) && (iIndex != m_nDeviceIndex))
// 		{
// // 			if (m_pPreviewPlay->SetDDrawDevice(iIndex))
// // 			{
// // 				m_nDeviceIndex = iIndex;
// // 			}
// 		}
// 	}
}


void CDlgPOSRegion::ReadyForZoom(CPoint point)
{
	m_iZoomType = -1;
	m_bEdge = false;
	//左上角
	CRect rcLT(m_rcRegion.left-4,m_rcRegion.top-4,m_rcRegion.left,m_rcRegion.top);
	//左边框中部
	CRect rcLeftCenter(m_rcRegion.left-4,(m_rcRegion.bottom+m_rcRegion.top)/2-2,m_rcRegion.left,(m_rcRegion.bottom+m_rcRegion.top)/2+2);
	//左下角
	CRect rcLB(m_rcRegion.left-4,m_rcRegion.bottom,m_rcRegion.left,m_rcRegion.bottom+4);
	//上边框的中部
	CRect rcTopCenter((m_rcRegion.left + m_rcRegion.right)/2-2,m_rcRegion.top-4,(m_rcRegion.left + m_rcRegion.right)/2+2,m_rcRegion.top);
	//右上角
	CRect rcRT(m_rcRegion.right,m_rcRegion.top-4,m_rcRegion.right+4,m_rcRegion.top);
	//右边框的中部
	CRect rcRightCenter(m_rcRegion.right,(m_rcRegion.bottom+m_rcRegion.top)/2-2,m_rcRegion.right+4,(m_rcRegion.bottom+m_rcRegion.top)/2+2);
	//y右下角
	CRect rcRB(m_rcRegion.right,m_rcRegion.bottom,m_rcRegion.right+4,m_rcRegion.bottom+4);
	//下边框的中部
	CRect rcBotCenter((m_rcRegion.left + m_rcRegion.right)/2-2,m_rcRegion.bottom,(m_rcRegion.left + m_rcRegion.right)/2+2,m_rcRegion.bottom+4);
	if(rcLT.PtInRect(point))
	{
		::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
		m_iZoomType = _LEFT_TOP;
	}
	else if(rcLB.PtInRect(point))
	{
		::SetCursor(::LoadCursor(NULL,IDC_SIZENESW));
		m_iZoomType = _LEFT_BOTTOM;
	}
	else if(rcRT.PtInRect(point))
	{
		::SetCursor(::LoadCursor(NULL,IDC_SIZENESW));
		m_iZoomType = _RIGHT_TOP;
	}
	else if(rcRB.PtInRect(point))
	{
		::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
		m_iZoomType = _RIGHT_BOTTOM;
	}
	else if(rcLeftCenter.PtInRect(point))
	{
		::SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
		m_iZoomType = _LEFT_POS;
	}
	else if(rcTopCenter.PtInRect(point))
	{
		::SetCursor(::LoadCursor(NULL,IDC_SIZENS));
		m_iZoomType = _TOP_POS;
	}
	else if(rcRightCenter.PtInRect(point))
	{
		::SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
		m_iZoomType = _RIGHT_POS;
	}
	else if(rcBotCenter.PtInRect(point))
	{
		::SetCursor(::LoadCursor(NULL,IDC_SIZENS));
		m_iZoomType = _BOTTOM_POS;
	}
	
	if (m_iZoomType >=0)
	{
		m_bEdge = true;
	}
	else
	{
		m_bEdge = false;
	}
}

BOOL CDlgPOSRegion::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (m_bLBDown)
	{
		switch(m_iZoomType)
		{
		case _LEFT_TOP:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
			break;
			
		case _LEFT_BOTTOM:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENESW));
			break;
		case _RIGHT_TOP:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENESW));
			break;
		case _RIGHT_BOTTOM:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENWSE));
			break;
		case _LEFT_POS:
			::SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
			break;
		case _TOP_POS:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENS));
			break;
		case _RIGHT_POS:
			::SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
			break;
		case _BOTTOM_POS:
			::SetCursor(::LoadCursor(NULL,IDC_SIZENS));
			break;
		default:
			break;
		}
		return TRUE;
	}
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CDlgPOSRegion::DrawRect(CDC *pDC)
{
	if (NULL == pDC)
	{
		return;
	}
	//八个特殊的点
	CRect rcLT(m_rcRegion.left-4,m_rcRegion.top-4,m_rcRegion.left,m_rcRegion.top);
	CRect rcLeftCenter(m_rcRegion.left-4,(m_rcRegion.bottom+m_rcRegion.top)/2-2,m_rcRegion.left,(m_rcRegion.bottom+m_rcRegion.top)/2+2);
	CRect rcLB(m_rcRegion.left-4,m_rcRegion.bottom,m_rcRegion.left,m_rcRegion.bottom+4);
	CRect rcTopCenter((m_rcRegion.left + m_rcRegion.right)/2-2,m_rcRegion.top-4,(m_rcRegion.left + m_rcRegion.right)/2+2,m_rcRegion.top);
	CRect rcRT(m_rcRegion.right,m_rcRegion.top-4,m_rcRegion.right+4,m_rcRegion.top);
	CRect rcRightCenter(m_rcRegion.right,(m_rcRegion.bottom+m_rcRegion.top)/2-2,m_rcRegion.right+4,(m_rcRegion.bottom+m_rcRegion.top)/2+2);
	CRect rcRB(m_rcRegion.right,m_rcRegion.bottom,m_rcRegion.right+4,m_rcRegion.bottom+4);
	CRect rcBotCenter((m_rcRegion.left + m_rcRegion.right)/2-2,m_rcRegion.bottom,(m_rcRegion.left + m_rcRegion.right)/2+2,m_rcRegion.bottom+4);
	pDC->FillSolidRect (rcLT, RGB(0,0,255));
	pDC->FillSolidRect (rcLB, RGB(0,0,255));
	pDC->FillSolidRect (rcRT, RGB(0,0,255));
	pDC->FillSolidRect (rcRB, RGB(0,0,255));
	pDC->FillSolidRect (rcLeftCenter, RGB(0,0,255));
	pDC->FillSolidRect (rcTopCenter, RGB(0,0,255));
	pDC->FillSolidRect (rcRightCenter, RGB(0,0,255));
	pDC->FillSolidRect (rcBotCenter, RGB(0,0,255));
	
	CPen pen(PS_SOLID, 1, RGB(0,255,0));
	int OldRop2 = pDC->SetROP2(R2_XORPEN);
	CPen *pOldPen = pDC->SelectObject(&pen);
	if( !m_rcRegion.IsRectNull() )
	{
		pDC->MoveTo(m_rcRegion.left,m_rcRegion.top);
		pDC->LineTo(m_rcRegion.right,m_rcRegion.top);
		pDC->LineTo(m_rcRegion.right,m_rcRegion.bottom);
		pDC->LineTo(m_rcRegion.left,m_rcRegion.bottom);
		pDC->LineTo(m_rcRegion.left,m_rcRegion.top);
	}
	

	
	
	pDC->SetBkMode(TRANSPARENT);
//	pDC->SetTextColor(theApp.m_FontColor[m_stPOSDisplay.byFontColor]);
	
	CString szText = "please set pos Area"; ///*"请拖动设置POS数据显示区域"*/theApp.LoadStringByID(IDS_POS_TEST_DATA);
	int nTextLen = szText.GetLength();
	pDC->DrawText(szText, nTextLen, m_rcRegion, DT_LEFT | DT_TOP);
	

	
	pDC->SetROP2(OldRop2);
	if (pOldPen)
	{
		pDC->SelectObject(pDC);
	}
}

void CDlgPOSRegion::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	SetDoubleScreen();
}


BOOL CDlgPOSRegion::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message) 
	{
	case WM_KEYDOWN:
		if (pMsg->wParam == VK_RETURN)
		{
			////TRACE("Message RETURN ......");
			return TRUE;
		}
		if(pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
		break;
	case WM_SYSKEYDOWN:
		//屏蔽点击键盘Alt + F4组合按钮，关闭对话框
		if(pMsg->wParam == VK_F4)
		{
			return TRUE;
		}
		break;
	default:
		break;
	}
// 	if( theApp.m_bLock)
// 	{
// 		switch(pMsg->message)
// 		{
// 		case WM_LBUTTONUP:
// 		case WM_LBUTTONDBLCLK:
// 		case WM_LBUTTONDOWN:
// 		case WM_RBUTTONDBLCLK:
// 		case WM_RBUTTONDOWN:
// 		case WM_RBUTTONUP:
// 		case WM_KEYDOWN:
// 		case WM_SYSKEYDOWN:
// 			return TRUE;
// 		default:
// 			break;
// 		}
// 	}
	return CDialog::PreTranslateMessage(pMsg);
}