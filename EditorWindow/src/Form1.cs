using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EditorWindow
{
    public partial class Form1 : Form
    {
        src.MemMap memmap;
        public Form1()
        {
            memmap = new src.MemMap();
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            memmap.OpenMemMap();
        }
    }
}
