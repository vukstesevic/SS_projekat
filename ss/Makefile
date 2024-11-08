# Imena fajlova
LEXER=misc/lexer.l
PARSER=misc/parser.ypp
LEXER_OUT=lex.yy.cpp
PARSER_OUT=parser.tab.cpp
PARSER_HEADER=parser.tab.hpp
ASSEMBLER=src/assembler/assembler.cpp 
EXTRA_CPP=src/assembler/direktive.cpp src/assembler/instrukcije.cpp src/assembler/kod.cpp
LINKER_CPP=src/linker/linker.cpp 
EMULATOR_CPP=src/emulator/emulator.cpp  src/emulator/obrada.cpp
ASSEMBLER_EXEC=assembler
LINKER_EXEC=linker
EMULATOR_EXEC=emulator  # Emulator executable

# Compiler i flagovi
CXX=g++
CXXFLAGS=-Wall -g

# Ciljevi
all: $(ASSEMBLER_EXEC) $(LINKER_EXEC) $(EMULATOR_EXEC)  # Build all executables

$(ASSEMBLER_EXEC): $(LEXER_OUT) $(PARSER_OUT) $(ASSEMBLER) $(EXTRA_CPP)
	$(CXX) $(CXXFLAGS) -o $@ $(LEXER_OUT) $(PARSER_OUT) $(ASSEMBLER) $(EXTRA_CPP) -lfl

$(LINKER_EXEC): $(LINKER_CPP)
	$(CXX) $(CXXFLAGS) -o $@ $(LINKER_CPP) -lfl

$(EMULATOR_EXEC): $(EMULATOR_CPP)
	$(CXX) $(CXXFLAGS) -o $@ $(EMULATOR_CPP) -lfl

$(LEXER_OUT): $(LEXER) $(PARSER_HEADER)
	flex -o lex.yy.cpp $(LEXER)

$(PARSER_OUT) $(PARSER_HEADER): $(PARSER)
	bison -d -o $(PARSER_OUT) $(PARSER)

clean:
	rm -f $(LEXER_OUT) $(PARSER_OUT) $(PARSER_HEADER) $(ASSEMBLER_EXEC) $(LINKER_EXEC) $(EMULATOR_EXEC)
