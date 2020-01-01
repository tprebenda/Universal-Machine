/*
 * execute.c
 * COMP 40 Fall 2019 um
 * 
 * Implementation of execute interface
 *
 * Written by:    Troy Prebenda, Tim Holt
 * Last modified: Nov. 17, 2019
 */


#include "math.h"
#include "assert.h"

#include "execute.h"
#include "memory.h"
#include "unpack.h"


/* All UM instructions (not including LoadVal) */
typedef enum Um_opcode {
    CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
    NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;


/* Macro representing 2^32 */
#define MAX_VAL 4294967296

/* Macros for CEO struct data members */
#define REG_A CEO -> registers[inst -> reg_A]
#define REG_B CEO -> registers[inst -> reg_B]
#define REG_C CEO -> registers[inst -> reg_C]
#define LOAD_REG CEO -> registers[load -> reg_A]
#define PROG_COUNTER CEO -> prog_counter


/******************* PRIVATE UM FUNCTION PROTOTYPES **************************/
void execute_load(Executive CEO, Load_Val load);
void execute_cmove(General_Inst inst, Executive CEO);
void execute_sload(General_Inst inst, Executive CEO, Mem memory);
void execute_sstore(General_Inst inst, Executive CEO, Mem memory);
void execute_add(General_Inst inst, Executive CEO);
void execute_mult(General_Inst inst, Executive CEO);
void execute_divide(General_Inst inst, Executive CEO);
void execute_nand(General_Inst inst, Executive CEO);

void execute_halt(General_Inst inst, Executive CEO, Mem memory);
void execute_map(General_Inst inst, Executive CEO, Mem memory);
void execute_unmap(General_Inst inst, Executive CEO, Mem memory);
void execute_output(General_Inst inst, Executive CEO);
void execute_input(General_Inst inst, Executive CEO);
void execute_loadp(General_Inst inst, Executive CEO, Mem memory);


/************************** PUBLIC FUNCTIONS *********************************/

/* 
 * Function: new_Executive
 * Purpose:  ALlocates memory for Executive struct object
 * Input:    none
 * Output:   Executive object
 * Notes:    Sets all registers and program counter to 0
 */ 
Executive new_Executive()
{

    Executive CEO = malloc(sizeof(struct Executive));

    for (int i = 0; i < NUM_REG; i++) {
        CEO -> registers[i] = INIT_VAL;
    }

    PROG_COUNTER = INIT_VAL;

    return CEO;

}


/* 
 * Function: free_Executive
 * Purpose:  Frees memory of given Executive struct object
 * Input:    Executive CEO
 * Output:   none
 * Notes:    
 */ 
void free_Executive(Executive CEO)
{

    free(CEO);

}


/* 
 * Function: execute_inst
 * Purpose:  Gets instruction from segment 0, executes corresponding function
 * Input:    Executive CEO, Mem memory
 * Output:   none
 * Notes:    Creates either a Load_Val struct or a General_Inst struct based
 *           on the instruction being interpreted. Incremements the program
 *           counter, then calls corresponding function for that instruction
 */ 
void execute_inst(Executive CEO, Mem memory)
{

    uint32_t word = get_val(memory, 0, PROG_COUNTER);
    PROG_COUNTER ++;

    /* For any load value instruction */
    if(is_load_inst(word)){
        Load_Val load = load_inst(word);
        execute_load(CEO, load);
        free_Load_Val(load);
    }
    /* For any other instructions */
    else{
        General_Inst instruction = gen_inst(word);
        switch(instruction -> op_code) {
            case CMOV: execute_cmove(instruction, CEO);
                break;
            case SLOAD: execute_sload(instruction, CEO, memory);
                break;
            case SSTORE: execute_sstore(instruction, CEO, memory);
                break;
            case ADD: execute_add(instruction, CEO);
                break;
            case MUL: execute_mult(instruction, CEO);
                break;
            case DIV: execute_divide(instruction, CEO);
                break;
            case NAND: execute_nand(instruction, CEO);
                break;
            case HALT: execute_halt(instruction, CEO, memory);
                break;
            case ACTIVATE: execute_map(instruction, CEO, memory);
                break;
            case INACTIVATE: execute_unmap(instruction, CEO, memory);
                break;
            case OUT: execute_output(instruction, CEO);
                break;
            case IN: execute_input(instruction, CEO);
                break;
            case LOADP: execute_loadp(instruction, CEO, memory);
                break;
            default: assert(false);
        }
        free_General_Inst(instruction);
    }
  
}


/*************************** PRIVATE UM FUNCTIONS ****************************/


/* 
 * Function: execute_load
 * Purpose:  Loads value into register specified by CEO object
 * Input:    Executive CEO, Load_Val load
 * Output:   none
 * Notes:    
 */ 
void execute_load(Executive CEO, Load_Val load)
{

    LOAD_REG = load -> value;

}


/* 
 * Function: execute_cmove
 * Purpose:  Conditional move of values in registers specified by CEO object
 * Input:    General_Inst inst, Executive CEO
 * Output:   none
 * Notes:    
 */ 
void execute_cmove(General_Inst inst, Executive CEO)
{

    if (REG_C != 0) {
        REG_A = REG_B;
    } 

}


/* 
 * Function: execute_sload
 * Purpose:  Loads value from memory into register specified by CEO object
 * Input:    General_Inst inst, Executive CEO, Mem memory
 * Output:   none
 * Notes:    
 */ 
void execute_sload(General_Inst inst, Executive CEO, Mem memory)
{

    REG_A = get_val(memory, REG_B, REG_C);

}


/* 
 * Function: execute_sstore
 * Purpose:  Stores value from segment in register specified by CEO object
 * Input:    General_Inst inst, Executive CEO, Mem memory
 * Output:   none
 * Notes:    
 */ 
void execute_sstore(General_Inst inst, Executive CEO, Mem memory)
{

    put_val(memory, REG_A, REG_B, REG_C);

}


/* 
 * Function: execute_add
 * Purpose:  Adds values from registers specified by CEO object
 * Input:    General_Inst inst, Executive CEO
 * Output:   none
 * Notes:    
 */ 
void execute_add(General_Inst inst, Executive CEO)
{

    REG_A = (REG_B + REG_C) % MAX_VAL;

}


/* 
 * Function: execute_mult
 * Purpose:  Multiplies values from registers specified by CEO object
 * Input:    General_Inst inst, Executive CEO
 * Output:   none
 * Notes:    
 */ 
void execute_mult(General_Inst inst, Executive CEO)
{

    REG_A = (REG_B * REG_C) % MAX_VAL;

}


/* 
 * Function: execute_divide
 * Purpose:  Divides values from registers specified by CEO object
 * Input:    General_Inst inst, Executive CEO
 * Output:   none
 * Notes:    
 */ 
void execute_divide(General_Inst inst, Executive CEO)
{

    REG_A = floor(REG_B / REG_C);

}


/* 
 * Function: execute_nand
 * Purpose:  Performs bitwise nand operation on values from registers specified
 *           by CEO object
 * Input:    General_Inst inst, Executive CEO
 * Output:   none
 * Notes:    
 */ 
void execute_nand(General_Inst inst, Executive CEO)
{

    REG_A =  ~(REG_B & REG_C);
    
}


/* 
 * Function: execute_halt
 * Purpose:  Frees all associated memory and exits the program
 * Input:    General_Inst inst, Executive CEO, Mem memory
 * Output:   none
 * Notes:    
 */ 
void execute_halt(General_Inst inst, Executive CEO, Mem memory)
{

    free_General_Inst(inst);
    free_Executive(CEO);
    free_Mem(memory);

    exit(EXIT_SUCCESS);

}


/* 
 * Function: execute_map
 * Purpose:  Maps new segment in memory, stores its ID in register
 * Input:    General_Inst inst, Executive CEO, Mem memory
 * Output:   none
 * Notes:    
 */ 
void execute_map(General_Inst inst, Executive CEO, Mem memory)
{

    REG_B = map_seg(memory, REG_C);

}


/* 
 * Function: execute_unmap
 * Purpose:  Unmaps given segment in memory
 * Input:    General_Inst inst, Executive CEO, Mem memory
 * Output:   none
 * Notes:    
 */ 
void execute_unmap(General_Inst inst, Executive CEO, Mem memory)
{

    unmap_seg(memory, REG_C);

}


/* 
 * Function: execute_output
 * Purpose:  Prints the value of given register to stdout
 * Input:    General_Inst inst, Executive CEO
 * Output:   none
 * Notes:    
 */ 
void execute_output(General_Inst inst, Executive CEO)
{

    printf("%c", REG_C);

}


/* 
 * Function: execute_input
 * Purpose:  Takes a char from stdin, stores it in given register
 * Input:    General_Inst inst, Executive CEO
 * Output:   none
 * Notes:    Stores ~0 when EOF is the input  
 */ 
void execute_input(General_Inst inst, Executive CEO)
{

    int c = fgetc(stdin);
    uint32_t word;

    if (c == EOF) {
        word = ~0;
    }
    else {
        word = (uint32_t)c;
    }

    REG_C = word;

}


/* 
 * Function: execute_loadp
 * Purpose:  Duplicates segment specified by ID value in register, places it in
 *           position of segment 0 and sets program counter to value 
 *           specified by register
 * Input:    General_Inst inst, Executive CEO, Mem memory
 * Output:   none
 * Notes:    
 */ 
void execute_loadp(General_Inst inst, Executive CEO, Mem memory)
{

    duplicate_seg(memory, REG_B, 0);

    PROG_COUNTER = REG_C;

}