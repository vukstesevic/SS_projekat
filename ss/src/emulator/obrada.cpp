#include "../../inc/emulator/obrada.hpp"

uint32_t citajmem32(uint32_t adr)
{
  uint8_t dd = kont.memorija[adr];
  uint8_t r3d = kont.memorija[adr + 1];
  uint8_t r1r2 = kont.memorija[adr + 2];
  uint8_t OCMOD = kont.memorija[adr + 3];
  uint32_t povratna = (static_cast<uint32_t>(dd)) |
                      (static_cast<uint32_t>(r3d) << 8) |
                      (static_cast<uint32_t>(r1r2) << 16) |
                      (static_cast<uint32_t>(OCMOD) << 24);
  return povratna;
}

void upisimem32(uint32_t adr, uint32_t pod)
{
  kont.memorija[adr] = static_cast<uint8_t>(pod & 0xFF);
  kont.memorija[adr + 1] = static_cast<uint8_t>((pod >> 8) & 0xFF);
  kont.memorija[adr + 2] = static_cast<uint8_t>((pod >> 16) & 0xFF);
  kont.memorija[adr + 3] = static_cast<uint8_t>((pod >> 24) & 0xFF);
}

bool izvrsiInstrukciju_INT(uint32_t kod)
{
  uint8_t MOD = ((kod << 4) >> 28);
  if (MOD == 0)
  {
    kont.reg[14] -= 4;
    upisimem32(kont.reg[14], kont.csr[0]);
    kont.reg[14] -= 4;
    upisimem32(kont.reg[14], kont.reg[15]);
    kont.csr[2] = 4;
    kont.csr[0] = kont.csr[0] & (~0x1);
    kont.reg[15]= kont.csr[1];
    return true;
  }
  return false;
}

void prekid_terminal(){
    kont.reg[14] -= 4;
    upisimem32(kont.reg[14], kont.csr[0]);
    kont.reg[14] -= 4;
    upisimem32(kont.reg[14], kont.reg[15]);
    kont.csr[2] = 3;
    kont.csr[0] = kont.csr[0] & (~0x1);
    kont.reg[15]= kont.csr[1];
}

bool izvrsiInstrukciju_CALL(uint32_t kod)
{
  uint8_t MOD = ((kod << 4) >> 28);
  uint8_t REGA = ((kod << 8) >> 28);
  uint8_t REGB = ((kod << 12) >> 28);
  uint32_t Disp = ((kod << 20) >> 20);
  if (Disp & 0x800)
    Disp |= 0xFFFFF000;
  if (MOD == 0)
  {
    kont.reg[14] -= 4;
    upisimem32(kont.reg[14], kont.reg[15]);
    kont.reg[15] = kont.reg[REGA] + kont.reg[REGB] + Disp;
    return true;
  }
  else if (MOD == 1)
  {
    kont.reg[14] -= 4;
    upisimem32(kont.reg[14], kont.reg[15]);
    kont.reg[15] = citajmem32(kont.reg[REGA] + kont.reg[REGB] + Disp);
    return true;
  }
  else
  {
    return false;
  }
}

bool izvrsiInstrukciju_JMP(uint32_t kod)
{
  uint8_t MOD = ((kod << 4) >> 28);
  uint8_t REGA = ((kod << 8) >> 28);
  uint8_t REGB = ((kod << 12) >> 28);
  uint8_t REGC = ((kod << 16) >> 28);
  uint32_t Disp = ((kod << 20) >> 20);
  if (Disp & 0x800)
    Disp |= 0xFFFFF000;
  if (MOD == 0)
  {
    kont.reg[15] = kont.reg[REGA] + Disp;
    return true;
  }
  else if (MOD == 1)
  {
    if (kont.reg[REGB] == kont.reg[REGC])
    {
      kont.reg[15] = kont.reg[REGA] + Disp;
    }
    return true;
  }
  else if (MOD == 2)
  {
    if (kont.reg[REGB] != kont.reg[REGC])
    {
      kont.reg[15] = kont.reg[REGA] + Disp;
    }
    return true;
  }
  else if (MOD == 3)
  {
    if (kont.reg[REGB] > kont.reg[REGC])
    {
      kont.reg[15] = kont.reg[REGA] + Disp;
    }
    return true;
  }
  else if (MOD == 8)
  {
    kont.reg[15] = citajmem32(kont.reg[REGA] + Disp);
    return true;
  }
  else if (MOD == 9)
  {
    if (kont.reg[REGB] == kont.reg[REGC])
    {
      kont.reg[15] = citajmem32(kont.reg[REGA] + Disp);
    }
    return true;
  }
  else if (MOD == 10)
  {
    cout<<"R1 R2 "<<(int)kont.reg[1]<<" "<<kont.reg[2]<<endl;
    if (kont.reg[REGB] != kont.reg[REGC])
    {
      kont.reg[15] = citajmem32(kont.reg[REGA] + Disp);
    }
    return true;
  }
  else if (MOD == 11)
  {
    if (kont.reg[REGB] > kont.reg[REGC])
    {
      kont.reg[15] = citajmem32(kont.reg[REGA] + Disp);
    }
    return true;
  }
  return false;
}

bool izvrsiInstrukciju_XCHG(uint32_t kod)
{
  uint8_t REGB = ((kod << 12) >> 28);
  uint8_t REGC = ((kod << 16) >> 28);
  uint32_t temp = kont.reg[REGB];
  kont.reg[REGB] = kont.reg[REGC];
  kont.reg[REGC] = temp;
  return true;
}

bool izvrsiInstrukciju_RACUN(uint32_t kod)
{
  uint8_t MOD = ((kod << 4) >> 28);
  uint8_t REGA = ((kod << 8) >> 28);
  uint8_t REGB = ((kod << 12) >> 28);
  uint8_t REGC = ((kod << 16) >> 28);
  uint32_t Disp = ((kod << 20) >> 20);
  if (Disp & 0x800)
    Disp |= 0xFFFFF000;
  if (MOD == 0)
  {
    kont.reg[REGA] = kont.reg[REGB] + kont.reg[REGC];
    return true;
  }
  else if (MOD == 1)
  {
    kont.reg[REGA] = kont.reg[REGB] - kont.reg[REGC];
    return true;
  }
  else if (MOD == 2)
  {
    kont.reg[REGA] = kont.reg[REGB] * kont.reg[REGC];
    return true;
  }
  else if (MOD == 3)
  {
    kont.reg[REGA] = kont.reg[REGB] / kont.reg[REGC];
    return true;
  }
  return false;
}

bool izvrsiInstrukciju_LOGICKE(uint32_t kod){
  uint8_t MOD = ((kod << 4) >> 28);
  uint8_t REGA = ((kod << 8) >> 28);
  uint8_t REGB = ((kod << 12) >> 28);
  uint8_t REGC = ((kod << 16) >> 28);
  uint32_t Disp = ((kod << 20) >> 20);
  if (Disp & 0x800)
    Disp |= 0xFFFFF000;
  if(MOD==0){
    kont.reg[REGA]=~kont.reg[REGB];
    return true;
  }else if(MOD==1){
    kont.reg[REGA]=kont.reg[REGB] & kont.reg[REGC];
    return true;
  }else if(MOD==2){
    kont.reg[REGA]=kont.reg[REGB] | kont.reg[REGC];
    return true;
  }else if(MOD==3){
    kont.reg[REGA]=kont.reg[REGB] ^ kont.reg[REGC];
    return true;
  }
  return false;
}

bool izvrsiInstrukciju_SIFT(uint32_t kod){
  uint8_t MOD = ((kod << 4) >> 28);
  uint8_t REGA = ((kod << 8) >> 28);
  uint8_t REGB = ((kod << 12) >> 28);
  uint8_t REGC = ((kod << 16) >> 28);
  uint32_t Disp = ((kod << 20) >> 20);
  if (Disp & 0x800)
    Disp |= 0xFFFFF000;
  if(MOD==0){
    kont.reg[REGA]=kont.reg[REGB] << kont.reg[REGC];
    return true;
  }
  if(MOD==1){
    kont.reg[REGA]=kont.reg[REGB] >> kont.reg[REGC];
    return true;
  }
  return false;
}

bool izvrsiInstrukciju_ST(uint32_t kod){
  uint32_t adr;
  bool prom=false;
  bool ispravno=false;
  uint8_t MOD = ((kod << 4) >> 28);
  uint8_t REGA = ((kod << 8) >> 28);
  uint8_t REGB = ((kod << 12) >> 28);
  uint8_t REGC = ((kod << 16) >> 28);
  uint32_t Disp = ((kod << 20) >> 20);
  if (Disp & 0x800)
    Disp |= 0xFFFFF000;
  if(Disp == 0xFFFFFF00U){
   prom=true;
  }
  if(MOD==0){
    adr= kont.reg[REGA]+kont.reg[REGB]+Disp;
    upisimem32(adr, kont.reg[REGC]);
    ispravno= true;
  }else if(MOD==2){
    adr=kont.reg[REGA]+kont.reg[REGB]+Disp;
    adr=citajmem32(adr);
    upisimem32(adr, kont.reg[REGC]);
   ispravno= true;
  }else if(MOD==1){
    kont.reg[REGA]+=Disp;
    upisimem32(kont.reg[REGA],kont.reg[REGC]);
    ispravno= true;
  }
  if(prom){
    cout<<(char)(kont.reg[2]&0x000000FF);
  }
  return ispravno;
}

bool izvrsiInstrukciju_LD (uint32_t kod){
  uint8_t MOD = ((kod << 4) >> 28);
  uint8_t REGA = ((kod << 8) >> 28);
  uint8_t REGB = ((kod << 12) >> 28);
  uint8_t REGC = ((kod << 16) >> 28);
  uint32_t Disp = ((kod << 20) >> 20);
  if (Disp & 0x800)
    Disp |= 0xFFFFF000;
  if(MOD==0){
    kont.reg[REGA]=kont.csr[REGB];
    return true;
  }else if(MOD==1){
    kont.reg[REGA]=kont.reg[REGB]+Disp;
    return true;
  }else if(MOD==2){
    kont.reg[REGA]=citajmem32(kont.reg[REGB]+kont.reg[REGC]+Disp);
    //if((int)REGA==2 || ((int)REGA==1))cout<<"r"<<(int)REGA<<" = "<<hex<<kont.reg[REGA]<<endl;
    return true;
  }else if(MOD==3){
    kont.reg[REGA]=citajmem32(kont.reg[REGB]);
    kont.reg[REGB]=kont.reg[REGB]+Disp;
    return true;
  }
  else if(MOD==4){
    kont.csr[REGA]=kont.reg[REGB];
    return true;
  }else if(MOD==5){
    kont.csr[REGA]=kont.csr[REGB] | Disp;
    return true;
  }else if(MOD==6){
    kont.csr[REGA]=citajmem32(kont.reg[REGB]+kont.reg[REGC]+Disp);
    return true;
  }else if(MOD==7){
    kont.csr[REGA]=citajmem32(kont.reg[REGB]);
    kont.reg[REGB]=kont.reg[REGB]+Disp;
    return true;
  }
  return false;
}


bool pronadjiInstrukciju(uint32_t kod)
{
  kont.reg[15] += 4;
  bool dobro = true;
  switch (kod >> 28 & 0xF)
  {
  case KP_HALT:
    //cout << "Izvrsavam HALT instrukciju" << endl;
    halt=true;
    return false;

  case KP_INT:
    //cout << "Izvrsavam INT instrukciju" << endl;
    dobro = izvrsiInstrukciju_INT(kod);
    if (!dobro)
    {
      cout << "INT Nepoznata operacija!" << endl;
      return false;
    }
    return true;

  case KP_CALL:
    //cout << "Izvrsavam CALL instrukciju" << endl;
    dobro = izvrsiInstrukciju_CALL(kod);
    if (!dobro)
    {
      cout << "Nepoznata operacija!" << endl;
      return false;
    }
    return true;

  case KP_JMP:
    //cout << "Izvrsavam JMP instrukciju" << endl;
    dobro = izvrsiInstrukciju_JMP(kod);
    if (!dobro)
    {
      cout << "Nepoznata operacija!" << endl;
      return false;
    }
    return true;

  case KP_XCHG:
    //cout << "Izvrsavam XCHG instrukciju" << endl;
    dobro = izvrsiInstrukciju_XCHG(kod);
    if (!dobro)
    {
      cout << "Nepoznata operacija!" << endl;
      return false;
    }
    return true;

  case KP_RACUN:
    //cout << "Izvrsavam RACUN instrukciju" << endl;
    dobro = izvrsiInstrukciju_RACUN(kod);
    if (!dobro)
    {
      cout << "Nepoznata operacija!" << endl;
      return false;
    }
    return true;
  case KP_LOGICKE:
    //cout << "Izvrsavam LOGIC instrukciju" << endl;
    dobro = izvrsiInstrukciju_LOGICKE(kod);
    if (!dobro)
    {
      cout << "Nepoznata operacija!" << endl;
      return false;
    }
    return true;
  case KP_SIFT:
    //cout << "Izvrsavam SHIFT instrukciju" << endl;
    dobro = izvrsiInstrukciju_SIFT(kod);
    if (!dobro)
    {
      cout << "Nepoznata operacija!" << endl;
      return false;
    }
    return true;

  case KP_ST:
    //cout << "Izvrsavam ST instrukciju" << endl;
    dobro = izvrsiInstrukciju_ST(kod);
    if (!dobro)
    {
      cout << "Nepoznata operacija!" << endl;
      return false;
    }
    return true;

  case KP_LD:
    //cout << "Izvrsavam LD instrukciju" << endl;
    dobro = izvrsiInstrukciju_LD(kod);
    if (!dobro)
    {
      cout << "LD Nepoznata operacija!" << endl;
      return false;
    }
    return true;

  default:
    cout << "Nepoznata operacija!" << endl;
    return false;
  }
}
