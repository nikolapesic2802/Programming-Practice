using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.ServiceModel;

namespace Common
{
    [ServiceContract]
    public interface Interface
    {
        [OperationContract]
        [FaultContract(typeof(Error))]
        Artikli GetArtikli(int id);

        [OperationContract]
        [FaultContract(typeof(Error))]
        void PostArtikli(Artikli artikli);

        [OperationContract]
        [FaultContract(typeof(Error))]
        void PutArtikli(Artikli artikli);

        [OperationContract]
        [FaultContract(typeof(Error))]
        void DeleteArtikli(int id);

        [OperationContract]
        [FaultContract(typeof(Error))]
        FiskalniRacun GetFiskalniRacun(int id);

        [OperationContract]
        [FaultContract(typeof(Error))]
        void PostFiskalniRacun(FiskalniRacun fiskalniRacun);

        [OperationContract]
        [FaultContract(typeof(Error))]
        void PutFiskalniRacun(FiskalniRacun fiskalniRacun);

        [OperationContract]
        [FaultContract(typeof(Error))]
        void DeleteFiskalniRacun(int id);

        [OperationContract]
        [FaultContract(typeof(Error))]
        Magacin GetMagacin(int id);

        [OperationContract]
        [FaultContract(typeof(Error))]
        void PostMagacin(Magacin magacin);

        [OperationContract]
        [FaultContract(typeof(Error))]
        void PutMagacin(Magacin magacin);

        [OperationContract]
        [FaultContract(typeof(Error))]
        void DeleteMagacin(int id);
    }
}
