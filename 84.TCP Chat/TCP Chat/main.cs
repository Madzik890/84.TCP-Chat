using System;//lib for c# standart
using System.Threading;
using System.Runtime.InteropServices;
using TCP_NET;//client class


namespace TCP_Client
{
    class Program
    {
        static int port = 1024;
        static string ip = "127.0.0.1";
        static string nickname = "default_nick";
        static Client client = new Client();//client

        static void Main(string[] args)
        {
            Console.WriteLine("Write ip of server:");
            ip = Console.ReadLine();
            Console.WriteLine("Write your nickname:");
            nickname = Console.ReadLine();
            Console.Clear();

            client.TryConnect(ip, nickname, port);

            handler = new ConsoleEventDelegate(ConsoleEventCallback);
            SetConsoleCtrlHandler(handler, true);

            while (client.connected)
            {
                client.netWork();
            }
            client.Disconnect();
            Console.Read();
        }

        static bool ConsoleEventCallback(int eventType)//checking whether program isn't closing
        {
            if (eventType == 2)//if is 
            {
                client.Disconnect();//client disconnecting from the server
            }
            return false;
        }
        static ConsoleEventDelegate handler;   // Keeps it from getting garbage collected
                                               
        private delegate bool ConsoleEventDelegate(int eventType);
        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool SetConsoleCtrlHandler(ConsoleEventDelegate callback, bool add);
    }
}
