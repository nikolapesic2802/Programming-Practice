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
    public class Magacin
    {
        private int idStavke;
        private int idArtikla;
        private int kolicina;
        private int cena;
        private DateTime vremeIDatum;
        [DataMember]
        public int IdStavke
        {
            get { return idStavke; }
            set { idStavke = value; }
        }
        [DataMember]
        public int IdArtikla
        {
            get { return idArtikla; }
            set { idArtikla = value; }
        }
        [DataMember]
        public int Kolicina
        {
            get { return kolicina; }
            set { kolicina = value; }
        }
        [DataMember]
        public int Cena
        {
            get { return cena; }
            set { cena = value; }
        }
        [DataMember]
        public DateTime VremeIDatum
        {
            get { return vremeIDatum; }
            set { vremeIDatum = value; }
        }
        public Magacin(int idS,int idA,int k,int c,DateTime v)
        {
            idStavke = idS;
            idArtikla = idA;
            kolicina = k;
            cena = c;
            vremeIDatum = v;
        }
    }
}
