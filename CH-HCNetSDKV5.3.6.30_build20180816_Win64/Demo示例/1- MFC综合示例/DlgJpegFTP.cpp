// JpegFTP.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgJpegFTP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BYTE F_HexStrToByte(CString sTmp, int len)
{
    int e, j;
    BYTE t = 0;
    char s;
    for(j=0;j<len;j++)
    { 
        s = sTmp.GetAt(j); 
        
        switch(s){ 
        case 'A':
        case 'a':
            e=10; 
            break;
            
        case 'B':
        case 'b':
            e=11; 
            break;
            
        case 'C':
        case 'c':
            e=12; 
            break;
            
        case 'D':
        case 'd':
            e=13; 
            break;
            
        case 'E':
        case 'e':
            e=14; 
            break;
            
        case 'F':
        case 'f':
            e=15; 
            break;
        default:
            e = atoi(&s);
        }
        t=t*16+e; 
    }
    return t;
}
/////////////////////////////////////////////////////////////////////////////
// CJpegFTP dialog


CJpegFTP::CJpegFTP(CWnd* pParent /*=NULL*/)
: CDialog(CJpegFTP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJpegFTP)
	m_CardLen1 = 0;
	m_CardLen2 = 0;
	m_Delimiter = _T("");
	m_EndSign1 = _T("");
	m_EndSign2 = _T("");
	m_EveryTimes = 0;
	m_FTPport = 0;
	m_FTPpsw = _T("");
	m_StartPos1 = 0;
	m_StartPos2 = 0;
	m_StartSgin1 = _T("");
	m_StartSgin2 = _T("");
	m_UpInterval = 0;
	m_FTPname = _T("");
	m_bChan232_1 = FALSE;
	m_bChan232_10 = FALSE;
	m_bChan232_11 = FALSE;
	m_bChan232_12 = FALSE;
	m_bChan232_13 = FALSE;
	m_bChan232_14 = FALSE;
	m_bChan232_15 = FALSE;
	m_bChan232_16 = FALSE;
	m_bChan485_1 = FALSE;
	m_bChan485_2 = FALSE;
	m_bChan485_3 = FALSE;
	m_bChan232_2 = FALSE;
	m_bChan485_4 = FALSE;
	m_bChan485_5 = FALSE;
	m_bChan485_6 = FALSE;
	m_bChan485_7 = FALSE;
	m_bChan485_8 = FALSE;
	m_bChan485_9 = FALSE;
	m_bChan485_10 = FALSE;
	m_bChan485_11 = FALSE;
	m_bChan485_12 = FALSE;
	m_bChan485_13 = FALSE;
	m_bChan232_3 = FALSE;
	m_bChan485_14 = FALSE;
	m_bChan485_15 = FALSE;
	m_bChan485_16 = FALSE;
	m_bChanAlarm_1 = FALSE;
	m_bChanAlarm_2 = FALSE;
	m_bChanAlarm_3 = FALSE;
	m_bChanAlarm_4 = FALSE;
	m_bChanAlarm_5 = FALSE;
	m_bChanAlarm_6 = FALSE;
	m_bChanAlarm_7 = FALSE;
	m_bChan232_4 = FALSE;
	m_bChanAlarm_8 = FALSE;
	m_bChanAlarm_9 = FALSE;
	m_bChanAlarm_10 = FALSE;
	m_bChanAlarm_11 = FALSE;
	m_bChanAlarm_12 = FALSE;
	m_bChanAlarm_13 = FALSE;
	m_bChanAlarm_14 = FALSE;
	m_bChanAlarm_15 = FALSE;
	m_bChanAlarm_16 = FALSE;
	m_bChan232_5 = FALSE;
	m_bChan232_6 = FALSE;
	m_bChan232_7 = FALSE;
	m_bChan232_8 = FALSE;
	m_bChan232_9 = FALSE;
	m_FTPIP = _T("");
	m_CapInterval = 0;
	m_bCatchMode1 = FALSE;
	m_bCatchMode2 = FALSE;
	m_bCatchMode3 = FALSE;
	m_bCatchMode4 = FALSE;
	m_bCatchMode5 = FALSE;
	//}}AFX_DATA_INIT
}


void CJpegFTP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJpegFTP)
	DDX_Control(pDX, IDC_COMBOUSEFTPUP, m_UseFTPUpCtrl);
	DDX_Control(pDX, IDC_COMBOSAVEHD, m_SaveHDCtrl);
	DDX_Control(pDX, IDC_COMBOQUALITY, m_QualityCtrl);
	DDX_Control(pDX, IDC_COMBOPICSIZE, m_PicSizeCtrl);
	DDX_Control(pDX, IDC_COMBONAMEITEM, m_NameItemCtrl);
	DDX_Control(pDX, IDC_COMBONAMEELEMENT, m_NameElementCtrl);
	DDX_Control(pDX, IDC_COMBODIRMODETWO, m_DirMode2Ctrl);
	DDX_Control(pDX, IDC_COMBODIRMODEONE, m_DirMode1Ctrl);
	DDX_Control(pDX, IDC_COMBODIRLEVEL, m_DirLevelCtrl);
	DDX_Control(pDX, IDC_COMBOCHANNUM, m_ChanNumCtrl);
	DDX_Control(pDX, IDC_COMBOALARMIN, m_AlarmInCtrl);
	DDX_Text(pDX, IDC_EDITCARDLEN1, m_CardLen1);
	DDX_Text(pDX, IDC_EDITCARDLEN2, m_CardLen2);
	DDX_Text(pDX, IDC_EDITDELIMITER, m_Delimiter);
	DDX_Text(pDX, IDC_EDITENDSIGN1, m_EndSign1);
	DDX_Text(pDX, IDC_EDITENDSIGN2, m_EndSign2);
	DDX_Text(pDX, IDC_EDITEVERYTIMES, m_EveryTimes);
	DDX_Text(pDX, IDC_EDITPORT, m_FTPport);
	DDX_Text(pDX, IDC_EDITPSWD, m_FTPpsw);
	DDX_Text(pDX, IDC_EDITSTARTPOS1, m_StartPos1);
	DDX_Text(pDX, IDC_EDITSTARTPOS2, m_StartPos2);
	DDX_Text(pDX, IDC_EDITSTARTSIGN1, m_StartSgin1);
	DDX_Text(pDX, IDC_EDITSTARTSIGN2, m_StartSgin2);
	DDX_Text(pDX, IDC_EDITUPINTERVAL, m_UpInterval);
	DDX_Text(pDX, IDC_EDITUSER, m_FTPname);
	DDX_Check(pDX, IDC_CHECK1, m_bChan232_1);
	DDX_Check(pDX, IDC_CHECK10, m_bChan232_10);
	DDX_Check(pDX, IDC_CHECK11, m_bChan232_11);
	DDX_Check(pDX, IDC_CHECK12, m_bChan232_12);
	DDX_Check(pDX, IDC_CHECK13, m_bChan232_13);
	DDX_Check(pDX, IDC_CHECK14, m_bChan232_14);
	DDX_Check(pDX, IDC_CHECK15, m_bChan232_15);
	DDX_Check(pDX, IDC_CHECK16, m_bChan232_16);
	DDX_Check(pDX, IDC_CHECK17, m_bChan485_1);
	DDX_Check(pDX, IDC_CHECK18, m_bChan485_2);
	DDX_Check(pDX, IDC_CHECK19, m_bChan485_3);
	DDX_Check(pDX, IDC_CHECK2, m_bChan232_2);
	DDX_Check(pDX, IDC_CHECK20, m_bChan485_4);
	DDX_Check(pDX, IDC_CHECK21, m_bChan485_5);
	DDX_Check(pDX, IDC_CHECK22, m_bChan485_6);
	DDX_Check(pDX, IDC_CHECK23, m_bChan485_7);
	DDX_Check(pDX, IDC_CHECK24, m_bChan485_8);
	DDX_Check(pDX, IDC_CHECK25, m_bChan485_9);
	DDX_Check(pDX, IDC_CHECK26, m_bChan485_10);
	DDX_Check(pDX, IDC_CHECK27, m_bChan485_11);
	DDX_Check(pDX, IDC_CHECK28, m_bChan485_12);
	DDX_Check(pDX, IDC_CHECK29, m_bChan485_13);
	DDX_Check(pDX, IDC_CHECK3, m_bChan232_3);
	DDX_Check(pDX, IDC_CHECK30, m_bChan485_14);
	DDX_Check(pDX, IDC_CHECK31, m_bChan485_15);
	DDX_Check(pDX, IDC_CHECK32, m_bChan485_16);
	DDX_Check(pDX, IDC_CHECK33, m_bChanAlarm_1);
	DDX_Check(pDX, IDC_CHECK34, m_bChanAlarm_2);
	DDX_Check(pDX, IDC_CHECK35, m_bChanAlarm_3);
	DDX_Check(pDX, IDC_CHECK36, m_bChanAlarm_4);
	DDX_Check(pDX, IDC_CHECK37, m_bChanAlarm_5);
	DDX_Check(pDX, IDC_CHECK38, m_bChanAlarm_6);
	DDX_Check(pDX, IDC_CHECK39, m_bChanAlarm_7);
	DDX_Check(pDX, IDC_CHECK4, m_bChan232_4);
	DDX_Check(pDX, IDC_CHECK40, m_bChanAlarm_8);
	DDX_Check(pDX, IDC_CHECK41, m_bChanAlarm_9);
	DDX_Check(pDX, IDC_CHECK42, m_bChanAlarm_10);
	DDX_Check(pDX, IDC_CHECK43, m_bChanAlarm_11);
	DDX_Check(pDX, IDC_CHECK44, m_bChanAlarm_12);
	DDX_Check(pDX, IDC_CHECK45, m_bChanAlarm_13);
	DDX_Check(pDX, IDC_CHECK46, m_bChanAlarm_14);
	DDX_Check(pDX, IDC_CHECK47, m_bChanAlarm_15);
	DDX_Check(pDX, IDC_CHECK48, m_bChanAlarm_16);
	DDX_Check(pDX, IDC_CHECK5, m_bChan232_5);
	DDX_Check(pDX, IDC_CHECK6, m_bChan232_6);
	DDX_Check(pDX, IDC_CHECK7, m_bChan232_7);
	DDX_Check(pDX, IDC_CHECK8, m_bChan232_8);
	DDX_Check(pDX, IDC_CHECK9, m_bChan232_9);
	DDX_Text(pDX, IDC_EDITIP, m_FTPIP);
	DDX_Text(pDX, IDC_EDITCAPINTERVAL, m_CapInterval);
	DDX_Check(pDX, IDC_CHECKCATCHMODE1, m_bCatchMode1);
	DDX_Check(pDX, IDC_CHECKCATCHMODE2, m_bCatchMode2);
	DDX_Check(pDX, IDC_CHECKCATCHMODE3, m_bCatchMode3);
	DDX_Check(pDX, IDC_CHECKCATCHMODE4, m_bCatchMode4);
	DDX_Check(pDX, IDC_CHECKCATCHMODE5, m_bCatchMode5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJpegFTP, CDialog)
//{{AFX_MSG_MAP(CJpegFTP)
ON_BN_CLICKED(IDC_BUTCANCLE, OnButcancle)
ON_CBN_SELCHANGE(IDC_COMBONAMEITEM, OnSelchangeCombonameitem)
ON_CBN_SELCHANGE(IDC_COMBOALARMIN, OnSelchangeComboalarmin)
ON_CBN_SELCHANGE(IDC_COMBOCHANNUM, OnSelchangeCombochannum)
ON_BN_CLICKED(IDC_BUTALARMINOK, OnButalarminok)
ON_BN_CLICKED(IDC_BUTPICQUALITYOK, OnButpicqualityok)
ON_BN_CLICKED(IDC_BUTJPEGNAME, OnButjpegname)
ON_BN_CLICKED(IDC_BUTSAVEJPEG, OnButsavejpeg)
ON_BN_CLICKED(IDC_BUTSAVEFTP, OnButsaveftp)
ON_BN_CLICKED(IDC_BUTCATPIC, OnButcatpic)
ON_CBN_SELCHANGE(IDC_COMBODIRLEVEL, OnSelchangeCombodirlevel)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJpegFTP message handlers

void CJpegFTP::OnButcancle() 
{
	CDialog::OnCancel();	
}

BOOL CJpegFTP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitUI();	

	return TRUE;
}


void CJpegFTP::F_Show232ChanCtrl()
{
	//232
	if (m_iChannelnumber>=1)
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		m_bChan232_1 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 1) & 0x01;
	}
	if (m_iChannelnumber>=2)
	{
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		m_bChan232_2 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 2) & 0x01;
	}
	if (m_iChannelnumber>=3)
	{
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		m_bChan232_3 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 3) & 0x01;
	}
	if (m_iChannelnumber>=4)
	{
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		m_bChan232_4 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 4) & 0x01;
	}
	if (m_iChannelnumber>=5)
	{
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
		m_bChan232_5 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 5) & 0x01;
	}
	if (m_iChannelnumber>=6)
	{
		GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);
		m_bChan232_6 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 6) & 0x01;
	}
	if (m_iChannelnumber>=7)
	{
		GetDlgItem(IDC_CHECK7)->EnableWindow(TRUE);
		m_bChan232_7 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 7) & 0x01;
	}
	if (m_iChannelnumber>=8)
	{
		GetDlgItem(IDC_CHECK8)->EnableWindow(TRUE);
		m_bChan232_8 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 8) & 0x01;
	}
	if (m_iChannelnumber>=9)
	{
		GetDlgItem(IDC_CHECK9)->EnableWindow(TRUE);
		m_bChan232_9 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 9) & 0x01;
	}
	if (m_iChannelnumber>=10)
	{
		GetDlgItem(IDC_CHECK10)->EnableWindow(TRUE);
		m_bChan232_10 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 10) & 0x01;
	}
	if (m_iChannelnumber>=11)
	{
		GetDlgItem(IDC_CHECK11)->EnableWindow(TRUE);
		m_bChan232_11 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 11) & 0x01;
	}
	if (m_iChannelnumber>=12)
	{
		GetDlgItem(IDC_CHECK12)->EnableWindow(TRUE);
		m_bChan232_12 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 12) & 0x01;
	}
	if (m_iChannelnumber>=13)
	{
		GetDlgItem(IDC_CHECK13)->EnableWindow(TRUE);
		m_bChan232_13 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 13) & 0x01;
	}
	if (m_iChannelnumber>=14)
	{
		GetDlgItem(IDC_CHECK14)->EnableWindow(TRUE);
		m_bChan232_14 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 14) & 0x01;
	}
	if (m_iChannelnumber>=15)
	{
		GetDlgItem(IDC_CHECK15)->EnableWindow(TRUE);
		m_bChan232_15 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 15) & 0x01;
	}
	if (m_iChannelnumber>=16)
	{
		GetDlgItem(IDC_CHECK16)->EnableWindow(TRUE);
		m_bChan232_16 = (m_jpegcfg.struRs232Cfg.dwTriggerPicChans >> 16) & 0x01;
	}	
}

void CJpegFTP::F_Show485ChanCtrl()
{
	//485
	if (m_iChannelnumber>=1)
	{
		GetDlgItem(IDC_CHECK17)->EnableWindow(TRUE);
		m_bChan485_1 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 1) & 0x01;
	}
	if (m_iChannelnumber>=2)
	{
		GetDlgItem(IDC_CHECK18)->EnableWindow(TRUE);
		m_bChan485_2 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 2) & 0x01;
	}
	if (m_iChannelnumber>=3)
	{
		GetDlgItem(IDC_CHECK19)->EnableWindow(TRUE);
		m_bChan485_3 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 3) & 0x01;
	}
	if (m_iChannelnumber>=4)
	{
		GetDlgItem(IDC_CHECK20)->EnableWindow(TRUE);
		m_bChan485_4 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 4) & 0x01;
	}
	if (m_iChannelnumber>=5)
	{
		GetDlgItem(IDC_CHECK21)->EnableWindow(TRUE);
		m_bChan485_5 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 5) & 0x01;
	}
	if (m_iChannelnumber>=6)
	{
		GetDlgItem(IDC_CHECK22)->EnableWindow(TRUE);
		m_bChan485_6 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 6) & 0x01;
	}
	if (m_iChannelnumber>=7)
	{
		GetDlgItem(IDC_CHECK23)->EnableWindow(TRUE);
		m_bChan485_7 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 7) & 0x01;
	}
	if (m_iChannelnumber>=8)
	{
		GetDlgItem(IDC_CHECK24)->EnableWindow(TRUE);
		m_bChan485_8 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 8) & 0x01;
	}
	if (m_iChannelnumber>=9)
	{
		GetDlgItem(IDC_CHECK25)->EnableWindow(TRUE);
		m_bChan485_9 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 9) & 0x01;
	}
	if (m_iChannelnumber>=10)
	{
		GetDlgItem(IDC_CHECK26)->EnableWindow(TRUE);
		m_bChan485_10 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 10) & 0x01;
	}
	if (m_iChannelnumber>=11)
	{
		GetDlgItem(IDC_CHECK27)->EnableWindow(TRUE);
		m_bChan485_11 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 11) & 0x01;
	}
	if (m_iChannelnumber>=12)
	{
		GetDlgItem(IDC_CHECK28)->EnableWindow(TRUE);
		m_bChan485_12 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 12) & 0x01;
	}
	if (m_iChannelnumber>=13)
	{
		GetDlgItem(IDC_CHECK29)->EnableWindow(TRUE);
		m_bChan485_13 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 13) & 0x01;
	}
	if (m_iChannelnumber>=14)
	{
		GetDlgItem(IDC_CHECK30)->EnableWindow(TRUE);
		m_bChan485_14 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 14) & 0x01;
	}
	if (m_iChannelnumber>=15)
	{
		GetDlgItem(IDC_CHECK31)->EnableWindow(TRUE);
		m_bChan485_15 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 15) & 0x01;
	}
	if (m_iChannelnumber>=16)
	{
		GetDlgItem(IDC_CHECK32)->EnableWindow(TRUE);
		m_bChan485_16 = (m_jpegcfg.struRs485Cfg.dwTriggerPicChans >> 16) & 0x01;
	}	
}

void CJpegFTP::F_ShowAlarmInChanCtrl(int chan)
{
	
	//alarmin
	if (m_iChannelnumber>=1)
	{
		GetDlgItem(IDC_CHECK33)->EnableWindow(TRUE);
		m_bChanAlarm_1 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 1) & 0x01;
	}
	if (m_iChannelnumber>=2)
	{
		GetDlgItem(IDC_CHECK34)->EnableWindow(TRUE);
		m_bChanAlarm_2 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 2) & 0x01;
	}
	if (m_iChannelnumber>=3)
	{
		GetDlgItem(IDC_CHECK35)->EnableWindow(TRUE);
		m_bChanAlarm_3 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 3) & 0x01;
	}
	if (m_iChannelnumber>=4)
	{
		GetDlgItem(IDC_CHECK36)->EnableWindow(TRUE);
		m_bChanAlarm_4 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 4) & 0x01;
	}
	if (m_iChannelnumber>=5)
	{
		GetDlgItem(IDC_CHECK37)->EnableWindow(TRUE);
		m_bChanAlarm_5 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 5) & 0x01;
	}
	if (m_iChannelnumber>=6)
	{
		GetDlgItem(IDC_CHECK38)->EnableWindow(TRUE);
		m_bChanAlarm_6 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 6) & 0x01;
	}
	if (m_iChannelnumber>=7)
	{
		GetDlgItem(IDC_CHECK39)->EnableWindow(TRUE);
		m_bChanAlarm_7 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 7) & 0x01;
	}
	if (m_iChannelnumber>=8)
	{
		GetDlgItem(IDC_CHECK40)->EnableWindow(TRUE);
		m_bChanAlarm_8 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 8) & 0x01;
	}
	if (m_iChannelnumber>=9)
	{
		GetDlgItem(IDC_CHECK41)->EnableWindow(TRUE);
		m_bChanAlarm_9 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 9) & 0x01;
	}
	if (m_iChannelnumber>=10)
	{
		GetDlgItem(IDC_CHECK42)->EnableWindow(TRUE);
		m_bChanAlarm_10 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 10) & 0x01;
	}
	if (m_iChannelnumber>=11)
	{
		GetDlgItem(IDC_CHECK43)->EnableWindow(TRUE);
		m_bChanAlarm_11 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 11) & 0x01;
	}
	if (m_iChannelnumber>=12)
	{
		GetDlgItem(IDC_CHECK44)->EnableWindow(TRUE);
		m_bChanAlarm_12 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 12) & 0x01;
	}
	if (m_iChannelnumber>=13)
	{
		GetDlgItem(IDC_CHECK45)->EnableWindow(TRUE);
		m_bChanAlarm_13 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 13) & 0x01;
	}
	if (m_iChannelnumber>=14)
	{
		GetDlgItem(IDC_CHECK46)->EnableWindow(TRUE);
		m_bChanAlarm_14 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 14) & 0x01;
	}
	if (m_iChannelnumber>=15)
	{
		GetDlgItem(IDC_CHECK47)->EnableWindow(TRUE);
		m_bChanAlarm_15 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 15) & 0x01;
	}
	if (m_iChannelnumber>=16)
	{
		GetDlgItem(IDC_CHECK48)->EnableWindow(TRUE);
		m_bChanAlarm_16 = (m_jpegcfg.dwAlarmInPicChanTriggered[chan] >> 16) & 0x01;
	}
}


void CJpegFTP::F_Set232ChanCtrl()
{
	//232
	m_jpegcfg.struRs232Cfg.dwTriggerPicChans = 0;
	
	if (m_iChannelnumber>=1)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_1 << 1;
	}
	if (m_iChannelnumber>=2)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_2 << 2;
	}
	
	if (m_iChannelnumber>=3)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_3 << 3;
	}
	if (m_iChannelnumber>=4)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_4 << 4;
	}
	if (m_iChannelnumber>=5)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_5 << 5;
	}
	if (m_iChannelnumber>=6)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_6 << 6;
	}
	if (m_iChannelnumber>=7)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_7 << 7;
	}
	if (m_iChannelnumber>=8)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_8 << 8;
	}
	if (m_iChannelnumber>=9)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_9 << 9;
	}
	if (m_iChannelnumber>=10)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_10 << 10;
	}
	if (m_iChannelnumber>=11)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_11 << 11;
	}
	if (m_iChannelnumber>=12)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_12 << 12;
	}
	if (m_iChannelnumber>=13)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_13 << 13;
	}
	if (m_iChannelnumber>=14)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_14 << 14;
	}
	if (m_iChannelnumber>=15)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_15 << 15;
	}
	if (m_iChannelnumber>=16)
	{
		m_jpegcfg.struRs232Cfg.dwTriggerPicChans |= m_bChan232_16 << 16;
	}
}


void CJpegFTP::F_Set485ChanCtrl()
{
	m_jpegcfg.struRs485Cfg.dwTriggerPicChans = 0;
	if (m_iChannelnumber>=1)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_1 << 1;
	}
	if (m_iChannelnumber>=2)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_2 << 2;
	}
	if (m_iChannelnumber>=3)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_3 << 3;
	}
	if (m_iChannelnumber>=4)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_4 << 4;
	}
	if (m_iChannelnumber>=5)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_5 << 5;
	}
	if (m_iChannelnumber>=6)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_6 << 6;
	}
	if (m_iChannelnumber>=7)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_7 << 7;
	}
	if (m_iChannelnumber>=8)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_8 << 8;
	}
	if (m_iChannelnumber>=9)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_9 << 9;
	}
	if (m_iChannelnumber>=10)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_10 << 10;
	}
	if (m_iChannelnumber>=11)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_11 << 11;
	}
	if (m_iChannelnumber>=12)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_12 << 12;
	}
	if (m_iChannelnumber>=13)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_13 << 13;
	}
	if (m_iChannelnumber>=14)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_14 << 14;
	}
	if (m_iChannelnumber>=15)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_15 << 15;
	}
	if (m_iChannelnumber>=16)
	{
		m_jpegcfg.struRs485Cfg.dwTriggerPicChans |= m_bChan485_16 << 16;
	}	
}

void CJpegFTP::F_SetAlarmInChanCtrl(int chan)
{
	m_jpegcfg.dwAlarmInPicChanTriggered[chan] = 0;
	
	if (m_iChannelnumber>=1)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_1 << 1;
	}
	if (m_iChannelnumber>=2)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_2 << 2;
	}
	if (m_iChannelnumber>=3)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_3 << 3;
	}
	if (m_iChannelnumber>=4)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_4 << 4;
	}
	if (m_iChannelnumber>=5)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_5 << 5;
	}
	if (m_iChannelnumber>=6)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_6 << 6;
	}
	if (m_iChannelnumber>=7)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_7 << 7;
	}
	if (m_iChannelnumber>=8)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_8 << 8;
	}
	if (m_iChannelnumber>=9)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_9 << 9;
	}
	if (m_iChannelnumber>=10)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_10 << 10;
	}
	if (m_iChannelnumber>=11)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_11 << 11;
	}
	if (m_iChannelnumber>=12)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_12 << 12;
	}
	if (m_iChannelnumber>=13)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_13 << 13;
	}
	if (m_iChannelnumber>=14)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_14 << 14;
	}
	if (m_iChannelnumber>=15)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_15 << 15;
	}
	if (m_iChannelnumber>=16)
	{
		m_jpegcfg.dwAlarmInPicChanTriggered[chan] |=  m_bChanAlarm_16 << 16;
	}	
}



void CJpegFTP::OnSelchangeCombonameitem() 
{
	UpdateData(TRUE);
	
	int temp = m_NameItemCtrl.GetCurSel();
	m_NameElementCtrl.SetCurSel(m_jpegcfg.struPicNameRule.byItemOrder[temp]);
	
	UpdateData(FALSE);	
}

void CJpegFTP::OnSelchangeComboalarmin() 
{
	UpdateData(TRUE);
	
	int temp = m_AlarmInCtrl.GetCurSel();
	F_ShowAlarmInChanCtrl(temp);
	
	UpdateData(FALSE);		
}

void CJpegFTP::OnSelchangeCombochannum() 
{
	UpdateData(TRUE);
	
	int temp = m_ChanNumCtrl.GetCurSel();
	m_PicSizeCtrl.SetCurSel(m_jpegcfg.struJpegPara[temp].wPicSize);
	m_QualityCtrl.SetCurSel(m_jpegcfg.struJpegPara[temp].wPicQuality);
    m_EveryTimes = m_jpegcfg.dwTriggerPicTimes[temp];
    UpdateData(FALSE);
}

void CJpegFTP::OnButalarminok() 
{
	UpdateData(TRUE);
	
	int temp = m_AlarmInCtrl.GetCurSel();
	F_SetAlarmInChanCtrl(temp);
}

void CJpegFTP::OnButpicqualityok() 
{
	UpdateData(TRUE);
	int temp = m_ChanNumCtrl.GetCurSel();
	m_jpegcfg.struJpegPara[temp].wPicSize = m_PicSizeCtrl.GetCurSel();
	m_jpegcfg.struJpegPara[temp].wPicQuality = m_QualityCtrl.GetCurSel();
	m_jpegcfg.dwTriggerPicTimes[temp] =  m_EveryTimes;	
}

void CJpegFTP::OnButjpegname() 
{
	UpdateData(TRUE);
	
	int temp = m_NameItemCtrl.GetCurSel();
	m_jpegcfg.struPicNameRule.byItemOrder[temp] = m_NameElementCtrl.GetCurSel();
	if ("" != m_Delimiter)
	{
		m_jpegcfg.struPicNameRule.byDelimiter = m_Delimiter.GetAt(0);
	}
}

void CJpegFTP::OnButsavejpeg() 
{
	UpdateData(TRUE);
	CString sTemp;
	char szLan[128] = {0};
	int temp;
	
	//图片命名规则
	if ("" != m_Delimiter)
	{
		m_jpegcfg.struPicNameRule.byDelimiter = m_Delimiter.GetAt(0);
	}
	
	temp = m_NameItemCtrl.GetCurSel();
	m_jpegcfg.struPicNameRule.byItemOrder[temp] = m_NameElementCtrl.GetCurSel();
	
    CString sTmp;
    BYTE byTmp;
    int nStrLen;
    //232配置/**/
    nStrLen = m_StartSgin1.GetLength();
    if ((nStrLen > 2)&&(nStrLen < 5))
    {		
        if ((m_StartSgin1.GetAt(0) != '0')||(m_StartSgin1.GetAt(1) != 'x'))
        {
			g_StringLanType(szLan, "232开始符请填入标准16进制格式的数字！如0x34", "232Begin sign,please infilling standard hexadecimal number! Such as 0x34");
            AfxMessageBox(szLan);
            return;
        }
        sTmp = m_StartSgin1.Mid(2,nStrLen-2);
        byTmp = F_HexStrToByte(sTmp, nStrLen-2);
        m_jpegcfg.struRs232Cfg.byStrFlag = byTmp;
    }
    else
    {
		g_StringLanType(szLan, "232开始符请填入一位16进制数，如0x5,0xfe！", "232Begin sign,please infilling a hexadecimal number，such as 0x5,0xfe!");
        AfxMessageBox(szLan);
        return ;
    }
    
    nStrLen = m_EndSign1.GetLength();
    if ((nStrLen > 2)&&(nStrLen < 5))
    {		
        if ((m_EndSign1.GetAt(0) != '0')||(m_EndSign1.GetAt(1) != 'x'))
        {
			g_StringLanType(szLan, "232结束符请填入标准16进制格式的数字！如0x34", "232End sign,please infilling standard hexadecimal number!such as  0x34");
            AfxMessageBox(szLan);
            return;
        }
        sTmp = m_EndSign1.Mid(2,nStrLen-2);
        byTmp = F_HexStrToByte(sTmp, nStrLen-2);
        m_jpegcfg.struRs232Cfg.byEndFlag = byTmp;
    }
    else
    {	
		g_StringLanType(szLan, "232结束符请填入一位16进制数，如0x5,0xfe！", "232End sign,please infilling a hexadecimal number，such as 0x5,such as  0xfe!");
        AfxMessageBox(szLan);
        return ;
    }
	
    m_jpegcfg.struRs232Cfg.wCardIdx = (WORD)m_StartPos1;
    m_jpegcfg.struRs232Cfg.dwCardLen = m_CardLen1;
    F_Set232ChanCtrl();
    
    //485配置
    nStrLen = m_StartSgin2.GetLength();
    if ((nStrLen > 2)&&(nStrLen < 5))
    {		
        if ((m_StartSgin2.GetAt(0) != '0')||(m_StartSgin2.GetAt(1) != 'x'))
        {
			g_StringLanType(szLan, "485开始符请填入标准16进制格式的数字！如0x34", "485Begin sign,please infilling standard hexadecimal number! Such as 0x34");
            AfxMessageBox(szLan);
            return;
        }
        sTmp = m_StartSgin2.Mid(2,nStrLen-2);
        
        byTmp = F_HexStrToByte(sTmp, nStrLen-2);
        m_jpegcfg.struRs485Cfg.byStrFlag = byTmp;
    }
    else
    {
		g_StringLanType(szLan, "485开始符请填入一位16进制数，如0x5,0xfe！", "Begin sign,please infilling a hexadecimal number，such as 0x5,0xfe");
        AfxMessageBox(szLan);
        return ;
    }
    
    nStrLen = m_EndSign2.GetLength();
    if ((nStrLen > 2)&&(nStrLen < 5))
    {		
        if ((m_EndSign2.GetAt(0) != '0')||(m_EndSign2.GetAt(1) != 'x'))
        {
			g_StringLanType(szLan, "485结束符请填入标准16进制格式的数字！如0x34", "485End sign,please infilling standard hexadecimal number!如0x34");
			AfxMessageBox(szLan);
            return;
        }
        sTmp = m_EndSign2.Mid(2,nStrLen-2);
        byTmp = F_HexStrToByte(sTmp, nStrLen-2);
        m_jpegcfg.struRs485Cfg.byEndFlag = byTmp;
    }
    else
    {
		g_StringLanType(szLan, "485结束符请填入一位16进制数，如0x5,0xfe！", "End sign,please infilling a hexadecimal number，such as 0x5,0xfe!");
        AfxMessageBox(szLan);
        return ;
    }	
    m_jpegcfg.struRs485Cfg.wCardIdx = (WORD)m_StartPos2;	
    m_jpegcfg.struRs485Cfg.dwCardLen = m_CardLen2;
    F_Set485ChanCtrl();
	//报警输入
	temp = m_AlarmInCtrl.GetCurSel();
	F_SetAlarmInChanCtrl(temp);	
	
	//通道抓图
	temp = m_ChanNumCtrl.GetCurSel();
	m_jpegcfg.struJpegPara[temp].wPicQuality = m_QualityCtrl.GetCurSel();
	m_jpegcfg.struJpegPara[temp].wPicSize = m_PicSizeCtrl.GetCurSel();
	m_jpegcfg.dwTriggerPicTimes[temp] = m_EveryTimes;	
	
	m_jpegcfg.wBurstMode = 0;
	m_jpegcfg.wBurstMode |= (m_bCatchMode1 << 0);
	m_jpegcfg.wBurstMode |= (m_bCatchMode2 << 1);
	m_jpegcfg.wBurstMode |= (m_bCatchMode3 << 2);
	m_jpegcfg.wBurstMode |= (m_bCatchMode4 << 3);
	m_jpegcfg.wBurstMode |= (m_bCatchMode5 << 4);
	
	m_jpegcfg.bySaveToHD = m_SaveHDCtrl.GetCurSel();
	m_jpegcfg.wUploadInterval = m_UpInterval;
	m_jpegcfg.wCatchInterval = m_CapInterval;
	
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_JPEGCFG_V30, 0, &m_jpegcfg, sizeof(NET_DVR_JPEGCFG_V30)))
	{
		g_StringLanType(szLan, "设置JPEG参数失败", "Setup JPEG config failed!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_StringLanType(szLan, "设置JPEG参数成功", "Setup JPEG config succeed!");
		AfxMessageBox(szLan);
		return;
	}
}

void CJpegFTP::OnButsaveftp() 
{
	UpdateData(TRUE);
	CString sTemp;
	char szLan[128] = {0};

	//FTP配置	
	int temp, tmp1, tmp2;
    temp = m_DirLevelCtrl.GetCurSel();
    switch (temp)
    {
    case 0:
        m_ftpcfg.dwDirLevel = 0;
        break;
    case 1:
        m_ftpcfg.dwDirLevel = 1;
		tmp1 = m_DirMode1Ctrl.GetCurSel();
        if (tmp1 == 0)
        {
            m_ftpcfg.wTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
            m_ftpcfg.wTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
            m_ftpcfg.wTopDirMode = 0x3;
        }
        break;
    case 2:
        m_ftpcfg.dwDirLevel = 2;
        tmp1 = m_DirMode1Ctrl.GetCurSel();
        if (tmp1 == 0)
        {
            m_ftpcfg.wTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
            m_ftpcfg.wTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
            m_ftpcfg.wTopDirMode = 0x3;
        }
		tmp2 = m_DirMode2Ctrl.GetCurSel();
        if (tmp2 == 0)
        {
            m_ftpcfg.wSubDirMode = 0x1;
        }
        if (tmp2 == 1)
        {
            m_ftpcfg.wSubDirMode = 0x2;
        }
    default:
        break;
    }

	m_ftpcfg.dwEnableFTP = m_UseFTPUpCtrl.GetCurSel();
	
	m_ftpcfg.dwFTPPort = m_FTPport;
	sprintf((char*)m_ftpcfg.sPassword, m_FTPpsw, PASSWD_LEN);
	sprintf((char*)m_ftpcfg.sUserName, m_FTPname, NAME_LEN);
	sprintf((char*)m_ftpcfg.sFTPIP, m_FTPIP, 16);
	
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_FTPCFG, 0, &m_ftpcfg, sizeof(NET_DVR_FTPCFG)))
	{
		g_StringLanType(szLan, "设置FTP配置信息失败!", "Setup FTP config failed!");
		AfxMessageBox(szLan);	
		return;
	}
	else
	{
		g_StringLanType(szLan, "FTP参数保存成功!", "Setup FTP config succeed!");
		AfxMessageBox(szLan);	
	}
}

void CJpegFTP::OnButcatpic() 
{
	char cFilename[256];
	char szLan[128] = {0};
	CString sTemp;
	NET_DVR_JPEGPARA JpegPara;
	int temp;
	UpdateData(TRUE);
	temp = m_ChanNumCtrl.GetCurSel();
	JpegPara.wPicQuality = m_QualityCtrl.GetCurSel();;
	JpegPara.wPicSize = m_PicSizeCtrl.GetCurSel();
	CTime time = CTime::GetCurrentTime();
	sTemp.Format("%s\\", g_struLocalParam.chPictureSavePath);		
	if (GetFileAttributes(sTemp) != FILE_ATTRIBUTE_DIRECTORY)
	{
		CreateDirectory(sTemp, NULL);
	}
	sprintf(cFilename, "%s\\JPEG_%s_%02d_%4d%02d%02d_%02d%02d%02d_%d.jpg", g_struLocalParam.chPictureSavePath, m_ServerIP, temp+1,	\
		time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), GetTickCount());
	TRACE("Picture save file name : %s", cFilename);
	if (!g_struLocalParam.bUseCard)
	{
		if (NET_DVR_CaptureJPEGPicture(m_lServerID, temp+1, &JpegPara, cFilename))
		{
			g_StringLanType(szLan, "JPEG 抓图成功!", "JPEG capture succeed!");
			AfxMessageBox(szLan); 
			return;
		}
		else
		{
			g_StringLanType(szLan, "JPEG 抓图失败!", "JPEG capture failed!");
			AfxMessageBox(szLan); 
		}
	}
	
}

void CJpegFTP::OnSelchangeCombodirlevel() 
{
	UpdateData(TRUE);
	int temp;
	temp = m_DirLevelCtrl.GetCurSel();
	switch (temp)
	{
	case 0:	
		m_DirMode1Ctrl.EnableWindow(FALSE);
        m_DirMode2Ctrl.EnableWindow(FALSE);		
		break;
	case 1:
		m_DirMode1Ctrl.EnableWindow(TRUE); 
		m_DirMode2Ctrl.EnableWindow(FALSE);
		break;
	case 2:
		m_DirMode1Ctrl.EnableWindow(TRUE);
		m_DirMode2Ctrl.EnableWindow(TRUE);
		break;
	default:	
		break;
	}
	
	UpdateData(FALSE);
}

void CJpegFTP::OnButtonUpdate() 
{
	InitUI();
}

void CJpegFTP::InitUI()
{
	char szLan[128] = {0};
	
	DWORD dwReturned;
	CString sTemp;
    DWORD m_dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    
    m_ChanNumCtrl.ResetContent();	
    m_lServerID = g_struDeviceInfo[m_dwDeviceIndex].lLoginID;
    m_lStartChannel = g_struDeviceInfo[m_dwDeviceIndex].iStartChan;
    m_iChannelnumber = g_struDeviceInfo[m_dwDeviceIndex].iDeviceChanNum;
    m_AlarmInNum = g_struDeviceInfo[m_dwDeviceIndex].iAlarmInNum;
	
	
	int i;
	for (i=0; i<m_iChannelnumber; i++)
	{
		sTemp.Format("Channel%d", (m_lStartChannel+i));
		m_ChanNumCtrl.AddString(sTemp);
	}
	
	m_AlarmInCtrl.ResetContent();	
	
	for (i=0; i<m_AlarmInNum; i++)
	{
		sTemp.Format("AlarmIn%d", i);
		m_AlarmInCtrl.AddString(sTemp);
	}
	
	ZeroMemory(&m_ftpcfg, sizeof(NET_DVR_FTPCFG));
	ZeroMemory(&m_jpegcfg, sizeof(NET_DVR_JPEGCFG_V30));
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_FTPCFG, 0,&m_ftpcfg, sizeof(NET_DVR_FTPCFG), &dwReturned))
	{
        g_StringLanType(szLan, "获取FTP配置信息失败!", "Get FTP Config Failed!");	
		AfxMessageBox(szLan);	
		g_pMainDlg->AddLog(m_dwDeviceIndex,OPERATION_FAIL_T,"NET_DVR_GET_FTPCFG");
	}
	else
	{
		m_DirLevelCtrl.SetCurSel(m_ftpcfg.dwDirLevel);
        int temp;
        temp = m_DirLevelCtrl.GetCurSel();
        switch (temp)
        {
        case 0:	
			m_DirMode1Ctrl.EnableWindow(FALSE);
            m_DirMode2Ctrl.EnableWindow(FALSE);
            break;
        case 1:
            m_DirMode1Ctrl.EnableWindow(TRUE); 
            if (m_ftpcfg.wTopDirMode == 0x1)
            {
                m_DirMode1Ctrl.SetCurSel(0);
            }
            if (m_ftpcfg.wTopDirMode == 0x2)
            {
				m_DirMode1Ctrl.SetCurSel(1);
            }
            if (m_ftpcfg.wTopDirMode == 0x3)
            {
                m_DirMode1Ctrl.SetCurSel(2);
            }
            m_DirMode2Ctrl.EnableWindow(FALSE);
            break;
        case 2:
            m_DirMode1Ctrl.EnableWindow(TRUE);
            m_DirMode2Ctrl.EnableWindow(TRUE);
            if (m_ftpcfg.wTopDirMode == 0x1)
            {
                m_DirMode1Ctrl.SetCurSel(0);
            }
            if (m_ftpcfg.wTopDirMode == 0x2)
            {
                m_DirMode1Ctrl.SetCurSel(1);
            }
            if (m_ftpcfg.wTopDirMode == 0x3)
            {
                m_DirMode1Ctrl.SetCurSel(2);
            }
            if (m_ftpcfg.wSubDirMode == 0x1 )
            {
                m_DirMode2Ctrl.SetCurSel(0);
            }
            if (m_ftpcfg.wSubDirMode == 0x2 )
            {
                m_DirMode2Ctrl.SetCurSel(1);
            }
            break;
        default:	
            break;
        }

		m_UseFTPUpCtrl.SetCurSel(m_ftpcfg.dwEnableFTP);	
		m_FTPport = m_ftpcfg.dwFTPPort;
		m_FTPpsw = m_ftpcfg.sPassword;
		m_FTPname = m_ftpcfg.sUserName;
		m_FTPIP = m_ftpcfg.sFTPIP;
	}
	
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_JPEGCFG_V30, 0,&m_jpegcfg, sizeof(NET_DVR_JPEGCFG_V30), &dwReturned))
	{
        g_StringLanType(szLan, "获取JPEG配置信息失败!", "Get JPEG Config Failed!");	
		AfxMessageBox(szLan);
	}
	else
	{
		//图片命名规则
		char cTemp[4];
		memcpy(cTemp, &(m_jpegcfg.struPicNameRule.byDelimiter), 1);
		memcpy(cTemp+1, "\0", 1);
		m_Delimiter.Format("%s",cTemp);
		m_NameItemCtrl.SetCurSel(0);
		m_NameElementCtrl.SetCurSel(m_jpegcfg.struPicNameRule.byItemOrder[0]);
		F_Show232ChanCtrl();
		F_Show485ChanCtrl();
		F_ShowAlarmInChanCtrl(0);
		
        //232配置	
        m_StartSgin1.Format("0x%x", m_jpegcfg.struRs232Cfg.byStrFlag);	
        m_StartPos1 = m_jpegcfg.struRs232Cfg.wCardIdx;
        
        m_EndSign1.Format("0x%x", m_jpegcfg.struRs232Cfg.byEndFlag);	
        m_CardLen1 = m_jpegcfg.struRs232Cfg.dwCardLen;
        
        //485配置
        m_StartSgin2.Format("0x%x", m_jpegcfg.struRs485Cfg.byStrFlag);	
        m_StartPos2 = m_jpegcfg.struRs485Cfg.wCardIdx;
        
        m_EndSign2.Format("0x%x", m_jpegcfg.struRs485Cfg.byEndFlag);	
        m_CardLen2 = m_jpegcfg.struRs485Cfg.dwCardLen;       		
		m_StartPos1 = m_jpegcfg.struRs232Cfg.wCardIdx;
		m_CardLen1 = m_jpegcfg.struRs232Cfg.dwCardLen;		
		m_StartPos2 = m_jpegcfg.struRs485Cfg.wCardIdx;		
		m_CardLen2 = m_jpegcfg.struRs485Cfg.dwCardLen;
		
		//报警输入
		m_AlarmInCtrl.SetCurSel(0);
		
		//通道抓图
		m_ChanNumCtrl.SetCurSel(0);
		m_QualityCtrl.SetCurSel(m_jpegcfg.struJpegPara[0].wPicQuality);
		m_PicSizeCtrl.SetCurSel(m_jpegcfg.struJpegPara[0].wPicSize);
		m_EveryTimes = m_jpegcfg.dwTriggerPicTimes[0];
		
		m_bCatchMode1 = m_jpegcfg.wBurstMode & 0x01;
		m_bCatchMode2 = (m_jpegcfg.wBurstMode>>1)&0x01;
		m_bCatchMode3 = (m_jpegcfg.wBurstMode>>2)&0x01;
		m_bCatchMode4 = (m_jpegcfg.wBurstMode>>3)&0x01;
		m_bCatchMode5 = (m_jpegcfg.wBurstMode>>4)&0x01;
		
		m_SaveHDCtrl.SetCurSel(m_jpegcfg.bySaveToHD);
		m_UpInterval = m_jpegcfg.wUploadInterval;
		m_CapInterval = m_jpegcfg.wCatchInterval;
	}
	
	UpdateData(FALSE);
}
