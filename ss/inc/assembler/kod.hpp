#ifndef _KOD_HPP
#define _KOD_HPP
#include <cstdint> 
#include <iomanip>
#include <iostream>
using namespace std;
#include <vector>
#include <fstream>
#include "../strukture.hpp"


enum TipKoda{
  Instr,
  Word_s,
  Word_l,
  Skip,
  Ascii
};

struct Kod{
  uint8_t OC: 4;
  uint8_t MOD: 4;
  uint8_t RegA: 4;
  uint8_t RegB: 4;
  uint8_t RegC: 4;
  int16_t Disp : 12;
  TipKoda tip;
  int brojNula;
  int simb;
  int lit;
  int brojLinije;
  int pomeraj;
  int sekcija;
  const char* ascii;
};

struct tabelaSekcija{
  int redniBr;
  const char* naziv;
  int velicina;
};

void bekpecuj(std::vector<Kod>& kodovi);
int izlazniFajl(char* naziv,std::vector<Kod>& kodovi);


#endif