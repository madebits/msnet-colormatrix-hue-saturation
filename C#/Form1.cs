using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.Windows.Forms;

namespace QM
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                if (this.openFileDialog.ShowDialog(this) == DialogResult.Cancel)
                {
                    return;
                }
                OpenImage(this.openFileDialog.FileName);
            }
            catch(Exception ex)
            {
                MessageBox.Show(this, ex.Message, "Error");
            }
        }

        private Bitmap bmp = null;
        private void OpenImage(string file)
        {
            bmp = new Bitmap(file);
            this.pictureBox.Image = bmp;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void UpdateImage()
        {
            if (bmp == null) return;
            // quick test code, do not copy paste in real apps
            this.Text = "H: " + trHue.Value.ToString()
                + " S: " + (trSat.Value / 100.0f).ToString("0.0")
                + " B: " + (trBri.Value / 100.0f).ToString("0.0");
            Bitmap b = null;
            if (chkUseGdi.Checked)
            {
                ImageAttributes imageAttr = new ImageAttributes();
                Img.QColorMatrix qm = new Img.QColorMatrix();
                qm.RotateHue(trHue.Value);
                qm.SetSaturation2(trSat.Value / 100.0f);
                qm.SetBrightness(trBri.Value / 100.0f);
                imageAttr.SetColorMatrix(qm.ToColorMatrix());
                b = new Bitmap(bmp.Width, bmp.Height);
                using (Graphics g = Graphics.FromImage(b))
                {
                    Rectangle r = new Rectangle(0, 0, bmp.Width, bmp.Height);
                    g.DrawImage(bmp, r, 0, 0, bmp.Width, bmp.Height, GraphicsUnit.Pixel, imageAttr);
                }
            }
            else
            {
                b = (Bitmap)bmp.Clone();
                Img.QColorMatrix qm = new Img.QColorMatrix();
                qm.RotateHue(trHue.Value);
                qm.SetSaturation2(trSat.Value / 100.0f);
                qm.SetBrightness(trBri.Value / 100.0f);
                for (int i = 0; i < b.Width; i++)
                {
                    for (int j = 0; j < b.Height; j++)
                    {
                        Color c = b.GetPixel(i, j);
                        c = Img.QColorMatrix.Vector2Color(qm.TransformVector(Img.QColorMatrix.Color2Vector(c), true));
                        b.SetPixel(i, j, c);
                    }
                }
            }
            if (b != null)
            {
                this.pictureBox.Image = b;
            }
        }

        private void trHue_ValueChanged(object sender, EventArgs e)
        {
            UpdateImage();
        }

        private void trSat_ValueChanged(object sender, EventArgs e)
        {
            UpdateImage();
        }

        private void trBri_ValueChanged(object sender, EventArgs e)
        {
            UpdateImage();
        }

        private void trHue_Scroll(object sender, EventArgs e)
        {
            //UpdateImage();
        }

        private void trSat_Scroll(object sender, EventArgs e)
        {
            //UpdateImage();
        }

        private void trBri_Scroll(object sender, EventArgs e)
        {
            //UpdateImage();
        }

    }
}
