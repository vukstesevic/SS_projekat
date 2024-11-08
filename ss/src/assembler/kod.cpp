#include "../../inc/assembler/kod.hpp"
#include "../../inc/assembler/assembler.hpp"
#include <cstring>
#include <iostream>
#include <bitset>
using namespace std;

int broj = 0;

void bekpecuj(std::vector<Kod> &kodovi)
{
  for (int i = 0; i < (int)(bek.size()); i++)
  {
    if (bek[i].bazen)
    {
      int sekcija = bek[i].sekcija;
      int br = bek[i].brojLinije;
      int pom = 0;
      for (int i = 0; i < (int)(bazenLiterala.size()); i++)
      {
        if (bazenLiterala[i].sekcija == sekcija)
        {
          if (bazenLiterala[i].brojLinije != br)
            pom += 4;
          else
            break;
        }
      }
      int velicinaSekcije = tabelaSimbola[sekcija].velicina;
      for (int j = 0; j < (int)(kodovi.size()); j++)
      {
        if (kodovi[j].brojLinije == br)
        {
          kodovi[j].Disp = pom + velicinaSekcije - bek[i].pomeraj - 4;
          break;
        }
      }
      tabelaSimbola[bek[i].sekcija].velicina += 4;
    }
    else
    {
      bool nepostoji = true;
      int vrednost = 0;
      for (int j = 0; j < (int)(tabelaSimbola.size()); j++)
      {
        if (strcmp(tabelaSimbola[j].naziv, bek[i].simbol) == 0)
        {
          vrednost = tabelaSimbola[j].vrednost;
          nepostoji = false;
          break;
        }
      }
      if (nepostoji)
      {
        cout << "Greška, simbol " << bek[i].simbol << " nije definisan! \n";
        exit(-1);
      }
      if (vrednost == -1)
      {
        ElementRelokacionaTabela ert;
        ert.sekcija = bek[i].sekcija;
        ert.pomeraj = bek[i].pomeraj;
        ert.simbol = bek[i].simbol;
        relokacionaTabela.push_back(ert);
        return;
      }
      for (int j = 0; j < (int)(kodovi.size()); j++)
      {
        if (kodovi[j].brojLinije == bek[i].brojLinije)
        {
          kodovi[j].Disp = (vrednost - kodovi[j].pomeraj - 4) & 0xFFF;
          break;
        }
      }
    }
  }
  for (int j = 0; j < (int)(tabelaSimbola.size()); j++)
  {
    if (tabelaSimbola[j].vrednost == -1 && tabelaSimbola[j].globalan == true)
    {
      tabelaSimbola[j].eksteran = true;
      tabelaSimbola[j].globalan = false;
    }
  }
}

int izlazniFajl(char *naziv, std::vector<Kod> &kodovi)
{
  ofstream izlaz;
  izlaz.open(naziv);
  if (!izlaz.is_open())
  {
    cerr << "Greška pri otvaranju izlaznog fajla!" << endl;
    return -1;
  }

  vector<tabelaSekcija> sekcije;
  for (int j = 1; j < (int)(tabelaSimbola.size()); j++)
  {
    if (tabelaSimbola[j].pripadnostSekciji == j)
    {
      tabelaSekcija tbl;
      tbl.redniBr = ++broj;
      tbl.naziv = tabelaSimbola[j].naziv;
      tbl.velicina = tabelaSimbola[j].velicina;
      sekcije.push_back(tbl);
    }
  }
  izlaz << hex << setw(4) << setfill('0') << sekcije.size();

  for (int j = 0; j < (int)(sekcije.size()); j++)
  {
    izlaz << hex << setw(4) << setfill('0') << sekcije[j].redniBr;
    for (int i = 0; sekcije[j].naziv[i] != '\0'; i++)
    {
      izlaz << hex << setw(2) << setfill('0') << (int)sekcije[j].naziv[i];
    }
    izlaz << hex << setw(2) << setfill('0') << "00";
    izlaz << hex << setw(4) << setfill('0') << sekcije[j].velicina;
  }

  izlaz << hex << setw(4) << setfill('0') << tabelaSimbola.size();

  for (int j = 0; j < (int)(tabelaSimbola.size()); j++)
  {
    izlaz << hex << setw(4) << setfill('0') << tabelaSimbola[j].redniBr;
    for (int i = 0; tabelaSimbola[j].naziv[i] != '\0'; i++)
    {
      izlaz << hex << setw(2) << setfill('0') << (int)tabelaSimbola[j].naziv[i];
    }
    izlaz << hex << setw(2) << setfill('0') << "00";
    izlaz << hex << setw(4) << setfill('0') << (tabelaSimbola[j].vrednost & 0xFFFF);
    izlaz << hex << setw(4) << setfill('0') << (tabelaSimbola[j].velicina & 0xFFFF);
    izlaz << hex << setw(4) << setfill('0') << tabelaSimbola[j].pripadnostSekciji;
    izlaz << hex << setw(4) << setfill('0') << tabelaSimbola[j].globalan;
    izlaz << hex << setw(4) << setfill('0') << tabelaSimbola[j].eksteran;
  }

  for (int j = 0; j < (int)(sekcije.size()); j++)
  {
    int brojRelok = 0;
    for (int k = 0; k < (int)relokacionaTabela.size(); k++)
    {
      if (strcmp(sekcije[j].naziv, tabelaSimbola[relokacionaTabela[k].sekcija].naziv) == 0)
      {
        brojRelok += 1;
      }
    }

    izlaz << hex << setw(4) << setfill('0') << brojRelok;

    for (int k = 0; k < (int)relokacionaTabela.size(); k++)
    {
      if (strcmp(sekcije[j].naziv, tabelaSimbola[relokacionaTabela[k].sekcija].naziv) == 0)
      {
        izlaz << hex << setw(4) << setfill('0') << relokacionaTabela[k].pomeraj;
        for (int i = 0; relokacionaTabela[k].simbol[i] != '\0'; i++)
        {
          izlaz << hex << setw(2) << setfill('0') << (int)relokacionaTabela[k].simbol[i];
        }
        izlaz << hex << setw(2) << setfill('0') << "00";
      }
    }

    for (int k = 0; k < (int)kodovi.size(); k++)
    {
      if (strcmp(sekcije[j].naziv, tabelaSimbola[kodovi[k].sekcija].naziv) == 0)
      {
        if (kodovi[k].tip == Instr)
          izlaz << hex << (int)kodovi[k].OC << hex << (int)kodovi[k].MOD << hex << (int)kodovi[k].RegA << hex << (int)kodovi[k].RegB << hex << (int)kodovi[k].RegC << hex << setw(3) << setfill('0') << (kodovi[k].Disp & 0xFFF);
        else if (kodovi[k].tip == Skip)
        {
          for (int p = 0; p < kodovi[k].brojNula; p++)
          {
            izlaz << hex << setw(2) << setfill('0') << "00";
          }
        }
        else if (kodovi[k].tip == Word_l)
        {
          izlaz << hex << setw(8) << setfill('0') << kodovi[k].lit;
        }
        else if (kodovi[k].tip == Word_s)
        {
          izlaz << hex << setw(8) << setfill('0') << "00000000";
        }
        else if (kodovi[k].tip == Ascii)
        {
          int duzina = strlen(kodovi[k].ascii);
          for (int m = 0; m < duzina; m += 4)
          {
            unsigned char cetiriBajta[4] = {0, 0, 0, 0}; 
           
            for (int n = 0; n < 4 && (m + n) < duzina; n++)
            {
              cetiriBajta[n] = kodovi[k].ascii[m + n]; 
            }

            
            for (int q = 3; q >= 0; q--)
            {
              izlaz << std::hex << std::setw(2) << std::setfill('0') << (int)cetiriBajta[q];
            }
          }
        }
      }
    }

    for (int k = 0; k < (int)bazenLiterala.size(); k++)
    {
      if (strcmp(sekcije[j].naziv, tabelaSimbola[bazenLiterala[k].sekcija].naziv) == 0)
      {
        izlaz << hex << setw(8) << setfill('0') << bazenLiterala[k].literal;
      }
    }
  }

  izlaz.close();

  return 0;
}
