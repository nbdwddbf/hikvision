// DlgVcaEnterRegion.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaEnterRegion.h"
#include "math.h"
#include "gdiplus/GdiPlus.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaEnterRegion dialog
CDlgVcaEnterRegion* g_pIVMSEnterAreaSet = NULL;
void CALLBACK DrawIVMSATMEnterRegionShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 255, 255));

	g_pIVMSEnterAreaSet->F_DrawFun(lRealHandle, hDc, dwUser);
}

CDlgVcaEnterRegion::CDlgVcaEnterRegion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaEnterRegion::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaEnterRegion)
	m_bDrawPolygon = FALSE;
	m_bActive = FALSE;
	//}}AFX_DATA_INIT
    m_lPUServerID = -1;
	memset(&m_struPolygon, 0 ,sizeof(NET_VCA_POLYGON));
	memset(&m_struVCAEnterRegion, 0, sizeof(NET_VCA_ENTER_REGION));
    memset(&m_struPuStream, 0, sizeof(m_struPuStream));
}

void CDlgVcaEnterRegion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaEnterRegion)
	DDX_Check(pDX, IDC_CHK_DRAW_POLYGON, m_bDrawPolygon);
	DDX_Check(pDX, IDC_CHECK_ACTIVE, m_bActive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaEnterRegion, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaEnterRegion)
	ON_BN_CLICKED(IDC_CHK_DRAW_POLYGON, OnChkDrawPolygon)
	ON_BN_CLICKED(IDC_CHECK_ACTIVE, OnCheckActive)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaEnterRegion message handlers


void CDlgVcaEnterRegion::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
	if (m_struVCAEnterRegion.byEnable)
	{
		COLORREF color;
		color = RGB(255, 255, 0);//Yellow
		F_DrawFrame(lPlayHandle, hDc, dwUser, color);
	}
}

void CDlgVcaEnterRegion::F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color)
{
    UNREFERENCED_PARAMETER(dwUser);
    UNREFERENCED_PARAMETER(lRealHandle);
    
    using namespace Gdiplus;
    Graphics graphics(hDc);
    SolidBrush  brush(Color(50, 0, 0, 0));
    brush.SetColor(Color(50, GetRValue(color), GetGValue(color), GetBValue(color)));
    
    POINT point[VCA_MAX_POLYGON_POINT_NUM] = {0};
    
	CPen DrawPen;
	unsigned int i;
	
	DrawPen.CreatePen(PS_SOLID, 1, color);
	SetTextColor(hDc,color);
	
	HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
	MoveToEx(hDc, (int)(m_struPolygon.struPos[0].fX*m_rcWndRect.Width()), \
		(int)(m_struPolygon.struPos[0].fY*m_rcWndRect.Height()), NULL);
	
	for(i=1; i<m_struPolygon.dwPointNum; i++)
	{
        
		LineTo(hDc, (int)(m_struPolygon.struPos[i].fX*m_rcWndRect.Width()),\
			(int)(m_struPolygon.struPos[i].fY*m_rcWndRect.Height()));
		//if the new line is crossed with existing line, redraw.
		if(i>=MIN_PNT_NUM && !m_bMouseMove && IsCrossLine(&m_struPolygon))
		{
			char szLan[128] = {0};
			g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Polygon edges are not adjacent is intersect");
			AfxMessageBox(szLan);
			m_dwPosNum--;
			m_struPolygon.dwPointNum--;
			break;
		}
		if(!m_bCloseIn)
		{
			m_bDrawPolygon = TRUE;
		}
	}
	
    for (i=0; i<(int)m_struPolygon.dwPointNum ; i++)
    {
        if (i == VCA_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(m_struPolygon.struPos[i].fX*m_rcWndRect.Width());
        point[i].y = (int)(m_struPolygon.struPos[i].fY*m_rcWndRect.Height());
    }
	//close the polygon automatically if the 10th points is drawn
	if(VCA_MAX_POLYGON_POINT_NUM == i && !m_bMouseMove)
	{
		if (IsValidArea(&m_struPolygon))
		{
            graphics.FillPolygon(&brush, (Point *)point, m_struPolygon.dwPointNum);
            
			LineTo(hDc, (int)(m_struPolygon.struPos[0].fX*m_rcWndRect.Width()), (int)(m_struPolygon.struPos[0].fY*m_rcWndRect.Height()));	
			m_bCloseIn = TRUE;
		}else//redraw
		{
			m_bCloseIn = FALSE;
			m_bNeedRedraw = TRUE;
			m_struPolygon.dwPointNum--;
			m_dwPosNum--;
		}
		//check if it's a valid region
    }
    else if(m_struPolygon.dwPointNum>2 && m_bCloseIn)
	{
		if (IsValidArea(&m_struPolygon))
		{
            graphics.FillPolygon(&brush, (Point *)point, m_struPolygon.dwPointNum);
            
			LineTo(hDc, (int)(m_struPolygon.struPos[0].fX*m_rcWndRect.Width()),(int)(m_struPolygon.struPos[0].fY*m_rcWndRect.Height()));
		}else
		{
			m_bNeedRedraw = TRUE;
			m_bCloseIn = FALSE;
		}
	}
	
	SelectObject(hDc, pOldPen);
	DeleteObject(DrawPen);

}

BOOL CDlgVcaEnterRegion::IsValidArea(NET_VCA_POLYGON *alarm_region)
{
	if(alarm_region == NULL)
	{
		return FALSE;
	}
	// check if all points are in same line
	if (F_IsStraightLine(alarm_region))
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "所有点在同一直线上，不能组成多边形!",\
			"All points have been in the same line, not able to form the polygon");
		MessageBox(szLan);
		return FALSE;
	}
	
	// check if the line of start point and end point is crossed by existing line.
	if (F_IsACrossLine(alarm_region))
	{
		char szLan[128] = {0};
		g_StringLanType(szLan,"终点和起点的连线与已有的直线相交，不能组成有效的多边形!", \
			"There are straight-line intersection, can not be composed of an effective polygon");
		MessageBox(szLan);
		return FALSE;
	}
	
	return TRUE;
}

BOOL CDlgVcaEnterRegion::F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2)
{
	NET_VCA_POINT p1_q1, q2_q1, p2_q1, q1_p1, p2_p1, q2_p1;       // vectorial difference；；
	float z1, z2, z3, z4;
	BOOL  line_cross = FALSE;
	
	// p1 - q1;
	p1_q1.fX = p1.fX - q1.fX;
	p1_q1.fY = p1.fY - q1.fY;
	
	// q2 - q1;
	q2_q1.fX = q2.fX - q1.fX;
	q2_q1.fY = q2.fY - q1.fY;
	
	// p2 - q1;
	p2_q1.fX = p2.fX - q1.fX;
	p2_q1.fY = p2.fY - q1.fY;
	
	// cross product1 (p1 - q1) × (q2 - q1)；
	z1 = p1_q1.fX * q2_q1.fY - q2_q1.fX * p1_q1.fY; 
	
	// cross product2 (q2 - q1) × (p2 - q1)；
	z2 = q2_q1.fX * p2_q1.fY - p2_q1.fX * q2_q1.fY;
	
	// q1 - p1;
	q1_p1.fX = q1.fX - p1.fX;
	q1_p1.fY = q1.fY - p1.fY;
	
	// p2 - p1;
	p2_p1.fX = p2.fX - p1.fX;
	p2_p1.fY = p2.fY - p1.fY;
	
	// q2 - p1;
	q2_p1.fX = q2.fX - p1.fX;
	q2_p1.fY = q2.fY - p1.fY;
	
	// cross product3 (q1 - p1) × (p2 - p1)；
	z3 = q1_p1.fX * p2_p1.fY - p2_p1.fX * q1_p1.fY;
	
	// cross product4 (p2 - p1) × (q2 - p1);
	z4 = p2_p1.fX * q2_p1.fY - q2_p1.fX * p2_p1.fY;
	
	
	// check if two lines are crossed;
	if( ((z1 >= 0.0f && z2 >= 0.0f) || (z1 < 0.0f && z2 < 0.0f)) && 
		((z3 >= 0.0f && z4 >= 0.0f) || (z3 < 0.0f && z4 < 0.0f)))
	{
		line_cross = TRUE;	
	}else
	{
		line_cross = FALSE;
	}
	
	return line_cross;
}

BOOL CDlgVcaEnterRegion::F_IsACrossLine(NET_VCA_POLYGON *alarm_region)
{
	if(alarm_region == NULL)
	{
		return FALSE;
	}
	unsigned int i;
	DWORD	 nPointTotal;
	NET_VCA_POINT *pPointArray;
	NET_VCA_POINT *pPntArr;
	BOOL    bCrossLine;
	
	pPointArray = alarm_region->struPos;
	nPointTotal = alarm_region->dwPointNum;
	bCrossLine  = FALSE;
	
	// polygon has 3 vertexes
	if (nPointTotal == VCA_MAX_POLYGON_POINT_NUM)
	{
		bCrossLine = FALSE;
	}
	//more than 3
	else
	{
		pPntArr = new NET_VCA_POINT[nPointTotal];
		if (pPntArr == NULL)
		{
			char szLan[128] = {0};
			g_StringLanType(szLan, "内存分配失败!","Memory allocation failure!");
			AfxMessageBox(szLan);
			exit(EXIT_FAILURE);
		}
		
		//  copy vertexes to an array, which length is 1 more than vertexes
		for (i = 0; i < nPointTotal; i++)
		{
			pPntArr[i] = pPointArray[i];
		}
		//      pPntArr[nPointTotal] = pPointArray[0];
		
		for(i = 0; i < nPointTotal - 1; i++)
		{
			
			if (F_LineCrossDetect(pPntArr[0], pPntArr[nPointTotal - 1], pPntArr[i], pPntArr[i + 1]))
			{
				bCrossLine = TRUE;
			}			
		} 
		delete [] pPntArr;
	}
	return bCrossLine;
}


BOOL CDlgVcaEnterRegion::IsCrossLine(NET_VCA_POLYGON *alarm_region)
{
	if(alarm_region == NULL)
	{
		return FALSE;
	}
	unsigned int i, j;
	DWORD nPointTotal = 0;
	NET_VCA_POINT *pPointArray = NULL;
	NET_VCA_POINT *pPntArr = NULL;
	BOOL    bCrossLine;
	
	pPointArray = alarm_region->struPos;
	nPointTotal = alarm_region->dwPointNum;
	bCrossLine  = FALSE;
	
	// polygon has 3 vertexes
	if (nPointTotal >= 3)
	{
		bCrossLine = FALSE;
	}
	// more than 3
	else
	{
		pPntArr = new NET_VCA_POINT[nPointTotal];
		if (pPntArr == NULL)
		{
			char szLan[128] = {0};
			g_StringLanType(szLan, "内存分配失败!","Memory allocation failure!");
			AfxMessageBox(szLan);
			exit(EXIT_FAILURE);
		}
		
		// copy vertexes to an array, which length is 1 more than vertexes
		for (i = 0; i < nPointTotal; i++)
		{
			pPntArr[i] = pPointArray[i];
		}
		
		for(i = 0; i < nPointTotal - 3; i++)
		{
			for (j = i + 2; j < nPointTotal-1; j++)
			{
				
				if (F_LineCrossDetect(pPntArr[i], pPntArr[i + 1], pPntArr[j], pPntArr[j + 1]))
				{
					bCrossLine = TRUE;
				}			
			}
		}
		if (pPntArr != NULL)
		{
			delete [] pPntArr;
		}
	}
	return bCrossLine;
}

BOOL CDlgVcaEnterRegion::F_IsStraightLine(NET_VCA_POLYGON *alarm_region)
{
	if(alarm_region == NULL)
	{
		return FALSE;
	}
	unsigned int i = 0;
	BOOL         bStraightLine;
	float        fSlope;
	float        fDistance;
	float        fCoefficient;
	float        fOffset;
	DWORD		 nPointTotal;
	NET_VCA_POINT *pPointArray;
	int          nXOffset;
	int          nYOffset;
	
	pPointArray = alarm_region->struPos;
	nPointTotal = alarm_region->dwPointNum;
	
	nXOffset = (int)(pPointArray[0].fX - pPointArray[1].fX);
	nYOffset = (int)(pPointArray[0].fY - pPointArray[1].fY);
	bStraightLine = TRUE;
	
	// check all points compose a vertical  line
	if (0 == nXOffset)
	{
		for (i = 2; i < nPointTotal; i++)
		{
			if (pPointArray[0].fX != pPointArray[i].fX)
			{
				bStraightLine = FALSE;
				break;
			}
		}
	}
	
	//  check all points compose a horizontal line
	if (0 == nYOffset)
	{
		for (i = 2; i < nPointTotal; i++)
		{
			if (pPointArray[0].fY != pPointArray[i].fY)
			{
				bStraightLine = FALSE;
				break;
			}                 
		}
	}
	
	// check all points compose bias
	if ((0 != nXOffset) && (0 != nYOffset))
	{
		// slope
		fSlope  = 1.0f * nYOffset / nXOffset;
		// intercept of calculating slope intercept form Equation
		fOffset = pPointArray[0].fY - fSlope * pPointArray[1].fX;
		// Coefficient for calculating distance between point to line. 
		fCoefficient = (float)sqrt(1.0 + fSlope * fSlope);
		
		for (i = 2; i < nPointTotal; i ++)
		{
			// calculating the distance to the line consist of point 0 and point 1. 
			fDistance = (float)fabs(fSlope * pPointArray[i].fX - pPointArray[i].fY + fOffset)/fCoefficient;
			
			// if one distance is larger than 0, the polygon is valid. 
			if ((fDistance - 0.0f) > 0.000001f)
			{
				bStraightLine = FALSE;
				break;
			}
		}		
	}
	
	return bStraightLine;	
}

BOOL CDlgVcaEnterRegion::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CPoint pt(0,0);
	CRect  rcWnd(0,0,0,0);
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
	GetCursorPos(&pt);
	CString strTemp = _T("");
	int i=0;
	BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;

	switch(pMsg->message) 
	{
	case WM_LBUTTONDOWN:
		if(m_bDrawPolygon && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if(PtInRect(&rcWnd,pt))
			{	
				if(m_bNeedRedraw)
				{			
					if(m_bCloseIn)
					{
						m_dwPosNum = 0;
						m_struPolygon.dwPointNum = m_dwPosNum;		
					}
					if(m_dwPosNum>9)
					{
						char szLan[128] = {0};
						g_StringLanType(szLan,"多边形顶点不能超过10个!","Polygon vertex can not be over 10!");
						AfxMessageBox(szLan);
						return TRUE;
					}
					if((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPolygon.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPolygon.struPos[m_dwPosNum-1].fX-0.01\
						&& (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPolygon.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPolygon.struPos[m_dwPosNum-1].fY-0.01)
					{
						char szLan[128] = {0};
						g_StringLanType(szLan,"多边形顶点不能超过10个!","Polygon vertex can not be over 10!");
						AfxMessageBox(szLan);
						return TRUE;
					}
					m_bCloseIn = FALSE;
					m_bMouseMove = FALSE;
					m_struPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
					m_struPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
					m_dwPosNum++;
					m_struPolygon.dwPointNum = m_dwPosNum;			
				}
				else
				{
					return TRUE;
				}
			}
		}//Draw the first coordinate of minimum rectangle
		break;
	case WM_MOUSEMOVE:
		if(m_bDrawPolygon && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if(PtInRect(&rcWnd,pt))
			{
				if(m_dwPosNum > 9)
				{
					return TRUE;
				}
				if( m_bNeedRedraw && !m_bCloseIn)
				{
					m_bMouseMove = TRUE;
					m_struPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
					m_struPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
					m_struPolygon.dwPointNum = m_dwPosNum+1;				
				}
			}
		}
		break;
	case WM_RBUTTONDOWN://right click to close
		if(m_bDrawPolygon && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if(PtInRect(&rcWnd,pt))
			{
				if(m_dwPosNum > 9)
				{
					return TRUE;
				}
				for(i=0; i<(int)m_dwPosNum; i++)
				{
					if(m_struPolygon.struPos[i].fX != m_struPolygon.struPos[i+1].fX)
					{
						bXOneLine = FALSE;
						break;
					}
				}
				for(i = 0; i < (int)m_dwPosNum; i++)
				{
					if(m_struPolygon.struPos[i].fY != m_struPolygon.struPos[i+1].fY)
					{
						bYOneLine = FALSE;
						break;
					}
				}
				bOneLine = bXOneLine||bYOneLine;
				if(bOneLine)
				{
					char szlan[128] = {0};
					g_StringLanType(szlan, "所画点成一线，无法构成区域!","Can not constitute a regional");
					AfxMessageBox(szlan);
					return TRUE;
				}
				if( m_bNeedRedraw && !m_bCloseIn)
				{
					if(m_bMouseMove)
					{
						m_bMouseMove = FALSE;
						m_struPolygon.dwPointNum--;
					}
					m_bCloseIn = TRUE;
				}
			}
		}
		else if(m_bDrawPolygon)
		{
			if(PtInRect(&rcWnd,pt))
			{
				if(m_dwPosNum == 0)
				{
					return TRUE;
				}
				if( m_bNeedRedraw && !m_bCloseIn)
				{
					m_struPolygon.dwPointNum--;
					m_dwPosNum--;
				}
				else if( m_bNeedRedraw && m_bCloseIn)
				{
					m_struPolygon.dwPointNum = 0;
					m_dwPosNum = 0;
					m_bCloseIn = FALSE;
				}
			}
		}
		break;
	default:
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgVcaEnterRegion::OnChkDrawPolygon() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bDrawPolygon)
	{
		m_bNeedRedraw = TRUE;//redraw polygon
		UpdateData(FALSE);
	}
	else
	{
		if (m_bNeedRedraw && !m_bCloseIn)
		{
			if (m_bMouseMove && m_struPolygon.dwPointNum > 0)
			{
				m_bMouseMove = FALSE;
				m_struPolygon.dwPointNum--;
			}
			m_bCloseIn = TRUE;
		}		
	}
}


BOOL CDlgVcaEnterRegion::OnInitDialog() 
{
	CDialog::OnInitDialog();

    g_pIVMSEnterAreaSet = this;
    if (IDS52XX != g_struDeviceInfo[m_iDevIndex].iDeviceType)
    {
        if (!GetEnterRegion())
        {
            AfxMessageBox("Fail to get enter region");
            //return FALSE;
        }
    }
	
	m_bActive = m_struVCAEnterRegion.byEnable;

	GetDlgItem(IDC_CHK_DRAW_POLYGON)->EnableWindow(m_bActive);
	memcpy(&m_struPolygon, &m_struVCAEnterRegion.struPolygon, sizeof(NET_VCA_POLYGON));
	UpdateData(false);

	//area for preview
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWndRect);
	m_lPlayHandle = StartPlay(); 
	
//	BOOL bRet = FALSE;
	if (m_lPlayHandle < 0)
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
		AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
	}
	if (m_bActive && m_lPlayHandle >= 0)
	{
		OnChkDrawPolygon();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaEnterRegion::OnOK() 
{
	// TODO: Add extra validation here
	memcpy(&m_struVCAEnterRegion.struPolygon, &m_struPolygon, sizeof(NET_VCA_POLYGON));
    
    if (!IDS52XX != g_struDeviceInfo[m_iDevIndex].iDeviceType)
    {
        if (!SetEnterRegion())
        {
            AfxMessageBox("Fail to set enter region");
        }
        else
        {
            AfxMessageBox("Succ to set enter region");
        }
        return;
    }

	CDialog::OnOK();
}

void CDlgVcaEnterRegion::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

void CDlgVcaEnterRegion::OnCheckActive() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struVCAEnterRegion.byEnable = (BYTE)m_bActive;
	GetDlgItem(IDC_CHK_DRAW_POLYGON)->EnableWindow(m_bActive);		
}

BOOL CDlgVcaEnterRegion::GetEnterRegion()
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VCA_ENTER_REGION, m_iChannel, &m_struVCAEnterRegion, sizeof(m_struVCAEnterRegion), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_ENTER_REGION");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_ENTER_REGION");
        bRet = TRUE;
    }
    return bRet;    
}

BOOL CDlgVcaEnterRegion::SetEnterRegion()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VCA_ENTER_REGION, m_iChannel, &m_struVCAEnterRegion, sizeof(m_struVCAEnterRegion)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_ENTER_REGION");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_ENTER_REGION");
        bRet = TRUE;
    }

    return bRet;
}

void CDlgVcaEnterRegion::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
    StopPlay();
    
    g_pIVMSEnterAreaSet = NULL;

	CDialog::PostNcDestroy();
}

LONG CDlgVcaEnterRegion::StartPlay()
{
    //  如果能去前端流设备 
    if (GetPuStreamCfg(m_struPuStream))
    {
        NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
        
        m_lPUServerID = NET_DVR_Login_V30(m_struPuStream.struDevChanInfo.struIP.sIpV4, m_struPuStream.struDevChanInfo.wDVRPort,
            (char*)m_struPuStream.struDevChanInfo.sUserName, (char*)m_struPuStream.struDevChanInfo.sPassword, &struDeviceInfo);
        if (m_lPUServerID < 0)
        {
            AfxMessageBox("Fail to login front device");
            return m_lPUServerID;
        }
        
        NET_DVR_CLIENTINFO struPlay;
        struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
        struPlay.lChannel 	= m_struPuStream.struDevChanInfo.byChannel; 
        struPlay.lLinkMode 	= 0;
        struPlay.sMultiCastIP = "";	
        
        m_lPlayHandle = NET_DVR_RealPlay_V30(m_lPUServerID, &struPlay, NULL, NULL, TRUE); 
        
        BOOL bRet = FALSE;
        if (m_lPlayHandle < 0)
        {
            g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
            AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
        }
        else
        {
            g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
            bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawIVMSATMEnterRegionShow, 0);//DC Draw callback
        }
        return m_lPlayHandle;
    }
    else // 到设备去取流预览
    {
        NET_DVR_CLIENTINFO struPlay;
        struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
        struPlay.lChannel 	= m_iChannel; 
        struPlay.lLinkMode 	= 0;
        struPlay.sMultiCastIP = "";	
        
        m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE); 
        BOOL bRet = FALSE;
        if (m_lPlayHandle < 0)
        {
            g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
            AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
        }
        else
        {
            g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
            bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawIVMSATMEnterRegionShow, 0);//DC Draw callback
        }
        return m_lPlayHandle;
    } 
}

BOOL CDlgVcaEnterRegion::StopPlay()
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
    
    if (m_lPUServerID >= 0)
    {
        NET_DVR_Logout_V30(m_lPUServerID);
        m_lPUServerID = -1;
    }
    return TRUE;
}

BOOL CDlgVcaEnterRegion::GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG,m_iChannel, &struPUStream, sizeof(struPUStream), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PU_STREAMCFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PU_STREAMCFG");
        return FALSE;
    }
}
