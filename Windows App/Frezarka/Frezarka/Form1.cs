using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Frezarka
{
    public partial class Form1 : Form
    {
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
    }




}
