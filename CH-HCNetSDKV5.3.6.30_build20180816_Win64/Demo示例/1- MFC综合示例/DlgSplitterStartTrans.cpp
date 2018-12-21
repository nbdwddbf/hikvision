// DlgSplitterStartTrans.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSplitterStartTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SERIAL_SEND_TIMER   1234
/////////////////////////////////////////////////////////////////////////////
// CDlgSplitterStartTrans dialog
CDlgSplitterStartTrans *g_pDlgAlarmHostTransparent = NULL;

void CALLBACK g_fCodeSplitterDataCallBack(LONG lSerialHandle, LONG lPort, LONG lDateType, char *pRecvDataBuffer, DWORD  dwBufSize,void *pUser)
{
    
    CString tmp1 = "";
    CString tmp2 = "";
    char ch[1024] = {0};
    CTime ct;
    if (NULL != g_pDlgAlarmHostTransparent)
    {
        int nIndex = 0;
        ct = CTime::GetCurrentTime();
        tmp1.Format("%d-%d-%d %d:%d:%d", ct.GetYear(), ct.GetMonth(), ct.GetDay(), ct.GetHour(),
            ct.GetMinute(), ct.GetSecond());
        int nItem = g_pDlgAlarmHostTransparent->m_listRecvData.GetItemCount();
        nItem = g_pDlgAlarmHostTransparent->m_listRecvData.InsertItem(nItem, tmp1, 0);
        nIndex++;            
        tmp1.Format("%d", lPort);
        g_pDlgAlarmHostTransparent->m_listRecvData.SetItemText(nItem, nIndex, tmp1);
        nIndex++;
        if (0 == lDateType)
        {
            tmp1 = "Date";
        }
        else if (1 == lDateType)
        {
            tmp1 = "Fail to send";
        }
        g_pDlgAlarmHostTransparent->m_listRecvData.SetItemText(nItem, nIndex, tmp1);
        nIndex++;
		
        memcpy(ch, pRecvDataBuffer, dwBufSize);
		
        g_pDlgAlarmHostTransparent->m_listRecvData.SetItemText(nItem, nIndex, ch);
        nIndex++;
        for (int i=0; i<(int)dwBufSize; i++)
        {
            tmp2.Format("0x%x ", (BYTE)pRecvDataBuffer[i]);
            tmp1 += tmp2;
        }
        g_pDlgAlarmHostTransparent->m_listRecvData.SetItemText(nItem, nIndex, tmp1);
        nIndex++;
		
    }

}

CDlgSplitterStartTrans::CDlgSplitterStartTrans(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSplitterStartTrans::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSplitterStartTrans)
	m_csData = _T("");
		// NOTE: the ClassWizard will add member initialization here
	m_lServerID = -1;    
    m_lSerialHandle = -1;
	//}}AFX_DATA_INIT
}


void CDlgSplitterStartTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSplitterStartTrans)
	DDX_Control(pDX, IDC_LISTRECVDATA, m_listRecvData);
	DDX_Control(pDX, IDC_COMBO_CHAN, m_comboChan);
	DDX_Control(pDX, IDC_COMBO_SERIAL_TYPE, m_comboSerialType);
	DDX_Text(pDX, IDC_EDIT_DATA, m_csData);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSplitterStartTrans, CDialog)
	//{{AFX_MSG_MAP(CDlgSplitterStartTrans)	
	ON_BN_CLICKED(IDC_CREATECHANNEL, OnCreatechannel)
	ON_BN_CLICKED(IDC_DESTROYCHANNEL, OnDestroychannel)
	ON_CBN_SELCHANGE(IDC_COMBO_SERIAL_TYPE, OnSelchangeComboSerialType)
	ON_BN_CLICKED(IDC_BTN_SEND_DATA, OnBtnSendData)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_WM_CLOSE()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BTN_SEND_DATA_AUTO, OnBtnSendDataAuto)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitterStartTrans message handlers

BOOL CDlgSplitterStartTrans::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_pDlgAlarmHostTransparent = this;
	m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
	InitWnd();
	m_comboSerialType.SetCurSel(1);
    OnSelchangeComboSerialType();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSplitterStartTrans::OnCreatechannel() 
{
	// TODO: Add your control notification handler code here
	LONG lSerialHandle = -1;
    LONG lSerialType = m_comboSerialType.GetItemData(m_comboSerialType.GetCurSel());
	if (m_lSerialHandle >= 0)
	{
		AfxMessageBox("Already start a Direct Transmission");
		return;
	}
    lSerialHandle = NET_DVR_AlarmHostSerialStart(m_lServerID, lSerialType, g_fCodeSplitterDataCallBack, &m_lServerID);
    if (lSerialHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostSerialStart serial[%d]", lSerialHandle);
        AfxMessageBox("Start Direct Transmission Failed");
        return;
    }
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostSerialStart serial[%d]", lSerialHandle);
    m_lSerialHandle = lSerialHandle;
}


void CDlgSplitterStartTrans::InitWnd()
{
    InitSerialTypeCombo();
    InitRecvDataList();
}

void CDlgSplitterStartTrans::InitSerialTypeCombo()
{
    int nIndex = 0;
    m_comboSerialType.ResetContent();
    
    m_comboSerialType.InsertString(nIndex, "Rs232");
    m_comboSerialType.SetItemData(nIndex, 1);
    nIndex++;
    
    m_comboSerialType.InsertString(nIndex, "RS485");
    m_comboSerialType.SetItemData(nIndex, 2);
    nIndex++;
}

void CDlgSplitterStartTrans::InitChannelCombo(int nChanNum)
{
    int nIndex = 0;
    m_comboChan.ResetContent();
    char szLan[128] = {0};
    for (nIndex = 0; nIndex < nChanNum; nIndex++)
    {
        sprintf(szLan, "RS485 %d", nIndex+1);
        m_comboChan.AddString(szLan);
    }
    m_comboChan.SetCurSel(0);
}

void CDlgSplitterStartTrans::InitRecvDataList()
{
    m_listRecvData.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_listRecvData.InsertColumn(0, "Time", LVCFMT_LEFT, 100, 0);
    m_listRecvData.InsertColumn(1, "Port", LVCFMT_LEFT, 50, 0);
    m_listRecvData.InsertColumn(2, "Status", LVCFMT_LEFT, 50, 0);
    m_listRecvData.InsertColumn(3, "Content", LVCFMT_LEFT, 200, 0);
    m_listRecvData.InsertColumn(4, "Hex", LVCFMT_LEFT, 450, 0);
}


void CDlgSplitterStartTrans::OnDestroychannel() 
{
	// TODO: Add your control notification handler code here
	if (m_lSerialHandle != -1)
	{
		if (NET_DVR_AlarmHostSerialStop(m_lSerialHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostSerialStop");
			m_lSerialHandle = -1;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostSerialStop");
		}
	}
    
    KillTimer(SERIAL_SEND_TIMER);
}

void CDlgSplitterStartTrans::OnSelchangeComboSerialType() 
{
	// TODO: Add your control notification handler code here
	CString csStr;
	if (m_comboSerialType.GetItemData(m_comboSerialType.GetCurSel()) == 1) //232
	{
		m_comboChan.ResetContent();
		m_comboChan.AddString("RS232 1");
		m_comboChan.SetCurSel(0);
		
// 		for (int i=0; i<MAX_SERIAL_PORT; i++)
// 		{
// 			csStr.Format("RS232 %d", i+1);
// 			m_comboChan.AddString(csStr);
// 		}
	}
    if (m_comboSerialType.GetItemData(m_comboSerialType.GetCurSel()) == 2) // 485
    {
        InitChannelCombo(8);
    }
}

void CDlgSplitterStartTrans::OnBtnSendData() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	
    if (m_lSerialHandle < 0)
    {
        g_StringLanType(szLan, "请先建立透明通道", "Please create serial transparent");
        AfxMessageBox(szLan);
		
        return;
    }
    
    UpdateData(TRUE);
    if (AlarmHostSerialSend())
    {
        m_csData.Empty();
    }
    else
    {
        AfxMessageBox("Fail to send data");
    }
}

BOOL CDlgSplitterStartTrans::AlarmHostSerialSend()
{
    if (NET_DVR_AlarmHostSerialSend(m_lSerialHandle, m_comboChan.GetCurSel() + 1, m_csData.GetBuffer(0), m_csData.GetLength()))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostSerialSend");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostSerialSend");
        return FALSE;
    }
}

void CDlgSplitterStartTrans::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	OnDestroychannel();
	OnCancel();
}


void CDlgSplitterStartTrans::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	OnDestroychannel();
	CDialog::OnClose();
}

void CDlgSplitterStartTrans::OnCancelMode() 
{
	OnDestroychannel();
	CDialog::OnCancelMode();	
	// TODO: Add your message handler code here
	
}

void CDlgSplitterStartTrans::OnBtnSendDataAuto() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lSerialHandle < 0)
    {
        g_StringLanType(szLan, "请先建立透明通道", "Please create serial transparent");
        AfxMessageBox(szLan);
		
        return;
    }
	m_dwChan = 1;
	SetTimer(SERIAL_SEND_TIMER, 500, NULL);
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgSplitterStartTrans::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgSplitterStartTrans::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	
    if (nIDEvent == SERIAL_SEND_TIMER)
    {
		UpdateData(TRUE);
		if (m_comboSerialType.GetCurSel() == 0)
		{
			if (NET_DVR_AlarmHostSerialSend(m_lSerialHandle, 1, m_csData.GetBuffer(0), m_csData.GetLength()))
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostSerialSend");
			}
			else
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostSerialSend");
			}
		}
		else if (m_comboSerialType.GetCurSel() == 1)
		{			
			if (NET_DVR_AlarmHostSerialSend(m_lSerialHandle, m_dwChan, m_csData.GetBuffer(0), m_csData.GetLength()))
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostSerialSend");
			}
			else
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostSerialSend");
			}

			if (++m_dwChan > 8)
			{
				m_dwChan = 1;
			}
		}        
    }
	CDialog::OnTimer(nIDEvent);
}
