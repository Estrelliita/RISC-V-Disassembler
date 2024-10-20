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

signed int extract_i_imm(unsigned int minstr){
    signed int imm = (minstr & 0xfff00000) >> 20;
    if (imm & 0x800) { // Check if negative
      imm |= 0xfffff000; // Sign-extend if necessary
    }
    return imm;
}

int disassemble(unsigned int minstr) {

    unsigned int opcode = (minstr & OPCODEMASK);
    unsigned int rd = (minstr & RDMASK) >> 7;
    unsigned int funct3 = (minstr & FUNCT3MASK) >> 12;
    unsigned int rs1 = (minstr & RS1MASK) >> 15;
    unsigned int rs2 = (minstr & RS2MASK) >> 20;
    unsigned int funct7 = (minstr & FUNCT7MASK) >> 25;
    signed int iimm = extract_i_imm(minstr);
    printf("Opcode: 0x%02X\n", opcode);
    printf("rd: %d\n", rd);
    printf("funct3: %d\n", funct3);
    printf("rs1: %d\n", rs1);
    printf("rs2: %d\n", rs2);
    printf("funct7: %d\n", funct7);
    printf("I-type imm: %d\n", iimm); 
    
    return(0);
}
            
