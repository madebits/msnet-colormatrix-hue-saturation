namespace QM
{
    partial class Form1
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.trHue = new System.Windows.Forms.TrackBar();
            this.trSat = new System.Windows.Forms.TrackBar();
            this.trBri = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.chkUseGdi = new System.Windows.Forms.CheckBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trHue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trSat)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trBri)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(320, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(114, 24);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(114, 24);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // pictureBox
            // 
            this.pictureBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox.Location = new System.Drawing.Point(12, 39);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(296, 192);
            this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox.TabIndex = 1;
            this.pictureBox.TabStop = false;
            // 
            // trHue
            // 
            this.trHue.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.trHue.AutoSize = false;
            this.trHue.Location = new System.Drawing.Point(88, 271);
            this.trHue.Maximum = 180;
            this.trHue.Minimum = -180;
            this.trHue.Name = "trHue";
            this.trHue.Size = new System.Drawing.Size(220, 32);
            this.trHue.TabIndex = 3;
            this.trHue.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trHue.ValueChanged += new System.EventHandler(this.trHue_ValueChanged);
            this.trHue.Scroll += new System.EventHandler(this.trHue_Scroll);
            // 
            // trSat
            // 
            this.trSat.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.trSat.AutoSize = false;
            this.trSat.Location = new System.Drawing.Point(88, 309);
            this.trSat.Maximum = 300;
            this.trSat.Minimum = -100;
            this.trSat.Name = "trSat";
            this.trSat.Size = new System.Drawing.Size(220, 32);
            this.trSat.TabIndex = 5;
            this.trSat.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trSat.Value = 100;
            this.trSat.ValueChanged += new System.EventHandler(this.trSat_ValueChanged);
            this.trSat.Scroll += new System.EventHandler(this.trSat_Scroll);
            // 
            // trBri
            // 
            this.trBri.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.trBri.AutoSize = false;
            this.trBri.Location = new System.Drawing.Point(88, 347);
            this.trBri.Maximum = 100;
            this.trBri.Minimum = -100;
            this.trBri.Name = "trBri";
            this.trBri.Size = new System.Drawing.Size(220, 32);
            this.trBri.TabIndex = 7;
            this.trBri.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trBri.ValueChanged += new System.EventHandler(this.trBri_ValueChanged);
            this.trBri.Scroll += new System.EventHandler(this.trBri_Scroll);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 271);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 17);
            this.label1.TabIndex = 2;
            this.label1.Text = "Hue";
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 309);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(73, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Saturation";
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 347);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(75, 17);
            this.label3.TabIndex = 6;
            this.label3.Text = "Brightness";
            // 
            // chkUseGdi
            // 
            this.chkUseGdi.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.chkUseGdi.AutoSize = true;
            this.chkUseGdi.Checked = true;
            this.chkUseGdi.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkUseGdi.Location = new System.Drawing.Point(12, 244);
            this.chkUseGdi.Name = "chkUseGdi";
            this.chkUseGdi.Size = new System.Drawing.Size(141, 21);
            this.chkUseGdi.TabIndex = 1;
            this.chkUseGdi.Text = "Use GDI+ (faster)";
            this.chkUseGdi.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(320, 384);
            this.Controls.Add(this.chkUseGdi);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.trBri);
            this.Controls.Add(this.trSat);
            this.Controls.Add(this.trHue);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "QMatrix Hue Demo";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trHue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trSat)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trBri)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.TrackBar trHue;
        private System.Windows.Forms.TrackBar trSat;
        private System.Windows.Forms.TrackBar trBri;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox chkUseGdi;
    }
}

