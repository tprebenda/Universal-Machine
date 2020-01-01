/*
 * unpack.h
 * COMP 40 Fall 2019 um
 * 
 * Interface for interpreting 32bit words as UM instructions
 *
 * Written by:    Troy Prebenda, Tim Holt
 * Last modified: Nov. 15, 2019
 */

/* ------------------------------- includes -------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


/* ------------------------------- define ---------------------------------- */

#ifndef UNPACK_INCLUDED
#define UNPACK_INCLUDED

/* ---------------------------- struct defintions -------------------------- */

/* Struct for all load value instructions */
typedef struct Load_Val {
    uint32_t value;
    uint32_t reg_A;
} *Load_Val;


/* Struct for all other instructions */
typedef struct General_Inst {
    uint32_t op_code;
    uint32_t reg_A, reg_B, reg_C;
} *General_Inst;

/* ------------------------------- prototypes------------------------------- */


/* ALLOCATES MEMORY FOR ASSOCIATED STRUCTS */
Load_Val new_Load_Val();

General_Inst new_General_Inst();


/* FREES MEMORY ALLOCATED FOR ASSOCIATED STRUCTS */
void free_Load_Val(Load_Val obj);

void free_General_Inst(General_Inst obj);


/* Determines whether or not given instruction is a loadval instruction */
bool is_load_inst(uint32_t word);

/* Creates Load_Val object for given word */
Load_Val load_inst(uint32_t word);

/* Creates General_Inst object for given word */
General_Inst gen_inst(uint32_t word);


#endif