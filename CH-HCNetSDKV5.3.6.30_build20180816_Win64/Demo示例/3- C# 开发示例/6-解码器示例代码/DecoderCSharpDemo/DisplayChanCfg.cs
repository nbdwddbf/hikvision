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
    public partial class DisplayChanCfg : Form
    {
        public CHCNetSDK.NET_DVR_MATRIX_ABILITY_V41 m_struDecAbility = new CHCNetSDK.NET_DVR_MATRIX_ABILITY_V41();
        public CHCNetSDK.NET_DVR_MATRIX_VOUTCFG m_struDisplayCfg = new CHCNetSDK.NET_DVR_MATRIX_VOUTCFG();
        public int iDisplayNo = 1;
        public int iDisplayIndex = 0;
        public Int32 m_lUserID = -1;
        private uint iLastErr = 0;
        private string strErr;
        private int i = 0;
        private int iIndex = 0;
        private string str;
        private uint[] dwSupportResolution = new uint[32];

        public DisplayChanCfg()
        {
            InitializeComponent();
            comboBoxWinMode.ResetText();
        }

        private void checkBoxAudio_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxAudio.Checked)
            {
                comboBoxAudio.Enabled = true;
            }
            else
            {
                comboBoxAudio.Enabled = false;
            }
        }     

        private string GetResolutionString(uint dwRes)
        {
            string lpResString = ""; 
            switch (dwRes)
            {
                case CHCNetSDK.NOT_AVALIABLE:
                    lpResString = "NOT_AVALIABLE";
                    break;
                case CHCNetSDK.SVGA_60HZ:
                    lpResString = "SVGA_60HZ";
                    break;
                case CHCNetSDK.SVGA_75HZ:
                    lpResString = "SVGA_75HZ";
                    break;
                case CHCNetSDK.XGA_60HZ:
                    lpResString = "XGA_60HZ";
                    break;
                case CHCNetSDK.XGA_75HZ:
                    lpResString = "XGA_75HZ";
                    break;
                case CHCNetSDK.SXGA_60HZ:
                    lpResString = "SXGA_60HZ";
                    break;
                case CHCNetSDK.SXGA2_60HZ:
                    lpResString = "SXGA2_60HZ";
                    break;
                case CHCNetSDK._720P_60HZ:
                    lpResString = "_720P_60HZ";
                    break;
                case CHCNetSDK._720P_50HZ:
                    lpResString = "_720P_50HZ";
                    break;
                case CHCNetSDK._1080I_60HZ:
                    lpResString = "_1080I_60HZ";
                    break;
                case CHCNetSDK._1080I_50HZ:
                    lpResString = "_1080I_50HZ";
                    break;
                case CHCNetSDK._1080P_60HZ:
                    lpResString = "_1080P_60HZ";
                    break;
                case CHCNetSDK._1080P_50HZ:
                    lpResString = "_1080P_50HZ";
                    break;
                case CHCNetSDK._1080P_30HZ:
                    lpResString = "_1080P_30HZ";
                    break;
                case CHCNetSDK._1080P_25HZ:
                    lpResString = "_1080P_25HZ";
                    break;
                case CHCNetSDK._1080P_24HZ:
                    lpResString = "_1080P_24HZ";
                    break;
                case CHCNetSDK.UXGA_60HZ:
                    lpResString = "UXGA_60HZ";
                    break;
                case CHCNetSDK.UXGA_30HZ:
                    lpResString = "UXGA_30HZ";
                    break;
                case CHCNetSDK.WSXGA_60HZ:
                    lpResString = "WSXGA_60HZ";
                    break;
                case CHCNetSDK.WUXGA_60HZ:
                    lpResString = "WUXGA_60HZ";
                    break;
                case CHCNetSDK.WUXGA_30HZ:
                    lpResString = "WUXGA_30HZ";
                    break;
                case CHCNetSDK.WXGA_60HZ:
                    lpResString = "WXGA_60HZ";
                    break;
                default:
                    break;
            }
            return lpResString;        
        }
        private void DisplayChanCfg_Load(object sender, EventArgs e)
        {  
            comboBoxWinMode.Items.Clear();
            comboBoxWinMode.SelectedIndex = -1;
            comboBoxWinMode.Text = "";

            comboBoxResolution.Items.Clear();
            comboBoxResolution.SelectedIndex = -1;
            comboBoxResolution.Text = "";

            int iKeep = 0;
            int j = 0;

            //VGA输出
            if (iDisplayIndex < m_struDecAbility.struVgaInfo.byChanNums)  
            {
                //画面分割模式 Window mode
                for (i = 0; i < CHCNetSDK.MAX_DISPNUM_V41; i++)
                {
                    if (m_struDecAbility.struDispMode[i].byDispChanType != 1)
                    {
                        continue;
                    }
                    break;
                }
                iKeep = i + iDisplayIndex;
                for (i = 0; i < CHCNetSDK.MAX_WINDOWS_NUM; i++)
                {
                    if (m_struDecAbility.struDispMode[iKeep].byDispMode[i] != 0)
                    {
                        str = String.Format("{0}", m_struDecAbility.struDispMode[iKeep].byDispMode[i]);
                        comboBoxWinMode.Items.Add(str);
                    }
                }
                //分辨率 Resolution
                for (i = 0; i < CHCNetSDK.MAX_SUPPORT_RES; i++)
                {
                    string sResStr= "";
                    sResStr= GetResolutionString(m_struDecAbility.struVgaInfo.dwSupportResolution[i]);
                    if (comboBoxResolution.FindStringExact(sResStr, 0) == -1)
                    {
                        comboBoxResolution.Items.Add(sResStr);
                        iIndex = comboBoxResolution.FindStringExact(sResStr, 0);
                        dwSupportResolution[j++] = m_struDecAbility.struVgaInfo.dwSupportResolution[i];
                    }
                }
            }

            //BNC输出
            if ((iDisplayIndex >= m_struDecAbility.struVgaInfo.byChanNums) && (iDisplayIndex < m_struDecAbility.struVgaInfo.byChanNums + m_struDecAbility.struBncInfo.byChanNums))
            {
                //画面分割模式 Window mode
                for (i = 0; i < CHCNetSDK.MAX_DISPNUM_V41; i++)
                {
                    if (m_struDecAbility.struDispMode[i].byDispChanType != 0)
                    {
                        continue;
                    }
                    break;
                }
                iKeep = i + iDisplayIndex - m_struDecAbility.struVgaInfo.byChanNums;
                for (i = 0; i < CHCNetSDK.MAX_WINDOWS_NUM; i++)
                {
                    if (m_struDecAbility.struDispMode[iKeep].byDispMode[i] != 0)
                    {
                        str = String.Format("{0}", m_struDecAbility.struDispMode[iKeep].byDispMode[i]);
                        comboBoxWinMode.Items.Add(str);
                    }
                }

                //分辨率 Resolution
                for (i = 0; i < CHCNetSDK.MAX_SUPPORT_RES; i++)
                {
                    string sResStr = "";
                    sResStr = GetResolutionString(m_struDecAbility.struBncInfo.dwSupportResolution[i]);
                    if (comboBoxResolution.FindStringExact(sResStr, 0) == -1)
                    {
                        comboBoxResolution.Items.Add(sResStr);
                        iIndex = comboBoxResolution.FindStringExact(sResStr, 0);
                        dwSupportResolution[j++] = m_struDecAbility.struBncInfo.dwSupportResolution[i];
                    }
                }
            }

            //HDMI输出
            if ((iDisplayIndex >= m_struDecAbility.struVgaInfo.byChanNums + m_struDecAbility.struBncInfo.byChanNums) && (iDisplayIndex < m_struDecAbility.struVgaInfo.byChanNums + m_struDecAbility.struBncInfo.byChanNums + m_struDecAbility.struHdmiInfo.byChanNums))
            {
                //画面分割模式 Window mode
                for (i = 0; i < CHCNetSDK.MAX_DISPNUM_V41; i++)
                {
                    if (m_struDecAbility.struDispMode[i].byDispChanType != 2)
                    {
                        continue;
                    }
                    break;
                }
                iKeep = i + iDisplayIndex - m_struDecAbility.struVgaInfo.byChanNums - m_struDecAbility.struBncInfo.byChanNums;
                for (i = 0; i < CHCNetSDK.MAX_WINDOWS_NUM; i++)
                {
                    if (m_struDecAbility.struDispMode[iKeep].byDispMode[i] != 0)
                    {
                        str = String.Format("{0}", m_struDecAbility.struDispMode[iKeep].byDispMode[i]);
                        comboBoxWinMode.Items.Add(str);
                    }
                }

                //分辨率 Resolution
                for (i = 0; i < CHCNetSDK.MAX_SUPPORT_RES; i++)
                {
                    string sResStr = "";
                    sResStr = GetResolutionString(m_struDecAbility.struHdmiInfo.dwSupportResolution[i]);
                    if (comboBoxResolution.FindStringExact(sResStr, 0) == -1)
                    {
                        comboBoxResolution.Items.Add(sResStr);
                        iIndex = comboBoxResolution.FindStringExact(sResStr, 0);
                        dwSupportResolution[j++] = m_struDecAbility.struHdmiInfo.dwSupportResolution[i];
                    }
                }
            }

            //DVI输出
            if ((iDisplayIndex >= m_struDecAbility.struVgaInfo.byChanNums + m_struDecAbility.struBncInfo.byChanNums + m_struDecAbility.struHdmiInfo.byChanNums) && (iDisplayIndex < m_struDecAbility.struVgaInfo.byChanNums + m_struDecAbility.struBncInfo.byChanNums + m_struDecAbility.struHdmiInfo.byChanNums + m_struDecAbility.struDviInfo.byChanNums))
            {
                //画面分割模式 Window mode
                for (i = 0; i < CHCNetSDK.MAX_DISPNUM_V41; i++)
                {
                    if (m_struDecAbility.struDispMode[i].byDispChanType != 3)
                    {
                        continue;
                    }
                    break;
                }
                iKeep = i + iDisplayIndex - m_struDecAbility.struVgaInfo.byChanNums - m_struDecAbility.struBncInfo.byChanNums - m_struDecAbility.struHdmiInfo.byChanNums;
                for (i = 0; i < CHCNetSDK.MAX_WINDOWS_NUM; i++)
                {
                    if (m_struDecAbility.struDispMode[iKeep].byDispMode[i] != 0)
                    {
                        str = String.Format("{0}", m_struDecAbility.struDispMode[iKeep].byDispMode[i]);
                        comboBoxWinMode.Items.Add(str);
                    }
                }

                //分辨率 Resolution
                for (i = 0; i < CHCNetSDK.MAX_SUPPORT_RES; i++)
                {
                    string sResStr = "";
                    sResStr = GetResolutionString(m_struDecAbility.struDviInfo.dwSupportResolution[i]);
                    if (comboBoxResolution.FindStringExact(sResStr, 0) == -1)
                    {
                        comboBoxResolution.Items.Add(sResStr);
                        iIndex = comboBoxResolution.FindStringExact(sResStr, 0);
                        dwSupportResolution[j++] = m_struDecAbility.struDviInfo.dwSupportResolution[i];
                    }
                }
            }

            btnGetDispCfg_Click(sender, e);
        }

        private void comboBoxWinMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            comboBoxSubWin.Items.Clear();
            comboBoxSubWin.SelectedIndex = -1;
            comboBoxSubWin.Text = "";

            comboBoxAudio.Items.Clear();
            comboBoxAudio.SelectedIndex = -1;
            comboBoxAudio.Text = "";

            comboBoxEnlarge.Items.Clear();
            comboBoxEnlarge.SelectedIndex = -1;
            comboBoxEnlarge.Text = "";

            comboBoxDecNo.Items.Clear();
            comboBoxDecNo.SelectedIndex = -1;
            comboBoxDecNo.Text = "";

            //画面分割模式 Window mode
            string iWinMode = (string)comboBoxWinMode.SelectedItem;
            Int32 iWindowMode = Int32.Parse(iWinMode);
            for (i = 0; i < iWindowMode; i++)
            {
                str = String.Format("{0}", i+1);
                comboBoxSubWin.Items.Add(str);
                comboBoxAudio.Items.Add(str);
                comboBoxEnlarge.Items.Add(str);
            }

            //窗口关联的解码通道 The decoding channel assocaited with the sub window
            for (i = 0; i < m_struDecAbility.byDecChanNums; i++)
            {
                str = String.Format("{0}", i+1);
                comboBoxDecNo.Items.Add(str);
            }

            comboBoxSubWin.SelectedIndex = 0;
            comboBoxAudio.SelectedIndex = 0;
            comboBoxEnlarge.SelectedIndex = 0;

            updateDisplayCfg();
        }

        private void comboBoxSubWin_SelectedIndexChanged(object sender, EventArgs e)
        {
            str = String.Format("{0}", m_struDisplayCfg.byJoinDecChan[comboBoxSubWin.SelectedIndex]);
            iIndex = comboBoxDecNo.FindStringExact(str, 0);
            if (iIndex != -1)
            {
                comboBoxDecNo.SelectedIndex = iIndex;
            }
            else 
            {
                comboBoxDecNo.SelectedIndex = -1;
            }
        }

        private void updateDisplayCfg()
        {
            comboBoxFormat.SelectedIndex = m_struDisplayCfg.byVedioFormat;//视频制式 Video format

            //分辨率 Resolution
            str = GetResolutionString(m_struDisplayCfg.dwResolution);
            iIndex = comboBoxResolution.FindStringExact(str, 0);
            if (iIndex != -1)
            {
                comboBoxResolution.SelectedIndex = iIndex;
            }

            //是否处于放大状态 Enlarge or not
            if (m_struDisplayCfg.byEnlargeStatus == 0)
            {
                checkBoxEnlarge.Checked = false;
            }
            else
            {
                checkBoxEnlarge.Checked = true;
                str = String.Format("{0}", m_struDisplayCfg.byEnlargeSubWindowIndex);
                iIndex = comboBoxEnlarge.FindStringExact(str, 0);
                if (iIndex != -1)
                {
                    comboBoxEnlarge.SelectedIndex = iIndex;
                }
            }

            //音频是否开启 Start audio or not
            if (m_struDisplayCfg.byAudio == 0)
            {
                checkBoxAudio.Checked = false;
            }
            else
            {
                checkBoxAudio.Checked = true;
                str = String.Format("{0}", m_struDisplayCfg.byAudioWindowIdx);
                iIndex = comboBoxAudio.FindStringExact(str, 0);
                if (iIndex != -1)
                {
                    comboBoxAudio.SelectedIndex = iIndex;
                }
            }

            comboBoxScale.SelectedIndex = m_struDisplayCfg.byScale; //显示模式 Display mode                 
        }

        private void btnGetDispCfg_Click(object sender, EventArgs e)
        {
            if (!CHCNetSDK.NET_DVR_MatrixGetDisplayCfg_V41(m_lUserID, (uint)iDisplayNo, ref m_struDisplayCfg))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_MatrixGetDisplayCfg_V41 failed, error code= " + iLastErr;
                //获取显示通道配置失败，输出错误号 Failed to get the display configuration of decoder and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                //画面模式 Window Mode
                str = String.Format("{0}", m_struDisplayCfg.dwWindowMode);
                iIndex = comboBoxWinMode.FindStringExact(str, 0);
                if (iIndex != -1)
                {
                    comboBoxWinMode.SelectedIndex = iIndex;
                }

                updateDisplayCfg();
            }
        }

        private void btnSubWin_Click(object sender, EventArgs e)
        {
            m_struDisplayCfg.byJoinDecChan[comboBoxSubWin.SelectedIndex] = (byte)(comboBoxDecNo.SelectedIndex + 1);
        }

        private void btnSetDispCfg_Click(object sender, EventArgs e)
        {
            string iWinMode = (string)comboBoxWinMode.SelectedItem;
            m_struDisplayCfg.dwWindowMode = uint.Parse(iWinMode);

            if (checkBoxAudio.Checked)
            {
                m_struDisplayCfg.byAudio = 1;
                m_struDisplayCfg.byAudioWindowIdx = (byte)(comboBoxAudio.SelectedIndex + 1);
            }
            else
            {
                m_struDisplayCfg.byAudio = 0;
            }      

            m_struDisplayCfg.byVedioFormat = (byte)comboBoxFormat.SelectedIndex;
            m_struDisplayCfg.dwResolution = dwSupportResolution[comboBoxResolution.SelectedIndex];
            m_struDisplayCfg.byScale = (byte)comboBoxScale.SelectedIndex;

            if (!CHCNetSDK.NET_DVR_MatrixSetDisplayCfg_V41(m_lUserID, (uint)iDisplayNo, ref m_struDisplayCfg))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_MatrixSetDisplayCfg_V41 failed, error code= " + iLastErr;
                //设置显示通道配置失败，输出错误号 Failed to get the display configuration of decoder and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                MessageBox.Show("Successful to set the display parameters!");
            }
        }

        private void btnEnlarge_Click(object sender, EventArgs e)
        {
            if (!CHCNetSDK.NET_DVR_MatrixDiaplayControl(m_lUserID, (uint)iDisplayNo, 1, (uint)comboBoxEnlarge.SelectedIndex + 1))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_MatrixDiaplayControl failed, error code= " + iLastErr;
                //显示通道控制窗口放大失败，输出错误号 Failed to enlarge the window and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                checkBoxEnlarge.Checked = true;
            }
        }

        private void btnResume_Click(object sender, EventArgs e)
        {
            if (!CHCNetSDK.NET_DVR_MatrixDiaplayControl(m_lUserID, (uint)iDisplayNo, 2, (uint)comboBoxEnlarge.SelectedIndex + 1))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_MatrixDiaplayControl failed, error code= " + iLastErr;
                //显示通道控制窗口放大恢复失败，输出错误号 Failed to resume the window and output the error code
                MessageBox.Show(strErr);
            }
            else
            {
                checkBoxEnlarge.Checked = false;
            }
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
            this.Dispose(); 
        }      
    }
}
