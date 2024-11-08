#include "../../inc/assembler/instrukcije.hpp"
#include "../../inc/assembler/kod.hpp"
#include <cstring>
#include <iostream>
using namespace std;

Kod instrukcija_HALT(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0000;
  kod.MOD = 0b0000;
  kod.RegA = 0b0000;
  kod.RegB = 0b0000;
  kod.RegC = 0b0000;
  kod.Disp = 0b000000000000;
  return kod;
}
Kod instrukcija_INT(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0001;
  kod.MOD = 0b0000;
  kod.RegA = 0b0000;
  kod.RegB = 0b0000;
  kod.RegC = 0b0000;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_XCHG(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0100;
  kod.MOD = 0b0000;
  kod.RegA = 0b0000;
  int regB = L.podaci.ins.regD;
  int regC = L.podaci.ins.regS;
  kod.RegB = regB & 0x0F;
  kod.RegC = regC & 0x0F;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_ADD(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0101;
  kod.MOD = 0b0000;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegA = regD & 0x0F;
  kod.RegB = regD & 0x0F;
  kod.RegC = regS & 0x0F;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_SUB(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0101;
  kod.MOD = 0b0001;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegA = regD & 0x0F;
  kod.RegB = regD & 0x0F;
  kod.RegC = regS & 0x0F;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_MUL(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0101;
  kod.MOD = 0b0010;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegA = regD & 0x0F;
  kod.RegB = regD & 0x0F;
  kod.RegC = regS & 0x0F;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_DIV(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0101;
  kod.MOD = 0b0011;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegA = regD & 0x0F;
  kod.RegB = regD & 0x0F;
  kod.RegC = regS & 0x0F;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_NOT(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0110;
  kod.MOD = 0b0000;
  int regD = L.podaci.ins.regD;
  kod.RegA = regD & 0x0F;
  kod.RegB = regD & 0x0F;
  kod.RegC = 0b0000;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_AND(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0110;
  kod.MOD = 0b0001;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegA = regD & 0x0F;
  kod.RegB = regD & 0x0F;
  kod.RegC = regS & 0x0F;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_OR(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0110;
  kod.MOD = 0b0010;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegA = regD & 0x0F;
  kod.RegB = regD & 0x0F;
  kod.RegC = regS & 0x0F;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_XOR(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0110;
  kod.MOD = 0b0011;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegA = regD & 0x0F;
  kod.RegB = regD & 0x0F;
  kod.RegC = regS & 0x0F;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_SHL(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0111;
  kod.MOD = 0b0000;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegA = regD & 0x0F;
  kod.RegB = regD & 0x0F;
  kod.RegC = regS & 0x0F;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_SHR(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.brojNula = 0;
  kod.OC = 0b0111;
  kod.MOD = 0b0001;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegA = regD & 0x0F;
  kod.RegB = regD & 0x0F;
  kod.RegC = regS & 0x0F;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_JMP(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b0011;
  kod.RegB = 0b0000;
  kod.RegC = 0b0000;
  if (L.podaci.ins.operand.tip == LITERAL)
  {
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      kod.RegA = 0b1111;
      kod.MOD = 0b1000;
      kod.Disp = 0b000000000000;

      ElementBazenLiterala elem;
      elem.brojLinije = L.broj;
      elem.pomeraj = LC;
      elem.sekcija = trenutnaSekcija;
      elem.literal = L.podaci.ins.operand.lit;
      bazenLiterala.push_back(elem);

      bekpecing bpc;
      bpc.sekcija = trenutnaSekcija;
      bpc.pomeraj = LC;
      bpc.brojLinije = L.broj;
      bpc.bazen = true;
      bek.push_back(bpc);

      return kod;
    }
    else
    {
      kod.RegA = 0b0000;
      kod.MOD = 0b0000;
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
      return kod;
    }
  }
  else if (L.podaci.ins.operand.tip == SIMBOL)
  {
    for (int i = 0; i < (int)(tabelaSimbola.size()); i++)
    {
      if (strcmp(L.podaci.ins.operand.simb, tabelaSimbola[i].naziv) == 0)
      {
        if (tabelaSimbola[i].eksteran)
        {

          ElementRelokacionaTabela etb;
          etb.pomeraj = LC;
          etb.simbol = L.podaci.ins.operand.simb;
          etb.sekcija = trenutnaSekcija;
          relokacionaTabela.push_back(etb);

          kod.MOD = 0b1000;
          kod.RegA = 0b1111;
          kod.Disp = 0b000000000000;
          return kod;
        }
        else if (tabelaSimbola[i].pripadnostSekciji != trenutnaSekcija && tabelaSimbola[i].globalan == true)
        {
          bekpecing bpc;
          bpc.bazen = false;
          bpc.sekcija = trenutnaSekcija;
          bpc.pomeraj = LC;
          bpc.brojLinije = L.broj;
          bpc.simbol = L.podaci.ins.operand.simb;
          bek.push_back(bpc);
          kod.MOD = 0b0000;
          kod.RegA = 0b1111;
          kod.Disp = 0b000000000000;
          return kod;
        }
        else if (tabelaSimbola[i].pripadnostSekciji == trenutnaSekcija)
        {
          kod.MOD = 0b0000;
          kod.RegA = 0b1111;
          int pomeraj = tabelaSimbola[i].vrednost - LC - 4;
          kod.Disp = pomeraj & 0xFFF;
          return kod;
        }
      }
    }
    bekpecing bpc;
    bpc.bazen = false;
    bpc.sekcija = trenutnaSekcija;
    bpc.pomeraj = LC;
    bpc.brojLinije = L.broj;
    bpc.simbol = L.podaci.ins.operand.simb;
    bek.push_back(bpc);
    kod.MOD = 0b0000;
    kod.RegA = 0b1111;
    kod.Disp = 0b000000000000;
  }
  return kod;
}

Kod instrukcija_BEQ(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b0011;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegB = regS & 0x0F;
  kod.RegC = regD & 0x0F;

  if (L.podaci.ins.operand.tip == LITERAL)
  {
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      kod.RegA = 0b1111;
      kod.MOD = 0b1001;
      kod.Disp = 0b000000000000;

      ElementBazenLiterala elem;
      elem.brojLinije = L.broj;
      elem.pomeraj = LC;
      elem.sekcija = trenutnaSekcija;
      elem.literal = L.podaci.ins.operand.lit;
      bazenLiterala.push_back(elem);

      bekpecing bpc;
      bpc.bazen = true;
      bpc.pomeraj = LC;
      bpc.brojLinije = L.broj;
      bpc.sekcija = trenutnaSekcija;
      bek.push_back(bpc);
      return kod;
    }
    else
    {
      kod.RegA = 0b0000;
      kod.MOD = 0b0001;
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
      return kod;
    }
  }
  else if (L.podaci.ins.operand.tip == SIMBOL)
  {
    for (int i = 0; i < (int)(tabelaSimbola.size()); i++)
    {
      if (strcmp(L.podaci.ins.operand.simb, tabelaSimbola[i].naziv) == 0)
      {
        if (tabelaSimbola[i].eksteran)
        {
          ElementRelokacionaTabela etb;
          etb.pomeraj = LC;
          etb.simbol = L.podaci.ins.operand.simb;
          etb.sekcija = trenutnaSekcija;
          relokacionaTabela.push_back(etb);

          kod.MOD = 0b1001;
          kod.RegA = 0b1111;
          kod.Disp = 0b000000000000;
          return kod;
        }
        else if (tabelaSimbola[i].pripadnostSekciji != trenutnaSekcija && tabelaSimbola[i].globalan == true)
        {
          bekpecing bpc;
          bpc.bazen = false;
          bpc.sekcija = trenutnaSekcija;
          bpc.pomeraj = LC;
          bpc.brojLinije = L.broj;
          bpc.simbol = L.podaci.ins.operand.simb;
          bek.push_back(bpc);
          kod.MOD = 0b0000;
          kod.RegA = 0b1111;
          kod.Disp = 0b000000000000;
          return kod;
        }
        else if (tabelaSimbola[i].pripadnostSekciji == trenutnaSekcija)
        {
          kod.MOD = 0b0001;
          kod.RegA = 0b1111;
          int pomeraj = tabelaSimbola[i].vrednost - LC - 4;
          kod.Disp = pomeraj & 0xFFF;
          return kod;
        }
      }
    }
    bekpecing bpc;
    bpc.bazen = false;
    bpc.sekcija = trenutnaSekcija;
    bpc.pomeraj = LC;
    bpc.brojLinije = L.broj;
    bpc.simbol = L.podaci.ins.operand.simb;
    bek.push_back(bpc);
    kod.MOD = 0b0001;
    kod.RegA = 0b1111;
    kod.Disp = 0b000000000000;
  }
  return kod;
}

Kod instrukcija_BNE(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b0011;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegB = regS & 0x0F;
  kod.RegC = regD & 0x0F;

  if (L.podaci.ins.operand.tip == LITERAL)
  {
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      kod.RegA = 0b1111;
      kod.MOD = 0b1010;
      kod.Disp = 0b000000000000;

      ElementBazenLiterala elem;
      elem.brojLinije = L.broj;
      elem.pomeraj = LC;
      elem.sekcija = trenutnaSekcija;
      elem.literal = L.podaci.ins.operand.lit;
      bazenLiterala.push_back(elem);

      bekpecing bpc;
      bpc.sekcija = trenutnaSekcija;
      bpc.pomeraj = LC;
      bpc.brojLinije = L.broj;
      bpc.bazen = true;
      bek.push_back(bpc);
      return kod;
    }
    else
    {
      kod.RegA = 0b0000;
      kod.MOD = 0b0010;
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
      return kod;
    }
  }
  else if (L.podaci.ins.operand.tip == SIMBOL)
  {
    for (int i = 0; i < (int)(tabelaSimbola.size()); i++)
    {
      if (strcmp(L.podaci.ins.operand.simb, tabelaSimbola[i].naziv) == 0)
      {
        if (tabelaSimbola[i].eksteran)
        {
          ElementRelokacionaTabela etb;
          etb.pomeraj = LC;
          etb.simbol = L.podaci.ins.operand.simb;
          etb.sekcija = trenutnaSekcija;
          relokacionaTabela.push_back(etb);

          kod.MOD = 0b1010;
          kod.RegA = 0b1111;
          kod.Disp = 0b000000000000;
          return kod;
        }
        else if (tabelaSimbola[i].pripadnostSekciji != trenutnaSekcija && tabelaSimbola[i].globalan == true)
        {
          bekpecing bpc;
          bpc.bazen = false;
          bpc.sekcija = trenutnaSekcija;
          bpc.pomeraj = LC;
          bpc.brojLinije = L.broj;
          bpc.simbol = L.podaci.ins.operand.simb;
          bek.push_back(bpc);
          kod.MOD = 0b0000;
          kod.RegA = 0b1111;
          kod.Disp = 0b000000000000;
          return kod;
        }
        else if (tabelaSimbola[i].pripadnostSekciji == trenutnaSekcija)
        {
          kod.MOD = 0b0010;
          kod.RegA = 0b1111;
          int pomeraj = tabelaSimbola[i].vrednost - LC - 4;
          kod.Disp = pomeraj & 0xFFF;
          return kod;
        }
      }
    }
    bekpecing bpc;
    bpc.bazen = false;
    bpc.sekcija = trenutnaSekcija;
    bpc.pomeraj = LC;
    bpc.brojLinije = L.broj;
    bpc.simbol = L.podaci.ins.operand.simb;
    bek.push_back(bpc);
    kod.MOD = 0b0010;
    kod.RegA = 0b1111;
    kod.Disp = 0b000000000000;
  }
  return kod;
}

Kod instrukcija_BGT(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b0011;
  int regD = L.podaci.ins.regD;
  int regS = L.podaci.ins.regS;
  kod.RegA = 0b1111;
  kod.RegB = regS & 0x0F;
  kod.RegC = regD & 0x0F;

  if (L.podaci.ins.operand.tip == LITERAL)
  {
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      kod.RegA = 0b1111;
      kod.MOD = 0b1011;
      kod.Disp = 0b000000000000;

      ElementBazenLiterala elem;
      elem.brojLinije = L.broj;
      elem.pomeraj = LC;
      elem.sekcija = trenutnaSekcija;
      elem.literal = L.podaci.ins.operand.lit;
      bazenLiterala.push_back(elem);

      bekpecing bpc;
      bpc.sekcija = trenutnaSekcija;
      bpc.pomeraj = LC;
      bpc.brojLinije = L.broj;
      bpc.bazen = true;
      bek.push_back(bpc);
      return kod;
    }
    else
    {
      kod.RegA = 0b0000;
      kod.MOD = 0b0011;
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
      return kod;
    }
  }
  else if (L.podaci.ins.operand.tip == SIMBOL)
  {
    for (int i = 0; i < (int)(tabelaSimbola.size()); i++)
    {
      if (strcmp(L.podaci.ins.operand.simb, tabelaSimbola[i].naziv) == 0)
      {
        if (tabelaSimbola[i].eksteran)
        {
          ElementRelokacionaTabela etb;
          etb.pomeraj = LC;
          etb.simbol = L.podaci.ins.operand.simb;
          etb.sekcija = trenutnaSekcija;
          relokacionaTabela.push_back(etb);

          kod.MOD = 0b1011;
          kod.RegA = 0b1111;
          kod.Disp = 0b000000000000;
          return kod;
        }
        else if (tabelaSimbola[i].pripadnostSekciji != trenutnaSekcija && tabelaSimbola[i].globalan == true)
        {
          bekpecing bpc;
          bpc.bazen = false;
          bpc.sekcija = trenutnaSekcija;
          bpc.pomeraj = LC;
          bpc.brojLinije = L.broj;
          bpc.simbol = L.podaci.ins.operand.simb;
          bek.push_back(bpc);
          kod.MOD = 0b0000;
          kod.RegA = 0b1111;
          kod.Disp = 0b000000000000;
          return kod;
        }
        else if (tabelaSimbola[i].pripadnostSekciji == trenutnaSekcija)
        {
          kod.MOD = 0b0011;
          kod.RegA = 0b1111;

          int pomeraj = tabelaSimbola[i].vrednost - LC - 4;
          kod.Disp = pomeraj & 0xFFF;
          return kod;
        }
      }
    }
    bekpecing bpc;
    bpc.bazen = false;
    bpc.sekcija = trenutnaSekcija;
    bpc.pomeraj = LC;
    bpc.brojLinije = L.broj;
    bpc.simbol = L.podaci.ins.operand.simb;
    bek.push_back(bpc);
    kod.MOD = 0b0011;
    kod.RegA = 0b1111;
    kod.Disp = 0b000000000000;
  }
  return kod;
}

Kod instrukcija_CALL(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b0010;
  kod.RegB = 0b0000;
  kod.RegC = 0b0000;

  if (L.podaci.ins.operand.tip == LITERAL)
  {
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      kod.RegA = 0b1111;
      kod.MOD = 0b0001;
      kod.Disp = 0b000000000000;

      ElementBazenLiterala elem;
      elem.brojLinije = L.broj;
      elem.pomeraj = LC;
      elem.sekcija = trenutnaSekcija;
      elem.literal = L.podaci.ins.operand.lit;
      bazenLiterala.push_back(elem);

      bekpecing bpc;
      bpc.sekcija = trenutnaSekcija;
      bpc.pomeraj = LC;
      bpc.brojLinije = L.broj;
      bpc.bazen = true;
      bek.push_back(bpc);
      return kod;
    }
    else
    {
      kod.RegA = 0b0000;
      kod.MOD = 0b0000;
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
      return kod;
    }
  }
  else if (L.podaci.ins.operand.tip == SIMBOL)
  {
    for (int i = 0; i < (int)(tabelaSimbola.size()); i++)
    {
      if (strcmp(L.podaci.ins.operand.simb, tabelaSimbola[i].naziv) == 0)
      {
        if (tabelaSimbola[i].eksteran)
        {

          ElementRelokacionaTabela etb;
          etb.pomeraj = LC;
          etb.simbol = L.podaci.ins.operand.simb;
          etb.sekcija = trenutnaSekcija;
          relokacionaTabela.push_back(etb);

          kod.MOD = 0b0001;
          kod.RegA = 0b1111;
          kod.Disp = 0b000000000000;
          return kod;
        }
        else if (tabelaSimbola[i].pripadnostSekciji != trenutnaSekcija && tabelaSimbola[i].globalan == true)
        {
          bekpecing bpc;
          bpc.bazen = false;
          bpc.sekcija = trenutnaSekcija;
          bpc.pomeraj = LC;
          bpc.brojLinije = L.broj;
          bpc.simbol = L.podaci.ins.operand.simb;
          bek.push_back(bpc);
          kod.MOD = 0b0000;
          kod.RegA = 0b1111;
          kod.Disp = 0b000000000000;
          return kod;
        }
        else if (tabelaSimbola[i].pripadnostSekciji == trenutnaSekcija)
        {
          kod.MOD = 0b0000;
          kod.RegA = 0b1111;
          int pomeraj = tabelaSimbola[i].vrednost - LC - 4;
          kod.Disp = pomeraj & 0xFFF;
          return kod;
        }
      }
    }
    bekpecing bpc;
    bpc.bazen = false;
    bpc.sekcija = trenutnaSekcija;
    bpc.pomeraj = LC;
    bpc.brojLinije = L.broj;
    bpc.simbol = L.podaci.ins.operand.simb;
    bek.push_back(bpc);
    kod.MOD = 0b0000;
    kod.RegA = 0b1111;
    kod.Disp = 0b000000000000;
  }
  return kod;
}

Kod instrukcija_LD(Linija L, std::vector<Kod> &kodovi)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b1001;
  int reg = L.podaci.ins.regS;
  kod.RegA = reg & 0x0F;
  int regp;
  ElementBazenLiterala elem;
  bekpecing bpc;
  ElementRelokacionaTabela etb;
  bool bio = false;
  switch (L.podaci.ins.operand.mem)
  {
  case NEPOSREDNO_LITERAL:
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      kod.RegB = 0b1111;
      kod.RegC = 0b0000;
      kod.MOD = 0b0010;
      kod.Disp = 0b000000000000;

      elem.brojLinije = L.broj;
      elem.pomeraj = LC;
      elem.sekcija = trenutnaSekcija;
      elem.literal = L.podaci.ins.operand.lit;
      bazenLiterala.push_back(elem);

      bpc.bazen = true;
      bpc.sekcija = trenutnaSekcija;
      bpc.pomeraj = LC;
      bpc.brojLinije = L.broj;
      bek.push_back(bpc);
    }
    else
    {
      kod.RegB = 0b0000;
      kod.MOD = 0b0001;
      kod.RegC = 0b0000;
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
    }
    break;

  case NEPOSREDNO_SIMBOL:
    for (int i = 0; i < (int)tabelaSimbola.size(); i++)
    {
      if (strcmp(tabelaSimbola[i].naziv, L.podaci.ins.operand.simb) == 0)
      {
        bio = true;
        if (tabelaSimbola[i].pripadnostSekciji != trenutnaSekcija)
        {
          kod.MOD = 0b0010;
          break;
        }
        else
        {
          kod.MOD = 0b0001;
          break;
        }
      }
    }
    if (!bio)
      kod.MOD = 0b0010;
    kod.RegB = 0b1111;
    kod.RegC = 0b0000;
    kod.Disp = 0b000000000000;
    etb.pomeraj = LC;
    etb.simbol = L.podaci.ins.operand.simb;
    etb.sekcija = trenutnaSekcija;
    relokacionaTabela.push_back(etb);
    break;

  case DIREKTNO_MEMORIJSKO_LITERAL:
    kod.MOD = 0b0010;
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      kod.RegB = 0b1111;
      kod.RegC = 0b0000;
      kod.Disp = 0b000000000000;

      ElementBazenLiterala elem;
      elem.brojLinije = L.broj;
      elem.pomeraj = LC;
      elem.sekcija = trenutnaSekcija;
      elem.literal = L.podaci.ins.operand.lit;
      bazenLiterala.push_back(elem);

      bpc.sekcija = trenutnaSekcija;
      bpc.pomeraj = LC;
      bpc.brojLinije = L.broj;
      bpc.bazen = true;
      bek.push_back(bpc);
    }
    else
    {
      kod.RegB = 0b0000;
      kod.RegC = 0b0000;
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
    }
    break;

  case DIREKTNO_MEMORIJSKO_SIMBOL:
   /*  for (int i = 0; i < (int)tabelaSimbola.size(); i++)
    {
      if (strcmp(tabelaSimbola[i].naziv, L.podaci.ins.operand.simb) == 0)
      {
        bio = true;
        if (tabelaSimbola[i].pripadnostSekciji != trenutnaSekcija)
        { */
          Kod kod1;
          kod1.sekcija = trenutnaSekcija;
          kod1.pomeraj = LC;
          kod1.tip = Instr;
          kod1.OC = kod.OC;
          kod1.MOD = 0b0010;
          kod1.RegA = kod.RegA;
          kod1.RegB = 0b1111;
          kod1.RegC = 0b0000;
          kod1.Disp = 0b000000000000;
          kodovi.push_back(kod1);

          etb.pomeraj = LC;
          etb.simbol = L.podaci.ins.operand.simb;
          etb.sekcija = trenutnaSekcija;
          relokacionaTabela.push_back(etb);

          LC += 4;

          kod.MOD = 0b0010;
          kod.RegB = kod.RegA;
          kod.RegC = 0b0000;
          kod.Disp = 0b000000000000;
          break;
    /*     }
        else
        {
          kod.MOD = 0b0010;
          kod.RegB = kod.RegA;
          kod.RegC = 0b0000;
          kod.Disp = 0b000000000000;

          etb.pomeraj = LC;
          etb.simbol = L.podaci.ins.operand.simb;
          etb.sekcija = trenutnaSekcija;
          relokacionaTabela.push_back(etb);
          break;
        }
      }
    }
    if (!bio)
    {
      kod.MOD = 0b0010;
      kod.RegB = kod.RegA;
      kod.RegC = 0b0000;
      kod.Disp = 0b000000000000;

      etb.pomeraj = LC;
      etb.simbol = L.podaci.ins.operand.simb;
      etb.sekcija = trenutnaSekcija;
      relokacionaTabela.push_back(etb);
    }
    break; */

  case DIREKTNO_REGISTARSKO:
    kod.MOD = 0b0001;
    regp = L.podaci.ins.operand.reg;
    kod.RegB = regp & 0x0F;
    kod.RegC = 0b0000;
    kod.Disp = 0b000000000000;
    break;

  case INDIREKTNO_REGISTARSKO:
    kod.MOD = 0b0010;
    regp = L.podaci.ins.operand.reg;
    kod.RegB = regp & 0x0F;
    kod.RegC = 0b0000;
    kod.Disp = 0b000000000000;
    break;

  case INDIREKTNO_REGISTARSKO_SIMBOL:
    break;

  case INDIREKTNO_REGISTARSKO_LITERAL:
    kod.MOD = 0b0010;
    regp = L.podaci.ins.operand.reg;
    kod.RegB = regp & 0x0F;
    kod.RegC = 0b0000;
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      cout << "Greška u asembliranju";
      exit(-1);
    }
    else
    {
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
    }
    break;
  }
  return kod;
}

Kod instrukcija_ST(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b1000;
  int reg = L.podaci.ins.regS;
  kod.RegC = reg & 0x0F;
  int regp;
  ElementBazenLiterala elem;
  bekpecing bpc;
  ElementRelokacionaTabela etb;
  bool bio=false;
  switch (L.podaci.ins.operand.mem)
  {
  case NEPOSREDNO_LITERAL:
    kod.MOD = 0b0000;
    kod.RegB = 0b0000;
    kod.RegA = 0b0000;
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      kod.RegB = 0b1111;
      kod.MOD = 0b0000;
      kod.Disp = 0b000000000000;

      elem.brojLinije = L.broj;
      elem.pomeraj = LC;
      elem.sekcija = trenutnaSekcija;
      elem.literal = L.podaci.ins.operand.lit;
      bazenLiterala.push_back(elem);

      bpc.sekcija = trenutnaSekcija;
      bpc.pomeraj = LC;
      bpc.brojLinije = L.broj;
      bpc.bazen = true;
      bek.push_back(bpc);
    }
    else
    {
      kod.RegB = 0b0000;
      kod.MOD = 0b0000;
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
    }

    break;
  case NEPOSREDNO_SIMBOL:
    for (int i = 0; i < (int)tabelaSimbola.size(); i++)
    {
      if (strcmp(tabelaSimbola[i].naziv, L.podaci.ins.operand.simb) == 0)
      {
        bio=true;
        if (tabelaSimbola[i].pripadnostSekciji != trenutnaSekcija)
        {
          kod.MOD = 0b0010;
          break;
        }
        else
        {
          kod.MOD = 0b0000;
          break;
        }
      }
    }
    if(!bio)kod.MOD = 0b0000;
    kod.RegB = 0b0000;
    kod.RegA = 0b1111;
    etb.pomeraj = LC;
    etb.simbol = L.podaci.ins.operand.simb;
    etb.sekcija = trenutnaSekcija;
    relokacionaTabela.push_back(etb);
    kod.Disp = 0b000000000000;
    break;
  case DIREKTNO_MEMORIJSKO_LITERAL:
    kod.MOD = 0b0010;
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      kod.RegA = 0b1111;
      kod.RegB = 0b0000;
      kod.Disp = 0b000000000000;

      ElementBazenLiterala elem;
      elem.brojLinije = L.broj;
      elem.pomeraj = LC;
      elem.sekcija = trenutnaSekcija;
      elem.literal = L.podaci.ins.operand.lit;
      bazenLiterala.push_back(elem);

      bpc.sekcija = trenutnaSekcija;
      bpc.pomeraj = LC;
      bpc.brojLinije = L.broj;
      bpc.bazen = true;
      bek.push_back(bpc);
    }
    else
    {
      kod.RegA = 0b0000;
      kod.RegB = 0b0000;
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
    }
    break;
  case DIREKTNO_MEMORIJSKO_SIMBOL:
    for (int i = 0; i < (int)tabelaSimbola.size(); i++)
    {
      if (strcmp(tabelaSimbola[i].naziv, L.podaci.ins.operand.simb) == 0)
      {
        bio=true;
        if (tabelaSimbola[i].pripadnostSekciji != trenutnaSekcija)
        {
          kod.MOD = 0b0010;
          break;
        }
        else
        {
          kod.MOD = 0b0000;
          break;
        }
      }
    }
    if(!bio)kod.MOD=0b0000;
    kod.RegB = 0b0000;
    kod.RegA = 0b1111;
    kod.Disp = 0b000000000000;
    etb.pomeraj = LC;
    etb.simbol = L.podaci.ins.operand.simb;
    etb.sekcija = trenutnaSekcija;
    relokacionaTabela.push_back(etb);

    break;
  case DIREKTNO_REGISTARSKO:
    kod.MOD = 0b0000;
    regp = L.podaci.ins.operand.reg;
    kod.RegA = regp & 0x0F;
    kod.RegB = 0b0000;
    kod.Disp = 0b000000000000;
    break;
  case INDIREKTNO_REGISTARSKO:
    kod.MOD = 0b0000;
    regp = L.podaci.ins.operand.reg;
    kod.RegA = regp & 0x0F;
    kod.RegB = 0b0000;
    kod.Disp = 0b000000000000;
    break;

  case INDIREKTNO_REGISTARSKO_SIMBOL:
    break;

  case INDIREKTNO_REGISTARSKO_LITERAL:
    kod.MOD = 0b0010;
    regp = L.podaci.ins.operand.reg;
    kod.RegA = regp & 0x0F;
    kod.RegB = 0b0000;
    if (L.podaci.ins.operand.lit < -2048 || L.podaci.ins.operand.lit > 2047)
    {
      cout << "Greška u asembliranju";
      exit(-1);
    }
    else
    {
      kod.Disp = L.podaci.ins.operand.lit & 0xFFF;
    }
    break;
  }
  return kod;
}

Kod instrukcija_CSRRD(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b1001;
  kod.MOD = 0b0000;
  int reg = L.podaci.ins.regS;
  kod.RegA = reg & 0x0F;
  int csr = 0;
  if (strcmp(L.podaci.ins.operand.simb, "status") == 0)
    csr = 0;
  else if (strcmp(L.podaci.ins.operand.simb, "handler") == 0)
    csr = 1;
  else if (strcmp(L.podaci.ins.operand.simb, "cause") == 0)
    csr = 2;
  kod.RegB = csr & 0x0F;
  kod.RegC = 0b0000;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_CSRWR(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b1001;
  kod.MOD = 0b0100;
  int reg = L.podaci.ins.regS;
  kod.RegB = reg & 0x0F;
  int csr = 0;
  if (strcmp(L.podaci.ins.operand.simb, "status") == 0)
    csr = 0;
  else if (strcmp(L.podaci.ins.operand.simb, "handler") == 0)
    csr = 1;
  else if (strcmp(L.podaci.ins.operand.simb, "cause") == 0)
    csr = 2;
  kod.RegA = csr & 0x0F;
  kod.RegC = 0b0000;
  kod.Disp = 0b000000000000;
  return kod;
}

Kod instrukcija_POP(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b1001;
  kod.MOD = 0b0011;
  int reg = L.podaci.ins.regS;
  kod.RegA = reg & 0x0F;
  kod.RegB = 0b1110;
  kod.RegC = 0b0000;
  kod.Disp = 0b000000000100;
  return kod;
}

Kod instrukcija_PUSH(Linija L)
{
  Kod kod;
  kod.tip = Instr;
  kod.brojLinije = L.broj;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b1000;
  kod.MOD = 0b0001;
  kod.RegA = 0b1110;
  kod.RegB = 0b0000;
  int reg = L.podaci.ins.regS;
  kod.RegC = reg & 0x0F;
  kod.Disp = 0b111111111100;
  return kod;
}

Kod instrukcija_RET()
{
  Kod kod;
  kod.tip = Instr;
  kod.pomeraj = LC;
  kod.sekcija = trenutnaSekcija;
  kod.OC = 0b1001;
  kod.MOD = 0b0011;
  kod.RegA = 0b1111;
  kod.RegB = 0b1110;
  kod.RegC = 0b0000;
  kod.Disp = 0b000000000100;
  return kod;
}

void instrukcija_IRET(std::vector<Kod> &kodovi)
{
  Kod kod1;
  kod1.tip = Instr;
  kod1.pomeraj = LC;
  kod1.sekcija = trenutnaSekcija;
  kod1.OC = 0b1001;
  kod1.MOD = 0b0001;
  kod1.RegA = 0b1110;
  kod1.RegB = 0b1110;
  kod1.RegC = 0b0000;
  kod1.Disp = 0b000000001000;
  kodovi.push_back(kod1);

  Kod kod2;
  kod2.tip = Instr;
  kod2.pomeraj = LC;
  kod2.sekcija = trenutnaSekcija;
  kod2.OC = 0b1001;
  kod2.MOD = 0b0110;
  kod2.RegA = 0b0000;
  kod2.RegB = 0b1110;
  kod2.RegC = 0b0000;
  kod2.Disp = 0b111111111100;
  kodovi.push_back(kod2);

  Kod kod3;
  kod3.tip = Instr;
  kod3.pomeraj = LC;
  kod3.sekcija = trenutnaSekcija;
  kod3.OC = 0b1001;
  kod3.MOD = 0b010;
  kod3.RegA = 0b1111;
  kod3.RegB = 0b1110;
  kod3.RegC = 0b0000;
  kod3.Disp = 0b111111111000;
  kodovi.push_back(kod3);
}