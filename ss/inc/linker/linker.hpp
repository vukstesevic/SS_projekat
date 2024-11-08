#ifndef _LINKER_HPP
#define _LINKER_HPP
#include <vector>
#include <fstream>
#include <sstream>

struct tabelaSekcija{
    int redniBr;
    std::string naziv;
    int velicina;
};

struct tabelaSimbola {
    std::string naziv;
    int vrednost;
    int velicina;
    int pripadnostSekciji;
    int globalan;
    int eksteran;
};

struct relokacioniUlaz{
  int sekcija;
  int pomeraj;
  std::string simbol;
};

struct Fajl{
  std::vector<relokacioniUlaz> relok;
  std::string kod;
};


struct Fajlovi{
  int rBr;
  std::vector<tabelaSimbola> tabelaSimb;
  std::vector<tabelaSekcija> tabelaSek;
  std::vector<Fajl> sekcije;
};


struct zaPlace{
  std::string naziv;
  uint32_t adresa;
};

struct elementRelokacionaTabela{
  uint32_t baza;
  int pomeraj;
  std::string simbol;
  int brFajla;
};

struct sekcija{
  uint32_t baza;
  std::string naziv;
  int velicina;
  std::vector<elementRelokacionaTabela> relokacije;
  std::string kod;
};

struct simbol{
  std::string naziv;
  uint32_t vrednost;
  std::string pripadnostSekciji;
  uint32_t baza;
  int brFajla;
};


void mapiranje(char* naziv);
std::string readHexString(std::ifstream& ulaz, int numChars);
int readHexInt(std::ifstream& ulaz, int numChars);

extern std::vector<sekcija> sekcije;
extern std::vector<simbol> tabela;
extern std::vector<zaPlace> placeovi;
extern std::vector<Fajlovi> ucitani;
extern bool opcijaHex;
extern bool opcijaReloc;

#endif