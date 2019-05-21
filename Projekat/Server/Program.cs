using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Runtime.Serialization;
using System.ServiceModel;
using Common;

namespace Server
{
    class Program
    {
        public static string sqlString = "Data Source = localhost"+Convert.ToString(Convert.ToChar(92))+"SQLEXPRESS;\nInitial Catalog = master;\nUser ID=user;\nPassword=user;";
        static void Main(string[] args)
        {
            var serviceHost = new ServiceHost(typeof(Service));
            serviceHost.AddServiceEndpoint(typeof(Interface), new NetTcpBinding(), "net.tcp://localhost:8000/");
            serviceHost.Open();
            Console.WriteLine("Server radi na portu 8000");
            /*
             Server=localhost\SQLEXPRESS;Database=master;Trusted_Connection=True;
            */
        }
    }
}
