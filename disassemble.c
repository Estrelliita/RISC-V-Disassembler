#include <stdio.h>
#include "disassemble.h"
#include <stdlib.h>

char mnemonics[NINSTRUCTIONS][5] = {
    "add ", //0
    "sub ", //1
    "and ", //2
    "or  ", //3
    "xor ", //4
    "sll ", //5
    "srl ", //6
    "sra ", //7
    "addi", //8
    "andi", //9
    "ori ", //10
    "xori", //11
    "slli", //12
    "srli",
    "srai", //14
    "lw  ",
    "sw  " //16
};

signed int extract_i_imm(unsigned int minstr){
    signed int imm = (minstr & 0xfff00000) >> 20;
    if (imm & 0x800) { // Check if negative
      imm |= 0xfffff000; // Sign-extend if necessary
    }
    return imm;
}

signed int extract_s_imm(unsigned int minstr){
    signed int imm_11_5 = (minstr & 0xfe000000) >> 25; 
    signed int imm_4_0 = (minstr & 0x00000f80) >> 7;
    signed int imm = (imm_11_5 << 5) | imm_4_0; 
    if (imm & 0x800) { // Check if negative
      imm |= 0xfffff000; // Sign-extend if necessary
    }
    return imm;
}

int disassemble(unsigned int minstr) {

    char instr[20];

    //Format sections
    unsigned int opcode = (minstr & OPCODEMASK);
    unsigned int rd = (minstr & RDMASK) >> 7;
    unsigned int funct3 = (minstr & FUNCT3MASK) >> 12;
    unsigned int rs1 = (minstr & RS1MASK) >> 15;
    unsigned int rs2 = (minstr & RS2MASK) >> 20;
    unsigned int funct7 = (minstr & FUNCT7MASK) >> 25;
    signed int iimm = extract_i_imm(minstr);
    signed int simm = extract_s_imm(minstr);

    //Debugging print statements
    printf("Opcode: 0x%02X\n", opcode);
    printf("rd: %d\n", rd);
    printf("funct3: %d\n", funct3);
    printf("rs1: %d\n", rs1);
    printf("rs2: %d\n", rs2);
    printf("funct7: 0x%02X\n", funct7);
    printf("I-Type imm: %d\n", iimm); 
    printf("S-Type imm: %d\n", simm);

    switch (opcode) {
      case 0x33: // R-type instructions
        switch (funct3) {
          case 0x0: 
            if (funct7 == 0x00) { 
              //add
              sprintf(instr, "%s x%d, x%d, x%d", mnemonics[0], rd, rs1, rs2); break;
            } else if (funct7 == 0x20) {
              //sub
              sprintf(instr, "%s x%d, x%d, x%d", mnemonics[1], rd, rs1, rs2); break;
            } 
            break;
          //xor
          case 0x1: sprintf(instr, "%s x%d, x%d, x%d", mnemonics[5], rd, rs1, rs2); break;
          //srl
          case 0x4: sprintf(instr, "%s x%d, x%d, x%d", mnemonics[4], rd, rs1, rs2); break;
          case 0x5: 
            if (funct7 == 0x00) {
              //srl
              sprintf(instr, "%s x%d, x%d, x%d", mnemonics[6], rd, rs1, rs2); break; 
            } else if (funct7 == 0x20) {
              //sra
              sprintf(instr, "%s x%d, x%d, x%d", mnemonics[7], rd, rs1, rs2); break;
            } break;
          //or
          case 0x6: sprintf(instr, "%s x%d, x%d, x%d", mnemonics[3], rd, rs1, rs2); break;
          //and
          case 0x7: sprintf(instr, "%s x%d, x%d, x%d", mnemonics[2], rd, rs1, rs2); break;
          default: printf("Unknown R-type instruction\n"); exit(-1);
    }
    break;

      case 0x13: // I-type instructions (arithmetic and logical)
        switch (funct3) {
          //addi
          case 0x0: sprintf(instr, "%s x%d, x%d, %d", mnemonics[8], rd, rs1, rs2); break;
          //slli
          case 0x1: sprintf(instr, "%s x%d, x%d, %d", mnemonics[12], rd, rs1, rs2); break;
          //xori
          case 0x4: sprintf(instr, "%s x%d, x%d, %d", mnemonics[11], rd, rs1, rs2); break;
          //ori
          case 0x5: 
            //I am using funct7 even though immediate does not use it because it uses exactly the bits 11:5
            if (funct7 == 0x00){
                //srli
                sprintf(instr, "%s x%d, x%d, %d", mnemonics[13], rd, rs1, rs2); break;
            }
            else if (funct7 == 0x20){
                //srai
                sprintf(instr, "%s x%d, x%d, %d", mnemonics[14], rd, rs1, rs2); break;
            } break;
          case 0x6: sprintf(instr, "%s x%d, x%d, %d", mnemonics[10], rd, rs1, rs2); break;
          //andi 
          case 0x7: sprintf(instr, "%s x%d, x%d, %d", mnemonics[9], rd, rs1, rs2); break;
          default: printf("Unknown or unimplemented I-type instruction\n"); exit(-1);
        } break;
    
      case 0x03: // I-type instructions (load)
        switch (funct3) {
          //lw
          case 0x2: sprintf(instr, "%s x%d, %d(x%d)", mnemonics[15], rd, simm, rs2); break; 
          default: printf("Unknown or unimplemented I-type instruction\n"); exit(-1);
        } break;
    
      case 0x23: // S-type instructions (store)
        switch (funct3) {
          //sw
          case 0x2: sprintf(instr, "%s x%d, %d(x%d)", mnemonics[16], rd, iimm, rs1); break;
          default: printf("Unknown store instruction\n"); exit(-1);
        } break;   
    
      default: printf("Unknown instruction\n"); exit(-1);
    } 
    printf("%s\n", instr);  
    return(0);
}
            
