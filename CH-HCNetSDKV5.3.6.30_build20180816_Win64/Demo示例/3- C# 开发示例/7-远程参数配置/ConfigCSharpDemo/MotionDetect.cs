using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace ConfigCSharpDemo
{
    public partial class MotionDetect : Form
    {
        private uint iLastErr = 0;
        private string strErr;
        public int m_lUserID;
        public int m_lChannel;
        public CHCNetSDK.NET_DVR_DEVICEINFO_V30 m_struDeviceInfo;
        public CHCNetSDK.NET_DVR_PICCFG_V40 m_struPicCfgV40;
        private CHCNetSDK.DRAWFUN m_fMotionDraw = null;
        private CHCNetSDK.NET_DVR_MOTION_V40 m_struMotionV40;
        private int m_lMotionPlayHandle = -1;

        public MotionDetect()
        {
            InitializeComponent();
        }

        private void MotionDetect_Load(object sender, EventArgs e)
        {
            string str = "";
            byte byCount;
            for (byCount = 1; byCount <= m_struDeviceInfo.byChanNum; byCount++)
            {
                str = String.Format("Camera {0}", byCount);
                treeViewRecordChan.Nodes.Add(str); //关联的录像通道 - 模拟通道                
            }

            for (byCount = 1; byCount <= m_struDeviceInfo.byIPChanNum; byCount++)
            {
                str = String.Format("IPCamera {0}", byCount);
                treeViewRecordIPChan.Nodes.Add(str);//关联的录像通道 - IP通道
            }

            for (byCount = 1; byCount <= m_struDeviceInfo.byAlarmOutPortNum; byCount++)
            {
                str = String.Format("Alarm Out {0}", byCount);//关联的报警输出口
                treeViewAlarmOut.Nodes.Add(str);
            }

            CHCNetSDK.NET_DVR_PREVIEWINFO struClientInfo = new CHCNetSDK.NET_DVR_PREVIEWINFO();
            struClientInfo.lChannel = m_lChannel; //预览通道号
            struClientInfo.dwStreamType = 0;//0-主码流，1-子码流，2-码流3，3-虚拟码流
            struClientInfo.dwLinkMode = 0;//0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP 
            struClientInfo.hPlayWnd = MotionRealPlay.Handle;
            struClientInfo.bBlocked = true;

            m_lMotionPlayHandle = CHCNetSDK.NET_DVR_RealPlay_V40(m_lUserID, ref struClientInfo, null, IntPtr.Zero);

            if (m_lMotionPlayHandle < 0)
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_RealPlay_V40 failed, error code= " + iLastErr;
                //预览失败，输出错误号 Failed to start live view and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                //注册画图回调
                m_fMotionDraw = new CHCNetSDK.DRAWFUN(MotionDrawCallBack);
                CHCNetSDK.NET_DVR_RigisterDrawFun(m_lMotionPlayHandle, m_fMotionDraw, 0);
            }

            m_struMotionV40 = m_struPicCfgV40.struMotion;

            //是否处理移动侦测
            if (m_struMotionV40.byEnableHandleMotion == 0)
            {
                checkBoxEnableMotion.Checked = false;
            }
            else
            {
                checkBoxEnableMotion.Checked = true;
            }

            if (m_struMotionV40.byEnableDisplay == 1)
            {
                checkBoxDisplay.Checked = true;
            }
            else
            {
                checkBoxDisplay.Checked = false;
            }

            //普通模式灵敏度
            if (m_struMotionV40.byConfigurationMode == 0)
            {
                //获取移动侦测灵敏度
                GetMotionSensitivityCurSel(m_struMotionV40.struMotionMode.struMotionSingleArea.byMotionSensitive);                
            }

            comboBoxWeekday.SelectedIndex = 0;
            comboBoxWeekdayCopy.SelectedIndex = 0;   
           
            //设置布防时间、触发录像通道、触发报警输出口
            GetAlarmTimeWnd();
            GetRecordChanWnd();
            GetAlarmHandleWnd();
        }

        private void GetRecordChanWnd()
        {
            int iCount = 0;
            for (iCount = 0; iCount < CHCNetSDK.MAX_CHANNUM_V40; iCount++)
            {
                uint iRelChannel = m_struMotionV40.dwRelRecordChan[iCount];
                if (iRelChannel != 0xffffffff)
                {
                    if (iRelChannel < m_struDeviceInfo.byStartDChan)
                        treeViewRecordChan.Nodes[(int)iRelChannel-1].Checked = true;
                    else
                        treeViewRecordIPChan.Nodes[(int)iRelChannel - m_struDeviceInfo.byStartDChan].Checked = true;
                }
            }
        }

        private void SetRecordChanWnd()
        {
            int iCount =0;
            int iRelRecordChan = 0;

            for (iCount = 0; iCount < CHCNetSDK.MAX_CHANNUM_V40; iCount++)
            {
                m_struMotionV40.dwRelRecordChan[iCount] = 0xffffffff;
            }

            for (iCount = 0; iCount < m_struDeviceInfo.byChanNum; iCount++)
            {
                if (treeViewRecordChan.Nodes[iCount].Checked)
                {
                    m_struMotionV40.dwRelRecordChan[iRelRecordChan++] = (uint)iCount + m_struDeviceInfo.byStartChan;
                }                
            }

            for (iCount = 0; iCount < m_struDeviceInfo.byIPChanNum; iCount++)
            {
                if (treeViewRecordIPChan.Nodes[iCount].Checked)
                {
                    m_struMotionV40.dwRelRecordChan[iRelRecordChan++] = (uint)iCount + m_struDeviceInfo.byStartDChan;
                }
            }
        }

        public void MotionDrawCallBack(int lRealHandle, IntPtr hDc, uint dwUser)
        {
            
        }

        private void GetAlarmTimeWnd()
        {
            //获取布防时间
            int nDayIndex = comboBoxWeekday.SelectedIndex;
            textBoxHour11.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 0].byStartHour.ToString();
            textBoxMin11.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 0].byStartMin.ToString();
            textBoxHour12.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 0].byStopHour.ToString();
            textBoxMin12.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 0].byStopMin.ToString();

            textBoxHour21.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 1].byStartHour.ToString();
            textBoxMin21.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 1].byStartMin.ToString();
            textBoxHour22.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 1].byStopHour.ToString();
            textBoxMin22.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 1].byStopMin.ToString();

            textBoxHour31.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 2].byStartHour.ToString();
            textBoxMin31.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 2].byStartMin.ToString();
            textBoxHour32.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 2].byStopHour.ToString();
            textBoxMin32.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 2].byStopMin.ToString();

            textBoxHour41.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 3].byStartHour.ToString();
            textBoxMin41.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 3].byStartMin.ToString();
            textBoxHour42.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 3].byStopHour.ToString();
            textBoxMin42.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 3].byStopMin.ToString();

            textBoxHour51.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 4].byStartHour.ToString();
            textBoxMin51.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 4].byStartMin.ToString();
            textBoxHour52.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 4].byStopHour.ToString();
            textBoxMin52.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 4].byStopMin.ToString();

            textBoxHour61.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 5].byStartHour.ToString();
            textBoxMin61.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 5].byStartMin.ToString();
            textBoxHour62.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 5].byStopHour.ToString();
            textBoxMin62.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 5].byStopMin.ToString();

            textBoxHour71.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 6].byStartHour.ToString();
            textBoxMin71.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 6].byStartMin.ToString();
            textBoxHour72.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 6].byStopHour.ToString();
            textBoxMin72.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 6].byStopMin.ToString();

            textBoxHour81.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 7].byStartHour.ToString();
            textBoxMin81.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 7].byStartMin.ToString();
            textBoxHour82.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 7].byStopHour.ToString();
            textBoxMin82.Text = m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 7].byStopMin.ToString();
        }

        private void SetAlarmTimeWnd()
        {
            //设置布防时间
            int nDayIndex = comboBoxWeekday.SelectedIndex;
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 0].byStartHour = byte.Parse(textBoxHour11.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 0].byStartMin = byte.Parse(textBoxMin11.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 0].byStopHour = byte.Parse(textBoxHour12.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 0].byStopMin = byte.Parse(textBoxMin12.Text);

            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 1].byStartHour = byte.Parse(textBoxHour21.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 1].byStartMin = byte.Parse(textBoxMin21.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 1].byStopHour = byte.Parse(textBoxHour22.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 1].byStopMin = byte.Parse(textBoxMin22.Text);

            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 2].byStartHour = byte.Parse(textBoxHour31.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 2].byStartMin = byte.Parse(textBoxMin31.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 2].byStopHour = byte.Parse(textBoxHour32.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 2].byStopMin = byte.Parse(textBoxMin32.Text);

            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 3].byStartHour = byte.Parse(textBoxHour41.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 3].byStartMin = byte.Parse(textBoxMin41.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 3].byStopHour = byte.Parse(textBoxHour42.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 3].byStopMin = byte.Parse(textBoxMin42.Text);

            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 4].byStartHour = byte.Parse(textBoxHour51.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 4].byStartMin = byte.Parse(textBoxMin51.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 4].byStopHour = byte.Parse(textBoxHour52.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 4].byStopMin = byte.Parse(textBoxMin52.Text);

            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 5].byStartHour = byte.Parse(textBoxHour61.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 5].byStartMin = byte.Parse(textBoxMin61.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 5].byStopHour = byte.Parse(textBoxHour62.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 5].byStopMin = byte.Parse(textBoxMin62.Text);

            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 6].byStartHour = byte.Parse(textBoxHour71.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 6].byStartMin = byte.Parse(textBoxMin71.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 6].byStopHour = byte.Parse(textBoxHour72.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 6].byStopMin = byte.Parse(textBoxMin72.Text);

            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 7].byStartHour = byte.Parse(textBoxHour81.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 7].byStartMin = byte.Parse(textBoxMin81.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 7].byStopHour = byte.Parse(textBoxHour82.Text);
            m_struMotionV40.struAlarmTime[nDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + 7].byStopMin = byte.Parse(textBoxMin82.Text);

        }
        private void GetAlarmHandleWnd()
        {
            //获取报警处理方式

            if (1 == ((m_struMotionV40.dwHandleType >> 0) & 0x01))
            {
                checkBoxShowAlarm.Checked = true;
            }

            if (1 == ((m_struMotionV40.dwHandleType >> 1) & 0x01))
            {
                checkBoxAudioAlarm.Checked = true;
            }

            if (1 == ((m_struMotionV40.dwHandleType >> 2) & 0x01))
            {
                checkBoxReportAlarm.Checked = true;
            }

            if (1 == ((m_struMotionV40.dwHandleType >> 3) & 0x01))
            {
                checkBoxTriggerAlarm.Checked = true;
            }

            if (1 == ((m_struMotionV40.dwHandleType >> 4) & 0x01))
            {
                checkBoxEmailAlarm.Checked = true;
            }

            if (1 == ((m_struMotionV40.dwHandleType >> 9) & 0x01))
            {
                checkBoxFTPAlarm.Checked = true;
            }

            treeViewAlarmOut.Enabled = checkBoxTriggerAlarm.Checked;
            for (int i = 0; i < treeViewAlarmOut.Nodes.Count; i++)
            {
                uint iAlarmout = m_struMotionV40.dwRelAlarmOut[i];//触发报警输出号
                if (iAlarmout != 0xffffffff)
                {
                    treeViewAlarmOut.Nodes[(int)iAlarmout].Checked = true;
                }              
            }
        }
        private void SetAlarmHandleWnd()
        {
            //设置报警处理方式

            m_struMotionV40.dwHandleType = 0;
            if (checkBoxShowAlarm.Checked)
            {
                m_struMotionV40.dwHandleType |= (0x01 << 0);
            }

            if (checkBoxAudioAlarm.Checked)
            {
                m_struMotionV40.dwHandleType |= (0x01 << 1);
            }

            if (checkBoxReportAlarm.Checked)
            {
                m_struMotionV40.dwHandleType |= (0x01 << 2);
            }

            if (checkBoxTriggerAlarm.Checked)
            {
                m_struMotionV40.dwHandleType |= (0x01 << 3);
            }

            if (checkBoxEmailAlarm.Checked)
            {
                m_struMotionV40.dwHandleType |= (0x01 << 4);
            }

            if (checkBoxFTPAlarm.Checked)
            {
                m_struMotionV40.dwHandleType |= (0x01 << 9);
            }

            int dwRelAlarmOutChanNum = 0;
            for (int i = 0; i < treeViewAlarmOut.Nodes.Count; i++)
            {
                if (treeViewAlarmOut.Nodes[i].Checked)
                {
                    m_struMotionV40.dwRelAlarmOut[dwRelAlarmOutChanNum++] = (uint)i;
                }
            }
            m_struMotionV40.dwRelAlarmOut[dwRelAlarmOutChanNum] = 0xffffffff;

        }
        private void GetMotionSensitivityCurSel(byte bySensitity)
        {
            if (bySensitity == 0xff)
            {
                comboBoxMotionSensitive.SelectedIndex = 0;
            }
            else
            {
                comboBoxMotionSensitive.SelectedIndex = bySensitity + 1;
            }
        }
        private byte SetMotionSensitivityCurSel()
        {
            byte byReturn;
            if (0 == comboBoxMotionSensitive.SelectedIndex)
            {
                byReturn = 0xff;
            }
            else
            {
                byReturn = (byte)(comboBoxMotionSensitive.SelectedIndex - 1);
            }
            return byReturn;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            GetAlarmTimeWnd();
        }

        private void btnMotionSetup_Click(object sender, EventArgs e)
        {
            m_struMotionV40.struMotionMode.struMotionSingleArea.byMotionSensitive = SetMotionSensitivityCurSel();
            SetAlarmHandleWnd();
            SetAlarmTimeWnd();
            SetRecordChanWnd();
            if (checkBoxEnableMotion.Checked)
            {
                m_struMotionV40.byEnableHandleMotion = 1;
            }
            else
            {
                m_struMotionV40.byEnableHandleMotion = 0;
            }

            //设置移动侦测区域 
            if (checkBoxMotionScope.Checked)
            {
                for (int i = 0; i < 18; i++)
                {
                    for (int j = 0; j < 22; j++ )
                    {
                        m_struMotionV40.struMotionMode.struMotionSingleArea.byMotionScope[i * 96 + j] = 1;
                    }
                }
            }

            if (checkBoxDisplay.Checked)
            {
                m_struMotionV40.byEnableDisplay = 1;            
            }

            m_struPicCfgV40.struMotion = m_struMotionV40;

            MessageBox.Show("保存参数成功!");
            this.Close();
            this.Dispose();          
        }

        private void btnMotionDayCopy_Click(object sender, EventArgs e)
        {
            int iDayIndex = comboBoxWeekday.SelectedIndex;
            int iCopyDayIndex = comboBoxWeekdayCopy.SelectedIndex - 1;
            if (iCopyDayIndex == -1)
            {
                for (int j = 0; j < 7; j++)
                {
                    if (iDayIndex != j)
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            m_struMotionV40.struAlarmTime[j * CHCNetSDK.MAX_TIMESEGMENT_V30 + i] = m_struMotionV40.struAlarmTime[iDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + i];
                        }
                    }
                }
            }
            else
            {
                if (iDayIndex != iCopyDayIndex)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        m_struMotionV40.struAlarmTime[iCopyDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + i] = m_struMotionV40.struAlarmTime[iDayIndex * CHCNetSDK.MAX_TIMESEGMENT_V30 + i];
                    }
                }
            }
        }

        private void MotionDetect_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (m_lMotionPlayHandle >= 0)
            {
                if (CHCNetSDK.NET_DVR_StopRealPlay(m_lMotionPlayHandle))
                {
                    Debug.Print("NET_DVR_StopRealPlay Succ\n");
                }
                else
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    strErr = "NET_DVR_StopRealPlay failed, error code= " + iLastErr;
                    Debug.Print(strErr);
                }
            }
        }

        private void btnMotionDayOk_Click(object sender, EventArgs e)
        {
            SetAlarmHandleWnd();
        }

        private void checkBoxTriggerAlarm_CheckedChanged(object sender, EventArgs e)
        {
            treeViewAlarmOut.Enabled =  checkBoxTriggerAlarm.Checked;
        }
    }
}
