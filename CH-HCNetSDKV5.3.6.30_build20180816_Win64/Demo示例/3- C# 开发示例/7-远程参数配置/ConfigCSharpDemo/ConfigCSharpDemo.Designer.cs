namespace ConfigCSharpDemo
{
    partial class ConfigCSharpDemo
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (m_lUserID >= 0)
            {
                CHCNetSDK.NET_DVR_Logout(m_lUserID);
            }
            if (m_bInitSDK == true)
            {
                CHCNetSDK.NET_DVR_Cleanup();
            }

            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxPassword = new System.Windows.Forms.TextBox();
            this.textBoxUserName = new System.Windows.Forms.TextBox();
            this.textBoxPort = new System.Windows.Forms.TextBox();
            this.textBoxIP = new System.Windows.Forms.TextBox();
            this.btnLogin = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnExit = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnDevCfgGet = new System.Windows.Forms.Button();
            this.btnDevCfgSet = new System.Windows.Forms.Button();
            this.textBoxDevVersion = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.textBoxNetNum = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.textBoxAlarmOutNum = new System.Windows.Forms.TextBox();
            this.textBoxAlarmInNum = new System.Windows.Forms.TextBox();
            this.textBoxZeroNum = new System.Windows.Forms.TextBox();
            this.textBoxIPNum = new System.Windows.Forms.TextBox();
            this.textBoxANum = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.textBoxDevSerial = new System.Windows.Forms.TextBox();
            this.textBoxDevType = new System.Windows.Forms.TextBox();
            this.textBoxDevName = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnNetCfgGet = new System.Windows.Forms.Button();
            this.btnNetCfgSet = new System.Windows.Forms.Button();
            this.textBoxSdkCfg = new System.Windows.Forms.TextBox();
            this.label25 = new System.Windows.Forms.Label();
            this.textBoxHttpCfg = new System.Windows.Forms.TextBox();
            this.label26 = new System.Windows.Forms.Label();
            this.textBoxHostPort = new System.Windows.Forms.TextBox();
            this.label27 = new System.Windows.Forms.Label();
            this.textBoxHostIP = new System.Windows.Forms.TextBox();
            this.label28 = new System.Windows.Forms.Label();
            this.textBoxPPPoEPsw = new System.Windows.Forms.TextBox();
            this.label24 = new System.Windows.Forms.Label();
            this.textBoxPPPoeName = new System.Windows.Forms.TextBox();
            this.label21 = new System.Windows.Forms.Label();
            this.checkBoxPPPoe = new System.Windows.Forms.CheckBox();
            this.checkBoxDhcp = new System.Windows.Forms.CheckBox();
            this.textBoxDns = new System.Windows.Forms.TextBox();
            this.label23 = new System.Windows.Forms.Label();
            this.textBoxSubMask = new System.Windows.Forms.TextBox();
            this.label22 = new System.Windows.Forms.Label();
            this.textBoxGateWay = new System.Windows.Forms.TextBox();
            this.label20 = new System.Windows.Forms.Label();
            this.textBoxIPAddr = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.textBoxSecond = new System.Windows.Forms.TextBox();
            this.label32 = new System.Windows.Forms.Label();
            this.textBoxMinute = new System.Windows.Forms.TextBox();
            this.label31 = new System.Windows.Forms.Label();
            this.textBoxHour = new System.Windows.Forms.TextBox();
            this.textBoxDay = new System.Windows.Forms.TextBox();
            this.label30 = new System.Windows.Forms.Label();
            this.textBoxMonth = new System.Windows.Forms.TextBox();
            this.label29 = new System.Windows.Forms.Label();
            this.textBoxYear = new System.Windows.Forms.TextBox();
            this.btnTimeSet = new System.Windows.Forms.Button();
            this.btnTimeGet = new System.Windows.Forms.Button();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.btnChanCfg = new System.Windows.Forms.Button();
            this.label33 = new System.Windows.Forms.Label();
            this.comboBoxChan = new System.Windows.Forms.ComboBox();
            this.groupBox3.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(221, 70);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(29, 12);
            this.label8.TabIndex = 27;
            this.label8.Text = "密码";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(18, 70);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 12);
            this.label7.TabIndex = 26;
            this.label7.Text = "用户名";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(219, 25);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 25;
            this.label6.Text = "设备端口";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(18, 25);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 24;
            this.label5.Text = "设备IP";
            // 
            // textBoxPassword
            // 
            this.textBoxPassword.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.textBoxPassword.Location = new System.Drawing.Point(295, 65);
            this.textBoxPassword.Name = "textBoxPassword";
            this.textBoxPassword.PasswordChar = '*';
            this.textBoxPassword.Size = new System.Drawing.Size(112, 21);
            this.textBoxPassword.TabIndex = 23;
            this.textBoxPassword.Text = "12345";
            // 
            // textBoxUserName
            // 
            this.textBoxUserName.Location = new System.Drawing.Point(86, 64);
            this.textBoxUserName.Name = "textBoxUserName";
            this.textBoxUserName.Size = new System.Drawing.Size(114, 21);
            this.textBoxUserName.TabIndex = 22;
            this.textBoxUserName.Text = "admin";
            // 
            // textBoxPort
            // 
            this.textBoxPort.Location = new System.Drawing.Point(295, 19);
            this.textBoxPort.Name = "textBoxPort";
            this.textBoxPort.Size = new System.Drawing.Size(112, 21);
            this.textBoxPort.TabIndex = 21;
            this.textBoxPort.Text = "8000";
            // 
            // textBoxIP
            // 
            this.textBoxIP.Location = new System.Drawing.Point(86, 18);
            this.textBoxIP.Name = "textBoxIP";
            this.textBoxIP.Size = new System.Drawing.Size(114, 21);
            this.textBoxIP.TabIndex = 20;
            this.textBoxIP.Text = "10.16.2.2";
            // 
            // btnLogin
            // 
            this.btnLogin.Location = new System.Drawing.Point(424, 19);
            this.btnLogin.Name = "btnLogin";
            this.btnLogin.Size = new System.Drawing.Size(64, 63);
            this.btnLogin.TabIndex = 19;
            this.btnLogin.Text = "登录设备 Login";
            this.btnLogin.Click += new System.EventHandler(this.btnLogin_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(20, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 10);
            this.label1.TabIndex = 16;
            this.label1.Text = "Device IP";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(20, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 15);
            this.label2.TabIndex = 15;
            this.label2.Text = "User Name";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(219, 56);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 16);
            this.label3.TabIndex = 18;
            this.label3.Text = "Password";
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(219, 12);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(79, 17);
            this.label4.TabIndex = 17;
            this.label4.Text = "Device Port";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btnLogin);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Location = new System.Drawing.Point(4, -1);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(524, 97);
            this.groupBox3.TabIndex = 41;
            this.groupBox3.TabStop = false;
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(545, 16);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(75, 69);
            this.btnExit.TabIndex = 46;
            this.btnExit.Text = "退出 Exit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnDevCfgGet);
            this.groupBox1.Controls.Add(this.btnDevCfgSet);
            this.groupBox1.Controls.Add(this.textBoxDevVersion);
            this.groupBox1.Controls.Add(this.label18);
            this.groupBox1.Controls.Add(this.textBoxNetNum);
            this.groupBox1.Controls.Add(this.label17);
            this.groupBox1.Controls.Add(this.textBoxAlarmOutNum);
            this.groupBox1.Controls.Add(this.textBoxAlarmInNum);
            this.groupBox1.Controls.Add(this.textBoxZeroNum);
            this.groupBox1.Controls.Add(this.textBoxIPNum);
            this.groupBox1.Controls.Add(this.textBoxANum);
            this.groupBox1.Controls.Add(this.label16);
            this.groupBox1.Controls.Add(this.label15);
            this.groupBox1.Controls.Add(this.label14);
            this.groupBox1.Controls.Add(this.label13);
            this.groupBox1.Controls.Add(this.label12);
            this.groupBox1.Controls.Add(this.textBoxDevSerial);
            this.groupBox1.Controls.Add(this.textBoxDevType);
            this.groupBox1.Controls.Add(this.textBoxDevName);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Location = new System.Drawing.Point(5, 102);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(641, 142);
            this.groupBox1.TabIndex = 47;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "设备信息 Device  Info.";
            // 
            // btnDevCfgGet
            // 
            this.btnDevCfgGet.Location = new System.Drawing.Point(463, 112);
            this.btnDevCfgGet.Name = "btnDevCfgGet";
            this.btnDevCfgGet.Size = new System.Drawing.Size(75, 23);
            this.btnDevCfgGet.TabIndex = 55;
            this.btnDevCfgGet.Text = "刷新";
            this.btnDevCfgGet.UseVisualStyleBackColor = true;
            this.btnDevCfgGet.Click += new System.EventHandler(this.btnDevCfgGet_Click);
            // 
            // btnDevCfgSet
            // 
            this.btnDevCfgSet.Location = new System.Drawing.Point(554, 112);
            this.btnDevCfgSet.Name = "btnDevCfgSet";
            this.btnDevCfgSet.Size = new System.Drawing.Size(75, 23);
            this.btnDevCfgSet.TabIndex = 48;
            this.btnDevCfgSet.Text = "设置";
            this.btnDevCfgSet.UseVisualStyleBackColor = true;
            this.btnDevCfgSet.Click += new System.EventHandler(this.btnDevCfg_Click);
            // 
            // textBoxDevVersion
            // 
            this.textBoxDevVersion.Location = new System.Drawing.Point(503, 20);
            this.textBoxDevVersion.Name = "textBoxDevVersion";
            this.textBoxDevVersion.ReadOnly = true;
            this.textBoxDevVersion.Size = new System.Drawing.Size(126, 21);
            this.textBoxDevVersion.TabIndex = 54;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(414, 23);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(83, 12);
            this.label18.TabIndex = 53;
            this.label18.Text = "设备主控版本:";
            // 
            // textBoxNetNum
            // 
            this.textBoxNetNum.Location = new System.Drawing.Point(551, 51);
            this.textBoxNetNum.Name = "textBoxNetNum";
            this.textBoxNetNum.ReadOnly = true;
            this.textBoxNetNum.Size = new System.Drawing.Size(78, 21);
            this.textBoxNetNum.TabIndex = 52;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(486, 56);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(59, 12);
            this.label17.TabIndex = 51;
            this.label17.Text = "网口个数:";
            // 
            // textBoxAlarmOutNum
            // 
            this.textBoxAlarmOutNum.Location = new System.Drawing.Point(250, 83);
            this.textBoxAlarmOutNum.Name = "textBoxAlarmOutNum";
            this.textBoxAlarmOutNum.ReadOnly = true;
            this.textBoxAlarmOutNum.Size = new System.Drawing.Size(79, 21);
            this.textBoxAlarmOutNum.TabIndex = 50;
            // 
            // textBoxAlarmInNum
            // 
            this.textBoxAlarmInNum.Location = new System.Drawing.Point(90, 83);
            this.textBoxAlarmInNum.Name = "textBoxAlarmInNum";
            this.textBoxAlarmInNum.ReadOnly = true;
            this.textBoxAlarmInNum.Size = new System.Drawing.Size(77, 21);
            this.textBoxAlarmInNum.TabIndex = 49;
            // 
            // textBoxZeroNum
            // 
            this.textBoxZeroNum.Location = new System.Drawing.Point(405, 51);
            this.textBoxZeroNum.Name = "textBoxZeroNum";
            this.textBoxZeroNum.ReadOnly = true;
            this.textBoxZeroNum.Size = new System.Drawing.Size(75, 21);
            this.textBoxZeroNum.TabIndex = 48;
            // 
            // textBoxIPNum
            // 
            this.textBoxIPNum.Location = new System.Drawing.Point(250, 51);
            this.textBoxIPNum.Name = "textBoxIPNum";
            this.textBoxIPNum.ReadOnly = true;
            this.textBoxIPNum.Size = new System.Drawing.Size(79, 21);
            this.textBoxIPNum.TabIndex = 12;
            // 
            // textBoxANum
            // 
            this.textBoxANum.Location = new System.Drawing.Point(90, 52);
            this.textBoxANum.Name = "textBoxANum";
            this.textBoxANum.ReadOnly = true;
            this.textBoxANum.Size = new System.Drawing.Size(77, 21);
            this.textBoxANum.TabIndex = 11;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(171, 87);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(83, 12);
            this.label16.TabIndex = 10;
            this.label16.Text = "模拟报警输出:";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(6, 86);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(83, 12);
            this.label15.TabIndex = 9;
            this.label15.Text = "模拟报警输入:";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(334, 56);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(71, 12);
            this.label14.TabIndex = 8;
            this.label14.Text = "零通道个数:";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(173, 56);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(71, 12);
            this.label13.TabIndex = 7;
            this.label13.Text = "IP通道个数:";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(7, 56);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(83, 12);
            this.label12.TabIndex = 6;
            this.label12.Text = "模拟通道个数:";
            // 
            // textBoxDevSerial
            // 
            this.textBoxDevSerial.Location = new System.Drawing.Point(404, 85);
            this.textBoxDevSerial.Name = "textBoxDevSerial";
            this.textBoxDevSerial.ReadOnly = true;
            this.textBoxDevSerial.Size = new System.Drawing.Size(225, 21);
            this.textBoxDevSerial.TabIndex = 5;
            // 
            // textBoxDevType
            // 
            this.textBoxDevType.Location = new System.Drawing.Point(271, 20);
            this.textBoxDevType.Name = "textBoxDevType";
            this.textBoxDevType.ReadOnly = true;
            this.textBoxDevType.Size = new System.Drawing.Size(129, 21);
            this.textBoxDevType.TabIndex = 4;
            // 
            // textBoxDevName
            // 
            this.textBoxDevName.Location = new System.Drawing.Point(65, 22);
            this.textBoxDevName.Name = "textBoxDevName";
            this.textBoxDevName.Size = new System.Drawing.Size(130, 21);
            this.textBoxDevName.TabIndex = 3;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(332, 88);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(71, 12);
            this.label11.TabIndex = 2;
            this.label11.Text = "设备序列号:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(211, 25);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(59, 12);
            this.label10.TabIndex = 1;
            this.label10.Text = "设备类型:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 26);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(59, 12);
            this.label9.TabIndex = 0;
            this.label9.Text = "设备名称:";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnNetCfgGet);
            this.groupBox2.Controls.Add(this.btnNetCfgSet);
            this.groupBox2.Controls.Add(this.textBoxSdkCfg);
            this.groupBox2.Controls.Add(this.label25);
            this.groupBox2.Controls.Add(this.textBoxHttpCfg);
            this.groupBox2.Controls.Add(this.label26);
            this.groupBox2.Controls.Add(this.textBoxHostPort);
            this.groupBox2.Controls.Add(this.label27);
            this.groupBox2.Controls.Add(this.textBoxHostIP);
            this.groupBox2.Controls.Add(this.label28);
            this.groupBox2.Controls.Add(this.textBoxPPPoEPsw);
            this.groupBox2.Controls.Add(this.label24);
            this.groupBox2.Controls.Add(this.textBoxPPPoeName);
            this.groupBox2.Controls.Add(this.label21);
            this.groupBox2.Controls.Add(this.checkBoxPPPoe);
            this.groupBox2.Controls.Add(this.checkBoxDhcp);
            this.groupBox2.Controls.Add(this.textBoxDns);
            this.groupBox2.Controls.Add(this.label23);
            this.groupBox2.Controls.Add(this.textBoxSubMask);
            this.groupBox2.Controls.Add(this.label22);
            this.groupBox2.Controls.Add(this.textBoxGateWay);
            this.groupBox2.Controls.Add(this.label20);
            this.groupBox2.Controls.Add(this.textBoxIPAddr);
            this.groupBox2.Controls.Add(this.label19);
            this.groupBox2.Location = new System.Drawing.Point(5, 248);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(641, 154);
            this.groupBox2.TabIndex = 48;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "网络参数 Network Parameter";
            // 
            // btnNetCfgGet
            // 
            this.btnNetCfgGet.Location = new System.Drawing.Point(463, 125);
            this.btnNetCfgGet.Name = "btnNetCfgGet";
            this.btnNetCfgGet.Size = new System.Drawing.Size(75, 23);
            this.btnNetCfgGet.TabIndex = 57;
            this.btnNetCfgGet.Text = "刷新";
            this.btnNetCfgGet.UseVisualStyleBackColor = true;
            this.btnNetCfgGet.Click += new System.EventHandler(this.btnNetCfgGet_Click);
            // 
            // btnNetCfgSet
            // 
            this.btnNetCfgSet.Location = new System.Drawing.Point(554, 125);
            this.btnNetCfgSet.Name = "btnNetCfgSet";
            this.btnNetCfgSet.Size = new System.Drawing.Size(75, 23);
            this.btnNetCfgSet.TabIndex = 56;
            this.btnNetCfgSet.Text = "设置";
            this.btnNetCfgSet.UseVisualStyleBackColor = true;
            this.btnNetCfgSet.Click += new System.EventHandler(this.btnNetCfgSet_Click);
            // 
            // textBoxSdkCfg
            // 
            this.textBoxSdkCfg.Location = new System.Drawing.Point(302, 99);
            this.textBoxSdkCfg.Name = "textBoxSdkCfg";
            this.textBoxSdkCfg.Size = new System.Drawing.Size(130, 21);
            this.textBoxSdkCfg.TabIndex = 77;
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(220, 103);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(71, 12);
            this.label25.TabIndex = 76;
            this.label25.Text = "设备端口号:";
            // 
            // textBoxHttpCfg
            // 
            this.textBoxHttpCfg.Location = new System.Drawing.Point(303, 72);
            this.textBoxHttpCfg.Name = "textBoxHttpCfg";
            this.textBoxHttpCfg.Size = new System.Drawing.Size(130, 21);
            this.textBoxHttpCfg.TabIndex = 75;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(219, 76);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(59, 12);
            this.label26.TabIndex = 74;
            this.label26.Text = "HTTP端口:";
            // 
            // textBoxHostPort
            // 
            this.textBoxHostPort.Location = new System.Drawing.Point(303, 45);
            this.textBoxHostPort.Name = "textBoxHostPort";
            this.textBoxHostPort.Size = new System.Drawing.Size(130, 21);
            this.textBoxHostPort.TabIndex = 73;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(218, 49);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(83, 12);
            this.label27.TabIndex = 72;
            this.label27.Text = "报警主机端口:";
            // 
            // textBoxHostIP
            // 
            this.textBoxHostIP.Location = new System.Drawing.Point(303, 18);
            this.textBoxHostIP.Name = "textBoxHostIP";
            this.textBoxHostIP.Size = new System.Drawing.Size(130, 21);
            this.textBoxHostIP.TabIndex = 71;
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(218, 22);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(83, 12);
            this.label28.TabIndex = 70;
            this.label28.Text = "报警主机地址:";
            // 
            // textBoxPPPoEPsw
            // 
            this.textBoxPPPoEPsw.Enabled = false;
            this.textBoxPPPoEPsw.Location = new System.Drawing.Point(526, 98);
            this.textBoxPPPoEPsw.Name = "textBoxPPPoEPsw";
            this.textBoxPPPoEPsw.Size = new System.Drawing.Size(103, 21);
            this.textBoxPPPoEPsw.TabIndex = 69;
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(462, 102);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(65, 12);
            this.label24.TabIndex = 68;
            this.label24.Text = "PPPoE密码:";
            // 
            // textBoxPPPoeName
            // 
            this.textBoxPPPoeName.Enabled = false;
            this.textBoxPPPoeName.Location = new System.Drawing.Point(526, 71);
            this.textBoxPPPoeName.Name = "textBoxPPPoeName";
            this.textBoxPPPoeName.Size = new System.Drawing.Size(103, 21);
            this.textBoxPPPoeName.TabIndex = 67;
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(462, 75);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(65, 12);
            this.label21.TabIndex = 66;
            this.label21.Text = "PPPoE账号:";
            // 
            // checkBoxPPPoe
            // 
            this.checkBoxPPPoe.AutoSize = true;
            this.checkBoxPPPoe.Location = new System.Drawing.Point(463, 49);
            this.checkBoxPPPoe.Name = "checkBoxPPPoe";
            this.checkBoxPPPoe.Size = new System.Drawing.Size(126, 16);
            this.checkBoxPPPoe.TabIndex = 65;
            this.checkBoxPPPoe.Text = "是否启用PPPoE拨号";
            this.checkBoxPPPoe.UseVisualStyleBackColor = true;
            this.checkBoxPPPoe.CheckedChanged += new System.EventHandler(this.checkBoxPPPoe_CheckedChanged);
            // 
            // checkBoxDhcp
            // 
            this.checkBoxDhcp.AutoSize = true;
            this.checkBoxDhcp.Location = new System.Drawing.Point(463, 24);
            this.checkBoxDhcp.Name = "checkBoxDhcp";
            this.checkBoxDhcp.Size = new System.Drawing.Size(156, 16);
            this.checkBoxDhcp.TabIndex = 64;
            this.checkBoxDhcp.Text = "是否启用DHCP自动获取IP";
            this.checkBoxDhcp.UseVisualStyleBackColor = true;
            this.checkBoxDhcp.CheckedChanged += new System.EventHandler(this.checkBoxDhcp_CheckedChanged);
            // 
            // textBoxDns
            // 
            this.textBoxDns.Location = new System.Drawing.Point(65, 101);
            this.textBoxDns.Name = "textBoxDns";
            this.textBoxDns.Size = new System.Drawing.Size(130, 21);
            this.textBoxDns.TabIndex = 63;
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(6, 105);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(53, 12);
            this.label23.TabIndex = 62;
            this.label23.Text = "首选DNS:";
            // 
            // textBoxSubMask
            // 
            this.textBoxSubMask.Location = new System.Drawing.Point(65, 74);
            this.textBoxSubMask.Name = "textBoxSubMask";
            this.textBoxSubMask.Size = new System.Drawing.Size(130, 21);
            this.textBoxSubMask.TabIndex = 61;
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(6, 78);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(59, 12);
            this.label22.TabIndex = 60;
            this.label22.Text = "子网掩码:";
            // 
            // textBoxGateWay
            // 
            this.textBoxGateWay.Location = new System.Drawing.Point(65, 47);
            this.textBoxGateWay.Name = "textBoxGateWay";
            this.textBoxGateWay.Size = new System.Drawing.Size(130, 21);
            this.textBoxGateWay.TabIndex = 59;
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(6, 51);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(59, 12);
            this.label20.TabIndex = 58;
            this.label20.Text = "默认网关:";
            // 
            // textBoxIPAddr
            // 
            this.textBoxIPAddr.Location = new System.Drawing.Point(65, 20);
            this.textBoxIPAddr.Name = "textBoxIPAddr";
            this.textBoxIPAddr.Size = new System.Drawing.Size(130, 21);
            this.textBoxIPAddr.TabIndex = 57;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(6, 24);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(59, 12);
            this.label19.TabIndex = 56;
            this.label19.Text = "IPv4地址:";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.textBoxSecond);
            this.groupBox4.Controls.Add(this.label32);
            this.groupBox4.Controls.Add(this.textBoxMinute);
            this.groupBox4.Controls.Add(this.label31);
            this.groupBox4.Controls.Add(this.textBoxHour);
            this.groupBox4.Controls.Add(this.textBoxDay);
            this.groupBox4.Controls.Add(this.label30);
            this.groupBox4.Controls.Add(this.textBoxMonth);
            this.groupBox4.Controls.Add(this.label29);
            this.groupBox4.Controls.Add(this.textBoxYear);
            this.groupBox4.Controls.Add(this.btnTimeSet);
            this.groupBox4.Controls.Add(this.btnTimeGet);
            this.groupBox4.Location = new System.Drawing.Point(5, 406);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(641, 58);
            this.groupBox4.TabIndex = 49;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "时间参数 Device Time";
            // 
            // textBoxSecond
            // 
            this.textBoxSecond.Location = new System.Drawing.Point(192, 22);
            this.textBoxSecond.Name = "textBoxSecond";
            this.textBoxSecond.Size = new System.Drawing.Size(20, 21);
            this.textBoxSecond.TabIndex = 13;
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(179, 26);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(11, 12);
            this.label32.TabIndex = 12;
            this.label32.Text = ":";
            // 
            // textBoxMinute
            // 
            this.textBoxMinute.Location = new System.Drawing.Point(157, 22);
            this.textBoxMinute.Name = "textBoxMinute";
            this.textBoxMinute.Size = new System.Drawing.Size(20, 21);
            this.textBoxMinute.TabIndex = 10;
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(147, 26);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(11, 12);
            this.label31.TabIndex = 9;
            this.label31.Text = ":";
            // 
            // textBoxHour
            // 
            this.textBoxHour.Location = new System.Drawing.Point(124, 22);
            this.textBoxHour.Name = "textBoxHour";
            this.textBoxHour.Size = new System.Drawing.Size(20, 21);
            this.textBoxHour.TabIndex = 8;
            // 
            // textBoxDay
            // 
            this.textBoxDay.Location = new System.Drawing.Point(92, 22);
            this.textBoxDay.Name = "textBoxDay";
            this.textBoxDay.Size = new System.Drawing.Size(20, 21);
            this.textBoxDay.TabIndex = 7;
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(82, 26);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(11, 12);
            this.label30.TabIndex = 6;
            this.label30.Text = "-";
            // 
            // textBoxMonth
            // 
            this.textBoxMonth.Location = new System.Drawing.Point(60, 22);
            this.textBoxMonth.Name = "textBoxMonth";
            this.textBoxMonth.Size = new System.Drawing.Size(20, 21);
            this.textBoxMonth.TabIndex = 5;
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(51, 26);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(11, 12);
            this.label29.TabIndex = 4;
            this.label29.Text = "-";
            // 
            // textBoxYear
            // 
            this.textBoxYear.Location = new System.Drawing.Point(8, 22);
            this.textBoxYear.Name = "textBoxYear";
            this.textBoxYear.Size = new System.Drawing.Size(42, 21);
            this.textBoxYear.TabIndex = 3;
            // 
            // btnTimeSet
            // 
            this.btnTimeSet.Location = new System.Drawing.Point(554, 18);
            this.btnTimeSet.Name = "btnTimeSet";
            this.btnTimeSet.Size = new System.Drawing.Size(75, 23);
            this.btnTimeSet.TabIndex = 2;
            this.btnTimeSet.Text = "设置";
            this.btnTimeSet.UseVisualStyleBackColor = true;
            this.btnTimeSet.Click += new System.EventHandler(this.btnTimeSet_Click);
            // 
            // btnTimeGet
            // 
            this.btnTimeGet.Location = new System.Drawing.Point(464, 18);
            this.btnTimeGet.Name = "btnTimeGet";
            this.btnTimeGet.Size = new System.Drawing.Size(75, 23);
            this.btnTimeGet.TabIndex = 1;
            this.btnTimeGet.Text = "刷新";
            this.btnTimeGet.UseVisualStyleBackColor = true;
            this.btnTimeGet.Click += new System.EventHandler(this.btnTimeGet_Click);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.btnChanCfg);
            this.groupBox5.Controls.Add(this.label33);
            this.groupBox5.Controls.Add(this.comboBoxChan);
            this.groupBox5.Location = new System.Drawing.Point(4, 466);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(642, 53);
            this.groupBox5.TabIndex = 50;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "通道参数 Video Parameters";
            // 
            // btnChanCfg
            // 
            this.btnChanCfg.Location = new System.Drawing.Point(219, 18);
            this.btnChanCfg.Name = "btnChanCfg";
            this.btnChanCfg.Size = new System.Drawing.Size(99, 23);
            this.btnChanCfg.TabIndex = 2;
            this.btnChanCfg.Text = "通道参数配置";
            this.btnChanCfg.UseVisualStyleBackColor = true;
            this.btnChanCfg.Click += new System.EventHandler(this.btnChanCfg_Click);
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(10, 25);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(47, 12);
            this.label33.TabIndex = 1;
            this.label33.Text = "通道号:";
            // 
            // comboBoxChan
            // 
            this.comboBoxChan.FormattingEnabled = true;
            this.comboBoxChan.Location = new System.Drawing.Point(66, 20);
            this.comboBoxChan.Name = "comboBoxChan";
            this.comboBoxChan.Size = new System.Drawing.Size(130, 20);
            this.comboBoxChan.TabIndex = 0;
            // 
            // ConfigCSharpDemo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(651, 558);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.textBoxPassword);
            this.Controls.Add(this.textBoxUserName);
            this.Controls.Add(this.textBoxPort);
            this.Controls.Add(this.textBoxIP);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.groupBox3);
            this.Name = "ConfigCSharpDemo";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Configuration Demo";
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxPassword;
        private System.Windows.Forms.TextBox textBoxUserName;
        private System.Windows.Forms.TextBox textBoxPort;
        private System.Windows.Forms.TextBox textBoxIP;
        private System.Windows.Forms.Button btnLogin;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxDevSerial;
        private System.Windows.Forms.TextBox textBoxDevType;
        private System.Windows.Forms.TextBox textBoxDevName;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox textBoxAlarmOutNum;
        private System.Windows.Forms.TextBox textBoxAlarmInNum;
        private System.Windows.Forms.TextBox textBoxZeroNum;
        private System.Windows.Forms.TextBox textBoxIPNum;
        private System.Windows.Forms.TextBox textBoxANum;
        private System.Windows.Forms.TextBox textBoxDevVersion;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox textBoxNetNum;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Button btnDevCfgSet;
        private System.Windows.Forms.Button btnDevCfgGet;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox textBoxDns;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.TextBox textBoxSubMask;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.TextBox textBoxGateWay;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox textBoxIPAddr;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.TextBox textBoxPPPoEPsw;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.TextBox textBoxPPPoeName;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.CheckBox checkBoxPPPoe;
        private System.Windows.Forms.CheckBox checkBoxDhcp;
        private System.Windows.Forms.Button btnNetCfgGet;
        private System.Windows.Forms.Button btnNetCfgSet;
        private System.Windows.Forms.TextBox textBoxSdkCfg;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.TextBox textBoxHttpCfg;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.TextBox textBoxHostPort;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.TextBox textBoxHostIP;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnTimeSet;
        private System.Windows.Forms.Button btnTimeGet;
        private System.Windows.Forms.TextBox textBoxDay;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.TextBox textBoxMonth;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.TextBox textBoxYear;
        private System.Windows.Forms.TextBox textBoxSecond;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.TextBox textBoxMinute;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.TextBox textBoxHour;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.ComboBox comboBoxChan;
        private System.Windows.Forms.Button btnChanCfg;
    }
}

