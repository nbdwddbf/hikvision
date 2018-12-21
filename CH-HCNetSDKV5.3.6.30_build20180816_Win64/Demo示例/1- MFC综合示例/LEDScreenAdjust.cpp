// LEDScreenAdjust.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "LEDScreenAdjust.h"
#include "afxdialogex.h"
HWND g_Hwnd;
void CALLBACK cbScreenAdjust(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
#define  IDC_EDIT 0xffff
#define  VM_SCRREEN_ADJUST_MESSAGE_SUCC 1001
#define  VM_SCRREEN_ADJUST_MESSAGE_FAIL 1002
#define  VM_SCRREEN_ADJUST_MESSAGE_FRESH 1003

// LEDScreenAdjust 对话框
NET_SDK_SCREEN_CHECK_RESPONSE_DATA g_struScreenCheckRespon = {0};
IMPLEMENT_DYNAMIC(LEDScreenAdjust, CDialog)

LEDScreenAdjust::LEDScreenAdjust(CWnd* pParent /*=NULL*/)
	: CDialog(LEDScreenAdjust::IDD, pParent)
	, m_lRgbPermil(0)
	, m_lRedPermil(0)
	, m_lGreenPermil(0)
	, m_lBluePermil(0)
{
}

LEDScreenAdjust::~LEDScreenAdjust()
{
}

void LEDScreenAdjust::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMB_OPERATETYPE, m_CombOperateType);
	DDX_Control(pDX, IDC_COMB_RGBSYNC, m_CombRGBSync);
	DDX_Control(pDX, IDC_LIST_SCREENAREA, m_List_ScreenArea);
	DDX_Text(pDX, IDC_EDIT_RGBPERMIL, m_lRgbPermil);
	DDX_Text(pDX, IDC_EDIT_REDPERMIL, m_lRedPermil);
	DDX_Text(pDX, IDC_EDIT_GREENPERMIL, m_lGreenPermil);
	DDX_Text(pDX, IDC_EDIT_BLUEPERMIL, m_lBluePermil);
	DDX_Control(pDX, IDC_PROG_SCREENADJUST, m_Progress_ScreenAdjust);
}


BEGIN_MESSAGE_MAP(LEDScreenAdjust, CDialog)
	ON_BN_CLICKED(IDC_BTN_OPERATE, &LEDScreenAdjust::OnBnClickedBtnOperate)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SCREENAREA, &LEDScreenAdjust::OnNMClickListScreenarea)
	ON_MESSAGE(VM_SCRREEN_ADJUST_MESSAGE_SUCC, OnScreenAdjustMessageSucc)
	ON_MESSAGE(VM_SCRREEN_ADJUST_MESSAGE_FAIL, OnScreenAdjustMessageFail)
	ON_MESSAGE(VM_SCRREEN_ADJUST_MESSAGE_FRESH, OnScreenAdjustMessageFresh)
END_MESSAGE_MAP()

LRESULT LEDScreenAdjust::OnScreenAdjustMessageSucc(WPARAM wParam, LPARAM lParam)
{
	if (m_lHandle == -1)
	{
		return 0;
	}
	NET_DVR_StopRemoteConfig(m_lHandle);
	//AfxMessageBox("操作成功");
	return 0;
}

LRESULT LEDScreenAdjust::OnScreenAdjustMessageFail(WPARAM wParam, LPARAM lParam)
{
	if (m_lHandle == -1)
	{
		return 0;
	}
	NET_DVR_StopRemoteConfig(m_lHandle);
	AfxMessageBox("操作失败");
	return 0;
}

LRESULT LEDScreenAdjust::OnScreenAdjustMessageFresh(WPARAM wParam, LPARAM lParam)
{
	if (m_lHandle == -1)
	{
		return 0;
	}
	//NET_DVR_StopRemoteConfig(m_lHandle);
	OnFreshList();
	return 0;
}

BOOL LEDScreenAdjust::OnInitDialog()
{
	CDialog::OnInitDialog();
	char szLan[128] = { 0 };

	RECT rect;
	m_List_ScreenArea.GetClientRect(&rect);
	g_StringLanType(szLan, "序号", "NO.");
	m_List_ScreenArea.InsertColumn(0, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "起点X坐标", "X");
	m_List_ScreenArea.InsertColumn(1, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "起点Y坐标", "Y");
	m_List_ScreenArea.InsertColumn(2, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "矩形宽度", "Weight");
	m_List_ScreenArea.InsertColumn(3, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "矩形高度", "Height");
	m_List_ScreenArea.InsertColumn(4, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "校正状态", "Status");
	m_List_ScreenArea.InsertColumn(5, szLan, LVCFMT_LEFT, 80);
	m_List_ScreenArea.SetExtendedStyle(m_List_ScreenArea.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	
	for (int i = 0; i<20; i++)
	{
		CString str;
		m_List_ScreenArea.InsertItem(i, NULL);
		str.Format("%d", i+1);
		m_List_ScreenArea.SetItemText(i, 0, str);
		str.Format("");
		m_List_ScreenArea.SetItemText(i, 1, str);
		m_List_ScreenArea.SetItemText(i, 2, str);
		m_List_ScreenArea.SetItemText(i, 3, str);
		m_List_ScreenArea.SetItemText(i, 4, str);
	}
	m_Progress_ScreenAdjust.SetPos(0);
	sprintf(szLan, "%d%%", 0);
	SetDlgItemText(IDC_STATIC_ADJUSTPROGRESS, szLan);
	m_CombOperateType.SetCurSel(0);
	m_CombRGBSync.SetCurSel(0);
	m_rowCount = m_List_ScreenArea.GetItemCount();
	m_lRgbPermil = 0;
	m_lRedPermil = 0;
	m_lGreenPermil = 0;
	m_lBluePermil = 0;
	m_bFreshed = FALSE;
	m_needSave = FALSE;
	g_Hwnd = this->GetSafeHwnd();

	return TRUE;
}



// LEDScreenAdjust 消息处理程序

void CALLBACK cbScreenAdjust(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	LEDScreenAdjust* pDlg = (LEDScreenAdjust*)pUserData;
	pDlg->OnScreenAdjust(dwType, lpBuffer, dwBufLen);
}


void LEDScreenAdjust::OnScreenAdjust(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
	CString strItem = "";
	WPARAM param1 = 0;
	LPARAM param2 = 0;
	//HWND hWnd1 = AfxGetMainWnd()->m_hWnd;
	if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
	{
		DWORD dwStatus = *(DWORD*)lpBuffer;
		
		if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
		{
			
			::PostMessage(g_Hwnd, VM_SCRREEN_ADJUST_MESSAGE_SUCC, (WPARAM)param1, (LPARAM)param2);
		}
		else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
		{
			::PostMessage(g_Hwnd, VM_SCRREEN_ADJUST_MESSAGE_FAIL, (WPARAM)param1, (LPARAM)param2);
		}
	}
	else if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
	{
		memset(&g_struScreenCheckRespon, 0, sizeof(g_struScreenCheckRespon));
		memcpy(&g_struScreenCheckRespon, lpBuffer, sizeof(g_struScreenCheckRespon));
	
		::PostMessage(g_Hwnd, VM_SCRREEN_ADJUST_MESSAGE_FRESH, (WPARAM)param1, (LPARAM)param2);
	}
	
}

void LEDScreenAdjust::OnFreshList()
{
	//UpdateData(TRUE);
	char szStatus[128] = { 0 };

	if (g_struScreenCheckRespon.byDataType == 1)	//进度
	{
		m_Progress_ScreenAdjust.SetPos(g_struScreenCheckRespon.byProgress);//g_struScreenCheckRespon.byProgress
		sprintf(szStatus, "%d%%", g_struScreenCheckRespon.byProgress);
		SetDlgItemText(IDC_STATIC_ADJUSTPROGRESS, szStatus);
		if (g_struScreenCheckRespon.byProgress == 100)
		{	
			//匹配到相应列并写入状态
			for (int i = 0; i < m_rowCountNew; i++)
			{
				/*if (g_struScreenCheckRespon.struRect.dwXCoordinate == m_struScreenCheck.struRectList[i].dwXCoordinate
					&& g_struScreenCheckRespon.struRect.dwYCoordinate == m_struScreenCheck.struRectList[i].dwYCoordinate
					&& g_struScreenCheckRespon.struRect.dwHeight == m_struScreenCheck.struRectList[i].dwHeight
					&& g_struScreenCheckRespon.struRect.dwWidth == m_struScreenCheck.struRectList[i].dwWidth)
					{*/
					sprintf(szStatus, "校正成功");
					CString cString = m_List_ScreenArea.GetItemText(i, 5);
					if (cString == "\0")
					{
						m_List_ScreenArea.SetItemText(i, 5, szStatus);
					}		
				//}
					/*else
					{
					continue;
					}*/
			}

		}
		m_bFreshed = TRUE;
	}
	else if (g_struScreenCheckRespon.byDataType == 2)	//状态
	{
		if (g_struScreenCheckRespon.byStatus == 1)//LED屏幕区域校正失败
		{
			//匹配到相应列并写入状态
			for (int i = 0; i < m_rowCountNew; i++)
			{
				if (g_struScreenCheckRespon.struRect.dwXCoordinate == m_struScreenCheck.struRectList[i].dwXCoordinate
					&& g_struScreenCheckRespon.struRect.dwYCoordinate == m_struScreenCheck.struRectList[i].dwYCoordinate
					&& g_struScreenCheckRespon.struRect.dwHeight == m_struScreenCheck.struRectList[i].dwHeight
					&& g_struScreenCheckRespon.struRect.dwWidth == m_struScreenCheck.struRectList[i].dwWidth)
				{
					sprintf(szStatus, "LED屏幕区域校正失败");
					m_List_ScreenArea.SetItemText(i, 5, szStatus);
				}
				else
				{
					continue;
				}
			}
			
			
		}
		else if (g_struScreenCheckRespon.byStatus == 2)//LED屏幕区域对应的接收卡不存在
		{
			//匹配到相应列并写入状态
			for (int i = 0; i < m_rowCountNew; i++)
			{
				if (g_struScreenCheckRespon.struRect.dwXCoordinate == m_struScreenCheck.struRectList[i].dwXCoordinate
					&& g_struScreenCheckRespon.struRect.dwYCoordinate == m_struScreenCheck.struRectList[i].dwYCoordinate
					&& g_struScreenCheckRespon.struRect.dwHeight == m_struScreenCheck.struRectList[i].dwHeight
					&& g_struScreenCheckRespon.struRect.dwWidth == m_struScreenCheck.struRectList[i].dwWidth)
				{
					sprintf(szStatus, "LED屏幕区域对应的接收卡不存在");
					m_List_ScreenArea.SetItemText(i, 5, szStatus);
				}
				else
				{
					continue;
				}
			}
		}
		m_bFreshed = TRUE;
	}
	UpdateData(FALSE);
}

void LEDScreenAdjust::OnBnClickedBtnOperate()
{
	// TODO:  在此添加控件通知处理程序代码
	//InitList();

	//NET_SDK_LED_SCREEN_CHECK_PARAM struScreenCheck = {0};
	UpdateData(TRUE);
	memset(&m_struScreenCheck, 0, sizeof(m_struScreenCheck));
	if (0 == m_CombRGBSync.GetCurSel())
	{
		m_struScreenCheck.byIsRGBSynChk = 0;
	}
	else
	{
		m_struScreenCheck.byIsRGBSynChk = 1;
	}
	m_struScreenCheck.byOperateType = m_CombOperateType.GetCurSel() + 1;
	m_struScreenCheck.wRgbPermil = m_lRgbPermil;
	m_struScreenCheck.wRedPermil = m_lRedPermil;
	m_struScreenCheck.wGreenPermil = m_lGreenPermil;
	m_struScreenCheck.wBluePermil = m_lBluePermil;
	int j = 0;
	for (int i = 0; i < m_rowCount; i++)
	{
		DWORD dwX;
		DWORD dwY;
		DWORD dwW;
		DWORD dwH;
		
		dwX = atol(m_List_ScreenArea.GetItemText(i, 1));
		dwY = atol(m_List_ScreenArea.GetItemText(i, 2));
		dwW = atol(m_List_ScreenArea.GetItemText(i, 3));
		dwH = atol(m_List_ScreenArea.GetItemText(i, 4));
		if (dwX==0 && dwY==0 && dwW==0 && dwH==0)
		{
			continue;
		}
		m_struScreenCheck.struRectList[j].dwXCoordinate = dwX;
		m_struScreenCheck.struRectList[j].dwYCoordinate = dwY;
		m_struScreenCheck.struRectList[j].dwWidth = dwW;
		m_struScreenCheck.struRectList[j].dwHeight = dwH;
		j++;
		
	}
	m_rowCountNew = j;
	m_struScreenCheck.dwRectCount = m_rowCountNew;
	m_struScreenCheck.dwSize = sizeof(m_struScreenCheck);
	LONG UserData = 0;
	char szErrLan[128] = { 0 };
	m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_SDK_LED_SCREEN_CHECK, &m_struScreenCheck, sizeof(m_struScreenCheck),
		(cbScreenAdjust), &UserData);
	if (m_lHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_SDK_LED_SCREEN_CHECK err=%d", NET_DVR_GetLastError());
		
		/*sprintf_s(szErrLan, "ErrCode:%d", NET_DVR_GetLastError());
		AfxMessageBox(szErrLan);*/
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_SDK_LED_SCREEN_CHECK err=%d", NET_DVR_GetLastError());
		sprintf_s(szErrLan, "ErrCode:%d", NET_DVR_GetLastError());
		AfxMessageBox(szErrLan);
	}
	//m_Progress_ScreenAdjust.SetPos(0);
	//int i = 200;
	//while(i--)// && g_struScreenCheckRespon.byProgress<100
	//{
	//	OnFreshList();
	//}
	//::PostMessage(g_pMainDlg->m_hWnd, (UINT)1003, (WPARAM)param1, (LPARAM)param2);

	UpdateData(FALSE);

}



void LEDScreenAdjust::OnNMClickListScreenarea(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;

	CRect  EditRect;

	if (m_needSave)
	{
		//needSave == TURE
		CString  EditStr;
		m_Edit.GetWindowText(EditStr); //获取输入的内容
		m_List_ScreenArea.SetItemText(m_Item, m_SubItem, EditStr); //m_Item,m_SubItem这两个变量的值是原来的单元格的值

	}

	m_Item = pEditCtrl->iItem;
	m_SubItem = pEditCtrl->iSubItem;
	if (m_Item == -1)
	{
		return;
	}
	if (m_Item < MAX_SCREEN_AREA_NUM)
	{
		m_List_ScreenArea.GetSubItemRect(m_Item, m_SubItem, LVIR_LABEL, EditRect);
		m_needSave = TRUE;
		if (m_Edit.m_hWnd == NULL)

		{    
			m_Edit.Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN | WS_BORDER,
				CRect(0, 0, 0, 0), this, IDC_EDIT);

			//IDC_EDIT已近在头文件中定义,这个很重要,很多时候会忽略,
			//网上找到的实现编辑办法中这个都没说明
			//我定义为#define  IDC_EDIT 0xffff
			m_Edit.ShowWindow(SW_HIDE); //Edit创建完后隐藏
			m_Edit.SetFont(this->GetFont(), FALSE);//设置字体
		}
		m_Edit.SetParent(&m_List_ScreenArea); //将list control设置为父窗口,生成的Edit才能正确定位,这个也很重要,

		EditRect.SetRect(EditRect.left, EditRect.top, EditRect.left + m_List_ScreenArea.GetColumnWidth(m_SubItem), EditRect.bottom);
		//m_list.GetColumnWidth(m_SubItem)获取列的宽度

		CString strItem = m_List_ScreenArea.GetItemText(m_Item, m_SubItem);
		m_Edit.MoveWindow(&EditRect);
		m_Edit.ShowWindow(SW_SHOW);
		m_Edit.SetWindowText(strItem);
		m_Edit.SetFocus();//设置为焦点
		m_Edit.SetSel(0, -1);  //0,-1表示单元格内容全选中

	}
	*pResult = 0;
}
