/* add definitions of masks below */
#define OPCODEMASK 0x7f // 0000 0000 0000 0000 0000 0000 0111 1111
#define RDMASK 0xf80 // 0000 0000 0000 0000 0000 1111 1000 0000
#define FUNCT3MASK 0x7000
#define RS1MASK 0xf8000
#define RS2MASK 0x1f00000
#define FUNCT7MASK 0xfe000000
#define NINSTRUCTIONS 17

enum instruction{ADD, SUB, AND, OR, XOR, SLL, SRL, SRA, ADDI, ANDI, ORI, XORI, SLLI, SRLI, SRAI, LW, SW};

extern int disassemble(unsigned int minstr);
