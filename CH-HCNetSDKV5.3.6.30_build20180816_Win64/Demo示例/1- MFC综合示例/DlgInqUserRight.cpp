// DlgInqUserRight.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInqUserRight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInqUserRight dialog


CDlgInqUserRight::CDlgInqUserRight(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInqUserRight::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInqUserRight)
	m_bLocalDelRecRight = FALSE;
	m_bNetPreviewAudio = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struInqUserRightCfg, 0, sizeof(NET_DVR_INQUEST_USER_RIGHT_CFG));
	m_iCurRightType = -1;
	m_iUserIndex = -1;
	m_bSuperUserLogin = FALSE;
}


void CDlgInqUserRight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInqUserRight)
	DDX_Control(pDX, IDC_LIST_VIDEO_CHAN, m_listCtrl_Chan);
	DDX_Control(pDX, IDC_COMBO_USER_INDEX, m_cmbUserIndex);
	DDX_Control(pDX, IDC_COMBO_RIGHT_TYPE, m_cmbRightType);
	DDX_Check(pDX, IDC_CHK_LOCAL_DEL_REC, m_bLocalDelRecRight);
	DDX_Check(pDX, IDC_CHK_REMOTE_AUDIO, m_bNetPreviewAudio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInqUserRight, CDialog)
	//{{AFX_MSG_MAP(CDlgInqUserRight)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMBO_USER_INDEX, OnSelchangeComboUserIndex)
	ON_CBN_SELCHANGE(IDC_COMBO_RIGHT_TYPE, OnSelchangeComboRightType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInqUserRight message handlers

void CDlgInqUserRight::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	GetChanInfoFromWnd();

	char szLan[128] = {0};
	
	m_struInqUserRightCfg.dwSize = sizeof(NET_DVR_INQUEST_USER_RIGHT_CFG);
	LONG lInqUserIndex = m_cmbUserIndex.GetCurSel() + 1;

	memset(m_struInqUserRightCfg.byLocalRight, 0, MAX_RIGHT);
	memset(m_struInqUserRightCfg.byRemoteRight, 0, MAX_RIGHT);
	m_struInqUserRightCfg.byLocalRight[0] = m_bLocalDelRecRight;
	m_struInqUserRightCfg.byRemoteRight[0] = m_bNetPreviewAudio;
	
	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_INQUEST_USER_RIGHT, lInqUserIndex, &m_struInqUserRightCfg, sizeof(NET_DVR_INQUEST_USER_RIGHT_CFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_INQUEST_USER_RIGHT");
		sprintf(szLan,"NET_DVR_SET_INQUEST_USER_RIGHT failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_INQUEST_USER_RIGHT");
    }
}

BOOL CDlgInqUserRight::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	InitUserIndexCombo();
	InitRightList();

	NET_DVR_USER_V40* pStruUserCfg_V40;
	pStruUserCfg_V40 = new NET_DVR_USER_V40;
	if (pStruUserCfg_V40 == NULL)
	{
		return FALSE;
	}
	
	memset(pStruUserCfg_V40, 0, sizeof(NET_DVR_USER_V40));

	DWORD dwReturned = -1;
	pStruUserCfg_V40->dwSize = sizeof(NET_DVR_USER_V40);
	
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_USERCFG_V40, 0, pStruUserCfg_V40, sizeof(NET_DVR_USER_V40), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_USERCFG_V40");
		char szLan[128] = {0};
		g_StringLanType(szLan, "获取用户参数失败！", "Get User Parameter failed");
		
		AfxMessageBox(szLan);
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_USERCFG_V40");
	}

	if (strcmp(g_struDeviceInfo[m_iDeviceIndex].chLoginUserName, "admin")==0)
	{
		m_bSuperUserLogin = TRUE;
	}
	else
	{
		m_bSuperUserLogin = FALSE;
	}

	CString csUserName;
	char cTemp[100] = {0};
	int i = 0;
// 	if (m_bSuperUserLogin)
// 	{
// 		m_iUserIndex = 0;			
// 		m_comboUserSel.SetCurSel(m_iUserIndex);
// 	}
// 	else
	{
		for (i=0; i<MAX_USERNUM_V30; i++)
		{
			ZeroMemory(cTemp, 100);
			memcpy(cTemp, pStruUserCfg_V40->struUser[i].sUserName, MAX_NAMELEN);
			csUserName.Format("%s", cTemp);
			if (strcmp(csUserName, g_struDeviceInfo[m_iDeviceIndex].chLoginUserName) == 0)
			{
				break;
			}
		}
        if ( i == MAX_USERNUM_V30 )
        {
            return FALSE ; 
        }
		m_iUserIndex = i;
		//m_comboUserSel.SetCurSel(m_iUserIndex);
	}

	m_cmbUserIndex.SetCurSel(m_iUserIndex);
	m_cmbRightType.SetCurSel(0);
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInqUserRight::InitUserIndexCombo()
{
    char szLan[128] = {0};
    m_cmbUserIndex.ResetContent();
	int i = -1;

	sprintf(szLan, "admin");
    m_cmbUserIndex.AddString(szLan);

    for (i = 1; i < 32; i ++)
    {
        sprintf(szLan, "User %d", i);
        m_cmbUserIndex.AddString(szLan);
    }
}


void CDlgInqUserRight::InitRightList()
{ 
	LONG lChanNum = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	//g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo->chChanName

	char szLan[128] = {0};

	m_listCtrl_Chan.SetExtendedStyle(LVS_EX_CHECKBOXES);
	int i = -1;
	for (i=0; i<lChanNum; i++)
	{
		//g_StringLanType(szLan, "通道", "Chan");
		sprintf(szLan, "%s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
		//sprintf(szLan, "%s%d", szLan, i+1);
		m_listCtrl_Chan.InsertItem(i, szLan);
	}
	UpdateData(FALSE);
}

void CDlgInqUserRight::OnBtnGet()
{
    char szLan[128] = {0};
	DWORD dwBytesReturned = -1;
	
	m_struInqUserRightCfg.dwSize = sizeof(NET_DVR_INQUEST_USER_RIGHT_CFG);
	LONG lInqUserIndex = m_cmbUserIndex.GetCurSel() + 1;
	
	if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_INQUEST_USER_RIGHT, lInqUserIndex, &m_struInqUserRightCfg, sizeof(NET_DVR_INQUEST_USER_RIGHT_CFG), &dwBytesReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_INQUEST_USER_RIGHT");
		sprintf(szLan,"NET_DVR_GET_INQUEST_USER_RIGHT failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_INQUEST_USER_RIGHT");
    }

	m_bLocalDelRecRight = m_struInqUserRightCfg.byLocalRight[0];
	m_bNetPreviewAudio = m_struInqUserRightCfg.byRemoteRight[0];

	m_cmbRightType.SetCurSel(0);
	SetChanInfoToDlg();

	UpdateData(FALSE);
}

void CDlgInqUserRight::OnSelchangeComboUserIndex() 
{
	// TODO: Add your control notification handler code here
	OnBtnGet();
}


void CDlgInqUserRight::GetChanInfoFromWnd() 
{
	UpdateData(TRUE);
	int i = -1;

	if (m_iCurRightType == 0)
	{
		memset(m_struInqUserRightCfg.byNetAudioRight, 0, sizeof(m_struInqUserRightCfg.byNetAudioRight));
		for (i=0; i<m_listCtrl_Chan.GetItemCount(); i++)
		{
			m_struInqUserRightCfg.byNetAudioRight[i] = m_listCtrl_Chan.GetCheck(i);
		}
	}

}

void CDlgInqUserRight::SetChanInfoToDlg()
{
	int iRightType = m_cmbRightType.GetCurSel();
	int i = -1;
	if (iRightType == 0)	//远程音频预览
	{
		for ( i = 0 ; i < m_listCtrl_Chan.GetItemCount(); i++ )
		{
			m_listCtrl_Chan.SetCheck( i, (m_struInqUserRightCfg.byNetAudioRight[i]) );
		}
	}

	m_iCurRightType = iRightType;
	
	UpdateData(FALSE);
}

void CDlgInqUserRight::OnSelchangeComboRightType() 
{
	// TODO: Add your control notification handler code here
	GetChanInfoFromWnd();
	SetChanInfoToDlg();
}
