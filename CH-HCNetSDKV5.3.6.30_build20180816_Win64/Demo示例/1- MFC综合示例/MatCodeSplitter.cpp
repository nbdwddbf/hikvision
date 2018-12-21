// MatCodeSplitter.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatCodeSplitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatCodeSplitter dialog


CMatCodeSplitter::CMatCodeSplitter(CWnd* pParent /*=NULL*/)
	: CDialog(CMatCodeSplitter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatCodeSplitter)
	m_iDecoderAddress = 0;
	m_strCodeSplitterIp = _T("");
	m_strCodeSplitterName = _T("");
	m_strCodeSplitterPsw = _T("");
	m_dwCodeSplitterPort = 0;
	m_iDecoderAddr = 0;
	//}}AFX_DATA_INIT
}


void CMatCodeSplitter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatCodeSplitter)
	DDX_Control(pDX, IDC_COMBOFLOWCONTROL, m_FlowControlCtrl);
	DDX_Control(pDX, IDC_COMBOSTOPBIT, m_StopBitCtrl);
	DDX_Control(pDX, IDC_COMBOPARITY, m_ParityCtrl);
	DDX_Control(pDX, IDC_COMBODATABIT, m_DataBitCtrl);
	DDX_Control(pDX, IDC_COMBOBAUDRATE, m_BaudRateCtrl);
	DDX_Control(pDX, IDC_COMBODECODERTYPE, m_DecoderTypeCtrl);
	DDX_Control(pDX, IDC_COMBODECODERCHAN, m_DecoderChanCtrl);
	DDX_Control(pDX, IDC_COMBOCODENUM, m_CodeNumCtrl);
	DDX_Text(pDX, IDC_EDITDECODERADDRESS, m_iDecoderAddress);
	DDX_Text(pDX, IDC_EDITCODESPLITTERIP, m_strCodeSplitterIp);
	DDX_Text(pDX, IDC_EDITCODESPLITTERNAME, m_strCodeSplitterName);
	DDX_Text(pDX, IDC_EDITCODESPLITTERPASS, m_strCodeSplitterPsw);
	DDX_Text(pDX, IDC_EDITCODESPLITTERPORT, m_dwCodeSplitterPort);
	DDX_Text(pDX, IDC_DECODERADDRESS, m_iDecoderAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatCodeSplitter, CDialog)
	//{{AFX_MSG_MAP(CMatCodeSplitter)
	ON_BN_CLICKED(IDEXIT, OnExit)
	ON_BN_CLICKED(IDC_GETCODESPLITTER, OnGetcodesplitter)
	ON_BN_CLICKED(IDC_SETCODESPLITTER, OnSetcodesplitter)
    //ON_CBN_SELCHANGE(IDC_COMBOBAUDRATE, OnSelchangeCombobaudrate)
	ON_BN_CLICKED(IDC_BUTTON_SURE, OnButtonSure)
	ON_CBN_SELCHANGE(IDC_COMBOCODENUM, OnSelchangeCombocodenum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatCodeSplitter message handlers

void CMatCodeSplitter::OnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}

void CMatCodeSplitter::OnGetcodesplitter() 
{
	// TODO: Add your control notification handler code here
    for(int i = 0; i < 4; i++)
    {
        if (!NET_DVR_MatrixGetCodeSplitter(m_lServerID, i + 1, &m_CodeSplitterInfo[i]))
        {
            MessageBox(NET_DVR_GetErrorMsg());
            return;
        }
    }
    
    OnSelchangeCombocodenum();
    MessageBox("Set successfully");
}

void CMatCodeSplitter::OnSetcodesplitter() 
{
	// TODO: Add your control notification handler code here
	for(int i = 0; i < 4; i++)
    {
        if (!NET_DVR_MatrixSetCodeSplitter(m_lServerID, i + 1, &m_CodeSplitterInfo[i]))
        {
            MessageBox(NET_DVR_GetErrorMsg());
            return;
        }
    }

    MessageBox("Set successfully");
}

BOOL CMatCodeSplitter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for(int i = 0; i < 4; i++)
    {
        if (!NET_DVR_MatrixGetCodeSplitter(m_lServerID, i + 1, &m_CodeSplitterInfo[i]))
        {
            MessageBox(NET_DVR_GetErrorMsg());
            return FALSE;
        }
    }
    m_CodeNumCtrl.SetCurSel(0);
    
//     m_FlowControlCtrl.SetCurSel(m_CodeSplitterInfo[0].byFlowControl);
//     m_StopBitCtrl.SetCurSel(m_CodeSplitterInfo[0].byStopBit);
//     m_ParityCtrl.SetCurSel(m_CodeSplitterInfo[0].byParity);
//     m_DataBitCtrl.SetCurSel(m_CodeSplitterInfo[0].byDataBit);
//     m_BaudRateCtrl.SetCurSel(m_CodeSplitterInfo[0].dwBaudRate);
//     m_DecoderTypeCtrl.SetCurSel(m_CodeSplitterInfo[0].wDecoderType);
    m_DecoderChanCtrl.SetCurSel(m_CodeSplitterInfo[0].byChan - 1);
    
    m_iDecoderAddress = m_CodeSplitterInfo[0].by485Port;
    m_dwCodeSplitterPort = m_CodeSplitterInfo[0].wPort;
    m_strCodeSplitterName = m_CodeSplitterInfo[0].sUserName;
    m_strCodeSplitterPsw = m_CodeSplitterInfo[0].sPassword;
    m_strCodeSplitterIp = m_CodeSplitterInfo[0].struIP.sIpV4;
	//m_iDecoderAddr = m_CodeSplitterInfo[0].wDecoderAddress;

    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatCodeSplitter::OnButtonSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int sel = m_CodeNumCtrl.GetCurSel();
    m_CodeSplitterInfo[sel].by485Port = m_iDecoderAddress;
    m_CodeSplitterInfo[sel].byChan = m_DecoderChanCtrl.GetCurSel() + 1;
//     m_CodeSplitterInfo[sel].byDataBit = m_DataBitCtrl.GetCurSel();
//     m_CodeSplitterInfo[sel].byFlowControl = m_FlowControlCtrl.GetCurSel();
//     m_CodeSplitterInfo[sel].byParity = m_ParityCtrl.GetCurSel();
//     m_CodeSplitterInfo[sel].byStopBit = m_StopBitCtrl.GetCurSel();
//     m_CodeSplitterInfo[sel].dwBaudRate = m_BaudRateCtrl.GetCurSel();
//     m_CodeSplitterInfo[sel].wDecoderType = m_DecoderTypeCtrl.GetCurSel();
    m_CodeSplitterInfo[sel].wPort = m_dwCodeSplitterPort;
    memcpy(m_CodeSplitterInfo[sel].sPassword, m_strCodeSplitterPsw, PASSWD_LEN);
    memcpy(m_CodeSplitterInfo[sel].struIP.sIpV4, m_strCodeSplitterIp, 16);
    memcpy(m_CodeSplitterInfo[sel].sUserName, m_strCodeSplitterName, NAME_LEN);
	//m_CodeSplitterInfo[sel].wDecoderAddress = m_iDecoderAddr;
}

void CMatCodeSplitter::OnSelchangeCombocodenum() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int sel = m_CodeNumCtrl.GetCurSel();
    
//     m_FlowControlCtrl.SetCurSel(m_CodeSplitterInfo[sel].byFlowControl);
//     m_StopBitCtrl.SetCurSel(m_CodeSplitterInfo[sel].byStopBit);
//     m_ParityCtrl.SetCurSel(m_CodeSplitterInfo[sel].byParity);
//     m_DataBitCtrl.SetCurSel(m_CodeSplitterInfo[sel].byDataBit);
//     m_BaudRateCtrl.SetCurSel(m_CodeSplitterInfo[sel].dwBaudRate);
//     m_DecoderTypeCtrl.SetCurSel(m_CodeSplitterInfo[sel].wDecoderType);
    m_DecoderChanCtrl.SetCurSel(m_CodeSplitterInfo[sel].byChan - 1);
    m_iDecoderAddress = m_CodeSplitterInfo[sel].by485Port;
    m_dwCodeSplitterPort = m_CodeSplitterInfo[sel].wPort;
    m_strCodeSplitterName = m_CodeSplitterInfo[sel].sUserName;
    m_strCodeSplitterPsw = m_CodeSplitterInfo[sel].sPassword;
    m_strCodeSplitterIp = m_CodeSplitterInfo[sel].struIP.sIpV4;
	//m_iDecoderAddr = m_CodeSplitterInfo[sel].wDecoderAddress;
    
    UpdateData(FALSE);
}
