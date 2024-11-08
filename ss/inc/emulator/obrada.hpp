#ifndef _OBRADA_HPP
#define _OBRADA_HPP
#include <cstdint>
#include"emulator.hpp"
using namespace std;

uint32_t citajmem32(uint32_t);
void upisimem32(uint32_t, uint32_t);
bool pronadjiInstrukciju(uint32_t);

bool izvrsiInstrukciju_INT(uint32_t);
bool izvrsiInstrukciju_CALL(uint32_t);
bool izvrsiInstrukciju_JMP(uint32_t);
bool izvrsiInstrukciju_XCHG(uint32_t);
bool izvrsiInstrukciju_RACUN(uint32_t);
bool izvrsiInstrukciju_LOGICKE(uint32_t);
bool izvrsiInstrukciju_SIFT(uint32_t);
bool izvrsiInstrukciju_ST(uint32_t);
bool izvrsiInstrukciju_LD(uint32_t);

void prekid_terminal();

enum kod_operacije{
	KP_HALT = 0,
	KP_INT = 1,
	KP_CALL = 2,
	KP_JMP = 3,
	KP_XCHG = 4,
	KP_RACUN = 5,
	KP_LOGICKE = 6,
	KP_SIFT = 7,
	KP_ST = 8,
	KP_LD = 9
};

#endif
