// PTZButton1.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "PTZButton1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPTZButton1
extern BOOL PTZControlAll(LONG lRealHandle, int m_iDevIndex, int m_iChannel, DWORD dwPTZCommand,DWORD dwStop, char *szCmdString);

CPTZButton1::CPTZButton1()
{
	m_lPlayHandle = -1;
	m_iChannel  = -1;
	m_iPTZType = -1;
	m_iDevIndex = -1;

}

CPTZButton1::~CPTZButton1()
{
}


BEGIN_MESSAGE_MAP(CPTZButton1, CButton)
	//{{AFX_MSG_MAP(CPTZButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPTZButton1 message handlers

void CPTZButton1::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL bRet = FALSE;

	switch (m_iPTZType)
	{
	case TILT_UP:        //Move up
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_UP, 0, "TILT_UP");
		break;
	case TILT_DOWN:			//Move down
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_DOWN, 0, "TILT_DOWN");
		break;
	case PAN_LEFT:			//Move left
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_LEFT, 0, "PAN_LEFT");
		break;
	case PAN_RIGHT:			//Move right
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_RIGHT, 0, "PAN_RIGHT");
		break;
	case ZOOM_IN:         //zoom in
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, ZOOM_IN, 0, "ZOOM_IN");
		break;
	case ZOOM_OUT:			//zoom out
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, ZOOM_OUT, 0, "ZOOM_OUT");
		break;
	case FOCUS_NEAR:			//focus in
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, FOCUS_NEAR, 0, "FOCUS_NEAR");
		break;
	case FOCUS_FAR:			//focus out
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, FOCUS_FAR, 0, "FOCUS_FAR");
		break;
	case IRIS_OPEN:			//iris open
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, IRIS_OPEN, 0, "IRIS_OPEN");
		break;
	case IRIS_CLOSE:			//iris close
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, IRIS_CLOSE, 0, "IRIS_CLOSE");
		break;
	case TILT_UP_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_UP_ZOOM_IN, 0, "TILT_UP_ZOOM_IN");
		break;
	case TILT_UP_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_UP_ZOOM_OUT, 0, "TILT_UP_ZOOM_OUT");
		break;
	case TILT_DOWN_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_DOWN_ZOOM_IN, 0, "TILT_DOWN_ZOOM_IN");
		break;
	case TILT_DOWN_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_DOWN_ZOOM_OUT, 0, "TILT_DOWN_ZOOM_OUT");
		break;
	case PAN_LEFT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_LEFT_ZOOM_IN, 0, "PAN_LEFT_ZOOM_IN");
		break;
	case PAN_LEFT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_LEFT_ZOOM_OUT, 0, "PAN_LEFT_ZOOM_OUT");
		break;
	case PAN_RIGHT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_RIGHT_ZOOM_IN, 0, "PAN_RIGHT_ZOOM_IN");
		break;
	case PAN_RIGHT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_RIGHT_ZOOM_OUT, 0, "PAN_RIGHT_ZOOM_OUT");
		break;
	case UP_LEFT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, UP_LEFT_ZOOM_IN, 0, "UP_LEFT_ZOOM_IN");
		break;
	case UP_LEFT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, UP_LEFT_ZOOM_OUT, 0, "UP_LEFT_ZOOM_OUT");
		break;
	case UP_RIGHT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, UP_RIGHT_ZOOM_IN, 0, "UP_RIGHT_ZOOM_IN");
		break;
	case UP_RIGHT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, UP_RIGHT_ZOOM_OUT, 0, "UP_RIGHT_ZOOM_OUT");
		break;
	case DOWN_LEFT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, DOWN_LEFT_ZOOM_IN, 0, "DOWN_LEFT_ZOOM_IN");
		break;
	case DOWN_LEFT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, DOWN_LEFT_ZOOM_OUT, 0, "DOWN_LEFT_ZOOM_OUT");
		break;
	case DOWN_RIGHT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, DOWN_RIGHT_ZOOM_IN, 0, "DOWN_RIGHT_ZOOM_IN");
		break;
	case DOWN_RIGHT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, DOWN_RIGHT_ZOOM_OUT, 0, "DOWN_RIGHT_ZOOM_OUT");
		break;
	default:
		break;
	}
	CButton::OnLButtonDown(nFlags, point);
}

void CPTZButton1::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL bRet;
	
	switch (m_iPTZType)
	{
	case TILT_UP:       //Move up
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_UP, 1, "TILT_UP");
		break;
	case TILT_DOWN:		//Move down
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_DOWN, 1, "TILT_DOWN");
		break;
	case PAN_LEFT:			//Move left
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_LEFT, 1, "PAN_LEFT");
		break;
	case PAN_RIGHT:		//Move right
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_RIGHT, 1, "PAN_RIGHT");
		break;
	case ZOOM_IN:         //zoom in
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, ZOOM_IN, 1, "ZOOM_IN");
		break;
	case ZOOM_OUT:			//zoom out
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, ZOOM_OUT, 1, "ZOOM_OUT");
		break;
	case FOCUS_NEAR:		//focus in
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, FOCUS_NEAR, 1, "FOCUS_NEAR");
		break;
	case FOCUS_FAR:			//focus out
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, FOCUS_FAR, 1, "FOCUS_FAR");
		break;
	case IRIS_OPEN:			//iris open
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, IRIS_OPEN, 1, "IRIS_OPEN");
		break;
	case IRIS_CLOSE:			//iris close
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, IRIS_CLOSE, 1, "IRIS_CLOSE");
		break;
	case TILT_UP_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_UP_ZOOM_IN, 1, "TILT_UP_ZOOM_IN");
		break;
	case TILT_UP_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_UP_ZOOM_OUT, 1, "TILT_UP_ZOOM_OUT");
		break;
	case TILT_DOWN_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_DOWN_ZOOM_IN, 1, "TILT_DOWN_ZOOM_IN");
		break;
	case TILT_DOWN_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, TILT_DOWN_ZOOM_OUT, 1, "TILT_DOWN_ZOOM_OUT");
		break;
	case PAN_LEFT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_LEFT_ZOOM_IN, 1, "PAN_LEFT_ZOOM_IN");
		break;
	case PAN_LEFT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_LEFT_ZOOM_OUT, 1, "PAN_LEFT_ZOOM_OUT");
		break;
	case PAN_RIGHT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_RIGHT_ZOOM_IN, 1, "PAN_RIGHT_ZOOM_IN");
		break;
	case PAN_RIGHT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, PAN_RIGHT_ZOOM_OUT, 1, "PAN_RIGHT_ZOOM_OUT");
		break;
	case UP_LEFT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, UP_LEFT_ZOOM_IN, 1, "UP_LEFT_ZOOM_IN");
		break;
	case UP_LEFT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, UP_LEFT_ZOOM_OUT, 1, "UP_LEFT_ZOOM_OUT");
		break;
	case UP_RIGHT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, UP_RIGHT_ZOOM_IN, 1, "UP_RIGHT_ZOOM_IN");
		break;
	case UP_RIGHT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, UP_RIGHT_ZOOM_OUT, 1, "UP_RIGHT_ZOOM_OUT");
		break;
	case DOWN_LEFT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, DOWN_LEFT_ZOOM_IN, 1, "DOWN_LEFT_ZOOM_IN");
		break;
	case DOWN_LEFT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, DOWN_LEFT_ZOOM_OUT, 1, "DOWN_LEFT_ZOOM_OUT");
		break;
	case DOWN_RIGHT_ZOOM_IN:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, DOWN_RIGHT_ZOOM_IN, 1, "DOWN_RIGHT_ZOOM_IN");
		break;
	case DOWN_RIGHT_ZOOM_OUT:      
		bRet = PTZControlAll(m_lPlayHandle, m_iDevIndex, m_iChannel, DOWN_RIGHT_ZOOM_OUT, 1, "DOWN_RIGHT_ZOOM_OUT");
		break;
	default:
		break;
	}
	if (!bRet)
	{
		char szLan[32] = {0};
		g_StringLanType(szLan, "ÔÆÌ¨¿ØÖÆÊ§°Ü", "ptz control failed!");
		MessageBox(szLan);
	}

	CButton::OnLButtonUp(nFlags, point);
}
