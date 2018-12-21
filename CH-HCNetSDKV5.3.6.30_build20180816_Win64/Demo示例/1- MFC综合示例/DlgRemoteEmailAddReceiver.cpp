/**********************************************************
FileName:    DlgRemoteEmailAddReceiver.cpp
Description: add Email Recerver's handling
Date:        2008/05/29
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/29>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRemoteEmailAddReceiver.h"
#include ".\dlgremoteemailaddreceiver.h"


// CDlgRemoteEmailAddReceiver dialog
/*********************************************************
  Function:	CheckCharLegal
  Desc:		Check email string
  Input:	front,last checking status;ch,验证字符;
  Output:	
  Return:	TRUE/FALSE
**********************************************************/
BOOL CheckCharLegal(BOOL front,TCHAR ch)
{
	if (ch<='z'&&ch>='a' || ch<='Z'&&ch>='A' || ch<='9'&&ch>='0' || ch =='.')
	{
		return TRUE;
	}
	if (front && (ch == '-' || ch =='_'))
	{
		return TRUE;
	}
	return FALSE;
}

/*********************************************************
  Function:	CheckEmailAddress
  Desc:		check email address validation
  Input:	csEmailAddr,email addr;
  Output:	
  Return:	TRUE/FALSE
**********************************************************/
BOOL CheckEmailAddress(CString csEmailAddr)
{
	int iPos = csEmailAddr.Find('@');
	if (iPos == -1 || iPos == 0 || iPos == (csEmailAddr.GetLength()-1))
	{
		return FALSE;
	}
	CString csTmp = csEmailAddr.Left(iPos);
	int i;
	for (i=0;i<iPos;i++)
	{
		if (!CheckCharLegal(TRUE,csTmp.GetAt(i)))
		{
			return FALSE;
		}
	}
	csTmp.Empty();
	csTmp = csEmailAddr.Right(csEmailAddr.GetLength()-1-iPos);
	iPos = csTmp.Find('.');
	if (iPos == -1 || iPos == 0 || iPos == (csTmp.GetLength()-1))
	{
		return FALSE;
	}
	for (i=0;i<csTmp.GetLength();i++)
	{
		if (!CheckCharLegal(FALSE,csTmp.GetAt(i)))
		{
			return FALSE;
		}
	}
	return TRUE;
}

/*********************************************************
Function:	CDlgRemoteEmailAddReceiver
Desc:		Constructor
Input:	
Output:	
Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteEmailAddReceiver, CDialog)
CDlgRemoteEmailAddReceiver::CDlgRemoteEmailAddReceiver(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteEmailAddReceiver::IDD, pParent)
	, m_csReceiverName(_T(""))
	, m_csReceiverAddr(_T(""))
{
}

/*********************************************************
Function:	~CDlgRemoteEmailAddReceiver
Desc:		destructor
Input:	
Output:	
Return:	
**********************************************************/
CDlgRemoteEmailAddReceiver::~CDlgRemoteEmailAddReceiver()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteEmailAddReceiver::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteEmailAddReceiver)
	DDX_Text(pDX, IDC_EDIT_EMAIL_RECERVER_NAME, m_csReceiverName);
	DDX_Text(pDX, IDC_EDIT_EMAIL_RECEIVER_ADDR, m_csReceiverAddr);
    //}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteEmailAddReceiver, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteEmailAddReceiver)	
	ON_BN_CLICKED(IDC_BTN_EMAIL_RECEIVER_OK, OnBnClickedBtnEmailReceiverOk)
	ON_BN_CLICKED(IDC_BTN_EMAIL_RECEIVER_EXIT, OnBnClickedBtnEmailReceiverExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgRemoteEmailAddReceiver message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteEmailAddReceiver::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
}

/*********************************************************
Function:	OnBnClickedBtnEmailReceiverOk
Desc:		complete receiver info
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteEmailAddReceiver::OnBnClickedBtnEmailReceiverOk()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
			
	if (m_csReceiverName.IsEmpty())
	{
		g_StringLanType(szLan, "姓名不能为空", "Name should not be empty");
		AfxMessageBox(szLan);
		return;

	}
	if (!CheckEmailAddress(m_csReceiverAddr))
	{
		g_StringLanType(szLan, "Email地址非法!", "Email address illegal!");
		AfxMessageBox(szLan);
		return;
	}

	CDialog::OnOK();
}

/*********************************************************
Function:	OnBnClickedBtnEmailReceiverExit
Desc:		exit settings
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteEmailAddReceiver::OnBnClickedBtnEmailReceiverExit()
{
	CDialog::OnCancel();
}
