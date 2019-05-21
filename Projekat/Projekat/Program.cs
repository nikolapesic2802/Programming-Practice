using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.ServiceModel;
using Common;

namespace Projekat
{
    class Program
    {
        static void Main(string[] args)
        {
            var channelFactory = new ChannelFactory<Interface>(new NetTcpBinding(), new EndpointAddress("net.tcp://localhost:8000/"));
            var proxy = channelFactory.CreateChannel();
            meni.Init(proxy);
        }
    }
}
