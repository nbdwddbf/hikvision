// DlgAccessCameraCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAccessCameraCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAccessCameraCfg dialog

void __stdcall cbSetAccessCameraState(LONG lHandle, DWORD dwState, LPVOID pUser)
{
	CDlgAccessCameraCfg *pThis = (CDlgAccessCameraCfg*)pUser;
	HWND hWnd = pThis->GetSafeHwnd();
	if (NULL == hWnd)
	{
		return;
	}

// 	char szPrint[64] = {0};
// 	sprintf(szPrint, "demo cbSetAccessCameraState state = %d\n", dwState);
// 	OutputDebugString(szPrint);
	
	::PostMessage(hWnd, MSG_SET_ACCESS_CAMERA_STATE, (WPARAM)dwState, NULL);
}


CDlgAccessCameraCfg::CDlgAccessCameraCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAccessCameraCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAccessCameraCfg)
	m_strAccessCameraInfo = _T("");
	m_strSetAccessCameraState = _T("");
	m_szVlaue = _T("");
    m_bTrialChannelFlag = 0;
	//}}AFX_DATA_INIT
}

CDlgAccessCameraCfg::~CDlgAccessCameraCfg()
{
    if (m_iHandle >= 0)
    {
        if (!NET_DVR_CloseLongCfgHandle(m_iHandle))
        {
            g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_CloseLongCfgHandle");
        }
    }
}


void CDlgAccessCameraCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAccessCameraCfg)
    DDX_Control(pDX, IDC_CMB_CHAN_NO, m_cmbChanNo);
	DDX_Control(pDX, IDC_COMBO_INTERFACE_TYPE, m_cmbInferfaceType);
	DDX_Text(pDX, IDC_EDIT_ACCESS_CAMERA_INFO, m_strAccessCameraInfo);
	DDX_Text(pDX, IDC_STATIC_STATE, m_strSetAccessCameraState);
	DDX_Text(pDX, IDC_STATIC_ACCESS_CAMERA_INFO, m_szVlaue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAccessCameraCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAccessCameraCfg)
	ON_MESSAGE(MSG_SET_ACCESS_CAMERA_STATE, OnSetAccessCameraState)
	ON_BN_CLICKED(ID_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(ID_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAccessCameraCfg message handlers


LRESULT CDlgAccessCameraCfg::OnSetAccessCameraState(WPARAM wParam, LPARAM lParam)
{
	DWORD dwState = (DWORD)wParam;
// 	char szPrint[64] = {0};
// 	sprintf(szPrint, "demo MSG OnSetAccessCameraState state = %d\n", dwState);
// 	OutputDebugString(szPrint);
	switch (dwState)
	{
	case SET_CAMERA_TYPE_SUCCESS:
		m_strSetAccessCameraState = "设置成功";
		break;
	case SET_CAMERA_TYPE_FAIL:
        m_strSetAccessCameraState.Format("设置失败 Error %d",NET_DVR_GetLastError());
		break;
	case SET_CAMERA_TYPE_PROCESSING:
		m_strSetAccessCameraState = "正在处理...";
		break;
	default:
		m_strSetAccessCameraState = "不支持";
		break;
		
	}
	
	UpdateData(FALSE);
	return NULL;

}

void CDlgAccessCameraCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here

	// 初始化控件
// 	m_strSetAccessCameraState = "";
// 	UpdateData(FALSE);

	// 释放上一次操作资源
	if (m_iHandle >= 0)
	{
		if (!NET_DVR_CloseLongCfgHandle(m_iHandle))
		{
			g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_CloseLongCfgHandle");
		}

		m_iHandle = -1;
	}

	// 开始设置
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_ACCESS_CAMERA_INFO struAccessCameraInfo;
	memset(&struAccessCameraInfo, 0, sizeof(NET_DVR_ACCESS_CAMERA_INFO));

	struAccessCameraInfo.dwSize = sizeof(NET_DVR_ACCESS_CAMERA_INFO);
	strncpy(struAccessCameraInfo.sCameraInfo, m_strAccessCameraInfo.GetBuffer(0), 32);
	struAccessCameraInfo.byInterfaceType = m_cmbInferfaceType.GetCurSel()+1;

    if (m_bTrialChannelFlag)
    {
        m_lChannel = m_cmbChanNo.GetItemData(m_cmbChanNo.GetCurSel());
    }

	m_iHandle = NET_DVR_SetAccessCameraInfo(m_lUserID, m_lChannel, &struAccessCameraInfo, cbSetAccessCameraState, this);
	
	if(-1 == m_iHandle)
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SetAccessCameraInfo");
		g_StringLanType(szLan, "设置前端相机信息失败!", "Fail to set access camera info");
		AfxMessageBox(szLan);
	}

/*    UpdateData(FALSE);*/
}

void CDlgAccessCameraCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	NET_DVR_ACCESS_CAMERA_INFO struAccessCameraInfo;
	memset(&struAccessCameraInfo, 0, sizeof(NET_DVR_ACCESS_CAMERA_INFO));

	DWORD dwReturnedBytes = 0;

    if (m_bTrialChannelFlag)
    {
        m_lChannel = m_cmbChanNo.GetItemData(m_cmbChanNo.GetCurSel());
    }

	if(TRUE == NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ACCESS_CAMERA_INFO, m_lChannel, &struAccessCameraInfo, sizeof(NET_DVR_ACCESS_CAMERA_INFO), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ACCESS_CAMERA_INFO");
        m_strAccessCameraInfo.Format("%s", struAccessCameraInfo.sCameraInfo);
        m_cmbInferfaceType.SetCurSel(struAccessCameraInfo.byInterfaceType - 1);
		g_StringLanType(szLan, "获取前端相机信息成功!", "Success to get access camera info");
	//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ACCESS_CAMERA_INFO");
		g_StringLanType(szLan, "获取前端相机信息失败!", "Fail to get access camera info");
		AfxMessageBox(szLan);
/*		return;*/
	}

// 	strncpy(m_strAccessCameraInfo.GetBuffer(0), struAccessCameraInfo.sCameraInfo, 32);
// 	m_cmbInferfaceType.SetCurSel(struAccessCameraInfo.byInterfaceType-1);
// 
// 	UpdateData(FALSE);
}

BOOL CDlgAccessCameraCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//OnBtnGet();
	m_cmbInferfaceType.SetCurSel(0);
	m_iHandle = -1;
	
    m_cmbChanNo.ResetContent();
    DWORD dwIndex = 0;
    for (int i= 0; i< g_struDeviceInfo[m_dwDevIndex].iDeviceChanNum;i++)
    {
        m_cmbChanNo.AddString(g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].chChanName);
        m_cmbChanNo.SetItemData(dwIndex,g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].iChannelNO);
        dwIndex++;
    }
    
    
    NET_DVR_TRIAL_SYSTEM_INFO struSystemInfo = {0};
    DWORD dwRet = NET_DVR_NOERROR;
    dwIndex = 0;
    if (NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_TRIAL_SYSTEM_CFG,NULL,&struSystemInfo,sizeof(NET_DVR_TRIAL_SYSTEM_INFO),&dwRet))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRIAL_SYSTEM_CFG");
        m_cmbChanNo.ResetContent();
        
        char szLan[128] = {0};
        for (int i = 0; i< struSystemInfo.byVideoInTypeNum  && i < MAX_VIDEOIN_TYPE_NUM ;i++)
        {
            if(struSystemInfo.struVideoIn[i].wInType == 1)
            {
                for (int j = 0; j < struSystemInfo.struVideoIn[i].wInNum;j++)
                {
                    sprintf(szLan,"VGA%d",j+1);
                    m_cmbChanNo.AddString(szLan);
                    m_cmbChanNo.SetItemData(dwIndex, j+struSystemInfo.struVideoIn[i].wStartNo);
                    dwIndex++;

                }
                /*                break;*/
            }
            else if (struSystemInfo.struVideoIn[i].wInType == 2)
            {
                for (int j = 0; j < struSystemInfo.struVideoIn[i].wInNum; j++)
                {

                    sprintf(szLan, "HDMI%d", j + 1);
                    m_cmbChanNo.AddString(szLan);
                    m_cmbChanNo.SetItemData(dwIndex, j + struSystemInfo.struVideoIn[i].wStartNo);
                    dwIndex++;
                }

            }
        }

    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRIAL_SYSTEM_CFG");
    }
    
    m_cmbChanNo.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
