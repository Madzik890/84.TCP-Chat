using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;

namespace TCP_NET
{
    interface TCP_Client
    {
        bool TryConnect();//trying connect to server | if bool is true checking other ports
        bool TryConnect(string ip, string nickname, int port);
        void netWork();//main loop
    }

    class Client : TCP_Client
    {
        private int port = 1045;//default port
        private string ip = "127.0.0.1";//internal computer ip
        private string nickname = "default_nick";//default nickname
        private string message = "";//string for message
        private TcpClient client = new TcpClient();
        private NetworkStream nwStream;

        public Client(string ip, string nickname, int port) { this.ip = ip; this.nickname = nickname; this.port = port; }
        public Client() { }//default constructor
        ~Client() { client.Close(); nwStream.Close(); }
                                                        //operation on
        public string server_ip { set { ip = value; } get { return ip; } }//string of ip
        public string nick { set { nickname = value; } get { return nickname; } }//string of nick
        public int server_port { set { port = value; } get { return port; } }//int of port
        public bool connected { get { return client.Connected; } }//returning status of connected
        public bool TryConnect()//trying connect to server
        {
            client.Connect(ip, port);//trying connect to server
            if(client.Connected)
            {
                nwStream = client.GetStream();
                SendNickname(nickname);
                ClearCurrentConsoleLine();
                Console.Write("Your message:");
                return true;//returning result
            }
            else
            return false;//returning result
        }
        public bool TryConnect(string ip, string nickname, int port)
        {
            client.Connect(ip, port);//trying connect to server
            if (client.Connected)
            {
                nwStream = client.GetStream();
                SendNickname(nickname);
                ClearCurrentConsoleLine();
                Console.Write("Your message:");
                return true;//returning result
            }
            else
                return false;//returning result
        }
        public void netWork()//main network function
        {
            while (Console.KeyAvailable)//while key is available loop start
            {
                var key = Console.ReadKey(true);//get actual key
                switch (key.Key)//switch for keyboard controls
                {
                    case ConsoleKey.Enter:
                        byte[] bytesToSend = ASCIIEncoding.ASCII.GetBytes(message);//encoding message to ascii
                        nwStream.Write(bytesToSend, 0, bytesToSend.Length);//sending a message to server
                        ClearCurrentConsoleLine();//clearing a line for message
                        Console.WriteLine("You:" + message + " | " + DateTime.Now.ToLongTimeString());
                        message = "";//clearing a string
                        Console.Write("Your message:" + message);//drawing type message
                        break;

                    case ConsoleKey.Backspace://if backspace was pressed
                        if (message.Length > 0)
                        {
                            message = message.Remove(message.Length - 1);//remove last char from string
                            ClearCurrentConsoleLine();//clearing actual line
                            Console.Write("Your message:" + message);//drawing this key
                        }
                        break;

                    default://if key was pressed
                        message += key.KeyChar;
                        Console.Write(key.KeyChar);
                        break;
                }
            }

            if (nwStream.DataAvailable == true)//if nwStream received any data
            {
                byte[] bytesToRead = new byte[client.ReceiveBufferSize];//creating data buffer
                int bytesRead = nwStream.Read(bytesToRead, 0, client.ReceiveBufferSize);//reading data from buffer
                ClearCurrentConsoleLine();
                Console.WriteLine(Encoding.ASCII.GetString(bytesToRead, 0, bytesRead) + " | " + DateTime.Now.ToLongTimeString());//Writing data
                Console.Write("Your message:" + message);
            }
        }
        static public void ClearCurrentConsoleLine()//clearing actual console line
        {
            int currentLineCursor = System.Console.CursorTop;
            System.Console.SetCursorPosition(0, System.Console.CursorTop);
            System.Console.Write(new string(' ', System.Console.WindowWidth));
            System.Console.SetCursorPosition(0, currentLineCursor);
        }

        private void SendNickname(string nickname)
        {
            byte[] bytesToSend = ASCIIEncoding.ASCII.GetBytes("$#@!set_nick:" + nickname);//encoding nickname to ascii
            nwStream.Write(bytesToSend, 0, bytesToSend.Length);//sending nick to server
        }
    }

}
