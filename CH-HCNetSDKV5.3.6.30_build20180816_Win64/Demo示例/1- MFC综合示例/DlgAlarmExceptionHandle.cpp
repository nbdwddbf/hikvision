// DlgAlarmExceptionHandle.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmExceptionHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmExceptionHandle dialog


CDlgAlarmExceptionHandle::CDlgAlarmExceptionHandle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmExceptionHandle::IDD, pParent)
    , m_bChkSmsAlarm(FALSE)
{
	//{{AFX_DATA_INIT(CDlgAlarmExceptionHandle)
	m_bChkMonitorAlarm = FALSE;
	m_bChkAudioAlarm = FALSE;
	m_bChkReportCenter = FALSE;
	m_bChkInvokeAlarmOut = FALSE;
	m_bChkInvokeJpegCapture = FALSE;
	m_bChkPicFtp = FALSE;
	m_bChkEmapAlarmOut = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struHandleException, 0, sizeof(NET_DVR_HANDLEEXCEPTION_V30));
}


void CDlgAlarmExceptionHandle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmExceptionHandle)
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Check(pDX, IDC_CHK_MONITOR_WARNING, m_bChkMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_AUDIO_WARNING, m_bChkAudioAlarm);
	DDX_Check(pDX, IDC_CHK_NOTIFY_SURVEILLANCE_CENTER, m_bChkReportCenter);
	DDX_Check(pDX, IDC_CHK_TRIGGER_ALARM_OUTPUT, m_bChkInvokeAlarmOut);
	DDX_Check(pDX, IDC_CHK_EMAIL_JPEG, m_bChkInvokeJpegCapture);
	DDX_Check(pDX, IDC_CHK_NOTIFY_PIC_TO_FTP, m_bChkPicFtp);
	DDX_Check(pDX, IDC_CHK_ALARMOUT_EMAP, m_bChkEmapAlarmOut);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHK_SMS_WARNING, m_bChkSmsAlarm);
}


BEGIN_MESSAGE_MAP(CDlgAlarmExceptionHandle, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmExceptionHandle)
	ON_BN_CLICKED(IDC_BTN_SET_ALARM_EXCEPTION_HANDLE, OnBtnSetAlarmExceptionHandle)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_BN_CLICKED(IDC_CHK_TRIGGER_ALARM_OUTPUT, OnChkTriggerAlarmOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmExceptionHandle message handlers

void CDlgAlarmExceptionHandle::OnBtnSetAlarmExceptionHandle() 
{
	UpdateData(TRUE);

	m_struHandleException->dwHandleType = 0;
	m_struHandleException->dwHandleType |= (m_bChkMonitorAlarm << 0);
	m_struHandleException->dwHandleType |= (m_bChkAudioAlarm << 1);
	m_struHandleException->dwHandleType |= (m_bChkReportCenter << 2);
	m_struHandleException->dwHandleType |= (m_bChkInvokeAlarmOut << 3);
	m_struHandleException->dwHandleType |= (m_bChkInvokeJpegCapture << 4);
	m_struHandleException->dwHandleType |= (m_bChkEmapAlarmOut<<6);
	m_struHandleException->dwHandleType |= (m_bChkPicFtp << 9);
	m_struHandleException->dwHandleType |= (m_bChkSmsAlarm << 13);

	for (int i=0; i<MAX_ALARMOUT_V30; i++)
	{
		m_struHandleException->byRelAlarmOut[i] = (BYTE)m_bAlarmOut[i];
	}
	CDialog::OnOK();
}

BOOL CDlgAlarmExceptionHandle::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bChkMonitorAlarm = m_struHandleException->dwHandleType &0x01;
	m_bChkAudioAlarm = (m_struHandleException->dwHandleType>>1)&0x01;
	m_bChkReportCenter = (m_struHandleException->dwHandleType>>2)&0x01;
	m_bChkInvokeAlarmOut = (m_struHandleException->dwHandleType>>3)&0x01;
	m_bChkInvokeJpegCapture = (m_struHandleException->dwHandleType>>4)&0x01;
	m_bChkEmapAlarmOut = (m_struHandleException->dwHandleType>>6)&0x01;
	m_bChkPicFtp = (m_struHandleException->dwHandleType>>9)&0x01;
	m_bChkSmsAlarm = (m_struHandleException->dwHandleType >> 13) & 0x01;

	for (int i=0; i<MAX_ALARMOUT_V30; i++)
	{
		m_bAlarmOut[i] = m_struHandleException->byRelAlarmOut[i];
	}
	
	m_treeAlarmOut.ModifyStyle( TVS_CHECKBOXES, 0 );
	m_treeAlarmOut.ModifyStyle( 0, TVS_CHECKBOXES );
	UpdateData(FALSE);
	
	g_CreateAlarmOutTree(m_treeAlarmOut, m_dwDevIndex, m_bAlarmOut);
	OnChkTriggerAlarmOutput();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmExceptionHandle::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ALARM_OUT)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmOut.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeAlarmOut.SelectItem(hSelect);
	DWORD dwIndex = m_treeAlarmOut.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeAlarmOut.GetCheck(hSelect);
	m_bAlarmOut[dwIndex] = !bCheck;
	
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmOut.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeAlarmOut.SetCheck(hSelect, bCheck);
	}
	
	*pResult = 0;
}

void CDlgAlarmExceptionHandle::OnChkTriggerAlarmOutput() 
{
	UpdateData(TRUE);
	HTREEITEM hRoot, hBrother;

	if (m_bChkInvokeAlarmOut)
	{
		GetDlgItem(IDC_TREE_ALARM_OUT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_TREE_ALARM_OUT)->EnableWindow(FALSE);
		
		hRoot = m_treeAlarmOut.GetRootItem();
		m_treeAlarmOut.SetCheck(hRoot, FALSE);
		for (int i=0; i<m_treeAlarmOut.GetCount() - 1; i++)
		{
			hBrother = m_treeAlarmOut.GetNextSiblingItem(hRoot);
			m_treeAlarmOut.SetCheck(hBrother, FALSE);
		}
	}
	
}
