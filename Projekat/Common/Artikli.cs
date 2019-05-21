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
    public class Artikli
    {
        private int idArtikla;
        private string naziv;
        private string jedinicaMere;
        [DataMember]
        public int IdArtikla
        {
            get { return idArtikla; }
            set { idArtikla = value; }
        }
        [DataMember]
        public string Naziv
        {
            get { return naziv; }
            set { naziv = value; }
        }
        [DataMember]
        public string JedinicaMere
        {
            get { return jedinicaMere; }
            set { jedinicaMere = value; }
        }
        public Artikli(int id,string n,string j)
        {
            idArtikla = id;
            naziv = n;
            jedinicaMere = j;
        }
    }
}
