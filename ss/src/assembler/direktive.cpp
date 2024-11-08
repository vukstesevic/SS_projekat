#include "../../inc/assembler/direktive.hpp"
#include "../../inc/assembler/kod.hpp"
#include "../../inc/assembler/assembler.hpp"

Kod direktiva_SKIP(Linija L)
{
  Kod kod;
  kod.sekcija = trenutnaSekcija;
  kod.tip = Skip;
  kod.brojLinije = L.broj;
  kod.brojNula = L.podaci.dir.unija.broj;
  kod.OC = 0b0000;
  kod.MOD = 0b0000;
  kod.RegA = 0b0000;
  kod.RegB = 0b0000;
  kod.RegC = 0b0000;
  kod.Disp = 0b000000000000;
  return kod;
}

void direktiva_WORD(Linija L, std::vector<Kod> &kodovi)
{
  int broj = L.podaci.dir.unija.operandi.broj;
  for (int i = 0; i < broj; i++)
  {
    Kod kod;
    kod.sekcija = trenutnaSekcija;
    kod.brojLinije = L.broj;
    kod.OC = 0b0000;
    kod.MOD = 0b0000;
    kod.RegA = 0b0000;
    kod.RegB = 0b0000;
    kod.RegC = 0b0000;
    kod.Disp = 0b000000000000;
    if (L.podaci.dir.unija.operandi.operandi[i].tip == SIMBOL)
    {
      kod.tip = Word_s;
      kodovi.push_back(kod);
      ElementRelokacionaTabela etb;
    
      etb.pomeraj = LC;
      etb.simbol = L.podaci.ins.operand.simb;
      etb.sekcija = trenutnaSekcija;
      relokacionaTabela.push_back(etb);
    }
    else
    {
      kod.tip = Word_l;
      kod.lit = L.podaci.dir.unija.operandi.operandi[i].lit;
      kodovi.push_back(kod);
    }
    LC += 4;
  }
}

 Kod direktiva_ASCII(Linija L)
  {
    Kod kod;
    kod.sekcija = trenutnaSekcija;
    kod.tip = Ascii;
    kod.brojLinije = L.broj;
    kod.ascii=L.podaci.dir.unija.simb;
    kod.OC = 0b0000;
    kod.MOD = 0b0000;
    kod.RegA = 0b0000;
    kod.RegB = 0b0000;
    kod.RegC = 0b0000;
    return kod;
  }