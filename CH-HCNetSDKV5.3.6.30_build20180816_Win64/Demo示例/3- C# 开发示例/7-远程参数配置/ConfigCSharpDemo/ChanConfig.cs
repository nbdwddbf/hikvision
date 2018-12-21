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
    public partial class ChanConfig : Form
    {
        public CHCNetSDK.NET_DVR_DEVICEINFO_V30 m_struDeviceInfo;
        private CHCNetSDK.NET_DVR_PICCFG_V40 m_struPicCfgV40;
        private CHCNetSDK.NET_DVR_SHOWSTRING_V30 m_struShowStrCfg;
        private uint iLastErr = 0;
        private string strErr;
        public int m_lUserID;
        public int m_lChannel;

        public ChanConfig()
        {
            InitializeComponent();
        }

        private void buttonGetEncode_Click(object sender, EventArgs e)
        {
            UInt32 dwReturn = 0;
            Int32 nSize = Marshal.SizeOf(m_struPicCfgV40);
            IntPtr ptrPicCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struPicCfgV40, ptrPicCfg, false);
            if (!CHCNetSDK.NET_DVR_GetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_GET_PICCFG_V40, m_lChannel, ptrPicCfg, (UInt32)nSize, ref dwReturn))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_GET_PICCFG_V40 failed, error code= " + iLastErr;
                //获取图像参数失败，输出错误号 Failed to get image parameters and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                m_struPicCfgV40 = (CHCNetSDK.NET_DVR_PICCFG_V40)Marshal.PtrToStructure(ptrPicCfg, typeof(CHCNetSDK.NET_DVR_PICCFG_V40));
                if (m_struPicCfgV40.dwShowChanName == 1)
                {
                    checkBoxChanName.Checked = true;
                }
                else
                {
                    checkBoxChanName.Checked = false;
                }
                textBoxChanName.Text = System.Text.Encoding.GetEncoding("GBK").GetString(m_struPicCfgV40.sChanName);
                textBoxXName.Text = Convert.ToString(m_struPicCfgV40.wShowNameTopLeftX);
                textBoxYName.Text = Convert.ToString(m_struPicCfgV40.wShowNameTopLeftY);
                if (m_struPicCfgV40.dwShowOsd == 1)
                {
                    checkBoxOSD.Checked = true;
                }
                else
                {
                    checkBoxOSD.Checked = false;
                }
                if (m_struPicCfgV40.byDispWeek == 1)
                {
                    checkBoxWeek.Checked = true;
                }
                else
                {
                    checkBoxWeek.Checked = false;
                }
                comboBoxTime.SelectedIndex = m_struPicCfgV40.byHourOSDType;
                comboBoxDate.SelectedIndex = m_struPicCfgV40.byOSDType;

                if (m_struPicCfgV40.byFontSize == 0xff)
                {
                    comboBoxSize.SelectedIndex = 4;

                }
                else
                {
                    comboBoxSize.SelectedIndex = m_struPicCfgV40.byFontSize;
                }
                comboBoxDisplay.SelectedIndex = m_struPicCfgV40.byOSDAttrib - 1;
                textBoxXOSD.Text = Convert.ToString(m_struPicCfgV40.wOSDTopLeftX);
                textBoxYOSD.Text = Convert.ToString(m_struPicCfgV40.wOSDTopLeftY);
            }
            Marshal.FreeHGlobal(ptrPicCfg);
        }

        private void ChanConfig_Load(object sender, EventArgs e)
        {
            buttonGetEncode_Click(sender, e);
            btnShowStringGet_Click(sender, e);
        }

        private void btnImageCfgSet_Click(object sender, EventArgs e)
        {
            if(checkBoxChanName.Checked)
            {
                m_struPicCfgV40.dwShowChanName = 1;
            }
            else
            {
                m_struPicCfgV40.dwShowChanName = 0;
            }

            byte[] byName = System.Text.Encoding.Default.GetBytes(textBoxChanName.Text);
            m_struPicCfgV40.sChanName = new byte[32];
            byName.CopyTo(m_struPicCfgV40.sChanName, 0);

            m_struPicCfgV40.wShowNameTopLeftX = UInt16.Parse(textBoxXName.Text);
            m_struPicCfgV40.wShowNameTopLeftY = UInt16.Parse(textBoxYName.Text);

            if (checkBoxOSD.Checked)
            {
                m_struPicCfgV40.dwShowOsd = 1;
            }
            else
            {
                m_struPicCfgV40.dwShowOsd = 0;
            }

            if (checkBoxWeek.Checked)
            {
                m_struPicCfgV40.byDispWeek = 1;
            }
            else
            {
                m_struPicCfgV40.byDispWeek = 0;
            }

            m_struPicCfgV40.byHourOSDType = (byte)comboBoxTime.SelectedIndex;
            m_struPicCfgV40.byOSDType = (byte)comboBoxDate.SelectedIndex;

            if (comboBoxSize.SelectedIndex == 4)
            {
                m_struPicCfgV40.byFontSize = 0xff;
            }
            else
            {
                m_struPicCfgV40.byFontSize = (byte)comboBoxSize.SelectedIndex;
            }
            m_struPicCfgV40.byOSDAttrib = (byte)(comboBoxDisplay.SelectedIndex + 1);
            m_struPicCfgV40.wOSDTopLeftX = UInt16.Parse(textBoxXOSD.Text);
            m_struPicCfgV40.wOSDTopLeftY = UInt16.Parse(textBoxYOSD.Text);

            Int32 nSize = Marshal.SizeOf(m_struPicCfgV40);
            IntPtr ptrPicCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struPicCfgV40, ptrPicCfg, false);

            if (!CHCNetSDK.NET_DVR_SetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_SET_PICCFG_V40, m_lChannel, ptrPicCfg, (UInt32)nSize))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_SET_PICCFG_V40 failed, error code= " + iLastErr;
                //设置图像参数失败，输出错误号 Failed to set image parameters and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                MessageBox.Show("设置图像参数成功！");
            }

            Marshal.FreeHGlobal(ptrPicCfg);
        }

        private void btnShowStringGet_Click(object sender, EventArgs e)
        {
            UInt32 dwReturn = 0;
            Int32 nSize = Marshal.SizeOf(m_struShowStrCfg);
            IntPtr ptrShowStrCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struShowStrCfg, ptrShowStrCfg, false);
            if (!CHCNetSDK.NET_DVR_GetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_GET_SHOWSTRING_V30, m_lChannel, ptrShowStrCfg, (UInt32)nSize, ref dwReturn))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_GET_SHOWSTRING_V30 failed, error code= " + iLastErr;
                //获取字符叠加参数失败，输出错误号 Failed to get overlay parameters and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                m_struShowStrCfg = (CHCNetSDK.NET_DVR_SHOWSTRING_V30)Marshal.PtrToStructure(ptrShowStrCfg, typeof(CHCNetSDK.NET_DVR_SHOWSTRING_V30));
                
                checkBoxOSD1.Checked = (m_struShowStrCfg.struStringInfo[0].wShowString == 1);
                textBoxOSD1.Text = m_struShowStrCfg.struStringInfo[0].sString;
                textBoxOSD1X.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[0].wShowStringTopLeftX);
                textBoxOSD1Y.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[0].wShowStringTopLeftY);

                checkBoxOSD2.Checked = (m_struShowStrCfg.struStringInfo[1].wShowString == 1);
                textBoxOSD2.Text = m_struShowStrCfg.struStringInfo[1].sString;
                textBoxOSD2X.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[1].wShowStringTopLeftX);
                textBoxOSD2Y.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[1].wShowStringTopLeftY);

                checkBoxOSD3.Checked = (m_struShowStrCfg.struStringInfo[2].wShowString == 1);
                textBoxOSD3.Text = m_struShowStrCfg.struStringInfo[2].sString;
                textBoxOSD3X.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[2].wShowStringTopLeftX);
                textBoxOSD3Y.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[2].wShowStringTopLeftY);

                checkBoxOSD4.Checked = (m_struShowStrCfg.struStringInfo[3].wShowString == 1);
                textBoxOSD4.Text = m_struShowStrCfg.struStringInfo[3].sString;
                textBoxOSD4X.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[3].wShowStringTopLeftX);
                textBoxOSD4Y.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[3].wShowStringTopLeftY);

                checkBoxOSD5.Checked = (m_struShowStrCfg.struStringInfo[4].wShowString == 1);
                textBoxOSD5.Text = m_struShowStrCfg.struStringInfo[4].sString;
                textBoxOSD5X.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[4].wShowStringTopLeftX);
                textBoxOSD5Y.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[4].wShowStringTopLeftY);

                checkBoxOSD6.Checked = (m_struShowStrCfg.struStringInfo[5].wShowString == 1);
                textBoxOSD6.Text = m_struShowStrCfg.struStringInfo[5].sString;
                textBoxOSD6X.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[5].wShowStringTopLeftX);
                textBoxOSD6Y.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[5].wShowStringTopLeftY);

                checkBoxOSD7.Checked = (m_struShowStrCfg.struStringInfo[6].wShowString == 1);
                textBoxOSD7.Text = m_struShowStrCfg.struStringInfo[6].sString;
                textBoxOSD7X.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[6].wShowStringTopLeftX);
                textBoxOSD7Y.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[6].wShowStringTopLeftY);

                checkBoxOSD8.Checked = (m_struShowStrCfg.struStringInfo[7].wShowString == 1);
                textBoxOSD8.Text = m_struShowStrCfg.struStringInfo[7].sString;
                textBoxOSD8X.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[7].wShowStringTopLeftX);
                textBoxOSD8Y.Text = Convert.ToString(m_struShowStrCfg.struStringInfo[7].wShowStringTopLeftY);  
            }
            Marshal.FreeHGlobal(ptrShowStrCfg);
        }

        private void btnShowStringSet_Click(object sender, EventArgs e)
        {
            if(checkBoxOSD1.Checked)
                m_struShowStrCfg.struStringInfo[0].wShowString = 1;
            else
                m_struShowStrCfg.struStringInfo[0].wShowString = 0;
            m_struShowStrCfg.struStringInfo[0].sString = textBoxOSD1.Text;
            m_struShowStrCfg.struStringInfo[0].wStringSize = (ushort)textBoxOSD1.Text.Length;
            m_struShowStrCfg.struStringInfo[0].wShowStringTopLeftX = UInt16.Parse(textBoxOSD1X.Text);
            m_struShowStrCfg.struStringInfo[0].wShowStringTopLeftY = UInt16.Parse(textBoxOSD1Y.Text);

            if (checkBoxOSD2.Checked)
                m_struShowStrCfg.struStringInfo[1].wShowString = 1;
            else
                m_struShowStrCfg.struStringInfo[1].wShowString = 0;
            m_struShowStrCfg.struStringInfo[1].sString = textBoxOSD2.Text;
            m_struShowStrCfg.struStringInfo[1].wStringSize = (ushort)textBoxOSD2.Text.Length;
            m_struShowStrCfg.struStringInfo[1].wShowStringTopLeftX = UInt16.Parse(textBoxOSD2X.Text);
            m_struShowStrCfg.struStringInfo[1].wShowStringTopLeftY = UInt16.Parse(textBoxOSD2Y.Text);

            if (checkBoxOSD3.Checked)
                m_struShowStrCfg.struStringInfo[2].wShowString = 1;
            else
                m_struShowStrCfg.struStringInfo[2].wShowString = 0;
            m_struShowStrCfg.struStringInfo[2].sString = textBoxOSD3.Text;
            m_struShowStrCfg.struStringInfo[2].wStringSize = (ushort)textBoxOSD3.Text.Length;
            m_struShowStrCfg.struStringInfo[2].wShowStringTopLeftX = UInt16.Parse(textBoxOSD3X.Text);
            m_struShowStrCfg.struStringInfo[2].wShowStringTopLeftY = UInt16.Parse(textBoxOSD3Y.Text);

            if (checkBoxOSD4.Checked)
                m_struShowStrCfg.struStringInfo[3].wShowString = 1;
            else
                m_struShowStrCfg.struStringInfo[3].wShowString = 0;
            m_struShowStrCfg.struStringInfo[3].sString = textBoxOSD4.Text;
            m_struShowStrCfg.struStringInfo[3].wStringSize = (ushort)textBoxOSD4.Text.Length;
            m_struShowStrCfg.struStringInfo[3].wShowStringTopLeftX = UInt16.Parse(textBoxOSD4X.Text);
            m_struShowStrCfg.struStringInfo[3].wShowStringTopLeftY = UInt16.Parse(textBoxOSD4Y.Text);

            if (checkBoxOSD5.Checked)
                m_struShowStrCfg.struStringInfo[4].wShowString = 1;
            else
                m_struShowStrCfg.struStringInfo[4].wShowString = 0;
            m_struShowStrCfg.struStringInfo[4].sString = textBoxOSD5.Text;
            m_struShowStrCfg.struStringInfo[4].wStringSize = (ushort)textBoxOSD5.Text.Length;
            m_struShowStrCfg.struStringInfo[4].wShowStringTopLeftX = UInt16.Parse(textBoxOSD5X.Text);
            m_struShowStrCfg.struStringInfo[4].wShowStringTopLeftY = UInt16.Parse(textBoxOSD5Y.Text);

            if (checkBoxOSD6.Checked)
                m_struShowStrCfg.struStringInfo[5].wShowString = 1;
            else
                m_struShowStrCfg.struStringInfo[5].wShowString = 0;
            m_struShowStrCfg.struStringInfo[5].sString = textBoxOSD6.Text;
            m_struShowStrCfg.struStringInfo[5].wStringSize = (ushort)textBoxOSD6.Text.Length;
            m_struShowStrCfg.struStringInfo[5].wShowStringTopLeftX = UInt16.Parse(textBoxOSD6X.Text);
            m_struShowStrCfg.struStringInfo[5].wShowStringTopLeftY = UInt16.Parse(textBoxOSD6Y.Text);

            if (checkBoxOSD7.Checked)
                m_struShowStrCfg.struStringInfo[6].wShowString = 1;
            else
                m_struShowStrCfg.struStringInfo[6].wShowString = 0;
            m_struShowStrCfg.struStringInfo[6].sString = textBoxOSD7.Text;
            m_struShowStrCfg.struStringInfo[6].wStringSize = (ushort)textBoxOSD7.Text.Length;
            m_struShowStrCfg.struStringInfo[6].wShowStringTopLeftX = UInt16.Parse(textBoxOSD7X.Text);
            m_struShowStrCfg.struStringInfo[6].wShowStringTopLeftY = UInt16.Parse(textBoxOSD7Y.Text);

            if (checkBoxOSD8.Checked)
                m_struShowStrCfg.struStringInfo[7].wShowString = 1;
            else
                m_struShowStrCfg.struStringInfo[7].wShowString = 0;
            m_struShowStrCfg.struStringInfo[7].sString = textBoxOSD8.Text;
            m_struShowStrCfg.struStringInfo[7].wStringSize = (ushort)textBoxOSD8.Text.Length;
            m_struShowStrCfg.struStringInfo[7].wShowStringTopLeftX = UInt16.Parse(textBoxOSD8X.Text);
            m_struShowStrCfg.struStringInfo[7].wShowStringTopLeftY = UInt16.Parse(textBoxOSD8Y.Text);

            Int32 nSize = Marshal.SizeOf(m_struShowStrCfg);
            IntPtr ptrShowStrCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struShowStrCfg, ptrShowStrCfg, false);

            if (!CHCNetSDK.NET_DVR_SetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_SET_SHOWSTRING_V30, m_lChannel, ptrShowStrCfg, (UInt32)nSize))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_SET_SHOWSTRING_V30 failed, error code= " + iLastErr;
                //设置字符叠加参数失败，输出错误号 Failed to set overlay parameters and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                MessageBox.Show("设置图像参数成功！");
            }

            Marshal.FreeHGlobal(ptrShowStrCfg);
        }

        private void btnMotionCfg_Click(object sender, EventArgs e)
        {
            MotionDetect dlg = new MotionDetect();
            dlg.m_lUserID = m_lUserID;
            dlg.m_struDeviceInfo = m_struDeviceInfo;
            dlg.m_struPicCfgV40 = m_struPicCfgV40;
            dlg.m_lChannel = m_lChannel;
            dlg.ShowDialog();
            m_struPicCfgV40 = dlg.m_struPicCfgV40;
        }
    }
}
