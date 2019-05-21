using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.ServiceModel;

namespace Common
{
    [DataContract]
    public class Error
    {
        private string err;
        [DataMember]
        public string Err
        {
            get { return err; }
            set { err = value; }
        }
        public Error(string e) { this.err = e; }
    }
}
