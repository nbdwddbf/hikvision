// DlgGatewayCardInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGatewayCardInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGatewayCardInfo dialog


CDlgGatewayCardInfo::CDlgGatewayCardInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGatewayCardInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGatewayCardInfo)
	m_strCardNumber = _T("");
	m_nCardType = -1;
	//}}AFX_DATA_INIT
}


void CDlgGatewayCardInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGatewayCardInfo)
	DDX_Control(pDX, IDC_COMBO_CARD_TYPE, m_comboCardType);
	DDX_Text(pDX, IDC_EDIT_CARD_NUMBER, m_strCardNumber);
	DDX_CBIndex(pDX, IDC_COMBO_CARD_TYPE, m_nCardType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGatewayCardInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgGatewayCardInfo)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGatewayCardInfo message handlers

void CDlgGatewayCardInfo::OnBtnSet() 
{
	UpdateData(TRUE);
	OnOK();
}

BOOL CDlgGatewayCardInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitCtrlState();
	
	return TRUE;  
}

void CDlgGatewayCardInfo::InitCtrlState()
{
	// BYTE byCardType; //卡类型，1-普通卡，2-残疾人卡，3-黑名单卡，4-巡更卡，5-胁迫卡，6-超级卡，7-来宾卡，默认普通卡
	m_comboCardType.ResetContent();
	m_comboCardType.InsertString(0,"无效类型");
	m_comboCardType.InsertString(1,"普通卡");
	m_comboCardType.InsertString(2,"残疾人卡");
	m_comboCardType.InsertString(3,"黑名单卡");
	m_comboCardType.InsertString(4,"巡更卡");
	m_comboCardType.InsertString(5,"胁迫卡");
	m_comboCardType.InsertString(6,"超级卡");
	m_comboCardType.InsertString(7,"来宾卡");

	m_comboCardType.SetCurSel(m_nCardType);
}

void CDlgGatewayCardInfo::SetCardInfo(const GATEWAY_CARD_INFO& struCardInfo)
{
	m_strCardNumber = struCardInfo.byCardNumber;
	m_nCardType = struCardInfo.byCardType;
}

void CDlgGatewayCardInfo::GetCardInfo(GATEWAY_CARD_INFO& struCardInfo)
{
	strncpy((char*)struCardInfo.byCardNumber,m_strCardNumber,ACS_CARD_NO_LEN);
	struCardInfo.byCardType = m_nCardType;
}
