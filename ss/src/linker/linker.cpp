#include "../../inc/linker/linker.hpp"
#include <vector>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdint>
#include <bitset>
using namespace std;

std::vector<Fajlovi> ucitani;
std::vector<sekcija> sekcije;
std::vector<simbol> definisani;
std::vector<simbol> nedefinisani;
std::vector<zaPlace> placeovi;
bool opcijaHex = false;
bool opcijaReloc = false;

int redniBroj = 0;
uint32_t baza = 0;

std::string readHexString(std::ifstream &ulaz, int numChars)
{
  char buffer[5];
  ulaz.read(buffer, numChars);
  buffer[numChars] = '\0';
  return std::string(buffer);
}

int readHexInt(std::ifstream &ulaz, int numChars)
{
  std::string hexStr = readHexString(ulaz, numChars);
  unsigned int result;
  std::stringstream ss;
  ss << std::hex << hexStr;
  ss >> result;
  return result;
}

void ucitavanje(char *naziv)
{
  std::ifstream ulaz(naziv);
  if (!ulaz.is_open())
  {
    std::cerr << "Greška pri otvaranju ulaznog fajla!" << std::endl;
    return;
  }

  Fajlovi fajlovi;
  fajlovi.rBr = redniBroj++;

  char hexa[5];
  hexa[4] = '\0';

  ulaz.read(hexa, 4);

  unsigned int brojSekcija;
  std::stringstream ss;
  ss << std::hex << hexa;
  ss >> brojSekcija;

  for (int i = 0; i < (int)brojSekcija; ++i)
  {
    tabelaSekcija ts;
    ts.redniBr = readHexInt(ulaz, 4);
    ts.naziv = "";
    char ch;
    while ((ch = readHexInt(ulaz, 2)) != 0)
    {
      ts.naziv += static_cast<char>(ch);
    }
    ts.velicina = readHexInt(ulaz, 4);
    fajlovi.tabelaSek.push_back(ts);
  }

  int brojSimbola = readHexInt(ulaz, 4);

  for (int i = 0; i < brojSimbola; ++i)
  {
    tabelaSimbola simbol;
    readHexInt(ulaz, 4);
    simbol.naziv = "";
    char ch;
    while ((ch = readHexInt(ulaz, 2)) != 0)
    {
      simbol.naziv += static_cast<char>(ch);
    }
    simbol.vrednost = readHexInt(ulaz, 4);
    simbol.velicina = readHexInt(ulaz, 4);
    simbol.pripadnostSekciji = readHexInt(ulaz, 4);
    simbol.globalan = readHexInt(ulaz, 4);
    simbol.eksteran = readHexInt(ulaz, 4);
    fajlovi.tabelaSimb.push_back(simbol);
  }

  for (int k = 0; k < (int)fajlovi.tabelaSek.size(); k++)
  {
    Fajl fajl;
    fajl.kod = "";
    int brojRelok = readHexInt(ulaz, 4);
    for (int i = 0; i < brojRelok; i++)
    {
      relokacioniUlaz ru;
      ru.pomeraj = readHexInt(ulaz, 4);
      ru.simbol = "";
      char ch;
      while ((ch = readHexInt(ulaz, 2)) != 0)
      {
        ru.simbol += static_cast<char>(ch);
      }
      fajl.relok.push_back(ru);
    }
    for (int l = 0; l < fajlovi.tabelaSek[k].velicina; l++)
    {
      fajl.kod += readHexString(ulaz, 2);
    }
    fajlovi.sekcije.push_back(fajl);
  }

  ucitani.push_back(fajlovi);
  ulaz.close();
  return;
}

void ispis(vector<sekcija> &sek, const char *naziv)
{
  ofstream izlaz;
  izlaz.open(naziv);
  if (!izlaz.is_open())
  {
    cerr << "Greška pri otvaranju izlaznog fajla!" << endl;
    return;
  }

  if (opcijaHex)
  {
    for (sekcija &s : sekcije)
    {
      int baza = s.baza;
      for (int i = 0; i < (int)s.kod.size();)
      {
        izlaz << hex << setw(8) << setfill('0') << baza << ": ";
        if (i + 15 < (int)s.kod.size())
          izlaz << s.kod[i + 6] << s.kod[i + 7] << " " << s.kod[i + 4] << s.kod[i + 5] << " " << s.kod[i + 2] << s.kod[i + 3] << " " << s.kod[i] << s.kod[i + 1] << " " << s.kod[i + 14] << s.kod[i + 15] << " " << s.kod[i + 12] << s.kod[i + 13] << " " << s.kod[i + 10] << s.kod[i + 11] << " " << s.kod[i + 8] << s.kod[i + 9] << endl;
        else
          izlaz << s.kod[i + 6] << s.kod[i + 7] << " " << s.kod[i + 4] << s.kod[i + 5] << " " << s.kod[i + 2] << s.kod[i + 3] << " " << s.kod[i] << s.kod[i + 1] << endl;
        baza += 8;
        i += 16;
      }
    }
  }
  else if (opcijaReloc)
  {
    izlaz << hex << setw(4) << setfill('0') << sekcije.size();
    int i = 1;
    for (sekcija &s : sekcije)
    {
      izlaz << hex << setw(4) << setfill('0') << i++;
      for (char c : s.naziv)
      {
        izlaz << hex << setw(2) << setfill('0') << (int)c;
      }
      izlaz << hex << setw(2) << setfill('0') << "00";
      izlaz << hex << setw(4) << setfill('0') << (s.velicina & 0xFFFF);
    }
    izlaz << hex << setw(4) << setfill('0') << definisani.size();
    i = 0;
    for (simbol sim : definisani)
    {
      izlaz << hex << setw(4) << setfill('0') << i++;
      for (char c : sim.naziv)
      {
        izlaz << hex << setw(2) << setfill('0') << (int)c;
      }
      izlaz << hex << setw(2) << setfill('0') << "00";
      izlaz << hex << setw(4) << setfill('0') << (sim.vrednost & 0xFFFF);
      izlaz << hex << setw(4) << setfill('0') << "0000";
      int p = 0;
      for (simbol sek : definisani)
      {
        if (sim.pripadnostSekciji == sek.naziv)
          {izlaz << hex << setw(4) << setfill('0') << p;
          break;
          }
          p++;
      }
      izlaz << hex << setw(4) << setfill('0') << "0000";
      izlaz << hex << setw(4) << setfill('0') << "0000";
    }
  
    for (sekcija &s : sekcije)
    {
      izlaz << hex << setw(4) << setfill('0') << s.relokacije.size();
      for (elementRelokacionaTabela ert : s.relokacije)
      {
        izlaz << hex << setw(4) << setfill('0') << ert.pomeraj;
        for (char c : ert.simbol)
        {
          izlaz << hex << setw(2) << setfill('0') << (int)c;
        }
        izlaz << hex << setw(2) << setfill('0') << "00";
      }
      izlaz << hex << setw(4) << setfill('0') << s.kod;
    }
  }
  izlaz.close();
}

int main(int argc, char *argv[])
{
  cout << "\nDOBRODOŠLI U LINKER\n";
  const char *izlazniFajl = "";

  for (int i = 1; i < argc; i++)
  {
    char *opcija = argv[i];
    if (strcmp(opcija, "-o") == 0)
    {
      izlazniFajl = argv[++i];
      cout << izlazniFajl << "\n";
    }
    else if (strcmp(opcija, "-hex") == 0)
    {
      opcijaHex = true;
      opcijaReloc = false;
    }
    else if (strncmp(opcija, "-place", 6) == 0)
    {
      std::string str = argv[i];
      str = str.substr(7);
      int pos = str.find('@');
      zaPlace plc;
      plc.naziv = str.substr(0, pos);
      std::string num = str.substr(pos + 1);
      plc.adresa = strtol(num.substr(2).c_str(), NULL, 16);
      placeovi.push_back(plc);
    }
    else if (strcmp(opcija, "-relocatable") == 0)
    {
      opcijaHex = false;
      opcijaReloc = true;
    }
    else
    {
      ucitavanje(argv[i]);
    }
  }

  for (int i = 0; i < (int)ucitani.size(); i++)
  {
    for (int k = 0; k < (int)ucitani[i].tabelaSek.size(); k++)
    {
      bool post = true;
      for (int j = 0; j < (int)sekcije.size(); j++)
      {
        if (sekcije[j].naziv == ucitani[i].tabelaSek[k].naziv)
        {
          post = false;
          sekcije[j].velicina += ucitani[i].tabelaSek[k].velicina;
          sekcije[j].kod += ucitani[i].sekcije[ucitani[i].tabelaSek[k].redniBr - 1].kod;
          for (int c = 0; c < (int)ucitani[i].sekcije[ucitani[i].tabelaSek[k].redniBr - 1].relok.size(); c++)
          {
            elementRelokacionaTabela ert;
            ert.baza = 0;
            ert.pomeraj = ucitani[i].sekcije[ucitani[i].tabelaSek[k].redniBr - 1].relok[c].pomeraj;
            ert.simbol = ucitani[i].sekcije[ucitani[i].tabelaSek[k].redniBr - 1].relok[c].simbol;
            ert.brFajla = i;
            sekcije[j].relokacije.push_back(ert);
          }
        }
      }
      if (post)
      {
        sekcija sekcija;
        sekcija.baza = 0;
        sekcija.velicina = ucitani[i].tabelaSek[k].velicina;
        sekcija.naziv = ucitani[i].tabelaSek[k].naziv;
        sekcija.kod = ucitani[i].sekcije[ucitani[i].tabelaSek[k].redniBr - 1].kod;
        for (int c = 0; c < (int)ucitani[i].sekcije[ucitani[i].tabelaSek[k].redniBr - 1].relok.size(); c++)
        {
          elementRelokacionaTabela ert;
          ert.baza = 0;
          ert.pomeraj = ucitani[i].sekcije[ucitani[i].tabelaSek[k].redniBr - 1].relok[c].pomeraj;
          ert.simbol = ucitani[i].sekcije[ucitani[i].tabelaSek[k].redniBr - 1].relok[c].simbol;
          ert.brFajla = i;
          sekcija.relokacije.push_back(ert);
        }
        sekcije.push_back(sekcija);
      }
    }
  }

  if (!opcijaReloc)
  {
    for (int j = 0; j < (int)sekcije.size(); j++)
    {
      for (zaPlace el : placeovi)
      {
        if (el.naziv == sekcije[j].naziv)
        {
          sekcije[j].baza = el.adresa;
          if (el.adresa > baza)
          { 
            baza = el.adresa + sekcije[j].velicina + sekcije[j].relokacije.size() * 4;
            if (baza % 8 != 0)
              baza += 4;
          }
        }
      }
    }
    std::sort(sekcije.begin(), sekcije.end(), [](const sekcija &a, const sekcija &b)
              { return a.baza < b.baza; });

    for (sekcija &sek : sekcije)
    {
      if (sek.baza == 0)
      {
        sek.baza = baza;
        baza = baza + sek.velicina + sek.relokacije.size() * 4;
        while (baza % 8 != 0)
        {
          baza += 1;
        };
      }
    }

    std::sort(sekcije.begin(), sekcije.end(), [](const sekcija &a, const sekcija &b)
              { return a.baza < b.baza; });
    for (int i = 0; i < (int)sekcije.size(); i++)
    {
      if (i != (int)sekcije.size() - 1)
      {
        if (sekcije[i].baza + sekcije[i].velicina > sekcije[i + 1].baza)
        {
          cout << "GREŠKA U LINKERU PREKLAPAJU SE SEKCIJE";
          exit(-1);
        }
      }
    }
  }

  for (Fajlovi &fa : ucitani)
  {
    for (tabelaSimbola &simb : fa.tabelaSimb)
    {
      if (simb.eksteran == true)
      {
        bool dodaj = true;
        simbol simbad;
        simbad.baza = 0;
        simbad.brFajla = fa.rBr;
        simbad.naziv = simb.naziv;
        simbad.pripadnostSekciji = fa.tabelaSimb[simb.pripadnostSekciji].naziv;
        simbad.vrednost = simb.vrednost;
        for (simbol &ss : nedefinisani)
        {
          if (simbad.naziv == ss.naziv)
          {
            dodaj = false;
          }
        }
        for (simbol &ss : definisani)
        {
          if (simbad.naziv == ss.naziv)
          {
            dodaj = false;
          }
        }
        if (dodaj)
          nedefinisani.push_back(simbad);
      }
      else if (simb.naziv != "UND" && simb.eksteran == false)
      {
        simbol simbad;
        simbad.baza = 0;
        simbad.brFajla = fa.rBr;
        simbad.naziv = simb.naziv;
        simbad.pripadnostSekciji = fa.tabelaSimb[simb.pripadnostSekciji].naziv;
        simbad.vrednost = simb.vrednost;
        for (simbol &ss : nedefinisani)
        {
          if (simbad.naziv == ss.naziv)
          {
            std::string naziv = simbad.naziv;
            nedefinisani.erase(
                std::remove_if(nedefinisani.begin(), nedefinisani.end(), [naziv](const simbol &s)
                               { return s.naziv == naziv; }),
                nedefinisani.end());
          }
        }
        for (simbol &ss : definisani)
        {
          if (simbad.naziv == ss.naziv && simb.vrednost != 65535 )
          {
            cout << simbad.naziv << "\n";
            cout << "LINKER GREŠKA DVOSTRUKA DEFINICIJA SIMBOLA!";
            exit(-1);
          }
        }
        bool bio=true;
        for (simbol &ss : definisani)
        {
          if (simbad.naziv == ss.naziv && simb.vrednost == 65535 )
          {
            bio=false;
          }
        }
        if(bio)definisani.push_back(simbad);
      }
    }
  }
  if (nedefinisani.size() > 0)
  {
    for (auto simb : nedefinisani)
    {
      cout << simb.naziv << " ";
    }
    cout << "LINKER GREŠKA NEDEFINISAN SIMBOL!";
    exit(-1);
  }
  for (simbol &simb : definisani)
  {
    for (sekcija &sek : sekcije)
    {
      if (sek.naziv == simb.pripadnostSekciji)
      {
        simb.baza = sek.baza;
        break;
      }
    }
    for (int i = 0; i < simb.brFajla; i++)
    {
      for (int j = 0; j < (int)ucitani[i].tabelaSek.size(); j++)
      {
        if (ucitani[i].tabelaSek[j].naziv == simb.pripadnostSekciji)
        {
          simb.vrednost += ucitani[i].tabelaSek[j].velicina;
        }
      }
    }
  }

  for (sekcija &sek : sekcije)
  {
    for (elementRelokacionaTabela &ert : sek.relokacije)
    {
      ert.baza = sek.baza;
      for (int i = 0; i < ert.brFajla; i++)
      {
        for (int j = 0; j < (int)ucitani[i].tabelaSek.size(); j++)
        {
          if (ucitani[i].tabelaSek[j].naziv == sek.naziv)
          {
            ert.pomeraj += ucitani[i].tabelaSek[j].velicina;
          }
        }
      }
    }
  }

  if (opcijaReloc)
  {
    ispis(sekcije, izlazniFajl);
  }
  else if (opcijaHex)
  {
    for (sekcija &sek : sekcije)
    {
      for (elementRelokacionaTabela &ert : sek.relokacije)
      {
        uint32_t lokacija = ert.pomeraj + ert.baza;
        int vrednost = 0;
        for (simbol &simb : definisani)
        {
          if (simb.naziv == ert.simbol)
          {
            vrednost = simb.vrednost + simb.baza;
          }
        }
        //cout<<"Vrednost: "<<hex<<vrednost<<" "<<hex<<"lokacija: "<<hex<<lokacija<<endl;
        if (vrednost > -2048 && vrednost < 2047)
        {
          vrednost &= 0xFFF;
          std::stringstream ss;
          ss << std::hex << std::setw(3) << std::setfill('0') << vrednost;
          std::string hexVrednost = ss.str();
          sek.kod.replace((lokacija - sek.baza) * 2 + 5, 3, hexVrednost);
        }
        else
        {
          std::stringstream ss;
          ss << std::hex << std::setw(8) << std::setfill('0') << vrednost;
          std::string hexVrednost = ss.str();
          sek.kod += hexVrednost;

          vrednost = (sek.baza + sek.velicina) - (ert.baza + ert.pomeraj) - 4;
          vrednost &= 0xFFF;
          std::stringstream pp;
          pp << std::hex << std::setw(3) << std::setfill('0') << vrednost;
          std::string hexVrednostpom = pp.str();
          sek.kod.replace((lokacija - sek.baza) * 2 + 5, 3, hexVrednostpom);
          sek.velicina += 4;
        }
      }
    }
    ispis(sekcije, izlazniFajl);
  }
}
