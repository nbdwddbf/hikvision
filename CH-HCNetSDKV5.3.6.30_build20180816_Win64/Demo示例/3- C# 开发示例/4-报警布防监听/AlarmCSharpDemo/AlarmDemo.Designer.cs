namespace AlarmCSharpDemo
{
    partial class AlarmDemo
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
            this.listViewAlarmInfo = new System.Windows.Forms.ListView();
            this.ColumnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ColumnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btn_SetAlarm = new System.Windows.Forms.Button();
            this.listViewDevice = new System.Windows.Forms.ListView();
            this.ColumnNumber = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ColumnIP = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ColumnStatus = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.btnCloseAlarm = new System.Windows.Forms.Button();
            this.btnExit = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.btnStartListen = new System.Windows.Forms.Button();
            this.btnStopListen = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.textBoxListenIP = new System.Windows.Forms.TextBox();
            this.textBoxListenPort = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox3.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(221, 77);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(29, 12);
            this.label8.TabIndex = 27;
            this.label8.Text = "密码";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(21, 76);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 12);
            this.label7.TabIndex = 26;
            this.label7.Text = "用户名";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(219, 31);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 25;
            this.label6.Text = "设备端口";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(21, 30);
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
            this.textBoxPassword.Text = "hik12345";
            // 
            // textBoxUserName
            // 
            this.textBoxUserName.Location = new System.Drawing.Point(87, 65);
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
            this.textBoxIP.Location = new System.Drawing.Point(87, 19);
            this.textBoxIP.Name = "textBoxIP";
            this.textBoxIP.Size = new System.Drawing.Size(114, 21);
            this.textBoxIP.TabIndex = 20;
            this.textBoxIP.Text = "10.18.37.119";
            // 
            // btnLogin
            // 
            this.btnLogin.Location = new System.Drawing.Point(424, 19);
            this.btnLogin.Name = "btnLogin";
            this.btnLogin.Size = new System.Drawing.Size(64, 63);
            this.btnLogin.TabIndex = 19;
            this.btnLogin.Text = "添加设备 Add";
            this.btnLogin.Click += new System.EventHandler(this.btnLogin_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(21, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 18);
            this.label1.TabIndex = 16;
            this.label1.Text = "Device IP";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(21, 56);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 16);
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
            // listViewAlarmInfo
            // 
            this.listViewAlarmInfo.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.ColumnHeader1,
            this.ColumnHeader2,
            this.columnHeader3});
            this.listViewAlarmInfo.FullRowSelect = true;
            this.listViewAlarmInfo.GridLines = true;
            this.listViewAlarmInfo.Location = new System.Drawing.Point(223, 102);
            this.listViewAlarmInfo.MultiSelect = false;
            this.listViewAlarmInfo.Name = "listViewAlarmInfo";
            this.listViewAlarmInfo.Size = new System.Drawing.Size(413, 389);
            this.listViewAlarmInfo.TabIndex = 32;
            this.listViewAlarmInfo.TabStop = false;
            this.listViewAlarmInfo.UseCompatibleStateImageBehavior = false;
            this.listViewAlarmInfo.View = System.Windows.Forms.View.Details;
            // 
            // ColumnHeader1
            // 
            this.ColumnHeader1.Text = "报警时间";
            this.ColumnHeader1.Width = 140;
            // 
            // ColumnHeader2
            // 
            this.ColumnHeader2.Text = "报警设备";
            this.ColumnHeader2.Width = 114;
            // 
            // columnHeader3
            // 
            this.columnHeader3.Text = "报警信息";
            this.columnHeader3.Width = 246;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btnLogin);
            this.groupBox3.Location = new System.Drawing.Point(4, -1);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(524, 97);
            this.groupBox3.TabIndex = 41;
            this.groupBox3.TabStop = false;
            // 
            // btn_SetAlarm
            // 
            this.btn_SetAlarm.Location = new System.Drawing.Point(4, 468);
            this.btn_SetAlarm.Name = "btn_SetAlarm";
            this.btn_SetAlarm.Size = new System.Drawing.Size(91, 23);
            this.btn_SetAlarm.TabIndex = 43;
            this.btn_SetAlarm.Text = "全部布防";
            this.btn_SetAlarm.UseVisualStyleBackColor = true;
            this.btn_SetAlarm.Click += new System.EventHandler(this.btn_SetAlarm_Click);
            // 
            // listViewDevice
            // 
            this.listViewDevice.Activation = System.Windows.Forms.ItemActivation.OneClick;
            this.listViewDevice.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.ColumnNumber,
            this.ColumnIP,
            this.ColumnStatus});
            this.listViewDevice.FullRowSelect = true;
            this.listViewDevice.GridLines = true;
            this.listViewDevice.HideSelection = false;
            this.listViewDevice.Location = new System.Drawing.Point(4, 102);
            this.listViewDevice.Name = "listViewDevice";
            this.listViewDevice.Size = new System.Drawing.Size(213, 360);
            this.listViewDevice.TabIndex = 44;
            this.listViewDevice.TabStop = false;
            this.listViewDevice.UseCompatibleStateImageBehavior = false;
            this.listViewDevice.View = System.Windows.Forms.View.Details;
            this.listViewDevice.MouseClick += new System.Windows.Forms.MouseEventHandler(this.listViewDevice_MouseClick);
            // 
            // ColumnNumber
            // 
            this.ColumnNumber.Text = "UserID";
            this.ColumnNumber.Width = 50;
            // 
            // ColumnIP
            // 
            this.ColumnIP.Text = "设备IP地址";
            this.ColumnIP.Width = 90;
            // 
            // ColumnStatus
            // 
            this.ColumnStatus.Text = "状态";
            this.ColumnStatus.Width = 160;
            // 
            // btnCloseAlarm
            // 
            this.btnCloseAlarm.Location = new System.Drawing.Point(111, 468);
            this.btnCloseAlarm.Name = "btnCloseAlarm";
            this.btnCloseAlarm.Size = new System.Drawing.Size(90, 23);
            this.btnCloseAlarm.TabIndex = 45;
            this.btnCloseAlarm.Text = "全部撤防";
            this.btnCloseAlarm.UseVisualStyleBackColor = true;
            this.btnCloseAlarm.Click += new System.EventHandler(this.btnCloseAlarm_Click);
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
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(12, 428);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(161, 12);
            this.label9.TabIndex = 47;
            this.label9.Text = "注：鼠标右键删除选中的设备";
            // 
            // btnStartListen
            // 
            this.btnStartListen.Location = new System.Drawing.Point(391, 16);
            this.btnStartListen.Name = "btnStartListen";
            this.btnStartListen.Size = new System.Drawing.Size(88, 23);
            this.btnStartListen.TabIndex = 48;
            this.btnStartListen.Text = "启动监听";
            this.btnStartListen.UseVisualStyleBackColor = true;
            this.btnStartListen.Click += new System.EventHandler(this.btnStartListen_Click);
            // 
            // btnStopListen
            // 
            this.btnStopListen.Enabled = false;
            this.btnStopListen.Location = new System.Drawing.Point(501, 16);
            this.btnStopListen.Name = "btnStopListen";
            this.btnStopListen.Size = new System.Drawing.Size(90, 23);
            this.btnStopListen.TabIndex = 49;
            this.btnStopListen.Text = " 停止监听";
            this.btnStopListen.UseVisualStyleBackColor = true;
            this.btnStopListen.Click += new System.EventHandler(this.btnStopListen_Click);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(7, 21);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(71, 12);
            this.label10.TabIndex = 50;
            this.label10.Text = "监听IP地址:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(197, 21);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(59, 12);
            this.label11.TabIndex = 51;
            this.label11.Text = "监听端口:";
            // 
            // textBoxListenIP
            // 
            this.textBoxListenIP.Location = new System.Drawing.Point(81, 18);
            this.textBoxListenIP.Name = "textBoxListenIP";
            this.textBoxListenIP.Size = new System.Drawing.Size(99, 21);
            this.textBoxListenIP.TabIndex = 52;
            // 
            // textBoxListenPort
            // 
            this.textBoxListenPort.Location = new System.Drawing.Point(255, 18);
            this.textBoxListenPort.Name = "textBoxListenPort";
            this.textBoxListenPort.Size = new System.Drawing.Size(100, 21);
            this.textBoxListenPort.TabIndex = 53;
            this.textBoxListenPort.Text = "7200";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnStopListen);
            this.groupBox1.Controls.Add(this.textBoxListenPort);
            this.groupBox1.Controls.Add(this.btnStartListen);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.textBoxListenIP);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Location = new System.Drawing.Point(4, 497);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(632, 49);
            this.groupBox1.TabIndex = 54;
            this.groupBox1.TabStop = false;
            // 
            // AlarmDemo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(652, 558);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.btnCloseAlarm);
            this.Controls.Add(this.listViewDevice);
            this.Controls.Add(this.btn_SetAlarm);
            this.Controls.Add(this.listViewAlarmInfo);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBoxPassword);
            this.Controls.Add(this.textBoxUserName);
            this.Controls.Add(this.textBoxPort);
            this.Controls.Add(this.textBoxIP);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox1);
            this.Name = "AlarmDemo";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Alarm Test Demo";
            this.groupBox3.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
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
        private System.Windows.Forms.ListView listViewAlarmInfo;
        private System.Windows.Forms.ColumnHeader ColumnHeader1;
        private System.Windows.Forms.ColumnHeader ColumnHeader2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btn_SetAlarm;
        private System.Windows.Forms.ListView listViewDevice;
        private System.Windows.Forms.ColumnHeader ColumnNumber;
        private System.Windows.Forms.ColumnHeader ColumnIP;
        private System.Windows.Forms.ColumnHeader ColumnStatus;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.Button btnCloseAlarm;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button btnStartListen;
        private System.Windows.Forms.Button btnStopListen;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBoxListenIP;
        private System.Windows.Forms.TextBox textBoxListenPort;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}

