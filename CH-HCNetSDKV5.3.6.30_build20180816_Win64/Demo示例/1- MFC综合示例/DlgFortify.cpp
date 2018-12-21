/**********************************************************
FileName:    DlgFortify.cpp
Description: set and remove guard      
Date:        2008/11/19
Note: 		 <global>struct, define refer to GeneralDef.h, global variables and functions refer to ClientDemo.cpp    
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/11/19>       <created>
***********************************************************/

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgFortify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFortify dialog

/*********************************************************
  Function:	CDlgFortify
  Desc:		Constructor
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
CDlgFortify::CDlgFortify(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFortify::IDD, pParent)
    , m_bConfirmMechanism(FALSE)
	, m_bChkFaceSnap(FALSE)
    , m_bChkJsonURL(FALSE)
    , m_bFaceMatch(FALSE)
    , m_bCopilotFace(FALSE)
    , m_bFaceMatchBroken(FALSE)
    , m_bFaceSnapBroken(FALSE)
    , m_strSubEventXml(_T(""))
    , m_bJSONBroken(FALSE)
    , m_bOldPlateResult(FALSE)
    , m_bChkHeatMapDuration(FALSE)
    , m_bChkHeatMapIntersection(FALSE)
  {
	m_bFortify = FALSE;
	m_iTaskNo = 0;
	//{{AFX_DATA_INIT(CDlgFortify)
	m_bChkBKN = FALSE;
	m_bChkPDC = FALSE;
	m_bChkHeatMap = FALSE;
	//}}AFX_DATA_INIT
}

/*********************************************************
  Function:	~CDlgFortify
  Desc:		Destructor
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgFortify::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgFortify)
    DDX_Control(pDX, IDC_COMBO_FACE_ALARM_TYPE, m_comFaceAlarmType);
    DDX_Control(pDX, IDC_COMBO_DEPLOY_TYPE, m_comDeployType);
    DDX_Control(pDX, IDC_TREEALL, m_treeAll);
    DDX_Text(pDX, IDC_EDIT_TASK_NO, m_iTaskNo);
    DDX_Check(pDX, IDC_CHK_BKN, m_bChkBKN);
    DDX_Check(pDX, IDC_CHK_PDC, m_bChkPDC);
    DDX_Check(pDX, IDC_CHK_HEATMAP, m_bChkHeatMap);
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHK_CONFIRM, m_bConfirmMechanism);

    DDX_Check(pDX, IDC_CHK_FACESNAP, m_bChkFaceSnap);
    DDX_Check(pDX, IDC_CHK_JSONURL, m_bChkJsonURL);
    DDX_Check(pDX, IDC_CHK_FACEMATCH, m_bFaceMatch);
    DDX_Control(pDX, IDC_COMBO_ALARM_LEVEL, m_comAlarmLevel);
    DDX_Check(pDX, IDC_CHK_COPILOT_FACE, m_bCopilotFace);
    DDX_Check(pDX, IDC_CHK_FACEMATCHBROKEN, m_bFaceMatchBroken);
    DDX_Check(pDX, IDC_CHK_FACESNAPBROKEN, m_bFaceSnapBroken);
    DDX_Text(pDX, IDC_EDIT_SUB_EVENT_XML, m_strSubEventXml);
    DDX_Check(pDX, IDC_CHK_JSONBKN, m_bJSONBroken);
    DDX_Check(pDX, IDC_CHECK_OLD_PLATE_RESULT, m_bOldPlateResult);
    DDX_Check(pDX, IDC_CHK_HEAT_MAP_DURATION, m_bChkHeatMapDuration);
    DDX_Check(pDX, IDC_CHK_HEAT_MAP_INTERSECTION, m_bChkHeatMapIntersection);
  }

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgFortify, CDialog)
	//{{AFX_MSG_MAP(CDlgFortify)
	ON_BN_CLICKED(ID_BTN_FORTIFY, OnBtnFortify)
	ON_NOTIFY(NM_CLICK, IDC_TREEALL, OnClickTreeall)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_CHK_BKN, OnChkBkn)
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
BOOL CDlgFortify::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	LoadTreeImage();
	CreateTree();
	m_comFaceAlarmType.SetCurSel(1);
    m_comDeployType.SetCurSel(0);
    m_comAlarmLevel.SetCurSel(0);
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
void CDlgFortify::CreateTree(void)
{
	char szLan[1024] = {0};
	g_StringLanType(szLan, "所有设备", "All Devices");
	HTREEITEM hRoot = m_treeAll.InsertItem(szLan, TREE_ALL, TREE_ALL);
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hDevice = NULL;
	for (i = 0; i < MAX_DEVICES; i++)
	{
		if (g_struDeviceInfo[i].iDeviceChanNum != -1)
		{
			strTemp.Format("%s", g_struDeviceInfo[i].chLocalNodeName);
			//sprintf(buf,"%s\r\n",g_struDeviceInfo[i].chLocalNodeName);				//server title
			if (g_struDeviceInfo[i].lLoginID >= 0)
			{
				hDevice =  m_treeAll.InsertItem(strTemp, DEVICE_LOGIN, DEVICE_LOGIN,hRoot);
				m_treeAll.SetItemData(hDevice, DEVICE_LOGIN*1000 + g_struDeviceInfo[i].iDeviceIndex);
// 				if (g_struDeviceInfo[i].lFortifyHandle>=0)
// 				{
// 					m_treeAll.SetCheck(hDevice, TRUE);
// 				}
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
  Desc:		choose the device node and update the status
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgFortify::OnClickTreeall(NMHDR* pNMHDR, LRESULT* pResult) 
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
  Desc:		check the status of the device
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgFortify::CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag)
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
		int iLoginType = m_treeAll.GetItemData(hChild)/1000;

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
void CDlgFortify::LoadTreeImage(void)
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
  Function:	OnBtnFortify
  Desc:		fortify the choosed devices
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgFortify::OnBtnFortify() 
{
	UpdateData(TRUE);
	char szLan[1024] = {0};
	
	HTREEITEM hRoot;
	HTREEITEM hChild;
	
	int iDevIndex = 0;
	CString sTemp;
	BOOL bChk = FALSE;
	
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
			if(g_struDeviceInfo[iDevIndex].lFortifyHandle == -1)
			{   
                NET_DVR_SETUPALARM_PARAM_V50 struSetupAlarmParam = { 0 };
				struSetupAlarmParam.dwSize = sizeof(struSetupAlarmParam);
				struSetupAlarmParam.byRetVQDAlarmType = TRUE; //Prefer VQD Alarm type of NET_DVR_VQD_ALARM
				struSetupAlarmParam.byRetAlarmTypeV40 = TRUE;
				struSetupAlarmParam.byFaceAlarmDetection = m_comFaceAlarmType.GetCurSel();
				struSetupAlarmParam.wTaskNo = m_iTaskNo;
                struSetupAlarmParam.byBrokenNetHttp = 0;
                struSetupAlarmParam.byBrokenNetHttp |= (m_bChkBKN << 0);
                struSetupAlarmParam.byBrokenNetHttp |= (m_bChkPDC << 1);
                struSetupAlarmParam.byBrokenNetHttp |= (m_bChkHeatMap << 2);
                struSetupAlarmParam.byBrokenNetHttp |= (m_bFaceSnapBroken << 3);
                struSetupAlarmParam.byBrokenNetHttp |= (m_bFaceMatchBroken << 4);
                struSetupAlarmParam.byBrokenNetHttp |= (m_bJSONBroken << 5);
                struSetupAlarmParam.byBrokenNetHttp |= (m_bChkHeatMapDuration << 6);
                struSetupAlarmParam.byBrokenNetHttp |= (m_bChkHeatMapIntersection << 7);
                
                struSetupAlarmParam.byRetDevInfoVersion = TRUE;
				struSetupAlarmParam.byAlarmInfoType = m_bOldPlateResult ? 0 : 1;
                struSetupAlarmParam.bySupport |= (m_bConfirmMechanism << 1);
                struSetupAlarmParam.byDeployType = m_comDeployType.GetCurSel();
				struSetupAlarmParam.bySupport |= (1 << 2);
				struSetupAlarmParam.byAlarmTypeURL |= (m_bChkFaceSnap << 0);
                struSetupAlarmParam.byAlarmTypeURL |= (m_bChkJsonURL << 1);
                struSetupAlarmParam.byAlarmTypeURL |= (m_bFaceMatch << 2);
                struSetupAlarmParam.byCustomCtrl = m_bCopilotFace;
                struSetupAlarmParam.byLevel = m_comAlarmLevel.GetCurSel();

                char *pSub = m_strSubEventXml.GetBuffer(m_strSubEventXml.GetLength());
                int pSubSize = m_strSubEventXml.GetLength();
                if (pSubSize == 0)
                {
                    pSub = NULL;
                }

                g_struDeviceInfo[iDevIndex].lFortifyHandle = NET_DVR_SetupAlarmChan_V50(g_struDeviceInfo[iDevIndex].lLoginID, &struSetupAlarmParam, pSub, pSubSize);
				if(g_struDeviceInfo[iDevIndex].lFortifyHandle == -1)
				{	
					m_treeAll.SetItemImage(hChild,0,0);
                    g_pMainDlg->AddLog(iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetupAlarmChan_V50 %s", NET_DVR_GetErrorMsg());
					g_StringLanType(szLan, "报警设防失败", "Setup alarm chan failed");
					AfxMessageBox(szLan);
				}
				else
				{
					g_pMainDlg->AddLog(iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetupAlarmChan_V50");
				}
			}
			else if(g_struDeviceInfo[iDevIndex].lFortifyHandle >= 0)
			{
				if(NET_DVR_CloseAlarmChan_V30(g_struDeviceInfo[iDevIndex].lFortifyHandle))
				{
					g_struDeviceInfo[iDevIndex].lFortifyHandle = -1;
					g_pMainDlg->AddLog(iDevIndex, OPERATION_SUCC_T, "NET_DVR_CloseAlarmChan_V30");
				}
				else
				{
					m_treeAll.SetItemImage(hChild,1,1);
                    g_pMainDlg->AddLog(iDevIndex, OPERATION_FAIL_T, "NET_DVR_CloseAlarmChan_V30 %s", NET_DVR_GetErrorMsg());
					g_StringLanType(szLan, "报警撤防失败", "Close alarm chan failed");
					AfxMessageBox(szLan);
				}
			}
		}
		
		hChild =m_treeAll.GetNextSiblingItem(hChild);
	}
	m_bFortify = TRUE;
	g_StringLanType(szLan, "布防撤防完成", "Setup/close alarm chan succeed");
	AfxMessageBox(szLan);
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		exit the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgFortify::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgFortify::OnChkBkn() 
{
	// TODO: Add your control notification handler code here
	
}
