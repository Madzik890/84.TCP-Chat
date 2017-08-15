using System;//lib for c# standart
using TCP_NET;//client class

namespace TCP_Client
{
    class Program
    {
        static int port = 1024;
        static string ip = "127.0.0.1";
        static string nickname = "default_nick";

        static void Main(string[] args)
        {
            Console.WriteLine("Write ip of server:");
            ip = Console.ReadLine();
            Console.WriteLine("Write your nickname:");
            nickname = Console.ReadLine();
            
            Client client = new Client();
            client.TryConnect(ip, nickname, port);

            while(client.connected)
            {
                client.netWork();
            }
            Console.Read();
        }
    }
}
