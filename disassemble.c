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
    printf("I-Type imm: 0x%02X\n", iimm); 
    printf("R-Type imm: 0x%02X\n", simm);

    switch (opcode) {
      case 0x33: // R-type instructions
        switch (funct3) {
          case 0x0: 
            if (funct7 == 0x00) {
              sprintf(instr, "%s, x%d, x%d, x%d", mnemonics[0], rd, rs1, rs2); break;
            } else if (funct7 == 0x20) {
              sprintf(instr, "%s, x%d, x%d, x%d", mnemonics[1], rd, rs1, rs2); break;
            } 
            break;
          case 0x1: printf("sll "); break;
          case 0x2: printf("slt "); break;
          case 0x4: printf("xor "); break;
          case 0x5: 
            if (funct7 == 0x00) {
              printf("srl "); 
            } else if (funct7 == 0x20) {
              printf("sra ");
            } 
            break;
          case 0x6: printf("or  "); break;
          case 0x7: printf("and "); break;
          default: printf("Unknown R-type instruction\n");
    }
    // ... (code to print rd, rs1, rs2) ...
    break;

  case 0x13: // I-type instructions (arithmetic and logical)
    switch (funct3) {
      case 0x0: printf("addi"); break;
      case 0x4: printf("xori"); break;
      case 0x6: printf("ori "); break;
      case 0x7: printf("andi"); break;
      default: printf("Unknown I-type instruction\n"); 
    }
    // ... (code to print rd, rs1, immediate) ...
    break;

  case 0x03: // I-type instructions (load)
    switch (funct3) {
      case 0x2: printf("lw  "); break; 
      // ... (add cases for other load instructions like lh, lb, lhu, lbu) ...
      default: printf("Unknown load instruction\n");
    }
    // ... (code to print rd, rs1, immediate) ...
    break;

  case 0x23: // S-type instructions (store)
    switch (funct3) {
      case 0x2: printf("sw  "); break;
      // ... (add cases for other store instructions like sh, sb) ...
      default: printf("Unknown store instruction\n");
    }
    // ... (code to print rs2, rs1, immediate) ...
    break;

  // ... (add cases for other opcode types as needed) ... 

  default: printf("Unknown instruction\n");
  }
    printf("%s\n", instr);  
    return(0);
}
            
