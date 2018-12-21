// DlgCreateVD.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCreateVD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateVD dialog


CDlgCreateVD::CDlgCreateVD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateVD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCreateVD)
	m_csVDName = _T("");
	m_csArrayName = _T("");
	m_nVDCapacity = 0;
	m_dwBlockSize = 0;
	m_strWarrantIP = _T("");
	m_strArrayIDGroup = _T("");
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struArraySpaceAlloc, 0, sizeof(m_struArraySpaceAlloc));
    memset(&m_struArrayInfo, 0, sizeof(m_struArrayInfo));
}

inline BOOL CDlgCreateVD::ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) > 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}
	return FALSE;
}


void CDlgCreateVD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateVD)
	DDX_Control(pDX, IDC_COMBO_VD_TYPE, m_cmbVDType);
	DDX_Control(pDX, IDC_COMBO_INIT_TYPE, m_comboInitType);
	DDX_Control(pDX, IDC_COMBO_VD_SLOT, m_comboVDSlot);
	DDX_Text(pDX, IDC_EDIT_VD_NAME, m_csVDName);
	DDX_Text(pDX, IDC_STATIC_ARRAY_NAME, m_csArrayName);
	DDX_Text(pDX, IDC_EDIT_VD_CAPACITY, m_nVDCapacity);
	DDX_Text(pDX, IDC_EDIT_VD_BLOCK_SIZE, m_dwBlockSize);
	DDX_Text(pDX, IDC_EDIT_WARRANT_IP, m_strWarrantIP);
	DDX_Text(pDX, IDC_EDIT_ARRAY_ID_GROUP, m_strArrayIDGroup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateVD, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateVD)
	ON_BN_CLICKED(IDC_BTN_CRATE_ARRAY, OnBtnCrateArray)
	ON_CBN_SELCHANGE(IDC_COMBO_VD_SLOT, OnSelchangeComboVdSlot)
	ON_CBN_SELCHANGE(IDC_COMBO_VD_TYPE, OnSelchangeComboVdType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateVD message handlers

void CDlgCreateVD::OnBtnCrateArray() 
{
    UpdateData(TRUE);
	unsigned __int64 dwCapacity =  ((unsigned __int64)m_nVDCapacity) * 1024 *1024;

	m_struOpeateVD.byVDType = m_cmbVDType.GetCurSel();
	if (0 == m_struOpeateVD.byVDType)
	{
		m_struOpeateVD.uVDParam.struHikVDParam.byName;
		strncpy((char*)m_struOpeateVD.uVDParam.struHikVDParam.byName, m_csVDName.GetBuffer(0), 15);
		CString strSlotNum;
		m_comboVDSlot.GetWindowText(strSlotNum);
		m_struOpeateVD.uVDParam.struHikVDParam.bySlot = atoi(strSlotNum);
		m_struOpeateVD.uVDParam.struHikVDParam.wArrayID = m_struArrayInfo.wArrayID;
		
		m_struOpeateVD.uVDParam.struHikVDParam.dwLCapacity = *((DWORD*)&dwCapacity);
		m_struOpeateVD.uVDParam.struHikVDParam.dwHCapacity = *((DWORD*)((char*)&dwCapacity + 4));
		m_struOpeateVD.uVDParam.struHikVDParam.byInitType = m_comboInitType.GetCurSel();
	}
	else if (1 == m_struOpeateVD.byVDType)
	{
		strncpy((char*)m_struOpeateVD.uVDParam.struLunParam.szName, m_csVDName.GetBuffer(0), 15);
		m_struOpeateVD.uVDParam.struLunParam.dwBlockSize = m_dwBlockSize;
		strncpy(m_struOpeateVD.uVDParam.struLunParam.szArrayIDGroup, m_strArrayIDGroup, 31);
		m_struOpeateVD.uVDParam.struLunParam.dwLCapacity = *((DWORD*)&dwCapacity);
		m_struOpeateVD.uVDParam.struLunParam.dwHCapacity = *((DWORD*)((char*)&dwCapacity + 4));
	}
	else if (2 == m_struOpeateVD.byVDType)
	{
		strncpy((char*)m_struOpeateVD.uVDParam.struDvrParam.szName, m_csVDName.GetBuffer(0), 15);
		m_struOpeateVD.uVDParam.struDvrParam.dwBlockSize = m_dwBlockSize;
		strncpy(m_struOpeateVD.uVDParam.struDvrParam.szArrayIDGroup, m_strArrayIDGroup, 31);
		m_struOpeateVD.uVDParam.struDvrParam.dwLCapacity = *((DWORD*)&dwCapacity);
		m_struOpeateVD.uVDParam.struDvrParam.dwHCapacity = *((DWORD*)((char*)&dwCapacity + 4));
		if (ValidIPv6((unsigned char*)m_strWarrantIP.GetBuffer(0)))
		{
			strncpy((char*)m_struOpeateVD.uVDParam.struDvrParam.struWarrantIP.byIPv6, m_strWarrantIP, 127);
		}
		else
		{
			strncpy(m_struOpeateVD.uVDParam.struDvrParam.struWarrantIP.sIpV4, m_strWarrantIP, 15);
		}
	}

 
    if (!CreateVD())
    {
        AfxMessageBox("Fail to create VD");
    }
    else
    {
        if (!GetArraySpaceAlloc(m_struArrayInfo.wArrayID))
        {
            //MessageBox("Fail to GetArraySpaceAlloc");
            //return;
        }
        
        InitWnd();
    }
    
}

BOOL CDlgCreateVD::GetArraySpaceAlloc(DWORD dwArraySlot)
{
    
    if (!NET_DVR_GetArraySpaceAlloc(m_lServerID, dwArraySlot, &m_struArraySpaceAlloc))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetArraySpaceAlloc");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetArraySpaceAlloc");
        return TRUE;
    }
}

BOOL CDlgCreateVD::CreateVD()
{
    if (!NET_DVR_CreateVDEx(m_lServerID, &m_struOpeateVD))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CreateVD");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CreateVD");
        return TRUE;
    }
}

BOOL CDlgCreateVD::OnInitDialog() 
{
	CDialog::OnInitDialog();

    m_csArrayName = m_struArrayInfo.byArrayName;
    UpdateData(FALSE);

    if (!GetArraySpaceAlloc(m_struArrayInfo.wArrayID))
    {
//         MessageBox("Fail to GetArraySpaceAlloc");
//         return FALSE;
    }

    InitWnd();

    m_comboVDSlot.SetCurSel(0);
    OnSelchangeComboVdSlot();
	OnSelchangeComboVdType();
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCreateVD::InitWnd()
{
    char szLan[128] = {0};
    m_comboVDSlot.ResetContent();
    for (int i = 0; i < m_struArraySpaceAlloc.byVDSlotCount; i++)
    {
        sprintf(szLan, "%d", m_struArraySpaceAlloc.struVDSlots[i].wVDSlot);
        m_comboVDSlot.AddString(szLan);
    }

    m_comboInitType.ResetContent();
    g_StringLanType(szLan, "快速初始化", "Quick Format");
    m_comboInitType.AddString(szLan);
    g_StringLanType(szLan, "前台完全初始化", "Front full format");
    m_comboInitType.AddString(szLan); 
    g_StringLanType(szLan, "后台完全初始化", "Back full format");
    m_comboInitType.AddString(szLan);
	g_StringLanType(szLan, "不初始化", "Back full format");
    m_comboInitType.AddString(szLan);
    m_comboInitType.SetCurSel(0);

	m_cmbVDType.SetCurSel(0);

}

void CDlgCreateVD::OnSelchangeComboVdSlot() 
{
    char szLan[128] = {0};
    int nSlotIndex = m_comboVDSlot.GetCurSel();

    unsigned __int64 dwCapacity = 0;
    	
    *((DWORD*)&dwCapacity) = m_struArraySpaceAlloc.struVDSlots[nSlotIndex].dwLVDSlotSize;
    *((DWORD*)((char*)&dwCapacity + 4))  = m_struArraySpaceAlloc.struVDSlots[nSlotIndex].dwHVDSlotSize;
    dwCapacity >>= 20;

    if (m_struArraySpaceAlloc.struVDSlots[nSlotIndex].byAlloc)
    {
        sprintf(szLan, "have Alloced: VD = %d spcace = %I64u Gb", m_struArraySpaceAlloc.struVDSlots[nSlotIndex].wVDSlot,
            dwCapacity);
    }
    else
    {
        sprintf(szLan, "haven't Alloced: spcace = %I64u Gb", dwCapacity);
    }
    GetDlgItem(IDC_STATIC_SLOT_INFO)->SetWindowText(szLan);
}

void CDlgCreateVD::OnSelchangeComboVdType() 
{
	// TODO: Add your control notification handler code here
	switch (m_cmbVDType.GetCurSel())
	{
	case 0:
		GetDlgItem(IDC_STATIC_ARRAY_NAME)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_VD_SLOT)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_VD_SLOT)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_INIT_TYPE)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_INIT_TYPE)->ShowWindow(TRUE); 
		GetDlgItem(IDC_STATIC_SLOT_INFO)->ShowWindow(TRUE); 

		GetDlgItem(IDC_EDIT_ARRAY_ID_GROUP)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_BLOCK_SIZE)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_VD_BLOCK_SIZE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_IP)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_WARRANT_IP)->ShowWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_EDIT_ARRAY_ID_GROUP)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_BLOCK_SIZE)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VD_BLOCK_SIZE)->ShowWindow(TRUE);

		GetDlgItem(IDC_STATIC_IP)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_WARRANT_IP)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_ARRAY_NAME)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_VD_SLOT)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_VD_SLOT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_INIT_TYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_INIT_TYPE)->ShowWindow(FALSE); 
		GetDlgItem(IDC_STATIC_SLOT_INFO)->ShowWindow(FALSE); 
		break;
	case 2:
		GetDlgItem(IDC_EDIT_ARRAY_ID_GROUP)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_BLOCK_SIZE)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_VD_BLOCK_SIZE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_IP)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_WARRANT_IP)->ShowWindow(TRUE);

		GetDlgItem(IDC_STATIC_ARRAY_NAME)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_VD_SLOT)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_VD_SLOT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_INIT_TYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_INIT_TYPE)->ShowWindow(FALSE); 
		GetDlgItem(IDC_STATIC_SLOT_INFO)->ShowWindow(FALSE); 
		break;

	}
}
