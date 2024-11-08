#include "../../parser.tab.hpp"
#include "../../inc/strukture.hpp"
#include "../../inc/assembler/assembler.hpp"
#include "../../inc/assembler/instrukcije.hpp"
#include "../../inc/assembler/direktive.hpp"
#include "../../inc/assembler/kod.hpp"
#include <vector>
#include <cstring>
#include <iostream>
#include <bitset>

using namespace std;
extern FILE *yyin;

int LC = 0;
int trenutnaSekcija = 0;
int redniBroj = 0;

vector<TabelaSimbola> tabelaSimbola;
vector<ElementRelokacionaTabela> relokacionaTabela;
vector<ElementBazenLiterala> bazenLiterala;
vector<bekpecing> bek;

int main(int argc, char *argv[])
{

  vector<Kod> kodovi;
  vector<Linija> linije;

  FILE *file = fopen(argv[3], "r");
  yyin = file;
  yyparse(linije);

  TabelaSimbola und;
  und.globalan = false;
  und.redniBr = redniBroj++;
  und.pripadnostSekciji = und.redniBr;
  und.naziv = "UND";
  und.velicina = 0;
  und.vrednost = 0;
  und.globalan = false;
  und.eksteran = false;
  trenutnaSekcija = und.redniBr;
  tabelaSimbola.push_back(und);

  for (int i = 0; i < (int)(linije.size()); i++)
  {
    if (linije[i].labela != nullptr)
    {
      bool napravljena = false;
      char *labela = linije[i].labela;
      for (int j = 0; j < (int)(tabelaSimbola.size()); j++)
      {
        if (strcmp(labela, tabelaSimbola[j].naziv) == 0 && tabelaSimbola[j].vrednost != -1)
        {
          cout << "Greška na liniji " << linije[i].broj << " labela " << labela << " već postoji!";
          exit(-1);
        }
        else if (strcmp(labela, tabelaSimbola[j].naziv) == 0 && tabelaSimbola[j].vrednost == -1)
        {
          tabelaSimbola[j].vrednost = LC;
          tabelaSimbola[j].pripadnostSekciji = trenutnaSekcija;
          napravljena = true;
          break;
        }
      }
      if (!napravljena)
      {
        TabelaSimbola simbol;
        simbol.naziv = labela;
        simbol.redniBr = redniBroj++;
        simbol.globalan = false;
        simbol.eksteran = false;
        simbol.pripadnostSekciji = trenutnaSekcija;
        simbol.velicina = -1;
        simbol.vrednost = LC;
        tabelaSimbola.push_back(simbol);
      }
    }
    if (linije[i].tip == Linija_Direktiva)
    {

      if (linije[i].podaci.dir.tip == GLOBAL)
      {
        for (int j = 0; j < linije[i].podaci.dir.unija.operandi.broj; j++)
        {
          TabelaSimbola simb;
          simb.redniBr = redniBroj++;
          simb.velicina = 0;
          simb.vrednost = -1;
          simb.globalan = true;
          simb.eksteran = false;
          simb.pripadnostSekciji = 0;
          simb.naziv = (linije[i].podaci.dir.unija.operandi.operandi[j].simb);
          tabelaSimbola.push_back(simb);
        }
      }
      else if (linije[i].podaci.dir.tip == EXTERN)
      {
        for (int j = 0; j < linije[i].podaci.dir.unija.operandi.broj; j++)
        {
          TabelaSimbola simb;
          simb.redniBr = redniBroj++;
          simb.velicina = 0;
          simb.vrednost = -1;
          simb.globalan = true;
          simb.eksteran = true;
          simb.pripadnostSekciji = 0;
          simb.naziv = (linije[i].podaci.dir.unija.operandi.operandi[j].simb);
          tabelaSimbola.push_back(simb);
        }
      }
      else if (linije[i].podaci.dir.tip == SEKCIJA)
      {
        bool postoji = false;
        tabelaSimbola[trenutnaSekcija].velicina = LC;
        for (int j = 0; j < (int)(tabelaSimbola.size()); j++)
        {
          if (strcmp(linije[i].podaci.dir.unija.simb, tabelaSimbola[j].naziv) == 0)
          {
            LC = tabelaSimbola[j].velicina;
            postoji = true;
            break;
          }
        }
        if (!postoji)
        {
          TabelaSimbola simb;
          simb.redniBr = redniBroj++;
          simb.velicina = 0;
          simb.vrednost = -1;
          simb.globalan = false;
          simb.eksteran = false;
          simb.pripadnostSekciji = simb.redniBr;
          simb.naziv = linije[i].podaci.dir.unija.simb;
          tabelaSimbola.push_back(simb);
          trenutnaSekcija = simb.redniBr;
          LC = 0;
        }
      }
      else if (linije[i].podaci.dir.tip == WORD)
      {
        direktiva_WORD(linije[i], kodovi);
      }
      else if (linije[i].podaci.dir.tip == SKIP)
      {
        LC += linije[i].podaci.dir.unija.broj;
        kodovi.push_back(direktiva_SKIP(linije[i]));
      }
      else if (linije[i].podaci.dir.tip == ASCII)
      {
        kodovi.push_back(direktiva_ASCII(linije[i]));
        // LC+=4;
        for (int p = 0; linije[i].podaci.dir.unija.simb[p] != '\0'; p++)
        {
          LC += 1;
        }
        while (LC % 8 != 0)
        {
          LC += 1;
        }
      }
      else if (linije[i].podaci.dir.tip == END)
      {
        tabelaSimbola[trenutnaSekcija].velicina = LC;
        break;
      }
    }

    else if (linije[i].tip == Linija_Instrukcija)
    {
      switch (linije[i].podaci.ins.tip)
      {
      case HALT:
        kodovi.push_back(instrukcija_HALT(linije[i]));
        break;
      case INT:
        kodovi.push_back(instrukcija_INT(linije[i]));
        break;
      case IRET:
        instrukcija_IRET(kodovi);
        LC += 8;
        break;
      case RET:
        kodovi.push_back(instrukcija_RET());
        break;
      case CALL:
        kodovi.push_back(instrukcija_CALL(linije[i]));
        break;
      case JMP:
        kodovi.push_back(instrukcija_JMP(linije[i]));
        break;
      case BEQ:
        kodovi.push_back(instrukcija_BEQ(linije[i]));
        break;
      case BNE:
        kodovi.push_back(instrukcija_BNE(linije[i]));
        break;
      case BGT:
        kodovi.push_back(instrukcija_BGT(linije[i]));
        break;
      case PUSH:
        kodovi.push_back(instrukcija_PUSH(linije[i]));
        break;
      case POP:
        kodovi.push_back(instrukcija_POP(linije[i]));
        break;
      case NOT:
        kodovi.push_back(instrukcija_NOT(linije[i]));
        break;
      case XCHG:
        kodovi.push_back(instrukcija_XCHG(linije[i]));
        break;
      case ADD:
        kodovi.push_back(instrukcija_ADD(linije[i]));
        break;
      case SUB:
        kodovi.push_back(instrukcija_SUB(linije[i]));
        break;
      case MUL:
        kodovi.push_back(instrukcija_MUL(linije[i]));
        break;
      case DIV:
        kodovi.push_back(instrukcija_DIV(linije[i]));
        break;
      case AND:
        kodovi.push_back(instrukcija_AND(linije[i]));
        break;
      case OR:
        kodovi.push_back(instrukcija_OR(linije[i]));
        break;
      case XOR:
        kodovi.push_back(instrukcija_XOR(linije[i]));
        break;
      case SHL:
        kodovi.push_back(instrukcija_SHL(linije[i]));
        break;
      case SHR:
        kodovi.push_back(instrukcija_SHR(linije[i]));
        break;
      case LD:
        kodovi.push_back(instrukcija_LD(linije[i], kodovi));
        break;
      case ST:
        kodovi.push_back(instrukcija_ST(linije[i]));
        break;
      case CSRRD:
        kodovi.push_back(instrukcija_CSRRD(linije[i]));
        break;
      case CSRWR:
        kodovi.push_back(instrukcija_CSRWR(linije[i]));
        break;
      }
      LC += 4;
    }
  }

  bekpecuj(kodovi);

  izlazniFajl(argv[2], kodovi);

/*   for (int i = 0; i < (int)(tabelaSimbola.size()); i++)
  {
    cout << tabelaSimbola[i].redniBr << " " << tabelaSimbola[i].naziv << " Pripada: " << tabelaSimbola[i].pripadnostSekciji << " Veličina: " << tabelaSimbola[i].velicina << " Vrednost: " << tabelaSimbola[i].vrednost << " Eksteran: " << tabelaSimbola[i].eksteran << " Globalan: " << tabelaSimbola[i].globalan << "\n";
  } */

/*   for (int i = 0; i < (int)(kodovi.size()); i++)
  {
    cout << std::bitset<4>(kodovi[i].OC) << " " << std::bitset<4>(kodovi[i].MOD) << " " << std::bitset<4>(kodovi[i].RegA) << " " << std::bitset<4>(kodovi[i].RegB) << " " << std::bitset<4>(kodovi[i].RegC) << " " << std::bitset<12>(kodovi[i].Disp) << " " << kodovi[i].sekcija << "\n";
  } */
}