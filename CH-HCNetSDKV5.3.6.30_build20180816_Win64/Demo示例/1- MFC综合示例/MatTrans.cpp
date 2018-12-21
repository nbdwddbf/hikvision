// MatTrans.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatTrans.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatTrans dialog

CMatTrans::CMatTrans(CWnd* pParent /*=NULL*/)
	: CDialog(CMatTrans::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatTrans)
	m_Ip = _T("");
	m_Port = 0;
	m_232FullDup = 0;
	m_485FullDup = 0;
	m_strUser = _T("");
	m_strPassword = _T("");
	m_dwSerialNo = 0;
	m_dwSubBoard = 0;
	m_dwSubSys = 0;
	m_dwLocalSerialNo = 0;
	//}}AFX_DATA_INIT
	m_lSerialCount = 0;
	m_iDeviceType = -1;
}


void CMatTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatTrans)
	DDX_Control(pDX, IDC_BAUD485, m_BaudCtrl);
	DDX_Control(pDX, IDC_STOPBIT485, m_StopBitCtrl);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_FLOW485, m_FlowCtrl);
	DDX_Control(pDX, IDC_DATABIT485, m_DataBitCtrl);
	DDX_Control(pDX, IDC_CHECKBIT485, m_CheckBitCtrl);
	DDX_Control(pDX, IDC_COMSER2, m_SerCtrl1);
	DDX_Control(pDX, IDC_COMSER, m_SerCtrl);
	DDX_Control(pDX, IDC_COMPRO, m_ProCtrl);
	DDX_Text(pDX, IDC_EDITIP, m_Ip);
	DDX_Text(pDX, IDC_EDITPORT, m_Port);
	DDX_Text(pDX, IDC_FULLDUPNUM232, m_232FullDup);
	DDX_Text(pDX, IDC_FULLDUPNUM485, m_485FullDup);
	DDX_Text(pDX, IDC_USER, m_strUser);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_SERIALNO, m_dwSerialNo);
	DDX_Text(pDX, IDC_EDIT_SUBBOARD, m_dwSubBoard);
	DDX_Text(pDX, IDC_EDIT_SUBSYS, m_dwSubSys);
	DDX_Text(pDX, IDC_EDIT_LOCAL_SERIALNO, m_dwLocalSerialNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatTrans, CDialog)
	//{{AFX_MSG_MAP(CMatTrans)
	ON_BN_CLICKED(IDC_BUTSET, OnButset)
	ON_BN_CLICKED(IDC_BUTEXIT, OnButexit)
	ON_BN_CLICKED(IDC_ADDTOLIST, OnAddtolist)
	ON_BN_CLICKED(IDC_DELFROMLIST, OnDelfromlist)
	ON_BN_CLICKED(IDC_SETFULLDUP, OnSetfulldup)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST1, OnItemclickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_CBN_SELCHANGE(IDC_COMSER2, OnSelchangeComser2)
	ON_CBN_SELCHANGE(IDC_COMSER, OnSelchangeComser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatTrans message handlers

void CMatTrans::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

void CMatTrans::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CMatTrans::ConInfoToDisp(int index, int i)
{
	char szLan[128] = {0};
	CString tmp;	
 	if (m_stru.struTranInfo[i].byTranChanEnable == 1)
 	{
		g_StringLanType(szLan, "开", "Open");
 	}
 	else if (m_stru.struTranInfo[i].byTranChanEnable == 0)
 	{
 		g_StringLanType(szLan, "关", "Close");
 	}
 	m_List.SetItemText(index, 1, szLan);
 	
 	tmp.Empty();
 	if (m_stru.struTranInfo[i].byLocalSerialDevice == 0)
 	{
 		tmp = "RS485";
 	}
 	else if (m_stru.struTranInfo[i].byLocalSerialDevice == 1)
 	{
 		tmp = "RS232 Console";
 	}
	else if (m_stru.struTranInfo[i].byLocalSerialDevice == 2)
	{
		tmp = "Dual Scom";
	}
 	m_List.SetItemText(index, 2, tmp);

	tmp.Empty();
	tmp.Format("%d", m_stru.struTranInfo[i].dwLocalSerialNo);
	m_List.SetItemText(index, 3, tmp);


 	tmp.Format("%s", m_stru.struTranInfo[i].struRemoteDevIP.sIpV4);
 	m_List.SetItemText(index, 4, tmp);
 	
 	tmp.Format("%d", m_stru.struTranInfo[i].wRemoteDevPort);
 	m_List.SetItemText(index, 5, tmp);
 	
    tmp.Empty();
    if (m_stru.struTranInfo[i].byRemoteSerialDevice == 1)
    {
        tmp = "RS232";
    }
    else if (m_stru.struTranInfo[i].byRemoteSerialDevice == 2)
    {
        tmp = "RS485";
    }
    m_List.SetItemText(index, 6, tmp);

	tmp.Empty();
	tmp.Format("%d", m_stru.struTranInfo[i].dwRemoteSerialNo);
	m_List.SetItemText(index, 7, tmp);
	
	tmp.Empty();
	if (m_stru.struTranInfo[i].byIsEstablished == 1)
	{
		g_StringLanType(szLan, "成功", "Success");
	}
	else if (m_stru.struTranInfo[i].byIsEstablished == 0)
	{
		g_StringLanType(szLan, "失败", "Failed");
	}
	m_List.SetItemText(index, 8, szLan);
	
	tmp.Format("%s", m_stru.struTranInfo[i].byUsername);
	m_List.SetItemText(index, 9, tmp);
	
	tmp.Empty();
	tmp.Format("%s", m_stru.struTranInfo[i].byPassword);
	m_List.SetItemText(index, 10, tmp);
}

BOOL CMatTrans::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceType = g_struDeviceInfo[g_pMainDlg->GetCurDeviceIndex()].iDeviceType;

	char szLan[128] = {0};
	m_ProCtrl.SetCurSel(0);
	m_SerCtrl.SetCurSel(0);
	OnSelchangeComser();
	m_SerCtrl1.SetCurSel(0);
	OnSelchangeComser2();
	
	m_DataBitCtrl.SetCurSel(3);
	m_BaudCtrl.SetCurSel(9);
	m_FlowCtrl.SetCurSel(0);
	m_StopBitCtrl.SetCurSel(0);
	m_CheckBitCtrl.SetCurSel(0);

	m_Port = 0;

	m_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	g_StringLanType(szLan, "序号", "No.");
	m_List.InsertColumn(0, szLan, LVCFMT_LEFT, 40, -1);
	g_StringLanType(szLan, "开关", "Switch");
	m_List.InsertColumn(1, szLan, LVCFMT_LEFT, 40, -1);
	g_StringLanType(szLan, "本地串口类型", "Local Serial Type");
	m_List.InsertColumn(2, szLan, LVCFMT_LEFT, 90, -1);
	g_StringLanType(szLan, "本地串口号", "Local Serial No.");
	m_List.InsertColumn(3, szLan, LVCFMT_LEFT, 90, -1);
	g_StringLanType(szLan, "IP地址", "Ip address");
	m_List.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "端口号", "Port");
	m_List.InsertColumn(5, szLan, LVCFMT_LEFT, 50, -1);
	g_StringLanType(szLan, "远程串口类型", "Remote Serial Type");
	m_List.InsertColumn(6, szLan, LVCFMT_LEFT, 90, -1);
	g_StringLanType(szLan, "远程串口号", "Remote Serial No.");
	m_List.InsertColumn(7, szLan, LVCFMT_LEFT, 90, -1);
	g_StringLanType(szLan, "透明通道建立状态", "Serial Set status");
	m_List.InsertColumn(8, szLan, LVCFMT_LEFT, 120, -1);
	g_StringLanType(szLan, "用户名", "User");
	m_List.InsertColumn(9, szLan, LVCFMT_LEFT, 50, -1);
	g_StringLanType(szLan, "密码", "Password");
	m_List.InsertColumn(10, szLan, LVCFMT_LEFT, 50, -1);

// 	if (m_iDeviceType == DS_B20_MSU_NP || m_iDeviceType == DS64XXHD_T) //B20主控
// 	{
		GetDlgItem(IDC_EDIT_SUBBOARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SUBSYS)->EnableWindow(TRUE);
// 	}
// 	else
// 	{
// 		GetDlgItem(IDC_EDIT_SUBBOARD)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_EDIT_SUBSYS)->EnableWindow(FALSE);
// 	}
	
 	CString tmp;
 	memset(&m_stru, 0, sizeof(m_stru));
 	if (!NET_DVR_MatrixGetTranInfo_V30(m_lServerID, &m_stru))
 	{
 		tmp.Format("Error: NET_DVR_MatrixGetTranInfo = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 	}
 	else
 	{
 		int index = 0;
 		for (int i=0; i<MAX_SERIAL_NUM; i++)
 		{
 			tmp.Format("%d", i+1);
 			index = m_List.InsertItem(m_List.GetItemCount(), tmp);
 
 			ConInfoToDisp(index, i);
 		}
 	}
 	m_232FullDup = (char)m_stru.by232IsDualChan;
 	m_485FullDup = (char)m_stru.by485IsDualChan;
	UpdateData(FALSE);
	return TRUE; 	              
}

void CMatTrans::OnButset() 
{
	// TODO: Add your control notification handler code here
 	UpdateData(TRUE);
 
 	m_stru.dwSize = sizeof(m_stru);
 	m_stru.by232IsDualChan = m_232FullDup;
 	m_stru.by485IsDualChan = m_485FullDup;
 
 	if (!NET_DVR_MatrixSetTranInfo_V30(m_lServerID, &m_stru))
 	{
 		CString tmp;
 		tmp.Format("Error: NET_DVR_MatrixSetTranInfo = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 		return;
 	}
	char szLan[128] = {0};
	g_StringLanType(szLan, "设置成功", "Set successfully");
	AfxMessageBox(szLan);	
}


void CMatTrans::OnButexit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CMatTrans::OnAddtolist() 
{
	// TODO: Add your control notification handler code here
 	UpdateData(TRUE);
 	
 	POSITION pos = m_List.GetFirstSelectedItemPosition();
 	if (pos == NULL)
 	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "不能添加，建议先在列表里选一项再改", "Can not add, it is recommended select a item in a list");
		AfxMessageBox(szLan);
 		return;
 	}
 	int sel = m_List.GetNextSelectedItem(pos);
 
 	memset(&(m_stru.struTranInfo[sel]), 0, sizeof(m_stru.struTranInfo[sel]));
 
 	m_stru.struTranInfo[sel].byTranChanEnable = m_ProCtrl.GetCurSel();
 	m_stru.struTranInfo[sel].byLocalSerialDevice = m_SerCtrl.GetCurSel();
	m_stru.struTranInfo[sel].dwLocalSerialNo = m_dwLocalSerialNo;
 	m_stru.struTranInfo[sel].byRemoteSerialDevice = m_SerCtrl1.GetCurSel()+1;
// 	if (m_iDeviceType == DS_B20_MSU_NP || m_iDeviceType == DS64XXHD_T) //B20主控
// 	{
		m_stru.struTranInfo[sel].dwRemoteSerialNo = m_dwSubBoard<<16|m_dwSubSys<<8|m_dwSerialNo;
// 	}
// 	else
// 	{
// 		m_stru.struTranInfo[sel].dwRemoteSerialNo = m_dwSerialNo;
// 	}
 	sprintf(m_stru.struTranInfo[sel].struRemoteDevIP.sIpV4, "%s", m_Ip);
    sprintf((char*)m_stru.struTranInfo[sel].byUsername, "%s", m_strUser);
    sprintf((char*)m_stru.struTranInfo[sel].byPassword, "%s", m_strPassword);
 	m_stru.struTranInfo[sel].wRemoteDevPort = m_Port;
 	m_stru.struTranInfo[sel].RemoteSerialDevCfg.baudrate = m_BaudCtrl.GetCurSel();
 	m_stru.struTranInfo[sel].RemoteSerialDevCfg.databits = m_DataBitCtrl.GetCurSel();
 	m_stru.struTranInfo[sel].RemoteSerialDevCfg.stopbits = m_StopBitCtrl.GetCurSel();
 	m_stru.struTranInfo[sel].RemoteSerialDevCfg.parity = m_CheckBitCtrl.GetCurSel();
 	m_stru.struTranInfo[sel].RemoteSerialDevCfg.flowcontrol = m_FlowCtrl.GetCurSel();
 
 	ConInfoToDisp(sel, sel);
 	UpdateData(FALSE);
}

void CMatTrans::OnDelfromlist() 
{
	// TODO: Add your control notification handler code here
 	UpdateData(TRUE);
 	
 	POSITION pos = m_List.GetFirstSelectedItemPosition();
 	if (pos == NULL)
 	{
 		return;
 	}
 	int sel = m_List.GetNextSelectedItem(pos);
 
 	memset(&(m_stru.struTranInfo[sel]), 0, sizeof(m_stru.struTranInfo[sel]));
 
 	ConInfoToDisp(sel, sel);
 	UpdateData(FALSE);
}

void CMatTrans::OnSetfulldup() 
{
	// TODO: Add your control notification handler code here
 	UpdateData(TRUE);
 	
 	POSITION pos = m_List.GetFirstSelectedItemPosition();
 	if (pos == NULL)
 	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "请先选中一项", "Please select a item first");
		AfxMessageBox(szLan);
 		return;
 	}
 	int sel = m_List.GetNextSelectedItem(pos);
 
 	if (m_stru.struTranInfo[sel].struRemoteDevIP.sIpV4 != "" && m_stru.struTranInfo[sel].wRemoteDevPort != 0)
 	{
 		if (m_stru.struTranInfo[sel].byLocalSerialDevice == 0)
 		{
 			m_485FullDup = sel + 1;
 		}
 		else
 		{
 			m_232FullDup = sel + 1;
 		}
 	}
 
 	UpdateData(FALSE);
}

void CMatTrans::OnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
 	UpdateData(TRUE);
 
 	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
 	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CMatTrans::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	
	// TODO: Add your control notification handler code here
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}
	int sel = m_List.GetNextSelectedItem(pos);
	
	m_ProCtrl.SetCurSel(m_stru.struTranInfo[sel].byTranChanEnable);
	m_SerCtrl.SetCurSel(m_stru.struTranInfo[sel].byLocalSerialDevice);
	OnSelchangeComser();
	m_dwLocalSerialNo = m_stru.struTranInfo[sel].dwLocalSerialNo;
	if (m_stru.struTranInfo[sel].byRemoteSerialDevice > 0)
	{
		m_SerCtrl1.SetCurSel(m_stru.struTranInfo[sel].byRemoteSerialDevice-1);
	}
	else
	{
		m_SerCtrl1.SetCurSel(m_stru.struTranInfo[sel].byRemoteSerialDevice);
	}
	OnSelchangeComser2();
// 	if (m_iDeviceType == DS_B20_MSU_NP || m_iDeviceType == DS64XXHD_T) //B20主控
// 	{
		DWORD dwRemoteSerialNo = m_stru.struTranInfo[sel].dwRemoteSerialNo;
		m_dwSubBoard = dwRemoteSerialNo>>16;
		m_dwSubSys = dwRemoteSerialNo>>8&0x000000ff;
		m_dwSerialNo = dwRemoteSerialNo&0x000000ff;
// 	}
// 	else
// 	{
// 		m_dwSerialNo = m_stru.struTranInfo[sel].dwRemoteSerialNo;
// 	}
	m_Ip.Format("%s", m_stru.struTranInfo[sel].struRemoteDevIP.sIpV4);
	m_Port = m_stru.struTranInfo[sel].wRemoteDevPort;
	m_BaudCtrl.SetCurSel(m_stru.struTranInfo[sel].RemoteSerialDevCfg.baudrate);
	m_DataBitCtrl.SetCurSel(m_stru.struTranInfo[sel].RemoteSerialDevCfg.databits);
	m_StopBitCtrl.SetCurSel(m_stru.struTranInfo[sel].RemoteSerialDevCfg.stopbits);
	m_FlowCtrl.SetCurSel(m_stru.struTranInfo[sel].RemoteSerialDevCfg.flowcontrol);
	m_CheckBitCtrl.SetCurSel(m_stru.struTranInfo[sel].RemoteSerialDevCfg.parity);
    m_strUser.Format("%s", m_stru.struTranInfo[sel].byUsername);
    m_strPassword.Format("%s", m_stru.struTranInfo[sel].byPassword);
	
	UpdateData(FALSE);
	*pResult = 0;
}

void CMatTrans::OnSelchangeComser2() 
{
	// TODO: Add your control notification handler code here
}

void CMatTrans::OnSelchangeComser() 
{
	// TODO: Add your control notification handler code here
	
}
