// DlgLcdSerial.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLcdSerial.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdSerial dialog


CDlgLcdSerial::CDlgLcdSerial(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLcdSerial::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLcdSerial)
	m_dwCurrentSerial = 0;
	m_bySerialNum = 0;
	//}}AFX_DATA_INIT
}


void CDlgLcdSerial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLcdSerial)
	DDX_Control(pDX, IDC_COMBO_SERIAL_PROTOCOL, m_comboSerialProtocol);
	DDX_Control(pDX, IDC_COMBO_DIST_SERIALSET, m_comboDistSerialSet);
	DDX_Text(pDX, IDC_EDIT_DIST_CURRENTSERIAL, m_dwCurrentSerial);
	DDX_Text(pDX, IDC_EDIT_DIST_SERIALNUM, m_bySerialNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLcdSerial, CDialog)
	//{{AFX_MSG_MAP(CDlgLcdSerial)
	ON_BN_CLICKED(IDC_BUT_DIST_SERIAL_GET, OnButDistSerialGet)
	ON_BN_CLICKED(IDC_BUT_DIST_CURRENTSERIAL_GET, OnButDistCurrentserialGet)
	ON_BN_CLICKED(IDC_BUT_DIST_CURRENTSERIAL_SET, OnButDistCurrentserialSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdSerial message handlers

BOOL CDlgLcdSerial::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

    memset(&m_struSerialCtrl, 0, sizeof(m_struSerialCtrl));
    memset(&m_struUsingSerialPort, 0, sizeof(m_struUsingSerialPort));

    m_struSerialCtrl.dwSize = sizeof(m_struSerialCtrl);
    m_struUsingSerialPort.dwSize = sizeof(m_struUsingSerialPort);
	m_comboSerialProtocol.ResetContent(); 
	unsigned int *pSerialProto = NULL; 
	DWORD dwNum = 0; 
	GetSerialProto(pSerialProto, dwNum); 
	for (int i=0; i<dwNum; i++)
	{
		m_comboSerialProtocol.AddString((char *)pSerialProto[i]);
	}		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLcdSerial::OnButDistSerialGet() 
{
	// TODO: Add your control notification handler code here
    char szLan[64] = {0};
    DWORD dwReturned = 0;
    int i = 0;
    CString cs;

    if (!NET_DVR_GetDVRConfig(m_lUserId, NET_DVR_BIGSCREEN_GETSERIAL, 0, &m_struSerialCtrl, sizeof(m_struSerialCtrl), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_BIGSCREEN_GETSERIAL");
        g_StringLanType(szLan, "获取串口集失败", "Get serial set fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_BIGSCREEN_GETSERIAL");
        m_comboDistSerialSet.ResetContent();

        for (i = 0; i < m_struSerialCtrl.bySerialNum; i++)
        {
            cs.Format("%d", m_struSerialCtrl.bySerial[i]);
            m_comboDistSerialSet.AddString(cs);            
        }
        if ( m_struSerialCtrl.bySerialNum )
        {
            m_comboDistSerialSet.SetCurSel(0); 
            m_bySerialNum = m_struSerialCtrl.bySerialNum; 
        }
        
        UpdateData(FALSE);
    }
}

void CDlgLcdSerial::OnButDistCurrentserialGet() 
{
	// TODO: Add your control notification handler code here
    DWORD dwReturned = 0;
    char szLan[64] = {0};

	if (!NET_DVR_GetDVRConfig(m_lUserId, NET_DVR_GET_USING_SERIALPORT, 0, &m_struUsingSerialPort, sizeof(m_struUsingSerialPort), &dwReturned))
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_USING_SERIALPORT");
        g_StringLanType(szLan, "获取当前串口参数失败", "Get current serial port parameter fail");
        AfxMessageBox(szLan);
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_USING_SERIALPORT");
        m_dwCurrentSerial = m_struUsingSerialPort.dwSerialPort;
        m_comboSerialProtocol.SetCurSel(m_struUsingSerialPort.byProtocolType - 1);
        UpdateData(FALSE);
    }
}

void CDlgLcdSerial::OnButDistCurrentserialSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[64] = {0};

    m_struUsingSerialPort.byProtocolType = m_comboSerialProtocol.GetCurSel() + 1;
    m_struUsingSerialPort.dwSerialPort = m_dwCurrentSerial;

    if (!NET_DVR_SetDVRConfig(m_lUserId, NET_DVR_SET_USING_SERIALPORT, 0, &m_struUsingSerialPort, sizeof(m_struUsingSerialPort)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_USING_SERIALPORT");
        g_StringLanType(szLan, "设置当前串口参数失败", "Set current serial port parameter fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_USING_SERIALPORT");
    }
}
