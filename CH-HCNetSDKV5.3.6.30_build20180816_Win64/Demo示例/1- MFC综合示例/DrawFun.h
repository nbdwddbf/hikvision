#ifndef _DRAW_FUN_H_
#define _DRAW_FUN_H_

#include "ClientDemo.h"
typedef struct  tagDRAW_POLYGON_PARAM
{
    COLORREF color; 
    CRect   rcWnd;
    NET_VCA_POLYGON struVcaPolygon;
    BOOL    bCloseIn;
    BOOL    bMouseMove;
    char    chName[32]; 
}DRAW_POLYGON_PARAM, *LPDRAW_POLYGON_PARAM;

typedef struct tagDRAW_TRAVERSE_PLANE_PARAM
{
    COLORREF color;
    CRect rcWnd;
    NET_VCA_LINE struVcaLine;
    DWORD   dwCrossDirection;   
}DRAW_TRAVERSE_PLANE_PARAM, *LPDRAW_TRAVERSE_PLANE_PARAM;

typedef struct tagDRAW_RECT_PARAM
{
     COLORREF color;
     CRect rcWnd;
     NET_VCA_RECT struVcaRect;
}DRAW_RECT_PARAM, *LPDRAW_RECT_PARAM;

typedef struct tagDRAW_DIRECTION_PARAM
{
    COLORREF color;
    CRect    rcWnd;
    NET_DVR_DIRECTION struDirection;
}DRAW_DIRECTION_PARAM, *LPDRAW_DIRECTION_PARAM;

typedef struct tagDRAW_LINE_SEGMENT_PARAM
{
    COLORREF color;
    CRect rcWnd;
    NET_DVR_LINE_SEGMENT struLineSegment;
}DRAW_LINE_SEGMENT_PARAM, *LPDRAW_LINE_SEGMENT_PARAM;

typedef struct tagDRAW_VCA_POINT_PARAM
{
    COLORREF color;
    CRect rcWnd;
    NET_VCA_POINT struVcaPoint;
}DRAW_VCA_POINT_PARAM, *LPDRAW_VCA_POINT_PARAM;

typedef struct tagDRAW_POINT_PARAM
{
    COLORREF color;
    CPoint  point;
}DRAW_POINT_PARAM, *LPDRAW_POINT_PARAM;

typedef struct tagDRAW_LINE_PARAM
{
	COLORREF color;
    CRect rcWnd;
    NET_VCA_LINE struVcaLine;
}DRAW_LINE_PARAM,*LPDRAW_LINE_PARAM;

typedef struct tagDRAW_POLYGON_PARAM_EX
{
	COLORREF color; 
    CRect    rcWnd;
    NET_VCA_POINT* pArryPt;
	DWORD    dwPtNum;
	char     chName[32]; 
}DRAW_POLYGON_PARAM_EX,*LPDRAW_POLYGON_PARAM_EX;

class CDrawFun
{
public:
    static void DrawDirection(HDC hDc, LPDRAW_DIRECTION_PARAM lpDrawDirection);
    static void DrawVcaPolygon(HDC hDc, LPDRAW_POLYGON_PARAM lpDrawPolygon);
	static void DrawPolygonEx(HDC hDc,LPDRAW_POLYGON_PARAM_EX lpDrawPolygon);
    static void DrawVcaRect(HDC hDc, LPDRAW_RECT_PARAM lpDrawRect);
    static void DrawTraversePlane(HDC hDc, LPDRAW_TRAVERSE_PLANE_PARAM lpDrawTaversePlane);
	static void DrawLine(HDC hDc,LPDRAW_LINE_PARAM lpDrawLine);
    static void DrawLineSegment(HDC hDc, LPDRAW_LINE_SEGMENT_PARAM lpDrawLineSegment);

    static void DrawVcaPoint(HDC hDc, LPDRAW_VCA_POINT_PARAM lpDrawVcaPoint);
    static void DrawPoint(HDC hDc, LPDRAW_POINT_PARAM lpDrawPoint);

    static void DrawSensorText(HDC hDc, CString str, COLORREF color, CRect rect, int nFontSize);
protected:
    static BOOL IsCrossLine(NET_VCA_POLYGON *alarm_region);
    static BOOL IsValidArea(NET_VCA_POLYGON *alarm_region);
    static BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
    static BOOL F_IsStraightLine(NET_VCA_POLYGON *alarm_region);
    static BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);
    
    static void F_DrawArrowhead(HDC hDc, LPDRAW_TRAVERSE_PLANE_PARAM lpDrawTaversePlane);
private:
};



#endif 
