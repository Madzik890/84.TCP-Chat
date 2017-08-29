using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vector
{
    public struct vector2
    {
        public vector2(int x = 0, int y = 0) { this.x = x; this.y = y; }//constructor who assigns all variable with default method
        public int x;
        public int y;

        static public vector2 operator +(vector2 x, vector2 y) { return new vector2(x.x + y.x, x.y + y.y); }//adding operator
        static public vector2 operator -(vector2 x, vector2 y) { return new vector2(x.x - y.x, x.y - y.y); }//subtracting operator
        static public vector2 operator /(vector2 x, vector2 y) { return new vector2(x.x / y.x, x.y / y.y); }//dividing operator
        static public vector2 operator *(vector2 x, vector2 y) { return new vector2(x.x * y.x, x.y * y.y); }//multiplying operator
    }

}
