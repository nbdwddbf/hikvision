using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace DecoderCSharpDemo
{
    public partial class DynnamicDecode : Form
    {
        public Int32 m_lUserID = -1;
        public uint dwDecChanNum;
        private uint iLastErr = 0;
        private string strErr;
        private CHCNetSDK.NET_DVR_IPC_PROTO_LIST m_struProtoList = new CHCNetSDK.NET_DVR_IPC_PROTO_LIST();
        private CHCNetSDK.NET_DVR_DEC_STREAM_DEV_EX m_struStreamDev = new CHCNetSDK.NET_DVR_DEC_STREAM_DEV_EX();
        private CHCNetSDK.NET_DVR_PU_STREAM_URL m_struStreamURL = new CHCNetSDK.NET_DVR_PU_STREAM_URL();
        private CHCNetSDK.NET_DVR_DEC_DDNS_DEV m_struStreamDDNS = new CHCNetSDK.NET_DVR_DEC_DDNS_DEV();

        public DynnamicDecode()
        {
            InitializeComponent();
        }        

        private void DynnamicDecode_Load(object sender, EventArgs e)
        {
            if (!CHCNetSDK.NET_DVR_GetIPCProtoList(m_lUserID, ref m_struProtoList))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_GetIPCProtoList failed, error code= " + iLastErr;
                //获取设备支持的IPC协议表，输出错误号 Failed to get the IPC protocol list and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                for (int i = 0; i < (int)m_struProtoList.dwProtoNum; i++)
                {
                    comboBoxFactory.Items.Add(m_struProtoList.struProto[i].byDescribe);
                }                
            }
            if (comboBoxFactory.Items.Count != 0)
            {
                comboBoxFactory.SelectedIndex = 0;
            }

            comboBoxStreamMode.SelectedIndex = 0;
            comboBoxChanType.SelectedIndex = 0;
            comboBoxTransType.SelectedIndex = 0;
            comboBoxStreamType.SelectedIndex = 0;
            comboBoxDomainType.SelectedIndex = 0;
            comboBoxFactory_D.SelectedIndex = 0;
            comboBoxChanType_D.SelectedIndex = 0;
            comboBoxTransType_D.SelectedIndex = 0;
            comboBoxStreamType_D.SelectedIndex = 0;
            comboBoxSeverProcotol.SelectedIndex = 0;

            //获取通道信息
            btnChanInfo_Click(sender, e);
        }

        private void comboBoxStreamMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBoxStreamMode.SelectedIndex)
            { 
                case 0:
                    groupBoxIPMode.Enabled = true;
                    groupBoxDomain.Enabled = false;
                    groupBoxURL.Enabled = false;
                    checkBoxStreamSever.Enabled = true;
                    break;               
                case 1:
                    groupBoxIPMode.Enabled = false;
                    groupBoxDomain.Enabled = false;
                    groupBoxURL.Enabled = true;
                    checkBoxStreamSever.Enabled = false;
                    break;
                case 2:
                    groupBoxIPMode.Enabled = false;
                    groupBoxDomain.Enabled = true;
                    groupBoxURL.Enabled = false;
                    checkBoxStreamSever.Enabled = true;
                    break;
                default:
                    break;
            }
        }

        private void checkBoxStreamSever_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxStreamSever.Checked)
            {
                groupBoxStreamServer.Enabled = true;
            }
            else
            {
                groupBoxStreamServer.Enabled = false;
            }
                
        }

        private void comboBoxChanType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxChanType.SelectedIndex == 2)
            {
                label4.Text = "流ID:";
            }
            else
            {
                label4.Text = "远程设备通道号:";            
            }
        }

        private void comboBoxChanType_D_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxChanType_D.SelectedIndex == 2)
            {
                label17.Text = "流ID:";
            }
            else
            {
                label17.Text = "远程设备通道号:";
            }
        }

        private void btnStartDecode_Click(object sender, EventArgs e)
        {
            CHCNetSDK.NET_DVR_PU_STREAM_CFG_V41 m_struStreamCfgV41 = new CHCNetSDK.NET_DVR_PU_STREAM_CFG_V41();
            m_struStreamCfgV41.dwSize = (uint)Marshal.SizeOf(m_struStreamCfgV41);
            m_struStreamCfgV41.byStreamMode = (byte)(comboBoxStreamMode.SelectedIndex + 1);

            //通过IP地址或者域名从设备或者流媒体服务器取流
            if (m_struStreamCfgV41.byStreamMode == 1)
            {
                m_struStreamDev.struDevChanInfo.byChanType = (byte)comboBoxChanType.SelectedIndex;
                if (m_struStreamDev.struDevChanInfo.byChanType == 2)
                {
                    m_struStreamDev.struDevChanInfo.byStreamId = textBoxChanNo.Text;
                }
                else
                {
                    m_struStreamDev.struDevChanInfo.dwChannel = uint.Parse(textBoxChanNo.Text);
                    m_struStreamDev.struDevChanInfo.byChannel = byte.Parse(textBoxChanNo.Text);
                }
                m_struStreamDev.struDevChanInfo.byAddress = textBoxDevIP.Text;
                m_struStreamDev.struDevChanInfo.wDVRPort = ushort.Parse(textBoxDevPort.Text);
                m_struStreamDev.struDevChanInfo.byTransProtocol = (byte)comboBoxTransType.SelectedIndex;
                m_struStreamDev.struDevChanInfo.byTransMode = (byte)comboBoxStreamType.SelectedIndex;
                m_struStreamDev.struDevChanInfo.byFactoryType = (byte)m_struProtoList.struProto[comboBoxFactory.SelectedIndex].dwType;
                m_struStreamDev.struDevChanInfo.sUserName = textBoxUserName.Text;
                m_struStreamDev.struDevChanInfo.sPassword = textBoxPassword.Text;
                if (checkBoxStreamSever.Checked)
                {
                    m_struStreamDev.struStreamMediaSvrCfg.byValid = 1;
                    m_struStreamDev.struStreamMediaSvrCfg.byAddress = textBoxSeverIP.Text;
                    m_struStreamDev.struStreamMediaSvrCfg.wDevPort = ushort.Parse(textBoxServerPort.Text);
                    m_struStreamDev.struStreamMediaSvrCfg.byTransmitType = (byte)comboBoxSeverProcotol.SelectedIndex;
                }
                else
                {
                    m_struStreamDev.struStreamMediaSvrCfg.byValid = 0;
                }

                uint dwUnionSize = (uint)Marshal.SizeOf(m_struStreamCfgV41.uDecStreamMode);
                IntPtr ptrStreamUnion = Marshal.AllocHGlobal((Int32)dwUnionSize);
                Marshal.StructureToPtr(m_struStreamDev, ptrStreamUnion, false);
                m_struStreamCfgV41.uDecStreamMode = (CHCNetSDK.NET_DVR_DEC_STREAM_MODE)Marshal.PtrToStructure(ptrStreamUnion, typeof(CHCNetSDK.NET_DVR_DEC_STREAM_MODE));
                Marshal.FreeHGlobal(ptrStreamUnion);
            }

            //通过URL从设备或者流媒体服务器取流
            if (m_struStreamCfgV41.byStreamMode == 2)
            {
                m_struStreamURL.byEnable = 1;
                m_struStreamURL.strURL = textBoxURL.Text;

                uint dwUnionSize = (uint)Marshal.SizeOf(m_struStreamCfgV41.uDecStreamMode);
                IntPtr ptrStreamUnion = Marshal.AllocHGlobal((Int32)dwUnionSize);
                Marshal.StructureToPtr(m_struStreamURL, ptrStreamUnion, false);
                m_struStreamCfgV41.uDecStreamMode = (CHCNetSDK.NET_DVR_DEC_STREAM_MODE)Marshal.PtrToStructure(ptrStreamUnion, typeof(CHCNetSDK.NET_DVR_DEC_STREAM_MODE));
                Marshal.FreeHGlobal(ptrStreamUnion);
            }

            //通过动态域名解析从设备或者流媒体服务器取流
            if (m_struStreamCfgV41.byStreamMode == 3)
            {
                m_struStreamDDNS.struDdnsInfo.byChanType = (byte)comboBoxChanType_D.SelectedIndex;
                if (m_struStreamDDNS.struDdnsInfo.byChanType == 2)
                {
                    m_struStreamDDNS.struDdnsInfo.byStreamId = textBoxChanNo_D.Text;
                }
                else
                {
                    m_struStreamDDNS.struDdnsInfo.dwChannel = uint.Parse(textBoxChanNo_D.Text);
                }
                m_struStreamDDNS.struDdnsInfo.byDevAddress = textBoxDevDomain.Text;
                m_struStreamDDNS.struDdnsInfo.byTransProtocol = (byte)comboBoxTransType_D.SelectedIndex;
                m_struStreamDDNS.struDdnsInfo.byTransMode = (byte)comboBoxStreamType_D.SelectedIndex;
                m_struStreamDDNS.struDdnsInfo.byDdnsType = 4;
                m_struStreamDDNS.struDdnsInfo.byDdnsAddress = textBoxDDNSAddr.Text;
                m_struStreamDDNS.struDdnsInfo.wDdnsPort = ushort.Parse(textBoxDDNSPort.Text);
                m_struStreamDDNS.struDdnsInfo.byFactoryType = (byte)m_struProtoList.struProto[comboBoxFactory_D.SelectedIndex].dwType;
                m_struStreamDDNS.struDdnsInfo.sUserName = textBoxUserName_D.Text;
                m_struStreamDDNS.struDdnsInfo.sPassword = textBoxPassword_D.Text;
                m_struStreamDDNS.struDdnsInfo.wDevPort = ushort.Parse(textBoxDevPort_D.Text);

                if (checkBoxStreamSever.Checked)
                {
                    m_struStreamDDNS.struMediaServer.byValid = 1;
                    m_struStreamDDNS.struMediaServer.byAddress = textBoxSeverIP.Text;
                    m_struStreamDDNS.struMediaServer.wDevPort = ushort.Parse(textBoxServerPort.Text);
                    m_struStreamDDNS.struMediaServer.byTransmitType = (byte)comboBoxSeverProcotol.SelectedIndex;
                }
                else
                {
                    m_struStreamDDNS.struMediaServer.byValid = 0;
                }

                uint dwUnionSize = (uint)Marshal.SizeOf(m_struStreamCfgV41.uDecStreamMode);
                IntPtr ptrStreamUnion = Marshal.AllocHGlobal((Int32)dwUnionSize);
                Marshal.StructureToPtr(m_struStreamDDNS, ptrStreamUnion, false);
                m_struStreamCfgV41.uDecStreamMode = (CHCNetSDK.NET_DVR_DEC_STREAM_MODE)Marshal.PtrToStructure(ptrStreamUnion, typeof(CHCNetSDK.NET_DVR_DEC_STREAM_MODE));
                Marshal.FreeHGlobal(ptrStreamUnion);
            }

            if (!CHCNetSDK.NET_DVR_MatrixStartDynamic_V41(m_lUserID, dwDecChanNum, ref m_struStreamCfgV41))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_MatrixStartDynamic_V41 failed, error code= " + iLastErr;
                //启动动态解码失败，输出错误号 Failed to start dynamic decoding and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                MessageBox.Show("Successful to start dynamic decoding!");
            }
        }

        private void btnStopDecode_Click(object sender, EventArgs e)
        {
            if (!CHCNetSDK.NET_DVR_MatrixStopDynamic(m_lUserID, dwDecChanNum))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_MatrixStopDynamic failed, error code= " + iLastErr;
                //停止动态解码失败，输出错误号 Failed to stop dynamic decoding and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                MessageBox.Show("Successful to stop dynamic decoding!");
            }
        }

        private void btnChanInfo_Click(object sender, EventArgs e)
        {
            CHCNetSDK.NET_DVR_MATRIX_DEC_CHAN_INFO_V41 m_struDecChanInfo = new CHCNetSDK.NET_DVR_MATRIX_DEC_CHAN_INFO_V41();
            
            if (!CHCNetSDK.NET_DVR_MatrixGetDecChanInfo_V41(m_lUserID, dwDecChanNum, ref m_struDecChanInfo))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_MatrixGetDecChanInfo_V41 failed, error code= " + iLastErr;
                //获取当前解码通道信息失败，输出错误号 Failed to get the decoding info of the channel and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                comboBoxStreamMode.SelectedIndex = m_struDecChanInfo.byStreamMode - 1;
                //通过IP地址或者域名从设备或者流媒体服务器取流
                if (m_struDecChanInfo.byStreamMode == 1)
                {
                    uint dwUnionSize = (uint)Marshal.SizeOf(m_struDecChanInfo.uDecStreamMode);
                    IntPtr ptrStreamUnion = Marshal.AllocHGlobal((Int32)dwUnionSize);
                    Marshal.StructureToPtr(m_struDecChanInfo.uDecStreamMode, ptrStreamUnion, false);
                    m_struStreamDev = (CHCNetSDK.NET_DVR_DEC_STREAM_DEV_EX)Marshal.PtrToStructure(ptrStreamUnion, typeof(CHCNetSDK.NET_DVR_DEC_STREAM_DEV_EX));
                    Marshal.FreeHGlobal(ptrStreamUnion);

                    comboBoxChanType.SelectedIndex = m_struStreamDev.struDevChanInfo.byChanType;
                    if (m_struStreamDev.struDevChanInfo.byChanType == 2)
                    {
                        textBoxChanNo.Text = m_struStreamDev.struDevChanInfo.byStreamId;
                    }
                    else
                    {
                        textBoxChanNo.Text = Convert.ToString(m_struStreamDev.struDevChanInfo.dwChannel);
                    }

                    textBoxDevIP.Text = m_struStreamDev.struDevChanInfo.byAddress;
                    textBoxDevPort.Text = Convert.ToString(m_struStreamDev.struDevChanInfo.wDVRPort);
                    comboBoxTransType.SelectedIndex = m_struStreamDev.struDevChanInfo.byTransProtocol;
                    comboBoxStreamType.SelectedIndex = m_struStreamDev.struDevChanInfo.byTransMode;
                    for (int i = 0; i < (int)m_struProtoList.dwProtoNum; i++)
                    {
                        //设备（厂家）协议类型,通过NET_DVR_GetIPCProtoList获取
                        if (m_struProtoList.struProto[i].dwType == m_struStreamDev.struDevChanInfo.byFactoryType)
                        {
                            comboBoxFactory.SelectedIndex = i;
                        }
                    }                    
                    textBoxUserName.Text = m_struStreamDev.struDevChanInfo.sUserName;
                    textBoxPassword.Text = m_struStreamDev.struDevChanInfo.sPassword;

                    if (m_struStreamDev.struStreamMediaSvrCfg.byValid==1)
                    {
                        checkBoxStreamSever.Checked = true;
                        textBoxSeverIP.Text = m_struStreamDev.struStreamMediaSvrCfg.byAddress;
                        textBoxServerPort.Text = Convert.ToString(m_struStreamDev.struStreamMediaSvrCfg.wDevPort);
                        comboBoxSeverProcotol.SelectedIndex = m_struStreamDev.struStreamMediaSvrCfg.byTransmitType;
                    }
                    else
                    {
                        checkBoxStreamSever.Checked = false;
                    }
                }

                //通过URL从设备或者流媒体服务器取流
                if (m_struDecChanInfo.byStreamMode == 2)
                {
                    uint dwUnionSize = (uint)Marshal.SizeOf(m_struDecChanInfo.uDecStreamMode);
                    IntPtr ptrStreamUnion = Marshal.AllocHGlobal((Int32)dwUnionSize);
                    Marshal.StructureToPtr(m_struDecChanInfo.uDecStreamMode, ptrStreamUnion, false);
                    m_struStreamURL = (CHCNetSDK.NET_DVR_PU_STREAM_URL)Marshal.PtrToStructure(ptrStreamUnion, typeof(CHCNetSDK.NET_DVR_PU_STREAM_URL));
                    Marshal.FreeHGlobal(ptrStreamUnion);

                    if (m_struStreamURL.byEnable == 1)
                    {
                        textBoxURL.Text = m_struStreamURL.strURL;                    
                    }    
                }

                //通过动态域名解析从设备或者流媒体服务器取流
                if (m_struDecChanInfo.byStreamMode == 3)
                {
                    uint dwUnionSize = (uint)Marshal.SizeOf(m_struDecChanInfo.uDecStreamMode);
                    IntPtr ptrStreamUnion = Marshal.AllocHGlobal((Int32)dwUnionSize);
                    Marshal.StructureToPtr(m_struDecChanInfo.uDecStreamMode, ptrStreamUnion, false);
                    m_struStreamDDNS = (CHCNetSDK.NET_DVR_DEC_DDNS_DEV)Marshal.PtrToStructure(ptrStreamUnion, typeof(CHCNetSDK.NET_DVR_DEC_DDNS_DEV));
                    Marshal.FreeHGlobal(ptrStreamUnion);

                    comboBoxChanType_D.SelectedIndex = m_struStreamDDNS.struDdnsInfo.byChanType;
                    if (m_struStreamDDNS.struDdnsInfo.byChanType == 2)
                    {
                        textBoxChanNo_D.Text = m_struStreamDDNS.struDdnsInfo.byStreamId;
                    }
                    else
                    {
                        textBoxChanNo_D.Text = Convert.ToString(m_struStreamDDNS.struDdnsInfo.dwChannel);
                    }

                    textBoxDevDomain.Text = m_struStreamDDNS.struDdnsInfo.byDevAddress;
                    comboBoxTransType_D.SelectedIndex = m_struStreamDDNS.struDdnsInfo.byTransProtocol;
                    comboBoxStreamType_D.SelectedIndex = m_struStreamDDNS.struDdnsInfo.byTransMode;
                    textBoxDDNSAddr.Text = m_struStreamDDNS.struDdnsInfo.byDdnsAddress;
                    textBoxDDNSPort.Text = Convert.ToString(m_struStreamDDNS.struDdnsInfo.wDdnsPort);

                    for (int i = 0; i < (int)m_struProtoList.dwProtoNum; i++)
                    {
                        //设备（厂家）协议类型,通过NET_DVR_GetIPCProtoList获取
                        if (m_struProtoList.struProto[i].dwType == m_struStreamDDNS.struDdnsInfo.byFactoryType)
                        {
                            comboBoxFactory_D.SelectedIndex = i;
                        }
                    }

                    textBoxUserName_D.Text = m_struStreamDDNS.struDdnsInfo.sUserName;
                    textBoxPassword_D.Text = m_struStreamDDNS.struDdnsInfo.sPassword;
                    textBoxDevPort_D.Text = Convert.ToString(m_struStreamDDNS.struDdnsInfo.wDevPort);

                    if (m_struStreamDDNS.struMediaServer.byValid == 1)
                    {
                        checkBoxStreamSever.Checked = true;
                        textBoxSeverIP.Text = m_struStreamDDNS.struMediaServer.byAddress;
                        textBoxServerPort.Text = Convert.ToString(m_struStreamDDNS.struMediaServer.wDevPort);
                        comboBoxSeverProcotol.SelectedIndex = m_struStreamDDNS.struMediaServer.byTransmitType;
                    }
                    else
                    {
                        checkBoxStreamSever.Checked = false;
                    }
                }
            }
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
            this.Dispose(); 
        }
    }
}
