namespace CsChatDemo
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
            this.testBtn = new System.Windows.Forms.Button();
            this.connectBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.phoneText = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.superCodeText = new System.Windows.Forms.TextBox();
            this.logLabel = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // testBtn
            // 
            this.testBtn.Location = new System.Drawing.Point(420, 12);
            this.testBtn.Margin = new System.Windows.Forms.Padding(1);
            this.testBtn.Name = "testBtn";
            this.testBtn.Size = new System.Drawing.Size(54, 19);
            this.testBtn.TabIndex = 0;
            this.testBtn.Text = "Test";
            this.testBtn.UseVisualStyleBackColor = true;
            this.testBtn.Click += new System.EventHandler(this.testBtn_Click);
            // 
            // connectBtn
            // 
            this.connectBtn.Location = new System.Drawing.Point(345, 12);
            this.connectBtn.Margin = new System.Windows.Forms.Padding(1);
            this.connectBtn.Name = "connectBtn";
            this.connectBtn.Size = new System.Drawing.Size(56, 19);
            this.connectBtn.TabIndex = 1;
            this.connectBtn.Text = "Connect";
            this.connectBtn.UseVisualStyleBackColor = true;
            this.connectBtn.Click += new System.EventHandler(this.connectBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 16);
            this.label1.Margin = new System.Windows.Forms.Padding(1, 0, 1, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "Phone:";
            // 
            // phoneText
            // 
            this.phoneText.Location = new System.Drawing.Point(48, 14);
            this.phoneText.Margin = new System.Windows.Forms.Padding(1);
            this.phoneText.Name = "phoneText";
            this.phoneText.Size = new System.Drawing.Size(104, 21);
            this.phoneText.TabIndex = 3;
            this.phoneText.Text = "13910001000";
            this.phoneText.TextChanged += new System.EventHandler(this.phoneText_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(159, 16);
            this.label2.Margin = new System.Windows.Forms.Padding(1, 0, 1, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "SuperCode:";
            // 
            // superCodeText
            // 
            this.superCodeText.Location = new System.Drawing.Point(227, 14);
            this.superCodeText.Margin = new System.Windows.Forms.Padding(1);
            this.superCodeText.Name = "superCodeText";
            this.superCodeText.Size = new System.Drawing.Size(102, 21);
            this.superCodeText.TabIndex = 5;
            // 
            // logLabel
            // 
            this.logLabel.Location = new System.Drawing.Point(12, 67);
            this.logLabel.Name = "logLabel";
            this.logLabel.Size = new System.Drawing.Size(459, 178);
            this.logLabel.TabIndex = 6;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(14, 52);
            this.label4.Name = "label4";
            this.label4.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 7;
            this.label4.Text = "：日志";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(479, 254);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.logLabel);
            this.Controls.Add(this.superCodeText);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.phoneText);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.connectBtn);
            this.Controls.Add(this.testBtn);
            this.Margin = new System.Windows.Forms.Padding(1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button testBtn;
        private System.Windows.Forms.Button connectBtn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox phoneText;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox superCodeText;
        private System.Windows.Forms.Label logLabel;
        private System.Windows.Forms.Label label4;
    }
}

