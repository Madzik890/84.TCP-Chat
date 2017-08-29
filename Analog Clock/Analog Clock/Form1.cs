using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Analog;

namespace Analog_Clock
{
    public partial class Form1 : Form
    {
        private Clock clock = new Clock();

        public Form1()
        {
            InitializeComponent();
        }

        private void Display(object sender, PaintEventArgs e)
        {
            clock.Draw(sender, e);
        }
    }
}
