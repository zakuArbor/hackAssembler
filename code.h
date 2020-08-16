#ifndef CODE_H
#define CODE_H

#define JUMP_SIZE 3
#define DEST_SIZE 3
#define COMP_SIZE 6

//INSTRUCTION BIT TYPE
enum instr_type {
    A_INSTR, //0
    C_INSTR, //1
    INVALID,
};

//INSTRUCTION HEADER
#define C_HEADER   "111"
#define A_HEADER   "0"

#define C_HEADER_SIZE 3
#define A_HEADER_SIZE 1

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
#define ZERO       "0101010"
#define ONE        "0111111"
#define NEG_ONE    "0111010"
#define D          "0001100"
#define A          "0110000"
#define NOT_D      "0001101"
#define NOT_A      "0110001"
#define MINUS_D    "0001111"
#define MINUS_A    "0110011"
#define D_PLUS_1   "0011111"
#define A_PLUS_1   "0110111"
#define D_MINUS_1  "0001110"
#define A_MINUS_1  "0110010"
#define D_PLUS_A   "0000010"
#define D_MINUS_A  "0010011"
#define A_MINUS_D  "0000111"
#define D_AND_A    "0000000"
#define D_OR_A     "0010101"

//a = 1
#define M          "1110000"
#define NOT_M      "1110001"
#define MINUS_M    "1110011"
#define M_PLUS_1   "1110111"
#define M_MINUS_1  "1110010"
#define D_PLUS_M   "1000010"
#define D_MINUS_M  "1010011"
#define M_MINUS_D  "1000111"
#define D_AND_M    "1000000"
#define D_OR_M     "1010101"
/**********************/
#endif