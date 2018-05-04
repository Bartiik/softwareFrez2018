namespace Frezarka
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
            this.components = new System.ComponentModel.Container();
            this.ConnectButton = new System.Windows.Forms.Button();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.SpeedText = new System.Windows.Forms.TextBox();
            this.SetSpeedButton = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.SpeedBar = new System.Windows.Forms.TrackBar();
            this.label7 = new System.Windows.Forms.Label();
            this.HomeY = new System.Windows.Forms.Button();
            this.ZPosText = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.HomeX = new System.Windows.Forms.Button();
            this.YPosText = new System.Windows.Forms.TextBox();
            this.HomeZ = new System.Windows.Forms.Button();
            this.XPosText = new System.Windows.Forms.TextBox();
            this.X4minus = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.X4plus = new System.Windows.Forms.Button();
            this.Z4plus = new System.Windows.Forms.Button();
            this.X3plus = new System.Windows.Forms.Button();
            this.X3minus = new System.Windows.Forms.Button();
            this.Z3plus = new System.Windows.Forms.Button();
            this.X1minus = new System.Windows.Forms.Button();
            this.X2plus = new System.Windows.Forms.Button();
            this.X2minus = new System.Windows.Forms.Button();
            this.Z2plus = new System.Windows.Forms.Button();
            this.X1plus = new System.Windows.Forms.Button();
            this.ZChangeText = new System.Windows.Forms.TextBox();
            this.Z1plus = new System.Windows.Forms.Button();
            this.Z4minus = new System.Windows.Forms.Button();
            this.Z3minus = new System.Windows.Forms.Button();
            this.Z2minus = new System.Windows.Forms.Button();
            this.Z1minus = new System.Windows.Forms.Button();
            this.Y4minus = new System.Windows.Forms.Button();
            this.BoardHoldButton = new System.Windows.Forms.Button();
            this.Y4plus = new System.Windows.Forms.Button();
            this.Y3plus = new System.Windows.Forms.Button();
            this.Y3minus = new System.Windows.Forms.Button();
            this.HomeAllButton = new System.Windows.Forms.Button();
            this.Y2minus = new System.Windows.Forms.Button();
            this.Y2plus = new System.Windows.Forms.Button();
            this.Y1minus = new System.Windows.Forms.Button();
            this.Y1plus = new System.Windows.Forms.Button();
            this.TableFlipButton = new System.Windows.Forms.Button();
            this.XYChangeText = new System.Windows.Forms.TextBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.MoveQueueDown = new System.Windows.Forms.Button();
            this.MoveQueueUp = new System.Windows.Forms.Button();
            this.AddCommandToQueue = new System.Windows.Forms.Button();
            this.label11 = new System.Windows.Forms.Label();
            this.CommandComboBox = new System.Windows.Forms.ComboBox();
            this.RemoveFromQueueButton = new System.Windows.Forms.Button();
            this.GCodeQueue = new System.Windows.Forms.ListBox();
            this.label10 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.UnloadGCode = new System.Windows.Forms.Button();
            this.AddGCodeToQueue = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.OpenedGCodesList = new System.Windows.Forms.ListBox();
            this.GCodeBrowseButton = new System.Windows.Forms.Button();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.CommandSendButton = new System.Windows.Forms.Button();
            this.customGText = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.CommunicationBox = new System.Windows.Forms.ListBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.CommandsInQueueLabel = new System.Windows.Forms.Label();
            this.MillingMachineStateLabel = new System.Windows.Forms.Label();
            this.ProgressBar = new System.Windows.Forms.ProgressBar();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.StopButton = new System.Windows.Forms.Button();
            this.PauseButton = new System.Windows.Forms.Button();
            this.OpenPortLabel = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.BeginButton = new System.Windows.Forms.Button();
            this.HardStopButton = new System.Windows.Forms.Button();
            this.PortListCombo = new System.Windows.Forms.ComboBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.tableLayoutPanel1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.groupBox6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SpeedBar)).BeginInit();
            this.groupBox8.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ConnectButton
            // 
            this.ConnectButton.Location = new System.Drawing.Point(146, 14);
            this.ConnectButton.Name = "ConnectButton";
            this.ConnectButton.Size = new System.Drawing.Size(88, 23);
            this.ConnectButton.TabIndex = 0;
            this.ConnectButton.Tag = "0";
            this.ConnectButton.Text = "Open Port";
            this.ConnectButton.UseVisualStyleBackColor = true;
            this.ConnectButton.Click += new System.EventHandler(this.ConnectButton_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel1.Controls.Add(this.groupBox2, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.groupBox3, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.groupBox4, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.groupBox1, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 60F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1008, 561);
            this.tableLayoutPanel1.TabIndex = 1;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.tableLayoutPanel2);
            this.groupBox2.Controls.Add(this.groupBox7);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Location = new System.Drawing.Point(3, 54);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(1002, 300);
            this.groupBox2.TabIndex = 8;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Control";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 3;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.tableLayoutPanel2.Controls.Add(this.groupBox6, 2, 0);
            this.tableLayoutPanel2.Controls.Add(this.groupBox8, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.groupBox5, 0, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 16);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(996, 241);
            this.tableLayoutPanel2.TabIndex = 5;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.SpeedText);
            this.groupBox6.Controls.Add(this.SetSpeedButton);
            this.groupBox6.Controls.Add(this.label8);
            this.groupBox6.Controls.Add(this.SpeedBar);
            this.groupBox6.Controls.Add(this.label7);
            this.groupBox6.Controls.Add(this.HomeY);
            this.groupBox6.Controls.Add(this.ZPosText);
            this.groupBox6.Controls.Add(this.label2);
            this.groupBox6.Controls.Add(this.HomeX);
            this.groupBox6.Controls.Add(this.YPosText);
            this.groupBox6.Controls.Add(this.HomeZ);
            this.groupBox6.Controls.Add(this.XPosText);
            this.groupBox6.Controls.Add(this.X4minus);
            this.groupBox6.Controls.Add(this.label1);
            this.groupBox6.Controls.Add(this.X4plus);
            this.groupBox6.Controls.Add(this.Z4plus);
            this.groupBox6.Controls.Add(this.X3plus);
            this.groupBox6.Controls.Add(this.X3minus);
            this.groupBox6.Controls.Add(this.Z3plus);
            this.groupBox6.Controls.Add(this.X1minus);
            this.groupBox6.Controls.Add(this.X2plus);
            this.groupBox6.Controls.Add(this.X2minus);
            this.groupBox6.Controls.Add(this.Z2plus);
            this.groupBox6.Controls.Add(this.X1plus);
            this.groupBox6.Controls.Add(this.ZChangeText);
            this.groupBox6.Controls.Add(this.Z1plus);
            this.groupBox6.Controls.Add(this.Z4minus);
            this.groupBox6.Controls.Add(this.Z3minus);
            this.groupBox6.Controls.Add(this.Z2minus);
            this.groupBox6.Controls.Add(this.Z1minus);
            this.groupBox6.Controls.Add(this.Y4minus);
            this.groupBox6.Controls.Add(this.BoardHoldButton);
            this.groupBox6.Controls.Add(this.Y4plus);
            this.groupBox6.Controls.Add(this.Y3plus);
            this.groupBox6.Controls.Add(this.Y3minus);
            this.groupBox6.Controls.Add(this.HomeAllButton);
            this.groupBox6.Controls.Add(this.Y2minus);
            this.groupBox6.Controls.Add(this.Y2plus);
            this.groupBox6.Controls.Add(this.Y1minus);
            this.groupBox6.Controls.Add(this.Y1plus);
            this.groupBox6.Controls.Add(this.TableFlipButton);
            this.groupBox6.Controls.Add(this.XYChangeText);
            this.groupBox6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox6.Location = new System.Drawing.Point(599, 3);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(394, 235);
            this.groupBox6.TabIndex = 2;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Manual Control";
            // 
            // SpeedText
            // 
            this.SpeedText.Enabled = false;
            this.SpeedText.Location = new System.Drawing.Point(325, 170);
            this.SpeedText.Name = "SpeedText";
            this.SpeedText.Size = new System.Drawing.Size(60, 20);
            this.SpeedText.TabIndex = 88;
            this.SpeedText.Text = "0";
            this.SpeedText.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.SpeedText.TextChanged += new System.EventHandler(this.SpeedText_TextChanged);
            // 
            // SetSpeedButton
            // 
            this.SetSpeedButton.Enabled = false;
            this.SetSpeedButton.Location = new System.Drawing.Point(325, 189);
            this.SetSpeedButton.Name = "SetSpeedButton";
            this.SetSpeedButton.Size = new System.Drawing.Size(60, 23);
            this.SetSpeedButton.TabIndex = 104;
            this.SetSpeedButton.Text = "set";
            this.SetSpeedButton.UseVisualStyleBackColor = true;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(319, 53);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(72, 13);
            this.label8.TabIndex = 0;
            this.label8.Text = "spindle speed";
            // 
            // SpeedBar
            // 
            this.SpeedBar.Enabled = false;
            this.SpeedBar.Location = new System.Drawing.Point(332, 66);
            this.SpeedBar.Maximum = 255;
            this.SpeedBar.Name = "SpeedBar";
            this.SpeedBar.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.SpeedBar.Size = new System.Drawing.Size(45, 104);
            this.SpeedBar.TabIndex = 0;
            this.SpeedBar.Scroll += new System.EventHandler(this.SpeedBar_Scroll);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(82, 206);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(14, 13);
            this.label7.TabIndex = 103;
            this.label7.Text = "Z";
            // 
            // HomeY
            // 
            this.HomeY.Enabled = false;
            this.HomeY.Location = new System.Drawing.Point(80, 39);
            this.HomeY.Name = "HomeY";
            this.HomeY.Size = new System.Drawing.Size(58, 24);
            this.HomeY.TabIndex = 89;
            this.HomeY.Tag = "HOME Y";
            this.HomeY.Text = "Home Y";
            this.HomeY.UseVisualStyleBackColor = true;
            this.HomeY.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.HomeY.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // ZPosText
            // 
            this.ZPosText.Enabled = false;
            this.ZPosText.Location = new System.Drawing.Point(102, 203);
            this.ZPosText.Name = "ZPosText";
            this.ZPosText.Size = new System.Drawing.Size(58, 20);
            this.ZPosText.TabIndex = 89;
            this.ZPosText.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(82, 180);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(14, 13);
            this.label2.TabIndex = 102;
            this.label2.Text = "Y";
            // 
            // HomeX
            // 
            this.HomeX.Enabled = false;
            this.HomeX.Location = new System.Drawing.Point(80, 11);
            this.HomeX.Name = "HomeX";
            this.HomeX.Size = new System.Drawing.Size(58, 25);
            this.HomeX.TabIndex = 88;
            this.HomeX.Tag = "HOME X";
            this.HomeX.Text = "Home X";
            this.HomeX.UseVisualStyleBackColor = true;
            this.HomeX.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.HomeX.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // YPosText
            // 
            this.YPosText.Enabled = false;
            this.YPosText.Location = new System.Drawing.Point(102, 177);
            this.YPosText.Name = "YPosText";
            this.YPosText.Size = new System.Drawing.Size(58, 20);
            this.YPosText.TabIndex = 88;
            this.YPosText.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // HomeZ
            // 
            this.HomeZ.Enabled = false;
            this.HomeZ.Location = new System.Drawing.Point(80, 66);
            this.HomeZ.Name = "HomeZ";
            this.HomeZ.Size = new System.Drawing.Size(58, 25);
            this.HomeZ.TabIndex = 90;
            this.HomeZ.Tag = "HOME Z";
            this.HomeZ.Text = "Home Z";
            this.HomeZ.UseVisualStyleBackColor = true;
            this.HomeZ.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.HomeZ.MouseHover += new System.EventHandler(this.ManualControlZMouseHoverEvent);
            // 
            // XPosText
            // 
            this.XPosText.Enabled = false;
            this.XPosText.Location = new System.Drawing.Point(102, 151);
            this.XPosText.Name = "XPosText";
            this.XPosText.Size = new System.Drawing.Size(58, 20);
            this.XPosText.TabIndex = 87;
            this.XPosText.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // X4minus
            // 
            this.X4minus.Enabled = false;
            this.X4minus.Location = new System.Drawing.Point(159, 87);
            this.X4minus.Name = "X4minus";
            this.X4minus.Size = new System.Drawing.Size(20, 60);
            this.X4minus.TabIndex = 94;
            this.X4minus.Tag = "X -10";
            this.X4minus.Text = "<\r\n<\r\n<\r\n<";
            this.X4minus.UseVisualStyleBackColor = true;
            this.X4minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.X4minus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(82, 154);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(14, 13);
            this.label1.TabIndex = 101;
            this.label1.Text = "X";
            // 
            // X4plus
            // 
            this.X4plus.Enabled = false;
            this.X4plus.Location = new System.Drawing.Point(237, 87);
            this.X4plus.Name = "X4plus";
            this.X4plus.Size = new System.Drawing.Size(20, 60);
            this.X4plus.TabIndex = 95;
            this.X4plus.Tag = "X +10";
            this.X4plus.Text = ">\r\n>\r\n>\r\n>";
            this.X4plus.UseVisualStyleBackColor = true;
            this.X4plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.X4plus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // Z4plus
            // 
            this.Z4plus.Enabled = false;
            this.Z4plus.Location = new System.Drawing.Point(6, 81);
            this.Z4plus.Name = "Z4plus";
            this.Z4plus.Size = new System.Drawing.Size(60, 20);
            this.Z4plus.TabIndex = 100;
            this.Z4plus.Tag = "Z +10";
            this.Z4plus.Text = "/\\/\\/\\/\\";
            this.Z4plus.UseVisualStyleBackColor = true;
            this.Z4plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Z4plus.MouseHover += new System.EventHandler(this.ManualControlZMouseHoverEvent);
            // 
            // X3plus
            // 
            this.X3plus.Enabled = false;
            this.X3plus.Location = new System.Drawing.Point(255, 93);
            this.X3plus.Name = "X3plus";
            this.X3plus.Size = new System.Drawing.Size(20, 48);
            this.X3plus.TabIndex = 93;
            this.X3plus.Tag = "X +5";
            this.X3plus.Text = ">\r\n>\r\n>";
            this.X3plus.UseVisualStyleBackColor = true;
            this.X3plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.X3plus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // X3minus
            // 
            this.X3minus.Enabled = false;
            this.X3minus.Location = new System.Drawing.Point(140, 93);
            this.X3minus.Name = "X3minus";
            this.X3minus.Size = new System.Drawing.Size(20, 48);
            this.X3minus.TabIndex = 78;
            this.X3minus.Tag = "X -5";
            this.X3minus.Text = "<\r\n<\r\n<";
            this.X3minus.UseVisualStyleBackColor = true;
            this.X3minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.X3minus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // Z3plus
            // 
            this.Z3plus.Enabled = false;
            this.Z3plus.Location = new System.Drawing.Point(12, 62);
            this.Z3plus.Name = "Z3plus";
            this.Z3plus.Size = new System.Drawing.Size(48, 20);
            this.Z3plus.TabIndex = 99;
            this.Z3plus.Tag = "Z +5";
            this.Z3plus.Text = "/\\/\\/\\";
            this.Z3plus.UseVisualStyleBackColor = true;
            this.Z3plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Z3plus.MouseHover += new System.EventHandler(this.ManualControlZMouseHoverEvent);
            // 
            // X1minus
            // 
            this.X1minus.Enabled = false;
            this.X1minus.Location = new System.Drawing.Point(102, 104);
            this.X1minus.Name = "X1minus";
            this.X1minus.Size = new System.Drawing.Size(20, 26);
            this.X1minus.TabIndex = 76;
            this.X1minus.Tag = "X -0.1";
            this.X1minus.Text = "<";
            this.X1minus.UseVisualStyleBackColor = true;
            this.X1minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.X1minus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // X2plus
            // 
            this.X2plus.Enabled = false;
            this.X2plus.Location = new System.Drawing.Point(274, 99);
            this.X2plus.Name = "X2plus";
            this.X2plus.Size = new System.Drawing.Size(20, 36);
            this.X2plus.TabIndex = 92;
            this.X2plus.Tag = "X +1";
            this.X2plus.Text = ">\r\n>";
            this.X2plus.UseVisualStyleBackColor = true;
            this.X2plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.X2plus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // X2minus
            // 
            this.X2minus.Enabled = false;
            this.X2minus.Location = new System.Drawing.Point(121, 99);
            this.X2minus.Name = "X2minus";
            this.X2minus.Size = new System.Drawing.Size(20, 36);
            this.X2minus.TabIndex = 77;
            this.X2minus.Tag = "X -1";
            this.X2minus.Text = "<\r\n<";
            this.X2minus.UseVisualStyleBackColor = true;
            this.X2minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.X2minus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // Z2plus
            // 
            this.Z2plus.Enabled = false;
            this.Z2plus.Location = new System.Drawing.Point(18, 43);
            this.Z2plus.Name = "Z2plus";
            this.Z2plus.Size = new System.Drawing.Size(36, 20);
            this.Z2plus.TabIndex = 98;
            this.Z2plus.Tag = "Z +1";
            this.Z2plus.Text = "/\\/\\";
            this.Z2plus.UseVisualStyleBackColor = true;
            this.Z2plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Z2plus.MouseHover += new System.EventHandler(this.ManualControlZMouseHoverEvent);
            // 
            // X1plus
            // 
            this.X1plus.Enabled = false;
            this.X1plus.Location = new System.Drawing.Point(293, 104);
            this.X1plus.Name = "X1plus";
            this.X1plus.Size = new System.Drawing.Size(20, 26);
            this.X1plus.TabIndex = 91;
            this.X1plus.Tag = "X +0.1";
            this.X1plus.Text = ">";
            this.X1plus.UseVisualStyleBackColor = true;
            this.X1plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.X1plus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // ZChangeText
            // 
            this.ZChangeText.Enabled = false;
            this.ZChangeText.Location = new System.Drawing.Point(6, 107);
            this.ZChangeText.Name = "ZChangeText";
            this.ZChangeText.Size = new System.Drawing.Size(60, 20);
            this.ZChangeText.TabIndex = 87;
            this.ZChangeText.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Z1plus
            // 
            this.Z1plus.Enabled = false;
            this.Z1plus.Location = new System.Drawing.Point(23, 24);
            this.Z1plus.Name = "Z1plus";
            this.Z1plus.Size = new System.Drawing.Size(26, 20);
            this.Z1plus.TabIndex = 97;
            this.Z1plus.Tag = "Z +0.1";
            this.Z1plus.Text = "/\\";
            this.Z1plus.UseVisualStyleBackColor = true;
            this.Z1plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Z1plus.MouseHover += new System.EventHandler(this.ManualControlZMouseHoverEvent);
            // 
            // Z4minus
            // 
            this.Z4minus.Enabled = false;
            this.Z4minus.Location = new System.Drawing.Point(6, 133);
            this.Z4minus.Name = "Z4minus";
            this.Z4minus.Size = new System.Drawing.Size(60, 20);
            this.Z4minus.TabIndex = 96;
            this.Z4minus.Tag = "Z -10";
            this.Z4minus.Text = "\\/\\/\\/\\/";
            this.Z4minus.UseVisualStyleBackColor = true;
            this.Z4minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Z4minus.MouseHover += new System.EventHandler(this.ManualControlZMouseHoverEvent);
            // 
            // Z3minus
            // 
            this.Z3minus.Enabled = false;
            this.Z3minus.Location = new System.Drawing.Point(12, 152);
            this.Z3minus.Name = "Z3minus";
            this.Z3minus.Size = new System.Drawing.Size(48, 20);
            this.Z3minus.TabIndex = 95;
            this.Z3minus.Tag = "Z -5";
            this.Z3minus.Text = "\\/\\/\\/";
            this.Z3minus.UseVisualStyleBackColor = true;
            this.Z3minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Z3minus.MouseHover += new System.EventHandler(this.ManualControlZMouseHoverEvent);
            // 
            // Z2minus
            // 
            this.Z2minus.Enabled = false;
            this.Z2minus.Location = new System.Drawing.Point(18, 171);
            this.Z2minus.Name = "Z2minus";
            this.Z2minus.Size = new System.Drawing.Size(36, 20);
            this.Z2minus.TabIndex = 94;
            this.Z2minus.Tag = "Z -1";
            this.Z2minus.Text = "\\/\\/";
            this.Z2minus.UseVisualStyleBackColor = true;
            this.Z2minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Z2minus.MouseHover += new System.EventHandler(this.ManualControlZMouseHoverEvent);
            // 
            // Z1minus
            // 
            this.Z1minus.Enabled = false;
            this.Z1minus.Location = new System.Drawing.Point(23, 190);
            this.Z1minus.Name = "Z1minus";
            this.Z1minus.Size = new System.Drawing.Size(26, 20);
            this.Z1minus.TabIndex = 93;
            this.Z1minus.Tag = "Z -0.1";
            this.Z1minus.Text = "\\/";
            this.Z1minus.UseVisualStyleBackColor = true;
            this.Z1minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Z1minus.MouseHover += new System.EventHandler(this.ManualControlZMouseHoverEvent);
            // 
            // Y4minus
            // 
            this.Y4minus.Enabled = false;
            this.Y4minus.Location = new System.Drawing.Point(178, 147);
            this.Y4minus.Name = "Y4minus";
            this.Y4minus.Size = new System.Drawing.Size(60, 20);
            this.Y4minus.TabIndex = 88;
            this.Y4minus.Tag = "Y -10";
            this.Y4minus.Text = "\\/\\/\\/\\/";
            this.Y4minus.UseVisualStyleBackColor = true;
            this.Y4minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Y4minus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // BoardHoldButton
            // 
            this.BoardHoldButton.Enabled = false;
            this.BoardHoldButton.Location = new System.Drawing.Point(242, 23);
            this.BoardHoldButton.Name = "BoardHoldButton";
            this.BoardHoldButton.Size = new System.Drawing.Size(74, 40);
            this.BoardHoldButton.TabIndex = 92;
            this.BoardHoldButton.Text = "board hold/unhold";
            this.BoardHoldButton.UseVisualStyleBackColor = true;
            // 
            // Y4plus
            // 
            this.Y4plus.Enabled = false;
            this.Y4plus.Location = new System.Drawing.Point(178, 68);
            this.Y4plus.Name = "Y4plus";
            this.Y4plus.Size = new System.Drawing.Size(60, 20);
            this.Y4plus.TabIndex = 83;
            this.Y4plus.Tag = "Y +10";
            this.Y4plus.Text = "/\\/\\/\\/\\";
            this.Y4plus.UseVisualStyleBackColor = true;
            this.Y4plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Y4plus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // Y3plus
            // 
            this.Y3plus.Enabled = false;
            this.Y3plus.Location = new System.Drawing.Point(184, 49);
            this.Y3plus.Name = "Y3plus";
            this.Y3plus.Size = new System.Drawing.Size(48, 20);
            this.Y3plus.TabIndex = 82;
            this.Y3plus.Tag = "Y +5";
            this.Y3plus.Text = "/\\/\\/\\";
            this.Y3plus.UseVisualStyleBackColor = true;
            this.Y3plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Y3plus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // Y3minus
            // 
            this.Y3minus.Enabled = false;
            this.Y3minus.Location = new System.Drawing.Point(184, 166);
            this.Y3minus.Name = "Y3minus";
            this.Y3minus.Size = new System.Drawing.Size(48, 20);
            this.Y3minus.TabIndex = 85;
            this.Y3minus.Tag = "Y -5";
            this.Y3minus.Text = "\\/\\/\\/";
            this.Y3minus.UseVisualStyleBackColor = true;
            this.Y3minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Y3minus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // HomeAllButton
            // 
            this.HomeAllButton.Enabled = false;
            this.HomeAllButton.Location = new System.Drawing.Point(178, 87);
            this.HomeAllButton.Name = "HomeAllButton";
            this.HomeAllButton.Size = new System.Drawing.Size(60, 40);
            this.HomeAllButton.TabIndex = 79;
            this.HomeAllButton.Tag = "HOME";
            this.HomeAllButton.Text = "Home All";
            this.HomeAllButton.UseVisualStyleBackColor = true;
            this.HomeAllButton.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.HomeAllButton.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // Y2minus
            // 
            this.Y2minus.Enabled = false;
            this.Y2minus.Location = new System.Drawing.Point(190, 185);
            this.Y2minus.Name = "Y2minus";
            this.Y2minus.Size = new System.Drawing.Size(36, 20);
            this.Y2minus.TabIndex = 84;
            this.Y2minus.Tag = "Y -1";
            this.Y2minus.Text = "\\/\\/";
            this.Y2minus.UseVisualStyleBackColor = true;
            this.Y2minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Y2minus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // Y2plus
            // 
            this.Y2plus.Enabled = false;
            this.Y2plus.Location = new System.Drawing.Point(190, 30);
            this.Y2plus.Name = "Y2plus";
            this.Y2plus.Size = new System.Drawing.Size(36, 20);
            this.Y2plus.TabIndex = 81;
            this.Y2plus.Tag = "Y +1";
            this.Y2plus.Text = "/\\/\\";
            this.Y2plus.UseVisualStyleBackColor = true;
            this.Y2plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Y2plus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // Y1minus
            // 
            this.Y1minus.Enabled = false;
            this.Y1minus.Location = new System.Drawing.Point(195, 204);
            this.Y1minus.Name = "Y1minus";
            this.Y1minus.Size = new System.Drawing.Size(26, 20);
            this.Y1minus.TabIndex = 83;
            this.Y1minus.Tag = "Y -0.1";
            this.Y1minus.Text = "\\/";
            this.Y1minus.UseVisualStyleBackColor = true;
            this.Y1minus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Y1minus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // Y1plus
            // 
            this.Y1plus.Enabled = false;
            this.Y1plus.Location = new System.Drawing.Point(195, 11);
            this.Y1plus.Name = "Y1plus";
            this.Y1plus.Size = new System.Drawing.Size(26, 20);
            this.Y1plus.TabIndex = 80;
            this.Y1plus.Tag = "Y +0.1";
            this.Y1plus.Text = "/\\";
            this.Y1plus.UseVisualStyleBackColor = true;
            this.Y1plus.MouseLeave += new System.EventHandler(this.ManualControlXYZMouseLeaveEvent);
            this.Y1plus.MouseHover += new System.EventHandler(this.ManualControlXYMouseHoverEvent);
            // 
            // TableFlipButton
            // 
            this.TableFlipButton.Enabled = false;
            this.TableFlipButton.Location = new System.Drawing.Point(242, 177);
            this.TableFlipButton.Name = "TableFlipButton";
            this.TableFlipButton.Size = new System.Drawing.Size(71, 28);
            this.TableFlipButton.TabIndex = 91;
            this.TableFlipButton.Text = "Flip Table";
            this.TableFlipButton.UseVisualStyleBackColor = true;
            // 
            // XYChangeText
            // 
            this.XYChangeText.Enabled = false;
            this.XYChangeText.Location = new System.Drawing.Point(179, 127);
            this.XYChangeText.Name = "XYChangeText";
            this.XYChangeText.Size = new System.Drawing.Size(58, 20);
            this.XYChangeText.TabIndex = 86;
            this.XYChangeText.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.MoveQueueDown);
            this.groupBox8.Controls.Add(this.MoveQueueUp);
            this.groupBox8.Controls.Add(this.AddCommandToQueue);
            this.groupBox8.Controls.Add(this.label11);
            this.groupBox8.Controls.Add(this.CommandComboBox);
            this.groupBox8.Controls.Add(this.RemoveFromQueueButton);
            this.groupBox8.Controls.Add(this.GCodeQueue);
            this.groupBox8.Controls.Add(this.label10);
            this.groupBox8.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox8.Location = new System.Drawing.Point(301, 3);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(292, 235);
            this.groupBox8.TabIndex = 4;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Milling Process Overview";
            // 
            // MoveQueueDown
            // 
            this.MoveQueueDown.Location = new System.Drawing.Point(141, 136);
            this.MoveQueueDown.Name = "MoveQueueDown";
            this.MoveQueueDown.Size = new System.Drawing.Size(75, 23);
            this.MoveQueueDown.TabIndex = 7;
            this.MoveQueueDown.Text = "Move Down";
            this.MoveQueueDown.UseVisualStyleBackColor = true;
            // 
            // MoveQueueUp
            // 
            this.MoveQueueUp.Location = new System.Drawing.Point(141, 107);
            this.MoveQueueUp.Name = "MoveQueueUp";
            this.MoveQueueUp.Size = new System.Drawing.Size(75, 23);
            this.MoveQueueUp.TabIndex = 6;
            this.MoveQueueUp.Text = "Move Up";
            this.MoveQueueUp.UseVisualStyleBackColor = true;
            // 
            // AddCommandToQueue
            // 
            this.AddCommandToQueue.Location = new System.Drawing.Point(141, 62);
            this.AddCommandToQueue.Name = "AddCommandToQueue";
            this.AddCommandToQueue.Size = new System.Drawing.Size(119, 23);
            this.AddCommandToQueue.TabIndex = 5;
            this.AddCommandToQueue.Text = "Add Command";
            this.AddCommandToQueue.UseVisualStyleBackColor = true;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(138, 23);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(120, 13);
            this.label11.TabIndex = 4;
            this.label11.Text = "Add command to queue";
            // 
            // CommandComboBox
            // 
            this.CommandComboBox.FormattingEnabled = true;
            this.CommandComboBox.Location = new System.Drawing.Point(141, 39);
            this.CommandComboBox.Name = "CommandComboBox";
            this.CommandComboBox.Size = new System.Drawing.Size(119, 21);
            this.CommandComboBox.TabIndex = 3;
            // 
            // RemoveFromQueueButton
            // 
            this.RemoveFromQueueButton.Location = new System.Drawing.Point(9, 196);
            this.RemoveFromQueueButton.Name = "RemoveFromQueueButton";
            this.RemoveFromQueueButton.Size = new System.Drawing.Size(120, 23);
            this.RemoveFromQueueButton.TabIndex = 2;
            this.RemoveFromQueueButton.Text = "Remove From Queue";
            this.RemoveFromQueueButton.UseVisualStyleBackColor = true;
            // 
            // GCodeQueue
            // 
            this.GCodeQueue.FormattingEnabled = true;
            this.GCodeQueue.Location = new System.Drawing.Point(9, 39);
            this.GCodeQueue.Name = "GCodeQueue";
            this.GCodeQueue.Size = new System.Drawing.Size(120, 147);
            this.GCodeQueue.TabIndex = 1;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 23);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(78, 13);
            this.label10.TabIndex = 0;
            this.label10.Text = "G-code queue:";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.UnloadGCode);
            this.groupBox5.Controls.Add(this.AddGCodeToQueue);
            this.groupBox5.Controls.Add(this.label9);
            this.groupBox5.Controls.Add(this.OpenedGCodesList);
            this.groupBox5.Controls.Add(this.GCodeBrowseButton);
            this.groupBox5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox5.Location = new System.Drawing.Point(3, 3);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(292, 235);
            this.groupBox5.TabIndex = 1;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Open G-Code file";
            // 
            // UnloadGCode
            // 
            this.UnloadGCode.Location = new System.Drawing.Point(140, 117);
            this.UnloadGCode.Name = "UnloadGCode";
            this.UnloadGCode.Size = new System.Drawing.Size(146, 23);
            this.UnloadGCode.TabIndex = 104;
            this.UnloadGCode.Text = "Unload the G-Code";
            this.UnloadGCode.UseVisualStyleBackColor = true;
            // 
            // AddGCodeToQueue
            // 
            this.AddGCodeToQueue.Location = new System.Drawing.Point(140, 88);
            this.AddGCodeToQueue.Name = "AddGCodeToQueue";
            this.AddGCodeToQueue.Size = new System.Drawing.Size(146, 23);
            this.AddGCodeToQueue.TabIndex = 103;
            this.AddGCodeToQueue.Text = "Add the G-Code to queue";
            this.AddGCodeToQueue.UseVisualStyleBackColor = true;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(3, 72);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(126, 13);
            this.label9.TabIndex = 102;
            this.label9.Text = "G-Codes already loaded: ";
            // 
            // OpenedGCodesList
            // 
            this.OpenedGCodesList.FormattingEnabled = true;
            this.OpenedGCodesList.Location = new System.Drawing.Point(6, 88);
            this.OpenedGCodesList.Name = "OpenedGCodesList";
            this.OpenedGCodesList.Size = new System.Drawing.Size(123, 134);
            this.OpenedGCodesList.TabIndex = 1;
            // 
            // GCodeBrowseButton
            // 
            this.GCodeBrowseButton.Location = new System.Drawing.Point(6, 23);
            this.GCodeBrowseButton.Name = "GCodeBrowseButton";
            this.GCodeBrowseButton.Size = new System.Drawing.Size(62, 21);
            this.GCodeBrowseButton.TabIndex = 0;
            this.GCodeBrowseButton.Text = "browse...";
            this.GCodeBrowseButton.UseVisualStyleBackColor = true;
            this.GCodeBrowseButton.Click += new System.EventHandler(this.GCodeBrowseButton_Click);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.CommandSendButton);
            this.groupBox7.Controls.Add(this.customGText);
            this.groupBox7.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.groupBox7.Location = new System.Drawing.Point(3, 257);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(996, 40);
            this.groupBox7.TabIndex = 3;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Custom G-Code";
            // 
            // CommandSendButton
            // 
            this.CommandSendButton.Enabled = false;
            this.CommandSendButton.Location = new System.Drawing.Point(6, 14);
            this.CommandSendButton.Name = "CommandSendButton";
            this.CommandSendButton.Size = new System.Drawing.Size(76, 23);
            this.CommandSendButton.TabIndex = 1;
            this.CommandSendButton.Text = "Send";
            this.CommandSendButton.UseVisualStyleBackColor = true;
            this.CommandSendButton.Click += new System.EventHandler(this.CommandSendButton_Click);
            // 
            // customGText
            // 
            this.customGText.Dock = System.Windows.Forms.DockStyle.Right;
            this.customGText.Enabled = false;
            this.customGText.Location = new System.Drawing.Point(81, 16);
            this.customGText.Name = "customGText";
            this.customGText.Size = new System.Drawing.Size(912, 20);
            this.customGText.TabIndex = 0;
            this.customGText.KeyDown += new System.Windows.Forms.KeyEventHandler(this.customGText_KeyDown);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.CommunicationBox);
            this.groupBox3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox3.Location = new System.Drawing.Point(3, 360);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(1002, 147);
            this.groupBox3.TabIndex = 9;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Communication Dialog";
            // 
            // CommunicationBox
            // 
            this.CommunicationBox.ColumnWidth = 900;
            this.CommunicationBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.CommunicationBox.FormattingEnabled = true;
            this.CommunicationBox.Location = new System.Drawing.Point(3, 16);
            this.CommunicationBox.MultiColumn = true;
            this.CommunicationBox.Name = "CommunicationBox";
            this.CommunicationBox.Size = new System.Drawing.Size(996, 128);
            this.CommunicationBox.TabIndex = 1;
            this.CommunicationBox.TabStop = false;
            this.CommunicationBox.UseTabStops = false;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.CommandsInQueueLabel);
            this.groupBox4.Controls.Add(this.MillingMachineStateLabel);
            this.groupBox4.Controls.Add(this.ProgressBar);
            this.groupBox4.Controls.Add(this.label5);
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox4.Location = new System.Drawing.Point(3, 513);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(1002, 45);
            this.groupBox4.TabIndex = 10;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Status";
            // 
            // CommandsInQueueLabel
            // 
            this.CommandsInQueueLabel.AutoSize = true;
            this.CommandsInQueueLabel.Location = new System.Drawing.Point(486, 26);
            this.CommandsInQueueLabel.Name = "CommandsInQueueLabel";
            this.CommandsInQueueLabel.Size = new System.Drawing.Size(13, 13);
            this.CommandsInQueueLabel.TabIndex = 0;
            this.CommandsInQueueLabel.Text = "0";
            // 
            // MillingMachineStateLabel
            // 
            this.MillingMachineStateLabel.AutoSize = true;
            this.MillingMachineStateLabel.Location = new System.Drawing.Point(166, 26);
            this.MillingMachineStateLabel.Name = "MillingMachineStateLabel";
            this.MillingMachineStateLabel.Size = new System.Drawing.Size(13, 13);
            this.MillingMachineStateLabel.TabIndex = 1;
            this.MillingMachineStateLabel.Text = "0";
            // 
            // ProgressBar
            // 
            this.ProgressBar.Location = new System.Drawing.Point(759, 19);
            this.ProgressBar.Name = "ProgressBar";
            this.ProgressBar.Size = new System.Drawing.Size(234, 23);
            this.ProgressBar.Step = 100;
            this.ProgressBar.TabIndex = 10;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(699, 25);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(54, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Progress: ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(331, 25);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(149, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Messages awaiting in Queue: ";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 26);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(151, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Current Milling Machine State: ";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.StopButton);
            this.groupBox1.Controls.Add(this.PauseButton);
            this.groupBox1.Controls.Add(this.OpenPortLabel);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.BeginButton);
            this.groupBox1.Controls.Add(this.HardStopButton);
            this.groupBox1.Controls.Add(this.ConnectButton);
            this.groupBox1.Controls.Add(this.PortListCombo);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(3, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1002, 45);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Connections";
            // 
            // StopButton
            // 
            this.StopButton.Enabled = false;
            this.StopButton.Location = new System.Drawing.Point(626, 14);
            this.StopButton.Name = "StopButton";
            this.StopButton.Size = new System.Drawing.Size(75, 23);
            this.StopButton.TabIndex = 11;
            this.StopButton.Text = "Stop Early";
            this.StopButton.UseVisualStyleBackColor = true;
            // 
            // PauseButton
            // 
            this.PauseButton.Enabled = false;
            this.PauseButton.Location = new System.Drawing.Point(545, 14);
            this.PauseButton.Name = "PauseButton";
            this.PauseButton.Size = new System.Drawing.Size(75, 23);
            this.PauseButton.TabIndex = 10;
            this.PauseButton.Text = "Pause";
            this.PauseButton.UseVisualStyleBackColor = true;
            // 
            // OpenPortLabel
            // 
            this.OpenPortLabel.AutoSize = true;
            this.OpenPortLabel.Location = new System.Drawing.Point(350, 19);
            this.OpenPortLabel.Name = "OpenPortLabel";
            this.OpenPortLabel.Size = new System.Drawing.Size(13, 13);
            this.OpenPortLabel.TabIndex = 9;
            this.OpenPortLabel.Text = "0";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(240, 19);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(104, 13);
            this.label6.TabIndex = 0;
            this.label6.Text = "Currently Used Port: ";
            // 
            // BeginButton
            // 
            this.BeginButton.Enabled = false;
            this.BeginButton.Location = new System.Drawing.Point(425, 14);
            this.BeginButton.Name = "BeginButton";
            this.BeginButton.Size = new System.Drawing.Size(114, 23);
            this.BeginButton.TabIndex = 8;
            this.BeginButton.Text = "Start Milling Process";
            this.BeginButton.UseVisualStyleBackColor = true;
            // 
            // HardStopButton
            // 
            this.HardStopButton.BackColor = System.Drawing.Color.Red;
            this.HardStopButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.HardStopButton.ForeColor = System.Drawing.SystemColors.ControlText;
            this.HardStopButton.Location = new System.Drawing.Point(797, 9);
            this.HardStopButton.Name = "HardStopButton";
            this.HardStopButton.Size = new System.Drawing.Size(196, 30);
            this.HardStopButton.TabIndex = 7;
            this.HardStopButton.Text = "STOP";
            this.HardStopButton.UseVisualStyleBackColor = false;
            // 
            // PortListCombo
            // 
            this.PortListCombo.FormattingEnabled = true;
            this.PortListCombo.Location = new System.Drawing.Point(19, 16);
            this.PortListCombo.Name = "PortListCombo";
            this.PortListCombo.Size = new System.Drawing.Size(121, 21);
            this.PortListCombo.TabIndex = 6;
            this.PortListCombo.Enter += new System.EventHandler(this.PortListCombo_Enter);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "\"G-Code files(*.g)|*.g|All files (*.*)|*.*\"";
            // 
            // serialPort
            // 
            this.serialPort.BaudRate = 115200;
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 561);
            this.Controls.Add(this.tableLayoutPanel1);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(1024, 600);
            this.MinimumSize = new System.Drawing.Size(1024, 600);
            this.Name = "Form1";
            this.Text = "Form1";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.SpeedBar)).EndInit();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button ConnectButton;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label MillingMachineStateLabel;
        private System.Windows.Forms.Label CommandsInQueueLabel;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox PortListCombo;
        private System.Windows.Forms.ProgressBar ProgressBar;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label OpenPortLabel;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button BeginButton;
        private System.Windows.Forms.Button HardStopButton;
        private System.Windows.Forms.ListBox CommunicationBox;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Button GCodeBrowseButton;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Button StopButton;
        private System.Windows.Forms.Button PauseButton;
        private System.Windows.Forms.TextBox customGText;
        private System.Windows.Forms.Button BoardHoldButton;
        private System.Windows.Forms.TextBox ZChangeText;
        private System.Windows.Forms.Button TableFlipButton;
        private System.Windows.Forms.Button HomeX;
        private System.Windows.Forms.TextBox XYChangeText;
        private System.Windows.Forms.Button HomeY;
        private System.Windows.Forms.Button Y3minus;
        private System.Windows.Forms.Button HomeZ;
        private System.Windows.Forms.Button Y2minus;
        private System.Windows.Forms.Button Y1minus;
        private System.Windows.Forms.Button Y3plus;
        private System.Windows.Forms.Button Y2plus;
        private System.Windows.Forms.Button Y1plus;
        private System.Windows.Forms.Button HomeAllButton;
        private System.Windows.Forms.Button X3minus;
        private System.Windows.Forms.Button X2minus;
        private System.Windows.Forms.Button X1minus;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox ZPosText;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox YPosText;
        private System.Windows.Forms.TextBox XPosText;
        private System.Windows.Forms.Button X4minus;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button X4plus;
        private System.Windows.Forms.Button Z4plus;
        private System.Windows.Forms.Button X3plus;
        private System.Windows.Forms.Button Z3plus;
        private System.Windows.Forms.Button X2plus;
        private System.Windows.Forms.Button Z2plus;
        private System.Windows.Forms.Button X1plus;
        private System.Windows.Forms.Button Z1plus;
        private System.Windows.Forms.Button Z4minus;
        private System.Windows.Forms.Button Z3minus;
        private System.Windows.Forms.Button Z2minus;
        private System.Windows.Forms.Button Z1minus;
        private System.Windows.Forms.Button Y4minus;
        private System.Windows.Forms.Button Y4plus;
        private System.Windows.Forms.TextBox SpeedText;
        private System.Windows.Forms.Button SetSpeedButton;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TrackBar SpeedBar;
        private System.Windows.Forms.ListBox OpenedGCodesList;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.ComboBox CommandComboBox;
        private System.Windows.Forms.Button RemoveFromQueueButton;
        private System.Windows.Forms.ListBox GCodeQueue;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Button UnloadGCode;
        private System.Windows.Forms.Button AddGCodeToQueue;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button MoveQueueUp;
        private System.Windows.Forms.Button AddCommandToQueue;
        private System.Windows.Forms.Button MoveQueueDown;
        private System.Windows.Forms.Button CommandSendButton;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.IO.Ports.SerialPort serialPort;
    }
}

