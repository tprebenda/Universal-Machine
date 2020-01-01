/*
 * fileio.h
 * COMP 40 Fall 2019 iii
 * 
 * fileio interface. Opens and closes files and detects if file is stdin
 * 
 * Written by:    Rosa Vitiello, Troy Prebenda
 * Last modified: Sep. 27, 2019
 */

/* -------------------------------- includes -------------------------------- */

#include <stdio.h>
#include <stdlib.h>

/* ------------------------------- definitions ------------------------------ */

#ifndef FILEIO_INCLUDED
#define FILEIO_INCLUDED

/* ------------------------------- prototypes ------------------------------- */

FILE *open_read_file(const char *fname);

FILE *open_write_file(const char *fname);

void close_file(FILE *fp);

#endif