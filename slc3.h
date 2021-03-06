/*
TCSS372 - Computer Architecture
Problem #4
Group Members: 
Shaun Coleman
Phansa Chaonpoj
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// States
#define FETCH 0
#define DECODE 1
#define EVAL_ADDR 2
#define FETCH_OP 3
#define EXECUTE 4
#define STORE 5

#define REG_SIZE 8
#define IO_REG 0
#define RETURN_REG 7
#define SP_REG 6

// Opcodes
#define ADD 1
#define AND 5
#define NOT 9
#define TRAP 15
#define LD 2
#define ST 3
#define JMP 12 // and RET
#define BR 0
#define LEA 14
#define JSR 4 // and JSRR
#define STR 7
#define LDR 6

// Macros to get IR bit fields
#define OPCODE(instr)  (instr >> 12 & 0x000F)
#define DSTREG(instr)  (instr >> 9 & 0x0007)
#define SRCREG(instr)  (instr >> 6 & 0x0007)
#define SRCREG2(instr)  (instr & 0x0007)
#define IMMBIT(instr)  ((instr & 0x0020) >> 5) 
#define NBIT(instr)  ((instr & 0x0800) >> 11) 
#define ZBIT(instr)  ((instr & 0x0400) >> 10) 
#define PBIT(instr)  ((instr & 0x0200) >> 9) 
 
// ZEXT trap
#define ZEXTTRAPVECT(instr) (instr & 0x00FF)

// SEXT
#define SEXTPCOFFSET9(instr) ((instr << 23 ) >> 23)
#define SEXTPCOFFSET6(instr)  ((instr << 26) >> 26) 
#define SEXTIMMVAL(instr)  ((instr << 27) >> 27) 

// Trap Vectors
#define GETCH 0x0020
#define OUT 0x0021
#define PUTS 0x0022
#define HALT 0x0025

// Constants
#define MAXMEM 65536
#define HEX_MODE 16
#define EXPECTED_HEX_DIGITS 4
#define MENU_SELECTION 0
#define SINGLE_CHAR 1
#define NULL_CPU_POINTER -1
#define NULL_MEMORY_POINTER -2


// Condition Codes
typedef struct {
  unsigned short n : 1;
  unsigned short z : 1;
  unsigned short p: 1;
} CC_s;

typedef struct {
    unsigned short reg_file[REG_SIZE];
    unsigned short mar, mdr, ir, pc;
    unsigned short alu_a, alu_b, alu_r;
    CC_s conCodes;
} CPU_s;

typedef CPU_s* CPU_p;