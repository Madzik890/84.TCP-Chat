using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using Vector;

namespace Analog
{
    public class Clock
    {
        public Clock()
        {
            leads.Add(new Lead(new vector2(100,200),new vector2(100,100),Color.Chartreuse,3));
          /*  leads.Add(new Lead());
            leads.Add(new Lead());*/
        }

        public List<Lead> leads = new List<Lead>();

        public virtual void Draw(object sender, PaintEventArgs e)
        {
            foreach (Lead value in leads)
            {
                Pen pen = new Pen(value.Color, value.thickness);
                // Create points that define line.
                Point point1 = new Point(value.Begin.x, value.Begin.y);
                Point point2 = new Point(value.End.x, value.End.y);

                // Draw line to screen.
                e.Graphics.DrawLine(pen, point1, point2);
            }
        }
        public virtual void Recentry(Size size)//function which center the clock in window
        {
            foreach(Lead value in leads)
            {
                value.Begin = new vector2(size.Width/2, size.Height/2);
            }
        }   
        public class Lead//hands of the clock
        {
            public Lead() { }//default constructor
            public Lead(vector2 begin, vector2 end, Color color, float thickness)
            {
                this.begin = begin; this.end = end; this.color = color; this.thickness = thickness;
            }

            public vector2 Begin { set { this.begin = value; } get { return begin; } }
            public vector2 End { set { this.end = value; } get { return end; } }
            public Color Color { set { this.color = value; } get { return color; } }
            public float thickness = 3;


            private Color color = new Color();
            private vector2 begin = new vector2(100, 200);
            private vector2 end = new vector2(100, 100);
        }
    }
}
