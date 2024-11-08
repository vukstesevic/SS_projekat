#ifndef _STRUKTURE_HPP
#define _STRUKTURE_HPP

enum TipOperanda{
  REGISTAR,
  SIMBOL,
  LITERAL
};

enum MemorijskiPristup {
  NEPOSREDNO_LITERAL,
  NEPOSREDNO_SIMBOL,
  DIREKTNO_MEMORIJSKO_LITERAL,
  DIREKTNO_MEMORIJSKO_SIMBOL,
  DIREKTNO_REGISTARSKO,
  INDIREKTNO_REGISTARSKO,
  INDIREKTNO_REGISTARSKO_SIMBOL,
  INDIREKTNO_REGISTARSKO_LITERAL
};

struct Operand{
  TipOperanda tip;
  MemorijskiPristup mem;
  int reg;
  char* simb;
  int lit;
};


enum tipDirektive{
  GLOBAL,
  EXTERN,
  SEKCIJA,
  WORD,
  SKIP,
  ASCII,
  END
};

struct ListaOperanada{
  int broj;
  Operand* operandi;
};

struct Direktiva{
  tipDirektive tip;
  union{
  ListaOperanada operandi;
  char* simb;
  int broj;
  }unija;
};

enum TipInstrukcije{
  HALT,
  INT,
  IRET,
  RET,
  CALL,
  JMP,
  BEQ,
  BNE,
  BGT,
  PUSH,
  POP,
  NOT,
  XCHG,
  ADD,
  SUB,
  MUL,
  DIV,
  AND,
  OR,
  XOR,
  SHL,
  SHR,
  LD,
  ST,
  CSRRD,
  CSRWR
};

struct Instrukcija{
  TipInstrukcije tip;
  int regS;
  int regD;
  Operand operand;
};

enum TipLinije{
  Linija_Instrukcija,
  Linija_Direktiva,
  Linija_Nebitna
};


struct Linija{
  TipLinije tip;
  char* labela;
  int broj;
  union{
    Direktiva dir;
    Instrukcija ins;
  } podaci;
  Linija(){labela=nullptr;}
};

#endif