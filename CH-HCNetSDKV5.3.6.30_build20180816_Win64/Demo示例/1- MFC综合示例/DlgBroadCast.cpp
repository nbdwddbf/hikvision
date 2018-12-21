/**********************************************************
FileName:    DlgBroadCast.cpp
Description: audio broadcast    
Date:        2008/06/10
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/10>       <created>
***********************************************************/

#include "stdafx.h"
#include "clientdemo.h"
#include "ClientDemoDlg.h"
#include ".\dlgbroadcast.h"
// CBroadCast dialog

FILE* fpCast1 = NULL;
FILE* fpCast2 = NULL;
void CALLBACK fAudioCastDataCallBack(char *pRecvDataBuffer, DWORD dwBufSize, void *pUser)
{
// 	if (!fpCast1)
// 	{
// 		fpCast1 = fopen("D:\\Castlocal.264","wb");
// 	}
	
// 	if (!fp2)
// 	{
// 		fp2 = fopen("D:\\device.264","wb");
// 	}
	
//	fwrite(pRecvDataBuffer, 1, dwBufSize, fpCast1);

}

/*********************************************************
  Function:	CDlgBroadCast
  Desc:		Constructor
  Input:	pParent, parent window pointer
  Output:	none
  Return:	none
**********************************************************/
IMPLEMENT_DYNAMIC(CBroadCast, CDialog)
CBroadCast::CBroadCast(CWnd* pParent /*=NULL*/)
	: CDialog(CBroadCast::IDD, pParent)
{
}

/*********************************************************
  Function:	~CDlgBroadCast
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CBroadCast::~CBroadCast()
{
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	pDX, CDataExchange,pass the data exchange object to the window CWnd::DoDataExchange
  Output:	none
  Return:	none
**********************************************************/
void CBroadCast::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBroadCast)
	DDX_Control(pDX, IDC_TREEALL, m_treeBroadCast);
	//}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	first parameter:name of current class; second: name of base class
  Output:	none
  Return:	none
**********************************************************/
BEGIN_MESSAGE_MAP(CBroadCast, CDialog)
	//{{AFX_MSG_MAP(CBroadCast)	
	ON_NOTIFY(NM_CLICK, IDC_TREEALL, OnNMClickTreeall)
	ON_BN_CLICKED(ID_BTN_BROAD_CAST, OnBnClickedBtnBroadCast)
	ON_BN_CLICKED(IDC_BTN_BROAD_CAST_EXIT, OnBnClickedBtnBroadCastExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CBroadCast message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CBroadCast::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	LoadTreeImage();
	if (g_struLocalParam.bBroadCast)
	{
		char szLan[1024] = {0};
		g_StringLanType(szLan, "停止广播", "stop broadcast");
		GetDlgItem(ID_BTN_BROAD_CAST)->SetWindowText(szLan);
	}
	else
	{
		char szLan[1024] = {0};
		g_StringLanType(szLan, "开始广播", "Start Broadcast");
		GetDlgItem(ID_BTN_BROAD_CAST)->SetWindowText(szLan);
	}

	CreateTree();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	CreateTree
  Desc:	    create device tree
  Input:	
  Output:	
  Return:	
**********************************************************/
void CBroadCast::CreateTree(void)
{
	char szLan[1024] = {0};
	g_StringLanType(szLan, "所有设备", "All Devices");
	HTREEITEM hRoot = m_treeBroadCast.InsertItem(szLan, TREE_ALL, TREE_ALL);
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	int iData =0;
	int j = 0;
	HTREEITEM hDevice = NULL;
	HTREEITEM hChanItem = NULL;
	NET_DVR_WORKSTATE_V30 struWorkState;
	for (i = 0; i < MAX_DEVICES; i++)
	{
		if (g_struDeviceInfo[i].iDeviceChanNum != -1)
		{
			strTemp.Format("%s", g_struDeviceInfo[i].chLocalNodeName);
			//sprintf(buf,"%s\r\n",g_struDeviceInfo[i].chLocalNodeName);				//server title
			if (g_struDeviceInfo[i].lLoginID >= 0)
			{
				hDevice =  m_treeBroadCast.InsertItem(strTemp, DEVICE_LOGIN, DEVICE_LOGIN, hRoot);
				m_treeBroadCast.SetItemData(hDevice, DEVICE_LOGIN*1000 + g_struDeviceInfo[i].iDeviceIndex);
				memset(&struWorkState, 0, sizeof(NET_DVR_WORKSTATE_V30));
				if (!NET_DVR_GetDVRWorkState_V30(g_struDeviceInfo[i].lLoginID, &struWorkState))
				{
					g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_GetDVRWorkState_V30");
				}
							
				for (j=0; j<g_struDeviceInfo[i].iAudioNum; j++)
				{
					if (struWorkState.byAudioChanStatus[j] == 1)
					{
						strTemp.Format("audio%d-used", j+1);
						iData = 3*1000 + struWorkState.byAudioChanStatus[j]*100 + j;
					}
					else if (struWorkState.byAudioChanStatus[j] == 0)
					{
						strTemp.Format("audio%d-not used", j+1);
						iData = 3*1000 + struWorkState.byAudioChanStatus[j]*100 + j;
					}
					else if (struWorkState.byAudioChanStatus[j] == 0xff)
					{
						strTemp.Format("audio%d", j+1);
						iData = 3*1000 + j;
					}
					 			
					hChanItem =  m_treeBroadCast.InsertItem(strTemp, 3, 3, hDevice);
					m_treeBroadCast.SetItemData(hChanItem, iData);
					// tick if the device is in the broadcast
					if (g_struDeviceInfo[i].bCheckBroadcast[j])
					{
						m_treeBroadCast.SetCheck(hChanItem, TRUE);
					}				
				}
				m_treeBroadCast.Expand(hDevice,TVE_EXPAND);
			}
			else
			{
				hDevice =  m_treeBroadCast.InsertItem(strTemp, DEVICE_LOGOUT, DEVICE_LOGOUT,hRoot);
				m_treeBroadCast.SetItemData(hDevice, DEVICE_LOGOUT*1000 + g_struDeviceInfo[i].iDeviceIndex);
			}	
		}
	}
	m_treeBroadCast.Expand(hRoot,TVE_EXPAND);
	m_treeBroadCast.Expand(m_treeBroadCast.GetRootItem(),TVE_EXPAND);
}

/*********************************************************
  Function:	OnNMClickTreeall
  Desc:		choose the device node for add or delete from the broadcast queue
  Input:	pNMHDR, Contains the click information
  Output:	pResult, result after handle notification	
  Return:	
**********************************************************/
void CBroadCast::OnNMClickTreeall(NMHDR *pNMHDR, LRESULT *pResult)
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
	HTREEITEM hSelect= m_treeBroadCast.HitTest(pt, &uFlag);

	if (NULL == hSelect) 
	{
		return;
	}
	
	m_treeBroadCast.SelectItem(hSelect);

	BOOL bCheck = m_treeBroadCast.GetCheck(hSelect);
	bCheck = !bCheck;
	int iDevIndex = 0;
	if (TREE_ALL_T == m_treeBroadCast.GetItemData(hSelect)/1000)
	{
		CheckAllDevState(hSelect, bCheck, uFlag);
	}
	else if (DEVICE_LOGIN == m_treeBroadCast.GetItemData(hSelect)/1000)
	{
		CheckAllAudioState(hSelect, bCheck, uFlag);
	}
	else if (3 == m_treeBroadCast.GetItemData(hSelect)/1000)//audio chan
	{
		HTREEITEM hDevItem = m_treeBroadCast.GetParentItem(hSelect);
		int iAudioIndex = m_treeBroadCast.GetItemData(hSelect)%1000;
		iDevIndex = m_treeBroadCast.GetItemData(hDevItem)%1000;

		if (uFlag != LVHT_TOLEFT )
		{
			m_treeBroadCast.SetCheck(hSelect, bCheck);
		}
		else
		{// click check box, set its box status on the left
			m_treeBroadCast.SetCheck(hSelect, !bCheck);
		}
		g_struDeviceInfo[iDevIndex].bCheckBroadcast[iAudioIndex] = bCheck;
		if (g_struLocalParam.bBroadCast)
		{
			AddDVR(iDevIndex, iAudioIndex, bCheck);
		}
	}

	*pResult = 0;
}

/*********************************************************
  Function:	CheckAllDevState
  Desc:		check the status of all devices
  Input:	hRoot, root node;bCheck, status of the check box; uFlag, the click item flag data
  Output:	
  Return:	
**********************************************************/
void CBroadCast::CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag)
{
	if (uFlag == LVHT_TOLEFT)
	{
		m_treeBroadCast.SetCheck(hRoot, !bCheck);
	}
	else
	{
		m_treeBroadCast.SetCheck(hRoot, bCheck);
	}	

	HTREEITEM hChild = m_treeBroadCast.GetChildItem(hRoot);
	int iDevIndex = 0;
	while (hChild)
	{
		iDevIndex = m_treeBroadCast.GetItemData(hChild)%1000;
		
		if (g_struDeviceInfo[iDevIndex].lLoginID >= 0)
		{
			m_treeBroadCast.SetCheck(hChild, bCheck);
			CheckAllAudioState(hChild, bCheck, 0);
		}

		hChild = m_treeBroadCast.GetNextSiblingItem(hChild);
	}
}

/*********************************************************
  Function:	LoadTreeImage
  Desc:		load the tree image
  Input:	
  Output:	
  Return:	
**********************************************************/
void CBroadCast::LoadTreeImage(void)
{
	CBitmap bmp[4];

	m_TreeImage.Create(16,16,ILC_COLOR32 | ILC_MASK,1,1);
	bmp[TREE_ALL].LoadBitmap(IDB_BITMAP_TREE);
	m_TreeImage.Add(&bmp[TREE_ALL],RGB(1,1,1));
	bmp[DEVICE_LOGOUT].LoadBitmap(IDB_BITMAP_LOGOUT);
	m_TreeImage.Add(&bmp[DEVICE_LOGOUT],RGB(1,1,1));
	bmp[DEVICE_LOGIN].LoadBitmap(IDB_BITMAP_LOGIN);
	m_TreeImage.Add(&bmp[DEVICE_LOGIN],RGB(1,1,1));
	bmp[3].LoadBitmap(IDB_BITMAP_AUDIO);
	m_TreeImage.Add(&bmp[3],RGB(1,1,1));
	
	m_treeBroadCast.SetImageList(&m_TreeImage, LVSIL_NORMAL);
}
 
/*********************************************************
  Function:	AddDVR
  Desc:		add or delete some DVR device in broadcast
  Input:	hDevice,handle of the device;iDeviceIndex,index of the device ;bCheck,whether added into broadcast;
  Output:	
  Return:	
**********************************************************/
BOOL CBroadCast::AddDVR(int iDeviceIndex, int iAudioIndex, BOOL bCheck)
{
	BOOL bRet = FALSE;
	if (!g_struLocalParam.bBroadCast)
	{
		return FALSE;
	}
	g_struDeviceInfo[iDeviceIndex].bCheckBroadcast[iAudioIndex] = bCheck;
	if (bCheck)
	{
		if (g_struDeviceInfo[iDeviceIndex].lAudioHandle[iAudioIndex] < 0)  
		{
			g_struDeviceInfo[iDeviceIndex].lAudioHandle[iAudioIndex] = NET_DVR_AddDVR_V30(g_struDeviceInfo[iDeviceIndex].lLoginID, iAudioIndex+1);
			if (g_struDeviceInfo[iDeviceIndex].lAudioHandle[iAudioIndex] >=0 )
			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_AddDVR_V30 audio[%d]", iAudioIndex+1);
				bRet = TRUE;
			}
			else
			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_AddDVR_V30 audio[%d]", iAudioIndex+1);
			}
		}
	}
	else
	{
		//delete devices from multicast
		if (g_struDeviceInfo[iDeviceIndex].lAudioHandle[iAudioIndex] >= 0)
		{
			bRet = NET_DVR_DelDVR_V30(g_struDeviceInfo[iDeviceIndex].lAudioHandle[iAudioIndex]);	
			if (bRet)
			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_DelDVR_V30 Audio[%d]", iAudioIndex+1);
				g_struDeviceInfo[iDeviceIndex].lAudioHandle[iAudioIndex] = -1;
			}
			else
			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_DelDVR_V30 Audio[%d]", iAudioIndex+1);
			}
		}
	}

	return bRet;
}

/*********************************************************
  Function:	OnBnClickedBtnBroadCast
  Desc:		start to broadcast
  Input:	
  Output:	
  Return:	
**********************************************************/
void CBroadCast::OnBnClickedBtnBroadCast()
{
    UpdateData(TRUE);
	int i = 0;
	int j = 0;
 	if (!g_struLocalParam.bBroadCast)
	{
// 		if (g_lVoiceHandle >= 0)
// 		{
// 			char szLan[1024] = {0};
// 			g_StringLanType(szLan, "有设备正在对讲，请先停止!", "a device is talking now, please stop at first!");
// 			AfxMessageBox(szLan);
// 			return;
// 		}

		if (!NET_DVR_ClientAudioStart_V30(/*fAudioCastDataCallBack*/NULL, NULL))
		{
			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_ClientAudioStart_V30");
		}
		else
		{
			g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_ClientAudioStart_V30");
		}

		for (i = 0; i < MAX_DEVICES; i++)
		{
			if (g_struDeviceInfo[i].lLoginID < 0)
			{
				continue;
			}
			for (j = 0; j<g_struDeviceInfo[i].iAudioNum; j++)
			{
				if (g_struDeviceInfo[i].bCheckBroadcast[j] && g_struDeviceInfo[i].lAudioHandle[j] < 0)  
				{
					g_struDeviceInfo[i].lAudioHandle[j] = NET_DVR_AddDVR_V30(g_struDeviceInfo[i].lLoginID, j+1);
					if (g_struDeviceInfo[i].lAudioHandle[j] < 0)
					{
						g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_AddDVR_V30 audio[%d]", j+1);
					}
					else
					{
						g_pMainDlg->AddLog(i, OPERATION_SUCC_T, "NET_DVR_AddDVR_V30 audio[%d]", j+1);
					}
				}
			}
		}
			char szLan[1024] = {0};
		g_StringLanType(szLan, "停止广播", "Stop Broadcast");
		GetDlgItem(ID_BTN_BROAD_CAST)->SetWindowText(szLan);
	}
	else
	{
		if (!NET_DVR_ClientAudioStop())
		{
			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_ClientAudioStop");
		}
		else
		{
			g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_ClientAudioStop");
		}
		for (i = 0; i < MAX_DEVICES; i++)
		{
			for (j = 0; j<g_struDeviceInfo[i].iAudioNum; j++)
			{
				g_struDeviceInfo[i].lAudioHandle[j] = -1;
			}
		}
		char szLan[1024] = {0};
		g_StringLanType(szLan, "开始广播", "Start Broadcast");
		GetDlgItem(ID_BTN_BROAD_CAST)->SetWindowText(szLan);
	}
	g_struLocalParam.bBroadCast = !g_struLocalParam.bBroadCast;
}

/*********************************************************
  Function:	OnBnClickedBtnBroadCastExit
  Desc:		exit audio broadcast
  Input:	
  Output:	
  Return:	
**********************************************************/
void CBroadCast::OnBnClickedBtnBroadCastExit()
{
	CDialog::OnCancel();
}


/*********************************************************
  Function:	CheckAllDevState
  Desc:		add or delete all the audio channel in the device
  Input:	hDev, device node; bCheck, add or delete
  Output:	none
  Return:	
**********************************************************/
void CBroadCast::CheckAllAudioState(HTREEITEM hDev, BOOL bCheck, int uFlag)
{
	if (uFlag == LVHT_TOLEFT)
	{
		m_treeBroadCast.SetCheck(hDev, !bCheck);
	}
	else
	{
		m_treeBroadCast.SetCheck(hDev, bCheck);
	}	
	int iAudioIndex = 0;
	int iDevIndex = m_treeBroadCast.GetItemData(hDev)%1000;
	if (iDevIndex < 0)
	{
		return;
	}
	HTREEITEM hChild = m_treeBroadCast.GetChildItem(hDev);
	while (hChild)
	{
		iAudioIndex = m_treeBroadCast.GetItemData(hChild)%1000;
		m_treeBroadCast.SetCheck(hChild, bCheck);
		g_struDeviceInfo[iDevIndex].bCheckBroadcast[iAudioIndex] = bCheck;
		if (g_struLocalParam.bBroadCast)
		{
			AddDVR(iDevIndex, iAudioIndex, bCheck);
		}
		hChild = m_treeBroadCast.GetNextSiblingItem(hChild);
	}
}
