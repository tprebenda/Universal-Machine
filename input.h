/*
 * input.h
 * COMP 40 Fall 2019 um
 * 
 * Interface for processing input file into segment 0
 *
 * Written by:    Troy Prebenda, Tim Holt
 * Last modified: Nov. 15, 2019
 */

/* ------------------------------- includes -------------------------------- */

#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

/* ------------------------------- define ---------------------------------- */

#ifndef INPUT_INCLUDED
#define INPUT_INCLUDED

/* ------------------------------- prototypes------------------------------- */

/* Loads all instructions from given file into segment 0 of memory object */
Mem load_instructions(char *um_file);


#endif