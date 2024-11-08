#ifndef _INSTRUKCIJE_HPP
#define _INSTRUKCIJE_HPP
#include "../strukture.hpp"
#include "kod.hpp"
using namespace std;
#include <vector>
#include "assembler.hpp"

Kod instrukcija_HALT(Linija L);
Kod instrukcija_INT(Linija L);
void instrukcija_IRET(std::vector<Kod>& kodovi);
Kod instrukcija_RET(); 
Kod instrukcija_CALL(Linija L);
Kod instrukcija_JMP(Linija L);
Kod instrukcija_BEQ(Linija L);
Kod instrukcija_BNE(Linija L);
Kod instrukcija_BGT(Linija L);
Kod instrukcija_PUSH(Linija L);
Kod instrukcija_POP(Linija L);
Kod instrukcija_NOT(Linija L);
Kod instrukcija_XCHG(Linija L);
Kod instrukcija_ADD(Linija L);
Kod instrukcija_SUB(Linija L);
Kod instrukcija_MUL(Linija L);
Kod instrukcija_DIV(Linija L);
Kod instrukcija_AND(Linija L);
Kod instrukcija_OR(Linija L);
Kod instrukcija_XOR(Linija L);
Kod instrukcija_SHL(Linija L);
Kod instrukcija_SHR(Linija L);
Kod instrukcija_LD(Linija L,std::vector<Kod>& kodovi);
Kod instrukcija_ST(Linija L);
Kod instrukcija_CSRRD(Linija L);
Kod instrukcija_CSRWR(Linija L);

#endif
