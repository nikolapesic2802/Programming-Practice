using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Common;

namespace Projekat
{
    public class meni
    {
        public static void Init(Interface i)
        {
            int input = 0;
            while(input != 4)
            {
                Console.Write("1)Artikli\n2)FiskalniRacun\n3)Magacin\n4)Izlaz\n");
                input = Convert.ToInt32(Console.ReadLine());
                if (input == 1)
                {
                    int input2 = 0;
                    while(input2 != 5)
                    {
                        Console.Write("1)Ispis Artikla\n2)Dodaj Artikal\n3)Izmeni Artikal\n4)Obrisi Artikal\n5)Izlaz\n");
                        input2 = Convert.ToInt32(Console.ReadLine());
                        if(input2==1)
                        {
                            int id;
                            id= Convert.ToInt32(Console.ReadLine());
                            Artikli a = i.GetArtikli(id);
                            Console.WriteLine(a);
                        }
                        if(input2==2)
                        {
                            int id;
                            string naz, jed;
                            id = Convert.ToInt32(Console.ReadLine());
                            naz = Convert.ToString(Console.ReadLine());
                            jed = Convert.ToString(Console.ReadLine());
                            Artikli a=new Artikli(id, naz, jed);
                            i.PostArtikli(a);
                        }
                        if(input2==3)
                        {
                            int id;
                            string naz, jed;
                            id = Convert.ToInt32(Console.ReadLine());
                            naz = Convert.ToString(Console.ReadLine());
                            jed = Convert.ToString(Console.ReadLine());
                            Artikli a = new Artikli(id, naz, jed);
                            i.PutArtikli(a);
                        }
                        if (input2 == 4)
                        {
                            int id;
                            id = Convert.ToInt32(Console.ReadLine());
                            i.DeleteArtikli(id);
                        }
                    }
                }
                if (input == 2)
                {
                    int input2 = 0;
                    while (input2 != 5)
                    {
                        Console.Write("1)Ispis Fiskalnog Racuna\n2)Dodaj Fiskalni Racun\n3)Izmeni Fiskalni Racun\n4)Obrisi Fiskalni Racun\n5)Izlaz\n");
                        input2 = Convert.ToInt32(Console.ReadLine());
                        if (input2 == 1)
                        {
                            int id;
                            id = Convert.ToInt32(Console.ReadLine());
                            FiskalniRacun a = i.GetFiskalniRacun(id);
                            Console.WriteLine(a);
                        }
                        if (input2 == 2)
                        {
                            int id, idStavke, kolicina;
                            DateTime vreme;
                            id = Convert.ToInt32(Console.ReadLine());
                            idStavke = Convert.ToInt32(Console.ReadLine());
                            vreme = Convert.ToDateTime(Console.ReadLine());
                            kolicina = Convert.ToInt32(Console.ReadLine());
                            FiskalniRacun a = new FiskalniRacun(id, idStavke,vreme,kolicina);
                            i.PostFiskalniRacun(a);
                        }
                        if (input2 == 3)
                        {
                            int id, idStavke, kolicina;
                            DateTime vreme;
                            id = Convert.ToInt32(Console.ReadLine());
                            idStavke = Convert.ToInt32(Console.ReadLine());
                            vreme = Convert.ToDateTime(Console.ReadLine());
                            kolicina = Convert.ToInt32(Console.ReadLine());
                            FiskalniRacun a = new FiskalniRacun(id, idStavke, vreme, kolicina);
                            i.PutFiskalniRacun(a);
                        }
                        if (input2 == 4)
                        {
                            int id;
                            id = Convert.ToInt32(Console.ReadLine());
                            i.DeleteFiskalniRacun(id);
                        }
                    }
                }
                if (input == 3)
                {
                    int input2 = 0;
                    while (input2 != 4)
                    {
                        Console.Write("1)Ispis Magacina\n2)Dodaj Magacin\n3)Izmeni Magacin\n4)Obrisi Magacin\n5)Izlaz\n");
                        input2 = Convert.ToInt32(Console.ReadLine());
                        if (input2 == 1)
                        {
                            int id;
                            id = Convert.ToInt32(Console.ReadLine());
                            Magacin a = i.GetMagacin(id);
                            Console.WriteLine(a);
                        }
                        if (input2 == 2)
                        {
                            int id,idArtikla,kolicina,cena;
                            DateTime vreme;
                            id = Convert.ToInt32(Console.ReadLine());
                            idArtikla = Convert.ToInt32(Console.ReadLine());
                            kolicina = Convert.ToInt32(Console.ReadLine());
                            cena = Convert.ToInt32(Console.ReadLine());
                            vreme = Convert.ToDateTime(Console.ReadLine());
                            Magacin a = new Magacin(id,idArtikla,kolicina,cena,vreme);
                            i.PostMagacin(a);
                        }
                        if (input2 == 3)
                        {
                            int id, idArtikla, kolicina, cena;
                            DateTime vreme;
                            id = Convert.ToInt32(Console.ReadLine());
                            idArtikla = Convert.ToInt32(Console.ReadLine());
                            kolicina = Convert.ToInt32(Console.ReadLine());
                            cena = Convert.ToInt32(Console.ReadLine());
                            vreme = Convert.ToDateTime(Console.ReadLine());
                            Magacin a = new Magacin(id, idArtikla, kolicina, cena, vreme);
                            i.PutMagacin(a);
                        }
                        if (input2 == 4)
                        {
                            int id;
                            id = Convert.ToInt32(Console.ReadLine());
                            i.DeleteMagacin(id);
                        }
                    }
                }
            }
        }
    }
}
