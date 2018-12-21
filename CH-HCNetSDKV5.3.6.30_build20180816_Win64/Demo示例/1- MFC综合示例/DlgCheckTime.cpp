/**********************************************************
FileName:    DlgCheckTime.cpp
Description: check the time of the devices      
Date:        11/19/2008
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <11/19/2008>       <created>
***********************************************************/
#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCheckTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCheckTime dialog

/*********************************************************
  Function:	CDlgCheckTime
  Desc:		Constructor
  Input:	pParent, parent window pointer
  Output:	none
  Return:	none
**********************************************************/
CDlgCheckTime::CDlgCheckTime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCheckTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCheckTime)
	m_checkDate = COleDateTime::GetCurrentTime();
	m_checkTime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	pDX, CDataExchange,pass the data exchange object to the window CWnd::DoDataExchange
  Output:	none
  Return:	none
**********************************************************/
void CDlgCheckTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCheckTime)
	DDX_Control(pDX, IDC_TREEALL, m_treeAll);
	DDX_DateTimeCtrl(pDX, IDC_CHECK_DATE, m_checkDate);
	DDX_DateTimeCtrl(pDX, IDC_CHECK_TIME, m_checkTime);
	//}}AFX_DATA_MAP
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	pDX, CDataExchange,pass the data exchange object to the window CWnd::DoDataExchange
  Output:	none
  Return:	none
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgCheckTime, CDialog)
	//{{AFX_MSG_MAP(CDlgCheckTime)
	ON_BN_CLICKED(ID_BTN_CHECK_TIME, OnBtnCheckTime)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_NOTIFY(NM_CLICK, IDC_TREEALL, OnClickTreeall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BOOL CDlgCheckTime::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	LoadTreeImage();
	CreateTree();
	COleDateTime timeCur = COleDateTime::GetCurrentTime();
	COleDateTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),\
		timeCur.GetHour(), timeCur.GetMinute(), timeCur.GetSecond());
	m_checkDate = timeStart;
	m_checkTime = timeStart;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	CreateTree	
  Desc:		create the device tree
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgCheckTime::CreateTree(void)
{
	HTREEITEM hRoot = m_treeAll.InsertItem("All Devices", TREE_ALL, TREE_ALL,TVI_ROOT);
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hDevice = NULL;
	for (i = 0; i < MAX_DEVICES; i++)
	{
		if (g_struDeviceInfo[i].iDeviceChanNum != -1)
		{
			strTemp.Format("%s", g_struDeviceInfo[i].chLocalNodeName);
			if (g_struDeviceInfo[i].lLoginID >= 0)
			{
				hDevice =  m_treeAll.InsertItem(strTemp, DEVICE_LOGIN, DEVICE_LOGIN,hRoot);
				m_treeAll.SetItemData(hDevice, DEVICE_LOGIN*1000 + g_struDeviceInfo[i].iDeviceIndex);
			}
			else
			{
				hDevice =  m_treeAll.InsertItem(strTemp, DEVICE_LOGOUT, DEVICE_LOGOUT,hRoot);
				m_treeAll.SetItemData(hDevice, DEVICE_LOGOUT*1000 + g_struDeviceInfo[i].iDeviceIndex);
			}	
		}
	}
	m_treeAll.Expand(hRoot,TVE_EXPAND);
	m_treeAll.Expand(m_treeAll.GetRootItem(),TVE_EXPAND);
}

/*********************************************************
  Function:	OnClickTreeall
  Desc:		choose the tree node, and update parameters
  Input:	pNMHDR, Contains the click information
  Output:	pResult, result after handle notification
  Return:	none
**********************************************************/
void CDlgCheckTime::OnClickTreeall(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREEALL)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;

	UINT uFlag = 0;
	HTREEITEM hSelect= m_treeAll.HitTest(pt, &uFlag);

	if (NULL == hSelect) 
	{
		return;
	}
	
	m_treeAll.SelectItem(hSelect);

	BOOL bCheck = m_treeAll.GetCheck(hSelect);
	bCheck = !bCheck;

	if (TREE_ALL_T == m_treeAll.GetItemData(hSelect)/1000)
	{
		CheckAllDevState(hSelect, bCheck, uFlag);
	}
	else
	{
		int iDevIndex = m_treeAll.GetItemData(hSelect)%1000;
		if ((g_struDeviceInfo[iDevIndex].lLoginID >= 0 && uFlag != LVHT_TOLEFT)\
			|| (g_struDeviceInfo[iDevIndex].lLoginID < 0 && uFlag == LVHT_TOLEFT) )
		{
			m_treeAll.SetCheck(hSelect, bCheck);
		}
		else
		{
			m_treeAll.SetCheck(hSelect, !bCheck);
		}
	}

	*pResult = 0;
}

/*********************************************************
  Function:	CheckAllDevState
  Desc:		choose all the logined device
  Input:	hRoot, root node item;bCheck, status of the check box; uFlag, the click item flag data
  Output:	none
  Return:	none
**********************************************************/
void CDlgCheckTime::CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag)
{
	if (uFlag == LVHT_TOLEFT)
	{
		m_treeAll.SetCheck(hRoot, !bCheck);
	}
	else
	{
		m_treeAll.SetCheck(hRoot, bCheck);
	}
	

	HTREEITEM hChild = m_treeAll.GetChildItem(hRoot);
	while (hChild)
	{
		int iDevIndex = m_treeAll.GetItemData(hChild)%1000;
		if (g_struDeviceInfo[iDevIndex].lLoginID >= 0)
		{
			m_treeAll.SetCheck(hChild, bCheck);
		}

		hChild = m_treeAll.GetNextSiblingItem(hChild);
	}
}

/*********************************************************
  Function:	LoadTreeImage
  Desc:		load the tree image
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgCheckTime::LoadTreeImage(void)
{
	CBitmap bmp[3];

	m_TreeImage.Create(16,16,ILC_COLOR32 | ILC_MASK,1,1);
	bmp[TREE_ALL].LoadBitmap(IDB_BITMAP_TREE);
	m_TreeImage.Add(&bmp[TREE_ALL],RGB(1,1,1));
	bmp[DEVICE_LOGOUT].LoadBitmap(IDB_BITMAP_LOGOUT);
	m_TreeImage.Add(&bmp[DEVICE_LOGOUT],RGB(1,1,1));
	bmp[DEVICE_LOGIN].LoadBitmap(IDB_BITMAP_LOGIN);
	m_TreeImage.Add(&bmp[DEVICE_LOGIN],RGB(1,1,1));
	
	m_treeAll.SetImageList(&m_TreeImage, LVSIL_NORMAL);
}

/*********************************************************
  Function:	OnBtnCheckTime
  Desc:		check the device time
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgCheckTime::OnBtnCheckTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_TIME CurTime;
	char szLan[1024] = {0};
	CurTime.dwYear = m_checkDate.GetYear();
	CurTime.dwMonth = m_checkDate.GetMonth();
	CurTime.dwDay = m_checkDate.GetDay();
	CurTime.dwHour = m_checkTime.GetHour();
	CurTime.dwMinute = m_checkTime.GetMinute();
	CurTime.dwSecond = m_checkTime.GetSecond();
	
	HTREEITEM hRoot;
	HTREEITEM hChild;

	int iDevIndex = 0;
	CString sTemp;
	BOOL bChk = FALSE;
	BOOL bFail = FALSE;
	
	hRoot = m_treeAll.GetRootItem();
	if (hRoot==NULL)
	{
		return;
	}

	hChild = m_treeAll.GetChildItem(hRoot);
	
	while(hChild!=NULL)
	{
		iDevIndex=m_treeAll.GetItemData(hChild)%1000;
		bChk = m_treeAll.GetCheck(hChild);
		if(bChk)
		{
			if(!NET_DVR_SetDVRConfig(g_struDeviceInfo[iDevIndex].lLoginID, NET_DVR_SET_TIMECFG, 0\
				, &CurTime, sizeof(NET_DVR_TIME)))
			{	
				m_treeAll.SetItemImage(hChild,0,0);
				g_pMainDlg->AddLog(iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TIMECFG");
				bFail = TRUE;
			}
			else
			{
				g_pMainDlg->AddLog(iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TIMECFG");
			}
		}

		hChild =m_treeAll.GetNextSiblingItem(hChild);
	}	
	if (bFail)
	{
		g_StringLanType(szLan, "校时失败!", "check time fail!");
	}
	else
	{	
		g_StringLanType(szLan, "校时完成!", "check time succ!");
	}

	AfxMessageBox(szLan);
			
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		exit the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgCheckTime::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
