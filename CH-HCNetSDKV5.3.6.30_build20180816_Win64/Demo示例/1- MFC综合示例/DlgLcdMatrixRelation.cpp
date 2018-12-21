// DlgLcdMatrixRelation.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLcdMatrixRelation.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdMatrixRelation dialog


CDlgLcdMatrixRelation::CDlgLcdMatrixRelation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLcdMatrixRelation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLcdMatrixRelation)
	m_dwMatrixOutput = 0;
	//}}AFX_DATA_INIT
}


void CDlgLcdMatrixRelation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLcdMatrixRelation)
	DDX_Control(pDX, IDC_LIST_MATRIX_RELATION, m_listRelation);
	DDX_Text(pDX, IDC_EDIT_MATRIX_OUTPUT, m_dwMatrixOutput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLcdMatrixRelation, CDialog)
	//{{AFX_MSG_MAP(CDlgLcdMatrixRelation)
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MATRIX_RELATION, OnClickListMatrixRelation)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdMatrixRelation message handlers

BOOL CDlgLcdMatrixRelation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    char szLan[64] = {0};

    m_listRelation.SetExtendedStyle(m_listRelation.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    g_StringLanType(szLan, "屏幕索引号", "Screen index");
    m_listRelation.InsertColumn(0, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "矩阵输出号", "Matrix output no");
    m_listRelation.InsertColumn(1, szLan, LVCFMT_LEFT, 120, -1);

	DrawList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLcdMatrixRelation::OnBtnModify() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CString cs;
    char szLan[64] = {0};

    if (m_iCurSel == -1)
    {
        g_StringLanType(szLan, "未选中条目", "Please select an item");
        return;
    }

    m_lpMatrixInfo->wMatrixOutputChanRef[m_iCurSel] = m_dwMatrixOutput;
    cs.Format("%d", m_dwMatrixOutput);
    m_listRelation.SetItemText(m_iCurSel, 1, cs);

    UpdateData(FALSE);
}

void CDlgLcdMatrixRelation::OnClickListMatrixRelation(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    POSITION  iPos = m_listRelation.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }

    m_iCurSel = m_listRelation.GetNextSelectedItem(iPos);
    m_dwMatrixOutput = m_lpMatrixInfo->wMatrixOutputChanRef[m_iCurSel];
    UpdateData(FALSE);
    
	*pResult = 0;
}

void CDlgLcdMatrixRelation::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}

void CDlgLcdMatrixRelation::DrawList()
{
    int i = 0;
    CString cs;

    for (i = 0; i < 100; i++)
    {
        cs.Format("%d", i+1);
        m_listRelation.InsertItem(i, cs, 0);
        cs.Format("%d", m_lpMatrixInfo->wMatrixOutputChanRef[i]);
        m_listRelation.SetItemText(i, 1, cs);
    }

    UpdateData(FALSE);
}
