using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Threading;
using System.Net;

namespace TCP_Client
{
    class Program
    {
        static void Main(string[] args)
        {

            Socket clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP);
            /*clientSocket.Connect("127.0.0.1", 1024); // próba połączenia
            if(clientSocket.Connected)
             clientSocket.Send(ASCIIEncoding.ASCII.GetBytes("Hello world!"));*/
            for (int i = 0;i<=10;i++)
            {
            Console.WriteLine(i.ToString() + ":" + "huj");
            Thread.Sleep(100);
            }

            Console.Read();
        }
    }
}
