using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace ConfigCSharpDemo
{
    public partial class ConfigCSharpDemo : Form
    {
        public Int32 m_lUserID = -1;
        private bool m_bInitSDK = false;
        private uint iLastErr = 0;
        private string strErr;

        public CHCNetSDK.NET_DVR_DEVICECFG_V40 m_struDeviceCfg;
        public CHCNetSDK.NET_DVR_NETCFG_V30 m_struNetCfg;
        public CHCNetSDK.NET_DVR_TIME m_struTimeCfg;
        public CHCNetSDK.NET_DVR_DEVICEINFO_V30 m_struDeviceInfo;
        public CHCNetSDK.NET_DVR_IPPARACFG_V40 m_struIpParaCfgV40;

        [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct CHAN_INFO
        {
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 256, ArraySubType = UnmanagedType.U4)]
            public Int32[] lChannelNo;
            public void Init()
            {
                lChannelNo = new Int32[256];
                for (int i = 0; i < 256; i++)
                    lChannelNo[i] = -1;
            }
        }

        public CHAN_INFO m_struChanNoInfo= new CHAN_INFO();

        public ConfigCSharpDemo()
        {
            InitializeComponent();

            //SDK初始化
            m_bInitSDK = CHCNetSDK.NET_DVR_Init();
            if (m_bInitSDK == false)
            {
                MessageBox.Show("NET_DVR_Init error!");
                return;
            }
            else
            {
                //保存SDK日志 To save the SDK log
                CHCNetSDK.NET_DVR_SetLogToFile(3, "C:\\SdkLog\\", true);
            }
        }

        /***清空参数***/
        public void ParameterClear()
        {
            textBoxDevName.Text = "";
            textBoxDevType.Text = "";
            textBoxANum.Text = "";
            textBoxIPNum.Text = "";
            textBoxZeroNum.Text = "";
            textBoxNetNum.Text = "";
            textBoxAlarmInNum.Text = "";
            textBoxAlarmOutNum.Text = "";
            textBoxDevSerial.Text = "";
            textBoxDevVersion.Text = "";  
            textBoxIPAddr.Text = "";  
            textBoxGateWay.Text = "";  
            textBoxSubMask.Text = "";  
            textBoxDns.Text = "";
            textBoxHostIP.Text = "";
            textBoxHostPort.Text = "";
            textBoxHttpCfg.Text = "";  
            textBoxSdkCfg.Text = "";  
            checkBoxDhcp.Checked = false;
            checkBoxPPPoe.Checked = false;
            textBoxPPPoeName.Text = "";
            textBoxPPPoEPsw.Text = "";  
            TextEnable(true);
            comboBoxChan.Items.Clear();
            comboBoxChan.SelectedIndex = -1;
            comboBoxChan.Text = "";
        }

        /***获取通道***/
        public void GetDevChanList()
        {
            int i = 0, j = 0;
            string str;
            m_struChanNoInfo.Init();

            if (m_struDeviceInfo.byIPChanNum > 0)
            {
                uint dwSize = (uint)Marshal.SizeOf(m_struIpParaCfgV40);

                IntPtr ptrIpParaCfgV40 = Marshal.AllocHGlobal((Int32)dwSize);
                Marshal.StructureToPtr(m_struIpParaCfgV40, ptrIpParaCfgV40, false);

                uint dwReturn = 0;
                if (!CHCNetSDK.NET_DVR_GetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_GET_IPPARACFG_V40, -1, ptrIpParaCfgV40, dwSize, ref dwReturn))
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    strErr = "NET_DVR_GET_IPPARACFG_V40 failed, error code= " + iLastErr;
                    //获取IP通道信息失败，输出错误号 Failed to Get IP Channel info and output the error code
                    MessageBox.Show(strErr);
                }
                else
                {
                    m_struIpParaCfgV40 = (CHCNetSDK.NET_DVR_IPPARACFG_V40)Marshal.PtrToStructure(ptrIpParaCfgV40, typeof(CHCNetSDK.NET_DVR_IPPARACFG_V40));

                    //获取可用的模拟通道
                    for (i = 0; i < m_struIpParaCfgV40.dwAChanNum; i++)
                    {
                        if (m_struIpParaCfgV40.byAnalogChanEnable[i]==1)
                        {
                            str = String.Format("通道{0}", i+1);
                            comboBoxChan.Items.Add(str);
                            m_struChanNoInfo.lChannelNo[j] = i + m_struDeviceInfo.byStartChan;
                            j++;
                        }
                    }

                    //获取在线的IP通道
                    byte byStreamType;
                    for (i = 0; i < m_struIpParaCfgV40.dwDChanNum; i++)
                    {
                        byStreamType = m_struIpParaCfgV40.struStreamMode[i].byGetStreamType;
                        CHCNetSDK.NET_DVR_STREAM_MODE m_struStreamMode = new CHCNetSDK.NET_DVR_STREAM_MODE();
                        dwSize = (uint)Marshal.SizeOf(m_struStreamMode);
                        switch (byStreamType)
                        {
                            //0- 直接从设备取流 0- get stream from device directly
                            case 0:
                                IntPtr ptrChanInfo = Marshal.AllocHGlobal((Int32)dwSize);
                                Marshal.StructureToPtr(m_struIpParaCfgV40.struStreamMode[i].uGetStream, ptrChanInfo, false);
                                CHCNetSDK.NET_DVR_IPCHANINFO m_struChanInfo = new CHCNetSDK.NET_DVR_IPCHANINFO();
                                m_struChanInfo = (CHCNetSDK.NET_DVR_IPCHANINFO)Marshal.PtrToStructure(ptrChanInfo, typeof(CHCNetSDK.NET_DVR_IPCHANINFO));

                                //列出IP通道 List the IP channel
                                if (m_struChanInfo.byEnable==1)
                                {
                                    str = String.Format("IP通道{0}", i + 1);
                                    comboBoxChan.Items.Add(str);
                                    m_struChanNoInfo.lChannelNo[j] = i + (int)m_struIpParaCfgV40.dwStartDChan;
                                    j++;
                                }
                                Marshal.FreeHGlobal(ptrChanInfo);
                                break;
                            //6- 直接从设备取流扩展 6- get stream from device directly(extended)
                            case 6:                            
                                IntPtr ptrChanInfoV40 = Marshal.AllocHGlobal((Int32)dwSize);
                                Marshal.StructureToPtr(m_struIpParaCfgV40.struStreamMode[i].uGetStream, ptrChanInfoV40, false);
                                CHCNetSDK.NET_DVR_IPCHANINFO_V40 m_struChanInfoV40 = new CHCNetSDK.NET_DVR_IPCHANINFO_V40();
                                m_struChanInfoV40 = (CHCNetSDK.NET_DVR_IPCHANINFO_V40)Marshal.PtrToStructure(ptrChanInfoV40, typeof(CHCNetSDK.NET_DVR_IPCHANINFO_V40));

                                //列出IP通道 List the IP channel
                                if (m_struChanInfoV40.byEnable == 1)
                                {
                                    str = String.Format("IP通道{0}", i + 1);
                                    comboBoxChan.Items.Add(str);
                                    m_struChanNoInfo.lChannelNo[j] = i + (int)m_struIpParaCfgV40.dwStartDChan;
                                    j++;
                                }
                                Marshal.FreeHGlobal(ptrChanInfoV40);
                                break;
                            default:
                                break;
                        }
                    }
                }
                Marshal.FreeHGlobal(ptrIpParaCfgV40);
            }
            else
            {
                for (i = 0; i < m_struDeviceInfo.byChanNum; i++)
                {
                    str = String.Format("通道{0}", i + 1);
                    comboBoxChan.Items.Add(str);
                    m_struChanNoInfo.lChannelNo[j] = i + m_struDeviceInfo.byStartChan;
                    j++;                    
                }
            }
            comboBoxChan.SelectedIndex = 0;
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            if (m_lUserID < 0)
            {
                if (textBoxIP.Text == "" || textBoxPort.Text == "" ||
                textBoxUserName.Text == "" || textBoxPassword.Text == "")
                {
                    MessageBox.Show("Please input prarameters: ");
                    return;
                }
                string DVRIPAddress = textBoxIP.Text;
                Int16 DVRPortNumber = Int16.Parse(textBoxPort.Text);
                string DVRUserName = textBoxUserName.Text;
                string DVRPassword = textBoxPassword.Text;

                //登录设备 Login the device
                m_lUserID = CHCNetSDK.NET_DVR_Login_V30(DVRIPAddress, DVRPortNumber, DVRUserName, DVRPassword, ref m_struDeviceInfo);
                if (m_lUserID == -1)
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    strErr = "NET_DVR_Login_V30 failed, error code= " + iLastErr; 
                    //登录失败，输出错误号 Failed to login and output the error code
                    MessageBox.Show(strErr);
                    return;
                }
                else
                {
                    btnLogin.Text = "注销登录 Logout";
                    btnDevCfgGet_Click(sender, e);
                    btnNetCfgGet_Click(sender, e);
                    btnTimeGet_Click(sender, e);
                    GetDevChanList();
                }
            }
            else
            {
                //注销登录 Logout the device
                if (!CHCNetSDK.NET_DVR_Logout(m_lUserID))
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    strErr = "NET_DVR_Logout failed, error code= " + iLastErr; //注销登录失败，输出错误号 Failed to logout and output the error code
                    MessageBox.Show(strErr);
                }
                else 
                {
                    btnLogin.Text = "登录设备 Login";
                    m_lUserID = -1;
                    ParameterClear();
                }            
            }

        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            //注销登录 Logout the device           
            CHCNetSDK.NET_DVR_Logout(m_lUserID);

            //释放SDK资源，在程序结束之前调用
            CHCNetSDK.NET_DVR_Cleanup();

            Application.Exit();
        }

        private void btnDevCfg_Click(object sender, EventArgs e)
        {
            byte[] byName = System.Text.Encoding.Default.GetBytes(textBoxDevName.Text);
            m_struDeviceCfg.sDVRName = new byte[32];
            byName.CopyTo(m_struDeviceCfg.sDVRName, 0);

            Int32 nSize = Marshal.SizeOf(m_struDeviceCfg);
            IntPtr ptrDeviceCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struDeviceCfg, ptrDeviceCfg, false);

            if (!CHCNetSDK.NET_DVR_SetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_SET_DEVICECFG_V40, -1, ptrDeviceCfg, (UInt32)nSize))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_SET_DEVICECFG_V40 failed, error code= " + iLastErr;
                //设置设备参数失败，输出错误号 Failed to set the basic parameters of device and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                MessageBox.Show("设置设备参数成功！");
            }

            Marshal.FreeHGlobal(ptrDeviceCfg);
        }

        private void btnDevCfgGet_Click(object sender, EventArgs e)
        {
            UInt32 dwReturn = 0;
            Int32 nSize = Marshal.SizeOf(m_struDeviceCfg);
            IntPtr ptrDeviceCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struDeviceCfg, ptrDeviceCfg, false);
            if (!CHCNetSDK.NET_DVR_GetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_GET_DEVICECFG_V40, -1, ptrDeviceCfg, (UInt32)nSize, ref dwReturn))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_GET_DEVICECFG_V40 failed, error code= " + iLastErr;
                //获取设备参数失败，输出错误号 Failed to get the basic parameters of device and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                m_struDeviceCfg = (CHCNetSDK.NET_DVR_DEVICECFG_V40)Marshal.PtrToStructure(ptrDeviceCfg, typeof(CHCNetSDK.NET_DVR_DEVICECFG_V40));
                
                textBoxDevName.Text = System.Text.Encoding.GetEncoding("GBK").GetString(m_struDeviceCfg.sDVRName);
                textBoxDevType.Text = System.Text.Encoding.UTF8.GetString(m_struDeviceCfg.byDevTypeName);
                textBoxANum.Text = Convert.ToString(m_struDeviceCfg.byChanNum) ;
                textBoxIPNum.Text = Convert.ToString(m_struDeviceCfg.byIPChanNum + 256 * m_struDeviceCfg.byHighIPChanNum);
                textBoxZeroNum.Text = Convert.ToString(m_struDeviceCfg.byZeroChanNum);
                textBoxNetNum.Text = Convert.ToString(m_struDeviceCfg.byNetworkPortNum);
                textBoxAlarmInNum.Text = Convert.ToString(m_struDeviceCfg.byAlarmInPortNum);
                textBoxAlarmOutNum.Text = Convert.ToString(m_struDeviceCfg.byAlarmOutPortNum);
                textBoxDevSerial.Text = System.Text.Encoding.UTF8.GetString(m_struDeviceCfg.sSerialNumber);

                uint iVer1 = (m_struDeviceCfg.dwSoftwareVersion >> 24) & 0xFF;
                uint iVer2 = (m_struDeviceCfg.dwSoftwareVersion >> 16) & 0xFF;
                uint iVer3 = m_struDeviceCfg.dwSoftwareVersion & 0xFFFF;
                uint iVer4 = (m_struDeviceCfg.dwSoftwareBuildDate >> 16) & 0xFFFF;
                uint iVer5 = (m_struDeviceCfg.dwSoftwareBuildDate >> 8) & 0xFF;
                uint iVer6 = m_struDeviceCfg.dwSoftwareBuildDate & 0xFF;

                textBoxDevVersion.Text = "V" + iVer1 + "." + iVer2 + "." + iVer3 + " Build " + string.Format("{0:D2}", iVer4) + string.Format("{0:D2}", iVer5) + string.Format("{0:D2}", iVer6);     
            }
            Marshal.FreeHGlobal(ptrDeviceCfg);
        }

        public void TextEnable(bool bIsAble)
        {
            textBoxIPAddr.Enabled = bIsAble;
            textBoxGateWay.Enabled = bIsAble;
            textBoxSubMask.Enabled = bIsAble;
            textBoxDns.Enabled = bIsAble;
        }

        private void btnNetCfgGet_Click(object sender, EventArgs e)
        {
            UInt32 dwReturn = 0;
            Int32 nSize = Marshal.SizeOf(m_struNetCfg);
            IntPtr ptrNetCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struNetCfg, ptrNetCfg, false);

            if (!CHCNetSDK.NET_DVR_GetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_GET_NETCFG_V30, -1, ptrNetCfg, (UInt32)nSize, ref dwReturn))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_GET_NETCFG_V30 failed, error code= " + iLastErr;
                //获取网络参数失败，输出错误号 Failed to get the network parameters and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                m_struNetCfg = (CHCNetSDK.NET_DVR_NETCFG_V30)Marshal.PtrToStructure(ptrNetCfg, typeof(CHCNetSDK.NET_DVR_NETCFG_V30));
                textBoxIPAddr.Text = m_struNetCfg.struEtherNet[0].struDVRIP.sIpV4;
                textBoxGateWay.Text = m_struNetCfg.struGatewayIpAddr.sIpV4;
                textBoxSubMask.Text = m_struNetCfg.struEtherNet[0].struDVRIPMask.sIpV4;
                textBoxDns.Text = m_struNetCfg.struDnsServer1IpAddr.sIpV4;
                textBoxHostIP.Text = m_struNetCfg.struAlarmHostIpAddr.sIpV4;
                textBoxHostPort.Text = Convert.ToString(m_struNetCfg.wAlarmHostIpPort);
                textBoxHttpCfg.Text = Convert.ToString(m_struNetCfg.wHttpPortNo);
                textBoxSdkCfg.Text = Convert.ToString(m_struNetCfg.struEtherNet[0].wDVRPort);

                if (m_struNetCfg.byUseDhcp == 1)
                {
                    checkBoxDhcp.Checked = true;
                    TextEnable(false);
                }
                else
                {
                    checkBoxDhcp.Checked = false;
                }

                if (m_struNetCfg.struPPPoE.dwPPPOE == 1)
                {
                    checkBoxPPPoe.Checked = true;
                    textBoxPPPoeName.Text = System.Text.Encoding.UTF8.GetString(m_struNetCfg.struPPPoE.sPPPoEUser);
                    textBoxPPPoEPsw.Text = m_struNetCfg.struPPPoE.sPPPoEPassword;
                    TextEnable(false);
                }

                else
                {
                    textBoxPPPoeName.Text = "";
                    textBoxPPPoEPsw.Text = "";
                    checkBoxPPPoe.Checked = false;
                }

                if (m_struNetCfg.byUseDhcp == 0 && m_struNetCfg.struPPPoE.dwPPPOE == 0)
                {
                    TextEnable(true);                
                }
            }
            Marshal.FreeHGlobal(ptrNetCfg);
        }

        private void btnNetCfgSet_Click(object sender, EventArgs e)
        {
            m_struNetCfg.struEtherNet[0].struDVRIP.sIpV4 = textBoxIPAddr.Text;
            m_struNetCfg.struGatewayIpAddr.sIpV4 = textBoxGateWay.Text;
            m_struNetCfg.struEtherNet[0].struDVRIPMask.sIpV4 = textBoxSubMask.Text;
            m_struNetCfg.struDnsServer1IpAddr.sIpV4 = textBoxDns.Text;
            m_struNetCfg.wHttpPortNo = UInt16.Parse(textBoxHttpCfg.Text);
            m_struNetCfg.struEtherNet[0].wDVRPort = UInt16.Parse(textBoxSdkCfg.Text);
            m_struNetCfg.struAlarmHostIpAddr.sIpV4 = textBoxHostIP.Text;
            m_struNetCfg.wAlarmHostIpPort = UInt16.Parse(textBoxHostPort.Text);

            if (checkBoxDhcp.Checked)
            {
                if (m_struNetCfg.struPPPoE.dwPPPOE == 1)
                {
                    MessageBox.Show("设备PPPoE已启用，需要先禁用PPPoE才能启动DHCP自动获取IP！");
                    checkBoxDhcp.Checked = false;
                }
                else
                    m_struNetCfg.byUseDhcp = 1;
            }
            else
            {
                m_struNetCfg.byUseDhcp = 0;
            }

            if (checkBoxPPPoe.Checked)
            {
                    m_struNetCfg.struPPPoE.dwPPPOE = 1;
                    byte[] byName = System.Text.Encoding.Default.GetBytes(textBoxPPPoeName.Text);
                    m_struNetCfg.struPPPoE.sPPPoEUser=new byte[32];
                    byName.CopyTo(m_struNetCfg.struPPPoE.sPPPoEUser, 0);
                    m_struNetCfg.struPPPoE.sPPPoEPassword = textBoxPPPoEPsw.Text;
            }
            else
            {
                m_struNetCfg.struPPPoE.dwPPPOE = 0;
            }

            Int32 nSize = Marshal.SizeOf(m_struNetCfg);
            IntPtr ptrNetCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struNetCfg, ptrNetCfg, false);

            if (!CHCNetSDK.NET_DVR_SetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_SET_NETCFG_V30, -1, ptrNetCfg, (UInt32)nSize))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_SET_NETCFG_V30 failed, error code= " + iLastErr;
                //设置网络参数失败，输出错误号 Failed to set the network parameters and output the error code
                MessageBox.Show(strErr);
            }
            else 
            {
                MessageBox.Show("设置网络参数成功！");
            }
            Marshal.FreeHGlobal(ptrNetCfg);
        }

        private void checkBoxDhcp_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxDhcp.Checked)
            {
                if (checkBoxPPPoe.Checked)
                {
                    checkBoxDhcp.Checked = false;
                    MessageBox.Show("请先禁用PPPoE！");                    
                    return;
                }
                TextEnable(true);
            }
            else
            {
                TextEnable(false);
            }
        }

        private void checkBoxPPPoe_CheckedChanged(object sender, EventArgs e)
        { 
            if (checkBoxPPPoe.Checked)
            {
                if (checkBoxDhcp.Checked)
                {
                    checkBoxPPPoe.Checked = false;
                    MessageBox.Show("请先禁用DHCP！");                    
                    return;                
                }
                textBoxPPPoeName.Enabled = true;
                textBoxPPPoEPsw.Enabled = true;

            }
            else
            {
                textBoxPPPoeName.Enabled = false;
                textBoxPPPoEPsw.Enabled = false;
            }
        }

        private void btnTimeGet_Click(object sender, EventArgs e)
        {
            UInt32 dwReturn = 0;
            Int32 nSize = Marshal.SizeOf(m_struTimeCfg);
            IntPtr ptrTimeCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struTimeCfg, ptrTimeCfg, false);
            if (!CHCNetSDK.NET_DVR_GetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_GET_TIMECFG, -1, ptrTimeCfg, (UInt32)nSize, ref dwReturn))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_GET_TIMECFG failed, error code= " + iLastErr;
                //获取设备时间失败，输出错误号 Failed to get time of the device and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                m_struTimeCfg = (CHCNetSDK.NET_DVR_TIME)Marshal.PtrToStructure(ptrTimeCfg, typeof(CHCNetSDK.NET_DVR_TIME));
                textBoxYear.Text = Convert.ToString(m_struTimeCfg.dwYear);
                textBoxMonth.Text = Convert.ToString(m_struTimeCfg.dwMonth);
                textBoxDay.Text = Convert.ToString(m_struTimeCfg.dwDay);
                textBoxHour.Text = Convert.ToString(m_struTimeCfg.dwHour);
                textBoxMinute.Text = Convert.ToString(m_struTimeCfg.dwMinute);
                textBoxSecond.Text = Convert.ToString(m_struTimeCfg.dwSecond);
            }
            Marshal.FreeHGlobal(ptrTimeCfg);
        }

        private void btnTimeSet_Click(object sender, EventArgs e)
        {
            m_struTimeCfg.dwYear = UInt32.Parse(textBoxYear.Text);
            m_struTimeCfg.dwMonth = UInt32.Parse(textBoxMonth.Text);
            m_struTimeCfg.dwDay = UInt32.Parse(textBoxDay.Text);
            m_struTimeCfg.dwHour = UInt32.Parse(textBoxHour.Text);
            m_struTimeCfg.dwMinute = UInt32.Parse(textBoxMinute.Text);
            m_struTimeCfg.dwSecond = UInt32.Parse(textBoxSecond.Text);

            Int32 nSize = Marshal.SizeOf(m_struTimeCfg);
            IntPtr ptrTimeCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struTimeCfg, ptrTimeCfg, false);

            if (!CHCNetSDK.NET_DVR_SetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_SET_TIMECFG, -1, ptrTimeCfg, (UInt32)nSize))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_SET_TIMECFG failed, error code= " + iLastErr;
                //设置时间失败，输出错误号 Failed to set the time of device and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                MessageBox.Show("校时成功！");
            }

            Marshal.FreeHGlobal(ptrTimeCfg);
        }

        private void btnChanCfg_Click(object sender, EventArgs e)
        {
            ChanConfig dlg = new ChanConfig();
            dlg.m_lUserID = m_lUserID;

            if ((dlg.m_lUserID < 0) || (comboBoxChan.SelectedIndex < 0))
            {
                MessageBox.Show("请先登录设备获取通道！");
                return;
            }

            if (comboBoxChan.SelectedIndex < 0)
            {
                MessageBox.Show("没有获取到设备通道！");
                return;
            }

            dlg.m_lChannel = m_struChanNoInfo.lChannelNo[comboBoxChan.SelectedIndex];
            dlg.m_struDeviceInfo = m_struDeviceInfo;
            dlg.ShowDialog();
        }
    }
}
