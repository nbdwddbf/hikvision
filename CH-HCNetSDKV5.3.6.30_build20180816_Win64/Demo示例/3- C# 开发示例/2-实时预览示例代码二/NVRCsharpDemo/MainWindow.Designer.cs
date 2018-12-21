namespace NVRCsharpDemo
{
    partial class MainWindow
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
            if (m_lRealHandle >= 0)
            {
                CHCNetSDK.NET_DVR_StopRealPlay(m_lRealHandle);
            }
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
            this.label10 = new System.Windows.Forms.Label();
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
            this.RealPlayWnd = new System.Windows.Forms.PictureBox();
            this.listViewIPChannel = new System.Windows.Forms.ListView();
            this.ColumnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ColumnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.btnPreview = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.btnBMP = new System.Windows.Forms.Button();
            this.label14 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label12 = new System.Windows.Forms.Label();
            this.comboBoxView = new System.Windows.Forms.ComboBox();
            this.label15 = new System.Windows.Forms.Label();
            this.btnRecord = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.btnJPEG = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.checkBoxHiDDNS = new System.Windows.Forms.CheckBox();
            this.btn_Exit = new System.Windows.Forms.Button();
            this.TextBoxInfo = new System.Windows.Forms.TextBox();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.RealPlayWnd)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(517, 37);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(29, 12);
            this.label10.TabIndex = 28;
            this.label10.Text = "登录";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(285, 97);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(29, 12);
            this.label8.TabIndex = 27;
            this.label8.Text = "密码";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(9, 97);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 12);
            this.label7.TabIndex = 26;
            this.label7.Text = "用户名";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(283, 57);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 25;
            this.label6.Text = "设备端口";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 57);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 12);
            this.label5.TabIndex = 24;
            this.label5.Text = "设备IP或域名";
            // 
            // textBoxPassword
            // 
            this.textBoxPassword.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.textBoxPassword.Location = new System.Drawing.Point(371, 81);
            this.textBoxPassword.Name = "textBoxPassword";
            this.textBoxPassword.PasswordChar = '*';
            this.textBoxPassword.Size = new System.Drawing.Size(112, 21);
            this.textBoxPassword.TabIndex = 23;
            this.textBoxPassword.Text = "12345";
            // 
            // textBoxUserName
            // 
            this.textBoxUserName.Location = new System.Drawing.Point(121, 81);
            this.textBoxUserName.Name = "textBoxUserName";
            this.textBoxUserName.Size = new System.Drawing.Size(141, 21);
            this.textBoxUserName.TabIndex = 22;
            this.textBoxUserName.Text = "admin";
            // 
            // textBoxPort
            // 
            this.textBoxPort.Location = new System.Drawing.Point(371, 43);
            this.textBoxPort.Name = "textBoxPort";
            this.textBoxPort.Size = new System.Drawing.Size(112, 21);
            this.textBoxPort.TabIndex = 21;
            this.textBoxPort.Text = "8000";
            // 
            // textBoxIP
            // 
            this.textBoxIP.Location = new System.Drawing.Point(121, 43);
            this.textBoxIP.Name = "textBoxIP";
            this.textBoxIP.Size = new System.Drawing.Size(141, 21);
            this.textBoxIP.TabIndex = 20;
            this.textBoxIP.Text = "10.16.3.245";
            // 
            // btnLogin
            // 
            this.btnLogin.Location = new System.Drawing.Point(498, 52);
            this.btnLogin.Name = "btnLogin";
            this.btnLogin.Size = new System.Drawing.Size(78, 50);
            this.btnLogin.TabIndex = 19;
            this.btnLogin.Text = "Login";
            this.btnLogin.Click += new System.EventHandler(this.btnLogin_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(8, 39);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(103, 15);
            this.label1.TabIndex = 16;
            this.label1.Text = "Device IP/Domain";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(8, 81);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 16);
            this.label2.TabIndex = 15;
            this.label2.Text = "User Name";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(283, 81);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 16);
            this.label3.TabIndex = 18;
            this.label3.Text = "Password";
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(283, 39);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(79, 17);
            this.label4.TabIndex = 17;
            this.label4.Text = "Device Port";
            // 
            // RealPlayWnd
            // 
            this.RealPlayWnd.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.RealPlayWnd.Location = new System.Drawing.Point(184, 124);
            this.RealPlayWnd.Name = "RealPlayWnd";
            this.RealPlayWnd.Size = new System.Drawing.Size(428, 341);
            this.RealPlayWnd.TabIndex = 30;
            this.RealPlayWnd.TabStop = false;
            // 
            // listViewIPChannel
            // 
            this.listViewIPChannel.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.ColumnHeader1,
            this.ColumnHeader2});
            this.listViewIPChannel.FullRowSelect = true;
            this.listViewIPChannel.GridLines = true;
            this.listViewIPChannel.Location = new System.Drawing.Point(4, 124);
            this.listViewIPChannel.MultiSelect = false;
            this.listViewIPChannel.Name = "listViewIPChannel";
            this.listViewIPChannel.Size = new System.Drawing.Size(174, 311);
            this.listViewIPChannel.TabIndex = 32;
            this.listViewIPChannel.UseCompatibleStateImageBehavior = false;
            this.listViewIPChannel.View = System.Windows.Forms.View.Details;
            this.listViewIPChannel.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.listViewIPChannel_ItemSelectionChanged);
            this.listViewIPChannel.MouseClick += new System.Windows.Forms.MouseEventHandler(this.listViewIPChannel_MouseClick);
            // 
            // ColumnHeader1
            // 
            this.ColumnHeader1.Text = "通道 Channel";
            this.ColumnHeader1.Width = 90;
            // 
            // ColumnHeader2
            // 
            this.ColumnHeader2.Text = "状态 Status";
            this.ColumnHeader2.Width = 90;
            // 
            // btnPreview
            // 
            this.btnPreview.Location = new System.Drawing.Point(153, 15);
            this.btnPreview.Name = "btnPreview";
            this.btnPreview.Size = new System.Drawing.Size(75, 27);
            this.btnPreview.TabIndex = 33;
            this.btnPreview.Text = "Live View";
            this.btnPreview.UseVisualStyleBackColor = true;
            this.btnPreview.Click += new System.EventHandler(this.btnPreview_Click);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(176, 47);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(29, 12);
            this.label11.TabIndex = 34;
            this.label11.Text = "预览";
            // 
            // btnBMP
            // 
            this.btnBMP.Location = new System.Drawing.Point(239, 16);
            this.btnBMP.Name = "btnBMP";
            this.btnBMP.Size = new System.Drawing.Size(79, 27);
            this.btnBMP.TabIndex = 36;
            this.btnBMP.Text = "Capture BMP";
            this.btnBMP.UseVisualStyleBackColor = true;
            this.btnBMP.Click += new System.EventHandler(this.btnBMP_Click);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(255, 47);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(47, 12);
            this.label14.TabIndex = 38;
            this.label14.Text = "BMP抓图";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label12);
            this.groupBox2.Controls.Add(this.comboBoxView);
            this.groupBox2.Controls.Add(this.label15);
            this.groupBox2.Controls.Add(this.btnRecord);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.label14);
            this.groupBox2.Controls.Add(this.btnJPEG);
            this.groupBox2.Controls.Add(this.label11);
            this.groupBox2.Controls.Add(this.btnPreview);
            this.groupBox2.Controls.Add(this.btnBMP);
            this.groupBox2.Location = new System.Drawing.Point(4, 462);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(528, 68);
            this.groupBox2.TabIndex = 40;
            this.groupBox2.TabStop = false;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(12, 44);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(0, 12);
            this.label12.TabIndex = 47;
            // 
            // comboBoxView
            // 
            this.comboBoxView.FormattingEnabled = true;
            this.comboBoxView.Items.AddRange(new object[] {
            "Direct:直接预览 ",
            "Callback:回调解码 "});
            this.comboBoxView.Location = new System.Drawing.Point(8, 18);
            this.comboBoxView.Name = "comboBoxView";
            this.comboBoxView.Size = new System.Drawing.Size(139, 20);
            this.comboBoxView.TabIndex = 46;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(439, 45);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(65, 12);
            this.label15.TabIndex = 45;
            this.label15.Text = "客户端录像";
            // 
            // btnRecord
            // 
            this.btnRecord.Location = new System.Drawing.Point(431, 17);
            this.btnRecord.Name = "btnRecord";
            this.btnRecord.Size = new System.Drawing.Size(89, 25);
            this.btnRecord.TabIndex = 44;
            this.btnRecord.Text = "Record";
            this.btnRecord.UseVisualStyleBackColor = true;
            this.btnRecord.Click += new System.EventHandler(this.btnRecord_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(346, 46);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(53, 12);
            this.label9.TabIndex = 43;
            this.label9.Text = "JPEG抓图";
            // 
            // btnJPEG
            // 
            this.btnJPEG.Location = new System.Drawing.Point(326, 17);
            this.btnJPEG.Name = "btnJPEG";
            this.btnJPEG.Size = new System.Drawing.Size(97, 26);
            this.btnJPEG.TabIndex = 42;
            this.btnJPEG.Text = "Capture JPEG";
            this.btnJPEG.UseVisualStyleBackColor = true;
            this.btnJPEG.Click += new System.EventHandler(this.btnJPEG_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.checkBoxHiDDNS);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.textBoxPassword);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.textBoxPort);
            this.groupBox3.Controls.Add(this.textBoxIP);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.textBoxUserName);
            this.groupBox3.Controls.Add(this.btnLogin);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Location = new System.Drawing.Point(4, -2);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(608, 117);
            this.groupBox3.TabIndex = 41;
            this.groupBox3.TabStop = false;
            // 
            // checkBoxHiDDNS
            // 
            this.checkBoxHiDDNS.AutoSize = true;
            this.checkBoxHiDDNS.Location = new System.Drawing.Point(9, 16);
            this.checkBoxHiDDNS.Name = "checkBoxHiDDNS";
            this.checkBoxHiDDNS.Size = new System.Drawing.Size(108, 16);
            this.checkBoxHiDDNS.TabIndex = 29;
            this.checkBoxHiDDNS.Text = "HiDDNS域名登录";
            this.checkBoxHiDDNS.UseVisualStyleBackColor = true;
            this.checkBoxHiDDNS.CheckedChanged += new System.EventHandler(this.checkBoxHiDDNS_CheckedChanged);
            // 
            // btn_Exit
            // 
            this.btn_Exit.Location = new System.Drawing.Point(538, 470);
            this.btn_Exit.Name = "btn_Exit";
            this.btn_Exit.Size = new System.Drawing.Size(69, 53);
            this.btn_Exit.TabIndex = 42;
            this.btn_Exit.Text = "退出 Exit";
            this.btn_Exit.UseVisualStyleBackColor = true;
            this.btn_Exit.Click += new System.EventHandler(this.btn_Exit_Click);
            // 
            // TextBoxInfo
            // 
            this.TextBoxInfo.Location = new System.Drawing.Point(4, 536);
            this.TextBoxInfo.Multiline = true;
            this.TextBoxInfo.Name = "TextBoxInfo";
            this.TextBoxInfo.Size = new System.Drawing.Size(608, 35);
            this.TextBoxInfo.TabIndex = 43;
            // 
            // btnRefresh
            // 
            this.btnRefresh.Location = new System.Drawing.Point(4, 439);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(70, 23);
            this.btnRefresh.TabIndex = 44;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(80, 444);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(77, 12);
            this.label13.TabIndex = 45;
            this.label13.Text = "刷新通道列表";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(619, 577);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.btnRefresh);
            this.Controls.Add(this.TextBoxInfo);
            this.Controls.Add(this.btn_Exit);
            this.Controls.Add(this.listViewIPChannel);
            this.Controls.Add(this.RealPlayWnd);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox3);
            this.Name = "MainWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Main Window";
            ((System.ComponentModel.ISupportInitialize)(this.RealPlayWnd)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label10;
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
        private System.Windows.Forms.PictureBox RealPlayWnd;
        private System.Windows.Forms.ListView listViewIPChannel;
        private System.Windows.Forms.ColumnHeader ColumnHeader1;
        private System.Windows.Forms.ColumnHeader ColumnHeader2;
        private System.Windows.Forms.Button btnPreview;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Button btnBMP;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button btnJPEG;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Button btnRecord;
        private System.Windows.Forms.Button btn_Exit;
        private System.Windows.Forms.CheckBox checkBoxHiDDNS;
        private System.Windows.Forms.TextBox TextBoxInfo;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.ComboBox comboBoxView;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.Label label13;

    }
}

