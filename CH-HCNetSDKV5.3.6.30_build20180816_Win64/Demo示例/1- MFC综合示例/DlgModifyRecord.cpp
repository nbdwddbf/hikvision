// DlgModifyRecord.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgModifyRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgModifyRecord dialog


CDlgModifyRecord::CDlgModifyRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgModifyRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgModifyRecord)
	m_dwOutputNum = 0;
	//}}AFX_DATA_INIT
	m_iCurSel = -1; 
}


void CDlgModifyRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgModifyRecord)
	DDX_Control(pDX, IDC_LIST_SCREEN_MODIFY, m_lstScreenM);
	DDX_Control(pDX, IDC_LIST_SCREEN, m_lstScreen);
	DDX_Text(pDX, IDC_EDT_VIDEOWALL_OUTPUTNUM, m_dwOutputNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgModifyRecord, CDialog)
	//{{AFX_MSG_MAP(CDlgModifyRecord)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL_MODIFY, OnBtnDelModify)
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
	ON_BN_CLICKED(IDC_BTN_UPDATEMODIFY, OnBtnUpdatemodify)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SCREEN, OnClickListScreen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgModifyRecord message handlers

BOOL CDlgModifyRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_DispPosBM.Init(m_struWallParam, sizeof(m_struWallParam), sizeof(m_struWallParam[0]) );

	char szLan[128] = {0}; 
	m_lstScreen.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT);
	g_StringLanType(szLan, "序号", "DispChan No.");
	m_lstScreen.InsertColumn(0, szLan, LVCFMT_LEFT,30, -1);	
    g_StringLanType(szLan, "显示输出号", "DispChan No.");
	m_lstScreen.InsertColumn(1, szLan, LVCFMT_LEFT,40, -1);	

	m_lstScreenM.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT);
	g_StringLanType(szLan, "序号", "DispChan No.");
	m_lstScreenM.InsertColumn(0, szLan, LVCFMT_LEFT,30, -1);	
    g_StringLanType(szLan, "显示输出号", "DispChan No.");
	m_lstScreenM.InsertColumn(1, szLan, LVCFMT_LEFT,40, -1);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//实现比较函数
bool DispNoCmp (const void *ItemF, const void *ItemS)
{
	const NET_DVR_VIDEOWALLDISPLAYPOSITION * CfgItemF = (const NET_DVR_VIDEOWALLDISPLAYPOSITION *) ItemF; 
	const NET_DVR_VIDEOWALLDISPLAYPOSITION * CfgItemS = (const NET_DVR_VIDEOWALLDISPLAYPOSITION *) ItemS; 
	return (CfgItemF->dwDisplayNo == CfgItemS->dwDisplayNo);
}


void CDlgModifyRecord::DrawList()
{
	 m_lstScreen.DeleteAllItems();
	 char szLan[128] = {0}; 
	 int iIndex = 0 ; 
	 for (int i=0; i<m_DispPosBM.GetUsedNum(); i++)
	 {
		sprintf(szLan, "%d", i); 
		iIndex = m_lstScreen.InsertItem(i, szLan);
		sprintf(szLan, "%d", m_struWallParam[i].dwDisplayNo); 
		m_lstScreen.SetItemText(iIndex, 1, szLan);
	 }
	 UpdateData(FALSE); 
}

void CDlgModifyRecord::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_VIDEOWALLDISPLAYPOSITION struPos = {0}; 
	struPos.dwDisplayNo = m_dwOutputNum; 
	m_DispPosBM.Add(&struPos, DispNoCmp); 
	DrawList(); 
}

void CDlgModifyRecord::OnBtnDelModify() 
{
	// TODO: Add your control notification handler code here
	m_DispPosBM.Clear(); 
}

void CDlgModifyRecord::OnBtnModify() 
{
	// TODO: Add your control notification handler code here

	if (m_iCurSel == -1 || m_iCurSel > m_DispPosBM.GetUsedNum() )
	{
		return;
	}
	UpdateData(TRUE); 
	NET_DVR_VIDEOWALLDISPLAYPOSITION struPos = {0}; 
	struPos.dwDisplayNo = m_dwOutputNum; 
	m_DispPosBM.Modify(&struPos, m_iCurSel); 
	DrawList(); 
}

void CDlgModifyRecord::OnBtnUpdatemodify() 
{
	// TODO: Add your control notification handler code here
	LPNET_DVR_VIDEOWALLDISPLAYPOSITION lpDisplayPos = NULL; 
	//获取修改的内容 和个数 
	DWORD dwChangeNum = m_DispPosBM.GetMod((void **)&lpDisplayPos);
	m_lstScreenM.DeleteAllItems(); 
	char szLan[128] = {0}; 
	int iIndex = 0 ; 
	for (int i=0; i< dwChangeNum; i++)
	{
		sprintf(szLan, "%d", i); 
		iIndex = m_lstScreenM.InsertItem(i, szLan);
		sprintf(szLan, "%d", lpDisplayPos[i].dwDisplayNo); 
		m_lstScreenM.SetItemText(iIndex, 1, szLan);
		
	}
	UpdateData(FALSE); 
}

void CDlgModifyRecord::OnClickListScreen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION  iPos = m_lstScreen.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
 	m_iCurSel = m_lstScreen.GetNextSelectedItem(iPos);
	if (m_iCurSel == -1 || m_iCurSel > m_DispPosBM.GetUsedNum() )
	{
		return;
	}
	m_dwOutputNum = m_struWallParam[m_iCurSel].dwDisplayNo; 
	UpdateData(FALSE); 
	*pResult = 0;
}
