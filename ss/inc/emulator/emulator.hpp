#ifndef _EMULATOR_HPP
#define _EMULATOR_HPP
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <fstream>
#include <map>
using namespace std;

struct kontekst{
  uint32_t reg[16];
  uint32_t csr[3];
  std::map<uint32_t, uint8_t> memorija;
};

void ucitaj(char* naziv);

extern kontekst kont;
extern bool halt;




#endif