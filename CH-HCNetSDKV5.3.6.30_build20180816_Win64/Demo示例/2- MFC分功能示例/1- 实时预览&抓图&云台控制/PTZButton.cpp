/*******************************************************
Copyright 2008-2011 Digital Technology Co., Ltd. 
文  件：	PTZButton.cpp
开发单位：	杭州
编  写：	shizhiping
日  期：	2009.5
描  述：	云台按钮类
修  改：	
********************************************************/
#include "stdafx.h"
#include "RealPlay.h"
#include "PTZButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int g_iPtzBtnIndex  = 0;
/////////////////////////////////////////////////////////////////////////////
// CPTZButton

CPTZButton::CPTZButton()
{
	m_iSubBtnIndex = g_iPtzBtnIndex++;
	m_lPlayHandle  = -1;
}

CPTZButton::~CPTZButton()
{

}


BEGIN_MESSAGE_MAP(CPTZButton, CButton)
	//{{AFX_MSG_MAP(CPTZButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPTZButton message handlers

/*************************************************
函数名:    	OnLButtonDown
函数描述:	鼠标左键按下，开始云台动作
输入参数:   
输出参数:   			
返回值:		
*************************************************/
void CPTZButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	LONG lPlayHandle = g_pMainDlg->GetPlayHandle();
	int iPTZSpeed = g_pMainDlg->GetPTZSpeed();
	switch(m_iSubBtnIndex)
	{
	case 0:        //云台上
		PTZControlAll(lPlayHandle,TILT_UP,0,iPTZSpeed);
		break;
	case 1:			//云台下
		PTZControlAll(lPlayHandle,TILT_DOWN,0,iPTZSpeed);
		break;
	case 2:			//云台左
		PTZControlAll(lPlayHandle,PAN_LEFT,0,iPTZSpeed);
		break;
	case 3:			//云台右
		PTZControlAll(lPlayHandle,PAN_RIGHT,0,iPTZSpeed);
		break;
	case 4:         //调焦左
		PTZControlAll(lPlayHandle,ZOOM_IN,0,iPTZSpeed);
		break;
	case 5:			//调焦右
		PTZControlAll(lPlayHandle,ZOOM_OUT,0,iPTZSpeed);
		break;
	case 6:			//聚焦左
		PTZControlAll(lPlayHandle,FOCUS_NEAR,0,iPTZSpeed);
		break;
	case 7:			//聚焦右
		PTZControlAll(lPlayHandle,FOCUS_FAR,0,iPTZSpeed);
		break;
	case 8:			//光圈左
		PTZControlAll(lPlayHandle,IRIS_OPEN,0,iPTZSpeed);
		break;
	case 9:			//光圈右
		PTZControlAll(lPlayHandle,IRIS_CLOSE,0,iPTZSpeed);
		break;
	case 10:        //左上
		PTZControlAll(lPlayHandle,UP_LEFT,0,iPTZSpeed);
		break;
	case 11:        //右上
		PTZControlAll(lPlayHandle,UP_RIGHT,0,iPTZSpeed);
		break;
	case 12:        //左下
		PTZControlAll(lPlayHandle,DOWN_LEFT,0,iPTZSpeed);
		break;
	case 13:        //右下
		PTZControlAll(lPlayHandle,DOWN_RIGHT,0,iPTZSpeed);
		break;

	default:
		break;
	}
	
	CButton::OnLButtonDown(nFlags, point);
}

/*************************************************
函数名:    	OnLButtonUp
函数描述:	鼠标左键弹起，停止云台动作
输入参数:   
输出参数:   			
返回值:		
*************************************************/
void CPTZButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
//	int iChanIndex = pMainDlg->GetCurChanIndex();
	LONG lPlayHandle = g_pMainDlg->GetPlayHandle();
	int iPTZSpeed = g_pMainDlg->GetPTZSpeed();
	switch(m_iSubBtnIndex)
	{
	case 0:        //云台上
		PTZControlAll(lPlayHandle,TILT_UP,1,iPTZSpeed);
		break;
	case 1:			//云台下
		PTZControlAll(lPlayHandle,TILT_DOWN,1,iPTZSpeed);
		break;
	case 2:			//云台左
		PTZControlAll(lPlayHandle,PAN_LEFT,1,iPTZSpeed);
		break;
	case 3:			//云台右
		PTZControlAll(lPlayHandle,PAN_RIGHT,1,iPTZSpeed);
		break;
	case 4:         //调焦左
		PTZControlAll(lPlayHandle,ZOOM_IN,1,iPTZSpeed);
		break;
	case 5:			//调焦右
		PTZControlAll(lPlayHandle,ZOOM_OUT,1,iPTZSpeed);
		break;
	case 6:			//聚焦左
		PTZControlAll(lPlayHandle,FOCUS_NEAR,1,iPTZSpeed);
		break;
	case 7:			//聚焦右
		PTZControlAll(lPlayHandle,FOCUS_FAR,1,iPTZSpeed);
		break;
	case 8:			//光圈左
		PTZControlAll(lPlayHandle,IRIS_OPEN,1,iPTZSpeed);
		break;
	case 9:			//光圈右
		PTZControlAll(lPlayHandle,IRIS_CLOSE,1,iPTZSpeed);
		break;
	case 10:        //左上
		PTZControlAll(lPlayHandle,UP_LEFT,1,iPTZSpeed);
		break;
	case 11:        //右上
		PTZControlAll(lPlayHandle,UP_RIGHT,1,iPTZSpeed);
		break;
	case 12:        //左下
		PTZControlAll(lPlayHandle,DOWN_LEFT,1,iPTZSpeed);
		break;
	case 13:        //右下
		PTZControlAll(lPlayHandle,DOWN_RIGHT,1,iPTZSpeed);
		break;
//	case 14:        //自动
//		PTZControlAll(lPlayHandle,PAN_AUTO,1,iPTZSpeed);
//		break;
	default:
		break;
	}
	CButton::OnLButtonUp(nFlags, point);
}

/*************************************************
函数名:    	PTZControlAll
函数描述:	云台控制函数
输入参数:   
输出参数:   			
返回值:		
*************************************************/
void CPTZButton::PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop, int Speed)
{
	if(lRealHandle>=0)
	{
		BOOL ret;
		if(Speed>=1)
		{
			ret = NET_DVR_PTZControlWithSpeed(lRealHandle,dwPTZCommand,dwStop,Speed);
			if(!ret)
			{
				MessageBox("云台控制失败!");
				return;
			}
		}
		else
		{
			ret = NET_DVR_PTZControl(lRealHandle,dwPTZCommand,dwStop);
			if(!ret)
			{
				MessageBox("云台控制失败!");
				return;
			}
		}
	}

}
