// DlgInfoDiffusionTermainlServer.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionTermainlServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTermainlServer dialog


CDlgInfoDiffusionTermainlServer::CDlgInfoDiffusionTermainlServer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionTermainlServer::IDD, pParent)
    , m_csUserName(_T(""))
    , m_csPwd(_T(""))
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionTermainlServer)
	m_byRegister = FALSE;
	m_dwGroupId = 0;
	m_szIP = _T("");
	m_dwPort = 0;
	m_dwTerminalId = 0;
	//}}AFX_DATA_INIT

    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    memset(&m_struAddr, 0, sizeof(m_struAddr));
    m_struAddr.dwSize = sizeof(m_struAddr);
    m_pOutputXmlBuffer = new char[MAX_LEN_XML];
    memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
    m_nCurSelGroup = -1;
	m_nCurSelTerminal = -1;
}


void CDlgInfoDiffusionTermainlServer::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInfoDiffusionTermainlServer)
    DDX_Control(pDX, IDC_LIST_TERMINAL, m_listTerminal);
    DDX_Control(pDX, IDC_LIST_GROUP, m_listGroup);
    DDX_Control(pDX, IDC_COMBO_OPE_TYPE, m_cmbOprType);
    DDX_Control(pDX, IDC_COMBO_IPTYPE, m_cmbIPType);
    DDX_Check(pDX, IDC_CHECK_REG, m_byRegister);
    DDX_Text(pDX, IDC_EDIT_GROUPID, m_dwGroupId);
    DDX_Text(pDX, IDC_EDIT_IP, m_szIP);
    DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
    DDX_Text(pDX, IDC_EDIT_TER_ID, m_dwTerminalId);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_USERNAME, m_csUserName);
    DDX_Text(pDX, IDC_EDIT_PWD, m_csPwd);
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionTermainlServer, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionTermainlServer)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_GROUP_ADD, OnBtnGroupAdd)
	ON_BN_CLICKED(IDC_BTN_GROUP_DEL, OnBtnGroupDel)
	ON_BN_CLICKED(IDC_BTN_GROUP_MOD, OnBtnGroupMod)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_TER_ADD, OnBtnTerAdd)
	ON_BN_CLICKED(IDC_BTN_TER_DEL, OnBtnTerDel)
	ON_BN_CLICKED(IDC_BTN_TER_MOD, OnBtnTerMod)
	ON_NOTIFY(NM_CLICK, IDC_LIST_GROUP, OnClickListGroup)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TERMINAL, OnClickListTerminal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTermainlServer message handlers

void CDlgInfoDiffusionTermainlServer::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	CString strCommand;
    strCommand.Format("GET /ISAPI/Publish/TerminalMgr/publishServerAddr\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();

    char szStatusBuff[1024]={0};
    NET_DVR_XML_CONFIG_OUTPUT strOutputParm = {0};
    strOutputParm.dwSize =sizeof(struInputParam);
    strOutputParm.lpOutBuffer = m_pOutputXmlBuffer;
    strOutputParm.dwOutBufferSize = MAX_LEN_XML;
    strOutputParm.lpStatusBuffer = szStatusBuff;
    strOutputParm.dwStatusSize = sizeof(szStatusBuff);
    if(NET_DVR_STDXMLConfig(m_lUserID,&struInputParam,&strOutputParm))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
    memset(&m_struAddr,0,sizeof(m_struAddr));
    m_struAddr.dwSize = sizeof(m_struAddr);
    ConvertTerServerParamsXmlToStru(m_pOutputXmlBuffer,&m_struAddr);
    m_byRegister = m_struAddr.byRegister;
    if(0 == strcmp(m_struAddr.szFormatType,"ipaddress"))
    {
        m_cmbIPType.SetCurSel(1);
        m_szIP = m_struAddr.szIpv4;
    }
    else if(0 == strcmp(m_struAddr.szFormatType,"hostname"))
    {
        m_cmbIPType.SetCurSel(0);
        m_szIP = m_struAddr.szHostName;
    }
    else if(0 == strcmp(m_struAddr.szFormatType,"ipv6address"))
    {
        m_cmbIPType.SetCurSel(2);
        m_szIP = m_struAddr.szIpv6;
    }
    m_cmbOprType.SetCurSel(m_cmbOprType.FindString(-1,m_struAddr.szOparaType));
    m_dwPort = m_struAddr.wPort;
    UpdatList();
    UpdateData(FALSE);
}

void CDlgInfoDiffusionTermainlServer::OnBtnGroupAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CString str;
    int nIndex = m_listGroup.GetItemCount();
    str.Format("%d",nIndex+1);
    m_listGroup.InsertItem(nIndex,str);
    str.Format("%d",m_dwGroupId);
    m_listGroup.SetItemText(nIndex,1,str);
    m_listGroup.SetItemState(m_nCurSelGroup,0,-1);
    m_listGroup.SetItemState(nIndex,LVIS_SELECTED,LVIS_SELECTED);
    m_listGroup.SetFocus();
    m_nCurSelGroup = nIndex;
    m_struAddr.arrGroup[nIndex] = m_dwGroupId;
    m_struAddr.dwGroupNo++;
}

void CDlgInfoDiffusionTermainlServer::OnBtnGroupDel() 
{
	// TODO: Add your control notification handler code here
	for(int nGroup = m_nCurSelGroup;nGroup<m_listGroup.GetItemCount()-1;nGroup++)
    {
        m_struAddr.arrGroup[nGroup] = m_struAddr.arrGroup[nGroup+1];
        m_listGroup.SetItemText(nGroup, 1, m_listGroup.GetItemText(nGroup+1, 1));
    }
    m_struAddr.arrGroup[m_listGroup.GetItemCount()-1] = 0;
    m_listGroup.DeleteItem(m_listGroup.GetItemCount()-1);
    m_nCurSelGroup = -1;
    m_struAddr.dwGroupNo--;
}

void CDlgInfoDiffusionTermainlServer::OnBtnGroupMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CString str;
    str.Format("%d",m_dwGroupId);
    m_listGroup.SetItemText(m_nCurSelGroup,1,str);
    m_struAddr.arrGroup[m_nCurSelGroup]=m_dwGroupId;
}

void CDlgInfoDiffusionTermainlServer::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	int nSel = m_cmbIPType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    if(nSel == 0)
    {
        strcpy(m_struAddr.szFormatType,"hostname");
        strcpy(m_struAddr.szHostName , m_szIP);
    }
    else if(nSel == 1)
    {
        strcpy(m_struAddr.szFormatType,"ipaddress");
        strcpy(m_struAddr.szIpv4 ,m_szIP);
    }
    else if(nSel == 2)
    {
        strcpy(m_struAddr.szFormatType,"ipv6address");
        strcpy(m_struAddr.szIpv6 ,m_szIP);
    }
    nSel = m_cmbOprType.GetCurSel();
    if(nSel == CB_ERR)
    {
        return;
    }
    CString strOType;
    m_cmbOprType.GetLBText(nSel,strOType);
    strcpy(m_struAddr.szOparaType,strOType);
    m_struAddr.dwSize = sizeof(m_struAddr);
    m_struAddr.wPort = m_dwPort;
    char* pInputBuff = NULL;
    DWORD dwInputSize = 0;
    memcpy(m_struAddr.szUserName, m_csUserName.GetBuffer(0), m_csUserName.GetLength());
    memcpy(m_struAddr.szPwd, m_csPwd.GetBuffer(0), m_csPwd.GetLength());
	ConvertTermServerParamsStruToXml(&m_struAddr, &pInputBuff,dwInputSize);

    CString strCommand;
    strCommand.Format("PUT /ISAPI/Publish/TerminalMgr/publishServerAddr\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
    struInputParam.lpInBuffer = pInputBuff;
    struInputParam.dwInBufferSize = dwInputSize;
    
    char szStatusBuff[1024] = {0};
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);
    
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        delete[] pInputBuff;
        pInputBuff = NULL;
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
    UpdateData(FALSE);
}

void CDlgInfoDiffusionTermainlServer::OnBtnTerAdd() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CString str;
    int nIndex = m_listTerminal.GetItemCount();
    str.Format("%d",nIndex+1);
    m_listTerminal.InsertItem(nIndex,str);
    str.Format("%d",m_dwTerminalId);
    m_listTerminal.SetItemText(nIndex,1,str);
    m_listTerminal.SetItemState(m_nCurSelTerminal,0,-1);
    m_listTerminal.SetItemState(nIndex,LVIS_SELECTED,LVIS_SELECTED);
    m_listTerminal.SetFocus();
    m_nCurSelTerminal = nIndex;
    m_struAddr.arrTerminal[nIndex] = m_dwTerminalId;
    m_struAddr.dwTerminalNo++;
}

void CDlgInfoDiffusionTermainlServer::OnBtnTerDel() 
{
	// TODO: Add your control notification handler code here
    for(int nTerminal = m_nCurSelTerminal;nTerminal<m_listTerminal.GetItemCount()-1;nTerminal++)
    {
        m_struAddr.arrTerminal[nTerminal] = m_struAddr.arrTerminal[nTerminal+1];
        m_listTerminal.SetItemText(nTerminal, 1, m_listTerminal.GetItemText(nTerminal+1, 1));
    }
    m_struAddr.arrTerminal[m_listTerminal.GetItemCount()-1] = 0;
    m_listTerminal.DeleteItem(m_listTerminal.GetItemCount()-1);
    m_nCurSelTerminal = -1;
    m_struAddr.dwTerminalNo--;
}

void CDlgInfoDiffusionTermainlServer::OnBtnTerMod() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CString str;
    str.Format("%d",m_dwTerminalId);
    m_listTerminal.SetItemText(m_nCurSelTerminal,1,str);
    m_struAddr.arrTerminal[m_nCurSelTerminal]=m_dwTerminalId;
}

void CDlgInfoDiffusionTermainlServer::OnClickListGroup(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    POSITION pos = m_listGroup.GetFirstSelectedItemPosition();
    if(pos)
    {
        m_nCurSelGroup = m_listGroup.GetNextSelectedItem(pos);
        m_dwGroupId = m_struAddr.arrGroup[m_nCurSelGroup];
        UpdateData(FALSE);
    }
	*pResult = 0;
}

void CDlgInfoDiffusionTermainlServer::OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listTerminal.GetFirstSelectedItemPosition();
    if(pos)
    {
        m_nCurSelTerminal = m_listTerminal.GetNextSelectedItem(pos);
        m_dwTerminalId = m_struAddr.arrTerminal[m_nCurSelTerminal];
        UpdateData(FALSE);
    }
	*pResult = 0;
}

void CDlgInfoDiffusionTermainlServer::InitList()
{
    DWORD dwExStyle = m_listGroup.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
    m_listGroup.SetExtendedStyle(dwExStyle);
    
    char szLan[512] = {0};
    g_StringLanType(szLan, "ÐòºÅ", "Index");
    m_listGroup.InsertColumn(0, szLan);
    m_listGroup.SetColumnWidth(0, 60);
    
    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "ÖÕ¶Ë×é±àºÅ", "Group No.");
    m_listGroup.InsertColumn(1, szLan);
    m_listGroup.SetColumnWidth(1, 80);
    

    m_listTerminal.SetExtendedStyle(dwExStyle);
    g_StringLanType(szLan, "ÐòºÅ", "Index");
    m_listTerminal.InsertColumn(0, szLan);
    m_listTerminal.SetColumnWidth(0, 60);
    
    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "ÖÕ¶Ë±àºÅ", "Terminal No.");
    m_listTerminal.InsertColumn(1, szLan);
	m_listTerminal.SetColumnWidth(1, 100);
}

void CDlgInfoDiffusionTermainlServer::UpdatList()
{
    if(0 == strcmp(m_struAddr.szOparaType,"byTerminal"))
    {
        m_listTerminal.DeleteAllItems();
        CString str;
        for(int nTer = 0;nTer < m_struAddr.dwTerminalNo;nTer++)
        {
            str.Format("%d",nTer+1);
            m_listTerminal.InsertItem(nTer,str);
            str.Format("%d",m_struAddr.arrTerminal[nTer]);
            m_listTerminal.SetItemText(nTer,1,str);
        }
    }
    else if(0 == strcmp(m_struAddr.szOparaType,"byGroup"))
    {
        m_listTerminal.DeleteAllItems();
        CString str;
        for(int nTer = 0;nTer < m_struAddr.dwTerminalNo;nTer++)
        {
            str.Format("%d",nTer+1);
            m_listTerminal.InsertItem(nTer,str);
            str.Format("%d",m_struAddr.arrTerminal[nTer]);
            m_listTerminal.SetItemText(nTer,1,str);
        }
    }
    
}

BOOL CDlgInfoDiffusionTermainlServer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
