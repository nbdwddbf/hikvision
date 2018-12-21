// DlgInfoXmlCfgWithUrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgInfoXmlCfgWithUrl.h"
#include "afxdialogex.h"
#include "DlgInfoGerenal.h"

#define XML_IN_LEN	1024*100
#define XML_OUT_LEN	100*1024

// CDlgInfoXmlCfgWithUrl 对话框

IMPLEMENT_DYNAMIC(CDlgInfoXmlCfgWithUrl, CDialogEx)

CDlgInfoXmlCfgWithUrl::CDlgInfoXmlCfgWithUrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInfoXmlCfgWithUrl::IDD, pParent)
    , m_csUrl(_T(""))
    , m_csInput(_T(""))
    , m_csOutput(_T(""))
    , m_csCommand(_T(""))
{

}

CDlgInfoXmlCfgWithUrl::~CDlgInfoXmlCfgWithUrl()
{
}

void CDlgInfoXmlCfgWithUrl::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_CBString(pDX, IDC_COMBO_OPERATE_TYPE, m_csUrl);
    DDX_Text(pDX, IDC_EDIT_PARAM_INPUT, m_csInput);
    DDX_Text(pDX, IDC_EDIT_PARAM_OUTPUT, m_csOutput);
    DDX_Control(pDX, IDC_COMBO_OPERATE_TYPE, m_cmbUrl);
    DDX_Text(pDX, IDC_EDIT_COMMAND, m_csCommand);
}


BEGIN_MESSAGE_MAP(CDlgInfoXmlCfgWithUrl, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO_OPERATE_TYPE, &CDlgInfoXmlCfgWithUrl::OnSelchangeComboOperateType)
    ON_BN_CLICKED(IDC_BTN_OPERATE, &CDlgInfoXmlCfgWithUrl::OnBnClickedBtnOperate)
END_MESSAGE_MAP()


// CDlgInfoXmlCfgWithUrl 消息处理程序




BOOL CDlgInfoXmlCfgWithUrl::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    m_pOutBuf = new char[XML_OUT_LEN];
    memset(m_pOutBuf, 0, XML_OUT_LEN);

    m_pInputBuf = new char[XML_IN_LEN];
    memset(m_pInputBuf,0,XML_IN_LEN);


    m_cmbUrl.InsertString(0, ("新建日程发布计划")); //新建日程发布计划
    m_cmbUrl.InsertString(1, ("获取所有发布计划")); //获取所有发布计划
    m_cmbUrl.InsertString(2, ("获取单个发布计划")); //获取单个发布计划
    m_cmbUrl.InsertString(3, ("设置单个发布计划")); //设置单个发布计划
    m_cmbUrl.InsertString(4, ("删除发布计划"));//删除发布计划
    m_cmbUrl.InsertString(5, ("发布计划查找")); //发布计划查找
    m_cmbUrl.InsertString(6, ("获取所有发布计划状态")); //获取所有发布计划状态
    m_cmbUrl.InsertString(7, ("获取单个发布计划状态")); //获取单个发布计划状态
    m_cmbUrl.InsertString(8, ("取消日程发布")); //取消日程发布
    m_cmbUrl.InsertString(9, ("区域搜索")); //区域搜索
    m_cmbUrl.InsertString(10, ("获取终端所有参数配置")); //获取终端所有参数配置
    m_cmbUrl.InsertString(11, ("设置终端所有参数配置")); //设置终端所有参数配置
    m_cmbUrl.InsertString(12, ("批量配置终端所有参数配置")); //批量配置终端所有参数配置
    m_cmbUrl.InsertString(13, ("获取所有终端绑定IPC")); //获取所有终端绑定IPC
    m_cmbUrl.InsertString(14, ("获取单个终端绑定IPC")); //获取单个终端绑定IPC
    m_cmbUrl.InsertString(15, ("设置单个终端绑定IPC")); //设置单个终端绑定IPC

    m_cmbUrl.InsertString(16, ("获取终端IP")); //获取终端IP
    m_cmbUrl.InsertString(17, ("设置终端IP")); //设置终端IP
    m_cmbUrl.InsertString(18, ("终端查找")); //终端查找
    m_cmbUrl.InsertString(19, ("文字消息发布")); //文字消息发布

    m_cmbUrl.InsertString(20, ("日程批量配置")); //日程批量配置
    m_cmbUrl.InsertString(21, ("日程多条件查找")); //日程多条件查找

    m_cmbUrl.InsertString(22, ("获取信息发布和HDMI切换计划")); //获取信息发布和HDMI切换计划
    m_cmbUrl.InsertString(23, ("设置信息发布和HDMI切换计划")); //设置信息发布和HDMI切换计划

    m_cmbUrl.InsertString(24, ("新增组织")); //新增组织
    m_cmbUrl.InsertString(25, ("设置组织信息")); //设置组织信息
    m_cmbUrl.InsertString(26, ("删除组织")); //删除组织
    m_cmbUrl.InsertString(27, ("获取组织")); //获取组织

    m_cmbUrl.InsertString(28, ("新增用户")); //新增用户
    m_cmbUrl.InsertString(29, ("设置用户")); //设置用户
    m_cmbUrl.InsertString(30, ("删除用户")); //删除用户
    m_cmbUrl.InsertString(31, ("获取用户")); //获取用户

    m_cmbUrl.InsertString(32, ("设置用户权限")); //设置用户权限
    m_cmbUrl.InsertString(33, ("获取用户权限")); //获取用户权限

    m_cmbUrl.InsertString(34, ("抓图配置")); //获取用户权限

    m_cmbUrl.InsertString(35, ("获取硬盘初始化状态")); //获取硬盘初始化
    m_cmbUrl.InsertString(36, ("设置初始化")); //设置硬盘初始化
    m_cmbUrl.InsertString(37, ("获取硬盘初始化进度")); //获取硬盘初始化
    m_cmbUrl.SetCurSel(0);

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CDlgInfoXmlCfgWithUrl::OnSelchangeComboOperateType()
{
    // TODO:  在此添加控件通知处理程序代码
    int nCurSel = m_cmbUrl.GetCurSel();
    if (nCurSel == CB_ERR)
    {
        return;
    }
    if (nCurSel == 0)
    {
        m_csInput = "";
        SYSTEMTIME st = { 0 };
        GetLocalTime(&st);
        CString strTime;
        strTime.Format("%04d%02d%02dT%02d:%02d:%02d+08\n",
            st.wYear,
            st.wMonth,
            st.wDay,
            st.wHour,
            st.wMinute,
            st.wSecond);
        m_csCommand.Format("POST /ISAPI/Publish/ScheduleMgr/schedulePlan\r\n");//新建日程发布计划
        m_csInput.Format("<SchedulePlan version=\"2.0\">\r\n"\
            "<planId>1</planId>\r\n" \
            "<scheduleNo>1</scheduleNo>\r\n" \
            "<releaseType>byTerminal</releaseType>\r\n" \
            "<TerminalNoList>\r\n" \
            "<terminalNo>1</terminalNo>\r\n"\
            "</TerminalNoList>\r\n" \
            "<TerminalGroupNoList>\r\n" \
            "<terminalGroupNo></terminalGroupNo>\r\n" \
            "</TerminalGroupNoList>\r\n" \
            "<releaseTime>%s</releaseTime>\r\n" \
            "<effectiveTime>%s</effectiveTime>\r\n"
            "<releaseState>notRelease,releasing,released</releaseState>\r\n" \
            "</SchedulePlan>\r\n",strTime,strTime);
    }
    else if (nCurSel == 1)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/ScheduleMgr/schedulePlan\r\n"); //获取所有发布计划
    }
    else if (nCurSel == 2)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/ScheduleMgr/schedulePlan/1\r\n"); //获取单个发布计划
    }
    else if (nCurSel == 3)
    {
        SYSTEMTIME st = { 0 };
        GetLocalTime(&st);
        CString strTime;
        strTime.Format("%04d%02d%02dT%02d:%02d:%02d+08\n",
            st.wYear,
            st.wMonth,
            st.wDay,
            st.wHour,
            st.wMinute,
            st.wSecond);
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Publish/ScheduleMgr/schedulePlan/1\r\n"); //设置单个发布计划
        m_csInput.Format("<SchedulePlan version=\"2.0\">\r\n" \
            "<planId></planId>\r\n" \
            "<scheduleNo></scheduleNo>\r\n" \
            "<releaseType>byTerminal</releaseType>\r\n" \
            "<TerminalNoList>\r\n" \
            "<terminalNo></terminalNo>\r\n" \
            "</TerminalNoList>\r\n" \
            "<TerminalGroupNoList>\r\n" \
            "<terminalGroupNo></terminalGroupNo>\r\n" \
            "</TerminalGroupNoList>\r\n" \
            "<releaseTime>%s</releaseTime>\r\n" \
            "<releaseState>notRelease,releasing,released</releaseState>\r\n" \
            "</SchedulePlan>",strTime
            );
    }
    else if (nCurSel == 4)
    {
        m_csInput = "";
        m_csCommand.Format("DELETE /ISAPI/Publish/ScheduleMgr/schedulePlan/1\r\n");//删除发布计划
    }
    else if (nCurSel == 5)
    {
        m_csInput = "";
        m_csCommand.Format("POST /ISAPI/Publish/ScheduleMgr/schedulePlanSearch\r\n"); //发布计划查找
        m_csInput.Format("<PlanSearchDescription version=\"2.0\">"\
            "<searchID></searchID>\r\n"\
            "<scheduleNo></scheduleNo>\r\n" \
            "<releaseType></releaseType>\r\n" \
            "<releaseState></releaseState>\r\n" \
            "<TimeSpanList>\r\n" \
            "<TimeSpan>\r\n" \
            "<startTime></startTime>\r\n" \
            "<endTIme></endTime>\r\n" \
            "</TimeSpan>\r\n" \
            "</TimeSpanList>\r\n" \
            "<maxResults></maxResults>\r\n" \
            "<searchResultsPosition></searchResultsPosition>\r\n" \
            "</PlanSearchDescription>\r\n"
            );
    }
    else if (nCurSel == 6)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/ScheduleMgr/schedulePlanState\r\n"); //获取所有发布计划状态
    }
    else if (nCurSel == 7)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/ScheduleMgr/schedulePlanState/1\r\n"); //获取单个发布计划状态
    }
    else if (nCurSel == 8)
    {
        SYSTEMTIME st = { 0 };
        GetLocalTime(&st);
        CString strTime;
        strTime.Format("%04d%02d%02dT%02d:%02d:%02d+08\n",
            st.wYear,
            st.wMonth,
            st.wDay,
            st.wHour,
            st.wMinute,
            st.wSecond);
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Publish/ScheduleMgr/release/cancel\r\n"); //取消日程发布
        m_csInput.Format("<ScheduleRelease version=\"2.0\">\r\n"\
            "<scheduleNo>1</scheduleNo>\r\n"\
            "<releaseTime>%s</releaseTime>\r\n" \
            "<releaseType>byTerminal</releaseType>\r\n"\
            "<TerminalNoList>\r\n"\
            "<terminalNo>1</terminalNo>\r\n"\
            "</TerminalNoList>\r\n"\
            "<TerminalGroupNoList>\r\n"\
            "<terminalGroupNo></terminalGroupNo>\r\n"\
            "</TerminalGroupNoList>\r\n"\
            "</ScheduleRelease>"
            ,strTime);
    }
    else if (nCurSel == 9)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/areaSearch/1\r\n"); //区域搜索
    }
    else if (nCurSel == 10)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/TerminalMgr/terminals/config/1\r\n"); //获取终端所有参数配置
    }
    else if (nCurSel == 11)
    {
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Publish/TerminalMgr/terminals/config/1\r\n"); //设置终端所有参数配置
        m_csInput.Format("<TerminalConfig version=\"2.0\">\r\n" \
            "<id>1</id>\r\n" \
            "<PlayerParam>\r\n"\
            "<volume>10</volume>\r\n"\
            "</PlayerParam>\r\n" \
            "<ScreenParam>\r\n"\
            "<backLightLevel>1</backLightLevel>\r\n"\
            "<bootLogoEnabled>true</bootLogoEnabled>\r\n"\
            "</ScreenParam>\r\n"\
            "<DefaultSchedule>\r\n"\
            "<scheduleId>1</scheduleId>\r\n"\
            "<scheduleName></scheduleName>\r\n"\
            "<enable>true</enable>\r\n"\
            "</DefaultSchedule>\r\n"\
            "<PasswordCfg>\r\n"\
            "<oldPwd></oldPwd>\r\n"\
            "<newPwd></newPwd>\r\n"\
            "</PasswordCfg>\r\n"\
            "</TerminalConfig>\r\n"\
            );
    }
    else if (nCurSel == 12)
    {
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Publish/TerminalMgr/terminals/batchconfig\r\n"); //批量配置终端所有参数配置
        m_csInput.Format("<BatchTerminalConfig version=\"2.0\">\r\n"\
            "<cfgType>volume,light,logo,defaultSchedule,password</cfgType>\r\n"\
            "<volume>10</volume>\r\n"\
            "<backLightLevel>1</backLightLevel>\r\n"\
            "<bootLogoEnabled>true</bootLogoEnabled>\r\n"\
            "<DefaultSchedule>\r\n"\
            "<scheduleId>1</scheduleId>\r\n"\
            "<scheduleName></scheduleName>\r\n"\
            "<enable>true</enable>\r\n"\
            "</DefaultSchedule>\r\n"\
            "<PasswordCfg>\r\n"\
            "<oldPwd></oldPwd>\r\n"\
            "<newPwd></newPwd>\r\n"\
            "</PasswordCfg>\r\n"\
            "<targetType>byTerminal,byGroup,byOrg</targetType>\r\n"\
            "<TerminalNoList>\r\n"\
            "<terminalNo>1</terminalNo>\r\n"\
            "</TerminalNoList>\r\n"\
            "<GroupNoList>\r\n"\
            "<groupNo>1</groupNo>\r\n"\
            "</GroupNoList>\r\n"\
            "<OrgNoList>\r\n"\
            "<orgNo>1</orgNo>\r\n"\
            "</OrgNoList>\r\n"\
            "</BatchTerminalConfig>\r\n"\
            );
    }
    else if (nCurSel == 13)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/TerminalMgr/bindIPC\r\n"); //获取所有终端绑定IPC
    }
    else if (nCurSel == 14)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/TerminalMgr/bindIPC/1\r\n"); //获取单个终端绑定IPC
    }
    else if (nCurSel == 15)
    {
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Publish/TerminalMgr/bindIPC/1\r\n"); //设置单个终端绑定IPC
        m_csInput.Format("<BindIPC version=\"2.0\">\r\n"\
            "<TerminalId>1</TerminalId>\r\n"\
            "<IPCList>\r\n"\
            "<IPC>\r\n"\
            "<id>1</id>\r\n"\
            "<IPCType>normal</IPCType>\r\n"\
            "<channelNo>1</channelNo>\r\n"\
            "<IPCAddress>\r\n"\
            "<addressingFormatType>ipaddress</addressingFormatType>\r\n"\
            "<hostName></hostName>\r\n"\
            "<IpAddress>\r\n"\
            "<ipVersion>v4</ipVersion>\r\n"\
            "<ipAddress>10.17.132.43</ipAddress>\r\n"\
            "<ipv6Address></ipv6Address>\r\n"\
            "</IpAddress>\r\n"\
            "</IPCAddress>\r\n"\
            "<portNo>8000</portNo>\r\n"\
            "<userName>admin</userName>\r\n"\
            "<passWord>123456</passWord>\r\n"\
            "<ipcChannelNo>1</ipcChannelNo>\r\n"\
            "<transmitProtocol>tcp</transmitProtocol>\r\n"\
            "<streamType>main</streamType>\r\n"\
            "</IPC>\r\n"\
            "</IPCList>\r\n"\
            "</BindIPC>\r\n"
            );
    }
    else if (nCurSel == 16)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/TerminalMgr/terminals/addressCfg/1"); //获取终端IP
    }
    else if (nCurSel == 17)
    {
        m_csInput = "";
        m_csCommand.Format("SET /ISAPI/Publish/TerminalMgr/terminals/addressCfg/1"); //设置终端IP
        m_csInput.Format("<AddressCfg versiong=\"2.0\">\r\n"
            "<id>1</id>\r\n"
            "<ipVersion>v4</ipVersion>\r\n"
            "<ipAddress>0.0.0.0</ipAddress>\r\n"
            "<subnetMask>0.0.0.0</subnetMask>\r\n"
            "<ipv6Address>0.0.0.0</ipv6Address>\r\n"
            "<bitMask>0.0.0.0</bitMask>\r\n"
            "<DefaultGateway>\r\n"
            "<ipAddress>0.0.0.0</ipAddress>\r\n"
            "</DefaultGateway>\r\n"
            "<terminalPwd>soft12345</termnalPwd>\r\n"
            "</AddressCfg>\r\n"
            );
    }
    else if (nCurSel == 18)
    {
        m_csInput = "";
        m_csCommand.Format("POST /ISAPI/Publish/TerminalMgr/terminalSearch"); //终端查找
        m_csInput.Format("<TerminalSearchDescription version=\"2.0\">\r\n"\
            "<searchID>1</searchID>\r\n"\
            "<terminalName></terminalName>\r\n"\
            "<terminalNameLike></terminalNameLike>\r\n"\
            "<terminalRemarksLike></terminalRemarksLike>\r\n"\
            "<orgName></orgName>\r\n"\
            "<onlineState>all</onlineState>\r\n"\
            "<softwareVersion></softwareVersion>\r\n"\
            "<PublishStateList>\r\n"\
            "<publishState>publishing,success,failed,null</publishState>\r\n"\
            "</PublishStateList>\r\n"\
            "<InsertStateList>\r\n"\
            "<insertState>null,publishing,inserting,failed</insertState>\r\n"\
            "</InsertState>\r\n"\
            "<PlayStateList>\r\n"\
            "<playState>HDMI,VGA,schedulePlay,scheduleStop,screenOff</playState>\r\n"\
            "</PlayStateList>\r\n"\
            "<maxResults>10</maxResults>\r\n"\
            "<searchResultsPosition>0</searchResultsPosition>\r\n"\
            "</TerminalSearchDescription>\r\n"
            );
    }
    else if (nCurSel == 19)
    {
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Publish/TerminalMgr/insertCharacterCfg"); //文字消息发布
        m_csInput.Format("<InsertCharacterCfg version=\"2.0\">\r\n"\
            "<InsertCharacter>\r\n"\
            "<InsertMessageList>\r\n"\
            "<InsertMessage>\r\n"\
            "<id>1</id>\r\n"\
            "<msgName>msgName1</msgName>\r\n"\
            "<content></content>\r\n"\
            "<TimeRange>\r\n"\
            "<beginTime></beginTime>\r\n"\
            "<endTime></endTime>\r\n"\
            "</TimeRange>\r\n"\
            "</InsertMessage>\r\n"\
            "</InsertMessageList>\r\n"\
            "<msgPos>top,middle,bottom,selfDefine</msgPos>\r\n"\
            "<Position>\r\n"\
            "<positionX></positionX>\r\n"\
            "<positionY></positionY>\r\n"\
            "<height></height>\r\n"\
            "<width></width>\r\n"\
            "</Position>\r\n"\
            "<CharactersEffect>\r\n"\
            "<fontSize>1</fontSize>\r\n"\
            "<FontColor>\r\n"\
            "<RGB>1</RGB>\r\n"\
            "</FontColor>\r\n"\
            "<BackColor>\r\n"\
            "<RGB>1</RGB>\r\n"\
            "</BackColor>\r\n"\
            "<backTransparent>1</backTransparent>\r\n"\
            "<subtitlesEnabled>true</subtitlesEnabled>\r\n"\
            "<scrollDirection>none,left,right,up,down</scrollDirection>\r\n"\
            "<scrollSpeed>1</scrollSpeed>\r\n"\
            "</CharactersEffect>\r\n"\
            "</InsertCharacter>\r\n"\
            "<OperateParam>\r\n"\
            "<operateType>byTerminal</operateType>\r\n"\
            "<TerminalNoList>\r\n"\
            "<terminalNo>1</terminalNo>\r\n"\
            "</TerminalNoList>\r\n"\
            "<OrgNoList>\r\n"\
            "<orgNo>1</orgNo>\r\n"\
            "</OrgNoList>\r\n"\
            "</OperateParam>\r\n"\
            "</InsertCharacterCfg>\r\n"
            );
    }
    else if (nCurSel == 20)
    {
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Publish/ScheduleMgr/playScheduleBatchInfo"); //日程批量配置
        m_csInput.Format("<PlayScheduleBatchInfo version =\"2.0\">\r\n"\
            "<operatorType>property,remark,approve</operatorType>\r\n"\
            "<shareProperty>public,private</shareProperty>\r\n"\
            "<scheduleRemarks></scheduleRemarks>\r\n"\
            "<approveState>approved,notPass,notApprove</approveState>\r\n"\
            "<approveRemarks></approveRemarks>\r\n"\
            "<PlayScheduleIdList>\r\n"\
            "<playScheduleId>1</playScheduleId>\r\n"\
            "<playScheduleId>2</playScheduleId>\r\n"\
            "</PlayScheduleIdList>\r\n"\
            "</PlayScheduleBatchInfo>\r\n"
            );
    }
    else if (nCurSel == 21)
    {
        m_csInput = "";
        SYSTEMTIME st = { 0 };
        GetLocalTime(&st);
        CString strStartTime,strStopTime;
        strStartTime.Format("%04d%02d%02dT%02d:%02d:%02d+08\n",
            st.wYear,
            st.wMonth,
            st.wDay,
            0,
            0,
            0);
        strStopTime.Format("%04d%02d%02dT%02d:%02d:%02d+08\n",
            st.wYear,
            st.wMonth,
            st.wDay,
            23,
            59,
            59);
        m_csCommand.Format("POST /ISAPI/Publish/ScheduleMgr/scheduleMoreSearch"); //日程多条件查找
        m_csInput.Format("<ScheduleMoreSearchDescription version =\"2.0\">\r\n"
            "<searchID>1</searchID>\r\n"
            "<scheduleName></scheduleName>\r\n"
            "<scheduleNameLike></scheduleNameLike>\r\n"
            "<scheduleRemarksLike></scheduleRemarksLike>\r\n"
            "<shareProperty>public,private,all</shareProperty>\r\n"
            "<uploader>admin</uploader>\r\n"
            "<moder>admin</moder>\r\n"
            "<orgName></orgName>\r\n"
            "<ScheduleTypeList>\r\n"
            "<scheduleType>selfDefine,daily,weekly,loop,defaultSchedule</scheduleType>\r\n"
            "</ScheduleTypeList>\r\n"
            "<ApproveStateList>\r\n"
            "<approveState>approved,notPass,notApprove</approveState>\r\n"
            "</ApproveStateList>\r\n"
            "<ScheduleModeList>\r\n"
            "<scheduleMode>normal,decode,touch</scheduleMode>\r\n"
            "</ScheduleModeList>\r\n"
            "<TimeSpanList>\r\n"
            "<TimeSpan>\r\n"
            "<startTime>%s</startTime>\r\n"
            "<endTIme>%s</endTime>\r\n"
            "</TimeSpan>\r\n"
            "</TimeSpanList>\r\n"
            "<maxResults>10</maxResults>\r\n"
            "<searchResultsPosition>0</searchResultsPosition>\r\n"
            "</ScheduleMoreSearchDescription>\r\n"
            ,strStartTime,strStopTime);
    }
    else if (nCurSel == 22)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/TerminalMgr/inputPlanCfg/1/inputPlan"); //获取信息发布和HDMI切换计划
    }
    else if (nCurSel == 23)
    {
        SYSTEMTIME st = { 0 };
        GetLocalTime(&st);
        CString strStartTime, strStopTime;
        strStartTime.Format("%04d%02d%02dT%02d:%02d:%02d+08\n",
            st.wYear,
            st.wMonth,
            st.wDay,
            10,
            0,
            0);
        strStopTime.Format("%04d%02d%02dT%02d:%02d:%02d+08\n",
            st.wYear,
            st.wMonth,
            st.wDay,
            10,
            59,
            59);
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Publish/TerminalMgr/inputPlanCfg"); //设置信息发布和HDMI切换计划
        m_csInput.Format("<InputPlanCfg version=\"2.0\">\r\n"\
            "<InputPlan>\r\n"\
            "<planType>daily,weekly</planType>\r\n"\
            "<DailyPlan>\r\n"\
            "<InputSpanList>\r\n"\
            "<InputSpan>\r\n"\
            "<id>1</id>\r\n"\
            "<inputType>HDMI,InfoPublish,VGA</inputType>\r\n"\
            "<beginTime>%s</beginTime>\r\n"\
            "<endTime>%s</endTime>\r\n"\
            "</InputSpan>\r\n"\
            "</InputSpanList> \r\n"\
            "</DailyPlan>\r\n"\
            "<WeeklyPlan>\r\n"\
            "<DayList>\r\n"\
            "<Day>\r\n"\
            "<id>1</id>\r\n"\
            "<dayOfWeek>monday</dayOfWeek>\r\n"\
            "<InputSpanList>\r\n"\
            "<InputSpan>\r\n"\
            "<id>1</id>\r\n"\
            "<inputType>HDMI,InfoPublish,VGA</inputType>\r\n"\
            "<beginTime>%s</beginTime>\r\n"\
            "<endTime>%s</endTime>\r\n"\
            "</InputSpan>\r\n"\
            "</InputSpanList>\r\n"\
            "</Day>\r\n"\
            "</DayList>\r\n"\
            "</WeeklyPlan>\r\n"\
            "</InputPlan>\r\n"\
            "<OperateParam>\r\n"\
            "<operateType>byTerminal,byGroup,byOrg</operateType>\r\n"\
            "<TerminalNoList>\r\n"\
            "<terminalNo>1</terminalNo>\r\n"\
            "</TerminalNoList>\r\n"\
            "<TerminalGroupNoList>\r\n"\
            "<terminalGroupNo>1</terminalGroupNo>\r\n"\
            "</TerminalGroupNoList>\r\n"\
            "<OrgNoList>\r\n"\
            "<orgNo>1</orgNo>\r\n"\
            "</OrgNoList>\r\n"\
            "</OperateParam>\r\n"\
            "</InputPlanCfg>\r\n"
            ,strStartTime,strStopTime,strStartTime,strStopTime);
    }
    else if (nCurSel == 24)
    {
        m_csInput = "";
        m_csCommand.Format("POST /ISAPI/Publish/orgMgr/organization"); //新增组织
        m_csInput.Format("<Organization version=\"2.0\">\r\n"\
            "<id></id>\r\n"\
            "<orgName>orgName1</orgName>\r\n"\
            "<orgRemarks>orgName default</orgRemarks>\r\n"\
            "<belongOrg>1</belongOrg>\r\n"\
            "</Organization>\r\n"
            );
    }
    else if (nCurSel == 25)
    {
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Publish/orgMgr/organization/1"); //设置组织信息
        m_csInput.Format("<Organization version=\"2.0\">\r\n"\
            "<id></id>\r\n"\
            "<orgName>orgName1</orgName>\r\n"\
            "<orgRemarks>orgName default</orgRemarks>\r\n"\
            "<belongOrg>1</belongOrg>\r\n"\
            "</Organization>\r\n"
            );
    }
    else if (nCurSel == 26)
    {
        m_csInput = "";
        m_csCommand.Format("DELETE /ISAPI/Publish/orgMgr/organization/1"); //删除组织
    }
    else if (nCurSel == 27)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/orgMgr/organization/1"); //获取组织
    }

    else if (nCurSel == 28)
    {
        m_csInput = "";
        m_csCommand.Format("POST /ISAPI/Security/users"); //新增用户
        m_csInput.Format("<User version=\"2.0\">\r\n"\
            "<id></id>\r\n"\
            "<userName>user1</userName>\r\n"\
            "<password>12345</password>\r\n"\
            "<userLevel>Administrator,Operator,Viewer</userLevel>\r\n"\
            "<belongOrgNo>1</belongOrgNo>\r\n"\
            "<loginPassword>soft12345</loginPassword>\r\n"\
            "</User>\r\n"
            );
    }
    else if (nCurSel == 29)
    {
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Security/users/1"); //设置用户
        m_csInput.Format("<User version=\"2.0\">\r\n"\
            "<id>1</id>\r\n"\
            "<userName>user1</userName>\r\n"\
            "<password>12345</password>\r\n"\
            "<userLevel>Administrator,Operator,Viewer</userLevel>\r\n"\
            "<belongOrgNo>1</belongOrgNo>\r\n"\
            "<loginPassword>soft12345</loginPassword>\r\n"\
            "</User>\r\n"
            );
    }
    else if (nCurSel == 30)
    {
        m_csInput = "";
        m_csCommand.Format("DELETE /ISAPI/Security/users/1"); //删除用户
    }
    else if (nCurSel == 31)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Security/users/1"); //获取用户
    }
    else if (nCurSel == 32)
    {
        m_csInput = "";
        m_csCommand.Format("PUT /ISAPI/Security/UserPermission/1/remotePermission"); //设置用户权限
        m_csInput.Format("<RemotePermission version=\"2.0\">\r\n"\
            "<materialReview>true</materialReview>\r\n"\
            "<programReview>true</programReview>\r\n"\
            "<uploadMaterial>true</uploadMaterial>\r\n"\
            "<addProgram>true</addProgram>\r\n"\
            "<addSchedule>true</addSchedule>\r\n"\
            "<programPlay>true</programPlay>\r\n"\
            "<terminalMgr>true</terminalMgr>\r\n"\
            "<shopSmart>true</shopSmart>\r\n"\
            "<materialReplace>true</materialReplace>\r\n"\
            "<scheduleRelease>true</scheduleRelease>\r\n"\
            "<scheduleReview>true</scheduleReview>\r\n"\
            "<addTerminal>true</addTerminal>\r\n"\
            "<terminalDispatch>true</terminalDispatch>\r\n"\
            "<addUser>true</addUser>\r\n"\
            "<addOrg>true</addOrg>\r\n"\
            "<logMgr>true</logMgr>\r\n"\
            "<dataUpdate>true</dataUpdate>\r\n"\
            "<insertMessage>true</insertMessage>\r\n"\
            "</RemotePermission>\r\n"
            );
    }
    else if (nCurSel == 33)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Security/UserPermission/1/remotePermission"); //获取用户权限
    }
    else if (nCurSel == 34)
    {
        m_csInput = "";
        m_csCommand.Format("POST /ISAPI/Publish/GerDataMgr/transData"); //抓图
        m_csInput.Format("<TransData version=\"2.0\">\r\n"\
            "<materialNo>1</materialNo >\r\n"\
            "<destType>byTerminal</destType>\r\n"\
            "<TerminalNoList>\r\n"\
            "<terminalNo>1 </terminalNo >\r\n"\
            "</TerminalNoList>\r\n"\
            "<TerminalGroupNoList>\r\n"\
            "<terminalGroupNo>1</terminalGroupNo>\r\n"\
            "</TerminalGroupNoList>\r\n"\
            "<dataType>command</dataType>\r\n"\
            "<sendCommand>startCapture, stopPic</sendCommand>\r\n"\
            "</TransData>\r\n"
            );
    }
    else if (nCurSel == 35)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/HDMgr/Init/1"); //获取硬盘初始化
    }
    else if (nCurSel == 36)
    {
        m_csInput = "";
        m_csCommand.Format("SET /ISAPI/Publish/HDMgr/Init/1"); //设置硬盘初始化
        m_csInput.Format("<HardDiskInit version=\"2.0\">\r\n"\
            "<id>1</id>\r\n"\
            "<initalized>true</initalized>\r\n"\
            "</HardDiskInit>\r\n"
            );
    }
    else if (nCurSel == 37)
    {
        m_csInput = "";
        m_csCommand.Format("GET /ISAPI/Publish/HDMgr/Init/1/status"); //获取硬盘初始化进度
    }
    UpdateData(FALSE);

}


void CDlgInfoXmlCfgWithUrl::OnBnClickedBtnOperate()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpInBuffer = m_csInput.GetBuffer(0);
    struInputParam.dwInBufferSize = m_csInput.GetLength();

    string utf_8 = GB2UTF((char*)struInputParam.lpInBuffer);
    memset(struInputParam.lpInBuffer, 0, sizeof(struInputParam.lpInBuffer));
    struInputParam.lpInBuffer = (void*)utf_8.c_str();
    struInputParam.dwInBufferSize = utf_8.length();


    struInputParam.lpRequestUrl = m_csCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = m_csCommand.GetLength();

    char szStatusBuff[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);

    memset(m_pOutBuf, 0, XML_OUT_LEN);
    struOutputParam.lpOutBuffer = m_pOutBuf;
    struOutputParam.dwOutBufferSize = XML_OUT_LEN;
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = 1024;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
    m_csOutput = "";
    string str_gb2312 = UTF2GB(m_pOutBuf);
    m_csOutput = str_gb2312.c_str();


    UpdateData(FALSE);
}
