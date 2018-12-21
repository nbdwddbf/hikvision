using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace PreviewDemo
{
    public partial class PreSet : Form
    {
        public int m_lUserID = -1;
        public int m_lRealHandle = -1;
        public int m_lChannel =1;
        private bool bAuto = false;
        private uint iLastErr = 0;
        public int PreSetNo = 0;
        public CHCNetSDK.NET_DVR_PTZPOS m_struPtzCfg;
        public CHCNetSDK.NET_DVR_PTZSCOPE m_struPtzCfg1;
        public CHCNetSDK.NET_DVR_PRESET_NAME[] m_struPreSetCfg = new CHCNetSDK.NET_DVR_PRESET_NAME[300];

        private string str = "";
        
        public PreSet()
        {
            InitializeComponent();
        }
        private void PreSet_Load(object sender, EventArgs e)
        {
            comboBoxSpeed.SelectedIndex = 3;
            if (m_lRealHandle > -1)
            {
                checkBoxPreview.Checked = true;
            }
            else
            {
                checkBoxPreview.Checked = false;
            }
        }

        private void PreSetSet_Click(object sender, EventArgs e)
        {
            while (comboBox1.Text != "")
            {
                if (textBoxPanPos1.Text == "" || textBoxTiltPos1.Text == "" || textBoxZoomPos1.Text == "" || PreSetName.Text == "")
                {
                    MessageBox.Show("please input the Parameters");
                    return;
                }
                else
                {
                    PreSetNo = comboBox1.Items.IndexOf(comboBox1.Text);
                    m_struPreSetCfg[PreSetNo].byRes = new byte[58];
                    m_struPreSetCfg[PreSetNo].byRes1 = new byte[2];
                    Int32 nSize = Marshal.SizeOf(m_struPreSetCfg[PreSetNo]);
                    IntPtr ptrPreSetCfg = Marshal.AllocHGlobal(nSize);


                    m_struPreSetCfg[PreSetNo].dwSize = (uint)nSize;
                    /*str1 = "dddd";
                    m_struPreSetCfg[PreSetNo].byName = System.Text.Encoding.Default.GetBytes(str1);*/
                    /* m_struPreSetCfg[PreSetNo].byName = new byte[32];
                     m_struPreSetCfg[PreSetNo].byName[0] = 100;
                     m_struPreSetCfg[PreSetNo].byName[1] = 100;
                     m_struPreSetCfg[PreSetNo].byName[2] = 100;
                     m_struPreSetCfg[PreSetNo].byName[3] = 100;*/
                    byte[] byName = System.Text.Encoding.Default.GetBytes(PreSetName.Text);
                    m_struPreSetCfg[PreSetNo].byName = new byte[32];
                    byName.CopyTo(m_struPreSetCfg[PreSetNo].byName, 0);
                    /* m_struPreSetCfg[PreSetNo].wPanPos = new UInt16();
                    m_struPreSetCfg[PreSetNo].wPanPos = ushort.Parse(textBoxPanPos.Text);
                    /*  m_struPreSetCfg[PreSetNo].wTiltPos = ushort.Parse(textBoxTiltPos.Text);
                     m_struPreSetCfg[PreSetNo].wZoomPos = ushort.Parse(textBoxZoomPos.Text);*/

                    /*for (i = 0; i < 32; i++)
                    {
                        m_struPreSetCfg[PreSetNo].byName[i] = byte.Parse(str);
                    }*/
                    Marshal.StructureToPtr(m_struPreSetCfg[PreSetNo], ptrPreSetCfg, false);

                    //设置参数失败
                    if (!CHCNetSDK.NET_DVR_SetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_SET_PRESET_NAME, 1, ptrPreSetCfg, (UInt32)nSize))
                    {
                        iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                        str = "NET_DVR_SetDVRConfig failed, error code= " + iLastErr;
                        MessageBox.Show(str);
                        return;
                    }
                    else
                    {
                        m_struPreSetCfg[PreSetNo] = (CHCNetSDK.NET_DVR_PRESET_NAME)Marshal.PtrToStructure(ptrPreSetCfg, typeof(CHCNetSDK.NET_DVR_PRESET_NAME));
                        MessageBox.Show("设置成功" );
                    }
                    Marshal.FreeHGlobal(ptrPreSetCfg);
                    return;
                }
            }
            MessageBox.Show("please input the PtrPreSetNo");
        }

        private void PreSetGet_Click(object sender, EventArgs e)
        {
            while (comboBox1.Text != "")
            {
                PreSetNo = comboBox1.Items.IndexOf(comboBox1.Text);
                UInt32 dwReturn = 0;
                Int32 nSize = Marshal.SizeOf(m_struPreSetCfg[PreSetNo]);
                Int32 nOutBufSize = nSize * 300;
                IntPtr ptrPreSetCfg = Marshal.AllocHGlobal(nOutBufSize);
                int i;
                for (i = 0; i < 300; i++)
                {
                    //m_struPreSetCfg[i] = new CHCNetSDK.NET_DVR_PRESET_NAME();
                   /* if (i == PreSetNo)
                    {
                        textBoxPanPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wPanPos);
                        textBoxTiltPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wTiltPos);
                        textBoxZoomPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wZoomPos);
                    }*/
                    Marshal.StructureToPtr(m_struPreSetCfg[i], (IntPtr)((Int32)(ptrPreSetCfg)+ i * nSize), false);
                 
                }
                //获取参数失败
                if (!CHCNetSDK.NET_DVR_GetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_GET_PRESET_NAME, 1, ptrPreSetCfg, (UInt32)nOutBufSize, ref dwReturn))
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    str = "NET_DVR_GetDVRConfig failed, error code= " + iLastErr;
                    MessageBox.Show(str);
                    return;
                }
                else
                {
                    for (i = 0; i < 300; i++)
                    {
                        m_struPreSetCfg[i] = (CHCNetSDK.NET_DVR_PRESET_NAME)Marshal.PtrToStructure((IntPtr)((Int32)(ptrPreSetCfg) + i * nSize), typeof(CHCNetSDK.NET_DVR_PRESET_NAME));
                    }
                    textBoxPanPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wPanPos);
                    textBoxTiltPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wTiltPos);
                    textBoxZoomPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wZoomPos);
                    if (m_struPreSetCfg[PreSetNo].byName != null)
                    {
                        str = System.Text.Encoding.Default.GetString(m_struPreSetCfg[PreSetNo].byName);                     
                    }
                 
                    PreSetName.Text = str;
                    MessageBox.Show("获取成功");
                }
                Marshal.FreeHGlobal(ptrPreSetCfg);
                return;
               
            }
            MessageBox.Show("please input the PtrPreSetNo");
            
        }

        private void PreSetGo_Click(object sender, EventArgs e)
        {
            while (comboBox1.Text != "")
            {
                PreSetNo = comboBox1.Items.IndexOf(comboBox1.Text);
                if (!CHCNetSDK.NET_DVR_PTZPreset_Other(m_lUserID, 1, CHCNetSDK.GOTO_PRESET, (UInt32)(PreSetNo+1)))
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    str = "NET_DVR_PTZPreset_Other failed, error code= " + iLastErr;
                    MessageBox.Show(str);
                    return;
                }
                else
                {
                    /*if (m_struPreSetCfg[PreSetNo].wPanPos == 0)
                    {
                        MessageBox.Show("该预置点还没有设置");
                        return;
                    }*/
                    textBoxPanPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wPanPos);
                    textBoxTiltPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wTiltPos);
                    textBoxZoomPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wZoomPos);
                    if (m_struPreSetCfg[PreSetNo].byName != null)
                    {
                        PreSetName.Text = System.Text.Encoding.Default.GetString(m_struPreSetCfg[PreSetNo].byName);
                    }
                    MessageBox.Show("调用成功" );
                }
                return;
            }
            MessageBox.Show("please input the PtrPreSetNo");
        }


        private void btnLeft_MouseDown(object sender, MouseEventArgs e)
        {
            if (checkBoxPreview.Checked)
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed(m_lRealHandle, CHCNetSDK.PAN_LEFT, 0, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
            else
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed_Other(m_lUserID, m_lChannel, CHCNetSDK.PAN_LEFT, 0, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
        }

        private void btnLeft_MouseUp(object sender, MouseEventArgs e)
        {
            if (checkBoxPreview.Checked)
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed(m_lRealHandle, CHCNetSDK.PAN_LEFT, 1, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
            else
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed_Other(m_lUserID, m_lChannel, CHCNetSDK.PAN_LEFT, 1, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
        }

        private void btnUp_MouseDown(object sender, MouseEventArgs e)
        {
            if (checkBoxPreview.Checked)
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed(m_lRealHandle, CHCNetSDK.TILT_UP, 0, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
            else
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed_Other(m_lUserID, m_lChannel, CHCNetSDK.TILT_UP, 0, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
        }

        private void btnUp_MouseUp(object sender, MouseEventArgs e)
        {
            if (checkBoxPreview.Checked)
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed(m_lRealHandle, CHCNetSDK.TILT_UP, 1, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
            else
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed_Other(m_lUserID, m_lChannel, CHCNetSDK.TILT_UP, 1, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
        }

        private void btnRight_MouseDown(object sender, MouseEventArgs e)
        {
            if (checkBoxPreview.Checked)
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed(m_lRealHandle, CHCNetSDK.PAN_RIGHT, 0, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
            else
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed_Other(m_lUserID, m_lChannel, CHCNetSDK.PAN_RIGHT, 0, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
        }

        private void btnRight_MouseUp(object sender, MouseEventArgs e)
        {
            if (checkBoxPreview.Checked)
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed(m_lRealHandle, CHCNetSDK.PAN_RIGHT, 1, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
            else
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed_Other(m_lUserID, m_lChannel, CHCNetSDK.PAN_RIGHT, 1, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
        }

        private void btnDown_MouseDown(object sender, MouseEventArgs e)
        {
            if (checkBoxPreview.Checked)
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed(m_lRealHandle, CHCNetSDK.TILT_DOWN, 0, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
            else
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed_Other(m_lUserID, m_lChannel, CHCNetSDK.TILT_DOWN, 0, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
        }

        private void btnDown_MouseUp(object sender, MouseEventArgs e)
        {
            if (checkBoxPreview.Checked)
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed(m_lRealHandle, CHCNetSDK.TILT_DOWN, 1, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
            else
            {
                CHCNetSDK.NET_DVR_PTZControlWithSpeed_Other(m_lUserID, m_lChannel, CHCNetSDK.TILT_DOWN, 1, (uint)comboBoxSpeed.SelectedIndex + 1);
            }
        }

        private void btnAuto_Click(object sender, EventArgs e)
        {
            if (checkBoxPreview.Checked)
            {
                if (!bAuto)
                {
                    CHCNetSDK.NET_DVR_PTZControlWithSpeed(m_lRealHandle, CHCNetSDK.PAN_AUTO, 0, (uint)comboBoxSpeed.SelectedIndex + 1);
                    btnAuto.Text = "Stop";
                    bAuto = true;
                }
                else
                {
                    CHCNetSDK.NET_DVR_PTZControlWithSpeed(m_lRealHandle, CHCNetSDK.PAN_AUTO, 1, (uint)comboBoxSpeed.SelectedIndex + 1);
                    btnAuto.Text = "Auto";
                    bAuto = false;
                }
            }
            else
            {
                if (!bAuto)
                {
                    CHCNetSDK.NET_DVR_PTZControlWithSpeed_Other(m_lUserID, m_lChannel, CHCNetSDK.PAN_AUTO, 0, (uint)comboBoxSpeed.SelectedIndex + 1);
                    btnAuto.Text = "Stop";
                    bAuto = true;
                }
                else
                {
                    CHCNetSDK.NET_DVR_PTZControlWithSpeed_Other(m_lUserID, m_lChannel, CHCNetSDK.PAN_AUTO, 1, (uint)comboBoxSpeed.SelectedIndex + 1);
                    btnAuto.Text = "Auto";
                    bAuto = false;
                }
            }
        }

        private void btnUp_Click(object sender, EventArgs e)
        {

        }

        private void PreSet_Load_1(object sender, EventArgs e)
        {

        }

        private void PreSet_Set_Click(object sender, EventArgs e)
        {
            while (comboBox1.Text != "")
            {
                DialogResult dr;
                dr = MessageBox.Show("确认将当前点设置为预置点" + comboBox1.Text, "设置", MessageBoxButtons.YesNo,
                         MessageBoxIcon.Warning, MessageBoxDefaultButton.Button1);
                if (dr == DialogResult.Yes)
                {
                    PreSetNo = comboBox1.Items.IndexOf(comboBox1.Text);
                    if (!CHCNetSDK.NET_DVR_PTZPreset_Other(m_lUserID, 1, CHCNetSDK.SET_PRESET, (UInt32)(PreSetNo + 1)))
                    {
                        iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                        str = "NET_DVR_PTZPreset_Other failed, error code= " + iLastErr;
                        MessageBox.Show(str);
                        return;
                    }
                    else
                    {
                        textBoxPanPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wPanPos);
                        textBoxTiltPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wTiltPos);
                        textBoxZoomPos1.Text = Convert.ToString(0.1 * m_struPreSetCfg[PreSetNo].wZoomPos);
                        MessageBox.Show("设置成功");
                    }
                    return;
                }
                else return;
            }
            MessageBox.Show("please input the PtrPreSetNo");
        }

        private void PreSet_Delete_Click(object sender, EventArgs e)
        {
            while (comboBox1.Text != "")
            {
                DialogResult dr;
                dr = MessageBox.Show("确认删除预置点" + comboBox1.Text, "删除", MessageBoxButtons.YesNo,
                         MessageBoxIcon.Warning, MessageBoxDefaultButton.Button1);
                if (dr == DialogResult.Yes)
                {
                    PreSetNo = comboBox1.Items.IndexOf(comboBox1.Text);
                    if (!CHCNetSDK.NET_DVR_PTZPreset_Other(m_lUserID, 1, CHCNetSDK.CLE_PRESET, (UInt32)(PreSetNo + 1)))
                    {
                        iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                        str = "NET_DVR_PTZPreset_Other failed, error code= " + iLastErr;
                        MessageBox.Show(str);
                        return;
                    }
                    else
                    {
                        textBoxPanPos1.Text = Convert.ToString(0);
                        textBoxTiltPos1.Text = Convert.ToString(0);
                        textBoxZoomPos1.Text = Convert.ToString(1);
                        MessageBox.Show("删除成功");
                    }
                    return;
                }
                else return;
            }
            MessageBox.Show("please input the PtrPreSetNo");
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void PtzGet_Click(object sender, EventArgs e)
        {
            UInt32 dwReturn = 0;
            Int32 nSize = Marshal.SizeOf(m_struPtzCfg);
            IntPtr ptrPtzCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struPtzCfg, ptrPtzCfg, false);
            //获取参数失败
            if (!CHCNetSDK.NET_DVR_GetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_GET_PTZPOS, -1, ptrPtzCfg, (UInt32)nSize, ref dwReturn))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                str = "NET_DVR_GetDVRConfig failed, error code= " + iLastErr;
                MessageBox.Show(str);
                return;
            }
            else
            {
                m_struPtzCfg = (CHCNetSDK.NET_DVR_PTZPOS)Marshal.PtrToStructure(ptrPtzCfg, typeof(CHCNetSDK.NET_DVR_PTZPOS));
                //成功获取显示ptz参数
                ushort wPanPos = Convert.ToUInt16(Convert.ToString(m_struPtzCfg.wPanPos, 16));
                float WPanPos = wPanPos * 0.1f;
                textBoxPanPos.Text = Convert.ToString(WPanPos);
                ushort wTiltPos = Convert.ToUInt16(Convert.ToString(m_struPtzCfg.wTiltPos, 16));
                float WTiltPos = wTiltPos * 0.1f;
                textBoxTiltPos.Text = Convert.ToString(WTiltPos);
                ushort wZoomPos = Convert.ToUInt16(Convert.ToString(m_struPtzCfg.wZoomPos, 16));
                float WZoomPos = wZoomPos * 0.1f;
                textBoxZoomPos.Text = Convert.ToString(WZoomPos);
                /*textBoxPanPos.Text= Convert.ToString(Convert.ToUInt32(Convert.ToString(m_struPtzCfg.wPanPos,16))*0.1f,10);
                textBoxTiltPos.Text = Convert.ToString(Convert.ToUInt32(Convert.ToUInt32(Convert.ToString(m_struPtzCfg.wTiltPos, 16)) * 0.1f), 10);
                textBoxZoomPos.Text = Convert.ToString(Convert.ToUInt32(Convert.ToString(m_struPtzCfg.wZoomPos, 16)) * 0.1), 10);*/
                //textBoxPanPos.Text=Convert.ToString(m_struPtzCfg.wPanPos,16);
            }
            return;
        }

        private void PtzSet_Click(object sender, EventArgs e)
        {
            int flag = 1;
            float wPanPos, wTiltPos, wZoomPos;
            String str1, str2, str3;
            if (comboBox2.Text == "")
            {
                MessageBox.Show("Please input the operation type  ");
            }
            /* wPanPos = ushort.Parse(textBoxPanPos.Text);
             wTiltPos = ushort.Parse(textBoxTiltPos.Text);
             wZoomPos = ushort.Parse(textBoxZoomPos.Text);*/
            switch (comboBox2.Items.IndexOf(comboBox2.Text))//下拉框中的数据
            {
                case 0:

                    if (textBoxPanPos.Text == "" || textBoxTiltPos.Text == "" ||
                        textBoxZoomPos.Text == "")
                    {

                        MessageBox.Show("Please input prarameters of P,T,Z: ");
                        return;
                    }
                    else
                    {
                        flag = 0;
                        m_struPtzCfg.wAction = 1;
                        //m_struPtzCfg.wPanPos = ushort.Parse(textBoxPanPos.Text);
                        /* m_struPtzCfg.wPanPos = Convert.ToUInt16(wPanPos);
                          m_struPtzCfg.wTiltPos = wTiltPos;
                          m_struPtzCfg.wZoomPos = wZoomPos;*/
                        /* m_struPtzCfg.wPanPos = Convert.ToUInt16(Convert.ToString(Convert.ToUInt32(Convert.ToString(wPanPos * 10, 16)), 10));
                        m_struPtzCfg.wTiltPos = Convert.ToUInt16(Convert.ToString(Convert.ToUInt32(Convert.ToString(wTiltPos*10, 16)), 10));
                         m_struPtzCfg.wZoomPos = Convert.ToUInt16(Convert.ToString(Convert.ToUInt32(Convert.ToString(wZoomPos*10, 16)), 10));*/
                        str1 = Convert.ToString(float.Parse(textBoxPanPos.Text) * 10);
                        m_struPtzCfg.wPanPos = (ushort)(Convert.ToUInt16(str1, 16));
                        str2 = Convert.ToString(float.Parse(textBoxTiltPos.Text) * 10);
                        m_struPtzCfg.wTiltPos = (ushort)(Convert.ToUInt16(str2, 16));
                        str3 = Convert.ToString(float.Parse(textBoxZoomPos.Text) * 10);
                        m_struPtzCfg.wZoomPos = (ushort)(Convert.ToUInt16(str3, 16));
                        /* m_struPtzCfg.wTiltPos = ushort.Parse(textBoxTiltPos.Text);
                         m_struPtzCfg.wZoomPos = ushort.Parse(textBoxZoomPos.Text);*/
                    }
                    break;
                case 1:
                    if (textBoxPanPos.Text == "")
                    {
                        MessageBox.Show("Please input prarameters of P: ");
                        return;
                    }
                    else
                    {
                        flag = 0;
                        m_struPtzCfg.wAction = 2;

                        //wPanPos = float.Parse(textBoxPanPos.Text);
                        str1 = Convert.ToString(float.Parse(textBoxPanPos.Text) * 10);
                        m_struPtzCfg.wPanPos = (ushort)(Convert.ToUInt16(str1, 16));

                        //m_struPtzCfg.wPanPos = ushort.Parse(textBoxPanPos.Text);

                    }
                    break;
                case 2:
                    if (textBoxTiltPos.Text == "")
                    {
                        MessageBox.Show("Please input prarameters of T: ");
                        return;
                    }
                    else
                    {
                        flag = 0;
                        m_struPtzCfg.wAction = 3;
                        m_struPtzCfg.wTiltPos = ushort.Parse(textBoxTiltPos.Text);

                        str2 = Convert.ToString(float.Parse(textBoxTiltPos.Text) * 10);
                        m_struPtzCfg.wTiltPos = (ushort)(Convert.ToUInt16(str2, 16));

                    }
                    break;
                case 3:
                    if (textBoxZoomPos.Text == "")
                    {
                        MessageBox.Show("Please input prarameters of Z: ");
                        return;
                    }
                    else
                    {
                        flag = 0;
                        m_struPtzCfg.wAction = 4;
                        m_struPtzCfg.wZoomPos = ushort.Parse(textBoxZoomPos.Text);

                        str3 = Convert.ToString(float.Parse(textBoxZoomPos.Text) * 10);
                        m_struPtzCfg.wZoomPos = (ushort)(Convert.ToUInt16(str3, 16));
                    }
                    break;
                case 4:
                    if (textBoxTiltPos.Text == "" || textBoxPanPos.Text == "")
                    {
                        MessageBox.Show("Please input prarameters of P,T: ");
                        return;
                    }
                    else
                    {
                        flag = 0;
                        m_struPtzCfg.wAction = 5;
                        m_struPtzCfg.wPanPos = ushort.Parse(textBoxPanPos.Text);
                        m_struPtzCfg.wTiltPos = ushort.Parse(textBoxTiltPos.Text);

                        str1 = Convert.ToString(float.Parse(textBoxPanPos.Text) * 10);
                        m_struPtzCfg.wPanPos = (ushort)(Convert.ToUInt16(str1, 16));
                        str2 = Convert.ToString(float.Parse(textBoxTiltPos.Text) * 10);
                        m_struPtzCfg.wTiltPos = (ushort)(Convert.ToUInt16(str2, 16));

                    }
                    break;


            }


            while (flag == 0)
            {

                Int32 nSize = Marshal.SizeOf(m_struPtzCfg);
                IntPtr ptrPtzCfg = Marshal.AllocHGlobal(nSize);
                Marshal.StructureToPtr(m_struPtzCfg, ptrPtzCfg, false);

                if (!CHCNetSDK.NET_DVR_SetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_SET_PTZPOS, 1, ptrPtzCfg, (UInt32)nSize))
                {
                    iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                    str = "NET_DVR_SetDVRConfig failed, error code= " + iLastErr;
                    //设置POS参数失败
                    MessageBox.Show(str);
                    return;
                }
                else
                {
                    MessageBox.Show("设置成功!");
                    break;
                }

                Marshal.FreeHGlobal(ptrPtzCfg);

            }
            return;
        }

        private void PtzRange_Click(object sender, EventArgs e)
        {
            UInt32 dwReturn = 0;
            Int32 nSize = Marshal.SizeOf(m_struPtzCfg1);
            IntPtr ptrPtzCfg = Marshal.AllocHGlobal(nSize);
            Marshal.StructureToPtr(m_struPtzCfg1, ptrPtzCfg, false);

            //获取参数失败
            if (!CHCNetSDK.NET_DVR_GetDVRConfig(m_lUserID, CHCNetSDK.NET_DVR_GET_PTZSCOPE, -1, ptrPtzCfg, (UInt32)nSize, ref dwReturn))
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                str = "NET_DVR_GetDVRConfig failed, error code= " + iLastErr;
                MessageBox.Show(str);
                return;
            }
            else
            {
                m_struPtzCfg1 = (CHCNetSDK.NET_DVR_PTZSCOPE)Marshal.PtrToStructure(ptrPtzCfg, typeof(CHCNetSDK.NET_DVR_PTZSCOPE));
                //成功获取显示ptz参数范围
                ushort wPanPosMax = Convert.ToUInt16(Convert.ToString(m_struPtzCfg1.wPanPosMax, 16));
                float WPanPosMax = wPanPosMax * 0.1f;
                ushort wTiltPosMax = Convert.ToUInt16(Convert.ToString(m_struPtzCfg1.wTiltPosMax, 16));
                float WTiltPosMax = wTiltPosMax * 0.1f;
                ushort wZoomPosMax = Convert.ToUInt16(Convert.ToString(m_struPtzCfg1.wZoomPosMax, 16));
                float WZoomPosMax = wZoomPosMax * 0.1f;
                ushort wPanPosMin = Convert.ToUInt16(Convert.ToString(m_struPtzCfg1.wPanPosMin, 16));
                float WPanPosMin = wPanPosMin * 0.1f;
                ushort wTiltPosMin = Convert.ToUInt16(Convert.ToString(m_struPtzCfg1.wTiltPosMin, 16));
                float WTiltPosMin = wTiltPosMin * 0.1f;
                ushort wZoomPosMin = Convert.ToUInt16(Convert.ToString(m_struPtzCfg1.wZoomPosMin, 16));
                float WZoomPosMin = wZoomPosMin * 0.1f;

                str = "PMax=" + WPanPosMax + "    TMax=" + WTiltPosMax + "  ZMax=" + WZoomPosMax + "   PMin=" + WPanPosMin + "    TMin=" + WTiltPosMin + "  ZMin=" + WZoomPosMin;
                label13.Text = str;

            }
            return;
        }

        private void btnLeft_Click(object sender, EventArgs e)
        {

        }

        private void checkBoxPreview_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }
    }
}


