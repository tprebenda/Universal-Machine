/*
 * unpack.c
 * COMP 40 Fall 2019 um
 * 
 * Implementation of unpack interface and related function definitions
 *
 * Written by:    Troy Prebenda, Tim Holt
 * Last modified: Nov. 15, 2019
 */

#include <stdio.h>
#include <stdlib.h>

#include "assert.h"

#include "unpack.h"
#include "bitpack.h"

/* Macros */
#define LOAD_CODE 13
#define VAL_SIZE 25
#define VAL_LSB 0

#define OP_CODE_LSB 28
#define OP_CODE_WIDTH 4
#define REG_WIDTH 3
#define A_LSB 6
#define B_LSB 3
#define C_LSB 0

/* 
 * Function: new_Load_Val
 * Purpose:  Allocates memory for Load_Val struct object
 * Input:    none
 * Output:   Load_Val struct object
 * Notes:    
 */ 
Load_Val new_Load_Val()
{

    Load_Val obj = malloc(sizeof(struct Load_Val));
    assert(obj != NULL);

    return obj;

}


/* 
 * Function: new_General_Inst
 * Purpose:  Allocates memory for General_Inst struct object
 * Input:    none
 * Output:   General_Inst struct object
 * Notes:    
 */ 
General_Inst new_General_Inst()
{

    General_Inst obj = malloc(sizeof(struct General_Inst));
    assert(obj != NULL);

    return obj;

}


/* 
 * Function: free_Load_Val
 * Purpose:  Frees memory allocated for given Load_Val struct object
 * Input:    Load_Val obj
 * Output:   none
 * Notes:    
 */ 
void free_Load_Val(Load_Val obj)
{
    free(obj);
}


/* 
 * Function: free_General_Inst
 * Purpose:  Frees memory allocated for given General_Inst struct object
 * Input:    General_Inst obj
 * Output:   none
 * Notes:    
 */ 
void free_General_Inst(General_Inst obj)
{
    free(obj);
}


/* 
 * Function: is_load_inst
 * Purpose:  Determines if given instruction relates to loading values or not
 * Input:    uint32_t word
 * Output:   bool
 * Notes:    
 */ 
bool is_load_inst(uint32_t word)
{

    uint32_t op_code = Bitpack_getu(word, OP_CODE_WIDTH, OP_CODE_LSB);
    return (op_code == LOAD_CODE);

}


/* 
 * Function: load_inst
 * Purpose:  Creates Load_Val struct object and initializes values based
 *           on given word
 * Input:    uint32_t word
 * Output:   (initialized) Load_Val struct object
 * Notes:    
 */ 
Load_Val load_inst(uint32_t word)
{

    Load_Val instruction = new_Load_Val();

    instruction -> reg_A = Bitpack_getu(word, REG_WIDTH, VAL_SIZE);
    instruction -> value = Bitpack_getu(word, VAL_SIZE, VAL_LSB);

    return instruction;

}


/* 
 * Function: gen_inst
 * Purpose:  Creates General_Inst struct object and initializes values based
 *           on given word
 * Input:    uint32_t word
 * Output:   (initialized) General_Inst struct object
 * Notes:    
 */ 
General_Inst gen_inst(uint32_t word)
{

    General_Inst instruction = new_General_Inst();

    instruction -> op_code = Bitpack_getu(word, OP_CODE_WIDTH, OP_CODE_LSB);
    instruction -> reg_A = Bitpack_getu(word, REG_WIDTH, A_LSB);
    instruction -> reg_B = Bitpack_getu(word, REG_WIDTH, B_LSB);
    instruction -> reg_C = Bitpack_getu(word, REG_WIDTH, C_LSB);

    return instruction; 

}