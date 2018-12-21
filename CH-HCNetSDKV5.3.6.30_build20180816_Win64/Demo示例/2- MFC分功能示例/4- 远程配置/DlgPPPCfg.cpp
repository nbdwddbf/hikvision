/**********************************************************
FileName:    DlgPPPCfg.cpp
Description: ≤¶∫≈≈‰÷√      
Date:        
Note: 		
Modification History:      
<version>    <time>         <desc>

***********************************************************/

#include "stdafx.h"
#include "config.h"
#include "DlgPPPCfg.h"


/*********************************************************
  Function:	CDlgPPPCfg
  Desc:		constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgPPPCfg, CDialog)
CDlgPPPCfg::CDlgPPPCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPPPCfg::IDD, pParent)
	, m_csUserName(_T(""))
	, m_csPwd(_T(""))
	, m_csRemoteIP(_T(""))
	, m_csLocalIP(_T(""))
	, m_csVerifyPwd(_T(""))
	, m_csIPMask(_T(""))
	, m_csTelNum(_T(""))
	, m_bChkDataEncrypt(FALSE)
	, m_bChkRedial(FALSE)
{
}

/*********************************************************
  Function:	~CDlgPPPCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgPPPCfg::~CDlgPPPCfg()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPPPCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPPPCfg)
	DDX_Control(pDX, IDC_COMBO_PPP_MODE, m_comboPPPMode);
	DDX_Control(pDX, IDC_COMBO_REDIAL_MODE, m_comboRedialMode);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_csPwd);
	DDX_Text(pDX, IDC_EDIT_REMOTEIP, m_csRemoteIP);
	DDX_Text(pDX, IDC_EDIT_LOCALIP, m_csLocalIP);
	DDX_Text(pDX, IDC_EDIT_VERIFY_PWD, m_csVerifyPwd);
	DDX_Text(pDX, IDC_EDIT_IPMASK, m_csIPMask);
	DDX_Text(pDX, IDC_EDIT_TEL_NUM, m_csTelNum);
	DDX_Check(pDX, IDC_CHK_DATA_ENCRYPT, m_bChkDataEncrypt);
	DDX_Check(pDX, IDC_CHK_REDIAL, m_bChkRedial);
    //}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgPPPCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgPPPCfg)	
	ON_BN_CLICKED(IDC_BTN_SETUP, OnBnClickedBtnSetup)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBnClickedBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgPPPCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	char cTemp[100] = {0};

	m_comboPPPMode.SetCurSel(m_struPPPConfig.byPPPMode);
	m_comboRedialMode.SetCurSel(m_struPPPConfig.byRedialMode);
	m_bChkRedial = m_struPPPConfig.byRedial;
	m_bChkDataEncrypt = m_struPPPConfig.byDataEncrypt;
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struPPPConfig.sUsername, NAME_LEN);
	m_csUserName.Format("%s", cTemp);
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struPPPConfig.sPassword, PASSWD_LEN);
	m_csPwd.Format("%s", cTemp);
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struPPPConfig.sPassword, PASSWD_LEN);
	m_csVerifyPwd.Format("%s", cTemp);


	m_csRemoteIP = m_struPPPConfig.struRemoteIP.sIpV4;
	m_csLocalIP = m_struPPPConfig.struLocalIP.sIpV4;
	m_csIPMask = m_struPPPConfig.sLocalIPMask;//struLocalIPMask.sIpV4
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struPPPConfig.sTelephoneNumber, PHONENUMBER_LEN);
	m_csTelNum.Format("%s", cTemp);


	UpdateData(FALSE);
	return TRUE;  
}

/*********************************************************
  Function:	OnBnClickedBtnSetup
  Desc:		…Ë÷√PPP≈‰÷√
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPPPCfg::OnBnClickedBtnSetup()
{
	UpdateData(TRUE);
	if (m_csVerifyPwd != m_csPwd)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "√‹¬Î–£—È≤ª’˝»∑£°", "Verify Password incorrect!");
		AfxMessageBox(szLan);
		return ;
	}
	m_struPPPConfig.byPPPMode = m_comboPPPMode.GetCurSel();
	m_struPPPConfig.byRedialMode = m_comboRedialMode.GetCurSel();
	m_struPPPConfig.byRedial = (BYTE)m_bChkRedial;
	m_struPPPConfig.byDataEncrypt = (BYTE)m_bChkDataEncrypt;
	memcpy(m_struPPPConfig.sUsername,m_csUserName,NAME_LEN);
	memcpy(m_struPPPConfig.sPassword, m_csPwd, PASSWD_LEN);
	memcpy(m_struPPPConfig.struRemoteIP.sIpV4, m_csRemoteIP, 16);
	memcpy(m_struPPPConfig.struLocalIP.sIpV4, m_csLocalIP, 16);
	memcpy(m_struPPPConfig.sLocalIPMask, m_csIPMask, 16);//struLocalIPMask.sIpV4
	memcpy(m_struPPPConfig.sTelephoneNumber, m_csTelNum, PHONENUMBER_LEN);
	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedBtnExit
  Desc:		ÕÀ≥ˆPPP≤¶∫≈≈‰÷√
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPPPCfg::OnBnClickedBtnExit()
{
	CDialog::OnCancel();
}
