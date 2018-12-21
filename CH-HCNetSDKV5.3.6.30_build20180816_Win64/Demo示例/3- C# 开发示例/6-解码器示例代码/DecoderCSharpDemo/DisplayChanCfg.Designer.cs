namespace DecoderCSharpDemo
{
    partial class DisplayChanCfg
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
            this.comboBoxWinMode = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBoxSubWin = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBoxDecNo = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnSubWin = new System.Windows.Forms.Button();
            this.checkBoxAudio = new System.Windows.Forms.CheckBox();
            this.comboBoxAudio = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBoxFormat = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.comboBoxResolution = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.comboBoxScale = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.comboBoxEnlarge = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnGetDispCfg = new System.Windows.Forms.Button();
            this.btnSetDispCfg = new System.Windows.Forms.Button();
            this.btnEnlarge = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnExit = new System.Windows.Forms.Button();
            this.btnResume = new System.Windows.Forms.Button();
            this.checkBoxEnlarge = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBoxWinMode
            // 
            this.comboBoxWinMode.FormattingEnabled = true;
            this.comboBoxWinMode.Location = new System.Drawing.Point(109, 10);
            this.comboBoxWinMode.Name = "comboBoxWinMode";
            this.comboBoxWinMode.Size = new System.Drawing.Size(121, 20);
            this.comboBoxWinMode.TabIndex = 0;
            this.comboBoxWinMode.SelectedIndexChanged += new System.EventHandler(this.comboBoxWinMode_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(26, 14);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "画面分割模式";
            // 
            // comboBoxSubWin
            // 
            this.comboBoxSubWin.FormattingEnabled = true;
            this.comboBoxSubWin.Location = new System.Drawing.Point(108, 50);
            this.comboBoxSubWin.Name = "comboBoxSubWin";
            this.comboBoxSubWin.Size = new System.Drawing.Size(121, 20);
            this.comboBoxSubWin.TabIndex = 2;
            this.comboBoxSubWin.SelectedIndexChanged += new System.EventHandler(this.comboBoxSubWin_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(29, 57);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "子窗口";
            // 
            // comboBoxDecNo
            // 
            this.comboBoxDecNo.FormattingEnabled = true;
            this.comboBoxDecNo.Location = new System.Drawing.Point(108, 79);
            this.comboBoxDecNo.Name = "comboBoxDecNo";
            this.comboBoxDecNo.Size = new System.Drawing.Size(121, 20);
            this.comboBoxDecNo.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(29, 83);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(77, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "关联解码通道";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnSubWin);
            this.groupBox1.Location = new System.Drawing.Point(21, 36);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(287, 73);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            // 
            // btnSubWin
            // 
            this.btnSubWin.Location = new System.Drawing.Point(227, 20);
            this.btnSubWin.Name = "btnSubWin";
            this.btnSubWin.Size = new System.Drawing.Size(53, 38);
            this.btnSubWin.TabIndex = 0;
            this.btnSubWin.Text = "确定";
            this.btnSubWin.UseVisualStyleBackColor = true;
            this.btnSubWin.Click += new System.EventHandler(this.btnSubWin_Click);
            // 
            // checkBoxAudio
            // 
            this.checkBoxAudio.AutoSize = true;
            this.checkBoxAudio.Location = new System.Drawing.Point(31, 122);
            this.checkBoxAudio.Name = "checkBoxAudio";
            this.checkBoxAudio.Size = new System.Drawing.Size(72, 16);
            this.checkBoxAudio.TabIndex = 7;
            this.checkBoxAudio.Text = "开启音频";
            this.checkBoxAudio.UseVisualStyleBackColor = true;
            this.checkBoxAudio.CheckedChanged += new System.EventHandler(this.checkBoxAudio_CheckedChanged);
            // 
            // comboBoxAudio
            // 
            this.comboBoxAudio.Enabled = false;
            this.comboBoxAudio.FormattingEnabled = true;
            this.comboBoxAudio.Location = new System.Drawing.Point(124, 143);
            this.comboBoxAudio.Name = "comboBoxAudio";
            this.comboBoxAudio.Size = new System.Drawing.Size(104, 20);
            this.comboBoxAudio.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(31, 148);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(89, 12);
            this.label4.TabIndex = 9;
            this.label4.Text = "音频开启子窗口";
            // 
            // comboBoxFormat
            // 
            this.comboBoxFormat.FormattingEnabled = true;
            this.comboBoxFormat.Items.AddRange(new object[] {
            "NULL",
            "NTSC",
            "PAL"});
            this.comboBoxFormat.Location = new System.Drawing.Point(107, 186);
            this.comboBoxFormat.Name = "comboBoxFormat";
            this.comboBoxFormat.Size = new System.Drawing.Size(121, 20);
            this.comboBoxFormat.TabIndex = 10;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(27, 188);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 11;
            this.label5.Text = "视频制式";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(27, 222);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 12);
            this.label6.TabIndex = 13;
            this.label6.Text = "分辨率";
            // 
            // comboBoxResolution
            // 
            this.comboBoxResolution.FormattingEnabled = true;
            this.comboBoxResolution.Location = new System.Drawing.Point(107, 220);
            this.comboBoxResolution.Name = "comboBoxResolution";
            this.comboBoxResolution.Size = new System.Drawing.Size(121, 20);
            this.comboBoxResolution.TabIndex = 12;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(28, 253);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(71, 12);
            this.label7.TabIndex = 15;
            this.label7.Text = "BNC显示模式";
            // 
            // comboBoxScale
            // 
            this.comboBoxScale.FormattingEnabled = true;
            this.comboBoxScale.Items.AddRange(new object[] {
            "真实显示",
            "缩放显示"});
            this.comboBoxScale.Location = new System.Drawing.Point(108, 251);
            this.comboBoxScale.Name = "comboBoxScale";
            this.comboBoxScale.Size = new System.Drawing.Size(121, 20);
            this.comboBoxScale.TabIndex = 14;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(27, 325);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(65, 12);
            this.label8.TabIndex = 18;
            this.label8.Text = "放大子窗口";
            // 
            // comboBoxEnlarge
            // 
            this.comboBoxEnlarge.FormattingEnabled = true;
            this.comboBoxEnlarge.Location = new System.Drawing.Point(107, 321);
            this.comboBoxEnlarge.Name = "comboBoxEnlarge";
            this.comboBoxEnlarge.Size = new System.Drawing.Size(121, 20);
            this.comboBoxEnlarge.TabIndex = 17;
            // 
            // groupBox2
            // 
            this.groupBox2.Location = new System.Drawing.Point(24, 277);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(280, 10);
            this.groupBox2.TabIndex = 19;
            this.groupBox2.TabStop = false;
            // 
            // groupBox3
            // 
            this.groupBox3.Location = new System.Drawing.Point(24, 166);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(280, 10);
            this.groupBox3.TabIndex = 20;
            this.groupBox3.TabStop = false;
            // 
            // btnGetDispCfg
            // 
            this.btnGetDispCfg.Location = new System.Drawing.Point(52, 372);
            this.btnGetDispCfg.Name = "btnGetDispCfg";
            this.btnGetDispCfg.Size = new System.Drawing.Size(63, 25);
            this.btnGetDispCfg.TabIndex = 21;
            this.btnGetDispCfg.Text = "刷新";
            this.btnGetDispCfg.UseVisualStyleBackColor = true;
            this.btnGetDispCfg.Click += new System.EventHandler(this.btnGetDispCfg_Click);
            // 
            // btnSetDispCfg
            // 
            this.btnSetDispCfg.Location = new System.Drawing.Point(126, 372);
            this.btnSetDispCfg.Name = "btnSetDispCfg";
            this.btnSetDispCfg.Size = new System.Drawing.Size(60, 25);
            this.btnSetDispCfg.TabIndex = 22;
            this.btnSetDispCfg.Text = "设置";
            this.btnSetDispCfg.UseVisualStyleBackColor = true;
            this.btnSetDispCfg.Click += new System.EventHandler(this.btnSetDispCfg_Click);
            // 
            // btnEnlarge
            // 
            this.btnEnlarge.Location = new System.Drawing.Point(248, 293);
            this.btnEnlarge.Name = "btnEnlarge";
            this.btnEnlarge.Size = new System.Drawing.Size(53, 26);
            this.btnEnlarge.TabIndex = 23;
            this.btnEnlarge.Text = "放大";
            this.btnEnlarge.UseVisualStyleBackColor = true;
            this.btnEnlarge.Click += new System.EventHandler(this.btnEnlarge_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Location = new System.Drawing.Point(24, 351);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(280, 10);
            this.groupBox4.TabIndex = 20;
            this.groupBox4.TabStop = false;
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(199, 374);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(58, 23);
            this.btnExit.TabIndex = 25;
            this.btnExit.Text = "退出";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // btnResume
            // 
            this.btnResume.Location = new System.Drawing.Point(248, 324);
            this.btnResume.Name = "btnResume";
            this.btnResume.Size = new System.Drawing.Size(53, 23);
            this.btnResume.TabIndex = 26;
            this.btnResume.Text = "还原";
            this.btnResume.UseVisualStyleBackColor = true;
            this.btnResume.Click += new System.EventHandler(this.btnResume_Click);
            // 
            // checkBoxEnlarge
            // 
            this.checkBoxEnlarge.AutoSize = true;
            this.checkBoxEnlarge.Location = new System.Drawing.Point(27, 299);
            this.checkBoxEnlarge.Name = "checkBoxEnlarge";
            this.checkBoxEnlarge.Size = new System.Drawing.Size(132, 16);
            this.checkBoxEnlarge.TabIndex = 16;
            this.checkBoxEnlarge.Text = "是否有窗口放大显示";
            this.checkBoxEnlarge.UseVisualStyleBackColor = true;
            // 
            // DisplayChanCfg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(333, 412);
            this.Controls.Add(this.btnResume);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.btnEnlarge);
            this.Controls.Add(this.btnSetDispCfg);
            this.Controls.Add(this.btnGetDispCfg);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.comboBoxEnlarge);
            this.Controls.Add(this.checkBoxEnlarge);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.comboBoxScale);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.comboBoxResolution);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.comboBoxFormat);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.comboBoxAudio);
            this.Controls.Add(this.checkBoxAudio);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.comboBoxDecNo);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.comboBoxSubWin);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBoxWinMode);
            this.Controls.Add(this.groupBox1);
            this.Name = "DisplayChanCfg";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "显示通道配置 Display Channel Configuration";
            this.Load += new System.EventHandler(this.DisplayChanCfg_Load);
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBoxWinMode;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBoxSubWin;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBoxDecNo;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnSubWin;
        private System.Windows.Forms.CheckBox checkBoxAudio;
        private System.Windows.Forms.ComboBox comboBoxAudio;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboBoxFormat;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox comboBoxResolution;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox comboBoxScale;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ComboBox comboBoxEnlarge;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnGetDispCfg;
        private System.Windows.Forms.Button btnSetDispCfg;
        private System.Windows.Forms.Button btnEnlarge;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.Button btnResume;
        private System.Windows.Forms.CheckBox checkBoxEnlarge;
    }
}