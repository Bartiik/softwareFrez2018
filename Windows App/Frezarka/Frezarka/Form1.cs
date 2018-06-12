using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Threading;
using System.Windows.Forms;
namespace Frezarka
{
    public partial class Form1 : Form
    {
        public List<Command> AllCommands = new List<Command>();
        public List<string> FilesLoaded = new List<string>();
        bool workingMessage = false;
        bool WorkInProgress = false;
        int currentMessage = 0;
        public List<Command> Queue = new List<Command>();
        int Commands;
        public Form1()
        {
            InitializeComponent();
        }
        private void ManualControlXYMouseHoverEvent(object sender, EventArgs e)
        {
            XYChangeText.Text = ((Button)sender).Tag.ToString();
        }
        private void ManualControlZMouseHoverEvent(object sender, EventArgs e)
        {
            ZChangeText.Text = ((Button)sender).Tag.ToString();
        }
        private void ManualControlXYZMouseLeaveEvent(object sender, EventArgs e)
        {
            ZChangeText.Text = "";
            XYChangeText.Text = "";
        }
        private void GCodeBrowseButton_Click(object sender, EventArgs e)
        {

        }
        private void SpeedBar_Scroll(object sender, EventArgs e)
        {
            SpeedText.Text = (SpeedBar.Value*100).ToString();
        }
        private void SpeedText_TextChanged(object sender, EventArgs e)
        {
           
        }
        private void ConnectButton_Click(object sender, EventArgs e)
        {
            try
            {
                if (ConnectButton.Tag.ToString() == "0")
                {
                    ConnectButton.Tag = "1";
                    ConnectButton.Text = "Close Port";
                    serialPort.BaudRate = 115200;
                    serialPort.PortName = PortListCombo.SelectedItem.ToString();
                    serialPort.Open();
                    if (serialPort.IsOpen)
                    {
                        OpenPortLabel.Text = serialPort.PortName;
                    }
                    Command begin = new Command(Int32.Parse(XYAxisSteps.Text),Int32.Parse(ZAxisSteps.Text));
                    begin.Fill("U4");
                    try
                    {
                        serialPort.DiscardOutBuffer();
                    }
                    catch (Exception error1)
                    {
                        MessageBox.Show("buffer is empty\n" + error1);
                    }
                    Thread.Sleep(1000);
                    prepareMessage(begin);
                    ManualControlEnable(true);
                    MillingProcessEnable(true);


                }
                else
                {
                    ConnectButton.Tag = "0";
                    ConnectButton.Text = "Open Port";
                    serialPort.Close();
                    ManualControlEnable(false);
                    MillingProcessEnable(false);
                }
            }
            catch (Exception error)
            {
                MessageBox.Show("Wrong port\n" + error);
            }

        }
        private void CommandSendButton_Click(object sender, EventArgs e)
        {
            String gcode = customGText.Text;
            Command temp = new Command(Int32.Parse(XYAxisSteps.Text),Int32.Parse(ZAxisSteps.Text));
            if (temp.Fill(gcode))
            {
                //MessageBox.Show(temp.ToSend());
                customGText.Clear();
                prepareMessage(temp);
            }
            else MessageBox.Show("Something went Wrong");
        }
        void sendCommand(Command comm)
        {
            if (serialPort.IsOpen)
            {
                if (serialPort.BytesToWrite > 0)
                {
                    serialPort.DiscardOutBuffer();
                }
                comm = updateMovement(comm);
                addToCommunicationBox(true, comm);
                serialPort.WriteLine(comm.ToSend());
                workingMessage = true;
            }
        }
        void MillingProcessEnable(bool e)
        {
            BeginButton.Enabled = e;
            PauseButton.Enabled = e;
            StopButton.Enabled = e;
        }
        void ManualControlEnable(bool e)
        {
            
            Z1plus.Enabled = e;
            Z2plus.Enabled = e;
            Z3plus.Enabled = e;
            Z4plus.Enabled = e;
            Z1minus.Enabled = e;
            Z2minus.Enabled = e;
            Z3minus.Enabled = e;
            Z4minus.Enabled = e;
            Y1plus.Enabled = e;
            Y2plus.Enabled = e;
            Y3plus.Enabled = e;
            Y4plus.Enabled = e;
            Y1minus.Enabled = e;
            Y2minus.Enabled = e;
            Y3minus.Enabled = e;
            Y4minus.Enabled = e;
            X1plus.Enabled = e;
            X2plus.Enabled = e;
            X3plus.Enabled = e;
            X4plus.Enabled = e;
            X1minus.Enabled = e;
            X2minus.Enabled = e;
            X3minus.Enabled = e;
            X4minus.Enabled = e;
            HomeAllButton.Enabled = e;
            HomeX.Enabled = e;
            HomeY.Enabled = e;
            HomeZ.Enabled = e;
            BoardHoldButton.Enabled = e;
            TableFlipButton.Enabled = e;
            SpeedBar.Enabled = e;
            SpeedText.Enabled = e;
            SetSpeedButton.Enabled = e;
            CommandSendButton.Enabled = e;
            customGText.Enabled = e;
            GenerateButton.Enabled = e;
            SpindleOnOff.Enabled = e;
            XYAxisSteps.Enabled = e;
            ZAxisSteps.Enabled = e;
        }
        private void customGText_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                CommandSendButton_Click(sender, e);
            }
        }
        void addToCommunicationBox(bool messageToArduino, Command C)
        {
            String time = DateTime.Now.ToString("hh:mm:ss tt");
            StringBuilder k = new StringBuilder();
            k.Append(time);
            if (messageToArduino)
            {
                k.Append(" <<<< ");
            }
            else
            {
                k.Append(" >>>> ");
            }
            k.Append(C.ToString());
            CommunicationBox.Invoke((MethodInvoker)delegate
            {
                CommunicationBox.Items.Add(k.ToString());
                CommunicationBox.SelectedIndex = CommunicationBox.Items.Count - 1;
            });
        }
        void addToCommunicationBox(bool messageToArduino, String C)
        {
            String time = DateTime.Now.ToString("hh:mm:ss tt");
            StringBuilder k = new StringBuilder();
            k.Append(time);
            if (messageToArduino)
            {
                k.Append(" <<<< ");
            }
            else
            {
                k.Append(" >>>> ");
            }
            k.Append(C);
            CommunicationBox.Invoke((MethodInvoker)delegate
            {
                CommunicationBox.Items.Add(k.ToString());
                CommunicationBox.SelectedIndex = CommunicationBox.Items.Count - 1;
            });
        }
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Command temp = new Command(Int32.Parse(XYAxisSteps.Text),Int32.Parse(ZAxisSteps.Text));
            String msg = serialPort.ReadLine();
            String State;
            int state;
            State = msg[0].ToString();
            //MessageBox.Show(msg);
            String st = MillingMachineStateLabel.Text;

            if (Int32.TryParse(State, out state))
            {
                State = state.ToString();
            }
            else
            {
                State = "ERROR";
            }
            MillingMachineStateLabel.Invoke((MethodInvoker)delegate
            {
                MillingMachineStateLabel.Text = State;
            });
            msg = msg.Remove(0, 1);
            String message;
            if (temp.Fill(msg))
            {
                if (temp.returnValue('W') != 1234.56789)
                {
                    switch (temp.returnValue('W'))
                    {
                        case 0:
                            {
                                message = "Warning.";
                            }
                            break;
                        case 1:
                            {
                                message = "Warning. Interpretation failed";
                            }
                            break;
                        default:
                            {
                                message = "Warning. Unknown";
                            }
                            break;
                    }

                }
                else if (temp.returnValue('E') != 1234.56789)
                {
                    switch (temp.returnValue('E'))
                    {
                        case 1:
                            {
                                message = "ERROR! Unexpected state change.";
                            }
                            break;
                        case 2:
                            {
                                message = "ERROR! Unknown state reached.";
                            }
                            break;
                        case 3:
                            {
                                message = "ERROR! Unknown G-Code sent.";
                            }
                            break;

                        default:
                            {
                                message = "ERROR! Unknown.";
                            }
                            break;
                    }
                }
                else if (temp.returnValue('U') == 5)
                {
                    //message = "OK.";
                    message = msg;
                    XPosText.Invoke((MethodInvoker)delegate
                    {
                        XPosText.Text = Math.Round(temp.returnValue('X') / double.Parse(XYAxisSteps.Text),5).ToString();
                    });
                    YPosText.Invoke((MethodInvoker)delegate
                    {
                        YPosText.Text = Math.Round(temp.returnValue('Y') / double.Parse(XYAxisSteps.Text),5).ToString();
                    });
                    ZPosText.Invoke((MethodInvoker)delegate
                    {
                        ZPosText.Text = Math.Round(temp.returnValue('Z') / double.Parse(ZAxisSteps.Text),5).ToString();
                    });


                }
                else message = msg;

                addToCommunicationBox(false, message);
            }
            workingMessage = false;
            if (Queue.Count > 0)
            {
                prepareMessage(Queue[0]);
                Queue.RemoveAt(0);
                CommandsInQueueLabel.Invoke((MethodInvoker)delegate
                {
                    CommandsInQueueLabel.Text = Queue.Count.ToString();
                });
                
                
            }
            if(WorkInProgress)
            {
                prepareMessage(AllCommands[currentMessage]);
                ProgressBar.Value = currentMessage;
                RemainingGCodesLabel.Text = (AllCommands.Count-currentMessage).ToString();
                currentMessage++;

            }



            //if (st == "0" && State == "2")
            //{
            //    temp.Fill("U4");
            //    sendCommand(temp);
            //}
        }
        private void PortListCombo_MouseDown(object sender, MouseEventArgs e)
        {
            PortListCombo.Items.Clear();
            PortListCombo.Items.AddRange(SerialPort.GetPortNames());
        }
        private void GCodeBrowseButton_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop)) e.Effect = DragDropEffects.Copy;
        }
        private void GCodeBrowseButton_DragDrop(object sender, DragEventArgs e)
        {
            //int length = 0;
            //int length1 = 0;
            List<String> codes = new List<string>();
            List<int> val = new List<int>();

            StringBuilder k = new StringBuilder();
            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
            foreach (string file in files)
            {
                //k.AppendLine(Path.GetFileName(file));
                //foreach(String line in File.ReadAllLines(file))
                //{
                //    length++;
                //    string code = line.Substring(0, 3);
                //    if(!codes.Contains(code))
                //    {
                //        codes.Add(code);
                //        val.Add(1);
                //    }
                //    else
                //    {
                //        val[codes.IndexOf(code)]++;
                //    }
                //}
                //for(int i = 0; i< val.Count; i++)
                //{
                //    k.Append(codes[i]);
                //    k.Append(" : ");
                //    k.AppendLine(val[i].ToString());
                //    length1 += val[i];
                //}
                //k.AppendLine(length1.ToString());
                //k.AppendLine(length.ToString());
                //MessageBox.Show(k.ToString());
                //k.Clear();
                if (!OpenedGCodesList.Items.Contains(Path.GetFileName(file)))
                {
                    FilesLoaded.Add(Path.GetFileName(file));
                    OpenedGCodesList.Items.Add(Path.GetFileName(file));
                }
                else
                    MessageBox.Show(Path.GetFileName(file) + " already exists!");
            }

        }
        private void RemoveFileButton_Click(object sender, EventArgs e)
        {
            if (OpenedGCodesList.SelectedItem != null)
            {
                int chosen = OpenedGCodesList.SelectedIndex;

                if (FirstLayerTextBox.Text == OpenedGCodesList.SelectedItem.ToString()) FirstLayerTextBox.Clear();
                if (SecondLayerTextBox.Text == OpenedGCodesList.SelectedItem.ToString()) SecondLayerTextBox.Clear();
                if (HolesTextBox.Text == OpenedGCodesList.SelectedItem.ToString()) HolesTextBox.Clear();
                if (BoundaryTextBox.Text == OpenedGCodesList.SelectedItem.ToString()) BoundaryTextBox.Clear();
                FilesLoaded.RemoveAt(chosen);
                OpenedGCodesList.Items.RemoveAt(chosen);
            }

        }
        private void Clear(object sender, EventArgs e)
        {
            switch (((Button)sender).Tag.ToString())
            {
                case "1": FirstLayerTextBox.Clear(); break;
                case "2": SecondLayerTextBox.Clear(); break;
                case "3": HolesTextBox.Clear(); break;
                case "4": BoundaryTextBox.Clear(); break;
            }
        }
        private void Add(object sender, EventArgs e)
        {
            if (OpenedGCodesList.SelectedItem != null)
                switch (((Button)sender).Tag.ToString())
                {
                    case "1": FirstLayerTextBox.Text = OpenedGCodesList.SelectedItem.ToString(); break;
                    case "2": SecondLayerTextBox.Text = OpenedGCodesList.SelectedItem.ToString(); break;
                    case "3": HolesTextBox.Text = OpenedGCodesList.SelectedItem.ToString(); break;
                    case "4": BoundaryTextBox.Text = OpenedGCodesList.SelectedItem.ToString(); break;
                }

        }
        private void drop(object sender, DragEventArgs e)
        {
            List<String> codes = new List<string>();
            List<int> val = new List<int>();

            StringBuilder k = new StringBuilder();
            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
            if (files.Length > 1)
            {
                MessageBox.Show("too many items, first one is added: " + files[0]);
            }
            string file = files[0];
            if (!OpenedGCodesList.Items.Contains(Path.GetFileName(file)))
            {
                FilesLoaded.Add(file);
                OpenedGCodesList.Items.Add(Path.GetFileName(file));
            }
            else
                MessageBox.Show(Path.GetFileName(file) + " already exists!");

            switch (((TextBox)sender).Tag.ToString())
            {
                case "1": FirstLayerTextBox.Text = Path.GetFileName(file); break;
                case "2": SecondLayerTextBox.Text = Path.GetFileName(file); break;
                case "3": HolesTextBox.Text = Path.GetFileName(file); break;
                case "4": BoundaryTextBox.Text = Path.GetFileName(file); break;
            }
        }
        private void Drag_Enter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop)) e.Effect = DragDropEffects.Copy;
        }
        private void GenerateButton_Click(object sender, EventArgs e)
        {
            AllCommands.Clear();
            StringBuilder k = new StringBuilder();
            int i = 0;
            Command temp = new Command(Int32.Parse(XYAxisSteps.Text),Int32.Parse(ZAxisSteps.Text));
            if (FirstLayerTextBox.Text != "")
                foreach (String line in File.ReadAllLines(FilesLoaded[OpenedGCodesList.Items.IndexOf(FirstLayerTextBox.Text)]))
                {
                    if (temp.Fill(line))
                    {
                        AllCommands.Add(temp);
                    }
                    else
                    {
                        k.AppendLine(line);
                        i++;
                    }
                }
            if (SecondLayerTextBox.Text != "")
                foreach (String line in File.ReadAllLines(FilesLoaded[OpenedGCodesList.Items.IndexOf(SecondLayerTextBox.Text)]))
                {
                    if (temp.Fill(line))
                    {
                        AllCommands.Add(temp);
                    }
                    else
                    {
                        k.AppendLine(line);
                        i++;
                    }
                }
            if (HolesTextBox.Text != "")
                foreach (String line in File.ReadAllLines(FilesLoaded[OpenedGCodesList.Items.IndexOf(HolesTextBox.Text)]))
                {
                    if (temp.Fill(line))
                    {
                        AllCommands.Add(temp);
                    }
                    else
                    {
                        k.AppendLine(line);
                        i++;
                    }
                }
            if (BoundaryTextBox.Text != "")
                foreach (String line in File.ReadAllLines(FilesLoaded[OpenedGCodesList.Items.IndexOf(BoundaryTextBox.Text)]))
                {
                    if (temp.Fill(line))
                    {
                        AllCommands.Add(temp);
                    }
                    else
                    {
                        k.AppendLine(line);
                        i++;
                    }
                }
            Commands = AllCommands.Count;
            RemainingGCodesLabel.Text = Commands.ToString();
            ProgressBar.Maximum = AllCommands.Count;
            ProgressBar.Value = 0;
            if(i>0)
                MessageBox.Show(k.ToString());
        }
        private bool prepareMessage(Command C)
        {
            if (workingMessage)
            {
                Queue.Add(C);
                CommandsInQueueLabel.Text = Queue.Count.ToString();
                return false;
            }
            else
            {
                sendCommand(C);
                return true;
            }
                
        }
        private void BeginButton_Click(object sender, EventArgs e)
        {
            if(AllCommands.Count>0)
            {
                WorkInProgress = true;
                ManualControlEnable(false);
                prepareMessage(AllCommands[0]);
            }
            else
            {
                MessageBox.Show("Generate G-Codes first!");
            }

        }
        private void PauseButton_Click(object sender, EventArgs e)
        {
            WorkInProgress = false;
            ManualControlEnable(true);
        }
        private void StopButton_Click(object sender, EventArgs e)
        {
            WorkInProgress = false;
            ManualControlEnable(true);
            AllCommands.Clear();
            Queue.Clear();
            CommandsInQueueLabel.Text = "0";
            RemainingGCodesLabel.Text = "0";
        }
        private void HardStopButton_Click(object sender, EventArgs e)
        {
            Command temp = new Command(Int32.Parse(XYAxisSteps.Text),Int32.Parse(ZAxisSteps.Text));
            temp.Fill("U7");
            sendCommand(temp);
        }
        private void ManualControlButton(object sender, EventArgs e)
        {
            Command temp = new Command(Int32.Parse(XYAxisSteps.Text), Int32.Parse(ZAxisSteps.Text));
            String message;
            String tag = ((Button)sender).Tag.ToString();
            switch (tag)
            {
                case "HOME": message = "G28"; break;
                case "HOME X": message = "G28"; break;
                case "HOME Y": message = "G28"; break;
                case "HOME Z": message = "G28"; break;
                case "SET":
                    {
                        message = "S1"+SpeedText.Text;
                        break;
                    }
                case "HOLD":
                    {
                        {
                            if (SpindleOnOff.Text == "Table Hold")
                            {
                                message = "M01";
                                SpindleOnOff.Text = "Table Unhold";
                            }
                            else
                            {
                                message = "M02";
                                SpindleOnOff.Text = "Table Hold";
                            }

                            break;
                        }
                    }
                    break;
                case "SPINDLE":
                    {
                        if(SpindleOnOff.Text=="Spindle On")
                        {
                            message = "M03";
                            SpindleOnOff.Text="Spindle Off";
                        }
                        else
                        {
                            message = "M05";
                            SpindleOnOff.Text = "Spindle On";
                        }
                        
                        break;
                    }
                case "FLIP": message = "U0"; break;
                default:
                    {
                        StringBuilder k = new StringBuilder();
                        k.Append("G00");
                        k.Append(tag[0]);
                        tag = tag.Replace('.', ',');
                        tag = tag.Remove(0, 2);
                        float val = 0;
                        if (tag[0] == '+')
                        {
                            tag = tag.Remove(0, 1);
                            val = val + float.Parse(tag);
                        }
                        else
                        {
                            tag = tag.Remove(0, 1);
                            val = val - float.Parse(tag);
                        }
                        k.Append(val);
                        message = k.ToString();
                        break;
                    }
            };
            temp.Fill(message);
            prepareMessage(temp);
        }
        private void SpeedText_KeyUp(object sender, KeyEventArgs e)
        {
            int value;
            if (Int32.TryParse(SpeedText.Text, out value))
            {
                if (value > SpeedBar.Maximum)
                {
                    SpeedBar.Value = SpeedBar.Maximum;
                    SpeedText.Text = SpeedBar.Maximum.ToString();
                }
                else if (value > SpeedBar.Minimum)
                {
                    SpeedBar.Value = value;
                }
                else
                {
                    SpeedBar.Value = SpeedBar.Minimum;
                    SpeedText.Text = SpeedBar.Minimum.ToString();
                }
            }
            else SpeedBar.Value = 0;
        }
        private Command updateMovement(Command comm)
        {
            if(comm.returnValue('G') != 1234.56789)
            {
                Command C = new Command(Int32.Parse(XYAxisSteps.Text), Int32.Parse(ZAxisSteps.Text));
                double X = comm.returnValue('X');
                double Y = comm.returnValue('Y');
                double Z = comm.returnValue('Z');
                StringBuilder k = new StringBuilder();
                k.Append('G');
                k.Append(comm.returnValue('G'));
                if (X != 1234.56789)
                {
                    k.Append('X');
                    k.Append(X + double.Parse(XPosText.Text));
                }
                if (Y != 1234.56789)
                {
                    k.Append('Y');
                    k.Append(Y + double.Parse(YPosText.Text));
                }
                if (Z != 1234.56789)
                {
                    k.Append('Z');
                    k.Append(Z + double.Parse(ZPosText.Text));
                }
                C.Fill(k.ToString());
                comm = C;
            }
            

            return comm;
        }
    }
    
}
