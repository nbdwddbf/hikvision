// DlgProductVcaCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgProductVcaCfg.h"
#include "DlgVcaChanCtrlCfg.h"
#include "DlgPUStream.h"
#include "DlgVcaDrawMode.h"
#include "DlgVcaIvmsCfg.h"
#include "DlgVcaBehaviorCfg.h"
#include "DlgVcaPositionRule.h"
#include "DlgVcaITSCfg.h"
#include "DlgPdcRuleCfg.h"
#include "DlgVcaSceneTrafficCfg.h"
#include "DlgVcaFace.h"
#include "DlgVcaParamkey.h"
#include "DlgVcaFunCfg.h"
#include "DlgDiagnosticServer.h"
#include "DlgVcaBVCalibrate.h"
#include "DlgBvCalibParamCfg.h"
#include "DlgVcaResetCounterCfg.h"
#include "DlgVCARuleColorCfg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProductVcaCfg dialog


CDlgProductVcaCfg::CDlgProductVcaCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProductVcaCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProductVcaCfg)
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_lChannel = -1;
	m_iDevIndex = -1;
}


void CDlgProductVcaCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProductVcaCfg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProductVcaCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgProductVcaCfg)
	ON_BN_CLICKED(IDC_BTN_VCACHAN_CTRL, OnBtnVcachanCtrl)
	ON_BN_CLICKED(IDC_BTN_PUSTREAM, OnBtnPustream)
	ON_BN_CLICKED(IDC_BTN_RESTART_VCALIB, OnBtnRestartVcalib)
	ON_BN_CLICKED(IDC_BTN_VCA_DRAW_MODE, OnBtnVcaDrawMode)
	ON_BN_CLICKED(IDC_BTN_VCARULE, OnBtnVcarule)
	ON_BN_CLICKED(IDC_BTN_KEYPARAM, OnBtnKeyparam)
	ON_BN_CLICKED(IDC_BTN_VCA_VERSION, OnBtnVcaVersion)
	ON_BN_CLICKED(IDC_BTN_VCA_FUN, OnBtnVcaFun)
	ON_BN_CLICKED(IDC_BTN_DIAGNOISTIC_SERVER, OnBtnDiagnoisticServer)
	ON_BN_CLICKED(IDC_BTN_POSITION_RULE, OnBtnPositionRule)
	ON_BN_CLICKED(IDC_BTN_BV_CALIB_CFG, OnBtnBvCalibCfg)
	ON_BN_CLICKED(IDC_BTN_BV_CORRECT_PARAM, OnBtnBvCorrectParam)
	ON_BN_CLICKED(IDC_BTN_VCA_DECODECFG, OnBtnVcaDecodecfg)
	ON_BN_CLICKED(IDC_BTN_RULE_COLOR_CFG, OnBtnRuleColorCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProductVcaCfg message handlers


BOOL CDlgProductVcaCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_dlgVcaDevAbility.m_lServerID = m_lUserID;
    m_dlgVcaDevAbility.m_iDevIndex = m_iDevIndex;
	m_dlgVcaDevAbility.Create(CDlgVcaDevAbility::IDD,this);

	ArrangeWndLayout();
	ShowChildWnd();
	
	return TRUE;
}

void CDlgProductVcaCfg::ArrangeWndLayout()
{   
	int nBtnRegionHeight = 180;
    
	CRect rcClient;
	GetClientRect(rcClient);

	CRect rcChildRgn = rcClient;
	rcChildRgn.DeflateRect(0,0,0,nBtnRegionHeight);

	GetDlgItem(IDC_CHILDRGN)->MoveWindow(rcChildRgn);
	m_dlgVcaDevAbility.MoveWindow(rcChildRgn);
}

void CDlgProductVcaCfg::ShowChildWnd()
{   
	BOOL bBtnEnable = (m_lChannel > 0) ? TRUE : FALSE;
    GetDlgItem(IDC_BTN_VCACHAN_CTRL)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_PUSTREAM)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_RESTART_VCALIB)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_VCA_DRAW_MODE)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_KEYPARAM)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_VCARULE)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_VCA_VERSION)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_VCA_FUN)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_DIAGNOISTIC_SERVER)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_POSITION_RULE)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_BV_CALIB_CFG)->EnableWindow(bBtnEnable);
	GetDlgItem(IDC_BTN_BV_CORRECT_PARAM)->EnableWindow(bBtnEnable);
}

void CDlgProductVcaCfg::OnBtnVcachanCtrl() 
{
	CDlgVcaChanCtrlCfg dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_iVcaChannel = m_lChannel;
	dlg.m_iChannelNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
    dlg.DoModal();
}

void CDlgProductVcaCfg::OnBtnPustream() 
{
	CDlgPUStream dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lServerID = m_lUserID;
    dlg.DoModal();
}

void CDlgProductVcaCfg::OnBtnRestartVcalib() 
{
	char szLan[128] = {0};
    if (!NET_VCA_RestartLib(m_lUserID, m_lChannel))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_RestartLib %d", m_lChannel);
        char sBufCn[128] =  {0};
        char sBufEn[128] = {0};
        sprintf(sBufCn, "智能通道%d智能库重启失败", m_lChannel);
        sprintf(sBufEn, "VcaChannel%d failed to restart VCA library", m_lChannel);
        g_StringLanType(szLan, sBufCn, sBufEn);
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_RestartLib %d", m_lChannel);
    }	
}

void CDlgProductVcaCfg::OnBtnVcaVersion() 
{
    NET_DVR_VCA_VERSION struVcaVersion = {0};
    if (!NET_DVR_GetVCAVersion(m_lUserID, m_lChannel, &struVcaVersion))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetVCAVersion");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetVCAVersion");
        char szLan[128] = {0};
        sprintf(szLan, "VCA Version: %d.%d.%d build%d%0.2d%0.2d. Type:%d", struVcaVersion.wMajorVersion, struVcaVersion.wMinorVersion,
            struVcaVersion.wRevisionNumber, struVcaVersion.wVersionYear,
            struVcaVersion.byVersionMonth, struVcaVersion.byVersionDay, struVcaVersion.byType);
        MessageBox(szLan, "About");
    }
}

void CDlgProductVcaCfg::OnBtnVcaDrawMode() 
{
	CDlgVcaDrawMode dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lServerID = m_lUserID;
    dlg.DoModal();
}

void CDlgProductVcaCfg::OnBtnVcarule() 
{
	 char szLan[128] = {0};
	NET_VCA_DEV_ABILITY struVcaDevAbility = {0};
	
	BOOL bSupportChanEx = FALSE;
    memset(&struVcaDevAbility, 0, sizeof(NET_VCA_DEV_ABILITY));
    if(!NET_DVR_GetDeviceAbility(m_lUserID,  VCA_DEV_ABILITY, NULL, 0, (char*)&struVcaDevAbility, sizeof(NET_VCA_DEV_ABILITY)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_DEV_ABILITY");
    }
    else 
    {   
		bSupportChanEx = (struVcaDevAbility.bySupport & 0x02) ? TRUE : FALSE;
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "VCA_DEV_ABILITY");
    }
	

	int iVCAType = 0;
	BYTE byVcaChanMode = 0;
	
	if (bSupportChanEx)
	{
		DWORD dwStatus = 0;
		NET_DVR_VCA_CTRLINFO_COND struCond = {0};
		NET_DVR_VCA_CTRLINFO_CFG struVcaCtrlInfo = {0};
		struCond.dwSize = sizeof(struCond);
		struCond.struStreamInfo.dwChannel = m_lChannel;
		BOOL bRet = NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_VCA_CTRLINFO_CFG, 1, &struCond,sizeof(struCond),&dwStatus, &struVcaCtrlInfo, sizeof(struVcaCtrlInfo));
		
		if (!(bRet && (0 == dwStatus)))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_CTRLINFO_CFG");            
			bRet = FALSE;
		}
		else
		{
			iVCAType = struVcaCtrlInfo.byVCAType;
			byVcaChanMode = struVcaCtrlInfo.byMode;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_CTRLINFO_CFG");            
		}
		
	}
	else
	{   
		DWORD dwReturned = 0;
        NET_VCA_CTRLCFG struVcaCtrlCfg = {0};
		if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VCA_CTRLCFG, 0, &struVcaCtrlCfg, sizeof(NET_VCA_CTRLCFG), &dwReturned))	
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_CTRLCFG");
		}
		else
		{
			iVCAType = struVcaCtrlCfg.struCtrlInfo[m_lChannel - 1].byVCAType;
			byVcaChanMode = struVcaCtrlCfg.struCtrlInfo[m_lChannel - 1].byMode;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_CTRLCFG");
		}
	}

    switch (g_struDeviceInfo[m_iDevIndex].iDeviceType)
	{
	case TRAFFIC_VAR:
		{
			CDlgVcaSceneTrafficCfg dlg;
			dlg.m_lServerID = m_lUserID;
			dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;	
			dlg.m_iDevIndex = m_iDevIndex;
			dlg.m_iChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
			dlg.m_iVcaChannel = m_lChannel;
			dlg.DoModal();
			break;
		}
	case IDS52XX:
		{
            CDlgVcaIvmsCfg  dlg;
            dlg.m_lServerID = m_lUserID;
            dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;	
            dlg.m_iDevIndex = m_iDevIndex;
            dlg.m_iChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
			dlg.DoModal();
		}
		break;
    case IDS8104_AHL_S_H:   // 81ATM
    case IDS6101_HF_A:
	case IDS6002_HF_B:
	case IDS6101_HF_B:
    case IDS90XX:
    case IDS91XX:
    case IVMS_6200_BP:
        {
            CDlgVcaBehaviorCfg dlg;
            dlg.m_lServerID = m_lUserID;
            dlg.m_iDevIndex = m_iDevIndex;
            dlg.m_iChannelNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
			dlg.m_iVcaChannel = m_lChannel;
			dlg.m_byVcaType = iVCAType;
			dlg.m_byVcaChanMode = byVcaChanMode;
            dlg.DoModal();
        }
        break;
    case IPDOME:  
    case IPDOME_MEGA200:
    case IPDOME_MEGA130:
	case IPDOME_AI: 
        {   
			CDlgVcaFace dlg;
			dlg.m_lServerID = m_lUserID;
			dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;	
			dlg.m_iDevIndex = m_iDevIndex;
			dlg.m_iChannelNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
			dlg.m_iVcaChannel = m_lChannel;
			dlg.DoModal();

//             CDlgVcaPositionRule dlg;
//             dlg.m_lServerID = m_lUserID;
//             dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;	
//             dlg.m_iDevIndex = m_iDevIndex;
//             dlg.m_iChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
//             dlg.DoModal();
        }
        break;
	case ITCCAM:
        {
            CDlgVcaITSCfg  dlg;
            dlg.m_lServerID = m_lUserID;
            dlg.m_iDevIndex = m_iDevIndex;
			dlg.m_iVcaChannel = m_lChannel;
            dlg.DoModal();
        }
        break;
	case IVMS_6200_B:
    case IVMS_6200_C:
	case IVMS_6200_T:
		{
            switch (iVCAType)
            {
			case VCA_BEHAVIOR_BASE:
			case VCA_BEHAVIOR_ADVANCE:
			case VCA_BEHAVIOR_FULL:
			case VCA_BEHAVIOR_PRISON:
			case VCA_BEHAVIOR_PRISON_PERIMETER:
				{
					CDlgVcaBehaviorCfg dlg;
					dlg.m_lServerID = m_lUserID;
					dlg.m_iDevIndex = m_iDevIndex;
					dlg.m_iChannelNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
					dlg.m_iVcaChannel = m_lChannel;
					dlg.m_byVcaType = iVCAType;
			        dlg.m_byVcaChanMode = byVcaChanMode;
					dlg.DoModal();
				}
				break;
			case VCA_PDC:
				{
					CDlgPdcRuleCfg dlg;
					dlg.m_lServerID = m_lUserID;
					dlg.m_iDevIndex = m_iDevIndex;
					dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;
					dlg.m_iChannelNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
					dlg.m_iCurChannel = m_lChannel - 1;
					dlg.m_iVcaChan = m_lChannel;
					dlg.DoModal();
				}
				break;
			case VCA_ITS:
				{   
					if (g_struDeviceInfo[m_iDevIndex].bySupport1 & 0x8)
					{
						CDlgVcaSceneTrafficCfg dlg;
						dlg.m_lServerID = m_lUserID;
						dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;
						dlg.m_iDevIndex = m_iDevIndex;
						dlg.m_iChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
						dlg.m_iVcaChannel = m_lChannel;
                        dlg.DoModal();
					}
					else
					{
						CDlgVcaITSCfg  dlg;
						dlg.m_lServerID = m_lUserID;
						dlg.m_iDevIndex = m_iDevIndex;
						dlg.m_iVcaChannel = m_lChannel;
                        dlg.DoModal();
					}
				}
				break;
			case VCA_TPS:
				{
					CDlgVcaITSCfg  dlg;
					dlg.m_lServerID = m_lUserID;
					dlg.m_iDevIndex = m_iDevIndex;
					dlg.m_iVcaChannel = m_lChannel;
                    dlg.DoModal();
				}
				break;
			case VCA_TFS:
				{   
					CDlgVcaSceneTrafficCfg dlg;
					dlg.m_lServerID = m_lUserID;
					dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;	
					dlg.m_iDevIndex = m_iDevIndex;
					dlg.m_iChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
					dlg.m_iVcaChannel = m_lChannel;
                    dlg.DoModal();
				}
				break;
			case VCA_PLATE:
				{
					CDlgVcaITSCfg  dlg;
					dlg.m_lServerID = m_lUserID;
					dlg.m_iDevIndex = m_iDevIndex;
					dlg.m_iVcaChannel = m_lChannel;
                    dlg.DoModal();
				}
				break;
			case 0:
				{
					CDlgVcaResetCounterCfg dlg;
					dlg.m_lServerID = m_lUserID;
					dlg.m_iDevIndex = m_iDevIndex;
					dlg.m_iVcaChan = m_lChannel;
					dlg.DoModal();
				}
				break;
			default:
                break;
            }
		}
		break;
	case IVMS_6200_F:
    case IVMS_6200_F_S:
	case IIP_CAM_F:
	case IVS_IPCAM:
	case MEGA_IPCAM:
		{
			CDlgVcaFace dlg;
			dlg.m_lServerID = m_lUserID;
			dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;	
			dlg.m_iDevIndex = m_iDevIndex;
			dlg.m_iChannelNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
			dlg.m_iVcaChannel = m_lChannel;
			dlg.DoModal();
		}
		break;
	default:
        {
            CDlgVcaBehaviorCfg dlg;
            dlg.m_lServerID = m_lUserID;
            dlg.m_iDevIndex = m_iDevIndex;
            dlg.m_iChannelNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
			dlg.m_iVcaChannel = m_lChannel;
			dlg.m_byVcaType = iVCAType;
			dlg.m_byVcaChanMode = byVcaChanMode;
            dlg.DoModal();
        }
		break;
	}
}

void CDlgProductVcaCfg::OnBtnKeyparam() 
{
	CDlgVcaParamkey dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}

void CDlgProductVcaCfg::UpdateWindowParam(LONG lDevIndex,LONG lChannel)
{
	m_lUserID = g_struDeviceInfo[lDevIndex].lLoginID;
	m_lChannel = lChannel;
	if (m_iDevIndex != lDevIndex)
	{   
		m_iDevIndex = lDevIndex;
		m_dlgVcaDevAbility.UpdateWindowParam(m_iDevIndex);
	}
	ShowChildWnd();
}


void CDlgProductVcaCfg::OnBtnVcaFun() 
{
	CDlgVcaFunCfg dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_iChannelIndex =  m_lChannel;
	dlg.DoModal();	
}

void CDlgProductVcaCfg::OnBtnDiagnoisticServer() 
{
	CDlgDiagnosticServer dlg;
	dlg.m_lServerID = m_lUserID;			
	dlg.m_iDevIndex = m_iDevIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgProductVcaCfg::OnBtnPositionRule() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaPositionRule dlg;
	
	dlg.m_lServerID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	//dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].iStartChan;
    dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_iChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum + g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan;
	
    dlg.DoModal();
}

void CDlgProductVcaCfg::OnBtnBvCalibCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaBVCalibrate dlg;
	
	dlg.m_lServerID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_lChannel = m_lChannel;
	
    dlg.DoModal();
}

void CDlgProductVcaCfg::OnBtnBvCorrectParam() 
{
	// TODO: Add your control notification handler code here
	CDlgBvCalibParamCfg dlg;
	
	dlg.m_lLoginID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_lChannel = m_lChannel;
	
    dlg.DoModal();
}

#include "DlgVCAAlarmLogo.h"
void CDlgProductVcaCfg::OnBtnVcaDecodecfg() 
{
	// TODO: Add your control notification handler code here
	DlgVCAAlarmLogo dlg; 
    dlg.DoModal(); 
}

void CDlgProductVcaCfg::OnBtnRuleColorCfg() 
{
	// TODO: Add your control notification handler code here
    // TODO: Add your control notification handler code here
    CDlgVCARuleColorCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    
	dlg.DoModal();	
}
