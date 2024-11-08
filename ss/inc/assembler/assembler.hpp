#ifndef _ASEMBLER_HPP
#define _ASEMBLER_HPP

#include "../../inc/assembler/instrukcije.hpp"
#include "../../inc/assembler/direktive.hpp"
#include "../../inc/assembler/kod.hpp"


struct TabelaSimbola{
  int redniBr;
  int vrednost;
  int velicina;
  bool globalan;
  bool eksteran;
  int pripadnostSekciji;
  const char* naziv;
};


struct ElementRelokacionaTabela{
  int sekcija;
  int pomeraj;
  char* simbol;
};

struct bekpecing{
  int sekcija;
  int pomeraj;
  int brojLinije;
  char* simbol;
  bool bazen;
};

struct ElementBazenLiterala{
  int sekcija;
  int pomeraj;
  int brojLinije;
  uint32_t literal;
};




extern int LC;
extern int trenutnaSekcija;
extern std::vector<TabelaSimbola> tabelaSimbola;
extern std::vector<ElementRelokacionaTabela> relokacionaTabela;
extern std::vector<ElementBazenLiterala> bazenLiterala;
extern std::vector<bekpecing> bek;


#endif