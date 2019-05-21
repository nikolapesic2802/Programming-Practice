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
    public class FiskalniRacun
    {
        private int idFiskalnog;
        private int idStavke;
        private DateTime vremeIDatum;
        private int kolicina;
        [DataMember]
        public int IdFiskalnog
        {
            get { return idFiskalnog; }
            set { idFiskalnog = value; }
        }
        [DataMember]
        public int IdStavke
        {
            get { return idStavke; }
            set { idStavke = value; }
        }
        [DataMember]
        public DateTime VremeIDatum
        {
            get { return vremeIDatum; }
            set { vremeIDatum = value; }
        }
        [DataMember]
        public int Kolicina
        {
            get { return kolicina; }
            set { kolicina = value; }
        }
        public FiskalniRacun(int idFis,int idSta,DateTime v,int k)
        {
            idFiskalnog = idFis;
            idStavke = idSta;
            vremeIDatum = v;
            kolicina = k;
        }
    }
}
