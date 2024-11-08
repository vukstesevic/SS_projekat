ASSEMBLER=./assembler
LINKER=./linker
EMULATOR=./emulator

${ASSEMBLER} -o main.o test/nivo-a/main.s
${ASSEMBLER} -o math.o test/nivo-a/math.s
${ASSEMBLER} -o handler.o test/nivo-a/handler.s
${ASSEMBLER} -o isr_timer.o test/nivo-a/isr_timer.s
${ASSEMBLER} -o isr_terminal.o test/nivo-a/isr_terminal.s
${ASSEMBLER} -o isr_software.o test/nivo-a/isr_software.s
${LINKER} -relocatable\
  -place=my_code@0x40000000 -place=math@0xF0000000 \
  -o program.o \
  handler.o math.o main.o isr_terminal.o isr_timer.o isr_software.o
${LINKER} -hex\
 -place=my_code@0x40000000 -place=math@0xF0000000 \
  -o program.hex \
program.o
${EMULATOR} program.hex