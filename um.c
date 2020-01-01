/*
 * um.c
 * COMP 40 Fall 2019 um
 * 
 * Driver file for all UM-related instructions/functionality
 *
 * Written by:    Troy Prebenda, Tim Holt
 * Last modified: Nov. 17, 2019
 */


#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "memory.h"
#include "execute.h"

/* Macros */
#define PROG_COUNTER CEO -> prog_counter
#define TOTAL_NUM_INST seg_length(memory, 0)

/* Runs all instructions */
void run_emulator(Mem memory);


int main(int argc, char *argv[])
{

    if (argc != 2) {
        fprintf(stderr, "Must provide .um file for instructions\n");
        exit(EXIT_FAILURE);
    }

    Mem memory = load_instructions(argv[1]);

    run_emulator(memory);

    free_Mem(memory);

    return 0;

}


/* 
 * Function: run_emulator
 * Purpose:  Executes all instructions
 * Input:    Mem memory
 * Output:   none
 * Notes:    
 */ 
void run_emulator(Mem memory)
{

    Executive CEO = new_Executive();
    while (PROG_COUNTER < TOTAL_NUM_INST) {
        execute_inst(CEO, memory);
    }

    free_Executive(CEO);

}