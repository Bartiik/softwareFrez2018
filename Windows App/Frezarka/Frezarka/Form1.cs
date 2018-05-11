using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Frezarka
{
    public partial class Form1 : Form
    {
        public List<Command> AllCommands = new List<Command>();
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
            if(openFileDialog1.ShowDialog()==DialogResult.OK)
            {
                Stream myStream = null;
                
                try
                {
                    if ((myStream = openFileDialog1.OpenFile()) != null)
                    {
                        OpenedGCodesList.Items.Add(openFileDialog1.FileName);
                        using (myStream)
                        {
                            StreamReader stream = new StreamReader(myStream);
                            while(!stream.EndOfStream)
                            {
                                Command temp = new Command();
                                temp.Fill(stream.ReadLine());
                                temp.ParentFile = openFileDialog1.FileName;
                                AllCommands.Add(temp);
                            }
                        }
                    }
                    
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: Could not read file from disk. Original error: " + ex.Message);
                }
            }
            
        }

        private void SpeedBar_Scroll(object sender, EventArgs e)
        {
            SpeedText.Text = SpeedBar.Value.ToString();
        }

        private void SpeedText_TextChanged(object sender, EventArgs e)
        {

            int value;
            if (Int32.TryParse(SpeedText.Text, out value))
            {
                if (value > 255) SpeedBar.Value = 255;
                else if (value > 0) SpeedBar.Value = value;
                else SpeedBar.Value = 0;
            }
            else SpeedBar.Value = 0;




        }

        private void PortListCombo_Enter(object sender, EventArgs e)
        {
            PortListCombo.Items.Clear();
            PortListCombo.Items.AddRange(SerialPort.GetPortNames());
        }

        private void ConnectButton_Click(object sender, EventArgs e)
        {
            if(ConnectButton.Tag.ToString() == "0")
            {
                ConnectButton.Tag = "1";
                ConnectButton.Text = "Close Port";
                serialPort.BaudRate = 115200;
                serialPort.PortName = PortListCombo.SelectedItem.ToString();
                serialPort.Open();
                if(serialPort.IsOpen)
                {
                    OpenPortLabel.Text = serialPort.PortName;
                }
                DisableEnable(true);
            }
            else
            {
                ConnectButton.Tag = "0";
                ConnectButton.Text = "Open Port";
                serialPort.Close();
                DisableEnable(false);
            }
        }

        private void CommandSendButton_Click(object sender, EventArgs e)
        {
            String gcode = customGText.Text;
            Command temp = new Command();
            if (temp.Fill(gcode))
            {
                addToCommunicationBox(true, temp);
                customGText.Clear();
                sendCommand(temp);
            }
            else MessageBox.Show("Something went Wrong");
        }
        void sendCommand(Command comm)
        {
            if(serialPort.IsOpen)
            {
                serialPort.WriteLine(comm.ToSend());
            }
        }
        void DisableEnable(bool e)
        {
            //BeginButton.Enabled = e;
            //PauseButton.Enabled = e;
            //StopButton.Enabled = e;
            //Z1plus.Enabled = e;
            //Z2plus.Enabled = e;
            //Z3plus.Enabled = e;
            //Z4plus.Enabled = e;
            //Z1minus.Enabled = e;
            //Z2minus.Enabled = e;
            //Z3minus.Enabled = e;
            //Z4minus.Enabled = e;
            //Y1plus.Enabled = e;
            //Y2plus.Enabled = e;
            //Y3plus.Enabled = e;
            //Y4plus.Enabled = e;
            //Y1minus.Enabled = e;
            //Y2minus.Enabled = e;
            //Y3minus.Enabled = e;
            //Y4minus.Enabled = e;
            //X1plus.Enabled = e;
            //X2plus.Enabled = e;
            //X3plus.Enabled = e;
            //X4plus.Enabled = e;
            //X1minus.Enabled = e;
            //X2minus.Enabled = e;
            //X3minus.Enabled = e;
            //X4minus.Enabled = e;
            //HomeAllButton.Enabled = e;
            //HomeX.Enabled = e;
            //HomeY.Enabled = e;
            //HomeZ.Enabled = e;
            //BoardHoldButton.Enabled = e;
            //TableFlipButton.Enabled = e;
            //SpeedBar.Enabled = e;
            //SpeedText.Enabled = e;
            //SetSpeedButton.Enabled = e;
            CommandSendButton.Enabled = e;
            customGText.Enabled = e;
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
            if(messageToArduino)
            {
                k.Append(" <<<< ");
            }
            else
            {
                k.Append(" >>>> ");
            }
            k.Append(C.ToString());
            //CommunicationBox.Items.Add(k.ToString());
            CommunicationBox.Invoke((MethodInvoker)delegate {
                CommunicationBox.Items.Add(k.ToString() );
            });
        }
        
    
        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Command temp = new Command();
            String msg = serialPort.ReadLine();
            String State;
            int state;
            if(Int32.TryParse(msg,out state))
            {
                State = state.ToString();
            }
            else
            {
                State = "ERROR";
            }
            MillingMachineStateLabel.Invoke((MethodInvoker)delegate {
                MillingMachineStateLabel.Text = State;
            });
            msg.Remove(0, 1);
            if(temp.Fill(msg))
                addToCommunicationBox(false, temp);
        }
    }
    



}
