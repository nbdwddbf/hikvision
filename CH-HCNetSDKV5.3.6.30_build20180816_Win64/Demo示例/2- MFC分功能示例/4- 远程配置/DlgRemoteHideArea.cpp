/**********************************************************
FileName:    DlgRemoteHideArea.cpp
Description: 遮盖处理      
Date:        
Note: 		
Modification History:      
<version> <time>         <desc>
    
***********************************************************/


#include "stdafx.h"
#include "DlgRemoteHideArea.h"

RECT g_rectHideAreaShow[MAX_SHELTERNUM];//遮盖显示区域
RECT g_rectHideAreaMouse[MAX_SHELTERNUM];//遮盖设置区域
int	g_iHideAreaCount = 4;//遮盖区域个数

/*********************************************************
  Function:	ShelterAreaGetCallBack
  Desc:		遮盖区域获取并显示的实现函数
  Input:	
  Output:	
  Return:	
**********************************************************/
void CALLBACK ShelterAreaGetCallBack(LONG nPort,HDC hDc,DWORD nUser)
{
	CRect rect;
	int i = 0,j = 0;
	//CPoint point;
	HBRUSH hBrush=::CreateSolidBrush(COLORREF(0xffffff));

	for (i=0; i<g_iHideAreaCount; i++)
	{
		rect.left = g_rectHideAreaMouse[i].left;
		rect.top = g_rectHideAreaMouse[i].top;
		rect.right = g_rectHideAreaMouse[i].right;
		rect.bottom = g_rectHideAreaMouse[i].bottom;
		::FillRect(hDc, &rect, hBrush);
		//::DrawEdge(hDc,&rect,BDR_SUNKENOUTER,BF_RECT);
	}
	SetBkMode(hDc,TRANSPARENT);
}

/*********************************************************
  Function:	ShelterAreaSetCallBack
  Desc:		设置遮盖时的区域显示
  Input:	
  Output:	
  Return:	
**********************************************************/
void CALLBACK ShelterAreaSetCallBack(LONG nPort,HDC hDc,DWORD nUser)
{
	for (int i=0; i<g_iHideAreaCount; i++)
	{
		::DrawEdge(hDc,&g_rectHideAreaShow[i],BDR_SUNKENOUTER,BF_RECT);
	}
	SetBkMode(hDc,TRANSPARENT);
}

// CDlgRemoteHideArea dialog
/*********************************************************
  Function:	CDlgRemoteHideArea
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteHideArea, CDialog)
CDlgRemoteHideArea::CDlgRemoteHideArea(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteHideArea::IDD, pParent)
	, m_bCheckHideAreaShow(FALSE)
	, m_bCheckHideAreaSet(FALSE)
	, m_iChanShowNum(0)
	, m_lLoginID(-1)
	, m_bDrawdetect(FALSE)
	, m_lPlayHandle(NULL)
{
	memset(&m_struShelter, 0, sizeof(NET_DVR_SHELTER));
}

/*********************************************************
  Function:	CDlgRemoteHideArea
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgRemoteHideArea::~CDlgRemoteHideArea()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteHideArea::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteHideArea)
	DDX_Check(pDX, IDC_CHK_HIDE_AREA_SHOW, m_bCheckHideAreaShow);
	DDX_Check(pDX, IDC_CHK_HIDE_AREA_SET, m_bCheckHideAreaSet);
	DDX_Control(pDX, IDC_PIC_DETECT_AREA, m_picDetectArea);
    //}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteHideArea, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteHideArea)	
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(ID_BTN_HIDE_AREA_OK, OnBnClickedBtnHideAreaOk)
	ON_BN_CLICKED(ID_BTN_HIDE_AREA_EXIT, OnBnClickedBtnHideAreaExit)
	ON_BN_CLICKED(IDC_CHK_HIDE_AREA_SHOW, OnBnClickedChkHideAreaShow)
	ON_BN_CLICKED(IDC_CHK_HIDE_AREA_SET, OnBnClickedChkHideAreaSet)
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()


// CDlgRemoteHideArea message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteHideArea::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	int i;
	m_picDetectArea.MoveWindow(DETECT_AREA_LEFT,DETECT_AREA_TOP, 352, 288);
	for (i=0; i<MAX_SHELTERNUM; i++)
	{
		g_rectHideAreaMouse[i].left = m_struShelter[i].wHideAreaTopLeftX/2;
		g_rectHideAreaMouse[i].top = m_struShelter[i].wHideAreaTopLeftY/2;
		g_rectHideAreaMouse[i].bottom = (m_struShelter[i].wHideAreaTopLeftY+m_struShelter[i].wHideAreaHeight)/2;
		g_rectHideAreaMouse[i].right = (m_struShelter[i].wHideAreaTopLeftX+m_struShelter[i].wHideAreaWidth)/2;
	}	
	NET_DVR_CLIENTINFO struPlayInfo;
	struPlayInfo.hPlayWnd = m_picDetectArea.GetSafeHwnd();
	struPlayInfo.lChannel = m_iChanShowNum;
	struPlayInfo.lLinkMode = 0;
	struPlayInfo.sMultiCastIP = "";	 

	m_lPlayHandle = NET_DVR_RealPlay(m_lLoginID, &struPlayInfo);	
	if (m_lPlayHandle == -1)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "网络连接失败", "Network connection failure");
		AfxMessageBox(szLan);
	}	
	m_bDrawdetect = FALSE;
	GetDlgItem(IDC_CHK_HIDE_AREA_SHOW)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHK_HIDE_AREA_SET)->EnableWindow(TRUE);	
	return TRUE;
}

/*********************************************************
  Function:	OnLButtonDown
  Desc:		鼠标左键加ctrl键响应函数,画遮盖设置区域
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideArea::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bDrawdetect)
	{
		if (MK_CONTROL&nFlags)
		{
			NET_DVR_RigisterDrawFun(m_lPlayHandle, ShelterAreaSetCallBack, 0);
			if (g_iHideAreaCount >=MAX_SHELTERNUM)
				g_iHideAreaCount = 0;
			point.x -= DETECT_AREA_LEFT;
			point.y -= DETECT_AREA_TOP;
			if (point.x < 0)
				point.x = 0;
			g_rectHideAreaMouse[g_iHideAreaCount].left=point.x/16*16;
			if (point.y < 0)
				point.y = 0;
			g_rectHideAreaMouse[g_iHideAreaCount].top=point.y/16*16;
			g_rectHideAreaMouse[g_iHideAreaCount].right=g_rectHideAreaMouse[g_iHideAreaCount].left;
			g_rectHideAreaMouse[g_iHideAreaCount].bottom=g_rectHideAreaMouse[g_iHideAreaCount].top;
			POINT tPoint=point;
			g_rectHideAreaShow[g_iHideAreaCount].left=tPoint.x/16*16;
			g_rectHideAreaShow[g_iHideAreaCount].top=tPoint.y/16*16;
			g_rectHideAreaShow[g_iHideAreaCount].right=tPoint.x/16*16+1;
			g_rectHideAreaShow[g_iHideAreaCount].bottom=tPoint.y/16*16+1;
			g_iHideAreaCount ++;
		}
	}		
	CDialog::OnLButtonDown(nFlags, point);
}

/*********************************************************
  Function:	OnMouseMove
  Desc:		鼠标拖动加左键结合,设置遮盖区域
  Input:	nFlags,功能键状态;point,鼠标位置
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideArea::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDrawdetect)
	{
		if (MK_CONTROL&nFlags&&MK_LBUTTON&nFlags)
		{
			point.x -= DETECT_AREA_LEFT;
			point.y -= DETECT_AREA_TOP;
			if (point.x > 352)
				point.x = 352;
			g_rectHideAreaMouse[g_iHideAreaCount-1].right=point.x/16*16;
			if (point.y > 288)
				point.y = 288;
			g_rectHideAreaMouse[g_iHideAreaCount-1].bottom=point.y/16*16;
			POINT tPoint=point;
			g_rectHideAreaShow[g_iHideAreaCount-1].right=tPoint.x/16*16;
			g_rectHideAreaShow[g_iHideAreaCount-1].bottom=tPoint.y/16*16;
		}
	}	
	CDialog::OnMouseMove(nFlags, point);
}

/*********************************************************
  Function:	OnBnClickedBtnHideAreaOk
  Desc:		完称遮盖区域设置;
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideArea::OnBnClickedBtnHideAreaOk()
{
	int k=0;
	for (k=0; k<MAX_SHELTERNUM; k++)
	{
		m_struShelter[k].wHideAreaTopLeftX = 0;
		m_struShelter[k].wHideAreaTopLeftY = 0;
		m_struShelter[k].wHideAreaWidth = 0;
		m_struShelter[k].wHideAreaHeight = 0;
	}
	for (k=0; k<g_iHideAreaCount; k++)
	{
		if (g_rectHideAreaMouse[k].top <= g_rectHideAreaMouse[k].bottom)
		{
			if (g_rectHideAreaMouse[k].left <= g_rectHideAreaMouse[k].right)
			{
				m_struShelter[k].wHideAreaTopLeftX = (WORD)g_rectHideAreaMouse[k].left*2;
				m_struShelter[k].wHideAreaTopLeftY = (WORD)g_rectHideAreaMouse[k].top*2;
				m_struShelter[k].wHideAreaWidth = (WORD)(g_rectHideAreaMouse[k].right-g_rectHideAreaMouse[k].left)*2;
				m_struShelter[k].wHideAreaHeight = (WORD)(g_rectHideAreaMouse[k].bottom-g_rectHideAreaMouse[k].top)*2;		
			}
			else
			{
				m_struShelter[k].wHideAreaTopLeftX = (WORD)g_rectHideAreaMouse[k].right*2;
				m_struShelter[k].wHideAreaTopLeftY = (WORD)g_rectHideAreaMouse[k].top*2;
				m_struShelter[k].wHideAreaWidth = (WORD)(g_rectHideAreaMouse[k].left-g_rectHideAreaMouse[k].right)*2;
				m_struShelter[k].wHideAreaHeight = (WORD)(g_rectHideAreaMouse[k].bottom-g_rectHideAreaMouse[k].top)*2;						
			}
		}
		else
		{
			if (g_rectHideAreaMouse[k].left <= g_rectHideAreaMouse[k].right)
			{
				m_struShelter[k].wHideAreaTopLeftX = (WORD)g_rectHideAreaMouse[k].left*2;
				m_struShelter[k].wHideAreaTopLeftY = (WORD)g_rectHideAreaMouse[k].bottom*2;
				m_struShelter[k].wHideAreaWidth = (WORD)(g_rectHideAreaMouse[k].right-g_rectHideAreaMouse[k].left)*2;
				m_struShelter[k].wHideAreaHeight = (WORD)(g_rectHideAreaMouse[k].top-g_rectHideAreaMouse[k].bottom)*2;
			}
			else
			{
				m_struShelter[k].wHideAreaTopLeftX = (WORD)g_rectHideAreaMouse[k].right*2;
				m_struShelter[k].wHideAreaTopLeftY = (WORD)g_rectHideAreaMouse[k].bottom*2;
				m_struShelter[k].wHideAreaWidth = (WORD)(g_rectHideAreaMouse[k].left-g_rectHideAreaMouse[k].right)*2;
				m_struShelter[k].wHideAreaHeight = (WORD)(g_rectHideAreaMouse[k].top-g_rectHideAreaMouse[k].bottom)*2;
			}
		}
	}
}

/*********************************************************
  Function:	OnBnClickedBtnHideAreaExit
  Desc:		取消区域设置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideArea::OnBnClickedBtnHideAreaExit()
{
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedChkHideAreaShow
  Desc:		显示已经设置的遮盖区域
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideArea::OnBnClickedChkHideAreaShow()
{
	if (m_lPlayHandle < 0)
		return;
	UpdateData(TRUE);
	if (m_bCheckHideAreaSet)
	{
		m_bCheckHideAreaSet = FALSE;
		m_bDrawdetect = FALSE;
		UpdateData(FALSE);
		GetDlgItem(ID_BTN_HIDE_AREA_OK)->EnableWindow(FALSE);
	}
	if (m_bCheckHideAreaShow)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		Sleep(200);
		NET_DVR_RigisterDrawFun(m_lPlayHandle,ShelterAreaGetCallBack, 0);
	}
	else
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
	}
}

/*********************************************************
  Function:	OnBnClickedChkHideAreaSet
  Desc:		开始遮盖区域设置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideArea::OnBnClickedChkHideAreaSet()
{
	if (m_lPlayHandle < 0)
		return;
	UpdateData(TRUE);
	if (m_bCheckHideAreaShow)
	{
		m_bCheckHideAreaShow = FALSE;
		UpdateData(FALSE);
	}
	if (m_bCheckHideAreaSet)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL,0);
		m_bDrawdetect = TRUE;
		g_iHideAreaCount = 0;
		for (int i=0; i<MAX_SHELTERNUM; i++)
		{
			g_rectHideAreaMouse[i].left = 0;
			g_rectHideAreaMouse[i].top = 0;
			g_rectHideAreaMouse[i].bottom = 0;
			g_rectHideAreaMouse[i].right = 0;
		}
		GetDlgItem(ID_BTN_HIDE_AREA_OK)->EnableWindow(TRUE);
	}
	else
	{
		m_bDrawdetect = FALSE;
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL,0);
		GetDlgItem(ID_BTN_HIDE_AREA_OK)->EnableWindow(FALSE);
	}
}

/*********************************************************
Function:	OnCancel
Desc:		按ESC退出窗口，释放播放资源。
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteHideArea::OnCancel() 
{
	NET_DVR_StopRealPlay(m_lPlayHandle);
	CDialog::OnCancel();
}
