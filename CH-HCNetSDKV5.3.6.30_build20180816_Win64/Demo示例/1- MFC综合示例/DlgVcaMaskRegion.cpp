// DlgVcaMaskRegion.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaMaskRegion.h"
#include "math.h"
#include "gdiplus/GdiPlus.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaMaskRegion dialog
CDlgVcaMaskRegion *g_pIVMSMaskAreaSet = NULL;

void CALLBACK DrawIVMSMaskRegionShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 255, 255));
	g_pIVMSMaskAreaSet->F_DrawFun(lRealHandle, hDc, dwUser);
}

CDlgVcaMaskRegion::CDlgVcaMaskRegion(CWnd* pParent /*=NULL*/)
: CDialog(CDlgVcaMaskRegion::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaMaskRegion)
	m_bDrawPolygon = FALSE;
	m_bActive1 = FALSE;
	m_bActive2 = FALSE;
	m_bActive3 = FALSE;
	m_bActive4 = FALSE;
	//}}AFX_DATA_INIT
	m_bPolygon1 = FALSE;
	m_bPolygon2 = FALSE;
	m_bPolygon3 = FALSE;
	m_bPolygon4 = FALSE;
	m_iPolygonId = -1;
	m_dwPosNum = 0;
	m_lPlayHandle = -1;
	memset(&m_struPolygon[0], 0 ,MAX_MASK_REGION_NUM*sizeof(NET_VCA_POLYGON));
	memset(&m_struMaskRegionList, 0, sizeof(NET_VCA_MASK_REGION_LIST));
	
	memset(&m_bNeedRedraw[0], 0, MAX_MASK_REGION_NUM*sizeof(BOOL));
	memset(&m_bMouseMove[0], 0, MAX_MASK_REGION_NUM*sizeof(BOOL));
	memset(&m_bCloseIn[0], 0, MAX_MASK_REGION_NUM*sizeof(BOOL));

    m_lPUServerID = -1;
    memset(&m_struPuStream, 0, sizeof(m_struPuStream));
}

void CDlgVcaMaskRegion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaMaskRegion)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Check(pDX, IDC_CHK_DRAW_POLYGON, m_bDrawPolygon);
	DDX_Check(pDX, IDC_CHECK_MASK_ACTIVE1, m_bActive1);
	DDX_Check(pDX, IDC_CHECK_MASK_ACTIVE2, m_bActive2);
	DDX_Check(pDX, IDC_CHECK_MASK_ACTIVE3, m_bActive3);
	DDX_Check(pDX, IDC_CHECK_MASK_ACTIVE4, m_bActive4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgVcaMaskRegion, CDialog)
//{{AFX_MSG_MAP(CDlgVcaMaskRegion)
ON_BN_CLICKED(IDC_CHK_DRAW_POLYGON, OnChkDrawPolygon)
//ON_EN_CHANGE(IDC_EDIT_MASK_NUM, OnChangeEditMaskNum)
//ON_BN_CLICKED(IDC_CHECK_MASK_ACTIVE, OnCheckMaskActive)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_RADIO_POLYGON1, OnRadioPolygon1)
ON_BN_CLICKED(IDC_RADIO_POLYGON2, OnRadioPolygon2)
ON_BN_CLICKED(IDC_RADIO_POLYGON3, OnRadioPolygon3)
ON_BN_CLICKED(IDC_RADIO_POLYGON4, OnRadioPolygon4)
ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaMaskRegion message handlers

void CDlgVcaMaskRegion::OnChkDrawPolygon() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}



BOOL CDlgVcaMaskRegion::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreCreateWindow(cs);
}

BOOL CDlgVcaMaskRegion::PreTranslateMessage(MSG* pMsg) 
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
				if(m_bNeedRedraw[m_iPolygonId])
				{			
					if(m_bCloseIn[m_iPolygonId])
					{
						m_dwPosNum = 0;
						m_struPolygon[m_iPolygonId].dwPointNum = m_dwPosNum;		
					}
					if(m_dwPosNum>9)
					{
						char szLan[128] = {0};
						g_StringLanType(szLan,"多边形顶点不能超过10个!","Polygon vertex can not be over 10!");
						AfxMessageBox(szLan);
						return TRUE;
					}
					if((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPolygon[m_iPolygonId].struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPolygon[m_iPolygonId].struPos[m_dwPosNum-1].fX-0.01\
						&& (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPolygon[m_iPolygonId].struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPolygon[m_iPolygonId].struPos[m_dwPosNum-1].fY-0.01)
					{
						char szLan[128] = {0};
						g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
						AfxMessageBox(szLan);
						return TRUE;
					}
					m_bCloseIn[m_iPolygonId] = FALSE;
					m_bMouseMove[m_iPolygonId] = FALSE;
					m_struPolygon[m_iPolygonId].struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
					m_struPolygon[m_iPolygonId].struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
					m_dwPosNum++;
					m_struPolygon[m_iPolygonId].dwPointNum = m_dwPosNum;
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
				if( m_bNeedRedraw[m_iPolygonId] && !m_bCloseIn[m_iPolygonId])
				{
					m_bMouseMove[m_iPolygonId] = TRUE;
					m_struPolygon[m_iPolygonId].struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
					m_struPolygon[m_iPolygonId].struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
					m_struPolygon[m_iPolygonId].dwPointNum = m_dwPosNum+1;				
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
				for(i = 0; i < (int)m_dwPosNum; i++)
				{
					if(m_struPolygon[m_iPolygonId].struPos[i].fX != m_struPolygon[m_iPolygonId].struPos[i+1].fX)
					{
						bXOneLine = FALSE;
						break;
					}
				}
				for(i = 0; i < (int)m_dwPosNum; i++)
				{
					if(m_struPolygon[m_iPolygonId].struPos[i].fY != m_struPolygon[m_iPolygonId].struPos[i+1].fY)
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
				if( m_bNeedRedraw[m_iPolygonId] && !m_bCloseIn[m_iPolygonId])
				{
					if(m_bMouseMove[m_iPolygonId])
                    { 
						m_bMouseMove[m_iPolygonId] = FALSE;
						m_struPolygon[m_iPolygonId].dwPointNum--;
					}
					m_bCloseIn[m_iPolygonId] = TRUE;
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
				if( m_bNeedRedraw[m_iPolygonId] && !m_bCloseIn[m_iPolygonId])
				{
					m_struPolygon[m_iPolygonId].dwPointNum--;
					m_dwPosNum--;
				}
				else if( m_bNeedRedraw[m_iPolygonId] && m_bCloseIn[m_iPolygonId])
				{
					m_struPolygon[m_iPolygonId].dwPointNum = 0;
					m_dwPosNum = 0;
					m_bCloseIn[m_iPolygonId] = FALSE;
				}
			}
		}
		break;
	default:
		break;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


BOOL CDlgVcaMaskRegion::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	g_AddChanInfoToComBox(m_cmbChannel, m_iDevIndex);

	m_iChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

    if (g_struDeviceInfo[m_iDevIndex].iDeviceType != IDS52XX)
    {
        if (!GetMaskRegion())
        {
            AfxMessageBox("Fail to  get mask region");
        }
    }


	g_pIVMSMaskAreaSet = this;
	int i = 0;
	for(i = 0;i<MAX_MASK_REGION_NUM; i++)
	{
		m_bNeedRedraw[i] = FALSE;//redraw polygon
		m_bCloseIn[i] = TRUE;//check if polygon is cloesd or not
	}
	
	
	m_bActive1 = m_struMaskRegionList.struMask[0].byEnable;
	m_bActive2 = m_struMaskRegionList.struMask[1].byEnable;
	m_bActive3 = m_struMaskRegionList.struMask[2].byEnable;
	m_bActive4 = m_struMaskRegionList.struMask[3].byEnable;

    for (i = 0; i < MAX_MASK_REGION_NUM; i++)
    {
        memcpy(&m_struPolygon[i], &m_struMaskRegionList.struMask[i].struPolygon, sizeof(NET_VCA_POLYGON));
    }
	UpdateData(FALSE);
	
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWndRect);
	//area from preview
    StartPlay();
	if (m_lPlayHandle < 0)
	{
		AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
	}
	
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaMaskRegion::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
    for (int i = 0; i <MAX_MASK_REGION_NUM; i++)
    {
        if (m_struPolygon[i].dwPointNum > 2)
        {
            memcpy(&m_struMaskRegionList.struMask[i].struPolygon, &m_struPolygon[i], sizeof(NET_VCA_POLYGON));
        }
    }

	m_struMaskRegionList.struMask[0].byEnable = (BYTE)m_bActive1;
	m_struMaskRegionList.struMask[1].byEnable = (BYTE)m_bActive2;
	m_struMaskRegionList.struMask[2].byEnable = (BYTE)m_bActive3;
	m_struMaskRegionList.struMask[3].byEnable = (BYTE)m_bActive4;

    if (g_struDeviceInfo[m_iDevIndex].iDeviceType != IDS52XX)
        
    {
        if (!SetMaskRegion())
        {
            AfxMessageBox("Fail to set mask region");
        }
        else
        {
            AfxMessageBox("Succ to set mask region");
        }
        return;
    }
    CDialog::OnOK();
}

void CDlgVcaMaskRegion::OnCancel() 
{
	// TODO: Add extra cleanup here

	CDialog::OnCancel();
}

void CDlgVcaMaskRegion::EnableDrawPolygon(BOOL Enable)
{
	// 	UpdateData(TRUE);
	// 	if (Enable)
	// 	{
	// 		BOOL bRet = FALSE;
	// // 		if (m_lPlayHandle < 0)
	// // 		{
	// // 			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
	// // 			AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
	// // 		}
	// //		else
	// 		{
	// 			LONG m_lPlayHandle = 0;
	// 			bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawATMMaskRegionShow, 0);//set DC draw callback
	// 		}
	// 
	// 	}
}

void CDlgVcaMaskRegion::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
	COLORREF color;
	color = RGB(255, 255, 0);//yellow
	F_DrawFrame(lPlayHandle, hDc, dwUser,  color);
}


void CDlgVcaMaskRegion::F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color)
{
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    
    for (int i = 0; i < MAX_MASK_REGION_NUM; i++)
    {
        if (i == m_iPolygonId)
        {
            struPolygonParam.color = RGB(244,62,0);
			struPolygonParam.bCloseIn = m_bCloseIn[i];
        }
        else
        {   
			struPolygonParam.bCloseIn = TRUE;
			struPolygonParam.color = RGB(255, 255, 0);
           
        }
        
        struPolygonParam.bMouseMove = FALSE;
		memcpy(&struPolygonParam.rcWnd, &m_rcWndRect, sizeof(m_rcWndRect));
        memcpy(&struPolygonParam.struVcaPolygon, &m_struPolygon[i], sizeof(struPolygonParam.struVcaPolygon));
		CDrawFun::DrawVcaPolygon(hDc, &struPolygonParam);
	}
}


BOOL CDlgVcaMaskRegion::IsCrossLine(NET_VCA_POLYGON *alarm_region)
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
	
	// // polygon should have 3 vertexes at least
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


void CDlgVcaMaskRegion::F_AddLabel(HDC hDc, DWORD dwRuleID)
{
}


BOOL CDlgVcaMaskRegion::IsValidArea(NET_VCA_POLYGON *alarm_region)
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



BOOL CDlgVcaMaskRegion::F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2)
{
	NET_VCA_POINT p1_q1, q2_q1, p2_q1, q1_p1, p2_p1, q2_p1;       // vectorial difference;
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
	
	//cross product4 (p2 - p1) × (q2 - p1);
	z4 = p2_p1.fX * q2_p1.fY - q2_p1.fX * p2_p1.fY;
	
	
	//  check if two lines are crossed；
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

BOOL CDlgVcaMaskRegion::F_IsACrossLine(NET_VCA_POLYGON *alarm_region)
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


BOOL CDlgVcaMaskRegion::F_IsStraightLine(NET_VCA_POLYGON *alarm_region)
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
	
	//check all points compose one vertical line
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
	
	// 	//check all points compose one horizontal line

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
		// intercept of calculating  slope intercept form Equation
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
BOOL CDlgVcaMaskRegion::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}


void CDlgVcaMaskRegion::OnChangeEditMaskNum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDlgVcaMaskRegion::OnCheckMaskActive() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDlgVcaMaskRegion::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here	
}

void CDlgVcaMaskRegion::OnRadioPolygon1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//	EnableDrawPolygon(m_bPolygon1);
	m_iPolygonId =0;
	m_dwPosNum = 0;
	// 	m_bPolygon2 = FALSE;
	// 	m_bPolygon3 =FALSE;
	// 	m_bPolygon4 =FALSE;
	// 	UpdateData(FALSE);
	m_bDrawPolygon = TRUE;
	UpdateData(FALSE);
	if(m_bDrawPolygon)
	{
		m_bNeedRedraw[m_iPolygonId] = TRUE;//redraw polygon
		UpdateData(FALSE);
	}
	else
	{
		if (m_bNeedRedraw[m_iPolygonId]&& !m_bCloseIn[m_iPolygonId])
		{
			if (m_bMouseMove[m_iPolygonId])
			{
				m_bMouseMove[m_iPolygonId] = FALSE;
				m_struPolygon[m_iPolygonId].dwPointNum--;
			}
			m_bCloseIn[m_iPolygonId] = TRUE;
		}		
	}
	BOOL bRet;
	bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawIVMSMaskRegionShow, 0);
	
	
	
}

void CDlgVcaMaskRegion::OnRadioPolygon2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//	EnableDrawPolygon(m_bPolygon2);
	m_iPolygonId =1;
	m_bDrawPolygon = TRUE;
	m_dwPosNum = 0;
	UpdateData(FALSE);
	// 	m_bPolygon1 = FALSE;
	// 	m_bPolygon3 =FALSE;
	// 	m_bPolygon4 =FALSE;
	// 	UpdateData(FALSE);
	
	
	if(m_bDrawPolygon)
	{
		m_bNeedRedraw[m_iPolygonId] = TRUE;//redraw polygon
		UpdateData(FALSE);
	}
	else
	{
		if (m_bNeedRedraw[m_iPolygonId]&& !m_bCloseIn[m_iPolygonId])
		{
			if (m_bMouseMove[m_iPolygonId])
			{
				m_bMouseMove[m_iPolygonId] = FALSE;
				m_struPolygon[m_iPolygonId].dwPointNum--;
			}
			m_bCloseIn[m_iPolygonId] = TRUE;
		}		
	}
	BOOL bRet;
	bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawIVMSMaskRegionShow, 0);
	
	
}

void CDlgVcaMaskRegion::OnRadioPolygon3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//	EnableDrawPolygon(m_bPolygon3);
	m_iPolygonId =2;
	m_bDrawPolygon = TRUE;
	m_dwPosNum = 0;
	UpdateData(FALSE);
	// 	m_bPolygon1 = FALSE;
	// 	m_bPolygon2 =FALSE;
	// 	m_bPolygon4 =FALSE;
	// 	UpdateData(FALSE);
	
	if(m_bDrawPolygon)
	{
		m_bNeedRedraw[m_iPolygonId] = TRUE;//redraw polygon
		UpdateData(FALSE);
	}
	else
	{
		if (m_bNeedRedraw[m_iPolygonId]&& !m_bCloseIn[m_iPolygonId])
		{
			if (m_bMouseMove[m_iPolygonId])
			{
				m_bMouseMove[m_iPolygonId] = FALSE;
				m_struPolygon[m_iPolygonId].dwPointNum--;
			}
			m_bCloseIn[m_iPolygonId] = TRUE;
		}		
	}
	BOOL bRet;
	bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawIVMSMaskRegionShow, 0);
}

void CDlgVcaMaskRegion::OnRadioPolygon4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//	EnableDrawPolygon(m_bPolygon4);
	m_iPolygonId = 3;
	m_dwPosNum = 0;
	// 	m_bPolygon1 = FALSE;
	// 	m_bPolygon2 =FALSE;
	// 	m_bPolygon3 =FALSE;
	// 	UpdateData(FALSE);
	
	m_bDrawPolygon = TRUE;
	UpdateData(FALSE);
	if(m_bDrawPolygon)
	{
		m_bNeedRedraw[m_iPolygonId] = TRUE;//redraw polygon
		UpdateData(FALSE);
	}
	else
	{
		if (m_bNeedRedraw[m_iPolygonId]&& !m_bCloseIn[m_iPolygonId])
		{
			if (m_bMouseMove[m_iPolygonId])
			{
				m_bMouseMove[m_iPolygonId] = FALSE;
				m_struPolygon[m_iPolygonId].dwPointNum--;
			}
			m_bCloseIn[m_iPolygonId] = TRUE;
		}		
	}
	BOOL bRet;
	bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawIVMSMaskRegionShow, 0);
}

void CDlgVcaMaskRegion::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
   
    StopPlay();
    
    g_pIVMSMaskAreaSet = NULL;
	CDialog::PostNcDestroy();
}


BOOL CDlgVcaMaskRegion::GetMaskRegion()
{
	UpdateData(TRUE);
	m_iChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VCA_MASK_REGION, m_iChannel, &m_struMaskRegionList, sizeof(m_struMaskRegionList), &dwReturn)) 
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_MASK_REGION");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_MASK_REGION");
    }

	for (int i = 0; i < MAX_MASK_REGION_NUM; i++)
	{
		memcpy(&m_struPolygon[i], &m_struMaskRegionList.struMask[i].struPolygon, sizeof(NET_VCA_POLYGON));
	}

    m_bActive1 = m_struMaskRegionList.struMask[0].byEnable;
    m_bActive2 = m_struMaskRegionList.struMask[1].byEnable;
    m_bActive3 = m_struMaskRegionList.struMask[2].byEnable;
    m_bActive4 = m_struMaskRegionList.struMask[3].byEnable;

    UpdateData(FALSE);

	return TRUE;
}

BOOL CDlgVcaMaskRegion::SetMaskRegion()
{
	UpdateData(TRUE);
	m_iChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());


    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VCA_MASK_REGION, m_iChannel, &m_struMaskRegionList, sizeof(m_struMaskRegionList)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_MASK_REGION");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_MASK_REGION");
        return TRUE;
    }
}

BOOL CDlgVcaMaskRegion::GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream)
{
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	m_iChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

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

LONG CDlgVcaMaskRegion::StartPlay()
{
	UpdateData(TRUE);
	m_iChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());


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
            bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawIVMSMaskRegionShow, 0);//DC Draw callback
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
            bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawIVMSMaskRegionShow, 0);//DC Draw callback
        }
        return m_lPlayHandle;
    } 

}

BOOL CDlgVcaMaskRegion::StopPlay()
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


void CDlgVcaMaskRegion::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	StopPlay();
	StartPlay();
}

void CDlgVcaMaskRegion::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	GetMaskRegion();
}