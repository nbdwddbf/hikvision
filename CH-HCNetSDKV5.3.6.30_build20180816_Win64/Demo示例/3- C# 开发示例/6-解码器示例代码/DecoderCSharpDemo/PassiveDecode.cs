using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.IO;

namespace DecoderCSharpDemo
{
    public partial class PassiveDecode : Form
    {
        public Int32 m_lUserID = -1;
        public uint dwDecChanNum;
        private uint iLastErr = 0;
        private string strErr;
        private Int32 lPassiveHandle = -1;
        private CHCNetSDK.NET_DVR_MATRIX_PASSIVEMODE m_struPassivePara = new CHCNetSDK.NET_DVR_MATRIX_PASSIVEMODE();
        public Int32 lUserID = -1;
        private int lRealHandle = -1;
        public FileStream hFileHandle = null;
        public int iStreamSize = 0;
        public bool hExitThread = false;
        public Thread filetrd = null;

        public PassiveDecode()
        {
            InitializeComponent();
        }

        private void PassiveDecode_Load(object sender, EventArgs e)
        {
            comboBoxTransProtol.SelectedIndex = 0;
            comboBoxStreamMode.SelectedIndex = 0;
            comboBoxStreamType.SelectedIndex = 0;
            comboBoxRealProtol.SelectedIndex = 0;
        }

        private void btnStartDecode_Click(object sender, EventArgs e)
        {
            m_struPassivePara.wTransProtol = (ushort)comboBoxTransProtol.SelectedIndex; //传输协议：0-TCP，1-UDP，2-MCAST
            m_struPassivePara.wPassivePort = ushort.Parse(textBoxPort.Text);  //TCP或者UDP端口
            m_struPassivePara.byStreamType = (byte)(comboBoxStreamMode.SelectedIndex + 1);  //数据播放模式: 1-实时流, 2-文件流

            lPassiveHandle = CHCNetSDK.NET_DVR_MatrixStartPassiveDecode(m_lUserID, dwDecChanNum, ref m_struPassivePara);
            if (lPassiveHandle == -1)
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_MatrixStartPassiveDecode failed, error code= " + iLastErr;
                //启动动态解码失败，输出错误号 Failed to start dynamic decoding and output the error code
                MessageBox.Show(strErr);
                return;
            }
            else
            {
                MessageBox.Show("Successful to start passive decoding!");
                hExitThread = false;
            }
        }

        public void RealDataCallBack(Int32 lRealHandle, UInt32 dwDataType, IntPtr pBuffer, UInt32 dwBufSize, IntPtr pUser)
        {
            //此处代码仅供参考，实际应用时回调中获取实时流数据后需要在回调外面处理或处理数据
            if (!CHCNetSDK.NET_DVR_MatrixSendData(lPassiveHandle, pBuffer, dwBufSize))
            {
                //发送失败 Failed to send data to the decoder
            }
        }


        private void btnSendData_Click(object sender, EventArgs e)
        {
            if (comboBoxStreamMode.SelectedIndex == 0) //实时流解码：登录编码器获取实时流然后转发给解码器
            {
                string DVRIPAddress = textBoxDevAddr.Text;
                Int16 DVRPortNumber = Int16.Parse(textBoxDevPort.Text);
                string DVRUserName = textBoxUserName.Text;
                string DVRPassword = textBoxPassword.Text;

                //登录设备 Login the device
                CHCNetSDK.NET_DVR_DEVICEINFO_V30 m_struDeviceInfo = new CHCNetSDK.NET_DVR_DEVICEINFO_V30();
                lUserID = CHCNetSDK.NET_DVR_Login_V30(DVRIPAddress, DVRPortNumber, DVRUserName, DVRPassword, ref m_struDeviceInfo);
                if (lUserID < 0)
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    strErr = "NET_DVR_Login_V30 failed, error code= " + iLastErr;
                    //登录失败，输出错误号 Failed to login and output the error code
                    MessageBox.Show(strErr);
                    return;
                }
                else
                {
                    CHCNetSDK.NET_DVR_PREVIEWINFO lpPreviewInfo = new CHCNetSDK.NET_DVR_PREVIEWINFO();
                    lpPreviewInfo.hPlayWnd = IntPtr.Zero;//预览窗口设为NULL，只取流不解码
                    lpPreviewInfo.lChannel = Int32.Parse(textBoxChannel.Text);//预te览的设备通道
                    lpPreviewInfo.dwStreamType = (uint)comboBoxStreamType.SelectedIndex;//码流类型：0-主码流，1-子码流，2-码流3，3-码流4，以此类推
                    lpPreviewInfo.dwLinkMode = (uint)comboBoxRealProtol.SelectedIndex;//连接方式：0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP 
                    lpPreviewInfo.bBlocked = true; //0- 非阻塞取流，1- 阻塞取流

                    CHCNetSDK.REALDATACALLBACK RealData = new CHCNetSDK.REALDATACALLBACK(RealDataCallBack);//预览实时流回调函数
                    IntPtr pUser = new IntPtr();//用户数据

                    //打开预览 Start live view 
                    lRealHandle = CHCNetSDK.NET_DVR_RealPlay_V40(lUserID, ref lpPreviewInfo, RealData, pUser);
                    if (lRealHandle < 0)
                    {
                        iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                        strErr = "NET_DVR_RealPlay_V40 failed, error code= " + iLastErr;
                        //预览失败，输出错误号 Failed to start live view and output the error code
                        MessageBox.Show(strErr);
                        return;
                    }
                    else
                    {
                        //预览取流成功 Success to start live view  
                        MessageBox.Show("Start to send the steam data to the decoder!");
                    }
                }

            }
            else //文件流解码：读取文件里面的数据发送给解码器
            {
                int iDataSize = Int32.Parse(textBoxReadSize.Text);
                if (iDataSize < 1 || iDataSize > 512)
                {
                    MessageBox.Show("Please set a applicable value!");
                    return;
                }

                iStreamSize = int.Parse(textBoxReadSize.Text);

                if (hFileHandle != null)
                {
                    hFileHandle.Close();
                    hFileHandle = null;
                }
                hFileHandle = new FileStream(textBoxFilePath.Text, FileMode.Open, FileAccess.Read); //打开文件 Open the file             
                if (hFileHandle == null)
                {
                    return;                
                }
              
                int lHandle = lPassiveHandle;
                filetrd = new Thread(FileThreadTask); //创建读取文件数据的线程（仅供参考）
                filetrd.IsBackground = true;
                filetrd.Start((object)lHandle);
                MessageBox.Show("Start to send the file data to the decoder!");
            }
        }

        private void FileThreadTask(object lHandle)
        {
            //该线程数据处理方式仅供参考，实际使用时请自行优化

            long left = hFileHandle.Length;
            byte[] tmpFile = new byte[iStreamSize * 1024];
            int maxLength = tmpFile.Length;
            int istart = 0;
            int iRealSize = 0;

            while (left > 0)
            {
                if (hExitThread)
                    break;

                hFileHandle.Position = istart;
                iRealSize = 0;
                if (left < maxLength)
                    iRealSize = hFileHandle.Read(tmpFile, 0, Convert.ToInt32(left));
                else
                    iRealSize = hFileHandle.Read(tmpFile, 0, maxLength);
                
                if (iRealSize == 0)
                    break;

                istart += iRealSize;
                left -= iRealSize;

                //将读取到的文件数据发送给解码器 
                IntPtr pBuffer = Marshal.AllocHGlobal((Int32)iRealSize);
                Marshal.Copy(tmpFile, 0, pBuffer, iRealSize);
                if (!CHCNetSDK.NET_DVR_MatrixSendData((int)lHandle, pBuffer, (uint)iRealSize))
                {
                    //发送失败 Failed to send data to the decoder
                    //数据发送失败，可以循环重新发送，避免数据丢失导致卡顿
                }
                Marshal.FreeHGlobal(pBuffer);
                Thread.Sleep(10);
            }

            if (!hExitThread)
            {
                MessageBox.Show("Finished to read data from the video file!");
            }

            filetrd.Abort();
            filetrd = null;
        }

        private void btnStopDecode_Click(object sender, EventArgs e)
        {
            if (comboBoxStreamMode.SelectedIndex == 0) //实时流解码：登录编码器获取实时流然后转发给解码器
            {
                //停止预览 Stop live view 
                if (lRealHandle >= 0)
                {
                    if (!CHCNetSDK.NET_DVR_StopRealPlay(lRealHandle))
                    {
                        iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                        strErr = "NET_DVR_StopRealPlay failed, error code= " + iLastErr;
                        MessageBox.Show(strErr);
                        return;
                    }
                }

                //注销登录 Logout the device
                if (lUserID >= 0)
                {
                    if (!CHCNetSDK.NET_DVR_Logout(lUserID))
                    {
                        iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                        strErr = "NET_DVR_Logout failed, error code= " + iLastErr;
                        MessageBox.Show(strErr);
                        return;
                    }
                }

                //停止被动解码 Stop the passive decoding
                if (!CHCNetSDK.NET_DVR_MatrixStopPassiveDecode(lPassiveHandle))
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    strErr = "NET_DVR_MatrixStopPassiveDecode failed, error code= " + iLastErr;
                    MessageBox.Show(strErr);
                    return;
                }
                lPassiveHandle = -1;
                MessageBox.Show("Successful to stop the passive decoding!");
            }
            else //文件流解码：读取文件里面的数据发送给解码器
            {
                hExitThread = true;

                if (hFileHandle != null)
                {
                    hFileHandle.Close();
                    hFileHandle = null;
                }

                //停止被动解码 Stop the passive decoding
                if (!CHCNetSDK.NET_DVR_MatrixStopPassiveDecode(lPassiveHandle))
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    strErr = "NET_DVR_MatrixStopPassiveDecode failed, error code= " + iLastErr;
                    MessageBox.Show(strErr);
                    return;
                }
                lPassiveHandle = -1;
                MessageBox.Show("Successful to stop the passive decoding!");
            }
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            if (filetrd != null)
            {
                filetrd.Abort();
                filetrd = null;
            }
            
            if (hFileHandle != null)
            {
                hFileHandle.Close();
                hFileHandle = null;
            }

            this.Close();
            this.Dispose(); 
        }

        private void btnOpenFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All files (*.*)|*.*|All files (*.*)|*.*";
            dlg.FilterIndex = 2;
            dlg.RestoreDirectory = true;
            if (dlg.ShowDialog() == DialogResult.OK) 
            {
                textBoxFilePath.Text = dlg.FileName;  
	        }
        }
    }
}
