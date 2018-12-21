// DlgPlayDvrRecord.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPlayDvrRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayDvrRecord dialog


CDlgPlayDvrRecord::CDlgPlayDvrRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayDvrRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPlayDvrRecord)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPlayDvrRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlayDvrRecord)
	DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_comboRecordType);
	DDX_Control(pDX, IDC_COMBO_RECORD_CHANNEL, m_cmRecordChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPlayDvrRecord, CDialog)
	//{{AFX_MSG_MAP(CDlgPlayDvrRecord)
	ON_BN_CLICKED(IDC_BTN_START_RECORD, OnBtnStartRecord)
	ON_BN_CLICKED(IDC_BTN_STOP_RECORD, OnBtnStopRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayDvrRecord message handlers

CDlgPlayDvrRecord::~CDlgPlayDvrRecord()
{

}

/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgPlayDvrRecord::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);	
	return TRUE;
}

/*********************************************************
  Function:	SetParentWnd
  Desc:		transmit the handle of parent dialog box
  Input:	hhWnd, pointer to handle array
  Output:	
  Return:	
**********************************************************/
void CDlgPlayDvrRecord::SetParentWnd(HWND *hhWnd, int iParentNum)
{
	VERIFY(iParentNum==2);
	m_hPareDlgWnd=hhWnd[0];
	m_hPareTabWnd=hhWnd[1];
}

/*********************************************************
  Function:	CheckInitParam
  Desc:		check current device parameters, and initialize dialog box parameters
  Input:	
  Output:	
  Return:	TRUE,check and initialize correctly;FALSE,check failed,not initialized;
**********************************************************/
BOOL CDlgPlayDvrRecord::CheckInitParam()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		UpdateData(FALSE);
		return FALSE;
	}
	
	//if (iDeviceIndex != m_iDeviceIndex)
	//{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
		m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;		
		m_lStartChan = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
	//}
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	
	if (iChanIndex != m_iChanIndex)//-1 all channel
	{
		m_iChanIndex = iChanIndex;
	}

	InitComboBox();
	UpdateData(FALSE); 
	return TRUE;
}

void CDlgPlayDvrRecord::OnBtnStartRecord() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    BOOL ret;
	char szLan[128] = {0};
	//m_lChannel = g_struDeviceInfo[m_iDeviceIndex].struChanInfo[m_iChanIndex].iChannelNO;//(LONG)m_iChanIndex + m_lStartChan; 
	m_lChannel = m_cmRecordChannel.GetItemData(m_cmRecordChannel.GetCurSel());
	m_lRecordType = m_comboRecordType.GetCurSel();
	ret = NET_DVR_StartDVRRecord(m_lLoginID, m_lChannel, m_lRecordType);

	if (!ret)
	{
		g_StringLanType(szLan,"录像失败","Fail to record");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Record err");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex,OPERATION_SUCC_T,"NET_DVR_StartDVRRecord");
		return;
	}

}

void CDlgPlayDvrRecord::OnBtnStopRecord() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BOOL ret;
	char szLan[128] = {0};
	//m_lChannel = g_struDeviceInfo[m_iDeviceIndex].struChanInfo[m_iChanIndex].iChannelNO;
	m_lChannel = m_cmRecordChannel.GetItemData(m_cmRecordChannel.GetCurSel());
	ret = NET_DVR_StopDVRRecord(m_lLoginID, m_lChannel);

	if (!ret)
	{
		g_StringLanType(szLan,"操作失败","Fail to stop");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Operate err");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex,OPERATION_SUCC_T,"NET_DVR_StopDVRRecord");
		return;
	}
}

void CDlgPlayDvrRecord::InitComboBox()
{
	m_cmRecordChannel.ResetContent();
	char szLan[128] = {0};
	CString csStr;
	int iIndex = 0;
	int i = 0; 
	for(i=0; i<g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
	{
        m_cmRecordChannel.AddString(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
		m_cmRecordChannel.SetItemData(iIndex++, g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO);
	}
	
	for(i=g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo; i<g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo + g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum; i++)
	{
		g_StringLanType(szLan, "MirrorChannel", "MirrorChannel");
		csStr.Format("%s %d", szLan, 1 + i - g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo);
		m_cmRecordChannel.AddString(csStr);
		m_cmRecordChannel.SetItemData(iIndex++, i);
	}
	g_StringLanType(szLan, "所有模拟通道", "ALL the analog cameras");
	m_cmRecordChannel.AddString(szLan);
	m_cmRecordChannel.SetItemData(iIndex++, 0xff);
	
	g_StringLanType(szLan, "所有数字通道", "ALL the IP cameras");
	m_cmRecordChannel.AddString(szLan);
	m_cmRecordChannel.SetItemData(iIndex++, 0xff00);
	
	g_StringLanType(szLan, "所有通道", "ALL the cameras");
	m_cmRecordChannel.AddString(szLan);
	m_cmRecordChannel.SetItemData(iIndex++, 0xffff);
}
