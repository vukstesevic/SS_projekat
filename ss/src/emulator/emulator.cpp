#include "../../inc/emulator/emulator.hpp"
#include "../../inc/emulator/obrada.hpp"
#include "../../inc/emulator/terminal.hpp"
#include "terminal.cpp"
#include <map>

kontekst kont;
bool halt=false;

void ucitaj(char *naziv)
{
  std::ifstream ulaz(naziv);
  if (!ulaz.is_open())
  {
    std::cerr << "Greška pri otvaranju ulaznog fajla!" << std::endl;
  }
  std::string linija;
  while (std::getline(ulaz, linija))
  {
    size_t pozicija = linija.find(':');
    uint32_t adresa = strtol(linija.substr(0, pozicija).c_str(), NULL, 16);
    std::string podaci = linija.substr(pozicija + 2);
    for (size_t i = 0; i < podaci.length(); i += 3)
    {
      std::string byteStr = podaci.substr(i, 2);
      uint8_t heks = (strtol(byteStr.c_str(), NULL, 16));
      kont.memorija.insert({adresa, heks});
      adresa += 1;
    }
  }
/*   for (auto map : kont.memorija)
  {
    cout << std::hex << (int)map.first << " " << std::hex << (int)map.second << endl;
  } */
}

void kraj(){
  cout<<"\n-----------------------------------------------------------------"<<endl;
  cout<<"Emulated processor executed halt instruction"<<endl;
  cout<<"Emulated processor state:"<<endl;
  for(int i=0; i<16;){
    cout<<"r"<<i<<"=0x"<<hex<<setw(8)<<setfill('0')<<kont.reg[i]<<"   "<<"r"<<i+1<<"=0x"<<hex<<setw(8)<<setfill('0')<<kont.reg[i+1]<<"   "<<"r"<<i+2<<"=0x"<<hex<<setw(8)<<setfill('0')<<kont.reg[i+2]<<"   "<<"r"<<i+3<<"=0x"<<hex<<setw(8)<<setfill('0')<<kont.reg[i+3]<<"   "<<endl;
    i+=4;
  }


}



int main(int argc, char *argv[])
{
  kont.reg[15] = 0x40000000;
  kont.reg[0] = 0;
  nonblock(1);
  ucitaj(argv[1]);
  bool dalje = true;
  while (dalje)
  {
    if (akcija()) {
			int c = fgetc(stdin);
			upisimem32(term_in, c);
			if((kont.csr[0] & 0x3) == 0) {
				prekid_terminal();
        cout<<kont.memorija[0xFFFFFF00];
			}
		}
    uint32_t kod = citajmem32(kont.reg[15]);
    dalje = pronadjiInstrukciju(kod);
  }
  
  nonblock(0);

  if(halt) kraj();
}