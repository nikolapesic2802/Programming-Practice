using System;
using System.Collections.Generic;
using System.Linq;
using System.Data;
using System.Data.SqlClient;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.ServiceModel;
using Common;

namespace Server
{
    [ServiceContract]
    public class Service : Interface
    {
        public Artikli GetArtikli(int id)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var select = new SqlCommand($"SELECT * FROM ARTIKLI WHERE ID = {id};", connection);
                var a = new SqlDataAdapter(select);
                a.Fill(dataSet, "Altikli");
                var b = dataSet.Tables["Artikli"].Select()[0];
                return new Artikli(Convert.ToInt32(b["id"]), Convert.ToString(b["naziv"]), Convert.ToString(b["jedinicaMere"]));
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public void PostArtikli(Artikli ar)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var insert = new SqlCommand($"INSERT INTO ARTIKLI(id,naziv,jedinicaMere) VALUES ({ar.IdArtikla},{ar.Naziv},{ar.JedinicaMere});",connection);
                var a = new SqlDataAdapter(insert);
                insert.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public void PutArtikli(Artikli ar)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var update = new SqlCommand($"UPDATE ARTIKLI SET naziv ={ar.Naziv}, jedinicaMere = {ar.JedinicaMere} WHERE id = {ar.IdArtikla};", connection);
                update.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public void DeleteArtikli(int id)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var update = new SqlCommand($"DELETE FROM ARTIKLI WHERE id = {id};", connection);
                update.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public FiskalniRacun GetFiskalniRacun(int id)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var select = new SqlCommand($"SELECT * FROM FISKALNI_RACUN WHERE ID = {id};", connection);
                var a = new SqlDataAdapter(select);
                a.Fill(dataSet, "FiskalniRacun");
                var b = dataSet.Tables["FiskalniRacun"].Select()[0];
                return new FiskalniRacun(Convert.ToInt32(b["id"]), Convert.ToInt32(b["idStavke"]), Convert.ToDateTime(b["vremeIDatum"]), Convert.ToInt32(b["kolicina"]));
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public void PostFiskalniRacun(FiskalniRacun ar)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var insert = new SqlCommand($"INSERT INTO FISKALNI_RACUN(id,idStavke,vremeIDatum,kolicina) VALUES ({ar.IdFiskalnog},{ar.IdStavke},{ar.VremeIDatum},{ar.Kolicina});", connection);
                var a = new SqlDataAdapter(insert);
                insert.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public void PutFiskalniRacun(FiskalniRacun ar)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var update = new SqlCommand($"UPDATE FISKALNI_RACUN SET idStavke ={ar.IdStavke}, vremeIDatum = {ar.VremeIDatum}, kolicina = {ar.Kolicina} WHERE id = {ar.IdFiskalnog};", connection);
                update.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public void DeleteFiskalniRacun(int id)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var update = new SqlCommand($"DELETE FROM FISKALNI_RACUN WHERE id = {id};", connection);
                update.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public Magacin GetMagacin(int id)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var select = new SqlCommand($"SELECT * FROM MAGACIN WHERE ID = {id};", connection);
                var a = new SqlDataAdapter(select);
                a.Fill(dataSet, "Magacin");
                var b = dataSet.Tables["Magacin"].Select()[0];
                return new Magacin(Convert.ToInt32(b["id"]), Convert.ToInt32(b["idArtikla"]), Convert.ToInt32(b["kolicina"]), Convert.ToInt32(b["cena"]), Convert.ToDateTime(b["vremeIDatum"]));
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public void PostMagacin(Magacin ar)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var insert = new SqlCommand($"INSERT INTO MAGACIN(id,idArtikla,kolicina,cena,vremeIDatum) VALUES ({ar.IdArtikla},{ar.IdStavke},{ar.Kolicina},{ar.Cena},{ar.VremeIDatum});", connection);
                var a = new SqlDataAdapter(insert);
                insert.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public void PutMagacin(Magacin ar)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var update = new SqlCommand($"UPDATE MAGACIN SET idArtikla ={ar.IdStavke}, kolicina = {ar.Kolicina}, cena = {ar.Cena}, vremeIDatum = {ar.VremeIDatum} WHERE id = {ar.IdArtikla};", connection);
                update.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
        public void DeleteMagacin(int id)
        {
            try
            {
                var dataSet = new DataSet();
                var connection = new SqlConnection(Program.sqlString);
                connection.Open();
                var update = new SqlCommand($"DELETE FROM MAGACIN WHERE id = {id};", connection);
                update.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                throw new FaultException<Error>(new Error(e.Message));
            }
        }
    }
}
