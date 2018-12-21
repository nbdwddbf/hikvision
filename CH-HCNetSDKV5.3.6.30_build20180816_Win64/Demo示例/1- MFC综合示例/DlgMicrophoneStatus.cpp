// DlgMicrophoneStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMicrophoneStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMicrophoneStatus dialog


CDlgMicrophoneStatus::CDlgMicrophoneStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMicrophoneStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMicrophoneStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMicrophoneStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMicrophoneStatus)
	DDX_Control(pDX, IDC_LIST_MICROPHONE, m_listMicrophone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMicrophoneStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgMicrophoneStatus)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MICROPHONE, OnClickListMicrophone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMicrophoneStatus message handlers

void CDlgMicrophoneStatus::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	m_struTrialMicroPhoneStatus.dwSize = sizeof(NET_DVR_TRIAL_MICROPHONE_STATUS);
	
	DWORD dwRet = 0;
	if(!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_TRIAL_MICROPHONE_STATUS,0,&m_struTrialMicroPhoneStatus,sizeof(NET_DVR_TRIAL_MICROPHONE_STATUS),&dwRet))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRIAL_MICROPHONE_STATUS");
		char szLan[1024] = {0};
		sprintf(szLan,"NET_DVR_GET_TRIAL_MICROPHONE_STATUS failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRIAL_MICROPHONE_STATUS");
	}
	for (int i = 0; i < MICROPHONE_NUM; i++)
	{
		if(m_struTrialMicroPhoneStatus.byMicrophoneStatus[i])
		{
			m_listMicrophone.SetCheck(i + 1);
		}
	}
}

void CDlgMicrophoneStatus::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	m_struTrialMicroPhoneStatus.dwSize = sizeof(NET_DVR_TRIAL_MICROPHONE_STATUS);
	if(!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_TRIAL_MICROPHONE_STATUS,0,&m_struTrialMicroPhoneStatus,sizeof(NET_DVR_TRIAL_MICROPHONE_STATUS)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRIAL_MICROPHONE_STATUS");
		char szLan[1024] = {0};
		sprintf(szLan,"NET_DVR_SET_TRIAL_MICROPHONE_STATUS failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRIAL_MICROPHONE_STATUS");
	}
}

BOOL CDlgMicrophoneStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_listMicrophone.SetExtendedStyle(m_listMicrophone.GetExtendedStyle()|LVS_EX_CHECKBOXES);

	int iIndex = 0;
	m_listMicrophone.InsertItem(iIndex, "All Chans");
	m_listMicrophone.SetItemData(iIndex, 0xffff);
	iIndex ++;	
	CString csTemp;
	for (int i = 0; i < MICROPHONE_NUM; i++)
	{
		csTemp.Format("%d",i);
		m_listMicrophone.InsertItem(iIndex, csTemp);
		m_listMicrophone.SetItemData(iIndex, i);
		iIndex ++;	
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMicrophoneStatus::OnClickListMicrophone(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	DWORD dwPos = GetMessagePos();
	CPoint point( LOWORD(dwPos), HIWORD(dwPos));
	
	m_listMicrophone.ScreenToClient(&point);

	UINT uFlag = 0;
	int iSel = m_listMicrophone.HitTest(point, &uFlag);//
	if (iSel < 0)
	{
		return;
	}
	int iData = m_listMicrophone.GetItemData(iSel);

	BOOL bRet = m_listMicrophone.GetCheck(iSel);

	if (iData == 0xffff)
	{
		OnChkAllChan(!bRet);
		TRACE("uFlag = %d, bRet = %d\n", uFlag, bRet);
		if (uFlag == LVHT_ONITEMLABEL)//uFlag | LVHT_ONITEM > 0
		{
			m_listMicrophone.SetCheck(iSel, !bRet);			
		}
		return;
	}
	if (bRet)
	{
		m_struTrialMicroPhoneStatus.byMicrophoneStatus[iData] = 0;
	}
	else
	{
		m_struTrialMicroPhoneStatus.byMicrophoneStatus[iData] = 1;
	}
	*pResult = 0;
}

void CDlgMicrophoneStatus::OnChkAllChan(BOOL bAll) 
{
	int iSel = 0;
	for(int i = 0; i < MICROPHONE_NUM; i++)
	{
		iSel++;
        m_listMicrophone.SetCheck(iSel, bAll);
		if (bAll)
		{
			m_struTrialMicroPhoneStatus.byMicrophoneStatus[i] = 1;
		}
		else
		{
			m_struTrialMicroPhoneStatus.byMicrophoneStatus[i] = 0;
        }
	}
}
