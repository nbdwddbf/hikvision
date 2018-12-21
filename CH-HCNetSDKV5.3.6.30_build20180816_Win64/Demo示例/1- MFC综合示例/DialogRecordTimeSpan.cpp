// DialogRecordTimeSpan.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DialogRecordTimeSpan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogRecordTimeSpan dialog


CDialogRecordTimeSpan::CDialogRecordTimeSpan(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRecordTimeSpan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogRecordTimeSpan)
	m_StartDate = 0;
	m_StopDate = 0;
	m_StartTime = 0;
	m_StopTime = 0;
	m_iCurrentChan = 0;
	m_csStartTime = _T("");
	m_csStopTime = _T("");
	//}}AFX_DATA_INIT
}


void CDialogRecordTimeSpan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogRecordTimeSpan)
	DDX_Control(pDX, IDC_COMBO_RECORD_TYPE_RETURN, m_comboRecordTypeReturn);
	DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_comboRecordType);
	DDX_Text(pDX, IDC_EDIT_CURRENT_CHAN, m_iCurrentChan);
	DDX_Text(pDX, IDC_EDIT_START_TIME, m_csStartTime);
	DDX_Text(pDX, IDC_EDIT_STOP_TIME, m_csStopTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogRecordTimeSpan, CDialog)
	//{{AFX_MSG_MAP(CDialogRecordTimeSpan)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON_INRUIRY, OnButtonInruiry)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogRecordTimeSpan message handlers

BOOL CDialogRecordTimeSpan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_iCurrentChan = m_lChannel;
	m_comboRecordType.SetCurSel(0);
	m_comboRecordTypeReturn.SetCurSel(0);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogRecordTimeSpan::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CDialogRecordTimeSpan::OnButtonInruiry() 
{
	char szLan[128] = {0};

	m_csStartTime = _T("");
	m_csStopTime = _T("");

	NET_DVR_RECORD_TIME_SPAN_INQUIRY strInquiry = {0};
	strInquiry.dwSize = sizeof(strInquiry);
	strInquiry.byType = m_comboRecordType.GetCurSel();

	NET_DVR_RECORD_TIME_SPAN strResult = {0};
	if(NET_DVR_InquiryRecordTimeSpan(m_lServerID, m_lChannel, &strInquiry, &strResult))
	{
		m_comboRecordTypeReturn.SetCurSel(strResult.byType);
		m_csStartTime.Format("%04d/%02d/%02d %02d:%02d:%02d", strResult.strBeginTime.dwYear, strResult.strBeginTime.dwMonth, strResult.strBeginTime.dwDay, strResult.strBeginTime.dwHour, strResult.strBeginTime.dwMinute, strResult.strBeginTime.dwSecond);
		m_csStopTime.Format("%04d/%02d/%02d %02d:%02d:%02d", strResult.strEndTime.dwYear, strResult.strEndTime.dwMonth, strResult.strEndTime.dwDay, strResult.strEndTime.dwHour, strResult.strEndTime.dwMinute, strResult.strEndTime.dwSecond);
	
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_InquiryRecordTimeSpan");
		UpdateData(FALSE);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_InquiryRecordTimeSpan");
	}
}

void CDialogRecordTimeSpan::OnButtonExit() 
{
	CDialog::OnCancel();	
}
