// DlgLocalInputInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLocalInputInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLocalInputInfo dialog


CDlgLocalInputInfo::CDlgLocalInputInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocalInputInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLocalInputInfo)
	m_sChannel = _T("");
	//}}AFX_DATA_INIT
	memset(&m_struLocalInputInfo,0,sizeof(m_struLocalInputInfo));
	memset(&m_struTrialSystemInfo,0,sizeof(m_struTrialSystemInfo));
}


void CDlgLocalInputInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLocalInputInfo)
	DDX_Control(pDX, IDC_COMBO_INPUT_CHAN, m_comboInputChan);
	DDX_Text(pDX, IDC_CHANNEL, m_sChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLocalInputInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgLocalInputInfo)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLocalInputInfo message handlers
void CDlgLocalInputInfo::setParam(NET_DVR_TRIAL_SYSTEM_INFO struTrialSystemInfo)
{
	m_struTrialSystemInfo = struTrialSystemInfo;
}

void CDlgLocalInputInfo::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	int chanIndex = m_comboInputChan.GetCurSel();
	int channel = m_comboInputChan.GetItemData(chanIndex);
	char chanName[32] = {0};
	sprintf(chanName,m_sChannel);
	memcpy(m_struLocalInputInfo.byChannelName,chanName,NAME_LEN);
	m_struLocalInputInfo.dwSize = sizeof(NET_DVR_LOCAL_INPUT_INFO);
	if(!NET_DVR_SetDVRConfig(lUserID,NET_DVR_SET_LOCAL_INPUT_CFG,channel,&m_struLocalInputInfo,sizeof(NET_DVR_LOCAL_INPUT_INFO)))
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LOCAL_INPUT_CFG");
		char szLan[1024] = {0};
		sprintf(szLan,"NET_DVR_SET_LOCAL_INPUT_CFG failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
    else
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LOCAL_INPUT_CFG");
    }
}

void CDlgLocalInputInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	int chanIndex = m_comboInputChan.GetCurSel();
	int channel = m_comboInputChan.GetItemData(chanIndex);
	DWORD dwRet = 0;
	m_struLocalInputInfo.dwSize = sizeof(NET_DVR_LOCAL_INPUT_INFO);
	if (!NET_DVR_GetDVRConfig(lUserID,NET_DVR_GET_LOCAL_INPUT_CFG,channel,&m_struLocalInputInfo,sizeof(NET_DVR_LOCAL_INPUT_INFO),&dwRet))
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LOCAL_INPUT_CFG");
		char szLan[1024] = {0};
		sprintf(szLan,"NET_DVR_GET_LOCAL_INPUT_CFG failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
    else
    {
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LOCAL_INPUT_CFG");
    }

	m_sChannel.Format("%s",m_struLocalInputInfo.byChannelName);
	UpdateData(FALSE);
}

BOOL CDlgLocalInputInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int j = 0;
	int index = 0;
	char sTemp[32] = {0};
	for (int i = 0; i < m_struTrialSystemInfo.byVideoInTypeNum; i++)
    {
        switch (m_struTrialSystemInfo.struVideoIn[i].wInType)
        {
        case 0:
            for(j = 0; j < m_struTrialSystemInfo.struVideoIn[i].wInNum; j++)
			{
				sprintf(sTemp,"SDI%d",j+1);
				m_comboInputChan.AddString(sTemp);
				m_comboInputChan.SetItemData(index,m_struTrialSystemInfo.struVideoIn[i].wStartNo + j);
				index++;
			}
            break;
        case  1:
			for(j = 0; j < m_struTrialSystemInfo.struVideoIn[i].wInNum; j++)
			{
				sprintf(sTemp,"VGA%d",j+1);
				m_comboInputChan.AddString(sTemp);
				m_comboInputChan.SetItemData(index,m_struTrialSystemInfo.struVideoIn[i].wStartNo + j);
				index++;
			}
            break;
        case 2:
            for(j = 0; j < m_struTrialSystemInfo.struVideoIn[i].wInNum; j++)
			{
				sprintf(sTemp,"HDMI%d",j+1);
				m_comboInputChan.AddString(sTemp);
				m_comboInputChan.SetItemData(index,m_struTrialSystemInfo.struVideoIn[i].wStartNo + j);
				index++;
			}
            break;
        case 3:
            for(j = 0; j < m_struTrialSystemInfo.struVideoIn[i].wInNum; j++)
			{
				sprintf(sTemp,"IP%d",j+1);
				m_comboInputChan.AddString(sTemp);
				m_comboInputChan.SetItemData(index,m_struTrialSystemInfo.struVideoIn[i].wStartNo + j);
				index++;
			}
            break;
        case 4:
            for(j = 0; j < m_struTrialSystemInfo.struVideoIn[i].wInNum; j++)
			{
				sprintf(sTemp,"PIP%d",j+1);
				m_comboInputChan.AddString(sTemp);
				m_comboInputChan.SetItemData(index,m_struTrialSystemInfo.struVideoIn[i].wStartNo + j);
				index++;
			}
            break;
        case 5:
            for(j = 0; j < m_struTrialSystemInfo.struVideoIn[i].wInNum; j++)
			{
				sprintf(sTemp,"POE%d",j+1);
				m_comboInputChan.AddString(sTemp);
				m_comboInputChan.SetItemData(index,m_struTrialSystemInfo.struVideoIn[i].wStartNo + j);
				index++;
			}
            break;
        case 6:
           for(j = 0; j < m_struTrialSystemInfo.struVideoIn[i].wInNum; j++)
		   {
			   sprintf(sTemp,"YPBPR%d",j+1);
			   m_comboInputChan.AddString(sTemp);
			   m_comboInputChan.SetItemData(index,m_struTrialSystemInfo.struVideoIn[i].wStartNo + j);
			   index++;
			}
            break;
        default:
            break;
        }
    }
	m_comboInputChan.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
