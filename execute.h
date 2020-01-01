/*
 * execute.h
 * COMP 40 Fall 2019 um
 * 
 * Interface for Executive struct and related functions
 *
 * Written by:    Troy Prebenda, Tim Holt
 * Last modified: Nov. 15, 2019
 */

/* ------------------------------- includes -------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "memory.h"

/* ------------------------------- define ---------------------------------- */

#ifndef EXECUTE_INCLUDED
#define EXECUTE_INCLUDED

#define NUM_REG 8
#define INIT_VAL 0

/* ---------------------------- struct defintions -------------------------- */

typedef struct Executive {
    uint32_t registers[NUM_REG];
    uint32_t prog_counter; 
} *Executive;

/* ------------------------------- prototypes------------------------------- */

/* Allocates memory for Executive struct object */
Executive new_Executive();

/* Frees memory allocated for Executive struct object */
void free_Executive(Executive CEO);

/* Executes innstructions from segment 0 */
void execute_inst(Executive CEO, Mem memory);


#endif