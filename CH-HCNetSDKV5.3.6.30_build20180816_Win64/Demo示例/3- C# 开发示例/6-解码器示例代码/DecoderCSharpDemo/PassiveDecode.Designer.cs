namespace DecoderCSharpDemo
{
    partial class PassiveDecode
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
            this.label1 = new System.Windows.Forms.Label();
            this.comboBoxTransProtol = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxPort = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBoxStreamMode = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxDevAddr = new System.Windows.Forms.TextBox();
            this.textBoxDevPort = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxUserName = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textBoxPassword = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.comboBoxStreamType = new System.Windows.Forms.ComboBox();
            this.comboBoxRealProtol = new System.Windows.Forms.ComboBox();
            this.textBoxChannel = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.groupBoxRealStream = new System.Windows.Forms.GroupBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textBoxFilePath = new System.Windows.Forms.TextBox();
            this.btnOpenFile = new System.Windows.Forms.Button();
            this.textBoxReadSize = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.groupBoxFileStream = new System.Windows.Forms.GroupBox();
            this.btnStartDecode = new System.Windows.Forms.Button();
            this.btnSendData = new System.Windows.Forms.Button();
            this.btnStopDecode = new System.Windows.Forms.Button();
            this.btnExit = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBoxRealStream.SuspendLayout();
            this.groupBoxFileStream.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "传输协议:";
            // 
            // comboBoxTransProtol
            // 
            this.comboBoxTransProtol.FormattingEnabled = true;
            this.comboBoxTransProtol.Items.AddRange(new object[] {
            "TCP",
            "UDP"});
            this.comboBoxTransProtol.Location = new System.Drawing.Point(67, 22);
            this.comboBoxTransProtol.Name = "comboBoxTransProtol";
            this.comboBoxTransProtol.Size = new System.Drawing.Size(87, 20);
            this.comboBoxTransProtol.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(169, 26);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "端口:";
            // 
            // textBoxPort
            // 
            this.textBoxPort.Location = new System.Drawing.Point(208, 22);
            this.textBoxPort.Name = "textBoxPort";
            this.textBoxPort.Size = new System.Drawing.Size(57, 21);
            this.textBoxPort.TabIndex = 3;
            this.textBoxPort.Text = "8000";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(284, 26);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "数据类型:";
            // 
            // comboBoxStreamMode
            // 
            this.comboBoxStreamMode.FormattingEnabled = true;
            this.comboBoxStreamMode.Items.AddRange(new object[] {
            "实时流",
            "文件流"});
            this.comboBoxStreamMode.Location = new System.Drawing.Point(349, 22);
            this.comboBoxStreamMode.Name = "comboBoxStreamMode";
            this.comboBoxStreamMode.Size = new System.Drawing.Size(95, 20);
            this.comboBoxStreamMode.TabIndex = 5;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBoxStreamMode);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.textBoxPort);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.comboBoxTransProtol);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(7, 8);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(455, 53);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "被动解码参数";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 29);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 12);
            this.label4.TabIndex = 7;
            this.label4.Text = "设备地址:";
            // 
            // textBoxDevAddr
            // 
            this.textBoxDevAddr.Location = new System.Drawing.Point(66, 25);
            this.textBoxDevAddr.Name = "textBoxDevAddr";
            this.textBoxDevAddr.Size = new System.Drawing.Size(137, 21);
            this.textBoxDevAddr.TabIndex = 8;
            this.textBoxDevAddr.Text = "10.16.2.251";
            // 
            // textBoxDevPort
            // 
            this.textBoxDevPort.Location = new System.Drawing.Point(66, 54);
            this.textBoxDevPort.Name = "textBoxDevPort";
            this.textBoxDevPort.Size = new System.Drawing.Size(137, 21);
            this.textBoxDevPort.TabIndex = 10;
            this.textBoxDevPort.Text = "8000";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 58);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "设备端口:";
            // 
            // textBoxUserName
            // 
            this.textBoxUserName.Location = new System.Drawing.Point(307, 25);
            this.textBoxUserName.Name = "textBoxUserName";
            this.textBoxUserName.Size = new System.Drawing.Size(137, 21);
            this.textBoxUserName.TabIndex = 12;
            this.textBoxUserName.Text = "admin";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(230, 29);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(71, 12);
            this.label6.TabIndex = 11;
            this.label6.Text = "设备用户名:";
            // 
            // textBoxPassword
            // 
            this.textBoxPassword.Location = new System.Drawing.Point(307, 54);
            this.textBoxPassword.Name = "textBoxPassword";
            this.textBoxPassword.PasswordChar = '*';
            this.textBoxPassword.Size = new System.Drawing.Size(137, 21);
            this.textBoxPassword.TabIndex = 14;
            this.textBoxPassword.Text = "12345";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(230, 58);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 12);
            this.label7.TabIndex = 13;
            this.label7.Text = "设备密码:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(8, 86);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(47, 12);
            this.label8.TabIndex = 15;
            this.label8.Text = "通道号:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(304, 86);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(59, 12);
            this.label9.TabIndex = 17;
            this.label9.Text = "传输协议:";
            // 
            // comboBoxStreamType
            // 
            this.comboBoxStreamType.FormattingEnabled = true;
            this.comboBoxStreamType.Items.AddRange(new object[] {
            "主码流",
            "子码流"});
            this.comboBoxStreamType.Location = new System.Drawing.Point(207, 82);
            this.comboBoxStreamType.Name = "comboBoxStreamType";
            this.comboBoxStreamType.Size = new System.Drawing.Size(80, 20);
            this.comboBoxStreamType.TabIndex = 18;
            // 
            // comboBoxRealProtol
            // 
            this.comboBoxRealProtol.FormattingEnabled = true;
            this.comboBoxRealProtol.Items.AddRange(new object[] {
            "TCP",
            "UDP"});
            this.comboBoxRealProtol.Location = new System.Drawing.Point(367, 82);
            this.comboBoxRealProtol.Name = "comboBoxRealProtol";
            this.comboBoxRealProtol.Size = new System.Drawing.Size(75, 20);
            this.comboBoxRealProtol.TabIndex = 19;
            // 
            // textBoxChannel
            // 
            this.textBoxChannel.Location = new System.Drawing.Point(66, 82);
            this.textBoxChannel.Name = "textBoxChannel";
            this.textBoxChannel.Size = new System.Drawing.Size(52, 21);
            this.textBoxChannel.TabIndex = 20;
            this.textBoxChannel.Text = "1";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(144, 86);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(59, 12);
            this.label10.TabIndex = 21;
            this.label10.Text = "码流类型:";
            // 
            // groupBoxRealStream
            // 
            this.groupBoxRealStream.Controls.Add(this.label10);
            this.groupBoxRealStream.Controls.Add(this.textBoxChannel);
            this.groupBoxRealStream.Controls.Add(this.comboBoxRealProtol);
            this.groupBoxRealStream.Controls.Add(this.comboBoxStreamType);
            this.groupBoxRealStream.Controls.Add(this.label9);
            this.groupBoxRealStream.Controls.Add(this.label8);
            this.groupBoxRealStream.Controls.Add(this.textBoxPassword);
            this.groupBoxRealStream.Controls.Add(this.label7);
            this.groupBoxRealStream.Controls.Add(this.textBoxUserName);
            this.groupBoxRealStream.Controls.Add(this.label6);
            this.groupBoxRealStream.Controls.Add(this.textBoxDevPort);
            this.groupBoxRealStream.Controls.Add(this.label5);
            this.groupBoxRealStream.Controls.Add(this.textBoxDevAddr);
            this.groupBoxRealStream.Controls.Add(this.label4);
            this.groupBoxRealStream.Location = new System.Drawing.Point(7, 71);
            this.groupBoxRealStream.Name = "groupBoxRealStream";
            this.groupBoxRealStream.Size = new System.Drawing.Size(455, 111);
            this.groupBoxRealStream.TabIndex = 22;
            this.groupBoxRealStream.TabStop = false;
            this.groupBoxRealStream.Text = "实时流(登录一台编码设备进行取流，然后调用被动解码接口发送给解码器)";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(10, 24);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(59, 12);
            this.label11.TabIndex = 23;
            this.label11.Text = "录像文件:";
            // 
            // textBoxFilePath
            // 
            this.textBoxFilePath.Location = new System.Drawing.Point(73, 20);
            this.textBoxFilePath.Name = "textBoxFilePath";
            this.textBoxFilePath.Size = new System.Drawing.Size(290, 21);
            this.textBoxFilePath.TabIndex = 24;
            // 
            // btnOpenFile
            // 
            this.btnOpenFile.Location = new System.Drawing.Point(377, 19);
            this.btnOpenFile.Name = "btnOpenFile";
            this.btnOpenFile.Size = new System.Drawing.Size(67, 23);
            this.btnOpenFile.TabIndex = 25;
            this.btnOpenFile.Text = "浏览";
            this.btnOpenFile.UseVisualStyleBackColor = true;
            this.btnOpenFile.Click += new System.EventHandler(this.btnOpenFile_Click);
            // 
            // textBoxReadSize
            // 
            this.textBoxReadSize.Location = new System.Drawing.Point(123, 48);
            this.textBoxReadSize.Name = "textBoxReadSize";
            this.textBoxReadSize.Size = new System.Drawing.Size(89, 21);
            this.textBoxReadSize.TabIndex = 27;
            this.textBoxReadSize.Text = "16";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(10, 52);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(107, 12);
            this.label12.TabIndex = 26;
            this.label12.Text = "每次读取数据大小:";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(216, 52);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(23, 12);
            this.label13.TabIndex = 28;
            this.label13.Text = "(K)";
            // 
            // groupBoxFileStream
            // 
            this.groupBoxFileStream.Controls.Add(this.label13);
            this.groupBoxFileStream.Controls.Add(this.textBoxReadSize);
            this.groupBoxFileStream.Controls.Add(this.label12);
            this.groupBoxFileStream.Controls.Add(this.btnOpenFile);
            this.groupBoxFileStream.Controls.Add(this.textBoxFilePath);
            this.groupBoxFileStream.Controls.Add(this.label11);
            this.groupBoxFileStream.Location = new System.Drawing.Point(7, 188);
            this.groupBoxFileStream.Name = "groupBoxFileStream";
            this.groupBoxFileStream.Size = new System.Drawing.Size(455, 79);
            this.groupBoxFileStream.TabIndex = 29;
            this.groupBoxFileStream.TabStop = false;
            this.groupBoxFileStream.Text = "文件流";
            // 
            // btnStartDecode
            // 
            this.btnStartDecode.Location = new System.Drawing.Point(19, 285);
            this.btnStartDecode.Name = "btnStartDecode";
            this.btnStartDecode.Size = new System.Drawing.Size(75, 23);
            this.btnStartDecode.TabIndex = 30;
            this.btnStartDecode.Text = "开始被动解码";
            this.btnStartDecode.UseVisualStyleBackColor = true;
            this.btnStartDecode.Click += new System.EventHandler(this.btnStartDecode_Click);
            // 
            // btnSendData
            // 
            this.btnSendData.Location = new System.Drawing.Point(140, 285);
            this.btnSendData.Name = "btnSendData";
            this.btnSendData.Size = new System.Drawing.Size(75, 23);
            this.btnSendData.TabIndex = 31;
            this.btnSendData.Text = "开始发送数据";
            this.btnSendData.UseVisualStyleBackColor = true;
            this.btnSendData.Click += new System.EventHandler(this.btnSendData_Click);
            // 
            // btnStopDecode
            // 
            this.btnStopDecode.Location = new System.Drawing.Point(256, 285);
            this.btnStopDecode.Name = "btnStopDecode";
            this.btnStopDecode.Size = new System.Drawing.Size(75, 23);
            this.btnStopDecode.TabIndex = 32;
            this.btnStopDecode.Text = "停止被动解码";
            this.btnStopDecode.UseVisualStyleBackColor = true;
            this.btnStopDecode.Click += new System.EventHandler(this.btnStopDecode_Click);
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(374, 285);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(75, 23);
            this.btnExit.TabIndex = 33;
            this.btnExit.Text = "退出";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // PassiveDecode
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(474, 324);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.btnStopDecode);
            this.Controls.Add(this.btnSendData);
            this.Controls.Add(this.btnStartDecode);
            this.Controls.Add(this.groupBoxFileStream);
            this.Controls.Add(this.groupBoxRealStream);
            this.Controls.Add(this.groupBox1);
            this.Name = "PassiveDecode";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "被动解码 Passive Decoding";
            this.Load += new System.EventHandler(this.PassiveDecode_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBoxRealStream.ResumeLayout(false);
            this.groupBoxRealStream.PerformLayout();
            this.groupBoxFileStream.ResumeLayout(false);
            this.groupBoxFileStream.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBoxTransProtol;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxPort;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBoxStreamMode;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxDevAddr;
        private System.Windows.Forms.TextBox textBoxDevPort;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxUserName;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBoxPassword;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ComboBox comboBoxStreamType;
        private System.Windows.Forms.ComboBox comboBoxRealProtol;
        private System.Windows.Forms.TextBox textBoxChannel;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.GroupBox groupBoxRealStream;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBoxFilePath;
        private System.Windows.Forms.Button btnOpenFile;
        private System.Windows.Forms.TextBox textBoxReadSize;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.GroupBox groupBoxFileStream;
        private System.Windows.Forms.Button btnStartDecode;
        private System.Windows.Forms.Button btnSendData;
        private System.Windows.Forms.Button btnStopDecode;
        private System.Windows.Forms.Button btnExit;
    }
}