%{
  #include <vector>
  #include "inc/strukture.hpp"
  #include "parser.tab.hpp"

  #include <iostream>
  using namespace std;

  extern "C" int yylex();
  int brojLinije=0;
%}


%option nounput
%option noyywrap



GLOBAL ^\.global
EXTERN ^\.extern
SECTION ^\.section
WORD ^\.word
SKIP ^\.skip 
ASCII ^\.ascii
END ^\.end 

HALT halt 
INT int
IRET iret 
CALL call 
RET ret
JMP jmp 
BEQ beq 
BNE bne 
BGT bgt 
PUSH push 
POP pop
XCHG xchg 
ADD add 
SUB sub 
MUL mul 
DIV div 
NOT not 
AND and 
OR or 
XOR xor 
SHL shl 
SHR shr 
LD ld 
ST st 
CSRRD csrrd 
CSRWR csrwr 

GPR (%r([0-9]|1[0-3]))
SP (%sp|%r14)
PC (%pc|%r15)
STATUS status
HANDLER handler
CAUSE cause

OZAGRADA \(
ZZAGRADA \)
OUGLASTA \[
ZUGLASTA   \]
PLUS \+
MINUS -
PROCENAT %
DOLAR \$
TACKAZAPETA ;
DVETACKE :
ZAPETA ,
ZVEZDICA \*

LABELA [a-zA-Z_][a-zA-Z0-9_]*[ \t]*:
SIMBOL [a-zA-Z_.][a-zA-Z0-9_.]*
NOVIRED \n
NULA 0
BROJ [1-9][0-9]*
HEKSA 0[xX][0-9a-fA-F]+
KOMENTAR #.*
STRING \"[^"]+\" 
PRAZNO \s*

%%

{GLOBAL} {cout<<"DIREKTIVA GLOBAL "; return DIREKTIVA_GLOBAL;}
{EXTERN} {cout<<"DIREKTIVA EXTERN "; return DIREKTIVA_EXTERN;}
{SECTION} {cout<<"DIREKTIVA SECTIONA "; return DIREKTIVA_SECTION;}
{WORD} {cout<<"DIREKTIVA WORD "; return DIREKTIVA_WORD;}
{SKIP} {cout<<"DIREKTIVA SKIP "; return DIREKTIVA_SKIP;}
{ASCII} {cout<<"DIREKTIVA ASCII "; return DIREKTIVA_ASCII;}
{END} {cout<<"DIREKTIVA END "; return DIREKTIVA_END;}

{HALT} {cout<<"INSTRUKCIJA HALT "; return INSTRUKCIJA_HALT;} 
{INT} {cout<<"INSTRUKCIJA INT "; return INSTRUKCIJA_INT;}
{IRET} {cout<<"INSTRUKCIJA IRET "; return INSTRUKCIJA_IRET;} 
{CALL} {cout<<"INSTRUKCIJA CALL "; return INSTRUKCIJA_CALL;}
{RET} {cout<<"INSTRUKCIJA RET "; return INSTRUKCIJA_RET;}
{JMP} {cout<<"INSTRUKCIJA JMP "; return INSTRUKCIJA_JMP;}
{BEQ} {cout<<"INSTRUKCIJA BEQ "; return INSTRUKCIJA_BEQ;}
{BNE} {cout<<"INSTRUKCIJA BNE "; return INSTRUKCIJA_BNE;}
{BGT} {cout<<"INSTRUKCIJA BGT "; return INSTRUKCIJA_BGT;}
{PUSH} {cout<<"INSTRUKCIJA PUSH " ;return INSTRUKCIJA_PUSH;}
{POP} {cout<<"INSTRUKCIJA POP " ;return INSTRUKCIJA_POP;}
{XCHG} {cout<<"INSTRUKCIJA XCHG "; return INSTRUKCIJA_XCHG;}
{ADD} {cout<<"INSTRUKCIJA ADD "; return INSTRUKCIJA_ADD;}
{SUB} {cout<<"INSTRUKCIJA SUB "; return INSTRUKCIJA_SUB;}
{MUL} {cout<<"INSTRUKCIJA MUL ";return INSTRUKCIJA_MUL;}
{DIV} {cout<<"INSTRUKCIJA DIV "; return INSTRUKCIJA_DIV;}
{NOT} {cout<<"INSTRUKCIJA NOT "; return INSTRUKCIJA_NOT;}
{AND} {cout<<"INSTRUKCIJA AND ";return INSTRUKCIJA_AND;}
{OR} {cout<<"INSTRUKCIJA OR "; return INSTRUKCIJA_OR;}
{XOR} {cout<<"INSTRUKCIJA XOR ";return INSTRUKCIJA_XOR;}
{SHL} {cout<<"INSTRUKCIJA SHL ";return INSTRUKCIJA_SHL;}
{SHR} {cout<<"INSTRUKCIJA SHR ";return INSTRUKCIJA_SHR;}
{LD} {cout<<"INSTRUKCIJA LD ";return INSTRUKCIJA_LD;}
{ST} {cout<<"INSTRUKCIJA ST ";return INSTRUKCIJA_ST;}
{CSRRD} {cout<<"INSTRUKCIJA CSRRD "; return INSTRUKCIJA_CSRRD;}
{CSRWR} {cout<<"INSTRUKCIJA CSRWR "; return INSTRUKCIJA_CSRWR;}

{GPR} {cout<<"REGISTAR ";yylval.reg = atoi(yytext+2); return TOKEN_REG;}
{SP} {cout<<"SP ";yylval.reg=14; return TOKEN_REG;}
{PC} {cout<<"PC ";yylval.reg=15; return TOKEN_REG;}


{OZAGRADA} {cout<<"OTVORENA ZAGRADA "; return TOKEN_OZAGRADA;}
{ZZAGRADA} {cout<<"ZATVORENA ZAGRADA "; return TOKEN_ZZAGRADA;}
{OUGLASTA} {cout<<"OTVORENA UGLASTA "; return TOKEN_OUGLASTA;}
{ZUGLASTA} {cout<<"ZATVORENA UGLASTA "; return TOKEN_ZUGLASTA;}
{PLUS} {cout<<"PLUS ";return TOKEN_PLUS;}
{MINUS} {cout<<"MINUS ";return TOKEN_MINUS;}
{PROCENAT} {cout<<"PROCENAT ";return TOKEN_PROCENAT;}
{DOLAR} {cout<<"DOLAR ";return TOKEN_DOLAR;}
{TACKAZAPETA} {cout<<"TACKAZAPETA ";return TOKEN_TACKAZAPETA;}
{DVETACKE} {cout<<"DVETACKE ";return TOKEN_DVETACKE;}
{ZAPETA} {cout<<"ZAPETA "; return TOKEN_ZAPETA;}
{ZVEZDICA} {cout<<"ZVEZDICA ";return TOKEN_ZVEZDICA;}

{LABELA} {cout<<"LABELA "; yylval.labela = strdup(yytext); 
    for(int i=0; yylval.labela[i]!='\0';i++){
      char c = yylval.labela[i];
        if (c == '\t' || c == ' ' || c == ':') {
            yylval.labela[i] = '\0';
            break;
        }
    }
    return TOKEN_LABELA;}
{SIMBOL} {cout<<"SIMBOL ";yylval.simbol = strdup(yytext); return TOKEN_SIMBOL;}
{NOVIRED} {cout<< endl; brojLinije++; return TOKEN_NOVIRED;}
{NULA} {cout<<"BROJ "; yylval.broj=0; return TOKEN_BROJ;}
{BROJ}  {cout<<"BROJ "; yylval.broj=atoi(yytext); return TOKEN_BROJ;}
{HEKSA} {cout<<"BROJ "; yylval.broj=strtol(yytext + 2, NULL, 16); return TOKEN_BROJ;}
{KOMENTAR} {return TOKEN_KOMENTAR;}
{STRING} {cout<<"STRING "; yytext[strlen(yytext) - 1] = '\0'; yylval.string = strdup(yytext + 1); cout<<yylval.string; return TOKEN_STRING;}
{PRAZNO} {}
. ;
%%



void yyerror(std::vector<Linija>& linije, const char *s){
  fprintf(stderr, "Greška na liniji %d: %s\n", brojLinije, s);
}
