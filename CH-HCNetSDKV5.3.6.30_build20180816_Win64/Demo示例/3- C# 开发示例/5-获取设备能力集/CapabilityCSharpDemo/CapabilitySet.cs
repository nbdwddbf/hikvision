using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace CapabilityCSharpDemo
{
    public partial class FormCapability : Form
    {
        public Int32 m_lUserID = -1;
        private bool m_bInitSDK = false;
        private uint iLastErr = 0;
        private string strErr;
        private uint m_dwAbilityType = 0;
        private string xmlInput;

        public FormCapability()
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

        private string GetErrorDescription(uint iErrCode)
        {
            string strDescription = "";
            switch(iErrCode)
            {
                case 1000:
                    strDescription = "设备不支持该能力节点的获取";
                    break;
                case 1001:
                    strDescription = "输出内存不足";
                    break;
                case 1002:
                    strDescription = "无法找到对应的本地xml";
                    break;
                case 1003:
                    strDescription = "加载本地xml出错";
                    break;
                case 1004:
                    strDescription = "设备能力数据格式错误";
                    break;
                case 1005:
                    strDescription = "能力集类型错误";
                    break;
                case 1006:
                    strDescription = "XML能力节点格式错误";
                    break;
                case 1007:
                    strDescription = "输入的能力XML节点值错误";
                    break;
                case 1008:
                    strDescription = "XML版本不匹配";
                    break;
                default:
                    break;        
            }
            return strDescription;   
        }

        private void btnGet_Click(object sender, EventArgs e)
        {
            IntPtr pInBuf;
            Int32 nSize;
            if (xmlInput == null)
            {
                pInBuf = IntPtr.Zero;
                nSize = 0;
            }
            else
            {
                nSize = xmlInput.Length;
                pInBuf = Marshal.AllocHGlobal(nSize);
                pInBuf = Marshal.StringToHGlobalAnsi(xmlInput);
            }

            int XML_ABILITY_OUT_LEN = 3 * 1024 * 1024;
            IntPtr pOutBuf = Marshal.AllocHGlobal(XML_ABILITY_OUT_LEN);

            if (!CHCNetSDK.NET_DVR_GetDeviceAbility(m_lUserID, m_dwAbilityType, pInBuf, (uint)nSize, pOutBuf, (uint)XML_ABILITY_OUT_LEN))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_GetDeviceAbility failed, error code= " + iLastErr + "\r\n" + GetErrorDescription(iLastErr);
                //获取设备能力集失败，输出错误号 Failed to get the capability set and output the error code
                textBoxCapability.Text = strErr;
            }
            else
            {
                string strOutBuf = Marshal.PtrToStringAnsi(pOutBuf, XML_ABILITY_OUT_LEN);
                strOutBuf = strOutBuf.Replace(">\n<", ">\r\n<");
                textBoxCapability.Text = strOutBuf; 
            }
            Marshal.FreeHGlobal(pInBuf); 
            Marshal.FreeHGlobal(pOutBuf); 
        }

        private void FormCapability_Load(object sender, EventArgs e)
        {

        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            if (m_lUserID < 0)
            {
                string DVRIPAddress = textBoxIP.Text;
                Int16 DVRPortNumber = Int16.Parse(textBoxPort.Text);
                string DVRUserName = textBoxUserName.Text;
                string DVRPassword = textBoxPassword.Text;

                CHCNetSDK.NET_DVR_DEVICEINFO_V30 m_struDeviceInfo = new CHCNetSDK.NET_DVR_DEVICEINFO_V30();
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
                    comboBoxCapability.SelectedIndex = 0;
                    btnLogin.Text = "注销 Logout";
                }
            }
            else
            {
                if (!CHCNetSDK.NET_DVR_Logout(m_lUserID))
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    strErr = "NET_DVR_Logout failed, error code= " + iLastErr; //注销登录失败，输出错误号 Failed to logout and output the error code
                    MessageBox.Show(strErr);
                }
                else
                {
                    btnLogin.Text = "登录 Login";
                    m_lUserID = -1;
                    comboBoxCapability.SelectedIndex = -1;
                    comboBoxCapability.Text = "";
                    textBoxCapability.Text = "";
                }
            }
        }

        private void comboBoxCapability_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBoxCapability.SelectedIndex)
            {
                case 0:	//软硬件能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_SOFTHARDWARE_ABILITY;
                    break;
                case 1:	//Wifi能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_NETWORK_ABILITY;
                    break;
                case 2: //编码能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_ENCODE_ALL_ABILITY_V20;
                    xmlInput = "<AudioVideoCompressInfo><AudioChannelNumber>1</AudioChannelNumber><VoiceTalkChannelNumber>1</VoiceTalkChannelNumber><VideoChannelNumber>1</VideoChannelNumber></AudioVideoCompressInfo>";
                    break;
                case 3:	//设备前端参数能力
                    m_dwAbilityType = CHCNetSDK.IPC_FRONT_PARAMETER_V20;
                    xmlInput = "<CAMERAPARA><ChannelNumber>1</ChannelNumber></CAMERAPARA>";
                    break;
                case 4:	//Raid能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_RAID_ABILITY;
                    break;
                case 5:	//设备报警能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_ALARM_ABILITY;
                    xmlInput = "<AlarmAbility version='2.0'><channelID>1</channelID></AlarmAbility>";
                    break;
                case 6:	//设备数字通道能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_DYNCHAN_ABILITY;
                    xmlInput = "<DynChannelAbility version='2.0'><channelNO>1</channelNO></DynChannelAbility>";
                    break;
                case 7: //设备用户管理参数能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_USER_ABILITY;
                    xmlInput = "<UserAbility version='2.0'/>"; 
                    break;
                case 8: //设备网络应用参数能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_NETAPP_ABILITY;
                    xmlInput = "<NetAppAbility version='2.0'></NetAppAbility>";
                    break;
                case 9: //设备图像参数能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_VIDEOPIC_ABILITY;
                    xmlInput = "<VideoPicAbility version='2.0'><channelNO>1</channelNO></VideoPicAbility>";
                    break;
                case 10: //设备JPEG抓图能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_JPEG_CAP_ABILITY;
                    xmlInput = "<JpegCaptureAbility version='2.0'><channelNO>1</channelNO></JpegCaptureAbility>";
                    break;
                case 11: //设备RS232和RS485串口能力
                    m_dwAbilityType = CHCNetSDK.DEVICE_SERIAL_ABILITY;
                    xmlInput = "<SerialAbility version='2.0'/>";
                    break;
                case 12: //报警事件处理能力集
                    m_dwAbilityType = CHCNetSDK.DEVICE_ABILITY_INFO;
                    xmlInput = "<EventAbility version='2.0'><channelNO>1</channelNO></EventAbility>";
                    break;             
                default:
                    m_dwAbilityType = 0;
                    break;
            }
            textBoxCapability.Text = "";
        }
    }
}
