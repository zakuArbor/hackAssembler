#ifndef CODE_H
#define CODE_H

#define JUMP_SIZE 3
#define DEST_SIZE 3
#define COMP_SIZE 6

//INSTRUCTION BIT TYPE
enum instr_type {
    A_INSTR, //0
    C_INSTR, //1
};

//INSTRUCTION HEADER
#define C_HEADER   "111"
#define A_HEADER   "1"

//JUMPS
#define NULL_J     "000"
#define JGT        "001"
#define JEQ        "010"
#define JGE        "011"
#define JLT        "100"
#define JNE        "101"
#define JLE        "110"
#define JMP        "111"

//DESTINATION
#define NULL_DEST  "000"
#define M_DEST     "001"
#define D_DEST     "010"
#define MD_DEST    "011"
#define A_DEST     "100"
#define AM_DEST    "101"
#define AD_DEST    "110"
#define AMD_DEST   "111"

/*** C-INSTRUCTIONS ***/
//a = 0
#define ZERO       "101010"
#define ONE        "111111"
#define NEG_ONE    "111010"
#define D          "001100"
#define A          "110000"
#define NOT_D      "001101"
#define NOT_A      "110001"
#define MINUS_D    "001111"
#define MINUS_A    "110011"
#define D_PLUS_1   "011111"
#define A_PLUS_1   "110111"
#define D_MINUS_1  "001110"
#define A_MINUS_1  "110010"
#define D_PLUS_A   "000010"
#define D_MINUS_A  "010011"
#define A_MINUS_D  "000111"
#define D_AND_A    "000000"
#define D_OR_A     "010101"

//a = 1
#define M          "110000"
#define NOT_M      "110001"
#define MINUS_M    "110011"
#define M_PLUS_1   "110111"
#define M_MINUS_1  "110010"
#define D_PLUS_M   "000010"
#define D_MINUS_M  "010011"
#define M_MINUS_D  "000111"
#define D_AND_M    "000000"
#define D_OR_M     "010101"
/**********************/
#endif