#include <stdio.h>
#include "disassemble.h"

char mnemonics[NINSTRUCTIONS][5] = {
    "add ",
    "sub ",
    "and ",
    "or  ",
    "xor ",
    "sll ",
    "srl ",
    "sra ",
    "addi",
    "andi",
    "ori ",
    "xori",
    "slli",
    "srli",
    "srai",
    "lw  ",
    "sw  "
};

int disassemble(unsigned int minstr) {

  unsigned int opcode = (mminstr & OPCODEMASK);
  unsigned int rd = (minstr & RDMASK);
  unsigned int funct3 = (minstr & FUNCT3MASK);
  unsigned int rs1 = (minstr & RS1MASK);
  unsigned int rs2 = (minstr & RS2MASK);
  unsigned int funct7 = (minstr & FUNCT7MASK);

    return(0);
}
            
