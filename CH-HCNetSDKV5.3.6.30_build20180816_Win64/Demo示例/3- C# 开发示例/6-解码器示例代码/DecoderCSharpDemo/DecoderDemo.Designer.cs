namespace DecoderCSharpDemo
{
    partial class DecoderDemo
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
            this.textBoxPassword = new System.Windows.Forms.TextBox();
            this.textBoxUserName = new System.Windows.Forms.TextBox();
            this.textBoxPort = new System.Windows.Forms.TextBox();
            this.textBoxIP = new System.Windows.Forms.TextBox();
            this.btnLogin = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnExit = new System.Windows.Forms.Button();
            this.btnDispChanCfg = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.comboBoxDispChan = new System.Windows.Forms.ComboBox();
            this.btnPassiveDecCfg = new System.Windows.Forms.Button();
            this.btnDynDecCfg = new System.Windows.Forms.Button();
            this.label33 = new System.Windows.Forms.Label();
            this.comboBoxDecChan = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBoxPassword
            // 
            this.textBoxPassword.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.textBoxPassword.Location = new System.Drawing.Point(299, 74);
            this.textBoxPassword.Name = "textBoxPassword";
            this.textBoxPassword.PasswordChar = '*';
            this.textBoxPassword.Size = new System.Drawing.Size(112, 21);
            this.textBoxPassword.TabIndex = 23;
            this.textBoxPassword.Text = "12345";
            // 
            // textBoxUserName
            // 
            this.textBoxUserName.Location = new System.Drawing.Point(90, 74);
            this.textBoxUserName.Name = "textBoxUserName";
            this.textBoxUserName.Size = new System.Drawing.Size(114, 21);
            this.textBoxUserName.TabIndex = 22;
            this.textBoxUserName.Text = "admin";
            // 
            // textBoxPort
            // 
            this.textBoxPort.Location = new System.Drawing.Point(299, 29);
            this.textBoxPort.Name = "textBoxPort";
            this.textBoxPort.Size = new System.Drawing.Size(112, 21);
            this.textBoxPort.TabIndex = 21;
            this.textBoxPort.Text = "8000";
            // 
            // textBoxIP
            // 
            this.textBoxIP.Location = new System.Drawing.Point(90, 28);
            this.textBoxIP.Name = "textBoxIP";
            this.textBoxIP.Size = new System.Drawing.Size(114, 21);
            this.textBoxIP.TabIndex = 20;
            this.textBoxIP.Text = "10.16.0.222";
            // 
            // btnLogin
            // 
            this.btnLogin.Location = new System.Drawing.Point(415, 19);
            this.btnLogin.Name = "btnLogin";
            this.btnLogin.Size = new System.Drawing.Size(64, 63);
            this.btnLogin.TabIndex = 19;
            this.btnLogin.Text = "登录设备 Login";
            this.btnLogin.Click += new System.EventHandler(this.btnLogin_Click);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(22, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 10);
            this.label1.TabIndex = 16;
            this.label1.Text = "Device IP";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(22, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 15);
            this.label2.TabIndex = 15;
            this.label2.Text = "User Name";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(223, 67);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 16);
            this.label3.TabIndex = 18;
            this.label3.Text = "Password";
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(215, 13);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(79, 17);
            this.label4.TabIndex = 17;
            this.label4.Text = "Device Port";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(22, 36);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 24;
            this.label5.Text = "设备IP";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(215, 30);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 25;
            this.label6.Text = "设备端口";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(22, 80);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 12);
            this.label7.TabIndex = 26;
            this.label7.Text = "用户名";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(225, 83);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(29, 12);
            this.label8.TabIndex = 27;
            this.label8.Text = "密码";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btnLogin);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Location = new System.Drawing.Point(8, 9);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(493, 97);
            this.groupBox3.TabIndex = 41;
            this.groupBox3.TabStop = false;
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(416, 233);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(75, 30);
            this.btnExit.TabIndex = 46;
            this.btnExit.Text = "退出 Exit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // btnDispChanCfg
            // 
            this.btnDispChanCfg.Location = new System.Drawing.Point(224, 125);
            this.btnDispChanCfg.Name = "btnDispChanCfg";
            this.btnDispChanCfg.Size = new System.Drawing.Size(90, 32);
            this.btnDispChanCfg.TabIndex = 51;
            this.btnDispChanCfg.Text = "显示通道配置";
            this.btnDispChanCfg.UseVisualStyleBackColor = true;
            this.btnDispChanCfg.Click += new System.EventHandler(this.btnDispChanCfg_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(15, 135);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(71, 12);
            this.label9.TabIndex = 6;
            this.label9.Text = "显示通道号:";
            // 
            // comboBoxDispChan
            // 
            this.comboBoxDispChan.FormattingEnabled = true;
            this.comboBoxDispChan.Location = new System.Drawing.Point(90, 131);
            this.comboBoxDispChan.Name = "comboBoxDispChan";
            this.comboBoxDispChan.Size = new System.Drawing.Size(114, 20);
            this.comboBoxDispChan.TabIndex = 5;
            // 
            // btnPassiveDecCfg
            // 
            this.btnPassiveDecCfg.Location = new System.Drawing.Point(311, 178);
            this.btnPassiveDecCfg.Name = "btnPassiveDecCfg";
            this.btnPassiveDecCfg.Size = new System.Drawing.Size(75, 32);
            this.btnPassiveDecCfg.TabIndex = 8;
            this.btnPassiveDecCfg.Text = "被动解码";
            this.btnPassiveDecCfg.UseVisualStyleBackColor = true;
            this.btnPassiveDecCfg.Click += new System.EventHandler(this.btnPassiveDecCfg_Click);
            // 
            // btnDynDecCfg
            // 
            this.btnDynDecCfg.Location = new System.Drawing.Point(224, 178);
            this.btnDynDecCfg.Name = "btnDynDecCfg";
            this.btnDynDecCfg.Size = new System.Drawing.Size(72, 32);
            this.btnDynDecCfg.TabIndex = 7;
            this.btnDynDecCfg.Text = "动态解码";
            this.btnDynDecCfg.UseVisualStyleBackColor = true;
            this.btnDynDecCfg.Click += new System.EventHandler(this.btnDynDecCfg_Click);
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(15, 188);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(71, 12);
            this.label33.TabIndex = 6;
            this.label33.Text = "解码通道号:";
            // 
            // comboBoxDecChan
            // 
            this.comboBoxDecChan.FormattingEnabled = true;
            this.comboBoxDecChan.Location = new System.Drawing.Point(90, 184);
            this.comboBoxDecChan.Name = "comboBoxDecChan";
            this.comboBoxDecChan.Size = new System.Drawing.Size(114, 20);
            this.comboBoxDecChan.TabIndex = 5;
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(10, 220);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(487, 10);
            this.groupBox1.TabIndex = 52;
            this.groupBox1.TabStop = false;
            // 
            // DecoderDemo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(513, 270);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.btnPassiveDecCfg);
            this.Controls.Add(this.comboBoxDispChan);
            this.Controls.Add(this.btnDynDecCfg);
            this.Controls.Add(this.btnDispChanCfg);
            this.Controls.Add(this.label33);
            this.Controls.Add(this.comboBoxDecChan);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.textBoxPassword);
            this.Controls.Add(this.textBoxUserName);
            this.Controls.Add(this.textBoxPort);
            this.Controls.Add(this.textBoxIP);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.groupBox3);
            this.Name = "DecoderDemo";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Decoder Demo";
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion     

        private System.Windows.Forms.TextBox textBoxPassword;
        private System.Windows.Forms.TextBox textBoxUserName;
        private System.Windows.Forms.TextBox textBoxPort;
        private System.Windows.Forms.TextBox textBoxIP;
        private System.Windows.Forms.Button btnLogin;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.Button btnDispChanCfg;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ComboBox comboBoxDispChan;
        private System.Windows.Forms.Button btnPassiveDecCfg;
        private System.Windows.Forms.Button btnDynDecCfg;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.ComboBox comboBoxDecChan;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}

