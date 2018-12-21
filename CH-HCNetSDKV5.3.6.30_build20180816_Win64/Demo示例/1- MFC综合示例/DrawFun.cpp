#include "stdafx.h"
#include "DrawFun.h"
#include "gdiplus/GdiPlus.h"
#include "math.h"
#define  USERDEFINE_VALUE  0.005

void CDrawFun::DrawVcaPolygon(HDC hDc, LPDRAW_POLYGON_PARAM lpDrawPolygon)
{
	if (lpDrawPolygon->struVcaPolygon.dwPointNum > VCA_MAX_POLYGON_POINT_NUM)
	{
		return;
	}

    using namespace Gdiplus;
    Graphics graphics(hDc);
    SolidBrush  brush(Color(50, 0, 0, 0));
    brush.SetColor(Color(50, GetRValue(lpDrawPolygon->color), GetGValue(lpDrawPolygon->color), GetBValue(lpDrawPolygon->color)));
    
    POINT point[VCA_MAX_POLYGON_POINT_NUM] = {0};
    
    CPen DrawPen;
    unsigned int i;
    
    DrawPen.CreatePen(PS_SOLID, 1, lpDrawPolygon->color);
    SetTextColor(hDc,lpDrawPolygon->color);
    SetBkMode(hDc, TRANSPARENT);
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, (int)(lpDrawPolygon->struVcaPolygon.struPos[0].fX*lpDrawPolygon->rcWnd.Width()), \
        (int)(lpDrawPolygon->struVcaPolygon.struPos[0].fY*lpDrawPolygon->rcWnd.Height()), NULL);
    
    for(i=1; i<lpDrawPolygon->struVcaPolygon.dwPointNum && i < VCA_MAX_POLYGON_POINT_NUM; i++)
    {
        
        LineTo(hDc, (int)(lpDrawPolygon->struVcaPolygon.struPos[i].fX*lpDrawPolygon->rcWnd.Width()),\
            (int)(lpDrawPolygon->struVcaPolygon.struPos[i].fY*lpDrawPolygon->rcWnd.Height()));
        //Redraw the polygon if the lines are intersectant.
        if(i>=MIN_PNT_NUM && !lpDrawPolygon->bMouseMove && IsCrossLine(&lpDrawPolygon->struVcaPolygon))
        {
            char szLan[128] = {0};
            g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Edges of Polygon can be intersectant, please redraw.!");
            //AfxMessageBox(szLan);
            lpDrawPolygon->struVcaPolygon.dwPointNum--;
            break;
        }
    }
    
    for (i=0; i<(int)lpDrawPolygon->struVcaPolygon.dwPointNum ; i++)
    {
        if (i == VCA_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(lpDrawPolygon->struVcaPolygon.struPos[i].fX*lpDrawPolygon->rcWnd.Width());
        point[i].y = (int)(lpDrawPolygon->struVcaPolygon.struPos[i].fY*lpDrawPolygon->rcWnd.Height());
    }
    //After drawing the 10th point, connect it with the 1st point.
    if(VCA_MAX_POLYGON_POINT_NUM == i && !lpDrawPolygon->bMouseMove)
    {
        if (IsValidArea(&lpDrawPolygon->struVcaPolygon))
        {
            graphics.FillPolygon(&brush, (Point *)point, lpDrawPolygon->struVcaPolygon.dwPointNum);
            
            LineTo(hDc, point[0].x, point[0].y);
            TextOut(hDc, point[0].x, point[0].y, lpDrawPolygon->chName, strlen(lpDrawPolygon->chName));

            lpDrawPolygon->bCloseIn = TRUE;
        }else//redraw
        {

        }
        //check if the alarm region is intact
    }
    else if(lpDrawPolygon->struVcaPolygon.dwPointNum>2 && lpDrawPolygon->bCloseIn)
    {
        if (IsValidArea(&lpDrawPolygon->struVcaPolygon))
        {
            graphics.FillPolygon(&brush, (Point *)point, lpDrawPolygon->struVcaPolygon.dwPointNum);
            
            LineTo(hDc, point[0].x, point[0].y);

            TextOut(hDc, point[0].x, point[0].y, lpDrawPolygon->chName, strlen(lpDrawPolygon->chName));
//            F_AddLabel(hDc, AlarmArea, dwRuleID);
        }else
        {
//             m_bNeedRedraw[dwRuleID] = TRUE;
//             m_bCloseIn[dwRuleID] = FALSE;
        }
    }
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
    
    return;
}

void CDrawFun::DrawPolygonEx(HDC hDc,LPDRAW_POLYGON_PARAM_EX lpDrawPolygon)
{   
	const int MAX_POLYGON_POINT_NUM = 20;
	if (lpDrawPolygon == NULL || lpDrawPolygon->pArryPt == NULL ||
		lpDrawPolygon->dwPtNum == 0 || lpDrawPolygon->dwPtNum > MAX_POLYGON_POINT_NUM)
	{
		return;
	}

	using namespace Gdiplus;
    Graphics graphics(hDc);
    SolidBrush  brush(Color(50, 0, 0, 0));
    brush.SetColor(Color(50, GetRValue(lpDrawPolygon->color), GetGValue(lpDrawPolygon->color), GetBValue(lpDrawPolygon->color)));
    
    POINT point[MAX_POLYGON_POINT_NUM] = {0};
    
    CPen DrawPen;
    unsigned int i;
    
    DrawPen.CreatePen(PS_SOLID, 1, lpDrawPolygon->color);
    SetTextColor(hDc,lpDrawPolygon->color);
    SetBkMode(hDc, TRANSPARENT);
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);

	for (i=0; i< lpDrawPolygon->dwPtNum ; i++)
    {
        if (i >= MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(lpDrawPolygon->pArryPt[i].fX * lpDrawPolygon->rcWnd.Width());
        point[i].y = (int)(lpDrawPolygon->pArryPt[i].fY * lpDrawPolygon->rcWnd.Height());
    }

    MoveToEx(hDc,point[0].x,point[0].y, NULL);
    
    for( i=1; i < lpDrawPolygon->dwPtNum; i++)
    {
        LineTo(hDc, point[i].x,point[i].y);
    }

	LineTo(hDc, point[0].x,point[0].y);

	graphics.FillPolygon(&brush, (Point*)point, lpDrawPolygon->dwPtNum);
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
}

BOOL CDrawFun::IsCrossLine(NET_VCA_POLYGON *alarm_region)
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
    
    // The apexes of polygon should be more than 3
    if (nPointTotal >= 3)
    {
        bCrossLine = FALSE;
    }
    else
    {
        pPntArr = new NET_VCA_POINT[nPointTotal];
        if (pPntArr == NULL)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "内存分配失败!","Allocate memory failed!");
            //AfxMessageBox(szLan);
            exit(EXIT_FAILURE);
        }
        
        //Copy the apex to a array
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

BOOL CDrawFun::IsValidArea(NET_VCA_POLYGON *alarm_region)
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
    // 判断组成多边形的所有点是否在一条直线上
    if (F_IsStraightLine(alarm_region))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "所有点在同一直线上，不能组成多边形!",\
            "All points have been in the same line, not able to form the polygon");
        //AfxMessageBox(szLan);
        return FALSE;
    }
    // 判断组成多边形的终点和起点的连线与已有的直线是否有交叉
    if (F_IsACrossLine(alarm_region))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan,"终点和起点的连线与已有的直线相交，不能组成有效的多边形!", \
            "There are straight-line intersection, can not be composed of an effective polygon");
        //AfxMessageBox(szLan);
        return FALSE;
    }
    return TRUE;
}

BOOL CDrawFun::F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2)
{
    NET_VCA_POINT p1_q1, q2_q1, p2_q1, q1_p1, p2_p1, q2_p1;       //Difference vector
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
    
    // 1 (p1 - q1) × (q2 - q1)；
    z1 = p1_q1.fX * q2_q1.fY - q2_q1.fX * p1_q1.fY; 
    
    // 2 (q2 - q1) × (p2 - q1)；
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
    
    // 3 (q1 - p1) × (p2 - p1)；
    z3 = q1_p1.fX * p2_p1.fY - p2_p1.fX * q1_p1.fY;
    
    //4 (p2 - p1) × (q2 - p1);
    z4 = p2_p1.fX * q2_p1.fY - q2_p1.fX * p2_p1.fY;
    
    
    //  check the span of two segment
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

BOOL CDrawFun::F_IsStraightLine(NET_VCA_POLYGON *alarm_region)
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
    
    //Check if all points construct a vertical line.
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
    
    // Check if all points construct a horizontal line.
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
    
    // Check if all points construct a diagonal.
    if ((0 != nXOffset) && (0 != nYOffset))
    {
        // calculate slope
        fSlope  = 1.0f * nYOffset / nXOffset;
        // intercept 
        fOffset = pPointArray[0].fY - fSlope * pPointArray[1].fX;
        // the coefficient for calculating the distance between point and line. 
        fCoefficient = (float)sqrt(1.0 + fSlope * fSlope);
        
        for (i = 2; i < nPointTotal; i ++)
        {
            // Calculate the distance between other point and the line constructed by point 1 and point 2. 
            fDistance = (float)fabs(fSlope * pPointArray[i].fX - pPointArray[i].fY + fOffset)/fCoefficient;
            
            // if there is one distance of points that is more than 0, the polygon is valid.
            if ((fDistance - 0.0f) > 0.000001f)
            {
                bStraightLine = FALSE;
                break;
            }
        }		
    }
    
    return bStraightLine;	
}

BOOL CDrawFun::F_IsACrossLine(NET_VCA_POLYGON *alarm_region)
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
    
    
    if (nPointTotal == VCA_MAX_POLYGON_POINT_NUM)
    {
        bCrossLine = FALSE;
    }
    else
    {
        pPntArr = new NET_VCA_POINT[nPointTotal];
        if (pPntArr == NULL)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "Allocate memory failed!","Memory allocation failure!");
            //AfxMessageBox(szLan);
            exit(EXIT_FAILURE);
        }
        
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

void CDrawFun::DrawVcaRect(HDC hDc, LPDRAW_RECT_PARAM lpDrawRect)
{
    CPen DrawPen;
    
    DrawPen.CreatePen(PS_SOLID, 1, lpDrawRect->color);
    CBrush brTmp;
    brTmp.CreateSolidBrush(lpDrawRect->color);
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    CRect rect;
    rect.left = (int)(lpDrawRect->struVcaRect.fX*lpDrawRect->rcWnd.Width());
    rect.top = (int)(lpDrawRect->struVcaRect.fY*lpDrawRect->rcWnd.Height());
    rect.right = (int)((lpDrawRect->struVcaRect.fX+lpDrawRect->struVcaRect.fWidth)*lpDrawRect->rcWnd.Width());
    rect.bottom = (int)((lpDrawRect->struVcaRect.fY+lpDrawRect->struVcaRect.fHeight)*lpDrawRect->rcWnd.Height());
    FrameRect(hDc, rect, brTmp);
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
}

void CDrawFun::DrawTraversePlane(HDC hDc, LPDRAW_TRAVERSE_PLANE_PARAM lpDrawTaversePlane)
{
    int iDirect = -1;
    int x1 = (int)(lpDrawTaversePlane->struVcaLine.struStart.fX*lpDrawTaversePlane->rcWnd.Width());
    int y1 = (int)(lpDrawTaversePlane->struVcaLine.struStart.fY*lpDrawTaversePlane->rcWnd.Height());
    int x2 = (int)(lpDrawTaversePlane->struVcaLine.struEnd.fX*lpDrawTaversePlane->rcWnd.Width());
    int y2 = (int)(lpDrawTaversePlane->struVcaLine.struEnd.fY*lpDrawTaversePlane->rcWnd.Height());

    SetTextColor(hDc,lpDrawTaversePlane->color);
    
    using namespace Gdiplus;
    Graphics graphics(hDc);
    Color DrawColor;
    DrawColor.SetValue(DrawColor.MakeARGB(50,GetRValue(lpDrawTaversePlane->color) ,GetGValue(lpDrawTaversePlane->color),GetBValue(lpDrawTaversePlane->color)));
    
    Pen pen(lpDrawTaversePlane->color, 4);
    pen.SetStartCap(LineCapFlat);
    pen.SetEndCap(LineCapFlat);
    
    CPen DrawPen;
    DrawPen.CreatePen(PS_SOLID, 1, lpDrawTaversePlane->color);
    
    bool bRect = false;
    int k = 0;
    //calculate slope
    if(x2 != x1)
    {
        k = (y2 - y1) / (x2 - x1);
        
        //if the absolute value of slope is more than 2, draw rectangle directly
        if(abs(k) >= 2)
        {
            bRect = true;
        }
    }
    else
    {
        bRect = true;
    }
    
    if(bRect)
    {
        pen.SetColor(DrawColor);
        if(k < 0)
        {
            graphics.DrawLine(&pen, x1-2, y1-1, x2-2, y2-1);
        }
        else
        {
            graphics.DrawLine(&pen, x1+2, y1-1, x2+2, y2-1);
        }
    }
    else
    {
        //Draw parallelogram, the vertical height is 8
        SolidBrush  brush(DrawColor);
        POINT point[4];
        point[0].x = x1;
        point[0].y = y1;
        point[1].x = x2;
        point[1].y = y2;
        point[2].x = x2;
        point[2].y = y2-8;
        point[3].x = x1;
        point[3].y = y1-8;
        graphics.FillPolygon(&brush, (Point *)point, 4);
    }
    
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, x1, y1, NULL);
    LineTo(hDc, x2, y2);
    
    //Draw arrow
    F_DrawArrowhead(hDc, lpDrawTaversePlane);
    //Draw label
    
    SelectObject(hDc, pOldPen);
	DeleteObject(DrawPen);
}

void CDrawFun::DrawLine(HDC hDc,LPDRAW_LINE_PARAM lpDrawLine)
{
	SetBkMode(hDc, TRANSPARENT);
    CPen   DrawPen;	
	
    DrawPen.CreatePen(PS_SOLID, 2, lpDrawLine->color);
    
    HGDIOBJ hOldPen = SelectObject(hDc, DrawPen);
    
    
    CPoint cStartPointTemp;
    
    cStartPointTemp.x = lpDrawLine->struVcaLine.struStart.fX * lpDrawLine->rcWnd.Width() + USERDEFINE_VALUE;
    cStartPointTemp.y = lpDrawLine->struVcaLine.struStart.fY * lpDrawLine->rcWnd.Height() + USERDEFINE_VALUE;

    CPoint cEndPointTemp;
    
    cEndPointTemp.x = lpDrawLine->struVcaLine.struEnd.fX * lpDrawLine->rcWnd.Width() + USERDEFINE_VALUE;
    cEndPointTemp.y = lpDrawLine->struVcaLine.struEnd.fY * lpDrawLine->rcWnd.Height() + USERDEFINE_VALUE;
    
    MoveToEx(hDc, cStartPointTemp.x, cStartPointTemp.y, NULL);
    LineTo(hDc, cEndPointTemp.x, cEndPointTemp.y);
    
    SelectObject(hDc, hOldPen);
    DrawPen.DeleteObject();
}

// void CDlgVcaRuleCfg::F_DrawLine(long lPlayHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color)
// {
//     
//     int iDirect = -1;
//     int x1 = (int)(lpVcaRect->struStart.fX*lpDrawTaversePlane->rcWnd.Width());
//     int y1 = (int)(lpVcaRect->struStart.fY*m_rcWndRect.Height());
//     int x2 = (int)(lpVcaRect->struEnd.fX*m_rcWndRect.Width());
//     int y2 = (int)(lpVcaRect->struEnd.fY*m_rcWndRect.Height());
//     
//     SetTextColor(hDc,color);
//     
//     using namespace Gdiplus;
//     Graphics graphics(hDc);
//     Color DrawColor;
//     DrawColor.SetValue(DrawColor.MakeARGB(50,GetRValue(color) ,GetGValue(color),GetBValue(color)));
//     
//     Pen pen(color, 4);
//     pen.SetStartCap(LineCapFlat);
//     pen.SetEndCap(LineCapFlat);
//     
//     CPen DrawPen;
//     DrawPen.CreatePen(PS_SOLID, 1, color);
//     
//     bool bRect = false;
//     int k = 0;
//     //calculate slope
//     if(x2 != x1)
//     {
//         k = (y2 - y1) / (x2 - x1);
//         
//         //if the absolute value of slope is more than 2, draw rectangle directly
//         if(abs(k) >= 2)
//         {
//             bRect = true;
//         }
//     }
//     else
//     {
//         bRect = true;
//     }
//     
//     if(bRect)
//     {
//         TRACE("Line\n");
//         
//         pen.SetColor(DrawColor);
//         if(k < 0)
//         {
//             graphics.DrawLine(&pen, x1-2, y1-1, x2-2, y2-1);
//         }
//         else
//         {
//             graphics.DrawLine(&pen, x1+2, y1-1, x2+2, y2-1);
//         }
//     }
//     else
//     {
//         //Draw parallelogram, the vertical height is 8
//         SolidBrush  brush(DrawColor);
//         POINT point[4];
//         point[0].x = x1;
//         point[0].y = y1;
//         point[1].x = x2;
//         point[1].y = y2;
//         point[2].x = x2;
//         point[2].y = y2-8;
//         point[3].x = x1;
//         point[3].y = y1-8;
//         graphics.FillPolygon(&brush, (Point *)point, 4);
//     }
//     
//     
//     HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
//     MoveToEx(hDc, x1, y1, NULL);
//     LineTo(hDc, x2, y2);
//     
//     //Draw arrow
//     F_DrawArrowhead(hDc, dwRuleID, m_struOneRule.uEventParam.struTraversePlane.dwCrossDirection);
//     //Draw label
//     F_AddLabel(hDc, AlarmLine, dwRuleID);
//     
//     SelectObject(hDc, pOldPen);
//     DeleteObject(DrawPen);
// }


// void CDrawFun::F_DrawFilter(long lRealHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color)
// {
//     UNREFERENCED_PARAMETER(dwRuleID);
//     UNREFERENCED_PARAMETER(dwUser);
//     UNREFERENCED_PARAMETER(lRealHandle);
//     //	if (m_bSetMiniFilter || m_bSetMaxFilter)
//     if (m_bFilterActive)
//     {
//         CPen DrawPen;
//         
//         DrawPen.CreatePen(PS_SOLID, 1, color);
//         CBrush brTmp;
//         brTmp.CreateSolidBrush(color);
//         
//         HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
//         CRect rectMini, rectMax;
//         rectMini.left = (int)(m_struOneRule.struSizeFilter.struMiniRect.fX*m_rcWndRect.Width());
//         rectMini.top = (int)(m_struOneRule.struSizeFilter.struMiniRect.fY*m_rcWndRect.Height());
//         rectMini.right = (int)((m_struOneRule.struSizeFilter.struMiniRect.fX+m_struOneRule.struSizeFilter.struMiniRect.fWidth)*m_rcWndRect.Width());
//         rectMini.bottom = (int)((m_struOneRule.struSizeFilter.struMiniRect.fY+m_struOneRule.struSizeFilter.struMiniRect.fHeight)*m_rcWndRect.Height());
//         FrameRect(hDc, rectMini, brTmp);
//         
//         rectMax.left = (int)(m_struOneRule.struSizeFilter.struMaxRect.fX*m_rcWndRect.Width());
//         rectMax.top = (int)(m_struOneRule.struSizeFilter.struMaxRect.fY*m_rcWndRect.Height());
//         rectMax.right = (int)((m_struOneRule.struSizeFilter.struMaxRect.fX+m_struOneRule.struSizeFilter.struMaxRect.fWidth)*m_rcWndRect.Width());
//         rectMax.bottom = (int)((m_struOneRule.struSizeFilter.struMaxRect.fY+m_struOneRule.struSizeFilter.struMaxRect.fHeight)*m_rcWndRect.Height());
//         FrameRect(hDc, rectMax, brTmp);
//         
//         SelectObject(hDc, pOldPen);
//         DeleteObject(DrawPen);
//     }
//}

void CDrawFun::F_DrawArrowhead(HDC hDc, LPDRAW_TRAVERSE_PLANE_PARAM lpDrawTaversePlane)
{
    POINT ptArrow_start0;/*, ptArrow_start1, ptArrow_start2;*/
    POINT ptArrow_end;
    float fLine_k = 0.0, fArrow_k = 0.0, fArrow_k1 = 0.0;
    int   iTheta = 0;

    //coordinate of arrow's end
    ptArrow_start0.x = (long)(lpDrawTaversePlane->rcWnd.Width()*(lpDrawTaversePlane->struVcaLine.struStart.fX+lpDrawTaversePlane->struVcaLine.struEnd.fX) / 2);
    ptArrow_start0.y = (long)(lpDrawTaversePlane->rcWnd.Height()*(lpDrawTaversePlane->struVcaLine.struStart.fY + lpDrawTaversePlane->struVcaLine.struEnd.fY) / 2);

    //slope
    fLine_k = (lpDrawTaversePlane->struVcaLine.struEnd.fY*lpDrawTaversePlane->rcWnd.Height() - lpDrawTaversePlane->struVcaLine.struStart.fY*lpDrawTaversePlane->rcWnd.Height()) / 
        (lpDrawTaversePlane->struVcaLine.struEnd.fX*lpDrawTaversePlane->rcWnd.Width() - lpDrawTaversePlane->struVcaLine.struStart.fX*lpDrawTaversePlane->rcWnd.Width());

    POINT ptStart0;

    using namespace Gdiplus;
    Graphics graphics(hDc);

    Color color(80, 0, 0, 0);
    color.SetValue(color.MakeARGB(80,GetRValue(lpDrawTaversePlane->color),GetGValue(lpDrawTaversePlane->color),GetBValue(lpDrawTaversePlane->color)));

    Pen pen(color, 5);
    //if the absolute value of slope is more than 2, the width of arrow is 4
    if(abs(fLine_k) >= 2)
		{
        pen.SetWidth(4);
    }
    else
    {
        //otherwise the width of arrow is 8*cos(alpha)
        float fWidth = 8.0 / sqrt(1.0 + fLine_k * fLine_k);
        pen.SetWidth(fWidth);
    }

    pen.SetStartCap(LineCapFlat);
    pen.SetEndCap(LineCapArrowAnchor);

    if (fLine_k != 0.0)
    {
        //perpendicular segment on the line
        fArrow_k =  -1.0 / fLine_k;

        iTheta = (int)(atan(fArrow_k ) / PI * 180);

        if (VCA_LEFT_GO_RIGHT == lpDrawTaversePlane->dwCrossDirection || VCA_BOTH_DIRECTION == lpDrawTaversePlane->dwCrossDirection)
        {
            //reduce 1 of width to prevent the arrow deviate from the segment
            if(fLine_k > 0)
            {
                ptStart0.x = ptArrow_start0.x - (8-1) * sin(iTheta / 180.0 * PI) * cos(iTheta / 180.0 * PI);
                ptStart0.y = ptArrow_start0.y - (8-1) * sin(iTheta / 180.0 * PI) * sin(iTheta / 180.0 * PI);
		}
            else
		{
                ptStart0.x = ptArrow_start0.x;
                ptStart0.y = ptArrow_start0.y;
            }

            ptArrow_end.x = ptStart0.x + 20 * cos(iTheta / 180.0 * PI);
            ptArrow_end.y = 20 * sin(iTheta / 180.0 * PI) + ptStart0.y;

            graphics.DrawLine(&pen, ptStart0.x, ptStart0.y, ptArrow_end.x, ptArrow_end.y);
        }

        if (VCA_RIGHT_GO_LEFT == lpDrawTaversePlane->dwCrossDirection || VCA_BOTH_DIRECTION == lpDrawTaversePlane->dwCrossDirection)
        {
            if(fLine_k > 0)
            {
                ptStart0.x = ptArrow_start0.x;
                ptStart0.y = ptArrow_start0.y;
            }
            else
            {
                ptStart0.x = ptArrow_start0.x - (8-1) * sin(iTheta / 180.0 * PI) * cos(iTheta / 180.0 * PI);
                ptStart0.y = ptArrow_start0.y - (8-1) * sin(iTheta / 180.0 * PI) * sin(iTheta / 180.0 * PI);
            }

            ptArrow_end.x = ptStart0.x - 20 * cos(iTheta / 180.0 * PI);
            ptArrow_end.y = (-20) * sin(iTheta / 180.0 * PI) + ptStart0.y ;

            graphics.DrawLine(&pen, ptStart0.x, ptStart0.y, ptArrow_end.x, ptArrow_end.y);
		}
	}else
	{
        //The arrow is vertical
        if (VCA_LEFT_GO_RIGHT == lpDrawTaversePlane->dwCrossDirection || VCA_BOTH_DIRECTION == lpDrawTaversePlane->dwCrossDirection)
		{
			//
            ptStart0.x = ptArrow_start0.x;
            ptStart0.y = ptArrow_start0.y;// + 4;

            ptArrow_end.x = ptStart0.x ;
            ptArrow_end.y = ptStart0.y + 20;

            graphics.DrawLine(&pen, ptStart0.x, ptStart0.y, ptArrow_end.x, ptArrow_end.y);
		}
        if (VCA_RIGHT_GO_LEFT == lpDrawTaversePlane->dwCrossDirection || VCA_BOTH_DIRECTION == lpDrawTaversePlane->dwCrossDirection)
		{
			// 
            ptStart0.x = ptArrow_start0.x;
            ptStart0.y = ptArrow_start0.y - 8;

            ptArrow_end.x = ptStart0.x ;
            ptArrow_end.y = ptStart0.y - 20;

            graphics.DrawLine(&pen, ptStart0.x, ptStart0.y, ptArrow_end.x, ptArrow_end.y);
		}		
	}
}

void CDrawFun::DrawDirection(HDC hDc, LPDRAW_DIRECTION_PARAM lpDrawDirection)
{
    CPen cpDrawPen;
    //将设备中的相对坐标转化为屏幕的实际坐标
    
    int x1 = (int)(lpDrawDirection->struDirection.struStartPoint.fX*lpDrawDirection->rcWnd.Width());
    int y1 = (int)(lpDrawDirection->struDirection.struStartPoint.fY*lpDrawDirection->rcWnd.Height());
    
    int x2 = (int)(lpDrawDirection->struDirection.struEndPoint.fX*lpDrawDirection->rcWnd.Width());
    int y2 = (int)(lpDrawDirection->struDirection.struEndPoint.fY*lpDrawDirection->rcWnd.Height());
    
    //如果是点，则不画
    if ((x1 == x2) && (y1 == y2))
    {
        return;
    }
    
    //画线
    using namespace Gdiplus;
    Graphics graphics(hDc);
    
    Color color(80, 0, 0, 0);
    
    Pen pen(color, 7);
    
    pen.SetStartCap(LineCapFlat);
    
    Point pt1 = Point(0, -1);
    Point pt2 = Point(2, -1);
    Point pt3 = Point(0, 4);
    Point pt4 = Point(-2, -1);
    GraphicsPath fillPath;
    fillPath.AddLine(pt1, pt2);
    fillPath.AddLine(pt2, pt3);
    fillPath.AddLine(pt3, pt4);
    CustomLineCap custCap(&fillPath, NULL);
    pen.SetCustomEndCap(&custCap);
    cpDrawPen.CreatePen(PS_SOLID, 1, lpDrawDirection->color);
    color.SetValue(color.MakeARGB(100, GetRValue(lpDrawDirection->color), GetGValue(lpDrawDirection->color), GetBValue(lpDrawDirection->color)));
    
    int k = 0;
    //求斜率
    if(x2 != x1)
        k = (y2 - y1) / (x2 - x1);
    
    pen.SetColor(color);
    
    if(k < 0)
        graphics.DrawLine(&pen, x1-2, y1-1, x2-2, y2-1);
    else
        graphics.DrawLine(&pen, x1+2, y1-1, x2+2, y2-1);
    
    HGDIOBJ cpOldPen = SelectObject(hDc, cpDrawPen);
    
    cpDrawPen.DeleteObject();
    SelectObject(hDc, cpOldPen);
    
    graphics.ReleaseHDC(hDc);
}


void CDrawFun::DrawLineSegment(HDC hDc, LPDRAW_LINE_SEGMENT_PARAM lpDrawLineSegment)
{
    SetBkMode(hDc, TRANSPARENT);
    CPen   DrawPen;	

    DrawPen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    
    HGDIOBJ hOldPen = SelectObject(hDc, DrawPen);
    
    
    CPoint cStartPointTemp;
    
    cStartPointTemp.x = lpDrawLineSegment->struLineSegment.struStartPoint.fX * lpDrawLineSegment->rcWnd.Width() + USERDEFINE_VALUE;
    cStartPointTemp.y = lpDrawLineSegment->struLineSegment.struStartPoint.fY * lpDrawLineSegment->rcWnd.Height() + USERDEFINE_VALUE;
//     DRAW_POINT_PARAM struPointParam;
//     memset(&struPointParam, 0, sizeof(struPointParam));
//     struPointParam.color = RGB(233,255,0);
//     memcpy(&struPointParam.point, &cStartPointTemp, sizeof(cStartPointTemp));
//     DrawPoint(hDc, &struPointParam);
    CPoint cEndPointTemp;
    
    cEndPointTemp.x = lpDrawLineSegment->struLineSegment.struEndPoint.fX * lpDrawLineSegment->rcWnd.Width() + USERDEFINE_VALUE;
    cEndPointTemp.y = lpDrawLineSegment->struLineSegment.struEndPoint.fY * lpDrawLineSegment->rcWnd.Height() + USERDEFINE_VALUE;
    
    MoveToEx(hDc, cStartPointTemp.x, cStartPointTemp.y, NULL);
    LineTo(hDc, cEndPointTemp.x, cEndPointTemp.y);
    
    if (cStartPointTemp.x == 0 && cStartPointTemp.y == 0 && cEndPointTemp.x  == 0 && cEndPointTemp.x == 0)
    {
        
    }
    else
    {
        CString str;
        if (lpDrawLineSegment->struLineSegment.byLineMode == HEIGHT_LINE)
        {
            str.Format("H%3.2f", lpDrawLineSegment->struLineSegment.fValue);
        }
        else if (lpDrawLineSegment->struLineSegment.byLineMode == LENGTH_LINE)
        {
            str.Format("L%3.2f", lpDrawLineSegment->struLineSegment.fValue);
        }

        TextOut(hDc, ((int)(cStartPointTemp.x + cEndPointTemp.x) >> 1) + 5,
            (int)(cStartPointTemp.y + cEndPointTemp.y) >> 1, str,str.GetLength());		
    }
    
    SelectObject(hDc, hOldPen);
    DrawPen.DeleteObject();
}

void CDrawFun::DrawVcaPoint(HDC hDc, LPDRAW_VCA_POINT_PARAM lpDrawVcaPoint)
{
    CPoint point;
    point.x = lpDrawVcaPoint->struVcaPoint.fX * lpDrawVcaPoint->rcWnd.Width() + USERDEFINE_VALUE;
    point.y = lpDrawVcaPoint->struVcaPoint.fY * lpDrawVcaPoint->rcWnd.Height() + USERDEFINE_VALUE;
    DRAW_POINT_PARAM struPointParam;
    memset(&struPointParam, 0 , sizeof(struPointParam));
    struPointParam.color = lpDrawVcaPoint->color;
    memcpy(&struPointParam.point, &point, sizeof(struPointParam.point));
    DrawPoint(hDc, &struPointParam);
}

void CDrawFun::DrawPoint(HDC hDc, LPDRAW_POINT_PARAM lpDrawPoint)
{
    CPen DrawPen;
    DrawPen.CreatePen(PS_SOLID, 2, lpDrawPoint->color);
    HGDIOBJ hOldPen = SelectObject(hDc, DrawPen);
//     MoveToEx(hDc, lpDrawPoint->point.x - 4, lpDrawPoint->point.y);
//     LineTo(hDc, lpDrawPoint->point.x - 4, lpDrawPoint->point.y);
    Arc(hDc, lpDrawPoint->point.x - 2, lpDrawPoint->point.y - 2,
        lpDrawPoint->point.x + 2, lpDrawPoint->point.y + 2,
        lpDrawPoint->point.x, lpDrawPoint->point.y,
        lpDrawPoint->point.x, lpDrawPoint->point.y);

    SelectObject(hDc, hOldPen);
    DrawPen.DeleteObject();
}



void CDrawFun::DrawSensorText(HDC hDc, CString str, COLORREF color, CRect rect, int nFontSize)
{
//     LOGFONT   logfont;       //改变输出字体
//     ZeroMemory(&logfont,  0, sizeof(LOGFONT));
//     logfont.lfCharSet   =   GB2312_CHARSET;
//     logfont.lfHeight   =   20;      //设置字体的大小
//     HFONT   hFont   =   CreateFontIndirect(&logfont); 

    CFont cFont;
//     cFont.CreateFont(15,15,0,0,FW_THIN,true,false,false,
//         CHINESEBIG5_CHARSET,OUT_CHARACTER_PRECIS,
//         CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
//         FF_MODERN,"宋体");

//     { return Attach(::CreateFont(nHeight, nWidth, nEscapement,
//         nOrientation, nWeight, bItalic, bUnderline, cStrikeOut,
//         nCharSet, nOutPrecision, nClipPrecision, nQuality,
// 		nPitchAndFamily, lpszFacename)); }

    if (MINOR_FONT == nFontSize)
    {
        rect.top += 40;
        rect.left += 4;
        cFont.CreateFont(14,8,0,0,FW_DONTCARE,false,false,false,
            GB2312_CHARSET,OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
            FF_DONTCARE,"宋体");

    }
    else if (NORMAL_FONT == nFontSize)
    {
        rect.top += 40*2;
        rect.left += 4*2;
        cFont.CreateFont(28,16,0,0,FW_DONTCARE,false,false,false,
            GB2312_CHARSET,OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
            FF_DONTCARE,"宋体");
    }
    else if (MAJOR_FONT == nFontSize)
    {
        rect.top += 40*3;
        rect.left += 4*3;
        cFont.CreateFont(42,24,0,0,FW_DONTCARE,false,false,false,
            GB2312_CHARSET,OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
            FF_DONTCARE,"宋体");
    }

    CPen DrawPen;
    DrawPen.CreatePen(PS_SOLID, 1, color);
    SetTextColor(hDc,color);
    SetBkMode(hDc, TRANSPARENT);

    SelectObject(hDc, cFont);

    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);

    DrawText(hDc, str.GetBuffer(0),str.GetLength(), &rect, DT_WORDBREAK);
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
    DeleteObject(cFont);
    //DeleteObject(hFont); 
}
