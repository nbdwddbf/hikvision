/**********************************************************
FileName:    DlgDeviceInfo.cpp
Description: device basic info  
Date:        2008/05/17
Note: 		<global>struct, define refer to GeneralDef.h, global variables and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgDeviceInfo.h"
#include ".\dlgdeviceinfo.h"


// CDlgDeviceInfo dialog
/*********************************************************
  Function:	CDlgDeviceInfo
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgDeviceInfo, CDialog)
CDlgDeviceInfo::CDlgDeviceInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceInfo::IDD, pParent)
	, m_csLocalNodeName(_T(""))
	, m_csUserName(_T(""))
	, m_csPwd(_T(""))
	, m_iPort(0)
	, m_csMultiIP(_T(""))
	, m_iChanNum(0)
	, m_csSerialNo(_T(""))
	//, m_csIPOnIPServer(_T(""))
	, m_iDeviceIndex(-1)
    , m_csDeviceClassName(_T(""))
    , m_csClassName(_T(""))
{
}

/*********************************************************
  Function:	~CDlgDeviceInfo
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgDeviceInfo::~CDlgDeviceInfo()
{
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		map between control and data
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgDeviceInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgDeviceInfo)
    DDX_Text(pDX, IDC_DEVINFO_DEVICE_NAME, m_csLocalNodeName);
    DDX_Text(pDX, IDC_DEVINFO_USERNAME, m_csUserName);
    DDX_Control(pDX, IDC_DEVINFO_IP, m_ctrlIPAddr);
    DDX_Text(pDX, IDC_DEVINFO_DEVICE_PWD, m_csPwd);
    DDX_Text(pDX, IDC_DEVINFO_PORT, m_iPort);
    DDX_Text(pDX, IDC_DEVINFO_MULTIIP, m_csMultiIP);
    DDX_Text(pDX, IDC_DEVINFO_CHANNEL_NUM, m_iChanNum);
    //DDX_Control(pDX, IDC_COMBO_DEVINFO_DEV_TYPE, m_comboDeviceType);
    DDX_Text(pDX, IDC_DEVINFO_SERIALNUM, m_csSerialNo);
    DDX_Text(pDX, IDC_EDIT_DEVICE_TYPE_NAME, m_csDeviceTypeName);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_DEVICE_CLASS_NAME, m_csDeviceClassName);
    DDX_Control(pDX, IDC_COM_LOGIN_MODE, m_cmbLoginMode);
    DDX_Control(pDX, IDC_COM_HTTPS, m_cmbHttps);
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		map between message and function
  Input:	
  Output:	
  Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgDeviceInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgDeviceInfo)
	ON_BN_CLICKED(IDC_DEVINFO_OK, OnBnClickedDevinfoOk)
	ON_BN_CLICKED(IDC_DEVINFO_CANCEL, OnBnClickedDevinfoCancel)
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()


/*********************************************************
  Function:	OnInitDialog
  Desc:		initialize dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgDeviceInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
// 	m_iTypeNum = 0;
// 	m_comboDeviceType.ResetContent();
// 	m_comboDeviceType.AddString("DVR");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("ATMDVR");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, ATMDVR);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVS");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVS);
// 	m_iTypeNum++;
//     m_comboDeviceType.AddString("DS64XXHD_T");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS64XXHD_T);
// 	m_iTypeNum++;
//     m_comboDeviceType.AddString("DEC");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DEC);
//     m_iTypeNum++;
// 	m_comboDeviceType.AddString("ENC_DEC");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, ENC_DEC);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HC");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HC);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HT");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HT);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HF");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HF);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HS");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HS);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HTS");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HTS);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HB");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HB);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HCS");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HCS);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVS_A");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVS_A);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HC_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HC_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HT_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HT_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HF_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HF_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HS_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HS_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("ATMDVR_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, ATMDVR_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("LOWCOST_DVR");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, LOWCOST_DVR);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DEC_MAT");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DEC_MAT);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_MOBILE");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_MOBILE);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HD_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HD_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HD_SL");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HD_SL);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HC_SL");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HC_SL);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVR_HS_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVR_HS_ST);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DVS_HW");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DVS_HW);
// 	m_iTypeNum++;
//     m_comboDeviceType.AddString("DS630X_D");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS630X_D);
// 	m_iTypeNum++;
//     m_comboDeviceType.AddString("DS640X_HD");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS640X_HD);
// 	m_iTypeNum++;
//     m_comboDeviceType.AddString("DS610X_D");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS610X_D);
//     m_iTypeNum++;
// 	m_comboDeviceType.AddString("IPCAM");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, IPCAM);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("MEGA_IPCAM");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, MEGA_IPCAM);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("IPCAM_X62MF");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, IPCAM_X62MF);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("ITCCAM");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, ITCCAM);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("IVS_IPCAM");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, IVS_IPCAM);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("IPDOME");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, IPDOME);
//     m_iTypeNum++;
//     //2009-9-14 added by likui begin    
//     m_comboDeviceType.AddString("IPDOME_MEGA200");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IPDOME_MEGA200);
//     m_iTypeNum++;
//     m_comboDeviceType.AddString("IPDOME_MEGA130");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IPDOME_MEGA130);
//     m_iTypeNum++;
//     //2009-9-14 added by likui end
// 	m_comboDeviceType.AddString("IPDOME_AI");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, IPDOME_AI);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("TII_IPCAM");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, TII_IPCAM);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("IPMOD");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, IPMOD);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS71XX_H");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS71XX_H);
// 	m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("IDS6101_HF_A");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS6101_HF_A);
//     m_iTypeNum++;
// 
// 	m_comboDeviceType.AddString("IDS6101_HF_B");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, IDS6101_HF_B);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("IDS6002_HF_B");//lead and follow ptz track
// 	m_comboDeviceType.SetItemData(m_iTypeNum, IDS6002_HF_B);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("IDS52XX");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, IDS52XX);
// 	m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("IDS90XX");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS90XX);
// 	m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("IDS8104_AHL_S_H");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS8104_AHL_S_H);
//     m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("IDS91XX");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS91XX);
// 	m_iTypeNum++;
// 
// 	m_comboDeviceType.AddString("DS72XX_H_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS72XX_H_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS73XX_H_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS73XX_H_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS72XX_HF_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS72XX_HF_S);
// 	m_iTypeNum++;
// 
// 	m_comboDeviceType.AddString("DS73XX_HFI_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS73XX_HFI_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS76XX_H_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS76XX_H_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS76XX_N_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS76XX_N_S);
// 	m_iTypeNum++;
// 
// 	m_comboDeviceType.AddString("DS81XX_HS_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_HS_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS81XX_HL_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_HL_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS81XX_HC_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_HC_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS81XX_HD_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_HD_S);
// 	m_iTypeNum++;
// 	
// 	m_comboDeviceType.AddString("DS81XX_HE_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_HE_S);
// 	m_iTypeNum++;
// 
// 
// 	m_comboDeviceType.AddString("DS81XX_HF_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_HF_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS81XX_AH_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_AH_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS81XX_AHF_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_AHF_S);
// 	m_iTypeNum++;
//     
//     m_comboDeviceType.AddString("DS90XX_HF_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS90XX_HF_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS91XX_HF_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS91XX_HF_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS91XX_HD_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS91XX_HD_S);
// 	m_iTypeNum++;
//     m_comboDeviceType.AddString("IDS90XX_A");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS90XX_A);
//     m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("IDS91XX_A");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS91XX_A);
//     m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("DS95XX_N_S");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS95XX_N_S);
// 	m_iTypeNum++;
//     
//     m_comboDeviceType.AddString("DS96XX_N_SH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS96XX_N_SH);
// 	m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("DS90XX_HF_SH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS90XX_HF_SH);
//     m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("DS91XX_HF_SH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS91XX_HF_SH);
//     m_iTypeNum++;
// 
//     //2009-10-15 added by likui begin
//     m_comboDeviceType.AddString("DS_B10_XY");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS_B10_XY);
//     m_iTypeNum++;
//     m_comboDeviceType.AddString("DS_6504HF_B10");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS_6504HF_B10);
//     m_iTypeNum++;
//     m_comboDeviceType.AddString("DS_6504D_B10");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS_6504D_B10);
//     m_iTypeNum++;
// 	//65XX DVS
// 	m_comboDeviceType.AddString("DS_65XXHC");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_65XXHC);
// 	m_iTypeNum++;
// 	
// 	m_comboDeviceType.AddString("DS_65XXHC_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_65XXHC_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS_65XXHF");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_65XXHF);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS_65XXHF_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_65XXHF_S);
// 	m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("IVMS_6200(/C)");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IVMS_6200_C);
//     m_iTypeNum++;
//     
//     m_comboDeviceType.AddString("IVMS_6200(/B)");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IVMS_6200_B);
//     m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("IVMS_6200(/T)");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IVMS_6200_T);
//     m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("IVMS_6200(/BP)");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IVMS_6200_BP);
//     m_iTypeNum++;
// 
// 	m_comboDeviceType.AddString("DS_72XXHV_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_72XXHV_ST15);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS_81XXHC_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_81XXHC_ST);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS_81XXHS_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_81XXHS_ST);
// 	m_iTypeNum++;	
// 	m_comboDeviceType.AddString("DS_81XXAH_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_81XXAH_ST);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS_81XXAHF_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_81XXAHF_ST);
// 	m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("DS_19DXX");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS_19DXX);
//     m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("DS_19XX");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS_19XX);
//     m_iTypeNum++;
// 
// 	m_comboDeviceType.AddString("DS96xxN_ST");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS96xxN_ST);
//     m_iTypeNum++;	
// 	m_comboDeviceType.AddString("DS86xxN_ST");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS86xxN_ST);
//     m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS80xxHF_ST");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS80xxHF_ST);
//     m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS90xxHF_ST");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS90xxHF_ST);
//     m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS76xxN_ST");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS76xxN_ST);
//     m_iTypeNum++;
// 
//     m_comboDeviceType.AddString("ENCODER_SERVER");
//     m_comboDeviceType.SetItemData(m_iTypeNum, ENCODER_SERVER);
//     m_iTypeNum++;
//     m_comboDeviceType.AddString("DECODER_SERVER");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DECODER_SERVER);
//     m_iTypeNum++;
//     m_comboDeviceType.AddString("PCNVR_SERVER");
//     m_comboDeviceType.SetItemData(m_iTypeNum, PCNVR_SERVER);
//     m_iTypeNum++;
// 
// 	m_comboDeviceType.AddString("CVR_SERVER");
//     m_comboDeviceType.SetItemData(m_iTypeNum, CVR_SERVER);
//     m_iTypeNum++;
//     
//     m_comboDeviceType.AddString("IDS_8104_AHFL_S_H");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS_8104_AHFL_S_H);
//     m_iTypeNum++;
//     
//     m_comboDeviceType.AddString("IDS_65XX_HF_A");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS_65XX_HF_A);
//     m_iTypeNum++;
// #ifdef DEMO_LAN_CN
//     m_comboDeviceType.AddString("IDS90XX_HF_RH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS90XX_HF_RH);
//     m_iTypeNum++;
// #else
//     m_comboDeviceType.AddString("IDS90XX_HFI_RH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS90XX_HFI_RH);
//     m_iTypeNum++;
// #endif
// 
// #ifdef DEMO_LAN_CN
//     m_comboDeviceType.AddString("IDS91XX_HF_RH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS91XX_HF_RH);
//     m_iTypeNum++;
// #else
//     m_comboDeviceType.AddString("IDS91XX_HFI_RH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS91XX_HFI_RH);
//     m_iTypeNum++;
// #endif
// 
//     m_comboDeviceType.AddString("IDS_65XX_HF_B");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS_65XX_HF_B);
//     m_iTypeNum++;
//     m_comboDeviceType.AddString("IDS_65XX_HF_P");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IDS_65XX_HF_P);
//     m_iTypeNum++;
// 
// 	m_comboDeviceType.AddString("IVMS_6200_F");
//     m_comboDeviceType.SetItemData(m_iTypeNum, IVMS_6200_F);
//     m_iTypeNum++;
// 
// #ifdef DEMO_LAN_CN
//     m_comboDeviceType.AddString("DS90XX_HF_RH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS90XX_HF_RH);
//     m_iTypeNum++;
// #else
//     m_comboDeviceType.AddString("DS90XX_HF_RH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS90XX_HF_RH);
//     m_iTypeNum++;
// #endif
// 
// #ifdef DEMO_LAN_CN
//     m_comboDeviceType.AddString("DS91XX_HF_RH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS91XX_HF_RH);
//     m_iTypeNum++;
// #else
//     m_comboDeviceType.AddString("DS91XX_HF_RH");
//     m_comboDeviceType.SetItemData(m_iTypeNum, DS91XX_HF_RH);
//     m_iTypeNum++;
// #endif
// 	m_comboDeviceType.AddString("DS_66XXDVS");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_66XXDVS);
// 	m_iTypeNum++;
// 	//2011-03-29
// #ifdef DEMO_LAN_CN
// 	m_comboDeviceType.AddString("DS78XX_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS78XX_S);
// 	m_iTypeNum++;
// #else
// 	m_comboDeviceType.AddString("DS72XXHVI_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS72XXHVI_S);
// 	m_iTypeNum++;
// #endif
// 	m_comboDeviceType.AddString("DS81XXHW_S");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XXHW_S);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS81XXHW_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XXHW_ST);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS91XXHW_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS91XXHW_ST);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS91XX_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS91XX_ST);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS81XX_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_ST);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS81XXHX_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XXHX_ST);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS73XXHX_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS73XXHX_ST);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS81XX_SH");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_SH);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS81XX_SN");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS81XX_SN);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS_91XXHFH_ST");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_91XXHFH_ST);
// 	m_iTypeNum++;
// 	m_comboDeviceType.AddString("DS_66XXHFH");
// 	m_comboDeviceType.SetItemData(m_iTypeNum, DS_66XXHFH);
// 	m_iTypeNum++;

	if (g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum == -1)
	{
		m_iChanNum= 16;
		m_iPort = 8000;
		//m_comboDeviceType.SetCurSel(0);
	}
	else
	{

        char	chLoginUserName[NAME_LEN + 1] = {0};

        memcpy(chLoginUserName, g_struDeviceInfo[m_iDeviceIndex].chLoginUserName, NAME_LEN);
		m_csLocalNodeName.Format("%s",g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName);
		m_csUserName.Format("%s",chLoginUserName);
		m_csPwd.Format("%s",g_struDeviceInfo[m_iDeviceIndex].chLoginPwd);
		m_iChanNum = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
		m_ctrlIPAddr.SetAddress(CStringTodwIP(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP));
		m_csMultiIP.Format(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP);
		m_iPort = g_struDeviceInfo[m_iDeviceIndex].lDevicePort;
		//2011-12-29
		m_csDeviceTypeName.Format("%s",g_struDeviceInfo[m_iDeviceIndex].chDeviceName);
// 		for (int i=0; i<m_iTypeNum; i++)
// 		{
// 			if (m_comboDeviceType.GetItemData(i) == (unsigned)g_struDeviceInfo[m_iDeviceIndex].iDeviceType)
// 			{
// 				m_iSelType = i;
// 				break;
// 			}
// 		}
// 		m_comboDeviceType.SetCurSel(m_iSelType);
        m_csDeviceClassName.Format("%s", g_struDeviceInfo[m_iDeviceIndex].chDeviceClassName);
		m_csSerialNo.Format("%s", g_struDeviceInfo[m_iDeviceIndex].chSerialNumber);

        m_cmbLoginMode.SetCurSel(g_struDeviceInfo[m_iDeviceIndex].byLoginMode);
        m_cmbHttps.SetCurSel(g_struDeviceInfo[m_iDeviceIndex].byHttps);

	}
	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
  Function:	OnBnClickedDevinfoOk
  Desc:		finish modifying device info and exit
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgDeviceInfo::OnBnClickedDevinfoOk()
{
	UpdateData(TRUE);
	DWORD dwDeviceIP = 0;
	m_ctrlIPAddr.GetAddress(dwDeviceIP);
	CString csIP = IPToStr(dwDeviceIP);
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP, "%s", csIP.GetBuffer(0));
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName, "%s", m_csLocalNodeName.GetBuffer(0));
	g_struDeviceInfo[m_iDeviceIndex].lDevicePort = m_iPort;
	memcpy(g_struDeviceInfo[m_iDeviceIndex].chLoginPwd, m_csPwd, PASSWD_LEN);
	memcpy(g_struDeviceInfo[m_iDeviceIndex].chLoginUserName, m_csUserName, NAME_LEN);

    g_struDeviceInfo[m_iDeviceIndex].byLoginMode = m_cmbLoginMode.GetCurSel();
    g_struDeviceInfo[m_iDeviceIndex].byHttps = m_cmbHttps.GetCurSel();
	
//update node name in main dialog
	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedDevinfoCancel
  Desc:		exit device info box
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgDeviceInfo::OnBnClickedDevinfoCancel()
{
	CDialog::OnCancel();
}
